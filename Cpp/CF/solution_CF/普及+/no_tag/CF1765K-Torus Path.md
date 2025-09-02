# Torus Path

## 题目描述

You are given a square grid with $ n $ rows and $ n $ columns, where each cell has a non-negative integer written in it. There is a chip initially placed at the top left cell (the cell with coordinates $ (1, 1) $ ). You need to move the chip to the bottom right cell (the cell with coordinates $ (n, n) $ ).

In one step, you can move the chip to the neighboring cell, but:

1. you can move only right or down. In other words, if the current cell is $ (x, y) $ , you can move either to $ (x, y + 1) $ or to $ (x + 1, y) $ . There are two special cases: 
  - if the chip is in the last column (cell $ (x, n) $ ) and you're moving right, you'll teleport to the first column (to the cell $ (x, 1) $ );
  - if the chip is in the last row (cell $ (n, y) $ ) and you're moving down, you'll teleport to the first row (to the cell $ (1, y) $ ).
2. you cannot visit the same cell twice. The starting cell is counted visited from the beginning (so you cannot enter it again), and you can't leave the finishing cell once you visit it.

Your total score is counted as the sum of numbers in all cells you have visited. What is the maximum possible score you can achieve?

## 样例 #1

### 输入

```
2
1 2
3 4```

### 输出

```
8```

## 样例 #2

### 输入

```
3
10 10 10
10 0 10
10 10 10```

### 输出

```
80```

# 题解

## 作者：Alex_Wei (赞：5)

**赛时做法**：从某一列的最后一行跨越至第一行后，无法从某一行的最后一列跨越至第一列，否则路径必然交叉。因此，设 $f_{i, j, k}$ 表示第一次进入第 $i$ 列的位置为 $(k, i)$，当前位置为 $(j, i)$ 的最大收益。根据实际意义转移。注意行列交换再做一次。时间复杂度 $\mathcal{O}(n ^ 3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 200 + 5;
int n, a[N][N], vis[N][N][N];
ll f[N][N][N], ans;
ll dfs(int i, int j, int k) {
  if(i == n && j == n) return a[i][j];
  if(vis[i][j][k]) return f[i][j][k];
  ll ans = -1e18;
  vis[i][j][k] = 1;
  if(i < n) ans = max(ans, dfs(i + 1, j, j));
  int nxt = j == n ? 1 : j + 1;
  if(nxt != k) ans = max(ans, dfs(i, nxt, k));
  return f[i][j][k] = ans + a[i][j];
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n;
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
      cin >> a[i][j];
  ans = dfs(1, 1, 1);
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= i; j++)
      swap(a[i][j], a[j][i]);
  memset(vis, 0, sizeof(vis));
  cout << max(ans, dfs(1, 1, 1)) << "\n";
  return 0;
}
/*
g++ K.cpp -o K -std=c++14 -O2 -DALEX_WEI
*/
```

**官方做法**：手玩几组 $n$ 较小时的简单情况，发现无论怎么走，至少一个副对角线上的元素无法经过，且除此以外所有位置都能经过。证明即考虑可达副对角线的位置共 $n$ 个，但 $(n, n)$ 作为终点，所以最多 $n - 1$ 次经过可达副对角线的位置。钦定某位置不可达后，可用简单策略生成 $(1, 1)$ 到 $(n, n)$ 的路径：每次向下走，只有向下走非法时才向右走。时间复杂度 $\mathcal{O}(n ^ 2)$。

赛时做法可以解决 $a_i < 0$ 的情况，但标算不行。是否存在 $\mathcal{O}(n ^ 2)$ 且能解决 $a_i < 0$ 的做法？

设 $f_{i, j}$ 表示第 $i$ 列经过最后一个格子为 $(j, i)$ 的最大收益，则对于 $k\geq j$，产生 $f_{i, j} + \sum_{p = j} ^ k a_{p, i + 1}$ 贡献。对于 $k < j$，产生 $f_{i, j} + \sum_{p = j} ^ n a_{p, i + 1} + \sum_{p = 1} ^ k a_{p, i + 1}$ 贡献。容易前缀和，前后缀 $\max$ 优化。时间复杂度 $\mathcal{O}(n ^ 2)$。代码懒得写了。

---

## 作者：Dog_E (赞：2)

### 思路

这题其实很简单：

由于只能向右或者向下走，画图可以知道是不可能把**所有格子**走完的。

贪心的走，每次走到末尾的时候偏移一个量（如图），最后就可以得到 $n^2 - 1$ 个格子内的所有分数。

而每次偏移转向的位置是不一样的，所以不可能走到的唯一一个格子**分布在副对角线上**。

最后的答案减去副对角线上最小的值就好了。

![图例](https://cdn.luogu.com.cn/upload/image_hosting/dlbwy4b7.png)


### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[110][110];
long long sum, minn = 2E9;

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            sum += a[i][j];
        }
        minn = min(minn, 1LL * a[i][n - i - 1]);
    }
    cout << sum - minn << "\n";
    return 0;
}
```


---

## 作者：hanjinghao (赞：1)

题意：有 $ n $ $\times$ $ n $ 个格子，第 $ i $ 行第 $ j $ 列的格子的权值为 $ a_{i,j} $，你需要从左上角 $ (1, 1) $ 出发，走若干步，到达右下角 $ (n, n) $。每一步只能向右或向下走。特别地，如果当前在第 $ n $ 行第 $ y $ 列，往下走一步会到达第 $ 1 $ 行第 $ y $ 列；如果当前在第 $ x $ 行第 $ n $ 列，往右走一部会到达第 $ x $ 行第 $ 1 $ 列。同一个格子不能被经过超过一次。问所有合法方案中，经过点的权值和最大是多少。

保证 $ n $ 不超过 $ 200 $。

===================================================

首先，第一行不能横着穿越，第一列不能竖着穿越，否则会二次经过 $ (1, 1) $。我们把第一次穿越前和第一次穿越后分成两部分。设从 $ (1, 1) $ 出发，不经过穿越，走到了 $ (x, y) $，然后从 $ (x, y) $ 向右走，直到穿越到 $ (x, 1) $。注意到一个非常重要的现象：在此之后，要么不穿越，要么还是横着穿越，但不能竖着穿越了。因为以上经过的这些点已经构成了一堵墙，如果在这之后竖着穿越，那么穿越到第一行以后往下走的过程中一定会被墙堵住，即无论怎么走都会有格子被经过两次。所以说，如果第一次穿越是横着穿越，那么之后就不能再竖着穿越了。同理，如果第一次穿越是竖着穿越，那么之后就不能再横着穿越了。

以上，我们已经分析出，既有横着穿越，又有竖着穿越的方案一定不合法。那么只要考虑只横着穿越或只竖着穿越的方案即可。

先考虑只横着穿越的情况。

记状态 $ g_{i,j} $ 表示走到 $ (i, j) $ 之后，往右一直走到 $ (i, n) $，经过的点的权值和的最大值。可以发现，只要在这个基础上再往右走一步，就可以穿越到 $ (i, 1) $。我们可以再记状态 $ f_{i,j} $ 表示第 i 行已经从 $ (i, n) $ 横着穿越到 $ (i, 1) $ 之后，再往右走到 $ (i, j) $，经过的点的权值和的最大值。

一开始先预处理出 $ s_{i,j} $，表示第 $ i $ 行，前 $ j $ 个格子的权值和。

```cpp
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= n; ++j)
			s[i][j] = s[i][j - 1] + a[i][j];
```

这是第一行的状态（第一行因为不能横着穿越，所以 $ g $ 全是零）。

```cpp
	for (register int i = 1; i <= n; ++i)
		f[1][i] = s[1][i];
```

通过刷表法求出其他的状态。

```cpp
	for (register int i = 1; i < n; ++i)
	{
		for (register int j = 1; j <= n; ++j)
			g[i + 1][j] = f[i][j] + s[i + 1][n] - s[i + 1][j - 1];
		for (register int j = 1; j <= n; ++j)
			for (register int k = j; k <= n; ++k)
				f[i + 1][k] = max(f[i + 1][k], f[i][j] + s[i + 1][k] - s[i + 1][j - 1]);
		for (register int j = 1; j < n; ++j)
			for (register int k = j + 1; k <= n; ++k)
				f[i + 1][j] = max(f[i + 1][j], s[i + 1][j] + g[i + 1][k]);
	}

```

以上求出的 $ f_{n,n} $ 表示的是只横着穿越，到达 $ (n, n) $ 的所有方案中，经过的点的权值和的最大值。

用同样的方法，可以求出只竖着穿越，到达 $ (n, n) $ 的所有方案中，经过的点的权值和的最大值，两者取 $ max $ 即为最终答案。

---

