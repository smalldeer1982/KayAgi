---
title: "Boneca Ambalabu"
layout: "post"
diff: 普及/提高-
pid: CF2094E
tag: ['贪心', '位运算']
---

# Boneca Ambalabu

## 题目描述

Boneca Ambalabu 给你一个包含 $n$ 个整数的序列 $a_1,a_2,\ldots,a_n$。

在所有 $1 \leq k \leq n$ 中，输出 $(a_k \oplus a_1) + (a_k \oplus a_2) + \ldots + (a_k \oplus a_n)$ 的最大值。注意 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——独立测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 2 \cdot 10^5$）——数组的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$（$0 \leq a_i < 2^{30}$）。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，在新的一行输出最大值。

## 说明/提示

在第一个测试用例中，我们能得到的最大值是 $(18 \oplus 18) + (18 \oplus 18) + (18 \oplus 18) = 0$。

在第二个测试用例中，我们选择 $k=5$ 得到 $(16 \oplus 1) + (16 \oplus 2) + (16 \oplus 4) + (16 \oplus 8) + (16 \oplus 16) = 79$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
18 18 18
5
1 2 4 8 16
5
8 13 4 5 15
6
625 676 729 784 841 900
1
1
```

### 输出

```
0
79
37
1555
0
```

