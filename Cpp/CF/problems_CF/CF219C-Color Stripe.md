---
title: "Color Stripe"
layout: "post"
diff: 普及/提高-
pid: CF219C
tag: []
---

# Color Stripe

## 题目描述

A colored stripe is represented by a horizontal row of $ n $ square cells, each cell is pained one of $ k $ colors. Your task is to repaint the minimum number of cells so that no two neighbouring cells are of the same color. You can use any color from 1 to $ k $ to repaint the cells.

## 输入格式

The first input line contains two integers $ n $ and $ k $ ( $ 1<=n<=5·10^{5}; 2<=k<=26 $ ). The second line contains $ n $ uppercase English letters. Letter "A" stands for the first color, letter "B" stands for the second color and so on. The first $ k $ English letters may be used. Each letter represents the color of the corresponding cell of the stripe.

## 输出格式

Print a single integer — the required minimum number of repaintings. In the second line print any possible variant of the repainted stripe.

## 样例 #1

### 输入

```
6 3
ABBACC

```

### 输出

```
2
ABCACA

```

## 样例 #2

### 输入

```
3 2
BBB

```

### 输出

```
1
BAB

```

