dnl $Id$
dnl config.m4 for extension stock

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(stock, for stock support,
[  --enable-stock           Enable stock support])

if test "$PHP_STOCK" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-stock -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/stock.h"  # you most likely want to change this
  dnl if test -r $PHP_STOCK/$SEARCH_FOR; then # path given as parameter
  dnl   STOCK_DIR=$PHP_STOCK
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for stock files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       STOCK_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$STOCK_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the stock distribution])
  dnl fi

  dnl # --with-stock -> add include path
  dnl PHP_ADD_INCLUDE($STOCK_DIR/include)

  dnl # --with-stock -> check for lib and symbol presence
  dnl LIBNAME=stock # you may want to change this
  dnl LIBSYMBOL=stock # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $STOCK_DIR/lib, STOCK_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_STOCKLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong stock lib version or lib not found])
  dnl ],[
  dnl   -L$STOCK_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(STOCK_SHARED_LIBADD)

  PHP_NEW_EXTENSION(stock, stock.c, $ext_shared)
fi
