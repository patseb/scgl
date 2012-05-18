#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl.h"

int main() {
	scgl_graph_t *g1;;
	scgl_vertex_t **v;
	scgl_edge_t **e;
	unsigned int *p;
	cost_type_t *d;
	unsigned int i, n = 13, m = 22;

	v = (scgl_vertex_t**) malloc(sizeof(scgl_vertex_t*) * n);
	for(i=0; i<n; ++i)
		v[i] = scgl_vertex_create(NULL, NULL, 0, NULL, 0);

	e = (scgl_edge_t**) malloc(sizeof(scgl_edge_t*) * m);
	for(i=0; i<m; ++i)
		e[i] = scgl_edge_create(NULL, NULL, 0, 0, NULL, 0);

	g1 = scgl_graph_create(NULL, v, n, e, m);

	scgl_edge_add_vertex(e[0], v[0], 0);
	scgl_edge_add_vertex(e[0], v[1], 1);
	scgl_edge_add_vertex(e[1], v[0], 0);
	scgl_edge_add_vertex(e[1], v[2], 1);
	scgl_edge_add_vertex(e[2], v[2], 0);
	scgl_edge_add_vertex(e[2], v[1], 1);
	scgl_edge_add_vertex(e[3], v[1], 0);
	scgl_edge_add_vertex(e[3], v[6], 1);
	scgl_edge_add_vertex(e[4], v[1], 0);
	scgl_edge_add_vertex(e[4], v[5], 1);
	scgl_edge_add_vertex(e[5], v[5], 0);
	scgl_edge_add_vertex(e[5], v[6], 1);
	scgl_edge_add_vertex(e[6], v[6], 0);
	scgl_edge_add_vertex(e[6], v[7], 1);
	scgl_edge_add_vertex(e[7], v[7], 0);
	scgl_edge_add_vertex(e[7], v[8], 1);
	scgl_edge_add_vertex(e[8], v[8], 0);
	scgl_edge_add_vertex(e[8], v[6], 1);
	scgl_edge_add_vertex(e[9], v[5], 0);
	scgl_edge_add_vertex(e[9], v[8], 1);
	scgl_edge_add_vertex(e[10], v[5], 0);
	scgl_edge_add_vertex(e[10], v[4], 1);
	scgl_edge_add_vertex(e[11], v[8], 0);
	scgl_edge_add_vertex(e[11], v[9], 1);
	scgl_edge_add_vertex(e[12], v[4], 0);
	scgl_edge_add_vertex(e[12], v[9], 1);
	scgl_edge_add_vertex(e[13], v[9], 0);
	scgl_edge_add_vertex(e[13], v[10], 1);
	scgl_edge_add_vertex(e[14], v[12], 0);
	scgl_edge_add_vertex(e[14], v[9], 1);
	scgl_edge_add_vertex(e[15], v[9], 0);
	scgl_edge_add_vertex(e[15], v[11], 1);
	scgl_edge_add_vertex(e[16], v[11], 0);
	scgl_edge_add_vertex(e[16], v[3], 1);
	scgl_edge_add_vertex(e[17], v[10], 0);
	scgl_edge_add_vertex(e[17], v[12], 1);
	scgl_edge_add_vertex(e[18], v[10], 0);
	scgl_edge_add_vertex(e[18], v[3], 1);
	scgl_edge_add_vertex(e[19], v[4], 0);
	scgl_edge_add_vertex(e[19], v[3], 1);
	scgl_edge_add_vertex(e[20], v[11], 0);
	scgl_edge_add_vertex(e[20], v[2], 1);
	scgl_edge_add_vertex(e[21], v[3], 0);
	scgl_edge_add_vertex(e[21], v[12], 1);
	scgl_edge_set_cost(e[0], 1);
	scgl_edge_set_cost(e[1], 1);
	scgl_edge_set_cost(e[2], 1);
	scgl_edge_set_cost(e[3], 4);
	scgl_edge_set_cost(e[4], 14);
	scgl_edge_set_cost(e[5], 10);
	scgl_edge_set_cost(e[6], 8);
	scgl_edge_set_cost(e[7], 9);
	scgl_edge_set_cost(e[8], 19);
	scgl_edge_set_cost(e[9], 12);
	scgl_edge_set_cost(e[10], 15);
	scgl_edge_set_cost(e[11], 9);
	scgl_edge_set_cost(e[12], 9);
	scgl_edge_set_cost(e[13], 6);
	scgl_edge_set_cost(e[14], 5);
	scgl_edge_set_cost(e[15], 16);
	scgl_edge_set_cost(e[16], 11);
	scgl_edge_set_cost(e[17], 13);
	scgl_edge_set_cost(e[18], 18);
	scgl_edge_set_cost(e[19], 2);
	scgl_edge_set_cost(e[20], 7);
	scgl_edge_set_cost(e[21], 17);

	p = (unsigned int*) malloc(sizeof(unsigned int) * n);
	d = (cost_type_t*) malloc(sizeof(cost_type_t*) *n);

	for (i=0; i<10000; ++i)
		scgl_dijkstra(g1, v[0], p, d);

	free(p);
	free(d);

	scgl_graph_destroy(&g1, NULL);

	free(v);
	free(e);

	return 0;
}
