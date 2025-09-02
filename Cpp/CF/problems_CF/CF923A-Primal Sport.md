---
title: "Primal Sport"
layout: "post"
diff: 普及+/提高
pid: CF923A
tag: ['贪心', '枚举', '素数判断,质数,筛法']
---

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 输入格式

The input contains a single integer $ X_{2} $ ( $ 4<=X_{2}<=10^{6} $ ). It is guaranteed that the integer $ X_{2} $ is composite, that is, is not prime.

## 输出格式

Output a single integer — the minimum possible $ X_{0} $ .

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14

```

### 输出

```
6

```

## 样例 #2

### 输入

```
20

```

### 输出

```
15

```

## 样例 #3

### 输入

```
8192

```

### 输出

```
8191

```

