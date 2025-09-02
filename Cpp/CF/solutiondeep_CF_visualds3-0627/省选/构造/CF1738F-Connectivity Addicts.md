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



## 算法分类
**贪心算法**

---

## 题解思路与核心算法分析

### 核心思路
所有题解均围绕以下关键点展开：
1. **度数排序**：将顶点按度数从大到小排序，优先处理度数大的顶点。
2. **贪心染色**：对于每个未染色的顶点，通过查询其邻接点，合并到已存在的颜色或新建颜色块。
3. **连通性保证**：每次处理顶点时，确保其所在颜色块的连通性和度数约束条件。

### 解决难点
- **度数约束条件**：通过排序保证后续合并的块中最大度数 ≤ 当前块大小。
- **查询次数限制**：每次处理顶点时，最多查询其度数次，总次数不超过 `n`。
- **动态合并**：利用并查集或颜色标记动态维护连通块。

### 算法流程
1. **初始化**：按度数排序顶点。
2. **遍历处理**：
   - 对每个未染色的顶点 `u`，依次查询其邻接点。
   - 若邻接点已染色，则将 `u` 及其邻接点合并到该颜色。
   - 否则新建颜色，标记所有邻接点。
3. **终止条件**：所有顶点染色完成。

---

## 题解评分（≥4星）

1. **周子衡（★★★★☆）**  
   - **亮点**：理论证明完整，通过引理明确保证条件成立。
   - **代码关键点**：直接按度数排序，动态维护颜色块。

2. **zac2010（★★★★☆）**  
   - **亮点**：代码简洁高效，通过排序和邻接点查询快速合并。
   - **代码片段**：
     ```cpp
     sort(id + 1, id + n + 1, cmp);
     FL(i, 1, n) if(!c[id[i]]){
         vector<int> v;
         FL(j, 1, d[id[i]]){
             cout << "? " << id[i] << endl;
             cin >> u; if(c[u]) break;
             v.emplace_back(u);
         }
         c[id[i]] = c[u]? c[u] : ++col;
         for(const int &x: v) c[x] = c[id[i]];
     }
     ```

3. **Sol1（★★★★☆）**  
   - **亮点**：使用并查集维护连通块，优化合并效率。
   - **代码关键点**：动态更新并查集，减少重复查询。

---

## 最优思路提炼
**贪心染色 + 度数排序 + 动态合并**  
1. **度数排序**：从大到小处理，确保后续合并时度数条件自动满足。
2. **邻接点查询**：每次处理顶点时，优先合并到已存在的颜色块。
3. **动态维护**：通过并查集或颜色标记快速合并连通块。

---

## 类似题目推荐
1. **CF1316E Team Building**（贪心选择 + 动态规划）
2. **CF1490G Old Floppy Drive**（贪心构造 + 数学分析）
3. **Luogu P1550 [USACO08OCT] Watering Hole G**（并查集 + 贪心）

---

## 可视化设计

### 动画方案
1. **像素风格界面**：
   - **颜色块**：不同颜色用8-bit色块区分（如16色调色板）。
   - **顶点显示**：顶点以圆点表示，内部显示度数，按度数从大到小排列。
   - **操作高亮**：当前处理的顶点用闪烁边框标记，查询的邻接点用箭头连接。

2. **流程演示**：
   - **Step 1**：排序顶点，显示初始度数。
   - **Step 2**：处理顶点 `u`，查询邻接点 `v`，若 `v` 已染色，合并颜色块。
   - **Step 3**：新建颜色块时播放“合成音效”，合并时播放“连接音效”。

3. **交互功能**：
   - **速度调节**：滑块控制动画速度（0.5x~3x）。
   - **单步执行**：允许用户逐帧观察合并过程。
   - **音效触发**：每次查询或合并时触发8-bit音效。

### 代码片段（Canvas绘制示例）
```javascript
// 绘制顶点
function drawVertex(ctx, x, y, color, degree) {
    ctx.fillStyle = COLORS[color % 16];
    ctx.beginPath();
    ctx.arc(x, y, 20, 0, 2 * Math.PI);
    ctx.fill();
    ctx.fillStyle = "#000";
    ctx.font = "16px Arial";
    ctx.textAlign = "center";
    ctx.fillText(degree, x, y + 5);
}
```

---

## 总结
本题通过贪心策略和度数排序，结合动态合并机制，在有限查询次数内构造合法解。核心难点在于理论证明和高效实现，而可视化设计通过像素风格和音效增强了算法理解。

---
处理用时：60.36秒