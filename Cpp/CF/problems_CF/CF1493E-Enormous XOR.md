---
title: "Enormous XOR"
layout: "post"
diff: 省选/NOI-
pid: CF1493E
tag: []
---

# Enormous XOR

## 题目描述

You are given two integers $ l $ and $ r $ in binary representation. Let $ g(x, y) $ be equal to the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all integers from $ x $ to $ y $ inclusive (that is $ x \oplus (x+1) \oplus \dots \oplus (y-1) \oplus y $ ). Let's define $ f(l, r) $ as the maximum of all values of $ g(x, y) $ satisfying $ l \le x \le y \le r $ .

Output $ f(l, r) $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the length of the binary representation of $ r $ .

The second line contains the binary representation of $ l $ — a string of length $ n $ consisting of digits $ 0 $ and $ 1 $ ( $ 0 \le l < 2^n $ ).

The third line contains the binary representation of $ r $ — a string of length $ n $ consisting of digits $ 0 $ and $ 1 $ ( $ 0 \le r < 2^n $ ).

It is guaranteed that $ l \le r $ . The binary representation of $ r $ does not contain any extra leading zeros (if $ r=0 $ , the binary representation of it consists of a single zero). The binary representation of $ l $ is preceded with leading zeros so that its length is equal to $ n $ .

## 输出格式

In a single line output the value of $ f(l, r) $ for the given pair of $ l $ and $ r $ in binary representation without extra leading zeros.

## 说明/提示

In sample test case $ l=19 $ , $ r=122 $ . $ f(x,y) $ is maximal and is equal to $ 127 $ , with $ x=27 $ , $ y=100 $ , for example.

## 样例 #1

### 输入

```
7
0010011
1111010
```

### 输出

```
1111111
```

## 样例 #2

### 输入

```
4
1010
1101
```

### 输出

```
1101
```

