---
title: "LKS - Large Knapsack"
layout: "post"
diff: 普及-
pid: SP15259
tag: []
---

# LKS - Large Knapsack

## 题目描述

The **[knapsack problem](https://en.wikipedia.org/wiki/Knapsack_problem)** or **rucksack problem** is a problem in <a>combinatorial optimization</a>: Given a set of items, each with a weight and a value, determine the number of each item to include in a collection so that the total weight is less than or equal to a given limit and the total value is as large as possible. It derives its name from the problem faced by someone who is constrained by a fixed-size <a>knapsack</a> and must fill it with the most valuable items.

Just implement 0/1 Knapsack.

## 输入格式

First line contains two integers K and N, where K in the maximum knapsack size and N is the number of items. N lines follow where i $ ^{th} $ line describes i $ ^{th} $ item in the form v $ _{i} $ and w $ _{i} $ where v $ _{i} $ is the value and w $ _{i} $ is the weight of i $ ^{th} $ item.

## 输出格式

Output a single number - maximum value of knapsack. (All operations and the answer are guaranteed to fit in signed 32-bit integer.)

_Time limit changed to 2s on 02.07.11._

## 样例 #1

### 输入

```
10 3
7 3
8 8
4 6
```

### 输出

```
11
```

