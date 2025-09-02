---
title: "Cormen — The Best Friend Of a Man"
layout: "post"
diff: 普及-
pid: CF732B
tag: []
---

# Cormen — The Best Friend Of a Man

## 题目描述

Recently a dog was bought for Polycarp. The dog's name is Cormen. Now Polycarp has a lot of troubles. For example, Cormen likes going for a walk.

Empirically Polycarp learned that the dog needs at least $ k $ walks for any two consecutive days in order to feel good. For example, if $ k=5 $ and yesterday Polycarp went for a walk with Cormen $ 2 $ times, today he has to go for a walk at least $ 3 $ times.

Polycarp analysed all his affairs over the next $ n $ days and made a sequence of $ n $ integers $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the number of times Polycarp will walk with the dog on the $ i $ -th day while doing all his affairs (for example, he has to go to a shop, throw out the trash, etc.).

Help Polycarp determine the minimum number of walks he needs to do additionaly in the next $ n $ days so that Cormen will feel good during all the $ n $ days. You can assume that on the day before the first day and on the day after the $ n $ -th day Polycarp will go for a walk with Cormen exactly $ k $ times.

Write a program that will find the minumum number of additional walks and the appropriate schedule — the sequence of integers $ b_{1},b_{2},...,b_{n} $ ( $ b_{i}>=a_{i} $ ), where $ b_{i} $ means the total number of walks with the dog on the $ i $ -th day.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n,k<=500 $ ) — the number of days and the minimum number of walks with Cormen for any two consecutive days.

The second line contains integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=500 $ ) — the number of walks with Cormen on the $ i $ -th day which Polycarp has already planned.

## 输出格式

In the first line print the smallest number of additional walks that Polycarp should do during the next $ n $ days so that Cormen will feel good during all days.

In the second line print $ n $ integers $ b_{1},b_{2},...,b_{n} $ , where $ b_{i} $ — the total number of walks on the $ i $ -th day according to the found solutions ( $ a_{i}<=b_{i} $ for all $ i $ from 1 to $ n $ ). If there are multiple solutions, print any of them.

## 样例 #1

### 输入

```
3 5
2 0 1

```

### 输出

```
4
2 3 2

```

## 样例 #2

### 输入

```
3 1
0 0 0

```

### 输出

```
1
0 1 0

```

## 样例 #3

### 输入

```
4 6
2 4 3 5

```

### 输出

```
0
2 4 3 5

```

