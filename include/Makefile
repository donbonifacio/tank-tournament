# Generated automatically from Makefile.in by configure.
# Makefile.in generated automatically by automake 1.4-p6 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999, 2001 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = .
top_srcdir = ..
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/Tank
pkglibdir = $(libdir)/Tank
pkgincludedir = $(includedir)/Tank

top_builddir = ..

ACLOCAL = aclocal-1.4
AUTOCONF = autoconf
AUTOMAKE = automake-1.4
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL_PROGRAM}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = i686-pc-linux-gnu
host_triplet = i686-pc-linux-gnu
AS = @AS@
CC = gcc
CXX = c++
DLLTOOL = @DLLTOOL@
ECHO = echo
EXEEXT = 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
MAKEINFO = makeinfo
NO_PREFIX_PACKAGE_DATA_DIR = share/Tank
NO_PREFIX_PACKAGE_DOC_DIR = doc/Tank
NO_PREFIX_PACKAGE_HELP_DIR = share/Tank/help
NO_PREFIX_PACKAGE_MENU_DIR = share/Tank
NO_PREFIX_PACKAGE_PIXMAPS_DIR = share/Tank/pixmaps
OBJDUMP = @OBJDUMP@
OBJEXT = o
PACKAGE = Tank
PACKAGE_DATA_DIR = /usr/local/share/Tank
PACKAGE_DOC_DIR = /usr/local/doc/Tank
PACKAGE_HELP_DIR = /usr/local/share/Tank/help
PACKAGE_MENU_DIR = /usr/local/share/Tank
PACKAGE_PIXMAPS_DIR = /usr/local/share/Tank/pixmaps
RANLIB = ranlib
SDL_CFLAGS = -I/usr/include/SDL -D_REENTRANT
SDL_CONFIG = /usr/bin/sdl-config
SDL_LIBS = -L/usr/lib -lSDL -lpthread
STRIP = strip
VERSION = 0.1

tank_includedir = $(pkgincludedir)

tank_include_DATA =  	StringTokenizer.h 	Ptrsolit.h 	Properties.h 	Exceptions.h 	Log.h 	Safe.h 	SharedPointer.h 	Surface.h 	SpriteSequence.h 	Screen.h 	Menu.h 	Rectangle.h 	Actor.h 	Terrain.h 	Global.h 	SpriteHandler.h 	TerrainFactory.h 	Map.h 	Movable.h 	Point.h 	Direction.h 	Task.h 	Arena.h 	BaseTank.h 	KeyHandler.h 	HumanPlayer.h 	Bullet.h 	Weapon.h 	Weapons.h 	Explosion.h 	Enemy.h 	HumanDriver.h 	Lagartas.h 	Printable.h 	Random.h 	Tank.h 	TankController.h 	TankFactory.h 	TankPart.h


EXTRA_DIST = $(tank_include_DATA)
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = ../config.h
CONFIG_CLEAN_FILES = 
DATA =  $(tank_include_DATA)

DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = gtar
GZIP_ENV = --best
all: all-redirect
.SUFFIXES:
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu include/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status $(BUILT_SOURCES)
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


install-tank_includeDATA: $(tank_include_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(tank_includedir)
	@list='$(tank_include_DATA)'; for p in $$list; do \
	  if test -f $(srcdir)/$$p; then \
	    echo " $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(tank_includedir)/$$p"; \
	    $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(tank_includedir)/$$p; \
	  else if test -f $$p; then \
	    echo " $(INSTALL_DATA) $$p $(DESTDIR)$(tank_includedir)/$$p"; \
	    $(INSTALL_DATA) $$p $(DESTDIR)$(tank_includedir)/$$p; \
	  fi; fi; \
	done

uninstall-tank_includeDATA:
	@$(NORMAL_UNINSTALL)
	list='$(tank_include_DATA)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(tank_includedir)/$$p; \
	done
tags: TAGS
TAGS:


distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = include

distdir: $(DISTFILES)
	here=`cd $(top_builddir) && pwd`; \
	top_distdir=`cd $(top_distdir) && pwd`; \
	distdir=`cd $(distdir) && pwd`; \
	cd $(top_srcdir) \
	  && $(AUTOMAKE) --include-deps --build-dir=$$here --srcdir-name=$(top_srcdir) --output-dir=$$top_distdir --gnu include/Makefile
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am:
install-exec: install-exec-am

install-data-am: install-tank_includeDATA
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-tank_includeDATA
uninstall: uninstall-am
all-am: Makefile $(DATA)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(tank_includedir)


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-generic clean-am
	-rm -f libtool

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: uninstall-tank_includeDATA install-tank_includeDATA tags distdir \
info-am info dvi-am dvi check check-am installcheck-am installcheck \
install-exec-am install-exec install-data-am install-data install-am \
install uninstall-am uninstall all-redirect all-am all installdirs \
mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
