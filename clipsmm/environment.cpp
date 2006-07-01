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
#include "environment.h"

#include <stdexcept>

#include <clips/clips.h>

namespace CLIPS {

std::map<void*, Environment*> Environment::m_environment_map;

Environment::Environment()
{
  m_cobj = CreateEnvironment();

  m_environment_map[m_cobj] = this;

  if ( EnvAddClearFunction( m_cobj, "clipsmm_clear_callback", Environment::clear_callback, 2001 ) == 0 )
    throw std::logic_error("clipsmm: Error adding clear callback to clips environment");
  if ( EnvAddPeriodicFunction( m_cobj, "clipsmm_periodic_callback", Environment::periodic_callback, 2001 ) == 0 )
    throw std::logic_error("clipsmm: Error adding periodic callback to clips environment");
  if ( EnvAddResetFunction( m_cobj, "clipsmm_reset_callback", Environment::reset_callback, 2001 ) == 0 )
    throw std::logic_error("clipsmm: Error adding reset callback to clips environment");
}

Environment::~Environment()
{
  EnvRemoveClearFunction( m_cobj, "clipsmm_clear_callback" );
  EnvRemovePeriodicFunction( m_cobj, "clipsmm_periodic_callback" );
  EnvRemoveResetFunction( m_cobj, "clipsmm_reset_callback" );
  
  m_environment_map.erase(m_cobj);
  
  DestroyEnvironment( m_cobj );
}

void* Environment::cobj()
{
  return m_cobj;
}

bool Environment::batch_evaluate( std::string filename ) {
  return EnvBatchStar( m_cobj, const_cast<char*>( filename.c_str() ) );
}

bool Environment::binary_load( std::string filename ) {
  return EnvBload( m_cobj, const_cast<char*>( filename.c_str() ) );
}

bool Environment::binary_save( std::string filename ) {
  return EnvBsave( m_cobj, const_cast<char*>( filename.c_str() ) );
}

bool Environment::build( std::string construct ) {
  return EnvBuild( m_cobj, const_cast<char*>( construct.c_str() ) );
}

void Environment::clear( ) {
  EnvClear( m_cobj );
}

int Environment::load( std::string filename )
{
  return EnvLoad( m_cobj, const_cast<char*>( filename.c_str() ) );
}

void Environment::reset( )
{
  EnvReset( m_cobj );
}

bool Environment::save( std::string filename )
{
  return EnvSave( m_cobj, const_cast<char*>( filename.c_str() ) );
}

bool Environment::is_dribble_active( ) {
  return EnvDribbleActive( m_cobj );
}

bool Environment::dribble_off( ) {
  return EnvDribbleOff( m_cobj );
}

bool Environment::dribble_on( std::string filename )
{
  return EnvDribbleOn( m_cobj, const_cast<char*>( filename.c_str() ) );
}

int Environment::is_watched( std::string item ) {
  return EnvGetWatchItem( m_cobj, const_cast<char*>( item.c_str() ) );
}

bool Environment::watch( std::string item )
{
  return EnvWatch( m_cobj, const_cast<char*>( item.c_str() ) );
}

bool Environment::unwatch( std::string item )
{
  return EnvUnwatch( m_cobj, const_cast<char*>( item.c_str() ) );
}

long int Environment::run( long int runlimit )
{
  return EnvRun( m_cobj, runlimit );
}

void Environment::set_as_current( )
{
  SetCurrentEnvironment( m_cobj );
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

Fact::pointer Environment::assert( std::string factstring )
{
  void* clips_fact = EnvAssertString( m_cobj, const_cast<char*>(factstring.c_str()) );
  if ( clips_fact != NULL )
    return Fact::create( *this, clips_fact );
  else
    return Fact::pointer();
}

}

