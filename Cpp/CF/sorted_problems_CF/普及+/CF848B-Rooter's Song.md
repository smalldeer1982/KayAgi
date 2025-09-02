---
title: "Rooter's Song"
layout: "post"
diff: 普及+/提高
pid: CF848B
tag: ['模拟']
---

# Rooter's Song

## 题目描述

Wherever the destination is, whoever we meet, let's render this song together.

On a Cartesian coordinate plane lies a rectangular stage of size $ w×h $ , represented by a rectangle with corners $ (0,0) $ , $ (w,0) $ , $ (w,h) $ and $ (0,h) $ . It can be seen that no collisions will happen before one enters the stage.

On the sides of the stage stand $ n $ dancers. The $ i $ -th of them falls into one of the following groups:

- Vertical: stands at $ (x_{i},0) $ , moves in positive $ y $ direction (upwards);
- Horizontal: stands at $ (0,y_{i}) $ , moves in positive $ x $ direction (rightwards).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/78a4617a270ecba0555a87f4deb825cf1f501330.png)According to choreography, the $ i $ -th dancer should stand still for the first $ t_{i} $ milliseconds, and then start moving in the specified direction at $ 1 $ unit per millisecond, until another border is reached. It is guaranteed that no two dancers have the same group, position and waiting time at the same time.

When two dancers collide (i.e. are on the same point at some time when both of them are moving), they immediately exchange their moving directions and go on.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/14a342567b0e0e96e2854bafb4e39a8b293ebae4.png)Dancers stop when a border of the stage is reached. Find out every dancer's stopping position.

## 输入格式

The first line of input contains three space-separated positive integers $ n $ , $ w $ and $ h $ ( $ 1<=n<=100000 $ , $ 2<=w,h<=100000 $ ) — the number of dancers and the width and height of the stage, respectively.

The following $ n $ lines each describes a dancer: the $ i $ -th among them contains three space-separated integers $ g_{i} $ , $ p_{i} $ , and $ t_{i} $ ( $ 1<=g_{i}<=2 $ , $ 1<=p_{i}<=99999 $ , $ 0<=t_{i}<=100000 $ ), describing a dancer's group $ g_{i} $ ( $ g_{i}=1 $ — vertical, $ g_{i}=2 $ — horizontal), position, and waiting time. If $ g_{i}=1 $ then $ p_{i}=x_{i} $ ; otherwise $ p_{i}=y_{i} $ . It's guaranteed that $ 1<=x_{i}<=w-1 $ and $ 1<=y_{i}<=h-1 $ . It is guaranteed that no two dancers have the same group, position and waiting time at the same time.

## 输出格式

Output $ n $ lines, the $ i $ -th of which contains two space-separated integers $ (x_{i},y_{i}) $ — the stopping position of the $ i $ -th dancer in the input.

## 说明/提示

The first example corresponds to the initial setup in the legend, and the tracks of dancers are marked with different colours in the following figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/d441e2a826ff927d107333215574de12d2f00a07.png)In the second example, no dancers collide.

## 样例 #1

### 输入

```
8 10 8
1 1 10
1 4 13
1 7 1
1 8 2
2 2 0
2 5 14
2 6 0
2 6 1

```

### 输出

```
4 8
10 5
8 8
10 6
10 2
1 8
7 8
10 6

```

## 样例 #2

### 输入

```
3 2 3
1 1 2
2 1 1
1 1 5

```

### 输出

```
1 3
2 1
1 3

```

