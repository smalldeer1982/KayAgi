---
title: "The same permutation "
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF804E
tag: []
---

# The same permutation 

## 题目描述

Seyyed and MoJaK are friends of Sajjad. Sajjad likes a permutation. Seyyed wants to change the permutation in a way that Sajjad won't like it. Seyyed thinks more swaps yield more probability to do that, so he makes MoJaK to perform a swap between every pair of positions $ (i,j) $ , where $ i&lt;j $ , exactly once. MoJaK doesn't like to upset Sajjad.

Given the permutation, determine whether it is possible to swap all pairs of positions so that the permutation stays the same. If it is possible find how to do that.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=1000 $ ) — the size of the permutation.

As the permutation is not important, you can consider $ a_{i}=i $ , where the permutation is $ a_{1},a_{2},...,a_{n} $ .

## 输出格式

If it is not possible to swap all pairs of positions so that the permutation stays the same, print "NO",

Otherwise print "YES", then print ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804E/c0359cb82752ff2b028ccb729bac55ece58968d2.png) lines: the $ i $ -th of these lines should contain two integers $ a $ and $ b $ ( $ a&lt;b $ ) — the positions where the $ i $ -th swap is performed.

## 样例 #1

### 输入

```
3

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
1

```

### 输出

```
YES

```

