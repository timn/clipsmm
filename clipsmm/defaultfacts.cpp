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
#include "defaultfacts.h"

extern "C" {
  #include <clips/clips.h>
};

#include <clipsmm/environment.h>

namespace CLIPS {

  DefaultFacts::DefaultFacts( Environment& environment, void* cobj ) :
  EnvironmentObject( environment, cobj ) {}

  DefaultFacts::pointer DefaultFacts::create( Environment & environment, void * cobj ) {
    return DefaultFacts::pointer( new DefaultFacts( environment, cobj ) );
  }

  DefaultFacts::~DefaultFacts() {}

  std::string DefaultFacts::name( ) {
    if ( m_cobj )
      return EnvGetDeffactsName( m_environment.cobj(), m_cobj );
    else
      return std::string();
  }

  std::string DefaultFacts::module_name( ) {
    if ( m_cobj )
      return EnvDeffactsModule( m_environment.cobj(), m_cobj );
    else
      return std::string();
  }

  std::string DefaultFacts::formatted( ) {
    if ( m_cobj )
      return EnvGetDeffactsPPForm( m_environment.cobj(), m_cobj );
    else
      return std::string();
  }

  DefaultFacts::pointer DefaultFacts::next( ) {
    void * nxt;

    if ( !m_cobj )
      return DefaultFacts::pointer();

    nxt = EnvGetNextDeffacts( m_environment.cobj(), m_cobj );

    if ( nxt )
      return DefaultFacts::create( m_environment, nxt );
    else
      return DefaultFacts::pointer();
  }

  bool DefaultFacts::is_deletable( ) {
    if ( m_cobj )
      return EnvIsDeffactsDeletable( m_environment.cobj(), m_cobj );
    else
      return false;
  }

  bool DefaultFacts::retract( ) {
    if ( m_cobj )
      return EnvUndeffacts( m_environment.cobj(), m_cobj );
    else
      return false;
  }

}

