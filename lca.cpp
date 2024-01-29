#include <vector>

using namespace std;

vector <vector <int> > graph;
vector <bool> visited;
vector <vector <int> > preds;
vector <int> dist;
vector <int> pow2s;

int logn = 0;

void fill_dfs(int root, int prev) {
    visited[root] = true;
    preds[root][0] = prev;
    if(root != prev) dist[root] = dist[prev] + 1;
    for(int i = 1; i <= logn; i++) {
        preds[root][i] = preds[preds[root][i - 1]][i - 1];
    }

    for(auto u : graph[root]) {
        if(!visited[u]) fill_dfs(u, root);
    }
}

int ancestor_at_level(int u, int lvl) {
    int d = dist[u] - lvl;
    if(!d) return u;
    int i = logn;

    while(d) {
        if(pow2s[i] <= d) {
            u = preds[u][i];
            d -= pow2s[i];
        }

        i--;
    }

    return u;
}

int lca(int a, int b) {
    if(dist[a] < dist[b]) swap(a, b);
    a = ancestor_at_level(a, dist[b]);
    if(a == b) return a;

    int i = logn;
    while(a != b) {
        while(preds[a][i] == preds[b][i]) {
            i--;
            if(i <= 0) break;
        }

        if(i < 0) i = 0;
        a = preds[a][i];
        b = preds[b][i];
    }

    return a;
}

int main() {
    int n;
    graph.resize(n);
    visited.resize(n, false);
    preds.resize(n);
    dist.resize(n);

    int p = 1;
    while(p < n) {
        p *= 2;
        logn++;
    }

    pow2s.push_back(1);
    for(int i = 1; i <= logn; i++) {
        pow2s.push_back(pow2s[i - 1] * 2);
    }

    fill_dfs(0, 0);

    return 0;
}