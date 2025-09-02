---
title: "Proper Nutrition"
layout: "post"
diff: 入门
pid: CF898B
tag: ['枚举']
---

# Proper Nutrition

## 题目描述

Vasya has $ n $ burles. One bottle of Ber-Cola costs $ a $ burles and one Bars bar costs $ b $ burles. He can buy any non-negative integer number of bottles of Ber-Cola and any non-negative integer number of Bars bars.

Find out if it's possible to buy some amount of bottles of Ber-Cola and Bars bars and spend exactly $ n $ burles.

In other words, you should find two non-negative integers $ x $ and $ y $ such that Vasya can buy $ x $ bottles of Ber-Cola and $ y $ Bars bars and $ x·a+y·b=n $ or tell that it's impossible.

## 输入格式

First line contains single integer $ n $ ( $ 1<=n<=10000000 $ ) — amount of money, that Vasya has.

Second line contains single integer $ a $ ( $ 1<=a<=10000000 $ ) — cost of one bottle of Ber-Cola.

Third line contains single integer $ b $ ( $ 1<=b<=10000000 $ ) — cost of one Bars bar.

## 输出格式

If Vasya can't buy Bars and Ber-Cola in such a way to spend exactly $ n $ burles print «NO» (without quotes).

Otherwise in first line print «YES» (without quotes). In second line print two non-negative integers $ x $ and $ y $ — number of bottles of Ber-Cola and number of Bars bars Vasya should buy in order to spend exactly $ n $ burles, i.e. $ x·a+y·b=n $ . If there are multiple answers print any of them.

Any of numbers $ x $ and $ y $ can be equal $ 0 $ .

## 说明/提示

In first example Vasya can buy two bottles of Ber-Cola and one Bars bar. He will spend exactly $ 2·2+1·3=7 $ burles.

In second example Vasya can spend exactly $ n $ burles multiple ways:

- buy two bottles of Ber-Cola and five Bars bars;
- buy four bottles of Ber-Cola and don't buy Bars bars;
- don't buy Ber-Cola and buy $ 10 $ Bars bars.

In third example it's impossible to but Ber-Cola and Bars bars in order to spend exactly $ n $ burles.

## 样例 #1

### 输入

```
7
2
3

```

### 输出

```
YES
2 1

```

## 样例 #2

### 输入

```
100
25
10

```

### 输出

```
YES
0 10

```

## 样例 #3

### 输入

```
15
4
8

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
9960594
2551
2557

```

### 输出

```
YES
1951 1949

```

