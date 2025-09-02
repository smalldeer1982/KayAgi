---
title: "Counter Attack"
layout: "post"
diff: 提高+/省选-
pid: CF190E
tag: []
---

# Counter Attack

## 题目描述

Berland has managed to repel the flatlanders' attack and is now starting the counter attack.

Flatland has $ n $ cities, numbered from $ 1 $ to $ n $ , and some pairs of them are connected by bidirectional roads. The Flatlandian maps show roads between cities if and only if there is in fact no road between this pair of cities (we do not know whether is it a clever spy-proof strategy or just saving ink). In other words, if two cities are connected by a road on a flatland map, then there is in fact no road between them. The opposite situation is also true: if two cities are not connected by a road on a flatland map, then in fact, there is a road between them.

The berlanders got hold of a flatland map. Now Vasya the Corporal is commissioned by General Touristov to find all such groups of flatland cities, that in each group of cities you can get from any city to any other one, moving along the actual roads. Also the cities from different groups are unreachable from each other, moving along the actual roads. Indeed, destroying such groups one by one is much easier than surrounding all Flatland at once!

Help the corporal complete this task and finally become a sergeant! Don't forget that a flatland map shows a road between cities if and only if there is in fact no road between them.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ $ (1<=n<=5·10^{5},0<=m<=10^{6}) $ — the number of cities and the number of roads marked on the flatland map, correspondingly.

Next $ m $ lines contain descriptions of the cities on the map. The $ i $ -th line contains two integers $ a_{i} $ and $ b_{i} $ $ (1<=a_{i},b_{i}<=n,a_{i}≠b_{i}) $ — the numbers of cities that are connected by the $ i $ -th road on the flatland map.

It is guaranteed that each pair of cities occurs in the input no more than once.

## 输出格式

On the first line print number $ k $ — the number of groups of cities in Flatland, such that in each group you can get from any city to any other one by flatland roads. At the same time, the cities from different groups should be unreachable by flatland roads.

On each of the following $ k $ lines first print $ t_{i} $ $ (1<=t_{i}<=n) $ — the number of vertexes in the $ i $ -th group. Then print space-separated numbers of cities in the $ i $ -th group.

The order of printing groups and the order of printing numbers in the groups does not matter. The total sum $ t_{i} $ for all $ k $ groups must equal $ n $ .

## 说明/提示

In the first sample there are roads only between pairs of cities 1-4 and 2-3.

In the second sample there is no road between cities 1 and 2, but still you can get from one city to the other one through city number 3.

## 样例 #1

### 输入

```
4 4
1 2
1 3
4 2
4 3

```

### 输出

```
2
2 1 4 
2 2 3 

```

## 样例 #2

### 输入

```
3 1
1 2

```

### 输出

```
1
3 1 2 3 

```

