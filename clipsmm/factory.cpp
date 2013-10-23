/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.  <rvinyard@cs.nmsu.edu>    *
 *   Copyright (C) 2013 by Tim Niemueller [http://www.niemueller.de]       *
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
#include <clipsmm/factory.h>

#include <string>
#include <stdexcept>

extern "C" {
  #include <clips/clips.h>
};

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
      p = (((struct externalAddressHashNode *) (clipsdo.value))->externalAddress);
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
	case EXTERNAL_ADDRESS:
	  p = ValueToExternalAddress( GetMFValue( mfptr, iter ) );
	  values.push_back( Value( p, TYPE_EXTERNAL_ADDRESS ) );
	  break;
	default:
	  throw std::logic_error( "clipsmm::data_object_to_values: Unhandled multifield type" );
	}
      }
      return values;
    default:
      //std::cout << std::endl << "Type: " << GetType(clipsdo) << std::endl;
      throw std::logic_error( "clipsmm::data_object_to_values: Unhandled data object type" );
    }
  }

  dataObject *
  value_to_data_object(const Environment& env, const Value & value, dataObject *obj)
  {
    return value_to_data_object_rawenv(env.cobj(), value, obj);
  }


  dataObject *
  value_to_data_object_rawenv(void *env, const Value & value, dataObject *obj)
  {
    void *p;

    dataObject* clipsdo = obj;
    if (! clipsdo) {
      clipsdo = new dataObject;
    }

    SetpType(clipsdo, value.type() );
    switch ( value.type() ) {
      case TYPE_SYMBOL:
      case TYPE_STRING:
      case TYPE_INSTANCE_NAME:
        p = EnvAddSymbol( env,
                          const_cast<char*>( value.as_string().c_str())
                        );
        SetpValue(clipsdo, p);
        return clipsdo;
      case TYPE_INTEGER:
        p = EnvAddLong( env, value.as_integer() );
        SetpValue(clipsdo, p);
        return clipsdo;
      case TYPE_FLOAT:
        p = EnvAddDouble( env, value.as_float() );
        SetpValue(clipsdo, p);
        return clipsdo;
      case TYPE_EXTERNAL_ADDRESS:
        p = EnvAddExternalAddress( env, value.as_address(), EXTERNAL_ADDRESS );
        SetpValue(clipsdo, p);
        return clipsdo;
      default:
        throw std::logic_error( "clipsmm::value_to_data_object: Unhandled data object type" );
    }

    return NULL;
  }

  dataObject *
  value_to_data_object(const Environment& env, const Values & values,
		       dataObject *obj)
  {
    return value_to_data_object_rawenv(env.cobj(), values, obj);
  }

  dataObject *
  value_to_data_object_rawenv(void *env, const Values & values,
			      dataObject *obj)
  {
    void *p, *p2;

    dataObject* clipsdo = obj;
    if (! clipsdo) {
      clipsdo = new dataObject;
    }

    p = EnvCreateMultifield( env, values.size() );
    for (unsigned int iter = 0; iter < values.size(); iter++) {
      unsigned int mfi = iter + 1; // mfptr indices start at 1
      SetMFType(p, mfi, values[iter].type());
      switch ( values[iter].type() ) {
        case TYPE_SYMBOL:
        case TYPE_STRING:
        case TYPE_INSTANCE_NAME:
          p2 = EnvAddSymbol( env,
                             const_cast<char*>(values[iter].as_string().c_str())
                           );
          SetMFValue(p, mfi, p2);
          break;
        case TYPE_INTEGER:
          p2 = EnvAddLong( env, values[iter].as_integer() );
          SetMFValue(p, mfi, p2);
          break;
        case TYPE_FLOAT:
          p2 = EnvAddDouble( env, values[iter].as_float() );
          SetMFValue(p, mfi, p2);
          break;
      case TYPE_EXTERNAL_ADDRESS:
        p2 = EnvAddExternalAddress( env, values[iter].as_address(), EXTERNAL_ADDRESS );
	SetMFValue(p, mfi, p2);
	break;
        default:
          throw std::logic_error( "clipsmm::value_to_data_object: Unhandled data object type" );
      }
    }
    SetpType(clipsdo, MULTIFIELD);
    SetpValue(clipsdo, p);
    SetpDOBegin(clipsdo, 1);
    SetpDOEnd(clipsdo, values.size());
    return clipsdo;
  }

}
