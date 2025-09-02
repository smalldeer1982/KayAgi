# [GCJ 2008 Finals] The Year of Code Jam

## 题目描述

2008 年将被称为变革与转折之年，是新时代的开始：我们当然说的是全新的 Google Code Jam 赛制。今年举办了如此多精彩的编程竞赛，以至于人们开始称其为“Code Jam 之年”。

热情的参赛者 Sphinny 正在查看她这一年的日历，发现有大量编程比赛已经安排好。她在日历上的每一天都做了如下三种标记之一：

- 白色：这一天她不会参加比赛。要么没有比赛安排，要么她有更重要的事情要做（生活中肯定还有其他美好的事物！）。
- 蓝色：这一天她一定会参加比赛。
- 问号：这一天有比赛安排，但她还没有决定是否参加。

注意：为简化问题，我们假设没有资格赛的概念：你不需要参加某场比赛才能有资格参加另一场。

在 Sphinny 所处的世界中，她的日历有一些我们必须说明的特点：它有 $N$ 个月，每个月恰好有 $M$ 天。

下图展示了一个有 5 个月、每月 8 天、15 个蓝色日和 5 个问号的日历。

![](https://cdn.luogu.com.cn/upload/image_hosting/ln25sw62.png)

Sphinny 看着她漂亮的日历，决定每一天最多有 4 个邻居：同一个月的前一天、同一个月的后一天、同一天的上一个月、同一天的下一个月。

Sphinny 希望通过这些比赛最大化她的幸福感，她估算幸福值的方法是对所有蓝色日的数值求和。对于每一个蓝色日，其数值计算如下：

- 初始值为 4。
- 每有一个蓝色邻居，该日的数值减少 1。

你可能会觉得 Sphinny 很喜欢比赛，但连续两天参赛会让她有点疲惫。出于美学原因，在连续两个月的同一天参赛也不是很理想。

Sphinny 现在想要规划她的全年日程，决定每一个问号日到底是白色还是蓝色。她的目标很简单：让幸福值最大化。

下图展示了上述例子的一个解法。通过将两个问号改为蓝色日，将另外三个改为白色日，她可以获得 42 的幸福值。

![](https://cdn.luogu.com.cn/upload/image_hosting/d6qxnu8l.png)

## 说明/提示

**样例说明**

请注意，第二个样例就是上面图片中的例子。

**数据范围**

- $1 \leqslant T \leqslant 100$。

**小数据集（7 分，测试点 1 - 可见）**

- 时间限制：~~30~~ 3 秒。
- $1 \leqslant M, N \leqslant 15$。

**大数据集（23 分，测试点 2 - 隐藏）**

- 时间限制：~~120~~ 12 秒。
- $1 \leqslant M, N \leqslant 50$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3 3
.?.
.?.
.#.
5 8
.#...##.
.##..?..
.###.#.#
??#..?..
###?#...```

### 输出

```
Case #1: 8
Case #2: 42```

# 题解

## 作者：zhangxiaoyu008 (赞：0)

说实话这道题和 [这道题](/problem/AT_abc193_f) 很像，~~不知道是不是 **Atcoder** 抄了这道题~~。

首先，在整个日历外面新加一圈白色的格子。

加完这一圈后，我们可以先把原题中的蓝色日数值的总和转化为相邻的黑格和白格的对数，就转化为了那道 **Atcoder**。

~~因为这道题有网络流标签，所以很自然的想到网络流。~~

然后发现最大流好像不太好刻画，于是使用最小割。

首先算出所有的对数，然后减去相邻的相同颜色格子的对数。

但是这里有个问题：如果直接求最小割，求到的是不同颜色的最小对数，而非相同颜色的最小对数，于是可以考虑黑白染色，把黑/白的所有格子翻转颜色，再求最小割就相当于原来相同颜色格子的最小对数。

连边：

设将 $S$ 集合内的点染成白色，把 $T$ 集合内的点染成白色（当然你也可以反过来做）。

如果当前格子确定是白色，则从 $S$ 到当前格子连一条 $+ \infty$ 的边，表示该边不能被割掉（即它一定在 $S$ 集合里），实现时 $4$ 其实就够了。

如果当前格子确定是黑色，同理可得。

然后向上下左右各连一条边权为 $1$ 的边，就做完了。

:::info[$\large{\mathbf{Code}}$]{open}
[AC 记录](https://www.luogu.com.cn/record/229219734)

```cpp line-numbers
#include <bits/stdc++.h>
using namespace std;‌‍
const int N = 50 + 10, V = 5e3 + 10, E = 1e5 + 10;‌‍
int cases, n, m, S, T, id[N][N], dx[] = {‌‍-1, 0}‌‍, dy[] = {‌‍0, -1}‌‍;‌‍
char g[N][N];‌‍
template<typename T>
struct FlowGraph{‌‍ // Max Flow Graph
    int s, t, vtot;‌‍
    int h[V], etot;‌‍
    int dist[V], cur[V];‌‍
    struct Edge{‌‍
        int v, nxt;‌‍
        T f;‌‍
    }‌‍e[E << 1];‌‍
    void add_edge(int u, int v, T f, T f2 = 0) {‌‍
        e[etot] = {‌‍v, h[u], f}‌‍;‌‍ h[u] = etot ++;‌‍
        e[etot] = {‌‍u, h[v], f2}‌‍;‌‍ h[v] = etot ++;‌‍
    }‌‍
    bool bfs() {‌‍
        for(int i = 1;‌‍ i <= vtot;‌‍ i ++) {‌‍
            dist[i] = 0;‌‍
            cur[i] = h[i];‌‍
        }‌‍
        queue<int> q;‌‍
        q.push(s);‌‍ dist[s] = 1;‌‍
        while(!q.empty()) {‌‍
            int u = q.front();‌‍ q.pop();‌‍
            for(int i = h[u];‌‍ ~i;‌‍ i = e[i].nxt) {‌‍
                int v = e[i].v;‌‍
                if(e[i].f && !dist[v]) {‌‍
                    dist[v] = dist[u] + 1;‌‍
                    if(v == t) return true;‌‍
                    q.push(v);‌‍
                }‌‍
            }‌‍
        }‌‍
        return false;‌‍
    }‌‍
    T dfs(int u, T m) {‌‍
        if(u == t) return m;‌‍
        T flow = 0;‌‍
        for(int &i = cur[u];‌‍ ~i;‌‍ i = e[i].nxt) {‌‍
            int v = e[i].v;‌‍
            if(e[i].f && dist[v] == dist[u] + 1) {‌‍
                T f = dfs(v, min(e[i].f, m));‌‍
                e[i].f -= f;‌‍
                e[i ^ 1].f += f;‌‍
                flow += f;‌‍
                if(!(m -= f)) break;‌‍
            }‌‍
        }‌‍
        if(!flow) dist[u] = -1;‌‍
        return flow;‌‍
    }‌‍
    T dinic() {‌‍
        T flow = 0;‌‍
        while(bfs()) flow += dfs(s, numeric_limits<T>::max());‌‍
        return flow;‌‍
    }‌‍
    void init(int s_, int t_, int vtot_) {‌‍
        s = s_, t = t_, vtot = vtot_, etot = 0;‌‍
        for(int i = 1;‌‍ i <= vtot;‌‍ i ++) h[i] = -1;‌‍
    }‌‍
}‌‍;‌‍
FlowGraph<int> G;‌‍
int main()
{‌‍
    scanf("%d", &cases);‌‍
    for(int C = 1;‌‍ C <= cases;‌‍ C ++) {‌‍
        scanf("%d%d", &n, &m);‌‍
        for(int i = 1;‌‍ i <= n;‌‍ i ++) scanf("%s", g[i] + 1);‌‍
        n ++, m ++;‌‍
        int tot = 0;‌‍
        for(int i = 0;‌‍ i <= n;‌‍ i ++) g[i][0] = g[i][m] = '.';‌‍ // 添加外圈
        for(int i = 0;‌‍ i <= m;‌‍ i ++) g[0][i] = g[n][i] = '.';‌‍ // 添加外圈
        for(int i = 0;‌‍ i <= n;‌‍ i ++) {‌‍
            for(int j = 0;‌‍ j <= m;‌‍ j ++) {‌‍
                id[i][j] = ++ tot;‌‍
                if(((i + j) & 1) && g[i][j] != '?') g[i][j] ^= '.' ^ '#';‌‍ // 把黑白染色中同色的翻转
            }‌‍
        }‌‍
        S = ++ tot, T = ++ tot;‌‍
        G.init(S, T, T);‌‍
        for(int i = 0;‌‍ i <= n;‌‍ i ++) {‌‍
            for(int j = 0;‌‍ j <= m;‌‍ j ++) {‌‍
                if(g[i][j] == '.') G.add_edge(S, id[i][j], 4);‌‍
                if(g[i][j] == '#') G.add_edge(id[i][j], T, 4);‌‍
                for(int k = 0;‌‍ k < 2;‌‍ k ++) {‌‍
                    int x = i + dx[k], y = j + dy[k];‌‍
                    if(x >= 0 && x <= n && y >= 0 && y <= m) G.add_edge(id[i][j], id[x][y], 1, 1);‌‍ // 这里直接把两条边合在一起建，会快一点 104 ms -> 67 ms
                }‌‍
            }‌‍
        }‌‍
        printf("Case #%d: %d\n", C, n * (m + 1) + m * (n + 1) - G.dinic());‌‍ // 总对数 - 最小割
    }‌‍
    return 0;‌‍
}‌‍
```
:::

---

