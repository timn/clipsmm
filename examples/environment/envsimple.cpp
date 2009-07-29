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
#include <clipsmm.h>

int main( int argc, char** argv )
{
  // Before any clipsmm objects are instantiated or any other
  // calls are made, call CLIPS::init() to initialize the clipsmm
  // environment, which includes the threading system.
  CLIPS::init();

  CLIPS::Environment env1;
  CLIPS::Environment env2;

  env1.load( "strips.clp" );
  env2.load( "strips.clp" );

  env1.watch( "all" );
  env2.watch( "all" );

  env1.reset();
  env2.reset();

  env1.run( -1 );
  env2.run( -1 );

  return 0;
}
