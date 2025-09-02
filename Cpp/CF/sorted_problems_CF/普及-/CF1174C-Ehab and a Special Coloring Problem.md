---
title: "Ehab and a Special Coloring Problem"
layout: "post"
diff: 普及-
pid: CF1174C
tag: []
---

# Ehab and a Special Coloring Problem

## 题目描述

You're given an integer $ n $ . For every integer $ i $ from $ 2 $ to $ n $ , assign a positive integer $ a_i $ such that the following conditions hold:

- For any pair of integers $ (i,j) $ , if $ i $ and $ j $ are coprime, $ a_i \neq a_j $ .
- The maximal value of all $ a_i $ should be minimized (that is, as small as possible).

A pair of integers is called [coprime](https://en.wikipedia.org/wiki/Coprime_integers) if their [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) is $ 1 $ .

## 输入格式

The only line contains the integer $ n $ ( $ 2 \le n \le 10^5 $ ).

## 输出格式

Print $ n-1 $ integers, $ a_2 $ , $ a_3 $ , $ \ldots $ , $ a_n $ ( $ 1 \leq a_i \leq n $ ).

If there are multiple solutions, print any of them.

## 说明/提示

In the first example, notice that $ 3 $ and $ 4 $ are coprime, so $ a_3 \neq a_4 $ . Also, notice that $ a=[1,2,3] $ satisfies the first condition, but it's not a correct answer because its maximal value is $ 3 $ .

## 样例 #1

### 输入

```
4

```

### 输出

```
1 2 1 
```

## 样例 #2

### 输入

```
3

```

### 输出

```
2 1
```

