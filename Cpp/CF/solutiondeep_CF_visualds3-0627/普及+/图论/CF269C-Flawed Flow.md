# 题目信息

# Flawed Flow

## 题目描述

Emuskald considers himself a master of flow algorithms. Now he has completed his most ingenious program yet — it calculates the maximum flow in an undirected graph. The graph consists of $ n $ vertices and $ m $ edges. Vertices are numbered from 1 to $ n $ . Vertices $ 1 $ and $ n $ being the source and the sink respectively.

However, his max-flow algorithm seems to have a little flaw — it only finds the flow volume for each edge, but not its direction. Help him find for each edge the direction of the flow through this edges. Note, that the resulting flow should be correct maximum flow.

More formally. You are given an undirected graph. For each it's undirected edge ( $ a_{i} $ , $ b_{i} $ ) you are given the flow volume $ c_{i} $ . You should direct all edges in such way that the following conditions hold:

1. for each vertex $ v $ $ (1&lt;v&lt;n) $ , sum of $ c_{i} $ of incoming edges is equal to the sum of $ c_{i} $ of outcoming edges;
2. vertex with number $ 1 $ has no incoming edges;
3. the obtained directed graph does not have cycles.

## 说明/提示

In the first test case, 10 flow units pass through path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/112cc3d7bc5d5ae260d516a02ced6ab796839bee.png), and 5 flow units pass directly from source to sink: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269C/851f40f264708d94590f3171217fe3d9e053dcee.png).

## 样例 #1

### 输入

```
3 3
3 2 10
1 2 10
3 1 5
```

### 输出

```
1
0
1
```

## 样例 #2

### 输入

```
4 5
1 2 10
1 3 10
2 3 5
4 2 15
3 4 5
```

### 输出

```
0
0
1
1
0
```

# AI分析结果



---

**唯一算法分类**：拓扑排序

---

### **题解思路、算法要点与解决难点**

#### **核心思路**
1. **流量平衡与拓扑排序**  
   - 中间节点总流量为所有边流量之和，必须为偶数（入流=出流=总流量/2）。  
   - 通过拓扑排序依次处理节点，维护剩余流量 `f[i]`，当 `f[i]` 归零时加入队列，确保无环。

2. **方向确定**  
   - 从源点出发，每次处理当前节点的所有未定向边，调整邻接节点的剩余流量。  
   - 边方向由处理顺序决定（如 `u→v` 或 `v→u`），反向边标记为无效。

#### **解决难点**
- **无环保证**：拓扑排序顺序确保每个节点在处理时，所有可能的入边已被处理，避免成环。  
- **流量维护**：通过 `f[i] -= 2*w` 操作快速调整邻接节点的剩余流量（两倍边权抵消原统计的总流量）。

---

### **题解评分 (≥4星)**

1. **灵茶山艾府（⭐⭐⭐⭐⭐）**  
   - **亮点**：代码简洁，直接维护 `f[i]` 并利用队列处理节点，逻辑清晰。  
   - **核心代码**：  
     ```go
     for _, e := range g[v] {
         if ans[e.i] == -1 {
             ans[e.i] = e.d
             f[e.to] -= e.f
             if f[e.to] == 0 { q.append(e.to) }
         }
     }
     ```

2. **OIer_ACMer（⭐⭐⭐⭐）**  
   - **亮点**：预处理反向边标记，通过 `liuliang[v] -= 2 * e.w` 快速调整流量。  
   - **个人心得**：强调反向边标记的重要性，防止重复处理。

3. **SFlyer（⭐⭐⭐⭐）**  
   - **亮点**：通过 `id>m` 判断方向，代码简洁高效。  
   - **核心代码**：  
     ```cpp
     ans[(id>m?(id-m):id)] = (id>m);
     deg[y] -= c;
     if (deg[y] == 0) q.push(y);
     ```

---

### **最优思路或技巧提炼**

- **拓扑排序+BFS**：通过队列维护待处理的平衡节点，确保无环构造。  
- **流量减半操作**：中间节点的总流量除以 2 作为入流/出流阈值。  
- **方向标记与反向边无效化**：处理边后立即标记反向边，避免重复计算。

---

### **同类型题或类似算法套路**

- **拓扑排序应用**：如课程表问题（LeetCode 207）、任务调度（LeetCode 210）。  
- **DAG构造**：如边定向使图无环（Codeforces 1180B）。

---

### **推荐洛谷题目**

1. **P1113 杂务**（拓扑排序基础）  
2. **P2742 [USACO5.1] 圈奶牛**（几何+图论构造）  
3. **P3376 【模板】网络最大流**（网络流基础，理解流量方向）

---

### **可视化与算法演示**

#### **动画方案**
- **节点状态**：  
  - **绿色**：已处理（`f[i]=0`）。  
  - **黄色**：正在处理（队列头部）。  
  - **红色**：未处理。  
- **边方向**：动态绘制箭头，处理时高亮当前边。  
- **流量显示**：节点旁显示 `f[i]` 的实时数值。

#### **复古游戏化设计**
- **8位像素风格**：节点为 16x16 像素方块，边为彩色线条。  
- **音效**：  
  - **处理节点**：短促“哔”声。  
  - **完成定向**：上扬音效。  
- **自动演示**：按队列顺序逐步处理，支持暂停/加速。

---

### **代码核心逻辑**

以 **灵茶山艾府** 的 Golang 代码为例：  
```go
// 初始化流量 f[i] = sum(c) / 2
for i := range f {
    f[i] >>= 1
}

// BFS处理节点队列
q := []int{1}
for len(q) > 0 {
    v := q[0]
    q = q[1:]
    for _, e := range g[v] {
        if ans[e.i] == -1 {
            ans[e.i] = e.d      // 标记方向
            f[e.to] -= e.f      // 调整邻接节点流量
            if f[e.to] == 0 {   // 平衡后入队
                q = append(q, e.to)
            }
        }
    }
}
```

---

### **总结**

本题通过拓扑排序思想，结合流量平衡条件，逐步确定边方向并保证无环。核心在于维护剩余流量和队列处理顺序，适合用 BFS 实现。可视化设计可突出节点状态和队列变化，复古风格增强理解趣味性。

---
处理用时：79.32秒