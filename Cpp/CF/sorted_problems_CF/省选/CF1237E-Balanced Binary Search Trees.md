---
title: "Balanced Binary Search Trees"
layout: "post"
diff: 省选/NOI-
pid: CF1237E
tag: []
---

# Balanced Binary Search Trees

## 题目描述

Recall that a binary search tree is a rooted binary tree, whose nodes each store a key and each have at most two distinguished subtrees, left and right. The key in each node must be greater than any key stored in the left subtree, and less than any key stored in the right subtree.

The depth of a vertex is the number of edges on the simple path from the vertex to the root. In particular, the depth of the root is $ 0 $ .

Let's call a binary search tree perfectly balanced if there doesn't exist a binary search tree with the same number of vertices that has a strictly smaller sum of depths of its vertices.

Let's call a binary search tree with integer keys striped if both of the following conditions are satisfied for every vertex $ v $ :

- If $ v $ has a left subtree whose root is $ u $ , then the parity of the key of $ v $ is different from the parity of the key of $ u $ .
- If $ v $ has a right subtree whose root is $ w $ , then the parity of the key of $ v $ is the same as the parity of the key of $ w $ .

You are given a single integer $ n $ . Find the number of perfectly balanced striped binary search trees with $ n $ vertices that have distinct integer keys between $ 1 $ and $ n $ , inclusive. Output this number modulo $ 998\,244\,353 $ .

## 输入格式

The only line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ), denoting the required number of vertices.

## 输出格式

Output the number of perfectly balanced striped binary search trees with $ n $ vertices and distinct integer keys between $ 1 $ and $ n $ , inclusive, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, this is the only tree that satisfies the conditions: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237E/4e380cf51a86e19e2f842af24fccbe15c0690783.png)

In the second example, here are various trees that don't satisfy some condition: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237E/2e8a40da0f5146c1c54bd64b0e3ffa3e8248274f.png)

## 样例 #1

### 输入

```
4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3

```

### 输出

```
0

```

