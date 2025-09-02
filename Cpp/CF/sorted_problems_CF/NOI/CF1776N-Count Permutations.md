---
title: "Count Permutations"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1776N
tag: ['杨表']
---

# Count Permutations

## 题目描述

You are given a string $ s $ with length $ n-1 $ whose characters are either $ \texttt{<} $ or $ \texttt{>} $ .

Count the permutations $ p_1, \, p_2, \, \dots, \, p_n $ of $ 1, \, 2, \, \dots, \, n $ such that, for all $ i = 1, \, 2, \, \dots, \, n - 1 $ , if $ s_i $ is $ \texttt{<} $ then $ p_i < p_{i+1} $ and if $ s_i $ is $ \texttt{>} $ then $ p_i > p_{i+1} $ .

Since this number can be very large, compute its logarithm in base $ 2 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 100\,000 $ ).

The second line contains a string $ s $ of length $ n-1 $ ; each character of $ s $ is either $ \texttt{<} $ or $ \texttt{>} $ .

## 输出格式

Print the logarithm in base $ 2 $ of the number of permutations satisfying the constraints described in the statement.

Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-6} $ . Formally, let your answer be $ x $ and let the correct answer be $ y $ . Your answer is accepted if and only if $ \frac{|x - y|}{\max{(1, |y|)}} \le 10^{-6} $ .

## 说明/提示

In the first sample, there is only one valid permutation, that is $ [2, 1] $ . Since $ \log_2(1)=0 $ , the correct output is $ 0 $ .

In the second sample, there are $ 2 $ valid permutations, that are $ [3, 1, 2] $ and $ [2, 1, 3] $ . Since $ \log_2(2)=1 $ , the correct output is $ 1 $ .

In the third sample, there are $ 4 $ valid permutations, that are $ [1, 5, 4, 3, 2] $ , $ [2, 5, 4, 3, 1] $ , $ [3, 5, 4, 2, 1] $ , $ [4, 5, 3, 2, 1] $ . Since $ \log_2(4)=2 $ , the correct output is $ 2 $ .

In the fourth sample, there are $ 909 $ valid permutations. Notice that $ \log_2(909)=9.828136484194\ldots $

## 样例 #1

### 输入

```
2
<
```

### 输出

```
0.0000000000
```

## 样例 #2

### 输入

```
3
<>

```

### 输出

```
1.0000000000
```

## 样例 #3

### 输入

```
5
><<<

```

### 输出

```
2.0000000000
```

## 样例 #4

### 输入

```
10
<><<<<<>>

```

### 输出

```
9.8281364842
```

