---
title: "[ARC110D] Binomial Coefficient is Fun"
layout: "post"
diff: 提高+/省选-
pid: AT_arc110_d
tag: []
---

# [ARC110D] Binomial Coefficient is Fun

## 题目描述

我们有一个包含 $N$ 个非负整数的序列 $A$。

对于所有长度为 $N$ 且和不超过 $M$ 的非负整数序列 $B$，求 $\prod_{i = 1}^N {B_i \choose A_i}$ 之和， 对 $(10^9 + 7)$ 取模。

## 输入格式

第一行输入两个整 $N, M$，第二行 $N$ 个整数，表示序列 $A$。

## 输出格式

一行，表示答案对 $(10^9 + 7)$ 取模的值。





### 样例解释1

有四个序列 $B$ 满足 $\prod_{i=1}^N {B_i \choose A_i}$ 至少为 $1$：
	
- $B = \{1, 2, 1\}, \prod_{i = 1}^N{B_i \choose A_i} = {1 \choose 1} \times {2 \choose 2} \times {1 \choose 1} = 1$;
- $B = \{2, 2, 1\}, \prod_{i = 1}^N{B_i \choose A_i} = {2 \choose 1} \times {2 \choose 2} \times {1 \choose 1} = 2$;
- $B = \{1, 3, 1\}, \prod_{i = 1}^N{B_i \choose A_i} = {1 \choose 1} \times {3 \choose 2} \times {1 \choose 1} = 3$;
- $B = \{1, 2, 2\}, \prod_{i = 1}^N{B_i \choose A_i} = {1 \choose 1} \times {2 \choose 2} \times {2 \choose 1} = 2$.

它们的答案之和为 $1+2+3+2=8$。

###### $\text{\tiny{Translated by @nr0728.}}$

## 说明/提示

- $1 \le N \le 2000$
- $1 \le M \le 10^9$
- $0 \le A_i \le 2000$

## 样例 #1

### 输入

```
3 5
1 2 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
10 998244353
31 41 59 26 53 58 97 93 23 84
```

### 输出

```
642612171
```

