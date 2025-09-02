---
title: "Lunar New Year and a Recursive Sequence"
layout: "post"
diff: 省选/NOI-
pid: CF1106F
tag: ['数学', '矩阵加速']
---

# Lunar New Year and a Recursive Sequence

## 题目描述

Lunar New Year is approaching, and Bob received a gift from his friend recently — a recursive sequence! He loves this sequence very much and wants to play with it.

Let $ f_1, f_2, \ldots, f_i, \ldots $ be an infinite sequence of positive integers. Bob knows that for $ i > k $ , $ f_i $ can be obtained by the following recursive equation:

 $ $$$f_i = \left(f_{i - 1} ^ {b_1} \cdot f_{i - 2} ^ {b_2} \cdot \cdots \cdot f_{i - k} ^ {b_k}\right) \bmod p, $ $ </p><p>which in short is</p><p> $ $ f_i = \left(\prod_{j = 1}^{k} f_{i - j}^{b_j}\right) \bmod p, $ $ </p><p>where  $ p = 998\\,244\\,353 $  (a widely-used prime),  $ b\_1, b\_2, \\ldots, b\_k $  are known integer constants, and  $ x \\bmod y $  denotes the remainder of  $ x $  divided by  $ y $ .</p><p>Bob lost the values of  $ f\_1, f\_2, \\ldots, f\_k $ , which is extremely troublesome – these are the basis of the sequence! Luckily, Bob remembers the first  $ k - 1 $  elements of the sequence:  $ f\_1 = f\_2 = \\ldots = f\_{k - 1} = 1 $  and the  $ n $ -th element:  $ f\_n = m $ . Please find any possible value of  $ f\_k$$$. If no solution exists, just tell Bob that it is impossible to recover his favorite sequence, regardless of Bob's sadness.

## 输入格式

The first line contains a positive integer $ k $ ( $ 1 \leq k \leq 100 $ ), denoting the length of the sequence $ b_1, b_2, \ldots, b_k $ .

The second line contains $ k $ positive integers $ b_1, b_2, \ldots, b_k $ ( $ 1 \leq b_i < p $ ).

The third line contains two positive integers $ n $ and $ m $ ( $ k < n \leq 10^9 $ , $ 1 \leq m < p $ ), which implies $ f_n = m $ .

## 输出格式

Output a possible value of $ f_k $ , where $ f_k $ is a positive integer satisfying $ 1 \leq f_k < p $ . If there are multiple answers, print any of them. If no such $ f_k $ makes $ f_n = m $ , output $ -1 $ instead.

It is easy to show that if there are some possible values of $ f_k $ , there must be at least one satisfying $ 1 \leq f_k < p $ .

## 说明/提示

In the first sample, we have $ f_4 = f_3^2 \cdot f_2^3 \cdot f_1^5 $ . Therefore, applying $ f_3 = 4 $ , we have $ f_4 = 16 $ . Note that there can be multiple answers.

In the third sample, applying $ f_7 = 1 $ makes $ f_{23333} = 1 $ .

In the fourth sample, no such $ f_1 $ makes $ f_{88888} = 66666 $ . Therefore, we output $ -1 $ instead.

## 样例 #1

### 输入

```
3
2 3 5
4 16

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5
4 7 1 5 6
7 14187219

```

### 输出

```
6

```

## 样例 #3

### 输入

```
8
2 3 5 6 1 7 9 10
23333 1

```

### 输出

```
1

```

## 样例 #4

### 输入

```
1
2
88888 66666

```

### 输出

```
-1

```

## 样例 #5

### 输入

```
3
998244352 998244352 998244352
4 2

```

### 输出

```
-1

```

## 样例 #6

### 输入

```
10
283 463 213 777 346 201 463 283 102 999
2333333 6263423

```

### 输出

```
382480067

```

