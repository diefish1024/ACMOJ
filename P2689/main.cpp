#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi adj;
vvi parent;
vi depth;
int log_n;

void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int j = log_n; j >= 0; --j) {
        if (depth[u] - (1 << j) >= depth[v]) {
            u = parent[u][j];
        }
    }
    if (u == v) return u;
    for (int j = log_n; j >= 0; --j) {
        if (parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
        }
    }
    return parent[u][0];
}

int dist(int u, int v) {
    int ancestor = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[ancestor];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    adj.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    log_n = ceil(log2(n));
    parent.resize(n + 1, vi(log_n + 1, 0));
    depth.resize(n + 1, 0);

    dfs(1, 1, 0);

    for (int j = 1; j <= log_n; ++j) {
        for (int i = 1; i <= n; ++i) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }

    for (int i = 0; i < q; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        int d_uv = dist(u, v);
        int d_vw = dist(v, w);
        int d_uw = dist(u, w);

        if ((d_uv + d_vw == d_uw) || (d_uw + d_vw == d_uv) || (d_uv + d_uw == d_vw)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
