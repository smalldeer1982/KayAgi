# [NOISG 2022 Finals] Fruits

## 题目描述

超市里通常有专门的一区卖水果。

兔子 $\text{Benson}$ 常去的超市一共有 $N$ 个柜台用来卖 $N$ 种水果。柜台编号从 $1 \sim N$，水果编号从 $1 \sim N$。第 $i$ 种水果的美味度是 $i$，购买需要花费 $C_i$ 元。**保证对于所有的 $1 \le i < j \le N$，有 $C_i \le C_j$。**

每一个柜台都只买一种水果，每一种水果都有且仅有一个柜台售卖。现在，工作人员规定了每个柜台卖哪一种水果。第 $i$ 个柜台卖第 $A_i$ 种水果。如果 $A_i=-1$，则表示这个柜台还没有确定卖什么。

当所有柜台的水果都摆放好，$\text{Benson}$ 就会进店抢购。他会按照 $1 \sim N$ 的顺序去这些柜台。当他到了一个柜台，如果他的购物车里还是空的，或当前柜台水果的美味度大于所有他购物车里的水果，那么他就会购买这种水果，将其放进购物车中。

现在你需要让商店赚到最多的钱。你需要计算怎么来摆放那些 $A_i=-1$ 的柜台使得利润最大化。由于 $\text{Benson}$ 很赶时间，他可能不会逛完所有柜台，所以你需要对于所有的 $1 \le k \le N$ 计算如果 $\text{Benson}$ 只逛第 $1 \sim k$ 个柜台，那么这些柜台应该如何摆放最优。

## 说明/提示

**【数据范围】**

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$6$|$N\le8$|
|$2$|$5$|对于所有 $1\le j\le N$，$A_j=-1$|
|$3$|$11$|$N\le200$|
|$4$|$13$|$N\le2000$|
|$5$|$23$|对于所有 $1\le j\le N$，$C_j=1$|
|$6$|$42$|无|

对于 $100\%$ 的数据，$1 \le N \le 400000,1 \le A_j \le N$ 或 $A_j=-1,1 \le C_i \le 10^9$。

## 样例 #1

### 输入

```
5
-1 -1 -1 -1 -1
1 1 1 1 1```

### 输出

```
1 2 3 4 5
```

## 样例 #2

### 输入

```
5
-1 3 -1 -1 -1
1 2 2 2 3
```

### 输出

```
3 4 7 9 9```

## 样例 #3

### 输入

```
13
-1 -1 5 6 -1 -1 7 11 -1 -1 10
-1 -1
1 1 1 1 1 1 1 1 1 1 1 1 1
```

### 输出

```
1 2 3 4 5 6 6 7 8 9 9 9 9```

## 样例 #4

### 输入

```
10
-1 -1 -1 -1 5 -1 -1 -1 9 -1
5 11 24 27 35 60 72 81 91 92```

### 输出

```
92 173 245 305 305 332 356 367 406 498
```

# 题解

## 作者：liangbowen (赞：7)

[blog](https://www.cnblogs.com/liangbowen/p/18631565)。写了好几天，人都要死了。提供一个不同的切入口，方便大家理解这个分段是在干嘛，以及一个更容易的线段树 DS。题解一堆废话，大家看看就行（

## $O(N^3)$

先把 $a_i\ne-1$ 且无论如何无法成为前缀 max 的位置 ban 掉。

由于答案只与 premax 的位置有关，于是**设 $dp_{i,j}$ 表示确定完 $a_1,a_2,\cdots,a_i$ 且 premax 的位置为 $j$ 的答案。**

考虑转移 $dp_{i,j}$。

+ **若 $a_i=-1$：**
  + [1-1] 随便放个以后不用的小的：$dp_{i,j}\gets dp_{i-1,j}$。
  + [1-2] 若上一个 premax 比 $j$ 小，现在必须贪心地放 $j$（要求 $vis_j=\textbf{true}$）：$dp_{i,j}\gets\max\limits_{w=0}^{j-1}dp_{i-1,w}+c_j$。
+ **若 $a_i\ne-1$：可以发现，只需要考虑 $j\ge a_i$ 的情况。**
  + [2-1] 我要我要！这个时候强制 $j=a_i$：$dp_{i,a[i]}\gets\max\limits_{w=0}^{a[i]-1}dp_{i-1,w}+c_{a[i]}$。
  + [2-2] 不要不要！这需要保证前面的 premax 比 $a_i$ 大：$dp_{i,j}\gets dp_{i-1,j}\ \ (a_i<j\le n)$。


初始化 $-\infty$，$dp_{0,0}=0$；第 $K$ 个答案即为 $\max\limits_{i=0}^n dp_{K,i}$。

```cpp
const int N = 4e5 + 5;
int n, a[N], c[N]; bool vis[N]; ll dp[2005][2005];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), ~a[i] ? (vis[a[i]] = true) : 0;
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
  
	for (int i = 1, p = 0; i <= n; i++)
		if (~a[i]) {if (p > a[i]) c[a[i]] = 0;} else {while (vis[++p]);}

	mems(dp, -0x3f), dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		if (~a[i]) {
			for (int j = 0; j < a[i]; j++) dp[i][a[i]] = max(dp[i][a[i]], dp[i - 1][j] + c[a[i]]);
			for (int j = a[i] + 1; j <= n; j++) dp[i][j] = dp[i - 1][j];
		} else {
			for (int j = 1; j <= n; j++) {
				dp[i][j] = dp[i - 1][j];
				if (!vis[j]) {for (int k = 0; k < j; k++) dp[i][j] = max(dp[i][j], dp[i - 1][k] + c[j]);}
			}
		}
		printf("%lld ", *max_element(dp[i], dp[i] + n + 1));
	}
	return 0;
}
```

## $O(N^2)$

前缀 max 容易优化至 $O(n^2)$。由于过一会要上 DS，我们先把 code 变好看一点：

1. 钦定 $vis_j=\textbf{false}$ 时 $c^{\prime}_j=-\infty$ 否则 $c^{\prime}_j=c_j$。于是可以删个 [1-2] 的判断条件。

2. **令 $f_{i,j}$ 表示确定完 $a_1,a_2,\cdots,a_i$ 且 premax 的位置为 $\le j$ 的答案**。即 $f_{i,j}=\max\limits_{w=0}^j dp_{i,w}$。注意到可以全程依赖 $f$ 进行转移！只要在每次结束后进行 [3-1] 前缀 chkmax 操作就行。

```cpp
const int N = 4e5 + 5;
int n, a[N], c[N]; bool vis[N]; ll ccc[N], f[2005][2005];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), ~a[i] ? (vis[a[i]] = true) : 0;
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
  
	for (int i = 1, p = 0; i <= n; i++) if (~a[i]) {if (p > a[i]) c[a[i]] = 0;} else {while (vis[++p]);}
	for (int i = 1; i <= n; i++) ccc[i] = (!vis[i] ? c[i] : -0x3f3f3f3f3f3f3f3f);

	mems(f, -0x3f), mems(f[0], 0);
	for (int i = 1; i <= n; i++) {
		if (~a[i]) {
			f[i][a[i]] = f[i - 1][a[i] - 1] + c[a[i]];
			for (int j = a[i] + 1; j <= n; j++) f[i][j] = f[i - 1][j];
		} else {
			for (int j = 1; j <= n; j++) f[i][j] = max(f[i - 1][j], f[i - 1][j - 1] + ccc[j]);
		}
		for (int j = 1; j <= n; j++) f[i][j] = max(f[i][j - 1], f[i][j]); printf("%lld ", f[i][n]);
	}
	return 0;
}
```

进而把代码改成 1D 形式。可以直接 DS......吗？

```cpp
const int N = 4e5 + 5; const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, a[N], c[N]; bool vis[N]; ll ccc[N], f[N], g[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), ~a[i] ? (vis[a[i]] = true) : 0;
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);

	for (int i = 1, p = 0; i <= n; i++) if (~a[i]) {if (p > a[i]) c[a[i]] = 0;} else {while (vis[++p]);}
	for (int i = 1; i <= n; i++) ccc[i] = (!vis[i] ? c[i] : -INF);

	for (int i = 1; i <= n; i++) {
		if (~a[i]) {
			f[a[i]] = f[a[i] - 1] + c[a[i]];
			for (int j = 0; j < a[i]; j++) f[j] = -INF;
		} else {
			for (int j = n; j; j--) f[j] = max(f[j], f[j - 1] + ccc[j]);
			f[0] = -INF;
		}
		for (int j = 1; j <= n; j++) f[j] = max(f[j - 1], f[j]); printf("%lld ", f[n]);
	}
	return 0;
}
```

## Optimize1

其中一个大问题是 $\forall(j:n\to1)\ f_j=\max(f_j,f_{j-1}+c^{\prime}_j)$ 这一句？这个结构是线段树无法维护的。这个是本题的最大难点。但是打表发现，**只要 $f_{j-1}\ne-\infty$，那么这个 chkmax 一定是后面成功！**

（这是因为当 $f_{j-1}\ne-\infty$，说明这个值及其后缀的值都是有效的。那么，如果 $f_j>f_{j-1}+c^{\prime}_j$，**由于 $c$ 单调不降**，那么我们将 $f_j$ 处最大值的贡献更换为任意一个数，必定仍然有 $f_j>f_{j-1}$，这说明 $f_{j-1}$ 可以取更大，矛盾！）

进一步地，由于 $f$ 单调不降，所以 $f_{j}\ne-\infty$ 的一定是一段后缀。我们可以维护指针 $up$ 表示这个后缀。

```cpp
const int N = 4e5 + 5; const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, a[N], c[N]; bool vis[N]; ll ccc[N], f[N], g[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), ~a[i] ? (vis[a[i]] = true) : 0;
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
	
	for (int i = 1, p = 0; i <= n; i++) if (~a[i]) {if (p > a[i]) c[a[i]] = 0;} else {while (vis[++p]);}
	for (int i = 1; i <= n; i++) ccc[i] = (!vis[i] ? c[i] : -INF);

	int up = 0;
	for (int i = 1; i <= n; i++) {
		if (~a[i]) {
			f[a[i]] = max(f[a[i]], f[a[i] - 1] + c[a[i]]);
			for (int j = 0; j < a[i]; j++) f[j] = -INF;
		} else {
			for (int j = n; j > up; j--) f[j] = f[j - 1] + ccc[j];
			f[0] = -INF;
		}
		for (int j = 1; j <= n; j++) f[j] = max(f[j - 1], f[j]);
		for (int j = 1; j <= n; j++) if (f[j] >= 0) {up = j; break;}
		printf("%lld ", f[n]);
	}
	return 0;
}
```

## Optimize2

另一个问题是前缀 chkmax。这个反而不困难，我们挖掘代码中的单调性质就能解决。

先看看 $up$。若 $a_i\ne-1$，那么每次等价于 $up\gets\max(up,a_i)$；否则， $a_i=1$ 时除了边界情况，$up$ 都应该不变。**这说明 $up$ 单调不降**。

+ 对于 $a_i\ne-1$ 的情况，直接写成主动转移的形式（$\forall j\in(up,n],f_j\gets\max(f_j,f_{a_i-1}+c_{a_i})$），发现此时前缀 chkmax 操作直接丢掉就行。
+ 对于 $a_i=-1$ 的情况，发现若 $\forall c^{\prime}_j=c_j$，那么 $f_{j-1}+c^{\prime}_j$ 是单调的（因为 $f,c$ 都单调）！也就是说，所有 $c^{\prime}_j=-\infty$ 的位置的值，都可以变成前面的第一个 $c^{\prime}_j\ne-\infty$ 的位置的值。

自然地，考虑能否将 $c^{\prime}_j=-\infty$ 的位置直接丢掉。

**这显然是可以的**！只要将所有 $c^{\prime}_j=-\infty$ 即 $vis_j=\textbf{false}$ 的位置与其后一个 $vis_j=\textbf{true}$ 的位置划分成一段，记录 $up$ 的时候记录两个（一个是真实值，一个是对应到块的值）就行，每个块除了 $-\infty$ 的情况，全部元素都应当是相同的。

```cpp
const int N = 4e5 + 5; const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, up, ups, a[N], c[N], bel[N]; bool vis[N]; ll f[N], ccc[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), ~a[i] ? (vis[a[i]] = true) : 0;
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
  
	for (int i = 1, p = 0; i <= n; i++) if (~a[i]) {if (p > a[i]) c[a[i]] = 0;} else {while (vis[++p]);}
	for (int i = 1; i <= n; i++) {if (!vis[i]) ccc[++m] = c[i]; bel[i] = m;}

	for (int i = 1; i <= n; i++) {
		if (~a[i]) {
			if (ups < a[i]) {
				int p = bel[a[i]]; ll x = f[p] + c[a[i]];
				for (int j = 0; j < p; j++) f[j] = -INF;
				for (int j = p; j <= m; j++) f[j] = max(f[j], x);
				ups = a[i], up = p;
			}
		} else {
			for (int j = m; j > up; j--) f[j] = f[j - 1] + ccc[j];
			f[0] = -INF;
			if (!up) {ups = 1; for (int j = 1; j <= m; j++) if (f[j] >= 0) {up = j; break;}}
		}
		printf("%lld ", f[m]);
	}
	return 0;
}
```

## ShiftTag + DS

终于，启动 DS！最麻烦的一个部分是"区间平移 + 区间加对应位置的数"。前者可以打 Shift Tag，后缀可以维护 $f_i=v_i+\sum\limits_{l_i}^{r_i} c_i$ 转化为 $r_i$ 的区间加。

有点问题的是区间 chkmax 操作，但由于 $f$ 有单调性，二分分界点后就能转为区间覆盖。

```cpp
const int N = 8e5 + 5, X = 4e5; const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, up, ups, a[N], c[N], bel[N]; bool vis[N]; ll f[N], l[N], r[N], ccc[N], s[N];
inline ll cal(int x) {return f[x] + s[r[x]] - s[l[x] - 1];}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), ~a[i] ? (vis[a[i]] = true) : 0;
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);

	for (int i = 1, p = 0; i <= n; i++) if (~a[i]) {if (p > a[i]) c[a[i]] = 0;} else {while (vis[++p]);}
	for (int i = 1; i <= n; i++) {if (!vis[i]) ccc[++m] = c[i]; bel[i] = m;}
	for (int i = 1; i <= m; i++) s[i] = s[i - 1] + ccc[i];

	int S = 0;
	for (int i = 0; i <= 4e5; i++) l[i + X - S] = i + 1, r[i + X - S] = i;
	for (int i = 1; i <= n; i++) {
		if (~a[i]) {
			if (ups < a[i]) {
				int p = bel[a[i]]; ll x = cal(p + X - S) + c[a[i]];
				for (int j = 0; j < p; j++) f[j + X - S] = -INF;
				for (int j = p; j <= m; j++) if (x > cal(j + X - S)) f[j + X - S] = x, l[j + X - S] = j + 1, r[j + X - S] = j;
				ups = a[i], up = p;
			}
		} else {
			f[up - 1 + X - S] = f[up + X - S], l[up - 1 + X - S] = l[up + X - S], r[up - 1 + X - S] = r[up + X - S];
			for (int j = up; j < m; j++) r[j + X - S]++;
			S++; f[0 + X - S] = -INF, l[0 + X - S] = 1, r[0 + X - S] = 0; if (!up) up = ups = 1;
		}
		printf("%lld ", cal(m + X - S));
	}
	return 0;
}
```

这样再怎么样你都会做了吧？再维护一个 $l^{\prime}_i=l_i+i,r^{\prime}_i=r_i+i$ 消除 $\Delta$，然后对 $v,l^{\prime},r^{\prime}$ 各维护一棵线段树就行。二分部分在三棵线段树上并行二分就能做到单 log。其余部分只需要区间加、区间覆盖、单点查。

综上，我们用大常数 $O(N\log N)$ 通过了此题，被 deque 做法吊打。

## Code

没啥参考价值的。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define mems(x, v) memset(x, v, sizeof x)
#define mcpy(x, y) memcpy(x, y, sizeof x)
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double wisdom;

const int N = 8e5 + 1005, X = 4e5 + 100; const ll INF = 0x3f3f3f3f3f3f3f3f, NOTVIS = -INF - 114514;
int n, m, up, ups, a[N], c[N], bel[N]; bool vis[N]; ll ccc[N], s[N];

#define ls pos << 1
#define rs pos << 1 | 1
struct SGT {
	// ll a[N];
	// void ADD(int l, int r, ll k) {for (int i = l; i <= r; i++) a[i] += k;} void COV(int l, int r, ll k) {for (int i = l; i <= r; i++) a[i] = k;} ll Q(int x) {return a[x];}
	ll LV[N << 2], add[N << 2], cov[N << 2]; void pushup(int pos) {LV[pos] = LV[ls];} void lcov(int pos, ll k) {cov[pos] = LV[pos] = k, add[pos] = 0;} void ladd(int pos, ll k) {add[pos] += k, LV[pos] += k;}
	void C(int pos) {if (cov[pos] != NOTVIS) lcov(ls, cov[pos]), lcov(rs, cov[pos]), cov[pos] = NOTVIS;} void A(int pos) {if (add[pos]) ladd(ls, add[pos]), ladd(rs, add[pos]), add[pos] = 0;} void pushdown(int pos) {C(pos), A(pos);}
	void update(int l, int r, int pos, int L, int R, ll k) {if (L <= l && r <= R) return (l == r ? void() : C(pos)), ladd(pos, k); int mid = (l + r) >> 1; pushdown(pos); if (L <= mid) update(l, mid, ls, L, R, k); if (mid < R) update(mid + 1, r, rs, L, R, k); pushup(pos);}
	void modify(int l, int r, int pos, int L, int R, ll k) {if (L <= l && r <= R) return lcov(pos, k); int mid = (l + r) >> 1; pushdown(pos); if (L <= mid) modify(l, mid, ls, L, R, k); if (mid < R) modify(mid + 1, r, rs, L, R, k); pushup(pos);}
	ll query(int l, int r, int pos, int id) {if (l == r) return LV[pos]; int mid = (l + r) >> 1; pushdown(pos); return id <= mid ? query(l, mid, ls, id) : query(mid + 1, r, rs, id);}
	inline void ADD(int l, int r, ll k) {if (l <= r) update(1, 801000, 1, l, r, k);} inline void COV(int l, int r, ll k) {if (l <= r) modify(1, 801000, 1, l, r, k);} ll Q(int x) {return query(1, 801000, 1, x);}
	inline void ADD(int x, ll k) {ADD(x, x, k);} inline void COV(int x, ll k) {COV(x, x, k);}
} F, L, R;

inline ll cal(int x) {return F.Q(x) + s[R.Q(x) + x] - s[L.Q(x) + x - 1];}
int fnd(int l, int r, int pos, int pl, int pr, ll x) {
	if (l == r) return l; int mid = (l + r) >> 1; F.pushdown(pos), L.pushdown(pos), R.pushdown(pos);
	if (mid >= pr) return fnd(l, mid, ls, pl, pr, x); if (pl > mid) return fnd(mid + 1, r, rs, pl, pr, x);
	return F.LV[rs] + s[R.LV[rs] + (mid + 1)] - s[L.LV[rs] + (mid + 1) - 1] >= x ? fnd(l, mid, ls, pl, pr, x) : fnd(mid + 1, r, rs, pl, pr, x);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), ~a[i] ? (vis[a[i]] = true) : 0;
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);

	for (int i = 1, p = 0; i <= n; i++) if (~a[i]) {if (p > a[i]) c[a[i]] = 0;} else {while (vis[++p]);}
	for (int i = 1; i <= n; i++) {if (!vis[i]) ccc[++m] = c[i]; bel[i] = m;}
	for (int i = 1; i <= m; i++) s[i] = s[i - 1] + ccc[i];

	for (int i = 0; i < (N << 2); i++) F.cov[i] = L.cov[i] = R.cov[i] = NOTVIS;
	int S = 0;
	for (int i = 0; i <= 4e5 + 100; i++) L.COV(i + X - S, S - X + 1), R.COV(i + X - S, S - X);
	for (int i = 1; i <= n; i++) {
		if (~a[i]) {
			if (ups < a[i]) {
				int p = bel[a[i]]; ll x = cal(p + X - S) + c[a[i]];
				//int lo = p + X - S, hi = m + X - S; while (lo < hi) {int md = (lo + hi + 1) >> 1; cal(md) < x ? lo = md : hi = md - 1;}
				int lo = fnd(1, 801000, 1, p + X - S, m + X - S, x);
				F.COV(p + X - S, lo, x), L.COV(p + X - S, lo, S - X + 1), R.COV(p + X - S, lo, S - X);
				ups = a[i], up = p;
			}
		} else {
			F.COV(up - 1 + X - S, F.Q(up + X - S)), L.COV(up - 1 + X - S, L.Q(up + X - S) + 1), R.COV(up - 1 + X - S, R.Q(up + X - S) + 1);
			R.ADD(up + X - S, m + X - S, 1);
			S++; F.COV(0 + X - S, -INF), L.COV(0 + X - S, 1 - (0 + X - S)), R.COV(0 + X - S, 0 - (0 + X - S)); if (!up) up = ups = 1;
		}
		printf("%lld ", cal(m + X - S));
	}
	return 0;
}
```

---

## 作者：yyyyxh (赞：7)

简要题意：给定一个递增数组的权值数组 $c$，和一个已经确定了部分位置的排列，你需要补全这个排列，使得长度为 $k$ 的所有前缀最大值权值和最大化，对于每个 $k$ 求出答案。

牛牛牛题，zhy 一个上午之内拿下了一个做法 orz，然后我需要一个上午+一个下午才会这个题！

这个题第一步便是需要给出一个可以做到 $O(n^2)$ 的想法，一个想法是考虑对于所有已经确定位置的前缀最大值，你 DP 它的一个子集，钦定这个子集一定产生贡献，这个可以导向 zhy 的想法。

假设你只是想拿 $O(n^2)$ 的分跑路，你可以考虑一些更加暴力的 DP，比如设 $dp_{i,j}$ 表示前 $i$ 个数的最大值为 $j$，最大的权值和。利用前缀 $\max$ 转移是简单的。为了保证这个状态是合法的，也就是说必须要存在一个合法排列前 $i$ 个数最大值为 $j$，要求的条件是 $s_i\le t_j$。其中 $s_i$ 表示前 $i$ 个位置中有多少个没确定的元素，$t_j$ 表示 $1\sim j$ 中有多少个还没被填入排列。你只需要将不满足 $s_i\le t_j$ 的位置清空就行了。

优化这种形式简单的二维 DP 的方向往往是进行某种整体 DP。为了更好地向整体 DP 的形式进发，你需要对 DP 形式进行一点简化。原 DP 状态一个很不舒服的点在于假设你关注到一个固定的 $i$ 所有 $j$ 对应的 DP 值，发现除了一段前缀是 $-\infin$ 之外，其中还有很多零散的 $-\infin$ 的位置。这些位置产生的原因在于在后 $n-i$ 个数中有一些已经被填入的位置不能填到前面去，所以前面 $i$ 个数的最大值不能是这些。

解决这个问题的想法是我们将所有还未填入排列中的数排序形成一个数组 $b$，我们考虑到对于一个前缀 $i$ 其可能的最大值，要么是已经填入的数的前缀最大值 $mx$，要么就是 $b$ 中比 $mx$ 大且位置 $\ge s_i$ 的那些元素。重新设计状态 $f_{i,j}$ 表示前 $i$ 个数最大值为 $b_j$ 的最大权值，$g_i$ 表示前 $i$ 个数最大值为 $mx$ 的最大权值。

将 DP 改写成如下形式之后，就可以马上发现一个重要性质：$f_i$ 恰好是一个后缀有值，且有值的部分单调不降，但是这并不意味着 $g_i$ 一定比 $f_i$ 的最小值小。证明是显然的，因为对于 $x<y$ 你可以把 $f_{i,x}$ 中的一个 $x$ 直接修改成 $y$，使得权值变大。我们先写出一份 $O(n^2)$ 代码（`cur` 就是 $g_i$ 啊）：

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 400003;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int read() {/* fast read */}
int n, m;
int a[N], b[N], c[N], s[N], t[N];
bool vis[N];
ll f[N];
inline void chmx(ll &x, ll v) {/* check max */}
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        if (~a[i])
            vis[a[i]] = 1;
        t[i] = t[i - 1] + (a[i] < 0);
    }
    for (int i = 1; i <= n; ++i) {
        c[i] = read();
        if (!vis[i]) {
            s[++m] = c[i];
            b[m] = i;
        }
    }
    int mx = 0, lim = 1, cnt = 0;
    for (int i = 1; i <= m; ++i)
        f[i] = -INF;
    ll cur = 0;
    for (int i = 1; i <= n; ++i) {
        ll now = -INF;
        if (~a[i]) {
            if (mx < a[i]) {
                chmx(now, cur);
                while (lim <= m and b[lim] < a[i])
                    chmx(now, f[lim++]);
                if (lim > cnt)
                    cur = now + c[a[i]];
                else
                    cur = -INF;
                mx = a[i];
            }
        } else {
            for (int j = m; j >= lim; --j) {
                if (j > lim) chmx(f[j], f[j - 1] + s[j]);
                chmx(f[j], cur + s[j]);
            }
            ++cnt;
            if (cnt > lim)
                ++lim;
        }
        printf("%lld ", max(cur, f[m]));
    }
    putchar('\n');
    return 0;
}
```

然后我的思想陷入到了瓶颈中，我当时以为 `chmx(f[j], f[j - 1] + s[j])` 这种形式的更新可以通过某种数据结构快速维护，所以一直在想如何用线段树维护这个形式。这些想法不出意外地都假了。

下午回来换了换🧠，听说到了 zhy 的做法是关于某种决策单调性的，于是开始意识到这个 DP 转移式子中有些特殊性质我没有发现。

我们注意到 $f_{i,j}$ 如果去掉最大值的贡献，也就是减去一个 $c_{b_j}$ （代码中写成 $s_j$ 了），其依然满足单调不降的性质，因为就算最大值没贡献，依然是越大的最大值给前面的限制越松。

这也就意味着代码中的 `chmx(f[j], cur + s[j]);` 很诈骗，它实际上正好是对一个前缀赋值。此时已经有直接用数据结构优化的可能了，但是还可以继续思考性质。

对于代码中的 `chmx(f[j], f[j - 1] + s[j]);` 我们通过“IOI 赛制中的改一改再交上去法”验证注意到这其实是一定会 checkmax 成功的。

思考一下为什么？因为 $f_{i,j}$ 和 $f_{i,j-1}$ 之间不可能差了一整个 $c_{b_j}$，否则将 $f_{i,j}$ 方案中的 $b_j$ 去掉换任意一个数填上来它的贡献都不劣于 $f_{i,j-1}$。所以这条语句写成 `f[j] = f[j - 1] + s[i]` 也是对的。

接下来的工作就很简单了！轻松套路整体 DP！我们对于固定的 $i$ 维护一整个 $f'_{i,j} = f_{i,j}-c_{b_j}$ 数组，我们需要支持哪些操作：

+ 查询头尾。
+ 删除一段前缀。
+ 全局与某个数取 $\max$，由于 $f'_i$ 递增，实际上就是前缀赋值。
+ 从有值第二个数开始，每个数等于原来的前一个数加上 $c_{b_{j-1}}$。

可以使用 `deque` + 懒标记来维护这个数组。懒标记的含义形如加上从当前位置开始往前一段区间中所有 $c_{b_{j-1}}$ 的和。记录这个区间的长度作为懒标记就行了。

还有前缀赋值这个操作，这个可以直接考虑颜色段均摊。二分出需要赋值的前缀长度之后，删除一段前缀再往前 `emplace_front` 一段新的区间就可以了。时间复杂度为常数极小无比的 $O(n\log n)$（因为二分你只需要在某一个颜色段里二分就行了）。

```cpp
#include <algorithm>
#include <cstdio>
#include <deque>
using namespace std;
const int N = 400003;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int read() {
    char c = getchar();
    int x = 0;
    bool f = 0;
    while (c < 48 or c > 57)
        f |= (c == '-'), c = getchar();
    do
        x = (x * 10) + (c ^ 48), c = getchar();
    while (c >= 48 and c <= 57);
    return f ? -x : x;
}
int n, m, cnt, lim;
int a[N], b[N], c[N], s[N];
bool vis[N];
ll w[N];
inline void chmx(ll &x, ll v) {
    if (x < v)
        x = v;
}
struct Info {
    int len, tag;
    ll val;
    Info(int L, int T, ll V) : len(L), tag(T), val(V) {
    }
};
deque<Info> dq;
ll get_front() {
    if (dq.empty())
        return -INF;
    ll res = dq.front().val;
    int t = cnt - dq.front().tag;
    res += w[lim - t] - w[lim];
    return res;
}
ll get_back() {
    if (dq.empty())
        return -INF;
    ll res = dq.back().val;
    int t = cnt - dq.back().tag;
    res += w[m - t] - w[m];
    return res;
}
void del_front() {
    if (!--dq.front().len)
        dq.pop_front();
}
void del_back() {
    if (!--dq.back().len)
        dq.pop_back();
}
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        if (~a[i])
            vis[a[i]] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        c[i] = read();
        if (!vis[i]) {
            s[++m] = c[i];
            b[m] = i;
        }
    }
    int mx = 0;
    for (int i = m; ~i; --i)
        w[i] = w[i + 1] + s[i];
    lim = 1;
    dq.emplace_back(m, 0, -INF);
    ll cur = 0;
    for (int i = 1; i <= n; ++i) {
        if (~a[i]) {
            if (mx < a[i]) {
                ll now = cur;
                while (lim <= m and b[lim] < a[i])
                    chmx(now, get_front() + s[lim]), del_front(), ++lim;
                if (lim > cnt)
                    cur = now + c[a[i]];
                else
                    cur = -INF;
                mx = a[i];
            }
        } else {
            ll now = get_front();
            ++cnt;
            if (!dq.empty())
                del_back(), dq.emplace_front(1, cnt, now);
            int sz = 0;
            while (!dq.empty()) {
                int x = lim + dq.front().len - 1, t = cnt - dq.front().tag;
                ll val = dq.front().val + w[x - t] - w[x];
                if (val > cur)
                    break;
                sz += dq.front().len;
                lim += dq.front().len;
                dq.pop_front();
            }
            if (!dq.empty()) {
                int l = lim, r = lim + dq.front().len,
                    tt = cnt - dq.front().tag;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    ll now = dq.front().val + w[mid - tt] - w[mid];
                    if (now <= cur)
                        l = mid + 1;
                    else
                        r = mid;
                }
                sz += r - lim;
                dq.front().len -= r - lim;
                lim = r;
            }
            if (sz)
                dq.emplace_front(sz, cnt, cur), lim -= sz;
            if (cnt > lim)
                del_front(), ++lim;
        }
        printf("%lld ", max(cur, get_back() + s[m]));
    }
    putchar('\n');
    return 0;
}
```

---

## 作者：XZhuRen (赞：5)

DP 好题，细节较多，不是很好写。

### 引入

这个排列的限制很弱，可以忽略掉，因为每次有用的必然是前缀最大值，这个是不重的。

我们首先想一个 $\mathcal{O}(n^{2})$ 的 DP：

$f_{i,x}$ ：到第 $i$ 位，前缀最大值为 $x$ 的最大价值。

这个可以每次枚举没有存在的数字来转移，转移的时候取前缀最大值就好，遇到固定数字就把小于它的部分全部设为 $-\inf$。

### 性质分析

考虑利用 $C_{i} \uparrow $ 性质。

先考虑 $C_{i}$ 全部相同，且没有固定数字的情况：

相当于求从 $1$ 开始的最短极长上升子序列，对于每一个 $f_{i}$，**它的第二维是随 $x$ 上升单调不降的，且一定可以在下一次更新为 $f_{x-1}+C_{x}$（第一位保持原样不变）**。

这里由于 $C_{i}$ 单增，所以**一般地，$f_{i}$ 也有一样的性质**。

但是我们发现 $f_{i}$ 不一定连续，所以这里把所有未出现的数字独立出来，按照升序设为 $b_{i}$，略去第一维，设 $f_{j}$ 表示：当前前缀最大值为 $b_{j}$ 时的最大花费，这个是递增且连续的。

分离了之后再考虑固定的数字，
设 $g$ 为当前的前缀最大值恰为已确定数字的前缀最大值时的答案。

再利用前面的性质，

所以粗略的思维是：

1. 遇到不定数字的时候旋转一次序列，也就是进行一次全局 $f_{j-1}+C_{b_{j}} \to f_{j},(j\in (\min\{j\}(b_{j}>premx\{a_{i}\}),size_{b}])$ 操作，记为 $rotate()$，这时需要用 $g$ 尝试更新 $f$。

2. 对于一个**固定的**，且**可以作为前缀最大值的数 $a_{i}$**，我们检查删去 $b$ 中 $b_{j} \le a_{i}$ 的数，且利用这些数尝试更新 $g$。

这里有一些边界情况。

如果 $a_{i}$ **不是 $premax\{a_{i}\}$，或者前面按顺序填 $b$ 数组的所有小数字一定会使 $a_{i}<premax\{b\}$**，则 $a_{i}$ 是不能作为前缀最大值的，其**对应的** $g$ 是不存在的（记为 $-\inf$）。

我们的 $f$ 的第一个数字 $f_{start}$ 可以表示为 $\max(g,0)+C_{b_{start}}$。

### 具体实现：

记 $sumv(l,r)=\sum_{i=l}^{i=r} C_{b_{i}}$。

用一个双端队列 $q \in[head,tail]$（数组模拟）维护 $f$：

每次旋转操作相当于：在 $head$ 前加上一个 $0$，把 $tail$ 删除，记下旋转次数。

对于一个更改的元素，知道它当前代表的位置 $pos$，记录它的初值 $w$，与它是在**哪一次旋转后被加入的** $addtime$，它与当前总旋转次数的差 $_\Delta{t}$ 就可以计算出 它的当前值为 $w+sumv(pos-_\Delta{t}+1,pos)$。

然后用 $f$ 更新 $g$ 只需扫描前缀并删除，这一部分暴力即可，均摊是线性的。

用 $g$ 更新 $f$ 相当于给一段前缀赋值，**注意这里你的更新方式决定了你的比较方式，例如你先进行了一次 $rotate()$ 操作，那么下面你就需要把 $f_{j}$ 的值减去 $sumv(j,j)$**。

把每次赋值视为加入一段（类似珂朵莉树），这里加入的段数是 $\mathcal{O}(n)$ 的，但是变化的点数是 $\mathcal{O}(n^{2})$ 的，所以扫描一段连续的需要利用二分（二者的单调性不确定）。

更多细节见代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void in(T &n){
    n=0;char c=getchar();bool flag=0;
    for(;c<'0'||c>'9';c=getchar()) if (c=='-') flag=1;
    for(;c>='0'&&c<='9';c=getchar()) (n*=10)+=(c^48);
    if (flag) n=-n;
}
int wlsk[45];int wltp;
template<typename T>
void out(T n,char c=0){
    if (n==0){putchar('0');if (c)putchar(c);return ;}
    if (n<0) putchar('-'),n=-n;
    while(n) wlsk[++wltp]=(n%10),n/=10;
    while(wltp) putchar(wlsk[wltp--]^48);
    if (c) putchar(c);
}
const int N=1e6+5;
typedef long long ll1;
const ll1 inf=1e15+9;

ll1 val[N];
int n;
bool fixd[N];//是否是固定值。
int a[N];
int totb=0;
int b[N];
int premx[N];//前缀固定值最大值。
/*
考虑维护两个dp状态，f[]&g[]：
f：前缀最大值为x的最大价值。(x未在a[]中被固定)
g：前缀最大值为固定的premx的最大价值
所以有两种：
1.非固定：f[]：单调递增,且每次可以继承上一个f数组的值。
2.固定：用f[]更新g，下一个用g[]更新f[]
*/
ll1 sv[N];
int st;//b的开始位置，其余位置全部被ban掉
int spintimes=0;
ll1 Ans[N];
ll1 g;
ll1 sumv(int l,int r){if(l>r)return 0;return sv[r]-sv[l-1];}
namespace Deque{
	struct Node{
		int len;//长度
		ll1 w;//初始的值
		int adt;//加入的时间，用于计算出到底要加哪些cost
	//加入的时间，我们要找出这个颜色段加入的时间，
	//也就找出了它至今进行的多少次位移。
	//单次位移只需要累加次数并在开头插入0
	}q[N*4];
	int hd=N*2+1,tl=N*2;
	void split_front(){//尝试拆分头部
		if(hd>tl||q[hd].len==1)return;
		hd--;q[hd]=q[hd+1];
		q[hd].len=1,q[hd+1].len--;
	}
	void split_back(){//尝试拆分尾部
		if(hd>tl||q[tl].len==1)return;
		tl++;q[tl]=q[tl-1];
		q[tl].len=1,q[tl-1].len--;
	}
	void split_front_1(int lenth){
		hd--;q[hd]=q[hd+1];
		q[hd].len=lenth,q[hd+1].len-=lenth;
	}
	void pop_front(){split_front();hd++;}
	void pop_back(){split_back();tl--;}
	ll1 calc_front(){//计算头值
		if(hd>tl)return 0;
		int tmp=spintimes-q[hd].adt+1;//要旋转几次
		return q[hd].w+sumv(st-tmp+1,st);
	}
	ll1 calc_back(){//计算尾值
		if(hd>tl)return 0;
		int tmp=spintimes-q[tl].adt+1;
		return q[tl].w+sumv(totb-tmp+1,totb);
	}
	ll1 calc_front_1(int lenth){
		int tmp=spintimes-q[hd].adt+1;
		return q[hd].w+sumv(st+lenth-tmp,st+lenth-1);
	}
	void pop_front_1(){hd++;}
	void push_front(Node x){q[--hd]=x;}
	void push_back(Node x){q[++tl]=x;}
	void rotate(){
		spintimes++;
		push_front((Node){1,0,spintimes});
		pop_back();
	}
}//珂朵莉队列：颜色并不均摊堆。
bool flag_1[N];
void work(){
	using namespace Deque;
	st=1;//开始为b[1]
	int cnt=0;
	ll1 tg=0;
	push_front((Node){totb,0,1});
	for(int i=1;i<=n;i++){
		if(a[i]>0){//这一位填固定的，但是：
			if(a[i]==premx[i]){
				//更新了最大值，不更新最大值相当于没影响，直接跳过
				//收缩至合适的b[i]
				//最后一个删除的f[]更新g[i]
				tg=g+val[a[i]];
				for(;hd<=tl&&b[st]<a[i];st++){//把小于a[i]的全部弹掉
					tg=max(tg,calc_front()+val[a[i]]);
					pop_front();
				}
				if(flag_1[i])g=-inf;
				else g=tg;
			}
		}else{//这一位填浮动的
			//考虑两个事情：
			//1.旋转一次
			//2.用g[i]更新f
			//如何用g[i]更新：不断往后跳直到找到大于的,累加它们的计数作为len。
			cnt=0;
			rotate();
			for(;hd<=tl;){
			 	if(calc_front()>=g+sumv(st,st))break;
			 	if(calc_front_1(q[hd].len)<g+sumv(st,st)){
			 		st+=q[hd].len,cnt+=q[hd].len;
			 		pop_front_1();
			 		continue;
			 	}
			 	int l=1,r=q[hd].len,md,tres=0;
			 	while(l<=r){
			 		md=(l+r)>>1;
			 		if(calc_front_1(md)<g+sumv(st,st))tres=md,l=md+1;
			 		else r=md-1;
			 	}
			 	split_front_1(tres),pop_front_1();
			 	st+=tres,cnt+=tres;
			}
			st-=cnt;
			if(cnt)push_front((Node){cnt,g,spintimes});
		}
		Ans[i]=g;
		if(hd<=tl)Ans[i]=max(Ans[i],calc_back());//没删完的时候还有值
		out(Ans[i],' ');
	}
}
int main(){
	in(n);
	for(int i=1;i<=n;i++){
		in(a[i]);
		fixd[a[i]]=1;
		premx[i]=max(a[i],premx[i-1]);//前缀值mx
	}
	for(int i=1;i<=n;i++)in(val[i]);
	for(int i=1;i<=n;i++){
		if(fixd[i])continue;
		b[++totb]=i;//浮动值
	}
	for(int i=1;i<=totb;i++)sv[i]=sv[i-1]+val[b[i]];
	for(int tc=0,i=1;i<=n;i++){
		if(a[i]==-1)tc++;
		if(a[i]!=premx[i])continue;
		if(a[i]<b[tc])flag_1[i]=1;
	}
	work();
	return 0;
}
```

---

## 作者：takanashi_mifuru (赞：2)

细节有点太友好了……

题意是，从第一个位置开始往后走，然后每次能取一个键值更大的，就换成更大的，问最后被取到的点的权值和最大是多少。

注意到这个取值的模式很容易导出一个平方的 dp，你设 $dp_{i,j}$ 表示到第 $i$ 个点同时前面的最大值为 $j$，那么假设我们枚举到了一个定值，我们就把在这个定值以下的全部强制更新到定值上，定值以上的状态不变，否则的话枚举上一位选什么以及这一位选什么，判掉非法状态（已经被定值填在后面或者最小值都没办法填出这么小），然后就可以直接转移了。

但是这个形式非常的不好，为啥不好呢，合法状态不连续，因为有可能定值在后面使得中间挖了几个空。

于是我们把定义改掉，把这个定值独立出来（因为你考虑如果想要使用定值的状态，其实只有当前的前缀最大值有效），那么对于非定值容易发现他变得连续了，因为给到他的限制只有不能填得特别小了。

写到这里整理一下转移式子，容易发现有一个前缀 max，这个东西显然随着下标单调不降，而每个点的点权也随着下标单调不降，所以更新出来的 dp 数组也单调不降，所以前缀 max 可以直接写成 $dp_{i-1,j-1}$，所以操作相当于是位移一位。

然而位移一位还要统计权值是难以做到的，我们考虑不让数字位移而是让数轴位移，那么每个点相当于是向后找一个区间的贡献。

好，写完发现根本没法过，因为我们把定值给忘掉了，现在的非定值 dp 数组传下来的值都可以被定值 dp 更新，而定值 dp 只有一个数，所以这个问题就变成了全局 chkmax，但是 dp 数组是单调不降的，所以就变成了前缀赋值，考虑颜色段均摊一下暴力找就可以了。

啊，这个题没法不提实现细节，考虑咋实现呢，你可以写一个双端队列来维护这个位移（具体就是把最后一个扔出去再插一个 0 到最开头），然后考虑写一个时间标记 $need$，假设现在的时间是 $tim$，那么我们就相当于是有 $tim-need$ 的时间这个东西在做位移，而假设移到了当前点 $now$，则区间 $[now-(tim-need)+1,now]$ 的所有非定值的 $c$ 的和都需要加回来，于是我们成功地这么设计一个标记使得我们能够快速调取一个点的值。

**因为要先位移再 chkmax，所以在调取值的时候一定一定要使用位移之前的下标而非位移之后的下标。**

同时不要用下标来维护更新时间，而是另外起一个变量，因为如果是定值并不会操作位移。

最后求答案可以直接把定值答案和非定值的最后一个拿出来取 max，这个比较容易。

还有注意先塞 $0$ 再丢非法值，因为更新和丢值本来是同时进行的，我们使用双端队列导致我们必须决定先后顺序，那为了正常更新我们就要把 0 拉出去垫背了。

然后就做完了，因为取到边界的时候可能有一个颜色段会被不完整的切割出来这个时候需要二分所以时间复杂度为 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[400005];
int c[400005];
bool vis[400005];
int pre[400005];
int need[400005];
int rnk[400005];
int dp[400005];
int f[400005];
int g;
int val[400005],pos;
int pmax[400005];
int premax[400005];
int Min[400005];
int ans[400005];
int prec[400005];
struct node{
	int val,need,len;
};
int getval(node tmp,int now,int tim){
	int need=tim-tmp.need;
	return tmp.val+prec[now]-prec[now-need];
}
deque<node> dq;
void solve(int ed){
	for(int i=1;i<=n;i++){
		if(!vis[i])val[++pos]=i;
	}
	int gnow=0;
	for(int i=1;i<=n;i++){
		if(a[i]==-1)gnow++;
		Min[i]=gnow;
	}
	for(int i=1;i<=n;i++){
		premax[i]=max(premax[i-1],a[i]);
	}
	int now=n;
	int low=1;;
	int st=1;
	if(a[1]>0){
		low=1;
		g=c[a[1]];
		while(val[low]<a[1])low++;
		ans[1]=g;
		st=low;
		for(int i=low;i<=pos;i++)dq.push_back(node{0,2,1});
	} 
	else{
		for(int i=1;i<=pos;i++){
			dp[i]=c[val[i]];
			ans[1]=max(ans[1],dp[i]);
			dq.push_back(node{c[val[i]],2,1});
		}
	}
	for(int i=1;i<=pos;i++){
		prec[i]=prec[i-1]+c[val[i]];
	}
	int nowtim=2;
	for(int i=2;i<=n;i++){
		if(a[i]>0){
			int k=low;
			if(premax[i]==a[i]){
				g=g+c[a[i]];
			}
			while(low<=pos&&val[low]<a[i]){
				g=max(g,getval(dq.front(),low,nowtim)+c[a[i]]);
				low++;
				dq.front().len--;
				if(!dq.front().len)dq.pop_front();
			}
			if(val[Min[i]]>premax[i])g=0;
			ans[i]=g;
			if(dq.size())ans[i]=max(ans[i],getval(dq.back(),pos,nowtim));
			continue;
		}
		dq.push_front(node{0,nowtim,1});
		int num=Min[i]-low;
		while(num>0){
			num--;
			dq.front().len--;
			if(!dq.front().len)dq.pop_front();
		}
		low=max(low,Min[i]);
		if(dq.back().len>1)dq.back().len--;
		else dq.pop_back();
		int st=low;
		while(dq.size()){
			int gp=dq.front().val;
			int lt=st;
			int rt=lt+dq.front().len-1;
			int need=dq.front().need;
			int neta=getval(dq.front(),rt-1,nowtim);
			if(neta<=g){
				st=rt+1;
				dq.pop_front();
				continue;
			}
			int L=lt-1,R=rt+1;
			while(L+1<R){
				int mid=L+R>>1;
				int vnow=getval(dq.front(),mid-1,nowtim);
				if(vnow<=g)L=mid;
				else R=mid;
			}
			st=L+1;
			node tmp=dq.front(); 
			tmp.len=rt-st+1;
			dq.pop_front();
			dq.push_front(tmp);
			break;
		}
		if(st>low)dq.push_front(node{g,nowtim,st-low});
		if(val[Min[i]]>premax[i]){
			g=0;
		}
		ans[i]=g;
		nowtim++;
		if(dq.size()){
			ans[i]=max(ans[i],getval(dq.back(),pos,nowtim));
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",ans[i]);
	}
	puts("");
	return;
}
signed main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]>0)vis[a[i]]=true,rnk[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&c[i]);
	}
	for(int i=1;i<=n;i++){
		pre[i]=pre[i-1]+(a[i]>0);
	}
	for(int i=1;i<=n;i++){
		need[i]=need[i-1]+(!vis[i]);
	}
	for(int i=1;i<=n;i++){
		pmax[i]=max(pmax[i-1],a[i]);
	}
	solve(n);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P11331)

**题目大意**

> 给定 $w_1\sim w_n$，定义一个序列的权值 $p$ 为所有前缀最大值 $x$ 处的 $\sum w_{p_x}$。
>
> 已知排列 $a$ 中的若干元素，对于每个前缀求其权值的最大值。
>
> 数据范围：$n\le 4\times 10^5$。

**思路分析**

朴素 dp 就是 $f_{i,j}$ 表示 $[1,i]$ 最大值为 $j$ 的方案数，但此时 $f$ 中有很多零散的 $-\infty$，难以维护。

我们把已经在 $a$ 中出现的 $j$ 从状态中删掉，然后对于 $a_i\ne -1$ 的点特殊维护 $f_{i,a_i}$ 并删除 $f_i$ 中的一段前缀。

此时 $f_{i,j}$ 是单调递增的（$f_{i,j}$ 的解把 $j$ 换成 $j+1$ 就得到 $f_{i,j+1}$ 的解）。

那么对于一个 $a_i=-1$ 的点，转移就是 $f_{i,j}\gets\max(f_{i-1,j-1}+v_j,f_{i-1,j})$，其中 $v_j$ 是第 $j$ 个 $\not\in A$ 的数的权值。

直接使用数据结构维护这个过程是不可能的。

但我们发现 $f_{i,j}-v_j\le f_{i,j-1}$，在最优解处把 $j$ 换成 $j-1$ 就能证明。

因此这个操作直接就变成 $f_{i,j}\gets f_{i-1,j-1}+v_j$。

设 $k=\max f_{i,a_i}$，那么还有一个操作是 $f_{i,j}\gets k+v_j$，这个操作不好维护，但是我们可以转而维护 $f_{i,j}-v_j$。

很显然这个式子也有单调性，相当于不考虑最大值的贡献，此时 $j$ 越大对前面的限制依然越宽松，这样这个转移就变成了全局 chkmax，也就是前缀赋值操作，前一个转移变成 $f_{i,j}\gets f_{i-1,j-1}+v_{j-1}$。

现在我们只要用数据结构维护这个简单 dp 即可。

首先操作二先把所有数循环移位一下，然后打一个懒标记 $k$ 表示 $f_{i,j}$ 要加上 $v_{j-k}\sim v_{j-1}$。

前缀赋值操作可以用颜色段均摊，动态维护 $f$ 初值相同的连续段，暴力弹出开头的若干 $<k$ 的连续段，并且在最后一段上二分分界点即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define LF dp.front()
#define RF dp.back()
using namespace std;
const int MAXN=4e5+5;
const ll inf=1e18;
int n,a[MAXN],st[MAXN],v[MAXN],w[MAXN];
ll sv[MAXN];
bool vs[MAXN];
int hd=1,tl=0,tg=0;
struct info {
	int len,tg; ll val;
};
deque <info> dp;
ll qryL(int p=hd) {
	if(dp.empty()) return -inf;
	return LF.val+sv[p-(tg-LF.tg)]-sv[p];
}
ll qryR() {
	if(dp.empty()) return -inf;
	return RF.val+sv[tl-(tg-RF.tg)]-sv[tl];
}
void popL() { if(!--LF.len) dp.pop_front(); }
void popR() { if(!--RF.len) dp.pop_back(); }
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) {
		cin>>a[i];
		if(~a[i]) vs[a[i]]=true;
	}
	for(int i=1;i<=n;++i) {
		cin>>w[i];
		if(!vs[i]) st[++tl]=i,v[tl]=w[i];
	}
	for(int i=tl;i>=0;--i) sv[i]=sv[i+1]+v[i];
	ll pr=0; dp.push_back({tl,tg,-inf});
	for(int i=1,pmx=0;i<=n;++i) {
		if(a[i]==-1) {
			ll z=qryL(); ++tg;
			if(dp.size()) popR(),dp.push_front({1,tg,z});
			int sz=0;
			while(dp.size()&&qryL(hd+LF.len-1)<pr) hd+=LF.len,sz+=LF.len,dp.pop_front();
			if(dp.size()) {
				int l=1,r=LF.len,d=0;
				while(l<=r) {
					int mid=(l+r)>>1;
					if(qryL(hd+mid-1)<pr) d=mid,l=mid+1;
					else r=mid-1;
				}
				sz+=d,hd+=d,LF.len-=d;
			}
			if(sz) dp.push_front({sz,tg,pr}),hd-=sz;
			if(hd<tg) popL(),++hd;
		} else if(a[i]>pmx) {
			ll mx=pr; pmx=a[i];
			for(;hd<=tl&&st[hd]<a[i];++hd) mx=max(mx,qryL()+v[hd]),popL();
			pr=(hd>tg?mx+w[a[i]]:-inf);
		}
		cout<<max(pr,qryR()+v[tl])<<" \n"[i==n];
	}
	return 0;
}
```

---

## 作者：一只绝帆 (赞：0)

考虑先搞出一个 $\text{poly}(n)$ 的做法，所以我们先枚举每个前缀。

我们发现只需关心前缀最大值，前缀最大值更大的一定没填，更小的一定没用（可以随便当占位符）。

$f_{i,j}$ 表示前 $i$ 个，前缀最大值是 $j$，其实无需枚举前缀，得到了一个平方做法。

接下来，如果你顺着优化空间复杂度，从而只关心那些确定的位置，而在非确定的位置贪心，你就走入歧途了。

题目中还有一个关键性质我们没用：$C$ 单调。

考虑先规范化我们的状态，若 $j$ 中的数不是自由数，那一定是非自由数的前缀最大值，于是我们设 $g_i$ 表示 $j$ 是这种数，而原来的 $f_{i,j}$，我们可以把 $j$ 离散化。

如果不考虑 $g$，则现在的转移变成了 $\max(f_{i-1,j},f_{i-1,j-1}+c_j)\to f_{i,j}$（$f_{i-1,<j}$ 由于状态的单调性，可以简化为 $f_{i-1,j-1}$）。

不妨考虑整体 $\rm dp$，我们惊奇地发现 $f_{i-1,j-1}+c_j$ 比 $f_{i-1,j}$ 要优秀（$c$ 是单调的，$i-1$ 比 $i$ 差的那个数肯定不如 $c_i$），换句话说我们仅仅是平移然后加上对应位置的值，而免去了取 $\max$。 

你可能会觉得这没什么大不了的，不就是没有确定的位置时我们应该从大往小填嘛。

但我们还有新的性质：$f_{i,j}-c_j$ 对于 $j$ 来说仍然是单调的，这是由转移的范围决定的，也就是说 $g+c_j\to f_j$ 这个转移也只会更改一段前缀。

于是事情就变得相当简单了，我们需要支持：

- 删除前缀，全局对一个数取 $\max$（填平前缀）。
- 向后平移一位并 $\text{push\_front}$，加对应位置的数。

最后一个操作可以直接打标记，标记的含义是加了向前一段 多长 的区间和。

前缀赋值可以直接颜色段均摊，我们定义能被表示成一个值打了一个标记（信息量可接受）的区间是一个段，使用 `std::deque` 来维护段，每次是 pop 若干个段并在最后一个段中二分，裂开该段并把前缀变成新段。

全局打标记，我们可以记录每个段比全局标记多多少，这样每个段加一只需把全局标记减一，因为我们对标记的支持仅仅是查询一个节点的标记、加入新点、全局加。

实现上有一坨细节，注意仅在经过的 $-1$ 的个数 $\le$ 我们钦定的前缀最大值的排名时，我们才可以选择填一个“占位符”，否则我们必须删掉该位置的合法性，保留会导致更优的解。

[code](https://www.luogu.com.cn/paste/9yu8ucah)。

---

