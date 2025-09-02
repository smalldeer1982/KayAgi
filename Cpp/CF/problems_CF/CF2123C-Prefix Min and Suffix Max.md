---
title: "Prefix Min and Suffix Max"
layout: "post"
diff: 难度0
pid: CF2123C
tag: []
---

# Prefix Min and Suffix Max

## 题目描述

You are given an array $ a $ of distinct integers.

In one operation, you may either:

- choose a nonempty prefix $ ^{\text{∗}} $ of $ a $ and replace it with its minimum value, or
- choose a nonempty suffix $ ^{\text{†}} $ of $ a $ and replace it with its maximum value.

Note that you may choose the entire array $ a $ .

For each element $ a_i $ , determine if there exists some sequence of operations to transform $ a $ into $ [a_i] $ ; that is, make the array $ a $ consist of only one element, which is $ a_i $ . Output your answer as a binary string of length $ n $ , where the $ i $ -th character is $ 1 $ if there exists a sequence to transform $ a $ into $ [a_i] $ , and $ 0 $ otherwise.

 $ ^{\text{∗}} $ A prefix of an array is a subarray consisting of the first $ k $ elements of the array, for some integer $ k $ .

 $ ^{\text{†}} $ A suffix of an array is a subarray consisting of the last $ k $ elements of the array, for some integer $ k $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 2 \leq n \leq 2\cdot 10^5 $ ) — the size of the array $ a $ .

The second line of each test case contains $ n $ integers, $ a_1,a_2,\dots,a_n $ ( $ 1 \leq a_i \leq 10^6 $ ). It is guaranteed that all $ a_i $ are distinct.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a binary string of length $ n $ — the $ i $ -th character should be $ 1 $ if there exists a sequence of operations as described above, and $ 0 $ otherwise.

## 说明/提示

In the first sample, you can first choose the prefix of size $ 3 $ . Then the array is transformed into

1472 Next, you can choose the suffix of size $ 2 $ . Then the array is transformed into 147 Finally, you can choose the prefix of size $ 3 $ . Then the array is transformed into 1 So we see that it is possible to transform $ a $ into $ [1] $ .It can be shown that it is impossible to transform $ a $ into $ [3] $ .

## 样例 #1

### 输入

```
3
6
1 3 5 4 7 2
4
13 10 12 20
7
1 2 3 4 5 6 7
```

### 输出

```
100011
1101
1000001
```

