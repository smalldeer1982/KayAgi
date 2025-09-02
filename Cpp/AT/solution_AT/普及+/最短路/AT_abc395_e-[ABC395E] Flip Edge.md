# [ABC395E] Flip Edge

## 题目描述

给定一个包含 $N$ 个顶点和 $M$ 条边的有向图。第 $i$ 条边（$1 \leq i \leq M$）从顶点 $u_i$ 指向顶点 $v_i$。

初始时，你位于顶点 $1$，需要通过重复以下操作到达顶点 $N$：

- 选择以下两种操作之一：
  - **移动操作**：从当前顶点沿边移动到相邻顶点，成本为 $1$。具体来说，设当前顶点为 $v$，选择一条从 $v$ 指向 $u$ 的边，移动到顶点 $u$。
  - **翻转操作**：反转所有边的方向，成本为 $X$。具体来说，在操作前存在的每条从 $v$ 到 $u$ 的边，在操作后将变为从 $u$ 到 $v$ 的边，反之亦然。

题目保证存在从顶点 $1$ 到顶点 $N$ 的操作序列。

请计算到达顶点 $N$ 所需的最小总成本。

## 说明/提示

### 约束条件
- $2 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^5$
- $1 \leq X \leq 10^9$
- $1 \leq u_i \leq N$（$1 \leq i \leq M$）
- $1 \leq v_i \leq N$（$1 \leq i \leq M$）
- 输入均为整数

### 样例解释 1
给定图的示意图（图片链接略）。通过以下操作序列，总成本为 $4$：
- 花费 $1$ 移动到顶点 $2$
- 花费 $1$ 移动到顶点 $4$
- 花费 $1$ 移动到顶点 $3$
- 花费 $1$ 移动到顶点 $5$

无法以 $3$ 或更小的总成本到达顶点 $5$，因此输出 `4`。

### 样例解释 2
图的边与样例 1 相同，但翻转成本不同。通过以下操作序列，总成本为 $3$：
- 花费 $1$ 移动到顶点 $2$
- 花费 $1$ 执行翻转操作
- 花费 $1$ 移动到顶点 $5$

无法以 $2$ 或更小的总成本到达顶点 $5$，因此输出 `3`。

### 样例解释 3
答案可能超过 32 位整数范围，需注意处理大数。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5 6 5
1 2
2 4
3 1
3 5
4 3
5 2```

### 输出

```
4```

## 样例 #2

### 输入

```
5 6 1
1 2
2 4
3 1
3 5
4 3
5 2```

### 输出

```
3```

## 样例 #3

### 输入

```
8 7 613566756
2 1
2 3
4 3
4 5
6 5
6 7
8 7```

### 输出

```
4294967299```

## 样例 #4

### 输入

```
20 13 5
1 3
14 18
18 17
12 19
3 5
4 6
13 9
8 5
14 2
20 18
8 14
4 9
14 8```

### 输出

```
21```

# 题解

## 作者：Sanust (赞：6)

# AT_abc395_e Flip Edge

题意大概是从一个有向图的 $1$ 号节点出发，所有边的边权都是 $1$，还可以选择花 $X$ 的代价翻转一次边的方向，问到达 $N$ 号节点的最小代价。问题的关键在于如何解决翻转方向。

考虑建一个双层图，层与层之间建一条代价为 $X$ 的**无向**边，上面一层图是原图，下面一层图是反向边后的图。这样建图后的样例二看起来就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/tmt770id.png)

红色箭头标注的路径即为从 $1$ 到 $5$ 的最短路。接着从上面一层图的 $1$ 号节点跑一遍最短路即可，答案是 $1$ 号节点分别到上下两层图的 $N$ 号节点的代价的**较小值**。

类似于 [P4568飞行路线](https://www.luogu.com.cn/problem/P4568) 这道题一样，建多层图跑最短路是对于有一些特殊条件或操作的题目的较为常见的可能思路。做多层图的题一定要注意开大空间，因为对本题而言多连了 $M+2N$ 条有向边，多建了 $N$ 个点，赛时因为这个 `RE` 了一发，还有记得开 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 5;
struct Edge
{
    ll u, v, w, nxt;
} e[N];
ll n, m, x, head[N], pos, dis[N];
bool vis[N];
void addEdge(ll u, ll v, ll w)
{
    e[++pos] = {u, v, w, head[u]};
    head[u] = pos;
}
struct node
{
    ll v, w;
    bool operator<(const node t) const
    {
        return t.w < w;
    }
};
void dijkstra(ll st)
{
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<node> q;
    q.push({st, 0}), dis[st] = 0;
    while (!q.empty())
    {
        ll u = q.top().v;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (ll i = head[u]; i != -1; i = e[i].nxt)
        {
            ll v = e[i].v, w = e[i].w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                q.push({v, dis[v]});
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(head, -1, sizeof(head));
    cin >> n >> m >> x;
    for (int i = 1; i <= n; i++) // 上下两层图建边权为x的无向边
        addEdge(i, i + n, x), addEdge(i + n, i, x);
    for (ll i = 0; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
        addEdge(u, v, 1); // 原图正向边
        addEdge(v + n, u + n, 1); // 复制图反向边
    }
    dijkstra(1); // 从原图1号点开跑
    cout << min(dis[n], dis[2 * n]); // 比较两种可能的答案并取最小
    return 0;
}
```

---

## 作者：Clover_Lin (赞：5)

https://blog.csdn.net/ArmeriaLeap/article/details/145955054

## 题目大意
[有向图最短路，可以花钱反转所有边。](https://atcoder.jp/contests/abc395/tasks/abc395_e)
## 思路
**注：为了与代码呼应，本文用 $K$ 代替原题面中的 $X$，如有不便敬请谅解。**

数据范围：$N,M \le 2\times 10^5$，**Dijkstra** 能过。

读入：正反边存一个图，标注清楚。

记录当前点：$(x,t)$。其中 $x$ 是节点编号，$t=1$ 时这个点是从正向边过来的，$t=2$ 时相反。每一次，要么顺着 $t$ 的方向走（花费 $1$ 日元），要么反之（花费 $K+1$ 日元，反转费 + 走路费）。
## 代码实现
[Submission #63274095](https://atcoder.jp/contests/abc395/submissions/63274095)

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n, m, k;
long long dis[200010][10];
int vis[200010][10];

struct edge
{
	int y, t;
} ;

vector<edge> g[200010];

struct node
{
	int x, t;
	long long d;
	
	bool operator < (const node & b) const
	{
		return d > b.d;
	}
} ;

void dijkstra(int s)
{
	priority_queue<node> q;
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	q.push((node){s, 1, 0});
	dis[s][1] = 0;
	while (q.size())
	{
		int x = q.top().x;
		int t = q.top().t;
		q.pop();
		if (vis[x][t]) continue;
		vis[x][t] = 1;
		for (int i = 0; i < g[x].size(); i++)
		{
			int y = g[x][i].y, tt = g[x][i].t;
			int w = 1; if (tt != t) w += k;
			if (dis[y][tt] > dis[x][t] + w)
			{
				dis[y][tt] = dis[x][t] + w;
				q.push((node){y, tt, dis[y][tt]});
			}
		}
	}
}

int main()
{
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
	{
		int x, y; cin >> x >> y;
		g[x].push_back((edge){y, 1});
		g[y].push_back((edge){x, 2});
	}
	dijkstra(1);
	cout << min(dis[n][1], dis[n][2]) << endl;
	return 0;
}
// 思维难度比 D 低，细节也少，难度大概是黄题
```

---

## 作者：exLucas (赞：4)

# 思路：
这一题直接跑 Dijkstra 算法就可以。但是由于存在反转边操作，我们需要额外记录当前图的边的方向状态。可以使用一个三元组 $(u, d, dir)$ 来表示当前状态，其中 $u$ 是当前所在的顶点，$d$是到达该顶点的最小花费，$dir$ 表示当前图的边的方向状态,可以用 $0$ 表示原始方向，$1$ 表示反转后的方向。

具体来说跑最短路时只需要在板子上加上尝试反转当前边的代码就可以了。

# 复杂度：
- 时间复杂度：$O((M + N)\log(N))$ ，其中 $N$ 是顶点数，$M$ 是边数。
- 空间复杂度：$O(M + N)$

# Code:
这么简单就不放了吧（

---

## 作者：Lovely_yhb (赞：4)

### 题意

给定一个有向图，可以花 $x$ 的代价把边反转，花 $1$ 的代价走一条边。

问从 $1$ 到 $n$ 的最小代价。

### 思路

分层图最短路练手题。

一共两层图，一层正图，一层反图。在两层之间连一条权值为 $x$ 的双向边。然后跑 dijkstra 即可。

有可能是到反转层的终点最短，也有可能是到原层的终点最短，所以答案应该是二者间取 $\min$。

记得开 long long。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,x,u,v,dis[N];
vector<pair<int,int> > to[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
signed main() {
	cin>>n>>m>>x;
	int tot=2*n;
	for(int i=0; i<m; i++) {
		cin>>u>>v;
		int u0=2*(u-1),v0=2*(v-1);
		to[u0].push_back({v0,1});
		int u1=2*(u-1)+1,v1=2*(v-1)+1;
		to[v1].push_back({u1,1});
	}
	for(int v=1; v<=n; v++) {
		int s0=2*(v-1),s1=s0+1;
		to[s0].push_back({s1,x});
		to[s1].push_back({s0,x});
	}
	memset(dis,0x3f,sizeof dis);
	dis[0]=0;
	q.push({0,0});
	while(!q.empty()) {
		auto[d,u]=q.top();
		q.pop();
		if(d!=dis[u]) continue;
		for(auto[v,w]:to[u]) {
			if(dis[v]>d+w) {
				dis[v]=d+w;
				q.push({dis[v],v});
			}
		}
	}
	cout<<min(dis[2*(n-1)],dis[2*(n-1)+1]);
	return 0;
}
```

---

## 作者：__Creeper__ (赞：3)

## 题意

给你一个有向图，图中有 $N$ 个顶点和 $M$ 条边。 $i$ -th 边 $(1 \leq i \leq M)$ 是一条从顶点 $u _ i$ 到顶点 $v _ i$ 的有向边。

最初，您位于顶点 $1$ 。您要重复以下操作直到到达顶点 $N$ ：

- 执行以下两个操作之一：
    - 从当前顶点沿一条有向边移动。这需要花费 $1$ 。更精确地说，如果你在顶点 $v$ ，选择一个顶点 $u$ ，使得有一条从 $v$ 到 $u$ 的有向边，然后移动到顶点 $u$ 。
    - 反转所有边的方向。这样做的代价是 $X$ 。更确切地说，如果且仅如果在此操作之前有一条从 $v$ 到 $u$ 的有向边，那么在此操作之后有一条从 $u$ 到 $v$ 的有向边。

可以保证，对于给定的图，重复这些操作可以从顶点 $1$ 到达顶点 $N$ 。

求到达顶点 $N$ 所需的最小总成本。

## 思路

本题考虑分层图。

我们将图分成两层，第一层为正常的图，第二层为反图。第一层进入第二层花费代价为 $X$。每次向上或向下跑一层，就相当于换方向。建完图再用 Dijkstra 求从顶点 $1$ 出发的单源最短路，答案为第一层和第二层的 $dis_n$ 的最小值。


## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 4e5 + 5;
struct node {
	int x, y, id;
}a[N];
int n, m, x, dis[N], cnt[N];
bool inq[N];
vector<pair<int, int> > G[N];
bool vis[N];
struct did {
	int u, d;
	bool operator< (const did &o) const{
		return d > o.d;
	}
};

void dij(int s) {
	memset(dis, 0x7f - 1, sizeof(dis));
	dis[s] = 0;
	priority_queue<did> q;
	q.push({s, 0});
	while(!q.empty()) {
		did x = q.top();
		q.pop();
		if(vis[x.u]) continue;
		vis[x.u] = 1;
		for(auto [v, w]: G[x.u]) {
			if(dis[x.u] + w < dis[v]) {
				dis[v] = dis[x.u] + w;
				q.push({v, dis[v]});
			}
		}
	}
}

void solve() {
	cin >> n >> m >> x;
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back({v, 1}); // 正常的图
		G[v + n].push_back({u + n, 1}); // 反图
	}
	for(int i = 1; i <= n; i++) {
		G[i].push_back({i + n, x}); // 连接两层图
		G[i + n].push_back({i, x});
	}
	dij(1);
	cout << min(dis[n], dis[n * 2]);
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
//	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：xyx404 (赞：2)

## 题意：
给定一个有向图，我们从顶点 $1$ 出发，想要到达顶点 $N$。 

有两种操作：
1. 沿着有向边移动到下一个顶点，花费为 $1$。
2. 反转所有边的方向，花费为 $X$。

我们的目标是找到到达 $N$ 的最小总花费。

## 思路：
最短路，迪杰斯特拉。

只需要改建图就行了。

### 建图：
每个顶点 $u$ 在原图和反转图中被分别表示为两个节点 $2 \times u$ 为状态 $0$ 原图和 $2 \times u+1$ 为状态 $1$ 反转图。

原图边：对于原边 $u$ 到 $v$，在状态 $0$ 中添加边 $2 \times u$ 到 $2 \times v$ 代价为 $1$。

反转边：对于原边 $u$ 到 $v$，在状态 $1$ 中添加边 $2 \times v+1$ 到 $2 \times u+1$ 代价为 $1$。

状态切换边：每个顶点 $u$ 在两种状态间添加 $2 \times u$  到 $2 \times u + 1$ 的双向边，代价为 $X$。

之后照常跑迪杰斯特拉就行了。

因为每个点都被分成了两个，所以最后输出要在两个终点中取最小值。

[提交记录和代码](https://atcoder.jp/contests/abc395/submissions/63284382)。

---

## 作者：chenhanzheapple (赞：2)

# 思路

一眼分层图。

分成两层，第一层正向边，第二层反向边，每个节点可以花 $x$ 的代价换层，具体见代码。

# 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,xx;
struct node{
    int x,w;
    bool operator <(const node &x)const{
        return x.w<w;
    }
};
int dis[400005];
bool vis[400005];
vector<node> v[400005];
void dijkstra(int s){
    priority_queue<node> que;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s] = 0;
    que.push((node){s,0});
    while(!que.empty()){
        node t = que.top();
        que.pop();
        if(vis[t.x]){
            continue;
        }
        vis[t.x] = 1;
        for(auto x:v[t.x]){
            if(dis[t.x]+x.w<dis[x.x]){
                dis[x.x] = dis[t.x]+x.w;
                que.push((node){x.x,dis[x.x]});
            }
        }
    }
}
signed main(){
    cin >> n >> m >> xx;
    for(int i=1;i<=m;i++){
        int x,y;
        cin >> x >> y;
        v[x].push_back((node){y,1});//正向边
        v[y+n].push_back((node){x+n,1});//反向边
    }
    for(int i=1;i<=n;i++){
        v[i].push_back((node){i+n,xx});//换层
        v[i+n].push_back((node){i,xx});//换层
    }
    dijkstra(1);
    cout << min(dis[n],dis[n+n]);
    return 0;
}

```

---

## 作者：Moya_Rao (赞：2)

# 题目大意
给定一张有 $n$ 个点（分别编号为 $1 \sim n$）、$m$ 条边的有向图，现在我们要从点 $1$ 走到点 $n$。

每一秒可以执行下面两个步骤中的一个：
- 从当前位置出发，走一条从当前位置通往另外位置的边。需耗费 $1$ 的代价。
- 停留在当前位置，并且将所有边都反转。例如原本有一条 $u$ 到 $v$ 的边，现在变成了一条 $v$ 到 $u$ 的边。需耗费 $k$ 的代价。

在不考虑时间的情况下，请计算出从 $1$ 走到 $n$ 所需的最小代价。题目保证总有一种方案可以从 $1$ 走到 $n$。

$2 \le n \le 2 \times 10^5$，$2 \le m \le 2 \times 10^5$，$1 \le k \le 10^9$。

更加详细的题面请看[原题](https://atcoder.jp/contests/abc395/tasks/abc395_e)。

# 思路
这种题目呀，一看，就会联想到 BFS，对不？

如果我们不考虑反转所有边的那种操作，那此题就变成了一个完全没有难度的普通 BFS 了，不过需要注意的是，是有向图哟。相信这一步，大家都能够想到。

现在问题来了，反转所有边的那种操作，到底该怎么解决呢？

其实上很简单，简单想想就能知道，我们无论反转多少次，总只有两种情况的——一种是最正常的原图（之后称之为“正图”），另外一种就是反图。那么，我们就可以把那个用来存边的 `vector` 开两个，一个存正图，一个存反图。  
根据我的定义，那么 $g_{0,i}$ 存储的就是在正图下 $i$ 连向的所有点，$g_{1,i}$ 则存储了在反图下 $i$ 连向的所有点。容易发现，这两张图是反过来的，因此可以在读入的时候全部建好。

接下来呢？继续跑普通 BFS 呗！只要在队列的传参里加一个 $t$ 变量表示现在是正图还是反图就行了，然后遍历边的时候根据 $t$ 来遍历即可。不过要多添加一个反转边的操作。

做完了吗？当然没有！大家肯定都发现了——反转边的代价是 $k$，而正常走一步的代价只有 $1$！这样子，最普通的 BFS 可做不了了！那咋办？上优先队列！  
是的，弄一个优先队列 BFS 就可以了，额外写个比较函数，让它把代价小的放在前面就是啦。

可是，最终的答案既有可能是在正图下结束的，也有可能是在反图下结束的，而我们没办法很方便的存储下答案啊。怎么办？记忆化呗！我们开个二维的 $f$ 数组，其中 $f_{i,x}$ 表示从点 $1$ 走到点 $x$，并且图的结束状态为 $i$ （$i$ 只有可能是 $0$ 或 $1$）时，所需的最小代价。这样，我们在操作的时候，额外判断一下当前行为是否足够优，优才继续嘛。

那最终答案到底该是多少呢？肯定是 $\min(f_{0,n},f_{1,n})$ 嘛！这样，这道题目就做完咯。

不过要记得，$f$ 一开始要全部初始化成极大值，但要将 $f_{0,1}$ 的值赋成 $0$ 哟。

最后扯一嘴题外话（或者说是笑话）：我赛时将那个比较函数写反了，导致“堆优化”顺利化身为“堆劣化”，几乎一半的测试点都超时了。赛时没能找出问题来，就没过（导致最终等级分还掉了）。赛后几分钟内发现错误，修改并提交，过了。气了我一晚上。

# 代码
你们爱看的代码来咯！别说我的代码防抄袭，我把[提交记录](https://atcoder.jp/contests/abc395/submissions/63321626)都给你！当然代码还是要放上的咯。

由于我认为本题代码比较好理解，因此就没有添加注释了，结合着思路自己理解理解吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
struct node{long long x,t,c;};
bool operator < (const node &A, const node &B){
    return A.c > B.c ;
}
long long n,m,k,f[2][N];
vector<int> g[2][N];
priority_queue<node> q;
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        g[0][x].push_back(y);
        g[1][y].push_back(x);
    }
    q.push({1,0,0});
    memset(f,0x3f,sizeof(f));
    f[0][1]=0;
    while(!q.empty()){
        node pp=q.top();q.pop();
        if(f[1-pp.t][pp.x]>pp.c+k){
            f[1-pp.t][pp.x]=pp.c+k;
            q.push({pp.x,1-pp.t,pp.c+k});
        }
        for(int i=0;i<g[pp.t][pp.x].size();i++){
            int v=g[pp.t][pp.x][i];
            if(f[pp.t][v]>pp.c+1){
                f[pp.t][v]=pp.c+1;
                q.push({v,pp.t,pp.c+1});
            }
        }
    }
    cout<<min(f[0][n],f[1][n]);
    return 0;
}
```

如果本篇题解对你有帮助，请你留下一个小小的赞，万分感谢！

---

## 作者：xiaoshumiao (赞：2)

很明显是个最短路，关键在于如何建模。

考虑给每个点加一个维度 $type$，$type=0$ 表示正向图，$type=1$ 表示反向图。

在做 Dijkstra 时，每次先在当前 $type$ 所表示的图上扩展，然后尝试使用反转边的操作，即 $type \gets type \operatorname{xor} 1$，边权为 $X$。

具体代码实现见下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = 2e5 + 10;
int cnt, h[N][2];
long long d[N][2];
bool vis[N][2];
struct Edge
{
    int v, nxt;
} e[M << 1];
void add(int u, int v) { e[++cnt] = {v, h[u][0]}, h[u][0] = cnt, e[++cnt] = {u, h[v][1]}, h[v][1] = cnt; }
struct State
{
    int u, type;
    long long d;
    bool operator<(const State &a) const { return d > a.d; }
};
int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, m, x, u, v;
    cin >> n >> m >> x;
    while (m--)
        cin >> u >> v, add(u, v);
    priority_queue<State> pq;
    memset(d, 0x7f7f7f7f, sizeof(d)), d[1][0] = 0, pq.push({1, 0, d[1][0]});
    while (!pq.empty())
    {
        int u = pq.top().u, type = pq.top().type;
        pq.pop();
        if (vis[u][type])
            continue;
        vis[u][type] = true;
        for (int i = h[u][type]; i; i = e[i].nxt)
        {
            int v = e[i].v;
            if (d[v][type] > d[u][type] + 1)
                d[v][type] = d[u][type] + 1, pq.push({v, type, d[v][type]});
        }
        if (d[u][type ^ 1] > d[u][type] + x)
            d[u][type ^ 1] = d[u][type] + x, pq.push({u, type ^ 1, d[u][type ^ 1]});
    }
    cout << min(d[n][0], d[n][1]);
    return 0;
}
```

---

## 作者：SY_nzwmb83 (赞：1)

题意很简单，给出一个有向图，可以花费 $1$ 的价值沿着边的方向走一步，或花费 $x$ 的价值反转所有边的方向，求从 $1$ 号点走到 $n$ 号点的最小价值。

不难想到暴力拆点，把一个点拆成两层，一层建原图，一层建反图，同一个点的两层间建长为 $x$ 的双向边。最后跑一遍最短路就做完了。

建图的代码：


```cpp
for(int i=1;i<=m;i++)
{
    int u,v;
    cin>>u>>v;
    g[u].push_back({v,1});
    g[v+n].push_back({u+n,1});
}
for(int i=1;i<=n;i++)
{
    g[i].push_back({i+n,X});
    g[i+n].push_back({i,X});
}
```

---

## 作者：da_ke (赞：1)

> fyy 行驶在小溪上，路线可以看作有向图。每条边的边权为 $1$。
>
> 因为「逆水行舟，不进则退」，fyy 要么沿着边的方向前进，要么逆着边的方向前进。顺、逆之间的转换需要代价 $X$。
>
> fyy 想知道从 $1$ 到 $N$ 的最短代价是多少。

发现顺着和逆着似乎有着隔阂。这便是「层」。

- 将每个点 $i$ 拆成两个点 $i,i+N$。
  - 将 $(i,i+N),(i+N,i)$ 连接，边权皆为 $X$。
- 对于每个原来的边 $(u,v)$：
  - 连接 $(u,v)$ 和 $(v+N,u+N)$。这里体现顺、逆。

然后 Dijkstra 跑最短路即可。时间复杂度取决于 Dijkstra 的写法。

[代码](https://atcoder.jp/contests/abc395/submissions/63278948)

---

## 作者：Dream_poetry (赞：1)

### 思路：
显然最短路。

考虑在 dij 过程中额外存储一个状态 $op$，表示当前全局的边是否反转，$0$ 表示已经被反转。

另外，在用链式前向星存边的时候，记录一下它的状态为 $1$，并改为双向边，反边状态为 $0$。

首先不急着存边权，因为边权是会变的。

然后正常的跑 dij，这个过程中考虑：

若现在找出的这条边的状态，和我们从优先队列中取出 $op$ 一致，说明不需要反转，边权为 $1$。

否则需要反转，反转后还要再走过去，边权为 $X+1$。

按照这个思路跑 dij 即可。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long


int n,m,X;


struct node{
	int to,nex,tag;
}e[5000005];
int tot;
int he[5000005];

int ans[1000005][2];


inline void add(int x,int y,int tag){
	e[++tot].nex=he[x];
	e[tot].to=y;
	he[x]=tot;
	e[tot].tag=tag;
}

int vis[1000005][2];

inline void bfs(int s){
	priority_queue<pair<int,pair<int,int> > >q;
	q.push(make_pair(-X,make_pair(s,0)));
	q.push(make_pair(0,make_pair(s,1)));
	ans[s][1]=0;
	ans[s][0]=X;
	while (q.size()){
		int x=q.top().second.first;
		int flag=q.top().second.second;
		q.pop();
		if (vis[x][flag]) continue;
		vis[x][flag]=1;
		for (int i=he[x];i;i=e[i].nex){
			int v=e[i].to;
			int op=e[i].tag;
			int w=0;
			if (op==flag){
				w=1;
			}
			else{
				w=X+1;
			}
			if (ans[v][op]>ans[x][flag]+w){
				ans[v][op]=ans[x][flag]+w;
				q.push(make_pair(-ans[v][op],make_pair(v,op)));
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>X;
	for (int i=1;i<=n;i++){
		ans[i][0]=ans[i][1]=1e18;
	}
	for (int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		add(x,y,1);
		add(y,x,0);
	}
	bfs(1);
	cout<<min(ans[n][0],ans[n][1]);
	
	return 0;
}
```

---

## 作者：include13_fAKe (赞：1)

最短路基础练习题。

建 $2\times n$ 个点，新图的 $u$ 向 $v$ 连边，$v+n$ 向 $u+n$ 连边。边权均为 $1$。

改变方向可以看成在改变前和改变后的两个图中“横跳”。直接在 $u$ 和 $u+n$ 之间连双向的边权为 $x$ 的边即可。

跑堆优化 dijkstra，时间复杂度 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long 
#define mp(a,b) make_pair(a,b)
using namespace std;

const int N=5e5+5;
priority_queue<pair<int,int> > q;
int n,m;
vector<pair<int,int> > g[N];
int zdl[N];
signed main(){
	cin>>n>>m;
	int x;
	cin>>x;
	for(int i=1;i<=n;i++){
		g[i].push_back(mp(i+n,x)),g[i+n].push_back(mp(i,x));
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(mp(v,1)),g[v+n].push_back(mp(u+n,1));
	}
	memset(zdl,0x3f,sizeof(zdl));
	zdl[1]=0;
	q.push(mp(0,1));
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		for(int i=0;i<g[u].size();i++){
			int v=g[u][i].first;
			int w=g[u][i].second;
			if(zdl[v]>zdl[u]+w){
				zdl[v]=zdl[u]+w;
				q.push(mp(-zdl[v],v));
			}
		}
	}
	cout<<min(zdl[n],zdl[n*2])<<endl;
	return 0;
}
```

笑点解析：忘开 vp 被教练说了一顿。

---

## 作者：roumeideclown (赞：1)

### 题意简述

略。

### 解法分析

题目要求从顶点 $1$ 走到顶点 $n$ 的最小代价，那么很自然地想到最短路。

但是本题多了一个翻转所有边的操作，显然不能直接套板子。

注意到题目中图只有原图和翻转了之后的图两种状态，于是考虑分层图。其中一层为原图，另一层为翻转之后的图，边权均为 $1$；两层之间每个对应的顶点连一条无向边，权值为 $X$。

然后从顶点 $1$ 为起点跑最短路，答案为两层上顶点 $n$ 的距离的最小值。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using pii=pair<ll,int>;
#define fi first
#define se second
constexpr int N=2e5+5;
int n,m,k;
struct enode {
	int nxt,to;ll val;
} edge[1000005];
int tot,head[N*2];
void add(int u,int v,ll w) {
	edge[++tot].nxt=head[u];
	edge[tot].to=v;
	edge[tot].val=w;
	head[u]=tot;
}
ll dist[N*2];
bool vis[N*2];
priority_queue<pii,vector<pii>,greater<pii>> q;
void dijkstra(int s) {
	memset(dist,0x3f,sizeof(dist));
	q.push({dist[s]=0,s});
	while(!q.empty()) {
		int u=q.top().se;q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].nxt) {
			int v=edge[i].to;ll w=edge[i].val;
			if(dist[v]>dist[u]+w) q.push({dist[v]=dist[u]+w,v});
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	// 读入 & 建图，其中翻转图一层的顶点 u 编号为 n+u
	for(int i=1;i<=m;i++) {
		int u,v;cin>>u>>v;
		add(u,v,1);
		add(n+v,n+u,1);
	}
	for(int i=1;i<=n;i++) add(i,n+i,k),add(n+i,i,k);
	// 最短路
	dijkstra(1);
	cout<<min(dist[n],dist[2*n])<<"\n";
	return 0;
}

```

---

## 作者：__youzimo2014__ (赞：1)

简单的最短路。

首先，我们建图的时候要有一个正向图和一个反向图。

我们可以考虑给节点带上参数 $type$，表示当前的图是正向的还是反向的。

于是乎，这个问题就非常简单了。

每次遍历临边的时候，除了遍历现在所在的正/反向图，还需要尝试翻转这张图并往前走，代价为 $X + 1$。

完结撒花！

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
const int N = 2e5 + 5;
int n, m;
ll reversd_val; // 题目里面的 x 
vector<int> rev[N], forw[N]; // rev 是反向，forw是正向 
bool vis[N][2];
ll dis[N][2];
struct Nod {
    int x, type; // type = 0 是正向，type = 1 是反向 
	ll len;
    Nod(int x_, int type_, ll len_) {
        x = x_;
        type = type_;
        len = len_;
    }
};
bool operator>(Nod a, Nod b) {
	if (a.len != b.len) return a.len > b.len;
	if (a.x != b.x) return a.x > b.x;
	return a.type > b.type;
}
void dijkstra() {
	priority_queue<Nod, vector<Nod>, greater<Nod> > q;
	q.emplace(1, 0, 0);
	dis[1][0] = 0;
	while (!q.empty()) {
		Nod x = q.top(); q.pop();
		if (vis[x.x][x.type]) continue;
		vis[x.x][x.type] = true;
		if (x.type == 0) {
            for (auto v : forw[x.x]) {
                if (x.len + 1ll < dis[v][0]) {
                    q.emplace(v, 0, dis[v][0] = x.len + 1ll);
                }
            }
            for (auto v : rev[x.x]) {
                if (x.len + reversd_val + 1ll < dis[v][1]) {
                    q.emplace(v, 1, dis[v][1] = x.len + reversd_val + 1ll);
                }
            }
        } else {
            for (auto v : rev[x.x]) {
                if (x.len + 1ll < dis[v][1]) {
                    q.emplace(v, 1, dis[v][1] = x.len + 1ll);
                }
            }
            for (auto v : forw[x.x]) {
                if (x.len + reversd_val + 1ll < dis[v][0]) {
                    q.emplace(v, 0, dis[v][0] = x.len + reversd_val + 1ll);
                }
            }
        }
	}
}
int main () {
    memset(dis, 0xff, sizeof dis);
    ios::sync_with_stdio(false);
    cin >> n >> m >> reversd_val;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        forw[u].push_back(v);
        rev[v].push_back(u);
    }
    dijkstra();	
    cout << min(dis[n][0], dis[n][1]) << endl;
    return 0;
}
```

---

## 作者：哈哈人生 (赞：1)

![](https://cdn.luogu.com.cn/upload/image_hosting/gc4iz7iu.png)

六百六十六盐都不盐了。

但是还是要说明一下，我有通过记录的，在 AtCoder 上。

## 题意
给你一张有向图，你每次可以花费 $1$ 的代价走到相邻节点，或花费 $x$ 的代价将每条边方向反转，问从 $1$ 号点走到 $n$ 号点的最小花费。

## 思路
很显然得用分层图，而且想到分层图就做完了。将给定图再复制一遍，只不过全部边为反向，边权和原图一样都为 $1$，再将对应的点分别连一条权值为 $x$ 的双向边（因为反转操作可以多次）。因为 $x$ 非负，以 $1$ 为源点跑 Dijkstra 即可。注意，在第一层（相当于原图）和第二层（相当于反向图）中到达 $n$ 号点都是可以的，所以结果为二者取最小值。当然，跑两遍 BFS 应该也是可以的。

分层图要注意空间开多倍，大家不要像我这个小笨蛋一样吃罚时。

## 代码
$1$ 到 $n$ 号点是第一层，$n+1$ 到 $2\times n$ 号点是第二层。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,x,dis[400005];
bool vis[400005];
struct A{
	int to,w;
};
vector<A> v[400005];
struct B{
	int p,d;
};
bool operator <(B a,B b){
	return a.d>b.d;
}
priority_queue<B> q;
void dik(){
	for(int i=2;i<=n;i++)dis[i]=1e18;
	dis[1]=0;
	q.push({1,dis[1]});
	while(!q.empty()){
		int p=q.top().p;
		q.pop();
		if(vis[p])continue;
		vis[p]=1;
		for(int i=0;i<v[p].size();i++){
			int to=v[p][i].to,w=v[p][i].w;
			if(dis[to]>dis[p]+w){
				dis[to]=dis[p]+w;
				q.push({to,dis[to]});
			}
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>x;
	for(int i=1;i<=n;i++)v[i].push_back({i+n,x}),v[i+n].push_back({i,x});
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		v[a].push_back({b,1});
		v[b+n].push_back({a+n,1});
	}
	n*=2;
	dik();
	cout<<min(dis[n/2],dis[n]);
	return 0;
}
```

---

## 作者：Jayfeather2012 (赞：0)

本蒟蒻第一次 abc 场切 T5，写篇题解纪念一下。
## 思路
分层图~~   
不懂分层图的戳[这里](https://blog.csdn.net/m0_74315382/article/details/139370635)    
一般有神奇操作的题目都是可以用分层图解的。  
根据题目中将边反转方向的操作，我们建立两层图，第一层是原图，第二层是反图，再根据反转操作，将原图的每一个顶点连接一条终点为反图的此顶点，边权为 $x$ 的边，因为可以多次反转，反图的每一个顶点也要连接一条终点为原图的此顶点，边权为 $x$ 的边。  
看图或许更直观：  
以样例二为例：  
![](https://cdn.luogu.com.cn/upload/image_hosting/71eqdncl.png)
红边为反转操作，权值为 $x$。  
后缀为 $z$ 表示原图，为 $f$ 表示反图。  
最后跑一遍 Dijkstra 就好啦！  
具体细节看代码吧！
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
//注意要开 long long 
#define pp pair<int,int>
using namespace std;
int n,m,x,d[500005],v[500005];
vector<pp>a[500005];
//邻接表，1~n表示原图，n+1~n*2表示反图 
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>x;
	for(int i=1;i<=m;++i){
		int u,v;
		cin>>u>>v;
		a[u].emplace_back(make_pair(v,1));
		//原图建边 
		a[v+n].emplace_back(make_pair(u+n,1));
		//反图建边 
	}
	for(int i=1;i<=n;++i){
		a[i].emplace_back(make_pair(n+i,x));
		a[i+n].emplace_back(make_pair(i,x));
		//反转操作建边，权值为 x 
	}
	priority_queue<pp,vector<pp>,greater<pp>>q;
	q.push(make_pair(0,1));
	memset(d,0x3f,sizeof(d));
	d[1]=0;
	while(q.size()){
		int u=q.top().second;
		q.pop();
		if(v[u])continue;
		v[u]=1;
		for(auto t:a[u]){
			int v=t.first,w=t.second;
			if(d[v]>d[u]+w){
				d[v]=d[u]+w;
				q.push(make_pair(d[v],v));
			}
		}
	}
	//Dijkstra 
	cout<<min(d[n],d[n*2])<<"\n";
	//注意是取原图和反图到 n的最小值 
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

慢报：本作者赛时分层图写挂半小时。

对于这一类，我们可以搞一个虚拟的图，这张图里面的所有边全部反向建。

显然，两张图之间的“桥梁”的边权都是 $x$。

Dijkstra 跑一边即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define endl '\n'
const int N = 4e5 + 10;
const int inf = 1e16;
const int mod = 1e9 + 7;
int n,m,x;
int dis[N],vis[N];
struct edge{
	int v,w;
	bool operator < (const edge &a) const{
		return w > a.w;
	}
};
vector <edge> g[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void Dijkstra (int s){
	for (int i = 1 ; i <= n * 2 ; i++)
		dis[i] = inf;
	dis[s] = 0;
	priority_queue <edge> q; q.push((edge){s,0});
	while (!q.empty()){
		int u = q.top().v;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto e : g[u]){
			int v = e.v,w = e.w;
			if (dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				q.push((edge){v,dis[v]});
			}
		}
	}
}
signed main(){
	close();
	cin >> n >> m >> x;
	for (int i = 1 ; i <= m ; i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back((edge){v,1}); // 真图
		g[u].push_back((edge){u + n,x}); // 架“桥梁”
		g[u + n].push_back((edge){u,x}); // 既然有过去的边也要有回来的边
		g[v + n].push_back((edge){u + n,1}); // 虚拟图
		g[v].push_back((edge){v + n,x});
		g[v + n].push_back((edge){v,x}); 
	}
	Dijkstra(1);
	cout << min(dis[n],dis[n * 2]) << endl;
	return 0;
}
```

---

## 作者：lanthe0 (赞：0)

## 题意
给你一个**有向图**，所有边权为 $1$，在任意时刻可以进行一个花费为 $X$ 的操作使得所有边反转，问你从 $1$ 号点到 $n$ 号点的最小花费。
## 思路
很明显的最短路板子，在建图的时候建个分层图即可。具体来说就是将 $n$ 个点扩展到 $2n$ 个点，对于点 $a$ 在第二层就是点 $a+n$，每一层中点与点之间的边权为 $1$，而在不同层的同一个点之间建一条边权为 $X$ 的双向边。建图的时候在第一层先建一条 $u$ 到 $v$ 的边，再在第二层建一条反向边，最后跑一次 Dijkstra 即可。
最后要注意的就是开 long long。
## 代码
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <bitset>
using namespace std;
using ll = long long;
using PII = pair<ll,ll>;
const int N=2e5+10;

struct edge{
    ll to,w;
};
vector<edge> h[N*2];
int n,m,x;
ll dis[N*2];
bitset<N*2> st;//此处等效于一个bool数组

void dij(){
    memset(dis,0x3f,sizeof dis);
    dis[1]=0;
    priority_queue<PII,vector<PII>,greater<PII>> q;
    q.push({0,1});
    while(q.size())
    {
        auto t=q.top();
        q.pop();
        ll idx=t.second,d=t.first;
        //cout<<"idx::"<<idx<<" d::"<<d<<endl;
        if(st[idx]) continue;
        st[idx]=1;
        for(auto &par:h[idx]){
            int j=par.to,cost=par.w;
       
            if(dis[j]>d+cost){
                dis[j]=d+cost;
                q.push({dis[j],j});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>x;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        h[a].push_back({b,1});
        h[b+n].push_back({a+n,1});
    }
    for(int i=1;i<=n;i++)
        h[i].push_back({i+n,x}),
        h[i+n].push_back({i,x});
    dij();
    cout<<min(dis[n],dis[n+n])<<endl;//记得是输出俩层中的最小值
    return 0;
}

```

---

## 作者：Leo_hele (赞：0)

跳转题目：[ABC395-E](https://www.luogu.com.cn/problem/AT_abc395_e)
### 题目翻译
给一个有向图，每次可以进行两种操作
- 花费 $1$ 走过一条边；
- 花费 $X$ 反转所有边。

求从点 $1$ 走到点 $n$ 的最小花费。

---
### 思路
1. 建 $2$ 个图，一个正图，一个反图。在 $G_{1,i}$ 与 $G_2,i$ 间建一条权值为$X$的边。  
2. 然后跑 `Dijkstra`。  
3. 最后答案为 $\min(dis_{1,n},dis_{2,n})$。
时间复杂度为 $\mathcal{O}(n\log n)$。
---
### 代码
```cpp
#include<bits/stdc++.h>
#define _fo(i, l, cod, s, ...) for (int i = l; cod; i += s)
#define fo(...) _fo(__VA_ARGS__, 1)
#define _up(i, l, r, s, ...) _fo(i, l, i <= r, s)
#define up(...) _up(__VA_ARGS__, 1)
#define _dn(i, r, l, s, ...) _fo (i, r, i >= l, -(s))
#define dn(...) _dn(__VA_ARGS__, 1)
#define int long long
#define ull unsigned long long
#define addstr(s) s = " " + s
using namespace std;
const int N = 2e5+5;
int n, m, X;
vector<int> G1[N], G2[N]; // 正反图
int dis[N][2];
struct node{
	int u, v, s;
	bool operator<(const node& rhs) const{
		return v > rhs.v;
	}
};
priority_queue<node> q;
signed main(){
	cin >> n >> m >> X;
	while (m--){
		int u, v;
		cin >> u >> v;
        // 建图
		G1[u].push_back(v);
		G2[v].push_back(u);
	}
    // Dijkstra
	memset(dis, 0x3f, sizeof dis);
	dis[1][0] = 0;
	q.push({1, 0, 0});
	while (! q.empty()){
		node o = q.top(); q.pop();
		int u = o.u, d = o.v, s = o.s;
		if (d != dis[u][s]) continue;
		auto *g = (s ? G2 : G1);
        // 其他边
		for (auto v: g[u]){
			int nv = dis[u][s] + 1;
			if (dis[v][s] > nv)
				dis[v][s] = nv, q.push({v, nv, s});
		}
        // 跳转图的边
		int nv = dis[u][s] + X;
		if (dis[u][s^1] > nv)
			dis[u][s^1] = nv, q.push({u, nv, s^1});
	}
	cout << min(dis[n][0], dis[n][1]);
	return 0;
}

```

---

## 作者：zhangzheng2026 (赞：0)

设 $d_{i,0/1}$ 表示从 $1$ 走到 $i$ 当前图是否反转的最小花费。跑一遍最短路。

- 如果当前边为反边，将图反转，即第二维异或一，到该节点的代价为 $x+1$。
- 否则代价为 $1$。

答案即为 $\min(d_{n,0},d_{n,1})$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,p,h[N],cnt,vst[N][2],d[N][2];
struct node{int next,to,v;}a[N<<1];
priority_queue<pair<int,pair<int,int> > >pq;
void add(int x,int y,int v){a[++cnt].to=y,a[cnt].next=h[x],a[cnt].v=v,h[x]=cnt;}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>p,memset(d,0x3f,sizeof(d));
	for(int x,y,i=1;i<=m;i++) cin>>x>>y,add(x,y,1),add(y,x,0);
	pq.push({0,{1,0}}),d[1][0]=0;
	while(!pq.empty())
	{
		pair<int,pair<int,int> > x=pq.top();pq.pop();
		int y=x.second.first,z=x.second.second;
		if(vst[y][z]) continue;
		vst[y][z]=1;
		for(int i=h[y];i;i=a[i].next)
		{
			int k=a[i].to,v=a[i].v,w,s=z;
			if(v^x.second.second) w=1;
			else w=1+p,s^=1;
			if(d[k][s]>d[y][z]+w) d[k][s]=d[y][z]+w,pq.push({-d[k][s],{k,s}});
		}
	}
	cout<<min(d[n][0],d[n][1]);
	return 0;
}
```

---

## 作者：cyq32ent (赞：0)

最简单的 E 题。

建两个图，其中一个是本来的图 $G$，另一个是反向之后的图 $G'$。将图反向相当于从节点 $u$ 走到 $u'$ 或从 $u'$ 走到 $u$。然后就是最短路板子了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int foo=202503;
vector<pair<int,int> >G[foo*2+31];
int N,M,X,dis[foo*2+31];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >Q;
signed main(){
	memset(dis,0x3f,sizeof dis);
	cin>>N>>M>>X;
	for(int u,v;M--;){
		cin>>u>>v;
		G[u].push_back({v,1});
		G[foo+v].push_back({foo+u,1});
	}for(int u=1;u<=N;u++){
		G[u].push_back({foo+u,X});
		G[foo+u].push_back({u,X});
	}Q.push({0,1});dis[1]=0;
	while(Q.size()){
		auto [d,u]=Q.top();
		Q.pop();
		for(auto v:G[u]){
			if(dis[u]+v.second<dis[v.first])Q.push({dis[v.first]=dis[u]+v.second,v.first});
		}
	}
	cout<<min(dis[N],dis[N+foo]);
	return 0;
}
```

---

## 作者：Quartz_Blocks (赞：0)

## Solution of AT_abc395_e [ABC395E] Flip Edge

分层图~~模板~~练习好题。

题目意思：给定一个有向图，边权为 $1$，还可以用 $X$ 的花费翻转每一条边的方向。

分层图是什么？它可以被看作是多层的图，每层之间有某种关系连接，路径可以跨越每一层图。

注意到翻转每一条边的方向是翻转了整个图，可以再开辟第二层图直接存相反方向的边。而将翻转每一条边的方向就可以抽象为从当前点直接走向另外一层当中的这个点，边权为 $X$。

那么如何去处理这个分层图？

可以直接开两倍的空间，点 $1$ 到 $N$ 是原来的图，点 $N+1$ 到 $2 \times N$ 是第二层的图。

建边时可以按照如下操作处理：

- 对于 $1 \le i \le N$，对 $i$ 到 $i+N$ 添加双向边，权值为 $X$。
- 对于 $1 \le i \le M$，对 $u_i$ 到 $v_i$ 添加单向边，$v_i+N$ 到 $u_i+N$ 添加单向边。


然后发现可以直接跑最短路。我用的是 Dijkstra 单源最短路算法。

Code:

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 400010, M = 800010;
//hd[u]:以u为起点的最后一条边的边号 
int n, m, s, cnt, hd[N], d[N];
bool vis[N];
struct edge{
	//nxt：指向相同起点的上一条边的边号 
	int v, w, nxt;
}e[M];
struct node{
	int u, dis;
	//维护以dis为权值的小根堆 
	bool operator < (const node &a) const{
		return a.dis < dis;
	}
};
void addedge(int u, int v, int w)
{
//	cout << u << ' ' << v << ' ' << w << endl;
	e[++cnt] = edge{v, w, hd[u]};
	hd[u] = cnt; 
}
void djstl(int s)
{
	
	memset(d, -1, sizeof(d));
	
	
	priority_queue<node> q;
	q.push(node{s, 0});
	d[s] = 0;
	
	while(!q.empty())
	{
		//选取当前没有成为最优值的最优值
//		int u = -1;
//		for(int j = 1; j <= n; j++)
//		{
//			if(d[j] == -1 || vis[j]) continue;
//			if(u == -1 || d[u] > d[j]) u = j;
//		} 
		int u = q.top().u;
		q.pop();
		//为什么堆里会取出来一个之前已经成为最优值的点？？？ 
		if(vis[u]) continue;
		vis[u] = 1;
		
		for(int j = hd[u]; j; j = e[j].nxt)
		{
			int v = e[j].v, w = e[j].w;
			if(d[v] == -1 || d[v] > d[u] + w)
				d[v] = d[u] + w, q.push(node{v, d[v]});
		}
	}
}
//i 当前点 i+n 反边的当前点
int x;
signed main(){
	cin >> n >> m >> x;
	for(int i = 1, u, v;i <= m; i++){
		cin >> u >> v;
		addedge(u, v, 1);//正常的图
		addedge(v+n,u+n,1);//反向的图
	}
	for(int i = 1;i <= n;i++) addedge(i,i+n,x),addedge(i+n,i,x);//连接正图和反图
	
	djstl(1);
//	for(int i = 1;i <= n*2;i++) cout << d[i] << ' ';
	cout << (long long)(min((d[n] != -1 ? d[n] : 1e9),(d[n+n] != -1 ? d[2*n] : 1e9))) << endl;
	
	return 0;
}
```

---

## 作者：ANDER_ (赞：0)

#### 考察：Dijistra，图上 DP。 
### 题意

给定有向图 $G=(V,E)$，顶点 $1$ 为起点，顶点 $N$ 为终点。允许以下两种操作：

- **沿边移动**：从当前顶点 $u$ 通过边 $u \to v$ 移动，代价为 $1$。

- **反转所有边**：将图中所有边方向反转，代价为 $X$。

求出从 $1$ 通过操作移动到 $N$ 的最小代价。
### 数据范围

-   $2 \leq N \leq 2 \times 10^5$
-   $1 \leq M \leq 2 \times 10^5$
-   $1 \leq X \leq 10^9$
-   $1 \leq u _ i \leq N \ (1 \leq i \leq M)$
-   $1 \leq v _ i \leq N \ (1 \leq i \leq M)$
-   对于给定的图，保证可以通过描述的操作从顶点 $1$ 到顶点 $N$ 可以到达。
-   所有输入值均为整数。
### 思路
这道题需要思考 Dijistra 的实现正确性是怎么得出以及实现的本质。

钦定 $dp_{k,v}$ 表示在状态 $k$ 下到达顶点 $v$ 的最小成本，有：
$$
dp_{k,v} = \min \begin{cases}
dp_{k,u} + 1 & \text{move 1} \\
dp_{1-k,u} + X & \text{move 2}
\end{cases}
$$

实现是容易的，对于题目中给定的每条边 $(u,v)$，令 $edge_{0,u} = v,egde_{1,v} = u$。后考虑对 Dijistra 拓展，先初始化 $dp_{0,1} = 0$，优先队列维护三元组 $(cost, v, k)$，并每次取出队列中最小 $cost$ 的状态进行扩展。

于是我们在时间复杂度 $\Theta(M + N \log_2 N)$ 的时间复杂度内解决了这道题目，[赛时代码](https://atcoder.jp/contests/abc395/submissions/63288512)。

---

## 作者：hjyowl (赞：0)

### 思路

由于可以反转每条边，所以说，我们考虑使用分层图解决。

对于 $a$，$b$ 这两个点，首先在实层上从 $a$ 到 $b$ 连接一条权值为 $1$ 的边，然后再在虚层上面建立反边。

接下来，我们再对于每一个 $i$，从实层的 $i$ 到虚层的 $i$ 连一条长度为 $k$ 的边，这里就是题目反转所有边的代价。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 1000010;
long long h[N],e[N * 10],ne[N * 10],w[N * 10],idx = 0;
void add(long long a,long long b,long long c){
	e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx ++ ;
}
long long dist[N]; 
bool st[N];
typedef pair<long long,long long> PII;
void dijkstra(long long S){
	memset(dist,0x3f,sizeof dist);
	memset(st,0,sizeof st);
	dist[S] = 0;
	priority_queue<PII,vector<PII>,greater<PII> >q;
	q.push({0,S});
	while (q.size()){
		auto t = q.top();
		q.pop();
		long long ver = t.second;
		if (st[ver]){
			continue;
		}
		st[ver] = 1;
		for (long long i = h[ver]; ~i; i = ne[i]){
			long long j = e[i];
			if (dist[j] > dist[ver] + w[i]){
				dist[j] = dist[ver] + w[i];
				q.push({dist[j],j});
			}
		}
	}
}
int main(){
	memset(h,-1,sizeof h);
	long long n,m,k;
	cin >> n >> m >> k;
	long long S = 1,T = n;
	while (m -- ){
		long long a,b,c;
		cin >> a >> b;
		add(a,b,1);
		add(b + n,a + n,1);
		add(a,a + n,k);
		add(b,b + n,k);
		add(a + n,a,k);
		add(b + n,b,k);
	}
	dijkstra(S);
	cout << min(dist[T],dist[n + T]);
	return 0;
}
```

---

## 作者：lfxxx_ (赞：0)

我们考虑建分层图，第一层的图表示原来的图，第二层是反图。

我们先考虑同一层节点的连边，对于一条边 $(u,v)$，我们建一条 $u$ 指向 $v$ 的，边权为 $1$ 的边，同时建一条 $v+n$ 指向 $u+n$，边权为 $1$ 的边。

然后考虑不同层数节点的连边，容易观察到第一层到第二层或者第二层到第一层就是反转这个图，故我们建一条 $u$ 指向 $u+n$，边权为 $X$ 的边，$u+n$ 也向 $u$ 建一条边权为 $X$ 的边。

我们从节点 $1$ 跑一遍最短路，记 $1$ 到 $i$ 的距离为 $dis_i$，则答案就是 $\min(dis_n,dis_{n+n})$。

时间复杂度：$O(M \log N)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
vector<pair<int,int> >edge[N];
int dis[N],vis[N];
void dijkstra(int s)
{
    memset(dis,0x3f,sizeof dis);
    memset(vis,0,sizeof vis);
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
    q.emplace(0,s);
    dis[s]=0;
    while(!q.empty())
    {
        int u=q.top().second;q.pop();
        if(vis[u])
            continue;
        vis[u]=1;
        for(auto &[v,w]:edge[u])
        {
            if(dis[u]+w<dis[v])
            {
                dis[v]=dis[u]+w;
                q.emplace(dis[v],v);
            }
        }
    }
}
signed main()
{
    int n,m,w;
    cin>>n>>m>>w;
    for(int i=1;i<=m;++i)
    {
        int u,v;
        cin>>u>>v;
        edge[u].emplace_back(v,1);
        edge[v+n].emplace_back(u+n,1);
    }
    for(int i=1;i<=n;++i)
    {
        edge[i].emplace_back(i+n,w);
        edge[i+n].emplace_back(i,w);
    }
    dijkstra(1);
    cout<<min(dis[n],dis[n<<1]);   
}
```

---

