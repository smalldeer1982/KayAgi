# Happy Sets

## 题目描述

Define a set $ A $ as a child of set $ B $ if and only if for each element of value $ x $ that is in $ A $ , there exists an element of value $ x+1 $ that is in $ B $ .

Given integers $ N $ and $ K $ . In order to make Chaneka happy, you must find the number of different arrays containing $ N $ sets $ [S_1, S_2, S_3, \ldots, S_N] $ such that: - Each set can only contain zero or more different integers from $ 1 $ to $ K $ . - There exists a way to rearrange the order of the array of sets into $ [S'_1, S'_2, S'_3, \ldots, S'_N] $ such that $ S'_i $ is a child of $ S'_{i+1} $ for each $ 1\leq i\leq N-1 $ .

Print the answer modulo $ 998\,244\,353 $ .

Two sets are considered different if and only if there is at least one value that only occurs in one of the two sets.

Two arrays of sets are considered different if and only if there is at least one index $ i $ such that the sets at index $ i $ in the two arrays are different.

## 说明/提示

In the first example, there are $ 11 $ different arrays of sets possible, which are:

- $ [\{\}, \{\}] $
- $ [\{\}, \{1\}] $
- $ [\{\}, \{1, 2\}] $
- $ [\{\}, \{2\}] $
- $ [\{1\}, \{\}] $
- $ [\{1\}, \{1, 2\}] $
- $ [\{1\}, \{2\}] $
- $ [\{1, 2\}, \{\}] $
- $ [\{1, 2\}, \{1\}] $
- $ [\{2\}, \{\}] $
- $ [\{2\}, \{1\}] $

## 样例 #1

### 输入

```
2 2```

### 输出

```
11```

## 样例 #2

### 输入

```
1 3```

### 输出

```
8```

## 样例 #3

### 输入

```
3 1```

### 输出

```
4```

# 题解

## 作者：Aleph_Drawer (赞：6)

首先我们一眼鉴定重排列是干扰用的。显然的观察到，对于一个不需要重排列就可以满足要求的数组 $[S_1, S_2, \dots, S_n]$，假设它是满足要求的，那么其所有的**不同的**重排列数组都是可以被计算到答案里的。

那么，我们现在考虑不需要重排列满足要求的数组。由于数组中重复的元素的数量会影响到方案数量的计算，所以不妨来先考虑一下重复的元素。非常明显的发现：

> 数组中重复的元素只可能有 $\{\}$，即空集合。

接下来是一段简短的证明。假设非空集合 $S_k$ 与其后面的 $S_{k +x}$ 重复。设 $S_{k + x}$ 的最大值为 $r$。那么，显然的，$S_k$ 最大值最大只能为 $r - x$。显然 $r - x \neq r$。假设不成立，证毕。

那么，我们来枚举 $\{\}$ 的数量，设为 $etn$。由于我们在统计的是不需要重排列就可以满足要求的数组数量，所以对于此时的 $ent$，算到答案的贡献即为 $C_{n}^{n - etn} \times (n - etn)! \times count$，其中 $count$ 即为我们正在计算的不需要重排列就可以满足要求的数组数量。

不妨对于 $i \in [1,k]$ 分别考虑，假设 $S_n$ 中出现了 $i$，那么显然的，$S_{n - 1}$ 有两种选择：出现 $i - 1$，或者什么都不出现。如果出现了 $i - 1$，那么 $S_{n - 2}$ 又可以做出相似的选择。如果没有 $\{\}$ 的限制，一共可以做出 $i + 1$ 种不同的选择。即对于单个数 $i$ 而言，贡献有 $i + 1$。根据乘法原理，总数量就是 $2 \times 3 \times 4 \times \cdots$。这个可以用阶乘预处理搞完。但是这样忽略了几种情况。

首先第一种，有可能存在某种情况，其有数的集合长度大于 $n - etn$。具体表现在数 $i$ 代表的贡献 $i + 1 > n - etn + 1$。此时我们只需要一律按照 $n - etn + 1$ 计算贡献即可。即上述的计算总数量的式子就变成了 $2 \times 3 \times 4 \times \cdots \times (n - etn) \times (n - etn + 1) \times (n - en + 1) \times \cdots$。这个可以用快速幂解决。

还有一种情况，可能存在某种情况，其最终有数的集合长度小于 $n - etn$，为了防止重复计算，我们是要删掉这些的。这里就有一个很巧妙的方法：我们先直接计算，然后减掉直接按照空集合长度为 $etn + 1$ 的情况的数量即可。

这样，我们就算出了 $count$。可能说的有点混乱，但是这种计数的东西不是三两句可以讲清楚的，建议结合代码理解。

时间复杂度不太会算，感觉是 $\Theta(n \log \log n)$ 的。但是复杂度的绝对上界 $O(n \log n)$ 也稳过。

放个代码。

```c++
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 105;
const ll MOD = 998244353;

int n, k;
ll fr[N], invfr[N];

ll qpow(ll bas, int exp) {
    ll res = 1;
    while(exp) {
        if(exp & 1) res *= bas, res %= MOD;
        bas *= bas, bas %= MOD;
        exp >>= 1;
    }
    return res;
}

ll C(ll n, ll m) {
    return fr[n] * invfr[m] % MOD * invfr[n - m] % MOD;
}

int main() {
    scanf("%d%d", &n, &k);
    fr[0] = 1;
    for(ll i = 1; i < N; i++)
        fr[i] = fr[i - 1] * i % MOD;
    invfr[N - 1] = qpow(fr[N - 1], MOD - 2);
    for(ll i = N - 2; i >= 0; i--)
        invfr[i] = invfr[i + 1] * (i + 1) % MOD;
    ll ans = 0;
    for(ll etn = 0; etn <= n; etn++) { // representing {}_num
        if(etn < n - k) continue;
        // left = n - etn
        ll tmp = fr[n - etn + 1] * qpow(n - etn + 1, k - n + etn) % MOD - fr[n - etn] * qpow(n - etn, k - n + etn + 1) % MOD;
        tmp = (tmp % MOD) + MOD % MOD;
        ans += C(n, n - etn) * tmp % MOD * fr[n - etn] % MOD;
        ans %= MOD;
    }
    printf("%lld\n", (ans % MOD + MOD) % MOD);
    return 0;
}
```

---

## 作者：_tobi_ (赞：3)

观察到除了空集，其他集合不可能重复，因为后面的集合最大值一定比前面的集合至少大了 $1$。

因此考虑首先枚举空集数量 $t$，记 $n - t$ 个集合，不考虑排列的方案数 $cnt$，则答案为 $\binom{n}{n - t} \times (n - t)! \times cnt$。

计算 $cnt$，考虑每个元素被删除的位置 $p$（$p$ 还在，$p - 1$ 没了，位置 $0$ 代表空集）：

如果一个数 $x \geq n - t$，那么他有 $n - t + 1$ 种方案（可以不选，可以在 $1 \sim n-t$ 的任意位置被删除），贡献是 $(n - t + 1) ^ {k - (n - t) + 1}$。

但是我们钦定了位置 $0$ 是空集，位置 $1$ 不是空集，那么容斥一下，要减去位置 $1$ 也变成了空集的情况，即
$(n - t) ^ {k - (n - t) + 1}$ （所有数都不在 $1$ 删除）

对于其他的数 $y \leq n - t - 1$，他们在 $1 \sim y$ 的任意位置都可以被删除，也可以不选，所以贡献为：

$2 \times 3 \times \cdots \times (n - t - 1 + 1) = (n - t)!$。

综上，答案即为 $\sum\limits_{t = n - k}^n ((n - t + 1) ^ {k - (n - t) + 1} - (n - t) ^ {k - (n - t) + 1}) \times (n - t)! \times \binom{n}{n - t} \times (n - t)!$。

[代码](https://codeforces.com/contest/1866/submission/280832489)

---

## 作者：huangrenheluogu (赞：1)

看到重排，应该怎么算？

想必大家的想法都是按顺序枚举，使得前一个是后一个的 child（就是翻译中的子集，但感觉会和我们平时定义的子集搞乱，所以用原文中的 child）。

接下来，是求出每一种的个数，然后排序。在样例解释里，我们看到可以有两个空集，那么，其他的集合会重复吗？

不会的，原因是集合的最大值会变大。

那么，只有空集会重复。所以我们可以枚举空集的数量 $i$，然后这种方案的总数就是 $A_n^{n-i}$。

那么，接下来考虑计算。在接下来的叙述中，我想从最后一个集合（不是别人的 child 的集合）开始，进行“删数”操作。

为了方便，我们在第一个集合（非空）前面（第 $0$ 个集合）设置为空集，而把其他空集不考绿。

首先，我们的 $1\sim k$ 的数可以分成两类。第一类是可能“存活”到第一个集合，在第 $1$ 个集合变成第 $0$ 个集合的时候删掉。总共有 $n-i$ 个非空集合，这种数就有 $k-(n-i)+1$ 个。

这些数可以被删去的位置是 $1\rightarrow0,2\rightarrow1,\dots,n-i\rightarrow n-i-1$ 这 $n-i$ 次删除中被删除。当然，还可以不选，那么就当时在到 $n-i$ 个集合的时候被删除，这一部分的贡献是 $(n-i+1)^{k-(n-i)+1}$。

当然，由于第一个集合是非空的，所以必须有 $1$ 个是在 $1\rightarrow 0$ 的时候删除的。太难算了，考虑减去不合法的数量，都在 $2\rightarrow1,\dots,n-i\rightarrow n-i-1$ 次删除或者不选，那么就是 $(n-i)^{k-(n-i)+1}$。

因此，第一部分的贡献是 $(n-i+1)^{k-(n-i)+1}-(n-i)^{k-(n-i)+1}$。

-------------------

下面是其他 $n-i-1$ 个数的贡献。

考虑数 $1\le j\le n-i-1$，可以不选或者在 $j$ 个位置被删除，所以就是 $j+1$ 种可能。

根据乘法原理，总数就是 $((n-i+1)^{k-(n-i)+1}-(n-i)^{k-(n-i)+1})\times(n-i-1+1)\times(n-i-2+1)\times\dots\times(1+1)$。

所以就是 $((n-i+1)^{k-(n-i)+1}-(n-i)^{k-(n-i)+1})\times(n-i)!$。

这种的排列数是 $A_n^{n-i}$，前面已经说过了。

预处理前缀积和它的逆元，复杂度可以做到 $O(n\log n)$（认为 $n,k$ 同阶）。

由于作者太菜了，不会处理全是空集的情况，所以只枚举了 $0\sim n-1$ 个空集，然后把 $ans$ 增加 $1$。

[code](https://codeforces.com/contest/1866/submission/239042829)

说一下我的非人类智慧行为警示后人/自己：

- mod 写成了 $9982244353$。

- 调试忘记删了。

---

