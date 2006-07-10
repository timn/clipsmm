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
#include <clipsmm/environment.h>

namespace CLIPS {

  Values data_object_to_values( dataObject* clipsdo ) {
    return data_object_to_values( *clipsdo );
  }

  Values data_object_to_values( dataObject& clipsdo ) {
    Values values;
    
    std::string s;
    double d;
    long int i;
    void* p;
    
    void* mfptr;
    long int end;

    switch ( GetType( clipsdo ) ) {
      case RVOID:
        return values;
      case STRING:
        s = DOToString( clipsdo );
        values.push_back( Value( s, TYPE_STRING ) );
        return values;
      case INSTANCE_NAME:
        s = DOToString( clipsdo );
        values.push_back( Value( s, TYPE_INSTANCE_NAME ) );
        return values;
      case SYMBOL:
        s = DOToString( clipsdo );
        values.push_back( Value( s, TYPE_SYMBOL ) );
        return values;
      case FLOAT:
        d = DOToDouble( clipsdo );
        values.push_back( Value( d ) );
        return values;
      case INTEGER:
        i = DOToLong( clipsdo );
        values.push_back( Value( i ) );
        return values;
      case INSTANCE_ADDRESS:
        p = DOToPointer( clipsdo );
        values.push_back( Value( p, TYPE_INSTANCE_ADDRESS ) );
        return values;
      case EXTERNAL_ADDRESS:
        p = DOToPointer( clipsdo );
        values.push_back( Value( p, TYPE_EXTERNAL_ADDRESS ) );
        return values;
      case MULTIFIELD:
        end = GetDOEnd( clipsdo );
        mfptr = GetValue( clipsdo );
        for ( int iter = GetDOBegin( clipsdo ); iter <= end; iter++ ) {
          switch ( GetMFType( mfptr, iter ) ) {
            case STRING:
              s = ValueToString( GetMFValue( mfptr, iter ) );
              values.push_back( Value( s, TYPE_STRING ) );
              break;
            case SYMBOL:
              s = ValueToString( GetMFValue( mfptr, iter ) );
              values.push_back( Value( s, TYPE_SYMBOL ) );
              break;
            case FLOAT:
              d = ValueToDouble( GetMFValue( mfptr, iter ) );
              values.push_back( Value( d ) );
              break;
            case INTEGER:
              i = ValueToLong( GetMFValue( mfptr, iter ) );
              values.push_back( Value( i ) );
              break;
            default:
              throw std::logic_error( "clipsmm::data_object_to_values: Unhandled multifield type" );
          }
        }
        return values;
      default:
        std::cout << std::endl << "Type: " << GetType(clipsdo) << std::endl;
        throw std::logic_error( "clipsmm::data_object_to_values: Unhandled data object type" );
    }
  }

	dataObject * value_to_data_object( const Environment& env, const Value & value )
	{
    void *p;
		dataObject* clipsdo = new dataObject;

    SetpType(clipsdo, value.type() );
    switch ( value.type() ) {
      case SYMBOL:
      case STRING:
      case INSTANCE_NAME:
        p = EnvAddSymbol( env.cobj(),
                          const_cast<char*>( value.as_string().c_str())
                        );
        SetpValue(clipsdo, p);
        return clipsdo;
      case INTEGER:
        p = EnvAddLong( env.cobj(), value.as_integer() );
        SetpValue(clipsdo, p);
        return clipsdo;
      case FLOAT:
        p = EnvAddDouble( env.cobj(), value.as_float() );
        SetpValue(clipsdo, p);
        return clipsdo;
      default:
        throw std::logic_error( "clipsmm::value_to_data_object: Unhandled data object type" );
    }

		return NULL;
	}

  dataObject * value_to_data_object( const Environment& env, const Values & values )
  {
    void *p, *p2;

    if (values.size() == 0 )
      return NULL;
    
    if ( values.size() == 1 )
      return value_to_data_object( env, values[0] );
    
    dataObject* clipsdo = new dataObject;

    p = EnvCreateMultifield( env.cobj(), values.size() );
    for (int iter = 0; iter < values.size(); iter++) {
      SetMFType(p, iter, values[iter].type());
      switch ( values[iter].type() ) {
        case SYMBOL:
        case STRING:
        case INSTANCE_NAME:
          p2 = EnvAddSymbol( env.cobj(),
                             const_cast<char*>(values[iter].as_string().c_str())
                           );
          SetMFValue(p, iter, p2);
          break;
        case INTEGER:
          p2 = EnvAddLong( env.cobj(), values[iter].as_integer() );
          SetMFValue(p, iter, p2);
          break;
        case FLOAT:
          p2 = EnvAddDouble( env.cobj(), values[iter].as_float() );
          SetMFValue(p, iter, p2);
          break;
        default:
          throw std::logic_error( "clipsmm::value_to_data_object: Unhandled data object type" );
      }
    }
    SetpType(clipsdo, MULTIFIELD);
    SetpValue(clipsdo, p);
    return clipsdo;
  }

}
