# 题目信息

# Maze

## 题目描述

A maze is represented by a tree (an undirected graph, where exactly one way exists between each pair of vertices). In the maze the entrance vertex and the exit vertex are chosen with some probability. The exit from the maze is sought by Deep First Search. If there are several possible ways to move, the move is chosen equiprobably. Consider the following pseudo-code:

```plain
DFS(x)
    if x == exit vertex then
        finish search
    flag[x] <- TRUE
    random shuffle the vertices' order in V(x) // here all permutations have equal probability to be chosen
    for i <- 1 to length[V] do
        if flag[V[i]] = FALSE then
            count++;
            DFS(y);
    count++;
```

$ V(x) $ is the list vertices adjacent to $ x $ . The $ flag $ array is initially filled as FALSE. $ DFS $ initially starts with a parameter of an entrance vertex. When the search is finished, variable $ count $ will contain the number of moves.

Your task is to count the mathematical expectation of the number of moves one has to do to exit the maze.

## 说明/提示

In the first sample the entrance vertex is always 1 and the exit vertex is always 2.

In the second sample the entrance vertex is always 1 and the exit vertex with the probability of 2/5 will be 2 of with the probability if 3/5 will be 3. The mathematical expectations for the exit vertices 2 and 3 will be equal (symmetrical cases). During the first move one can go to the exit vertex with the probability of 0.5 or to go to a vertex that's not the exit vertex with the probability of 0.5. In the first case the number of moves equals 1, in the second one it equals 3. The total mathematical expectation is counted as $ 2/5×(1×0.5+3×0.5)+3/5×(1×0.5+3×0.5) $

## 样例 #1

### 输入

```
2
1 2
0 1
1 0
```

### 输出

```
1.00000000000000000000
```

## 样例 #2

### 输入

```
3
1 2
1 3
1 0
0 2
0 3
```

### 输出

```
2.00000000000000000000
```

## 样例 #3

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7
1 1
1 1
1 1
1 1
1 1
1 1
1 1
```

### 输出

```
4.04081632653```

# AI分析结果



## 算法分类
树形动态规划（树形DP）、期望计算

---

## 综合分析与结论

### 核心思路
题目要求计算DFS在树形迷宫中寻找随机终点的期望步数。各题解的核心思路均围绕以下关键点展开：
1. **期望的线性性**：将总期望拆分为每个子树贡献的期望之和。
2. **子树性质**：在DFS中，若进入错误子树（不含终点），需遍历整个子树后才回溯。
3. **概率与贡献计算**：每个子树的贡献 = 该子树被选为起点的概率 × 终点概率 × 子树大小。

### 解决难点
- **贡献分析**：正确识别哪些子树会贡献步数（错误子树贡献固定值，正确路径贡献动态值）。
- **概率整合**：将起点、终点的概率分布与子树大小结合，进行线性累加。
- **高效实现**：通过一次DFS遍历完成子树大小和概率的统计。

### 可视化设计
1. **树结构绘制**：在Canvas中以节点为中心绘制树形结构，用不同颜色区分当前处理的子树。
2. **动态贡献计算**：
   - 高亮当前终点节点（如红色）。
   - 以绿色标记当前计算的子树，显示其大小 `siz[v]` 和概率 `x[v] * y[u]`。
   - 逐步累加贡献值到总期望中，右侧面板实时更新计算结果。
3. **复古像素风格**：
   - 节点用8x8像素方块表示，子树枝条用低分辨率线段绘制。
   - 音效设计：计算贡献时播放短促“滴”声，总期望更新时播放胜利音效。

---

## 题解清单 (评分≥4星)

### 1. Xu_brezza（⭐⭐⭐⭐⭐）
- **关键亮点**：
  - 将总期望拆解为每个终点的贡献，通过子树概率乘积直接累加。
  - 代码简洁高效，仅需一次DFS遍历，时间复杂度O(n)。
  - 利用 `siz[v]` 直接表示错误子树的步数贡献。
- **核心代码**：
  ```cpp
  void dfs(int u, int fa) {
      siz[u] = 1;
      for (int v : g[u]) {
          if (v == fa) continue;
          dfs(v, u);
          siz[u] += siz[v];
          x[u] += x[v];
          ans += x[v] * siz[v] * y[u]; // 子树贡献
      }
      ans += (sx - x[u]) * (n - siz[u]) * y[u]; // 外部贡献
  }
  ```

### 2. hwk0518（⭐⭐⭐⭐）
- **关键亮点**：
  - 通过边贡献模型，证明错误边的期望贡献为1。
  - 换根DP处理不同根节点的情况，适用于更复杂变种。
- **核心公式**：
  - 错误边贡献：`E = 1/2 * 2 + 1/2 * 0 = 1`

### 3. Phartial（⭐⭐⭐⭐）
- **关键亮点**：
  - 路径分类模型，将步数拆分为必经路径和错误路径。
  - 利用LCA快速判断子树关系，减少计算量。

---

## 最优思路提炼

### 关键技巧
- **子树贡献模型**：直接计算每个子树对期望的贡献，公式为 `ans += x[v] * siz[v] * y[u]`。
- **一次DFS统计**：在DFS中同时统计子树大小 `siz` 和概率累加值 `x`，实现O(n)复杂度。
- **外部贡献计算**：用 `(sx - x[u])` 表示非子树起点的概率，`(n - siz[u])` 表示外部子树大小。

### 同类型题套路
1. **树上的期望计算**：通常利用DFS/BFS遍历，结合子树分解。
2. **贡献拆分**：将整体问题拆解为每个节点/边的独立贡献。
3. **换根DP**：处理不同根节点视角下的统计量（如[CF1092F Tree with Maximum Cost](https://codeforces.com/problemset/problem/1092/F)）。

---

## 推荐题目
1. [CF1092F Tree with Maximum Cost](https://codeforces.com/problemset/problem/1092/F)  
   （树形DP，贡献计算）
2. [Luogu P1351 联合权值](https://www.luogu.com.cn/problem/P1351)  
   （树形结构，距离统计）
3. [CF1843E Tracking Segments](https://codeforces.com/problemset/problem/1843/E)  
   （期望与二分结合）

---

## 个人心得摘录
> "自己做出来滴紫色期望！！！好开心！！！" —— Xu_brezza  
> **总结**：复杂期望问题需耐心拆分贡献，树形结构常隐含递归子问题。

---

## 可视化算法演示

### 核心逻辑动画
```html
<!-- 示例：Canvas绘制树结构 -->
<canvas id="treeCanvas" width="800" height="600"></canvas>
<script>
class TreeVisualizer {
  constructor() {
    this.nodes = { /* 节点坐标 */ };
    this.highlightNode = null; // 当前高亮终点
    this.currentSubtree = null; // 当前计算子树
    this.totalExpectation = 0;
  }

  drawTree() {
    // 递归绘制树结构，高亮当前子树
  }

  stepCalculation(v, contribution) {
    this.totalExpectation += contribution;
    // 播放音效并更新显示
  }
}
</script>
```

### 复古风格设计
- **调色板**：16色，主色调为深绿、浅蓝、红色（终点高亮）。
- **音效**：使用[jsfxr](https://sfxr.me/)生成8位音效：
  - 贡献计算：短促“滴”声（频率800Hz，时长0.1s）。
  - 总期望更新：胜利音效（上升琶音）。

---

## 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int> g[N];
double x[N], y[N], ans, sx, sy;
int siz[N], n;

void dfs(int u, int fa) {
    siz[u] = 1;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
        x[u] += x[v];
        ans += x[v] * siz[v] * y[u]; // 子树贡献
    }
    ans += (sx - x[u]) * (n - siz[u]) * y[u]; // 外部贡献
}

int main() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
        sx += x[i]; sy += y[i];
    }
    for (int i = 1; i <= n; ++i) {
        x[i] /= sx; y[i] /= sy; // 归一化概率
    }
    dfs(1, 0);
    printf("%.10lf", ans);
}
```

---
处理用时：71.84秒