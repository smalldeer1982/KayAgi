---
title: "Maximal Binary Matrix"
layout: "post"
diff: 普及/提高-
pid: CF803A
tag: ['贪心', '递归']
---

# Maximal Binary Matrix

## 题目描述

You are given matrix with $ n $ rows and $ n $ columns filled with zeroes. You should put $ k $ ones in it in such a way that the resulting matrix is symmetrical with respect to the main diagonal (the diagonal that goes from the top left to the bottom right corner) and is lexicographically maximal.

One matrix is lexicographically greater than the other if the first different number in the first different row from the top in the first matrix is greater than the corresponding number in the second one.

If there exists no such matrix then output -1.

## 输入格式

The first line consists of two numbers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 0<=k<=10^{6} $ ).

## 输出格式

If the answer exists then output resulting matrix. Otherwise output -1.

## 样例 #1

### 输入

```
2 1

```

### 输出

```
1 0 
0 0 

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
1 0 0 
0 1 0 
0 0 0 

```

## 样例 #3

### 输入

```
2 5

```

### 输出

```
-1

```

