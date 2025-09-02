---
title: "Make a Square"
layout: "post"
diff: 普及/提高-
pid: CF962C
tag: ['递归', '枚举', '概率论']
---

# Make a Square

## 题目描述

You are given a positive integer $ n $ , written without leading zeroes (for example, the number 04 is incorrect).

In one operation you can delete any digit of the given integer so that the result remains a positive integer without leading zeros.

Determine the minimum number of operations that you need to consistently apply to the given integer $ n $ to make from it the square of some positive integer or report that it is impossible.

An integer $ x $ is the square of some positive integer if and only if $ x=y^2 $ for some positive integer $ y $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{9} $ ). The number is given without leading zeroes.

## 输出格式

If it is impossible to make the square of some positive integer from $ n $ , print -1. In the other case, print the minimal number of operations required to do it.

## 说明/提示

In the first example we should delete from $ 8314 $ the digits $ 3 $ and $ 4 $ . After that $ 8314 $ become equals to $ 81 $ , which is the square of the integer $ 9 $ .

In the second example the given $ 625 $ is the square of the integer $ 25 $ , so you should not delete anything.

In the third example it is impossible to make the square from $ 333 $ , so the answer is -1.

## 样例 #1

### 输入

```
8314

```

### 输出

```
2

```

## 样例 #2

### 输入

```
625

```

### 输出

```
0

```

## 样例 #3

### 输入

```
333

```

### 输出

```
-1

```

