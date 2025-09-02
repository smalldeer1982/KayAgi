---
title: "Perishable Roads"
layout: "post"
diff: 省选/NOI-
pid: CF773D
tag: []
---

# Perishable Roads

## 题目描述

In the country of Never, there are $ n $ cities and a well-developed road system. There is exactly one bidirectional road between every pair of cities, thus, there are as many as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF773D/c0359cb82752ff2b028ccb729bac55ece58968d2.png) roads! No two roads intersect, and no road passes through intermediate cities. The art of building tunnels and bridges has been mastered by Neverians.

An independent committee has evaluated each road of Never with a positive integer called the perishability of the road. The lower the road's perishability is, the more pleasant it is to drive through this road.

It's the year of transport in Never. It has been decided to build a museum of transport in one of the cities, and to set a single signpost directing to some city (not necessarily the one with the museum) in each of the other cities. The signposts must satisfy the following important condition: if any Neverian living in a city without the museum starts travelling from that city following the directions of the signposts, then this person will eventually arrive in the city with the museum.

Neverians are incredibly positive-minded. If a Neverian travels by a route consisting of several roads, he considers the perishability of the route to be equal to the smallest perishability of all the roads in this route.

The government of Never has not yet decided where to build the museum, so they consider all $ n $ possible options. The most important is the sum of perishabilities of the routes to the museum city from all the other cities of Never, if the travelers strictly follow the directions of the signposts. The government of Never cares about their citizens, so they want to set the signposts in a way which minimizes this sum. Help them determine the minimum possible sum for all $ n $ possible options of the city where the museum can be built.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=2000 $ ) — the number of cities in Never.

The following $ n-1 $ lines contain the description of the road network. The $ i $ -th of these lines contains $ n-i $ integers. The $ j $ -th integer in the $ i $ -th line denotes the perishability of the road between cities $ i $ and $ i+j $ .

All road perishabilities are between $ 1 $ and $ 10^{9} $ , inclusive.

## 输出格式

For each city in order from 1 to $ n $ , output the minimum possible sum of perishabilities of the routes to this city from all the other cities of Never if the signposts are set in a way which minimizes this sum.

## 说明/提示

The first example is explained by the picture below. From left to right, there is the initial road network and the optimal directions of the signposts in case the museum is built in city 1, 2 and 3, respectively. The museum city is represented by a blue circle, the directions of the signposts are represented by green arrows.

For instance, if the museum is built in city 3, then the signpost in city 1 must be directed to city 3, while the signpost in city 2 must be directed to city 1. Then the route from city 1 to city 3 will have perishability 2, while the route from city 2 to city 3 will have perishability 1. The sum of perishabilities of these routes is 3.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF773D/5887985fd626a2ff9e975202ab209676c3725e09.png)

## 样例 #1

### 输入

```
3
1 2
3

```

### 输出

```
2
2
3

```

## 样例 #2

### 输入

```
6
2 9 9 6 6
7 1 9 10
9 2 5
4 10
8

```

### 输出

```
6
5
7
5
7
11

```

