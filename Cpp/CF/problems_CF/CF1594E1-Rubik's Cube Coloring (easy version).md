---
title: "Rubik's Cube Coloring (easy version)"
layout: "post"
diff: 普及-
pid: CF1594E1
tag: []
---

# Rubik's Cube Coloring (easy version)

## 题目描述

It is the easy version of the problem. The difference is that in this version, there are no nodes with already chosen colors.

Theofanis is starving, and he wants to eat his favorite food, sheftalia. However, he should first finish his homework. Can you help him with this problem?

You have a perfect binary tree of $ 2^k - 1 $ nodes — a binary tree where all vertices $ i $ from $ 1 $ to $ 2^{k - 1} - 1 $ have exactly two children: vertices $ 2i $ and $ 2i + 1 $ . Vertices from $ 2^{k - 1} $ to $ 2^k - 1 $ don't have any children. You want to color its vertices with the $ 6 $ Rubik's cube colors (White, Green, Red, Blue, Orange and Yellow).

Let's call a coloring good when all edges connect nodes with colors that are neighboring sides in the Rubik's cube.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/b0755608caf4588a1ceffdca8e2be827560017bc.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/c6ef9fa6fcd45f3211d7baf9a8cc69c074f640a9.png)A picture of Rubik's cube and its 2D map.More formally:

- a white node can not be neighboring with white and yellow nodes;
- a yellow node can not be neighboring with white and yellow nodes;
- a green node can not be neighboring with green and blue nodes;
- a blue node can not be neighboring with green and blue nodes;
- a red node can not be neighboring with red and orange nodes;
- an orange node can not be neighboring with red and orange nodes;

You want to calculate the number of the good colorings of the binary tree. Two colorings are considered different if at least one node is colored with a different color.

The answer may be too large, so output the answer modulo $ 10^9+7 $ .

## 输入格式

The first and only line contains the integers $ k $ ( $ 1 \le k \le 60 $ ) — the number of levels in the perfect binary tree you need to color.

## 输出格式

Print one integer — the number of the different colorings modulo $ 10^9+7 $ .

## 说明/提示

In the picture below, you can see one of the correct colorings of the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1594E1/dcebca3c4893383a751dc627ead5632c7d038ce7.png)

## 样例 #1

### 输入

```
3
```

### 输出

```
24576
```

## 样例 #2

### 输入

```
14
```

### 输出

```
934234
```

