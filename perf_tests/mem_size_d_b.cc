#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef
adjacency_list_traits<vecS, vecS, directedS>::vertex_descriptor
Vertex;

typedef
adjacency_list <vecS, vecS, directedS, no_property, property<edge_weight_t, unsigned int> >
Graph;

typedef
graph_traits<Graph>::edge_descriptor
Edge;

int main()
{
	unsigned int i;
	Graph g;

	for(i=0; i<1000; ++i) {
		add_vertex(g);
		add_edge(i, i+1, g);
	}
}
