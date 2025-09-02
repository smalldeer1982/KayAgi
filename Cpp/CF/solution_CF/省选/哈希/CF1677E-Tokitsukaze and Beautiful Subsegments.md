# Tokitsukaze and Beautiful Subsegments

## 题目描述

Tokitsukaze has a permutation $ p $ of length $ n $ .

Let's call a segment $ [l,r] $ beautiful if there exist $ i $ and $ j $ satisfying $ p_i \cdot p_j = \max\{p_l, p_{l+1}, \ldots, p_r \} $ , where $ l \leq i < j \leq r $ .

Now Tokitsukaze has $ q $ queries, in the $ i $ -th query she wants to know how many beautiful subsegments $ [x,y] $ there are in the segment $ [l_i,r_i] $ (i. e. $ l_i \leq x \leq y \leq r_i $ ).

## 说明/提示

In the first example, for the first query, there are $ 2 $ beautiful subsegments — $ [1,2] $ and $ [1,3] $ .

## 样例 #1

### 输入

```
8 3
1 3 5 2 4 7 6 8
1 3
1 1
1 8```

### 输出

```
2
0
10```

## 样例 #2

### 输入

```
10 10
6 1 3 2 5 8 4 10 7 9
1 8
1 10
1 2
1 4
2 4
5 8
4 10
4 7
8 10
5 9```

### 输出

```
17
25
1
5
2
0
4
1
0
0```

# 题解

## 作者：Fido_Puppy (赞：9)

[或许更好的阅读体验。](https://www.cnblogs.com/FidoPuppy/p/16307476.html)

$$\texttt{Foreword}$$

感谢 [$\mathcal{AutumnKite}$](https://www.luogu.com.cn/user/20561) 神犇提供的思路！

$$\texttt{Description}$$

[CF1677E Tokitsukaze and Beautiful Subsegments](https://www.luogu.com.cn/problem/CF1677E)

$$\texttt{Solution}$$

一个区间 $l \sim r$ 是美丽的，当且仅当存在两个数 $i, j$ 满足 $l \leq i < j \leq r$ 且 $a_i \cdot a_j = \max\limits^{k\leq r}_{k=l}a_k$。

看到 $\max\limits^{k\leq r}_{k=l}a_k$，我们就能想到用一个单调栈来解决。

我们可以先用单调栈预处理处对于每一个 $a_i$，它后面第一个比它大的数的下标 $R_i$ 和它前面第一个比它大的数的下标 $L_i$。

所以对于所有的区间 $l \sim r$ 满足 $L_i < l \leq r < R_i$，都有 $\max\limits^{k\leq r}_{k=l}a_k=a_i$。

于是我们就能够直接得到一个区间的最大值。

接着我们先考虑如何求解整个数列的美丽区间个数。

可以先对于每个 $a_i$ 暴力枚举，枚举区间的右端点 $r\ (i\leq r < R_i)$，确定左端点的范围，也可以枚举区间左端点 $l \ (L_i < l \leq i)$，确定右端点的范围。

我们这里以枚举右端点为例。

假设我们现在有一个区间：

$1\ \ 3\ \ 4\ \ 2\ \ 12\ \ 8\ \ 6$。

枚举到的 $a_i = 12$。

我们设区间左端点的范围为 $L \sim R$，明显 $L = L_i + 1$。

首先，我们初始化 $R = L_i$，也就是没有合法的区间。

接着，我们枚举 $a_i$ 的因数，设两个因数分别为 $x, y\ \ (x \ne y)$，数的位置为 $pos_x$ 和 $pos_y$（$pos$ 数组可以预处理，因为这是一个 $1 \sim n$ 的排列），判断是否 $L_i < pos_x, pos_y \leq i$，即在范围内，然后更新 $R = \min(pos_x, pos_y)$。

感性理解一下，例如在这里，我们可以枚举到 $12$ 的因数有 $3$ 和 $4$。

所以更新 $R = \min(pos_3, pos_4) = 2$，即只需左端点在 $1 \sim 2$ 中，包含着 $3$ 和 $4$，那么就有 $3 \times 4 = 12$，即这个区间是美丽的。

这样总时间复杂度为 $\mathcal{O(\Sigma^{i\leq n}_{i=1}\sqrt a_i)}$。

然后我们可以对于每一个枚举到的右端点，算出与它的乘积为 $a_i$ 的那个数的位置，判断是否在范围内，如果在，则更新 $R = \max(R, pos)$，这里要注意，可能 $pos > i$，这是需要在更新 $R = \min(R, i)$。

例如枚举到 $6$ 时，算出 $\dfrac{12}{6}=2, pos_2 = 4$，所以更新 $R = 4$，即右端点在 $6$ 之后只需要左端点中包含 $2$，就有 $2 \times 6 = 12$，即这个区间是美丽的。

对于每一个这样的三元组 $(L,R,r)$ 表示右端点为 $r$ 时左端点为 $L \sim R$ 时区间时美丽的，我们都可以用一个 vector 把它记录下来。

具体地，我们可以这样操作：

```cpp
vector < pair <int, int> > vec[MAXN];

// Insert operation.

vec[r].push_back(make_pair(L, R));
```
如果枚举左端点，三元组 $(L, R, l)$ 表示左端点为 $l$ 时右端点为 $L \sim R$ 时区间是美丽的，同理。

如果全局查询，我们只需要把每一个三元组的 $R - L + 1$ 给加起来就是答案。

可是现在是区间查询。

所以我们可以参考扫描线的思想。

首先把询问离线，按照右端点从小到大排序，用 $i$ 指针从 $1\ sim n$ 枚举，每次把右端点为 $i$ 的所有三元组给加到一个线段树中，就是把区间 $L \sim R$ 加上 $1$，然后遇到对应的询问 $(l, r)$ 时，查询线段树上 $l \sim r$ 的和就行了。

如果时枚举左端点，就按照左端点从大到小排序，用 $i$ 指针逆序扫，其余同理。

这样我们可以完成区间查询了，但是时间复杂度却是可怜的 $\mathcal{O(n^2)}$。

我们会发现对于一个数 $a_i$，枚举左端点和右端点都可以，根据正常人的思维，哪一个短就枚举哪一个。

结果我们发现这过了。

其实这个是启发式分裂的思想，这样能够保证枚举的数量不超过 $n \log n$ 个。

所以加上线段树查询的时间复杂度，总时间复杂度为 $\mathcal{O(n \log^2 n + q \log n + \Sigma^{i\le n}_{i = 1}\sqrt a_i)}$。

$$\texttt{Code}$$

最后不要忘记开 long long。

并且这道题有一些神奇，不用快读快输过不去。

```cpp
// Thanks for solution given from AutumnKite! Orz %%%
#include <bits/stdc++.h>

using namespace std;

#define int long long

static char buf[100010], *p1 = buf, *p2 = buf;
#define gc p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100010, stdin), p1 == p2)? EOF: *p1++

inline int read() {
	int res = 0, w = 0; char c = gc;
	while (!isdigit(c)) w |= c == '-', c = gc;
	while (isdigit(c)) res = (res << 1) + (res << 3) + (c ^ 48), c = gc;
	return (w? -res : res);
}

inline void write(int x) {
	static int sta[50], top = 0;
	if (x < 0) putchar('-'), x = -x;
	do {
		sta[ top++ ] = x % 10, x /= 10;
	} while (x);
	while (top) putchar(sta[ --top ] + 48);
	putchar('\n');
}

#define ls (p << 1)
#define rs (p << 1 | 1)

const int MAXN = 2e5 + 10;

int n, Q, a[MAXN], pos[MAXN], L[MAXN], R[MAXN];
int sta[MAXN], top, Qnum;

vector < pair <int, int> > vec1[MAXN], vec2[MAXN];

struct Query {
	int l, r, id;
}q[ (int)(1e6 + 10) ];

int Ans[ (int)(1e6 + 10) ];

inline bool Comp1(Query a, Query b) {
	return a.r < b.r;
}

inline bool Comp2(Query a, Query b) {
	return a.l > b.l;
}

struct Node {
	int len, data, add;
	Node() = default;
	Node(const int Len, const int Data, const int Add) : len(Len), data(Data), add(Add) {}
}t[ MAXN << 2 ];

inline void build(int p, int l, int r) {
	t[p] = Node(r - l + 1, 0, 0);
	if (l == r) return ;
	int mid = l + r >> 1;
	build(ls, l, mid); build(rs, mid + 1, r);
}

inline void pushdown(int p) {
	t[ls] = Node(t[ls].len, t[ls].data + t[ls].len * t[p].add, t[p].add + t[ls].add);
	t[rs] = Node(t[rs].len, t[rs].data + t[rs].len * t[p].add, t[p].add + t[rs].add);
	t[p].add = 0;
}

inline void update(int p, int l, int r, int x, int y, int k) {
	if (l >= x && r <= y) {
		t[p] = Node(t[p].len, t[p].data + t[p].len * k, t[p].add + k);
		return ;
	}
	pushdown(p);
	int mid = l + r >> 1;
	if (x <= mid) update(ls, l, mid, x, y, k);
	if (mid < y) update(rs, mid + 1, r, x, y, k);
	t[p].data = t[ls].data + t[rs].data;
}

inline int query(int p, int l, int r, int x, int y) {
	if (l >= x && r <= y) return t[p].data;
	int ans = 0, mid = l + r >> 1;
	pushdown(p);
	if (x <= mid) ans += query(ls, l, mid, x, y);
	if (mid < y) ans += query(rs, mid + 1, r, x, y);
	return ans;
}

signed main() {
	n = read(); Q = read();
	for (int i = 1; i <= n; i++) {
		a[i] = read();
		pos[ a[i] ] = i;
	}
	
	top = 0;
	for (int i = 1; i <= n; i++) {
		while (top > 0 && a[ sta[top] ] < a[i]) top--;
		L[i] = sta[top];
		sta[ ++top ] = i;
	}
	
	top = 0;
	sta[0] = n + 1;
	for (int i = n; i >= 1; i--) {
		while (top > 0 && a[ sta[top] ] < a[i]) top--;
		R[i] = sta[top];
		sta[ ++top ] = i;
	}
	
	for (int i = 1; i <= Q; i++) {
		q[i].l = read(); q[i].r = read();
		q[i].id = i;
	}
	
	for (int i = 1; i <= n; i++) {
		int left, right;
		if (R[i] - i <= i - L[i]) {
			right = L[i];
			for (int j = 1; j * j <= a[i]; j++) {
				if (a[i] % j != 0) continue;
				int fx = pos[j], fy = pos[ a[i] / j ];
				if (fx == fy) continue;
				if (fx > fy) swap(fx, fy);
				if (fx > L[i] && fy <= i)
					right = max(right, fx);
			}
			for (int j = i; j < R[i]; j++) {
				if (a[i] % a[j] == 0) {
					int num = a[i] / a[j];
					if (pos[num] == j) continue;
					if (pos[num] > L[i] && pos[num] < j) {
						right = max(right, pos[num]);
						right = min(right, i); 
					}
				}
				if (L[i] < right)
					vec1[j].push_back(make_pair(L[i] + 1, right));
			}
		}
		else {
			left = R[i];
			for (int j = 1; j * j <= a[i]; j++) {
				if (a[i] % j != 0) continue;
				int fx = pos[j], fy = pos[ a[i] / j ];
				if (fx == fy) continue;
				if (fx > fy) swap(fx, fy);
				if (fy < R[i] && fx >= i)
					left = min(left, fy);
			}
			for (int j = i; j > L[i]; j--) {
				if (a[i] % a[j] == 0) {
					int num = a[i] / a[j];
					if (pos[num] == j) continue;
					if (pos[num] > j && pos[num] < R[i]) {
						left = min(left, pos[num]);
						left = max(left, i);
					}
				}
				if (left < R[i])
					vec2[j].push_back(make_pair(left, R[i] - 1));
			}
		}
	}

	sort(q + 1, q + Q + 1, Comp1);
	build(1, 1, n);
	
	Qnum = 1;
	for (int i = 1; i <= n; i++) {
		for (auto v : vec1[i]) {
			update(1, 1, n, v.first, v.second, 1);
		}
		for (; q[Qnum].r == i && Qnum <= Q; Qnum++) {
			Ans[ q[Qnum].id ] += query(1, 1, n, q[Qnum].l, q[Qnum].r);
		}
	}
	
	sort(q + 1, q + Q + 1, Comp2);
	build(1, 1, n);
	
	Qnum = 1;
	for (int i = n; i >= 1; i--) {
		for (auto v : vec2[i]) {
			update(1, 1, n, v.first, v.second, 1);
		}
		for (; q[Qnum].l == i && Qnum <= Q; Qnum++) {
			Ans[ q[Qnum].id ] += query(1, 1, n, q[Qnum].l, q[Qnum].r);
		}
	}
	
	for (int i = 1; i <= Q; i++) write(Ans[i]); 
	
	return 0;
}
```
$$\texttt{Thanks for watching!}$$

---

## 作者：xzzduang (赞：8)

[传送门](https://codeforces.com/problemset/problem/1677/E)

首先考虑怎么找到好的区间，我们可以用调和级数的时间枚举 $p_i$ 和 $p_j$，设 $t_i$ 表示 $p$ 中值为 $i$ 的下标，$L_i,R_i$ 分别表示下标 $i$ 往左的第一个比它值大的位置和往右的第一个的位置，则一个区间只要包含了 $p_i$ 和 $p_j$ 以及 $p_i\cdot p_j$，且左端点不达到 $L_{t_{p_i\cdot p_j}}$ ，右端点不达到 $R_{t_{p_i\cdot p_j}}$，那它就是一个美的区间。

显然，这个区间左端点范围形如 $(L_{t_{p_i\cdot p_j}},l]$，右端点形如 $[r,R_{t_{p_i\cdot p_j}})$。如果我们把左端点当作 $x$ 轴，右端点当作 $y$ 轴，现在的问题其实变成了矩形赋 1，矩形求和了。但是赋 1 不比加 1，难以做到一个 $\log$，需要一些转换。

发现对于不同的 $p_i\cdot p_j$ 的矩形不可能相交，因为区间最大值都不一样了，肯定不是同一个区间，那如果我们把同个 $p_i\cdot p_j$ 的所有矩形分割为若干个不同的矩形，那所有矩形就都没有交了，赋 1 操作就会变成加 1 操作。

发现对于同个 $p_i\cdot p_j$，每个矩形的左边界都是一样的 $L_{t_{p_i\cdot p_j}}$，上边界都是一样的 $R_{t_{p_i\cdot p_j}}$，所以这些矩形并起来应该长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/vkhpx9m0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

显然是一个可以拿单调栈维护的东西，所以我们已经把问题转化为了矩形加 1，矩形求和了。

考虑扫描线，从下往上扫，先把询问前缀和转化，当我们扫到第 $i$ 行，要加入一个矩形了，当以后扫到第 $j$ 行时，这个矩形在此列产生的贡献为 $j-i+1$，这其实是一个关于 $j$ 的一次函数，我们值需要分别维护两个系数的和几个，到时候就可以直接把 $j$ 带入求值了。删除一个矩形其实同理，其实就是减掉一个一次函数，跟之前的加入抵消成一个常函数。

```cpp
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<vector>
#include<algorithm>
#include<math.h>
#define N 200005
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define int long long
using namespace std;
inline int read(){
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch==45),ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
int n,q,a[N],t[N],st[N],top,L[N],R[N],val[N],ans[1000005];
vector<pair<int,int> > mp[N],add[N],del[N];
vector<pair<pair<int,int>,int> > que[N]; 
struct segmentTree{
	int l,r,sum,cnt,as,ac;
}d[4*N];
void build(int k,int l,int r){
	d[k].l=l,d[k].r=r;
	if(l==r) return;
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
}
inline void pushdown(int k){
	if(d[k].as){
		d[ls].sum+=(d[ls].r-d[ls].l+1)*d[k].as;
		d[rs].sum+=(d[rs].r-d[rs].l+1)*d[k].as;
		d[ls].as+=d[k].as,d[rs].as+=d[k].as;
		d[k].as=0;
	}
	if(d[k].ac){
		d[ls].cnt+=(d[ls].r-d[ls].l+1)*d[k].ac;
		d[rs].cnt+=(d[rs].r-d[rs].l+1)*d[k].ac;
		d[ls].ac+=d[k].ac,d[rs].ac+=d[k].ac;
		d[k].ac=0;
	}
}
void update(int k,int x,int y,int v1,int v2){
	if(x<=d[k].l && d[k].r<=y){
		d[k].cnt+=(d[k].r-d[k].l+1)*v1,d[k].ac+=v1;
		d[k].sum+=(d[k].r-d[k].l+1)*v2,d[k].as+=v2;
		return;
	}
	pushdown(k);
	int mid=d[k].l+d[k].r>>1;
	if(x<=mid) update(ls,x,y,v1,v2);
	if(mid+1<=y) update(rs,x,y,v1,v2);
	d[k].sum=d[ls].sum+d[rs].sum;
	d[k].cnt=d[ls].cnt+d[rs].cnt;
}
int query(int k,int x,int y,int v){
	if(x<=d[k].l && d[k].r<=y) return d[k].cnt*v+d[k].sum;
	pushdown(k);
	int mid=d[k].l+d[k].r>>1,res=0;
	if(x<=mid) res+=query(ls,x,y,v);
	if(mid+1<=y) res+=query(rs,x,y,v);
	return res;
}
signed main(){
	n=read(),q=read();
	for(int i=1;i<=n;++i) a[i]=read(),t[a[i]]=i;
	a[0]=a[n+1]=1e9;st[top=1]=0;
	for(int i=1;i<=n;++i){
		while(top && a[i]>a[st[top]]) top--;
		L[i]=st[top]+1,st[++top]=i;
	}
	st[top=1]=n+1;
	for(int i=n;i>=1;--i){
		while(top && a[i]>a[st[top]]) top--;
		R[i]=st[top]-1,st[++top]=i;
	}
	for(int i=1;i<=n;++i){
		for(int j=1;i*j<=n;++j){
			if(t[i]>=t[j]) continue;
			if(t[i]<L[t[i*j]] || t[j]>R[t[i*j]]) continue;
			mp[t[i*j]].push_back({min(t[i],t[i*j]),max(t[j],t[i*j])});
		}
	}
	for(int i=1;i<=n;++i){
		if(mp[i].empty()) continue;
		sort(mp[i].begin(),mp[i].end());
		st[top=1]=L[i]-1;
		for(auto v:mp[i]){
			while(top>1 && v.se<=val[top-1]) top--;
			st[++top]=v.fi;val[top-1]=v.se;
		}
		for(int j=1;j<top;++j){
			add[val[j]].push_back({st[j]+1,st[j+1]});
			del[R[i]].push_back({st[j]+1,st[j+1]});
		}
	}
	for(int i=1;i<=q;++i){
		int ll=read(),rr=read();
		que[rr].push_back({{ll,rr},i});
		que[ll-1].push_back({{ll,rr},-i});
	}
	build(1,1,n);
	for(int i=1;i<=n;++i){
		for(auto v:add[i]) update(1,v.fi,v.se,1,-i+1);
		for(auto v:del[i]) update(1,v.fi,v.se,-1,i);
		for(auto v:que[i])
			ans[abs(v.se)]+=(v.se>0?1:-1)*query(1,v.fi.fi,v.fi.se,i);
	}
	for(int i=1;i<=q;++i) printf("%lld\n",ans[i]);
	return 0;
}
```



---

## 作者：Renshey (赞：7)

#### 题意

给定排列 $\{p_n\}$，定义一个区间 $[l,r]$ 是好的，当且仅当存在 $l \le i < j \le r$，满足 $p_i\times p_j = \max\{p_l, p_{l + 1}, \dots, p_r\}$，$q$ 次询问 $[l,r]$，求 $[l,r]$ 有多少个子区间是好的。

#### 数据范围

$n \le 2 \times 10^5, q \le 10^6$

#### 题解

这是一个经典的区间子区间问题，考虑经典方法。

首先枚举 $\max$ 算贡献，设 $p_0 = p_{n + 1} = n + 1$，记 $pre_i = \max\{j \mid p_j > p_i\},nxt_i = \min\{j \mid p_j > p_i\}$。若 $p_i$ 能成为最大值，则必定在区间 $[pre_i + 1, nxt_i - 1]$ 内。考虑所有的二元组 $(x,y)$ 使得 $p_x \times p_y = p_i$。首先二元组的总数显然是 $O(n \log n)$ 级别的（实际上不超过 $2 \times 10^6$）。对于每个二元组 $(x,y)$，显然会使 $l \in (pre_i, x], r \in [y, nxt_i)$ 的所有区间产生贡献。放到二维平面上相当于矩形覆盖，而查询相当于矩形求和。

矩形覆盖是难以处理的，考虑进一步分析矩形之间的关系。注意到两个矩形有交则产生它们的 $i$ 一定是同一个，因此只需要对每个 $i$ 做好容斥即可。暴力扫描线效率是对的，但显然有更好的做法。对于 $x_1\le x_2,y_1 \ge y_2$，$(x_2,y_2)$ 能完全包含 $(x_1,y_1)$。因此实际上有效的若干二元组 $(x_1,y_1),(x_2,y_2),\dots,(x_m,y_m)$，假设 $x_1 < x_2 < \dots < x_m$，则一定有 $y_1 < y_2 < \dots < y_m$。这些二元组不难通过排序 + 栈求出，然后满足上述偏序关系的矩形覆盖可以直接用容斥转化为一次矩形 $+1$ 与一次矩形 $-1$。

至此问题化为矩形加、矩形求和，直接扫描线+树状数组即可。

时间复杂度 $O(n\log^2 n + q \log n)$，空间复杂度 $O(n \log n + q)$。

#### 代码

```cpp
#include <bits/stdc++.h>
#define Getchar() p1 == p2 and (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++
char buf[1 << 21], *p1, *p2;
inline int read (void)
{
	int x = 0; char c = Getchar(); bool f = (c != '-');
	while (c < '0' or c > '9') c = Getchar(), f &= c != '-';
	while (c >= '0' and c <= '9') x = x * 10 + c - 48, c = Getchar();
	return f ? x : -x;
}
const int maxn = 200000 + 10;
int n, m, p[maxn], q[maxn], pre[maxn], nxt[maxn], st[maxn];
std::vector<std::pair<int, int>> D[maxn], Q[maxn];
std::vector<std::array<int, 3>> A[maxn]; long long ans[1 << 20];
struct Tree
{
	long long t1[maxn], t2[maxn];
	inline void add1 (int x, long long w) {for (int i = x; i <= n; i += i & (-i)) t1[i] += w;}
	inline void add2 (int x, long long w) {for (int i = x; i <= n; i += i & (-i)) t2[i] += w;}
	inline long long ask1 (int x) {long long res = 0; for (int i = x; i; i -= i & (-i)) res += t1[i]; return res;}
	inline long long ask2 (int x) {long long res = 0; for (int i = x; i; i -= i & (-i)) res += t2[i]; return res;}
	inline void add (int l, int r, int w) {add1(l, w); add1(r + 1, -w); add2(l, 1LL * l * w); add2(r + 1, -1LL * (r + 1) * w);}
	inline long long ask (int l, int r) {return (r + 1) * ask1(r) - l * ask1(l - 1) - ask2(r) + ask2(l - 1);}
} T1, T2;
signed main ()
{
	n = read(); m = read();
	for (int i = 1; i <= n; i++) q[p[i] = read()] = i;
	for (int i = 1, tp = 0; i <= n; i++)
	{
		while (tp and p[st[tp]] < p[i]) tp--;
		pre[i] = st[tp]; st[++tp] = i;
	}
	st[0] = n + 1;
	for (int i = n, tp = 0; i >= 1; i--)
	{
		while (tp and p[st[tp]] < p[i]) tp--;
		nxt[i] = st[tp]; st[++tp] = i;
	}
	for (int i = 1; i * (i + 1) <= n; i++) for (int j = i + 1; i * j <= n; j++)
		if (pre[q[i * j]] < std::min(q[i], q[j]) and std::max(q[i], q[j]) < nxt[q[i * j]])
			D[q[i * j]].push_back({std::min({q[i], q[j], q[i * j]}), std::max({q[i], q[j], q[i * j]})});
	for (int i = 1; i <= n; i++)
	{
		std::vector<std::pair<int, int>> W;
		W.push_back({pre[i], i - 1});
		std::sort(D[i].begin(), D[i].end(), [&](const std::pair<int, int> &A, const std::pair<int, int> &B){
			return A.first == B.first ? A.second > B.second : A.first < B.first;
		});
		for (auto [l, r]: D[i])
		{
			while (r <= W.back().second) W.pop_back();
			W.push_back({l, r});
		}
		for (int j = 1; j < (int)W.size(); j++)
			A[W[j].second].push_back({W[j - 1].first + 1, W[j].first, 1}), A[nxt[i]].push_back({W[j - 1].first + 1, W[j].first, -1});
	}
	for (int i = 1, l, r; i <= m; i++) l = read(), r = read(), Q[r].push_back({l, i});
	for (int i = 1; i <= n; i++)
	{
		for (auto [l, r, w]: A[i]) T1.add(l, r, w * (i - 1)), T2.add(l, r, w);
		for (auto [p, id]: Q[i]) ans[id] = i * T2.ask(p, i) - T1.ask(p, i);
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：huangzirui (赞：5)

题意：

给定排列，记子区间 $[L,R]$ 是好的，则存在 $i,j\in[L,R]$ 满足 $a_ia_j=\max\limits_{k=L}^R(a_k)$。

$q$ 次询问区间有多少子区间是好的，

$n \leqslant 2\times 10^5,q\leqslant 10^6$

---

显然，我们能抽出 $n\ln n$ 个三元组 $(i,j,k)$，满足只要区间 $[L,R]$ 包含它，且最大值为 $a_k$，那么就有 $1$ 的贡献。

考虑放在二维平面上，考虑平面的下三角部分。那么每次相当于矩形赋 $1$，多次查询矩形和。

这个不太好维护，我们再找一下性质。

首先对于不同的 $k$，对应的矩形显然不会相交。

否则容易发现，这些矩形的右边界和下边界都是一致的。

具体来说，因为每个三元组都是形如左端点在范围 $[A,B]$ 之间，右端点在 $[C,D]$，而 $A,D$ 只用于限制最大值为 $a_k$，因此这些矩形的 $A,D$ 都是固定的。

于是我们对于相同的 $k$ 可以容易的拆成若干个互不相干的矩形，然后扫描线就好了。


---

## 作者：joke3579 (赞：4)

看到 $\max$ 想到单调栈。  
找到任意元素左右第一个大于它的位置，对于 $i$ 记作 $l_i,r_i$。

然后考虑一个元素对答案的贡献。令 $s_i$ 为 $i$ 元素所在位置，并记 $[l,r]$ 为美丽的区间指代了 $l$ 与 $r$ 配对。  
仍然是枚举 $a_i$ 的因子，设两个因子为 $p,q$。如果 $l_i < s_p \le i \le s_q < r_i$，则任意 $s_q\le r < r_i$ 的位置都可以作为右端点和 $l_i < l \le s_p$ 的左端点配对。如果 $s_p,s_q \le i$ 或 $i\le s_p,s_q$ 基本同理。我们只需要得到左右两侧可能可行的范围即可，随后枚举一侧，去另一侧找可以与当前枚举位置配对的位置。容易知道这些位置构成了一个区间。

讨论对 $a_i$ 对应区间的左侧的枚举。假设当前枚举到了位于 $l$ 位置的元素 $p$，则我们需要在右侧找到 $\frac {a_i} p$ 的位置 $r$，若存在则对于 $l$ 位置，任意 $[r,r_i-1]$ 的位置都可以对答案产生贡献。
随后我们从右到左扫描线。扫描时在所有能和当前元素配对的范围内分别加 $1$ ，表示以当前点或更左侧点为左端点的话取该范围内点为右端点是可行的。  
维护即可。  

但是我们发现这样产生的区间是 $O(n^2)$ 的。   
考虑启发式。每次扫描更小的一侧，这样产生的区间个数是 $O(n\log n)$ 的。从左右两侧分别扫描线即可统计完贡献。

时间复杂度 $O(n\log^2 n)$。



```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
template<typename T> void get(T & x) {
	x = 0; char ch = getchar(); bool f = false; while (ch < '0' or ch > '9') f = f or ch == '-', ch = getchar();
	while ('0' <= ch and ch <= '9') x = (x << 1) + (x << 3) + ch - '0', ch = getchar(); f && (x = -x); 
} template <typename T, typename ... Args> void get(T & a, Args & ... b) { get(a); get(b...); }
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
#define pre(i,s,t) for (register int i = (s), i##_ = (t) - 1; i > i##_; -- i)
const int N = 1e6 + 10; typedef long long ll;
int n, q, l, r, a[N], lp[N], rp[N], pos[N], ans[N];
int stk[N], top;
vector <pair<int,int> > d1[N], d2[N];
struct queries {
    int l, r, id;
} qy[N];

class SegmentCitrus {

  private : 

    #define ls (p << 1)
    #define rs (p << 1 | 1)
    #define sum(p) seg[p].sum
    #define siz(p) seg[p].size
    #define lzy(p) seg[p].lazy
    struct node {
        int size, lazy, sum;
    } seg[N << 2];

    void ps_d(int p) {
        if (lzy(p) == 0) return;
        sum(ls) += siz(ls) * lzy(p), sum(rs) += siz(rs) * lzy(p);
        lzy(ls) += lzy(p), lzy(rs) += lzy(p);
        lzy(p) = 0; return ;
    }

    void ps_p(int p) { sum(p) = sum(ls) + sum(rs); }

    void build(int p, int l, int r) {
        siz(p) = r - l + 1, lzy(p) = sum(p) = 0;
        if (l == r) return;
        int mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid+1, r);
    }

    void add(int p, int l, int r, int L, int R, int v) {
        if (L <= l and r <= R) {
            sum(p) += v * siz(p);
            lzy(p) += v;
            return;
        } int mid = l + r >> 1; ps_d(p);
        if (L <= mid) add(ls, l, mid, L, R, v);
        if (mid < R) add(rs, mid+1, r, L, R, v);
        ps_p(p);
    }

    int qry(int p, int l, int r, int L, int R) {
        if (L <= l and r <= R) return sum(p);
        int mid = l + r >> 1, ret = 0; ps_d(p);
        if (L <= mid) ret += qry(ls, l, mid, L, R);
        if (mid < R) ret += qry(rs, mid+1, r, L, R);
        return ret;
    }
    
    #undef ls
    #undef rs
    #undef sum
    #undef siz
    #undef lzy

  public : 

    void clear() { build(1, 1, n); }
    void update(int l, int r, int v) { add(1, 1, n, l, r, v); }
    int query(int l, int r) { return qry(1, 1, n, l, r); }

} Tr;

signed main() {
    get(n, q); rep(i,1,n) get(a[i]), pos[a[i]] = i; a[0] = a[n + 1] = n + 1;
    rep(i,1,q) get(qy[i].l, qy[i].r), qy[i].id = i;

    stk[top = 1] = 0;
    rep(i,1,n) {
        while (top and a[stk[top]] < a[i]) -- top;
        lp[i] = stk[top]; stk[++top] = i;
    } 
    stk[top = 1] = n + 1;
    pre(i,n,1) {
        while (top and a[stk[top]] < a[i]) -- top;
        rp[i] = stk[top]; stk[++top] = i;
    }

	rep(i,1,n) {
		if (rp[i] - i <= i - lp[i]) {
			r = lp[i];
			for (int j = 1; j * j <= a[i]; ++j) {
				if (a[i] % j != 0) continue;
				int fx = pos[j], fy = pos[a[i] / j];
				if (fx == fy) continue;
				if (fx > fy) swap(fx, fy);
				if (fx > lp[i] && fy <= i) r = max(r, fx);
			}
			for (int j = i; j < rp[i]; ++j) {
				if (a[i] % a[j] == 0) {
					int nw = a[i] / a[j];
					if (pos[nw] == j) continue;
					if (pos[nw] > lp[i] && pos[nw] < j) {
						r = max(r, pos[nw]);
						r = min(r, i);
					}
				}
				if (lp[i] < r) d1[j].push_back({lp[i] + 1, r});
			}
		} else {
			l = rp[i];
			for (int j = 1; j * j <= a[i]; ++j) {
				if (a[i] % j != 0) continue;
				int fx = pos[j], fy = pos[a[i] / j];
				if (fx == fy) continue;
				if (fx > fy) swap(fx, fy);
				if (fy < rp[i] && fx >= i) l = min(l, fy);
			}
			for (int j = i; j > lp[i]; --j) {
				if (a[i] % a[j] == 0) {
					int nw = a[i] / a[j];
					if (pos[nw] == j) continue;
					if (pos[nw] > j && pos[nw] < rp[i]) {
						l = min(l, pos[nw]);
						l = max(l, i);
					}
				}
				if (l < rp[i]) d2[j].push_back({l, rp[i] - 1});
			}
		}
	}

    sort(qy+1, qy+1+q, [&](queries x, queries y){ return x.r < y.r; });
    Tr.clear();
    for (int i(1), p(1); i <= n; ++ i) {
        for (auto [l, r] : d1[i]) Tr.update(l, r, 1);
        while (p <= q and qy[p].r == i) ans[qy[p].id] += Tr.query(qy[p].l, qy[p].r), ++ p;
    }

    sort(qy+1, qy+1+q, [&](queries x, queries y){ return x.l > y.l; });
    Tr.clear();
    for (int i(n), p(1); i > 0; -- i) {
        for (auto [l, r] : d2[i]) Tr.update(l, r, 1);
        while (p <= q and qy[p].l == i) ans[qy[p].id] += Tr.query(qy[p].l, qy[p].r), ++ p;
    }

    rep(i,1,q) cout << ans[i] << '\n';
}
```

---

## 作者：Graphcity (赞：2)

考虑笛卡尔树，设 $[L_i,R_i]$ 是 $a_i$ 为最大值的区间。

我们对笛卡尔树每个结点 $i$ 分别考虑。枚举 $a_i$ 所有因数 $p$，令 $l=a^{-1}_p,r=a^{-1}_{\frac{a_i}{p}}$，假设 $l\le r$。那么一个区间如果包含 $[\min(l,r,i),\max(l,r,i)]$ 且在 $[L_i,R_i]$ 内，它就是好的。

然后把所有的 $[\min(l,r,i),\max(l,r,i)]$ 放到一起。如果一个区间包含另一个，那么那个更大的区间可以删掉（因为没用）。现在所有区间在左端点递增的同时右端点递增。我们就可以找到若干个四元组 $(l_1,r_1,l_2,r_2)$ 表示左端点在 $[l_1,r_1]$ 内且右端点在 $[l_2,r_2]$ 内时合法。

如果我们把这个四元组看成二维平面上 $x\in[l_1,r_1],y\in[l_2,r_2]$ 的矩形，那么可以发现所有矩形不相交。询问就是查询矩形 $(l,r,l,r)$ 跟这些矩形交的大小。

这个相当于历史版本和问题。用树状数组解决即可做到 $O(n\log^2 n+q\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,Maxk=1e6;

int n,m,a[Maxn+5],id[Maxn+5],mx[Maxn+5][20];
int L[Maxn+5],R[Maxn+5],ch[Maxn+5][2],rt; ll ans[Maxk+5];
vector<int> w[Maxn+5]; vector<pair<int,int>> qr[Maxn+5];
struct Data{int l,r,op;}; vector<Data> v[Maxn+5];

struct BIT
{
    ll t1[Maxn+5],t2[Maxn+5];
    #define lowbit(x) (x&-x)
    inline void Add(int x,ll y) {ll k=x*y; while(x<=n) t1[x]+=y,t2[x]+=k,x+=lowbit(x);}
    inline void Add(int l,int r,ll k) {Add(l,k),Add(r+1,-k);}
    inline ll Count1(int x) {ll res=0; while(x) res+=t1[x],x-=lowbit(x); return res;}
    inline ll Count2(int x) {ll res=0; while(x) res+=t2[x],x-=lowbit(x); return res;}
    inline ll Count(int x) {return 1ll*(x+1)*Count1(x)-Count2(x);}
    inline ll Count(int l,int r) {return Count(r)-Count(l-1);}
} T1,T2; int tim;

inline void Add(int l,int r,int k) {T1.Add(l,r,k),T2.Add(l,r,1ll*k*tim);}
inline ll Count(int l,int r) {return T1.Count(l,r)*tim-T2.Count(l,r);}
inline int GetID(int x,int y) {return a[x]>a[y]?x:y;}
inline int GetMx(int l,int r)
{int len=__lg(r-l+1); return GetID(mx[l][len],mx[r-(1<<len)+1][len]);}
inline int Build(int l,int r)
{
    if(l>r) return 0; int k=GetMx(l,r); L[k]=l,R[k]=r;
    ch[k][0]=Build(l,k-1),ch[k][1]=Build(k+1,r); return k;
}
inline void Add(int l1,int r1,int l2,int r2)
{v[l2].push_back(Data{l1,r1,1}),v[r2+1].push_back(Data{l1,r1,-1});}
inline void dfs(int x)
{
    int l=L[x],r=R[x]; vector<pair<int,int>> vx,vk;
    for(auto i:w[a[x]])
    {
        int p=id[i],q=id[a[x]/i];
        if(l<=p && p<q && q<=r) p=min(p,x),q=max(q,x),vx.emplace_back(p,q);
    } sort(vx.begin(),vx.end(),[&](auto a,auto b){
        return a.first>b.first || (a.first==b.first && a.second<b.second);});
    int mn=n+5; for(auto [p,q]:vx) if(q<mn) vk.emplace_back(p,q),mn=q;
    reverse(vk.begin(),vk.end());
    if(!vk.empty()) {int pr=L[x]; for(auto [p,q]:vk) Add(pr,p,q,R[x]),pr=p+1;}
    if(ch[x][0]) dfs(ch[x][0]); if(ch[x][1]) dfs(ch[x][1]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    For(i,1,n) cin>>a[i],id[a[i]]=i,mx[i][0]=i;
    For(i,1,n) for(int j=i;j<=n;j+=i) w[j].push_back(i);
    For(j,1,19) for(int i=1;i+(1<<j)-1<=n;++i)
        mx[i][j]=GetID(mx[i][j-1],mx[i+(1<<j-1)][j-1]);
    rt=Build(1,n),dfs(rt);
    For(i,1,m) {int l,r; cin>>l>>r; qr[r].emplace_back(l,i);}
    For(i,1,n)
    {
        for(auto [l,r,k]:v[i]) Add(l,r,k); ++tim;
        for(auto [l,id]:qr[i]) ans[id]=Count(l,n);
    }
    For(i,1,m) printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：2)

给你一个 $n$ 排列 $p$，称区间 $[l,r]$ 是好的，当且仅当存在 $l\le i\lt j\le r$ 使得 $p_i\times p_j=\max\{p_k \mid l\le k\le r\}$。

$q$ 次询问，每次给出 $l,r$，问有多少个 $i,j$ 满足 $l\le i\le j\le r$ 且区间 $[i,j]$ 是好的。

$n\le 2\times 10^5,q\le 10^6$。

------------

给我自个整出来了，真不错。

一眼离线下来扫描线，然后用到单调栈，这是常规的技巧。

思考一下维护的内容是什么。具体而言，设当前枚举右端点为 $r$，那么 $s_l$ 是 $[l,l],[l,l+1],...,[l,r]$ 里好的区间的数目。这样当 $r=R$ 时，直接求当前 $s_L+...+s_{R}$，就是询问 $[L,R]$ 的答案。

当我们 $r\leftarrow r+1$ 的时候，$s$ 发生了什么样的变化？这个问题不是很好直接研究。在单调栈上，可以把 $[1,r]$ 划分成若干个三元组 $[L,R,maxn]$，意为 $[L,r],[L+1,r],...,[R,r]$ 这些区间的最大值都为 $maxn$。当右端点加一的时候，栈顶的一些三元组将被删除，且压入一个新的三元组。

因此，我们实质研究的问题是，对于 $[L,R,maxn]$ 来说，哪些位置 $pos$ 是满足 $[pos,r]$ 是好的区间。我们要做的是把这些 $s_{pos}$ 加上一。

有一个关键的性质：若 $pos\gt L$ 且 $[pos,r]$ 是好的，显然 $[pos-1,r]$ 也是好的。换言之你只要求出一个最大的 $pos<=R$ 满足 $[pos,r]$ 是好的即可。然后把 $s_{L\sim pos}$ 全部加上一就行。

如何求 $pos$？显然，我们可以二分 $pos$，然后枚举 $maxn$ 的所有分解 $maxn=u\times v(u\lt v)$，并判断 $u$ 和 $v$ 的出现是否都在 $[pos,r]$ 内。但是这个复杂度过高了。事实上，直接枚举 $maxn$ 的所有分解 $maxn=u\times v(u\lt v)$，并且令 $pos=\max\{pos,\min\{occ_u,occ_v\}\}$ 即可。正确性不难说明。则一次求 $pos$ 的复杂度为 $\omega(maxn)$，其中 $\omega$ 表示因子个数。

此时还有一个易被忽视的问题。事实上，对于 $maxn\gt p_r$ 的四元组，虽然它不会被弹出和 $p_r$ 所在的四元组合并，但由于多了一个 $p_r$ 加入，实质上 $pos$ 可能会变大。为了处理这类改动，首先我们需要用一个数组，快速记录 $maxn=k$ 的四元组在栈中的位置，这样可以快速找到它并直接在栈里修改。然后暴力枚举 $p_r$ 的所有倍数 $P$，直接对 $maxn=P$ 的那个四元组花 $O(\omega(P))$ 的时间重新计算 $pos$ 即可。

到这里分析已经差不多了，我们想看看复杂度是否可行。不难发现实质上运算量是 $\sum_{i=1}^{n}\omega(n)^2$。我不知道这玩意是不是 $n\log^2 n$ 级别的（如果是一次显然是 $n\log n$ 级别），但是 $n=2\times 10^5$ 的时候算出来也不超过 $4\times 10^7$，而且注意到其实没什么常数，完全可以接受。

到这里真的就结束了吗？

一次 $r$ 拓展结束以后，那些栈深处的，没被涉及的，同时也没有被重新计算 $pos$ 的四元组，仍然产生贡献。事实上，这些没被改变的区间，依旧会把 $s_{L\sim pos}$ 分别加上一。

事实上，你注意到，$s$ 被修改，都是这种 $s_{L\sim pos}$ 全部加一的操作。而我们整个的过程中：会加入一组新的 $[L,pos]$，或者删除一个以前的 $[L,pos]$（修改可以视作删除后再加入）。而一个时刻的操作结束后，所有存在的 $[L,pos]$，都应该使得 $S_{L\sim pos}$ 加一。

所以，真正的问题，是在离线扫描线并单调栈后转成的这个问题：

- 每个时刻，加入任意多的区间，删除任意多的区间。

- 每个时刻，区间的加入和删除结束后，对于存在的每一个区间 $[L,R]$，把 $s_{L\sim R}$ 全部加一。

- 每个时刻，加一结束后，你应该有能力能够计算 $s$ 的任意区间和。

这东西怎么做呢，我可以告诉大家我不会做。

但是单调栈把 $[1,r]$ 划分出的若干个区间是不交的，所以任意时刻 $[L,pos]$ 也是不交的。放在这个问题上，就是说任意时刻没有两个区间有交。问题瞬间可做起来。

考虑，没有删除怎么做。那么没有被区间覆盖的点对答案是无意义的。如果一个点被覆盖，只要把当前时间和它被覆盖的时间作差 $+1$ 就行。 

更一般地，设 $t_i$ 是点 $i$ 被覆盖的时刻（如果不被覆盖，则 $t_i=0$），然后对于一次 $[l,r]$ 的求和。设当前时间为 $j$,$[l,r]$ 内有 $k$ 个被覆盖的点，则 $ans=k\times (j+1)-\sum_{i=l}^{r}t_i$。

$t$ 和用来求 $k$ 的线段树都是一个区间推平，区间求和，至少看上去是。但是你认真想一下就知道是区间加减，区间求和了，不作解释。

然后删除也很简单，再开一个线段树 $f$ 记录这些删除点的贡献。就是说假设一个存在了 $a$ 个时刻的区间 $[L,R]$ 删除，那么把 $f_{L\sim R}$ 全部加 $a$ 即可。然后求答案的时候把上面那个式子额外加上 $f_{L\sim R}$ 就行了~

这样这个问题就解决了... 设有 $m$ 个区间，则时间复杂度是 $O(m\log n)$ 的。

显然本题里 $m=n\log n$ （其实就是$(\sum_{i=1}^{n}\omega(i)$）。

不难发现最后整个完整的复杂度是 $O(\sum_{i=1}^{n}\omega(i)^2+n\log^2 n+q\log n)$ 的。由于运算量还是有点大，这个时候线段树都是“区间加，区间求和”发挥用场了：全部用 2 颗 BIT 去替代即可让常数小很多。

P.S. 请大家不要使用 ```std::endl``` ，卡了半天常数发现是这里太慢了，换种 IO 就过了，呜呜呜。
 
```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int MAXN=2e5+19,MAXQ=1e6+10;
int n,q,p[MAXN],pos[MAXN];
vector<int>d[MAXN];
int calc(int l,int r,int R,int maxn){
    int ret=0;
    for(auto u:d[maxn]){
        int v=maxn/u;if(u>=v)break;
        if(pos[u]>=l && pos[v]>=l && pos[u]<=R && pos[v]<=R)ret=max(ret,min(pos[u],pos[v]));
    }
    return min(ret,r);
}   
struct BIT{
    ll t[MAXN];
    void upd(int x,ll val){for(;x<=n;x+=lowbit(x))t[x]+=val;}
    ll qry(int x,ll s=0){for(;x;x-=lowbit(x))s+=t[x];return s;}
};
struct Seg{
    BIT t1,t2;
    void upd(int l,int r,ll val){
        t1.upd(l,val);t2.upd(l,l*val);
        t1.upd(r+1,-val);t2.upd(r+1,-(r+1)*val);
    }
    ll qry(int l){
        if(!l)return 0;
        return (l+1)*t1.qry(l)-t2.qry(l);
    }   
    ll qry(int l,int r){return qry(r)-qry(l-1);}
}F,S,T;
//F:答案
//S:时间和
//T:标记
vector<array<int,2> >qry[MAXN];
ll ans[MAXQ];
void insert_interval(int l,int r,int t){
    //时刻t，插入区间[l,r]
    T.upd(l,r,1);S.upd(l,r,t);
}
void remove_interval(int l,int r,int s,int t){
    //时刻t删除时刻s的区间[l,r]
    F.upd(l,r,t-s);T.upd(l,r,-1);S.upd(l,r,-s);
}
ll ask_sum(int l,int r,int t){
    //时刻t查询s[l]~s[r]
    ll ret=F.qry(l,r),cnt=T.qry(l,r),sum=S.qry(l,r);
    ret+=cnt*(t+1)-sum;
    return ret;
}
array<int,5>st[MAXN];
int idx[MAXN],top;
void solve(){
    rep(i,1,n){
        int l=i,r=i;
        while(top && st[top][0]<p[i]){
            l=st[top][1];
            idx[st[top][0]]=0;
            if(st[top][3])remove_interval(st[top][1],st[top][3],st[top][4],i);
            top--;
        }
        int ret=calc(l,r,r,p[i]);
        st[++top]={p[i],l,r,ret,i};
        idx[p[i]]=top;
        if(ret)insert_interval(l,ret,i);
        rep(j,2,n)if(p[i]*j<=n){
            if(!idx[p[i]*j])continue;
            int u=idx[p[i]*j];
            //修改第u段的信息
            if(st[u][3])remove_interval(st[u][1],st[u][3],st[u][4],i);
            int l=st[u][1],r=st[u][2],ret=calc(l,r,i,st[u][0]);
            st[u][3]=ret;st[u][4]=i;
            if(st[u][3])insert_interval(st[u][1],st[u][3],i);
        }else break;
        for(auto q:qry[i])ans[q[1]]=ask_sum(q[0],i,i);
    }
}
void Read(int& num){
    char ch;
    while((ch=getchar()) && !isdigit(ch));
    num=ch-'0';
    while((ch=getchar()) && isdigit(ch))num=num*10+ch-'0';
}
void Write(ll num){
    if(!num)return;
    Write(num/10);putchar('0'+num%10);
}
int main(){
    Read(n);Read(q);
    rep(i,1,n)rep(j,1,n)if(i*j<=n)d[i*j].push_back(i);else break;
    rep(i,1,n)Read(p[i]),pos[p[i]]=i;
    rep(i,1,q){
        int l,r;Read(l);Read(r);
        qry[r].push_back({l,i});
    }
    solve();
    rep(i,1,q){
        if(ans[i])Write(ans[i]);else putchar('0');putchar('\n');
    }
    return 0;
}
```

---

## 作者：Mirasycle (赞：1)

尝试找到可以贡献的区间放到二维平面内，其中横坐标代表左端点，纵坐标代表右端点，然后求子区间就是平面矩阵求和。

对于 $p_i\times p_j$ 是一个经典的调和级数处理，我们枚举 $p_i$，再枚举 $p_j$ 满足 $p_i\times p_j\le n$，是 $O(n\operatorname{ln} n)$。此时确定了 $i,j$ 之后可以唯一确定 $k$，接着根据三者位置关系可以得到若干满足条件的区间。

可以用单调栈求出 $p_k$ 作为最大值的区间 $[ml_k,mr_k]$，如果 $i,j\in [ml_k,mr_k]$ 的话，我们就可以得到左端点在 $[ml_k,\min(i,j,k)]$ 之间，右端点在 $[\max(i,j,k),mr_k]$ 之间的区间可以对于答案产生贡献。

对于一个 $k$ 可能有多个贡献区间，某些贡献会算重。考虑去重，对于 $k$ 所支配的若干个区间 $(l_i,r_i)$，我们以 $l_i$ 为第一关键字降序排序，$r_i$ 为第二关键字升序排序。考虑 $(l_{i-1},r_{i-1})$ (棕线) 和 $(l_i,r_i)$ （银线），可以发现银线中去除棕线内容后就是红色部分，于是我们每次截取这个红色部分矩阵加入贡献即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/15mm1ewr.png)

这样子就不会算重了，问题就变成了若干次矩阵加之后进行若干次矩阵求和，可以用扫描线加历史和来解决。

时间复杂度 $O(n\log^2 n)$。贡献区间个数是 $O(n\operatorname{ln} n)$ 级别的，所以是 2log。


```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
const int maxm=1e6+10;
int n,m,p[maxn],pos[maxn]; ll ans[maxm];
int st[maxn],ml[maxn],mr[maxn],top=0,tot=0;
vector<pair<int,int> > vec[maxn]; pair<int,int> b[maxn]; 
void chkmax(int &x,int y){ x=x>y?x:y; }
void chkmin(int &x,int y){ x=x<y?x:y; }
struct Info{
	ll s,hs; int len;
}info[maxn<<2];
struct Tag{
	ll ad,had;
}tag[maxn<<2];
Info operator + (Info a,const Info b){ return {a.s+b.s,a.hs+b.hs,a.len+b.len}; }
Info operator + (Info a,Tag b){ return {a.s+b.ad*a.len,a.hs+b.had*a.len,a.len}; }
Tag operator + (Tag a,Tag b){ return {a.ad+b.ad,a.had+b.had}; }
struct SegmentTree{
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid (l+r>>1)
	void pushup(int p){ info[p]=info[ls]+info[rs]; }
	void upd(int p,Tag z){ info[p]=info[p]+z; tag[p]=tag[p]+z; }
	void pushdown(int p){
		upd(ls,tag[p]); upd(rs,tag[p]);
		tag[p]={0,0};
	}
	void build(int p,int l,int r){
		if(l==r){ info[p]={0,0,1}; return ; }
		build(ls,l,mid); build(rs,mid+1,r); pushup(p);
	}
	void modify(int p,int l,int r,int ql,int qr,Tag z){
		if(ql<=l&&r<=qr){ upd(p,z); return ; }
		pushdown(p);
		if(ql<=mid) modify(ls,l,mid,ql,qr,z);
		if(qr>mid) modify(rs,mid+1,r,ql,qr,z);
		pushup(p);
	}
	Info query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return info[p];
		pushdown(p); Info res={0,0};
		if(ql<=mid) res=res+query(ls,l,mid,ql,qr);
		if(qr>mid) res=res+query(rs,mid+1,r,ql,qr);
		return res;
	}
}seg;
struct Q{
	int l,r,v,id;
}; vector<Q> qu[maxn];
struct Add{
	int l,r,v;
}; vector<Add> ad[maxn];
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m; seg.build(1,1,n);
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) pos[p[i]]=i;
	st[top=1]=0;
	for(int i=1;i<=n;i++){
		while(p[i]>p[st[top]]&&top>1) top--;
		ml[i]=st[top]+1; st[++top]=i; 
	}
	st[top=1]=n+1;
	for(int i=n;i>=1;i--){
		while(p[i]>p[st[top]]&&top>1) top--;
		mr[i]=st[top]-1; st[++top]=i;
	}
	for(int i=1;i*i<n;i++){
		for(int j=1;j*i<=n;j++){
			if(i>=j) continue;
			int p1=pos[i],p2=pos[j],p3=pos[i*j];
			if(min(p1,p2)<ml[p3]||max(p1,p2)>mr[p3]) continue;
			int L=min(min(p1,p2),p3),R=max(max(p1,p2),p3);
			vec[p3].pb(L,-R);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vec[i].size()) continue;
		sort(vec[i].begin(),vec[i].end()); 
		reverse(vec[i].begin(),vec[i].end());
		int l=i+1,r=mr[i]+1;
		for(auto z:vec[i]){
			int ql=z.fi,qr=-z.se;
			if(ql<l&&qr<r){
				ad[ml[i]].pb((Add){qr,r-1,1});
				ad[ql+1].pb((Add){qr,r-1,-1});
			}
			chkmin(l,ql); chkmin(r,qr);
		}
	}
	for(int i=1;i<=m;i++){
		int l,r; cin>>l>>r;
		qu[l-1].pb((Q){l,r,-1,i});
		qu[r].pb((Q){l,r,1,i});
	}
	seg.build(1,1,n); int T=0;
	for(int i=1;i<=n;i++,T++){
		for(auto z:ad[i]) seg.modify(1,1,n,z.l,z.r,Tag{z.v,T*z.v});
		for(auto z:qu[i]){
			Info res=seg.query(1,1,n,z.l,z.r);
			ans[z.id]+=z.v*(res.s*(T+1)-res.hs);
		}
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：_ANIG_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1677E)

首先根据经典套路把询问离线，按照右端点递增的顺序处理询问。

假设当前右端点为 $r$，$T_l$ 为 $0/1$，表示区间 $[l,r]$ 是否合法。

考虑哪些区间的合法性会改变。

首先考虑如何把合法区间变得不合法。

可以发现，若区间 $[l,r]$ 本来是合法的，则使这个区间变得不合法的情况只可能是区间最大值发生了改变。

于是可以维护一个单调栈，如果区间 $[l,r]$ 的最大值发生改变，可以直接把 $T_l$ 设成 $0$，不应该变成 $0$ 的会在下文被变回去。

下面考虑哪些不合法区间会变合法。

要么区间最大值发生改变，要么出现了新的合法二元组 $(i,j)$。

对于第一种情况，由于最大值改变只可能变成 $a_r$，所以我们枚举 $a_r$ 的因数，然后找到对应合法的区间即可。

对于第二种情况，我们枚举 $i$ 的值，总次数是调和级数 $O(n\ln n)$。

再维护一个 $ans_l$，操作完直接把每个 $ans_l$ 加上 $T_l$，查询的时候求 $ans$ 的区间和。

于是问题变为区间 $T$ 赋值，区间 $ans$ 加上 $T$ 和区间 $ans$ 求和。

可以用矩阵维护，每个点维护一个 $1\times 3$ 的向量，分别是 $T$，$ans$ 和常量 $1$。

这样**理论**复杂度为 $O(n\log^2 n+q\log n)$，还有 $27$ 倍常数，几乎跟三个 $\log$ 没啥区别。

需要卡一下常。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5,M=1e6+5,inf=1e9;
int hh[3][3];
struct jz{
    ll w[3][3];
    friend jz operator*(jz a,jz b){
        jz c;
		c.w[0][0]=a.w[0][0]*b.w[0][0]+a.w[0][1]*b.w[1][0];
        c.w[0][1]=a.w[0][0]*b.w[0][1]+a.w[0][1]*b.w[1][1];
        c.w[0][2]=a.w[0][0]*b.w[0][2]+a.w[0][1]*b.w[1][2]+a.w[0][2]*b.w[2][2];
        c.w[1][0]=a.w[1][0]*b.w[0][0]+a.w[1][1]*b.w[1][0];
        c.w[1][1]=a.w[1][0]*b.w[0][1]+a.w[1][1]*b.w[1][1];
        c.w[1][2]=a.w[1][0]*b.w[0][2]+a.w[1][1]*b.w[1][2]+a.w[1][2]*b.w[2][2];
        c.w[2][2]=a.w[2][0]*b.w[0][2]+a.w[2][1]*b.w[1][2]+a.w[2][2]*b.w[2][2];
		return c;
    }
    friend jz operator+(jz a,jz b){
		for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                a.w[i][j]+=b.w[i][j];
            }
        }
		return a;
    }
    bool empty(){
        return w[0][0]==1&&w[0][1]==0&&w[0][2]==0&&w[1][0]==0&&w[1][1]==1&&w[1][2]==0&&w[2][0]==0&&w[2][1]==0&&w[2][2]==1;
    }
}emp,st0,st1,ad;
namespace tr{
    struct node{
        int l,r;
        jz sm,laz;
    }p[N<<2];
    void upset(int x){
        p[x].sm=p[x<<1].sm+p[x<<1|1].sm;
    }
    void reset(int x,int l,int r){
        p[x].l=l,p[x].r=r;
        p[x].laz=emp;
        if(l==r){
            p[x].sm.w[0][1]=1;
            return;
        }
        int mid=l+r>>1;
        reset(x<<1,l,mid);
        reset(x<<1|1,mid+1,r);
        upset(x);
    }
    void mul(int x,jz sm){
        p[x].sm=p[x].sm*sm;
        p[x].laz=p[x].laz*sm;
    }
    void dnset(int x){
        if(!p[x].laz.empty()){
            mul(x<<1,p[x].laz);
            mul(x<<1|1,p[x].laz);
            p[x].laz=emp;
        }
    }
    void mul(int x,int l,int r,jz sm){
        if(l>r)return;
        if(l<=p[x].l&&r>=p[x].r){
            mul(x,sm);
            return;
        }
        int mid=p[x].l+p[x].r>>1;
        dnset(x);
        if(l<=mid)mul(x<<1,l,r,sm);
        if(r>mid)mul(x<<1|1,l,r,sm);
        upset(x);
    }
    jz gets(int x,int l,int r){
        if(l<=p[x].l&&r>=p[x].r)return p[x].sm;
        int mid=p[x].l+p[x].r>>1;
        dnset(x);
        if(r<=mid)return gets(x<<1,l,r);
        if(l>mid)return gets(x<<1|1,l,r);
        return gets(x<<1,l,r)+gets(x<<1|1,l,r);
    }
}
int n,m,p[N],wz[N],lst[N],nxt[N];
ll rs[M];
vector<pair<int,int> >g[N];
vector<int>ys[N],qq;
struct node{
    int l,r,sm;
};
vector<node>q;
void write(ll x){
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int read(){
    int res=0;char c;
    do{
        c=getchar();
    }while(!isdigit(c));
    while(isdigit(c))res=res*10+c-'0',c=getchar();
    return res;
}
signed main(){
    int sttt=clock();
    emp.w[0][0]=emp.w[1][1]=emp.w[2][2]=1;
    st1.w[1][0]=1;st1.w[1][1]=1;st1.w[2][2]=1;
    st0.w[1][1]=1;st0.w[2][2]=1;
    ad.w[0][0]=1,ad.w[1][1]=1,ad.w[2][2]=1,ad.w[0][2]=1;
    cin>>n>>m;
    for(int i=1;i<=n;i++)p[i]=n-i+1,scanf("%d",&p[i]),wz[p[i]]=i;
    qq.push_back(0);
    p[0]=p[n+1]=inf;
    for(int i=1;i<=n;i++){
        while(p[qq.back()]<=p[i])qq.pop_back();
        lst[i]=qq.back();
        qq.push_back(i);
    }
    qq.clear();
    qq.push_back(n+1);
    for(int i=n;i>=1;i--){
        while(p[qq.back()]<=p[i])qq.pop_back();
        nxt[i]=qq.back();
        qq.push_back(i);
    }
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j+=i)ys[j].push_back(i);
    for(int i=1;i<=m;i++){
        int l,r;
        l=read(),r=read();
        g[r].push_back(make_pair(l,i));
    }
    tr::reset(1,1,n);
    for(int i=1;i<=n;i++){
        int zh=i;
        while(q.size()&&q.back().sm<=p[i]){
            tr::mul(1,q.back().l,q.back().r,st0);
            zh=q.back().l;
            q.pop_back();
        }
        if(!q.size())q.push_back((node){1,i,p[i]});
        else q.push_back((node){q.back().r+1,i,p[i]});
        vector<pair<int,int> >jl;
        int mx=0;
        for(int j=0;j<ys[p[i]].size();j++){
            int a=ys[p[i]][j],b=p[i]/a;
            if(wz[a]>=wz[b]||wz[a]>i||wz[b]>i)continue;
            mx=max(mx,wz[a]);
        }
        jl.push_back(make_pair(zh,mx));
        for(int j=1;j*p[i]<=n;j++){
            if(wz[j*p[i]]>i)continue;
            if(wz[j]>=i)continue;
            if(nxt[wz[j*p[i]]]<=i)continue;
            jl.push_back(make_pair(lst[wz[j*p[i]]]+1,min(wz[j],wz[j*p[i]])));
        }
        sort(jl.begin(),jl.end());
        int zd=0;
        for(int j=0;j<jl.size();j++){
            tr::mul(1,max(jl[j].first,zd+1),jl[j].second,st1);
            zd=max(zd,jl[j].second);
        }
        tr::mul(1,1,i,ad);
        for(int j=0;j<g[i].size();j++){
            rs[g[i][j].second]=tr::gets(1,g[i][j].first,n).w[0][2];
        }
    }
    for(int i=1;i<=m;i++){
        write(rs[i]);
        putchar('\n');
    }
}
```


---

## 作者：Lgx_Q (赞：1)

题意：给出 $n,a_{1...n}$。多次询问，给出 $[l,r]$，求 $[l,r]$ 有多少个子区间满足条件。

条件：区间 $[x,y]$ 中，存在 $i,j(x\le i<j\le y)$，满足 $a_i\cdot a_j=\max\limits_{x\le k\le y}\{a_k\}$。

$1\le n\le 2\times 10^5,\space 1\le q\le 10^6$

----

套路题。

考虑枚举 $k,i,j$，对询问的区间做贡献，这与 ARC067F 的套路是类似的。

在笛卡尔树上枚举 $k$，可以确定合法的 $i,j$ 范围；对于 $a_k$，考虑枚举他的约数，通过这样就能枚举出合法的 $i,j$。

设 $k$ 在笛卡尔树上覆盖的区间为 $[L,R]$，令 $x=\min(k,i,j),y=\max(k,i,j)$，那么这个条件贡献的区间 $[l,r]$ 满足 $L\le l\le x,\space y\le r\le R$。

把 $l,r$ 作为两个维度，放在二维平面上，我们相当于覆盖了一个矩形，每次查询一个矩形里被覆盖的面积。

覆盖矩形不好做。考虑一个点 $(l,r)$ 只会被同一个 $k$ 覆盖多次，即同一个 $k$，被多个 $i,j$ 贡献。把对应的 $x,y$ 排序，用栈存下有用的信息，即可将矩形覆盖转化为一个矩形区域 $+1$。

最后 离线扫描线 + 线段树/树状数组维护区间历史版本和 即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define max(a,b) ((a)>(b)? (a):(b))
#define min(a,b) ((a)<(b)? (a):(b))
#define pir pair<ll,ll>
#define mkp make_pair
#define x first
#define y second 
using namespace std;
const ll maxn=2e5+10;
ll n,m,st[20][maxn],a[maxn],b[maxn],Log[maxn],wt,ans[maxn*5],tree[4][maxn];
vector<ll>fac[maxn];
pir lsm[maxn];
void add(ll ty,ll x,ll v)
{
	while(x<=n)
	{
		tree[ty][x]+=v; x+=x&-x;
	}
}
ll ask(ll ty,ll x)
{
	ll v=0;
	while(x)
	{
		v+=tree[ty][x]; x-=x&-x;
	}
	return v;
}
struct node
{
	ll l,r,v;
};
struct query
{
	ll l,r,id,v;
};
vector<query>Qry[maxn];
vector<node>vec[maxn];
ll Max(ll x,ll y)
{
	return a[x]>a[y]? x:y;
}
ll qry(ll l,ll r)
{
	ll k=Log[r-l+1];
	return Max(st[k][l],st[k][r-(1<<k)+1]);
}
void solve(ll l,ll r)
{
	if(l>r) return;
	ll x=qry(l,r), y=a[x];
	solve(l,x-1);
	solve(x+1,r);
	wt=0;
	for(ll i:fac[y])
	{
		if(i*i>=y) break;
		ll p=min(min(b[i],b[y/i]),x), q=max(max(b[i],b[y/i]),x);
		if(l<=p&&q<=r) lsm[++wt]=mkp(-p,q);
	}
	sort(lsm+1,lsm+wt+1);
	ll wf=0;
	for(ll i=1;i<=wt;i++)
		if(!wf||lsm[wf].y>lsm[i].y) lsm[++wf]=lsm[i], lsm[wf].x*=-1;
	reverse(lsm+1,lsm+1+wf);
	wt=wf;
	for(ll i=1;i<=wt;i++)
	{
		ll kl=(i==1? l:lsm[i-1].x+1);
		vec[kl].pb((node){lsm[i].y,r,1});
		vec[lsm[i].x+1].pb((node){lsm[i].y,r,-1});
	}
}
ll Ask(ll ty,ll l,ll r)
{
	--l;
	return (ask(ty*2,r)*(r+1)-ask(ty*2+1,r))-(ask(ty*2,l)*(l+1)-ask(ty*2+1,l));
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)
		for(ll j=i;j<=n;j+=i)
			fac[j].pb(i);
	for(ll i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
		st[0][i]=i; b[a[i]]=i;
	}
	for(ll i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
	for(ll i=1;(1<<i)<=n;i++)
		for(ll j=1;j+(1<<i)-1<=n;j++)
			st[i][j]=Max(st[i-1][j],st[i-1][j+(1<<i-1)]);
	solve(1,n);
	for(ll i=1;i<=m;i++)
	{
		ll l,r; scanf("%lld%lld",&l,&r);
		Qry[r].pb((query){l,r,i,1});
		Qry[l-1].pb((query){l,r,i,-1});
	}
	for(ll i=1;i<=n;i++)
	{
		for(node nd:vec[i])
		{
			add(0,nd.l,nd.v);
			add(0,nd.r+1,-nd.v);
			add(1,nd.l,nd.v*nd.l);
			add(1,nd.r+1,-nd.v*(nd.r+1));
			add(2,nd.l,nd.v*(i-1));
			add(2,nd.r+1,-nd.v*(i-1));
			add(3,nd.l,nd.v*nd.l*(i-1));
			add(3,nd.r+1,-nd.v*(nd.r+1)*(i-1));
		}
		for(query qr:Qry[i])
		{
			ans[qr.id]+=qr.v*(Ask(0,qr.l,qr.r)*i-Ask(1,qr.l,qr.r));
		}
	}
	for(ll i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：CatFromMars (赞：0)

首先简单观察一下，注意到
1. 形如 $a_ia_j = a_k$ 的三元组 $(i, j, k)$ 只有 $O(n\log n)$ 组。
2. $\max_{i = l}^r a_i$ 有关可以笛卡尔树后考虑贡献。

于是我们容易想到对于 $x$ 考虑它在 $[sl, sr]$ 内是最大值，每一对 $a_ua_v = a_x, u, v\in[sl, sr]$ 最后都可以转化为 $l\in[sl, L], r\in[R, sr]$ 时这个点对时合法的。对于不同的 $x$ 不会重复计数，但是对于同一个 $x$ 可能会，因为可能会有一个区间存在两个乘积等于 $a_x$ 的点对。对于同一个 $x$ 考虑去重。把 $l, r$ 画成一个矩形，以 $l$ 为横轴，$r$ 为纵轴，那么我们发现每个矩形的左上角都是固定的，只需要用类单调栈的东西就可以把这些矩形的并求出来。

然后问题就变成了矩形 $+1$，矩形求和，可以离线后转化为区间加区间历史和问题。

```cpp
#include <bits/stdc++.h>
#define int long long
#define il inline
#define ll long long
using namespace std;
const int N = 2e5, M = 4e6;
il int read() {
	int k = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') {
		k = k * 10 + ch - '0';
		ch = getchar();
	}
	return k;
}
il void write(int x) {
	if(!x) {
		putchar('0');
		return ;
	}
	int tmp[20], len = 0;
	while(x) tmp[++len] = x % 10, x /= 10;
	for(int i = len; i >= 1; i--)
		putchar(char(tmp[i] + '0'));
}

vector <int> fac[N + 10];
int n, q;
int a[N + 10], pa[N + 10];
int sta[N + 10], top, sl[N + 10], sr[N + 10];

struct node {
	int xl, xr, yl, yr;
};
vector <node> vec;

struct dot {
	int l, r;
	bool operator < (const dot &other) const {
		if(l != other.l) return l < other.l;
		else return r < other.r;
	}
};

int qzm[N + 10];
void work(int x) {//求矩形并
	vector <dot> r;
	for(int i = 0; i < fac[a[x]].size(); i++) {
		int w = fac[a[x]][i];
		if(a[w] * a[w] < a[x]) {
			int v = pa[a[x] / a[w]];
			if(w > v) swap(w, v);
			int L = min(x, w);
			int R = max(x, v);
			if(L >= sl[x] && R <= sr[x]) {
				r.push_back((dot){L, R});
			}
		}
	}
	sort(r.begin(), r.end());

	if(r.empty()) return ;
	vector <int> sk;
	sk.push_back(r[r.size() - 1].l);
	qzm[r.size() - 1] = r[r.size() - 1].r;
	int last = r.size() - 1;
	for(int i = r.size() - 2; i >= 0; i--) {
		if(qzm[i + 1] > r[i].r) {
			qzm[i] = r[i].r;
			int t = sk[sk.size() - 1];
			sk.push_back(r[i].l);
			if(r[i].l + 1 <= t)
				vec.push_back((node){r[i].l + 1, t, qzm[i + 1], sr[x]});
			last = i;
		}
		else qzm[i] = qzm[i + 1];
	}
	int t = sk[sk.size() - 1];
	if(sl[x] <= t)
	vec.push_back((node){sl[x], t, qzm[0], sr[x]});
}

struct ddt {
	int x, yl, yr, val;
	bool operator < (const ddt &other) const {
		return x < other.x;
	}
};
struct qy {
	int x, l, r, t, ind;
	bool operator < (const qy &other) const {
		return x < other.x;
	}
} Q[M * 2 + 10];
int Ans[M + 10];
vector <ddt> dotvc;
struct piar {
	ll x, y;
};
namespace seg {
	il int ls(int x) {
		return x * 2;
	}
	il int rs(int x) {
		return x * 2 + 1;
	}
	ll sum[N * 4 + 10], sumh[N * 4 + 10];
	ll tag[N * 4 + 10], tagh[N * 4 + 10];
	il void push_up(int now) {
		sum[now] = sum[ls(now)] + sum[rs(now)];
		sumh[now] = sumh[ls(now)] + sumh[rs(now)];
	}
	il void push_tag(int now, int s, int t, ll v1, ll v2) {
		sum[now] += 1ll * (t - s + 1) * v1;
		sumh[now] += 1ll * (t - s + 1) * v2;
		tag[now] += v1;
		tagh[now] += v2;
	}
	il void push_down(int now, int s, int t) {
		if(tag[now] || tagh[now]) {
			int mid = (s + t) >> 1;
			push_tag(ls(now), s, mid, tag[now], tagh[now]);
			push_tag(rs(now), mid + 1, t, tag[now], tagh[now]);
			tag[now] = tagh[now] = 0;
		}
	}
	void upd(int ql, int qr, int s, int t, int now, ll v1, ll v2) {
		if(ql <= s && t <= qr) {
			push_tag(now, s, t, v1, v2);
			return ;
		}
		int mid = (s + t) >> 1;
		push_down(now, s, t);
		if(ql <= mid) upd(ql, qr, s, mid, ls(now), v1, v2);
		if(qr > mid) upd(ql, qr, mid + 1, t, rs(now), v1, v2);
		push_up(now);
	}
	piar qry(int ql, int qr, int s, int t, int now) {
		if(ql <= s && t <= qr) return (piar){sum[now], sumh[now]};
		int mid = (s + t) >> 1;
		push_down(now, s, t);
		if(ql > mid) return qry(ql, qr, mid + 1, t, rs(now));
		if(qr <= mid) return qry(ql, qr, s, mid, ls(now));
		piar A = qry(ql, qr, s, mid, ls(now));
		piar B = qry(ql, qr, mid + 1, t, rs(now));
		return (piar){A.x + B.x, A.y + B.y};
	}
}
signed main() {
	n = read(), q = read();
	for(int i = 1; i <= n; i++)
		a[i] = read(), pa[a[i]] = i;
	for(int i = 1; i <= n; i++) {
		for(int j = i; j <= n; j += i)
			fac[j].push_back(pa[i]);
	}
	top = 0;
	for(int i = 1; i <= n; i++) {
		while(top)
			if(a[sta[top]] < a[i]) top--;
			else break;
		if(!top) sl[i] = 1;
		else sl[i] = sta[top] + 1;
		sta[++top] = i;
	}
	top = 0;
	for(int i = n; i >= 1; i--) {
		while(top)
			if(a[sta[top]] < a[i]) top--;
			else break;
		if(!top) sr[i] = n;
		else sr[i] = sta[top] - 1;
		sta[++top] = i;
	}

	for(int i = 1; i <= n; i++)
		work(i);

	for(int i = 0; i < vec.size(); i++) {
		if(vec[i].xl == vec[i].yl && vec[i].yl == vec[i].xr && vec[i].yl == vec[i].yr) continue;
		dotvc.push_back((ddt){vec[i].xl, vec[i].yl, vec[i].yr, 1});
		dotvc.push_back((ddt){vec[i].xr + 1, vec[i].yl, vec[i].yr, -1});
	}

	sort(dotvc.begin(), dotvc.end());
	for(int i = 1; i <= q; i++) {
		int l, r; l = read(), r = read();
		Q[2 * i - 1] = (qy){l - 1, l, r, -1, i};
		Q[2 * i] = (qy){r, l, r, 1, i};
	}
	sort(Q + 1, Q + 2 * q + 1);

	int now = 0, lastx = 0;
	for(int i = 1; i <= 2 * q; i++) {
		// cout << i << endl;
		while(now < dotvc.size() && dotvc[now].x <= Q[i].x) {
			seg::upd(dotvc[now].yl, dotvc[now].yr, 1, n, 1, dotvc[now].val, 1ll * dotvc[now].val * dotvc[now].x);
			now++;
		}
		piar t = seg::qry(Q[i].l, Q[i].r, 1, n, 1);
		Ans[Q[i].ind] += (1ll *((Q[i].x + 1) * t.x) - t.y) * Q[i].t;
	}
	for(int i = 1; i <= q; i++)
		write(Ans[i]), putchar('\n');
}
```

---

## 作者：intel_core (赞：0)

先枚举子区间最大值，然后考虑计算答案。

注意到 $a_ia_j=\max$ 的 $(i,j)$ 只有 $n\log n$ 对，所以对于每个 $k$ 作为最大值时，可以把对应的 $i,j$ 位置找出来。

设前后第一个比 $a_k$ 大的数是 $a_L$ 和 $a_R$，假设现在有一对 $(i,j)$ 满足 $a_ia_j=a_k$ 且 $i<k<j$，那么对于 $L<x\le i<j\le y<R$ 的子区间 $[x,y]$ 一定都是美丽的。$i,j,k$ 的其它相对大小关系类似。

转到二维平面上，相当于现在有 $O(n\log n)$ 个矩形，要询问一个矩形区域内至少被一个矩形覆盖过的点的个数。这个是历史和板子题。

故复杂度 $O(n\log ^2n+q\log n)$。

---

## 作者：orz_z (赞：0)

### CF1677E Tokitsukaze and Beautiful Subsegments

好题。

对于区间最大值，考虑单调栈维护，记一个数 $a_i$ 左右边第一个比他大的数分别为 $L_i$ 和 $R_i$。

则对于区间 $[l,r]$ 满足 $L_i<l\leq r<R_i$，有 $\max_{k=l}^{r}a_k=a_i$。

对于每个 $a_i$，我们可以尝试确定区间左端点范围 $[L,R]$，初始 $L=L_i+1$，$R=L_i$。

接着，枚举 $a_i$ 的因数 $x,y$，判断是否 $L_i<pos_x,pos_y \leq i$，即在范围内，然后更新 $R=\min(pos_x,pos_y)$，总时间复杂度 $\mathcal O(\sum\sqrt{a_i})$。

然后枚举区间右端点，算出与它乘积为 $a_i$ 的数的位置，判断是否在范围内，更新 $R$，记录。

这样就记录下了 $(L,R,r)$，表示右端点为 $r$，左端点为 $[L,R]$ 的区间是美丽的。

考虑扫描线，将询问离线，右端点升序，把右端点为 $i$ 的所有三元组加入线段树，即区间加 $1$。

时间复杂度 $\mathcal O(n^2\log n)$。

考虑优化，每次枚举 $[i,R_i]$ 和 $[L_i,i]$ 中长度小的，记录三元组，这样时间复杂度均摊 $\mathcal O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * f;
}

inline void write(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 1e6 + 10;

int n, q, s[_], t, a[_], pos[_], L[_], R[_], sz[_ << 2], tag[_ << 2], tr[_ << 2], as[_];

struct abc {
	int l, r, id;
} qr[_];

bool cmp(abc a, abc b) {
	return a.r < b.r;
}

bool cmp2(abc a, abc b) {
	return a.l > b.l;
}

vector<pair<int, int>> d[_], d2[_];

void build(int o, int l, int r) {
	sz[o] = (r - l + 1), tr[o] = tag[o] = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r);
}

void pushdown(int o) {
	if (tag[o]) {
		tr[o << 1] += sz[o << 1] * tag[o];
		tr[o << 1 | 1] += sz[o << 1 | 1] * tag[o];
		tag[o << 1] += tag[o];
		tag[o << 1 | 1] += tag[o];
		tag[o] = 0;
	}
}

void upd(int o, int l, int r, int L, int R, int k) {
	if (L <= l && r <= R) {
		tr[o] += sz[o] * k, tag[o] += k;
		return;
	}
	pushdown(o);
	int mid = (l + r) >> 1;
	if (L <= mid) upd(o << 1, l, mid, L, R, k);
	if (R > mid) upd(o << 1 | 1, mid + 1, r, L, R, k);
	tr[o] = tr[o << 1] + tr[o << 1 | 1];
}

int qry(int o, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tr[o];
	pushdown(o);
	int mid = (l + r) >> 1, res = 0;
	if (L <= mid) res = qry(o << 1, l, mid, L, R);
	if (R > mid) res += qry(o << 1 | 1, mid + 1, r, L, R);
	tr[o] = tr[o << 1] + tr[o << 1 | 1];
	return res;
}

signed main() {
	n = read(), q = read();
	for (int i = 1; i <= n; ++i) a[i] = read(), pos[a[i]] = i;
	t = 0;
	for (int i = 1; i <= n; ++i) {
		while (t > 0 && a[s[t]] < a[i]) t--;
		L[i] = s[t];
		s[++t] = i;
	}
	t = 0, s[0] = n + 1;
	for (int i = n; i >= 1; --i) {
		while (t > 0 && a[s[t]] < a[i]) t--;
		R[i] = s[t];
		s[++t] = i;
	}
	for (int i = 1; i <= q; ++i)
		qr[i].l = read(), qr[i].r = read(), qr[i].id = i;
	for (int i = 1; i <= n; ++i) {
		int l, r;
		if (R[i] - i <= i - L[i]) {
			r = L[i];
			for (int j = 1; j * j <= a[i]; ++j) {
				if (a[i] % j != 0) continue;
				int fx = pos[j], fy = pos[a[i] / j];
				if (fx == fy) continue;
				if (fx > fy) swap(fx, fy);
				if (fx > L[i] && fy <= i) r = max(r, fx);
			}
			for (int j = i; j < R[i]; ++j) {
				if (a[i] % a[j] == 0) {
					int nw = a[i] / a[j];
					if (pos[nw] == j) continue;
					if (pos[nw] > L[i] && pos[nw] < j) {
						r = max(r, pos[nw]);
						r = min(r, i);
					}
				}
				if (L[i] < r) d[j].push_back({L[i] + 1, r});
			}
		} else {
			l = R[i];
			for (int j = 1; j * j <= a[i]; ++j) {
				if (a[i] % j != 0) continue;
				int fx = pos[j], fy = pos[a[i] / j];
				if (fx == fy) continue;
				if (fx > fy) swap(fx, fy);
				if (fy < R[i] && fx >= i) l = min(l, fy);
			}
			for (int j = i; j > L[i]; --j) {
				if (a[i] % a[j] == 0) {
					int nw = a[i] / a[j];
					if (pos[nw] == j) continue;
					if (pos[nw] > j && pos[nw] < R[i]) {
						l = min(l, pos[nw]);
						l = max(l, i);
					}
				}
				if (l < R[i]) d2[j].push_back({l, R[i] - 1});
			}
		}
	}
	sort(qr + 1, qr + q + 1, cmp);
	build(1, 1, n);
	int k = 1;
	for (int i = 1; i <= n; ++i) {
		for (auto v : d[i]) upd(1, 1, n, v.first, v.second, 1);
		for (; qr[k].r == i && k <= q; ++k)
			as[qr[k].id] += qry(1, 1, n, qr[k].l, qr[k].r);
	}
	sort(qr + 1, qr + q + 1, cmp2);
	build(1, 1, n);
	k = 1;
	for (int i = n; i >= 1; --i) {
		for (auto v : d2[i]) upd(1, 1, n, v.first, v.second, 1);
		for (; qr[k].l == i && k <= q; ++k)
			as[qr[k].id] += qry(1, 1, n, qr[k].l, qr[k].r);
	}
	for (int i = 1; i <= q; ++i) write(as[i]), he;
	return 0;
}
```



---

