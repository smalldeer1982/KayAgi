---
title: "Median"
layout: "post"
diff: 普及/提高-
pid: CF166C
tag: []
---

# Median

## 题目描述

A median in an array with the length of $ n $ is an element which occupies position number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/a3cce6c26f6207c41846eedd0e6a59cdcc521015.png) after we sort the elements in the non-decreasing order (the array elements are numbered starting with $ 1 $ ). A median of an array $ (2,6,1,2,3) $ is the number $ 2 $ , and a median of array $ (0,96,17,23) $ — the number $ 17 $ .

We define an expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/ff48225f7f772c08409f2d464b02c44cf20620e2.png) as the integer part of dividing number $ a $ by number $ b $ .

One day Vasya showed Petya an array consisting of $ n $ integers and suggested finding the array's median. Petya didn't even look at the array and said that it equals $ x $ . Petya is a very honest boy, so he decided to add several numbers to the given array so that the median of the resulting array would be equal to $ x $ .

Petya can add any integers from $ 1 $ to $ 10^{5} $ to the array, including the same numbers. Of course, he can add nothing to the array. If a number is added multiple times, then we should consider it the number of times it occurs. It is not allowed to delete of change initial numbers of the array.

While Petya is busy distracting Vasya, your task is to find the minimum number of elements he will need.

## 输入格式

The first input line contains two space-separated integers $ n $ and $ x $ ( $ 1<=n<=500 $ , $ 1<=x<=10^{5} $ ) — the initial array's length and the required median's value. The second line contains $ n $ space-separated numbers — the initial array. The elements of the array are integers from $ 1 $ to $ 10^{5} $ . The array elements are not necessarily different.

## 输出格式

Print the only integer — the minimum number of elements Petya needs to add to the array so that its median equals $ x $ .

## 说明/提示

In the first sample we can add number $ 9 $ to array $ (10,20,30) $ . The resulting array $ (9,10,20,30) $ will have a median in position ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF166C/087e5fa70c281cf5e7b5f392e766cd46089615e4.png), that is, $ 10 $ .

In the second sample you should add numbers $ 4 $ , $ 5 $ , $ 5 $ , $ 5 $ . The resulting array has median equal to $ 4 $ .

## 样例 #1

### 输入

```
3 10
10 20 30

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 4
1 2 3

```

### 输出

```
4

```

