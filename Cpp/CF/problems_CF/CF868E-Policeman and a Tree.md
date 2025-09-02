---
title: "Policeman and a Tree"
layout: "post"
diff: 省选/NOI-
pid: CF868E
tag: []
---

# Policeman and a Tree

## 题目描述

You are given a tree (a connected non-oriented graph without cycles) with vertices numbered from $ 1 $ to $ n $ , and the length of the $ i $ -th edge is $ w_{i} $ . In the vertex $ s $ there is a policeman, in the vertices $ x_{1},x_{2},...,x_{m} $ ( $ x_{j}≠s $ ) $ m $ criminals are located.

The policeman can walk along the edges with speed $ 1 $ , the criminals can move with arbitrary large speed. If a criminal at some moment is at the same point as the policeman, he instantly gets caught by the policeman. Determine the time needed for the policeman to catch all criminals, assuming everybody behaves optimally (i.e. the criminals maximize that time, the policeman minimizes that time). Everybody knows positions of everybody else at any moment of time.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=50 $ ) — the number of vertices in the tree. The next $ n-1 $ lines contain three integers each: $ u_{i} $ , $ v_{i} $ , $ w_{i} $ ( $ 1<=u_{i},v_{i}<=n $ , $ 1<=w_{i}<=50 $ ) denoting edges and their lengths. It is guaranteed that the given graph is a tree.

The next line contains single integer $ s $ ( $ 1<=s<=n $ ) — the number of vertex where the policeman starts.

The next line contains single integer $ m $ ( $ 1<=m<=50 $ ) — the number of criminals. The next line contains $ m $ integers $ x_{1},x_{2},...,x_{m} $ ( $ 1<=x_{j}<=n $ , $ x_{j}≠s $ ) — the number of vertices where the criminals are located. $ x_{j} $ are not necessarily distinct.

## 输出格式

If the policeman can't catch criminals, print single line "Terrorists win" (without quotes).

Otherwise, print single integer — the time needed to catch all criminals.

## 说明/提示

In the first example one of the optimal scenarios is the following. The criminal number $ 2 $ moves to vertex $ 3 $ , the criminal $ 4 $ — to vertex $ 4 $ . The policeman goes to vertex $ 4 $ and catches two criminals. After that the criminal number $ 1 $ moves to the vertex $ 2 $ . The policeman goes to vertex $ 3 $ and catches criminal $ 2 $ , then goes to the vertex $ 2 $ and catches the remaining criminal.

## 样例 #1

### 输入

```
4
1 2 2
1 3 1
1 4 1
2
4
3 1 4 1

```

### 输出

```
8

```

## 样例 #2

### 输入

```
6
1 2 3
2 3 5
3 4 1
3 5 4
2 6 3
2
3
1 3 5

```

### 输出

```
21

```

