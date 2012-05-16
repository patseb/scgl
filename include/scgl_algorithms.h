#ifndef SCGL_ALGORITHMS_H
#define SCGL_ALGORITHMS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scgl_edge.h"
#include "scgl_def.h"

/**
 * function calculates shortest patch from source to every vertex in graph
 * function implements dijkstra algorithm with heap based priority queue
 * results will be stored in p and d tables.
 * p will contain predecessor of every vertex in graph
 * d will contain distance from source to every vertex in graph
 * p and d will be indexed: 0 ... count(vertexes), 0 means vertex added first to graph, 1 means second added vertex, etc.
 * You can get reference to vertex by scgl_graph_get_vertex_at()
 *
 * @param graph reference to graph object
 * @param src   reference to source vertex
 * @param p    reference to predecessors table, memory have to be allocated by user (vertexes count length)
 * @param d     reference to distance table, memory have to be allocated by user (vertexex count lenght)
 *
 * @see scgl_graph_get_vertex_at()
 */
void scgl_dijkstra(const scgl_graph_t *graph, scgl_vertex_t *src, unsigned int *p, cost_type_t *d);

#ifdef __cplusplus
}
#endif

#endif
