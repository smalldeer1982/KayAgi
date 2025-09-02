# Counting Shortcuts

## 题目描述

Given an undirected connected graph with $ n $ vertices and $ m $ edges. The graph contains no loops (edges from a vertex to itself) and multiple edges (i.e. no more than one edge between each pair of vertices). The vertices of the graph are numbered from $ 1 $ to $ n $ .

Find the number of paths from a vertex $ s $ to $ t $ whose length differs from the shortest path from $ s $ to $ t $ by no more than $ 1 $ . It is necessary to consider all suitable paths, even if they pass through the same vertex or edge more than once (i.e. they are not simple).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650G/3360dade3a147f98c6dd4b25980520a2ae6123a6.png)Graph consisting of $ 6 $ of vertices and $ 8 $ of edgesFor example, let $ n = 6 $ , $ m = 8 $ , $ s = 6 $ and $ t = 1 $ , and let the graph look like the figure above. Then the length of the shortest path from $ s $ to $ t $ is $ 1 $ . Consider all paths whose length is at most $ 1 + 1 = 2 $ .

- $ 6 \rightarrow 1 $ . The length of the path is $ 1 $ .
- $ 6 \rightarrow 4 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 2 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 5 \rightarrow 1 $ . Path length is $ 2 $ .

There is a total of $ 4 $ of matching paths.

## 样例 #1

### 输入

```
4

4 4
1 4
1 2
3 4
2 3
2 4

6 8
6 1
1 4
1 6
1 5
1 2
5 6
4 6
6 3
2 6

5 6
1 3
3 5
5 4
3 1
4 2
2 1
1 4

8 18
5 1
2 1
3 1
4 2
5 2
6 5
7 3
8 4
6 4
8 7
1 4
4 7
1 6
6 7
3 8
8 5
4 5
4 3
8 2```

### 输出

```
2
4
1
11```

# 题解

## 作者：StudyingFather (赞：16)

考虑先对图上点进行分层。设 $d(s,i)$ 表示从 $s$ 点到 $i$ 点的距离。

分层之后，容易发现，图上的边可以分为两类。

1. 层间边。该边连接的两点的层数差 1。
2. 层内边。该边连接的两点层数相同。

最短路的数量在分层时可以顺带算出。现在思考如何算出比最短路长度恰好多 1 的路径数量。

注意到，每走一次层内边，到终点的总距离至少增加 1；而每走一次深度减小的层间边，到终点的距离至少增加 2。另外由于 BFS 的性质，如果只走层间边，且一直朝着深度增大的方向，路径一定与最短路相等。

从而得出结论：一条比最短路长度恰好多 1 的路径，一定经过恰好一条层内边。

（这个结论同时告诉我们：满足条件的路径一定是简单路径。因为非简单路径一定会走至少一条深度减小的层间边。）

考虑枚举层内边 $(u,v)$，如果 $d(s,u) + 1 + d(v,t) = d(s,t) + 1$，则该路径即为所求路径。

$d(s,u)$ 可以通过从 $s$ 点出发的 BFS 求出，$d(v,t)$ 可以通过从 $t$ 点出发的 BFS 求出，在 BFS 的同时顺带求出 $s$ 点到各点，各点到 $t$ 点的最短路径数即可。

对于每一条层内边，利用乘法原理即可求出经过该层内边，且路径长度满足条件的总路径数量。

```cpp
// Problem: G. Counting Shortcuts
// Contest: Codeforces - Codeforces Round #776 (Div. 3)
// URL: https://codeforces.com/contest/1650/problem/G
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
const int mod = 1000000007;
vector<int> e[200005];
pii ed[200005];
int dis1[200005], dis2[200005];
int f1[200005], f2[200005];
int n, m, s, t;
void bfs(int s, int* dis, int* f) {
  queue<int> q;
  memset(dis, -1, sizeof(int) * (n + 1));
  memset(f, 0, sizeof(int) * (n + 1));
  dis[s] = 0, f[s] = 1;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : e[u])
      if (dis[v] == -1) {
        dis[v] = dis[u] + 1;
        f[v] = f[u];
        q.push(v);
      } else if (dis[v] == dis[u] + 1)
        f[v] = (f[v] + f[u]) % mod;
  }
}
int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    cin >> s >> t;
    for (int i = 1; i <= n; i++) e[i].clear();
    for (int i = 1; i <= m; i++) {
      int u, v;
      cin >> u >> v;
      ed[i] = make_pair(u, v);
      e[u].push_back(v);
      e[v].push_back(u);
    }
    bfs(s, dis1, f1);
    bfs(t, dis2, f2);
    long long ans = f1[t];
    for (int i = 1; i <= m; i++) {
      int u = ed[i].first, v = ed[i].second;
      if (dis1[u] == dis1[v]) {
        if (dis1[u] + dis2[v] == dis1[t])
          ans = (ans + 1ll * f1[u] * f2[v]) % mod;
        if (dis1[v] + dis2[u] == dis1[t])
          ans = (ans + 1ll * f1[v] * f2[u]) % mod;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
```

---

## 作者：char_phi (赞：13)

~~图论专题本来打算先挑最简单的做，结果做了两个多小时（~~

题意就是让你找从起点 $s$ 到终点 $t$ 的最短路以及次短路个数，本题次短路长度指的是最短路长度 $+1$。

考虑 $\text{DP}$。

设 $dp_{u,0/1}$ 为当前到了点 $u$，$0/1$ 是与 $s$ 到 $u$ 的最短路长度相差 $0/1$ 的路径的条数。

手模几组样例容易得出转移方程。先跑一遍 $\text{Dijkstra}$ 算出 $s$ 到所有点的最短路 $dis$，设当前点为 $u$，下一个点为 $v$。则有：

- 若 $dis_v = dis_u$，则说明 $v$ 的最短路并非 $u$ 的最短路 $+1$，而是 $u$ 的最短路和 $v$ 的最短路差 $1$，则可 $dp_{u, 0} \to dp_{v, 1}$。

- 若 $dis_v = dis_u + 1$，则说明 $v$ 的最短路是可以由 $u$ 转移过来的。于是v继承u的所有状态。即：$dp_{u, 0} \to dp_{v, 0}\text{，}dp_{u, 1} \to dp_{v, 1}$。

初态是 $dp_{s, 0} = 1$，因为题目问的是最短路与次短路个数之和所以末态为 $dp_{t, 0} + dp_{t, 1}$。

至此就可以高高兴兴写出一个 $\text{dfs}$ 代码了。

```cpp
void dfs(int x) {
	if (x == hd)
		return ;
	vis[x] = true;
	for (re i = head[x] ; i ; i = e[i].nxt) {
		int v = e[i].v;
		if (vis[v] == true)
			continue;
		if (dis[v] == dis[x])
			Plus(dp[v][1], dp[x][0]);
		else if (dis[v] == dis[x] + 1)
			Plus(dp[v][0], dp[x][0]), Plus(dp[v][1], dp[x][1]);
		dfs(v);
	}
	vis[x] = false;
}
```

然后测一下前三个样例，哇，都过了。以为这题就要切了，测第四个样例结果发现输出 `1204`。

显然是转移多了。考虑下面一张图：

![image](https://cdn.luogu.com.cn/upload/image_hosting/ag23vczn.png)

按照写的 $\text{dfs}$ 模一下发现点 $4$ 和点 $3$ 转移到点 $5$ 的时候出现了问题：转移顺序。

比如转移顺序：$2 \to 4 \to 5$，但是还有 $2 \to 3 \to 4 \to 5$，发现在第一遍转移的时候已经转移给了点 $5$，但是第二次转移的时候除了把新的值转移给了 $5$，还把以前的值又转移了一遍。所以就转移多了。

考虑如何解决。既然你是重复转移了前一次的，那我对于每个点转移过了之后把他的 $\text{dp}$ 值清空，下一次再来到这个点的时候就不会重复转移上一次的值了。

```cpp
void dfs(int x) {
	if (x == hd)
		return ;
	vis[x] = true;
	for (re i = head[x] ; i ; i = e[i].nxt) {
		int v = e[i].v;
		if (vis[v] == true)
			continue;
		if (dis[v] == dis[x])
			Plus(dp[v][1], dp[x][0]);
		else if (dis[v] == dis[x] + 1)
			Plus(dp[v][0], dp[x][0]), Plus(dp[v][1], dp[x][1]);
		dfs(v);
	}
	dp[x][0] = dp[x][1] = 0;// 多加了这一句
	vis[x] = false;
}
```

交上去会发现 `TLE on test #3`，我不太清楚 $\text{dfs}$ 常数大还是咋地，卡了半天常也过不去（

> $\text{Update}$：加个记搜大概能过，$\text{dfs}$ 慢是因为有重复的转移，旁边的大佬说造个完全图可以卡到指数级别（。

考虑换一种解决方法。发现重复转移的实质就是拿还没转移完毕的去更新其他的了，于是考虑如何让他转移完毕再去更新。

注意到点 $u$ 所有的转移都是对于 $dis_v = dis_u$ 或 $dis_v = dis_u + 1$ 的 $v$ 去转移，这启示我们按照 $dis$ 对原图进行分层。对于每个点 $u$ 先对于同层也就是 $dis_v = dis_u$ 的点 $v$ 进行转移，全部转移完毕后再去转移 $dis_v = dis_u + 1$ 的点 $v$ 即可。

$\text{DP}$ 转移时间复杂度是 $\mathcal O(n)$ 的，最短路时间复杂度是 $\mathcal O(n \log n)$ 的，于是总时间复杂度为 $\mathcal O(n \log n)$。

```cpp
#pragma GCC optimize(2)
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#define GMY (520 & 1314)
#define char_phi int
#define re register int
#define FBI_OPENTHEDOOR(x, y) freopen(#x ".in", "r", stdin), freopen(#y ".out", "w", stdout)
#define N 2000005
#define M 2000005
#define P 1000000007
using namespace std;
inline void Fastio_setup() { ios :: sync_with_stdio(false); cin.tie(NULL), cout.tie(NULL); }
inline int MAX(int x, int y) { return ((x > y) ? (x) : (y)); }
inline int MIN(int x, int y) { return ((x < y) ? (x) : (y)); }
 
int n, m, star_cnt, yd, hd;
char vis[N];
int head[N], q[M<<3], dis[N];
int dp[N][2];
 
struct star { int v, nxt; };
struct Node {
	int x, d;
	
	friend bool operator < (Node A, Node B) { return A.d > B.d; }
};
 
struct star e[M<<1];
 
priority_queue<Node> heap;
vector<int> vec[N];
 
inline void star_add(int u, int v) { e[++ star_cnt].v=v, e[star_cnt].nxt=head[u], head[u]=star_cnt; }
inline void Clean() {
	star_cnt = 0; vec[0].clear();
	for (re i = 1 ; i <= n ; ++ i) {
		head[i] = dp[i][0] = dp[i][1] = 0;
		vec[i].clear();
	}
}
 
inline void Dijkstra() {
	int x = yd; for (re i = 1 ; i <= n ; ++ i) dis[i] = 0x3f3f3f3f, vis[i] = false;
	heap.push( (Node) {x, 0} ); dis[x] = 0;
	while (heap.empty() == false) {
		x = heap.top().x; heap.pop();
		if (vis[x] == true)
			continue;
		vis[x] = true;
		for (re i = head[x] ; i ; i = e[i].nxt) {
			int v = e[i].v;
			if (dis[v] > dis[x] + 1) {
				dis[v] = dis[x] + 1;
				if (vis[v] == false)
					heap.push( (Node) { v, dis[v] } );
			}
		}
	}
}
inline void Plus(int& who, int val) { who += val; if (who >= P) who -= P; }
 
inline void Search() {// 先更新0再更新1
	for (re i = 1 ; i <= n ; ++ i) {
		vis[i] = false;
		vec[dis[i]].emplace_back(i);
	}
	
	dp[yd][0] = 1;
	for (re dep = 0 ; dep <= n ; ++ dep) {
		for (auto x : vec[dep])
			for (re i = head[x] ; i ; i = e[i].nxt) {// 先转移同层的
				int v = e[i].v;
				if (dis[v] == dep)
					Plus(dp[v][1], dp[x][0]);
			}
		for (auto x : vec[dep])
			for (re i = head[x] ; i ; i = e[i].nxt) {// 再转移其他层的
				int v = e[i].v;
				if (dis[v] == dep + 1)
					Plus(dp[v][0], dp[x][0]), Plus(dp[v][1], dp[x][1]);
			}
	}
}


inline void work() {
	Clean();
	cin >> n >> m; cin >> yd >> hd;
	for (re i = 1, uu, vv ; i <= m ; ++ i)
		{cin >> uu >> vv; star_add(uu, vv), star_add(vv, uu);}
	
	Dijkstra();
	Search();// 也许算是bfs罢
	
	cout << (dp[hd][0] + dp[hd][1]) % P << '\n';
}
 
#undef int
// #define IXINGMY
char_phi main() {
	#ifdef IXINGMY
		FBI_OPENTHEDOOR(a, a);
	#endif
	Fastio_setup();
	int T; cin >> T;
	while (T --)
		work();
	return GMY;
}
```

> $\text{Hint}$：参考了[ $\text{Jerry-Black}$ 大佬](https://www.cnblogs.com/Jerry-Black/p/16008034.html)的思路。

---

## 作者：Sellaris (赞：5)

 -  题意 : 非简单次短路计数
 
 -  TIP : 模板题
 
 -  前置知识：Dijkstra
 
 -  思路 : 寻找与最短路长度相差不超过 $1$ 的路径数，而题目又是无边权，即可得到 **“寻找次短路径数”** 的题意。对于最短路，考虑 Dijkstra 算法，有最短路更新最短路，更新则记录原最短路为次短路。对于每条路径，判断长度是否等于次短路，等于便更新答案即可。
 
 - 详情可见代码注释。
 
 - 特别感谢 @cmll02 大佬帮忙调错
 
```cpp
#pragma once
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#include <bits/extc++.h>

#define int LL 

using namespace std;
using namespace __gnu_pbds;

typedef long long LL;
const int maxn = 2e5 + 5;//顶点数
const int maxm = 4e5 + 5;//边数
const LL inf = 0x3f3f3f3f3f3f3f3f;
const LL mo=1000000007;

__gnu_pbds::tree <LL,null_type,less<LL>,rb_tree_tag,tree_order_statistics_node_update> TREE ;

struct Dijstra{
    mutable int n, m;//d2[t] < inf代表有解
    mutable int d[2][maxn];//d[0]记录最短路，d[1]记录次短路
    mutable int cnt[2][maxn];//cnt[0]记录最短路条数，cnt[1]记录次短路径条数
    mutable int head[maxn];
	//int par[maxn]; //记录路径
    struct Edge{
        mutable int to, nxt;
        mutable int dis;
    }e[maxm];
    
    struct Node{
        mutable int f;//0代表最短路，1代表次短路
        mutable int u;//结点编号
        mutable int dis;
        bool operator<(const Node &rhs) const{
            return dis > rhs.dis;
        }
    };

    inline void init(int nn){
        n = nn;
        m = 0;
        memset(head, 0xff, sizeof head);
    }

    inline void addEdge(int from, int to, int dis){
        e[m].to = to;
        e[m].dis = dis;
        e[m].nxt = head[from];
        head[from] = m++;
    }
    
    inline void finda(int s){
        std::priority_queue<Node> q;
        for(int i = 0; i < n; ++i) d[0][i]  = d[1][i] = inf;//0~n-1，注意下标从哪里开始
        d[0][s] = 0;
        for(int i = 0; i < n; ++i) cnt[0][i] = cnt[1][i] = 0;
        cnt[0][s] = 1;
        q.push((Node){0, s, 0});
        while(!q.empty()){
            Node x = q.top(); q.pop();
            int u = x.u;
            int dis = x.dis;
            int f = x.f;
            if(d[f][u] < dis) continue;
            for(int i = head[u]; ~i; i = e[i].nxt){
                int v = e[i].to;
                int dd = dis + e[i].dis;
                if(d[0][v] > dd){//能更新最短路就先更新最短路
                    if(d[0][v] < inf){
                        d[1][v] = d[0][v];//之前的最短路变为次短路
                        cnt[1][v] = cnt[0][v];
                        q.push((Node){1, v, d[1][v]});
                    }
                    //更新最短路
                    d[0][v] = dd;
                    cnt[0][v] = cnt[f][u];
                    q.push((Node){0, v, d[0][v]});
                }
                else if(d[0][v] == dd){
                    ( cnt[0][v] += cnt[f][u] ) %= mo ;//更新最短路条数
                }
                else if(d[1][v] > dd){
                    d[1][v] = dd;//不能更新最短路，只能更新次短路
                    cnt[1][v] = cnt[f][u];
                    q.push((Node){1, v, d[1][v]});
                }
                else if(d[1][v] == dd){
                    ( cnt[1][v] += cnt[f][u] ) %= mo ;//更新次短路条数
                }
            }
        }
    }
}a;

signed main(){
    int T;
    scanf("%lld" , &T);
    while(T--){
        int n, m;
        scanf("%lld%lld", &n, &m);
        int s, t;
        scanf("%lld%lld", &s, &t);
		--s;--t;
        a.init(n);
        int u, v, w=1;
        for(int i = 0; i < m; ++ i){
            scanf("%lld%lld", &u, &v);
            a.addEdge(u-1, v-1, w);
            a.addEdge(v-1, u-1, w);
        }
        a.finda(s);
        int res = a.cnt[0][t];
        if(a.d[1][t] - 1 == a.d[0][t]) ( res += a.cnt[1][t] ) %= mo ;
        printf("%lld\n", res);
    }
    return 0;
}
```



---

## 作者：AmamiyaYuuko (赞：4)

首先用 Dijkstra 求出 $s$ 到任意一个点的最短路，设为 $d_x$。

设 $f(i, 0 / 1)$ 表示在点 $i$，与最短路相差 $0 / 1$ 的方案数，可以写出转移方程：

$$
\begin{aligned}
&f(u, 1) \to f(v, 1), d_v = d_u + 1 \\
&f(u, 0) \to f(v, 0), d_v = d_u + 1 \\
&f(u, 0) \to f(v, 1), d_v = d_u
\end{aligned}
$$

其中 $u \to v$ 是原图中的一条边。初始有 $f(s, 0) = 1$，答案为 $f(t, 0) + f(t, 1)$。

由于转移顺序可能比较复杂，可以使用记忆化搜索实现。

代码：

```cpp
#include <bits/stdc++.h>

template <class T>
inline void read(T &x) {
    x = 0;
    int f = 0;
    char ch = getchar();
    while (!isdigit(ch))    { f |= ch == '-'; ch = getchar(); }
    while (isdigit(ch))     { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return ;
}

typedef unsigned long long uLL;
typedef long long LL;

const LL mod = 1e9 + 7;

struct Node {
    int pos, dis;
    friend bool operator < (const Node &a, const Node &b) {
        return a.dis > b.dis;
    }
};

std::vector<int> g[200010];
LL f[200010][2];
int d[200010];
int T, n, m, s, t;
bool vis[200010];

void dijkstra() {
    for (int i = 1; i <= n; ++i)    d[i] = 2e9;
    d[s] = 0;
    std::priority_queue<Node> q;
    q.push((Node){s, 0});
    while (!q.empty()) {
        Node now = q.top();
        q.pop();
        if (vis[now.pos])    continue;
        vis[now.pos] = true;
        for (auto i : g[now.pos]) {
            if (d[i] > d[now.pos] + 1) {
                d[i] = d[now.pos] + 1;
                q.push((Node){i, d[i]});
            }
        }
    }
}

LL dp(int x, int k) {
    if (~f[x][k])    return f[x][k];
    LL s = 0;
    for (auto i : g[x]) {
        if (d[i] + 1 == d[x])    s += dp(i, k), s %= mod;
        else if (d[i] == d[x] && k == 1)    s += dp(i, k - 1), s %= mod;
    }
    return f[x][k] = s;
}

int main() {
    read(T);
    while (T--) {
        read(n), read(m);
        for (int i = 1; i <= n; ++i)    g[i].clear(), f[i][0] = f[i][1] = -1, vis[i] = false;
        read(s), read(t);
        for (int i = 1, u, v; i <= m; ++i) {
            read(u), read(v);
            g[u].push_back(v), g[v].push_back(u);
        }
        dijkstra();
        f[s][0] = 1;
        printf("%lld\n", (dp(t, 0) + dp(t, 1)) % mod);
    }
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

## 题面大意

给出一个无重边无自环的无向图，求从 $s$ 点到 $t$ 点最多比最短距离多 $1$ 的路径数，对 $998244353$ 取模。

## 思路

考虑 $dp$，$dp_{i,j}$ 表示看到 $i$ 点，比最短距离长 $j$ 的路径条数。将整个图按最短距离划分成层。$dp_{s,0}=1,dp_{s,1}=0$，首先我们考虑将距离 $s$ 为 $i$ 的节点进行 bfs 扩展，得到所有距离 $s$ 为 $i+1$ 的节点，同时状态转移（考虑 $u$ 为目前节点，$v$ 为扩展节点，$dist_{v}=dist_{u}+1$）$dp_{v,0}:=dp_{v,0}+dp_{u,0},dp_{v,1}:=dp_{v,1}+dp_{u,1}$。在此之后，我们还要考虑距离 $s$ 为 $i+1$ 互相之间连的边（考虑 $u,v$ 之间有边，$dist_u=dist_v$）$dp_{v,1}:=dp_{v,1}+dp_{u,0},dp_{u,1}:=dp_{u,1}+dp_{v,0}$，然后让 $i$ 加一，继续扩展即可。

最后输出 $dp_{t,0}+dp_{t,1}$，**记住最后相加后还要再对 $998244353$ 取模**。（别问我为啥加粗，要问就是我赛时降智。）

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int f[200005][2],minv[200005];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		int s,t;
		cin>>s>>t;
		vector<int> g[n+1];
		for(int i=1;i<=n;i++){
			minv[i]=1e18;
			f[i][0]=f[i][1]=0;
		}
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			g[u].push_back(v);
			g[v].push_back(u);
		} 
		queue<int> q;
		q.push(s);
		f[s][0]=1;
		minv[s]=0;
		while(!q.empty()){
			int lev=minv[q.front()];
			queue<int> sq;
			while(!q.empty()){
				int u=q.front();
				q.pop();
				sq.push(u);
				for(auto v:g[u]){
					if(minv[v]==minv[u]){
						f[v][1]=(f[v][1]+f[u][0])%mod;
					}
				}
			}
			while(!sq.empty()){
				int u=sq.front();
				sq.pop();
				for(auto v:g[u]){
					if(minv[v]==1e18){
						minv[v]=minv[u]+1;
						f[v][0]=f[u][0];
						f[v][1]=f[u][1];
						q.push(v);
					}
					else if(minv[v]==minv[u]+1){
						f[v][0]+=f[u][0];
						f[v][1]+=f[u][1];
					}
					f[v][0]%=mod;
					f[v][1]%=mod;
				}
			}
		}
		cout<<(f[t][0]+f[t][1])%mod<<endl;
	}
	return 0;
}
```

---

## 作者：aimcf (赞：0)

简单题。看到这一类题直接想到以 $s$、$t$ 分别跑一遍最短路，然后考虑到若一条路径满足条件则它的最后一个不重合的点 $v$ 一定满足 $s$ 到 $v$ 的距离和 $s$ 到下一个重合的点 $u$ 的距离相等。因此只需要枚举一条边，判断它是否可以是不重合路径上最后一条边，然后分类计算其贡献即可。

时间复杂度为最短路的时间复杂度。

```cpp
vector<int> z[N];
int d1[N], d2[N], c1[N], c2[N];
struct qwq {
    int u, dis;
    bool operator<(const qwq &r) const {
        return dis > r.dis;
    }
};
void dijk(int s, int *d, int *c) {
    priority_queue<qwq> q;
    q.push({s, d[s] = 0});
    c[s] = 1;
    while (q.size()) {
        qwq t = q.top();
        q.pop();
        if (t.dis <= d[t.u]) {
            for (auto &g : z[t.u]) {
                if (d[g] > d[t.u] + 1) {
                    d[g] = d[t.u] + 1;
                    c[g] = c[t.u];
                    q.push({g, d[g]});
                } else if (d[g] == d[t.u] + 1) {
                    c[g] += c[t.u];
                    c[g] %= mod;
                }
            }
        }
    }
}
void run() {
    int T = read();
    while (T--) {
        int n = read(), m = read(), s = read(), t = read();
        for (int i = 1; i <= n; ++i) {
            d1[i] = d2[i] = 1e18;
            c1[i] = c2[i] = 0;
            z[i].clear();
        }
        vector<pair<int, int>> edge;
        for (int i = 0; i < m; ++i) {
            int x = read(), y = read();
            z[x].eb(y), z[y].eb(x);
            edge.eb(x, y);
        }
        dijk(s, d1, c1);
        dijk(t, d2, c2);
        int sc = c1[t];
        for (auto &[x, y] : edge) {
            if (d1[x] == d1[y]) {
                if (d2[x] + d1[y] == d1[t]) {
                    sc = (sc + c1[y] * c2[x]) % mod;
                } if (d2[y] + d1[x] == d1[t]) {
                    sc = (sc + c2[y] * c1[x]) % mod;
                }
            }
        }
        cout << sc << '\n';
    }
} }

signed main() {
    ttq012::run();
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

### Preface

赛场上被 Hack 了 qwq。

### Analysis

设最短路长度为 $D$，以及 $dis_i$ 表示 $s\to i$ 的最短路径长度。首先，$s\to t$ 的长度为 $D+1$ 的路径一定不会有点被多次经过。

引理 A：每条边 $(x,y)$ 必然满足 $|dis_x-dis_y|\le 1$。

**证明：**

反证，假设有一条路径（其实只能算通道了）经过的点集为 $\{s,p_1,p_2,\dots,p_D,t\}$ 且存在 $u<v$ 使得 $p_u=p_v$。由引理可得 $dis_{p_u}\le u$，即 $dis_{p_v}\le u$，此时得出 $p_v\to t$ 的最短路径长度一定 $\ge D-u$，而 $\{p_v,p_{v+1},\dots,p_D,t\}$ 的长度为 $D-v<D-u$，矛盾，原命题得证。$\blacksquare$

由这个证明我们也得到：$s\to t$ 的长度为 $D+1$ 的路径包含且仅包含一条边 $(u,v)$ 使得 $dis_u=dis_v$。我们枚举这条特殊的边，分别预处理出 $s\to u$ 和 $v\to t$ 的最短路径条数相乘即可。

时间 $O(n+m)$。

### Code

[Link](https://codeforces.com/contest/1650/submission/149199434)

---

