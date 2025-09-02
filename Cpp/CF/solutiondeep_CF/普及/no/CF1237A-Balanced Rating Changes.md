# 题目信息

# Balanced Rating Changes

## 题目描述

Another Codeforces Round has just finished! It has gathered $ n $ participants, and according to the results, the expected rating change of participant $ i $ is $ a_i $ . These rating changes are perfectly balanced — their sum is equal to $ 0 $ .

Unfortunately, due to minor technical glitches, the round is declared semi-rated. It means that all rating changes must be divided by two.

There are two conditions though:

- For each participant $ i $ , their modified rating change $ b_i $ must be integer, and as close to $ \frac{a_i}{2} $ as possible. It means that either $ b_i = \lfloor \frac{a_i}{2} \rfloor $ or $ b_i = \lceil \frac{a_i}{2} \rceil $ . In particular, if $ a_i $ is even, $ b_i = \frac{a_i}{2} $ . Here $ \lfloor x \rfloor $ denotes rounding down to the largest integer not greater than $ x $ , and $ \lceil x \rceil $ denotes rounding up to the smallest integer not smaller than $ x $ .
- The modified rating changes must be perfectly balanced — their sum must be equal to $ 0 $ .

Can you help with that?

## 说明/提示

In the first example, $ b_1 = 5 $ , $ b_2 = -3 $ and $ b_3 = -2 $ is another correct solution.

In the second example there are $ 6 $ possible solutions, one of them is shown in the example output.

## 样例 #1

### 输入

```
3
10
-5
-5
```

### 输出

```
5
-2
-3
```

## 样例 #2

### 输入

```
7
-7
-29
0
3
24
-29
38
```

### 输出

```
-3
-15
0
2
12
-15
19
```

# AI分析结果

### 题目内容重写
# Balanced Rating Changes

## 题目描述

又一场Codeforces比赛结束了！这次比赛有 $ n $ 名参与者，根据比赛结果，参与者 $ i $ 的预期评分变化为 $ a_i $。这些评分变化是完美平衡的——它们的总和为 $ 0 $。

不幸的是，由于一些小的技术故障，比赛被宣布为半评分。这意味着所有评分变化必须除以二。

但有两个条件：

- 对于每个参与者 $ i $，他们的修改后的评分变化 $ b_i $ 必须是整数，并且尽可能接近 $ \frac{a_i}{2} $。这意味着 $ b_i = \lfloor \frac{a_i}{2} \rfloor $ 或 $ b_i = \lceil \frac{a_i}{2} \rceil $。特别地，如果 $ a_i $ 是偶数，$ b_i = \frac{a_i}{2} $。这里 $ \lfloor x \rfloor $ 表示向下取整到不大于 $ x $ 的最大整数，$ \lceil x \rceil $ 表示向上取整到不小于 $ x $ 的最小整数。
- 修改后的评分变化必须是完美平衡的——它们的总和必须为 $ 0 $。

你能帮忙解决这个问题吗？

## 说明/提示

在第一个示例中，$ b_1 = 5 $，$ b_2 = -3 $ 和 $ b_3 = -2 $ 是另一个正确的解。

在第二个示例中有 $ 6 $ 个可能的解，其中一个在示例输出中展示。

## 样例 #1

### 输入

```
3
10
-5
-5
```

### 输出

```
5
-2
-3
```

## 样例 #2

### 输入

```
7
-7
-29
0
3
24
-29
38
```

### 输出

```
-3
-15
0
2
12
-15
19
```

### 算法分类
贪心

### 题解分析与结论
本题的核心在于如何处理奇数的评分变化，使得最终的总和保持为0。大多数题解都采用了贪心策略，通过交替进行向上和向下取整来平衡奇数的贡献。

### 所选高星题解
1. **作者：fengqiao17 (4星)**
   - **关键亮点**：通过一个标志位 `flag` 来交替进行向上和向下取整，代码简洁且易于理解。
   - **代码片段**：
     ```cpp
     int flag = 1;
     for (int i = 1; i <= n; i++) {
         int x;
         scanf("%d", &x);
         if (x % 2 == 1) {
             printf("%d\n", (x + flag) / 2);
             flag *= -1;
         } else {
             printf("%d\n", x / 2);
         }
     }
     ```

2. **作者：Mubuky (4星)**
   - **关键亮点**：提供了两种思路，第一种思路通过调整奇数的取整方式来平衡总和，第二种思路与fengqiao17类似，使用标志位进行交替取整。
   - **代码片段**：
     ```cpp
     int flag = 1;
     for (int i = 1; i <= n; i++) {
         int x;
         scanf("%d", &x);
         if (x % 2) {
             printf("%d\n", (x + flag) / 2);
             flag *= -1;
         } else {
             printf("%d\n", x / 2);
         }
     }
     ```

3. **作者：StudyingFather (4星)**
   - **关键亮点**：简洁明了地解释了如何处理奇数的取整问题，并通过标志位实现交替取整。
   - **代码片段**：
     ```cpp
     int f = 1;
     for (int i = 1; i <= n; i++) {
         int x;
         scanf("%d", &x);
         if (x % 2 == 0) printf("%d\n", x / 2);
         else printf("%d\n", (x + f) / 2), f *= -1;
     }
     ```

### 最优关键思路或技巧
- **交替取整**：通过一个标志位（如 `flag` 或 `f`）来交替进行向上和向下取整，确保奇数的贡献相互抵消，从而保持总和为0。
- **贪心策略**：在处理奇数时，采用贪心策略，尽可能简单高效地解决问题。

### 可拓展之处
- **类似问题**：可以扩展到其他需要平衡总和的问题，如资源分配、任务调度等。
- **算法套路**：贪心算法在处理需要快速决策且局部最优能导致全局最优的问题时非常有效。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

### 个人心得摘录
- **fengqiao17**：通过标志位实现交替取整，代码简洁且易于理解。
- **Mubuky**：提供了两种思路，第一种思路通过调整奇数的取整方式来平衡总和，第二种思路与fengqiao17类似，使用标志位进行交替取整。
- **StudyingFather**：简洁明了地解释了如何处理奇数的取整问题，并通过标志位实现交替取整。

---
处理用时：36.04秒