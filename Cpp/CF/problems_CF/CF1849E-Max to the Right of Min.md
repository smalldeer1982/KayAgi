---
title: "Max to the Right of Min"
layout: "post"
diff: 提高+/省选-
pid: CF1849E
tag: []
---

# Max to the Right of Min

## 题目描述

You are given a permutation $ p $ of length $ n $ — an array, consisting of integers from $ 1 $ to $ n $ , all distinct.

Let $ p_{l,r} $ denote a subarray — an array formed by writing down elements from index $ l $ to index $ r $ , inclusive.

Let $ \mathit{maxpos}_{l,r} $ denote the index of the maximum element on $ p_{l,r} $ . Similarly, let $ \mathit{minpos}_{l,r} $ denote the index of the minimum element on it.

Calculate the number of subarrays $ p_{l,r} $ such that $ \mathit{maxpos}_{l,r} > \mathit{minpos}_{l,r} $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the number of elements in the permutation.

The second line contains $ n $ integers $ p_1, p_2, \dots, p_n $ ( $ 1 \le p_i \le n $ ). All $ p_i $ are distinct.

## 输出格式

Print a single integer — the number of subarrays $ p_{l,r} $ such that $ \mathit{maxpos}_{l,r} > \mathit{minpos}_{l,r} $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
5 3 6 1 4 2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
10
5 1 6 2 8 3 4 10 9 7
```

### 输出

```
38
```

