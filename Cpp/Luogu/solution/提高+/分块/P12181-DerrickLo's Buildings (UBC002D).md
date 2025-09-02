# DerrickLo's Buildings (UBC002D)

## 题目描述

在某游戏中，DerrickLo 的任务是操作一堆建筑。这些建筑被摆放在了编号为 $1$ 到 $M$ 的空位上，它们的高度也分别为 $1$ 到 $M$。一开始，对于所有 $i = 1, 2, \dots, M$，高度为 $i$ 的建筑被摆在了 $i$ 号位置上。

在这个游戏中，有 $M$ 个挑战。具体地，第 $i$ 个挑战都会指定一个高度因数 $l = i$ 和目标长度 $N$，这个挑战的**得分**为在重新摆放建筑后，对于所有 $j = 1, 2, \dots N$，满足高度为 $j$ 的建筑被摆在了 $j \times l$ 号位置的数量。**注意：所有挑战的目标长度都是相同的，但高度因数是互不相同的。**

为了重新摆放这些建筑，DerrickLo 需要指定一个调换排列 $v$，每执行一次调换，就会**同时**将位置 $i$ 上的建筑移到 $v(i)$ 处。

由于 DerrickLo 并不是很看重得分是否最高，因此他指定的排列 $v$ 将是从所有 $1$ 到 $M$ 的排列中**等概率**选取的一个。不过，他还是很好奇，对于每一个挑战 $i$，在他分别调换 $1, 2, \dots, V$ 次时，他的期望得分是多少。

由于挑战的个数以及调换的次数实在太多，DerrickLo 希望你告诉所有这些得分之和模 $998244353$ 之后的结果。即：
$$
\left(\sum_{i=1}^M\sum_{k=1}^VE\left(\sum_{j=1}^N[v_k(j) = i \times j]\right)\right)\bmod 998244353
$$
其中 $v_k(j)$ 表示根据排列 $v$ 调换了 $k$ 次之后，高度为 $j$ 的建筑所在的位置编号。

## 说明/提示

在样例中，$v$ 只有 $\{1, 2\}$ 与 $\{2, 1\}$ 两种取值。你需要计算：
$$
\sum_{i=1}^2E([v(1) = i])
$$
当 $i=1$ 时，$E([v(1) = 1]) = \frac 1 2$；当 $i=2$ 时，$E([v(1) = 2]) = \frac 1 2$。因此，求和之后是 $\frac{1 + 1}{2} = 1$。

---

对于所有测试数据：

- $1 \le T \le 5$。
- $1 \le N \le M \le 10^{12}$。
- $2 \le (M \bmod 998244353)$。
- $1 \le V \le 10^{12}$。

**注意：输入数据不一定在 `int` 范围内。**


## 样例 #1

### 输入

```
1
1 2 1```

### 输出

```
1```

# 题解

## 作者：cosf (赞：1)

我们可以对 $i$ 分类讨论。当 $i \ge 2$ 时，所有的情况都相似，仅有一个系数的差别。

因为 $v$ 只有 $M!$ 种取值，所以我们先化简 $E \times M!$，最后再除掉就行了。也就是，我们要计算：

1. $\sum_{k=1}^V\left(\sum_{v \text{ is a permutation of }[M]}\sum_{j=1}^N[v_k(j) = j]\right)$
2. $\sum_{k=1}^V\left(\sum_{v \text{ is a permutation of }[M]}\sum_{j=1}^N[v_k(j) = 2j]\right)$

由期望的线性性，所有合理范围内的 $j$ 贡献都是一样的。因此，第一个式子中，我们只需算出 $1$ 的贡献，乘上 $N$ 即可。第二个式子中，算出 $1$ 的贡献，乘上 $\min\left\{N, \frac{M}{2}\right\}$ 即可。

## 第一个式子

定义排列 $v$ 上的一个环为由不同数字组成的序列 $\{a_1, a_2, \dots, a_m\}$，使得 $v(a_1) = a_2, v(a_2) = a_3, \dots, v(a_m) = a_1$，其中 $m$ 是环长。可以发现，一个排列总能被唯一划分成若干个环。

那么，当 $k$ 确定时，问题可以描述为：“有多少个排列 $v$，$1$ 所在的环的长度是 $k$ 的因数”。

则，我们可以枚举环长 $m$，则对于所有的 $m$ 的倍数 $k$，它的贡献是 $A_{M - 1}^{m - 1} \times (M - m)! = (M - 1)!$。这个值和 $m$ 无关，所以 $m$ 的贡献是 $\lfloor\frac{V}{m}\rfloor \times (M - 1)!$。那么，最终和式的值就是 $(M - 1)! \times \sum_{m=1}^M\lfloor\frac{V}{m}\rfloor$。

除去 $M!$ 之后，$E = \frac{N}{M} \times \sum_{m=1}^M\lfloor\frac{V}{m}\rfloor$，可以 $O(\sqrt{V})$ 计算。

## 第二个式子

我们只需要 $1$ 和 $2$ 在同一个环即可。当 $k$ 和 $m$ 确定的时候，$1$ 和 $2$ 在环内的相对位置是固定的。将 $1$ 设定为 $a_1$，若 $2$ 位于 $a_j$，则 $j$ 就必须满足 $j - 1 \equiv k \pmod m$。这也说明 $k$ 不能是 $m$ 的倍数。

当 $k$ 不为 $m$ 的倍数时，有 $A_{M - 2}^{m - 2} \times (M - m)! = (M - 2)!$ 个这样的排列。这样的 $k$ 一共有 $V -\lfloor\frac{V}{m}\rfloor$ 个，因此，$m$ 的贡献就是 $(M - 2)! \times (V - \lfloor\frac{V}{m}\rfloor)$。答案即 $\frac{\min\{N, \lfloor\frac{M}{2}\rfloor\}}{M(M - 1)} \times \left(MV - \sum_{m=1}^M\lfloor\frac{V}{m}\rfloor\right)$。同样可以在 $O(\sqrt{V})$ 的时间内算完。

当 $i \ge 3$ 时，这个式子就是 $\frac{\min\{N, \lfloor\frac{M}{i}\rfloor\}}{M(M - 1)} \times (MV - \sum^{M}_{m = 1}\lfloor\frac{V}{m}\rfloor)$，后面的一项和 $i$ 无关，前面的同样在 $O(\sqrt{M})$ 的复杂度内算出来。

---

更新：有个式子写错了。

### std

```cpp
#include <iostream>
using namespace std;

#define MOD 998244353ll

using ll = long long;

ll pow(ll b, ll p, ll m)
{
    b %= MOD;
    ll r = 1;
    while (p)
    {
        if (p & 1)
        {
            r = r * b % m;
        }
        b = b * b % m;
        p >>= 1;
    }
    return r;
}

ll inv(ll p)
{
    return pow(p, MOD - 2, MOD);
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll n, m, v;
        cin >> n >> m >> v;
        ll s = 0;
        for (ll l = 1, r; l <= m && l <= v; l = r + 1)
        {
            r = min(m, v / (v / l));
            s = (s + (r - l + 1) % MOD * (v / l % MOD) % MOD) % MOD;
        }
        ll mid = m / n;
        ll res = (mid - 1) % MOD * (n % MOD) % MOD;
        for (ll l = mid + 1, r; l <= m; l = r + 1)
        {
            r = m / (m / l);
            res = (res + (r - l + 1) % MOD * (m / l % MOD) % MOD) % MOD;
        }
        cout << (res * (((m % MOD) * (v % MOD) % MOD - s + MOD) % MOD) % MOD * inv(m % MOD * ((m - 1) % MOD) % MOD) % MOD + n % MOD * inv(m % MOD) % MOD * s % MOD) % MOD << endl;
    }

    return 0;
}
```

---

