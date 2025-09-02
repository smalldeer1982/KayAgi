---
title: "AmShZ Farm"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1528F
tag: ['组合数学', 'Stirling 数']
---

# AmShZ Farm

## 题目描述

To AmShZ, all arrays are equal, but some arrays are more-equal than others. Specifically, the arrays consisting of $ n $ elements from $ 1 $ to $ n $ that can be turned into permutations of numbers from $ 1 $ to $ n $ by adding a non-negative integer to each element.

Mashtali who wants to appear in every problem statement thinks that an array $ b $ consisting of $ k $ elements is compatible with a more-equal array $ a $ consisting of $ n $ elements if for each $ 1 \le i \le k $ we have $ 1 \le b_i \le n $ and also $ a_{b_1} = a_{b_2} = \ldots = a_{b_k} $ .

Find the number of pairs of arrays $ a $ and $ b $ such that $ a $ is a more-equal array consisting of $ n $ elements and $ b $ is an array compatible with $ a $ consisting of $ k $ elements modulo $ 998244353 $ .

Note that the elements of $ b $ are not necessarily distinct, same holds for $ a $ .

## 输入格式

The first line of input contains two integers $ n $ and $ k $ $ (1 \le n \le 10^9 , 1 \le k \le 10^5) $ .

## 输出格式

Print a single integer — the answer to the problem modulo $ 998244353 $ .

## 说明/提示

There are eight possible pairs for the second example:

1. $ a = \{1, 1\}, b = \{1, 1\} $
2. $ a = \{1, 1\}, b = \{1, 2\} $
3. $ a = \{1, 1\}, b = \{2, 1\} $
4. $ a = \{1, 1\}, b = \{2, 2\} $
5. $ a = \{1, 2\}, b = \{1, 1\} $
6. $ a = \{1, 2\}, b = \{2, 2\} $
7. $ a = \{2, 1\}, b = \{1, 1\} $
8. $ a = \{2, 1\}, b = \{2, 2\} $

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
8
```

## 样例 #3

### 输入

```
5 4
```

### 输出

```
50400
```

## 样例 #4

### 输入

```
20 100
```

### 输出

```
807645526
```

## 样例 #5

### 输入

```
10000000 10000
```

### 输出

```
883232350
```

