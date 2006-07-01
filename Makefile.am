############################################################################
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

include aminclude.am

if DX_COND_man

dist_man3_MANS = @DX_DOCDIR@/man/man3/*

$(dist_man3_MANS): doxygen-doc

dist-hook:
	rm ${distdir}/@DX_DOCDIR@/man/man3/_*.3 || test true

endif

if DX_COND_html

htmldir = $(datadir)/doc/$(PACKAGE)-devel-$(VERSION)/html
html_DATA = docs/www/reference/html/*
$(html_DATA): doxygen-doc

dist-hook:
	rm -rf `find $(distdir)/docs -name CVS`
	mkdir -p $(distdir)/docs/reference
	mv $(distdir)/docs/www/reference/html $(distdir)/docs/reference/html

endif

CLEANFILES = $(DX_CLEANFILES)

MOSTLYCLEANFILES = $(DX_CLEANFILES)

EXTRA_DIST = $(PACKAGE).kdevelop packaging/fedora-5/$(PACKAGE).spec packaging/suse-10.1/$(PACKAGE).spec $(DX_CONFIG) docs/www/reference/html

SUBDIRS = clipsmm examples packaging

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = @PACKAGE_NAME@-1.0.pc

INCLUDES = $(PROJECT_CFLAGS)

upload-www:
	make clean
	make doxygen-doc
	rsync -azvcu --delete --cvs-exclude docs/www/* $(PACKAGE_WWWHOST)

upload-release:
	make clean
	make doxygen-doc
	make dist-bzip2
	curl -T $(PACKAGE)-$(VERSION).tar.bz2 $(PACKAGE_RELEASEHOST)

fedora-rpms:
	make clean
	make doxygen-doc
	make dist-bzip2
	cp $(PACKAGE)-$(VERSION).tar.bz2 /usr/src/redhat/SOURCES/
	rpmbuild -ba --sign packaging/fedora-5/$(PACKAGE_NAME).spec

suse-rpms:
	make clean
	make doxygen-doc
	make dist-bzip2
	cp $(PACKAGE)-$(VERSION).tar.bz2 /usr/src/packages/SOURCES/
	rpmbuild -ba --sign packaging/suse-10.1/$(PACKAGE_NAME).spec


