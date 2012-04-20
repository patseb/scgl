#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
		list_append(g->vertexes, (void*)vertexes[i]);

	for (i=0; i<edges_n; ++i)
		list_append(g->edges, (void*)edges[i]);

	return g;
}

void
scgl_graph_destroy(scgl_graph_t **graph) {
	scgl_edge_t *e;
	scgl_vertex_t *v;

	if (graph != NULL && *graph != NULL) {
		list_iterator_start((*graph)->edges);
		while (list_iterator_hasnext((*graph)->edges)) {
			e = (scgl_edge_t*) list_iterator_next((*graph)->edges);
			if (e != NULL) {
				e->owner = NULL; /* prevents remove edge from edges */
				scgl_edge_destroy(&e);
			}
		}
		list_iterator_stop((*graph)->edges);

		list_iterator_start((*graph)->vertexes);
		while (list_iterator_hasnext((*graph)->vertexes)) {
			v = (scgl_vertex_t*) list_iterator_next((*graph)->vertexes);
			if (v != NULL) {
				v->owner = NULL; /* prevents remove vertex from vertexes */
				scgl_vertex_destroy(&v);
			}
		}
		list_iterator_stop((*graph)->vertexes);

		list_destroy((*graph)->vertexes);
		list_destroy((*graph)->edges);
		free((*graph)->vertexes);
		free((*graph)->edges);
		free((*graph)->id);
		(*graph)->vertexes = NULL;
		(*graph)->edges = NULL;
		(*graph)->id = NULL;
		free(*graph);
		*graph = NULL;
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
scgl_graph_del_vertex(scgl_graph_t *graph, scgl_vertex_t* vertex) {
	scgl_edge_t *e;

	if (graph == NULL)
		return;

	if (vertex != NULL) {
		list_iterator_start(vertex->in);
		while (list_iterator_hasnext(vertex->in)) {
			e = (scgl_edge_t*) list_iterator_next(vertex->in);
			scgl_edge_destroy(&e);
		}
		list_iterator_stop(vertex->in);

		list_iterator_start(vertex->out);
		while (list_iterator_hasnext(vertex->out)) {
			e = (scgl_edge_t*) list_iterator_next(vertex->out);
			scgl_edge_destroy(&e);
		}
		list_iterator_stop(vertex->out);

		list_delete(graph->vertexes, vertex);

		scgl_vertex_destroy(&vertex);
	}
}

scgl_vertex_t*
scgl_graph_get_vertex(const scgl_graph_t *graph, const char *vertex_id) {
	if (graph == NULL || vertex_id == NULL)
		return NULL;
	return list_seek(graph->vertexes, vertex_id);
}

scgl_vertex_t*
scgl_graph_get_vertex_at(const scgl_graph_t *graph, unsigned int i) {
	if (graph == NULL || graph->vertexes == NULL)
		return NULL;
	return list_get_at(graph->vertexes, i);
}

int
scgl_graph_get_vertexes_count(const scgl_graph_t *graph) {
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
scgl_graph_del_edge(scgl_graph_t *graph, scgl_edge_t *edge) {
	if (graph != NULL && edge != NULL) {
		list_delete(graph->edges, edge);
		scgl_edge_destroy(&edge);
	}
}

scgl_edge_t*
scgl_graph_get_edge(const scgl_graph_t *graph, const char *edge_id) {
	if (graph == NULL || edge_id == NULL)
		return NULL;
	return list_seek(graph->edges, edge_id);
}

scgl_edge_t*
scgl_graph_get_edge_at(const scgl_graph_t *graph, unsigned int i) {
	if (graph == NULL || graph->edges == NULL)
		return NULL;
	return list_get_at(graph->edges, i);
}

int
scgl_graph_get_edges_count(const scgl_graph_t *graph) {
	if (graph == NULL)
		return -1;
	return list_size(graph->edges);
}

void
scgl_graph_dump(scgl_graph_t *graph, FILE *fp, attr_foreach_function fun) {
	int i, n;

	if (graph == NULL || fp == NULL)
		return;

	fprintf(fp, "Graph: %s \n", graph->id);

	n = scgl_graph_get_edges_count(graph);
	for (i=0 ; i<n; ++i)
		scgl_edge_dump(scgl_graph_get_edge_at(graph, i), fp, fun);

	n = scgl_graph_get_vertexes_count(graph);
	for (i=0; i<n; ++i)
		scgl_vertex_dump(scgl_graph_get_vertex_at(graph, i), fp);
}
