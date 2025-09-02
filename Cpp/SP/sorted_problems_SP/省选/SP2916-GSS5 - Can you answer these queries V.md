---
title: "GSS5 - Can you answer these queries V"
layout: "post"
diff: 省选/NOI-
pid: SP2916
tag: ['线段树', '前缀和']
---

# GSS5 - Can you answer these queries V

## 题目描述

 You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| <= 10000 , 1 <= N <= 10000 ). A query is defined as follows: Query(x1,y1,x2,y2) = Max { A\[i\]+A\[i+1\]+...+A\[j\] ; x1 <= i <= y1 , x2 <= j <= y2 and x1 <= x2 , y1 <= y2 }. Given M queries (1 <= M <= 10000), your program must output the results of these queries.

## 输入格式

 The first line of the input consist of the number of tests cases <= 5. Each case consist of the integer N and the sequence A. Then the integer M. M lines follow, contains 4 numbers x1, y1, x2 y2.

## 输出格式

 Your program should output the results of the M queries for each test case, one query per line.

## 样例 #1

### 输入

```
2
6 3 -2 1 -4 5 2
2
1 1 2 3
1 3 2 5
1 1
1
1 1 1 1
```

### 输出

```
2
3
1
```

