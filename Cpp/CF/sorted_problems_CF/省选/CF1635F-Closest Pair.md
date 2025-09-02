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

