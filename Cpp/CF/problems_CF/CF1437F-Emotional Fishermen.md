---
title: "Emotional Fishermen"
layout: "post"
diff: 省选/NOI-
pid: CF1437F
tag: ['动态规划 DP', '组合数学']
---

# Emotional Fishermen

## 题目描述

$ n $ fishermen have just returned from a fishing vacation. The $ i $ -th fisherman has caught a fish of weight $ a_i $ .

Fishermen are going to show off the fish they caught to each other. To do so, they firstly choose an order in which they show their fish (each fisherman shows his fish exactly once, so, formally, the order of showing fish is a permutation of integers from $ 1 $ to $ n $ ). Then they show the fish they caught according to the chosen order. When a fisherman shows his fish, he might either become happy, become sad, or stay content.

Suppose a fisherman shows a fish of weight $ x $ , and the maximum weight of a previously shown fish is $ y $ ( $ y = 0 $ if that fisherman is the first to show his fish). Then:

- if $ x \ge 2y $ , the fisherman becomes happy;
- if $ 2x \le y $ , the fisherman becomes sad;
- if none of these two conditions is met, the fisherman stays content.

Let's call an order in which the fishermen show their fish emotional if, after all fishermen show their fish according to this order, each fisherman becomes either happy or sad. Calculate the number of emotional orders modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 5000 $ ).

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

Print one integer — the number of emotional orders, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 4 9
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4
4 3 2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
4 2 1
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
42 1337 13 37 420 666 616 97
```

### 输出

```
19200
```

