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
#include <clipsmm/clipsmm-config.h>

#ifndef CLIPSPOINTER
#define CLIPSPOINTER
  // Headers for smart pointers
  #ifdef CLIPSMM_USE_BOOST_SMART_POINTER
    #include <boost/shared_ptr.hpp>
    #define CLIPSPointer boost::shared_ptr
  #else
    #include <typeinfo>
    #include <memory>
    #include <functional>
    #include <bits/concurrence.h>
    #include <ext/mt_allocator.h>
    #include <tr1/boost_shared_ptr.h>
    #define CLIPSPointer std::tr1::shared_ptr
  #endif
#endif
