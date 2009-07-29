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
#ifndef CLIPSMODULE_H
#define CLIPSMODULE_H

#include <clipsmm/environmentobject.h>

namespace CLIPS {

/**
	@author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
*/
class Module: public EnvironmentObject {
public:
  typedef CLIPSPointer<Module> pointer;

  Module( Environment& environment, void* cobj=NULL );

  static Module::pointer create( Environment& environment, void* cobj=NULL );

  ~Module();

  std::string name();

  std::string formatted();

  Module::pointer next();

  // TODO add accessors for getting items associated with a module

  /** Sets the current module and returns the old module */
  Module::pointer set_current();

  void focus();

};

}

#endif
