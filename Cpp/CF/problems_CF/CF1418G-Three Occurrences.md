---
title: "Three Occurrences"
layout: "post"
diff: 省选/NOI-
pid: CF1418G
tag: []
---

# Three Occurrences

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. We denote the subarray $ a[l..r] $ as the array $ [a_l, a_{l + 1}, \dots, a_r] $ ( $ 1 \le l \le r \le n $ ).

A subarray is considered good if every integer that occurs in this subarray occurs there exactly thrice. For example, the array $ [1, 2, 2, 2, 1, 1, 2, 2, 2] $ has three good subarrays:

- $ a[1..6] = [1, 2, 2, 2, 1, 1] $ ;
- $ a[2..4] = [2, 2, 2] $ ;
- $ a[7..9] = [2, 2, 2] $ .

Calculate the number of good subarrays of the given array $ a $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 5 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ ( $ 1 \le a_i \le n $ ).

## 输出格式

Print one integer — the number of good subarrays of the array $ a $ .

## 样例 #1

### 输入

```
9
1 2 2 2 1 1 2 2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10
1 2 3 4 1 2 3 1 2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
12
1 2 3 4 3 4 2 1 3 4 2 1
```

### 输出

```
1
```

