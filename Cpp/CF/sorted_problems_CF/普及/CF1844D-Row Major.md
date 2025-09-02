---
title: "Row Major"
layout: "post"
diff: 普及/提高-
pid: CF1844D
tag: []
---

# Row Major

## 题目描述

The row-major order of an $ r \times c $ grid of characters $ A $ is the string obtained by concatenating all the rows, i.e. $ $$$ A_{11}A_{12} \dots A_{1c}A_{21}A_{22} \dots A_{2c} \dots A_{r1}A_{r2} \dots A_{rc}.  $ $ </p><p>A grid of characters  $ A $  is <span class="tex-font-style-it">bad</span> if there are some two adjacent cells (cells sharing an edge) with the same character.</p><p>You are given a positive integer  $ n $ . Consider all strings  $ s $  consisting of only lowercase Latin letters such that they are <span class="tex-font-style-bf">not</span> the row-major order of <span class="tex-font-style-bf">any</span> bad grid. Find any string with the minimum number of distinct characters among all such strings of length  $ n$$$.

It can be proven that at least one such string exists under the constraints of the problem.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The only line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a string with the minimum number of distinct characters among all suitable strings of length $ n $ .

If there are multiple solutions, print any of them.

## 说明/提示

In the first test case, there are $ 3 $ ways $ s $ can be the row-major order of a grid, and they are all not bad:

tththathatat It can be proven that $ 3 $ distinct characters is the minimum possible.In the second test case, there are $ 2 $ ways $ s $ can be the row-major order of a grid, and they are both not bad:

iiss It can be proven that $ 2 $ distinct characters is the minimum possible.In the third test case, there is only $ 1 $ way $ s $ can be the row-major order of a grid, and it is not bad.

In the fourth test case, there are $ 4 $ ways $ s $ can be the row-major order of a grid, and they are all not bad:

ttotomtomatoomaatomtoato It can be proven that $ 4 $ distinct characters is the minimum possible. Note that, for example, the string "orange" is not an acceptable output because it has $ 6 > 4 $ distinct characters, and the string "banana" is not an acceptable output because it is the row-major order of the following bad grid: banana

## 样例 #1

### 输入

```
4
4
2
1
6
```

### 输出

```
that
is
a
tomato
```

