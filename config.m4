dnl $Id$
dnl config.m4 for extension charit

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(charit, for charit support,
dnl Make sure that the comment is aligned:
dnl [  --with-charit             Include charit support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(charit, whether to enable charit support,
dnl Make sure that the comment is aligned:
[  --enable-charit           Enable charit support])

if test "$PHP_CHARIT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-charit -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/charit.h"  # you most likely want to change this
  dnl if test -r $PHP_CHARIT/$SEARCH_FOR; then # path given as parameter
  dnl   CHARIT_DIR=$PHP_CHARIT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for charit files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       CHARIT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$CHARIT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the charit distribution])
  dnl fi

  dnl # --with-charit -> add include path
  dnl PHP_ADD_INCLUDE($CHARIT_DIR/include)

  dnl # --with-charit -> check for lib and symbol presence
  dnl LIBNAME=charit # you may want to change this
  dnl LIBSYMBOL=charit # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $CHARIT_DIR/lib, CHARIT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_CHARITLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong charit lib version or lib not found])
  dnl ],[
  dnl   -L$CHARIT_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(CHARIT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(charit, charit.c, $ext_shared)
  PHP_ADD_EXTENSION_DEP(charit, spl)
fi
