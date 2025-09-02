# Shohag Loves Counting (Hard Version)

## 题目描述

此题为困难版本。简单版本和困难版本的区别在于 $t,m,\sum m$ 的数据范围。

对于一个包含 $n$ 个元素的数组 $a$，定义 $f(k)$ 表示数组 $a$ 所有长度为 $k$ 的子串的最大值的最大公因数。

例如，对于数组 $[2,1,4,6,2]$，$f(3)=\gcd(\max(2,1,4),\max(1,4,6),\max(4,6,2))=\gcd(4,6,6)=2$。

定义一个数组 $a$ 是好的，当且仅当 $\forall 1\leq i<j\leq n，f(i)\neq f(j)$。现在，给定一个数 $m$，请你算出任意非空的仅包含 $1$ 到 $m$ 内的所有整数的好的数组有多少个。由于这样的数组可能很多，答案请对 $998244353$ 取模。

例如，当 $m=2$ 时，所有满足上述要求的数组有 $[1],[1,2],[2],[2,1]$。

## 说明/提示

$1\leq t\leq 3\times 10^5,1\leq m\leq 10^6.$

**注意 $\sum m$ 没有限制。**

## 样例 #1

### 输入

```
3
2
5
9```

### 输出

```
4
29
165```

# 题解

## 作者：Mine_King (赞：4)

[更好的阅读体验](https://caijimk.netlify.app/post/transpose-principle)

*注：本文前半部分大致描述了转置原理，中间为 CF2039F1/F2 的题解，最后一部分是其在 NTT 上的应用。*

---

对于一些算法，如果我们可以将其视作对一个向量的若干线性变换，则称这种算法为线性算法。

具体地，我们可以将算法过程中维护的变量写成一个向量 $\vec{v}$，然后如果对这些变量的操作都是在向量上的线性变换，那么这就是一个线性算法。

把线性变换写作一个矩阵 $A$，就可以将该算法表示为矩阵与向量的乘法 $A \times \vec{v}$。

我们称 $A^T \vec{v}$ 为这个算法的转置算法。

但是我们显然不能把矩阵 $A$ 给直接写出来，因此需要考虑如何快速得到转置算法。

首先把矩阵 $A$ 拆成若干个初等矩阵相乘的形式：$A = B_k B_{k - 1} \ldots B_1$，于是就有：

$B_k B_{k - 1} \ldots B_1 \vec{v} = B_1^T B_2^T \ldots B_k^T \vec{v}$

这样就相当于把所有初等变换的顺序倒过来然后把每个初等变换转置一下，于是我们只需要求每个初等变换的转置就好了：

考虑一个初等矩阵 $M$ 对应的初等变换（以初等行变换为例）：

- 对于初等变换交换矩阵的某两行 $i, j$：$M_{j, i} = M_{i, j} = 1, M_{i, i} = M_{j, j} = 0$，转置后有 $M^T_{j, i} = M^T_{i, j} = 1, M^T_{i, i} = M^T_{j, j} = 0$，因此这种初等变换的转置和原本一样，对应到向量上的操作就是交换两维。
- 对于初等变换给第 $i$ 行乘上 $k$：$M_{i, i} = k$，转置后有 $M^T_{i, i} = k$，因此这种初等变换的转置和原本一样，对应到向量上的操作就是某一维乘上一个系数 $k$。
- 对于初等变换给第 $i$ 行加上第 $j$ 行：$M_{i, j} = 1$，转置后有 $M^T_{j, i} = 1$，对应到向量上的操作就是给第 $i$ 维加上第 $j$ 维变成给第 $j$ 维变成第 $i$ 维。

于是我们可以得到线性算法所有运算均为以下三种之一：

- 交换变量 $x, y$，转置依然是交换变量 $x, y$。
- $x \gets kx$，转置后依然是 $x \gets kx$。注意 $k$ 可以等于 $0$。
- $x \gets x + ky$，转置后变成 $y \gets y + kx$。$x \gets y$ 可以写成上一运算与该运算的组合，即 $x \gets 0x, x\gets x + y$。

显然一个算法转置后复杂度不变，如果我们能对转置后的算法进行优化，那优化后再转置一次就可以得到原算法的优化了。

另一方面，在某些题目中可以将转置后的算法进行一些小修改使其达到与原算法相同的效果。

## 例题

[CF2039F1 Shohag Loves Counting (Easy Version)](https://codeforces.com/contest/2039/problem/F1) / [CF2039F2 Shohag Loves Counting (Hard Version)](https://codeforces.com/contest/2039/problem/F2)

先考虑 F1，考虑什么样的序列是好的，显然每次长度增加 $1$，其权值都是原本权值的倍数，因此首先可以得到好的序列长度为 $O(\log m)$。

然后考虑区间 $\max$ 构成的集合，显然每次删掉的都必须是最小值且只删掉最小值，因此序列必须是单谷的。然后又可以得到序列中每个数都必须互不相同，否则会存在某个时刻中间有两个最小值，然后下一时刻最小值就不会被删掉。

因此问题转化成：求所有单调递减序列 $a_n$ 使得 $\forall i \in [1, n), \gcd(a_1, a_2, \ldots, a_i) > \gcd(a_1, a_2, \ldots, a_i, a_{i + 1})$，并且这个序列的贡献为 $2^{n - 1}$。

设 $f_{i, j}$ 表示 $\gcd = i$，长度为 $j$ 的答案，转移就考虑加入最小值 $x$。为了满足加入的数确实是最小值，我们可以从大到小枚举 $x$ 进行转移。

转移式子大概长这样：

$$
f_{i, j} \gets f_{i, j} + \sum\limits_{k = 2} f_{ik, j - 1} [\gcd(ik, x) = i] \\
f_{x, 1} = 1
$$

然后发现系数是 $2^{j - 1}$，这个可以直接乘进去，所以修改状态定义令 $f_i$ 为 $\gcd = i$ 的所有序列的贡献和：

$$
f_i \gets f_i + \sum\limits_{k = 2} 2f_{ik} [\gcd(ik, x) = i] \\
f_x \gets f_x + 1
$$

考虑优化转移，显然可以改成容斥，令 $s_i = \sum_{k = 1} f_{ik}$，则转移变为：

$$
f_i = f_i + \sum\limits_{i | j \land j | x} 2 s_j \mu\left(\frac{j}{i}\right) - 2f_i \\
f_x \gets f_x + 1
$$

后面减去的是求 $\gcd$ 后等于自己的方案数。

直接做是 $O(m\log^2m)$，可以高维后缀和优化到 $O(m\log m\log\log m)$。

参考代码：

```cpp
// 長い夜の終わりを信じながら
// Think twice, code once.
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eputchar(c) putc(c, stderr)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define eputs(str) fputs(str, stderr), putc('\n', stderr)
using namespace std;

const int mod = 998244353;

int T, n, mu[1000005], dp[1000005], sum[1000005], tmp[1000005];
vector<int> vec[1000005];

int main() {
	mu[1] = 1;
	for (int i = 1; i <= 1000000; i++)
		for (int j = i; j <= 1000000; j += i) {
			vec[j].push_back(i);
			if (j != i) mu[j] -= mu[i];
		}
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) dp[i] = sum[i] = 0;
		for (int i = n; i >= 1; i--) {
			for (int j : vec[i]) tmp[j] = (mod - dp[j] * 2 % mod) % mod;
			for (int j : vec[i])
				for (int k : vec[j]) tmp[k] = (tmp[k] + 2ll * sum[j] * mu[j / k] % mod + mod) % mod;
			tmp[i] = (tmp[i] + 1) % mod;
			for (int j : vec[i]) {
				dp[j] = (dp[j] + tmp[j]) % mod;
				for (int k : vec[j]) sum[k] = (sum[k] + tmp[j]) % mod;
			}
		}
		printf("%d\n", sum[1]);
	}
	return 0;
}
```

由于我们是从后往前枚举的，因此无法通过 F2。

但是这显然是线性算法，我们可以将其视为有一个向量 $\vec{v}$：

$$
\vec{v} = \left(\begin{matrix}
s_1 \\
s_2 \\
\vdots \\
s_n\\
f_1 \\
f_2 \\
\vdots \\
f_n \\
tmp_1 \\
tmp_2 \\
\vdots \\
tmp_n \\
1
\end{matrix}\right)
$$

初始时 $\vec{v}$ 除了最后一维都是 $0$。

然后枚举的每个 $i$ 都视为将其乘上一个矩阵 $A_i$，则问题答案即为：

$$
\left(\begin{matrix}
1 & 0 & 0 & \cdots & 0
\end{matrix}\right)
\times 
A_1 A_2 \cdots A_m \times
\left(\begin{matrix}
0 \\
0 \\
\vdots \\
0 \\
1
\end{matrix}\right)
$$

将其转置后即为：

$$
\left(\begin{matrix}
0 & 0 & \cdots & 0 & 1
\end{matrix}\right)
\times 
A_m^T \cdots A_2^T A_1^T \times
\left(\begin{matrix}
1 \\
0 \\
0 \\
\vdots \\
0
\end{matrix}\right)
$$

也就是初始时令 $s_1 = 1$，用一个变量 $val$ 来维护原向量中的那个 $1$，从前往后枚举 $i$ 并乘上转置后的矩阵，最后 $val$ 即为答案。

由于是从前往后做的，因此后一个的答案可以从前一个继承过来，只需要做一遍就可以求出所有 $m$ 的解然后 $O(1)$ 查询了。

参考代码：

```cpp
// 長い夜の終わりを信じながら
// Think twice, code once.
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eputchar(c) putc(c, stderr)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define eputs(str) fputs(str, stderr), putc('\n', stderr)
using namespace std;

const int mod = 998244353;

int T, n, mu[1000005], dp[1000005], sum[1000005], tmp[1000005], val, ans[1000005];
vector<int> vec[1000005];

int main() {
	mu[1] = 1;
	for (int i = 1; i <= 1000000; i++)
		for (int j = i; j <= 1000000; j += i) {
			vec[j].push_back(i);
			if (j != i) mu[j] -= mu[i];
		}
	sum[1] = 1;
	for (int i = 1; i <= 1000000; i++) {
		for (int j : vec[i]) {
			tmp[j] = (tmp[j] + dp[j]) % mod;
			for (int k : vec[j]) tmp[j] = (tmp[j] + sum[k]) % mod;
		}
		val = (val + tmp[i]) % mod;
		for (int j : vec[i])
			for (int k : vec[j]) sum[j] = (sum[j] + 2ll * tmp[k] * mu[j / k] % mod + mod) % mod;
		for (int j : vec[i]) dp[j] = (dp[j] - tmp[j] * 2 % mod) % mod;
		for (int j : vec[i]) tmp[j] = 0;
		ans[i] = val;
	}
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}
```

## 优化 NTT

先贴个码：

```cpp
static void NTT(poly &g, int flag) {
	int n = g.size();
	vector<unsigned long long> f(g.begin(), g.end());
	vector<int> swp(n);
	for (int i = 0; i < n; i++) {
		swp[i] = swp[i >> 1] >> 1 | ((i & 1) * (n >> 1));
		if (i < swp[i]) std::swap(f[i], f[swp[i]]);
	}
	for (int mid = 1; mid < n; mid <<= 1) {
		int w1 = power(flag ? G : invG, (mod - 1) / mid / 2);
		vector<int> w(mid);
		w[0] = 1;
		for (int i = 1; i < mid; i++) w[i] = (long long)w[i - 1] * w1 % mod;
		for (int i = 0; i < n; i += mid << 1)
			for (int j = 0; j < mid; j++) {
				int t = (long long)w[j] * f[i + mid + j] % mod;
				f[i + mid + j] = f[i + j] - t + mod;
				f[i + j] += t;
			}
		if (mid == 1 << 10)
			for (int i = 0; i < n; i++) f[i] %= mod;
	}
	int inv = flag ? 1 : power(n, mod - 2);
	for (int i = 0; i < n; i++) g[i] = f[i] % mod * inv % mod;
	return;
}
```

显然 NTT 也是线性算法，考虑它的转置长什么样。

首先翻转顺序，然后考虑中间这部分：

```cpp
int t = (long long)w[j] * f[i + mid + j] % mod;
f[i + mid + j] = f[i + j] - t + mod;
f[i + j] += t;
```

以下用 $w, x, y$ 来表示 $w_j, f_{i + j}, f_{i + mid + j}$，这部分的运算可以写成：

$$
t \gets 0, t \gets t + wy \\
y \gets 0, y \gets y + x, y \gets y - t \\
x \gets x + t \\
t \gets 0
$$

转置后就变成：

$$
t \gets 0 \\
t \gets t + x \\
t \gets t - y, x \gets x + y, y \gets 0 \\
y \gets y + wt, t \gets 0
$$

于是我们可以写出转置后的 NTT：

```cpp
static void NTT(poly &g, int flag) {
	int n = g.size();
	vector<unsigned long long> f(g.begin(), g.end());
	int inv = flag ? 1 : power(n, mod - 2);
	for (int i = 0; i < n; i++) f[i] = f[i] % mod * inv % mod;
	for (int mid = n >> 1; mid >= 1; mid >>= 1) {
		int w1 = power(flag ? G : invG, (mod - 1) / mid / 2);
		vector<int> w(mid);
		w[0] = 1;
		for (int i = 1; i < mid; i++) w[i] = (long long)w[i - 1] * w1 % mod;
		for (int i = 0; i < n; i += mid << 1)
			for (int j = 0; j < mid; j++) {
				int t = (long long)(f[i + j] - f[i + mid + j] % mod + mod) * w[j] % mod;
				f[i + j] += f[i + mid + j];
				f[i + mid + j] = t;
			}
		if (mid == 1 << 10)
			for (int i = 0; i < n; i++) f[i] %= mod;
	}
	vector<int> swp(n);
	for (int i = 0; i < n; i++) {
		swp[i] = swp[i >> 1] >> 1 | ((i & 1) * (n >> 1));
		if (i < swp[i]) std::swap(f[i], f[swp[i]]);
	}
	for (int i = 0; i < n; i++) g[i] = f[i] % mod;
	return;
}
```

然后考虑 NTT 的本质是什么，本质是求多项式在 $\omega_n^0, \omega_n^1, \ldots, \omega_n^{n - 1}$ 处的点值（DFT）和根据点值求多项式的系数（IDFT），如果你把这个东西直接写成矩阵，你会发现它们分别是：

$$
\begin{matrix}
\omega_n^0 & \omega_n^0 & \omega_n^0 & \cdots & \omega_n^0 \\
\omega_n^0 & \omega_n^1 & \omega_n^2 & \cdots & \omega_n^{n - 1} \\
\omega_n^0 & \omega_n^2 & \omega_n^4 & \cdots & \omega_n^{2n - 2} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
\omega_n^0 & \omega_n^{n - 1} & \omega_n^{2n - 2} & \cdots & \omega_n^{(n - 1)^2}
\end{matrix}
$$

和：

$$
\begin{matrix}
\frac{\omega_n^0}{n} & \frac{\omega_n^0}{n} & \frac{\omega_n^0}{n} & \cdots & \frac{\omega_n^0}{n} \\
\frac{\omega_n^0}{n} & \frac{\omega_n^{-1}}{n} & \frac{\omega_n^{-2}}{n} & \cdots & \frac{\omega_n^{1 - n}}{n} \\
\frac{\omega_n^0}{n} & \frac{\omega_n^{-2}}{n} & \frac{\omega_n^{-4}}{n} & \cdots & \frac{\omega_n^{2 - 2n}}{n} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
\frac{\omega_n^0}{n} & \frac{\omega_n^{1 - n}}{n} & \frac{\omega_n^{2 - 2n}}{n} & \cdots & \frac{\omega_n^{-(n - 1)^2}}{n}
\end{matrix} \\
$$

所以 NTT 的转置和 NTT 效果完全相同！

对于很多多项式操作（如多项式乘法、求逆等），在 DFT 之后 IDFT 之前，我们并不关心其每个值的顺序，因此如果只对 DFT 转置，那 DFT 和 IDFT 之间的两次蝴蝶变换就可以被省略掉了！

```cpp
// 这份代码还稍微优化了下取模常数。
static void NTT(poly &g, int flag) {
	int n = g.size();
	vector<int> f(g.begin(), g.end());
	if (flag) {
		for (int mid = n >> 1; mid >= 1; mid >>= 1) {
			int w1 = power(G, (mod - 1) / mid / 2);
			vector<int> w(mid);
			w[0] = 1;
			for (int i = 1; i < mid; i++) w[i] = (long long)w[i - 1] * w1 % mod;
			for (int i = 0; i < n; i += mid << 1)
				for (int j = 0; j < mid; j++) {
					int t = (long long)(f[i + j] - f[i + mid + j] + mod) * w[j] % mod;
					f[i + j] = f[i + j] + f[i + mid + j] >= mod ?
						f[i + j] + f[i + mid + j] - mod : f[i + j] + f[i + mid + j];
					f[i + mid + j] = t;
				}
		}
		for (int i = 0; i < n; i++) g[i] = f[i];
	} else {
		for (int mid = 1; mid < n; mid <<= 1) {
			int w1 = power(invG, (mod - 1) / mid / 2);
			vector<int> w(mid);
			w[0] = 1;
			for (int i = 1; i < mid; i++) w[i] = (long long)w[i - 1] * w1 % mod;
			for (int i = 0; i < n; i += mid << 1)
				for (int j = 0; j < mid; j++) {
					int t = (long long)w[j] * f[i + mid + j] % mod;
					f[i + mid + j] = f[i + j] - t < 0 ? f[i + j] - t + mod : f[i + j] - t;
					f[i + j] = f[i + j] + t >= mod ? f[i + j] + t - mod : f[i + j] + t;
				}
		}
		int inv = power(n, mod - 2);
		for (int i = 0; i < n; i++) g[i] = (long long)f[i] * inv % mod;
	}
	return;
}
```

---

## 作者：MisaYuzuki (赞：3)

作为勤劳的题解自动姬来写这篇题解三周目。

---

F1 部分（$\Theta(n\log^3n)$ 做法）

发现如果从大往小去构造方案，那么下一步能放什么数只和上一步的值以及前面所有数的 $\gcd$ 有关。所以设 $f_{i,j}$ 为上一步的 $\gcd$ 为 $i$，以及最后一个值为 $i\times j$ 的方案数。那么可以想到如下转移：
$$
f_{p,q}\to f_{i,j}[p\lt i,\gcd(pq,i)=p,pq\lt ij]​
$$
很容易发现从大往小转移和从小往大转移其实差不多，所以为了有拓展性，我们选择从小往大转移（从大往小转移需要枚举边界，扫过一遍复杂度是 $\Theta(n^2)$ 的）。

如果直接枚举 $p,q,i,j$ 时间肯定会超。那么只能考虑先预处理一部分信息然后整合优化维度。

我们选择去从小往大枚举 $p$**（注：这是两种做法唯一的区别）**。对于所有 $q$ 假设已经预处理完 $f_{p,q}$。那么对于所有合法（即满足 $p\mid i,p\neq i,ij\le n$）的二元组 $(i,j)$，与 $q$ 有关联的约束有 $pq\lt ij$。那么可以在每一个 $q^\prime$ 做完的时候找到所有满足 $ij\in(pq^\prime,p(q^\prime+1)]$ 的合法二元组 $(i,j)$ 做一次更新即可。然后仔细分析如何利用已处理的信息：
$$
f_{i,j}=\sum_{p\mid i}\sum_{q\mid \frac{p}{i}}f_{p,q}[\gcd(pq,i)=p]
\\
f_{i,j}=\sum_{p\mid i}\sum_{q\mid \frac{p}{i}}f_{p,q}[\gcd(q,\frac{i}{p})=1]
\\
f_{i,j}=\sum_{p\mid i}\sum_{q\mid \frac{p}{i}}f_{p,q}\sum_{x\mid \frac{i}{pq}}\mu(x)
$$
也就是在同一个 $p$ 中，当所有 $\lt pq$ 的信息都处理完的时候，还需要再次枚举 $x$ 加上莫比乌斯函数系数。由于 $(a,b,c,d)(a\mid b,b\mid c,c\mid d)$ 四元组个数是 $\Theta(n\log^3n)$ 级别的（这里不放证明，感兴趣的读者可以自证），所以相当于瓶颈在于枚举四元组 $(p,px,i,ij)$ 上。容易做到 $\Theta(n\log^3n)$。

[code](https://codeforces.com/contest/2039/submission/292993374)

---

F2 部分（$\Theta(n\log^2n)$ 做法）

我们发现上一步的瓶颈在于枚举四元组，所以考虑是否能优化掉其中的一个数。容易观察到 $p$ 约束比较麻烦的条件为 $pq\lt ij$，所以我们考虑直接枚举 $pq/ij$。然后内层循环枚举 $p/i$。然后也就是限制 $pq\lt ij$ 被优化掉了。那也就是可能可以合并 $(p,px)$，优化掉一维。发现此时 $pq$ 的值已经不重要了，我们只需要让 $px\mid i$ 即可。那即枚举每一对 $(p,q)$ 时，多枚举一维 $x$，然后将信息存入 $px$ 的桶内，即 $f_{p,q}\mu(x)$。然后枚举到 $(i,j)$ 时直接遍历 $px\mid i$ 即可。此时瓶颈变成枚举三元组，所以复杂度是 $\Theta(n\log^2n)$。

[code](https://codeforces.com/contest/2039/submission/293177634)

给珂爱的小妹妹点个赞吧 qwq

update：

2024.11.28 发现了一处式子条件错误，已更改。

---

## 作者：SunsetGlow95 (赞：2)

我不会的题，那就是好题。

## 题意简述

假设有一个数组 $a$，$f(k)$ 表示 $a$ 所有长度为 $k$ 的子区间的最大值的 $\gcd$，$a$ 是好的当且仅当在定义域内 $f(k)$ 两两不同。求有多少个值域为 $[1,m]$ 的整数的任意长度的 $a$ 是好的。对 F2 Hard Version，$m\le 10^6$。

## 观察

$f(k)$ 两两不同，首先要定长区间最大值集合两两不同。从 $k=2$ 考虑，就是要求 $\nexists i\ \text{s.t.}\ a_i\ge a_{i-1},a_i\ge a_{i+1}$。然后发现对后续的过程还要求 $a_i$ 两两不同。

手动模拟后总结一下：好的序列必须是一个严格单谷序列，并且从小到大排序后，所有后缀 $\gcd$ 两两不同。

## Easy Version

既然是后缀，$\sum m$ 也很小，考虑从大到小插入数。令 $f_i$ 维护当前后缀 $\gcd$ 为 $i$ 的序列个数，然后每次长度加一的时候因为最小值有两个位置可以插入（当前最小值的左右），所以 $\times$ 贡献过去。每次插入一个数 $i$，考虑 $f_j$ 向 $f_{\gcd(i,j)}$ 贡献。直接做是 $O(m^2\log m)$。

看到 $\gcd$ 一个想法是莫反。推一推式子，假设当前考虑对 $f_j$ 的增量，且暂且不考虑贡献时 $\gcd(i,j)<j$ 的限制：

$$\begin{aligned}&\sum_k f_k[\gcd(k,i)=j] \\
=& \sum_k f_{jk}[\gcd(k,\frac{i}{j})=1] \\
=& \sum_k f_{jk}\sum_{d\mid \gcd(k,\frac{i}{j})} \mu(d) \\
=& \sum_{dj\mid i} \mu(d)\sum_k f_{djk} \\ \end{aligned}$$

实时维护一下 $g_i=\sum_j f_{ij}$，遍历每个 $i$ 的因子 $j$，套一层遍历每个 $\frac{i}{j}$ 的因子 $d$，把 $\mu (d)g_{dj}$ 加入贡献中。最后把限制减掉 $f_j$ 对自身的贡献，这部分的贡献 $\times 2$。然后新建一个点的贡献就是给 $f_i$ 做一次 $+1$。细节上，这些都是同时做的，所以把所有的贡献暂存然后再一起加回去。

单次时间 $O(\sum_{1\le i\le n}\sum_{d\mid i}\sigma(d))$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN = 100005;
const int DVS = 998244353;
int T, N, cnt[MXN], sum[MXN], ans, delta[MXN], mu[MXN];
vector<int> fac[MXN];

inline void add(int i, int v) {
  cnt[i] = (cnt[i] + v) % DVS;
  for (int j : fac[i]) sum[j] = (sum[j] + v) % DVS;
}

int main() {
  mu[1] = 1;
  for (int i(1); i != MXN; ++i) {
    fac[i].push_back(i);
    for (int j(i + i); j < MXN; j += i) fac[j].push_back(i), mu[j] -= mu[i];
    mu[i] = (DVS + mu[i]) % DVS;
  }
  cin >> T;
  while (T--) {
    cin >> N;
    for (int i(1); i <= N; ++i) cnt[i] = 0, sum[i] = 0;
    for (int i(N); i; --i) {
      for (int j : fac[i]) {
        delta[j] = (DVS - cnt[j]) % DVS;
        for (int k : fac[i / j])
          delta[j] = (delta[j] + mu[k] * 1LL * sum[j * k]) % DVS;
        delta[j] = delta[j] * 2 % DVS;
      }
      delta[i] = (delta[i] + 1) % DVS;
      for (int j : fac[i]) add(j, delta[j]), delta[j] = 0;
    }
    ans = 0;
    for (int i(1); i <= N; ++i) ans = (ans + cnt[i]) % DVS;
    cout << ans << endl;
  }
  return 0;
}
```

## Hard Version

发现强制要求从小往大插，离线存一下答案。

那好吧，令 $f_{i,j}$ 表示当前位的后缀 $\gcd$ 填 $i$，当前位本身是 $ij$。再次考虑莫反算贡献，枚举当前 $i$ 的每个因子 $j$：

$$\begin{aligned} &\sum_{k,l} f_{k,l}[\gcd(kl,j)=k] \\
=& \sum_{k,l} f_{k,l}[\gcd(l,\frac{j}{k})=1] \\
=& \sum_{kd\mid j} \mu(d) \sum_{l} f_{k,dl}
\end{aligned}$$

你以为这里要两维都记然后达成 $O(n\log n)$ 的空间复杂度？不用！只要存 $g_i=\sum_{d\mid i} \mu(d) \sum_{l} f_{\frac{i}{d},dl}$，每次查询 $g_{kd}$ 即可。复杂度不变。

这么做还是不考虑贡献时 $\gcd(i,j)<j$ 的限制，所以仍然要除去 $s_i=\sum_k f_{i,k}$ 对自身的贡献。那么空间上只存 $g,s$ 两个。空间是 $O(n)$ 的。

每次加入一个数 $i$，对所有 $j\mid i$ 的 $f_{j,\frac{i}{j}}$ 做更新，而且每个都要 $+1$。而答案的差分即为 $f_{i,1}$，前缀和一下即可。

时间有点紧（虽然我没卡常），可以通过存因数的时候先做 `vector::reserve()` 加速。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN = 1000005;
const int DVS = 998244353;
int T, N, cnt[MXN], sum[MXN], ans[MXN], delta[MXN], mu[MXN];
vector<int> fac[MXN];

inline void add(int i, int v) {
  cnt[i] = (cnt[i] + v) % DVS;
}

int main() {
  mu[1] = 1;
  for (int i(1); i != MXN; ++i) fac[i].reserve(10);
  for (int i(1); i != MXN; ++i) {
    fac[i].push_back(i);
    for (int j(i + i); j < MXN; j += i) fac[j].push_back(i), mu[j] -= mu[i];
    mu[i] = (DVS + mu[i]) % DVS;
  }
  for (int i(1); i != MXN; ++i) {
    for (int j : fac[i]) {
      delta[j] = (DVS - cnt[j]) % DVS;
      for (int k : fac[j]) delta[j] = (delta[j] + sum[k]) % DVS;
      delta[j] = (delta[j] + delta[j] + 1) % DVS;
    }
    for (int j : fac[i]) {
      for (int k : fac[i / j])
        sum[j * k] = (sum[j * k] + mu[k] * 1LL * delta[j]) % DVS;
      cnt[j] = (cnt[j] + delta[j]) % DVS;
    }
    ans[i] = (ans[i - 1] + cnt[i]) % DVS;
  }
  scanf("%d", &T);
  while (T--) scanf("%d", &N), printf("%d\n", ans[N]);
  return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

奇了怪了，理论上我应该很擅长做这种题啊，怎么会是呢。

考虑 Easy Version，这部分只需要给出关于 $m$ 的一个 Polylog 做法

首先考虑什么样的序列是好的。考虑序列的最大元素，它必定是唯一的且出现在序列的左右两端；此时删去它，剩下的序列应当还是好的。

因此好的序列所有数都不重复，且对于数列 $a_1<a_2<\cdots<a_n$，如果 $\gcd(a_i,a_{i+1},\cdots,a_n)$ 对于所有 $i$ 互不相同，有 $2^{n-1}$ 种方法将它排列成好的，否则不能排成好的。

------

对 F1，有一个很简单的 DP：从后往前考虑序列，设 $dp_{i,j}$ 表示当前序列的第一个数是 $j$，序列的 $\gcd$ 是 $i$ 的方案数。

加入一个数字 $d$ 之后（顺序是 $m$ 到 $1$），考虑所有 $i \mid d$，我们更新 $dp_{i,d}$，也就是需要对 $dp_{j,*}$ 进行计数，满足 $i \mid j$ 且 $\gcd(j,d)=i$。

可以考虑让每个 $j$ 对 $i$ 贡献，再对第二维做莫比乌斯反演。

考虑枚举了 $d$，$d$ 的因数，$\frac{i}{d}$ 的因数，$d$ 的因数的因数的因数（套娃），复杂度是 $O(m \log^3 m)$，可以通过 F1 了（$700 \rm ms$）

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MOD=998244353;
int T,n,flg[MAXN],mu[MAXN],sum[MAXN],slen[MAXN];
vector<int> ff[MAXN],fr[MAXN],dp[MAXN],DP[MAXN];
void init(int mx) {
	n=mx;
	vector<int> pr;
	mu[1]=1;
	ffor(i,2,mx) {
		if(!flg[i]) mu[i]=-1,pr.push_back(i);
		for(auto v:pr) {
			if(i*v>mx) break ;
			flg[i*v]=1;
			if(i%v==0) break ;
			mu[i*v]=-mu[i];
		}
	}
	ffor(i,2,n) ffor(j,1,n/i) fr[i*j].push_back(j);
	ffor(i,1,n) if(mu[i]) ffor(j,1,n/i) ff[i*j].push_back(i);
	return ;
}
void add(int u,int v) {
	for(auto f:fr[u]) {
		int div=u/f;
		for(auto k:ff[div]) dp[f][k]=(dp[f][k]+v*mu[k])%MOD;
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	init(100000);
	while(T--) {
		cin>>n;
		ffor(i,1,n) dp[i].clear(),dp[i].resize(n/i+1),DP[i].resize(n/i+1),sum[i]=0,slen[i]=0;
		roff(i,n,1) {
			sum[i]=(sum[i]+1+dp[i][1]*2)%MOD;
			add(i,1+dp[i][1]*2);
			for(auto d:fr[i]) {
				int delta=0,Delta=0;
				for(auto v:ff[i/d]) delta=(delta+dp[d][v]*2)%MOD;
				sum[d]=(sum[d]+delta)%MOD,add(d,delta);
			}
		}	
		int ans=0;
		ffor(i,1,n) ans=(ans+sum[i])%MOD;
		cout<<(ans%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

-----

对于 F2 来说，上限是不确定的，所以要正着枚举。

设 $dp_{i,j}$ 表示，当前最后一个数字为 $i$，且最终序列中该位置的后缀 $\gcd$ 为 $j$ 的方案数。

加入数字 $i$ 时，对于 $d \mid i$，将满足 $\gcd(k,j)=d$（$d \neq j$，$k<i$） 的 $dp_{k,d}$ 加入 $dp_{i,j}$ 中。

按照顺序枚举的时候，显然有 $k<i$ 满足（注意不会出现 $k=i$ 的情况，因为 $j \mid i$）

如何保证 $\gcd(k,j) = d$。这个式子肯定要莫比乌斯反演，将 $\frac{k}{d}$ 和 $\frac{j}{d}$ 的因子进行枚举。

注意到第一维可能没那么重要，因为你已经钦定时间顺序了。所以只维护 $dp_j$ 表示当前的 $dp_{i,j}$ 处的值。

在 F1 的做法中，对于这种莫比乌斯反演我是将它挂在 $d$ 处的，即在每个 $i$ 开一个大小为 $\frac{n}{i}$ 的 `vector` 维护莫比乌斯反演后的值。

但是注意公因子 $z \mid \frac{k}{d}$ 和 $z \mid \frac{j}{d}$ 可以可化为 $d \mid t \mid j$ 的一个整除链，其中 $t = zd$，因此可以把反演后的值加到 $t$ 中，这样就是一维的了。

复杂度是长度为 $3$ 的整除链的个数，为 $O(V \log^2 V)$，$V$ 是值域。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,MOD=998244353;
int T,m,ans[MAXN],flg[MAXN],mu[MAXN],dp[MAXN],tmp[MAXN];
vector<int> fr[MAXN],pr;
void update(int d,int v,int mul) {
	for(auto dd:fr[mul]) tmp[d*dd]=(tmp[d*dd]+v*mu[dd])%MOD;
	return ;
}
int calc(int u) {
	int ans=0;
	for(auto d:fr[u]) ans=(ans+tmp[d])%MOD;
	return ans;	
}
void solve(int mx) {
	int n=mx;
	ffor(i,1,n) {
		ans[i]=dp[i]=(1+calc(i))%MOD,update(i,2*dp[i]%MOD,1);
		for(auto d:fr[i]) if(d!=i) {
			int dt=(calc(d)-2*dp[d]+1)%MOD;
			dp[d]=(dp[d]+dt)%MOD,update(d,2*dt%MOD,i/d);
		}
	}
	ffor(i,1,n) ans[i]=(ans[i]+ans[i-1])%MOD;
	return ;
}
void init(int mx) {
	mu[1]=1;
	ffor(i,2,mx) {
		if(!flg[i]) pr.push_back(i),mu[i]=-1;
		for(auto v:pr) {
			if(i*v>mx) break ;
			flg[i*v]=1;
			if(i%v==0) break ;
			mu[i*v]=-mu[i];	
		}
	}
	ffor(i,1,mx) ffor(j,1,mx/i) fr[i*j].push_back(i);
	solve(mx);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	init(1000000);
	cin>>T;
	while(T--) {
		int n;
		cin>>n;
		cout<<(ans[n]%MOD+MOD)%MOD<<'\n';	
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2039F2)

**题目大意**

> 给定 $m$，求有多少值域 $[1,m]$ 的序列 $a_1\sim a_n$ 满足：$\gcd(S_1)\sim \gcd(S_n)$ 互不相同，其中 $S_i$ 表示所有长度为 $i$ 的子区间的最大值构成的集合。
>
> $T$ 组数据。
>
> 数据范围：$m,T\le 10^6$。

**思路分析**

首先区间最大值问题建出笛卡尔树，那么 $S_i$ 就是子树 $\ge i$ 的节点构成的集合。

由于 $\gcd(S_{i-1})\ne \gcd(S_i)$ 所以 $S_{i-1}\ne S_i$，所以对于每个 $i$，笛卡尔树上都有一个大小恰为 $i$ 的子树。

那么笛卡尔树一定是一条链，我们只关心链的权值序列，对应的序列很显然有 $2^{n-1}$ 种。

那么我们现在要计数值域 $[1,m]$ 的递减序列满足每个前缀 $\gcd$ 不同。

用 $f_{i}$ 表示前缀 $\gcd=i$ 的方案数，从大到小枚举 $x=n\sim 1$ 尝试填入序列末尾，转移为 $2f_j\to f_{\gcd(i,x)}$。

这个形式难以优化，用莫比乌斯反演展开：
$$
\begin{aligned}
f_i
&\gets \sum_{j>i}2[\gcd(j,x)=i]f_j\\
&\gets \sum_{j>i} 2f_j\sum_{id\mid j,id\mid x}\mu(d)\\
&\gets \sum_{id\mid x} \mu(d)2\sum_{id\mid j}f_j
\end{aligned}
$$
用 $s_i$ 表示 $\sum_{i\mid j}f_j$，则 $f_i\gets \sum_{k\mid x}\mu(x/k)2s_k$。

此时枚举 $(i,k,x)$ 由于 $i\mid k,k\mid x$，因此复杂度 $\mathcal O(m\log^2m)$。

那么我们得到一个 $\mathcal O(Tm\log^2m)$ 的做法，但 $x$ 要倒序枚举，因此不同的 $m$ 不能统一求答案。

尝试正序枚举 $x$，观察这个 dp 的本质：可以把 $1,f_i,s_i,ans$ 看成 $2n+2$ 个点，那么 dp 就是在他们之间转移。

每个 $x$ 实际上就是在这些点之间连一些带权的边，而答案就是 $1\to ans$ 的所有路径权值乘积之和，要求依次经过 $x=m\sim 1$ 的边。

如果我们正序枚举 $x$，那么要依次处理 $x=1\sim m$ 的边，这是简单的，把图的所有边都取反，计数 $ans\to 1$ 的路径权值乘积之和即可。

实际上这就是转置原理，或者说原 dp 中令 $x\gets x+ky$ 则转置后令 $y\gets y+kx$。

那么做转置后的 dp 就能预处理出所有 $m$ 的答案。

时间复杂度 $\mathcal O(m\log^2m+T)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5,MOD=998244353;
vector <int> pr;
bool isc[MAXN];
int mu[MAXN],f[MAXN],g[MAXN],s[MAXN],rs[MAXN];
int a[MAXN*20],l[MAXN],r[MAXN];
inline void add(int &x,const int &y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
inline void sub(int &x,const int &y) { x=(x>=y)?x-y:x+MOD-y; }
signed main() {
	const int n=1e6;
	mu[1]=1;
	for(int i=2;i<=n;++i) {
		if(!isc[i]) mu[i]=-1,pr.push_back(i);
		for(int p:pr) {
			if(i*p>n) break;
			isc[i*p]=true,mu[i*p]=-mu[i];
			if(i%p==0) { mu[i*p]=0; break; }
		}
	}
	for(int i=1;i<=n;++i) for(int j=i;j<=n;j+=i) ++r[j];
	for(int i=1;i<=n;++i) l[i]=r[i]+=r[i-1];
	for(int i=n;i>=1;--i) for(int j=i;j<=n;j+=i) a[--l[j]]=i;
	s[1]=1;
	int ans=0;
	for(int x=1;x<=n;++x) {
		for(int u=l[x],i;u<r[x];++u) {
			i=a[u],g[i]=f[i];
			for(int j=l[i];j<r[i];++j) add(g[i],s[a[j]]);
		}
		add(ans,g[x]),rs[x]=ans;
		for(int u=l[x],k;u<r[x];++u) {
			k=a[u];
			for(int v=l[k],i;v<r[k];++v) {
				i=a[v];
				if(mu[k/i]==1) add(s[k],g[i]),add(s[k],g[i]);
				else if(mu[k/i]==-1) sub(s[k],g[i]),sub(s[k],g[i]);
			}
		}
		for(int i=l[x];i<r[x];++i) sub(f[a[i]],g[a[i]]),sub(f[a[i]],g[a[i]]);
	}
	int _; scanf("%d",&_);
	for(int m;_--;) scanf("%d",&m),printf("%d\n",rs[m]);
	return 0;
}
```

---

## 作者：Union_of_Britain (赞：1)

来点考前题解。幽默的是场上以为 F2 就是 $\sum m\le 10^6$ 然后以为被卡常乐，鉴定为眼瞎导致的。最后六分钟意识到正确题意 rush 失败。

考虑某数在笛卡尔树上的子树大小 $s$，这意思是可以在 $1\sim s$ 的长度做贡献。由于 $f$ 两两不同，相邻的 $f$ 一定被不同的贡献，也就是说 $s_1,s_2\dots s_n$ 两两不同，也只能是 $1,2,\dots n$。易见此数组两两不同，因此 $n$ 长度数组的确定值域后的方案数是 $2^{n-1}$，这是因为次小值到最大值都可以随意选择放左侧/右侧。

现在只需对值域 dp 选了哪些。写成多步转移是 $f_{i,j}$，表示 $i\sim m$ 里面选的 gcd 是 $j$。转移为

$$f_{i,j}\gets f_{i,j}+2f_{i+1,k}(\gcd(k,i)=j<k)\\ f_{i,i}\gets f_{i,i}+1$$

这是 $O(m^2)$ 的（在 F1 中），考虑优化。注意到每次被影响的 $d=j$ 只有 $d\mid i$，枚举 $d$，使用莫反优化 dp。需要计算

$$
\sum_k f_{i+1,k}[(k,i)=d]=\sum_{d\mid k}f_{i+1,k}[(\frac kd,\frac id)=1]\\
=\sum_{d\mid k}f_{i+1,k}\sum _{t\mid (\frac kd,\frac id)}\mu (t)\\
=\sum _{t\mid \frac id}\mu (t)\sum_{dt\mid k}f_{i+1,k}
$$

若记 $F_x=\sum_{x\mid k}f_{i+1,k}$，则

$$=\sum _{dt\mid i}\mu (t)F_{dt}$$

暴力枚举 $t$，总复杂度为 

$$\sum_{i\mid j\mid k\le m}=O(m\log^2m)$$

每次更新 $f_{i,j}$ 后暴力更新 $F$，复杂度同上，可以通过 F1。

F2 需要从小到大 dp！易见转移是线性变换，那么记 $f=[0,0,0,\dots 0,1]$（$m$ 个 $0$），$A$ 为每次的转移矩阵，答案可以写为：

$$ans=\sum_i (fA_m A_{m-1}A_{m-2}\dots A_1)_i$$

记 $f'=[1,1,1,\dots 1]$，转置之：

$$ans=(f'A_1^TA_2^T\dots A_m^T)_{m+1}$$

现在转移变成了 $(i,k)\to k$ 了，也类似地莫反转移即可（当然也可以直接转置掉 F1 的 dp）。

---

## 作者：Acoipp (赞：0)

提供一个不太需要脑子的做法。

因为没有保证所有 $m$ 的和的范围，因此不难发现它是预处理出所有答案，然后 $O(1)$ 询问。

回到结论（证明参见 CF2039F1 题解区），对于一个 $m$，答案是所有合法的 $a$ 的 $2^{|a|-1}$ 的和。

而 $a$ 合法当且仅当 $a$ 严格递增，并且其每个后缀 $\gcd$ 都互不相同。

于是我们记 $f_{i,j,k}$ 表示 $a_i=j$，并且强制 $\gcd(a_i,a_{i+1},\dots,a_n)=k$ 的 $a_{1 \sim i}$ 的方案数。

转移即为枚举 $l>j,p>k$ 并且满足 $\gcd(p,j)=k$ 将 $f_{i,j,k}$ 转移到 $f_{i+1,l,p}$。

最后询问一个 $m$ 的答案就是 $\sum_{1 \le n \le m} \sum_i f_{i,n,n} 2^{i-1}$。

然后我们发现第一维没有比较记，可以直接写到转移式里面，并且因为 $a$ 递增，我们按照值递增的顺序转移，因此式子变成了：

$$
f_{l,p} \gets f_{j,k} \times 2(l>j,p>k,\gcd(p,j)=k)
$$

答案就是 $\sum_{i=1}^m f_{i,i}$，于是我们只需要求出 $f_{*,*}$ 就可以做到 $O(1)$ 询问。

因为我们枚举值递增的顺序转移，所以 $l>j$ 这条限制没有用，就算有更新也不会影响答案，并且 $p>k$ 可以转化为 $p \ne k$。

于是式子可以写成：

$$
f_{l,p} \gets f_{j,k} \times 2(\gcd(p,j)=k,p \not= k)
$$

注意到 $p \mid l,k \mid p$，并且 $l$ 没有意义，我们枚举 $j,k$，然后利用容斥的方法让所有 $\gcd(\frac pk,\frac jk)=1$ 的 $p$ 所对应的 $f$ 都整体加上 $2f_{j,k}$ 即可，具体来说，我们按照计算 $\varphi$ 的方式，例如 $\frac jk=12=2^23$，发现我们先让 $f_p$ 第二维为所有 $k$ 的倍数的值加上 $2f_{j,k}$，然后让 $f_p$ 第二维为所有 $2k$ 和 $3k$（有的会被减去两次）的倍数的值减去 $2f_{j,k}$，最后让 $f_p$ 第二维为所有 $6k$（有的会被减去两次）的倍数的值加上 $2f_{j,k}$，根据容斥原理，这么做是对的。

因为要有让所有为 $a$ 的倍数的值加上 $num$，于是我们记 $p_a$ 表示 $\sum num$，然后查询 $f_{i,*}$ 的时候直接以 $\sum_{j \mid i} p_j$ 计算即可。

请注意：上述的过程一定要注意先后顺序，不能乱了。

最后就是初始化的时候 $f_{i,j} = 1$，满足 $j \mid i$ 即可（注意不要与前面的各种优化写在一起导致代码错误）。

考虑时间复杂度，设 $f(i)$ 表示 $i$ 因数个数，设 $g(i)$ 表示 $i$ 分解质因数之后有多少个不同的质因数，那么答案为：$\sum_{i=1}^m \sum_{j \mid i} (f(j)+2^{g(j)})$。

算出来可能有 $2 \times 10^8$ 次运算，跑得还可以。

代码如下，仅供参考，部分细节可能与题解内容中不一样，并且可能需要把 `vector` 替换掉卡一下常（尽管不换也可以稳定通过）：

```cpp
#include<bits/stdc++.h>
#define ll int
#define mod 998244353
#define N 1000005
using namespace std;
vector<ll> ps[N];
ll T,n,i,j,k,l,qzh[N],ans[N],val[N],val2[N],vis[N],id[N],cnt[N],res[N],cntt[N],now[N],bin[N*20],*pos(bin),*inv[N];
inline void add(ll &x,ll y){(x+=y)>=mod&&(x-=mod);}
inline void sub(ll &x,ll y){(x-=y)<0&&(x+=mod);}
inline ll q2(ll x){return (x<<1)>=mod?((x<<1)-mod):(x<<1);}
inline ll get_val(ll x){
	ll res = 0;
	for(ll i=0;i<cntt[x];i++) add(res,val[inv[x][i]]);
	(res+=val2[x])>=mod&&(res-=mod);
	return res;
}
inline void solve(){
	for(i=1;i<=1e6;i++) for(j=i;j<=1e6;j+=i) cntt[j]++;
	for(i=1;i<=1e6;i++) inv[i]=pos,pos+=cntt[i];
	for(i=1;i<=1e6;i++) for(j=i;j<=1e6;j+=i) inv[j][now[j]++]=i;
	for(i=2;i<=1e6;i++) if(!vis[i]) for(j=i;j<=1e6;j+=i) vis[j]=1,ps[j].push_back(i);
	for(i=1;i<=1e6;i++){
		ans[i] = (1+get_val(i))%mod,add(ans[i],ans[i-1]);
		for(j=0;j<cntt[i];j++){
			ll p = inv[i][j],p2 = i/p;
			ll num = q2((1+get_val(p))%mod);
			res[0] = p;
			for(k=0;k<(1<<ps[p2].size());k++){
				if(k) res[k]=res[k-(k&(-k))]*ps[p2][id[(k&(-k))]];
				if(cnt[k]&1) sub(val[res[k]],num);
				else add(val[res[k]],num);
			}
			sub(val2[p],num);
		}
	}
}
int main(){
	for(i=0;i<10;i++) id[1<<i]=i;
	for(i=0;i<(1<<10);i++) cnt[i]=__builtin_popcount(i);
	solve();
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}
	return 0;
}
```

---

