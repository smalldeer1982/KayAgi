---
title: "Radio stations"
layout: "post"
diff: 省选/NOI-
pid: CF762E
tag: []
---

# Radio stations

## 题目描述

In the lattice points of the coordinate line there are $ n $ radio stations, the $ i $ -th of which is described by three integers:

- $ x_{i} $ — the coordinate of the $ i $ -th station on the line,
- $ r_{i} $ — the broadcasting range of the $ i $ -th station,
- $ f_{i} $ — the broadcasting frequency of the $ i $ -th station.

We will say that two radio stations with numbers $ i $ and $ j $ reach each other, if the broadcasting range of each of them is more or equal to the distance between them. In other words $ min(r_{i},r_{j})>=|x_{i}-x_{j}| $ .

Let's call a pair of radio stations $ (i,j) $ bad if $ i&lt;j $ , stations $ i $ and $ j $ reach each other and they are close in frequency, that is, $ |f_{i}-f_{j}|<=k $ .

Find the number of bad pairs of radio stations.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=10^{5} $ , $ 0<=k<=10 $ ) — the number of radio stations and the maximum difference in the frequencies for the pair of stations that reach each other to be considered bad.

In the next $ n $ lines follow the descriptions of radio stations. Each line contains three integers $ x_{i} $ , $ r_{i} $ and $ f_{i} $ ( $ 1<=x_{i},r_{i}<=10^{9} $ , $ 1<=f_{i}<=10^{4} $ ) — the coordinate of the $ i $ -th radio station, it's broadcasting range and it's broadcasting frequency. No two radio stations will share a coordinate.

## 输出格式

Output the number of bad pairs of radio stations.

## 样例 #1

### 输入

```
3 2
1 3 10
3 2 5
4 10 8

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 3
1 3 10
3 2 5
4 10 8

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5 1
1 3 2
2 2 4
3 2 1
4 2 1
5 3 3

```

### 输出

```
2

```

## 样例 #4

### 输入

```
5 1
1 5 2
2 5 4
3 5 1
4 5 1
5 5 3

```

### 输出

```
5

```

