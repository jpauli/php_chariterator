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

#include "charit_internal.h"

static zend_object_iterator_funcs spl_CharIterator_it_funcs = {
		spl_CharIterator_it_func_dtor,
		spl_CharIterator_it_func_valid,
		spl_CharIterator_it_func_get_current_data,
		spl_CharIterator_it_func_get_current_key,
		spl_CharIterator_it_func_move_forward,
		spl_CharIterator_it_func_rewind
};

PHP_CHARIT_API void spl_CharIterator_it_func_dtor(zend_object_iterator *iter)
{
	charit_object_iterator *charit = (charit_object_iterator *) iter;
	zval_ptr_dtor((zval **)(&((charit_object *)charit->zit.data)->charval));
	if (charit->previous_val) {
		zval_ptr_dtor(charit->previous_val);
		efree(charit->previous_val);
	}
	efree(charit);
}

PHP_CHARIT_API void spl_CharIterator_it_func_move_forward(zend_object_iterator *iter)
{

}

PHP_CHARIT_API void spl_CharIterator_it_func_rewind(zend_object_iterator *iter)
{
	iter->index = 0;
}

PHP_CHARIT_API int spl_CharIterator_it_func_get_current_key(zend_object_iterator *iter,  char **str_key, uint *str_key_len, ulong *int_key)
{
	*int_key = iter->index;

	return HASH_KEY_IS_LONG;
}

PHP_CHARIT_API void spl_CharIterator_it_func_get_current_data(zend_object_iterator *iter, zval ***data)
{
	zval **zv = (zval **)emalloc(sizeof(zval *));
	charit_object_iterator *charit = (charit_object_iterator *) iter;
	ALLOC_INIT_ZVAL(*zv);
	size_t size_to_copy;
	size_to_copy = FETCH_CHARIT_OBJECT_PROP(iter, chunk_size); /* default */

	if (iter->index == FETCH_CHARIT_OBJECT_PROP(iter, max_offset)) {
		size_to_copy = Z_STRLEN_P(FETCH_CHARIT_OBJECT_PROP(iter, charval)) - FETCH_CHARIT_OBJECT_PROP(iter, max_offset) * FETCH_CHARIT_OBJECT_PROP(iter, chunk_size);
	}

	ZVAL_STRINGL(*zv, (Z_STRVAL_P((zval *)(FETCH_CHARIT_OBJECT_PROP(iter, charval))) + iter->index * FETCH_CHARIT_OBJECT_PROP(iter, chunk_size)), size_to_copy , 1);
	*data = zv; /* Iterator will increment refcount, let it do it */
	if (charit->previous_val) {
		zval_ptr_dtor(charit->previous_val);
		efree(charit->previous_val);
	}
	charit->previous_val = zv;
}

PHP_CHARIT_API int spl_CharIterator_it_func_valid(zend_object_iterator *iter)
{
	return iter->index <= FETCH_CHARIT_OBJECT_PROP(iter, max_offset) ? SUCCESS : FAILURE;
}

PHP_CHARIT_API zend_object_iterator* spl_CharIterator_get_iterator(zend_class_entry *ce, zval *object, int by_ref TSRMLS_DC)
{
	charit_object_iterator * it;
	it = (charit_object_iterator *)emalloc(sizeof(charit_object_iterator));
	it->zit.data = zend_object_store_get_object(object);
	Z_ADDREF_P((zval *)((charit_object *)it->zit.data)->charval);
	it->zit.funcs = &spl_CharIterator_it_funcs;
	it->previous_val = NULL;
	return (zend_object_iterator *) it;
}

PHP_CHARIT_API void spl_CharIterator_object_dtor(void *object)
{
	charit_object *myobject = (charit_object *)object;
	if (myobject->charval) {
		zval_ptr_dtor(&myobject->charval);
	}
	zend_object_std_dtor(&myobject->zobj);
	efree(object);
}

PHP_CHARIT_API zend_object_value spl_CharIterator_create_object(zend_class_entry *class_type TSRMLS_DC)
{
	zend_object_value object;
	charit_object *myobject;

	myobject = (charit_object *)ecalloc(1 , sizeof(charit_object));
	memset(myobject, 0, sizeof(charit_object));
	myobject->offset = 0;

	zend_object_std_init(&myobject->zobj, class_type);
	object_properties_init(&myobject->zobj, class_type);

	object.handle = zend_objects_store_put(myobject, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t)spl_CharIterator_object_dtor, NULL TSRMLS_CC);
	object.handlers = &spl_CharIterator_object_handlers;

	return object;
}
