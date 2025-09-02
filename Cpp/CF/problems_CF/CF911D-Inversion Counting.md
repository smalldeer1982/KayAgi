---
title: "Inversion Counting"
layout: "post"
diff: 普及+/提高
pid: CF911D
tag: ['数学', '平衡树', '树状数组']
---

# Inversion Counting

## 题目描述

A permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array. An inversion in a permutation $ p $ is a pair of indices $ (i,j) $ such that $ i>j $ and $ a_{i}<a_{j} $ . For example, a permutation $ [4,1,3,2] $ contains $ 4 $ inversions: $ (2,1) $ , $ (3,1) $ , $ (4,1) $ , $ (4,3) $ .

You are given a permutation $ a $ of size $ n $ and $ m $ queries to it. Each query is represented by two indices $ l $ and $ r $ denoting that you have to reverse the segment $ [l,r] $ of the permutation. For example, if $ a=[1,2,3,4] $ and a query $ l=2 $ , $ r=4 $ is applied, then the resulting permutation is $ [1,4,3,2] $ .

After each query you have to determine whether the number of inversions is odd or even.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=1500 $ ) — the size of the permutation.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=n $ ) — the elements of the permutation. These integers are pairwise distinct.

The third line contains one integer $ m $ ( $ 1<=m<=2·10^{5} $ ) — the number of queries to process.

Then $ m $ lines follow, $ i $ -th line containing two integers $ l_{i} $ , $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) denoting that $ i $ -th query is to reverse a segment $ [l_{i},r_{i}] $ of the permutation. All queries are performed one after another.

## 输出格式

Print $ m $ lines. $ i $ -th of them must be equal to odd if the number of inversions in the permutation after $ i $ -th query is odd, and even otherwise.

## 说明/提示

The first example:

1. after the first query $ a=[2,1,3] $ , inversion: $ (2,1) $ ;
2. after the second query $ a=[2,3,1] $ , inversions: $ (3,1) $ , $ (3,2) $ .

The second example:

1. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
2. $ a=[3,4,2,1] $ , inversions: $ (3,1) $ , $ (4,1) $ , $ (3,2) $ , $ (4,2) $ , $ (4,3) $ ;
3. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
4. $ a=[1,4,2,3] $ , inversions: $ (3,2) $ , $ (4,2) $ .

## 样例 #1

### 输入

```
3
1 2 3
2
1 2
2 3

```

### 输出

```
odd
even

```

## 样例 #2

### 输入

```
4
1 2 4 3
4
1 1
1 4
1 4
2 3

```

### 输出

```
odd
odd
odd
even

```

