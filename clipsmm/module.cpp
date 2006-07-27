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
#include "module.h"

extern "C" {
  #include <clips/clips.h>
};

#include <clipsmm/environment.h>

namespace CLIPS {

Module::Module( Environment& environment, void* cobj ):
    EnvironmentObject( environment, cobj )
{
}

Module::pointer Module::create( Environment & environment, void * cobj )
{
  return Module::pointer( new Module( environment, cobj ) );
}

Module::~Module()
{
}

std::string Module::name( )
{
  if ( m_cobj )
    return EnvGetDefmoduleName( m_environment.cobj(), m_cobj );
  else
    return std::string();
}

std::string Module::formatted( )
{
  if ( m_cobj )
    return EnvGetDefmodulePPForm( m_environment.cobj(), m_cobj );
  else
    return std::string();
}

Module::pointer Module::next( )
{
  void* nxt;
  if ( !m_cobj )
    return Module::pointer();
  nxt = EnvGetNextDefmodule( m_environment.cobj(), m_cobj );
  if ( nxt )
    return Module::create( m_environment, nxt );
  else
    return Module::pointer();
}

Module::pointer Module::set_current( )
{
  void* old;
  if ( !m_cobj )
    return Module::pointer();
  old = EnvSetCurrentModule( m_environment.cobj(), m_cobj );
  if ( old )
    return Module::create( m_environment, old );
  else
    return Module::pointer();
}

void Module::focus( )
{
  if ( m_cobj )
    EnvFocus( m_environment.cobj(), m_cobj );
}

}

