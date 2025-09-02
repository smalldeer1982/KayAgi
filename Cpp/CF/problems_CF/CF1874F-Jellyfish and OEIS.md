---
title: "Jellyfish and OEIS"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1874F
tag: []
---

# Jellyfish and OEIS

## 题目描述

Jellyfish always uses OEIS to solve math problems, but now she finds a problem that cannot be solved by OEIS:

Count the number of permutations $ p $ of $ [1, 2, \dots, n] $ such that for all $ (l, r) $ such that $ l \leq r \leq m_l $ , the subarray $ [p_l, p_{l+1}, \dots, p_r] $ is not a permutation of $ [l, l+1, \dots, r] $ .

Since the answer may be large, you only need to find the answer modulo $ 10^9+7 $ .

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1 \leq n \leq 200 $ ) — the length of the permutation.

The second line of the input contains $ n $ integers $ m_1, m_2, \dots, m_n $ ( $ 0 \leq m_i \leq n $ ).

## 输出格式

Output the number of different permutations that satisfy the conditions, modulo $ 10^9+7 $ .

## 说明/提示

In the first example, $ [2, 3, 1] $ and $ [3, 1, 2] $ satisfies the condition.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 4 3 4 5
```

### 输出

```
38
```

## 样例 #3

### 输入

```
5
5 1 1 1 1
```

### 输出

```
0
```

