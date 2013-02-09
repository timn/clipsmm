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
#ifndef CLIPSFACTORY_H
#define CLIPSFACTORY_H

#include <clipsmm/value.h>

extern "C" {
  struct dataObject;
}

namespace CLIPS {
  class Environment;

  /** TODO Move to utility, since these are no longer factory methods */
  Values data_object_to_values(dataObject* clipsdo);
  Values data_object_to_values(dataObject& clipsdo);

  dataObject* value_to_data_object(const Environment& env, const Values& values,
				   dataObject *obj = NULL);
  dataObject* value_to_data_object(const Environment& env, const Value& value,
				   dataObject *obj = NULL);

  dataObject* value_to_data_object_rawenv(void *env, const Values& values,
					  dataObject *obj = NULL);
  dataObject* value_to_data_object_rawenv(void *env, const Value& value,
					  dataObject *obj = NULL);

}

#endif
