# Nanami's Power Plant

## 题目描述

Nanami likes playing games, and is also really good at it. This day she was playing a new game which involved operating a power plant. Nanami's job is to control the generators in the plant and produce maximum output.

There are $ n $ generators in the plant. Each generator should be set to a generating level. Generating level is an integer (possibly zero or negative), the generating level of the $ i $ -th generator should be between $ l_{i} $ and $ r_{i} $ (both inclusive). The output of a generator can be calculated using a certain quadratic function $ f(x) $ , where $ x $ is the generating level of the generator. Each generator has its own function, the function of the $ i $ -th generator is denoted as $ f_{i}(x) $ .

However, there are $ m $ further restrictions to the generators. Let the generating level of the $ i $ -th generator be $ x_{i} $ . Each restriction is of the form $ x_{u}<=x_{v}+d $ , where $ u $ and $ v $ are IDs of two different generators and $ d $ is an integer.

Nanami found the game tedious but giving up is against her creed. So she decided to have a program written to calculate the answer for her (the maximum total output of generators). Somehow, this became your job.

## 说明/提示

In the first sample, $ f_{1}(x)=x $ , $ f_{2}(x)=x+1 $ , and $ f_{3}(x)=x+2 $ , so we are to maximize the sum of the generating levels. The restrictions are $ x_{1}<=x_{2} $ , $ x_{2}<=x_{3} $ , and $ x_{3}<=x_{1} $ , which gives us $ x_{1}=x_{2}=x_{3} $ . The optimal configuration is $ x_{1}=x_{2}=x_{3}=2 $ , which produces an output of 9.

In the second sample, restrictions are equal to $ |x_{i}-x_{i+1}|<=3 $ for $ 1<=i&lt;n $ . One of the optimal configurations is $ x_{1}=1 $ , $ x_{2}=4 $ , $ x_{3}=5 $ , $ x_{4}=8 $ and $ x_{5}=7 $ .

## 样例 #1

### 输入

```
3 3
0 1 0
0 1 1
0 1 2
0 3
1 2
-100 100
1 2 0
2 3 0
3 1 0
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5 8
1 -8 20
2 -4 0
-1 10 -10
0 1 0
0 -1 1
1 9
1 4
0 10
3 11
7 9
2 1 3
1 2 3
2 3 3
3 2 3
3 4 3
4 3 3
4 5 3
5 4 3
```

### 输出

```
46
```

# 题解

## 作者：pufanyi (赞：5)

考虑网络流，对每个函数都建立 $[l_i,r_i]$ 的点，点 $(i,j)$ 表示函数 $f_i$ 当 $x_i=j$ 时的点。

我们考虑最小损失。设一个极大值 $lim$（大于所有的 $f_i(x)$），将也就是要求 $lim-f_i(x)$ 的最小值。

我们从点 $(i,j)$ 向点 $(i,j+1)$（如果 $j=r_i$ 那就是超汇 $T$）流 $lim - f_i(j)$，从超源 $S$ 向点 $(i,l_i)$ 流 $\infty$。

大概就是这样一张图：

![](https://pufanyi.github.io/oi-blog/CF434D/flow1.svg)

如果这些函数的取值互补干涉，那么 $n\times lim-\text{最小割}$ 就是答案。

我们考虑如何加入这些限制。

如果现在有限制 $x_u\le x_v+d$，也就是 $x_v\ge x_u-d$。如果我们割了 $x_u$ 这条边，在$v$这条链上我们只能割 $x_u-d$ 以后的边。那就不妨从$u$这条表上所有的$x$向$v$这条边上所有的 $x-d$ 连一条 $\infty$ 的边。

如果割绿色的那两条线：

![](https://pufanyi.github.io/oi-blog/CF434D/flow.svg)

很开心地测一下样例，炸了……

我们来看这种情形（对样例1略有改动）：

```plain
2 2
0 1 0
0 1 1
2 3
1 2
1 2 0
2 1 0
```

建出来的图大概是长这样的：

![](https://pufanyi.github.io/oi-blog/CF434D/flow4.svg)

最小割是选 $(1,3)\to T$ 和 $(2,3)\to T$。

但显然 $(1,3)\to T$ 是不能选的。因为由 $x_1\le x_2$ 和 $x_2\le x_1$ 可知 $x_1=x_2$。

于是我们只得再建一个 $(i,r_i+1)$ 点，$(i,r_i)\to (i,r_i+1)$ 流 $f_i(r_i)$，$(i,r_i+1)\to T$ 流 $\infty$。

![](https://pufanyi.github.io/oi-blog/CF434D/flow5.svg)

这样就完美了。

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const LL maxn = 10005;
const LL maxm = 5000005;
const LL inf = 0x3f3f3f3f3f3f3f3f;
const LL lim = 1000000000000;

struct Edge
{
    LL to, nxt, cap;
} e[maxm << 1];

LL first[maxn], first_bak[maxn];

inline void add_edge(LL from, LL to, LL cap)
{
    static LL cnt = -1;
    e[++cnt].nxt = first[from];
    first[from] = cnt;
    e[cnt].to = to;
    e[cnt].cap = cap;
    e[++cnt].nxt = first[to];
    first[to] = cnt;
    e[cnt].to = from;
    e[cnt].cap = 0;
}

LL n, m, S, T;

LL bh[105][205];
LL a[maxn], b[maxn], c[maxn];
LL ll[maxn];
LL rr[maxn];
LL dep[maxn];

inline LL getans(LL I, LL x)
{
    return a[I] * x * x + b[I] * x + c[I];
}

inline bool bfs()
{
    memset(dep, 0x3f, sizeof(dep));
    queue<LL> q;
    q.push(S);
    dep[S] = 0;
    for(int i = S; i <= T; ++i)
        first[i] = first_bak[i];
    while(!q.empty())
    {
        LL now = q.front();
        q.pop();
        for(int i = first[now]; ~i; i = e[i].nxt)
        {
            LL to = e[i].to;
            if(dep[to] >= inf && e[i].cap > 0)
            {
                dep[to] = dep[now] + 1;
                q.push(to);
            }
        }
    }
    return dep[T] < inf;
}

inline LL dfs(LL now, LL lim)
{
    if(!lim || now == T)
        return lim;
    LL flow = 0;
    for(int i = first[now]; ~i; i = e[i].nxt)
    {
        first[now] = i;
        register LL to = e[i].to, f;
        if(dep[to] == dep[now] + 1 && (f = dfs(to, min(lim, e[i].cap))) > 0)
        {
            lim -= f;
            flow += f;
            e[i].cap -= f;
            e[i ^ 1].cap += f;
            if(lim <= 0)
                break;
        }
    }
    return flow;
}

inline LL dinic()
{
    LL flow = 0;
    while(bfs())
        flow += dfs(S, inf);
    return flow;
}

int main()
{
    memset(first, 0xff, sizeof(first));
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", &ll[i], &rr[i]);
        add_edge(S, T + 1, inf);
        for(LL j = ll[i] + 100; j <= rr[i] + 101; ++j)
        {
            bh[i][j] = ++T;
            if(j != ll[i] + 100)
                add_edge(bh[i][j - 1], bh[i][j], lim - getans(i, j - 1 - 100));
        }
    }
    T++;
    for(LL i = 1; i <= n; ++i)
        add_edge(bh[i][rr[i] + 101], T, inf);
    for(int i = 1, u, v, d; i <= m; ++i)
    {
        scanf("%d%d%d", &u, &v, &d);
        for(int j = ll[u]; j <= rr[u] + 1; ++j)
            if(ll[v] <= j - d && j - d <= rr[v] + 1)
                add_edge(bh[u][j + 100], bh[v][j - d + 100], inf);
    }
    for(int i = S; i <= T; ++i)
        first_bak[i] = first[i];
    printf("%lld\n", n * lim - dinic());
    return 0;
}
```

---

## 作者：xtx1092515503 (赞：2)

debug 1 week，精神崩溃，后来发现是空间开小了……

------

虽然这个奇奇怪怪的限制让人很难不往**差分约束**去想，但是如果差分约束的话就不方便求出最大值，因此我们不得不思考其它的算法。

考虑将方案抽象出来——给你许多物品，每个物品各有一些取值，且其中某些物品对不能取某些值对，求最优的取值。

再进一步观察，发现实际上每一个物品的所有可能取值中，均**能且只能**选一个；所有不合法值对中，均**至多**选一个。并且，这两个是唯二的限制。

多选一问题，因为本题是带权的所以不能简单用SAT问题解决，所以考虑**最小割**。

因为每个物品的所有取值中选且仅选一个，放到最小割上就是一条从源点到汇点的路径，这样在最小割中就割且仅割一条。

可是我们要的是最大权值，这样建图的话求出来的应该是最小权值。

但是我们发现，因为这样建图会割且仅割 $n$ 条边，所以我们对于一个取值为 $k$ 的物品，实际连上一条边权为 $lim-k$ 的边，其中 $lim$ 是一个足够大的值，为了保证不存在负权边。实际取 $10^6$ 足矣。

这样，若最小割是 $cut$，则答案即为 $n\times lim-cut$。

于是我们设 $id_{i,j}$ 表示第 $i$ 个函数取值为 $j$ 时代表的节点，$f_{i,j}$ 表示取值为 $j$ 时的收益，同时设其取值范围为 $[L_i,R_i]$。

则在我们上述方案中，就要连边 $(S,id_{i,L_i},lim-f_{i,j})$，$(id_{i,j-1},id_{i,j},lim-f_{i,j}),\text{where }j\in(L_i,R_i]$，$(id_{i,R_i},T,\infty)$。

这样下来考虑限制 $x_u\leq x_v+d$。显然，该限制不成立，当且仅当 $x_v<x_u-d$。于是我们枚举 $x_u$ 的取值，考虑使得所有 $x_v$ 的取值 $<x_u-d$ 的割不合法。

明显，$x_v<x_u-d$ 是从源点到汇点的路径上一段前缀，于是我们只需连边 $(id_{u,x_u},id_{v,x_u-d},\infty)$，这样所有上述的割都不合法了。

需要注意的是，对于某些 $x_u$ 或者 $x_v$，可能压根不存在任何对应的另一个变量，这时候需要手动禁掉这些取值，具体来说是从 $S$ 连来无穷的边或者连到 $T$ 无穷的边，视情况而定，具体自己稍微画画图推推就出来了，或者也可以参考代码。

若设 $V$ 为值域大小的话，考虑点数，发现其为 $nV$ 级别的；再考虑边数，是 $mV$ 的，都在接受范围内。

我们发现所有的限制都已经被考虑到了，故这就是正解。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int LIM=1000000;
int n,m,a[110],b[110],c[110],L[110],R[110],id[110][2100],tot;
namespace MaxFlow{
	const int N=201000,M=2001000;
	int head[N],cur[N],dep[N],cnt,S,T,res;
	struct node{int to,next,val;}edge[M];
	void ae(int u,int v,int w){
//		printf("%d %d %d\n",u,v,w);
		edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,head[u]=cnt++;
		edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=0,head[v]=cnt++;
	}
	queue<int>q;
	inline bool bfs(){
		memset(dep,0,sizeof(dep)),q.push(S),dep[S]=1;
		while(!q.empty()){
			register int x=q.front();q.pop();
			for(register int i=cur[x]=head[x];i!=-1;i=edge[i].next)if(edge[i].val&&!dep[edge[i].to])dep[edge[i].to]=dep[x]+1,q.push(edge[i].to);
		}
		return dep[T]>0;
	}
	bool reach;
	inline int dfs(int x,int flow){
		if(x==T){res+=flow,reach=true;return flow;}
		int used=0;
		for(register int &i=cur[x];i!=-1;i=edge[i].next){
			if(!edge[i].val||dep[edge[i].to]!=dep[x]+1)continue;
			register int ff=dfs(edge[i].to,min(edge[i].val,flow-used));
			if(ff){edge[i].val-=ff,edge[i^1].val+=ff,used+=ff;if(used==flow)break;}
		}
		return used;
	}
	inline void Dinic(){while(bfs()){reach=true;while(reach)reach=false,dfs(S,0x3f3f3f3f);}}
}
using namespace MaxFlow;
#define ID(x,y) id[x][(y)+L[x]]
#define VL(x,y) (a[x]*(y)*(y)+b[x]*(y)+c[x])
int main(){
	scanf("%d%d",&n,&m),S=1,T=2,tot=2,memset(head,-1,sizeof(head));
	for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i],&b[i],&c[i]);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&L[i],&R[i]);
		for(int j=L[i];j<=R[i];j++)ID(i,j)=++tot;
		ae(S,ID(i,L[i]),LIM-VL(i,L[i]));
		for(int j=L[i]+1;j<=R[i];j++)ae(ID(i,j-1),ID(i,j),LIM-VL(i,j));
		ae(ID(i,R[i]),T,0x3f3f3f3f);
	}
	for(int i=1,u,v,d;i<=m;i++){
		scanf("%d%d%d",&u,&v,&d);
		if(L[v]<=L[u]-d-1&&L[u]-d-1<=R[v])ae(S,ID(v,L[u]-d-1),0x3f3f3f3f);
		for(int j=L[u];j<=R[u];j++){
			if(j-d<L[v])continue;
			if(j-d<=R[v])ae(ID(u,j),ID(v,j-d),0x3f3f3f3f);
			else ae(ID(u,j),T,0x3f3f3f3f);
		}
	}
	Dinic();
	printf("%d\n",LIM*n-res);
	return 0;
}
```



---

## 作者：Drind (赞：1)

### 题目解析

给出 $n$ 个函数 $f(i,x)$，在满足 $m$ 个形如 $x_u\le x_v+d$ 的条件下使得 $\sum_{i=1}^nf(i,x_i)$ 最大。

首先我们要知道这道题跟二次函数一点关系没有别被骗了。其次，我们先抛弃约束条件看一看这题要怎么做。因为 $x_i$ 都是整数，而且函数的定义域都很小，所以直接把定义域上每个整数建一个点，只有 $200n$ 个点完全不慌。然后我们分开考虑每个函数，那么我们就看出来这是一个在很多点中取最大值的问题，这个问题我们完全可以把点权转化为边权然后做最小割解决，为什么不直接暴力找最大值？因为后面还有约束条件。

我们现在考虑 $x_u\le x_v+d$ 的约束条件，假设 $x_u$ 已知，那么 $x_v\ge x_u-d$，也就是给 $x_v$ 设置了一个下限。这个东西可以巧妙地套在我们刚才的 $n$ 条链上最小割模型中。怎么做呢？具体的就是把 $u$ 函数的第 $x_u$ 个点指向 $v$ 函数的第 $x_u-d$ 个点上，这样子，如果我们割开了 $x_u$ 的出边（也就是选中了这个点），那么在 $v$ 函数上就不能再割 $x_u-d$ 之前的边了，因为没卵用（直接从 $x_u$ 跳到 $v$ 上就行），大概建成的图如下，注意边是有向的。

![](https://cdn.luogu.com.cn/upload/image_hosting/2nfipprn.png)

省略最大流模板代码如下，注意 `inf` 和 `INF` 在代码里的定义完全不一样，前者数量级大于后者。
```cpp
struct func{
	int a,b,c,l,r;
}f[N];

inline int work(int p,int x){
	return f[p].a*x*x+f[p].b*x+f[p].c;
}

int res=0;
int dot[51][202];

inline void fake_main(){
	memset(head,-1,sizeof head);
	
	int n,m; cin>>n>>m;
	s=N-1,t=s-1;
	for(int i=1;i<=n;i++) cin>>f[i].a>>f[i].b>>f[i].c;
	for(int i=1;i<=n;i++) cin>>f[i].l>>f[i].r;
	
	for(int i=1;i<=n;i++){
		for(int j=f[i].l+100;j<=f[i].r+101;j++){
			dot[i][j]=++res;
			if(j!=f[i].l+100) adde(dot[i][j-1],dot[i][j],INF-work(i,j-101));
		}//这里是因为要找最大值，但是最小割是最小值，所以转成负数，那用一个极大值加上这个负数转变成整数即可。
	}
	for(int i=1;i<=n;i++) adde(s,dot[i][f[i].l+100],inf);
	for(int i=1;i<=n;i++) adde(dot[i][f[i].r+101],t,inf);
	for(int i=1;i<=m;i++){
		int u,v,d; cin>>u>>v>>d;
		for(int j=f[u].l;j<=f[u].r+1;j++){
			if(f[v].l<=j-d&&j-d<=f[v].r+1) adde(dot[u][j+100],dot[v][j-d+100],inf);
		}
	}
	cout<<n*INF-dinic()<<"\n";
}
```

---

## 作者：strcmp (赞：0)

**「前言」**

《这题虽然是黑题》《但简直是模板切糕》

![](https://cdn.luogu.com.cn/upload/image_hosting/4qlpul1h.png)

---

相信你也是刚写完切糕来写这道题。

跟前言一样，**[前置题目](https://www.luogu.com.cn/problem/P3227)**。

让我们复习一下切糕怎么连的边，给每个二维点拆 $R$ 个点：

令 $x$ 为一个二维点。

- $(x,\,y) \to (x,\,y+1),\,w_{x,\,y}$。

- $s \to (x,\,1),\,+\infty$。

- $(x,\,r + 1) \to t,\,+\infty$。

- 对于所有二维点 $(x,\,y)$ 和相邻二维点 $(nx,\,ny)$，$(x,\,y,\,z) \to (nx,\,ny,\,z - D)$。

然后~~这题就做完了。~~

但也不是完全一样，我们考虑一下它更改了切糕原题的哪些东西。

- 三维变成二维，直接改成枚举二维。

- 最小代价变成最大总收益。简单，给所有边权 $w$ 变成 $\text{inf} - w$ 就完了。

- 有 $x \in [l,\,r]$ 的限制，好办，先给 $l,\,r$ 加 $100$。然后把 $x$ 这个链头的 $[0,\,l - 1]$ 和 $[r + 1,\,200]$ 的区间的边设置为 $+\infty$。

- 然后注意到我们最后连接了一堆空结点，显然很没有脑子，因此直接把无用边给去掉。

- 限制是单向的，直接去掉多出来的一边。

- 好了最后答案是什么？$\text{inf} \times n - \text{mincut}$。

注意我们令 $200 \ll \text{inf} \ll +\infty$。

对于切糕模型的正确性网上一堆，不赘述了。

```cpp
// LUOGU_RID: 170382831
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair
using namespace std;
typedef long long int ll;
using __int128_t = ll;
using pii = pair<int, int>;
constexpr int maxn = 1e5 + 10;
const ll top = 114514191981000LL, inf = top * 1000;
struct edge { int to, nxt; ll w; } nd[maxn]; int h[maxn], cnt = 0;
inline void add(int u, int v, ll w) { nd[cnt].nxt = h[u], nd[cnt].to = v, nd[cnt].w = w, h[u] = cnt++; }
inline void addE(int u, int v, ll w) { add(u, v, w); add(v, u, 0); }
int T, s, t, now, n, m, cur[maxn], d[maxn], que[maxn], hd = 1, ta = 0; ll sum = 0;
inline int bfs() {
	memset(d, 0x3f, (now + 1) * sizeof(int));
	hd = 1, ta = 0; que[++ta] = t; d[t] = 0;
	while (hd <= ta) {
		int u = que[hd++];
		for (int i = h[u]; ~i; i = nd[i].nxt) {
			int v = nd[i].to;
			if (d[v] > d[u] + 1 && nd[i ^ 1].w) d[v] = d[u] + 1, que[++ta] = v;
		}
	}
	return d[s] < 1e9;
}
ll dfs(int u, ll fl) {
	if (u == t || !fl) return fl; ll nw = fl;
	for (int& i = cur[u]; ~i; i = nd[i].nxt) {
		if (d[u] != d[nd[i].to] + 1 || !nd[i].w) continue;
		ll c = nd[i].w, wv = dfs(nd[i].to, min(fl, c));
		if (!(nd[i].w -= wv, nd[i ^ 1].w += wv, fl -= wv)) return nw;
	}
	if (fl) d[u] = 1e9;
	return nw - fl;
}
inline void Dinic() { while (bfs()) memcpy(cur, h, sizeof(cur)), sum += dfs(s, inf); }
ll a[maxn], b[maxn], c[maxn], l[maxn], r[maxn]; int id[205][505];
ll f(int i, int x) { return a[i] * x * x + b[i] * x + c[i]; }
int main() {
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m); s = 1, t = now = 2; 
	rep(i, 1, n) scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	rep(i, 1, n) scanf("%lld%lld", &l[i], &r[i]), l[i] += 100, r[i] += 100;
	rep(i, 1, n) {
		addE(s, now + 1, inf);
		rep(j, l[i], r[i] + 1) id[i][j] = ++now;
		addE(now, t, inf);
		rep(j, l[i], r[i]) addE(id[i][j], id[i][j + 1], top - f(i, j - 100));
	}
	for (int i = 1, u, v, d = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &d);
		rep(j, l[u], r[u]) addE(id[u][j], id[v][j - d], inf);
	}
	Dinic();
	printf("%lld\n", top * n - sum);
	return 0;
}
```

---

