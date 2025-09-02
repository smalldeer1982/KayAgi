---
title: "MMATRIX - SHIFT Operator on Matrix"
layout: "post"
diff: 难度0
pid: SP3935
tag: []
---

# MMATRIX - SHIFT Operator on Matrix

## 题目描述

[English](/problems/MMATRIX/en/) [Vietnamese](/problems/MMATRIX/vn/) ```

Given an n×n matrix A, whose entries Ai,j are integer numbers ( 0 ≤ i < n,
0 ≤ j < n ). An operation SHIFT at row i ( 0 ≤ i < n ) will move the integers
in the row one position right, and the rightmost integer will wrap around
to the leftmost column.
```
 [![Image and video hosting by TinyPic](https://cdn.luogu.com.cn/upload/vjudge_pic/SP3935/bbada0fafe275fea0b98698f09737d60ff1338e8.png)](http://tinypic.com) ```

You can do the SHIFT operation at arbitrary row, and as many times as you like. 
Define Cj=A0,j+A1,j+..+A(n-1),j and M = max {Cj|0<=j < n } . 
Cj is the sum of all number in column ith.
Your job is to minimize M. 
```

## 输入格式

```

The input consists of several test cases. The ﬁrst line of each test case 
contains an integer n. Each of the following n lines contains n integers, 
indicating the matrix A. The input is terminated by a single line with 
an integer −1. You may assume that 1 ≤ n ≤ 7 and |Ai,j| < 10^4.

Sample Input
2
4 6
3 7
3
1 2 3
4 5 6
7 8 9
-1
```

## 输出格式

```
 
For each test case, print a line containing the minimum value of the maximum
of column sums.

Sample output
11
15
```

