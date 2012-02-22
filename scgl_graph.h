#ifndef SCGL_GRAPH_H
#define SCGL_GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"
#include "scgl_vertex.h"
#include "scgl_edges.h"

typedef struct {
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
 * free memory occupied by vertex object. Doesn't free vertexes and edges memory.
 *
 * @param graph	graph object
 */
void scgl_graph_destroy(scgl_graph_t *graph);

/**
 * add vertex to existing graph object
 *
 * @param graph	graph object
 * @param vertex	vertex object
 * @return	0 for success, -1 for failure
 */
int scgl_graph_add_vertex(scgl_graph_t *graph, const scgl_vertex_t *vertex);

/**
 * remove vertex from existing graph object
 *
 * @param graph	graph object
 * @param vertex_id	vertex identifier
 * @return	deleted vertex for success, NULL for failure
 */
scgl_vertex_t* scgl_graph_del_veretex(scgl_graph_t *graph, char *vertex_id);

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
int scgl_graph_add_edge(scgl_graph_t *graph, const scgl_edge_t *edge);

/**
 * remove edge from existing graph object
 *
 * @param graph	graph object
 * @param edge_id	edge identifier
 * @return	deleted edge for success, NULL for failure
 */
scgl_edge_t* scgl_graph_del_edge(scgl_graph_t *graph, const char *edge_id);

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
