---
title: "Drivers Dissatisfaction"
layout: "post"
diff: 省选/NOI-
pid: CF733F
tag: []
---

# Drivers Dissatisfaction

## 题目描述

In one kingdom there are $ n $ cities and $ m $ two-way roads. Each road connects a pair of cities, and for each road we know the level of drivers dissatisfaction — the value $ w_{i} $ .

For each road we know the value $ c_{i} $ — how many lamziks we should spend to reduce the level of dissatisfaction with this road by one. Thus, to reduce the dissatisfaction with the $ i $ -th road by $ k $ , we should spend $ k·c_{i} $ lamziks. And it is allowed for the dissatisfaction to become zero or even negative.

In accordance with the king's order, we need to choose $ n-1 $ roads and make them the main roads. An important condition must hold: it should be possible to travel from any city to any other by the main roads.

The road ministry has a budget of $ S $ lamziks for the reform. The ministry is going to spend this budget for repair of some roads (to reduce the dissatisfaction with them), and then to choose the $ n-1 $ main roads.

Help to spend the budget in such a way and then to choose the main roads so that the total dissatisfaction with the main roads will be as small as possible. The dissatisfaction with some roads can become negative. It is not necessary to spend whole budget $ S $ .

It is guaranteed that it is possible to travel from any city to any other using existing roads. Each road in the kingdom is a two-way road.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=2·10^{5} $ , $ n-1<=m<=2·10^{5} $ ) — the number of cities and the number of roads in the kingdom, respectively.

The second line contains $ m $ integers $ w_{1},w_{2},...,w_{m} $ ( $ 1<=w_{i}<=10^{9} $ ), where $ w_{i} $ is the drivers dissatisfaction with the $ i $ -th road.

The third line contains $ m $ integers $ c_{1},c_{2},...,c_{m} $ ( $ 1<=c_{i}<=10^{9} $ ), where $ c_{i} $ is the cost (in lamziks) of reducing the dissatisfaction with the $ i $ -th road by one.

The next $ m $ lines contain the description of the roads. The $ i $ -th of this lines contain a pair of integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ ) which mean that the $ i $ -th road connects cities $ a_{i} $ and $ b_{i} $ . All roads are two-way oriented so it is possible to move by the $ i $ -th road from $ a_{i} $ to $ b_{i} $ , and vice versa. It is allowed that a pair of cities is connected by more than one road.

The last line contains one integer $ S $ ( $ 0<=S<=10^{9} $ ) — the number of lamziks which we can spend for reforms.

## 输出格式

In the first line print $ K $ — the minimum possible total dissatisfaction with main roads.

In each of the next $ n-1 $ lines print two integers $ x,v_{x} $ , which mean that the road $ x $ is among main roads and the road $ x $ , after the reform, has the level of dissatisfaction $ v_{x} $ .

Consider that roads are numbered from $ 1 $ to $ m $ in the order as they are given in the input data. The edges can be printed in arbitrary order. If there are several answers, print any of them.

## 样例 #1

### 输入

```
6 9
1 3 1 1 3 1 2 2 2
4 1 4 2 2 5 3 1 6
1 2
1 3
2 3
2 4
2 5
3 5
3 6
4 5
5 6
7

```

### 输出

```
0
1 1
3 1
6 1
7 2
8 -5

```

## 样例 #2

### 输入

```
3 3
9 5 1
7 7 2
2 1
3 1
3 2
2

```

### 输出

```
5
3 0
2 5

```

