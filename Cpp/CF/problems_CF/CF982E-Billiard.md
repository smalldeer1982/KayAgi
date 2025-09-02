---
title: "Billiard"
layout: "post"
diff: 提高+/省选-
pid: CF982E
tag: []
---

# Billiard

## 题目描述

Consider a [billiard table](https://en.wikipedia.org/wiki/Billiard_table) of rectangular size $ n \times m $ with four pockets. Let's introduce a coordinate system with the origin at the lower left corner (see the picture).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF982E/5400ec264949b612eb9900ddf2189fccb1a2c217.png)There is one ball at the point $ (x, y) $ currently. Max comes to the table and strikes the ball. The ball starts moving along a line that is parallel to one of the axes or that makes a $ 45^{\circ} $ angle with them. We will assume that:

1. the angles between the directions of the ball before and after a collision with a side are equal,
2. the ball moves indefinitely long, it only stops when it falls into a pocket,
3. the ball can be considered as a point, it falls into a pocket if and only if its coordinates coincide with one of the pockets,
4. initially the ball is not in a pocket.

Note that the ball can move along some side, in this case the ball will just fall into the pocket at the end of the side.

Your task is to determine whether the ball will fall into a pocket eventually, and if yes, which of the four pockets it will be.

## 输入格式

The only line contains $ 6 $ integers $ n $ , $ m $ , $ x $ , $ y $ , $ v_x $ , $ v_y $ ( $ 1 \leq n, m \leq 10^9 $ , $ 0 \leq x \leq n $ ; $ 0 \leq y \leq m $ ; $ -1 \leq v_x, v_y \leq 1 $ ; $ (v_x, v_y) \neq (0, 0) $ ) — the width of the table, the length of the table, the $ x $ -coordinate of the initial position of the ball, the $ y $ -coordinate of the initial position of the ball, the $ x $ -component of its initial speed and the $ y $ -component of its initial speed, respectively. It is guaranteed that the ball is not initially in a pocket.

## 输出格式

Print the coordinates of the pocket the ball will fall into, or $ -1 $ if the ball will move indefinitely.

## 说明/提示

The first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF982E/69be840146adfcf731c5725a9e0b894673e7da29.png)The second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF982E/a92c4ee568a643301b20d63f7451b437aa813098.png)In the third sample the ball will never change its $ y $ coordinate, so the ball will never fall into a pocket.

## 样例 #1

### 输入

```
4 3 2 2 -1 1

```

### 输出

```
0 0
```

## 样例 #2

### 输入

```
4 4 2 0 1 1

```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 10 10 1 -1 0

```

### 输出

```
-1
```

