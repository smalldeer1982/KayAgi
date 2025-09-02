# 题目信息

# Kostyanych's Theorem

## 题目描述

This is an interactive problem.

Kostyanych has chosen a complete undirected graph $ ^{\dagger} $ with $ n $ vertices, and then removed exactly $ (n - 2) $ edges from it. You can ask queries of the following type:

- "? $ d $ " — Kostyanych tells you the number of vertex $ v $ with a degree at least $ d $ . Among all possible such vertices, he selects the vertex with the minimum degree, and if there are several such vertices, he selects the one with the minimum number. He also tells you the number of another vertex in the graph, with which $ v $ is not connected by an edge (if none is found, then $ 0 $ is reported). Among all possible such vertices, he selects the one with the minimum number. Then he removes the vertex $ v $ and all edges coming out of it. If the required vertex $ v $ is not found, then " $ 0\ 0 $ " is reported.

Find a Hamiltonian path $ ^{\ddagger} $ in the original graph in at most $ n $ queries. It can be proven that under these constraints, a Hamiltonian path always exists.

 $ ^{\dagger} $ A complete undirected graph is a graph in which there is exactly one undirected edge between any pair of distinct vertices. Thus, a complete undirected graph with $ n $ vertices contains $ \frac{n(n-1)}{2} $ edges.

 $ ^{\ddagger} $ A Hamiltonian path in a graph is a path that passes through each vertex exactly once.

## 说明/提示

In the first test case, the original graph looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979F/42089518245c2488c2bfecf2fe23dadea3c789e8.png)Consider the queries:

- There are no vertices with a degree of at least $ 3 $ in the graph, so " $ 0\ 0 $ " is reported.
- There are four vertices with a degree of at least $ 2 $ , and all of them have a degree of exactly $ 2 $ : $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ . Vertex $ 1 $ is reported, because it has the minimum number, and vertex $ 4 $ is reported, because it is the only one not connected to vertex $ 1 $ . After this, vertex $ 1 $ is removed from the graph.
- There are three vertices with a degree of at least $ 1 $ , among them vertices $ 2 $ and $ 3 $ have a minimum degree of $ 1 $ (vertex $ 4 $ has a degree of $ 2 $ ). Vertex $ 2 $ is reported, because it has the minimum number, and vertex $ 3 $ is reported, because it is the only one not connected to vertex $ 2 $ . After this, vertex $ 2 $ is removed from the graph.

The path $ 4 - 3 - 1 - 2 $ is a Hamiltonian path.

In the second test case, the original graph looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979F/8d69c71de95e98946d0d15367d0511bf08d2ba0a.png)Consider the queries:

- Vertex $ 1 $ has a degree of at least $ 3 $ , but it is connected to all vertices, so " $ 1\ 0 $ " is reported. After this, vertex $ 1 $ is removed from the graph.
- The remaining vertices $ 2 $ , $ 3 $ , and $ 4 $ have a degree of at least $ 0 $ , but among them vertex $ 4 $ has the minimum degree of $ 0 $ (vertices $ 2 $ and $ 3 $ have a degree of $ 1 $ ). Vertex $ 4 $ is not connected to both vertices $ 2 $ and $ 3 $ , so vertex $ 2 $ is reported (as it has the minimum number). After this, vertex $ 4 $ is removed from the graph.

The path $ 4 - 1 - 2 - 3 $ is a Hamiltonian path.

In the third test case, the graph consists of $ 2 $ vertices connected by an edge.

## 样例 #1

### 输入

```
3
4

0 0

1 4

2 3

4

1 0

4 2

2

1 0```

### 输出

```
? 3

? 2

? 1

! 4 3 1 2

? 3

? 0

! 4 1 2 3

? 0

! 2 1```

# AI分析结果



## 算法分类
**构造算法**

---

## 题解思路与算法要点

### 核心思路
1. **递归分解**：每次询问较大的度数阈值（如 `d = n-2`），根据响应判断是否存在高度数顶点：
   - 若存在度数为 `n-2` 的顶点 `u`，递归处理剩余图，并将 `u` 连接到路径的端点。
   - 若不存在，则存在度数为 `n-1` 的顶点 `u`，需额外找到一个低度数顶点 `p`，并递归处理更小规模的子图。

2. **双端队列维护路径**：使用 `deque` 动态维护路径两端，根据顶点 `u` 的连接情况选择在队列前端或后端插入。

### 解决难点
- **度数分类讨论**：通过询问 `d = n-2` 确定是否存在关键顶点，避免暴力枚举。
- **路径动态拼接**：利用递归性质，将大问题分解为子问题，通过队列操作保证路径连续性。
- **交互式删点**：每次询问后顶点被删除，需保证后续递归的正确性。

---

## 题解评分 (≥4星)

### 1. sunzz3183 [★★★★★]
- **思路清晰**：详细数学证明支撑递归策略，代码简洁。
- **代码可读性**：使用 `deque` 维护路径，逻辑明确。
- **实践性**：直接处理交互逻辑，适合快速实现。

### 2. CCPSDCGK [★★★★☆]
- **数学严谨性**：通过引理证明哈密顿路径存在的必然性。
- **代码简洁**：短小精悍，但缺少详细注释。

### 3. daniEl_lElE [★★★★☆]
- **数据结构优化**：利用 `set` 维护剩余顶点，递归终止条件明确。
- **代码简洁性**：省略部分细节，适合高手参考。

---

## 最优思路提炼

### 关键技巧
1. **递归参数动态调整**：通过 `d` 的递减逐步缩小问题规模。
2. **双端队列动态拼接**：根据 `v` 是否匹配路径端点决定插入方向。
3. **交互式顶点删除**：利用系统自动删除顶点的特性，避免重复处理。

### 代码片段
```cpp
void dfs(int d) {
    if (d < -1) return;
    if (d == -1) { // 终止条件：处理最后一个顶点
        query(0);
        q.push_back(u);
        return;
    }
    query(d); // 询问度数阈值 d
    if (v) { // 存在度数为 d 的顶点 u
        dfs(d - 1);
        if (q.front() == v) q.push_front(u);
        else q.push_back(u);
    } else { // 不存在，处理度数 n-1 的顶点 u 和低度数顶点 p
        int x = u;
        query(0); // 找到低度数顶点 p
        int y = u;
        dfs(d - 2); // 递归处理剩余顶点
        q.push_back(x);
        q.push_back(y);
    }
}
```

---

## 类似题目与扩展
1. **洛谷 P1763**（哈密顿回路构造）
2. **洛谷 P2730**（特定结构图路径搜索）
3. **CodeForces 862B**（二分图构造）

---

## 可视化设计

### 动画方案
1. **递归层次展示**：以树状图展示递归层级，当前层用绿色高亮。
2. **双端队列操作**：用左右箭头表示插入方向，队列元素颜色渐变表示插入顺序。
3. **顶点状态标记**：
   - 红色：已删除顶点。
   - 蓝色：当前处理顶点。
   - 绿色：路径中的顶点。

### 复古像素风格
- **8位音效**：每次查询播放 `8-bit` 音效，路径拼接成功时播放胜利音效。
- **Canvas 绘制**：网格化展示顶点和边，删除顶点时显示爆炸像素动画。

---

## 总结
本题通过递归分解和双端队列动态拼接，高效利用交互特性构造哈密顿路径。核心在于通过度数阈值快速定位关键顶点，并利用递归维护路径的正确性。

---
处理用时：64.08秒