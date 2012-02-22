#ifndef SCGL_VERTEX_H
#define SCGL_VERTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "simclist.h"

/* vertex object */
typedef struct {
	/* vertex identyficator */
	char *id;
	/* list of edges which are directed to vertex */
	list_t *in;
	/* list of edges which are directed out of vertex */
	list_t *out;
} scgl_vertex_t;

#ifdef __cplusplus
}
#endif

#endif
