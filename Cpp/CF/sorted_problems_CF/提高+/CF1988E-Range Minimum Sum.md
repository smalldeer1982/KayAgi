---
title: "Range Minimum Sum"
layout: "post"
diff: 提高+/省选-
pid: CF1988E
tag: []
---

# Range Minimum Sum

## 题目描述

For an array $ [a_1,a_2,\ldots,a_n] $ of length $ n $ , define $ f(a) $ as the sum of the minimum element over all subsegments. That is, $ $$$f(a)=\sum_{l=1}^n\sum_{r=l}^n \min_{l\le i\le r}a_i. $ $ </p><p>A permutation is a sequence of integers from  $ 1 $  to  $ n $  of length  $ n $  containing each number exactly once. You are given a permutation  $ \[a\_1,a\_2,\\ldots,a\_n\] $ . For each  $ i $ , solve the following problem independently:</p><ul> <li> Erase  $ a\_i $  from  $ a $ , concatenating the remaining parts, resulting in  $ b = \[a\_1,a\_2,\\ldots,a\_{i-1},\\;a\_{i+1},\\ldots,a\_{n}\] $ . </li><li> Calculate  $ f(b)$$$.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1\le n\le 5\cdot 10^5 $ ).

The second line of each test case contains $ n $ distinct integers $ a_1,\ldots,a_n $ ( $ 1\le a_i\le n $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print one line containing $ n $ integers. The $ i $ -th integer should be the answer when erasing $ a_i $ .

## 说明/提示

In the second test case, $ a=[3,1,2] $ .

- When removing $ a_1 $ , $ b=[1,2] $ . $ f(b)=1+2+\min\{1,2\}=4 $ .
- When removing $ a_2 $ , $ b=[3,2] $ . $ f(b)=3+2+\min\{3,2\}=7 $ .
- When removing $ a_3 $ , $ b=[3,1] $ . $ f(b)=3+1+\min\{3,1\}=5 $ .

## 样例 #1

### 输入

```
4
1
1
3
3 1 2
5
4 2 1 5 3
8
8 1 4 6 7 3 5 2
```

### 输出

```
0 
4 7 5 
19 21 27 17 19 
79 100 72 68 67 80 73 80
```

