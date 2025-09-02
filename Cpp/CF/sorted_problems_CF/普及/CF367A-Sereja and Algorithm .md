---
title: "Sereja and Algorithm "
layout: "post"
diff: 普及/提高-
pid: CF367A
tag: []
---

# Sereja and Algorithm 

## 题目描述

Sereja loves all sorts of algorithms. He has recently come up with a new algorithm, which receives a string as an input. Let's represent the input string of the algorithm as $ q=q_{1}q_{2}...\ q_{k} $ . The algorithm consists of two steps:

1. Find any continuous subsequence (substring) of three characters of string $ q $ , which doesn't equal to either string "zyx", "xzy", "yxz". If $ q $ doesn't contain any such subsequence, terminate the algorithm, otherwise go to step 2.
2. Rearrange the letters of the found subsequence randomly and go to step 1.

Sereja thinks that the algorithm works correctly on string $ q $ if there is a non-zero probability that the algorithm will be terminated. But if the algorithm anyway will work for infinitely long on a string, then we consider the algorithm to work incorrectly on this string.

Sereja wants to test his algorithm. For that, he has string $ s=s_{1}s_{2}...\ s_{n} $ , consisting of $ n $ characters. The boy conducts a series of $ m $ tests. As the $ i $ -th test, he sends substring $ s_{li}s_{li}+1...\ s_{ri} $ $ (1<=l_{i}<=r_{i}<=n) $ to the algorithm input. Unfortunately, the implementation of his algorithm works too long, so Sereja asked you to help. For each test $ (l_{i},r_{i}) $ determine if the algorithm works correctly on this test or not.

## 输入格式

The first line contains non-empty string $ s $ , its length ( $ n $ ) doesn't exceed $ 10^{5} $ . It is guaranteed that string $ s $ only contains characters: 'x', 'y', 'z'.

The second line contains integer $ m $ $ (1<=m<=10^{5}) $ — the number of tests. Next $ m $ lines contain the tests. The $ i $ -th line contains a pair of integers $ l_{i} $ , $ r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ .

## 输出格式

For each test, print "YES" (without the quotes) if the algorithm works correctly on the corresponding test and "NO" (without the quotes) otherwise.

## 说明/提示

In the first example, in test one and two the algorithm will always be terminated in one step. In the fourth test you can get string "xzyx" on which the algorithm will terminate. In all other tests the algorithm doesn't work correctly.

## 样例 #1

### 输入

```
zyxxxxxxyyz
5
5 5
1 3
1 11
1 4
3 6

```

### 输出

```
YES
YES
NO
YES
NO

```

