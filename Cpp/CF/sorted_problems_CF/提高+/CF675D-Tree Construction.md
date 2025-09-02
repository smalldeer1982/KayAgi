---
title: "Tree Construction"
layout: "post"
diff: 提高+/省选-
pid: CF675D
tag: []
---

# Tree Construction

## 题目描述

During the programming classes Vasya was assigned a difficult problem. However, he doesn't know how to code and was unable to find the solution in the Internet, so he asks you to help.

You are given a sequence $ a $ , consisting of $ n $ distinct integers, that is used to construct the binary search tree. Below is the formal description of the construction process.

1. First element $ a_{1} $ becomes the root of the tree.
2. Elements $ a_{2},a_{3},...,a_{n} $ are added one by one. To add element $ a_{i} $ one needs to traverse the tree starting from the root and using the following rules: 
  1. The pointer to the current node is set to the root.
  2. If $ a_{i} $ is greater than the value in the current node, then its right child becomes the current node. Otherwise, the left child of the current node becomes the new current node.
  3. If at some point there is no required child, the new node is created, it is assigned value $ a_{i} $ and becomes the corresponding child of the current node.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the length of the sequence $ a $ .

The second line contains $ n $ distinct integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ) — the sequence $ a $ itself.

## 输出格式

Output $ n-1 $ integers. For all $ i&gt;1 $ print the value written in the node that is the parent of the node with value $ a_{i} $ in it.

## 说明/提示

Picture below represents the tree obtained in the first sample.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675D/81b08320b33046f6dd8d383835aa5713076f0650.png)

Picture below represents the tree obtained in the second sample.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675D/a69a26d019b1bf51600e9935b0aa85fc4fdf5e99.png)

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
1 2

```

## 样例 #2

### 输入

```
5
4 2 3 1 6

```

### 输出

```
4 2 2 4

```

