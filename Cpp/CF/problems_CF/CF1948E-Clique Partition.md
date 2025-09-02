---
title: "Clique Partition"
layout: "post"
diff: 普及+/提高
pid: CF1948E
tag: ['贪心', '构造']
---

# Clique Partition

## 题目描述

You are given two integers, $ n $ and $ k $ . There is a graph on $ n $ vertices, numbered from $ 1 $ to $ n $ , which initially has no edges.

You have to assign each vertex an integer; let $ a_i $ be the integer on the vertex $ i $ . All $ a_i $ should be distinct integers from $ 1 $ to $ n $ .

After assigning integers, for every pair of vertices $ (i, j) $ , you add an edge between them if $ |i - j| + |a_i - a_j| \le k $ .

Your goal is to create a graph which can be partitioned into the minimum possible (for the given values of $ n $ and $ k $ ) number of cliques. Each vertex of the graph should belong to exactly one clique. Recall that a clique is a set of vertices such that every pair of vertices in it are connected with an edge.

Since BledDest hasn't really brushed his programming skills up, he can't solve the problem "given a graph, partition it into the minimum number of cliques". So we also ask you to print the partition itself.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1600 $ ) — the number of test cases.

Each test case consists of one line containing two integers $ n $ and $ k $ ( $ 2 \le n \le 40 $ ; $ 1 \le k \le 2n $ ).

## 输出格式

For each test case, print three lines:

- the first line should contain $ n $ distinct integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — the values you assign to the vertices;
- the second line should contain one integer $ q $ ( $ 1 \le q \le n $ ) — the number of cliques you partition the graph into;
- the third line should contain $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le q $ ) — the partition of the graph into cliques. Where two vertices $ u $ and $ v $ are in the same clique if $ c_u = c_v $ .

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
2 3
5 4
8 16
```

### 输出

```
2 1
1
1 1
3 1 5 2 4
2
1 1 2 1 2
1 2 3 4 5 6 7 8
1
1 1 1 1 1 1 1 1
```

