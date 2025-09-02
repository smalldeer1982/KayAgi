---
title: "Distances to Zero"
layout: "post"
diff: 普及-
pid: CF803B
tag: []
---

# Distances to Zero

## 题目描述

You are given the array of integer numbers $ a_{0},a_{1},...,a_{n-1} $ . For each element find the distance to the nearest zero (to the element which equals to zero). There is at least one zero element in the given array.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=2·10^{5} $ ) — length of the array $ a $ . The second line contains integer elements of the array separated by single spaces ( $ -10^{9}<=a_{i}<=10^{9} $ ).

## 输出格式

Print the sequence $ d_{0},d_{1},...,d_{n-1} $ , where $ d_{i} $ is the difference of indices between $ i $ and nearest $ j $ such that $ a_{j}=0 $ . It is possible that $ i=j $ .

## 样例 #1

### 输入

```
9
2 1 0 3 0 0 3 2 4

```

### 输出

```
2 1 0 1 0 0 1 2 3 
```

## 样例 #2

### 输入

```
5
0 1 2 3 4

```

### 输出

```
0 1 2 3 4 
```

## 样例 #3

### 输入

```
7
5 6 0 1 -2 3 4

```

### 输出

```
2 1 0 1 2 3 4 
```

