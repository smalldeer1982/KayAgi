---
title: "Summer Earnings"
layout: "post"
diff: 省选/NOI-
pid: CF333E
tag: []
---

# Summer Earnings

## 题目描述

Many schoolchildren look for a job for the summer, and one day, when Gerald was still a schoolboy, he also decided to work in the summer. But as Gerald was quite an unusual schoolboy, he found quite unusual work. A certain Company agreed to pay him a certain sum of money if he draws them three identical circles on a plane. The circles must not interfere with each other (but they may touch each other). He can choose the centers of the circles only from the $ n $ options granted by the Company. He is free to choose the radius of the circles himself (all three radiuses must be equal), but please note that the larger the radius is, the more he gets paid.

Help Gerald earn as much as possible.

## 输入格式

The first line contains a single integer $ n $ — the number of centers ( $ 3<=n<=3000 $ ). The following $ n $ lines each contain two integers $ x_{i},y_{i} $ ( $ -10^{4}<=x_{i},y_{i}<=10^{4} $ ) — the coordinates of potential circle centers, provided by the Company.

All given points are distinct.

## 输出格式

Print a single real number — maximum possible radius of circles. The answer will be accepted if its relative or absolute error doesn't exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
3
0 1
1 0
1 1

```

### 输出

```
0.50000000000000000000

```

## 样例 #2

### 输入

```
7
2 -3
-2 -3
3 0
-3 -1
1 -2
2 -2
-1 0

```

### 输出

```
1.58113883008418980000

```

