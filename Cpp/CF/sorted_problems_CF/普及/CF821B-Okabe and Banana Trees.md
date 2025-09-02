---
title: "Okabe and Banana Trees"
layout: "post"
diff: 普及/提高-
pid: CF821B
tag: []
---

# Okabe and Banana Trees

## 题目描述

Okabe needs bananas for one of his experiments for some strange reason. So he decides to go to the forest and cut banana trees.

Consider the point $ (x,y) $ in the 2D plane such that $ x $ and $ y $ are integers and $ 0<=x,y $ . There is a tree in such a point, and it has $ x+y $ bananas. There are no trees nor bananas in other points. Now, Okabe draws a line with equation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821B/943332af45ee9b24d3dd582c61cd6fb6bc9281c7.png). Okabe can select a single rectangle with axis aligned sides with all points on or under the line and cut all the trees in all points that are inside or on the border of this rectangle and take their bananas. Okabe's rectangle can be degenerate; that is, it can be a line segment or even a point.

Help Okabe and find the maximum number of bananas he can get if he chooses the rectangle wisely.

Okabe is sure that the answer does not exceed $ 10^{18} $ . You can trust him.

## 输入格式

The first line of input contains two space-separated integers $ m $ and $ b $ ( $ 1<=m<=1000 $ , $ 1<=b<=10000 $ ).

## 输出格式

Print the maximum number of bananas Okabe can get from the trees he cuts.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF821B/9062959c907537ca725899b162ca1dad63845c7e.png)The graph above corresponds to sample test 1. The optimal rectangle is shown in red and has $ 30 $ bananas.

## 样例 #1

### 输入

```
1 5

```

### 输出

```
30

```

## 样例 #2

### 输入

```
2 3

```

### 输出

```
25

```

