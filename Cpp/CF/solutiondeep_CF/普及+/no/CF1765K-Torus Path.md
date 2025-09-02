# 题目信息

# Torus Path

## 题目描述

You are given a square grid with $ n $ rows and $ n $ columns, where each cell has a non-negative integer written in it. There is a chip initially placed at the top left cell (the cell with coordinates $ (1, 1) $ ). You need to move the chip to the bottom right cell (the cell with coordinates $ (n, n) $ ).

In one step, you can move the chip to the neighboring cell, but:

1. you can move only right or down. In other words, if the current cell is $ (x, y) $ , you can move either to $ (x, y + 1) $ or to $ (x + 1, y) $ . There are two special cases: 
  - if the chip is in the last column (cell $ (x, n) $ ) and you're moving right, you'll teleport to the first column (to the cell $ (x, 1) $ );
  - if the chip is in the last row (cell $ (n, y) $ ) and you're moving down, you'll teleport to the first row (to the cell $ (1, y) $ ).
2. you cannot visit the same cell twice. The starting cell is counted visited from the beginning (so you cannot enter it again), and you can't leave the finishing cell once you visit it.

Your total score is counted as the sum of numbers in all cells you have visited. What is the maximum possible score you can achieve?

## 样例 #1

### 输入

```
2
1 2
3 4```

### 输出

```
8```

## 样例 #2

### 输入

```
3
10 10 10
10 0 10
10 10 10```

### 输出

```
80```

# AI分析结果

### 题目内容重写
# 环形路径

## 题目描述

给定一个 $n$ 行 $n$ 列的正方形网格，每个单元格中写有一个非负整数。初始时，芯片位于左上角的单元格 $(1, 1)$。你需要将芯片移动到右下角的单元格 $(n, n)$。

每一步，你可以将芯片移动到相邻的单元格，但有以下限制：

1. 只能向右或向下移动。也就是说，如果当前单元格是 $(x, y)$，你可以移动到 $(x, y + 1)$ 或 $(x + 1, y)$。有两个特殊情况：
   - 如果芯片位于最后一列（单元格 $(x, n)$）并且你向右移动，芯片将传送到第一列（单元格 $(x, 1)$）；
   - 如果芯片位于最后一行（单元格 $(n, y)$）并且你向下移动，芯片将传送到第一行（单元格 $(1, y)$）。
2. 不能重复访问同一个单元格。起始单元格被视为已访问（因此不能再次进入），且一旦访问了终点单元格，就不能离开。

你的总得分为所有访问过的单元格中的数字之和。你能获得的最大可能得分是多少？

## 样例 #1

### 输入

```
2
1 2
3 4```

### 输出

```
8```

## 样例 #2

### 输入

```
3
10 10 10
10 0 10
10 10 10```

### 输出

```
80```

### 算法分类
动态规划

### 题解分析与结论
1. **Alex_Wei的题解**：使用动态规划，状态定义为 $f_{i, j, k}$，表示第一次进入第 $i$ 列的位置为 $(k, i)$，当前位置为 $(j, i)$ 的最大收益。通过DFS进行状态转移，时间复杂度为 $\mathcal{O}(n^3)$。该解法能够处理负数情况，但复杂度较高。
2. **Dog_E的题解**：采用贪心策略，通过分析发现无法访问副对角线上的一个格子，因此直接计算所有格子的总和并减去副对角线上最小的值。时间复杂度为 $\mathcal{O}(n^2)$，简洁高效，但无法处理负数情况。
3. **hanjinghao的题解**：通过分析路径穿越的性质，将问题分为只横向穿越和只纵向穿越两种情况，分别计算最大得分。使用前缀和优化状态转移，时间复杂度为 $\mathcal{O}(n^2)$。该解法思路清晰，但实现较为复杂。

### 所选高星题解
1. **Dog_E的题解**（4星）
   - **关键亮点**：简洁高效的贪心策略，直接计算总和并减去副对角线上最小值，时间复杂度低。
   - **代码核心思想**：计算所有格子的总和，并找到副对角线上最小的值，最终输出总和减去最小值。
   ```cpp
   int n;
   int a[110][110];
   long long sum, minn = 2E9;

   int main() {
       ios::sync_with_stdio(0);
       cin >> n;
       for (int i = 0; i < n; i++) {
           for (int j = 0; j < n; j++) {
               cin >> a[i][j];
               sum += a[i][j];
           }
           minn = min(minn, 1LL * a[i][n - i - 1]);
       }
       cout << sum - minn << "\n";
       return 0;
   }
   ```

### 最优关键思路
- **贪心策略**：通过分析路径性质，发现无法访问副对角线上的一个格子，因此直接计算总和并减去该最小值，时间复杂度低且实现简单。

### 可拓展之处
- 类似问题可以考虑路径限制下的最大得分问题，结合贪心或动态规划进行优化。

### 推荐题目
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
2. [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：33.61秒