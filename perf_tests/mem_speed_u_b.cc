#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef
adjacency_list_traits<vecS, vecS, undirectedS>::vertex_descriptor
Vertex;

typedef
adjacency_list <vecS, vecS, undirectedS, no_property, property<edge_weight_t, unsigned int> >
Graph;

typedef
graph_traits<Graph>::edge_descriptor
Edge;

int main(int argc, char **argv) {
	unsigned int i, j;

	for (i=0; i<1000; ++i) {
		Graph g;

		for(j=0; j<1001; ++j)
			add_vertex(g);

		for(j=0; j<1000; ++j) {
			Edge e1 = add_edge(j, j+1, g).first;
			get(edge_weight, g, e1) = j;
		}
	}

	return 0;
}
