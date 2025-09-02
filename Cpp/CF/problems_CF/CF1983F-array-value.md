---
title: "array-value"
layout: "post"
diff: 提高+/省选-
pid: CF1983F
tag: []
---

# array-value

## 题目描述

You have an array of non-negative integers $ a_1, a_2, \ldots, a_n $ .

The value of a sub-array of length $ \ge 2 $ , $ a[l, r] = [a_l, a_{l+1}, \ldots, a_r] $ is the minimum value of $ a_i \oplus a_j $ such that $ l \le i < j \le r $ , where $ \oplus $ is the xor (exclusive-or) operator.

You have to find the $ k $ -th smallest value over all sub-arrays of length $ \ge 2 $ .

## 输入格式

The first line of the input contains multiple test cases $ t $ ( $ 1 \le t \le 2 \cdot 10^4 $ ).

The first line of each test case contains integer numbers $ n $ and $ k $ ( $ 2 \le n \le 10^5 $ , $ 1 \le k \le \frac{n\cdot(n-1)}{2} $ ).

The second line of the input contains $ n $ non-negative integer numbers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the array itself.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

Print the $ k $ -th smallest value obtained over all subarrays of length at least $ 2 $ .

## 说明/提示

In the first testcase, we have subarrays with their smallest exclusive-or pair as:

 $ [1,2]: 3 $

 $ [2,3]: 1 $

 $ [3,4]: 7 $

 $ [4,5]: 1 $

 $ [1,2,3]: 1 $

 $ [2,3,4]: 1 $

 $ [3,4,5]: 1 $

 $ [1,2,3,4]: 1 $

 $ [2,3,4,5]: 1 $

 $ [1,2,3,4,5]: 1 $

The sorted order would be: $ 1, 1, 1, 1, 1, 1, 1, 1, 3, 7 $ . Therefore, the second smallest element would be $ 1 $ .

## 样例 #1

### 输入

```
4
5 2
1 2 3 4 5
2 1
4 3
4 6
1 2 4 8
5 9
1 2 3 4 5
```

### 输出

```
1
7
12
3
```

