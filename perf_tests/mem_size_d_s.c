#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl.h"

int main(int argc, char **argv) {
	scgl_graph_t *g1;
	scgl_vertex_t *v;
	scgl_edge_t *e;
	unsigned int i, n = 1001, m = 1000;

	g1 = scgl_graph_create(NULL, NULL, 0, NULL, 0);

	for(i=0; i<n; ++i) {
		v = scgl_vertex_create(NULL, NULL, 0, NULL, 0);
		scgl_graph_add_vertex(g1, v);
	}

	for(i=0; i<m; ++i) {
		e = scgl_edge_create(NULL, NULL, 0, i, NULL, 0);
		scgl_graph_add_edge(g1, e);
	}

	scgl_graph_destroy(&g1, NULL);

	return 0;
}
