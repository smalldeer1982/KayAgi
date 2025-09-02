---
title: "Wizard's Tour"
layout: "post"
diff: 省选/NOI-
pid: CF858F
tag: []
---

# Wizard's Tour

## 题目描述

All Berland residents are waiting for an unprecedented tour of wizard in his Blue Helicopter over the cities of Berland!

It is well-known that there are $ n $ cities in Berland, some pairs of which are connected by bidirectional roads. Each pair of cities is connected by no more than one road. It is not guaranteed that the road network is connected, i.e. it is possible that you can't reach some city from some other.

The tour will contain several episodes. In each of the episodes:

- the wizard will disembark at some city $ x $ from the Helicopter;
- he will give a performance and show a movie for free at the city $ x $ ;
- he will drive to some neighboring city $ y $ using a road;
- he will give a performance and show a movie for free at the city $ y $ ;
- he will drive to some neighboring to $ y $ city $ z $ ;
- he will give a performance and show a movie for free at the city $ z $ ;
- he will embark the Helicopter and fly away from the city $ z $ .

It is known that the wizard doesn't like to use roads, so he agrees to use each road at most once (regardless of direction). In other words, for road between $ a $ and $ b $ he only can drive once from $ a $ to $ b $ , or drive once from $ b $ to $ a $ , or do not use this road at all.

The wizards wants to plan as many episodes as possible without violation the above rules. Help the wizard!

Please note that the wizard can visit the same city multiple times, the restriction is on roads only.

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 1<=n<=2·10^{5} $ , $ 0<=m<=2·10^{5} $ ) — the number of cities and the number of roads in Berland, respectively.

The roads description follow, one in each line. Each description is a pair of two integers $ a_{i},b_{i} $ ( $ 1<=a_{i},b_{i}<=n $ , $ a_{i}≠b_{i} $ ), where $ a_{i} $ and $ b_{i} $ are the ids of the cities connected by the $ i $ -th road. It is guaranteed that there are no two roads connecting the same pair of cities. Every road is bidirectional. The cities are numbered from $ 1 $ to $ n $ .

It is possible that the road network in Berland is not connected.

## 输出格式

In the first line print $ w $ — the maximum possible number of episodes. The next $ w $ lines should contain the episodes in format $ x $ , $ y $ , $ z $ — the three integers denoting the ids of the cities in the order of the wizard's visits.

## 样例 #1

### 输入

```
4 5
1 2
3 2
2 4
3 4
4 1

```

### 输出

```
2
1 4 2
4 3 2

```

## 样例 #2

### 输入

```
5 8
5 3
1 2
4 5
5 1
2 5
4 3
1 4
3 2

```

### 输出

```
4
1 4 5
2 3 4
1 5 3
5 2 1

```

