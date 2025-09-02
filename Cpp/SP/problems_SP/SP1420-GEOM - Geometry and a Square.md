---
title: "GEOM - Geometry and a Square"
layout: "post"
diff: 难度0
pid: SP1420
tag: []
---

# GEOM - Geometry and a Square

## 题目描述

Is there anyone who doesn't love geometry?! Just imagine: on the plane you are given a square ABCD, with vertices given in the clockwise direction. Also given is a point P which is different from all of A, B, C or D. Have you imagined it? Interested? Ok, let's continue!  
  
 Through vertex A a line _a_ is drawn that is perpendicular to line BP, through vertex B a line _b_ is drawn that is perpendicular to line CP, through vertex C a line _c_ is drawn that is perpendicular to line DP, through vertex D a line _d_ is drawn that is perpendicular to line AP. Do the lines _a_, _b_, _c_ and _d_ cross each other in one point? Ok, it depends on what the square is and what point P is given. Write the program that discovers if these lines cross in one point, and if so, finds the coordinates of this point.

## 输入格式

In the first line you are given the integer coordinates of the point in which diagonals of the square intersect. In the second line you are given one integer - the length of the side of the square. In the third line you are given the integer coordinates of point P. The integers do not exceed 100, in terms of absolute value.

## 输出格式

For each test case you must output YES if the sought point exsists, and NO otherwise. If you answer YES then in the second line you must output the coordinates of the intersection point. Coordinates must be rounded to one digit after the point.

## 样例 #1

### 输入

```
10 10
20
5 12
```

### 输出

```
YES
8.0 5.0
```

