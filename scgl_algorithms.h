#ifndef SCGL_ALGORITHMS_H
#define SCGL_ALGORITHMS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scgl_def.h"

void scgl_dijkstra(const scgl_graph_t *graph, scgl_vertex_t *src, unsigned int **p, cost_type **d);

#ifdef __cplusplus
}
#endif

#endif
