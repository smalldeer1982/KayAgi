---
title: "Tiles"
layout: "post"
diff: 普及/提高-
pid: CF1178C
tag: []
---

# Tiles

## 题目描述

Bob is decorating his kitchen, more precisely, the floor. He has found a prime candidate for the tiles he will use. They come in a simple form factor — a square tile that is diagonally split into white and black part as depicted in the figure below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178C/51fd9adf02d36f09b63ea5e4909ce958161fd4a1.png)The dimension of this tile is perfect for this kitchen, as he will need exactly $ w \times h $ tiles without any scraps. That is, the width of the kitchen is $ w $ tiles, and the height is $ h $ tiles. As each tile can be rotated in one of four ways, he still needs to decide on how exactly he will tile the floor. There is a single aesthetic criterion that he wants to fulfil: two adjacent tiles must not share a colour on the edge — i.e. one of the tiles must have a white colour on the shared border, and the second one must be black.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178C/b795f3504af8553334180ece9878d04b86535357.png)The picture on the left shows one valid tiling of a $ 3 \times 2 $ kitchen. The picture on the right shows an invalid arrangement, as the bottom two tiles touch with their white parts.Find the number of possible tilings. As this number may be large, output its remainder when divided by $ 998244353 $ (a prime number).

## 输入格式

The only line contains two space separated integers $ w $ , $ h $ ( $ 1 \leq w,h \leq 1\,000 $ ) — the width and height of the kitchen, measured in tiles.

## 输出格式

Output a single integer $ n $ — the remainder of the number of tilings when divided by $ 998244353 $ .

## 样例 #1

### 输入

```
2 2

```

### 输出

```
16

```

## 样例 #2

### 输入

```
2 4

```

### 输出

```
64

```

