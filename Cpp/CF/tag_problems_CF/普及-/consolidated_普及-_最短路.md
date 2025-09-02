---
title: "Shortest path of the king"
layout: "post"
diff: 普及-
pid: CF3A
tag: ['模拟', '贪心', '最短路']
---

# Shortest path of the king

## 题目描述

国王独自一人在国际象棋棋盘上。尽管他很孤独，但他并不会灰心，因为他有国家大事要做。例如，他必须对方格 $t$ 进行访问。因为国王没有浪费时间的习惯，所以他想从目前的位置（方格 $s$）上出发，走最少的步数。请你帮他做这件事。

在一次移动中，国王可以到达与他目前所在方格有共同的边或共同的顶点的方格里（通常情况下，他可以移动到 $8$ 个不同的方格里）。

## 输入格式

第一行包含方格 $s$ 的棋盘坐标，第二行包含方格 $t$ 的棋盘坐标。

棋盘坐标由两个字符组成，第一个是从 `a` 到 `h` 的小写拉丁字母，第二个是从 `1` 到 `8` 的数字。具体情况如上图所示。

## 输出格式

在第一行输出 $n$——国王移动的最小步数。然后接下来 $n$ 行输出移动的每一步。每次移动用 `L`、`R`、`U`、`D`、`LU`、`LD`、`RU` 或 `RD` 中的一个来描述。

`L`、`R`、`U`、`D` 分别指向左、向右、向上和向下移动，两个字母的组合代表沿着对角线移动（如 `RU` 代表向右上方移动）。如果答案不唯一，请输出任意一个答案。

## 样例 #1

### 输入

```
a8
h1

```

### 输出

```
7
RD
RD
RD
RD
RD
RD
RD

```



---

---
title: "Obsession with Robots"
layout: "post"
diff: 普及-
pid: CF8B
tag: ['广度优先搜索 BFS', '最短路']
---

# Obsession with Robots

## 题目描述

The whole world got obsessed with robots,and to keep pace with the progress, great Berland's programmer Draude decided to build his own robot. He was working hard at the robot. He taught it to walk the shortest path from one point to another, to record all its movements, but like in many Draude's programs, there was a bug — the robot didn't always walk the shortest path. Fortunately, the robot recorded its own movements correctly. Now Draude wants to find out when his robot functions wrong. Heh, if Draude only remembered the map of the field, where he tested the robot, he would easily say if the robot walked in the right direction or not. But the field map was lost never to be found, that's why he asks you to find out if there exist at least one map, where the path recorded by the robot is the shortest.

The map is an infinite checkered field, where each square is either empty, or contains an obstruction. It is also known that the robot never tries to run into the obstruction. By the recorded robot's movements find out if there exist at least one such map, that it is possible to choose for the robot a starting square (the starting square should be empty) such that when the robot moves from this square its movements coincide with the recorded ones (the robot doesn't run into anything, moving along empty squares only), and the path from the starting square to the end one is the shortest.

In one movement the robot can move into the square (providing there are no obstrutions in this square) that has common sides with the square the robot is currently in.

## 输入格式

The first line of the input file contains the recording of the robot's movements. This recording is a non-empty string, consisting of uppercase Latin letters L, R, U and D, standing for movements left, right, up and down respectively. The length of the string does not exceed 100.

## 输出格式

In the first line output the only word OK (if the above described map exists), or BUG (if such a map does not exist).

## 样例 #1

### 输入

```
LLUUUR

```

### 输出

```
OK

```

## 样例 #2

### 输入

```
RRUULLDD

```

### 输出

```
BUG

```



---

---
title: "The Way to Home"
layout: "post"
diff: 普及-
pid: CF910A
tag: ['图论', '最短路']
---

# The Way to Home

## 题目描述

一只青蛙现在在一个数轴上，它现在要从点 $1$ 跳到点 $n$ ，它每次可以向右跳不超过 $d$ 个单位。比如，它可以从点 $x$ 跳到点 $x+a$  $( 1<=a<=d )$ 。特别的，青蛙只能在有百合花的点上停留。保证点 $1$ 和点 $n$ 之间有一些点有百合花。请输出青蛙到达点 $n$ 的最小跳跃次数。

## 输入格式

输入的第一行包括两个正整数 $n$ 和 $d$  $( 2<=n<=100, 1<=d<=n-1 )$ 。
输入的第二行是一个长度为 $n$ 的无空格字符串，由`0`和`1`组成，表示哪些点上有百合花（`1`表示有）。保证点 $1$ 和点 $n$ 有百合花。

## 输出格式

输出青蛙的最小跳跃次数。如果它不可能到达，输出-1。

## 输入输出样例
略

## 说明/提示

在样例1中，青蛙可以从点 $1$ 跳3个单位到点 $4$ ，再从点 $4$ 跳4个单位到点 $8$ .
在样例2中，青蛙不能到达点 $n$ ，因为它至少需要跳3个单位，但它最多只能跳2个单位。

由 @星烁晶熠辉 提供翻译

## 样例 #1

### 输入

```
8 4
10010101

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 2
1001

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
8 4
11100101

```

### 输出

```
3

```

## 样例 #4

### 输入

```
12 3
101111100101

```

### 输出

```
4

```



---

