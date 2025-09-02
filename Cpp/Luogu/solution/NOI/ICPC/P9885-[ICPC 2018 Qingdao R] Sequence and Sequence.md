# [ICPC 2018 Qingdao R] Sequence and Sequence

## 题目描述

考虑下列两个序列 $P$ 和 $Q$。我们用 $P(i)$ 表示序列 $P$ 中的第  $i$ 个元素，用 $Q(i)$ 表示序列 $Q$ 中的第 $i$ 个元素：

- 序列 $P$ 是一个**已排序的**序列，其中，对于所有 $k \in \mathbb{Z^+}$，$k$ 在序列 $P$ 中出现 $(k+1)$ 次（$\mathbb{Z^+}$ 为正整数集）。也就是说，$P = \{1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, \dots \}$
- 序列 $Q$ 可以由以下方程导出：
$$\begin{cases} Q(1) = 1 & \\ Q(i) = Q(i-1) + Q(P(i)) & \text{if } i > 1 \end{cases}$$   
也就是说，$Q = \{1, 2, 4, 6, 8, 12, 16, 20, 24, 30, 36, 42, 48, 54, 62, \dots \}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ukq7qs74.png)

给定一个正整数 $n$，请计算 $Q(n)$ 的值。

## 样例 #1

### 输入

```
4
10
100
1000
987654321123456789```

### 输出

```
30
2522
244274
235139898689017607381017686096176798```

# 题解

## 作者：cxyMOI (赞：5)

# P9885

## 算法

在这篇题解中，用 $P_k$ 代替 $P(k)$。

对 $Q(k)-Q(k-1)=Q(P_k)$ 累和，并注意 $Q(1)=Q(P_1)$，即有
$$\begin{aligned}
&Q(n)\\
=&\sum_{k=1}^nQ(P_k)\\
=&\sum_{x=1}^{P_n-1}\left(\sum_{k=\frac{x^2+x}{2}}^{\frac{x^2+3x}{2}}1\right)Q(x)+\left(\sum_{k=\frac{P_n^2+P_n}{2}}^n1\right)Q(P_n)\\
\end{aligned}$$

第二项中 $Q(P_n)$ 的系数是 $\sum\limits_{k=\frac{P_n^2+P_n}{2}}^n1=n+1-\frac{P_n^2+P_n}{2}$ 可以 $O(1)$ 求出，于是第二项可以递归求出。下面计算第一项。

$$\begin{aligned}
&\sum_{x=1}^{P_n-1}\left(\sum_{k=\frac{x^2+x}{2}}^{\frac{x^2+3x}{2}}1\right)Q(x)\\
=&\sum_{x=1}^{P_n-1}\left((x+1)Q(x)\right)\\
=&\sum_{x=1}^{P_n-1}\left((x+1)\sum_{k=1}^xQ(P_k)\right)\\
=&\sum_{k=1}^{P_n-1}\left(\sum_{x=k}^{P_n-1}(x+1)\right)Q(P_k)\\
=&\sum_{k=1}^{P_n-1}\frac{\left(P_n-k\right)\left(P_n+k+1\right)}{2}Q(P_k)\\
=&\sum_{x=1}^{P_{P_n-1}-1}\left(\sum_{k=\frac{x^2+x}{2}}^{\frac{x^2+3x}{2}}\frac{\left(P_n-k\right)\left(P_n+k+1\right)}{2}\right)Q(x)+\left(\sum_{k=\frac{P_{P_n-1}^2+P_{P_n-1}}{2}}^{P_n-1}\frac{\left(P_n-k\right)\left(P_n+k+1\right)}{2}\right)Q(P_{P_n-1})\\
\end{aligned}$$

第二项中 $Q(P_{P_n-1})$ 的系数是

$$\begin{aligned}
&\sum\limits_{k=\frac{P_{P_n-1}^2+P_{P_n-1}}{2}}^{P_n-1}\frac{\left(P_n-k\right)\left(P_n+k+1\right)}{2}\\
=&\frac{\left(-P_{P_n-1}^2-P_{P_n-1}+2 P_n\right) \left(-P_{P_n-1}^2-P_{P_n-1}+2 P_n+2\right) \left(P_{P_n-1}^2+P_{P_n-1}+4 P_n+2\right)}{48}
\end{aligned}$$

可以 $O(1)$ 求出，于是第二项可以递归求出。下面计算第一项。

$$\begin{aligned}
&\sum_{x=1}^{P_{P_n-1}-1}\left(\sum_{k=\frac{x^2+x}{2}}^{\frac{x^2+3x}{2}}\frac{\left(P_n-k\right)\left(P_n+k+1\right)}{2}\right)Q(x)\\
=&\sum_{x=1}^{P_{P_n-1}-1}\left(\frac{(x+1)\left(12P_n^2+12P_n-3x^4-12x^3-19x^2-14x\right)}{24}\right)Q(x)\\
=&\sum_{x=1}^{P_{P_n-1}-1}\left(\left(\frac{(x+1)\left(12P_n^2+12P_n-3x^4-12x^3-19x^2-14x\right)}{24}\right)\sum_{k=1}^xQ(P_k)\right)\\
=&\sum_{k=1}^{P_{P_n-1}-1}\left(\sum_{x=k}^{P_{P_n-1}-1}\left(\frac{(x+1)\left(12P_n^2+12P_n-3x^4-12x^3-19x^2-14x\right)}{24}\right)\right)Q(P_k)\\
=&\sum_{k=1}^{P_{P_n-1}-1}\frac{\left(k-P_{P_n-1}\right) \left(k+P_{P_n-1}+1\right) \left(k^4+2 k^3+k^2 P_{P_n-1}^2+k^2 P_{P_n-1}+k^2+k P_{P_n-1}^2+k P_{P_n-1}+P_{P_n-1}^4+2 P_{P_n-1}^3-12 P_n^2+P_{P_n-1}^2-12 P_n-4\right)}{48}Q(P_k)\\
=&\sum_{x=1}^{P_{P_{P_n-1}-1}-1}\left(\sum_{k=\frac{x^2+x}{2}}^{\frac{x^2+3x}{2}}\frac{\left(k-P_{P_n-1}\right) \left(k+P_{P_n-1}+1\right) \left(k^4+2 k^3+k^2 P_{P_n-1}^2+k^2 P_{P_n-1}+k^2+k P_{P_n-1}^2+k P_{P_n-1}+P_{P_n-1}^4+2 P_{P_n-1}^3-12 P_n^2+P_{P_n-1}^2-12 P_n-4\right)}{48}\right)Q(x)\\
&+\left(\sum_{k=\frac{P_{P_{P_n-1}-1}^2+P_{P_{P_n-1}-1}}{2}}^{P_{P_n-1}-1}\frac{\left(k-P_{P_n-1}\right) \left(k+P_{P_n-1}+1\right) \left(k^4+2 k^3+k^2 P_{P_n-1}^2+k^2 P_{P_n-1}+k^2+k P_{P_n-1}^2+k P_{P_n-1}+P_{P_n-1}^4+2 P_{P_n-1}^3-12 P_n^2+P_{P_n-1}^2-12 P_n-4\right)}{48}\right)Q(P_{P_{P_n-1}-1})\\
\end{aligned}$$

第一项 $\sum\limits_{x=1}^{P_{P_{P_n-1}-1}-1}$ 里的式子中，$Q(x)$ 的系数等于

$$\begin{aligned}
&\frac{35 x^{13}+455 x^{12}+2905 x^{11}+11935 x^{10}+34475 x^9+72345 x^8+110955 x^7+122325 x^6+90454 x^5+32620 x^4-13160 x^3-24640 x^2-10624 x}{107520}\cdot1\\
+&(x+1)\cdot\frac{P_{P_n-1} \left(P_{P_n-1}+1\right) \left(12 P_n \left(P_n+1\right)+4-P_{P_n-1}^2 \left(P_{P_n-1}+1\right)^2\right)}{48}\\
-&\frac{3 x^5+15 x^4+31 x^3+33 x^2+14 x}{24}\cdot\frac{P_n \left(P_n+1\right)}{2}\\
\end{aligned}$$

这里每一项都是一个关于 $x$ 的多项式和一个关于 $P_n$ 和 $P_{P_n-1}$ 的多项式的乘积。后者是常数可以提出去 $O(1)$ 计算，只需要计算前者乘以 $Q(x)$ 的前缀和。由于 $P_{P_{P_n-1}-1}-1\le183999$，预处理即可。

第二项中 $Q(P_{P_{P_n-1}-1})$ 的系数是：

$$\begin{aligned}
&\sum_{k=\frac{P_{P_{P_n-1}-1}^2+P_{P_{P_n-1}-1}}{2}}^{P_{P_n-1}-1}\frac{\left(k-P_{P_n-1}\right) \left(k+P_{P_n-1}+1\right) \left(k^4+2 k^3+k^2 P_{P_n-1}^2+k^2 P_{P_n-1}+k^2+k P_{P_n-1}^2+k P_{P_n-1}+P_{P_n-1}^4+2 P_{P_n-1}^3-12 P_n^2+P_{P_n-1}^2-12 P_n-4\right)}{48}\\
=&\frac{1}{215040}\left(2 P_{P_n-1}-P_{P_{P_n-1}-1}^2-P_{P_{P_n-1}-1}\right) \left(2 P_{P_n-1}+2-P_{P_{P_n-1}-1}^2-P_{P_{P_n-1}-1}\right)\left(\text{A long polynomial}\right)
\end{aligned}$$

其中 $\text{A long polynomial}$ 因为太长了，所以放到代码块里。它的值是：

```
8960 P_n^2 P_{P_n-1}-960 P_{P_n-1}^5+2240 P_n^2 P_{P_{P_n-1}-1}^2-400 P_{P_n-1}^4 P_{P_{P_n-1}-1}^2-160 P_{P_n-1}^3 P_{P_{P_n-1}-1}^4-60 P_{P_n-1}^2 P_{P_{P_n-1}-1}^6-20 P_{P_n-1} P_{P_{P_n-1}-1}^8-5 P_{P_{P_n-1}-1}^{10}+2240 P_n^2 P_{P_{P_n-1}-1}-400 P_{P_n-1}^4 P_{P_{P_n-1}-1}-320 P_{P_n-1}^3 P_{P_{P_n-1}-1}^3-180 P_{P_n-1}^2 P_{P_{P_n-1}-1}^5-80 P_{P_n-1} P_{P_{P_n-1}-1}^7-25 P_{P_{P_n-1}-1}^9+4480 P_n^2-2400 P_{P_n-1}^4-960 P_{P_n-1}^3 P_{P_{P_n-1}-1}^2-420 P_{P_n-1}^2 P_{P_{P_n-1}-1}^4-180 P_{P_n-1} P_{P_{P_n-1}-1}^6-60 P_{P_{P_n-1}-1}^8-800 P_{P_n-1}^3 P_{P_{P_n-1}-1}-540 P_{P_n-1}^2 P_{P_{P_n-1}-1}^3-260 P_{P_n-1} P_{P_{P_n-1}-1}^5-90 P_{P_{P_n-1}-1}^7+8960 P_n P_{P_n-1}-1408 P_{P_n-1}^3+2240 P_n P_{P_{P_n-1}-1}^2-368 P_{P_n-1}^2 P_{P_{P_n-1}-1}^2-136 P_{P_n-1} P_{P_{P_n-1}-1}^4-49 P_{P_{P_n-1}-1}^6+2240 P_n P_{P_{P_n-1}-1}-128 P_{P_n-1}^2 P_{P_{P_n-1}-1}+68 P_{P_n-1} P_{P_{P_n-1}-1}^3+63 P_{P_{P_n-1}-1}^5+4480 P_n+288 P_{P_n-1}^2+336 P_{P_n-1} P_{P_{P_n-1}-1}^2+170 P_{P_{P_n-1}-1}^4+272 P_{P_n-1} P_{P_{P_n-1}-1}+180 P_{P_{P_n-1}-1}^3+3072 P_{P_n-1}+776 P_{P_{P_n-1}-1}^2+704 P_{P_{P_n-1}-1}+1408
```

虽然很长，但仍然可以 $O(1)$ 求出，又因为 $Q(P_{P_{P_n-1}-1})$ 可以预处理，于是第二项可以 $O(1)$ 求出。

## 复杂度

空间复杂度是 $\Theta(n^{\frac{1}{8}})$，因为需要预处理 $\Theta(n^{\frac{1}{8}})$ 大小的前缀和。

假设大数计算的时间复杂度为 $\Theta(1)$。

预处理的时间复杂度显然是 $\Theta(n^{\frac{1}{8}})$。

设计算 $Q(2^{2^x})$ 的时间复杂度为 $T(x)$。有 $T(x)=O(1)+T(x-1)+T(x-2)$，于是 $T(x)=\Theta(\left(\frac{1+\sqrt{5}}{2}\right)^x)$，故单次询问时间复杂度为 $\Theta(\left(\frac{1+\sqrt{5}}{2}\right)^{\log_2{\log_2{n}}})=\Theta((\log_2{n})^{\log_2{\frac{1+\sqrt{5}}{2}}})$。

## 实现

那些很长的多项式导致常数极大，需要卡常。

* 预处理时适当地通过加法计算 $Q(x)$ 的系数，从而避免使用高精度乘法。
* 用尽量少的计算次数计算那些非常长的多项式。例如可以用 Horner 形式重写多项式。
* 压位高精度。

[代码](https://www.luogu.com.cn/paste/mpu69nv8)

---

## 作者：Alex_Wei (赞：4)

### A. [P9885 [ICPC2018 Qingdao R] Sequence and Sequence](https://www.luogu.com.cn/problem/P9885)

注意到 $P(n) = \mathcal{O}(\sqrt n)$，考虑在这一点上做文章，将规模为 $n$ 的问题归纳到规模为 $\mathcal{O}(\sqrt n)$ 的问题上。

设 $R_n$ 为 $n$ 在 $P$ 中最后一次出现的位置，即 $\binom {n + 2} 2 - 1$，设 $p = P(n)$，可知
$$
Q(n) = \sum_{i = 1} ^ {R_{p - 1}} (i + 1)\cdot Q(i) + (n - R_{p - 1}) \cdot Q(p)
$$
$Q(p)$ 就是规模为 $\mathcal{O}(\sqrt n)$ 的子问题，但前面的怎么处理？

$i + 1$ 是关于 $i$ 的多项式，如果将 $\sum (i + 1) \cdot Q(i)$ 的每个 $Q(i)$ 继续展开为 $p$ 更小的 $Q(p)$ 之和，可以预料到新的贡献系数也是多项式，除了边界要特殊处理。

来推一下吧。设当前要算 $\sum_{i = 1} ^ n f(i) \cdot Q(i)$，$p = P(n)$。

对于 $1\leq k < p$，新的贡献系数为
$$
f'(k) = \sum_{i = R_{k - 1} + 1} ^ {R_k} f(i) \cdot (i - R_{k - 1}) + \sum_{i = R_k + 1} ^ n f(i) \cdot (k + 1)
$$
$T$ 在 $10 ^ 4$ 级别，为了保证复杂度，尽量不要对每个 $n$ 都求贡献系数多项式，所以需要让多项式和 $n$ 无关，而只和递归层数有关。

设 $F$ 为 $f$ 的前缀和，$F_2$ 为 $f(i) \cdot i$ 的前缀和，则 $\deg F = \deg f + 1$，$\deg F_2 = \deg f + 2$，且
$$
f'(k) = (F_2(R_k) - F_2(R_{k - 1})) -R_{k - 1}(F(R_k) - F(R_{k - 1})) + (k + 1) \cdot (F(n)- F(R_k))
$$
因为 $R_k$ 是关于 $k$ 的二次多项式，所以对任意多项式 $G$，$\deg G(R_k) = 2\deg G(k)$。于是
$$
\deg f' = \max(2\deg F_2 - 1, 2 + (2\deg F - 1), 1 + 2\deg F) = 2\deg f + 3
$$
将 $F(n)$ 一项去掉，这样多项式就和 $n$ 无关了。但是少算了 $F(n) \cdot \sum_{i = 1} ^ {p - 1} (i + 1) \cdot Q(i)$，这刚好是一开始的形式，太巧了！

对于 $k = p$，新的贡献系数为
$$
f'(p) = \sum_{i = R_{p - 1} + 1} ^ n f(i) \cdot (i - R_{k - 1})
$$
只有一项，根据 $F$ 和 $F_2$ 算出系数之后乘以 $Q(p)$ 就是这部分的贡献了。

多项式只和递归层数有关，需要在递归层数和 $n$ 之间寻找平衡。$f$ 按上述公式迭代三次，得到 $29$ 次多项式 $f'''$，此时用 $P(n)\leq \sqrt {2n}$ 粗略估计得到
$$
P(P(P(P(n)))) \leq 605
$$
预处理 $f, f', f'', f'''$，它们的前缀和以及乘以 $k$ 的前缀和，**用点值形式维护**，方便做前缀和以及拉格朗日插值（用多项式维护麻烦不死你哦）。再对每个 $0\leq d < 4$ 和 $1\leq n\leq 605$ 预处理递归 $d$ 次 $n$ 的答案。

拉格朗日插值高精度运算常数太大怎么办？中国剩余定理走起！易知 $Q(n) \leq n ^ 2$，只要 $9$ 个 $10 ^ 9$ 级别的质数就行。但是存储下标以及 CRT 合并答案的时候依然需要高精度，所以还是要高精度板子，甚至要高精度取模和开根！二分求 $P$ 避免高精度开根，但是取模不太能避免。提供一份比较厉害的压位高精 [板子](https://www.luogu.com.cn/paste/daslqo66)，当然最好的方法是用蟒蛇 3 写。

看了某 s 卷玉的代码，貌似写成 $\sum_{i = 1} ^ nf(i)\cdot Q(P(i))$ 会更好维护一点，而且这样 $Q(n)$ 和 $\sum_{i = 1} ^ n f(i) \cdot Q(P(i))$ 形式一致，可以合并在一起。

时间复杂度 $\mathcal{O}($能过$)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

// 此处省略一万行高精度板子

using namespace decimal;

using bi = bigint;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;
using LL = __int128_t;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;

// ---------- templates above ----------

struct FastMod {
  ull b, m;
  void init(ull p) {b = p, m = ull((LL(1) << 64) / p);}
  ull rd(ull a) {
    ull q = (LL(a) * m) >> 64;
    ull r = a - q * b;
    return r >= b ? r - b : r;
  }
};

constexpr int L = 610;
constexpr int N = 32;
constexpr int M = 1e6 + 5;

bi rpos(bi k) {return k * (k + 1) / 2 + k;}

ll P[M], Q[M];
map<bi, bi> mpp;
bi calcP(bi n) {
  if(n < M) return P[int(n)];
  auto it = mpp.find(n);
  if(it != mpp.end()) return it->second;
  bi l = 1, r = min(n - 1, bi("141500000000000000000"));
  while(l < r) {
    bi m = (l + r + 2) / 2;
    if(m * (m + 1) <= n + n) l = m;
    else r = m - 1;
  }
  return mpp[n] = l;
}

struct solver {
  int mod, inv;
  FastMod R;
  void addt(int &x, int y) {
    x += y, x >= mod && (x -= mod);
  }
  int add(int x, int y) {
    return x += y, x >= mod && (x -= mod), x;
  }
  int ksm(int a, int b) {
    int s = 1;
    while(b) {
      if(b & 1) s = R.rd(1ll * s * a);
      a = R.rd(1ll * a * a), b >>= 1;
    }
    return s;
  }
  int de[N], iv[N];
  int f[4][N], F[4][N], F2[4][N], g[4][L];
  int eval(int *f, bi _x) {
    int x = int(_x % mod);
    static int pre[N], suf[N + 1];
    pre[0] = suf[N] = 1;
    for(int i = 1; i < N; i++) {
      pre[i] = pre[i - 1];
      pre[i] = R.rd(1ll * pre[i] * (x + mod - i));
    }
    for(int i = N - 1; i; i--) {
      suf[i] = suf[i + 1];
      suf[i] = R.rd(1ll * suf[i] * (x + mod - i));
    }
    int ans = 0;
    for(int i = 1; i < N; i++) {
      int nume = R.rd(1ll * pre[i - 1] * suf[i + 1]);
      addt(ans, R.rd(R.rd(1ll * nume * f[i]) * iv[i]));
    }
    return ans;
  }
  int eval(int *f, bi l, bi r) {
    return add(eval(f, r), mod - eval(f, l));
  }
  void init(int p) {
    R.init(mod = p);
    for(int i = 1; i < N; i++) {
      de[i] = 1;
      for(int j = 1; j < N; j++) {
        if(i != j) de[i] = R.rd(1ll * de[i] * (i + mod - j));
      }
      iv[i] = ksm(de[i], mod - 2);
    }
    for(int k = 1; k < N; k++) {
      f[0][k] = k + 1;
      F[0][k] = add(F[0][k - 1], f[0][k]);
      F2[0][k] = add(F2[0][k - 1], R.rd(1ll * f[0][k] * k));
    }
    for(int i = 1; i < 4; i++) {
      for(int k = 1; k < N; k++) {
        int rk = int(rpos(k)), lk = rk - (k + 1);
        f[i][k] = eval(F2[i - 1], lk, rk);
        addt(f[i][k], R.rd(1ll * (mod - lk) * eval(F[i - 1], lk, rk)));
        addt(f[i][k], mod - R.rd(1ll * (k + 1) * eval(F[i - 1], rk)));
        F[i][k] = add(F[i][k - 1], f[i][k]);
        F2[i][k] = add(F2[i][k - 1], R.rd(1ll * f[i][k] * k));
      }
    }
    for(int i = 0; i < 4; i++) {
      for(int j = 1; j < L; j++) {
        g[i][j] = add(g[i][j - 1], R.rd(1ll * eval(f[i], j) * Q[j]));
      }
    }
  }
  int calc(int dep, bi n);
  int calcQ(bi n);
  map<bi, int> mp[4], mpq;
} f[9];

int solver::calc(int dep, bi n) {
  if(n < L) return g[dep][int(n)];
  auto it = mp[dep].find(n);
  if(it != mp[dep].end()) return it->second;
  bi p = calcP(n), rp = rpos(p - 1);
  int coef = eval(F2[dep], rp, n);
  addt(coef, R.rd(1ll * int(mod - rp % mod) * eval(F[dep], rp, n)));
  int res = R.rd(1ll * coef * calcQ(p));
  addt(res, R.rd(1ll * eval(F[dep], n) * calc(0, p - 1)));
  addt(res, calc(dep + 1, p - 1));
  return mp[dep][n] = res;
}

int solver::calcQ(bi n) {
  if(n < M) return R.rd(Q[int(n)]);
  auto it = mpq.find(n);
  if(it != mpq.end()) return it->second;
  bi p = calcP(n), rp = rpos(p - 1);
  int coef = int((n - rp) % mod);
  int res = add(calc(0, p - 1), R.rd(1ll * coef * calcQ(p)));
  return mpq[n] = res;
}

bi PR = 1;
void init() {
  for(int i = 1, c = 1; c < M; i++) {
    for(int j = 1; j <= i + 1 && c < M; j++) {
      P[c++] = i;
    }
  }
  Q[1] = 1;
  for(int i = 2; i < M; i++) {
    Q[i] = Q[i - 1] + Q[P[i]];
  }
  for(int i = 1e9, c = 0; c < 9; i++) {
    bool prime = 1;
    for(int j = 2; j * j <= i && prime; j++) {
      prime &= i % j > 0;
    }
    if(prime) f[c++].init(i), PR *= i;
  }
  for(int i = 0; i < 9; i++) {
    f[i].inv = f[i].ksm(int((PR / f[i].mod) % f[i].mod), f[i].mod - 2);
  }
}

void solve(int T) {
  bi n, ans = 0;
  cin >> n;
  for(int i = 0; i < 9; i++) {
    int res = f[i].calcQ(n);
    ans += (PR / f[i].mod) * res * f[i].inv;
  }
  cout << ans % PR << "\n";
}

bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  init();
  int T = 1;
  cin >> T;
  // T = 1e4;
  while(T--) solve(T);
  fprintf(stderr, "%.3lf ms\n", 1e3 * clock() / CLOCKS_PER_SEC);
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：not_clever_syl (赞：3)

模拟赛搬了这个题，写一发题解~~纪念我成功补掉依托shi~~。

以下 $p_i=P(i),q_i=Q(i)$。

首先根据递推式我们可得：

$$
q_n=\sum_{i=1}^n{q_{p_i}}
$$

当 $i \in [1,n]$ 时 $p_i \leq O(\sqrt{n})$，所以我们希望凑出一些式子含有 $p_{i}-p_{i-1}$ 的形式或 $q_{p_i}-q_{p_{i-1}}$ 之类的形式。

接下来是一种叫“分部求和法”的神秘技巧：

令 $f_0(x)=1$，$F_i(x)=\sum_{j=1}^xf_i(j)$，$f_{i+1}(x)=F_i(\frac{x(x+1)}{2}-1)$，那么：

$$
\begin{aligned}
q_n
&=\sum_{i=1}^n{q_{p_i}}\\
&=\sum_{i=1}^nf_0(i){q_{p_i}}\\
&=\sum_{i=1}^n(F_0(i)-F_0(i-1)){q_{p_i}}\\
&=F_0(n)q_{p_n}+\sum_{i=1}^{n-1} F_0(i)(q_{p_i}-q_{p_{i+1}})\\
&=F_0(n)q_{p_n}-\sum_{i=0}^{n-1} F_0(i)(q_{p_{i+1}}-q_{p_{i}})\\
&=F_0(n)q_{p_n}-\sum_{i=1}^{n} F_0(i-1)(q_{p_{i}}-q_{p_{i-1}})\\
\end{aligned}
$$

出现了 $q_{p_{i}}-q_{p_{i-1}}$ 的形式，这样我们枚举 $p_{i}\neq p_{i-1}$ 的 $i=\frac{j(j+1)}{2},j \in \N$，且我们可以发现 $j=p_i$。

于是我们枚举 $j$：

$$
\begin{aligned}

q_n
&=F_0(n)q_{p_n}-\sum_{i=1}^{n} F_0(i-1)(q_{p_{i}}-q_{p_{i-1}})\\
&=F_0(n)q_{p_n}-\sum_{j=1}^{p_{n}} F_0(\frac{j(j+1)}{2}-1)(q_{j}-q_{j-1})\\
&=F_0(n)q_{p_n}-\sum_{j=1}^{p_{n}} F_0(\frac{j(j+1)}{2}-1)q_{p_j}\\
&=F_0(n)q_{p_n}-\sum_{j=1}^{p_{n}} f_1(j)q_{p_j}\\
\end{aligned}
$$

这时我们设 $g(n,k)=\sum_{i=1}^nf_k(i)q_{p_i}$，那么我们就可以知道：

$$
\begin{aligned}
q_n&=g(n,0)\\
g(n,k)&=F_k(n)q_{p_n}-\sum_{j=1}^{p_{n}} f_{k+1}(j)q_{p_j}\\
&=F_k(n)g(p_{n},0)-g(p_{n},k+1)\\
\end{aligned}
$$

每次递归都可以把 $n$ 的大小开根号。

用 $p_n \leq \sqrt{2n}$ 估计递归四层以后 $n$ 只有 $605$ 的大小，可以直接预处理。

关于维护 $f_k,F_k$ 的部分，可以维护一些连续点值，然后求值的时候直接拉插即可。

预处理时间复杂度很小，查询复杂度是 $O(2^{\max k}q\max{\deg F_i})$，其中 $\max k=5,\max \deg F_i = 47$。

python 代码：

~~python跑得比C++还快拿了最优解（那个匿名用户不算）~~

```python
f = [None]*5
F = [None]*5

f[0] = [1]

fc = [1]*80

for i in range(1,80):
    fc[i] = fc[i-1]*i

def getf(f:list, x:int):
    n = len(f)
    if x < n and x>=0:
        return f[x]
    if n>=80:
        print(n)
    r = 0
    m = 1
    for i in range(n):
        m = m*(x-i)
    for i in range(n):
        t = m//(x-i)*f[i]*(-1 if (n-i-1)%2==1 else 1)
        r += t*(fc[n]//fc[i])*(fc[n]//fc[n-i-1])
    return r//(fc[n]*fc[n])

def work2(f):
    r = f.copy()
    n = len(f)
    r.append(getf(f,n))
    r[0] = 0
    for i in range(1,len(r)):
        r[i] += r[i-1]
    return r

def work1(f):
    r = [None]*len(f)*2
    for i in range(len(r)):
        r[i] = getf(f,i*(i+1)//2-1)
    return r

ans = [None]*5
B = 700
q = [None]*B
p = [None]*B

def init():
    q[0] = 0
    q[1] = 1
    q[2] = 2
    p[0] = 0
    p[1] = p[2] = 1
    idc = 2
    c = 0
    for i in range(3,B):
        q[i] = q[i-1] + q[idc]
        p[i] = idc
        c += 1
        if c == idc + 1:
            idc += 1
            c = 0
    for i in range(5):
        if i:
            f[i] = work1(F[i-1])
        F[i] = work2(f[i])
        ans[i] = [None]*B
        ans[i][0] = 0
        for j in range(1,B):
            ans[i][j] = ans[i][j-1] + getf(f[i],j)*q[p[j]]

def getp(n: int):
    l = 1
    r = n
    while r-l>1:
        mid = (l+r)>>1
        if mid*(mid+3)<2*n:
            l = mid
        else:
            r = mid
    return r

def g(d:int, n:int):
    if n<B:
        return ans[d][n]
    p = getp(n)
    return getf(F[d],n)*g(0,p)-g(d+1,p)

init()

t=int(input())
for tc in range(t):
    n=int(input())
    print(g(0,n))
```

---

## 作者：yukimianyan (赞：0)

## 1. Abel 分部求和公式

[数分笔记——Abel 分部求和公式 - 知乎](https://zhuanlan.zhihu.com/p/611254454)

$A_i=\sum_{j=1}^ia_j$。
$$
\sum_{i=1}^na_ib_i=A_nb_n-\sum_{i=1}^{n-1}A_i(b_{i+1}-b_i)
$$
因为左式
$$
\begin{aligned}
=&\sum_{i=1}^n(A_i-A_{i-1})b_i\\
=&\sum_{i=1}^nA_ib_i-\sum_{i=1}^nA_{i-1}b_i\\
=&\sum_{i=1}^nA_ib_i-\sum_{i=0}^{n-1}A_{i}b_{i+1}\\
=&A_nb_n-A_0b_1+\sum_{i=1}^{n-1}A_i(b_i-b_{i+1})\\
\end{aligned}
$$
等于右式。**这里我们默认 $A_0=0$ 了**。

## 3. 题解

$$
Q(n)=\sum_{i=1}^nQ(P(i))
$$

诱人的是 $P(i)$ 取值连续，我们想要将其用 $Q(P(i))-Q(P(i-1))$ 的线性组合表示 $Q(n)$。

令 $f(x)=1$，则
$$
Q(n)=\sum_{i=1}^nf(i)Q(P(i))
$$


令 $F(n)=\sum_{i=1}^nf(i)$。应用分部求和法，无论是上面的哪一种形式，总之我们有

$$
Q(n)=\sum_{i=1}^nf(i)Q(P(i))=F(n)Q(P(n))-\sum_{i=1}^{n-1}F(i)(Q(P(i+1))-Q(P(i)))
$$
取出右边和式：注意 $F(0)$ 被我们默认为 $0$。
$$
\begin{aligned}
&\sum_{i=1}^{n-1}F(i)(Q(P(i+1))-Q(P(i)))\\
=&\sum_{i=1}^{n}F(i-1)(Q(P(i))-Q(P(i-1)))\\
=&\sum_{i=1}^{P(n)}F(i(i+1)/2-1)(Q(i)-Q(i-1))\\
=&\sum_{i=1}^{P(n)}F(i(i+1)/2-1)Q(P(i))\\
\end{aligned}
$$
最后一步由定义得到。所以记 $g(f, n)=\sum_{i=1}^nf(i)Q(P(i))$ 则
$$
g(f, n)=F(n)Q(P(n))-g(h, P(n))=F(n)g(I, P(n))-g(h, P(n))
$$
其中 $F(n)=\sum_{i=1}^nf(i)$、$h(i)=F(i(i+1)/2-1)$，总是可以算的。$Q(n)=g(I, n)$。

因为 $P(n)=O(\sqrt n)$，大概迭代三次 $P(P(P(n)))\leq 10^6$ 就直接计算了。注意 $g$ 一开始的定义，暴力不要求错东西。

## 4. 代码实现

实现比较困难，第一是高精度，这个直接使用板子（强烈推荐 [封装 BigInt 的伟大计划 - 洛谷专栏](https://www.luogu.com/article/if2kg5xm)、[剪贴板直达](https://www.luogu.com/paste/47gujppj)）就算了，真考了就写 python。

第二是 $F(n)=\sum_{i=1}^nf(i)$、$h(i)=F(i(i+1)/2-1)$ 这个鬼畜的东西，又有前缀和又有二次函数复合。正常做法是拉格朗日插值。但是我们有高精度，控制不好的话会有麻烦。

考虑使用 python3 的 sympy 库（正赛没有这个库可以用），具体用法你自己问 AI，反正能写出来个这东西：

```python
#!/bin/env python3
import sympy

x = sympy.Symbol('x')
i = sympy.Symbol('i')

def presum(f):
    return sympy.Sum(f.subs(x, i), (i, 1, x)).doit().simplify()

def uplevel(F):
    return F.subs(x, x * (x + 1) / 2 - 1).simplify()
```

$presum(f)$ 就是 $f\to F$，$uplevel(F)$ 就是 $F\to h$ 的计算。大概意思就是，这个 `Subs` 函数就是函数复合，`f.subs(x, i)` 将 $f(x)$ 换成 $f(i)$，`F.subs(x, x * (x + 1) / 2 - 1)` 就是 $f(x)$ 变成 $f(x(x+1)/2-1)$。然后 `Sum` 就是求和，看格式，然后 `simplify`就是化简（但实际上简单不了多少，也可以换成 `expand` 或者 `factor`）。然后就可以 `print` 出来：

```python
def trans(F):
    return presum(uplevel(F))

def trans2(f):
    return uplevel(presum(f))

f = x # 大 F
⁦print(f)
print(trans(f))
print(trans(trans(f)))
print(trans(trans(trans(f))))
# print(trans(trans(trans(trans(f)))))
f = x - x + 1 # 小 f，注意可能有一点神经，需要指定一下未知的元
print(f)
print(trans2(f))
print(trans2(trans2(f)))
print(trans2(trans2(trans2(f))))
# print(trans2(trans2(trans2(trans2(f)))))
```

然后要粘贴到 C++ 里面，需要把 python 的 `**` 幂运算去掉。`mint` 是我们的高精度类型。

```python
def custom_print(expr):
    s = str(expr.factor()) # 推荐输出前 factor（因式分解）
    for i in range(100, 1, -1):
        s = s.replace(f'x**{i}', '*'.join(['x'] * i))
    print(f'+[](mint x) -> mint {{ return {s}; }},')
```

将 `print` 全部换成 `custom_print`。

输出如下：

```cpp
+[](mint x) -> mint { return x; },
+[](mint x) -> mint { return x*(x - 1)*(x + 4)/6; },
+[](mint x) -> mint { return x*(x - 1)*(5*x*x*x*x*x + 40*x*x*x*x + 131*x*x*x + 236*x*x - 44*x - 1024)/1680; },
+[](mint x) -> mint { return x*(x - 1)*(x + 4)*(429*x*x*x*x*x*x*x*x*x*x*x*x + 5148*x*x*x*x*x*x*x*x*x*x*x + 26697*x*x*x*x*x*x*x*x*x*x + 75636*x*x*x*x*x*x*x*x*x + 122031*x*x*x*x*x*x*x*x + 89604*x*x*x*x*x*x*x - 37373*x*x*x*x*x*x - 205140*x*x*x*x*x - 1140248*x*x*x*x - 4246656*x*x*x - 8781968*x*x - 10100160*x + 41554944)/276756480; },
+[](mint x) -> mint { return 1; },
+[](mint x) -> mint { return (x - 1)*(x + 2)/2; },
+[](mint x) -> mint { return (x - 1)*(x + 2)*(x*x + x - 4)*(x*x + x + 6)/48; },
+[](mint x) -> mint { return (x - 1)*(x + 2)*(x*x + x - 4)*(5*x*x*x*x*x*x*x*x*x*x + 25*x*x*x*x*x*x*x*x*x + 80*x*x*x*x*x*x*x*x + 170*x*x*x*x*x*x*x + 289*x*x*x*x*x*x + 377*x*x*x*x*x + 546*x*x*x*x + 612*x*x*x - 3864*x*x - 4128*x - 26880)/215040; },
```

`+[](mint x) -> mint { return 1; }` 是一个转型为函数指针的 Lambda 对象，其类型为 `mint (*)(mint)`。于是就可以将这 $8$ 个函数存到代码里。

其它的代码不需要我教你怎么写了吧！

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef local
#define debug(...) fprintf(stderr, ##__va_args__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
// 省略一个高精度板子，见上
using mint = BigInt<9>;
mint operator*(int x, mint y) { return y * x; }
using LL = long long;
using FuncPtr = mint (*)(mint);
const FuncPtr F[] = {/*{{{*/
    /* 四个函数 */
}; /*}}}*/
const FuncPtr f[] = {/*{{{*/
    /* 四个函数 */
};/*}}}*/
constexpr int L = 1e6, N = L + 10;
mint q[N], preq[4][N];
int p[N];
mint P(mint n) {
  mint l = 0, r = mint(1) << (mint::n * 16 - 2), ans = 0;
  while (l <= r) {
    mint mid = (l + r) >> 1;
    if ((mid * (mid + 1) >> 1) <= n)
      ans = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  return ans;
}
mint ns[110];
mint g(int c, int d) {
  if (ns[c] <= L) return preq[d][(int)ns[c]];
  return F[d](ns[c]) * g(c + 1, 0) - g(c + 1, d + 1);
}
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  q[1] = 1, p[1] = 1;
  int lst = 1;
  for (int i = 2; i <= L; i++) {
    if ((lst + 1) * (lst + 2) / 2 == i) ++lst;
    p[i] = lst;
    q[i] = q[i - 1] + q[lst];
  }
  for (int j = 0; j < 4; j++) {
    for (int i = 1; i <= L; i++) {
      preq[j][i] = preq[j][i - 1] + f[j](i) * q[p[i]];
    }
  }
  int t;
  cin >> t;
  while (t--) {
    cin >> ns[0];
    for (int i = 1; i <= 4; i++) ns[i] = P(ns[i - 1]);
    cout << g(0, 0) << endl;
  }
  return 0;
}
```
因为剪贴板已经无法查看，我在这里贴一下高精度模板，出处见上：
```cpp
template <size_t N>
class BigInt {/*{{{*/
private :
	uint32_t bit[N];
	uint32_t& operator [](size_t index) { return bit[index]; }
	const uint32_t& operator [](size_t index)const { return bit[index]; }
public :
	static constexpr size_t n = N;
	static bool sign(const BigInt &x) { return x[n - 1] & (1 << 31); }
	static BigInt StringToBigInt(const string &str) {
		BigInt res;
		size_t len = str.size(), start = 0;
		bool sgn = (str[0] == '-'); if(sgn) start = 1;
		for(size_t i = start; i < len; i++) {
			uint32_t carry = str[i] ^ 48;
			for(size_t j = 0; j < n; j++) {
				uint64_t temp = static_cast<uint64_t>(res[j]) * 10 + carry;
				res[j] = static_cast<uint32_t>(temp);
				carry = temp >> 32;
			}
		}
		return sgn ? -res : res;
	}
	static string BigIntToString(BigInt num) {
		bool sgn = sign(num);
		if(sgn) num = -num;
		vector<uint8_t> s;
		for(int i = n - 1; i >= 0; i--) {
			size_t m = s.size();
			uint32_t carry = num[i];
			for(size_t j = 0; j < m; j++) {
				uint64_t temp = (static_cast<uint64_t>(s[j]) << 32) + carry;
				s[j] = temp % 10;
				carry = temp / 10;
			}
			while(carry) s.emplace_back(carry % 10), carry /= 10;
		}
		string res;
	    for(auto it = s.rbegin(); it != s.rend(); ++it) res += (*it) ^ 48;
	    if(res.empty()) res = "0";
		return sgn ? '-' + res : res;
	}
  explicit operator int() const {
    auto str = BigIntToString(*this);
    int x;
    sscanf(str.c_str(), "%d", &x);
    return x;
  }
	BigInt() { memset(bit, 0, n * sizeof(uint32_t)); }
	BigInt operator ~() const { BigInt res; for(size_t i = 0; i < n; i++) res[i] = ~bit[i]; return res; }
	BigInt operator -() const {
		BigInt res = ~(*this);
		uint32_t carry = 1;
		for(size_t i = 0; i < n; i++) {
			uint64_t temp = static_cast<uint64_t>(res[i]) + carry;
			res[i] = static_cast<uint32_t>(temp);
			carry = temp >> 32;
		}
		return res;
	}
	BigInt(int x) {
		bool sgn = (x < 0); if(sgn) x = -x;
		bit[0] = x; memset(bit + 1, 0, (n - 1) * sizeof(uint32_t));
		if(sgn) *this = -(*this);
	}
	BigInt(long long x) {
		bool sgn = (x < 0); if(sgn) x = -x;
		bit[0] = x & 0xFFFFFFFF, bit[1] = x >> 32; memset(bit + 2, 0, (n - 2) * sizeof(uint32_t));
		if(sgn) *this = -(*this);
	}
	BigInt(const string &str) { *this = StringToBigInt(str); }
	friend istream& operator >> (istream &in, BigInt &x) { string str; in >> str; x = StringToBigInt(str); return in; }
	friend ostream& operator << (ostream &out, const BigInt &x) { out << BigIntToString(x); return out; }
	BigInt& operator &= (const BigInt &o) { for (size_t i = 0; i < n; i++) bit[i] &= o[i]; return *this; }
	BigInt operator & (const BigInt &o) const { BigInt res = *this; return res &= o; }
	BigInt& operator |= (const BigInt &o) { for (size_t i = 0; i < n; i++) bit[i] |= o[i]; return *this; }
	BigInt operator | (const BigInt &o) const { BigInt res = *this; return res |= o; }
	BigInt& operator ^= (const BigInt &o) { for (size_t i = 0; i < n; i++) bit[i] ^= o[i]; return *this; }
	BigInt operator ^ (const BigInt &o) const { BigInt res = *this; return res ^= o; }
	BigInt& operator <<= (size_t shift) {
	    if(shift == 0) return *this;
	    size_t wordShift = shift >> 5, bitShift = shift & 31;
	    if(wordShift >= n) { memset(bit, 0, sizeof(bit)); return *this; }
	    if(wordShift > 0) {
	        for(size_t i = n - 1; i >= wordShift; --i)
	            bit[i] = bit[i - wordShift];
	        memset(bit, 0, wordShift * sizeof(uint32_t));
	    }
	    if(bitShift > 0) {
	        for(size_t i = n - 1; i > 0; --i)
	            bit[i] = (bit[i] << bitShift) | (bit[i - 1] >> (32 - bitShift));
	        bit[0] <<= bitShift;
	    }
	    return *this;
	}
    BigInt& operator >>= (size_t shift) {
        if(shift == 0) return *this;
        size_t wordShift = shift >> 5, bitShift = shift & 31;
        if(wordShift >= n) { memset(bit, 0, sizeof(bit)); return *this; }
        if(wordShift > 0) {
            for(size_t i = 0; i < n - wordShift; ++i)
                bit[i] = bit[i + wordShift];
            memset(bit + n - wordShift, 0, wordShift * sizeof(uint32_t));
        }
        if(bitShift > 0) {
            for(size_t i = 0; i < n - 1; ++i)
                bit[i] = (bit[i] >> bitShift) | (bit[i + 1] << (32 - bitShift));
            bit[n - 1] >>= bitShift;
        }
        return *this;
    }
	BigInt operator << (const size_t &o) const { BigInt res = *this; return res <<= o; }
	BigInt operator >> (const size_t &o) const { BigInt res = *this; return res >>= o; }
	bool operator == (const BigInt &o) const {
		for(size_t i = 0; i < n; i++)
			if(bit[i] != o[i]) return false;
		return true;
	}
	bool operator != (const BigInt &o) const { return !(*this == o); }
    bool operator < (const BigInt &o) const {
		bool signT = sign(*this), signO = sign(o);
		if(signT != signO) return signT;
		for(int i = n - 1; i >= 0; i--)
			if(bit[i] != o[i]) return signT ? bit[i] > o[i] : bit[i] < o[i];
		return false;
	}
	bool operator > (const BigInt &o) const { return o < *this; }
	bool operator <= (const BigInt &o) const { return !(o < *this); }
	bool operator >= (const BigInt &o) const { return !(*this < o); }

	BigInt& operator += (const BigInt &o) {
		uint32_t carry = 0;
		for(size_t i = 0; i < n; i++) {
			uint64_t temp = static_cast<uint64_t>(bit[i]) + o[i] + carry;
			bit[i] = static_cast<uint32_t>(temp);
			carry = temp >> 32;
		}
		return *this;
	}
	BigInt operator + (const BigInt &o) const { BigInt res = *this; return res += o; }
	BigInt& operator -= (const BigInt &o) { *this += -o; return *this; }
	BigInt operator - (const BigInt &o) const { BigInt res = *this; return res += -o; }
    BigInt& operator ++ () { return *this += 1; }
	BigInt operator ++ (int) { BigInt res = *this; *this += 1; return res; }
	BigInt& operator -- () { return *this += -1; }
	BigInt operator -- (int) { BigInt res = *this; *this += -1; return res; }
	BigInt& operator *= (const BigInt &o) {
	    BigInt res;
	    for(size_t i = 0; i < n; i++) {
	        uint32_t carry = 0;
	        for(size_t j = 0; j + i < n; j++) {
	            uint64_t temp = static_cast<uint64_t>(bit[i]) * o[j] + res[i + j] + carry;
	            res[i + j] = static_cast<uint32_t>(temp);
	            carry = temp >> 32;
	        }
	    }
	    return *this = res;
	}
	BigInt operator * (const BigInt &o) const { BigInt res = *this; return res *= o; }
    BigInt& operator *= (const uint32_t &o) {
	    uint32_t carry = 0;
	    for(size_t i = 0; i < n; i++) {
	        uint64_t temp = static_cast<uint64_t>(bit[i]) * o + carry;
	        bit[i] = static_cast<uint32_t>(temp);
	        carry = temp >> 32;
	    }
	    return *this;
	}
	BigInt operator * (const uint32_t &o) const { BigInt res = *this; return res *= o; }
	BigInt& operator *= (int o) {
	    bool sgn = (o < 0); if(sgn) o = -o;
	    *this *= static_cast<uint32_t>(o);
	    if(sgn) *this = -(*this);
	    return *this;
	}
	BigInt operator * (const int &o) const { BigInt res = *this; return res *= o; }
    BigInt& operator /= (const BigInt &o) {
//		if(o == BigInt(0)) assert(false);
        bool sgn = sign(*this) ^ sign(o);
        if(sign(*this)) *this = -(*this);
        BigInt divisor = sign(o) ? -o : o;
        BigInt quotient, remainder;
        for(int i = (n << 5) - 1; i >= 0; --i) {
            remainder <<= 1;
            remainder[0] |= (bit[i >> 5] >> (i & 31)) & 1;
            if (remainder >= divisor) {
                remainder -= divisor;
                quotient[i >> 5] |= (1u << (i & 31));
            }
        }
        return *this = sgn ? -quotient : quotient;
    }
    BigInt operator / (const BigInt &o) const { BigInt res = *this; return res /= o; }
	BigInt& operator /= (const uint32_t &o) {
		bool sgn = sign(*this); if(sgn) *this = -(*this);
	    uint64_t carry = 0;
	    for(int i = n - 1; i >= 0; i--) {
	        uint64_t current = (carry << 32) | bit[i];
	        bit[i] = static_cast<uint32_t>(current / o);
	        carry = current % o;
	    }
	    if(sgn) *this = -(*this);
	    return *this;
	}
	BigInt operator / (const uint32_t &o) const { BigInt res = *this; return res /= o; }
	BigInt& operator /= (int o) {
	    bool sgn = (o < 0); if(sgn) o = -o;
	    *this /= static_cast<uint32_t>(o);
	    if(sgn) *this = -(*this);
	    return *this;
	}
	BigInt operator / (const int &o) const { BigInt res = *this; return res /= o; }
    BigInt& operator %= (const BigInt &o) {
//		if(o == BigInt(0)) assert(false);
        bool sgn = sign(*this);
        if(sign(*this)) *this = -(*this);
        BigInt divisor = sign(o) ? -o : o;
        BigInt quotient, remainder;
        for(int i = (n << 5) - 1; i >= 0; --i) {
            remainder <<= 1;
            remainder[0] |= (bit[i >> 5] >> (i & 31)) & 1;
            if (remainder >= divisor) remainder -= divisor;
        }
        return *this = sgn ? -remainder : remainder;
    }
    BigInt operator % (const BigInt &o) const { BigInt res = *this; return res %= o; }
	BigInt& operator %= (const uint32_t &o) {
		bool sgn = sign(*this); if(sgn) *this = -(*this);
	    uint32_t carry = 0;
	    for(int i = n - 1; i >= 0; i--) {
	        uint64_t current = (static_cast<uint64_t>(carry) << 32) | bit[i];
	        bit[i] = 0;
	        carry = current % o;
	    }
	    bit[0] = carry;
	    if(sgn) *this = -(*this);
	    return *this;
	}
	BigInt operator % (const uint32_t &o) const { BigInt res = *this; return res %= o; }
	BigInt& operator %= (int o) {
	    if (o < 0) o = -o;
	    *this %= static_cast<uint32_t>(o);
	    return *this;
	}
	BigInt operator % (const int &o) const { BigInt res = *this; return res %= o; }
};/*}}}*/
```

---

## 作者：RainWetPeopleStart (赞：0)

某机构摸你赛 T3。

正解用了一种叫“分部求和法”的东西。

设 $P(0)=0,Q(0)=0$。

首先，由递推式，得 $Q(n)=\sum\limits_{i=1}^nQ(P(i))$。

性质：对于大部分的 $i$，$P(i)=P(i+1)$。

然后，考虑往这个性质上靠，设计多项式 $f_0(x)=1$，$F_0(x)=\sum\limits_{i=1}^xf_0(i)$。

有 $\sum\limits_{i=1}^nQ(P(i))=\sum\limits_{i=1}^nf_0(i)Q(P(i))$。

然后就可以推式子了。

$\begin{aligned}\sum\limits_{i=1}^nQ(P(i)) &=\sum\limits_{i=1}^nf_0(i)Q(P(i))
\\&=\sum\limits_{i=1}^n(F_0(i)-F_0(i-1))Q(P(i))
\\&=\sum\limits_{i=1}^n(F_0(i)-F_0(i-1))Q(P(i))+F_0(0)Q(P(0))
\\&=F_0(n)Q(P(n))+\sum\limits_{i=0}^{n-1}F_0(i)(Q(P(i))-Q(P(i+1)))
\\&=F_0(n)Q(P(n))+\sum\limits_{i=0}^{n-1}F_0(i)(Q(P(i+1))-Q(P(i)))
\\&=F_0(n)Q(P(n))+\sum\limits_{i=1}^{n}F_0(i-1)(Q(P(i))-Q(P(i-1)))
\end{aligned}$

此时，对于绝大部分的情况，$Q(P(i))-Q(P(i-1))=0$。

考虑枚举使 $Q(P(i))-Q(P(i-1))\neq 0$ 的 $i$。

发现这样的 $i$ 可以被表示为 $\frac{P(i)P(i+1)}{2}$ 的形式。

继续化式子：
$\begin{aligned}
F_0(n)Q(P(n))+\sum\limits_{i=1}^{n}F_0(i-1)(Q(P(i))-Q(P(i-1)))&=F_0(n)Q(P(n))+\sum\limits_{i=1}^{P(n)}F_0(\frac{i(i+1)}{2}-1)(Q(i)-Q(i-1))
\\&=F_0(n)Q(P(n))+\sum\limits_{i=1}^{P(n)}F_0(\frac{i(i+1)}{2}-1)Q(P(i))
\end{aligned}$

记 $f_1(x)=F_0(\frac{x(x+1)}{2}-1)$，原问题就被转化为了规模更小的，类似的子问题。

类似的，设 $f_i(x)=F_{i-1}(\frac{x(x+1)}{2}-1)$，$F_i(x)=\sum\limits_{i=1}^nf_i(x)$。

这样就可以化简这些子问题。

记 $cal(k,n)$ 表示 $\sum\limits_{i=1}^nf_k(i)Q(P(i))$。

有 $cal(k,n)=F_k(n)Q(P(n))-\sum\limits_{i=1}^{P(n)}f_{k+1}(i)Q(P(i))$。

得 $cal(k,n)=F_k(n)cal(0,P(n))-cal(k+1,P(n))$。

这样发现递归 4 层后 $n\le 800$。(这不是准确的上界)

对 $n\le 800$ 预处理即可。

记递归最大层数为 $D$，多项式最大长度为 $K$。

可得 $D=4$ 时 $K=31$。

可以预处理点值，使用拉格朗日插值计算多项式的值，因为点值连续，可以 $O(K)$ 算。

忽略高精度复杂度，单次查询可以 $O(2^DK)$。

实现细节：

直接拉格朗日插值可能需要写高精度除高精度，常数大，可以先处理模意义下的答案，在 CRT 合并，这样只需一次高精度取模。

[代码](https://www.luogu.com.cn/paste/sap7b97x)写了 6kb 左右。是目前（2024.12.28）除 Python 外的洛谷最短解。

---

