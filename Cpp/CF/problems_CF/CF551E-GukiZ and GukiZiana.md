---
title: "GukiZ and GukiZiana"
layout: "post"
diff: 省选/NOI-
pid: CF551E
tag: []
---

# GukiZ and GukiZiana

## 题目描述

Professor GukiZ was playing with arrays again and accidentally discovered new function, which he called $ GukiZiana $ . For given array $ a $ , indexed with integers from $ 1 $ to $ n $ , and number $ y $ , $ GukiZiana(a,y) $ represents maximum value of $ j-i $ , such that $ a_{j}=a_{i}=y $ . If there is no $ y $ as an element in $ a $ , then $ GukiZiana(a,y) $ is equal to $ -1 $ . GukiZ also prepared a problem for you. This time, you have two types of queries:

1. First type has form $ 1 $ $ l $ $ r $ $ x $ and asks you to increase values of all $ a_{i} $ such that $ l<=i<=r $ by the non-negative integer $ x $ .
2. Second type has form $ 2 $ $ y $ and asks you to find value of $ GukiZiana(a,y) $ .

For each query of type $ 2 $ , print the answer and make GukiZ happy!

## 输入格式

The first line contains two integers $ n $ , $ q $ ( $ 1<=n<=5*10^{5},1<=q<=5*10^{4} $ ), size of array $ a $ , and the number of queries.

The second line contains $ n $ integers $ a_{1},a_{2},...\ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ), forming an array $ a $ .

Each of next $ q $ lines contain either four or two numbers, as described in statement:

If line starts with $ 1 $ , then the query looks like $ 1 $ $ l $ $ r $ $ x $ ( $ 1<=l<=r<=n $ , $ 0<=x<=10^{9} $ ), first type query.

If line starts with $ 2 $ , then th query looks like $ 2 $ $ y $ ( $ 1<=y<=10^{9} $ ), second type query.

## 输出格式

For each query of type $ 2 $ , print the value of $ GukiZiana(a,y) $ , for $ y $ value for that query.

## 样例 #1

### 输入

```
4 3
1 2 3 4
1 1 2 1
1 1 1 1
2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 3
1 2
1 2 2 1
2 3
2 4

```

### 输出

```
0
-1

```

