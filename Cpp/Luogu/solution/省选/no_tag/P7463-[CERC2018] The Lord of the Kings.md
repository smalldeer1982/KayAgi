# [CERC2018] The Lord of the Kings

## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [The Lord of the Kings](https://contest.felk.cvut.cz/18cerc/solved/king.pdf)**

在多年与海外国家的战争后，我们的国家终于成功去除了大多数反动势力和敌人。如此光辉的胜利应该被长时间记住并庆祝。因此，我们的国王宣布将胜利日这一天定为一个公共节日，并且要举行胜利游行。在游行中，军队会跟着国王从他的宫殿出发，访问国家里的每个城市。

国王和他的随从将一种环保的电动直升机作为交通工具。这种直升机有一个缺点，就是它的航程较短。国王让你和你的顾问在一些农场和所有城市中修建停机坪，使得从他的宫殿出发，经过一些停机坪后都可以到达任何城市。然而，建停机坪和基础设施都很费钱。所以要最小化最小化停机坪的修建数量。

此外，由于直升机特殊的设计，国王和他的士兵需要以特殊的方式移动，这就会影响停机坪的数量和位置。

给你一张这个国家的矩形网格地图，其中包含代表村庄，城市和宫殿的网格。同时，也给你了直升机的移动方式——与国际象棋中「车（Rook）」、「后（Queen）」、「象（Bishop）」、「马（Knight）」或「王（King）」之一的移动方式一样（每种棋子的详细移动方式见「数据范围与提示」）。你的任务是求出最少需要在多少农场或城市修停机坪才能够满足国王的需求。国王的宫殿中已经修建了停机坪，因此不需要修一个新的了。

## 说明/提示

$1 ≤ N, M ≤ 15,1 ≤ T ≤ 10, 1 ≤ X ,W ≤ N,1≤Y, Z≤M$

下图为直升机的运输方式（同国际象棋对应棋子的行棋规则）：
![#1](https://cdn.luogu.com.cn/upload/image_hosting/ip5cnfsa.png)

## 样例 #1

### 输入

```
3 3
3 1 K
2
1 1
1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
3 1 Q
2
1 1
1 3```

### 输出

```
2```

## 样例 #3

### 输入

```
5 5
4 4 R
4
1 2
2 1
2 5
5 1```

### 输出

```
6```

# 题解

## 作者：xuyifei0302 (赞：1)

读完题，我们看见“特殊点”、“最小代价”、以及那极小的数据范围，可以很轻松地想到是最小斯坦纳树。

先给出最小斯坦纳树的板子的转移：


```cpp
for (int i = 0; i < k; i ++) {
		int x, y;
		cin >> x >> y;
		dp[point(x, y)][1 << i] = 0;
	}
	for (int i = 0; i < (1 << k); i ++) {
		for (int j = 1; j <= n * m; j ++) {
			for (int k1 = i; k1 >= 0; k1 --) {
				if ((i | k1) == i) {
					dp[j][i] = min(dp[j][i], dp[j][k1] + dp[j][i - k1]);
				}
			}
			if (dp[j][i] < INF) {
				pq.push({j, dp[j][i]});
			}
		}
		dj(i);
	}
```


难点在于建图，我们要按照每一种棋子的运动方式建图，模拟即可。

- 对于皇后，我们对于某一个格子斜方向所能到达的所有格子都建一条边，竖直方向所能到达的所有格子都建一条边，水平方向所能到达的所有格子都建一条边。

- 对于车，我们对于竖直方向所能到达的所有格子都建一条边，水平方向所能到达的所有格子都建一条边。

- 对于相，我们对于某一个格子斜方向所能到达的所有格子都建一条边。

- 对于马，我们对于某一个格子马的所有运动方向所能到达的所有格子都建一条边。

但细节很多，详见代码。

下面是代码环节：


```cpp#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;
struct Node {
	int u, dis;
	Node (int u_, int dis_) {
		u = u_, dis = dis_;
	}
};
bool operator < (Node x, Node y) {
	return x.dis > y.dis;
}
int n, m, X, Y, k, dp[400][(1 << 10)];
char ch;
vector<int> v[400];
priority_queue<Node> pq;
int point(int x, int y) {
	return (x - 1) * m + y;
}
void dj(int s) {
	while (!pq.empty()) {
		int u = pq.top().u, dis = pq.top().dis;
		pq.pop();
		if (dp[u][s] < dis) {
			continue;
		}
		for (auto i : v[u]) {
			if (dp[i][s] > dp[u][s] + 1) {
				dp[i][s] = dp[u][s] + 1;
				pq.push({i, dp[i][s]});
			}
		}
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> X >> Y >> ch >> k;
//	cout << "Ok\n";
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
//			cout << i << " " << j << "k\n";
			if (ch == 'N') {
				if (i > 1 && j > 2)	{
					v[point(i, j)].push_back(point(i - 1, j - 2));
				}
				if (i > 1 && j + 1 < m)	{
					v[point(i, j)].push_back(point(i - 1, j + 2));
				}
				if (i < n && j > 2)	{
					v[point(i, j)].push_back(point(i + 1, j - 2));
				}
				if (i < n && j + 1 < m)	{
					v[point(i, j)].push_back(point(i + 1, j + 2));
				}
				if (j > 1 && i > 2)	{
					v[point(i, j)].push_back(point(i - 2, j - 1));
				}
				if (j > 1 && i + 1 < n)	{
					v[point(i, j)].push_back(point(i + 2, j - 1));
				}
				if (j < m && i > 2)	{
					v[point(i, j)].push_back(point(i - 2, j + 1));
				}
				if (j < m && i + 1 < n)	{
					v[point(i, j)].push_back(point(i + 2, j + 1));
				}
			} else if (ch == 'K') {
				if (i > 1)	{
					v[point(i, j)].push_back(point(i - 1, j));
				}
				if (j > 1)	{
					v[point(i, j)].push_back(point(i, j - 1));
				}
				if (i < n)	{
					v[point(i, j)].push_back(point(i + 1, j));
				}
				if (j < m)	{
					v[point(i, j)].push_back(point(i, j + 1));
				}
				if (i > 1 && j > 1)	{
					v[point(i, j)].push_back(point(i - 1, j - 1));
				}
				if (i > 1 && j < m)	{
					v[point(i, j)].push_back(point(i - 1, j + 1));
				}
				if (i < n && j > 1)	{
					v[point(i, j)].push_back(point(i + 1, j - 1));
				}
				if (i < n && j < m)	{
					v[point(i, j)].push_back(point(i + 1, j + 1));
				}
			} else if (ch == 'R') {
				for (int k1 = 1; k1 <= n; k1 ++) {
					if (k1 != i) {
						v[point(i, j)].push_back(point(k1, j));
					}
				}
				for (int k1 = 1; k1 <= m; k1 ++) {
					if (k1 != j) {
						v[point(i, j)].push_back(point(i, k1));
					}
				}
			} else if (ch == 'B') {
				for (int xx = i - 1, yy = j - 1; xx && yy; xx --, yy --) {
					v[point(i, j)].push_back(point(xx, yy));
				}
				for (int xx = i - 1, yy = j + 1; xx && yy <= m; xx --, yy ++) {
					v[point(i, j)].push_back(point(xx, yy));
				}
				for (int xx = i + 1, yy = j - 1; xx <= n && yy; xx ++, yy --) {
					v[point(i, j)].push_back(point(xx, yy));
				}
				for (int xx = i + 1, yy = j + 1; xx <= n && yy <= m; xx ++, yy ++) {
					v[point(i, j)].push_back(point(xx, yy));
				}
			} else if (ch == 'Q') {
				for (int k1 = 1; k1 <= n; k1 ++) {
					if (k1 != i) {
						v[point(i, j)].push_back(point(k1, j));
					}
				}
				for (int k1 = 1; k1 <= m; k1 ++) {
					if (k1 != j) {
						v[point(i, j)].push_back(point(i, k1));
					}
				}
				for (int xx = i - 1, yy = j - 1; xx && yy; xx --, yy --) {
					v[point(i, j)].push_back(point(xx, yy));
				}
				for (int xx = i - 1, yy = j + 1; xx && yy <= m; xx --, yy ++) {
					v[point(i, j)].push_back(point(xx, yy));
				}
				for (int xx = i + 1, yy = j - 1; xx <= n && yy; xx ++, yy --) {
					v[point(i, j)].push_back(point(xx, yy));
				}
				for (int xx = i + 1, yy = j + 1; xx <= n && yy <= m; xx ++, yy ++) {
					v[point(i, j)].push_back(point(xx, yy));
				}
			}
		}
	}
//	cout << "ok\n";
	for (int i = 1; i <= n * m; i ++) {
		for (int j = 0; j < (1 << k); j ++) {
			dp[i][j] = INF;
		}
	}
//	cout << "Ok";
//	for (int i = 1; i <= n * m; i ++) {
//		for (int j = 0; j < (1 << k); j ++) {
//			cout << dp[i][j] << " ";
//		}
//		cout << "\n";
//	}
	if (dp[point(X, Y)][(1 << k) - 1] == INF) {
		cout << "-1";
	} else {
		cout << dp[point(X, Y)][(1 << k) - 1];
	}
	return 0;
}
/*
3 3
3 1 K
2
1 1
1 3
1000000000 0 2 2
1000000000 1 1 2
1000000000 2 0 2
1000000000 1 2 3
1000000000 1 1 2
1000000000 2 1 3
1000000000 2 2 3
1000000000 2 2 3
1000000000 2 2 3

15 15 4 13 K 10 12 7 10 14 1 10 6 3 8 3 11 9 14 13 3 2 6 11 7 11
*/
```

---

## 作者：Walrus (赞：1)

## Problem

有一个 $n\times m$ 的网格，有一个人在这个网格图上乱跳，有很多种跳的方式，具体看题面，是国际象棋中一些棋子的走法。

其中有 $k$ 个点是关键点，这个人的初始位置在 $(x,y)$，问你这个人从初始位置跳到所有关键点**所经过的格子的总数最少是多少（包括关键点）。**

## Solution

斯坦纳树，注意到棋子的走法与题目几乎无关，只会影响建图。

还有一个，这个题是点权，不是边权，在一些其它的东西也会用到点权边权互相转化的 trick，比如树剖。

在斯坦纳树中将点权转为边权在转移时体现，如下：

```cpp
for(int S2 = S1 & S1 - 1; S2; S2 = S2 - 1 & S1) f[i][S1] = min(f[i][S1], f[i][S2] + f[i][S1 ^ S2] - 1);
```

当然 spfa 时就无需额外进行任何操作。

注意答案并不是 $\min\limits_{\forall u\in S} f_{u,(1<<k)-1}$，而是 $f_{id_{x,y},(1<<k)-1}$，$id(x,y)$ 是点 $(x,y)$ 转化为一维后的下标，$S$ 是关键点集合。

建图，其余是板子：
```cpp
const int Kingdx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int Kingdy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
const int Knightdx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
const int Knightdy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };

//上面拿的别人的

void add_edge(char id) {
	if(id == 'N') {
		rep(i, 1, n) {
			rep(j, 1, m) {
				rep(pp, 0, 7) {
					int x = i + Knightdx[pp], y = j + Knightdy[pp];
					if(x < 1 || x > n || y < 1 || y > m) continue;
					e[H(i, j)].pb(H(x, y));
				}
			}
		}
	}
	if(id == 'K') {
		rep(i, 1, n) {
			rep(j, 1, m) {
				rep(pp, 0, 7) {
					int x = i + Kingdx[pp], y = j + Kingdy[pp];
					if(x < 1 || x > n || y < 1 || y > m) continue;
					e[H(i, j)].pb(H(x, y));
				}
			}
		}
	}
	if(id == 'R') {
		rep(i, 1, n) {
			rep(j, 1, m) {
				rep(pp, 1, n) if(pp != i) e[H(i, j)].pb(H(pp, j));
				rep(pp, 1, m) if(pp != j) e[H(i, j)].pb(H(i, pp));
			}
		}
	}
	if(id == 'B') {
		rep(i, 1, n) {
			rep(j, 1, m) {
				rep(l, 1, n) rep(r, 1, m) if(i + j == l + r || i - j == l - r) e[H(i, j)].pb(H(l, r));
			}
		}
	}
	if(id == 'Q') {
		rep(i, 1, n) {
			rep(j, 1, m) {
				rep(pp, 1, n) if(pp != i) e[H(i, j)].pb(H(pp, j));
				rep(pp, 1, m) if(pp != j) e[H(i, j)].pb(H(i, pp));
			}
		}
		rep(i, 1, n) {
			rep(j, 1, m) {
				rep(l, 1, n) rep(r, 1, m) if(i + j == l + r || i - j == l - r) e[H(i, j)].pb(H(l, r));
			}
		}
	}
}
```

[code](https://www.luogu.me/paste/nujo6hq8)

---

## 作者：PineappleSummer (赞：1)

[P7463 [CERC2018] The Lord of the Kings](https://www.luogu.com.cn/problem/P7463)

前置知识：[最小斯坦纳树](https://www.luogu.com.cn/article/oy261ksx)。在此不做赘述。

题意看似复杂，其实就是建完图后跑一个最小斯坦纳树，答案即为 $\min\limits _{1}^{n\times m}f_{i,2^k-1}$。

难点在于建图，这里给出一个 $O(n^4)$ 的建图方法。

```cpp
// 将二维转一维，方便状态转移
int get (int x, int y) { return (x - 1) * m + y; }
void add (int x, int y) {
	G[x].emplace_back (y);
}
const int Kingdx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int Kingdy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int Knightdx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int Knightdy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
```
```cpp
for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++) {
		if (type == 'R') { // 车
			for (int x = 1; x <= n; x++)
				for (int y = 1; y <= m; y++)
					if ((x == i && y != j) || (x != i && y == j)) // 同一列或同一行
						add (get (i, j), get (x, y));
		}
		else if (type == 'Q') { // 后
			for (int x = 1; x <= n; x++)
				for (int y = 1; y <= m; y++)
					if ((x != i || y != j) && (x == i || y == j || x + y == i + j || x - y == i - j))
						add (get (i, j), get (x, y));
		}
		else if (type == 'B') { // 象
			for (int x = 1; x <= n; x++)
				for (int y = 1; y <= m; y++)
					if ((x != i || y != j) && (x + y == i + j || x - y == i - j))
						add (get (i, j), get (x, y));
		}
		else if (type == 'K') { // 王
			for (int p = 0; p < 8; p++) {
				int x = i + Kingdx[p];
				int y = j + Kingdy[p];
				if (x >= 1 && x <= n && y >= 1 && y <= m)
					add (get (i, j), get (x, y));
			}
		}
		else if (type == 'N') { // 马
			for (int p = 0; p < 8; p++) {
				int x = i + Knightdx[p];
				int y = j + Knightdy[p];
				if (x >= 1 && x <= n && y >= 1 && y <= m)
					add (get (i, j), get (x, y));
			}
		}
	}
```

最后正常的跑一遍最小斯坦纳树，再统计答案就行了。
```cpp
for (int i = 1; i <= k; i++) f[1 << (i - 1)][a[i]] = 1;
for (int mask = 1; mask < (1 << k); mask ++) {
	for (int i = 1; i <= n * m; i++) {
		for (int j = mask & (mask - 1); j; j = (j - 1) & mask)
			f[mask][i] = min (f[mask][i], f[j][i] + f[mask ^ j][i] - 1);
		if (f[mask][i] < INF) q.push ({f[mask][i], i});
	}
	Dijkstra (mask);
}
for (int i = 1; i <= n * m; i++) ans = min (ans, f[(1 << k) - 1][i]);
cout << (ans == INF ? -1 : ans - 1); // 记得判断无解
```

---

## 作者：Heldivis (赞：1)

## [CERC2018] The Lord of the Kings

前置知识：[最小斯坦纳树](https://www.luogu.com.cn/problem/P6192)。

这个题建图比较麻烦，要根据不同棋子的走法连边。

其中主教和后的走法有斜线，斜线上的点 $i,j$ 符合 $\forall i, j$ 有 $x_i+y_i=x_j+y_j \text{ or } x_i-y_i=x_j-y_j$，可以根据这个连边。我的建图是 $O(N^4)$ 的，可以有 $O(N^3)$ 写法。

具体看代码：

```cpp
// 二维转一维
int To(int x, int y) { return (x - 1) * lie + y; }
// 王的走法
const int KingDx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int KingDy[8] = {1, -1, 0, 1, -1, -1, 0, 1};
// 骑士走法
const int KnightDx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int KnightDy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
// 加边
void Add(int u, int v) {
  e[u].push_back(v);
  e[v].push_back(u);
}

// 以下在主函数中
for (int i = 1; i <= hang; ++i)
for (int j = 1; j <= lie; ++j) {
  if (op == 'R') {
    for (int x = 1; x <= hang; ++x)
      for (int y = 1; y <= lie; ++y) {
        if ((x != i || y != j) && (x == i || y == j))
          Add(To(i, j), To(x, y));
      }
  }
  if (op == 'Q') {
    for (int x = 1; x <= hang; ++x)
      for (int y = 1; y <= lie; ++y) {
        if ((x != i || y != j) &&
            (x == i || y == j || x + y == i + j || x - y == i - j))
          Add(To(i, j), To(x, y));
      }
  }
  if (op == 'B') {
    for (int x = 1; x <= hang; ++x)
      for (int y = 1; y <= lie; ++y) {
        if ((x != i || y != j) && (x + y == i + j || x - y == i - j))
          Add(To(i, j), To(x, y));
      }
  }
  if (op == 'K') {
    for (int k = 0; k < 8; ++k) {
      int x = i + KingDx[k], y = j + KingDy[k];
      if (1 <= x && x <= hang && 1 <= y && y <= lie)
        Add(To(i, j), To(x, y));
    }
  }
  if (op == 'N') {
    for (int k = 0; k < 8; ++k) {
      int x = i + KnightDx[k], y = j + KnightDy[k];
      if (1 <= x && x <= hang && 1 <= y && y <= lie)
        Add(To(i, j), To(x, y));
    }
  }
}
```

然后跑一个点权的最小斯坦纳树即可：

```cpp
for (int i = 0; i < k; ++i) f[1 << i][poi[i]] = 1;
for (int mask = 0; mask < (1 << k); ++mask) {
  for (int i = 1; i <= n; ++i) {
    for (int sub = mask; sub; sub = (sub - 1) & mask)
      f[mask][i] = std::min(f[mask][i], f[sub][i] + f[mask ^ sub][i] - 1);
    // 这里 -1 是因为 f[sub][i] 和 f[mask ^ sub][i] 都计算了 i
    if (f[mask][i] < Inf) q.push({-f[mask][i], i});
  }
  for (int i = 1; i <= n; ++i) vis[i] = false;
  while (!q.empty()) {
    x = q.top().second;
    q.pop();
    if (!vis[x]) {
      vis[x] = true;
      for (int y : e[x])
        if (f[mask][y] > f[mask][x] + 1) {
          f[mask][y] = f[mask][x] + 1;
          if (!vis[y]) q.push({-f[mask][y], y});
        }
    }
  }
}
```

最后统计答案，注意起点不计入答案，要在判断无解后答案减去 $1$。

```cpp
ll res = Inf;
for (int i = 1; i <= n; ++i) res = std::min(res, f[(1 << k) - 1][i]);
printf("%lld\n", res == Inf ? -1 : res - 1);
```

这样就做完了。

双倍经验：[P4294 WC2008 游览计划](https://www.luogu.com.cn/problem/P4294)，这个题比本题建图较简单，但是要输出方案。

---

## 作者：LastKismet (赞：0)

# Sol
首先这是一个很板的斯坦纳树问题，这里不对板子进行讲解，如有不会出门左转斯坦纳树模板。

关于建图，虽然很繁琐，但是很简单吧，直接模拟就行，详见代码部分。

然后一个问题就是这道题是点权，初始化时将关键点最小代价设作自己的点权、在 SPFA 或者其他方式更新的时候将边权视作对面的点权即可，注意在合并子树的时候根节点的点权被多算了一次，需要减去。

这里为了方便将初始点点权也视作了 $1$，最后答案减去 $1$ 即可。

# Code
```cpp
#define id(x,y) ((x)*mm+(y))

const int N=15*15+5,K=11;

int nn,mm;
int n,k;
vec<pii> G[N];
int p[K],f[N][1<<K];
queue<int> q;
bool inq[N];
void spfa(int s){
	while(!q.empty()){
		int x=q.front();q.pop();inq[x]=0;
		for(auto e:G[x]){
			int y=e.fir,v=e.sec;
			if(f[y][s]>f[x][s]+v){
				f[y][s]=f[x][s]+v;
				if(!inq[y])q.push(y),inq[y]=1;
			}
		}
	}
}
void solve(){
	repl(i,0,n)repl(j,0,1<<k)f[i][j]=inf;
	repl(i,0,k)f[p[i]][1<<i]=1;
	repl(s,1,1<<k){
		repl(i,0,n){
			for(int t=s&s-1;t;t=s&t-1)chmin(f[i][s],f[i][t]+f[i][s^t]-1);
			if(f[i][s]<inf)q.push(i),inq[i]=1;
		}
		spfa(s);
	}
	put(f[p[0]][(1<<k)-1]<inf?f[p[0]][(1<<k)-1]-1:-1);
}

int mdx[8]={-2,-1,1,2,2,1,-1,-2};
int mdy[8]={1,2,2,1,-1,-2,-2,-1};

inline void Main(){
	read(nn,mm);
	int x,y;char c;read(x,y,c);
	p[0]=id(x-1,y-1);
	repl(x,0,nn)repl(y,0,mm){
		if(c=='R'){
			repl(xx,x+1,nn)G[id(x,y)].pub({id(xx,y),1});
			per(xx,x-1,0)G[id(x,y)].pub({id(xx,y),1});
			repl(yy,y+1,mm)G[id(x,y)].pub({id(x,yy),1});
			per(yy,y-1,0)G[id(x,y)].pub({id(x,yy),1});
		}else if(c=='Q'){
			repl(xx,x+1,nn)G[id(x,y)].pub({id(xx,y),1});
			per(xx,x-1,0)G[id(x,y)].pub({id(xx,y),1});
			repl(yy,y+1,mm)G[id(x,y)].pub({id(x,yy),1});
			per(yy,y-1,0)G[id(x,y)].pub({id(x,yy),1});
			int xx,yy;
			for(xx=x+1,yy=y+1;xx<nn&&yy<mm;++xx,++yy)G[id(x,y)].pub({id(xx,yy),1});
			for(xx=x+1,yy=y-1;xx<nn&&yy>=0;++xx,--yy)G[id(x,y)].pub({id(xx,yy),1});
			for(xx=x-1,yy=y+1;xx>=0&&yy<mm;--xx,++yy)G[id(x,y)].pub({id(xx,yy),1});
			for(xx=x-1,yy=y-1;xx>=0&&yy>=0;--xx,--yy)G[id(x,y)].pub({id(xx,yy),1});
		}else if(c=='B'){
			int xx,yy;
			for(xx=x+1,yy=y+1;xx<nn&&yy<mm;++xx,++yy)G[id(x,y)].pub({id(xx,yy),1});
			for(xx=x+1,yy=y-1;xx<nn&&yy>=0;++xx,--yy)G[id(x,y)].pub({id(xx,yy),1});
			for(xx=x-1,yy=y+1;xx>=0&&yy<mm;--xx,++yy)G[id(x,y)].pub({id(xx,yy),1});
			for(xx=x-1,yy=y-1;xx>=0&&yy>=0;--xx,--yy)G[id(x,y)].pub({id(xx,yy),1});
		}else if(c=='N'){
			repl(k,0,8){
				int xx=x+mdx[k],yy=y+mdy[k];
				if(xx<0||xx>=nn||yy<0||yy>=mm)continue;
				G[id(x,y)].pub({id(xx,yy),1});
			}
		}else{
			rep(xx,x-1,x+1)rep(yy,y-1,y+1){
				if(xx<0||xx>=nn||yy<0||yy>=mm||xx==x&&yy==y)continue;
				G[id(x,y)].pub({id(xx,yy),1});
			}
		}
	}
	read(k);++k;
	repl(i,1,k)read(x,y),p[i]=id(x-1,y-1);
	n=nn*mm;
	solve();
}
```

---

## 作者：Sorato_ (赞：0)

# P7463 The Lord of the Kings 题解

## 题目大意

给定一个 $n\times m$ 的网格图，和 $k$ 个特殊点 $(x_k,y_k)$。给定起点 $(a,b)$。选出一些点并规定只能经过这些点，使得起点可以通过特定的移动方式（题目给定为国际象棋中车、后、象、王的移动方式之一），到达所有特殊点，代价为选出点的个数。求最小代价。起点不计入代价。

## Solve

前置芝士：[斯坦纳树](https://www.cnblogs.com/sorato/p/18334710)。在此不再赘述。

了解之后，我们按照给定移动方式建出边，跑最小斯坦纳树就可以了。难点在于建边，$O(n^3)$ 小模拟，细节不少。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=20,K=10,inf=1e9;
int n,k,m,f[1<<K][N*N],S;
typedef pair<int,int> PII;
vector<int>e[N*N];
priority_queue<PII,vector<PII>,greater<PII>>q;
inline void dij(int s)
{
	while(!q.empty())
	{
		int u=q.top().second,d=q.top().first;q.pop();
		if(d>f[s][u])	continue;
		for(int i:e[u])
			if(f[s][i]>d+1)	q.push({f[s][i]=d+1,i});
	}
}
char c;
inline int Get(int x,int y){return (x-1)*m+y;}//二维转一维
inline void add()
{
	for(int i=1;i<=n;i=-~i)
		for(int j=1;j<=m;j=-~j)
		{
			int p=Get(i,j);
			if(c=='N')//马
			{
				if(i>1&&j>2)	e[p].push_back(Get(i-1,j-2));
				if(i>1&&j+1<m)	e[p].push_back(Get(i-1,j+2));
				if(i<n&&j>2)	e[p].push_back(Get(i+1,j-2));
				if(i<n&&j+1<m)	e[p].push_back(Get(i+1,j+2));
				if(j>1&&i>2)	e[p].push_back(Get(i-2,j-1));
				if(j>1&&i+1<n)	e[p].push_back(Get(i+2,j-1));
				if(j<m&&i>2)	e[p].push_back(Get(i-2,j+1));
				if(j<m&&i+1<n)	e[p].push_back(Get(i+2,j+1));
			}
			if(c=='K')//王，相邻的八个点
			{
				if(i>1)	e[p].push_back(Get(i-1,j));
				if(j>1)	e[p].push_back(Get(i,j-1));
				if(i<n)	e[p].push_back(Get(i+1,j));
				if(j<m)	e[p].push_back(Get(i,j+1));
				if(i>1&&j>1)	e[p].push_back(Get(i-1,j-1));
				if(i>1&&j<m)	e[p].push_back(Get(i-1,j+1));
				if(i<n&&j>1)	e[p].push_back(Get(i+1,j-1));
				if(i<n&&j<m)	e[p].push_back(Get(i+1,j+1));
			}
			if(c=='R'||c=='Q')//横/竖着走
			{
				for(int x=i-1;x;x--)	e[p].push_back(Get(x,j));
				for(int x=i+1;x<=n;x=-~x)	e[p].push_back(Get(x,j));
				for(int y=j-1;y;y--)	e[p].push_back(Get(i,y));
				for(int y=j+1;y<=m;y=-~y)	e[p].push_back(Get(i,y));
			}
			if(c=='B'||c=='Q')//斜着走
			{
				for(int x=i-1,y=j-1;x&&y;x--,y--)	e[p].push_back(Get(x,y));
				for(int x=i-1,y=j+1;x&&y<=m;x--,y=-~y)	e[p].push_back(Get(x,y));
				for(int x=i+1,y=j-1;x<=n&&y;x=-~x,y--)	e[p].push_back(Get(x,y));
				for(int x=i+1,y=j+1;x<=n&&y<=m;x=-~x,y=-~y)	e[p].push_back(Get(x,y));
			}
		}
}
int x,y;
signed main()
{
	n=read();m=read();
	x=read();y=read();S=Get(x,y);
	scanf("%c",&c);add();
	k=read();
	for(int s=0;s<(1<<k);s=-~s)
		for(int i=1;i<=n*m;i=-~i)	f[s][i]=inf;
	for(int i=0;i<k;i=-~i)
		x=read(),y=read(),f[1<<i][Get(x,y)]=0;//初始状态，与自己连通代价为0
	for(int s=0;s<(1<<k);s=-~s)//斯坦纳树板子
	{
		for(int t=s;t;t=(t-1)&s)
			for(int i=1;i<=n*m;i=-~i)
				f[s][i]=min(f[s][i],f[t][i]+f[s^t][i]);
		for(int i=1;i<=n*m;i=-~i)
			if(f[s][i]!=inf)	q.push({f[s][i],i});
		dij(s);
	}
	return printf("%d",f[(1<<k)-1][S]<inf?f[(1<<k)-1][S]:-1),0;//若以 S 为根无法使全部连通，输出-1
}
```

---

