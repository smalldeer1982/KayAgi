# 题目信息

# Envy

## 题目描述

For a connected undirected weighted graph $ G $ , MST (minimum spanning tree) is a subgraph of $ G $ that contains all of $ G $ 's vertices, is a tree, and sum of its edges is minimum possible.

You are given a graph $ G $ . If you run a MST algorithm on graph it would give you only one MST and it causes other edges to become jealous. You are given some queries, each query contains a set of edges of graph $ G $ , and you should determine whether there is a MST containing all these edges or not.

## 说明/提示

This is the graph of sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891C/d7f37868e211da76f9c523f75a033c3f4d56f21c.png)Weight of minimum spanning tree on this graph is $ 6 $ .

MST with edges $ (1,3,4,6) $ , contains all of edges from the first query, so answer on the first query is "YES".

Edges from the second query form a cycle of length $ 3 $ , so there is no spanning tree including these three edges. Thus, answer is "NO".

## 样例 #1

### 输入

```
5 7
1 2 2
1 3 2
2 3 1
2 4 1
3 4 1
3 5 2
4 5 2
4
2 3 4
3 3 4 5
2 1 7
2 1 2
```

### 输出

```
YES
NO
YES
NO
```

# AI分析结果



## 算法分类
**最小生成树 (Kruskal算法) + 并查集**

---

## 综合分析与结论

### 核心思路与难点
**题目本质**：判断给定边集是否能同时存在于某个最小生成树中。  
**核心性质**：
1. 所有最小生成树中，每个权值的边数量固定。
2. 处理完比某权值小的所有边后，图的连通性唯一确定。

**关键算法流程**：
1. **预处理**：运行Kruskal算法，记录每条边在加入所有更小权值边后的连通块状态（即两端点的并查集根）。
2. **查询处理**：对每个查询的边按权值分组，模拟在对应权值的连通状态下合并，检查是否成环。
3. **动态并查集**：每次处理完一个权值的边后重置并查集，避免状态污染。

**解决难点**：如何高效处理多个查询中的动态连通性检查。通过预处理和按权值分层处理，将复杂度优化至与查询规模相关。

---

## 题解清单 (≥4星)

1. **wuzhaoxin（5星）**  
   **亮点**：  
   - 预处理每条边的连通块状态，查询时直接模拟合并操作。  
   - 代码简洁高效，按权值分组处理，利用临时并查集快速重置。  
   **核心代码**：预处理每条边的`tx`和`ty`，查询时按权值排序并检查环。

2. **GKxx（4.5星）**  
   **亮点**：  
   - 离线处理查询，使用可撤销并查集分层处理不同权值。  
   - 通过栈保存操作状态，确保各查询独立处理。  
   **核心代码**：离线排序查询边，按权值处理并动态合并/撤销。

3. **ZCETHAN（4星）**  
   **亮点**：  
   - 代码结构清晰，直接利用Kruskal预处理结果。  
   - 动态维护并查集状态，快速处理查询中的合并与重置。  
   **核心代码**：预处理边权后，对查询边分组处理并检查连通性。

---

## 最优思路与技巧提炼

**核心步骤**：
1. **预处理连通块**：通过Kruskal算法预处理每条边在加入所有更小权值边后的连通块根节点。
2. **权值分层检查**：对查询边按权值分组，每组内部独立检查是否成环。
3. **动态并查集重置**：每组处理完毕后，通过双指针或栈回滚操作，实现并查集快速重置。

**关键技巧**：
- **按权值分层处理**：不同权值的边互不影响，可独立处理。
- **轻量级并查集**：仅维护当前权值相关的连通块状态，避免全量重置。
- **离线排序优化**：通过排序减少冗余操作，提升处理效率。

---

## 类似题目推荐

1. **P3366 【模板】最小生成树**  
   **关键词**：Kruskal算法基础应用，验证边是否在MST中。

2. **P1967 货车运输**  
   **关键词**：最大生成树与路径最小值查询，可结合并查集与倍增。

3. **P4180 [BJWC2010] 严格次小生成树**  
   **关键词**：MST性质扩展，处理严格次小边替换问题。

---

## 可视化与算法演示

**动画设计**：
1. **分步Kruskal预处理**：  
   - 按权值升序逐步合并边，高亮当前处理的边。  
   - 颜色标记不同连通块，动态显示合并过程。

2. **查询边模拟合并**：  
   - 按权值分组，为每组分配不同颜色。  
   - 动态显示并查集合并过程，若成环则触发红色闪烁提示。

3. **复古像素风格**：  
   - **颜色方案**：8位色调色板（绿：连通块，红：环，黄：当前操作边）。  
   - **音效**：合并成功（清脆音效），成环（低沉音效），重置（回声音效）。  
   - **Canvas网格**：节点以像素方块表示，边动态绘制为连线。

**交互功能**：
- **步进控制**：允许暂停/继续，调整动画速度。  
- **自动演示**：AI模式自动遍历所有查询，展示正确与错误案例。  
- **关卡积分**：每通过一个查询获得积分，连续正确触发连击奖励。

---

## 核心代码实现（wuzhaoxin解法）

```cpp
// 预处理部分：记录每条边在更小权值边处理后的连通块根
for(int i = 1; i <= m;) {
    int j = i;
    do {
        e[j].tx = find(e[j].x);
        e[j].ty = find(e[j].y);
        j++;
    } while(j <= m && e[j].val == e[j - 1].val);
    while(i < j) {
        if(find(e[i].x) != find(e[i].y)) merge(e[i].x, e[i].y);
        i++;
    } 
}

// 查询处理：按权值分组检查环
vector<edge> v;
sort(v.begin(), v.end());
bool flag = 1;
for(int i = 0; i < v.size() && flag;) {
    if(v[i].x == v[i].y) { flag = 0; break; }
    merge(v[i].x, v[i].y);
    int j = i + 1;
    while(j < v.size() && v[j].val == v[i].val) {
        if(find(v[j].x) == find(v[j].y)) { flag = 0; break; }
        merge(v[j].x, v[j].y); j++;
    }
    while(i < j) { // 重置并查集
        fa[v[i].x] = v[i].x; 
        fa[v[i].y] = v[i].y; 
        i++;
    }
}
```

---

## 个人心得摘录

> **调试踩坑**：预处理时未正确处理相同权值边的连续处理，导致部分边未被正确记录连通状态。  
> **优化顿悟**：按权值分层后，每组查询独立处理，无需全局重置并查集，仅需回滚相关操作。  
> **思维突破**：不同权值边独立处理的性质大幅简化问题复杂度，避免动态维护全局状态。

---
处理用时：75.26秒