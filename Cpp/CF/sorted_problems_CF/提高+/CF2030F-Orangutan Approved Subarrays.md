---
title: "Orangutan Approved Subarrays"
layout: "post"
diff: 提高+/省选-
pid: CF2030F
tag: ['线段树']
---

# Orangutan Approved Subarrays

## 题目描述

Suppose you have an array $ b $ . Initially, you also have a set $ S $ that contains all distinct elements of $ b $ . The array $ b $ is called orangutan-approved if it can be emptied by repeatedly performing the following operation:

- In one operation, select indices $ l $ and $ r $ ( $ 1 \leq l \leq r \leq |b| $ ) such that $ v = b_l = b_{l+1} = \ldots = b_r $ and $ v $ is present in $ S $ . Remove $ v $ from $ S $ , and simultaneously remove all $ b_i $ such that $ l \leq i \leq r $ . Then, reindex the elements $ b_{r+1}, b_{r+2}, \ldots $ as $ b_l, b_{l+1}, \ldots $ accordingly.

You are given an array $ a $ of length $ n $ and $ q $ queries.

Each query consists of two indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ), and you need to determine whether or not the subarray $ a_{l}, a_{l+1}, \ldots, a_r $ is orangutan-approved.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains integers $ n $ and $ q $ ( $ 1 \leq n,q \leq 2 \cdot 10^5 $ ) — the size of $ a $ and the number of queries, respectively.

The following line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of the array $ a $ .

The following $ q $ lines contain two integers $ l $ and $ r $ — the endpoints of the subarray for each query ( $ 1 \leq l \leq r \leq n $ ).

It is guaranteed that the sum of $ n $ and $ q $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output "YES" (without quotes) if the subarray from $ l $ to $ r $ is orangutan-approved, and "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yES", "yes" and "Yes" will be recognized as a positive response).

## 说明/提示

In the first query of the first testcase, the answer is YES.

- Initially, $ S=\{1,2\} $ and $ b=[1,2,2,1] $
- Select $ l=2 $ and $ r=3 $ . Since $ b_2=b_3=2 $ is in $ S $ , we may erase $ b_2 $ and $ b_3 $ from the array, as well as erasing $ 2 $ from $ S $ . The set $ S $ becomes $ \{1\} $ and the array becomes $ [1,1] $ .
- Select $ l=1 $ and $ r=2 $ . Since $ b_1=b_2=1 $ is in $ S $ , we may erase $ b_1 $ and $ b_2 $ from the array, as well as erasing $ 1 $ from $ S $ . The set $ S $ becomes $ \{\} $ and the array becomes $ [] $ .
- Since the array is now empty, we can say the original array is orangutan-approved.

In the first query of the second testcase, the answer is NO, because it can be shown that the subarray $ [2,1,2,1] $ cannot become empty through any sequence of valid operations.

## 样例 #1

### 输入

```
3
4 2
1 2 2 1
1 4
1 3
5 3
1 2 1 2 1
2 5
3 5
1 3
8 4
1 2 3 2 1 3 2 3
1 5
2 8
3 5
6 8
```

### 输出

```
YES
YES
NO
YES
YES
YES
NO
YES
YES
```

