#############################################################################
##   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            ##
##   rvinyard@cs.nmsu.edu                                                  ##
##                                                                         ##
##   This file is part of the clipsmm library.                             ##
##                                                                         ##
##   The clipsmm library is free software; you can redistribute it and/or  ##
##   modify it under the terms of the GNU General Public License           ##
##   version 3 as published by the Free Software Foundation.               ##
##                                                                         ##
##   The clipsmm library is distributed in the hope that it will be        ##
##   useful, but WITHOUT ANY WARRANTY; without even the implied warranty   ##
##   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   ##
##   General Public License for more details.                              ##
##                                                                         ##
##   You should have received a copy of the GNU General Public License     ##
##   along with this software. If not see <http://www.gnu.org/licenses/>.  ##
#############################################################################

INCLUDES = -I$(top_srcdir)/. $(CLIPSMM_CFLAGS) $(UNIT_TEST_CFLAGS)
METASOURCES = AUTO

if CLIPSMM_UNIT_TESTS

noinst_PROGRAMS = clipsmm_unit_tests
clipsmm_unit_tests_LDADD = $(top_builddir)/clipsmm/libclipsmm.la -ldl -lcppunit \
	$(CLIPSMM_LIBS) $(UNIT_TEST_LIBS)
clipsmm_unit_tests_SOURCES = clipsmm_unit_tests.cpp
noinst_HEADERS = fact_tests.h value_tests.h function_tests.h

endif
