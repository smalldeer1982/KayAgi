---
title: "Inversion Expectation"
layout: "post"
diff: 提高+/省选-
pid: CF1096F
tag: []
---

# Inversion Expectation

## 题目描述

A permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array. An inversion in a permutation $ p $ is a pair of indices $ (i, j) $ such that $ i > j $ and $ a_i < a_j $ . For example, a permutation $ [4, 1, 3, 2] $ contains $ 4 $ inversions: $ (2, 1) $ , $ (3, 1) $ , $ (4, 1) $ , $ (4, 3) $ .

You are given a permutation $ p $ of size $ n $ . However, the numbers on some positions are replaced by $ -1 $ . Let the valid permutation be such a replacement of $ -1 $ in this sequence back to numbers from $ 1 $ to $ n $ in such a way that the resulting sequence is a permutation of size $ n $ .

The given sequence was turned into a valid permutation randomly with the equal probability of getting each valid permutation.

Calculate the expected total number of inversions in the resulting valid permutation.

It can be shown that it is in the form of $ \frac{P}{Q} $ where $ P $ and $ Q $ are non-negative integers and $ Q \ne 0 $ . Report the value of $ P \cdot Q^{-1} \pmod {998244353} $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the sequence.

The second line contains $ n $ integers $ p_1, p_2, \dots, p_n $ ( $ -1 \le p_i \le n $ , $ p_i \ne 0 $ ) — the initial sequence.

It is guaranteed that all elements not equal to $ -1 $ are pairwise distinct.

## 输出格式

Print a single integer — the expected total number of inversions in the resulting valid permutation.

It can be shown that it is in the form of $ \frac{P}{Q} $ where $ P $ and $ Q $ are non-negative integers and $ Q \ne 0 $ . Report the value of $ P \cdot Q^{-1} \pmod {998244353} $ .

## 说明/提示

In the first example two resulting valid permutations are possible:

- $ [3, 1, 2] $ — $ 2 $ inversions;
- $ [3, 2, 1] $ — $ 3 $ inversions.

The expected value is $ \frac{2 \cdot 1 + 3 \cdot 1}{2} = 2.5 $ .

In the second example no $ -1 $ are present, thus the only valid permutation is possible — the given one. It has $ 0 $ inversions.

In the third example there are two resulting valid permutations — one with $ 0 $ inversions and one with $ 1 $ inversion.

## 样例 #1

### 输入

```
3
3 -1 -1

```

### 输出

```
499122179

```

## 样例 #2

### 输入

```
2
1 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2
-1 -1

```

### 输出

```
499122177

```

