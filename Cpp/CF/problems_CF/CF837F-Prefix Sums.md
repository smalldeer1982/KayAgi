---
title: "Prefix Sums"
layout: "post"
diff: 提高+/省选-
pid: CF837F
tag: []
---

# Prefix Sums

## 题目描述

Consider the function $ p(x) $ , where $ x $ is an array of $ m $ integers, which returns an array $ y $ consisting of $ m+1 $ integers such that $ y_{i} $ is equal to the sum of first $ i $ elements of array $ x $ ( $ 0<=i<=m $ ).

You have an infinite sequence of arrays $ A^{0},A^{1},A^{2}... $ , where $ A^{0} $ is given in the input, and for each $ i>=1 $ $ A^{i}=p(A^{i-1}) $ . Also you have a positive integer $ k $ . You have to find minimum possible $ i $ such that $ A^{i} $ contains a number which is larger or equal than $ k $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2<=n<=200000 $ , $ 1<=k<=10^{18} $ ). $ n $ is the size of array $ A^{0} $ .

The second line contains $ n $ integers $ A^{0}_{0},A^{0}_{1}...\ A^{0}_{n-1} $ — the elements of $ A^{0} $ ( $ 0<=A^{0}_{i}<=10^{9} $ ). At least two elements of $ A^{0} $ are positive.

## 输出格式

Print the minimum $ i $ such that $ A^{i} $ contains a number which is larger or equal than $ k $ .

## 样例 #1

### 输入

```
2 2
1 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 6
1 1 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 1
1 0 1

```

### 输出

```
0

```

