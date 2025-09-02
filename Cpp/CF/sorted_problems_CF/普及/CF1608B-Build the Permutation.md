---
title: "Build the Permutation"
layout: "post"
diff: 普及/提高-
pid: CF1608B
tag: []
---

# Build the Permutation

## 题目描述

You are given three integers $ n, a, b $ . Determine if there exists a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ , such that:

- There are exactly $ a $ integers $ i $ with $ 2 \le i \le n-1 $ such that $ p_{i-1} < p_i > p_{i+1} $ (in other words, there are exactly $ a $ local maximums).
- There are exactly $ b $ integers $ i $ with $ 2 \le i \le n-1 $ such that $ p_{i-1} > p_i < p_{i+1} $ (in other words, there are exactly $ b $ local minimums).

If such permutations exist, find any such permutation.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of test cases follows.

The only line of each test case contains three integers $ n $ , $ a $ and $ b $ ( $ 2 \leq n \leq 10^5 $ , $ 0 \leq a,b \leq n $ ).

The sum of $ n $ over all test cases doesn't exceed $ 10^5 $ .

## 输出格式

For each test case, if there is no permutation with the requested properties, output $ -1 $ .

Otherwise, print the permutation that you are found. If there are several such permutations, you may print any of them.

## 说明/提示

In the first test case, one example of such permutations is $ [1, 3, 2, 4] $ . In it $ p_1 < p_2 > p_3 $ , and $ 2 $ is the only such index, and $ p_2> p_3 < p_4 $ , and $ 3 $ the only such index.

One can show that there is no such permutation for the third test case.

## 样例 #1

### 输入

```
3
4 1 1
6 1 2
6 4 0
```

### 输出

```
1 3 2 4
4 2 3 1 5 6
-1
```

