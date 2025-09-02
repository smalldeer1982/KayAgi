---
title: "Divisors"
layout: "post"
diff: 提高+/省选-
pid: CF448E
tag: []
---

# Divisors

## 题目描述

Bizon the Champion isn't just friendly, he also is a rigorous coder.

Let's define function $ f(a) $ , where $ a $ is a sequence of integers. Function $ f(a) $ returns the following sequence: first all divisors of $ a_{1} $ go in the increasing order, then all divisors of $ a_{2} $ go in the increasing order, and so on till the last element of sequence $ a $ . For example, $ f([2,9,1])=[1,2,1,3,9,1] $ .

Let's determine the sequence $ X_{i} $ , for integer $ i $ $ (i>=0) $ : $ X_{0}=[X] $ ( $ [X] $ is a sequence consisting of a single number $ X $ ), $ X_{i}=f(X_{i-1}) $ $ (i&gt;0) $ . For example, at $ X=6 $ we get $ X_{0}=[6] $ , $ X_{1}=[1,2,3,6] $ , $ X_{2}=[1,1,2,1,3,1,2,3,6] $ .

Given the numbers $ X $ and $ k $ , find the sequence $ X_{k} $ . As the answer can be rather large, find only the first $ 10^{5} $ elements of this sequence.

## 输入格式

A single line contains two space-separated integers — $ X $ $ (1<=X<=10^{12}) $ and $ k $ $ (0<=k<=10^{18}) $ .

## 输出格式

Print the elements of the sequence $ X_{k} $ in a single line, separated by a space. If the number of elements exceeds $ 10^{5} $ , then print only the first $ 10^{5} $ elements.

## 样例 #1

### 输入

```
6 1

```

### 输出

```
1 2 3 6 

```

## 样例 #2

### 输入

```
4 2

```

### 输出

```
1 1 2 1 2 4 

```

## 样例 #3

### 输入

```
10 3

```

### 输出

```
1 1 1 2 1 1 5 1 1 2 1 5 1 2 5 10 

```

