---
title: "Gluttony"
layout: "post"
diff: 普及+/提高
pid: CF891B
tag: []
---

# Gluttony

## 题目描述

You are given an array $ a $ with $ n $ distinct integers. Construct an array $ b $ by permuting $ a $ such that for every non-empty subset of indices $ S={x_{1},x_{2},...,x_{k}} $ ( $ 1<=x_{i}<=n $ , $ 0&lt;k&lt;n $ ) the sums of elements on that positions in $ a $ and $ b $ are different, i. e.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF891B/3cd3fa1580a1bdd16185974adbd0425cf2d97136.png)

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=22 $ ) — the size of the array.

The second line contains $ n $ space-separated distinct integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ) — the elements of the array.

## 输出格式

If there is no such array $ b $ , print -1.

Otherwise in the only line print $ n $ space-separated integers $ b_{1},b_{2},...,b_{n} $ . Note that $ b $ must be a permutation of $ a $ .

If there are multiple answers, print any of them.

## 说明/提示

An array $ x $ is a permutation of $ y $ , if we can shuffle elements of $ y $ such that it will coincide with $ x $ .

Note that the empty subset and the subset containing all indices are not counted.

## 样例 #1

### 输入

```
2
1 2

```

### 输出

```
2 1 

```

## 样例 #2

### 输入

```
4
1000 100 10 1

```

### 输出

```
100 1 1000 10

```

