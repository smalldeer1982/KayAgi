# [AGC036F] Square Constraints

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc036/tasks/agc036_f

整数 $ N $ が与えられます。 $ (0,1,\cdots,2N-1) $ の順列 $ (P_0,P_1,\cdots,P_{2N-1}) $ であって、次の条件を満たすものの個数を求めてください。 ただし、答えは非常に大きくなることがあるので、$ M $ で割ったあまりを求めてください。

- 条件: すべての $ i\ (0\ \leq\ i\ \leq\ 2N-1) $ について、$ N^2\ \leq\ i^2+P_i^2\ \leq\ (2N)^2 $ が成り立つ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 250 $
- $ 2\ \leq\ M\ \leq\ 10^9 $
- 入力される値はすべて整数である。

### Sample Explanation 1

条件を満たす順列は、以下の $ 4 $ つです。 - $ (2,3,0,1) $ - $ (2,3,1,0) $ - $ (3,2,0,1) $ - $ (3,2,1,0) $

## 样例 #1

### 输入

```
2 998244353```

### 输出

```
4```

## 样例 #2

### 输入

```
10 998244353```

### 输出

```
53999264```

## 样例 #3

### 输入

```
200 998244353```

### 输出

```
112633322```

# 题解

## 作者：Sol1 (赞：28)

upd. 感谢 Yoralen 的提醒，有一个地方连乘打成了连加，现已修正。

---

EI 在课上讲的神仙题，掉线了一节课之后回家补上了。

## 0 转化

题目的要求相当于：

![](https://cdn.luogu.com.cn/upload/image_hosting/vnzw70m1.png)

在两个圆之间的圆环区域中放置 $2n-1$ 个车，要求车都放在整点上，且互不攻击，求方案数，任意模数。

## 1 弱化

如果里面的圆不存在，此时方案数是多少？

为了方便，记 $L_i=\lceil\sqrt{n^2-i^2}\rceil$，$R_i=\lfloor\sqrt{4n^2-i^2}\rfloor$。

![](https://cdn.luogu.com.cn/upload/image_hosting/tyeoqv1h.png)

此时可以在圆内画出图中的几条线段。

显然，每一个车放在一条线段上，并且不能在同一横排。

那么就先考虑最短线段（即第 $2n-1$ 条线段）上面的车，此时有 $R_{2n-1}+1$ 种方案。

在决策完这个车放在哪里之后，剩下的每一条线段都会少一个可以放的位置。

对第二短的线段重复一遍这个过程，可以发现也会让剩下的每一条线段少一个可以放的位置。

因此，如果设 $R$ 排序后的数组为 $R'$，那么方案数就是：

$$\prod_{i=0}^{2n-1}R'_i-i+1$$

## 2 容斥

既然对于没有下限的问题有了一个快速解法，那么这个解法是否有可能应用到有下限的问题中呢？

不满足要求的方案数也是前缀，这引诱我们进行容斥。（引用 EI 原话）

如果恰有 $k$ 个元素的上界是 $L_i-1$，那么这个方案数对答案的贡献就是 $(-1)^k\times f_k$。

考虑 DP 出 $f_k$。

## 3 DP

因为现在上界是 $L_i-1$，所以 $[0,n)$ 内的元素取关键字为 $L_i-1$，$[n,2n)$ 内的元素取关键字为 $R_i$ 进行排序。

现在我们得到了一个排好序的数组，就可以进行 DP 了。

设 $f_{i,j}$ 为 DP 到前 $i$ 个，并且有 $j$ 个选择 $L-1$ 作为上界的元素的总方案数。

显然有 $f_{0,0}=1$。

下面考虑每一个元素。

如果这个元素没有下界，即原本处于区间 $[n,2n)$ 之间，那么它的方案数可以这么考虑：

- 原本有 $R_i+1$ 个方案；
- 它前面的选择 $L-1$ 的，由于排序保证了它小于 $R_i$，所以每一个限制掉一个方案。这类会限制掉 $j$ 个方案；
- 它前面的没有下界的，同样是由于排序；这个需要在 DP 过程中统计，设其为 $c_1$。

所以可行的决策数为 $R_i+1-j-c_1$。有转移：

$$f_{i+1,j}\leftarrow f_{i,j}\cdot(R_i+1-j-c_1)$$

然后考虑有下界的情况。这类要分开讨论。

如果取上界为 $L_i-1$，则：

- 原本有 $L_i$ 个方案；
- 它前面的选择 $L-1$ 的和没有下界的，限制住 $c_1+j$ 个方案。

可行决策有 $L_i-c_1-j$ 个。有转移：

$$f_{i+1,j+1}\leftarrow f_{i,j}\cdot (L_i-c_1-j)$$

如果取上界为 $R$，则：

- 原本有 $R_i+1$ 个方案；
- **关键性质：由于在 $[0,n)$ 内，最小的 $R$ 是 $\sqrt 2n$ 大于最大的 $L$，所以任何有下界且选择 $L-1$ 的元素都一定会影响这里的决策。**
- 由于这个性质的存在，所以这一类的限制为 $k$。
- 此时的 $R$ 大于所有满足 $i\in [n,2n)$ 的 $R_i$，每一个都产生限制，限制为 $n$。
- 如果有下界的取上界为 $R$，那么在这个元素之前的也会影响决策。为了统计这个方案数，可以统计之前有下界的元素数量，设其为 $c_2$，则这里限制为 $c_2-j$。

故可行决策有 $R_i+1-n-k-c_2+j$ 个。转移：

$$f_{i+1,j}\leftarrow f_{i,j}\cdot (R_i+1-n-k-c_2+j)$$

答案即为 $f_{2n,k}$。

DP 的复杂度为 $O(n^2)$，前面还要枚举一个 $k$，所以最终时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$，可以通过本题。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

int n, mod, dp[505][505];
pair <int, int> p[505];

inline void Prefix() {
	for (int i = 0;i < n;i++) {
		p[i + 1].first = ceil(sqrt(n * n - i * i)) - 1;
		p[i + 1].second = floor(sqrt(4 * n * n - i * i));
		if (p[i + 1].second > 2 * n - 1) p[i + 1].second = 2 * n - 1;
	}
	for (int i = n;i < 2 * n;i++) {
		p[i + 1].first = floor(sqrt(4 * n * n - i * i));
		if (p[i + 1].first > 2 * n - 1) p[i + 1].first = 2 * n - 1;
		p[i + 1].second = 0;
	}
	sort(p + 1, p + 2 * n + 1);
}

inline int Calc(int k) {
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	int limcnt = 0, cntr = 0;
	for (int i = 1;i <= 2 * n;i++) {
		if (p[i].second == 0) {
			for (int j = 0;j <= limcnt;j++) dp[i][j] = (dp[i][j] + 1ll * dp[i - 1][j] * (p[i].first - cntr - j + 1) % mod) % mod;
			cntr++;
		} else {
			for (int j = 0;j <= limcnt;j++) {
				dp[i][j] = (dp[i][j] + 1ll * dp[i - 1][j] * (p[i].second + 1 - n - k - limcnt + j) % mod) % mod;
				dp[i][j + 1] = (dp[i][j + 1] + 1ll * dp[i - 1][j] * (p[i].first - cntr - j + 1) % mod) % mod;
			}
			limcnt++;
		}
	}
	return dp[2 * n][k];
}

inline void Solve() {
	long long ans = 0;
	for (int i = 0;i <= n;i++) {
		if (i & 1) ans = (ans - Calc(i) + mod) % mod;
		else ans = (ans + Calc(i)) % mod;
		//printf("%d\n", Calc(i));
	}
	printf("%lld", ans);
}

int main() {
	n = qread(); mod = qread();
	Prefix();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：xht (赞：10)

## [Square Constraints](https://atcoder.jp/contests/agc036/tasks/agc036_f)

### 题意

- 给定 $n$，求满足以下条件的 $0 \sim 2n-1$ 的排列 $p_{0\dots2n-1}$ 的个数。
  - 对于 $i \in [0,2n-1]$，满足 $n^2 \le i^2 + p_i^2 \le (2n)^2$。
- $n \le 250$，答案对 $P$ 取模。

### 题解

本质上，这依然是一个 $p_i \in [l_i,r_i]$ 的计数问题。

在没有下界限制的情况下，我们有个经典的做法是，将 $r_i$ 从小到大排序，这样当考虑第 $i$ 个数时，由于前面的 $r$ 都 $\le r_i$，因此无论前面怎么填，第 $i$ 个数的方案数都为 $r_i + 1 - i$（编号从 $0$ 开始），总方案数为 $\prod_{i=0}^{2n-1} r_i + 1 - i$。

在有下界时，我们可以考虑容斥，设 $f(k)$ 表示至少有 $k$ 个数小于下界时的方案数，则答案为 $\sum_{k=0}^{2n} (-1)^kf(k)$。

回到本题，题意的约束条件比较奇怪，考虑将它变得直观一点就是：

- 以原点为圆心在第一象限画两个半径分别为 $n,2n$ 的 $1/4$ 圆，对于 $i \in [0,2n-1]$，$(i,p_i)$ 必须在这两个 $1/4$ 圆之间（含圆上）。

于是我们有 $l_{n\dots2n-1} = 0$，因此只有对于 $i \in [0,n-1]$ 才有可能 $p_i < l_i$。

考虑枚举若干个 $i$ 要求 $p_i < l_i$，则此时相当于没有下界限制的计数，用上面的方法即可。

然而显然我们不能枚举每个 $i \in [0, n-1]$ 是否要求 $p_i < l_i$，有没有什么办法可以直接计算出 $f(k)$ 呢？

注意到对 $r$ 排序后求 $\prod_{i=0}^{2n-1} r_i + 1 - i$，本质上相当于对于每个 $i$，其贡献为，$\le r_i$ 的数的个数（$r_i+1$ 个），减去比 $r_i$ 小的限制的个数（$r_i$ 相同则钦定一个顺序）。

考虑：

- 对于 $i \in[0,n-1]$，以 $l_i - 1$ 为第一关键字，$r_i$ 为第二关键字。
- 对于 $i \in [n, 2n-1]$，以 $r_i$ 为第一关键字，$l_i-1$ 为第二关键字。

排序，设排序后的序列为 $q_{1\dots2n}$（注意，这里是从 $1$ 开始编号，也只有这里从 $1$ 开始编号）。

考虑 DP，设 $f_{i,j}$ 表示对于 $q_{1\dots i}$ 均满足 $\le r$，且其中有 $j$ 项满足 $< l$ 时对答案的贡献。

设 $q_{1\dots i-1}$ 中 $\in[0,n-1]$ 的有 $t$ 个，考虑如何转移，观察上面那个直观的限制图：

- 若 $q_i \in [0,n-1]$，且只要求 $p_{q_i} \le r_{q_i}$，其贡献为：
  $\le r_{q_i}$ 的数（$r_{q_i} + 1$ 个），减去比 $r_{q_i}$ 小的限制的个数：

  - 所有 $i \in [n,2n-1]$ 的 $r_i$（$n$ 个）
  - $q_{1\dots i-1}$ 中 $\in[0,n-1]$ 的 $q$（$t$ 个）
  - $q_{i+1\dots 2n-1}$ 中 $\in [0,n-1]$ 且要求 $<l$ 的 $q$（$k-j$ 个）

  转移：$f_{i,j}\leftarrow f_{i-1,j} \cdot (r_{q_i} + 1 - (n + t + k - j))$。

- 若 $q_i \in [0,n-1]$，且要求 $p_{q_i} < l_{q_i}$，其贡献为：
  $< l_{q_i}$ 的数（$l_{q_i}$ 个），减去比 $l_{q_i}-1$ 小的限制的个数：

  - $q_{1\dots i-1}$ 中 $\in [n,2n-1]$ 的 $q$（$i-1-t$ 个）
  - $q_{1\dots i-1}$ 中 $\in[0,n-1]$ 且要求 $<l$ 的 $q$（$j-1$ 个）

  转移：$f_{i,j} \leftarrow f_{i-1,j-1} \cdot (l_{q_i} - (i-1-t+(j-1)))$。

- 若 $q_{n,2n-1}$，其贡献为：
  $\le r_{q_i}$ 的数（$r_{q_i} + 1$ 个），减去比 $r_{q_i}$ 小的限制的个数：

  - $q_{1\dots i-1}$ 中 $\in [n,2n-1]$ 的 $q$（$i-1-t$ 个）
  - $q_{1\dots i-1}$ 中 $\in[0,n-1]$ 且要求 $<l$ 的 $q$（$j$ 个）

  转移：$f_{i,j} \leftarrow f_{i-1,j} \cdot (r_{q_i} + 1 - (i-1-t+j))$。

时间复杂度 $\mathcal O(n^3)$。

### 代码

```cpp
const int N = 507;
int n, l[N], r[N], q[N];
modint f[N][N], ans;

inline modint calc(int k) {
	f[0][0] = 1;
	for (int i = 1, t = 0; i <= n << 1; t += q[i] < n, i++)
		for (int j = 0; j <= min(min(i, k), t + (q[i] < n)); j++)
			if (q[i] < n) f[i][j] = f[i-1][j] * (r[q[i]] + 1 - (n + t + k - j)) + (j ? f[i-1][j-1] * (l[q[i]] - (i - 1 - t + (j - 1))) : 0);
			else f[i][j] = f[i-1][j] * (r[q[i]] + 1 - (i - 1 - t + j));
	return f[n<<1][k];
}

int main() {
	rd(n, P);
	for (int i = 0; i < n << 1; i++)
		l[i] = max(0, (int)ceil(sqrt(n * n - i * i))),
		r[i] = min(2 * n - 1, (int)floor(sqrt(4 * n * n - i * i))),
		q[i+1] = i;
	sort(q + 1, q + (n << 1 | 1), [&](int i, int j) {
		pi x = i < n ? mp(l[i] - 1, r[i]) : mp(r[i], l[i] - 1);
		pi y = j < n ? mp(l[j] - 1, r[j]) : mp(r[j], l[j] - 1);
		return x < y;
	});
	for (int i = 0; i <= n; i++)
		if (i & 1) ans -= calc(i);
		else ans += calc(i);
	print(ans);
	return 0;
}
```

---

## 作者：9AC8E2 (赞：8)

**注意下标从$0$开始**

对于每个位置 $i$,它的上界 $R_i$ 与下界 $L_i$ 都是确定的.
$$\forall i\in [0,n),L_i=\lceil \sqrt{n^2-i^2}\rceil,R_i=\lfloor \sqrt{4n^2-i^2}\rfloor$$
$$\forall i\in[n,2n),L_i=0,R_i=\lfloor \sqrt{4n^2-i^2}\rfloor$$

容易发现的是,$L_i,R_i$ 单调不递增,且 $\max_{i\in [0,n)}\{L_i\}\leq \min_{i\in [0,n)}\{R_i\}$

考虑如果没有 $L_i$ 的限制该怎么做.将 $R$ 从小到大排序,这样答案就是 $\prod_{i\in[0,2n)}R_i-i+1$.(下标从$0$开始)

然后考虑容斥出有下界的合法方案.设钦点 $k$ 个位置不满足下界的答案为 $f_k$ (即钦点这 $k$ 个位置的上界为 $L-1$ ).然后发现只有前面 $n$ 个位置可能不满足下界.

$$ans=\sum_{i=0}^{n}(-1)^i\times f_i$$

考虑怎么 $\texttt{DP}$ 出这个 $f$.

假设现在已经按新的上界为第一关键字,位置**的负数**为第二关键字将所有位置排序(因为考虑 $rank$ 的话相同的值比较麻烦)

$\forall i\in[n,2n)$,排在位置 $i$ 之前的位置有且仅有

- $[n,2n)$ 中按 $R$ 排序后本身就排在 $i$ 之前的位置
- $[0,n)$ 中取上界为 $L-1$ 且排序后排在 $i$ 之前的位置

$\forall i\in[0,n)$,若取 $R$ 为上界,排在位置 $i$ 之前的位置有且仅有

- $[0,n)$ 中取上界为 $R$ 且按 $R$ 排序后本身就排在 $i$ 之前的位置
- $[n,2n)$ 中的所有位置
- $[0,n)$ 中取上界为 $L-1$ 的所有位置

$\forall i\in[0,n)$,若取 $L-1$ 为上界,排在位置 $i$ 之前的位置有且仅有

- $[n,2n)$ 中按 $R$ 排序后本身就排在 $i$ 之前的位置
- $[0,n)$ 中取上界为 $L-1$ 且排序后排在 $i$ 之前的位置

这样,将 $[0,n)$ 中的元素按 $L$ 为第一关键字, $R$ 为第二关键字, $[n,2n)$ 中的元素按 $R$ 为第一关键字, $0$ 为第二关键字排序,从前往后 $\texttt{DP}$.

设 $dp_{i,j}$ 表示 $\texttt{DP}$ 到 $i$ 位置,有 $j$ 个位置取上界为 $L-1$ 的总方案数. $dp_{0,0}=1$.

设 $from_i$ 表示位置 $i$ 的来源,$cnt1_i$ 表示前 $i$ 个位置中 $from\in[n,2n)$ 的个数,$cnt2_i$ 表示前 $i$ 个位置中 $from\in [0,n)$ 的个数,$k$ 表示要求的是有 $k$ 位置取上界为 $L_1$ 的答案

考虑 $dp_{i,j}$ 怎么转移.

## $from_{i}\in[n,2n)$

显然这种时候只能取上界为 $R$

$$dp_{i+1,j}\leftarrow dp_{i,j}\times (R-(cnt1_i+j)+1)$$

## $from_{i}\in[0,n)$

### 取上界为 $L-1$
$$dp_{i+1,j+1}\leftarrow dp_{i,j}\times(L-(cnt1_i+j))$$

### 取上界为 $R$

$$dp_{i+1,j}\leftarrow dp_{i,j}\times (R+1-(n+k+(cnt2_i-j)))$$

[代码](https://www.luogu.com.cn/paste/vxg80rl1)

---

## 作者：N2MENT (赞：4)

[blog](https://www.cnblogs.com/0x0620AF/articles/AGC036F.html)

[AGC036F](https://www.luogu.com.cn/problem/AT_agc036_f)

有意思的，自然的。

---

刚开始有些地方没懂，想清楚之后记录一下。

原题可以转化一下，要求每个元素在半径分别为 $n$ 和 $2n$ 的之间（包含圆上）。 

注意到如果没有下界，只有上界是好做的，只要把上界从小到大排序，每一个位置上选择一个值都会使得后面每个位置的方案数 $-1$。


---

有下界，考虑容斥，设 $f_k$ 表示钦定 $k$ 个位置一定不合法（小于下界）的方案数：

$$ans = \sum_{k = 0}^n (-1)^k \cdot f_k$$

考虑 $f_k$ 如何计算。

---

设 $i$ 的上界为 $R_i$，下界为 $L_i$（若没有则为 $0$）。

我们对于原序列中一个位置 $i$，限制不大于它的位置 $j$ 有哪些。

$n \leq i < 2n$：

- $n \leq j < 2n$ 那么要求 $R_j \leq R_i$；

- $0 \leq j < n$ 那么如果钦定了 $j$ 不合法则要求 $L_j - 1 \leq R_i$；如果没钦定则 $R_j > R_i$， 不可能 。

$0 \leq i < n$ 且被钦定不合法：

- $n \leq j < 2n$ 那么要求 $R_j \leq L_i - 1$；

- $0 \leq j < n$ 那么如果钦定 $j$ 不合法则要求 $L_j - 1 \leq L_i - 1$；如果没钦定则不可能。

$0 \leq i < n$ 且不被钦定：

- $n \leq j < 2n$ 那么一定满足；

- $0 \leq j < n$ 那么如果钦定即一定满足；如果没钦定则要求 $R_j \leq R_i \Leftrightarrow L_j - 1 \leq L_i - 1$。

注意到所有的 $i$ 和 $j$ 之间的限制都可以转化为相似形式，$0 \leq i < n$ 以 $L_i - 1$ 为关键字，$n \leq  i < 2n$ 以 $R_i$ 为关键字，排序后进行 dp。

设 $f_{i, j}$ 表示考虑前 $i$ 个位置，钦定了 $j$ 个不合法的方案数，$r$ 表示前 $i - 1$ 个位置中原属于 $[n,2n)$ 的位置个数，$l$ 表示前 $i - 1$ 个位置中原属于 $[0,n)$ 的位置个数。

如果 $L_i = 0$ 那么 $i$ 原来在 $ [  n,2n)$ 区间上：

$$f_{i,j} \longleftarrow f_{i, j} + f_{i-1, j} \cdot (R_i + 1 - r - j)$$

否则原来在 $[0,n)$ 区间上：

若钦定这一位：

$$f_{i,j} \longleftarrow f_{i, j} + f_{i-1, j} \cdot (L_i - r - (j - 1))$$

若不钦定这一位：

$$f_{i,j} \longleftarrow f_{i, j} + f_{i-1, j - 1} \cdot (R_i + 1 - k - n - (l - j))$$

原理见前文。


```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const int maxn = 510;
const int inf = 1e9;
int n, mod;
int f[maxn][maxn];
vector<pair<int, int>> lim;
int Calc(int k) {
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    int lcnt = 0, rcnt = 0;
    for(int i = 1; i <= (n << 1); i++) {
        if(lim[i].second == 0) {
            for(int j = 0; j <= k; j++) {
                f[i][j] = (f[i][j] + (ll)f[i - 1][j] * (lim[i].first + 1 - rcnt - j) % mod) % mod;
            }
            rcnt++;
        } else {
            for(int j = 0; j <= k; j++) {
                f[i][j] = (f[i][j] + (ll)f[i - 1][j] * (lim[i].second + 1 - k - (lcnt - j) - n) % mod) % mod;
                if(j) f[i][j] = (f[i][j] + (ll)f[i - 1][j - 1] * (lim[i].first - j - rcnt + 2) % mod) % mod;
            }
            lcnt++;
        }
    }
    return f[n << 1][k];
}
void Init() {
    lim.emplace_back(-inf, -inf);
    for(int i = 0; i < n; i++) {
        int l = ceil(sqrt((ld)n * n - i * i));
        int r = min(2 * n - 1, (int)floor(sqrt(4 * n * n - i * i)));
        lim.emplace_back(l - 1, r);
    }
    for(int i = n; i < 2 * n; i++) {
        int r = min(2 * n - 1, (int)floor(sqrt(4 * n * n - i * i)));
        lim.emplace_back(r, 0);
    }
    sort(lim.begin(), lim.end());
}
int main() {
    cin >> n >> mod;
    Init();
    int ans = 0;
    for(int i = 0; i <= n; i++) {
        int del = Calc(i);
        if(i & 1) ans = (ans - del + mod) % mod;
        else ans = (ans + del) % mod;
    }
    cout << ans;
}
```

---

## 作者：cwfxlh (赞：3)

# [AT_agc036_f](https://www.luogu.com.cn/problem/AT_agc036_f)          

对于不带下界的问题，是好做的，将上界从小到大排序后，答案为：           

$$\prod_{i=1}^{n}{{R_i-(i-1)}}$$        

对于带了下界的情况，考虑容斥，钦定有 $k$ 个位置是不符合要求的，这个时候，相当于把钦定的这 $k$ 个位置的上界改为了 $L_i-1$，排序后再按上面的即可求出答案。容斥系数就是 $(-1)^k$。            

先枚举一个 $k$，接下来就需要求出钦定 $k$ 个位置不合法的答案。答案的值与每个上界的排名有关，于是需要设计一个方法来计算排名。对于 $[n,2n-1]$ 中的元素，其下界为 0，可以只考虑上界，但是对于 $[0,n-1]$ 中的元素，它有两种可以选择的上界。$L_i-1$ 这个上界的排名不好考虑，因为它会与 $[n,2n-1]$ 混杂在一起，但是 $R_i$ 这个上界是好考虑的，因为 $[0,n-1]$ 中最小的 $R_i$ 比 $[0,n-1]$ 中最大的 $L_i-1$ 都大。         

所以说，对于一个 $R_i$，比它小的上界至少有 $n+k$ 个，其余比它小的上界都是 $[0,n-1]$ 的 $R_i$。先将 $2n$ 个点分别按 $L_i-1$ 和 $R_i$ 排序（前一半用 $L_i-1$，后一半用 $R_i$），前一半的元素，如果 $L_i-1$ 相同，则将 $R_i$ 小的排到前面。从前往后钦定，发现排名是可以计算的。         

考虑前 $i$ 个元素钦定了 $j$ 个不合法，有 $cnt$ 个元素属于 $[n,2n-1]$。如果 $i+1$ 为后半段，则比它小的数有 $j+cnt$ 个。如果 $i+1$ 为前半段，选择 $L_i-1$ 作为上界，则比它小的数有 $j+cnt$ 个。如果 $i+1$ 为前半段，选择 $R_i$ 作为上界，则比它小的数有 $k+n+(i-cnt-j)$ 个。写成 dp 即可，一次 dp 复杂度 $O(n^2)$，总复杂度 $O(n^3)$。          

代码：    


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,MOD,dp[503][503],ans,L[503],R[503],cnt;
pair<int,int>num[503];
bool comp(pair<int,int>X,pair<int,int>Y){
    if(X.first!=Y.first)return X.first<Y.first;
    return X.second>Y.second;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>MOD;
    for(int i=0;i<2*n;i++)R[i]=min((int)(sqrt(4*n*n-i*i)),2*n-1);
    for(int i=0;i<n;i++){
        L[i]=sqrt(n*n-i*i);
        if(L[i]*L[i]+i*i<n*n)L[i]++;
    }
    for(int k=0;k<=n;k++){
        for(int i=0;i<2*n;i++){
            num[i].second=i;
            if(i>=n)num[i].first=sqrt(4*n*n-i*i);
            else{
                num[i].first=sqrt(n*n-i*i);
                if(num[i].first*num[i].first+i*i>=n*n)num[i].first--;
            }
        }
        sort(num,num+2*n,comp);
        for(int i=2*n;i;i--)num[i]=num[i-1];
        dp[0][0]=1;
        cnt=0;
        for(int i=1;i<=2*n;i++){
            if(num[i].second<n){
                for(int j=(i-cnt);j>=0;j--){
                    dp[i][j]=dp[i-1][j]*(R[num[i].second]+1-k-n-(i-1-cnt-j))%MOD;
                    if(j>0)dp[i][j]=(dp[i][j]+dp[i-1][j-1]*(num[i].first+1-(j-1)-cnt))%MOD;
                }
            }
            else{
                for(int j=(i-1-cnt);j>=0;j--){
                    dp[i][j]=dp[i-1][j]*(num[i].first+1-j-cnt)%MOD; 
                }
                cnt++;
            }
        }
        if(k%2==0)ans=(ans+dp[2*n][k])%MOD;
        else ans=(ans-dp[2*n][k])%MOD;
    }
    ans%=MOD;
    ans+=MOD;
    ans%=MOD;
    cout<<ans;
    return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：2)

[[AGC036F] Square Constraints](https://www.luogu.com.cn/problem/AT_agc036_f)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/18034997)

![image.png](https://s2.loli.net/2024/02/26/ILEVDfJWkrChcYZ.png)

可以看成是求值域两个半圆间的排列的个数。

首先对于每个 $i$ 设 $L_i,R_i$ 表示 $p_i$ 取值的下界和上界。

如果没有小圆的限制即没有下界，问题很简单：把 $R$ 从小到大排序，然后 $\prod_{i=1}^nR_i-i+1$ 即为答案，原因显然，因为前面已经选了 $i-1$ 个并且前 $i-1$ 个值域 $\leq R_i$。

现在加入了 $L$ 的限制，考虑容斥，用 $\leq R_i$ 的答案减去 $\leq L_i-1$ 的答案即为原问题的答案。容斥系数为钦定为 $L_i-1$ 的位置的个数，其余正常算。

但是因为上面的公式只有在上界有序的情况下（即知道每个限制最终的排名）才能使用，实际上选的是：

1. $[0,n]$ 中选了一些 $L-1$。

2. $[0,n]$ 中剩下的部分的选了 $R$。

3. $[n+1,2n-1]$ 中因为没有下界限制无法进行容斥，所以都选的是 $R$。

这样三个部分内部都是有序的，而且第 $2$ 部分一定是最大的。所以我们需要把 $1,3$ 进行一个类似归并的过程来计算方案数。

把 $[n+1,2n-1]$ 的 $R_i$ 挂在 $[0,n]$ 最后一个满足 $L_j-1\geq R_i$ 的 $j$ 上，设 $f_{i,j}$ 为考虑了 $[i,n]$ 中所有数，钦定了 $j$ 个做容斥，带容斥系数的方案数。$f_{i,j}$ 应当计算的部分是上一步挂在 $[i,n]$ 上的所有 $R$ 的贡献，$[i,n]$ 内容斥的 $L$ 的贡献和 $[i,n]$ 内没有容斥的 $R$ 的贡献。

但是直接做有一个问题：计算方案数使用开头的那个 $\prod R_i-i+1$ 的公式算的，但是在 $[i,n]$ 内没有容斥的 $R$ 计算途中并不知道他的排名。

如果已知最后要容斥几个，那 $[i,n]$ 内没有容斥的 $R$ 的排名在 dp 过程中就已知了。可以最外层枚举目的要容斥 $k$ 个，这样内层进行 dp，$f_{i,j}$ 意义和上面一样，但是这里可以不带容斥系数，因为我们最后只会用到 $f_{1,k}$。

外层枚举复杂度 $\mathcal O(n)$，内层 dp $\mathcal O(n^2)$，总复杂度 $\mathcal O(n^3)$。

```cpp
	int n,M,ans,lim,L[510],R[510],a[510],f[510][510];
	vector<int> ve[510];
	inline void mian()
	{
		read(n,M);
		for(int i=0;i<2*n;++i)
		{
			R[i+1]=sqrt(4*n*n-i*i)+1;
			if(i<n)L[i+1]=ceil(sqrt(n*n-i*i))+1;
			else L[i+1]=1;
		}
		R[1]--;
		for(int i=2*n;i>=n+2;--i)
		{
			if(R[i]>=L[1]){!lim?lim=i:0;ve[0].eb(R[i]);continue;}
			for(int j=n+1;j>=1;--j)
			if(L[j]-1>=R[i]){ve[j].eb(R[i]);break;}
		}
		for(int i=n+1;i>=1;--i)a[i]=a[i+1]+ve[i].size();
		for(int i=0;i<=n;++i)
		{
			memset(f,0,sizeof(f)),f[n+1][0]=1;
			for(int l=0;l<(int)ve[0].size();++l)
			f[n+1][0]=1ll*f[n+1][0]*(ve[0][l]-l-i-a[1])%M;
			for(int j=n+1;j>=1;--j)
			{
				for(int k=0;k<=i;++k)
				{
					for(int l=0;l<(int)ve[j].size();++l)
					f[j][k]=1ll*f[j][k]*(ve[j][l]-a[j+1]-k-l)%M;
					if(k<i&&L[j]-1-k>0)
					f[j-1][k+1]=(f[j-1][k+1]+1ll*f[j][k]*(L[j]-1-k-a[j])%M+M)%M;
					f[j-1][k]=(f[j-1][k]+1ll*f[j][k]*(R[j]-(2*n-(j-(i-k)))))%M;
				}
			}
			if(i&1)ans=(ans-f[0][i]+M)%M;
			else ans=(ans+f[0][i])%M;
		}
		write(ans);
	}
```

---

## 作者：Purslane (赞：1)

# Solution

感觉很难。

本题的重点在于使用图形直观分析性质。~~如果让我把图画出来我就切了。~~

本质上是对下图中只能在蓝色区域内放格点的排列计数。

![](https://s21.ax1x.com/2025/02/24/pE1mOv8.png)

很自然的，考虑容斥。假设钦定了 $k$ 个位置要放在左下角的小圆之内。

如果我们确定了所有点是否容斥，那么计数是简单的——每个位置可能的取值都是**一段前缀**，这样可以直接对上界排序之后，逐个枚举计数。

所以，上界的序很重要。每个数只有两种上界：$u_1$ 和 $u_2$，分别表示容斥时较小的上界和本身的上界。

设横坐标 $< n$ 的为一类点，$n$ 到 $2n-1$ 之间的为二类点。取一类点的 $u_1$ 和二类点的 $u_2$ 排序。发现最终的顺序相当于保留了 $k$ 个一类点，将其他的一类点**保持原顺序放到末尾去**。

这样当 $k$ 一定的时候，就可以直接 DP 计数了。（根据排序好的顺序进行扫描，记录前缀保留了多少个点，很容易计算出最终的排名）时间复杂度 $O(n^3)$。

本题和一般的容斥计数最大的不同是，**并没有将容斥系数直接塞进 DP 离进行转移**，而是利用容斥的结果在 DP 种计算某些事情。而且，对于区间限制类数数问题，可以考虑限制的前缀性。

代码和 sol1 老师写的很像，因为我对着他的代码条的。

注意如果一类点的 $u_1$ 相同，要按 $u_2$ 从小到大排序。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500+10;
int n,MOD,ans,u1[MAXN],u2[MAXN],id[MAXN],dp[MAXN][MAXN];
int solve(int k) {
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	int cnt=0,nxt=0;
	ffor(i,1,n+n) {
		ffor(j,0,k) if(dp[i-1][j]) {
			if(id[i]>=n) dp[i][j]=(dp[i][j]+dp[i-1][j]*(u2[id[i]]+1-cnt-j))%MOD;
			else {
				dp[i][j+1]=(dp[i][j+1]+dp[i-1][j]*(u1[id[i]]+1-cnt-j))%MOD;
				dp[i][j]=(dp[i][j]+dp[i-1][j]*(u2[id[i]]+1-(n+nxt+k-j)))%MOD;
			}
		}
		if(id[i]>=n) cnt++;
		else nxt++;
//		cnt+=(id[i]>=n);
//		nxt+=(id[i]<n);
	}
	return dp[n+n][k]%MOD;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>MOD;
	ffor(i,0,n-1) u1[i]=sqrt(n*n-i*i-1),u2[i]=sqrt(n*n*4-i*i);
	ffor(i,n,n+n-1) u2[i]=sqrt(n*n*4-i*i);
	ffor(i,0,n+n-1) u2[i]=min(u2[i],n+n-1);
	ffor(i,1,n+n-1) assert((u2[i]+1)*(u2[i]+1)+i*i>n*n*4);
	vector<pair<int,int>> st;
	ffor(i,0,n-1) st.push_back({u1[i],i});
	ffor(i,n,n+n-1) st.push_back({u2[i],i});
	sort(st.begin(),st.end(),[](pair<int,int> a,pair<int,int> b){
		if(a.first!=b.first) return a.first<b.first;
		return a.second>b.second;
	});
	ffor(i,1,n+n) id[i]=st[i-1].second;
	ffor(i,0,n) if(i&1) ans=(ans-solve(i))%MOD;
	else ans=(ans+solve(i))%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

