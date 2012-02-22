#ifndef SCGL_VERTEX_H
#define SCGL_VERTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"
#include "scgl_edge.h"

/* vertex object */
typedef struct {
	/* vertex identifier */
	char *id;
	/* list of edges which are directed to vertex */
	list_t *in;
	/* list of edges which are directed out of vertex */
	list_t *out;
} scgl_vertex_t;

/**
 * create vertex object, allocate and initialize memory
 *
 * @param id	unique vertex identifier
 * @param in	table of edge objects which are directed to vertex, can be NULL
 * @param in_n	in table length, should be 0 if 'in' is NULL
 * @param out	table of edge objects which are directed out of vertex, can be NULL
 * @param out_n	out table length, should be 0 if 'out' is NULL
 * @return	vertex object for success, NULL for failure
 */
vertex_t* scgl_vertex_create(char *id, edge_t **in, unsigned int in_n, edge_t **out, unsigned int out_n);

/**
 * free memory occupied by vertex object
 *
 * @param vertex	vertex object
 */
void scgl_vertex_destroy(vertex_t *vertex);

/**
 * add edge to existing vertex, if edge isn't related with vertex function fails
 *
 * @param vertex	vertex object
 * @param edge	edge object
 * @return	0 for success, -1 for failure
 */
int scgl_vertex_add_edge(vertex_t *vertex, const edge_t *edge);

/**
 * remove edge from existing vertex, function also modifies edge (from/to attributes)
 *
 * @param vertex	vertex object
 * @param edge	edge object
 * @return	0 for success, -1 for failure
 */
int scgl_vertex_del_edge(vertex_t *vertex, edge_t *edge);

/**
 * count edges which are directed to vertex
 *
 * @param vertex	vertex object
 * @return	number of edges for success, -1 for failure
 */
int scgl_vertex_get_edges_in_count(const vertex_t *vertex);

/**
 * count edges which are directed out of vertex
 *
 * @param vertex	vertex object
 * @return	number of edges for success, -1 for failure
 */
int scgl_vertex_get_edges_out_count(const vertex_t *vertex);

#ifdef __cplusplus
}
#endif

#endif
