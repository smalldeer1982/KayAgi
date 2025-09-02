---
title: "Beautiful Matrix"
layout: "post"
diff: 入门
pid: CF263A
tag: []
---

# Beautiful Matrix

## 题目描述

You've got a $ 5×5 $ matrix, consisting of $ 24 $ zeroes and a single number one. Let's index the matrix rows by numbers from $ 1 $ to $ 5 $ from top to bottom, let's index the matrix columns by numbers from $ 1 $ to $ 5 $ from left to right. In one move, you are allowed to apply one of the two following transformations to the matrix:

1. Swap two neighboring matrix rows, that is, rows with indexes $ i $ and $ i+1 $ for some integer $ i $ $ (1<=i&lt;5) $ .
2. Swap two neighboring matrix columns, that is, columns with indexes $ j $ and $ j+1 $ for some integer $ j $ $ (1<=j&lt;5) $ .

You think that a matrix looks beautiful, if the single number one of the matrix is located in its middle (in the cell that is on the intersection of the third row and the third column). Count the minimum number of moves needed to make the matrix beautiful.

## 输入格式

The input consists of five lines, each line contains five integers: the $ j $ -th integer in the $ i $ -th line of the input represents the element of the matrix that is located on the intersection of the $ i $ -th row and the $ j $ -th column. It is guaranteed that the matrix consists of $ 24 $ zeroes and a single number one.

## 输出格式

Print a single integer — the minimum number of moves needed to make the matrix beautiful.

## 样例 #1

### 输入

```
0 0 0 0 0
0 0 0 0 1
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

```

### 输出

```
3

```

## 样例 #2

### 输入

```
0 0 0 0 0
0 0 0 0 0
0 1 0 0 0
0 0 0 0 0
0 0 0 0 0

```

### 输出

```
1

```

