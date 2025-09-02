---
title: "Repainting Street"
layout: "post"
diff: 普及-
pid: CF1415B
tag: []
---

# Repainting Street

## 题目描述

- 有一条街道，$n$ 栋房子排成一行，编号从 $1$ 到 $n$。每个房子的颜色为 $c_i$ ，工人每次可粉刷连续的 $k$ 个房子，求出将整条街刷成同一个颜色的最短的次数。

------------

## 输入格式

- 第一行输入整数 $t$ 为街道的条数，并且保证 $t$（$1 \leqslant t \leqslant {10}^4$）
- 第二行输入两个整数 $n$ 和 $k$（$1 \leqslant k \leqslant n \leqslant {10}^5$）
- 第三行输入房屋初始颜色 $c_i$（$1 \leqslant c_i \leqslant 100$）

------------

## 输出格式

- 输出 $t$ 行，每行为每个街道粉刷需要的最少天数

Translated by [Seth](https://www.luogu.com.cn/user/358800).

## 样例 #1

### 输入

```
3
10 2
1 1 2 2 1 1 2 2 2 1
7 1
1 2 3 4 5 6 7
10 3
1 3 3 3 3 1 2 1 3 3
```

### 输出

```
3
6
2
```

