#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl_list.h"
#include "scgl_edge.h"
#include "scgl_pair.h"
#include "scgl_vertex.h"
#include "scgl_graph.h"

scgl_edge_t*
scgl_edge_create(char *id, scgl_vertex_t *from, scgl_vertex_t *to, int is_directed, cost_type_t cost, scgl_pair_t **attr, unsigned int attr_n) {
	scgl_edge_t *e;
	unsigned int i;

	e = (scgl_edge_t*) malloc(sizeof(scgl_edge_t));
	e->id = (char*) malloc(strlen(id)+1);
	strcpy(e->id, id);

	e->owner = NULL;

	e->from = from;
	e->to = to;
	if (from != NULL) {
		scgl_list_add(&from->out->list, e);
		if (is_directed == 0)
			scgl_list_add(&from->in->list, e);
	}
	if (to != NULL) {
		scgl_list_add(&to->in->list, e);
		if (is_directed == 0)
			scgl_list_add(&to->out->list, e);
	}
	e->is_directed = is_directed;

	e->cost = cost;
	e->attributes = (scgl_list_t*) malloc(sizeof(scgl_list_t));
	INIT_LIST_HEAD(&e->attributes->list);
	for (i=0; i<attr_n; ++i)
		scgl_list_add(&e->attributes->list, attr[i]);

	e->attr_free_fun = NULL;

	return e;
}

void
scgl_edge_destroy(scgl_edge_t **edge) {
	scgl_list_t *tmp;
	list_head_t *i, *j;

	if (edge != NULL && *edge != NULL) {
		if ((*edge)->to != NULL) {
			scgl_list_delete(&(*edge)->to->in->list, *edge);
			if ((*edge)->is_directed == 0)
				scgl_list_delete(&(*edge)->to->out->list, *edge);
			(*edge)->to = NULL;
		}
		if ((*edge)->from != NULL) {
			scgl_list_delete(&(*edge)->from->out->list, *edge);
			if ((*edge)->is_directed == 0)
				scgl_list_delete(&(*edge)->from->in->list, *edge);
			(*edge)->from = NULL;
		}

		if ((*edge)->owner != NULL)
			scgl_list_delete(&(*edge)->owner->edges->list, *edge);

		list_for_each_safe(i, j, &(*edge)->attributes->list) {
			tmp = list_entry(i, scgl_list_t, list);
			list_del(i);
			scgl_pair_destroy((scgl_pair_t*)tmp->data, (*edge)->attr_free_fun);
			free(tmp);
		}

		free((*edge)->attributes);
		free((*edge)->id);
		(*edge)->attributes = NULL;
		(*edge)->id = NULL;
		free(*edge);
		*edge = NULL;
	}
}

char*
scgl_edge_get_id(const scgl_edge_t *edge) {
	return (edge == NULL ? NULL : edge->id);
}

void
scgl_edge_set_id(scgl_edge_t *edge, const char *id) {
	if (edge == NULL || id == NULL)
		return;

	if (edge->id != NULL)
		free(edge->id);
	edge->id = (char*) malloc(strlen(id)+1);

	strcpy(edge->id, id);
}

cost_type_t
scgl_edge_get_cost(const scgl_edge_t *edge) {
	return (edge == NULL ? -1 : edge->cost);
}

void
scgl_edge_set_cost(scgl_edge_t *edge, const cost_type_t cost) {
	if (edge == NULL)
		return;
	edge->cost = cost;
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
				scgl_list_delete(&edge->from->out->list, edge);
				if (edge->is_directed == 0)
					scgl_list_delete(&edge->from->in->list, edge);
		}
		edge->from = vertex;
		scgl_list_add(&vertex->out->list, edge);
		if (edge->is_directed == 0)
			scgl_list_add(&vertex->in->list, edge);
	}
	else if (endpoint == 1) {
		if (edge->to != NULL) {
				scgl_list_delete(&edge->to->in->list, edge);
				if (edge->is_directed == 0)
					scgl_list_delete(&edge->to->out->list, edge);
		}
		edge->to = vertex;
		scgl_list_add(&vertex->in->list, edge);
		if (edge->is_directed == 0)
			scgl_list_add(&vertex->out->list, edge);
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
scgl_edge_add_attribute(scgl_edge_t *edge, const char *key, void *value) {
	scgl_pair_t *p;

	if (edge == NULL)
		return;

	p = scgl_pair_create(key, value);
	scgl_list_add(&edge->attributes->list, p);
}

void
scgl_edge_del_attribute(scgl_edge_t *edge, const char *key) {
	list_head_t *i;
	scgl_list_t *tmp;

	list_for_each(i, &edge->attributes->list) {
		tmp = list_entry(i, scgl_list_t, list);
		if (strcmp(((scgl_pair_t*)tmp->data)->key, key)) {
			scgl_pair_destroy((scgl_pair_t*)tmp, edge->attr_free_fun);
			break;
		}
	}
	free(tmp);
}

void*
scgl_edge_get_attribute(scgl_edge_t *edge, const char *key) {
	list_head_t *i;
	scgl_list_t *tmp;

	list_for_each(i, &edge->attributes->list) {
		tmp = list_entry(i, scgl_list_t, list);
		if (strcmp(((scgl_pair_t*)tmp)->key, key)) {
			return (scgl_pair_t*)tmp->data;
		}
	}
	return NULL;
}

int
scgl_edge_get_attributes_count(const scgl_edge_t *edge) {
	return (edge == NULL ? -1 : scgl_list_count(&edge->attributes->list));
}

scgl_pair_t*
scgl_edge_get_attribute_at(const scgl_edge_t *edge, unsigned int i) {
	unsigned int k = 0;
	list_head_t *j;
	scgl_list_t *tmp;

	list_for_each(j, &edge->attributes->list) {
		if (i == k++) {
			tmp = list_entry(j, scgl_list_t, list);
			return (scgl_pair_t*)tmp->data;
		}
	}
	return NULL;
}

void
scgl_edge_foreach_attribute(scgl_edge_t *edge, attr_foreach_function fun, void *data) {
	scgl_pair_t *attr;
	list_head_t *i;
	scgl_list_t *tmp;

	if (edge == NULL)
		return;

	list_for_each(i, &edge->attributes->list) {
		tmp = list_entry(i, scgl_list_t, list);
		if (tmp->data != NULL) {
			attr = (scgl_pair_t*)tmp->data;
			(*fun)(attr->key, attr->value, data);
		}
	}
}

void
scgl_edge_attr_free_function(scgl_edge_t *edge, attr_free_function fun) {
	if (edge != NULL)
		edge->attr_free_fun = fun;
}

int
scgl_edge_get_is_directed(const scgl_edge_t *edge) {
	return (edge == NULL ? -1 : edge->is_directed);
}

void
scgl_edge_set_is_directed(scgl_edge_t *edge, const unsigned int directed) {
	if (edge != NULL) {
		if (edge->is_directed != directed) {
			edge->is_directed = directed;
			if (edge->from != NULL && edge->to != NULL) {
				if (directed == 0) {
					scgl_list_add(&edge->from->in->list, edge);
					scgl_list_add(&edge->to->out->list, edge);
				}
				else {
					scgl_list_delete(&edge->from->in->list, edge);
					scgl_list_delete(&edge->to->out->list, edge);
				}
			}
		}
	}
}

void
scgl_edge_dump(scgl_edge_t *edge, FILE *fp, attr_foreach_function fun) {
	if (edge == NULL || fp == NULL)
		return;

	fprintf(fp,
	        "Edge: %s \n"
	            "\tCost: " cost_fmt "\n"
	            "\tDirected: %s \n"
	            "\tEndpoint 1: %s \n"
	            "\tEndpoint 2: %s \n"
	            "\tAttributes: \n",
	        edge->id,
	        edge->cost,
	        (edge->is_directed == 1 ? "Yes" : "No"),
	        (edge->from ? edge->from->id : NULL),
	        (edge->to ? edge->to->id : NULL));

	scgl_edge_foreach_attribute(edge, fun, fp);
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
