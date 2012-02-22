#ifndef SCGL_EDGE_H
#define SCGL_EDGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"
#include "scgl_vertex.h"
#include "scgl_pair.h"

typedef struct {
	/* edge identifier */
	char *id;
	/* 0 - edge is undirected, edge is 1 directed */
	int is_directed;
	double weight;
	/* edge source vertex */
	scgl_vertex_t *from;
	/* edge destination vertex */
	scgl_vertex_t *to;
	/* user-purpose list of edge attributes */
	list_t *attributes;
} scgl_edge_t;

/**
 * create edge object, allocate and initialize memory
 *
 * @param id	unique edge identifier
 * @param from	edge source (vertex object)
 * @param from	edge destination (vertex object)
 * @param is_directed 1 means that edge is directed, 0 opposite
 * @param weight	edge weight
 * @param attr	table of pair objects, user-purpose attributes
 * @param attr_n	lenght of attributes table
 * @return	edge object for success, NULL for failure
 */
edge_t* scgl_edge_create(char *id, vertex_t *from, vertex_t *to, int is_directed, double weight, pair_t **attr, unsigned int attr_n);

/**
 * free memory occupied by edge object
 *
 * @param edge	edge object
 */
void scgl_edge_destroy(edge_t *edge);

/**
 * add new attribute to existing edge
 *
 * @param edge	edge object
 * @param key	unique key for indexing attribute
 * @param value	value to be added
 */
void scgl_edge_add_attribute(edge_t *edge, const char *key, void *value);

/**
 * get attribute's value for specified key
 *
 * @param edge	edge object
 * @param key	key corresponding to the requested value
 * @return	value for success, NULL for failure
 */
void* scgl_edge_get_attribute(edge_t *edge, const char *key);

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

#ifdef __cplusplus
}
#endif

#endif
