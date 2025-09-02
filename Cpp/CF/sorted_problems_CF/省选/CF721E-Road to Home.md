---
title: "Road to Home"
layout: "post"
diff: 省选/NOI-
pid: CF721E
tag: []
---

# Road to Home

## 题目描述

Once Danil the student was returning home from tram stop lately by straight road of length $ L $ . The stop is located at the point $ x=0 $ , but the Danil's home — at the point $ x=L $ . Danil goes from $ x=0 $ to $ x=L $ with a constant speed and does not change direction of movement.

There are $ n $ street lights at the road, each of which lights some continuous segment of the road. All of the $ n $ lightened segments do not share common points.

Danil loves to sing, thus he wants to sing his favourite song over and over again during his walk. As soon as non-lightened segments of the road scare him, he sings only when he goes through the lightened segments.

Danil passes distance $ p $ while performing his favourite song once. Danil can't start another performance if the segment passed while performing is not fully lightened. Moreover, if Danil has taken a pause between two performances, he is not performing while not having passed a segment of length at least $ t $ . Formally,

1. Danil can start single performance at a point $ x $ only if every point of segment $ [x,x+p] $ is lightened;
2. If Danil has finished performing at a point $ x+p $ , then the next performance can be started only at a point $ y $ such that $ y=x+p $ or $ y>=x+p+t $ satisfying the statement under the point $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF721E/3f2808218281075db371b77f474d7f1e009cc138.png)Blue half-circles denote performances. Please note that just after Danil has taken a pause in performing, he has not sang for a path of length of at least $ t $ .Determine how many times Danil can perform his favourite song during his walk from $ x=0 $ to $ x=L $ .

Please note that Danil does not break a single performance, thus, started singing another time, he finishes singing when having a segment of length of $ p $ passed from the performance start point.

## 输入格式

The first line of the input contains four integers $ L $ , $ n $ , $ p $ and $ t $ ( $ 1<=L<=10^{9} $ , $ 0<=n<=100000 $ , $ 1<=p<=10^{9} $ , $ 1<=t<=10^{9} $ ) — the length of the Danil's path, the number of street lights at the road, the distance Danil passes while doing single performance and the minimum distance of pause respectively.

The next $ n $ lines describe segments lightened by street lights. $ i $ -th of them contains two integers $ l_{i},r_{i} $ ( $ 0<=l_{i}&lt;r_{i}<=L $ ) — the endpoints of the segment lightened by $ i $ -th street light. It is guaranteed that no two segments are intersecting, nesting, or touching each other. The segments are given in the order from left to right.

## 输出格式

Print the only integer — the maximum number of performances of Danil's favourite song on the path from $ x=0 $ to $ x=L $ .

## 说明/提示

The first sample case is just about corresponding to the picture from the statement.

## 样例 #1

### 输入

```
17 2 2 6
0 9
13 17

```

### 输出

```
5

```

## 样例 #2

### 输入

```
12 2 2 2
0 5
6 11

```

### 输出

```
4

```

## 样例 #3

### 输入

```
12 2 2 4
0 5
6 11

```

### 输出

```
3

```

