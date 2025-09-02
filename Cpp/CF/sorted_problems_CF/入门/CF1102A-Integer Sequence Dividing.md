---
title: "Integer Sequence Dividing"
layout: "post"
diff: 入门
pid: CF1102A
tag: []
---

# Integer Sequence Dividing

## 题目描述

You are given an integer sequence $ 1, 2, \dots, n $ . You have to divide it into two sets $ A $ and $ B $ in such a way that each element belongs to exactly one set and $ |sum(A) - sum(B)| $ is minimum possible.

The value $ |x| $ is the absolute value of $ x $ and $ sum(S) $ is the sum of elements of the set $ S $ .

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1 \le n \le 2 \cdot 10^9 $ ).

## 输出格式

Print one integer — the minimum possible value of $ |sum(A) - sum(B)| $ if you divide the initial sequence $ 1, 2, \dots, n $ into two sets $ A $ and $ B $ .

## 说明/提示

Some (not all) possible answers to examples:

In the first example you can divide the initial sequence into sets $ A = \{1, 2\} $ and $ B = \{3\} $ so the answer is $ 0 $ .

In the second example you can divide the initial sequence into sets $ A = \{1, 3, 4\} $ and $ B = \{2, 5\} $ so the answer is $ 1 $ .

In the third example you can divide the initial sequence into sets $ A = \{1, 4, 5\} $ and $ B = \{2, 3, 6\} $ so the answer is $ 1 $ .

## 样例 #1

### 输入

```
3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
5

```

### 输出

```
1

```

## 样例 #3

### 输入

```
6

```

### 输出

```
1

```

