---
title: "Square of Rectangles"
layout: "post"
diff: 难度0
pid: CF2120A
tag: []
---

# Square of Rectangles

## 题目描述

Aryan 非常喜欢正方形，但讨厌矩形（是的，他知道所有正方形都是矩形）。但是 Harshith 喜欢捉弄 Aryan。Harshith 给了 Aryan 三个矩形，尺寸分别为 $l_1\times b_1$、$l_2\times b_2$ 和 $l_3\times b_3$，其中 $l_3\leq l_2\leq l_1$ 且 $b_3\leq b_2\leq b_1$。为了打败 Harshith，Aryan 决定将这三个矩形排列成一个正方形，要求矩形之间不能重叠，并且矩形必须沿边对齐。不允许旋转矩形。请你帮助 Aryan 判断他是否能够打败 Harshith。

## 输入格式

每组测试数据包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。

每个测试用例包含一行，包含 $6$ 个用空格分隔的整数 $l_1, b_1, l_2, b_2, l_3, b_3$（$1 \leq l_3\le l_2\le l_1\le 100$，$1\le b_3\le b_2\le b_1 \leq 100$），表示三个矩形的尺寸。

## 输出格式

对于每个测试用例，如果可以将这三个矩形排列成一个正方形，输出 "YES"；否则输出 "NO"。

输出不区分大小写。例如，"yEs"、"yes"、"Yes" 和 "YES" 都会被识别为肯定回答。

## 说明/提示

在第二个测试用例中，三个矩形 $5\times 3$、$5\times 1$ 和 $5\times 1$ 可以如下图所示排列成一个正方形。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120A/0d2c10850310a468f465b43bc2b22a0dad40baad.png)

在第四个测试用例中，可以证明无法在给定的限制条件下将这三个矩形排列成一个正方形。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
100 100 10 10 1 1
5 3 5 1 5 1
2 3 1 2 1 1
8 5 3 5 3 3
3 3 3 3 2 1
```

### 输出

```
NO
YES
YES
NO
NO
```

