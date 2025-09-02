---
title: "Wrong Subtraction"
layout: "post"
diff: 入门
pid: CF977A
tag: ['模拟', '字符串', '栈']
---

# Wrong Subtraction

## 题目描述

Little girl Tanya is learning how to decrease a number by one, but she does it wrong with a number consisting of two or more digits. Tanya subtracts one from a number by the following algorithm:

- if the last digit of the number is non-zero, she decreases the number by one;
- if the last digit of the number is zero, she divides the number by 10 (i.e. removes the last digit).

You are given an integer number $ n $ . Tanya will subtract one from it $ k $ times. Your task is to print the result after all $ k $ subtractions.

It is guaranteed that the result will be positive integer number.

## 输入格式

The first line of the input contains two integer numbers $ n $ and $ k $ ( $ 2 \le n \le 10^9 $ , $ 1 \le k \le 50 $ ) — the number from which Tanya will subtract and the number of subtractions correspondingly.

## 输出格式

Print one integer number — the result of the decreasing $ n $ by one $ k $ times.

It is guaranteed that the result will be positive integer number.

## 说明/提示

The first example corresponds to the following sequence: $ 512 \rightarrow 511 \rightarrow 510 \rightarrow 51 \rightarrow 50 $ .

## 样例 #1

### 输入

```
512 4

```

### 输出

```
50

```

## 样例 #2

### 输入

```
1000000000 9

```

### 输出

```
1

```

