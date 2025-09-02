---
title: "Mice and Holes"
layout: "post"
diff: 提高+/省选-
pid: CF797F
tag: []
---

# Mice and Holes

## 题目描述

One day Masha came home and noticed $ n $ mice in the corridor of her flat. Of course, she shouted loudly, so scared mice started to run to the holes in the corridor.

The corridor can be represeted as a numeric axis with $ n $ mice and $ m $ holes on it. $ i $ th mouse is at the coordinate $ x_{i} $ , and $ j $ th hole — at coordinate $ p_{j} $ . $ j $ th hole has enough room for $ c_{j} $ mice, so not more than $ c_{j} $ mice can enter this hole.

What is the minimum sum of distances that mice have to go through so that they all can hide in the holes? If $ i $ th mouse goes to the hole $ j $ , then its distance is $ |x_{i}-p_{j}| $ .

Print the minimum sum of distances.

## 输入格式

The first line contains two integer numbers $ n $ , $ m $ ( $ 1<=n,m<=5000 $ ) — the number of mice and the number of holes, respectively.

The second line contains $ n $ integers $ x_{1},x_{2},...,x_{n} $ ( $ -10^{9}<=x_{i}<=10^{9} $ ), where $ x_{i} $ is the coordinate of $ i $ th mouse.

Next $ m $ lines contain pairs of integer numbers $ p_{j},c_{j} $ ( $ -10^{9}<=p_{j}<=10^{9},1<=c_{j}<=5000 $ ), where $ p_{j} $ is the coordinate of $ j $ th hole, and $ c_{j} $ is the maximum number of mice that can hide in the hole $ j $ .

## 输出格式

Print one integer number — the minimum sum of distances. If there is no solution, print -1 instead.

## 样例 #1

### 输入

```
4 5
6 2 8 9
3 6
2 1
3 6
4 7
4 7

```

### 输出

```
11

```

## 样例 #2

### 输入

```
7 2
10 20 30 40 50 45 35
-1000000000 10
1000000000 1

```

### 输出

```
7000000130

```

