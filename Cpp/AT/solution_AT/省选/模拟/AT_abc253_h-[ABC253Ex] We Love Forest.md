# [ABC253Ex] We Love Forest

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc253/tasks/abc253_h

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点 $ 0 $ 辺のグラフ $ G $ があります。また、長さ $ M $ の数列 $ u=(u_1,u_2,\ldots,u_M),v=(v_1,v_2,\ldots,v_M) $ が与えられます。

あなたは以下の操作を $ N-1 $ 回行います。

- $ i $ $ (1\ \leq\ i\ \leq\ M) $ を一様ランダムに選ぶ。 $ G $ に頂点 $ u_i $ と頂点 $ v_i $ を結ぶ無向辺を追加する。

すでに $ G $ に $ u_i $ と $ v_i $ を結ぶ辺があった場合も、新たに辺を追加する操作を行うことに注意してください。すなわち、操作後の $ G $ には多重辺が存在する可能性があります。

$ K=1,2,\ldots,N-1 $ について、$ K $ 回の操作後に $ G $ が森になっている確率を $ \bmod\ 998244353 $ で求めてください。

 森とは？閉路を含まない無向グラフのことを森と呼びます。森は連結でなくても構いません。

 確率 $ \bmod\ 998244353 $ の定義この問題で求める確率は必ず有理数になることが証明できます。 また、この問題の制約下では、求める確率を既約分数 $ \frac{y}{x} $ で表したときに $ x $ が $ 998244353 $ で割り切れないことが保証されます。

このとき $ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の整数 $ z $ が一意に定まります。この $ z $ を答えてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 14 $
- $ N-1\ \leq\ M\ \leq\ 500 $
- $ 1\ \leq\ u_i,v_i\ \leq\ N $
- $ u_i\neq\ v_i $
- 入力は全て整数

### Sample Explanation 1

頂点 $ u $ と頂点 $ v $ を結ぶ辺を $ (u,v) $ と書きます。 操作を $ 1 $ 回行った後の $ G $ は以下のようになります。 - $ 1/2 $ の確率で、辺 $ (1,\ 2) $ が存在する。 - $ 1/2 $ の確率で、辺 $ (2,\ 3) $ が存在する。 どちらの場合も $ G $ は森なので、 $ K=1 $ の場合の答えは $ 1 $ です。 操作を $ 2 $ 回行った後の $ G $ は以下のようになります。 - $ 1/4 $ の確率で、辺 $ (1,\ 2),(1,2) $ が存在する。 - $ 1/4 $ の確率で、辺 $ (2,\ 3),(2,3) $ が存在する。 - $ 1/2 $ の確率で、辺 $ (1,\ 2),(2,3) $ が存在する。 辺 $ (1,2),(2,3) $ が存在するときのみ $ G $ は森となっています。よって求める確率は $ 1/2 $ であり、これを $ \bmod\ 998244353 $ で表した $ 499122177 $ を出力してください。

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
1
499122177```

## 样例 #2

### 输入

```
4 5
1 2
1 2
1 4
2 3
2 4```

### 输出

```
1
758665709
918384805```

# 题解

## 作者：Aleph1022 (赞：7)

我们先来计算各个点集的导出子图的生成树个数。

考虑枚举 $k=1,\dots,n$，依次计算所有 $S \subseteq \{1,\dots,k\}$ 的答案。  
考虑每次加入一个点 $k+1$，对于 $S \subseteq \{1,\dots,k\}$，我们考虑如何在其中加入 $k+1$。  
自然只需枚举断开 $k+1$ 后会构成哪些连通块，不难发现这就是一个集合幂级数的 exp 操作。

核心代码（执行完后 $f_S$ 为 $S$ 导出子图的生成树个数，$e_u$ 为邻接矩阵，$\exp$ 表示将 $f_{2^k,\dots,2^{k+1}-1}$ 原地 $\exp$）：
```cpp
f[0] = 1;
for (int k = 0; k < lg; ++k) {
  for (int i = 0; i < (1 << k); ++i) f[i + (1 << k)] = (ll)f[i] * popcnt(e[k] & i) % mod;
  Set::exp(f + (1 << k), f + (1 << k), k);
}
```

时间复杂度由 $T(n) = T(n-1) + O(n^2 2^n)$ 得到，为 $O(n^2 2^n)$。  
从而这也叫做**逐点牛顿迭代法**。

接下来，问题为给定集合幂级数 $F(x)$，对于 $k=0,\dots,n$ 计算 $[x^U] F^k(x)$。  
我们不妨泛化为给定系数序列 $b_S$，计算序列
$$
a_k = \sum_{S\subseteq U} b_S [x^S] F^k(x)
$$

将其**转置**，即得
$$
b_S = [x^S] \sum_{k=0}^n a_k F^k(x)
$$

这就是一般的多项式复合集合幂级数问题，应用**逐点牛顿迭代法**也可以做到 $O(n^2 2^n)$。  
具体地，对于 $f, G$，令 $F = f(G)$。在两边作用 $\frac{\partial}{\partial x_n}$（相当于取 $[x_n^1]$），可得
$$
\frac{\partial}{\partial x_n} F = f'(G) \cdot \frac{\partial}{\partial x_n} G
$$

也就是说，若令 $G_k(x) = G(x) | _{x_n=x_{n-1}=\dots=x_{n-k+1}=0}$，则对于 $G_{n-k}$ 我们需要计算 $f,f',\dots,f^{(k)}$ 复合 $G_{n-k}$ 的结果。  
如此递归，复杂度为 $\sum_{k\ge 0} (n-k) \cdot k^2 2^k = O(n^2 2^n)$。  
如预处理 $G_{0,\dots,n}$ 的 FMT 数组，常数会更小。

---

## 作者：ღꦿ࿐ (赞：4)

一个不超纲的爆标做法。

容易将题目规约到对 $k=1\dots n - 1$ 条边的生成森林计数。

考虑先处理生成树计数，求出每个点集的生成树个数，首先一种很无趣的做法可以先枚举一个点集，然后直接使用 Matrix-Tree 定理，时间复杂度 $O(2^nn^3)$，有点违背本题子集幂级数的本意，我们考虑用状压 dp 的方式来做这个生成树计数。

考虑一个点集的生成树的构成一定是由其中编号最大的那个点向若干个更小的树每个连出一条边，我们 dp 的思想就是把点集 $S$ 的问题归约到这些小点集 $T$ 的问题。

因此我们考虑从小到大加入每个点，加入第 $p$ 个点时维护 $[1,p-1]$ 这些点构成集合的 $f(S)$ 表示 $S$ 的生成树个数。考虑转移到包含 $p$ 的生成树，假设 $p$ 在这个生成树中链接了 $k$ 个独立小树 $T_1\dots T_k$（$T_i$ 之间无序），则有 $\prod_{i=1}^k f (T_i)\times E(p,T_i) \to f'((\bigcup_{i=1}^k T_i) \cup u)$，其中 $E(p,T_i)$ 表示 $p$ 和 $T_i$ 之间的边数，即可以在这些边中任选一条连接。 

这个过程可以通过枚举子集在 $O(3^n)$ 时间复杂度实现，但是注意到这个形式是一个子集无序组合的形式。在这部分可以通过子集卷积的 exp 在 $O(2^n n^2)$ 的复杂度实现。（原理与子集卷积是相同的，因为 FWT 的线性性，可以直接对集合幂级数的占位位进行 exp）

我们累计需要加入 $n$ 个数，但第 $i$ 次加入的复杂度是 $O(2^i\times i^2)$ 的，所以复杂度是 $\sum _{i=1}^n O(2^i\times i^2)=O(2^n\times n ^2)$ 的，比使用 Matrix-Tree 定理优。



接下来我们知道每个点集的生成树个数了，我们考虑求生成森林计数，显然可以通过枚举森林中编号最小的点所在的生成树做到 $O(3^n\times n)$，但是依然注意到这是一个 形如若干独立（生成树）集合无序构成集族（生成森林）的问题，若我们不考虑记录边数仅求生成森林个数的话，其集合幂级数关系依然是 $G=exp (F)$，直接 exp 计算即可。 若我们要计算边数的话，可以将集合幂级数中的每项都替换成一个多项式 $\sum A_i x^i$ 表示其中是个 $A_i$ 个连通块的生成森林的方案数，然后直接进行子集 exp，多项式间的乘法就对应了连通块数的加法卷积。





复杂度 $O(2^n\times n^3)$，若对集合幂级数的占位位的卷积使用快速傅里叶变换进行计算则可以达到 $O(2^n n^2 \log n)$ 或 $O(2^n n^2)$ 的理论复杂度。

这里是 [代码](https://www.luogu.com.cn/paste/hkpye4qh)。

如果你不会 $O(2^n\times n^2)$ 的集合幂级数操作：[推荐文章](https://kewth.github.io/2020/05/06/%E9%9B%86%E5%90%88%E5%B9%82%E7%BA%A7%E6%95%B0/)。

---

---

## 作者：Register_int (赞：4)

首先选 $i$ 步的总方案数是 $m^i$，所以直接把方案数算出来，再一除就是概率了。

看到 $n\le14$ 就知道复杂度绝对带一个 $3^n$，直接子集 dp。设 $dp_{i,S}$ 表示 $i$ 步后点集 $S$ 为森林的方案数。显然可以让一个子集裂开，自己变成一棵树。再用上固定基准点的经典套路，得到转移方程：

$$dp_{i,S}=\sum_{S_1\in T\subseteq S}dp_{i-|T|+1,S/T}\times f_T$$

其中，$f_T$ 表示让点集 $T$ 成为一颗树的方案数。显然可以得知，当 $|S|=1$ 时，$f_S=1$。然而还不是很好处理，此时运用树的一个性质：断开任意一条边后树会裂开成两棵树。那么继续枚举子集裂开，得到：

$$f_S=\sum_{T\subset S}f_{S/T}\times f_T\times edge_{S/T,T}$$

然而这样是不行的，会有很多重复的情况。对于每一种方案，考虑其中的一条边，设断开该边后组成的树为 $T$ 和 $S/T$。显然，该方案会被 $T,S/T$ 与 $S/T,S/(S/T)=T$ 计算两遍，树中总计 $|S|-1$ 条边，计算次数就是 $2(|S|-1)$，除掉即可。

最后处理边数。暴力与处理绝对不行，考虑继续容斥（~~套了三层了已经~~），边数为两个子集并的内部连边数减去两个子集内部的边数，即：

$$edge_{S,T}=edge_{S\cup T}-edge_S-edge_T$$

暴力预处理每个子集的答案即可。最后，设 $V$ 为所有点组成的点集，由于没有指定加入 $i$ 条边的顺序，所以方案数为：

$$dp_{i,V}\times i!$$

概率为：

$$\dfrac{dp_{i,V}\times i!}{m^i}$$

完结撒花！

# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e3 + 10;
const int mod = 998244353;

inline 
ll inv(ll b, ll p = mod - 2) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

int n, m; ll p = 1;

int u[510], v[510], cnt[1 << 14];

ll num[1 << 14], f[1 << 14], dp[14][1 << 14], fac[14];

inline 
ll calc(int s, int t) {
	return num[s | t] - num[s] - num[t];
}

int main() {
	scanf("%d%d", &n, &m), *f = *fac = 1;
	for (int i = 1; i <= m; i++) scanf("%d%d", &u[i], &v[i]), u[i]--, v[i]--;
	for (int i = 1; i < n; i++) fac[i] = fac[i - 1] * i % mod;
	for (int s = 0; s < 1 << n; s++) {
		for (int i = 1; i <= m; i++) if (s >> u[i] & 1 && s >> v[i] & 1) num[s]++;
		if (s) cnt[s] = cnt[s ^ s & -s] + 1;
	}
	for (int s = 1; s < 1 << n; s++) {
		if (s == (s & -s)) { f[s] = 1; continue; }
		for (int t = s - 1 & s; t; t = t - 1 & s) {
			f[s] = (f[s] + f[s ^ t] * f[t] % mod * calc(s ^ t, t) % mod) % mod;
		}
		f[s] = f[s] * inv(cnt[s] - 1 << 1) % mod;
	}
	for (int i = 0; i < n; i++) {
		for (int s = 0, k, x; s < 1 << n; s++) {
			if (cnt[s] - 1 == i) dp[i][s] = f[s];
			if (!s) continue;
			x = s & -s, k = s ^ x;
			for (int t = k - 1 & k; t != k; t = t - 1 & k) {
				if (cnt[t] <= i) dp[i][s] = (dp[i][s] + dp[i - cnt[t]][s ^ t ^ x] * f[t ^ x] % mod) % mod;
			}
		}
	}
	for (int i = 1; i < n; i++) p = p * m % mod, printf("%lld\n", dp[i][(1 << n) - 1] * fac[i] % mod * inv(p) % mod);
}
```

---

## 作者：zhaoyp (赞：2)

[ABC253Ex](https://atcoder.jp/contests/abc253/tasks/abc253_h)
$\text{Difficulty : 2758}$ ：给定 $n$ 个点，$m$ 条边的无向图。每次等概率随机一条边加入初始为空的新图中。要求新图没有环，问选择了 $k$ 条边的概率？

对 $k = 1,2,\cdots,n - 1$ 输出答案，对大质数取模。

设 $f_{s,k}$ 表示选出的点集为 $s$，形成了 $k$ 个连通块的方案数（顺序不同看做不同的方案）。

记集合 $s$ 的大小为 $sz_s$。

先单独考虑 $f_{s,1}$ 的转移：

$$f_{S,1} = \dfrac{\sum\limits_{}f_{T,-1}\times f_{S-T,1}\times \dbinom{sz_S-2}{sz_T-1}\times edgenum(T,S-T)}{2}$$

其中 $S-T$ 表示 $S$ 集合中减去 $T$ 的部分，$edgenum(T,S-T)$ 表示 $T$ 与 $S-T$ 两个电集之间的边数，可以 $O(2^nn^2)$ 预处理每个点到所有点集的边数，然后每次 $O(n)$ 求得。对于合并的点集内部共有 $sz_S-2$ 条边，两边各自的顺序已经确定，所以要乘上 $\dbinom{sz_S-2}{sz_T-1}$。又因为这一步的 $S-T$ 会被之后当成 $T$ 重复计算了 $2$ 遍，所以要除 $2$。

采用枚举子集的方式转移，时间复杂度 $O(3^nn)$。

然后考虑合并若干个连通块：

$$f_{s,k} = \dfrac{\sum\limits_{}f_{T,1}\times f_{S-T,k-1}\times \dbinom{sz_S - k}{sz_T - 1}}{k}$$

转移同理，读者不妨自行推导。

最后统计答案计算即可。时间复杂度 $O(3^nn)$。

### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x)	(x & -x)
const int maxn = 20;
const int maxs = (1 << 14) + 5;
const int mod = 998244353;
const int inv2 = 998244354 / 2;
long long n,m,u,v,e[maxn][maxn],ans[maxn],f[maxs][maxn],t[maxs],vis[maxn][maxs],fac[maxn],inv[maxn];
inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return f * x;
}
long long qpow(long long a,long long b){long long ans=1;while(b){if(b&1)ans=ans*a%mod;a=a*a%mod;b>>=1;}return ans;}
inline long long calc(int n,int m){return (m > n) ? 0 : fac[n] * inv[m] % mod * inv[n - m] % mod;}
inline int numedge(int s,int t)
{
	int res = 0;
	for(int i = 1;i <= n;++i)
		if(s & (1 << (i - 1)))
			res += vis[i][t];
	return res;
}
void input()
{
	n = read(),m = read();
	for(int i = 1;i <= m;i++)
	{
		u = read(),v = read();
		if(u == v)
			continue;
		e[u][v]++,e[v][u]++;
	}
}
void prefix()
{
	for(int i = 1;i <= n;++i)
		for(int s = 1;s < (1 << n);++s)
			for(int j = 1;j <= n;++j)
				if(s & (1 << (j - 1)))
					vis[i][s] += e[i][j];
	for(int i = 1;i < (1 << n);++i)
		t[i] = t[i >> 1] + (i & 1);
	fac[0] = 1;
	for(int i = 1;i <= n;i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = qpow(fac[n],mod - 2);
	for(int i = n - 1;i >= 0;--i)
		inv[i] = inv[i + 1] * (i + 1) % mod;
}
void dp()
{
	for(int i = 1;i <= n;++i)
		f[(1 << (i - 1))][1] = 1;
	for(int s = 1;s < (1 << n);++s)
	{
		for(int T = s & (s - 1);T;T = s & (T - 1))
			if(f[T][1]&&f[s ^ T][1])
				f[s][1] += f[T][1] * f[s ^ T][1] % mod * calc(t[s] - 1 - 1,t[T] - 1) % mod * numedge(T,s ^ T) % mod,f[s][1] %= mod;
		if(s != lowbit(s))
			f[s][1] = f[s][1] * inv2 % mod;
	}
	for(int i = 1;i <= n;++i)
		f[(1 << (i - 1))][1] = 0;
	for(int k = 2;k <= n;++k)
		for(int s = 1;s < (1 << n);++s)
		{
			for(int T = s;T;T = s & (T - 1))
				if(f[T][1]&&f[s ^ T][k - 1])
				f[s][k] += f[T][1] * f[s ^ T][k - 1] % mod * calc(t[s] - k,t[T] - 1) % mod;
			f[s][k] = f[s][k] % mod * qpow(k,mod - 2) % mod;
		}
}
void solve()
{
	for(int s = 1;s < (1 << n);s++)
		for(int k = 1;k < t[s];k++)
			if(t[s] >= k)
				ans[t[s] - k] += f[s][k];
	for(int i = 1;i < n;i++)
		ans[i] %= mod;
}
void output()
{
	for(int i = 1;i <= n - 1;i++)
		printf("%lld\n",ans[i] * qpow(qpow(m,i),mod - 2) % mod);
}
int main()
{
	input();
	prefix();
	dp();
	solve();
	output();
	return 0 ;
}
/*
NOIP 2022 RP++
*/
```

---

## 作者：Tsawke (赞：1)

# [[ABC253Ex] We Love Forest](https://www.luogu.com.cn/problem/AT_abc253_h) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC253Ex)

## 题面

给定 $ n $ 个点无边的图，给定 $ m $ 条待选的无向边。每次等概率地从 $ m $ 条边中抽取一条边加入图中。 $ n - 1 $ 次询问求加 $ 1, 2, \cdots, n - 1 $ 次边后原图形成一个森林（一棵树亦为森林）的概率为多少。对 $ 998244353 $ 取模。

## Solution

考虑 FZT，即子集计数，具体可参考 [FZT - 子集计数学习笔记](http://blog.tsawke.com/?t=FZT) 或 [[ABC213G] Connectivity 2 Solution](http://blog.tsawke.com?t=ABC213G)，发现本题与 ABC213G 相似。

因为本题存在选的边数的限制，所以不难想到需要在一般 FZT 的状态中额外添加一维记录。

状态类比 ABC213G，较为显然，令 $ F(i, S) $ 表示选了 $ i $ 条边，点集状态为 $ S $ 形成的森林数。令 $ G(S) $ 表示点集状态为 $ S $ 生成树的总方案数。

首先考虑如何处理 $ G(S) $，发现这个东西就是个裸的矩阵树定理。不过也可以通过枚举子集设计转移来实现，令 $ cnt(S, T) $ 表示点集 $ S $ 和点集 $ T $ 之间的边数，方程不难想到为：
$$
G(S) = \sum_{T \subsetneq S}G(T) \times G(S \oplus T) \times cnt(T, S \oplus T)
$$
然后发现这个东西有重复，不难想到重复分为两种，一种是因为 $ T $ 和 $ S \oplus T $ 对调之后属于相同方案而被重复统计了，这个可以通过钦定一个点解决，或者在最终答案乘一个 $ \dfrac{1}{2} $ 解决。另一种是因为我们的转移，是通过将两个树形结构通过之间的边拼接在一起来实现的，而这种情况也可以认为是将一棵完整的树通过断开某一条边然后分别计算子树，这样的话对于一棵确定的树断开每条边都是等价的，所以会重复边数次，也就是答案需要乘一个 $ \dfrac{1}{\lvert S \rvert - 1} $，故可以考虑将转移改为：
$$
G(S) = \dfrac{1}{2(\lvert S \rvert - 1)} \sum_{T \subsetneq S}G(T) \times G(S \oplus T) \times cnt(T, S \oplus T)
$$
或：
$$
G(S) = \dfrac{1}{\lvert S \rvert - 1} \sum_{\operatorname{lowbit}(S) \in T \subsetneq S}G(T) \times G(S \oplus T) \times cnt(T, S \oplus T)
$$
然后初始值大概是 $ G(2^k) = 1 $。

不难发现如果无脑处理 $ cnt $ 的话复杂度是 $ O(2^{2n}m) $，显然寄，于是考虑优化，令 $ cnte(S) $ 表示点集 $ S $ 中的边数，不难想到对于 $ cnt $ 可以如下容斥：
$$
cnt(S, T) = cnte(S \vee T) - cnte(S) - cnte(T)
$$
则预处理 $ cnte $ 的复杂度为 $ O(m2^n) $，$ cnt $ 可以 $ O(1) $ 求解，$ G $ 的处理则是 $ O(3^n) $ 的。

然后矩阵树定理的结论大概就是首先对这个图建出拉普拉斯矩阵 $ L $，然后答案就是 $ \det(L_0) $，其中 $ L_0 $ 表示 $ L $ 去掉第 $ i $ 行第 $ i $ 列的子矩阵，其中 $ i $ 任意。具体证明参考 [矩阵树定理（Matrix-tree Theorem）笔记](https://zhuanlan.zhihu.com/p/108209378)。所以只需要矩阵建出来无脑求一下行列式即可。

于是考虑如何转移 $ F $，依然类比 ABC213G，我们令 $ \lvert S \rvert $ 表示点集 $ S $ 中点的数量，也就是 `__builtin_popcount(S)`，不难发现转移：
$$
F(i, S) = \sum_{1 \in      T \subsetneq S} G(T) \times F(i - (\lvert T \rvert - 1), S \oplus T)
$$
也就是钦定一个子集为一棵树，然后剩下的作为森林，钦定 $ 1 $ 节点在树中可以去重，具体在 ABC213G 也有说明。

不过很遗憾这个又是错的。我们在 ABC213G 中钦定 $ 1 $ 是因为 $ 1 $ 一定被选，但是在本题里并没有这个限制，所以我们要换一种写法，不难想到使用 $ S $ 中的最后一个 $ 1 $ 是易于实现且正确的，即 $ \operatorname{lowbit}(S) $，或者说 $ S \land -S $。于是转移改为：
$$
F(i, S) = \sum_{\operatorname{lowbit}(S) \in T \subsetneq S} G(T) \times F(i - (\lvert T \rvert - 1), S \oplus T)
$$
边界条件的话就是如果 $ S $ 的点数恰好为 $ i + 1 $，那么显然就是一棵树，即 $ F(i, S) = G(S) $。

然后考虑答案，令 $ Smx = 2^n - 1 $，即全集，不难想到对于选 $ i $ 条边的答案 $ ans_i $ 有：
$$
ans_i = \dfrac{F(i, Smx) \times i!}{m^i} \bmod{998244353}
$$
也不难理解，概率转计数，总方案数为 $ m_i $，然后要让所有点形成森林，方案中选择的 $ i $ 条边任意排列均不同，所以需要在乘一个 $ i! $。



大概就这样了，处理 $ G $ 的复杂度为 $ O(n^3 2^n) $，处理 $ F $ 的复杂度为 $ O(n 3^n) $，处理答案复杂度作为常数，最终复杂度 $ O((m + n^3) 2^n + 3^n) $，可以通过。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MAX_STATUS (20000)
#define MOD (ll)(998244353)
#define EXIST(x) (S & (1 << ((x) - 1)))

template < typename T = int >
inline T read(void);

struct Edge{
    Edge* nxt;
    int to;
    OPNEW;
}ed[1100];
ROPNEW(ed);
Edge* head[20];

int N, M;
int deg[20];
ll G[MAX_STATUS], F[20][MAX_STATUS];
int cnte[MAX_STATUS];
ll fact[30];

int lowbit(int x){return x & -x;}
int CalCnt(int S, int T){return cnte[S | T] - cnte[S] - cnte[T];}
ll qpow(ll a, ll b){
    ll ret(1), mul(a);
    while(b){
        if(b & 1)ret = ret * mul % MOD;
        b >>= 1;
        mul = mul * mul % MOD;
    }return ret;
}

int main(){fact[0] = 1;
    for(int i = 1; i <= 20; ++i)fact[i] = fact[i - 1] * i % MOD;
    N = read(), M = read();
    const int Smx = (1 << N) - 1;
    for(int i = 1; i <= M; ++i){
        int s = read(), t = read();
        head[s] = new Edge{head[s], t};
        head[t] = new Edge{head[t], s};
    }
    for(int S = Smx; S; S = (S - 1) & Smx){
        int cnt(0);
        for(int p = 1; p <= N; ++p)
            for(auto i = head[p]; i; i = i->nxt)
                if(EXIST(p) && EXIST(SON))++cnt;
        cnt >>= 1;
        cnte[S] = cnt;
    }
    for(int S = 1; S <= Smx; ++S){
        if(__builtin_popcount(S) == 1){G[S] = 1; continue;}
        for(int T = (S - 1) & S; T; T = (T - 1) & S)
            if(T & lowbit(S))
                (G[S] += G[T] * G[S ^ T] % MOD * CalCnt(T, S ^ T) % MOD) %= MOD;
        (G[S] *= qpow(__builtin_popcount(S) - 1, MOD - 2)) %= MOD;
    }
    for(int i = 0; i <= N - 1; ++i)
        for(int S = 0; S <= Smx; ++S){
            if(__builtin_popcount(S) == i + 1){F[i][S] = G[S]; continue;}
            for(int T = (S - 1) & S; T; T = (T - 1) & S)
                if(T & lowbit(S) && i - (__builtin_popcount(T) - 1) >= 0)
                    (F[i][S] += G[T] * F[i - (__builtin_popcount(T) - 1)][S ^ T]) %= MOD;
        }
    for(int i = 1; i <= N - 1; ++i)
        printf("%lld\n", F[i][Smx] * fact[i] % MOD * qpow(qpow(M, i), MOD - 2) % MOD);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_07 初稿

---

## 作者：2008verser (赞：0)

转为计数长为 $1,2,\ldots,n-1$ 序列个数，序列元素代表一条边，序列要满足：把元素代表的那些边加入后是森林。

设 $f_{i,S}$ 表示长为 $i$ 的序列，连通块大小 $\geq2$ 的点集为 $S$ 的方案数。枚举序列最后一条边所属连通块 $T$，有

$$
f_{i,S}=\sum_{|T|\geq 2,T\subseteq S} f_{i-|T|+1,S\setminus T}\times g(T)\times{i-1\choose |T|-2}
$$

$g(S)$ 代表长为 $|S|-1$ 的序列方案数，满足序列边加入后将 $S$ 联通。转移更是基础，枚举最后一条边划分的俩点集：

$$
g(S)=\frac12\sum_{T\subset S,T\neq\emptyset}g(T)\times g(S\setminus T)\times {|S|-2\choose |T|-1}\times E(T,S\setminus T)
$$

上面的转移都比较基础，应该无需多做解释了。

$E(A,B)$ 表示点集 $A,B$ 之间的边数，直接暴力算，时间复杂度 $O(3^nn^2)$。

[AC 链接](https://atcoder.jp/contests/abc253/submissions/60630204)

---

