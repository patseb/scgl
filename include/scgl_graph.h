#ifndef SCGL_GRAPH_H
#define SCGL_GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scgl_edge.h"
#include "scgl_def.h"

/** graph object */
struct scgl_graph {
	/** graph identifier */
	char *id;
	/** list of all graph vertexes */
	list_head_t vertexes;
	/** list of all graph edges */
	list_head_t edges;
};

/**
 * create graph object, allocate and initialize memory
 *
 * @param id	unique graph identifier
 * @param vertexes	table of vertex objects, can be NULL
 * @param vertexes_n	vertexes table length, should be 0 if vertexes is NULL
 * @param edges	table of edge objects, can be NULL
 * @param edges_n	edges table length, should be 0 if edges is NULL
 * @return	graph object for success, NULL for failure
 */
scgl_graph_t* scgl_graph_create(char *id, scgl_vertex_t **vertexes, unsigned int vertexes_n, scgl_edge_t **edges, unsigned int edges_n);

/**
 * free memory occupied by graph and related vertex/edge objects.
 * id memory will be freed
 *
 * @param graph	graph object
 * @param fun   user function which will free memory occupied by edge's attributes
 */
void scgl_graph_destroy(scgl_graph_t **graph, attr_function fun);

/**
 * copy graph object, all graph's vertexes and edges are copied too (their ids and attributes too)
 *
 * @param graph reference to graph object
 * @param fun   function which will copy each edge attribute, store new scgl_attr_t in data parameter
 * @return reference to copied graph or NULL for failure
 */
scgl_graph_t* scgl_graph_copy(const scgl_graph_t *graph, attr_function fun);

/**
 * return graph's id
 *
 * @param graph  reference to graph object
 * @return  graph's id or NULL for failure
 *      */
char* scgl_graph_get_id(const scgl_graph_t *graph);

/**
 * set graph's id
 * functions copy string content
 *
 * @param graph  reference to graph object
 * @param id    new id
 */
void scgl_graph_set_id(scgl_graph_t *graph, char *id);

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
 * @param fun   user function which will free memory occupied by edge's attriubtes (called when destroying edges)
 * @see scgl_vertex_free()
 */
void scgl_graph_del_vertex(scgl_graph_t *graph, scgl_vertex_t **vertex, attr_function fun);

/**
 * return vertex from graph using vertex identifier
 *
 * @param graph	graph object
 * @param vertex_id	vertex identifier
 * @return	vertex for success, NULL for failure
 */
scgl_vertex_t* scgl_graph_get_vertex(const scgl_graph_t *graph, const char *vertex_id);

/**
 * return an vertex at give position
 *
 * @param graph reference to graph object
 * @param i [0, vertex_count-1] position index of the element
 * @return  reference to vertex or NULL for failure
 *
 * @see scgl_graph_get_edge_count()
 */
scgl_vertex_t* scgl_graph_get_vertex_at(const scgl_graph_t *graph, unsigned int i);

/**
 * return amount of vertexes in graph
 *
 * @param graph	graph object
 * @return	amount of vertexes for success, 0 for failure
 */
unsigned int scgl_graph_get_vertexes_count(const scgl_graph_t *graph);

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
 * @param fun   user function which will free memory occupied by edge's attributes
 * @see scgl_edge_destroy
 */
void scgl_graph_del_edge(scgl_graph_t *graph, scgl_edge_t **edge, attr_function fun);

/**
 * return an edge at give position
 *
 * @param graph reference to graph object
 * @param i [0, edges_count-1] position index of the element
 * @return  reference to edge or NULL for failure
 *
 * @see scgl_graph_get_edge_count()
 */
scgl_edge_t* scgl_graph_get_edge_at(const scgl_graph_t *graph, unsigned int i);

/**
 * return amount of edges in graph
 *
 * @param graph	graph object
 * @return	amount of edges for success, 0 for failure
 */
unsigned int scgl_graph_get_edges_count(const scgl_graph_t *graph);

/**
 * print graph object to stream
 *
 * @param graph reference to graph object
 * @param fp    object containing information to control a stream
 * @param fun function to print edge's attributes
 */
void scgl_graph_dump(scgl_graph_t *graph, FILE *fp, attr_function fun);

#ifdef __cplusplus
}
#endif

#endif
