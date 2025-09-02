---
title: "Gerald and Path"
layout: "post"
diff: 省选/NOI-
pid: CF559E
tag: []
---

# Gerald and Path

## 题目描述

The main walking trail in Geraldion is absolutely straight, and it passes strictly from the north to the south, it is so long that no one has ever reached its ends in either of the two directions. The Geraldionians love to walk on this path at any time, so the mayor of the city asked the Herald to illuminate this path with a few spotlights. The spotlights have already been delivered to certain places and Gerald will not be able to move them. Each spotlight illuminates a specific segment of the path of the given length, one end of the segment is the location of the spotlight, and it can be directed so that it covers the segment to the south or to the north of spotlight.

The trail contains a monument to the mayor of the island, and although you can walk in either directions from the monument, no spotlight is south of the monument.

You are given the positions of the spotlights and their power. Help Gerald direct all the spotlights so that the total length of the illuminated part of the path is as much as possible.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the number of spotlights. Each of the $ n $ lines contains two space-separated integers, $ a_{i} $ and $ l_{i} $ ( $ 0<=a_{i}<=10^{8} $ , $ 1<=l_{i}<=10^{8} $ ). Number $ a_{i} $ shows how much further the $ i $ -th spotlight to the north, and number $ l_{i} $ shows the length of the segment it illuminates.

It is guaranteed that all the $ a_{i} $ 's are distinct.

## 输出格式

Print a single integer — the maximum total length of the illuminated part of the path.

## 样例 #1

### 输入

```
3
1 1
2 2
3 3

```

### 输出

```
5

```

## 样例 #2

### 输入

```
4
1 2
3 3
4 3
6 2

```

### 输出

```
9

```

