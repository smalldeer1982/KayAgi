---
title: "Unusual Sequences"
layout: "post"
diff: 提高+/省选-
pid: CF900D
tag: ['数论', '莫比乌斯反演', '组合数学', '容斥原理']
---

# Unusual Sequences

## 题目描述

Count the number of distinct sequences $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i} $ ) consisting of positive integers such that $ gcd(a_{1},a_{2},...,a_{n})=x $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF900D/b6b0405f12ef386aeb195f818cd0534bcf4623e0.png). As this number could be large, print the answer modulo $ 10^{9}+7 $ .

 $ gcd $ here means the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor).

## 输入格式

The only line contains two positive integers $ x $ and $ y $ ( $ 1<=x,y<=10^{9} $ ).

## 输出格式

Print the number of such sequences modulo $ 10^{9}+7 $ .

## 说明/提示

There are three suitable sequences in the first test: $ (3,3,3) $ , $ (3,6) $ , $ (6,3) $ .

There are no suitable sequences in the second test.

## 样例 #1

### 输入

```
3 9

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 8

```

### 输出

```
0

```

