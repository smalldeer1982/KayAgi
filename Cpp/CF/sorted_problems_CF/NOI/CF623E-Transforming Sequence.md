---
title: "Transforming Sequence"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF623E
tag: ['快速傅里叶变换 FFT']
---

# Transforming Sequence

## 题目描述

Let's define the transformation $ P $ of a sequence of integers $ a_{1},a_{2},...,a_{n} $ as $ b_{1},b_{2},...,b_{n} $ , where $ b_{i}=a_{1} | a_{2} | ... | a_{i} $ for all $ i=1,2,...,n $ , where $ | $ is the bitwise OR operation.

Vasya consequently applies the transformation $ P $ to all sequences of length $ n $ consisting of integers from $ 1 $ to $ 2^{k}-1 $ inclusive. He wants to know how many of these sequences have such property that their transformation is a strictly increasing sequence. Help him to calculate this number modulo $ 10^{9}+7 $ .

## 输入格式

The only line of the input contains two integers $ n $ and $ k $ ( $ 1<=n<=10^{18},1<=k<=30000 $ ).

## 输出格式

Print a single integer — the answer to the problem modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2 3

```

### 输出

```
30

```

## 样例 #3

### 输入

```
3 3

```

### 输出

```
48

```

