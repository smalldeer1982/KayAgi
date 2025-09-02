---
title: "Count Binary Strings"
layout: "post"
diff: 提高+/省选-
pid: CF1767C
tag: ['动态规划 DP']
---

# Count Binary Strings

## 题目描述

You are given an integer $ n $ . You have to calculate the number of binary (consisting of characters 0 and/or 1) strings $ s $ meeting the following constraints.

For every pair of integers $ (i, j) $ such that $ 1 \le i \le j \le n $ , an integer $ a_{i,j} $ is given. It imposes the following constraint on the string $ s_i s_{i+1} s_{i+2} \dots s_j $ :

- if $ a_{i,j} = 1 $ , all characters in $ s_i s_{i+1} s_{i+2} \dots s_j $ should be the same;
- if $ a_{i,j} = 2 $ , there should be at least two different characters in $ s_i s_{i+1} s_{i+2} \dots s_j $ ;
- if $ a_{i,j} = 0 $ , there are no additional constraints on the string $ s_i s_{i+1} s_{i+2} \dots s_j $ .

Count the number of binary strings $ s $ of length $ n $ meeting the aforementioned constraints. Since the answer can be large, print it modulo $ 998244353 $ .

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ).

Then $ n $ lines follow. The $ i $ -th of them contains $ n-i+1 $ integers $ a_{i,i}, a_{i,i+1}, a_{i,i+2}, \dots, a_{i,n} $ ( $ 0 \le a_{i,j} \le 2 $ ).

## 输出格式

Print one integer — the number of strings meeting the constraints, taken modulo $ 998244353 $ .

## 说明/提示

In the first example, the strings meeting the constraints are 001, 010, 011, 100, 101, 110.

In the second example, the strings meeting the constraints are 001, 110.

## 样例 #1

### 输入

```
3
1 0 2
1 0
1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
1 1 2
1 0
1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
1 2 1
1 0
1
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3
2 0 2
0 1
1
```

### 输出

```
0
```

