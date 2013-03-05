/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.  <rvinyard@cs.nmsu.edu>    *
 *   Copyright (C) 2011-2013 by Tim Niemueller [http://www.niemueller.de]  *
 *                                                                         *
 *   This file is part of the clipsmm library.                             *
 *                                                                         *
 *   The clipsmm library is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License           *
 *   version 3 as published by the Free Software Foundation.               *
 *                                                                         *
 *   The clipsmm library is distributed in the hope that it will be        *
 *   useful, but WITHOUT ANY WARRANTY; without even the implied warranty   *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   *
 *   General Public License for more details.                              *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this software. If not see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
#include "environment.h"

#include <stdexcept>

extern "C" {
  #include <clips/clips.h>
};

#include <clipsmm/utility.h>

namespace CLIPS {

std::map<void*, Environment*> Environment::m_environment_map;

Environment::Environment():
  m_run_thread(NULL)
{
  m_cobj = CreateEnvironment();

  m_environment_map[m_cobj] = this;

  if ( EnvAddClearFunction( m_cobj, (char *)"clipsmm_clear_callback", Environment::clear_callback, 2001 ) == 0 )
    throw std::logic_error("clipsmm: Error adding clear callback to clips environment");
  if ( EnvAddPeriodicFunction( m_cobj, (char *)"clipsmm_periodic_callback", Environment::periodic_callback, 2001 ) == 0 )
    throw std::logic_error("clipsmm: Error adding periodic callback to clips environment");
  if ( EnvAddResetFunction( m_cobj, (char *)"clipsmm_reset_callback", Environment::reset_callback, 2001 ) == 0 )
    throw std::logic_error("clipsmm: Error adding reset callback to clips environment");
  if ( EnvAddRunFunction( m_cobj, (char *)"clipsmm_rule_firing_callback", Environment::rule_firing_callback, 2001 ) == 0 )
    throw std::logic_error("clipsmm: Error adding rule firing callback to clips environment");
}

Environment::~Environment()
{
  EnvRemoveClearFunction( m_cobj, (char *)"clipsmm_clear_callback" );
  EnvRemovePeriodicFunction( m_cobj, (char *)"clipsmm_periodic_callback" );
  EnvRemoveResetFunction( m_cobj, (char *)"clipsmm_reset_callback" );
  EnvRemoveRunFunction( m_cobj, (char *)"clipsmm_rule_firing_callback" );

  m_environment_map.erase(m_cobj);

  DestroyEnvironment( m_cobj );

  std::map<std::string, char *>::iterator r;
  for (r = m_func_restr.begin(); r != m_func_restr.end(); ++r) {
    free(r->second);
  }
  m_func_restr.clear();
}

bool Environment::batch_evaluate( const std::string& filename ) {
  return EnvBatchStar( m_cobj, const_cast<char*>( filename.c_str() ) );
}

bool Environment::binary_load( const std::string& filename ) {
  return EnvBload( m_cobj, const_cast<char*>( filename.c_str() ) );
}

bool Environment::binary_save( const std::string& filename ) {
  return EnvBsave( m_cobj, const_cast<char*>( filename.c_str() ) );
}

bool Environment::build( const std::string& construct ) {
  return EnvBuild( m_cobj, const_cast<char*>( construct.c_str() ) );
}

void Environment::clear( ) {
  EnvClear( m_cobj );
}

int Environment::load( const std::string& filename )
{
  return EnvLoad( m_cobj, const_cast<char*>( filename.c_str() ) );
}

void Environment::reset( )
{
  EnvReset( m_cobj );
}

bool Environment::save( const std::string& filename )
{
  return EnvSave( m_cobj, const_cast<char*>( filename.c_str() ) );
}

bool Environment::is_dribble_active( ) {
  return EnvDribbleActive( m_cobj );
}

bool Environment::dribble_off( ) {
  return EnvDribbleOff( m_cobj );
}

bool Environment::dribble_on( const std::string& filename )
{
  return EnvDribbleOn( m_cobj, const_cast<char*>( filename.c_str() ) );
}

int Environment::is_watched( const std::string& item ) {
  return EnvGetWatchItem( m_cobj, const_cast<char*>( item.c_str() ) );
}

bool Environment::watch( const std::string& item )
{
  return EnvWatch( m_cobj, const_cast<char*>( item.c_str() ) );
}

bool Environment::unwatch( const std::string& item )
{
  return EnvUnwatch( m_cobj, const_cast<char*>( item.c_str() ) );
}

long int Environment::run( long int runlimit )
{
  long int executed;
  m_mutex_run.lock(); // Grab the lock before running
  executed = EnvRun( m_cobj, runlimit ); // Run CLIPS
  m_mutex_run_signal.lock(); // Lock the emit signal to guarantee that another run doesn't emit first
  m_mutex_run.unlock(); // Unlock the run, because we have the signal lock
  m_signal_run.emit(executed); // Emit the signal for this run
  m_mutex_run_signal.unlock(); // Unlock the signal
  return executed;
}

void Environment::run_threaded( long int runlimit, int priority ) {
  // No matter what, let's start by grabbing the run queue lock
  // If we have it here, we can safely test for the run lock next because we would
  // stall the thread before it does it's while() check
  m_mutex_run_queue.lock();
  if ( m_mutex_threaded_run.trylock() ) {
    m_run_queue.push( Job( priority, runlimit ) );
    m_mutex_run.lock();
    // Will enter thread with run queue, threaded run, and run locks
    m_run_thread = Glib::Thread::create( sigc::mem_fun(*this, &Environment::threaded_run), true );
    // But, this function is done and will return, with the locks safely in the hands of the thread
    return;
  } else {
    // If we got here, then a thread is already running, we have the queue
    // so, push on the new job
    m_run_queue.push( Job( priority, runlimit ) );
    m_mutex_run_queue.unlock();
    return;
  }
}

void Environment::join_run_thread() {
  m_mutex_run_queue.lock();
  if ( m_mutex_threaded_run.trylock() ) {
    // If we got here, we have the queue and the threaded run locked
    // That means there wasn't a thread already running, so we need to
    // release both locks and return since there isn't anything to join.
    m_mutex_threaded_run.unlock();
    m_mutex_run_queue.unlock();
    return;
  }
  else {
    // If we got here, we got the run queue lock, but couldn't get the threaded run
    // lock. That means the thread is running, but we have the lock. We need to
    // release the queue lock and call join, then return.
    m_mutex_run_queue.unlock();
    m_run_thread->join();
    return;
  }
}

sigc::signal<void,long int> Environment::signal_run() {
  return m_signal_run;
}

void Environment::threaded_run() {
  long int executed;
  long int current_runlimit;

  // We have the run queue, threaded run, and run locks here
  while ( m_run_queue.size() > 0 ) {
    current_runlimit = m_run_queue.top().runlimit;
    m_run_queue.pop();

    // We have the top job, let's release the queue until we need it again
    m_mutex_run_queue.unlock();

    executed = EnvRun( m_cobj, current_runlimit ); // Run CLIPS

    m_mutex_run_signal.lock(); // Grab the signal lock, signal and release it
    m_signal_run.emit(executed);
    m_mutex_run_signal.unlock();

    // Make sure the queue is locked again while we check the size
    m_mutex_run_queue.lock();
  }

  // Here, we still have the queue lock, so we can start releasing the other locks
  m_mutex_threaded_run.unlock();
  m_mutex_run.unlock();
  m_mutex_run_queue.unlock();
}

void Environment::set_as_current( )
{
  SetCurrentEnvironment( m_cobj );
}

void Environment::clear_focus_stack( )
{
  EnvClearFocusStack( m_cobj );
}

bool Environment::auto_float_dividend_enabled() {
  return EnvGetAutoFloatDividend( m_cobj );
}

bool Environment::use_auto_float_dividend(bool use) {
  return EnvSetAutoFloatDividend( m_cobj, use );
}

bool Environment::dynamic_constraint_checking_enabled() {
  return EnvGetDynamicConstraintChecking( m_cobj );
}

bool Environment::use_dynamic_constraint_checking(bool use) {
  return EnvSetDynamicConstraintChecking( m_cobj, use );
}

bool Environment::sequence_operator_recognition_enabled() {
  return EnvGetSequenceOperatorRecognition( m_cobj );
}

bool Environment::use_sequence_operator_recognition(bool use) {
  return EnvSetSequenceOperatorRecognition( m_cobj, use );
}

bool Environment::static_constraint_checking_enabled() {
  return EnvGetStaticConstraintChecking( m_cobj );
}

bool Environment::use_static_constraint_checking(bool use) {
  return EnvSetStaticConstraintChecking( m_cobj, use );
}

bool Environment::fact_duplication_enabled() {
  return EnvGetFactDuplication( m_cobj );
}

bool Environment::use_fact_duplication(bool use) {
  return EnvSetFactDuplication( m_cobj, use );
}

bool Environment::global_reset_enable() {
  return EnvGetResetGlobals( m_cobj );
}

bool Environment::use_global_reset( bool use ) {
  return EnvSetResetGlobals( m_cobj, use );
}


Fact::pointer
Environment::get_facts()
{
  void *f = EnvGetNextFact(m_cobj, NULL);
  if (f) {
    return Fact::create(*this, f);
  } else {
    return Fact::pointer();
  }
}

DefaultFacts::pointer Environment::get_default_facts( const std::string & default_facts_name )
{
  void* deffacts;
  deffacts = EnvFindDeffacts( m_cobj, const_cast<char*>(default_facts_name.c_str()) );
  if ( deffacts )
    return DefaultFacts::create( *this, deffacts );
  else
    return DefaultFacts::pointer();
}

std::vector< std::string > Environment::get_default_facts_names( )
{
  DATA_OBJECT clipsdo;
  EnvGetDeffactsList( m_cobj, &clipsdo, NULL );
  return data_object_to_strings( clipsdo );
}

std::vector<std::string> Environment::get_default_facts_names(const Module& module) {
  DATA_OBJECT clipsdo;
  if ( module.cobj() ) {
    EnvGetDeffactsList( m_cobj, &clipsdo, module.cobj() );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

std::vector<std::string> Environment::get_default_facts_names(Module::pointer module) {
  DATA_OBJECT clipsdo;
  if ( module && module->cobj() ) {
    EnvGetDeffactsList( m_cobj, &clipsdo, module->cobj() );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

DefaultFacts::pointer Environment::get_default_facts_list_head( )
{
  void* df;
  df = EnvGetNextDeffacts( m_cobj, NULL );
  if (df)
    return DefaultFacts::create( *this, df );
  else
    return DefaultFacts::pointer();
}

Template::pointer Environment::get_template( const std::string & template_name )
{
  if ( ! m_cobj )
    return Template::pointer();

  void* tem = EnvFindDeftemplate( m_cobj, const_cast<char*>( template_name.c_str() ) );

  if ( !tem )
    return Template::pointer();

  return Template::create( *this, tem );
}

std::vector< std::string > Environment::get_template_names( )
{
  DATA_OBJECT clipsdo;
  EnvGetDeftemplateList( m_cobj, &clipsdo, NULL );
  return data_object_to_strings( clipsdo );
}

std::vector<std::string> Environment::get_template_names(const Module& module) {
  DATA_OBJECT clipsdo;
  if ( module.cobj() ) {
    EnvGetDeftemplateList( m_cobj, &clipsdo, module.cobj() );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

std::vector<std::string> Environment::get_template_names(Module::pointer module) {
  DATA_OBJECT clipsdo;
  if ( module && module->cobj() ) {
    EnvGetDeftemplateList( m_cobj, &clipsdo, module->cobj() );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

Template::pointer Environment::get_template_list_head( )
{
  void* tem;
  tem = EnvGetNextDeftemplate( m_cobj, NULL );
  if (tem)
    return Template::create( *this, tem );
  else
    return Template::pointer();
}

Rule::pointer Environment::get_rule( const std::string & rule_name )
{
  void* rule;
  rule = EnvFindDefrule( m_cobj, const_cast<char*>(rule_name.c_str()) );
  if ( rule )
    return Rule::create( *this, rule );
  else
    return Rule::pointer();
}

std::vector< std::string > Environment::get_rule_names( )
{
  DATA_OBJECT clipsdo;
  EnvGetDefruleList( m_cobj, &clipsdo, NULL );
  return data_object_to_strings( clipsdo );
}

std::vector<std::string> Environment::get_rule_names(const Module& module) {
  DATA_OBJECT clipsdo;
  if ( module.cobj() ) {
    EnvGetDefruleList( m_cobj, &clipsdo, module.cobj() );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

std::vector<std::string> Environment::get_rule_names(Module::pointer module) {
  DATA_OBJECT clipsdo;
  if ( module && module->cobj() ) {
    EnvGetDefruleList( m_cobj, &clipsdo, module->cobj() );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

Rule::pointer Environment::get_rule_list_head( )
{
  void* r;
  r = EnvGetNextDefrule( m_cobj, NULL );
  if (r)
    return Rule::create( *this, r );
  else
    return Rule::pointer();
}

void Environment::remove_rules( )
{
  EnvUndefrule( m_cobj, NULL );
}

Fact::pointer Environment::assert_fact( const std::string& factstring )
{
  void* clips_fact = EnvAssertString( m_cobj, const_cast<char*>(factstring.c_str()) );
  if ( clips_fact )
    return Fact::create( *this, clips_fact );
  else
    return Fact::pointer();
}


Fact::pointer Environment::assert_fact( Fact::pointer fact )
{
  void* clips_fact = EnvAssert( m_cobj, fact->cobj() );
  if ( clips_fact )
    return Fact::create( *this, clips_fact );
  else
    return Fact::pointer();
}


Fact::pointer Environment::assert_fact_f(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  char *factstring;
  int vasprintf_rv = vasprintf(&factstring, format, args);
  va_end(args);

  if (vasprintf_rv != -1) {
    void* clips_fact = EnvAssertString( m_cobj, factstring);
    free(factstring);
    if ( clips_fact )
      return Fact::create( *this, clips_fact );
    else
      return Fact::pointer();
  } else {
    return Fact::pointer();
  }
}

bool Environment::incremental_reset_enabled( )
{
  return EnvGetIncrementalReset( m_cobj );
}

bool Environment::use_incremental_reset( bool use )
{
  return EnvSetIncrementalReset( m_cobj, use );
}

Module::pointer Environment::get_module( const std::string & module_name )
{
  void* module;
  module = EnvFindDefmodule( m_cobj, const_cast<char*>(module_name.c_str()) );
  if (module)
    return Module::create( *this, module );
  else
    return Module::pointer();
}

Module::pointer Environment::get_current_module( )
{
  void* module;
  module = EnvGetCurrentModule( m_cobj );
  if ( module )
    return Module::create( *this, module );
  else
    return Module::pointer();
}

Module::pointer Environment::get_focused_module( )
{
  void* module;
  module = EnvGetFocus( m_cobj );
  if ( module )
    return Module::create( *this, module );
  else
    return Module::pointer();
}

std::vector<std::string> Environment::get_focus_stack() {
  DATA_OBJECT clipsdo;
  EnvGetFocusStack( m_cobj, &clipsdo );
  return data_object_to_strings( clipsdo );
}

Activation::pointer Environment::get_activation_list_head( )
{
  void* head;
  head = EnvGetNextActivation( m_cobj, NULL );
  if (head)
    return Activation::create( *this, head );
  else
    return Activation::pointer();
}

void Environment::refresh_agenda() {
  EnvRefreshAgenda( m_cobj, NULL );
}

void Environment::refresh_agenda(const Module& module) {
  if ( module.cobj() )
    EnvRefreshAgenda( m_cobj, module.cobj() );
}

void Environment::refresh_agenda(Module::pointer module) {
  if ( module && module->cobj() )
    EnvRefreshAgenda( m_cobj, module->cobj() );
}

void Environment::reorder_agenda() {
  EnvReorderAgenda( m_cobj, NULL );
}

void Environment::reorder_agenda(const Module& module) {
  if ( module.cobj() )
    EnvReorderAgenda( m_cobj, module.cobj() );
}

void Environment::reorder_agenda(Module::pointer module) {
  if ( module && module->cobj() )
    EnvReorderAgenda( m_cobj, module->cobj() );
}

SalienceEvaluation Environment::get_salience_evaluation( )
{
  return (SalienceEvaluation) EnvGetSalienceEvaluation( m_cobj );
}

SalienceEvaluation Environment::set_salience_evaluation( SalienceEvaluation se )
{
  return (SalienceEvaluation) EnvSetSalienceEvaluation( m_cobj, se );
}

ConflictResolution Environment::get_conflict_resolution_strategy( )
{
  return (ConflictResolution) EnvGetStrategy( m_cobj );
}

ConflictResolution Environment::set_conflict_resolution_strategy( ConflictResolution cr )
{
  return (ConflictResolution) EnvSetStrategy( m_cobj, cr );
}

std::vector< std::string > Environment::get_module_names( )
{
  DATA_OBJECT clipsdo;
  EnvGetDefmoduleList( m_cobj, &clipsdo );
  return data_object_to_strings( clipsdo );
}

Module::pointer Environment::get_module_list_head( )
{
  void* module;
  module = EnvGetNextDefmodule( m_cobj, NULL );
  if (module)
    return Module::create( *this, module );
  else
    return Module::pointer();
}

Values Environment::evaluate( const std::string& expression )
{
  DATA_OBJECT clipsdo;
  int result;
  result = EnvEval( m_cobj, const_cast<char*>(expression.c_str()), &clipsdo );
  if ( result )
    return data_object_to_values( clipsdo );
  else
    return Values();
}

Values Environment::function( const std::string & function_name,
                              const std::string & arguments )
{
  DATA_OBJECT clipsdo;
  int result;
  result = EnvFunctionCall( m_cobj,
                            const_cast<char*>(function_name.c_str()),
                            const_cast<char*>(arguments.c_str()),
                            &clipsdo);
  if ( !result )
    return data_object_to_values( clipsdo );
  else
    return Values();
}

bool Environment::remove_function( std::string name )
{
  bool result = UndefineFunction( m_cobj, const_cast<char*>(name.c_str()) );
  m_slots.erase(name);
  if (m_func_restr.find(name) != m_func_restr.end()) {
    free(m_func_restr[name]);
    m_func_restr.erase(name);
  }
  return result;
}

Global::pointer Environment::get_global( const std::string& global_name ) {
  void* clips_global = EnvFindDefglobal( m_cobj, const_cast<char*>(global_name.c_str()));
  if ( clips_global )
    return Global::create( *this, clips_global );
  else
    return Global::pointer();
}

Global::pointer Environment::get_global_list_head( )
{
  void* global;
  global = EnvGetNextDefglobal( m_cobj, NULL );
  if (global)
    return Global::create( *this, global );
  else
    return Global::pointer();
}

std::vector<std::string> Environment::get_globals_names()
{
  DATA_OBJECT clipsdo;
  EnvGetDefglobalList( m_cobj, &clipsdo, NULL );
  return data_object_to_strings( clipsdo );
}

std::vector<std::string> Environment::get_globals_names( const Module& module )
{
  DATA_OBJECT clipsdo;
  if ( module.cobj() ) {
    EnvGetDefglobalList( m_cobj, &clipsdo, module.cobj() );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

std::vector<std::string> Environment::get_globals_names( Module::pointer module )
{
  DATA_OBJECT clipsdo;
  if ( module && module->cobj() ) {
    EnvGetDefglobalList( m_cobj, &clipsdo, module->cobj() );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

Function::pointer Environment::get_function( const std::string& function_name ) {
  void* clips_function = EnvFindDeffunction( m_cobj, const_cast<char*>(function_name.c_str()));
  if ( clips_function )
    return Function::create( *this, clips_function );
  else
    return Function::pointer();
}

Function::pointer Environment::get_function_list_head( )
{
  void* function;
  function = EnvGetNextDeffunction( m_cobj, NULL );
  if (function)
    return Function::create( *this, function );
  else
    return Function::pointer();
}

std::vector<std::string> Environment::get_function_names()
{
  DATA_OBJECT clipsdo;
  EnvGetDeffunctionList( m_cobj, &clipsdo, NULL );
  return data_object_to_strings( clipsdo );
}

std::vector<std::string> Environment::get_function_names( const Module& module )
{
  DATA_OBJECT clipsdo;
  if ( module.cobj() ) {
    EnvGetDeffunctionList( m_cobj, &clipsdo, (defmodule*)(module.cobj()) );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

std::vector<std::string> Environment::get_function_names( Module::pointer module )
{
  DATA_OBJECT clipsdo;
  if ( module && module->cobj() ) {
    EnvGetDeffunctionList( m_cobj, &clipsdo, (defmodule*)(module->cobj()) );
    return data_object_to_strings( clipsdo );
  }
  else
    return std::vector<std::string>();
}

sigc::signal< void > Environment::signal_clear( )
{
  return m_signal_clear;
}

sigc::signal< void > Environment::signal_periodic( )
{
  return m_signal_periodic;
}

sigc::signal< void > Environment::signal_reset( )
{
  return m_signal_reset;
}

sigc::signal< void > Environment::signal_rule_firing( )
{
  return m_signal_rule_firing;
}

bool Environment::check_agenda_changed() {
  if ( EnvGetAgendaChanged( m_cobj ) ) {
    EnvSetAgendaChanged( m_cobj, 0 );
    m_signal_agenda_changed.emit();
    return true;
  }
  else
    return false;
}

sigc::signal< void > Environment::signal_agenda_changed()
{
  return m_signal_agenda_changed;
}

bool Environment::check_globals_changed() {
  if ( EnvGetGlobalsChanged( m_cobj ) ) {
    EnvSetGlobalsChanged( m_cobj, 0 );
    m_signal_globals_changed.emit();
    return true;
  }
  else
    return false;
}

sigc::signal< void > Environment::signal_globals_changed()
{
  return m_signal_globals_changed;
}

void Environment::clear_callback( void * env )
{
  m_environment_map[env]->m_signal_clear.emit();
}

void Environment::periodic_callback( void * env )
{
  m_environment_map[env]->m_signal_periodic.emit();
}

void Environment::reset_callback( void * env )
{
  m_environment_map[env]->m_signal_reset.emit();
}

void Environment::rule_firing_callback( void * env )
{
  m_environment_map[env]->m_signal_rule_firing.emit();
}

int Environment::get_arg_count( void* env ) {
  return EnvRtnArgCount( env );
}

void* Environment::get_function_context( void* env ) {
  return GetEnvironmentFunctionContext( env );
}

void Environment::set_return_values( void *env, void *rv, const Values &v ) {
  void *mfptr = CreateMultifield(v.size());
  for (unsigned int i = 0; i < v.size(); ++i) {
    unsigned int mfi = i + 1; // mfptr indices start at 1
    switch (v[i].type()) {
    case TYPE_FLOAT:
      SetMFType(mfptr, mfi, FLOAT);
      SetMFValue(mfptr, mfi, EnvAddDouble(env, v[i].as_float()));
      break;
    case TYPE_INTEGER:
      SetMFType(mfptr, mfi, INTEGER);
      SetMFValue(mfptr, mfi, EnvAddLong(env, v[i].as_integer()));
      break;
    case TYPE_SYMBOL:
      SetMFType(mfptr, mfi, SYMBOL);
      SetMFValue(mfptr, mfi,
                 EnvAddSymbol(env, const_cast<char*>(v[i].as_string().c_str())));
      break;
    case TYPE_STRING:
      SetMFType(mfptr, mfi, STRING);
      SetMFValue(mfptr, mfi,
                 EnvAddSymbol(env, const_cast<char*>(v[i].as_string().c_str())));
      break;
    case TYPE_INSTANCE_NAME:
      SetMFType(mfptr, mfi, INSTANCE_NAME);
      SetMFValue(mfptr, mfi,
                 EnvAddSymbol(env, const_cast<char*>(v[i].as_string().c_str())));
      break;
    case TYPE_EXTERNAL_ADDRESS:
      SetMFType(mfptr, mfi, EXTERNAL_ADDRESS);
      SetMFValue(mfptr, mfi,
		 EnvAddExternalAddress(env, v[i].as_address(), EXTERNAL_ADDRESS));
      break;
    default:
      throw std::logic_error("clipsmm: value type not supported for multifield return value");
    }
  }

  DATA_OBJECT_PTR rvptr = static_cast<DATA_OBJECT_PTR>(rv);

  SetpType(rvptr, MULTIFIELD);
  SetpValue(rvptr, mfptr);

  SetpDOBegin(rvptr, 1);
  SetpDOEnd(rvptr, v.size());
}

void Environment::set_return_value( void *env, void *rv, const Value &v)
{
  value_to_data_object_rawenv(env, v, (struct dataObject *)rv);
}

void* Environment::add_symbol( const char* s ) {
  return AddSymbol( const_cast<char*>(s) );
}

}

