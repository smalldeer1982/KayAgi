---
title: "The Cake Is a Lie"
layout: "post"
diff: 入门
pid: CF1519B
tag: []
---

# The Cake Is a Lie

## 题目描述

有一个 $n\times m$ 的矩阵，初始时你站在 $(1,1)$ ，终点在 $(n,m)$。

当你站在 $(x,y)$ 时，你可以：

- 走向 $(x,y+1)$，获得 $x$ 点分数；
- 走向 $(x+1,y)$，获得 $y$ 点分数。

请问你是否可以在走到终点时**恰好获得** $k$ 点分数。

## 输入格式

第一行有一个正整数 $t$ ( $1\le t\le 100$ )，表示询问组数。

## 输出格式

对于每组询问，若满足要求则输出 `YES`，否则输出 `NO`。

Translated by Rosmarinus.

## 样例 #1

### 输入

```
6
1 1 0
2 2 2
2 2 3
2 2 4
1 4 3
100 100 10000
```

### 输出

```
YES
NO
YES
NO
YES
NO
```

