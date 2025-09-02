---
title: "Dividing Island"
layout: "post"
diff: 普及+/提高
pid: CF63D
tag: []
---

# Dividing Island

## 题目描述

## 题目简述

有一个 $a \times b$ 和一个 $c \times d$ 的矩形 $(b \neq d\;)$ ，其中长度为 $a$ 和 $c$ 的边共线，如图所示:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63D/d0dfe8fb20d3bd76651bd208632c7ccbf8e3af11.png)

要求将这个图形分为 $n$ 个完整的块，其中第 $i$ 块的面积为 $x_i$。

## 输入格式

给出 $a,b,c,d,n$ 和 $\{x_n\}$，保证 $x$ 的元素和等于图形的面积。数据范围见英文描述。

## 输出格式

判断是否存在可行的输出方案，输出 `YES` 或 `NO`。 接着输出一种可行的分割方案（一个 $\max(b,d) \times (a + c)$ 的矩形），不属于图形的部分用 `.` 表示，每一个分割块用一个小写字母表示。

## 样例 #1

### 输入

```
3 4 2 2 3
5 8 3

```

### 输出

```
YES
aaabb
aabbb
cbb..
ccb..

```

## 样例 #2

### 输入

```
3 2 1 4 4
1 2 3 4

```

### 输出

```
YES
abbd
cccd
...d
...d

```

