---
title: "Painting Square"
layout: "post"
diff: 省选/NOI-
pid: CF300D
tag: []
---

# Painting Square

## 题目描述

Vasily the bear has got a large square white table of $ n $ rows and $ n $ columns. The table has got a black border around this table.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300D/ddbad6e90fff9934de05472a83c397e11ee2a641.png)The example of the initial table at $ n $ = 5.Vasily the bear wants to paint his square table in exactly $ k $ moves. Each move is sequence of actions:

1. The bear chooses some square inside his table. At that the square must have a black border painted around it. Also, the square shouldn't contain a black cell. The number of cells in the square shouldn't be less than $ 2 $ .
2. The bear chooses some row and some column inside the chosen square. Then he paints each cell of this row and this column inside the chosen square. After that the rectangles, formed by the square's border and the newly painted cells, must be squares of a non-zero area.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300D/2f670f9945e1926b1278ff5823ebb3aa45519652.png)  An example of correct painting at $ n $ = 7 и $ k $ = 2.The bear already knows numbers $ n $ and $ k $ . Help him — find the number of ways to paint the square in exactly $ k $ moves. Two ways to paint are called distinct if the resulting tables will differ in at least one cell. As the answer can be rather large, print the remainder after dividing it by $ 7340033 $ .

## 输入格式

The first line contains integer $ q $ $ (1<=q<=10^{5}) $ — the number of test data.

Each of the following $ q $ lines contains two integers $ n $ and $ k $ $ (1<=n<=10^{9},0<=k<=1000) $ — the size of the initial table and the number of moves for the corresponding test.

## 输出格式

For each test from the input print the answer to the problem modulo $ 7340033 $ . Print the answers to the tests in the order in which the tests are given in the input.

## 说明/提示

All possible painting ways for the test $ n=7 $ and $ k=2 $ are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300D/1f5221421bd715ed9c40286f4e2330edd5cee6fd.png)

## 样例 #1

### 输入

```
8
1 0
1 1
3 0
3 1
2 0
2 1
3 2
7 2

```

### 输出

```
1
0
1
1
1
0
0
4

```

