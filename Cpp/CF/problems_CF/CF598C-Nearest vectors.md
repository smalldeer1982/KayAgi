---
title: "Nearest vectors"
layout: "post"
diff: 普及+/提高
pid: CF598C
tag: ['向量']
---

# Nearest vectors

## 题目描述

You are given the set of vectors on the plane, each of them starting at the origin. Your task is to find a pair of vectors with the minimal non-oriented angle between them.

Non-oriented angle is non-negative value, minimal between clockwise and counterclockwise direction angles. Non-oriented angle is always between $ 0 $ and $ π $ . For example, opposite directions vectors have angle equals to $ π $ .

## 输入格式

First line of the input contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the number of vectors.

The $ i $ -th of the following $ n $ lines contains two integers $ x_{i} $ and $ y_{i} $ ( $ |x|,|y|<=10000,x^{2}+y^{2}&gt;0 $ ) — the coordinates of the $ i $ -th vector. Vectors are numbered from $ 1 $ to $ n $ in order of appearing in the input. It is guaranteed that no two vectors in the input share the same direction (but they still can have opposite directions).

## 输出格式

Print two integer numbers $ a $ and $ b $ ( $ a≠b $ ) — a pair of indices of vectors with the minimal non-oriented angle. You can print the numbers in any order. If there are many possible answers, print any.

## 样例 #1

### 输入

```
4
-1 0
0 -1
1 0
1 1

```

### 输出

```
3 4

```

## 样例 #2

### 输入

```
6
-1 0
0 -1
1 0
1 1
-4 -5
-4 -6

```

### 输出

```
6 5
```

