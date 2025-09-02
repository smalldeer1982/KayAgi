---
title: "Minimize Inversions Number"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1637H
tag: ['树状数组']
---

# Minimize Inversions Number

## 题目描述

You are given a permutation $ p $ of length $ n $ .

You can choose any subsequence, remove it from the permutation, and insert it at the beginning of the permutation keeping the same order.

For every $ k $ from $ 0 $ to $ n $ , find the minimal possible number of inversions in the permutation after you choose a subsequence of length exactly $ k $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 50\,000 $ ) — the number of test cases.

The first line of each test case contains one integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ) — the length of the permutation.

The second line of each test case contains the permutation $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ).

It is guaranteed that the total sum of $ n $ doesn't exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case output $ n + 1 $ integers. The $ i $ -th of them must be the answer for the subsequence length of $ i - 1 $ .

## 说明/提示

In the second test case:

- For the length $ 0 $ : $ [4, 2, 1, 3] \rightarrow [4, 2, 1, 3] $ : $ 4 $ inversions.
- For the length $ 1 $ : $ [4, 2, \mathbf{1}, 3] \rightarrow [1, 4, 2, 3] $ : $ 2 $ inversions.
- For the length $ 2 $ : $ [4, \mathbf{2}, \mathbf{1}, 3] \rightarrow [2, 1, 4, 3] $ , or $ [4, 2, \mathbf{1}, \textbf{3}] \rightarrow [1, 3, 4, 2] $ : $ 2 $ inversions.
- For the length $ 3 $ : $ [4, \mathbf{2}, \mathbf{1}, \mathbf{3}] \rightarrow [2, 1, 3, 4] $ : $ 1 $ inversion.
- For the length $ 4 $ : $ [\mathbf{4}, \mathbf{2}, \mathbf{1}, \mathbf{3}] \rightarrow [4, 2, 1, 3] $ : $ 4 $ inversions.

## 样例 #1

### 输入

```
3
1
1
4
4 2 1 3
5
5 1 3 2 4
```

### 输出

```
0 0
4 2 2 1 4
5 4 2 2 1 5
```

