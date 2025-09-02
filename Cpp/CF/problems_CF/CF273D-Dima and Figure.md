---
title: "Dima and Figure"
layout: "post"
diff: 提高+/省选-
pid: CF273D
tag: []
---

# Dima and Figure

## 题目描述

Dima loves making pictures on a piece of squared paper. And yet more than that Dima loves the pictures that depict one of his favorite figures.

A piece of squared paper of size $ n×m $ is represented by a table, consisting of $ n $ rows and $ m $ columns. All squares are white on blank squared paper. Dima defines a picture as an image on a blank piece of paper, obtained by painting some squares black.

The picture portrays one of Dima's favorite figures, if the following conditions hold:

- The picture contains at least one painted cell;
- All painted cells form a connected set, that is, you can get from any painted cell to any other one (you can move from one cell to a side-adjacent one);
- The minimum number of moves needed to go from the painted cell at coordinates $ (x_{1},y_{1}) $ to the painted cell at coordinates $ (x_{2},y_{2}) $ , moving only through the colored cells, equals $ |x_{1}-x_{2}|+|y_{1}-y_{2}| $ .

Now Dima is wondering: how many paintings are on an $ n×m $ piece of paper, that depict one of his favorite figures? Count this number modulo $ 1000000007 (10^{9}+7) $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ — the sizes of the piece of paper $ (1<=n,m<=150) $ .

## 输出格式

In a single line print the remainder after dividing the answer to the problem by number $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
2 2

```

### 输出

```
13

```

## 样例 #2

### 输入

```
3 4

```

### 输出

```
571

```

