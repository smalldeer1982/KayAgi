---
title: "MEXimize the Score"
layout: "post"
diff: 提高+/省选-
pid: CF2030E
tag: ['动态规划 DP', '组合数学', '排列组合']
---

# MEXimize the Score

## 题目描述

Suppose we partition the elements of an array $ b $ into any number $ k $ of non-empty multisets $ S_1, S_2, \ldots, S_k $ , where $ k $ is an arbitrary positive integer. Define the score of $ b $ as the maximum value of $ \operatorname{MEX}(S_1) $ $ ^{\text{∗}} $ $  + \operatorname{MEX}(S_2) + \ldots + \operatorname{MEX}(S_k) $ over all possible partitions of $ b $ for any integer $ k $ .

Envy is given an array $ a $ of size $ n $ . Since he knows that calculating the score of $ a $ is too easy for you, he instead asks you to calculate the sum of scores of all $ 2^n - 1 $ non-empty subsequences of $ a $ . $ ^{\text{†}} $ Since this answer may be large, please output it modulo $ 998\,244\,353 $ .

 $ ^{\text{∗}} $ $ \operatorname{MEX} $ of a collection of integers $ c_1, c_2, \ldots, c_k $ is defined as the smallest non-negative integer $ x $ that does not occur in the collection $ c $ . For example, $ \operatorname{MEX}([0,1,2,2]) = 3 $ and $ \operatorname{MEX}([1,2,2]) = 0 $

 $ ^{\text{†}} $ A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deleting several (possibly, zero or all) elements.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i < n $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the answer, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, we must consider seven subsequences:

- $ [0] $ : The score is $ 1 $ .
- $ [0] $ : The score is $ 1 $ .
- $ [1] $ : The score is $ 0 $ .
- $ [0,0] $ : The score is $ 2 $ .
- $ [0,1] $ : The score is $ 2 $ .
- $ [0,1] $ : The score is $ 2 $ .
- $ [0,0,1] $ : The score is $ 3 $ .

 The answer for the first testcase is $ 1+1+2+2+2+3=11 $ .In the last testcase, all subsequences have a score of $ 0 $ .

## 样例 #1

### 输入

```
4
3
0 0 1
4
0 0 1 1
5
0 0 1 2 2
4
1 1 1 1
```

### 输出

```
11
26
53
0
```

