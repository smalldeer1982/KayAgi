---
title: "Path Counting"
layout: "post"
diff: 省选/NOI-
pid: CF954H
tag: []
---

# Path Counting

## 题目描述

You are given a rooted tree. Let's denote $ d(x) $ as depth of node $ x $ : depth of the root is $ 1 $ , depth of any other node $ x $ is $ d(y)+1 $ , where $ y $ is a parent of $ x $ .

The tree has the following property: every node $ x $ with $ d(x)=i $ has exactly $ a_{i} $ children. Maximum possible depth of a node is $ n $ , and $ a_{n}=0 $ .

We define $ f_{k} $ as the number of unordered pairs of vertices in the tree such that the number of edges on the simple path between them is equal to $ k $ .

Calculate $ f_{k} $ modulo $ 10^{9}+7 $ for every $ 1<=k<=2n-2 $ .

## 输入格式

The first line of input contains an integer $ n $ ( $ 2<=n<=5000 $ ) — the maximum depth of a node.

The second line of input contains $ n-1 $ integers $ a_{1},a_{2},...,a_{n-1} $ ( $ 2<=a_{i}<=10^{9} $ ), where $ a_{i} $ is the number of children of every node $ x $ such that $ d(x)=i $ . Since $ a_{n}=0 $ , it is not given in the input.

## 输出格式

Print $ 2n-2 $ numbers. The $ k $ -th of these numbers must be equal to $ f_{k} $ modulo $ 10^{9}+7 $ .

## 说明/提示

This the tree from the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954H/8a09c9c56935b94e970d5753d7484c0e7a756d44.png)

## 样例 #1

### 输入

```
4
2 2 2

```

### 输出

```
14 19 20 20 16 16 
```

## 样例 #2

### 输入

```
3
2 3

```

### 输出

```
8 13 6 9 
```

