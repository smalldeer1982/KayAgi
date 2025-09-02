---
title: "DZY Loves Fibonacci Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF446C
tag: ['数学', '线段树', '斐波那契数列']
---

# DZY Loves Fibonacci Numbers

## 题目描述

In mathematical terms, the sequence $ F_{n} $ of Fibonacci numbers is defined by the recurrence relation

 $ F_{1}=1; F_{2}=1; F_{n}=F_{n-1}+F_{n-2} (n>2). $ DZY loves Fibonacci numbers very much. Today DZY gives you an array consisting of $ n $ integers: $ a_{1},a_{2},...,a_{n} $ . Moreover, there are $ m $ queries, each query has one of the two types:

1. Format of the query " $ 1\ l\ r $ ". In reply to the query, you need to add $ F_{i-l+1} $ to each element $ a_{i} $ , where $ l<=i<=r $ .
2. Format of the query " $ 2\ l\ r $ ". In reply to the query you should output the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF446C/9b1c73158dd7a4166f7d8fde16bb75f36899bc0e.png) modulo $ 1000000009 (10^{9}+9) $ .

Help DZY reply to all the queries.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=300000 $ ). The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} (1<=a_{i}<=10^{9}) $ — initial array $ a $ .

Then, $ m $ lines follow. A single line describes a single query in the format given in the statement. It is guaranteed that for each query inequality $ 1<=l<=r<=n $ holds.

## 输出格式

For each query of the second type, print the value of the sum on a single line.

## 说明/提示

After the first query, $ a=[2,3,5,7] $ .

For the second query, $ sum=2+3+5+7=17 $ .

After the third query, $ a=[2,4,6,9] $ .

For the fourth query, $ sum=2+4+6=12 $ .

## 样例 #1

### 输入

```
4 4
1 2 3 4
1 1 4
2 1 4
1 2 4
2 1 3

```

### 输出

```
17
12

```

