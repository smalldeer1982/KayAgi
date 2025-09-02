---
title: "Prime Number"
layout: "post"
diff: 普及+/提高
pid: CF359C
tag: []
---

# Prime Number

## 题目描述

Simon has a prime number $ x $ and an array of non-negative integers $ a_{1},a_{2},...,a_{n} $ .

Simon loves fractions very much. Today he wrote out number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/30ceed91a13d03a8240cb0eaa60aa832738192a0.png) on a piece of paper. After Simon led all fractions to a common denominator and summed them up, he got a fraction: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/e0810919ce9aff20137654b00c598ccaa33ece8d.png), where number $ t $ equals $ x^{a_{1}+a_{2}+...+a_{n}} $ . Now Simon wants to reduce the resulting fraction.

Help him, find the greatest common divisor of numbers $ s $ and $ t $ . As GCD can be rather large, print it as a remainder after dividing it by number $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains two positive integers $ n $ and $ x $ ( $ 1<=n<=10^{5} $ , $ 2<=x<=10^{9} $ ) — the size of the array and the prime number.

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{1}<=a_{2}<=...<=a_{n}<=10^{9} $ ).

## 输出格式

Print a single number — the answer to the problem modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/a1e2654626975b2109236cae030121c98f55e9d0.png). Thus, the answer to the problem is $ 8 $ .

In the second sample, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/21aa04c7cee2f3b67d81ff94d48ffd8a4add7ce1.png). The answer to the problem is $ 27 $ , as $ 351=13·27 $ , $ 729=27·27 $ .

In the third sample the answer to the problem is $ 1073741824 mod 1000000007=73741817 $ .

In the fourth sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/b75d78ae6544e1f3836b40eca1b29ba08f0f671d.png). Thus, the answer to the problem is $ 1 $ .

## 样例 #1

### 输入

```
2 2
2 2

```

### 输出

```
8

```

## 样例 #2

### 输入

```
3 3
1 2 3

```

### 输出

```
27

```

## 样例 #3

### 输入

```
2 2
29 29

```

### 输出

```
73741817

```

## 样例 #4

### 输入

```
4 5
0 0 0 0

```

### 输出

```
1

```

