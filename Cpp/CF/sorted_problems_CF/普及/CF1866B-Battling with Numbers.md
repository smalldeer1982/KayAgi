---
title: "Battling with Numbers"
layout: "post"
diff: 普及/提高-
pid: CF1866B
tag: []
---

# Battling with Numbers

## 题目描述

On the trip to campus during the mid semester exam period, Chaneka thinks of two positive integers $ X $ and $ Y $ . Since the two integers can be very big, both are represented using their prime factorisations, such that:

- $ X=A_1^{B_1}\times A_2^{B_2}\times\ldots\times A_N^{B_N} $ (each $ A_i $ is prime, each $ B_i $ is positive, and $ A_1<A_2<\ldots<A_N $ )
- $ Y=C_1^{D_1}\times C_2^{D_2}\times\ldots\times C_M^{D_M} $ (each $ C_j $ is prime, each $ D_j $ is positive, and $ C_1<C_2<\ldots<C_M $ )

Chaneka ponders about these two integers for too long throughout the trip, so Chaneka's friend commands her "Gece, deh!" (move fast) in order to not be late for the exam.

Because of that command, Chaneka comes up with a problem, how many pairs of positive integers $ p $ and $ q $ such that $ \text{LCM}(p, q) = X $ and $ \text{GCD}(p, q) = Y $ . Since the answer can be very big, output the answer modulo $ 998\,244\,353 $ .

Notes:

- $ \text{LCM}(p, q) $ is the smallest positive integer that is simultaneously divisible by $ p $ and $ q $ .
- $ \text{GCD}(p, q) $ is the biggest positive integer that simultaneously divides $ p $ and $ q $ .

## 输入格式

The first line contains a single integer $ N $ ( $ 1 \leq N \leq 10^5 $ ) — the number of distinct primes in the prime factorisation of $ X $ .

The second line contains $ N $ integers $ A_1, A_2, A_3, \ldots, A_N $ ( $ 2 \leq A_1 < A_2 < \ldots < A_N \leq 2 \cdot 10^6 $ ; each $ A_i $ is prime) — the primes in the prime factorisation of $ X $ .

The third line contains $ N $ integers $ B_1, B_2, B_3, \ldots, B_N $ ( $ 1 \leq B_i \leq 10^5 $ ) — the exponents in the prime factorisation of $ X $ .

The fourth line contains a single integer $ M $ ( $ 1 \leq M \leq 10^5 $ ) — the number of distinct primes in the prime factorisation of $ Y $ .

The fifth line contains $ M $ integers $ C_1, C_2, C_3, \ldots, C_M $ ( $ 2 \leq C_1 < C_2 < \ldots < C_M \leq 2 \cdot 10^6 $ ; each $ C_j $ is prime) — the primes in the prime factorisation of $ Y $ .

The sixth line contains $ M $ integers $ D_1, D_2, D_3, \ldots, D_M $ ( $ 1 \leq D_j \leq 10^5 $ ) — the exponents in the prime factorisation of $ Y $ .

## 输出格式

An integer representing the number of pairs of positive integers $ p $ and $ q $ such that $ \text{LCM}(p, q) = X $ and $ \text{GCD}(p, q) = Y $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the integers are as follows:

- $ X=2^2\times3^1\times5^1\times7^2=2940 $
- $ Y=3^1\times7^1=21 $

The following are all possible pairs of $ p $ and $ q $ :

- $ p=21 $ , $ q=2940 $
- $ p=84 $ , $ q=735 $
- $ p=105 $ , $ q=588 $
- $ p=147 $ , $ q=420 $
- $ p=420 $ , $ q=147 $
- $ p=588 $ , $ q=105 $
- $ p=735 $ , $ q=84 $
- $ p=2940 $ , $ q=21 $

In the third example, the integers are as follows:

- $ X=2^1\times5^1=10 $
- $ Y=2^1\times3^1=6 $

There is no pair $ p $ and $ q $ that simultaneously satisfies $ \text{LCM}(p,q)=10 $ and $ \text{GCD}(p,q)=6 $ .

## 样例 #1

### 输入

```
4
2 3 5 7
2 1 1 2
2
3 7
1 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
2
1299721 1999993
100000 265
2
1299721 1999993
100000 265
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2
2 5
1 1
2
2 3
1 1
```

### 输出

```
0
```

