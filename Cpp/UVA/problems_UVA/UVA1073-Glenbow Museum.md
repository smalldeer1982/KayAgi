---
title: "Glenbow Museum"
layout: "post"
diff: 省选/NOI-
pid: UVA1073
tag: []
---

# Glenbow Museum

## 题目描述

[PDF](https://uva.onlinejudge.org/external/10/p1073.pdf)

对于一个各边长度任意且都平行于坐标轴的多边形，我们可以用这样的方式描述它：考虑它的每一个内角，如果这个内角为 $90^\circ$，那么用 $\texttt R$ 代表它；如果这个内角为 $270^\circ$，那么用 $\texttt O$ 代表它。从某个点开始，按照逆时针的顺序读取 $\texttt R$ 和 $\texttt O$，最后得到一个由 $\texttt R, \texttt O$ 组成的字符串。


显然，一个 $\texttt R, \texttt O$ 字符串可能对应多个多边形。例如，Figure $1$ 对应的多边形 $1$ 可以被描述为 $\texttt{RRRR}$，多边形 $2$ 可以被描述为 $\texttt{RRORRORRORRO}$、$\texttt{RORRORRORROR}$ 或 $\texttt{ORRORRORRORR}$。

给定整数 $L$，问有多少个长度为 $L$ 的 $\texttt R, \texttt O$ 字符串，使得有一个或以上与之对应的多边形，满足这个多边形内部有一点，可以看到这个多边形的所有内角（即，这个点与多边形所有内角顶点的连线都不与多边形的边相交）。

## 输入格式

**本题在单测试点内包含多组测试数据。**

对于每组数据，一行一个整数 $L (1 \leq L \leq 1,000)$。

输入以单独的一行 `0` 结尾。

## 输出格式

对于每组数据，输出数据点编号和一个整数，表示上文所提到的满足条件的字符串个数。具体格式参见输出样例。

