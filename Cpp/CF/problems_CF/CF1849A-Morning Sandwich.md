---
title: "Morning Sandwich"
layout: "post"
diff: 入门
pid: CF1849A
tag: []
---

# Morning Sandwich

## 题目描述

Monocarp always starts his morning with a good ol' sandwich. Sandwiches Monocarp makes always consist of bread, cheese and/or ham.

A sandwich always follows the formula:

- a piece of bread
- a slice of cheese or ham
- a piece of bread
- $ \dots $
- a slice of cheese or ham
- a piece of bread

So it always has bread on top and at the bottom, and it alternates between bread and filling, where filling is a slice of either cheese or ham. Each piece of bread and each slice of cheese or ham is called a layer.

Today Monocarp woke up and discovered that he has $ b $ pieces of bread, $ c $ slices of cheese and $ h $ slices of ham. What is the maximum number of layers his morning sandwich can have?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of testcases.

Each testcase consists of three integers $ b, c $ and $ h $ ( $ 2 \le b \le 100 $ ; $ 1 \le c, h \le 100 $ ) — the number of pieces of bread, slices of cheese and slices of ham, respectively.

## 输出格式

For each testcase, print a single integer — the maximum number of layers Monocarp's morning sandwich can have.

## 说明/提示

In the first testcase, Monocarp can arrange a sandwich with three layers: either a piece of bread, a slice of cheese and another piece of bread, or a piece of bread, a slice of ham and another piece of bread.

In the second testcase, Monocarp has a lot of bread, but not too much filling. He can arrange a sandwich with four pieces of bread, one slice of cheese and two slices of ham.

In the third testcase, it's the opposite — Monocarp has a lot of filling, but not too much bread. He can arrange a sandwich with three pieces of bread and two slices of cheese, for example.

## 样例 #1

### 输入

```
3
2 1 1
10 1 2
3 7 8
```

### 输出

```
3
7
5
```

