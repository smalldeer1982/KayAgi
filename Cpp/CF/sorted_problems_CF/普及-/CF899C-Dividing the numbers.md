---
title: "Dividing the numbers"
layout: "post"
diff: 普及-
pid: CF899C
tag: []
---

# Dividing the numbers

## 题目描述

Petya has $ n $ integers: $ 1,2,3,...,n $ . He wants to split these integers in two non-empty groups in such a way that the absolute difference of sums of integers in each group is as small as possible.

Help Petya to split the integers. Each of $ n $ integers should be exactly in one group.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=60000 $ ) — the number of integers Petya has.

## 输出格式

Print the smallest possible absolute difference in the first line.

In the second line print the size of the first group, followed by the integers in that group. You can print these integers in arbitrary order. If there are multiple answers, print any of them.

## 说明/提示

In the first example you have to put integers $ 1 $ and $ 4 $ in the first group, and $ 2 $ and $ 3 $ in the second. This way the sum in each group is $ 5 $ , and the absolute difference is $ 0 $ .

In the second example there are only two integers, and since both groups should be non-empty, you have to put one integer in the first group and one in the second. This way the absolute difference of sums of integers in each group is $ 1 $ .

## 样例 #1

### 输入

```
4

```

### 输出

```
0
2 1 4 

```

## 样例 #2

### 输入

```
2

```

### 输出

```
1
1 1 

```

