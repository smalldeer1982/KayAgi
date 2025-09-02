# 题目信息

# Building Permutation

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

You have a sequence of integers $ a_{1},a_{2},...,a_{n} $ . In one move, you are allowed to decrease or increase any number by one. Count the minimum number of moves, needed to build a permutation from this sequence.

## 说明/提示

In the first sample you should decrease the first number by one and then increase the second number by one. The resulting permutation is $ (2,1) $ .

In the second sample you need 6 moves to build permutation $ (1,3,2) $ .

## 样例 #1

### 输入

```
2
3 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
-1 -1 2
```

### 输出

```
6
```

# AI分析结果

### 题目内容
# 构建排列

## 题目描述
排列 $p$ 是一个有序整数集合 $p_1, p_2, \ldots, p_n$，由 $n$ 个不同的正整数组成，每个数都不超过 $n$。我们将排列 $p$ 的第 $i$ 个元素记为 $p_i$。我们称数字 $n$ 为排列 $p_1, p_2, \ldots, p_n$ 的大小或长度。

你有一个整数序列 $a_1, a_2, \ldots, a_n$。在一次移动中，你可以将任何一个数增加或减少 $1$。计算从这个序列构建一个排列所需的最少移动次数。

## 说明/提示
在第一个样例中，你应该将第一个数减 $1$，然后将第二个数加 $1$。得到的排列是 $(2, 1)$。

在第二个样例中，你需要 $6$ 次移动来构建排列 $(1, 3, 2)$。

## 样例 #1
### 输入
```
2
3 0
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3
-1 -1 2
```
### 输出
```
6
```

### 算法分类
贪心

### 综合分析与结论
这些题解思路基本一致，均采用贪心策略。要点在于先对原数列排序，之后计算排序后数列中每个数与对应下标（从1开始）差值的绝对值之和，即 $\sum\limits_{i=1}^n{\lvert a_i - i\rvert}$，此和即为最少移动次数。由于数据范围较大，答案变量需用 `long long` 类型。所有题解都实现了基本功能，但在思路清晰度和代码可读性上略有差异。

### 通用建议与扩展思路
对于此类贪心问题，关键在于找到一个合理的贪心策略，本题通过排序让每个数与目标位置的差值最小。类似套路可应用于其他需要通过操作使序列达到特定目标状态且求最少操作次数的题目。同类型题可考虑对序列进行其他限定条件下的变换，如变换后序列需满足特定顺序或和值要求等。

### 洛谷题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123) 

---
处理用时：22.70秒