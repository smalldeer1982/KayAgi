---
title: "Bear and Prime Numbers"
layout: "post"
diff: 普及+/提高
pid: CF385C
tag: []
---

# Bear and Prime Numbers

## 题目描述

Recently, the bear started studying data structures and faced the following problem.

You are given a sequence of integers $ x_{1},x_{2},...,x_{n} $ of length $ n $ and $ m $ queries, each of them is characterized by two integers $ l_{i},r_{i} $ . Let's introduce $ f(p) $ to represent the number of such indexes $ k $ , that $ x_{k} $ is divisible by $ p $ . The answer to the query $ l_{i},r_{i} $ is the sum: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF385C/835eb9f4aebf62a9178a923ec511d1ceb493d06f.png), where $ S(l_{i},r_{i}) $ is a set of prime numbers from segment $ [l_{i},r_{i}] $ (both borders are included in the segment).

Help the bear cope with the problem.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{6}) $ . The second line contains $ n $ integers $ x_{1},x_{2},...,x_{n} $ $ (2<=x_{i}<=10^{7}) $ . The numbers are not necessarily distinct.

The third line contains integer $ m $ $ (1<=m<=50000) $ . Each of the following $ m $ lines contains a pair of space-separated integers, $ l_{i} $ and $ r_{i} $ $ (2<=l_{i}<=r_{i}<=2·10^{9}) $ — the numbers that characterize the current query.

## 输出格式

Print $ m $ integers — the answers to the queries on the order the queries appear in the input.

## 说明/提示

Consider the first sample. Overall, the first sample has 3 queries.

1. The first query $ l=2 $ , $ r=11 $ comes. You need to count $ f(2)+f(3)+f(5)+f(7)+f(11)=2+1+4+2+0=9 $ .
2. The second query comes $ l=3 $ , $ r=12 $ . You need to count $ f(3)+f(5)+f(7)+f(11)=1+4+2+0=7 $ .
3. The third query comes $ l=4 $ , $ r=4 $ . As this interval has no prime numbers, then the sum equals 0.

## 样例 #1

### 输入

```
6
5 5 7 10 14 15
3
2 11
3 12
4 4

```

### 输出

```
9
7
0

```

## 样例 #2

### 输入

```
7
2 3 5 7 11 4 8
2
8 10
2 123

```

### 输出

```
0
7

```

