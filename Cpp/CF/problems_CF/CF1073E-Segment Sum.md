---
title: "Segment Sum"
layout: "post"
diff: 省选/NOI-
pid: CF1073E
tag: ['动态规划 DP', '数位 DP', '状态合并']
---

# Segment Sum

## 题目描述

You are given two integers $ l $ and $ r $ ( $ l \le r $ ). Your task is to calculate the sum of numbers from $ l $ to $ r $ (including $ l $ and $ r $ ) such that each number contains at most $ k $ different digits, and print this sum modulo $ 998244353 $ .

For example, if $ k = 1 $ then you have to calculate all numbers from $ l $ to $ r $ such that each number is formed using only one digit. For $ l = 10, r = 50 $ the answer is $ 11 + 22 + 33 + 44 = 110 $ .

## 输入格式

The only line of the input contains three integers $ l $ , $ r $ and $ k $ ( $ 1 \le l \le r < 10^{18}, 1 \le k \le 10 $ ) — the borders of the segment and the maximum number of different digits.

## 输出格式

Print one integer — the sum of numbers from $ l $ to $ r $ such that each number contains at most $ k $ different digits, modulo $ 998244353 $ .

## 说明/提示

For the first example the answer is just the sum of numbers from $ l $ to $ r $ which equals to $ \frac{50 \cdot 51}{2} - \frac{9 \cdot 10}{2} = 1230 $ . This example also explained in the problem statement but for $ k = 1 $ .

For the second example the answer is just the sum of numbers from $ l $ to $ r $ which equals to $ \frac{2345 \cdot 2346}{2} = 2750685 $ .

For the third example the answer is $ 101 + 110 + 111 + 112 + 113 + 114 + 115 + 116 + 117 + 118 + 119 + 121 + 122 + 131 + 133 + 141 + 144 + 151 = 2189 $ .

## 样例 #1

### 输入

```
10 50 2

```

### 输出

```
1230

```

## 样例 #2

### 输入

```
1 2345 10

```

### 输出

```
2750685

```

## 样例 #3

### 输入

```
101 154 2

```

### 输出

```
2189

```

