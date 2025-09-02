---
title: "Jeff and Periods"
layout: "post"
diff: 普及-
pid: CF352B
tag: []
---

# Jeff and Periods

## 题目描述

One day Jeff got hold of an integer sequence $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ of length $ n $ . The boy immediately decided to analyze the sequence. For that, he needs to find all values of $ x $ , for which these conditions hold:

- $ x $ occurs in sequence $ a $ .
- Consider all positions of numbers $ x $ in the sequence $ a $ (such $ i $ , that $ a_{i}=x $ ). These numbers, sorted in the increasing order, must form an arithmetic progression.

Help Jeff, find all $ x $ that meet the problem conditions.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ . The next line contains integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ $ (1<=a_{i}<=10^{5}) $ . The numbers are separated by spaces.

## 输出格式

In the first line print integer $ t $ — the number of valid $ x $ . On each of the next $ t $ lines print two integers $ x $ and $ p_{x} $ , where $ x $ is current suitable value, $ p_{x} $ is the common difference between numbers in the progression (if $ x $ occurs exactly once in the sequence, $ p_{x} $ must equal 0). Print the pairs in the order of increasing $ x $ .

## 说明/提示

In the first test $ 2 $ occurs exactly once in the sequence, ergo $ p_{2}=0 $ .

## 样例 #1

### 输入

```
1
2

```

### 输出

```
1
2 0

```

## 样例 #2

### 输入

```
8
1 2 1 3 1 2 1 5

```

### 输出

```
4
1 2
2 4
3 0
5 0

```

