---
title: "Fraction"
layout: "post"
diff: 普及-
pid: CF854A
tag: []
---

# Fraction

## 题目描述

Petya is a big fan of mathematics, especially its part related to fractions. Recently he learned that a fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF854A/9f8335062cbc9ed9ecb9607f5d06d53170cb1e1a.png) is called proper iff its numerator is smaller than its denominator ( $ a<b $ ) and that the fraction is called irreducible if its numerator and its denominator are coprime (they do not have positive common divisors except $ 1 $ ).

During his free time, Petya thinks about proper irreducible fractions and converts them to decimals using the calculator. One day he mistakenly pressed addition button ( $ + $ ) instead of division button ( $ ÷ $ ) and got sum of numerator and denominator that was equal to $ n $ instead of the expected decimal notation.

Petya wanted to restore the original fraction, but soon he realized that it might not be done uniquely. That's why he decided to determine maximum possible proper irreducible fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF854A/9f8335062cbc9ed9ecb9607f5d06d53170cb1e1a.png) such that sum of its numerator and denominator equals $ n $ . Help Petya deal with this problem.

## 输入格式

In the only line of input there is an integer $ n $ ( $ 3<=n<=1000 $ ), the sum of numerator and denominator of the fraction.

## 输出格式

Output two space-separated positive integers $ a $ and $ b $ , numerator and denominator of the maximum possible proper irreducible fraction satisfying the given sum.

## 样例 #1

### 输入

```
3

```

### 输出

```
1 2

```

## 样例 #2

### 输入

```
4

```

### 输出

```
1 3

```

## 样例 #3

### 输入

```
12

```

### 输出

```
5 7

```

