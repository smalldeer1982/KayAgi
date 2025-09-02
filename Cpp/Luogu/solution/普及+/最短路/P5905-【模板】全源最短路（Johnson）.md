# 【模板】全源最短路（Johnson）

## 题目描述

给定一个包含 $n$ 个结点和 $m$ 条带权边的有向图，求所有点对间的最短路径长度，一条路径的长度定义为这条路径上所有边的权值和。

注意：

1. 边权**可能**为负，且图中**可能**存在重边和自环；

2. 部分数据卡 $n$ 轮 SPFA 算法。



## 说明/提示

【样例解释】

左图为样例 $1$ 给出的有向图，最短路构成的答案矩阵为：

```
0 4 11 8 11 
1000000000 0 7 4 7 
1000000000 -5 0 -3 0 
1000000000 -2 5 0 3 
1000000000 -1 4 1 0 
```

右图为样例 $2$ 给出的有向图，红色标注的边构成了负环，注意给出的图不一定连通。

![](https://cdn.luogu.com.cn/upload/image_hosting/7lb35u4u.png)

【数据范围】

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^3,\ \ 1\leq m\leq 6\times 10^3,\ \ 1\leq u,v\leq n,\ \ -3\times 10^5\leq w\leq 3\times 10^5$。

对于 $20\%$ 的数据，$1\leq n\leq 100$，不存在负环（可用于验证 Floyd 正确性）

对于另外 $20\%$ 的数据，$w\ge 0$（可用于验证 Dijkstra 正确性）

upd. 添加一组 Hack 数据：针对 SPFA 的 SLF 优化

## 样例 #1

### 输入

```
5 7
1 2 4
1 4 10
2 3 7
4 5 3
4 2 -2
3 4 -3
5 3 4```

### 输出

```
128
1000000072
999999978
1000000026
1000000014
```

## 样例 #2

### 输入

```
5 5
1 2 4
3 4 9
3 4 -3
4 5 3
5 3 -2```

### 输出

```
-1```

# 题解

## 作者：StudyingFather (赞：619)

Johnson 和 Floyd 一样，是一种能求出无负环图上任意两点间最短路径的算法。该算法在 1977 年由 Donald B. Johnson 提出。

## 1 算法概述

任意两点间的最短路可以通过枚举起点，跑 $n$ 次 Bellman-Ford 算法解决，时间复杂度是 $O(n^2m)$ 的，也可以直接用 Floyd 算法解决，时间复杂度为 $O(n^3)$ 。

注意到堆优化的 Dijkstra 算法求单源最短路径的时间复杂度比 Bellman-Ford 更优，如果枚举起点，跑 $n$ 次 Dijkstra 算法，就可以在 $O(nm\log m)$ （本文中的 Dijkstra 采用 `priority_queue` 实现，下同）的时间复杂度内解决本问题，比上述跑 $n$ 次 Bellman-Ford 算法的时间复杂度更优秀，在稀疏图上也比 Floyd 算法的时间复杂度更加优秀。

但 Dijkstra 算法不能正确求解带负权边的最短路，因此我们需要对原图上的边进行预处理，确保所有边的边权均非负。

一种容易想到的方法是给所有边的边权同时加上一个正数 $x$ ，从而让所有边的边权均非负。如果新图上起点到终点的最短路经过了 $k$ 条边，则将最短路减去 $kx$ 即可得到实际最短路。

但这样的方法是错误的。考虑下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/d4cvwbqn.png)

$1 \to 2$ 的最短路为 $1 \to 5 \to 3 \to 2$，长度为 $-2$。

但假如我们把每条边的边权加上 $5$ 呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/ahz1uv1u.png)

新图上 $1 \to 2$ 的最短路为 $1 \to 4 \to 2$ ，已经不是实际的最短路了。

Johnson 算法则通过另外一种方法来给每条边重新标注边权。

我们新建一个虚拟节点（在这里我们就设它的编号为 $0$ ）。从这个点向其他所有点连一条边权为 $0$ 的边。

接下来用 Bellman-Ford 算法求出从 $0$ 号点到其他所有点的最短路，记为 $h_i$ 。

假如存在一条从 $u$ 点到 $v$ 点，边权为 $w$ 的边，则我们将该边的边权重新设置为 $w+h_u-h_v$ 。

接下来以每个点为起点，跑 $n$ 轮 Dijkstra 算法即可求出任意两点间的最短路了。

容易看出，该算法的时间复杂度是 $O(nm\log m)$ 。

Q：那这么说，Dijkstra 也可以求出负权图（无负环）的单源最短路径了？  
A：没错。但是预处理要跑一遍 Bellman-Ford，还不如直接用 Bellman-Ford 呢。

## 2 正确性证明

为什么这样重新标注边权的方式是正确的呢？

在讨论这个问题之前，我们先讨论一个物理概念——势能。

诸如重力势能，电势能这样的势能都有一个特点，势能的变化量只和起点和终点的相对位置有关，而与起点到终点所走的路径无关。

势能还有一个特点，势能的绝对值往往取决于设置的零势能点，但无论将零势能点设置在哪里，两点间势能的差值是一定的。

接下来回到正题。

在重新标记后的图上，从 $s$ 点到 $t$ 点的一条路径 $s \to p_1 \to p_2 \to \dots \to p_k \to t$ 的长度表达式如下：

$(w(s,p_1)+h_s-h_{p_1})+(w(p_1,p_2)+h_{p_1}-h_{p_2})+ \dots +(w(p_k,t)+h_{p_k}-h_t)$

化简后得到：

$w(s,p_1)+w(p_1,p_2)+ \dots +w(p_k,t)+h_s-h_t$ 

无论我们从 $s$ 到 $t$ 走的是哪一条路径， $h_s-h_t$ 的值是不变的，这正与势能的性质相吻合！

为了方便，下面我们就把 $h_i$ 称为 $i$ 点的势能。

上面的新图中 $s \to t$ 的最短路的长度表达式由两部分组成，前面的边权和为原图中 $s \to t$ 的最短路，后面则是两点间的势能差。因为两点间势能的差为定值，因此原图上 $s \to t$ 的最短路与新图上 $s \to t$ 的最短路相对应。

到这里我们的正确性证明已经解决了一半——我们证明了重新标注边权后图上的最短路径仍然是原来的最短路径。接下来我们需要证明新图中所有边的边权非负，因为在非负权图上，Dijkstra 算法能够保证得出正确的结果。

根据三角形不等式，新图上任意一边 $(u,v)$ 上两点满足： $h_v \leq h_u + w(u,v)$ 。这条边重新标记后的边权为 $w'(u,v)=w(u,v)+h_u-h_v \geq 0$ 。这样我们证明了新图上的边权均非负。

至此，我们就证明了 Johnson 算法的正确性。

## 3 参考代码

（被各位 D 惨了，所以把代码扔到 clang-format 里格式化了下 /wq）

```cpp
#include <cstring>
#include <iostream>
#include <queue>
#define INF 1e9
using namespace std;
struct edge {
  int v, w, next;
} e[10005];
struct node {
  int dis, id;
  bool operator<(const node& a) const { return dis > a.dis; }
  node(int d, int x) { dis = d, id = x; }
};
int head[5005], vis[5005], t[5005];
int cnt, n, m;
long long h[5005], dis[5005];
void addedge(int u, int v, int w) {
  e[++cnt].v = v;
  e[cnt].w = w;
  e[cnt].next = head[u];
  head[u] = cnt;
}
bool spfa(int s) {
  queue<int> q;
  memset(h, 63, sizeof(h));
  h[s] = 0, vis[s] = 1;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].v;
      if (h[v] > h[u] + e[i].w) {
        h[v] = h[u] + e[i].w;
        if (!vis[v]) {
          vis[v] = 1;
          q.push(v);
          t[v]++;
          if (t[v] == n + 1) return false;
        }
      }
    }
  }
  return true;
}
void dijkstra(int s) {
  priority_queue<node> q;
  for (int i = 1; i <= n; i++) dis[i] = INF;
  memset(vis, 0, sizeof(vis));
  dis[s] = 0;
  q.push(node(0, s));
  while (!q.empty()) {
    int u = q.top().id;
    q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].v;
      if (dis[v] > dis[u] + e[i].w) {
        dis[v] = dis[u] + e[i].w;
        if (!vis[v]) q.push(node(dis[v], v));
      }
    }
  }
  return;
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    addedge(u, v, w);
  }
  for (int i = 1; i <= n; i++) addedge(0, i, 0);
  if (!spfa(0)) {
    cout << -1 << endl;
    return 0;
  }
  for (int u = 1; u <= n; u++)
    for (int i = head[u]; i; i = e[i].next) e[i].w += h[u] - h[e[i].v];
  for (int i = 1; i <= n; i++) {
    dijkstra(i);
    long long ans = 0;
    for (int j = 1; j <= n; j++) {
      if (dis[j] == INF)
        ans += j * INF;
      else
        ans += j * (dis[j] + h[j] - h[i]);
    }
    cout << ans << endl;
  }
  return 0;
}
```

## 4 应用

虽然算法名告诉我们它可以用于求解全源最短路，但是实际场景中需要求解全源最短路的场合并不太多。

在费用流问题中，存在思想类似的 [Primal-Dual 原始对偶算法](https://oi-wiki.org/graph/flow/min-cost/#primal-dual)。它通过类似的方法将所有边的边权转为非负值，从而可以使用 Dijkstra 算法求出残量网络上的最短增广路。

## Reference

- [Johnson's algorithm - Wikipedia](https://en.wikipedia.org/wiki/Johnson%27s_algorithm)
- 《算法导论（中译本，第 3 版）》，25.3 用于稀疏图的 Johnson 算法，409-411 页

---

## 作者：ix35 (赞：58)

## P5905 Johnson 全源最短路

---

有一篇洛谷日报讲的是这个，写得很不错：[Johnson 全源最短路 By Studing Father](https://studyingfather.blog.luogu.org/johnson-algorithm)

先来看全源最短路的几个基本想法：

1. Floyd：时间复杂度为 $O(n^3)$，能够解决负权边，不能解决负环，缺点就是很慢，虽然常数很小但是这道题当然是过不了的；

2. Dijkstra：以每个点为源点做一次 Dijkstra，时间复杂度为 $O(nm\log n)$，时间上可以过，但是 Dijkstra 只能解决非负权边，一旦出现负权边就得另想办法；

3. BellmanFord：以每个点为源点做一次 BellmanFord，时间复杂度为 $O(n^2m)$，能搞定所有权值情况，但是太慢。至于队列版本（SPFA），已经被我卡到本机 200s 左右（有什么 SPFA 优化可以交，过了我就继续卡）。

首先来解决负环的问题，这个跑一遍 BellmanFord 就可以了。

看一遍上面的几个算法，似乎只有 Dijkstra 有希望了。而 Johnson 全源最短路算法就是改造这张图的边权，使得它等效成一张非负权图的方案。

思路非常简单，我们对于每个顶点 $u$，取某个值 $d_u$，然后利用差分的思想，将一条边 $(u,v,w)$ 改造成 $(u,v,w-d_u+d_v)$，这样一条路径 $(p_1,p_2,...,p_k)$ 中，新图上 $d_{p_2},...,d_{p_{k-1}}$ 这些值都会在边权相加的过程中抵消掉，假设原图中这条路径长为 $W$，那么新图中的长度就是 $W-d_{p_1}+d_{p_k}$。对于确定的起点和终点，$d_{p_k}-d_{p_1}$ 只是一个常数偏移量，不会影响最短路的路线。

下面我们要使得 $w-d_u+d_v$ 是一个非负数，这样就可以用 Dijkstra 了，这不难实现，因为这是一个三角形不等式的形式。

建立超级源点 $n+1$，从它向原图中每个点建一条 $0$ 权边，先从它为源点用 BellmanFord 跑最短路，直接令 $d_u$ 等于这个最短路即可，三角形不等式自然满足。

参考代码（BellmanFord 采用队列版本，因为是几个模板拼凑的，所以显得有些冗长）：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3010,INF=1000000000;
priority_queue < pair<int,int> > q;
queue <int> qu;
int n,m,tot,tot2,x,y,z,d[MAXN][MAXN],vis[MAXN];
int hd[MAXN],ver[3*MAXN],nx[3*MAXN],edge[3*MAXN];
int dis[MAXN],hd2[MAXN],ver2[6*MAXN],nx2[6*MAXN],edge2[6*MAXN],vis2[MAXN],tim[MAXN];
struct Edge {
	Edge () {u=v=w=0;}
	Edge (int a,int b,int c) {u=a,v=b,w=c;}
	int u,v,w;
}e[3*MAXN];
void add_edge (int x,int y,int z) {
	ver[++tot]=y;
	edge[tot]=z,nx[tot]=hd[x];
	hd[x]=tot;
	return;
}
void add_edge1 (int x,int y,int z) {
	ver2[++tot2]=y;
	edge2[tot2]=z,nx2[tot2]=hd2[x];
	hd2[x]=tot2;
	return;
}
bool spfa (int s) {
	dis[s]=0,vis2[s]=1;
	qu.push(s);
	while (!qu.empty()) {
		int a=qu.front();
		qu.pop();
		vis2[a]=0;
		if (++tim[a]>n-1) {
			return 0;
		}
		for (int i=hd2[a];i;i=nx2[i]) {
			if (dis[ver2[i]]>dis[a]+edge2[i]) {
				dis[ver2[i]]=dis[a]+edge2[i];
				if (!vis2[ver2[i]]) {
					vis2[ver2[i]]=1;
					qu.push(ver2[i]);
				}
			}
		}
	}
	return 1;
}
void dijkstra (int s) {
	memset(vis,0,sizeof(vis));
	d[s][s]=0;
	q.push(make_pair(0,s));
	while (!q.empty()) {
		pair <int,int> a=q.top();
		q.pop();
		if (vis[a.second]) {continue;}
		vis[a.second]=1;
		for (int i=hd[a.second];i;i=nx[i]) {
			if (d[s][ver[i]]>d[s][a.second]+edge[i]) {
				d[s][ver[i]]=d[s][a.second]+edge[i];
				q.push(make_pair(-d[s][ver[i]],ver[i]));
			}
		}
	}
}
int main () {
	memset(dis,0x3f,sizeof(dis));
	memset(d,0x3f,sizeof(d));
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		add_edge1(x,y,z);
		if (z>500000||z<-500000) {printf("err\n");return 0;}
		e[i]=Edge(x,y,z);
	}
	for (int i=1;i<=n;i++) {
		add_edge1(n+1,i,0);
	}
	if (!spfa(n+1)) {
		printf("-1\n");
		return 0;
	}
	for (int i=1;i<=m;i++) {
		add_edge(e[i].u,e[i].v,e[i].w+dis[e[i].u]-dis[e[i].v]);
	}
	for (int i=1;i<=n;i++) {
		dijkstra(i);
	}
	for (int i=1;i<=n;i++) {
		ll ans=0;
		for (int j=1;j<=n;j++) {
			if (d[i][j]==0x3f3f3f3f) {ans+=1ll*INF*j;}
			else {ans+=1ll*(d[i][j]-dis[i]+dis[j])*j;}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：SDqwq (赞：30)

[博客食用更佳](https://www.luogu.com.cn/blog/Sham-Devour/solution-p5905)

[前置芝士：最短路](https://oi-wiki.org//graph/shortest-path/)

### Description

> 给出一个 $n$ 个结点和 $m$ 条边的 **有向图**。若图中有负环，直接输出 `-1`。否则定义 $dis_{i,j}$ 为结点 $i$ 到结点 $j$ 的最短路，求出：

> $$\sum\limits_{i=1}^{n} j\times dis_{i,j}$$

> 其中，若结点 $i$ 不能到达结点 $j$，则 $dis_{i,j}=10^9$；若 $i=j$，则 $dis_{i,j}=0$。

### Solution

Johnson 全源最短路模板题。

- 建立一个虚点 $0$ 号结点。

- 从 $0$ 号结点向 $i(i\in[1,n])$ 连接一条权值为 $0$ 的有向边。

- 使用 spfa 算法求出从 $0$ 号结点到 $i(i\in[1,n])$ 的最短路 $dis_i$。

- 由于 dijkstra 不能求负权最短路，所以将连接 $u,v$ 的边权 $w$ 更新为 $w+dis_u-dis_v$。

- 接下来对 $i(i\in[1,n])$ 号点进行 dijkstra，统计答案即可。

**注意：**

- 记得开 long long。

- 判负环时由于增加了 $0$ 号点，所以当某个结点入队次数 $>n$ 时才说明有负环。

### Problem Solving!

```cpp
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>

typedef long long ll;

const int inf = 0x3f3f3f3f;

using namespace std;

int n, m, cnt, elast[3005], dis[3005], d[3005], num[3005];
bool vis[3005];

struct edge {
	int to, len, next;
} e[9005];

queue<int> q;

void add (int u, int v, int w) {
	e[++cnt].to = v;
	e[cnt].len = w;
	e[cnt].next = elast[u];
	elast[u] = cnt;
}

bool spfa (int x) {
	dis[x] = 0;
	q.push(x);
	vis[x] = true;
	num[x]++;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = elast[u]; i != 0; i = e[i].next)
			if (dis[e[i].to] > dis[u] + e[i].len) {
				dis[e[i].to] = dis[u] + e[i].len;
				if (!vis[e[i].to]) {
					q.push(e[i].to);
					vis[e[i].to] = true;
					num[e[i].to]++;
					if (num[e[i].to] == n + 1)
						return false;
				}
			}
	}
	return true;
}

struct ybmq {
	int dis, id;
} bjhz[3005];

bool operator < (ybmq x, ybmq y) {
	return x.dis > y.dis;
}

void dijkstra (int x) {
	priority_queue<ybmq> pq;
	d[x] = 0;
	ybmq u;
	u.dis = 0;
	u.id = x;
	pq.push(u);
	while (!pq.empty()) {
		ybmq u = pq.top();
		pq.pop();
		if (vis[u.id])
			continue;
		vis[u.id] = true;
		for (int i = elast[u.id]; i != 0; i = e[i].next)
			if (d[e[i].to] > d[u.id] + e[i].len) {
				d[e[i].to] = d[u.id] + e[i].len;
				ybmq v;
				v.dis = d[e[i].to];
				v.id = e[i].to;
				pq.push(v);
			}
	}
}

int main () {
	memset(dis, inf, sizeof(dis));
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add(u, v, w);
	}
	for (int i = 1; i <= n; i++)
		add(n + 1, i, 0);
	bool flag = spfa(n + 1);
	if (!flag) {
		puts("-1");
		return 0;
	}
	for (int i = 1; i <= n; i++)
		for (int j = elast[i]; j != 0; j = e[j].next)
			e[j].len += dis[i] - dis[e[j].to];
	for (int i = 1; i <= n; i++) {
		memset(d, inf, sizeof(d));
		memset(vis, false, sizeof(vis));
		dijkstra(i);
		ll ans = 0;
		for (int j = 1; j <= n; j++) {
			if (d[j] == inf)
				ans += 1ll * 1e9 * j;
			else
				ans += 1ll * (d[j] - dis[i] + dis[j]) * j;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Mine_King (赞：24)

- **2020/06/10 Upd：根据评论做了一些小修改。**
- **2020/11/05 Upd：被hack了，更改了代码并修了一点小锅**

例题：[P5905 【模板】Johnson 全源最短路](https://www.luogu.com.cn/problem/P5905)

首先考虑求全源最短路的几种方法：

- Floyd：时间复杂度$O(n^3)$，可以处理负权边，但不能处理负环，而且速度很慢。
- Bellman-Ford：以每个点为源点做一次Bellman-Ford，时间复杂度$O(n^2m)$，可以处理负权边，可以处理负环，但好像比Floyd还慢？
- dijkstra：以每个点为源点做一次dijkstra，时间复杂度$O(nmlogm)$，不能处理负权边，但比前面两个快多了。

好像……只有dijkstra还有希望？但负权边处理不了真是很棘手啊。

一种方法是让每条边都加上一个数$x$使得边权为正，但考虑下图：  
![](https://i.loli.net/2020/05/09/TxFjbA3oypn7Vmi.png)  
$1$到$2$的最短路应为：$1 -> 3 -> 4 -> 2$，长度为$-1$。如果我们把每条边的边权都加上$5$：  
![](https://i.loli.net/2020/05/09/X9TGEagWif8q6CU.png)  
此时的最短路是：$1 -> 5 -> 2$，就不是实际的最短路了，所以这种方法行不通

**注：因为两条路径经过的边数不一样，加的值也不同，所以会导致这种错误。**

接下来，就该 Johnson 登场啦！Johnson 其实就是用另一种方法标记边权啦。

首先来看看实现方法：我们新建一个虚拟结点（不妨设他的编号为0），由他向其他的所有结点都连一条边权为$0$的边，然后求0号节点为源点的单源最短路，存到一个$h$数组中。然后，让每条边的权值$w$变为$w+h_u-h_v$，这里$u$和$v$分别为这条边的起点和终点。然后再以每个点为源点做 dijkstra 就OK了。

Q：那这么说，Dijkstra 也可以求出负权图（无负环）的单源最短路径了？  
A：没错。但是预处理要跑一遍 Bellman-Ford，还不如直接用 Bellman-Ford 呢。

如何证明这是正确的呢？

首先，从$s$到$t$的路径中随便取出一条：
$$s -> p_1 -> p_2 -> \cdots -> p_k -> t$$
则这条路径的长度为：
$$(w_{s,p_1}+h_s-h_{p_1})+(w_{p_1,p_2}+h_{p_1}-h_{p_2})+\dots+(w_{p_k,t}+h_{p_k}-h_t)$$
简化后得到：
$$w_{s,p_1}+w_{p_1,p_2}+\cdots+w_{p_k,t}+h_s-h_t$$
可以发现，不管走哪条路径，最后都是$+h_s-h_t$，而$h_s$和$h_t$又是不变的，所以最终得到的最短路径还是原来的最短路径。

到这里已经证明一半了，接下来要证明得到的边权非负，必须要无负权边才能使 dijkstra 跑出来的结果正确。根据三角形不等式（就是那个三角形里任意两条边的长度之和大于等于另一条边的长度），新图上的任意一条边$(u,v)$上的两点满足：$h_v \le w_{u,v}+h_u$，则新边的边权$w_{u,v}+h_u-h_v \ge 0$。所以新图的边权非负。

正确性证明就是这个亚子。

**代码实现（注意处理精度问题，该开ll的时候开ll）：**
```cpp
#include<cstdio>
#include<queue>
#define MAXN 5005
#define MAXM 10005
#define INF 1e9
using namespace std;
int n,m;
int vis[MAXN];
long long h[MAXN],dis[MAXN];
bool f[MAXN];
struct graph
{
	int tot;
	int hd[MAXN];
	int nxt[MAXM],to[MAXM],dt[MAXM];
	void add(int x,int y,int w)
	{
		tot++;
		nxt[tot]=hd[x];
		hd[x]=tot;
		to[tot]=y;
		dt[tot]=w;
		return ;
	}
}g;//链式前向星
bool SPFA(int s)//这里用了Bellman-Ford的队列优化
{
	queue<int>q;
	for(int i=1;i<=n;++i) h[i]=INF,f[i]=false;
	h[s]=0;
	f[s]=true;
	q.push(s);
	while(!q.empty())
	{
		int xx=q.front();
		q.pop();
		f[xx]=false;
		for(int i=g.hd[xx];i;i=g.nxt[i])
			if(h[g.to[i]]>h[xx]+g.dt[i])
			{
				h[g.to[i]]=h[xx]+g.dt[i];
				if(!f[g.to[i]])
				{
					if(++vis[g.to[i]]>=n+1) return false;//注意在有重边的情况下要记录入队次数而不是松弛次数，以及因为新加入了一个0点，所以次数应该判n+1而不是n。
					f[g.to[i]]=true,q.push(g.to[i]);
				}
			}
	}
	return true;
}
void dijkstra(int s)
{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
	for(int i=1;i<=n;i++) dis[i]=INF,f[i]=false;
	q.push(make_pair(0,s));
	dis[s]=0;
	while(!q.empty())
	{
		int xx=q.top().second;
		q.pop();
		if(!f[xx])
		{
			f[xx]=true;
			for(int i=g.hd[xx];i;i=g.nxt[i])
				if(dis[g.to[i]]>dis[xx]+g.dt[i])
				{
					dis[g.to[i]]=dis[xx]+g.dt[i];
					if(!f[g.to[i]])
						q.push(make_pair(dis[g.to[i]],g.to[i]));
				}
		}
	}
	return ;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g.add(u,v,w);
	}
	for(int i=1;i<=n;i++) g.add(0,i,0);//建虚拟节点0并且往其他的点都连一条边权为0的边
	if(!SPFA(0))//求h的同时也判了负环
	{
		printf("-1");
		return 0;
	}
	for(int u=1;u<=n;u++)
		for(int i=g.hd[u];i;i=g.nxt[i])
			g.dt[i]+=h[u]-h[g.to[i]];//求新边的边权
	for(int i=1;i<=n;i++)
	{
		dijkstra(i);//以每个点为源点做一遍dijkstra
		long long ans=0;
		for(int j=1;j<=n;j++)//记录答案
			if(dis[j]==INF) ans+=1ll*j*INF;
			else ans+=1ll*j*(dis[j]+(h[j]-h[i]));
		printf("%lld\n",ans);
	}
	return 0;
}
```
最后[安利一发博客](https://www.luogu.com.cn/blog/195331/)

---

## 作者：king_xbz (赞：16)

# 前言

谁说SPFA死了？谁说SPFA一定会被卡死？谁说Johnson是DIJ的舞台？今天，我将在这里为SPFA正名，**他，还活着**。这是本题迄今唯一的一篇SPFA的题解，希望能让读者朋友们满意。

# 最短路问题

常见的最短路算法有SPFA，Dijkstra，Floyd,Bellman-Ford等算法。如果让这些算法同时跑全源最短路问题，那他们的复杂度如下：

Dijkstra：时间复杂度为 $O(n×(E + VlogV))$

Floyd：时间复杂度为$O(n^3)$

SPFA：时间复杂度为$O(n×k×m)$（玄学待定）

Bellman-Ford：时间复杂度为 $O(VE)$

显然，n遍floyd或者n遍SPFA貌似要比Floyd更优。然而，SPFA容易被卡成doge，Dijkstra则无法在有负环好好表现。**怎么办呢？优化！**

# Johnson和他的Re-weight

在 1977 年，[Donald B. Johnson](http://en.wikipedia.org/wiki/Johnson's_algorithm) 提出了对所有边的权值进行 "re-weight" 的算法，使得边的权值非负，进而可以使用Dijkstra算法来处理此问题。

显然，我们不能简单地对每条边的权值加上一个较大的正数，使其非负。

新增一个源顶点s，并使其与所有顶点连通，新边赋权值为0，使用 Bellman-Ford 算法计算新的顶点到所有其它顶点的最短路径，根据公式：

```cpp
w(u, v) = w(u, v) + (h[u] - h[v]).
```

进行边权更新使其非负。

该算法复杂度：$O(V^2logV + V×E)$

**仅此而已吗？**

# 全新的升级

随着时代的变迁，Bellman——Ford算法已经被更优的SPFA算法取代，而SPFA在随机数据下的表现也远胜于dijkstra。所以，我们要寻求变革，**全新的双SPFA——Johnson算法出世了！**

毒瘤的出题人显然不想看到SPFA这个简单明了但有些玄学的算法生存下去。于是祭出了稠密图大发。我们SPFA党也相应的推出了**堆优化SPFA**来与堆优化Dij分庭抗礼。

代码和普通SPFA相似，只是将queue改为priority_queue

代码：[【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

```cpp
inline void SPFA(int x)
{
	priority_queue <point>q;
	for(fint i=1;i<=n;i++)
	dis[i]=inf;
	memset(vis,0,sizeof(vis));
	dis[x]=0,vis[x]=1;
	q.push((point){x,0});
	while(!q.empty())
	{
		point hea=q.top();
		q.pop();
		vis[hea.now]=0;
		for(fint i=head[hea.now];i;i=e[i].nxt)
		if(dis[e[i].to]>dis[hea.now]+e[i].val)
		{
			dis[e[i].to]=dis[hea.now]+e[i].val;
			if(!vis[e[i].to])
			vis[e[i].to]=1,q.push((point){e[i].to,dis[e[i].to]});
		}
	}
	return ;
}
```

速度果然碾压Dij

那么面对只有68分的普通双SPFA，我们是否可以将其变成100分呢？

**答案是肯定的**

我们用SPFA_pre()预处理并判环，然后多源跑SPFA()根据Johnson算法更新答案即可。

Johnson的re—weight算法

```cpp
for(fint i=1;i<=m;i++)
	x=read(),y=read(),z=read(),adds(x,y,z);
	for(fint i=1;i<=n;i++)
	adds(0,i,0);
	if(SPFA_pre())
	{
		cout<<-1;
		return 0;
	}
	for(fint i=1;i<=n;i++)
	for(fint j=head[i];j;j=e[j].nxt)
	e[j].val+=d[i]-d[e[j].to];
	for(fint i=1;i<=n;i++)
	{
		SPFA(i);
		int ans=0;
		for(fint j=1;j<=n;j++)
		if(dis[j]!=inf)
		ans+=j*(dis[j]+(d[j]-d[i]));
		else
		ans+=j*inf;
		printf("%lld\n",ans);
	}
```

预处理+判环的第一个SPFA

```cpp
inline int SPFA_pre()
{
	queue <int>q;
	for(fint i=0;i<=n;i++)
	d[i]=inf;
	memset(vis,0,sizeof(vis));
	memset(vis_tim,0,sizeof(vis_tim));
	d[0]=0,vis[0]=1;
	q.push(0);
	while(!q.empty())
	{
		int hea=q.front();
		q.pop();
		vis[hea]=0;
		for(fint i=head[hea];i;i=e[i].nxt)
		if(d[e[i].to]>d[hea]+e[i].val)
		{
			d[e[i].to]=d[hea]+e[i].val;
			if(!vis[e[i].to])
			{
				vis[e[i].to]=1,q.push(e[i].to);
				vis_tim[e[i].to]++;
				if(vis_tim[e[i].to]>n)
				return 1;
			}
		}
	}
	return 0;
}
```

堆优化跑最短路的第二个SPFA

```cpp
inline void SPFA(int x)
{
	priority_queue <point>q;
	for(fint i=1;i<=n;i++)
	dis[i]=inf;
	memset(vis,0,sizeof(vis));
	dis[x]=0,vis[x]=1;
	q.push((point){x,0});
	while(!q.empty())
	{
		point hea=q.top();
		q.pop();
		vis[hea.now]=0;
		for(fint i=head[hea.now];i;i=e[i].nxt)
		if(dis[e[i].to]>dis[hea.now]+e[i].val)
		{
			dis[e[i].to]=dis[hea.now]+e[i].val;
			if(!vis[e[i].to])
			vis[e[i].to]=1,q.push((point){e[i].to,dis[e[i].to]});
		}
	}
	return ;
}
```

这样我们就用这个奄奄一息的SPFA算法创造了奇迹！！！

[完整代码](https://www.luogu.com.cn/paste/xnsruisq)

祝大家AC愉快，谢谢大家！

---

## 作者：warzone (赞：15)

与其说 $Johnson$ 算法是一个全源最短路算法,  
不如说它是在求最短路时将负权图转化为正权图的算法。

### 一、问题导入

在求最短路的时候,我们经常会遇到负权边

首选的方式肯定是 $Floyd$ $(\Theta(n^3)\text{ 全源 })$  
以及 $Bellman\text{-}Ford$ $(\Theta(nm)\text{ 单源 })$,二者各有优缺点: 

1. $Floyd$ 适用于全源,用于单源太过浪费,可用于负权边但无法用于负环,  
	而且适用于稠密图,对于稀疏图其时间不敢恭维。


2. $Bellman\text{-}Ford$ 适用于单源,用于全源则 $\Theta(n^2m)$ 的复杂度比 $Floyd$ 更高,  
	虽可以解决负环,但不论怎么优化总会被构造卡到最坏复杂度。
     
    
  而能获得较优且稳定的复杂度的,只有 $Dijkstra$ 了,其在稠密图上复杂度为 $\Theta(n^2)$,  
稀疏图上通过堆优化可以优化到 $\Theta(nm\log_2m)$ ,但其只能应用于正权图。


对于 稀疏图+负权+多次求解 的组合,就要通过 $Johnson$ 算法改造全图了。

### 二、算法概述

这里略过证明和部分过程,可以去看另外几位 $dalao$ 的题解

首先,要保证没有负环(通过一轮 $Bellman\text{-}Ford$ ),既然没有负环,  
那么去掉正权边它就会变成一个 有向无环图$(DAG)$。

既然是 $DAG$，那其在求最短路的过程中必有一定的层次性,  
不难发现加入正权边后也是如此

于是引入一个概念：势。新增一个 $0$ 号节点，从这个点向所有点连上边权为 $0$ 的边,  
用 $Bellman\text{-}Ford$ 所求出的 $0$ 号点到点 $p$ 的最短路就是该点的势

我们可以明显发现势完好地保留了这种层次：

![](https://cdn.luogu.com.cn/upload/image_hosting/sx6582kk.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

如图,标红的为负权边,可以发现这些点的势满足拓补关系

于是,我们将边加上其入点和出点的势的差,就能得到一个正权图,图上的最短路和原来路径相同

算出最短路之后再将长度减去起点和终点的势的差,就能得到最终的最短路长度

于是不难得到转化和求最短路长度的代码：
```cpp
//略去手写的模板，头文件
int dis[3010][3010],value[6010],h[3010];
int head[3010],to[6010],next[6010];
int n,m;
bool isuse[3010];
struct point{
	int id,length;
	inline bool operator <(point p){
		return length<p.length;}
}p,q;//Dij的键值
HEAP<point,6010> heap;//手写堆,略去实现
inline bool spfa(int id){//深搜Bellman-Ford判负环并求势
	if(isuse[id]) return 1;
	isuse[id]=1;
	for(int i=head[id];i!=0;i=next[i])
		if(h[to[i]]>h[id]+value[i]){
			h[to[i]]=h[id]+value[i];
			if(spfa(to[i])) return 1;
		}
	return isuse[id]=0;
}
int main(){
	cin>>n>>m;//cin,cout实均为手写快读快写,此处略去实现
	for(int from;m>0;m--){
		cin>>from>>to[m]>>value[m];
		next[m]=head[from];
		head[from]=m;
	}
	for(int i=1;i<=n;i++)
		if(spfa(i)) return cout<<-1,0;//求势
	for(int id=1;id<=n;id++)
		for(int i=head[id];i!=0;i=next[i])
			value[i]=value[i]+h[id]-h[to[i]];//给边加上势差 
	memset(dis,0x7f,sizeof(dis));
	long long ans;
	for(int begin=1;begin<=n;begin++){
		p.id=begin,p.length=dis[begin][begin]=0;
		heap.push(p),ans=0;
		while(!heap.empty()){//Dij求最短路 
			p=heap.top(),heap.pop();
			if(dis[begin][p.id]<p.length) continue;
			for(int i=head[p.id];i!=0;i=next[i])
				if(dis[begin][to[i]]>p.length+value[i]){
					q.length=dis[begin][q.id=to[i]]=p.length+value[i];
					heap.push(q);
				}
		}
		for(long long i=1;i<=n;i++) //减去总的势差并统计 
			ans+=i*(dis[begin][i]==0x7f7f7f7f? 1e9:dis[begin][i]+h[i]-h[begin]);
		cout<<ans<<'\n';
	}
    return 0;
}
```

### 三、应用举例

这个算法有什么用呢? 用它跑单源还不如 $Bellman\text{-}Ford$

但这一算法在**网络流**上,有极为重要的作用

求解最小费用最大流就是不断求解最短路,然后通过最短路增广的过程

由于走反向边费用要取负,无法使用 $Dijksta$ 增广,只能通过 $Bellman\text{-}Ford$

而有了 $Johnson$ 算法以后,就可以先做一轮 $Bellman\text{-}Ford$,

然后不断通过 $Dijksta$ 增广，运行更稳定,效率更高

(快死了的 $SPFA$ 能少用一点是一点)

费用流模板是$\color{blue}\text{蓝}$的，$Johnson$ 模板是$\color{green}\text{绿}$的,费用流题目$\color{purple}\text{紫}$题起步，

$1\color{blue}\text{蓝}$ $+1\color{green}\text{绿}$ $=n\color{purple}\text{紫}$，何乐而不为呢

---

## 作者：ACMlearning (赞：14)

新手刚接触关于最短路径问题，然而今天却接触了一道Johnson全源最短路的问题，于是就从Bellman-Ford 算法开始学习，最后终于对于Johnson有了一点自己的领悟，于是在此发表题解留念，还望各位巨佬及大神指点批评。

#### 一、负环问题
刚开始准备用spfa直接判断负环，发现连第二个样例都没过去（原因，spfa不能直接判断非连通图的负环，于是我就建个虚拟点，与每个点连一条边权为0的边就可以判断了）。最后由于需要Bellman-Ford 算法求h[]，所以还是采用的Bellman-Ford 算法进行负环的判断。

#### 二、全源最短路的解决：

①Floyd：时间复杂度为 O(n^3），能够解决负权边，不能解决负环，缺点就是很慢。

②Dijkstra：以每个点为源点做一次 Dijkstra，时间复杂度为O(nmlogn)，时间上可以过，但是 Dijkstra 只能解决非负权边，一旦出现负权边就得另想办法；

两个好像都不能解决问题：开始学习Johnson 算法

③Johnson 算法：是用来解决在有负权重边图里的最短路径问题的，它主要了结合 Dijkstra 算法和 Bellman-Ford 算法。同时 Johnson 算法在稀疏图里复杂度是 O(n^2log(n))，数据可以过。
Johnson 算法的证明：（由于推导小白看不懂，就用第一个样例的数据来证明）

![](https://cdn.luogu.com.cn/upload/image_hosting/fw57sg1k.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于第一个点跑一遍Dijkstra算法算出：
dis[1][1] = 0;dis[1][2] = 4;dis[1][3] = 11;dis[1][4] = 10;dis[1][5] = 13;
与正确答案不一致，因为存在负权值，所以是不能使用 Dijkstra 去求最短路径的。

而Johnson 的方法是通过给每个节点设置一个值，用这些节点的值去做 reweight，公式如下：

w[u, v] = w[u, v] +h[u] - h[v]

h[x] 就是节点 X 的值，这个值是通过 Bellman-Ford 求出来的。

现在来说说怎么求这个 h[x]。其实很简单，在这个图中添加一个虚拟的节点这个虚拟节点指向所有的节点，而指向所有节点的边权重为 0。如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/jgut8bbe.png)

h[x] 就是用 Bellman-ford 去求这个虚拟节点到每个节点的最短距离。
一遍Bellman-ford求出h[0] = 0,h[1] = 0,h[2] = -5,h[3] = 0,h[4] = -3,h[5] = 0.

有了这些 h[x] 值后就可以对每条边进行 reweight 操作了，对每条边进行w[u, v] = w[u, v] +h[u] - h[v]得如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2fgy0nns.png)

此时用Dijkstra算法跑一遍算出dis[1][1] = 0;dis[1][2] = 9;dis[1][3] = 11;dis[1][4] = 11;dis[1][5] = 11; 

由于之前对每条边进行 reweight 操作了，最终的路径应该要减去开始节点的 h 值，再加上结束节点的 h 值。

以dis[1][4]为例：
dis[1][4] = (w(1,2)+h[1]-h[2])+(w(2,3)+h[2]-h[3])+(w(3,4)+h[3]-h[4]) =w(1,2)+w(2,3)+w(3,4)+h[1]-h[4]

所以正确的dis[1][4] = w(1,2)+w(2,3)+w(3,4) = dis[1][4] (重新reweight之后跑出来的结果)+h[4]-h[1] = 8;

同理：可以得到dis[1][1] = 0;dis[1][2] = 4;dis[1][3] = 11;dis[1][4] = 8;dis[1][5] = 11;

数据证明完毕。

参考代码（我采用的是vector来存储邻接表）
```c
#include<iostream>
#include<cstring>
#include<string>
#include<math.h>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define inf 1000000000
typedef long long ll;
typedef unsigned long long ull;

int N,M;
struct edge{
	int v;//顶点和边的权值
	ll w;
};
edge make_edge(int _v,int _w){
	edge cur;cur.v = _v;cur.w = _w;
	return cur;
}
struct node {
	ll dis;
	int v;
	friend bool operator < (node A,node B){
		return A.dis>B.dis;//重载小于号，默认为大顶堆 
	}
};
node make_node(ll _dis,int _v){
	node cur;cur.dis = _dis;cur.v = _v;
	return cur;
}
vector<edge> g[100005];
ll dis[3005][3005]; //dis[i][j]表示第i个点到第j个点的最短距离 
ll d[3005]; //存放虚拟点到各个点的最短距离 
int vis[100005];
priority_queue<node>q; //优先队列来存放顶点和改顶点距源点的距离 

bool Dellman_Ford(int s){
	int i,j,k;
	for(i = 1;i<=N;i++){
		int flag = 0;
		for(j = 1;j<=N;j++){
			for(k = 0;k<g[j].size();k++){
				if(d[g[j][k].v]>d[j]+g[j][k].w){
					flag = 1;
					d[g[j][k].v] = d[j]+g[j][k].w;	
				}
			}
		}
		if(flag == 0)
			return true;
	}
	//进行负环的验证 
	for(j = 1;j<=N;j++){
		for(k = 0;k<g[j].size();k++){
			if(d[g[j][k].v]>d[j]+g[j][k].w){
				return false;	
			}
		}
	}
	return true;
}
void dijkstra(int s){
	int now;//用于存放从队列中取出当前距离最小的点 
	memset(vis,0,sizeof(vis));
	dis[s][s] = 0;
	q.push(make_node(dis[s][s],s));
	while(!q.empty()){
		now = q.top().v;q.pop(); //取出队列中距离最小的点 
		if(vis[now] == 1)continue;//如果该点访问过则continue 
		vis[now] = 1;
		for(int  i = 0;i<g[now].size();i++){
			int v = g[now][i].v; //与now相邻的点 
			int w = g[now][i].w; //边权 
			if(dis[s][v]>dis[s][now]+w){
				dis[s][v] = dis[s][now]+w;
				q.push(make_node(dis[s][v],v));
			}
		}
	}
}

int main(){
	int i,j,k;
	int a,b;
	ll c;
	cin>>N>>M;
	for(i = 1;i<=N;i++){
		for(j = 1;j<=N;j++){
			dis[i][j] = inf;
		}
	}
	for(i = 1;i<=N;i++){
		dis[i][i] = 0;
	}
	for(i = 1;i<=M;i++){
		scanf("%d %d %lld",&a,&b,&c);
		g[a].push_back(make_edge(b,c));
	}
	if(!Dellman_Ford(0)){
		printf("-1\n");
		return 0;
	}
	
	//更新权值
	for(i = 1;i<=N;i++){
		for(j = 0;j<g[i].size();j++){
			g[i][j].w = g[i][j].w + d[i]-d[g[i][j].v];
		}
	}
	for(i = 1;i<=N;i++){
		dijkstra(i);
	}
	
	//更新最小距离 
	for(i =1;i<=N;i++){
		for(j = 1;j<=N;j++){
			if(dis[i][j] == inf)//将第i行要输出的数存在dis[i][0]中 
				dis[i][0] +=j*dis[i][j];
			else{
				dis[i][j] = dis[i][j]+d[j]-d[i];
				dis[i][0]+=j*dis[i][j];
			}
		}
	}
	
	for(i = 1;i<=N;i++){
			printf("%lld\n",dis[i][0]);
	}
	return 0;
}
```







---

## 作者：银杉水杉秃杉 (赞：7)

朋友们好啊！

[题目传送门 P5905 【模板】Johnson 全源最短路](https://www.luogu.com.cn/problem/P5905)

题目不用再做过多的描述，我们直奔主题。

很明显这是一道最短路问题，我们脑海里浮现出了$Floyd$、$Spfa$和$Dijkstra$。再来看看数据范围$n≤1000$，$m≤6000$。$Floyd$ $O(n^3)$就可以排除了。

题目告诉我们：

**1. 边权可能为负，且图中可能存在重边和自环；**

**2. 部分数据卡$n$轮$Spfa$算法。**

所以只能先用$Spfa$来判断负环，再用$Dijkstra+$堆优化来求最短路。

温馨提示：同学们可以先去看一下这两道模板题：

[P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)

[P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

这里有些细节要注意一下（划重点啦）。众所周知，$Dijkstra$是不能处理负边的，我们必须把每条边变成非负值。但我们不能每条边同时加同一个数，这样会影响答案。

这就是这道题最妙的地方了。当我们跑$Spfa$时，我们可以先设一个虚拟点$0$，这个点连上每一个点，边权为$0$。然后我们以这个点位源点，跑一个$Spfa$单源最短路径，用$h$数组记录，即$0$到每个点的最短路。接着，对于一条边$u,v,w_{u,v}$。由三角形不等式$h_u+w_{u,v}≥h_v$得，$w_{u,v}+h_u-h_v≥0$。我们只需要将每条边的边权$w_{u,v}$加上$(h_u-h_v)$即可满足非负。最终求出来的最短路$d_{s,t}$减去$(h_s-h_t)$即可。

完整代码（AC code）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int n,m,t;
int head[3010],vis[3010],cnt[3010],h[3010],d[3010];
struct edge
{
	int to,next,val;
}e[100010];
void addedge(int u,int v,int w)
{
	e[++t].to=v;
	e[t].next=head[u];
	e[t].val=w;
	head[u]=t;
}
bool spfa(int s)//本题中s为0
{
	queue<int> q;
	memset(vis,0,sizeof(vis));//初始化
	for (int i=1;i<=n;i++)
		h[i]=inf;
	h[s]=0;
	vis[s]=1;
	q.push(s);
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for (int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to,w=e[i].val;
			if (h[v]>h[u]+w)
			{
				h[v]=h[u]+w;
				if (!vis[v])
				{
					vis[v]=1;
					cnt[v]++;
					q.push(v);
					if (cnt[v]==n+1)//当一个点被扫过超过n次时，说明存在负环
						return 0;
				}
			}
		}
	}
	return 1;
}
void dijkstra(int s)
{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
	memset(vis,0,sizeof(vis));//重置
	for (int i=1;i<=n;i++)
		d[i]=inf;
	d[s]=0;
	q.push(make_pair(0,s));
	while (!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if (vis[u])
			continue;
		vis[u]=1;
		for (int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to,w=e[i].val;
			if (d[v]>d[u]+w)
			{
				d[v]=d[u]+w;
				q.push(make_pair(d[v],v));
			}
		}
	}
}
int main()
{
	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w; 
		addedge(u,v,w);//单向建边
	}
	for (int i=1;i<=n;i++)
		addedge(0,i,0);//以0为起点，其余每个点为终点建边
	if (!spfa(0))//若存在负环
	{
		cout<<-1<<endl;
		return 0;
	}
	for (int u=1;u<=n;u++)
		for (int i=head[u];i;i=e[i].next)//将每条边变为非负值
		{
			int v=e[i].to;
			e[i].val+=h[u]-h[v];
		}
	for (int i=1;i<=n;i++)
	{
		dijkstra(i);//以每个点为起点求最短路
		long long ans=0;
		for (int j=1;j<=n;j++)
			if (d[j]==inf)
				ans+=1ll*j*inf;//如题目描述的最大值1e9
			else
				ans+=1ll*j*(d[j]+h[j]-h[i]);
		cout<<ans<<endl;
	}
	return 0;
}//❀❀完结撒花❀❀
```
这道题的题解就到这了，谢谢朋友们！

---

## 作者：Immortal_Bird (赞：7)

基建第十篇

Johnson 全源最短路解决的是带负边权的任意两点之间最短路。

由于$Dijkstra$不能解决负边权，
- 我们考虑新建一个节点$S$，每个点向它连一条权值为0的边，然后在这个点跑一次$SPFA$判负环

- 在没有负环的情况下，由于$dij$不能处理负边权，我们对于每一条边的权值$w[u,v]$变成$w(u,v)+d(u)-d(v)$，找到合适的$d(u)$和$d(v)$令$w(u,v)+d(u)-d(v)>=0$。这样就不存在了负边权，再在每一个点跑一遍$Dij$。

- $d(u)$和$d(v)$可以设为$S$到$u$和$v$的最短路。当图中存在负边权时$d(u),d(v)$可能小于0.但是$d(u)-d(v)>=0$且$d(u)-d(v)>=|w(u,v)|$。所以这样下来整个图就是一个正全图了。

- 统计的时候把它加上就行。

[P5905](https://www.luogu.com.cn/problem/P5905)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int x=0;bool f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}

void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(48+x%10);
}

void writeln(int x){write(x);putchar('\n');}
void writebl(int x){write(x);putchar(' ');}

#define I inline
#define R register

const int maxn = 3e3+5; 
const int maxm = maxn*6;
#define inf 1000000000

struct Johnson{
	struct edge{int v,w,next;}e[maxm];	
	int head[maxn],vis[maxn],dis[maxn],tot,h[maxn];	
	void add(int u,int v,int w){e[++tot]=(edge){v,w,head[u]};head[u]=tot;}
	struct node{
		int dis;int pos;
		bool operator < (const node &x)const{return x.dis<dis;}
	};	
	priority_queue<node> q;	
	I void dijkstra(int s){
		memset(dis,0x3f,sizeof(dis));memset(vis,0,sizeof(vis));
		dis[s] = 0;
		q.push((node){0,s});
		while(!q.empty()){
			node tmp = q.top();q.pop();
			int x = tmp.pos,d = tmp.dis;
			if(vis[x])continue;vis[x] = 1;
			for(int i = head[x];i;i = e[i].next){
				int v = e[i].v;
				if(dis[v] > dis[x] + e[i].w){
					dis[v] = dis[x] + e[i].w;
					if(!vis[v])q.push((node){dis[v],v});
				}
			}
		}
	}
	int tim[maxn];
	I bool spfa(int s,int n){
		queue<int> q;
		memset(h,0x3f,sizeof(h));memset(vis,0,sizeof(vis));
		h[s]=0;vis[s]=1;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();vis[u]=0;
			if(++tim[u]>n-1)return 0;
			for(R int i=head[u];i;i=e[i].next){
				int v=e[i].v;
				if(h[v]>h[u]+e[i].w){
					h[v]=h[u]+e[i].w;
					if(!vis[v])q.push(v),vis[v]=1;
				}
			}
		}
		return 1;
	}
}J;
int n,m;
signed main(){
	n=read(),m=read();
	for(R int i=1,u,v,w;i<=m;++i){
		u=read(),v=read(),w=read();
		J.add(u,v,w);
	}
	for(R int i=1;i<=n;++i)J.add(0,i,0);
	if(!J.spfa(0,n)){puts("-1");return 0;}
	for(R int u=1;u<=n;++u)
		for(R int i=J.head[u];i;i=J.e[i].next){
			int v=J.e[i].v;
			J.e[i].w+=J.h[u]-J.h[v];
		}
	for(R int i=1;i<=n;++i){
		J.dijkstra(i);
		long long ans=0;
		for(R int j=1;j<=n;++j){
			if(J.dis[j]==J.dis[n+1])ans+=j*inf;
			else ans+=j*(J.dis[j]+J.h[j]-J.h[i]);
		}
		writeln(ans);
	}
}

```


---

## 作者：intel_core (赞：7)

~~偶尔看到这个题目，直接切了~~  
### 进入正题  
1.分析    
众所周知，$Dijkstra$算法的时间复杂度是$O(mlogn)$的   
在本题的稀疏图下，比$Floyd$要优   
但是$Dijkstra$只能处理边权为正的最短路  
所以我们要想办法让边权变成正的   

2.实(kou)验(hu)    
做法1：将每个边权直接赋为正，最后再减去经过的边   
贴代码（无主程）：   
```cpp
#include<bits/stdc++.h>
#define NR 100001
#define MR 200001
using namespace std;
struct Edge{
	int to,next,w;
}g[MR];
int dis[MR];
int fte[NR];
struct Node{
	int x,dis;
	bool operator < (const Node &A) const {
		return dis > A.dis;
	}
};
int n,m,s;
int tot;
void add(int x,int y,int w){
	g[++tot]=(Edge){y,fte[x],w};
	fte[x]=tot;
}
bool flag[MR];
int cnt[NR];
void dijkstra(int x){
	memset(dis,999999,sizeof(dis));
	dis[x]=0;
	priority_queue<Node>q;
	q.push((Node){x,0});
 	cnt[x]=0;
	while(!q.empty()){
		int AK=q.top().x;
		q.pop();
		if(flag[AK])continue;
		flag[AK]=true;
		for(int i=fte[AK];i;i=g[i].next){
			int y=g[i].to;
			if(flag[y])continue;
			if(dis[y]<=dis[AK]+g[i].w)continue;
			dis[y]=dis[AK]+g[i].w;
        cnt[y]=cnt[x]+1;
			q.push((Node){y,dis[y]});
		}
	}
}
```
~~都说了是口胡，你还信？？？~~   
这个算法有个漏洞：原来边权满足的不等式，在加上一个值后可能不等号会变号。   
所以我们需要想个办法让所有边权变成正数。   
3.概念引入     
引入一个物理概念：势能   
文化课比较好的同学应该知道，势能只与起点和终点的位置有关；与走过的路程无关。     
所以两点间势能的差值是不变的。     
将u,v两点的边权用势能表示：   
$w(u,v)+h_u-h_v$       
将一条路径表示出来:   
$v_1->v_2->v_3.......->v_n$    
它的距离为：   
$w(v_1,v_2)+w(v_2,v_3)+...+w(v_(n-1),v_n)+h_1-h_2.....+h_(n-1)+h_n$   
化简得$w(v_1,v_2)+w(v_2,v_3)+...+w(v_(n-1),v_n)+h_1-h_n$  
这就是从$v_1$到$v_n$的势能差   
于是我们就有了一个思路    
4.$Johnson$全源最短路    
有了前面的理论基础，我们可以先计算出所有点关于势能原点的势能差   
再利用势能差把边权转成正的   
这就是$Johnson$全源最短路的精髓    
简单介绍下算法流程:      
*    建立虚拟原点，$SPFA$跑出所有点的势能
*    利用每个点的势能将所有边权转成正数
*    $Dijkstra$跑两点间势能差    
*    将势能差转化为两点间最短路    
*    $Then?$   
*    $AC$本题   
以下是参考代码：   

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=3e3+10;
const int MR=6e3+10;
struct edge{
	int to,next,val;
}g[MR<<1];
int fte[NR];
int tot;
void add(int x,int y,int z){
	g[++tot]=(edge){y,fte[x],z};
	fte[x]=tot;
}
int cnt[NR];
bool panduan[NR];
queue<int>q;
int dist[NR];
int n,m;
bool SPFA(int s){
	memset(dist,999999,sizeof(dist));
	dist[s]=0;
	q.push(s);
	panduan[s]=true;
	cnt[s]++;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		panduan[x]=false;
		for(int i=fte[x];i;i=g[i].next){
			int y=g[i].to;
			if(dist[y]<=dist[x]+g[i].val)continue;
			dist[y]=dist[x]+g[i].val;
			if(panduan[y])continue;
			q.push(y);
			panduan[y]=true;
			cnt[y]++;
			if(cnt[y]==n+1){
				return false;
			}
		}
	}	
	return true;
}
struct node{
	int id;
	int dis;
	bool operator <(const node &T)const{
		return dis>T.dis;
	}
};
int dis[NR];
priority_queue<node>pq;
void dijkstra(int s){
	memset(panduan,false,sizeof(panduan));
	for(int i=1;i<=n;i++)dis[i]=1e9;
	dis[s]=0;
	pq.push((node){s,0});
	while(!pq.empty()){
		int x=pq.top().id;
		pq.pop();
		if(panduan[x])continue;
		panduan[x]=true;
		for(int i=fte[x];i;i=g[i].next){
			int y=g[i].to;
			if(dis[y]<=dis[x]+g[i].val)continue;
			dis[y]=dis[x]+g[i].val;
			if(panduan[y])continue;
			pq.push((node){y,dis[y]});
		}
	}
}
signed main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout); 
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);
	}
	for(int i=1;i<=n;i++)add(0,i,0);
	if(!SPFA(0)){
		puts("-1");
		return 0;
	}
	for(int i=1;i<=n;i++)
		for(int j=fte[i];j;j=g[j].next)
			g[j].val=g[j].val+dist[i]-dist[g[j].to];
	for(int i=1;i<=n;i++){
		long long ans=0;
		dijkstra(i);
		for(int j=1;j<=n;j++){
			if(dis[j]!=1e9)ans+=1ll*j*(dis[j]+dist[j]-dist[i]);
			else ans+=1e9*j;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：zjrdmd (赞：5)

对原来的题解做一个修正，原来过了这次也求管理大大给过啊qwq

2020.8.7：原来的代码被新增的数据hack了，感谢@Oak_limy大佬的提醒，现在代码是**是可以AC的。**

Johnson 和 Floyd 一样，是一种能求出无负环图上任意两点间最短路径的算法。

对于此题来说，folyd复杂度肯定会炸，SPFA也已经被卡死了，那么可虑dijkstra吧，但是我们会发现，毒瘤的出题人设置了负权，那么我们新算法的思路其实就是把负权变为正权，那么柿子其他几位大佬讲的很清楚了，我只来讲一下证明吧

众所周知:
   
   假设我们要更改的边的编号为i,0号点（超级节点）到其他点的最短路为f[1],f[2],f[3],f[4].........f[n-1],f[n];
   
那么i号边经过柿子变化会变成edge[i].val=edge[i].val+f[这条边的起点]-f[这条边的终点]

那么假设我们要求从x->y的最短路，那么我们对原式和经过处理后的柿子做一个比较
 
**原式**：val[x,p1]+val[p1,p2]+val[p2,p3]+val[p3,p4]+.....val[pt-1，t]

**变化后的柿子**:(val[x,p1]+f[x]-val[p1])+(val[p1,p2]+f[p1]-f[p2])+(val[p2,p3]+f[p2]-f[p3])+(val[pt-1,t]+f[pt-1]-p[t];

这个是显而易见的对吧，那么我们对柿子进行化简，可以得到一个新的柿子

val[x,p1]+val[p1,p2]+val[p2,p3]+val[p3,p4]+val[pt-1,t]+f[s]-f[t]

 那么我们把两个柿子做一个对比，可以发现新的柿子比原来的柿子只是多了一个+f[s]-f[t]，那么这个只是一个常量偏移，不会对答案产生任何影响对吧，那么我们就证明了他的正确性

------------
我们再来康康**证明2**

我们如果要证明边权不为负数，那么其实需要证明的就是val[x,y]+f[x]-f[y]>=0

转化一下可以得到val[x,y]+f[x]>=f[y],这也是显而易见的，根据三角形不等式可以轻松证明，需要明白的一点是0到达其他点的最短路一定是<=0的，那么并且f[y]<=f[x]画张图自己模拟一下就好啦！！！

------------

终于讲完了，打这么多字好累啊（感谢各位神仙可以认真读完我的题解），那么上福利代码吧！！！！

------------
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stdlib.h>
#include <queue>
#include <stack>
#define ri register int
#define inf 1e9

struct Node{
	int to,next,val;
}edge[60005];
int head[5005],cnt=1;
int in[5005];
int dis[5005];
bool vis[5005];
int n,m;
int dist[5005];

inline void add(int u,int v,int w){
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	edge[cnt].val=w;
	head[u]=cnt++;
} 

inline bool spfa(){
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;
	vis[0]=true;
	std::queue<int>q;
	q.push(0);
	while(q.size()){
		int p=q.front();
		q.pop();
		vis[p]=false;
		for(ri i=head[p];i;i=edge[i].next){
			int v=edge[i].to;
			if(dis[v]>dis[p]+edge[i].val){
				dis[v]=dis[p]+edge[i].val;
				if(!vis[v])vis[v]=true,q.push(v),in[v]++;
				if(in[v]>=n+1)return true;
			}
		}
	} 
	return false;
}
struct node{
	int pos,dis;
	bool operator<(const node &x)const{
		return x.dis<dis;
	}
};

inline void dijkstra(int k){
	std::priority_queue<node>q;
	long long ans=0;
	q.push((node){k,0});
	for(ri i=1;i<=n;i++){
		vis[i]=false;
		dist[i]=inf;
	} 
	dist[k]=0;
	while(q.size()){
		int p=q.top().pos;
		q.pop(); 
		if(vis[p])continue;
		vis[p]=true;
		for(ri i=head[p];i;i=edge[i].next){
			int v=edge[i].to;
			if(dist[v]>dist[p]+edge[i].val){
				dist[v]=dist[p]+edge[i].val;
				if(!vis[v])q.push((node){v,dist[v]});
			}
		}
	}
	for(ri i=1;i<=n;i++){
		if(dist[i]==inf){
			ans+=i*inf;
			continue;
		}
		ans=ans+(1ll*i*(dist[i]+dis[i]-dis[k]));
	}
	printf("%lld\n",ans);
}
int main(){
	scanf("%d%d",&n,&m);
	for(ri i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	for(ri i=1;i<=n;i++){
		add(0,i,0);
	}
	if(spfa()){
		printf("-1");
		return 0;
	}
	for(ri i=1;i<=n;i++){//每一个起点 
		for(ri j=head[i];j;j=edge[j].next){//每一条边 
			edge[j].val=edge[j].val+dis[i]-dis[edge[j].to];
		}
	}
	for(ri i=1;i<=n;i++){
		dijkstra(i);
	}
	return 0;
} 
```


------------
**最后再把转换的核心代码展示一下：**


------------
```cpp
for(ri i=1;i<=n;i++){
		for(ri j=head[i];j;j=edge[j].next){
			edge[j].val=edge[j].val+dis[i]-dis[edge[j].to];
		}
	}
```


------------
敲一篇题解不容易，麻烦管理员给过吧,谢谢啦。

如果我哪里写错了，请各位神仙指出，我一定会及时改正！！




---

## 作者：D2T1 (赞：4)

[$\color{blue}{\text {pwp }~{\to\textbf{My blog}\gets}}~\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

以此纪念我学会该算法。

**update 2021-7-7:** 更新复杂度。

# Johnson 全源最短路

Johnson 全源最短路可以用来求有负权的图的全源最短路。

## 步骤

1.  新建一个虚拟 $0$ 号节点。

2. 在节点 $0$ 至节点 $i(i \in [1,n])$ 中插入一条权值为 $0$ 的有向边。

3. 使用 Bellman-ford 算法（SPFA 也可）计算节点 $0$ 到其它节点的最短路径（顺便判断负环），记为 $H_i$。

4. 将原图每条边的权值 $w_{u,v}$ 改为 $w_{u,v}+H_u-H_v$。

5. 跑 $n$ 轮 Dijkstra 算法，求出全源最短路。

复杂度：$O(1)+O(n)+O(nm)+O(m)+n*O((n+m)\log n)=O(nm\log n)$

## 证明

### 如何证明 $w_{u,v}+H_u-H_v \geq 0$？

显然，对于任意一条边 $(u,v)$ 满足 $H_v \leq w_{u,v}+H_u$，否则就可以用 $w_{u,v}+H_u$ 去更新 $H_v$ 的答案。

对上不等式稍加变形即可证明。

### 如何证明改变权值后不改变最短路？

设 $s$ 到 $t$ 的一条路径 $s \to n_1 \to n_2 \to ... \to t$，改变权值后的路径长度为 $(w_{s,n_1}+H_s-H_{n_1})+(w_{n_1,n_2}+H_{n_1}-H_{n_2})+...+(w_{n_k,t}+H_{n_k}-H_t)=w_{s,n_1}+w_{n_1,n_2}+...+w_{n_k,t}+H_s-H_t$。

所以不管是哪条路径，最后加上的总是 $H_s-H_t$，不影响最短路。

因此 Johnson 全源最短路是正确的。

## 代码

```cpp
//P5905
#include <cstring>
#include <utility>
#include <cstdio>
#include <queue>
using namespace std;
const int N=10000,INF=1e9;

int Head[N],Edge[N],Leng[N],Next[N],tot;
long long H[N],C[N],Dis[N];
bool V[N];
int n,m; 
inline void addedge(int u,int v,int w){ Edge[++tot]=v,Leng[tot]=w,Next[tot]=Head[u],Head[u]=tot; }

inline bool spfa(int s){
	queue<int> q;
	memset(H,0x3f,sizeof(H));
	memset(V,false,sizeof(V));
	H[s]=0,V[s]=true,q.push(s);
	while(!q.empty()){
		int x=q.front(); q.pop(); V[x]=false;
		for(int i=Head[x]; i; i=Next[i]){
			int y=Edge[i],z=Leng[i];
			if(H[y]>H[x]+z){
				H[y]=H[x]+z;
				if(!V[y]){
					V[y]=true,q.push(y),++C[y];
					if(C[y]>n) return false;
				} 
			}
		}
	}
	return true;
}

inline void dijkstra(int s){
	priority_queue<pair<int,int> > q;
	for(int i=1; i<=n; ++i) Dis[i]=INF;
	memset(V,false,sizeof(V));
	Dis[s]=0,q.push(make_pair(0,s));
	while(!q.empty()){
		int x=q.top().second; q.pop();
		if(V[x]) continue;
		V[x]=true;
		for(int i=Head[x]; i; i=Next[i]){
			int y=Edge[i],z=Leng[i];
			if(Dis[y]>Dis[x]+z){
				Dis[y]=Dis[x]+z;
				if(!V[y]) q.push(make_pair(-Dis[y],y));
			}
		}
	}
	return;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		addedge(x,y,z);
	}
	
	for(int i=1; i<=n; ++i) addedge(0,i,0);
	if(!spfa(0)) return puts("-1")&0;
	
	for(int i=1; i<=n; ++i)
		for(int j=Head[i]; j; j=Next[j])
			Leng[j]=Leng[j]+H[i]-H[Edge[j]];
	for(int i=1; i<=n; ++i){
		dijkstra(i);
		long long ans=0;
		for(int j=1; j<=n; ++j)
			ans+=j*(Dis[j]==INF ? INF : Dis[j]-H[i]+H[j]);
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

