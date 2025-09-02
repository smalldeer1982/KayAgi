---
title: "Problem for Nazar"
layout: "post"
diff: 普及+/提高
pid: CF1151C
tag: []
---

# Problem for Nazar

## 题目描述

Nazar, a student of the scientific lyceum of the Kingdom of Kremland, is known for his outstanding mathematical abilities. Today a math teacher gave him a very difficult task.

Consider two infinite sets of numbers. The first set consists of odd positive numbers ( $ 1, 3, 5, 7, \ldots $ ), and the second set consists of even positive numbers ( $ 2, 4, 6, 8, \ldots $ ). At the first stage, the teacher writes the first number on the endless blackboard from the first set, in the second stage — the first two numbers from the second set, on the third stage — the next four numbers from the first set, on the fourth — the next eight numbers from the second set and so on. In other words, at each stage, starting from the second, he writes out two times more numbers than at the previous one, and also changes the set from which these numbers are written out to another.

The ten first written numbers: $ 1, 2, 4, 3, 5, 7, 9, 6, 8, 10 $ . Let's number the numbers written, starting with one.

The task is to find the sum of numbers with numbers from $ l $ to $ r $ for given integers $ l $ and $ r $ . The answer may be big, so you need to find the remainder of the division by $ 1000000007 $ ( $ 10^9+7 $ ).

Nazar thought about this problem for a long time, but didn't come up with a solution. Help him solve this problem.

## 输入格式

The first line contains two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq 10^{18} $ ) — the range in which you need to find the sum.

## 输出格式

Print a single integer — the answer modulo $ 1000000007 $ ( $ 10^9+7 $ ).

## 说明/提示

In the first example, the answer is the sum of the first three numbers written out ( $ 1 + 2 + 4 = 7 $ ).

In the second example, the numbers with numbers from $ 5 $ to $ 14 $ : $ 5, 7, 9, 6, 8, 10, 12, 14, 16, 18 $ . Their sum is $ 105 $ .

## 样例 #1

### 输入

```
1 3

```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 14

```

### 输出

```
105
```

## 样例 #3

### 输入

```
88005553535 99999999999

```

### 输出

```
761141116
```

