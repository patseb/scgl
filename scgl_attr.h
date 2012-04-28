#ifndef SCGL_ATTR_H
#define SCGL_ATTR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include "scgl_def.h"
#include "scgl_edge.h"

struct scgl_attr {
	list_head_t list;
	char *key;
	void *value;
};

/**
 * create attr object, allocate and initialize memory
 *
 * @param key	unique identifier for value
 * @param value	value indexed by key
 * @return	attr object for success, NULL for failure
 */
scgl_attr_t* scgl_attr_create(char *key, void *value);

/**
 * free memory occupied by attr object
 *
 * @param attr	attr object
 * @param fun   function which will free value memory
 */
void scgl_attr_destroy(scgl_attr_t **attr, attr_free_function fun);

/**
 * return key argument from attr object
 *
 * @attr    reference to attr object
 * @return reference to key, NULL for failure
 */
char* scgl_attr_get_key(const scgl_attr_t* attr);

/**
 * return value argument from attr object
 *
 * @attr    reference to attr object
 * @return reference to value, NULL for failure
 */
void* scgl_attr_get_value(const scgl_attr_t* attr);

/* internal functions section */
int scgl_attr_comparator(const void *a, const void *b);

#ifdef __cplusplus
}
#endif

#endif
