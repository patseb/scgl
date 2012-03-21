#ifndef SCGL_PAIR_H
#define SCGL_PAIR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scgl_edge.h"

typedef struct scgl_pair {
	char *key;
	void *value;
} scgl_pair_t;

/**
 * create pair object, allocate and initialize memory
 *
 * @param key	unique identifier for value
 * @param value	value indexed by key
 * @return	pair object for success, NULL for failure
 */
scgl_pair_t* scgl_pair_create(const char *key, void *value);

/**
 * free memory occupied by pair object
 *
 * @param pair	pair object
 * @param fun   function which will free value memory
 */
void scgl_pair_destroy(scgl_pair_t *pair, attr_free_function fun);

/* internal functions section */
int scgl_pair_seeker(const void *elem, const void *key);
int scgl_pair_comparator(const void *a, const void *b);

#ifdef __cplusplus
}
#endif

#endif
