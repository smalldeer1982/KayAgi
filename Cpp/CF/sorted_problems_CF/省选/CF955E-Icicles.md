---
title: "Icicles"
layout: "post"
diff: 省选/NOI-
pid: CF955E
tag: []
---

# Icicles

## 题目描述

Andrew's favourite Krakozyabra has recenly fled away and now he's eager to bring it back!

At the moment the refugee is inside an icy cave with $ n $ icicles dangling from the ceiling located in integer coordinates numbered from $ 1 $ to $ n $ . The distance between floor and the $ i $ -th icicle is equal to $ a_{i} $ .

Andrew is free to choose an arbitrary integer point $ T $ in range from $ 1 $ to $ n $ inclusive and at time instant $ 0 $ launch a sound wave spreading into both sides (left and right) at the speed of one point per second. Any icicle touched by the wave starts falling at the same speed (that means that in a second the distance from floor to icicle decreases by one but cannot become less that zero). While distance from icicle to floor is more than zero, it is considered passable; as soon as it becomes zero, the icicle blocks the path and prohibits passing.

Krakozyabra is initially (i.e. at time instant $ 0 $ ) is located at point ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955E/6201067a97da7a97c457211e210f5a8e998bdde9.png) and starts running in the right direction at the speed of one point per second. You can assume that events in a single second happen in the following order: first Krakozyabra changes its position, and only then the sound spreads and icicles fall; in particular, that means that if Krakozyabra is currently at point ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955E/1c5af17636ba64dd5732c7aa8ec584757d0bd2cf.png) and the falling (i.e. already touched by the sound wave) icicle at point $ i $ is $ 1 $ point from the floor, then Krakozyabra will pass it and find itself at ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955E/698ff77408e1322df2c02364658180d6abdd0230.png) and only after that the icicle will finally fall and block the path.

Krakozyabra is considered entrapped if there are fallen (i.e. with $ a_{i}=0 $ ) icicles both to the left and to the right of its current position. Help Andrew find the minimum possible time it takes to entrap Krakozyabra by choosing the optimal value of $ T $ or report that this mission is impossible.

## 输入格式

The first line contains the number of icicles $ n $ $ (2<=n<=10^{5}) $ .

The next line contains $ n $ space-separated numbers $ a_{i} $ $ (1<=a_{i}<=10^{5}) $ — the distances from floor to icicles.

## 输出格式

Print an only integer — the minimum time it takes to entrap Krakozyabra between two fallen icicles. If it is impossible, print $ -1 $ .

## 说明/提示

In sample case one it's optimal to launch the sound wave from point $ 3 $ . Then in two seconds icicles $ 1 $ and $ 5 $ will start falling, and in one more seconds they will block the paths. Krakozyabra will be located at ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF955E/6a876c63f063c77b3b3f7a4894559278a4f9c115.png) at that time. Note that icicle number $ 3 $ will also be fallen, so there will actually be two icicles blocking the path to the left.

In sample case two it is optimal to launch the wave from point $ 2 $ and entrap Krakozyabra in $ 2 $ seconds.

In sample case four the answer is impossible.

## 样例 #1

### 输入

```
5
1 4 3 5 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
1 2 1 1

```

### 输出

```
2

```

## 样例 #3

### 输入

```
2
2 1

```

### 输出

```
3

```

## 样例 #4

### 输入

```
2
1 2

```

### 输出

```
-1

```

