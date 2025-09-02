---
title: "Ela and Prime GCD"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1737F
tag: []
---

# Ela and Prime GCD

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737F/d4d68449517a75bb21a32e949b46f5b762acfe62.png)After a long, tough, but fruitful day at DTL, Ela goes home happily. She entertains herself by solving Competitive Programming problems. She prefers short statements, because she already read too many long papers and documentation at work. The problem of the day reads:You are given an integer $ c $ . Suppose that $ c $ has $ n $ divisors. You have to find a sequence with $ n - 1 $ integers $ [a_1, a_2, ... a_{n - 1}] $ , which satisfies the following conditions:

- Each element is strictly greater than $ 1 $ .
- Each element is a divisor of $ c $ .
- All elements are distinct.
- For all $ 1 \le i < n - 1 $ , $ \gcd(a_i, a_{i + 1}) $ is a prime number.

In this problem, because $ c $ can be too big, the result of prime factorization of $ c $ is given instead. Note that $ \gcd(x, y) $ denotes the greatest common divisor (GCD) of integers $ x $ and $ y $ and a prime number is a positive integer which has exactly $ 2 $ divisors.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) - the number of test cases.

The first line of each test case contains one integer $ m $ ( $ 1 \le m \le 16 $ ) - the number of prime factor of $ c $ .

The second line of each test case contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i < 2^{20} $ ) — exponents of corresponding prime factors of $ c $ , so that $ c = p_1^{b_1} \cdot p_2^{b_2} \cdot \ldots \cdot p_m^{b_m} $ and $ n = (b_1 + 1)(b_2 + 1) \ldots (b_m + 1) $ hold. $ p_i $ is the $ i $ -th smallest prime number.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 2^{20} $ .

## 输出格式

Print the answer for each test case, one per line. If there is no sequence for the given $ c $ , print $ -1 $ .

Otherwise, print $ n - 1 $ lines. In $ i $ -th line, print $ m $ space-separated integers. The $ j $ -th integer of $ i $ -th line is equal to the exponent of $ j $ -th prime number from $ a_i $ .

If there are multiple answers, print any of them.

## 说明/提示

In each test case, the values of $ c $ are $ 6 $ , $ 2 $ , $ 30 $ , $ 16 $ , and $ 12 $ in that order.

In the first test case, $ 1 $ , $ 2 $ , $ 3 $ , $ 6 $ are divisors of $ 6 $ . Here, sequences $ [2, 6, 3] $ and $ [3, 6, 2] $ can be answer. Permutation $ [3, 2, 6] $ is invalid because $ \gcd(a_1, a_2) = 1 $ is not a prime number.

In the forth test case, $ 1 $ , $ 2 $ , $ 4 $ , $ 8 $ , $ 16 $ are divisors of $ 16 $ . Among the permutation of sequence $ [2, 4, 8, 16] $ , no valid answer exist.

## 样例 #1

### 输入

```
5
2
1 1
1
1
3
1 1 1
1
4
2
2 1
```

### 输出

```
0 1 
1 1 
1 0 
1 
0 1 1 
0 0 1 
1 0 1 
1 1 0 
0 1 0 
1 1 1 
1 0 0 
-1
2 0 
1 1 
0 1 
2 1 
1 0
```

