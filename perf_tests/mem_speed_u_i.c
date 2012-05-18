#include <igraph.h>

int main(void)
{
	unsigned int i;

	for (i=0; i<1000; ++i) {
		igraph_t graph;
		igraph_vector_t edges;

		igraph_empty(&graph, 1001, 0);
		igraph_vector_init(&edges, 2000);
		igraph_add_edges(&graph, &edges, NULL);

		igraph_destroy(&graph);
		igraph_vector_destroy(&edges);
	}
	return 0;
}

