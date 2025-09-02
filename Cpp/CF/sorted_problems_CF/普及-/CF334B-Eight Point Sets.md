---
title: "Eight Point Sets"
layout: "post"
diff: 普及-
pid: CF334B
tag: []
---

# Eight Point Sets

## 题目描述

Gerald is very particular to eight point sets. He thinks that any decent eight point set must consist of all pairwise intersections of three distinct integer vertical straight lines and three distinct integer horizontal straight lines, except for the average of these nine points. In other words, there must be three integers $ x_{1},x_{2},x_{3} $ and three more integers $ y_{1},y_{2},y_{3} $ , such that $ x_{1}&lt;x_{2}&lt;x_{3} $ , $ y_{1}&lt;y_{2}&lt;y_{3} $ and the eight point set consists of all points $ (x_{i},y_{j}) $ ( $ 1<=i,j<=3 $ ), except for point $ (x_{2},y_{2}) $ .

You have a set of eight points. Find out if Gerald can use this set?

## 输入格式

The input consists of eight lines, the $ i $ -th line contains two space-separated integers $ x_{i} $ and $ y_{i} $ ( $ 0<=x_{i},y_{i}<=10^{6} $ ). You do not have any other conditions for these points.

## 输出格式

In a single line print word "respectable", if the given set of points corresponds to Gerald's decency rules, and "ugly" otherwise.

## 样例 #1

### 输入

```
0 0
0 1
0 2
1 0
1 2
2 0
2 1
2 2

```

### 输出

```
respectable

```

## 样例 #2

### 输入

```
0 0
1 0
2 0
3 0
4 0
5 0
6 0
7 0

```

### 输出

```
ugly

```

## 样例 #3

### 输入

```
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2

```

### 输出

```
ugly

```

