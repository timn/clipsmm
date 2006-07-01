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

#include <sigc++/sigc++.h>

// Headers for smart pointers
#include <typeinfo>
#include <memory>
#include <functional>
#include <bits/concurrence.h>
#include <ext/mt_allocator.h>
#include <tr1/boost_shared_ptr.h>

#include <clipsmm/template.h>

namespace CLIPS {

class Environment;

/**
	@author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
*/
class Fact: public sigc::trackable {
public:
  typedef std::tr1::shared_ptr<Fact> pointer;

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

    typedef std::vector<std::string> SlotNames;
    /** Returns the slot names associated with this fact */
    SlotNames slot_names();

    /** Returns a pointer to the underlying CLIPS C object */
    void* cobj();

  protected:
    Environment* m_environment;
    void* m_cobj;
};

}

#endif
