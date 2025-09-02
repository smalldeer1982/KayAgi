---
title: "Bob and stages"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF852H
tag: []
---

# Bob and stages

## 题目描述

The citizens of BubbleLand are celebrating their 10th anniversary so they decided to organize a big music festival. Bob got a task to invite $ N $ famous singers who would sing on the fest. He was too busy placing stages for their performances that he totally forgot to write the invitation e-mails on time, and unfortunately he only found $ K $ available singers. Now there are more stages than singers, leaving some of the stages empty. Bob would not like if citizens of BubbleLand noticed empty stages and found out that he was irresponsible.

Because of that he decided to choose exactly $ K $ stages that form a convex set, make large posters as edges of that convex set and hold festival inside. While those large posters will make it impossible for citizens to see empty stages outside Bob still needs to make sure they don't see any of the empty stages inside that area.

Since lots of people are coming, he would like that the festival area is as large as possible. Help him calculate the maximum area that he could obtain respecting the conditions. If there is no such area, the festival cannot be organized and the answer is 0.00.

## 输入格式

The first line of input contains two integers $ N\ (3<=N<=200) $ and $ K\ (3<=K<=min(N,50)) $ , separated with one empty space, representing number of stages and number of singers, respectively.

Each of the next $ N $ lines contains two integers $ X_{i} $ and $ Y_{i} $ $ (0<=X_{i},Y_{i}<=10^{6}) $ representing the coordinates of the stages. There are no three or more collinear stages.

## 输出格式

Output contains only one line with one number, rounded to exactly two decimal places: the maximal festival area. Rounding is performed so that $ 0.5 $ and more rounds up and everything else rounds down.

## 说明/提示

Example explanation: From all possible convex polygon with $ 4 $ vertices and no other vertex inside, the largest is one with points $ (0,0) $ , $ (2,1) $ , $ (4,4) $ and $ (1,5) $ .

## 样例 #1

### 输入

```
5 4
0 0
3 0
2 1
4 4
1 5

```

### 输出

```
10.00

```

