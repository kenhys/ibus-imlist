#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([ibus-imlist], [0.1.0], [kenhys@gmail.com])
AC_CONFIG_SRCDIR([src/ibus-imlist.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign tar-pax])

# Checks for programs.
AC_PROG_CC

PKG_CHECK_MODULES([GLIB], glib-2.0 >= 2.26)
PKG_CHECK_MODULES([GIO], gio-2.0)
PKG_CHECK_MODULES([IBUS], ibus-1.0)

# For debug
AC_ARG_ENABLE(debug,
  [AS_HELP_STRING([--enable-debug],
                  [use debug flags (default=no)])],
  [ibus_imlist_debug="$enableval"],
  [ibus_imlist_debug="no"])
if test "x$ibus_imlist_debug" != "xno"; then
  ibus_imlist_debug="yes"
  if test "$CLANG" = "yes"; then
    CFLAGS="$CFLAGS -O0 -g"
    CXXFLAGS="$CXXFLAGS -O0 -g"
  elif test "$GCC" = "yes"; then
    CFLAGS="$CFLAGS -O0 -g3"
    CXXFLAGS="$CXXFLAGS -O0 -g3"
  fi
fi

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

GLIB_GSETTINGS

AC_CONFIG_FILES([
	Makefile		
	src/Makefile		
])

AC_OUTPUT
