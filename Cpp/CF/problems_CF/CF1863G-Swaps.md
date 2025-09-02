---
title: "Swaps"
layout: "post"
diff: 省选/NOI-
pid: CF1863G
tag: []
---

# Swaps

## 题目描述

You are given an array of integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ). You can perform the following operation several (possibly, zero) times:

- pick an arbitrary $ i $ and perform swap $ (a_i, a_{a_i}) $ .

How many distinct arrays is it possible to attain? Output the answer modulo $ (10^9 + 7) $ .

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 10^6 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1\le a_i\le n $ ).

## 输出格式

Output the number of attainable arrays modulo $ (10^9 + 7) $ .

## 说明/提示

In the first example, the initial array is $ [1, 1, 2] $ . If we perform the operation with $ i = 3 $ , we swap $ a_3 $ and $ a_2 $ , obtaining $ [1, 2, 1] $ . One can show that there are no other attainable arrays.

In the second example, the four attainable arrays are $ [2, 1, 4, 3] $ , $ [1, 2, 4, 3] $ , $ [1, 2, 3, 4] $ , $ [2, 1, 3, 4] $ . One can show that there are no other attainable arrays.

## 样例 #1

### 输入

```
3
1 1 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
2 1 4 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
6
2 3 1 1 1 2
```

### 输出

```
18
```

