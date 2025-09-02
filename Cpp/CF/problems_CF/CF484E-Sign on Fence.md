---
title: "Sign on Fence"
layout: "post"
diff: 省选/NOI-
pid: CF484E
tag: []
---

# Sign on Fence

## 题目描述

Bizon the Champion has recently finished painting his wood fence. The fence consists of a sequence of $ n $ panels of $ 1 $ meter width and of arbitrary height. The $ i $ -th panel's height is $ h_{i} $ meters. The adjacent planks follow without a gap between them.

After Bizon painted the fence he decided to put a "for sale" sign on it. The sign will be drawn on a rectangular piece of paper and placed on the fence so that the sides of the sign are parallel to the fence panels and are also aligned with the edges of some panels. Bizon the Champion introduced the following constraints for the sign position:

1. The width of the sign should be exactly $ w $ meters.
2. The sign must fit into the segment of the fence from the $ l $ -th to the $ r $ -th panels, inclusive (also, it can't exceed the fence's bound in vertical direction).

The sign will be really pretty, So Bizon the Champion wants the sign's height to be as large as possible.

You are given the description of the fence and several queries for placing sign. For each query print the maximum possible height of the sign that can be placed on the corresponding segment of the fence with the given fixed width of the sign.


## 输入格式

The first line of the input contains integer $n$~--- the number of panels in the fence ($1 \leq n \leq 10^{5}$). 

The second line contains $n$ space-separated integers $h_{i}$, --- the heights of the panels ($1 \leq h_{i} \leq 10^{9}$). 

The third line contains an integer $m$ --- the number of the queries ($1 \leq m \leq 10^{5}$). 

The next $m$ lines contain the descriptions of the queries, each query is represented by three integers $l$, $r$ and $w$ ($1 \leq l \leq r \leq n$, $1 \leq w \leq r-l+1$) --- the segment of the fence and the width of the sign respectively.


## 输出格式

For each query print the answer on a separate line — the maximum height of the sign that can be put in the corresponding segment of the fence with all the conditions being satisfied.

## 说明/提示

The fence described in the sample looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484E/6257a310d2207c0e1a05992058b31d44d0ead77b.png)The possible positions for the signs for all queries are given below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484E/4bfca5e8ee81f8d76187af1e0be6e7c7b6bf35e2.png) The optimal position of the sign for the first query.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484E/f28ed7253a1a74cdc9e367c2f43ac177854f54b6.png) The optimal position of the sign for the second query.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484E/5dde0308a1ff26588bc67b02973df5bc0c317178.png) The optimal position of the sign for the third query.

## 样例 #1

### 输入

```
5
1 2 2 3 3
3
2 5 3
2 5 2
1 5 5

```

### 输出

```
2
3
1

```

