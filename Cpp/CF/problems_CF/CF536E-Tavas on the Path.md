---
title: "Tavas on the Path"
layout: "post"
diff: 省选/NOI-
pid: CF536E
tag: []
---

# Tavas on the Path

## 题目描述

Tavas lives in Tavaspolis. Tavaspolis has $ n $ cities numbered from $ 1 $ to $ n $ connected by $ n-1 $ bidirectional roads. There exists a path between any two cities. Also each road has a length.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF536E/d3484f8e760e70be37b15d454f75fce51db0bf40.png)Tavas' favorite strings are binary strings (they contain only 0 and 1). For any binary string like $ s=s_{1}s_{2}...\ s_{k} $ , $ T(s) $ is its $ Goodness $ . $ T(s) $ can be calculated as follows:

Consider there are exactly $ m $ blocks of $ 1 $ s in this string (a block of $ 1 $ s in $ s $ is a maximal consecutive substring of $ s $ that only contains $ 1 $ ) with lengths $ x_{1},x_{2},...,x_{m} $ .

Define ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF536E/355506c834e033a7323a71320e8c5f755ccad647.png) where $ f $ is a given sequence (if $ m=0 $ , then $ T(s)=0 $ ).

Tavas loves queries. He asks you to answer $ q $ queries. In each query he gives you numbers $ v,u,l $ and you should print following number:

Consider the roads on the path from city $ v $ to city $ u $ : $ e_{1},e_{2},...,e_{x} $ .

Build the binary string $ b $ of length $ x $ such that: $ b_{i}=1 $ if and only if $ l<=w(e_{i}) $ where $ w(e) $ is the length of road $ e $ .

You should print $ T(b) $ for this query.

## 输入格式

The first line of input contains integers $ n $ and $ q $ ( $ 2<=n<=10^{5} $ and $ 1<=q<=10^{5} $ ).

The next line contains $ n-1 $ space separated integers $ f_{1},f_{2},...,f_{n-1} $ ( $ |f_{i}|<=1000 $ ).

The next $ n-1 $ lines contain the details of the roads. Each line contains integers $ v,u $ and $ w $ and it means that there's a road between cities $ v $ and $ u $ of length $ w $ ( $ 1<=v,u<=n $ and $ 1<=w<=10^{9} $ ).

The next $ q $ lines contain the details of the queries. Each line contains integers $ v,u,l $ ( $ 1<=v,u<=n $ , $ v≠u $ and $ 1<=l<=10^{9} $ ).

## 输出格式

Print the answer of each query in a single line.

## 样例 #1

### 输入

```
2 3
10
1 2 3
1 2 2
1 2 3
1 2 4

```

### 输出

```
10
10
0

```

## 样例 #2

### 输入

```
6 6
-5 0 0 2 10
1 2 1
2 3 2
3 4 5
4 5 1
5 6 5
1 6 1
1 6 2
1 6 5
3 6 5
4 6 4
1 4 2

```

### 输出

```
10
-5
-10
-10
-5
0

```

