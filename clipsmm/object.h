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
#ifndef CLIPSOBJECT_H
#define CLIPSOBJECT_H

#include <sigc++/sigc++.h>

#include <clipsmm/pointer.h>

namespace CLIPS {

/**
 * @author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
 */
class Object : public sigc::trackable
{
public:
  typedef CLIPSPointer<Object> pointer;

    Object(void* cobj=NULL);

    ~Object();

    /** Returns a pointer to the underlying CLIPS C object */
    void* cobj() const;

  protected:
    /** The underlying CLIPS C object */
    void* m_cobj;

};

}

#endif
