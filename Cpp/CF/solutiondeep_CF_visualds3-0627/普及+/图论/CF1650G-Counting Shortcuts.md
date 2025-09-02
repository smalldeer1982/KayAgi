# 题目信息

# Counting Shortcuts

## 题目描述

Given an undirected connected graph with $ n $ vertices and $ m $ edges. The graph contains no loops (edges from a vertex to itself) and multiple edges (i.e. no more than one edge between each pair of vertices). The vertices of the graph are numbered from $ 1 $ to $ n $ .

Find the number of paths from a vertex $ s $ to $ t $ whose length differs from the shortest path from $ s $ to $ t $ by no more than $ 1 $ . It is necessary to consider all suitable paths, even if they pass through the same vertex or edge more than once (i.e. they are not simple).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650G/3360dade3a147f98c6dd4b25980520a2ae6123a6.png)Graph consisting of $ 6 $ of vertices and $ 8 $ of edgesFor example, let $ n = 6 $ , $ m = 8 $ , $ s = 6 $ and $ t = 1 $ , and let the graph look like the figure above. Then the length of the shortest path from $ s $ to $ t $ is $ 1 $ . Consider all paths whose length is at most $ 1 + 1 = 2 $ .

- $ 6 \rightarrow 1 $ . The length of the path is $ 1 $ .
- $ 6 \rightarrow 4 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 2 \rightarrow 1 $ . Path length is $ 2 $ .
- $ 6 \rightarrow 5 \rightarrow 1 $ . Path length is $ 2 $ .

There is a total of $ 4 $ of matching paths.

## 样例 #1

### 输入

```
4

4 4
1 4
1 2
3 4
2 3
2 4

6 8
6 1
1 4
1 6
1 5
1 2
5 6
4 6
6 3
2 6

5 6
1 3
3 5
5 4
3 1
4 2
2 1
1 4

8 18
5 1
2 1
3 1
4 2
5 2
6 5
7 3
8 4
6 4
8 7
1 4
4 7
1 6
6 7
3 8
8 5
4 5
4 3
8 2```

### 输出

```
2
4
1
11```

# AI分析结果



## 算法分类
**最短路计数 + 分层 BFS**

---

## 题解思路与核心难点

### 核心思路
题目要求统计从起点 `s` 到终点 `t` 的最短路和次短路（长度恰好多1）的路径总数。核心思路分为两步：
1. **分层 BFS**：从 `s` 和 `t` 分别进行 BFS，计算每个节点的最短距离和路径数。
2. **枚举层内边**：次短路必须经过一条层内边（连接同一层的两个节点）。通过枚举这些边，验证其是否满足条件，并累加路径数。

### 解决难点
- **次短路的性质**：严格证明次短路必须且只能包含一条层内边，避免重复或遗漏。
- **高效计数**：通过预处理 `s` 和 `t` 的最短路径数，用乘法原理快速统计贡献。

---

## 题解评分（≥4星）

1. **StudyingFather（★★★★★）**  
   - 亮点：思路清晰，两次 BFS 预处理后直接枚举边，代码高效简洁。
   - 关键代码：
     ```cpp
     void bfs(int s, int* dis, int* f) {
         // BFS 计算最短路及路径数
     }
     for (每条边 (u, v)) {
         if (u 和 v 是层内边) {
             // 检查条件并累加贡献
         }
     }
     ```

2. **char_phi（★★★★☆）**  
   - 亮点：动态规划状态设计巧妙，按层处理避免重复。
   - 个人心得：初始 DFS 因转移顺序错误导致问题，改用分层 BFS 后正确。

3. **daniEl_lElE（★★★★☆）**  
   - 亮点：分层 BFS 转移状态，分阶段处理同层边和下层边。

---

## 最优思路提炼

### 关键步骤
1. **两次 BFS 预处理**：
   - 从 `s` 出发，计算每个节点的最短距离 `dis1` 和路径数 `f1`。
   - 从 `t` 出发，计算 `dis2` 和 `f2`。
2. **枚举层内边**：
   - 对于每条边 `(u, v)`，若 `dis1[u] == dis1[v]`，则检查是否满足 `dis1[u] + 1 + dis2[v] == 最短路长度 + 1`，累加 `f1[u] * f2[v]` 和 `f1[v] * f2[u]`。

### 代码片段
```cpp
void bfs(int s, int* dis, int* f) {
    queue<int> q;
    memset(dis, -1, sizeof(int) * (n + 1));
    memset(f, 0, sizeof(int) * (n + 1));
    dis[s] = 0, f[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : e[u]) {
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                f[v] = f[u];
                q.push(v);
            } else if (dis[v] == dis[u] + 1) {
                f[v] = (f[v] + f[u]) % mod;
            }
        }
    }
}
```

---

## 相似题目推荐
1. **P1144 最短路计数**  
   - 基础最短路计数问题，适合练习 BFS 或 Dijkstra 的变形。
2. **P1608 路径统计**  
   - 含权图的最短路计数，需注意重复边处理。
3. **P2865 Roadblocks**  
   - 求次短路，与本题思路类似。

---

## 可视化设计

### 算法演示
- **像素风格动画**：在 Canvas 上用网格表示图，节点颜色表示距离，边颜色表示类型（层间/层内）。
- **关键高亮**：
  - 红色：当前处理的层内边。
  - 绿色：满足条件的边，显示 `f1[u] * f2[v]` 计算过程。
- **控制面板**：支持暂停/继续、调整动画速度。

### 复古音效
- **步进音效**：每处理一条边时播放“哔”声。
- **成功音效**：找到有效边时播放上扬音调。

---

## 总结
最优解法通过两次 BFS 和层内边枚举，高效解决了次短路计数问题。其核心在于利用图的层次性质，将问题转化为简单的条件检查和乘法原理应用，适合快速实现和扩展。

---
处理用时：95.47秒