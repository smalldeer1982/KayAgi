# 「RiOI-03」A Journey to the Moonlight（加强版）

## 题目背景

本题相较于 [P9919](/problem/P9919) 扩大了数据范围。

## 题目描述

对于一个右部点为 $m$ 个的二分图 $G$，定义它的权值 $w(G)$ 如下：

- 选择一种匹配方案，标记第一个已匹配的右部点。如果不存在这样的点，那么标记第一个未匹配的右部点。
- 每次随机选择一个 $1,2,\cdots,m$ 的排列，当未匹配的右部点与被标记的点 **按标号顺序作为一个子段出现在排列中时** 停止操作。
- $w(G)$ 为在所有匹配方案中操作次数期望的 **最小值**。

将这个二分图 $G$ 定义为 **$k$ 合法** 的，当且仅当：

- 所有左部点的度数在 $k\sim \color{red}2$ 之间。
- 没有任意两个左部点，与其相邻的点组成的集合相同。

定义 $f(k,x)$ 为所有右部点 $x$ 个，左部点不进行区分的 $k$ 合法二分图 $G$ 的 $w(G)$ 之和。

给定 $n,k,a_{0\sim n}$，求 $\sum\limits^n_ia_if(k,i) \bmod998244353$。

## 说明/提示

约定一个左部点连接了编号为 $x,y$ 的右部点表示为 $(x,y)$。

#### 【样例 1 解释】

对于 $n=0,1$，答案显然为 $1,2$。

对于 $n=2$，可能的二分图为（用每个左部点的邻接点组成的元组表示）：

$()$

$(1),(2),(1,2)$

$\{(1),(2)\},\{(1,2),(2)\},\{(1,2),(1)\},\{(1,2),(1),(2)\}$

期望相同的二分图被分为一组。答案为 $\dfrac21+\dfrac21\times3+\dfrac22\times4=12$，输出 $1\times1+1\times2+1\times12=15$。

#### 【样例 2 解释】

对于 $n=0,1,2$，答案为 $1,1,4$。

对于 $n=3$，可能的二分图为（用每个左部点的邻接点组成的元组表示）：

$()$

$(1,2),(1,3),(2,3)$

$\{(1,2),(1,3)\},\{(1,2),(2,3)\},\{(1,3),(2,3)\}$

$\{(1,2),(2,3),(1,3)\}$

答案为 $\dfrac61+\dfrac61\times3+\dfrac62\times3+\dfrac66=34$。

#### 【数据范围】

对于 $100\%$ 的数据，$0\le n\le10^5$，$1\le k\le2$，$0\le a_i<998244353$。

## 样例 #1

### 输入

```
2 1
1 1 1```

### 输出

```
15```

## 样例 #2

### 输入

```
3 2
1 1 1 1```

### 输出

```
40```

## 样例 #3

### 输入

```
12 1
1 1 4 5 1 4 1 9 1 9 8 1 0```

### 输出

```
721168027```

# 题解

## 作者：Register_int (赞：27)

upd on 2024.7.31：做法太唐，重写。

根据 [简单版](//www.luogu.com.cn/problem/p9919) 的柿子，我们要计算下面这个东西：

$$\forall 0\le i\le n,[x^i]G(F+1)^i$$

先 $F\gets F+1$。考虑引入第二元 $y$ 用于区分不同的 $i$。我们只需要求出：

$$
\begin{aligned}
&[x^0]\sum_iy^iGF^ix^{-i}\\
\overset{\operatorname{rev}}{=}&[x^n]G\sum y^iF^{n-i}x^i\\
=&[x^n]GF^n\sum y^i(xF^{-1})^i\\
=&[x^n]\frac{GF^n}{1-yxF^{-1}}\\
\end{aligned}
$$

直接 bostan-mori 计算，时间复杂度 $O(n\log^2 n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 998244353;

using namespace polynomial; // By R_i.

typedef vector<poly<int>> polyv;

inline 
polyv operator * (const polyv &f, const polyv &g) {
	int n = f.size(), m = g.size(), x = f[0].size(), y = g[0].size();
	poly<int> a(n * (x + y - 1)), b(m * (x + y - 1));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < x; j++) a[i * (x + y - 1) + j] = f[i][j];
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < y; j++) b[i * (x + y - 1) + j] = g[i][j];
	}
	a *= b; polyv res(n + m - 1, poly<int>(x + y - 1));
	for (int i = 0; i < n + m - 1; i++) {
		for (int j = 0; j < x + y - 1; j++) res[i][j] = a[i * (x + y - 1) + j];
	}
	return res;
}

poly<int> bostan_mori(int n, polyv f, polyv g) {
	if (!n) return f[0] * inv(g[0]);
	if (n + 1 < f.size()) f.resize(n + 1);
	if (n + 1 < g.size()) g.resize(n + 1);
	polyv h = g;
	for (int i = 1; i < h.size(); i += 2) h[i] = -h[i];
	f = f * h, g = g * h; polyv a, b;
	for(int i = n & 1; i < f.size(); i += 2) a.push_back(f[i]);
	for(int i = 0; i < g.size(); i += 2) b.push_back(g[i]);
	return bostan_mori(n >> 1, a, b);
}

const int MAXN = 1e5 + 10;

int fac[MAXN], ifac[MAXN], tk[MAXN], p2[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = (ll)ifac[i] * i % mod;
	tk[1] = 1;
	for (int i = 2; i <= n; i++) tk[i] = qpow(i, i - 2);
	*p2 = 1;
	for (int i = 1; i <= n; i++) p2[i] = (p2[i - 1] << 1) % mod;
}

int n, k, ans, t = 1, a[MAXN];

poly<int> f, g; polyv p, q;

int main() {
	scanf("%d%d", &n, &k), ++n, init(n), f.resize(n), g.resize(n);
	for (int i = 0; i < n; i++) g[i] = (ll)t * ifac[i] % mod, t = (ll)t * p2[i + 2 - k] % mod;
	for (int i = 0; i < n; i++) f[i] = (ll)tk[i] * ifac[i] % mod;
	g *= inv(exp(f)), g.resize(n), f[0]++;
	g = g * pow(f, n - 1), f = inv(f) >> 1;
	for (int i = 0; i < n; i++) {
		p.push_back(vector<int>({ g[i], 0 }));
		q.push_back(vector<int>({ !i, mod - f[i] }));
	}
	g = bostan_mori(n - 1, p, q), g.resize(n), g.reverse();
	for (int i = 0; i < n; i++) g[i] = (ll)g[i] * fac[i] % mod;
	for (int i = 0; i < n; i++) scanf("%d", &a[i]), ans = (ans + (ll)a[i] * g[i] % mod) % mod;
	printf("%lld", ans);
}
```

---

