---
title: "Gardener Alex"
layout: "post"
diff: 省选/NOI-
pid: CF1220F
tag: []
---

# Gardener Alex

## 题目描述

Gardener Alex loves to grow trees. We remind that tree is a connected acyclic graph on $ n $ vertices.

Today he decided to grow a rooted binary tree. A binary tree is a tree where any vertex has no more than two sons. Luckily, Alex has a permutation of numbers from $ 1 $ to $ n $ which he was presented at his last birthday, so he decided to grow a tree according to this permutation. To do so he does the following process: he finds a minimum element and makes it a root of the tree. After that permutation is divided into two parts: everything that is to the left of the minimum element, and everything that is to the right. The minimum element on the left part becomes the left son of the root, and the minimum element on the right part becomes the right son of the root. After that, this process is repeated recursively on both parts.

Now Alex wants to grow a forest of trees: one tree for each cyclic shift of the permutation. He is interested in what cyclic shift gives the tree of minimum depth. Unfortunately, growing a forest is a hard and long process, but Alex wants the answer right now. Will you help him?

We remind that cyclic shift of permutation $ a_1, a_2, \ldots, a_k, \ldots, a_n $ for $ k $ elements to the left is the permutation $ a_{k + 1}, a_{k + 2}, \ldots, a_n, a_1, a_2, \ldots, a_k $ .

## 输入格式

First line contains an integer number $ n ~ (1 \leqslant n \leqslant 200\,000) $ — length of the permutation.

Second line contains $ n $ integer numbers $ a_1, a_2, \ldots, a_n ~ (1 \leqslant a_i \leqslant n) $ , and it is guaranteed that all numbers occur exactly one time.

## 输出格式

Print two numbers separated with space: minimum possible depth of a tree and how many elements we need to shift left to achieve this depth. The number of elements should be a number from $ 0 $ to $ n - 1 $ . If there are several possible answers, print any of them.

## 说明/提示

The following picture depicts all possible trees for sample test and cyclic shifts on which they are achieved.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1220F/842ebd6718bd1cfe86bfa2961c3f54499387dbf1.png)

## 样例 #1

### 输入

```
4
1 2 3 4

```

### 输出

```
3 2

```

