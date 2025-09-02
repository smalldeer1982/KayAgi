---
title: "Distance to Different"
layout: "post"
diff: 提高+/省选-
pid: CF1989E
tag: ['动态规划 DP']
---

# Distance to Different

## 题目描述

Consider an array $ a $ of $ n $ integers, where every element is from $ 1 $ to $ k $ , and every integer from $ 1 $ to $ k $ appears at least once.

Let the array $ b $ be constructed as follows: for the $ i $ -th element of $ a $ , $ b_i $ is the distance to the closest element in $ a $ which is not equal to $ a_i $ . In other words, $ b_i = \min \limits_{j \in [1, n], a_j \ne a_i} |i - j| $ .

For example, if $ a = [1, 1, 2, 3, 3, 3, 3, 1] $ , then $ b = [2, 1, 1, 1, 2, 2, 1, 1] $ .

Calculate the number of different arrays $ b $ you can obtain if you consider all possible arrays $ a $ , and print it modulo $ 998244353 $ .

## 输入格式

The only line of the input contains two integers $ n $ and $ k $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ 2 \le k \le \min(n, 10) $ ).

## 输出格式

Print one integer — the number of different arrays $ b $ you can obtain, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6 2
```

### 输出

```
20
```

## 样例 #4

### 输入

```
6 5
```

### 输出

```
3
```

## 样例 #5

### 输入

```
133 7
```

### 输出

```
336975971
```

