---
title: "Bear and Floodlight"
layout: "post"
diff: 提高+/省选-
pid: CF385D
tag: []
---

# Bear and Floodlight

## 题目描述

One day a bear lived on the $ Oxy $ axis. He was afraid of the dark, so he couldn't move at night along the plane points that aren't lit. One day the bear wanted to have a night walk from his house at point $ (l,0) $ to his friend's house at point $ (r,0) $ , along the segment of length $ (r-l) $ . Of course, if he wants to make this walk, he needs each point of the segment to be lit. That's why the bear called his friend (and yes, in the middle of the night) asking for a very delicate favor.

The $ Oxy $ axis contains $ n $ floodlights. Floodlight $ i $ is at point $ (x_{i},y_{i}) $ and can light any angle of the plane as large as $ a_{i} $ degree with vertex at point $ (x_{i},y_{i}) $ . The bear asked his friend to turn the floodlights so that he (the bear) could go as far away from his house as possible during the walking along the segment. His kind friend agreed to fulfill his request. And while he is at it, the bear wonders: what is the furthest he can go away from his house? Hep him and find this distance.

Consider that the plane has no obstacles and no other light sources besides the floodlights. The bear's friend cannot turn the floodlights during the bear's walk. Assume that after all the floodlights are turned in the correct direction, the bear goes for a walk and his friend goes to bed.

## 输入格式

The first line contains three space-separated integers $ n $ , $ l $ , $ r $ $ (1<=n<=20; -10^{5}<=l<=r<=10^{5}) $ . The $ i $ -th of the next $ n $ lines contain three space-separated integers $ x_{i} $ , $ y_{i} $ , $ a_{i} $ $ (-1000<=x_{i}<=1000; 1<=y_{i}<=1000; 1<=a_{i}<=90) $ — the floodlights' description.

Note that two floodlights can be at the same point of the plane.

## 输出格式

Print a single real number — the answer to the problem. The answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-6} $ .

## 说明/提示

In the first sample, one of the possible solutions is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF385D/70cd74581588ecc939447891194dd426bcc1962c.png)In the second sample, a single solution is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF385D/6d28a59da2dde7e6425608e1f0cdf10b62cece79.png)In the third sample, a single solution is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF385D/10b4dd48817911ff77f858eb6a9fd18802c09260.png)

## 样例 #1

### 输入

```
2 3 5
3 1 45
5 1 45

```

### 输出

```
2.000000000

```

## 样例 #2

### 输入

```
1 0 1
1 1 30

```

### 输出

```
0.732050808

```

## 样例 #3

### 输入

```
1 0 1
1 1 45

```

### 输出

```
1.000000000

```

## 样例 #4

### 输入

```
1 0 2
0 2 90

```

### 输出

```
2.000000000

```

