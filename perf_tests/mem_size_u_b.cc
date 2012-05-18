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

int main()
{
	Graph g(0);

	for(unsigned int i=0; i<1000; ++i) {
		Edge e1 = add_edge(i, i+1, g).first;
		get(edge_weight, g, e1) = i;
  }
}
