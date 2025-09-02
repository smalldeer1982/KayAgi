# Cheap Robot

## 题目描述

You're given a simple, undirected, connected, weighted graph with $ n $ nodes and $ m $ edges.

Nodes are numbered from $ 1 $ to $ n $ . There are exactly $ k $ centrals (recharge points), which are nodes $ 1, 2, \ldots, k $ .

We consider a robot moving into this graph, with a battery of capacity $ c $ , not fixed by the constructor yet. At any time, the battery contains an integer amount $ x $ of energy between $ 0 $ and $ c $ inclusive.

Traversing an edge of weight $ w_i $ is possible only if $ x \ge w_i $ , and costs $ w_i $ energy points ( $ x := x - w_i $ ).

Moreover, when the robot reaches a central, its battery is entirely recharged ( $ x := c $ ).

You're given $ q $ independent missions, the $ i $ -th mission requires to move the robot from central $ a_i $ to central $ b_i $ .

For each mission, you should tell the minimum capacity required to acheive it.

## 说明/提示

In the first example, the graph is the chain $ 10 - 9 - 2^C - 4 - 1^C - 5 - 7 - 3^C - 8 - 6 $ , where centrals are nodes $ 1 $ , $ 2 $ and $ 3 $ .

For the mission $ (2, 3) $ , there is only one simple path possible. Here is a simulation of this mission when the capacity is $ 12 $ .

- The robot begins on the node $ 2 $ , with $ c = 12 $ energy points.
- The robot uses an edge of weight $ 4 $ .
- The robot reaches the node $ 4 $ , with $ 12 - 4 = 8 $ energy points.
- The robot uses an edge of weight $ 8 $ .
- The robot reaches the node $ 1 $ with $ 8 - 8 = 0 $ energy points.
- The robot is on a central, so its battery is recharged. He has now $ c = 12 $ energy points.
- The robot uses an edge of weight $ 2 $ .
- The robot is on the node $ 5 $ , with $ 12 - 2 = 10 $ energy points.
- The robot uses an edge of weight $ 3 $ .
- The robot is on the node $ 7 $ , with $ 10 - 3 = 7 $ energy points.
- The robot uses an edge of weight $ 2 $ .
- The robot is on the node $ 3 $ , with $ 7 - 2 = 5 $ energy points.
- The robot is on a central, so its battery is recharged. He has now $ c = 12 $ energy points.
- End of the simulation.

Note that if value of $ c $ was lower than $ 12 $ , we would have less than $ 8 $ energy points on node $ 4 $ , and we would be unable to use the edge $ 4 \leftrightarrow 1 $ of weight $ 8 $ . Hence $ 12 $ is the minimum capacity required to acheive the mission.

—

The graph of the second example is described here (centrals are red nodes):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1253F/a26fbeba71b5c3f08f761ccd3ba5eda79178ef04.png)The robot can acheive the mission $ (3, 1) $ with a battery of capacity $ c = 38 $ , using the path $ 3 \rightarrow 9 \rightarrow 8 \rightarrow 7 \rightarrow 2 \rightarrow 7 \rightarrow 6 \rightarrow 5 \rightarrow 4 \rightarrow 1 $

The robot can acheive the mission $ (2, 3) $ with a battery of capacity $ c = 15 $ , using the path $ 2 \rightarrow 7 \rightarrow 8 \rightarrow 9 \rightarrow 3 $

## 样例 #1

### 输入

```
10 9 3 1
10 9 11
9 2 37
2 4 4
4 1 8
1 5 2
5 7 3
7 3 2
3 8 4
8 6 13
2 3
```

### 输出

```
12
```

## 样例 #2

### 输入

```
9 11 3 2
1 3 99
1 4 5
4 5 3
5 6 3
6 4 11
6 7 21
7 2 6
7 8 4
8 9 3
9 2 57
9 3 2
3 1
2 3
```

### 输出

```
38
15
```

# 题解

## 作者：Suzt_ilymtics (赞：38)

## Description

> $n$ 个点，$m$ 条边，$k$ 个充电站，$Q$ 次询问，每次询问给出两个点 $p_1$ , $p_2$ ，两个点一定在充电站上，问从 $p_1$ 到  $p_2$ 的电池容量最少需要多少

[题目传送](https://www.luogu.com.cn/problem/CF1253F)

## 前置知识

- 最短路算法
- 最小生成树算法
- 倍增求LCA / 树链剖分

## Solution

考虑如何求出任意一个点到离它最近的充电站的距离？

暴力的做法是对每一个充电站跑一边单源最短路，但复杂度实在承受不了

有一个很巧妙的处理方法是，我们可以建一个超级源点，连向所有充电站，权值设为 $0$，然后在新图上跑一个最短路，就能求出所有点到离它最近的充电站得距离了

有什么用？别急，让我们接着往下看

设走到一个点 $i$，剩余电量为 $x$， 那么一定有 $x > dis_i$ （不管是中途充电还是到达终点均成立，因为保证了终点也是充电站）

假设我们要求的电容量为 $c$，那么三者关系满足：

$$c \ge x \ge dis_i$$

因为走到 $i$ 点至少消耗了 $dis_i$ 的电（最少的情况是以对 $i$ 来说它的起点刚好是最近的充电站来说的），那么上面的不等式可以改为：

$$c - dis_i \ge x \ge dis_i$$

设下一个点为 $j$，边权为 $w_{i,j}$，同理有：

$$c - dis_j \ge x - w_{i,j} \ge dis_j$$

结合上面两个式子，进行合并得到 $dis_j \le x - w_{i,j}$，即：

$$dis_j \le c - dis_i - w_{i,j}$$

交换一下位置：

$$c \ge dis_i + dis_j + w_{i,j}$$

这个不等式的含义为，从 $i$ 点到 $j$ 点所需最小的电池容量为 $dis_i + dis_j + w_{i,j}$，也就是说没条边的最小限制已经求出来了，用这个最小限制就可以更新图上所有的边

那么每次询问一个起点 $a$ 到 $b$ 的最小电池容量，就是找一条从 $a$ 点到 $b$ 点的路径，使得这个路径上的最大值最小

~~很像二分？~~ 但用不着那么麻烦

因为这条路径一定在最小生成树上，同时在这个最小生成树上每对点都有一个简单路径，最小生成树的构建过程也保证了这条简单路径上的最大值就是答案

那么用LCA+倍增法求出路径上的最大值即可（也可以用树链剖分来实现，~~前提是码力足够强~~）

具体实现来看代码

## Code

```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)

思路极其鬼畜：
1、最短路
2、生成树
3、倍增+LCA
4、查询 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
//#include<time.h>
#define LL long long
#define int long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 4e5+5;
const int MAXM = 6e5+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

struct edge{
    int from, to, w, nxt;
}e[MAXM << 2], E[MAXM], E2[MAXM << 1];
int head[MAXN], num_edge = 0;
int Head[MAXN], Num_edge = 0;

struct node{
    int bh, val;
    bool operator < (const node &b) const { return val > b.val; }
};

int n, m, k, Q, cnt;
int dis[MAXN], fa[MAXN], f[MAXN][22], dep[MAXN], maxm[MAXN][22];
bool vis[MAXN];
priority_queue<node> q;

int read(){
	int s = 0, f = 0;
	char ch = getchar();
	while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
	return f ? -s : s;
}

bool cmp(edge x, edge y){ return x.w < y.w; }
void add_edge(int from, int to, int w){ e[++num_edge] = (edge){from, to, w, head[from]}, head[from] = num_edge; }
void Add_edge(int from, int to, int w){ E2[++Num_edge] = (edge){from, to, w, Head[from]}, Head[from] = Num_edge; }
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void dij(){//跑一边dij求出所有点到最近的充电站的距离
    memset(dis, 0x3f, sizeof dis);
    dis[0] = 0;
    q.push((node){0, 0});
    while(!q.empty()){
        node u = q.top(); q.pop();
        if(vis[u.bh]) continue;
        vis[u.bh] = true;
        for(int i = head[u.bh]; i; i = e[i].nxt){
            int v = e[i].to;
            if(dis[v] > dis[u.bh] + e[i].w){
                dis[v] = dis[u.bh] + e[i].w;
                if(!vis[v]) q.push((node){v, dis[v]});
            }
        }
    }
}

void kruskal(){//建出更新权值后的图的最小生成树
	for(int i = 1; i <= n; ++i) fa[i] = i;//重置父亲 
	for(int i = 1; i <= m; ++i){
//    	cout<<E[i].from<<" "<<E[i].to<<" "<<E[i].w<<"lkp"<<endl;
		int uf = find(E[i].from), vf = find(E[i].to);
		if(uf != vf){
//			orz;
//			if(rand() % 2) fa[uf] = vf;//随机连父亲，随机化优化复杂度 
//			else 
			fa[vf] = uf;
			Add_edge(E[i].from, E[i].to, E[i].w), Add_edge(E[i].to, E[i].from, E[i].w);//建出最小生成树来 
			cnt++;
			if(cnt == n - 1) return ;//如果建了n - 1条边，就结束 
		}
	}
}

void dfs(int u, int fa){//dfs预处理lca ，注意这里跑的是新图
	f[u][0] = fa;
	for(int i = Head[u]; i; i = E2[i].nxt){
		int v = E2[i].to;
		if(v == fa) continue;
		dep[v] = dep[u] + 1;
		maxm[v][0] = E2[i].w;
//		cout<<maxm[v][0]<<endl;
		dfs(v, u);
	}
}

void init(){//倍增法预处理lca，顺便维护一个最大值
	for(int i = 1; i <= 20; ++i){
		for(int j = 1; j <= n; ++j){
			f[j][i] = f[f[j][i - 1]][i - 1];
			maxm[j][i] = max(maxm[j][i - 1], maxm[f[j][i - 1]][i - 1]);
//			cout<<maxm[j][i]<<endl;
		}
	}
}

int get_max(int x, int y){//可以直接在求两点lca的过程中求出两点简单路径的最大值
	int ans = 0;
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; i >= 0; --i){
		if(dep[f[x][i]] < dep[y]) continue;
		ans = max(ans, maxm[x][i]);
		x = f[x][i];
	}
	if(x == y) return ans;
	for(int i = 20; i >= 0; --i){
		if(f[x][i] == f[y][i]) continue;
		ans = max(ans, max(maxm[x][i], maxm[y][i]));
//		cout<<ans<<endl;
		x = f[x][i];
		y = f[y][i];
	}
	ans = max(ans, max(maxm[x][0], maxm[y][0]));
	return ans;
}

signed main()
{
//	srand(time(0));
    n = read(), m = read(), k = read(), Q = read();
    for(int i = 1, u, v, w; i <= m; ++i){
        u = read(), v = read(), w = read();
        add_edge(u, v, w), add_edge(v, u, w);
        E[i].from = u, E[i].to = v, E[i].w = w;
    }
    for(int i = 1; i <= k; ++i){
        add_edge(0, i, 0), add_edge(i, 0, 0);    
    }
    dij();
//  for(int i = 1; i <= n; ++i) cout<<i<<" "<<dis[i]<<" lkp"<<endl;
    for(int i = 1; i <= m; ++i){//更新边的权值
    	E[i].w += dis[E[i].from] + dis[E[i].to];
	}
	sort(E + 1, E + m + 1, cmp);//按边权大小由小到大排序 
	kruskal();
	
//	memset(minn, 0x7f, sizeof minn);
	dep[1] = 1;
	dfs(1, -1);
	init();
	
	for(int i = 1, u, v; i <= Q; ++i){
		u = read(), v = read();
		cout<<get_max(u, v)<<endl;//直接输出所求结果即可
	}
	return 0;
}
```

---

## 作者：Fading (赞：14)

值得思考的一题。

------------

设电量最大上限为$c$。

首先发现一个点以$x$的电量到达点$y$，那么我们可以到一个最近的补给点获得能量再回来。

然后我们设$\text{dis}_y$表示点$y$走到最近的补给点需要花费多少能量。这个数组可以用 dijkstra 求出。

**性质$1$** 如果$x\geq \text{dis}_y$，那么$x$可以通过上述操作变成$c-\text{dis}_y$。

否则我们发现这个点不可能到达终点了（因为题目说终点起点都是补给点）

~~然后我就不会了~~

**性质$2$** 就是如果$x\geq \text{dis}_y$，那么$c-\text{dis}_y$一定$\geq x$。

为什么呢？设上一个补给点到$y$的距离为$z$，那么$x=c-z$。显然$z\geq \text{dis}_y$，所以$x\leq c-\text{dis}_y$。所以每到一个点就往最近的补给点走一走是最优的。

换句话说，$y$显然是从一个补给点走来的（这用到了起点也是补给点的性质）。$c-\text{dis}_y$只能比$\geq x$大，因为$\text{dis}_y$已经是最近的了。

这个性质十分重要，我当时就是因为自己没有发现这个性质才没做出这道题...

------------

这两个性质启示我们可以可以用图的连通性去做这道题。

如果一条边$(a,b,w)$有希望从$a$经过这条边到$b$，而且依靠剩余的电量有希望到达最近的补给点，那么我们就把这条边加入一张新的图。发现问题等价于判断新图两点是否连通了。（这用到了起点终点都是补给点的性质，不然不等价）

一条边能加入的条件是

$$c-\text{dis}_a-w\geq \text{dis}_b$$

根据上述性质可以看出。

移项

$$c\geq \text{dis}_b+\text{dis}_a+w$$

发现如果我们枚举$c$，然后把所有满足条件的边加入新图，看看是否连通，不就可以了吗？

这样问题就简单了。可以用离线的并查集按秩合并，也可以用在线的 kruskal 重构树。当然你也可以通过贪心建出最大生成树。

后者空间不够优秀，所以我写了前者...
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;char ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
struct edge{
    int to,nxt,from;
    ll dis;
}g[1010101];
int head[1010101],tot,n,m,K,Q;
inline void made(int from,int to,ll dis){
    g[++tot].to=to;g[tot].nxt=head[from];head[from]=tot;
    g[tot].dis=dis;g[tot].from=from;
}
int F[1010101],sz[1010101];
ll dis[1010101];
int find(int u){
    if (F[u]!=u) F[u]=find(F[u]);
    return F[u];
}
struct que{
    int x,y;
    int id;
}q[1010101];
ll ans[1010101];
vector<que> G[1010101];
inline bool cmp(edge a,edge b){
    return a.dis<b.dis;
}
ll NOW;
bool vis[1010101];
int main(){
    // freopen("data.in","r",stdin);
    n=read(),m=read(),K=read(),Q=read();
    for (int i=1;i<=m;i++){
        int x=read(),y=read();
        ll z=read();
        made(x,y,z);made(y,x,z);
    }
    for (int i=1;i<=n;i++){
        F[i]=i;sz[i]=1;
    }
    priority_queue<pair<ll,int> > dl;
    memset(dis,0x3f,sizeof dis);
    while (!dl.empty()) dl.pop();
    for (int i=1;i<=K;i++) dis[i]=0,dl.push(make_pair(0,i));
    while (!dl.empty()){
        int u=dl.top().second;dl.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (int i=head[u];i;i=g[i].nxt){
            int v=g[i].to;
            if (dis[v]>dis[u]+g[i].dis){
                dis[v]=dis[u]+g[i].dis;
                if (!vis[v]){
                    dl.push(make_pair(-dis[v],v));
                }
            }
        }
    }
    for (int i=1;i<=tot;i++){
        g[i].dis=g[i].dis+dis[g[i].from]+dis[g[i].to];
    }
    sort(g+1,g+1+tot,cmp);
    for (int i=1;i<=Q;i++){
        q[i].id=i;q[i].x=read(),q[i].y=read();
        G[q[i].x].push_back(q[i]);G[q[i].y].push_back(q[i]);
    }
    for (int i=1;i<=tot;i++){
        int u=g[i].from,v=g[i].to;
        NOW=g[i].dis;
        int fu=find(u),fv=find(v);
        if (fu!=fv){
            if (sz[fu]<sz[fv]){
                swap(fu,fv);swap(u,v);
            }
            sz[fu]+=sz[fv];F[fv]=fu;
            for (auto now:G[fv]){
                if (find(now.x)==find(now.y)){
                    if (!ans[now.id]){
                        ans[now.id]=NOW;
                    }
                }else{
                    G[fu].push_back(now);
                }
            }
        }
    }
    for (int i=1;i<=Q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
```


---

## 作者：Zxsoul (赞：6)

- update 2021/9/22 根据回复，我来改一下 md。


> $N$ 个点， $m$ 条边，并且存在可以来回走动的边，走动的代价是花费你当前的电量 $W$, 开始你有且上限为 $C$ 的电池容量，$N$ 个点中有 $k$ 个充电站，可以使自己充满电且无花费，现给出 $Q$ 次询问，每次为$[P_1,P_2]$ 求出保证电池容量至少为多少，才能够抱孩子能从 $P_1$ 到 $P_2$

##  思路

我们的子任务肯定是了解在 $i$ 距离最近的充电站，这样才能够完成目标， 那么首先想到的是**全源最短路**。

但是没必要，我们可以设立一个**超级源点**，连接每个充电站，跑一个单源最短路，得到的 $dis[i]$,表示 $i$ 到源点的最短路，换言之，因为源点与充电站的边权为零，那么我们可以等价的表示为：$i$ 到充电站的最短路径

我们设 $X_i$ 为当前在 $i$ 点的电池容量，他与 $dis[i]$ 的关系是：
$$
    X_i\ge dis[i]
$$
若设 电池上限总容量为 $C$ ，那三者之间的关系应该是
$$
    C\ge X_i\ge dis[i]
$$
进而推得

$$
    C-dis[i]\ge X_i\ge dis[i]
$$
为什么？

对于一个满电量的状态要到达 $i$ 点，至少要消耗 $dis[i]$ 电，反过来看，就是从加油站到 $i$ 是等价的

那么对于 $i$ 与 $j$ 有一条 $W_{i,j}$ 的边，那么按照上述式子推得
$$
    C-dis[i]\ge X_i-W_{i,j}\ge dis[j]
$$
对于一个 $X$ 是不稳定的，即我们不知道 $X$ 的具体状态，所以可以想办法将其消掉

   我们已知两式子：
  $$
    dis[j] \le X_i-W_{i,j}
    $$

$$
		dis[j] \le C-dis[i]-W_{i,j}
$$

 将 $C$ 移项得
$$
    C\ge dis[i]+dis[j]+W_{i,j}
$$
    这是一个充要条件

所以每条边必须满足的条件即为上述式子，对于每个充电站我们必须要满足这个条件，这样我们就可以重现建一张图，$i$ 到 $j$ 的权值为 $dis[i]+dis[j]+W_{i,j}$。

故我们只需要知道 $P_1$ 到 $P_2$ 路径上最大所需电池容量，即边权就可以是合法解，题目中是**至少**，也就是电池容量**最小**，也就是**最大边最小**，那么就是转换成跑**最小生成树**问题。

## Code
```c
/*
  CF1253F
*/
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
struct edgexx{
  int v, nxt, w;
} edge[B];//跑最短路
struct edgex{
  int v, nxt;
} edge_[B];//新图 
struct node{
  ll d;
  int id;
  bool operator<(const node &a)const{return d > a.d;}
};
struct xxs{
	int u,v;
	ll w;
	bool operator<(const xxs &e)const{return w<e.w;}
}e[B];
/*------------------------------------------------------*/
int n, cnt, js, k, c, t, head[B], m, q, head2[B], fa[B], u_fa[B];
ll dis[B], wnd[B];
int sz[B], son[B], top[B], dep[B];
priority_queue<node> pq;
/*------------------------------------------------------*/ 
void add1(int u, int v, int w)
{
  edge[++cnt].nxt = head[u];
  edge[cnt].v = v;
  edge[cnt].w = w;
  head[u] = cnt;
}//边表1
void add2(int u, int v){
  edge_[++js].nxt = head2[u];
  edge_[js].v = v;
  head2[u] = js;
}
int find(int x){
  if(x == u_fa[x]) return x;
  return u_fa[x] = find(u_fa[x]);
}//并查集 
void dfs1(int u, int f){
  sz[u] = 1;
  dep[u] = dep[fa[u] = f] + 1;
  for (int i = head2[u]; i; i = edge_[i].nxt){
    int v = edge_[i].v;
    if(v == f) continue;
    dfs1 (v, u);
    sz[u] += sz[v];
    if(sz[v] > sz[son[u]]) son[u] = v;
 }
}
void dfs2(int u, int topf){
  top[u] = topf;
  if(son[u]) dfs2(son[u], topf);
  for (int i = head2[u]; i; i = edge_[i].nxt){
    int v = edge_[i].v;
    if(v == fa[u] || v == son[u]) continue;
    dfs2(v, v);
  }
}//dfs序求lca 
int lca(int u, int v){
  while (top[u] != top[v]){
    if(dep[top[u]] < dep[top[v]]) swap(u, v);
    u = fa[top[u]];
  }
  return dep[u] < dep[v] ? u : v;
}
int main() {
  cin >> n >> m >> k >> q;
  for (int i = 1; i <= m; i++)
  {
    int x = read(), y = read(), z = read();
    add1(x, y, z);
    add1(y, x, z);
    e[i] = (xxs){x, y, z}; 
  }
  memset (dis, 0x3f, sizeof(dis));
  for (int i = 1; i <= k; i++) pq.push((node){dis[i] = 0, i});
  while(!pq.empty()){
    ll d = pq.top().d;
    int u = pq.top().id;
    pq.pop();
    if (d != dis[u]) continue;
    for (int i = head[u]; i; i = edge[i].nxt){
      int v = edge[i].v;
      if (dis[v] > d + edge[i].w) pq.push((node){dis[v] = d + edge[i].w, v});
    }
  }//跑最短路 地杰斯特拉
  for (int i = 1; i <= m; i++) e[i].w += dis[e[i].u] + dis[e[i].v];//重建边 
  sort(e + 1, e+ 1 + m); 
  for (int i = 1; i <= 2 * n; i++) u_fa[i] = i;
  cnt = n;
  for (int i = 1; i <= m; i++){
      int u = e[i].u, v = e[i].v;
      ll w = e[i].w;
      u = find(u);
      v = find(v);
      if (u == v) continue;
      u_fa[u] = u_fa[v] = ++cnt;
      wnd[cnt] = w;
      add2(cnt, u); add2(cnt, v);
  }//库鲁斯卡尔
  dfs1(cnt, 0); dfs2(cnt, cnt);
  while(q--){
    int u = read(), v = read();
    printf("%lld\n", wnd[lca(u, v)]);
  }
  return 0;
}




```

---

## 作者：YLWang (赞：5)

时隔五个月就不会套路了 /kl

---

### 题意简述

https://www.luogu.com.cn/problem/CF1253F。

### 题解

我们考虑在乱七八糟的图上搞事情显然是不好搞的。于是我们考虑把关键点拎出来建一幅新图，最好是树。

一个简单的思想就是跑全源最短路然后连起来边，之后跑个货物运输状物。这东西显然是不得行的。

但是一定要跑全源最短路吗？

我们烤滤对于每一条原图中的边 $(u, v)$ 计算出离它最近的两个关键点$(fr_u, fr_v)$。然后连边 $fr_u, fr_v$，边权为 $dist(fr_u, u) + (u, v) +dist(v, fr_v)$。这样的话一定可以烤滤到所有在最短路上的点。读者自证不难。这个套路在[这里](https://www.luogu.com.cn/problem/solution/CF196E)是有的。事实上，这种转化来剪枝的方法是很好的思想。

实现的话没啥技巧，正常地写就过了。

---

## 作者：FutaRimeWoawaSete (赞：3)

被诈骗了，其实也不需要证明的那么复杂。            

因为要求的询问都是电桩点，所以我们可以这么贪心走：每次走到下一个点的时候去距它最近的电桩点补满点再走回来，这样做一定可以保证再以当前状态走下去的电量最多。         

由于只询问充电桩之间的答案，所以考虑枚举答案 $c$，每次重新加上满足条件的如下边：

记当前的点为 $a$，走到的点为 $b$，如果存在一条边权为 $w$ 的连边 $(a,b)$ 那么 $(a,b)$ 想要重连的条件为 $0 \leq c - dis_a - w - dis_b$。其中 $c - dis_a$ 可以看作在 $a$ 点时的电量。           

如果不是询问充电桩之间的答案的话这样做会导致你开头的点和结尾的点维持的电量并不一定是最优电量而导致贪心的全过程不存在最优子结构。但是若保证开头的点和结尾的点都是充电桩上的点的话就不存在这个问题了。        

这一过程就直接离散化后枚举也行，写一个 kruskal 重构树也行，瓶颈不在这里，个人实现的是一个 $O(n \log n)$ 的 kruskal 重构树做法。

```cpp
/*
每次从最近的充电站走回来就好了
md怎么连多源最短路都不会了rnm 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 3e5 + 5;
const long long Inf = 1e18;
int n,m,k,q,head[Len],cnt,id,lim,dp[Len][28],dep[Len];
long long dis[Len],w[Len];
bool flag[Len];
struct NNode
{
	int to;long long val;
	NNode(){to = val = 0;}
	NNode(int TO,long long VAL){to = TO , val = VAL;}
	bool operator < (const NNode &Ano) const
	{
		return val > Ano.val;
	}
}P,PP;
struct Node
{
	int x,y;long long val;
	Node(){x = y = val = 0;}
	Node(int X,int Y,long long VAL){x = X , y = Y , val = VAL;}
}Edge[Len];bool cmp(Node x,Node y){return x.val < y.val;}
vector<NNode> v[Len];
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
int fa[Len];
void makeSet(int x){for(int i = 1 ; i <= x ; i ++) fa[i] = i;}
int findSet(int x){return fa[x] == x ? fa[x] : fa[x] = findSet(fa[x]);}
void rebuild()
{
	id = n , lim = n << 1;makeSet(lim);
	for(int i = 1 ; i <= m ; i ++)
	{
		int u = findSet(Edge[i].x) , v = findSet(Edge[i].y);
		if(u == v) continue;
		fa[u] = fa[v] = ++ id;
		add(id , u) , add(id , v);
		w[id] = Edge[i].val;
		if(id == lim - 1) break;
	}
}
void dfs(int x,int f)
{
	dep[x] = dep[f] + 1;
	dp[x][0] = f;
	for(int i = 1 ; (1 << i) <= dep[x] ; i ++) dp[x][i] = dp[dp[x][i - 1]][i - 1];
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs(to , x);
	}
}
int FLCA(int x,int y)
{
	if(dep[x] < dep[y]) swap(x , y);
	for(int i = 25 ; i >= 0 ; i --) if(dep[dp[x][i]] >= dep[y]) x = dp[x][i];
	if(x == y) return x;
	for(int i = 25 ; i >= 0 ; i --) if(dp[x][i] != dp[y][i]) x = dp[x][i] , y = dp[y][i];
	return dp[x][0]; 
}
int main()
{
	scanf("%d %d %d %d",&n,&m,&k,&q);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;long long z;scanf("%d %d %lld",&x,&y,&z);
		v[x].push_back(NNode(y , z)) , v[y].push_back(NNode(x , z));
		Edge[i] = Node(x , y , z);
	}
	priority_queue<NNode> Q;
	for(int i = 1 ; i <= n ; i ++) dis[i] = Inf;
	for(int i = 1 ; i <= k ; i ++) dis[i] = 0 , flag[i] = 0 , Q.push(NNode(i , 0));
	while(!Q.empty())
	{
		P = Q.top();Q.pop();
		if(!flag[P.to])
		{
			flag[P.to] |= 1;
			for(int i = 0 ; i < v[P.to].size() ; i ++) 
			{
				int to = v[P.to][i].to;
				if(dis[to] > dis[P.to] + v[P.to][i].val) 
				{
					dis[to] = dis[P.to] + v[P.to][i].val;	
					if(!flag[to]) Q.push(NNode(to , dis[P.to] + v[P.to][i].val));
				}
			}	
		}
	}
	for(int i = 1 ; i <= m ; i ++) Edge[i].val += dis[Edge[i].x] + dis[Edge[i].y];
	sort(Edge + 1 , Edge + 1 + m , cmp);
	rebuild();
	dfs(id , 0); 
	for(int i = 1 ; i <= q ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		printf("%lld\n",w[FLCA(x , y)]);
	}
	return 0;
} 
```

---

## 作者：ez_lcw (赞：3)

首先发现所有询问点都是充电桩这个条件很有用。

它能滋生出一种暴力到极端的想法：用 Floyd 对全局跑一遍最短路。然后新建一个图，图中两两充电桩连一条边，边权为它们之间的最短路，代表着从这个充电桩直接走到那个充电桩最少要备多少电。然后再把新图的最小生成树建出来，询问时直接询问树上两点路径边权最大值。

发现时间压根过不去，也不太好直接优化。

发现瓶颈主要是在跑 Floyd $O(n^3)$ 和建图 $O(k^2)$，这是我们我们远远不能接受的。

但是原图最多也就 $m$ 条边，所以上面的做法只能把时间复杂化。

于是考虑能不能直接在题目给的原图上搞东西。

于是就有了一种神奇的思路：

既然充电桩直接两两建边我们不能接受，我们不如直接枚举 $c$，把两个距离 $\leq c$ 的充电桩之间连一条边，然后再看题目询问的 $A$ 和 $B$ 充电桩在什么时候联通。

但是枚举 $c$ 貌似也要跟充电桩两两间的距离有关，那怎么转移到原图上的边呢？

在原图上，我们先用 dijkstra 预处理出每一个点 $i$ 到离它最近的充电桩的距离 $dis_i$。然后设当前枚举的为 $c$：

然后对于原图中的每一条边 $(u,v)$，设其边权为 $w$。如果 $dis_u+w+dis_v\leq c$，，那么就连上边 $(u,v)$，然后再判断 $A$ 和 $B$ 在原图中是否联通。

为什么这样做是对的呢？（以下的 $A$ 和 $B$ 均代表任意两个充电桩）

1. 若 $(u,v)$ 被连上，那么 $u$ 和 $v$ 的最近充电桩间的距离 $\leq c$。

   证明显然，根据 $(u,v)$ 被连上的条件的定义即可得出。

2. 若 $A$ 和 $B$ 的距离 $\leq c$，那么 $A$、$B$ 联通。

   如果两个充电桩 $A$ 和 $B$ 的距离 $\leq c$，那么这样做之后他们一定联通。因为对于 $A$ 和 $B$ 最短路上的每一条边 $(u,v)$，它肯定能满足 $dis_u+w+dis_v\leq c$，因为这个式子代表着从离 $u$ 最近的充电桩出发、能经过 $(u,v)$ 走到离 $v$ 最近的充电桩且满足路程 $\leq c$，而从 $A$ 走到 $B$ 肯定算入一种方案，所以 $(u,v)$ 这条边肯定能连上。

3. 推广到间接联通上，如果 $A$ 和 $B$ 联通，$A$ 就真的能到达 $B$ 吗？

   答案是肯定的，因为 $A$ 和 $B$ 的联通路径上的每一条边都被连上，那么根据上述两点证明，可以得出这条边的两个端点的最近充电桩可以互相到达，而 $A$ 可以通过这些能互相到达的充电桩直接或间接地到达 $B$。

所以这样做是正确的。

至于维护连边的过程，我们可以用并查集。

同时我们可以把询问离线下来，在并查集的每个联通块内记录这个连通块内包含的未解决询问，而合并连通块时要用启发式合并才能保证时间复杂度，具体详见代码。

然后枚举 $c$ 实在是太大了，不然直接先把每条边按 $dis_u+w+dis_v$ 排序，再依次枚举边。

这样你就发现这种 “给边排序，再依次加入图中判断联通” 的方法和 kruskal 类似，只不过边权改了一下而已，而且还带上了询问。

具体代码如下：

```cpp
#include<bits/stdc++.h>

#define N 100010
#define M 300010
#define ll long long

using namespace std;

struct Edge
{
	int u,v;
	ll w;
}e[M];

struct Query
{
	int a,b;
	ll ans;
	Query(){ans=-1;}
}q[M];

struct data
{
	int u;
	ll s;
	data(){};
	data(int a,ll b){u=a,s=b;}
	bool operator < (const data &a) const
	{
		return s>a.s;
	}
};

int n,m,k,Q;
int fa[N];
int cnt,head[N],nxt[M<<1],to[M<<1],w[M<<1];
ll dis[N];

vector<int>g[N];
priority_queue<data>que;

void adde(int u,int v,int wi)
{
	to[++cnt]=v;
	w[cnt]=wi;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

void dijkstra()
{
	memset(dis,127,sizeof(dis));
	for(int i=1;i<=k;i++)
		que.push(data(i,0)),dis[i]=0;
	while(!que.empty())
	{
		data now=que.top();
		que.pop();
		for(int i=head[now.u];i;i=nxt[i])
		{
			int v=to[i];
			if(dis[now.u]+w[i]<=dis[v])
			{
				dis[v]=dis[now.u]+w[i];
				que.push(data(v,dis[v]));
			}
		}
	}
}

bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}

int find(int x)
{
	return x==fa[x]?x:(fa[x]=find(fa[x]));
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&Q);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lld",&e[i].u,&e[i].v,&e[i].w);
		adde(e[i].u,e[i].v,e[i].w),adde(e[i].v,e[i].u,e[i].w);
	}
	for(int i=1;i<=Q;i++)
	{
		scanf("%d%d",&q[i].a,&q[i].b);
		g[q[i].a].push_back(i),g[q[i].b].push_back(i);
	}
	dijkstra();
	for(int i=1;i<=m;i++)
		e[i].w=e[i].w+dis[e[i].u]+dis[e[i].v];
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int a=find(e[i].u),b=find(e[i].v);
		if(a!=b)
		{
			if(g[b].size()<g[a].size()) swap(a,b);//注意启发式合并的size比较不是比较的并查集的size而是询问大小的size
			fa[a]=b;
			for(int j=0,size=g[a].size();j<size;j++)
			{
				int x=find(q[g[a][j]].a),y=find(q[g[a][j]].b);
				if(x==y)
				{
					if(q[g[a][j]].ans==-1)
						q[g[a][j]].ans=e[i].w;
				}
				else g[b].push_back(g[a][j]);
			}
		}
	}
	for(int i=1;i<=Q;i++)
		printf("%lld\n",q[i].ans);
	return 0;
}
```



---

## 作者：NinT_W (赞：1)

我们可以变换一下，首先考虑机器人在某个点离它最近的充电站到它的距离，我们将其设置为 $dis_i$，如果对每个点都跑一边最短路，那我就不用干别的了 ~~一个最短路就 Game Over 了。~~

我们引入超级源点（这个之前涉及过，在差分约束），看自己喜好，这里我将其设为 0 号点，那么将 0 号点与其他所有能充电的点连边的边权全部设为 0，由于是无向边，则不难想出其他不能充电的点到最近的能充电的点的距离为 $ dis_i $ ，即超级源点到他的最短路，用 Dij 预处理即可。

然后我们会发现，设在这个点的电量为 $x$，那 $x$ 应该大于等于 $dis_i$ ，小于等于电池容量 $c-dis_i$（这个上课我口胡对力），所以 $dis_i \leq x \leq c-dis_i$ ，又因为从 $i$ 到 $j$ ，边权为 $val$ ，那么在 $i$ 剩余电量为 $x$，则在j剩余电量为 $x-val$ ，则有

$ dis_j \leq x-val \leq c-dis_j $

即 $dis_j+val \leq x \leq c-dis_j+val$

可得 $dis_j+val \leq x \leq c-dis_i$

即 $dis_j+val \leq c-dis_i$ 

$dis_i+dis_j+val \leq c$

我们通过预处理出 $dis_i$ ，那么我们就可以将边权转化为 $dis_i+dis_j+val$ ，以这个为新的边权，建出它的一棵最小生成树来。

那么答案显然是在树上两点间的所有边里最大的边权值，即树上区间最值。

由于这里最小生成树是并查集存储的，我们可以新建一棵树，来实现最小生成树（kruskal 重构树）。

然后就是树上区间最值了，zhx 讲的是倍增。

但是倍增多麻烦。。。。我直接树剖套线段树。

TM define int long long 被卡常了，懒得改了，直接吸氧 AC。

自己注意一下就好。

AC code

```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<queue>
#define int long long
#define pii pair<int,int>

using namespace std;

const int maxm=1e5+5;

const int maxn=4e5+5;

inline int read()
{
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}

int fath[maxn];
bool vis[maxn];
int max_son[maxn];
long long a[maxn];
long long dis[maxm];
long long val[maxn];
int head_tree[maxn];
int n,tot,m,k,q,cnt;
int top[maxn],id[maxn];
int head[maxn],fa[maxn];
int siz[maxn],deep[maxn];

struct edge
{
	int to;
	int next;
	long long val;
}e[maxn*2],tree[maxn*2];

struct s_t
{
	int l,r;
	int val;
}t[maxn*4];

struct node
{
	int from;
	int to;
	long long val;
}edg[maxn];

void add(int x,int y,int z)
{
	tot++;
	e[tot].to=y;
	e[tot].val=z;
	e[tot].next=head[x];
	head[x]=tot;
}

void add_tree(int x,int y,int z)
{
	tot++;
	tree[tot].to=y;
	tree[tot].val=z;
	tree[tot].next=head_tree[x];
	head_tree[x]=tot;
}

bool cmp(node x,node y)
{
	return x.val<y.val;
}

void init()
{
	n=read();
	m=read();
	k=read();
	q=read();
	for(int i=1;i<=m;i++)
	{
		int u=read();
		int v=read();
		long long val=read();
		add(u,v,val);
		add(v,u,val);
		edg[i]={u,v,val};
	}
}

void dij()
{
	for(int i=1;i<=k;i++) add(0,i,0);
	priority_queue <pii,vector<pii>,greater<pii> > q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,false,sizeof(vis));
	dis[0]=0; q.push(make_pair(dis[0],0));
	while(!q.empty())
	{
		int k=q.top().second;
		q.pop();
		if(vis[k]) continue;
		vis[k]=true;
		for(int i=head[k];i;i=e[i].next)
		{
			int to=e[i].to;
			if(vis[to]) continue;
			if(dis[to]>dis[k]+e[i].val)
			{
				dis[to]=dis[k]+e[i].val;
				q.push(make_pair(dis[to],to));
			}
		}
	}	
}

int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}

void merger(int x,int y)
{
	fa[y]=x;
}

void kruskal()
{	
	for(int i=1;i<=m;i++)
	{
		int u=edg[i].from;
		int v=edg[i].to;
		edg[i].val+=dis[u]+dis[v];
	}
	for(int i=1;i<=n;i++) fa[i]=i;
	sort(edg+1,edg+m+1,cmp);tot=0;
	for(int i=1;i<=m;i++)
	{
		int u=edg[i].from;
		int v=edg[i].to;
		long long w=edg[i].val;
		if(find(u)==find(v)) continue;
		merger(find(u),find(v));cnt++;
		add_tree(u,v,w);add_tree(v,u,w);
		if(cnt==n-1) break;
	}
}

void dfs_first(int x,int f)
{
	siz[x]=1;deep[x]=deep[f]+1;fath[x]=f;
	for(int i=head_tree[x];i;i=tree[i].next)
	{
		int to=tree[i].to;
		if(to==f) continue;
		val[to]=tree[i].val;
		dfs_first(to,x);
		siz[x]+=siz[to];
		if(siz[to]>siz[max_son[x]])
		{
			max_son[x]=to;
		}
	}
}

void dfs_second(int x,int t)
{
	top[x]=t; tot++;
	id[x]=tot;
	a[tot]=val[x];
	if(max_son[x]==0) return ;
	dfs_second(max_son[x],top[x]);
	for(int i=head_tree[x];i;i=tree[i].next)
	{
		int to=tree[i].to;
		if(to!=max_son[x] && to!=fath[x])
			dfs_second(to,to);
	}
}

void build(int p,int l,int r)
{
	t[p].l=l,t[p].r=r;
	if(l==r)
	{
		t[p].val=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p].val=max(t[p*2].val,t[p*2+1].val);
}

long long query(int p,int l,int r)
{
	if(l>r) return 0;
	if(l<=t[p].l && t[p].r<=r)
	{
		return t[p].val;
	}
	int mid=(t[p].l+t[p].r)>>1;
	long long ans=0;
	if(l<=mid)
	{
		ans=max(ans,query(p*2,l,r));
	}
	if(r>mid)
	{
		ans=max(ans,query(p*2+1,l,r));
	}
	return ans;
}

long long get_ans(int x,int y)
{
	long long ans=0;
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]]) swap(x,y);
		ans=max(ans,query(1,id[top[x]],id[x]));
		x=fath[top[x]];
	}
	if(deep[x]>deep[y])	swap(x,y);
	ans=max(ans,query(1,id[x]+1,id[y]));
	return ans;
}

signed main()
{	
	init();dij();kruskal();
	
	tot=0; dfs_first(1,0);
	tot=0; dfs_second(1,1);
	
	build(1,1,n);
	
	for(int i=1;i<=q;i++)
	{
		int x=read();
		int y=read();
		cout<<get_ans(x,y)<<endl;
	}
	
	return 0;
}
```


---

## 作者：zhenjianuo2025 (赞：0)

### Problem

[题目传送门](https://www.luogu.com.cn/problem/CF1253F)

### Solve

设电池容量为 $c$，走到 $u$ 点剩余的电量为 $x$，显然 $0\le x\le c$。

如果设 $d_u$ 为离 $u$ 点最近的加油站的距离（如果 $u$ 是加油站就是 $0$），则还应满足 $d_u\le x\le c-d_u$。因为 $u$ 点剩余的电量一定可以到达离它最近的加油站完成一次充电，而且电量最多也只会是从离它最近的加油站加了油来到 $u$。

如果从 $u$ 走到相邻的 $v$，边权为 $w$，显然也应该满足 $d_v\le x-w\le c-d_v$。

合并 $d_u\le x\le c-d_u$ 和 $d_v\le x-w\le c-d_v$，得 $d_v\le c-d_u-w$，即 $d_v+d_u+w\le c$。

对于一条边 $u\to v(w)$，连接一条边权为 $d_v+d_u+w$ 的边，得到一个新图。若询问 $x$ 和 $y$，即最小化 $x$ 到 $y$ 路径的边权的最大值，在最小生成树上倍增最大值即可。

关于 $d$ 数组如何求得，可以建立超级源点，向每个加油站连接一条边权为 $0$ 的边，$d_i$ 就是 $i$ 到超级原点的最短路。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 100010
#define MAXM 300010 
#define INF 1000000000000000ll
int n, m, k, q, fat[MAXN], dis[MAXN], inq[MAXN], dep[MAXN], anc[MAXN][25], mxn[MAXN][25];
struct edge {
	int u, v, w;
	edge() {}
	edge(int a, int b, int c) {
		u = a, v = b, w = c;
	}
} z[MAXM];
bool cmp(edge a, edge b) {
	return a.w < b.w;
}
vector<pair<int, int> > g[MAXN], e[MAXN];
int find(int u) {
	if (fat[u] == u) return u;
	return fat[u] = find(fat[u]);
}
void dijk(int s) {
	for (int i = 0; i <= n; i++) dis[i] = INF;
	dis[s] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	q.push({0, s});
	while (!q.empty()) {
		int d = q.top().first, u = q.top().second; q.pop();
		if (inq[u]) continue;
		inq[u] = 1;
		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first, w = g[u][i].second;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push({dis[v], v}); 
			}
		}
	}
}
void dfs(int u, int fa) {
	for (int i = 0; i < e[u].size(); i++) {
		int v = e[u][i].first, w = e[u][i].second;
		if (v == fa) continue;
		dep[v] = dep[u] + 1;
		anc[v][0] = u; mxn[v][0] = w;
		dfs(v, u);
	}
}
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int ans = 0;
	for (int i = 24; i >= 0; i--)
		if (dep[anc[u][i]] >= dep[v]) ans = max(ans, mxn[u][i]), u = anc[u][i];
	if (u == v) return ans;
	for (int i = 24; i >= 0; i--)
		if (anc[u][i] != anc[v][i]) ans = max(ans, max(mxn[u][i], mxn[v][i])), u = anc[u][i], v = anc[v][i];
	return max(ans, max(mxn[u][0], mxn[v][0]));
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> k >> q;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		z[i] = edge(u, v, w);
		g[u].push_back({v, w}), g[v].push_back({u, w});
	}
	for (int i = 1; i <= k; i++) g[0].push_back({i, 0});
	dijk(0);
	for (int i = 1; i <= m; i++) z[i].w += dis[z[i].u] + dis[z[i].v];
	sort(z + 1, z + m + 1, cmp);
	for (int i = 1; i <= n; i++) fat[i] = i;
	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		int u = z[i].u, v = z[i].v, w = z[i].w;
		if (find(u) != find(v)) {
			fat[find(u)] = find(v);
			e[u].push_back({v, w}), e[v].push_back({u, w});
			cnt++;
			if (cnt == n - 1) break;
		}
	}
	dep[1] = 1; dfs(1, 0);
	for (int j = 1; j <= 24; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1], mxn[i][j] = max(mxn[i][j - 1], mxn[anc[i][j - 1]][j - 1]);
	while (q--) {
		int u, v;
		cin >> u >> v;
		cout << lca(u, v) << "\n";
	}
	return 0;
} 
```

---

## 作者：Aisaka_Taiga (赞：0)

## 本题需要以下知识点

1. 求单源最短路。
2. kruskal 算法。
3. 倍增求 LCA（用于求树上两点距离）。

## 本题思路

首先可以知道有 $k$ 个充电点，我们如果要保证电池容量尽可能的小的话就要尽量走当前点到另一个充电点的距离尽量小的那一条路，然后我们就要先预处理出每一个点到离他最近的充电站的距离，这样的话肯定是不能每一个点跑一遍迪杰斯特拉，那样就对不起他紫的标签了；所以我们来考虑一下该如何预处理能快，我们可以发现当前的充电点是 $1\sim k$，从哪一个点开始都不能够满足我们的需求，最简单的方式就是我们把这 $k$ 个点向一个源点连一条边权为 $0$ 的边，此时跑一个最短路就可以完美的处理出所有的点到离他最近的充电点的距离了。为什么一定要连充电点呢？思考一下，如果是连其他点的话，那样会导致不知道哪一个是充电点，这样就很难处理，因为除充电点以外都可以看作是一个起点，我们从充电点这个终点开始走的话，那么无论走到哪里都是起点，这样就可以完美解决 TLE 的痛苦。

迪杰斯特拉就不用说了吧应该都会。

预处理完之后就要进行边权的更新，因为我们已经处理出了 $dis$ 数组（存放每一个点到最近充电点的距离），设我们当前剩余的电池电量是 $x$，那么我们可以得出一个结论就是当前从起点到终点上的点的 $dis[i]$ 值要小于等于 $x$，设我们要求的电池容量为 $c$ 那么可以得出这个式子： $dis[i]\le x\le c$,走到下一个充电点至少要走 $dis[i]$，所以得出 $dis[i]\le x\le c-dis[i]$，设下一个点是 $j$，那么走到点 $j$ 至少就要 $w_{ij}$，所以可以得到 $c-dis[j]\ge x-w_{i,j}\ge dis[j]$，结合一下可以得到 $dis[j]\le x-w_{i,j}$，也就是 $dis[j]\le c-dis[i]-w_{i,j}$，交换一下位置得到 $c\ge dis[i]+dis[j]+w_{i,j}$，所以我们就可以把边权改成他。

接下来来考虑如何进行最小生成树：这已经很显而易见了，把之前的边权已更新然后直接跑最小生成树。

然后就是倍增求 LCA 了（应该都会吧），这个有一点不同的是我们要用一个跟倍增数组一样的维护最大值的数组，这样就可以在求两点距离的时候处理出最大值然后直接输出即可。

为什么存副本只存单边？因为后面建最小生成树的时候会建两条，所以没有必要去存正反两边，费时又费空间。

对了一定不要在 dfs 的里面进行 init 函数，会 TLE。

## code

```cpp
#include<bits/stdc++.h>
#define re register 
#define bug cout<<"WTF?"<<'\n'
#define int long long
#define N 1000100
using namespace std;
struct sb{int u,v,w,next;}e[N],e1[N],e2[N];//e存放一开始输入的边，e1存放一开始的边的一个副本（单边），e2存放生成的最小生成树的边 
int head1[N],cnt1=0,head2[N],cnt2=0;//链式前向星用 
struct SB{int id,val;bool operator < (const SB &b)const{return val>b.val;}};//dij堆优化用，按边权从小到大排序 
int n,m,k,qq,vis[N],num;//vis标记当前点是否已求出最短路，num最小生成树建边计数器 
int dis[N],fa[N],f[N][21],dep[N],maxn[N][21];//
priority_queue<SB>q;//优先队列 
inline int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){f=ch!='-';ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return f?x:-x;}
int cmp(sb a,sb b){return a.w<b.w;}//结构体比较函数，按边权从小到大排序 
void add(int u,int v,int w){e[++cnt1]=(sb){u,v,w,head1[u]};head1[u]=cnt1; }//一开始的存图 
void Add(int u,int v,int w){e2[++cnt2]=(sb){u,v,w,head2[u]};head2[u]=cnt2;}//建好最小生成树后存图 
int fid(int x){return fa[x]==x?x:fa[x]=fid(fa[x]);}//并查集find函数 
void dij()
{
//	bug;
	memset(dis,0x3f,sizeof dis);//dis赋初值 
	{
		dis[0]=0;//标记起点不用走 
		q.push((SB){0,0});//起点入列 
		while(!q.empty())//只要队列不空 
		{
//			bug;
			SB qwq=q.top();q.pop();//取出队头元素 
			int u=qwq.id;//取出起点编号 
			if(vis[u])continue;//如果已经有最短路了就放弃 
			vis[u]=1;//标记 
			for(int i=head1[u];i;i=e[i].next)//遍历每一条与之相连的边 
			{
//				bug;
				int v=e[i].v;//取出终点 
				if(dis[v]>dis[u]+e[i].w)//松弛操作 
				  dis[v]=dis[u]+e[i].w;
				if(!vis[v])q.push((SB){v,dis[v]});//如果没有最短路的话就放入队列 
			}
		}
	}
}
void kruskal()
{
//	bug;
	for(re int i=1;i<=n;i++)
	  fa[i]=i;//初始化fa数组 
	for(re int i=1;i<=m;i++)
	{
//		bug;
		int xx=fid(e1[i].u);
		int yy=fid(e1[i].v);//取出起点和终点的代表节点 
		if(xx!=yy)//不相等 
		{
			fa[xx]=yy;//合并并建边 
			Add(e1[i].u,e1[i].v,e1[i].w);
			Add(e1[i].v,e1[i].u,e1[i].w);
			num++;//建边数加一 
			if(num==n-1)return ;//够n-1条就退出 
		}
	}
}
void init()//预处理倍增数组 
{
	for(re int j=1;j<=20;j++)//千万不能两个反过来 
	  for(re int i=1;i<=n;i++)
	  {
	    f[i][j]=f[f[i][j-1]][j-1];//祖先倍增 
		maxn[i][j]=max(maxn[i][j-1],maxn[f[i][j-1]][j-1]);//最长路径倍增 
	  }
}
void dfs(int u,int fa)//处理每一个点的深度 
{
//	init(); 
//	bug;
	f[u][0]=fa;//这里先把父亲节点给处理出来 
	for(re int i=head2[u];i;i=e2[i].next)//枚举每一条与之相连的边 
	{
//		bug;
		int v=e2[i].v;//取出终点 
		if(v==fa)continue;//如果终点就是父节点就跳过 
		dep[v]=dep[u]+1;//处理深度 
		maxn[v][0]=e2[i].w;//maxn也要赋初值 
		dfs(v,u);//继续搜索 
	}
}
int get_max(int x,int y)//x到y路径的最大值 
{
	int ans=0;//ans存放答案 
	if(dep[x]<dep[y])swap(x,y);//保证x的深度比y大 
	for(re int i=20;i>=0;i--)
	{
		if(dep[f[x][i]]<dep[y])continue;//如果会超过y就不跳 
		ans=max(ans,maxn[x][i]);//更新路径上边权最大值 
		x=f[x][i];//更新x点的编号 
	}
	if(x==y)return ans;//如果xy在一条链上就直接返回答案 
	for(re int i=20;i>=0;i--)
	{
		if(f[x][i]==f[y][i])continue;//如果跳到公共祖先就返回 
		ans=max(ans,max(maxn[x][i],maxn[y][i]));//否则就更新最大值 
		x=f[x][i];y=f[y][i];//更新xy点编号 
	}
	ans=max(ans,max(maxn[x][0],maxn[y][0]));//更新最大值 
	return ans;//返回答案 
}
signed main()
{
	n=read();m=read();k=read();qq=read();
	for(re int i=1;i<=m;i++)
	{
//		bug;
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);//输入边 
		e1[i]=(sb){u,v,w};//存副本 
	}
	for(re int i=1;i<=k;i++)
//	  bug,
	  add(0,i,0),add(i,0,0);//建超级源点并连边 
	dij();//跑一遍dij 
//	cout<<'\n';
//	for(int i=1;i<=n;i++)
//	  cout<<dis[i]<<'\n';
	for(re int i=1;i<=m;i++)
//	  bug,
	  e1[i].w+=dis[e1[i].u]+dis[e1[i].v];//更新边的权值 
	sort(e1+1,e1+m+1,cmp);//排序 
	kruskal();//生成最小生成树 
	dep[1]=1;//标记第一个点的深度为1 
//	cout<<'\n';
//	for(int i=1;i<=m;i++)
//		cout<<e2[i].u<<" "<<e2[i].v<<" "<<e2[i].w<<" "<<e2[i].next<<'\n';
	dfs(1,-1);//开始搜索处理深度 
	init();//预处理出两个倍增数组 
	for(re int i=1;i<=qq;i++)
	{
		int x=read(),y=read();
		cout<<get_max(x,y)<<'\n';//直接输出询问 
	}
	return 0;//好习惯 
}
```

---

