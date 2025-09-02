---
title: "Segments Removal"
layout: "post"
diff: 普及+/提高
pid: CF899E
tag: ['线段树', '优先队列', '队列']
---

# Segments Removal

## 题目描述

Vasya has an array of integers of length $ n $ .

Vasya performs the following operations on the array: on each step he finds the longest segment of consecutive equal integers (the leftmost, if there are several such segments) and removes it. For example, if Vasya's array is $ [13,13,7,7,7,2,2,2] $ , then after one operation it becomes $ [13,13,2,2,2] $ .

Compute the number of operations Vasya should make until the array becomes empty, i.e. Vasya removes all elements from it.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the length of the array.

The second line contains a sequence $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — Vasya's array.

## 输出格式

Print the number of operations Vasya should make to remove all elements from the array.

## 说明/提示

In the first example, at first Vasya removes two fives at the second and third positions. The array becomes $ [2,2] $ . In the second operation Vasya removes two twos at the first and second positions. After that the array becomes empty.

In the second example Vasya has to perform five operations to make the array empty. In each of them he removes the first element from the array.

In the third example Vasya needs three operations. In the first operation he removes all integers $ 4 $ , in the second — all integers $ 100 $ , in the third — all integers $ 2 $ .

In the fourth example in the first operation Vasya removes the first two integers $ 10 $ . After that the array becomes $ [50,10,50,50] $ . Then in the second operation Vasya removes the two rightmost integers $ 50 $ , so that the array becomes $ [50,10] $ . In the third operation he removes the remaining $ 50 $ , and the array becomes $ [10] $ after that. In the last, fourth operation he removes the only remaining $ 10 $ . The array is empty after that.

## 样例 #1

### 输入

```
4
2 5 5 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
6 3 4 1 5

```

### 输出

```
5

```

## 样例 #3

### 输入

```
8
4 4 4 2 2 100 100 100

```

### 输出

```
3

```

## 样例 #4

### 输入

```
6
10 10 50 10 50 50

```

### 输出

```
4

```

