---
title: "Beautiful Subarrays"
layout: "post"
diff: 普及+/提高
pid: CF665E
tag: ['前缀和', '字典树 Trie']
---

# Beautiful Subarrays

## 题目描述

One day, ZS the Coder wrote down an array of integers $ a $ with elements $ a_{1},a_{2},...,a_{n} $ .

A subarray of the array $ a $ is a sequence $ a_{l},a_{l+1},...,a_{r} $ for some integers $ (l,r) $ such that $ 1<=l<=r<=n $ . ZS the Coder thinks that a subarray of $ a $ is beautiful if the bitwise xor of all the elements in the subarray is at least $ k $ .

Help ZS the Coder find the number of beautiful subarrays of $ a $ !

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=10^{6},1<=k<=10^{9} $ ) — the number of elements in the array $ a $ and the value of the parameter $ k $ .

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{9} $ ) — the elements of the array $ a $ .

## 输出格式

Print the only integer $ c $ — the number of beautiful subarrays of the array $ a $ .

## 样例 #1

### 输入

```
3 1
1 2 3

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 2
1 2 3

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3 3
1 2 3

```

### 输出

```
2

```

