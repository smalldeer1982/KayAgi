---
title: "Gregor and the Odd Cows (Easy)"
layout: "post"
diff: 提高+/省选-
pid: CF1548D1
tag: []
---

# Gregor and the Odd Cows (Easy)

## 题目描述

This is the easy version of the problem. The only difference from the hard version is that in this version all coordinates are even.

There are $ n $ fence-posts at distinct coordinates on a plane. It is guaranteed that no three fence posts lie on the same line.

There are an infinite number of cows on the plane, one at every point with integer coordinates.

Gregor is a member of the Illuminati, and wants to build a triangular fence, connecting $ 3 $ distinct existing fence posts. A cow strictly inside the fence is said to be enclosed. If there are an odd number of enclosed cows and the area of the fence is an integer, the fence is said to be interesting.

Find the number of interesting fences.

## 输入格式

The first line contains the integer $ n $ ( $ 3 \le n \le 6000 $ ), the number of fence posts which Gregor can choose to form the vertices of a fence.

Each of the next $ n $ line contains two integers $ x $ and $ y $ ( $ 0 \le x,y \le 10^7 $ , $ x $ and $ y $ are even), where $ (x,y) $ is the coordinate of a fence post. All fence posts lie at distinct coordinates. No three fence posts are on the same line.

## 输出格式

Print a single integer, the number of interesting fences. Two fences are considered different if they are constructed with a different set of three fence posts.

## 说明/提示

In the first example, there is only $ 1 $ fence. That fence is interesting since its area is $ 4 $ and there is $ 1 $ enclosed cow, marked in red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1548D1/0403ceae6e73450fcff5ed53159c4a8d4ef6577c.png)In the second example, there are $ 3 $ interesting fences.

- $ (0,0) $ — $ (30,14) $ — $ (2,10) $
- $ (2,16) $ — $ (30,14) $ — $ (2,10) $
- $ (30,14) $ — $ (4,6) $ — $ (2,10) $

## 样例 #1

### 输入

```
3
0 0
2 0
0 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
0 0
2 16
30 14
4 6
2 10
```

### 输出

```
3
```

