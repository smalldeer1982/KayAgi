# Converging Array (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ 1 \le q \le 10^5 $ . You can make hacks only if both versions of the problem are solved.

There is a process that takes place on arrays $ a $ and $ b $ of length $ n $ and length $ n-1 $ respectively.

The process is an infinite sequence of operations. Each operation is as follows:

- First, choose a random integer $ i $ ( $ 1 \le i \le n-1 $ ).
- Then, simultaneously set $ a_i = \min\left(a_i, \frac{a_i+a_{i+1}-b_i}{2}\right) $ and $ a_{i+1} = \max\left(a_{i+1}, \frac{a_i+a_{i+1}+b_i}{2}\right) $ without any rounding (so values may become non-integer).

 See notes for an example of an operation.It can be proven that array $ a $ converges, i. e. for each $ i $ there exists a limit $ a_i $ converges to. Let function $ F(a, b) $ return the value $ a_1 $ converges to after a process on $ a $ and $ b $ .

You are given array $ b $ , but not array $ a $ . However, you are given a third array $ c $ . Array $ a $ is good if it contains only integers and satisfies $ 0 \leq a_i \leq c_i $ for $ 1 \leq i \leq n $ .

Your task is to count the number of good arrays $ a $ where $ F(a, b) \geq x $ for $ q $ values of $ x $ . Since the number of arrays can be very large, print it modulo $ 10^9+7 $ .

## 说明/提示

The following explanation assumes $ b = [2, 1] $ and $ c=[2, 3, 4] $ (as in the sample).

Examples of arrays $ a $ that are not good:

- $ a = [3, 2, 3] $ is not good because $ a_1 > c_1 $ ;
- $ a = [0, -1, 3] $ is not good because $ a_2 < 0 $ .

One possible good array $ a $ is $ [0, 2, 4] $ . We can show that no operation has any effect on this array, so $ F(a, b) = a_1 = 0 $ .

Another possible good array $ a $ is $ [0, 1, 4] $ . In a single operation with $ i = 1 $ , we set $ a_1 = \min(\frac{0+1-2}{2}, 0) $ and $ a_2 = \max(\frac{0+1+2}{2}, 1) $ . So, after a single operation with $ i = 1 $ , $ a $ becomes equal to $ [-\frac{1}{2}, \frac{3}{2}, 4] $ . We can show that no operation has any effect on this array, so $ F(a, b) = -\frac{1}{2} $ .

## 样例 #1

### 输入

```
3
2 3 4
2 1
5
-1 0 1 -100000 100000```

### 输出

```
56
28
4
60
0```

# 题解

## 作者：syksykCCC (赞：25)

**UPD：修复了原来取值范围不严谨的问题。**

----

把 $a_i$ 和 $\frac{a_i + a_{i + 1} - b_i}{2}$ 做个比较，发现前者**小于等于**后者的条件为 $a_{i + 1} - a_{i} \ge b_i$。

把 $a_{i + 1}$ 和 $\frac{a_i + a_{i + 1} + b_i}{2}$ 做个比较，发现前者**大于等于**后者的条件为 $a_{i + 1} - a_i \ge b_i$。

发现这两个条件是一样的，也就是说，一次操作的本质是：

* 如果 $a_{i + 1} - a_i \ge b_{i}$，则**不会**发生变化。
* 如果 $a_{i + 1} - a_i < b_i$，则**会**发生变化。

更近一步的，如果发生了一次变化，那相邻两个数的差会变成什么呢？

$$ \frac{a_{i} + a_{i + 1} + b_{i}}{2} - \frac{a_{i} + a_{i + 1} - b_{i}}{2} = b_i $$

也就是说，相邻的两个数的差，从原本的 $< b_i$ 变成了 $ = b_i$，且这两个数的**和不变**。

设 $f_{1 \cdots n}$ 表示最终收敛的数组，必然对任意 $i$ 都存在 $f_{i+1} - f_i \ge b_i$。

并且如果 $f_{i + 1} - f_i > b_i$，则整个过程中，$a_i$ 和 $a_{i + 1}$ 之间就**从来没有发生过**赋值操作。

> 这是因为，如果发生了操作，那么这次操作后 $f_{i + 1} - f_{i}$ 就会变得等于 $b_i$，而且我们知道两个数的差只能从小于 $b_i$ 变成等于 $b_i$，而不能变成大于 $b_i$，所以最终无法满足 $f_{i + 1} - f_i > b_i$ 的条件。

以满足这种严格大于关系的点 $i$ 为断点，可以发现，$a_{1 \cdots i}$ 和 $a_{i + 1 \cdots n}$ 是完全**互相不影响**的。

现在要解决最棘手的一个问题，如何求出 $f_1$ 呢？

假设我们知道了第一个断点的位置是 $p$，那可以得到一个方程组：

$$ \begin{cases} f_{2} - f_{1} = b_{1} \\ f_{3} - f_{2} = b_{2} \\ \cdots \\ f_{p} - f_{p - 1} = b_{p - 1} \\ \sum\limits_{i = 1}^{p} f_i = \sum\limits_{i = 1}^{p} a_i \end{cases} $$

将 $f$ 看成未知数，则有 $p$ 个未知数，$p$ 个方程！于是我们可以手动解出 $f_1$ 的值：

$$ \begin{aligned} (f_1) + (f_1 + b_1) + (f_1 + b_1 + b_2) + \cdots & = \sum_{i = 1}^{p} a_i \\ f_1 \times p + \sum_{i = 1}^{p - 1}(p - i)b_i & = \sum_{i = 1}^{p} a_i \\ f_{1} & = \frac{\sum\limits_{i = 1}^{p} a_i - \sum\limits_{i = 1}^{p - 1}(p - i)b_i}{p} \end{aligned} $$

设 $sa_p = \sum\limits_{i = 1}^{p}a_i, sb_p = \sum\limits_{i = 1}^{p - 1}(p - i)b_i$，则 $f_1 = \frac{sa_p - sb_p}{p}$。

但问题是，我们并不知道 $p$ 是多少。正确的解决方法是，将每个位置都**尝试作为第一个端点**，取解出来的 $f_1$ 的**最小值**即可，也就是 $f_1 = \min \left\{ \frac{s a_i - sb_i}{i} \right\}$。

> 首先证明 $f_1 \ge \min \left\{ \frac{sa_i - sb_i}{i} \right\}$，这是因为必然**存在**某个前缀 $p$ 使得 $f_1 = \frac{sa_p - sb_p}{p}$，所以 $f_1$ 大于等于取任意 $p$ 时的最小值。 
>
> 然后证明 $f_1 \le \min \left\{ \frac{sa_i - sb_i}{i} \right\}$，这是因为对于任意前缀 $p$，如果 $f_1 \ne \frac{sa_p - sb_p}{p}$，就说明必然存在 $f_{i + 1} - f_i > b_i\ (i < p)$ 的位置。但因为 $\sum f$ 是保持不变的，为了使得**跨度变大**只能**减小初值**，得出 $f_1 < \frac{sa_p - sb_p}{p}$。

回到原题，现在变成了一个计数问题。即，能找到多少个序列 $a$，满足 $0 \le a_i \le c_i$，且 $\min \left\{ \frac{s a_i - sb_i}{i} \right\} \ge x$。

取 $\min$ 转化为任意，命题等价于，对任意前缀 $i$，都要满足：

$$ \frac{sa_i - sb_i}{i} \ge x \quad \Rightarrow \quad sa_i \ge i \cdot x + sb_i $$

当 $q = 1$ 时，不等式右边都是已知量，考虑一个 DP，用 $f_{i, j}$ 表示前 $i$ 项，和为 $j$ 的方案数。因为合法的 $a$ 必然是一个后缀，使用前缀和优化转移即可，单次转移 $O(1)$。

时间复杂度 $O(qn^2m)$，$m$ 是 $a$ 的上限。

现在考虑多组询问，不同的 $x$ 是否存在等价关系呢？

* 如果存在 $i$，满足 $ i \cdot x + sb_i > i \cdot m$，即 $x > \min\left\{\frac{i \cdot m - sb_i}{i}\right\}$，答案必然为 $0$。
* 如果任意 $i$，满足 $i \cdot x + sb_i \le 0$，即 $x \le \min\left\{ \frac{-sb_i}{i} \right\}$，答案必然为 $\prod(c_i + 1)$。

现在只需要特别考虑 $x \in \left(\min\left\{ \frac{-sb_i}{i} \right\}, \min\left\{\frac{i \cdot m - sb_i}{i}\right\}\right]$ 即可。

于是只有 $O(m)$ 种本质不同的询问，全部预处理丢 `map` 里即可。时间复杂度 $O(n^2m^2 + q \log m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105, MOD = 1e9 + 7;
int n, f[N * N], g[N * N], b[N], sb[N], c[N];
map<int, int> ans;
int Solve(int x)
{
	fill(g, g + N * N, 1);
	for(int i = 1, sumc = c[1], lim; i <= n; i++, sumc += c[i]) 
	{
		lim = i * x + sb[i]; memset(f, 0, sizeof(f));
		for(int j = max(0, lim); j < N * N; j++) f[j] = (g[j] - (j - c[i] - 1 >= 0 ? g[j - c[i] - 1] : 0) + MOD) % MOD;
		memset(g, 0, sizeof(g)); g[0] = f[0];
		for(int j = 1; j < N * N; j++) g[j] = (g[j - 1] + f[j]) % MOD;
	}
	return g[N * N - 1];
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	int prod = 1;
	for(int i = 1; i <= n; i++) { cin >> c[i]; prod = (ll)prod * (c[i] + 1) % MOD; }
	for(int i = 1; i < n; i++) cin >> b[i];
	for(int i = 1; i <= n; i++) for(int j = 1; j < i; j++) sb[i] += (i - j) * b[j];
	int lb = 0, rb = INT_MAX, m = *max_element(c + 1, c + n + 1);
	for(int i = 1; i <= n; i++) lb = min(lb, -((sb[i] - 1) / i + 1)), rb = min(rb, (i * m - sb[i] - 1) / i + 1);
	for(int i = lb; i <= rb; i++) ans[i] = Solve(i);
	int q; cin >> q;
	while(q--)
	{
		int x; cin >> x;
		if(x >= lb && x <= rb) cout << ans[x] << endl;
		else if(x > rb) cout << 0 << endl;
		else if(x < lb) cout << prod << endl;
	}
	return 0;
}
```

---

## 作者：CXY07 (赞：6)

> 题目链接：[CF1540C Converging Array](https://www.luogu.com.cn/problem/CF1540C2)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/313/)**

题意：

> 现在有长度为 $n$ 的数组 $a$ 和长度为 $n - 1$ 的数组 $b$，进行无穷次如下过程直至 $a$ 数组值收敛。

> - 选择一个数字 $i$。
> - 同时使 $a_i = \min(a_i, \frac{a_i + a_{i + 1} - b_i}{2})$，$a_{i + 1} = \max(a_{i + 1}, \frac{a_i + a_{i + 1} + b_i}{2})$（没有取整）。

> 定义 $F(a, b)$ 为操作完成后 $a_1$ 的值。

> 现在你知道数组 $b$ 和长度为 $n$ 的数组 $c$，保证 $\forall i \in [1, n],\ 0 \le a_i \le c_i$。

> 有 $q$ 组询问，每次问使 $F(a, b) \ge x$ 的数组 $a$ 有多少个。

> $2\le n\le 100,0\le b_i,c_i\le 100,1\le q\le 10^5,-10^5\le x\le 10^5$。

首先，对于上述操作，有几个比较基本的观察：

> 两个操作要么同时成功，要么同时失败。

第一个操作成功当且仅当 $2a_i>a_i+a_{i+2}-b_i$，第二个操作成功当且仅当 $2a_{i+1}<a_i+a_{i+1}+b_i$，这两个不等式显然等价。

> 进行任意次操作，$\sum_{i=0}^n a_i$ 保持不变。

因为 $\dfrac{a_i+a_{i+1}-b_i}{2}+\dfrac{a_i+a_{i+1}+b_i}{2}=a_i+a_{i+1}$。

> 一次操作成功，当且仅当 $|a_{i+1}-a_i|<b_i$，操作过后 $a_{i+1}-a_i=b_i$。

因为上述操作实际上可以描述为先取平均数，然后左右各走 $\dfrac{b_i}{2}$ 步。

于是，假设 $\{a_n\}$ “收敛”后变成 $\{f_n\}$，则 $\{f_n\}$ 需要满足以下条件：

- $\sum_{i=1}^n a_i=\sum_{i=1}^n f_i$。

- $\forall 1\le i<n, f_{i+1}\ge f_{i}+b_i$。

注意到，若对于任意 $1\le i<n$，$f_{i+1}=f_i+b_i$，又有 $\sum_{i=1}^n f_i$ 的限制，于是我们实际上可以解出 $\{f_n\}$。具体来说：

$$
f_i=f_1+\sum_{j=1}^{i-1} b_j
$$

$$
\sum_{i=1}^n a_i=\sum_{i=1}^n f=\sum_{i=1}^n(f_1+\sum_{j=1}^{i-1} b_j)
$$
$$
=f_1 \times n+\sum_{i=1}^{n-1}(n-i)\times b_i
$$

于是可以得到：

$$
f_1=\dfrac{\sum_{i=1}^n a_i-\sum_{i=1}^{n-1}(n-i)\times b_i}{n}
$$

但是，我们知道并不一定所有 $f_{i+1}=f_i+b_i$。不过，对于 $f_{i+1}>f_{i}+b_i$ 的情况，我们可以得知：在 $i$ 与 $i+1$ 之间**没有进行过操作**。

这是因为我们一次操作一定会使得 $f_{i+1}=f_i+b_i$，但最后 $f_{i+1}>f_i+b_i$，只能说明一开始 $a_i$ 与 $a_{i+1}$ 的差就已经 $>b_i$ 了。

于是，总存在一个前缀 $[1,p]$，满足 $\forall 1\le i<p,f_{i+1}=f_i+b_i$，且 $[p+1,n]$ 与 $[1,p]$ 是互不影响的。因此，如果我们已经得知了 $p$ 的确切值，那么 $f_1$ 的值就得到了确定，他应该是：

$$
\dfrac{\text{suma}_p-\text{sumb}_p}{p}
$$

其中：

$$
\text{suma}_p=\sum_{i=1}^p a_i,\ \text{sumb}_p=\sum_{i=1}^{p-1}(p-i)\times b_i
$$

不过实际上，$p$ 的取值是未知的。那应该怎么确定 $f_1$ 呢？

首先，由于一定存在一个合法的 $p$，所以：

$$
f_1\in\Big\{\dfrac{\text{suma}_p-\text{sumb}_p}{p}\ |\ p\in[1,n]\Big\}
$$

同时，假设对于一个前缀 $p$，他**不满足** $\forall 1\le i<p,f_{i+1}=f_i+b_i$，那么一定有：

$$
f_1<\dfrac{\text{suma}_p-\text{sumb}_p}{p}
$$

这是因为，前缀 $p$ 不满足一定是因为存在一个位置满足 $f_{i+1}>f_i+b_i$，则 $f_{i+1}$ 的大小超出了我们的预计。又 $f$ 的和是一定的，所以 $i$ 及其前面的部分**应该比预计的更小**。

于是，结合上述两条观察，我们可以得出一个厉害的结论：

$$
f_1=\min\Big\{\dfrac{\text{suma}_p-\text{sumb}_p}{p}\Big\}
$$

至此，我们得到了一种方式，能够快速通过 $\{a_n\}$、$\{b_n\}$ 来计算 $F(a,b)$（即 $f_1$）的值。

接下来考虑计数，$F(a,b)\ge x$ 实际上就是：

$$
\forall\ p\in[1,n],\ \dfrac{\text{suma}_p-\text{sumb}_p}{p}\ge x
$$

即：

$$
\text{suma}_p\ge \text{sumb}_p+p\times x
$$

这是一个背包的模型，设 $m$ 为 $a_i$ 的值域上界的话，对于单个 $x$ 进行求解的复杂度是 $\mathcal{O}(n^2m^2)$，容易通过前缀和优化的方式做到单次 $\mathcal{O}(n^2m)$。于是，我们便得到了一种 $\mathcal{O}(qn^2m)$ 的做法。

但在困难版中，$q\le 10^5$，这是无法接受的。考虑如何快速计算不同 $x$ 的答案。

感性地想，如果这个 $x$ 极小，导致甚至 $\{a_n\}$ 中全是 $0$ 都合法，那么便说明所有序列都是合法的，方案数是：

$$
\prod_{i=1}^n (c_i+1)
$$

需要满足什么条件？应该是：

$$
x\le \min\Big\{\dfrac{-\text{sumb}_p}{p}\Big\}
$$

即就算 $\{a_n\}$ 中全是 $0$ 仍然合法。相应的，如果这个 $x$ 极大，导致 $\forall\ 1\le i\le n,\ a_i=c_i$ 都不满足条件，则说明所有序列都是不合法的，答案为 $0$。他需要满足条件：

$$
x>\min\Big\{\dfrac{p\times m-\text{sumb}_p}{p}\Big\}
$$

因此，只有 $x\in \Big(\min\Big\{\dfrac{-\text{sumb}_p}{p}\Big\},\ \min\Big\{\dfrac{p\times m-\text{sumb}_p}{p}\Big\}\Big]$ 的部分是需要计算的，这里只有 $\mathcal{O}(m)$ 个取值！

因此，我们可以在 $\mathcal{O}(n^2m^2)$ 的时间内进行预处理，然后 $\mathcal{O}(1)$ 回答。

```cpp
//Code By CXY07 - It's My Fiesta.
#include<bits/stdc++.h>
using namespace std;

//#define FILE
#define int long long
#define randint(l, r) (rand() % ((r) - (l) + 1) + (l))
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define popc(x) __builtin_popcount(x)
#define inv(x) qpow((x), mod - 2)
#define lowbit(x) ((x) & (-(x)))
#define ull unsigned long long
#define pii pair<int, int>
#define LL long long
#define mp make_pair
#define pb push_back
#define scd second
#define vec vector
#define fst first
#define endl '\n'
#define y1 _y1

const int MAXN = 110;
const int MAXX = 2e5 + 10;
const int SIZ = 1e4 + 10;
const int INF = 2e9;
const double eps = 1e-6;
const double PI = acos(-1);
const int mod = 1e9 + 7;
//const int mod = 998244353;
//const int G = 3;
//const int base = 131;

int n, m, q, prod = 1, c[MAXN], b[MAXN];
int L, R, sav[MAXX], sumb[MAXN];
int dp[SIZ], sum[SIZ];
bool vis[MAXX];

template<typename T> inline bool read(T &a) {
	a = 0; char c = getchar(); int f = 1;
	while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
	while(c >= '0' && c <= '9') { a = a * 10 + (c ^ 48); c = getchar(); }
	return a *= f, true;
}

template<typename A, typename ...B>
inline bool read(A &x, B &...y) { return read(x) && read(y...); }

int calc(int x) {
	if(vis[x + (int)1e5]) return sav[x + (int)1e5];
	vis[x + (int)1e5] = true;
	memset(sum, 0, sizeof sum); 
	for(int i = 0; i <= n * m; ++i) sum[i] = 1;
	for(int i = 1; i <= n; ++i) {
		memset(dp, 0, sizeof dp);
		for(int j = 0; j <= n * m; ++j) {
			if(j < i * x + sumb[i]) continue;
			dp[j] = sum[j];
			if(j > c[i]) (dp[j] -= sum[j - c[i] - 1]) %= mod;
		}
		for(int j = 0; j <= n * m; ++j)
			sum[j] = (dp[j] + (j > 0 ? sum[j - 1] : 0)) % mod;
	}
	return sav[x + (int)1e5] = (sum[n * m] + mod) % mod;
}

signed main () {
#ifdef FILE
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
	read(n), m = 100; 
	for(int i = 1; i <= n; ++i) {
		read(c[i]);
		prod = prod * (c[i] + 1) % mod;
	}
	for(int i = 1; i < n; ++i) read(b[i]);
	L = R = INF;
	for(int i = 1, s = 0, si = 0; i <= n; ++i) {
		sumb[i] = (i * s - si + mod) % mod;
		(s += b[i]) %= mod, (si += b[i] * i) %= mod;
		L = min(L, -sumb[i] / i - 1);
		R = min(R, (i * m - sumb[i]) / i + 1);
	}
	read(q);
	while(q--) {
		int x; read(x);
		if(x < L) printf("%lld\n", prod);
		else if(x > R) puts("0");
		else printf("%lld\n", calc(x));
	}
	return 0;
}
```

---

## 作者：Kubic (赞：3)

首先分析一下这个非常奇怪的操作的一些性质。

$a_i=\min\{a_i,\dfrac{a_i+a_{i+1}-b_i}{2}\}$

$a_{i+1}=\max\{a_{i+1},\dfrac{a_i+a_{i+1}+b_i}{2}\}$

容易发现，这个操作在 $a_{i+1}-a_i<b_i$ 时会执行，且 $a_i'+a_{i+1}'=a_i+a_{i+1},a_{i+1}'-a_i'=b_i$。

设最终状态为 $A$。

题目说这个序列会收敛，那么最终状态一定满足 $\forall i\in [1,n),A_{i+1}-A_i\ge b_i$。

感性理解一下这个过程，对于相邻的两个数，如果 $a_{i+1}-a_i$ 比较小那么 $A_{i+1}-A_i=b_i$，否则那么最终差 $A_{i+1}-A_i>b_i$。

但我们不能停留在感性上，要用柿子把 $A_1$ 刻画出来。

令 $sa_t=\sum\limits_{i=1}^t a_i,sA_t=\sum\limits_{i=1}^t A_i$。

每一次操作一定是左边变小，右边变大，易得 $sA_t\le sa_t$。根据之前的推导容易知道 $A_{i+1}-A_i\ge b_i$。所以每一个 $t$ 都对 $A_1$ 有所限制，因为要保证 $sA_t\le sa_t$。如果 $A_1$ 过大，就不存在一组合适的 $A_{1\dots t}$ 满足条件。

那么我们考虑极限情况：$\forall i\in [1,t),A_{i+1}-A_i=b_i$。此时 $A_i=A_1+\sum\limits_{j=1}^{i-1} b_j$。可用 $a_t$ 表示出 $A_1$ 的范围。

令 $sb_t=\sum\limits_{i=1}^{t-1}\sum\limits_{j=1}^i b_j$。则 $A_1\le\dfrac{sa_t-sb_t}{t}$。也就是说 $A_1\le\min\{\dfrac{sa_t-sb_t}{t}\}$。

我们再取 $t$ 使得 $t$ 为满足 $\forall i\in [1,t),A_{i+1}-A_i=b_i$ 的最大值，那么下标在 $(t,n]$ 中的元素显然不会对 $A_1$ 产生任何影响。此时 $A_1=\dfrac{sa_t-sb_t}{t}$。

综上，$A_1=\min\{\dfrac{sa_t-sb_t}{t}\}$。

历经千辛万苦，我们终于把条件变得正常了！！1

此时可以将题目转化为：给定 $x$，求满足 $\forall t,\dfrac{sa_t-sb_t}{t}\ge x$ 的不同 $a$ 的方案数。

这个可以简单 $dp$ 解决。$dp_{i,j}$ 表示考虑到 $a_i$，当前 $sa_i=j$ 的方案数，前缀和优化转移即可。对于一个 $x$ 计算的复杂度为 $O(n\sum c_i)$。

但是 $q\le 10^5$？？？接下来这一步似乎卡了不少人，但实际上并不难想到（?）

方案数有上界 $\prod (c_i+1)$ 和下界 $0$。

令 $sc_t=\sum\limits_{i=1}^t c_i$。

达到下界时一定是 $x$ 特别大的时候，此时全部取到 $a_i=c_i$ 也无法满足条件。也就是存在至少一个 $t$ 使得 $\dfrac{sc_t-sb_t}{t}<x$。所以 $x>\min\{\dfrac{sc_t-sb_t}{t}\}$ 时答案全部是 $0$。

达到上界时一定时 $x$ 特别小的时候，此时全部取到 $a_i=0$ 也能满足条件。也就是满足 $\forall t,\dfrac{-sb_t}{t}\ge x$。所以 $x\le\min\{\dfrac{-sb_t}{t}\}$ 时答案全部是 $\prod (c_i+1)$。

容易发现剩下需要额外计算的情况数量 $\le\max\{\dfrac{sc_t}{t}\}\le\max\{c_i\}$。全部暴力用上面的 $dp$ 计算一遍，询问时直接 $O(1)$ 查表即可。总复杂度 $O(n\max\{c_i\}\sum c_i+q)$。

参考代码（变量名与题解差距非常大，请谨慎食用）：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 105
#define M 200005
#define MOD 1000000007
const int lim=1e5;
int n,m,L=lim,R=lim,a[N],b[N],ans[M],dp[N*N],s[N*N];
int f(int x,int y) {return x>0?x/y:-(-x-1)/y-1;}
int slv(int x)
{
	int res=0;for(int i=0;i<=a[n];++i) dp[i]=0;dp[0]=1;
	for(int i=1,t;i<=n;++i)
	{
		for(int j=0;j<=a[n];++j)
			s[j]=(dp[j]+(j?s[j-1]:0))%MOD,dp[j]=0;
		for(int j=max(b[i]+x*i,0);j<=a[n];++j)
			t=a[i]-a[i-1],dp[j]=(s[j]-(j>t?s[j-t-1]:0))%MOD;
	}for(int i=0;i<=a[n];++i) res=(res+dp[i])%MOD;
	return (res+MOD)%MOD;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),a[i]+=a[i-1];
	for(int i=2;i<=n;++i) scanf("%d",&b[i]),b[i]+=b[i-1];
	scanf("%d",&m);for(int i=2;i<=n;++i) b[i]+=b[i-1];
	for(int i=1;i<=n;++i)
		L=min(L,f(-b[i],i)),R=min(R,f(a[i]-b[i],i));
	L=max(L,-lim);for(int i=L;i<=R;++i) ans[lim+i]=slv(i);
	for(int i=1,x;i<=m;++i)
		scanf("%d",&x),printf("%d\n",ans[lim+max(x,L)]);return 0;
}
```

---

## 作者：xcyle (赞：3)



经过观察不难发现一些最终序列的特征：

- $a_i - a_{i - 1} \ge b_{i - 1}$

而每一次有效操作显然会同时更改两个位置的值， 注意到它们的和不变，那么本质上就是把他们差变为 $b_i$。



考虑一种简单的初始情况：

$\forall i, a_i - a_{i - 1}<b_{i - 1}$

由于无限次操作会不断地均摊这些东西，显然最终任意两个的差都是对应的 $b$，容易列方程求得每一个位置的值

然而如果初始状态存在 $\forall i, a_i - a_{i - 1}\le b_{i - 1}$，需要另当别论。因为按这种地方划分后相邻两块东西可能拼在一起也可能不会。

自闭了，于是我又看眼题目，只考虑 $a_1$ 的值？那好办了

可以通过以下方法检查一个序列：考察每个前缀拼起来后 $a_1$ 是否合法。无论它们是否真的拼起来，我们都默认它们拼起来。因为就算不是不会影响结果。

因此对于固定的询问，问题转化为每个前缀和都有一个下界，背包即可，可以前缀和优化。时间复杂度 $O(n^3)$

至此可以通过C1

当询问变多了，发现 $x$ 的值域和询问数差不多，因此可以预处理每一个询问的答案。

不难注意到大部分的询问很特别：如果 $x$ 很大，可能出现每个前缀和下界极大，即答案为0；如果 $x$  很小，可能出现没个前缀和下界极小，即答案为 $\prod c_i + 1$。我们称除了上述两种情况之外的询问为“有意义的”。

结论是“有意义的”的只有 $O(100)$ 个，也很显然，单独看每一个前缀，在它的意义下“有意义的”大概是 $O(100)$ 个连续的，而我们要对每一个前缀的“有意义的”区间右端点取min，因此最多只有 $O(100)$ 个。总时间复杂度 $O(n^4)$

至此可以通过C2


---

vp的时候B调了一年于是没时间做C呜呜呜。C1还是好过的，C2或许是一个常用的套路？

---

## 作者：Alex_Eon (赞：1)

### Change log

- 2024.1.18 修改不严谨格式。

#### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)

#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Ksy/solution-cf1540c2)

### 主体思路：性质+DP

### 复杂度：$O(n^2V^2)$

其中 $V$ 是 $a$ 的取值上界，即 $\max\{c_i\}$。

### 完整思路

修改是神秘的，考虑发掘其一些性质，记一次操作为 $(a_i, a_{i + 1})$。

首先其意义可以感性理解为将 $a_i, a_{i + 1}$ 差距根据平均数拉开至 $b_i$，如果 $a_{i + 1} - a_i \ge b_i$ 那么这次操作不会改变任何值。

所有项的和永远是不变的。

考虑当 $a_{i + 1} - a_i < b_i$ 时操作会发生什么，$a_{i + 1} - a_i$ 变为 $b_i$ ，并且 $a_{i + 2} - a_{i + 1},a_i - a_{i - 1}$ 减小，如果 $a_{i + 2}, a_{i - 1}$ 存在的话。

想象这样一种情况，存在某一个 $a_{t + 1} - a_t$ 是极大的，使得首先我们无法通过操作 $(a_t, a_{t + 1})$ 来减小两者的差，并且通过操作 $(a_{t - 1}, a_t),(a_{t +1}, a_{t + 2})$ 也无法使得 $a_{t + 1} - a_t < b_t$。

这样的情况会使得操作断层，即 $t$ 以及之前的位置与 $t + 1$ 以及以后的位置操作时不会互相影响，因为我们只需要求最后 $a_1$ 的值，所以只需要考虑第一个断点 $t$ 之前的所有元素。

现在来考虑一下序列收敛后的形态，设序列 $s$ 为 $a$ 进行操作后收敛为的序列，容易知道 $s$ 满足 $s_{i + 1} - s_i \ge b_i$，其中 $s_{i + 1} - s_i > b_i$ 的位置就是刚才所说差值极大的位置，我们假设已知当前最靠前的差值极大的位置 $t$（即 $s_{t + 1} - s_t > b_t$），于是可以得到以下方程组：

$$
\begin{cases} 
s_{2} - s_{1} = b_{1} \\ 
s_{3} - s_{2} = b_{2} \\ 
\cdots \\ 
s_{t} - s_{t - 1} = b_{t - 1} \\ 
\sum\limits_{i = 1}^{t} s_i = \sum\limits_{i = 1}^{t} a_i 
\end{cases} 
$$

可以通过将 $s_1$ 从上往下依次代入每个方程解出其值：
$$
s_1 = \frac{\sum \limits_{i = 1}^t a_t - \sum \limits_{i = 1}^{t - 1} (t - i)b_i}{t}
$$
但我们并不知道 $t$ 的取值，我们尝试枚举 $t$，可以求解出 $n - 1$ 个 $s_1$ 的值，现有结论其中最小的那个 $s_1$ 即真实的 $s_1$。

换种理解方式，首先对于固定的 $a$ 序列，其变换后的形态 $s$ 是固定的，但我们并不好求出 $s$ 的每个值，假设 $t'$ 为 $s$ 中真实的满足差极大的那个位置，$t$ 为我们枚举的位置，现在的结论是当 $t=t'$ 时，我们求出的 $s_1$ 是最小的，所以我们可以从所有的 $s_1$ 中取最小值作为答案。

简单证明这个结论。有 $s_{i + 1} - s_i \ge b_i$ 即 $s_i + b_i \le s_{i + 1}$，可以继续推导至 $s_{i - 1} + b_{i - 1} + b_i \le s_{i + 1}$，以此类推可以有 $s_1 + \sum \limits_{j = 1}^{i - 1} b_j \le s_i$，将 $s_i$ 求和可以有不等式（$i$ 为任意 $1 \le i \le n$ 都成立）：
$$
\sum \limits_{j = 1}^i (s_1 + \sum \limits_{k = 1}^{j - 1} b_k) \le \sum \limits_{j = 1}^i s_j = \sum \limits_{j = 1}^i a_j
$$

化简左侧部分：
$$
\sum \limits_{j = 1}^i (s_1 + \sum \limits_{k = 1}^{j - 1} b_k) = i \cdot s_1 + \sum \limits_{j = 1}^{i - 1} (i - j)b_j
$$
于是有：
$$
i \cdot s_1 + \sum \limits_{j = 1}^{i - 1} (i - j)b_j \le \sum \limits_{j = 1}^i a_j
$$
化简可得：
$$
s_1 \le \frac{\sum \limits_{j = 1}^i a_i - \sum \limits_{j = 1}^{i - 1} (i - j)b_j}{i}
$$

方便起见，设 $sa_t = \sum\limits_{i = 1}^t a_t, sb_t = \sum \limits_{i = 1}^{t - 1} (t - i)b_i$。

现在问题转化为求有多少个序列 $a$，满足 $0 \le a_i \le c_i \land \min \limits_{i = 1}^n\{\frac{sa_i - sb_t}{i}\} \ge x$。

经典转化，相当于求序列需要满足任意项 $i$ 满足 $\frac{sa_i - sb_t}{i} \ge x$ 即 $sa_i \ge x \cdot i + sb_i$。

设 $f_{i, j}$ 表示前 $i$ 项，总和为 $j$ 的方案数。

对于上述不等式显然和越大越容易满足不等式，所以对于固定的 $i, j$ 来说，满足条件的 $a_i$ 为一个后缀，可以用前缀和优化转移。

转移方程是简单的，略过。

每次询问尝试做一遍 DP，复杂度来到 $O(qn^2V)$，可以通过简单版。

考虑询问 $x$ 的上下界。

当 $x$ 特别大的时候，$a_i$ 全取到上界 $c_i$ 仍然无法满足条件，即存在 $x > \frac{sc_i - sb_i}{i}$，等价于 $x > \min \{\frac{sc_i - sb_i}{i}\}$ 时，答案为 $0$。其中 $sc_i$ 为 $a_i$ 上界 $c_i$ 的前缀和。

当 $x$ 特别小的时候，$a_i$ 全取到下界 $0$，即任意 $i$ 都满足 $\frac{-sb_i}{i} \ge x$，等价于 $x \le \min\{\frac{sb_i}{i}\}$ 时，答案为 $\prod\limits_{i = 1}^{n} (c_i +1) $。

这样 $x$ 可取的个数可以缩小到 $V$ 级别（$\max\{c_i\}$），加一个记忆化即可。

代码是简单的，就不放了。

---

## 作者：hsaht2426 (赞：1)

#### 前言：

难的\*2900。

#### 思路：

显然我们应该先研究给定 $a$ 如何判定最终的 $a_1'$ 是否小于 $x$。

首先的想法是手摸小数据，但是这东西比 ARC126E 还难摸。所以想简化只能找**必要条件**。问题是这东西不好构造。

那么一步一步来。设最终序列为 $d$。**注意到**操作两边 $\max/\min$ 的是同时取到极值的。

- **注意到**和：每次操作不会改变两数的和，所以有 $\sum\limits_{i=1}^{n} a_i = \sum\limits_{i=1}^{n} d_i$。

- **注意到**差：最终一定会改变差小于 $b_i$ 的位置，所以有 $d_i-d_{i-1} \ge b_i$，$d_1 \ge x$。

三个量，两个条件，**这启发我们消元消去 $d$**。

所以现在我们有 $\sum_{i=1}^n a_i = \sum_{i=1}^n d_i \ge ix+\sum_{i=1}^{n-1}(n-i) \cdot b_i$，显然它是一个必要条件。那它是否充分呢？很遗憾简单手摸后发现并不是。

但是后面的式子事实上适用范围更广，即
 $\sum_{j=1}^id_j \ge ix+\sum_{j=1}^{i-1}(i-j) \cdot b_i$，这启发我们考虑 $a$ 与 $d$ 的大小关系。

- **注意到**大小：将任意一组操作序列划分为左边操作，右边操作与对两者的操作，由上文可知前两者对和均不影响，而对两者的操作总会使前缀的和变小，于是有 $\sum_{j=1}^ia_j \ge \sum_{j=1}^id_j$。

那么现在我们有了 $\sum_{j=1}^ia_j \ge ix+\sum_{j=1}^{i-1}(i-j) \cdot b_i$，它是否充分呢？是的，若某一时刻 $a$ 不满足该条件，则存在 $\sum_{j=1}^ia_j < \sum_{j=1}^id_j$，矛盾。

得到此充要条件后，注意到我们可以直接处理含 $c$ 的问题了。大力 $O(n^4)$(视 $n,v$ 同级，此文其他复杂度同理) 背包即可通过 $C1$。

对于 $C2$，$O(tn^4)$ 无法通过，使用前缀和优化背包过程，最终 $O(tn^3)$ 仍无法通过。考虑 $\text{DP}$ 状态已达 $O(n^3)$ (笔者太菜不会多项式)，我们必须**裁剪**询问。

考虑**特殊**值，当 $x$ 极小时，此时有答案为 $\prod_{i=1}^n(c_i+1)$；$x$ 极大时，此时有答案为 $0$，发现可以把大于某个上界的与小于某个下界的 $x$ **单独分出来处理查询**。

那么这个上下界是多少？回到式子 $\sum_{j=1}^ia_j \ge ix+\sum_{j=1}^{i-1}(i-j) \cdot b_i$，把已知量套进来 $\sum_{j=1}^ic_j \ge ix+\sum_{j=1}^{i-1}(i-j) \cdot b_i$，所以有 $0 \le ix+\sum_{j=1}^{i-1}(i-j) \cdot b_i \le iV$，即 $-\frac{\sum_{j=1}^{i-1}(i-j) \cdot b_i}{i} \le x \le V-\frac{\sum_{j=1}^{i-1}(i-j) \cdot b_i}{i}$。$i=n$ 时显然为最终上下界(自证不难)。

上下界内暴力与处理即可 $O(1)$ 回答询问。总时间复杂度为 $O(n^4+q)$。

[代码](https://codeforces.com/contest/1540/submission/233072353)

---

## 作者：FZzzz (赞：1)

考虑所谓“converge”的实际意义。设第 $i$ 位收敛于 $f_i$，则根据一般“收敛”的定义，无论如何对序列 $f$ 进行操作，都无法改变任何一位。那么则可以定义此题中的“收敛”为：对序列 $a$ 进行有限多次有效操作后，可以证明（题目给出，具体如何证明并不重要，有兴趣的读者可以自行思考）最后会得到唯一一个不可进行有效操作的序列 $f$，则称 $a$ 收敛于 $f$。

考虑题中所说操作的本质。不难发现对任意 $1\le i<n$，对 $i$ 进行一次操作即为保持 $a_i+a_{i+1}$ 不变，同时令 $a_{i+1}-a_i$ 对 $b_i$ 取 max。故，对于任意 $1\le i<n$，有 $f_{i+1}-f_i\ge b_i$。

注意到，对 $i$ 进行一次有效操作会使 $a_{i+1}-a_{i}$ 变为 $b_i$，同时使 $a_i-a_{i-1}$ 和 $a_{i+2}-a_{i+1}$（如果存在）变小，所以一次有效操作永远不会使一个已经大于 $b_i$ 的 $a_{i+1}-a_i$ 变得更大。

我们设 $i$ 为第一个满足 $f_{i+1}-f_i>b_i$ 的 $i$，那么可以得到，对于任意 $1\le j<i$，有 $f_{j+1}-f_j=b_j$。由上面的结论，$i$ 永远没有被进行过有效操作，故我们可以把 $1$ 到 $i$ 和 $i+1$ 到 $n$ 分成两部分来看，则 $\sum\limits_{j=1}^if_j=\sum\limits_{j=1}^ia_j$，即 $\sum\limits_{j=1}^i(f_1+\sum\limits_{k=1}^{j-1}b_j)=\sum\limits_{j=1}^ia_j$。令 $a$ 的前缀和为 $sa$，$b$ 的前缀和的前缀和为 $sb$，解得 $f_1=\dfrac{sa_i-sb_{i-1}}i$。

由上面的推导可知，必定存在一个 $i$ 使得 $f_1=\dfrac{sa_i-sb_{i-1}}i$。又由于对于任意 $i$，$f_{i+1}-f_i\ge b_i$，则对于任意 $i$，$\sum\limits_{j=1}^i(f_1+\sum\limits_{k=1}^{j-1}b_j)\le\sum\limits_{j=1}^if_j\le\sum\limits_{j=1}^ia_j$，$f_1\le\dfrac{sa_i-sb_{i-1}}i$。综上，我们可以得到 $f_1=\min\limits_{i=1}^n\dfrac{sa_i-sb_{i-1}}i$。

那么回到原题，现在问题就转化为了求使得 $\min\limits_{i=1}^n\dfrac{sa_i-sb_{i-1}}i\ge x$ 的序列 $a$ 数。即，对于任意 $i$，满足 $sa_i-sb_{i-1}\ge ix$ 的序列 $a$ 数。这可以通过简单的 dp 求出：设 $dp_{i,j}$ 为现在填到第 $i$ 位，$sa_{i-1}=j$，并且假设前面已经填过的部分全部合法，此时的方案数。转移时算出 $sa_i$ 的上下界，然后可以利用前缀和 $O(1)$ 转移。假定值域是 $O(n)$ 级别，对一个确定的 $x$ 进行 dp 的时间复杂度是 $O(n^3)$。

其他题解都说有意义的 $x$ 的下界是 $\min\limits_{i=1}^n-\dfrac{sb_{i-1}}i$，但是实际上我们可以发现 $\dfrac{sb_{i-1}}i$ 是不减的（读者自证不难），所以下界其实就是 $-\dfrac{sb_{n-1}}n$，上界同理。至此，问题可以 $O(n^4)$ 预处理，$O(1)$ 单次询问完成。空间复杂度可以优化到 $O(n^2)$，但我的实现是 $O(n^3)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=100+5;
int n,c[maxn],b[maxn],q;
int sb[maxn];
typedef long long ll;
const ll mod=1e9+7;
ll dp[maxn+5][2][maxn*maxn],s[maxn*maxn];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	for(int i=1;i<=n;i++) c[i]=readint();
	for(int i=1;i<n;i++) b[i]=readint();
	for(int i=1;i<n;i++) sb[i]=sb[i-1]+b[i];
	for(int i=1;i<n;i++) sb[i]+=sb[i-1];
	ll prod=1;
	for(int i=1;i<=n;i++) prod=prod*(c[i]+1)%mod;
	int mn=-sb[n-1]/n-1,mx=maxn-sb[n-1]/n+1;
	for(int i=mn;i<=mx;i++){
		for(int j=0;j<maxn*maxn;j++) dp[i-mn][(n+1)%2][j]=1;
		for(int j=n;j>0;j--){
			s[0]=dp[i-mn][(j+1)%2][0];
			for(int k=0;k<maxn*maxn;k++)
				s[k]=(s[k-1]+dp[i-mn][(j+1)%2][k])%mod;
			for(int k=0;k<maxn*maxn;k++){
				int l=max(k,i*j+sb[j-1]),r=min(k+c[j],maxn*maxn-1);
				if(l>r) dp[i-mn][j%2][k]=0;
				else dp[i-mn][j%2][k]=(s[r]-(l?s[l-1]:0)+mod)%mod;
			}
		}
	}
	int q=readint();
	while(q--){
		int x=readint();
		if(x<mn) printf("%lld\n",prod);
		else if(x>mx) printf("0\n");
		else printf("%lld\n",dp[x-mn][1][0]);
	}
	return 0;
}
```

---

