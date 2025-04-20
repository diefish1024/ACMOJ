#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long ll;
using namespace std;
const int N=1e5 + 5;

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
int a[N], f[N];
int v2id[N];
pair<int, int> pos[N];
int main() {
    freopen("input.txt", "r", stdin);
    freopen("main_output.txt", "w", stdout);
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        v2id[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        read(f[i]);
    }

    pos[1] = {v2id[1], v2id[1]};
    for (int i = 2; i <= n; ++i) {
        int id = v2id[i];
        pos[i] = {id, id};
        if (pos[i - 1].first < id) {
            pos[i].first = pos[i - 1].first;
        }
        if (pos[i - 1].second > id) {
            pos[i].second = pos[i - 1].second;
        }
    }

    for (int i = 1; i <= n; ++i) if (f[i] <= i) {
        int len = pos[f[i]].second - pos[f[i]].first + 1;
        if (i >= len) {
            cout << i << endl;
            return 0;
        }
    }
    puts("0");
    return 0;
}