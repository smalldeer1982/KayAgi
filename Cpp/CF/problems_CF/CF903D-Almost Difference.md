---
title: "Almost Difference"
layout: "post"
diff: 提高+/省选-
pid: CF903D
tag: []
---

# Almost Difference

## 题目描述

Let's denote a function

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF903D/775e2389c0046855a8c7f1a2f9b05b0f64f8c0ab.png)

You are given an array $ a $ consisting of $ n $ integers. You have to calculate the sum of $ d(a_{i},a_{j}) $ over all pairs $ (i,j) $ such that $ 1<=i<=j<=n $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=200000 $ ) — the number of elements in $ a $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of the array.

## 输出格式

Print one integer — the sum of $ d(a_{i},a_{j}) $ over all pairs $ (i,j) $ such that $ 1<=i<=j<=n $ .

## 说明/提示

In the first example:

1. $ d(a_{1},a_{2})=0 $ ;
2. $ d(a_{1},a_{3})=2 $ ;
3. $ d(a_{1},a_{4})=0 $ ;
4. $ d(a_{1},a_{5})=2 $ ;
5. $ d(a_{2},a_{3})=0 $ ;
6. $ d(a_{2},a_{4})=0 $ ;
7. $ d(a_{2},a_{5})=0 $ ;
8. $ d(a_{3},a_{4})=-2 $ ;
9. $ d(a_{3},a_{5})=0 $ ;
10. $ d(a_{4},a_{5})=2 $ .

## 样例 #1

### 输入

```
5
1 2 3 1 3

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4
6 6 5 5

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4
6 6 4 4

```

### 输出

```
-8

```

