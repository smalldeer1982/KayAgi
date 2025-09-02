---
title: "Golden Plate"
layout: "post"
diff: 普及-
pid: CF1031A
tag: []
---

# Golden Plate

## 题目描述

You have a plate and you want to add some gilding to it. The plate is a rectangle that we split into $ w\times h $ cells. There should be $ k $ gilded rings, the first one should go along the edge of the plate, the second one — $ 2 $ cells away from the edge and so on. Each ring has a width of $ 1 $ cell. Formally, the $ i $ -th of these rings should consist of all bordering cells on the inner rectangle of size $ (w - 4(i - 1))\times(h - 4(i - 1)) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1031A/347cd2ee781d01fc5a8212010a9a488ef250ad46.png)The picture corresponds to the third example.Your task is to compute the number of cells to be gilded.

## 输入格式

The only line contains three integers $ w $ , $ h $ and $ k $ ( $ 3 \le w, h \le 100 $ , $ 1 \le k \le \left\lfloor \frac{min(n, m) + 1}{4}\right\rfloor $ , where $ \lfloor x \rfloor $ denotes the number $ x $ rounded down) — the number of rows, columns and the number of rings, respectively.

## 输出格式

Print a single positive integer — the number of cells to be gilded.

## 说明/提示

The first example is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1031A/8ef68100f0e4d74d121ee779a666ca2b2a0d0fdf.png)The second example is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1031A/22b59cf41d139cb0bc1ae7e108eb90b4ef24521f.png)The third example is shown in the problem description.

## 样例 #1

### 输入

```
3 3 1

```

### 输出

```
8

```

## 样例 #2

### 输入

```
7 9 1

```

### 输出

```
28

```

## 样例 #3

### 输入

```
7 9 2

```

### 输出

```
40

```

