---
title: "Koxia and Number Theory"
layout: "post"
diff: 普及+/提高
pid: CF1770C
tag: []
---

# Koxia and Number Theory

## 题目描述

Joi has an array $ a $ of $ n $ positive integers. Koxia wants you to determine whether there exists a positive integer $ x > 0 $ such that $ \gcd(a_i+x,a_j+x)=1 $ for all $ 1 \leq i < j \leq n $ .

Here $ \gcd(y, z) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ y $ and $ z $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains an integer $ n $ ( $ 2 \leq n \leq 100 $ ) — the size of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq {10}^{18} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case, output "YES" (without quotes) if there exists a positive integer $ x $ such that $ \gcd(a_i+x,a_j+x)=1 $ for all $ 1 \leq i < j \leq n $ , and "NO" (without quotes) otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, we can set $ x = 4 $ . This is valid because:

- When $ i=1 $ and $ j=2 $ , $ \gcd(a_i+x,a_j+x)=\gcd(5+4,7+4)=\gcd(9,11)=1 $ .
- When $ i=1 $ and $ j=3 $ , $ \gcd(a_i+x,a_j+x)=\gcd(5+4,10+4)=\gcd(9,14)=1 $ .
- When $ i=2 $ and $ j=3 $ , $ \gcd(a_i+x,a_j+x)=\gcd(7+4,10+4)=\gcd(11,14)=1 $ .

In the second test case, any choice of $ x $ makes $ \gcd(a_1 + x, a_2 + x) = \gcd(3+x,3+x)=3+x $ . Therefore, no such $ x $ exists.

## 样例 #1

### 输入

```
2
3
5 7 10
3
3 3 4
```

### 输出

```
YES
NO
```

