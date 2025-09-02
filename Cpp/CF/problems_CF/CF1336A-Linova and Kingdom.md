---
title: "Linova and Kingdom"
layout: "post"
diff: 普及+/提高
pid: CF1336A
tag: []
---

# Linova and Kingdom

## 题目描述

Writing light novels is the most important thing in Linova's life. Last night, Linova dreamed about a fantastic kingdom. She began to write a light novel for the kingdom as soon as she woke up, and of course, she is the queen of it.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/776211708d76e2738717d34c412159f730c6de15.png)There are $ n $ cities and $ n-1 $ two-way roads connecting pairs of cities in the kingdom. From any city, you can reach any other city by walking through some roads. The cities are numbered from $ 1 $ to $ n $ , and the city $ 1 $ is the capital of the kingdom. So, the kingdom has a tree structure.

As the queen, Linova plans to choose exactly $ k $ cities developing industry, while the other cities will develop tourism. The capital also can be either industrial or tourism city.

A meeting is held in the capital once a year. To attend the meeting, each industry city sends an envoy. All envoys will follow the shortest path from the departure city to the capital (which is unique).

Traveling in tourism cities is pleasant. For each envoy, his happiness is equal to the number of tourism cities on his path.

In order to be a queen loved by people, Linova wants to choose $ k $ cities which can maximize the sum of happinesses of all envoys. Can you calculate the maximum sum for her?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2\le n\le 2 \cdot 10^5 $ , $ 1\le k< n $ ) — the number of cities and industry cities respectively.

Each of the next $ n-1 $ lines contains two integers $ u $ and $ v $ ( $ 1\le u,v\le n $ ), denoting there is a road connecting city $ u $ and city $ v $ .

It is guaranteed that from any city, you can reach any other city by the roads.

## 输出格式

Print the only line containing a single integer — the maximum possible sum of happinesses of all envoys.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/550bbb250626ee83a75f7874e99bb74967e95572.png)

In the first example, Linova can choose cities $ 2 $ , $ 5 $ , $ 6 $ , $ 7 $ to develop industry, then the happiness of the envoy from city $ 2 $ is $ 1 $ , the happiness of envoys from cities $ 5 $ , $ 6 $ , $ 7 $ is $ 2 $ . The sum of happinesses is $ 7 $ , and it can be proved to be the maximum one.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336A/42ded7a124702f40fc5538e5ca404a7c3df59128.png)

In the second example, choosing cities $ 3 $ , $ 4 $ developing industry can reach a sum of $ 3 $ , but remember that Linova plans to choose exactly $ k $ cities developing industry, then the maximum sum is $ 2 $ .

## 样例 #1

### 输入

```
7 4
1 2
1 3
1 4
3 5
3 6
4 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 1
1 2
1 3
2 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
8 5
7 5
1 7
6 1
3 7
8 3
2 1
4 5
```

### 输出

```
9
```

