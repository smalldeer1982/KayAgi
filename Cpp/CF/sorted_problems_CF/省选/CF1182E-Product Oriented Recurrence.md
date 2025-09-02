---
title: "Product Oriented Recurrence"
layout: "post"
diff: 省选/NOI-
pid: CF1182E
tag: []
---

# Product Oriented Recurrence

## 题目描述

当 $x \geq 4$ 时，$f_x = c^{2x - 6} \cdot f_{x - 1} \cdot f_{x - 2} \cdot f_{x - 3}$ 。

现在已知 $n,f_1,f_2,f_3,c$ 的值，求 $f_n$ 的值，对 $10^9 + 7$ 取模。

$(4 \leq n \leq 10^{18},1 \leq f_1,f_2,f_3,c \leq 10^9)$

## 输入格式

共一行，依次输入 $n,f_1,f_2,f_3,c$ 。

## 输出格式

共一行，输出 $f_n \bmod (10^9 + 7)$ 。

## 样例 #1

### 输入

```
5 1 2 5 3

```

### 输出

```
72900

```

## 样例 #2

### 输入

```
17 97 41 37 11

```

### 输出

```
317451037

```

