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
#ifndef CLIPSVALUEBASE_H
#define CLIPSVALUEBASE_H

// Headers for smart pointers
#include <typeinfo>
#include <memory>
#include <functional>
#include <bits/concurrence.h>
#include <ext/mt_allocator.h>
#include <tr1/boost_shared_ptr.h>

#include <vector>

#include <sigc++/sigc++.h>

namespace CLIPS {

  class ValueBase: public sigc::trackable {
    public:
      typedef std::tr1::shared_ptr<ValueBase> pointer;

      /** Default constructor that doesn't do much. */
      ValueBase () { }

      /** Destructor */
      virtual ~ValueBase() { }

      /**
       * Returns the RTTI type id of the contained type
       */
      virtual const std::type_info& type() const = 0;

      /**
       * Returns the size in bytes of the contained type,
       * and not necessarily the size of this class.
       */
      virtual size_t size() const = 0;

      /** Signal emitted when the value is changed. */
      sigc::signal<void> signal_changed() {
        return m_signal_changed;
      }

    protected:
      /**
       * Signal emitted when underlying data is changed.
       */
      sigc::signal<void> m_signal_changed;

  };

  typedef std::vector<ValueBase::pointer> Values;
  
}

#endif
