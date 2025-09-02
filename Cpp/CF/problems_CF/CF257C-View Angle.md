---
title: "View Angle"
layout: "post"
diff: 普及+/提高
pid: CF257C
tag: []
---

# View Angle

## 题目描述

Flatland has recently introduced a new type of an eye check for the driver's licence. The check goes like that: there is a plane with mannequins standing on it. You should tell the value of the minimum angle with the vertex at the origin of coordinates and with all mannequins standing inside or on the boarder of this angle.

As you spend lots of time "glued to the screen", your vision is impaired. So you have to write a program that will pass the check for you.

## 输入格式

The first line contains a single integer $ n\ (1<=n<=10^{5}) $ — the number of mannequins.

Next $ n $ lines contain two space-separated integers each: $ x_{i},y_{i}\ (|x_{i}|,|y_{i}|<=1000) $ — the coordinates of the $ i $ -th mannequin. It is guaranteed that the origin of the coordinates has no mannequin. It is guaranteed that no two mannequins are located in the same point on the plane.

## 输出格式

Print a single real number — the value of the sought angle in degrees. The answer will be considered valid if the relative or absolute error doesn't exceed $ 10^{-6} $ .

## 说明/提示

Solution for the first sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/52a22a58227cc8e3cd175061056d878bb5e11b91.png)Solution for the second sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/ec228a55fc379b89df62107b0fadfa9651c34033.png)Solution for the third sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/477a3f097accae6f2425e7d37a546ed3af1f9885.png)Solution for the fourth sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/8ce489535c5d9f609dbb5be22269ebed1502e2d2.png)

## 样例 #1

### 输入

```
2
2 0
0 2

```

### 输出

```
90.0000000000

```

## 样例 #2

### 输入

```
3
2 0
0 2
-2 2

```

### 输出

```
135.0000000000

```

## 样例 #3

### 输入

```
4
2 0
0 2
-2 0
0 -2

```

### 输出

```
270.0000000000

```

## 样例 #4

### 输入

```
2
2 1
1 2

```

### 输出

```
36.8698976458

```

