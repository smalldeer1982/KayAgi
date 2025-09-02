---
title: "Rendez-vous de Marian et Robin"
layout: "post"
diff: 普及+/提高
pid: CF2014E
tag: ['最短路']
---

# Rendez-vous de Marian et Robin

## 题目描述

In the humble act of meeting, joy doth unfold like a flower in bloom.



Absence makes the heart grow fonder. Marian sold her last ware at the Market at the same time Robin finished training at the Major Oak. They couldn't wait to meet, so they both start without delay.

The travel network is represented as $ n $ vertices numbered from $ 1 $ to $ n $ and $ m $ edges. The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ , and takes $ w_i $ seconds to travel (all $ w_i $ are even). Marian starts at vertex $ 1 $ (Market) and Robin starts at vertex $ n $ (Major Oak).

In addition, $ h $ of the $ n $ vertices each has a single horse available. Both Marian and Robin are capable riders, and could mount horses in no time (i.e. in $ 0 $ seconds). Travel times are halved when riding. Once mounted, a horse lasts the remainder of the travel. Meeting must take place on a vertex (i.e. not on an edge). Either could choose to wait on any vertex.

Output the earliest time Robin and Marian can meet. If vertices $ 1 $ and $ n $ are disconnected, output $ -1 $ as the meeting is cancelled.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1\leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case consists of three integers $ n $ , $ m $ , $ h $ ( $ 2 \le n \le 2 \cdot 10^5, \;1 \le m \le 2 \cdot 10^5, \; 1 \le h \le n $ ) — the number of vertices, the number of edges and the number of vertices that have a single horse.

The second line of each test case contains $ h $ distinct integers $ a_1, a_2, \ldots, a_h $ ( $ 1 \le a_i \le n $ ) — the vertices that have a single horse available.

Then follow $ m $ lines of each test case, each with three integers $ u_i $ , $ v_i $ , $ w_i $ ( $ 1\le u_i,v_i \le n, \; 2\le w_i \le 10^6 $ ) — meaning that there is an edge between vertices $ u_i $ and $ v_i $ with travel cost $ w_i $ seconds without a horse.

There are no self loops or multiple edges. By good fortune, all $ w_i $ are even integers.

It is guaranteed that the sums of both $ n $ and $ m $ over all test cases do not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer, the earliest time Robin and Marian can meet. If it is impossible for them to meet, output $ -1 $ .

## 说明/提示

In the first test case, Marian rides from vertex $ 1 $ to vertex $ 2 $ , Robin waits.

In the second test case, vertices $ 1 $ and $ 3 $ are not connected.

In the third test case, both Marian and Robin travel to vertex $ 2 $ to meet.

In the fourth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides to vertex $ 3 $ to meet Robin.

In the fifth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides back to vertex $ 1 $ and then to vertex $ 3 $ . Robin waits.

## 样例 #1

### 输入

```
6
2 1 1
1
1 2 10
3 1 2
2 3
1 2 10
3 3 1
2
1 2 4
1 3 10
2 3 6
4 3 2
2 3
1 2 10
2 3 18
3 4 16
3 2 1
2
1 2 4
1 3 16
7 7 1
3
1 5 2
2 6 12
1 2 12
6 4 8
7 3 4
6 3 4
7 6 4
```

### 输出

```
5
-1
6
19
14
12
```

