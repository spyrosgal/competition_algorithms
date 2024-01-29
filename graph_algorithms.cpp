#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
#include <climits>
#include "graph_algorithms.h"

using namespace std;

//this function takes as input the edge list (and the size) of a graph and the index of a root and returns the distances from the root to all other vertices.
//if there is a negative cycle, the function returns the empty vector.
vector <int> bellman_ford(int n, vector <tuple <int, int, int> > &edges, int root) {
	vector <int> distances;
	distances.resize(n);
	for (int i = 0; i < n; i++) {
		distances[i] = ((i == root) ? 0 : INT_MAX);
	}

	int a, b, w;
	for (int i = 0; i < n - 1; i++) {
		for (auto e : edges) {
			tie(a, b, w) = e;
			distances[b] = min(distances[b], distances[a] + w);
		}
	}

	for (auto e : edges) {
		tie(a, b, w) = e;
		if (distances[b] > distances[a] + w || distances[a] > distances[b] + w) {
			return {};
		}
	}

	return distances;
}

//a standard implementation of dijkstra's algorithm. It takes as input a graph and the index of the rood and returns a vector
//with the distances from the root to everything else.
vector <int> dijkstra(vector <vector <pair <int, int> > > &graph, int root) {
	int n = graph.size();
	vector <int> distances;
	vector <bool> visited;
	distances.resize(n);
	visited.resize(n);

	priority_queue <pair <int, int>> q;
	q.push(make_pair(0, root));

	for (int i = 0; i < n; i++) {
		distances[i] = ((i == root) ? 0 : INT_MAX);
	}

	int a;
	while (!q.empty()) {
		a = q.top().second;
		q.pop();
		if (!visited[a]) {
			visited[a] = true;
			for (auto u : graph[a]) {
				if (distances[a] + u.first < distances[u.second]) {
					distances[u.second] = distances[a] + u.first;
					q.push(make_pair(-distances[u.second], u.second));
				}
			}
		}
	}

	return distances;
}

//this function finds the most distant node from the root of a tree and returns a pair with the index of the node and the 
//distance from the root. Successive calls of this function require resetting the visited vector.
pair <int, int> farthest(int root, vector <vector <int> > &graph, vector <int>& visited) {
	visited[root] = true;
	pair <int, int> res;
	res.first = root;
	res.second = 0;
	pair <int, int> t;
	for (auto u : graph[root]) {
		if (!visited[u]) {
			t = farthest(u, graph, visited);
			if (t.second + 1 > res.second) {
				res = t;
				res.second++;
			}
		}
	}

	return res;
}

//this function determines the diameter of a tree.
int diam(vector <vector <int> > graph) {
	vector <int> v;
	v.resize(graph.size());
	int w = farthest(0, graph, v).first;
	v.clear();
	v.resize(graph.size());
	return farthest(w, graph, v).second;
}

//auxiliary function for topological_sort.
bool topological_dfs(int root, vector <vector <int> > &dir_graph, vector <int>& visited, vector <int>& top_sort) {
	visited[root] = 1;
	bool t;
	for (auto u : dir_graph[root]) {
		if (visited[u] == 0) {
			t = topological_dfs(u, dir_graph, visited, top_sort);
			if (t == false) return false;
		}
		else if (visited[u] == 1) {
			return false;
		}
	}

	visited[root] = 2;
	top_sort.push_back(root);
	return true;
}

//this function takes as input a directed graph and returns a topological sort of it. 
//If there is a cycle, the function returns the empty vector.
vector <int> topological_sort(vector <vector <int> > &dir_graph) {
	vector <int> res;
	vector <int> visited;
	visited.resize(dir_graph.size());
	bool t;
	for (int i = 0; i < dir_graph.size(); i++) {
		if (visited[i] == 0) {
			t = topological_dfs(i, dir_graph, visited, res);
			if (t == false) return {};
		}
	}

	vector <int> rev_res;
	for (int i = 0; i < res.size(); i++) {
		rev_res.push_back(res[res.size() - 1 - i]);
	}
	return rev_res;
}

//this function takes a successor graph (and the starting node) and returns a pair with the starting node of a cycle and its length
pair <int, int> floyd(int x, vector <int> succ) {
	int a = succ[x];
	int b = succ[succ[x]];
	pair <int, int> res;

	while (a != b) {
		a = succ[a];
		b = succ[succ[b]];
	}

	a = x;
	while (a != b) {
		a = succ[a];
		b = succ[b];
	}
	res.first = a;

	b = succ[a];
	res.second = 1;
	while (a != b) {
		b = succ[b];
		res.second++;
	}

	return res;
}

//auxiliary function for kosajaru's algorithm.
void kosaraju_first_dfs(int root, vector <vector <int> > &dir_graph, vector <bool>& visited, vector <int>& order) {
	visited[root] = true;
	for (auto u : dir_graph[root]) {
		if (!visited[u]) {
			kosaraju_first_dfs(u, dir_graph, visited, order);
		}
	}

	order.push_back(root);
}

//auxiliary function for kosajaru's algorithm.
void kosaraju_second_dfs(int root, vector <vector <int> > &dir_graph, vector <bool>& visited, vector <int>& components) {
	visited[root] = true;
	for (auto u : dir_graph[root]) {
		if (!visited[u]) {
			components[u] = components[root];
			kosaraju_second_dfs(u, dir_graph, visited, components);
		}
	}
}

//this function takes a directed graph and assigns to each vertex an integer representing the strongly connected component it belongs in.
vector <int> kosaraju(vector <vector <int> > &dir_graph) {
	int n = dir_graph.size();
	vector <bool> visited;
	visited.resize(n);

	vector <int> order;
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			kosaraju_first_dfs(i, dir_graph, visited, order);
		}
	}

	vector <vector <int> > aux_graph;
	visited.clear();
	visited.resize(n);
	aux_graph.resize(n);
	for (int i = 0; i < n; i++) {
		for (auto u : dir_graph[i]) {
			aux_graph[u].push_back(i);
		}
	}

	vector <int> components;
	int conncomps = -1;
	components.resize(n);
	for (int i = 0; i < n; i++) {
		if (!visited[order[n - 1 - i]]) {
			conncomps++;
			components[order[n - 1 - i]] = conncomps;
			kosaraju_second_dfs(order[n - 1 - i], aux_graph, visited, components);
		}
	}

	return components;
}

//auxiliary function for Kruskal's algorithm (union-find structure)
bool same(int a, int b, vector <int> &rep) {
	while (rep[a] != a) a = rep[a];
	while (rep[b] != b) b = rep[b];
	return (a == b);
}

//auxiliary function for Kruskal's algorithm (union-find structure)
void unite(int a, int b, vector <int>& rep, vector <int>& size) {
	while (rep[a] != a) a = rep[a];
	while (rep[b] != b) b = rep[b];
	if (size[a] < size[b]) {
		int t = a;
		a = b;
		b = t;
	}

	size[a] += size[b];
	rep[b] = a;
}

//this function takes as input the edges of a graph and returns the edges of the spanning tree produced by Kruskal's algorithm
vector <tuple <int, int, int> > kruskal(vector <tuple <int, int, int> > &graph, int n) {
	sort(graph.begin(), graph.end(), [](const tuple <int, int, int>& a, const tuple <int, int, int>& b) {return get<2>(a) < get<2>(b); });
	vector <int> rep;
	vector <int> size;
	rep.resize(n);
	size.resize(n);
	for (int i = 0; i < n; i++) {
		rep[i] = i;
		size[i] = 1;
	}

	vector <tuple <int, int, int> > res;
	for (auto e : graph) {
		if (!same(get<0>(e), get<1>(e), rep)) {
			unite(get<0>(e), get<1>(e), rep, size);
			res.push_back(e);
		}
	}

	return res;
}