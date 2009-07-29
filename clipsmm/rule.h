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
#ifndef CLIPSRULE_H
#define CLIPSRULE_H

#include <clipsmm/environmentobject.h>

namespace CLIPS {

/**
	@author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
*/
class Rule: public EnvironmentObject {
public:
  typedef CLIPSPointer<Rule> pointer;

  Rule( Environment& environment, void* cobj=NULL );

  static Rule::pointer create( Environment& environment, void* cobj=NULL );

    ~Rule();

    bool is_breakpoint_set();

    std::string module_name();

    std::string name();

    std::string formatted();

    bool activations_watched();

    bool firings_watched();

    Rule::pointer next();

    bool is_deletable();

    void refresh();

    bool remove_break();

    void set_break();

    void set_watch_activations( bool set=true );

    void set_watch_firings( bool set=true );

    bool retract();

    /** TODO Matches */

  protected:

};

}

#endif
