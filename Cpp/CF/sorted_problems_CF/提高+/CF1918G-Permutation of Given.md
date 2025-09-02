---
title: "Permutation of Given"
layout: "post"
diff: 提高+/省选-
pid: CF1918G
tag: ['构造']
---

# Permutation of Given

## 题目描述

You were given only one number, $ n $ . It didn't seem interesting to you, so you wondered if it's possible to come up with an array of length $ n $ consisting of non-zero integers, such that if each element of the array is replaced by the sum of its neighbors (the elements on the ends are replaced by their only neighbors), you obtain a permutation of the numbers in the original array.

## 输入格式

Each test case contains only one number, $ n $ ( $ 2 \leq n \leq 10^6 $ ).

## 输出格式

If a solution exists, output "YES" (without quotes), followed by an array $ a $ ( $ -10^9 \leq a_i \leq 10^9, a_i \neq 0 $ ) that satisfies the condition of the problem. If there are multiple possible answers, output any of them.

If there is no suitable array, output "NO" (without quotes).

The words "YES" and "NO" can be output in any case, for example, "YES", "Yes", "yEs", and so on.

## 说明/提示

In the first test, the array \[ $ 1, 2, -2, -1 $ \] is suitable, because if each element is replaced by the sum of its neighbors, the resulting array is \[ $ 2, -1, 1, -2 $ \], which is a permutation of the original array.

In the second test, it can be shown that there is no solution.

## 样例 #1

### 输入

```
4
```

### 输出

```
YES
1 2 -2 -1
```

## 样例 #2

### 输入

```
5
```

### 输出

```
NO
```

