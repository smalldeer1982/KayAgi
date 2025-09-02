---
title: "Matvey's Birthday"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF718E
tag: ['枚举', '最短路', '进制']
---

# Matvey's Birthday

## 题目描述

Today is Matvey's birthday. He never knows what to ask as a present so friends gave him a string $ s $ of length $ n $ . This string consists of only first eight English letters: 'a', 'b', $ ... $ , 'h'.

First question that comes to mind is: who might ever need some string? Matvey is a special boy so he instantly found what to do with this string. He used it to build an undirected graph where vertices correspond to position in the string and there is an edge between distinct positions $ a $ and $ b $ ( $ 1<=a,b<=n $ ) if at least one of the following conditions hold:

1. $ a $ and $ b $ are neighbouring, i.e. $ |a-b|=1 $ .
2. Positions $ a $ and $ b $ contain equal characters, i.e. $ s_{a}=s_{b} $ .

Then Matvey decided to find the diameter of this graph. Diameter is a maximum distance (length of the shortest path) among all pairs of vertices. Also, Matvey wants to find the number of pairs of vertices such that the distance between them is equal to the diameter of the graph. As he is very cool and experienced programmer he managed to solve this problem very fast. Will you do the same?

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the length of the string.

The second line contains the string $ s $ itself. It's guaranteed that $ s $ consists of only first eight letters of English alphabet.

## 输出格式

Print two integers — the diameter of the graph and the number of pairs of positions with the distance equal to the diameter.

## 说明/提示

Consider the second sample.

The maximum distance is $ 2 $ . It's obtained for pairs $ (1,4) $ , $ (2,4) $ , $ (4,6) $ and $ (4,7) $ .

## 样例 #1

### 输入

```
3
abc

```

### 输出

```
2 1

```

## 样例 #2

### 输入

```
7
aaabaaa

```

### 输出

```
2 4

```

