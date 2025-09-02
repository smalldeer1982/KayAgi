---
title: "Superultra's Favorite Permutation"
layout: "post"
diff: 普及-
pid: CF2037C
tag: ['数学', '数论']
---

# Superultra's Favorite Permutation

## 题目描述

Superultra, a little red panda, desperately wants primogems. In his dreams, a voice tells him that he must solve the following task to obtain a lifetime supply of primogems. Help Superultra!

Construct a permutation $ ^{\text{∗}} $ $ p $ of length $ n $ such that $ p_i + p_{i+1} $ is composite $ ^{\text{†}} $ over all $ 1 \leq i \leq n - 1 $ . If it's not possible, output $ -1 $ .

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^{\text{†}} $ An integer $ x $ is composite if it has at least one other divisor besides $ 1 $ and $ x $ . For example, $ 4 $ is composite because $ 2 $ is a divisor.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

Each test case contains an integer $ n $ ( $ 2 \leq n \leq 2 \cdot 10^5 $ ) — the length of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, if it's not possible to construct $ p $ , output $ -1 $ on a new line. Otherwise, output $ n $ integers $ p_1, p_2, \ldots, p_n $ on a new line.

## 说明/提示

In the first example, it can be shown that all permutation of size $ 3 $ contain two adjacent elements whose sum is prime. For example, in the permutation $ [2,3,1] $ the sum $ 2+3=5 $ is prime.

In the second example, we can verify that the sample output is correct because $ 1+8 $ , $ 8+7 $ , $ 7+3 $ , $ 3+6 $ , $ 6+2 $ , $ 2+4 $ , and $ 4+5 $ are all composite. There may be other constructions that are correct.

## 样例 #1

### 输入

```
2
3
8
```

### 输出

```
-1
1 8 7 3 6 2 4 5
```

