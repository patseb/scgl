#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scgl_edge.h"
#include "scgl_attr.h"
#include "scgl_vertex.h"

static scgl_edge_t*
scgl_edge_create_sibling(scgl_vertex_t* from, scgl_vertex_t* to, cost_type_t cost, scgl_edge_t *sibling) {
	scgl_edge_t *e;

	e = (scgl_edge_t*) malloc(sizeof(scgl_edge_t));

	INIT_LIST_HEAD(&e->from_list);
	INIT_LIST_HEAD(&e->to_list);

	e->sibling = sibling;
	e->to = to;
	e->from = from;
	e->cost = cost;

	if (from != NULL)
		list_add_tail(&e->from_list, &from->out);
	if (to != NULL)
		list_add_tail(&e->to_list, &to->in);

	return e;
}

scgl_edge_t*
scgl_edge_create(scgl_vertex_t *from, scgl_vertex_t *to, int undirected, cost_type_t cost, scgl_attr_t **attr, unsigned int attr_n) {
	scgl_edge_t *e;
	unsigned int i;

	e = (scgl_edge_t*) malloc(sizeof(scgl_edge_t));

	INIT_LIST_HEAD(&e->attributes);
	INIT_LIST_HEAD(&e->from_list);
	INIT_LIST_HEAD(&e->to_list);
	INIT_LIST_HEAD(&e->owner_list);

	e->from = from;
	e->to = to;
	if (from != NULL)
		list_add_tail(&e->from_list, &from->out);
	if (to != NULL)
		list_add_tail(&e->to_list, &to->in);

	e->sibling = NULL;
	if (undirected == 1)
		e->sibling = scgl_edge_create_sibling(to, from, cost, e);
	e->cost = cost;

	for (i=0; i<attr_n; ++i)
		list_add_tail(&attr[i]->list, &e->attributes);

	return e;
}

static void
scgl_edge_destroy_sibling(scgl_edge_t **edge) {
	if (edge != NULL && *edge != NULL) {
		if ((*edge)->to != NULL)
			list_del(&(*edge)->to_list);

		if ((*edge)->from != NULL)
			list_del(&(*edge)->from_list);

		free(*edge);
		*edge = NULL;
	}
}

void
scgl_edge_destroy(scgl_edge_t **edge, attr_function fun) {
	scgl_attr_t *tmp;
	list_head_t *i, *j;

	if (edge != NULL && *edge != NULL) {
		if ((*edge)->to != NULL)
			list_del(&(*edge)->to_list);
		if ((*edge)->from != NULL)
			list_del(&(*edge)->from_list);

		list_del(&(*edge)->owner_list);

		list_for_each_safe(i, j, &(*edge)->attributes) {
			tmp = list_entry(i, scgl_attr_t, list);
			scgl_attr_destroy(&tmp, fun);
		}

		scgl_edge_destroy_sibling(&(*edge)->sibling);

		free(*edge);
		(*edge) = NULL;
	}
}

cost_type_t
scgl_edge_get_cost(const scgl_edge_t *edge) {
	assert(edge == NULL);
	return edge->cost;
}

void
scgl_edge_set_cost(scgl_edge_t *edge, const cost_type_t cost) {
	if (edge == NULL)
		return;
	edge->cost = cost;
	if (edge->sibling != NULL)
		edge->sibling->cost = cost;
}

scgl_vertex_t*
scgl_edge_get_vertex(scgl_edge_t *edge, const unsigned int endpoint) {
	if (edge == NULL)
		return NULL;
	return (endpoint == 0 ? edge->from : (endpoint == 1 ? edge->to : NULL));
}

int
scgl_edge_set_vertex(scgl_edge_t *edge, scgl_vertex_t *vertex, const unsigned int endpoint) {
	if (edge == NULL || vertex == NULL)
		return -1;

	if (endpoint == 0) {
		if (edge->from != NULL) {
			list_del(&edge->from_list);
			if (edge->sibling != NULL)
				list_del(&edge->sibling->to_list);
		}
		edge->from = vertex;
		list_add_tail(&edge->from_list, &vertex->out);
		if (edge->sibling != NULL) {
			list_add_tail(&edge->sibling->to_list, &vertex->in);
			edge->sibling->to = vertex;
		}
	}
	else if (endpoint == 1) {
		if (edge->to != NULL) {
			list_del(&edge->to_list);
			if (edge->sibling != NULL)
				list_del(&edge->sibling->from_list);
		}
		edge->to = vertex;
		list_add_tail(&edge->to_list, &vertex->in);
		if (edge->sibling != NULL) {
			list_add_tail(&edge->sibling->from_list, &vertex->out);
			edge->sibling->from = vertex;
		}
	}
	else
		return -1;

	return 0;
}

int
scgl_edge_del_vertex(scgl_edge_t *edge, scgl_vertex_t *vertex) {
	return scgl_vertex_del_edge(vertex, edge);
}

void
scgl_edge_add_attribute(scgl_edge_t *edge, char *key, void *value) {
	scgl_attr_t *p;

	if (edge == NULL)
		return;

	p = scgl_attr_create(key, value);
	list_add_tail(&p->list, &edge->attributes);
}

void
scgl_edge_del_attribute(scgl_edge_t *edge, const char *key, attr_function fun) {
	list_head_t *i;
	scgl_attr_t *tmp = NULL;

	list_for_each(i, &edge->attributes) {
		tmp = list_entry(i, scgl_attr_t, list);
		if (tmp != NULL)
			if (strcmp(tmp->key, key)) {
				scgl_attr_destroy(&tmp, fun);
				break;
			}
	}
	free(tmp);
}

void*
scgl_edge_get_attribute(scgl_edge_t *edge, const char *key) {
	list_head_t *i;
	scgl_attr_t *tmp;

	list_for_each(i, &edge->attributes) {
		tmp = list_entry(i, scgl_attr_t, list);
		if (strcmp(tmp->key, key)) {
			return tmp;
		}
	}
	return NULL;
}

int
scgl_edge_get_attributes_count(const scgl_edge_t *edge) {
	return (edge == NULL ? -1 : list_count(&edge->attributes));
}

scgl_attr_t*
scgl_edge_get_attribute_at(const scgl_edge_t *edge, unsigned int i) {
	unsigned int k = 0;
	list_head_t *j;
	scgl_attr_t *tmp;

	list_for_each(j, &edge->attributes) {
		if (i == k++) {
			tmp = list_entry(j, scgl_attr_t, list);
			return tmp;
		}
	}
	return NULL;
}

void
scgl_edge_foreach_attribute(scgl_edge_t *edge, attr_function fun, void *data) {
	list_head_t *i;
	scgl_attr_t *tmp;

	if (edge == NULL)
		return;

	list_for_each(i, &edge->attributes) {
		tmp = list_entry(i, scgl_attr_t, list);
		(*fun)(tmp->key, tmp->value, data);
	}
}

int
scgl_edge_get_undirected(const scgl_edge_t *edge) {
	return (edge == NULL ? -1 : edge->sibling == NULL ? 0 : 1);
}

void
scgl_edge_set_undirected(scgl_edge_t *edge, unsigned int undirected) {
	if (edge != NULL) {
		if (edge->sibling == NULL && undirected == 1)
			edge->sibling = scgl_edge_create_sibling(edge->to, edge->from, edge->cost, edge);
		else if (edge->sibling != NULL && undirected == 0)
			scgl_edge_destroy_sibling(&edge->sibling);
	}
}

void
scgl_edge_dump(scgl_edge_t *edge, FILE *fp, attr_function fun) {
	if (edge == NULL || fp == NULL)
		return;

	fprintf(fp,
	        "Edge: %p \n"
	            "\tCost: " cost_fmt "\n"
	            "\tUndirected: %s \n"
	            "\tFrom: %s \n"
	            "\tTo: %s \n"
	            "\tAttributes: \n",
	        (void*)edge,
	        edge->cost,
	        (edge->sibling != NULL ? "Yes" : "No"),
	        (edge->from ? edge->from->id : NULL),
	        (edge->to ? edge->to->id : NULL));

	scgl_edge_foreach_attribute(edge, fun, fp);
}
