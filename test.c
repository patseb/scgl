#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scgl_algorithms.h"
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
	unsigned int i, n = 13, m = 22;
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

	e = (scgl_edge_t**) malloc(sizeof(scgl_edge_t*) * m);
	for(i=0; i<m; ++i) {
		//char buf[10];
		//buf = (char*) malloc(6);
		//sprintf(buf, "E-%d", i);
		e[i] = scgl_edge_create(NULL, NULL, 1, 0, NULL, 0);
		//free(buf);
		//char *buf1 = (char*) malloc(10);
		//sprintf(buf1, "%d", i);
		//scgl_edge_add_attribute(e[i], "ATR", buf);
		//free(buf1);
		//scgl_edge_attr_free_function(e[i], my_free);
		scgl_graph_add_edge(g1, e[i]);
	}

	//for(i=0; i<n-1; ++i) {
		scgl_edge_set_vertex(e[0], v[0], 0);
		scgl_edge_set_vertex(e[0], v[1], 1);
		scgl_edge_set_vertex(e[1], v[0], 0);
		scgl_edge_set_vertex(e[1], v[2], 1);
		scgl_edge_set_vertex(e[2], v[2], 0);
		scgl_edge_set_vertex(e[2], v[1], 1);
		scgl_edge_set_vertex(e[3], v[1], 0);
		scgl_edge_set_vertex(e[3], v[6], 1);
		scgl_edge_set_vertex(e[4], v[1], 0);
		scgl_edge_set_vertex(e[4], v[5], 1);
		scgl_edge_set_vertex(e[5], v[5], 0);
		scgl_edge_set_vertex(e[5], v[6], 1);
		scgl_edge_set_vertex(e[6], v[6], 0);
		scgl_edge_set_vertex(e[6], v[7], 1);
		scgl_edge_set_vertex(e[7], v[7], 0);
		scgl_edge_set_vertex(e[7], v[8], 1);
		scgl_edge_set_vertex(e[8], v[8], 0);
		scgl_edge_set_vertex(e[8], v[6], 1);
		scgl_edge_set_vertex(e[9], v[5], 0);
		scgl_edge_set_vertex(e[9], v[8], 1);
		scgl_edge_set_vertex(e[10], v[5], 0);
		scgl_edge_set_vertex(e[10], v[4], 1);
		scgl_edge_set_vertex(e[11], v[8], 0);
		scgl_edge_set_vertex(e[11], v[9], 1);
		scgl_edge_set_vertex(e[12], v[4], 0);
		scgl_edge_set_vertex(e[12], v[9], 1);
		scgl_edge_set_vertex(e[13], v[9], 0);
		scgl_edge_set_vertex(e[13], v[10], 1);
		scgl_edge_set_vertex(e[14], v[12], 0);
		scgl_edge_set_vertex(e[14], v[9], 1);
		scgl_edge_set_vertex(e[15], v[9], 0);
		scgl_edge_set_vertex(e[15], v[11], 1);
		scgl_edge_set_vertex(e[16], v[11], 0);
		scgl_edge_set_vertex(e[16], v[3], 1);
		scgl_edge_set_vertex(e[17], v[10], 0);
		scgl_edge_set_vertex(e[17], v[12], 1);
		scgl_edge_set_vertex(e[18], v[10], 0);
		scgl_edge_set_vertex(e[18], v[3], 1);
		scgl_edge_set_vertex(e[19], v[4], 0);
		scgl_edge_set_vertex(e[19], v[3], 1);
		scgl_edge_set_vertex(e[20], v[11], 0);
		scgl_edge_set_vertex(e[20], v[2], 1);
		scgl_edge_set_vertex(e[21], v[3], 0);
		scgl_edge_set_vertex(e[21], v[12], 1);
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
	//}
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

	scgl_graph_dump(g1, stdout, edge_attr_dump);

	unsigned int *p = NULL;
	cost_type *d = NULL;
	scgl_dijkstra(g1, v[0], &p, &d);
	printf("pred = ");
	for(i=0; i<n; ++i)
		printf("%d, ", p[i]);
	printf("\ndist = ");
	for(i=0; i<n; ++i)
		printf(cost_fmt ", ", d[i]);
	printf("\n");
	free(p);
	free(d);
	//g2 = scgl_graph_copy(g1);
	//scgl_graph_dump(g2, stdout, edge_attr_dump);

	/* unnecessary */
	for(i=0; i<m; ++i)
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
