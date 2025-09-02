# 题目信息

# The Chocolate Spree

## 题目描述

Alice and Bob have a tree (undirected acyclic connected graph). There are $ a_{i} $ chocolates waiting to be picked up in the $ i $ -th vertex of the tree. First, they choose two different vertices as their starting positions (Alice chooses first) and take all the chocolates contained in them.

Then, they alternate their moves, selecting one vertex at a time and collecting all chocolates from this node. To make things more interesting, they decided that one can select a vertex only if he/she selected a vertex adjacent to that one at his/her previous turn and this vertex has not been already chosen by any of them during other move.

If at any moment one of them is not able to select the node that satisfy all the rules, he/she will skip his turns and let the other person pick chocolates as long as he/she can. This goes on until both of them cannot pick chocolates any further.

Due to their greed for chocolates, they want to collect as many chocolates as possible. However, as they are friends they only care about the total number of chocolates they obtain together. What is the maximum total number of chocolates they may pick?

## 说明/提示

In the first sample, Alice may start at the vertex $ 9 $ and Bob at vertex $ 8 $ . Alice will select vertex $ 1 $ and Bob has no options now. Alice selects the vertex $ 7 $ and they both stop.

In the second sample, both of them will pick either of the nodes alternately.

## 样例 #1

### 输入

```
9
1 2 3 4 5 6 7 8 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
```

### 输出

```
25
```

## 样例 #2

### 输入

```
2
20 10
1 2
```

### 输出

```
30
```

# AI分析结果



**唯一算法分类**：树形动态规划（树形DP）

---

### **综合分析与结论**
题目要求树中选取两条不相交的路径，使得权值和最大。核心思路是通过树形DP维护多个状态，覆盖所有可能的路径组合情况，最终合并最优解。各题解中，树形DP的实现方式略有不同，但核心思想一致：通过递归遍历树，维护子树中的最长链、次长链、两条链的组合等状态，逐步合并子节点信息。

**核心难点**在于如何设计状态转移方程，确保所有可能的路径情况（如路径经过当前节点、路径在子树中等）都被覆盖。例如，NOIPZZY的题解通过定义 `f[u][0]`（两条链之和）、`f[u][1]`（一条链）等状态，并结合 `g[u]`（链延伸与另一链的组合）、`down[u]`（到叶子的最长链），全面覆盖了所有情况。

**可视化设计思路**：
- **颜色标记**：在递归过程中，用不同颜色高亮当前处理的节点及其子节点的状态（如红色表示最长链，蓝色表示次长链）。
- **动画步骤**：逐步展开DFS过程，展示每个节点如何合并子节点的信息，并通过箭头动态连接路径。
- **复古像素风格**：用8位网格表示树结构，当前节点闪烁显示，子节点状态以不同色块更新。

---

### **题解清单 (≥4星)**
1. **NOIPZZY (5星)**  
   - **亮点**：状态设计清晰，注释详细，代码结构简洁，覆盖所有可能路径组合。
   - **代码片段**：
     ```cpp
     void dfs(int cur, int fa) {	
         f[cur][0] = w[cur]; // 初始化为当前节点的权值
         for (int u : G[cur]) {	
             dfs(u, cur);
             // 合并子节点的四种情况
             f[cur][0] = max(f[cur][0], f[cur][1] + f[u][1]);
             f[cur][0] = max(f[cur][0], down[cur] + g[u]);
         }
     }
     ```

2. **Liuxizai (4星)**  
   - **亮点**：状态命名直观，转移方程注释详细，提供扩展阅读链接。
   - **关键思路**：通过 `DP[now,0]` 维护两条链的和，利用前缀和后缀优化合并子节点信息。

3. **傅思维666 (4星)**  
   - **亮点**：代码简洁，核心逻辑与NOIPZZY一致，适合快速理解。
   - **个人心得**：调试时发现需注意路径不相交的边界条件。

---

### **最优思路提炼**
1. **状态设计**：  
   - `f[u][0]`：子树中两条不相交链的最大和。  
   - `f[u][1]`：子树中最长单链。  
   - `down[u]`：从 `u` 到叶子的最长链。  
   - `g[u]`：链延伸与另一链的组合最大值。

2. **转移关键**：  
   - 合并子节点时，需考虑四条链的组合情况（如 `f[u][1]+子节点链` 或 `down[u]+子节点g值`）。
   - 通过维护前缀和后缀最大值，避免重复计算。

---

### **相似题目推荐**
1. **P4383 [八省联考2018]林克卡特树**  
   - 同样利用树形DP维护多条链的最优解。
2. **P4516 [JSOI2018]潜入行动**  
   - 树形DP结合状态压缩，覆盖复杂子树状态。
3. **P5658 [CSP-S2019]括号树**  
   - 树形DP处理路径组合问题。

---

### **代码实现（核心片段）**
```cpp
void dfs(int u, int fa) {
    f[u][0] = f[u][1] = w[u];
    LL max1 = 0, max2 = 0; // 维护子节点的最长和次长链
    for (int v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        // 更新两条链的最大和
        f[u][0] = max(f[u][0], f[v][0]);
        f[u][0] = max(f[u][0], f[u][1] + f[v][1]);
        // 更新最长单链
        f[u][1] = max(f[u][1], f[v][1] + w[u]);
        // 维护子节点的链信息
        if (down[v] > max1) {
            max2 = max1;
            max1 = down[v];
        } else if (down[v] > max2) {
            max2 = down[v];
        }
    }
    // 合并子节点链的组合
    f[u][0] = max(f[u][0], max1 + max2 + w[u]);
}
```

---

### **可视化与游戏化设计**
1. **像素动画**：  
   - 树结构用网格表示，节点为色块，边为连线。  
   - 当前处理节点高亮为黄色，子节点状态更新时闪烁绿色/红色。  
   - 音效：合并状态时播放“叮”声，找到最优解时播放胜利音效。

2. **交互功能**：  
   - **步进控制**：用户可点击“下一步”观察状态更新。  
   - **自动模式**：AI自动遍历树，速度可调。  
   - **积分系统**：每正确合并一次状态得10分，错误操作扣分。

---

**总结**：树形DP通过多状态覆盖所有路径组合是本题最优解，结合递归和动态规划思想，适合类似树结构的最优化问题。

---
处理用时：75.68秒