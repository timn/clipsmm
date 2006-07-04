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
#ifndef CLIPSTEMPLATE_H
#define CLIPSTEMPLATE_H

#include <vector>

#include <clipsmm/environmentobject.h>
#include <clipsmm/value.h>

#undef NO_DEFAULT
#undef STATIC_DEFAULT
#undef DYNAMIC_DEFAULT

namespace CLIPS {

typedef enum DefaultType {
  NO_DEFAULT=0,
  STATIC_DEFAULT=1,
  DYNAMIC_DEFAULT=2,
} DefaultType;

/**
	@author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
*/
class Template: public EnvironmentObject {
public:
  typedef std::tr1::shared_ptr<Template> pointer;

  Template( Environment& environment, void* cobj=NULL );

  static Template::pointer create( Environment& environment, void* cobj=NULL );

    ~Template();

    /** The name of this template */
    std::string name();

    /** The name of the module this template is in */
    std::string module();

    std::string formatted();

    /** Returns the allowed values for a given slot */
		Values slot_allowed_values( const std::string& slot_name );

    /** Returns the cardinality information for a slot */
    Values slot_cardinality( const std::string& slot_name );

    /** Determines whether a slot has a default value */
    DefaultType slot_default_type( const std::string& slot_name );

    /** Returns the default value for a given slot */
    Values slot_default_value( const std::string& slot_name );

    /** Returns the range information for a slot */
    Values slot_range( const std::string& slot_name );

    /** Determines whether a slot exists in the template */
    bool slot_exists( const std::string& slot_name );

    /** Determines whether a slot is a multifield slot */
    bool is_multifield_slot( const std::string& slot_name );

    /** Determines whether a slot is a single field slot */
    bool is_single_field_slot( const std::string& slot_name );

    /** Returns the slot names associated with this template */
    std::vector<std::string> slot_names();
    
    /** True is this template is being watched */
    bool is_watched();

    Template::pointer next();

    bool is_deletable();

    void set_watch( unsigned state );

    bool undefine();
    
  protected:

};

}

#endif
