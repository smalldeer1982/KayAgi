# 题目信息

# XY Sequence

## 题目描述

You are given four integers $ n $ , $ B $ , $ x $ and $ y $ . You should build a sequence $ a_0, a_1, a_2, \dots, a_n $ where $ a_0 = 0 $ and for each $ i \ge 1 $ you can choose:

- either $ a_i = a_{i - 1} + x $
- or $ a_i = a_{i - 1} - y $ .

Your goal is to build such a sequence $ a $ that $ a_i \le B $ for all $ i $ and $ \sum\limits_{i=0}^{n}{a_i} $ is maximum possible.

## 说明/提示

In the first test case, the optimal sequence $ a $ is $ [0, 1, 2, 3, 4, 5] $ .

In the second test case, the optimal sequence $ a $ is $ [0, 10^9, 0, 10^9, 0, 10^9, 0, 10^9] $ .

In the third test case, the optimal sequence $ a $ is $ [0, -3, -6, 1, -2] $ .

## 样例 #1

### 输入

```
3
5 100 1 30
7 1000000000 1000000000 1000000000
4 1 7 3```

### 输出

```
15
4000000000
-10```

# AI分析结果

### 题目内容
# XY序列

## 题目描述
给定四个整数 $n$、$B$、$x$ 和 $y$ 。需要构建一个序列 $a_0, a_1, a_2, \dots, a_n$ ，其中 $a_0 = 0$ ，对于每个 $i \geq 1$ ，可以选择：
 - 要么 $a_i = a_{i - 1} + x$ 
 - 要么 $a_i = a_{i - 1} - y$ 。

目标是构建这样一个序列 $a$ ，使得对于所有的 $i$ ，都有 $a_i \leq B$ ，并且 $\sum\limits_{i=0}^{n}{a_i}$ 尽可能大。

## 说明/提示
在第一个测试用例中，最优序列 $a$ 是 $[0, 1, 2, 3, 4, 5]$ 。
在第二个测试用例中，最优序列 $a$ 是 $[0, 10^9, 0, 10^9, 0, 10^9, 0, 10^9]$ 。
在第三个测试用例中，最优序列 $a$ 是 $[0, -3, -6, 1, -2]$ 。

## 样例 #1
### 输入
```
3
5 100 1 30
7 1000000000 1000000000 1000000000
4 1 7 3
```
### 输出
```
15
4000000000
-10
```

### 算法分类
贪心

### 综合分析与结论
所有题解均采用贪心算法解决该问题，思路核心为每次优先选择加法操作（即 $a_i = a_{i - 1} + x$ ），当加上 $x$ 后超过 $B$ 时，再选择减法操作（即 $a_i = a_{i - 1} - y$ ）。通过这种方式保证序列总和最大。各题解的不同主要体现在代码实现细节上，如输入输出方式、变量命名、是否优化空间等。

### 通用建议与扩展思路
 - **通用建议**：在实现贪心算法时，要清晰理解贪心策略的正确性，并在代码实现中注意边界条件和数据类型。像本题中数据范围较大，需要使用 `long long` 类型避免溢出。同时，在多组测试数据的情况下，注意变量的初始化。
 - **扩展思路**：类似的贪心问题通常可以通过分析每次操作对结果的影响，来确定贪心策略。例如，对于一些资源分配问题，每次优先选择价值高的资源进行分配等。同类型题目可能会在操作选择的条件、限制条件等方面进行变化，解题时需仔细分析题目条件，确定合适的贪心策略。

### 推荐题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
 - [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)

---
处理用时：20.17秒