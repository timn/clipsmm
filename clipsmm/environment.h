/***************************************************************************
*   clipsmm C++ wrapper for the CLIPS c library                           *
*   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            *
*   rvinyard@cs.nmsu.edu                                                  *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of version 2 of the GNU General Public License as  *
*   published by the Free Software Foundation.                            *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU Lesser General Public      *
*   License along with this library; if not, write to the                 *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
***************************************************************************/
#ifndef CLIPSENVIRONMENT_H
#define CLIPSENVIRONMENT_H

#include <string>
#include <map>
#include <typeinfo>
#include <stdexcept>
#include <map>

#include <iostream>

#include <sigc++/sigc++.h>

#include <clipsmm/enum.h>
#include <clipsmm/object.h>
#include <clipsmm/fact.h>
#include <clipsmm/activation.h>
#include <clipsmm/defaultfacts.h>
#include <clipsmm/template.h>
#include <clipsmm/rule.h>
#include <clipsmm/module.h>
#include <clipsmm/utility.h>
#include <clipsmm/any.h>

extern "C" {
  int EnvDefineFunction5( void *, char *, int, int ( * ) ( void * ), char *, char *, void * );
}

namespace CLIPS {

  /**
   * @author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
   */
  class Environment: public Object {
    public:
      typedef std::tr1::shared_ptr<Environment> pointer;

      Environment();

      ~Environment();

      /**
       * Evaluates a series of commands in the specified file
       * @return false if an error occurred, true otherwise
       */
      bool batch_evaluate( const std::string& filename );

      /**
       * Loads a binary image of constructs into the CLIPS data base
       * @return false if an error occurred, true otherwise
       */
      bool binary_load( const std::string& filename );

      /**
       * Saves a binary image of constructs from the CLIPS data base
       * @return false if an error occurred, true on success
       */
      bool binary_save( const std::string& filename );

      /**
       * Allows a construct to be defined
       * @return false if the construct could not be parsed, true on success
       */
      bool build( const std::string& construct );

      /**
       * Clears the environment
       */
      void clear( );

      /**
       * Evaluates and expression and returns a vector of the results.
       * If the expression could not be evaluated a zero-length vector
       * is returned.
       */
      Values evaluate( const std::string& expression );

      /**
       * Evaluates a CLIPS function.
       * If the function could not be evaluated a zero-length vector
       * is returned.
       */
      Values function( const std::string& function_name, const std::string& arguments=std::string() );

      /**
       * Loads a set of constructs into the CLIPS data base
       * @return Zero if the file couldn’t be opened, -1 if the file
       *         was opened but an error occurred while loading, and 1
       *         if the file was opened and no errors occurred while
       *         loading.
       *
       * If syntactic errors are in the constructs, load still will
       * attempt to read the entire file and error notices will be sent
       * to werror.
       */
      int load( const std::string& filename );

      /**
       * Resets the CLIPS environment
       */
      void reset();

      /**
       * Saves a set of constructs to the specified file
       * @return false if an error occurred, true on success
       */
      bool save( const std::string& filename );

      /**
       * Returns the current state of the auto-float dividend behavior.
       * When enabled, the dividend of the division function is automatically converted
       * to a floating point number.
       * @return true if enabled, false if disabled
       */
      bool auto_float_dividend_enabled();

      /**
       * Sets the auto-float dividend behavior.
       * When enabled, the dividend of the division function is automatically converted
       * to a floating point number.
       * Default is enabled.
       * @return the new value for the behavior; true if enabled, false if disabled
       */
      bool use_auto_float_dividend( bool use = true );

      /**
       * Returns the current state of the dynamic constraint checking behavior.
       * When enabled, slot values for newly created data objects are checked for
       * constraint violations.
       * @return true if enabled, false if disabled
       */
      bool dynamic_constraint_checking_enabled();

      /**
       * Sets the dynamic constraint checking behavior.
       * When enabled, slot values for newly created data objects are checked for
       * constraint violations.
       * Default is disabled.
       * @return the new value for the behavior; true if enabled, false if disabled
       */
      bool use_dynamic_constraint_checking( bool use = true );

      /**
       * Returns the current state of the sequence operator recognition behavior.
       * When enabled, multifield variables are expanded and passed as separate arguments
       * in the function call.
       * @return true if enabled, false if disabled
       */
      bool sequence_operator_recognition_enabled();

      /**
       * Sets the sequence operator recognition behavior.
       * When enabled, multifield variables are expanded and passed as separate arguments
       * in the function call.
       * Default is disabled.
       * @return the new value for the behavior; true if enabled, false if disabled
       */
      bool use_sequence_operator_recognition( bool use = true );

      /**
       * Returns the current state of the static constraint checking behavior.
       * When enabled, constraint violations are checked when function calls and constructs
       * are parsed.
       * @return true if enabled, false if disabled
       */
      bool static_constraint_checking_enabled();

      /**
       * Sets the static constraint checking behavior.
       * When enabled, constraint violations are checked when function calls and constructs
       * are parsed.
       * @return the new value for the behavior; true if enabled, false if disabled
       */
      bool use_static_constraint_checking( bool use = true );

      /**
       * Returns the current state of the fact duplication behavior.
       * When disabled, asserting a duplicate of a fact in the fact-list will result in no effect.
       * When enabled, a duplicate fact is asserted with a new fact-index.
       * Default is disabled.
       * @return true if enabled, false if disabled
       */
      bool fact_duplication_enabled();

      /**
       * Sets the static constraint checking behavior.
       * When enabled, constraint violations are checked when function calls and constructs
       * are parsed.
       * @return the new value for the behavior; true if enabled, false if disabled
       */
      bool use_fact_duplication( bool use = true );

      bool incremental_reset_enabled();

      bool use_incremental_reset( bool use = true );

      /**
       * Determines if the storing of dribble information is active.
       * @return true if dribbling is active, false if it is inactive
       */
      bool is_dribble_active( );

      /**
       * Turns off the storing of dribble information
       * @return false if an error occurred closing the file; true on success.
       */
      bool dribble_off( );

      /**
       * Allows the dribble function of CLIPS to be turned on
       * @return false if an error occurred opening the file; true on success.
       */
      bool dribble_on( const std::string& dribble_file );

      /**
       * Determine if an item is being watched
       * @param item must be one of the following strings: facts, rules, activations, focus,
       *             compilations, statistics, globals, instances, slots, messages,
       *             message-handlers, generic-functions, method, or deffunctions.
       * @return 1 if the item is watched, 0 if the item is not watched, -1 if the item doesn't exist
       */
      int is_watched( const std::string& item );

      bool watch( const std::string& item );

      bool unwatch( const std::string& item );

      void set_as_current();

      Fact::pointer assert( const std::string& factstring );

      void clear_focus_stack();

      /** TODO Facts */

      DefaultFacts::pointer get_default_facts( const std::string& default_facts_name );

      /** Gets a list of default facts names from all modules */
      std::vector<std::string> get_default_facts_names();

      /** Gets a list of default facts names from a specific module */
      std::vector<std::string> get_default_facts_names( const Module& module );

      /** Gets a list of default facts names from a specific module */
      std::vector<std::string> get_default_facts_names( Module::pointer module );

      DefaultFacts::pointer get_default_facts_list_head();

      Template::pointer get_template( const std::string& template_name );

      /** Gets a list of template names from all modules */
      std::vector<std::string> get_template_names();

      /** Gets a list of template names from a specific module */
      std::vector<std::string> get_template_names( const Module& module );

      /** Gets a list of template names from a specific module */
      std::vector<std::string> get_template_names( Module::pointer module );

      Template::pointer get_template_list_head();

      Rule::pointer get_rule( const std::string& rule_name );

      /** Gets a list of rule names from all modules */
      std::vector<std::string> get_rule_names();

      /** Gets a list of rule names from a specific module */
      std::vector<std::string> get_rule_names( const Module& module );

      /** Gets a list of rule names from a specific module */
      std::vector<std::string> get_rule_names( Module::pointer module );

      Rule::pointer get_rule_list_head();

      void remove_rules();

      Module::pointer get_module( const std::string& module_name );

      Module::pointer get_current_module();

      std::vector<std::string> get_module_names();

      Module::pointer get_module_list_head();

      /**
       * Refreshes the agenda for all modules.
       * Recomputes the salience values for all activations on the agenda
       * and then reorders the agenda.
       */
      void refresh_agenda();

      /**
       * Refreshes the agenda for a specific module.
       * Recomputes the salience values for all activations on the agenda
       * and then reorders the agenda.
       */
      void refresh_agenda( const Module& module );

      /**
       * Refreshes the agenda for a specific module.
       * Recomputes the salience values for all activations on the agenda
       * and then reorders the agenda.
       */
      void refresh_agenda( Module::pointer module );

      /**
       * Reorders the agenda for all modules.
       * Reorders the agenda based on the current conflict resolution
       * strategy and current activation saliences.
       */
      void reorder_agenda();

      /**
       * Reorders the agenda for a specific module.
       * Reorders the agenda based on the current conflict resolution
       * strategy and current activation saliences.
       */
      void reorder_agenda( const Module& module );

      /**
       * Reorders the agenda for a specific module.
       * Reorders the agenda based on the current conflict resolution
       * strategy and current activation saliences.
       */
      void reorder_agenda( Module::pointer module );

      /**
       * Allows rules to execute
       * @return The number of rules that fired
       * @param runlimit How many rules should file
       * If runlimit is negative, rules will fire until the agenda is empty
       */
      long int run( long int runlimit = -1 );

      /** Gets the salience evaluation mode */
      SalienceEvaluation get_salience_evaluation();

      /**
       * Sets the salience evaluation mode.
       * @return the old salience evaluation mode
       */
      SalienceEvaluation set_salience_evaluation( SalienceEvaluation se );

      /** Gets the current conflict resolution strategy */
      ConflictResolution get_conflict_resolution_strategy();

      /**
       * Sets the conflict resolution strategy.
       * @return the old conflict resolution strategy
       */
      ConflictResolution set_conflict_resolution_strategy( ConflictResolution cr );

      /** TODO ListDefmodules */

      /**
       * Checks whether the agenda has changed and emits the agenda changed signal if it has.
       * The agenda does not include any callbacks when the agenda is changed.
       * This method returns true if the agenda has changed and emits the
       * agenda changed signal.
       */
      bool check_agenda_changed();

      Module::pointer get_focused_module();

      std::vector<std::string> get_focus_stack();

      Activation::pointer get_activation_list_head();

      sigc::signal<void> signal_clear();
      sigc::signal<void> signal_periodic();
      sigc::signal<void> signal_reset();
      sigc::signal<void> signal_rule_firing();
      sigc::signal<void> signal_agenda_changed();

      template < typename T_return >
      bool add_function( std::string name, const sigc::slot0<T_return>& slot);

      template < typename T_return, typename T_arg1 >
      bool add_function( std::string name, const sigc::slot1<T_return, T_arg1>& slot);

      template < typename T_arg1, typename T_arg2 >
      bool add_function( std::string name, const sigc::slot2<std::string, T_arg1, T_arg2>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2 >
      bool add_function( std::string name, const sigc::slot2<T_return, T_arg1, T_arg2>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
      bool add_function( std::string name, const sigc::slot3<T_return, T_arg1, T_arg2, T_arg3>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
      bool add_function( std::string name, const sigc::slot4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
      bool add_function( std::string name, const sigc::slot5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
      bool add_function( std::string name, const sigc::slot6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
      bool add_function( std::string name, const sigc::slot7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>& slot);

      bool remove_function( std::string name );

    protected:
      /**
       * Holds any dynamically created slots.
       * Type any is used to hold different smart pointers, each of which hold different
       * slots. When a slot is undefined, or at destruction when the map goes out of scope,
       * the memory is reclaimed through the smart pointer.
       */
      std::map<std::string,any> m_slots;

      sigc::signal<void> m_signal_clear;
      sigc::signal<void> m_signal_periodic;
      sigc::signal<void> m_signal_reset;
      sigc::signal<void> m_signal_rule_firing;
      sigc::signal<void> m_signal_agenda_changed;

      static std::map<void*, Environment*> m_environment_map;

      static void clear_callback( void* env );
      static void periodic_callback( void* env );
      static void reset_callback( void* env );
      static void rule_firing_callback( void* end );

      template < typename T_return >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2 >
      static T_return callback( void* theEnv );

      template < typename T_arg1, typename T_arg2 >
      static void* strcallback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
      static T_return callback( void* theEnv );

      static int get_arg_count( void* env );
      static void* get_user_data( void* env );
      static void* add_symbol( const char* s );
  };

  template < typename T_return>
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot0<T_return>* cb;
    void * cbptr = get_user_data( theEnv );
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 0 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 0" );
      cb = static_cast<sigc::slot0<T_return>*>( cbptr );
      return ( *cb ) ();
    }
    throw;
  }

  template < typename T_return, typename T_arg1 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot1<T_return,T_arg1>* cb;
    void * cbptr = get_user_data( theEnv );
    T_arg1 arg1;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 1 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 1" );
      get_argument( theEnv, 1, arg1 );
      cb = static_cast<sigc::slot1<T_return,T_arg1>*>( cbptr );
      return ( *cb ) ( arg1 );
    }
    throw;
  }

  template < typename T_return, typename T_arg1, typename T_arg2 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot2<T_return, T_arg1, T_arg2>* cb;
    void * cbptr = get_user_data( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 2 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 2" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      cb = static_cast<sigc::slot2<T_return, T_arg1, T_arg2>*>( cbptr );
      return ( *cb ) ( arg1, arg2 );
    }
    throw;
  }

  template < typename T_arg1, typename T_arg2 >
  inline
  void* Environment::strcallback( void* theEnv ) {
    sigc::slot2<std::string, T_arg1, T_arg2>* cb;
    void * cbptr = get_user_data( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    std::string s;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 2 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 2" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      cb = static_cast<sigc::slot2<std::string, T_arg1, T_arg2>*>( cbptr );
      s = ( *cb ) ( arg1, arg2 );
      return add_symbol( s.c_str() );
    }
    throw;
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot3<T_return,T_arg1,T_arg2,T_arg3>* cb;
    void * cbptr = get_user_data( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 3 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 3" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      cb = static_cast<sigc::slot3<T_return, T_arg1, T_arg2,T_arg3>*>( cbptr );
      return ( *cb ) ( arg1, arg2, arg3 );
    }
    throw;
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4>* cb;
    void * cbptr = get_user_data( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 4 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 4" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      cb = static_cast<sigc::slot4<T_return, T_arg1, T_arg2,T_arg3,T_arg4>*>( cbptr );
      return ( *cb ) ( arg1, arg2, arg3, arg4 );
    }
    throw;
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>* cb;
    void * cbptr = get_user_data( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 5 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 5" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      get_argument( theEnv, 5, arg5 );
      cb = static_cast<sigc::slot5<T_return, T_arg1, T_arg2,T_arg3,T_arg4,T_arg5>*>( cbptr );
      return ( *cb ) ( arg1, arg2, arg3, arg4, arg5 );
    }
    throw;
  }

 template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
 inline
 T_return Environment::callback( void* theEnv ) {
   sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>* cb;
   void * cbptr = get_user_data( theEnv );
   T_arg1 arg1;
   T_arg2 arg2;
   T_arg3 arg3;
   T_arg4 arg4;
   T_arg5 arg5;
   T_arg6 arg6;
   if ( cbptr ) {
     if ( get_arg_count( theEnv ) != 6 )
       throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 6" );
     get_argument( theEnv, 1, arg1 );
     get_argument( theEnv, 2, arg2 );
     get_argument( theEnv, 3, arg3 );
     get_argument( theEnv, 4, arg4 );
     get_argument( theEnv, 5, arg5 );
     get_argument( theEnv, 6, arg6 );
     cb = static_cast<sigc::slot6<T_return, T_arg1, T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>*>( cbptr );
     return ( *cb ) ( arg1, arg2, arg3, arg4, arg5, arg6 );
   }
   throw;
 }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>* cb;
    void * cbptr = get_user_data( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    T_arg6 arg6;
    T_arg7 arg7;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 7 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 7" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      get_argument( theEnv, 5, arg5 );
      get_argument( theEnv, 6, arg6 );
      get_argument( theEnv, 7, arg7 );
      cb = static_cast<sigc::slot7<T_return, T_arg1, T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>*>( cbptr );
      return ( *cb ) ( arg1, arg2, arg3, arg4, arg5, arg6, arg7 );
    }
    throw;
  }

  template < typename T_return >
  inline
  bool Environment::add_function( std::string name, const sigc::slot0<T_return>& slot) {
    char retcode = get_return_code<T_return>( );
    char argstring[ 10 ] = { '0', '0', 'u', 0x00 };
    sigc::slot0<T_return>* scb = new sigc::slot0<T_return>(slot);
    any holder = std::tr1::shared_ptr<sigc::slot0<T_return> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction5( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return>,
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 ( void* ) scb ) );
  }

  template < typename T_return, typename T_arg1 >
  inline
  bool Environment::add_function( std::string name, const sigc::slot1<T_return, T_arg1>& slot) {
    char retcode = get_return_code<T_return>( );
    char argstring[ 10 ] = { '1', '1', 'u', 0x00 };
    argstring[ 3 ] = get_argument_code<T_arg1>( );
    sigc::slot1<T_return, T_arg1>* scb = new sigc::slot1<T_return, T_arg1>(slot);
    any holder = std::tr1::shared_ptr<sigc::slot1<T_return, T_arg1> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction5( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return, T_arg1>,
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb ) );
  }

  template < typename T_return, typename T_arg1, typename T_arg2 >
  inline
  bool Environment::add_function( std::string name, const sigc::slot2<T_return, T_arg1, T_arg2>& slot) {
    char retcode = get_return_code<T_return>( );
    char argstring[ 10 ] = { '2', '2', 'u', 0x00 };
    argstring[ 3 ] = get_argument_code<T_arg1>( );
    argstring[ 4 ] = get_argument_code<T_arg2>( );
    sigc::slot2<T_return, T_arg1, T_arg2>* scb = new sigc::slot2<T_return, T_arg1, T_arg2>(slot);
    any holder = std::tr1::shared_ptr<sigc::slot2<T_return, T_arg1, T_arg2> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction5( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return, T_arg1, T_arg2>,
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb ) );
  }

  template < typename T_arg1, typename T_arg2 >
      inline
          bool Environment::add_function( std::string name, const sigc::slot2<std::string, T_arg1, T_arg2>& slot) {
        char retcode = get_return_code<std::string>( );
        char argstring[ 10 ] = { '2', '2', 'u', 0x00 };
        argstring[ 3 ] = get_argument_code<T_arg1>( );
        argstring[ 4 ] = get_argument_code<T_arg2>( );
        sigc::slot2<std::string, T_arg1, T_arg2>* scb = new sigc::slot2<std::string, T_arg1, T_arg2>(slot);
        any holder = std::tr1::shared_ptr<sigc::slot2<std::string, T_arg1, T_arg2> >(scb);
        m_slots[name] = holder;
        return ( EnvDefineFunction5( m_cobj,
                 const_cast<char*>( name.c_str() ),
                 retcode,
                 ( int ( * ) ( void* ) ) ( void* ( * ) ( void* ) ) strcallback<T_arg1, T_arg2>,
                 const_cast<char*>( name.c_str() ),
                 argstring,
                 scb ) );
          }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
  inline
  bool Environment::add_function( std::string name, const sigc::slot3<T_return,T_arg1,T_arg2,T_arg3>& slot) {
    char retcode = get_return_code<T_return>( );
    char argstring[ 10 ] = { '3', '3', 'u', 0x00 };
    argstring[ 3 ] = get_argument_code<T_arg1>( );
    argstring[ 4 ] = get_argument_code<T_arg2>( );
    argstring[ 5 ] = get_argument_code<T_arg3>( );
    sigc::slot3<T_return,T_arg1,T_arg2,T_arg3>* scb =
        new sigc::slot3<T_return,T_arg1,T_arg2,T_arg3>(slot);
    any holder = std::tr1::shared_ptr<sigc::slot3<T_return,T_arg1,T_arg2,T_arg3> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction5( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return,T_arg1,T_arg2,T_arg3>,
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
  inline
  bool Environment::add_function( std::string name, const sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4>& slot) {
    char retcode = get_return_code<T_return>( );
    char argstring[ 10 ] = { '4', '4', 'u', 0x00 };
    argstring[ 3 ] = get_argument_code<T_arg1>( );
    argstring[ 4 ] = get_argument_code<T_arg2>( );
    argstring[ 5 ] = get_argument_code<T_arg3>( );
    argstring[ 6 ] = get_argument_code<T_arg4>( );
    sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4>* scb =
        new sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4>(slot);
    any holder = std::tr1::shared_ptr<sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction5( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return,T_arg1,T_arg2,T_arg3,T_arg4>,
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
  inline
  bool Environment::add_function( std::string name,
                              const sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>& slot) {
    char retcode = get_return_code<T_return>( );
    char argstring[ 10 ] = { '5', '5', 'u', 0x00 };
    argstring[ 3 ] = get_argument_code<T_arg1>( );
    argstring[ 4 ] = get_argument_code<T_arg2>( );
    argstring[ 5 ] = get_argument_code<T_arg3>( );
    argstring[ 6 ] = get_argument_code<T_arg4>( );
    argstring[ 7 ] = get_argument_code<T_arg5>( );
    sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>* scb =
        new sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>(slot);
    any holder = std::tr1::shared_ptr<sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction5( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>,
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
  inline
  bool Environment::add_function( std::string name,
                              const sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>& slot) {
    char retcode = get_return_code<T_return>( );
    char argstring[ 10 ] = { '6', '6', 'u', 0x00 };
    argstring[ 3 ] = get_argument_code<T_arg1>( );
    argstring[ 4 ] = get_argument_code<T_arg2>( );
    argstring[ 5 ] = get_argument_code<T_arg3>( );
    argstring[ 6 ] = get_argument_code<T_arg4>( );
    argstring[ 7 ] = get_argument_code<T_arg5>( );
    argstring[ 8 ] = get_argument_code<T_arg6>( );
    sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>* scb =
        new sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>(slot);
    any holder = std::tr1::shared_ptr<sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction5( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>,
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
  inline
  bool Environment::add_function( std::string name,
                                  const sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>& slot) {
    char retcode = get_return_code<T_return>( );
    char argstring[ 10 ] = { '7', '7', 'u', 0x00 };
    argstring[ 3 ] = get_argument_code<T_arg1>( );
    argstring[ 4 ] = get_argument_code<T_arg2>( );
    argstring[ 5 ] = get_argument_code<T_arg3>( );
    argstring[ 6 ] = get_argument_code<T_arg4>( );
    argstring[ 7 ] = get_argument_code<T_arg5>( );
    argstring[ 8 ] = get_argument_code<T_arg6>( );
    argstring[ 9 ] = get_argument_code<T_arg7>( );
    sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>* scb =
        new sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>(slot);
    any holder = std::tr1::shared_ptr<sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction5( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>,
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }


}

#endif
