---
title: "Serval and Bonus Problem"
layout: "post"
diff: 省选/NOI-
pid: CF1153F
tag: []
---

# Serval and Bonus Problem

## 题目描述

Getting closer and closer to a mathematician, Serval becomes a university student on math major in Japari University. On the Calculus class, his teacher taught him how to calculate the expected length of a random subsegment of a given segment. Then he left a bonus problem as homework, with the award of a garage kit from IOI. The bonus is to extend this problem to the general case as follows.

You are given a segment with length $ l $ . We randomly choose $ n $ segments by choosing two points (maybe with non-integer coordinates) from the given segment equiprobably and the interval between the two points forms a segment. You are given the number of random segments $ n $ , and another integer $ k $ . The $ 2n $ endpoints of the chosen segments split the segment into $ (2n+1) $ intervals. Your task is to calculate the expected total length of those intervals that are covered by at least $ k $ segments of the $ n $ random segments.

You should find the answer modulo $ 998244353 $ .

## 输入格式

First line contains three space-separated positive integers $ n $ , $ k $ and $ l $ ( $ 1\leq k \leq n \leq 2000 $ , $ 1\leq l\leq 10^9 $ ).

## 输出格式

Output one integer — the expected total length of all the intervals covered by at least $ k $ segments of the $ n $ random segments modulo $ 998244353 $ .

Formally, let $ M = 998244353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first example, the expected total length is $ \int_0^1 \int_0^1 |x-y| \,\mathrm{d}x\,\mathrm{d}y = {1\over 3} $ , and $ 3^{-1} $ modulo $ 998244353 $ is $ 332748118 $ .

## 样例 #1

### 输入

```
1 1 1

```

### 输出

```
332748118

```

## 样例 #2

### 输入

```
6 2 1

```

### 输出

```
760234711

```

## 样例 #3

### 输入

```
7 5 3

```

### 输出

```
223383352

```

## 样例 #4

### 输入

```
97 31 9984524

```

### 输出

```
267137618

```

