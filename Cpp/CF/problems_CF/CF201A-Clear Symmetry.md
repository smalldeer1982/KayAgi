---
title: "Clear Symmetry"
layout: "post"
diff: 普及-
pid: CF201A
tag: []
---

# Clear Symmetry

## 题目描述

Consider some square matrix $ A $ with side $ n $ consisting of zeros and ones. There are $ n $ rows numbered from $ 1 $ to $ n $ from top to bottom and $ n $ columns numbered from $ 1 $ to $ n $ from left to right in this matrix. We'll denote the element of the matrix which is located at the intersection of the $ i $ -row and the $ j $ -th column as $ A_{i,j} $ .

Let's call matrix $ A $ clear if no two cells containing ones have a common side.

Let's call matrix $ A $ symmetrical if it matches the matrices formed from it by a horizontal and/or a vertical reflection. Formally, for each pair $ (i,j) $ $ (1<=i,j<=n) $ both of the following conditions must be met: $ A_{i,j}=A_{n-i+1,j} $ and $ A_{i,j}=A_{i,n-j+1} $ .

Let's define the sharpness of matrix $ A $ as the number of ones in it.

Given integer $ x $ , your task is to find the smallest positive integer $ n $ such that there exists a clear symmetrical matrix $ A $ with side $ n $ and sharpness $ x $ .

## 输入格式

The only line contains a single integer $ x $ ( $ 1<=x<=100 $ ) — the required sharpness of the matrix.

## 输出格式

Print a single number — the sought value of $ n $ .

## 说明/提示

The figure below shows the matrices that correspond to the samples:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF201A/4a353f15397909088e2fcb0cff23c93ecb30c822.png)

## 样例 #1

### 输入

```
4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
9

```

### 输出

```
5

```

