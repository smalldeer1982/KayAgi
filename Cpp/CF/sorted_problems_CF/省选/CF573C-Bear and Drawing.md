---
title: "Bear and Drawing"
layout: "post"
diff: 省选/NOI-
pid: CF573C
tag: []
---

# Bear and Drawing

## 题目描述

Limak is a little bear who learns to draw. People usually start with houses, fences and flowers but why would bears do it? Limak lives in the forest and he decides to draw a tree.

Recall that tree is a connected graph consisting of $ n $ vertices and $ n-1 $ edges.

Limak chose a tree with $ n $ vertices. He has infinite strip of paper with two parallel rows of dots. Little bear wants to assign vertices of a tree to some $ n $ distinct dots on a paper so that edges would intersect only at their endpoints — drawn tree must be planar. Below you can see one of correct drawings for the first sample test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573C/3e1f6bfb27269bc2d4c98e1421026d340bfdb0da.png)Is it possible for Limak to draw chosen tree?

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=10^{5} $ ).

Next $ n-1 $ lines contain description of a tree. $ i $ -th of them contains two space-separated integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n,a_{i}≠b_{i} $ ) denoting an edge between vertices $ a_{i} $ and $ b_{i} $ . It's guaranteed that given description forms a tree.

## 输出格式

Print "Yes" (without the quotes) if Limak can draw chosen tree. Otherwise, print "No" (without the quotes).

## 样例 #1

### 输入

```
8
1 2
1 3
1 6
6 4
6 7
6 5
7 8

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
13
1 2
1 3
1 4
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13

```

### 输出

```
No

```

