---
title: "A Problem about Polyline"
layout: "post"
diff: 普及/提高-
pid: CF578A
tag: ['数学']
---

# A Problem about Polyline

## 题目描述

There is a polyline going through points $ (0,0)–(x,x)–(2x,0)–(3x,x)–(4x,0)–...-(2kx,0)–(2kx+x,x)–... $ .

We know that the polyline passes through the point $ (a,b) $ . Find minimum positive value $ x $ such that it is true or determine that there is no such $ x $ .

## 输入格式

Only one line containing two positive integers $ a $ and $ b $ ( $ 1<=a,b<=10^{9} $ ).

## 输出格式

Output the only line containing the answer. Your answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-9} $ . If there is no such $ x $ then output $ -1 $ as the answer.

## 说明/提示

You can see following graphs for sample 1 and sample 3.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578A/abf33c2e979ad11f626e45babf5d2a8a224a3964.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF578A/567201d8db120e4f8136d5be265b91eca027e0d4.png)

## 样例 #1

### 输入

```
3 1

```

### 输出

```
1.000000000000

```

## 样例 #2

### 输入

```
1 3

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
4 1

```

### 输出

```
1.250000000000

```

