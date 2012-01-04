/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            *
 *   rvinyard@cs.nmsu.edu                                                  *
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
#include "global.h"

extern "C" {
  #include <clips/clips.h>
};

#include <clipsmm/environment.h>

namespace CLIPS {

Global::Global( Environment& environment, void* cobj ) :
    EnvironmentObject( environment, cobj ) {}

Global::pointer Global::create( Environment & environment, void * cobj ) {
  return Global::pointer( new Global( environment, cobj ) );
  }

Global::~Global()
{
}

std::string Global::name( )
{
  if ( m_cobj )
    return EnvGetDefglobalName( m_environment.cobj(), m_cobj );
  else
    return std::string();
}

std::string Global::formatted( )
{
  if ( m_cobj )
    return EnvGetDefglobalPPForm( m_environment.cobj(), m_cobj );
  else
    return std::string();
}

std::string Global::module_name() {
  if ( m_cobj )
    return EnvDefglobalModule( m_environment.cobj(), m_cobj );
  else
    return std::string();
}

Values Global::value() {
  DATA_OBJECT clips_do;
  if ( m_cobj ) {
    QGetDefglobalValue( m_environment.cobj(), m_cobj, &clips_do );
    return data_object_to_values( clips_do );
  }
  else
    return Values();
}

void Global::set_value( const Values& value ) {
  DATA_OBJECT* clips_do;
  if ( m_cobj ) {
    clips_do = value_to_data_object( m_environment, value );
    QSetDefglobalValue( m_environment.cobj(), (defglobal*)m_cobj, clips_do, false );
    delete clips_do;
  }
}

void Global::set_value( const Value& value ) {
  DATA_OBJECT* clips_do;
  if ( m_cobj ) {
    clips_do = value_to_data_object( m_environment, value );
    QSetDefglobalValue( m_environment.cobj(), (defglobal*)m_cobj, clips_do, false );
    delete clips_do;
  }
}

void Global::reset_value() {
  if ( m_cobj )
    QSetDefglobalValue( m_environment.cobj(), (defglobal*)m_cobj, NULL, true );
}

bool Global::is_watched() {
  if ( m_cobj )
    return EnvGetDefglobalWatch( m_environment.cobj(), m_cobj );
  else
    return false;
}

void Global::set_watch( bool watch ) {
  if ( m_cobj )
    EnvSetDefglobalWatch( m_environment.cobj(), watch, m_cobj );
}

Global::pointer Global::next() {
  void* nxt;
  if ( m_cobj ) {
    nxt = EnvGetNextDefglobal( m_environment.cobj(), m_cobj );
    if ( nxt )
      return Global::create( m_environment, nxt );
  }
  return Global::pointer();
}

bool Global::is_deletable() {
  if ( m_cobj )
    return EnvIsDefglobalDeletable( m_environment.cobj(), m_cobj );
  return false;
}

bool Global::undefine() {
  if ( m_cobj )
    return EnvUndefglobal( m_environment.cobj(), m_cobj );
  return false;
}

}
