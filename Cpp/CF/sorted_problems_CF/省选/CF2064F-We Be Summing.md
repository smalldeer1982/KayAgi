---
title: "We Be Summing"
layout: "post"
diff: 省选/NOI-
pid: CF2064F
tag: []
---

# We Be Summing

## 题目描述

You are given an array $ a $ of length $ n $ and an integer $ k $ .

Call a non-empty array $ b $ of length $ m $ epic if there exists an integer $ i $ where $ 1 \le i < m $ and $ \min(b_1,\ldots,b_i) + \max(b_{i + 1},\ldots,b_m) = k $ .

Count the number of epic subarrays $ ^{\text{∗}} $ of $ a $ .

 $ ^{\text{∗}} $ An array $ a $ is a subarray of an array $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains integers $ n $ and $ k $ ( $ 2 \le n \le 2 \cdot 10^5 $ ; $ n < k < 2 \cdot n $ ) — the length of the array $ a $ and $ k $ .

The second line of each testcase contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ).

The sum of $ n $ across all testcases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, output the number of epic contiguous subarrays of $ a $ .

## 说明/提示

These are all the epic subarrays in the first testcase:

- $ [2, 3, 4, 5] $ , because $ \min(2, 3) + \max(4, 5) = 2 + 5 = 7 $ .
- $ [3, 4] $ , because $ \min(3) + \max(4) = 3 + 4 = 7 $ .

In the second test case, every subarray that contains at least one $ 6 $ and at least one $ 7 $ is epic.

## 样例 #1

### 输入

```
6
5 7
1 2 3 4 5
7 13
6 6 6 6 7 7 7
6 9
4 5 6 6 5 1
5 9
5 5 4 5 5
5 6
3 3 3 3 3
6 8
4 5 4 5 4 5
```

### 输出

```
2
12
3
8
10
4
```

