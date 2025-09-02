---
title: "Rotation Matching"
layout: "post"
diff: 普及/提高-
pid: CF1365C
tag: []
---

# Rotation Matching

## 题目描述

After the mysterious disappearance of Ashish, his two favourite disciples Ishika and Hriday, were each left with one half of a secret message. These messages can each be represented by a permutation of size $ n $ . Let's call them $ a $ and $ b $ .

Note that a permutation of $ n $ elements is a sequence of numbers $ a_1, a_2, \ldots, a_n $ , in which every number from $ 1 $ to $ n $ appears exactly once.

The message can be decoded by an arrangement of sequence $ a $ and $ b $ , such that the number of matching pairs of elements between them is maximum. A pair of elements $ a_i $ and $ b_j $ is said to match if:

- $ i = j $ , that is, they are at the same index.
- $ a_i = b_j $

His two disciples are allowed to perform the following operation any number of times:

- choose a number $ k $ and cyclically shift one of the permutations to the left or right $ k $ times.

A single cyclic shift to the left on any permutation $ c $ is an operation that sets $ c_1:=c_2, c_2:=c_3, \ldots, c_n:=c_1 $ simultaneously. Likewise, a single cyclic shift to the right on any permutation $ c $ is an operation that sets $ c_1:=c_n, c_2:=c_1, \ldots, c_n:=c_{n-1} $ simultaneously.

Help Ishika and Hriday find the maximum number of pairs of elements that match after performing the operation any (possibly zero) number of times.

## 输入格式

The first line of the input contains a single integer $ n $ $ (1 \le n \le 2 \cdot 10^5) $ — the size of the arrays.

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ $ (1 \le a_i \le n) $ — the elements of the first permutation.

The third line contains $ n $ integers $ b_1 $ , $ b_2 $ , ..., $ b_n $ $ (1 \le b_i \le n) $ — the elements of the second permutation.

## 输出格式

Print the maximum number of matching pairs of elements after performing the above operations some (possibly zero) times.

## 说明/提示

For the first case: $ b $ can be shifted to the right by $ k = 1 $ . The resulting permutations will be $ \{1, 2, 3, 4, 5\} $ and $ \{1, 2, 3, 4, 5\} $ .

For the second case: The operation is not required. For all possible rotations of $ a $ and $ b $ , the number of matching pairs won't exceed $ 1 $ .

For the third case: $ b $ can be shifted to the left by $ k = 1 $ . The resulting permutations will be $ \{1, 3, 2, 4\} $ and $ \{2, 3, 1, 4\} $ . Positions $ 2 $ and $ 4 $ have matching pairs of elements. For all possible rotations of $ a $ and $ b $ , the number of matching pairs won't exceed $ 2 $ .

## 样例 #1

### 输入

```
5
1 2 3 4 5
2 3 4 5 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
5 4 3 2 1
1 2 3 4 5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
1 3 2 4
4 2 3 1
```

### 输出

```
2
```

