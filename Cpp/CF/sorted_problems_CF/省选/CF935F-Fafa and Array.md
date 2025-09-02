---
title: "Fafa and Array"
layout: "post"
diff: 省选/NOI-
pid: CF935F
tag: []
---

# Fafa and Array

## 题目描述

Fafa has an array $ A $ of $ n $ positive integers, the function $ f(A) $ is defined as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935F/dc9a0a0772798ba9fb8b149f527b509b8571b93b.png). He wants to do $ q $ queries of two types:

- $ 1lrx $ — find the maximum possible value of $ f(A) $ , if $ x $ is to be added to one element in the range $ [l,r] $ . You can choose to which element to add $ x $ .
- $ 2lrx $ — increase all the elements in the range $ [l,r] $ by value $ x $ .

Note that queries of type $ 1 $ don't affect the array elements.

## 输入格式

The first line contains one integer $ n $ $ (3<=n<=10^{5}) $ — the length of the array.

The second line contains $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ $ (0<a_{i}<=10^{9}) $ — the array elements.

The third line contains an integer $ q $ $ (1<=q<=10^{5}) $ — the number of queries.

Then $ q $ lines follow, line $ i $ describes the $ i $ -th query and contains four integers $ t_{i}l_{i}r_{i}x_{i} $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935F/b4776844d7d2421177af411bd5745433670f68b1.png).

It is guaranteed that at least one of the queries is of type $ 1 $ .

## 输出格式

For each query of type $ 1 $ , print the answer to the query.

## 样例 #1

### 输入

```
5
1 1 1 1 1
5
1 2 4 1
2 2 3 1
2 4 4 2
2 3 4 1
1 3 3 2

```

### 输出

```
2
8

```

## 样例 #2

### 输入

```
5
1 2 3 4 5
4
1 2 4 2
2 2 4 1
2 3 4 1
1 2 4 2

```

### 输出

```
6
10

```

