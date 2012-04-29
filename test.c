#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scgl_graph.h"
#include "scgl_vertex.h"
#include "scgl_edge.h"

void my_free(char *key, void *value, void *data) {
	free(value);
	free(key);
}

void edge_attr_dump(char *key, void *value, void *fp) {
	if (fp != NULL)
		fprintf((FILE*)fp, "\t\t%s : %s \n", key, (char*)value);
}

int main() {
	scgl_graph_t *g1;//, *g2;
	scgl_vertex_t **v;
	scgl_edge_t **e;
	unsigned int i, n = 1000;
	char *buf;

	buf = (char*) malloc(3);
	sprintf(buf, "G1");
	g1 = scgl_graph_create(buf, NULL, 0, NULL, 0);

	v = (scgl_vertex_t**) malloc(sizeof(scgl_vertex_t*) * n);
	for(i=0; i<n; ++i) {
		buf = (char*) malloc(4);
		sprintf(buf, "%d", i);
		v[i] = scgl_vertex_create(buf, NULL, 0, NULL, 0);
		scgl_graph_add_vertex(g1, v[i]);
	}

	e = (scgl_edge_t**) malloc(sizeof(scgl_edge_t*) * n);
	for(i=0; i<n; ++i) {
		//char buf[10];
		//buf = (char*) malloc(6);
		//sprintf(buf, "E-%d", i);
		e[i] = scgl_edge_create(NULL, NULL, 0, i, NULL, 0);
		//free(buf);
		//char *buf1 = (char*) malloc(10);
		//sprintf(buf1, "%d", i);
		//scgl_edge_add_attribute(e[i], "ATR", buf);
		//free(buf1);
		//scgl_edge_attr_free_function(e[i], my_free);
		scgl_graph_add_edge(g1, e[i]);
	}

	for(i=0; i<n-1; ++i) {
		scgl_edge_set_vertex(e[i], v[i], 0);
		scgl_edge_set_vertex(e[i], v[i+1], 1);
	}
/*
	scgl_edge_destroy(&e[0]);
	scgl_edge_set_undirected(e[1], 1);
	//scgl_edge_set_undirected(e[1], 0);
	scgl_vertex_del_edge(v[1], e[1]);
	scgl_vertex_add_edge(v[1], e[1], 0);
	scgl_vertex_add_edge(v[0], e[1], 0);
	scgl_graph_del_vertex(g1, &v[1]);
	scgl_vertex_destroy(&v[0]);
	scgl_graph_del_edge(g1, &e[3]); 
*/

	//scgl_graph_dump(g1, stdout, edge_attr_dump);
	//g2 = scgl_graph_copy(g1);
	//scgl_graph_dump(g2, stdout, edge_attr_dump);

	/* unnecessary */
	for(i=0; i<n; ++i)
		scgl_edge_destroy(&e[i], my_free);
	/* unnecessary */
	for(i=0; i<n; ++i)
		scgl_vertex_destroy(&v[i]);

	scgl_graph_destroy(&g1, my_free);
	//scgl_graph_destroy(&g2, my_free);

	free(v);
	free(e);

	//printf ("%d \n ", (sizeof(scgl_vertex_t)*1000) + (sizeof(scgl_edge_t)*1000));

	return 0;
}
