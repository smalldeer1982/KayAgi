---
title: "Circle Perimeter"
layout: "post"
diff: 普及/提高-
pid: CF1971F
tag: ['数学']
---

# Circle Perimeter

## 题目描述

Given an integer $ r $ , find the number of lattice points that have a Euclidean distance from $ (0, 0) $ greater than or equal to $ r $ but strictly less than $ r+1 $ .

A lattice point is a point with integer coordinates. The Euclidean distance from $ (0, 0) $ to the point $ (x,y) $ is $ \sqrt{x^2 + y^2} $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The only line of each test case contains a single integer $ r $ ( $ 1 \leq r \leq 10^5 $ ).

The sum of $ r $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of lattice points that have an Euclidean distance $ d $ from $ (0, 0) $ such that $ r \leq d < r+1 $ .

## 说明/提示

The points for the first three test cases are shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971F/aff456cddb623f0decb8386de3943888d72800f7.png)

## 样例 #1

### 输入

```
6
1
2
3
4
5
1984
```

### 输出

```
8
16
20
24
40
12504
```

