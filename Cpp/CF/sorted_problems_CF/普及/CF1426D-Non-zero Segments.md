---
title: "Non-zero Segments"
layout: "post"
diff: 普及/提高-
pid: CF1426D
tag: []
---

# Non-zero Segments

## 题目描述

Kolya got an integer array $ a_1, a_2, \dots, a_n $ . The array can contain both positive and negative integers, but Kolya doesn't like $ 0 $ , so the array doesn't contain any zeros.

Kolya doesn't like that the sum of some subsegments of his array can be $ 0 $ . The subsegment is some consecutive segment of elements of the array.

You have to help Kolya and change his array in such a way that it doesn't contain any subsegments with the sum $ 0 $ . To reach this goal, you can insert any integers between any pair of adjacent elements of the array (integers can be really any: positive, negative, $ 0 $ , any by absolute value, even such a huge that they can't be represented in most standard programming languages).

Your task is to find the minimum number of integers you have to insert into Kolya's array in such a way that the resulting array doesn't contain any subsegments with the sum $ 0 $ .

## 输入格式

The first line of the input contains one integer $ n $ ( $ 2 \le n \le 200\,000 $ ) — the number of elements in Kolya's array.

The second line of the input contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ -10^{9} \le a_i \le 10^{9}, a_i \neq 0 $ ) — the description of Kolya's array.

## 输出格式

Print the minimum number of integers you have to insert into Kolya's array in such a way that the resulting array doesn't contain any subsegments with the sum $ 0 $ .

## 说明/提示

Consider the first example. There is only one subsegment with the sum $ 0 $ . It starts in the second element and ends in the fourth element. It's enough to insert one element so the array doesn't contain any subsegments with the sum equal to zero. For example, it is possible to insert the integer $ 1 $ between second and third elements of the array.

There are no subsegments having sum $ 0 $ in the second example so you don't need to do anything.

## 样例 #1

### 输入

```
4
1 -5 3 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
4 -2 3 -9 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
9
-1 1 -1 1 -1 1 1 -1 -1
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
16 -5 -11 -15 10 5 4 -4
```

### 输出

```
3
```

