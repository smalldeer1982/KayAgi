---
title: "Gripping Story"
layout: "post"
diff: 省选/NOI-
pid: CF198E
tag: []
---

# Gripping Story

## 题目描述

One day Qwerty the Ranger witnessed two transport ships collide with each other. As a result, all contents of their cargo holds scattered around the space. And now Qwerty wants to pick as many lost items as possible to sell them later.

The thing is, both ships had lots of new gravitational grippers, transported to sale. A gripper is a device that can be installed on a spaceship and than draw items in space to itself ("grip") and transport them to the ship's cargo hold.

Overall the crashed ships lost $ n $ gravitational grippers: the $ i $ -th gripper is located at a point with coordinates $ (x_{i},y_{i}) $ . Each gripper has two features — $ p_{i} $ (the power) and $ r_{i} $ (the action radius) and can grip any items with mass of no more than $ p_{i} $ at distance no more than $ r_{i} $ . A gripper itself is an item, too and it has its mass of $ m_{i} $ .

Qwerty's ship is located at point $ (x,y) $ and has an old magnetic gripper installed, its characteristics are $ p $ and $ r $ . There are no other grippers in the ship's cargo holds.

Find the largest number of grippers Qwerty can get hold of. As he picks the items, he can arbitrarily install any gripper in the cargo hold of the ship, including the gripper he has just picked. At any moment of time the ship can have only one active gripper installed. We consider all items and the Qwerty's ship immobile when the ranger picks the items, except for when the gripper moves an item — then the item moves to the cargo holds and the ship still remains immobile. We can assume that the ship's cargo holds have enough room for all grippers. Qwerty can use any gripper he finds or the initial gripper an arbitrary number of times.

## 输入格式

The first line contains five integers $ x $ , $ y $ , $ p $ , $ r $ and $ n $ ( $ -10^{9}<=x,y<=10^{9} $ , $ 1<=p,r<=10^{9} $ , $ 1<=n<=250000 $ ) — the ship's initial position, the initial gripper's features and the number of grippers that got into the space during the collision.

Next $ n $ lines contain the grippers' descriptions: the $ i $ -th line contains five integers $ x_{i} $ , $ y_{i} $ , $ m_{i} $ , $ p_{i} $ , $ r_{i} $ ( $ -10^{9}<=x_{i},y_{i}<=10^{9} $ , $ 1<=m_{i},p_{i},r_{i}<=10^{9} $ ) — the $ i $ -th gripper's coordinates and features.

It is guaranteed that all grippers are located at different points. No gripper is located at the same point with Qwerty's ship.

## 输出格式

Print a single number — the maximum number of grippers Qwerty can draw to his ship. You do not need to count the initial old magnet gripper.

## 说明/提示

In the first sample you should get the second gripper, then use the second gripper to get the first one, then use the first gripper to get the fourth one. You cannot get neither the third gripper as it is too heavy, nor the fifth one as it is too far away.

## 样例 #1

### 输入

```
0 0 5 10 5
5 4 7 11 5
-7 1 4 7 8
0 2 13 5 6
2 -3 9 3 4
13 5 1 9 9

```

### 输出

```
3

```

