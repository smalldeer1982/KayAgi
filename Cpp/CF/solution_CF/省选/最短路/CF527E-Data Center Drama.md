# Data Center Drama

## 题目描述

The project of a data center of a Big Software Company consists of $ n $ computers connected by $ m $ cables. Simply speaking, each computer can be considered as a box with multiple cables going out of the box. Very Important Information is transmitted along each cable in one of the two directions. As the data center plan is not yet approved, it wasn't determined yet in which direction information will go along each cable. The cables are put so that each computer is connected with each one, perhaps through some other computers.

The person in charge of the cleaning the data center will be Claudia Ivanova, the janitor. She loves to tie cables into bundles using cable ties. For some reasons, she groups the cables sticking out of a computer into groups of two, and if it isn't possible, then she gets furious and attacks the computer with the water from the bucket.

It should also be noted that due to the specific physical characteristics of the Very Important Information, it is strictly forbidden to connect in one bundle two cables where information flows in different directions.

The management of the data center wants to determine how to send information along each cable so that Claudia Ivanova is able to group all the cables coming out of each computer into groups of two, observing the condition above. Since it may not be possible with the existing connections plan, you are allowed to add the minimum possible number of cables to the scheme, and then you need to determine the direction of the information flow for each cable (yes, sometimes data centers are designed based on the janitors' convenience...)

## 说明/提示

Picture for the first sample test. The tied pairs of cables are shown going out from the same point.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527E/4abda3017c500d7e7862903d06b135eb9ad26230.png)Picture for the second test from the statement. The added cables are drawin in bold.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527E/01fdb0d798b75335f4d207095e9844e2c00bee6c.png)Alternative answer for the second sample test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527E/1fee03d352ebeccd4924ce3e2bd284be7d51be5e.png)

## 样例 #1

### 输入

```
4 6
1 2
2 3
3 4
4 1
1 3
1 3
```

### 输出

```
6
1 2
3 4
1 4
3 2
1 3
1 3```

## 样例 #2

### 输入

```
3 4
1 2
2 3
1 1
3 3
```

### 输出

```
6
2 1
2 3
1 1
3 3
3 1
1 1
```

# 题解

## 作者：xht (赞：21)

> [CF527E Data Center Drama](https://codeforces.com/contest/527/problem/E)

## 题意

- 给定一张 $n$ 个点 $m$ 条边无向图。
- 你需要加尽可能少的边，然后给所有边定向，使得每一个点的出入度都是偶数。
- 边可以是自环，也可以由重边。
- $n \le 10^5$，$m \le 2 \times 10^5$。

## 题解

若每个点的出入度都是偶数，则每个点的总度数是偶数，而这是一张图存在**欧拉回路**的充要条件。

所以将所有总度数为奇数的点两两相连。

但是并不是所有存在欧拉回路的图都满足条件，还需要满足边数为偶数。

那么随便找一个点加一个自环即可。

这显然是最少的加边方案。

最后跑一个欧拉回路出来，然后隔一条边换一个方向即可。

## 代码

```cpp
const int N = 1e5 + 7, M = 1e6 + 7;
int n, m, h[N], e[M], t[M], tot = 1, d[N], v[M], k;
vi p;

inline void add(int x, int y, int o = 1) {
	e[++tot] = y, t[tot] = h[x], h[x] = tot;
	if (o) ++d[x], ++d[y], add(y, x, 0);
}

void dfs(int x) {
	for (int &i = h[x]; i; i = t[i]) {
		if (v[i]) continue;
		v[i] = v[i^1] = 1;
		int y = e[i];
		dfs(y);
		if ((++k) & 1) print(x, ' '), print(y);
		else print(y, ' '), print(x);
	}
}

int main() {
	rd(n), rd(m);
	for (int i = 1, x, y; i <= m; i++) rd(x), rd(y), add(x, y);
	for (int i = 1; i <= n; i++) if (d[i] & 1) p.pb(i);
	for (ui i = 0; i < p.size(); i += 2) add(p[i], p[i+1]), ++m;
	if (m & 1) add(1, 1), ++m;
	print(m), dfs(1);
	return 0;
}
```

---

## 作者：Nemlit (赞：12)

提供一个$naive$做法。

~~如果你和我一样没有看出这是一个欧拉回路，也许这篇Bolg可以帮助你~~

满足题意显然要所有点的度数都是偶数并且总边数是偶数。

一种暴力是先任意定向，然后选择两个出度为奇数的点任意跑出一条路径，将之间方向取反，然后这两个点度数变为偶数，中间的点度数奇偶性不变。

发现我们只需要给任意一种路径变向即可，所以我们可以弄出原图的一个生成树，然后操作变成每次选择两个度数为奇数的点，然后将这两个点中间的树边全部反向，我们可以用树剖实现。

还有一种搞法是把所有的反祖边随意定向，然后用树边来调整即可。但懒得写代码了……
### $\rm Code$
```cpp
/* This code is written by Nemlit */
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define rep(i, a, b) for(re int i = (a); i <= (b); ++ i)
#define Next(i, u) for(re int i = head[u]; i; i = e[i].next)
#define mem(k, p) memset(k, p, sizeof(k))
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define ls k * 2
#define rs k * 2 + 1
#define N 600005
int head[N], cnt, n, m, U[N], V[N], du[N], size[N], dep[N], tag[N * 4], L[N], id[N];
int fa[N], top[N], tot, vis[N], st[N], dfn[N], son[N], Top;
struct edge { int v, next; }e[N << 1];
il void add(int u, int v, int I) { e[++ cnt] = (edge){v, head[u]}, head[u] = cnt, ++ du[u], id[cnt] = I; }
il void dfs(int u) {
	vis[u] = size[u] = 1;
	Next(i, u) {
		int v = e[i].v;
		if(vis[v]) continue;
		fa[v] = u, dep[v] = dep[u] + 1, dfs(v), L[v] = id[i], size[u] += size[v];
		if(size[son[u]] < size[v]) son[u] = v;
	}
}
il void dfs2(int u, int fr) {
	vis[u] = 1, top[u] = fr, dfn[u] = ++ tot;
	if(son[u]) dfs2(son[u], fr);
	Next(i, u) {
		int v = e[i].v;
		if(!vis[v]) dfs2(v, v);
	}
}
il void pushdown(int k) {
	if(tag[k] == 1) tag[ls] ^= 1, tag[rs] ^= 1, tag[k] = 0;
}
il void modify(int k, int l, int r, int ll, int rr) {
	if(ll <= l && r <= rr) {
		tag[k] ^= 1;
		return;
	}
	pushdown(k);
	int mid = (l + r) >> 1;
	if(ll <= mid) modify(ls, l, mid, ll, rr);
	if(mid < rr) modify(rs, mid + 1, r, ll, rr);
}
il void modify(int u, int v) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		modify(1, 1, n, dfn[top[u]], dfn[u]), u = fa[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	if(u != v) modify(1, 1, n, dfn[v] + 1, dfn[u]);
}
il int query(int k, int l, int r, int ll) {
	if(l == r) return tag[k];
	pushdown(k);
	int mid = (l + r) >> 1;
	if(ll <= mid) return query(ls, l, mid, ll);
	return query(rs, mid + 1, r, ll);
}
signed main() {
	n = read(), m = read();
	rep(i, 1, m) {
		int u = read(), v = read();
		add(u, v, i), add(v, u, i), U[i] = u, V[i] = v;
	}
	rep(i, 1, n) if(du[i] & 1) st[++ Top] = i;
	for(re int i = 1; i <= Top; i += 2) ++ m, add(st[i], st[i + 1], m), add(st[i + 1], st[i], m), U[m] = st[i], V[m] = st[i + 1];
	if(m & 1) U[++ m] = V[m] = 1;
	mem(du, 0), Top = 0, dep[1] = 1, dfs(1), mem(vis, 0), dfs2(1, 1);
	rep(i, 1, m) ++ du[U[i]];
	rep(i, 1, n) if(du[i] & 1) st[++ Top] = i;
	for(re int i = 1; i <= Top; i += 2) modify(st[i], st[i + 1]);
	printf("%d\n", m);
	rep(i, 2, n) if(query(1, 1, n, dfn[i])) swap(U[L[i]], V[L[i]]);
	rep(i, 1, m) printf("%d %d\n", U[i], V[i]);
	return 0;
}
```

---

## 作者：_Felix (赞：5)


  题意：给出一个无向简单图，然后你自己再加一点边，然后你给他们定向，要使得每个点的出度和入度都是偶数。输出加的边最少的任意方案。

  先提出一种构造方案。
  - 我们发现：对于一个有偶数条边、有欧拉路径的图，以 $a\rightarrow b\leftarrow c\rightarrow d\leftarrow ...\rightarrow a$ 的方式定向，可以使得每个点的出度和入度都是偶数。（因为每次访问一个点都会使得它的入度/出度 +2）。
  - 对于一个奇数条边的有欧拉路径的图，随便在某个点加个自环，就变成了一个偶数条边的图。
  - 把原图加成一个有欧拉路径的图：考虑一个图只可能有偶数个奇点，那么把奇点配对相连即可。
     
  梳理一下，就是我们先把奇点配对相连，然后如果有奇数条边就在随便哪个节点加个自环。然后找一条欧拉路径就行了。

正确性：
  - 定向前答案的图一定是一个有欧拉路径的图，否则它存在点度数不是奇数，定向后也不可能入度+出度是偶数。如果原图不是那必须得加边。显然你加的边数已经是最少的了
  - 一个奇数条边的图，定向后不可能所有点都入度+出度是偶数，所以必须加边，那就加一条自环，也是最少的。
  
虽然但是，这篇题解不过审核原因是“数学公式没加LaTeX"，可是哪里有数学公式啊。猜测是“$a\rightarrow b\leftarrow c\rightarrow d\leftarrow ...\rightarrow a$” ？

---

## 作者：chenxia25 (赞：3)

提供一个不用欧拉回路的做法。（其实是自己降智了

首先，「每个点入度和出度都是偶数」等价于「每个点入度是偶数且在无向图上的度数是偶数」。这样，把无向图上每个点度数补齐到偶数是必要的：由于总度数 $2m$ 是偶数，那么度数是奇数的点肯定有偶数个，可以两两配对连边，使加边数达到了下界。

接下来还要满足每个点入度都是偶数。一个必要条件是每个点入度之和（显然也就是 $m$）是偶数。于是如果 $m$ 是奇数，需要再随便加一条边。

此时已经可以给出构造方案了，加边数显然达到下界。不同于其他题解的是，我不是用欧拉回路构造方案的。

先给每条边随意定向，算出每个点的入度。类似于本篇题解第二段地，整出所有入度是奇数的点，由于入度之和是偶数，这样的点一定有偶数个，可以两两匹配。

不能再加边了，那么匹配的每一对怎么调整呢？由于图是连通的，容易发现，找到两点间的任意一条路径（找路径时视为无向图），将上面的边全部反向即可。因为令某个点 $x$ 的一条邻边反向，能使 $x$ 的入度奇偶性翻转；而一条路径上只有两端被翻转了奇数次（一次），中间点都被翻转了偶数次（两次）。

暴力找路径，最坏会达到 $\mathrm O(n^2)$，怎么办呢？dfs 树是个好东西。建出 dfs 树，翻转两点间的树上唯一简单路径，树上差分即可。

---

## 作者：关怀他人 (赞：3)

### CF 527E
#### Solution
首先一个充要条件是每个点的度数为偶数且总边数为偶数。考虑求如何最少增加的边的数量：随便匹配两个奇数度的点，最后判断是否需要再连一条自环即可。

因为上述条件也等价于图中存在一条欧拉回路。最后跑一遍欧拉回路，对于回路上第奇数条边原方向，偶数条边反方向即可，这样保证了每经过一个点，要么它的入度$+2$,要么出度$+2$。

注意使用链式前向星跑欧拉回路时一定要将用过的边删掉，否则会 TLE。

时间复杂度 $\mathcal O(n)$
#### Code
```cpp
int n,m,cnt,len = 1;
int deg[MAXN],vis[MAXN],head[MAXN];

struct Edge{
    int to,next;
} e[MAXN];

void add_edge(int u,int v){
    e[++len] = (Edge){v,head[u]};
    head[u] = len;
    e[++len] = (Edge){u,head[v]};
    head[v] = len;
    deg[u] += 1; deg[v] += 1;
}

void dfs(int u){
    for(int &i = head[u];i;i = e[i].next){
        if(vis[i]) continue;
        vis[i] = vis[i ^ 1] = 1;
        int v = e[i].to; dfs(v);
        cnt += 1;
        if(cnt & 1) printf("%d %d\n",u,v);
        else printf("%d %d\n",v,u);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1,u,v;i <= m;i++)
        scanf("%d%d",&u,&v), add_edge(u,v);
    vector<int> vec;
    for(int i = 1;i <= n;i++)
        if(deg[i] & 1) vec.push_back(i);
    for(int i = 0;i < (int)vec.size();i += 2)
        add_edge(vec[i],vec[i + 1]), m += 1;
    if(m & 1) add_edge(1,1), m += 1;
    printf("%d\n",m); dfs(1);
    return 0;
}
```

---

## 作者：Elma_ (赞：3)

[CF527E Data Center Drama](https://www.luogu.com.cn/problem/CF527E)

## Description

- 给定一张 $n$ 个点 $m$ 条边无向图。
- 你需要加尽可能少的边，然后给所有边定向，使得每一个点的出入度都是偶数。
- 边可以是自环，也可以有重边。
- $n \leq 10^5$，$m \leq 10^5$。

## Solution

如果你熟悉欧拉回路的话，那么你一定知道，每一个点的出入度为偶数是一张图存在欧拉回路的充要条件。

但是仅仅满足这个条件是不够的。首先有一个很显然的结论，在定向后的图中所有点的入度之和等于所有点的出度之和，且恰好等于边数 $m$。因此我们还应该满足最后的边数 $m$ 为偶数，否则，若 $m$ 为奇数，则若干个偶数的和不可能为奇数。

我们可以记录下每一个点的度数，度数为奇数的点之间连边，这样就可以保证每一个点的度数都是偶数了。对于 $m$ 为偶数的情况，就跑一边欧拉回路，然后隔一条边换一个方向，显然这样对每个点的出入度的贡献均为偶数。

那么对于 $m$ 为奇数的情况如何处理呢？因为我们要保证最后的 $m$ 为偶数。

做法很简单，其实只要随便抓一个点加一条自环就可以了。显然这是最优的方案。

## Code

```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define maxn 100005
#define maxm 400005
using namespace std;

inline int read()
{
    char ch = getchar(); int x = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
    return x;
}

struct node
{
	int nxt, to;
}edge[maxm << 1];
int head[maxn], d[maxn];bool vis[maxm << 1];
int n, m, tot = 1, pos;
vector<int> q;

inline void add(int u, int v)
{
	edge[++tot].nxt = head[u];
	edge[tot].to = v;
	head[u] = tot;
}

inline void addedge(int u, int v)
{
	d[u]++, d[v]++, add(u, v), add(v, u);
}

void dfs(int u)
{
	for (int &i = head[u];i;i = edge[i].nxt)
	{
		if (!vis[i])
		{
			int v = edge[i].to;vis[i] = vis[i ^ 1] = true;
			dfs(v);
			if ((++pos) & 1) printf("%d %d\n", u, v);
			else printf("%d %d\n", v, u);
		}
		
	}
}

int main(void)
{
	n = read(), m = read();
	for (int i = 1;i <= m;i++)
	{
		int u = read(), v = read();
		addedge(u, v);
	}
	for (int i = 1;i <= n;i++)
		if (d[i] & 1) q.push_back(i);
	for (int i = 0;i < q.size();i += 2)
		addedge(q[i], q[i + 1]), m++;
	if (m & 1) m++, addedge(1, 1);
	printf("%d\n", m);dfs(1);
	return 0;
}
```


---

## 作者：RainsAFO (赞：3)

题意：

给你一张无向图，求加最少的边，使得构成的有向图中点的出路入度均为偶数。

记度数为奇数的点为奇点，其余为偶点。

首先题目中给的要求是一个图有**欧拉回路**的充要条件。

考虑构造，允许重边自环。

重边可以改变一点出度，一点入度的奇偶性，但是这比较麻烦。

自环可以改变一点出入度的奇偶性，**不改变其是奇点还是偶点**。

只需要在奇点之间连边，多出来的连自环。

最后在图上跑欧拉回路即可

---

## 作者：无意识躺枪人 (赞：3)

# $$\text{一道欧拉回路题}$$

最终的图是欧拉回路，则每个点最终的入度等于出度。

若该回路长为偶数，我们只需要对原图中所有度数为奇数的点依次连无向边，这样原图所有点度数均为偶数

在这个图上跑欧拉，即可得到路径，将其变为有向图的欧拉回路，这样无向图的偶数度数一半为出度，一半为入度

若无向边总数为奇数，随便找点加自环即可

```c
#include<bits/stdc++.h>
#define MAXN 233333
using namespace std;

int n,m;
int u,v;
int tot;//边的总数
int du[MAXN];//每个点的度
vector<int>oo,ans;
multiset<int>gg[MAXN];

inline void AddEdge(int U,int V) {gg[U].insert(V);}

template<class T> inline void read(T &re)
{
	re=0;T sign=1;char tmp;
	while((tmp=getchar())&&(tmp<'0'||tmp>'9')) if(tmp=='-') sign=-1;re=tmp-'0';
	while((tmp=getchar())&&(tmp>='0'&&tmp<='9')) re=re*10+(tmp-'0');re*=sign;
}

void DFS(int x)
{
	while(!gg[x].empty())
	{
		int v=*gg[x].begin();
		gg[x].erase(gg[x].begin());
		gg[v].erase(gg[v].find(x));
		DFS(v);
	}
	ans.push_back(x);
}

int main()
{
	read(n);read(m);
	for(int i=1;i<=m;i++)
	{
		read(u);read(v);
		AddEdge(u,v);
		AddEdge(v,u);
		tot++;
		du[v]++;
		du[u]++;
	}//存图

	for(int i=1;i<=n;i++) if(du[i]&1) oo.push_back(i);//记录边

	for(int i=0;i<(int)oo.size();i+=2)
	{
		int uu=oo[i],vv=oo[i+1];
		AddEdge(uu,vv);
		AddEdge(vv,uu);
		tot++;
	}

	if(tot&1) {tot++,AddEdge(1,1),AddEdge(1,1);}//添加自环边

	DFS(1);printf("%d\n",tot);

	for(int i=0;i<(int)ans.size()-1;i++)
	{
		if(i&1) printf("%d %d\n",ans[i],ans[i+1]);
		else printf("%d %d\n",ans[i+1],ans[i]);
	}

	return 0;
}
```

注意跑欧拉的时候一定要删边，否则会T！

---

## 作者：Purslane (赞：2)

# Solution

感觉联想到欧拉回路有点过于强大了。。。

给出一个不需要欧拉回路的算法。

-----

问题转化为：保证所有点的入度和无向图上的度数都是偶数。

先去掉所有自环，默认把入度增加 $1$。并且将原无向图上度数是奇数的点两两配对并连边。这时候已经满足无向图上的度数都是偶数。而注意到

$$
m = \sum_{u \in V} \mathrm{degin}_u
$$

（这里的 $m$ 是增加配对边之后的边数，包括之前删掉的自环）

因此如果 $2 \nmid m$，还需要增加一条边，方便起见就增加自环，然后再把它去掉。

容易发现，我们新增的边都是必要的。下面构造地证明解一定存在。

-------

随便求出原图的一棵 DFS 树。

将非树边的指向随便定。

自底向上确定每条树边的方向。具体的，如果儿子的入度为奇数，树边就指向儿子，否则指向父亲。

而根节点的入度等于 $m$ 减去其他所有点的入度，必定为偶数。

因此我们找到了一个合法的方案。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,m,deg[MAXN],dout[MAXN],vis[MAXN],dep[MAXN];
vector<int> G[MAXN],T[MAXN];
vector<pair<int,int>> ans;
void dfs(int u,int f) {
	dep[u]=dep[f]+1,vis[u]=1;	
	int cnt=0;
	for(auto v:G[u]) {
		if(v==f) if(!cnt) {cnt=1;continue;}
		if(vis[v]&&dep[v]<dep[u]) ans.push_back({u,v}),dout[u]++;	
		if(vis[v]) continue ;
		T[u].push_back(v),dfs(v,u);
	}
	return ;
}
void solve(int u,int f) {
	for(auto v:T[u]) {
		solve(v,u);
		if(dout[v]&1) ans.push_back({v,u});
		else ans.push_back({u,v}),dout[u]++;
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {
		int u,v;
		cin>>u>>v;
		if(u==v) {
			ans.push_back({u,v}),dout[u]++;
			continue ;	
		}
		G[u].push_back(v),G[v].push_back(u),deg[u]++,deg[v]++;
	}
	vector<int> vc;
	ffor(i,1,n) if(deg[i]&1) vc.push_back(i);
	ffor(i,1,vc.size()/2) {
		int u=vc[2*i-2],v=vc[2*i-1];
		G[u].push_back(v),G[v].push_back(u);	
		m++;
	}
	if(m&1) m++,ans.push_back({1,1}),dout[1]++;
	dfs(1,0);
	solve(1,0);
	cout<<m<<'\n';
	for(auto pr:ans) cout<<pr.first<<' '<<pr.second<<'\n';
	return 0;
}
```

---

## 作者：Leasier (赞：2)

每个点度数为偶数意味着看成无向图后这张图有**欧拉回路**。

考虑抓出度数为奇数的点两两连边，这样每个点的度数就都是偶数。

但是考虑到重边的问题，实际上此时总边数可能为偶数。此时我们需要再加上一个自环。

最后在这张图上跑出一条欧拉回路，相邻边定向相反即可。

代码：
```cpp
#include <stdio.h>

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 1;
bool op = true;
int deg[100007], head[100007], bucket[100007];
bool vis[600007];
Edge edge[600007];

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs(int u){
	for (int &i = head[u]; i != 0; i = edge[i].nxt){
		if (!vis[i]){
			int x = edge[i].end;
			vis[i] = vis[i ^ 1] = true;
			dfs(x);
			if (op){
				printf("%d %d\n", u, x);
			} else {
				printf("%d %d\n", x, u);
			}
			op = !op;
		}
	}
}

int main(){
	int n, m, cnt = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		deg[a]++;
		deg[b]++;
		add_edge(a, b);
		add_edge(b, a);
	}
	for (int i = 1; i <= n; i++){
		if (deg[i] % 2 == 1) bucket[++cnt] = i;
	}
	for (int i = 1; i <= cnt; i += 2){
		int u = bucket[i], v = bucket[i + 1];
		m++;
		add_edge(u, v);
		add_edge(v, u);
	}
	if (m % 2 == 1){
		m++;
		add_edge(1, 1);
		add_edge(1, 1);
	}
	printf("%d\n", m);
	dfs(1);
	return 0;
}
```

---

## 作者：81179332_ (赞：2)

若每个点的出入度都是偶数，则每个点的总度数都是偶数，这是无向图存在欧拉回路的充要条件。

所以我们首先将所有度数为奇数的边之间连一条边

如果边数为奇数，因为将无向图定向后，$\text{出度和}=\text{入度和}=m$，而偶数的和不可能为奇数，所以不可能满足条件，我们需要加入一个自环使得边数为偶数

最后我们跑出来一条欧拉回路，我们使路径上的边正向与反向交替，则每经过一个点，该点入度/出度 $+2$，满足入度与出度均为偶数

```cpp
//timeuse:15min
const int N = 100010,M = 400010;
int n,m,d[N],id;bool vis[M << 1];
struct edge { int to,nxt; }e[M << 1];int head[N],cnt = 1;
void add(int u,int v) { e[++cnt].to = v,e[cnt].nxt = head[u],head[u] = cnt; }
void add_edge(int u,int v) { d[u]++,d[v]++,add(u,v),add(v,u); }
void dfs(int u)
{
	for(int &i = head[u],v;i;i = e[i].nxt) if(!vis[i])
	{
		v = e[i].to,vis[i] = vis[i ^ 1] = 1;
		dfs(v);
		if((++id) & 1) pprint(u),fprint(v);
		else pprint(v),fprint(u);
	}
}
int main()
{
	n = read(),m = read();
	for(int i = 1;i <= m;i++) add_edge(read(),read());
	vector<int> p;
	for(int i = 1;i <= n;i++) if(d[i] & 1) p.push_back(i);
	for(int i = 0;i < p.size();i += 2) add_edge(p[i],p[i + 1]),m++;
	if(m & 1) m++,add_edge(1,1);
	fprint(m),dfs(1);
	return 0;
}
```

---

## 作者：lahlah (赞：1)

https://www.luogu.com.cn/problem/CF527E

要注意图是联通的

首先要知道

**若每个点的出入度都是偶数，则每个点的总度数是偶数，是一张图存在欧拉回路的充要条件。**

然后对于原图，先把总度数是奇数的两两相连

就保证了存在欧拉回路

但这样不能保证每个点出度和出度都是偶数

可能存在每个点的边数都是偶数，但是总边数为奇数

如：

1-2 ， 2-3， 1-3

所以要随便找一个点连个自环，这样就能保证总边数是偶数



跑一边欧拉回路，边的方向交替，这样就能保证对于一个点再出去的这两条边要么同时是出边，要么同时是入边

code:


```cpp
#include<bits/stdc++.h>
#define N 800005
using namespace std;
struct edge {
	int v, nxt;
} e[N << 1];
int p[N], eid;
void init() {
//	memset(p, -1, sizeof p);
	eid = 2;
}
void insert(int u, int v) {
	e[eid].v = v;
	e[eid].nxt = p[u];
	p[u] = eid ++;
}
int n, m, in[N], vis[N << 1], gs, sz, a[N];
void dfs(int u) {
	for(int &i = p[u]; i; i = e[i].nxt) {
		if(vis[i]) continue;
		vis[i] = vis[i ^ 1] = 1;
		int v = e[i].v;
		dfs(v);
		if((++ gs) & 1) printf("%d %d\n", u, v);
		else printf("%d %d\n", v, u);//交替定向 
		//dfs(v);
	}
}
int main() {
	init();
	scanf("%d%d", &n ,&m);
	for(int i = 1; i <= m; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		insert(u, v);
		insert(v, u);
		in[u] ++, in[v] ++;
	}
	for(int i = 1; i <= n; i ++) if(in[i] & 1) a[++ sz] = i;
	for(int i = 1; i <= sz; i += 2) insert(a[i], a[i + 1]), insert(a[i + 1], a[i]), ++ m;
	if(m & 1) insert(1, 1), insert(1, 1), ++ m;
	printf("%d\n", m);
	dfs(1); 
	return 0;
}

```
主要是看到度数偶数要联想到欧拉回路，做这种题思维要跳跃一些



---

## 作者：ollo (赞：1)

## 题意

- 给定一张 $n$ 个点 $m$ 条边无向图。
- 你需要加尽可能少的边，然后给所有边定向，使得每一个点的出入度都是偶数。
- 边可以是自环，也可以有重边。
- $n \le 10^5$ ，$m \le 2 \times 10^5$。

## 题解

### 加边

**每个点的总度数是偶数，即入度加出度的和是偶数，是一张图存在欧拉回路的充分必要条件。**

然后对于原图，先把度数和为奇数的边进行连接，**注意不是两两相连，而是相邻点相连**，这样就保证了存在欧拉回路。但这样不能保证每个点出度和出度都是偶数。比如 $1-2$ ,$2-3$ ,$3-1$,总度数为偶数，但每个点的出入度不可能同时为偶数。所以，在这个基础上，还要在总边数为奇数时给任意一个点连自环。

### 定向
跑一边欧拉回路，边的方向交替（如第一条边为 $u$ 连向 $v$,第二条边为 $v$ 连向 $u$），这样就能保证对于一个点加上边后出度和入度还是偶数。

### 代码
```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>//火车头卡常
#define M 400010
#define N 100010

using namespace std;

struct S{
	int nxt, to;
}a[M << 1];
int d[N], head[N], tot = 1;

int z, n, m;
bool vis[M << 1];
vector<int> g;

inline int read(){//快读
    char ch = getchar(); int x = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
    return x;
}

inline void dfs(int u){//定向
	for(int i = head[u]; i; i = a[i].nxt){
		if(!vis[i]){
			int v = a[i].to;
			vis[i] = vis[i ^ 1] = 1;
			dfs(v);
			if((++z) & 1){
				printf("%d %d\n", u, v);
			}
			else{
				printf("%d %d\n", v, u);
			}
		}
	}
}



inline void add(int u, int v){
	a[++tot].nxt = head[u];
	a[tot].to = v;
	head[u] = tot;
}

inline void adda(int u, int v){//建图
	d[u]++;d[v]++;
	add(u, v);add(v, u);
}

int main(){
	n = read();m = read();
	for(int i = 1; i <= m; i++){
		int u, v;
		u = read();v = read();
		adda(u, v);
	}
	for(int i = 1; i <= n; i++){
		if(d[i] & 1){
			g.push_back(i);
		}
	}
	for(int i = 0; i < g.size(); i += 2){
		adda(g[i], g[i + 1]);
		m++;
	}
	if(m & 1){
		m++;
		adda(1, 1);
	}//加边
	printf("%d\n", m);
	dfs(1);
	return 0;
}
```


---

