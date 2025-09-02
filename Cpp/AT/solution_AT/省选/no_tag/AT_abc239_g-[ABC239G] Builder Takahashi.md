# [ABC239G] Builder Takahashi

## 题目描述

给定一张 $n$ 个点 $m$ 条边的连通无向图，要求在某些点（不能为 $1$ 号点或者 $n$ 号点）设立障碍，在 $i$ 号点建立障碍的费用为 $c_i$，要使得 $1$ 号点和 $n$ 号点不连通，求最小花费的方案。

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 5
2 4
4 5
0 8 3 4 0```

### 输出

```
7
2
3 4```

## 样例 #2

### 输入

```
3 2
1 2
2 3
0 1 0```

### 输出

```
1
1
2```

## 样例 #3

### 输入

```
5 9
1 2
1 3
1 4
2 3
2 4
2 5
3 4
3 5
4 5
0 1000000000 1000000000 1000000000 0```

### 输出

```
3000000000
3
2 3 4```

# 题解

## 作者：CrTsIr400 (赞：4)

你发现一个点可以拆成两个点，中间连一条代价为 $c_i$ 的边，然后就转成最小割做就行了。

大家可以手写网络流，也可以想我一样用 AtCoder Library 的 `maxflow`。

这里稍微讲一下它输出最小割残量网络的功能：有一个函数 `mincut`，返回类型为 `vector<bool>`，代表每个节点是否能通过网络流的 $s$ 点到达。

然后我只需要判断 $i$ 点在残量网络中，且 $i+n$ 号点不在残量网络，那么这条边就被割掉了。

这个 `mincut` 函数的功能或许可以启发我们残量网络的代码实现。

```cpp
#include<bits/stdc++.h>
#include<atcoder/maxflow>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
I n,m;
#define ade add_edge
const LL Linf=1ll<<60;
vector<I>v;
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	atcoder::mf_graph<LL>g(n+n+1);
	fo(i,1,m){I u,v;cin>>u>>v;
		g.ade(u+n,v,Linf);
		g.ade(v+n,u,Linf);}
	fo(i,1,n){I x;cin>>x;
		g.ade(i,i+n,x);}
	printf("%lld\n",g.flow(n+1,n));
	vector<bool>ans=g.min_cut(n+1);
	fo(i,1,n)if(ans[i]&&!ans[i+n])v.push_back(i);
	printf("%d\n",v.size());
	for(I i:v)printf("%d ",i);
	return 0;}
```

---

## 作者：ethan0328 (赞：1)

## 题意

求删除一些点使 $1$ 和 $n$ 不连通的最小代价和方案。

## 思路

首先是删点，所以拆点，把每个点拆成 $i$ 和 $i+n$，$i$ 到 $i+n$ 连边的容量为删点的代价。

然后根据最大流最小割定理，这张图的最大流即为最小割，即答案。

最后考虑输出方案。发现残图从 $1$ 开始可以到达的点与无法到达的点间的边应被删除，所以只要 $i$ 和 $i+n$ 一个可到达，一个无法到达，$i$ 就会被删除。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
struct edge
{
	int next,to,mx;
};
int n,m,ind=1,cnt,out[N],a[N],head[N];
edge e[N*N];
int pos[N],now[N];
queue<int> q;
void add(int x,int y,int z)
{
	e[++ind].to=y;e[ind].mx=z;
	e[ind].next=head[x];head[x]=ind;
}
bool bfs(int s,int t)
{
	int x,y;
	for(int i=1;i<=n*2;i++)
	{
		pos[i]=-1;
		now[i]=head[i];
	}
    while(!q.empty())
    {
        q.pop();
    }
	pos[s]=1;
	q.push(s);
	while(!q.empty())
	{
		x=q.front();
		q.pop();
		for(int i=head[x];i;i=e[i].next)
		{
			y=e[i].to;
			if(pos[y]!=-1||!e[i].mx)
			{
				continue;
			}
			pos[y]=pos[x]+1;
			q.push(y);
			if(y==t)
			{
				return 1;
			}
		}
	}
	return 0;
}
int dfs(int x,int flow,int t)
{
	if(x==t)
	{
		return flow;
	}
	int rst=flow;
	for(;now[x];now[x]=e[now[x]].next)
	{
		int p=now[x];
		int y=e[p].to;
		if(pos[y]!=pos[x]+1||!e[p].mx)
		{
			continue;
		}
		int v=dfs(y,min(e[p].mx,rst),t);
		if(!v)
		{
			pos[y]=-1;
		}
		e[p].mx-=v;
		e[p^1].mx+=v;
		rst-=v;
		if(!rst)
		{
			break;
		}
	}
	return flow-rst;
}
int dinic(int s,int t)
{
	int ret=0;
	while(bfs(s,t))
	{
		ret+=dfs(s,2e18,t);
	}
	return ret;
}
signed main()
{
	int x,y;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		add(x+n,y,2e18);
		add(y,x+n,0);
		add(y+n,x,2e18);
		add(x,y+n,0);
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		add(i,i+n,a[i]);
		add(i+n,i,0);
	}
	cout<<dinic(1+n,n)<<"\n";
	for(int i=2;i<n;i++)
	{
		if(pos[i]==-1&&pos[i+n]!=-1||pos[i]!=-1&&pos[i+n]==-1)
		{
			out[++cnt]=i;
		}
	}
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++)
	{
		cout<<out[i]<<" ";
	}
}
```


---

## 作者：Link_Cut_Y (赞：0)

简单网络牛蹄。

拆点，拆出来两个点分别为出点和入点。从出点到入点连接容量为 $c_i$ 的边。以 $1$ 号点的出点为源点，$n$ 号点的入点为汇点做最小割即可。

对于方案的输出：对于最终选上的点，在最后一次 bfs 建分层图后，一定有入点可以被遍历到，出点不可以被遍历到。输出即可。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <vector>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )

using namespace std;

const int INF = 2e9;
const int N = 200010;
int h[N], e[N], ne[N], f[N], idx = 1;
int n, m, S, T, cur[N], d[N], a[N], b[N], c[N];
vector<int> ans;
void add(int a, int b, int c) {
    e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx, f[idx] = c;
    e[ ++ idx] = a, ne[idx] = h[b], h[b] = idx, f[idx] = 0;
}
bool bfs() {
    queue<int> q; memcpy(cur, h, sizeof cur); 
    memset(d, -1, sizeof d); q.push(S); d[S] = 0;
    while (q.size()) {
        auto u = q.front(); q.pop(); if (u == T) return 1;
        for (int i = h[u]; i; i = ne[i]) {
            int v = e[i]; if ((~d[v]) || (!f[i])) continue;
            d[v] = d[u] + 1; cur[v] = h[v], q.push(v);
        }
    } return 0;
}
int dfs(int u, int F) {
    if (u == T) return F; int now = 0;
    for (int &i = cur[u]; i; i = ne[i]) {
        int v = e[i]; if (d[v] == d[u] + 1 and f[i]) {
            if (now = dfs(v, min(F, f[i]))) {
                f[i] -= now, f[i ^ 1] += now; return now;
            }
        }
    } return 0;
}
int dinic(int s = 0, int nw = 0) {
    while (bfs()) while (nw = dfs(S, INF)) s += nw; return s;
}
signed main() {
    scanf("%lld%lld", &n, &m);
    rep(i, 1, m) scanf("%lld%lld", &a[i], &b[i]);
    rep(i, 1, n) scanf("%lld", &c[i]);
    rep(i, 1, n) add(i, i + n, c[i]);
    rep(i, 1, m) add(a[i] + n, b[i], INF), add(b[i] + n, a[i], INF);
    S = 1 + n, T = n; printf("%lld\n", dinic());
    rep(i, 2, n - 1) if ((~d[i]) and (d[i + n] == -1))
    	ans.push_back(i);
    sort(ans.begin(), ans.end()); printf("%lld\n", (int)ans.size());
    for (auto i : ans) printf("%lld ", i); return 0;
}
```

---

## 作者：junxis (赞：0)

# Perface
最小割求方案板子题。
# Analysis
首先，我们拆点，将点权转化为原点和虚点之间的一条可割边，而原图中的所有边都是不可割边，即边权为无穷。

形式化地，记网络的边集为 $F$，原图 $G=(V,E)$。

$\forall (u,v)\in E:F \gets F \cup (u',v,+\infty)\cup(v,u',+\infty)$。

$\forall u\in V:F \gets F \cup (u,u',c_u)\cup(u',u,c_u)$。

这样我们就建好了图，用 dinic 求出最小割即可。

接着，我们需要求出方案。

不妨记最终图中与原点联通的点集为 $S$，与汇点联通的点集为 $T$。

显然，根据最小割的定义，方案即为所有 $(u,v) \in E$ 满足 $u\in S, v \in T$。

考虑 dinic 的最后一次增广，此次增广的网络已然不连通，那么所有被增广到的点即为 $S$ 集，没被增广到的即为 $T$ 集。

至此，问题解决。

# CODE
```cpp
/**
 * 	  author: 	 spoonjunxi
 * 	  created:   2022-12-24 14:05:02
**/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#ifdef LOCAL
#include "C:/algo/debug.h"
#else
#define debug(...) 42
#endif

const int V = 210, E = 11000;
template<typename T> 
struct FlowGraph {
    int s, t, vtot, etot, dis[V], cur[V], head[V];
    struct edge {
        int v, nxt;
        T f; 
    } e[E * 2];

    void addedge(int u, int v, T f, T f2 = 0) {
        e[etot] = {v, head[u], f}; head[u] = etot++;
        e[etot] = {u, head[v], f2}; head[v] = etot++;
    }
    
    bool bfs() {
        for (int i = 1; i <= vtot; i++) {
            dis[i] = 0;
            cur[i] = head[i];
        }
        queue<int> q;
        q.push(s); dis[s]=1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; ~i; i = e[i].nxt) {
                int v = e[i].v;
                if (e[i].f > 0 && !dis[v]) {
                    dis[v] = dis[u] + 1;
                    if (v == t) return true;
                    q.push(v);
                }
            }
        } 
        return false;
    }

    T dfs(int u, T m) {
        if (u == t) return m;
        T flow = 0;
        for (int i = cur[u]; ~i; cur[u] = i = e[i].nxt) {
            if (e[i].f && dis[e[i].v] == dis[u] + 1) {
                T f = dfs(e[i].v, min(m, e[i].f));
                e[i].f -= f;
                e[i^1].f += f;
                m -= f;
                flow += f;
                if (!m) break;
            }
        }
        if (!flow) dis[u] = -1;
        return flow;
    }

    T dinic() {
        T flow = 0;
        while (bfs()) flow += dfs(s, std::numeric_limits<T>::max());
        return flow;
    }

    void init(int s_, int t_, int vtot_) {
        vtot=vtot_; s=s_; t=t_;
        for (int i = 1; i <= vtot; i++) head[i] = -1;
    }
};

int n, m;
FlowGraph<ll> g;

int main() {
    scanf("%d%d", &n, &m);
    g.init(n + 1, n, n + n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g.addedge(u + n, v, 1ll << 60);
        g.addedge(v + n, u, 1ll << 60);
    }
    for (int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);
        g.addedge(i, i + n, c);
        g.addedge(i + n, i, c);
    }
    printf("%lld\n", g.dinic());
    vector<int> ans;
    for (int i = 2; i < n; i++) if (g.dis[i] && !g.dis[i + n]) 
        ans.push_back(i);
    printf("%d\n", (int)ans.size());
    for (auto v : ans) printf("%d ", v);
    puts("");
}
```

---

