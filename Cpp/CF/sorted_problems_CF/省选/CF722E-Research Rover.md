---
title: "Research Rover"
layout: "post"
diff: 省选/NOI-
pid: CF722E
tag: []
---

# Research Rover

## 题目描述

Unfortunately, the formal description of the task turned out to be too long, so here is the legend.

Research rover finally reached the surface of Mars and is ready to complete its mission. Unfortunately, due to the mistake in the navigation system design, the rover is located in the wrong place.

The rover will operate on the grid consisting of $ n $ rows and $ m $ columns. We will define as $ (r,c) $ the cell located in the row $ r $ and column $ c $ . From each cell the rover is able to move to any cell that share a side with the current one.

The rover is currently located at cell $ (1,1) $ and has to move to the cell $ (n,m) $ . It will randomly follow some shortest path between these two cells. Each possible way is chosen equiprobably.

The cargo section of the rover contains the battery required to conduct the research. Initially, the battery charge is equal to $ s $ units of energy.

Some of the cells contain anomaly. Each time the rover gets to the cell with anomaly, the battery looses half of its charge rounded down. Formally, if the charge was equal to $ x $ before the rover gets to the cell with anomaly, the charge will change to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/5e007d05e4d6f2ed51d5f62962d41cc3679ff923.png).

While the rover picks a random shortest path to proceed, compute the expected value of the battery charge after it reaches cell $ (n,m) $ . If the cells $ (1,1) $ and $ (n,m) $ contain anomaly, they also affect the charge of the battery.

## 输入格式

The first line of the input contains four integers $ n $ , $ m $ , $ k $ and $ s $ ( $ 1<=n,m<=100000 $ , $ 0<=k<=2000 $ , $ 1<=s<=1000000 $ ) — the number of rows and columns of the field, the number of cells with anomaly and the initial charge of the battery respectively.

The follow $ k $ lines containing two integers $ r_{i} $ and $ c_{i} $ ( $ 1<=r_{i}<=n $ , $ 1<=c_{i}<=m $ ) — coordinates of the cells, containing anomaly. It's guaranteed that each cell appears in this list no more than once.

## 输出格式

The answer can always be represented as an irreducible fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/00f1f3a9533210841fcc58db3ebf06c253f3f34f.png). Print the only integer $ P·Q^{-1} $ modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, the rover picks one of the following six routes:

1. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/9ec03018ca0f56c6c2f6d978bba5abe354af00a2.png), after passing cell $ (2,3) $ charge is equal to $ 6 $ .
2. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/c33021a457ac8c5bc889f817a80d61835c80a6b0.png), after passing cell $ (2,3) $ charge is equal to $ 6 $ .
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/f31c3021594dce78e1218b41ad36645544e3eb2f.png), charge remains unchanged and equals $ 11 $ .
4. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/d616d340616d474f1cf131e388bc97ff077c00fd.png), after passing cells $ (2,1) $ and $ (2,3) $ charge equals $ 6 $ and then $ 3 $ .
5. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/58b582f83e30271c9a15562ebd2f560f6b5dd797.png), after passing cell $ (2,1) $ charge is equal to $ 6 $ .
6. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/856271589dd61834f189db966542ee9a7b753d25.png), after passing cell $ (2,1) $ charge is equal to $ 6 $ .

Expected value of the battery charge is calculated by the following formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF722E/56e29a53ed442392bc44fee422ffcf414eab5cce.png).

Thus $ P=19 $ , and $ Q=3 $ .

 $ 3^{-1} $ modulo $ 10^{9}+7 $ equals $ 333333336 $ .

 $ 19·333333336=333333342 (mod 10^{9}+7) $

## 样例 #1

### 输入

```
3 3 2 11
2 1
2 3

```

### 输出

```
333333342

```

## 样例 #2

### 输入

```
4 5 3 17
1 2
3 3
4 1

```

### 输出

```
514285727

```

## 样例 #3

### 输入

```
1 6 2 15
1 1
1 5

```

### 输出

```
4

```

