---
title: "Expected Median"
layout: "post"
diff: 普及+/提高
pid: CF1999F
tag: ['组合数学', '排列组合']
---

# Expected Median

## 题目描述

Arul has a binary array $ ^{\text{∗}} $ $ a $ of length $ n $ .

He will take all subsequences $ ^{\text{†}} $ of length $ k $ ( $ k $ is odd) of this array and find their median. $ ^{\text{‡}} $

What is the sum of all these values?

As this sum can be very large, output it modulo $ 10^9 + 7 $ . In other words, print the remainder of this sum when divided by $ 10^9 + 7 $ .

 $ ^{\text{∗}} $ A binary array is an array consisting only of zeros and ones.

 $ ^{\text{†}} $ An array $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements. Subsequences don't have to be contiguous.

 $ ^{\text{‡}} $ The median of an array of odd length $ k $ is the $ \frac{k+1}{2} $ -th element when sorted.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \leq k \leq n \leq 2 \cdot 10^5 $ ,  $ k $ is odd) — the length of the array and the length of the subsequence, respectively.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 0 \leq a_i \leq 1 $ ) — the elements of the array.

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print the sum modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, there are four subsequences of $ [1,0,0,1] $ with length $ k=3 $ :

- $ [1,0,0] $ : median $ = 0 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [0,0,1] $ : median $ = 0 $ .

 The sum of the results is $ 0+1+1+0=2 $ .In the second test case, all subsequences of length $ 1 $ have median $ 1 $ , so the answer is $ 5 $ .

## 样例 #1

### 输入

```
8
4 3
1 0 0 1
5 1
1 1 1 1 1
5 5
0 1 0 1 0
6 3
1 0 1 0 1 1
4 3
1 0 1 1
5 3
1 0 1 1 0
2 1
0 0
34 17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

### 输出

```
2
5
0
16
4
7
0
333606206
```

