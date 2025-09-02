---
title: "Transformation: from A to B"
layout: "post"
diff: 普及-
pid: CF727A
tag: []
---

# Transformation: from A to B

## 题目描述

Vasily has a number $ a $ , which he wants to turn into a number $ b $ . For this purpose, he can do two types of operations:

- multiply the current number by $ 2 $ (that is, replace the number $ x $ by $ 2·x $ );
- append the digit $ 1 $ to the right of current number (that is, replace the number $ x $ by $ 10·x+1 $ ).

You need to help Vasily to transform the number $ a $ into the number $ b $ using only the operations described above, or find that it is impossible.

Note that in this task you are not required to minimize the number of operations. It suffices to find any way to transform $ a $ into $ b $ .

## 输入格式

The first line contains two positive integers $ a $ and $ b $ ( $ 1<=a&lt;b<=10^{9} $ ) — the number which Vasily has and the number he wants to have.

## 输出格式

If there is no way to get $ b $ from $ a $ , print "NO" (without quotes).

Otherwise print three lines. On the first line print "YES" (without quotes). The second line should contain single integer $ k $ — the length of the transformation sequence. On the third line print the sequence of transformations $ x_{1},x_{2},...,x_{k} $ , where:

- $ x_{1} $ should be equal to $ a $ ,
- $ x_{k} $ should be equal to $ b $ ,
- $ x_{i} $ should be obtained from $ x_{i-1} $ using any of two described operations ( $ 1&lt;i<=k $ ).

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
2 162

```

### 输出

```
YES
5
2 4 8 81 162 

```

## 样例 #2

### 输入

```
4 42

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
100 40021

```

### 输出

```
YES
5
100 200 2001 4002 40021 

```

