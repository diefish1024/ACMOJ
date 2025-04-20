#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

int main() {
    freopen("input.txt", "w", stdout); // 输出到 input.txt

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib_n(1, 10); // n 的范围，可以根据需要调整，例如 1 到 10

    int n = distrib_n(gen);
    cout << n << endl;

    vector<int> a(n);
    iota(a.begin(), a.end(), 1); // 初始化为 1, 2, ..., n
    shuffle(a.begin(), a.end(), gen); // 打乱顺序生成排列
    for (int i = 0; i < n; ++i) {
        cout << a[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    uniform_int_distribution<> distrib_f(1, n); // f_i 的范围，可以根据需要调整，例如 1 到 n
    for (int i = 0; i < n; ++i) {
        cout << distrib_f(gen) << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    fclose(stdout);
    return 0;
}
