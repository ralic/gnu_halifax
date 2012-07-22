dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.50)
AC_INIT(config.h.in)

AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(ghfaxviewer, 0.29.10)

AC_CANONICAL_HOST

AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CC

dnl AC_LIBTOOL_WIN32_DLL
dnl AC_PROG_LIBTOOL
dnl AC_SUBST(LIBTOOL_DEPS)

dnl AM_PROG_CC_STDC
dnl AC_HEADER_STDC
dnl AC_C_CONST
dnl AC_C_INLINE

dnl AC_EXEEXT

case $host_os in
  *cygwin* ) CYGWIN=yes;
             CYGWIN=no;;
  *mingw32* ) MINGW32=yes;
              MINGW32=no;;
          * ) MINGW32=no;
              CYGWIN=no;;
esac

AC_PROG_INSTALL
AC_LANG_C

WINDOWS_DETECTED=no

ALL_LINGUAS="de fr pl zh_TW.Big5"

MANPAGES=ghfaxviewer.1
PIXMAPS_DIR="$datadir/pixmaps/ghfaxviewer"

AC_PATH_PROG(LIBTOOL, "libtool")
  
AM_GNU_GETTEXT

dnl Test for libtiff
  
AC_PATH_X
  
dnl if test x"$have_x" = x"yes"; then
dnl  AC_CHECK_LIB(tiff, TIFFReadScanline,
dnl       AC_CHECK_HEADER(tiffio.h,
dnl                     TIFF='tiff'; TIFF_LIBS="${LDFLAGS} -ltiff",
dnl       AC_MSG_WARN(*** please install libtiff (TIFF header files not found) ***)),
dnl       AC_CHECK_LIB(tiff, TIFFWriteScanline,
dnl         AC_CHECK_HEADER(tiffio.h,
dnl                         TIFF='tiff'; TIFF_LIBS="${LDFLAGS} -ltiff -ljpeg -lz",
dnl           AC_MSG_WARN(*** please install libtiff (TIFF header files not found) ***)),
dnl           AC_CHECK_LIB(tiff34, TIFFFlushData,
dnl             AC_CHECK_HEADER(tiffio.h,
dnl                             TIFF='tiff'; TIFF_LIBS="${LDFLAGS} -ltiff34 -ljpeg -lz",
dnl               AC_MSG_WARN(*** please install libtiff (TIFF header files not found) ***)),
dnl              AC_MSG_WARN(*** please install libtiff (TIFF library not found) ***), -ljpeg -lz -lm), -ljpeg -lz -lm), -lm)
dnl fi

dnl deps="$TIFF_LIBS"

AC_ARG_ENABLE(debug,
  [  --enable-debug          warnings, debugging codes and messages],
      debug="$enableval", debug="no")

AC_MSG_CHECKING([whether debugging is requested])
if test x"$debug" = x"yes"; then
    AC_MSG_RESULT([yes])
    CFLAGS="$CFLAGS -Wall -O0 -ggdb3"
else
    AC_MSG_RESULT([no])
fi

# are we configured from halifax parent dir or from independent ghfaxviewer
# subdir ?
if test "x$cache_file" == "x.././config.cache"; then
  SUPPSUBDIRS=
  docsubdir=no
  if test ! -f docs/Makefile.in; then
    mkdir docs
    echo "install clean distclean dist:" > docs/Makefile.in
  fi
else
  SUPPSUBDIRS=docs
  docsubdir=yes
fi

PKG_CHECK_MODULES(GNOME, libgnomeui-2.0 >= 0.14.0  libgnomeprintui-2.2 >= 0.14.0)
PKG_CHECK_MODULES(GHFAXWIDGETS, libgnomeui-2.0 >= 0.14.0  libgnomeprintui-2.2 >= 0.14.0)
AC_SUBST(GNOME_CFLAGS)
AC_SUBST(GNOME_LIBS)
AC_SUBST(GNOME_PRINT_CFLAGS)
AC_SUBST(GNOME_PRINT_LIBS)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

AC_SUBST(GHFW_CFLAGS)
AC_SUBST(GHFW_LIBS)

AC_SUBST(SUPPSUBDIRS)

AC_SUBST(PIXMAPS_DIR)
AC_SUBST(MANPAGES)
AC_SUBST(TIFF_LIBS)
dnl AC_SUBST(RC_ICON_DIRECTIVE)

dnl AM_CONDITIONAL(TARGET_GNU, test $OS = GNU)
dnl AM_CONDITIONAL(TARGET_WIN32, test $OS = WIN32)
AM_CONDITIONAL(HAVE_TIFF, test "x$TIFF_LIBS" != x)
dnl AM_CONDITIONAL(GNOME, test x"$USING_GNOME" = xyes)
dnl AM_CONDITIONAL(WITHOUT_GNOMEPRINT, test "x$no_gnome_print" = xyes)

AC_OUTPUT([
Makefile
ghfaxviewer.spec
debian/Makefile
intl/Makefile
docs/Makefile
src/Makefile
src/ghfaxviewer-res.rc
src/pixmaps/Makefile
po/Makefile.in
po/Makefile
])

dnl if test x"$XPM2WICO" = x && test $OS = WIN32; then
dnl  AC_MSG_WARN([The xpm2wico utility was not found. As a result,
dnl	the application icon won't be generated, which won't arm anything
dnl	anyway.
dnl	To benefit from its functionalities, please get the latest version
dnl	of xpm2wico from:
  
dnl	ftp://ftp.gnu.org/gnu/halifax/tools])
dnl fi