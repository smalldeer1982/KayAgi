---
title: "Coin Troubles"
layout: "post"
diff: 省选/NOI-
pid: CF283C
tag: []
---

# Coin Troubles

## 题目描述

In the Isle of Guernsey there are $ n $ different types of coins. For each $ i $ $ (1<=i<=n) $ , coin of type $ i $ is worth $ a_{i} $ cents. It is possible that $ a_{i}=a_{j} $ for some $ i $ and $ j $ $ (i≠j) $ .

Bessie has some set of these coins totaling $ t $ cents. She tells Jessie $ q $ pairs of integers. For each $ i $ $ (1<=i<=q) $ , the pair $ b_{i},c_{i} $ tells Jessie that Bessie has a strictly greater number of coins of type $ b_{i} $ than coins of type $ c_{i} $ . It is known that all $ b_{i} $ are distinct and all $ c_{i} $ are distinct.

Help Jessie find the number of possible combinations of coins Bessie could have. Two combinations are considered different if there is some $ i $ $ (1<=i<=n) $ , such that the number of coins Bessie has of type $ i $ is different in the two combinations. Since the answer can be very large, output it modulo $ 1000000007 $ $ (10^{9}+7) $ .

If there are no possible combinations of coins totaling $ t $ cents that satisfy Bessie's conditions, output 0.

## 输入格式

The first line contains three space-separated integers, $ n,q $ and $ t $ $ (1<=n<=300; 0<=q<=n; 1<=t<=10^{5}) $ . The second line contains $ n $ space separated integers, $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{5}) $ . The next $ q $ lines each contain two distinct space-separated integers, $ b_{i} $ and $ c_{i} $ $ (1<=b_{i},c_{i}<=n; b_{i}≠c_{i}) $ .

It's guaranteed that all $ b_{i} $ are distinct and all $ c_{i} $ are distinct.

## 输出格式

A single integer, the number of valid coin combinations that Bessie could have, modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

For the first sample, the following 3 combinations give a total of 17 cents and satisfy the given conditions: $ {0 of type 1,1 of type 2,3 of type 3,2 of type 4},{0,0,6,1},{2,0,3,1} $ .

No other combinations exist. Note that even though 4 occurs in both $ b_{i} $ and $ c_{i}, $ the problem conditions are still satisfied because all $ b_{i} $ are distinct and all $ c_{i} $ are distinct.

## 样例 #1

### 输入

```
4 2 17
3 1 2 5
4 2
3 4

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 2 6
3 1 1
1 2
2 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 2 10
1 2 3
1 2
2 1

```

### 输出

```
0

```

