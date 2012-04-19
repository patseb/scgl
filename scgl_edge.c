#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "simclist.h"
#include "scgl_edge.h"
#include "scgl_pair.h"
#include "scgl_vertex.h"
#include "scgl_graph.h"

scgl_edge_t*
scgl_edge_create(char *id, scgl_vertex_t *from, scgl_vertex_t *to, int is_directed, double weight, scgl_pair_t **attr, unsigned int attr_n) {
	scgl_edge_t *e;
	unsigned int i;

	e = (scgl_edge_t*) malloc(sizeof(scgl_edge_t));
	e->id = (char*) malloc(strlen(id)+1);
	strcpy(e->id, id);

	e->owner = NULL;

	e->from = from;
	e->to = to;
	if (from != NULL) {
		list_append(from->out, e);
		if (is_directed == 0)
			list_append(from->in, e);
	}
	if (to != NULL) {
		list_append(to->in, e);
		if (is_directed == 0)
			list_append(to->out, e);
	}
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
	int pos;

	if (edge != NULL) {
		if (edge->to != NULL) {
			list_delete(edge->to->in, edge);
			if (edge->is_directed == 0)
				list_delete(edge->to->out, edge);
			edge->to = NULL;
		}
		if (edge->from != NULL) {
			list_delete(edge->from->out, edge);
			if (edge->is_directed == 0)
				list_delete(edge->from->in, edge);
			edge->from = NULL;
		}

		list_iterator_start(edge->attributes);
		while (list_iterator_hasnext(edge->attributes)) {
			p = (scgl_pair_t*) list_iterator_next(edge->attributes);
			if (p != NULL)
				scgl_pair_destroy(p, edge->attr_free_fun);
		}
		list_iterator_stop(edge->attributes);
/*
		if (edge->owner != NULL) {
			pos = list_locate(edge->owner->edges, edge);
			if (pos > 0)
				list_delete_at(edge->owner->edges, pos);
		}
*/
		if (edge->owner != NULL)
			list_delete(edge->owner->edges, edge);

		list_destroy(edge->attributes);
		free(edge->attributes);
		free(edge->id);
		edge->attributes = NULL;
		edge->id = NULL;
		free(edge);
		edge = NULL;
	}
}

int
scgl_edge_set_vertex(scgl_edge_t *edge, scgl_vertex_t *vertex, const unsigned int endpoint) {
	if (edge != NULL && vertex != NULL)
		return -1;

	if (endpoint == 0) {
		if (edge->from != NULL) {
				list_delete(edge->from->out, edge);
				if (edge->is_directed == 0)
					list_delete(edge->from->in, edge);
		}
		edge->from = vertex;
		list_append(vertex->out, edge);
		if (edge->is_directed == 0)
			list_append(vertex->in, edge);
	}
	else if (endpoint == 1) {
		if (edge->to != NULL) {
				list_delete(edge->to->in, edge);
				if (edge->is_directed == 0)
					list_delete(edge->to->out, edge);
		}
		edge->to = vertex;
		list_append(vertex->in, edge);
		if (edge->is_directed == 0)
			list_append(vertex->out, edge);
	}
	else
		return -1;

	return 0;
}

void
scgl_edge_add_attribute(scgl_edge_t *edge, const char *key, void *value) {
	scgl_pair_t *p;

	assert(edge != NULL);
	p = scgl_pair_create(key, value);
	list_append(edge->attributes, (void*) p);
}

void
scgl_edge_del_attribute(scgl_edge_t *edge, const char *key) {
	scgl_pair_t *p;

	p = list_seek(edge->attributes, key);
	if (p != NULL)
		scgl_pair_destroy(p, edge->attr_free_fun);
	free(p);
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

void
scgl_edge_set_is_directed(scgl_edge_t *edge, const unsigned int directed) {
	if (edge != NULL)
		if (edge->is_directed != directed) {
			edge->is_directed = directed;
			if (edge->from != NULL && edge->to != NULL)
				if (directed == 0) {
					list_append(edge->from->in, edge);
					list_append(edge->to->out, edge);
				}
				else {
					list_delete(edge->from->in, edge);
					list_delete(edge->to->out, edge);
				}
		}
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
