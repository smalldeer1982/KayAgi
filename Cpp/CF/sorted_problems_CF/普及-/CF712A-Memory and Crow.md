---
title: "Memory and Crow"
layout: "post"
diff: 普及-
pid: CF712A
tag: []
---

# Memory and Crow

## 题目描述

There are $ n $ integers $ b_{1},b_{2},...,b_{n} $ written in a row. For all $ i $ from $ 1 $ to $ n $ , values $ a_{i} $ are defined by the crows performing the following procedure:

- The crow sets $ a_{i} $ initially $ 0 $ .
- The crow then adds $ b_{i} $ to $ a_{i} $ , subtracts $ b_{i+1} $ , adds the $ b_{i+2} $ number, and so on until the $ n $ 'th number. Thus, $ a_{i}=b_{i}-b_{i+1}+b_{i+2}-b_{i+3}... $ .

Memory gives you the values $ a_{1},a_{2},...,a_{n} $ , and he now wants you to find the initial numbers $ b_{1},b_{2},...,b_{n} $ written in the row? Can you do it?

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the number of integers written in the row.

The next line contains $ n $ , the $ i $ 'th of which is $ a_{i} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ) — the value of the $ i $ 'th number.

## 输出格式

Print $ n $ integers corresponding to the sequence $ b_{1},b_{2},...,b_{n} $ . It's guaranteed that the answer is unique and fits in 32-bit integer type.

## 说明/提示

In the first sample test, the crows report the numbers $ 6 $ , $ -4 $ , $ 8 $ , $ -2 $ , and $ 3 $ when he starts at indices $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ respectively. It is easy to check that the sequence $ 2 $ $ 4 $ $ 6 $ $ 1 $ $ 3 $ satisfies the reports. For example, $ 6=2-4+6-1+3 $ , and $ -4=4-6+1-3 $ .

In the second sample test, the sequence $ 1 $ , $ -3 $ , $ 4 $ , $ 11 $ , $ 6 $ satisfies the reports. For example, $ 5=11-6 $ and $ 6=6 $ .

## 样例 #1

### 输入

```
5
6 -4 8 -2 3

```

### 输出

```
2 4 6 1 3 

```

## 样例 #2

### 输入

```
5
3 -2 -1 5 6

```

### 输出

```
1 -3 4 11 6 

```

