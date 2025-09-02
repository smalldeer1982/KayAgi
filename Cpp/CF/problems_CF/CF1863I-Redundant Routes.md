---
title: "Redundant Routes"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1863I
tag: []
---

# Redundant Routes

## 题目描述

You are given a tree with $ n $ vertices labeled $ 1, 2, \ldots, n $ . The length of a simple path in the tree is the number of vertices in it.

You are to select a set of simple paths of length at least $ 2 $ each, but you cannot simultaneously select two distinct paths contained one in another. Find the largest possible size of such a set.

Formally, a set $ S $ of vertices is called a route if it contains at least two vertices and coincides with the set of vertices of a simple path in the tree. A collection of distinct routes is called a timetable. A route $ S $ in a timetable $ T $ is called redundant if there is a different route $ S' \in T $ such that $ S \subset S' $ . A timetable is called efficient if it contains no redundant routes. Find the largest possible number of routes in an efficient timetable.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 3000 $ ).

The $ i $ -th of the following $ n - 1 $ lines contains two integers $ u_i $ and $ v_i $ ( $ 1 \le u_i, v_i \le n $ , $ u_i \neq v_i $ ) — the numbers of vertices connected by the $ i $ -th edge.

It is guaranteed that the given edges form a tree.

## 输出格式

Print a single integer — the answer to the problem.

## 说明/提示

In the first example, possible efficient timetables are $ \{\{1, 2\}, \{1, 3\}, \{1, 4\}\} $ and $ \{\{1, 2, 3\}, \{1, 2, 4\}, \{1, 3, 4\}\} $ .

In the second example, we can choose $ \{ \{1, 2, 3\}, \{2, 3, 4\}, \{3, 4, 6\}, \{2, 3, 5\}, \{3, 4, 5\}, \{3, 4, 7\}, \{4, 6, 7\}\} $ .

## 样例 #1

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
2 1
3 2
4 3
5 3
6 4
7 4
```

### 输出

```
7
```

