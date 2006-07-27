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
#include "activation.h"

extern "C" {
  #include <clips/clips.h>
};

#include <clipsmm/environment.h>

#include <limits.h>

namespace CLIPS {

  Activation::Activation( Environment& environment, void* cobj ) :
  EnvironmentObject( environment, cobj ) {}

  Activation::pointer Activation::create( Environment & environment, void * cobj ) {
    return Activation::pointer( new Activation( environment, cobj ) );
  }


  Activation::~Activation() {}

  std::string Activation::name( )
  {
    if ( m_cobj )
      return EnvGetActivationName( m_environment.cobj(), m_cobj );
    else
      return std::string();
  }

  std::string Activation::formatted( )
  {
    char temp[2001];
    if ( m_cobj ) {
      EnvGetActivationPPForm( m_environment.cobj(), temp, 2000, m_cobj );
      return temp;
    }
    else
      return std::string();
  }

  bool Activation::deactivate( )
  {
    if ( m_cobj )
      return EnvDeleteActivation( m_environment.cobj(), m_cobj );
    else
      return false;
  }

  int Activation::salience( )
  {
    if ( m_cobj )
      return EnvGetActivationSalience( m_environment.cobj(), m_cobj );
    else
      return INT_MIN;
  }

  int Activation::set_salience( int sal )
  {
    if ( m_cobj )
      return EnvSetActivationSalience( m_environment.cobj(), m_cobj, sal );
    else
      return INT_MIN;
  }

  Activation::pointer Activation::next( )
  {
    void* nxt = NULL;
    if ( m_cobj ) {
      nxt = EnvGetNextActivation( m_environment.cobj(), m_cobj );
      if ( nxt )
        return Activation::create( m_environment, nxt );
    }

    return Activation::pointer();
  }

}

