---
title: "Maximal AND"
layout: "post"
diff: 普及-
pid: CF1669H
tag: []
---

# Maximal AND

## 题目描述

Let $ \mathsf{AND} $ denote the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), and $ \mathsf{OR} $ denote the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

You are given an array $ a $ of length $ n $ and a non-negative integer $ k $ . You can perform at most $ k $ operations on the array of the following type:

- Select an index $ i $ ( $ 1 \leq i \leq n $ ) and replace $ a_i $ with $ a_i $ $ \mathsf{OR} $ $ 2^j $ where $ j $ is any integer between $ 0 $ and $ 30 $ inclusive. In other words, in an operation you can choose an index $ i $ ( $ 1 \leq i \leq n $ ) and set the $ j $ -th bit of $ a_i $ to $ 1 $ ( $ 0 \leq j \leq 30 $ ).

Output the maximum possible value of $ a_1 $ $ \mathsf{AND} $ $ a_2 $ $ \mathsf{AND} $ $ \dots $ $ \mathsf{AND} $ $ a_n $ after performing at most $ k $ operations.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains the integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le k \le 10^9 $ ).

Then a single line follows, containing $ n $ integers describing the arrays $ a $ ( $ 0 \leq a_i < 2^{31} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single line containing the maximum possible $ \mathsf{AND} $ value of $ a_1 $ $ \mathsf{AND} $ $ a_2 $ $ \mathsf{AND} $ $ \dots $ $ \mathsf{AND} $ $ a_n $ after performing at most $ k $ operations.

## 说明/提示

For the first test case, we can set the bit $ 1 $ ( $ 2^1 $ ) of the last $ 2 $ elements using the $ 2 $ operations, thus obtaining the array \[ $ 2 $ , $ 3 $ , $ 3 $ \], which has $ \mathsf{AND} $ value equal to $ 2 $ .

For the second test case, we can't perform any operations so the answer is just the $ \mathsf{AND} $ of the whole array which is $ 4 $ .

## 样例 #1

### 输入

```
4
3 2
2 1 1
7 0
4 6 6 28 6 6 12
1 30
0
4 4
3 1 3 1
```

### 输出

```
2
4
2147483646
1073741825
```

