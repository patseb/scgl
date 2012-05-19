#include <stdio.h>
#include <stdlib.h>
#include "scgl.h"

int main(int argc, char **argv) {
	scgl_graph_t *g1;
	scgl_vertex_t **v;
	scgl_edge_t **e;
	unsigned int i, j, n = 1001, m = 1000;

	for(i=0; i<1000; ++i) {
		v = (scgl_vertex_t**) malloc(sizeof(scgl_vertex_t*) * n);
		for(j=0; j<n; ++j)
			v[j] = scgl_vertex_create(NULL, NULL, 0, NULL, 0);

		e = (scgl_edge_t**) malloc(sizeof(scgl_edge_t*) *m);
		for(j=0; j<m; ++j)
			e[j] = scgl_edge_create(v[j], v[j+1], 1, i, NULL, 0);

		g1 = scgl_graph_create(NULL, v, n, e, m);
		scgl_graph_destroy(&g1, NULL);
		free(v);
		free(e);
	}

	return 0;
}
