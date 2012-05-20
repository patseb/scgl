#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scgl.h"

void edge_attr_free(char *key, void *value, void **data) {
	free(value);
}

void edge_attr_dump(char *key, void *value, void **fp) {
	if (fp != NULL && *fp != NULL)
		fprintf((FILE*)*fp, "%s %s ", key, (char*)value);
}

void edge_attr_copy(char *key, void *value, void **data) {
	scgl_attr_t *a;
	char *k, *v;
	if (data != NULL) {
		k = (char*) malloc(strlen(key)+1);
		v = (char*) malloc(strlen((char*)value)+1);
		strcpy(k, key);
		strcpy(v, (char*)value);
		a = scgl_attr_create(k, v);
		*data = a;
	}
}

void edge_foreach(scgl_edge_t *edge, void **data) {
	if (edge != NULL)
		printf(cost_fmt " ", edge->cost);
}

void dijkstra_test(unsigned int undirected) {
	scgl_graph_t *g1;
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
		e[i] = scgl_edge_create(NULL, NULL, undirected, 0, NULL, 0);

	g1 = scgl_graph_create(NULL, v, n, e, m);

	scgl_edge_add_vertex( e[0], v[0],  0);
	scgl_edge_add_vertex( e[0], v[1],  1);
	scgl_edge_add_vertex( e[1], v[0],  0);
	scgl_edge_add_vertex( e[1], v[2],  1);
	scgl_edge_add_vertex( e[2], v[2],  0);
	scgl_edge_add_vertex( e[2], v[1],  1);
	scgl_edge_add_vertex( e[3], v[1],  0);
	scgl_edge_add_vertex( e[3], v[6],  1);
	scgl_edge_add_vertex( e[4], v[1],  0);
	scgl_edge_add_vertex( e[4], v[5],  1);
	scgl_edge_add_vertex( e[5], v[5],  0);
	scgl_edge_add_vertex( e[5], v[6],  1);
	scgl_edge_add_vertex( e[6], v[6],  0);
	scgl_edge_add_vertex( e[6], v[7],  1);
	scgl_edge_add_vertex( e[7], v[7],  0);
	scgl_edge_add_vertex( e[7], v[8],  1);
	scgl_edge_add_vertex( e[8], v[8],  0);
	scgl_edge_add_vertex( e[8], v[6],  1);
	scgl_edge_add_vertex( e[9], v[5],  0);
	scgl_edge_add_vertex( e[9], v[8],  1);
	scgl_edge_add_vertex(e[10], v[5],  0);
	scgl_edge_add_vertex(e[10], v[4],  1);
	scgl_edge_add_vertex(e[11], v[8],  0);
	scgl_edge_add_vertex(e[11], v[9],  1);
	scgl_edge_add_vertex(e[12], v[4],  0);
	scgl_edge_add_vertex(e[12], v[9],  1);
	scgl_edge_add_vertex(e[13], v[9],  0);
	scgl_edge_add_vertex(e[13], v[10], 1);
	scgl_edge_add_vertex(e[14], v[12], 0);
	scgl_edge_add_vertex(e[14], v[9],  1);
	scgl_edge_add_vertex(e[15], v[9],  0);
	scgl_edge_add_vertex(e[15], v[11], 1);
	scgl_edge_add_vertex(e[16], v[11], 0);
	scgl_edge_add_vertex(e[16], v[3],  1);
	scgl_edge_add_vertex(e[17], v[10], 0);
	scgl_edge_add_vertex(e[17], v[12], 1);
	scgl_edge_add_vertex(e[18], v[10], 0);
	scgl_edge_add_vertex(e[18], v[3],  1);
	scgl_edge_add_vertex(e[19], v[4],  0);
	scgl_edge_add_vertex(e[19], v[3],  1);
	scgl_edge_add_vertex(e[20], v[11], 0);
	scgl_edge_add_vertex(e[20], v[2],  1);
	scgl_edge_add_vertex(e[21], v[3],  0);
	scgl_edge_add_vertex(e[21], v[12], 1);
	scgl_edge_set_cost(e[0],   1);
	scgl_edge_set_cost(e[1],   1);
	scgl_edge_set_cost(e[2],   1);
	scgl_edge_set_cost(e[3],   4);
	scgl_edge_set_cost(e[4],  14);
	scgl_edge_set_cost(e[5],  10);
	scgl_edge_set_cost(e[6],   8);
	scgl_edge_set_cost(e[7],   9);
	scgl_edge_set_cost(e[8],  19);
	scgl_edge_set_cost(e[9],  12);
	scgl_edge_set_cost(e[10], 15);
	scgl_edge_set_cost(e[11],  9);
	scgl_edge_set_cost(e[12],  9);
	scgl_edge_set_cost(e[13],  6);
	scgl_edge_set_cost(e[14],  5);
	scgl_edge_set_cost(e[15], 16);
	scgl_edge_set_cost(e[16], 11);
	scgl_edge_set_cost(e[17], 13);
	scgl_edge_set_cost(e[18], 18);
	scgl_edge_set_cost(e[19],  2);
	scgl_edge_set_cost(e[20],  7);
	scgl_edge_set_cost(e[21], 17);

	p = (unsigned int*) malloc(sizeof(unsigned int) * n);
	d = (cost_type_t*) malloc(sizeof(cost_type_t) * n);

	scgl_dijkstra(g1, v[0], p, d);
	for(i=0; i<n; ++i)
		printf("%d, ", p[i]);
	for(i=0; i<n; ++i)
		printf(cost_fmt ", ", d[i]);
	printf("\n");

	scgl_graph_destroy(&g1, edge_attr_free);

	free(p);
	free(d);

	free(v);
	free(e);

}

int main(int argc, char **argv) {
	char *buf1, *buf2;
	scgl_vertex_t *v1, *v2;
	scgl_edge_t *e1, *e2;
	scgl_attr_t *a1;
	scgl_graph_t *g1, *g2;

	if (argc < 3)
		return -1;

	switch (argv[1][0]) {
		case 'v':
			switch (argv[2][0]) {
				case '1': {
					buf1 = (char*) malloc(5);
					sprintf(buf1, "test");
					v1 = scgl_vertex_create(buf1, NULL, 0, NULL, 0);
					if (v1 == NULL)
						return -1;
					printf("%s ", v1->id);
					scgl_vertex_destroy(&v1);
					printf("%d\n", (int)v1);
				} break;

				case '2': {
					buf1 = (char*) malloc(9);
					sprintf(buf1, "test_get");
					v1 = scgl_vertex_create(buf1, NULL, 0, NULL, 0);
					if (v1 == NULL)
						return -1;
					printf("%s ", scgl_vertex_get_id(v1));
					buf1 = (char*) malloc(9);
					sprintf(buf1, "test_set");
					scgl_vertex_set_id(v1, buf1);
					printf("%s", scgl_vertex_get_id(v1));
					printf("\n");
					scgl_vertex_destroy(&v1);
				} break;

				case '3': {
					v1 = scgl_vertex_create(NULL, NULL, 0, NULL, 0);
					e1 = scgl_edge_create(NULL, NULL, 0, 123, NULL, 0);
					if (v1 == NULL || e1 == NULL)
						return -1;
					scgl_vertex_add_edge(v1, e1, 0);
					printf("%d %d ",
					       (int) scgl_vertex_get_edge_out_at(v1, 0),
					       (int) scgl_vertex_get_edge_out_at(v1, 1));
					scgl_vertex_del_edge(v1, e1);
					printf("%d %d ",
					       (int)scgl_vertex_get_edge_out_at(v1, 0),
					       (int)scgl_vertex_get_edge_out_at(v1, 1));
					scgl_vertex_add_edge(v1, e1, 1);
					printf("%d %d\n",
					       (int)scgl_vertex_get_edge_in_at(v1, 0),
					       (int)scgl_vertex_get_edge_in_at(v1, 1));
					scgl_vertex_destroy(&v1);
					scgl_edge_destroy(&e1, NULL);
				} break;

				case '4': {
					v1 = scgl_vertex_create(NULL, NULL, 0, NULL, 0);
					e1 = scgl_edge_create(NULL, NULL, 0, 0, NULL, 0);
					e2 = scgl_edge_create(NULL, NULL, 0, 0, NULL, 0);
					if (v1 == NULL || e1 == NULL || e2 == NULL)
						return -1;
					printf("%d %d ",
					       scgl_vertex_get_edges_in_count(v1),
					       scgl_vertex_get_edges_out_count(v1));
					scgl_vertex_add_edge(v1, e1, 1);
					printf("%d %d ",
					       scgl_vertex_get_edges_in_count(v1),
					       scgl_vertex_get_edges_out_count(v1));
					scgl_vertex_add_edge(v1, e2, 0);
					printf("%d %d\n",
					       scgl_vertex_get_edges_in_count(v1),
					       scgl_vertex_get_edges_out_count(v1));
					scgl_vertex_destroy(&v1);
					scgl_edge_destroy(&e1, NULL);
					scgl_edge_destroy(&e2, NULL);
				} break;

				case '5': {
					v1 = scgl_vertex_create(NULL, NULL, 0, NULL, 0);
					e1 = scgl_edge_create(v1, NULL, 0, 1, NULL, 0);
					e2 = scgl_edge_create(NULL, v1, 0, 2, NULL, 0);
					if (v1 == NULL || e1 == NULL || e2 == NULL)
						return -1;
					scgl_vertex_foreach_edge(v1, 1, edge_foreach, NULL);
					scgl_vertex_foreach_edge(v1, 0, edge_foreach, NULL);
					printf("\n");
					scgl_edge_destroy(&e1, NULL);
					scgl_edge_destroy(&e2, NULL);
					scgl_vertex_destroy(&v1);
				} break;

				default:
					return -1;
			} break;

		case 'a':
			switch (argv[2][0]) {
				case '1': {
					buf1 = (char*) malloc(4);
					buf2 = (char*) malloc(6);
					sprintf(buf1, "key");
					sprintf(buf2, "value");
					a1 = scgl_attr_create(buf1, buf2);
					if (a1 == NULL)
						return -1;
					printf("%s %s ", a1->key, (char*)a1->value);
					scgl_attr_destroy(&a1, edge_attr_free);
					printf("%d\n", (int)a1);
				} break;

				case '2': {
					buf1 = (char*) malloc(4);
					buf2 = (char*) malloc(5);
					sprintf(buf1, "key");
					a1 = scgl_attr_create(buf1, NULL);
					if (a1 == NULL)
						return -1;
					printf("%s ", scgl_attr_get_key(a1));
					sprintf(buf2, "key2");
					scgl_attr_set_key(a1, buf2);
					printf("%s \n", scgl_attr_get_key(a1));
					scgl_attr_destroy(&a1, edge_attr_free);
				} break;

				case '3': {
					buf1 = (char*) malloc(5);
					buf2 = (char*) malloc(5);
					sprintf(buf1, "val1");
					sprintf(buf2, "val2");
					a1 = scgl_attr_create(NULL, buf1);
					if (a1 == NULL)
						return -1;
					printf("%s ", (char*)scgl_attr_get_value(a1));
					scgl_attr_set_value(a1, buf2, edge_attr_free);
					printf("%s \n", (char*)scgl_attr_get_value(a1));
					scgl_attr_destroy(&a1, edge_attr_free);
				} break;
			} break;

		case 'e':
			switch (argv[2][0]) {
				case '1': {
					buf1 = (char*) malloc(2);
					sprintf(buf1, "0");
					v1 = scgl_vertex_create(buf1, NULL, 0, NULL, 0);
					buf1 = (char*) malloc(2);
					sprintf(buf1, "1");
					v2 = scgl_vertex_create(buf1, NULL, 0, NULL, 0);
					if (v1 == NULL || v2 == NULL)
						return -1;
					e1 = scgl_edge_create(v1, v2, 1, 123, NULL, 0);
					if (e1 == NULL)
						return -1;
					printf("%s %s " cost_fmt " " cost_fmt,
					       e1->from->id, e1->to->id, e1->cost, e1->sibling->cost);
					scgl_edge_destroy(&e1, NULL);
					scgl_vertex_destroy(&v1);
					scgl_vertex_destroy(&v2);
					printf(" %d\n", (int)e1);
				} break;

				case '2': {
					e1 = scgl_edge_create(NULL, NULL, 0, 123, NULL, 0);
					if (e1 == NULL)
						return -1;
					printf(cost_fmt " ", scgl_edge_get_cost(e1));
					scgl_edge_set_cost(e1, 321);
					printf(cost_fmt "\n", scgl_edge_get_cost(e1));
					scgl_edge_destroy(&e1, NULL);
				} break;

				case '3': {
					e1 = scgl_edge_create(NULL, NULL, 0, 123, NULL, 0);
					v1 = scgl_vertex_create(NULL, NULL, 0, NULL, 0);
					v2 = scgl_vertex_create(NULL, NULL, 0, NULL, 0);
					if (e1 == NULL || v1 == NULL || v2 == NULL)
						return -1;
					scgl_edge_add_vertex(e1, v1, 0);
					printf("%d %d ",
					       (int)scgl_edge_get_vertex(e1, 0),
					       (int)scgl_edge_get_vertex(e1, 1));
					scgl_edge_del_vertex(e1, v1);
					scgl_edge_add_vertex(e1, v1, 1);
					printf("%d %d ",
					       (int)scgl_edge_get_vertex(e1, 0),
					       (int)scgl_edge_get_vertex(e1, 1));
					scgl_edge_destroy(&e1, NULL);
					e1 = scgl_edge_create(NULL, NULL, 1, 123, NULL, 0);
					if (e1 == NULL || v1 == NULL || v2 == NULL)
						return -1;
					scgl_edge_add_vertex(e1, v1, 0);
					printf("%d %d ",
					       (int)scgl_edge_get_vertex(e1->sibling, 0),
					       (int)scgl_edge_get_vertex(e1->sibling, 1));
					scgl_edge_del_vertex(e1, v1);
					scgl_edge_add_vertex(e1, v1, 1);
					printf("%d %d\n",
					       (int)scgl_edge_get_vertex(e1->sibling, 0),
					       (int)scgl_edge_get_vertex(e1->sibling, 1));
					scgl_edge_destroy(&e1, NULL);
					scgl_vertex_destroy(&v1);
					scgl_vertex_destroy(&v2);
				} break;

				case '4': {
					buf1 = (char*) malloc(5);
					buf2 = (char*) malloc(5);
					sprintf(buf1, "key1");
					sprintf(buf2, "val1");
					e1 = scgl_edge_create(NULL, NULL, 0, 1, NULL, 0);
					if (e1 == NULL)
						return -1;
					scgl_edge_add_attribute(e1, buf1, buf2);
					printf("%s %s %s ",
					       buf1,
					       buf2,
					       (char*)scgl_edge_get_attribute_value(e1, "key1"));
					scgl_edge_del_attribute(e1, "key1", edge_attr_free);
					printf("%d\n",
					       (int)scgl_edge_get_attribute_value(e1, "key1"));
					scgl_edge_destroy(&e1, edge_attr_free);
				} break;

				case '5': {
					buf1 = (char*) malloc(2);
					sprintf(buf1, "1");
					e1 = scgl_edge_create(NULL, NULL, 0, 1, NULL, 0);
					if (e1 == NULL)
						return -1;
					scgl_edge_add_attribute(e1, buf1, NULL);
					printf("%d ", scgl_edge_get_attributes_count(e1));
					scgl_edge_del_attribute(e1, "1", edge_attr_free);
					printf("%d\n", scgl_edge_get_attributes_count(e1));
					scgl_edge_destroy(&e1, edge_attr_free);
				} break;

				case '6': {
					buf1 = (char*) malloc(4);
					buf2 = (char*) malloc(4);
					sprintf(buf1, "key");
					sprintf(buf2, "val");
					e1 = scgl_edge_create(NULL, NULL, 0, 1, NULL, 0);
					if (e1 == NULL)
						return -1;
					scgl_edge_add_attribute(e1, buf1, buf2);
					scgl_edge_foreach_attribute(e1, edge_attr_dump, stdout);
					scgl_edge_destroy(&e1, edge_attr_free);
				} break;

				case '7': {
					e1 = scgl_edge_create(NULL, NULL, 0, 123, NULL, 0);
					v1 = scgl_vertex_create(NULL, NULL, 0, NULL, 0);
					if (e1 == NULL || v1 == NULL || v2 == NULL)
						return -1;
					scgl_edge_add_vertex(e1, v1, 0);
					printf("%d " cost_fmt " %d ",
					       (int)e1->sibling,
					       e1->cost,
					       scgl_vertex_get_edges_out_count(v1));
					scgl_edge_to_undirected(e1);
					printf("%d ", scgl_edge_is_undirected(e1));
					printf("%d " cost_fmt " %d\n",
					       (int)e1->sibling,
					       e1->sibling->cost,
					       scgl_vertex_get_edges_in_count(v1));
					scgl_edge_destroy(&e1, NULL);
					scgl_vertex_destroy(&v1);
				} break;

				default:
					return -1;
			} break;

		case 'g':
			switch (argv[2][0]) {
				case '1': {
					buf1 = (char*) malloc(3);
					sprintf(buf1, "G1");
					g1 = scgl_graph_create(buf1, NULL, 0, NULL, 0);
					if (g1 == NULL)
						return -1;
					printf("%s ", g1->id);
					scgl_graph_destroy(&g1, NULL);
					printf("%d\n", (int)g1);
				} break;

				case '2': {
					buf1 = (char*) malloc(3);
					sprintf(buf1, "G1");
					g1 = scgl_graph_create(buf1, NULL, 0, NULL, 0);
					if (g1 == NULL)
						return -1;
					printf("%s ", scgl_graph_get_id(g1));
					buf1 = (char*) malloc(3);
					sprintf(buf1, "G2");
					scgl_graph_set_id(g1, buf1);
					printf("%s \n", scgl_graph_get_id(g1));
					scgl_graph_destroy(&g1, NULL);
				} break;

				case '3': {
					buf1 = (char*) malloc(3);
					buf2 = (char*) malloc(3);
					sprintf(buf1, "V1");
					sprintf(buf2, "V2");
					g1 = scgl_graph_create(NULL, NULL, 0, NULL, 0);
					v1 = scgl_vertex_create(buf1, NULL, 0, NULL, 0);
					v2 = scgl_vertex_create(buf2, NULL, 0, NULL, 0);
					if (g1 == NULL || v1 == NULL || v2 == NULL)
						return -1;
					scgl_graph_add_vertex(g1, v1);
					scgl_graph_add_vertex(g1, v2);
					printf("%d %s %s ",
					       list_count(&g1->vertexes),
					       scgl_graph_get_vertex(g1, "V2")->id,
					       scgl_graph_get_vertex_at(g1, 0)->id);
					scgl_graph_del_vertex(g1, &v1, NULL);
					printf("%d %d %s \n",
					       list_count(&g1->vertexes),
					       (int)scgl_vertex_get_id(scgl_graph_get_vertex(g1, "V1")),
					       scgl_graph_get_vertex_at(g1, 0)->id);

					scgl_graph_destroy(&g1, NULL);
				} break;

				case '4': {
					g1 = scgl_graph_create(NULL, NULL, 0, NULL, 0);
					e1 = scgl_edge_create(NULL, NULL, 0, 123, NULL, 0);
					e2 = scgl_edge_create(NULL, NULL, 0, 321, NULL, 0);
					if (g1 == NULL || e1 == NULL || e2 == NULL)
						return -1;
					scgl_graph_add_edge(g1, e1);
					scgl_graph_add_edge(g1, e2);
					printf("%d " cost_fmt " " cost_fmt " ",
					       list_count(&g1->edges),
					       scgl_graph_get_edge_at(g1, 0)->cost,
					       scgl_graph_get_edge_at(g1, 1)->cost);
					scgl_graph_del_edge(g1, &e1, NULL);
					printf("%d " cost_fmt " %d\n",
					       list_count(&g1->edges),
					       scgl_graph_get_edge_at(g1, 0)->cost,
					       (int)scgl_graph_get_edge_at(g1, 1));

					scgl_graph_destroy(&g1, NULL);
				} break;

				case '5': {
					g1 = scgl_graph_create(NULL, NULL, 0, NULL, 0);
					v1 = scgl_vertex_create(NULL, NULL, 0, NULL, 0);
					v2 = scgl_vertex_create(NULL, NULL, 0, NULL, 0);
					e1 = scgl_edge_create(NULL, NULL, 0, 0, NULL, 0);
					e2 = scgl_edge_create(NULL, NULL, 0, 0, NULL, 0);
					if (g1 == NULL || v1 == NULL || v2 == NULL || e1 == NULL || e2 == NULL)
						return -1;
					printf("%d %d ",
					       scgl_graph_get_vertexes_count(g1),
					       scgl_graph_get_edges_count(g1));
					
					scgl_graph_add_edge(g1, e1);
					scgl_graph_add_edge(g1, e2);
					scgl_graph_add_vertex(g1, v1);
					scgl_graph_add_vertex(g1, v2);

					printf("%d %d\n",
					       scgl_graph_get_vertexes_count(g1),
					       scgl_graph_get_edges_count(g1));

					scgl_graph_destroy(&g1, NULL);
				} break;

				case '6': {
					buf1 = (char*) malloc(3);
					buf2 = (char*) malloc(3);
					sprintf(buf1, "V1");
					sprintf(buf2, "V2");
					g1 = scgl_graph_create(NULL, NULL, 0, NULL, 0);
					v1 = scgl_vertex_create(buf1, NULL, 0, NULL, 0);
					v2 = scgl_vertex_create(buf2, NULL, 0, NULL, 0);
					e1 = scgl_edge_create(NULL, NULL, 0, 123, NULL, 0);
					e2 = scgl_edge_create(NULL, NULL, 0, 321, NULL, 0);
					if (g1 == NULL || v1 == NULL || v2 == NULL || e1 == NULL || e2 == NULL)
						return -1;

					buf1 = (char*) malloc(4);
					buf2 = (char*) malloc(4);
					sprintf(buf1, "key");
					sprintf(buf2, "val");
					scgl_edge_add_attribute(e1, buf1, buf2);
					scgl_edge_add_vertex(e1, v1, 0);
					scgl_edge_add_vertex(e1, v2, 1);
					scgl_graph_add_edge(g1, e1);
					scgl_graph_add_edge(g1, e2);
					scgl_graph_add_vertex(g1, v1);
					scgl_graph_add_vertex(g1, v2);

					g2 = scgl_graph_copy(g1, edge_attr_copy);
					printf("%d %d %d %d %d %s %s %d %d\n",
					      (g1 == g2),
					      (scgl_graph_get_vertexes_count(g1) == scgl_graph_get_vertexes_count(g2)),
					      (scgl_graph_get_edges_count(g1) == scgl_graph_get_edges_count(g2)),
					      (scgl_graph_get_vertex_at(g1, 0) == scgl_graph_get_vertex_at(g2, 0)),
					      (scgl_graph_get_edge_at(g1, 1)->cost == scgl_graph_get_edge_at(g2, 1)->cost),
					      scgl_graph_get_vertex_at(g1, 1)->id,
					      scgl_graph_get_vertex_at(g2, 1)->id,
					      (scgl_graph_get_edge_at(g1, 0) == scgl_graph_get_edge_at(g2, 0)),
					      (scgl_vertex_get_edge_out_at(scgl_graph_get_vertex_at(g1, 0), 0)->cost == scgl_vertex_get_edge_out_at(scgl_graph_get_vertex_at(g2, 0), 0)->cost));

					scgl_graph_destroy(&g1, edge_attr_free);
					scgl_graph_destroy(&g2, edge_attr_free);
				} break;

				default:
					return -1;
			} break;

		case 'd':
			switch (argv[2][0]) {
				case '1': {
					dijkstra_test(0);
				} break;

				case '2': {
					dijkstra_test(1);
				} break;

				default:
					return -1;
			} break;

		default:
			return -1;
	}

	return 0;
}
