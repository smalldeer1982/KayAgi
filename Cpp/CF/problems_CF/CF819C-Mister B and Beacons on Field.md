---
title: "Mister B and Beacons on Field"
layout: "post"
diff: 省选/NOI-
pid: CF819C
tag: []
---

# Mister B and Beacons on Field

## 题目描述

Mister B has a house in the middle of a giant plain field, which attracted aliens life. For convenience, aliens specified the Cartesian coordinate system on the field in such a way that Mister B's house has coordinates $ (0,0) $ . After that they sent three beacons to the field, but something went wrong. One beacon was completely destroyed, while the other two landed in positions with coordinates $ (m,0) $ and $ (0,n) $ , respectively, but shut down.

Mister B was interested in this devices, so he decided to take them home. He came to the first beacon, placed at $ (m,0) $ , lifted it up and carried the beacon home choosing the shortest path. After that he came to the other beacon, placed at $ (0,n) $ , and also carried it home choosing the shortest path. When first beacon was lifted up, the navigation system of the beacons was activated.

Partially destroyed navigation system started to work in following way.

At time moments when both survived beacons are at points with integer coordinates the system tries to find a location for the third beacon. It succeeds if and only if there is a point with integer coordinates such that the area of the triangle formed by the two survived beacons and this point is equal to $ s $ . In this case the system sends a packet of information with beacon positions to aliens, otherwise it doesn't.

Compute how many packets of information system sent while Mister B was moving the beacons.

## 输入格式

The first line contains one integer $ t $ ( $ 1<=t<=1000 $ ) — the number of test cases. The next $ 3·t $ lines describe $ t $ test cases.

Every test case is described in three lines as follows. Note that each parameter is given as a product of three factors.

The first line of a test case contains three space-separated integers: $ n_{1} $ , $ n_{2} $ , $ n_{3} $ ( $ 1<=n_{i}<=10^{6} $ ) such that $ n=n_{1}·n_{2}·n_{3} $ .

The second line contains three space-separated integers: $ m_{1} $ , $ m_{2} $ , $ m_{3} $ ( $ 1<=m_{i}<=10^{6} $ ) such that $ m=m_{1}·m_{2}·m_{3} $ .

The third line contains three space-separated integers: $ s_{1} $ , $ s_{2} $ , $ s_{3} $ ( $ 1<=s_{i}<=10^{6} $ ) such that $ s=s_{1}·s_{2}·s_{3} $ .

Note that for hacks only tests with $ t=1 $ allowed.

## 输出格式

Print $ t $ integers one per line — the answers for each test.

## 说明/提示

First test case contains the following beacon positions: $ (2,0) $ and $ (0,2) $ , $ s=3 $ . The following packets could be sent: $ ((2,0),(0,2),(-1,0)) $ , $ ((1,0),(0,2),(4,0)) $ , $ ((0,0),(0,2),(3,1)) $ , $ ((0,0),(0,1),(-6,0)) $ , where $ (b_{1},b_{2},p) $ has next description: $ b_{1} $ — first beacon position, $ b_{2} $ — second beacon position, $ p $ — some generated point.

Second test case contains the following beacon initial positions: $ (4,0) $ and $ (0,5) $ , $ s=2 $ . The following packets could be sent: $ ((4,0),(0,5),(0,4)) $ , $ ((3,0),(0,5),(2,3)) $ , $ ((2,0),(0,5),(2,2)) $ , $ ((1,0),(0,5),(1,4)) $ , $ ((0,0),(0,4),(0,-1)) $ , $ ((0,0),(0,2),(2,0)) $ , $ ((0,0),(0,1),(4,0)) $ .

## 样例 #1

### 输入

```
3
2 1 1
2 1 1
1 1 3
1 5 1
2 2 1
1 1 2
10 6 18
2 103 2
13 1 13

```

### 输出

```
4
7
171

```

