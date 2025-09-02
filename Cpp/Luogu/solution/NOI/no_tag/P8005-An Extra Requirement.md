# An Extra Requirement

## 题目背景

由于 Codeforces [[1]](https://codeforces.com/contest/1610/problem/I) [[2]](https://codeforces.com/contest/1591/problem/F) 能从 Atcoder [[1]](https://atcoder.jp/contests/agc017/tasks/agc017_d) [[2]](https://atcoder.jp/contests/arc115/tasks/arc115_e) 搬题，于是出（搬）题人也从 Atcoder [[3]](https://atcoder.jp/contests/agc054/tasks/agc054_e) 搬了一道。

## 题目描述

对于一个长度为 $N$ 的排列 $P$，你可以进行若干次如下操作：选三个位置 $x,y,z(x<y<z)$，若 $P_y<\min\{P_x,P_z\}$ 或 $P_y>\max\{P_x,P_z\}$，那么可以删除 $P_y$。

统计存在一种删除方式，使得最后只剩下不超过两个数且 $P_1=A$ 的排列 $P$ 的个数。由于答案可能很大，你只需要输出个数模 $998244353$ 的结果即可。

## 说明/提示

**本题采用捆绑测试**

| 子任务编号 | 分值 | 特殊限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | $T,N\le 8$ |
| $1$ | $15$ | $T\le 5$，$N\le 100$ |
| $2$ | $10$ | $T\le 5$，$N\le 1000$ |
| $3$ | $15$ | $A=1$ |
| $4$ | $15$ | $T\le 5$，$N\le 5\times 10^4$ |
| $5$ | $15$ | $T\le 200$ |
| $6$ | $20$ | 无特殊限制 |

对于所有数据，保证：$1\le T\le 10^5$，$1\le A\le N\le 10^5$。

## 样例 #1

### 输入

```
7
3 1
3 2
3 3
4 1
4 2
4 3
4 4```

### 输出

```
1
2
1
3
5
5
3```

## 样例 #2

### 输入

```
5
5 2
6 3
7 4
8 5
9 6```

### 输出

```
20
104
648
4662
38040```

# 题解

## 作者：Elma_ (赞：2)

考虑什么样的排列是合法的。不妨设 $p_1 < p_n$：

> 引理 ：设 $l$ 为最小的使得 $p_1 \sim p_t$ 为 $1 \sim t$ 的排列的 $t$，$r$ 为最大的使得 $p_t \sim p_n$ 为 $t \sim n$ 的排列的 $t$，那么排列 $p$ 合法的充分必要条件是 $r - l \leq 1$。

我们称 $p_{1,\cdots,l}$ 为 “前缀”、$p_{r,\cdots,n}$ 为 “后缀”，那么上面那个条件其实就是： $p$ 的前缀和后缀能够覆盖整个排列。

证明：必要性是显然的，假设 $l + 1< r$，显然 $p_{l+1} \sim p_{r-1}$ 是一个 $l+1 \sim r-1$ 的排列，对于这个排列中的数 $p_i$，因为 $p_i > l = \max\{p_1,p_2, \cdots,p_l\}$ 且 $p_i < r = \min\{p_r,p_{r+1},\cdots,p_n\}$，因此 $p_i$ 只可能被这个排列内部的数删除。然而无论我们如何删除，这个排列中都至少会剩下一个数，那么剩下的这个数就永远无法被删掉。

对于 $l + 1\geq r$ 的排列 $p$，我们尝试给出一种构造的方法使得整个序列能够删到不多于 $2$ 个数。不妨先考虑前缀：

对于前缀，我们找到最大的 $i$ 使得 $p_i < p_1$，对于 $1 < j < i$  的 $p_j$，我们分类讨论：

- 若 $p_j > p_1$，那么由 $1 < j < i$ ，$p_j > p_1 = \max\{p_1,p_i\}$ 可知 $p_j$ 可被 $p_1,p_i$ 删掉。
- 若 $p_j < p_1$，那么由 $1 < j < n$，$p_j < p_1 = \min\{p_1,p_n\}$ 可知 $p_j$ 可被 $p_1,p_n$ 删掉。 

因此， $1 < j < i$ 的 $p_j$ 都可以被删掉。此时，我们再找到使得 $p_j$ 最大的 $j$，再找到最大的 $i'$ 使得 $p_{i'} < p_j$，重复这个过程直到无法找到新的数，这时 $p_1 \sim p_i$ 一定是一个 $1 \sim i$ 的排列，并且 $p_2 \sim p_i$ 都可以被删除。

证明：对于一个 $p_j$，我们找到最大的 $i$ 使得 $p_i < p_j$，那么 $p_1 \sim p_i$ 就包含了 $1 \sim p_j$ 的所有数。又因为 $p_j$ 是满足条件的最大的数，所以如果无法选出新的数，那么 $p_1 \sim p_i$ 就一定包含了 $1 \sim i$ 的所有数，即 $p_1 \sim p_i$ 是 $1 \sim i$ 的一个排列。而对于前缀，它没有更小的前缀是一个排列，因此 $p_2 \sim p_l$ 中的所有数都是能够被删掉的，后缀同理。又因为前后缀覆盖了整个排列，那么这个排列就是合法的。

现在考虑如何计数。设 $f_i$ 表示满足不存在更小的 $j$ 使得 $p_1 \sim p_j$ 为排列的 $1 \sim i$ 的排列个数。考虑容斥，枚举 $j$ 的位置，令 $p_1 \sim p_j$ 是不存在更小的 $k$ 使得 $p_1 \sim p_k$ 是 $1 \sim k$ 的排列的 $1 \sim j$ 的排列，剩下的位置随便放，可以得到式子：
$$
f_i = i! - \sum_{j=1}^{i-1} f_j (i -j)!
$$
 朴素地计算是 $O(n^2)$ 的。移项，可以得到：
$$
\sum_{j=1}^if_j(i-j)! = i!
$$
考虑 $f_i$ 的生成函数，令 $F(x) = \sum_{i = 0}^n f_ix^i$，$G(x) = \sum_{i = 1} ^n i! x^i$，则有：
$$
F(x)(G(x) + 1) = G(x)
$$
那么即有：
$$
F(x) = \dfrac{G(x)}{G(x) + 1}
$$
多项式求逆即可 $O(n \log n)$ 计算。

现在考虑如何计算答案，我们还是容斥，计算出不合法的排列个数然后减掉。由于 $p_1$ 是固定的，我们枚举最大的 $j$ 使得 $p_j \sim p_n$ 是 $j \sim n$ 的排列。然后对于中间的那一段排列，再枚举最大的 $k$ 使得 $P_k \sim p_{j−1}$ 是 $k \sim j − 1$ 的排列，这一段表示不能删掉它们。最后 $1 \sim k − 1$ 任意排列。当然，这要求 $k \geq p_1$。

对于固定的 $n$，设 $h_i$ 为 $k = i$ 时的方案数，不难写出：
$$
h_i = (k-2)!\sum_{j = k}^n f_{j - k+1} f_{n - j + 1}
$$
后面是一个卷积的形式，令 $g_n = \sum_{i = 0}^n f_{i} f_{n - i}$，那么：
$$
h_i = (k - 2)!g_{n - k + 1}
$$
因此对于固定 $n$ 的情况，NTT 计算 $F(x)^2$ 后就可以 $O(n)$ 计算 $h_i$ ，答案即为 $n! - \sum_{i = p_1 + 1}^n h_i$。但对于不同的 $n$，我们都必须重新计算答案，因此这个做法的时间复杂度为 $O(T n \log n)$，能获得 $80$ 分。

现在我们换一种思考的角度：考虑固定 $p_1$，计算在这种情况下的答案。设 $h_n$ 为长度为 $n$ 的排列的答案，则：
$$
h_n = \sum_{k = p_1 + 1}^{n} (k - 2)!g_{n-k+1} = \sum_{i = 0}^{n-p_1} g_{i}(n-i-1)!
$$
这也是一个卷积的形式，可以用 NTT  $O(n \log n)$ 计算。我们发现，当 $p_1$ 变为 $p_1 + 1$ 时，$h_n$ 仅仅会减少一项 $(p_1-1)!g_{n-p_1}$，也就是说，如果我们知道了固定 $p_1$ 时 $h_n$ 的值，我们可以 $O(1)$ 得到 $p_1+1$ 时的 $h_n$。

对于 $p_1 > p_n$ 的情况，我们同样可以按照上述方式计算。于是可以考虑对询问的 $A$ 分块，我们对 $A$ 排序，算出 $p_1 = B,2B \cdots$ 时的答案，每次询问 $O(B)$ 求出答案。假设 $T,n$ 同阶，那么时间复杂度为 $O(\frac{n}{B} n \log n + nB)$，当 $B = \sqrt{n \log n}$ 时取最优复杂度 $O(n \sqrt{n \log n})$。

然而我的 NTT 常数实在太大了，当 $B$ 取 $1300$ 的时后大概要跑 $460$ 次左右的 NTT... 所以这份代码只能获得 $80$ 分的好成绩。如果之后我卡过了会回来更新的qwq（或者来个神仙教教常数优化/kel）。

------------

**Upd**：这份代码里的一些点值是可以预处理的，这样就不用每次都 NTT 算一遍了，但大概还是需要 $300+$ 次的 NTT...所以还是没过/kk

```cpp
int Q, N, M, K, Lim, L, f[MN], g[MN], A[MN], B[MN], G[MN], F[MN], rev[MN], Mx, Frac[MN];

inline int qPow(int a, int b = Mod - 2) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % Mod;
        a = a * a % Mod, b >>= 1;
    }
    return res;
}
inline void NTT(int *a, int Ty) {
    for (int i = 0; i < Lim; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int i = 1; i < Lim; i <<= 1) {
        int rt = qPow(3, (Mod - 1) / (i << 1));
        if (Ty == -1) rt = qPow(rt);
        for (int j = 0; j < Lim; j += (i << 1)) {
            int w = 1;
            for (int k = 0; k < i; k++, w = w * rt % Mod) {
                int p = a[j + k], q = w * a[j + k + i] % Mod;
                a[j + k] = (p + q) % Mod, a[j + k + i] = ((p - q) % Mod + Mod) % Mod;
            }                   
        } 
    }
    if (Ty == -1) {  
        int Inv = qPow(Lim);
        for (int i = 0; i < Lim; i++) a[i] = (a[i] * Inv % Mod + Mod) % Mod;
    }
}
int Inv[MN];
inline void GetInv(int *f, int *g, int Len) {
    if (Len == 1) return g[0] = qPow(f[0]), void();
    GetInv(f, g, (Len + 1) >> 1);
    for (Lim = 1, L = 0; Lim < (Len << 1); Lim <<= 1) L++;
    for (int i = 1; i < Lim; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    for (int i = 0; i < Len; i++) Inv[i] = f[i];
    for (int i = Len; i < Lim; i++) Inv[i] = 0;
    NTT(Inv, 1), NTT(g, 1);
    for (int i = 0; i < Lim; i++) g[i] = ((2 - g[i] * Inv[i] % Mod) + Mod) % Mod * g[i] % Mod;
    NTT(g, -1);
    for (int i = Len; i < Lim; i++) g[i] = 0;
}

#define PI3 pair <pii, int>
#define mp3(x, y, z) mp(mp(x, y), z)
PI3 q[MN]; int Ans[MN];

inline void Work() {
    Mx = 1e5;
    Frac[0] = 1;
    for (int i = 1; i <= 2 * Mx; i++) Frac[i] = Frac[i - 1] * i % Mod;
    f[1] = 1, f[0] = 1;
    for (int i = 2; i <= Mx; i++) f[i] = f[i - 1] * i % Mod;
    GetInv(f, g, Mx);
    f[0]--;
    NTT(f, 1), NTT(g, 1);
    for (int i = 0; i < Lim; i++) f[i] = f[i] * g[i] % Mod;
    NTT(f, -1);
    // for (int i = 0; i < 10; i++) printf("%lld%c", f[i], " \n"[i == 9]);
    for (int i = Mx + 1; i < Lim; i++) f[i] = g[i] = 0;
    for (int i = 0; i <= Mx; i++) g[i] = f[i];
    NTT(f, 1), NTT(g, 1);
    for (int i = 0; i < Lim; i++) f[i] = f[i] * g[i] % Mod;
    NTT(f, -1);
    // for (int i = 0; i < 10; i++) printf("%lld%c", f[i], " \n"[i == 9]);
    int B = 1300;
    sort(q + 1, q + Q + 1, [&](const PI3 &i, const PI3 &j) { return i.fi.se < j.fi.se; });
    int o = 1, k = -1;
    while (o <= Q) {
        k++;
        int nB = k * B;
        if (!nB) nB = 1;
        for (int i = 0; i < Lim; i++) g[i] = A[i] = G[i] = F[i] = 0;
        for (int i = 1; i <= Mx; i++) g[i] = f[i];
        for (int i = 0; i <= Mx; i++) A[i] = Frac[nB + i - 1];
        NTT(g, 1), NTT(A, 1);
        for (int i = 0; i < Lim; i++) G[i] = g[i] * A[i] % Mod;
        NTT(G, -1);
        for (int i = 0; i < Lim; i++) g[i] = A[i] = 0;
        for (int i = 1; i < nB; i++) g[i] = f[i];
        for (int i = 1; i <= Mx; i++) A[i] = Frac[i - 1];
        NTT(g, 1), NTT(A, 1);
        for (int i = 0; i < Lim; i++) F[i] = g[i] * A[i] % Mod;
        NTT(F, -1);
        // for (int i = 0; i < 10; i++) printf("%lld%c", g[i], " \n"[i == 9]);
        // for (int i = 0; i < 10; i++) printf("%lld%c", F[i], " \n"[i == 9]);
        while (q[o].fi.se < B * (k + 1) && o <= Q) {
            int c = q[o].fi.se - nB, d = nB, w = G[q[o].fi.fi - nB] + F[q[o].fi.fi];
            while (c--) {
                w = (w - Frac[d - 1] * f[q[o].fi.fi - d] % Mod + Mod) % Mod;
                w = (w + Frac[q[o].fi.fi - d - 1] * f[d] % Mod) % Mod;
                d++;
            }
            Ans[q[o].se] = (Frac[q[o].fi.fi - 1] - w % Mod + Mod) % Mod;
            o++;
        }
    }
}

signed main(void) {
    Q = read();
    for (int i = 1; i <= Q; i++) q[i].fi.fi = read(), q[i].fi.se = read(), q[i].se = i;
    Work();
    for (int i = 1; i <= Q; i++) printf("%lld\n", Ans[i]);
    return 0;    
}
```


---

