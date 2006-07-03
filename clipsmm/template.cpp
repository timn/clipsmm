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
#include "template.h"

#include <clips/clips.h>

#include <clipsmm/environment.h>
#include <clipsmm/utility.h>

namespace CLIPS {

Template::Template( Environment& environment, void* cobj ):
    EnvironmentObject(environment, cobj)
{
}

Template::pointer Template::create( Environment& environment, void* cobj ) {
  return Template::pointer( new Template(environment,cobj) );
}

Template::~Template()
{
}

std::string Template::name() {
  if ( !m_cobj )
    return std::string();
  return EnvGetDeftemplateName( m_environment.cobj(), m_cobj );
}

Values Template::allowed_slot_values( const std::string& slot_name )
{
  DATA_OBJECT clipsdo;
  if ( !m_cobj )
    return Values();
  EnvDeftemplateSlotAllowedValues( m_environment.cobj(),
                                   m_cobj,
                                   const_cast<char*>(slot_name.c_str()),
                                   &clipsdo );
  return data_object_to_values( clipsdo );
}

Values Template::slot_cardinality( const std::string & slot_name )
{
  DATA_OBJECT clipsdo;
  if ( !m_cobj )
    return Values();
  EnvDeftemplateSlotCardinality( m_environment.cobj(),
                                 m_cobj,
                                 const_cast<char*>(slot_name.c_str()),
                                 &clipsdo );
  return data_object_to_values( clipsdo );
}

bool Template::slot_exists( const std::string & slot_name )
{
  if ( !m_cobj )
    return false;
  return EnvDeftemplateSlotExistP( m_environment.cobj(),
                                   m_cobj,
                                   const_cast<char*>(slot_name.c_str()) );
}

bool Template::is_multifield_slot( const std::string & slot_name )
{
  if ( !m_cobj )
    return false;
  return EnvDeftemplateSlotMultiP( m_environment.cobj(),
                                   m_cobj,
                                   const_cast<char*>(slot_name.c_str()) );
}

bool Template::is_single_field_slot( const std::string & slot_name )
{
  if ( !m_cobj )
    return false;
  return EnvDeftemplateSlotSingleP( m_environment.cobj(),
                                   m_cobj,
                                   const_cast<char*>(slot_name.c_str()) );
}

  std::vector<std::string> Template::slot_names() {
    DATA_OBJECT clipsdo;

    if ( !m_cobj )
      return std::vector<std::string>();

    EnvDeftemplateSlotNames( m_environment.cobj(), m_cobj, &clipsdo );

    return data_object_to_strings( clipsdo );
  }

  Values Template::slot_range( const std::string & slot_name )
  {
    DATA_OBJECT clipsdo;
    if ( !m_cobj )
      return Values();
    EnvDeftemplateSlotRange( m_environment.cobj(),
                             m_cobj,
                             const_cast<char*>(slot_name.c_str()),
                             &clipsdo );
    return data_object_to_values( clipsdo );
  }



}
