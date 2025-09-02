---
title: "Escape from Stones"
layout: "post"
diff: 普及/提高-
pid: CF264A
tag: []
---

# Escape from Stones

## 题目描述

Squirrel Liss lived in a forest peacefully, but unexpected trouble happens. Stones fall from a mountain. Initially Squirrel Liss occupies an interval $ [0,1] $ . Next, $ n $ stones will fall and Liss will escape from the stones. The stones are numbered from 1 to $ n $ in order.

The stones always fall to the center of Liss's interval. When Liss occupies the interval $ [k-d,k+d] $ and a stone falls to $ k $ , she will escape to the left or to the right. If she escapes to the left, her new interval will be $ [k-d,k] $ . If she escapes to the right, her new interval will be $ [k,k+d] $ .

You are given a string $ s $ of length $ n $ . If the $ i $ -th character of $ s $ is "l" or "r", when the $ i $ -th stone falls Liss will escape to the left or to the right, respectively. Find the sequence of stones' numbers from left to right after all the $ n $ stones falls.

## 输入格式

The input consists of only one line. The only line contains the string $ s $ ( $ 1<=|s|<=10^{6} $ ). Each character in $ s $ will be either "l" or "r".

## 输出格式

Output $ n $ lines — on the $ i $ -th line you should print the $ i $ -th stone's number from the left.

## 说明/提示

In the first example, the positions of stones 1, 2, 3, 4, 5 will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF264A/c25aff142a5735311a4288820a328b17b4aeb12a.png), respectively. So you should print the sequence: 3, 5, 4, 2, 1.

## 样例 #1

### 输入

```
llrlr

```

### 输出

```
3
5
4
2
1

```

## 样例 #2

### 输入

```
rrlll

```

### 输出

```
1
2
5
4
3

```

## 样例 #3

### 输入

```
lrlrr

```

### 输出

```
2
4
5
3
1

```

