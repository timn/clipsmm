#############################################################################
##   Copyright (C) 2001 by Rick L. Vinyard, Jr.                            ##
##   rvinyard@cs.nmsu.edu                                                  ##
##                                                                         ##
##   This program is free software; you can redistribute it and/or modify  ##
##   it under the terms of the GNU General Public License as               ##
##   published by the Free Software Foundation version 2.                  ##
##                                                                         ##
##   This program is distributed in the hope that it will be useful,       ##
##   but WITHOUT ANY WARRANTY; without even the implied warranty of        ##
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ##
##   GNU General Public License for more details.                          ##
##                                                                         ##
##   You should have received a copy of the GNU General Public             ##
##   License along with this library; if not, write to the                 ##
##   Free Software Foundation, Inc.,                                       ##
##   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              ##
#############################################################################
INCLUDES = -I$(top_srcdir)/. $(PROJECT_CFLAGS)
METASOURCES = AUTO
lib_LTLIBRARIES = libclipsmm.la

libclipsmm_la_LDFLAGS = -version-info @LIBTOOL_SO_VERSION@

libclipsmm_la_LIBADD = $(PROJECT_LIBS)

library_includedir = $(includedir)/@PACKAGE_NAME@-@PACKAGE_RELEASE@/@PACKAGE_NAME@

library_include_HEADERS = clipsmm.h environment.h value.h factory.h template.h \
			fact.h utility.h enum.h rule.h object.h environmentobject.h module.h \
	defaultfacts.h activation.h
libclipsmm_la_SOURCES = environment.cpp factory.cpp template.cpp fact.cpp \
				utility.cpp enum.cpp rule.cpp object.cpp environmentobject.cpp value.cpp module.cpp \
	defaultfacts.cpp activation.cpp
















