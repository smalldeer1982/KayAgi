---
title: "Arithmetic Operations"
layout: "post"
diff: 提高+/省选-
pid: CF1654E
tag: []
---

# Arithmetic Operations

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ .

You can do the following operation any number of times (possibly zero):

- Choose any index $ i $ and set $ a_i $ to any integer (positive, negative or $ 0 $ ).

What is the minimum number of operations needed to turn $ a $ into an arithmetic progression? The array $ a $ is an arithmetic progression if $ a_{i+1}-a_i=a_i-a_{i-1} $ for any $ 2 \leq i \leq n-1 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^5 $ ).

## 输出格式

Print a single integer: the minimum number of operations needed to turn $ a $ into an arithmetic progression.

## 说明/提示

In the first test, you can get the array $ a = [11, 10, 9, 8, 7, 6, 5, 4, 3] $ by performing $ 6 $ operations:

- Set $ a_3 $ to $ 9 $ : the array becomes $ [3, 2, 9, 8, 6, 9, 5, 4, 1] $ ;
- Set $ a_2 $ to $ 10 $ : the array becomes $ [3, 10, 9, 8, 6, 9, 5, 4, 1] $ ;
- Set $ a_6 $ to $ 6 $ : the array becomes $ [3, 10, 9, 8, 6, 6, 5, 4, 1] $ ;
- Set $ a_9 $ to $ 3 $ : the array becomes $ [3, 10, 9, 8, 6, 6, 5, 4, 3] $ ;
- Set $ a_5 $ to $ 7 $ : the array becomes $ [3, 10, 9, 8, 7, 6, 5, 4, 3] $ ;
- Set $ a_1 $ to $ 11 $ : the array becomes $ [11, 10, 9, 8, 7, 6, 5, 4, 3] $ .

 $ a $ is an arithmetic progression: in fact, $ a_{i+1}-a_i=a_i-a_{i-1}=-1 $ for any $ 2 \leq i \leq n-1 $ .

There is no sequence of less than $ 6 $ operations that makes $ a $ an arithmetic progression.

In the second test, you can get the array $ a = [-1, 2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35, 38] $ by performing $ 10 $ operations.

In the third test, you can get the array $ a = [100000, 80000, 60000, 40000, 20000, 0, -20000, -40000, -60000, -80000] $ by performing $ 7 $ operations.

## 样例 #1

### 输入

```
9
3 2 7 8 6 9 5 4 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
14
19 2 15 8 9 14 17 13 4 14 4 11 15 7
```

### 输出

```
10
```

## 样例 #3

### 输入

```
10
100000 1 60000 2 20000 4 8 16 32 64
```

### 输出

```
7
```

## 样例 #4

### 输入

```
4
10000 20000 10000 1
```

### 输出

```
2
```

