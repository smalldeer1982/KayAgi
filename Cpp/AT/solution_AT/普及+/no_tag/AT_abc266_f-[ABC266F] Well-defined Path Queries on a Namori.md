# [ABC266F] Well-defined Path Queries on a Namori

## 题目描述

给定一张有 $N$ 个点、$N$ 条边的简单连通无向图和 $Q$ 次询问，对于每次询问，给定 $x_i,y_i$，表示两点的编号，请你回答第 $x_i$ 个点和第 $y_i$ 个点之间是否**有且仅有**一条简单路径。

+ 什么是简单路径？

如果路径上的各顶点均不重复，则称这样的路径为简单路径。

## 说明/提示

对于 $30\%$ 的数据，$N \le 100$，$Q \le \frac{N(N-1)}{2}$；

对于 $100\%$ 的数据，$3 \le N \le 2 \times 10^5$，$1 \le u_i<v_i \le N$，$1 \le Q \le 2 \times 10^5$，$1 \le x_i < y_i \le N$，保证图没有重边或自环，且给定询问均不重复。

翻译 by @CarroT1212

## 样例 #1

### 输入

```
5
1 2
2 3
1 3
1 4
2 5
3
1 2
1 4
1 5```

### 输出

```
No
Yes
No```

## 样例 #2

### 输入

```
10
3 5
5 7
4 8
2 9
1 2
7 9
1 6
4 10
2 5
2 10
10
1 8
6 9
8 10
6 8
3 10
3 9
1 10
5 8
1 10
7 8```

### 输出

```
Yes
No
Yes
Yes
No
No
Yes
No
Yes
No```

# 题解

## 作者：yinhy09 (赞：2)

## 题目分析

一个 $n$ 个点 $n$ 条边的图，显然就是一个基环树。那么我们可以采用基环树经典操作——记录每一个点所在的树是从环上哪一个节点引出来的。如果询问的两个节点属于同一棵树，那么就是只有一条简单路径的（输出 `Yes`），否则就是有两条（在环上往两个方向走）。

基环树的基本操作这里就省略啦（QwQ

## AC Code :

```cpp
// Problem: F - Well-defined Path Queries on a Namori
// Contest: AtCoder - AtCoder Beginner Contest 266
// URL: https://atcoder.jp/contests/abc266/tasks/abc266_f
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Author: Luogu @yinhy09(575320),Codeforces @yinhy09

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll read()
{
	char c;
	ll x=0;
	ll f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll n;
const int maxn=2e5+5;
struct Edge
{
	ll v,next;
}e[maxn<<1];
ll h[maxn],fa[maxn];
ll tot=0;
bitset<maxn>in;
void addEdge(ll u,ll v)
{
	tot++;
	e[tot].v=v;
	e[tot].next=h[u];
	h[u]=tot;
}
ll found=0;
void dfs(ll u,ll f)
{
	if(found==1)return;
	fa[u]=f;
	for(int i=h[u];i;i=e[i].next)
	{
		if(found==1)return;
		ll v=e[i].v;
		if(v==f)continue;
		if(fa[v])
		{
			while(u!=v)
			{
				in.set(u);
				u=fa[u];
			}
			in.set(v);
			found=1;
			return;
		}
		else dfs(v,u);
	}
}
ll pre[maxn],vis[maxn];
void dfss(ll u)
{
	for(int i=h[u];i;i=e[i].next)
	{
		if(in[e[i].v]==1)continue;
		if(vis[e[i].v]==1)continue;
		pre[e[i].v]=pre[u];
		vis[e[i].v]=1;
		dfss(e[i].v);
	}
}
ll u,v;
ll q;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		u=read(),v=read();
		addEdge(u,v),addEdge(v,u);
	}
	dfs(1,1);
	for(int i=1;i<=n;i++)
	{
		if(in[i]==1)pre[i]=i,vis[i]=1,dfss(i);
	}
/*	for(int i=1;i<=n;i++)cout<<pre[i]<<" ";
	cout<<endl;*/
	q=read();
	while(q--)
	{
		u=read(),v=read();
		if(pre[u]!=pre[v])cout<<"No"<<endl;
		else cout<<"Yes"<<endl;
	}
	return 0;
}
```

谢谢观看喵~

---

## 作者：Nicrobot (赞：2)

注意到两点 $a,b$ 路径唯一，当且仅当该路径不经过环上的任何边，否则，一定可以反着走另外半圈。

因为边数 $m=n$，只有一个环。我们不用 Tarjan 或者其他东西，用 DFS 就可以找环了，找完求出所有在环上的点。

找出来环后，显然点 $x$ 到点 $y$ 满足简单路径条数唯一，则这两个点一定都是任意一个环上的点，在 **不经过环上的其它点** 的条件下，就能到达的点。考虑对于所有环上的点 $x$，将它挂着的那些点（不经过环上的其它点就能到达的点）给染上色，颜色即为 $x$。则颜色相同的点之间简单路径唯一，反之不唯一。

时间复杂度 $O(n)$ 。

[提交记录](https://atcoder.jp/contests/abc266/submissions/37443414)

---

## 作者：igAC (赞：2)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc266_f)

[ATlink](https://atcoder.jp/contests/abc266/tasks/abc266_f)

简要题意：

给定一棵基环树，问两点之间是否只有一条简单路径。

# $\text{Solution}$

简单题，考察基环树的基本操作以及一点点思维。

考虑合法的条件是什么。

我们发现如果这条路径如果经过环上的不止一个点，那么一定有一条从环的另一边绕过来的路径也可以到达。

我们可以记录每个点在环上的祖先，合法条件就是是否是同一个祖先，

时间复杂度，空间复杂度均是 $O(n)$。

# $\text{Solution}$

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,q,head[N],tot,fa[N];
bool vis[N],cir[N];
struct Edge{
	int to,nxt;
}e[N<<1];
void add_edge(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
void gettag(int x){
	int now=x;cir[x]=true;x=fa[x];
	while(now!=x){
		cir[x]=true;
		x=fa[x];
	}
}
void dfs1(int x,int f){
	if(vis[x]){
		gettag(x);
		return;
	}
	vis[x]=true;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f) continue;
		fa[y]=x;
		dfs1(y,x);
	}
}
void dfs2(int x,int f){
	if(!cir[x]) fa[x]=fa[f];
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f || cir[y]) continue;
		dfs2(y,x);
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		int x=read(),y=read();
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(1,0);
	memset(fa,0,sizeof(fa));
	for(int i=1;i<=n;++i){
		if(cir[i]){
			fa[i]=i;
			dfs2(i,0);
		}
	}
	q=read();
	while(q--){
		int x=read(),y=read();
		puts(fa[x]==fa[y]?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：lsj2009 (赞：1)

### Problem

给定一棵 $n$ 个点的基环树，有 $q$ 次询问，每次询问点对 $(u,v)$ 之间的简单路径是否唯一。

link-><https://atcoder.jp/contests/abc266/tasks/abc266_f>。

### Solution

首先考虑两点间路径唯一的充分必要条件是什么。正难则反，不妨想一想路径不唯一的条件是什么？更具体的说，如果路径不唯一，那另一条路径是什么？是的，容易想到，就是在环上，我们可以考虑直接由两点间的最短路径走过去，也可以绕环一圈，然后在另一端走过去。这样，我们则需要判断两点间的最短路径是否会经过该环。考虑缩点，然后由环为根节点，这样判断这两点是否在根节点下的同一子树即可。这一点很好判断，我们只需要预处理处每个节点在哪一棵子树即可。但是，还有一种特殊情况：如果经过的只是环的某一个节点，则我们绕环一圈，最终又会绕回那个节点，而我们在进入环的时候已经路过了这个节点，简单路径的定义是不能走重复的点、边，这与刚才的情况不符。所以，我们还需要记录每一棵子树是由那个节点进入环的。值得一提的是，由于同一棵子树进入环的节点相同，所以我们并不需要记录某节点属于某棵子树，只需要记录他所在的那棵子树进入环的节点即可。

做法相对正解复杂，但可拓展性强，应该可以拓展至任意无向图。

### Code


``` cpp
#include<bits/stdc++.h>
#define F first
#define S second
#define mk make_pair
#define INF 0x7fffffff
#define inf 0x3f3f3f3f
#define inf2 0x3f3f3f3f3f3f3f3f
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;++a)
#define _rep(a,b,c) for(int a=b;a>=c;--a)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e5+5;
int head[N],n,tot=1,root;
struct node {
	int from,to,nxt;
}; node edge[N<<1];
void add_edge(int u,int v) {
	++tot, edge[tot]={u,v,head[u]}, head[u]=tot;
}
int bridge[N<<1],dfn[N],low[N],cnt;
void tarjan(int u,int t) {
	dfn[u]=low[u]=++cnt;
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(!dfn[v]) {
			tarjan(v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u])
				bridge[i]=bridge[i^1]=1;
		} else if(i!=(t^1))
			low[u]=min(low[u],dfn[v]);
	}
}
int color,w[N],dcc[N],used[N];
int num[N];
void dfs(int u) {
	used[u]=1;
	++w[color];
	num[color]=u;
	dcc[u]=color;
	if(w[color]!=1)
		root=color;
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(!bridge[i]&&!used[v])
			dfs(v);
	}
}
int head2[N],to[N],tot2;
node edge2[N<<1];
void add_edge2(int u,int v) {
	edge2[++tot2]={u,v,head2[u]}, head2[u]=tot2;
}
void build() {
	_for(i,1,n) {
		int u=edge[i*2].from,v=edge[i*2].to;
		if(dcc[u]==root)
			to[v]=u;
		if(dcc[v]==root)
			to[u]=v;
		if(dcc[u]!=dcc[v])
			add_edge2(dcc[u],dcc[v]),add_edge2(dcc[v],dcc[u]);
	}
}
void dfs2(int u,int _fa) {
	for(int i=head2[u];i;i=edge2[i].nxt) {
		int v=edge2[i].to;
		if(v!=_fa) {
			to[num[v]]=to[num[u]]; dfs2(v,u);
		}
	}
}
signed main() {
	scanf("%d",&n);
	_for(i,1,n) {
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	tarjan(1,0);
	_for(i,1,n) {
		if(!dcc[i]) {
			++color; dfs(i);
		}
	}
//	_for(i,1,n)
//		printf("i = %d dcc = %d\n",i,dcc[i]);
	build();
//	_for(i,1,n)
//		printf("i = %d %d\n",i,to[i]);
	for(int i=head2[root];i;i=edge2[i].nxt) {
		int v=edge2[i].to; dfs2(v,root);
	}
	_for(i,1,n) {
		if(dcc[i]==root)
			to[i]=i;
	}
	int q;
	scanf("%d",&q);
//	_for(i,1,n)
//		printf("i = %d %d\n",i,to[i]);
	_for(i,1,q) {
		int u,v;
		scanf("%d%d",&u,&v);
		puts(to[u]==to[v]? "Yes":"No");
	}
	return 0;
}



```

---

## 作者：CQ_Bob (赞：0)

## 分析

对于两个点，如果某条路径经过了环上的点，则一定会有 $\ge 2$ 条简单路径。这很显然。

考虑将环中节点进行标记，然后通过前缀和求出来节点 $i$ 到根节点这条路径上会经过多少个环中节点，记为 $s_i$。那么，对于每次询问 $x,y$，如果 $s_x+s_y-2\times s_{lca_{x,y}} \ge 1$，则有 $\ge 2$ 条简单路径。其中 $s_x+s_y-2\times s_{lca_{x,y}}$ 是用来计算 $x\to y$ 的某条路径上经过环中节点数量。

注：对于基环树，记录环上某两个直接相连的点 $s,t$，不将其连边就可以使它变成一棵树。

## 代码

[Link](https://atcoder.jp/contests/abc266/submissions/47548664).

---

## 作者：Tibrella (赞：0)

题目中提到 $n$ 个点，$n$ 条边且联通，无重边无自环，容易发现是一棵基环树。  

基环树就是树多了一条边，形成的图仅有一个环。这个环上的每个点都是一棵环外的树的根节点。

然后我们考虑两个点什么时候简单路径不唯一，显然在同一棵环外树上的两点简单路径唯一。容易想到，如果两个点路径有一部分在环上，则他们的简单路径不唯一（在环上可以向两个方向走，最后能到达同一个点）。

我们可以给环上的每一棵树编号，如果两点不在一棵树内则输出 `No`，否则输出 `Yes`。

这里采用了拓扑排序找环的方法，对于每一个度数为 $0$ 的点为起始点进行拓扑排序，最后剩下度数为 $2$ 的点即是环上的点。然后遍历环上每个点对应的树，给同一棵树内的点编同样的号即可。

判断两点是否在同一棵树即为判断两点编号是否相同。

~~人傻常数大~~
~~模拟赛赛时空间开了 1/2~~


```cpp
#include <iostream>
#include <vector>

using std::cin;
using std::cout;

using i32 = int;
using i64 = long long;

#define N 200001

std::vector<i32> g[N];
i32 deg[N];

#include <queue>

i32 id[N], idx;

void topo(const i32 &u) {
    std::queue<i32> q;
    q.emplace(u);
    while (q.size()) {
        i32 u = q.front();
        q.pop();
        --deg[u];
        for (const auto &v : g[u])
            if (--deg[v] == 1) q.emplace(v);
    }
}

void dfs(const i32 &u, const i32 &fa) {
    id[u] = idx;
    for (const auto &v : g[u])
        if (v != fa && deg[v] <= 1) dfs(v, u);
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i32 n;
    cin >> n;
    for (i32 i = 1; i <= n; ++i) {
        i32 u, v;
        cin >> u >> v;
        ++deg[u], ++deg[v];
        g[u].emplace_back(v), g[v].emplace_back(u);
    }

    for (i32 i = 1; i <= n; ++i)
        if (deg[i] == 1) topo(i);

    for (i32 i = 1; i <= n; ++i)
        if (deg[i] > 1) ++idx, dfs(i, 0);

    i32 q;
    cin >> q;
    while (q--) {
        i32 x, y;
        cin >> x >> y;
        cout << ((id[x] == id[y]) ? "Yes\n" : "No\n");
    }

    return 0;
}
```

---

