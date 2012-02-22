#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simclist.h"
#include "scgl_edge.h"
#include "scgl_vertex.h"

scgl_vertex_t*
scgl_vertex_create(char *id, scgl_edge_t **in, unsigned int in_n, scgl_edge_t **out, unsigned int out_n) {
	scgl_vertex_t *v;
	unsigned int i;

	v = (scgl_vertex_t*) malloc(sizeof(scgl_vertex_t));

	v->id = (char*) malloc(strlen(id)+1);
	strcpy(v->id, id);

	list_init(v->in);
	list_init(v->out);

	for (i=0; i<in_n; ++i)
		list_append(v->in, (void*)in[i]);

	for (i=0; i<out_n; ++i)
		list_append(v->out, (void*)out[i]);

	return v;
}

void
scgl_vertex_destroy(scgl_vertex_t *vertex) {
	scgl_edge_t *e;

	if (vertex != NULL) {
		list_iterator_start(vertex->in);
		while (list_iterator_hasnext(vertex->in)) {
			e = (edge_t*) list_iterator_next(vertex->in);
			if (e != NULL)
				e->to = NULL;
		}
		list_iterator_stop(vertex->in);

		list_iterator_start(vertex->out);
		while (list_iterator_hasnext(vertex->out)) {
			e = (edge_t*) list_iterator_next(vertex->out);
			if (e != NULL)
				e->from = NULL;
		}
		list_iterator_stop(vertex->out);

		list_destroy(vertex->in);
		list_destroy(vertex->out);
		free(vertex->id);
		vertex = NULL;
	}
}

int
scgl_vertex_add_edge(scgl_vertex_t *vertex, const scgl_edge_t *edge) {
	if (vertex == NULL || edge == NULL)
		return -1;

	if (edge->from == vertex)
		list_append(vertex->out, edge);
	else if (edge->to == vertex)
		list_append(vertex->in, edge);
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
