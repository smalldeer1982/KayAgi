---
title: "Lesha and array splitting"
layout: "post"
diff: 普及/提高-
pid: CF754A
tag: []
---

# Lesha and array splitting

## 题目描述

One spring day on his way to university Lesha found an array $ A $ . Lesha likes to split arrays into several parts. This time Lesha decided to split the array $ A $ into several, possibly one, new arrays so that the sum of elements in each of the new arrays is not zero. One more condition is that if we place the new arrays one after another they will form the old array $ A $ .

Lesha is tired now so he asked you to split the array. Help Lesha!

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=100 $ ) — the number of elements in the array $ A $ .

The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{3}<=a_{i}<=10^{3} $ ) — the elements of the array $ A $ .

## 输出格式

If it is not possible to split the array $ A $ and satisfy all the constraints, print single line containing "NO" (without quotes).

Otherwise in the first line print "YES" (without quotes). In the next line print single integer $ k $ — the number of new arrays. In each of the next $ k $ lines print two integers $ l_{i} $ and $ r_{i} $ which denote the subarray $ A[l_{i}...\ r_{i}] $ of the initial array $ A $ being the $ i $ -th new array. Integers $ l_{i} $ , $ r_{i} $ should satisfy the following conditions:

- $ l_{1}=1 $
- $ r_{k}=n $
- $ r_{i}+1=l_{i+1} $ for each $ 1<=i&lt;k $ .

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
1 2 -3

```

### 输出

```
YES
2
1 2
3 3

```

## 样例 #2

### 输入

```
8
9 -12 3 4 -4 -10 7 3

```

### 输出

```
YES
2
1 2
3 8

```

## 样例 #3

### 输入

```
1
0

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
4
1 2 3 -5

```

### 输出

```
YES
4
1 1
2 2
3 3
4 4

```

