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
#include "function.h"

#include <clips.h>
#include <clipsmm/environment.h>

namespace CLIPS {

Function::Function( Environment& environment, void* cobj ) :
    EnvironmentObject( environment, cobj ) {}

Function::pointer Function::create( Environment & environment, void * cobj ) {
  return Function::pointer( new Function( environment, cobj ) );
  }

Function::~Function()
{
}

std::string Function::name( )
{
  if ( m_cobj )
    return EnvGetDeffunctionName( m_environment.cobj(), m_cobj );
  else
    return std::string();
}

std::string Function::formatted( )
{
  if ( m_cobj )
    return EnvGetDeffunctionPPForm( m_environment.cobj(), m_cobj );
  else
    return std::string();
}

std::string Function::module_name() {
  if ( m_cobj )
    return EnvDeffunctionModule( m_environment.cobj(), m_cobj );
  else
    return std::string();
}

bool Function::is_watched() {
  if ( m_cobj )
    return EnvGetDeffunctionWatch( m_environment.cobj(), m_cobj );
  else
    return false;
}

void Function::set_watch( bool watch ) {
  if ( m_cobj )
    EnvSetDeffunctionWatch( m_environment.cobj(), watch, m_cobj );
}

Function::pointer Function::next() {
  void* nxt;
  if ( m_cobj ) {
    nxt = EnvGetNextDeffunction( m_environment.cobj(), m_cobj );
    if ( nxt )
      return Function::create( m_environment, nxt );
  }
  return Function::pointer();
}

bool Function::is_deletable() {
  if ( m_cobj )
    return EnvIsDeffunctionDeletable( m_environment.cobj(), m_cobj );
  return false;
}

bool Function::undefine() {
  if ( m_cobj )
    return EnvUndeffunction( m_environment.cobj(), m_cobj );
  return false;
}

}
