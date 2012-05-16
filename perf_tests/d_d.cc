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
	Graph g(13);

	Edge  e1 = add_edge(0,  1, g).first;
	Edge  e2 = add_edge(0,  2, g).first;
	Edge  e3 = add_edge(2,  1, g).first;
	Edge  e4 = add_edge(1,  6, g).first;
	Edge  e5 = add_edge(1,  5, g).first;
	Edge  e6 = add_edge(5,  6, g).first;
	Edge  e7 = add_edge(6,  7, g).first;
	Edge  e8 = add_edge(7,  8, g).first;
	Edge  e9 = add_edge(8,  6, g).first;
	Edge e10 = add_edge(5,  8, g).first;
	Edge e11 = add_edge(5,  4, g).first;
	Edge e12 = add_edge(8,  9, g).first;
	Edge e13 = add_edge(4,  9, g).first;
	Edge e14 = add_edge(9, 10, g).first;
	Edge e15 = add_edge(12, 9, g).first;
	Edge e16 = add_edge(9, 11, g).first;
	Edge e17 = add_edge(11, 3, g).first;
	Edge e18 = add_edge(10,12, g).first;
	Edge e19 = add_edge(10, 3, g).first;
	Edge e20 = add_edge(4,  3, g).first;
	Edge e21 = add_edge(11, 2, g).first;
	Edge e22 = add_edge(3, 12, g).first;

	get(edge_weight, g,  e1) = 1;
	get(edge_weight, g,  e2) = 1;
	get(edge_weight, g,  e3) = 1;
	get(edge_weight, g,  e4) = 4;
	get(edge_weight, g,  e5) = 14;
	get(edge_weight, g,  e6) = 10;
	get(edge_weight, g,  e7) = 8;
	get(edge_weight, g,  e8) = 9;
	get(edge_weight, g,  e9) = 19;
	get(edge_weight, g, e10) = 12;
	get(edge_weight, g, e11) = 15;
	get(edge_weight, g, e12) = 9;
	get(edge_weight, g, e13) = 9;
	get(edge_weight, g, e14) = 6;
	get(edge_weight, g, e15) = 5;
	get(edge_weight, g, e16) = 16;
	get(edge_weight, g, e17) = 11;
	get(edge_weight, g, e18) = 13;
	get(edge_weight, g, e19) = 18;
	get(edge_weight, g, e20) = 2;
	get(edge_weight, g, e21) = 7;
	get(edge_weight, g, e22) = 17;

	vector<int> dist(num_vertices(g));
	vector<Vertex> pred(num_vertices(g));
	Vertex s = 0;

	for (unsigned int i=0; i<10000; ++i)
		dijkstra_shortest_paths(g, s, predecessor_map(&pred[0]).distance_map(&dist[0]));

	return 0;
}
