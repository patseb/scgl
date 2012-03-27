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
scgl_vertex_destroy(scgl_vertex_t *vertex) {
	scgl_edge_t *e;
	int pos;

	if (vertex != NULL) {
		list_iterator_start(vertex->in);
		while (list_iterator_hasnext(vertex->in)) {
			e = (scgl_edge_t*) list_iterator_next(vertex->in);
			if (e != NULL)
				e->to = NULL;
		}
		list_iterator_stop(vertex->in);

		list_iterator_start(vertex->out);
		while (list_iterator_hasnext(vertex->out)) {
			e = (scgl_edge_t*) list_iterator_next(vertex->out);
			if (e != NULL)
				e->from = NULL;
		}
		list_iterator_stop(vertex->out);

		if (vertex->owner != NULL) {
			pos = list_locate(vertex->owner->vertexes, vertex);
			if (pos > 0)
				list_delete_at(vertex->owner->vertexes, pos);
		}

		list_destroy(vertex->in);
		list_destroy(vertex->out);
		free(vertex->in);
		free(vertex->out);
		free(vertex->id);
		vertex->in = NULL;
		vertex->out = NULL;
		vertex->id = NULL;
		free(vertex);
		vertex = NULL;
	}
}

int
scgl_vertex_add_edge(scgl_vertex_t *vertex, scgl_edge_t *edge, const unsigned int direction) {
	if (vertex == NULL || edge == NULL)
		return -1;

	if (direction == 0) {
		list_append(vertex->out, edge);
		edge->from = vertex;
	}
	else if (direction == 1) {
		list_append(vertex->in, edge);
		edge->to = vertex;
	}
	else
		return -1;

	return 0;
}

int
scgl_vertex_del_edge(scgl_vertex_t *vertex, scgl_edge_t *edge) {
	if (vertex == NULL || edge == NULL)
		return -1;

	if (edge->from == vertex) {
		list_delete(vertex->out, edge);
		edge->from = NULL;
	}
	else if (edge->to == vertex) {
		list_delete(vertex->in, edge);
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


