#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "simclist.h"
#include "scgl_edge.h"
#include "scgl_pair.h"
#include "scgl_vertex.h"

edge_t*
scgl_edge_create(char *id, vertex_t *from, vertex_t *to, int is_directed, double weight, pair_t **attr, unsigned int attr_n) {
	edge_t *e;
	unsigned int i;

	e = (edge_t*) malloc(sizeof(edge_t));
	e->id = (char*) malloc(strlen(id)+1);
	strcpy(e->id, id);

	e->from = from;
	e->to = to;
	if (from != NULL)
		list_append(from->out, e);
	if (to != NULL)
		list_append(to->in, e);

	e->is_directed = is_directed;
	e->weight = weight;
	list_init(e->attributes);
	list_attributes_seeker(e->attributes, pair_seeker);
	list_attributes_comparator(e->attributes, pair_comparator);

	for (i=0; i<attr_n; ++i)
		list_append(e->attributes, (void*)attr[i]);

	return e;
}

void
scgl_edge_destroy(edge_t *edge) {
	if (edge != NULL) {
		if (edge->to != NULL)
			list_delete(edge->to->in, edge);
		if (edge->from != NULL)
			list_delete(edge->from->out, edge);

		list_destroy(edge->attributes);
		free(edge->id);
		free(edge);
		edge = NULL;
	}
}

void
scgl_edge_add_attribute(edge_t *edge, const char *key, void *value) {
	pair_t *p;

	assert(edge == NULL);
	p = scgl_pair_create(key, value);
	list_append(edge->attributes, p);
}

void*
scgl_edge_get_attribute(edge_t *edge, const char *key) {
	pair_t *p;

	assert(edge == NULL);

	p = list_seek(edge->attributes, key);
	if (p == NULL)
		return NULL;

	return p->value;
}

void
scgl_edge_foreach_attribute(edge_t *edge, attr_function, void *data) {
	assert(edge == NULL);

	list_iterator_start(edge->attributes);
	while (list_iterator_hasnext(edge->attributes)) {
		pair_t *attr = (pair_t*) list_iterator_next(edge->attributes);
		if (attr != NULL)
			(*function)(attr->key, attr->value, data);
	}
	list_iterator_stop(edge->attributes);
}

int
scgl_edge_seeker(const void *elem, const void *key) {
	const edge_t *e;
	if (elem == NULL || key == NULL)
		return 0;

	e = (edge_t*) elem;
	return !(strcmp(e->id, (char*)key));
}

int
scgl_edge_comparator(const void *a, const void *b) {
	const edge_t *e1, *e2;

	if (a == NULL && b == NULL)
		return 0;
	else if (a == NULL)
		return -1;
	else if (b == NULL)
		return 1;

	e1 = (const edge_t*) a;
	e2 = (const edge_t*) b;

	if (e1->id == NULL && e2->id == NULL)
		return 0;
	else if (e1->id == NULL)
		return -1;
	else if (e2->id == NULL)
		return 1;

	return strcmp(e1->id, e2->id)*(-1);
}
