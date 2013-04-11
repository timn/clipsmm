/***************************************************************************
 *   Copyright (C) 2006  Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>       *
 *   Copyright (C) 2013  Tim Niemueller [www.niemueller.de]                *
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
#ifndef CLIPSVALUE_H
#define CLIPSVALUE_H

#include <string>
#include <vector>

#include <sigc++/sigc++.h>

namespace CLIPS {

typedef enum Type {
  TYPE_UNKNOWN = -1,
  TYPE_FLOAT = 0,
  TYPE_INTEGER = 1,
  TYPE_SYMBOL = 2,
  TYPE_STRING = 3,
  TYPE_EXTERNAL_ADDRESS = 5,
  TYPE_INSTANCE_ADDRESS = 7,
  TYPE_INSTANCE_NAME = 8,
} Type;

/**
 * @author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
 * @author Tim Niemueller <tim@niemueller.de>
 */  
class Value: public sigc::trackable {
 public:

  /** Typeless constructor */
  Value ();

  /** Type constructor */
  Value (Type type);

  /** Constructor sets value and CLIPS type to FLOAT */
  Value( float x );

  /** Constructor sets value and CLIPS type to FLOAT */
  Value( double x );

  /** Constructor sets value and CLIPS type to INTEGER */
  Value( short int x );

  /** Constructor sets value and CLIPS type to INTEGER */
  Value( unsigned short int x );

  /** Constructor sets value and CLIPS type to INTEGER */
  Value( int x );

  /** Constructor sets value and CLIPS type to INTEGER */
  Value( unsigned int x );

  /** Constructor sets value and CLIPS type to INTEGER */
  Value( long int x );

  /** Constructor sets value and CLIPS type to INTEGER */
  Value( long long int x );

  /** Constructor sets value and CLIPS type */
  Value( const char* x, Type type=TYPE_STRING );

  /** Constructor sets value and CLIPS type */
  Value( const std::string& x, Type type=TYPE_STRING );
      
  /** Constructor sets value and CLIPS type to */
  Value( void* x, Type type=TYPE_EXTERNAL_ADDRESS );

  Value( const Value& value );

  /** Destructor */
  ~Value();

  double as_float() const;
  long long int as_integer() const;
  std::string& as_string() const;
  void* as_address() const;

  Value& set( float x, bool change_type=false );
  Value& set( double x, bool change_type=false  );
  Value& set( short int x, bool change_type=false  );
  Value& set( unsigned short int x, bool change_type=false  );
  Value& set( int x, bool change_type=false  );
  Value& set( unsigned int x, bool change_type=false  );
  Value& set( long int x, bool change_type=false  );
  Value& set( long long int x, bool change_type=false  );
  Value& set( const std::string& x, bool change_type=false, Type type=TYPE_STRING );
  Value& set( const char* x, bool change_type=false, Type type=TYPE_STRING );
  Value& set( void* x, bool change_type=false, Type type=TYPE_EXTERNAL_ADDRESS  );
      
  operator float( ) const;
  operator double( ) const;
  operator short int( ) const;
  operator unsigned short int( ) const;
  operator int( ) const;
  operator unsigned int( ) const;
  operator long int( ) const;
  operator long long int( ) const;
  operator std::string&( ) const;
  operator const char*( ) const;
  operator void*( ) const;

  /** Function call syntax to get the value with var() notation. */
  //       T& operator() () const { return this->get(); }

  /** Function call syntax to set the value with var(value) notation. */
  //       Value<T,CLIPSType>& operator() ( const T& val ) {
  //         this->set( val );
  //         return *this;
  //       }

  /** Returns the RTTI type id of the contained type */
  //       const std::type_info& type_info() const { return typeid( T ); }

  /**
   * Returns the size in bytes of the contained type,
   * and not necessarily the size of this class.
   */
  size_t size() const;

  /** Allows assignment to the property from the contained value type. */
  //       Value<T,CLIPSType>& operator= ( const T& val ) {
  //         this->set( val );
  //         return *this;
  //       }

  Value& operator=( float x );
  Value& operator=( double x );
  Value& operator=( short int x );
  Value& operator=( unsigned short int x );
  Value& operator=( int x );
  Value& operator=( unsigned int x );
  Value& operator=( long int x );
  Value& operator=( long long int x );
  Value& operator=( const std::string& x );
  Value& operator=( const char* x );
  Value& operator=( void* x );
  Value& operator=( const Value& x );
      
  bool operator==( float x ) const;
  bool operator==( double x ) const;
  bool operator==( short int x ) const;
  bool operator==( unsigned short int x ) const;
  bool operator==( int x ) const;
  bool operator==( unsigned int x ) const;
  bool operator==( long int x ) const;
  bool operator==( long long int x ) const;
  bool operator==( const std::string& x ) const;
  bool operator==( const char* x ) const;
  bool operator==( void* x ) const;

  bool operator!=( float x ) const;
  bool operator!=( double x ) const;
  bool operator!=( short int x ) const;
  bool operator!=( unsigned short int x ) const;
  bool operator!=( int x ) const;
  bool operator!=( unsigned int x ) const;
  bool operator!=( long int x ) const;
  bool operator!=( long long int x ) const;
  bool operator!=( const std::string& x ) const;
  bool operator!=( const char* x ) const;
  bool operator!=( void* x ) const;

  /**
   * Arithmetic assignment operator
   *
   * This method is implemented as a template for two reasons:
   *  - So that it will work with a variety of operands
   *  - So that a stub will not be generated if the operator is not defined for T
   *
   * T + X must be well defined
   */
  //       template <typename X>
  //       Value& operator+=( X other ) {
  //         this->set( this->get() + other );
  //         return *this;
  //       }

  /**
   * Arithmetic assignment operator
   *
   * This method is implemented as a template for two reasons:
   *  - So that it will work with a variety of operands
   *  - So that a stub will not be generated if the operator is not defined for T
   *
   * T - X must be well defined
   */
  //       template <typename X>
  //       Value& operator-=( X other ) {
  //         this->set( this->get() - other );
  //         return *this;
  //       }

  /**
   * Arithmetic assignment operator
   *
   * This method is implemented as a template for two reasons:
   *  - So that it will work with a variety of operands
   *  - So that a stub will not be generated if the operator is not defined for T
   *
   * T * X must be well defined
   */
  //       template <typename X>
  //       Value& operator*=( X other ) {
  //         this->set( this->get() * other );
  //         return *this;
  //       }

  /**
   * Arithmetic assignment operator
   *
   * This method is implemented as a template for two reasons:
   *  - So that it will work with a variety of operands
   *  - So that a stub will not be generated if the operator is not defined for T
   *
   * T / X must be well defined
   */
  //       template <typename X>
  //       Value& operator/=( X other ) {
  //         this->set( this->get() / other );
  //         return *this;
  //       }

  /**
   * Arithmetic assignment operator
   *
   * This method is implemented as a template for two reasons:
   *  - So that it will work with a variety of operands
   *  - So that a stub will not be generated if the operator is not defined for T
   *
   * T % X must be well defined
   */
  //       template <typename X>
  //       Value& operator%=( X other ) {
  //         this->set( this->get() % other );
  //         return *this;
  //       }

  /** Returns the CLIPS library type of this value */
  Type type() const;

  /** Sets the underlying storage type */
  Type set_type( Type type );

  /** Signal emitted when the value is changed. */
  sigc::signal<void> signal_changed();

 protected:
  /** Storage for the underlying value */
  void* m_value;

  /** Stores the CLIPS type information */
  Type m_clips_type;
      
  /** Signal emitted when underlying data is changed. */
  sigc::signal<void> m_signal_changed;

  void deallocate_storage();
};

 typedef std::vector<Value> Values;

}

#endif
