---
title: "Premutation"
layout: "post"
diff: 普及-
pid: CF1790C
tag: []
---

# Premutation

## 题目描述

A sequence of $ n $ numbers is called permutation if it contains all integers from $ 1 $ to $ n $ exactly once. For example, the sequences \[ $ 3, 1, 4, 2 $ \], \[ $ 1 $ \] and \[ $ 2,1 $ \] are permutations, but \[ $ 1,2,1 $ \], \[ $ 0,1 $ \] and \[ $ 1,3,4 $ \] — are not.

Kristina had a permutation $ p $ of $ n $ elements. She wrote it on the whiteboard $ n $ times in such a way that:

- while writing the permutation at the $ i $ -th ( $ 1 \le i \le n) $ time she skipped the element $ p_i $

 So, she wrote in total $ n $ sequences of length $ n-1 $ each.For example, suppose Kristina had a permutation $ p $ = $ [4,2,1,3] $ of length $ 4 $ . Then she did the following:

1. Wrote the sequence $ [2, 1, 3] $ , skipping the element $ p_1=4 $ from the original permutation.
2. Wrote the sequence $ [4, 1, 3] $ , skipping the element $ p_2=2 $ from the original permutation.
3. Wrote the sequence $ [4, 2, 3] $ , skipping the element $ p_3=1 $ from the original permutation.
4. Wrote the sequence $ [4, 2, 1] $ , skipping the element $ p_4=3 $ from the original permutation.

You know all $ n $ of sequences that have been written on the whiteboard, but you do not know the order in which they were written. They are given in arbitrary order. Reconstruct the original permutation from them.

For example, if you know the sequences $ [4, 2, 1] $ , $ [4, 2, 3] $ , $ [2, 1, 3] $ , $ [4, 1, 3] $ , then the original permutation will be $ p $ = $ [4, 2, 1, 3] $ .

## 输入格式

The first line of input data contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 3 \le n \le 100 $ ).

This is followed by $ n $ lines, each containing exactly $ n-1 $ integers and describing one of the sequences written out on the whiteboard.

It is guaranteed that all sequences could be obtained from some permutation $ p $ , and that the sum $ n^2 $ over all input sets does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output on a separate line a permutation $ p $ such that the given $ n $ sequences could be obtained from it.

It is guaranteed that the answer exists and it is the only one. In other words, for each test case the required permutation is sure to exist.

## 说明/提示

The first test case is described in the problem statement.

In the second test case, the sequences are written in the correct order.

## 样例 #1

### 输入

```
5
4
4 2 1
4 2 3
2 1 3
4 1 3
3
2 3
1 3
1 2
5
4 2 1 3
2 1 3 5
4 2 3 5
4 1 3 5
4 2 1 5
4
2 3 4
1 3 4
1 2 3
1 2 4
3
2 1
1 3
2 3
```

### 输出

```
4 2 1 3 
1 2 3 
4 2 1 3 5 
1 2 3 4 
2 1 3
```

