# 题目信息

# Rudolf and k Bridges

## 题目描述

Bernard loves visiting Rudolf, but he is always running late. The problem is that Bernard has to cross the river on a ferry. Rudolf decided to help his friend solve this problem.

The river is a grid of $ n $ rows and $ m $ columns. The intersection of the $ i $ -th row and the $ j $ -th column contains the number $ a_{i,j} $ — the depth in the corresponding cell. All cells in the first and last columns correspond to the river banks, so the depth for them is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/2420e4ab48e7eae57737cc3a1dbfde24de284901.png) The river may look like this.Rudolf can choose the row $ (i,1), (i,2), \ldots, (i,m) $ and build a bridge over it. In each cell of the row, he can install a support for the bridge. The cost of installing a support in the cell $ (i,j) $ is $ a_{i,j}+1 $ . Supports must be installed so that the following conditions are met:

1. A support must be installed in cell $ (i,1) $ ;
2. A support must be installed in cell $ (i,m) $ ;
3. The distance between any pair of adjacent supports must be no more than $ d $ . The distance between supports $ (i, j_1) $ and $ (i, j_2) $ is $ |j_1 - j_2| - 1 $ .

Building just one bridge is boring. Therefore, Rudolf decided to build $ k $ bridges on consecutive rows of the river, that is, to choose some $ i $ ( $ 1 \le i \le n - k + 1 $ ) and independently build a bridge on each of the rows $ i, i + 1, \ldots, i + k - 1 $ . Help Rudolf minimize the total cost of installing supports.

## 说明/提示

In the first test case, it is most profitable to build a bridge on the second row.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/7ad474029f5a4a6573b004238d770f23ae9fe42a.png) It is not a top view, but side view: gray cells — bridge itself, white cells are empty, black cells — supports, blue cells — water, brown cells — river bottom.In the second test case, it is most profitable to build bridges on the second and third rows. The supports will be placed in cells $ (2, 3) $ , $ (3, 2) $ , and on the river banks.

In the third test case the supports can be placed along the river banks.

## 样例 #1

### 输入

```
5
3 11 1 4
0 1 2 3 4 5 4 3 2 1 0
0 1 2 3 2 1 2 3 3 2 0
0 1 2 3 5 5 5 5 5 2 0
4 4 2 1
0 3 3 0
0 2 1 0
0 1 2 0
0 3 3 0
4 5 2 5
0 1 1 1 0
0 2 2 2 0
0 2 1 1 0
0 3 2 1 0
1 8 1 1
0 10 4 8 4 4 2 0
4 5 3 2
0 8 4 4 0
0 3 4 8 0
0 8 1 10 0
0 10 1 5 0```

### 输出

```
4
8
4
15
14```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

Bernard 喜欢拜访 Rudolf，但他总是迟到。问题的关键在于 Bernard 必须乘渡船过河。Rudolf 决定帮助他的朋友解决这个问题。

河流是一个 $n$ 行 $m$ 列的网格。第 $i$ 行第 $j$ 列的交叉点包含数字 $a_{i,j}$，表示该单元格的深度。第一列和最后一列的所有单元格对应河岸，因此它们的深度为 $0$。

Rudolf 可以选择某一行 $(i,1), (i,2), \ldots, (i,m)$ 并在其上建造一座桥。在每一行的每个单元格中，他可以安装一个桥墩。在单元格 $(i,j)$ 中安装桥墩的成本为 $a_{i,j}+1$。桥墩的安装必须满足以下条件：

1. 必须在单元格 $(i,1)$ 安装桥墩；
2. 必须在单元格 $(i,m)$ 安装桥墩；
3. 任何一对相邻桥墩之间的距离不得超过 $d$。桥墩 $(i, j_1)$ 和 $(i, j_2)$ 之间的距离为 $|j_1 - j_2| - 1$。

仅仅建造一座桥太无聊了。因此，Rudolf 决定在河流的连续 $k$ 行上建造 $k$ 座桥，即选择某个 $i$（$1 \le i \le n - k + 1$），并在每一行 $i, i + 1, \ldots, i + k - 1$ 上独立建造一座桥。帮助 Rudolf 最小化安装桥墩的总成本。

#### 说明/提示

在第一个测试用例中，最划算的是在第二行建造一座桥。

在第二个测试用例中，最划算的是在第二行和第三行建造桥。桥墩将放置在单元格 $(2, 3)$、$(3, 2)$ 以及河岸上。

在第三个测试用例中，桥墩可以沿着河岸放置。

#### 样例 #1

##### 输入

```
5
3 11 1 4
0 1 2 3 4 5 4 3 2 1 0
0 1 2 3 2 1 2 3 3 2 0
0 1 2 3 5 5 5 5 5 2 0
4 4 2 1
0 3 3 0
0 2 1 0
0 1 2 0
0 3 3 0
4 5 2 5
0 1 1 1 0
0 2 2 2 0
0 2 1 1 0
0 3 2 1 0
1 8 1 1
0 10 4 8 4 4 2 0
4 5 3 2
0 8 4 4 0
0 3 4 8 0
0 8 1 10 0
0 10 1 5 0
```

##### 输出

```
4
8
4
15
14
```

### 题解分析与结论

#### 综合分析与结论

本题的核心问题是如何在每一行中选择桥墩的位置，使得桥墩的安装成本最小，并且在连续 $k$ 行中选择最小的总成本。大多数题解都采用了动态规划（DP）结合单调队列优化的思路来解决这个问题。

1. **动态规划（DP）**：对于每一行，设 $f[i]$ 表示在第 $i$ 列安装桥墩的最小成本。状态转移方程为：
   \[
   f[i] = \min_{i-d-1 \le j < i} f[j] + a[i] + 1
   \]
   这个方程表示在第 $i$ 列安装桥墩的成本，取决于前 $d$ 列中最小成本加上当前列的成本。

2. **单调队列优化**：为了快速找到前 $d$ 列中的最小值，可以使用单调队列来维护一个滑动窗口的最小值。单调队列的优化使得时间复杂度从 $O(nmd)$ 降低到 $O(nm)$。

3. **前缀和优化**：在计算连续 $k$ 行的总成本时，可以使用前缀和来快速计算任意连续 $k$ 行的总成本，进一步优化时间复杂度。

#### 评分较高的题解

1. **题解作者：luobotianle（评分：5星）**
   - **关键亮点**：使用了单调队列优化 DP，代码清晰且高效，时间复杂度为 $O(T \cdot nm)$。
   - **核心代码**：
     ```cpp
     deque<ll> q;
     q.clear();
     f[1] = a[j][1] + 1;
     q.push_back(1);
     for (int i = 2; i <= m; i++) {
         if (!q.empty() && i - q.front() > d + 1) q.pop_front();
         f[i] = f[q.front()] + a[j][i] + 1;
         while (!q.empty() && f[q.back()] > f[i]) q.pop_back();
         q.push_back(i);
     }
     ```

2. **题解作者：2huk（评分：4星）**
   - **关键亮点**：同样使用了单调队列优化 DP，并且提供了线段树作为另一种优化方式的思路，代码结构清晰。
   - **核心代码**：
     ```cpp
     deque<int> q;
     q.push_back(1);
     f[1] = a[r][1] + 1;
     for (int i = 2; i <= m; i++) {
         while (!q.empty() && i - q.front() > d + 1) q.pop_front();
         f[i] = f[q.front()] + a[r][i] + 1;
         while (!q.empty() && f[q.back()] >= f[i]) q.pop_back();
         q.push_back(i);
     }
     ```

3. **题解作者：wsx248（评分：4星）**
   - **关键亮点**：详细解释了单调队列优化的思路，代码实现简洁，适合初学者理解。
   - **核心代码**：
     ```cpp
     deque<int> q;
     q.push_back(1);
     dp[1] = 1;
     for (int i = 2; i <= m; i++) {
         if (q.size() && q.front() < i - d - 1) q.pop_front();
         dp[i] = dp[q.front()] + a[i] + 1;
         while (q.size() && dp[q.back()] >= dp[i]) q.pop_back();
         q.push_back(i);
     }
     ```

#### 最优关键思路与技巧

- **单调队列优化**：单调队列是解决滑动窗口最小值问题的经典方法，能够将时间复杂度从 $O(n^2)$ 降低到 $O(n)$，适用于需要频繁查询区间最小值的场景。
- **前缀和优化**：前缀和可以快速计算任意区间的和，适用于需要频繁查询区间和的场景。

#### 可拓展之处

- **类似算法套路**：单调队列优化可以应用于其他需要滑动窗口最小值的 DP 问题，如最长上升子序列、最大子数组和等。
- **数据结构优化**：除了单调队列，线段树、优先队列等数据结构也可以用于优化 DP 问题。

#### 推荐题目

1. [P1725 琪露诺](https://www.luogu.com.cn/problem/P1725)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)

#### 个人心得摘录

- **调试经历**：在实现单调队列时，需要注意队列的维护顺序，先删除过期元素，再插入新元素，最后更新 DP 值。
- **踩坑教训**：在计算前缀和时，确保数组下标从 1 开始，避免越界错误。
- **顿悟感想**：单调队列的优化思路非常巧妙，能够大幅提升 DP 问题的效率，值得深入理解和掌握。

---
处理用时：75.31秒