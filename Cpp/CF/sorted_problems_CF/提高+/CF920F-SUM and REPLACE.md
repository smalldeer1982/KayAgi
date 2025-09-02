---
title: "SUM and REPLACE"
layout: "post"
diff: 提高+/省选-
pid: CF920F
tag: ['线段树', '递归', '分块']
---

# SUM and REPLACE

## 题目描述

Let $ D(x) $ be the number of positive divisors of a positive integer $ x $ . For example, $ D(2)=2 $ ( $ 2 $ is divisible by $ 1 $ and $ 2 $ ), $ D(6)=4 $ ( $ 6 $ is divisible by $ 1 $ , $ 2 $ , $ 3 $ and $ 6 $ ).

You are given an array $ a $ of $ n $ integers. You have to process two types of queries:

1. REPLACE $ l $ $ r $ — for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/8c67e39bbb4a436ecb9bbf84b28c1b332f05ca94.png) replace $ a_{i} $ with $ D(a_{i}) $ ;
2. SUM $ l $ $ r $ — calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/1deabb69ce88e0c9a5b8e5232e5782460ccfe87b.png).

Print the answer for each SUM query.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=3·10^{5} $ ) — the number of elements in the array and the number of queries to process, respectively.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{6} $ ) — the elements of the array.

Then $ m $ lines follow, each containing $ 3 $ integers $ t_{i} $ , $ l_{i} $ , $ r_{i} $ denoting $ i $ -th query. If $ t_{i}=1 $ , then $ i $ -th query is REPLACE $ l_{i} $ $ r_{i} $ , otherwise it's SUM $ l_{i} $ $ r_{i} $ ( $ 1<=t_{i}<=2 $ , $ 1<=l_{i}<=r_{i}<=n $ ).

There is at least one SUM query.

## 输出格式

For each SUM query print the answer to it.

## 样例 #1

### 输入

```
7 6
6 4 1 10 3 2 4
2 1 7
2 4 5
1 3 5
2 4 4
1 5 7
2 1 7

```

### 输出

```
30
13
4
22

```

