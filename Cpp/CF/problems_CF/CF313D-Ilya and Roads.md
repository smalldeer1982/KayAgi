---
title: "Ilya and Roads"
layout: "post"
diff: 提高+/省选-
pid: CF313D
tag: []
---

# Ilya and Roads

## 题目描述

Everything is great about Ilya's city, except the roads. The thing is, the only ZooVille road is represented as $ n $ holes in a row. We will consider the holes numbered from 1 to $ n $ , from left to right.

Ilya is really keep on helping his city. So, he wants to fix at least $ k $ holes (perharps he can fix more) on a single ZooVille road.

The city has $ m $ building companies, the $ i $ -th company needs $ c_{i} $ money units to fix a road segment containing holes with numbers of at least $ l_{i} $ and at most $ r_{i} $ . The companies in ZooVille are very greedy, so, if they fix a segment containing some already fixed holes, they do not decrease the price for fixing the segment.

Determine the minimum money Ilya will need to fix at least $ k $ holes.

## 输入格式

The first line contains three integers $ n,m,k $ $ (1<=n<=300,1<=m<=10^{5},1<=k<=n) $ . The next $ m $ lines contain the companies' description. The $ i $ -th line contains three integers $ l_{i},r_{i},c_{i} $ $ (1<=l_{i}<=r_{i}<=n,1<=c_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the minimum money Ilya needs to fix at least $ k $ holes.

If it is impossible to fix at least $ k $ holes, print -1.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
10 4 6
7 9 11
6 9 13
7 7 7
3 5 6

```

### 输出

```
17

```

## 样例 #2

### 输入

```
10 7 1
3 4 15
8 9 8
5 6 8
9 10 6
1 4 2
1 4 10
8 10 13

```

### 输出

```
2

```

## 样例 #3

### 输入

```
10 1 9
5 10 14

```

### 输出

```
-1

```

