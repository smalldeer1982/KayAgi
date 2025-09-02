---
title: "XOR and Favorite Number"
layout: "post"
diff: 提高+/省选-
pid: CF617E
tag: ['莫队']
---

# XOR and Favorite Number

## 题目描述

Bob has a favorite number $ k $ and $ a_{i} $ of length $ n $ . Now he asks you to answer $ m $ queries. Each query is given by a pair $ l_{i} $ and $ r_{i} $ and asks you to count the number of pairs of integers $ i $ and $ j $ , such that $ l<=i<=j<=r $ and the xor of the numbers $ a_{i},a_{i+1},...,a_{j} $ is equal to $ k $ .

## 输入格式

The first line of the input contains integers $ n $ , $ m $ and $ k $ ( $ 1<=n,m<=100000 $ , $ 0<=k<=1000000 $ ) — the length of the array, the number of queries and Bob's favorite number respectively.

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=1000000 $ ) — Bob's array.

Then $ m $ lines follow. The $ i $ -th line contains integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) — the parameters of the $ i $ -th query.

## 输出格式

Print $ m $ lines, answer the queries in the order they appear in the input.

## 说明/提示

In the first sample the suitable pairs of $ i $ and $ j $ for the first query are: ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 3 $ ), ( $ 3 $ , $ 6 $ ), ( $ 5 $ , $ 6 $ ), ( $ 6 $ , $ 6 $ ). Not a single of these pairs is suitable for the second query.

In the second sample xor equals $ 1 $ for all subarrays of an odd length.

## 样例 #1

### 输入

```
6 2 3
1 2 1 1 0 3
1 6
3 5

```

### 输出

```
7
0

```

## 样例 #2

### 输入

```
5 3 1
1 1 1 1 1
1 5
2 4
1 3

```

### 输出

```
9
4
4

```

