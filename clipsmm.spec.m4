%define clipsver 6.24
Summary:          C++ interface to the CLIPS expert system C library
Name:             clipsmm
Version:          PACKAGE_VERSION
Release:          1%{?dist}
License:          GPLv3
URL:              http://clipsmm.sourceforge.net
Group:            System Environment/Libraries
Source0:          http://downloads.sourceforge.net/%{name}/%{name}-%{version}.tar.bz2
Source1:          http://downloads.sourceforge.net/%{name}/%{name}-%{version}-doc.tar.bz2
BuildRoot:        %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:    clips-devel >= %{clipsver} 
BuildRequires:    glibmm24-devel >= 2.6.0 
BuildRequires:    cppunit-devel >= 1.11 
BuildRequires:    pkgconfig
BuildRequires:    m4

%description
The clipsmm library provides a C++ interface to the CLIPS C library.

CLIPS (C Language Integrated Production System) is an expert system
development tool which provides a complete environment for the
construction of rule and/or object based expert systems.

Created in 1985 by NASA at the Johnson Space Center, CLIPS is now
widely used throughout the government, industry, and academia.

%package          devel
Summary:          Headers for developing C++ applications with CLIPS
Group:            Development/Libraries
Requires:         %{name} = %{version}-%{release}
Requires:         clips-devel >= %{clipsver} 
Requires:         glibmm24-devel >= 2.6.0 
Requires:         pkgconfig

%description    devel
This package contains the libraries and header files needed for
developing clipsmm applications.

clipsmm provides a C++ interface to the CLIPS C library.

CLIPS (C Language Integrated Production System) is an expert system
development tool which provides a complete environment for the
construction of rule and/or object based expert systems.

Created in 1985 by NASA at the Johnson Space Center, CLIPS is now
widely used throughout the government, industry, and academia.

%package          doc
Summary:          Documentation for the C++ clipsmm library
Group:            Documentation
Requires:         gtk-doc
Requires:         devhelp
%if 0%{?fedora} > 9 || 0%{?rhel} > 5
BuildArch:        noarch
%endif

%description      doc
This package contains developer's documentation for the clipsmm
library. clipsmm provides C++ based bindings for the C based
CLIPS library.

The documentation can be viewed either through the devhelp
documentation browser or through a web browser. 

If using a web browser the documentation is installed in the gtk-doc
hierarchy and can be found at /usr/share/gtk-doc/html/clipsmm-API_VERSION

CLIPS (C Language Integrated Production System) is an expert system
development tool which provides a complete environment for the
construction of rule and/or object based expert systems.

Created in 1985 by NASA at the Johnson Space Center, CLIPS is now
widely used throughout the government, industry, and academia.

%prep
%setup -q -b 1

%build
%configure --enable-static=no
%{__make} %{?_smp_mflags}

%install
%{__rm} -rf %{buildroot}
%{__make} DESTDIR=%{buildroot} INSTALL="%{__install} -p" install
find %{buildroot} -type f -name "*.la" -exec rm -f {} ';'

%{__mkdir} -p %{buildroot}%{_datadir}/gtk-doc/html/clipsmm-API_VERSION/reference/html/
%{__install} -p --mode=0664 -t %{buildroot}%{_datadir}/gtk-doc/html/clipsmm-API_VERSION/reference/html/ doc/reference/html/*
%{__install} -p --mode=0664 -t %{buildroot}%{_datadir}/gtk-doc/html/clipsmm-API_VERSION/ doc/clipsmm-API_VERSION.devhelp

%clean
%{__rm} -rf %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/libclipsmm.so.*
%doc AUTHORS COPYING

%files devel
%defattr(-,root,root,-)
%{_libdir}/libclipsmm.so
%{_libdir}/pkgconfig/clipsmm-PKGCONFIG_VERSION.pc
%{_includedir}/clipsmm-PACKAGE_RELEASE/
%doc ChangeLog

%files doc
%defattr(-,root,root,-)
%doc %{_datadir}/gtk-doc/html/clipsmm-API_VERSION/


%changelog
* Mon Jul 27 2009 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.1.0-1
- New release

* Fri Jul 24 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.0.7-6
- Rebuilt for https://fedoraproject.org/wiki/Fedora_12_Mass_Rebuild

* Tue Feb 24 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.0.7-5
- Rebuilt for https://fedoraproject.org/wiki/Fedora_11_Mass_Rebuild

* Mon Mar 03 2008 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.7-4
- Bump release for make-tag error

* Mon Mar 03 2008 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.7-3
- Added boost-devel dependency

* Tue Feb 19 2008 Fedora Release Engineering <rel-eng@fedoraproject.org> - 0.0.7-2
- Autorebuild for GCC 4.3

* Sun Nov 12 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.7-1
- New release

* Sun Aug  6 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.6-1
- New release
- Added m4 to BuildRequires

* Mon Jul 31 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.5-1
- New release fixes autoconf generated headers
- Removed pkgconfig from BuildRequires
- Added pkgconfig to -devel Requires

* Sun Jul 30 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.4-2
- Changed make to %%{__make}
- Changed %%{name} to autoconf subst that puts specific name in devel requires
- Added comment regarding why cp occurs for docs
- Added package name to globs in so libs, .pc and demos
- Changed clips-libs BuildRequires to clips-devel
- Added cppunit-devel BuildRequires

* Sat Jul 29 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.4-1
- New release

* Sat Jul 21 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.3-1
- New release

* Sat Jul 20 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.2-1
- New release

* Sun Jun 25 2006 Rick L Vinyard Jr <rvinyard@cs.nmsu.edu> - 0.0.1-1
- Initial release
