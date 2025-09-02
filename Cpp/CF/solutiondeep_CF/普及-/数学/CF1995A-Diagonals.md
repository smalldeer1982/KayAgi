# 题目信息

# Diagonals

## 题目描述

Vitaly503 is given a checkered board with a side of $ n $ and $ k $ chips. He realized that all these $ k $ chips need to be placed on the cells of the board (no more than one chip can be placed on a single cell).

Let's denote the cell in the $ i $ -th row and $ j $ -th column as $ (i ,j) $ . A diagonal is the set of cells for which the value $ i + j $ is the same. For example, cells $ (3, 1) $ , $ (2, 2) $ , and $ (1, 3) $ lie on the same diagonal, but $ (1, 2) $ and $ (2, 3) $ do not. A diagonal is called occupied if it contains at least one chip.

Determine what is the minimum possible number of occupied diagonals among all placements of $ k $ chips.

## 说明/提示

In the first test case, there are no chips, so 0 diagonals will be occupied. In the second test case, both chips can be placed on diagonal $ (2, 1), (1, 2) $ , so the answer is 1. In the third test case, 3 chips can't be placed on one diagonal, but placing them on $ (1, 2), (2, 1), (1, 1) $ makes 2 diagonals occupied. In the 7th test case, chips will occupy all 5 diagonals in any valid placing.

## 样例 #1

### 输入

```
7
1 0
2 2
2 3
2 4
10 50
100 239
3 9```

### 输出

```
0
1
2
3
6
3
5```

# AI分析结果

【题目内容中文重写】
# 对角线

## 题目描述

Vitaly503 被给定一个边长为 $ n $ 的棋盘和 $ k $ 个棋子。他意识到需要将这些 $ k $ 个棋子放置在棋盘的单元格上（每个单元格最多只能放置一个棋子）。

我们将第 $ i $ 行和第 $ j $ 列的单元格表示为 $ (i, j) $。对角线是指所有满足 $ i + j $ 值相同的单元格的集合。例如，单元格 $ (3, 1) $、$ (2, 2) $ 和 $ (1, 3) $ 位于同一条对角线上，但 $ (1, 2) $ 和 $ (2, 3) $ 不在同一条对角线上。如果一条对角线上至少有一个棋子，则称该对角线被占据。

确定在所有可能的棋子放置方案中，被占据的对角线的最小数量是多少。

## 说明/提示

在第一个测试用例中，没有棋子，因此被占据的对角线数量为 0。在第二个测试用例中，两个棋子可以放置在 $ (2, 1) $ 和 $ (1, 2) $ 这条对角线上，因此答案为 1。在第三个测试用例中，3 个棋子不能全部放在一条对角线上，但将它们放置在 $ (1, 2) $、$ (2, 1) $ 和 $ (1, 1) $ 上时，被占据的对角线数量为 2。在第 7 个测试用例中，棋子无论如何放置都会占据所有 5 条对角线。

## 样例 #1

### 输入

```
7
1 0
2 2
2 3
2 4
10 50
100 239
3 9```

### 输出

```
0
1
2
3
6
3
5```

【题解分析与结论】

由于暂无题解，以下是一些通用建议与扩展思路：

1. **关键思路**：
   - 对角线的最小数量取决于棋子的数量 $ k $ 和棋盘的对角线总数 $ 2n-1 $。
   - 如果 $ k \leq n $，则可以将所有棋子放在同一条对角线上，最小占据对角线数量为 1。
   - 如果 $ k > n $，则需要将棋子分散到多条对角线上，最小占据对角线数量为 $ k - n + 1 $。

2. **算法优化**：
   - 通过数学推导，可以直接计算出最小占据对角线数量，而不需要实际模拟棋子的放置过程。

3. **代码实现**：
   - 核心代码可以通过简单的条件判断和数学计算来实现。

【推荐题目】
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008) - 考察数学思维和条件判断。
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012) - 考察字符串处理和数学思维。
3. [P1013 进制数](https://www.luogu.com.cn/problem/P1013) - 考察数学思维和进制转换。

【通用建议】
- 在解决类似问题时，优先考虑数学推导和优化，避免复杂的模拟过程。
- 通过分析问题的数学性质，可以简化问题的解决方案，提高代码的效率和可读性。

---
处理用时：26.15秒