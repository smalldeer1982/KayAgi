---
title: "Replace With Product"
layout: "post"
diff: 提高+/省选-
pid: CF1872G
tag: []
---

# Replace With Product

## 题目描述

Given an array $ a $ of $ n $ positive integers. You need to perform the following operation exactly once:

- Choose $ 2 $ integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) and replace the subarray $ a[l \ldots r] $ with the single element: the product of all elements in the subarray $ (a_l \cdot \ldots \cdot a_r) $ .

For example, if an operation with parameters $ l = 2, r = 4 $ is applied to the array $ [5, 4, 3, 2, 1] $ , the array will turn into $ [5, 24, 1] $ .

Your task is to maximize the sum of the array after applying this operation. Find the optimal subarray to apply this operation.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. This is followed by the description of the test cases.

The first line of each test case contains a single number $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of the values of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ 2 $ integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ) — the boundaries of the subarray to be replaced with the product.

If there are multiple solutions, output any of them.

## 说明/提示

In the first test case, after applying the operation with parameters $ l = 2, r = 4 $ , the array $ [1, 3, 1, 3] $ turns into $ [1, 9] $ , with a sum equal to $ 10 $ . It is easy to see that by replacing any other segment with a product, the sum will be less than $ 10 $ .

In the second test case, after applying the operation with parameters $ l = 3, r = 4 $ , the array $ [1, 1, 2, 3] $ turns into $ [1, 1, 6] $ , with a sum equal to $ 8 $ . It is easy to see that by replacing any other segment with a product, the sum will be less than $ 8 $ .

In the third test case, it will be optimal to choose any operation with $ l = r $ , then the sum of the array will remain $ 5 $ , and when applying any other operation, the sum of the array will decrease.

## 样例 #1

### 输入

```
9
4
1 3 1 3
4
1 1 2 3
5
1 1 1 1 1
5
10 1 10 1 10
1
1
2
2 2
3
2 1 2
4
2 1 1 3
6
2 1 2 1 1 3
```

### 输出

```
2 4
3 4
1 1
1 5
1 1
1 2
2 2
4 4
1 6
```

