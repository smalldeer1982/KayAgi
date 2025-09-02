# 题目信息

# [USACO10FEB] Chocolate Giving S

## 题目描述

FJ 有 $B$ 头奶牛 $(1\le B\le 25000)$，有 $N(2\times B\le N\le 50000)$ 个农场，编号 $1$ 到 $N$，有 $M(N-1\le M\le 100000)$ 条双向边，第 $i$ 条边连接农场 $R_i$ 和 $S_i(1\le R_i\le N, 1\le S_i\le N)$，该边的长度是 $L_i(1\le L_i\le 2000)$。居住在农场 $P_i$ 的奶牛 A $(1\le P_i\le N)$，想送一份新年礼物给居住在农场 $Q_i(1\le Q_i\le N)$ 的奶牛 B，但是奶牛 A 必须先到 FJ（居住在编号 $1$ 的农场）那里取礼物，然后再送给奶牛 B。你的任务是：奶牛 A 至少需要走多远的路程？

## 样例 #1

### 输入

```
6 7 3 
1 2 3 
5 4 3 
3 1 1 
6 1 9 
3 4 2 
1 4 4 
3 2 2 
2 4 
5 1 
3 6 
```

### 输出

```
6 
6 
10 
```

# AI分析结果

### 综合分析与结论

本题的核心是求解从奶牛A到FJ再到奶牛B的最短路径。由于图是无向的，且所有路径都要经过FJ（编号为1的农场），因此可以将问题转化为从FJ出发，分别求解到奶牛A和奶牛B的最短路径之和。大多数题解都采用了这一思路，避免了重复计算，提升了效率。

在算法选择上，Dijkstra和SPFA是最常用的两种方法。Dijkstra在时间复杂度上更为稳定，而SPFA在某些情况下可能更快，但容易被卡。题解中大部分使用了Dijkstra的堆优化版本，确保了较高的效率。

### 所选高星题解

#### 1. 封禁用户 (5星)
**关键亮点**：
- 使用Dijkstra堆优化，确保了算法的高效性。
- 代码结构清晰，注释详细，易于理解。
- 通过一次Dijkstra计算所有点到FJ的最短路径，避免了重复计算。

**个人心得**：
- 强调了无向图的性质，避免了不必要的路径计算。
- 通过优先队列优化Dijkstra，提升了运行效率。

**核心代码**：
```cpp
void dijkstra(int s) {
    priority_queue<P, vector<P>, greater<P>> q;
    for (int i = 1; i <= n; i++) d[i] = 1e9;
    d[s] = 0;
    q.push(P{0, s});
    while (!q.empty()) {
        P p = q.top(); q.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (int i = 0; i < G[v].size(); i++) {
            edge e = G[v][i];
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                q.push(P{d[e.to], e.to});
            }
        }
    }
}
```

#### 2. L_Y_T (4星)
**关键亮点**：
- 通过多次调试和优化，最终实现了高效的SPFA算法。
- 强调了无向图的性质，避免了重复计算。

**个人心得**：
- 通过多次提交和调试，最终发现了无向图的性质，避免了不必要的路径计算。

**核心代码**：
```cpp
void spfa(int s) {
    queue<int> q;
    for (int i = 1; i <= n; i++) dis[i] = inf;
    dis[s] = 0;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = a[i].next) {
            int v = a[i].y;
            if (dis[v] > dis[u] + a[i].z) {
                dis[v] = dis[u] + a[i].z;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}
```

#### 3. 小糯米 (4星)
**关键亮点**：
- 使用了Dijkstra的堆优化版本，确保了算法的高效性。
- 通过一次Dijkstra计算所有点到FJ的最短路径，避免了重复计算。

**个人心得**：
- 强调了无向图的性质，避免了不必要的路径计算。

**核心代码**：
```cpp
void dijkstra(int start) {
    priority_queue<State> q;
    for (long long i = 1; i <= n; ++i) d[i] = 2147483647;
    d[start] = 0;
    for (long long i = 1; i <= n; ++i) nps[i] = ph.insert(State{d[i], i});
    while (!ph.isEmpty()) {
        State ts;
        ph.deleteMin(ts);
        long long u = ts.nid;
        d[u] = ts.dis;
        nps[u] = nullptr;
        for (long long i = 0; i < g[u].size(); ++i) {
            long long v = g[u][i].v, w = g[u][i].w;
            if (d[v] > d[u] + w && nps[v] != nullptr) {
                d[v] = d[u] + w;
                ph.decreaseKey(nps[v], State{d[v], v});
            }
        }
    }
}
```

### 最优关键思路与技巧

1. **无向图的性质**：由于图是无向的，从A到FJ的最短路径等于从FJ到A的最短路径，因此只需一次Dijkstra或SPFA即可。
2. **Dijkstra堆优化**：通过优先队列优化Dijkstra，确保算法的高效性。
3. **避免重复计算**：通过一次计算所有点到FJ的最短路径，避免了多次调用最短路径算法的开销。

### 可拓展之处

- **类似算法套路**：在无向图中，若需要多次查询某点到其他点的最短路径，可以通过一次Dijkstra或SPFA预处理，避免重复计算。
- **同类型题**：类似的最短路径问题可以通过预处理和优化算法来提高效率。

### 推荐题目

1. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

---
处理用时：48.63秒