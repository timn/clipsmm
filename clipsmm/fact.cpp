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
#include "fact.h"

#include <clipsmm/environment.h>
#include <clips/clips.h>

namespace CLIPS {

  Fact::Fact( Environment& environment, void* cobj ) : m_environment( &environment ), m_cobj( cobj ) {
    EnvIncrementFactCount( m_environment->cobj(), m_cobj );
  }

  Fact::pointer Fact::create( Environment& environment, void* cobj ) {
    return Fact::pointer( new Fact( environment, cobj ) );
  }

  Fact::~Fact() {
    EnvDecrementFactCount( m_environment->cobj(), m_cobj );
  }

  bool Fact::assign_slot_defaults() {
    if ( m_cobj )
      return EnvAssignFactSlotDefaults( m_environment->cobj(), m_cobj );
  }

  Template::pointer Fact::get_template() {
    if ( !m_cobj )
      return Template::pointer();

    void* tem = EnvFactDeftemplate( m_environment->cobj(), m_cobj );

    if ( tem )
      return Template::create( *m_environment, tem );
    else
      return Template::pointer();
  }

  bool Fact::exists() {
    if ( m_cobj )
      return EnvFactExistp( m_environment->cobj(), m_cobj );
    return false;
  }

  long int Fact::index() {
    if ( m_cobj )
      return EnvFactIndex( m_environment->cobj(), m_cobj );
    return -1;
  }

  void* Fact::cobj() {
    return m_cobj;
  }

  std::vector<std::string> Fact::slot_names() {
    DATA_OBJECT clips_data_object;
    void* mfptr;
    long int end, i;
    std::string s;
    SlotNames slot_names;

    if ( !m_cobj )
      return SlotNames();

    EnvFactSlotNames( m_environment->cobj(), m_cobj, &clips_data_object );

    if ( ! GetType( clips_data_object ) == MULTIFIELD )
      return SlotNames();

    end = GetDOEnd( clips_data_object );
    mfptr = GetValue( clips_data_object );
    for ( i = GetDOBegin( clips_data_object ); i <= end; i++ ) {
      switch ( GetMFType( mfptr, i ) ) {
        case STRING:
        case SYMBOL:
          s = ValueToString( GetMFValue( mfptr, i ) );
          slot_names.push_back( s );
          break;
        default:
          break;
      }
    }
    return slot_names;
  }

}
