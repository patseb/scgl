#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simclist.h"
#include "scgl_edge.h"
#include "scgl_vertex.h"
#include "scgl_graph.h"

scgl_vertex_t*
scgl_vertex_create(char *id, scgl_edge_t **in, unsigned int in_n, scgl_edge_t **out, unsigned int out_n) {
	scgl_vertex_t *v;
	unsigned int i;

	v = (scgl_vertex_t*) malloc(sizeof(scgl_vertex_t));

	v->id = (char*) malloc(strlen(id)+1);
	strcpy(v->id, id);

	v->owner = NULL;

	v->in = (list_t*) malloc(sizeof(list_t));
	v->out = (list_t*) malloc(sizeof(list_t));

	list_init(v->in);
	list_init(v->out);

	for (i=0; i<in_n; ++i)
		if (in[i] != NULL) {
			list_append(v->in, (void*)in[i]);
			in[i]->to = v;
		}

	for (i=0; i<out_n; ++i)
		if (out[i] != NULL) {
			list_append(v->out, (void*)out[i]);
			out[i]->from = v;
		}

	return v;
}

void
scgl_vertex_destroy(scgl_vertex_t **vertex) {
	scgl_edge_t *e;
	int pos;

	if (vertex != NULL && *vertex != NULL) {
		list_iterator_start((*vertex)->in);
		while (list_iterator_hasnext((*vertex)->in)) {
			e = (scgl_edge_t*) list_iterator_next((*vertex)->in);
			if (e != NULL)
				e->to = NULL;
		}
		list_iterator_stop((*vertex)->in);

		list_iterator_start((*vertex)->out);
		while (list_iterator_hasnext((*vertex)->out)) {
			e = (scgl_edge_t*) list_iterator_next((*vertex)->out);
			if (e != NULL)
				e->from = NULL;
		}
		list_iterator_stop((*vertex)->out);

		if ((*vertex)->owner != NULL)
			list_delete((*vertex)->owner->vertexes, *vertex);

		list_destroy((*vertex)->in);
		list_destroy((*vertex)->out);
		free((*vertex)->in);
		free((*vertex)->out);
		free((*vertex)->id);
		(*vertex)->in = NULL;
		(*vertex)->out = NULL;
		(*vertex)->id = NULL;
		free(*vertex);
		*vertex = NULL;
	}
}

int
scgl_vertex_add_edge(scgl_vertex_t *vertex, scgl_edge_t *edge, unsigned int endpoint) {
	if (endpoint != 0 && endpoint != 1)
		endpoint = 0;
	return scgl_edge_set_vertex(edge, vertex, endpoint);
}

int
scgl_vertex_del_edge(scgl_vertex_t *vertex, scgl_edge_t *edge) {
	if (vertex == NULL || edge == NULL)
		return -1;

	if (edge->from == vertex) {
		list_delete(vertex->out, edge);
		if (edge->is_directed == 0)
			list_delete(vertex->in, edge);
		edge->from = NULL;
	}
	else if (edge->to == vertex) {
		list_delete(vertex->in, edge);
		if (edge->is_directed == 0)
			list_delete(vertex->out, edge);
		edge->to = NULL;
	}
	else
		return -1;

	return 0;
}

int
scgl_vertex_get_edges_in_count(const scgl_vertex_t *vertex) {
	if (vertex == NULL)
		return -1;
	return list_size(vertex->in);
}

int
scgl_vertex_get_edges_out_count(const scgl_vertex_t *vertex) {
	if (vertex == NULL)
		return -1;
	return list_size(vertex->out);
}

scgl_edge_t*
scgl_vertex_get_edge_in_at(const scgl_vertex_t *vertex, unsigned int i) {
	if (vertex != NULL)
		return list_get_at(vertex->in, i);
	else
		return NULL;
}

scgl_edge_t*
scgl_vertex_get_edge_out_at(const scgl_vertex_t *vertex, unsigned int i) {
	if (vertex != NULL)
		return list_get_at(vertex->out, i);
	else
		return NULL;
}

void
scgl_vertex_foreach_edge(const scgl_vertex_t *vertex, unsigned int direction, edge_foreach_function fun, void *data) {
	list_t *l;
	scgl_edge_t *e;

	if (vertex == NULL || (direction != 0 && direction != 1))
		return;

	l = direction ? vertex->out : vertex->in;
	if (l != NULL) {
		list_iterator_start(l);
		while (list_iterator_hasnext(l)) {
			e = (scgl_edge_t*) list_iterator_next(l);
			if (e != NULL)
				(*fun)(e, data);
		}
	}
}

static void
scgl_vertex_dump_edge(scgl_edge_t* edge, void *data) {
	if (edge != NULL) {
		fprintf((FILE*)data, " %s", edge->id);
	}
}

void
scgl_vertex_dump(scgl_vertex_t *vertex, FILE *fp) {
	if (vertex == NULL || fp == NULL)
		return;

	fprintf(fp,
	        "Vertex: %s \n",
	            "\tIncoming edges (%d):",
	        vertex->id,
	        (vertex->in ? scgl_vertex_get_edges_in_count(vertex) : 0));
	scgl_vertex_foreach_edge(vertex, 0, scgl_vertex_dump_edge, fp);
	fprintf(fp, "\tOutgoing edges (%d):", (vertex->out ? scgl_vertex_get_edges_out_count(vertex) : 0));
	scgl_vertex_foreach_edge(vertex, 1, scgl_vertex_dump_edge, fp);
}

int
scgl_vertex_seeker(const void *elem, const void *key) {
	const scgl_vertex_t *v;
	if (elem == NULL || key == NULL)
			return 0;

	v = (scgl_vertex_t*) elem;
	return !(strcmp(v->id, (char*)key));
}

int
scgl_vertex_comparator(const void *a, const void *b) {
	const scgl_vertex_t *v1, *v2;

	if (a == NULL && b == NULL)
		return 0;
	else if (a == NULL)
		return -1; 
	else if (b == NULL)
		return 1;

	v1 = (const scgl_vertex_t*) a;
	v2 = (const scgl_vertex_t*) b;

	if (v1->id == NULL && v2->id == NULL)
		return 0;
	else if (v1->id == NULL)
		return -1; 
	else if (v2->id == NULL)
		return 1;

	return strcmp(v1->id, v2->id)*(-1);
}


