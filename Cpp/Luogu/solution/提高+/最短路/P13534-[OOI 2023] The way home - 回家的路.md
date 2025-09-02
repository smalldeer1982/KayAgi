# [OOI 2023] The way home / 回家的路

## 题目背景

CF1801D

## 题目描述

著名魔术师博里斯·布迪尼在 X 国旅行，这个国家共有 $n$ 个城市。不幸的是，他在编号为 $1$ 的城市遭遇了盗窃。现在，布迪尼需要踏上回家的旅程，目标是回到编号为 $n$ 的城市。

他打算乘坐飞机返家。全国共有 $m$ 个航班，第 $i$ 个航班从城市 $a_i$ 飞往城市 $b_i$，票价为 $s_i$ 卢布。要搭乘某个航班，布迪尼必须身处起点城市 $a_i$，并且手中至少有 $s_i$ 卢布（这些钱在登机时会被扣除）。

被盗后，他仅剩 $p$ 卢布。但他并未气馁！在任意城市 $i$，他都可以随时举办魔术表演，每场表演能赚 $w_i$ 卢布。

请帮助布迪尼判断，他是否能够回到家乡。如果可以，求出他至少需要举办多少场表演。

## 说明/提示

### 样例解释

在第一个样例中，布迪尼最优策略是在第一个城市举办 $4$ 场表演，此时他共有 $2 + 7 \times 4 = 30$ 卢布，然后依次乘坐 $1 \to 3 \to 2 \to 4$ 的航班，花费 $6 + 8 + 11 = 25$ 卢布。

在第二个样例中，布迪尼最优策略是在第一个城市举办 $15$ 场表演，飞到第 $3$ 个城市后再举办 $9$ 场表演，然后前往第 $4$ 个城市。

### 评分说明

本题测试数据分为 6 组。只有通过某一组的全部测试点，且通过部分之前组的全部测试点后，才能获得该组分数。有些分组不要求通过样例测试点。**离线评测**表示该组的测试结果会在比赛结束后公布。

| 组别 | 分值 | $n$ | $m$ | $s_i$ | $w_i$ | 必须通过的组 | 备注 |
|:----:|:----:|:---:|:---:|:-----:|:-----:|:------------:|:----:|
| 0    | 0    | --  | --  | --    | --    | --           | 样例测试点 |
| 1    | 14   | --  | --  | --    | $w_i=1$ | --        |        |
| 2    | 13   | --  | $m = n - 1$ | --    | --    | --           | $a_i = i$，$b_i = i + 1$ |
| 3    | 17   | $n \le 10$ | --  | --    | --    | 0            |        |
| 4    | 19   | $n \le 100$ | -- | $s_i \le 100$ | -- | 0        |        |
| 5    | 21   | $n \le 100$ | -- | --    | --    | 0, 3, 4      |        |
| 6    | 16   | --  | --  | --    | --    | 0--5         | **离线评测** |

## 样例 #1

### 输入

```
4 4 2 0
7 4 3 1
1 2 21
3 2 6
1 3 8
2 4 11```

### 输出

```
4```

## 样例 #2

### 输入

```
4 4 10 0
1 2 10 1
1 2 20
2 4 30
1 3 25
3 4 89```

### 输出

```
24```

## 样例 #3

### 输入

```
4 4 7 0
5 1 6 2
1 2 5
2 3 10
3 4 50
3 4 70```

### 输出

```
10```

## 样例 #4

### 输入

```
4 1 2 0
1 1 1 1
1 3 2```

### 输出

```
-1```

# 题解

## 作者：chen_zhe (赞：4)

**本题解是官方题解的 AI 中文翻译。**

**子任务 1.** 如果所有 $w_i = 1$，那么答案就是最短路长度减去 $p$，可以用 Dijkstra 算法在 $O(m \log n)$ 内找到。

**子任务 4.** 如果所有 $s_i \leq 100$，可以设计状态 $dp[v][ans] = \text{最大剩余金钱}$，转移方式类似 Dijkstra 算法。注意到答案不会超过 $S \cdot n$，其中 $S = \max s_i$。因此总复杂度为 $O(S \cdot n \cdot (n + m) \cdot \log n)$。

**子任务 2.** 注意表演可以“延后”进行。当我们钱不够过某条边时，可以在已经经过的顶点中提前多次表演，以获取最多的钱。如果图是一个两端分别为 $1$ 和 $n$ 的链（bamboo），只需在前缀中维护 $w_i$ 最大的顶点，每当钱不够时就在该顶点表演。这样复杂度为 $O(n)$。

**完整解法.** 借鉴子任务 2 的思路，可以设计状态 $dp[v][best] = (\textit{最少表演次数}, \textit{最大剩余金钱})$，其中 $v$ 表示当前所在顶点，$best$ 表示已经经过的、$w_i$ 最大的顶点。可以证明，最优策略是先最小化表演次数，再最大化剩余金钱。该动态规划的转移方式与子任务 4 类似，总复杂度为 $\mathcal{O}(mn \log n)$。

---

## 作者：_cbw (赞：1)

[LOJ 1st](https://loj.ac/s/2380974)！

---

## Solution

图论，最优化，考虑最短路。

首先需要明白一件事情：不一定要等到没钱用的时候再表演，钱是一直可以用的。因此，可以先在演出费比较高的城市攒够了钱，以后就无需再表演了。

事实上，对于答案路径 $u_1, u_2, \cdots, u_k$，我们总是在那些 $w_{u_i}$ 是前缀最大值的地方表演。

据此可以设计最短路算法：每个状态维护当前点、当前路径的最大 $w_{u_i}$，当前的表演数、当前剩余的货币数 $(u, b, p, r)$。

执行松弛时，优先取 $p$ 最小的；在此前提下，优先取 $r$ 最大的；在此前提下，优先取 $b$ 最大的。
每当 $r < s_e$ 即买不起机票时就做 $\left \lceil \frac{s_e - r}{b} \right \rceil$ 次表演以使我们刚好买得起机票。

[然后就获得了 $46$ 分](https://loj.ac/s/2380960)。

想想问题出在哪。发现，当我们以不同的 $b$、相同的 $r$ 到达一个点的时候，若其需要表演，走过同一条边所需的表演次数可能会不同。或者说，当 $b$ 不同时每条边的**边权是不同的**。

对此，可以将“点”的定义修改为 $(u, u_i)$，其中 $u_i$ 是当前路径的最大 $w_{u_i}$ 对应的**点** $\bm{u_i}$。这样，对于同一个“点”，其连出边的“边权”也是固定的。

## Complexity

乍一看，好像“点”数是 $\Theta(n^2)$ 的，再来 $m$ 条边，实际总“边”数是 $\Theta(n^2m)$？

实际上，对于单个点（不带 $u_i$ 一维的原本的点）$u$，其只会贡献 $\min\{n, \text{indegree}_u\} \times \text{outdegree}_u$ 条“边”参与到松弛中。考虑到 $\sum_u \text{indegree}_u = \sum_u \text{outdegree}_u = m$，在“边”最多的情况下，也只为 $\Theta(nm)$ 级。

因此，最终的时间复杂度为 $\Theta(n^2 \log n^2 + nm) = \Theta(n^2 \log n + nm)$（Fib 堆）或 $\Theta(n^2 + nm \log nm)$（二叉堆），空间复杂度 $\Theta(n^2 + nm)$。

~~不是为啥我咋分析都分析不出 $\Theta(mn \log n)$ 的复杂度。太菜了导致的。~~

## Code

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#define MAXN 803
#define MAXM 3003
using namespace std;
using lli = long long;

struct Node
{
    int u, bes;
    lli mnp, mxw;
    bool operator<(const Node &other) const
    {
        if (mnp != other.mnp)
            return mnp > other.mnp;
        return mxw < other.mxw;
    }
    bool operator!=(const Node &other) const
    {
        return mnp != other.mnp || mxw != other.mxw;
    }
};
struct Edge
{
    int to, w, nxt;
} edges[MAXM];
int cnt, a[MAXN], head[MAXN];
Node dis[MAXN][MAXN];

inline void add_edge(const int &from, const int &to, const int &w)
{
    edges[++cnt] = {to, w, head[from]}, head[from] = cnt;
}
void dijkstra(const int &n, const int &begw)
{
    priority_queue<Node> que;
    Node cur, to;
    lli tmp;
    for (int i = 1; i <= n; ++i)
        fill(dis[i] + 1, dis[i] + n + 1, Node{0, 0, 0x3f3f3f3f3f3f3f3fLL, 0});
    que.push(dis[1][1] = {1, 1, 0, begw});
    while (!que.empty())
    {
        cur = que.top(), que.pop();
        if (cur != dis[cur.u][cur.bes])
            continue;
        for (int i = head[cur.u]; i; i = edges[i].nxt)
        {
            to = {edges[i].to, a[cur.bes] < a[edges[i].to] ? edges[i].to : cur.bes, cur.mnp, cur.mxw};
            if (to.mxw < edges[i].w)
                tmp = (edges[i].w - to.mxw + a[cur.bes] - 1) / a[cur.bes], to.mnp += tmp, to.mxw += tmp * a[cur.bes];
            to.mxw -= edges[i].w;
            if (dis[to.u][to.bes] < to)
                que.push(dis[to.u][to.bes] = to);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, m, begw, u, v, w;
    cin >> n >> m >> begw >> u;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    while (m--)
        cin >> u >> v >> w, add_edge(u, v, w);
    dijkstra(n, begw);
    Node cur = {0, 0, 0x3f3f3f3f3f3f3f3fLL, 0};
    for (int i = 1; i <= n; ++i)
        cur = max(cur, dis[n][i]);
    cout << (cur.mnp == 0x3f3f3f3f3f3f3f3fLL ? -1LL : cur.mnp);
    return 0;
}
```

---

