#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define fst first
#define scd second

using ll = int64_t;

const int N = (int)5e5 + 100;
const int L = 24;

int up[N][L + 1], tin[N], tout[N];
vector<int> g[N];
int timer = 0;

void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= L; i++)
        up[v][i] = up[up[v][i - 1]][i - 1];

    for (int u : g[v]) {
        if (u == p) 
            continue;
        dfs(u, v);
    }
    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;

    for (int i = L; i >= 0; i--) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }

    return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int root = 0;
    int n, q; cin >> n >> q;

    for (int i = 1; i < n; i++) {
        int par; cin >> par;
        g[par].pb(i);
        g[i].pb(par);
    }

    dfs(root, root);
    while(q--) {
        int u, v; cin >> u >> v;
        int w = lca(u, v);
    }

    return 0;
}