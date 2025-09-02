---
title: "Almost Perfect"
layout: "post"
diff: 省选/NOI-
pid: CF1726E
tag: []
---

# Almost Perfect

## 题目描述

A permutation $ p $ of length $ n $ is called almost perfect if for all integer $ 1 \leq i \leq n $ , it holds that $ \lvert p_i - p^{-1}_i \rvert \le 1 $ , where $ p^{-1} $ is the inverse permutation of $ p $ (i.e. $ p^{-1}_{k_1} = k_2 $ if and only if $ p_{k_2} = k_1 $ ).

Count the number of almost perfect permutations of length $ n $ modulo $ 998244353 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. The description of each test case follows.

The first and only line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 3 \cdot 10^5 $ ) — the length of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of almost perfect permutations of length $ n $ modulo $ 998244353 $ .

## 说明/提示

For $ n = 2 $ , both permutations $ [1, 2] $ , and $ [2, 1] $ are almost perfect.

For $ n = 3 $ , there are only $ 6 $ permutations. Having a look at all of them gives us:

- $ [1, 2, 3] $ is an almost perfect permutation.
- $ [1, 3, 2] $ is an almost perfect permutation.
- $ [2, 1, 3] $ is an almost perfect permutation.
- $ [2, 3, 1] $ is NOT an almost perfect permutation ( $ \lvert p_2 - p^{-1}_2 \rvert = \lvert 3 - 1 \rvert = 2 $ ).
- $ [3, 1, 2] $ is NOT an almost perfect permutation ( $ \lvert p_2 - p^{-1}_2 \rvert = \lvert 1 - 3 \rvert = 2 $ ).
- $ [3, 2, 1] $ is an almost perfect permutation.

So we get $ 4 $ almost perfect permutations.

## 样例 #1

### 输入

```
3
2
3
50
```

### 输出

```
2
4
830690567
```

