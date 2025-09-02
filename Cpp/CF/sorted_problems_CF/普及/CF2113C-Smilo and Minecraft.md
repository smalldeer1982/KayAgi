---
title: "Smilo and Minecraft"
layout: "post"
diff: 普及/提高-
pid: CF2113C
tag: ['贪心', '枚举', '前缀和']
---

# Smilo and Minecraft

## 题目描述

Smilo 在玩 Minecraft！为了准备去打龙，他需要大量的金苹果，所以他需要大量的金子。因此，Smilo 准备下矿。

矿洞是一个 $n\times m$ 的矩形网格，每个格子可能是金矿、石头或空地。Smilo 可以在一个空地点燃炸药，这会将以此空地为中心的边长为 $2k+1$ 的正方形区域夷为平地。如果一个金矿在正方形的内部并且没有和边框相接触，那么它会直接消失；如果金矿在正方形的边框上（在内部并且和正方形的边相接触），Smilo 将会获得这个金子。

求出 Smilo 最多可以获得多少金子。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据，第一行三个整数 $n,m,k(1\le n,m,k\le 500)$。\
接下来 $n$ 行，每行一个由 `g`，`#` 和 `.` 构成的长度为 $m$ 的字符串，表示矿洞。`g` 表示金矿，`#` 表示石头，`.` 表示空格。

保证单个测试点中 $\sum nm\le 2.5\times 10^5$。

## 输出格式

对于每组数据，输出一行一个整数表示答案。

## 说明/提示

**样例解释**

对于第一组数据，Smilo 可以在任意空地中引爆炸药获得 $2$ 个金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/31cdfd6d4d5bc2d30d1aa78bd3d2c6d2b0fc3eda.png)

对于第二组数据，Smilo 怎么做都不能获得任何金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/a0691441b6e186314d109f809a1563824ebb170d.png)

对于第三组数据，Smilo 可以先在左下角的空地中引爆炸药获得 $2$ 个金子，再在左边一个格子引爆炸药获得 $2$ 个金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/83af7f606c31f060510f0f11993f3494ca718e49.png)

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
3
2 3 1
#.#
g.g
2 3 2
#.#
g.g
3 4 2
.gg.
g..#
g##.
```

### 输出

```
2
0
4
```

