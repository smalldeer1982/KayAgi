---
title: "Painting Pebbles"
layout: "post"
diff: 普及+/提高
pid: CF509B
tag: []
---

# Painting Pebbles

## 题目描述

There are $ n $ piles of pebbles on the table, the $ i $ -th pile contains $ a_{i} $ pebbles. Your task is to paint each pebble using one of the $ k $ given colors so that for each color $ c $ and any two piles $ i $ and $ j $ the difference between the number of pebbles of color $ c $ in pile $ i $ and number of pebbles of color $ c $ in pile $ j $ is at most one.

In other words, let's say that $ b_{i,c} $ is the number of pebbles of color $ c $ in the $ i $ -th pile. Then for any $ 1<=c<=k $ , $ 1<=i,j<=n $ the following condition must be satisfied $ |b_{i,c}-b_{j,c}|<=1 $ . It isn't necessary to use all $ k $ colors: if color $ c $ hasn't been used in pile $ i $ , then $ b_{i,c} $ is considered to be zero.

## 输入格式

The first line of the input contains positive integers $ n $ and $ k $ ( $ 1<=n,k<=100 $ ), separated by a space — the number of piles and the number of colors respectively.

The second line contains $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=100 $ ) denoting number of pebbles in each of the piles.

## 输出格式

If there is no way to paint the pebbles satisfying the given condition, output "NO" (without quotes) .

Otherwise in the first line output "YES" (without quotes). Then $ n $ lines should follow, the $ i $ -th of them should contain $ a_{i} $ space-separated integers. $ j $ -th ( $ 1<=j<=a_{i} $ ) of these integers should be equal to the color of the $ j $ -th pebble in the $ i $ -th pile. If there are several possible answers, you may output any of them.

## 样例 #1

### 输入

```
4 4
1 2 3 4

```

### 输出

```
YES
1
1 4
1 2 4
1 2 3 4

```

## 样例 #2

### 输入

```
5 2
3 2 4 1 3

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5 4
3 2 4 3 5

```

### 输出

```
YES
1 2 3
1 3
1 2 3 4
1 3 4
1 1 2 3 4

```

