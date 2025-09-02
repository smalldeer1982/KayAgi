---
title: "Color the Carpet"
layout: "post"
diff: 省选/NOI-
pid: CF297D
tag: []
---

# Color the Carpet

## 题目描述

Even polar bears feel cold when lying on the ice. Therefore, a polar bear Alice is going to make a carpet. The carpet can be viewed as a grid with height $ h $ and width $ w $ . Then the grid is divided into $ h×w $ squares. Alice is going to assign one of $ k $ different colors to each square. The colors are numbered from 1 to $ k $ . She may choose not to use all of the colors.

However, there are some restrictions. For every two adjacent squares (squares that shares an edge) $ x $ and $ y $ , there is a color constraint in one of the forms:

- $ color(x)=color(y) $ , or
- $ color(x)≠color(y) $ .

Example of the color constraints:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/535d1d4ec9a1bcb4f1f5ac12060cde0f65471360.png)Ideally, Alice wants to satisfy all color constraints. But again, life in the Arctic is hard. It is not always possible to satisfy all color constraints. Fortunately, she will still be happy if at least ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/c7b5e8f543c3882ba6f2a662e01781b4de30f8c7.png) of the color constraints are satisfied.

If she has $ 4 $ colors she can color the carpet in the following way:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/84535e9e280c4fb80d9cbe6a8b779a69a879098d.png)And she is happy because ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/050547ba0080dee4ce4e2010a283122ee46b002c.png) of the color constraints are satisfied, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/93a2fe0ea2a5cac28f71987aac7a9527d1566697.png). Your task is to help her color the carpet.

## 输入格式

The first line contains three integers $ h,w,k $ $ (2<=h,w<=1000,1<=k<=w·h) $ .

The next $ 2h-1 $ lines describe the color constraints from top to bottom, left to right. They contain $ w-1,w,w-1,w,...,w-1 $ characters respectively. Each color constraint is represented by a character "E" or "N", where "E" means " $ = $ " and "N" means " $ ≠ $ ".

The color constraints listed in the order they are depicted on the picture.

## 输出格式

If there is a coloring that satisfies at least ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297D/c7b5e8f543c3882ba6f2a662e01781b4de30f8c7.png) of the color constraints, print "YES" (without quotes) in the first line. In each of the next $ h $ lines, print $ w $ integers describing the coloring.

Otherwise, print "NO" (without quotes).

## 样例 #1

### 输入

```
3 4 4
ENE
NNEE
NEE
ENEN
ENN

```

### 输出

```
YES
1 1 2 2
3 4 1 1
3 3 2 4
```

