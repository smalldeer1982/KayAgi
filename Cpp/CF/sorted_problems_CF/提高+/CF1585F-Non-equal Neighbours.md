---
title: "Non-equal Neighbours"
layout: "post"
diff: 提高+/省选-
pid: CF1585F
tag: ['动态规划 DP', '单调队列', '容斥原理']
---

# Non-equal Neighbours

## 题目描述

You are given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ . Your task is to calculate the number of arrays of $ n $ positive integers $ b_1, b_2, \ldots, b_n $ such that:

- $ 1 \le b_i \le a_i $ for every $ i $ ( $ 1 \le i \le n $ ), and
- $ b_i \neq b_{i+1} $ for every $ i $ ( $ 1 \le i \le n - 1 $ ).

The number of such arrays can be very large, so print it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

Print the answer modulo $ 998\,244\,353 $ in a single line.

## 说明/提示

In the first test case possible arrays are $ [1, 2, 1] $ and $ [2, 1, 2] $ .

In the second test case possible arrays are $ [1, 2] $ , $ [1, 3] $ , $ [2, 1] $ and $ [2, 3] $ .

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
2 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
0
```

