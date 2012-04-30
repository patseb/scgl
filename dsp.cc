#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef
adjacency_list_traits<vecS, vecS, undirectedS>::vertex_descriptor
Vertex;

typedef
adjacency_list <vecS, vecS, undirectedS, no_property, 
		property<edge_weight_t, int> >
Graph;

// typedef
// adjacency_list <vecS, vecS, undirectedS,
//                 property<vertex_distance_t, vector<int>,
//                 property<vertex_predecessor_t, vector<Vertex> > >,
//                 property<edge_weight_t, int> >
// Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;

/**
 * This is the << operator for a vector.
 */
template <typename T>
ostream &operator << (ostream &os, const vector<T> &v)
{
  typename vector<T>::const_iterator i = v.begin();

  while(i != v.end())
    {
      os << *i;
      if (++i != v.end())
        os << ", ";
    }

  return os;
}

int main()
{
  Graph g(3);

  Edge e1 = add_edge(0, 1, g).first;
  Edge e2 = add_edge(1, 2, g).first;
//  Edge e3 = add_edge(2, 5, g).first;
//  Edge e4 = add_edge(1, 3, g).first;
//  Edge e5 = add_edge(2, 4, g).first;
//  Edge e6 = add_edge(0, 3, g).first;
//  Edge e7 = add_edge(3, 4, g).first;
//  Edge e8 = add_edge(4, 5, g).first;

  get(edge_weight, g, e1) = 1;
  get(edge_weight, g, e2) = 2;
//  get(edge_weight, g, e3) = 4;
//  get(edge_weight, g, e4) = 1;
//  get(edge_weight, g, e5) = 5;
//  get(edge_weight, g, e6) = 10;
//  get(edge_weight, g, e7) = 1;
//  get(edge_weight, g, e8) = 2;

  vector<int> dist(num_vertices(g));
  vector<Vertex> pred(num_vertices(g));

  // Source vertex.
  Vertex s = 0;
  dijkstra_shortest_paths
    (g, s, predecessor_map(&pred[0]).distance_map(&dist[0]));

  cout << "dist = " << dist << endl;
  cout << "pred = " << pred << endl;
}
