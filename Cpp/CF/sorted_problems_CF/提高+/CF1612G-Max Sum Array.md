---
title: "Max Sum Array"
layout: "post"
diff: 提高+/省选-
pid: CF1612G
tag: []
---

# Max Sum Array

## 题目描述

You are given an array $ c = [c_1, c_2, \dots, c_m] $ . An array $ a = [a_1, a_2, \dots, a_n] $ is constructed in such a way that it consists of integers $ 1, 2, \dots, m $ , and for each $ i \in [1,m] $ , there are exactly $ c_i $ occurrences of integer $ i $ in $ a $ . So, the number of elements in $ a $ is exactly $ \sum\limits_{i=1}^{m} c_i $ .

Let's define for such array $ a $ the value $ f(a) $ as $ $$$f(a) = \sum_{\substack{1 \le i < j \le n\\ a_i = a_j}}{j - i}. $ $ </p><p>In other words,  $ f(a) $  is the total sum of distances between all pairs of equal elements.</p><p>Your task is to calculate the maximum possible value of  $ f(a) $  and the number of arrays yielding the maximum possible value of  $ f(a)$$$. Two arrays are considered different, if elements at some position differ.

## 输入格式

The first line contains a single integer $ m $ ( $ 1 \le m \le 5 \cdot 10^5 $ ) — the size of the array $ c $ .

The second line contains $ m $ integers $ c_1, c_2, \dots, c_m $ ( $ 1 \le c_i \le 10^6 $ ) — the array $ c $ .

## 输出格式

Print two integers — the maximum possible value of $ f(a) $ and the number of arrays $ a $ with such value. Since both answers may be too large, print them modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, all possible arrays $ a $ are permutations of $ [1, 2, 3, 4, 5, 6] $ . Since each array $ a $ will have $ f(a) = 0 $ , so maximum value is $ f(a) = 0 $ and there are $ 6! = 720 $ such arrays.

In the second example, the only possible array consists of $ 10^6 $ ones and its $ f(a) = \sum\limits_{1 \le i < j \le 10^6}{j - i} = 166\,666\,666\,666\,500\,000 $ and $ 166\,666\,666\,666\,500\,000 \bmod{10^9 + 7} = 499\,833\,345 $ .

## 样例 #1

### 输入

```
6
1 1 1 1 1 1
```

### 输出

```
0 720
```

## 样例 #2

### 输入

```
1
1000000
```

### 输出

```
499833345 1
```

## 样例 #3

### 输入

```
7
123 451 234 512 345 123 451
```

### 输出

```
339854850 882811119
```

