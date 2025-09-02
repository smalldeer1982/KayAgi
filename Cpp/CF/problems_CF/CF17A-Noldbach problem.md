---
title: "Noldbach problem"
layout: "post"
diff: 普及/提高-
pid: CF17A
tag: []
---

# Noldbach problem

## 题目描述

Nick is interested in prime numbers. Once he read about Goldbach problem. It states that every even integer greater than $ 2 $ can be expressed as the sum of two primes. That got Nick's attention and he decided to invent a problem of his own and call it Noldbach problem. Since Nick is interested only in prime numbers, Noldbach problem states that at least $ k $ prime numbers from $ 2 $ to $ n $ inclusively can be expressed as the sum of three integer numbers: two neighboring prime numbers and $ 1 $ . For example, 19 = 7 + 11 + 1, or 13 = 5 + 7 + 1.

Two prime numbers are called neighboring if there are no other prime numbers between them.

You are to help Nick, and find out if he is right or wrong.

## 输入格式

The first line of the input contains two integers $ n $ ( $ 2<=n<=1000 $ ) and $ k $ ( $ 0<=k<=1000 $ ).

## 输出格式

Output YES if at least $ k $ prime numbers from $ 2 $ to $ n $ inclusively can be expressed as it was described above. Otherwise output NO.

## 说明/提示

In the first sample the answer is YES since at least two numbers can be expressed as it was described (for example, 13 and 19). In the second sample the answer is NO since it is impossible to express 7 prime numbers from 2 to 45 in the desired form.

## 样例 #1

### 输入

```
27 2

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
45 7

```

### 输出

```
NO
```

