# 题目信息

# Rebellion

## 题目描述

You have an array $ a $ of size $ n $ consisting only of zeroes and ones. You can do the following operation:

- choose two indices $ 1 \le i , j \le n $ , $ i \ne j $ ,
- add $ a_{i} $ to $ a_{j} $ ,
- remove $ a_{i} $ from $ a $ .

Note that elements of $ a $ can become bigger than $ 1 $ after performing some operations. Also note that $ n $ becomes $ 1 $ less after the operation.

What is the minimum number of operations needed to make $ a $ non-decreasing, i. e. that each element is not less than the previous element?

## 说明/提示

In the first test case, $ a $ is already non-decreasing, so you don't need to do any operations and the answer is $ 0 $ .

In the second test case, you can perform an operation for $ i = 1 $ and $ j = 5 $ , so $ a $ will be equal to $ [0, 0, 1, 2] $ and it becomes non-decreasing.

In the third test case, you can perform an operation for $ i = 2 $ and $ j = 1 $ , so $ a $ will be equal to $ [1] $ and it becomes non-decreasing.

## 样例 #1

### 输入

```
4
8
0 0 1 1 1 1 1 1
5
1 0 0 1 1
2
1 0
11
1 1 0 0 1 0 0 1 1 1 0```

### 输出

```
0
1
1
3```

# AI分析结果

### 题目内容
# 反抗

## 题目描述
你有一个大小为 $n$ 的数组 $a$，数组中仅由 $0$ 和 $1$ 组成。你可以进行以下操作：
- 选择两个索引 $1 \leq i, j \leq n$，且 $i \neq j$，
- 将 $a_{i}$ 加到 $a_{j}$ 上，
- 从 $a$ 中移除 $a_{i}$。

注意，在执行一些操作后，$a$ 的元素可能会大于 $1$。同时注意，操作后 $n$ 会减少 $1$。

要使 $a$ 变为非递减数组，即每个元素都不小于前一个元素，所需的最小操作次数是多少？

## 说明/提示
在第一个测试用例中，$a$ 已经是非递减的，所以你不需要进行任何操作，答案为 $0$。

在第二个测试用例中，你可以对 $i = 1$ 和 $j = 5$ 执行操作，这样 $a$ 将变为 $[0, 0, 1, 2]$，它就变成非递减的了。

在第三个测试用例中，你可以对 $i = 2$ 和 $j = 1$ 执行操作，这样 $a$ 将变为 $[1]$，它就变成非递减的了。

## 样例 #1
### 输入
```
4
8
0 0 1 1 1 1 1 1
5
1 0 0 1 1
2
1 0
11
1 1 0 0 1 0 0 1 1 1 0
```
### 输出
```
0
1
1
3
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是将原序列转化为类似 $000\cdots111$ 的非递减序列以达到最小操作次数。
 - **思路方面**：多数题解考虑到删除前面的 $1$ 并加到后面的 $0$ 上是最优操作，少数通过排序后对比错位情况求解。
 - **算法要点**：主要通过统计 $0$ 和 $1$ 的数量、位置，或者直接模拟将前面的 $1$ 与后面的 $0$ 匹配的过程来计算操作次数。
 - **解决难点**：难点在于理解如何操作能使操作次数最小，即为何将前面的 $1$ 加到后面的 $0$ 上是最优选择。各题解通过不同方式阐述此关键逻辑，部分通过举例说明其他操作方式不优，部分直接从最终目标序列出发推导。

### 通用建议与扩展思路
解决此类问题关键在于找出最优的操作策略，可通过分析不同操作对最终目标序列的影响来确定。对于类似数组变换求最小操作次数的题目，通常要先明确最终目标状态，再思考如何以最少步骤达成。可拓展到其他元素取值有限且目标为特定顺序的数组变换问题，同样从寻找最优操作策略入手。

### 洛谷相似题目推荐
 - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过合并果子求最小代价，与本题类似在于都需寻找最优合并策略以达最小结果。
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及选择武将使收益最大，需考虑最优选择策略，与本题思路有相通之处。
 - [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：通过处理序列求最长重复子串，在寻找最优解的思考方式上可类比本题。 

---
处理用时：30.15秒