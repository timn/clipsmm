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
