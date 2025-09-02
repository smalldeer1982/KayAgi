---
title: "MEX counting"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1608F
tag: []
---

# MEX counting

## 题目描述

For an array $ c $ of nonnegative integers, $ MEX(c) $ denotes the smallest nonnegative integer that doesn't appear in it. For example, $ MEX([0, 1, 3]) = 2 $ , $ MEX([42]) = 0 $ .

You are given integers $ n, k $ , and an array $ [b_1, b_2, \ldots, b_n] $ .

Find the number of arrays $ [a_1, a_2, \ldots, a_n] $ , for which the following conditions hold:

- $ 0 \le a_i \le n $ for each $ i $ for each $ i $ from $ 1 $ to $ n $ .
- $ |MEX([a_1, a_2, \ldots, a_i]) - b_i| \le k $ for each $ i $ from $ 1 $ to $ n $ .

As this number can be very big, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line of the input contains two integers $ n, k $ ( $ 1 \le n \le 2000 $ , $ 0 \le k \le 50 $ ).

The second line of the input contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ -k \le b_i \le n+k $ ) — elements of the array $ b $ .

## 输出格式

Output a single integer — the number of arrays which satisfy the conditions from the statement, modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
4 0
0 0 0 0
```

### 输出

```
256
```

## 样例 #2

### 输入

```
4 1
0 0 0 0
```

### 输出

```
431
```

## 样例 #3

### 输入

```
4 1
0 0 1 1
```

### 输出

```
509
```

## 样例 #4

### 输入

```
5 2
0 0 2 2 0
```

### 输出

```
6546
```

## 样例 #5

### 输入

```
3 2
-2 0 4
```

### 输出

```
11
```

