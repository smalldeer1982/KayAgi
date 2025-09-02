# 题目信息

# Connectivity Addicts

## 题目描述

This is an interactive problem.

Given a simple undirected graph with $ n $ vertices numbered from $ 1 $ to $ n $ , your task is to color all the vertices such that for every color $ c $ , the following conditions hold:

1. The set of vertices with color $ c $ is connected;
2. $ s_c \leq n_c^2 $ , where $ n_c $ is the number of vertices with color $ c $ , and $ s_c $ is the sum of degrees of vertices with color $ c $ .

 It can be shown that there always exists a way to color all the vertices such that the above conditions hold. Initially, you are only given the number $ n $ of vertices and the degree of each vertex.

In each query, you can choose a vertex $ u $ . As a response, you will be given the $ k $ -th edge incident to $ u $ , if this is the $ k $ -th query on vertex $ u $ .

You are allowed to make at most $ n $ queries.

An undirected graph is simple if it does not contain multiple edges or self-loops.

The degree of a vertex is the number of edges incident to it.

A set $ S $ of vertices is connected if for every two different vertices $ u, v \in S $ , there is a path, which only passes through vertices in $ S $ , that connects $ u $ and $ v $ . That is, there is a sequence of edges $ (u_1, v_1), (u_2, v_2), \dots, (u_k, v_k) $ with $ k \geq 1 $ such that

1. $ u_1 = u $ , $ v_k = v $ , and $ v_i = u_{i+1} $ for every $ 1 \leq i < k $ ; and
2. $ u_k \in S $ and $ v_k \in S $ for every $ 1 \leq i \leq k $ .

 Especially, a set containing only one vertex is connected.

## 说明/提示

In the example, there is only one test case.

In the test case, there are $ n = 5 $ vertices with vertices $ 1, 2, 3, 4 $ of degree $ 2 $ and vertex $ 5 $ of degree $ 0 $ . It is obvious that vertex $ 5 $ is isolated, i.e., it does not connect to any other vertices.

A possible interaction is shown in the sample input and output, where $ 4 $ "?" queries are made on vertex $ 1 $ twice and vertex $ 3 $ twice. According to the responses to these queries, we know that each of vertex $ 1 $ and vertex $ 3 $ connects to two vertices $ 2 $ and $ 4 $ .

A possible solution is shown in the sample output, where vertex $ 1 $ and vertex $ 2 $ are colored by $ 1 $ , vertex $ 3 $ and vertex $ 4 $ are colored by $ 2 $ , and vertex $ 5 $ is colored by $ 3 $ . It can be seen that this solution satisfies the required conditions as follows.

- For color $ c = 1 $ , vertex $ 1 $ and vertex $ 2 $ are connected. Moreover, $ n_1 = 2 $ and $ s_1 = d_1 + d_2 = 2 + 2 = 4 \leq n_1^2 = 2^2 = 4 $ ;
- For color $ c = 2 $ , vertex $ 3 $ and vertex $ 4 $ are connected. Moreover, $ n_2 = 2 $ and $ s_2 = d_3 + d_4 = 2 + 2 = 4 \leq n_2^2 = 2^2 = 4 $ ;
- For color $ c = 3 $ , there is only one vertex (vertex $ 5 $ ) colored by $ 3 $ . Moreover, $ n_3 = 1 $ and $ s_3 = d_5 = 0 \leq n_3^2 = 1^2 = 1 $ .

## 样例 #1

### 输入

```
1
5
2 2 2 2 0

2

4

2

4```

### 输出

```
? 1

? 1

? 3

? 3

! 1 1 2 2 3```

# AI分析结果



---

### 综合分析与结论

**题目核心**：在交互限制下，构造满足连通性约束（每个颜色块连通且度数总和 ≤ 块大小的平方）的图染色方案。  
**关键难点**：如何在有限查询次数内确定连通结构，并保证数学条件。  
**核心解法**：贪心策略基于度数排序，每次处理当前最大度数的未染色节点，通过查询其邻接点动态合并或新建颜色块。  
**贪心策略验证**：度数最大的节点所在连通块的大小至少为其度数 +1，从而保证 $\max_{u \in S} d_u \leq |S|$，进而满足 $s_c \leq n_c^2$。  
**可视化设计**：  
- **动画方案**：以像素网格展示节点，按度数从大到小排序后逐个处理，高亮当前节点并逐步查询邻接点。  
- **颜色标记**：已染色节点显示为不同颜色块，新查询的邻接点动态合并到对应颜色。  
- **音效交互**：查询邻接点时播放"点击"音效，合并颜色时播放"融合"音效，成功染色后播放胜利音效。  
- **8位风格**：节点用像素方块表示，颜色渐变以区分不同连通块，控制面板支持步进/自动播放。

---

### 题解清单 (≥4星)

1. **周子衡（4星）**  
   - **亮点**：提出度数最大节点的合法性引理，代码实现简洁高效，时间复杂度 $O(n)$。  
   - **关键代码**：按度数排序后逐个处理，动态合并颜色块。  
   - **引用**：“显见给出的染色方案是合法的。总询问次数 $=n-$ 最后的颜色数 < $n$。”

2. **Alex_Wei（4星）**  
   - **亮点**：深入分析菊花图结构的合法性，提出删除已处理节点的优化思路。  
   - **关键思想**：“任意时刻连通块大小大于其中所有节点的最大度数。”

3. **liangbowen（4星）**  
   - **亮点**：将条件转化为 $\max deg \leq |S|$，构造方法直观。  
   - **代码亮点**：直接按度数排序后处理邻居，实现简单。

---

### 最优思路与技巧提炼

1. **贪心排序策略**：按度数从大到小处理节点，确保当前处理的节点是未染色的最大度数节点。  
2. **动态合并机制**：查询邻接点时，若遇到已染色节点则立即合并，减少查询次数。  
3. **合法性保证**：每个颜色块的 $\max_{u \in S} d_u \leq |S|$，由度数排序和合并顺序自然满足。  
4. **查询优化**：每个节点的查询次数不超过其度数，总次数 $\leq n$。

---

### 同类型题目与算法套路

**通用贪心场景**：  
- **区间覆盖**：选择覆盖范围最大的区间。  
- **任务调度**：优先处理耗时最短或收益最高的任务。  
- **图连通性构造**：通过最大度/关键节点保证连通性。

**洛谷推荐题目**：  
1. P1231 教辅的分配（贪心匹配）  
2. P1969 积木大赛（区间覆盖贪心）  
3. P5021 赛道修建（树形贪心构造）

---

### 代码核心实现

```cpp
// 周子衡题解核心代码（简化）
sort(id + 1, id + n + 1, [&](int x, int y) { return d[x] > d[y]; });
for (int i = 1; i <= n; i++) {
    if (!col[id[i]]) {
        int u = id[i];
        vector<int> neighbors;
        for (int j = 1; j <= d[u]; j++) {
            cout << "? " << u << endl;
            int v; cin >> v;
            neighbors.push_back(v);
            if (col[v]) break; // 遇到已染色节点则终止查询
        }
        int cur_col = col[neighbors.back()] ? col[neighbors.back()] : ++color_cnt;
        col[u] = cur_col;
        for (int v : neighbors) col[v] = cur_col; // 合并邻接点
    }
}
```

---

### 可视化与游戏化设计

1. **像素风格布局**：  
   - 每个节点为 32x32 像素方块，初始颜色按度数深浅渐变（深红→浅红）。  
   - 当前处理节点闪烁显示，查询邻接点时显示连线动画。

2. **交互控制面板**：  
   - **播放/暂停**：控制动画进度。  
   - **步进按钮**：单步执行每次查询或合并操作。  
   - **速度调节**：滑动条控制动画速度（0.5x~3x）。

3. **音效系统**：  
   - **查询音效**：8-bit "beep" 声。  
   - **合并音效**：短促合成音。  
   - **完成音效**：经典 FC 过关音乐。

4. **自动演示模式**：  
   - AI 模拟最优查询顺序，高亮显示每次决策逻辑。  
   - 状态栏显示当前颜色块数和剩余查询次数。

**示例代码片段（Canvas 绘制）**：  
```javascript
function drawNode(ctx, node, color) {
    ctx.fillStyle = color;
    ctx.fillRect(node.x * 40, node.y * 40, 32, 32);
    ctx.strokeStyle = '#000';
    ctx.strokeRect(node.x * 40, node.y * 40, 32, 32);
}
```

---

### 个人心得摘录

- **周子衡**：“显见染色方案合法”——强调贪心策略的天然正确性，无需复杂证明。  
- **liangbowen**：“duel 时对上了脑电波”——体现对问题模式的直觉培养重要性。  
- **Sol1**：“冷静一下会发现超出操作次数”——调试时需严格验证边界条件。

---
处理用时：77.80秒