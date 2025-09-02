---
title: "Longest k-Good Segment"
layout: "post"
diff: 普及/提高-
pid: CF616D
tag: []
---

# Longest k-Good Segment

## 题目描述

The array $ a $ with $ n $ integers is given. Let's call the sequence of one or more consecutive elements in $ a $ segment. Also let's call the segment k-good if it contains no more than $ k $ different values.

Find any longest k-good segment.

As the input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 输入格式

The first line contains two integers $ n,k $ ( $ 1<=k<=n<=5·10^{5} $ ) — the number of elements in $ a $ and the parameter $ k $ .

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{6} $ ) — the elements of the array $ a $ .

## 输出格式

Print two integers $ l,r $ ( $ 1<=l<=r<=n $ ) — the index of the left and the index of the right ends of some k-good longest segment. If there are several longest segments you can print any of them. The elements in $ a $ are numbered from $ 1 $ to $ n $ from left to right.

## 样例 #1

### 输入

```
5 5
1 2 3 4 5

```

### 输出

```
1 5

```

## 样例 #2

### 输入

```
9 3
6 5 1 2 3 2 1 4 5

```

### 输出

```
3 7

```

## 样例 #3

### 输入

```
3 1
1 2 3

```

### 输出

```
1 1

```

