#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simclist.h"
#include "scgl_edge.h"
#include "scgl_pair.h"
#include "scgl_vertex.h"
#include "scgl_graph.h"

graph_t*
scgl_graph_create(char *id, vertex_t **vertexes, unsigned int vertexes_n, edge_t **edges, unsigned int edges_n) {
	graph_t *g;
	unsigned int i;

	g = (graph_t*) malloc(sizeof(graph_t));

	list_init(g->vertexes);
	list_init(g->edges);

	list_attributes_seeker(g->vertexes, vertex_seeker);
	list_attributes_seeker(g->edges, edge_seeker);

	list_attributes_comparator(g->vertexes, vertex_comparator);
	list_attributes_comparator(g->edges, edge_comparator);

	for (i=0; i<vertexes_n; ++i)
		list_append(g->vertexes,(void*)vertexes[i]);

	for (i=0; i<edges_n; ++i)
		list_append(g->edges, (void*)edges[i]);

	return g;
}

void
scgl_graph_destroy(graph_t *graph) {
	if (graph != NULL) {
		//deep free - todo
		list_destroy(graph->vertexes);
		list_destroy(graph->edges);
		free(graph->id);
		free(graph);
		graph = NULL;
	}
}

int
scgl_graph_add_vertex(graph_t *graph, const vertex_t *vertex) {
	if (graph == NULL || vertex == NULL)
		return -1;

	list_append(graph->vertexes, vertex);

	return 0;
}

vertex_t*
scgl_graph_del_veretex(graph_t *graph, char *vertex_id) {
	if (graph == NULL)
		return NULL;

	vertex_t *v;
	v = list_seek(graph->vertexes, vertex_id);
	if (v != NULL)
		list_delete(graph->vertexes, v);

	//problem jest taki ze, usuwając node z grafu nie musimy usuwać krawędzi,
	//ale powinniśmy dereference, ale to zaś "psuje" edge bo co to za edge bez reference,
	//moze zamiast dereference usuwac edge z graph - ale to bez sensu
	return v;
}

vertex_t*
scgl_graph_get_vertex(graph_t *graph, char *vertex_id) {
	if (graph == NULL || vertex_id == NULL)
		return NULL;
	return list_seek(graph->vertexes, vertex_id);
}

int
scgl_graph_get_vertex_count(const graph_t *graph) {
	if (graph == NULL)
		return -1;
	return list_size(graph->vertexes);
}

int
scgl_graph_add_edge(graph_t *graph, const edge_t *edge) {
	if (graph == NULL || edge == NULL)
		return -1;

	list_append(graph->edges, edge);
	return 0;
}
