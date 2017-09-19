/***************************************************************************
 *   Copyright (C) 2006,2009 by Rick L. Vinyard, Jr.                       *
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
#include <clipsmm/clipsmm-config.h>

#ifndef CLIPSPOINTER
#define CLIPSPOINTER
#if __cplusplus <= 199711L
  #error clipsmm requires at least a C++11 compliant compiler
#endif

#include <memory>
#define CLIPSPointer std::shared_ptr
#define CLIPSWeakPointer std::weak_ptr
#define clips_static_pointer_cast  std::static_pointer_cast
#define clips_const_pointer_cast   std::const_pointer_cast
#define clips_dynamic_pointer_cast std::dynamic_pointer_cast

#endif
