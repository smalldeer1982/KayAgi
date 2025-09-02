---
title: "New Year Tree Decorations"
layout: "post"
diff: 提高+/省选-
pid: CF379E
tag: []
---

# New Year Tree Decorations

## 题目描述

Due to atheistic Soviet past, Christmas wasn't officially celebrated in Russia for most of the twentieth century. As a result, the Russian traditions for Christmas and New Year mixed into one event celebrated on the New Year but including the tree, a Santa-like 'Grandfather Frost', presents and huge family reunions and dinner parties all over the country. Bying a Tree at the New Year and installing it in the house is a tradition. Usually the whole family decorates the tree on the New Year Eve. We hope that Codeforces is a big and loving family, so in this problem we are going to decorate a tree as well.

So, our decoration consists of $ n $ pieces, each piece is a piece of colored paper, its border is a closed polyline of a special shape. The pieces go one by one as is shown on the picture. The $ i $ -th piece is a polyline that goes through points: $ (0,0) $ , $ (0,y_{0}) $ , $ (1,y_{1}) $ , $ (2,y_{2}) $ , ..., $ (k,y_{k}) $ , $ (k,0) $ . The width of each piece equals $ k $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF379E/69b6f4a3736ea64c0c3cc034ee4bc0d7ac63d241.png)The figure to the left shows the decoration, the figure to the right shows the individual pieces it consists of.The piece number 1 (shown red on the figure) is the outer piece (we see it completely), piece number 2 (shown yellow) follows it (we don't see it completely as it is partially closed by the first piece) and so on. The programmers are quite curious guys, so the moment we hung a decoration on the New Year tree we started to wonder: what area of each piece can people see?

## 输入格式

The first line contains two integers, $ n $ and $ k $ $ (1<=n,k<=300) $ . Each of the following $ n $ lines contains $ k+1 $ integers — the description of the polyline. If the $ i $ -th line contains ontegers $ y_{i,0},y_{i,1},...,y_{i,k} $ , that means that the polyline of the $ i $ -th piece goes through points $ (0,0) $ , $ (0,y_{i,0}) $ , $ (1,y_{i,1}) $ , $ (2,y_{i,2}) $ , ..., $ (k,y_{i,k}) $ , $ (k,0) $ $ (1<=y_{i,j}<=1000) $ .

## 输出格式

Print $ n $ real numbers — for each polyline, the area of its visible part.

The answer will be considered correct if its relative or absolute error do not exceed $ 10^{-4} $ .

## 样例 #1

### 输入

```
2 2
2 1 2
1 2 1

```

### 输出

```
3.000000000000
0.500000000000

```

## 样例 #2

### 输入

```
1 1
1 1

```

### 输出

```
1.000000000000

```

## 样例 #3

### 输入

```
4 1
2 7
7 2
5 5
6 4

```

### 输出

```
4.500000000000
1.250000000000
0.050000000000
0.016666666667

```

