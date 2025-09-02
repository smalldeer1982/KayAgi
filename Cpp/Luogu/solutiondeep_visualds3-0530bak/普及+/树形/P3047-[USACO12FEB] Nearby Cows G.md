# 题目信息

# [USACO12FEB] Nearby Cows G

## 题目描述

Farmer John has noticed that his cows often move between nearby fields. Taking this into account, he wants to plant enough grass in each of his fields not only for the cows situated initially in that field, but also for cows visiting from nearby fields.

Specifically, FJ's farm consists of N fields (1 <= N <= 100,000), where some pairs of fields are connected with bi-directional trails (N-1 of them in total).  FJ has designed the farm so that between any two fields i and j, there is a unique path made up of trails connecting between i and j. Field i is home to C(i) cows, although cows sometimes move to a different field by crossing up to K trails (1 <= K <= 20).

FJ wants to plant enough grass in each field i to feed the maximum number of cows, M(i), that could possibly end up in that field -- that is, the number of cows that can potentially reach field i by following at most K trails.  Given the structure of FJ's farm and the value of C(i) for each field i, please help FJ compute M(i) for every field i.

给你一棵 $n$ 个点的树，点带权，对于每个节点求出距离它不超过 $k$ 的所有节点权值和 $m_i$。

## 说明/提示

There are 6 fields, with trails connecting (5,1), (3,6), (2,4), (2,1), and (3,2).  Field i has C(i) = i cows.


Field 1 has M(1) = 15 cows within a distance of 2 trails, etc.

【数据范围】  
对于 $100\%$ 的数据：$1 \le n \le 10^5$，$1 \le k \le 20$，$0 \le c_i \le 1000$

## 样例 #1

### 输入

```
6 2 
5 1 
3 6 
2 4 
2 1 
3 2 
1 
2 
3 
4 
5 
6 
```

### 输出

```
15 
21 
16 
10 
8 
11 
```

# AI分析结果



## 【唯一算法分类】
树形动态规划（换根DP）

---

## 【题解思路与算法要点】

### **核心思路**
1. **两次DFS遍历**：
   - **第一次DFS**（自底向上）：计算子树内各距离的贡献。`f[i][j]` 表示节点 `i` 子树内距离为 `j` 的权值和，通过累加所有子节点的 `f[son][j-1]` 得到。
   - **第二次DFS**（自顶向下）：处理父节点方向的贡献，并通过容斥避免重复计算。更新时，父节点的 `f[fa][j-1]` 减去子节点已计算的部分 `f[son][j-2]`。

2. **状态转移方程**：
   - **子树方向**：`f[u][j] += f[v][j-1]`（`v` 为 `u` 的子节点）。
   - **父节点方向**：`f[v][j] += f[u][j-1] - f[v][j-2]`（倒序更新避免覆盖）。

### **解决难点**
- **容斥原理**：父节点方向更新时，需减去子节点在子树中已计算的部分，防止重复累加。
- **时间复杂度**：通过两次 `O(nk)` 的遍历，高效处理大规模数据（`n ≤ 1e5, k ≤ 20`）。

---

## 【题解评分（≥4星）】

1. **asuldb（4.5星）**
   - **亮点**：代码简洁，容斥步骤清晰，注释详细。
   - **代码片段**：
     ```cpp
     void build(int r) {
         for (re int i = head[r]; i; i = e[i].nxt) {
             int v = e[i].v;
             if (!deep[v]) {
                 deep[v] = deep[r] + 1;
                 build(v);
                 for (int j = 1; j <= k; j++) f[r][j] += f[v][j-1];
             }
         }
     }
     ```

2. **Yuyuanqi（4星）**
   - **亮点**：分 `f` 和 `d` 数组解释，逻辑分明。
   - **代码片段**：
     ```cpp
     void dfs(int x, int fa) {
         for (int j = 0; j <= k; j++) d[x][j] = f[x][j];
         for (int j = 1; j <= k; j++) 
             d[v][j] += d[x][j-1] - d[v][j-2];
     }
     ```

3. **juruo_zjc（4星）**
   - **亮点**：使用通俗语言解释容斥，适合新手理解。
   - **个人心得**：“容斥是解题关键，先减后加避免重复”。

---

## 【最优思路提炼】
1. **两次DFS框架**：
   - **第一次**：子树贡献，递归子节点并累加。
   - **第二次**：父节点贡献，倒序更新避免覆盖，用容斥消除重复。

2. **关键技巧**：
   - **倒序循环**：第二次更新时，从 `k` 到 `1` 倒序处理，确保先减去旧值。
   - **状态复用**：`f[i][j]` 直接复用子树结果，父节点方向通过路径回溯动态调整。

---

## 【同类型题与算法套路】
- **通用解法**：树形问题中需要同时考虑子树和父节点贡献时，优先考虑换根DP。
- **类似题目**：
  1. [P3478 [POI2008]STA-Station](https://www.luogu.com.cn/problem/P3478)（求重心）
  2. [P2986 [USACO10MAR]Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)（换根统计路径和）
  3. [P3041 [USACO12JAN]Video Game G](https://www.luogu.com.cn/problem/P3041)（多模式匹配+DP）

---

## 【可视化设计】
### **动画方案**
1. **树结构绘制**：用Canvas绘制树形结构，节点按层分布，边用连线表示。
2. **颜色标记**：
   - **绿色**：当前处理的节点。
   - **红色**：子树方向更新的路径。
   - **蓝色**：父节点方向更新的路径。
3. **高亮步骤**：
   - **第一次DFS**：递归子节点时，显示绿色节点向下扩展，逐步填充子树贡献。
   - **第二次DFS**：父节点更新时，蓝色箭头从父节点指向子节点，红色箭头表示容斥减法。

### **复古像素风格**
- **8位调色板**：节点用16色方块表示，背景为黑色网格。
- **音效设计**：
  - **按键音**：每次状态更新播放短促“滴”声。
  - **完成音**：DFS完成时播放8-bit胜利音效。

### **交互功能**
- **步进控制**：支持暂停/继续，手动触发每一步更新。
- **速度调节**：滑动条控制动画速度（0.5x~3x）。

---

## **代码示例（关键DFS逻辑）**
```cpp
void dfs2(int u, int fa) {
    for (int v : tree[u]) {
        if (v == fa) continue;
        // 倒序更新，避免覆盖
        for (int j = k; j >= 2; j--) 
            f[v][j] -= f[v][j-2];
        for (int j = 1; j <= k; j++)
            f[v][j] += f[u][j-1];
        dfs2(v, u);
    }
}
```

---

## **总结**
通过两次DFS和容斥原理，高效解决了树形结构下的多距离累加问题。核心在于分离子树与父节点贡献，并通过动态规划状态复用降低复杂度。可视化设计通过颜色和音效强化了算法步骤的理解，适合教学与自学。

---
处理用时：72.09秒