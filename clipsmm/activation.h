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
#ifndef CLIPSACTIVATION_H
#define CLIPSACTIVATION_H

#include <string>

#include <clipsmm/environmentobject.h>

namespace CLIPS {

  /**
    @author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
  */
  class Activation : public EnvironmentObject {
    public:
      typedef CLIPSPointer<Activation> pointer;

      Activation( Environment& environment, void* cobj = NULL );

      static Activation::pointer create( Environment& environment, void* cobj = NULL );

      ~Activation();

      std::string name();

      std::string formatted();

      bool deactivate();

      int salience();

      /**
       * Sets the salience value.
       * @return the old salience value
       */
      int set_salience( int sal );

      Activation::pointer next();

  };

}

#endif
