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
#ifndef VALUETEST_H
#define VALUETEST_H

#include <cppunit/TestFixture.h>

#include <clipsmm.h>

using namespace CLIPS;

class ValueTest : public CppUnit::TestFixture {
  public:

    CPPUNIT_TEST_SUITE( ValueTest );
    CPPUNIT_TEST( value_create_and_compare_float );
    CPPUNIT_TEST( value_create_and_compare_double );
    CPPUNIT_TEST( value_create_and_compare_short_int );
    CPPUNIT_TEST( value_create_and_compare_short_unsigned_int );
    CPPUNIT_TEST( value_create_and_compare_int );
    CPPUNIT_TEST( value_create_and_compare_unsigned_int );
    CPPUNIT_TEST( value_create_and_compare_long_int );
    CPPUNIT_TEST( value_create_and_compare_string );
    CPPUNIT_TEST( value_create_and_compare_cstring );
    CPPUNIT_TEST( value_create_and_compare_address );
    CPPUNIT_TEST( value_assignment_float );
    CPPUNIT_TEST( value_assignment_double );
    CPPUNIT_TEST( value_assignment_short_int );
    CPPUNIT_TEST( value_assignment_short_unsigned_int );
    CPPUNIT_TEST( value_assignment_int );
    CPPUNIT_TEST( value_assignment_unsigned_int );
    CPPUNIT_TEST( value_assignment_long_int );
    CPPUNIT_TEST( value_assignment_string );
    CPPUNIT_TEST( value_assignment_cstring );
    CPPUNIT_TEST( value_assignment_address );
    CPPUNIT_TEST( value_change_type );
    CPPUNIT_TEST_SUITE_END();

  protected:
    CLIPS::Environment environment;
    
  public:
    void setUp() {
    }

    void tearDown() { }

    template <typename T, typename U>
    bool test_create_and_compare_equal( T x, U y ) {
      Value v(x);
      return v == y;
    }
    
    template <typename T, typename U>
    bool test_create_and_compare_inequal( T x, U y ) {
      Value v(x);
      return v != y;
    }
    
    void value_create_and_compare_float() {
      CPPUNIT_ASSERT( test_create_and_compare_equal( 3.3f, 3.3f ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( 3.3f, 3.4f ) );
    }

    void value_create_and_compare_double() {
      CPPUNIT_ASSERT( test_create_and_compare_equal( 3.3, 3.3 ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( 3.3, 3.4 ) );
    }

    void value_create_and_compare_short_int() {
      CPPUNIT_ASSERT( test_create_and_compare_equal( (short)3, (short)3 ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( (short)3, (short)4 ) );
    }

    void value_create_and_compare_short_unsigned_int() {
      CPPUNIT_ASSERT( test_create_and_compare_equal( (unsigned short)3, (unsigned short)3 ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( (unsigned short)3, (unsigned short)4 ) );
    }

    void value_create_and_compare_int() {
      CPPUNIT_ASSERT( test_create_and_compare_equal( 3, 3 ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( 3, 4 ) );
    }

    void value_create_and_compare_unsigned_int() {
      CPPUNIT_ASSERT( test_create_and_compare_equal( 3U, 3U ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( 3U, 4U ) );
    }

    void value_create_and_compare_long_int() {
      CPPUNIT_ASSERT( test_create_and_compare_equal( 3L, 3L ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( 3L, 4L ) );
    }

    void value_create_and_compare_string() {
      std::string x("one"), y("one"), z("two");
      CPPUNIT_ASSERT( test_create_and_compare_equal( x, y ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( x, z ) );
    }

    void value_create_and_compare_cstring() {
      CPPUNIT_ASSERT( test_create_and_compare_equal( "one", "one" ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( "one", "two" ) );
    }

    void value_create_and_compare_address() {
      double d1=3.3, d2=3.3;
      double *p1=&d1, *p2=&d1, *p3=&d2;
      CPPUNIT_ASSERT( test_create_and_compare_equal( p1, p2 ) );
      CPPUNIT_ASSERT( test_create_and_compare_inequal( p1, p3 ) );
    }

    void value_assignment_float() {
      Value v(3.3f);
      CPPUNIT_ASSERT( ( v = 3.5f ) == 3.5f );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = 3.5 ) == 3.5 );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = (short)3 ) == (short)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = (short unsigned)3 ) == (short unsigned)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = 3 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = 3U ) == 3U );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = 3L ) == 3L );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
    }

    void value_assignment_double() {
      Value v(3.3);
      CPPUNIT_ASSERT( ( v = 3.5f ) == 3.5f );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = 3.5 ) == 3.5 );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = (short)3 ) == (short)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = (short unsigned)3 ) == (short unsigned)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = 3 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = 3U ) == 3U );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( ( v = 3L ) == 3L );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
    }

    void value_assignment_short_int() {
      Value v((short)3);
      CPPUNIT_ASSERT( ( v = 3.5f ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3.5 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short)3 ) == (short)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short unsigned)3 ) == (short unsigned)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3U ) == 3U );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3L ) == 3L );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
    }

    void value_assignment_short_unsigned_int() {
      Value v((short unsigned)3);
      CPPUNIT_ASSERT( ( v = 3.5f ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3.5 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short)3 ) == (short)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short unsigned)3 ) == (short unsigned)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3U ) == 3U );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3L ) == 3L );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
    }

    void value_assignment_int() {
      Value v(3);
      CPPUNIT_ASSERT( ( v = 3.5f ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3.5 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short)3 ) == (short)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short unsigned)3 ) == (short unsigned)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3U ) == 3U );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3L ) == 3L );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
    }

    void value_assignment_unsigned_int() {
      Value v(3U);
      CPPUNIT_ASSERT( ( v = 3.5f ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3.5 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short)3 ) == (short)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short unsigned)3 ) == (short unsigned)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3U ) == 3U );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3L ) == 3L );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
    }

    void value_assignment_long_int() {
      Value v(3L);
      CPPUNIT_ASSERT( ( v = 3.5f ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3.5 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short)3 ) == (short)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = (short unsigned)3 ) == (short unsigned)3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3 ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3U ) == 3U );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( ( v = 3L ) == 3L );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
    }

    void value_assignment_string() {
      Value v(std::string("one"));
      CPPUNIT_ASSERT( ( v = std::string("two") ) == std::string("two") );
      CPPUNIT_ASSERT( v.type() == TYPE_STRING );
      CPPUNIT_ASSERT( ( v = "two" ) == "two" );
      CPPUNIT_ASSERT( v.type() == TYPE_STRING );
    }

    void value_assignment_cstring() {
      Value v("one");
      CPPUNIT_ASSERT( ( v = std::string("two") ) == std::string("two") );
      CPPUNIT_ASSERT( v.type() == TYPE_STRING );
      CPPUNIT_ASSERT( ( v = "two" ) == "two" );
      CPPUNIT_ASSERT( v.type() == TYPE_STRING );
    }

    void value_assignment_address() {
      double d=3.3;
      double *p;
      Value v(TYPE_EXTERNAL_ADDRESS);
      CPPUNIT_ASSERT( ( v = &d ) == &d );
      p = (double*)(void*)v;
      CPPUNIT_ASSERT( *p == 3.3 );
    }

    void value_change_type() {
      Value v(TYPE_STRING);
      CPPUNIT_ASSERT( v.set(3.5f, true) == 3.5f );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( v.set(3.6, true) == 3.6 );
      CPPUNIT_ASSERT( v.type() == TYPE_FLOAT );
      CPPUNIT_ASSERT( v.set( (short)4, true ) == (short)4 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( v.set( (short unsigned)5, true ) == (short unsigned)5 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( v.set( 3, true ) == 3 );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( v.set( 3U, true ) == 3U );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( v.set( 3L, true ) == 3L );
      CPPUNIT_ASSERT( v.type() == TYPE_INTEGER );
      CPPUNIT_ASSERT( v.set( std::string("two"), true, TYPE_STRING ) == std::string("two") );
      CPPUNIT_ASSERT( v.type() == TYPE_STRING );
      CPPUNIT_ASSERT( v.set( "three", true, TYPE_STRING ) == "three" );
      CPPUNIT_ASSERT( v.type() == TYPE_STRING );
      CPPUNIT_ASSERT( v.set( std::string("four"), true, TYPE_SYMBOL ) == std::string("four") );
      CPPUNIT_ASSERT( v.type() == TYPE_SYMBOL );
      CPPUNIT_ASSERT( v.set( "five", true, TYPE_SYMBOL ) == "five" );
      CPPUNIT_ASSERT( v.type() == TYPE_SYMBOL );
      CPPUNIT_ASSERT( v.set( std::string("six"), true, TYPE_INSTANCE_NAME ) == std::string("six") );
      CPPUNIT_ASSERT( v.type() == TYPE_INSTANCE_NAME );
      CPPUNIT_ASSERT( v.set( "seven", true, TYPE_INSTANCE_NAME ) == "seven" );
      CPPUNIT_ASSERT( v.type() == TYPE_INSTANCE_NAME );
    }

};

#endif
