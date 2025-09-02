---
title: "Wet Shark and Odd and Even"
layout: "post"
diff: 入门
pid: CF621A
tag: ['排序']
---

# Wet Shark and Odd and Even

## 题目描述

Today, Wet Shark is given $ n $ integers. Using any of these integers no more than once, Wet Shark wants to get maximum possible even (divisible by $ 2 $ ) sum. Please, calculate this value for Wet Shark.

Note, that if Wet Shark uses no integers from the $ n $ integers, the sum is an even integer $ 0 $ .

## 输入格式

The first line of the input contains one integer, $ n $ ( $ 1<=n<=100000 $ ). The next line contains $ n $ space separated integers given to Wet Shark. Each of these integers is in range from $ 1 $ to $ 10^{9} $ , inclusive.

## 输出格式

Print the maximum possible even sum that can be obtained if we use some of the given integers.

## 说明/提示

In the first sample, we can simply take all three integers for a total sum of $ 6 $ .

In the second sample Wet Shark should take any four out of five integers $ 999999999 $ .

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
999999999 999999999 999999999 999999999 999999999

```

### 输出

```
3999999996
```

