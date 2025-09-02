---
title: "Yet Yet Another Permutation Problem"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1936E
tag: []
---

# Yet Yet Another Permutation Problem

## 题目描述

You are given a permutation $ p $ of length $ n $ .

Please count the number of permutations $ q $ of length $ n $ which satisfy the following:

- for each $ 1 \le i < n $ , $ \max(q_1,\ldots,q_i) \neq \max(p_1,\ldots,p_i) $ .

Since the answer may be large, output the answer modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line of each test case contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ). It is guaranteed that $ p $ is a permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, $ p = [2, 1] $ . The only suitable $ q $ is $ [1, 2] $ . Indeed, we need to satisfy the inequality $ q_1 \neq p_1 $ . It only holds for $ q = [1, 2] $ .

In the second test case, $ p = [1, 2, 3] $ . So $ q $ has to satisfy two inequalities: $ q_1 \neq p_1 $ and $ \max(q_1, q_2) \neq \max(1, 2) = 2 $ . One can prove that this only holds for the following $ 3 $ permutations:

- $ q = [2, 3, 1] $ : in this case $ q_1 = 2 \neq 1 $ and $ \max(q_1, q_2) = 3 \neq 2 $ ;
- $ q = [3, 1, 2] $ : in this case $ q_1 = 3 \neq 1 $ and $ \max(q_1, q_2) = 3 \neq 2 $ ;
- $ q = [3, 2, 1] $ : in this case $ q_1 = 3 \neq 1 $ and $ \max(q_1, q_2) = 3 \neq 2 $ .

## 样例 #1

### 输入

```
6
2
2 1
3
1 2 3
3
3 1 2
4
2 4 1 3
5
3 5 1 4 2
15
6 13 2 8 7 11 1 3 9 15 4 5 12 10 14
```

### 输出

```
1
3
2
4
18
424488915
```

