---
title: "Valera and Queries"
layout: "post"
diff: 省选/NOI-
pid: CF369E
tag: []
---

# Valera and Queries

## 题目描述

Valera loves segments. He has recently come up with one interesting problem.

The $ Ox $ axis of coordinates has $ n $ segments, the $ i $ -th segment starts in position $ l_{i} $ and ends in position $ r_{i} $ (we will mark it as $ [l_{i},r_{i}] $ ). Your task is to process $ m $ queries, each consists of number $ cnt_{i} $ and a set of $ cnt_{i} $ coordinates of points located on the $ Ox $ axis. The answer to the query is the number of segments, such that each of them contains at least one point from the query. Segment $ [l,r] $ contains point $ q $ , if $ l<=q<=r $ .

Valera found the solution of this problem too difficult. So he asked you to help him. Help Valera.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 1<=n,m<=3·10^{5} $ ) — the number of segments on the axis of coordinates and the number of queries.

Next $ n $ lines contain the descriptions of the segments. The $ i $ -th line contains two positive integers $ l_{i} $ , $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=10^{6} $ ) — the borders of the $ i $ -th segment.

Next $ m $ lines contain the description of the queries, one per line. Each line starts from integer $ cnt_{i} $ ( $ 1<=cnt_{i}<=3·10^{5} $ ) — the number of points in the $ i $ -th query. Then the line contains $ cnt_{i} $ distinct positive integers $ p_{1},p_{2},...,p_{cnti} $ ( $ 1<=p_{1}&lt;p_{2}&lt;...&lt;p_{cnti}<=10^{6} $ ) — the coordinates of points in the $ i $ -th query.

It is guaranteed that the total number of points in all queries doesn't exceed $ 3·10^{5} $ .

## 输出格式

Print $ m $ non-negative integers, where the $ i $ -th number is the response to the $ i $ -th query.

## 样例 #1

### 输入

```
3 3
1 3
4 5
6 7
3 1 4 7
2 4 5
1 8

```

### 输出

```
3
1
0

```

