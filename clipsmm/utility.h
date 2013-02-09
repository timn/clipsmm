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
#ifndef CLIPSUTILITY_H
#define CLIPSUTILITY_H

#include <vector>
#include <string>
#include <stdexcept>

#include <clipsmm/value.h>

extern "C" {
  struct dataObject;
}

namespace CLIPS {

  /** The init method should be called before any other clipsmm functions. */
  void init( );

  std::vector<std::string> data_object_to_strings(dataObject* clipsdo);
  std::vector<std::string> data_object_to_strings(dataObject& clipsdo);

  void get_argument(void* env, int argposition, double& value);
  void get_argument(void* env, int argposition, float& value);
  void get_argument(void* env, int argposition, short& value);
  void get_argument(void* env, int argposition, short unsigned& value);
  void get_argument(void* env, int argposition, int& value);
  void get_argument(void* env, int argposition, unsigned& value);
  void get_argument(void* env, int argposition, long& value);
  void get_argument(void* env, int argposition, std::string& value);
  void get_argument(void* env, int argposition, Values& values);
  void get_argument(void* env, int argposition, Value& value);
  void get_argument(void* env, int argposition, void*& value);

  template <typename T_return> inline char get_return_code() {
    throw std::logic_error("clipsmm: Adding function with invalid return type");
  }
  template <> inline char get_return_code<void *>()      { return 'a'; }
  template <> inline char get_return_code<bool>()        { return 'b'; }
  template <> inline char get_return_code<char>()        { return 'c'; }
  template <> inline char get_return_code<double>()      { return 'd'; }
  template <> inline char get_return_code<float>()       { return 'f'; }
  template <> inline char get_return_code<int>()         { return 'i'; }
  template <> inline char get_return_code<long>()        { return 'l'; }
  template <> inline char get_return_code<std::string>() { return 's'; }
  template <> inline char get_return_code<void>()        { return 'v'; }
  template <> inline char get_return_code<Values>()      { return 'm'; }
  template <> inline char get_return_code<Value>()       { return 'u'; }

  template <typename T_return> inline char get_argument_code() {
    throw std::logic_error("clipsmm: Adding function with invalid argument type");
  }
  template <> inline char get_argument_code<void *>()      { return 'a'; }
  template <> inline char get_argument_code<double>()      { return 'd'; }
  template <> inline char get_argument_code<float>()       { return 'f'; }
  template <> inline char get_argument_code<int>()         { return 'i'; }
  template <> inline char get_argument_code<long>()        { return 'l'; }
  template <> inline char get_argument_code<std::string>() { return 's'; }
  template <> inline char get_argument_code<Values>()      { return 'm'; }
  template <> inline char get_argument_code<Value>()       { return 'u'; }

}

#endif
