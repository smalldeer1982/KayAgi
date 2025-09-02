---
title: "Levko and Array Recovery"
layout: "post"
diff: 普及+/提高
pid: CF360A
tag: []
---

# Levko and Array Recovery

## 题目描述

Levko loves array $ a_{1},a_{2},...\ ,a_{n} $ , consisting of integers, very much. That is why Levko is playing with array $ a $ , performing all sorts of operations with it. Each operation Levko performs is of one of two types:

1. Increase all elements from $ l_{i} $ to $ r_{i} $ by $ d_{i} $ . In other words, perform assignments $ a_{j}=a_{j}+d_{i} $ for all $ j $ that meet the inequation $ l_{i}<=j<=r_{i} $ .
2. Find the maximum of elements from $ l_{i} $ to $ r_{i} $ . That is, calculate the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF360A/b8abcd9e917cd04eb743a84b9d9be23896e61fc8.png).

Sadly, Levko has recently lost his array. Fortunately, Levko has records of all operations he has performed on array $ a $ . Help Levko, given the operation records, find at least one suitable array. The results of all operations for the given array must coincide with the record results. Levko clearly remembers that all numbers in his array didn't exceed $ 10^{9} $ in their absolute value, so he asks you to find such an array.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=5000 $ ) — the size of the array and the number of operations in Levko's records, correspondingly.

Next $ m $ lines describe the operations, the $ i $ -th line describes the $ i $ -th operation. The first integer in the $ i $ -th line is integer $ t_{i} $ ( $ 1<=t_{i}<=2 $ ) that describes the operation type. If $ t_{i}=1 $ , then it is followed by three integers $ l_{i} $ , $ r_{i} $ and $ d_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ , $ -10^{4}<=d_{i}<=10^{4} $ ) — the description of the operation of the first type. If $ t_{i}=2 $ , then it is followed by three integers $ l_{i} $ , $ r_{i} $ and $ m_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ , $ -5·10^{7}<=m_{i}<=5·10^{7} $ ) — the description of the operation of the second type.

The operations are given in the order Levko performed them on his array.

## 输出格式

In the first line print "YES" (without the quotes), if the solution exists and "NO" (without the quotes) otherwise.

If the solution exists, then on the second line print $ n $ integers $ a_{1},a_{2},...\ ,a_{n} $ $ (|a_{i}|<=10^{9}) $ — the recovered array.

## 样例 #1

### 输入

```
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 8

```

### 输出

```
YES
4 7 4 7
```

## 样例 #2

### 输入

```
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 13

```

### 输出

```
NO

```

