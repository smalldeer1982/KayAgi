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
这些题解主要围绕求无向连通图中两点间最短路径上的顶点集合展开，采用了多种最短路算法，如Floyd、Dijkstra、SPFA、BFS等。
- **思路对比**：大部分题解思路是先求出两点间最短路，再通过判断中间点是否满足特定条件（如中间点到起点和终点的距离之和等于起点到终点的最短距离）来确定其是否在最短路径上；部分题解采用记录前驱节点、迭代加深搜索等方法。
- **算法要点**：
    - **Floyd**：通过三重循环更新任意两点间的最短距离，适用于多源最短路问题，代码简洁，但时间复杂度为$O(n^3)$。
    - **Dijkstra**：单源最短路算法，可使用优先队列优化，时间复杂度为$O((n + m)\log n)$。
    - **SPFA**：单源最短路算法，在稀疏图中表现较好，但可能会被特殊数据卡到$O(nm)$。
    - **BFS**：适用于无权图，时间复杂度为$O(n + m)$。
- **解决难点**：主要难点在于判断哪些点在最短路径上，多数题解通过距离关系判断，部分题解通过记录前驱节点回溯得到最短路径上的点。

### 高评分题解
1. **作者：06ray (赞：44)，5星**
    - **关键亮点**：思路清晰，详细阐述了使用邻接表存储图和SPFA算法求最短距离的过程，代码注释丰富，易于理解。
    - **个人心得**：无
    - **核心代码**：
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
核心思想：使用SPFA算法求单源最短路，通过队列不断更新节点的最短距离。

2. **作者：かなで (赞：19)，4星**
    - **关键亮点**：提出BFS做法，在求最短路过程中记录前驱节点，从终点倒着搜得到答案，思路独特，时间复杂度相对较低。
    - **个人心得**：无
    - **核心代码**：
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
核心思想：使用BFS求最短路，记录每个节点的前驱节点，从终点倒着搜索得到最短路径上的点。

3. **作者：_Blue_ (赞：6)，4星**
    - **关键亮点**：使用Floyd算法解决多源最短路问题，思路清晰，代码简洁，通过优先队列对结果进行排序。
    - **个人心得**：之前觉得Floyd时间复杂度高没学，做这题后使用Floyd解决了问题。
    - **核心代码**：
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
核心思想：使用Floyd算法求任意两点间的最短距离，通过枚举中间点判断其是否在最短路径上。

### 最优关键思路或技巧
- **距离判断法**：若中间点到起点和终点的距离之和等于起点到终点的最短距离，则该中间点在最短路径上。
- **记录前驱节点**：在求最短路过程中记录每个节点的前驱节点，从终点倒着搜索可得到最短路径上的点。

### 可拓展之处
- **同类型题**：求有向图中两点间最短路径上的顶点集合、求带权图中最短路径上的顶点集合等。
- **类似算法套路**：在求最短路问题中，可根据图的特点选择合适的算法，如稀疏图用Dijkstra或SPFA，稠密图用Floyd；在判断节点是否在最短路径上，可利用距离关系或记录前驱节点的方法。

### 推荐题目
1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
2. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
3. [P2888 [USACO07NOV]Cow Hurdles S](https://www.luogu.com.cn/problem/P2888)

### 个人心得总结
- _Blue_：之前因觉得Floyd时间复杂度高而没学，做这题时使用Floyd解决了问题，说明在合适的场景下应尝试不同算法。

---
处理用时：41.65秒