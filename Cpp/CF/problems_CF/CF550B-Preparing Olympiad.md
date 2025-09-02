---
title: "Preparing Olympiad"
layout: "post"
diff: 普及/提高-
pid: CF550B
tag: []
---

# Preparing Olympiad

## 题目描述

You have $ n $ problems. You have estimated the difficulty of the $ i $ -th one as integer $ c_{i} $ . Now you want to prepare a problemset for a contest, using some of the problems you've made.

A problemset for the contest must consist of at least two problems. You think that the total difficulty of the problems of the contest must be at least $ l $ and at most $ r $ . Also, you think that the difference between difficulties of the easiest and the hardest of the chosen problems must be at least $ x $ .

Find the number of ways to choose a problemset for the contest.

## 输入格式

The first line contains four integers $ n $ , $ l $ , $ r $ , $ x $ ( $ 1<=n<=15 $ , $ 1<=l<=r<=10^{9} $ , $ 1<=x<=10^{6} $ ) — the number of problems you have, the minimum and maximum value of total difficulty of the problemset and the minimum difference in difficulty between the hardest problem in the pack and the easiest one, respectively.

The second line contains $ n $ integers $ c_{1},c_{2},...,c_{n} $ ( $ 1<=c_{i}<=10^{6} $ ) — the difficulty of each problem.

## 输出格式

Print the number of ways to choose a suitable problemset for the contest.

## 说明/提示

In the first example two sets are suitable, one consisting of the second and third problem, another one consisting of all three problems.

In the second example, two sets of problems are suitable — the set of problems with difficulties 10 and 30 as well as the set of problems with difficulties 20 and 30.

In the third example any set consisting of one problem of difficulty 10 and one problem of difficulty 20 is suitable.

## 样例 #1

### 输入

```
3 5 6 1
1 2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 40 50 10
10 20 30 25

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5 25 35 10
10 10 20 10 20

```

### 输出

```
6

```

