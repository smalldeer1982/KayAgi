---
title: "STONE2 - A Famous Stone Collector"
layout: "post"
diff: 难度0
pid: SP11574
tag: []
---

# STONE2 - A Famous Stone Collector

## 题目描述

Mr. B loves to play with colorful stones. There are n colors of stones in his collection. Two stones with the same color are indistinguishable. Mr. B would like to select some stones and arrange them in line to form a beautiful pattern. After several arrangements he finds that it's very hard for him to enumerate all the patterns. So he asks you to write a program to count the number of different patterns.

Two patterns are considered different, if and only if they have different number of stones or have different colors on at least one position.

## 输入格式

Each test case starts with a line containing an integer n indicating the kinds of stones Mr. B have. Following this is a line containing n integers - the number of available stones of each color respectively. All the input numbers will be nonnegative and no more than 100.

## 输出格式

For each test case, display a single line containing the case number and the number of different patterns Mr. B can make with these stones, modulo 1,000,000,007, which is a prime number.

## 样例 #1

### 输入

```
3
1 1 1
2
1 2
```

### 输出

```
Case 1: 15
Case 2: 8
```

