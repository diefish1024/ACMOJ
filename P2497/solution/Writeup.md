# P2497 Valencia 好强

## 思路

题目需要我们将 $m$ 个大将分成若干组，使得 $Eff$ 最大。

若 $a$ 为 $m$ 的一个无序拆分，那么 $Eff$ 的计算公式为
```math
Eff = \sum_{i=1}^{n} c_{a_{i}} + \sum_{1 \leq i \leq j \leq n} d_{a_{i}, a_{j}}
```

这个问题实际上是要求我们枚举 m 的所有可能的整数划分，对每种划分计算最大效率值。

直接枚举，复杂度 $O(m^{2}p(m))$ ，而通过以下代码可以计算 $p(m)$ 的值：

```cpp
#include <iostream>
#define MAXLENTH 50
using namespace std;

int main() {
	const int len = MAXLENTH;
	long num[len + 1] = { 1 };

	for (int i = 1; i <= len; ++i)
		for (int j = i; j <= len; ++j)
			num[j] += num[j - i];

	for (int i = 0; i <= len; i++)
		cout << i << " " << num[i] << endl;
	return 0;
}
```

在 $m=50$ 时，$p(m)=204226$，所以复杂度为 $O(m^{2}p(m))$ 是可以接受的。

## 细节

递归生成所有可能的划分比较方便，由于空间比较充裕，所以代码中为了清晰，先存了所有的划分再逐个计算，其实可以在递归的过程中计算，不需要存下来。