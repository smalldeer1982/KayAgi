---
title: "TCMCF+++"
layout: "post"
diff: 普及/提高-
pid: CF45I
tag: []
---

# TCMCF+++

## 题目描述

Vasya has gotten interested in programming contests in TCMCF+++ rules. On the contest $ n $ problems were suggested and every problem had a cost — a certain integral number of points (perhaps, negative or even equal to zero). According to TCMCF+++ rules, only accepted problems can earn points and the overall number of points of a contestant was equal to the product of the costs of all the problems he/she had completed. If a person didn't solve anything, then he/she didn't even appear in final standings and wasn't considered as participant. Vasya understood that to get the maximal number of points it is not always useful to solve all the problems. Unfortunately, he understood it only after the contest was finished. Now he asks you to help him: find out what problems he had to solve to earn the maximal number of points.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ) — the number of the suggested problems. The next line contains $ n $ space-separated integers $ c_{i} $ ( $ -100<=c_{i}<=100 $ ) — the cost of the $ i $ -th task. The tasks' costs may coinсide.

## 输出格式

Print space-separated the costs of the problems that needed to be solved to get the maximal possible number of points. Do not forget, please, that it was necessary to solve at least one problem. If there are several solutions to that problem, print any of them.

## 样例 #1

### 输入

```
5
1 2 -3 3 3

```

### 输出

```
3 1 2 3 

```

## 样例 #2

### 输入

```
13
100 100 100 100 100 100 100 100 100 100 100 100 100

```

### 输出

```
100 100 100 100 100 100 100 100 100 100 100 100 100 

```

## 样例 #3

### 输入

```
4
-2 -2 -2 -2

```

### 输出

```
-2 -2 -2 -2 

```

