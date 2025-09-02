---
title: "Sum the Fibonacci"
layout: "post"
diff: 省选/NOI-
pid: CF914G
tag: []
---

# Sum the Fibonacci

## 题目描述

You are given an array $ s $ of $ n $ non-negative integers.

A 5-tuple of integers $ (a,b,c,d,e) $ is said to be valid if it satisfies the following conditions:

- $ 1<=a,b,c,d,e<=n $
- $ (s_{a} $ | $ s_{b}) $ & $ s_{c} $ & $ (s_{d} $ ^ $ s_{e})=2^{i} $ for some integer $ i $
- $ s_{a} $ & $ s_{b}=0 $

Here, '|' is the bitwise OR, '&' is the bitwise AND and '^' is the bitwise XOR operation.

Find the sum of $ f(s_{a} $ | $ s_{b})*f(s_{c})*f(s_{d} $ ^ $ s_{e}) $ over all valid 5-tuples $ (a,b,c,d,e) $ , where $ f(i) $ is the $ i $ -th Fibonnaci number ( $ f(0)=0,f(1)=1,f(i)=f(i-1)+f(i-2) $ ).

Since answer can be is huge output it modulo $ 10^{9}+7 $ .

## 输入格式

The first line of input contains an integer $ n $ ( $ 1<=n<=10^{6} $ ).

The second line of input contains $ n $ integers $ s_{i} $ ( $ 0<=s_{i}<2^{17} $ ).

## 输出格式

Output the sum as described above, modulo $ 10^{9}+7 $

## 样例 #1

### 输入

```
2
1 2

```

### 输出

```
32

```

## 样例 #2

### 输入

```
3
7 4 1

```

### 输出

```
3520

```

## 样例 #3

### 输入

```
10
1 3 0 7 3 7 6 5 7 5

```

### 输出

```
1235424

```

## 样例 #4

### 输入

```
10
50 9 11 44 39 40 5 39 23 7

```

### 输出

```
113860062

```

