#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef
adjacency_list_traits<vecS, vecS, directedS>::vertex_descriptor
Vertex;

typedef
adjacency_list <vecS, vecS, directedS, no_property, property<edge_weight_t, int> >
Graph;

typedef
graph_traits<Graph>::edge_descriptor
Edge;

int main()
{
	for (unsigned int i=0; i<1000; ++i) {
		Graph g(0);

		for(unsigned int j=0; j<1000; ++j) {
			Edge e1 = add_edge(j, j+1, g).first;
			get(edge_weight, g, e1) = j;
		}
	}
}
