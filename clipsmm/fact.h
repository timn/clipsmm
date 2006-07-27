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
#ifndef CLIPSFACT_H
#define CLIPSFACT_H

#include <string>
#include <vector>

#include <clipsmm/environmentobject.h>
#include <clipsmm/template.h>
#include <clipsmm/factory.h>

namespace CLIPS {

/**
	@author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
*/
class Fact: public EnvironmentObject {
public:
  typedef SHAREDPTRNS::shared_ptr<Fact> pointer;

    Fact( Environment& environment, void* cobj=NULL );

    static Fact::pointer create( Environment& environment, void* cobj=NULL );

    ~Fact();

    /**
     * Assigns default values to a fact.
     * @return true if the default values were successfully set, false otherwise
     */
    bool assign_slot_defaults();

    /** Returns the template associated with a fact. */
    Template::pointer get_template();

    /**
     * Indicates whether a fact is still in the fact list or has been retracted
     * @return true if the fact is still in the fact list, false otherwise
     */
    bool exists();

    /**
     * Returns the fact index of a fact
     * @return the index of the fact or -1 if this fact object is uninitialized
     */
    long int index();

    /** Returns the slot names associated with this fact */
    std::vector<std::string> slot_names();

		/** Return the values contained within a slot */
    Values slot_value(const std::string& slot_name);

		/** Returns the next fact in the fact list */
		Fact::pointer next();

    /** Sets the named slot to a specific value or values */
    bool set_slot(const std::string& slot_name, const Values& values);

    /** Sets the named slot to a specific value or values */
    bool set_slot(const std::string& slot_name, const Value& value);

    /** Retracts a fact from the fact list */
		bool retract();

  protected:

};

}

#endif
