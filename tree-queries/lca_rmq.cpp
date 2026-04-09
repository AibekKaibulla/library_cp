#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define fst first
#define scd second

using ll = int64_t;
const int N = (int)2e5 + 123;
const int K = 24;
const int INF = (int)1e9;
vector<int> g[N];
vector<pair<int, int>> e; // (h, v)

int d[N], first[N], lg[N * 2];
pair<int, int> st[K][N * 2];
void dfs(int v, int p) {
    first[v] = min(first[v], (int)e.size());
    e.pb({d[v], v});

    for (int u : g[v]) {
        if (u == p)
            continue;
        d[u] = d[v] + 1;
        dfs(u, v);
        e.pb({d[v], v});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;

        g[p].pb(i);
        g[i].pb(p);
    }
    e.reserve(2 * n);
    for (int i = 0; i < n; i++)
        first[i] = INF;

    dfs(0, -1);
    int m = (int)e.size();

    for (int i = 0; i < K; i++) {
        for (int j = 0; j <= m; j++) {
            st[i][j] = {INF, INF};
        }
    }
    lg[1] = 0;

    for (int i = 0; i < m; i++) {
        st[0][i] = e[i];
        if (i > 1)
            lg[i] = lg[i/2] + 1;
    }


    lg[m] = lg[m/2] + 1;
    for (int i = 1; i < K; i++) {
        for (int j = 0; j + (1 << i) <= m; j++) {
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
    while(q--) {
        int u, v; cin >> u >> v;
        u--, v--;
        int L = min(first[u], first[v]), R = max(first[u], first[v]);
        int i = lg[R - L + 1];
        auto x = min(st[i][L], st[i][R - (1 << i) + 1]);
    }

    return 0;
}