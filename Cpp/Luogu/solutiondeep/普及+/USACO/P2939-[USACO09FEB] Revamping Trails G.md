# 题目信息

# [USACO09FEB] Revamping Trails G

## 题目描述

Farmer John dutifully checks on the cows every day. He traverses some of the M (1 <= M <= 50,000) trails conveniently numbered 1..M from pasture 1 all the way out to pasture N (a journey which is always possible for trail maps given in the test data). The N (1 <= N <= 10,000) pastures conveniently numbered 1..N on Farmer John's farm are currently connected by bidirectional dirt trails.  Each trail i connects pastures P1\_i and P2\_i (1 <= P1\_i <= N; 1 <= P2\_i <= N) and requires T\_i (1 <= T\_i <= 1,000,000) units of time to traverse.

He wants to revamp some of the trails on his farm to save time on his long journey. Specifically, he will choose K (1 <= K <= 20) trails to turn into highways, which will effectively reduce the trail's traversal time to 0. Help FJ decide which trails to revamp to minimize the resulting time of getting from pasture 1 to N.

TIME LIMIT: 2 seconds



## 说明/提示

K is 1; revamp trail 3->4 to take time 0 instead of 100. The new shortest path is 1->3->4, total traversal time now 1.


## 样例 #1

### 输入

```
4 4 1 
1 2 10 
2 4 10 
1 3 1 
3 4 100 
```

### 输出

```
1 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕分层图最短路算法解决问题，核心思路是将图分层，每层代表使用不同次数升级路的机会，通过连边构建分层图，再使用最短路算法（如 Dijkstra 或 SPFA）求解。部分题解采用动态规划思想结合最短路算法。不同题解在代码实现、数组大小处理、最短路算法选择及分层图构建细节上存在差异。

### 所选题解
- **作者：QQQfy（4星）**
    - **关键亮点**：详细解释了分层图的概念、意义和应用范围，代码注释清晰，对分层图的边权定义讲解透彻。
    - **个人心得**：提到很久以前想学分层图但找不到易于理解的教程，旨在为和自己一样的蒟蒻提供良好体验。
- **作者：齐天の小猴（4星）**
    - **关键亮点**：思路清晰，先阐述分层图的构建原理，再给出代码实现，对数组大小的处理有合理说明。
    - **个人心得**：多次题解未过，分层图最短路最近才学会，写的不好希望不要被喷。
- **作者：Diamiko（4星）**
    - **关键亮点**：以通俗易懂的语言解释分层图，对建图细节和数组大小计算有详细说明，代码注释丰富。
    - **个人心得**：以通俗易懂的讲法来让朋友们明白，自认为算比较详细的。

### 重点代码及核心实现思想
#### 分层图构建
```cpp
// 以 QQQfy 题解为例
for (int i = 1; i <= m; i++)
{
    int u, v, cost;
    cin >> u >> v >> cost;
    add(u, v, cost); add(v, u, cost);
    for (int j = 1; j <= k; j++)
    {
        add(n * j + u, n * j + v, cost); add(n * j + v, n * j + u, cost);
        add(n * (j - 1) + u, n * j + v, 0); add(n * (j - 1) + v, n * j + u, 0);
    }
}
```
**核心思想**：先构建原图的边，再复制 k 层图，每层图内部的边权与原图相同，相邻两层图之间的边权为 0，表示使用一次升级路的机会。

#### Dijkstra 算法
```cpp
// 以 QQQfy 题解为例
struct node
{
    int u, dis;
    bool operator<(const node x) const
    {
        return dis > x.dis;
    }
};

priority_queue<node> q;
int dist[maxn * 21];

void dij(int s)
{
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    q.push((node){s, 0});
    while (!q.empty())
    {
        node fr = q.top(); q.pop();
        int u = fr.u, dis = fr.dis;
        if (dis != dist[u]) continue;
        for (int v = head[u]; v; v = nextt[v])
            if (dist[to[v]] > dist[u] + w[v])
            {
                dist[to[v]] = dist[u] + w[v];
                q.push((node){to[v], dist[to[v]]});
            }
    }
}
```
**核心思想**：使用优先队列优化的 Dijkstra 算法，不断更新节点的最短距离，直到队列为空。

### 最优关键思路或技巧
- **分层图思想**：将图分层，每层代表不同的状态，通过连边构建分层图，将问题转化为普通的最短路问题。
- **优先队列优化**：在最短路算法中使用优先队列，提高算法效率。
- **数组大小处理**：考虑到分层图的节点和边数增加，合理设置数组大小，避免数组越界。

### 可拓展之处
同类型题或类似算法套路：
- 可以改变边权的最短路问题，如某些边可以免费通过一定次数。
- 图的状态可以改变的问题，如在不同时间点图的结构或边权不同。

### 推荐题目
- [P4568 [JLOI2011]飞行路线](https://www.luogu.org/problem/P4568)
- [P4822 [BJWC2012]冻结](https://www.luogu.org/problem/P4822)
- [P1948 [USACO08JAN]电话线Telephone Lines](https://www.luogu.org/problem/P1948)

### 个人心得总结
- 部分作者提到分层图学习困难，缺乏易于理解的教程，希望自己的题解能帮助其他蒟蒻。
- 有的作者多次题解未过，反映出写题解的不易。
- 一些作者在调试过程中遇到问题，如数组大小设置不当、Dijkstra 堆写错等，提醒我们在编程时要注意细节。

---
处理用时：39.06秒