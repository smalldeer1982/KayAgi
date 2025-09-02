---
title: "Duff in Mafia"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF587D
tag: []
---

# Duff in Mafia

## 题目描述

Duff is one if the heads of Mafia in her country, Andarz Gu. Andarz Gu has $ n $ cities (numbered from 1 to $ n $ ) connected by $ m $ bidirectional roads (numbered by $ 1 $ to $ m $ ).

Each road has a destructing time, and a color. $ i $ -th road connects cities $ v_{i} $ and $ u_{i} $ and its color is $ c_{i} $ and its destructing time is $ t_{i} $ .

Mafia wants to destruct a matching in Andarz Gu. A matching is a subset of roads such that no two roads in this subset has common endpoint. They can destruct these roads in parallel, i. e. the total destruction time is a maximum over destruction times of all selected roads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587D/a53c23915fc4382f2bfe77b7372f450a1320cd80.png)They want two conditions to be satisfied:

1. The remaining roads form a proper coloring.
2. Destructing time of this matching is minimized.

The remaining roads after destructing this matching form a proper coloring if and only if no two roads of the same color have same endpoint, or, in the other words, edges of each color should form a matching.

There is no programmer in Mafia. That's why Duff asked for your help. Please help her and determine which matching to destruct in order to satisfied those conditions (or state that this is not possible).

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 2<=n<=5×10^{4} $ and $ 1<=m<=5×10^{4} $ ), number of cities and number of roads in the country.

The next $ m $ lines contain the the roads. $ i-th $ of them contains four integers $ v_{i},u_{i},c_{i} $ and $ t_{i} $ ( $ 1<=v_{i},u_{i}<=n $ , $ v_{i}≠u_{i} $ and $ 1<=c_{i},t_{i}<=10^{9} $ for each $ 1<=i<=m $ ).

## 输出格式

In the first line of input, print "Yes" (without quotes) if satisfying the first condition is possible and "No" (without quotes) otherwise.

If it is possible, then you have to print two integers $ t $ and $ k $ in the second line, the minimum destructing time and the number of roads in the matching (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587D/465fbfd6bab02a6507061badb13bff93ada3fb77.png)).

In the third line print $ k $ distinct integers separated by spaces, indices of the roads in the matching in any order. Roads are numbered starting from one in order of their appearance in the input.

If there's more than one solution, print any of them.

## 说明/提示

Graph of Andarz Gu in the first sample case is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587D/9fdcf9000b9849deb07ed2166ba017b10266938b.png)A solution would be to destruct the roads with crosses.

Graph of Andarz Gu in the second sample case is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587D/80047b1233eefc696bafab007d4617701f011cf8.png)

## 样例 #1

### 输入

```
5 7
2 1 3 7
3 1 1 6
5 4 1 8
4 5 1 1
3 2 2 3
4 5 2 5
2 3 2 4

```

### 输出

```
Yes
3 2
4 5

```

## 样例 #2

### 输入

```
3 5
3 2 1 3
1 3 1 1
3 2 1 4
1 3 2 2
1 3 2 10

```

### 输出

```
No

```

