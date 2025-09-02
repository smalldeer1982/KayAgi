---
title: "Ladder"
layout: "post"
diff: 普及+/提高
pid: CF279C
tag: []
---

# Ladder

## 题目描述

You've got an array, consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Also, you've got $ m $ queries, the $ i $ -th query is described by two integers $ l_{i},r_{i} $ . Numbers $ l_{i},r_{i} $ define a subsegment of the original array, that is, the sequence of numbers $ a_{li},a_{li}+1,a_{li}+2,...,a_{ri} $ . For each query you should check whether the corresponding segment is a ladder.

A ladder is a sequence of integers $ b_{1},b_{2},...,b_{k} $ , such that it first doesn't decrease, then doesn't increase. In other words, there is such integer $ x $ $ (1<=x<=k) $ , that the following inequation fulfills: $ b_{1}<=b_{2}<=...<=b_{x}>=b_{x+1}>=b_{x+2}...>=b_{k} $ . Note that the non-decreasing and the non-increasing sequences are also considered ladders.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n,m<=10^{5}) $ — the number of array elements and the number of queries. The second line contains the sequence of integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9} $ ), where number $ a_{i} $ stands for the $ i $ -th array element.

The following $ m $ lines contain the description of the queries. The $ i $ -th line contains the description of the $ i $ -th query, consisting of two integers $ l_{i} $ , $ r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ — the boundaries of the subsegment of the initial array.

The numbers in the lines are separated by single spaces.

## 输出格式

Print $ m $ lines, in the $ i $ -th line print word "Yes" (without the quotes), if the subsegment that corresponds to the $ i $ -th query is the ladder, or word "No" (without the quotes) otherwise.

## 样例 #1

### 输入

```
8 6
1 2 1 3 3 5 2 1
1 3
2 3
2 4
8 8
1 4
5 8

```

### 输出

```
Yes
Yes
No
Yes
No
Yes

```

