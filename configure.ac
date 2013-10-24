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


#########################################################################
#  package specific values
#########################################################################
pushdef([PACKAGE_MAJOR_VERSION], [0])
pushdef([PACKAGE_MINOR_VERSION], [3])
pushdef([PACKAGE_MICRO_VERSION], [4])
pushdef([PKG_VERSION], PACKAGE_MAJOR_VERSION.PACKAGE_MINOR_VERSION.PACKAGE_MICRO_VERSION)

AC_INIT([clipsmm], PKG_VERSION, [rvinyard@cs.nmsu.edu])

[PACKAGE_MAJOR_VERSION]=PACKAGE_MAJOR_VERSION
[PACKAGE_MINOR_VERSION]=PACKAGE_MINOR_VERSION
[PACKAGE_MICRO_VERSION]=PACKAGE_MICRO_VERSION

popdef([PACKAGE_MAJOR_VERSION])
popdef([PACKAGE_MINOR_VERSION])
popdef([PACKAGE_MICRO_VERSION])
popdef([PKG_VERSION])

#
# +1 :  ? : +1 == new interface that does not break old one
# +1 :  ? :  0 == new interface that breaks old one
#  ? :  ? :  0 == no new interfaces, but breaks apps
#  ? : +1 :  ? == just some internal changes, nothing breaks but might work better
# CURRENT : REVISION : AGE
LIBTOOL_SO_VERSION=2:0:2
LIBTOOL_SO_VERSION_MAJOR=0
AC_SUBST(LIBTOOL_SO_VERSION)
AC_SUBST(LIBTOOL_SO_VERSION_MAJOR)

PKGCONFIG_REQUIRES="clips-6 >= 6.30 glibmm-2.4 >= 2.6.0 gthread-2.0 >= 2.6.0"
PKGCONFIG_VERSION="1.0"

#########################################################################
#  don't touch this
#########################################################################
PACKAGE_RELEASE=$PACKAGE_MAJOR_VERSION.$PACKAGE_MINOR_VERSION
AC_SUBST(PACKAGE_RELEASE)
AC_SUBST(PKGCONFIG_VERSION)

AC_DEFINE_UNQUOTED(PACKAGE_MAJOR_VERSION, $PACKAGE_MAJOR_VERSION, [Major version])
AC_DEFINE_UNQUOTED(PACKAGE_MINOR_VERSION, $PACKAGE_MINOR_VERSION, [Minor version])
AC_DEFINE_UNQUOTED(PACKAGE_MICRO_VERSION, $PACKAGE_MICRO_VERSION, [Micro version])
AC_SUBST(PACKAGE_MAJOR_VERSION)
AC_SUBST(PACKAGE_MINOR_VERSION)
AC_SUBST(PACKAGE_MICRO_VERSION)

AM_INIT_AUTOMAKE([1.9 tar-ustar dist-bzip2 dist-zip -Wno-portability])
AM_CONFIG_HEADER([config.h])
AX_PREFIX_CONFIG_H([clipsmm/clipsmm-config.h],[CLIPSMM],[config.h])

dnl this package needs m4
AC_CHECK_PROGS(M4, gm4 m4, m4)

AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_PROG_INSTALL
AC_CXX_COMPILE_STDCXX_0X

for top_builddir in . .. ../.. $ac_auxdir $ac_auxdir/..; do
test -f $top_builddir/configure && break
done
AC_PROG_LIBTOOL

AC_HEADER_STDC

AC_CONFIG_MACRO_DIR([m4])

#########################################################################
#  header check utility macros
#########################################################################
AC_DEFUN([AC_REQUIRE_HEADERS],[AC_CHECK_HEADERS($1,,AC_MSG_ERROR([Header $1 not found]))])
AC_DEFUN([AC_REQUIRE_LIB],[AC_CHECK_LIB($1,$2,,AC_MSG_ERROR(Library $1 not found))])

AC_CHECK_LIB([clips],\
             [GetEnvironmentFunctionContext],\
             AC_MSG_RESULT([Support for GetEnvironmentFunctionContext in clips found]),\
             AC_MSG_ERROR([GetEnvironmentFunctionContext was not found in the clips library. You need to patch and rebuild your version of clips or use clips 6.30 or higher.])\
             )

#########################################################################
#  Look for smart pointers in either tr1 or boost
#########################################################################
AC_DEFUN(
  [CHECK_FOR_BOOST_SMART_POINTER],
  [AC_MSG_CHECKING([for Boost smart pointers])
   AC_CHECK_HEADER( [boost/shared_ptr.hpp],
                     [AC_DEFINE(USE_BOOST_SMART_POINTER,[],[If defined, boost library smart pointers will be used])
                     ],
                     [AC_MSG_ERROR([No usable smart pointer library found])
                     ]
                   )
  ]
)

AC_DEFUN(
  [CHECK_FOR_TR1_SMART_POINTER],
  [AC_MSG_CHECKING([for TR1 smart pointers])
   AC_CHECK_HEADER( [tr1/boost_shared_ptr.h],
                     [AC_DEFINE(USE_TR1_SMART_POINTER,[],[If defined TR1 smart pointers will be used])
                     ],
                     [CHECK_FOR_BOOST_SMART_POINTER
                     ],
                     [
                       #include <typeinfo>
                       #include <memory>
                       #include <functional>
                       #include <bits/concurrence.h>
                       #include <ext/mt_allocator.h>
                     ]
                   )
  ]
)

AC_MSG_CHECKING([for c++0x smart pointers])
AS_IF([test "$ax_cv_cxx_compile_cxx0x_native" = yes ||
       test "$ax_cv_cxx_compile_cxx0x_cxx" = yes],
      [
        AS_IF([test "$ax_cv_cxx_compile_cxx0x_cxx" = yes],
              [ CXXFLAGS="$CXXFLAGS -std=c++0x"
                AC_SUBST(CXXFLAGS)
                CPP0XFLAGS="-std=c++0x"
                AC_SUBST(CPP0XFLAGS) ])
        AC_DEFINE(USE_CXX0X_SMART_POINTER,[],[If defined c++0x smart pointers will be used])
        AC_MSG_RESULT(yes)
      ],
      [ AC_MSG_RESULT(no)
        CPP0XFLAGS=""
        AC_SUBST(CPP0XFLAGS)
        CHECK_FOR_TR1_SMART_POINTER
      ]
     )


#########################################################################
#  pkgconfig package requirements
#########################################################################
PKG_CHECK_MODULES(CLIPSMM, $PKGCONFIG_REQUIRES)
AC_SUBST(PKGCONFIG_REQUIRES)
AC_SUBST(CLIPSMM_LIBS)
AC_SUBST(CLIPSMM_CFLAGS)

AC_ARG_ENABLE([doc],[AS_HELP_STRING([--enable-doc],[Build documentation [default=no]])],[enable_doc=$enableval],[enable_doc=no])
AM_CONDITIONAL(CLIPSMM_DOC, [test "x${enable_doc}" == xyes])

AC_ARG_ENABLE([unit-tests],[AS_HELP_STRING([--enable-unit-tests],[Build clipsmm unit test applications [default=no]])],[enable_unit_tests=$enableval],[enable_unit_tests=no])
AS_IF([test "x${enable_unit_tests}" == xyes],
  [ PKG_CHECK_MODULES([UNIT_TEST],[cppunit])
  ],
  [])
AM_CONDITIONAL(CLIPSMM_UNIT_TESTS, [test "x${enable_unit_tests}" == xyes])
AC_SUBST(UNIT_TEST_LIBS)
AC_SUBST(UNIT_TEST_CFLAGS)


AC_OUTPUT(clipsmm-1.0.pc Makefile clipsmm/Makefile examples/Makefile examples/environment/Makefile examples/facts/Makefile unit_tests/Makefile doc/Makefile)
