# [ICPC 2018 WF] Gem Island

## 题目描述

宝石岛是位于太平洋中部的一个小岛。直到最近，它还被认为是地球上最贫穷但也是最和平的地方之一。如今，它既不贫穷也不和平。发生了什么？

不久前的一个晴朗的早晨，宝石岛的所有居民都醒来时发现了一个惊喜。那天早上，他们每个人手中突然多了一颗闪闪发光的宝石。这些宝石在一夜之间神奇地出现了。这引起了极大的欢呼——每个人突然变得富有，他们终于可以买到他们梦寐以求的一切，他们岛的名字现在也更有意义了。

第二天早上，其中一位居民醒来时又发现了一个惊喜——她的宝石神奇地分裂成了两颗！接下来的每个晚上，岛上的一颗宝石（显然是从岛上的所有宝石中均匀随机选择的）都会分裂成两颗。

过了一段时间，宝石岛的居民拥有的宝石数量差异很大。有些人有很多，而许多人只有很少。为什么有些居民拥有的宝石比其他人多？他们是作弊了吗？他们只是幸运吗？还是有其他原因？

岛上的长老们请求你的帮助。他们希望你能确定宝石分布的不均衡是否可以用纯粹的偶然性来解释。如果是这样的话，这将大大减少岛上的紧张局势。

岛上有 $n$ 位居民。你需要确定经过 $d$ 个夜晚宝石分裂后的宝石分布。特别地，你感兴趣的是拥有最多宝石的 $r$ 个人所持有的宝石总数的期望值。更正式地说，假设经过 $d$ 个夜晚后，$n$ 位居民持有的宝石数量按非递增顺序排列为 $a_{1} \ge a_{2} \ge \ldots \ge a_{n}$。那么 $a_{1} + \cdots + a_{r}$ 的期望值是多少？

## 说明/提示

时间限制：3 秒，内存限制：1024 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 3 1
```

### 输出

```
3.5
```

## 样例 #2

### 输入

```
3 3 2
```

### 输出

```
4.9
```

## 样例 #3

### 输入

```
5 10 3
```

### 输出

```
12.2567433
```

# 题解

## 作者：CYJian (赞：30)

## 题目大意

- 有 $n$ 个人，初始时每个人手上有一颗宝石。
- 在 $d$ 天内，每天会等概率随机一颗宝石，将其分裂为两块宝石。
- 求 $d$ 天后，宝石数前 $r$ 多的人手上宝石数的期望，要求误差不超过 $10^{-6}$。
- $1 \leq n, d \leq 500$，$1 \leq r \leq n$。

## 题目解法

直接冲上去 `dp` 怎么看都不是很好做，考虑挖掘一点性质。

先看看对于一种最终状态 $a_1, a_2, \ldots, a_n$，其发生的方案数，我们可以分成两个部分：

第一步是将 $d$ 天分给 $n$ 个人，钦点这 $d$ 天是谁手上的宝石数增加了：

$$
\prod_{i=1}^{n}\binom{d-\sum_{j=1}^{i-1}(a_j-1)}{a_i-1}=\frac{d!}{\prod_{i=1}^{n}(a_i-1)!}
$$

第二步是对于每一天，计算当天被钦定的人手上宝石数增加的方案数；事实上，在一个人手上的宝石第 $i$ 次增加 $1$ 的时候，这时候发生这种情况的方案数就一定是 $i$ 种。则将 $n$ 个人的方案数都乘起来，则可以认为是：

$$
\prod_{i=1}^{n}(a_i-1)!
$$

将两个部分乘起来，则我们可以得到一个令人兴奋的结论：对于任何一种最终状态，它发生的方案数都是 $d!$。这也就意味着，所有的最终状态发生的概率都是相等的！

那么我们就可以直接 `dp` 所有方案数以及这些方案的前 $r$ 大的 $a_i$ 的和就行了。

考虑一种经典的“搭楼梯”的 `dp` 方法：

我们维护类似这样一个“楼梯”状的东西：

```
***
******
******
********
********
********
**********
**********
```

考虑设 $f_{i,j}$ 表示当前最高的“楼梯”有 $i$ 列，“楼梯”里头 `*` 的总数为 $j$ 的方案数。上面这个东西就是 $f_{3,59}$ 的一种方案。

转移很简单，考虑在最高层加入一行，枚举这行里头有 $k$ 个 `*`，然后从现有的 $j$ 列里头选 $k$ 列放到最左边，然后在这 $k$ 行上面各加上一个 `*` 就是一种转移了。比如对上面的 $f_{3,59}$，枚举 $k=2$ 的时候可以转移到 $f_{2,61}$，其转移系数为 $\binom{3}{2}$。转移之后的形态可以这么表示：


```
**          <--- 新增的行
***
******
******
********
********
********
**********
**********
```

将这个东西放到这个题中，我们可以将宝石对应成 `*`，每一列对应一个人就行了。

然后考虑计算所有方案的前 $r$ 大的 $a_i$ 的和。转化成上面的东西就变成了前 $r$ 列的 `*` 的和。事实上也很简单，由于我们每次加入一行的那些列，一定就是前 $k$ 大的列，而且每列都只加入了一个 `*`，所以我们可以直接计算贡献。具体来说，我们类比 $f_{i,j}$ 设 $g_{i,j}$ 为当前维护前 $i$ 大，一共有 $j$ 个宝石的所有方案的前 $r$ 大的数的和。那么转移就可以写成：

$$
g_{i,j}=\sum_{k=i}^{\min(n,i)}(g_{k,j-i}+\min(i, r) \times f_{k,j-i})\times \binom{k}{i}
$$

最后答案也很显然，就是

$$\frac{\sum_{i=1}^{n}g_{i,d}}{\sum_{i=1}^{n}f_{i,d}}$$

了。

由于此题比较神必，所以全上 `double` 就行了。

`Code`：(实际写的转移可能和上面叙述的有一点点小区别，本质一样）

```cpp
typedef long long ll;
typedef double db;

db f[1010][1010];
db g[1010][1010];
db C[1010][1010];

int main() {
	int n = ri, d = ri, r = ri;

	C[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}

	f[0][n] = 1;
	for(int i = 0; i < d; i++)
		for(int j = 1; j <= n; j++)
			for(int k = 1; k <= j; k++) {
				f[i + k][k] += f[i][j] * C[j][k];
				g[i + k][k] += (g[i][j] + min(r, k) * f[i][j]) * C[j][k];
			}

	db G = 0, F = 0;
	for(int i = 1; i <= n; i++)
		G += g[d][i], F += f[d][i];

	printf("%.8lf\n", G / F + r);

	return 0;
}
```

---

## 作者：Alex_Wei (赞：21)

[P6944 [ICPC2018 WF] Gem Island](https://www.luogu.com.cn/problem/P6944)

我们抽象出一些信息描述最终方案，发现可设 $c_i$ 表示第 $i$ 个人手上有 $c_i$ 颗宝石。

第 $i$ 个人手上的第 $j$ 颗宝石由前 $j - 1$ 个宝石之一分裂得到，方案数 $(c_i - 1)!$。安排每天分裂哪个人手上的宝石，方案数 $\dbinom {d} {c_1 - 1, c_2 - 1, \cdots, c_n - 1}$。相乘得 $d!$，这说明所有可能的 $c$ 出现的概率相同，因此答案可写为
$$
\dfrac {\sum\limits_{c} F(c) d!} {n ^ {\overline{d}}}
$$
其中 $F(c)$ 表示 $c_i$ 前 $r$ 大的数的和。将 $d!$ 除到分母上，我们需要计算 $\sum F(c)$。

因为要求数值前 $r$ 大且 $\sum c_i = n + d$，所以考虑经典拆分数 DP。将所有 $c_i$ 减去 $1$，答案加 $r$，限制变为 $\sum c_i = d$。

设 $f_{S, i} / g_{S, i}$ 表示总和为 $S$，当前最大值有 $i$ 个的方案数和总贡献。枚举 $i'\leq i$，则 $f_{i, S} \dbinom {i} {i'} \to f_{i', S + i'}$，$(g_{i, S} + f_{i, S} \min(r, i'))\dbinom {i} {i'} \to g_{i', S + i'}$。时间复杂度 $\mathcal{O}(n ^ 3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define TIME 1e3 * clock() / CLOCKS_PER_SEC

constexpr int N = 500 + 5;
int n, d, r;
double f[N][N], g[N][N], C[N][N];

int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> d >> r;
  for(int i = 0; i <= n; i++)
    for(int j = 0; j <= i; j++)
      C[i][j] = j ? C[i - 1][j - 1] + C[i - 1][j] : 1;
  f[0][n] = 1, g[0][n] = r;
  for(int S = 0; S < d; S++)
    for(int i = 1; i <= n; i++)
      for(int _i = 1; _i <= i && S + _i <= d; _i++) {
        double c = C[i][_i];
        f[S + _i][_i] += f[S][i] * c;
        g[S + _i][_i] += (g[S][i] + f[S][i] * min(r, _i)) * c;
      }
  double F = 0, G = 0;
  for(int i = 1; i <= n; i++) F += f[d][i], G += g[d][i];
  printf("%.9lf\n", G / F);
  return cerr << "Time: " << TIME << " ms\n", 0;
}
```

[加强版](https://loj.ac/p/3405)。

将数 $v$ 的贡献拆成 $\sum\limits_{j = 1} ^ {d} [v\geq j]$，枚举 $j$，则每个方案对答案的贡献为 $\min(i, r)$，其中 $i$ 是不小于 $j$ 的数的个数。考虑算出恰有 $i$ 个不小于 $j$ 的数的方案数 $f(i, j)$。根据上述分析，$\sum\limits_{j = 1} ^ d\sum\limits_{i = 0} ^ n f(i, j) \min(i, r)$ 即为所求。

钦定有 $i$ 个数不小于 $j$，方案数为 $g(i, j) = \dbinom {n} {i} \dbinom {d - ij + n - 1} {n - 1}$。根据 $g(i, j) = \sum\limits_{k = i} ^ n \dbinom {k} {i} f(k, j)$，二项式反演得到 $f(i, j) = \sum\limits_{k = i} ^ n (-1) ^ {k - i} \dbinom {k} {i} g(k, j)$。

推式子：
$$
\begin{aligned}
& \sum\limits_{j = 1} ^ d\sum\limits_{i = 0} ^ n \min(i, r) \sum\limits_{k = i} ^ n (-1) ^ {k - i} \dbinom {k} {i} g(k, j) \\
& \sum\limits_{i = 1} ^ n \min(i, r) \sum\limits_{k = i} ^ n (-1) ^ {k - i} \dbinom k i \sum\limits_{j = 1} ^ d g(k, j) \\
\end{aligned}
$$
对每个 $k$ 预处理 $h(k) = \sum\limits_{j = 1} ^ d g(k, j)$ 即可做到 $\mathcal{O}(nm)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define TIME 1e3 * clock() / CLOCKS_PER_SEC

constexpr int N = 1.5e7 + 5;
constexpr int mod = 998244353;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
inline int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}
int fc[N], ifc[N];
int bin(int n, int m) {
  if(n < 0 || m > n) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
int n, d, r, ans, g[N];

int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> d >> r;
  for(int i = fc[0] = 1; i < N; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[N - 1] = ksm(fc[N - 1], mod - 2);
  for(int i = N - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
  for(int k = 1; k <= n; k++)
    for(int j = 1; j * k <= d; j++)
      add(g[k], 1ll * bin(n, k) * bin(d - k * j + n - 1, n - 1) % mod);
  for(int i = 1; i <= n; i++) {
    int s = 0;
    for(int k = i; k <= n; k++) {
      int coef = 1ll * bin(k, i) * g[k] % mod;
      if(k - i & 1) coef = mod - coef;
      add(s, coef);
    }
    add(ans, 1ll * min(i, r) * s % mod);
  }
  cout << (1ll * ans * ksm(bin(n + d - 1, d), mod - 2) + r) % mod << "\n";
  return cerr << "Time: " << TIME << " ms\n", 0;
}
```

$h(k)$ 里面的组合数看起来不太能拆，所以考虑直接枚举 $k$：
$$
\begin{aligned}
& \sum\limits_{i = 1} ^ n \min(i, r) \sum\limits_{k = i} ^ n (-1) ^ {k - i} \dbinom k i h(k) \\
& \sum\limits_{k = 1} ^ n (-1) ^ k h(k) \sum\limits_{i = 1} ^ k (-1) ^ {i} \dbinom k i \min(i, r) \\
\end{aligned}
$$
设 $z(k) = \dbinom {d - k + n - 1} {n - 1}$，则 $h(k) = \sum z(kj)$，直接狄利克雷后缀和即可。问题转化为快速计算
$$
\begin{aligned}
& \sum\limits_{i = 1} ^ k (-1) ^ {i} \dbinom k i \min(i, r) \\
& \sum\limits_{i = 1} ^ k (-1) ^ {i} \dbinom k i \sum\limits_{j = 1} ^ {\min(i, r)} 1 \\
& \sum\limits_{j = 1} ^ r \sum\limits_{i = j} ^ k (-1) ^ i \dbinom k i
\end{aligned}
$$
后者是经典的杨辉三角第 $k$ 行带有交错正负号的部分和，推导方法为上指标反转，斜求和，上指标反转：
$$
\begin{aligned}
& \sum\limits_{j = 1} ^ r \sum\limits_{i = j} ^ k (-1) ^ i \dbinom k i \\
& \sum\limits_{j = 1} ^ r \sum\limits_{i = j} ^ k (-1) ^ {2i} \dbinom {i - k - 1} i \\
& \sum\limits_{j = 1} ^ r \left(\dbinom {(k + 1) - k - 1} k - \dbinom {j - k - 1} {j - 1} \right) \\
\end{aligned}
$$
因为 $k > 0$，所以 $\dbinom 0 k = 0$，得
$$
\begin{aligned}
& \sum\limits_{j = 1} ^ r -\dbinom {j - k - 1} {j - 1} \\
& \sum\limits_{j = 1} ^ r -(-1) ^ {j - 1} \dbinom {j - 1 - (j - k - 1) - 1} {j - 1} \\
& \sum\limits_{j = 1} ^ r (-1) ^ j \dbinom {k - 1} {j - 1} \\
\end{aligned}
$$
继续正负交错部分和，得
$$
\begin{aligned}
& \sum\limits_{j = 1} ^ r (-1) ^ j \dbinom {k - 1} {j - 1} \\
& -\sum\limits_{j = 0} ^ {r - 1} (-1) ^ j \dbinom {k - 1} j \\
& -\sum\limits_{j = 0} ^ {r - 1} (-1) ^ {2j} \dbinom {j - k} j \\
& -\dbinom {r - k} {r - 1} \\
& -(-1) ^ {r - 1} \dbinom {k - 2} {r - 1} \\
& (-1) ^ r \dbinom {k - 2} {r - 1} \\
\end{aligned}
$$
时间复杂度 $\mathcal{O}(n + d\log\log d)$。

直接按 $i\leq r$ 和 $i > r$ 分类讨论，做杨辉三角一行正负交错部分和也可得到 $\mathcal{O}(1)$ 计算的式子。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define TIME 1e3 * clock() / CLOCKS_PER_SEC

constexpr int N = 1.5e7 + 5;
constexpr int mod = 998244353;
void add(int &x, int y) {x += y, x >= mod && (x -= mod);}
inline int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}
int fc[N << 1], ifc[N << 1];
int bin(int n, int m) {
  if(n < 0 || m > n) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
int n, d, r, ans, z[N];
int cnt, pr[N / 12];
bool vis[N];
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> d >> r;
  for(int i = fc[0] = 1; i <= n + d; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[n + d] = ksm(fc[n + d], mod - 2);
  for(int i = n + d - 1; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
  for(int i = 1; i <= d; i++) z[i] = bin(d - i + n - 1, n - 1);
  for(int i = 2; i <= d; i++) {
    if(!vis[i]) pr[++cnt] = i;
    for(int j = 1; j <= cnt && i * pr[j] <= d; j++) {
      vis[i * pr[j]] = 1;
      if(i % pr[j] == 0) break;
    }
  }
  for(int i = 1; i <= cnt; i++)
    for(int j = d / pr[i]; j; j--)
      add(z[j], z[j * pr[i]]);
  for(int k = 1; k <= n; k++) {
    int h = 1ll * z[k] * bin(n, k) % mod, s = 0;
    if(k == 1) s = mod - 1;
    else s = r & 1 ? mod - bin(k - 2, r - 1) : bin(k - 2, r - 1);
    if(k & 1) s = mod - s;
    add(ans, 1ll * h * s % mod);
  }
  cout << (1ll * ans * ksm(bin(n + d - 1, d), mod - 2) + r) % mod << "\n";
  return cerr << "Time: " << TIME << " ms\n", 0;
}
```

---

## 作者：bai_tang (赞：12)

只要有信念，就一定能成功！

### 题意
有 $n$ 种球各一枚，有 $m$ 次操作在已有的球中等概率选择一个将其复制一个同色的放回，问前 $k$ 多种球的数量之和的期望，$k\le n$，$n,m\le 500$。

### 分析
因为白糖~~还是只小喵喵~~不会任何高级的东西，本着相信出题人善良的原则我们还是拿出在[这题](https://www.luogu.com.cn/blog/bai-tang/shuo-lie-ji-wang)使用过的操作序列模型，看看有什么东西可以搞的。

举个例子，$n=3,m=3,k=2$，对于操作序列 $223$，它的贡献就是 $5$，而概率即为 $\frac 13\times \frac 24\times \frac 15$。

对于贡献，就是前 $k$ 大之和，没啥好讲的。对于概率，你发现分母部分就是 $n^{\overline{m}}=(n+m-1)!/(n-1)!$，而分子部分就是最终结果的阶乘相乘。

形式化地说，对于 $n+m$ 的一个 $n$ 有序拆分 $a_1,a_2,a_3,\cdots,a_n$（它代表经过 $n$ 次操作后的结果），它的贡献显然是它前 $k$ 大的数值，而它出现的概率即为（后面乘上的是可重集排列）：
$$\frac{\prod_{i=1}^n(a_i-1)!}{n^{\overline{m}}}\cdot \frac{m!}{\prod_{i=1}^n(a_i-1)!}=\frac{m!}{n^{\overline{m}}}$$
枚举有序拆分，我们就有了 $2^n$ 量级的做法，不过显然你发现有序拆分与前 $k$ 大不太兼容，再乘上一个可重集排列，可以转化为无序拆分，我们就有了亚指数级别的做法，[代码](https://www.luogu.com.cn/paste/t0fod44q)。

形式化而言，对于 $n+m$ 的一个 $n$ 无序拆分 $a_1,a_2,a_3,\cdots ,a_n$（非严格降序排列），设 $b_1,b_2,\cdots ,b_{m+1}$ 其中 $b_x$ 为满足 $a_i=x$ 的 $i$ 的个数，那么它对答案的贡献即为：
$$\bigg(\sum_{i=1}^ka_i\bigg)\cdot \frac{n!}{\prod_{i=1}^{m+1}b_i!}\cdot \frac{m!}{n^{\overline{m}}}$$

把 $n!\cdot m!/n^{\overline{m}}$ 这个固定系数提出来，我们要处理的贡献分外简单，不写个 DP 都是对这个美好性质的极大侮辱啊！

设 $f(a,b,c)$ 为枚举 $a$ 到 $m+1$ 的数，已经选出了其中的 $b$ 个和为 $c$ 的数的贡献系数，那么就有：
$$\frac 1{i!}f(a+1,b,c)\to f(a,b+i,c+a\cdot i)$$

接下来是一个比较有趣的操作：我们在 $b<k$ 并且 $b+i\ge k$ 的时候，啪的一下把 $\sum_{i=1}^ka_i$ 的贡献乘上去，也就是这个的时候，我们有特殊的转移式：
$$\frac {c+(k-b)\cdot a}{i!}f(a+1,b,c)\to f(a,b+i,c+a\cdot i)$$
[代码](https://www.luogu.com.cn/paste/7l2poql1)，稍微卡卡常容易做到的复杂度为 $O(nm^2\log m)$。

### [加强](https://www.luogu.com.cn/problem/P6944)
此题相比原来的题目有加强如下：
- 需要用浮点数输出，故对常数和精度要求较高，原来的做法需要卡常，[代码](https://www.luogu.com.cn/paste/m8zvpwdd)，应该是最短且最慢的实现了。

学无止境，我们希望能得到一个更好的做法。

### 分析
之前的结论依旧是好用的，但是我们的 DP 方法真的无法更优吗？

在这里，我们尝试采用另一种方法来实现前 $k$ 大的查询，叫做填充法，我们把大于等于 $1$ 的所有东西先填充上一层 $1$，大于等于 $2$ 的所有东西先填充上一层 $2$，大于等于 $3$ 的所有东西填充上一层 $3$……以此类推：

形式化而言，设 $f(i,j,x)$ 表示前 $i$ 大刚好是 $i$ 个 $j$（第 $i+1$ 大小于 $j$），还剩下 $x$ 次机会分裂宝石，对答案的贡献（其中 $g$ 函数代表对应的方案数，感谢[Missa](https://www.luogu.com.cn/user/443664)提醒），那么即有：
$$C(i,a)\cdot (f(i,j,x)+g(i,j,x)\cdot \min(a,k))\to f(a,j+1,x-a)$$
$$C(i,a)\cdot g(i,j,x)\to f(a,j+1,x-a)$$
然后容易发现 $j$ 无关紧要，所以设 $f(i,j)$ 表示前 $i$ 大恰好相同，还剩下 $j$ 次机会分裂宝石的贡献。
$$C(i,a)\cdot(f(i,j)+g(i,j)\cdot \min(a,k))\to f(a,j-a)$$
$$C(i,a)\cdot g(i,j)\to f(a,j-a)$$
[代码](https://www.luogu.com.cn/paste/0v3citup)，复杂度 $O(nm\min(n,m))$。

### [二次加强](https://loj.ac/p/3405)
此题目相比原题加强如下。
- 将 $n,m,k$ 放到了 $1.5\times 10^7$，做法必须接近线性。
- 答案对 $998244353$ 取模，这严格来说并不算加强，下面会分析取模的必要性。

### 分析
由之前的 DP 给我们的启示：我们没必要把数当作一个整体，很多时候，这类数拆开来算会有不错的效果。

设 $f(i,j)$ 为 $n+m$ 的 $n$ 有序拆分恰好有 $i$ 个位置大于 $j$ 的方案数，那么容易发现答案即为：
$$\sum_{i,j}f(i,j)\cdot \min(i,k)$$
考虑设 $g(i,j)$ 为“钦定 $i$ 个位置大于 $j$ 的方案数”，显然：
$$g(i,j)=C(n,i)C(n+m-i\cdot j-1,n-1)$$
根据一位不知姓名的二项式反演，我们有：
$$f(i,j)=\sum_{z=i}(-1)^{z-i}C(z,i)g(z,j)$$
你发现答案的贡献系数只和 $i$ 有关，因此把 $j$ 打包起来。
$$\sum_{j}f(i,j)=\sum_{x=i}(-1)^{z-i}C(z,i)\sum_{j}g(z,j)$$
我们轻轻松松就做到了 $O(nm)$ 的复杂度，当然，由于利用了二项式反演，只能做到这样，不过它确实有很大的优化空间，[代码](https://www.luogu.com.cn/paste/cqjci7ze)。
- 另外，该做法有一个极其重大的缺陷，就是它几乎只有理论意义！由于反演的特殊性，误差在 $n,m,k\ge -\log\epsilon$ 的时候就会变得十分明显，因此，二次加强版的做法不能仅仅通过去掉取模的方式通过加强版的题目，而如果我们想要得到稍微有意义的结果，也绝不能仅凭数学推导就主观臆断去实现这个做法。

不过，抛开精度问题，这倒也不失为一种优秀的做法，那么这个做法可以优化吗。

### 优化
考虑我们本质上在求什么，求下面这坨恶心的式子（由于式子有点恶心，我把它立起来先）：
$$\sum_{i=1}^n\min(i,k)\sum_{j=i}^n(-1)^{j-i}\binom ji\sum_{z\ge 0}\binom nj\binom{n+m-j\cdot z-1}{n-1}$$
$$\sum_{i=1}^n\min(i,k)\sum_{j=i}^n(-1)^{j-i}\binom ji\binom nj\sum_{j|z}\binom{n+m-z-1}{n-1}$$
$$\sum_{i=1}^n\binom ni\cdot \bigg(\sum_{i|z}\binom{n+m-z-1}{n-1}\bigg)\cdot \bigg(\sum_{j=0}^i(-1)^{i-j}\binom ij\cdot \min(j,k)\bigg)$$
让我们思考如下函数：
$$f(n)=\sum_{i=0}^n(-1)^{n-i}\binom ni\min(i,k)$$
它实际上是我们时间复杂度瓶颈的罪魁祸首，如果我们能够让其能够快速求解，那么问题即迎刃而解。
- 但是鉴于作者不会推组合式子，就先采用一种奇妙的打表方法（如果有证明者请联系作者，我们会注明并感谢），[代码](https://www.luogu.com.cn/paste/wt8w03r1)，作者最后得到的结论是：
$$f(n)=(-1)^{n-k}\binom{n-2}{k-1}$$
- 感谢[奆佬](https://www.luogu.com.cn/user/90893)在[这篇](https://www.luogu.com.cn/discuss/516133)提供的证明！
- 欸，实践中发现一个特殊的边界情况：$f(1)=[k\ge 1]$，请注意。
最后使用迪利克雷后缀和，我们就可以在 $O(m\log\log m)$ 的时间内求出答案了，[代码](https://www.luogu.com.cn/paste/31arbj9z)。

---

## 作者：Starlight237 (赞：7)

> 将 $n+d$ 有序拆分为 $n$ 个正整数，求这些正整数中最大的 $r$ 个数之和的期望值。

稍微转化一下，改为将 $d$ 有序拆分成 $n$ 个非负整数，然后最后答案加上 $r$ 即可。

定义 $f_{i,j}$ 表示 $j$ 有序拆分成 $i$ 个非负整数的方案数，$g_{i,j}$ 表示所有 $f_{i,j}$ 种情况对应的前 $r$ 大数之和的总和。

$f_{i,j}$ 是非常经典的整数划分问题，考虑划分出来的至少有几个是正整数（大于等于 1），然后先给这些数各分一个 1，有转移 $f_{i,j}=\sum_{1\le k\le\min(i,j)}\binom{i}{k} f_{k,j-k}$。

$g_{i,j}$ 当然也可以对应地转移：$g_{i,j}=\sum_{1\le k\le\min(i,j)}(\binom{i}{k} g_{k,j-k}+\min(k,r)f_{k,j-k})$。$\min(k,r)f_{k,j-k}$ 即「先给这些数各分一个 1」所产生的贡献。

最后答案就是 $f_{n,d}/g_{n,d}+r$。需要使用 `double` 或 `long double` 进行计算（不知道 `double` 会不会被卡精度，我是使用 `long double` 的）。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace io {
#define BUFS 100000
	char in[BUFS], *p = in, *pp = in;
#define gc (p == pp && (pp = (p = in) + fread(in, 1, BUFS, stdin), p == pp) ? EOF : *p++)
	inline int read() {
		int x = 0; char ch, f = 0;
		while (!isdigit(ch = gc)) f |= ch == '-';
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc;
		return f ? -x : x;
	}
}
#define rd io :: read
int n, d, r;
long double f[510][510], g[510][510], C[510][510];
int main() {
	n = rd(), d = rd(), r = rd();
	C[0][0] = 1;
	for (int i = 1; i <= n; ++i) f[i][0] = C[i][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= i; ++j)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= d; ++j)
			for (int k = 0, l = min(i, j); k <= l; ++k)
				f[i][j] += C[i][k] * f[k][j - k];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= d; ++j)
			for (int k = 0, l = min(i, j); k <= l; ++k)
				g[i][j] += C[i][k] * (g[k][j - k] + min(k, r) * f[k][j - k]);
	printf("%lf", (double)(g[n][d] / f[n][d] + r));
	return 0;
}
```

---

## 作者：EuphoricStar (赞：4)

组合计数神题。下文的 $m$ 指原题面中的 $d$，$k$ 指原题面中的 $r$。

考虑最后每个人得到的宝石数量的序列 $s_1, s_2, \ldots, s_n$，考虑这种方案的出现次数。首先要在 $m$ 次操作中分别选 $s_i - 1$ 次给第 $i$ 个人，方案数为 $\frac{m!}{\prod\limits_{i = 1}^n (s_i - 1)!}$；然后对于一个人，当它的宝石数为 $k$ 时，选择一颗变成两颗的方案数为 $k$，所以每个人还有 $(s_i - 1)!$ 种方案的贡献，乘起来发现 $(s_i - 1)!$ 被约掉了，也就是说**对于任意一种 $s_1, s_2, \ldots, s_n$，它们出现概率均等。**

于是题目变成了，一个序列的价值为前 $k$ 大元素之和，求所有满足 $\sum\limits_{i = 1}^n s_i = m$ 的序列 $s$ 的价值之和（最后要除个方案数 $\binom{n + m - 1}{n - 1}$ 和加上原有的 $k$ 个）。

考虑对于一个固定的序列 $s$，我们以这样的方式计算它的价值：$\sum\limits_{a > 0} \min(k, \sum\limits_{i = 1}^n [s_i \ge a])$。可以想象成一个柱状图，就是把原来的从左到右算面积变成从上到下算面积。这样可以方便许多。

那么设 $f_{a, i}$ 为对于一个序列 $s$，**恰好**有 $i$ 个元素的值 $\ge a$ 的这样的序列个数；考虑二项式反演，设 $g_{a, i}$ 为对于一个序列 $s$，**钦定**有 $i$ 个元素的值 $\ge a$ 的这样的序列个数。$g_{a, i}$ 是好求的，相当于选 $i$ 个位置让他们 $\ge a$，就变成了一个和为 $m - ai$ 的插板，那么：

$$g_{a, i} = \binom{n}{i} \binom{m + n - ai - 1}{n - 1}$$

且：

$$g_{a, i} = \sum\limits_{j = i}^n \binom{j}{i} f_{a, j}$$

反演得：

$$f_{a, i} = \sum\limits_{j = i}^n (-1)^{j - i} \binom{j}{i} g_{a, j}$$

答案即为：

$$\sum\limits_{a = 1}^m \sum\limits_{i = 1}^n f_{a, i} \times \min(i, k)$$

这样已经可以做 $O(n^2m)$ 了，但是还不够。考虑把 $f$ 扔掉，直接计算每个 $g_{a, i}$ 对答案的贡献，那么答案也可以表示成：

$$\sum\limits_{a = 1}^m \sum\limits_{i = 1}^n g_{a, i} \sum\limits_{j = 1}^i (-1)^{i - j} \binom{i}{j} \min(j, k)$$

后面那一坨求和式子看上去不能考虑组合意义，那么可以尝试**递推**。设 $v_{n, k} = \sum\limits_{i = 1}^n (-1)^{n - i} \binom{n}{i} \min(i, k)$，那么根据 $\binom{n}{m} = \binom{n - 1}{m} + \binom{n - 1}{m - 1}$ 可以裂项后尝试递推：

$$\begin{aligned}v_{n, k} & = \sum\limits_{i = 1}^n (-1)^{n - i} \binom{n}{i} \min(i, k) \\ & = \sum\limits_{i = 1}^n (-1)^{n - i} \binom{n - 1}{i} \min(i, k) + \sum\limits_{i = 1}^n (-1)^{n - i} \binom{n - 1}{i - 1} \min(i, k) \\ & = -\sum\limits_{i = 1}^{n - 1} (-1)^{n - 1 - i} \binom{n - 1}{i} \min(i, k) + \sum\limits_{i = 1}^n (-1)^{n - 1 - (i - 1)} \binom{n - 1}{i - 1} (\min(i - 1, k - 1) + 1) \\ & = -\sum\limits_{i = 1}^{n - 1} (-1)^{n - 1 - i} \binom{n - 1}{i} \min(i, k) + \sum\limits_{i = 1}^{n - 1} (-1)^{n - 1 - i} \binom{n - 1}{i} \min(i, k - 1) + \sum\limits_{i = 1}^{n - 1} (-1)^{n - 1 - i} \binom{n - 1}{i} \\ & = -v_{n - 1, k} + v_{n - 1, k - 1} + (-1 + 1)^{n - 1} - 1 \\ & = -v_{n - 1, k} + v_{n - 1, k - 1} + [n = 1] \end{aligned}$$

那么我们得到了 $v_{n, k} = -v_{n - 1, k} + v_{n - 1, k - 1}$，边界 $\forall k > 0, v_{1, k} = 1$。考虑组合意义，可以看作是，$n - 1$ 次选 $i$ 次让 $k - 1$，$n - 1 - i$ 次让 $k$ 不 $-1$ 并变号，那么有 $v_{n, k} = \sum\limits_{i = 0}^{k - 1} (-1)^{n - 1 - i} \binom{n - 1}{i}$。再尝试递推：

$$\begin{aligned} v_{n, k} & = \sum\limits_{i = 0}^{k - 1} (-1)^{n - 1 - i} \binom{n - 1}{i} \\ & = \sum\limits_{i = 0}^{k - 1} (-1)^{n - 1 - i} \binom{n - 2}{i} + \sum\limits_{i = 0}^{k - 1} (-1)^{n - 1 - i} \binom{n - 2}{i - 1} \\ & = -\sum\limits_{i = 0}^{k - 1} (-1)^{n - i} \binom{n - 2}{i} + \sum\limits_{i = 0}^{k - 2} (-1)^{n - i} \binom{n - 2}{i} \\ & = (-1)^{n - k} \binom{n - 2}{k - 1} \end{aligned}$$

最后一步是运用了正负项抵消。那么我们有 $\forall k > 0, v_{1, k} = 1, \forall n > 1, v_{n, k} = (-1)^{n - k} \binom{n - 2}{k - 1}$。

再来考虑答案的式子：

$$\sum\limits_{a = 1}^m \sum\limits_{i = 1}^n g_{a, i} v_{i, k}$$

分别代入 $g_{a, i}, v_{i, k}$ 的式子得：

$$n \sum\limits_{a = 1}^m \binom{m + n - a - 1}{n - 1} + \sum\limits_{a = 1}^m \sum\limits_{i = 2}^n \binom{n}{i} \binom{m + n - ai - 1}{n - 1} (-1)^{i - k} \binom{i - 2}{k - 1}$$

关注后半部分：

$$\sum\limits_{a = 1}^m \sum\limits_{i = 2}^n \binom{n}{i} \binom{m + n - ai - 1}{n - 1} (-1)^{i - k} \binom{i - 2}{k - 1}$$

注意到 $ai \le m$，所以暴力算的复杂度就是 $O(m \log m)$ 的。但是还能更优。

$$\begin{aligned} ans & = \sum\limits_{a = 1}^m \sum\limits_{i = 2}^n \binom{n}{i} \binom{m + n - ai - 1}{n - 1} (-1)^{i - k} \binom{i - 2}{k - 1} \\ & = \sum\limits_{t = 2}^m \binom{m + n - t - 1}{n - 1} \sum\limits_{i \mid t} \binom{n}{i} (-1)^{i - k} \binom{i - 2}{k - 1} \\ & = \sum\limits_{i = 2}^n \binom{n}{i} (-1)^{i - k} \binom{i - 2}{k - 1} \sum\limits_{i \mid t} \binom{m + n - t - 1}{n - 1} \\ & = \sum\limits_{i = 2}^n \binom{n}{i} (-1)^{i - k} \binom{i - 2}{k - 1} h_i \end{aligned}$$

其中 $h_i = \sum\limits_{i \mid t} \binom{m + n - t - 1}{n - 1}$，可以高维前缀和预处理出。

至此，我们终于以 $O(n + m \log \log m)$ 的复杂度完成了这题。

[code](https://loj.ac/s/1946472)

---

## 作者：LiuIR (赞：1)

# [ICPC 2018 WF] Gem Island 题解

## 题目大意

有 $n$ 个人，每个人初始时有 $1$ 颗宝石。每天会随机选择一颗宝石，并将其分裂为两颗。问 $m$ 天后宝石数最多的那 $r$ 个人的宝石数之和的期望值。

$n,m,r\le500$。

## 题目解法

倘若直接按操作过程 DP 不是很好下手，于是就先分析终止状态的一些性质。

考虑记一个状态为序列 $a$，其中 $a_i$ 表示 $m$ 天后第 $i$ 个人的宝石数，然后计算能到达这一状态的操作方案数：

+ 每个人都在操作序列中出现了 $a_i-1$ 次，所以这部分的方案数是 $\binom{m}{a_1-1,a_2-1,\cdots,a_n-1}=\frac{m!}{\prod_{i=1}^n(a_i-1)!}$。

+ 若当前第 $i$ 个人有 $j$ 个宝石，那么他的其中一颗宝石分裂的方案数为 $j$。所以每个人第 $j$ 次出现在操作序列中所对应的分裂宝石的方案数为 $j$。换句话说，所有人分裂宝石的总方案数为 $\prod_{i=1}^n(a_i-1)!$。

令人惊喜的是，两者之积恰好是 $m!$。这表明每种终止状态是等概率出现的，方案数都是 $m!$。

于是只需求出每种终止状态的价值和以及方案数，把两者一除就可以得到期望。

考虑设 $f_{i,s}/g_{i,s}$ 表示 $\sum a_p=s$ 且 $a_p$ 的最大值有 $i$ 个的价值和/方案数，转移枚举 $j$ 表示给最大值中的 $j$ 个数加一，易得转移方程为

$$
(f_{i,s}+g_{i,s}\times\min(j,r))\times\binom{i}{j}\to f_{j,s+j}\\
g_{i,s}\times\binom{i}{j}\to g_{j,s+j}
$$

这样 DP 的原理就是按最终的 $a_p$ 从小到大确定，容易证明这样是不重不漏的。

时间复杂度 $O(n^2m)$。

```c++
cin >> n >> m >> k;
for (int i = 0; i <= n; i++)
{
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++)
        c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
}
f[0][n] = k;
g[0][n] = 1;
for (int s = 0; s < m; s++)
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i && s + j <= m; j++)
        {
            f[s + j][j] += (f[s][i] + g[s][i] * min(k, j)) * c[i][j];
            g[s + j][j] += g[s][i] * c[i][j];
        }
for (int i = 1; i <= n; i++)
    ans1 += f[m][i], ans2 += g[m][i];
ans = ans1 / ans2;
cout << ans;
return 0;
```

[加强版](https://loj.ac/p/3405)，$n,m,r\le1.5\times10^7$

考虑将一个数 $v$ 的贡献拆成 $\sum_{j=1}^m[v\ge j]$。那么若记 $i$ 表示 $\ge j$ 的数的个数，那么对答案的贡献为 $\min(i,r)$。据此，设 $f_{i,j}$ 表示恰有 $i$ 个数 $\ge j$ 的方案数，那么答案为 $\sum_{i=0}^n\sum_{j=1}^mf_{i,j}\min(i,r)$。

恰好就考虑二项式反演，设 $g_{i,j}$ 表示钦定有 $i$ 个数 $\ge j$ 的方案数，那么显然有

$$
f_{i,j}=\sum_{k=i}^n(-1)^{k-i}\binom{k}{i}g_{k,j}
$$

而 $g_{i,j}=\binom{n}{i}\times\binom{m-ij+n-1}{n-1}$，后面的组合数是插板法。

所以推一波式子可以得到

$$
\begin{aligned}
ans&=\sum_{i=0}^n\sum_{j=1}^mf_{i,j}\min(i,r)\\
&=\sum_{i=0}^n\min(i,r)\sum_{j=1}^m\sum_{k=i}^n(-1)^{k-i}\binom{k}{i}g_{k,j}\\
&=\sum_{i=0}^n\min(i,r)\sum_{k=i}^n(-1)^{k-i}\binom{k}{i}\sum_{j=1}^mg_{k,j}\\
\end{aligned}
$$

所以只需预处理出 $s_k=\sum_{j=1}^mg_{k,j}$ 即可，这样是 $O(n(n+m))$ 的。

考虑先枚举 $k$ 得到

$$
\begin{aligned}
ans&=\sum_{k=0}^n(-1)^ks_k\sum_{i=0}^k(-1)^i\min(i,r)\binom{k}{i}\\
&=\sum_{k=0}^n(-1)^k\binom{n}{k}\left(\sum_{j=1}^m\binom{m-kj+n-1}{n-1}\right)\left(\sum_{i=0}^k(-1)^i\min(i,r)\binom{k}{i}\right)
\end{aligned}
$$

于是考虑把 $s_k$ 改为 $\sum_{j=1}^m\binom{m-kj+n-1}{n-1}$，这可以用狄利克雷后缀和求出。

于是问题转变为求出

$$
\begin{aligned}
\sum_{i=0}^k(-1)^i\min(i,r)\binom{k}{i}&=\sum_{i=0}^k(-1)^i\binom{k}{i}\sum_{j=1}^{\min(i,r)}1\\
&=\sum_{i=0}^k\sum_{j=1}^{\min(i,r)}(-1)^i\binom{k}{i}\\
&=\sum_{j=1}^r\sum_{i=j}^k(-1)^i\binom{k}{i}
\end{aligned}
$$

手模一下就可以得出最后一步。

然后再是大力推一波式子（要用到平行求和法和上指标反转）

$$
\begin{aligned}
\sum_{j=1}^r\sum_{i=j}^k(-1)^i\binom{k}{i}&=\sum_{j=1}^r\sum_{i=j}^k(-1)^{2i}\binom{i-k-1}{i}\\
&=\sum_{j=1}^r\binom{k+1-k-1}{k}-\binom{j-k-1}{j-1}\\
&=\sum_{j=1}^r-\binom{j-k-1}{j-1}\\
&=\sum_{j=1}^r(-1)^{j}\binom{k-1}{j-1}
\end{aligned}
$$

可以发现这里和上面是类似的，用同样的方式可以推导出 $(-1)^r\binom{k-2}{r-1}$。其实上面的方法叫做杨辉三角某一行带有交错正负的部分和。

然后就可以直接计算了。

```c++
int n, m, r, tot, prime[N / 5], fac[N << 1], ifac[N << 1];
ll ans, sum[N];
bool bj[N << 1];

ll C(int n, int m){return n < m || m < 0 ? 0 : 1ll * fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;}
void Init(int);

signed main()
{
    SetIO();
    cin >> n >> m >> r;
    Init(n + m);
    for (int i = 1; i <= m; i++)
        sum[i] = C(m - i + n - 1, n - 1);
    for (int i = 1; i <= tot; i++)
        for (int j = m / prime[i]; j >= 1; j--)
            sum[j] += sum[j * prime[i]];
    for (int i = 1; i <= n; i++)
    {
        sum[i] %= MOD;
        ll val = C(n, i) % MOD * sum[i] % MOD;
        if (i == 1)
            val = MOD - val;
        else if (r & 1)
            val = val * (MOD - C(i - 2, r - 1)) % MOD;
        else
            val = val * C(i - 2, r - 1) % MOD;
        if (i & 1)
            Sub(ans, val);
        else
            Add(ans, val);
    }
    cout << add(ans * Pow(C(n + m - 1, m)) % MOD, r);
    return 0;
}

void Init(int n)
{
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = 1ll * fac[i - 1] * i % MOD;
    ifac[n] = Pow(fac[n]);
    for (int i = n; i > 1; i--)
        ifac[i - 1] = 1ll * ifac[i] * i % MOD;
    prime[++tot] = 2;
    for (int i = 3; i <= n; i += 2)if (!bj[i])
    {
        prime[++tot] = i;
        for (int j = 3 * i; j <= n; j += i + i)
            bj[j] = true;
    }
}
```

---

## 作者：WTR2007 (赞：1)

## [[ICPC2018 WF] Gem Island](https://www.luogu.com.cn/problem/P6944)

算法标签：动态规划，组合数学。

### 题目描述

有 $n$ 个人，最开始每个人手中有 $1$ 颗绿宝石，每天晚上，会随机选一个绿宝石分裂为两个，求 $d$ 个晚上后绿宝石数量最多的 $r$ 个人的绿宝石数和的期望值。

数据范围：$1 \le n,d \le 500$，$1 \le r\le n$。

### 题解

观察性质，设 $a_i$ 表示第 $i$ 个人手上有 $a_i$ 颗宝石，那么对于一种最终状态 $a_1, a_2, \dots, a_n$，我们分析这种状态出现的概率，即：

$$P = \dbinom{d}{a_1 - 1, a_2 - 1, \dots, a_n - 1} \times \dfrac{\prod\limits_{i = 1}^{n}(a_i - 1)!}{n^{\overline{d}}} = \dfrac{d!}{n^{\overline{d}}}$$

容易发现这个概率与最终状态无关，即每种最终状态的**出现概率相等**。至此，问题转为对于所有长度为 $n$ 的数组 $a$，满足 $\sum a_i = n + d$，求 $\sum\limits_c F(a) \times P$，其中 $F(a)$ 表示数组 $c$ 的最大的 $r$ 个数的和。

注意到数据范围很小，考虑用动态规划解决该问题。将所有 $a_i$ 减去 $1$，那么最终答案加 $r$，限制变为 $\sum a_i = d$。

因为最大的 $r$ 个数字难以用常规的 dp 维护，因此设计 dp 状态 $f_{i,S}/g_{i,S}$ 分别表示目前的**最大值有 $i$ 个**，现在的总和为 $S$，设 $1 \le j \le i$，容易写出转移：

$$\dbinom{i}{j} \times f_{i,S} \rightarrow f_{j, S + j}$$

$$\dbinom{i}{j} \times (g_{i,S} + \min(r, j) \times f_{i,S}) \rightarrow g_{j, S + j}$$

下面笔者将对该 dp 进行详细解读。如下图所示，我们以层为阶段自下而上的转移，最大的 $r$ 个数字的贡献只需分层加入即可。我们注意到最终的答案与第几层没有关系，我们可以将 $S$ 相同的状态合并，就可以获得更优的复杂度。

![image](https://pic.imgdb.cn/item/659261fbc458853aef6175fb.png)

若我们以另一个视角看，可以看作是一个不增序列 $c_i$，满足 $\sum c_i = d$，以 $\sum c_i$ 为阶段，每次看作往序列中加入一个数进行转移，此时 $f_{i,S}/g_{i,S}$ 的设计就显得更加合理了。

最终答案即为 $\dfrac{\sum\limits_{i = 1}^n g_{i,d}}{\sum\limits_{i = 1}^n f_{i,d}} + r$，时间复杂度为 $\mathcal{O}(n^3)$。

```cpp
#include<bits/stdc++.h>
#define MULT_TEST 0
using namespace std;
typedef long double ldb;
const int N = 505;
ldb f[N][N], g[N][N], c[N][N];
inline int read() {
    int w = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        w = (w << 1) + (w << 3) + ch - 48;
        ch = getchar();
    }
    return w * f;
}
inline void Solve() {
    int n, d, r;
    n = read(); d = read(); r = read();
    f[n][0] = 1;
    for (int i = 0; i <= n; i++) 
        for (int j = 0; j <= i; j++)
            c[i][j] = j ? c[i - 1][j] + c[i - 1][j - 1] : 1;
    for (int S = 0; S < d; S++) 
        for (int i = 1; i <= n; i++) 
            for (int j = 1; j <= min(d - S, i); j++) {
                f[j][S + j] += f[i][S] * c[i][j];
                g[j][S + j] += c[i][j] * (g[i][S] + f[i][S] * min(r, j));
            }
    ldb A = 0, B = 0;
    for (int i = 0; i <= n; i++) A += g[i][d], B += f[i][d];
    printf("%.12Lf\n", A / B + r);
}
signed main() {
    int T = 1;
#if MULT_TEST
    T = read();
#endif 
    while (T--) Solve();
    return 0;
}
```

---

## 作者：Engulf (赞：0)

尽量讲详细一点。

### 寻找性质

设最后第 $i$ 个人手上有 $a_i$ 个宝石。

每天都会新增一个宝石，所以 $d$ 天后共有 $n + d$ 个宝石。


$$\sum_{i=1}^n a_i = n + d$$

这个性质的发现需要一定注意力。

对于一种最终状态 $a$，能够有多少种到达它的方案数？

分两步统计：

#### 第一步

考虑每一天选择了哪个人。第 $i$ 个人初始只有一个宝石，最后有 $a_i$ 个，而每被选择一次，宝石数增加 $1$，所以这 $d$ 天中第 $i$ 个人共被选择了 $a_i - 1$ 次。把问题抽象化：

可重集合 $S$ 中有 $n$ 种元素 $1 \sim n$，每个元素 $i$ 有 $a_{i} - 1$ 个，故 $|S| = \sum\limits_{i=1}^na_i-1 = n + d - n = d$，这 $d$ 个元素的全排列数，即 $S$ 的 **多重集的排列数** 就是答案。

选人的方案数：

$$\binom{d!}{a_1 - 1, a_2 - 1, \cdots, a_n - 1} = \dfrac{d!}{\prod\limits_{i=1}^n (a_i - 1)!}$$

#### 第二步

选了人还不够，要从这个人当前有的宝石中选择一个宝石。可以发现，某天时第 $i$ 个人有 $c$ 个宝石，那么就有 $c$ 种选法。

这 $d$ 天中第 $i$ 个人被选了 $a_i - 1$ 次，第 $1$ 次被选时他有 $1$ 个宝石，有 $1$ 种选法；第 $2$ 次被选时他有 $2$ 个宝石，有 $2$ 种选法……第 $a_i - 1$ 次被选时有 $a_i - 1$ 种选法。根据乘法原理，第 $i$ 个人选择宝石数的方案为

$$(a_i - 1)!$$

乘法原理，把每个人的都乘起来，总的选宝石的方案数为

$$\prod_{i=1}^n (a_i - 1)!$$

### 发现性质

所以，对于一种最终状态 $a$，到达它的方案数等于选人的方案乘上选宝石的方案，也就是

$$\dfrac{d!}{\prod\limits_{i=1}^n (a_i - 1)!} \times \prod_{i=1}^n (a_i - 1)! = d!$$

这说明，对于任何一种状态 $a$，到达它的方案数恒为 $d!$，这也说明了每种状态 $a$ **等概率** 出现。

既然如此，不用分别考虑每种状态出现的概率了。

### 问题求解

转化一下题意。

:::info[原题]{open}

求出所有最终状态 $a$ 的前 $r$ 大的 $a_i$ 之和的期望。

:::

:::success[转化题意]{open}

将 $n + d$ 划分为 $n$ 个正整数，求所有划分方案的前 $r$ 大的数之和的期望。
:::

设划分方案数为 $F$，由于每种划分方案等概率出现，所以都是 $\dfrac{1}{F}$。

设所有划分方案的前 $r$ 大的数之和为 $G$，答案就是 $\dfrac{G}{F}$。

$F$ 和 $G$ 可以动态规划求出，事实上正整数拆分并不好做，更常见的是非负整数拆分，类似插板法地：

$$\sum_{i=1}^n a_i = n + d$$

令 $x_i = a_i - 1 (x_i \ge 0)$，

$$\sum_{i=1}^n x_i + 1 = n + d \Rightarrow \sum_{i=1}^nx_i = d$$

$$\sum_{前 \ r \ 大的}a_i = \sum_{前 \ r \ 大的}x_i+1 = r + \sum_{前 \ r \ 大的}x_i$$

$r$ 是常数，不影响答案，提出来最后加上即可。

:::success[转化题意]{open}

将 $d$ 划分为 $n$ 个非负整数，求所有划分方案的前 $r$ 大的数之和的期望。

:::

设
- $f_{i, j}$ 表示把 $j$ 划分为 $i$ 个非负整数的方案数；
- $g_{i, j}$ 表示把 $j$ 划分为 $i$ 个非负整数的方案中前 $r$ 大的数之和。

转移时，在 $i$ 个非负整数中钦定 $k$ 个数为正整数，先各分一个 $1$，选择的方案有 $\binom{i}{k}$ 种，剩下的部分就是把 $j - k$ 划分成 $k$ 个非负整数，有转移

$$f_{i, j} = \sum_{k=0}^{\min(i, j)}\binom{i}{k}f_{k, j - k}$$

$g$ 的转移是类似的，钦定 $k$ 个数为正整数，先各分一个 $1$，选择的方案有 $\binom{i}{k}$ 种。
- 去掉我们各分的 $k$ 个 $1$，剩下部分把 $j - k$ 划分为 $k$ 个非负整数的前 $r$ 大数之和为 $g_{k, j - k}$；
- 这 $k$ 个数各加上一个 $1$，不会改变原本划分集合中数的相对大小，只需考虑新加入的 $1$ 的贡献；
- 剩下有 $f_{k,j-k}$ 种划分方式，而因为对这 $k$ 个数都加了 $1$，每种划分方式会贡献 $\min(r, k)$。

所以有转移

$$g_{i, j} = \sum_{k=0}^{\min(i, j)}\binom{i}{k}[g_{k, j - k} + f_{k, j-k} \times \min(r, k)]$$

最终的答案

$$\boxed{r + \dfrac{g_{n, d}}{f_{n, d}}}$$

这题算出来的数会巨大，`unsigned long long` 都存不下，直接用 `long double` 存。

由于 $n, d$ 同阶，$\Theta(n^3)$。

:::success[代码]

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 505;

int n, d, r;

int a[N];

long double C[N][N];
long double f[N][N], g[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> d >> r;

    C[0][0] = 1;
    for (int i = 1; i <= max(d, n); i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }

    for (int i = 0; i <= n; i++)
        f[i][0] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= d; j++)
            for (int k = 0; k <= min(i, j); k++) {
                f[i][j] += C[i][k] * f[k][j - k];
                g[i][j] += C[i][k] * (g[k][j - k] + f[k][j - k] * min(k, r));
            }

    cout << fixed << setprecision(7);

    cout << r + g[n][d] / f[n][d] << "\n";
    return 0;
}
```

:::

::::info[几组数据，调试用]
:::info[数据 1]
输入
`500 500 101`

输出
`427.6246164`
:::
:::info[数据 2]
输入
`500 123 123`

输出
`246.0000000`
:::
:::info[数据 3]
输入
`390 42 75`

输出
`117.0000000`
:::
:::info[数据 4]
输入
`10 500 7`

输出
`475.8013872`
:::
::::

---

## 作者：lhc0707 (赞：0)

对于拆分了 $d$ 次之后每个人手中的宝石数构成的数列 $\{b_n\}$，考虑计算其出现概率。列出式子，

$$P(b)=\dbinom{d}{b_1-1,b_2-1,\dots,b_n-1}\dfrac{\prod_{i=1}^n(b_i-1)!}{\prod_{i=n-d+1}^ni}$$

把 $\dbinom{d}{b_1-1,b_2-1,\dots,b_n-1}$ 展开得到 $\dfrac{d!}{\prod_{i=1}^n(b_i-1)!}$，发现与 $b_i$ 相关的项都消掉了，于是得到结论：具体的分法对于答案没有影响，我们只关心拆分了多少次。

只研究新增的 $d$ 块宝石，不妨设 $b_i$ 单调递减，画出 $i-b_i$ 图，下图中竖着表示 $b_i$，横着表示 $i$。

```
....
.....
.......
.......
........
```

考虑对人递推，发现难以转移，考虑换一个方向递推，也就是上图中从下往上递推，因为这样实际上我们不关心具体递推到了第几层，并且从下往上看 `.` 的数量也是单调的。设 $f_{i,j}$ 表示当前最顶上一层 `.` 的数量为 $i$，总数为 $j$ 的方案数，转移的时候只需要枚举下一层的数量即可，即

$$f_{i,j}=\sum_{k\geq i}f_{k,j-i}\binom{k}{i}$$

$\binom{k}{i}$ 的系数计算的是选出这 $i$ 个点所对应的数的方案数。有了这个我们就可以列出 $g_{i,j}$ 表示最顶层数量为 $i$，总数为 $j$ 的价值和，有转移

$$g_{i,j}=\sum_{k\leq i}(g_{k,j-k}+\min(r,i)f_{j-k})\binom{k}{i}$$

答案就是 $\dfrac{\sum_{i=1}^ng_{i,d}}{\sum_{i=1}^nf_{i,d}}$，时间复杂度 $O(n^2d)$。

实现的时候用刷表写的，这样可以不用倒序枚举。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, d, r;
long double f[505][505], g[505][505], C[505][505], fz, fm, ans;
signed main()
{
	scanf("%d%d%d", &n, &d, &r);
	C[0][0] = f[n][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	for (int i = 0; i < d; i++) 
		for (int j = 1; j <= n; j++)
  	 	for (int k = 1; k <= j; k++)
			 if (i + k <= d) f[k][i + k] += f[j][i] * C[j][k], g[k][i + k] += (g[j][i] + f[j][i] * min(r, k)) * C[j][k];	
	for (int i = 1; i <= n; i++) fz += g[i][d], fm += f[i][d];
	printf("%.10Lf", 1.0 * (fz / fm + r));
	return 0;
} 
```

---

## 作者：zifanwang (赞：0)

记 $a_i$ 表示 $d$ 天后第 $i$ 个人拥有的宝石数，则确定每天被选择的人的方案数为 $\frac{d!}{\prod_{i=1}^n (a_i-1)!}$，确定宝石分裂顺序的方案数为 $\prod_{i=1}^n(a_i-1)!$，可以发现得到任意一种 $a$ 序列的方案数都为 $d!$。

接下来考虑 dp，记 $g_{S,i}$ 表示当前所有数的和为 $S$，最大值有 $i$ 个的方案数，$f_{S,i}$ 表示 $r$ 个最大值的和，直接转移即可：

$$
g_{S,i}=\sum_{j=i}^n {j\choose i}g_{S-j,j}\\

f_{S,i}=\sum_{j=i}^n {j\choose i}(f_{S-j,j}+g_{S-j,j}\min(r,i))\\
$$

时间复杂度 $\mathcal O(dn^2)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
#define drep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int n,d,r;
double s1,s2,f[503][503],g[503][503],c[503][503];
signed main(){
	cin>>n>>d>>r;
	c[0][0]=1;
	rep(i,1,n){
		c[i][0]=1;
		rep(j,1,i)c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	g[0][n]=1;
	rept(s,0,d){
		drep(i,n,1){
			rep(k,1,i){
				if(s+k>d)break;
				g[s+k][k]+=g[s][i]*c[i][k];
				f[s+k][k]+=(f[s][i]+g[s][i]*min(r,k))*c[i][k];
			}
		}
	}
	rep(i,1,n)s1+=g[d][i],s2+=f[d][i];
	printf("%.10lf",s2/s1+r);
	return 0;
}
```

---

