---
title: "Game Bundles"
layout: "post"
diff: 省选/NOI-
pid: CF1854E
tag: []
---

# Game Bundles

## 题目描述

Rishi is developing games in the 2D metaverse and wants to offer game bundles to his customers. Each game has an associated enjoyment value. A game bundle consists of a subset of games whose total enjoyment value adds up to $ 60 $ .

Your task is to choose $ k $ games, where $ 1 \leq k \leq 60 $ , along with their respective enjoyment values $ a_1, a_2, \dots, a_k $ , in such a way that exactly $ m $ distinct game bundles can be formed.

## 输入格式

The input is a single integer $ m $ ( $ 1 \le m \le 10^{10} $ ) — the desired number of game bundles.

## 输出格式

The first line should contain an integer $ k $ ( $ 1 \le k \le 60 $ ) — the number of games.

The second line should contain $ k $ integers, $ a_1, a_2, \dots, a_k $ ( $ 1 \le a_1, a_2, \dots, a_k \le 60 $ ) — the enjoyment values of the $ k $ games.

## 说明/提示

In the first sample, any subset of size $ 3 $ is a game bundle. There are $ 4 $ such subsets.

## 样例 #1

### 输入

```
4
```

### 输出

```
4
20 20 20 20
```

## 样例 #2

### 输入

```
722
```

### 输出

```
15
15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
```

## 样例 #3

### 输入

```
1
```

### 输出

```
1
60
```

