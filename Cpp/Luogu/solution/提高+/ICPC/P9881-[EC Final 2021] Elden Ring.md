# [EC Final 2021] Elden Ring

## 题目描述

教授 Pang 正沉迷于一款名为《Elden Ring》的游戏，其中的世界是一个包含 $n$ 个顶点（从 $1$ 到 $n$ 编号）和 $m$ 条无向边的连通图。玩家从顶点 $1$ 开始，穿越世界去击败位于顶点 $n$ 的神。

然而，这并不简单。对于除顶点 $1$ 以外的任何顶点 $i$，都有一个等级为 $l_i$ 的 Boss，玩家以等级 $l_1$ 开始游戏。每天，玩家可以从顶点 $1$ 前往任意顶点 $i$ 并挑战那里的 Boss。如果玩家当前的等级高于 Boss，Boss 将被消灭（失效），玩家的等级将增加 $A$。注意，经过一个有活跃 Boss 的顶点是被禁止的。（换句话说，教授 Pang 可以从顶点 $1$ 前往顶点 $i$，如果在图中存在一条从顶点 $1$ 到顶点 $i$ 的路径，使得该路径上的每个顶点（除了顶点 $i$）都没有活跃的 Boss。）同时，每天开始时，世界上所有剩余的 Boss 的等级都会增加 $B$。

要完成游戏的通关，你需要击败位于顶点 $n$ 的 Boss（Elden Beast）。给定世界的信息，教授 Pang 想知道他至少需要多少天才能做到这一点。

玩家每天只能挑战一个 Boss。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
5 4 5 8
1 2
1 3
1 4
4 5
15 1 1 1 1
5 4 10 5
1 2
1 3
1 4
4 5
10 4 4 4 19
```

### 输出

```
2
4
```

# 题解

## 作者：wangshi (赞：6)

模拟赛遇到这个题，写题解记录一下。

首先，因为每天一开始怪会先加 $B$ ,因此我们对于 $i \ge 2$ 把 $w_i$ 直接设置为 $w_i+B$ 。

然后，分两种情况讨论。

- $A \leq B$
  
  令 $t_i$ 为到达 $i$ 最晚时间。

  对于 $w_1 \leq w_i$ ,显然永远也到达不了 $i$ , $t_i$ 直接设为 $0$ 。

  
  对于 $w_1 > w_i$ ,有式子 $w_1+A(i-1) > w_i+B(i-1)$ ，移项得 $i < \frac{w_1-w_i}{B-A}$ ,因此 $t_i = \frac{w_1-w_i-1}{B-A}$ ，对于 $A=B$ 特殊判一下。
   
- $A > B$

  令 $t_i$ 为到达 $i$ 最早时间。

  对于 $w_1>w_i$ ，$t_i=1$ 。

  对于 $w_1 \leq w_i$ ,同样用上面的式子可以推出 $t_i = \frac{w_i-w_1}{B-A}+2$ 。

对两种情况分别跑最短路即可，可能有一些细节吧。

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define wang_shi return 0
using namespace std;
const int N=1e6+10;
typedef pair<int,int> PII;
int n,m,A,B,dis[N],vis[N],w[N],t[N];
vector<int> g[N];
void Solve1()
{
	for(int i=2;i<=n;++i)
	{
		if(A==B) t[i]=(w[1]>w[i]?1e18:0);
		else t[i]=(w[1]>w[i]?(w[1]-w[i]-1)/(B-A)+1:0);
		dis[i]=-1;
	}	
	queue<int> q; q.push(1);
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		for(int v:g[u])
		{
			if(dis[v]==-1&&dis[u]+1<=t[v])
			{
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	cout<<dis[n]<<'\n'; 
}
void Solve2()
{
	for(int i=2;i<=n;++i)
	{
		t[i]=(w[1]>w[i]?1:(w[i]-w[1])/(A-B)+2);
		dis[i]=1e18;
	}
	priority_queue<PII,vector<PII>,greater<PII>> q;
	q.push({0,1}); int sum=0;
	while(!q.empty())
	{
		int u=q.top().se; q.pop();
		if(vis[u]) continue;
		if(sum<dis[u]){dis[u]=1e18;continue;}
		sum++;
		for(int v:g[u])
		{
			if(max(dis[u]+1,t[v])<dis[v])
			{
				dis[v]=max(dis[u]+1,t[v]);
				q.push({dis[v],v});
			}
		}
	}
	cout<<(dis[n]==1e18?-1:dis[n])<<'\n';
} 
void Solve()
{
	cin>>n>>m>>A>>B;
	for(int i=1;i<=m;++i) 
	{
		int u,v; cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
	{
		cin>>w[i];
		w[i]+=(i==1?0:B);
	}
	if(A<=B) Solve1();
	else Solve2();
	for(int i=1;i<=n;++i)
	{
		w[i]=t[i]=dis[i]=vis[i]=0;
		g[i].clear();
	}	
}
signed main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int t=1; cin>>t;
	while(t--) Solve();
	wang_shi;
}
```

---

## 作者：hellolin (赞：4)

下文下标统一从 $0$ 开始。

由于怪物是一天开始时升级，为了方便不妨令 $l_i=l_i+B\ (1\le i < n)$，这样可以转化为在一天结束时升级。同时令 $w=l_0$。

---

首先我们考虑 $A=B$ 的情况，容易发现此时怪物的等级与玩家的等级之差不变，于是把大于等于玩家等级的节点删掉，求最短路即可。

---

其次是 $A<B$ 的情况，此时怪物的等级增长较快，玩家等级增长慢。此时玩家的策略一定是尽早击杀每个怪物，所以我们设计一个上限 $\mathrm{limit}_i$，表示如果玩家每天都可以升级，第 $i$ 个怪物可以被击杀的时间区间 $[1, \mathrm{limit}_i]$。

- 如果 $w\le l_i$，那么玩家无论如何也不能击杀该怪物，即区间为空集，可以令 $\mathrm{limit}_i=0$。
- 如果 $w>l_i$，那么满足 $w+(t-1)\times A>l_i+(t-1)\times B$ 的最大的 $t$ 就是 $\mathrm{limit}_i$。整理得 $\mathrm{limit}_i=\lfloor\frac{w-l_i+1}{B-A}\rfloor+1$。

我们限制每个节点的距离小于等于 $\mathrm{limit}_i$，求最短路即可。

---

最后是 $A>B$ 的情况，此时怪物可被击杀的时间区间是一个后缀区间，设为 $[\mathrm{limit}_i,+\infty)$。

- 如果 $w\le l_i$，那么满足 $w+(t-1)\times A>l_i+(t-1)\times B$ 的最小的 $t$ 就是 $\mathrm{limit}_i$，整理得 $\mathrm{limit}_i=\lfloor\frac{l_i-w}{A-B}\rfloor+2$。
- 如果 $w>l_i$，那么这个怪物任意时刻都能被击杀。令 $\mathrm{limit}_i=1$。

我们限制每个节点的距离大于等于 $\mathrm{limit}_i$，此时出现了问题，如果击杀一个怪物时等级不够，需要击杀其他等级低的怪升级，如何表示？

我们想到如果等级不够，可以将该节点的 $\mathrm{dist}_i$ 暂时记为 $\mathrm{limit}_i$，同时使用优先队列进行 BFS，击杀其他可以早击杀的怪（因为 $\mathrm{dist}_i$ 就相当于我们击杀某个怪的最短时间，所以使用优先队列可以让我们先取出容易击杀的怪），最后回来检查该节点的假设是否合法，不合法重置为 $+\infty$ 即可。

总时间复杂度 $O(n\log n)$。

``` cpp
namespace hellolin {
static constexpr int INF = 1e9;
void solve() {
  int n, m, a, b;
  io.read(n, m, a, b);

  vector<vector<int>> g(n);
  for (int i = 0, u, v; i < m; ++i) {
    io.read(u, v);
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vector<int> l(n);
  for (int &i : l) {
    io.read(i);
    i += b;
  }
  int w = l[0] - b;

  if (a <= b) {
    // 这里将等于和小于两种情况合并，他们的代码相似，把 limit 置 0 相当于删除某个节点
    vector<int> limit(n), dist(n, INF);
    dist[0] = 0;
    for (int i = 1; i < n; ++i) {
      if (a < b) {
        limit[i] = l[i] >= w ? 0 : ((w - l[i] - 1) / (b - a) + 1);
      } else {
        limit[i] = l[i] >= w ? 0 : INF;
      }
    }

    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (const int &v : g[u]) {
        if (dist[u] + 1 <= limit[v] and chmin(dist[v], dist[u] + 1)) {
          q.push(v);
        }
      }
    }

    io.writeln(dist[n - 1] == INF ? -1 : dist[n - 1]);
  } else {
    vector<int> limit(n), dist(n, INF);
    dist[0] = 0;
    for (int i = 1; i < n; ++i) {
      limit[i] = w > l[i] ? 1 : ((l[i] - w) / (a - b) + 2);
    }

    using state = pair<int, int>;
    priority_queue<state, vector<state>, greater<state>> q;
    q.emplace(0, 0);

    int current = 0;
    while (!q.empty()) {
      auto [_, u] = q.top();
      q.pop();
      if (current < dist[u]) {
        // 记录总共打了多少怪，如果升级不够就重置这个节点
        dist[u] = INF;
        continue;
      }
      ++current;
      for (const int &v : g[u]) {
        if (chmin(dist[v], max(dist[u] + 1, limit[v]))) {
          // 这里取 min 时同时取 limit，就是假设可以打其他怪升级后返回打这个怪
          q.emplace(dist[v], v);
        }
      }
    }

    io.writeln(dist[n - 1] == INF ? -1 : dist[n - 1]);
  }
}
void main() {
  int t;
  for (io.read(t); t--;)
    solve();
}
} // namespace hellolin
```

---

## 作者：Crepuscule (赞：3)

#### 思路

分为两种情况：

1. $A \le B$，此时无法通过打其他 boss 刷等级，每个 boss 如果要击杀的话就要尽早击杀。因此我们用 $t_i$ 表示击杀 $i$ 的最晚时间，推式子得 $t_u = \frac {w_1 - w_i - 1}{B - A} + 1$，$A = B$ 的情况特判。然后一遍 BFS 算最短路，判断从 $u$ 转移，时间是否小于 $t_v$ 才可以转移。

2. $A > B$，需要考虑打一些其他 boss 去给自己攒等级的情况，记录 $t_u$ 表示可以击杀 $u$ 的最早时间，推式子得 $t_u=\frac{t_i-t_1}{A - B} + 2$。然后一遍 dij 跑最短路，与 BFS 差不多。

#### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 20, inf = 1e18;
int T;
int n, m, A, B;
int w[N];
struct edge {
    int u, v, nxt;
} e[2 * N];
int head[N], cnt;
int t[N], dis[N];
void add (int u, int v) {
    e[++ cnt] = {u, v, head[u]};
    head[u] = cnt;
}
void init () {
    cnt = 0;
    for (int i = 1; i <= n; i ++)
        head[i] = 0;
    for (int i = 1; i <= 2 * n; i ++)
        e[i] = {0, 0, 0};
}
int work1 () { // A <= B fast
    dis[1] = t[1] = 0;
    for (int i = 2; i <= n; i ++) {
        if (A == B)
            t[i] = (w[1] <= w[i] ? 0 : inf);
        else t[i] = (w[1] <= w[i] ? 0 : (w[1] - w[i] - 1) / (B - A) + 1);
        dis[i] = -1;
    }
    queue <int> q;
    q.push (1);
    while (q.size()) {
        int u = q.front ();
        q.pop ();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if (dis[v] == -1 && dis[u] + 1 <= t[v]) {
                dis[v] = dis[u] + 1;
                q.push (v);
            }
        }
    }
    return dis[n];
}
int work2 () { // A > B up lv
    dis[1] = t[1] = 0;
    for (int i = 2; i <= n; i ++) {
        t[i] = (w[1] <= w[i] ? ((w[i] - w[1]) / (A - B) + 2) : 1);
        dis[i] = inf;
    }
    struct node {
        int u, l;
        bool operator < (const node x) const {
            return l > x.l;
        }
    };
    priority_queue <node> q;
    q.push ({1, 0});
    int now = 0;
    while (q.size()) {
        node f = q.top ();
        q.pop ();
        int u = f.u;
        if (now < dis[u]) {
            dis[u] = inf;
            continue;
        }
        now ++;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if (max (dis[u] + 1, t[v]) < dis[v]) {
                dis[v] = max (dis[u] + 1, t[v]);
                q.push ({v, dis[v]});
            }
        }
    }
    return (dis[n] == inf ? -1 : dis[n]);
}
void solve () {
    init ();
    cin >> n >> m >> A >> B;
    for (int i = 1; i <= m; i ++) {
        int u, v;
        cin >> u >> v;
        add (u, v), add (v, u);
    }
    for (int i = 1; i <= n; i ++) {
        cin >> w[i];
        if (i > 1)
            w[i] += B;
    }
    if (A <= B)
        cout << work1 ();
    else cout << work2 ();
    cout << '\n';
}
signed main () {
    ios::sync_with_stdio (0);
    cin.tie (0), cout.tie (0);

    cin >> T;
    while (T --)
        solve ();
    return 0;
}
```

---

## 作者：WZwangchongming (赞：1)

题意：

共有 $T$ 组数据，每组给定一个 $n$ 个节点 $m$ 条边的无向图，每个节点 $i$ 上存在一个初始等级为 $l_i$ 的 BOSS。玩家一开始位于 1 号节点，初始等级为 $l_1$。（保证 1 号节点没有 BOSS）

而且玩家击杀 BOSS 遵循以下条件：

- 每天只能击杀一个 BOSS。
- 玩家等级高于当前要杀的 BOSS。
- 每天开始，玩家从 1 号节点经过**没有 BOSS** 的节点到达要杀的 BOSS 的节点。

每击杀一个 BOSS，玩家等级会增加 $A$。每天开始时，所有**仍存活的 BOSS** 等级增加 $B$。玩家的最终目标是击杀节点 $n$ 的 BOSS，求出达成最终目标至少需要多少天，如果不能通关则输出 -1。

数据范围：$$1 \le T \le 10^5,2\le n \le 2 \times 10^5,1 \le m,A,B \le 2 \times 10^5,\sum n, \sum m \le 10^6$$。

## solution

先来思考如下问题：

- 固定一个天数 $t$，哪些点可以在 $t$ 天内攻占？
- 知道了哪些点在 $t$ 天内可以攻占，哪些点又可以在 $t+1$ 天内攻占？

设当前可攻占点集合为 $S$。一开始，$S$ 内只有节点 $1$。每天开始后，考虑到存活 BOSS 等级数提升 $B$ 比较麻烦，可以转换成自己的等级减少 $B$，接着遍历一遍所有与可用点相邻的且不在可攻占点集合 $S$ 中的点，如果其等级不大于当前的等级，则将其加入可攻占点集合 $S$。一天结束后，将自身等级加上 $A$。

可以证明如下结论：
> 固定一个天数 $t$，在第 $t$ 天时，对于可攻占点集合 $S$ 中的任意点，一定存在一种方案使得最多不超过 $t$ 天就能击败该节点上的 BOSS。

因此，当最终节点 $n$ 被加入可攻占点集合 $S$ 时，即为打败最终 BOSS 的最早时间；同时，最优情况下必定是每天都打败一个节点的 BOSS，否则 BOSS 会越来越强。

所以在最终节点 $n$ 被加入可攻占点集合 $S$ 前，若第 $t$ 天结束时 $|S| \le t$，则无论如何也无法打败最终的 BOSS。

至此，我们已经得到了 $O(n^2)$ 或 $O(nm)$ 的做法，考虑优化。

回顾将可攻占点相邻的点放入集合 $S$ 的过程，每次都要判断这些相邻的点上的 BOSS 的等级是否不大于当前等级。那么优化思路就很明显了：因为等级越小的这种点越容易进入 $S$，所以将所有这些点放入一个小根堆，按等级数从小到大排列，每天都不断地取出堆顶加入 $S$，直到堆顶等级数不小于当前等级数，再将当天加入 $S$ 的点相邻的、且不在 $S$ 中的点压入堆中。

这个过程有点像一个 dijkstra，时间复杂度 $O((n+m)\log(n+m))$。


---

### Main Code：


```cpp
struct D {
	int dis, pos;
	bool operator < (const D &x) const { 
		return dis > x.dis; 
	}
};
struct tmp { int x, y; };
int dijkstra() {
	priority_queue <D> q;
	int s = 1, S = 0, now = a[s] - B;
	vis[s] = true;
	for(auto &x : G[s]) 
		if(!vis[x]) {
			q.push((D){a[x], x});
			vis[x] = true;
		}
	for(int t = 1; t <= n; t++) {
		vector <tmp> v;
		while(!q.empty() && q.top().dis < now) {
			int x = q.top().pos;
			q.pop();
			S++;
			if(x == n) return t;
			for(auto &u : G[x])
				if(!vis[u]) {
					v.emplace_back((tmp){a[u], u});
					vis[u] = true;
				}
		}
		for(auto &p : v) q.push((D){p.x, p.y});
		if(!S) return -1;
		now += A - B;
		S--;
	}
	return -1;
}
```

---

## 作者：zheng_zx (赞：1)

## P9881 [EC Final 2021] Elden Ring

[题目传送门](https://www.luogu.com.cn/problem/P9881)

### 题意

--- 

给你一个无向边构成的图（可以有环），你在 $1$ 点，终极 ```BOSS``` 在 $n$ 号点，其他的点上都是小 ```boss```，然后会给你每个点的经验值，如果是 $1$ 号点就是自身经验，否则是boss的经验。你每天可以攻击 $1$ 个与你占领点相邻的 ```boss```，初始占领点只有 $1$ 号点，然后你如果战胜了 $i$ 号点，那么这个点也就成为了你的占领点。如果你的经验严格大于这个 ```boss```，你就可以战胜他并获得 $A$ 的经验，每天开始的时候所有 ```boss``` 都会获得 $B$ 经验，问你多少天可以消灭终极 ```BOSS```，如果永远不可以，输出 $-1$。

### 分析

---

首先因为勇士和 ```BOSS``` 的增量是不同的，我们可以分类讨论一下 $A$ 和 $B$ 的情况。

1. $A=B$：也是最明显的情况，直接跑最短路判断能不能走到 $n$ 号点，如果可以就输出 $dis[n]$，否则输出 $-1$。

2. $A<B$：因为 $A<B$，所以我们越快到达 $n$ 号点越好。如果你第 $i$ 天打不过 ```BOSS```，那么你 $i+1$ 天也一定打不过。这里我们存一个 $c[i]$，就是用来维护每个 ```BOSS``` 点最迟能够什么时候干掉。如果你一开始就干不过，就赋为 $-1$。对于每个节点而言，我们能够打赢的时间区间就是在 $[1,c[i]]$ 这段时间内。在这里所有占领点扔进优先队列中，优先队列就是正常的最短路的优先队列，存放 $dis$ 和 $id$，$dis$ 在这里的意义是你要多少天才能打赢该 ```boss```。如果 $c[i]=-1$，或者是当前判到的点 $x$ 和后继节点 $y$，他的 $dis[x]>c[y]$ 我们也不用管，因为即使更新了也没有价值。然后在 $dis[x]<dis[y]$ 的情况下正常更新。其实就是在正常的对天数跑最短路，附加了一个 $[l,r]$ 区间内的条件，只有在 $[l,r]$ 内才能更新最短路。

3. $A>B$：这种情况下其实我感觉比较绕，因为可以有选择性了，因为会把一些其他的 ```boss``` 当做军备去打。然后这种情况可能可以一个 ```dij``` 搞定？反正我补题的时候理得有点乱，我先去用一个 ```dij``` 判能不能走到 $n$ 点，再去拿另一个 ```dij``` 判需要多少步走到 $n$ 点。跟 $A<B$ 的时候一样，我们可以先存一个 $c[i]$ 数组，用来存放 $i$ 点的 ```boss``` 最早可以第几天打完，那么此时的区间就是 $[c[i],\infty]$。判断的时候我们把占领点扔进优先队列中，然后如果你当前的 $dis<$ 我的军备量，那么意味着我永远打不过你，但是你又是我当前队列中的最小 $dis$，所以之后都不用打了，直接输出 $-1$。否则，将你未在队列中的后继点都扔进来。这样，就实现了第一个目的——能不能。然后我们再跑一个 ```dij```，这里就和上一个 $A<B$ 大差不差了，我们这里判的是 $\operatorname{max}(dis[x],c[y])+1<dis[y]$，如果可以就更新。

无论什么情况，输出 $dis[n]$ 即可。

---

## 作者：ThisIsLu (赞：0)

首先你可以分讨一下 $A \le B$ 和 $A>B$。

如果 $A \le B$ 是好做的，因为肯定尽量快速到达 $n$，跑一个 bfs 就没了。

如果 $A>B$，你可以算出对于每一个点 $i$ 的一个下界 $l_i=\max\left(1,\left\lfloor\dfrac{w_i+B-w_1}{A-B}\right\rfloor+2\right)$，当你的时间大于等于该值时，就一定可行。

再记 $dis_i$ 表示击杀 $i$ 的最小时间。

可以类似 dijkstra 的用一个优先队列每次取出 dis 最小的 $dis_u$ 并记录当前打了几只 Boss，那么如果当前打的 Boss 数小于 $dis_u$，则直接跳过并将 $dis_u$ 改为 $\infty$。

接着 $dis_v=\min(dis_v,\max(dis_u+1,l_v))$ 转移即可。

code:
```CPP
#include<bits/stdc++.h>
using namespace std;
int n,m,A,B,T;
const int N=1e6,INF=0x3f3f3f3f;
struct edge{
	int v,nxt;
} e[(N<<1)+5];
int head[N+5],w[N+5],ecnt;
void add(int u,int v){
	ecnt++;
	e[ecnt].v=v;
	e[ecnt].nxt=head[u];
	head[u]=ecnt;
}
int dis[N+5];
int myque[N+5],qhead,qtail;
void bfs(){
	dis[qhead=qtail=myque[1]=1]=0;
	for(int i=2;i<=n;i++) dis[i]=INF;
	while(qhead<=qtail){
		int u=myque[qhead++];
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(dis[v]==INF&&w[1]+(A-B)*dis[u]-B>w[v]){
				dis[v]=dis[u]+1;
				myque[++qtail]=v;
			}
		}
	}
}
struct dijnode{
    int u,dist;
    dijnode(int u=0,int dist=INF):u(u),dist(dist){}
    friend bool operator<(dijnode x,dijnode y){
        return x.dist>y.dist;
    }
};
priority_queue<dijnode> q;
int l[N+5];
void dijkstra(){
    dis[1]=l[1]=0;
    for(int i=2;i<=n;i++){
        dis[i]=INF;
        if(w[i]+B-w[1]<0) l[i]=1;
        else l[i]=(w[i]+B-w[1])/(A-B)+2;
    }
    int num=0;
    q.push(dijnode(1,0));
    while(!q.empty()){
        int u=q.top().u,dist=q.top().dist;
        q.pop();
        if(dis[u]>dist) continue;
        if(num<dis[u]){
            dis[u]=INF;
            continue;
        }
        num++;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].v;
            if(dis[v]>max(dis[u]+1,l[v])){
                dis[v]=max(dis[u]+1,l[v]);
                q.push(dijnode(v,dis[v]));
            }
        }
    }
}
void solve(){
	cin>>n>>m>>A>>B;
	for(int i=1;i<=n;i++) head[i]=0;
	ecnt=0;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
        cin>>w[i];
    }
	if(A<=B) bfs();
    else dijkstra();
    if(dis[n]==INF) cout<<"-1\n";
	else cout<<dis[n]<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) solve(); 
	return 0;
}
```

---

