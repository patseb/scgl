#ifndef SCGL_EDGE_H
#define SCGL_EDGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"
#include "scgl_vertex.h"

typedef struct {
	/* edge identyficator */
	char *id;
	/* 0 - edge is undirected, edge is 1 directed */
	int is_directed;
	double weight;
	/* edge source vertex */
	scgl_vertex_t *from;
	/* edge destination vertex */
	scgl_vertex_t *to;
	/* user-purpose list of edge attributes */
	list_t *attributes;
} scgl_edge_t;

#ifdef __cplusplus
}
#endif

#endif
