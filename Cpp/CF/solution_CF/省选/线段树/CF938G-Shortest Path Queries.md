# Shortest Path Queries

## 题目描述

You are given an undirected connected graph with weighted edges. The length of some path between two vertices is the bitwise xor of weights of all edges belonging to this path (if some edge is traversed more than once, then it is included in bitwise xor the same number of times).

There are three types of queries you have to process:

- $ 1 $ $ x $ $ y $ $ d $ — add an edge connecting vertex $ x $ to vertex $ y $ with weight $ d $ . It is guaranteed that there is no edge connecting $ x $ to $ y $ before this query;
- $ 2 $ $ x $ $ y $ — remove an edge connecting vertex $ x $ to vertex $ y $ . It is guaranteed that there was such edge in the graph, and the graph stays connected after this query;
- $ 3 $ $ x $ $ y $ — calculate the length of the shortest path (possibly non-simple) from vertex $ x $ to vertex $ y $ .

Print the answers for all queries of type $ 3 $ .

## 样例 #1

### 输入

```
5 5
1 2 3
2 3 4
3 4 5
4 5 6
1 5 1
5
3 1 5
1 1 3 1
3 1 5
2 1 5
3 1 5
```

### 输出

```
1
1
2
```

# 题解

## 作者：p_b_p_b (赞：23)

[$$\large \color{purple} My\; Blog$$](https://www.cnblogs.com/p-b-p-b/p/10358109.html)

----------

分治的题目，或者说分治的思想，是非常灵活多变的。

~~所以对我这种智商低的选手特别不友好~~

脑子不好使怎么办？多做题吧……

---------------

## 前置知识

线性基是你必须会的，不然这题不可做。

推荐再去看看洛谷P4151。

--------

## 思路

看到异或最短路，显然线性基。

做题多一些的同学想必已经想到了“洛谷P4151 [WC2011]最大XOR和路径”了。

先考虑没有加边删边的做法：

1. 做出原图的任意一棵生成树；
2. 把每个非树边和树边形成的环丢进线性基里；
3. 询问时把两点在树上的路径异或和丢进线性基里求最小异或和。

为什么要这样？见洛谷P4151题解。

有加边呢？

其实差不了多少……加一条边就往线性基里丢个环就好了。

还有删边呢？

我们按时间分治，用线段树存储每一段新加了哪些边。

每到一个点，把边都连上，然后分治左右。退出时撤销即可。

然而此时图可能不连通，连边可能连了两棵不同的树，此时需要用可撤销并查集存储树的结构和每一个点到根的异或和。由于异或有着很好的性质，我们可以把两点连边改为两棵树的根连边，而答案不变。

然后就做完了~

-----------

## 代码

```cpp
#include<bits/stdc++.h>
namespace my_std{
	using namespace std;
	#define pii pair<int,int>
	#define fir first
	#define sec second
	#define MP make_pair
	#define rep(i,x,y) for (int i=(x);i<=(y);i++)
	#define drep(i,x,y) for (int i=(x);i>=(y);i--)
	#define go(x) for (int i=head[x];i;i=edge[i].nxt)
	#define sz 202020
	typedef long long ll;
	template<typename T>
	inline void read(T& t)
	{
		t=0;char f=0,ch=getchar();
		double d=0.1;
		while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
		while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
		if(ch=='.')
		{
			ch=getchar();
			while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();
		}
		t=(f?-t:t);
	}
	template<typename T,typename... Args>
	inline void read(T& t,Args&... args){read(t); read(args...);}
	void file()
	{
		#ifndef ONLINE_JUDGE
		freopen("a.txt","r",stdin);
		#endif
	}
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int n,m,Q;
map<pii,int>M;
struct hh{int f,t,w;hh(int ff=0,int tt=0,int ww=0){f=ff,t=tt,w=ww;}}edge[sz<<1];
int bg[sz<<1],ed[sz<<1];

struct HH
{
	int w[34];
	void ins(int x)
	{
		drep(i,30,0) if (x&(1<<i))
		{
			if (!w[i]) return (void)(w[i]=x);
			x^=w[i];
		}
	}
	int query(int x){ drep(i,30,0) if ((x^w[i])<x) x^=w[i]; return x; }
}_;

vector<hh>v[sz<<2];
#define ls k<<1
#define rs k<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
void insert(int k,int l,int r,int x,int y,hh e)
{
	if (x<=l&&r<=y) return (void)v[k].push_back(e);
	int mid=(l+r)>>1;
	if (x<=mid) insert(lson,x,y,e);
	if (y>mid) insert(rson,x,y,e);
}
int qx[sz],qy[sz];
int fa[sz],f[sz],dep[sz];
int getfa(int x){return x==fa[x]?x:getfa(fa[x]);}
int getdis(int x){return x==fa[x]?0:f[x]^getdis(fa[x]);}
struct hhh{int x,y;bool s;};
void solve(int k,int l,int r,HH G)
{
	stack<hhh>S;
	rep(i,0,(int)v[k].size()-1)
	{
		int x=v[k][i].f,y=v[k][i].t,w=v[k][i].w;
		int fx=getfa(x),fy=getfa(y);
		w^=getdis(x)^getdis(y);
		if (fx==fy) G.ins(w);
		else
		{
			if (dep[fx]>dep[fy]) swap(fx,fy),swap(x,y);
			hhh cur=(hhh){fx,fy,0};
			fa[fx]=fy;f[fx]=w;
			if (dep[fx]==dep[fy]) ++dep[fy],cur.s=1;
			S.push(cur);
		}
	}
	if (l==r) printf("%d\n",G.query(getdis(qx[l])^getdis(qy[l])));
	else
	{
		int mid=(l+r)>>1;
		solve(lson,G);solve(rson,G);
	}
	while (!S.empty()) f[fa[S.top().x]=S.top().x]=0,dep[S.top().y]-=S.top().s,S.pop();
}

int main()
{
	file();
	int x,y,z;
	read(n,m);
	rep(i,1,n) fa[i]=i;
	int c=m,tim=1;
	rep(i,1,m) read(x,y,z),M[MP(x,y)]=i,bg[i]=1,ed[i]=-1,edge[i]=hh(x,y,z);
	read(Q);
	rep(i,1,Q)
	{
		read(z,x,y);
		if (z==1)
		{
			read(z);
			M[MP(x,y)]=++c;bg[c]=tim;ed[c]=-1;
			edge[c]=hh(x,y,z);
		}
		else if (z==2) ed[M[MP(x,y)]]=tim-1;
		else qx[tim]=x,qy[tim]=y,++tim;
	}
	--tim;
	rep(i,1,c) if (ed[i]==-1) ed[i]=tim;
	rep(i,1,c) if (bg[i]<=ed[i]) insert(1,1,tim,bg[i],ed[i],edge[i]);
	solve(1,1,tim,_);
	return 0;
}
```



---

## 作者：zhiyangfan (赞：9)

## CF938G Shortest Path Queries
> 给出 $n$ 个点 $m$ 条边 的边带权连通无向图，和 $q$ 次操作：
> - 加入一条 $x,y$ 之间的边，边权为 $z$，保证之前这条边不存在。
> - 删去 $x,y$ 之间的边，保证这条边存在，且删去后原图仍然连通。
> - 询问 $x,y$ 之间的异或最短路径，路径不一定是简单路径。
>
> ($1\le n,m,q\le 2\times10^5,0\le z<2^{30}$)

注意到本题的路径不一定是简单路径，且路径算权值是异或算的，所以可以发现，我们可以不花费任何代价拿到一个环，因为我们可以从当前走的道路分叉去那个环，然后绕着环转一圈后原路返回，除了环的多余边都会走两次从而被消去。所以我们可以任意找一条路径，然后用一些环来增广它。（能任意找路径是因为，假如路径 $1$ 比路径 $2$ 更优，那选择这两条路径构成的环即可交换过去）所以现在我们的问题转化为了三个部分：
- 找到所有环，并能查询两点之间的任意一条异或路径。
- 查询某个集合内的值与某个值的异或最小值。
- 删除集合内的值。

对于找环，考虑找出原连通图的某个生成树，对于新加入的边，就在生成树上找到对应的环，将它的权值加入集合中。可以证明这样能组合出任何的环，感性证明：
- 对于仅由一条非树边构成的环，已经被记录了。
- 对于由多条非树边构成的环，将这些树边在生成树上的构成的环异或组合起来就能得到。

这个过程可以用一个带权并查集实现，顺便也能支持查询异或路径。

然后我们要知道线性基怎么查询和某个值的异或最小值。类似异或最大值，考虑从高位到低位贪心，能消掉这一位的 $1$ 就消掉这一位的 $1$，最终得到的答案即异或最小值。

最后，也是本题的难点，就是删除集合内的值了。有一种黑科技可以在 $\mathcal{O}(\log z+n)$ 的时间复杂度内修改集合内元素（其中 $n$ 是集合元素个数），当 $n,\log z$ 同阶时，这种做法非常好用。（具体可以看我一道非常类似的题 [P3733 [HAOI2017]八纵八横](https://www.luogu.com.cn/problem/P3733) 的题解）但本题中，$n$ 远大于 $\log z$，所以我们只能用另一种方法，线段树分治。

线段树分治可以用来解决一类 DS 的删除问题，这类 DS 支持加入，支持撤销，但很难支持删除。（注意区分删除和撤销）考虑预处理出每条边的存在区间，并把这些区间挂到线段树上，之后访问整棵线段树，每进入一个结点就加入这个结点对应的边，到叶子时，如果有询问就回答询问。离开一个结点时，把在这个结点进行一切操作撤销即可。（可以用个栈记录都干了点啥）再上个 `std::bitset` 优化一下，时间复杂度 $\mathcal{O}(\frac{q\log^2 z\log q}{w}+n\log n)$。
```cpp
#include <cstdio>
#include <bitset>
#include <vector>
#include <cstring>
#include <unordered_map>
const int N = 5e5 + 10, L = 31; typedef std::bitset<L> bs;
std::unordered_map<int, int> mp[N]; int sta[N], top;
struct edge{ int x, y; bs z; edge(int x = 0, int y = 0, bs z = 0) : x(x), y(y), z(z) { } }E[N];
struct query{ int x, y; }Q[N];
struct Linear_basis
{
    bs c[L]; int st[N], tp;
    inline void insert(bs x)
    {
        for (int i = L - 1; ~i; --i)
        {
            if (!x[i]) continue;
            if (c[i].none()) { st[++tp] = i; c[i] = x; break; }
            x ^= c[i];
        }
    }
    inline bs query(bs x)
    {
        bs ret = x;
        for (int i = L - 1; ~i; --i)
            if (ret[i] && c[i].any()) ret ^= c[i];
        return ret;
    }
    inline void del(int pos) { while (tp != pos) c[st[tp--]].reset(); }
}lb;
struct DSU
{
    int f[N], size[N], tp; bs dis[N];
    struct mem{ int x, y, s; mem(int x = 0, int y = 0, int s = 0) : x(x), y(y), s(s) { } }st[N];
    void init(int n) { for (int i = 1; i <= n; ++i) f[i] = i, size[i] = 1; }
    int getf(int x) { return x == f[x] ? x : getf(f[x]); }
    bs getdis(int x) { return x == f[x] ? dis[x] : dis[x] ^ getdis(f[x]); }
    inline void merge(int x, int y, bs w)
    {
        int t1, t2;
        if ((t1 = getf(x)) == (t2 = getf(y))) return lb.insert(getdis(x) ^ getdis(y) ^ w);
        if (size[t1] > size[t2]) std::swap(t1, t2); 
        st[++tp] = mem(t1, t2, size[t2]); dis[t1] = getdis(x) ^ getdis(y) ^ w;
        size[t2] += size[t1]; f[t1] = t2;
    }
    inline void del(int pos) { while (tp != pos) f[st[tp].x] = st[tp].x, size[st[tp].y] = st[tp].s, dis[st[tp--].x].reset(); }
}dsu;
struct SegTee
{
    #define ls(k) (k << 1)
    #define rs(k) (k << 1 | 1)
    struct node{ int l, r; std::vector<edge> e; }h[N << 2];
    void build(int k, int l, int r)
    {
        h[k].l = l; h[k].r = r; if (l == r) return ;
        int mid = (l + r) >> 1; build(ls(k), l, mid); build(rs(k), mid + 1, r);
    }
    void change(int k, int x, int y, edge v)
    {
        if (x <= h[k].l && h[k].r <= y) return h[k].e.emplace_back(v), void();
        int mid = (h[k].l + h[k].r) >> 1; 
        if (x <= mid) change(ls(k), x, y, v);
        if (mid < y) change(rs(k), x, y, v);
    }
    void query(int k)
    {
        int mem1 = lb.tp, mem2 = dsu.tp;
        for (auto d : h[k].e) dsu.merge(d.x, d.y, d.z);
        if (h[k].l == h[k].r && Q[h[k].l].x) 
        {
            int u = Q[h[k].l].x, v = Q[h[k].l].y;
            int z = (lb.query(dsu.getdis(u) ^ dsu.getdis(v))).to_ulong();
            printf("%d\n", z);
        }
        else if (h[k].l != h[k].r) query(ls(k)), query(rs(k));
        lb.del(mem1); dsu.del(mem2);
    }
}sgt;
int main()
{
    int n, m; scanf("%d%d", &n, &m); memset(sta, -1, sizeof (sta)); dsu.init(n);
    for (int i = 1, x, y, z; i <= m; ++i) 
        scanf("%d%d%d", &x, &y, &z), E[++top] = edge(x, y, z), sta[top] = 0, mp[x][y] = mp[y][x] = top;
    int q; scanf("%d", &q); sgt.build(1, 0, q);
    for (int i = 1, opt, x, y, z, id; i <= q; ++i)
    {
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1) scanf("%d", &z), E[++top] = edge(x, y, z), sta[top] = i, mp[x][y] = mp[y][x] = top;
        else 
        {
            if (opt == 2) id = mp[x][y], sgt.change(1, sta[id], i - 1, E[id]), sta[id] = -1;
            else Q[i].x = x, Q[i].y = y;
        }
    }
    for (int i = 1; i <= top; ++i) if (~sta[i]) sgt.change(1, sta[i], q, E[i]);
    sgt.query(1); return 0;
}
```

---

## 作者：Wen_kr (赞：7)

## 前置芝士 I : 线性基

一组数的线性基是另一组数 $a_1,a_2,a_3,a_4,\dots,a_n$ 其中 $a_x$ 最高位的 1 在 $x$ 位，这些数异或出的值域与原来的一组数相同。

在这道题里，显然一条边是不能重复走的，因为重复走就等价于不走，因此我们把每个环提出来构造线性基(显然每走一次值就可以异或这个环边权的异或和).

### 线性基的构造

对于一个数 $a_i$，我们尝试让它加入线性基，从高位到低位判断，若 $a_i$ 的二进制下第 $k$ 位为 $1$，我们则查看线性基的第 $k$ 位是否有值，若有，我们让 $a_i$ 异或上 $a_k$ 否则直接让 $a_k$ = $a_i$。

实现代码如下：

```cpp
for(int j = 30;j >= 0; -- j)
	if(w & (1 << j))
		if(base[dep][j] == 0)
		{
			base[dep][j] = w;
			for(int k = 30;k > j; -- k)
				if(base[dep][k] & (1 << j)) base[dep][k] ^= w;
			break;
		}
		else w ^= base[dep][j];
```

代码中 $w$ 就是要插入的数。

然后我们就可以把询问拿出来分治，对于每条边处理出它存在的时间 $[s,t]$，设当前分治到 $[l,r]$ 区间，若 $s \leq l,r \leq t$ 就把这条边加进去，这个过程可以用可撤销并查集实现。

## 前置芝士 II : 可撤销并查集

我们知道，路径压缩并查集是不能撤销的，要实现可撤销并查集，我们首先处理出每个节点的 $sz$，在合并时直接把 $sz$ 小的接到 $sz$ 大的即可。

这样做看似时间复杂度很大，实则均摊 $log n$ (笔者并没有严格证明过这个复杂度，也许会更小或更大)

在合并两个点时，将儿子节点压入栈，撤销时直接把儿子节点的贡献删除即可。

然后这道题就解决啦~

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct edge
{
	int u,v,w,x,y;
}e[400050];

vector<edge> g[800050];
map<pair<int,int>,int> mp;
int val[200050],fa[200050],sz[200050];
int stk[400050],top;

void Update(int rt,int l,int r,edge a)
{
	if(a.x > a.y) return ;
	if(l > r || l > a.y || r < a.x) return ;
	if(a.x <= l && r <= a.y)
	{
		g[rt].push_back(a);
		return ;
	}
	if(l == r) return ;
	int mid = (l + r) >> 1;
	Update(rt << 1,l,mid,a);
	Update(rt << 1 | 1,mid + 1,r,a);
}

int find_fa(int rt)
{
	return fa[rt] == rt ? rt : find_fa(fa[rt]);
}

int find_val(int rt)
{
	return fa[rt] == rt ? 0 : val[rt] ^ find_val(fa[rt]);
}

int base[75][35];

void ins(int k,int dep)
{
	for(int i = 0;i < g[k].size(); ++ i)
	{
		edge e = g[k][i];
		int u = e.u,v = e.v,w = e.w,x = u,y = v;
		u = find_fa(u); v = find_fa(v);
		if(u != v)
		{
			if(sz[u] > sz[v]) swap(u,v),swap(x,y);
			fa[u] = v;
			sz[v] += sz[u];
			val[u] = 0;
			val[u] = find_val(x) ^ find_val(y) ^ w;
			stk[++ top] = u;
		}
		else
		{
			w = find_val(x) ^ find_val(y) ^ e.w;
			for(int j = 30;j >= 0; -- j)
				if(w & (1 << j))
					if(base[dep][j] == 0)
					{
						base[dep][j] = w;
						for(int k = 30;k > j; -- k)
							if(base[dep][k] & (1 << j)) base[dep][k] ^= w;
						break;
					}
					else w ^= base[dep][j];
		}
	}
}

void reset(int to)
{
	while(top > to)
	{
		int u = stk[top --];
		sz[fa[u]] -= sz[u];
		val[u] = 0;
		fa[u] = u;
	}
}

struct qqq
{
	int u,v;
}qst[200050];

void solv(int k,int l,int r,int dep)
{
	if(l > r) return ;
	int tmp = top;
	ins(k,dep);
	if(l == r)
	{
		int x = qst[l].u,y = qst[l].v;
		int ans = find_val(x) ^ find_val(y);
		for(int i = 30;i >= 0; -- i)
			if(base[dep][i])
				ans = min(ans,ans ^ base[dep][i]);
		printf("%d\n",ans);
		reset(tmp);
		return ;
	}
	int mid = (l + r) >> 1;
	for(int i = 0;i <= 30; ++ i) base[dep + 1][i] = base[dep][i];
	solv(k << 1,l,mid,dep + 1);
	for(int i = 0;i <= 30; ++ i) base[dep + 1][i] = base[dep][i];
	solv(k << 1 | 1,mid + 1,r,dep + 1);
	reset(tmp);
}

int n,m,q;

int main()
{
	scanf("%d%d",&n,&m);
	int totq = 0,ecnt = 0;
	for(int i = 1;i <= m; ++ i)
	{
		ecnt ++;
		int u,v,w; scanf("%d%d%d",&u,&v,&w);
		e[ecnt] = (edge){u,v,w,1,-1};
		mp[make_pair(u,v)] = ecnt;
	}
	scanf("%d",&q);
	for(int i = 1;i <= q; ++ i)
	{
		int op,x,y,d;
		scanf("%d",&op);
		if(op == 1)
		{
			scanf("%d%d%d",&x,&y,&d);
			e[++ ecnt] = (edge){x,y,d,totq + 1,-1};
			mp[make_pair(x,y)] = ecnt;
		}
		else
		{
			scanf("%d%d",&x,&y);
			if(op == 2)
			{
				e[mp[make_pair(x,y)]].y = totq;
				mp[make_pair(x,y)] = 0;
			}
			else
			{
				qst[++ totq] = (qqq){x,y};
			}
		}
	}
	for(int i = 1;i <= ecnt; ++ i) if(e[i].y == -1) e[i].y = totq;
	for(int i = 1;i <= ecnt; ++ i) Update(1,1,totq,e[i]);
	for(int i = 1;i <= n; ++ i) fa[i] = i,sz[i] = 1;
	solv(1,1,totq,0);
}
```

---

## 作者：Kinandra (赞：6)

1. 标签: 线性基, 线段树分治, 按秩合并的并查集.
2. 首先不考虑删除的情况, 并且认为图是一棵**树**, 我们用并查集来维护每个点 $x$ 到根节点(即并查集祖先)的路径的值 $w_x$, 根据异或的性质, 易知两点 $x,y$ 距离等于 $w_x$ xor $w_y$.
3.  若图不是一棵树, 即我们加入某条边$(x, y, d)$ 的时候 $x, y$ 可能已经在同一个并查集内了, 那么我们加入这条边时会产生一条长度为 $w_x$ xor $w_y$ xor $d$ 的一个环, 我们发现如果从某个起点走到某个环上, 然后走一遍这个环, 再走回起点, 我们长度会 xor 上一个环长 $w$, 且起点不变. 于是我们想到将环的长度放入线性基内, 查询时先查出两点在树上路径的长度, 然后在线性基上跑最小值就好了.
4. 由于上述做法不支持删除操作, 我们想到使用线段树分治来避免删除操作, 注意到路径压缩并查集插入一条边可能会导致多个点保存的信息(父亲节点, 到父亲节点的距离)改变, 所以这里应当使用**按秩合并的并查集**(注意不要误认为是**可持久化并查集**, 如果使用可持久化并查集时间复杂度是 $\mathcal O(n\log^3n)$ 的, 空间复杂度是$\mathcal O(n\log^2n)$的, 代码复杂度是$\mathcal O($**炒鸡难打**$)$的), 那么插入一条边时保证只会改变两个点的信息(其实这两的点改变的信息互不相交, 可以看成只改变了一个点的信息).

```cpp
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
int read();
int n, m, q, cnt, ecnt, pcnt;
map<int, int> mp[200005];

struct Edge {
    int x, y, l, r, w;
    void init(int xx, int yy, int d, int L) { x = xx, y = yy, w = d, l = L; }
} e[400005];

struct P {
    int x, y;
};
vector<P> vp[200005];

struct liner_Base {
    int b[31];
    void ins(int w) {
        for (int i = 29; i >= 0; --i) {
            if (!(w >> i)) continue;
            if (!b[i]) {
                b[i] = w;
                break;
            }
            w ^= b[i];
        }
    }
    int work(int w) {
        for (int i = 29; i >= 0; --i) {
            if (!((w >> i) & 1)) continue;
            w ^= b[i];
        }
        return w;
    }
} lb[20];

struct T {
    int fa, w, sz;
};

struct Dsu {
    T t[200005];
    int find(int x, int &w) {
        while (x != t[x].fa) w ^= t[x].w, x = t[x].fa;
        return x;
    }
    void merge(int x, int y, int w, int id) {
        if (x == y) return lb[id].ins(w);
        if (t[x].sz > t[y].sz) swap(x, y);
        t[x].fa = y, t[x].w = w, t[y].sz += t[x].sz;
    }

    int qry(int x, int y, int id) {
        int w = 0;
        find(x, w), find(y, w);
        int t;
        return lb[id].work(w);
    }
} dsu;

int ppcnt;

struct Seg {
    vector<Edge> te[800005];
    void ins_edge(int l, int r, int k, Edge &e) {
        if (e.l > r || e.r < l) return;
        if (e.l <= l && e.r >= r) return ++ppcnt, te[k].push_back(e);
        int mid = l + r >> 1;
        ins_edge(l, mid, k << 1, e), ins_edge(mid + 1, r, k << 1 | 1, e);
    }

    T stt[800005];
    int st[800005], tag[20], top;

    void ins(int k, int d) {
        lb[d] = lb[d - 1], tag[d] = top;
        for (int i = 0; i < te[k].size(); ++i) {
            int x = te[k][i].x, y = te[k][i].y, wx = 0, wy = 0;
            x = dsu.find(x, wx), y = dsu.find(y, wy);
            st[++top] = x, stt[top] = dsu.t[x];
            st[++top] = y, stt[top] = dsu.t[y];
            dsu.merge(x, y, wx ^ wy ^ te[k][i].w, d);
        }
    }

    void del(int d) {
        while (top > tag[d]) dsu.t[st[top]] = stt[top], top--;
    }

    void work(int l, int r, int k, int d) {
        ins(k, d);
        if (l == r) {
            for (int i = 0; i < vp[l].size(); ++i)
                printf("%d\n", dsu.qry(vp[l][i].x, vp[l][i].y, d));
            return del(d);
        }
        int mid = l + r >> 1;
        work(l, mid, k << 1, d + 1), work(mid + 1, r, k << 1 | 1, d + 1);
        del(d);
    }
} seg;

int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i) dsu.t[i] = (T){i, 0, 1};
    for (int i = 1, x, y; i <= m; ++i)
        x = read(), y = read(),
        e[mp[x][y] = mp[y][x] = i].init(x, y, read(), 1);
    q = read();
    ecnt = m, cnt = 1;
    for (int i = 1, op, x, y; i <= q; ++i) {
        op = read(), x = read(), y = read();
        if (op == 1) e[mp[x][y] = mp[y][x] = ++ecnt].init(x, y, read(), ++cnt);
        if (op == 2) e[mp[x][y]].r = cnt++;
        if (op == 3) vp[cnt].push_back((P){x, y});
    }
    for (int i = 1; i <= ecnt; ++i) {
        if (!e[i].r) e[i].r = cnt;
        seg.ins_edge(1, cnt, 1, e[i]);
    }
    seg.work(1, cnt, 1, 1);
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```


---

## 作者：juju527 (赞：3)

**算法与数据结构：线段树分治+按秩合并+线性基**

### 前置问题

> 这是线性基的一个基本应用

**[[WC2011]最大XOR和路径](https://www.luogu.com.cn/problem/P4151)**

### solution

先不考虑$1,2$操作，那么该题与前置问题只有最大和最小的一点区别

具体做法可以用并查集维护一棵生成树，每成一个环，把环丢进线性基里

这个做法的正确性利用了异或的优秀性质，可以去前置问题详细学习

考虑$1$操作加边，我们做法不变

考虑$2$操作删边，我们知道线性基是不支持删除的，并查集想支持删除一定要用按秩合并

线性基不支持删除怎么办

我们换一个角度来看待此题

不难发现每一条边都出现了**一段时间**，然后被删除

我们由于应避免线性基需要删除操作，考虑**线段树分治**

线段树分治是一种与时间有关的优秀的离线算法

可以去[blog](https://juju527.blog.luogu.org/solution-p4585)学习一下

### 并查集部分的实现
由于并查集经常用来维护一个图的各种奇怪联通/距离问题，按秩合并也是删边有关并查集的唯一选择

蒟蒻我一直不太会用按秩合并，这里讲解一下按秩合并的实现
```cpp
int update(int k,int *p){
	int siz=0;
	for(int i=0;i<upd[k].size();i++){
		int id=upd[k][i];//加边操作编号
		int u=e[id].x,v=e[id].y;//边的两端点
		int x=find(u),y=find(v),d=e[id].d;
		d^=(getd(u)^getd(v));//在后面会提到
		if(rk[x]>rk[y])swap(x,y);//按秩合并
		if(x!=y){
			tp++;
			px[tp]=x;//在栈里存储信息以便撤销操作
			pd[tp]=dis[x];dis[x]=d;
			f[x]=y;
			pr[tp]=rk[y];
			if(rk[x]==rk[y])rk[y]++;//按秩合并
			siz++;
		}
		else
			ins(d,p);
	}
	return siz;
}

```
由于我们并查集并没有按原图连边

记$x,y$分别为$u,v$的祖先节点，对于一条边$(u,v,w)$，在并查集上会变成$(x,y)$

![](https://s1.ax1x.com/2020/06/10/tTOZnI.png)

记$d_i$表示$i$点到祖先的异或距离

$(x,y)$之间的权值应为$d_u\bigoplus d_v\bigoplus w$

该操作能使任意$d_i$计算无误

上图应该画得很清楚了，不再赘述

### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5,maxm=2e5+5,maxq=2e5+5;
struct edge{
	int x,y,d;
}e[maxm+maxq];
int len=0;
int s[maxn+maxq],t[maxn+maxq];
int q[maxq][3];
int f[maxn],rk[maxn],dis[maxn];
int ans[maxq];
map<long long,int>mp;
vector<int>upd[maxq<<2];
vector<int>que[maxq<<2];
int read(){
    int x=0,y=1;
    char ch=getchar();
    while(ch<48||ch>57){if(ch==45)y=-1;ch=getchar();}
    while(ch>=48&&ch<=57)x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*y;
}
void modify1(int k,int l,int r,int x,int y,int id){
	if(l>y||r<x)return ;
	if(l>=x&&r<=y){
		upd[k].push_back(id);
		return ;
	}
	int mid=l+((r-l)>>1);
	modify1(k<<1,l,mid,x,y,id);
	modify1(k<<1|1,mid+1,r,x,y,id);
	return ;
}
void modify2(int k,int l,int r,int x,int id){
	if(l>x||r<x)return ;
	if(l==r){
		que[k].push_back(id);
		return ;
	}
	int mid=l+((r-l)>>1);
	modify2(k<<1,l,mid,x,id);
	modify2(k<<1|1,mid+1,r,x,id);
	return ;
}
void ins(int x,int *p){
	for(int i=29;i>=0;i--){
		if(!x)return ;
		if(!(x&(1<<i)))continue;
		if(!p[i]){
			p[i]=x;
			return ;
		}
		x^=p[i];
	}
	return ;
}
int query(int val,int *p){
	int ans=val;
	for(int i=29;i>=0;i--)
		if((ans^p[i])<ans)
			ans^=p[i];
	return ans;
}
int find(int x){
	if(f[x]==x)return x;
	return find(f[x]);
}
int getd(int x){
	if(f[x]==x)return 0;
	return dis[x]^getd(f[x]);
}
int tp=0;
int px[maxn],pd[maxn],pr[maxn];
int update(int k,int *p){
	int siz=0;
	for(int i=0;i<upd[k].size();i++){
		int id=upd[k][i];
		int u=e[id].x,v=e[id].y;
		int x=find(u),y=find(v),d=e[id].d;
		d^=(getd(u)^getd(v));
		if(rk[x]>rk[y])swap(x,y);
		if(x!=y){
			tp++;
			px[tp]=x;
			pd[tp]=dis[x];dis[x]=d;
			f[x]=y;
			pr[tp]=rk[y];
			if(rk[x]==rk[y])rk[y]++;
			siz++;
		}
		else
			ins(d,p);
	}
	return siz;
}
void clear(int k,int siz){
	while(siz--){
		int x=px[tp],y=f[x];
		f[x]=x;
		dis[x]=pd[tp];
		rk[y]=pr[tp];
		tp--;
	}
	return ;
}
void solve(int k,int l,int r,int *p){
	int siz=update(k,p);
	if(l==r){
		for(int i=0;i<que[k].size();i++){
			int id=que[k][i];
			ans[id]=query(getd(q[id][1])^getd(q[id][2]),p);
		}
		clear(k,siz);
		return ;
	}
	int mid=l+((r-l)>>1);
	int h[30];
	for(int i=0;i<=29;i++)h[i]=p[i];
	solve(k<<1,l,mid,h);
	for(int i=0;i<=29;i++)h[i]=p[i];
	solve(k<<1|1,mid+1,r,h);
	clear(k,siz);
	return ;
}
int main(){
    freopen("CF938GShortestPathQueries.in","r",stdin);
    freopen("CF938GShortestPathQueries.out","w",stdout);
    long long n,m,qq;
	n=read();m=read();
	for(int i=1;i<=m;i++){
		long long x,y,d;
		x=read();y=read();d=read();
		if(x>y)swap(x,y);
		mp[x*n+y]=i;
		e[i].x=x;e[i].y=y;e[i].d=d;
		s[i]=1;
	}
	len=m;
	qq=read();
	int tim=1,Q=0;
	for(int i=1;i<=qq;i++){
		long long opt,x,y,d;
		opt=read();x=read();y=read();
		if(x>y)swap(x,y);
		if(opt==1){
			d=read();
			mp[x*n+y]=++len;
			e[len].x=x;e[len].y=y;e[len].d=d;
			s[len]=++tim;
		}
		else if(opt==2){
			int id=mp[x*n+y];
			t[id]=tim++;
		}
		else{
			Q++;
			q[Q][0]=tim;q[Q][1]=x;q[Q][2]=y;
		}
	}
	for(int i=1;i<=len;i++){
		if(!t[i])t[i]=tim;
		modify1(1,1,tim,s[i],t[i],i);
	}
	for(int i=1;i<=Q;i++)
		modify2(1,1,tim,q[i][0],i);
	for(int i=1;i<=n;i++)f[i]=i,dis[i]=0,rk[i]=1;
	int p[30];
	for(int i=0;i<=29;i++)p[i]=0;
	for(int i=1;i<=Q;i++)ans[i]=1<<30;
	solve(1,1,tim,p);
	for(int i=1;i<=Q;i++)
		printf("%d\n",ans[i]);
    return 0;
}

```

---

## 作者：gorokokoro (赞：2)

手打四百行然后直接过了，有点小激动。

考虑最小非空子集异或和的模型，建立出线性基取最小值即可。

如果硬点了选一个数 $x$，从线性基里提取，尽可能地把 $x$ 的 $1$ 消掉即可。

那么这里显然线段树分治一下，然后[照猫画虎](https://www.luogu.com.cn/problem/P4151)，分治的时候把所有的环都丢进线性基里，最后随便取一条路径作为初始值即可。

$\text{LCT}$ 维护。

复杂度 $\mathrm O(n\log^2n)$ 。

```cpp
#pragma GCC optimize("Ofast,inline,unroll-loops,fast-math")
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include <tuple>
#define N 200020
#define M 30
using namespace std;

class Linear
{
public:
    int f[M];

    Linear(void)
    {
        memset(f, 0, sizeof(f));

        return;
    }

    void InsertLinear(int x)
    {
        int i, j;

        for(i = M - 1; i > -1; i --)
            if(x & (1 << i))
            {
                if(f[i])
                {
                    x ^= f[i];
                    continue;
                }

                for(j = 0; j < i; j ++)
                    if(x & (1 << j))
                        x ^= f[j];
                for(j = i + 1; j < M; j ++)
                    if(f[j] & (1 << i))
                        f[j] ^= x;
                f[i] = x;
                break;
            }

        return;
    }
};

class Node
{
public:
    Node *s[2];
    Node *p;
    Node *q;
    int v;
    int x;
    bool f;

    Node(int _v = 0) : v(_v), x(_v), f(false)
    {
        s[0] = s[1] = p = q = NULL;

        return;
    }

    bool Relation(void)
    {
        return this == p -> s[1];
    }

    void Maintain(void)
    {
        x = v;
        if(s[0])
        {
            x ^= s[0] -> x;
            s[0] -> f ^= f;
        }
        if(s[1])
        {
            x ^= s[1] -> x;
            s[1] -> f ^= f;
        }
        if(f)
        {
            swap(s[0], s[1]);
            f = false;
        }

        return;
    }

    void Pushdown(void)
    {
        if(p)
            p -> Pushdown();
        Maintain();

        return;
    }
};

Node f[N];
vector<tuple<int, int, int> > g[N << 2];
pair<int, int> q[N << 2];
int o[N];

void RotateLCT(Node *x)
{
    Node *p;
    int k;

    p = x -> p;
    k = x -> Relation();

    x -> q = p -> q;
    p -> q = NULL;

    x -> p = p -> p;
    if(x -> p)
        x -> p -> s[p -> Relation()] = x;

    p -> s[k] = x -> s[!k];
    if(p -> s[k])
        p -> s[k] -> p = p;

    x -> s[!k] = p;
    p -> p = x;

    p -> Maintain();
    x -> Maintain();

    return;
}

void SplayLCT(Node *x)
{
    x -> Pushdown();
    while(x -> p)
        if(x -> p -> p)
        {
            if(x -> p -> Relation() == x -> Relation())
                RotateLCT(x -> p);
            else
                RotateLCT(x);
            RotateLCT(x);
        }
        else
            RotateLCT(x);

    return;
}

void ExposeLCT(Node *x)
{
    SplayLCT(x);
    if(x -> s[1])
    {
        x -> s[1] -> q = x;
        x -> s[1] -> p = NULL;
        x -> s[1] = NULL;
    }

    return;
}

bool SpliceLCT(Node *x)
{
    SplayLCT(x);
    if(!x -> q)
        return false;

    ExposeLCT(x -> q);
    x -> q -> s[1] = x;
    x -> p = x -> q;
    x -> q = NULL;

    return true;
}

void AccessLCT(Node *x)
{
    for(ExposeLCT(x); SpliceLCT(x); )
        ;

    return;
}

void EvertLCT(Node *x)
{
    AccessLCT(x);
    x -> f ^= 1;

    return;
}

Node *FindLCT(Node *x)
{
    AccessLCT(x);
    SplayLCT(x);
    for(; x -> s[0]; x = x -> s[0])
        ;
    SplayLCT(x);

    return x;
}

void LinkLCT(Node *x, Node *y)
{
    EvertLCT(x);
    x -> q = y;

    return;
}

void CutLCT(Node *x, Node *y)
{
    EvertLCT(x);
    AccessLCT(y);
    SplayLCT(x);
    if(x -> s[1] != y || x -> s[1] -> s[0])
    {
        // puts("while cutting");
        throw;
    }
    x -> s[1] -> p = NULL;
    x -> s[1] = NULL;

    return;
}

int XorLCT(Node *x, Node *y)
{
    EvertLCT(x);
    AccessLCT(y);
    SplayLCT(x);

    return x -> x;
}

void InsertSegment(int x, int l, int r, int s, int t, tuple<int, int, int> v)
{
    int m;

    if(l > t || r < s)
        return;
    if(l >= s && r <= t)
    {
        if(get<2>(v) == -1)
            q[x] = make_pair(get<0>(v), get<1>(v));
        else
            g[x].push_back(v);

        return;
    }

    m = (l + r) >> 1;
    InsertSegment(x << 1    , l    , m, s, t, v);
    InsertSegment(x << 1 | 1, m + 1, r, s, t, v);

    return;
}

void UndoSegment(vector<pair<Node *, bool> > &t, vector<tuple<int, int, int> > &g)
{
    int i;

    for(i = 0; i < (signed)t.size(); i ++)
        if(t[i].second)
        {
            // printf("cut %d-%d\n", get<0>(g[i]), get<1>(g[i]));
            CutLCT(&f[get<0>(g[i])], t[i].first);
            CutLCT(&f[get<1>(g[i])], t[i].first);
        }

    return;
}

void DFSSegment(int x, int l, int r, Linear h)
{
    int u, v, w;
    int i, m;
    vector<pair<Node *, bool> > t;

    for(i = 0; i < (signed)g[x].size(); i ++)
    {
        tie(u, v, w) = g[x][i];
        t.push_back(make_pair(new Node(w), true));
        if(FindLCT(&f[u]) == FindLCT(&f[v]))
        {
            h.InsertLinear(XorLCT(&f[u], &f[v]) ^ w);
            t.back().second = false;
        }
        else
        {
            LinkLCT(&f[u], t.back().first);
            LinkLCT(&f[v], t.back().first);
            // printf("linked %d-%d\n", u, v);
        }
    }

    if(l == r)
    {
        if(q[x].first)
        {
            tie(u, v) = q[x];
            // printf("ask %d-%d\n", u, v);
            if(FindLCT(&f[u]) != FindLCT(&f[v]))
                throw;
            w = XorLCT(&f[u], &f[v]);

            for(i = M - 1; i > -1; i --)
                if(w & (1 << i))
                    w ^= h.f[i];
            o[l] = w;
        }
        UndoSegment(t, g[x]);

        return;
    }

    m = (l + r) >> 1;
    DFSSegment(x << 1    , l    , m, h);
    DFSSegment(x << 1 | 1, m + 1, r, h);
    UndoSegment(t, g[x]);

    return;
}

int main(void)
{
    int n, m, u, v, w;
    int i;
    map<pair<int, int>, pair<int, int> > f;
    map<pair<int, int>, pair<int, int> >::iterator t;

    scanf("%d %d", &n, &m);
    while(m --)
    {
        scanf("%d %d %d", &u, &v, &w);
        if(u > v)
            swap(u, v);
        f[make_pair(u, v)] = make_pair(w, 0);
    }

    scanf("%d", &m);
    for(i = 1; i <= m; i ++)
    {
        scanf("%d %d %d", &w, &u, &v);
        if(u > v)
            swap(u, v);
        if(w == 1)
        {
            scanf("%d", &w);
            f[make_pair(u, v)] = make_pair(w, i);
        }
        else if(w == 2)
        {
            InsertSegment(1, 0, m, f[make_pair(u, v)].second, i - 1, make_tuple(u, v, f[make_pair(u, v)].first));
            f.erase(make_pair(u, v));
        }
        else
            InsertSegment(1, 0, m, i, i, make_tuple(u, v, -1));
    }
    for(t = f.begin(); t != f.end(); ++ t)
        InsertSegment(1, 0, m, t -> second.second, m, make_tuple(t -> first.first, t -> first.second, t -> second.first));

    memset(o, -1, sizeof(o));
    DFSSegment(1, 0, m, Linear());
    for(i = 1; i <= m; i ++)
        if(o[i] != -1)
            printf("%d\n", o[i]);

    return 0;
}

```

---

## 作者：Rorschachindark (赞：2)

# Shortest Path Queries
[题目传送门](https://www.luogu.com.cn/problem/CF938G)
## 前置知识
1. 按秩合并并查集

2. 线性基

3. 线段树分治

## 思路
$\ \ \ \ \ $ 如果你做过[P4151](https://www.luogu.com.cn/problem/P4151)可能会有些帮助，当然没做过也可以做。

$\ \ \ \ \ $ 考虑对于一个树怎么求出任意两个点的答案。我们可以用$dis[u]$记录$u$到根的权值异或和，然后对于$(u,v)$,答案就是$dis[u] \text { xor } dis[v]$。考虑如何拓展到联通无向图上，我们可以发现对于图上的一个环，我们如果从起点走这个环再走回起点，答案相当于异或上了这个环的异或和，于是我们就可以对于这个图上的每个环的异或和都提出来，丢进线性基里面，然后用$dis[u] \text { xor } dis[v]$去查询就好了。

$\ \ \ \ \ $ 回到这道题，这道题有一个神奇的东西就是每条边只会在某一段时间出现，熟悉套路的同学就不难想到使用线段树分治。我们直接按时间建一棵线段树，然后用按秩合并并查集维护一下树的形态的$\forall \text {u's } dis[u]$,再顺便求一下图中的环的异或和就好了。

$\ \ \ \ \ $ 这道题还是有一些比较$\text {naive}$的小技巧，就是线性基要每一层都建一个，因为你插入了数值之后就不好删除，而且在同一层内不同段的值两两不干扰，就没有什么问题了。
## $\text {Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 200005

int read ()
{
	int x = 0;char c = getchar();int f = 1;
	while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}
	while (c >= '0' && c <= '9'){x = (x << 3) + (x << 1) + c - '0';c = getchar();}
	return x * f;
}

void write (int x)
{
	if (x < 0){x = -x;putchar ('-');}
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
}

class Line_Base//线性基
{
	private:
		int b[31];
	public:
		void Insert (int w)
		{
			for (Int i = 29;i >= 0;-- i)
			{
				if (!(w >> i)) continue;
				if (!b[i])
				{
					b[i] = w;
					break;
				}
				w ^= b[i];
			}
		}
		int query (int w)
		{
			for (Int i = 29;i >= 0;-- i)
			{
				if (!((w >> i) & 1)) continue;
				w ^= b[i];
			}
			return w;
		}
}Lb[20]; 

struct T{int fa,w,size;};//按秩合并并查集的一个节点 

struct Dsu
{
	T t[MAXN];
	int findSet (int x,int &w)
	{
		while (x != t[x].fa) w ^= t[x].w,x = t[x].fa;
		return x;
	}
	void Merge (int x,int y,int w,int id)
	{
		if (x == y) return Lb[id].Insert (w);
		if (t[x].size > t[y].size) swap (x,y);
		t[x].fa = y,t[x].w = w,t[y].size += t[x].size; 
	}
	int query (int x,int y,int id)
	{
		int w = 0;
		findSet (x,w),findSet (y,w);
		return Lb[id].query (w);
	}
}dsu;

struct Node{int x,y;};

vector <Node> Que[MAXN];

struct Edge{int x,y,l,r,w;}e[MAXN << 1];

class Segment
{
	private:
		T stt[MAXN << 2];
		int top,tag[20],st[MAXN << 2];//tag是每一层原先的并查集中需要撤销的点的个数 
		vector <Edge> tree[MAXN << 2];
	public:
		void update (int k,int l,int r,Edge e)
		{
			if (l > e.r || e.l > r) return ;
			if (e.l <= l && r <= e.r) return tree[k].push_back (e);
			int mid = (l + r) >> 1; 
			update (k << 1,l,mid,e);
			update (k << 1 | 1,mid + 1,r,e);
		}
		void Insert (int k,int d)//k这个点，第d层 
		{
			Lb[d] = Lb[d - 1],tag[d] = top;
			for (Int i = 0;i < tree[k].size();++ i)
			{
				int x = tree[k][i].x,y = tree[k][i].y,wx = 0,wy = 0;
				x = dsu.findSet (x,wx),y = dsu.findSet (y,wy);
				st[++ top] = x,stt[top] = dsu.t[x];
				st[++ top] = y,stt[top] = dsu.t[y];
				dsu.Merge (x,y,wx ^ wy ^ tree[k][i].w,d);
			}
		}
		void Delete (int d)//对于d这一层进行并查集的撤销
		{
			while (top > tag[d]) dsu.t[st[top]] = stt[top],top --;
		} 
		void Divide (int k,int l,int r,int d)
		{
			Insert (k,d);
			if (l == r)
			{
				for (Int i = 0;i < Que[l].size();++ i)
					write (dsu.query (Que[l][i].x,Que[l][i].y,d)),putchar ('\n');
				return Delete (d);
			}
			int mid = (l + r) >> 1;
			Divide (k << 1,l,mid,d + 1);
			Divide (k << 1 | 1,mid + 1,r,d + 1);
			Delete (d);
		}
}Tree;

map <int,int> mp[MAXN];

signed main()
{
	int n = read (),m = read ();
	for (Int i = 1;i <= n;++ i) dsu.t[i] = T{i,0,1};
	for (Int i = 1;i <= m;++ i)
	{
		int u = read (),v = read (),w = read ();
		e[mp[u][v] = mp[v][u] = i] = Edge {u,v,1,0,w};
	}
	int q = read ();
	int ecnt = m,cnt = 1;
	for (Int i = 1;i <= q;++ i)
	{
		int type = read (),x = read (),y = read ();
		if (type == 1) e[mp[x][y] = mp[y][x] = ++ ecnt] = Edge {x,y,++ cnt,0,read ()};
		else if (type == 2) e[mp[x][y]].r = cnt ++;
		else Que[cnt].push_back (Node {x,y}); 
	}
	for (Int i = 1;i <= ecnt;++ i)
	{
		if (e[i].r == 0) e[i].r = cnt;
		Tree.update (1,1,cnt,e[i]);
	}
	Tree.Divide (1,1,cnt,1);
	return 0;
}
```

---

## 作者：lhm_ (赞：2)

题目让我们维护一个连通无向图，边有边权，支持加边删边和询问从$x$到$y$的异或最短路。

考虑到有删边这样的撤销操作，那么用线段树分治来实现，用线段树来维护询问的时间轴。

将每一条边的出现时间段标记到线段树上，表示在这一段询问中这条边存在。

异或最短路的处理方法与[最大XOR和路径](https://www.luogu.com.cn/problem/P4151)类似，给线段树上每个节点开一个线性基，找出当前所有的环，插入该节点的线性基，查询时任意找出一条从$x$到$y$的路径，到线性基中查询，即为答案。

具体实现时用可撤销并查集，采用按秩合并来优化，因为路径压缩会破坏树的结构。

具体实现细节看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 400010
using namespace std;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}
int n,m,q,num,tree_cnt,edge_cnt,root,top;
int ls[maxn],rs[maxn],pre[maxn],nxt[maxn],ans[maxn];
map<pair<int,int>,int> mp;
struct Edge
{
    int x,y,v;
}e[maxn];
struct node
{
    int x,y,deep;
}st[maxn];
struct query
{
    int x,y;
}qu[maxn];
void build(int l,int r,int &cur)
{
    if(!cur) cur=++tree_cnt;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(l,mid,ls[cur]);
    build(mid+1,r,rs[cur]);
}
vector<int> v[maxn];
void insert(int L,int R,int l,int r,int id,int cur)
{
    if(L<=l&&R>=r)
    {
        v[cur].push_back(id);
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid) insert(L,R,l,mid,id,ls[cur]);
    if(R>mid) insert(L,R,mid+1,r,id,rs[cur]);
}
int a[maxn][40];
void ins(int x,int cur)
{
    for(int i=30;i>=0;--i)
    {
        if(x&(1<<i))
        {
            if(!a[cur][i])
            {
                a[cur][i]=x;
                break;
            }
            else x^=a[cur][i];
        }
    }
}
int get(int x,int cur)
{
    for(int i=30;i>=0;--i)
        if((x^a[cur][i])<x)
            x^=a[cur][i];
    return x;
}
int fa[maxn],de[maxn],dis[maxn];
int find(int x)
{
    return fa[x]==x?x:find(fa[x]);
}
int xor_dis(int x)
{
    return fa[x]==x?dis[x]:dis[x]^xor_dis(fa[x]);
}
void merge(int x,int y,int v)
{
    if(de[x]<de[y]) swap(x,y);
    st[++top]=(node){x,y,de[x]};
    fa[y]=x,dis[y]=v,de[x]=max(de[x],de[y]+1);
}
void del(int id)
{
    int x=st[id].x,y=st[id].y;
    fa[y]=y,dis[y]=0,de[x]=st[id].deep;
}
void copy(int x,int y)
{
    for(int i=0;i<=30;++i) a[y][i]=a[x][i];
}
void dfs(int l,int r,int cur)
{
    int now=top,size=v[cur].size();
    for(int i=0;i<size;++i)
    {
        int id=v[cur][i],x=e[id].x,y=e[id].y,v=e[id].v;
        v^=xor_dis(x)^xor_dis(y),x=find(x),y=find(y);
        if(x==y) ins(v,cur);
        else merge(x,y,v);
    }
    if(l==r)
    {
        int x=qu[l].x,y=qu[l].y;
        ans[l]=get(xor_dis(x)^xor_dis(y),cur);
    }
    else
    {
        int mid=(l+r)>>1;
        copy(cur,ls[cur]),dfs(l,mid,ls[cur]);
        copy(cur,rs[cur]),dfs(mid+1,r,rs[cur]);
    }
    while(top>now) del(top--);
}
int main()
{
    read(n),read(m),edge_cnt=m;
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        read(e[i].x),read(e[i].y),read(e[i].v);
        mp[make_pair(e[i].x,e[i].y)]=i,pre[i]=1,nxt[i]=-1;
    }
    read(q);
    while(q--)
    {
        int opt,x,y,v;
        read(opt);
        if(opt==1)
        {
            read(x),read(y),read(v);
            e[++edge_cnt]=(Edge){x,y,v};
            mp[make_pair(x,y)]=edge_cnt;
            pre[edge_cnt]=num+1,nxt[edge_cnt]=-1;
        }
        if(opt==2)
        {
            read(x),read(y);
            nxt[mp[make_pair(x,y)]]=num;
        }
        if(opt==3)
        {
            read(x),read(y);
            qu[++num]=(query){x,y};
        }
    }
    build(1,num,root);
    for(int i=1;i<=edge_cnt;++i)
    {   
        if(nxt[i]<0) nxt[i]=num;
        if(pre[i]<=nxt[i]) insert(pre[i],nxt[i],1,num,i,root);
    }
    dfs(1,num,root);
    for(int i=1;i<=num;++i)
        printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：MikukuOvO (赞：1)

首先我们考虑原图中的一个环，在原来的路径基础上可以通过这个环来进行增广，而路径到这个环之间的权值由于异或两遍就没有贡献，所以我们不难发现如果我们对于$u$，$v$确定的任意路径，有意义的增广只有环，至于为什么是任意路径读者可以自行思考下。

那么这道题就不难了，我们考虑线段树分治，对于每一条边记录一个存活时间，压到线段树中，对于求两点之间的任意路径，我们可以用并查集维护，同时维护一下$u$到$fa_u$的权值，对于环我们压到线性基中即可。

代码：

```cpp
const int N=2e5+5;

struct edge
{
    int u,v,w;
};
struct node
{
    int x,y;
    bool operator<(const node&a)const
    {
        return (x==a.x)?y<a.y:x<a.x;
    }
};
struct rt
{
    int p[32];

    void insert(int x)
    {
        for(int i=29;i>=0;--i)
        {
            if(!((x>>i)&1)) continue;
            if(!p[i])
            {
                p[i]=x;
                break;
            }
            x^=p[i];
        }
    }
    int query(int x)
    {
        for(int i=29;i>=0;--i) if((x^p[i])<x) x^=p[i];
        return x;
    }
}sr;

int n,m,q,top,sig;
int anc[N],dis[N],d[N],be[N<<1],ed[N<<1];
int qu[N],qv[N];
edge e[N<<1];
vc<int>t[N<<2];
node stk[N<<4];
bool isq[N];
map<node,int>s;

void update(int x,int y,int l,int r,int i,int o)
{
    if(l>=x&&r<=y)
    {
        t[o].pub(i);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(x,y,l,mid,i,o<<1);
    if(y>mid) update(x,y,mid+1,r,i,o<<1|1);
}
void undo()
{
    int x=stk[top].x,y=stk[top].y;
    --top;
    d[anc[x]]-=y,anc[x]=x,dis[x]=0;
}
int find(int x)
{
    if(anc[x]==x) return x;
    return find(anc[x]);
}
int getdis(int x)
{
    if(anc[x]==x) return 0;
    return dis[x]^getdis(anc[x]);
}
void solve(int l,int r,int o,rt g)
{
    int num=top;
    for(auto i:t[o])
    {
        int u=e[i].u,v=e[i].v,w=e[i].w;
        int fx=find(u),fy=find(v);
        w^=getdis(u)^getdis(v);
        if(fx==fy) g.insert(w);
        else
        {
            if(d[fx]>d[fy]) swap(fx,fy);
            anc[fx]=fy,dis[fx]=w,d[fy]+=d[fx]==d[fy];
            stk[++top]={fx,d[fx]==d[fy]};
        }
    }
    if(l==r)
    {
        if(isq[l]) 
        {
            int t=getdis(qu[l])^getdis(qv[l]);
            print(g.query(t)),pc(10);
        }
    }
    else
    {
        int mid=(l+r)>>1;
        solve(l,mid,o<<1,g),solve(mid+1,r,o<<1|1,g);
    }
    while(top>num) undo();
}
int main()
{
    fio();
    gi(n,m);
    for(int i=1;i<=m;++i) gi(e[i].u,e[i].v,e[i].w);
    gi(q);
    for(int i=1;i<=m;++i) be[i]=1,ed[i]=q,s[{e[i].u,e[i].v}]=i;
    for(int i=1,op,x,y,z;i<=q;++i)
    {
        gi(op,x,y);
        if(op==1)
        {
            gi(z),++m;
            e[m].u=x,e[m].v=y,e[m].w=z;
            be[m]=i,ed[m]=q,s[{x,y}]=m;
        }
        else if(op==2) ed[s[{x,y}]]=i-1;
        else
        {
            isq[i]=true;
            qu[i]=x,qv[i]=y;
        }
    }
    for(int i=1;i<=m;++i) if(be[i]<=ed[i]) update(be[i],ed[i],1,q,i,1);
    for(int i=1;i<=n;++i) anc[i]=i;
    solve(1,q,1,sr);
    end();
}
```

---

## 作者：huayucaiji (赞：1)

# CF938G Shortest Path Queries

~~出现了!融合怪！~~

做本题之前建议先做掉 [最大XOR和路径](https://www.luogu.com.cn/problem/P4151) 和 [二分图](https://www.luogu.com.cn/problem/P5787) 两题。

~~其实这题就是这两题融合一下~~

我们来讲解法。首先我们看到了这个 XOR 的最小值问题，可以借鉴`最大XOR和路径`这道题的思路。其次我们有删边，加边的操作，可以用线段树分治的思路。但是很显然，这中间还有很多有待思考的问题。比如，如何实现线性基撤销？怎样合并边，并维护线性基？我们来一一攻破。

## 线性基撤销

这个我是没怎么好好想过，反正我是对于每个线段树上的节点都建了一个线性基，每次下传即可。挺暴力的，但是空间可以卡过的。

## 边的合并

我们可以这样想。如果此时两个点不在一个连通块里，我们可以在这两条边之间加一条边。但是这个违反了并查集的规则。并查集只能将两个集合的根节点合并。我们就需要用到`二分图`中的一个思路。比如说，如下图：

![1](http://image.qingtengbc.com/2021/03/12/808b079d953ad.png)

（由于绘图不支持 $\LaTeX$，所以下划线就标在那里了，不是图炸了）

我们现在要在 $2$ 和 $6$ 之间添一条边，权值为 $val_6$。我们应该得到下图：

![2](http://image.qingtengbc.com/2021/03/12/41a6d6b048e0c.png)

但是实际上我们不能这么做，我们的并查集只支持根节点合并。那么怎么办？我们令节点 $i$ 到它所属的并查集的根的距离为 $dis_i$。那么若我们连接 $u,v$ 两点，权值为 $w$，我们就相当于在这两个点分别所属的并查集的根节点连一条权值为 $dis_u \operatorname{xor} dis_v \operatorname{xor} w$ 的边。比如对于我们举的例子，就是这个效果：

![3](http://image.qingtengbc.com/2021/03/12/bbd1988f140d0.png)

这为什么是对的呢？其实就是运用了 $x\operatorname{xor} x=0$ 的性质。我们举几个例子，比如对于原图，$3->6$ 的路径权值为 $val_2\operatorname{xor}val_1\operatorname{xor} val_6$。而现在是 $val_2\operatorname{xor}\ (val_1\operatorname{xor}val_4\operatorname{val_6})\operatorname{val_4}$。居然是一样的。

如果连的边两个端点本来就在一个连通块里，就把环扔到线性基里，和 WC 那题一样。

好了，然后就到了写代码时间。。。。

反正我写了 208 行，调了 4 天，结果发现数组开小了。。。

参考代码：

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
#define pr pair<int,int>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=2e5+10;

int n,m,q,cnt;
int father[MAXN],dis[MAXN],size[MAXN],lb[MAXN<<2][32];

struct ege {
	int u,v,w;
}e[MAXN<<1];

map<pr,int> mp,index;
set<int> s;
vector<ege> edge[MAXN<<2];
vector<pr > qry[MAXN<<2];
stack<pr > stk;

pr make_edge(int x,int y) {
	return make_pair(min(x,y),max(x,y));
}
void insert(int x,int p) {
	for(int i=30;i>=0;i--) {
		if(x&(1<<i)) {
			if(lb[p][i]) {
				x^=lb[p][i];
			}
			else {
				lb[p][i]=x;
				return ;
			}
		}
	}
}
int find(int x) {
	if(x!=father[x]) {
		return find(father[x]);
	}
	return x;
}
int findis(int x) {
	if(x!=father[x]) {
		return dis[x]^findis(father[x]);
	}
	return 0;
}
void merge(ege s,int p) {
	int x=find(s.u);
	int y=find(s.v);
	if(x==y) {
		insert(findis(s.u)^findis(s.v)^s.w,p);
		stk.push(make_pair(-1,-1));
		return ;
	}
	if(size[x]>size[y]) {
		swap(x,y);
	}
	dis[x]=findis(s.u)^findis(s.v)^s.w;
	father[x]=y;
	size[y]+=size[x];
	stk.push(make_pair(x,y));
}
void del() {
	int x=stk.top().first;
	int y=stk.top().second;
	stk.pop();
	if(x==-1) {
		return ;
	}
	father[x]=x;
	dis[x]=0;
	size[y]-=size[x];
}

void modify(int l,int r,int p,int x,int y,ege s) {
	if(x>y||r<x||y<l) {
		return ;
	}
	if(x<=l&&r<=y) {
		edge[p].push_back(s);
		return ;
	}
	
	int mid=(l+r)>>1;
	modify(l,mid,p<<1,x,y,s);
	modify(mid+1,r,p<<1|1,x,y,s);
}
void modqry(int l,int r,int p,int x,int y,pr s) {
	if(x>y||r<x||y<l) {
		return ;
	}
	if(x<=l&&r<=y) {
		qry[p].push_back(s);
		return ;
	}
	
	int mid=(l+r)>>1;
	modqry(l,mid,p<<1,x,y,s);
	modqry(mid+1,r,p<<1|1,x,y,s);
}

void query(int l,int r,int p) {
	int sz=edge[p].size();
	for(int i=0;i<sz;i++) {
		merge(edge[p][i],p);
	}
	if(l==r) {
		int qsz=qry[p].size();
		for(int i=0;i<qsz;i++) {
			int ans=0;
			if(find(qry[p][i].first)!=find(qry[p][i].second)) {
				printf("0\n");
				break;
			}
			ans=findis(qry[p][i].first)^findis(qry[p][i].second);
			for(int j=30;j>=0;j--) {
				ans=min(ans,ans^lb[p][j]);
			}
			printf("%lld\n",ans);
		}
	}
	else {
		int mid=(l+r)>>1;
		for(int i=0;i<=30;i++) {
			lb[p<<1][i]=lb[p][i];
			lb[p<<1|1][i]=lb[p][i];
		}
		query(l,mid,p<<1);
		query(mid+1,r,p<<1|1);
	} 
	while(sz--) {
		del();
	}
}

signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		father[i]=i;
		size[i]=1;
		dis[i]=0;
	}
	for(int i=1;i<=m;i++) {
		e[i].u=read();e[i].v=read();e[i].w=read();
		pr tmp=make_edge(e[i].u,e[i].v);
		s.insert(i);
		mp[tmp]=1;
		index[tmp]=i;
	}
	cnt=m;
	
	cin>>q;
	for(int i=1;i<=q;i++) {
		int opt,u,v,w;
		opt=read();u=read();v=read();
		if(opt==1) {
			w=read(); 
			pr tmp=make_edge(u,v);
			e[++cnt].u=u;
			e[cnt].v=v;
			e[cnt].w=w;
			s.insert(cnt);
			mp[tmp]=i;
			index[tmp]=cnt;
		}
		if(opt==2) {
			pr tmp=make_edge(u,v);
			modify(1,q,1,mp[tmp],i-1,e[index[tmp]]);
			s.erase(s.find(index[tmp]));
			mp[tmp]=index[tmp]=0;
		}
		if(opt==3) {
			modqry(1,q,1,i,i,make_edge(u,v));
		}
	}
	
	for(set<int>::iterator it=s.begin();it!=s.end();it++) {
		modify(1,q,1,mp[make_edge(e[(*it)].u,e[*it].v)],q,e[*it]);
	}
	
	query(1,q,1);
	return 0;
}
/*
5 6
1 2 31
1 5 0
2 3 30
2 4 0
3 4 1
3 5 30
5
2 2 3
2 2 4
1 2 3 1
1 2 4 1
3 1 2


5 6
1 2 31
1 5 0
2 3 30
2 4 0
3 4 1
3 5 30
8
3 1 2
2 3 5
1 3 5 30
2 2 3
2 2 4
1 2 3 1
1 2 4 1
3 1 2
*/ 
```

---

## 作者：云浅知处 (赞：0)

> 题目链接：[Shortest Path Queries](https://www.luogu.com.cn/problem/CF938G)

首先我们都知道对于一个图，两点之间的异或最短/最长路就是：随便拎一条路径出来，设这条路径上 $\text{xor}$ 和为 $w$，把 $w$ 扔进图中所有环的环上边权异或和组成的集合的线性基，任意异或之后得到的最大/最小值。环的个数可以是指数级，但实际上随便拎一棵生成树后选取每条非树边与非树边中那条链构成的环上面的边权异或和，求一下线性基，得到的线性基就是正确的。

上面这些都是前置知识，不懂这些可以先去做做 P4151。下面说一下本题的重点

按照之前的套路我们需要维护一棵 dfs 生成树，尽管题目保证了图一直连通，但是如果删除的边恰好是一条树边我们发现就寄了，所以直接维护生成树是不可行的（或许写 LCT 是可行的

那这种题不想写 LCT 一般也就是线段树分治了。考虑线段树分治，那么现在需要支持加边和撤销。

用并查集可以轻松维护连通性。假设现在加了一条边 $(x,y)$，如果 $x,y$ 已经连通那么意味着多了一个环，我们需要知道 $x,y$ 在此时树上的路径异或和。那么只需要维护森林中每棵树上每个点到各自根路径上边权异或和即可。记这个值为 $f(i)$，那么新增的环的边权异或和就是 $f(x)\oplus f(y)\oplus w$，其中 $\oplus$ 表示异或。

但问题在于当 $x,y$ 属于森林中不同的树时，有许多点的 $f$ 值都发生了改变，怎么办呢

我们发现当用并查集维护时，如果连接的两个点恰好是两边连通块的树根，那么可以直接使用边带权的并查集进行维护。当这两个点不是树根时，设两边树根分别为 $r_1,r_2$，两个点为 $x_1,x_2$。若新增的边边权为 $w$，可以证明：

- 在 $x_1,x_2$ 间加边权为 $w$ 的边等价于在 $r_1,r_2$ 之间加边权为 $w\oplus d(x_1,r_1)\oplus d(x_2,r_2)$ 的边。

其中 $d(i,j)$ 表示树上 $i,j$ 两点间边权异或和。这个证明实在非常显然，留给读者。

那么现在就可以使用带撤销的边带权并查集维护了。同时还需要维护一个支持撤销的线性基，这个只需要在线段树上 dfs 的时候记录下每层的线性基形态即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int N=4e5+5;
const int D=30,LG=20;

struct Edge{
	int u,v,w;
	Edge(int U,int V,int W):u(U),v(V),w(W){}
	Edge(){}
};
vector<Edge>vec[N<<2];
int bas[D],tmp[LG][D];
int fa[N],dis[N],sz[N];

int find(int x){return x==fa[x]?x:find(fa[x]);}
int getdis(int x){return fa[x]==x?0:(dis[x]^getdis(fa[x]));}

void ins(int x){
	for(int i=D-1;i>=0;i--){
		int c=((x>>i)&1);
		if(!c)continue;
		if(bas[i]){x^=bas[i];continue;}
		else{bas[i]=x;return ;}
	}
}
int get(int w){
	for(int i=D-1;i>=0;i--)if((w^bas[i])<w)w^=bas[i];
	return w;
}

pair<int,int>stk[N<<1];
int top=0;

#define fi first
#define se second
#define mk make_pair

void addEdge(Edge t){
	int u=t.u,v=t.v,w=t.w;
	int fu=find(u),fv=find(v);
	if(fu==fv){ins(getdis(u)^getdis(v)^w);return ;}
	w^=getdis(u)^getdis(v);if(sz[fu]>sz[fv])swap(fu,fv);
	fa[fu]=fv,dis[fu]=w,stk[++top]=mk(fu,fv),sz[fv]+=sz[fu];
}
void del(int id){
	int u=stk[id].fi,v=stk[id].se;
	fa[u]=u,dis[u]=0,sz[v]-=sz[u];
}

int ans[N];
struct Node{
	int x,y,id;
	Node(int X,int Y,int I):x(X),y(Y),id(I){}
	Node(){}
};
Node q[N];

#define ls(p) (p<<1)
#define rs(p) (p<<1|1)
void add(int l,int r,Edge t,int ql,int qr,int p){
	if(l<=ql&&qr<=r){vec[p].emplace_back(t);return ;}
	int mid=(ql+qr)>>1;
	if(l<=mid)add(l,r,t,ql,mid,ls(p));
	if(r>mid)add(l,r,t,mid+1,qr,rs(p));
}
void dfs(int l,int r,int p,int d){
	memcpy(tmp[d],bas,sizeof(tmp[d]));int now=top;
	for(auto t:vec[p])addEdge(t);
	if(l==r){
		auto t=q[l];ans[t.id]=get(getdis(t.x)^getdis(t.y));
		memcpy(bas,tmp[d],sizeof(bas));while(top>now)del(top--);
		return ;
	}
	int mid=(l+r)>>1;
	dfs(l,mid,ls(p),d+1),dfs(mid+1,r,rs(p),d+1);
	memcpy(bas,tmp[d],sizeof(bas));while(top>now)del(top--);
}

int n,m,st[N],ed[N],Q;
Edge E[N];
bool used[N];

map<pair<int,int>,int>Map;

signed main(void){

	n=read(),m=read();int tot=m,T=1,qtot=0;
	for(int i=1;i<=n;i++)sz[i]=1,fa[i]=i;
	for(int i=1;i<=m;i++)E[i].u=read(),E[i].v=read(),E[i].w=read(),st[i]=1,Map[mk(E[i].u,E[i].v)]=i;
	int Q=read();for(int i=1;i<=Q;i++){
		int op=read(),x=read(),y=read();
		if(op==1){int w=read();E[++tot]=Edge(x,y,w);st[tot]=T,Map[mk(x,y)]=tot;}
		if(op==2){
			auto it=Map.find(mk(x,y));
			assert(it!=Map.end());int id=it->second;ed[id]=T-1,used[id]=1,Map.erase(it);
		}
		if(op==3)q[T++]=Node(x,y,++qtot);
	}
	for(int i=1;i<=tot;i++)if(!used[i])ed[i]=T;
	for(int i=1;i<=tot;i++)if(st[i]<=ed[i])add(st[i],ed[i],E[i],1,T,1);
	assert(T==qtot+1);
	dfs(1,T,1,0);for(int i=1;i<=qtot;i++)cout<<ans[i]<<'\n';

	return 0;
}
```


---

## 作者：寒鸽儿 (赞：0)

~~然而最终死在了并查集上，令人感叹。。。~~  
**考虑全局静态怎么做给图询问 xor 最短路**  
这里是一条非简单路径，我们考虑它由若干个圈加链构成（由 xor 的性质，用到圈只算一圈)。  
由 xor 性质，我们发现很多链的部分被抵消了，无论图的形态如何，最终留下的是一条直达的链（简单路径）和圈。  
易知原图中的所有圈都可以计入贡献，由于连通，从链条走一条简单路到圈再原路返回即可。  
这条路径的选取方式看起来很抽象，实际上只需要随便选一条：如果存在更佳的选择，一定与原先选的构成一个环，这个环会被计入贡献。  
**用线性基维护所有环，求任意简单路与之的异或 $\min$ 即可。**  
**考虑动态加边删边做这个东西：**  
一条边仅作用于一段连续的时间，**对时间线段树分治**，变成：**加边撤回维护环的贡献**。  
并查集维护求环，不带路径压缩是支持撤回的，加边复杂度 $\mathcal{O}(\log n)$，撤回 $\mathcal{O}(1)$。线性基插入和复制的代价是 $\mathcal{O}(\log w)$ 的。因此可以维护线段树分治过程中所需的信息。  
复杂度 $\mathcal{O}((n + q) \log (n + q) (\log n + \log w))$ 。  
~~关于标题是怎么来的可以看动态。~~  
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)

using namespace std;

const int maxn = 2e5 + 10;

struct xorBase {
	#define dig 30
	int p[dig + 1];
	bool zero;
	xorBase() { memset(p, 0, sizeof(p)); zero = false; }
	void insert(int x) {
		for(int i = dig; ~i; -- i)
			if(x & (1 << i)) {
				if(p[i]) x ^= p[i];
				else { p[i] = x; return ; }
			}
		zero = true;
	}
	int totmin(int ans = 0) {
		for(int i = dig; ~i; -- i)
			if((ans & (1 << i)) && p[i]) ans ^= p[i];
		return ans;
	}
} xb;

inline void copy(xorBase &lhs, xorBase &rhs) {
	lhs.zero = rhs.zero;
	memcpy(lhs.p, rhs.p, sizeof(lhs));
}

struct DSU {
	vector<int> fa, dis, rank;
	vector< pair<int, bool> > hist;
	void init(int n) {
		fa.resize(n + 1, 0); rep(i,1,n) fa[i] = i;
		dis.resize(n + 1, 0); rep(i,1,n) dis[i] = 0;
		rank.resize(n + 1, 0); rep(i,1,n) rank[i] = 1;
	}
	int find(int x, int &disCnt) {
		if(x == fa[x]) return x;
		int ret = find(fa[x], disCnt);
		disCnt ^= dis[x];
		return ret;
	}
	bool link(int x, int y, int w) {
		int dx = 0, dy = 0;
		x = find(x, dx);
		y = find(y, dy);
		if(x == y) return false;
		if(rank[x] < rank[y]) swap(x, y), swap(dx, dy);
		pair<int, bool> h = {y, 0};
		if(rank[x] == rank[y]) ++ rank[x], h.second = true;
		fa[y] = x, dis[y] = w ^ dx ^ dy;
		hist.push_back(h);
		return true;
	}
	void undo() {
		auto &it = hist.back();
		if(it.second) -- rank[fa[it.first]];
		fa[it.first] = it.first;
		dis[it.first] = 0;
		hist.pop_back();
	}
} dsu;

struct edge {
	int x, y;
	bool operator < (const edge &o) const {
		return x < o.x || x == o.x && y < o.y;
	}
};

struct ed {
	int x, y, w;
};

struct segTdiv {
	vector<ed> opr[maxn << 2];
	vector< pair<int, int> > qry[maxn];
	vector<int> ans;

	void insert(int p, int lp, int rp, int l, int r, ed e) {
		if(l <= lp && rp <= r) {
			opr[p].push_back(e);
			return ;
		}
		register int mid = (lp + rp) >> 1, ls = p << 1, rs = ls | 1;
		if(l <= mid) insert(ls, lp, mid, l, r, e);
		if(r > mid) insert(rs, mid + 1, rp, l, r, e);
	}

	void dfs(int p, int lp, int rp) {
		for(ed &e : opr[p]) {
			int w = e.w;
			if(dsu.link(e.x, e.y, w) == false) {
				dsu.find(e.x, w); dsu.find(e.y, w);
				xb.insert(w);
			}
		}
		if(lp == rp) {
			for(auto it : qry[lp]) {
				int dis = 0;
				dsu.find(it.first, dis);
				dsu.find(it.second, dis);
				ans.push_back(xb.totmin(dis));
			}
			return ;
		}
		register int mid = (lp + rp) >> 1;
		int sz = dsu.hist.size();
		xorBase tmp; copy(tmp, xb);
		dfs(p << 1, lp, mid);
		while(dsu.hist.size() > sz) dsu.undo();
		copy(xb, tmp);
		dfs(p << 1 | 1, mid + 1, rp);
	}
} tree;

map< edge, pair<int, pair<int, int> > > mp;

int main() {
	int n, m; 
	scanf("%d %d", &n, &m);
	dsu.init(n);
	int opt, x, y, w;
	int timer = 1;
	rep(i,1,m) {
		scanf("%d %d %d", &x, &y, &w);
		if(x > y) swap(x, y);
		mp[{x, y}] = {w, {1, 0}};
	}
	int q;
	scanf("%d", &q);
	rep(qr,1,q) {
		scanf("%d", &opt);
		if(opt != 3) ++ timer;
		if(opt == 1) {
			scanf("%d %d %d", &x, &y, &w);
			if(x > y) swap(x, y);
			mp[{x, y}] = {w, {timer, 0}};
		} else if(opt == 2) {
			scanf("%d %d", &x, &y);
			if(x > y) swap(x, y);
			mp[{x, y}].second.second = timer - 1;
		} else {
			scanf("%d %d", &x, &y);
			if(x > y) swap(x, y);
			tree.qry[timer].push_back({x, y});
		}
	}
	for(auto &it : mp) {
		if(it.second.second.second == 0) it.second.second.second = timer;
		tree.insert(1, 1, timer, it.second.second.first, it.second.second.second, {it.first.x, it.first.y, it.second.first});
	}
	tree.dfs(1, 1, timer);
	for(int a : tree.ans) printf("%d\n", a);
	return 0;
}
```

---

## 作者：fanypcd (赞：0)

### 前置芝士&题目：

线段树、线性基。

[P4151 [WC2011]最大XOR和路径](https://www.luogu.com.cn/problem/P4151)

---

回顾一下 P4151 怎么处理的：

- 任意得到一条 $1 - n$ 的路径长。

- 处理出所有环长，加入线性基。

- 所有的环都是可选可不选，用线性基求最大异或值。

所以我们这道题需要支持：

1. 动态维护两点之间任意一条异或路径长。

2. 加边后找到（可能出现的）环长，加入线性基。

对于 1. 可以用带权并查集维护一颗生成树（题目保证任意时刻连通），2. 则用并查集判断是否出现了环。这俩都不好直接进行删除，但是可以通过记录每次的操作来逐次撤回，所以上线段树分治。

对于询问操作，分治递归到当前时间时直接在线性基中查询即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
template <class T> inline void read(T &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + (ch - 48);
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define N 200005
int n, m, q;
struct edge
{
	int u, v, w;
};
struct linebase
{
	int p[35];
	stack<int> st;
	inline void insert(int v)
	{
		for(int i = 30; i >= 0; i--)
		{
			if(!(v >> i))
			{
				continue;
			}
			if(!p[i])
			{
				st.push(i);
				p[i] = v;
				break;
			}
			v ^= p[i];
		}
		return;
	}
	inline int query(int v)
	{
		int ret = v;
		for(int i = 30; i >= 0; i--)
		{
			if((ret ^ p[i]) < ret)
			{
				ret ^= p[i];
			}
		}
		return ret;
	}
	inline void del(int size)
	{
		while((int)st.size() != size)
		{
			p[st.top()] = 0;
			st.pop();
		}
		return;
	}
};
linebase LB;
struct mergeset
{
	int fa[N], dep[N], dis[N];
	struct node
	{
		int f1, f2, dep;
	};
	stack<node> st;
	inline void init()
	{
		for(int i = 1; i <= n; i++)
		{
			fa[i] = i;
			dep[i] = 1;
		}
		return;
	}
	inline int getfa(int x)
	{
		while(x != fa[x])
		{
			x = fa[x];
		}
		return x;
	}
	inline int qdis(int x)
	{
		int ret = 0;
		while(x != fa[x])
		{
			ret ^= dis[x];
			x = fa[x];
		}
		return ret;
	}
	inline void merge(edge x)
	{
		int f1 = getfa(x.u), f2 = getfa(x.v);
		if(f1 == f2)
		{
//			printf("\nupd:%d %d %d\n", x.u, x.v, qdis(x.u) ^ qdis(x.v) ^ x.w);
			LB.insert(qdis(x.u) ^ qdis(x.v) ^ x.w);
			return;
		}
		if(dep[f1] < dep[f2])
		{
			swap(f1, f2);
		}
		st.push((node){f1, f2, dep[f1]});
		dis[f2] = qdis(x.u) ^ qdis(x.v) ^ x.w;
		fa[f2] = f1;
		dep[f1] = max(dep[f1], dep[f2] + 1);
		return;
	}
	inline void del(int size)
	{
		while((int)st.size() != size)
		{
			fa[st.top().f2] = st.top().f2;
			dep[st.top().f1] = st.top().dep;
			dis[st.top().f2] = 0;
			st.pop();
		}
		return;
	}
};
mergeset MS;
vector<edge> tmp[N << 2];
void update(int root, int l, int r, int L, int R, edge x)
{
	if(L > R)
	{
		return;
	}
	if(L <= l && r <= R)
	{
		tmp[root].emplace_back(x);
		return;
	}
	int mid = (l + r) >> 1;
	if(L <= mid)
	{
		update(root << 1, l, mid, L, R, x);
	}
	if(mid < R)
	{
		update(root << 1 | 1, mid + 1, r, L, R, x);
	}
	return;
}
struct question
{
	int x, y;
};
question que[N];
void dfs(int root, int l, int r)
{
	int mem1 = MS.st.size(), mem2 = LB.st.size();
	for(auto x : tmp[root])
	{
		MS.merge(x);
	}
	if(l == r)
	{
		if(que[l].x)
		{
			printf("%d\n", LB.query(MS.qdis(que[l].x) ^ MS.qdis(que[l].y)));
//			printf("%d %d %d %d\n", que[l].x, que[l].y, MS.qdis(que[l].x), MS.qdis(que[l].y));
		}
	}
	else
	{
		int mid = (l + r) >> 1;
		dfs(root << 1, l, mid), dfs(root << 1 | 1, mid + 1, r);
	}
	MS.del(mem1), LB.del(mem2);
	return;
}
map<pair<int, int>, pair<int, int>> ti;
signed main()
{
	read(n), read(m);
	MS.init();
	int u, v, w;
	for(int i = 1; i <= m; i++)
	{
		read(u), read(v), read(w);
		ti[make_pair(u, v)] = make_pair(1, w);
	}
	read(q);
	int op;
	for(int i = 1; i <= q; i++)
	{
		read(op);
		if(op == 1)
		{
			read(u), read(v), read(w);
			ti[make_pair(u, v)] = make_pair(i, w);
		}
		else if(op == 2)
		{
			read(u), read(v);
			pair<int, int> last = ti[make_pair(u, v)];
			update(1, 1, q, last.first, i - 1, (edge){u, v, last.second});
			ti[make_pair(u, v)] = make_pair(0, 0);
		}
		else
		{
			read(que[i].x), read(que[i].y);
		}
	}
	for(auto x : ti)
	{
		if(x.second.first)
		{
			update(1, 1, q, x.second.first, q, (edge){x.first.first, x.first.second, x.second.second});
		}
	}
	dfs(1, 1, q);
	return 0;
}
```

---

