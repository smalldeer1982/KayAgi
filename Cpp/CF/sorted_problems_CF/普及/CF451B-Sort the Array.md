---
title: "Sort the Array"
layout: "post"
diff: 普及/提高-
pid: CF451B
tag: []
---

# Sort the Array

## 题目描述

Being a programmer, you like arrays a lot. For your birthday, your friends have given you an array $ a $ consisting of $ n $ distinct integers.

Unfortunately, the size of $ a $ is too small. You want a bigger array! Your friends agree to give you a bigger array, but only if you are able to answer the following question correctly: is it possible to sort the array $ a $ (in increasing order) by reversing exactly one segment of $ a $ ? See definitions of segment and reversing in the notes.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=10^{5} $ ) — the size of array $ a $ .

The second line contains $ n $ distinct space-separated integers: $ a[1],a[2],...,a[n] $ ( $ 1<=a[i]<=10^{9} $ ).

## 输出格式

Print "yes" or "no" (without quotes), depending on the answer.

If your answer is "yes", then also print two space-separated integers denoting start and end (start must not be greater than end) indices of the segment to be reversed. If there are multiple ways of selecting these indices, print any of them.

## 说明/提示

Sample 1. You can reverse the entire array to get $ [1,2,3] $ , which is sorted.

Sample 3. No segment can be reversed such that the array will be sorted.

Definitions

A segment $ [l,r] $ of array $ a $ is the sequence $ a[l],a[l+1],...,a[r] $ .

If you have an array $ a $ of size $ n $ and you reverse its segment $ [l,r] $ , the array will become:

 $ a[1],a[2],...,a[l-2],a[l-1],a[r],a[r-1],...,a[l+1],a[l],a[r+1],a[r+2],...,a[n-1],a[n]. $

## 样例 #1

### 输入

```
3
3 2 1

```

### 输出

```
yes
1 3

```

## 样例 #2

### 输入

```
4
2 1 3 4

```

### 输出

```
yes
1 2

```

## 样例 #3

### 输入

```
4
3 1 2 4

```

### 输出

```
no

```

## 样例 #4

### 输入

```
2
1 2

```

### 输出

```
yes
1 1

```

