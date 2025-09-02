---
title: "Best Subsegment"
layout: "post"
diff: 普及-
pid: CF1117A
tag: []
---

# Best Subsegment

## 题目描述

You are given array $ a_1, a_2, \dots, a_n $ . Find the subsegment $ a_l, a_{l+1}, \dots, a_r $ ( $ 1 \le l \le r \le n $ ) with maximum arithmetic mean $ \frac{1}{r - l + 1}\sum\limits_{i=l}^{r}{a_i} $ (in floating-point numbers, i.e. without any rounding).

If there are many such subsegments find the longest one.

## 输入格式

The first line contains single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — length of the array $ a $ .

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the array $ a $ .

## 输出格式

Print the single integer — the length of the longest subsegment with maximum possible arithmetic mean.

## 说明/提示

The subsegment $ [3, 4] $ is the longest among all subsegments with maximum arithmetic mean.

## 样例 #1

### 输入

```
5
6 1 6 6 0

```

### 输出

```
2

```

