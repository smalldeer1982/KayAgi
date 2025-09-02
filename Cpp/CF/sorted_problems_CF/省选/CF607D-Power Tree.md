---
title: "Power Tree"
layout: "post"
diff: 省选/NOI-
pid: CF607D
tag: []
---

# Power Tree

## 题目描述

Genos and Saitama went shopping for Christmas trees. However, a different type of tree caught their attention, the exalted Power Tree.

A Power Tree starts out as a single root vertex indexed $ 1 $ . A Power Tree grows through a magical phenomenon known as an update. In an update, a single vertex is added to the tree as a child of some other vertex.

Every vertex in the tree (the root and all the added vertices) has some value $ v_{i} $ associated with it. The power of a vertex is defined as the strength of the multiset composed of the value associated with this vertex ( $ v_{i} $ ) and the powers of its direct children. The strength of a multiset is defined as the sum of all elements in the multiset multiplied by the number of elements in it. Or in other words for some multiset $ S $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF607D/e4544f58f9cc15f32e75061d79960f17ec2c1efb.png)Saitama knows the updates that will be performed on the tree, so he decided to test Genos by asking him queries about the tree during its growth cycle.

An update is of the form $ 1 p v $ , and adds a new vertex with value $ v $ as a child of vertex $ p $ .

A query is of the form $ 2 u $ , and asks for the power of vertex $ u $ .

Please help Genos respond to these queries modulo $ 10^{9}+7 $ .

## 输入格式

The first line of the input contains two space separated integers $ v_{1} $ and $ q $ ( $ 1<=v_{1}&lt;10^{9} $ , $ 1<=q<=200000 $ ) — the value of vertex $ 1 $ and the total number of updates and queries respectively.

The next $ q $ lines contain the updates and queries. Each of them has one of the following forms:

- $ 1 p_{i} v_{i} $ , if these line describes an update. The index of the added vertex is equal to the smallest positive integer not yet used as an index in the tree. It is guaranteed that $ p_{i} $ is some already existing vertex and $ 1<=v_{i}&lt;10^{9} $ .
- $ 2 u_{i} $ , if these line describes a query. It is guaranteed $ u_{i} $ will exist in the tree.

It is guaranteed that the input will contain at least one query.

## 输出格式

For each query, print out the power of the given vertex modulo $ 10^{9}+7 $ .

## 说明/提示

For the first sample case, after all the updates the graph will have vertices labelled in the following manner: 1 — 2 — 3 — 4 — 5

These vertices will have corresponding values: 2 — 3 — 5 — 7 — 11

And corresponding powers: 344 — 170 — 82 — 36 — 11

## 样例 #1

### 输入

```
2 5
1 1 3
1 2 5
1 3 7
1 4 11
2 1

```

### 输出

```
344

```

## 样例 #2

### 输入

```
5 5
1 1 4
1 2 3
2 2
1 2 7
2 1

```

### 输出

```
14
94

```

