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
#ifndef FUNCTIONTEST_H
#define FUNCTIONTEST_H

#include <cppunit/TestFixture.h>

#include <clipsmm/clipsmm.h>
#include <clips/clips.h>

#include <sstream>
#include <cstdlib>

using namespace CLIPS;

class FunctionTest : public  CppUnit::TestFixture {
  public:

    CPPUNIT_TEST_SUITE( FunctionTest );
    CPPUNIT_TEST( expression_test_1 );
    CPPUNIT_TEST( expression_test_2 );
    CPPUNIT_TEST( builtin_function_test_1 );
    CPPUNIT_TEST( builtin_function_test_2 );
    CPPUNIT_TEST( class_method_test_0 );
    CPPUNIT_TEST( class_method_test_1 );
  CPPUNIT_TEST( class_method_test_2 );
  CPPUNIT_TEST( class_method_test_3 );
  CPPUNIT_TEST( class_method_test_5 );
  CPPUNIT_TEST( class_method_test_6 );
  CPPUNIT_TEST( class_method_test_7 );
  CPPUNIT_TEST_SUITE_END();

  protected:
    CLIPS::Environment environment;
    int temp_class_int;

  public:
    void setUp() {
      temp_class_int = 0;
    }

    void tearDown() { }

    void expression_test_1() {
      Values values = environment.evaluate( "(+ 3 4)" );
      CPPUNIT_ASSERT( values.size() == 1 );
      CPPUNIT_ASSERT( values[0] == (3+4) );
    }

  void expression_test_2() {
    Values values = environment.evaluate( "(- (+ 3 4) 2)" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == ((3+4)-2) );
  }

  void builtin_function_test_1() {
    Values values = environment.function( "+", "3 4");
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (3+4) );
  }

  void builtin_function_test_2() {
    Values values = environment.function( "-", "4 2");
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (4-2) );
  }

  void class_fun0() { temp_class_int = 42; }

  void class_method_test_0() {
    CPPUNIT_ASSERT( temp_class_int == 0 );
    environment.add_function( "class_fun0", sigc::slot<void>(sigc::mem_fun( *this, &FunctionTest::class_fun0 )) );
    environment.function( "class_fun0" );
    CPPUNIT_ASSERT( temp_class_int == 42 );
  }

  int class_fun1(double d) { return (int)(d+42); }

  void class_method_test_1() {
    environment.add_function( "class_fun1", sigc::slot<int,double>(sigc::mem_fun( *this, &FunctionTest::class_fun1 )) );
    Values values = environment.function( "class_fun1", "38.8" );
    // Only 38 is used to keep the function at an integer value
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == 38+42 );
  }

  double class_fun2(int i, double d) { return i+d; }

  void class_method_test_2() {
    environment.add_function( "class_fun2", sigc::slot<double,int,double>(sigc::mem_fun( *this, &FunctionTest::class_fun2 )) );
    Values values = environment.function( "class_fun2", "42 38.8" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == 42+38.8 );
  }

  std::string class_fun3(std::string s1, std::string s2) { return s1+s2; }

  void class_method_test_3() {
    environment.add_function( "class_fun3", sigc::slot<std::string,std::string,std::string>(sigc::mem_fun( *this, &FunctionTest::class_fun3 )) );
    Values values = environment.function( "class_fun3", "hello world" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == "helloworld" );
  }

  std::string class_fun4(int i, double d, std::string s1, float f) {
    std::ostringstream sout;
    sout << i << " " << d << s1 << f;
    return sout.str();
  }

  int class_fun5(int i, double d, std::string s2, long l, float f) {
    int t;
    std::istringstream sin(s2.substr(1,std::string::npos));
    sin >> t;
    return i+d+t+l+f;
  }

  void class_method_test_5() {
    environment.add_function( "class_fun5", sigc::slot<int,int,double,std::string,long,float>(sigc::mem_fun( *this, &FunctionTest::class_fun5 )) );
    Values values = environment.function( "class_fun5", "3 3.8 c4 2 1.3" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (int)(3+3.8+4+2+1.3) );
  }

  long class_fun6(int i1, long l1, double d, float f, int i2, long l2) {
    return (long)(i1+l1+d+f+i2+l2);
  }

  void class_method_test_6() {
    environment.add_function( "class_fun6", sigc::slot<long,int,long,double,float,int,long>(sigc::mem_fun( *this, &FunctionTest::class_fun6 )) );
    Values values = environment.function( "class_fun6", "3 56 3.8 1.3 42 192" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (long)(3+56+3.8+1.3+42+192) );
  }

  float class_fun7(int i1, long l1, double d1, float f, int i2, long l2, double d2) {
    CPPUNIT_ASSERT( i1 == 3 );
    CPPUNIT_ASSERT( l1 == 56l );
    CPPUNIT_ASSERT( d1 == 3.8 );
    CPPUNIT_ASSERT( f  == 1.3f );
    CPPUNIT_ASSERT( i2 == 42 );
    CPPUNIT_ASSERT( l2 == 192l );
    CPPUNIT_ASSERT( d2 == 28.444 );
    return i1+l1+d1+f+i2+l2+d2;
  }

  void class_method_test_7() {
    environment.add_function( "class_fun7", sigc::slot<float,int,long,double,float,int,long,double>(sigc::mem_fun( *this, &FunctionTest::class_fun7 )) );
    Values values = environment.function( "class_fun7", "3 56 3.8 1.3 42 192 28.444" );
  std::cout << "Value: " << (float)values[0] << std::endl;
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (float)(3+56l+3.8+1.3f+42+192l+28.444) );
  }


};

#endif
