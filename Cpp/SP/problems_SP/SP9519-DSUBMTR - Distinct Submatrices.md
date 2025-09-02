---
title: "DSUBMTR - Distinct Submatrices"
layout: "post"
diff: 难度0
pid: SP9519
tag: []
---

# DSUBMTR - Distinct Submatrices

## 题目描述

Consider an matrix of capital letters. By selecting consecutive columns and rows, we can define the sub-matrix as the elements on chosen columns and rows.

Two sub-matrices should be regarded the same if and only if they have the same detentions and characters (which, of course, are capital letters) on corresponding position. It is your task to find the number of distinct sub-matrices of a given letter matrix.

## 输入格式

The input contains a lot of test cases. The first line of input contains exactly one integer, indicating the number of test cases.

For each of the test case, the first line contains two integers **N** and **M**, denoting the number of rows and columns of the given matrix. (1 <= **N**, **M** <= 128)

The next **N** lines contain only capital letters, indicating the given matrix.

## 输出格式

For each test case, output a single integer denoting the number of distinct sub-matrices.

## 样例 #1

### 输入

```
2
2 2
AB
BA
3 3
ABA
BAA
AAA
```

### 输出

```
Case #1: 7
Case #2: 22
```

