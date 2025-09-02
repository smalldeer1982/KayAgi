---
title: "Perfect Triples"
layout: "post"
diff: 提高+/省选-
pid: CF1338C
tag: []
---

# Perfect Triples

## 题目描述

Consider the infinite sequence $ s $ of positive integers, created by repeating the following steps:

1. Find the lexicographically smallest triple of positive integers $ (a, b, c) $ such that 
  - $ a \oplus b \oplus c = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).
  - $ a $ , $ b $ , $ c $ are not in $ s $ .
  
   Here triple of integers $ (a_1, b_1, c_1) $ is considered to be lexicographically smaller than triple $ (a_2, b_2, c_2) $ if sequence $ [a_1, b_1, c_1] $ is lexicographically smaller than sequence $ [a_2, b_2, c_2] $ .
2. Append $ a $ , $ b $ , $ c $ to $ s $ in this order.
3. Go back to the first step.

You have integer $ n $ . Find the $ n $ -th element of $ s $ .

You have to answer $ t $ independent test cases.

A sequence $ a $ is lexicographically smaller than a sequence $ b $ if in the first position where $ a $ and $ b $ differ, the sequence $ a $ has a smaller element than the corresponding element in $ b $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases.

Each of the next $ t $ lines contains a single integer $ n $ ( $ 1\le n \le 10^{16} $ ) — the position of the element you want to know.

## 输出格式

In each of the $ t $ lines, output the answer to the corresponding test case.

## 说明/提示

The first elements of $ s $ are $ 1, 2, 3, 4, 8, 12, 5, 10, 15, \dots  $

## 样例 #1

### 输入

```
9
1
2
3
4
5
6
7
8
9
```

### 输出

```
1
2
3
4
8
12
5
10
15
```

