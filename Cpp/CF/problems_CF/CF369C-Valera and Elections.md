---
title: "Valera and Elections"
layout: "post"
diff: 普及+/提高
pid: CF369C
tag: []
---

# Valera and Elections

## 题目描述

The city Valera lives in is going to hold elections to the city Parliament.

The city has $ n $ districts and $ n-1 $ bidirectional roads. We know that from any district there is a path along the roads to any other district. Let's enumerate all districts in some way by integers from $ 1 $ to $ n $ , inclusive. Furthermore, for each road the residents decided if it is the problem road or not. A problem road is a road that needs to be repaired.

There are $ n $ candidates running the elections. Let's enumerate all candidates in some way by integers from $ 1 $ to $ n $ , inclusive. If the candidate number $ i $ will be elected in the city Parliament, he will perform exactly one promise — to repair all problem roads on the way from the $ i $ -th district to the district $ 1 $ , where the city Parliament is located.

Help Valera and determine the subset of candidates such that if all candidates from the subset will be elected to the city Parliament, all problem roads in the city will be repaired. If there are several such subsets, you should choose the subset consisting of the minimum number of candidates.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of districts in the city.

Then $ n-1 $ lines follow. Each line contains the description of a city road as three positive integers $ x_{i} $ , $ y_{i} $ , $ t_{i} $ ( $ 1<=x_{i},y_{i}<=n $ , $ 1<=t_{i}<=2 $ ) — the districts connected by the $ i $ -th bidirectional road and the road type. If $ t_{i} $ equals to one, then the $ i $ -th road isn't the problem road; if $ t_{i} $ equals to two, then the $ i $ -th road is the problem road.

It's guaranteed that the graph structure of the city is a tree.

## 输出格式

In the first line print a single non-negative number $ k $ — the minimum size of the required subset of candidates. Then on the second line print $ k $ space-separated integers $ a_{1},a_{2},...\ a_{k} $ — the numbers of the candidates that form the required subset. If there are multiple solutions, you are allowed to print any of them.

## 样例 #1

### 输入

```
5
1 2 2
2 3 2
3 4 2
4 5 2

```

### 输出

```
1
5 

```

## 样例 #2

### 输入

```
5
1 2 1
2 3 2
2 4 1
4 5 1

```

### 输出

```
1
3 

```

## 样例 #3

### 输入

```
5
1 2 2
1 3 2
1 4 2
1 5 2

```

### 输出

```
4
5 4 3 2 

```

