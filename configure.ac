# configure.in for frontline
#
# Author: Masatake YAMATO (yamato@redhat.com)
#
AC_INIT([autotrace], [0.31.1], [], [], [http://autotrace.sourceforge.net])
AM_INIT_AUTOMAKE(no-define subdir-objects)
AC_CONFIG_MACRO_DIR([m4])

#
# version setting up for libtool
#
LT_CURRENT=3
LT_REVISION=0
LT_AGE=0

AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

AC_PROG_CC
AC_PROG_CPP
AC_PROG_LIBTOOL
AC_PROG_INSTALL

AC_CHECK_HEADERS(malloc.h)

AM_SILENT_RULES([yes])
AM_CONFIG_HEADER(config.h)
AM_SANITY_CHECK

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION(0.18)

PKG_PROG_PKG_CONFIG([0.20])

dnl
dnl ImageMagick
dnl
HAVE_MAGICK=no
AC_ARG_WITH(magick,
	[AS_HELP_STRING([--with-magick=@<:@yes/no@:>@],
			[link with magick library @<:@default=no@:>@])],,
	[with_magick=no])

magick_ok=no
if test "x${with_magick}" = xyes; then
  PKG_CHECK_MODULES(MAGICK, MagickCore, magick_ok=yes, :)
fi
AM_CONDITIONAL(HAVE_MAGICK, test x$magick_ok == xyes)

dnl
dnl LIBPNG
dnl

dnl Test for zlib (from gimp-1.1.29)
HAVE_ZLIB=no
AC_CHECK_LIB(z, gzsetparams,
      	     [AC_CHECK_HEADER(zlib.h,
	                     HAVE_ZLIB=yes,
	                     AC_MSG_WARN(*** ZLIB header files not found: PNG Input will be disabled. ***))],
	     AC_MSG_WARN(*** ZLIB library files not found: PNG Input will be disabled. ***))

dnl Test for libpng
HAVE_LIBPNG_STAGE1=no
AC_CHECK_LIB(png, png_get_image_width,
	HAVE_LIBPNG_STAGE1=yes ,,-lz -lm)

HAVE_LIBPNG=no
if test "x$HAVE_LIBPNG_STAGE1" = "xyes" ; then
	AC_CHECK_LIB(png, png_read_png,
		HAVE_LIBPNG=yes ,,-lz -lm)
	if test "x$HAVE_LIBPNG" = "xyes" ; then
		LIBPNG_LDFLAGS="-lpng -lz -lm"
		AC_SUBST(LIBPNG_LDFLAGS)
		AC_DEFINE(HAVE_LIBPNG,1,[PNG library is available or not])
	else
	   AC_MSG_WARN([*** libpng exists but cannot find png_read_png in the libpng. ***])
	   AC_MSG_WARN([*** libpng might be old.                                      ***])
	   AC_MSG_WARN([*** You need libpng 1.0.6 or higher.                          ***])
	   AC_MSG_WARN([*** Png input handler is disabled.                            ***])
	fi
else
	AC_MSG_WARN([*** Cannot find libpng.            ***])
	AC_MSG_WARN([*** Png input handler is disabled. ***])
fi
AM_CONDITIONAL(HAVE_LIBPNG, test $HAVE_LIBPNG = yes)

dnl
dnl LIBMING(LIBSWF)
dnl
HAVE_LIBSWF=no

AC_CHECK_HEADER(ming.h,
	        swf_header_found=yes,
		swf_header_found=no)
if test "${swf_header_found}" = yes ; then
	AC_CHECK_LIB(ming, Ming_init, 
		     HAVE_LIBSWF=yes,,-lm)
	if test "$HAVE_LIBSWF" = "yes" ; then
		LIBSWF_LDFLAGS="-lming -lm"
		AC_SUBST(LIBSWF_LDFLAGS)
		AC_DEFINE(HAVE_LIBSWF,1,[SWF library is available or not])
	else
 		AC_MSG_WARN([*** Cannot find libming.    ***])
		AC_MSG_WARN([*** SWF output is disabled. ***])
	fi
else
	AC_MSG_WARN([*** Cannot find ming.h.     ***])
	AC_MSG_WARN([*** SWF output is disabled. ***])
fi
AM_CONDITIONAL(HAVE_LIBSWF, test x$HAVE_LIBSWF = xyes)

dnl
dnl Suppressing linker warning
dnl 
dnl On MacOS X(Darwin), getopt related symbols are defined 
dnl in /usr/lib/libm.dylib. They are conflicted with symbols 
dnl defined in getopt* of autotrace. To avoid warning-messages 
dnl about this confliction, "-multiply_defined suppress" is 
dnl passed to ld if autotrace is built on Darwin.
dnl
dnl BTW, Is getopt mathematical function?
dnl 
dnl libm.dylib on Darwin problem is reported by 
dnl Martin Kerscher <kerscher@theorie.physik.uni-muenchen.de>
dnl
AC_MSG_CHECKING([whether the host is Darwin])
case $host_os in
     darwin*) LDFLAGS="-Xlinker -multiply_defined -Xlinker suppress ${LDFLAGS}"
     AC_MSG_RESULT([yes])
     AC_MSG_WARN([linker messages that warns symbols are multiply defined 
are suppressed])
     ;;
     *)	
     AC_MSG_RESULT([no])
     ;;
esac

dnl
dnl pstoedit library
dnl

AC_ARG_WITH(pstoedit,
	[AS_HELP_STRING([--with-pstoedit=@<:@yes/no@:>@],
			[link with pstoedit library @<:@default=no@:>@])],,
	[with_pstoedit=no])

pstoedit_ok=no
if test "x${with_pstoedit}" = xyes; then
  PKG_CHECK_MODULES(LIBPSTOEDIT, pstoedit, pstoedit_ok=yes, :)
  if test "x${pstoedit_ok}" == "xyes"; then
    AC_CHECK_FUNCS([mkstemp])
    echo '*** pstoedit output functions are enabled.                      ***'
    echo '*** However, these are experimental functions in autotrace.     ***'
    echo '*** If you get an error in building time about pstoedit,        ***'
    echo '*** you can run configure with --without-pstoedit option again. ***'
  else
    AC_MSG_WARN([
*** Cannot find libpstoedit. ***
*** Output functions using libpstoedit are disabled ***])
  fi
else
  AC_MSG_WARN([pstoedit output functions are disabled from command line.])
fi
AM_CONDITIONAL(HAVE_LIBPSTOEDIT, test x$pstoedit_ok == xyes)

dnl
dnl GLib2
dnl

PKG_CHECK_MODULES(GLIB2, glib-2.0 >= 2.0  gmodule-2.0 >= 2.0 gthread-2.0 >= 2.0 gobject-2.0 >= 2.0, 
	          glib_ok=yes, glib_ok=no)
if test "x${glib_ok}" != "xyes"; then
   AC_MSG_ERROR([cannot find glib-2.0])
fi

AC_OUTPUT([
po/Makefile.in 
Makefile autotrace.pc autotrace.spec])

echo "

Configuration:
	imagemagick output support:	$magick_ok
	libpng output support:		$HAVE_LIBPNG
	swf output support by ming:	$HAVE_LIBSWF
	pstoedit output support:	$pstoedit_ok

"
