# [POI 2006] TAN-Dancing in Circles

## 题目描述

$n$ kids attend a certain kindergarten. Everyday the kids arrange themselves in $k$ circles and dance.

At least $l$ kids dance in each circle. Two arrangements of children are considered distinct if there isa child who has a different right neighbour in one of the arrangements than in the other.

Your task is to calculate the number of all distinct arrangements modulo $2005$. Should there beno arrangements satisfying the aforementioned conditions, the correct outcome is $0$.

TaskWrite a programme which:

reads the numbers $n$, $k$ and $l$ from the standard input,        calculates the number $d'=d\ mod\ 2005$, where $d$ denotes the number of distinct arrangements    of the children ($d\ mod\ 2005$ denotes the remainder of the division of $d$ by $2005$),        writes $d'$ to the standard output.

幼儿园中有N个小朋友在做游戏，每天小朋友们都会有一个尬舞方案（围成K个圈尬舞）。


每个圈子里至少有L个小朋友，如果在一个方案里有一个小朋友他右面的小朋友和另一个方案里他右面的小朋友不同，那么两个尬舞方案就会被认为是不同的。


你的任务是计算所有不同的尬舞方案的数量，因为结果可能比较大，所以最后输出答案mod2005的结果。


如果没有符合要求的尬舞方案，输出0。


## 说明/提示

感谢@Paperback\_Writer 提供翻译


## 样例 #1

### 输入

```
7 2 3```

### 输出

```
420```

# 题解

## 作者：JCY_ (赞：9)

[更好的阅读体验](https://www.cnblogs.com/JCY-std/p/16721625.html)

神仙题目！！！感谢程老师完成了几乎所有的证明过程。

首先注意到模数是 $2005$，去掉模数似乎很不可做，所以大胆猜测正解依赖模数。

不难发现，把 $n$ 个人分成 $k_1$ 个大小为 $a_1$ 的环，$k_2$ 个大小为 $a_2$ 的环，$\dots$ $k_m$ 个大小为 $a_m$ 的环的方案（$a_1 < a_2 < \dots < a_m$，$k_1, k_2, \dots, k_m>0$，$\sum _{i = 1} ^ m k_i = k$），对答案的贡献是：

$$\frac{n!}{\prod _{i = 1} ^ m a_i! ^ {k_i} \times k_i!}\times \prod _{i = 1} ^ m (a_i - 1)! ^ {k_i}=\frac{n!}{\prod _{i = 1} ^ m a_i ^ {k_i} \times k_i!}$$

设模数为 $p$，不妨令 $p$ 为质数，最后再用中国剩余定理合并答案。下述证明用到了质数的若干性质。现在考察上式模 $p$ 不为 $0$ 的情况下 $\left\{ a_m \right\}$ 和 $\left\{ k_m \right\}$ 具有的性质。

### 性质一：$a_m \le p$。

考察等号左边的式子。若 $a_m > p$ 则 $(a_m - 1)! ^ {k_m} \equiv 0\ ~ (\text{mod} ~ p)$，上式显然为 $0$。

### 性质二：$\forall n \ge p$，$a_m=p$。

考察等号右边的式子，记 $h(x)$ 表示 $x$ 含有的质因子 $p$ 的个数。考虑反证法，设 $a_m < p$。此时，$h(n!) > 0$，$h(\prod _{i = 1} ^ m a_i ^ {k_i} \times k_i!) = h(\prod _{i=1} ^ m k_i!) \le h(k!)$。因为 $l \ge 2$，所以 $k \le \lfloor \frac{n}{2} \rfloor$，即 $h(n!) > h(k!) \ge h(\prod _{i = 1} ^ m a_i ^ {k_i} \times k_i!)$，可知原式模意义下为 $0$。

记 $f(x,y)$ 为将 $x$ 个小朋友分成 $y$ 个大小不小于 $l$ 的环的方案数，考察上述性质能推出什么结论。

### 性质三：记 $q = \lfloor \frac{n}{p} \rfloor$，$f(n,k) \equiv (-1) ^ q \times f(n ~ \text{mod} ~ p, k - q) ~ (\text{mod} ~ p)$。

由性质二，不难递归证明 $n$ 个小朋友一定会分成 $q$ 个大小为 $p$ 的组。考虑这一过程的组合系数，即：

$$\binom{n}{q \times p} \times \frac{\prod _{i = 1} ^ q \binom{i \times p}{p}}{q!} \times (p - 1)! ^ q $$

由威尔逊定理可知，$(p - 1)! ^ q \equiv (-1) ^ q ~ (\text{mod} ~ p)$。

由卢卡斯定理可知，$\binom{n}{q \times p} \equiv \binom{q}{q} \times \binom{n ~ \text{mod} ~ p}{0} \equiv 1 ~ (\text{mod} ~ p)$。

$$\frac{\prod _{i = 1} ^ q \binom{i \times p}{p}}{q!} = \frac{\prod _{i = 1} ^ q i \times \binom{i \times p - 1}{p - 1}}{q!} = \prod _{i = 1} ^ q \binom{i \times p - 1}{p - 1}$$

同样由卢卡斯定理可知，$\prod _{i = 1} ^ q \binom{i \times p - 1}{p - 1} \equiv \prod _{i = 1} ^ q \binom{i - 1}{0} \times \binom{p - 1}{p - 1} \equiv 1 ~ (\text{mod} ~ p)$

所以 $\binom{n}{q \times p} \times \frac{\prod _{i = 1} ^ q \binom{i \times p}{p}}{q!} \times (p - 1)! ^ q \equiv (-1) ^ q ~ (\text{mod} ~ p)$。

所以模 $p$ 意义下的 $f(n,k)$ 可以转化为 $f(n ~ \text{mod} ~ p, k - q)$，注意到转化后合法的 $f(x,y)$ 均满足 $x, y \le 401$，所以可以直接 dp。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, k, l;
int f(int x, int y, int mod) {
    static int dp[410][410], chs[410];
    dp[0][0] = 1;
    for (int i = l; i <= x; ++i) {
        chs[i] = 1;
        for (int j = i - l + 1; j < i; ++j) chs[i] = chs[i] * j % mod;
    }
    for (int i = 1; i <= y; ++i) {
        for (int j = i * l; j <= x; ++j)
            dp[i][j] =
                (dp[i - 1][j - l] * chs[j] + dp[i][j - 1] * (j - 1)) % mod;
    }
    return dp[y][x];
}
int solve(int mod) {
    if (l > mod) return 0;
    int q = n / mod, r = n % mod;
    if (q > k || (ll)(k - q) * l > r) return 0;
    int ret = f(r, k - q, mod);
    if (q & 1) ret = (mod - ret) % mod;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> l;
    int t1 = solve(5), t2 = solve(401);
    while (t2 % 5 != t1) t2 += 401;
    cout << t2 << "\n";
    return 0;
}

---

