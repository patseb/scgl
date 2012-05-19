#include <igraph.h>

int main(int argc, char **argv) {
	igraph_t graph;
	igraph_vector_t edges;

	igraph_empty(&graph, 1001, 1);
	igraph_vector_init(&edges, 2000);
	igraph_add_edges(&graph, &edges, NULL);

	igraph_destroy(&graph);
	igraph_vector_destroy(&edges);

	return 0;
}

