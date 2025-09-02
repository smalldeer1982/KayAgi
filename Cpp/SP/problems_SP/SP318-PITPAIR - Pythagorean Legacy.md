---
title: "PITPAIR - Pythagorean Legacy"
layout: "post"
diff: 难度0
pid: SP318
tag: []
---

# PITPAIR - Pythagorean Legacy

## 题目描述

 It is necessary to find a minimal integer value R which is equal to the length of the hypotenuse (the side opposite the right angle) of N non-identical rectangular triangles with integer lengths of sides.

## 输入格式

 t - number of test cases \[t <= 100\], than t lines follow, each line contains one integer - N, equal to the required number of different rectangular triangles. \[1 <= N <= 2000\]

## 输出格式

 For each test case your program should output a number R in a separate line (R fits in a 64-bit integer), equal to the minimal integer value of a hypotenuse for which exactly N different rectangular triangles can be constructed; then in separate lines follow exactly N numbers equal to the shorter cathetus (side adjacent to the right angle) of each of the rectangular triangles, in ascending order.

## 样例 #1

### 输入

```
2
1
2
```

### 输出

```
5
3
25
7
15
```

