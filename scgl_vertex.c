#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl_list.h"
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

	v->in = (scgl_list_t*) malloc(sizeof(scgl_list_t));
	v->out = (scgl_list_t*) malloc(sizeof(scgl_list_t));
	INIT_LIST_HEAD(&v->in->list);
	INIT_LIST_HEAD(&v->out->list);

	for (i=0; i<in_n; ++i)
		if (in[i] != NULL) {
			scgl_list_add(&v->in->list, in[i]);
			in[i]->to = v;
		}

	for (i=0; i<out_n; ++i)
		if (out[i] != NULL) {
			scgl_list_add(&v->out->list, out[i]);
			out[i]->from = v;
		}

	return v;
}

void
scgl_vertex_destroy(scgl_vertex_t **vertex) {
	list_head_t *i;
	scgl_list_t *tmp;

	if (vertex != NULL && *vertex != NULL) {
		if ((*vertex)->in != NULL) {
			list_for_each(i, &(*vertex)->in->list) {
				tmp = list_entry(i, scgl_list_t, list);
				scgl_vertex_del_edge(*vertex, (scgl_edge_t*)tmp->data);
			}
		}

		if ((*vertex)->out != NULL) {
			list_for_each(i, &(*vertex)->out->list) {
				tmp = list_entry(i, scgl_list_t, list);
				scgl_vertex_del_edge(*vertex, (scgl_edge_t*)tmp->data);
			}
		}

		if ((*vertex)->owner != NULL)
			scgl_list_delete(&(*vertex)->owner->vertexes->list, *vertex);

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

char*
scgl_vertex_get_id(const scgl_vertex_t *vertex) {
	return (vertex == NULL ? NULL : vertex->id);
}

void
scgl_vertex_set_id(scgl_vertex_t *vertex, const char *id) {
	if (vertex == NULL || id == NULL)
		return;

	if (vertex->id != NULL)
		free(vertex->id);
	vertex->id = (char*) malloc(strlen(id)+1);

	strcpy(vertex->id, id);
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
		scgl_list_delete(&vertex->out->list, edge);
		if (edge->is_directed == 0)
			scgl_list_delete(&vertex->in->list, edge);
		edge->from = NULL;
	}
	else if (edge->to == vertex) {
		scgl_list_delete(&vertex->in->list, edge);
		if (edge->is_directed == 0)
			scgl_list_delete(&vertex->out->list, edge);
		edge->to = NULL;
	}
	else
		return -1;

	return 0;
}

int
scgl_vertex_get_edges_in_count(const scgl_vertex_t *vertex) {
	return (vertex == NULL ? -1 : scgl_list_count(&vertex->in->list));
}

int
scgl_vertex_get_edges_out_count(const scgl_vertex_t *vertex) {
	return (vertex == NULL ? -1 : scgl_list_count(&vertex->out->list));
}

scgl_edge_t*
scgl_vertex_get_edge_in_at(const scgl_vertex_t *vertex, unsigned int i) {
	//return (vertex == NULL ? NULL : list_get_at(vertex->in, i));
	return NULL;
}

scgl_edge_t*
scgl_vertex_get_edge_out_at(const scgl_vertex_t *vertex, unsigned int i) {
	//return (vertex == NULL ? NULL : list_get_at(vertex->out, i));
	return NULL;
}

void
scgl_vertex_foreach_edge(const scgl_vertex_t *vertex, unsigned int direction, edge_foreach_function fun, void *data) {
	scgl_list_t *tmp;
	list_head_t *l, *i;

	if (vertex == NULL || (direction != 0 && direction != 1))
		return;

	l = direction ? &vertex->out->list : &vertex->in->list;
	if (l != NULL) {
		list_for_each(i, l) {
			tmp = list_entry(i, scgl_list_t, list);
			if (tmp != NULL)
				(*fun)((scgl_edge_t*)tmp->data, data);
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

	fprintf(fp, "Vertex: %s \n", vertex->id);

	fprintf(fp, "\tIncoming edges (%d):", (vertex->in ? scgl_vertex_get_edges_in_count(vertex) : 0));
	scgl_vertex_foreach_edge(vertex, 0, scgl_vertex_dump_edge, fp);

	fprintf(fp, "\n\tOutgoing edges (%d):", (vertex->out ? scgl_vertex_get_edges_out_count(vertex) : 0));
	scgl_vertex_foreach_edge(vertex, 1, scgl_vertex_dump_edge, fp);

	fprintf(fp, "\n");
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


