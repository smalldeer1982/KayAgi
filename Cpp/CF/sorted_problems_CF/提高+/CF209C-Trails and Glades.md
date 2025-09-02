---
title: "Trails and Glades"
layout: "post"
diff: 提高+/省选-
pid: CF209C
tag: ['连通块', '欧拉回路', '概率论']
---

# Trails and Glades

## 题目描述

Vasya went for a walk in the park. The park has $ n $ glades, numbered from 1 to $ n $ . There are $ m $ trails between the glades. The trails are numbered from 1 to $ m $ , where the $ i $ -th trail connects glades $ x_{i} $ and $ y_{i} $ . The numbers of the connected glades may be the same $ (x_{i}=y_{i}) $ , which means that a trail connects a glade to itself. Also, two glades may have several non-intersecting trails between them.

Vasya is on glade 1, he wants to walk on all trails of the park exactly once, so that he can eventually return to glade 1. Unfortunately, Vasya does not know whether this walk is possible or not. Help Vasya, determine whether the walk is possible or not. If such walk is impossible, find the minimum number of trails the authorities need to add to the park in order to make the described walk possible.

Vasya can shift from one trail to another one only on glades. He can move on the trails in both directions. If Vasya started going on the trail that connects glades $ a $ and $ b $ , from glade $ a $ , then he must finish this trail on glade $ b $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=10^{6}; 0<=m<=10^{6}) $ — the number of glades in the park and the number of trails in the park, respectively. Next $ m $ lines specify the trails. The $ i $ -th line specifies the $ i $ -th trail as two space-separated numbers, $ x_{i} $ , $ y_{i} $ $ (1<=x_{i},y_{i}<=n) $ — the numbers of the glades connected by this trail.

## 输出格式

Print the single integer — the answer to the problem. If Vasya's walk is possible without adding extra trails, print 0, otherwise print the minimum number of trails the authorities need to add to the park in order to make Vasya's walk possible.

## 说明/提示

In the first test case the described walk is possible without building extra trails. For example, let's first go on the first trail, then on the second one, and finally on the third one.

In the second test case the described walk is impossible without adding extra trails. To make the walk possible, it is enough to add one trail, for example, between glades number one and two.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
2 5
1 1
1 2
1 2
2 2
1 2

```

### 输出

```
1

```

