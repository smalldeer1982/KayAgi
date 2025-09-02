---
title: "WATER - Water among Cubes"
layout: "post"
diff: 普及+/提高
pid: SP212
tag: []
---

# WATER - Water among Cubes

## 题目描述

 On a rectangular mesh comprising  _n\*m_ fields,  _n\*m_ cuboids were put, one cuboid on each field. A base of each cuboid covers one field and its surface equals to one square inch. Cuboids on adjacent fields adhere one to another so close that there are no gaps between them. A heavy rain pelted on a construction so that in some areas puddles of water appeared.

   
### Task

 Write a program which:

- reads from the standard input a size of the chessboard and heights of cuboids put on the fields,
- computes maximal water volume, which may gather in puddles after the rain,
- writes results in the standard output.

## 输入格式

 The number of test cases t is in the first line of input, then t test cases follow separated by an empty line. In the first line of each test case two positive integers 1 <=  _n_ <= 100, 1 <=  _m_ <= 100 are written. They are the size of the mesh. In each of the following  _n_ lines there are  _m_ integers from the interval \[1..10000\]; _i_-th number in _j_-th line denotes a height of a cuboid given in inches put on the field in the _i_-th column and _j_-th raw of the chessboard.

## 输出格式

 Your program should write for each tes case one integer equal to the maximal volume of water (given in cubic inches), which may gather in puddles on the construction.

## 样例 #1

### 输入

```
1
3 6
3 3 4 4 4 2
3 1 3 2 1 4
7 3 1 6 4 1
```

### 输出

```
5
```

