#ifndef SCGL_GRAPH_H
#define SCGL_GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"

typedef struct {
	/* graph identyficator */
	char *id;
	/* list of all graph vertexes */
	list_t *vertexes;
	/* list of all graph edges */
	list_t *edges;
} scgl_graph_t;

#ifdef __cplusplus
}
#endif

#endif
