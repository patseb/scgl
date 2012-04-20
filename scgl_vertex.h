#ifndef SCGL_VERTEX_H
#define SCGL_VERTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"

typedef struct scgl_edge scgl_edge_t;
typedef struct scgl_graph scgl_graph_t;

/**
 * a function for operate at vertex's edges
 *
 * Edge function will be called by foreach edge loop at specified vertex.
 *
 * @param edge  reference for edge object
 * @data    reference for additional data, or result storing
 *
 * @see scgl_vertex_foreach_edge()
 */
typedef void (*edge_foreach_function)(scgl_edge_t *edge, void *data);

/* vertex object */
typedef struct scgl_vertex {
	/* vertex identifier */
	char *id;
	/* list of edges which are directed to vertex */
	list_t *in;
	/* list of edges which are directed out of vertex */
	list_t *out;
	/* pointer to graph object which contains that vertex */
	scgl_graph_t *owner;
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
 * remove relation between vertex and edge, but doesn't free edge object
 * 
 * @param vertex	vertex object
 */
void scgl_vertex_destroy(scgl_vertex_t **vertex);

/**
 * add edge to existing vertex, function modify edge from/to attributes according to direction parameter
 *
 * @param vertex	vertex object
 * @param edge	edge object
 * @param endpoint 0 means edit 'from' edge's attribute, 1 means edit 'to' edge's attribute, doesn't matter when edge is undirected
 * @return	0 for success, -1 for failure
 */
int scgl_vertex_add_edge(scgl_vertex_t *vertex, scgl_edge_t *edge, unsigned int endpoint);

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

/**
 * retrun an incoming (to vertex) edge at a given position
 *
 * @param vertex	vertex object
 * @param i [0, edges_in_count-1] position index of the element
 * @return	reference to edge, or NULL for failure
 *
 * @see scgl_vertex_get_edges_in_count()
 */
scgl_edge_t* scgl_vertex_get_edge_in_at(const scgl_vertex_t *vertex, unsigned int i);

/**
 * retrun an outgoing (from vertex) edge at a given position
 *
 * @param vertex	vertex object
 * @param i [0, edges_out_count-1] position index of the element
 * @return	reference to edge, or NULL for failure
 *
 * @see scgl_vertex_get_edges_out_count()
 */
scgl_edge_t* scgl_vertex_get_edge_out_at(const scgl_vertex_t *vertex, unsigned int i);

/**
 * call fun function for every edge in vertex
 *
 * @param vertex    reference to vertex object
 * @param direction 0 for incoming edges, 1 for outgoing edges
 * @param fun   reference to the called function
 * @param result    reference to user data
 */
void scgl_vertex_foreach_edge(const scgl_vertex_t *vertex, unsigned int direction, edge_foreach_function fun, void *data);

/**
 * print vertex object to stream
 *
 * @param vertex    reference to vertex object
 * @param fp    object containing information to control a stream
 */
void scgl_vertex_dump(scgl_vertex_t *vertex, FILE *fp);

/* internal functions section */
int scgl_vertex_seeker(const void *elem, const void *key);
int scgl_vertex_comparator(const void *a, const void *b);
static void scgl_vertex_dump_edge(scgl_edge_t* edge, void *data);


#ifdef __cplusplus
}
#endif

#endif
