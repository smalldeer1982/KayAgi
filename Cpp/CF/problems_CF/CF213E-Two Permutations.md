---
title: "Two Permutations"
layout: "post"
diff: 省选/NOI-
pid: CF213E
tag: ['线段树', '平衡树', '枚举', '哈希 hashing']
---

# Two Permutations

## 题目描述

Rubik is very keen on number permutations.

A permutation $ a $ with length $ n $ is a sequence, consisting of $ n $ different numbers from 1 to $ n $ . Element number $ i $ $ (1<=i<=n) $ of this permutation will be denoted as $ a_{i} $ .

Furik decided to make a present to Rubik and came up with a new problem on permutations. Furik tells Rubik two number permutations: permutation $ a $ with length $ n $ and permutation $ b $ with length $ m $ . Rubik must give an answer to the problem: how many distinct integers $ d $ exist, such that sequence $ c $ $ (c_{1}=a_{1}+d,c_{2}=a_{2}+d,...,c_{n}=a_{n}+d) $ of length $ n $ is a subsequence of $ b $ .

Sequence $ a $ is a subsequence of sequence $ b $ , if there are such indices $ i_{1},i_{2},...,i_{n} $ $ (1<=i_{1}&lt;i_{2}&lt;...&lt;i_{n}<=m) $ , that $ a_{1}=b_{i1} $ , $ a_{2}=b_{i2} $ , $ ... $ , $ a_{n}=b_{in} $ , where $ n $ is the length of sequence $ a $ , and $ m $ is the length of sequence $ b $ .

You are given permutations $ a $ and $ b $ , help Rubik solve the given problem.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=m<=200000) $ — the sizes of the given permutations. The second line contains $ n $ distinct integers — permutation $ a $ , the third line contains $ m $ distinct integers — permutation $ b $ . Numbers on the lines are separated by spaces.

## 输出格式

On a single line print the answer to the problem.

## 样例 #1

### 输入

```
1 1
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1 2
1
2 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 3
2 3 1
1 2 3

```

### 输出

```
0

```

