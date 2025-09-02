# 题目信息

# Tree XOR

## 题目描述

You are given a tree with $ n $ vertices labeled from $ 1 $ to $ n $ . An integer $ a_{i} $ is written on vertex $ i $ for $ i = 1, 2, \ldots, n $ . You want to make all $ a_{i} $ equal by performing some (possibly, zero) spells.

Suppose you root the tree at some vertex. On each spell, you can select any vertex $ v $ and any non-negative integer $ c $ . Then for all vertices $ i $ in the subtree $ ^{\dagger} $ of $ v $ , replace $ a_{i} $ with $ a_{i} \oplus c $ . The cost of this spell is $ s \cdot c $ , where $ s $ is the number of vertices in the subtree. Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Let $ m_r $ be the minimum possible total cost required to make all $ a_i $ equal, if vertex $ r $ is chosen as the root of the tree. Find $ m_{1}, m_{2}, \ldots, m_{n} $ .

 $ ^{\dagger} $ Suppose vertex $ r $ is chosen as the root of the tree. Then vertex $ i $ belongs to the subtree of $ v $ if the simple path from $ i $ to $ r $ contains $ v $ .

## 说明/提示

In the first test case, to find $ m_1 $ we root the tree at vertex $ 1 $ .

1. In the first spell, choose $ v=2 $ and $ c=1 $ . After performing the spell, $ a $ will become $ [3, 3, 0, 1] $ . The cost of this spell is $ 3 $ .
2. In the second spell, choose $ v=3 $ and $ c=3 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 1] $ . The cost of this spell is $ 3 $ .
3. In the third spell, choose $ v=4 $ and $ c=2 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 3] $ . The cost of this spell is $ 2 $ .

Now all the values in array $ a $ are equal, and the total cost is $ 3 + 3 + 2 = 8 $ .

The values $ m_2 $ , $ m_3 $ , $ m_4 $ can be found analogously.

In the second test case, the goal is already achieved because there is only one vertex.

## 样例 #1

### 输入

```
2
4
3 2 1 0
1 2
2 3
2 4
1
100```

### 输出

```
8 6 12 10 
0```

# AI分析结果



**唯一算法分类**  
换根DP（树形动态规划）

---

**综合分析与结论**  
**核心思路**：所有题解均围绕换根DP展开。关键观察点：  
1. **贪心策略**：每次操作应优先处理子树，使其与父节点值一致，避免重复操作。  
2. **代价计算**：每个边 $(u, v)$ 的贡献为 $(a_u \oplus a_v) \times$ 子树大小，换根时动态调整子树大小的影响。  
3. **状态转移**：通过两次DFS，首次计算根节点的代价，第二次通过父节点信息推导子节点作为根时的代价。  

**难点与解决**：  
- **数学推导**：换根时的代价变化公式需严格推导（如西瓜nd的 $w_1 < w_2$ 证明）。  
- **子树大小动态维护**：不同根下子树大小变化需通过全局变量或差分处理（如xkcdjerry的差分数组）。  

**可视化设计**：  
- **动画流程**：  
  1. **初始DFS**：以根节点1为例，递归展开子树，标记当前处理节点为红色，子树区域用虚线框高亮，实时显示 `dp[u]` 计算过程。  
  2. **换根DFS**：当根从父节点u转移到子节点v时，用箭头动画表示状态转移，动态更新 `f[v] = f[u] + ...` 的数值变化。  
  3. **边贡献显示**：每条边旁显示其当前贡献值 $(a_u \oplus a_v) \times sz$，换根时数值变化以黄色闪烁提示。  
- **复古风格**：  
  - **像素节点**：每个节点用8x8像素方块表示，不同颜色区分父子关系。  
  - **音效触发**：DFS进入节点时播放“滴”声，换根时播放“咔嚓”声，计算完成播放胜利音效。  

---

**题解清单 (≥4星)**  
1. **西瓜nd（5星）**  
   - **亮点**：贪心策略证明清晰，代码简洁易懂，换根DP模板化。  
   - **代码片段**：  
     ```cpp
     void dfs2(int x, int fath) {
         for (int to : g[x]) {
             if (to == fath) continue;
             f[to] += f[x] - (dp[to] + siz[to]*(a[x]^a[to])) + (n-siz[to])*(a[x]^a[to]);
             dfs2(to, x);
         }
     }
     ```

2. **xkcdjerry（4星）**  
   - **亮点**：树上差分思路独特，利用全局贡献与局部调整降低计算量。  
   - **关键公式**：  
     ```  
     f[1] += sz[x] * w  
     f[x] -= sz[x] * w  
     f[x] += (n - sz[x]) * w  
     ```

3. **hcywoi（4星）**  
   - **亮点**：代码高度精简，直接推导总贡献公式，适合快速实现。  
   - **核心逻辑**：  
     ```cpp
     g[x] = g[p] + f[p] - f[x] + (n - 2*siz[x])*(a[x]^a[p]);
     ```

---

**最优思路提炼**  
1. **贪心调整顺序**：从叶子到根处理子树，保证子树值一致后再处理父节点。  
2. **换根公式推导**：  
   - 当根从 `u` 换到子节点 `v` 时，代价变化为：  
     ```  
     new_cost = old_cost - sz[v] * (a[u]^a[v]) + (n - sz[v]) * (a[u]^a[v])  
     ```  
3. **时间复杂度**：两次DFS实现O(n)，无需额外数据结构。  

---

**同类型题推荐**  
1. **CF1324F Maximum White Subtree**（换根DP经典题）  
2. **P3478 [POI2008] STA-Station**（求根节点使深度和最大）  
3. **ABC222F - Expensive Expense**（树中节点最远距离）  

---

**个人心得摘录**  
- **西瓜nd**：  
  > “贪心的想，对儿子操作比根操作更优，必须严格证明公式差异。”  
- **Demeanor_Roy**：  
  > “将树拍成DFS序后用差分，避免显式换根，减少代码复杂度。”  

---

**代码实现（西瓜nd题解核心）**  
```cpp
void dfs1(int x, int fath) {
    siz[x] = 1;
    for (int to : g[x]) {
        if (to == fath) continue;
        dfs1(to, x);
        siz[x] += siz[to];
        dp[x] += dp[to] + siz[to] * (a[x] ^ a[to]);
    }
}

void dfs2(int x, int fath) {
    for (int to : g[x]) {
        if (to == fath) continue;
        f[to] = f[x] - siz[to] * (a[x]^a[to]) + (n - siz[to]) * (a[x]^a[to]);
        dfs2(to, x);
    }
}
```

---

**可视化与游戏化设计**  
- **Canvas动画**：  
  - **节点渲染**：绿色方块表示当前处理节点，蓝色虚线框表示子树范围。  
  - **数值显示**：节点上方显示 `dp[u]` 和 `f[u]`，边旁显示贡献值。  
- **音效与交互**：  
  - **点击节点**：切换为根时播放“切换”音效，显示代价更新过程。  
  - **自动模式**：按DFS顺序自动执行，速度可调（1x/2x/5x）。  
- **复古风格**：  
  - **调色板**：16色FC风格，节点用红/绿/蓝三色区分状态。  
  - **背景音乐**：8-bit循环曲目，增强沉浸感。  

**示例动画帧**：  
1. 初始DFS处理节点2，子树（2,3,4）高亮，显示 `dp[2] = 3 + 3 = 6`。  
2. 换根到节点2时，父节点1的贡献减少3，新增 `(4-3)*1 = 1`，总代价更新为 `6 + (8-3+1) = 12`。

---
处理用时：117.77秒