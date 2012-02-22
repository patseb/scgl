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
