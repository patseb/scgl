#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef
adjacency_list_traits<vecS, vecS, undirectedS>::vertex_descriptor
Vertex;

typedef
adjacency_list <vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;

int main()
{
	Graph g(6);

	for (int i=0; i<1000; ++i) {
		Edge x = add_edge(i, i+1, g).first;
		get(edge_weight, g, x) = i; }
}
