# P2689 Yet Another Triple Problem

## 思路

要判断三个节点 $u, v, w$ 是否在同一简单路径上，可以检查它们之间的路径关系和距离关系。

如果三个节点 $u, v, w$ 在同一简单路径上，那么以下三个条件中至少有一个成立：\
    1. $\mathrm{dist}(u, v) + \mathrm{dist}(v, w) = \mathrm{dist}(u, w)$  (表示 $v$ 在 $u$ 和 $w$ 之间)\
    2. $\mathrm{dist}(u, w) + \mathrm{dist}(w, v) = \mathrm{dist}(u, v)$  (表示 $w$ 在 $u$ 和 $v$ 之间)\
    3. $\mathrm{dist}(v, u) + \mathrm{dist}(u, w) = \mathrm{dist}(v, w)$  (表示 $u$ 在 $v$ 和 $w$ 之间)

其中 $\mathrm{dist}(x, y)$ 表示节点 $x$ 和 $y$ 之间的距离。节点之间的距离等于它们路径上的边数，可以使用LCA 来计算：

$$\mathrm{dist}(u, v) = \mathrm{depth}(u) + \mathrm{depth}(v) - 2 \times \mathrm{depth}(LCA(u, v))$$

这里 $\mathrm{depth}(x)$ 表示节点 $x$ 的深度（根节点深度为 0）。

可以使用**倍增**求 LCA ，写法相对比较简洁。