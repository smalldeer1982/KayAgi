---
title: "To Become Max"
layout: "post"
diff: 普及+/提高
pid: CF1856C
tag: []
---

# To Become Max

## 题目描述

You are given an array of integers $ a $ of length $ n $ .

In one operation you:

- Choose an index $ i $ such that $ 1 \le i \le n - 1 $ and $ a_i \le a_{i + 1} $ .
- Increase $ a_i $ by $ 1 $ .

Find the maximum possible value of $ \max(a_1, a_2, \ldots a_n) $ that you can get after performing this operation at most $ k $ times.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 2 \le n \le 1000 $ , $ 1 \le k \le 10^{8} $ ) — the length of the array $ a $ and the maximum number of operations that can be performed.

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le 10^{8} $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case output a single integer — the maximum possible maximum of the array after performing at most $ k $ operations.

## 说明/提示

In the first test case, one possible optimal sequence of operations is: $[\textcolor{red}{1}, 3, 3] \rightarrow [2, \textcolor{red}{3}, 3] \rightarrow [\textcolor{red}{2}, 4, 3] \rightarrow [\textcolor{red}{3}, 4, 3] \rightarrow [4, 4, 3]$.

In the second test case, one possible optimal sequence of operations is: $[1, \textcolor{red}{3}, 4, 5, 1] \rightarrow [1, \textcolor{red}{4}, 4, 5, 1] \rightarrow [1, 5, \textcolor{red}{4}, 5, 1] \rightarrow [1, 5, \textcolor{red}{5}, 5, 1] \rightarrow [1, \textcolor{red}{5}, 6, 5, 1] \rightarrow [1, \textcolor{red}{6}, 6, 5, 1] \rightarrow [1, 7, 6, 5, 1]$.

## 样例 #1

### 输入

```
6
3 4
1 3 3
5 6
1 3 4 5 1
4 13
1 1 3 179
5 3
4 3 2 2 2
5 6
6 5 4 1 5
2 17
3 5
```

### 输出

```
4
7
179
5
7
6
```

