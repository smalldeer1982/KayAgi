---
title: "GSS1 - Can you answer these queries I"
layout: "post"
diff: 提高+/省选-
pid: SP1043
tag: ['线段树', '分治', '前缀和']
---

# GSS1 - Can you answer these queries I

## 题目描述

You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:   
 Query(x,y) = Max { a\[i\]+a\[i+1\]+...+a\[j\] ; x ≤ i ≤ j ≤ y }.   
 Given M queries, your program must output the results of these queries.

## 输入格式

- The first line of the input file contains the integer N.
- In the second line, N numbers follow.
- The third line contains the integer M.
- M lines follow, where line i contains 2 numbers xi and yi.

## 输出格式

 Your program should output the results of the M queries, one query per line.

## 样例 #1

### 输入

```
3 
-1 2 3
1
1 2
```

### 输出

```
2
```

