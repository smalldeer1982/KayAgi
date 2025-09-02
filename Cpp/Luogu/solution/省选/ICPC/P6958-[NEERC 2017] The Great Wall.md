# [NEERC 2017] The Great Wall

## 题目描述

最近你成为了西奈一个小国家的皇帝。你决定在边界建造一座长城保护你的国家不被野蛮人抢劫。你联系了“W Corp”——世界上唯一的建造坚不可摧的墙的公司。

“W Corp”用相同的格式建造所有墙。墙的长度是 $n$ 米，每一米墙按顺序从 $1$ 到 $n$ 编号，它们可能有不同的高度。高度的格式取决于三个固定的数组 $a,b,c$，它们各有 $n$ 个元素，对于任意 $1\le i\le n$ 满足 $a_i < b_i < c_i$，还有一个整数 $r\ (1\le r < n)$。三个数组和 $r$ 对于“W Corp”建造的任何墙都是相同的。

按照如下方式，具体的墙体设计的选择取决于两个不同的整数 $x,y\ (1\le x < y\le n-r+1)$。取两个整数区间：$[x,x+r-1]$ 和 $[y,y+r-1]$（区间包括端点）。那么第 $i$ 米墙的高度是：

- $a_i$，当 $i$ 不属于这两个区间
- $b_i$，当 $i$ 属于这两个区间中的恰好一个
- $c_i$，当 $i$ 属于这两个区间中的两个

墙的**强度**定义为每一米墙高度的和。

在“W Corp”建造的所有墙中，数组 $a,b,c$ 和整数 $r$ 都是固定的。公司提供了一份所有可能的墙体设计的列表，按照强度单调不减排序。你选择了其中第 $k$ 种墙体设计。你的任务是，求出你选择的墙的强度。

## 样例 #1

### 输入

```
4 2 1
1 2 3 4
3 3 5 5
7 7 7 7
```

### 输出

```
16
```

# 题解

## 作者：Starlight237 (赞：5)

小清新双指针+树状数组，不需要离散化/主席树/平衡树之类的东西。

> (**2021集训队作业 P6958 【[NEERC2017]The Great Wall】**)给定三个序列 $\{a_{0,n}\},\{a_{1,n}\},\{a_{2,n}\}(a_{i,j}<a_{i+1,j})$，你需要选择两个不同的长度为 $r$ 的区间 $I,J$，使得 $w(I,J)$ 是所有情况中第 k 小的。定义 $w(I,J)=\sum a_{[i\in I]+[i\in J],i}$。注意，$(I,J)$ 和 $(J,I)$ 视为相同的方案。

考虑二分答案 $x$，转化为统计答案不超过 $x$ 的方案个数是否至少有 k 个。首先可以将 $a_{1}$ 和 $a_2$ 中每个元素都减去 $a_0$ 对应位置的元素，最后答案加上 $a_0$ 中所有元素之和，转换成对于两个数组的问题 $b_{1,i}=a_{1,i}-a_{0,i},b_{2,i}=a_{2,i}-a_{0,i}$。

Case 1. $I\cap J=\varnothing$

设两个区间分别为 $I=[s,s+r-1]$ 和 $J=[t,t+r-1]$，则 $w(I,J)=\sum_{i\in I}b_{1,i}+\sum_{j\in J}b_{1,i}$，考虑前缀和优化，令 $pre_i=\sum_{j=1}^ib_{1,j}$，则 $w(I,J)=pre_{s+r-1}-pre_{s-1}+pre_{t+r-1}-pre_{t-1}$。设 $f_i=pre_{i+r-1}-pre_{i-1}$，则 $w(I,J)=f_s+f_t$。于是需要求出有多少对 $s,t$，满足 $1\le s\le n-2r+1,s+r\le t\le n-r+1,f_s+f_t< x$(我们不妨设 $J$ 在 $I$ 右边)，显然是一个二维数点问题。

Case 2. $I\cap J\not=\varnothing$

则 $w(I,J)=\sum_{i=s}^{t-1}b_{1,i}+\sum_{i=t}^{s+r-1}b_{2,i}+\sum_{i=s+r}^{t+r-1}b_{1,i}$，再令 $pre'_i=\sum_{j=1}^ib_{2,j},g_i=pre'_{i+r-1}-pre_{i-1}-pre_{i+r-1},h_i=pre_{i-1}-pre'_{i-1}+pre_{i+r-1}$，则 $w(I,J)=g_s+h_t$。于是也是一个二维数点：$1\le s< n-r+1,s< t\le\min(s+r-1,n-r+1),g_i+h_i< x$

双指针+BIT 即可。

```cpp
#define ll long long
#define pli pair<ll, int>
const int N = 30010;
int n, m, r, k, tr[N];
ll a[N], b[N], c[N];
pli f[N], g[N], h[N];
#define lowbit(x) ((x) & -(x))
inline void add(int x, int v) {
	for (; x <= m; x += lowbit(x)) tr[x] += v;
}
inline int qry(int x) {
	int sm = 0;
	for (; x > 0; x -= lowbit(x)) sm += tr[x];
	return sm;
}
inline int calc(ll x) {
	memset(tr, 0, sizeof tr);
	int cnt = 0;
	for (int t = m, s = 1; t; --t) {
		for (; s <= m && f[s].first + f[t].first <= x; ++s) add(f[s].second, 1);
		cnt += qry(f[t].second - r);
	}
	memset(tr, 0, sizeof tr);
	for (int t = m, s = 1; t; --t) {
		for (; s <= m && g[s].first + h[t].first <= x; ++s) add(g[s].second, 1);
		cnt += qry(h[t].second - 1) - qry(h[t].second - r);
	}
	return cnt;
}
int main() {
	n = rd(), r = rd(), k = rd(), m = n - r + 1;
	ll sm = 0;
	for (int i = 1; i <= n; ++i) a[i] = rd(), sm += a[i];
	for (int i = 1; i <= n; ++i) b[i] = b[i - 1] + rd() - a[i];
	for (int i = 1; i <= n; ++i) c[i] = c[i - 1] + rd() - a[i];
	for (int i = 1; i <= m; ++i)
		f[i] = make_pair(b[i + r - 1] - b[i - 1], i),
		g[i] = make_pair(c[i + r - 1] - b[i - 1] - b[i + r - 1], i),
		h[i] = make_pair(b[i - 1] - c[i - 1] + b[i + r - 1], i);
	sort(f + 1, f + m + 1), sort(g + 1, g + m + 1), sort(h + 1, h + m + 1);
	ll l = 0, r = c[n], mid, ans = 0;
	while (l <= r)
		mid = l + r >> 1, calc(mid) >= k ? ans = mid, r = mid - 1 : l = mid + 1;
	printf("%lld", sm + ans);
	return 0;
}
```

---

## 作者：鏡音リン (赞：5)

简要题意：给定三个长度为 $n$ 的整数数组 $a,b,c$ 和整数 $r$，且满足对于任意 $1\le i\le n$ 都有 $a_i<b_i<c_i$。在区间 $[1,n]$ 的所有长度为 $r$ 的子区间里不分顺序地选出两个，记作 $X,Y$。定义这次选择的权值为：

$$\sum_{i=1}^na_i[i\notin X\land i\notin Y]+\sum_{i=1}^nb_i[i\in X\oplus i\in Y]+\sum_{i=1}^nc_i[i\in X\land i\in Y]$$

求所有 $\frac{(n-r)(n-r+1)}{2}$ 种不同的选择方式中，权值第 $k$ 小的选择的权值是多少。

考虑二分答案。设当前二分中点为 $m$，统计权值小于 $m$ 的选择方案数，若大于 $k-1$ 则答案小于 $m$，否则答案大于等于 $m$。

令数组 $A,B,C$ 分别为 $a,b,c$ 的前缀和数组。令 $X=[x+1,x+r],Y=[y+1,y+r]$。由于 $X,Y$ 不分顺序，不妨设 $x<y$。按照 $X,Y$ 是否有交分类讨论，分别计算两类的选择方案数。

若 $X,Y$ 无交即 $x+r\le y$，则该方案的权值为 $A_x+B_{x+r}-B_x+A_y-A_{x+r}+B_{y+r}-B_y+A_n-A_{y+r}$。把上式中与 $y$ 有关的项记作 $F(y)$，无关的项记作 $G(x)$。如果枚举 $x$，相当于对每个 $x$ 求满足 $F(y)<m-G(x)$ 且 $y\ge x+r$ 的 $y$ 的数量。可以使用平衡树，从大到小枚举 $x$，一边插入 $F(x+r)$，一边查询平衡树中小于 $m-G(x)$ 的数的数量。

若 $X,Y$ 有交即 $x<y<x+r$，则该方案的权值为 $A_x+B_y-B_x+C_{x+r}-C_y+B_{y+r}-B_{x+r}+A_n-A_{y+r}$。可以用类似的方法，区别在于 $y$ 的范围变为了 $x<y<x+r$，可以先求出 $y>x$ 的方案数，再把 $y\ge x+r$ 的减去。

总时间复杂度为 $O(n\log n\log C_n)$，其中$C_n$ 作为二分的初始右边界。

---

## 作者：Loser_Syx (赞：1)

二分一个 $x$ 表示 $ans \leq x$ 的个数，那么只需要找到第一个 $\geq k$ 的就是答案，单调性显然。

我们发现对于两个区间 $[a,a+r-1],[b,b+r-1]$ 来说，他们只有两种情况，交与不交，于是考虑分类讨论计算出这两种的个数。

- 不交

  这个是简单的，我们对于每个区间处理它的 $b_i-a_i$，那么就是我们如果选这个区间的话就会增加这么多，自然地考虑按大小排序后二维数点，比如可以枚举 $b$ 然后查询 $x \leq b-r$ 的 $a$ 个数。

- 交

  那么被覆盖的区间就变成了一个“五段式”，为 $\texttt{abcba}$ 样子的，还是考虑维护 $s1_i=b_i-a_i+s1_{i-1}$ 和 $s2_i=c_i-a_i+s2_{i-1}$，这样子我们就可以通过前缀和快速得出组合出的答案是多少，这个 $\texttt{bcb}$ 段的四个端点分别是 $a,b,a+r-1,b+r-1$，同样的二位数点即可。

```cpp
const int N = 1e5 + 19;
int a[N], b[N], c[N], n, m, r, k;
pii A[N], B[N], C[N];
struct BIT {
	int t[N];
	void clear() {
		for (int i=0;i<N;++i) t[i]=0;
	}
	void add(int x, int s) {
		while (x < N) {
			t[x] += s; 
			x += lowbit(x);
		}
	}
	int ask(int x, int ans = 0) {
		while (x > 0) {
			ans += t[x];
			x -= lowbit(x);
		} return ans;
	}
	int query(int l, int r) { return ask(r) - ask(l-1); }
} bit;
int check(int x) {
	int tot = 0;
	bit.clear();
	for (int i=m,j=1;i;--i) {
		while (j<=m&&A[i].F+A[j].F<=x) bit.add(A[j++].S,1);
		tot+=bit.ask(A[i].S-r);
	}
	bit.clear();
	for (int i=m,j=1;i;--i) {
		while (j<=m&&B[i].F+C[j].F<=x) bit.add(C[j++].S,1);
		tot+=bit.query(B[i].S-r+1,B[i].S-1);
	}
	return tot >= k;
}
signed main() {
	read(n, r, k); m = n - r + 1;
	for (int i=1;i<=n;++i) read(a[i]);
	for (int i=1;i<=n;++i) b[i]=b[i-1]+read()-a[i];
	for (int i=1;i<=n;++i) c[i]=c[i-1]+read()-a[i];
	for (int i=1;i<=m;++i) {
		A[i]={b[i+r-1]-b[i-1],i};
		B[i]={-c[i-1]+b[i-1]+b[i+r-1],i};
		C[i]={c[i+r-1]-b[i-1]-b[i+r-1],i};
	}
	sort(A+1,A+1+m); sort(B+1,B+1+m); sort(C+1,C+1+m);
	int l=0,r=1e18;
	while (l < r) {
		int mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	for (int i=1;i<=n;++i) r+=a[i];
	write(r);
	return 0;
}
```

---

