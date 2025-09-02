---
title: "Fibonacci-ish"
layout: "post"
diff: 提高+/省选-
pid: CF633D
tag: ['枚举', '剪枝', '概率论']
---

# Fibonacci-ish

## 题目描述

Yash has recently learnt about the Fibonacci sequence and is very excited about it. He calls a sequence Fibonacci-ish if

1. the sequence consists of at least two elements
2. $ f_{0} $ and $ f_{1} $ are arbitrary
3. $ f_{n+2}=f_{n+1}+f_{n} $ for all $ n>=0 $ .

You are given some sequence of integers $ a_{1},a_{2},...,a_{n} $ . Your task is rearrange elements of this sequence in such a way that its longest possible prefix is Fibonacci-ish sequence.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 2<=n<=1000 $ ) — the length of the sequence $ a_{i} $ .

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ |a_{i}|<=10^{9} $ ).

## 输出格式

Print the length of the longest possible Fibonacci-ish prefix of the given sequence after rearrangement.

## 说明/提示

In the first sample, if we rearrange elements of the sequence as $ -1 $ , $ 2 $ , $ 1 $ , the whole sequence $ a_{i} $ would be Fibonacci-ish.

In the second sample, the optimal way to rearrange elements is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/d3ff4ea2c12e52c9ca4c15e14139f2b01f478bed.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/67db7509088e9e5340d450cc0af986d1466ce169.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/7be78903e0b1130fefbb3533b84d31cf4efaa940.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF633D/0d98505f3f5d3d9cd5c06747ea4bb30d03a8d1e8.png), $ 28 $ .

## 样例 #1

### 输入

```
3
1 2 -1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
28 35 7 14 21

```

### 输出

```
4

```

