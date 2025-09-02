---
title: "Sereja and Mirroring"
layout: "post"
diff: 普及/提高-
pid: CF426B
tag: []
---

# Sereja and Mirroring

## 题目描述

Let's assume that we are given a matrix $ b $ of size $ x×y $ , let's determine the operation of mirroring matrix $ b $ . The mirroring of matrix $ b $ is a $ 2x×y $ matrix $ c $ which has the following properties:

- the upper half of matrix $ c $ (rows with numbers from $ 1 $ to $ x $ ) exactly matches $ b $ ;
- the lower half of matrix $ c $ (rows with numbers from $ x+1 $ to $ 2x $ ) is symmetric to the upper one; the symmetry line is the line that separates two halves (the line that goes in the middle, between rows $ x $ and $ x+1 $ ).

Sereja has an $ n×m $ matrix $ a $ . He wants to find such matrix $ b $ , that it can be transformed into matrix $ a $ , if we'll perform on it several (possibly zero) mirrorings. What minimum number of rows can such matrix contain?

## 输入格式

The first line contains two integers, $ n $ and $ m $ $ (1<=n,m<=100) $ . Each of the next $ n $ lines contains $ m $ integers — the elements of matrix $ a $ . The $ i $ -th line contains integers $ a_{i1},a_{i2},...,a_{im} $ $ (0<=a_{ij}<=1) $ — the $ i $ -th row of the matrix $ a $ .

## 输出格式

In the single line, print the answer to the problem — the minimum number of rows of matrix $ b $ .

## 说明/提示

In the first test sample the answer is a $ 2×3 $ matrix $ b $ :

`<br></br>001<br></br>110<br></br>`If we perform a mirroring operation with this matrix, we get the matrix $ a $ that is given in the input:

`<br></br>001<br></br>110<br></br>110<br></br>001<br></br>`

## 样例 #1

### 输入

```
4 3
0 0 1
1 1 0
1 1 0
0 0 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 3
0 0 0
0 0 0
0 0 0

```

### 输出

```
3

```

## 样例 #3

### 输入

```
8 1
0
1
1
0
0
1
1
0

```

### 输出

```
2

```

