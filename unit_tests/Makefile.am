INCLUDES = -I$(top_srcdir)/. $(PROJECT_CFLAGS)
METASOURCES = AUTO
noinst_PROGRAMS = clipsmm_unit_tests
clipsmm_unit_tests_LDADD = $(top_builddir)/clipsmm/libclipsmm.la -ldl -lcppunit \
	$(PROJECT_LIBS)
clipsmm_unit_tests_SOURCES = clipsmm_unit_tests.cpp
noinst_HEADERS = fact_tests.h value_tests.h
