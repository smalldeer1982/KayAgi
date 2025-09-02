---
title: "Winter is here"
layout: "post"
diff: 省选/NOI-
pid: CF839D
tag: []
---

# Winter is here

## 题目描述

Winter is here at the North and the White Walkers are close. John Snow has an army consisting of $ n $ soldiers. While the rest of the world is fighting for the Iron Throne, he is going to get ready for the attack of the White Walkers.

He has created a method to know how strong his army is. Let the $ i $ -th soldier’s strength be $ a_{i} $ . For some $ k $ he calls $ i_{1},i_{2},...,i_{k} $ a clan if $ i_{1}&lt;i_{2}&lt;i_{3}&lt;...&lt;i_{k} $ and $ gcd(a_{i1},a_{i2},...,a_{ik})&gt;1 $ . He calls the strength of that clan $ k·gcd(a_{i1},a_{i2},...,a_{ik}) $ . Then he defines the strength of his army by the sum of strengths of all possible clans.

Your task is to find the strength of his army. As the number may be very large, you have to print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

Greatest common divisor (gcd) of a sequence of integers is the maximum possible integer so that each element of the sequence is divisible by it.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=200000 $ ) — the size of the army.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=1000000 $ ) — denoting the strengths of his soldiers.

## 输出格式

Print one integer — the strength of John Snow's army modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first sample the clans are $ {1},{2},{1,2} $ so the answer will be $ 1·3+1·3+2·3=12 $

## 样例 #1

### 输入

```
3
3 3 1

```

### 输出

```
12

```

## 样例 #2

### 输入

```
4
2 3 4 6

```

### 输出

```
39

```

