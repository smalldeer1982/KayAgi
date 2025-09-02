---
title: "Closest Pair"
layout: "post"
diff: 省选/NOI-
pid: CF1635F
tag: ['树状数组', '单调队列']
---

# Closest Pair

## 题目描述

There are $ n $ weighted points on the $ OX $ -axis. The coordinate and the weight of the $ i $ -th point is $ x_i $ and $ w_i $ , respectively. All points have distinct coordinates and positive weights. Also, $ x_i < x_{i + 1} $ holds for any $ 1 \leq i < n $ .

The weighted distance between $ i $ -th point and $ j $ -th point is defined as $ |x_i - x_j| \cdot (w_i + w_j) $ , where $ |val| $ denotes the absolute value of $ val $ .

You should answer $ q $ queries, where the $ i $ -th query asks the following: Find the minimum weighted distance among all pairs of distinct points among the points in subarray $ [l_i,r_i] $ .

## 输入格式

The first line contains 2 integers $ n $ and $ q $ $ (2 \leq n \leq 3 \cdot 10^5; 1 \leq q \leq 3 \cdot 10^5) $ — the number of points and the number of queries.

Then, $ n $ lines follows, the $ i $ -th of them contains two integers $ x_i $ and $ w_i $ $ (-10^9 \leq x_i \leq 10^9; 1 \leq w_i \leq 10^9) $ — the coordinate and the weight of the $ i $ -th point.

It is guaranteed that the points are given in the increasing order of $ x $ .

Then, $ q $ lines follows, the $ i $ -th of them contains two integers $ l_i $ and $ r_i $ $ (1 \leq l_i < r_i \leq n) $ — the given subarray of the $ i $ -th query.

## 输出格式

For each query output one integer, the minimum weighted distance among all pair of distinct points in the given subarray.

## 说明/提示

For the first query, the minimum weighted distance is between points $ 1 $ and $ 3 $ , which is equal to $ |x_1 - x_3| \cdot (w_1 + w_3) = |-2 - 1| \cdot (2 + 1) = 9 $ .

For the second query, the minimum weighted distance is between points $ 2 $ and $ 3 $ , which is equal to $ |x_2 - x_3| \cdot (w_2 + w_3) = |0 - 1| \cdot (10 + 1) = 11 $ .

For the fourth query, the minimum weighted distance is between points $ 3 $ and $ 4 $ , which is equal to $ |x_3 - x_4| \cdot (w_3 + w_4) = |1 - 9| \cdot (1 + 2) = 24 $ .

## 样例 #1

### 输入

```
5 5
-2 2
0 10
1 1
9 2
12 7
1 3
2 3
1 5
3 5
2 4
```

### 输出

```
9
11
9
24
11
```



---

---
title: "Ciel and Gondolas"
layout: "post"
diff: 省选/NOI-
pid: CF321E
tag: ['动态规划 DP', '单调队列', '凸完全单调性（wqs 二分）']
---

# Ciel and Gondolas

## 题目描述

Fox Ciel is in the Amusement Park. And now she is in a queue in front of the Ferris wheel. There are $ n $ people (or foxes more precisely) in the queue: we use first people to refer one at the head of the queue, and $ n $ -th people to refer the last one in the queue.

There will be $ k $ gondolas, and the way we allocate gondolas looks like this:

- When the first gondolas come, the $ q_{1} $ people in head of the queue go into the gondolas.
- Then when the second gondolas come, the $ q_{2} $ people in head of the remain queue go into the gondolas. ...
- The remain $ q_{k} $ people go into the last ( $ k $ -th) gondolas.

Note that $ q_{1} $ , $ q_{2} $ , ..., $ q_{k} $ must be positive. You can get from the statement that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321E/5aa86331c628d3d47e29fa23648bea351737ffff.png) and $ q_{i}>0 $ .

You know, people don't want to stay with strangers in the gondolas, so your task is to find an optimal allocation way (that is find an optimal sequence $ q $ ) to make people happy. For every pair of people $ i $ and $ j $ , there exists a value $ u_{ij} $ denotes a level of unfamiliar. You can assume $ u_{ij}=u_{ji} $ for all $ i,j $ $ (1<=i,j<=n) $ and $ u_{ii}=0 $ for all $ i $ $ (1<=i<=n) $ . Then an unfamiliar value of a gondolas is the sum of the levels of unfamiliar between any pair of people that is into the gondolas.

A total unfamiliar value is the sum of unfamiliar values for all gondolas. Help Fox Ciel to find the minimal possible total unfamiliar value for some optimal allocation.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=4000 $ and $ 1<=k<=min(n,800) $ ) — the number of people in the queue and the number of gondolas. Each of the following $ n $ lines contains $ n $ integers — matrix $ u $ , ( $ 0<=u_{ij}<=9 $ , $ u_{ij}=u_{ji} $ and $ u_{ii}=0 $ ).

Please, use fast input methods (for example, please use BufferedReader instead of Scanner for Java).

## 输出格式

Print an integer — the minimal possible total unfamiliar value.

## 说明/提示

In the first example, we can allocate people like this: {1, 2} goes into a gondolas, {3, 4, 5} goes into another gondolas.

In the second example, an optimal solution is : {1, 2, 3} | {4, 5, 6} | {7, 8}.

## 样例 #1

### 输入

```
5 2
0 0 1 1 1
0 0 1 1 1
1 1 0 0 0
1 1 0 0 0
1 1 0 0 0

```

### 输出

```
0

```

## 样例 #2

### 输入

```
8 3
0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1
1 1 1 0 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 1 1 0 1 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 0

```

### 输出

```
7

```

## 样例 #3

### 输入

```
3 2
0 2 0
2 0 3
0 3 0

```

### 输出

```
2

```



---

