---
title: "BRDGS - Bridges"
layout: "post"
diff: 难度0
pid: SP10443
tag: []
---

# BRDGS - Bridges

## 题目描述

A new planet full of rivers was discovered and is being prepared for colonization. We want to connect every piece of land by bridges, the cost of building a bridge is its width.

## 输入格式

The first number in the input file is T < 200, the number of test cases. Each test case starts with a line with a integer, N <= 500, the number of rivers. N lines are followed with 5 integers each, Di1, Fi1, Di2, Fi2 and Wi <= 1000000, the coordinates of the extremities and the width of the i-th river. Every D is between -90 and 90, and every F is between 0 and 359, they are measured in degrees and correspond to the spherical coordinates (latitude and longitude respectively).  
The two extremities of a river can be seen from above in a distance less than infinite, a course of a river is always the smallest possible and two rivers intersect in at most 1 point.

## 输出格式

For each test case print a single line with "Case #X: C" where X is the number of the test case (starting from 1) and C is the minimum cost to build the bridges so the islands and continents are connected directly or indirectly to each other.

## 样例 #1

### 输入

```
\n\n3\n4\n0 0 90 0 4\n90 0 0 179 2\n0 0 -90 0 1\n-90 0 0 179 1\n6\n0 0 10 90 3\n0 0 -20 90 3\n0 179 10 90 5\n0 179 -20 90 1\n0 0 0 179 10\n-20 90 20 90 1\n1\n0 2 0 3 1
```

### 输出

```
\nCase #1: 1\nCase #2: 6\nCase #3: 0
```

