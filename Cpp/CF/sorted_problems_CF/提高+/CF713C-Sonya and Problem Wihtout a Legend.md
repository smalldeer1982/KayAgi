---
title: "Sonya and Problem Wihtout a Legend"
layout: "post"
diff: 提高+/省选-
pid: CF713C
tag: []
---

# Sonya and Problem Wihtout a Legend

## 题目描述

Sonya was unable to think of a story for this problem, so here comes the formal description.

You are given the array containing $ n $ positive integers. At one turn you can pick any element and increase or decrease it by $ 1 $ . The goal is the make the array strictly increasing by making the minimum possible number of operations. You are allowed to change elements in any way, they can become negative or equal to $ 0 $ .

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=3000 $ ) — the length of the array.

Next line contains $ n $ integer $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print the minimum number of operation required to make the array strictly increasing.

## 说明/提示

In the first sample, the array is going to look as follows:

 $ 2 $ $ 3 $ $ 5 $ $ 6 $ $ 7 $ $ 9 $ $ 11 $

 $ |2-2|+|1-3|+|5-5|+|11-6|+|5-7|+|9-9|+|11-11|=9 $

And for the second sample:

 $ 1 $ $ 2 $ $ 3 $ $ 4 $ $ 5 $

 $ |5-1|+|4-2|+|3-3|+|2-4|+|1-5|=12 $

## 样例 #1

### 输入

```
7
2 1 5 11 5 9 11

```

### 输出

```
9

```

## 样例 #2

### 输入

```
5
5 4 3 2 1

```

### 输出

```
12

```

