---
title: "DOMINO2 - Domino"
layout: "post"
diff: 难度0
pid: SP4157
tag: []
---

# DOMINO2 - Domino

## 题目描述

### 题意简述
你有一个 $n*m$ 的矩阵，矩阵中一些单元格中有障碍物。你需要用 $1*2$ 或 $2*1$ 的多米诺骨牌覆盖这个矩阵。每个空单元格最多被覆盖一次，障碍物不能被覆盖。你需要确保至少有一块骨牌同时覆盖了第 $i$ 行中的某一格和第 $i+1$ 行中的某一格，其中 $1 \leq i \leq n-1$ 。同理，你需要确保至少有一块骨牌同时覆盖了第 $i$ 列中的某一格和第 $i+1$ 列中的某一格，其中 $1 \leq i \leq m-1$ 。请计算有多少种多米诺覆盖方式。

## 输入格式

输入的第一行是两个整数 $n$ 和 $m$ 。

接下来输入 $n$ 行，每行 $m$ 个字符，表示了这个矩阵。 字符 '.' ($ASCII$ 码是46) 表示该格是空单元格，字符 'x' ($ASCII$ 码是120) 表示该格中是障碍物。

## 输出格式

一个数表示合法的覆盖方法的数量。
答案可能很大，所以输出答案对 $19901013$ 取模。

## 说明/提示

两种方式：

相同颜色的数字表示同一块骨牌，$0$ 表示该格为空。

$\textcolor{red}{11}\textcolor{blue}{2}$

$\textcolor{orange}{4}\textcolor{black}{0}\textcolor{blue}{2}$

$\textcolor{orange}{4}\textcolor{green}{33}$

或

$\textcolor{red}{1}\textcolor{blue}{22}$

$\textcolor{red}{1}\textcolor{black}{0}\textcolor{green}{3}$

$\textcolor{orange}{44}\textcolor{green}{3}$


translated by @czcyf

## 样例 #1

### 输入

```
3 3
...
...
...
```

### 输出

```
2
```

