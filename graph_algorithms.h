#pragma once
#include <vector>
#include <tuple>

using namespace std;

//this function takes as input the edge list (and the size) of a graph and the index of a root and returns the distances from the root to all other vertices.
//if there is a negative cycle, the function returns the empty vector.
vector <int> bellman_ford(int n, vector <tuple <int, int, int> > &edges, int root);

//a standard implementation of dijkstra's algorithm. It takes as input a graph and the index of the rood and returns a vector
//with the distances from the root to everything else.
vector <int> dijkstra(vector <vector <pair <int, int> > > &graph, int root);

//this function finds the most distant node from the root of a tree and returns a pair with the index of the node and the 
//distance from the root. Successive calls of this function require resetting the visited vector.
pair <int, int> farthest(int root, vector <vector <int> > &graph, vector <int>& visited);

//this function determines the diameter of a tree.
int diam(vector <vector <int> > &graph);

//auxiliary function for topological sort.
bool topological_dfs(int root, vector <vector <int> > &dir_graph, vector <int>& visited, vector <int>& top_sort);

//this function takes as input a directed graph and returns a topological sort of it. 
//If there is a cycle, the function returns the empty vector.
vector <int> topological_sort(vector <vector <int> > &dir_graph);

//this function takes a successor graph (and the starting node) and returns a pair with the starting node of a cycle and its length
pair <int, int> floyd(int x, vector <int> &succ);

//auxiliary function for kosajaru's algorithm.
void kosaraju_first_dfs(int root, vector <vector <int> > &dir_graph, vector <bool>& visited, vector <int>& order);

//auxiliary function for kosajaru's algorithm.
void kosaraju_second_dfs(int root, vector <vector <int> > &dir_graph, vector <bool>& visited, vector <int>& components);

//this function takes a directed graph and assigns to each vertex an integer representing the strongly connected component it belongs in.
vector <int> kosaraju(vector <vector <int> > &dir_graph);

//auxiliary function for Kruskal's algorithm (union-find structure)
bool same(int a, int b, vector <int> &rep);

//auxiliary function for Kruskal's algorithm (union-find structure)
void unite(int a, int b, vector <int>& rep, vector <int>& size);

//this function takes as input the edges of a graph and returns the edges of the spanning tree produced by Kruskal's algorithm
vector <tuple <int, int, int> > kruskal(vector <tuple <int, int, int> > &graph, int n);