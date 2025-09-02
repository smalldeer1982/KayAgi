---
title: "Don't Blame Me"
layout: "post"
diff: 普及+/提高
pid: CF1829H
tag: []
---

# Don't Blame Me

## 题目描述

Sadly, the problem setter couldn't think of an interesting story, thus he just asks you to solve the following problem.

Given an array $ a $ consisting of $ n $ positive integers, count the number of non-empty subsequences for which the bitwise $ \mathsf{AND} $ of the elements in the subsequence has exactly $ k $ set bits in its binary representation. The answer may be large, so output it modulo $ 10^9+7 $ .

Recall that the subsequence of an array $ a $ is a sequence that can be obtained from $ a $ by removing some (possibly, zero) elements. For example, $ [1, 2, 3] $ , $ [3] $ , $ [1, 3] $ are subsequences of $ [1, 2, 3] $ , but $ [3, 2] $ and $ [4, 5, 6] $ are not.

Note that $ \mathsf{AND} $ represents the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case consists of two integers $ n $ and $ k $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ 0 \le k \le 6 $ ) — the length of the array and the number of set bits that the bitwise $ \mathsf{AND} $ the counted subsequences should have in their binary representation.

The second line of each test case consists of $ n $ integers $ a_i $ ( $ 0 \leq a_i \leq 63 $ ) — the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of subsequences that have exactly $ k $ set bits in their bitwise $ \mathsf{AND} $ value's binary representation. The answer may be large, so output it modulo $ 10^9+7 $ .

## 样例 #1

### 输入

```
6
5 1
1 1 1 1 1
4 0
0 1 2 3
5 1
5 5 7 4 2
1 2
3
12 0
0 2 0 2 0 2 0 2 0 2 0 2
10 6
63 0 63 5 5 63 63 4 12 13
```

### 输出

```
31
10
10
1
4032
15
```

