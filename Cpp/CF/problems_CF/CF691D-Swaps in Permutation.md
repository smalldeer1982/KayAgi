---
title: "Swaps in Permutation"
layout: "post"
diff: 普及+/提高
pid: CF691D
tag: []
---

# Swaps in Permutation

## 题目描述

You are given a permutation of the numbers $ 1,2,...,n $ and $ m $ pairs of positions $ (a_{j},b_{j}) $ .

At each step you can choose a pair from the given positions and swap the numbers in that positions. What is the lexicographically maximal permutation one can get?

Let $ p $ and $ q $ be two permutations of the numbers $ 1,2,...,n $ . $ p $ is lexicographically smaller than the $ q $ if a number $ 1<=i<=n $ exists, so $ p_{k}=q_{k} $ for $ 1<=k&lt;i $ and $ p_{i}&lt;q_{i} $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{6} $ ) — the length of the permutation $ p $ and the number of pairs of positions.

The second line contains $ n $ distinct integers $ p_{i} $ ( $ 1<=p_{i}<=n $ ) — the elements of the permutation $ p $ .

Each of the last $ m $ lines contains two integers $ (a_{j},b_{j}) $ ( $ 1<=a_{j},b_{j}<=n $ ) — the pairs of positions to swap. Note that you are given a positions, not the values to swap.

## 输出格式

Print the only line with $ n $ distinct integers $ p'_{i} $ ( $ 1<=p'_{i}<=n $ ) — the lexicographically maximal permutation one can get.

## 样例 #1

### 输入

```
9 6
1 2 3 4 5 6 7 8 9
1 4
4 7
2 5
5 8
3 6
6 9

```

### 输出

```
7 8 9 4 5 6 1 2 3

```

