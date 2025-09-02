---
title: "Tournament Construction"
layout: "post"
diff: 省选/NOI-
pid: CF850D
tag: []
---

# Tournament Construction

## 题目描述

Ivan is reading a book about tournaments. He knows that a tournament is an oriented graph with exactly one oriented edge between each pair of vertices. The score of a vertex is the number of edges going outside this vertex.

Yesterday Ivan learned Landau's criterion: there is tournament with scores $ d_{1}<=d_{2}<=...<=d_{n} $ if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850D/4fe680476592e82ee231e53c258b2a4afe965574.png) for all $ 1<=k&lt;n $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF850D/b56c7605c03639fe817d86958ff45e5e76f9d556.png).

Now, Ivan wanna solve following problem: given a set of numbers $ S={a_{1},a_{2},...,a_{m}} $ , is there a tournament with given set of scores? I.e. is there tournament with sequence of scores $ d_{1},d_{2},...,d_{n} $ such that if we remove duplicates in scores, we obtain the required set $ {a_{1},a_{2},...,a_{m}} $ ?

Find a tournament with minimum possible number of vertices.

## 输入格式

The first line contains a single integer $ m $ ( $ 1<=m<=31 $ ).

The next line contains $ m $ distinct integers $ a_{1},a_{2},...,a_{m} $ ( $ 0<=a_{i}<=30 $ ) — elements of the set $ S $ . It is guaranteed that all elements of the set are distinct.

## 输出格式

If there are no such tournaments, print string "=(" (without quotes).

Otherwise, print an integer $ n $ — the number of vertices in the tournament.

Then print $ n $ lines with $ n $ characters — matrix of the tournament. The $ j $ -th element in the $ i $ -th row should be $ 1 $ if the edge between the $ i $ -th and the $ j $ -th vertices is oriented towards the $ j $ -th vertex, and $ 0 $ otherwise. The main diagonal should contain only zeros.

## 样例 #1

### 输入

```
2
1 2

```

### 输出

```
4
0011
1001
0100
0010

```

## 样例 #2

### 输入

```
2
0 3

```

### 输出

```
6
000111
100011
110001
011001
001101
000000

```

