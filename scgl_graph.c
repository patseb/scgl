#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "scgl_edge.h"
#include "scgl_vertex.h"
#include "scgl_graph.h"

scgl_graph_t*
scgl_graph_create(char *id, scgl_vertex_t **vertexes, unsigned int vertexes_n, scgl_edge_t **edges, unsigned int edges_n) {
	scgl_graph_t *g;
	unsigned int i;

	g = (scgl_graph_t*) malloc(sizeof(scgl_graph_t));

	g->id = id;

	INIT_LIST_HEAD(&g->vertexes);
	INIT_LIST_HEAD(&g->edges);

	for (i=0; i<vertexes_n; ++i)
		list_add(&vertexes[i]->owner_list, &g->vertexes);

	for (i=0; i<edges_n; ++i)
		list_add(&edges[i]->owner_list, &g->edges);

	return g;
}

void
scgl_graph_destroy(scgl_graph_t **graph) {
	scgl_edge_t *e;
	scgl_vertex_t *v;
	list_head_t *i, *j;

	if (graph != NULL && *graph != NULL) {
		list_for_each_safe(i, j, &(*graph)->edges) {
			e = list_entry(i, scgl_edge_t, owner_list);
			scgl_edge_destroy(&e);
		}

		list_for_each_safe(i, j, &(*graph)->vertexes) {
			v = list_entry(i, scgl_vertex_t, owner_list);
			scgl_vertex_destroy(&v);
		}

		free((*graph)->id);
		(*graph)->id = NULL;
		free(*graph);
		*graph = NULL;
	}
}

char *
scgl_graph_get_id(const scgl_graph_t *graph) {
	return (graph == NULL ? NULL : graph->id);
}

void
scgl_graph_set_id(scgl_graph_t *graph, char *id) {
	if (graph == NULL || id == NULL)
		return;

	if (graph->id != NULL)
		free(graph->id);

	graph->id = id;
}

int
scgl_graph_add_vertex(scgl_graph_t *graph, scgl_vertex_t *vertex) {
	if (graph == NULL || vertex == NULL)
		return -1;

	list_add(&vertex->owner_list, &graph->vertexes);

	return 0;
}

void
scgl_graph_del_vertex(scgl_graph_t *graph, scgl_vertex_t **vertex) {
	scgl_edge_t *e;
	list_head_t *i, *j;

	if (graph == NULL)
		return;

	if (vertex != NULL && *vertex != NULL) {
		list_for_each_safe(i, j, &(*vertex)->in) {
			e = list_entry(i, scgl_edge_t, to_list);
			scgl_edge_destroy(&e);
		}

		list_for_each_safe(i, j, &(*vertex)->out) {
			e = list_entry(i, scgl_edge_t, from_list);
			scgl_edge_destroy(&e);
		}

		scgl_vertex_destroy(vertex);
	}
}

scgl_vertex_t*
scgl_graph_get_vertex(const scgl_graph_t *graph, const char *vertex_id) {
	list_head_t *i;
	scgl_vertex_t *tmp;

	if (graph == NULL || vertex_id == NULL)
		return NULL;

	list_for_each(i, &graph->vertexes) {
		tmp = list_entry(i, scgl_vertex_t, owner_list);
		if (strcmp(tmp->id, vertex_id))
			return tmp;
	}

	return NULL;
}

scgl_vertex_t*
scgl_graph_get_vertex_at(const scgl_graph_t *graph, unsigned int i) {
	unsigned int k = 0;
	list_head_t *j;
	scgl_vertex_t *tmp;

	if (graph == NULL)
		return NULL;

	list_for_each(j, &graph->vertexes) {
		if (i == k++) {
			tmp = list_entry(j, scgl_vertex_t, owner_list);
			return tmp;
		}
	}

	return NULL;
}

int
scgl_graph_get_vertexes_count(const scgl_graph_t *graph) {
	if (graph == NULL)
		return -1;
	return list_count(&graph->vertexes);
}

int
scgl_graph_add_edge(scgl_graph_t *graph, scgl_edge_t *edge) {
	if (graph == NULL || edge == NULL)
		return -1;

	list_add(&edge->owner_list, &graph->edges);

	return 0;
}

void
scgl_graph_del_edge(scgl_graph_t *graph, scgl_edge_t **edge) {
	if (graph != NULL && edge != NULL) {
		scgl_edge_destroy(edge);
	}
}

scgl_edge_t*
scgl_graph_get_edge_at(const scgl_graph_t *graph, unsigned int i) {
	unsigned int k = 0;
	list_head_t *j;

	if (graph == NULL)
		return NULL;

	list_for_each(j, &graph->edges) {
		if (i == k++)
			return list_entry(j, scgl_edge_t, owner_list);
	}

	return NULL;
}

int
scgl_graph_get_edges_count(const scgl_graph_t *graph) {
	if (graph == NULL)
		return -1;
	return list_count(&graph->edges);
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
