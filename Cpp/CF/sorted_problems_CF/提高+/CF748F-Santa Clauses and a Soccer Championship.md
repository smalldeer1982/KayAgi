---
title: "Santa Clauses and a Soccer Championship"
layout: "post"
diff: 提高+/省选-
pid: CF748F
tag: []
---

# Santa Clauses and a Soccer Championship

## 题目描述

The country Treeland consists of $ n $ cities connected with $ n-1 $ bidirectional roads in such a way that it's possible to reach every city starting from any other city using these roads. There will be a soccer championship next year, and all participants are Santa Clauses. There are exactly $ 2k $ teams from $ 2k $ different cities.

During the first stage all teams are divided into $ k $ pairs. Teams of each pair play two games against each other: one in the hometown of the first team, and the other in the hometown of the other team. Thus, each of the $ 2k $ cities holds exactly one soccer game. However, it's not decided yet how to divide teams into pairs.

It's also necessary to choose several cities to settle players in. Organizers tend to use as few cities as possible to settle the teams.

Nobody wants to travel too much during the championship, so if a team plays in cities $ u $ and $ v $ , it wants to live in one of the cities on the shortest path between $ u $ and $ v $ (maybe, in $ u $ or in $ v $ ). There is another constraint also: the teams from one pair must live in the same city.

Summarizing, the organizers want to divide $ 2k $ teams into pairs and settle them in the minimum possible number of cities $ m $ in such a way that teams from each pair live in the same city which lies between their hometowns.

## 输入格式

The first line of input contains two integers $ n $ and $ k $ ( $ 2<=n<=2·10^{5},2<=2k<=n $ ) — the number of cities in Treeland and the number of pairs of teams, respectively.

The following $ n-1 $ lines describe roads in Treeland: each of these lines contains two integers $ a $ and $ b $ ( $ 1<=a,b<=n,a≠b $ ) which mean that there is a road between cities $ a $ and $ b $ . It's guaranteed that there is a path between any two cities.

The last line contains $ 2k $ distinct integers $ c_{1},c_{2},...,c_{2k} $ ( $ 1<=c_{i}<=n $ ), where $ c_{i} $ is the hometown of the $ i $ -th team. All these numbers are distinct.

## 输出格式

The first line of output must contain the only positive integer $ m $ which should be equal to the minimum possible number of cities the teams can be settled in.

The second line should contain $ m $ distinct numbers $ d_{1},d_{2},...,d_{m} $ ( $ 1<=d_{i}<=n $ ) denoting the indices of the cities where the teams should be settled.

The $ k $ lines should follow, the $ j $ -th of them should contain $ 3 $ integers $ u_{j} $ , $ v_{j} $ and $ x_{j} $ , where $ u_{j} $ and $ v_{j} $ are the hometowns of the $ j $ -th pair's teams, and $ x_{j} $ is the city they should live in during the tournament. Each of the numbers $ c_{1},c_{2},...,c_{2k} $ should occur in all $ u_{j} $ 's and $ v_{j} $ 's exactly once. Each of the numbers $ x_{j} $ should belong to $ {d_{1},d_{2},...,d_{m}} $ .

If there are several possible answers, print any of them.

## 说明/提示

In the first test the orginizers can settle all the teams in the city number $ 2 $ . The way to divide all teams into pairs is not important, since all requirements are satisfied anyway, because the city $ 2 $ lies on the shortest path between every two cities from $ {2,4,5,6} $ .

## 样例 #1

### 输入

```
6 2
1 2
1 3
2 4
2 5
3 6
2 5 4 6

```

### 输出

```
1
2
5 4 2
6 2 2

```

