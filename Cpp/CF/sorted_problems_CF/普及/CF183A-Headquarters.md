---
title: "Headquarters"
layout: "post"
diff: 普及/提高-
pid: CF183A
tag: []
---

# Headquarters

## 题目描述

Sensation, sensation in the two-dimensional kingdom! The police have caught a highly dangerous outlaw, member of the notorious "Pihters" gang. The law department states that the outlaw was driving from the gang's headquarters in his car when he crashed into an ice cream stall. The stall, the car, and the headquarters each occupies exactly one point on the two-dimensional kingdom.

The outlaw's car was equipped with a GPS transmitter. The transmitter showed that the car made exactly $ n $ movements on its way from the headquarters to the stall. A movement can move the car from point $ (x,y) $ to one of these four points: to point $ (x-1,y) $ which we will mark by letter "L", to point $ (x+1,y) $ — "R", to point $ (x,y-1) $ — "D", to point $ (x,y+1) $ — "U".

The GPS transmitter is very inaccurate and it doesn't preserve the exact sequence of the car's movements. Instead, it keeps records of the car's possible movements. Each record is a string of one of these types: "UL", "UR", "DL", "DR" or "ULDR". Each such string means that the car made a single movement corresponding to one of the characters of the string. For example, string "UL" means that the car moved either "U", or "L".

You've received the journal with the outlaw's possible movements from the headquarters to the stall. The journal records are given in a chronological order. Given that the ice-cream stall is located at point $ (0,0) $ , your task is to print the number of different points that can contain the gang headquarters (that is, the number of different possible locations of the car's origin).

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=2·10^{5}) $ — the number of the car's movements from the headquarters to the stall.

Each of the following $ n $ lines describes the car's possible movements. It is guaranteed that each possible movement is one of the following strings: "UL", "UR", "DL", "DR" or "ULDR".

All movements are given in chronological order.

Please do not use the %lld specifier to read or write 64-bit integers in C++. It is preferred to use the cin and cout stream or the %I64d specifier.

## 输出格式

Print a single integer — the number of different possible locations of the gang's headquarters.

## 说明/提示

The figure below shows the nine possible positions of the gang headquarters from the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183A/5eedd58060bd35a7ed9fa57f2be7f5f0bfad5425.png)For example, the following movements can get the car from point $ (1,0) $ to point $ (0,0) $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183A/a0545c148a057862574d8aad0a7d3d66cb719bc3.png)

## 样例 #1

### 输入

```
3
UR
UL
ULDR

```

### 输出

```
9

```

## 样例 #2

### 输入

```
2
DR
DL

```

### 输出

```
4

```

