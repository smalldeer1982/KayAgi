---
title: "Restoring Painting"
layout: "post"
diff: 普及/提高-
pid: CF675B
tag: []
---

# Restoring Painting

## 题目描述

有一个九宫格，每个格子的值都在 $[1,n]$ 的区间内，现给出它上下左右四格的值，要求每一个 $2\times2$ 的方格的总和都相等，请你求出共有多少种填法。如果 $2\times2$ 格子的总和等于 $0$ ，则表示有数据被记错了。如果在不同的 $2\times2$ 的方格中包含两个不同的整数，则认为两个 $2\times2$ 的方格是不同的。

## 输入格式

一行，包含五个整数 $n$​​ ， $a$​​ ， $b$​​ ， $c$​​ 和 $d$​​ ( $1\le n\le 10^5$​​ , $1\le a,b,c,d\le n$​​​​ ) 。

## 输出格式

仅输出一个整数，表示填法的总数。

#### 样例解释：

样例1的两种方法如下： ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675B/025712069c9acbad081f2181d643827812c11163.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675B/9c464a7a8882ec5f9c7ca829fee67b297c3e5020.png)



样例2的六种方法如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675B/7027b6797b21d7224ee05ecd06a48452b2615498.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675B/098b5c120bcba03cb9e9e25703ed8cdcb8287d14.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675B/f60f2764919fa6766e9514333bfdbe0c808da67e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675B/11c0404b15c724e758635e9735d5c11cc4dbb178.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675B/9a488180531c0a7b3a83207a0b69b8c29e912592.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF675B/a75f8263ae2d6282b2410ef6a0c052f9244b963c.png)

## 样例 #1

### 输入

```
2 1 1 1 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 3 1 2 3

```

### 输出

```
6

```

