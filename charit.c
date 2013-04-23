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

/* If you declare any globals in php_charit.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(charit)
*/

/* True global resources - no need for thread safety here */
static int le_charit;

/* {{{ charit_functions[]
 *
 * Every user visible function must have an entry in charit_functions[].
 */
const zend_function_entry charit_functions[] = {
	PHP_FE_END	/* Must be the last line in charit_functions[] */
};
/* }}} */

SPL_METHOD(SplCharIterator, __construct)
{
	charit_object *obj;
	zval *val;
	obj = (charit_object *)zend_object_store_get_object(getThis());

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &val) == FAILURE) {
		return;
	}
	obj->charval = val;
	Z_ADDREF_P(val);
}

SPL_METHOD(SplCharIterator, valid)
{
	charit_object *obj;
	obj = (charit_object *)zend_object_store_get_object(getThis());

	RETVAL_BOOL(obj->offset < Z_STRLEN_P(obj->charval));
}

SPL_METHOD(SplCharIterator, next)
{
	charit_object *obj;
	obj = (charit_object *)zend_object_store_get_object(getThis());

	obj->offset++;
}

SPL_METHOD(SplCharIterator, key)
{
	charit_object *obj;
	obj = (charit_object *)zend_object_store_get_object(getThis());

	RETVAL_LONG((long)obj->offset);
}

SPL_METHOD(SplCharIterator, rewind)
{
	charit_object *obj;
	obj = (charit_object *)zend_object_store_get_object(getThis());

	obj->offset = 0;
}

SPL_METHOD(SplCharIterator, current)
{
	charit_object *obj;
	zval *zv;
	obj = (charit_object *)zend_object_store_get_object(getThis());

	ALLOC_INIT_ZVAL(zv);

	zv->type = IS_STRING;
	Z_STRVAL_P(zv) = emalloc(2);
	Z_STRVAL_P(zv)[0] = Z_STRVAL_P(obj->charval)[obj->offset];
	Z_STRVAL_P(zv)[1] = '\0';
	Z_STRLEN_P(zv) = 1;

	RETVAL_ZVAL(zv, 1, 1);
}

ZEND_BEGIN_ARG_INFO(arginfo_splchariterator___construct, 0)
	ZEND_ARG_INFO(0, string)
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

static void spl_CharIterator_it_func_dtor(zend_object_iterator *iter)
{
	charit_object_iterator *charit = (charit_object_iterator *) iter;
	int i;
	zval_ptr_dtor((zval **)(&charit->zit.data));
	for(i=0; i<charit->buf_size; i++) {
		if (charit->buf[i]) {
			zval_ptr_dtor(charit->buf[i]);
			efree(charit->buf[i]);
		}
	}
	efree(charit->buf);
	efree(charit);
}

static void spl_CharIterator_it_func_move_forward(zend_object_iterator *iter)
{

}

static void spl_CharIterator_it_func_rewind(zend_object_iterator *iter)
{
	iter->index = 0;
}

static void spl_CharIterator_it_func_get_current_key(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, iter->index);
}

static void spl_CharIterator_it_func_get_current_data(zend_object_iterator *iter, zval ***data)
{
	zval **zv = (zval **)emalloc(sizeof(zval *));
	charit_object_iterator *charit = (charit_object_iterator *) iter;
	ALLOC_INIT_ZVAL(*zv);
	(*zv)->type = IS_STRING;
	(*zv)->value.str.len = 1;
	(*zv)->value.str.val = (char *)emalloc(2);
	(*zv)->value.str.val[0] = Z_STRVAL_P((zval *)iter->data)[iter->index];
	(*zv)->value.str.val[1] = '\0';
	*data = zv; /* Iterator will increment refcount, let it do it */

	if (iter->index == charit->buf_size) {
		charit->buf_size *= 2; /* double size, why not? */
		charit->buf = (zval ***)erealloc(charit->buf, charit->buf_size * sizeof(zval **));
		void *buf = (void *)charit->buf;
		memset(charit->buf+iter->index, 0, (charit->buf_size-iter->index) * sizeof(zval **));
	}
	charit->buf[iter->index] = zv;
}

static int spl_CharIterator_it_func_valid(zend_object_iterator *iter)
{
	return iter->index < Z_STRLEN_P((zval *)iter->data) ? SUCCESS : FAILURE;
}

static zend_object_iterator_funcs spl_CharIterator_it_funcs = {
		spl_CharIterator_it_func_dtor,
		spl_CharIterator_it_func_valid,
		spl_CharIterator_it_func_get_current_data,
		spl_CharIterator_it_func_get_current_key,
		spl_CharIterator_it_func_move_forward,
		spl_CharIterator_it_func_rewind
};

static zend_object_iterator* spl_CharIterator_get_iterator(zend_class_entry *ce, zval *object, int by_ref TSRMLS_DC)
{
	charit_object_iterator * it;
	it = (charit_object_iterator *)emalloc(sizeof(charit_object_iterator));
	it->zit.data = (void *)((charit_object *)zend_object_store_get_object(object))->charval;
	Z_ADDREF_P((zval *)it->zit.data);
	it->zit.funcs = &spl_CharIterator_it_funcs;
	it->buf = (zval ***)ecalloc(CHARIT_DEFAULT_BUFFER_SIZE, sizeof(zval **));
	it->buf_size = CHARIT_DEFAULT_BUFFER_SIZE;
	return (zend_object_iterator *) it;
}

static void spl_CharIterator_object_dtor(void *object)
{
	charit_object *myobject = (charit_object *)object;
	zval_ptr_dtor(&myobject->charval);
	zend_object_std_dtor(&myobject->zobj);
	efree(object);
}

static zend_object_value spl_CharIterator_create_object(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value object;
	charit_object *myobject;

	myobject = (charit_object *)ecalloc(1 , sizeof(charit_object));
	myobject->offset = 0;

	zend_object_std_init(&myobject->zobj, class_type);
	object_properties_init(&myobject->zobj, class_type);

	object.handle = zend_objects_store_put(myobject, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t)spl_CharIterator_object_dtor, NULL TSRMLS_CC);
	object.handlers = &spl_CharIterator_object_handlers;

	return object;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
