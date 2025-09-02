---
title: "QUADAREA - Maximal Quadrilateral Area"
layout: "post"
diff: 普及+/提高
pid: SP2716
tag: ['计算几何']
---

# QUADAREA - Maximal Quadrilateral Area

## 题目描述

You are trying to build a house, but unfortunately you currently have only four available walls with side lengths a, b, c, and d. You want your house to be as big as possible, so you would like to know the largest possible area of any quadrilateral you can construct with these four side lengths.

## 输入格式

The first line contains the integer T (1 ≤ T ≤ 2,000), the number of tests. Each test contains a single line with four real numbers: a, b, c, and d (0 < a, b, c, d < 1,000). Note that it will always be possible to form a valid quadrilateral with these lengths; that is, the sum of any three side lengths will be strictly larger than the other one.

## 输出格式

For each test case, print a single line containing the largest possible area. Your output will be accepted if it is within 0.01 of the official answer.

## 样例 #1

### 输入

```
2
1 2 1 2
0.5 0.5 0.5 0.5
```

### 输出

```
2.00
0.25
```

