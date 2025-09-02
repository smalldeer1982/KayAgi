# [JOI Open 2022] 放学路 / School Road

## 题目背景

**译自 [JOI Open 2022](https://contests.ioi-jp.org/open-2022/index.html) T3. [通学路](https://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2022/school_road/2022-open-school_road-statement.pdf) / [School Road](http://s3-ap-northeast-1.amazonaws.com/data.cms.ioi-jp.org/open-2022/school_road/2022-open-school_road-statement-en.pdf)。**

----

在洛谷上，本题测试点和子任务配置可能导致评测结果页面难以理解。具体地，将评测结果页面中的子任务编号 $x$ 转为二进制后，从低到高第 $i$ 位为 $1$ 就表示子任务内所有测试点均满足题目中的子任务 $i$ 的限制。

## 题目描述

河狸国由 $N$ 座城市组成，编号为 $1 \sim N$。共有 $M$ 条道路连接这些城市，道路编号为 $1 \sim M$。道路 $i$（$1 \le i \le M$）双向连接城市 $A_i$ 和 $B_i$，并且道路 $i$ 的长度为 $C_i$。保证经过一定数量的道路，均可以从任意一座城市到达任意其他城市。

Bitaro 是一只住在城市 $1$ 的河狸。他要去城市 $N$ 上学。他上学通常都走一样的路线。他的上学路线满足如下条件。

- 令 $L$ 为从城市 $1$ 到城市 $N$ 的最短距离。
- Bitaro 的上学路是一条连接城市 $1$ 和城市 $N$ 且长度为 $L$ 的路径。

因为今天天气好，Bitaro 决定绕路回家。也就是说，他会选择一条从城市 $N$ 到城市 $1$ 且长度大于 $L$ 的路径。因为 Bitaro 很容易厌倦，他不想经过同一座城市多于一次。因此，当他绕远路回家时，不允许经过同一座城市多于一次，并且不允许走回头路。

给定河狸国的城市和道路的信息，写一个程序确定是否存在一条从学校到 Bitaro 的家的远路。

**赛时提醒：Bitaro 不允许在回家途中经过相同的城市超过一次，但是并不禁止经过在他上学路线中经过的城市。**

## 说明/提示

**【样例解释 \#1】**

在这组样例中，从城市 $1$（Bitaro 家）到城市 $4$（学校）的最短距离是 $5$。

有两条到 Bitaro 家并且不经过同一座城市多于一次的路径。

- 按顺序经过道路 $3 \to 1$，长度为 $5$ 的路径，按 $4 \to 2 \to 1$ 的顺序经过城市。
- 按顺序经过道路 $4 \to 2$，长度为 $5$ 的路径，按 $4 \to 3 \to 1$ 的顺序经过城市。

因为不存在到 Bitaro 家的，长度大于 $5$ 且不经过同一座城市多于一次的路径，因此输出 $0$。

这组样例满足所有子任务的限制。

----

**【样例解释 \#2】**

在这组样例中，从城市 $1$（Bitaro 家）到城市 $4$（学校）的最短距离是 $5$。

有两条到 Bitaro 家并且不经过同一座城市多于一次的路径。

- 按顺序经过道路 $3 \to 1$，长度为 $5$ 的路径，按 $4 \to 2 \to 1$ 的顺序经过城市。
- 按顺序经过道路 $4 \to 2$，长度为 $6$ 的路径，按 $4 \to 3 \to 1$ 的顺序经过城市。

因为存在到 Bitaro 家的，长度大于 $5$ 且不经过同一座城市多于一次的路径，因此输出 $1$。

这组样例满足所有子任务的限制。

----

**【样例解释 \#3】**

这组样例满足子任务 1、2、3、5 的限制。

----

**【样例解释 \#4】**

这组样例满足所有子任务的限制。

----

**【样例解释 \#5】**

这组样例满足子任务 1、2、3、5 的限制。

----

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（7 分）：$M \le 40$。
- 子任务 2（15 分）：$N \le 18$。
- 子任务 3（23 分）：$M - N \le 13$。
- 子任务 4（35 分）：对于任意三座不同的城市 $a, b, c$，均存在一条从城市 $a$ 到城市 $c$ 且不经过城市 $b$ 的路径。
- 子任务 5（20 分）：无特殊限制。

对于所有数据，满足 $2 \le N \le {10}^5$，$1 \le M \le 2 \times {10}^5$，$1 \le A_i < B_i \le N$，$1 \le C_i \le {10}^9$，保证经过一定数量的道路，均可以从任意一个城市到达任意其他城市。

## 样例 #1

### 输入

```
4 4
1 2 1
1 3 2
2 4 4
3 4 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4 4
1 2 1
1 3 3
2 4 4
3 4 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 4
1 2 1
1 2 2
1 3 3
1 3 3
```

### 输出

```
0
```

## 样例 #4

### 输入

```
4 5
1 2 1
1 3 2
2 4 4
3 4 3
2 3 1
```

### 输出

```
1
```

## 样例 #5

### 输入

```
12 17
2 4 656247308
4 6 106088453
1 5 754343261
9 12 497827261
3 8 759830309
3 4 61084725
1 6 324702188
3 6 415317430
7 12 846175092
5 8 278621369
1 10 891247646
10 12 755236904
6 8 511967203
5 6 597197970
1 7 800309458
7 9 348347831
10 11 134217757
```

### 输出

```
0
```

# 题解

## 作者：_LPF_ (赞：17)

[题目链接](https://www.luogu.com.cn/problem/P8426)

- 给定无向图，判断是否有 $1\to n$ 且长度不等于最短路的**简单路径**。
- $n\leq 10^5,m\leq 2\times 10^5$。

根据部分分大力得到正解，一步步来。

首先对于 $m\leq 40$ 可以搜索出所有路径，$n\leq 18$ 直接状压，那么目光聚集于 $m-n\leq 13$。

不难条件反射出广义串并联图方法（[广告：广义串并联图方法学习笔记](https://www.cnblogs.com/lpf-666/p/16602167.html)），缩合后得到 $m\leq 3\times 13$ 同样可以搜索做，当然这一方法的作用不止于此。

首先先描述一下具体的缩合方法：

- 一度点就直接删，二度点的边权就直接相加。
- 叠合重边则需要注意：
  - 如果重边的边权不同则将边权设置为不可到达，比如 $-1$（因为路径上显然不能包含这两个重边）。
  - 否则就还是原权值。
- 同时还有特殊的一点，就是 $1,n$ 即使度数 $\leq 2$ 也不作为缩合对象。

自行想象一下 no 的情况，大概就是所有 $1\to n$ 的简单路径们都缩到了 $(1,n)$ 这唯一一条边上，且边权不为 $-1$。

于是大胆断言答案为 no 当且仅当：缩合后 $s$ 的唯一出边是 $(s,t,w)$，且 $w\neq -1$。

当然这个猜测随便 hack，比如 Froggy 在 [LOJ 讨论](https://loj.ac/d/3763) 里提到的 hack 长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/k4v480kb.png)

虽然这个 hack 看上去有些取巧，但是至少是个 hack，而且变相的更加使我们相信这个不靠谱的猜想有一定正确性。

再看一眼部分分，发现有：对于任意三座不同的城市 a, b, c，均存在一条从城市 $a$ 到城市 $c$ 且不经过城市 $b$ 的路径 这个 sub。

翻译成人话就是整个图形成一个点双，同时不难发现上述 hack 的思路就是存在不同时包含 $1$ 和 $n$ 的点双。

那么难道说如果整张图是一个点双上述猜想就正确吗，实际上是这样的，证明如下：

**此处证明参考官方题解并结合自己的一点思考，可以看作是本题最核心部分之一**。

首先整理一下已知条件：整个图是点双联通的且所有点的度数 $\geq 3$。同时有点数 $n\geq 4$，否则无法满足度数均  $\geq 3$ 的限制。

考虑将所有边定向，根据从 $1$ 到它们的最短路，与最短路扩展方向同向定向。

如果此时就有 $(u,v,w)$ 使得 $\text{dis}(1,u)+w+\text{dis}(v,n)\neq \text{dis}(1,n)$ 的话那肯定是没救了。

否则定向后，称入度 $>$ 出度的点为红色点，否则称为蓝色点。

然后考虑 $1\to n$ 的经过节点个数最多的简单路径，$1\to a_1\to a_2\to \cdots\to a_p\to n$。

首先得到 $a_1$ 入度一定是 $1$，$a_p$ 的出度一定是 $1$，否则一定能找到经过点数更多的路径。

同时由于任意点度数 $\geq 3$，所以 $a_1$ 一定是蓝色的，$a_p$ 一定是红色的，换言之，路径一定经历了蓝红替换的过程。

考虑找到这样一条边，使得 $a_i=u,a_{i+1}=v$，且 $u$ 为蓝色，$v$ 为红色。

根据定义，一定存在 $u\to x(x\neq v)$ 以及 $y\to v(y\neq u)$，此时考虑路径 $1\to y\to v\to u\to x\to n$。

除了 $v\to u$ 之外，所有边任然需要根据定向移动。

如果它不是简单路径，不难发现只有可能是 $x\to n$ 与 $1\to y\to v$ 这段路径上有重合，不妨设第一个重合点为 $x'$。

那么将原路径替换为 $1\to u\to x\to z\to y\to v\to n$ 是经过更多点的选择，不符合定义。

所以这条路径一定是简单的，且 $>$ 最短路径的。证毕。

------------

如此，所有非正解的部分分都有了解决方法。

当然更进一步也是容易的，因为如果从 $1$ 出发进入一个以 $1$ 为割点且不包含 $n$ 的点双肯定是没有简单路径能到 $n$ 的。

所以直接加一条 $(1,n,\text{dis}(1,n))$ 即等于它们之间最短路径的边，然后只考虑同时包含 $1,n$ 的这个点双即可。

复杂度 $O(m\log m)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
#define rep(i, a, b) for(int i = (a); i <= (b); i ++)
#define per(i, a, b) for(int i = (a); i >= (b); i --)
#define Ede(i, u) for(int i = head[u]; i; i = e[i].nxt)
using namespace std;

#define eb emplace_back
typedef pair<int, ll> pii;
#define mp make_pair
#define fi first
#define se second

inline int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? - 1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

const int N = 1e5 + 10;
const ll inf = 1e16;
int n, m;

unordered_map<int, ll> g[N];

void add(int u, int v, ll w) {
	if(g[u].find(v) != g[u].end()) {
		if(g[u][v] != w) g[u][v] = g[v][u] = -1;
	}
	else g[u][v] = g[v][u] = w;
}


ll dis[N]; bool vis[N];
vector<pii> h[N];

ll getdis() {
	priority_queue<pair<ll, int> > q;
	rep(i, 1, n) dis[i] = inf;
	dis[1] = 0, q.push(mp(0, 1));
	while(! q.empty()) {
		int u = q.top().se; q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto e : h[u]) {
			int v = e.fi; ll w = e.se;
			if(dis[v] > dis[u] + w)
				dis[v] = dis[u] + w, q.push(mp(- dis[v], v));
		}
	}
	return dis[n];
}

int dfn[N], low[N], stk[N], top, tim, cnt;
vector<int> scc[N];

void dfs(int u) {
	dfn[u] = low[u] = ++ tim;
	stk[++ top] = u;
	for(auto e : h[u]) {
		int v = e.fi;
		if(! dfn[v]) {
			dfs(v), low[u] = min(low[u], low[v]);
			if(low[v] == dfn[u]) {
				int o = 0; cnt ++;
				do {o = stk[top --], scc[cnt].eb(o);} while(o != v);
				scc[cnt].eb(u);
			}
		}
		else low[u] = min(low[u], dfn[v]);
	}
}

bool valid[N];

void build() {
	n = read(), m = read();
	rep(i, 1, m) {
		int u = read(), v = read(), w = read();
		h[u].eb(mp(v, w));
		h[v].eb(mp(u, w));
	}
	ll cur = getdis();
	h[1].eb(mp(n, cur));
	h[n].eb(mp(1, cur));
	dfs(1);
	rep(i, 1, n) vis[i] = false;
	int pos = 0;
	rep(i, 1, cnt) {
		for(int o : scc[i]) vis[o] = true;
		if(vis[1] && vis[n]) {pos = i; break;}
		for(int o : scc[i]) vis[o] = false;
	}
	assert(pos);
	for(int o : scc[pos]) valid[o] = true;
	rep(u, 1, n) if(valid[u])
	for(auto e : h[u]) if(valid[e.fi]) add(u, e.fi, e.se);
}

queue<int> q;
void push(int u) {if(u != 1 && u != n && (int) g[u].size() <= 2) q.push(u);}

int main() {
	build();
	rep(i, 1, n) push(i);
	while(! q.empty()) {
		int u = q.front(); q.pop();
		if(g[u].empty()) continue;
		for(auto o : g[u]) g[o.fi].erase(u);
		if((int) g[u].size() == 2) {
			auto cur = g[u].begin();
			int x = cur -> fi; ll a = cur -> se; cur ++;
			int y = cur -> fi; ll b = cur -> se;
			ll w = (a == -1 || b == -1) ? -1 : a + b;
			add(x, y, w);
		}
		for(auto o : g[u]) push(o.fi);
		g[u].clear();
	}
	if(g[1].find(n) != g[1].end() && g[1][n] != -1 && (int) g[1].size() == 1) puts("0"); else puts("1");
	return 0;
}
```



---

## 作者：Rainy7 (赞：7)

WC2023 Day4 题目选讲。

> 给定一个 $n$ 个点 $m$ 条边的带权无向图，问是否存在一条 $n$ 到 $1$ 的路径，满足路径长度大于 $1$ 到 $n$ 的最短路。
>
> 保证 $n,m \le 2 \times 10^5$。

考虑转化题意，给边定向。

先求出该图的最短路图。按照最短路的方向，在最短路图上的边为正方向。否则方向为反方向。

于是题意转化为：

> 给一个 $n$ 个点 $m$ 条边的 DAG，给定两点 $s,t$，保证 DAG 中 $s$ 没有入边，$t$ 没有出边。
>
> 现在去除边的定向变为无向图，询问是否存在一条 $s$ 到 $t$ 的简单路径（无重复点），使得路径上至少有一条边经过方向与原 DAG 定向不同。  

如果存在一个点 $u$，在没定向前的图中，不存在 $s \rightarrow u \rightarrow t$ 的路径（不重复经过同一条边）那么我们可以直接把这个点删掉。

可以发现，上述操作等价于，连边 $s \leftrightarrow t$，删去与 $s,t$ 不在一个点双的点。

然后类似上题，我们继续对度数分类讨论。如果一个点的入度或者出度为 $0$，那么我们直接走 $s \rightarrow u \rightarrow t$ 路径即可，因为经过点 $u$ 一定会经过一条边和原来的定向不同。

如果存在一个点入度和出度均为 $1$，可以直接删去这个点，把他的前后两个点连起来。

考虑重边。如果该重边的权值全部相等并且为最短路图上的边，直接合并所有边。否则，如果存在一个大于最短路图上的边权的边，就将该边反向。

这些操作后，如果只剩下 $s \rightarrow t$ 两个点一条边，则无解。否则一定有解，考虑如何证明。

此时除了 $s,t$ 还会剩下一些点，且度数 $\ge 3$。我们取出 $s \rightarrow t$ 的有向最长路，此时取路径上的一点 $u$，他除了连向最长路上的点外，一定还会连向外面一个点，假设为 $p$。然后再经过一些点连回最长路。如果连回最长路的过程上，存在一个不顺向的边，那我们选这个路径，和剩余最长路的部分路径，就是满足他条件的答案。

如果不存在，假设他连回最长路的点为 $v$，他一定满足 $u \rightarrow p \rightarrow v$ 的路径大于 $u \rightarrow v$ 的路径长。此时 $p$ 还会连向另一跳路径，然后接在了最长路上的 $q$ 点。如果 $q$ 不在 $u \rightarrow v$ 中间，那么我们有答案形如 $u \rightarrow v \leftarrow p \rightarrow q$。

如果在中间，就接着往下考虑，由于需要满足 $u \rightarrow v \rightarrow p$ 为最长路的性质，在最后 $p,q$ 在最长路上距离为 $2$ 的时候一定满足条件。证毕。

---

## 作者：DaiRuiChen007 (赞：7)

# P8426 题解

**题目大意**

> 给一张 $n$ 个点 $m$ 条边的带权无向连通图，问是否存在一条 $1\to n$ 的简单路径长度与最短路长度不同。
>
> 数据范围：$n\le 10^5,m\le 2\times 10^5$。

**思路分析**

首先我们考虑简单一点的情况：不妨设整张图点双联通，感觉上这张图不能太复杂，否则肯定会找到解。

手模样例可以发现：假如这张图同胚于 $K_4$，即有四个点之间能找到六条边不交的路径将它们两两连接，那么这个图一定无解：

> 不妨设这四个点是 $a,b,c,d$，假设这张图依然无解，简单推理一下：
>
> - 由于 $w(a\to b\to c)=w(a\to d\to b\to c)$，因此 $w(a,d)+w(d,b)=w(a,b)$。
> - 由于 $w(a\to d\to c)=w(a\to b\to d\to c)$，因此 $w(a,d)=w(a,b)+w(b,d)$。
>
> 因此 $w(b,d)=w(a,b)-w(a,d)=w(a,d)-w(a,b)=0$，又因权值都是正整数，因此假设不成立，这样的图必然有解。

因此我们得到：同胚于 $K_4$ 的点双联通图必定有解。

注意到不同胚于 $K_4$ 的点就是广义串并联图，考虑广义串并联图方法简化这张图：

- 删一度点：直接删除，不影响答案。
- 叠合重边：如果两条边权一样无事发生，否则产生一条边权为 $-\infty$ 的边。
- 缩二度点：产生一条权值为两边权之和的新边。

注意增广的过程中要保证 $1,n$ 两个点不能入队，最后假如的图里只剩一条 $1\to n$ 的边，且边权不为 $-\infty$ 则合法，否则显然一定不合法。

然后考虑如何把图变成点双联通的，首先如果 $1,n$ 点双联通，直接缩点，取出 $1,n$ 所在的点双联通分量作为原图即可。

若 $1,n$ 不点双联通，那么连接一条 $1,n$ 之间的边，权值为他们之间的最短路长度，显然不影响答案判定，且能使得 $1,n$ 点双联通。

时间复杂度 $\mathcal O(m\log m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5;
int n,m;
struct Edge { int v; ll w; };
vector <Edge> G[MAXN];
ll dis[MAXN];
bool vis[MAXN];
inline ll Dijk() {
	memset(dis,0x3f,sizeof(dis));
	priority_queue <array<ll,2>,vector<array<ll,2>>,greater<array<ll,2>>> Q;
	Q.push({dis[1]=0,1});
	while(Q.size()) {
		int u=Q.top()[1]; Q.pop();
		if(vis[u]) continue; vis[u]=true;
		for(auto e:G[u]) if(dis[e.v]>dis[u]+e.w) Q.push({dis[e.v]=dis[u]+e.w,e.v});
	}
	return dis[n];
}
vector <int> vdcc;
int dfn[MAXN],low[MAXN],dcnt,stk[MAXN],tp;
inline void tarjan(int u) {
	dfn[u]=low[u]=++dcnt,stk[++tp]=u;
	for(auto e:G[u]) {
		int v=e.v;
		if(!dfn[v]) {
			tarjan(v),low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]) {
				int k; vector <int> cur{u};
				do k=stk[tp--],cur.push_back(k); while(k!=v);
				sort(cur.begin(),cur.end());
				if(cur.front()==1&&cur.back()==n) vdcc=cur;
			}
		} else low[u]=min(low[u],dfn[v]);
	}
}
bool inq[MAXN];
map <int,ll> g[MAXN];
inline void link(int u,int v,ll w) {
	if(g[u].count(v)) {
		if(w!=g[u][v]) g[u][v]=g[v][u]=-1;
	} else g[u][v]=g[v][u]=w;
}
queue <int> Q;
inline void upd(int x) { if(x!=1&&x!=n&&g[x].size()<=2) Q.push(x); }
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;++i) {
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	ll dist=Dijk();
	G[1].push_back({n,dist});
	G[n].push_back({1,dist});
	tarjan(1);
	for(int i:vdcc) inq[i]=true;
	for(int u:vdcc) for(auto e:G[u]) if(inq[e.v]) link(u,e.v,e.w);
	for(int i:vdcc) upd(i);
	while(Q.size()) {
		int u=Q.front(); Q.pop();
		for(auto e:g[u]) g[e.first].erase(u);
		if(g[u].size()==2) {
			int x=g[u].begin()->first,y=g[u].rbegin()->first;
			ll c=g[u].begin()->second,d=g[u].rbegin()->second;
			link(x,y,(~c&&~d)?c+d:-1);
		}
		for(auto e:g[u]) upd(e.first);
		g[u].clear();
	}
	if(g[1].count(n)&&~g[1][n]&&g[1].size()==1) puts("0");
	else puts("1");
	return 0;
}
```

---

## 作者：TianyiLemon (赞：5)

*一句话题意：正权无向连通图，判断是否存在两条从 $1$ 到 $n$ 长度不同的路径。*$n\le 100000,m\le 200000$

给个短一点的题解。

先考虑所有点在一个点双内的情况。根据点双的性质，对任意 $1\le x\le n$，均存在从 $1$ 到 $n$ 且经过 $x$ 的简单路径。

如果存在一个点 $1<x<n$，且 $x$ 度数为 $2$，设与它相邻的两个点为 $u,v$，可以把边 $(u,x),(x,v)$ 缩成边 $(u,v)$，不会影响答案。如果产生了重边，且它们权值不相同，那么答案一定为 $1$。否则，可以删掉其中一条边。

如果缩完之后图中存在 $1,n$ 之外的点，那么一定存在两个点度数不小于 $3$。这时候答案一定为 $1$。

> 证明：考虑反证法。假设答案为 $0$，那么有 $a+d=b+c+d\Rightarrow a=b+c$，同理有 $a+c=b$，解得 $c=0$，与边权为正矛盾。

>![](https://cdn.luogu.com.cn/upload/image_hosting/ehw5zs8b.png)

否则，缩完之后只剩边 $(1,n,dis(1,n))$，答案为 $0$。

接下来考虑 $1,n$ 不在一个点双内的情况。这时，我们需要知道哪些点 $x$ 满足：存在从 $1$ 到 $n$ 且经过 $x$ 的简单路径。只需考虑这些点即可。

结论：在图上添加一条边 $(1,n,dis(1,n))$，那么 $x$ 合法的充要条件是：在新图上，$x$ 和 $1,n$ 属于一个点双。

> 证明：先证必要性。如果原图上存在从 $1$ 到 $n$ 且经过 $x$ 的简单路径，那么在新图上，这条路径和 $(1,n,dis(1,n))$ 构成一个简单环。

> 再证充分性。如果 $u$ 和 $1,n$ 不属于一个点双，那么存在一个割点 $y$，从 $1$ 和 $n$ 出发到 $x$ 的所有路径都要经过 $y$。显然不合法。

套用之前的做法即可。

时间复杂度 $O(m\log m)$。

[提交记录](https://loj.ac/s/1699358)

---

## 作者：yukimianyan (赞：2)

虽然不知道为什么，但是首先发现这个图当起点是 $1$ 终点是 $4$ 的时候是一定无解的，因为 $w(2, 3)$ 被迫为 $0$。

![1-2,1-3,2-3,2-4,3-4](https://cdn.luogu.com.cn/upload/image_hosting/mwxkvat9.png)

放宽一下，也就是说图中有 $K_4$ 就无解。也不一定，如果 $1\to n$ 任何路径都不经过这个结构也是有解的。假如能把 $1\to n$ 到达不了的部分去掉，那么剩下就是广义串并联图了，直接广义串并联图方法启动。但是不能把 $1, n$ 两个点删掉。结束以后可能还会有这种结构会被广义串并联图留着，因为 $1, n$ 不能删，那么现在一定是 $1, n$ 两个点有至少一个点的度数 $\leq 2$ 阻拦了。轻轻地删一下度数 $\leq 1$ 的点，然后就会分成两条链。这两条链之间如果有边连接，立即不合法；两条链之间可以分裂，可是一旦分裂出来的两条链之间有边连接就也不合法（除非是接回去到分裂点所在的链中），你再仔细思考一下，是不是说缩完二度点，这些链变成边之后，实际上会成为一个巨大的环，把 $1\to n$ 这条边连上后环上的所有弦是不相交的。而这种形状会被广义串并联图方法缩成仅剩一条边，这就矛盾了，一开始根本不会分成两条链。也就是说不存在上图那种结构的时候，广义串并联图方法会将图缩成仅剩一条边。

我们整理一下，也就是说我们把 $1\to n$ 到达不了的部分去掉，连上 $1\to n$ 这条边，然后跑广义串并联图方法，由于上面那种结构会被升级为 $K_4$，因此如果跑完以后剩下的不只 $1\to n$ 单独一条边，那么就肯定是因为出现了上面那种结构。

最后再考虑一下 $1\to n$ 到达不了的部分怎么去掉，其实会比较自然，连上 $1\to n$ 这条边，然后和 $1, n$ 不在一个点双中的点直接忽略掉就肯定是对的了。然后跑广义串并联图方法，当且仅当剩下的只有 $1\to n$ 单独一条边而且叠合重边时没有出现冲突时，答案为 $0$。

以上证明不是很严谨甚至不是很对，看一下就好了，真的要证明还得看官方题解。总之就是以复杂度 $O(m\log m)$ 解决了本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
using LL = long long;
constexpr int N = 1e5 + 10;
int n, m;
LL dis[N];
vector<pair<int, LL>> g[N];
void dijkstra(int s) {/*{{{*/
  static bool vis[N];
  using pii = pair<LL, int>;
  priority_queue<pii, vector<pii>, greater<pii>> q;
  memset(dis, 0x3f, sizeof dis);
  memset(vis, false, sizeof vis);
  q.emplace(dis[s] = 0, s);
  while (!q.empty()) {
    int u = q.top().second; q.pop();
    if (exchange(vis[u], true)) continue;
    for (auto [v, w] : g[u]) if (dis[v] > dis[u] + w) q.emplace(dis[v] = dis[u] + w, v);
  }
}/*}}}*/
vector<int> dcc;
int dfn[N], low[N], stk[N], top, cnt;
void tarjan(int u) {
  dfn[u] = low[u] = ++cnt, stk[++top] = u;
  for (auto [v, w] : g[u]) {
    if (dfn[v]) low[u] = min(low[u], dfn[v]);
    else {
      tarjan(v), low[u] = min(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        vector<int> vec{u};
        do vec.push_back(stk[top]); while (stk[top--] != v);
        sort(vec.begin(), vec.end());
        if (vec[0] == 1 && vec.back() == n) dcc = vec;
      } 
    }
  }
}
map<int, LL> mp[N];
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  cin >> n >> m;
  for (int i = 1, u, v, w; i <= m; i++) {
    cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  dijkstra(1);
  g[1].emplace_back(n, dis[n]);
  g[n].emplace_back(1, dis[n]);
  for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
  assert(!dcc.empty());
  for (int u : dcc) {
    for (auto [v, w] : g[u]) if (binary_search(dcc.begin(), dcc.end(), v)) {
      if (mp[u].count(v) && mp[u][v] != w) mp[u][v] = -1; else mp[u][v] = w;
    }
  }
  for (int u : dcc) for (auto [v, w] : mp[u]) if (u < v) debug("-> %d %d %lld\n", u, v, w);
  static int deg[N];
  queue<int> q;
  for (int i : dcc) if ((deg[i] = (int)mp[i].size()) <= 2) q.push(i);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (deg[u] == 0 || u == 1 || u == n) continue;
    debug("u = %d\n", u);
    if (deg[u] == 1) {
      auto [x, w] = *mp[u].begin();
      mp[u].clear(), deg[u] = 0, mp[x].erase(u), deg[x] -= 1;
      if (deg[x] <= 2) q.push(x);
      assert(false);
    } else {
      auto [x, w1] = *mp[u].begin();
      auto [y, w2] = *mp[u].rbegin();
      mp[u].clear(), deg[u] = 0, mp[x].erase(u), mp[y].erase(u), deg[x] -= 1, deg[y] -= 1;
      auto w = w1 == -1 || w2 == -1 ? -1ll : w1 + w2;
      if (mp[x].count(y) && mp[x][y] != w) mp[x][y] = mp[y][x] = -1; else mp[x][y] = mp[y][x] = w;
      deg[x] = (int)mp[x].size(), deg[y] = (int)mp[y].size();
      if (deg[x] <= 2) q.push(x);
      if (deg[y] <= 2) q.push(y);
    }
  }
  for (int u : dcc) for (auto [v, w] : mp[u]) if (u < v) debug("-> %d %d %lld\n", u, v, w);
  for (int u : dcc) assert(deg[u] == (int)mp[u].size());
  bool flag = mp[1].size() == 1 && mp[n].size() == 1 && mp[1].count(n) && mp[1][n] != -1;
  for (int i : dcc) if (i != 1 && i != n && !mp[i].empty()) flag = false;
  cout << 1 - flag << endl;
  return 0;
}
```

---

## 作者：Lucyna_Kushinada (赞：1)

# P8426 [JOI Open 2022] 放学路 / School Road

引流：[已完成今日广义串并联图大学习。](https://www.cnblogs.com/Lucyna-Kushinada/p/19054179)

## 题意

给定一张 $n$ 个点 $m$ 条边的无向连通图，有边权。

请你判断是否存在一条 $1\to n$ 的**简单**路径，满足长度大于 $1\to n$ 的最短路长度。

$2\le n\le 10^5,m\le 2\times 10^5$。

## 题解

知识点：广义串并联图，点双连通分量，最短路。

好题啊。

可能会有的一个错误想法，是用单源最短路算法，分别求出最长路和最短路，然后比较一下，但这个图是不太能用单源最短路算法求最长路的，因为将边权取反后大概率会出现负环。

为了保证思维的流畅性，这里对每个子任务分别讲解。

### 子任务 1

$m\le 40$，直接暴力搜索即可，复杂度比较玄学，但是能过。

### 子任务 2

$n\le 18$，考虑状压 dp，求出**简单**路径中的最长路长度，最终和最短路比较一下。

前两个子任务对正解没什么提示性，毕竟不需要研究题目的任何性质。

### 子任务 3

令 $k=m-n$，则 $k\le 13$。

考虑转化题意，什么时候不存在题目所述的路径，就是 $1\to n$ 的所有路径的长度均相同的时候。

如果你学过广义串并联图方法，那么你应该会对这个条件非常敏感。

对这个图使用广义串并联图方法进行压缩后，会使得 $m\le 3k,n\le 2k$，而这个数据范围支持暴力搜索。

对于这题来讲，压缩的过程中，每条边 $(u,v)$ 维护的信息就是 $u\to v$ 路径长度 $w$，具体步骤如下：

- 删 $1$ 度点，设当前点为 $u$，只需要直接删除就行了，因为点不需要维护什么消息，它也无法贡献信息到其他边。

- 缩 $2$ 度点：设当前点为 $u$，记与其相邻的两个点为 $x,y$，那么直接删除旧边 $(u,x,w_x),(u,y,w_y)$，添加新边 $(x,y,w_x+w_y)$ 即可，这是不难理解的。

- 叠合重边：记连接两个点 $u,v$ 的两条重边分别为 $(u_1,v_1,w_1)$ 和 $(u_2,v_2,w_2)$，叠合后得到新边 $(u,v,w)$，那么如果 $w_1=w_2$，则 $w=w_1$，反之 $w=-1$，即标记为不合法，因为此时肯定存在两条 $u\to v$ 且长度不同的路径了。

特别地，上述步骤中的除了叠合重边 $u$ 和 $v$ 均不会是 $1$ 或者 $n$，也就是说 $1$ 和 $n$ 不参与上述前两种压缩方式。因为 $x$ 和 $y$ 可以为 $1$ 或 $n$，而叠合重边的操作，只会接在缩 $2$ 度点操作生成边 $(x,y,w_x+w_y)$ 的之后。

然后在压缩后的图上暴力搜索，如果存在一条经过过边权为 $-1$ 的边的 $1\to n$ 路径，那么说明肯定存在题目所说的路径。

### 子任务 4

这个条件看着比较抽象，其实就是想表达这张图是一张点双连通图，但似乎目前不太能知道这个条件有什么用。

考虑 子任务 3 解法的复杂度瓶颈，在于压缩完之后的那个搜索，能不能通过到一种方式，直接判定压缩后的图，是否存在题目所说的路径？

稍微手玩几组数据，可以初步猜测一个结论：

存在题目所说的路径，当且仅当压缩后的图只存在 $1$ 和 $n$ 两个点，且只有一条边 $(1,n,w)$，同时还满足 $w\neq -1$。

看着感觉确实很对啊，但是有以下一组 hack 数据：

![HACK](https://cdn.luogu.com.cn/upload/image_hosting/qwgugpua.png)

考虑为什么会错，因为图中的两个 $K_4$ 子图根本无法压缩，造成了误判的情况。

不过可以注意到，在这张图中，$1$ 和 $n$ 并不在同一个点双连通分量中。

正好这个子任务是点双连通图，不妨接着猜测，这种情况下，结论成立。

实际上，这个猜测是正确的，下面给出证明：

> 对于缩合后的图，若不是只有点 $1$ 和 $n$，且只有 $1$ 到 $n$ 一条边，那么这个图就一定存在同胚于 $K_4$ 的子图。\
此时若整个图是一个点双，则一定存在一个同胚于 $K_4$ 的子图且包含 $1$ 与 $n$，如果没有说明他们不在一个点双里，这与事实矛盾。\
在这种图中，因为边权 $\ge 1$，是无法保证每一条 $1$ 到 $n$ 路径长度均相同的（可以画一个 $K_4$ 自己理解一下）。证毕。

### 正解

先用 `dijkstra` 跑出 $1\to n$ 的最短路长度 $d$，加入新边 $(1,n,d)$，显然并不影响答案，只是会使得 $1$ 和 $n$ 在同一点双连通分量中，方便处理。

使用 `tarjan` 处理出同时包含 $1$ 和 $n$ 的点双连通分量点集 $S$。

建立一个新图，原图中的边 $(u,v,w)$ 出现在新图中当且仅当 $u\in S,v\in S$，显然这个新图是一个点双连通图。

为什么只需要考虑同时包含 $1$ 和 $n$ 的这个点双连通分量，因为其他的点与边加入与否都不可能会贡献一条新的从 $1$ 到 $n$ 的路径（否则就在这个点双里了），也不会降低连通度。

然后用广义串并联图方法压缩这个新图。

然后判断压缩后的图是否只存在 $1$ 和 $n$ 两个点，且只有一条边 $(1,n,w)$，同时还满足 $w\neq -1$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define bg(x) (x).begin()
#define ed(x) (x).end()

#define N 202508
#define int long long

int n,m;

struct edge{
    int t,w;
};

vector<edge>g[N];
bitset<N>f;

namespace ssp{
    int dis[N];

    inline void dijkstra(int s){
        rep(i,1,n){
            f[i]=0;
            dis[i]=1e18;
        }

        dis[s]=0;

        priority_queue<pr,vector<pr>,greater<pr>>q;

        q.push({dis[s],s});

        while(!q.empty()){
            int u=q.top().se;
            q.pop();

            if(f[u]){
                continue;
            }
            f[u]=1;

            for(edge x:g[u]){
                if(dis[u]+x.w<dis[x.t]){
                    dis[x.t]=dis[u]+x.w;
                    q.push({dis[x.t],x.t});
                }
            }
        }
    }

    inline int run(){
        dijkstra(1);

        return dis[n];
    }
}

map<int,int>e[N];

inline void add(int u,int v,int w){
    if(e[u].count(v)){
        int &re=e[u][v];

        if(re==-1){
            return;
        }

        re=(re==w)?w:-1;

        e[v][u]=re;

        return;
    }

    e[u][v]=e[v][u]=w;
}

int st[N],tp,dfn[N],low[N],num,id;
vector<int>scc[N];

inline void dfs(int k,int fa){
    dfn[k]=low[k]=++num;
    st[++tp]=k;

    for(edge x:g[k]){
        if(x.t==fa){
            continue;
        }

        if(!dfn[x.t]){
            dfs(x.t,k);
            
            low[k]=min(low[k],low[x.t]);

            if(low[x.t]>=dfn[k]){
                id++;

                do{
                    scc[id].pb(st[tp]);
                    tp--;
                }while(st[tp+1]!=x.t&&tp);

                scc[id].pb(k);
            }
        }
        else{
            low[k]=min(low[k],dfn[x.t]);
        }
    }
}

inline void init(){
    int dis=ssp::run();

    g[1].pb({n,dis});
    g[n].pb({1,dis});

    dfs(1,0);

    f.reset();

    int pos=0;

    rep(i,1,id){
        for(int x:scc[i]){
            f[x]=1;
        }

        if(f[1]&&f[n]){
            pos=i;
            break;
        }

        for(int x:scc[i]){
            f[x]=0;
        }
    }

    for(int x:scc[pos]){
        f[x]=1;
    }

    for(int x:scc[pos]){
        for(edge y:g[x]){
            if(!f[y.t]){
                continue;
            }

            add(x,y.t,y.w);
        }
    }
}

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>m;

    rep(i,1,m){
        int u,v,w;
        cin>>u>>v>>w;

        g[u].pb({v,w});
        g[v].pb({u,w});
    }

    init();

    queue<int>q;

    rep(i,1,n){
        if(sz(e[i])<3){
            q.push(i);
        }
    }

    while(!q.empty()){
        int u=q.front();
        q.pop();

        if(u==1||u==n){
            continue;
        }
        
        if(sz(e[u])==2){
            pr tx=*e[u].begin(),ty=*next(e[u].begin());
            
            add(tx.fi,ty.fi,tx.se+ty.se);
        }

        for(pr v:e[u]){
            int x=v.fi;

            e[x].erase(u);

            if(sz(e[x])<3){
                q.push(x);
            }
        }

        e[u].clear();
    }

    // cout<<sz(e[1])<<' '<<e[1].count(n)<<' '<<e[1][n]<<"\n";

    if(sz(e[1])==1&&e[1].count(n)&&e[1][n]!=-1){
        cout<<0;
    }
    else{
        cout<<1;
    }

    return 0;
}
```

---

## 作者：Grisses (赞：1)

[题面](https://www.luogu.com.cn/problem/P8426)

---

好题啊。广义串并联图好玩。

---

观察到有一个点满足 $m\le n+13$，这启示我们往广义串并联图考虑。

首先求出 1 到 $n$ 的最短路 $L$，然后考虑广义串并联图缩点，每次删 1 都点，缩 2 度点，复合重边时维护一下新边的最长距离，具体来说：

- 删 1 度点：因为不能走回头路，所以个点一定没用，直接丢掉。
- 缩 2 度点：新边的权值为原来两边之和。
- 复合重边：新边权值为原来两边的 $\max$。

注意特殊处理 1 号点和 $n$ 号点，不能把它们删了。

最后我们发现：要么是剩下一条连接 1 和 $n$ 的边，要么是剩下一个每个点度数不小于 3 的图。

前一种情况是平凡的，我们考虑下后一种情况，不难发现，后种情况的图如果把 1 和 $n$ 提出来大概长成这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/zdfosw3i.png)

即若干条从 1 到 $n$ 的路径，以及这些路径上的每个点都至少连出一条横插边，简单分析发现，这样一定是无法做到所有路径长度相同的，所以这种情况一定是 `Yes`。

---

## 作者：_Cheems (赞：0)

题意：给一张带权无向图，判断所有 $1\to n$ 的简单路径权值和是否相同。$n\le 10^5,m\le 2\times 10^5$。

考虑怎么做点双的特殊性质。因为是点双，所以可以把图看成 $1$ 为源点、$n$ 为汇点，然后中间夹着若干路径的图。你又看到了 $m-n\le 13$ 的部分分，尝试用广义串并联图方法：

* 删一度点：只要不是 $1,n$ 就删了。
* 缩二度点：显然缩成一条边没有影响。
* 叠重边：边权相等就保留一条边；反之，因为点双内必然存在经过这条边的路径，所以就输出不同。

对于最终的图，假如只有 $1,n$ 就输出相同；反之，设权值都相同，由于该图满足 $1\to n$ 的每条路径上的点都向外连一条边，也就是存在同胚于“杏仁图”的子图（$1,n$ 为两端），那么简单代数推导发现横叉边权值为 $0$，非法。可结合下图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/a6ibt2ar.png)


对于非点双的情况，发现对于圆方树 $1\to n$ 路径以外的点，一走进去就不是简单路径了，所以它们都没用。剩下的点虽然不是点双，但上面用到的性质都满足了，所以套用做法即可。

$O(m\log m)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;
int n, m, u[N], v[N], w[N];
int dfn[N], low[N], df, vccnt, col[N], stk[N], st;
bool vis[N];
vector<int> to[N];

inline void form(int x, int u){
    int tp; bool fl = false, fl2 = false; vector<int> vc;
    do{
        tp = stk[st--];
        vc.push_back(tp);
        fl |= (tp == 1), fl2 |= (tp == n);
    }while(tp ^ x);
    vc.push_back(u);
    fl |= (u == 1), fl2 |= (u == n); 
    if(fl && fl2) for(auto i : vc) vis[i] = true; 
}
inline void dfs(int u){
    dfn[u] = low[u] = ++df, stk[++st] = u;
    for(auto v : to[u])
        if(!dfn[v]){
            dfs(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) form(v, u);
        }
        else low[u] = min(low[u], dfn[v]);
}

#define id(u, v) (u * n + v)
int tot = 1, head[N], du[N], cnt;
bool used[N << 2];
struct edge{int u, v, nxt;} e[N << 2];
unordered_map<int, int> ew; 

inline void add(int u, int v) {e[++tot] = {u, v, head[u]}, head[u] = tot;}
inline int get(int u){
    while(used[head[u]]) head[u] = e[head[u]].nxt;
    return head[u];
}
inline void del(int id){
    used[id] = used[id ^ 1] = true;
    ew.erase(id(e[id].u, e[id].v)), ew.erase(id(e[id].v, e[id].u));
}
signed main(){
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) scanf("%lld%lld%lld", &u[i], &v[i], &w[i]), to[u[i]].push_back(v[i]), to[v[i]].push_back(u[i]);
    to[1].push_back(n), to[n].push_back(1);
    dfs(1);
    for(int i = 1; i <= m; ++i)
        if(vis[u[i]] && vis[v[i]]){
            int bef = ew[id(u[i], v[i])];
            if(bef){
                if(w[i] ^ bef){
                    puts("1");
                    return 0;
                }
            }
            else{
                add(u[i], v[i]), add(v[i], u[i]);
                ++du[u[i]], ++du[v[i]];
                ew[id(u[i], v[i])] = ew[id(v[i], u[i])] = w[i];
            }
        }
    queue<int> q;
    for(int i = 1; i <= n; ++i){
        cnt += vis[i];
        if(i > 1 && i < n && vis[i] && du[i] == 2) q.push(i);
    }
    while(!q.empty()){
        int u = q.front(), w = 0; --cnt, q.pop();
        int ls = get(u), x = e[ls].v; w += ew[id(x, u)]; del(ls);
        int rs = get(u), y = e[rs].v; w += ew[id(u, y)]; del(rs);
        int bef = ew[id(x, y)];
        if(bef){
            if(w ^ bef){
                puts("1");
                return 0;
            }
            if(x > 1 && x < n && --du[x] == 2) q.push(x);
            if(y > 1 && y < n && --du[y] == 2) q.push(y);
            
        }    
        else{
            add(x, y), add(y, x);
            ew[id(x, y)] = ew[id(y, x)] = w;
        }    
    }
    if(cnt > 2) puts("1");
    else puts("0");
    return 0;
}
```

---

