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
#include "value.h"

#include <stdexcept>

namespace CLIPS {

      Value::Value(): m_value(NULL) {
        this->set_type( TYPE_UNKNOWN );
      }

      Value::Value(Type type): m_value(NULL) {
        this->set_type( type );
      }

      Value::Value( float x ): m_value(NULL) {
        this->set_type( TYPE_FLOAT );
        this->set(x);
      }
      
      Value::Value( double x ): m_value(NULL) {
        this->set_type( TYPE_FLOAT );
        this->set(x);
      }
      
      Value::Value( short int x ): m_value(NULL) {
        this->set_type( TYPE_INTEGER );
        this->set(x);
      }
      
      Value::Value( unsigned short int x ): m_value(NULL) {
        this->set_type( TYPE_INTEGER );
        this->set(x);
      }
      
      Value::Value( int x ): m_value(NULL) {
        this->set_type( TYPE_INTEGER );
        this->set(x);
      }
      
      Value::Value( unsigned int x ): m_value(NULL) {
        this->set_type( TYPE_INTEGER );
        this->set(x);
      }
      
      Value::Value( long int x ): m_value(NULL) {
        this->set_type( TYPE_INTEGER );
        this->set(x);
      }

      Value::Value( long long int x ): m_value(NULL) {
        this->set_type( TYPE_INTEGER );
        this->set(x);
      }
      
      Value::Value( const char* x, Type type ): m_value(NULL) {
        this->set_type( type );
        this->set(x);
      }
      
      Value::Value( const std::string& x, Type type ): m_value(NULL) {
        this->set_type( type );
        this->set(x);
      }
      
      Value::Value( void* x, Type type ): m_value(NULL) {
        this->set_type( type );
        this->set(x);
      }

      Value::Value( const Value& value): m_value(NULL) {
        this->operator=(value);
      }
      
      Value::~Value() {
        deallocate_storage();
      }
      
      double Value::as_float() const {
        switch ( m_clips_type ) {
          case TYPE_FLOAT:
            return *static_cast<double*>(m_value);
          case TYPE_INTEGER:
            return *static_cast<long long int*>(m_value);
          default:
            throw std::logic_error("Invalid get_float() of non-float value");
        }
      }

      long long int Value::as_integer() const {
        switch ( m_clips_type ) {
          case TYPE_FLOAT:
            return static_cast<long long int>(*static_cast<double*>(m_value));
          case TYPE_INTEGER:
            return *static_cast<long long int*>(m_value);
          default:
            throw std::logic_error("Invalid get_float() of non-float value");
        }
      }

      std::string& Value::as_string() const {
        switch ( m_clips_type ) {
          case TYPE_STRING:
          case TYPE_SYMBOL:
          case TYPE_INSTANCE_NAME:
            return *static_cast<std::string*>(m_value);
          default:
            throw std::logic_error("Invalid get_string() of non-string value");
        }
      }

      void* Value::as_address() const {
        switch ( m_clips_type ) {
          case TYPE_EXTERNAL_ADDRESS:
            return m_value;
          case TYPE_INSTANCE_ADDRESS:
            return *static_cast<int**>(m_value);
          default:
            throw std::logic_error("Invalid get_address() of non-address value");
        }
      }

      Value& Value::set( float x, bool change_type ) {
        return this->set( static_cast<double>(x), change_type );
      }
      
      Value& Value::set( double x, bool change_type ) {
        if (change_type)
          this->set_type( TYPE_FLOAT );
        if ( m_clips_type == TYPE_INTEGER )
          return this->set( static_cast<long long int>(x) );
        if ( m_clips_type != TYPE_FLOAT )
          throw std::logic_error("Invalid set( double x ) on non-float value");
        *static_cast<double*>(m_value) = x;
        m_signal_changed.emit();
        return *this;
      }
      
      Value& Value::set( short int x, bool change_type ) {
        return this->set( static_cast<long long int>(x), change_type );
      }
      
      Value& Value::set( unsigned short int x, bool change_type ) {
        return this->set( static_cast<long long int>(x), change_type );
      }
      
      Value& Value::set( int x, bool change_type ) {
        return this->set( static_cast<long long int>(x), change_type );
      }
      
      Value& Value::set( unsigned int x, bool change_type ) {
        return this->set( static_cast<long long int>(x), change_type );
      }

      Value& Value::set( long int x, bool change_type ) {
        return this->set( static_cast<long long int>(x), change_type );
      }
      
      Value& Value::set( long long int x, bool change_type ) {
        if (change_type)
          this->set_type( TYPE_INTEGER );
        if ( m_clips_type == TYPE_FLOAT )
          return this->set( static_cast<double>(x) );
        if ( m_clips_type != TYPE_INTEGER )
          throw std::logic_error("Invalid set(long long int x) on non-integer value");
        *static_cast<long long int*>(m_value) = x;
        m_signal_changed.emit();
        return *this;
      }
      
      Value& Value::set( const std::string& x, bool change_type, Type type ) {
        if ( change_type )
          this->set_type( type );
        if ( ! ( m_clips_type == TYPE_STRING ||
                 m_clips_type == TYPE_SYMBOL ||
                 m_clips_type == TYPE_INSTANCE_NAME ) )
          throw std::logic_error("Invalid set( std::string x ) on non-string value");
        *static_cast<std::string*>(m_value) = x;
        m_signal_changed.emit();
        return *this;
      }
      
      Value& Value::set( const char* x, bool change_type, Type type ) {
        std::string s = x;
        return this->set( s, change_type, type );
      }

      Value& Value::set( void* x, bool change_type, Type type ) {
        if ( change_type )
          this->set_type( type );
        if ( ! ( m_clips_type == TYPE_EXTERNAL_ADDRESS ||
                 m_clips_type == TYPE_INSTANCE_ADDRESS ) )
          throw std::logic_error("Invalid set( void* x ) on non-address value");
	if (m_clips_type == TYPE_EXTERNAL_ADDRESS) {
	  m_value = x;
	} else {
          *static_cast<int**>(m_value) = static_cast<int*>(x);
	}
        m_signal_changed.emit();
        return *this;
      }
      
      Value::operator float( ) const {
        return this->as_float();
      }
      
      Value::operator double( ) const {
        return this->as_float();
      }
      
      Value::operator short int( ) const {
        return this->as_integer();
      }
      
      Value::operator unsigned short int( ) const {
        return this->as_integer();
      }
      
      Value::operator int( ) const {
        return this->as_integer();
      }
      
      Value::operator unsigned int( ) const {
        return this->as_integer();
      }
      
      Value::operator long int( ) const {
        return this->as_integer();
      }

      Value::operator long long int( ) const {
        return this->as_integer();
      }
      
      Value::operator std::string&( ) const {
        return this->as_string();
      }
      
      Value::operator const char*( ) const {
        return this->as_string().c_str();
      }
      
      Value::operator void*( ) const {
        return this->as_address();
      }

      size_t Value::size() const {
        switch ( m_clips_type ) {
          case TYPE_FLOAT:
            return sizeof(double);
          case TYPE_INTEGER:
            return sizeof(long long int);
          case TYPE_SYMBOL:
          case TYPE_STRING:
          case TYPE_INSTANCE_NAME:
            return sizeof( *static_cast<std::string*>(m_value) );
          case TYPE_EXTERNAL_ADDRESS:
            return sizeof(void*);

          case TYPE_INSTANCE_ADDRESS:
            return sizeof(int*);
        }
        return 0;
      }
      
      Value& Value::operator=( float x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( double x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( short int x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( unsigned short int x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( int x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( unsigned int x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( long int x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( long long int x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( const std::string& x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( const char* x ) {
        return this->set(x);
      }
      
      Value& Value::operator=( void* x ) {
        return this->set(x);
      }

      Value& Value::operator=( const Value& x ) {
        this->set_type( x.m_clips_type );
        switch ( m_clips_type ) {
          case TYPE_FLOAT:
            *static_cast<double*>(m_value) = *static_cast<double*>(x.m_value);
            break;
          case TYPE_INTEGER:
            *static_cast<long long int*>(m_value) =
	      *static_cast<long long int*>(x.m_value);
            break;
          case TYPE_SYMBOL:
          case TYPE_STRING:
          case TYPE_INSTANCE_NAME:
            *static_cast<std::string*>(m_value) = *static_cast<std::string*>(x.m_value);
            break;
          case TYPE_EXTERNAL_ADDRESS:
	    m_value = x.m_value;

          case TYPE_INSTANCE_ADDRESS:
            *static_cast<int**>(m_value) = *static_cast<int**>(x.m_value);
            break;
        }
        return *this;
      }

      bool Value::operator==( float x ) const {
        return this->as_float() == x;
      }
      
      bool Value::operator==( double x ) const {
        return this->as_float() == x;
      }
      
      bool Value::operator==( short int x ) const {
        return this->as_integer() == x;
      }
      
      bool Value::operator==( unsigned short int x ) const {
        return this->as_integer() == x;
      }

      bool Value::operator==( int x ) const {
        return this->as_integer() == x;
      }

      bool Value::operator==( unsigned int x ) const {
        return this->as_integer() == x;
      }

      bool Value::operator==( long int x ) const {
        return this->as_integer() == x;
      }

      bool Value::operator==( long long int x ) const {
        return this->as_integer() == x;
      }

      bool Value::operator==( const std::string& x ) const {
        return this->as_string() == x;
      }
      
      bool Value::operator==( const char* x ) const {
        return this->as_string() == x;
      }
      
      bool Value::operator==( void* x ) const {
        return this->as_address() == x;
      }

      bool Value::operator!=( float x ) const {
        return this->as_float() != x;
      }
      
      bool Value::operator!=( double x ) const {
        return this->as_float() != x;
      }
      
      bool Value::operator!=( short int x ) const {
        return this->as_integer() != x;
      }
      
      bool Value::operator!=( unsigned short int x ) const {
        return this->as_integer() != x;
      }
      
      bool Value::operator!=( int x ) const {
        return this->as_integer() != x;
      }
      
      bool Value::operator!=( unsigned int x ) const {
        return this->as_integer() != x;
      }
      
      bool Value::operator!=( long int x ) const {
        return this->as_integer() != x;
      }
      
      bool Value::operator!=( long long int x ) const {
        return this->as_integer() != x;
      }
      
      bool Value::operator!=( const std::string& x ) const {
        return this->as_string() != x;
      }
      
      bool Value::operator!=( const char* x ) const {
        return this->as_string() != x;
      }
      
      bool Value::operator!=( void* x ) const {
        return this->as_address() != x;
      }

      Type Value::type() const {
        return m_clips_type;
      }

      Type Value::set_type(Type type) {
        if (m_value)
          deallocate_storage();

        m_clips_type = type;
        switch (type) {
          case TYPE_FLOAT:
            m_value = new double;
            break;
          case TYPE_INTEGER:
            m_value = new long long int;
            break;
          case TYPE_SYMBOL:
          case TYPE_STRING:
          case TYPE_INSTANCE_NAME:
            m_value = new std::string;
            break;
          case TYPE_EXTERNAL_ADDRESS:
	    m_value = NULL;
	    break;
          case TYPE_INSTANCE_ADDRESS:
            m_value = new int*;
            break;
        }        
        return m_clips_type;
      }

      sigc::signal<void> Value::signal_changed() {
        return m_signal_changed;
      }

      void Value::deallocate_storage() {
        if (!m_value)
          return;
        switch (m_clips_type) {
          case TYPE_FLOAT:
            delete static_cast<double*>(m_value);
            break;
          case TYPE_INTEGER:
            delete static_cast<long long int*>(m_value);
            break;
          case TYPE_SYMBOL:
          case TYPE_STRING:
          case TYPE_INSTANCE_NAME:
            delete static_cast<std::string*>(m_value);
            break;
          case TYPE_EXTERNAL_ADDRESS:
	    m_value = NULL;
	    break;

          case TYPE_INSTANCE_ADDRESS:
            delete static_cast<int**>(m_value);
            break;
        }
        m_value = NULL;
      }

}
