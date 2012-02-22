#ifndef SCGL_VERTEX_H
#define SCGL_VERTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"
#include "scgl_edge.h"

/* vertex object */
typedef struct {
	/* vertex identyficator */
	char *id;
	/* list of edges which are directed to vertex */
	list_t *in;
	/* list of edges which are directed out of vertex */
	list_t *out;
} scgl_vertex_t;

/**
 * create vertex object, allocate and initialize memory
 *
 * @param id	unique vertex identyficator
 * @param in	table of pointers to edge_t objects which are directed to vertex, can be NULL
 * @param in_n	in table length, should be 0 if 'in' is NULL
 * @param out	table of pointers to edge_t objects which are directed out of vertex, can be NULL
 * @param out_n	out table length, should be 0 if 'out' is NULL
 * @return	pointer to vertex object for success, NULL for failure
 */
vertex_t* vertex_create(char *id, edge_t **in, unsigned int in_n, edge_t **out, unsigned int out_n)

/**
 * free memory occupied by vertex object
 *
 * @param vertex	vertex object
 */
void vertex_destroy(vertex_t *vertex)

/**
 * add edge to existing vertex
 *
 * @param vertex	vertex object
 * @param edge	edge object
 * @return	0 for success, -1 for failure
 */
int vertex_add_edge(vertex_t *vertex, const edge_t *edge)

/**
 * remove edge from existing vertex, function also modifies edge (from/to pointers)
 *
 * @param vertex	vertex object
 * @param edge	edge object
 * @return	0 for success, -1 for failure
 */
int vertex_del_edge(vertex_t *vertex, edge_t *edge)

#ifdef __cplusplus
}
#endif

#endif
