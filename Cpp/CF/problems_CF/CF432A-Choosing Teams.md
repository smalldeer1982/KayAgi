---
title: "Choosing Teams"
layout: "post"
diff: 入门
pid: CF432A
tag: []
---

# Choosing Teams

## 题目描述

The Saratov State University Olympiad Programmers Training Center (SSU OPTC) has $ n $ students. For each student you know the number of times he/she has participated in the ACM ICPC world programming championship. According to the ACM ICPC rules, each person can participate in the world championship at most 5 times.

The head of the SSU OPTC is recently gathering teams to participate in the world championship. Each team must consist of exactly three people, at that, any person cannot be a member of two or more teams. What maximum number of teams can the head make if he wants each team to participate in the world championship with the same members at least $ k $ times?

## 输入格式

The first line contains two integers, $ n $ and $ k $ $ (1<=n<=2000; 1<=k<=5) $ . The next line contains $ n $ integers: $ y_{1},y_{2},...,y_{n} $ $ (0<=y_{i}<=5) $ , where $ y_{i} $ shows the number of times the $ i $ -th person participated in the ACM ICPC world championship.

## 输出格式

Print a single number — the answer to the problem.

## 说明/提示

In the first sample only one team could be made: the first, the fourth and the fifth participants.

In the second sample no teams could be created.

In the third sample two teams could be created. Any partition into two teams fits.

## 样例 #1

### 输入

```
5 2
0 4 5 1 0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
6 4
0 1 2 3 4 5

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6 5
0 0 0 0 0 0

```

### 输出

```
2

```

