#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;
const int N = 50 + 5;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;

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


int n;
int c[N], d[N][N];

ll calc_eff(const vi& partition) {
    ll eff = 0;
    for (int i : partition) {
        eff += c[i];
    }
    for (int i = 0; i < partition.size(); i++) {
        for (int j = i + 1; j < partition.size(); j++) {
            eff += d[partition[i]][partition[j]];
        }
    }
    return eff;
}

void generate_partition(int left, int sum, vi& cur, vvi& par) {
    if (sum == n) {
        par.push_back(cur);
        return;
    }
    for (int i = left; i <= n - sum; i++) {
        cur.push_back(i);
        generate_partition(i, sum + i, cur, par);
        cur.pop_back();
    }

}

int main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(c[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            read(d[i][j]);
        }
    }
    vvi partitions;
    vi cur = {};
    generate_partition(1, 0, cur, partitions);
    ll max_eff = LLONG_MIN;
    for (const auto& partition : partitions) {
        ll eff = calc_eff(partition);
        max_eff = max(max_eff, eff);
    }
    cout << max_eff << endl;

    return 0;
}