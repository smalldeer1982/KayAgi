---
title: "Ultra-Meow"
layout: "post"
diff: 提高+/省选-
pid: CF1992G
tag: ['组合数学']
---

# Ultra-Meow

## 题目描述

K1o0n gave you an array $ a $ of length $ n $ , consisting of numbers $ 1, 2, \ldots, n $ . Accept it? Of course! But what to do with it? Of course, calculate $ \text{MEOW}(a) $ .

Let $ \text{MEX}(S, k) $ be the $ k $ -th positive (strictly greater than zero) integer in ascending order that is not present in the set $ S $ . Denote $ \text{MEOW}(a) $ as the sum of $ \text{MEX}(b, |b| + 1) $ , over all distinct subsets $ b $ of the array $ a $ .

Examples of $ \text{MEX}(S, k) $ values for sets:

- $ \text{MEX}(\{3,2\}, 1) = 1 $ , because $ 1 $ is the first positive integer not present in the set;
- $ \text{MEX}(\{4,2,1\}, 2) = 5 $ , because the first two positive integers not present in the set are $ 3 $ and $ 5 $ ;
- $ \text{MEX}(\{\}, 4) = 4 $ , because there are no numbers in the empty set, so the first $ 4 $ positive integers not present in it are $ 1, 2, 3, 4 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

In a single line of each test case, an integer $ n $ ( $ 1 \le n \le 5000 $ ) is entered, the size of the array of gifted numbers.

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 25 \cdot 10^6 $ .

## 输出格式

For each test case, output a single number — $ \text{MEOW}(a) $ . Since it may be very large, output it modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
5
2
3
4999
5
1
```

### 输出

```
12
31
354226409
184
4
```

