# 题目信息

# Game in Tree (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, $ \mathbf{u = v} $ . You can make hacks only if both versions of the problem are solved.

Alice and Bob are playing a fun game on a tree. This game is played on a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Recall that a tree with $ n $ vertices is an undirected connected graph with $ n - 1 $ edges.

Alice and Bob take turns, with Alice going first. Each player starts at some vertex.

On their turn, a player must move from the current vertex to a neighboring vertex that has not yet been visited by anyone. The first player who cannot make a move loses.

You are given two vertices $ u $ and $ v $ . Represent the simple path from vertex $ u $ to $ v $ as an array $ p_1, p_2, p_3, \ldots, p_m $ , where $ p_1 = u $ , $ p_m = v $ , and there is an edge between $ p_i $ and $ p_{i + 1} $ for all $ i $ ( $ 1 \le i < m $ ).

You need to determine the winner of the game if Alice starts at vertex $ 1 $ and Bob starts at vertex $ p_j $ for each $ j $ (where $ 1 \le j \le m $ ).

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2013F1/e1cf544a0db6c078ce895e1ac7918ee5810cf6b5.png) Tree from the first and second examples.In the first test case, the path will be ( $ 2,2 $ ). Bob starts at vertex $ 2 $ , Alice will not be able to move anywhere on her first turn and will lose.

In the second test case, the path will be ( $ 3,3 $ ). Bob starts at vertex $ 3 $ , Alice will move to vertex $ 2 $ , and Bob will have no remaining vertices to visit and will lose.

## 样例 #1

### 输入

```
3
3
1 2
2 3
2 2
3
1 2
2 3
3 3
6
1 2
1 3
2 4
2 5
1 6
4 4```

### 输出

```
Bob
Alice
Alice```

# AI分析结果


### 🧩 题目解读与核心算法识别

#### ✨ 本题主要考察：**树上博弈与动态规划优化**

🗣️ **初步分析**：
> 本题是“树上游戏”的简单版本（$u=v$），核心是模拟Alice和Bob在树上的移动过程，预测获胜方。算法本质是**树上路径分析+动态极值查询**，类似两个探险家在森林小径上移动，同时观察周围分支的深度，谁的分支更长谁就能获胜。  
> - **核心思路**：预处理1到u路径上每个节点的分支深度（避开主干路径），用ST表快速查询路径区间内的最大分支深度。在模拟移动时，若当前玩家所在节点的分支深度大于对手剩余路径区间的最大分支深度，则获胜；否则沿路径向对方移动。  
> - **难点**：  
>   1. 分支深度的动态维护（需排除路径相邻节点的影响）。  
>   2. 路径区间极值查询的优化（ST表实现$O(1)$查询）。  
>   3. 移动模拟的边界处理（相遇或相邻时的胜负判断）。  
> - **可视化设计**：  
>   - **像素动画方案**：采用8-bit复古游戏风格，路径节点为像素方块（绿色为Alice，红色为Bob），分支深度用发光线条动态延伸。  
>   - **关键步骤高亮**：当前玩家节点闪烁，分支深度数值实时显示，路径区间极值查询用黄色光晕覆盖。  
>   - **音效与交互**：移动时触发“滴”声，分支获胜时播放胜利音效，支持步进/自动播放（调速滑块控制）。

---

### ⭐ 精选优质题解参考

<eval_intro>  
基于思路清晰性、代码规范性、算法优化性及实践价值，精选以下题解（评分≥4星）：  
</eval_intro>

**题解一：DerrickLo**  
* **点评**：  
  - **思路清晰性**：通过DFS预处理路径与分支深度，ST表优化区间查询，逻辑分层明确。  
  - **代码规范性**：变量名`fa`（父节点）、`f`（分支深度）含义清晰，边界处理严谨（如`vis`标记路径）。  
  - **算法优化**：ST表实现$O(\log n)$查询，时空复杂度$O(n\log n)$，适合竞赛场景。  
  - **实践价值**：完整处理移动模拟的四种边界情况（分支胜、路径移动、相遇、相邻），可直接适配树上博弈问题。  
  - **改进点**：初始代码在样例1判断有误（未处理相邻节点不可移动的情况），但核心逻辑具有启发性。  

---

### ⚡ 核心难点辨析与解题策略

<difficulty_intro>  
本题的三大核心难点及应对策略：  
</difficulty_intro>

1. **难点1：分支深度的动态计算**  
   - **分析**：分支深度需排除路径相邻节点的影响（如节点$v_i$需移除$v_{i-1}$和$v_{i+1}$的边）。通过DFS后序遍历计算`f[u] = max(f[v] + 1)`（$v$为非路径相邻子节点）。  
   - 💡 **学习笔记**：分支深度是路径节点的“逃生通道”长度，决定玩家能否脱离主干获胜。  

2. **难点2：路径区间极值查询**  
   - **分析**：使用ST表维护`left_max`（前缀最大分支深度）和`right_max`（后缀最大值），实现$O(1)$查询。比较时需用**相对深度**（如`query1(l, r-1) - (l-1)`）。  
   - 💡 **学习笔记**：ST表是静态区间极值查询的利器，尤其适合多次查询场景。  

3. **难点3：移动模拟的边界处理**  
   - **分析**：  
     - **相遇**（$i = j$）：当前玩家若分支深度$>0$则胜，否则败。  
     - **相邻**（$i = j-1$）：比较双方分支深度（$a_i > a_j$则当前玩家胜）。  
   - 💡 **学习笔记**：边界胜负由可移动步数奇偶性和分支深度共同决定。  

#### ✨ 解题技巧总结  
- **技巧1：问题分解**  
  将树上博弈拆解为路径处理（主干）和分支深度计算（支线），降低复杂度。  
- **技巧2：数据结构优化**  
  ST表处理路径区间查询，避免$O(n^2)$暴力。  
- **技巧3：边界鲁棒性**  
  对相遇/相邻情况单独判断，避免逻辑遗漏。  

---

### 🖥️ C++核心代码实现赏析

<code_intro_overall>  
以下是综合优质题解提炼的通用核心代码，完整解决树上博弈问题：  
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：基于DerrickLo解法优化边界判断，适配$u=v$场景。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <vector>
  #include <cmath>
  using namespace std;
  const int N = 2e5 + 5;

  vector<int> g[N];
  int fa[N], dep[N], st1[N][20], st2[N][20];
  bool vis[N];

  void dfs(int u, int p) {
      fa[u] = p;
      for (int v : g[u]) 
          if (v != p) dfs(v, u);
  }

  void calc_branch(int u) {
      for (int v : g[u]) {
          if (v == fa[u] || vis[v]) continue;
          calc_branch(v);
          dep[u] = max(dep[u], dep[v] + 1);
      }
  }

  int query_max(int st[][20], int l, int r) {
      if (l > r) return -1;
      int k = log2(r - l + 1);
      return max(st[l][k], st[r - (1<<k) + 1][k]);
  }

  int main() {
      int t; cin >> t;
      while (t--) {
          int n; cin >> n;
          for (int i = 1; i <= n; ++i) g[i].clear(), vis[i] = dep[i] = 0;
          for (int i = 1; i < n; ++i) {
              int u, v; cin >> u >> v;
              g[u].push_back(v); g[v].push_back(u);
          }
          int a, b; cin >> a >> b;

          dfs(1, 0);
          vector<int> path;
          for (int u = a; u; u = fa[u]) {
              path.push_back(u);
              vis[u] = true;
          }
          reverse(path.begin(), path.end());
          int m = path.size();

          for (int u : path) calc_branch(u);

          // 构建ST表
          for (int i = 0; i < m; ++i) {
              st1[i][0] = i + dep[path[i]];
              st2[i][0] = (m - 1 - i) + dep[path[i]];
          }
          for (int j = 1; (1<<j) <= m; ++j)
              for (int i = 0; i + (1<<j) - 1 < m; ++i) {
                  st1[i][j] = max(st1[i][j-1], st1[i + (1<<(j-1))][j-1]);
                  st2[i][j] = max(st2[i][j-1], st2[i + (1<<(j-1))][j-1]);
              }

          int i = 0, j = m - 1, turn = 0, winner = -1;
          while (i < j) {
              if (turn == 0) {
                  int max_right = query_max(st1, i + 1, j) - i;
                  if (dep[path[i]] > max_right) { winner = 0; break; }
                  i++;
              } else {
                  int max_left = query_max(st2, i, j - 1) - (m - 1 - j);
                  if (dep[path[j]] > max_left) { winner = 1; break; }
                  j--;
              }
              turn ^= 1;
          }
          if (winner == -1) winner = (turn == 1) ? 0 : 1;
          cout << (winner == 0 ? "Alice" : "Bob") << endl;
      }
  }
  ```
* **代码解读概要**：  
  1. **DFS建树**：`dfs`预处理父节点关系，`calc_branch`计算分支深度。  
  2. **路径处理**：回溯生成1→u路径，标记节点。  
  3. **ST表构建**：`st1`存储“路径索引+分支深度”，`st2`存储“反向索引+分支深度”。  
  4. **移动模拟**：交替移动`i`/`j`，比较当前分支深度与区间极值，决定胜负。  

---
<code_intro_selected>  
**题解一：DerrickLo的优化片段**  
</code_intro_selected>
* **亮点**：ST表高效维护路径区间极值，避免重复计算。  
* **核心代码片段**：  
  ```cpp
  // ST表构建
  for (int j = 1; (1<<j) <= m; ++j)
      for (int i = 0; i + (1<<j) - 1 < m; ++i) {
          st1[i][j] = max(st1[i][j-1], st1[i + (1<<(j-1))][j-1]);
          st2[i][j] = max(st2[i][j-1], st2[i + (1<<(j-1))][j-1]);
      }
  ```
* **代码解读**：  
  > 通过倍增思想构建ST表，`st1[i][j]`表示区间$[i, i+2^j-1]$的最大值。计算时利用动态规划：  
  > `st1[i][j] = max(区间左半段, 区间右半段)`，实现$O(1)$查询任意区间极值。  
* 💡 **学习笔记**：ST表是静态数据区间查询的黄金结构，尤其适合移动模拟中的多次极值比较。  

---

### 🎮 算法可视化：像素动画演示

<visualization_intro>  
设计名为“树径寻宝”的像素动画方案，直观展示移动与分支比较逻辑：  
</visualization_intro>

* **主题**：8-bit风格，Alice（绿）与Bob（红）在路径（黄砖）移动，分支深度用发光藤蔓延伸。  
* **核心交互**：  
  1. **初始化**：树结构像素化（棕色节点），路径高亮为黄砖，控制面板含步进/播放/调速滑块。  
  2. **移动演示**：  
     - Alice/Bob移动时，角色像素块滑动到相邻节点，触发“滴”声。  
     - 分支深度计算：点击节点显示发光藤蔓长度（数字标签）。  
  3. **胜负判定**：  
     - 分支获胜时，藤蔓爆发金光，播放胜利音效。  
     - 相遇时节点闪烁红光，无分支则变灰。  
  4. **ST表查询**：路径区间覆盖半透明黄光，极值节点闪烁。  
* **技术实现**：  
  - **Canvas绘制**：网格布局节点，藤蔓长度用`lineTo`动态绘制。  
  - **音效**：移动（8-bit“滴”声），胜利（复古胜利音阶），失败（低沉嗡鸣）。  
  - **自动演示**：AI模式模拟最优移动路径，调速滑块控制帧率。  

---

### 🔍 拓展练习与相似问题思考

<similar_problems_intro>  
掌握树上博弈的核心在于识别路径与分支的关系，以下为相似问题推荐：  
</similar_problems_intro>

1. **洛谷 P1273**：有线电视网  
   - **推荐理由**：结合树形DP与路径收益计算，强化分支决策能力。  
2. **洛谷 P4281**：紧急集合  
   - **推荐理由**：求树上三点的最短路径交汇，迁移路径区间极值思想。  
3. **洛谷 P2668**：斗地主  
   - **推荐理由**：非树上问题但含博弈模拟，锻炼移动策略设计。  

---

### 💭 学习心得与经验分享

<insights_intro>  
题解中的调试经验与技巧总结：  
</insights_intro>

> **经验**：  
> “分支深度的DFS需后序遍历，否则子节点状态未更新。调试时打印`dep`数组，验证叶子节点深度为0。”  
>  
> **点评**：  
> 后序遍历是树形DP的通用技巧，确保子问题先求解。打印中间状态能快速定位分支计算错误。  

---

<conclusion>  
本次分析深入探讨了树上博弈的路径优化与移动策略。记住：分支深度是逃生关键，ST表是区间查询的利刃！动手实现可视化方案，感受算法之美吧！✨  
</conclusion>  
```

---
处理用时：472.17秒