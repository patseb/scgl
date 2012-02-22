#ifndef SCGL_GRAPH_H
#define SCGL_GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"
#include "scgl_vertex.h"
#include "scgl_edges.h"

typedef struct {
	/* graph identyficator */
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
graph_t* scgl_graph_create(char *id, vertex_t **vertexes, unsigned int vertexes_n, edge_t **edges, unsigned int edges_n);

/**
 * free memory occupied by vertex object. Doesn't free vertexes and edges memory.
 *
 * @param graph	graph object
 */
void scgl_graph_destroy(graph_t *graph);

/**
 * add vertex to existing graph object
 *
 * @param graph	graph object
 * @param vertex	vertex object
 * @return	0 for success, -1 for failure
 */
int scgl_graph_add_vertex(graph_t *graph, const vertex_t *vertex);

/**
 * removes vertex from existing graph object
 *
 * @param graph	graph object
 * @param vertex_id	vertex identifier
 * @return	deleted vertex for success, NULL for failure
 */
vertex_t* scgl_graph_del_veretex(graph_t *graph, char *vertex_id);

/**
 * returns vertex from graph using vertex identifier
 *
 * @param graph	graph object
 * @param vertex_id	vertex identifier
 * @return	vertex for success, NULL for failure
 */
vertex_t* scgl_graph_get_vertex(graph_t *graph, char *vertex_id);

/**
 * returns amount of vertexes in graph
 *
 * @param graph	graph object
 * @return	amount of vertexes for success, -1 for failure
 */
int scgl_graph_get_vertex_count(const graph_t *graph);

#ifdef __cplusplus
}
#endif

#endif
