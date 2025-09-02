---
title: "Curious Array"
layout: "post"
diff: 省选/NOI-
pid: CF407C
tag: []
---

# Curious Array

## 题目描述

You've got an array consisting of $ n $ integers: $ a[1],a[2],...,a[n] $ . Moreover, there are $ m $ queries, each query can be described by three integers $ l_{i},r_{i},k_{i} $ . Query $ l_{i},r_{i},k_{i} $ means that we should add ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF407C/7483b5d05694b4cb36893b9ef3b5ea6eca980e53.png) to each element $ a[j] $ , where $ l_{i}<=j<=r_{i} $ .

Record ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF407C/e80c4b14815086b581d3057ceea9005fcac2476e.png) means the binomial coefficient, or the number of combinations from $ y $ elements into groups of $ x $ elements.

You need to fulfil consecutively all queries and then print the final array.

## 输入格式

The first line contains integers $ n $ , $ m $ ( $ 1<=n,m<=10^{5} $ ).

The second line contains $ n $ integers $ a[1],a[2],...,a[n] $ ( $ 0<=a_{i}<=10^{9} $ ) — the initial array.

Next $ m $ lines contain queries in the format $ l_{i},r_{i},k_{i} $ — to all elements of the segment $ l_{i}...\ r_{i} $ add number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF407C/7483b5d05694b4cb36893b9ef3b5ea6eca980e53.png) ( $ 1<=l_{i}<=r_{i}<=n $ ; $ 0<=k<=100 $ ).

## 输出格式

Print $ n $ integers: the $ i $ -th number is the value of element $ a[i] $ after all the queries. As the values can be rather large, print them modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
5 1
0 0 0 0 0
1 5 0

```

### 输出

```
1 1 1 1 1

```

## 样例 #2

### 输入

```
10 2
1 2 3 4 5 0 0 0 0 0
1 6 1
6 10 2

```

### 输出

```
2 4 6 8 10 7 3 6 10 15

```

