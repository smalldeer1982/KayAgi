---
title: "Levels and Regions"
layout: "post"
diff: 省选/NOI-
pid: CF643C
tag: ['斜率优化', '前缀和', '期望']
---

# Levels and Regions

## 题目描述

Radewoosh is playing a computer game. There are $ n $ levels, numbered $ 1 $ through $ n $ . Levels are divided into $ k $ regions (groups). Each region contains some positive number of consecutive levels.

The game repeats the the following process:

1. If all regions are beaten then the game ends immediately. Otherwise, the system finds the first region with at least one non-beaten level. Let $ X $ denote this region.
2. The system creates an empty bag for tokens. Each token will represent one level and there may be many tokens representing the same level.
  - For each already beaten level $ i $ in the region $ X $ , the system adds $ t_{i} $ tokens to the bag (tokens representing the $ i $ -th level).
  - Let $ j $ denote the first non-beaten level in the region $ X $ . The system adds $ t_{j} $ tokens to the bag.
3. Finally, the system takes a uniformly random token from the bag and a player starts the level represented by the token. A player spends one hour and beats the level, even if he has already beaten it in the past.

Given $ n $ , $ k $ and values $ t_{1},t_{2},...,t_{n} $ , your task is to split levels into regions. Each level must belong to exactly one region, and each region must contain non-empty consecutive set of levels. What is the minimum possible expected number of hours required to finish the game?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=n<=200000 $ , $ 1<=k<=min(50,n) $ ) — the number of levels and the number of regions, respectively.

The second line contains $ n $ integers $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=100000 $ ).

## 输出格式

Print one real number — the minimum possible expected value of the number of hours spent to finish the game if levels are distributed between regions in the optimal way. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-4} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643C/73b7e412a182af1e0d063e02722d13792ecaced8.png).

## 说明/提示

In the first sample, we are supposed to split $ 4 $ levels into $ 2 $ regions. It's optimal to create the first region with only one level (it must be the first level). Then, the second region must contain other three levels.

In the second sample, it's optimal to split levels into two regions with $ 3 $ levels each.

## 样例 #1

### 输入

```
4 2
100 3 5 7

```

### 输出

```
5.7428571429

```

## 样例 #2

### 输入

```
6 2
1 2 4 8 16 32

```

### 输出

```
8.5000000000

```

