---
title: "Little Elephant and Shifts"
layout: "post"
diff: 提高+/省选-
pid: CF220C
tag: []
---

# Little Elephant and Shifts

## 题目描述

The Little Elephant has two permutations $ a $ and $ b $ of length $ n $ , consisting of numbers from 1 to $ n $ , inclusive. Let's denote the $ i $ -th $ (1<=i<=n) $ element of the permutation $ a $ as $ a_{i} $ , the $ j $ -th $ (1<=j<=n) $ element of the permutation $ b $ — as $ b_{j} $ .

The distance between permutations $ a $ and $ b $ is the minimum absolute value of the difference between the positions of the occurrences of some number in $ a $ and in $ b $ . More formally, it's such minimum $ |i-j| $ , that $ a_{i}=b_{j} $ .

A cyclic shift number $ i $ $ (1<=i<=n) $ of permutation $ b $ consisting from $ n $ elements is a permutation $ b_{i}b_{i+1}...\ b_{n}b_{1}b_{2}...\ b_{i-1} $ . Overall a permutation has $ n $ cyclic shifts.

The Little Elephant wonders, for all cyclic shifts of permutation $ b $ , what is the distance between the cyclic shift and permutation $ a $ ?

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{5}) $ — the size of the permutations. The second line contains permutation $ a $ as $ n $ distinct numbers from 1 to $ n $ , inclusive. The numbers are separated with single spaces. The third line contains permutation $ b $ in the same format.

## 输出格式

In $ n $ lines print $ n $ integers — the answers for cyclic shifts. Print the answers to the shifts in the order of the shifts' numeration in permutation $ b $ , that is, first for the 1-st cyclic shift, then for the 2-nd, and so on.

## 样例 #1

### 输入

```
2
1 2
2 1

```

### 输出

```
1
0

```

## 样例 #2

### 输入

```
4
2 1 3 4
3 4 2 1

```

### 输出

```
2
1
0
1

```

