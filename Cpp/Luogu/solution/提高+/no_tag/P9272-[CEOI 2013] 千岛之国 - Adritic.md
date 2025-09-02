# [CEOI 2013] 千岛之国 / Adritic

## 题目背景

翻译自 [CEOI 2013 Day 2](https://ceoi2013.hsin.hr/tasks/tasks_day2.pdf)。

“千岛之国”是克罗地亚旅游业在二十世纪九十年代中期的官方口号。虽然这个口号实际上不准确（克罗地亚的岛屿数量略多于 $1000$ 个），但“跳岛旅游”（从一个岛屿航行到另一个岛屿）是一个受欢迎的夏季活动。亚得里亚海的地图是由组成 $2500$ 行和 $2500$ 列的单位正方形组成的网格。行编号从北到南为 $1$ 到 $2500$，而列编号从西到东为 $1$ 到 $2500$。海中有 $N$ 个岛屿，编号为 $1$ 到 $N$，每个岛屿都位于网格的某个单位正方形内。岛屿 $K$ 的位置由相应的网格方格的坐标确定——其行号 $R_K$ 和列号 $C_K$。没有两个岛屿的位置相同。

由于风和海流的影响，只有当岛屿 $B$ 对于 $A$ 来说位于大致的西北或东南方向时才能直接从一个岛屿航行到另一个岛屿。更准确地说，只有在 $R_A < R_B$ 和 $C_A < C_B$ 都成立，或 $R_A > R_B$ 和 $C_A > C_B$ 都成立时，才可以从岛屿 $A$ “跳”到岛屿 $B$。请注意，两个岛屿之间的距离或其他岛屿的存在并不影响从一个岛屿跳到另一个岛屿的可能性。如果无法直接从 $A$ 跳到 $B$，则可能通过其他岛屿使用一些“跳跃”序列从 $A$ 到 $B$ 进行航行。从 $A$ 到 $B$ 的航行距离定义为从 $A$ 到 $B$ 所需的最少“跳跃”次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/hdqlicpn.png)

例如，在上面的图中，从位于第 $2$ 行第 $3$ 列的岛屿开始，我们可以跳到另外四个岛屿，而剩下的两个岛屿的航行距离为两个跳跃次数。

## 题目描述

一次帆船大会正在计划，组织者正在考虑每个岛屿作为大会的可能场地。在考虑候选岛屿时，他们想知道：如果每个其他岛屿都派出一艘帆船，为了使所有帆船都到达候选岛屿，需要的最小跳数是多少，或者等效地说，从所有其他岛屿到候选岛屿的航行距离之和是多少。

编写一个程序，对于给定 $N$ 个岛屿的位置，对于每个岛屿 $K$，计算所有其他岛屿到岛屿 $K$ 的航行距离之和。测试数据保证，对于所有岛屿 $A$ 和 $B$，可以使用一些跳跃序列从 $A$ 到 $B$ 航行。

## 说明/提示

在 $25\%$ 的测试用例中，$N$ 最多为 $100$。

在 $50\%$ 的测试用例中，$N$ 最多为 $1500$。

在 $60\%$ 的测试用例中，$N$ 最多为 $5000$。

在 $80\%$ 的测试用例中，$N$ 最多为 $25000$。

在 $100\%$ 的测试用例中，$1\le N\le250000$。

**注意：$N$ 可以是 $1$。**

## 样例 #1

### 输入

```
7
1 7
7 5
4 5
4 8
6 6
6 1
2 3```

### 输出

```
16
11
12
11
12
16
8```

## 样例 #2

### 输入

```
4
1 1
2 3
3 2
4 4```

### 输出

```
3
4
4
3```

# 题解

## 作者：cff_0102 (赞：8)

首先，可以等效地把题目看成从目标岛屿出发到达每个其他岛屿，这在思考上更容易一些。

![](https://cdn.luogu.com.cn/upload/image_hosting/fi7mmzuw.png)

显然，在区域 $1$ 和 $3$ 的地方可以一次去到。

![](https://cdn.luogu.com.cn/upload/image_hosting/vkiegiis.png)

与第一张图相比，代表区域 $2$ 的矩形已经收缩了，区域 $4$ 也是如此。随着 BFS 进展到第 $3,4$ 或者更多步，这两个矩形将继续缩小，直到进行到第 $i$ 步时，没有任何岛屿在其中（所有岛屿都能在 $i$ 步以内去到）。如果我们需要知道，在 BFS 的下一步，这两个白色区域将如何缩小，只要知道在它周围最靠边的岛屿就可以了。这些岛屿在下图中用浅灰色标记。

![](https://cdn.luogu.com.cn/upload/image_hosting/zqavwo3g.png)

设 $\operatorname{dp(r,c)}$ 为访问矩形 $(r,c)-(N,1)$（就是上面的空白部分）中岛屿所需的余下跳数，设 $\operatorname{cnt(r,c)}$ 为矩形中的岛屿数量。

如果矩形中没有岛屿（$\operatorname{cnt(r,c)}=0$），那么 $\operatorname{dp(r,c)}=0$，表示不需要再继续跳了。否则，当 BFS 继续，矩形会缩小至 $(\operatorname{min_r{(r,c)}},\operatorname{max_c{(r,c)}})-(N,1)$。其中 $\operatorname{min_r}$ 是矩形左侧所有岛屿中的最小行，$\operatorname{max_c}$ 是矩形下方所有岛屿中的最大列。现在，$\operatorname{dp(r,c)}$ 很容易状态转移为 $\operatorname{cnt(r,c)}+\operatorname{dp(min_r{(r,c)},max_c{(r,c)})}$。

对于左下角矩形，也用类似的方法，最后把结果加起来，就可以得到从起始岛屿开始的总跳数。

官方题解代码：

```cpp
// CEOI 2013 - Task: Adriatic - Solution
// Author: Gustav Matula

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define MAXC 2500
#define MAXN 250005
#define CFF 0102

int N;
int x[MAXN], y[MAXN];

int on[MAXC+2][MAXC+2];
int cnt[MAXC+2][MAXC+2];
int minx[MAXC+2][MAXC+2];
int miny[MAXC+2][MAXC+2];
int maxx[MAXC+2][MAXC+2];
int maxy[MAXC+2][MAXC+2];

int mur[MAXC+2][MAXC+2];
int mdl[MAXC+2][MAXC+2];

int ur(int x, int y) {
  int &ref = mur[x][y];
  if (ref != -1) return ref;
  if (cnt[x][MAXC] - cnt[x][y-1] == 0) return ref =  0;
  return ref = cnt[x][MAXC] - cnt[x][y-1] + ur(min(x, minx[x][y-1]), max(y, maxy[x+1][y]));
}

int dl(int x, int y) {
  int &ref = mdl[x][y];
  if (ref != -1) return ref;
  if (cnt[MAXC][y] - cnt[x-1][y] == 0) return ref =  0;
  return ref = cnt[MAXC][y] - cnt[x-1][y] + dl(max(x, maxx[x][y+1]), min(y, miny[x-1][y]));
}

int main(void)
{
  scanf("%d", &N);
  
  if (N == 1) std::cout << 0, exit(0);

  for (int i = 0; i < N; ++i) {
    scanf("%d%d", x+i, y+i);
    on[x[i]][y[i]] = 1;
  }

  memset(minx, 0x3f, sizeof minx);
  memset(miny, 0x3f, sizeof miny);

  for (int i = 1; i <= MAXC; ++i) {
    for (int j = 1; j <= MAXC; ++j) {
      cnt[i][j] = on[i][j] + cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1];
      minx[i][j] = on[i][j] ? min(i, minx[i-1][j]) : min(minx[i-1][j], minx[i][j-1]);
      miny[i][j] = on[i][j] ? min(j, miny[i][j-1]) : min(miny[i-1][j], miny[i][j-1]);
    }
  }

  for (int i = MAXC; i >= 1; --i) {
    for (int j = MAXC; j >= 1; --j) {
      maxx[i][j] = on[i][j] ? max(i, maxx[i+1][j]) : max(maxx[i+1][j], maxx[i][j+1]);
      maxy[i][j] = on[i][j] ? max(j, maxy[i][j+1]) : max(maxy[i+1][j], maxy[i][j+1]);
    }
  }

  memset(mur, -1, sizeof mur);
  memset(mdl, -1, sizeof mdl);

  for (int i = 0; i < N; ++i) 
    printf("%d\n", cnt[MAXC][MAXC] + ur(x[i], y[i]) + dl(x[i], y[i]) - 3);

  return 0;
}
```

这题还有一个小坑点。看到说明提示最后一行，发现 $N$ 可以为 $1$，这说明什么？尝试一下，$N=1$ 时，很明显应该输出的是 $0$。所以这份代码在 `main` 函数开头特判了一下，直接输出，结束程序，避免继续运行，产生错误的结果。


---

## 作者：2huk (赞：2)

[官方题解](https://ceoi2013.hsin.hr/tasks/tasks_and_solutions.pdf)的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/b5kgfb0m.png)

显然 $(r, c)$ 能一步到达的点在 **左上** 和 **右下** 这两块灰色区域。

两步能到达的点呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/qhk8mogy.png)

除了 **左下** 和 **右上** 这两块白色区域内的点都可以在 $\le 2$ 步内到达。

一些尝试后可以发现，BFS 到每个阶段时，仍不能到达的点一定是一块左下区域，和一块右上区域。尝试从这一点下手。

令 $f(x,y)$ 表示若除了矩阵 $(1,y)-(x,N)$ 外，所有点都已经到达（即 BFS 过），这个矩阵内的点到**矩阵外某个点**的最短路之和。$g(x,y)$ 同理表示左下角的矩阵的答案。

那么答案为 $n-1+f(x,y)-1 + g(x,y)-1$。表示我们分别计算第一步时右上矩阵和左下矩阵的答案。为啥有三个 $-1$？因为去掉自己。

考虑怎么求 $f(x, y)$。

考虑再进行一步 BFS 后，这个白色矩阵会缩小到多少。

还是这两张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bjcc4nkv.png)

不难发现是箭头指的点决定了缩小后矩阵的大小。因为**新变成灰色的点都可以通过这两个点一步走到**。

而这两个点分别是什么呢？右边这个是纵坐标 $> r$ 的横坐标最大的点，上边这个是横坐标 $<c$ 的纵坐标最小的点。预处理一下就好啦。

所以 $f(x,y) = cnt(x,y)+f(x',y')$。其中 $cnt(x,y)$ 表示矩阵 $(1,y)-(x,N)$ 内的点数，$x',y'$ 表示这个新矩阵的左下角坐标。

$g(x,y)$ 同理不再赘述。

```cpp
// Problem: 
//     P9272 [CEOI 2013] 千岛之国 / Adritic
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9272
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #define tests
#include <bits/stdc++.h>

using namespace std;

const int N = 250010;

int n;
int a[N], b[N];
bool gra[2510][2510];
int sum[2510][2510];

int calc(int x_1, int y_1, int x_2, int y_2) {
	return sum[x_2][y_2] - sum[x_1 - 1][y_2] - sum[x_2][y_1 - 1] + sum[x_1 - 1][y_1 - 1];
}

int xmin[N];		// 横坐标 <= i 的纵坐标的最小值  1
int xmax[N];		// 横坐标 >= i 的纵坐标的最大值  3
int ymin[N];		// 纵坐标 <= i 的横坐标的最小值  4
int ymax[N];		// 纵坐标 >= i 的横坐标的最大值  2

int f[2510][2510], g[2510][2510];

int dpf(int x, int y) {
	// cout << x << ' ' << y << '\n';
	if (~f[x][y]) return f[x][y];
	
	int cnt = calc(1, y, x, 2500);
	if (!cnt) return f[x][y] = 0;
	
	f[x][y] = 0;
	return f[x][y] = cnt + dpf(min(x, xmin[y - 1]), max(y, ymax[x + 1]));
}

int dpg(int x, int y) {
	if (~g[x][y]) return g[x][y];
	
	int cnt = calc(x, 1, 2500, y);
	if (!cnt) return g[x][y] = 0;
	
	g[x][y] = 0;
	return g[x][y] = cnt + dpg(max(x, xmax[y + 1]), min(y, ymin[x - 1]));
}

void solve() {
	cin >> n;
	
	memset(xmin, 0x3f, sizeof xmin);
	memset(ymin, 0x3f, sizeof ymin);
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i] >> b[i];
		gra[a[i]][b[i]] = true;
		ymin[a[i]] = min(ymin[a[i]], b[i]);
		ymax[a[i]] = max(ymax[a[i]], b[i]);
		xmin[b[i]] = min(xmin[b[i]], a[i]);
		xmax[b[i]] = max(xmax[b[i]], a[i]);
	}
	
	for (int i = 1; i <= 2500; ++ i )
		for (int j = 1; j <= 2500; ++ j )
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + gra[i][j];
	
	for (int i = 1; i <= 2500; ++ i ) {
		xmin[i] = min(xmin[i], xmin[i - 1]);
		ymin[i] = min(ymin[i], ymin[i - 1]);
	}
	
	for (int i = 2500; ~i; -- i ) {
		xmax[i] = max(xmax[i], xmax[i + 1]);
		ymax[i] = max(ymax[i], ymax[i + 1]);
	}
	
	memset(f, -1, sizeof f);
	memset(g, -1, sizeof g);
	for (int i = 1; i <= n; ++ i ) {
		cout << n - 1 + dpf(a[i], b[i]) + dpg(a[i], b[i]) - 2 << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
#ifdef tests
	cin >> T;
#endif
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：XuYueming (赞：1)

## 前言

[更好的体验](https://www.cnblogs.com/XuYueming/p/18295702)。

## 题意简述

你被困在一个被划分为 $2500 \times 2500$ 的二维平面内！平面上有 $n$（$n \leq 250000$）个岛屿你可以停留，你可以在这些岛屿之间行走，但是你只能走到严格在当前岛屿的左上或右下的岛屿。即目标点 $(x', y')$ 满足和当前点 $(x, y)$ 的关系为：$(x' < x \land y' < y) \lor (x' > x \land y' > y)$。问分别从每个岛屿出发，分别走到其他岛屿的最小步数之和是多少。

## 题目分析

你当然可以暴力建图加分别跑 BFS，时间复杂度 $\Theta(n ^ 3)$。优化？难道说扫描线的同时线段树优化建图再然后 01-BFS？似乎这样变得更劣、更难继续优化了？不太行。所以考虑换一个思路。

发现平面边长是 $2500$，在引导我们思考有关平面边长的平方的算法。

经过玩样例发现，不能直接一步走到的地方是左下角和右上角的一片区域。并且这两片区域会越来越小，直到里面一个岛屿都没有了后停止。

比如从 $(4, 5)$ 出发，用灰色区域表示能够直接一次走到的区域。即从当前 $k$ 步之内能到达的区域，使用 $k + 1$ 步能够到达的区域。

![](https://cdn.luogu.com.cn/upload/image_hosting/kn34lb3s.png)

然后继续，接下来能够直接一次走到的区域，也即走 $2$ 步及以内能到达的区域。

![](https://cdn.luogu.com.cn/upload/image_hosting/hncz7tll.png)

发现 $2$ 步以内就能走到所有岛屿。过程中，没有被灰色覆盖的区域就是所谓的“不能直接一步走到的区域”。这个逐渐减少的过程也很好理解。

那么，状态就可以记这两个区域了。发现两个区域互相独立，所以可以分别计算。并且发现，在计算步数时，每次加上当前不能一次走到的区域的个数就行了，这相当于把某一个区域对答案的贡献拆到了每走一步里。注意初始每个位置至少需要 $1$ 步，以及不要把起点算进去。这个式子在下面会列出来。

设 $f[x][y]$ 表示当前不能一次走到的区域是以 $(x, y)$ 为右上角的区域，里面的区域对答案的贡献。同理，$g[i][j]$ 表示当前不能一次走到的区域是以 $(x, y)$ 为左下角的区域，里面的区域对答案的贡献。

如果起点是 $(x, y)$，上面我们讲的答案就是 $(n - 1) + (f[x][y] - 1) + (g[x][y] - 1)$。

那该如何转移呢？以左下角的 $f[x][y]$ 为例。

首先，我们要知道这一片区域内岛屿的数量，二维前缀和即可。其次，我们要知道下一个状态。我们要在这个区域的右边能够到达的区域里，找到最下方的一个岛屿，下一个状态的纵坐标就是这个岛屿的纵坐标。以及在上方能够到达的区域里，找到最左边的一个岛屿，作为下一个状态的横坐标。可以结合上面的样例理解。这个可以用前后缀最值预处理。

实现的时候，用一个记忆化搜索就行了。不知道为什么有题解说要特判 $n = 1$，不特判也能过。

## 代码

略去了快写。

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

int n, x[250010], y[250010];
bool on[2510][2510];
int sum[2510][2510];
int mini[2510], minj[2510];
int maxi[2510], maxj[2510];

inline int min(int a, int b) {
	return a < b ? a : b;
}

inline int max(int a, int b) {
	return a > b ? a : b;
}

int ur(int x, int y) {
	static int f[2510][2510];
	static bool vis[2510][2510];
	if (vis[x][y]) return f[x][y];
	vis[x][y] = true;
	if (sum[x][2500] - sum[x][y - 1] == 0) return 0;
	return f[x][y] = sum[x][2500] - sum[x][y - 1] + ur(min(x, mini[y - 1]), max(y, maxj[x + 1]));
}

int dl(int x, int y) {
	static int f[2510][2510];
	static bool vis[2510][2510];
	if (vis[x][y]) return f[x][y];
	vis[x][y] = true;
	if (sum[2500][y] - sum[x - 1][y] == 0) return 0;
	return f[x][y] = sum[2500][y] - sum[x - 1][y] + dl(max(x, maxi[y + 1]), min(y, minj[x - 1]));
}

signed main() {
	fread(buf, 1, MAX, stdin);
	read(n);
	memset(mini, 0x3f, sizeof mini);
	memset(minj, 0x3f, sizeof minj);
	for (int i = 1; i <= n; ++i) {
		read(x[i]), read(y[i]), on[x[i]][y[i]] = true;
		mini[y[i]] = min(mini[y[i]], x[i]);
		maxi[y[i]] = max(maxi[y[i]], x[i]);
		minj[x[i]] = min(minj[x[i]], y[i]);
		maxj[x[i]] = max(maxj[x[i]], y[i]);
	}
	for (int i = 1; i <= 2500; ++i) {
		mini[i] = min(mini[i], mini[i - 1]);
		minj[i] = min(minj[i], minj[i - 1]);
	}
	for (int i = 2500; i; --i) {
		maxi[i] = max(maxi[i], maxi[i + 1]);
		maxj[i] = max(maxj[i], maxj[i + 1]);
	}
	for (int i = 1; i <= 2500; ++i)
	for (int j = 1; j <= 2500; ++j)
		sum[i][j] = on[i][j] + sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
	for (int i = 1; i <= n; ++i) {
		write(n + (ur(x[i], y[i]) - 1) + (dl(x[i], y[i]) - 1) - 1);
		putchar('\n');
	}
	fwrite(obuf, 1, o - obuf, stdout);
	return 0;
}
```

## 后记 & 反思

~~对对对，扫描线的同时线段树优化建图再然后 01-BFS 发现无从下手的人就是我。~~

这道题转化模型、寻找性质，以及拆贡献的方法，对我们有诸多启示。

---

## 作者：ln001 (赞：1)

### 闲话
膜拜 2huk 和他的题解。
## 题意
在**有限大小**的网格上给定若干点，对于每个点，求**与其他点的最短路之和**是多少。

连边规则为对于任意两点 $(x_1, y_1), (x_2, y_2)$ 在满足 $x_1 < x_2 $ 和 $y1 < y2$ 时连有**双向**且边权为 $1$ 的边。

## 做法
下文称点 $(x, y)$ 的左上矩形是左上角为 $(1, 1)$ 右下角为 $(x, y)$ 的矩形，左下、右上、右下矩形均同理。


现在考虑对点 $(x, y)$ 计算答案。与其的最短路为 $1$ 的点，显然位于点 $(x, y)$ 的左上与右下矩形中。

![图炸了，自己去官方题解找吧](https://cdn.luogu.com.cn/upload/image_hosting/b5kgfb0m.png)

当考虑的最短路长度增加到 $2$ 时，手动模拟，可以发现，不满足最短路长度小于等于 $2$ 的点由一个左下矩形和右上矩形组成。

![图炸了，自己去官方题解找吧](https://cdn.luogu.com.cn/upload/image_hosting/qhk8mogy.png)

进一步地，可以发现，不论合法最短路长度设为多大，不合法的点一定由一个左下和右上矩形组成。在点 $(x, y)$ 左下矩形及右上矩形中的点无法仅通过一条边连回点 $(x, y)$。这里的点指的是**网格中的格点**，不是题目中给的点。



---

上文的讨论中可以看出，左下矩形的右上矩形独立，分别考虑即可，这里只考虑右上矩形。

重申一下，现在是在对点 $(x, y)$ 计算答案。

设 $f_{i, j}$ 表示 $(i, j)$ 的右上矩形中的点**连向矩形外部任意一点的最短路**的和。$g_{i, j}$ 表示左下矩形的。

答案为 $(n - 1) + (f_{x, y} - 1) + (g_{x, y} - 1)$ 因为所有点连向点 $(x, y)$ 的最短路至少为 $1$，必须绕路的点产生的**额外贡献已经被计算**到 $f, g$ 中，$f, g$ 两数组后面跟减一是为了把点 $(x, y)$ 的贡献删去。

---

问题在于计算 $f$ 数组，一个矩形的值的来源肯定是一个被该矩形包含的矩形。

反过来想，从被包含的小矩形转移到需要计算的大矩形，变成从大矩形走向小矩形，那就需要找到最小的合法小矩形，满足大矩形中的点走一步就能到达小矩形中的点。不难发现，大矩形中有贡献的点仅有两个，第一个是位于大矩形下边界的上方（不能正好在下边界上，否则不能进行下一步转移）的**最靠左的点**，第二个是位于矩形左边界右侧最靠下的点。

$g$ 同理。

---

