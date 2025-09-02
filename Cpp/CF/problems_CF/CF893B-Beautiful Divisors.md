---
title: "Beautiful Divisors"
layout: "post"
diff: 普及-
pid: CF893B
tag: []
---

# Beautiful Divisors

## 题目描述

Recently Luba learned about a special kind of numbers that she calls beautiful numbers. The number is called beautiful iff its binary representation consists of $ k+1 $ consecutive ones, and then $ k $ consecutive zeroes.

Some examples of beautiful numbers:

- $ 1_{2} $ ( $ 1_{10} $ );
- $ 110_{2} $ ( $ 6_{10} $ );
- $ 1111000_{2} $ ( $ 120_{10} $ );
- $ 111110000_{2} $ ( $ 496_{10} $ ).

More formally, the number is beautiful iff there exists some positive integer $ k $ such that the number is equal to $ (2^{k}-1)*(2^{k-1}) $ .

Luba has got an integer number $ n $ , and she wants to find its greatest beautiful divisor. Help her to find it!

## 输入格式

The only line of input contains one number $ n $ ( $ 1<=n<=10^{5} $ ) — the number Luba has got.

## 输出格式

Output one number — the greatest beautiful divisor of Luba's number. It is obvious that the answer always exists.

## 样例 #1

### 输入

```
3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
992

```

### 输出

```
496

```

