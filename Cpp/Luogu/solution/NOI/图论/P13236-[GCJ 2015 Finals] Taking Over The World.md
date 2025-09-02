# [GCJ 2015 Finals] Taking Over The World

## 题目描述

你和你的朋友 Pinky 有一个征服世界的计划。但首先，你们需要关闭一个秘密武器。

这个武器被藏在一个错综复杂的迷宫（一个图）中，只有一个入口。Pinky 将会在有秘密武器的房间（顶点）里关闭它。与此同时，安全小队会在图的入口处被警报唤醒，并试图穿过图去阻止 Pinky。你要尽可能拖慢安全小队的速度，为 Pinky 争取时间。通过任意一条边都需要 1 个时间单位，但你还可以“阻碍”最多 $K$ 个顶点。每经过一个被阻碍的顶点，需要额外花费 1 个时间单位。你需要选择一组顶点进行阻碍，使得安全小队到达秘密武器房间所需的时间尽可能长。

安全小队会从图的入口出发，目标是到达秘密武器房间。你需要在安全小队开始行动前就决定所有要阻碍的顶点，且安全小队会知道你阻碍了哪些顶点，并会选择最优路径。

阻碍秘密武器房间没有意义，因为当安全小队到达那里时，Pinky 已经被抓住，无法再拖延时间。另一方面，阻碍入口显然是一个好主意。

## 说明/提示

**数据范围**

- $1 \leq T \leq 100$。
- $2 \leq N \leq 100$。
- $1 \leq M \leq N \times (N - 1) / 2$。
- $1 \leq K \leq N$。
- 保证从房间 0 到房间 $N-1$ 总是存在一条路径。

**小数据集（7 分）**

- 时间限制：5 秒。
- 使用给定的 $K$，安全小队最多只能被延迟 2 个时间单位（相较于最短未阻碍路径）。

**大数据集（29 分）**

- 时间限制：10 秒。
- 无额外限制。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
3 2 1
0 1
1 2
3 2 2
0 1
1 2
3 2 3
0 1
1 2
4 4 2
0 1
0 2
1 3
2 3
7 11 3
0 1
0 2
0 3
1 4
1 5
2 4
2 5
3 4
3 5
4 6
5 6```

### 输出

```
Case #1: 3
Case #2: 4
Case #3: 4
Case #4: 3
Case #5: 5```

# 题解

## 作者：Gszfzsf (赞：1)

# P13236 Taking Over The World 题解

## 前言：

这是一道“最短路”加“网络流”思维好题

## 题目大意：

给定 $n$ 个节点，$m$ 条边，要求放置 $k$ 个关键点，每个关键点会使经过节点的时间增加 $1$。现求最优情况下，从节点 $0$ 到节点 $n-1$ 的最短路径最长值，有多组数据。

## 样例分析：

这是题目样例的第 $5$ 组数据，关键点已在图中已经标出。

![](https://cdn.luogu.com.cn/upload/image_hosting/9g6w74rr.png)\
不难发现，阻碍节点 $0,4,5$ 号节点是最优的，此时最少经历两个障碍，最短时间为 $5$。

## 解题思路：

### 思路分析：

阻碍顶点的选择可以视为一种“资源分配”。

观察一下样例，**首先有一个很显然的特性：**

- 只有堵住所有的最短路径，让安全小队无论如何也绕不开障碍物，才对答案有所贡献，就像一堵墙一样。

- 反证：考虑如果安全小队绕开了仍可以走最短路，我们放的障碍就成了“马奇诺防线”，不会对答案产生贡献。

那么，以**最小花费堵住所有最短路径**，相当于求**切割最短径的最小花费**，和网络流的**最小割**是不是很像呢？

因此，我们在**最短路径上建出网络流图**，跑网络最大流，**求得的最小割就是这一次切割所需的障碍数**。

而每放一轮障碍切割完最短路径，都要**开始新的一回合**，重新跑最短路建立网络流，因为障碍使得最短路可能被更新了。

### 具体实现：

**思路很清晰了，下面讲讲具体怎么实现。**

***定义***：

- $Cut$ 为最小割。

- $Key_i$ 为第 $i$ 号点是否放障碍。

- $ds_i$ 和 $dt_i$ 分别为从起始点和结束点开始到第 $i$ 号点的最短路。

***对于每一次循环：***

**首先**：在原图上，分别从起始点和结束点开始，算上 $Key$ 标记跑最短路（求最短路）。

此时对于两个直接相连接的点 $i,j$，如果 $ds_i+dt_j=ds_{n-1}$，那么 $(i,j)$ 就一定在最短路上。

我们需要在流网络中强制包含这些边，从而确保阻碍顶点时能正确切断这些最短路径。

**其次**：将每个原始顶点拆分为“入点”和“出点”，并在它们之间建立边，这样可以表示阻碍该顶点的代价，其中的流量为 $1$ 表示可割，为 $\infty$ 表示不可割（建网络流）。

具体地（敲黑板）：

- 对于内部边 $(id_{int},id_{out})$：
  - $id_{in} \overset{1}{\longrightarrow} id_{out}$ （如果 $id$ 未被阻碍）。
  - $id_{in} \overset{\infty}{\longrightarrow} id_{out}$ （如果 $id$ 已被阻碍）。
- 对于外部每条边 $(u,v)$：
  - $u_{out} \overset{\infty}{\longrightarrow} v_{in}$。
  - $v_{in} \overset{0}{\longrightarrow} u_{out}$。

**随后**：跑网络最大流，即最小割 $Cut$，说明我们需要 $Cut$ 个障碍来阻碍安全小队（跑最小割）。

**最后**：如果 $Cut>k$ 则直接退出循环输出当前的最小距离。 否则我们用 $k$ 减去 $Cut$，标记出这次阻碍的点，开启下一次循环，直到无法继续阻碍。

具体地（划重点）：

- 如果 $dis_{id_{in}}\neq \infty$ 且 $dis_{id_{out}}=\infty$ 那么该点被割，即应该阻碍该点，打标记。
- 因为这意味着：
  - 从源点到 $id_{in}$ 有路径。
  - 但从 $id_{in}$ 无法到达 $id_{out}$（因为 $id_{in}\rightarrow id_{out}$ 被切断）。

**均摊时间复杂度：$O(TNMK)$。**

**空间复杂度：$O(N^2)$。**

Dinic 一般跑不满，复杂度非常的优秀！

## 代码：

码风丑陋，大佬们看个思路就行。

```c++
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 507;
int T, n, m, k;
int Key[N];	 // 关键点标记
int now[N];	 // 当前弧
int dis[N];	 // 网络流求路径
int Link[N], l = 1;
struct edge {
	int y, v, nxt;
} Edge[N * N << 1];
vector<int> V[N];  // 原图在这里

inline int Get(int id, bool flag) { return (id << 1) + ((flag) ? 1 : 0); }
// 求节点对应的分层图节点，false和true分别对应入点和出点

inline void Insert(int x, int y, int v) {
	l++;
	Edge[l].nxt = Link[x];
	Link[x] = l;
	Edge[l].y = y;
	Edge[l].v = v;
}  // 因为要跑网络流，vector存图不方便求反边，采用链式前向星

// 最短路部分
vector<int> Dijkstra(int s) {
	// 通过堆优化Dijkstra跑最短路，并且把数组传回solve函数
	vector<int> Dis(n + 7, INF);  // 这里大写Dis是防止和网络流的dis冲突
	vector<bool> vis(n + 7, false);
	priority_queue<pair<int, int>, vector<pair<int, int> >,
				   greater<pair<int, int> > >
		Q;
	Dis[s] = Key[s];
	Q.push({Dis[s], s});
	while (Q.empty() != true) {
		int dq = Q.top().second;
		Q.pop();
		if (vis[dq]) continue;
		vis[dq] = true;
		for (int yy : V[dq]) {
			if (Dis[yy] > Dis[dq] + Key[yy] + 1) {
				Dis[yy] = Dis[dq] + Key[yy] + 1;
				Q.push({Dis[yy], yy});
			}
		}
	}
	return Dis;
	// 直接传回数组，简单方便
}

// 网络流部分
bool BFS(int S, int T) {  // 寻找增广路
	for (int i = 0; i <= (n << 1); i++) dis[i] = INF;
	queue<int> Q;
	Q.push(S);
	dis[S] = 0;
	now[S] = Link[S];
	while (Q.empty() != true) {
		int dq = Q.front();
		Q.pop();
		for (int i = Link[dq]; i; i = Edge[i].nxt) {
			int yy = Edge[i].y;
			if (Edge[i].v > 0 && dis[yy] == INF) {
				Q.push(yy);
				now[yy] = Link[yy];
				dis[yy] = dis[dq] + 1;
				if (yy == T) return true;
			}
		}
	}
	return false;
}
int DFS(int dq, int T, int sum) {
	if (dq == T) return sum;
	int k, res = 0;
	for (int i = now[dq]; i && sum; i = Edge[i].nxt) {	// 剩余容量优化
		int yy = Edge[i].y;
		now[dq] = i;  // 当前弧优化
		if (Edge[i].v > 0 && dis[yy] == dis[dq] + 1) {
			k = DFS(yy, T, min(sum, Edge[i].v));
			if (k == 0) dis[yy] = INF;
			Edge[i].v -= k;
			sum -= k;
			Edge[i ^ 1].v += k;
			res += k;
		}
	}
	return res;
}
int Dinic(int S, int T) {
	int ans = 0;
	while (BFS(S, T)) ans += DFS(S, T, INF);
	return ans;
}

void solve(int id) {
	cin >> n >> m >> k;
	memset(Key, 0, sizeof(Key));
	for (int i = 0; i < n; i++) V[i].clear();
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		V[x].push_back(y);
		V[y].push_back(x);
	}  // 原始图用来跑最短路
	while (k > 0) {
		int S = Get(0, false);
		int T = Get(n - 1, false);
		// 链式前向星从奇数开始，因为要通过异或求反边
		memset(Link, 0, sizeof(Link));
		l = 1;
		for (int i = 0; i < n; i++) {
			// 入点到出点，INF为不可割，可割容量为1
			Insert(Get(i, false), Get(i, true), ((Key[i]) ? INF : 1));
			// 记得存反向边
			Insert(Get(i, true), Get(i, false), 0);
		}
		vector<int> ds = Dijkstra(0);
		vector<int> dt = Dijkstra(n - 1);
		for (int i = 0; i < n; i++) {
			for (int j : V[i]) {
				// 存在于最短路径上的边
				if (ds[i] + dt[j] + 1 == ds[n - 1]) {
					Insert(Get(i, true), Get(j, false), INF);
					Insert(Get(j, false), Get(i, true), 0);
				}
			}
		}
		int Cut = Dinic(S, T);
		if (Cut <= k) {
			k -= Cut;
			for (int i = 0; i < n; i++)
				if (dis[Get(i, false)] != INF && dis[Get(i, true)] == INF) //在最小割上
                    if (!Key[i]) Key[i] = 1;  // 没被割过
		} else
			break;
	}
	cout << "Case #" << id << ": " << Dijkstra(0)[n - 1] << '\n';
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;  // 多测要清空
	for (int id = 1; id <= T; id++) solve(id);
	return 0;
}
```

**好了，到此结束了（逃**

---

