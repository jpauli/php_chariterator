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

/* $Id$ */

#ifndef PHP_CHARIT_H
#define PHP_CHARIT_H

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/spl/php_spl.h"
#include "ext/spl/spl_functions.h"
#include "ext/spl/spl_engine.h"
#include "ext/spl/spl_iterators.h"
#include "ext/spl/spl_exceptions.h"
#include "zend_API.h"

extern zend_module_entry charit_module_entry;
#define phpext_charit_ptr &charit_module_entry

#ifdef PHP_WIN32
#	define PHP_CHARIT_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_CHARIT_API __attribute__ ((visibility("default")))
#else
#	define PHP_CHARIT_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(charit);
PHP_MSHUTDOWN_FUNCTION(charit);
PHP_RINIT_FUNCTION(charit);
PHP_RSHUTDOWN_FUNCTION(charit);
PHP_MINFO_FUNCTION(charit);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(charit)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(charit)
*/

#ifdef ZTS
#define CHARIT_G(v) TSRMG(charit_globals_id, zend_charit_globals *, v)
#else
#define CHARIT_G(v) (charit_globals.v)
#endif

#define FETCH_OBJECT charit_object *obj; \
		obj = (charit_object *)zend_object_store_get_object(getThis());

static zend_class_entry *spl_ce_CharIterator;
PHP_MINIT_FUNCTION(spl_char);

extern zend_class_entry *spl_ce_OutOfRangeException;

static zend_object_handlers spl_CharIterator_object_handlers;

typedef struct _charit_object {
	zend_object zobj;
	zval *charval;
	long chunk_size;
	int offset;
	int max_offset;
} charit_object;

typedef struct _charit_object_iterator {
	zend_object_iterator zit;
	zval **previous_val;
} charit_object_iterator;

static void spl_CharIterator_it_func_dtor(zend_object_iterator *iter);
static void spl_CharIterator_it_func_move_forward(zend_object_iterator *iter);
static void spl_CharIterator_it_func_rewind(zend_object_iterator *iter);
static void spl_CharIterator_it_func_get_current_key(zend_object_iterator *iter, zval *key);
static void spl_CharIterator_it_func_get_current_data(zend_object_iterator *iter, zval ***data);
static int spl_CharIterator_it_func_valid(zend_object_iterator *iter);
static zend_object_iterator* spl_CharIterator_get_iterator(zend_class_entry *ce, zval *object, int by_ref TSRMLS_DC);
static void spl_CharIterator_object_dtor(void *object);
static zend_object_value spl_CharIterator_create_object(zend_class_entry *class_type TSRMLS_DC);

#endif	/* PHP_CHARIT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
