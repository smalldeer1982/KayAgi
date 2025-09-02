# 题目信息

# Permutation

## 题目描述

Recall that a permutation of length $ n $ is an array where each element from $ 1 $ to $ n $ occurs exactly once.

For a fixed positive integer $ d $ , let's define the cost of the permutation $ p $ of length $ n $ as the number of indices $ i $ $ (1 \le i < n) $ such that $ p_i \cdot d = p_{i + 1} $ .

For example, if $ d = 3 $ and $ p = [5, 2, 6, 7, 1, 3, 4] $ , then the cost of such a permutation is $ 2 $ , because $ p_2 \cdot 3 = p_3 $ and $ p_5 \cdot 3 = p_6 $ .

Your task is the following one: for a given value $ n $ , find the permutation of length $ n $ and the value $ d $ with maximum possible cost (over all ways to choose the permutation and $ d $ ). If there are multiple answers, then print any of them.

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
2
1 2
3
2 1 3```

# AI分析结果

### 题目内容
# 排列

## 题目描述
回想一下，长度为 $n$ 的排列是一个数组，其中从 $1$ 到 $n$ 的每个元素恰好出现一次。

对于一个固定的正整数 $d$，我们将长度为 $n$ 的排列 $p$ 的代价定义为满足 $p_i \cdot d = p_{i + 1}$ 的索引 $i$ 的数量（$1 \le i < n$）。

例如，如果 $d = 3$ 且 $p = [5, 2, 6, 7, 1, 3, 4]$，那么这样一个排列的代价是 $2$，因为 $p_2 \cdot 3 = p_3$ 且 $p_5 \cdot 3 = p_6$。

你的任务如下：对于给定的 $n$ 值，找到长度为 $n$ 的排列和值 $d$，使得代价最大（在所有选择排列和 $d$ 的方式中）。如果有多个答案，则打印其中任何一个。

## 样例 #1
### 输入
```
2
2
3
```
### 输出
```
2
1 2
3
2 1 3
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过分析得出 $d = 2$ 时能使排列的代价最大，然后基于 $d = 2$ 来构造排列 $p$。不同题解在分析 $d = 2$ 的原因以及构造排列的具体方式描述上略有差异，但本质相同。在构造排列 $p$ 时，都是从某个数开始，以 $2$ 为公比生成等比数列，直到超过 $n$ 或者该数已在排列中出现过，再从下一个未使用的数开始构造。

### 通用建议与扩展思路
对于此类构造题，关键在于通过对问题的分析找到最优的构造策略。在分析过程中，可以从简单情况入手，逐步推导规律。扩展思路方面，类似题目可能会改变条件，比如改变代价的定义，或者对排列有其他限制条件，解题时需根据新条件重新分析最优构造方式。

### 推荐题目
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：通过枚举和构造来解决火柴棒拼等式的问题，锻炼构造能力。
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：涉及组合和构造，从给定数字中选择若干个数满足特定条件。
- [P1219 [USACO1.5]八皇后 Checker Challenge](https://www.luogu.com.cn/problem/P1219)：经典的八皇后问题，通过构造合法的摆放方案来解决，考察构造与搜索能力。 

---
处理用时：23.59秒