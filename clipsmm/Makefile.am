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

INCLUDES = -I$(top_srcdir)/. $(CLIPSMM_CFLAGS)
METASOURCES = AUTO
lib_LTLIBRARIES = libclipsmm.la

libclipsmm_la_LDFLAGS = -version-info @LIBTOOL_SO_VERSION@

libclipsmm_la_LIBADD = $(CLIPSMM_LIBS)

library_includedir = $(includedir)/@PACKAGE_NAME@-@PACKAGE_RELEASE@/@PACKAGE_NAME@

library_include_HEADERS = environment.h value.h factory.h template.h \
	fact.h utility.h enum.h rule.h object.h environmentobject.h module.h \
	defaultfacts.h activation.h any.h global.h function.h clipsmm-config.h pointer.h
libclipsmm_la_SOURCES = environment.cpp factory.cpp template.cpp fact.cpp \
						utility.cpp enum.cpp rule.cpp object.cpp environmentobject.cpp value.cpp module.cpp \
			defaultfacts.cpp activation.cpp global.cpp function.cpp

















