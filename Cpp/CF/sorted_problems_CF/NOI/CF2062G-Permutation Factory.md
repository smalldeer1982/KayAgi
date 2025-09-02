---
title: "Permutation Factory"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2062G
tag: []
---

# Permutation Factory

## 题目描述

You are given two permutations $ p_1,p_2,\ldots,p_n $ and $ q_1,q_2,\ldots,q_n $ of length $ n $ . In one operation, you can select two integers $ 1\leq i,j\leq n,i\neq j $ and swap $ p_i $ and $ p_j $ . The cost of the operation is $ \min (|i-j|,|p_i-p_j|) $ .

Find the minimum cost to make $ p_i = q_i $ hold for all $ 1\leq i\leq n $ and output a sequence of operations to achieve the minimum cost.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of input test cases.

The first line of each test case contains one integer $ n $ ( $ 2 \le n \le 100 $ ) — the length of permutations $ p $ and $ q $ .

The second line contains $ n $ integers $ p_1,p_2,\ldots,p_n $ ( $ 1\leq p_i\leq n $ ) — the permutation $ p $ . It is guaranteed that $ p_1,p_2,\ldots,p_n $ is a permutation of $ 1,2,\ldots,n $ .

The third line contains $ n $ integers $ q_1,q_2,\ldots,q_n $ ( $ 1\leq q_i\leq n $ ) — the permutation $ q $ . It is guaranteed that $ q_1,q_2,\ldots,q_n $ is a permutation of $ 1,2,\ldots,n $ .

It is guaranteed that the sum of $ n^3 $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output the total number of operations $ k $ ( $ 0\le k\le n^2 $ ) on the first line. Then output $ k $ lines, each containing two integers $ i,j $ ( $ 1\le i,j\le n $ , $ i\neq j $ ) representing an operation to swap $ p_i $ and $ p_j $ in order.

It can be shown that no optimal operation sequence has a length greater than $ n^2 $ .

## 说明/提示

In the second test case, you can swap $ p_1,p_3 $ costing $ \min(|1-3|,|1-3|)=2 $ . Then $ p $ equals $ q $ with a cost of $ 2 $ .

In the third test case, you can perform the following operations:

Initially, $ p=[2,1,4,3] $ .

1. Swap $ p_1,p_4 $ costing $ \min(|1-4|,|2-3|)=1 $ , resulting in $ p=[3,1,4,2] $ .
2. Swap $ p_2,p_4 $ costing $ \min(|2-4|,|1-2|)=1 $ , resulting in $ p=[3,2,4,1] $ .
3. Swap $ p_1,p_3 $ costing $ \min(|1-3|,|3-4|)=1 $ . Then $ p $ equals $ q $ with a cost of $ 3 $ .

## 样例 #1

### 输入

```
4
2
2 1
2 1
3
1 2 3
3 2 1
4
2 1 4 3
4 2 3 1
5
1 4 3 2 5
5 2 3 4 1
```

### 输出

```
0
1
1 3
3
1 4
2 4
1 3
4
1 2
4 5
2 5
1 4
```

