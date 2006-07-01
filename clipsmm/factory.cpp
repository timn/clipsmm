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
      case STRING:
        s = DOToString( clipsdo );
        values.push_back( String::create( s ) );
        return values;
      case INSTANCE_NAME:
        s = DOToString( clipsdo );
        values.push_back( InstanceName::create( s ) );
        return values;
      case SYMBOL:
        s = DOToString( clipsdo );
        values.push_back( Symbol::create( s ) );
        return values;
      case FLOAT:
        d = DOToDouble( clipsdo );
        values.push_back( Float::create( d ) );
        return values;
      case INTEGER: 
        i = DOToLong( clipsdo );
        values.push_back( Integer::create( i ) );
        return values;
      case INSTANCE_ADDRESS:
        p = DOToPointer( clipsdo );
        values.push_back( InstanceAddress::create( p ) );
        return values;
      case EXTERNAL_ADDRESS:
        p = DOToPointer( clipsdo );
        values.push_back( ExternalAddress::create( p ) );
        return values;
      case MULTIFIELD:
        end = GetDOEnd( clipsdo );
        mfptr = GetValue( clipsdo );
        for ( int iter = GetDOBegin( clipsdo ); iter <= end; iter++ ) {
          switch ( GetMFType( mfptr, iter ) ) {
            case STRING:
              s = ValueToString( GetMFValue( mfptr, iter ) );
              values.push_back( String::create( s ) );
              break;
            case SYMBOL:
              s = ValueToString( GetMFValue( mfptr, iter ) );
              values.push_back( Symbol::create( s ) );
              break;
            case FLOAT:
              d = ValueToDouble( GetMFValue( mfptr, iter ) );
              values.push_back( Float::create( d ) );
              break;
            case INTEGER:
              i = ValueToLong( GetMFValue( mfptr, iter ) );
              values.push_back( Integer::create( i ) );
              break;
            default:
              throw std::logic_error( "clipsmm: Unhandled multifield type" );
          }
        }
        return values;
      default:
        throw std::logic_error( "clipsmm: Unhandled data object type" );
    }
  }

	dataObject * values_to_data_object( Environment& env, Values & values )
	{
    void *p, *p2;
		dataObject* clipsdo = new dataObject;

    switch ( values.size() ) {
      case 0:
        return NULL;
      case 1:
        switch ( values[0]->clips_type() ) {
          case SYMBOL:
            p = EnvAddSymbol( env.cobj(), const_cast<char*>(Symbol::pointer_cast( values[0] )->get().c_str()));
            SetpType(clipsdo, SYMBOL);
            SetpValue(clipsdo, p);
            return clipsdo;
          case STRING:
            p = EnvAddSymbol( env.cobj(), const_cast<char*>(String::pointer_cast( values[0] )->get().c_str()));
            SetpType(clipsdo, STRING);
            SetpValue(clipsdo, p);
            return clipsdo;
          case INSTANCE_NAME:
            p = EnvAddSymbol( env.cobj(), const_cast<char*>(InstanceName::pointer_cast( values[0] )->get().c_str()));
            SetpType(clipsdo, INSTANCE_NAME);
            SetpValue(clipsdo, p);
            return clipsdo;
          case INTEGER:
            p = EnvAddLong( env.cobj(), Integer::pointer_cast( values[0] )->get());
            SetpType(clipsdo, INTEGER);
            SetpValue(clipsdo, p);
            return clipsdo;
          case FLOAT:
            p = EnvAddDouble( env.cobj(), Float::pointer_cast( values[0] )->get());
            SetpType(clipsdo, FLOAT);
            SetpValue(clipsdo, p);
            return clipsdo;
          default:
            throw std::logic_error( "clipsmm: Unhandled data object type" );
        }
      default:
        p = EnvCreateMultifield( env.cobj(), values.size() );
        for (int iter = 0; iter < values.size(); iter++) {
          switch ( values[iter]->clips_type() ) {
            case SYMBOL:
              p2 = EnvAddSymbol( env.cobj(), const_cast<char*>(Symbol::pointer_cast( values[iter] )->get().c_str()));
              SetMFType(p, iter, SYMBOL);
              SetMFValue(p, iter, p2);
              break;
            case STRING:
              p2 = EnvAddSymbol( env.cobj(), const_cast<char*>(String::pointer_cast( values[iter] )->get().c_str()));
              SetMFType(p, iter, STRING);
              SetMFValue(p, iter, p2);
              break;
            case INSTANCE_NAME:
              p2 = EnvAddSymbol( env.cobj(), const_cast<char*>(InstanceName::pointer_cast( values[iter] )->get().c_str()));
              SetMFType(p, iter, INSTANCE_NAME);
              SetMFValue(p, iter, p2);
              break;
            case INTEGER:
              p2 = EnvAddLong( env.cobj(), Integer::pointer_cast( values[iter] )->get());
              SetMFType(p, iter, INTEGER);
              SetMFValue(p, iter, p2);
              break;
            case FLOAT:
              p2 = EnvAddDouble( env.cobj(), Float::pointer_cast( values[iter] )->get());
              SetMFType(p, iter, FLOAT);
              SetMFValue(p, iter, p2);
              break;
            default:
              throw std::logic_error( "clipsmm: Unhandled data object type" );
          }
        }
        SetpType(clipsdo, MULTIFIELD);
        SetpValue(clipsdo, p);
        return clipsdo;
    }

		return NULL;
	}

}
