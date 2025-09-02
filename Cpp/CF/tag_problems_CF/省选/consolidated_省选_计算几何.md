---
title: "Satanic Panic"
layout: "post"
diff: 省选/NOI-
pid: CF1146H
tag: ['动态规划 DP', '计算几何', '区间 DP']
---

# Satanic Panic

## 题目描述

You are given a set of $ n $ points in a 2D plane. No three points are collinear.

A pentagram is a set of $ 5 $ points $ A,B,C,D,E $ that can be arranged as follows. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/f942ae06c7e29cb9bc6462315be09bb7d5b4c362.png) Note the length of the line segments don't matter, only that those particular intersections exist.

Count the number of ways to choose $ 5 $ points from the given set that form a pentagram.

## 输入格式

The first line contains an integer $ n $ ( $ 5 \leq n \leq 300 $ ) — the number of points.

Each of the next $ n $ lines contains two integers $ x_i, y_i $ ( $ -10^6 \leq x_i,y_i \leq 10^6 $ ) — the coordinates of the $ i $ -th point. It is guaranteed that no three points are collinear.

## 输出格式

Print a single integer, the number of sets of $ 5 $ points that form a pentagram.

## 说明/提示

A picture of the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/ecb5db206846ce3b41c177fcaeaebe0ee2b1bb2a.png) A picture of the second sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/4f7f38f01a0904403461b302f8dc7d443ccc0e93.png) A picture of the third sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146H/d922b8e812b7b67b3a0bbbb474a47be87ee53781.png)

## 样例 #1

### 输入

```
5
0 0
0 2
2 0
2 2
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
0 0
4 0
0 4
4 4
2 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
10
841746 527518
595261 331297
-946901 129987
670374 -140388
-684770 309555
-302589 415564
-387435 613331
-624940 -95922
945847 -199224
24636 -565799

```

### 输出

```
85

```



---

---
title: "Spaceship Exploration"
layout: "post"
diff: 省选/NOI-
pid: CF1906D
tag: ['计算几何', '凸包']
---

# Spaceship Exploration

## 题目描述

In The ICPC Galaxy, there exists a zone filled with asteroids that is unsafe to enter. The map of the galaxy is represented in a 2D Cartesian coordinate system. The zone is in the shape of an $ N $ -sided convex polygon. Each corner is numbered from $ 1 $ to $ N $ ; corner $ i $ is located at $ (X_i, Y_i) $ . At any moment, you should not be inside this polygon; however, it is safe to touch the side of the polygon.

There are $ Q $ scenarios (numbered from $ 1 $ to $ Q $ ). In scenario $ j $ , you want to go from a starting point at $ (A_j, B_j) $ to an ending point at $ (C_j, D_j) $ . You will be riding on a special spaceship that can only travel in a straight line. First, you set the direction of the spaceship, then the spaceship will start traveling in that direction. During the travel, you are only allowed to change direction at most once. Changing direction means you stop the spaceship, set a new direction, and then start traveling again in the new direction.

For each scenario, determine the minimum distance required to travel without being inside of the zone at any moment, or report if it is impossible to reach the ending point.

## 输入格式

The first line consists of an integer $ N $ ( $ 3 \leq N \leq 100\,000 $ ).

Each of the next $ N $ lines consists of two integers $ X_i $ $ Y_i $ ( $ -10^9 \leq X_i, Y_i \leq 10^9 $ ). The points form a convex polygon in counterclockwise order. There are no three points which are collinear.

The following line consists of an integer $ Q $ ( $ 1 \leq Q \leq 100\,000 $ ).

Each of the next $ Q $ lines consists of four integers $ A_j $ $ B_j $ $ C_j $ $ D_j $ ( $ -10^9 \leq A_j, B_j, C_j, D_j \leq 10^9 $ ). There are no starting points and ending points inside the zone. However, it is possible for the starting point and the ending point to be at the side of the zone.

All the coordinates in the input are integers.

## 输出格式

For each scenario, output the answer in a single line.

If it is possible to reach the ending point without being inside the zone at any moment, then output the minimum distance required to travel. Otherwise, output -1.

Your answer is considered correct if its absolute error or relative error does not exceed $ 10^{-6} $ . Namely, if your answer is $ a $ and the jury's answer is $ b $ , then your answer is accepted if $ \frac{|a - b|}{\max(1, |b|)} \leq 10^{-6} $ .

## 说明/提示

Explanation for the sample input/output #1

This sample is depicted in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906D/3b577bd1075a31373238167ad213c432f7146baa.png)During scenario $ 1 $ and $ 4 $ , you can directly go to the ending point without changing the direction.

During scenario $ 2 $ , you can go to $ (0, 2) $ , then change direction to the ending point.

During scenario $ 3 $ , you can go to $ (6, 2) $ , then change direction to the ending point.

During scenario $ 5 $ , it can be shown that it is impossible to reach the ending point.

## 样例 #1

### 输入

```
5
0 2
2 0
4 0
4 4
2 4
5
6 1 6 3
2 5 0 0
3 5 3 -1
1 4 5 4
3 4 3 0
```

### 输出

```
2
5.6055512755
8.48528137422
4
-1
```

## 样例 #2

### 输入

```
4
-10 -9
10 -9
10 9
-10 9
2
0 10 0 -10
-10 -10 -10 -10
```

### 输出

```
200.9975124224
0
```

## 样例 #3

### 输入

```
8
-20 -10
10 -20
25 -15
35 -5
30 10
15 20
-25 15
-30 5
6
-15 -15 -15 20
-30 -5 30 15
25 20 -5 -20
-5 25 20 -20
-30 10 30 -10
-30 -50 50 0
```

### 输出

```
59.0857761929
103.2455532034
94.7213595500
101.5640991922
164.8528137424
94.3398113206
```



---

---
title: "Building Castle"
layout: "post"
diff: 省选/NOI-
pid: CF2041L
tag: ['计算几何', '半平面交']
---

# Building Castle

## 题目描述

A-Ju 拥有一座美丽的城堡，她经常在其中生活。然而，长时间住在城堡让她感到无聊，所以她想将城堡重建为更漂亮的形状。

在二维平面上，我们用一个凸多边形来表示 A-Ju 的城堡。现在，她希望将城堡改造成一个具有点对称性质的凸多边形。所谓的点对称多边形，指的是存在某个中心点 $c$，使得多边形中任意一个点 $p$，其关于 $c$ 的对称点 $p^\prime$ 也在这个多边形内。

虽然设计一个点对称凸多边形并不难，但重建的花费却是非常大的。根据估算，重建的成本与原城堡和新形状之间的对称差集的面积有关。请参见下面的图示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041L/cc81c15b80e191d8f11f35ce9dd6d735fd831b60.png)

在上面的例子中，A-Ju 的城堡是由点 $(3, 7) - (2, 1) - (6, 3)$ 组成的凸多边形。经过重建，新的城堡变成由点 $(3, 7) - (\frac{7}{3}, 3) - (\frac{13}{3}, \frac{1}{3}) - (5, \frac{13}{3})$ 构成的多边形。这两个形状之间的对称差集的面积为 $\frac{11}{3}$。这个面积包含了新增的区域（绿色网格表示）以及被削减的区域（红色线条表示）。

请设计一个程序，帮助 A-Ju 规划新的城堡形状，使得原城堡与新城堡之间的对称差集面积达到最小。你只需要输出这个最小面积值，因为 A-Ju 需要先估算一下潜在的改造成本。

## 输入格式

第一行输入一个整数 $n$，表示组成 A-Ju 城堡的多边形的顶点数。

接下来有 $n$ 行，每行包含两个整数 $x_i, y_i$，表示第 $i$ 个顶点的坐标。顶点按逆时针顺序给出。

- $3 \leq n \leq 500$
- $|x_i|, |y_i| \leq 10^4$
- 顶点按逆时针顺序给出，并保证形成一个没有三点共线的凸多边形。

## 输出格式

输出一个实数，该数表示原城堡与新城堡之间对称差集的最小面积。

你的答案将被接受，如果其绝对误差或相对误差不超过 $10^{-4}$。具体来说，设你的答案为 $a$，标准答案为 $b$，则你的回答被视为正确，当 $\frac{|a-b|}{\max(1,|b|)} \le 10^{-4}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2 1
6 3
3 7
```

### 输出

```
3.666666666667
```

## 样例 #2

### 输入

```
4
0 0
5 0
5 5
0 5
```

### 输出

```
0.000000000000
```



---

---
title: "Cut Length"
layout: "post"
diff: 省选/NOI-
pid: CF598F
tag: ['计算几何']
---

# Cut Length

## 题目描述

Given simple (without self-intersections) $ n $ -gon. It is not necessary convex. Also you are given $ m $ lines. For each line find the length of common part of the line and the $ n $ -gon.

The boundary of $ n $ -gon belongs to polygon. It is possible that $ n $ -gon contains 180-degree angles.

## 输入格式

The first line contains integers $ n $ and $ m $ ( $ 3<=n<=1000;1<=m<=100 $ ). The following $ n $ lines contain coordinates of polygon vertices (in clockwise or counterclockwise direction). All vertices are distinct.

The following $ m $ lines contain line descriptions. Each of them contains two distict points of a line by their coordinates.

All given in the input coordinates are real numbers, given with at most two digits after decimal point. They do not exceed $ 10^{5} $ by absolute values.

## 输出格式

Print $ m $ lines, the $ i $ -th line should contain the length of common part of the given $ n $ -gon and the $ i $ -th line. The answer will be considered correct if the absolute or relative error doesn't exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
4 3
0 0
1 0
1 1
0 1
0 0 1 1
0 0 0 1
0 0 1 -1

```

### 输出

```
1.41421356237309514547
1.00000000000000000000
0.00000000000000000000

```



---

---
title: "Professor's task"
layout: "post"
diff: 省选/NOI-
pid: CF70D
tag: ['计算几何', '排序', '凸包', '叉积']
---

# Professor's task

## 题目描述

Once a walrus professor Plato asked his programming students to perform the following practical task.

The students had to implement such a data structure that would support a convex hull on some set of points $ S $ . The input to the program had $ q $ queries of two types:

1\. Add a point with coordinates $ (x,y) $ into the set $ S $ . Note that in this case the convex hull of $ S $ could have changed, and could have remained the same.

2\. Say whether a point with coordinates $ (x,y) $ belongs to an area limited by the convex hull, including the border.

All the students coped with the task. What about you?

## 输入格式

The first line contains an integer $ q $ ( $ 4<=q<=10^{5} $ ).

Then follow $ q $ lines in the following way: " $ t $ $ x $ $ y $ ", where $ t $ is the query type (1 or 2), and $ (x,y) $ are the coordinates of the point ( $ -10^{6}<=x,y<=10^{6} $ , $ x $ and $ y $ are integers).

There is at least one query of type 2.

It is guaranteed that the three queries of the first type follow first and the points given in the queries form a non-degenerative triangle. Also all the points added in $ S $ are distinct.

## 输出格式

For each query of the second type print one string containing "YES", if the point lies inside the convex hull or on its border. Otherwise, print "NO".

## 样例 #1

### 输入

```
8
1 0 0
1 2 0
1 2 2
2 1 0
1 0 2
2 1 1
2 2 1
2 20 -1

```

### 输出

```
YES
YES
YES
NO

```



---

