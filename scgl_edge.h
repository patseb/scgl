#ifndef SCGL_EDGE_H
#define SCGL_EDGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"

typedef struct scgl_pair scgl_pair_t;
typedef struct scgl_vertex scgl_vertex_t;

typedef struct scgl_edge {
	/* edge identifier */
	char *id;
	/* 0 - edge is undirected, edge is 1 directed */
	int is_directed;
	double weight;
	/* edge source vertex */
	scgl_vertex_t *from;
	/* edge destination vertex */
	scgl_vertex_t *to;
	/* user-purpose list of edge attributes (pair_t objects) */
	list_t *attributes;
} scgl_edge_t;

/**
 * create edge object, allocate and initialize memory
 *
 * @param id	unique edge identifier
 * @param from	edge source (vertex object)
 * @param to	edge destination (vertex object)
 * @param is_directed 1 means that edge is directed, 0 opposite
 * @param weight	edge weight
 * @param attr	table of pair objects, user-purpose attributes
 * @param attr_n	lenght of attributes table
 * @return	edge object for success, NULL for failure
 */
scgl_edge_t* scgl_edge_create(char *id, scgl_vertex_t *from, scgl_vertex_t *to, int is_directed, double weight, scgl_pair_t **attr, unsigned int attr_n);

/**
 * free memory occupied by edge object
 *
 * @param edge	edge object
 * @param fun   pointer to function which will free memory occupied by attribute value
 */
void scgl_edge_destroy(scgl_edge_t *edge, attr_free_function fun);

/**
 * modify edge 'from/to' attribute, function removes relation between edge and old vertex
 *
 * @param edge	edge object
 * @param vertex	vertex
 * @param direction	0 means edit 'from' attribute, 1 means edit 'to' attribute
 */
void scgl_edge_set_vertex(scgl_edge_t *edge, scgl_vertex_t *vertex, const unsigned int direction);

/**
 * add new attribute to existing edge
 *
 * @param edge	edge object
 * @param key	unique key for indexing attribute
 * @param value	value to be added
 */
void scgl_edge_add_attribute(scgl_edge_t *edge, const char *key, void *value);

/**
 * get attribute's value for specified key
 *
 * @param edge	edge object
 * @param key	key corresponding to the requested value
 * @return	value for success, NULL for failure
 */
void* scgl_edge_get_attribute(scgl_edge_t *edge, const char *key);

/**
 * a function for operate at attributes
 *
 * Attribute function will be called by foreach attribute loop at specified edge.
 * It can eg. sum values of all attributes and set edge weight field.
 *
 * @param key	reference for key attribute
 * @param value	reference for value attribute
 * @param result reference for result storing
 *
 * @see scgl_edge_foreach_attribute()
 */
typedef void (*attr_function)(char *key, void *value, void *result);

/**
 * a function for free occupied memory by attribute values
 *
 * Attribute function will be called by foreach attribute loop at specified edge.
 * Attribute key will be free by scgl_edge_destroy() function.
 *
 * @param key	reference for key attribute
 * @param value	reference for value attribute
 *
 * @see scgl_edge_destroy()
 */
typedef void (*attr_free_function)(char *key, void *value);

/**
 * call attr_function for every attribute of edge
 *
 * @param edge	edge object
 * @param fun	pointer to the called function
 * @param result reference to called function result
 */
void scgl_edge_foreach_attribute(scgl_edge_t *edge, attr_function fun, void *result);

/* internal functions section */
int scgl_edge_seeker(const void *elem, const void *key);
int scgl_edge_comparator(const void *a, const void *b);

#ifdef __cplusplus
}
#endif

#endif
