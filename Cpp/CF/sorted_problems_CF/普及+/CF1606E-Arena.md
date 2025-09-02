---
title: "Arena"
layout: "post"
diff: 普及+/提高
pid: CF1606E
tag: []
---

# Arena

## 题目描述

There are $ n $ heroes fighting in the arena. Initially, the $ i $ -th hero has $ a_i $ health points.

The fight in the arena takes place in several rounds. At the beginning of each round, each alive hero deals $ 1 $ damage to all other heroes. Hits of all heroes occur simultaneously. Heroes whose health is less than $ 1 $ at the end of the round are considered killed.

If exactly $ 1 $ hero remains alive after a certain round, then he is declared the winner. Otherwise, there is no winner.

Your task is to calculate the number of ways to choose the initial health points for each hero $ a_i $ , where $ 1 \le a_i \le x $ , so that there is no winner of the fight. The number of ways can be very large, so print it modulo $ 998244353 $ . Two ways are considered different if at least one hero has a different amount of health. For example, $ [1, 2, 1] $ and $ [2, 1, 1] $ are different.

## 输入格式

The only line contains two integers $ n $ and $ x $ ( $ 2 \le n \le 500; 1 \le x \le 500 $ ).

## 输出格式

Print one integer — the number of ways to choose the initial health points for each hero $ a_i $ , where $ 1 \le a_i \le x $ , so that there is no winner of the fight, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 5
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 3
```

### 输出

```
15
```

## 样例 #3

### 输入

```
5 4
```

### 输出

```
1024
```

## 样例 #4

### 输入

```
13 37
```

### 输出

```
976890680
```

