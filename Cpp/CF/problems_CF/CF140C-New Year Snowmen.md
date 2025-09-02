---
title: "New Year Snowmen"
layout: "post"
diff: 提高+/省选-
pid: CF140C
tag: ['离散化', '优先队列', '队列']
---

# New Year Snowmen

## 题目描述

As meticulous Gerald sets the table and caring Alexander sends the postcards, Sergey makes snowmen. Each showman should consist of three snowballs: a big one, a medium one and a small one. Sergey's twins help him: they've already made $ n $ snowballs with radii equal to $ r_{1} $ , $ r_{2} $ , ..., $ r_{n} $ . To make a snowman, one needs any three snowballs whose radii are pairwise different. For example, the balls with radii $ 1 $ , $ 2 $ and $ 3 $ can be used to make a snowman but $ 2 $ , $ 2 $ , $ 3 $ or $ 2 $ , $ 2 $ , $ 2 $ cannot. Help Sergey and his twins to determine what maximum number of snowmen they can make from those snowballs.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of snowballs. The next line contains $ n $ integers — the balls' radii $ r_{1} $ , $ r_{2} $ , ..., $ r_{n} $ ( $ 1<=r_{i}<=10^{9} $ ). The balls' radii can coincide.

## 输出格式

Print on the first line a single number $ k $ — the maximum number of the snowmen. Next $ k $ lines should contain the snowmen's descriptions. The description of each snowman should consist of three space-separated numbers — the big ball's radius, the medium ball's radius and the small ball's radius. It is allowed to print the snowmen in any order. If there are several solutions, print any of them.

## 样例 #1

### 输入

```
7
1 2 3 4 5 6 7

```

### 输出

```
2
3 2 1
6 5 4

```

## 样例 #2

### 输入

```
3
2 2 3

```

### 输出

```
0

```

