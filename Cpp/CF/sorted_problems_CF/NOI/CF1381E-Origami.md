---
title: "Origami"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1381E
tag: []
---

# Origami

## 题目描述

After being discouraged by 13 time-limit-exceeded verdicts on an ugly geometry problem, you decided to take a relaxing break for arts and crafts.

There is a piece of paper in the shape of a simple polygon with $ n $ vertices. The polygon may be non-convex, but we all know that proper origami paper has the property that any horizontal line intersects the boundary of the polygon in at most two points.

If you fold the paper along the vertical line $ x=f $ , what will be the area of the resulting shape? When you fold, the part of the paper to the left of the line is symmetrically reflected on the right side.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1381E/7c0a887e786d875943cedb8599c824aacb33ac7b.png)Your task is to answer $ q $ independent queries for values $ f_1,\ldots,f_q $ .

## 输入格式

The first line contains two integers $ n $ , $ q $ ( $ 3\le       n\le 10^5, 1\le q\le 10^5 $ ) — the number of polygon vertices and queries, respectively.

Each of the next $ n $ lines contains two integers $ x_i $ , $ y_i $ ( $ |x_i|, |y_i|\le 10^5 $ ) — the coordinates of the $ i $ -th point of the polygon. The polygon has an edge connecting each pair of adjacent points in the input, and also an edge between $ (x_1,y_1) $ and $ (x_n,y_n) $ . It is guaranteed that the polygon is non-degenerate and that any horizontal line intersects the boundary of the polygon in at most two points. In particular, no boundary edge is strictly horizontal. Two adjacent sides may be collinear.

Each of the next $ q $ lines contains a single integer $ f_i $ ( $ \min\limits_{j=1}^n(x_j)< f_i<       \max\limits_{j=1}^n(x_j) $ ) — the $ x $ -coordinate of the $ i $ -th fold query. It is guaranteed that all $ f_i $ are distinct.

## 输出格式

For each query, output the area $ A_i $ of the paper if you fold it along the line $ x=f_i $ .

Your answer is considered correct if its absolute or relative error does not exceed $ 10^{-4} $ .

Formally, let your answer be $ a $ , and the jury's answer be $ b $ . Your answer is accepted if and only if $ \frac{|a -       b|}{\max{(1, |b|)}} \le 10^{-4} $ .

## 说明/提示

The first test, with the fold $ f=-5 $ :

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1381E/fec64fce3a86c788f4837d43540c38f571946533.png)The second test, with the fold $ f=1 $ :

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1381E/e7e3d8d20382ff7916a59c0de15ac0f84f66fbdd.png)The third test, with the fold $ f=-1 $ :

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1381E/737679bae48f956654b312c402864578d8f6b5bf.png)

## 样例 #1

### 输入

```
4 7
0 10
10 0
0 -10
-10 0
-9
-5
-1
0
1
5
9
```

### 输出

```
199.0000000000
175.0000000000
119.0000000000
100.0000000000
119.0000000000
175.0000000000
199.0000000000
```

## 样例 #2

### 输入

```
4 1
0 0
0 2
2 4
2 2
1
```

### 输出

```
3.0000000000
```

## 样例 #3

### 输入

```
9 4
0 -3
2 -2
-1 -1
0 4
2 5
1 6
-2 3
-1 1
-3 0
0
-2
-1
1
```

### 输出

```
11.1250000000
11.7500000000
10.3446969697
11.3333333333
```

