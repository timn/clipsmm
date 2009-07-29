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

  int i;
  CLIPS::Environment env[4];

  // These really need a more computationally intense example
  // with periodic output to show the threading, but for now
  // strips.clp was at hand.
  env[0].load( "strips.clp" );
  env[1].load( "strips2.clp" );
  env[2].load( "strips3.clp" );
  env[3].load( "strips4.clp" );

  // Setup each environment - this part isn't threaded... yet
  for (i=0; i<4; i++) {
    env[i].watch( "all" );
    env[i].reset();
  }

  // Threaded execution
  for (i=0; i<4; i++)
    env[i].run_threaded(-1);

  // Wait for each of the threads to complete
  for (i=0; i<4; i++)
    env[i].join_run_thread();

  return 0;
}
