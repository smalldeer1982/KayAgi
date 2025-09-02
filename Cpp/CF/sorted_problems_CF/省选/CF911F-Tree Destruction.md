---
title: "Tree Destruction"
layout: "post"
diff: 省选/NOI-
pid: CF911F
tag: []
---

# Tree Destruction

## 题目描述

You are given an unweighted tree with $ n $ vertices. Then $ n-1 $ following operations are applied to the tree. A single operation consists of the following steps:

1. choose two leaves;
2. add the length of the simple path between them to the answer;
3. remove one of the chosen leaves from the tree.

Initial answer (before applying operations) is $ 0 $ . Obviously after $ n-1 $ such operations the tree will consist of a single vertex.

Calculate the maximal possible answer you can achieve, and construct a sequence of operations that allows you to achieve this answer!

## 输入格式

The first line contains one integer number $ n $ ( $ 2<=n<=2·10^{5} $ ) — the number of vertices in the tree.

Next $ n-1 $ lines describe the edges of the tree in form $ a_{i},b_{i} $ ( $ 1<=a_{i} $ , $ b_{i}<=n $ , $ a_{i}≠b_{i} $ ). It is guaranteed that given graph is a tree.

## 输出格式

In the first line print one integer number — maximal possible answer.

In the next $ n-1 $ lines print the operations in order of their applying in format $ a_{i},b_{i},c_{i} $ , where $ a_{i},b_{i} $ — pair of the leaves that are chosen in the current operation ( $ 1<=a_{i} $ , $ b_{i}<=n $ ), $ c_{i} $ ( $ 1<=c_{i}<=n $ , $ c_{i}=a_{i} $ or $ c_{i}=b_{i} $ ) — choosen leaf that is removed from the tree in the current operation.

See the examples for better understanding.

## 样例 #1

### 输入

```
3
1 2
1 3

```

### 输出

```
3
2 3 3
2 1 1

```

## 样例 #2

### 输入

```
5
1 2
1 3
2 4
2 5

```

### 输出

```
9
3 5 5
4 3 3
4 1 1
4 2 2

```

