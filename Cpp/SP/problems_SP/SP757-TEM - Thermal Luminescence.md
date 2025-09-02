---
title: "TEM - Thermal Luminescence"
layout: "post"
diff: 难度0
pid: SP757
tag: []
---

# TEM - Thermal Luminescence

## 题目描述

 After many years of hard work a group of scientists developed a shiny new state-of-the-art processor with a 3D configuration. Due to the high clock frequency at which this processor works, the silicon cube uses up too much energy. Even with its powerful cooling system, the processor is unable to cope with the heat discharge in some of its cubical blocks. With the help of special analysis methods, scientists have developed the overheat rate for each of the cubical blocks of the system. As it conveniently happens, this overheat rate is an integer value, either positive or negative depending on many factors (such as the proximity of ventilators, refrigerators, etc.).

 Science can do no more, so now the developers of the processor need your support. For a given three-dimensional matrix representing the overheat rate of elements of the processor, you have to find a submatrix for which the sum of overheat rates coming from all its elements is maximal.

## 输入格式

_t_ – number of test cases \[_t_ <= 99\], then t tests follow.   
 Each test begins with 3 integers: x, y, z – the width, length and height of matrix \[5 <= x, y, z <= 50\]. Then there follows the description of x rectangular 2D matrixes of height y and width z. In total there are x\*y\*z integers, which absolute value does not exceed 10000.

## 输出格式

For each test case you should output 6 integers: x1, y1, z1, x2, y2, z2, where each triple (xi, yi, zi) defines one of the two opposite corners of submatrix, resulting in the maximum overheat. \[1 <= x1 <= x2 <= x\] \[1 <= y1 <= y2 <= y\] \[1 <= z1 <= z2 <= z\]

## 样例 #1

### 输入

```
1
5 5 5
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
-1 -1 -10 -1 -1
-1 -1 -10 -1 -1
-1 -1 -10 -1 -1
-1 -1 -10 -1 -1
-1 -1 -10 -1 -1
20 2 2 2 20
20 2 2 2 20
20 2 2 2 20
20 2 2 2 20
20 2 2 2 20
5 5 5 5 5
5 5 5 5 5
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
-10 10 -10 10 -10
-10 10 -10 10 -10
-10 10 -10 10 -10
-10 10 -10 10 -10
-10 10 -10 10 -10
```

### 输出

```
3 1 1 4 5 5 

Note:
The maximum overheat for the example is equal to 295.
```

