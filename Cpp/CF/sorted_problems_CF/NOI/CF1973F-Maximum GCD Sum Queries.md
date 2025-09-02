---
title: "Maximum GCD Sum Queries"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1973F
tag: ['动态规划 DP', '数论']
---

# Maximum GCD Sum Queries

## 题目描述

For $ k $ positive integers $ x_1, x_2, \ldots, x_k $ , the value $ \gcd(x_1, x_2, \ldots, x_k) $ is the greatest common divisor of the integers $ x_1, x_2, \ldots, x_k $ — the largest integer $ z $ such that all the integers $ x_1, x_2, \ldots, x_k $ are divisible by $ z $ .

You are given three arrays $ a_1, a_2, \ldots, a_n $ , $ b_1, b_2, \ldots, b_n $ and $ c_1, c_2, \ldots, c_n $ of length $ n $ , containing positive integers.

You also have a machine that allows you to swap $ a_i $ and $ b_i $ for any $ i $ ( $ 1 \le i \le n $ ). Each swap costs you $ c_i $ coins.

Find the maximum possible value of $ $$$\gcd(a_1, a_2, \ldots, a_n) + \gcd(b_1, b_2, \ldots, b_n) $ $  that you can get by paying in total at most  $ d $  coins for swapping some elements. The amount of coins you have changes a lot, so find the answer to this question for each of the  $ q $  possible values  $ d\_1, d\_2, \\ldots, d\_q$$$.

## 输入格式

There are two integers on the first line — the numbers $ n $ and $ q $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ , $ 1 \leq q \leq 5 \cdot 10^5 $ ).

On the second line, there are $ n $ integers — the numbers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^8 $ ).

On the third line, there are $ n $ integers — the numbers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 10^8 $ ).

On the fourth line, there are $ n $ integers — the numbers $ c_1, c_2, \ldots, c_n $ ( $ 1 \leq c_i \leq 10^9 $ ).

On the fifth line, there are $ q $ integers — the numbers $ d_1, d_2, \ldots, d_q $ ( $ 0 \leq d_i \leq 10^{15} $ ).

## 输出格式

Print $ q $ integers — the maximum value you can get for each of the $ q $ possible values $ d $ .

## 说明/提示

In the first query of the first example, we are not allowed to do any swaps at all, so the answer is $ \gcd(1, 2, 3) + \gcd(4, 5, 6) = 2 $ . In the second query, one of the ways to achieve the optimal value is to swap $ a_2 $ and $ b_2 $ , then the answer is $ \gcd(1, 5, 3) + \gcd(4, 2, 6) = 3 $ .

In the second query of the second example, it's optimal to perform swaps on positions $ 1 $ and $ 3 $ , then the answer is $ \gcd(3, 3, 6, 9, 3) + \gcd(8, 4, 4, 8, 4) = 7 $ and we have to pay $ 40 $ coins in total.

## 样例 #1

### 输入

```
3 4
1 2 3
4 5 6
1 1 1
0 1 2 3
```

### 输出

```
2 3 3 3
```

## 样例 #2

### 输入

```
5 5
3 4 6 8 4
8 3 4 9 3
10 20 30 40 50
5 55 13 1000 113
```

### 输出

```
2 7 3 7 7
```

## 样例 #3

### 输入

```
1 1
3
4
5
0
```

### 输出

```
7
```

