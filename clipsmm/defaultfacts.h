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
#ifndef CLIPSDEFAULTFACTS_H
#define CLIPSDEFAULTFACTS_H

#include <string>

#include <clipsmm/environmentobject.h>

namespace CLIPS {

  /**
    @author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
  */
  class DefaultFacts : public EnvironmentObject {
    public:
      typedef CLIPSSmartPointer<DefaultFacts> pointer;

      DefaultFacts( Environment& environment, void* cobj = NULL );

      static DefaultFacts::pointer create( Environment& environment, void* cobj = NULL );

      ~DefaultFacts();

      std::string name();

      std::string module_name();

      std::string formatted();

      DefaultFacts::pointer next();

      bool is_deletable();

      bool retract();

  };

}

#endif
