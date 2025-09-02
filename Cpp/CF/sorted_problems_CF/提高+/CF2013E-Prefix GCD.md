---
title: "Prefix GCD"
layout: "post"
diff: 提高+/省选-
pid: CF2013E
tag: ['贪心', '数论']
---

# Prefix GCD

## 题目描述

Since Mansur is tired of making legends, there will be no legends for this task.

You are given an array of positive integer numbers $ a_1, a_2, \ldots, a_n $ . The elements of the array can be rearranged in any order. You need to find the smallest possible value of the expression $ $$$\gcd(a_1) + \gcd(a_1, a_2) + \ldots + \gcd(a_1, a_2, \ldots, a_n), $ $  where  $ \\gcd(a\_1, a\_2, \\ldots, a\_n) $  denotes the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor (GCD)</a> of  $ a\_1, a\_2, \\ldots, a\_n$$$.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single number $ n $ ( $ 1 \le n \le 10^5 $ ) — the size of the array.

The second line of each test case contains $ n $ numbers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^5 $ ) — the initial array.

The sum of $ n $ over all test cases does not exceed $ 10^5 $ .

The sum of $ \max(a_1, a_2, \ldots, a_n) $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single number on a separate line — the answer to the problem.

## 说明/提示

In the first test case, the elements can be rearranged as follows: $ [2, 4, 2] $ . Then the answer will be $ \gcd(2) + \gcd(2, 4) + \gcd(2, 4, 2) = 2 + 2 + 2 = 6 $ .

In the third test case, the elements can be rearranged as follows: $ [6, 10, 15] $ . Then the answer will be $ \gcd(6) + \gcd(6, 10) + \gcd(6, 10, 15) = 6 + 2 + 1 = 9 $ .

## 样例 #1

### 输入

```
5
3
4 2 2
2
6 3
3
10 15 6
5
6 42 12 52 20
4
42 154 231 66
```

### 输出

```
6
6
9
14
51
```

