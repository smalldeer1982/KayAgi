---
title: "Office Keys"
layout: "post"
diff: 提高+/省选-
pid: CF830A
tag: []
---

# Office Keys

## 题目描述

There are $ n $ people and $ k $ keys on a straight line. Every person wants to get to the office which is located on the line as well. To do that, he needs to reach some point with a key, take the key and then go to the office. Once a key is taken by somebody, it couldn't be taken by anybody else.

You are to determine the minimum time needed for all $ n $ people to get to the office with keys. Assume that people move a unit distance per $ 1 $ second. If two people reach a key at the same time, only one of them can take the key. A person can pass through a point with a key without taking it.

## 输入格式

The first line contains three integers $ n $ , $ k $ and $ p $ ( $ 1<=n<=1000 $ , $ n<=k<=2000 $ , $ 1<=p<=10^{9} $ ) — the number of people, the number of keys and the office location.

The second line contains $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — positions in which people are located initially. The positions are given in arbitrary order.

The third line contains $ k $ distinct integers $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{j}<=10^{9} $ ) — positions of the keys. The positions are given in arbitrary order.

Note that there can't be more than one person or more than one key in the same point. A person and a key can be located in the same point.

## 输出格式

Print the minimum time (in seconds) needed for all $ n $ to reach the office with keys.

## 说明/提示

In the first example the person located at point $ 20 $ should take the key located at point $ 40 $ and go with it to the office located at point $ 50 $ . He spends $ 30 $ seconds. The person located at point $ 100 $ can take the key located at point $ 80 $ and go to the office with it. He spends $ 50 $ seconds. Thus, after $ 50 $ seconds everybody is in office with keys.

## 样例 #1

### 输入

```
2 4 50
20 100
60 10 40 80

```

### 输出

```
50

```

## 样例 #2

### 输入

```
1 2 10
11
15 7

```

### 输出

```
7

```

