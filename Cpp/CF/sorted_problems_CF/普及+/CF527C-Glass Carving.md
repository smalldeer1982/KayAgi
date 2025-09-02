---
title: "Glass Carving"
layout: "post"
diff: 普及+/提高
pid: CF527C
tag: ['线段树', '排序']
---

# Glass Carving

## 题目描述

Leonid wants to become a glass carver (the person who creates beautiful artworks by cutting the glass). He already has a rectangular $ w $ mm $ × $ $ h $ mm sheet of glass, a diamond glass cutter and lots of enthusiasm. What he lacks is understanding of what to carve and how.

In order not to waste time, he decided to practice the technique of carving. To do this, he makes vertical and horizontal cuts through the entire sheet. This process results in making smaller rectangular fragments of glass. Leonid does not move the newly made glass fragments. In particular, a cut divides each fragment of glass that it goes through into smaller fragments.

After each cut Leonid tries to determine what area the largest of the currently available glass fragments has. Since there appear more and more fragments, this question takes him more and more time and distracts him from the fascinating process.

Leonid offers to divide the labor — he will cut glass, and you will calculate the area of the maximum fragment after each cut. Do you agree?

## 输入格式

The first line contains three integers $ w,h,n $ ( $ 2<=w,h<=200000 $ , $ 1<=n<=200000 $ ).

Next $ n $ lines contain the descriptions of the cuts. Each description has the form $ H y $ or $ V x $ . In the first case Leonid makes the horizontal cut at the distance $ y $ millimeters ( $ 1<=y<=h-1 $ ) from the lower edge of the original sheet of glass. In the second case Leonid makes a vertical cut at distance $ x $ ( $ 1<=x<=w-1 $ ) millimeters from the left edge of the original sheet of glass. It is guaranteed that Leonid won't make two identical cuts.

## 输出格式

After each cut print on a single line the area of the maximum available glass fragment in mm $ ^{2} $ .

## 说明/提示

Picture for the first sample test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/6468d2fd0321178fa316ccb774411f002769e9ee.png) Picture for the second sample test:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/40ba2772b27431a21bc874ab308dc348ec8365fd.png)

## 样例 #1

### 输入

```
4 3 4
H 2
V 2
V 3
V 1

```

### 输出

```
8
4
4
2

```

## 样例 #2

### 输入

```
7 6 5
H 4
V 3
V 5
H 2
V 1

```

### 输出

```
28
16
12
6
4

```

