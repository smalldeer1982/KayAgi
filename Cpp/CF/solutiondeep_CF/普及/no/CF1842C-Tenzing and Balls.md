# 题目信息

# Tenzing and Balls

## 题目描述

Enjoy erasing Tenzing, identified as Accepted!



Tenzing has $ n $ balls arranged in a line. The color of the $ i $ -th ball from the left is $ a_i $ .

Tenzing can do the following operation any number of times:

- select $ i $ and $ j $ such that $ 1\leq i < j \leq |a| $ and $ a_i=a_j $ ,
- remove $ a_i,a_{i+1},\ldots,a_j $ from the array (and decrease the indices of all elements to the right of $ a_j $ by $ j-i+1 $ ).

Tenzing wants to know the maximum number of balls he can remove.

## 说明/提示

In the first example, Tenzing will choose $ i=2 $ and $ j=3 $ in the first operation so that $ a=[1,3,3] $ . Then Tenzing will choose $ i=2 $ and $ j=3 $ again in the second operation so that $ a=[1] $ . So Tenzing can remove $ 4 $ balls in total.

In the second example, Tenzing will choose $ i=1 $ and $ j=3 $ in the first and only operation so that $ a=[2] $ . So Tenzing can remove $ 3 $ balls in total.

## 样例 #1

### 输入

```
2
5
1 2 2 3 3
4
1 2 1 2```

### 输出

```
4
3```

# AI分析结果

### 题目内容重写

Tenzing 有 $n$ 个球排成一行。第 $i$ 个球的颜色为 $a_i$。

Tenzing 可以进行以下操作任意次：

- 选择 $i$ 和 $j$，满足 $1 \leq i < j \leq |a|$ 且 $a_i = a_j$，
- 删除 $a_i, a_{i+1}, \ldots, a_j$ 并从数组中移除（并将 $a_j$ 右侧的所有元素的索引减少 $j - i + 1$）。

Tenzing 想知道他最多可以删除多少个球。

### 算法分类
动态规划

### 题解分析与结论
本题的核心是通过动态规划来求解最多可以删除的球数。各题解的主要思路是通过定义状态 $f_i$ 表示前 $i$ 个球中最多可以删除的球数，并通过优化转移方程来降低时间复杂度。大多数题解通过引入辅助数组（如 $mx$ 或 $sum$）来记录特定条件下的最大值，从而将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。

### 精选题解

#### 题解1：作者：Zhddd_ (赞：22)
- **星级**：5星
- **关键亮点**：通过引入 $mx$ 数组来记录 $f_{j-1} - j + 1$ 的最大值，从而在 $O(1)$ 时间内完成状态转移，思路清晰且代码简洁。
- **代码核心思想**：
  ```cpp
  for (int i = 1; i <= n; i++) {
      f[i] = max(f[i - 1], i + mx[a[i]]);
      mx[a[i]] = max(mx[a[i]], f[i - 1] - i + 1);
  }
  ```

#### 题解2：作者：_GW_ (赞：8)
- **星级**：4星
- **关键亮点**：通过 $sum$ 数组记录 $f_{j-1} - j$ 的最大值，优化了状态转移方程，代码实现较为清晰。
- **代码核心思想**：
  ```cpp
  for (int i = 1; i <= n; i++) {
      f[i] = max(f[i - 1], sum[a[i]] + i);
      sum[a[i]] = max(sum[a[i]], f[i - 1] - i + 1);
  }
  ```

#### 题解3：作者：highkj (赞：0)
- **星级**：4星
- **关键亮点**：通过 $Max$ 数组记录 $f_{i-1} - i + 1$ 的最大值，优化了状态转移方程，代码实现简洁。
- **代码核心思想**：
  ```cpp
  for (int i = 1; i <= n; i++) {
      f[i] = max(f[i - 1], Max[a[i]] + i);
      Max[a[i]] = max(Max[a[i]], f[i - 1] - i + 1);
  }
  ```

### 最优关键思路与技巧
1. **状态定义**：$f_i$ 表示前 $i$ 个球中最多可以删除的球数。
2. **优化转移**：通过引入辅助数组（如 $mx$、$sum$ 或 $Max$）来记录特定条件下的最大值，从而将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。
3. **代码实现**：简洁的代码实现和清晰的思路是解题的关键。

### 可拓展之处
类似的问题可以通过动态规划结合辅助数组来优化时间复杂度，例如区间删除、区间覆盖等问题。

### 推荐题目
1. [P1868 饥饿的奶牛](https://www.luogu.com.cn/problem/P1868)
2. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)

---
处理用时：26.52秒