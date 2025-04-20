#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

int calculate_g(const vector<int>& a_subarray) {
    set<int> s;
    for (int x : a_subarray) {
        s.insert(x);
    }
    int g_val = 1;
    while (s.count(g_val)) {
        g_val++;
    }
    return g_val;
}

int solve_brute_force(int n, const vector<int>& a, const vector<int>& f) {
    for (int i = 1; i <= n; ++i) {
        for (int l = 0; l < n; ++l) {
            for (int r = l; r < n; ++r) {
                if (r - l + 1 == i) {\
                    vector<int> subarray;
                    for (int j = l; j <= r; ++j) {
                        subarray.push_back(a[j]);
                    }
                    int g_lr = calculate_g(subarray);
                    if (f[i-1] < g_lr) {
                        return i;
                    }
                }
            }
        }
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("brute_output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<int> a(n), f(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> f[i];

    int result = solve_brute_force(n, a, f);
    cout << result << endl;

    return 0;
}
