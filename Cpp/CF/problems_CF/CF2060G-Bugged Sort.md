---
title: "Bugged Sort"
layout: "post"
diff: 难度0
pid: CF2060G
tag: []
---

# Bugged Sort

## 题目描述

Today, Alice has given Bob arrays for him to sort in increasing order again! At this point, no one really knows how many times she has done this.

Bob is given two sequences $ a $ and $ b $ , both of length $ n $ . All integers in the range from $ 1 $ to $ 2n $ appear exactly once in either $ a $ or $ b $ . In other words, the concatenated $ ^{\text{∗}} $ sequence $ a+b $ is a permutation $ ^{\text{†}} $ of length $ 2n $ .

Bob must sort both sequences in increasing order at the same time using Alice's swap function. Alice's swap function is implemented as follows:

- Given two indices $ i $ and $ j $ ( $ i \neq j $ ), it swaps $ a_i $ with $ b_j $ , and swaps $ b_i $ with $ a_j $ .

Given sequences $ a $ and $ b $ , please determine if both sequences can be sorted in increasing order simultaneously after using Alice's swap function any number of times.

 $ ^{\text{∗}} $ The concatenated sequence $ a+b $ denotes the sequence $ [a_1, a_2, a_3, \ldots , b_1, b_2, b_3, \ldots] $ .

 $ ^{\text{†}} $ A permutation of length $ m $ contains all integers from $ 1 $ to $ m $ in some order.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \le n \le 2 \cdot 10^5 $ ).

The second line of each test case contains $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le 2n $ ).

The third line of each test case contains $ b_1,b_2,\ldots,b_n $ ( $ 1 \le b_i \le 2n $ ).

It is guaranteed that all integers in the range $ [1,2n] $ appear exactly once in either $ a $ or $ b $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

If it is possible to sort both sequences simultaneously, print "YES" on a new line. Otherwise, print "NO" on a new line.

You can output the answer in any case. For example, the strings "yEs", "yes", and "Yes" will also be recognized as positive responses.

## 说明/提示

In the first test case, it can be shown that it is impossible.

In the second test case, Bob can perform one operation with indices $ i=1 $ and $ j=2 $ . The arrays become $ [3,4,5] $ and $ [1,2,6] $ respectively. Both arrays are now sorted.

## 样例 #1

### 输入

```
5
3
2 1 3
4 6 5
3
2 1 5
4 3 6
4
1 6 4 3
5 2 8 7
4
5 3 7 1
8 6 4 2
7
5 1 9 12 3 13 7
2 4 11 14 6 10 8
```

### 输出

```
NO
YES
NO
YES
YES
```

