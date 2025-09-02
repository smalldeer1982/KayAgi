---
title: "Points on Plane"
layout: "post"
diff: 普及-
pid: CF1809B
tag: []
---

# Points on Plane

## 题目描述

You are given a two-dimensional plane, and you need to place $ n $ chips on it.

You can place a chip only at a point with integer coordinates. The cost of placing a chip at the point $ (x, y) $ is equal to $ |x| + |y| $ (where $ |a| $ is the absolute value of $ a $ ).

The cost of placing $ n $ chips is equal to the maximum among the costs of each chip.

You need to place $ n $ chips on the plane in such a way that the Euclidean distance between each pair of chips is strictly greater than $ 1 $ , and the cost is the minimum possible.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Next $ t $ cases follow.

The first and only line of each test case contains one integer $ n $ ( $ 1 \le n \le 10^{18} $ ) — the number of chips you need to place.

## 输出格式

For each test case, print a single integer — the minimum cost to place $ n $ chips if the distance between each pair of chips must be strictly greater than $ 1 $ .

## 说明/提示

In the first test case, you can place the only chip at point $ (0, 0) $ with total cost equal to $ 0 + 0 = 0 $ .

In the second test case, you can, for example, place chips at points $ (-1, 0) $ , $ (0, 1) $ and $ (1, 0) $ with costs $ |-1| + |0| = 1 $ , $ |0| + |1| = 1 $ and $ |0| + |1| = 1 $ . Distance between each pair of chips is greater than $ 1 $ (for example, distance between $ (-1, 0) $ and $ (0, 1) $ is equal to $ \sqrt{2} $ ). The total cost is equal to $ \max(1, 1, 1) = 1 $ .

In the third test case, you can, for example, place chips at points $ (-1, -1) $ , $ (-1, 1) $ , $ (1, 1) $ , $ (0, 0) $ and $ (0, 2) $ . The total cost is equal to $ \max(2, 2, 2, 0, 2) = 2 $ .

## 样例 #1

### 输入

```
4
1
3
5
975461057789971042
```

### 输出

```
0
1
2
987654321
```

