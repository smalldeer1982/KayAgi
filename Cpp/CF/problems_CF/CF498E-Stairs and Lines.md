---
title: "Stairs and Lines"
layout: "post"
diff: 省选/NOI-
pid: CF498E
tag: []
---

# Stairs and Lines

## 题目描述

You are given a figure on a grid representing stairs consisting of 7 steps. The width of the stair on height $ i $ is $ w_{i} $ squares. Formally, the figure is created by consecutively joining rectangles of size $ w_{i}×i $ so that the $ w_{i} $ sides lie on one straight line. Thus, for example, if all $ w_{i}=1 $ , the figure will look like that (different colors represent different rectangles):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF498E/c6fb7071f303e3a83e13342e5c3149c16ebc124c.png)And if $ w={5,1,0,3,0,0,1} $ , then it looks like that:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF498E/81e637747a334268bc5ee9870a6a97e0703d91ae.png)Find the number of ways to color some borders of the figure's inner squares so that no square had all four borders colored. The borders of the squares lying on the border of the figure should be considered painted. The ways that differ with the figure's rotation should be considered distinct.

## 输入格式

The single line of the input contains 7 numbers $ w_{1},w_{2},...,w_{7} $ ( $ 0<=w_{i}<=10^{5} $ ). It is guaranteed that at least one of the $ w_{i} $ 's isn't equal to zero.

## 输出格式

In the single line of the output display a single number — the answer to the problem modulo $ 10^{9}+7 $ .

## 说明/提示

All the possible ways of painting the third sample are given below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF498E/c78e55a2090821d569ec77d319a0ea4d99457273.png)

## 样例 #1

### 输入

```
0 1 0 0 0 0 0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
0 2 0 0 0 0 0

```

### 输出

```
7

```

## 样例 #3

### 输入

```
1 1 1 0 0 0 0

```

### 输出

```
9

```

## 样例 #4

### 输入

```
5 1 0 3 0 0 1

```

### 输出

```
411199181

```

