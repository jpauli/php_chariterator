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

#ifndef CHARIT_INTERNAL_H_
#define CHARIT_INTERNAL_H_

#include "zend_API.h"
#include "charit_utils.h"

void spl_CharIterator_it_func_dtor(zend_object_iterator *iter);
void spl_CharIterator_it_func_move_forward(zend_object_iterator *iter);
void spl_CharIterator_it_func_rewind(zend_object_iterator *iter);
int spl_CharIterator_it_func_get_current_key(zend_object_iterator *iter, char **str_key, uint *str_key_len, ulong *int_key);
void spl_CharIterator_it_func_get_current_data(zend_object_iterator *iter, zval ***data);
int spl_CharIterator_it_func_valid(zend_object_iterator *iter);

extern zend_object_handlers spl_CharIterator_object_handlers;

typedef struct _charit_object {
	zend_object zobj;
	zval *charval;
	ulong chunk_size;
	uint offset;
	uint max_offset;
} charit_object;

typedef struct _charit_object_iterator {
	zend_object_iterator zit;
	zval **previous_val;
} charit_object_iterator;

#endif /* CHARIT_INTERNAL_H_ */
