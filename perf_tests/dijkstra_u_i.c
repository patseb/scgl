#include <igraph.h>

int main(void)
{
	unsigned int i;
	igraph_t graph;
	igraph_vector_t edges, weights;
	igraph_matrix_t res;

	igraph_empty(&graph, 13, 0);
	igraph_vector_init(&edges, 44);
	igraph_vector_init(&weights, 22);
	igraph_matrix_init(&res, 0, 0);

	VECTOR(edges)[0]  = 0;
	VECTOR(edges)[1]  = 1;
	VECTOR(edges)[2]  = 0;
	VECTOR(edges)[3]  = 2;
	VECTOR(edges)[4]  = 2;
	VECTOR(edges)[5]  = 1;
	VECTOR(edges)[6]  = 1;
	VECTOR(edges)[7]  = 6;
	VECTOR(edges)[8]  = 1;
	VECTOR(edges)[9]  = 5;
	VECTOR(edges)[10] = 5;
	VECTOR(edges)[11] = 6;
	VECTOR(edges)[12] = 6;
	VECTOR(edges)[13] = 7;
	VECTOR(edges)[14] = 7;
	VECTOR(edges)[15] = 8;
	VECTOR(edges)[16] = 8;
	VECTOR(edges)[17] = 6;
	VECTOR(edges)[18] = 5;
	VECTOR(edges)[19] = 8;
	VECTOR(edges)[20] = 5;
	VECTOR(edges)[21] = 4;
	VECTOR(edges)[22] = 8;
	VECTOR(edges)[23] = 9;
	VECTOR(edges)[24] = 4;
	VECTOR(edges)[25] = 9;
	VECTOR(edges)[26] = 9;
	VECTOR(edges)[27] = 10;
	VECTOR(edges)[28] = 12;
	VECTOR(edges)[29] = 9;
	VECTOR(edges)[30] = 9;
	VECTOR(edges)[31] = 11;
	VECTOR(edges)[32] = 11;
	VECTOR(edges)[33] = 3;
	VECTOR(edges)[34] = 10;
	VECTOR(edges)[35] = 12;
	VECTOR(edges)[36] = 10;
	VECTOR(edges)[37] = 3;
	VECTOR(edges)[38] = 4;
	VECTOR(edges)[39] = 3;
	VECTOR(edges)[40] = 11;
	VECTOR(edges)[41] = 2;
	VECTOR(edges)[42] = 3;
	VECTOR(edges)[43] = 12;

	VECTOR(weights)[0] = 1;
	VECTOR(weights)[1] = 1;
	VECTOR(weights)[2] = 1;
	VECTOR(weights)[3] = 4;
	VECTOR(weights)[4] = 14;
	VECTOR(weights)[5] = 10;
	VECTOR(weights)[6] = 8;
	VECTOR(weights)[7] = 9;
	VECTOR(weights)[8] = 19;
	VECTOR(weights)[9] = 12;
	VECTOR(weights)[10] = 15;
	VECTOR(weights)[11] = 9;
	VECTOR(weights)[12] = 9;
	VECTOR(weights)[13] = 6;
	VECTOR(weights)[14] = 5;
	VECTOR(weights)[15] = 16;
	VECTOR(weights)[16] = 11;
	VECTOR(weights)[17] = 13;
	VECTOR(weights)[18] = 18;
	VECTOR(weights)[19] = 2;
	VECTOR(weights)[20] = 7;
	VECTOR(weights)[21] = 17;

	igraph_add_edges(&graph, &edges, NULL);

	for (i=0; i<10000; ++i)
		igraph_shortest_paths_dijkstra(&graph, &res, igraph_vss_all(), &weights, IGRAPH_OUT);

	igraph_destroy(&graph);
	igraph_vector_destroy(&edges);
	igraph_vector_destroy(&weights);
	igraph_matrix_destroy(&res);

	return 0;
}

