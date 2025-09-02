---
title: "Airport"
layout: "post"
diff: 普及-
pid: CF218B
tag: []
---

# Airport

## 题目描述

Lolek and Bolek are about to travel abroad by plane. The local airport has a special "Choose Your Plane" offer. The offer's conditions are as follows:

- it is up to a passenger to choose a plane to fly on;
- if the chosen plane has $ x $ $ (x&gt;0) $ empty seats at the given moment, then the ticket for such a plane costs $ x $ zlotys (units of Polish currency).

The only ticket office of the airport already has a queue of $ n $ passengers in front of it. Lolek and Bolek have not stood in the queue yet, but they are already wondering what is the maximum and the minimum number of zlotys the airport administration can earn if all $ n $ passengers buy tickets according to the conditions of this offer?

The passengers buy tickets in turn, the first person in the queue goes first, then goes the second one, and so on up to $ n $ -th person.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n,m<=1000) $ — the number of passengers in the queue and the number of planes in the airport, correspondingly. The next line contains $ m $ integers $ a_{1},a_{2},...,a_{m} $ $ (1<=a_{i}<=1000) $ — $ a_{i} $ stands for the number of empty seats in the $ i $ -th plane before the ticket office starts selling tickets.

The numbers in the lines are separated by a space. It is guaranteed that there are at least $ n $ empty seats in total.

## 输出格式

Print two integers — the maximum and the minimum number of zlotys that the airport administration can earn, correspondingly.

## 说明/提示

In the first test sample the number of passengers is equal to the number of empty seats, so regardless of the way the planes are chosen, the administration will earn the same sum.

In the second sample the sum is maximized if the 1-st person in the queue buys a ticket to the 1-st plane, the 2-nd person — to the 2-nd plane, the 3-rd person — to the 3-rd plane, the 4-th person — to the 1-st plane. The sum is minimized if the 1-st person in the queue buys a ticket to the 1-st plane, the 2-nd person — to the 1-st plane, the 3-rd person — to the 2-nd plane, the 4-th person — to the 2-nd plane.

## 样例 #1

### 输入

```
4 3
2 1 1

```

### 输出

```
5 5

```

## 样例 #2

### 输入

```
4 3
2 2 2

```

### 输出

```
7 6

```

