#ifndef SCGL_ATTR_H
#define SCGL_ATTR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include "scgl_def.h"
#include "scgl_edge.h"

struct scgl_attr {
	/** list head which will be connected with attribute owner list */
	list_head_t list;
	/** attribute key */
	char *key;
	/** attribute value */
	void *value;
};

/**
 * create attribute object, allocate and initialize memory
 *
 * @param key	unique identifier for value
 * @param value	value indexed by key
 * @return	attribute object for success, NULL for failure
 */
scgl_attr_t* scgl_attr_create(char *key, void *value);

/**
 * free memory occupied by attribute object, calling user attr_free_function
 * function set pointers to key/value to NULL
 *
 * @param attr	attribute object
 * @param fun   user function which will free key/value memory
 */
void scgl_attr_destroy(scgl_attr_t **attr, attr_function fun);

/**
 * return key argument from attribute object
 *
 * @param attr    reference to attribute object
 * @return reference to key, NULL for failure
 */
char* scgl_attr_get_key(const scgl_attr_t* attr);

/**
 * return value argument from attribute object
 *
 * @param attr    reference to attribute object
 * @return reference to value, NULL for failure
 */
void* scgl_attr_get_value(const scgl_attr_t* attr);

#ifdef __cplusplus
}
#endif

#endif
