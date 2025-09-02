---
title: "Restore Permutation"
layout: "post"
diff: 普及+/提高
pid: CF1208D
tag: []
---

# Restore Permutation

## 题目描述

An array of integers $ p_{1},p_{2}, \ldots,p_{n} $ is called a permutation if it contains each number from $ 1 $ to $ n $ exactly once. For example, the following arrays are permutations: $ [3,1,2], [1], [1,2,3,4,5] $ and $ [4,3,1,2] $ . The following arrays are not permutations: $ [2], [1,1], [2,3,4] $ .

There is a hidden permutation of length $ n $ .

For each index $ i $ , you are given $ s_{i} $ , which equals to the sum of all $ p_{j} $ such that $ j < i $ and $ p_{j} < p_{i} $ . In other words, $ s_i $ is the sum of elements before the $ i $ -th element that are smaller than the $ i $ -th element.

Your task is to restore the permutation.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{5} $ ) — the size of the permutation.

The second line contains $ n $ integers $ s_{1}, s_{2}, \ldots, s_{n} $ ( $ 0 \le s_{i} \le \frac{n(n-1)}{2} $ ).

It is guaranteed that the array $ s $ corresponds to a valid permutation of length $ n $ .

## 输出格式

Print $ n $ integers $ p_{1}, p_{2}, \ldots, p_{n} $ — the elements of the restored permutation. We can show that the answer is always unique.

## 说明/提示

In the first example for each $ i $ there is no index $ j $ satisfying both conditions, hence $ s_i $ are always $ 0 $ .

In the second example for $ i = 2 $ it happens that $ j = 1 $ satisfies the conditions, so $ s_2 = p_1 $ .

In the third example for $ i = 2, 3, 4 $ only $ j = 1 $ satisfies the conditions, so $ s_2 = s_3 = s_4 = 1 $ . For $ i = 5 $ all $ j = 1, 2, 3, 4 $ are possible, so $ s_5 = p_1 + p_2 + p_3 + p_4 = 10 $ .

## 样例 #1

### 输入

```
3
0 0 0

```

### 输出

```
3 2 1

```

## 样例 #2

### 输入

```
2
0 1

```

### 输出

```
1 2

```

## 样例 #3

### 输入

```
5
0 1 1 1 10

```

### 输出

```
1 4 3 2 5

```

