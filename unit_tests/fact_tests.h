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
#ifndef FACTSTEST_H
#define FACTSTEST_H

#include <cppunit/TestFixture.h>

#include <clipsmm.h>

using namespace CLIPS;

class FactsTest : public  CppUnit::TestFixture {
  public:

    CPPUNIT_TEST_SUITE( FactsTest );
    CPPUNIT_TEST( assert_template_fact );
    CPPUNIT_TEST( check_template_fact_slots );
    CPPUNIT_TEST( assert_ordered_fact );
    CPPUNIT_TEST( check_ordered_fact_slots );
    CPPUNIT_TEST( check_template_fact_slot_values );
    CPPUNIT_TEST( check_ordered_fact_slot_values );
    CPPUNIT_TEST( set_template_fact_slot_values );
    CPPUNIT_TEST( template_fact_retraction );
    CPPUNIT_TEST( ordered_fact_retraction );
    CPPUNIT_TEST_SUITE_END();

  protected:
    CLIPS::Environment environment;
    CLIPS::Fact::pointer template_fact, ordered_fact;
    std::vector<std::string> slot_names;
    std::vector<std::string>::iterator iter;

  public:
    void setUp() {
      environment.load( "strips.clp" );
      template_fact = environment.assert_fact("(in (object R2D2) (location X-Wing) )");
      ordered_fact = environment.assert_fact("(numbers 1 2 3 4 5 )");
    }

    void tearDown() { }

    void assert_template_fact() { CPPUNIT_ASSERT( template_fact ); }

    void check_template_fact_slots() {
      slot_names = template_fact->slot_names();
      CPPUNIT_ASSERT( slot_names.size() == 2 );
      CPPUNIT_ASSERT( slot_names[0] == "object" );
      CPPUNIT_ASSERT( slot_names[1] == "location" );
    }

    void assert_ordered_fact() { CPPUNIT_ASSERT( ordered_fact ); }

    void check_ordered_fact_slots() {
      slot_names = ordered_fact->slot_names();
      CPPUNIT_ASSERT( slot_names.size() == 1 );
      CPPUNIT_ASSERT( slot_names[0] == "implied" );
    }

    void check_template_fact_slot_values() {
      Values values;
      values = template_fact->slot_value("object");
      CPPUNIT_ASSERT( values.size() == 1 );
      CPPUNIT_ASSERT( values[0] == "R2D2" );
      values = template_fact->slot_value("location");
      CPPUNIT_ASSERT( values.size() == 1 );
      CPPUNIT_ASSERT( values[0] == "X-Wing" );
    }

    void check_ordered_fact_slot_values() {
      Values values = ordered_fact->slot_value("");
      CPPUNIT_ASSERT( values.size() == 5 );
      CPPUNIT_ASSERT( values[0] == 1 );
      CPPUNIT_ASSERT( values[1] == 2 );
      CPPUNIT_ASSERT( values[2] == 3 );
      CPPUNIT_ASSERT( values[3] == 4 );
      CPPUNIT_ASSERT( values[4] == 5 );
    }

    void set_template_fact_slot_values() {
      template_fact->set_slot( "object", "C3PO" );
      template_fact->set_slot( "location", "Millenium Falcon" );
      Values values;
      values = template_fact->slot_value("object");
      CPPUNIT_ASSERT( values.size() == 1 );
      CPPUNIT_ASSERT( values[0] == "C3PO" );
      values = template_fact->slot_value("location");
      CPPUNIT_ASSERT( values.size() == 1 );
      CPPUNIT_ASSERT( values[0] == "Millenium Falcon" );
    }

    void template_fact_retraction() {
      CPPUNIT_ASSERT( template_fact->exists() );
      template_fact->retract();
      CPPUNIT_ASSERT( ! template_fact->exists() );
    }

    void ordered_fact_retraction() {
      CPPUNIT_ASSERT( ordered_fact->exists() );
      ordered_fact->retract();
      CPPUNIT_ASSERT( ! ordered_fact->exists() );
    }

};

#endif
