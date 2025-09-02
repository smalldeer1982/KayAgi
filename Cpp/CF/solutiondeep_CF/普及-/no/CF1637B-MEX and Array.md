# 题目信息

# MEX and Array

## 题目描述

Let there be an array $ b_1, b_2, \ldots, b_k $ . Let there be a partition of this array into segments $ [l_1; r_1], [l_2; r_2], \ldots, [l_c; r_c] $ , where $ l_1 = 1 $ , $ r_c = k $ , and for any $ 2 \leq i \leq c $ holds that $ r_{i-1} + 1 = l_i $ . In other words, each element of the array belongs to exactly one segment.

Let's define the cost of a partition as $c + \sum_{i = 1}^{c} \operatorname{mex}(\{b_{l_i}, b_{l_i + 1}, \ldots, b_{r_i}\}), $  where  $ \\operatorname{mex} $  of a set of numbers  $ S $  is the smallest non-negative integer that does not occur in the set  $ S $ . In other words, the cost of a partition is the number of segments plus the sum of MEX over all segments. Let's define the value of an array  $ b_1, b_2, \ldots, b_k $  as the maximum possible cost over all partitions of this array. You are given an array  $ a $  of size  $ n $ . Find the sum of values of all its subsegments.An array  $ x $  is a subsegment of an array  $ y $  if  $ x $  can be obtained from  $ y$ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

In the second test case:

- The best partition for the subsegment $ [2, 0, 1] $ : $ [2], [0, 1] $ . The cost of this partition equals to $ 2 + \operatorname{mex}(\{2\}) + \operatorname{mex}(\{0, 1\}) = 2 + 0 + 2 = 4 $ .
- The best partition for the subsegment $ [2, 0] $ : $ [2], [0] $ . The cost of this partition equals to $ 2 + \operatorname{mex}(\{2\}) + \operatorname{mex}(\{0\}) = 2 + 0 + 1 = 3 $
- The best partition for the subsegment $ [2] $ : $ [2] $ . The cost of this partition equals to $ 1 + \operatorname{mex}(\{2\}) = 1 + 0 = 1 $ .
- The best partition for the subsegment $ [0, 1] $ : $ [0, 1] $ . The cost of this partition equals to $ 1 + \operatorname{mex}(\{0, 1\}) = 1 + 2 = 3 $ .
- The best partition for the subsegment $ [0] $ : $ [0] $ . The cost of this partition equals to $ 1 + \operatorname{mex}(\{0\}) = 1 + 1 = 2 $ .
- The best partition for the subsegment $ [1] $ : $ [1] $ . The cost of this partition equals to $ 1 + \operatorname{mex}(\{1\}) = 1 + 0 = 1 $ .

The sum of values over all subsegments equals to $ 4 + 3 + 1 + 3 + 2 + 1 = 14 $ .

## 样例 #1

### 输入

```
4
2
1 2
3
2 0 1
4
2 0 5 1
5
0 1 1 0 1```

### 输出

```
4
14
26
48```

# AI分析结果

### 题目内容
#### MEX和数组
1. **题目描述**：
设有一个数组\(b_1, b_2, \ldots, b_k\) 。将这个数组划分为若干段\([l_1; r_1], [l_2; r_2], \ldots, [l_c; r_c]\)，其中\(l_1 = 1\)，\(r_c = k\)，并且对于任意\(2 \leq i \leq c\)，都有\(r_{i - 1} + 1 = l_i\)。换句话说，数组中的每个元素都恰好属于一段。
我们定义一种划分的代价为\(c + \sum_{i = 1}^{c} \text{mex}(\{b_{l_i}, b_{l_i + 1}, \ldots, b_{r_i}\})\)，其中集合\(S\)的\(\text{mex}\)是指最小的不在集合\(S\)中出现的非负整数。也就是说，划分的代价是段数加上所有段的\(\text{mex}\)之和。我们定义数组\(b_1, b_2, \ldots, b_k\)的值为该数组所有划分中可能的最大代价。给定一个大小为\(n\)的数组\(a\)，求其所有子段的值的总和。如果数组\(x\)可以通过从数组\(y\)的开头和结尾删除若干（可能为零个或全部）元素得到，那么数组\(x\)就是数组\(y\)的一个子段。
2. **说明/提示**：
在第二个测试用例中：
 - 对于子段\([2, 0, 1]\)，最优划分是\([2], [0, 1]\)。这种划分的代价等于\(2 + \text{mex}(\{2\}) + \text{mex}(\{0, 1\}) = 2 + 0 + 2 = 4\)。
 - 对于子段\([2, 0]\)，最优划分是\([2], [0]\)。这种划分的代价等于\(2 + \text{mex}(\{2\}) + \text{mex}(\{0\}) = 2 + 0 + 1 = 3\)。
 - 对于子段\([2]\)，最优划分是\([2]\)。这种划分的代价等于\(1 + \text{mex}(\{2\}) = 1 + 0 = 1\)。
 - 对于子段\([0, 1]\)，最优划分是\([0, 1]\)。这种划分的代价等于\(1 + \text{mex}(\{0, 1\}) = 1 + 2 = 3\)。
 - 对于子段\([0]\)，最优划分是\([0]\)。这种划分的代价等于\(1 + \text{mex}(\{0\}) = 1 + 1 = 2\)。
 - 对于子段\([1]\)，最优划分是\([1]\)。这种划分的代价等于\(1 + \text{mex}(\{1\}) = 1 + 0 = 1\)。
所有子段的值的总和等于\(4 + 3 + 1 + 3 + 2 + 1 = 14\)。
3. **样例 #1**
    - **输入**：
```
4
2
1 2
3
2 0 1
4
2 0 5 1
5
0 1 1 0 1
```
    - **输出**：
```
4
14
26
48
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先分析对于一个子段如何划分能得到最大代价，进而计算所有子段的最大代价和。大多题解通过分析发现将每个元素单独作为一段是最优划分方式。
 - **思路方面**：多数题解通过对不同情况（子段含0或不含0等）进行分析，得出每个元素单独成段代价最大的结论，再基于此计算所有子段贡献。如miao5题解考虑贪心让每个数发挥最大代价；windflower题解从不含0和含0子段分别分析代价；Novice233题解通过计算比较得出每个元素单独成段最优。
 - **算法要点**：由于数据范围小，大多采用\(O(n^2)\)枚举子段，再统计每个子段最大代价。部分题解通过推导得出非0元素对每个子段贡献为1，0元素贡献为2，从而优化计算。
 - **解决难点**：难点在于证明每个元素单独成段是最优划分。部分题解通过对包含不同数字情况的子段分别分析，比较划分前后代价得出结论。如清烛题解对包含\(\{0, 1, 2,\cdots, m\}\) 、包含\(\{0, 1, 2,\cdots, m\}\)及其他数、不包含0这几种情况分别证明。

### 通用建议与扩展思路
对于此类问题，关键在于通过对不同情况的细致分析找到最优划分策略。可进一步思考当数据范围增大时，如何优化算法，如能否通过预处理某些信息来降低时间复杂度。也可拓展到其他类似的数组划分并计算代价的问题，分析不同代价计算方式下的最优策略。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据的分析找到最优排序策略，与本题分析最优划分策略类似。
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：需分析如何安排顺序使总等待时间最小，同样涉及对最优策略的寻找。
 - [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：通过不同算法求解逆序对数量，与本题在数组处理和分析上有一定相似性。 

---
处理用时：47.53秒