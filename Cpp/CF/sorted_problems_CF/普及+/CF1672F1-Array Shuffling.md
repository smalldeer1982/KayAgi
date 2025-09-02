---
title: "Array Shuffling"
layout: "post"
diff: 普及+/提高
pid: CF1672F1
tag: []
---

# Array Shuffling

## 题目描述

oolimry has an array $ a $ of length $ n $ which he really likes. Today, you have changed his array to $ b $ , a permutation of $ a $ , to make him sad.

Because oolimry is only a duck, he can only perform the following operation to restore his array:

- Choose two integers $ i,j $ such that $ 1 \leq i,j \leq n $ .
- Swap $ b_i $ and $ b_j $ .

The sadness of the array $ b $ is the minimum number of operations needed to transform $ b $ into $ a $ .

Given the array $ a $ , find any array $ b $ which is a permutation of $ a $ that has the maximum sadness over all permutations of the array $ a $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ) — elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print $ n $ integers $ b_1, b_2, \ldots, b_n $ — describing the array $ b $ . If there are multiple answers, you may print any.

## 说明/提示

In the first test case, the array $ [1,2] $ has sadness $ 1 $ . We can transform $ [1,2] $ into $ [2,1] $ using one operation with $ (i,j)=(1,2) $ .

In the second test case, the array $ [3,3,2,1] $ has sadness $ 2 $ . We can transform $ [3,3,2,1] $ into $ [1,2,3,3] $ with two operations with $ (i,j)=(1,4) $ and $ (i,j)=(2,3) $ respectively.

## 样例 #1

### 输入

```
2
2
2 1
4
1 2 3 3
```

### 输出

```
1 2
3 3 2 1
```

