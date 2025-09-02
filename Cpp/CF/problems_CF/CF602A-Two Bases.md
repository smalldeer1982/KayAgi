---
title: "Two Bases"
layout: "post"
diff: 入门
pid: CF602A
tag: []
---

# Two Bases

## 题目描述

After seeing the "ALL YOUR BASE ARE BELONG TO US" meme for the first time, numbers $ X $ and $ Y $ realised that they have different bases, which complicated their relations.

You're given a number $ X $ represented in base $ b_{x} $ and a number $ Y $ represented in base $ b_{y} $ . Compare those two numbers.

## 输入格式

The first line of the input contains two space-separated integers $ n $ and $ b_{x} $ ( $ 1<=n<=10 $ , $ 2<=b_{x}<=40 $ ), where $ n $ is the number of digits in the $ b_{x} $ -based representation of $ X $ .

The second line contains $ n $ space-separated integers $ x_{1},x_{2},...,x_{n} $ ( $ 0<=x_{i}&lt;b_{x} $ ) — the digits of $ X $ . They are given in the order from the most significant digit to the least significant one.

The following two lines describe $ Y $ in the same way: the third line contains two space-separated integers $ m $ and $ b_{y} $ ( $ 1<=m<=10 $ , $ 2<=b_{y}<=40 $ , $ b_{x}≠b_{y} $ ), where $ m $ is the number of digits in the $ b_{y} $ -based representation of $ Y $ , and the fourth line contains $ m $ space-separated integers $ y_{1},y_{2},...,y_{m} $ ( $ 0<=y_{i}&lt;b_{y} $ ) — the digits of $ Y $ .

There will be no leading zeroes. Both $ X $ and $ Y $ will be positive. All digits of both numbers are given in the standard decimal numeral system.

## 输出格式

Output a single character (quotes for clarity):

- '<' if $ X&lt;Y $
- '>' if $ X&gt;Y $
- '=' if $ X=Y $

## 说明/提示

In the first sample, $ X=101111_{2}=47_{10}=Y $ .

In the second sample, $ X=102_{3}=21_{5} $ and $ Y=24_{5}=112_{3} $ , thus $ X&lt;Y $ .

In the third sample, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF602A/3af4a723fb1330e2df57121d231422a1cbe8a641.png) and $ Y=4803150_{9} $ . We may notice that $ X $ starts with much larger digits and $ b_{x} $ is much larger than $ b_{y} $ , so $ X $ is clearly larger than $ Y $ .

## 样例 #1

### 输入

```
6 2
1 0 1 1 1 1
2 10
4 7

```

### 输出

```
=

```

## 样例 #2

### 输入

```
3 3
1 0 2
2 5
2 4

```

### 输出

```
&lt;

```

## 样例 #3

### 输入

```
7 16
15 15 4 0 0 7 10
7 9
4 8 0 3 1 5 0

```

### 输出

```
&gt;

```

