---
title: "Compatible Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF165E
tag: ['动态规划 DP', '枚举', '进制']
---

# Compatible Numbers

## 题目描述

Two integers $ x $ and $ y $ are compatible, if the result of their bitwise "AND" equals zero, that is, $ a $ $ & $ $ b=0 $ . For example, numbers $ 90 $ $ (1011010_{2}) $ and $ 36 $ $ (100100_{2}) $ are compatible, as $ 1011010_{2} $ $ & $ $ 100100_{2}=0_{2} $ , and numbers $ 3 $ $ (11_{2}) $ and $ 6 $ $ (110_{2}) $ are not compatible, as $ 11_{2} $ $ & $ $ 110_{2}=10_{2} $ .

You are given an array of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to find the following for each array element: is this element compatible with some other element from the given array? If the answer to this question is positive, then you also should find any suitable element.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ) — the number of elements in the given array. The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=4·10^{6} $ ) — the elements of the given array. The numbers in the array can coincide.

## 输出格式

Print $ n $ integers $ ans_{i} $ . If $ a_{i} $ isn't compatible with any other element of the given array $ a_{1},a_{2},...,a_{n} $ , then $ ans_{i} $ should be equal to -1. Otherwise $ ans_{i} $ is any such number, that $ a_{i} $ $ & $ $ ans_{i}=0 $ , and also $ ans_{i} $ occurs in the array $ a_{1},a_{2},...,a_{n} $ .

## 样例 #1

### 输入

```
2
90 36

```

### 输出

```
36 90
```

## 样例 #2

### 输入

```
4
3 6 3 6

```

### 输出

```
-1 -1 -1 -1
```

## 样例 #3

### 输入

```
5
10 6 9 8 2

```

### 输出

```
-1 8 2 2 8
```

