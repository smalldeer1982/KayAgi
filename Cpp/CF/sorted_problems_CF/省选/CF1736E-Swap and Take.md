---
title: "Swap and Take"
layout: "post"
diff: 省选/NOI-
pid: CF1736E
tag: []
---

# Swap and Take

## 题目描述

You're given an array consisting of $ n $ integers. You have to perform $ n $ turns.

Initially your score is $ 0 $ .

On the $ i $ -th turn, you are allowed to leave the array as it is or swap any one pair of $ 2 $ adjacent elements in the array and change exactly one of them to $ 0 $ (and leave the value of other element unchanged) after swapping. In either case(whether you swap or not), after this you add $ a_i $ to your score.

What's the maximum possible score you can get?

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 500 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ).

## 输出格式

Print a single integer — the maximum possible score.

## 说明/提示

In the first example, to get the maximum score we do as follows. Do nothing on the first turn, add $ 3 $ to the score. Swap the first and the second elements and turn $ 1 $ to $ 0 $ on the second turn, and add $ 3 $ to the score. The final score is $ 6 $ .

## 样例 #1

### 输入

```
2
3 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
7 3 9 6 12
```

### 输出

```
52
```

