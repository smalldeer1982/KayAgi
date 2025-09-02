# 题目信息

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 5 6
```

### 输出

```
5```

# AI分析结果



### 综合分析与结论

**核心思路**  
各题解均围绕二进制操作展开，核心是将每个数的二进制表示视为树结构（完全二叉树或 Trie），通过遍历或动态规划找到所有数可达的公共节点，并计算最小操作次数。

**贪心策略与树结构方法的对比**  
- **贪心方法**：部分题解尝试寻找最长公共前缀（LCP）后枚举补零次数，但需验证是否能覆盖所有可能情况。例如，KυρωVixen 的题解通过预处理公共前缀并枚举补零次数，结合操作次数的最小调整，可能覆盖更多情况。
- **树结构方法**：通过构建完全二叉树，利用换根 DP 高效计算每个节点的总操作次数，时间复杂度更低（O(n + max a_i)），覆盖所有可能的公共节点。

**难点与解决方案**  
- **难点**：如何高效枚举所有可能的公共节点并计算操作次数。
- **解决**：基于完全二叉树的换根 DP 算法，利用子树大小动态调整总操作次数，避免重复计算。

**可视化设计思路**  
- **树状结构展示**：以完全二叉树形式展示每个节点，高亮当前计算的公共节点。
- **换根动画**：展示换根时操作次数的动态调整，子树节点减少操作次数，其余节点增加。
- **像素风格与音效**：8位像素风格节点，操作时播放音效，自动演示换根过程。

---

### 题解清单（≥4星）

1. **KokiNiwa（⭐⭐⭐⭐⭐）**  
   - **亮点**：使用完全二叉树结构，换根 DP 高效计算，代码简洁，时间复杂度 O(n + max a_i)。
   - **代码**：通过子树大小动态调整操作次数，避免显式建树。

2. **Mr_Wu（⭐⭐⭐⭐⭐）**  
   - **亮点**：找到 LCA 后向左子树换根，公式化操作次数调整（ans -= siz[x<<1], ans += n - siz[x<<1]）。
   - **代码**：简洁高效，仅需一次 DFS 和换根循环。

3. **Marsrayd（⭐⭐⭐⭐）**  
   - **亮点**：两次 DFS 分别计算初始答案和换根调整，逻辑清晰。
   - **心得**：强调操作次数的公式推导，换根时的步数调整直观。

---

### 最优思路与代码实现

**核心贪心逻辑**  
通过完全二叉树的换根 DP 实现：  
1. **DFS 初始化**：计算每个节点的子树大小（siz）和初始操作次数。
2. **换根调整**：从 LCA 出发，每次向左儿子移动，利用公式更新总操作次数。

**关键代码片段（Mr_Wu）**  
```cpp
void dfs(int u) {
    if (u > M) return;
    dep[u << 1] = dep[u << 1 | 1] = dep[u] + 1, dfs(u << 1), dfs(u << 1 | 1);
    siz[u] = siz[u << 1] + siz[u << 1 | 1] + vis[u];
}

// 换根循环
while ((root << 1) <= M) {
    tans += -siz[root << 1] + (N - siz[root << 1]);
    root = root << 1;
    ans = min(ans, tans);
}
```

---

### 同类型题与算法套路

**通用解法**  
- **树结构换根 DP**：适用于需要通过操作（如乘除、位移）转换到公共节点的题目。
- **贪心调整**：枚举所有可能的公共状态，统计最小操作次数。

**推荐题目**  
1. **P1966 火柴排队**（贪心排序与逆序对）
2. **P5019 铺设道路**（贪心区间覆盖）
3. **P2899 [USACO08JAN]Cell Phone Network G**（树形 DP 与贪心覆盖）

---

### 个人心得摘录

- **KokiNiwa**：强调处理重复状态的重要性，避免在 Trie 树中重复计数。
- **Marsrayd**：调试中发现直接向上走到 LCA 的操作次数计算错误，改用公式推导后通过。

---

### 可视化与算法演示

**像素风格树结构**  
- **Canvas 绘制**：每个节点为像素方块，颜色区分当前节点和操作路径。
- **自动换根演示**：AI 模式自动执行换根步骤，高亮子树大小变化。

**音效与交互**  
- **操作音效**：换根时播放不同音调，成功找到最小值时触发奖励音效。
- **关卡模式**：将换根步骤拆分为子关卡，通关后展示当前最优解。

```javascript
// 示例：Canvas 绘制节点
function drawNode(x, y, isCurrent) {
    ctx.fillStyle = isCurrent ? '#FF0000' : '#00FF00';
    ctx.fillRect(x * 30, y * 30, 25, 25);
}
```

**动画效果**  
- **步进控制**：用户可调整速度或单步观察换根过程。
- **连击积分**：连续正确换根选择增加连击分，提升沉浸感。

---
处理用时：125.32秒