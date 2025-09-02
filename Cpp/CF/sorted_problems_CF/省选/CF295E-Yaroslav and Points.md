---
title: "Yaroslav and Points"
layout: "post"
diff: 省选/NOI-
pid: CF295E
tag: []
---

# Yaroslav and Points

## 题目描述

Yaroslav has $ n $ points that lie on the $ Ox $ axis. The coordinate of the first point is $ x_{1} $ , the coordinate of the second point is $ x_{2} $ , ..., the coordinate of the $ n $ -th point is — $ x_{n} $ . Now Yaroslav wants to execute $ m $ queries, each of them is of one of the two following types:

1. Move the $ p_{j} $ -th point from position $ x_{pj} $ to position $ x_{pj}+d_{j} $ . At that, it is guaranteed that after executing such query all coordinates of the points will be distinct.
2. Count the sum of distances between all pairs of points that lie on the segment $ [l_{j},r_{j}] $ $ (l_{j}<=r_{j}) $ . In other words, you should count the sum of: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF295E/38769b41287eaecf62f3c386e08a6ca65538ebf0.png).

Help Yaroslav.

## 输入格式

The first line contains integer $ n $ — the number of points $ (1<=n<=10^{5}) $ . The second line contains distinct integers $ x_{1},x_{2},...,x_{n} $ — the coordinates of points $ (|x_{i}|<=10^{9}) $ .

The third line contains integer $ m $ — the number of queries $ (1<=m<=10^{5}) $ . The next $ m $ lines contain the queries. The $ j $ -th line first contains integer $ t_{j} $ $ (1<=t_{j}<=2) $ — the query type. If $ t_{j}=1 $ , then it is followed by two integers $ p_{j} $ and $ d_{j} $ $ (1<=p_{j}<=n,|d_{j}|<=1000) $ . If $ t_{j}=2 $ , then it is followed by two integers $ l_{j} $ and $ r_{j} $ $ (-10^{9}<=l_{j}<=r_{j}<=10^{9}) $ .

It is guaranteed that at any moment all the points have distinct coordinates.

## 输出格式

For each type 2 query print the answer on a single line. Print the answers in the order, in which the queries follow in the input.

Please, do not use the %lld specifier to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams of the %I64d specifier.

## 样例 #1

### 输入

```
8
36 50 28 -75 40 -60 -95 -48
20
2 -61 29
1 5 -53
1 1 429
1 5 130
2 -101 -71
2 -69 53
1 1 404
1 5 518
2 -101 53
2 50 872
1 1 -207
2 -99 -40
1 7 -389
1 6 -171
1 2 464
1 7 -707
1 1 -730
1 1 560
2 635 644
1 7 -677

```

### 输出

```
176
20
406
1046
1638
156
0

```

