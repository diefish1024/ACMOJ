#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1e3 + 5;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

template <typename T>
inline void read(T &x) {
    x = 0;
    int k = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') {
            k = -1;
        }
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
    x *= k;
}

int n, m;
int val[N][N];

vvi adj;
vi in_degree;
inline int p2id(int x, int y) { return m * (x - 1) + y - 1;}
inline void add(int u, int v) { // add u -> v
    adj[u].push_back(v);
    in_degree[v]++;
}

vi dis;
int ans;
void topo() {
    vector<int> q;
    for (int i = 0; i < n * m; ++i) {
        if (in_degree[i] == 0) {
            q.push_back(i);
            dis[i] = 0;
        }
    }

    while (!q.empty()) {
        int u = q.back();
        q.pop_back();
        for (int v : adj[u]) {
            in_degree[v]--;
            dis[v] = max(dis[v], dis[u] + 1);
            ans = max(ans, dis[v]);
            if (in_degree[v] == 0) {
                q.push_back(v);
            }
        }
    }
}

// DEBUG : print the graph
void debug() {
    for (int i = 0; i < n * m; ++i) {
        cout << "Node " << i << ": ";
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

void init_vector(int tot) {
    adj.resize(tot);
    in_degree.resize(tot, 0);
    dis.resize(tot, 0);
}

int main() {
    cin >> n >> m;
    init_vector(n * m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            read(val[i][j]);
            static const int dx[] = {-1, 0};
            static const int dy[] = {0, -1};
            for (int k = 0; k < 2; ++k) {
                int x = i + dx[k], y = j + dy[k];
                if (!x || !y) continue;

                if (val[i][j] > val[x][y]) {
                    add(p2id(x, y), p2id(i, j));
                }
                if (val[i][j] < val[x][y]) {
                    add(p2id(i, j), p2id(x, y));
                }
            }
        }
    }
    // debug();
    topo();
    cout << ans + 1 << endl;
    return 0;
}