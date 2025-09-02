# 题目信息

# Coin Rows

## 题目描述

Alice and Bob are playing a game on a matrix, consisting of $ 2 $ rows and $ m $ columns. The cell in the $ i $ -th row in the $ j $ -th column contains $ a_{i, j} $ coins in it.

Initially, both Alice and Bob are standing in a cell $ (1, 1) $ . They are going to perform a sequence of moves to reach a cell $ (2, m) $ .

The possible moves are:

- Move right — from some cell $ (x, y) $ to $ (x, y + 1) $ ;
- Move down — from some cell $ (x, y) $ to $ (x + 1, y) $ .

First, Alice makes all her moves until she reaches $ (2, m) $ . She collects the coins in all cells she visit (including the starting cell).

When Alice finishes, Bob starts his journey. He also performs the moves to reach $ (2, m) $ and collects the coins in all cells that he visited, but Alice didn't.

The score of the game is the total number of coins Bob collects.

Alice wants to minimize the score. Bob wants to maximize the score. What will the score of the game be if both players play optimally?

## 说明/提示

The paths for the testcases are shown on the following pictures. Alice's path is depicted in red and Bob's path is depicted in blue.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1555C/252b3575ef3aca0ba0371198bcb73812484716e5.png)

## 样例 #1

### 输入

```
3
3
1 3 7
3 5 1
3
1 3 9
3 5 1
1
4
7```

### 输出

```
7
8
0```

# AI分析结果

### 题目内容重写

Alice 和 Bob 在一个由 $2$ 行 $m$ 列组成的矩阵上玩游戏。矩阵中的每个单元格 $(i, j)$ 包含 $a_{i, j}$ 个硬币。初始时，Alice 和 Bob 都站在单元格 $(1, 1)$。他们需要通过一系列移动到达单元格 $(2, m)$。

可能的移动方式有两种：
- 向右移动：从单元格 $(x, y)$ 移动到 $(x, y + 1)$；
- 向下移动：从单元格 $(x, y)$ 移动到 $(x + 1, y)$。

Alice 先进行所有移动，直到她到达 $(2, m)$。她会收集所有经过的单元格中的硬币（包括起点）。当 Alice 完成后，Bob 开始他的移动。他也需要通过移动到达 $(2, m)$，并收集所有他经过但 Alice 没有经过的单元格中的硬币。

游戏的得分是 Bob 收集的硬币总数。Alice 希望最小化得分，Bob 希望最大化得分。如果双方都采取最优策略，游戏的得分会是多少？

### 算法分类
前缀和、贪心

### 题解分析与结论

题解的核心思路是通过枚举 Alice 的移动路径，计算 Bob 在每种情况下的最大得分，并取其中的最小值。由于矩阵只有两行，且移动方式受限，Alice 的路径选择实际上只有 $m$ 种可能（即她在哪一列向下移动）。对于每种选择，Bob 的得分只能是第一行的后缀和或第二行的前缀和中的最大值。因此，通过预处理前缀和和后缀和，可以快速计算每种情况下的得分，并取最小值作为最终答案。

### 评分较高的题解

#### 1. 作者：wind_seeker (赞：19)
**星级：4.5**
**关键亮点：**
- 通过画图直观展示了 Alice 和 Bob 的路径选择，帮助理解问题。
- 详细解释了前缀和和后缀和的计算方法，并给出了清晰的代码实现。
- 代码中使用了 `max` 和 `min` 函数来简化逻辑，提高了代码的可读性。

**代码核心思想：**
```cpp
for(int i=1;i<=m;i++) {
    sum1-=a[i]; // 红色部分从i+1开始
    ans[i]=max(sum1,sum2); // 取蓝色部分和红色部分中的大值
    answer=min(ans[i],answer); // 取所有大值中的最小值
    sum2+=b[i]; // 蓝色部分到i-1结束
}
```

#### 2. 作者：Gokix (赞：5)
**星级：4.0**
**关键亮点：**
- 简洁明了地指出了 Alice 走完后棋盘上剩下的两部分，并直接给出了预处理前缀和和后缀和的方法。
- 代码结构清晰，逻辑简单，易于理解。

**代码核心思想：**
```cpp
for(i=1;i<=n;i++) {
    ans=min(ans,max(pre[i-1],suf[i+1]));
}
```

#### 3. 作者：QZY2008 (赞：4)
**星级：4.0**
**关键亮点：**
- 强调了前缀和和后缀和的优化，避免了重复计算。
- 代码中使用了 `min` 和 `max` 函数，逻辑清晰，代码简洁。

**代码核心思想：**
```cpp
for(int i=1;i<=n;i++) {
    tmp=min(tmp,max(q_sum[i-1],h_sum[i+1]));
}
```

### 最优关键思路与技巧
1. **前缀和与后缀和的预处理**：通过预处理前缀和和后缀和，可以快速计算 Bob 在每种情况下的得分，避免了重复计算。
2. **枚举与贪心**：枚举 Alice 的所有可能路径，选择使 Bob 得分最小的路径，体现了贪心算法的思想。
3. **代码优化**：使用 `max` 和 `min` 函数简化逻辑，提高代码的可读性和效率。

### 可拓展之处
- 类似的问题可以扩展到更高维的矩阵，或者更复杂的移动规则，但核心思路仍然是枚举和贪心。
- 前缀和和后缀和的思想可以应用于其他需要快速计算区间和的问题。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：32.45秒