---
title: "White Magic"
layout: "post"
diff: 难度0
pid: CF2066B
tag: []
---

# White Magic

## 题目描述

We call a sequence $ a_1, a_2, \ldots, a_n $ magical if for all $ 1 \leq i \leq n-1 $ it holds that: $ \operatorname{min}(a_1, \ldots, a_i) \geq \operatorname{mex}(a_{i+1}, \ldots, a_n) $ . In particular, any sequence of length $ 1 $ is considered magical.

The minimum excluded (MEX) of a collection of integers $ a_1, a_2, \ldots, a_k $ is defined as the smallest non-negative integer $ t $ which does not occur in the collection $ a $ .

You are given a sequence $ a $ of $ n $ non-negative integers. Find the maximum possible length of a magical subsequence $ ^{\text{∗}} $ of the sequence $ a $ .

 $ ^{\text{∗}} $ A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) element from arbitrary positions.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the sequence $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq 10^9 $ ) — the elements of the sequence $ a $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the maximum possible length of a magical subsequence of the sequence $ a $ .

## 说明/提示

In the first test case, the sequence $ [4, 3, 2, 1, 0] $ is magical, since:

- $ \operatorname{min}(4) = 4, \operatorname{mex}(3, 2, 1, 0) = 4 $ . $ 4 \geq 4 $
- $ \operatorname{min}(4, 3) = 3, \operatorname{mex}(2, 1, 0) = 3 $ . $ 3 \geq 3 $
- $ \operatorname{min}(4, 3, 2) = 2, \operatorname{mex}(1, 0) = 2 $ . $ 2 \geq 2 $
- $ \operatorname{min}(4, 3, 2, 1) = 1, \operatorname{mex}(0) = 1 $ . $ 1 \geq 1 $

In the second test case, the sequence $ [4, 3, 3, 2, 1, 0] $ is not magical, since $ \operatorname{min}(4, 3) = 3, \operatorname{mex}(3, 2, 1, 0) = 4 $ , $ 3 < 4 $ . However, the subsequence $ [4, 3, 2, 1, 0] $ of this sequence is magical, so the answer is $ 5 $ .

## 样例 #1

### 输入

```
8
5
4 3 2 1 0
6
4 3 3 2 1 0
4
2 0 1 2
1
777
4
1000000000 1 7 9
2
0 1
2
1 2
4
0 1 0 1
```

### 输出

```
5
5
3
1
4
2
2
3
```

