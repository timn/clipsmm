INCLUDES = -I$(top_srcdir)/. $(PROJECT_CFLAGS)
METASOURCES = AUTO
noinst_PROGRAMS = envsimple envthreaded
envsimple_SOURCES = envsimple.cpp
envsimple_LDADD = $(top_builddir)/clipsmm/libclipsmm.la $(PROJECT_LIBS)
envthreaded_SOURCES = envthreaded.cpp
envthreaded_LDADD = $(top_builddir)/clipsmm/libclipsmm.la $(PROJECT_LIBS)
