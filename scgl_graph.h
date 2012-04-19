#ifndef SCGL_GRAPH_H
#define SCGL_GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"

typedef struct scgl_edge scgl_edge_t;
typedef struct scgl_vertex scgl_vertex_t;

typedef struct scgl_graph {
	/* graph identifier */
	char *id;
	/* list of all graph vertexes */
	list_t *vertexes;
	/* list of all graph edges */
	list_t *edges;
} scgl_graph_t;


/**
 * create graph object, allocate and initialize memory
 *
 * @param id	unique graph identifier
 * @param vertexes	table of vertex objects, can be NULL
 * @param vetexes_n	vertexes table length, should be 0 if vertexes is NULL
 * @param edges	table of edge objects, can be NULL
 * @param edges_n	edges table length, should be 0 if edges is NULL
 * @return	graph object for success, NULL for failure
 */
scgl_graph_t* scgl_graph_create(char *id, scgl_vertex_t **vertexes, unsigned int vertexes_n, scgl_edge_t **edges, unsigned int edges_n);

/**
 * free memory occupied by graph and related vertex/edge objects.
 *
 * @param graph	graph object
 */
void scgl_graph_destroy(scgl_graph_t **graph);

/**
 * add vertex to existing graph object
 *
 * @param graph	graph object
 * @param vertex	vertex object
 * @return	0 for success, -1 for failure
 */
int scgl_graph_add_vertex(scgl_graph_t *graph, scgl_vertex_t *vertex);

/**
 * remove vertex from existing graph object
 * it delete all related edges (edges can't begin/end at nothing)
 * and call scgl_vertex_free()
 *
 * @param graph	graph object
 * @param vertex	vertex object
 * @see scgl_vertex_free()
 */
void scgl_graph_del_vertex(scgl_graph_t *graph, scgl_vertex_t* vertex);

/**
 * return vertex from graph using vertex identifier
 *
 * @param graph	graph object
 * @param vertex_id	vertex identifier
 * @return	vertex for success, NULL for failure
 */
scgl_vertex_t* scgl_graph_get_vertex(scgl_graph_t *graph, char *vertex_id);

/**
 * return amount of vertexes in graph
 *
 * @param graph	graph object
 * @return	amount of vertexes for success, -1 for failure
 */
int scgl_graph_get_vertex_count(const scgl_graph_t *graph);

/**
 * add edge to existing graph object
 *
 * @param graph	graph object
 * @param edge	edge object
 * @return	0 for success, -1 for failure
 */
int scgl_graph_add_edge(scgl_graph_t *graph, scgl_edge_t *edge);

/**
 * remove edge from existing graph object, and call scgl_edge_destroy()
 *
 * @param graph	graph object
 * @param edge	edge object
 * @see scgl_edge_destroy
 */
void scgl_graph_del_edge(scgl_graph_t *graph, scgl_edge_t *edge);

/**
 * return edge from graph using edge identifier
 *
 * @param graph	graph object
 * @param edge_id	edge identifier
 * @return	edge for success, NULL for failure
 */
scgl_edge_t* scgl_graph_get_edge(const scgl_graph_t *graph, const char *edge_id);

/**
 * return amount of edges in graph
 *
 * @param graph	graph object
 * @return	amount of edges for success, -1 for failure
 */
int scgl_graph_get_edge_count(const scgl_graph_t *graph);

#ifdef __cplusplus
}
#endif

#endif
