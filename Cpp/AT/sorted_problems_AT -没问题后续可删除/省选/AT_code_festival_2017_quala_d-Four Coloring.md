---
title: "Four Coloring"
layout: "post"
diff: 省选/NOI-
pid: AT_code_festival_2017_quala_d
tag: []
---

# Four Coloring

## 题目描述

给定一个$H \times W$的网格，试给其中所有格子染`RYGB`四种颜色之一，使得网格上任意一对曼哈顿距离为$d$的格子颜色不同。

## 输入格式

一行两个正整数$H ,W , d$

$1 \leq H,W \leq 500 , 1 \leq d \leq H + W - 2$

## 输出格式

输出一个$H \times W$的字符矩阵表示染色方案

## 样例 #1

### 输入

```
2 2 1
```

### 输出

```
RY
GR
```

## 样例 #2

### 输入

```
2 3 2
```

### 输出

```
RYB
RGB
```

