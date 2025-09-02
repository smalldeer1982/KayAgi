---
title: "Wizards and Roads"
layout: "post"
diff: 省选/NOI-
pid: CF167D
tag: []
---

# Wizards and Roads

## 题目描述

In some country live wizards. They love to build cities and roads.

The country used to have $ k $ cities, the $ j $ -th city ( $ 1<=j<=k $ ) was located at a point ( $ x_{j} $ , $ y_{j} $ ). It was decided to create another $ n-k $ cities. And the $ i $ -th one ( $ k&lt;i<=n $ ) was created at a point with coordinates ( $ x_{i} $ , $ y_{i} $ ):

- $ x_{i}=(a·x_{i-1}+b) mod (10^{9}+9) $
- $ y_{i}=(c·y_{i-1}+d) mod (10^{9}+9) $

Here $ a $ , $ b $ , $ c $ , $ d $ are primes. Also, $ a≠c,b≠d $ .

After the construction of all $ n $ cities, the wizards have noticed something surprising. It turned out that for every two different cities $ i $ and $ j $ , $ x_{i}≠x_{j} $ and $ y_{i}≠y_{j} $ holds.

The cities are built, it's time to build roads! It was decided to use the most difficult (and, of course, the most powerful) spell for the construction of roads. Using this spell creates a road between the towns of $ u $ , $ v $ ( $ y_{u} $ > $ y_{v} $ ) if and only if for any city $ w $ which lies strictly inside the corner at the point $ u $ , $ v $ (see below), there is a city $ s $ that does not lie in the corner, which is located along the $ x $ -coordinate strictly between $ w $ and $ u $ and simultaneously $ y_{s}&gt;y_{v} $ .

A corner on the points $ p_{2} $ ( $ x_{2} $ , $ y_{2} $ ), $ p_{1} $ ( $ x_{1} $ , $ y_{1} $ ) ( $ y_{1}&lt;y_{2} $ ) is the set of points ( $ x,y $ ), for which at least one of the two conditions is fulfilled:

- $ min(x_{1},x_{2})<=x<=max(x_{1},x_{2}) $ and $ y>=y_{1} $
- $ y_{1}<=y<=y_{2} $ and $ (x-x_{2})·(x_{1}-x_{2})>=0 $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF167D/e6a75925f8bb3bfa6f6c97c47de7dcc2f9dc2c0a.png) The pictures showing two different corners In order to test the spell, the wizards will apply it to all the cities that lie on the $ x $ -coordinate in the interval $ [L,R] $ . After the construction of roads the national government wants to choose the maximum number of pairs of cities connected by the road, so that no city occurs in two or more pairs. Your task is for each $ m $ offered variants of values $ L $ , $ R $ to calculate the maximum number of such pairs after the construction of the roads. Please note that the cities that do not lie in the interval $ [L,R] $ on the $ x $ -coordinate, do not affect the construction of roads in any way.

## 输入格式

The first line contains two space-separated integers $ n $ , $ k $ ( $ 1<=k<=n<=10^{5} $ , $ k<=30 $ ). Next $ k $ lines contain coordinates of the cities' location points from the first to the $ k $ -th one. The $ j $ -th line contains space-separated pair of integers $ x_{j} $ , $ y_{j} $ ( $ 0<=x_{j},y_{j}&lt;10^{9}+9 $ ) — coordinates of the $ j $ -th city.

The next line contains space-separated integers $ a,b,c,d $ ( $ 2<=a,b,c,d&lt;10^{9}+9 $ ). It is guaranteed that those numbers are prime and also that $ a≠c,b≠d $ .

It's guaranteed, that for every two different cities $ i $ and $ j $ , $ x_{i}≠x_{j} $ and $ y_{i}≠y_{j} $ holds.

The next line contains integer $ m $ ( $ 1<=m<=10^{5} $ ) — the number of variants to build the roads. Next $ m $ lines contain pairs of space-separated integers $ L_{i} $ , $ R_{i} $ ( $ 0<=L_{i}<=R_{i}&lt;10^{9}+9 $ ) — the variants of choosing the cities to build the roads.

## 输出格式

For any pair of numbers $ L_{i} $ , $ R_{i} $ print the answer to the problem on a single line. Print the answers for the pairs in the order, in which the pairs are given in the input data.

## 说明/提示

In the first sample the roads connect the cities in a chain in the order of increasing of $ x $ .

In the second sample the remaining 5 cities will be located at points $ (5, 11); (20, 263098); (65, 292514823); (200, 76958738); (605, 622120197) $ .

## 样例 #1

### 输入

```
6 6
0 0
1 1
2 2
3 3
4 4
5 5
2 3 3 2
4
0 5
1 4
2 3
3 3

```

### 输出

```
3
2
1
0

```

## 样例 #2

### 输入

```
6 1
0 0
3 5 23917 11
4
0 1000000008
0 10
100 150
200 10000

```

### 输出

```
2
1
0
1

```

