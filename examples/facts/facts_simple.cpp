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

#include <iostream>

int main( int argc, char** argv )
{
  CLIPS::init();

  CLIPS::Environment environment;
  CLIPS::Fact::pointer fact;
  std::vector<std::string> slot_names;
  std::vector<std::string>::iterator iter;

  environment.load( "strips.clp" );

  fact = environment.assert_fact("(in (object R2D2) (location RoomC) )");
  slot_names = fact->slot_names();
  for (iter = slot_names.begin(); iter != slot_names.end(); iter++)
    std::cout << "Slot name: " << *iter << std::endl;
  std::cout << std::endl;

  fact = environment.assert_fact("(numbers 1 2 3 4 5 )");
  slot_names = fact->slot_names();
  for (iter = slot_names.begin(); iter != slot_names.end(); iter++)
    std::cout << "Slot name: " << *iter << std::endl;

  return 0;
}
