---
title: "Inversions After Shuffle"
layout: "post"
diff: 省选/NOI-
pid: CF749E
tag: ['树状数组', '枚举', '期望']
---

# Inversions After Shuffle

## 题目描述

You are given a permutation of integers from $ 1 $ to $ n $ . Exactly once you apply the following operation to this permutation: pick a random segment and shuffle its elements. Formally:

1. Pick a random segment (continuous subsequence) from $ l $ to $ r $ . All ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF749E/150441d31156a32e0b2da63844d600138a543898.png) segments are equiprobable.
2. Let $ k=r-l+1 $ , i.e. the length of the chosen segment. Pick a random permutation of integers from $ 1 $ to $ k $ , $ p_{1},p_{2},...,p_{k} $ . All $ k! $ permutation are equiprobable.
3. This permutation is applied to elements of the chosen segment, i.e. permutation $ a_{1},a_{2},...,a_{l-1},a_{l},a_{l+1},...,a_{r-1},a_{r},a_{r+1},...,a_{n} $ is transformed to $ a_{1},a_{2},...,a_{l-1},a_{l-1+p1},a_{l-1+p2},...,a_{l-1+pk-1},a_{l-1+pk},a_{r+1},...,a_{n} $ .

Inversion if a pair of elements (not necessary neighbouring) with the wrong relative order. In other words, the number of inversion is equal to the number of pairs $ (i,j) $ such that $ i&lt;j $ and $ a_{i}&gt;a_{j} $ . Find the expected number of inversions after we apply exactly one operation mentioned above.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100000 $ ) — the length of the permutation.

The second line contains $ n $ distinct integers from $ 1 $ to $ n $ — elements of the permutation.

## 输出格式

Print one real value — the expected number of inversions. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-9} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF749E/d8d110e69d298146d951837cc2710d1c4cc74a7d.png).

## 样例 #1

### 输入

```
3
2 3 1

```

### 输出

```
1.916666666666666666666666666667

```

