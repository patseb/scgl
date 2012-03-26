#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "simclist.h"
#include "scgl_edge.h"
#include "scgl_pair.h"
#include "scgl_vertex.h"
#include "scgl_graph.h"

scgl_graph_t*
scgl_graph_create(char *id, scgl_vertex_t **vertexes, unsigned int vertexes_n, scgl_edge_t **edges, unsigned int edges_n) {
	scgl_graph_t *g;
	unsigned int i;

	g = (scgl_graph_t*) malloc(sizeof(scgl_graph_t));
	g->id = (char*) malloc(strlen(id)+1);
	strcpy(g->id, id);

	g->vertexes = (list_t*) malloc(sizeof(list_t));
	g->edges = (list_t*) malloc(sizeof(list_t));

	list_init(g->vertexes);
	list_init(g->edges);

	list_attributes_seeker(g->vertexes, scgl_vertex_seeker);
	list_attributes_seeker(g->edges, scgl_edge_seeker);

	list_attributes_comparator(g->vertexes, scgl_vertex_comparator);
	list_attributes_comparator(g->edges, scgl_edge_comparator);

	for (i=0; i<vertexes_n; ++i)
		list_append(g->vertexes,(void*)vertexes[i]);

	for (i=0; i<edges_n; ++i)
		list_append(g->edges, (void*)edges[i]);

	return g;
}

void
scgl_graph_destroy(scgl_graph_t *graph) {
	if (graph != NULL) {
		list_iterator_start(graph->edges);
		while (list_iterator_hasnext(graph->edges))
			scgl_edge_destroy((scgl_edge_t*) list_iterator_next(graph->edges));
		list_iterator_stop(graph->edges);

		list_iterator_start(graph->vertexes);
		while (list_iterator_hasnext(graph->vertexes))
			scgl_vertex_destroy((scgl_vertex_t*) list_iterator_next(graph->vertexes));
		list_iterator_stop(graph->vertexes);

		list_destroy(graph->vertexes);
		list_destroy(graph->edges);
		free(graph->vertexes);
		free(graph->edges);
		free(graph->id);
		graph->vertexes = NULL;
		graph->edges = NULL;
		graph->id = NULL;
		free(graph);
		graph = NULL;
	}
}

int
scgl_graph_add_vertex(scgl_graph_t *graph, scgl_vertex_t *vertex) {
	if (graph == NULL || vertex == NULL)
		return -1;

	vertex->owner = graph;
	list_append(graph->vertexes, vertex);

	return 0;
}

void
scgl_graph_del_vertex(scgl_graph_t *graph, char *vertex_id) {
	scgl_vertex_t *v;
	scgl_edge_t *e;

	assert(graph != NULL);

	v = list_seek(graph->vertexes, vertex_id);
	if (v != NULL) {
		list_iterator_start(v->in);
		while (list_iterator_hasnext(v->in))
			scgl_edge_destroy((scgl_edge_t*) list_iterator_next(v->in));
		list_iterator_stop(v->in);

		list_iterator_start(v->out);
		while (list_iterator_hasnext(v->out))
			scgl_edge_destroy((scgl_edge_t*) list_iterator_next(v->out));
		list_iterator_stop(v->out);

		list_delete(graph->vertexes, v);

		scgl_vertex_destroy(v);
	}
}

scgl_vertex_t*
scgl_graph_get_vertex(scgl_graph_t *graph, char *vertex_id) {
	if (graph == NULL || vertex_id == NULL)
		return NULL;
	return list_seek(graph->vertexes, vertex_id);
}

int
scgl_graph_get_vertex_count(const scgl_graph_t *graph) {
	if (graph == NULL)
		return -1;
	return list_size(graph->vertexes);
}

int
scgl_graph_add_edge(scgl_graph_t *graph, scgl_edge_t *edge) {
	if (graph == NULL || edge == NULL)
		return -1;

	edge->owner = graph;
	list_append(graph->edges, edge);

	return 0;
}

void
scgl_graph_del_edge(scgl_graph_t *graph, const char *edge_id) {
	scgl_edge_t *e;
	e = list_seek(graph->edges, edge_id);
	if (e != NULL) {
		list_delete(graph->edges, e);
		scgl_edge_destroy(e);
	}
}

scgl_edge_t*
scgl_graph_get_edge(const scgl_graph_t *graph, const char *edge_id) {
	if (graph == NULL || edge_id == NULL)
		return NULL;
	return list_seek(graph->edges, edge_id);
}

int
scgl_graph_get_edge_count(const scgl_graph_t *graph) {
	if (graph == NULL)
		return -1;
	return list_size(graph->edges);
}
