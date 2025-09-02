---
title: "Bear and Strings"
layout: "post"
diff: 普及/提高-
pid: CF385B
tag: []
---

# Bear and Strings

## 题目描述

The bear has a string $ s=s_{1}s_{2}...\ s_{|s|} $ (record $ |s| $ is the string's length), consisting of lowercase English letters. The bear wants to count the number of such pairs of indices $ i,j $ $ (1<=i<=j<=|s|) $ , that string $ x(i,j)=s_{i}s_{i+1}...\ s_{j} $ contains at least one string "bear" as a substring.

String $ x(i,j) $ contains string "bear", if there is such index $ k $ $ (i<=k<=j-3) $ , that $ s_{k}=b $ , $ s_{k+1}=e $ , $ s_{k+2}=a $ , $ s_{k+3}=r $ .

Help the bear cope with the given problem.

## 输入格式

The first line contains a non-empty string $ s $ $ (1<=|s|<=5000) $ . It is guaranteed that the string only consists of lowercase English letters.

## 输出格式

Print a single number — the answer to the problem.

## 说明/提示

In the first sample, the following pairs $ (i,j) $ match: $ (1,4),(1,5),(1,6),(1,7),(1,8),(1,9) $ .

In the second sample, the following pairs $ (i,j) $ match: $ (1,4),(1,5),(1,6),(1,7),(1,8),(1,9),(1,10),(1,11),(2,10),(2,11),(3,10),(3,11),(4,10),(4,11),(5,10),(5,11),(6,10),(6,11),(7,10),(7,11) $ .

## 样例 #1

### 输入

```
bearbtear

```

### 输出

```
6

```

## 样例 #2

### 输入

```
bearaabearc

```

### 输出

```
20

```

