---
title: "Makes And The Product"
layout: "post"
diff: 普及/提高-
pid: CF817B
tag: []
---

# Makes And The Product

## 题目描述

After returning from the army Makes received a gift — an array $ a $ consisting of $ n $ positive integer numbers. He hadn't been solving problems for a long time, so he became interested to answer a particular question: how many triples of indices $ (i, j, k) $ ( $ i&lt;j&lt;k $ ), such that $ a_{i}·a_{j}·a_{k} $ is minimum possible, are there in the array? Help him with it!

## 输入格式

The first line of input contains a positive integer number $ n (3<=n<=10^{5}) $ — the number of elements in array $ a $ . The second line contains $ n $ positive integer numbers $ a_{i} (1<=a_{i}<=10^{9}) $ — the elements of a given array.

## 输出格式

Print one number — the quantity of triples $ (i, j, k) $ such that $ i, j $ and $ k $ are pairwise distinct and $ a_{i}·a_{j}·a_{k} $ is minimum possible.

## 说明/提示

In the first example Makes always chooses three ones out of four, and the number of ways to choose them is $ 4 $ .

In the second example a triple of numbers $ (1,2,3) $ is chosen (numbers, not indices). Since there are two ways to choose an element $ 3 $ , then the answer is $ 2 $ .

In the third example a triple of numbers $ (1,1,2) $ is chosen, and there's only one way to choose indices.

## 样例 #1

### 输入

```
4
1 1 1 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5
1 3 2 3 4

```

### 输出

```
2

```

## 样例 #3

### 输入

```
6
1 3 3 1 3 2

```

### 输出

```
1

```

