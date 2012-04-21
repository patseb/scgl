#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl_list.h"
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

	g->vertexes = (scgl_list_t*) malloc(sizeof(scgl_list_t));
	g->edges = (scgl_list_t*) malloc(sizeof(scgl_list_t));

	INIT_LIST_HEAD(&g->vertexes->list);
	INIT_LIST_HEAD(&g->edges->list);

//	list_attributes_seeker(g->vertexes, scgl_vertex_seeker);
//	list_attributes_seeker(g->edges, scgl_edge_seeker);

//	list_attributes_comparator(g->vertexes, scgl_vertex_comparator);
//	list_attributes_comparator(g->edges, scgl_edge_comparator);

	for (i=0; i<vertexes_n; ++i)
		scgl_list_add(&g->vertexes->list, vertexes[i]);

	for (i=0; i<edges_n; ++i)
		scgl_list_add(&g->edges->list, edges[i]);

	return g;
}

void
scgl_graph_destroy(scgl_graph_t **graph) {
	scgl_list_t *tmp;
	list_head_t *i, *j;

	if (graph != NULL && *graph != NULL) {
		list_for_each_safe(i, j, &(*graph)->edges->list) {
			tmp = list_entry(i, scgl_list_t, list);
			if (tmp->data != NULL) {
				((scgl_edge_t*)tmp->data)->owner = NULL;
				scgl_edge_destroy((scgl_edge_t**)&tmp->data);
			}
			list_del(i);
		}

		list_for_each_safe(i, j, &(*graph)->vertexes->list) {
			tmp = list_entry(i, scgl_list_t, list);
			if (tmp->data != NULL) {
				((scgl_vertex_t*)tmp->data)->owner = NULL;
				scgl_vertex_destroy((scgl_vertex_t**)&tmp->data);
			}
			list_del(i);
		}

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

char *
scgl_graph_get_id(const scgl_graph_t *graph) {
	return (graph == NULL ? NULL : graph->id);
}

void
scgl_graph_set_id(scgl_graph_t *graph, const char *id) {
	if (graph == NULL || id == NULL)
		return;

	if (graph->id != NULL)
		free(graph->id);
	graph->id = (char*) malloc(strlen(id)+1);

	strcpy(graph->id, id);
}

int
scgl_graph_add_vertex(scgl_graph_t *graph, scgl_vertex_t *vertex) {
	if (graph == NULL || vertex == NULL)
		return -1;

	vertex->owner = graph;
	scgl_list_add(&graph->vertexes->list, vertex);

	return 0;
}

void
scgl_graph_del_vertex(scgl_graph_t *graph, scgl_vertex_t* vertex) {
	scgl_list_t *tmp;
	list_head_t *i, *j;

	if (graph == NULL)
		return;

	if (vertex != NULL) {
		list_for_each_safe(i, j, &vertex->in->list) {
			tmp = list_entry(i, scgl_list_t, list);
			list_del(i);
			scgl_edge_destroy((scgl_edge_t**)&tmp->data);
		}

		list_for_each_safe(i, j, &vertex->out->list) {
			tmp = list_entry(i, scgl_list_t, list);
			list_del(i);
			scgl_edge_destroy((scgl_edge_t**)&tmp->data);
		}

		scgl_list_delete(&graph->vertexes->list, vertex);

		scgl_vertex_destroy(&vertex);
	}
}

scgl_vertex_t*
scgl_graph_get_vertex(const scgl_graph_t *graph, const char *vertex_id) {
	list_head_t *i;
	scgl_list_t *tmp;

	if (graph == NULL || vertex_id == NULL)
		return NULL;

	list_for_each(i, &graph->vertexes->list) {
		tmp = list_entry(i, scgl_list_t, list);
		if (strcmp(((scgl_vertex_t*)tmp->data)->id, vertex_id))
			return (scgl_vertex_t*)tmp->data;
	}

	return NULL;
}

scgl_vertex_t*
scgl_graph_get_vertex_at(const scgl_graph_t *graph, unsigned int i) {
	unsigned int k = 0;
	list_head_t *j;
	scgl_list_t *tmp;

	if (graph == NULL)
		return NULL;

	list_for_each(j, &graph->vertexes->list) {
		if (i == k++) {
			tmp = list_entry(j, scgl_list_t, list);
			return (scgl_vertex_t*)tmp->data;
		}
	}

	return NULL;
}

int
scgl_graph_get_vertexes_count(const scgl_graph_t *graph) {
	if (graph == NULL)
		return -1;
	return scgl_list_count(&graph->vertexes->list);
}

int
scgl_graph_add_edge(scgl_graph_t *graph, scgl_edge_t *edge) {
	if (graph == NULL || edge == NULL)
		return -1;

	edge->owner = graph;
	scgl_list_add(&graph->edges->list, edge);

	return 0;
}

void
scgl_graph_del_edge(scgl_graph_t *graph, scgl_edge_t *edge) {
	if (graph != NULL && edge != NULL) {
		scgl_list_delete(&graph->edges->list, edge);
		scgl_edge_destroy(&edge);
	}
}

scgl_edge_t*
scgl_graph_get_edge(const scgl_graph_t *graph, const char *edge_id) {
	list_head_t *i;
	scgl_list_t *tmp;

	if (graph == NULL || edge_id == NULL)
		return NULL;

	list_for_each(i, &graph->edges->list) {
		tmp = list_entry(i, scgl_list_t, list);
		if (strcmp(((scgl_edge_t*)(tmp->data))->id, edge_id))
			return (scgl_edge_t*)tmp->data;
	}

	return NULL;
}

scgl_edge_t*
scgl_graph_get_edge_at(const scgl_graph_t *graph, unsigned int i) {
	unsigned int k = 0;
	list_head_t *j;
	scgl_list_t *tmp;

	if (graph == NULL)
		return NULL;

	list_for_each(j, &graph->edges->list) {
		if (i == k++) {
			tmp = list_entry(j, scgl_list_t, list);
			return (scgl_edge_t*)tmp->data;
		}
	}

	return NULL;
}

int
scgl_graph_get_edges_count(const scgl_graph_t *graph) {
	if (graph == NULL)
		return -1;
	return scgl_list_count(&graph->edges->list);
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
