/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>     *
 *   Copyright (C) 2013 by Tim Niemueller <tim@niemueller.de>              *
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
#include "fact.h"

extern "C" {
  #include <clips/clips.h>
};

#include <clipsmm/utility.h>
#include <clipsmm/environment.h>

namespace CLIPS {

  Fact::Fact( Environment& environment, void* cobj )
    : EnvironmentObject(environment, cobj)
  {
    if (m_cobj)
      EnvIncrementFactCount( m_environment.cobj(), m_cobj );
  }

  Fact::pointer Fact::create( Environment& environment, void* cobj ) {
    return Fact::pointer( new Fact( environment, cobj ) );
  }

  Fact::pointer Fact::create( Environment& environment, Template::pointer temp ) {
    struct fact * f = EnvCreateFact(environment.cobj(), temp->cobj());
    return Fact::pointer( new Fact( environment, f ) );
  }

  Fact::~Fact() {
    if (m_cobj)
      EnvDecrementFactCount( m_environment.cobj(), m_cobj );
  }

  bool Fact::assign_slot_defaults() {
    if ( m_cobj )
      return EnvAssignFactSlotDefaults( m_environment.cobj(), m_cobj );
		return false;
  }

  Template::pointer Fact::get_template() {
    if ( !m_cobj )
      return Template::pointer();

    void* tem = EnvFactDeftemplate( m_environment.cobj(), m_cobj );

    if ( tem )
      return Template::create( m_environment, tem );
    else
      return Template::pointer();
  }

  bool Fact::exists() const {
    if ( m_cobj )
      return EnvFactExistp( m_environment.cobj(), m_cobj );
    return false;
  }

  long int Fact::index() const {
    if ( m_cobj )
      return EnvFactIndex( m_environment.cobj(), m_cobj );
    return -1;
  }

  std::vector<std::string> Fact::slot_names() {
    DATA_OBJECT clipsdo;

    if ( !m_cobj )
      return std::vector<std::string>();

    EnvFactSlotNames( m_environment.cobj(), m_cobj, &clipsdo );

    return data_object_to_strings( clipsdo );
  }

Values Fact::slot_value( const std::string & name )
	{
		DATA_OBJECT data_object;
		int result;

		if ( !m_cobj )
			return Values();

    if ( name == "" ) {
      result = EnvGetFactSlot( m_environment.cobj(), m_cobj, NULL, &data_object );
//       result = EnvGetFactSlot( m_environment.cobj(), m_cobj, "", &data_object );
    }
    else
  		result = EnvGetFactSlot( m_environment.cobj(), m_cobj, const_cast<char*>(name.c_str()), &data_object );
		if (result)
			return data_object_to_values( data_object );
    else
			return Values();
	}

Fact::pointer Fact::next( )
{
	void* next_fact;

	if ( !m_cobj )
		return Fact::pointer();

	// Can't call EnvGetNextFact on a fact that has been retracted
	if ( ! this->exists() )
		return Fact::pointer();

	next_fact = EnvGetNextFact( m_environment.cobj(), m_cobj );
	if ( next_fact )
		return Fact::create( m_environment, next_fact );
	else
		return Fact::pointer();
}

bool Fact::retract( )
{
  if ( !m_cobj )
    return false;
  return EnvRetract( m_environment.cobj(), m_cobj );
}

bool Fact::set_slot( const std::string & slot_name, const Value & value )
{
  DATA_OBJECT* clipsdo = value_to_data_object( m_environment, value );
  if ( !clipsdo || !m_cobj ) {
    delete clipsdo;
    return false;
  }
  bool rv = EnvPutFactSlot( m_environment.cobj(),
			    m_cobj,
			    const_cast<char*>(slot_name.c_str()),
			    clipsdo);
  delete clipsdo;
  return rv;
}

bool Fact::set_slot( const std::string & slot_name, const Values & values )
{
  DATA_OBJECT* clipsdo = value_to_data_object( m_environment, values );
  if ( !clipsdo || !m_cobj ) {
    delete clipsdo;
    return false;
  }
  bool rv = EnvPutFactSlot( m_environment.cobj(),
			    m_cobj,
			    const_cast<char*>(slot_name.c_str()),
			    clipsdo);
  delete clipsdo;
  return rv;
}


bool Fact::operator==(const Fact &other) const
{
  return (index() == other.index());
}

bool Fact::operator==(const Fact::pointer &other) const
{
  return (index() == other->index());
}

unsigned int
Fact::refcount() const
{
  if (!m_cobj)  return 0;

  struct fact *f = (struct fact *)m_cobj;
  return f->factHeader.busyCount;
}

}
