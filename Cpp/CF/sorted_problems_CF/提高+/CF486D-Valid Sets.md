---
title: "Valid Sets"
layout: "post"
diff: 提高+/省选-
pid: CF486D
tag: []
---

# Valid Sets

## 题目描述

As you know, an undirected connected graph with $ n $ nodes and $ n-1 $ edges is called a tree. You are given an integer $ d $ and a tree consisting of $ n $ nodes. Each node $ i $ has a value $ a_{i} $ associated with it.

We call a set $ S $ of tree nodes valid if following conditions are satisfied:

1. $ S $ is non-empty.
2. $ S $ is connected. In other words, if nodes $ u $ and $ v $ are in $ S $ , then all nodes lying on the simple path between $ u $ and $ v $ should also be presented in $ S $ .
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486D/178986cc3145e106df7e442d141768e61c090be6.png).

Your task is to count the number of valid sets. Since the result can be very large, you must print its remainder modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains two space-separated integers $d$ ($0 \le d \le 2000$) and $n$ ($1 \le n \le 2000$).

The second line contains $n$ space-separated positive integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 2000$).

Then the next $n - 1$ line each contain pair of integers $u$ and $v$ ($1 \le u, v \le n$) denoting that there is an edge between $u$ and $v$. It is guaranteed that these edges form a tree.

## 输出格式

Print the number of valid sets modulo $ 1000000007 $ .

## 说明/提示

In the first sample, there are exactly 8 valid sets: $ {1},{2},{3},{4},{1,2},{1,3},{3,4} $ and $ {1,3,4} $ . Set $ {1,2,3,4} $ is not valid, because the third condition isn't satisfied. Set $ {1,4} $ satisfies the third condition, but conflicts with the second condition.

## 样例 #1

### 输入

```
1 4
2 1 3 2
1 2
1 3
3 4

```

### 输出

```
8

```

## 样例 #2

### 输入

```
0 3
1 2 3
1 2
2 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
4 8
7 8 7 5 4 6 4 10
1 6
1 2
5 8
1 3
3 5
6 7
3 4

```

### 输出

```
41

```

