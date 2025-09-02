# ふたつのアンテナ (Two Antennas)

## 题目描述

有 $n$ 个天线，每个天线用 $a_i,l_i,r_i$ 描述。定义两个天线 $i,j$ 可以联络当且仅当 $|i-j|\in [l_i,r_i]\cap [l_j,r_j]$。

$q$ 次询问一个区间内可以联络的天线 $i,j$ 中 $|a_i-a_j|$ 最大是多少，不存在输出 $-1$。

$1\le n,q\le 2\times 10^5$，$1\le a_i\le 10^9$。

# 题解

## 作者：DaiRuiChen007 (赞：2)

# JOISC2019D 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2019_d)

**题目大意**

> 给定 $n$ 个点，每个点 $i$ 会向标号在 $[i-b_i,i-a_i]\cup[i+a_i,i+b_i]$ 范围内的人连一条有向边。
>
> $q$ 次询问 $[l,r]$ 之中所有双向连边的点 $(i,j)$，最大的 $|w_i-w_j|$ 是多少。
>
> 数据范围：$n,q\le 2\times 10^5$。

**思路分析**

显然 $|w_i-w_j|=\max(w_i-w_j,w_j-w_i)$，因此每个点权值取法再跑一遍即可得到答案。

考虑扫描线，线段树维护每个 $i$ 作为左端点的答案，把每个 $i$ 在 $i+a_i$ 处加入，$i+b_i+1$ 处删除。

对于每个 $i$ 作为右端点，我们用 $w_i$ 更新区间 $[i-b_i,i-a_i]$，线段树上维护 $-w_j$ 的最大值和 $w_i-w_j$ 的最大值，打标记的时候就很简单了。

注意删除 $i$ 的时候只能把 $-w_i$ 的最大值设成 $-\infty$，不能改 $w_i-w_j$ 的最大值，因为这些贡献依然存在。

时间复杂度 $\mathcal O((n+q)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5,inf=1e9;
int n,q;
struct SegmentTree {
	int tag[MAXN<<2],lmx[MAXN<<2],rmx[MAXN<<2];
	inline int L(int p) { return p<<1; }
	inline int R(int p) { return p<<1|1; }
	inline void psu(int p) {
		lmx[p]=max(lmx[L(p)],lmx[R(p)]);
		rmx[p]=max(rmx[L(p)],rmx[R(p)]);
	}
	inline void adt(int p,int k) {
		tag[p]=max(tag[p],k);
		rmx[p]=max(rmx[p],lmx[p]+k);
	}
	inline void psd(int p) {
		if(tag[p]!=-inf) adt(L(p),tag[p]),adt(R(p),tag[p]),tag[p]=-inf;
	}
	inline void build(int l=1,int r=n,int p=1) {
		tag[p]=lmx[p]=rmx[p]=-inf;
		if(l==r) return ;
		int mid=(l+r)>>1;
		build(l,mid,L(p)),build(mid+1,r,R(p));
	}
	inline void updl(int u,int k,int l=1,int r=n,int p=1) {
		if(l==r) return lmx[p]=k,void();
		int mid=(l+r)>>1; psd(p);
		if(u<=mid) updl(u,k,l,mid,L(p));
		else updl(u,k,mid+1,r,R(p));
		psu(p);
	}
	inline void updr(int ul,int ur,int k,int l=1,int r=n,int p=1) {
		if(ul<=l&&r<=ur) return adt(p,k);
		int mid=(l+r)>>1; psd(p);
		if(ul<=mid) updr(ul,ur,k,l,mid,L(p));
		if(mid<ur) updr(ul,ur,k,mid+1,r,R(p));
		psu(p);
	}
	inline int qry(int ul,int ur,int l=1,int r=n,int p=1) {
		if(ul<=l&&r<=ur) return rmx[p];
		int mid=(l+r)>>1; psd(p);
		if(ur<=mid) return qry(ul,ur,l,mid,L(p));
		if(mid<ul) return qry(ul,ur,mid+1,r,R(p));
		return max(qry(ul,ur,l,mid,L(p)),qry(ul,ur,mid+1,r,R(p)));
	}
}	TR;
struct Query { int l,r,id; };
vector <Query> Q[MAXN];
int h[MAXN],a[MAXN],b[MAXN],ans[MAXN];
vector <int> ins[MAXN<<1],ers[MAXN<<1];
inline void solve() {
	TR.build();
	for(int i=1;i<=n;++i) {
		for(int j:ins[i]) TR.updl(j,-h[j]);
		if(i>a[i]) TR.updr(max(1,i-b[i]),i-a[i],h[i]);
		for(auto x:Q[i]) ans[x.id]=max(ans[x.id],TR.qry(x.l,x.r));
		for(int j:ers[i]) TR.updl(j,-inf);
	}
}
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d%d%d",&h[i],&a[i],&b[i]);
		ins[i+a[i]].push_back(i),ers[i+b[i]].push_back(i);
	}
	scanf("%d",&q);
	for(int i=1,l,r;i<=q;++i) scanf("%d%d",&l,&r),Q[r].push_back({l,r,i});
	fill(ans+1,ans+q+1,-1);
	solve();
	for(int i=1;i<=n;++i) h[i]*=-1;
	solve();
	for(int i=1;i<=q;++i) printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：KellyFrog (赞：2)

将问题转化为对 $i<j$，求 $a_i-a_j$，做两遍即可。

将 $i$ 打到 $[i+l_i,i+r_i]$ 上，对 $j$ 做扫描线，对于 $j$ 就会有一个可能 $i$ 的集合，$j$ 会更新这个集合中在 $[j-r_j,j-l_j]$ 中的元素。

那么我们就要维护一个答案数组 $ans_i$，支持单点赋值 $a_i$（不在可能 $i$ 集合里的视为 $-\infty$）、区间求 $ans_i$ 的 $\max$、区间 $ans_i$ 和 $a_i-a_j$ 取 $\max$。

由于我们只需要求 $\max$，给每个线段树上节点打 $a_j$ 的 tag，打 tag 时更新答案，多个 tag 取最小的即可。

复杂度 $O((n+q)\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 2e5 + 5;
const int inf = 0x3f3f3f3f;

int n, q;
int a[N], l[N], r[N];
int ans[N];
vector<pair<int, int>> adj[N];
vector<int> bdj[N<<1];
int lazymx[N<<2], lazymi[N<<2], mx[N<<2], mi[N<<2], mxans[N<<2];

inline void setlazy(int o, int x) {
	lazymx[o] = max(lazymx[o], x);
	lazymi[o] = min(lazymi[o], x);
	mxans[o] = max(mxans[o], max(mx[o] - x, x - mi[o]));
}

inline void pushdown(int o) {
	if(lazymx[o] != -1) {
		setlazy(o << 1, lazymx[o]);
		setlazy(o << 1 | 1, lazymx[o]);
		lazymx[o] = -1;
	}
	if(lazymi[o] != inf) {
		setlazy(o << 1, lazymi[o]);
		setlazy(o << 1 | 1, lazymi[o]);
		lazymi[o] = inf;
	}
}

inline void pushup(int o) {
	mx[o] = max(mx[o << 1], mx[o << 1 | 1]);
	mi[o] = min(mi[o << 1], mi[o << 1 | 1]);
	mxans[o] = max(mxans[o << 1], mxans[o << 1 | 1]);
}

inline void modify(int o, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(o, x), void();
	pushdown(o);
	int mid = l + r >> 1;
	if(ql <= mid) modify(o << 1, ql, qr, x, l, mid);
	if(mid < qr) modify(o << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(o);
}

inline void modify(int o, int p, int op, int l, int r) {
	if(l == r) {
		if(op == -1) mi[o] = inf, mx[o] = 0;
		else mi[o] = mx[o] = a[l];
		return;
	}
	pushdown(o);
	int mid = l + r >> 1;
	if(p <= mid) modify(o << 1, p, op, l, mid);
	else modify(o << 1 | 1, p, op, mid + 1, r);
	pushup(o);
}

inline void build(int o, int l, int r) {
	mi[o] = inf, mx[o] = 0, mxans[o] = -1;
	lazymx[o] = -1;
	lazymi[o] = inf;
	if(l == r) return;
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}

inline int query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return mxans[o];
	pushdown(o);
	int mid = l + r >> 1;
	int res = -1;
	if(ql <= mid) res = max(res, query(o << 1, ql, qr, l, mid));
	if(mid < qr) res = max(res, query(o << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i] >> l[i] >> r[i], bdj[i+l[i]].pb(i), bdj[i+r[i]+1].pb(-i);
	cin >> q;
	rep(i, 1, q) {
		int l, r; cin >> l >> r;
		adj[r].emplace_back(l, i);
	}
	
	build(1, 1, n);

	rep(i, 1, n) {
		for(int j : bdj[i]) {
			if(j > 0) modify(1, j, 1, 1, n);
			else modify(1, -j, -1, 1, n);
		}
		if(i-l[i] >= 1) modify(1, i-r[i], i-l[i], a[i], 1, n);
		for(auto [j, id] : adj[i]) ans[id] = query(1, j, i, 1, n);
	}

	rep(i, 1, q) cout << ans[i] << "\n";
	
	return 0;
}

```

---

## 作者：Mirasycle (赞：1)

很巧妙的一个线段树配合扫描线维护信息的题目。

发现 $i,j$ 对称，不妨假设我们要求的是 $i<j$。

可以直接对于询问进行扫描线，扫 $j$，线段树维护 $i$ 位置处的答案。

在扫描线扫到 $i+l_i$ 时标记 $i$ 可用，在扫到 $i+r_i+1$ 时标记为不可用。只需要在扫描线扫到对应位置的时候插入删除即可。

然后对于每个 $j$ 在 $[j-r_j,j-l_j]$ 中为 $i$ 的可能集合。于是我们用 $a_j$ 在线段树上区间更新即可，线段树上维护 $\lvert a_j-a_i\rvert$ 的最大值。

实现方法是我们在线段树上维护五个标记 $mx,mn,tmx,tmn,A$ 前两个表示区间 $a_i$ 的最大最小值，中间两个表示区间 $a_j$ 的最大最小值，最后一个表示区间的答案。一定要注意 $i,j$ 要分开来维护，不能混用。每次就用 $mx-tmn$ 和 $tmx-mn$ 来更新答案即可。

上面还提到了 $a_i$ 的插入与删除，其实做法就是把单点修改 $mx\gets 0$，$mn\gets -\infty$。

时间复杂度 $O((n+m)\log n)$。

---

