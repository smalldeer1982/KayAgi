---
title: "Prefiquence"
layout: "post"
diff: 普及-
pid: CF1968B
tag: ['双指针 two-pointer']
---

# Prefiquence

## 题目描述

You are given two binary strings $ a $ and $ b $ . A binary string is a string consisting of the characters '0' and '1'.

Your task is to determine the maximum possible number $ k $ such that a prefix of string $ a $ of length $ k $ is a subsequence of string $ b $ .

A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements.

## 输入格式

The first line consists of a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1\le n,m \le 2 \cdot 10^5 $ ) — the length of string $ a $ and the length of string $ b $ , respectively.

The second line of each test case contains a binary string $ a $ of length $ n $ .

The third line of each test case contains a binary string $ b $ of length $ m $ .

It is guaranteed that the sum of values $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Similarly, the sum of values $ m $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the maximum $ k $ , such that the first $ k $ characters of $ a $ form a subsequence of $ b $ .

## 说明/提示

In the first example, the string ' $ 10 $ ' is a subsequence of ' $ 1\color{red}11\color{red}0 $ ' but the string ' $ 100 $ ' is not. So the answer is $ 2 $ .

In the fifth example, $ a $ =' $ 100 $ ', $ b $ =' $ 1\color{red}{10}1\color{red}0 $ ', whole string $ a $ is a subsequence of string $ b $ . So the answer is $ 3 $ .

In the sixth example, string $ b $ does not contain ' $ 1 $ ' so the answer is $ 0 $ .

## 样例 #1

### 输入

```
6
5 4
10011
1110
3 3
100
110
1 3
1
111
4 4
1011
1111
3 5
100
11010
3 1
100
0
```

### 输出

```
2
2
1
1
3
0
```

