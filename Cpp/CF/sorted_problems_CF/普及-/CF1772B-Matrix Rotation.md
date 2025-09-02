---
title: "Matrix Rotation"
layout: "post"
diff: 普及-
pid: CF1772B
tag: []
---

# Matrix Rotation

## 题目描述

You have a matrix $ 2 \times 2 $ filled with distinct integers. You want your matrix to become beautiful. The matrix is beautiful if the following two conditions are satisfied:

- in each row, the first element is smaller than the second element;
- in each column, the first element is smaller than the second element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1772B/3883cb5d5c3c3237649026ca712db7066e7d51ae.png)You can perform the following operation on the matrix any number of times: rotate it clockwise by $ 90 $ degrees, so the top left element shifts to the top right cell, the top right element shifts to the bottom right cell, and so on:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1772B/a844c7395726cf76b3147efc79ccce4d8f167fbf.png)Determine if it is possible to make the matrix beautiful by applying zero or more operations.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of two lines. Each of those lines contains two integers — the elements of the corresponding row of the matrix. In each matrix, all four elements are distinct integers from $ 1 $ to $ 100 $ .

## 输出格式

For each test case, print YES if the matrix can become beautiful, or NO otherwise. You may print each letter in any case (YES, yes, Yes will all be recognized as positive answer, NO, no and nO will all be recognized as negative answer).

## 样例 #1

### 输入

```
6
1 3
5 7
8 10
3 4
8 10
4 3
6 1
9 2
7 5
4 2
1 2
4 3
```

### 输出

```
YES
YES
NO
YES
YES
NO
```

