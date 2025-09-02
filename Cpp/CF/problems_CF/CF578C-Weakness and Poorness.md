---
title: "Weakness and Poorness"
layout: "post"
diff: 普及+/提高
pid: CF578C
tag: ['前缀和']
---

# Weakness and Poorness

## 题目描述

You are given a sequence of n integers $ a_{1},a_{2},...,a_{n} $ .

Determine a real number $ x $ such that the weakness of the sequence $ a_{1}-x,a_{2}-x,...,a_{n}-x $ is as small as possible.

The weakness of a sequence is defined as the maximum value of the poorness over all segments (contiguous subsequences) of a sequence.

The poorness of a segment is defined as the absolute value of sum of the elements of segment.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=200000 $ ), the length of a sequence.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ |a_{i}|<=10000 $ ).

## 输出格式

Output a real number denoting the minimum possible weakness of $ a_{1}-x,a_{2}-x,...,a_{n}-x $ . Your answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-6} $ .

## 说明/提示

For the first case, the optimal value of $ x $ is $ 2 $ so the sequence becomes $ -1 $ , $ 0 $ , $ 1 $ and the max poorness occurs at the segment "-1" or segment "1". The poorness value (answer) equals to $ 1 $ in this case.

For the second sample the optimal value of $ x $ is $ 2.5 $ so the sequence becomes $ -1.5,-0.5,0.5,1.5 $ and the max poorness occurs on segment "-1.5 -0.5" or "0.5 1.5". The poorness value (answer) equals to $ 2 $ in this case.

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
1.000000000000000

```

## 样例 #2

### 输入

```
4
1 2 3 4

```

### 输出

```
2.000000000000000

```

## 样例 #3

### 输入

```
10
1 10 2 9 3 8 4 7 5 6

```

### 输出

```
4.500000000000000

```

