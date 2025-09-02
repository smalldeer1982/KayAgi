# 题目信息

# White-Black Balanced Subtrees

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root is vertex $ 1 $ . There is also a string $ s $ denoting the color of each vertex: if $ s_i = \texttt{B} $ , then vertex $ i $ is black, and if $ s_i = \texttt{W} $ , then vertex $ i $ is white.

A subtree of the tree is called balanced if the number of white vertices equals the number of black vertices. Count the number of balanced subtrees.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root. In this problem, all trees have root $ 1 $ .

The tree is specified by an array of parents $ a_2, \dots, a_n $ containing $ n-1 $ numbers: $ a_i $ is the parent of the vertex with the number $ i $ for all $ i = 2, \dots, n $ . The parent of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root.

The subtree of a vertex $ u $ is the set of all vertices that pass through $ u $ on a simple path to the root. For example, in the picture below, $ 7 $ is in the subtree of $ 3 $ because the simple path $ 7 \to 5 \to 3 \to 1 $ passes through $ 3 $ . Note that a vertex is included in its subtree, and the subtree of the root is the entire tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676G/70fb6ac8a70942903450f21b07ea9969f086df2c.png) The picture shows the tree for $ n=7 $ , $ a=[1,1,2,3,3,5] $ , and $ s=\texttt{WBBWWBW} $ . The subtree at the vertex $ 3 $ is balanced.

## 说明/提示

The first test case is pictured in the statement. Only the subtrees at vertices $ 2 $ and $ 3 $ are balanced.

In the second test case, only the subtree at vertex $ 1 $ is balanced.

In the third test case, only the subtrees at vertices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are balanced.

## 样例 #1

### 输入

```
3
7
1 1 2 3 3 5
WBBWWBW
2
1
BW
8
1 2 3 4 5 6 7
BWBWBWBW```

### 输出

```
2
1
4```

# AI分析结果



### 唯一算法分类
树形动态规划（Tree DP）

---

### 题解思路、算法要点与解决难点

#### 核心思路对比
所有题解均采用 **后序遍历统计子树状态** 的思想，具体实现分为两种方向：
1. **黑白计数法**（如题解 2、3、4、5）：每个节点维护两个变量 `black_cnt` 和 `white_cnt`，分别表示子树中黑、白节点数量。通过 DFS 回溯累加子节点数据，最终判断是否相等。
2. **符号累加法**（如题解 1、8）：将黑节点视为 +1，白节点视为 -1，DFS 回溯时计算子树总和。总和为 0 的子树即为平衡子树。

#### 关键难点
- **子树定义**：需明确题目中的子树定义为包含所有祖先节点到根的路径节点，但实际处理时只需统计以当前节点为根的子树（传统子树定义）。
- **多测数据清空**：每次测试需重置邻接表、统计数组等数据结构。
- **高效状态传递**：通过递归实现自底向上的状态累加，确保时间复杂度为 O(n)。

---

### 题解评分（≥4星）

1. **a1co0av5ce5az1cz0ap_（5星）**
   - 亮点：代码最简，用符号累加法减少变量数量，通过单变量 `sum` 判断平衡。
   - 代码片段：
     ```cpp
     int co(int rt) {
         int sum = color[rt];
         for (auto child : v[rt]) sum += co(child);
         if (sum == 0) ans++;
         return sum;
     }
     ```

2. **Withers（4星）**
   - 亮点：结构清晰，使用 `struct node` 维护黑白计数，树形 DP 模板化实现。
   - 代码片段：
     ```cpp
     void dfs(int u, int fath) {
         for (auto v : g[u]) {
             dfs(v, u);
             k[u].b += k[v].b;
             k[u].w += k[v].w;
         }
         if (k[u].b == k[u].w) ans++;
     }
     ```

3. **5k_sync_closer（4星）**
   - 亮点：极致精简的代码风格，通过全局数组 `s[][]` 实现状态统计。
   - 代码片段：
     ```cpp
     void dfs(int x) {
         for (int i = h[x]; i; i = e[i].t)
             dfs(e[i].v), s[x][0] += s[e[i].v][0], s[x][1] += s[e[i].v][1];
         if (s[x][0] == s[x][1]) ++q;
     }
     ```

---

### 最优思路与技巧提炼

#### 关键技巧
1. **符号映射法**：将黑白节点转化为 +1/-1，简化平衡判断为 `sum == 0`。
2. **后序遍历状态传递**：利用递归天然的回溯特性，自底向上累加子树状态。
3. **邻接表建树**：通过父节点数组构建单向子节点列表，避免冗余双向边处理。

#### 同类型题套路
- **子树统计问题**：如统计子树和、子树平均值、子树特性验证（如红黑树平衡性）等，均可通过类似树形 DP 解决。
- **后序遍历应用**：需要先处理子节点再处理父节点的场景（如本题的累加操作）。

---

### 相似题目推荐
1. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)  
   （树形 DP + 中序遍历特性）
2. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)  
   （树形 DP 决策模型）
3. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)  
   （树形背包问题）

---

### 个人心得摘录
- **符号累加法的调试**：某题解提到初始未清空邻接表导致 WA，强调多测数据初始化的重要性。
- **子树定义误解**：有题解特别注释说明题目中子树定义与传统不同，但实际代码仍按传统实现，需注意题目描述细节。

---

### 可视化与算法演示

#### 核心算法动画设计
1. **树结构绘制**：以根节点为中心，按层级展开子节点，用不同颜色（黑/白）标记节点。
2. **递归过程高亮**：
   - **当前节点**：用闪烁边框标记。
   - **状态更新**：显示 `black_cnt` 和 `white_cnt`（或 `sum`）的累加过程。
3. **平衡判定**：当某节点的统计值满足条件时，其背景变为绿色并播放音效。

#### 复古像素风格实现
- **颜色方案**：8-bit 调色板，黑(#000000)、白(#FFFFFF)、高亮绿(#00FF00)。
- **Canvas 绘制**：
  ```javascript
  function drawNode(node, x, y) {
      ctx.fillStyle = node.color === 'B' ? '#000' : '#FFF';
      ctx.fillRect(x, y, 30, 30); // 节点主体
      ctx.fillStyle = '#F00';
      ctx.fillText(node.sum, x + 5, y + 20); // 显示当前 sum 值
  }
  ```
- **音效设计**：
  - **递归进入**：短促 "beep" 声。
  - **平衡触发**：8-bit 风格胜利音效（上升琶音）。

#### 交互功能
- **步进控制**：按钮支持暂停/继续/单步，观察递归栈变化。
- **自动演示**：AI 模式自动遍历节点，速度可调（1x~5x）。

---

### 核心代码实现（符号累加法）
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> tree[4005];
int color[4005], ans;

int dfs(int u) {
    int sum = color[u];
    for (int v : tree[u]) sum += dfs(v);
    if (sum == 0) ans++;
    return sum;
}

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 1; i <= n; i++) tree[i].clear();
        for (int i = 2; i <= n; i++) {
            int fa; cin >> fa;
            tree[fa].push_back(i);
        }
        string s; cin >> s;
        for (int i = 0; i < n; i++)
            color[i+1] = (s[i] == 'B' ? 1 : -1);
        ans = 0;
        dfs(1);
        cout << ans << endl;
    }
    return 0;
}
```

---
处理用时：91.32秒