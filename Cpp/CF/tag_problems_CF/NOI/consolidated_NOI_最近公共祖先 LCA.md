---
title: "Segment Covering"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1774G
tag: ['倍增', '最近公共祖先 LCA', '组合数学', '容斥原理']
---

# Segment Covering

## 题目描述

ChthollyNotaSeniorious gives DataStructures a number axis with $ m $ distinct segments on it. Let $ f(l,r) $ be the number of ways to choose an even number of segments such that the union of them is exactly $ [l,r] $ , and $ g(l,r) $ be the number of ways to choose an odd number of segments such that the union of them is exactly $ [l,r] $ .

ChthollyNotaSeniorious asked DataStructures $ q $ questions. In each query, ChthollyNotaSeniorious will give DataStructures two numbers $ l, r $ , and now he wishes that you can help him find the value $ f(l,r)-g(l,r) $ modulo $ 998\,244\,353 $ so that he wouldn't let her down.

## 输入格式

The first line of input contains two integers $ m $ ( $ 1 \leq m \leq 2 \cdot 10^5 $ ) and $ q $ ( $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the number of segments and queries, correspondingly.

The $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \leq x_i < y_i \leq 10^9 $ ), denoting a segment $ [x_i, y_i] $ .

It is guaranteed that all segments are distinct. More formally, there do not exist two numbers $ i, j $ with $ 1 \le i < j \le m $ such that $ x_i = x_j $ and $ y_i = y_j $ .

The $ i $ -th of the next $ q $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i < r_i \leq 10^9 $ ), describing a query.

## 输出格式

For each query, output a single integer — $ f(l_i,r_i)-g(l_i,r_i) $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first query, we have to find $ f(1, 4) - g(1, 4) $ . The only subset of segments with union $ [1, 4] $ is $ \{[1, 3], [2, 4]\} $ , so $ f(1, 4) = 1, g(1, 4) = 0 $ .

In the second query, we have to find $ f(1, 5) - g(1, 5) $ . The only subsets of segments with union $ [1, 5] $ are $ \{[1, 3], [2, 4], [3, 5]\} $ and $ \{[1, 3], [3, 5]\} $ , so $ f(1, 5) = 1, g(1, 5) = 1 $ .

## 样例 #1

### 输入

```
4 2
1 3
4 6
2 4
3 5
1 4
1 5
```

### 输出

```
1
0
```



---

---
title: "Tourist Guide"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF589H
tag: ['搜索', '生成树', '最近公共祖先 LCA']
---

# Tourist Guide

## 题目描述

It is not that easy to create a tourist guide as one might expect. A good tourist guide should properly distribute flow of tourists across the country and maximize the revenue stream from the tourism. This is why there is a number of conditions to be met before a guide may be declared as an official tourist guide and approved by Ministry of Tourism.

Ministry of Tourism has created a list of $ k $ remarkable cities out of $ n $ cities in the country. Basically, it means that in order to conform to strict regulations and to be approved by the ministry a tourist guide should be represented as a set of routes between remarkable cities so that the following conditions are met:

- the first and the last city of every route are distinct remarkable cities,
- each remarkable city can be an endpoint of at most one route,
- there is no pair of routes which share a road.

Please note that a route may pass through a remarkable city. Revenue stream from the tourism highly depends on a number of routes included in a tourist guide so the task is to find out a set of routes conforming the rules of a tourist guide with a maximum number of routes included.

## 输入格式

The first line contains three integer numbers $ n,m,k $ $ (1<=n<=50000,0<=m<=50000,1<=k<=n) $ — the number of cities in the country, the number of roads in the country and the number of remarkable cities correspondingly.

Each of the following $ m $ lines contains two integer numbers $ a_{i} $ and $ b_{i} $ $ (1<=a_{i},b_{i}<=n) $ — meaning that cities $ a_{i} $ and $ b_{i} $ are connected by a bidirectional road. It is guaranteed that $ a_{i} $ and $ b_{i} $ are distinct numbers and there is no more than one road between a pair of cities.

The last line contains $ k $ distinct integer numbers — a list of remarkable cities. All cities are numbered from 1 to $ n $ .

## 输出格式

The first line of the output should contain $ c $ — the number of routes in a tourist guide. The following $ c $ lines should contain one tourist route each. Every route should be printed in a form of " $ t $ $ v_{1} $ $ v_{2} $ ... $ v_{t+1} $ ", where $ t $ is a number of roads in a route and $ v_{1},v_{2},...,v_{t+1} $ — cities listed in the order they are visited on the route.

If there are multiple answers print any of them.

## 样例 #1

### 输入

```
6 4 4
1 2
2 3
4 5
5 6
1 3 4 6

```

### 输出

```
2
2 1 2 3
2 4 5 6

```

## 样例 #2

### 输入

```
4 3 4
1 2
1 3
1 4
1 2 3 4

```

### 输出

```
2
1 1 2
2 3 1 4

```



---

