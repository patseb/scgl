#ifndef SCGL_ALGORITHMS_H
#define SCGL_ALGORITHMS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scgl_def.h"

/**
 * function calculates shortest patch from source to every vertex in graph
 * function implements dijkstra algorithm with heap based priority queue
 *
 * @param graph reference to graph object
 * @param scr   reference to source vertex
 * @praram p    reference to predecessors table, function will allocate enought memory (vertexes count)
 * @param d     reference to distance table, function will allocate enought memory (vertexex count)
 *<F7>
 *
 */
void scgl_dijkstra(const scgl_graph_t *graph, scgl_vertex_t *src, unsigned int **p, cost_type **d);

#ifdef __cplusplus
}
#endif

#endif
