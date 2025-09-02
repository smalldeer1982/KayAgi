---
title: "Distance and Axis"
layout: "post"
diff: 入门
pid: CF1401A
tag: []
---

# Distance and Axis

## 题目描述

We have a point $ A $ with coordinate $ x = n $ on $ OX $ -axis. We'd like to find an integer point $ B $ (also on $ OX $ -axis), such that the absolute difference between the distance from $ O $ to $ B $ and the distance from $ A $ to $ B $ is equal to $ k $ .

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1401A/f02fe75a4f026973d3469bfb5deb655f92260259.png)The description of the first test case. Since sometimes it's impossible to find such point $ B $ , we can, in one step, increase or decrease the coordinate of $ A $ by $ 1 $ . What is the minimum number of steps we should do to make such point $ B $ exist?

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le       6000 $ ) — the number of test cases.

The only line of each test case contains two integers $ n $ and $ k $ ( $ 0 \le n, k \le 10^6 $ ) — the initial position of point $ A $ and desirable absolute difference.

## 输出格式

For each test case, print the minimum number of steps to make point $ B $ exist.

## 说明/提示

In the first test case (picture above), if we set the coordinate of $ B $ as $ 2 $ then the absolute difference will be equal to $ |(2 - 0) - (4 - 2)| = 0 $ and we don't have to move $ A $ . So the answer is $ 0 $ .

In the second test case, we can increase the coordinate of $ A $ by $ 3 $ and set the coordinate of $ B $ as $ 0 $ or $ 8 $ . The absolute difference will be equal to $ |8 - 0| =       8 $ , so the answer is $ 3 $ .

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1401A/e6ebf66babb223e2d9a48c8c52dd23c01a8fd602.png)

## 样例 #1

### 输入

```
6
4 0
5 8
0 1000000
0 0
1 0
1000000 1000000
```

### 输出

```
0
3
1000000
0
1
0
```

