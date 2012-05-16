#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl.h"

int main() {
	unsigned int j;

	for (j=0; j<1000; ++j) {
		scgl_graph_t *g1;
		scgl_vertex_t **v;
		scgl_edge_t **e;
		unsigned int i, n = 1001, m = 1000;

		v = (scgl_vertex_t**) malloc(sizeof(scgl_vertex_t*) * n);
		for(i=0; i<n; ++i)
			v[i] = scgl_vertex_create(NULL, NULL, 0, NULL, 0);

		e = (scgl_edge_t**) malloc(sizeof(scgl_edge_t*) * m);
		for(i=0; i<m; ++i)
			e[i] = scgl_edge_create(v[i], v[i+1], 0, i, NULL, 0);

		g1 = scgl_graph_create(NULL, v, n, e, m);

		scgl_graph_destroy(&g1, NULL);

		free(v);
		free(e);
	}

	return 0;
}
