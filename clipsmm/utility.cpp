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
#include "utility.h"
#include "factory.h"

#include <glibmm/thread.h>

extern "C" {
  #include <clips/clips.h>
};

namespace CLIPS {

  void init() {
    if(!Glib::thread_supported()) Glib::thread_init();
  }
  
  std::vector<std::string> data_object_to_strings( dataObject* clipsdo ) {
    return data_object_to_strings( *clipsdo );
  }

  std::vector<std::string> data_object_to_strings( dataObject& clipsdo ) {
    void* mfptr;
    long int end, i;
    std::string s;
    std::vector<std::string> strings;

    switch ( GetType(clipsdo) ) {
      case SYMBOL:
      case INSTANCE_NAME:
      case STRING:
        strings.push_back( DOToString( clipsdo ) );
        break;
      case MULTIFIELD:
        end = GetDOEnd( clipsdo );
        mfptr = GetValue( clipsdo );
        for ( i = GetDOBegin( clipsdo ); i <= end; i++ ) {
          switch ( GetMFType( mfptr, i ) ) {
            case SYMBOL:
            case STRING:
            case INSTANCE_NAME:
              strings.push_back( ValueToString( GetMFValue( mfptr, i ) ) );
              break;
            default:
              break;
          }
        }
      default:
        break;
    }

    return strings;
  }

  void get_argument(void* env, int argposition, void *& value) {
    struct dataObject obj;
    EnvRtnUnknown(env, argposition, &obj);
    if (obj.type == EXTERNAL_ADDRESS) {
      value = (((struct externalAddressHashNode *) (obj.value))->externalAddress);
    }
  }

  void get_argument(void* env, int argposition, double& value) {
    value = EnvRtnDouble(env, argposition);
  }

  void get_argument(void* env, int argposition, float& value) {
    value = static_cast<float>( EnvRtnDouble(env, argposition) );
  }

  void get_argument(void* env, int argposition, short& value) {
    value = static_cast<short>( EnvRtnLong(env, argposition) );
  }

  void get_argument(void* env, int argposition, short unsigned& value) {
    value = static_cast<short unsigned>( EnvRtnLong(env, argposition) );
  }

  void get_argument(void* env, int argposition, int& value) {
    value = static_cast<int>( EnvRtnLong(env, argposition) );
  }

  void get_argument(void* env, int argposition, unsigned& value) {
    value = static_cast<unsigned>( EnvRtnLong(env, argposition) );
  }

  void get_argument(void* env, int argposition, long& value) {
    value = EnvRtnLong(env, argposition);
  }

  void get_argument(void* env, int argposition, std::string& value) {
    value = EnvRtnLexeme(env, argposition);
  }

  void get_argument(void* env, int argposition, Values& values) {
    DATA_OBJECT arg;
    if (EnvArgTypeCheck(env, (char *)"clipsmm get_argument",
                        argposition, MULTIFIELD, &arg) == 0)   return;

    values.clear();

    int end = EnvGetDOEnd(env, arg);
    void *mfp = EnvGetValue(env, arg);
    for (int i = EnvGetDOBegin(env, arg); i <= end; ++i) {
      switch (GetMFType(mfp, i)) {
      case SYMBOL:
      case STRING:
      case INSTANCE_NAME:
        values.push_back(Value(ValueToString(GetMFValue(mfp, i))));
        break;
      case FLOAT:
        values.push_back(Value(ValueToDouble(GetMFValue(mfp, i))));
        break;
      case INTEGER:
        values.push_back(Value(ValueToInteger(GetMFValue(mfp, i))));
        break;
      default:
        continue;
        break;
      }
    }
  }

  void get_argument(void* env, int argposition, Value& value) {
    struct dataObject obj;
    EnvRtnUnknown(env, argposition, &obj);
    Values values = data_object_to_values(obj);
    if (values.size() > 0) {
      value = values[0];
    }
  }

}
