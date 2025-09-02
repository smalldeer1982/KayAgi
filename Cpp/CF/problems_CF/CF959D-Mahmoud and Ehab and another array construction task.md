---
title: "Mahmoud and Ehab and another array construction task"
layout: "post"
diff: 提高+/省选-
pid: CF959D
tag: ['枚举', '素数判断,质数,筛法']
---

# Mahmoud and Ehab and another array construction task

## 题目描述

Mahmoud has an array $ a $ consisting of $ n $ integers. He asked Ehab to find another array $ b $ of the same length such that:

- $ b $ is lexicographically greater than or equal to $ a $ .
- $ b_{i}>=2 $ .
- $ b $ is pairwise coprime: for every $ 1<=i<j<=n $ , $ b_{i} $ and $ b_{j} $ are coprime, i. e. $ GCD(b_{i},b_{j})=1 $ , where $ GCD(w,z) $ is the greatest common divisor of $ w $ and $ z $ .

Ehab wants to choose a special array so he wants the lexicographically minimal array between all the variants. Can you find it?

An array $ x $ is lexicographically greater than an array $ y $ if there exists an index $ i $ such than $ x_{i}>y_{i} $ and $ x_{j}=y_{j} $ for all $ 1<=j<i $ . An array $ x $ is equal to an array $ y $ if $ x_{i}=y_{i} $ for all $ 1<=i<=n $ .

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=10^{5}) $ , the number of elements in $ a $ and $ b $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ $ (2<=a_{i}<=10^{5}) $ , the elements of $ a $ .

## 输出格式

Output $ n $ space-separated integers, the $ i $ -th of them representing $ b_{i} $ .

## 说明/提示

Note that in the second sample, the array is already pairwise coprime so we printed it.

## 样例 #1

### 输入

```
5
2 3 5 4 13

```

### 输出

```
2 3 5 7 11 
```

## 样例 #2

### 输入

```
3
10 3 7

```

### 输出

```
10 3 7 
```

