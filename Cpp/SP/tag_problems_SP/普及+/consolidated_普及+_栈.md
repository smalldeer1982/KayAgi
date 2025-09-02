---
title: "HISTOGRA - Largest Rectangle in a Histogram"
layout: "post"
diff: 普及+/提高
pid: SP1805
tag: ['栈']
---

# HISTOGRA - Largest Rectangle in a Histogram

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP1805/b9567e3483620f1fe679470ac44083eae9842e79.png)

如图所示，在一条水平线上有  $n$ 个宽为  $1$ 的矩形，求包含于这些矩形的最大子矩形面积（图中的阴影部分的面积即所求答案）。

## 输入格式

有多组测试数据，每组数据占一行。输入零时读入结束。

每行开头为一个数字  $n(1\le n\le 10^5)$，接下来在同一行给出  $n$ 个数字  $h_1,h_2,\cdots, h_n (0\le hi\le 10^9)$，表示每个矩形的高度。

## 输出格式

对于每组数据，输出最大子矩阵面积，一组数据输出一行。

## 样例 #1

### 输入

```
7 2 1 4 5 1 3 3
4 1000 1000 1000 1000
0
```

### 输出

```
8
4000
```



---

