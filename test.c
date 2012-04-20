#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scgl_graph.h"
#include "scgl_vertex.h"
#include "scgl_edge.h"
#include "simclist.h"

void my_free(char *key, void *data) {
	free(data);
	data = NULL;
}

void edge_attr_dump(char *key, void *value, void *fp) {
	if (fp != NULL)
		fprintf((FILE*)fp, "\t\t%s : %s \n", key, (char*)value);
}

int main() {
	scgl_graph_t *g1;
	scgl_vertex_t **v;
	scgl_edge_t **e;
	unsigned int i, n = 4;

	g1 = scgl_graph_create("G1", NULL, 0, NULL, 0);

	v = (scgl_vertex_t**) malloc(sizeof(scgl_vertex_t) * n);
	for(i=0; i<n-1; ++i) {
		char buf[10];
		sprintf(buf, "V-%d", i);
		v[i] = scgl_vertex_create(buf, NULL, 0, NULL, 0);
		scgl_graph_add_vertex(g1, v[i]);
	}

	e = (scgl_edge_t**) malloc(sizeof(scgl_edge_t) * n);
	for(i=0; i<n; ++i) {
		char *buf1, *buf2;
		buf1 = (char*) malloc(10);
		sprintf(buf1, "E-%d", i);
		e[i] = scgl_edge_create(buf1, NULL, NULL, 1, 12.0, NULL, 0);
		free(buf1);
		buf1 = (char*) malloc(10);
		sprintf(buf1, "%d", i);
		buf2 = (char*) malloc(sizeof(char)*4);
		sprintf(buf2, "ATR");
		scgl_edge_add_attribute(e[i], buf1, buf2);
		free(buf1);
		scgl_edge_attr_free_function(e[i], my_free);
		scgl_graph_add_edge(g1, e[i]);
	}

	scgl_edge_set_vertex(e[0], v[0], 0);
	scgl_edge_set_vertex(e[0], v[1], 1);

	scgl_edge_set_vertex(e[1], v[0], 0);
	scgl_edge_set_vertex(e[1], v[2], 1);

	scgl_edge_set_vertex(e[2], v[1], 0);
	scgl_edge_set_vertex(e[2], v[2], 1);

	scgl_edge_set_vertex(e[3], v[0], 0);
	scgl_edge_set_vertex(e[3], v[0], 1);

	//e[2]->is_directed = 0;
	scgl_graph_dump(g1, stdout, edge_attr_dump);

	/* unnecessary */
	for(i=0; i<n; ++i)
		scgl_edge_destroy(&e[i]);
	/* unnecessary */
	for(i=0; i<n-1; ++i)
		scgl_vertex_destroy(&v[i]);

	scgl_graph_destroy(&g1);

	free(v);
	free(e);

	return 0;
}
