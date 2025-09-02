---
title: "DETER2 - Find The Determinant II"
layout: "post"
diff: 省选/NOI-
pid: SP1772
tag: ['莫比乌斯反演']
---

# DETER2 - Find The Determinant II

## 题目描述

对于一个$N\times N$的矩阵，$m_{ij}=\gcd(i,j)^k$  
你的任务是计算这个矩阵的行列式

## 输入格式

第一行输入一个整数t，代表任务个数  
下t行，每行两个整数N和k

## 输出格式

t行，每行输出一个整数，代表那个矩阵的行列式对1000003取模后的结果

## 说明/提示

t在20左右  
$1\le N\le 10^6$  
$1\le k\le 10^9$

## 样例 #1

### 输入

```
3
4 2
2 4
4 3
```

### 输出

```
288
15
10192
```

