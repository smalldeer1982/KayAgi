---
title: "Fun with Integers"
layout: "post"
diff: 普及/提高-
pid: CF1062D
tag: []
---

# Fun with Integers

## 题目描述

You are given a positive integer $ n $ greater or equal to $ 2 $ . For every pair of integers $ a $ and $ b $ ( $ 2 \le |a|, |b| \le n $ ), you can transform $ a $ into $ b $ if and only if there exists an integer $ x $ such that $ 1 < |x| $ and ( $ a \cdot x = b $ or $ b \cdot x = a $ ), where $ |x| $ denotes the absolute value of $ x $ .

After such a transformation, your score increases by $ |x| $ points and you are not allowed to transform $ a $ into $ b $ nor $ b $ into $ a $ anymore.

Initially, you have a score of $ 0 $ . You can start at any integer and transform it as many times as you like. What is the maximum score you can achieve?

## 输入格式

A single line contains a single integer $ n $ ( $ 2 \le n \le 100\,000 $ ) — the given integer described above.

## 输出格式

Print an only integer — the maximum score that can be achieved with the transformations. If it is not possible to perform even a single transformation for all possible starting integers, print $ 0 $ .

## 说明/提示

In the first example, the transformations are $ 2 \rightarrow 4 \rightarrow (-2) \rightarrow (-4) \rightarrow 2 $ .

In the third example, it is impossible to perform even a single transformation.

## 样例 #1

### 输入

```
4

```

### 输出

```
8
```

## 样例 #2

### 输入

```
6

```

### 输出

```
28
```

## 样例 #3

### 输入

```
2

```

### 输出

```
0
```

