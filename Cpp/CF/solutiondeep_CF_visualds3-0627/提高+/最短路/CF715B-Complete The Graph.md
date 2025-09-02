# 题目信息

# Complete The Graph

## 题目描述

ZS the Coder has drawn an undirected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ m $ edges between them. Each edge of the graph is weighted, each weight is a positive integer.

The next day, ZS the Coder realized that some of the weights were erased! So he wants to reassign positive integer weight to each of the edges which weights were erased, so that the length of the shortest path between vertices $ s $ and $ t $ in the resulting graph is exactly $ L $ . Can you help him?

## 说明/提示

Here's how the graph in the first sample case looks like :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715B/c442fd279761bfa74ef367b518cede1e1fa97983.png)In the first sample case, there is only one missing edge weight. Placing the weight of $ 8 $ gives a shortest path from $ 0 $ to $ 4 $ of length $ 13 $ .

In the second sample case, there is only a single edge. Clearly, the only way is to replace the missing weight with $ 123456789 $ .

In the last sample case, there is no weights to assign but the length of the shortest path doesn't match the required value, so the answer is "NO".

## 样例 #1

### 输入

```
5 5 13 0 4
0 1 5
2 1 2
3 2 3
1 4 0
4 3 4
```

### 输出

```
YES
0 1 5
2 1 2
3 2 3
1 4 8
4 3 4
```

## 样例 #2

### 输入

```
2 1 123456789 0 1
0 1 0
```

### 输出

```
YES
0 1 123456789
```

## 样例 #3

### 输入

```
2 1 999999999 1 0
0 1 1000000000
```

### 输出

```
NO
```

# AI分析结果



---

**算法分类**: 最短路算法（Dijkstra）

---

### **题解思路与算法要点**

#### **核心思路**
题目要求通过调整未知边权（原值为 0 的边），使得 $s \to t$ 的最短路恰好等于 $L$。核心难点在于动态调整边权时保证最短路长度精确匹配目标值。最优解法采用两次 Dijkstra 算法：
1. **第一次 Dijkstra**：将所有未知边权设为 1，计算最短路径。若此时最短路已超过 $L$，则无解。
2. **第二次 Dijkstra**：在遍历过程中动态调整未知边权，确保最终最短路长度等于 $L$。

#### **解决难点**
- **动态调整边权**：第二次 Dijkstra 中，若某未知边位于当前最短路径上，则调整其权值，使得该边的权值恰好补足与目标值的差值。
- **数学推导**：设第一次最短路长度为 $D_0$，需补足的差值为 $dif = L - D_0$。调整边权时，保证 $dis[x] + w + dif \geq dis[y]$，从而逐步逼近目标值。

#### **关键实现代码**
```cpp
// 第一次 Dijkstra：计算初始最短路
dijkstra(s);
if (dis[t] > L) return puts("NO");

// 第二次 Dijkstra：动态调整边权
dif = L - dis[t];
dijkstra_adjust(s);

// 调整边权的逻辑
for (每条边 u->v) {
    if (该边是未知边 && dis[u] + w < dis[v] + dif) {
        w = dis[v] + dif - dis[u];
    }
}
```

---

### **题解评分 (≥4星)**

| 题解作者       | 评分 | 关键亮点                                 |
|----------------|------|------------------------------------------|
| zhenliu        | ★★★★☆ | 两次 Dijkstra 思路清晰，代码可读性强       |
| SmallTownKid   | ★★★★☆ | 贪心策略直观，适合理解动态调整过程         |
| phmaprostrate  | ★★★★  | 分类讨论完整，SPFA 实现效率较高           |

---

### **最优思路提炼**
- **两次 Dijkstra 法**：通过两次最短路计算，第一次验证可行性，第二次动态调整边权。
- **差值补足**：利用 $dif = L - D_0$，在第二次遍历中调整边权，确保最终路径长度精确等于 $L$。
- **动态更新边权**：在松弛操作中直接修改未知边权，避免多次全局计算。

---

### **同类型题推荐**
1. [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)  
   **考察点**：基础 Dijkstra 实现。
2. [P4779 单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)  
   **考察点**：堆优化 Dijkstra 算法。
3. [P1186 玛丽卡](https://www.luogu.com.cn/problem/P1186)  
   **考察点**：动态调整边权后的最短路更新。

---

### **可视化与算法演示**

#### **动画设计**
1. **初始状态**：展示所有边（实线为已知边，虚线为未知边），初始权值为 1。
2. **第一次 Dijkstra**：以绿色高亮松弛路径，红色标记无法到达的节点。
3. **差值计算**：显示 $dif = L - D_0$ 的公式推导。
4. **第二次 Dijkstra**：动态调整边权时，用黄色闪烁当前边，显示权值更新公式 $w = dis[v] + dif - dis[u]$。
5. **最终路径**：用蓝色标记 $s \to t$ 的最短路径，显示长度 $L$。

#### **复古像素风格**
- **颜色方案**：8 位色系，绿色表示安全路径，红色表示错误，黄色表示调整中的边。
- **音效设计**：  
  - **松弛成功**：短促“滴”声。  
  - **调整边权**：8-bit 键盘音效。  
  - **达成目标**：经典 FC 过关音效。

---

### **核心代码实现**
```cpp
// 动态调整边权的 Dijkstra 实现
void dijkstra_adjust(int s) {
    priority_queue<Node> pq;
    memset(dis_adjust, 0x3f, sizeof(dis_adjust));
    dis_adjust[s] = 0;
    pq.push({s, 0});
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int u = cur.u;
        if (cur.dist > dis_adjust[u]) continue;
        for (Edge& e : graph[u]) {
            int v = e.v, w = e.w;
            if (e.is_zero) { // 动态调整未知边权
                w = max(w, dis_initial[v] + dif - dis_adjust[u]);
                e.w = w; // 更新权值
            }
            if (dis_adjust[v] > dis_adjust[u] + w) {
                dis_adjust[v] = dis_adjust[u] + w;
                pq.push({v, dis_adjust[v]});
            }
        }
    }
}
```

---

### **个人心得摘录**
- **调试教训**：初始未考虑多条未知边共同影响最短路，导致调整不充分。需确保每次调整覆盖所有可能路径。
- **优化顿悟**：动态调整边权时，只需保证当前路径的松弛条件，无需全局重新计算。

---

**总结**：通过两次 Dijkstra 算法，结合动态边权调整，高效解决了最短路径精确匹配问题。可视化设计通过复古风格和交互式动画，显著提升算法理解深度。

---
处理用时：75.66秒