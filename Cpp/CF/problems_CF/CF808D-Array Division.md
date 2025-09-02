---
title: "Array Division"
layout: "post"
diff: 普及+/提高
pid: CF808D
tag: []
---

# Array Division

## 题目描述

Vasya has an array $ a $ consisting of positive integer numbers. Vasya wants to divide this array into two non-empty consecutive parts (the prefix and the suffix) so that the sum of all elements in the first part equals to the sum of elements in the second part. It is not always possible, so Vasya will move some element before dividing the array (Vasya will erase some element and insert it into an arbitrary position).

Inserting an element in the same position he was erased from is also considered moving.

Can Vasya divide the array after choosing the right element to move and its new position?

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=100000 $ ) — the size of the array.

The second line contains $ n $ integers $ a_{1},a_{2}...\ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the elements of the array.

## 输出格式

Print YES if Vasya can divide the array after moving one element. Otherwise print NO.

## 说明/提示

In the first example Vasya can move the second element to the end of the array.

In the second example no move can make the division possible.

In the third example Vasya can move the fourth element by one position to the left.

## 样例 #1

### 输入

```
3
1 3 2

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
5
1 2 3 4 5

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
2 2 3 4 5

```

### 输出

```
YES

```

