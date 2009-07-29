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
#include "rule.h"

extern "C" {
  #include <clips/clips.h>
};

#include <clipsmm/environment.h>

namespace CLIPS {

Rule::Rule( Environment& environment, void* cobj ):
    EnvironmentObject( environment, cobj )
{
}

Rule::pointer Rule::create( Environment & environment, void * cobj )
{
  return Rule::pointer( new Rule( environment, cobj ) );
}

Rule::~Rule()
{
}

bool Rule::is_breakpoint_set( )
{
  if (!m_cobj)
    return false;
  return EnvDefruleHasBreakpoint( m_environment.cobj(), m_cobj );
}

std::string Rule::module_name( )
{
  if ( !m_cobj )
    return std::string();
  return EnvDefruleModule( m_environment.cobj(), m_cobj );
}

std::string Rule::name( )
{
  if ( !m_cobj )
    return std::string();
  return EnvGetDefruleName( m_environment.cobj(), m_cobj );
}

std::string Rule::formatted( ) {
  if ( !m_cobj )
    return std::string();
  return EnvGetDefrulePPForm( m_environment.cobj(), m_cobj );
}

bool Rule::activations_watched( )
{
  if ( !m_cobj )
    return false;
  return EnvGetDefruleWatchActivations( m_environment.cobj(), m_cobj );
}

bool Rule::firings_watched( )
{
  if ( !m_cobj )
    return false;
  return EnvGetDefruleWatchFirings( m_environment.cobj(), m_cobj );
}

Rule::pointer Rule::next( )
{
  void* nxt;

  if ( !m_cobj )
    return Rule::pointer();

  nxt = EnvGetNextDefrule( m_environment.cobj(), m_cobj );
  if ( nxt )
    return Rule::create( m_environment, nxt );
  else
    return Rule::pointer();
}

bool Rule::is_deletable( )
{
  if ( !m_cobj )
    return false;
  return EnvIsDefruleDeletable( m_environment.cobj(), m_cobj );
}

void Rule::refresh( )
{
  if ( m_cobj )
    EnvRefresh( m_environment.cobj(), m_cobj );
}

bool Rule::remove_break( )
{
  if ( !m_cobj )
    return false;
  return EnvRemoveBreak( m_environment.cobj(), m_cobj );
}

void Rule::set_break( )
{
  if ( m_cobj )
    EnvSetBreak( m_environment.cobj(), m_cobj );
}

void Rule::set_watch_activations( bool set )
{
  if ( m_cobj )
    EnvSetDefruleWatchActivations( m_environment.cobj(), set, m_cobj );
}

void Rule::set_watch_firings( bool set )
{
  if ( m_cobj )
    EnvSetDefruleWatchFirings( m_environment.cobj(), set, m_cobj );
}

bool Rule::retract( )
{
  if ( m_cobj )
    return EnvUndefrule( m_environment.cobj(), m_cobj );
  else
    return false;
}

}

