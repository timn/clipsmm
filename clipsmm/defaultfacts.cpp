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

