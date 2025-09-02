---
title: "Cities Excursions"
layout: "post"
diff: 省选/NOI-
pid: CF864F
tag: []
---

# Cities Excursions

## 题目描述

There are $ n $ cities in Berland. Some pairs of them are connected with $ m $ directed roads. One can use only these roads to move from one city to another. There are no roads that connect a city to itself. For each pair of cities $ (x,y) $ there is at most one road from $ x $ to $ y $ .

A path from city $ s $ to city $ t $ is a sequence of cities $ p_{1} $ , $ p_{2} $ , ... , $ p_{k} $ , where $ p_{1}=s $ , $ p_{k}=t $ , and there is a road from city $ p_{i} $ to city $ p_{i+1} $ for each $ i $ from $ 1 $ to $ k-1 $ . The path can pass multiple times through each city except $ t $ . It can't pass through $ t $ more than once.

A path $ p $ from $ s $ to $ t $ is ideal if it is the lexicographically minimal such path. In other words, $ p $ is ideal path from $ s $ to $ t $ if for any other path $ q $ from $ s $ to $ t $ $ p_{i}<q_{i} $ , where $ i $ is the minimum integer such that $ p_{i}≠q_{i} $ .

There is a tourist agency in the country that offers $ q $ unusual excursions: the $ j $ -th excursion starts at city $ s_{j} $ and ends in city $ t_{j} $ .

For each pair $ s_{j} $ , $ t_{j} $ help the agency to study the ideal path from $ s_{j} $ to $ t_{j} $ . Note that it is possible that there is no ideal path from $ s_{j} $ to $ t_{j} $ . This is possible due to two reasons:

- there is no path from $ s_{j} $ to $ t_{j} $ ;
- there are paths from $ s_{j} $ to $ t_{j} $ , but for every such path $ p $ there is another path $ q $ from $ s_{j} $ to $ t_{j} $ , such that $ p_{i}>q_{i} $ , where $ i $ is the minimum integer for which $ p_{i}≠q_{i} $ .

The agency would like to know for the ideal path from $ s_{j} $ to $ t_{j} $ the $ k_{j} $ -th city in that path (on the way from $ s_{j} $ to $ t_{j} $ ).

For each triple $ s_{j} $ , $ t_{j} $ , $ k_{j} $ ( $ 1<=j<=q $ ) find if there is an ideal path from $ s_{j} $ to $ t_{j} $ and print the $ k_{j} $ -th city in that path, if there is any.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ q $ ( $ 2<=n<=3000 $ , $ 0<=m<=3000 $ , $ 1<=q<=4·10^{5} $ ) — the number of cities, the number of roads and the number of excursions.

Each of the next $ m $ lines contains two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=n $ , $ x_{i}≠y_{i} $ ), denoting that the $ i $ -th road goes from city $ x_{i} $ to city $ y_{i} $ . All roads are one-directional. There can't be more than one road in each direction between two cities.

Each of the next $ q $ lines contains three integers $ s_{j} $ , $ t_{j} $ and $ k_{j} $ ( $ 1<=s_{j},t_{j}<=n $ , $ s_{j}≠t_{j} $ , $ 1<=k_{j}<=3000 $ ).

## 输出格式

In the $ j $ -th line print the city that is the $ k_{j} $ -th in the ideal path from $ s_{j} $ to $ t_{j} $ . If there is no ideal path from $ s_{j} $ to $ t_{j} $ , or the integer $ k_{j} $ is greater than the length of this path, print the string '-1' (without quotes) in the $ j $ -th line.

## 样例 #1

### 输入

```
7 7 5
1 2
2 3
1 3
3 4
4 5
5 3
4 6
1 4 2
2 6 1
1 7 3
1 3 2
1 3 5

```

### 输出

```
2
-1
-1
2
-1

```

