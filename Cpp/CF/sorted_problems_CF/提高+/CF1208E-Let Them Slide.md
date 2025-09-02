---
title: "Let Them Slide"
layout: "post"
diff: 提高+/省选-
pid: CF1208E
tag: []
---

# Let Them Slide

## 题目描述

You are given $ n $ arrays that can have different sizes. You also have a table with $ w $ columns and $ n $ rows. The $ i $ -th array is placed horizontally in the $ i $ -th row. You can slide each array within its row as long as it occupies several consecutive cells and lies completely inside the table.

You need to find the maximum sum of the integers in the $ j $ -th column for each $ j $ from $ 1 $ to $ w $ independently.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1208E/66577db70aaef36d98c0a37e28a9702a11eb45eb.png)Optimal placements for columns $ 1 $ , $ 2 $ and $ 3 $ are shown on the pictures from left to right.Note that you can exclude any array out of a column provided it remains in the window. In this case its value is considered to be zero.

## 输入格式

The first line contains two integers $ n $ ( $ 1 \le n \le 10^{6} $ ) and $ w $ ( $ 1 \le w \le 10^{6} $ ) — the number of arrays and the width of the table.

Each of the next $ n $ lines consists of an integer $ l_{i} $ ( $ 1 \le l_{i} \le w $ ), the length of the $ i $ -th array, followed by $ l_{i} $ integers $ a_{i1}, a_{i2}, \ldots, a_{il_i} $ ( $ -10^{9} \le a_{ij} \le 10^{9} $ ) — the elements of the array.

The total length of the arrays does no exceed $ 10^{6} $ .

## 输出格式

Print $ w $ integers, the $ i $ -th of them should be the maximum sum for column $ i $ .

## 说明/提示

Illustration for the first example is in the statement.

## 样例 #1

### 输入

```
3 3
3 2 4 8
2 2 5
2 6 3

```

### 输出

```
10 15 16 

```

## 样例 #2

### 输入

```
2 2
2 7 8
1 -8

```

### 输出

```
7 8 

```

