---
title: "Iron Man"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF704E
tag: []
---

# Iron Man

## 题目描述

Tony Stark is playing a game with his suits (they have auto-pilot now). He lives in Malibu. Malibu has $ n $ junctions numbered from $ 1 $ to $ n $ , connected with $ n-1 $ roads. One can get from a junction to any other junction using these roads (graph of Malibu forms a tree).

Tony has $ m $ suits. There's a special plan for each suit. The $ i $ -th suit will appear at the moment of time $ t_{i} $ in the junction $ v_{i} $ , and will move to junction $ u_{i} $ using the shortest path between $ v_{i} $ and $ u_{i} $ with the speed $ c_{i} $ roads per second (passing a junctions takes no time), and vanishing immediately when arriving at $ u_{i} $ (if it reaches $ u_{i} $ in time $ q $ , it's available there at moment $ q $ , but not in further moments). Also, suits move continuously (for example if $ v_{i}≠u_{i} $ , at time ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704E/339d93c52506ae3cb849704e1d4a746c6a07adbd.png) it's in the middle of a road. Please note that if $ v_{i}=u_{i} $ it means the suit will be at junction number $ v_{i} $ only at moment $ t_{i} $ and then it vanishes.

An explosion happens if at any moment of time two suits share the same exact location (it may be in a junction or somewhere on a road; while appearing, vanishing or moving).

Your task is to tell Tony the moment of the the first explosion (if there will be any).

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=100000 $ ) — the number of junctions and the number of suits respectively.

The next $ n-1 $ lines contain the roads descriptions. Each line contains two integers $ a_{i} $ and $ b_{i} $ — endpoints of the $ i $ -th road ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ ).

The next $ m $ lines contain the suit descriptions. The $ i $ -th of them contains four integers $ t_{i} $ , $ c_{i} $ , $ v_{i} $ and $ u_{i} $ ( $ 0<=t_{i}<=10000,1<=c_{i}<=10000 $ , $ 1<=v_{i},u_{i}<=n $ ), meaning the $ i $ -th suit will appear at moment of time $ t_{i} $ at the junction $ v_{i} $ and will move to the junction $ u_{i} $ with a speed $ c_{i} $ roads per second.

## 输出格式

If there would be no explosions at all, print -1 in the first and only line of output.

Otherwise print the moment of the first explosion.

Your answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
6 4
2 5
6 5
3 6
4 6
4 1
27 6 1 3
9 5 1 6
27 4 3 4
11 29 2 6

```

### 输出

```
27.3

```

## 样例 #2

### 输入

```
6 4
3 1
4 5
6 4
6 1
2 6
16 4 4 5
13 20 6 2
3 16 4 5
28 5 3 5

```

### 输出

```
-1

```

