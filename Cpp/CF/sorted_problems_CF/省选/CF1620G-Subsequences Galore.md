---
title: "Subsequences Galore"
layout: "post"
diff: 省选/NOI-
pid: CF1620G
tag: []
---

# Subsequences Galore

## 题目描述

For a sequence of strings $ [t_1, t_2, \dots, t_m] $ , let's define the function $ f([t_1, t_2, \dots, t_m]) $ as the number of different strings (including the empty string) that are subsequences of at least one string $ t_i $ . $ f([]) = 0 $ (i. e. the number of such strings for an empty sequence is $ 0 $ ).

You are given a sequence of strings $ [s_1, s_2, \dots, s_n] $ . Every string in this sequence consists of lowercase Latin letters and is sorted (i. e., each string begins with several (maybe zero) characters a, then several (maybe zero) characters b, ..., ends with several (maybe zero) characters z).

For each of $ 2^n $ subsequences of $ [s_1, s_2, \dots, s_n] $ , calculate the value of the function $ f $ modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 23 $ ) — the number of strings.

Then $ n $ lines follow. The $ i $ -th line contains the string $ s_i $ ( $ 1 \le |s_i| \le 2 \cdot 10^4 $ ), consisting of lowercase Latin letters. Each string $ s_i $ is sorted.

## 输出格式

Since printing up to $ 2^{23} $ integers would be really slow, you should do the following:

For each of the $ 2^n $ subsequences (which we denote as $ [s_{i_1}, s_{i_2}, \dots, s_{i_k}] $ ), calculate $ f([s_{i_1}, s_{i_2}, \dots, s_{i_k}]) $ , take it modulo $ 998244353 $ , then multiply it by $ k \cdot (i_1 + i_2 + \dots + i_k) $ . Print the XOR of all $ 2^n $ integers you get.

The indices $ i_1, i_2, \dots, i_k $ in the description of each subsequences are $ 1 $ -indexed (i. e. are from $ 1 $ to $ n $ ).

## 样例 #1

### 输入

```
3
a
b
c
```

### 输出

```
92
```

## 样例 #2

### 输入

```
2
aa
a
```

### 输出

```
21
```

## 样例 #3

### 输入

```
2
a
a
```

### 输出

```
10
```

## 样例 #4

### 输入

```
2
abcd
aabb
```

### 输出

```
124
```

## 样例 #5

### 输入

```
3
ddd
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaabbbbbbbbbbbcccccccccccciiiiiiiiiiiiiiiiiiiiiiooooooooooqqqqqqqqqqqqqqqqqqvvvvvzzzzzzzzzzzz
```

### 输出

```
15706243380
```

