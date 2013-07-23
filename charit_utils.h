/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Julien PAULI <jpauli@php.net>                                |
  +----------------------------------------------------------------------+
*/

#ifndef CHARIT_UTILS_H_
#define CHARIT_UTILS_H_

#define FETCH_OBJECT charit_object *obj; \
		obj = (charit_object *)zend_object_store_get_object(getThis());

#define FETCH_CHARIT_OBJECT(obj) ((charit_object *)(obj)->data)
#define FETCH_CHARIT_OBJECT_PROP(obj, prop) (FETCH_CHARIT_OBJECT((obj))->prop)

#ifdef PHP_WIN32
#	define PHP_CHARIT_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_CHARIT_API __attribute__ ((visibility("default")))
#else
#	define PHP_CHARIT_API
#endif

#endif /* CHARIT_UTILS_H_ */
