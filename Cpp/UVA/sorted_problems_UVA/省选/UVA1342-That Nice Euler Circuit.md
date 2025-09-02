---
title: "That Nice Euler Circuit"
layout: "post"
diff: 省选/NOI-
pid: UVA1342
tag: ['数学', '计算几何', '枚举']
---

# That Nice Euler Circuit

## 题目描述

给出一个平面上$n-1$个点的回路，第$n$个顶点与第$1$个顶点相同，求它把整个平面分成了几个部分（包括内部围起来的部分和外面的无限大的区域）。

## 输入格式

本题包含多组数据$(\leqslant 25)$。

对于每组数据，第一行，一个整数$n$。

第二行，$2n$个整数，为$x_i,y_i$，表示这$n$个点的坐标，数据保证$x_n=x_1,y_n=y_1$.

$n=0$表示数据结束。

## 输出格式

对于每组数据，输出一行，以下列格式输出，其中$x$表示第$x$组数据，$w$是答案。

**Case** $x$**: There are **$w$** pieces.**

## 说明/提示

数据组数$\leqslant 25$

$4\leqslant n\leqslant 300$

$-300\leqslant x_i,y_i\leqslant 300$

感谢@AThousandMoon 提供的翻译

