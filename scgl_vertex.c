#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simclist.h"
#include "scgl_edge.h"
#include "scgl_vertex.h"

vertex_t*
vertex_create(char *id, edge_t **in, unsigned int in_n, edge_t **out, unsigned int out_n) {
	vertex_t *v;
	unsigned int i;

	v = (vertex_t*) malloc(sizeof(vertex_t));

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
vertex_destroy(vertex_t *vertex) {
	edge_t *e;

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
