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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_charit.h"
#include "charit_internal.h"
/* If you declare any globals in php_charit.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(charit)
*/

static const zend_function_entry charit_functions[] = {
	PHP_FE_END
};



SPL_METHOD(SplCharIterator, __construct)
{
	zval *val;
	long chunk;
	FETCH_OBJECT

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z|l", &val, &chunk) == FAILURE) {
		return;
	}
	if (ZEND_NUM_ARGS() == 1) {
		chunk = 1;
	}
	if (chunk > Z_STRLEN_P(val)) {
		zend_throw_exception(spl_ce_OutOfRangeException, "Chunk is larger than string length", 0L);
		return;
	}
	if (chunk < 0) {
		zend_throw_exception(spl_ce_OutOfRangeException, "Chunk size must be positive", 0L);
		return;
	}
	obj->charval    = val;
	obj->chunk_size = chunk;
	obj->max_offset = Z_STRLEN_P(val) / obj->chunk_size + (Z_STRLEN_P(val) % obj->chunk_size ? 1 : 0) - 1;

	Z_ADDREF_P(val);
}

SPL_METHOD(SplCharIterator, valid)
{
	FETCH_OBJECT

	RETVAL_BOOL(obj->offset <= obj->max_offset);
}

SPL_METHOD(SplCharIterator, next)
{
	FETCH_OBJECT

	obj->offset++;
}

SPL_METHOD(SplCharIterator, key)
{
	FETCH_OBJECT

	RETVAL_LONG(obj->offset);
}

SPL_METHOD(SplCharIterator, rewind)
{
	FETCH_OBJECT

	obj->offset = 0;
}

SPL_METHOD(SplCharIterator, current)
{
	FETCH_OBJECT

	size_t size_to_copy;
	size_to_copy = obj->chunk_size; /* default */

	if (obj->offset == obj->max_offset) {
		size_to_copy = Z_STRLEN_P(obj->charval) - obj->max_offset * obj->chunk_size;
	}

	RETURN_STRINGL(Z_STRVAL_P(obj->charval) + obj->offset * obj->chunk_size, size_to_copy, 1)
}

ZEND_BEGIN_ARG_INFO(arginfo_splchariterator___construct, 0)
	ZEND_ARG_INFO(0, string)
	ZEND_ARG_INFO(0, chunk_length)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_splchariterator_key, 0)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_splchariterator_current, 0)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_splchariterator_next, 0)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_splchariterator_rewind, 0)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_splchariterator_valid, 0)
ZEND_END_ARG_INFO()

static const zend_function_entry spl_CharIterator_functions[] = {
	SPL_ME(SplCharIterator, __construct,   arginfo_splchariterator___construct, ZEND_ACC_PUBLIC)
	SPL_ME(SplCharIterator, key,   arginfo_splchariterator_key, ZEND_ACC_PUBLIC)
	SPL_ME(SplCharIterator, current,   arginfo_splchariterator_current, ZEND_ACC_PUBLIC)
	SPL_ME(SplCharIterator, next,   arginfo_splchariterator_next, ZEND_ACC_PUBLIC)
	SPL_ME(SplCharIterator, rewind,   arginfo_splchariterator_rewind, ZEND_ACC_PUBLIC)
	SPL_ME(SplCharIterator, valid,   arginfo_splchariterator_valid, ZEND_ACC_PUBLIC)
	PHP_FE_END
};

/* {{{ charit_module_entry
 */
zend_module_entry charit_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"charit",
	charit_functions,
	PHP_MINIT(charit),
	PHP_MSHUTDOWN(charit),
	PHP_RINIT(charit),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(charit),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(charit),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_CHARIT
ZEND_GET_MODULE(charit)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("charit.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_charit_globals, charit_globals)
    STD_PHP_INI_ENTRY("charit.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_charit_globals, charit_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_charit_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_charit_init_globals(zend_charit_globals *charit_globals)
{
	charit_globals->global_value = 0;
	charit_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(charit)
{
	REGISTER_SPL_STD_CLASS_EX(CharIterator, spl_CharIterator_create_object, spl_CharIterator_functions)
	memcpy(&spl_CharIterator_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	spl_ce_CharIterator->get_iterator = spl_CharIterator_get_iterator;
	zend_class_implements(spl_ce_CharIterator, 1, zend_ce_iterator);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(charit)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(charit)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(charit)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(charit)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "charit support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
