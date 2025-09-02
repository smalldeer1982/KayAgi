---
title: "Divide Square"
layout: "post"
diff: 提高+/省选-
pid: CF1401E
tag: []
---

# Divide Square

## 题目描述

There is a square of size $ 10^6 \times 10^6 $ on the coordinate plane with four points $ (0, 0) $ , $ (0, 10^6) $ , $ (10^6, 0) $ , and $ (10^6, 10^6) $ as its vertices.

You are going to draw segments on the plane. All segments are either horizontal or vertical and intersect with at least one side of the square.

Now you are wondering how many pieces this square divides into after drawing all segments. Write a program calculating the number of pieces of the square.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 0       \le n, m \le 10^5 $ ) — the number of horizontal segments and the number of vertical segments.

The next $ n $ lines contain descriptions of the horizontal segments. The $ i $ -th line contains three integers $ y_i $ , $ lx_i $ and $ rx_i $ ( $ 0 < y_i < 10^6 $ ; $ 0 \le       lx_i < rx_i \le 10^6 $ ), which means the segment connects $ (lx_i, y_i) $ and $ (rx_i, y_i) $ .

The next $ m $ lines contain descriptions of the vertical segments. The $ i $ -th line contains three integers $ x_i $ , $ ly_i $ and $ ry_i $ ( $ 0 < x_i < 10^6 $ ; $ 0 \le       ly_i < ry_i \le 10^6 $ ), which means the segment connects $ (x_i, ly_i) $ and $ (x_i, ry_i) $ .

It's guaranteed that there are no two segments on the same line, and each segment intersects with at least one of square's sides.

## 输出格式

Print the number of pieces the square is divided into after drawing all the segments.

## 说明/提示

The sample is like this:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1401E/17be53a5afe098ed0413461c4a2e30e4f2b8aabc.png)

## 样例 #1

### 输入

```
3 3
2 3 1000000
4 0 4
3 0 1000000
4 0 1
2 0 5
3 1 1000000
```

### 输出

```
7
```

