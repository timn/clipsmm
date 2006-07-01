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
#include <clipsmm/factory.h>

#include <string>
#include <stdexcept>

#include <clips/clips.h>

namespace CLIPS {

  Values data_object_to_values( dataObject* clipsdo ) {
    return data_object_to_values( *clipsdo );
  }

  Values data_object_to_values( dataObject& clipsdo ) {
    Values values;
    switch ( GetType( clipsdo ) ) {
      case STRING:
      case INSTANCE_NAME:
      case SYMBOL: {
          std::string s = DOToString( clipsdo );
          values.push_back( Value<std::string>::create( s ) );
          return values;
      }
      case FLOAT: {
          double d = DOToDouble( clipsdo );
          values.push_back( Value<double>::create( d ) );
          return values;
      }
      case INTEGER: {
          long int i = DOToLong( clipsdo );
          values.push_back( Value<long int>::create( i ) );
          return values;
      }
      case INSTANCE_ADDRESS:
      case EXTERNAL_ADDRESS: {
          void* p = DOToPointer( clipsdo );
          values.push_back( Value<void*>::create( p ) );
          return values;
      }
      case MULTIFIELD: {
          void* mfptr;
          long int end, i;
          end = GetDOEnd( clipsdo );
          mfptr = GetValue( clipsdo );
          for ( i = GetDOBegin( clipsdo ); i <= end; i++ ) {
            switch ( GetMFType( mfptr, i ) ) {
              case STRING:
              case SYMBOL: {
                  std::string s = ValueToString( GetMFValue( mfptr, i ) );
                  values.push_back( Value<std::string>::create( s ) );
                }
                break;
              case FLOAT: {
                  double d = ValueToDouble( GetMFValue( mfptr, i ) );
                  values.push_back( Value<double>::create( d ) );
                }
                break;
              case INTEGER: {
                  long int i = ValueToLong( GetMFValue( mfptr, i ) );
                  values.push_back( Value<long int>::create( i ) );
                }
                break;
              default:
                throw std::logic_error( "clipsmm: Unhandled multifield type" );
            }
          }
          return values;
      }
      default:
        throw std::logic_error( "clipsmm: Unhandled data object type" );
    }
  }

}
