---
title: "Dirty Arkady's Kitchen"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF827F
tag: []
---

# Dirty Arkady's Kitchen

## 题目描述

Arkady likes to walk around his kitchen. His labyrinthine kitchen consists of several important places connected with passages. Unfortunately it happens that these passages are flooded with milk so that it's impossible to pass through them. Namely, it's possible to pass through each passage in any direction only during some time interval.

The lengths of all passages are equal and Arkady makes through them in one second. For security reasons, Arkady can never stop, also, he can't change direction while going through a passage. In other words, if he starts walking in some passage, he should reach its end and immediately leave the end.

Today Arkady needs to quickly reach important place $ n $ from place $ 1 $ . He plans to exit the place $ 1 $ at time moment $ 0 $ and reach the place $ n $ as early as he can. Please find the minimum time he should spend on his way.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=5·10^{5} $ , $ 0<=m<=5·10^{5} $ ) — the number of important places and the number of passages, respectively.

After that, $ m $ lines follow, each of them describe one passage. Each line contains four integers $ a $ , $ b $ , $ l $ and $ r $ ( $ 1<=a,b<=n $ , $ a≠b $ , $ 0<=l&lt;r<=10^{9} $ ) — the places the passage connects and the time segment during which it's possible to use this passage.

## 输出格式

Print one integer — minimum time Arkady should spend to reach the destination. If he can't reach the place $ n $ , print -1.

## 说明/提示

In the first example Arkady should go through important places $ 1→3→4→5 $ .

In the second example Arkady can't start his walk because at time moment $ 0 $ it's impossible to use the only passage.

## 样例 #1

### 输入

```
5 6
1 2 0 1
2 5 2 3
2 5 0 1
1 3 0 1
3 4 1 2
4 5 2 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2 1
1 2 1 100

```

### 输出

```
-1

```

