# 「ALFR Round 2」B 篮球比赛

## 题目背景

![](https://nimg.ws.126.net/?url=http%3A%2F%2Fdingyue.ws.126.net%2F2023%2F0820%2F075e9bccj00rzoph900wkd000t200i6p.jpg&thumbnail=660x2147483647&quality=80&type=jpg)

## 题目描述

小山即将参加 $n$ 场篮球比赛，他有一个多项式函数 $f(x)=a_0+a_1x^1+a_2x^2+\dots+a_kx^k$ 与 $m$ 个和为 $1$ 的数 $p_1,p_2,p_3,\dots,p_m$。

他所在的球队有 $\dfrac{f(i)}{\sum_{j=1}^n f(j)}$ 的概率在第 $i$ 场比赛中取得**第一次**胜利，这意味着前面的 $i-1$ 场都输了。

接下来，如果第 $i$ 场比赛中小山所在球队取得了胜利，则对于 $1\le j\le m$，他们有 $p_j$ 的概率在第 $i+j$ 场比赛取得下一次胜利，这意味着如果 $j\gt1$，第 $i+1$ 场到第 $i+j-1$ 场都输了（若 $i+j>n$，则之后的比赛都输，没有再胜利）。

小山想知道他所在球队的期望胜利场数，你能帮帮他吗？

注意：在计算时，如果遇到分数（比如 $\dfrac{f(i)}{\sum_{j=1}^n f(j)}$），应使用分数取模形式。如果不知道什么是分数取模形式，参见 [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)。

为了方便你的计算，输入数据将直接给出 $p_i,a_i$ 对 $998244353$ 取模的结果。

## 说明/提示

### 样例解释

在第一组样例中：$p_1=0.2,p_2=0.3,p_3=0.5$；$f(1)=3,f(2)=9,f(3)=3,f(4)=15$。胜利场数期望为 $1.2988$。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | $n=1$ |
| $1$ | $30$ | $n\le10^6$ |
| $2$ | $60$ | - |

对于 $100\%$ 的数据，$1\le n\le 10^{18}$，$1\le m,k \le 50$，保证 $\sum_{j=1}^n f(j)$ 不被 $998244353$ 整除。

## 样例 #1

### 输入

```
4 3 3
598946612 898419918 499122177
998244308 79 998244317 5```

### 输出

```
319837492```

# 题解

## 作者：szh_AK_all (赞：7)

出题人题解。

### 正解
定义 $dp_i$ 为：第 $i$ 场比赛胜利的概率，则可得到如下代码（暴力）：
```cpp
int sum = 0;
for (int i = 1; i <= n; i++) {
	for (int j = 0; j <= k; j++)
		f[i] = (f[i] + aa[j] * qpow(i, j) % mod) % mod;
	sum = (sum + f[i]) % mod;
}
for (int i = 1; i <= n; i++)
	dp[i] = f[i] * qpow(sum, mod - 2) % mod;
for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
		dp[i + j] = (dp[i + j] + dp[i] * p[j] % mod) % mod;
sum = 0;
for (int i = 1; i <= n; i++)
	sum = (sum + dp[i]) % mod;
cout << sum;
```
其中 $k(i)$ 即为 $\dfrac{f(i)}{\sum_{j=1}^n f(j)}$。

最终期望胜利场数即为 $\sum_{i=1}^ndp_i$。

由于这种转移时间复杂度很慢，所以考虑矩阵乘法。

首先，求出 $\sum_{i=1}^n f(i)$。定义 $sum(i)=\sum_{j=1}^i f(j)$，从而构造初始矩阵：
$$
\begin{pmatrix}
  sum_{i-1} & 1 & i & i^2 & \dots & i^k \\ 
\end{pmatrix}
$$

接着根据二项式展开构造 $base$ 矩阵：
$$
\begin{pmatrix}
  1 & 0 & 0 & 0 &\dots\\ 
  a_0 & C_0^0 & C_1^0 & C_2^0 & \dots\\ 
  a_1 & 0 & C_1^1 & C_2^1 & \dots\\
  a_2 & 0 & 0 & C_2^2 & \dots\\
  a_3 & 0 & 0 & 0 & \dots\\
  \vdots\\
\end{pmatrix}
$$

两个矩阵相乘，可得出：
$$
\begin{pmatrix}
  sum_i & 1 & {i+1} & (i+1)^2 & \dots & (i+1)^k \\ 
\end{pmatrix}
$$

满足矩阵乘法。由于要用到分数取模形式，所以设 $inv$ 为 $\sum_{i=1}^n f(i)$
 的逆元。
 
接着求出 $dp_i$，设 $s_i=\sum_{j=1}^{i-1}dp_j$，由于 $dp_i=\sum_{j=1}^m dp_{i-j}\times p_j$（当 $i-j$ 小于 $0$ 时，$dp_{i-j}$ 可视为 $0$），所以可以得出初始矩阵：
$$
\begin{pmatrix}
  s_i & dp_i & dp_{i-1} & dp_{i-2} & \dots & dp_{i-m+1} & 1 & i & i^2 & \dots i^k\\ 
\end{pmatrix}
$$

接着构造 $base$ 矩阵：
$$
\begin{pmatrix}
  1 & 0 & 0 & 0 & 0 & \dots & 0 & 0 & 0 & 0 & 0 & \dots\\
  1 & p_1 & 1 & 0 & 0 & \dots & 0 & 0 & 0 & 0 & 0 & \dots\\
  0 & p_2 & 0 & 1 & 0 & \dots & 0 & 0 & 0 & 0 & 0 & \dots\\
  0 &p_3 & 0 & 0 & 1 & \dots & 0 & 0 & 0 & 0 & 0 & \dots\\
  \vdots\\
  0 & p_{m-1} & 0 & 0 & 0 & \dots &1 & 0 & 0 & 0 & 0 & \dots\\
  0 & p_m & 0 & 0 & 0 & \dots & 0 & 0 & 0 & 0 & 0 & \dots\\ 
  0 & inv\times a_0 & 0 & 0 & 0 &\dots & 0 & C_0^0 & C_1^0 & C_2^0 & C_3^0 & \dots\\ 
  0 & inv\times a_1 & 0 & 0 & 0 &\dots & 0 & 0& C_1^1 & C_2^1 & C_3^1 & \dots\\
  0 & inv\times a_2 & 0 & 0 & 0 &\dots & 0 & 0 & 0 & C_2^2 & C_3^2 & \dots\\
  0 & inv\times a_3 & 0 & 0 & 0 &\dots & 0 & 0 & 0 & 0 & C_3^3 & \dots\\
  \vdots\\
\end{pmatrix}
$$

两个矩阵相乘得到：
$$
\begin{pmatrix}
  s_{i+1} & dp_{i+1} & dp_i & dp_{i-1} & dp_{i-2} & \dots & dp_{i-m+2} & 1 & i+1 & (i+1)^2 & \dots & (i+1)^k\\ 
\end{pmatrix}
$$

### Code
```cpp
by 2023gdgz01
#include <cstdio>
#include <cstring>

long long n, m, k, inv, maxmk, p[55], A[55], c[55][55];

struct matrix {
	long long c[105][105];
	inline matrix operator* (const matrix &r) {
		matrix temp;
		memset(temp.c, 0, sizeof(temp.c));
		for (register int i = 1; i <= maxmk; ++i)
			for (register int j = 1; j <= maxmk; ++j)
				for (register int y = 1; y <= maxmk; ++y)
					temp.c[i][j] = (temp.c[i][j] + c[i][y] * r.c[y][j] % 998244353) % 998244353;
		return temp;
	}
};

matrix a, ans;

inline int max(int x, int y) {
	if (x > y)
		return x;
	return y;
}

inline void matrix_quick_power(matrix a, long long b) {
	while (b) {
		if (b & 1)
			ans = ans * a;
		a = a * a;
		b >>= 1;
	}
}

inline long long quick_power(long long a, long long b) {
	long long ans = 1;
	while (b) {
		if (b & 1)
			ans = ans * a % 998244353;
		a = a * a % 998244353;
		b >>= 1;
	}
	return ans % 998244353;
}

int main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for (register int i = 1; i <= m; ++i)
		scanf("%lld", p + i);
	for (register int i = 0; i <= k; ++i)
		scanf("%lld", A + i);
	maxmk = max(m, k) + 1 << 1;
	for (register int i = 0; i <= k; ++i) {
		c[i][0] = 1;
		for (register int j = 1; j <= i; ++j)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % 998244353;
	}
	for (register int i = 2; i <= k + 2; ++i)
		ans.c[1][i] = 1;
	a.c[1][1] = 1;
	for (register int i = 2; i <= k + 2; ++i) {
		a.c[i][1] = A[i - 2];
		for (register int j = i; j <= k + 2; ++j)
			a.c[i][j] = c[j - 2][i - 2];
	}
	matrix_quick_power(a, n);
	inv = quick_power(ans.c[1][1], 998244351);
	memset(ans.c, 0, sizeof(ans.c));
	memset(a.c, 0, sizeof(a.c));
	for (register int i = m + 2; i <= m + k + 2; ++i)
		ans.c[1][i] = 1;
	a.c[1][1] = a.c[2][1] = 1;
	for (register int i = 2; i <= m + 1; ++i) {
		a.c[i][2] = p[i - 1];
		if (i != m + 1)
			a.c[i][i + 1] = 1;
	}
	for (register int i = m + 2; i <= m + k + 2; ++i) {
		a.c[i][2] = inv * A[i - m - 2] % 998244353;
		for (register int j = i; j <= m + k + 2; ++j)
			a.c[i][j] = c[j - m - 2][i - m - 2];
	}
	matrix_quick_power(a, n + 1);
	printf("%lld", ans.c[1][1]);
	return 0;
}
```

---

## 作者：NaCly_Fish (赞：4)

题目很简单，不过有人想看所以还是写一下。

首先设
$$P(x)=\sum_{i=1}^mp_i x^i$$
那么第一次胜利后还剩 $r$ 场时，这其中胜场数不超过 $j$ 的概率为
$$a_j=1-[x^r]\frac{P(x)^j}{1-x}$$
故答案为
$$\sum_{i=1}^nf(i)\sum_{j}(j+1)[x^{n-i}]\frac{P(x)^j-P(x)^{j+1}}{1-x}$$
$$=[x^n]\frac{1}{1-x}\frac{1}{1-P(x)}\sum_{i=1}^\infty f(i) x^i$$
然后要用到一个结论：
$$(1-x)^{k+1}\sum_{i=0}^\infty f(i)x^i$$
是一个不超过 $k$ 次的多项式。证明很简单，因为 $k$ 次多项式做 $k+1$ 阶差分的话，后面的项显然都变成 $0$ 了。

求出 $f(0),f(1),\cdots,f(k)$ 后用一次卷积就可以求出此多项式，然后使用 LSB-first（或称 Bostan-Mori）算法直接求系数即可。

时间复杂度 $\Theta(k\log^2k+(m+k)\log (m+k)\log n)$（使用 FFT）或 $\Theta((m+k)^2 \log n)$（暴力计算卷积）。

[参考代码](https://www.luogu.com.cn/paste/doz8d7h7)。

---

