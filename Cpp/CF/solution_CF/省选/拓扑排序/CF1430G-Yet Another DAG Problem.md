# Yet Another DAG Problem

## 题目描述

You are given a directed acyclic graph (a directed graph that does not contain cycles) of $ n $ vertices and $ m $ arcs. The $ i $ -th arc leads from the vertex $ x_i $ to the vertex $ y_i $ and has the weight $ w_i $ .

Your task is to select an integer $ a_v $ for each vertex $ v $ , and then write a number $ b_i $ on each arcs $ i $ such that $ b_i = a_{x_i} - a_{y_i} $ . You must select the numbers so that:

- all $ b_i $ are positive;
- the value of the expression $ \sum \limits_{i = 1}^{m} w_i b_i $ is the lowest possible.

It can be shown that for any directed acyclic graph with non-negative $ w_i $ , such a way to choose numbers exists.

## 样例 #1

### 输入

```
3 2
2 1 4
1 3 2```

### 输出

```
1 2 0```

## 样例 #2

### 输入

```
5 4
1 2 1
2 3 1
1 3 6
4 5 8```

### 输出

```
43 42 41 1337 1336```

## 样例 #3

### 输入

```
5 5
1 2 1
2 3 1
3 4 1
1 5 1
5 4 10```

### 输出

```
4 3 2 1 2```

# 题解

## 作者：Clouder (赞：12)

## Before the Beginning

本文亦发表于笔者博客：[https://www.codein.icu/cf1430g/](https://www.codein.icu/cf1430g/)

## 题意
给定一个有向无环图，每条边都有 $w_i$ 的权重，给每个点分配权值 $a_i$，对于每条连接 $(u,v)$ 的边，定义其权值为 $b_i = a_u - a_v$，要求：

1. $b_i > 0$
2. $w_i \times b_i$ 最小

输出一种分配方案。

## 解法

听说方法多多，这里是一种网络流最小割的解法。
首先将边权贡献转化为点权贡献。

$\sum w_i \times (a_u - a_v)$

拆开后，将 $w_i$ 记到 $u$ 点权的权重，将 $-w_i$ 记到 $v$ 点权的权重。

现在只需要给点分配权值，就能计算出总贡献。

### 点权结论
有一个结论：所有点的权值都在 $[0,n - 1]$ 中。  

要求 $b_i > 0$，就是要求 $a_u > a_v$，感性理解：按拓扑序来分配权值，最劣是一条链的情况，依次为 $n,n-1,\ldots,0$
还有 Codeforces 官方证明：  

对于某一个值 $k$，如果存在 $a_i > k$ 而 $a_j < k$，且不存在 $a_g = k$，可以将 $> k$ 的权值都减小 $1$，而不会改变 $b$ 数组。  

因此所有点的权值都是连续的，即不存在 $0,1,3,\ldots$ 这样的分配方式，否则一定可以将 $3,\ldots$ 整体减小 $1$.  

那么最劣情况就是点权互不相同，值域为 $[0,n-1]$

### 建模

将点拆成一条链，每条边代表给该点选择一个权值，在链的一端连源点，另一端连汇点，边的容量为选择权值对应的贡献，跑最小割，割掉哪条边就选择了哪个权值。  

接下来将原图中的边的限制加上。  

只需要保证 $a_u > a_v$ 即可，就是要保证割了 $u$ 的权值为 $i$ 的边后，不能割 $v$ 的权值 $\ge i$ 的边。  

那么在对应的权值点间连无穷边即可加上限制，方式多样，具体看图：  

![buildgraph](https://cdn.jsdelivr.net/gh/Clouder0/myPics/img/buildgraph2.png)

给边赋值容量为该点选择该权值获得的贡献，即转化后的点权乘上权值。  

注意到转化后点权可能为负数，因此给容量整体加上一个较大值，平移为正数。  

## 代码

最后求方案，可以在残量网络上从源点开始深搜，找到 $S$ 点集内的所有点。  

Update on 10/21/2020: 
加上的较大值需要保证能够让边权为正数，考虑 $w_i \times j$ 的最大值，$w_i$ 可以达到 $-10^9 \times n$，而 $j < n$，因此需要设置 $10^9 \times n^2$ 级别的值.  
此外，删除了一个没有用到的数组。

```cpp
#include <algorithm>
#include <cstdio>
#include <ctype.h>
using namespace std;
const int bufSize = 1e6;
#define int long long
inline char nc()
{
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
inline T read(T& r)
{
    static char c;
    r = 0;
    for (c = nc(); !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r;
}
const int maxn = 510, maxm = 1e5;
struct node
{
    int to, next, cap;
} E[maxm];
int head[maxn], tot = 1;
inline void add(int x, int y, int cap)
{
    E[++tot].next = head[x], head[x] = tot, E[tot].to = y, E[tot].cap = cap;
    E[++tot].next = head[y], head[y] = tot, E[tot].to = x, E[tot].cap = 0;
}
int n, m, w[maxn];
int s, t, id[maxn][maxn], cnt, dep[maxn], cur[maxn];
int q[maxn], qt, qh;
bool bfs()
{
    for (int i = 1; i <= cnt; ++i) dep[i] = 0, cur[i] = head[i];
    qh = 1, q[qt = 1] = s, dep[s] = 1;
    while (qt >= qh)
    {
        int u = q[qh++];
        if (u == t) return 1;
        for (int p = head[u], v; p; p = E[p].next) 
            if (!dep[v = E[p].to] && E[p].cap) dep[v] = dep[u] + 1, q[++qt] = v;
    }
    return 0;
}
int dfs(int u, int flow)
{
    if (u == t || !flow) return flow;
    int sumflow = 0;
    for (int &p = cur[u], v, vflow; p; p = E[p].next)
        if (dep[v = E[p].to] == dep[u] + 1 && E[p].cap && (vflow = dfs(v, min(E[p].cap, flow))))
        {
            E[p].cap -= vflow, E[p ^ 1].cap += vflow, sumflow += vflow, flow -= vflow;
            if (flow == 0) break;
        }
    return sumflow;
}
const int inf = 1ll << 60;
const int big = 4e11;
bool vis[maxn];
void dfs2(int u)
{
    vis[u] = 1;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (!vis[v] && E[p].cap > 0) dfs2(v);
    }
}
signed main()
{
    read(n), read(m);
    s = ++cnt, t = ++cnt;
    for (int i = 1; i <= n; ++i) for (int j = 0; j <= n; ++j) id[i][j] = ++cnt;
    for (int i = 1, a, b, c; i <= m; ++i)
    {
        read(a), read(b), read(c), w[a] += c, w[b] -= c;
        for (int j = 0; j < n; ++j) add(id[b][j], id[a][j + 1], inf);
    }
    for (int i = 1; i <= n; ++i)
    {
        add(s, id[i][0], inf), add(id[i][n], t, inf);
        for (int j = 0; j < n; ++j) add(id[i][j], id[i][j + 1], w[i] * j + big);
    }
    while (bfs()) dfs(s, inf);
    dfs2(s);
    for (int i = 1; i <= n; ++i)
    {
        int ans = 0;
        for (int j = 0; j <= n; ++j) if (vis[id[i][j]]) ans = j;
        printf("%lld ", ans);
    }
    return 0;
}
```

---

## 作者：duyi (赞：8)

[超超超超超超超超超爽的阅读体验！！！！！！（芜湖！！！！！！）](https://www.cnblogs.com/dysyn1314/p/13951189.html)

# CF1430G Yet Another DAG Problem

## 题目大意

给定一张 $n$ 个点 $m$ 条边的**有向无环图**（DAG），第 $i$ 条边从 $x_i$ 通向 $y_i$，且有一个边权 $w_i$。

现在请你给每个点 $v$ 构造一个整数点权 $a_v$ ($0\leq a_v\leq 10^9$)。对每条边 $i$，我们设 $b_i = a_{x_i} - a_{y_i}$。你构造的点权必须满足：

- 所有 $b_i$ 都是正数。
- 最小化 $\sum_{i = 1}^{m}w_ib_i$。

请给出构造方案。可以证明方案一定存在。

数据范围：$1\leq n\leq 18$，$1\leq m\leq\frac{n(n-1)}{2}$，$1\leq x_i,y_i\leq n$，$1\leq w_i\leq10^5$。保证无自环，无重边。

## 本题题解

记 DAG 的节点集合为 $V$，边集为 $E$。

考虑给 DAG 分层。满足对所有 $(x\to y)\in E$，$x$ 的层数小于 $y$ 的层数。**每层点权相同**。层数越大，点权越小。确定分层后，我们很容易按层数从大到小，推出每个点的点权。

分层的过程可以用一个状压 DP 来实现。设 $f(S)$ 表示考虑了前若干层，包含了 $S$ 里的这些节点。

转移时考虑下一层有哪些节点，设为 $T$。首先，$T$ 与 $S$ 交一定为空。第二，所有能到达 $T$ 中至少一个点的点，都已经出现在了 $S$ 中，即：$\forall u \in T,\forall (v\to u)\in E:v\in S$。枚举所有这样的 $T$，从 $f(S)$ 转移到 $f(S\cup T)$。

考虑转移的系数。所有从 $S$ 连出的边，若终点不在 $S$ 里，则至少都在下一层。所以转移的代价是：$\displaystyle \sum_{(u\to v)\in E,u\in S,v\notin s} w_{u,v}$。也就是说，我们把一条边的代价，分摊到了它跨过的每一层里：它每跨过一层（转移一次），代价就增加 $w$。

因为 $T$ 是 $S$ 的补集的子集，枚举所有 $T$ 的时间复杂度之和是 $O(3^n)$ 的。我们预处理出：(1) 每个点集 $S$ 的转移代价；(2) 每个点集 $S$ 的入点集合（因为要判断 $T$ 是否属于该集合）。总时间复杂度 $O(2^nn+3^n)$。

## 参考代码

[来这里看！（坏笑）](https://www.cnblogs.com/dysyn1314/p/13951189.html)


---

## 作者：ZnPdCo (赞：5)

考虑单纯形。

这里 $b_i>0$ 看似不是线性规划，实际上因为 $b$ 为整数，所以同等于 $b_i\ge 1$。每条边可以被描述为限制 $1a_u+-1a_v\ge1$。$\min \sum w_ib_i$ 可以被拆分为 $\min\sum(w_i a_u+-w_i a_v)$，然后单纯形做就好了。

因为要求每一个点的取值，所以我不用对偶，直接将每一项系数乘以 $-1$ 也可以达到同样的效果。

有向图的关联矩阵是全幺模矩阵，所以最优解是整数的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define db long double
#define N 20
#define M 400
const db inf = 1e9, eps = 1e-8;
ll n, m;
db a[M][N], ans[N];
ll r[N + M];
mt19937 rnd(114514191);
void pivot(ll l, ll e) {
	swap(r[n + l], r[e]);
	db t = a[l][e];
	a[l][e] = 1;
	for(ll i = 0; i <= n; i ++) {
		a[l][i] /= t;
	}
	for(ll i = 0; i <= m; i ++) if(i != l && abs(a[i][e]) > eps) {
		t = a[i][e]; a[i][e] = 0;
		for(ll j = 0; j <= n; j ++) {
			a[i][j] -= t * a[l][j];
		}
	}
}
void init() {
	while(1) {
		ll l = 0, e = 0;
		for(ll i = 1; i <= m; i ++) {
			if(a[i][0] < -eps && (!l || rnd() % 2)) {
				l = i;
			}
		}
		if(!l) break;
		for(ll i = 1; i <= n; i ++) {
			if(a[l][i] < -eps && (!e || rnd() % 2)) {
				e = i;
			}
		}
		pivot(l, e);
	}
}
void simplex() {
	while(1) {
		ll l = 0, e = 0;
		db mn = inf;
		for(ll i = 1; i <= n; i ++) {
			if(a[0][i] > eps) {
				e = i;
				break;
			}
		}
		if(!e) break;
		for(ll i = 1; i <= m; i ++) {
			if(a[i][e] > eps && a[i][0] / a[i][e] < mn) {
				l = i;
				mn = a[i][0] / a[i][e];
			}
		}
		pivot(l, e);
	}
}
int main() {
	scanf("%lld %lld", &n, &m);
	for(ll i = 1; i <= m; i ++) {
		ll u, v, w;
		scanf("%lld %lld %lld", &u, &v, &w);
		a[i][u] = -1;
		a[i][v] = 1;
		a[i][0] = -1;
		a[0][u] -= w;
		a[0][v] += w;
	}
	for(ll i = 1; i <= n; i ++) {
		r[i] = i;
	}
	init();
	simplex();
	for(ll i = 1; i <= m; i ++) {
		ans[r[n + i]] = a[i][0];
	}
	for(ll i = 1; i <= n; i ++) {
		printf("%.Lf ", ans[i]);
	}
}
```

---

## 作者：daniEl_lElE (赞：4)

不难发现原题等价于每个点的价值 $val_i$ 为入度的 $-w_i$ 与出度的 $w_i$ 之和，$a_{u_i}>a_{v_i}$，求 $\sum_{i=1}^nval_ia_i$ 的最小值。

建反边，考虑 $dp_S$ 表示目前已经填了 $S$ 子集内的值，$\sum_{i=1}^nval_ia_i$ 的最小值。转移可以枚举一个 $T$，然后令 $T$ 中所有 $a_i$ 为 $S$ 中的 $\max+1$。为了转移方便可以简单看做给 $all\oplus S$ 的 $a_i$ 全部加上 $1$，就不用考虑 $S$ 中 $\max$ 的情况了。预处理出哪些 $T$ 是合法的即可。时间复杂度 $O(2^n\times n+3^n)$，实际那个 $3^n$ 跑不满，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
vector<int> vc[19]; 
int cnt[19],tot[262144],rc[262144],deg[19],vis[19],fs[19],minv[262144],lst[262144],ans[19];
signed main(){
	int n,m,ori=0; cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w; cin>>u>>v>>w;
		cnt[u]+=w,cnt[v]-=w;
		vc[v].push_back(u);
		deg[u]++;
		fs[u]|=(1<<(v-1));
	}
	for(int i=1;i<=n;i++) if(!deg[i]) ori|=(1<<(i-1));
	for(int i=0;i<(1<<n);i++){
		for(int j=1;j<=n;j++){
			if((i>>(j-1))&1){
				tot[i]+=cnt[j];
			}
		}
		for(int j=1;j<=n;j++){
			if(!((i>>(j-1))&1)){
				if((i&fs[j])==fs[j]){
					rc[i]|=(1<<(j-1));
				}
			}
		}
	}
	memset(minv,1,sizeof(minv));
	for(int i=ori;i;i=(i-1)&ori){
		minv[i]=tot[i^((1<<n)-1)];
		lst[i]=0;
	}
	for(int i=0;i<(1<<n);i++){
		for(int j=rc[i];j;j=(j-1)&rc[i]){
			if(minv[i|j]>minv[i]+tot[(i|j)^((1<<n)-1)]){
				minv[i|j]=minv[i]+tot[(i|j)^((1<<n)-1)];
				lst[i|j]=i;
			}
		}
	}
	int now=(1<<n)-1,tmp=100;
	while(now){
		for(int i=1;i<=n;i++){
			if(((now>>(i-1))&1)&&(!((lst[now]>>(i-1))&1))){
				ans[i]=tmp;
			}
		}
		tmp--;
		now=lst[now];
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：allenchoi (赞：3)

### 科技：  
最大流（最小割）  
### 思路：  
首先，转换贡献。显然每个点可以得到一个系数，然后权值可以表示为 $\sum_{i=1}^nw_i*a_i$。接着，我们可以让 $a_i$ 都取值于 $[1,n]$ 之内（因为原问是让点权做减法，同加同减差不变）。  
那么，还剩最后一个限制：对于一条有向边 $(u,v)$，要满足 $a_u>a_v$。  
看到这个限制有点像 [P3227切糕](https://www.luogu.com.cn/problem/P3227)，于是考虑相似的建图，跑最小割：  
令节点 $id_{i,j}$ 表示点 $i$ 取值 $j$。从 $id_{i,j}$ 向 $id_{i,j-1}$ 连一条流量为 $w_i\times j$ 的边（割这条的代价等于点 $i$ 取值 $j$ 的贡献；注意这个值可能为负，需要加上一个较大的值调整），$id_{i,n},id_{i,0}$ 分别连接源点，汇点。接着，对于一条有向边 $(x,y)$，从 $id_{x,j}$ 到 $id_{y,j-1}$ 连一条流量为无穷大的边（这条边不可能被割，而且可以保证 $a_x>a_y$）。如图：![](https://cdn.luogu.com.cn/upload/image_hosting/1t5xy5q2.png)  
跑完最小割后，在残量网络上搜索，如果一个点搜得到，说明它前面的边都没被割掉 。  
### 代码：  
~~~cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 410,M = 1e5 + 10;
const ll INF = 1e17,s = 4e15;
int n,m,S,T,tot = 1,cnt,w[N],id[N][N],dep[N],head[N],lst[N],to[M],nxt[M],vis[N];
ll val[M];
queue <int> q;
void add_(int x,int y,ll z)
{
	to[++tot] = y,val[tot] = z;
	nxt[tot] = head[x],head[x] = tot;
}
void add_edge(int x,int y,ll z){add_(x,y,z),add_(y,x,0);}
bool bfs()
{
	memset(dep,0,sizeof(dep));
	dep[S] = 1,lst[S] = head[S],q.push(S);
	for(int x,y;!q.empty();)
	{
		x = q.front(),q.pop();
		for(int i = head[x];i;i = nxt[i])
		{
			y = to[i];
			if(val[i] && !dep[y]) lst[y] = head[y],dep[y] = dep[x] + 1,q.push(y);
		}
	}
	return (dep[T] > 0);
}
ll dfs(int x,ll f)
{
	if(x == T) return f;
	ll ret = 0,tmp;
	for(int i = lst[x],y;i;i = nxt[i])
	{
		y = to[i],lst[x] = i;
		if(val[i] && dep[x] + 1 == dep[y])
		{
			tmp = dfs(y,min(f,val[i]));
			f -= tmp,val[i] -= tmp,val[i ^ 1] += tmp,ret += tmp;
		}
	}
	return ret;
}
ll dinic()
{
	ll flow = 0;
	while(bfs()) flow += dfs(S,INF);
	return flow;
}
void sch(int x)
{
	vis[x] = 1;
	for(int i = head[x],y;i;i = nxt[i])
	{
		y = to[i];
		if(val[i] && !vis[y]) sch(y);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	S = 0,T = n * (n + 1) + 1;
	for(int i = 1;i <= n;i++) for(int j = 0;j <= n;j++) id[i][j] = ++cnt;
	for(int i = 1,x,y,z;i <= m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		w[x] += z,w[y] -= z;
		for(int j = 1;j <= n;j++) add_edge(id[x][j],id[y][j - 1],INF);
	}
	for(int i = 1;i <= n;i++)
	{
		add_edge(S,id[i][n],INF);
		add_edge(id[i][0],T,INF);
		for(int j = 1;j <= n;j++) add_edge(id[i][j],id[i][j - 1],w[i] * j + s);
	}
	dinic();
	sch(S);
	for(int i = 1,v;i <= n;i++)
	{
		for(int j = n;j >= 1;j--) if(vis[id[i][j]]) v = j;
		printf("%d ",v);
	}
	printf("\n");
	return 0;
}
~~~

---

## 作者：Unnamed114514 (赞：0)

首先求出 $b_u=\sum\limits_{E_i=(u,v)}W_i-\sum\limits_{E_i=(v,u)} W_i$。

那么就等价于构造 $a$ 满足每条边起点的 $a$ 比终点的 $a$ 大，且要 $\sum\limits_{i=1}^n a_ib_i$ 最小。

考虑定义 $f_{state,i}$ 表示当前已经选的点状态为 $state$，最大深度为 $i$，那么枚举第 $i+1$ 层的点的状态进行转移，就能得到 $O(n3^n)$ 的做法。

这个是过不了的，考虑优化。

这里有一个经典 trick：提前计算，即如果我们在当前的 $state$ 里面没取的话，就会导致其它的深度都会变大，所以说可以直接加上 $state$ 补集的 $b$ 的和。

注意这个时候应该建反向边。

这样时间复杂度就是 $O(3^n)$ 了。

---

## 作者：CatFromMars (赞：0)

致敬黄队传奇之 WAon24#（

观察约束条件和计算代价条件。

约束条件：$A_u - A_v > 0$ 等价于 $A_u > A_v$，即在 DAG 上任意一条路径的点权单调下降。显然 $A_u \in [1, n]$。这启发我们对图进行分层，对于每个 $A_u = x$ 的 $x$ 作为一层。从第一层到最后一层 $x$ 逐渐递减。第 $i$ 层的点权为 $(n - i + 1)$。

代价条件：$W_iB_i = W_i(A_u - A_v)$，这是一个减法，我们不难想到费用均摊。又因为 $n\le 18$，所以我们大致可以猜测这是一个状压 dp。设 $f_{i, S}$ 为当 $S$ 内的点已经确定后，分了 $i$ 层的最小代价。问题就在于这个“代价”上面——如何均摊贡献？新添加一层的代价是多少？

$W_i(A_u - A_v) = \sum\limits_{ (n - A_u + 1)\le x < (n - A_v + 1)}W_i$。换句话说就是，对于第 $i$ 层 $x$，对于有向边 $(u, v)$。

- $u\in S, v\in S$ 或 $u\not\in S, v\not\in S$，不会产生贡献。
- $u\in S, v\not\in S$，会产生贡献 $W_i$。

我们预处理 $g_S$ 为有向边 $(u, v)$ 中有 $u\in S, v\not\in S$ 的边权和。转移时枚举第 $(i+1)$ 层的点 $S0$，不难得到 $f_{i + 1, S + S0} = f_{i, S} + g_S$。这个式子和 $i$ 没有任何关系，所以可以写成 $f_{S + S0} = f_S + g_S$。其中 $S0$ 是 $S$ 的下一层，因此 $S0$ 的所有点的可能的前继点都应该在 $S$ 内。

时间复杂度上，由于 $S0$ 是 $S$ 的补集的子集。因此取遍所有 $S$ 后 $S0$ 的总数量应该是 $O(3^n)$ 的，时间复杂度也是 $O(3^n)$。

代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 18, M = 800;
int f[(1 << N) + 10], rv[(1 << N) + 10], cost[(1 << N) + 10];
int X[M + 10], Y[M + 10], W[M + 10];
int lowbit(int x) {
	return (x & (-x));
}
struct node {
	int to, val;
	node(int T, int V) {
		to = T, val = V;
	}
};
int n, m;
vector <node> gra[N + 10], ngr[N + 10];
void link(int x, int y, int w) {
	gra[x].push_back(node(y, w));
	ngr[y].push_back(node(x, w));
}
void pre() {
	for(int S = 0; S < (1 << n); S++) {
		for(int i = 1; i <= m; i++)
			if(((S >> X[i]) & 1) && !((S >> Y[i]) & 1))
				cost[S] += W[i];//即 g[S]，边 (u, v, w) 中满足 u 在 S 内，v 不在 S 内的价值
	}
	for(int T = 1; T < (1 << n); T++) {
		int u = log2(lowbit(T));
		rv[T] |= rv[T - lowbit(T)];//集合 T 的中所有点的前驱点集合
		for(int i = 0; i < ngr[u].size(); i++) {
			int v = ngr[u][i].to;
			rv[T] |= (1 << v);
		}
	}
}
int ans[N + 10];
void print(int S, int ind) {//输出方案
	if(!S) return ;
	for(int S0 = S; S0; S0 = (S0 - 1) & S) {
		if(f[S] == f[S - S0] + cost[S - S0] && (rv[S0] & (S - S0)) == rv[S0]) {
			for(int i = 0; i < n; i++)
				if((S0 >> i) & 1)
					ans[i] = ind;

			print(S - S0, ind + 1);
			break;
		}
	}
}
void dp() {
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	int U = (1 << n) - 1, inf = f[2];
	for(int S = 0; S < (1 << n); S++) {
		for(int S0 = (U - S); S0; S0 = (S0 - 1) & (U - S)) {
			if((rv[S0] & S) == rv[S0] && f[S] != inf)//转移，S0 的前继点集应当为 S 的子集
				f[S0 + S] = min(f[S + S0], f[S] + cost[S]);
		}
	}
	print(U, 1);
	int sum = 0;
	for(int i = 0; i < n; i++)
		cout << ans[i] << ' ';
}
int main() {
	cin >> n >> m;
	for(int p = 1; p <= m; p++) {
		cin >> X[p] >> Y[p] >> W[p];
		X[p]--, Y[p]--;
		link(X[p], Y[p], W[p]);
	}
	pre();
	dp();
}
```

---

