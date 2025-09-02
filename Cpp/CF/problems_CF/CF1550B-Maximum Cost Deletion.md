---
title: "Maximum Cost Deletion"
layout: "post"
diff: 普及-
pid: CF1550B
tag: []
---

# Maximum Cost Deletion

## 题目描述

You are given a string $ s $ of length $ n $ consisting only of the characters 0 and 1.

You perform the following operation until the string becomes empty: choose some consecutive substring of equal characters, erase it from the string and glue the remaining two parts together (any of them can be empty) in the same order. For example, if you erase the substring 111 from the string 111110, you will get the string 110. When you delete a substring of length $ l $ , you get $ a \cdot l + b $ points.

Your task is to calculate the maximum number of points that you can score in total, if you have to make the given string empty.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2000 $ ) — the number of testcases.

The first line of each testcase contains three integers $ n $ , $ a $ and $ b $ ( $ 1 \le n \le 100; -100 \le a, b \le 100 $ ) — the length of the string $ s $ and the parameters $ a $ and $ b $ .

The second line contains the string $ s $ . The string $ s $ consists only of the characters 0 and 1.

## 输出格式

For each testcase, print a single integer — the maximum number of points that you can score.

## 说明/提示

In the first example, it is enough to delete the entire string, then we will get $ 2 \cdot 3 + 0 = 6 $ points.

In the second example, if we delete characters one by one, then for each deleted character we will get $ (-2) \cdot 1 + 5 = 3 $ points, i. e. $ 15 $ points in total.

In the third example, we can delete the substring 00 from the string 100111, we get $ 1 \cdot 2 + (-4) = -2 $ points, and the string will be equal to 1111, removing it entirely we get $ 1 \cdot 4 + (-4) = 0 $ points. In total, we got $ -2 $ points for $ 2 $ operations.

## 样例 #1

### 输入

```
3
3 2 0
000
5 -2 5
11001
6 1 -4
100111
```

### 输出

```
6
15
-2
```

