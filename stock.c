/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 321634 2012-01-01 13:15:04Z felipe $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_stock.h"

/* If you declare any globals in php_stock.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(stock)
*/
ZEND_DECLARE_MODULE_GLOBALS(stock);
/* True global resources - no need for thread safety here */
static int le_stock;

/* {{{ stock_functions[]
 *
 * Every user visible function must have an entry in stock_functions[].
 */
const zend_function_entry stock_functions[] = {
	PHP_FE(stock_extract_code,	NULL)		/* For testing, remove later. */
	PHP_FE(stock_extract_name,	NULL)		/* For testing, remove later. */
	{NULL, NULL, NULL}
};
/* }}} */

/* {{{ stock_module_entry
 */
zend_module_entry stock_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"stock",
	stock_functions,
	PHP_MINIT(stock),
	PHP_MSHUTDOWN(stock),
	PHP_RINIT(stock),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(stock),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(stock),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_STOCK
ZEND_GET_MODULE(stock)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("stock.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_stock_globals, stock_globals)
    STD_PHP_INI_ENTRY("stock.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_stock_globals, stock_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_stock_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_stock_init_globals(zend_stock_globals *stock_globals)
{
	stock_globals->global_value = 0;
	stock_globals->global_string = NULL;
}
*/
/* }}} */
static void stock_globals_ctor(zend_stock_globals *stock_globals TSRMLS_DC)
{
        FILE *fp;
        char code[6];
        char name[13];
        stock *list, *rear, *p;
        list = pemalloc(sizeof(stock), 1);
        fp = fopen("stock", "rb");
        rear = list;
        rear->next = NULL;
        while (!feof(fp)) {
                fscanf(fp, "%s%s", code, name);
                p = pemalloc(sizeof(stock), 1);
                p->code = pestrdup(code, 1);
                p->name = pestrdup(name, 1);
                p->next = NULL;
                rear->next = p;
                rear = p;
        }
        fclose(fp);
        stock_globals->list = list;
}

static void stock_globals_dtor(zend_stock_globals *stock_globals TSRMLS_DC)
{
	stock->list = NULL;
}
/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(stock)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
        #ifdef ZTS
                ts_allocate_id(stock_global_id, 4, stock_globals_ctor, stock_globals_dtor);
        #else
                stock_globals_ctor(&stock_globals TSRMLS_DC);
        #endif	
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(stock)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(stock)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(stock)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(stock)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "stock support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/**
	extract stock code from content
*/
PHP_FUNCTION(stock_extract_code)
{
        stock *list, *p;
        char *str;
        int str_len;
        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &str_len) == FAILURE) {
                return;
        }
        list = stock_globals.list;
        p = list->next;
        while (p) {
                if (strstr(str, p->code))
                        RETURN_STRING(p->code, 1);
                p = p->next;
        }
        RETURN_NULL();
}
/**
	extract stock name from content
*/

PHP_FUNCTION(stock_extract_name)
{
        stock *list, *p;
        char *str;
        int str_len;
        if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &str_len) == FAILURE) {
                return;
        }
        list = stock_globals.list;
        p = list->next;
        while (p) {
                if (strstr(str, p->name))
                        RETURN_STRING(p->name, 1);
                p = p->next;
        }
        RETURN_NULL();
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
