---
title: "More Reclamation"
layout: "post"
diff: 提高+/省选-
pid: CF335C
tag: []
---

# More Reclamation

## 题目描述

In a far away land, there are two cities near a river. One day, the cities decide that they have too little space and would like to reclaim some of the river area into land.

The river area can be represented by a grid with $ r $ rows and exactly two columns — each cell represents a rectangular area. The rows are numbered $ 1 $ through $ r $ from top to bottom, while the columns are numbered $ 1 $ and $ 2 $ .

Initially, all of the cells are occupied by the river. The plan is to turn some of those cells into land one by one, with the cities alternately choosing a cell to reclaim, and continuing until no more cells can be reclaimed.

However, the river is also used as a major trade route. The cities need to make sure that ships will still be able to sail from one end of the river to the other. More formally, if a cell $ (r,c) $ has been reclaimed, it is not allowed to reclaim any of the cells $ (r-1,3-c) $ , $ (r,3-c) $ , or $ (r+1,3-c) $ .

The cities are not on friendly terms, and each city wants to be the last city to reclaim a cell (they don't care about how many cells they reclaim, just who reclaims a cell last). The cities have already reclaimed $ n $ cells. Your job is to determine which city will be the last to reclaim a cell, assuming both choose cells optimally from current moment.

## 输入格式

The first line consists of two integers $ r $ and $ n $ ( $ 1<=r<=100,0<=n<=r $ ). Then $ n $ lines follow, describing the cells that were already reclaimed. Each line consists of two integers: $ r_{i} $ and $ c_{i} $ ( $ 1<=r_{i}<=r,1<=c_{i}<=2 $ ), which represent the cell located at row $ r_{i} $ and column $ c_{i} $ . All of the lines describing the cells will be distinct, and the reclaimed cells will not violate the constraints above.

## 输出格式

Output "WIN" if the city whose turn it is to choose a cell can guarantee that they will be the last to choose a cell. Otherwise print "LOSE".

## 说明/提示

In the first example, there are 3 possible cells for the first city to reclaim: $ (2,1) $ , $ (3,1) $ , or $ (3,2) $ . The first two possibilities both lose, as they leave exactly one cell for the other city.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335C/9dcf00d73fa4874adb1a93b4ff0aff43602b2edb.png)However, reclaiming the cell at $ (3,2) $ leaves no more cells that can be reclaimed, and therefore the first city wins.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF335C/3534861a36cc5545c6ce50c4536d43f04309cbd9.png)In the third example, there are no cells that can be reclaimed.

## 样例 #1

### 输入

```
3 1
1 1

```

### 输出

```
WIN

```

## 样例 #2

### 输入

```
12 2
4 1
8 1

```

### 输出

```
WIN

```

## 样例 #3

### 输入

```
1 1
1 2

```

### 输出

```
LOSE

```

