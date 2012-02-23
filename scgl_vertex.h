#ifndef SCGL_VERTEX_H
#define SCGL_VERTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"

typedef struct scgl_edge scgl_edge_t;

/* vertex object */
typedef struct scgl_vertex {
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
scgl_vertex_t* scgl_vertex_create(char *id, scgl_edge_t **in, unsigned int in_n, scgl_edge_t **out, unsigned int out_n);

/**
 * free memory occupied by vertex object
 *
 * @param vertex	vertex object
 */
void scgl_vertex_destroy(scgl_vertex_t *vertex);

/**
 * add edge to existing vertex, if edge isn't related with vertex function fails
 *
 * @param vertex	vertex object
 * @param edge	edge object
 * @return	0 for success, -1 for failure
 */
int scgl_vertex_add_edge(scgl_vertex_t *vertex, const scgl_edge_t *edge);

/**
 * remove edge from existing vertex, function also modifies edge (from/to attributes)
 *
 * @param vertex	vertex object
 * @param edge	edge object
 * @return	0 for success, -1 for failure
 */
int scgl_vertex_del_edge(scgl_vertex_t *vertex, scgl_edge_t *edge);

/**
 * count edges which are directed to vertex
 *
 * @param vertex	vertex object
 * @return	number of edges for success, -1 for failure
 */
int scgl_vertex_get_edges_in_count(const scgl_vertex_t *vertex);

/**
 * count edges which are directed out of vertex
 *
 * @param vertex	vertex object
 * @return	number of edges for success, -1 for failure
 */
int scgl_vertex_get_edges_out_count(const scgl_vertex_t *vertex);


/* internal functions section */
int scgl_vertex_seeker(const void *elem, const void *key);
int scgl_vertex_comparator(const void *a, const void *b);

#ifdef __cplusplus
}
#endif

#endif
