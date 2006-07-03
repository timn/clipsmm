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
#include "utility.h"

#include <clips/clips.h>

namespace CLIPS {

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

}
