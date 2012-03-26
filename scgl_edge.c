#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "simclist.h"
#include "scgl_edge.h"
#include "scgl_pair.h"
#include "scgl_vertex.h"

scgl_edge_t*
scgl_edge_create(char *id, scgl_vertex_t *from, scgl_vertex_t *to, int is_directed, double weight, scgl_pair_t **attr, unsigned int attr_n) {
	scgl_edge_t *e;
	unsigned int i;

	e = (scgl_edge_t*) malloc(sizeof(scgl_edge_t));
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
	e->attributes = (list_t*) malloc(sizeof(list_t));
	list_init(e->attributes);
	list_attributes_seeker(e->attributes, scgl_pair_seeker);
	list_attributes_comparator(e->attributes, scgl_pair_comparator);
	for (i=0; i<attr_n; ++i)
		list_append(e->attributes, (void*)attr[i]);
	e->attr_free_fun = NULL;

	return e;
}

void
scgl_edge_destroy(scgl_edge_t *edge) {
	scgl_pair_t *p;
	if (edge != NULL) {
		if (edge->to != NULL) {
			list_delete(edge->to->in, edge);
			edge->to = NULL;
		}
		if (edge->from != NULL) {
			list_delete(edge->from->out, edge);
			edge->from = NULL;
		}

		list_iterator_start(edge->attributes);
		while (list_iterator_hasnext(edge->attributes)) {
			p = (scgl_pair_t*) list_iterator_next(edge->attributes);
			if (p != NULL)
				scgl_pair_destroy(p, edge->attr_free_fun);
		}
		list_iterator_stop(edge->attributes);

		list_destroy(edge->attributes);
		free(edge->attributes);
		free(edge->id);
		edge->attributes = NULL;
		edge->id = NULL;
		free(edge);
		edge = NULL;
	}
}

void
scgl_edge_set_vertex(scgl_edge_t *edge, scgl_vertex_t *vertex, const unsigned int direction) {
	assert(edge != NULL);

	if (direction == 0) {
		if (edge->from != NULL)
				list_delete(edge->from->out, edge);
		edge->from = vertex;
		list_append(vertex->out, edge);
	}
	else if (direction == 1) {
		if (edge->to != NULL)
				list_delete(edge->to->in, edge);
		edge->to = vertex;
		list_append(vertex->in, edge);
	}
}

void
scgl_edge_add_attribute(scgl_edge_t *edge, const char *key, void *value) {
	scgl_pair_t *p;

	assert(edge != NULL);
	p = scgl_pair_create(key, value);
	list_append(edge->attributes, (void*) p);
}

void*
scgl_edge_get_attribute(scgl_edge_t *edge, const char *key) {
	scgl_pair_t *p;

	assert(edge != NULL);

	p = list_seek(edge->attributes, key);
	if (p == NULL)
		return NULL;

	return p->value;
}

void
scgl_edge_foreach_attribute(scgl_edge_t *edge, attr_foreach_function fun, void *data) {
	assert(edge != NULL);

	list_iterator_start(edge->attributes);
	while (list_iterator_hasnext(edge->attributes)) {
		scgl_pair_t *attr = (scgl_pair_t*) list_iterator_next(edge->attributes);
		if (attr != NULL)
			(*fun)(attr->key, attr->value, data);
	}
	list_iterator_stop(edge->attributes);
}

void
scgl_edge_attr_free_function(scgl_edge_t *edge, attr_free_function fun) {
	if (edge != NULL)
		edge->attr_free_fun = fun;
}

int
scgl_edge_seeker(const void *elem, const void *key) {
	const scgl_edge_t *e;
	if (elem == NULL || key == NULL)
		return 0;

	e = (scgl_edge_t*) elem;
	return !(strcmp(e->id, (char*)key));
}

int
scgl_edge_comparator(const void *a, const void *b) {
	const scgl_edge_t *e1, *e2;

	if (a == NULL && b == NULL)
		return 0;
	else if (a == NULL)
		return -1;
	else if (b == NULL)
		return 1;

	e1 = (const scgl_edge_t*) a;
	e2 = (const scgl_edge_t*) b;

	if (e1->id == NULL && e2->id == NULL)
		return 0;
	else if (e1->id == NULL)
		return -1;
	else if (e2->id == NULL)
		return 1;

	return strcmp(e1->id, e2->id)*(-1);
}
