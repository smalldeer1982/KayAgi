---
title: "The Closest Pair"
layout: "post"
diff: 普及/提高-
pid: CF311A
tag: []
---

# The Closest Pair

## 题目描述

Currently Tiny is learning Computational Geometry. When trying to solve a problem called "The Closest Pair Of Points In The Plane", he found that a code which gave a wrong time complexity got Accepted instead of Time Limit Exceeded.

The problem is the follows. Given $ n $ points in the plane, find a pair of points between which the distance is minimized. Distance between $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF311A/22fd88ba9a7f84161b680cf39a97d9a06bc287ba.png).

The pseudo code of the unexpected code is as follows:

`<br></br>input n<br></br>for i from 1 to n<br></br>    input the i-th point's coordinates into p[i]<br></br>sort array p[] by increasing of x coordinate first and increasing of y coordinate second<br></br>d=INF        //here INF is a number big enough<br></br>tot=0<br></br>for i from 1 to n<br></br>    for j from (i+1) to n<br></br>        ++tot<br></br>        if (p[j].x-p[i].x>=d) then break    //notice that "break" is only to be<br></br>                                            //out of the loop "for j"<br></br>        d=min(d,distance(p[i],p[j]))<br></br>output d<br></br>`Here, $ tot $ can be regarded as the running time of the code. Due to the fact that a computer can only run a limited number of operations per second, $ tot $ should not be more than $ k $ in order not to get Time Limit Exceeded.

You are a great hacker. Would you please help Tiny generate a test data and let the code get Time Limit Exceeded?

## 输入格式

A single line which contains two space-separated integers $ n $ and $ k $ ( $ 2<=n<=2000 $ , $ 1<=k<=10^{9} $ ).

## 输出格式

If there doesn't exist such a data which let the given code get TLE, print "no solution" (without quotes); else print $ n $ lines, and the $ i $ -th line contains two integers $ x_{i},y_{i} $ $ (|x_{i}|,|y_{i}|<=10^{9}) $ representing the coordinates of the $ i $ -th point.

The conditions below must be held:

- All the points must be distinct.
- $ |x_{i}|,|y_{i}|<=10^{9} $ .
- After running the given code, the value of $ tot $ should be larger than $ k $ .

## 样例 #1

### 输入

```
4 3

```

### 输出

```
0 0
0 1
1 0
1 1

```

## 样例 #2

### 输入

```
2 100

```

### 输出

```
no solution

```

