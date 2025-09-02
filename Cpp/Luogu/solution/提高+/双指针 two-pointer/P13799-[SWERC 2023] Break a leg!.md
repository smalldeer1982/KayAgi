# [SWERC 2023] Break a leg!

## 题目描述

:::align{center}

![](https://espresso.codeforces.com/a2628cf785edc53f8245d1203533bdfe5a5f491a.png)

:::

For the first time, breakdance will be featured in the Olympics. And you get to participate! Well, you get to participate to the jury... More precisely, you get to build the table in front of which the jury will be seated: still, that is an impressive feat, congratulations!


Actually, the top of the table is already built: it is plane, has constant width and constant density, and its shape consists in the interior of an $N$-sided non-crossing polygon $P_1 P_2 \dots P_N$ in which no three vertices are collinear (i.e., no line goes through three vertices or more). You have three table legs of same length and negligible width. Your task is to place them at distinct corners of the table so that the table remains stable when standing on these legs. In other words, you must choose three vertices $P_i$, $P_j$ and $P_k$ of the polygon such that the centre of gravity of the polygon lies in the interior of the triangle $P_i P_j P_k$ (and not on its boundary).


In how many different ways can you do this? If two ways of placing legs differ only by a permutation
of the legs, they are not counted as different ways.

## 样例 #1

### 输入

```
4
0 0
1 0
1 1
0 1```

### 输出

```
0```

## 样例 #2

### 输入

```
4
0 0
5 0
6 6
0 5```

### 输出

```
1```

## 样例 #3

### 输入

```
5
0 0
2 0
2 20
1 1
0 20```

### 输出

```
5```

