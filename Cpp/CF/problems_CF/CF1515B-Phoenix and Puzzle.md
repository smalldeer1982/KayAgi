---
title: "Phoenix and Puzzle"
layout: "post"
diff: 普及-
pid: CF1515B
tag: []
---

# Phoenix and Puzzle

## 题目描述

Phoenix is playing with a new puzzle, which consists of $ n $ identical puzzle pieces. Each puzzle piece is a right isosceles triangle as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/49a24f982b19e9535d6f30d4c91e443065d9fee9.png)A puzzle pieceThe goal of the puzzle is to create a square using the $ n $ pieces. He is allowed to rotate and move the pieces around, but none of them can overlap and all $ n $ pieces must be used (of course, the square shouldn't contain any holes as well). Can he do it?

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 10^9 $ ) — the number of puzzle pieces.

## 输出格式

For each test case, if Phoenix can create a square with the $ n $ puzzle pieces, print YES. Otherwise, print NO.

## 说明/提示

For $ n=2 $ , Phoenix can create a square like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/0fdfe011cd52355d3ad3123ce3848f97d63a78aa.png)For $ n=4 $ , Phoenix can create a square like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1515B/79f4dda31da05d0a22081f6d24d2a99d26f679bc.png)For $ n=6 $ , it is impossible for Phoenix to create a square.

## 样例 #1

### 输入

```
3
2
4
6
```

### 输出

```
YES
YES
NO
```

