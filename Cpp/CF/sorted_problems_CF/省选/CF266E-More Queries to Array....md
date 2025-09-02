---
title: "More Queries to Array..."
layout: "post"
diff: 省选/NOI-
pid: CF266E
tag: []
---

# More Queries to Array...

## 题目描述

You've got an array, consisting of $ n $ integers: $ a_{1},a_{2},...,a_{n} $ . Your task is to quickly run the queries of two types:

1. Assign value $ x $ to all elements from $ l $ to $ r $ inclusive. After such query the values of the elements of array $ a_{l},a_{l+1},...,a_{r} $ become equal to $ x $ .
2. Calculate and print sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF266E/633cb60e7d18ebc2282c71be46423585a8ce8f27.png), where $ k $ doesn't exceed $ 5 $ . As the value of the sum can be rather large, you should print it modulo $ 1000000007 (10^{9}+7) $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{5} $ ), showing, how many numbers are in the array and the number of queries, correspondingly. The second line contains $ n $ integers: $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{9} $ ) — the initial values of the array elements.

Then $ m $ queries follow, one per line:

1. The assign query has the following format: "![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF266E/5ec940bc32a3f231927e5e6ffbf9e249f67270e1.png)", ( $ 1<=l<=r<=n; 0<=x<=10^{9} $ ).
2. The query to calculate the sum has the following format: "![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF266E/1b593b7fe3d54e009840a9a4e6255ed5f3242b14.png)", ( $ 1<=l<=r<=n; 0<=k<=5 $ ).

All numbers in the input are integers.

## 输出格式

For each query to calculate the sum print an integer — the required sum modulo $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
4 5
5 10 2 1
? 1 2 1
= 2 2 0
? 2 4 3
= 1 4 1
? 1 4 5

```

### 输出

```
25
43
1300

```

## 样例 #2

### 输入

```
3 1
1000000000 1000000000 1000000000
? 1 3 0

```

### 输出

```
999999986

```

