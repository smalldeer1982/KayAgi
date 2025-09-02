---
title: "Heaps"
layout: "post"
diff: 省选/NOI-
pid: CF955F
tag: []
---

# Heaps

## 题目描述

You're given a tree with $ n $ vertices rooted at $ 1 $ .

We say that there's a $ k $ -ary heap of depth $ m $ located at $ u $ if the following holds:

- For $ m=1 $ $ u $ itself is a $ k $ -ary heap of depth $ 1 $ .
- For $ m&gt;1 $ vertex $ u $ is a $ k $ -ary heap of depth $ m $ if at least $ k $ of its children are $ k $ -ary heaps of depth at least $ m-1 $ .

Denote $ dp_{k}(u) $ as maximum depth of $ k $ -ary heap in the subtree of $ u $ (including $ u $ ). Your goal is to compute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955F/5de2414b533cccf22014f0b7eca5e58cbc6e8f9c.png).

## 输入格式

The first line contains an integer $ n $ denoting the size of the tree $ (2<=n<=3·10^{5}) $ .

The next $ n-1 $ lines contain two integers $ u $ , $ v $ each, describing vertices connected by $ i $ -th edge.

It's guaranteed that the given configuration forms a tree.

## 输出格式

Output the answer to the task.

## 说明/提示

Consider sample case one.

For $ k>=3 $ all $ dp_{k} $ will be equal to $ 1 $ .

For $ k=2 $ $ dp_{k} $ is $ 2 $ if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955F/295fea3eafde0a7829eafa0db84ff6ad03162c9f.png) and $ 1 $ otherwise.

For $ k=1 $ $ dp_{k} $ values are $ (3,1,2,1) $ respectively.

To sum up, $ 4·1+4·1+2·2+2·1+3+1+2+1=21 $ .

## 样例 #1

### 输入

```
4
1 3
2 3
4 3

```

### 输出

```
21

```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4

```

### 输出

```
22

```

