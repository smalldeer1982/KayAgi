---
title: "Aerodynamic"
layout: "post"
diff: 普及+/提高
pid: CF1299B
tag: []
---

# Aerodynamic

## 题目描述

Guy-Manuel and Thomas are going to build a polygon spaceship.

You're given a strictly convex (i. e. no three points are collinear) polygon $ P $ which is defined by coordinates of its vertices. Define $ P(x,y) $ as a polygon obtained by translating $ P $ by vector $ \overrightarrow {(x,y)} $ . The picture below depicts an example of the translation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1299B/83c2f1baf8b89730630e4ed629298d51b68af048.png)

Define $ T $ as a set of points which is the union of all $ P(x,y) $ such that the origin $ (0,0) $ lies in $ P(x,y) $ (both strictly inside and on the boundary). There is also an equivalent definition: a point $ (x,y) $ lies in $ T $ only if there are two points $ A,B $ in $ P $ such that $ \overrightarrow {AB} = \overrightarrow {(x,y)} $ . One can prove $ T $ is a polygon too. For example, if $ P $ is a regular triangle then $ T $ is a regular hexagon. At the picture below $ P $ is drawn in black and some $ P(x,y) $ which contain the origin are drawn in colored:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1299B/7e534d615e6a5f78b53ffae5177d7d1ddaf49471.png)

The spaceship has the best aerodynamic performance if $ P $ and $ T $ are similar. Your task is to check whether the polygons $ P $ and $ T $ are [similar](https://tinyurl.com/vp5m7vl).

## 输入格式

The first line of input will contain a single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the number of points.

The $ i $ -th of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ |x_i|, |y_i| \le 10^9 $ ), denoting the coordinates of the $ i $ -th vertex.

It is guaranteed that these points are listed in counterclockwise order and these points form a strictly convex polygon.

## 输出格式

Output "YES" in a separate line, if $ P $ and $ T $ are similar. Otherwise, output "NO" in a separate line. You can print each letter in any case (upper or lower).

## 说明/提示

The following image shows the first sample: both $ P $ and $ T $ are squares. The second sample was shown in the statements.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1299B/e9bf2b6bd412db56abfa4dcfff0f19e57982f841.png)

## 样例 #1

### 输入

```
4
1 0
4 1
3 4
0 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
100 86
50 0
150 0
```

### 输出

```
nO
```

## 样例 #3

### 输入

```
8
0 0
1 0
2 1
3 3
4 6
3 6
2 5
1 3
```

### 输出

```
YES
```

