---
title: "Tourist Reform"
layout: "post"
diff: 省选/NOI-
pid: CF732F
tag: []
---

# Tourist Reform

## 题目描述

Berland is a tourist country! At least, it can become such — the government of Berland is confident about this.

There are $ n $ cities in Berland, some pairs of which are connected by two-ways roads. Each road connects two different cities. In Berland there are no roads which connect the same pair of cities. It is possible to get from any city to any other city using given two-ways roads.

According to the reform each road will become one-way. It will be oriented to one of two directions.

To maximize the tourist attraction of Berland, after the reform for each city $ i $ the value $ r_{i} $ will be calculated. It will equal to the number of cities $ x $ for which there is an oriented path from the city $ i $ to the city $ x $ . In other words, $ r_{i} $ will equal the number of cities which can be reached from the city $ i $ by roads.

The government is sure that tourist's attention will be focused on the minimum value of $ r_{i} $ .

Help the government of Berland make the reform to maximize the minimum of $ r_{i} $ .

## 输入格式

The first line contains two integers $ n,m $ ( $ 2<=n<=400000,1<=m<=400000 $ ) — the number of cities and the number of roads.

The next $ m $ lines describe roads in Berland: the $ j $ -th of them contains two integers $ u_{j} $ and $ v_{j} $ ( $ 1<=u_{j},v_{j}<=n $ , $ u_{j}≠v_{j} $ ), where $ u_{j} $ and $ v_{j} $ are the numbers of cities which are connected by the $ j $ -th road.

The cities are numbered from $ 1 $ to $ n $ . It is guaranteed that it is possible to get from any city to any other by following two-ways roads. In Berland there are no roads which connect the same pair of cities.

## 输出格式

In the first line print single integer — the maximum possible value $ min_{1<=i<=n}{r_{i}} $ after the orientation of roads.

The next $ m $ lines must contain the description of roads after the orientation: the $ j $ -th of them must contain two integers $ u_{j},v_{j} $ , it means that the $ j $ -th road will be directed from the city $ u_{j} $ to the city $ v_{j} $ . Print roads in the same order as they are given in the input data.

## 样例 #1

### 输入

```
7 9
4 3
2 6
7 1
4 1
7 3
3 5
7 4
6 5
2 5

```

### 输出

```
4
4 3
6 2
7 1
1 4
3 7
5 3
7 4
5 6
2 5

```

