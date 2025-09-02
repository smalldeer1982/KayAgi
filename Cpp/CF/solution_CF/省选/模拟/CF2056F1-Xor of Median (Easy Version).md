# Xor of Median (Easy Version)

## 题目描述

# Xor of Median (Easy Version)
 
 
这是问题的简单版本。版本之间的区别在于，在此版本中，对 $t$、$k$ 和 $m$ 的约束较低。只有在你解决了这个问题的所有版本之后，才能进行hack。
 
如果满足以下条件，则称长度为 $n$ 的整数序列 $a$ 为好序列：
 
- 令 $\text{cnt}_x$ 为序列 $a$ 中 $x$ 的出现次数。对于所有满足 $0 \le i < j < m$ 的对 $(i, j)$，以下情况中至少有一种必须为真：$\text{cnt}_i = 0$，$\text{cnt}_j = 0$，或 $\text{cnt}_i \le \text{cnt}_j$。换句话说，如果 $i$ 和 $j$ 都出现在序列 $a$ 中，则 $a$ 中 $i$ 的出现次数小于或等于 $a$ 中 $j$ 的出现次数。
 
给定整数 $n$ 和 $m$。计算所有长度为 $n$、满足 $0 \le a_i < m$ 的好序列 $a$ 的中位数的按位异或值。
 
请注意，$n$ 的值可能非常大，因此给出的是其二进制表示形式。
 
$ ^{\text{*}} $ 序列 $a$ 的中位数定义为序列中第 $\left\lfloor\frac{n + 1}{2}\right\rfloor$ 小的值。

## 说明/提示

在第一个示例中，$n = 10_2 = 2$ 且 $m = 3$。所有元素小于 $m$ 的可能序列为：$[0, 0]$，$[0, 1]$，$[0, 2]$，$[1, 0]$，$[1, 1]$，$[1, 2]$，$[2, 0]$，$[2, 1]$，$[2, 2]$。它们都是好序列，所以答案是：$0 \oplus 0 \oplus 0 \oplus 0 \oplus 1 \oplus 1 \oplus 0 \oplus 1 \oplus 2 = 3$。
 
在第二个示例中，$n = 11_2 = 3$ 且 $m = 3$。一些好序列为 $[2, 2, 2]$，$[1, 0, 1]$ 和 $[2, 0, 1]$。然而，序列 $[2, 0, 0]$ 不是好序列，因为 $\text{cnt}_0 = 2$，$\text{cnt}_2 = 1$。因此，如果我们设置 $i = 0$ 和 $j = 2$，则 $i < j$ 成立，但 $\text{cnt}_i \le \text{cnt}_j$ 不成立。

## 样例 #1

### 输入

```
6
2 3
10
2 3
11
5 1
11101
7 9
1101011
17 34
11001010001010010
1 500
1```

### 输出

```
3
2
0
8
32
0```

# 题解

## 作者：Rain_chr (赞：8)

很厉害的题，评个紫不过分吧。虽然是我自己推出来的，但是花了一个小时，场上基本不可能过。

首先我们注意到题目要求的是中位数的异或和，感性理解一下可以发现很多方案中的中位数相互抵消了。假设我们有一种方案选取了 $k$ 种数字，从小到大分别选取了 $a_1,a_2,\dots,a_k$ 个，那么对应序列的方案应为：

$$\frac {n!} {\prod_{i=1}^k a_i!}$$

这是可重集排列的方案数，因为我们是异或，所以上述式子只有为奇数时才有贡献。定义函数 $f(n)$ 表示 $n!$ 中 $2$ 的次幂，也就是 $2^{f(n)}||n!$，上述式子在 $\bmod 2$ 意义下等价 $f(n)=\sum_{i=1}^k f(a_i)$，形式化表述：

$$\frac {n!} {\prod_{i=1}^k a_i!} \equiv [f(n)=\sum_{i=1}^k f(a_i)] \pmod 2$$

所以其实对于 $n$，我们只用统计 $f(n)=\sum_{i=1}^k f(a_i)$ 所有方案的中位数异或和。

那么什么样的 $a$ 序列满足上述条件呢？打个表发现，$a$ 序列是 $n$ 二进制位的一个拆分。形式化的说，我们应该统计满足如下性质的 $a$ 序列：

对于任意的 $i,j$，都满足 $a_i \operatorname{and} a_j=0$

并且 $\sum_{j=1}^k a_j=n$

这个证明不难，结论也很直观。

我们惊奇的发现，设 $n$ 的最高位是 $2^K$，因为 $2^K>\frac n 2$，所以在这个序列中中位数就是最大值。

那么这个就简单了，我们枚举 $k$，设 $n$ 的二进制位中有 $cnt$ 个 $1$，那么方案数就是 $cnt \brace k$，也就是将 $cnt$ 个 $1$ 分配到 $k$ 个集合中，且集合不为空的方案数。

同时，我们再枚举最大值 $x$，选取数字的方案显然就是 ${{cnt} \brace {k}} {x \choose k-1}$，当这个值是奇数的时候，我们就可以异或上 $x$，总复杂度是 $O(nk)$。

---

## 作者：PigNotFound (赞：1)

一道好题。

首先，注意到题目所求的是所有中位数的异或。而中位数的范围又在 $[0,m)$ 之内。只有当只有奇数个序列中位数为 $i$，答案才会异或上 $i$。 所以考虑枚举每一个中位数，来计算答案。

根据排列组合的公式，共有 $\frac{n!}{\prod_{i=0}^{m - 1}cnt_i!}$ 种序列对应 $cnt$，若 $\frac{n!}{\prod_{i=0}^{m - 1}cnt_i!}$ 为偶数，则这个序列的中位数不会算入答案。因为一个数被异或了偶数次。所以若 $cnt$ 要被算入答案中，则分式上下的 2 的次幂必须一样。

定义 $f(i)$ 为 $i!$ 中 2 的次幂。则能被算入答案的 $cnt$ 一定得满足 $f(n) = \sum_{i=0}^{m - 1}cnt_i$。易得只有当 $\sum_{i=0}^{m - 1}cnt_i=n$ 且 $cnt$ 中任意两个数按位与的值为 $0$。换句话说，$cnt$ 是 $n$ 的一个二进制拆分。举个例子，$n=7$ 时，对应的 $cnt$ 可以为 $1,6$，也可以为 $1,2,4$ 等等。

因为题目中要求序列的 $cnt$ 除 $0$ 以外的元素必须得递增，所以 $cnt$ 中最大的元素一定是 $cnt$ 中非 0 的最靠后的元素。又因为 $cnt$ 是 $n$ 的一个二进制拆分，所以 $\max\{cnt\}$ 一定包含二进制中 $n$ 的最高位。所以 $\max\{cnt\}$ 一定大于 $n / 2$。所以每个满足要求的序列的中位数只能是序列最大的元素。

所以，我们先枚举 $k$ 为序列中的元素个数。设 $cnt$ 为 $n$ 二进制中一的个数。共有 $S(cnt, k)$ 中方案。也就是将 $cnt$ 个进制位分配给 $k$ 个位置，位置无序的方案数。然后我们还需要枚举这些数放在哪个位置。设最大的数为 $i$，则方案数为 $C^{k - 1}_{x}$。总的方案数为 $S(cnt, k)C^{k - 1}_{x}$。只要其为奇数，就在答案中异或上 $x$。

复杂度 $O(nk)$。

---

## 作者：under_the_time (赞：0)

## 题意

> 定义一个好序列为：所有数都在 $0,1,\cdots,m-1$ 的范围内，且如果值 $i,j$ 均出现在序列中（$i<j$），那么 $i$ 的出现次数小于等于 $j$ 的出现次数。
>
> 给定 $n,m$，求所有长度为 $n$ 的好序列的中位数（第 $\lfloor(n+1)/2\rfloor$ 小的数）的异或和。
>
> $n\le 2^{200}$，$1\le m\le 500$。

## 解法

首先观察到一个序列好不好与顺序无关。考虑一个大小为 $n$ 的集合 $S$，由 $k$ 钟不同的数组成，分别出现了 $n_1,n_2,\cdots,n_k$ 次，那么这个集合可以构成 $\displaystyle\binom n{n_1,n_2,\cdots,n_k}=\cfrac{n!}{\prod_{i=1}^k n_k!}$ 种序列；若排列方案是偶数种，那么 $S$ 就没有贡献了。

怎么算 $\binom n{n_1,n_2,\cdots,n_k}$ 的奇偶性呢？考虑这个式子等于 $\binom{n}{n_1}\binom{n-n_1}{n_2}\cdots$，由卢卡斯定理我们知道对于组合数 $\binom{i}{j}\equiv 1\pmod 2$ 当且仅当 $j$ 在二进制下是 $i$ 的二进制的一个子集。归纳可得，$\binom n{n_1,n_2,\cdots,n_k}$ 是奇数当且仅当 $n_1,n_2,\cdots,n_k$ 将 $n$ 的二进制位上的 $1$ 进行了不重不漏的划分。

既然要划分，那么总有一个 $n_i$ 分走了 $n$ 二进制下最高位的 $1$，因此 $n_i$ 一定大于其余所有 $n_j$ 的和，那么中位数一定取到 $n_i$​；而由题意得出现次数最多的数一定是值最大的数，所以中位数就是序列中的最大值。

接下来就好办力，枚举序列的最大值 $mx$（即中位数）和序列中元素种类数 $j$，设 $n'$ 为 $n$ 二进制中 $1$ 的个数，那么对 $n$ 划分的方案数就是第二类斯特林数 $\left\{\begin{matrix}n'\\j\end{matrix}\right\}$；剩下 $j-1$ 种元素有 $\displaystyle\binom{mx}{j-1}$ 种方案，于是 $mx$ 作为好序列的中位数的方案数就是 $\displaystyle\sum_{j=1}^{n'}\left\{\begin{matrix}n'\\j\end{matrix}\right\}\binom{mx-1}{j-1}$，算出来看看奇偶性，若是奇数那么答案异或上 $mx$ 即可。范围不大可以直接递推求解第二类斯特林数，时间复杂度 $O(n'm)$，可以通过 Easy Version。

```cpp
#include <bits/stdc++.h>
bool MemoryST; using namespace std;
#define ll long long
#define mk make_pair
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define lowbit(x) ((x) & (-(x)))
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
#define BCNT __builtin_popcount
#define cost_time (1e3 * clock() / CLOCKS_PER_SEC) << "ms"
#define cost_space (abs(&MemoryST - &MemoryED) / 1024.0 / 1024.0) << "MB"
const int inf = 0x3f3f3f3f; 
const ll linf = 1e18; 
mt19937 rnd(random_device{}());
template<typename T> void chkmax(T& x, T y) { x = max(x, y); }
template<typename T> void chkmin(T& x, T y) { x = min(x, y); }
template<typename T> T abs(T x) { return (x < 0) ? -x : x; }
const int maxn = 205, maxm = 505;
int T, k, m, f[maxn][maxn]; char s[maxn];
bool MemoryED; int main() {
    f[0][0] = 1;
    for (int i = 1; i <= 200; i ++)
        for (int j = 0; j <= i; j ++)
            f[i][j] = (f[i - 1][j] & (j & 1)) ^ (j > 0 ? f[i - 1][j - 1] : 0);
    for (scanf("%d", &T); T --; ) {
        scanf("%d %d %s", &k, &m, s + 1); int n = 0;
        for (int i = 1; i <= k; i ++)
            if (s[i] == '1') n ++;
        int ans = 0;
        for (int mx = 1; mx < m; mx ++) {
            int cnt = 0;
            for (int j = 1; j <= n; j ++)
                cnt ^= (f[n][j] & ((mx & (j - 1)) == j - 1 ? 1 : 0));
            if (cnt & 1) ans ^= mx;
        } printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：DengDuck (赞：0)

前置知识：组合数和第二类斯特林数模 $2$ 的计算方式。

注意到最大的数字出现次数应该最多，所以 $\text{Cnt}_{\max}\geq \text{highbit}(n)$，$\text{highbit}(n)$ 表示 $n$ 二进制最高位。

由于 $2\times\text{highbit}(n)>n$，于是中位数必然是最大值。

推广一下我们发现答案应该和 $n$ 没关系，我们关心 $b=\text{popcount}(n)$ 就行了。

考虑枚举出现的最大数字 $x$，出现数字的总数 $k$。

我们把二进制分配到 $k$ 个集合里再排序就满足条件了，所以中位数是 $x$ 的方案数为：
$$
f(x)=\sum_{k=1}^m {b\brace k}\binom{x}{k-1}
$$

注意到这题是把东西都异或起来，所以我们只关心上面那玩意的奇偶性，相当于模 $2$，然后组合和第二类斯特林数都可以简单计算。

时间复杂度 $\mathcal O(m^2)$，于是可以通过 Easy Version。

---

