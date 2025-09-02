---
title: "Labeling the Tree with Distances"
layout: "post"
diff: 省选/NOI-
pid: CF1794E
tag: []
---

# Labeling the Tree with Distances

## 题目描述

You are given an unweighted tree of $ n $ vertices numbered from $ 1 $ to $ n $ and a list of $ n-1 $ integers $ a_1, a_2, \ldots, a_{n-1} $ . A tree is a connected undirected graph without cycles. You will use each element of the list to label one vertex. No vertex should be labeled twice. You can label the only remaining unlabeled vertex with any integer.

A vertex $ x $ is called good if it is possible to do this labeling so that for each vertex $ i $ , its label is the distance between $ x $ and $ i $ . The distance between two vertices $ s $ and $ t $ on a tree is the minimum number of edges on a path that starts at vertex $ s $ and ends at vertex $ t $ .

Find all good vertices.

## 输入格式

The first line contains one integer $ n $ ( $ 2\le n\le 2\cdot 10^5 $ ) — the number of vertices in the tree.

The second line contains $ n - 1 $ integers $ a_1,a_2,\ldots,a_{n-1} $ ( $ 0\le a_i < n $ ) — the given list.

Then, $ n−1 $ lines follow. Each of them contains two integers $ u $ and $ v $ ( $ 1\le u,v\le n $ ) denoting an edge between vertices $ u $ and $ v $ . It is guaranteed that the edges form a tree.

## 输出格式

In the first line print the number of good vertices.

In the second line, print the indices of all good vertices in ascending order.

## 说明/提示

This is the tree for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1794E/f54192bbd4a09409727069f5296c3b8069512eac.png)And these are two possible labelings with the elements on the list so that $ 2 $ is a good vertex (left) and $ 4 $ is a good vertex (right).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1794E/e87e5306fe63a198bad6dafe8ce7c0bd63e8d99b.png)The square below each vertex represents its label. The black squares contain the numbers which were on the given list and the only white square contains the only number which was not on the given list.

In the second example, the only good vertex is vertex $ 3 $ .

In the third example, there are no good vertices.

## 样例 #1

### 输入

```
6
2 1 0 1 2
1 2
2 3
2 4
4 5
4 6
```

### 输出

```
2
2 4
```

## 样例 #2

### 输入

```
5
1 2 1 2
1 2
3 2
3 4
5 4
```

### 输出

```
1
3
```

## 样例 #3

### 输入

```
3
2 2
1 2
2 3
```

### 输出

```
0
```

