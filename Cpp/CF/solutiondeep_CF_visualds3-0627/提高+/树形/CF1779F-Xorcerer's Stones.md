# 题目信息

# Xorcerer's Stones

## 题目描述

Misha had been banned from playing chess for good since he was accused of cheating with an engine. Therefore, he retired and decided to become a xorcerer.

One day, while taking a walk in a park, Misha came across a rooted tree with nodes numbered from $ 1 $ to $ n $ . The root of the tree is node $ 1 $ .

For each $ 1\le i\le n $ , node $ i $ contains $ a_i $ stones in it. Misha has recently learned a new spell in his xorcery class and wants to test it out. A spell consists of:

- Choose some node $ i $ ( $ 1 \leq i \leq n $ ).
- Calculate the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) $ x $ of all $ a_j $ such that node $ j $ is in the subtree of $ i $ ( $ i $ belongs to its own subtree).
- Set $ a_j $ equal to $ x $ for all nodes $ j $ in the subtree of $ i $ .

Misha can perform at most $ 2n $ spells and he wants to remove all stones from the tree. More formally, he wants $ a_i=0 $ to hold for each $ 1\leq i \leq n $ . Can you help him perform the spells?

A tree with $ n $ nodes is a connected acyclic graph which contains $ n-1 $ edges. The subtree of node $ i $ is the set of all nodes $ j $ such that $ i $ lies on the simple path from $ 1 $ (the root) to $ j $ . We consider $ i $ to be contained in its own subtree.

## 说明/提示

Please refer to the following pictures for an explanation of the third test. Only the first $ 4 $ spells are shown since the last $ 2 $ do nothing. The first picture represents the tree initially with the number of stones for each node written above it in green. Changes applied by the current spell are highlighted in red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1779F/87049d0f1cff376d7b36c99b33f175c4877519fa.png)

## 样例 #1

### 输入

```
2
13 13
1```

### 输出

```
1
1```

## 样例 #2

### 输入

```
7
5 2 8 3 4 1 31
1 1 2 2 3 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
9
3 31 1 2 7 30 7 3 1
1 1 1 2 5 5 3 4```

### 输出

```
6
3 2 3 1 2 2```

# AI分析结果



## 算法分类
**动态规划（树形DP）**

---

## 题解思路与核心难点

### 核心思路
1. **奇偶子树性质**：操作偶数大小的子树可以改变整体异或和，奇数大小子树不影响。
2. **操作序列约束**：操作节点必须互不为祖先，最终需操作根节点清零。
3. **动态规划**：用背包模型找符合条件的节点集合，满足异或和等于初始根异或值。

### 关键实现
1. **DFS预处理**：计算子树大小 `siz` 和异或值 `val`。
2. **线性DP设计**：在DFS序上进行状态转移，`f[i][j]` 表示前 `i` 个节点异或和为 `j` 是否可行。
3. **路径回溯**：根据DP结果逆向构造操作序列。

---

## 题解评分（≥4星）

1. **namelessgugugu（★★★★★）**  
   - **亮点**：线性DFS序DP降低复杂度，代码简洁高效，路径回溯清晰。
   - **代码**：预处理DFS序后，用一维数组实现状态转移，空间优化到位。

2. **Mars_Dingdang（★★★★）**  
   - **亮点**：自底向上树形DP，状态合并逻辑明确。
   - **不足**：使用 `vector` 管理状态，空间复杂度略高。

3. **Rushroom（★★★★）**  
   - **亮点**：代码简洁，回溯函数设计直观。
   - **不足**：状态转移部分未显式优化，但整体思路清晰。

---

## 最优思路提炼

1. **关键观察**  
   - 偶数子树操作改变异或和，奇数子树不影响。
   - 操作序列需互不为祖先，最终必操作根节点。

2. **算法核心**  
   - **DFS序背包DP**：将树转为线性结构，状态 `f[i][j]` 表示处理前 `i` 个节点能否得到异或和 `j`。
   - **转移方程**：  
     - 不选当前节点：`f[i+1][j]`  
     - 选当前节点（若为偶数）：`f[i+siz][j^val]`

3. **路径回溯**  
   - 逆向遍历DP状态，记录选中的节点并加入根节点操作。

---

## 同类型题目推荐

1. **CF1774E**：树结构动态规划，要求最小化操作次数。
2. **CF1494D**：基于子树性质的最优化问题。
3. **P2014 选课**：树形背包问题的经典变种。

---

## 代码核心片段

```cpp
// DFS预处理子树大小和异或值
void dfs(int x, int from) {
    dfn[++tt] = x, siz[x] = 1, val[x] = a[x];
    for (int i = head[x]; i; i = E[i].nxt) {
        int y = E[i].to;
        if(y == from) continue;
        dfs(y, x), siz[x] += siz[y], val[x] ^= val[y];
    }
}

// DP状态转移
for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 32; ++j) {
        if(f[i][j].first == -1) continue;
        int v = (siz[dfn[i]] & 1) ? 0 : val[dfn[i]];
        // 不选当前节点
        f[i + 1][j] = {i, j};
        // 选当前节点（偶数子树）
        f[i + siz[dfn[i]]][j ^ v] = {i, j};
    }
}

// 回溯构造操作序列
while(u != 0) {
    int tu = f[u][v].first, tv = f[u][v].second;
    if(u - tu == siz[dfn[tu]]) ans.push_back(dfn[tu]);
    u = tu, v = tv;
}
ans.push_back(1); // 最后操作根节点
```

---

## 可视化设计

### 动画演示方案
1. **DFS遍历**：  
   - 显示树结构，高亮当前遍历节点，逐步生成 `dfn` 数组。
2. **DP状态转移**：  
   - 网格展示 `f[i][j]`，动态更新可行状态，颜色区分选中/未选中。
3. **操作序列回溯**：  
   - 逆向路径用红色箭头标出，最终操作根节点时播放成功音效。

### 复古像素风格
- **颜色方案**：8位色（绿-未处理，红-选中，蓝-操作）。
- **Canvas绘制**：树节点显示为方块，DP网格实时更新。
- **音效**：  
  - 操作成功：8-bit 上升音阶。  
  - 状态更新：短促“哔”声。

---

## 总结

通过动态规划在DFS序上高效解决子树选择问题，结合奇偶性质优化操作次数，最终通过回溯构造合法操作序列。该思路兼顾时间复杂度和实现简洁性，是此类树形问题的典型解法。

---
处理用时：81.97秒