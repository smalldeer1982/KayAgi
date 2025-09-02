---
title: "Donkey and Stars"
layout: "post"
diff: 省选/NOI-
pid: CF249D
tag: []
---

# Donkey and Stars

## 题目描述

In the evenings Donkey would join Shrek to look at the stars. They would sit on a log, sipping tea and they would watch the starry sky. The sky hung above the roof, right behind the chimney. Shrek's stars were to the right of the chimney and the Donkey's stars were to the left. Most days the Donkey would just count the stars, so he knew that they are exactly $ n $ . This time he wanted a challenge. He imagined a coordinate system: he put the origin of the coordinates at the intersection of the roof and the chimney, directed the $ OX $ axis to the left along the roof and the $ OY $ axis — up along the chimney (see figure). The Donkey imagined two rays emanating from he origin of axes at angles $ α_{1} $ and $ α_{2} $ to the $ OX $ axis.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/01e07f49112d306c9832b3ead8a5e8c0cfbcc93c.png)Now he chooses any star that lies strictly between these rays. After that he imagines more rays that emanate from this star at the same angles $ α_{1} $ and $ α_{2} $ to the $ OX $ axis and chooses another star that lies strictly between the new rays. He repeats the operation as long as there still are stars he can choose between the rays that emanate from a star.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/87b736a4eb176865176dd95be306088882057bc0.png)As a result, the Donkey gets a chain of stars. He can consecutively get to each star if he acts by the given rules.

Your task is to find the maximum number of stars $ m $ that the Donkey's chain can contain.

Note that the chain must necessarily start in the point of the origin of the axes, that isn't taken into consideration while counting the number $ m $ of stars in the chain.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of stars. The second line contains simple fractions representing relationships " $ a $ / $ b $ $ c $ / $ d $ ", such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/001d6ed25a51cc97270d17f90f539721adafeb23.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/6337dac88a6615a66f2f81cd58bf23a08b9e3f93.png) ( $ 0<=a,b,c,d<=10^{5} $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/fc6c659b0d5627405e17dcff3cc9324566f85bb7.png); ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/bd710757ebfb2847fad7f627245fda1e53c8abb0.png); ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/f8e78907d2982a94cf586897df695dde51e86710.png)). The given numbers $ a $ , $ b $ , $ c $ , $ d $ are integers.

Next $ n $ lines contain pairs of integers $ x_{i} $ , $ y_{i} $ ( $ 1<=x_{i},y_{i}<=10^{5} $ )— the stars' coordinates.

It is guaranteed that all stars have distinct coordinates.

## 输出格式

In a single line print number $ m $ — the answer to the problem.

## 说明/提示

In the sample the longest chain the Donkey can build consists of four stars. Note that the Donkey can't choose the stars that lie on the rays he imagines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF249D/9b10980b4f4e779f5c4c6a72105611e261a67332.png)

## 样例 #1

### 输入

```
15
1/3 2/1
3 1
6 2
4 2
2 5
4 5
6 6
3 4
1 6
2 1
7 4
9 3
5 3
1 3
15 5
12 4

```

### 输出

```
4

```

