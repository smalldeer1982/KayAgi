---
title: "Unsorting Array"
layout: "post"
diff: 普及+/提高
pid: CF252B
tag: []
---

# Unsorting Array

## 题目描述

Little Petya likes arrays of integers a lot. Recently his mother has presented him one such array consisting of $ n $ elements. Petya is now wondering whether he can swap any two distinct integers in the array so that the array got unsorted. Please note that Petya can not swap equal integers even if they are in distinct positions in the array. Also note that Petya must swap some two integers even if the original array meets all requirements.

Array $ a $ (the array elements are indexed from 1) consisting of $ n $ elements is called sorted if it meets at least one of the following two conditions:

1. $ a_{1}<=a_{2}<=...<=a_{n} $ ;
2. $ a_{1}>=a_{2}>=...>=a_{n} $ .

Help Petya find the two required positions to swap or else say that they do not exist.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ). The second line contains $ n $ non-negative space-separated integers $ a_{1},a_{2},...,a_{n} $ — the elements of the array that Petya's mother presented him. All integers in the input do not exceed $ 10^{9} $ .

## 输出格式

If there is a pair of positions that make the array unsorted if swapped, then print the numbers of these positions separated by a space. If there are several pairs of positions, print any of them. If such pair does not exist, print -1. The positions in the array are numbered with integers from $ 1 $ to $ n $ .

## 说明/提示

In the first two samples the required pairs obviously don't exist.

In the third sample you can swap the first two elements. After that the array will look like this: 2 1 3 4. This array is unsorted.

## 样例 #1

### 输入

```
1
1

```

### 输出

```
-1

```

## 样例 #2

### 输入

```
2
1 2

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
4
1 2 3 4

```

### 输出

```
1 2

```

## 样例 #4

### 输入

```
3
1 1 1

```

### 输出

```
-1

```

