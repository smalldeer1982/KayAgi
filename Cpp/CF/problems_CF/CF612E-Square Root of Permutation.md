---
title: "Square Root of Permutation"
layout: "post"
diff: 省选/NOI-
pid: CF612E
tag: []
---

# Square Root of Permutation

## 题目描述

A permutation of length $ n $ is an array containing each integer from $ 1 $ to $ n $ exactly once. For example, $ q=[4,5,1,2,3] $ is a permutation. For the permutation $ q $ the square of permutation is the permutation $ p $ that $ p[i]=q[q[i]] $ for each $ i=1...\ n $ . For example, the square of $ q=[4,5,1,2,3] $ is $ p=q^{2}=[2,3,4,5,1] $ .

This problem is about the inverse operation: given the permutation $ p $ you task is to find such permutation $ q $ that $ q^{2}=p $ . If there are several such $ q $ find any of them.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{6} $ ) — the number of elements in permutation $ p $ .

The second line contains $ n $ distinct integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — the elements of permutation $ p $ .

## 输出格式

If there is no permutation $ q $ such that $ q^{2}=p $ print the number "-1".

If the answer exists print it. The only line should contain $ n $ different integers $ q_{i} $ ( $ 1<=q_{i}<=n $ ) — the elements of the permutation $ q $ . If there are several solutions print any of them.

## 样例 #1

### 输入

```
4
2 1 4 3

```

### 输出

```
3 4 2 1

```

## 样例 #2

### 输入

```
4
2 1 3 4

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
5
2 3 4 5 1

```

### 输出

```
4 5 1 2 3

```

