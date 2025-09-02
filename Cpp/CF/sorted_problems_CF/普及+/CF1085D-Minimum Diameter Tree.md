---
title: "Minimum Diameter Tree"
layout: "post"
diff: 普及+/提高
pid: CF1085D
tag: []
---

# Minimum Diameter Tree

## 题目描述

You are given a tree (an undirected connected graph without cycles) and an integer $ s $ .

Vanya wants to put weights on all edges of the tree so that all weights are non-negative real numbers and their sum is $ s $ . At the same time, he wants to make the diameter of the tree as small as possible.

Let's define the diameter of a weighed tree as the maximum sum of the weights of the edges lying on the path between two some vertices of the tree. In other words, the diameter of a weighed tree is the length of the longest simple path in the tree, where length of a path is equal to the sum of weights over all edges in the path.

Find the minimum possible diameter that Vanya can get.

## 输入格式

The first line contains two integer numbers $ n $ and $ s $ ( $ 2 \leq n \leq 10^5 $ , $ 1 \leq s \leq 10^9 $ ) — the number of vertices in the tree and the sum of edge weights.

Each of the following $ n−1 $ lines contains two space-separated integer numbers $ a_i $ and $ b_i $ ( $ 1 \leq a_i, b_i \leq n $ , $ a_i \neq b_i $ ) — the indexes of vertices connected by an edge. The edges are undirected.

It is guaranteed that the given edges form a tree.

## 输出格式

Print the minimum diameter of the tree that Vanya can get by placing some non-negative real weights on its edges with the sum equal to $ s $ .

Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is considered correct if $ \frac {|a-b|} {max(1, b)} \leq 10^{-6} $ .

## 说明/提示

In the first example it is necessary to put weights like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085D/c1a70d116ee899735bc4ecf7ff6c6bf75b292051.png)It is easy to see that the diameter of this tree is $ 2 $ . It can be proved that it is the minimum possible diameter.

In the second example it is necessary to put weights like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085D/7a6a70a648e37d9e55f1bb9aed6b2be7637ee566.png)

## 样例 #1

### 输入

```
4 3
1 2
1 3
1 4

```

### 输出

```
2.000000000000000000
```

## 样例 #2

### 输入

```
6 1
2 1
2 3
2 5
5 4
5 6

```

### 输出

```
0.500000000000000000
```

## 样例 #3

### 输入

```
5 5
1 2
2 3
3 4
3 5

```

### 输出

```
3.333333333333333333
```

