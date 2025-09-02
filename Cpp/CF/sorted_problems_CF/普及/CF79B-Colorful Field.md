---
title: "Colorful Field"
layout: "post"
diff: 普及/提高-
pid: CF79B
tag: []
---

# Colorful Field

## 题目描述

## 题意简述

给出一个 $n \times m$ 的矩阵，当中有 $k$ 个点是坏的。然后按照 **从上往下，从左往右** 的顺序依次填入胡萝卜、奇异果和葡萄（英文分别为 $\mathtt{Carrots}$、$\mathtt{Kiwis}$ 和 $\mathtt{Grapes}$ ）。当然，坏掉的点无法填入东西，也不参与填入矩阵的次序。

现给你 $t$ 次询问，每次给出一对数 $i$ 和 $j$，请输出矩阵第 $i$ 行第 $j$ 列所填的物品。（ **如果这一个点是坏的点，则输出**$\mathtt{Waste}$）

## 输入格式

第一行给出四个数 $n,m,k,t$，具体含义同上。

接下来 $k$ 行，每一行给出一对数 $x$ 和 $y$，表示第 $x$ 行的第 $y$ 列这个点是坏的点。

接下来是 $t$ 行，每一行给出一对数 $i$ 和 $j$，表示询问的点。

## 输出格式

对于每一次询问，输出一个字符串。（$\mathtt{Carrots}$、$\mathtt{Kiwis}$、$\mathtt{Grapes}$ 或 $\mathtt{Waste}$，注意需要大写第一个字母）

## 说明/提示

$1 \le n,m \le 4\cdot10^4$，$1 \le k,t \le 10^3$

## 样例 #1

### 输入

```
4 5 5 6
4 3
1 3
3 3
2 5
3 2
1 3
1 4
2 3
2 4
1 1
1 1

```

### 输出

```
Waste
Grapes
Carrots
Kiwis
Carrots
Carrots

```

