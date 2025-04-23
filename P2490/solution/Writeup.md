# P2490 RollingHash

## 思路

题目要求实现一个支持在线追加字符和查询子串哈希值的 `RollingHash` 类，并使用双模数哈希。

哈希函数定义为：\
$$H(S[1..n]) = (s_1 B^{n-1} + s_2 B^{n-2} + \dots + s_n B^0) \pmod P$$
或者使用求和符号：\
$$H(S[1..n]) = \left(\sum_{i=1}^n s_i B^{n-i}\right) \pmod P$$

为了高效计算子串哈希和支持在线追加，我们维护一个前缀哈希数组 `HashSum`\
$$\text{HashSum}[i] = (s_1 B^{i-1} + s_2 B^{i-2} + \dots + s_i B^0) \pmod P$$

这样，子串 `S[l..r]` 的哈希值可以表示为：
$$H(S[l..r]) = ( \text{HashSum}[r] - \text{HashSum}[l-1] ) \cdot B^{r} \pmod P$$

## 细节

1.  **双模数**: 选择两个较大的质数作为模数 `p1` 和 `p2` 以降低冲突概率。
2.  **预处理**:
    *   预计算 `B` 的幂 $\text{Bpow}[i] = B^i \pmod P$
    *   预计算 `B` 的模逆元的幂 $\text{Binvs}[i] = (B^{-1})^i \pmod P$
3.  **模逆元**: 由于模数 `p1` 和 `p2` 是质数，可以使用费马小定理计算 `B` 的模逆元：$B^{-1} \equiv B^{P-2} \pmod P$。这需要一个快速幂。
4.  **查询哈希 `getHash(l, r)`**: 出现了减法，需要注意处理负数取模。
