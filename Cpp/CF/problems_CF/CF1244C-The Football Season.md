---
title: "The Football Season"
layout: "post"
diff: 普及+/提高
pid: CF1244C
tag: []
---

# The Football Season

## 题目描述

Berland Capital Team 比了 $n$ 场比赛，总得分为 $p$。已知胜一场得 $w$ 分，平一场得 $d$ 分，败一场不得分。

求任意一组 $(x,y,z)$ 使得如果 Berland Capital Team 胜 $x$ 场，平 $y$ 场，败 $z$ 场时总分为 $p$。如果不存在这样的三元组，输出 $-1$。

### 形式化题意

求下列方程组的任意一组非负整数解，无解输出 $-1$：

$$
\begin{cases}
x\cdot w+y\cdot d=p\\
x+y+z=n
\end{cases}
$$

## 输入格式

一行四个正整数 $n,p,w,d$。保证 $1\leqslant n\leqslant 10^{12},0\leqslant p\leqslant10^{17},1\leqslant d\lt w\leqslant10^5$。

## 输出格式

如果方程组无解，输出 $-1$。否则输出一行三个非负整数 $x,y,z$ 表示方程组的一组解。

## 样例 #1

### 输入

```
30 60 3 1

```

### 输出

```
17 9 4

```

## 样例 #2

### 输入

```
10 51 5 4

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
20 0 15 5

```

### 输出

```
0 0 20

```

