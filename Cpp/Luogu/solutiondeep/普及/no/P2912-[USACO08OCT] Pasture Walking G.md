# 题目信息

# [USACO08OCT] Pasture Walking G

## 题目描述

The N cows (2 <= N <= 1,000) conveniently numbered 1..N are grazing among the N pastures also conveniently numbered 1..N. Most conveniently of all, cow i is grazing in pasture i.

Some pairs of pastures are connected by one of N-1 bidirectional walkways that the cows can traverse. Walkway i connects pastures A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N) and has a length of L\_i (1 <= L\_i <= 10,000).

The walkways are set up in such a way that between any two distinct pastures, there is exactly one path of walkways that travels between them. Thus, the walkways form a tree.

The cows are very social and wish to visit each other often. Ever in a hurry, they want you to help them schedule their visits by computing the lengths of the paths between 1 <= L\_i <= 10,000 pairs of pastures (each pair given as a query p1,p2 (1 <= p1 <= N; 1 <= p2 <= N).

POINTS: 200

有N(2<=N<=1000)头奶牛，编号为1到W，它们正在同样编号为1到N的牧场上行走.为了方 便，我们假设编号为i的牛恰好在第i号牧场上.

有一些牧场间每两个牧场用一条双向道路相连，道路总共有N - 1条，奶牛可以在这些道路 上行走.第i条道路把第Ai个牧场和第Bi个牧场连了起来(1 <= A\_i <= N; 1 <= B\_i <= N)，而它的长度 是 1 <= L\_i <= 10,000.在任意两个牧场间，有且仅有一条由若干道路组成的路径相连.也就是说，所有的道路构成了一棵树.

奶牛们十分希望经常互相见面.它们十分着急，所以希望你帮助它们计划它们的行程，你只 需要计算出Q(1 < Q < 1000)对点之间的路径长度•每对点以一个询问p1,p2 (1 <= p1 <= N; 1 <= p2 <= N). 的形式给出.



## 说明/提示

Query 1: The walkway between pastures 1 and 2 has length 2.

Query 2: Travel through the walkway between pastures 3 and 4, then the one between 4 and 1, and finally the one between 1 and 2, for a total length of 7.


## 样例 #1

### 输入

```
4 2 
2 1 2 
4 3 2 
1 4 3 
1 2 
3 2 
```

### 输出

```
2 
7 
```

# AI分析结果



### 算法分类
图论（LCA应用）

### 综合分析与结论
题目要求多次查询树上两点路径长度。核心思路是通过预处理节点到根的距离并结合最近公共祖先（LCA）计算路径长度。关键点在于利用LCA将路径分解为两段到根的路径之差，时间复杂度优化为O(n logn)预处理 + O(logn)查询。

---

### 精选题解

#### 1. **Watermatter（倍增LCA）** ★★★★★
- **关键亮点**：清晰的倍增实现，注释详细，代码结构规范。
- **核心思路**：预处理每个节点的深度、到根的距离及倍增祖先。查询时通过倍增调整节点至同深度后求LCA，距离公式为`dist[u] + dist[v] - 2 * dist[lca]`。
- **代码核心**：
```cpp
void dfs(int u,int fa,int dis) {
    depth[u] = depth[fa] + 1;
    f[u][0] = fa; 
    val[u] = val[fa] + dis; // 到根的距离
    for(int i = 1; (1<<i) <= depth[u]; i++)
        f[u][i] = f[f[u][i-1]][i-1];
    // 遍历邻接点...
}

int lca(int x, int y) {
    if(depth[x] < depth[y]) swap(x,y);
    for(int i=19; i>=0; i--) // 调整至同深度
        if(depth[f[x][i]] >= depth[y]) x = f[x][i];
    if(x == y) return x;
    for(int i=19; i>=0; i--) // 同时上跳找LCA
        if(f[x][i] != f[y][i]) x=f[x][i], y=f[y][i];
    return f[x][0];
}
```

#### 2. **顾z（带权倍增）** ★★★★☆
- **关键亮点**：显式维护向上跳跃的边权，适合带权路径问题。
- **实现要点**：维护`gw[i][j]`表示节点i向上2^j步的边权和，计算路径时累加跳跃的权值。
```cpp
for(int j=1; (1<<j)<=n; j++)
    for(int i=1; i<=n; i++)
        gw[i][j] = gw[i][j-1] + gw[f[i][j-1]][j-1];
```

#### 3. **Dijkspfa（Tarjan离线LCA）** ★★★★☆
- **优化点**：离线处理所有查询，DFS过程中动态合并并查集，常数更优。
- **技巧**：利用并查集记录已访问节点的父节点，查询时直接计算距离差。

---

### 关键技巧总结
1. **LCA选择**：倍增法平衡了实现难度与效率，树剖适合频繁查询，Tarjan适合离线场景。
2. **路径分解**：`dist(u,v) = dist(root,u) + dist(root,v) - 2*dist(root,lca)`。
3. **预处理优化**：深度、父节点、权值数组的预处理是核心，确保快速跳跃。

### 拓展练习
1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. [P3884 [JLOI2009] 二叉树问题](https://www.luogu.com.cn/problem/P3884)
3. [P1395 会议](https://www.luogu.com.cn/problem/P1395)

---
处理用时：54.82秒