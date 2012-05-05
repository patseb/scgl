#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scgl_edge.h"
#include "scgl_vertex.h"

scgl_vertex_t*
scgl_vertex_create(char *id, scgl_edge_t **in, unsigned int in_n, scgl_edge_t **out, unsigned int out_n) {
	scgl_vertex_t *v;
	unsigned int i;

	v = (scgl_vertex_t*) malloc(sizeof(scgl_vertex_t));
	assert(v != NULL);

	INIT_LIST_HEAD(&v->in);
	INIT_LIST_HEAD(&v->out);
	INIT_LIST_HEAD(&v->owner_list);

	v->id = id;

	for (i=0; i<in_n; ++i)
		if (in[i] != NULL) {
			list_add_tail(&in[i]->to_list, &v->in);
			in[i]->to = v;
		}

	for (i=0; i<out_n; ++i)
		if (out[i] != NULL) {
			list_add_tail(&out[i]->from_list, &v->out);
			out[i]->from = v;
		}

	return v;
}

void
scgl_vertex_destroy(scgl_vertex_t **vertex) {
	list_head_t *i, *j;
	scgl_edge_t *tmp;

	if (vertex != NULL && *vertex != NULL) {
		list_for_each_safe(i, j, &(*vertex)->in) {
			tmp = list_entry(i, scgl_edge_t, to_list);
			scgl_vertex_del_edge(*vertex, tmp);
		}

		list_for_each_safe(i, j, &(*vertex)->out) {
			tmp = list_entry(i, scgl_edge_t, from_list);
			scgl_vertex_del_edge(*vertex, tmp);
		}

		list_del(&(*vertex)->owner_list);

		free((*vertex)->id);
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
scgl_vertex_set_id(scgl_vertex_t *vertex, char *id) {
	if (vertex == NULL || id == NULL)
		return;

	if (vertex->id != NULL)
		free(vertex->id);

	vertex->id = id;
}

int
scgl_vertex_add_edge(scgl_vertex_t *vertex, scgl_edge_t *edge, unsigned int endpoint) {
	if (endpoint != 0 && endpoint != 1)
		endpoint = 0;
	return scgl_edge_add_vertex(edge, vertex, endpoint);
}

int
scgl_vertex_del_edge(scgl_vertex_t *vertex, scgl_edge_t *edge) {
	if (vertex == NULL || edge == NULL)
		return -1;

	if (edge->from == vertex) {
		list_del(&edge->from_list);
		if (edge->sibling != NULL) {
			list_del(&edge->sibling->to_list);
			edge->sibling->to = NULL;
		}
		edge->from = NULL;
	}
	else if (edge->to == vertex) {
		list_del(&edge->to_list);
		if (edge->sibling != NULL) {
			list_del(&edge->sibling->from_list);
			edge->sibling->from = NULL;
		}
		edge->to = NULL;
	}
	else
		return -1;

	return 0;
}

int
scgl_vertex_get_edges_in_count(const scgl_vertex_t *vertex) {
	return (vertex == NULL ? -1 : list_count(&vertex->in));
}

int
scgl_vertex_get_edges_out_count(const scgl_vertex_t *vertex) {
	return (vertex == NULL ? -1 : list_count(&vertex->out));
}

scgl_edge_t*
scgl_vertex_get_edge_in_at(const scgl_vertex_t *vertex, unsigned int i) {
	unsigned int k = 0;
	list_head_t *j;

	if (vertex == NULL)
		return NULL;

	list_for_each(j, &vertex->in) {
		if (i == k++)
			return list_entry(j, scgl_edge_t, to_list);
	}
	return NULL;
}

scgl_edge_t*
scgl_vertex_get_edge_out_at(const scgl_vertex_t *vertex, unsigned int i) {
	unsigned int k = 0;
	list_head_t *j;

	if (vertex == NULL)
		return NULL;

	list_for_each(j, &vertex->out) {
		if (i == k++)
			return list_entry(j, scgl_edge_t, from_list);
	}
	return NULL;
}

void
scgl_vertex_foreach_edge(const scgl_vertex_t *vertex, unsigned int direction, edge_foreach_function fun, void *data) {
	scgl_edge_t *tmp;
	list_head_t *i;

	if (vertex == NULL || (direction != 0 && direction != 1))
		return;

	if (direction) {
		list_for_each(i, &vertex->out) {
			tmp = list_entry(i, scgl_edge_t, from_list);
			(*fun)(tmp, &data);
		}
	}
	else {
		list_for_each(i, &vertex->in) {
			tmp = list_entry(i, scgl_edge_t, to_list);
			(*fun)(tmp, &data);
		}
	}
}

static void
scgl_vertex_dump_edge(scgl_edge_t *edge, void **data) {
	if (edge != NULL) {
		if (edge->sibling != NULL)
			fprintf((FILE*)data, " %p(s: %p)", (void*)edge, (void*)edge->sibling);
		else
			fprintf((FILE*)data, " %p", (void*)edge);
	}
}

void
scgl_vertex_dump(scgl_vertex_t *vertex, FILE *fp) {
	if (vertex == NULL || fp == NULL)
		return;

	fprintf(fp, "Vertex: [%s] %p \n", vertex->id, (void*)vertex);

	fprintf(fp, "\tIncoming edges (%d):", scgl_vertex_get_edges_in_count(vertex));
	scgl_vertex_foreach_edge(vertex, 0, scgl_vertex_dump_edge, fp);

	fprintf(fp, "\n\tOutgoing edges (%d):", scgl_vertex_get_edges_out_count(vertex));
	scgl_vertex_foreach_edge(vertex, 1, scgl_vertex_dump_edge, fp);

	fprintf(fp, "\n");
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


