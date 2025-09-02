---
title: "Sereja and Array"
layout: "post"
diff: 普及-
pid: CF315B
tag: []
---

# Sereja and Array

## 题目描述

Sereja has got an array, consisting of $ n $ integers, $ a_{1},a_{2},...,a_{n} $ . Sereja is an active boy, so he is now going to complete $ m $ operations. Each operation will have one of the three forms:

1. Make $ v_{i} $ -th array element equal to $ x_{i} $ . In other words, perform the assignment $ a_{vi}=x_{i} $ .
2. Increase each array element by $ y_{i} $ . In other words, perform $ n $ assignments $ a_{i}=a_{i}+y_{i} $ $ (1<=i<=n) $ .
3. Take a piece of paper and write out the $ q_{i} $ -th array element. That is, the element $ a_{qi} $ .

Help Sereja, complete all his operations.

## 输入格式

The first line contains integers $ n $ , $ m $ $ (1<=n,m<=10^{5}) $ . The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ — the original array.

Next $ m $ lines describe operations, the $ i $ -th line describes the $ i $ -th operation. The first number in the $ i $ -th line is integer $ t_{i} $ $ (1<=t_{i}<=3) $ that represents the operation type. If $ t_{i}=1 $ , then it is followed by two integers $ v_{i} $ and $ x_{i} $ , $ (1<=v_{i}<=n,1<=x_{i}<=10^{9}) $ . If $ t_{i}=2 $ , then it is followed by integer $ y_{i} $ $ (1<=y_{i}<=10^{4}) $ . And if $ t_{i}=3 $ , then it is followed by integer $ q_{i} $ $ (1<=q_{i}<=n) $ .

## 输出格式

For each third type operation print value $ a_{qi} $ . Print the values in the order, in which the corresponding queries follow in the input.

## 样例 #1

### 输入

```
10 11
1 2 3 4 5 6 7 8 9 10
3 2
3 9
2 10
3 1
3 10
1 1 10
2 10
2 10
3 1
3 10
3 9

```

### 输出

```
2
9
11
20
30
40
39

```

