# websocket client

AC_PREREQ([2.63])
AC_INIT([wsclient], [0.5], [support@commandus.com])
AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([1.11 foreign no-define])
AC_CONFIG_SRCDIR([wsclient.cpp])
AC_CONFIG_HEADERS([config.h])

m4_include([m4/ax_boost_base.m4])
m4_include([m4/ax_pthread.m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL

# Checks for libraries.
AX_BOOST_BASE()
AX_PTHREAD()
AC_CHECK_HEADERS([argtable2.h], [], AC_MSG_ERROR([Could not find argtable2.h. Try $ ./configure CFLAGS='-Iyour-argtable2-include-path]))
AC_CHECK_LIB(argtable2, arg_parse, [], AC_MSG_ERROR([Could not find libargtable2. Try $ ./configure LDFLAGS='-Lyour-argtable2-lib-path']))
#AC_CHECK_HEADERS([boost/thread.hpp], [], AC_MSG_ERROR([Could not find boost/*.hpp. Try $ ./configure CFLAGS='-Iyour-boost-include-path]))
AC_CHECK_HEADERS([fcntl.h])
AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([websocketpp/version.hpp], [], AC_MSG_ERROR([Could not find websocketpp/*.hpp. Try $ ./configure CFLAGS='-Iyour-websocketpp-include-path]))
AC_LANG_POP([C++])
# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.

AC_OUTPUT
