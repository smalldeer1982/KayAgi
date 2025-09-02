---
title: "COT2 - Count on a tree II"
layout: "post"
diff: 省选/NOI-
pid: SP10707
tag: ['莫队', '深度优先搜索 DFS']
---

# COT2 - Count on a tree II

## 题目描述

You are given a tree with **N** nodes. The tree nodes are numbered from **1** to **N**. Each node has an integer weight.

We will ask you to perform the following operation:

- **u v** : ask for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

## 输入格式

In the first line there are two integers **N** and **M**. (**N** <= 40000, **M** <= 100000)

In the second line there are **N** integers. The i-th integer denotes the weight of the i-th node.

In the next **N-1** lines, each line contains two integers **u** **v**, which describes an edge (**u**, **v**).

In the next **M** lines, each line contains two integers **u** **v**, which means an operation asking for how many different integers that represent the weight of nodes there are on the path from **u** to **v**.

## 输出格式

For each operation, print its result.

## 样例 #1

### 输入

```
8 2
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5
7 8
```

### 输出

```
4
4
```

