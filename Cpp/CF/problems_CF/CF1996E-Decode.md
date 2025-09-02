---
title: "Decode"
layout: "post"
diff: 普及/提高-
pid: CF1996E
tag: ['前缀和']
---

# Decode

## 题目描述

In a desperate attempt to obtain your waifu favorite character, you have hacked into the source code of the game. After days of struggling, you finally find the binary string that encodes the gacha system of the game. In order to decode it, you must first solve the following problem.

You are given a binary string $ s $ of length $ n $ . For each pair of integers $ (l, r) $ $ (1 \leq l \leq r \leq n) $ , count the number of pairs $ (x, y) $ $ (l \leq x \leq y \leq r) $ such that the amount of $ \mathtt{0} $ equals the amount of $ \mathtt{1} $ in the substring $ s_xs_{x+1}...s_y $ .

Output the sum of counts over all possible $ (l, r) $ modulo $ 10^9+7 $ .

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

Each test case contains a binary string $ s $ ( $ 1 \leq |s| \leq 2 \cdot 10^5 $ ). It is guaranteed $ s $ only contains characters $ \mathtt{0} $ and $ \mathtt{1} $ .

It is guaranteed the sum of $ |s| $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output an integer, the answer modulo $ 10^9+7 $ .

## 样例 #1

### 输入

```
4
0000
01010101
1100111001
11000000111
```

### 输出

```
0
130
147
70
```

