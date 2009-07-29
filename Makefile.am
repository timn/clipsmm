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


ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
	clipsmm.kdevelop \
	autogen.sh \
	clipsmm.spec \
	clipsmm.spec.m4

SUBDIRS = clipsmm examples unit_tests doc

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = clipsmm-$(PKGCONFIG_VERSION).pc

INCLUDES = -I$(top_srcdir)/. $(CLIPSMM_CFLAGS)

top_includedir = $(includedir)/clipsmm-$(PACKAGE_RELEASE)
top_include_HEADERS = clipsmm.h

PACKAGE_RELEASEHOST="${USER},clipsmm@frs.sourceforge.net:/home/frs/project/c/cl/clipsmm/$(VERSION)"

docs:
	cd doc && make docs

upload-docs:
	cd doc && make upload-docs

upload-docs-only:
	cd doc && make upload-docs-only

TO_UPLOAD = $(PACKAGE)-$(VERSION).tar.bz2 $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION).zip $(PACKAGE)-$(VERSION)-doc.tar.bz2 $(PACKAGE)-$(VERSION)-doc.tar.gz $(PACKAGE)-$(VERSION)-doc.zip
RELEASE_NOTES = $(PACKAGE)-$(VERSION)-release-notes.txt
TO_UPLOAD_RN = $(TO_UPLOAD) $(RELEASE_NOTES)

release-notes:
	gedit $(RELEASE_NOTES) ChangeLog

upload-release-only:
	if test -e $(RELEASE_NOTES); \
          then \
            scp $(TO_UPLOAD_RN) $(PACKAGE_RELEASEHOST); \
          else \
            scp $(TO_UPLOAD) $(PACKAGE_RELEASEHOST); \
        fi

upload-release: changelog release-notes dist upload-release-only

spec:
	m4 -D PACKAGE_VERSION=$(PACKAGE_VERSION) \
		-D PACKAGE_RELEASE=$(PACKAGE_RELEASE) \
		-D PKGCONFIG_VERSION=$(PKGCONFIG_VERSION) \
		-D API_VERSION=$(PACKAGE_RELEASE) \
		clipsmm.spec.m4 >clipsmm.spec

changelog:
	svn2cl --authors=svn2cl.authors -r HEAD:1 --group-by-day -a
	cat ChangeLog.old >> ChangeLog

rpm: spec dist-bzip2
	cp $(PACKAGE)-$(VERSION).tar.bz2 ~/rpmbuild/SOURCES/
	cp $(PACKAGE_NAME).spec ~/rpmbuild/SPECS/
	rpmbuild -ba $(PACKAGE_NAME).spec

srpm: spec dist-bzip2
	cp $(PACKAGE)-$(VERSION).tar.bz2 ~/rpmbuild/SOURCES/
	cp $(PACKAGE_NAME).spec ~/rpmbuild/SPECS/
	rpmbuild -bs $(PACKAGE_NAME).spec

mockbuild: srpm
	mock --rebuild ~/rpmbuild/SRPMS/$(PACKAGE)-$(VERSION)*.src.rpm

dist-hook:
	cd doc && make docsdist
	mv doc/$(PACKAGE)-$(VERSION)-doc.tar.gz .
	mv doc/$(PACKAGE)-$(VERSION)-doc.tar.bz2 .
	mv doc/$(PACKAGE)-$(VERSION)-doc.zip .

