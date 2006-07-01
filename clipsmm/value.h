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
#ifndef CLIPSVALUE_H
#define CLIPSVALUE_H

#include <clipsmm/valuebase.h>

namespace CLIPS {

/**
	@author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
 */
  template <typename T, unsigned short CLIPSType>
  class Value: public ValueBase {
    public:
      typedef std::tr1::shared_ptr<Value> pointer;
      typedef T value_type;

      /** Default constructor that doesn't do much. */
      Value () { }

      /** Initializing constructor */
      Value( const T& value ) : m_value( value ) { }

      static pointer create() {
        return std::tr1::shared_ptr<Value>( new Value() );
      }

      static pointer create( const T& value ) {
        return std::tr1::shared_ptr<Value>( new Value(value) );
      }

      static pointer pointer_cast( ValueBase::pointer p ) {
        return std::tr1::dynamic_pointer_cast<Value<T,CLIPSType> >( p );
      }
      
      /** Destructor */
      virtual ~Value() { }

      /** The canonical get() accessor method. */
      virtual T get() const { return m_value; }

      /**
       * Returns a raw pointer to the underlying storage value.
       * Note that using this method breaks encapsulation. Changing the
       * underlying value through this pointer will not emit the
       * changed signal.
       */
      virtual T* get_pointer() {
        return & m_value;
      }

      /** The canonical set() accessor method that also emits the changed signal. */
      virtual void set( const T& val ) {
        m_value = val;
        m_signal_changed.emit();
      }

      /** Allows for implicit casts to the contained type. */
      operator T () const { return this->get(); }

      /** Function call syntax to get the value with var() notation. */
      T& operator() () const { return this->get(); }

      /** Function call syntax to set the value with var(value) notation. */
      Value<T,CLIPSType>& operator() ( const T& val ) {
        this->set( val );
        return *this;
      }

      /**
       * A convenience operator when the value template type is a class.
       *
       * Allows class method to be accessed using notation var->class_method()
       */
      T* operator->() {
        return get_pointer();
      }

      /** Returns the RTTI type id of the contained type */
      const std::type_info& type() const { return typeid( T ); }

      /**
       * Returns the size in bytes of the contained type,
       * and not necessarily the size of this class.
       */
      size_t size() const { return sizeof( T ); }

      /** Allows assignment to the property from the contained value type. */
      Value<T,CLIPSType>& operator= ( const T& val ) {
        this->set( val );
        return *this;
      }

      /**
       * Arithmetic assignment operator
       *
       * This method is implemented as a template for two reasons:
       *  - So that it will work with a variety of operands
       *  - So that a stub will not be generated if the operator is not defined for T
       *
       * T + X must be well defined
       */
      template <typename X>
      Value<T,CLIPSType>& operator+=( X other ) {
        this->set( this->get() + other );
        return *this;
      }

      /**
       * Arithmetic assignment operator
       *
       * This method is implemented as a template for two reasons:
       *  - So that it will work with a variety of operands
       *  - So that a stub will not be generated if the operator is not defined for T
       *
       * T - X must be well defined
       */
      template <typename X>
      Value<T,CLIPSType>& operator-=( X other ) {
        this->set( this->get() - other );
        return *this;
      }

      /**
       * Arithmetic assignment operator
       *
       * This method is implemented as a template for two reasons:
       *  - So that it will work with a variety of operands
       *  - So that a stub will not be generated if the operator is not defined for T
       *
       * T * X must be well defined
       */
      template <typename X>
      Value<T,CLIPSType>& operator*=( X other ) {
        this->set( this->get() * other );
        return *this;
      }

      /**
       * Arithmetic assignment operator
       *
       * This method is implemented as a template for two reasons:
       *  - So that it will work with a variety of operands
       *  - So that a stub will not be generated if the operator is not defined for T
       *
       * T / X must be well defined
       */
      template <typename X>
      Value<T,CLIPSType>& operator/=( X other ) {
        this->set( this->get() / other );
        return *this;
      }

      /**
       * Arithmetic assignment operator
       *
       * This method is implemented as a template for two reasons:
       *  - So that it will work with a variety of operands
       *  - So that a stub will not be generated if the operator is not defined for T
       *
       * T % X must be well defined
       */
      template <typename X>
      Value<T,CLIPSType>& operator%=( X other ) {
        this->set( this->get() % other );
        return *this;
      }

      /** Returns the CLIPS library type of this value */
      virtual int clips_type() {
        return CLIPSType;
      }

    protected:
      T m_value;
  };

  typedef Value<double,      0> Float;
  typedef Value<long int,    1> Integer;
  typedef Value<std::string, 2> Symbol;
  typedef Value<std::string, 3> String;
  typedef Value<void*,       5> ExternalAddress;
  typedef Value<void*,       7> InstanceAddress;
  typedef Value<std::string, 8> InstanceName;

}

#endif
