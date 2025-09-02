---
title: "LIS or Reverse LIS?"
layout: "post"
diff: 普及+/提高
pid: CF1682C
tag: ['数学', '构造']
---

# LIS or Reverse LIS?

## 题目描述

You are given an array $ a $ of $ n $ positive integers.

Let $ \text{LIS}(a) $ denote the length of [longest strictly increasing subsequence](https://en.wikipedia.org/wiki/Longest_increasing_subsequence) of $ a $ . For example,

- $ \text{LIS}([2, \underline{1}, 1, \underline{3}]) $ = $ 2 $ .
- $ \text{LIS}([\underline{3}, \underline{5}, \underline{10}, \underline{20}]) $ = $ 4 $ .
- $ \text{LIS}([3, \underline{1}, \underline{2}, \underline{4}]) $ = $ 3 $ .

We define array $ a' $ as the array obtained after reversing the array $ a $ i.e. $ a' = [a_n, a_{n-1}, \ldots , a_1] $ .

The beauty of array $ a $ is defined as $ min(\text{LIS}(a),\text{LIS}(a')) $ .

Your task is to determine the maximum possible beauty of the array $ a $ if you can rearrange the array $ a $ arbitrarily.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ $ (1 \leq t \leq 10^4) $ — the number of test cases. Description of the test cases follows.

The first line of each test case contains a single integer $ n $ $ (1 \leq n \leq 2\cdot 10^5) $ — the length of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1,a_2, \ldots ,a_n $ $ (1 \leq a_i \leq 10^9) $ — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible beauty of $ a $ after rearranging its elements arbitrarily.

## 说明/提示

In the first test case, $ a $ = $ [6, 6, 6] $ and $ a' $ = $ [6, 6, 6] $ . $ \text{LIS}(a) = \text{LIS}(a') $ = $ 1 $ . Hence the beauty is $ min(1, 1) = 1 $ .

In the second test case, $ a $ can be rearranged to $ [2, 5, 4, 5, 4, 2] $ . Then $ a' $ = $ [2, 4, 5, 4, 5, 2] $ . $ \text{LIS}(a) = \text{LIS}(a') = 3 $ . Hence the beauty is $ 3 $ and it can be shown that this is the maximum possible beauty.

In the third test case, $ a $ can be rearranged to $ [1, 2, 3, 2] $ . Then $ a' $ = $ [2, 3, 2, 1] $ . $ \text{LIS}(a) = 3 $ , $ \text{LIS}(a') = 2 $ . Hence the beauty is $ min(3, 2) = 2 $ and it can be shown that $ 2 $ is the maximum possible beauty.

## 样例 #1

### 输入

```
3
3
6 6 6
6
2 5 4 5 2 4
4
1 3 2 2
```

### 输出

```
1
3
2
```

