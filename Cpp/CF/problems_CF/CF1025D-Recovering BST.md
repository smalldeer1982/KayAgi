---
title: "Recovering BST"
layout: "post"
diff: 省选/NOI-
pid: CF1025D
tag: ['搜索', '构造']
---

# Recovering BST

## 题目描述

Dima the hamster enjoys nibbling different things: cages, sticks, bad problemsetters and even trees!

Recently he found a binary search tree and instinctively nibbled all of its edges, hence messing up the vertices. Dima knows that if Andrew, who has been thoroughly assembling the tree for a long time, comes home and sees his creation demolished, he'll get extremely upset.

To not let that happen, Dima has to recover the binary search tree. Luckily, he noticed that any two vertices connected by a direct edge had their greatest common divisor value exceed $ 1 $ .

Help Dima construct such a binary search tree or determine that it's impossible. The definition and properties of a binary search tree can be found [here.](https://en.wikipedia.org/wiki/Binary_search_tree)

## 输入格式

The first line contains the number of vertices $ n $ ( $ 2 \le n \le 700 $ ).

The second line features $ n $ distinct integers $ a_i $ ( $ 2 \le a_i \le 10^9 $ ) — the values of vertices in ascending order.

## 输出格式

If it is possible to reassemble the binary search tree, such that the greatest common divisor of any two vertices connected by the edge is greater than $ 1 $ , print "Yes" (quotes for clarity).

Otherwise, print "No" (quotes for clarity).

## 说明/提示

The picture below illustrates one of the possible trees for the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025D/a6281ebfc3addc046e3a216e978640a7d00d938f.png)The picture below illustrates one of the possible trees for the third example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025D/422d22e6560dde35033dafdd73125c60e4d294d8.png)

## 样例 #1

### 输入

```
6
3 6 9 18 36 108

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
2
7 17

```

### 输出

```
No

```

## 样例 #3

### 输入

```
9
4 8 10 12 15 18 33 44 81

```

### 输出

```
Yes

```

