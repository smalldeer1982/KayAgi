---
title: "Masha and geometric depression"
layout: "post"
diff: 普及+/提高
pid: CF789B
tag: []
---

# Masha and geometric depression

## 题目描述

Masha really loves algebra. On the last lesson, her strict teacher Dvastan gave she new exercise.

You are given geometric progression $ b $ defined by two integers $ b_{1} $ and $ q $ . Remind that a geometric progression is a sequence of integers $ b_{1},b_{2},b_{3},... $ , where for each $ i&gt;1 $ the respective term satisfies the condition $ b_{i}=b_{i-1}·q $ , where $ q $ is called the common ratio of the progression. Progressions in Uzhlyandia are unusual: both $ b_{1} $ and $ q $ can equal $ 0 $ . Also, Dvastan gave Masha $ m $ "bad" integers $ a_{1},a_{2},...,a_{m} $ , and an integer $ l $ .

Masha writes all progression terms one by one onto the board (including repetitive) while condition $ |b_{i}|<=l $ is satisfied ( $ |x| $ means absolute value of $ x $ ). There is an exception: if a term equals one of the "bad" integers, Masha skips it (doesn't write onto the board) and moves forward to the next term.

But the lesson is going to end soon, so Masha has to calculate how many integers will be written on the board. In order not to get into depression, Masha asked you for help: help her calculate how many numbers she will write, or print "inf" in case she needs to write infinitely many integers.

## 输入格式

The first line of input contains four integers $ b_{1} $ , $ q $ , $ l $ , $ m $ (- $ 10^{9}<=b_{1},q<=10^{9} $ , $ 1<=l<=10^{9} $ , $ 1<=m<=10^{5} $ ) — the initial term and the common ratio of progression, absolute value of maximal number that can be written on the board and the number of "bad" integers, respectively.

The second line contains $ m $ distinct integers $ a_{1},a_{2},...,a_{m} $ (- $ 10^{9}<=a_{i}<=10^{9}) $ — numbers that will never be written on the board.

## 输出格式

Print the only integer, meaning the number of progression terms that will be written on the board if it is finite, or "inf" (without quotes) otherwise.

## 说明/提示

In the first sample case, Masha will write integers $ 3,12,24 $ . Progression term $ 6 $ will be skipped because it is a "bad" integer. Terms bigger than $ 24 $ won't be written because they exceed $ l $ by absolute value.

In the second case, Masha won't write any number because all terms are equal $ 123 $ and this is a "bad" integer.

In the third case, Masha will write infinitely integers $ 123 $ .

## 样例 #1

### 输入

```
3 2 30 4
6 14 25 48

```

### 输出

```
3
```

## 样例 #2

### 输入

```
123 1 2143435 4
123 11 -5453 141245

```

### 输出

```
0
```

## 样例 #3

### 输入

```
123 1 2143435 4
54343 -13 6 124

```

### 输出

```
inf
```

