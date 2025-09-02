---
title: "String"
layout: "post"
diff: 入门
pid: CF2062A
tag: []
---

# String

## 题目描述

You are given a string $ s $ of length $ n $ consisting of $ \mathtt{0} $ and/or $ \mathtt{1} $ . In one operation, you can select a non-empty subsequence $ t $ from $ s $ such that any two adjacent characters in $ t $ are different. Then, you flip each character of $ t $ ( $ \mathtt{0} $ becomes $ \mathtt{1} $ and $ \mathtt{1} $ becomes $ \mathtt{0} $ ). For example, if $ s=\mathtt{\underline{0}0\underline{101}} $ and $ t=s_1s_3s_4s_5=\mathtt{0101} $ , after the operation, $ s $ becomes $ \mathtt{\underline{1}0\underline{010}} $ .

Calculate the minimum number of operations required to change all characters in $ s $ to $ \mathtt{0} $ .

Recall that for a string $ s = s_1s_2\ldots s_n $ , any string $ t=s_{i_1}s_{i_2}\ldots s_{i_k} $ ( $ k\ge 1 $ ) where $ 1\leq i_1 < i_2 < \ldots <i_k\leq n $ is a subsequence of $ s $ .

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of input test cases.

The only line of each test case contains the string $ s $ ( $ 1\le |s|\le 50 $ ), where $ |s| $ represents the length of $ s $ .

## 输出格式

For each test case, output the minimum number of operations required to change all characters in $ s $ to $ \mathtt{0} $ .

## 说明/提示

In the first test case, you can flip $ s_1 $ . Then $ s $ becomes $ \mathtt{0} $ , so the answer is $ 1 $ .

In the fourth test case, you can perform the following three operations in order:

1. Flip $ s_1s_2s_3s_4s_5 $ . Then $ s $ becomes $ \mathtt{\underline{01010}} $ .
2. Flip $ s_2s_3s_4 $ . Then $ s $ becomes $ \mathtt{0\underline{010}0} $ .
3. Flip $ s_3 $ . Then $ s $ becomes $ \mathtt{00\underline{0}00} $ .

It can be shown that you can not change all characters in $ s $ to $ \mathtt{0} $ in less than three operations, so the answer is $ 3 $ .

## 样例 #1

### 输入

```
5
1
000
1001
10101
01100101011101
```

### 输出

```
1
0
2
3
8
```

