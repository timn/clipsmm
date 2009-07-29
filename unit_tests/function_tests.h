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
#ifndef FUNCTIONTEST_H
#define FUNCTIONTEST_H

#include <cppunit/TestFixture.h>

#include <clipsmm.h>
#include <clips/clips.h>

#include <sstream>
#include <cstdlib>

using namespace CLIPS;

int global_int = 0;

void function0() { global_int = 42; }

int function1(double d) { return (int)(d+42); }

double function2(int i, double d) { return i+d; }

std::string function3(std::string s1, std::string s2) { return s1+s2; }

double function4(int i1, int i2, float f, double d) {
  return i1+i2+f+d;
}

int function5(int i, double d, std::string s2, long l, float f) {
  int t;
  std::istringstream sin(s2.substr(1,std::string::npos));
  sin >> t;
  return (int)(i+d+t+l+f);
}

long function6(int i1, long l1, double d, float f, int i2, long l2) {
  return (long)(i1+l1+d+f+i2+l2);
}

float function7(int i1, long l1, double d1, float f, int i2, long l2, double d2) {
  CPPUNIT_ASSERT( i1 == 3 );
  CPPUNIT_ASSERT( l1 == 56l );
  CPPUNIT_ASSERT( d1 == 3.8 );
  CPPUNIT_ASSERT( f  == 1.3f );
  CPPUNIT_ASSERT( i2 == 42 );
  CPPUNIT_ASSERT( l2 == 192l );
  CPPUNIT_ASSERT( d2 == 28.444 );
  return i1+l1+d1+f+i2+l2+d2;
}


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
  CPPUNIT_TEST( function_test_0 );
  CPPUNIT_TEST( function_test_1 );
  CPPUNIT_TEST( function_test_2 );
  CPPUNIT_TEST( function_test_3 );
  CPPUNIT_TEST( function_test_4 );
  CPPUNIT_TEST( function_test_5 );
  CPPUNIT_TEST( function_test_6 );
  CPPUNIT_TEST( function_test_7 );
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

  void class_method0() { temp_class_int = 42; }

  void class_method_test_0() {
    CPPUNIT_ASSERT( temp_class_int == 0 );
    environment.add_function( "class_method0", sigc::slot<void>(sigc::mem_fun( *this, &FunctionTest::class_method0 )) );
    environment.function( "class_method0" );
    CPPUNIT_ASSERT( temp_class_int == 42 );
  }

  int class_method1(double d) { return (int)(d+42); }

  void class_method_test_1() {
    environment.add_function( "class_method1", sigc::slot<int,double>(sigc::mem_fun( *this, &FunctionTest::class_method1 )) );
    Values values = environment.function( "class_method1", "38.8" );
    // Only 38 is used to keep the function at an integer value
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == 38+42 );
  }

  double class_method2(int i, double d) { return i+d; }

  void class_method_test_2() {
    environment.add_function( "class_method2", sigc::slot<double,int,double>(sigc::mem_fun( *this, &FunctionTest::class_method2 )) );
    Values values = environment.function( "class_method2", "42 38.8" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == 42+38.8 );
  }

  std::string class_method3(std::string s1, std::string s2) { return s1+s2; }

  void class_method_test_3() {
    environment.add_function( "class_method3", sigc::slot<std::string,std::string,std::string>(sigc::mem_fun( *this, &FunctionTest::class_method3 )) );
    Values values = environment.function( "class_method3", "hello world" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == "helloworld" );
  }

  std::string class_method4(int i, double d, std::string s1, float f) {
    std::ostringstream sout;
    sout << i << " " << d << s1 << f;
    return sout.str();
  }

  int class_method5(int i, double d, std::string s2, long l, float f) {
    int t;
    std::istringstream sin(s2.substr(1,std::string::npos));
    sin >> t;
    return (int)(i+d+t+l+f);
  }

  void class_method_test_5() {
    environment.add_function( "class_method5", sigc::slot<int,int,double,std::string,long,float>(sigc::mem_fun( *this, &FunctionTest::class_method5 )) );
    Values values = environment.function( "class_method5", "3 3.8 c4 2 1.3" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (int)(3+3.8+4+2+1.3) );
  }

  long class_method6(int i1, long l1, double d, float f, int i2, long l2) {
    return (long)(i1+l1+d+f+i2+l2);
  }

  void class_method_test_6() {
    environment.add_function( "class_method6", sigc::slot<long,int,long,double,float,int,long>(sigc::mem_fun( *this, &FunctionTest::class_method6 )) );
    Values values = environment.function( "class_method6", "3 56 3.8 1.3 42 192" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (long)(3+56+3.8+1.3+42+192) );
  }

  float class_method7(int i1, long l1, double d1, float f, int i2, long l2, double d2) {
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
    environment.add_function( "class_method7", sigc::slot<float,int,long,double,float,int,long,double>(sigc::mem_fun( *this, &FunctionTest::class_method7 )) );
    Values values = environment.function( "class_method7", "3 56 3.8 1.3 42 192 28.444" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (float)(3+56l+3.8+1.3f+42+192l+28.444) );
  }

  void function_test_0() {
    CPPUNIT_ASSERT( global_int == 0 );
    environment.add_function( "function0", sigc::slot<void>(sigc::ptr_fun( &function0 )) );
    environment.function( "function0" );
    CPPUNIT_ASSERT( global_int == 42 );
  }

  void function_test_1() {
    environment.add_function( "function1", sigc::slot<int,double>(sigc::ptr_fun( &function1 )) );
    Values values = environment.function( "function1", "38.8" );
    // Only 38 is used to keep the function at an integer value
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == 38+42 );
  }

  void function_test_2() {
    environment.add_function( "function2", sigc::slot<double,int,double>(sigc::ptr_fun( &function2 )) );
    Values values = environment.function( "function2", "42 38.8" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == 42+38.8 );
  }

  void function_test_3() {
    environment.add_function( "function3", sigc::slot<std::string,std::string,std::string>(sigc::ptr_fun( &function3 )) );
    Values values = environment.function( "function3", "hello world" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == "helloworld" );
  }

  void function_test_4() {
    environment.add_function( "function4", sigc::slot<double,int,int,float,double>(sigc::ptr_fun( &function4 )) );
    Values values = environment.function( "function4", "1 2 3.0 4.0" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == 10.0 );
  }

  void function_test_5() {
    environment.add_function( "function5", sigc::slot<int,int,double,std::string,long,float>(sigc::ptr_fun( &function5 )) );
    Values values = environment.function( "function5", "3 3.8 c4 2 1.3" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (int)(3+3.8+4+2+1.3) );
  }

  void function_test_6() {
    environment.add_function( "function6", sigc::slot<long,int,long,double,float,int,long>(sigc::ptr_fun( &function6 )) );
    Values values = environment.function( "function6", "3 56 3.8 1.3 42 192" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (long)(3+56+3.8+1.3+42+192) );
  }

  void function_test_7() {
    environment.add_function( "function7", sigc::slot<float,int,long,double,float,int,long,double>(sigc::ptr_fun( &function7 )) );
    Values values = environment.function( "function7", "3 56 3.8 1.3 42 192 28.444" );
    CPPUNIT_ASSERT( values.size() == 1 );
    CPPUNIT_ASSERT( values[0] == (float)(3+56l+3.8+1.3f+42+192l+28.444) );
  }


};

#endif
