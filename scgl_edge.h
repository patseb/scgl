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
 * @param attr	table of pointer to pair objects, user-purpose attributes
 * @param attr_n	lenght of attributes table
 * @return	pointer to edge object for success, NULL for failure
 */
edge_t* edge_create(char *id, vertex_t *from, vertex_t *to, int is_directed, double weight, pair_t **attr, unsigned int attr_n);

#ifdef __cplusplus
}
#endif

#endif
