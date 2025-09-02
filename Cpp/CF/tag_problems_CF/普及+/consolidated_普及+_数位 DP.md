---
title: "Travelling Salesman and Special Numbers"
layout: "post"
diff: 普及+/提高
pid: CF914C
tag: ['递推', '数位 DP', '进制']
---

# Travelling Salesman and Special Numbers

## 题目描述

The Travelling Salesman spends a lot of time travelling so he tends to get bored. To pass time, he likes to perform operations on numbers. One such operation is to take a positive integer $ x $ and reduce it to the number of bits set to $ 1 $ in the binary representation of $ x $ . For example for number $ 13 $ it's true that $ 13_{10}=1101_{2} $ , so it has $ 3 $ bits set and $ 13 $ will be reduced to $ 3 $ in one operation.

He calls a number special if the minimum number of operations to reduce it to $ 1 $ is $ k $ .

He wants to find out how many special numbers exist which are not greater than $ n $ . Please help the Travelling Salesman, as he is about to reach his destination!

Since the answer can be large, output it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<2^{1000} $ ).

The second line contains integer $ k $ ( $ 0<=k<=1000 $ ).

Note that $ n $ is given in its binary representation without any leading zeros.

## 输出格式

Output a single integer — the number of special numbers not greater than $ n $ , modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, the three special numbers are $ 3 $ , $ 5 $ and $ 6 $ . They get reduced to $ 2 $ in one operation (since there are two set bits in each of $ 3 $ , $ 5 $ and $ 6 $ ) and then to $ 1 $ in one more operation (since there is only one set bit in $ 2 $ ).

## 样例 #1

### 输入

```
110
2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
111111011
2

```

### 输出

```
169

```



---

