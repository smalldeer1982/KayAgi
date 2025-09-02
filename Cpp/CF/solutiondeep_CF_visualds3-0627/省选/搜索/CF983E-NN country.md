# 题目信息

# NN country

## 题目描述

In the NN country, there are $ n $ cities, numbered from $ 1 $ to $ n $ , and $ n - 1 $ roads, connecting them. There is a roads path between any two cities.

There are $ m $ bidirectional bus routes between cities. Buses drive between two cities taking the shortest path with stops in every city they drive through. Travelling by bus, you can travel from any stop on the route to any other. You can travel between cities only by bus.

You are interested in $ q $ questions: is it possible to get from one city to another and what is the minimum number of buses you need to use for it?

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF983E/c42b59e68a69956240c890e5363c8c983d1d430c.png) Routes for first sample are marked on the picture.

## 样例 #1

### 输入

```
7
1 1 1 4 5 6
4
4 2
5 4
1 3
6 7
6
4 5
3 5
7 2
4 5
3 2
5 3
```

### 输出

```
1
3
-1
1
2
3
```

## 样例 #2

### 输入

```
7
1 1 2 3 4 1
4
4 7
3 5
7 6
7 6
6
4 6
3 1
3 2
2 7
6 3
5 3
```

### 输出

```
1
-1
-1
1
-1
1
```

# AI分析结果



## 算法分类：其他搜索（树形结构上的倍增与二维数点）

---

### 题解思路与算法要点

1. **核心算法架构**  
   - **倍增预处理**：为每个节点预处理向上跳跃的倍增数组，用于快速跳到 LCA 附近  
   - **DFS 序转化**：将子树查询转化为区间查询，便于二维数点处理  
   - **二维数点优化**：通过主席树/树状数组快速判断是否存在跨 LCA 的公交线路  

2. **搜索算法关键点**  
   - **搜索发起**：通过 DFS 预处理每个节点的父节点、深度、子树区间  
   - **剪枝策略**：预处理每个节点能到达的最浅祖先（通过公交线路优化跳跃步数）  
   - **数据结构**：  
     - 邻接表存储树结构  
     - 主席树维护公交线路的二维坐标（DFS 序区间）  
     - 倍增数组 `g[i][j]` 表示节点 i 向上跳 2^j 步的最浅位置  

3. **解决难点**  
   - **跳跃终止条件**：在 LCA 附近停止跳跃后，需判断是否存在跨子树公交线路  
   - **高效区间查询**：通过二维数点将 O(n) 查询优化至 O(logn)  

---

### 题解评分（≥4星）

1. **Acfboy（★★★★☆）**  
   - **亮点**：主席树实现简洁，代码逻辑清晰，完整实现跳跃与查询流程  
   - **关键代码**：  
     ```cpp
     // 主席树插入与查询核心逻辑
     void add(int &rt, int l, int r, int x) { ... }
     int Query(int rt, int l, int r, int x, int y) { ... }
     ```

2. **EuphoricStar（★★★★☆）**  
   - **亮点**：离线树状数组处理二维数点，避免动态数据结构的内存开销  
   - **关键代码**：  
     ```cpp
     // 树状数组离线处理
     for (int i=1;i<=cnt;i++) {
         while (now<=n && P[now] <= T[i].x) update(T[i].y), now++;
         res += T[i].val * query(...);
     }
     ```

3. **Mobius127（★★★★☆）**  
   - **亮点**：代码模块化程度高，分离 LCA 计算与二维数点逻辑，便于调试  
   - **关键代码**：  
     ```cpp
     // 二维数点与跳跃分离处理
     int ans = dx + dy + 2;
     if (Query(dfn[u], dfn[v])) ans--;
     ```

---

### 最优思路与技巧提炼

1. **倍增跳跃模板**  
   ```cpp
   for (int j=19; j>=0; j--) {
       if (dep[g[u][j]] > dep[LCA]) u = g[u][j], ans += (1<<j);
   }
   ```
   - 从高位向低位枚举跳跃步数，快速接近 LCA  

2. **DFS 序区间映射**  
   ```cpp
   dfs(u); // 预处理 dfn[u] 和 ed[u]
   bool in_subtree(int x, int y) {
       return dfn[x] <= dfn[y] && dfn[y] <= ed[x];
   }
   ```
   - 将子树判定转化为区间包含关系  

3. **二维数点优化**  
   ```cpp
   // 主席树版本
   rt[i] = rt[i-1];
   for (auto y : bus[p[i]]) add(rt[i], 1, n, y);
   ```
   - 按 DFS 序插入节点，实现前缀区间查询  

---

### 同类型题与算法套路

1. **类似问题**  
   - **树上路径覆盖**：判断路径是否被若干子路径覆盖  
   - **跳跃优化查询**：利用倍增/二分快速逼近目标  

2. **通用解法**  
   - **DFS 序 + 线段树**：处理子树相关查询  
   - **倍增预处理**：快速跳跃至目标区域  

---

### 推荐练习题

1. **P3379【模板】最近公共祖先（LCA）**  
   - 练习 LCA 的多种实现方式（倍增、Tarjan、树剖）  

2. **CF 342E Xenia and Tree**  
   - 结合 BFS 与树分块处理动态最近黑节点查询  

3. **P3302 [SDOI2013]森林**  
   - 树上路径查询与主席树结合的高级应用  

---

### 可视化与算法演示

**动画设计**：  
1. **树结构绘制**：Canvas 绘制树形结构，节点按 DFS 遍历顺序排列  
2. **跳跃过程**：高亮当前跳跃路径，显示倍增步数（如红色箭头表示跳跃方向）  
3. **二维数点演示**：在右侧平面坐标系中显示公交线路点，查询时绘制矩形区域  
4. **音效反馈**：跳跃时播放 "beep" 音效，查询命中时播放 "ding"  

**复古像素风格**：  
- **颜色方案**：16 色调色板，绿色表示已访问节点，黄色表示待访问  
- **音效设计**：8-bit 风格音效，使用 Web Audio API 触发  
- **自动演示**：AI 自动执行跳跃与查询，按空格键暂停/继续  

---

### 关键代码片段

**倍增预处理核心**  
```cpp
void dfs_pre(int u) {
    for (int j=1; j<=19; j++) {
        g[u][j] = g[g[u][j-1]][j-1];
    }
    for (int v : tree[u]) {
        dfs_pre(v);
    }
}
```

**二维数点查询（树状数组离线）**  
```cpp
struct Event { int x, y, val, id; };
vector<Event> events;
sort(events.begin(), events.end(), [](auto a, auto b) {
    return a.x < b.x;
});
for (auto [x,y,val,id] : events) {
    while (ptr <= x) update(y_array[ptr++]);
    res[id] += val * query(y);
}
```

---

### 总结

本题通过 **DFS 序转化** 和 **倍增优化** 将复杂路径查询拆解为高效子问题，结合 **二维数点** 实现快速判定。不同题解在实现细节（主席树 vs 树状数组）上各有优劣，但核心思想一致。可视化设计可帮助理解跳跃与区间查询的关联性。

---
处理用时：80.13秒