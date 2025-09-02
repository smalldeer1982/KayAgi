---
title: "Min Cost Permutation (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF1844F2
tag: []
---

# Min Cost Permutation (Hard Version)

## 题目描述

The only difference between this problem and the easy version is the constraints on $ t $ and $ n $ .

You are given an array of $ n $ positive integers $ a_1,\dots,a_n $ , and a (possibly negative) integer $ c $ .

Across all permutations $ b_1,\dots,b_n $ of the array $ a_1,\dots,a_n $ , consider the minimum possible value of $ $$$\sum_{i=1}^{n-1} |b_{i+1}-b_i-c|. $ $  Find the lexicographically smallest permutation  $ b $  of the array  $ a $  that achieves this minimum.</p><p>A sequence  $ x $  is lexicographically smaller than a sequence  $ y $  if and only if one of the following holds:</p><ul><li>  $ x $  is a prefix of  $ y $ , but  $ x \\ne y $ ;</li><li> in the first position where  $ x $  and  $ y $  differ, the sequence  $ x $  has a smaller element than the corresponding element in  $ y$$$.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ c $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ -10^9 \le c \le 10^9 $ ).

The second line of each test case contains $ n $ integers $ a_1,\dots,a_n $ ( $ 1 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers $ b_1,\dots,b_n $ , the lexicographically smallest permutation of $ a $ that achieves the minimum $ \sum\limits_{i=1}^{n-1} |b_{i+1}-b_i-c| $ .

## 说明/提示

In the first test case, it can be proven that the minimum possible value of $ \sum\limits_{i=1}^{n-1} |b_{i+1}-b_i-c| $ is $ 27 $ , and the permutation $ b = [9,3,1,4,5,1] $ is the lexicographically smallest permutation of $ a $ that achieves this minimum: $ |3-9-(-7)|+|1-3-(-7)|+|4-1-(-7)|+|5-4-(-7)|+|1-5-(-7)| = 1+5+10+8+3 = 27 $ .

In the second test case, the minimum possible value of $ \sum\limits_{i=1}^{n-1} |b_{i+1}-b_i-c| $ is $ 0 $ , and $ b = [1,3,5] $ is the lexicographically smallest permutation of $ a $ that achieves this.

In the third test case, there is only one permutation $ b $ .

## 样例 #1

### 输入

```
3
6 -7
3 1 4 1 5 9
3 2
1 3 5
1 2718
2818
```

### 输出

```
9 3 1 4 5 1
1 3 5
2818
```

