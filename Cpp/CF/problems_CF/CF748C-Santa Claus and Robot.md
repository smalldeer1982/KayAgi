---
title: "Santa Claus and Robot"
layout: "post"
diff: 普及/提高-
pid: CF748C
tag: []
---

# Santa Claus and Robot

## 题目描述

Santa Claus has Robot which lives on the infinite grid and can move along its lines. He can also, having a sequence of $ m $ points $ p_{1},p_{2},...,p_{m} $ with integer coordinates, do the following: denote its initial location by $ p_{0} $ . First, the robot will move from $ p_{0} $ to $ p_{1} $ along one of the shortest paths between them (please notice that since the robot moves only along the grid lines, there can be several shortest paths). Then, after it reaches $ p_{1} $ , it'll move to $ p_{2} $ , again, choosing one of the shortest ways, then to $ p_{3} $ , and so on, until he has visited all points in the given order. Some of the points in the sequence may coincide, in that case Robot will visit that point several times according to the sequence order.

While Santa was away, someone gave a sequence of points to Robot. This sequence is now lost, but Robot saved the protocol of its unit movements. Please, find the minimum possible length of the sequence.

## 输入格式

The first line of input contains the only positive integer $ n $ ( $ 1<=n<=2·10^{5} $ ) which equals the number of unit segments the robot traveled. The second line contains the movements protocol, which consists of $ n $ letters, each being equal either L, or R, or U, or D. $ k $ -th letter stands for the direction which Robot traveled the $ k $ -th unit segment in: L means that it moved to the left, R — to the right, U — to the top and D — to the bottom. Have a look at the illustrations for better explanation.

## 输出格式

The only line of input should contain the minimum possible length of the sequence.

## 说明/提示

The illustrations to the first three tests are given below.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748C/055feaa24aaf28c272b502eb1fa7804fe2ce0a51.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748C/795acf4da6085a8e5b976c179bfde9796711ae28.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF748C/75228340b2ee205f332e39cf435e438e28662e9d.png)

The last example illustrates that each point in the sequence should be counted as many times as it is presented in the sequence.

## 样例 #1

### 输入

```
4
RURD

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6
RRULDD

```

### 输出

```
2

```

## 样例 #3

### 输入

```
26
RRRULURURUULULLLDLDDRDRDLD

```

### 输出

```
7

```

## 样例 #4

### 输入

```
3
RLL

```

### 输出

```
2

```

## 样例 #5

### 输入

```
4
LRLR

```

### 输出

```
4

```

