#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simclist.h"
#include "scgl_edge.h"
#include "scgl_pair.h"
#include "scgl_vertex.h"

edge_t*
edge_create(char *id, vertex_t *from, vertex_t *to, int is_directed, double weight, pair_t **attr, unsigned int attr_n) {
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
