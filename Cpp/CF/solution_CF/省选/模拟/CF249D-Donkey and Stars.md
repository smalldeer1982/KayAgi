# Donkey and Stars

## 题目描述

In the evenings Donkey would join Shrek to look at the stars. They would sit on a log, sipping tea and they would watch the starry sky. The sky hung above the roof, right behind the chimney. Shrek's stars were to the right of the chimney and the Donkey's stars were to the left. Most days the Donkey would just count the stars, so he knew that they are exactly $ n $ . This time he wanted a challenge. He imagined a coordinate system: he put the origin of the coordinates at the intersection of the roof and the chimney, directed the $ OX $ axis to the left along the roof and the $ OY $ axis — up along the chimney (see figure). The Donkey imagined two rays emanating from he origin of axes at angles $ α_{1} $ and $ α_{2} $ to the $ OX $ axis.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/01e07f49112d306c9832b3ead8a5e8c0cfbcc93c.png)Now he chooses any star that lies strictly between these rays. After that he imagines more rays that emanate from this star at the same angles $ α_{1} $ and $ α_{2} $ to the $ OX $ axis and chooses another star that lies strictly between the new rays. He repeats the operation as long as there still are stars he can choose between the rays that emanate from a star.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/87b736a4eb176865176dd95be306088882057bc0.png)As a result, the Donkey gets a chain of stars. He can consecutively get to each star if he acts by the given rules.

Your task is to find the maximum number of stars $ m $ that the Donkey's chain can contain.

Note that the chain must necessarily start in the point of the origin of the axes, that isn't taken into consideration while counting the number $ m $ of stars in the chain.

## 说明/提示

In the sample the longest chain the Donkey can build consists of four stars. Note that the Donkey can't choose the stars that lie on the rays he imagines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/9b10980b4f4e779f5c4c6a72105611e261a67332.png)

## 样例 #1

### 输入

```
15
1/3 2/1
3 1
6 2
4 2
2 5
4 5
6 6
3 4
1 6
2 1
7 4
9 3
5 3
1 3
15 5
12 4
```

### 输出

```
4
```

# 题解

## 作者：Fido_Puppy (赞：4)

$$\texttt{Foreword}$$

上午刚讲完线性代数，和往常一样又没听懂，课后作业有这么一道，就来讲讲这道题如何不用线性代数做。

当然会线性代数肯定代码更好写并且时间复杂度更优，这篇题解专门面向像我一样不会线性代数的蒟蒻。

$$\texttt{Description}$$

[CF249D Donkey and Stars](https://www.luogu.com.cn/problem/CF249D)

$$\texttt{Solution}$$

我们能够把这道题转换为最长上升子序列问题，然后我们考虑两个点 $(x_i, y_i)$ 和 $(x_j, y_j)$ 要满足什么条件才能从 $j$ 转移到 $i$。

首先肯定要满足 $x_i > x_j$。

然后我们考虑斜率的两个限制。

对于第一个斜率大于 $\dfrac{a}{b}$ 的限制：

$$\dfrac{y_i - y_j}{x_i - x_j} > \dfrac{a}{b}$$

$$(y_i - y_j) \times b > (x_i - x_j) \times a$$

$$y_i \times b - y_j \times b > x_i \times a - x_j \times a$$

$$y_i \times b - x_i \times a > y_j \times b - x_j \times a$$

对于第二个斜率小于 $\dfrac{c}{d}$ 的限制，同理可得：

$$y_i \times d - x_i \times c < y_j \times d - x_j \times c$$

所以我们设 $F(i) = y_i \times b - x \times a, G(i) = y_i \times d - x_i \times c$。

就可以得到从 $j$ 转移到 $i$ 的条件：

$$x_i > x_j, F(i) > F(j), G(i) < G(j)$$

这明显可以对于 $\forall i \in [1, n], F(i)$ 和 $G(i)$ 离散化后，用 $\text{cdq}$ 分治优化转移。

$\text{cdq}$ 分治不会的可以右转 [OI Wiki](https://oi-wiki.org/misc/cdq-divide/)。

时间复杂度 $\mathcal{O(n \log^2 n)}$。

$$\texttt{Notice}$$

由于 $x, y, a, b, c, d \leq 10^5$，所以在计算 $y \times b - x \times a$ 或者 $y \times d - x \times c$ 时可能会爆 $\text{int}$。

由于起始点必须是原点，我们可以把原点加入之后，反着进行 $\text{dp}$，这样就变成了终点必须是原点，就取原点的 $\text{dp}$ 值即可。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' ' && __c != '\n' && __c != '\r'; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

int n, a, b, c, d, M1, M2;
ll dis1[N], dis2[N], B[N], C[N];

struct Node {
	int a, b, c, dp;
}f[N];

int t[N];
inline int lowbit(int x) {
	return x & (-x);
}

inline void update(int x, int v) {
	while (x > 0) {
		t[x] = max(t[x], v);
		x -= lowbit(x);
	}
}

inline void clear(int x) {
	while (x > 0) {
		t[x] = 0;
		x -= lowbit(x);
	}
}

inline int query(int x) {
	int ans = 0;
	while (x <= M1) {
		ans = max(ans, t[x]);
		x += lowbit(x);
	}
	return ans;
}

inline bool cmp1(Node A, Node B) {
	if (A.a ^ B.a) return A.a > B.a;
	if (A.c ^ B.c) return A.c < B.c;
	if (A.b ^ B.b) return A.b > B.b;
}

inline bool cmp2(Node A, Node B) {
	if (A.c ^ B.c) return A.c < B.c;
	if (A.b ^ B.b) return A.b > B.b;
	if (A.a ^ B.a) return A.a > B.a;
}

void cdq(int l, int r) {
	if (l == r) {
		f[l].dp++; return ;
	}
	int mid = l + r >> 1;
	cdq(l, mid);
	sort(f + l, f + mid + 1, cmp2);
	sort(f + mid + 1, f + r + 1, cmp2);
	int L = l;
	for (int R = mid + 1; R <= r; R++) {
		while (L <= mid && f[L].c < f[R].c) update(f[L].b, f[L].dp), L++;
		f[R].dp = max(f[R].dp, query(f[R].b + 1));
	}
	for (int i = l; i < L; i++) clear(f[i].b);
	sort(f + l, f + mid + 1, cmp1);
	sort(f + mid + 1, f + r + 1, cmp1);
	cdq(mid + 1, r);
}

int main() {
	gi(n); n++;
	gi(a); gi(b); gi(c); gi(d);
	dis1[1] = dis2[1] = f[1].a = f[1].b = f[1].c = f[1].dp = 0;
	for (int i = 2; i <= n; i++) {
		int x, y; gi(x); gi(y);
		f[i].a = x;
		dis1[i] = B[i] = 1ll * y * b - 1ll * x * a;
		dis2[i] = C[i] = 1ll * y * d - 1ll * x * c;
		f[i].dp = 0;
	}
	sort(dis1 + 1, dis1 + n + 1); sort(dis2 + 1, dis2 + n + 1);
	M1 = unique(dis1 + 1, dis1 + n + 1) - dis1 - 1;
	M2 = unique(dis2 + 1, dis2 + n + 1) - dis2 - 1;
	for (int i = 1; i <= n; i++) {
		f[i].b = lower_bound(dis1 + 1, dis1 + M1 + 1, B[i]) - dis1;
		f[i].c = lower_bound(dis2 + 1, dis2 + M2 + 1, C[i]) - dis2;
	}
	sort(f + 1, f + n + 1, cmp1);
	cdq(1, n);
	print(f[n].dp - 1);
	return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：zhylj (赞：3)

考虑令 $\mathbf u = (b,a),\mathbf v = (d,c)$，我们把所有 $(x_i,y_i)$ 表示成 $(\lambda_i,\mu_i)$，使得 $\lambda_i\mathbf u + \mu_i\mathbf v = (x_i,y_i)$，然后重新画在平面上，那么一个点 $(\lambda_i,\mu_i)$ 能看到的点 $(\lambda_j,\mu_j)$ 必然满足 $\lambda_i < \lambda_j$ 且 $\mu_i < \mu_j$，显然就是一个 LIS ，使用线段树优化 DP 就可以在 $\mathcal O(n\log n)$ 的时间内完成本题。

[代码链接](https://codeforces.com/contest/249/submission/124466210).

---

## 作者：Francais_Drake (赞：1)

### 题意
坐标系上给出 $n$ 个点，第 $i$ 个点为 $(x_i,y_i)$ 且这些点两两不同。求最多有多少个点依次连成的折线上的线段的斜率在 $\frac ab$ 到 $\frac cd$ 之间（**不包括** $\boldsymbol{\frac ab}$ **和** $\boldsymbol{\frac cd}$）。折线必须从坐标原点开始且坐标原点不计入答案。$1\le n,x_i,y_i\le 10^5,\boldsymbol{0\le}\ a,b,c,d\le 10^5,\frac ab<\frac cd$。
### 解法
考虑把两个点的斜率用另一种方式表示：$i$ 和 $j$ 之间的斜率在 $\frac ab$ 和 $\frac cd$ 之间可以表示如下：

定义向量 $\overrightarrow {e_1}=(b,a),\overrightarrow {e_2}=(d,c)$，同时将 $\overrightarrow{ij}$ 表示为 $a\overrightarrow{e_1}+b\overrightarrow{e_2}$（其中 $a$ 和 $b$ 为常数），则从 $i$ 点到 $j$ 点能延伸一条折线当且仅当 $a>0,b>0$。证明显然。

同时令原点为 $O$，则 $\overrightarrow{ij}=\overrightarrow{Oj}-\overrightarrow{Oi}$。故而可以对于第 $i$ 个点，处理 $A_i,B_i$ 满足 $\overrightarrow{Oi}=A_i\overrightarrow{e_1}+B_i\overrightarrow{e_2}$。可得 $B_i=\frac{y_ib-x_ia}{cb-ad},A_i=\frac{x_ic-y_id}{cb-ad}$。（注意有解对应了 $\frac cd>\frac ab$，也就是 $cb>ad$，故而可以只需要维护 $y_ib-x_ia$ 和 $x_ic-y_id$ 之间的大小关系）这样可以令 $dp_i$ 为 $O$ 点到 $i$ 点的最长折线长度，则转移方程有 $dp_i=\max_{A_i-A_j>0\text{ and }B_i-B_j>0}(dp_j)+1$。直接用树状数组统计二维偏序即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=100010;
int n,i,a,b,c,d,x,y; 
struct Vals{
	long long val;
	int idx;
	inline bool operator <(const Vals &p)const{return val<p.val;}
}A[maxn],B[maxn];
struct node{
	int ra,rb;
	inline bool operator <(const node &p)const{
		if(ra!=p.ra) return ra<p.ra;
		return rb<p.rb; 
	}
}N[maxn];
int C[maxn],dp[maxn];
inline void Add(int p,const int &v){
	for(;p<maxn;p+=(p&-p)) C[p]=max(C[p],v);
}
inline int Que(int p){
	int ret=0;
	for(;p;p&=(p-1)) ret=max(ret,C[p]);
	return ret;
}
long long lst;
int main(){
	scanf("%d",&n);
	scanf("%d/%d%d/%d",&a,&b,&c,&d);
	for(i=1;i<=n;++i){
		scanf("%d%d",&x,&y);
		A[i].idx=B[i].idx=i;
		B[i].val=(1LL*y*b)-(1LL*x*a);
		A[i].val=(1LL*x*c)-(1LL*y*d);
	}
	sort(A+1,A+n+1);sort(B+1,B+n+1);
	for(i=1;A[i].val<=0;++i);
	x=1;lst=A[i].val; 
	for(;i<=n;++i){
		while(A[i].val==lst) N[A[i++].idx].ra=x;
		lst=A[i].val;N[A[i].idx].ra=++x;
	}
	for(i=1;B[i].val<=0;++i);
	x=1;lst=B[i].val;
	for(;i<=n;++i){
		while(B[i].val==lst) N[B[i++].idx].rb=x;
		lst=B[i].val;N[B[i].idx].rb=++x;
	}
	sort(N+1,N+n+1);x=1;a=0;
	for(i=1;!N[i].ra;++i);
	for(;i<=n;++i){
		if(N[i].ra!=N[x].ra) for(;x<i;++x) if(N[x].rb) Add(N[x].rb,dp[x]);
		if(N[i].rb) a=max(a,dp[i]=Que(N[i].rb-1)+1);
	}
	printf("%d",a);
	return 0;
}
```

---

## 作者：Kazdale (赞：1)

做法：分式运算 + BIT + DP

- ## 分析
	我们设直线 $x_ix_j$ 的斜率在 $\frac{a}{b} \sim \frac{c}{d}$ 之间，假设 $x_i$ 在 $x_j$ 的右上方，那么有 $\frac{a}{b} < \frac{y_i- y_j}{x_i- x_j} < \frac{c}{d}$。
    
    那么可以推出 $ax_i - by_i < ax_j - by_j$ 且 $dx_i - cy_i < dx_j - cy_j$。
    
    接下来我们可以直接储存 $ax-by$ 和 $dx-cy$ 然后求偏序就能计算出当前位置向原点方向连边时所有合法的点。
    
    因为求最多点数，于是考虑 DP，设 $f_i$ 表示最后一个点为点 $i$ 时构成的合法折线的最多点数，显然最后的答案为 $\max_{i=0}^{n} f_i$。（设 $0$ 号点为原点，后文中的 $0$ 号点与此处同一定义）
    
    那么考虑转移，显然是选能转移的点中 $f_i$ 最大的点转移，则状态转移方程为 $f_i = \max_{j=0}^n [ax_i - by_i < ax_j - by_j] \times [dx_i - cy_i < dx_j - cy_j] \times f_j + 1$。
    
    接下来考虑初状态，因为第一个点只能是原点且原点不算入答案，所以在设初始值时令 $f[0]=0$，$f[1\sim n]=-\operatorname{INF}$。
    
    转移时需要保证所有满足 $ax-by$ 和 $dx-cy$ 均分别大于当前点的 $ax-by$ 和 $dx-cy$ 的点都已经被计算过，于是在转移前我们先对 $dx-cy$ 降序排序，然后再对 $ax-by$ 降序排序，这样就可以保证所有符合条件的点均在计算该点前就已经被转移完毕了。
    
    如何求所有满足条件的点的 $f_i$ 的最大值？考虑权值 BIT，因为我们已经排过序了，所以仅有 $dx-cy$ 大于当前点且 $ax-by$ 小于等于当前点时这一种非法情况会排在当前点前面，除此以外当前点前面都是合法的点，于是用权值 BIT 计算 $ax-by$ 大于当前点的点的 $f_i$ 值中的最大值即可。
    
   离散化后的总时间复杂度为 $\mathcal{O(n \log n)}$，可以通过本题。
   
- ## 代码

```
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define int long long 
using namespace std;
constexpr int MAXN(1000007);
constexpr int INF(0x3f3f3f3f3f3f3f3f);
vector <int> e[MAXN];
int tr[MAXN], x[MAXN], y[MAXN], w[MAXN], f[MAXN];
int n, a, b, c, d, cnt, ans;
struct SUF_BIT{
	inline int lowbit(int x) { return x & -x; }
	inline void update(int x, int val) { for (int i(x); i; i -= lowbit(i))  tr[i] = max(tr[i], val); }
	inline int query(int x) { int res(-INF);  for (int i(x); i <= cnt; i += lowbit(i))  res = max(res, tr[i]);  return res; }
}Luka;
inline void read(int &temp) { cin >> temp; }
inline bool cmp(int u, int v) { return x[u] < x[v]; }
signed main() {
	scanf("%lld", &n), scanf("%lld/%lld", &a, &b), scanf("%lld/%lld", &c, &d);
	for (int i(1), u, v; i <= n; ++i)  scanf("%lld", &u), scanf("%lld", &v), x[i] = a * u - b * v, y[i] = d * v - c * u;
	for (int i(0); i <= n; ++i)  w[++cnt] = x[i], w[++cnt] = y[i];
	sort(w + 1, w + cnt + 1), cnt = unique(w + 1, w + cnt + 1) - w - 1;
	for (int i(0); i <= n; ++i)  x[i] = lower_bound(w + 1, w + cnt + 1, x[i]) - w, y[i] = lower_bound(w + 1, w + cnt + 1, y[i]) - w, e[y[i]].push_back(i);
	for (int i(1); i <= cnt; ++i)  sort(e[i].begin(), e[i].end(), cmp);
	memset(tr, -0x3f, sizeof(tr));
	for (int i(cnt); i; --i) {
		for (int j(0); j < (int)e[i].size(); ++j) {
			int id = e[i][j];
			f[id] = Luka.query(x[id] + 1) + 1;
			if (!id)  f[id] = 0;
			Luka.update(x[id], f[id]);
			ans = max(ans, f[id]);
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：红黑树 (赞：0)

[可能更好的阅读体验](https://rbtr.ee/CF249D)

## [题意](https://codeforces.com/contest/249/problem/D)
给出平面直角坐标系上的 $n$ 个点。

求最多有多少个点依次连成的折线上的线段的斜率都在给定的范围内。

$1 \leq n \leq 10^5$

## 题解
首先来看一看什么情况下一个点能接在另一个点后面。

以给定的两个斜率代表的向量为基（即把 $x$ 轴和 $y$ 轴换成这两个项链所构成的坐标系），如果一个点的横坐标和纵坐标都大于另一个点，那么他们就可以接一起了。

这样的话就简单了，按照横坐标排序后就是求个最长上升子序列长度了。

有的人想的比较复杂，认为还要把离原点的距离也加入偏序，于是需要用 CDQ 分治优化 1D/1D DP，其实是不需要的。

## 代码
```cpp
// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  tp n, a, b, c, d; bin >> n >> a >> b >> c >> d;
  vector<PTT> p;
  while (n--) {
    tp x, y; bin >> x >> y;
    tp u = y * b - x * a;
    tp v = x * c - y * d;
    if (u > 0 && v > 0) p.emplace_back(u, -v);
  }
  stable_sort(FULL(p));
  vector<tp> s;
  for (tp i = 0; i < p.size(); ++i) {
    if (s.empty() || -p[i].second > s.back()) s.push_back(-p[i].second);
    else *lower_bound(FULL(s), -p[i].second) = -p[i].second;
  }
  bin << s.size() << '\n';
  return 0;
}

void MIST() {
}

// :\ *//
```

---

