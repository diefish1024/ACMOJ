#include <iostream>
#include <vector>
#include <string>
// #include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<unsigned int> vui;

inline void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    fastIO();
    int n, flg;
    cin >> n >> flg;

    if (flg == 1) {
        // Case flg == 1: Boyer-Moore algorithm without storing the array
        unsigned int candidate;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            unsigned int val;
            cin >> val;
            if (cnt == 0) {
                candidate = val;
                cnt = 1;
            } else if (val == candidate) {
                cnt++;
            } else {
                cnt--;
            }
        }
        cout << candidate << endl;

    } else if (flg == 0 || flg == 2) {
        // Cases flg == 0 and flg == 2: Need to store the array
        vui a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        if (flg == 0) {
            vui ans;
            map<unsigned int, int> cnt;
            for (int i = 0; i < n; ++i) {
                cnt[a[i]]++;
            }
            int max_cnt = 0;
            for (auto& p : cnt) {
                if (p.second > max_cnt) {
                    max_cnt = p.second;
                    ans.clear();
                    ans.push_back(p.first);
                } else if (p.second == max_cnt) {
                    ans.push_back(p.first);
                }
            }
            for (int i = 0; i < ans.size(); ++i) {
                cout << ans[i] << " ";
            }
        } else if (flg == 2) {
            unsigned int mx = a[0];
            for (int i = 1; i < n; ++i) {
                mx = max(mx, a[i]);
            }
            int len = log2(mx) + 1;
            vi cnt(len, 0);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < len; ++j) {
                    cnt[j] += ((a[i] >> j) & 1);
                }
            }
            vi ans(len, 0);
            int tot_unsure = 0;
            vi unsure(len, 0);
            for (int i = 0; i < len; ++i) {
                if ((cnt[i] << 1) == n) {
                    ans[i] = -1;
                    unsure[tot_unsure++] = i;
                } else {
                    ans[i] = (cnt[i] > n / 2) ? 1 : 0;
                }
            }
            vui res(1 << tot_unsure, 0);
            for (int i = 0; i < len; ++i) {
                if (ans[i] == 1)
                    res[0] += (1u << i);
            }
            for (int i = 1; i < (1 << tot_unsure); ++i) {
                res[i] = res[0];
                for (int j = 0; j < tot_unsure; ++j) {
                    if ((i >> j) & 1) {
                        res[i] += (1u << unsure[j]);
                    }
                }
            }
            for (int i = 0; i < (1 << tot_unsure); ++i) {
                cout << res[i] << " ";
            }
        }
    }

    return 0;
}
