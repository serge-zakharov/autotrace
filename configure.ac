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
[  --with-magick  compile with maigck(default)
  --without-magick  compile without maigck],,with_magick=yes)

if test $with_magick = yes ; then
	AC_CHECK_PROG(MAGICK_CONFIG, Magick-config, Magick-config, "")
	if test "x$MAGICK_CONFIG" = "xMagick-config" ; then
		CPPFLAGS_BACKUP="$CPPFLAGS"
		CPPFLAGS=`Magick-config --cppflags`
		AC_CHECK_HEADER(magick/api.h,
				magick_header_found=yes,
				magick_header_found=no)
		MAGICK_CFLAGS=${CPPFLAGS}
		CPPFLAGS=${CPPFLAGS_BACKUP}
		if test "x${magick_header_found}" = xyes ; then
			MAGICK_LDFLAGS="`Magick-config --ldflags` `Magick-config --libs`"
			dnl
			dnl Checking version
			dnl
			AC_MSG_CHECKING([ImageMagick - version >= 5.2.1])
			dnl Get version and split it into MAJOR, MINOR and MICRO
			MAGICK_VERSION=`Magick-config --version`
                        dnl The following test works because there was never
                        dnl any imagemagick 5.x.y with x >= 10.
                        case $MAGICK_VERSION in
                          [[01234]] | [[01234]].* | 5.[[01]]* | 5.2.0* )

			   	AC_MSG_RESULT(no($MAGICK_VERSION))
				AC_MSG_WARN([*** Version 5.2.1 or higher is required.             ***])
				AC_MSG_WARN([*** ImageMagick input handler is disabled.           ***])
				;;
			   *)
				AC_MSG_RESULT(yes($MAGICK_VERSION))
				AC_SUBST(MAGICK_CFLAGS)
				AC_SUBST(MAGICK_LDFLAGS)
				HAVE_MAGICK=yes
				AC_DEFINE(HAVE_MAGICK,1,[ImageMagick library is available or not])
			        ;;
			esac
		else
			AC_MSG_WARN([*** Magick-config is found but magick/api.h is not found in $MAGICK_CFLAGS ***])
 			AC_MSG_WARN([*** Check Magick-config.                                                   ***])
			AC_MSG_WARN([*** ImageMagick input handler is disabled.                                 ***])
		fi
	else
		AC_MSG_WARN([*** Magick-config is not found.                      ***])
		AC_MSG_WARN([*** ImageMagick input handler is disabled.           ***])		
	fi
fi
AM_CONDITIONAL(HAVE_MAGICK, test $HAVE_MAGICK = yes)

dnl
dnl libMagick.la sanity check
dnl 
dnl It seems that libMagick.la in RedHat 7.2 is broken.
dnl libMagick.la refers /usr/lib/libxml2.la. However, 
dnl /usr/lib/libxml2.la is not existed. Therefore linking
dnl against libMagick.la is failed.
dnl
libMagick_la_path=
libMagick_la_sanity=yes

dnl Stage one: finding libMagick.la
if test $HAVE_MAGICK = yes && test $enable_shared = yes; then
   for f in $MAGICK_LDFLAGS; do
      case ${f} in
	   -L*)
	       f=`echo $f | sed -e 's/-L//'`
	       if test -f ${f}/libMagick.la; then
		  libMagick_la_path="${f}/libMagick.la"
	       fi;;
      esac
   done
fi

dnl Stage two: Check internal of libMagick.la
if test -n "${libMagick_la_path}"; then
   AC_MSG_CHECKING([Sanity of libMagick.la])
   dnl libdir is defined in libMagick.al.
   dnl Don't use the value.
   libdir_backup=${libdir}
    . ${libMagick_la_path}
   libdir=${libdir_backup}
    for elt in ${dependency_libs}; do
	case ${elt} in
	    *.la )
		if test ! -f ${elt}; then
		   if test ${libMagick_la_sanity} = yes; then
		      AC_MSG_RESULT([broken])
		      libMagick_la_sanity=no
		   fi
		   AC_MSG_WARN([Cannot find $elt refereed in ${libMagick_la_path}])
		fi;;
	esac
    done
   if test ${libMagick_la_sanity} = yes; then
      AC_MSG_RESULT([ok])
   else
      AC_MSG_WARN([*** Building will be failed at link time.])
      AC_MSG_WARN([*** To avoid this failure, don't link libMagick.so: Run ./configure --without-magick])
   fi
fi

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
HAVE_LIBPSTOEDIT=no
HAVE_LIBPSTOEDIT_320=no
HAVE_LIBPSTOEDIT_321=no
LIBPSTOEDIT_CFLAGS=
LIBPSTOEDIT_LIBS=
LIBPSTOEDIT_EXTRA_LIBS=

AC_ARG_WITH(pstoedit,
[  --with-pstoedit link with pstoedit library(default)
  --without-pstoedit link without pstoedit library],,with_pstoedit=yes)
if test "x${with_pstoedit}" = xyes; then
dnl
dnl 
dnl
AC_PROG_CXX
dnl Standard C++ library and C++ Runtime
dnl --- WORKAROUND for pstoedit 3.32.0
CXX_RUNTIME_LIB=
CXX_STD_LIB=
if test x"$GXX" = xyes; then
   AC_CHECK_LIB(g++,main,CXX_RUNTIME_LIB=-lg++)
   AC_CHECK_LIB(stdc++,main,CXX_STD_LIB=-lstdc++,,${CXX_RUNTIME_LIB})
fi
AC_MSG_CHECKING([for C++ runtime])
LIBPSTOEDIT_EXTRA_LIBS="${CXX_STD_LIB} ${CXX_RUNTIME_LIB}"
AC_MSG_RESULT([${CXX_STD_LIB} ${CXX_RUNTIME_LIB}])
dnl dl library
dnl --- WORKAROUND for pstoedit 3.32.0
LIBLD_LDFLAGS=
AC_CHECK_LIB(dl,main,[LIBLD_LDFLAGS=-ldl])
if test "x${LIBLD_LDFLAGS}" != x; then
   LIBPSTOEDIT_EXTRA_LIBS="${LIBPSTOEDIT_EXTRA_LIBS} ${LIBLD_LDFLAGS}"
fi

echo '*** Checking pstoedit existence TWICE(if needed) ***'
echo '*** This is the 1st check                        ***'
AM_PATH_PSTOEDIT(3.32.1,HAVE_LIBPSTOEDIT_321=yes)
if test ${HAVE_LIBPSTOEDIT_321} != yes; then
   echo '*** The 1st check is failed.                     ***'
   LIBS_BAKCUP=$LIBS
   LIBS="$LIBS ${LIBPSTOEDIT_EXTRA_LIBS}"
   echo '*** This is the 2nd check                        ***'
   AM_PATH_PSTOEDIT(3.32.0,HAVE_LIBPSTOEDIT_320=yes)
   LIBS=${LIBS_BAKCUP}

   if test ${HAVE_LIBPSTOEDIT_320} = yes; then
	echo '*** The 2nd check is passed.                     ***'
        HAVE_LIBPSTOEDIT=yes
	AC_DEFINE(HAVE_LIBPSTOEDIT,1,[pstoedit library is available or not])
	LIBPSTOEDIT_LIBS="${PSTOEDIT_LIBS} ${LIBPSTOEDIT_EXTRA_LIBS}"
	LIBPSTOEDIT_CFLAGS="${PSTOEDIT_CFLAGS}"
   else
        echo '*** The 2nd check is failed.                     ***'
   fi
else
	echo '*** The 1st check is passed.                     ***'
	HAVE_LIBPSTOEDIT=yes
	AC_DEFINE(HAVE_LIBPSTOEDIT,1,[pstoedit library is available or not])
	LIBPSTOEDIT_LIBS="${PSTOEDIT_LIBS} ${LIBPSTOEDIT_EXTRA_LIBS}"	
	LIBPSTOEDIT_CFLAGS="${PSTOEDIT_CFLAGS}"
fi

if test ${HAVE_LIBPSTOEDIT} = yes; then
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
dnl
dnl
dnl
else
AC_MSG_WARN([pstoedit output functions are disabled from command line.])
fi
AC_SUBST(LIBPSTOEDIT_CFLAGS)
AC_SUBST(LIBPSTOEDIT_LIBS)
AM_CONDITIONAL(HAVE_LIBPSTOEDIT, test x$HAVE_LIBPSTOEDIT = xyes)

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
	imagemagick output support:	$HAVE_MAGICK
	libpng output support:		$HAVE_LIBPNG
	swf output support by ming:	$HAVE_LIBSWF
	pstoedit output support:	$HAVE_LIBPSTOEDIT

"
