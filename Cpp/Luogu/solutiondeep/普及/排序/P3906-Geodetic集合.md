# 题目信息

# Geodetic集合

## 题目描述

图 $\text G$ 是一个无向连通图，没有自环，并且两点之间至多只有一条边。我们定义顶点 $v,u$ 的最短路径就是从 $v$ 到 $u$ 经过边最少的路径。所有包含在 $v-u$ 的最短路径上的顶点被称为 $v-u$ 的 Geodetic 顶点，这些顶点的集合记作 $I(v,u)$。

我们称集合 $I(v,u)$ 为一个 Geodetic 集合。

例如下图中，$I(2,5)=\{2,3,4,5\}$，$I(1,5)=\{1,3,5\}$，$I(2,4)=\{2,4\}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/26c7a19d.png)

给定一个图 $\text G$ 和若干点对 $v,u$，请你分别求出 $I(v,u)$。

## 说明/提示

对于所有数据，满足 $1\leqslant n\leqslant 40$，$1\leqslant m\leqslant \frac{n(n-1)}2$。

## 样例 #1

### 输入

```
5 6
1 2
1 3
2 3
2 4
3 5
4 5
3
2 5
5 1
2 4```

### 输出

```
2 3 4 5
1 3 5
2 4```

# AI分析结果

### 综合分析与结论
本题主要求解无向连通图中给定两点的 Geodetic 集合，即两点最短路径上的顶点集合。题解主要采用了多种最短路算法，包括 Floyd、SPFA、Dijkstra 以及 BFS、DFS 搜索算法。
- **Floyd 算法**：通过三重循环求出任意两点间的最短距离，然后对于每个询问，枚举中间点判断是否在最短路径上。优点是代码简单，能处理多源最短路问题，时间复杂度稳定为 $O(n^3)$；缺点是对于大规模数据效率较低。
- **SPFA 算法**：使用队列优化的 Bellman - Ford 算法，通过多次松弛操作更新最短距离。优点是适用于稀疏图，能处理负权边；缺点是可能会被特殊数据卡到最坏情况。
- **Dijkstra 算法**：使用优先队列优化，每次选择距离源点最近的点进行松弛操作。优点是时间复杂度较稳定，适用于无负权边的图；缺点是代码相对复杂。
- **BFS 和 DFS 算法**：BFS 用于无权图求最短路径，DFS 用于回溯寻找路径。优点是思路直观；缺点是对于大规模数据可能会超时。

### 高评分题解
- **作者：06ray（5星）**
    - **关键亮点**：思路清晰，详细阐述了使用邻接表存储图和 SPFA 算法求最短距离的过程，代码注释丰富，可读性强。
    - **个人心得**：无
- **作者：かなで（4星）**
    - **关键亮点**：提出了 BFS 做法，在求最短路过程中记录前驱，通过倒搜得到答案，时间复杂度相对较优，代码简洁。
    - **个人心得**：指出题解几乎全是 Floyd，质疑无权图用 SPFA 的必要性。
- **作者：_Blue_（4星）**
    - **关键亮点**：使用 Floyd 算法，思路清晰，代码简洁，对核心判断条件有详细解释。
    - **个人心得**：感慨之前因觉得 Floyd 复杂度高而没学，体现了对算法学习的反思。

### 重点代码及核心思想
#### 作者：06ray
```cpp
void spfa(int s) {
    queue<int>q;
    fill(d + 1, d + n + 1, 100000000);
    fill(used + 1, used + n + 1, false);
    d[s] = 0;
    used[s] = true;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        used[v] = false;
        for (int i = 0; i < G[v].size(); i++) {
            node e = G[v][i];
            if (d[v] + e.cost < d[e.to]) {
                d[e.to] = d[v] + e.cost;
                if (!used[e.to]) {
                    q.push(e.to);
                    used[e.to] = true;
                }
            }
        }
    }
}
```
**核心思想**：使用 SPFA 算法求单源最短路径，通过队列不断更新最短距离。

#### 作者：かなで
```cpp
void bfs(int s, int t) {
    memset(num, 0, sizeof num), memset(dis, 63, sizeof dis);
    dis[s] = 0, q.push(s);
    while (!q.empty()) {
        s = q.front(), q.pop();
        for (int i = 1; i <= n; i++) if (a[s][i])
            if (dis[i] > dis[s] + 1)
                dis[i] = dis[s] + 1, pre[i][++num[i]] = s, q.push(i);
            else if (dis[i] == dis[s] + 1) pre[i][++num[i]] = s;
    }
    memset(ans, 0, sizeof ans), q.push(t), ans[t] = 1;
    while (!q.empty()) {
        s = q.front(), q.pop();
        for (int i = num[s]; i; i--) if (!ans[pre[s][i]])
            ans[pre[s][i]] = 1, q.push(pre[s][i]);
    }
    for (int i = 1; i <= n; i++) if (ans[i]) printf("%d ", i);
}
```
**核心思想**：BFS 求最短路径，记录前驱，从终点倒搜得到答案。

#### 作者：_Blue_
```cpp
for (int k = 1; k <= n; k++) {
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= n; i++) {
            if (i == j || i == k || j == k) continue;
            f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            f[j][i] = min(f[j][i], f[j][k] + f[k][i]);
        }
    }
}
for (int k = 1; k <= n; k++) {
    if (k == x || k == y) continue;
    if (f[x][y] == f[x][k] + f[k][y])  
        q.push(k);
}
```
**核心思想**：Floyd 算法求任意两点间最短距离，枚举中间点判断是否在最短路径上。

### 最优关键思路或技巧
- **判断点是否在最短路径上**：若点 $i$ 满足 $dis[u][i] + dis[i][v] = dis[u][v]$，则点 $i$ 在 $u$ 到 $v$ 的最短路径上。
- **数据结构选择**：根据图的稀疏程度选择合适的数据结构存储图，如邻接表适用于稀疏图，邻接矩阵适用于稠密图。
- **算法选择**：根据数据规模和图的特点选择合适的最短路算法，如数据规模小可使用 Floyd 算法，稀疏图可使用 SPFA 或 Dijkstra 算法。

### 拓展思路
- **同类型题**：求两点间最短路径上的边集合、求最短路径的数量等。
- **类似算法套路**：在最短路算法基础上增加额外信息的记录，如前驱节点、路径数量等，通过回溯或枚举判断满足条件的元素。

### 推荐题目
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：涉及 Floyd 算法的动态更新。
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：考察 Dijkstra 或 SPFA 算法。
- [P2850 [USACO06DEC]River Hopscotch S](https://www.luogu.com.cn/problem/P2850)：涉及二分查找和最短路思想。

### 个人心得总结
- **_Blue_**：之前因觉得 Floyd 复杂度高而没学，在做本题时才使用，体现了对算法学习应全面了解的感悟。
- **かなで**：质疑无权图用 SPFA 的必要性，提醒我们在选择算法时要根据问题特点进行合理选择。 

---
处理用时：51.08秒