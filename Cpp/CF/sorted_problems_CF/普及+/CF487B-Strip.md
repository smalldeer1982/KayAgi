---
title: "Strip"
layout: "post"
diff: 普及+/提高
pid: CF487B
tag: []
---

# Strip

## 题目描述

Alexandra has a paper strip with $ n $ numbers on it. Let's call them $ a_{i} $ from left to right.

Now Alexandra wants to split it into some pieces (possibly $ 1 $ ). For each piece of strip, it must satisfy:

- Each piece should contain at least $ l $ numbers.
- The difference between the maximal and the minimal number on the piece should be at most $ s $ .

Please help Alexandra to find the minimal number of pieces meeting the condition above.

## 输入格式

The first line contains three space-separated integers $n,s,l (1\le n\le10^5, 0\le s\le10^9, 1\le l\le10^5)$.

The second line contains $n$ integers $a_i$ separated by spaces $(-10^9\le a_i\le10^9)$.

## 输出格式

Output the minimal number of strip pieces.

If there are no ways to split the strip, output -1.

## 说明/提示

For the first sample, we can split the strip into $3$ pieces: $[1,3,1], [2,4], [1,2]$.

For the second sample, we can't let $1$ and $100$ be on the same piece, so no solution exists.

## 样例 #1

### 输入

```
7 2 2
1 3 1 2 4 1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7 2 2
1 100 1 100 1 100 1

```

### 输出

```
-1

```

