---
title: "My Beautiful Madness"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1464F
tag: []
---

# My Beautiful Madness

## 题目描述

You are given a tree. We will consider simple paths on it. Let's denote path between vertices $ a $ and $ b $ as $ (a, b) $ . Let $ d $ -neighborhood of a path be a set of vertices of the tree located at a distance $ \leq d $ from at least one vertex of the path (for example, $ 0 $ -neighborhood of a path is a path itself). Let $ P $ be a multiset of the tree paths. Initially, it is empty. You are asked to maintain the following queries:

- $ 1 $ $ u $ $ v $ — add path $ (u, v) $ into $ P $ ( $ 1 \leq u, v \leq n $ ).
- $ 2 $ $ u $ $ v $ — delete path $ (u, v) $ from $ P $ ( $ 1 \leq u, v \leq n $ ). Notice that $ (u, v) $ equals to $ (v, u) $ . For example, if $ P = \{(1, 2), (1, 2)\} $ , than after query $ 2 $ $ 2 $ $ 1 $ , $ P = \{(1, 2)\} $ .
- $ 3 $ $ d $ — if intersection of all $ d $ -neighborhoods of paths from $ P $ is not empty output "Yes", otherwise output "No" ( $ 0 \leq d \leq n - 1 $ ).

## 输入格式

The first line contains two integers $ n $ and $ q $ — the number of vertices in the tree and the number of queries, accordingly ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ 2 \leq q \leq 2 \cdot 10^5 $ ).

Each of the following $ n - 1 $ lines contains two integers $ x_i $ and $ y_i $ — indices of vertices connected by $ i $ -th edge ( $ 1 \le x_i, y_i \le n $ ).

The following $ q $ lines contain queries in the format described in the statement.

It's guaranteed that:

- for a query $ 2 $ $ u $ $ v $ , path $ (u, v) $ (or $ (v, u) $ ) is present in $ P $ ,
- for a query $ 3 $ $ d $ , $ P \neq \varnothing $ ,
- there is at least one query of the third type.

## 输出格式

For each query of the third type output answer on a new line.

## 样例 #1

### 输入

```
1 4
1 1 1
1 1 1
2 1 1
3 0
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5 3
1 2
1 3
3 4
4 5
1 1 2
1 5 5
3 1
```

### 输出

```
No
```

## 样例 #3

### 输入

```
10 6
1 2
2 3
3 4
4 7
7 10
2 5
5 6
6 8
8 9
1 9 9
1 9 8
1 8 5
3 0
3 1
3 2
```

### 输出

```
No
Yes
Yes
```

