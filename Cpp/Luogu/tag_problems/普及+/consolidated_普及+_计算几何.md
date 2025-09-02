---
title: "[NOIP 2001 提高组] Car 的旅行路线"
layout: "post"
diff: 普及+/提高
pid: P1027
tag: ['图论', '计算几何', '2001', 'NOIP 提高组', '最短路']
---
# [NOIP 2001 提高组] Car 的旅行路线
## 题目描述

又到暑假了，住在城市 A 的 Car 想和朋友一起去城市旅游。  
她知道每个城市都有 $4$ 个飞机场，分别位于一个矩形的 $4$ 个顶点上，同一个城市中两个机场之间有一条笔直的高速铁路，第 $i$ 个城市中高速铁路的单位里程价格为 $T_i$，任意两个不同城市的机场之间均有航线，所有航线单位里程的价格均为 $t$。


![](https://cdn.luogu.com.cn/upload/image_hosting/odqxn9sz.png)

**注意**：图中并没有标出所有的铁路与航线。


那么 Car 应如何安排到城市 B 的路线才能尽可能的节省花费呢？她发现这并不是一个简单的问题，于是她来向你请教。


找出一条从城市 A 到 B 的旅游路线，出发和到达城市中的机场可以任意选取，要求总的花费最少。

## 输入格式

第一行为一个正整数 $n$，表示有 $n$ 组测试数据。

每组的第一行有 $4$ 个正整数 $S,t,A,B$。

$S$ 表示城市的个数，$t$ 表示飞机单位里程的价格，$A$，$B$ 分别为城市A，B 的序号。

接下来有 $S$ 行，其中第 $i$ 行均有 $7$ 个正整数$x_{i1},y_{i1},x_{i2},y_{i2},x_{i3},y_{i3},T_i$，这当中的 $(x_{i1},y_{i1}), (x_{i2},y_{i2}), (x_{i3},y_{i3})$，分别是第 $i$ 个城市中任意 $3$ 个机场的坐标，$T_i$ 为第 $i$ 个城市高速铁路单位里程的价格。

## 输出格式

共有 $n$ 行，每行 $1$ 个数据对应测试数据。  
保留一位小数。

## 样例

### 样例输入 #1
```
1
3 10 1 3
1 1 1 3 3 1 30
2 5 7 4 5 2 1
8 6 8 8 11 6 3
```
### 样例输出 #1
```
47.5
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 10$，$1\le S \le 100$，$1\le A,B \le S$。

**【题目来源】**

NOIP 2001 提高组第四题


---

---
title: "[NOIP 2002 提高组] 矩形覆盖"
layout: "post"
diff: 普及+/提高
pid: P1034
tag: ['搜索', '计算几何', '2002', 'NOIP 提高组']
---
# [NOIP 2002 提高组] 矩形覆盖
## 题目描述

在平面上有 $n$ 个点，每个点用一对整数坐标表示。例如：当 $n=4$ 时，$4$ 个点的坐标分别为：$p_1(1,1)$，$p_2(2,2)$，$p_3(3,6)$，$p_4(0,7)$，见图一。

![](https://cdn.luogu.com.cn/upload/image_hosting/dxc1c5k9.png)

这些点可以用 $k$ 个矩形全部覆盖，矩形的边平行于坐标轴。当 $k=2$ 时，可用如图二的两个矩形 $s_1,s_2$ 覆盖，$s_1,s_2$ 面积和为 $4$。问题是当 $n$ 个点坐标和 $k$ 给出后，怎样才能使得覆盖所有点的 $k$ 个矩形的面积之和为最小呢？  
约定：覆盖一个点的矩形面积为 $0$；覆盖平行于坐标轴直线上点的矩形面积也为 $0$。各个矩形必须完全分开（边线与顶点也都不能重合）。

## 输入格式

第一行共两个整数 $n,k$，含义如题面所示。

接下来 $n$ 行，其中第 $i+1$ 行有两个整数 $x_i,y_i$，表示平面上第 $i$ 个点的坐标。

## 输出格式

共一行一个整数，为满足条件的最小的矩形面积之和。

## 样例

### 样例输入 #1
```
4 2
1 1
2 2
3 6
0 7

```
### 样例输出 #1
```
4
```
## 提示

对于 $100\%$ 数据，满足 $1\le n \le  50$，$1 \le k \le 4$，$0 \le x_i,y_i  \le 500$。

**【题目来源】**

NOIP 2002 提高组第四题


---

---
title: "[蓝桥杯 2025 省 A] 地雷阵"
layout: "post"
diff: 普及+/提高
pid: P12144
tag: ['贪心', '计算几何', '2025', '排序', '扫描线', '蓝桥杯省赛', '极角排序', '平面几何']
---
# [蓝桥杯 2025 省 A] 地雷阵
## 题目描述

小蓝正在平面直角坐标系中的第一象限里玩一个逃生小游戏。在第一象限中埋有 $n$ 颗地雷，第 $i$ 颗地雷的坐标为 $(x_i, y_i)$，触发范围为以 $(x_i, y_i)$ 为圆心，半径为 $r_i$ 的圆。一旦小蓝走进了圆内就会触发地雷导致游戏失败。小蓝初始在原点 $(0, 0)$ 上，他需要在第一象限内选择一个方向一直往前走，如果能不触发任何地雷即可成功通关游戏。他想知道在 $[0, \frac{\pi}{2}]$ 中均匀随机选择一个方向，即在 $0^\circ$（朝向 $x$ 轴正方向）至 $90^\circ$（朝向 $y$ 轴正方向）之间随机选择一个方向，通关游戏的概率是多少？
## 输入格式

输入的第一行包含一个正整数 $n$。

接下来 $n$ 行，每行包含三个正整数 $x_i, y_i, r_i$，相邻整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个实数，四舍五入保留三位小数，表示答案。
## 样例

### 样例输入 #1
```
1
2 2 1
```
### 样例输出 #1
```
0.540
```
### 样例输入 #2
```
2
1 3 1
3 1 1
```
### 样例输出 #2
```
0.181
```
## 提示

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n \leq 100$；
- 对于所有评测用例，$1 \leq n \leq 10^5$，$1 \leq x_i, y_i \leq 10^4$，$r_i < \min(x_i, y_i)$。


---

---
title: "[JSOI2004] 平衡点 / 吊打XXX"
layout: "post"
diff: 普及+/提高
pid: P1337
tag: ['计算几何', '2004', '二分', '各省省选', '江苏', '模拟退火']
---
# [JSOI2004] 平衡点 / 吊打XXX
## 题目描述

如图，有 $n$ 个重物，每个重物系在一条足够长的绳子上。

每条绳子自上而下穿过桌面上的洞，然后系在一起。图中 $x$ 处就是公共的绳结。假设绳子是完全弹性的（即不会造成能量损失），桌子足够高（重物不会垂到地上），且忽略所有的摩擦，求绳结 $x$ 最终平衡于何处。

**注意**：桌面上的洞都比绳结 $x$ 小得多，所以即使某个重物特别重，绳结 $x$ 也不可能穿过桌面上的洞掉下来，最多是卡在某个洞口处。

![](https://cdn.luogu.com.cn/upload/image_hosting/u20jvui9.png)
## 输入格式

文件的第一行为一个正整数 $n$（$1\le n\le 1000$），表示重物和洞的数目。

接下来的 $n$ 行，每行是 $3$ 个整数 $x_i, y_i, w_i$，分别表示第 $i$ 个洞的坐标以及第 $i$ 个重物的重量。（$-10000\le x_i,y_i\le10000, 0<w_i\le1000$）

## 输出格式

你的程序必须输出两个浮点数（保留小数点后三位），分别表示处于最终平衡状态时绳结 $x$ 的横坐标和纵坐标。两个数以一个空格隔开。
## 样例

### 样例输入 #1
```
3
0 0 1
0 2 1
1 1 1
```
### 样例输出 #1
```
0.577 1.000
```


---

---
title: "[GCJ 2011 #3] Irregular Cakes"
layout: "post"
diff: 普及+/提高
pid: P13378
tag: ['数学', '计算几何', '2011', '二分', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2011 #3] Irregular Cakes
## 题目描述

Mary the Mathematician has a bakery that she founded some years ago, but after all this time she has become bored with always baking the same rectangular and circular cakes. For her next birthday, she wants to bake an $irregular$ cake, which is defined as the area between two "polylines" between $x=0$ and $x=W$. These polylines will be called the lower boundary and the upper boundary.

![](https://cdn.luogu.com.cn/upload/image_hosting/khhniam4.png)

Formally, a polyline is defined by a sequence of points $(P_0, P_1, \ldots, P_n)$ going from left to right. Consecutive points are connected to form a sequence of line segments, which together make up the polyline.

Today is Mary's birthday and she has baked an irregular cake bounded by two polylines with $L$ points and $U$ points respectively. After singing "Happy Birthday," she wants to make $G-1$ vertical cuts to split the cake into $G$ slices with equal area. She can then share these cake slices with all her guests. However, the irregular cake shape makes this task pretty tricky. Can you help her decide where to make the cuts?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing four integers: $W$ (the cake's width), $L$ (the number of points on the lower boundary), $U$ (the number of points on the upper boundary) and $G$ (the number of guests at the party).

This is followed by $L$ lines specifying the lower boundary. The $i$-th line contains two integers $x_i$ and $y_i$, representing the coordinates of the $i$-th point on the lower boundary. This is followed by $U$ more lines specifying the upper boundary. The $j$-th line here contains two integers $x_j$ and $y_j$, representing the coordinates of the $j$-th point on the upper boundary.

## 输出格式

For each test case, output $G$ lines. The first line should be "Case #$x$: " where $x$ is the case number (starting from 1). The next $G-1$ lines should contain the $x$-coordinates at which cuts must be made, ordered from the leftmost cut to the rightmost cut.

Answers with a relative or absolute error of at most $10^{-6}$ will be considered correct.
## 样例

### 样例输入 #1
```
2
15 3 3 3
0 6
10 8
15 9
0 10
5 11
15 13
8 3 4 2
0 2
5 4
8 3
0 5
3 4
4 7
8 5
```
### 样例输出 #1
```
Case #1:
5.000000
10.000000
Case #2:
4.290588
```
## 提示

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq W \leq 1000$.
- $2 \leq L \leq 100$.
- $2 \leq U \leq 100$.
- All coordinates will be integers between -1000 and 1000, inclusive.
- The x-coordinate of the leftmost point of both boundaries will be 0.
- The x-coordinate of the rightmost point of both boundaries will be $W$.
- Points in the same boundary will be sorted increasingly by x-coordinate.
- Points in the same boundary will have different x-coordinates.
- The lower boundary will always be strictly below the upper boundary for all $x$ between 0 and $W$, inclusive. (In other words, the lower boundary will have a smaller y-coordinate than the upper boundary at every $x$ position.)

**Small dataset (Test set 1 - Visible)**

- $2 \leq G \leq 3$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (Test set 2 - Hidden)**

- $2 \leq G \leq 101$.
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[GCJ 2008 #2] Triangle Areas"
layout: "post"
diff: 普及+/提高
pid: P13467
tag: ['数学', '计算几何', '2008', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2008 #2] Triangle Areas
## 题目描述

Ten-year-old Tangor has just discovered how to compute the area of a triangle. Being a bright boy, he is amazed by how many different ways one can compute the area. He also convinced himself that, if all the points of the triangle have integer coordinates, then the triangle's area is always either an integer or half of an integer! Isn't that nice?

But today Tangor is trying to go in the opposite direction. Instead of taking a triangle and computing its area, he is taking an integer $A$ and trying to draw a triangle of area $A/2$. He restricts himself to using only the integer points on his graph paper for the triangle's vertices.

More precisely, the sheet of graph paper is divided into an $N$ by $M$ grid of square cells. The triangle's vertices may only be placed in the corners of those cells. If you imagine a coordinate system on the paper, then these points are of the form $(x, y)$, where $x$ and $y$ are integers such that $0 \leq x \leq N$ and $0 \leq y \leq M$.

Given the integer $A$, help Tangor find three integer points on the sheet of graph paper such that the area of the triangle formed by those points is exactly $A/2$, if that is possible. In case there is more than one way to do this, any solution will make him happy.

## 输入格式

One line containing an integer $C$, the number of test cases in the input file.

The next $C$ lines will each contain three integers $N$, $M$, and $A$, as described above.

## 输出格式

For each test case, output one line. If there is no way to satisfy the condition, output

Case #k: IMPOSSIBLE

where $k$ is the case number, starting from 1. Otherwise, output

Case #k: $x_1$ $y_1$ $x_2$ $y_2$ $x_3$ $y_3$

where $k$ is the case number and $(x_1, y_1)$, $(x_2, y_2)$, $(x_3, y_3)$ are any three integer points on the graph paper that form a triangle of area $A/2$.
## 样例

### 样例输入 #1
```
3
1 1 1
1 2 64
10 10 1
```
### 样例输出 #1
```
Case #1: 0 0 0 1 1 1
Case #2: IMPOSSIBLE
Case #3: 1 1 2 3 5 8
```
## 提示

**Limits**

- $0 \leq C \leq 1000$
- $1 \leq A \leq 10^8$

**Small dataset (5 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 50$
- $1 \leq M \leq 50$

**Large dataset (15 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 10000$
- $1 \leq M \leq 10000$



---

---
title: "房间最短路问题"
layout: "post"
diff: 普及+/提高
pid: P1354
tag: ['数学', '计算几何', '福建省历届夏令营']
---
# 房间最短路问题
## 题目描述

在一个长宽均为 $10$，入口、出口分别为 $(0,5)$、$(10,5)$ 的房间里，有几堵墙，每堵墙上有两个缺口，求入口到出口的最短路经。

![](https://cdn.luogu.com.cn/upload/image_hosting/i929rz3l.png)
## 输入格式

第一排为 $n$（$n \le 20$），墙的数目。

接下来 $n$ 排，每排 $5$ 个实数 $x,a_1,b_1,a_2,b_2$。

$x$ 表示墙的横坐标（所有墙都是竖直的），$a_1 \sim b_1$ 和 $a_2 \sim b_2$ 之间为空缺。

$a_1,b_1,a_2,b_2$ 保持递增，$x_1 \sim x_n$ 也是递增的。
## 输出格式

输出最短距离，保留 $2$ 位小数。
## 样例

### 样例输入 #1
```
2
4 2 7 8 9
7 3 4.5 6 7

```
### 样例输出 #1
```
10.06

```


---

---
title: "[NWERC 2024] Mouse Trap"
layout: "post"
diff: 普及+/提高
pid: P13751
tag: ['计算几何', '2024', 'Special Judge', '前缀和', '凸包', 'ICPC']
---
# [NWERC 2024] Mouse Trap
## 题目描述

Medea the cat is a real troublemaker.
Even though she is loving and caring with humans, sometimes she likes to crash on mouse parties in the field nearby her house, uninvited, just for the fun of it!


:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/zxffm682.png)

Medea with a mouse.

:::

A mouse party is a bunch of mice standing on the vertices of a convex polygon in the two-dimensional plane.
When Medea crashes a mouse party, she jumps, out of nowhere, to some point inside the party's polygon.
All the mice and Medea can be considered as points in the two-dimensional plane, meaning that they have no shape or dimensions.

Medea is still careful, however.
She considers how the mice might encircle her, so that she runs away before they get a chance to do so.
Medea defines an \textit{encirclement} as a subset of exactly three mice such that she lies strictly inside the triangle constructed with the mice as vertices.
An example can be seen in Figure M.1.

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/4rm403dp.png)

Figure M.1: Illustration of Sample Input 2, showing one of the three encirclements in the case where Medea jumps to $(1.4,1.4)$.

:::


One day, Medea decided to crash on a party of mice.
She does not jump accurately, so she does not know exactly which point inside the mouse party she is going to jump to -- all she knows is that she will jump to a uniformly random point with real coordinates inside the mouse party.

Medea wants to know the expected number of distinct encirclements after she lands inside the party.
This turned out to be too difficult to calculate, even for Medea's 200 IQ points, so she asked for your help!

## 输入格式

The input consists of:
- One line with an integer $n$ ($3 \leq n \leq 2\cdot 10^5$), the number of mice.
- $n$ lines, each with two integers $x$ and $y$ ($|x|, |y| \leq 10^7$), the coordinates of a mouse.

The coordinates of the mice are given in counterclockwise order and form a strictly convex polygon with non-zero area. A strictly convex polygon is a convex polygon such that no three consecutive vertices are on a straight line.
## 输出格式

Output the expected number of encirclements after Medea lands inside the polygon.

Your answer should have an absolute or relative error of at most $10^{-4}$.
## 样例

### 样例输入 #1
```
4
0 0
1 0
1 1
0 1
```
### 样例输出 #1
```
2.0
```
### 样例输入 #2
```
5
0 0
1 0
2 1
1 2
0 2
```
### 样例输出 #2
```
3.66666667
```
### 样例输入 #3
```
3
-3141592 -2718281
-3141593 -2718281
-3141592 -2718282
```
### 样例输出 #3
```
1.0
```


---

---
title: "[CERC 2021] Radar"
layout: "post"
diff: 普及+/提高
pid: P13770
tag: ['计算几何', '二分', '2021', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2021] Radar
## 题目描述

We are using a special radar to scan an area. The radar accepts a list of distances, e.g. 2, 4, 1, and a list of angles, e.g. $100^\circ$, $270^\circ$, $180^\circ$, $10^\circ$, $300^\circ$, and scans the points across all the given distances and angles. How close to some other points of interest will we be able to scan?
## 输入格式

The first line of the input gives three space-separated integers: $R$, $F$, $N$, representing the number of radii, the number of angles, and the number of points of interest, respectively. Then $R$ lines follow, $i$-th of which contains an integer $r_i$, representing the distance from the radar that will be scanned. Then, $F$ lines follow, each containing two space-separated integers $(f_x)_i$, $(f_y)_i$, that represent Cartesian coordinates of a point, defining the $i$-th angle. Then, $N$ lines follow, each containing two space-separated integers $x_i$, $y_i$, that represent the Cartesian coordinates of the $i$-th point.

The angle, defined by the point $(f_x)_i$, $(f_y)_i$ is the angle from the $x$-axis to the ray from the origin through $(f_x)_i$, $(f_y)_i$.
## 输出格式

Output $N$ lines, $i$-th of which should contain the distance from the point $(x_i, y_i)$ to the closest scanned point. The result will be considered correct if it is within the $10^{-6}$ of absolute or relative precision.
## 样例

### 样例输入 #1
```
3 7 5
2
4
7
8 4
2 8
-1 5
-7 2
-4 -4
1 -8
6 -3
3 -1
8 1
2 6
-5 2
-1 -1
```
### 样例输出 #1
```
0.977772290466
2.750120773895
0.846777708005
1.464071052924
0.585786437627
```
## 提示

### Comment

Illustration of sample case:

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/6rmdx4uq.png)
:::

### Input limits

* $1 \leq R, F, N \leq 10^5$
* $|x_i|, |y_i|, |(f_x)_i|, |(f_y)_i|, r_i < 10^6$
* $(f_x)_i^2 + (f_y)_i^2, r_i > 0$
* All $r_i$ are pairwise distinct.
* Rays, defined by $(f_x)_i, (f_y)_i$, are pairwise distinct.


---

---
title: "无线电测向"
layout: "post"
diff: 普及+/提高
pid: P2013
tag: ['计算几何']
---
# 无线电测向
## 题目描述

有天线定位装置的船能通过接收当地灯塔信号来确定自己的位置。每个灯塔固定在已知点上并发出特有的信号。当船检测到信号，它可通过旋转天线直到信号达到最大强度。这样就可确定自身与该灯塔的位置关系。只要接收到两个灯塔的信息，就有可能确定船当前的位置。

编程任务：通过一对灯塔信息来确定船的位置。

灯塔和船的位置被确定在一个直角坐标系内。$x$ 轴正向指向东，$y$ 轴正向指向北。船的航行路线从正北开始按顺时针用度表示。北是 $0^\circ$，东是 $90^\circ$，南是 $180^\circ$，西是 $270^\circ$。灯塔与船的位置关系用相对于船的航行方向顺时针用度表示。

## 输入格式

文件的第一行是一个整数，表示灯塔的数目 $N$。以下 $N$ 行，每行表示一个灯塔，为灯塔名称，$x$ 坐标和 $y$ 坐标。它们都用空格隔开。

灯塔信息下面是船的信息包括三行，一行是船的方向，其余两行是所接收到的灯塔信号。

具体如下：

| 输入数据 | 数据的含义|
| :-: | :-:|
| 方向 | 船的航行方向 |
| 名称 $1$，角度 $1$ | 第一个灯塔信息的名称，灯塔的方位 |
| 名称 $2$，角度 $2$ | 第二个灯塔信息的名称，灯塔的方位 |

灯塔的方位为船与灯塔所在的直线与船的航行方向的夹角（从船的航行方向开始顺时针）。$2$ 个数据用空格隔开。
## 输出格式

输出船的位置（精确到 $2$ 位小数）。如果无法确定船的位置，应输出 `NO ANSWER`（不能使用小写）。

## 样例

### 样例输入 #1
```
5
a 1 5
b 1 1000
c 2 4
d 51 60
e 153 79
30
e 160
d 210
```
### 样例输出 #1
```
160.83 123.41
```
## 提示

对于 $100 \%$ 的数据，$1 \le N \le 30$，灯塔名称是 $20$ 个以下的字母。



---

---
title: "物理1（phsic1）- 磁通量"
layout: "post"
diff: 普及+/提高
pid: P2785
tag: ['数学', '计算几何', '洛谷原创']
---
# 物理1（phsic1）- 磁通量
## 题目背景

蒟蒻 HansBug 在物理考场上，挠了无数次的头，可脑子里还是一片空白。
## 题目描述

眼下出现在 HansBug 蒟蒻面前的是一个奇怪的磁场，形状为多边形，可以描述为 $N$ 个点构成的序列，这些点即依次为该磁场的各个顶点。于是现在蒟蒻 HansBug 想要知道该磁场的磁通量为多少。可是他脑细胞和 RP 已经消耗殆尽，所以这个高端的任务就交给你们啦。
## 输入格式

第一行为一个整数 $N$ 和一个实数 $B$，$B$ 为磁感应强度。

第 $2\sim N+1$ 行，每行包含两个实数，表示该点的横纵坐标。
## 输出格式

一行，包含一个实数，即为磁通量（输出四舍五入保留四位小数）。
## 样例

### 样例输入 #1
```
3 1
0 0
1 0
0 2

```
### 样例输出 #1
```
1.0000
```
### 样例输入 #2
```
4 1
1 1
1 -1
-1 -1
-1 1

```
### 样例输出 #2
```
4.0000
```
## 提示

磁通量 $=$ 磁感应强度 $\times$ 磁场区域面积。

![](https://cdn.luogu.com.cn/upload/pic/2219.png)

$0\lt B\le 10$。


---

---
title: "偷上网"
layout: "post"
diff: 普及+/提高
pid: P4703
tag: ['计算几何', 'Special Judge', 'O2优化', '枚举', '向量', '洛谷月赛']
---
# 偷上网
## 题目描述

Alice 和 Bob 生活在一个 $l \times l$ 的正方形房子里，由于 Bob 最近沉迷隔膜，Alice 决定要限制 Bob 上网的频率。

Alice 建造了 $n$ 个无线信号屏蔽器，第 $i$ 个位于 $(x_i, y_i)$，屏蔽范围为 $\frac{l}{n}$。

Bob 网瘾发作按捺不住上网的冲动，找到了你，帮他找到一个位置 $(x, y)$，使得没有被 Alice 的无线信号屏蔽器覆盖。
## 输入格式

第一行两个整数 $n, l(1 \leq n \leq 10, 1 \leq l \leq 10^5)$，分别表示无线信号屏蔽器的个数和房子的大小。

接下来 $n$ 行，每行 $2$ 个数，分别是 $x_i, y_i(0 \leq x_i, y_i \leq l)$，意义如上所述。
## 输出格式

如果可以找到，输出两个数 $x, y(0 \leq x, y \leq l)$，意义如上所述，如果有多组解，输出任意一组即可。如果你输出的解满足到任意一个屏蔽器的距离都不小于 $\frac{l}{n} + 10^{-6}$，则视为正确。

否则输出 "GG"。
## 样例

### 样例输入 #1
```
1 1
0.000 0.000
```
### 样例输出 #1
```
0.999 0.999
```
### 样例输入 #2
```
1 2
1.000 1.000
```
### 样例输出 #2
```
GG
```
### 样例输入 #3
```
2 2
0.000 0.000
2.000 2.000
```
### 样例输出 #3
```
1.000 1.000
```


---

---
title: "[JLOI2010] 铁人双项比赛"
layout: "post"
diff: 普及+/提高
pid: P5485
tag: ['计算几何', '2010', '各省省选', '吉林']
---
# [JLOI2010] 铁人双项比赛
## 题目描述

铁人双项比赛是吉林教育学院的一项传统体育项目。该项目比赛由长跑和骑自行车组成，参赛选手必须先完成$k$公里的长跑，然后完成r公里的骑车，才能到达终点。每个参赛选手所擅长的项目不同，有的擅长长跑，有的擅长骑车。如果总赛程$s=k+r$一定，那么K越大，对擅长长跑的选手越有利；$k$越小，对擅长骑车的选手越有利。
 
现在给定总赛程$s$，以及每个选手长跑和骑车的平均速度，请你求出对于某个指定的选手最有利的k和r。所谓最有利，是指选择了这个$k$和$r$后，该选手可以获得冠军，且领先第$2$名尽量地多。
## 输入格式

你的程序从文件读入输入数据。
输入的第一行是两个正整数$s$和$n$，$s$表示总赛程（单位为公里，$s\leq 2^{31}$），$n$表示参赛总人数（$2\leq n\leq 100$）。
接下来的$n$行每行是两个实数，分别表示每个选手长跑的平均速度和骑车的平均速度（单位为千米/小时）。
第$n$个选手就是指定的选手，你的任务是求出对他最有利的$k$和$r$。
## 输出格式

你的程序的输出包括三个数$k,r,t$，分别表示对第$n$号选手最有利的$k$和$r$（浮点数，保留小数点后$2$位），以及在选择$k$和$r$的情况下，第$n$号选手最多可以领先第$2$名多少秒（四舍五入到整数）；如果另一个选手和该选手并列第一，则$t_i=0$。倘若无论选择什么$k$，$r$都不能使第$n$号选手获胜，则输出“$NO$”。
## 样例

### 样例输入 #1
```
100 3
10.0 40.0
20.0 30.0
15.0 35.0
```
### 样例输出 #1
```
14.29 85.71 612
```


---

---
title: "「Wdsr-2」方分"
layout: "post"
diff: 普及+/提高
pid: P6732
tag: ['计算几何', '2020', 'Special Judge', '枚举']
---
# 「Wdsr-2」方分
## 题目描述

平面直角坐标系上有两个相离的正方形 $A$ 和 $B$。请找到任意一条直线把它们分隔到直线的两侧。

**注意：这条直线不应该和正方形有公共点。**
## 输入格式

**输入包含多组数据**。

第一行输入一个正整数 $T$ ，代表数据组数。

对于每组数据，共有 $8$ 行，每行 $2$ 个实数，描述一个点的 $x$ 轴坐标和 $y$ 轴坐标。前四行表示正方形 $A$ 四个顶点的坐标，后四行表示正方形 $B$ 四个顶点的坐标。

保证这四个顶点坐标一定能构成一个正方形，但顺序可以是任意的。两个正方形一定是相离的。

**没有**保证正方形的边和坐标轴平行！
## 输出格式

对于每组数据，输出一行三个实数 $a,b,c$，表示你找到的直线方程是 $ax+by=c$。
## 样例

### 样例输入 #1
```
1
1.0 1.0
2.0 2.0
1.0 2.0
2.0 1.0
0.0 0.0
-0.5 -0.5
0.0 -1.0
0.5 -0.5
```
### 样例输出 #1
```
0.0 1.0 0.5
```
## 提示

$1\le T\le 10000$。

输入的坐标绝对值不超过 $10^3$，小数点后最多有 $3$ 位数字。

**SPJ 使用双精度浮点数计算验证你的答案，请尽可能地避免精度误差。**

避免精度误差的方式有：不要输出绝对值过大或过小的数字，输出尽可能多的小数点后位数，比较大小时使用 eps，等等。

赛后已加入 Hack 数据。


---

---
title: "「Wdsr-3」迷途竹林"
layout: "post"
diff: 普及+/提高
pid: P8008
tag: ['计算几何', 'Special Judge', 'O2优化', '线段相交', '差分']
---
# 「Wdsr-3」迷途竹林
## 题目背景

迷途竹林是生长着高耸入云的、无边无际的竹子的竹林。由于特殊地势的缘故，所有竹子都向着一侧倾斜生长。由于竹子顶部的叶片交错在一起，因此即使竹子的下端已经被砍掉，仍然会因为其他竹子的相互作用而无法掉落。

作为白玉楼的亭师，白玉楼的实际管家，魂魄妖梦时常需要收集一些竹子用于维修竹制家具以及竹楼。因为她拥有精湛的剑术，因此可以在瞬间砍伐一大片的竹子作为材料。当然，妖梦并不希望拥有过多的竹子。因此她会选择一个多边形区域进行采集。在那一瞬间，妖梦会用楼观剑顺着多边形的边进行砍伐。

不过，由于掉落下来的竹子数量实在太多，因此妖梦无暇统计砍下来的竹子。你能帮帮她吗？
## 题目描述

妖梦在迷途竹林里选定的竹子，可以看作在同一平面上。竹子可以看作有 $+\infty$ 根，每相邻两根竹子间距相等，并且每根竹子的倾斜程度相同。竹子的高度可以看作是无限高。

妖梦选定了一块多边形区域进行竹子的砍伐。**只有在多边形内的部分**才会被收集到。多边形共有 $n$ 条边，为了防止出现歧义，保证任意一条边都不和竹子平行；保证多边形是[简单多边形](https://baike.baidu.com/item/%E7%AE%80%E5%8D%95%E5%A4%9A%E8%BE%B9%E5%BD%A2/18891697)。

我们会使用两个实数 $\theta$ 和 $a$ 来描述这些竹子。这两个字母表示的含义可以参考下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7j0tx5xy.png)

现在妖梦需要知道她砍下来的竹子的总长度，也就是求出这些竹子（图中橙色的这些线段）的长度之和。
## 输入格式

- 第一行有一个正整数 $n$，表示多边形的边数。  
- 接下来 $n$ 行，将会**按照顺时针顺序**给出多边形的 $n$ 个顶点的坐标，第 $i$ 个点与第 $i+1$ 个点连接 $(1\le i<n)$，第 $n$ 个点与第 $1$ 个点连接。
- 接着给出描述线段的参数 $\theta$ 和 $a$。
## 输出格式

- 共一行，一个实数，表示所求得的竹子的总长。你的答案 $\mathit{ans}$ 被认为是正确的，当且仅当与标准答案 $\mathit{std}$ 满足 $\dfrac{|\mathit{ans}-\mathit{std}\ |}{\max(1.0,\mathit{std}\ )}\le 10^{-6}$。
## 样例

### 样例输入 #1
```
4
2.0000 2.0000
2.0000 -2.0000
-2.0000 -2.0000
-2.0000 2.0000
45.0000 1.0000
```
### 样例输出 #1
```
22.6274169980
```
### 样例输入 #2
```
8
0.0000 2.5000
1.0000 1.5000
2.5000 1.0000
2.0000 -1.0000
1.0000 -2.0000
-2.0000 -2.0000
-2.5000 1.0000
-1.0000 2.0000
60.0000 0.8000
```
### 样例输出 #2
```
23.1662217484
```
## 提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/ajm42r7v.png)

容易发现，竹子总长（即橘红色线段的总长度）为 $16\sqrt 2$。

#### 样例 2 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/anqb86a9.png)

我有一个精妙绝伦的方法解释样例 $2$，可惜这里空白太小写不下。

#### 数据范围及约定

$$
\def{\arraystretch}{1.5}
\begin{array}{|c|c|c|c|}\hline
\textbf{Subtask} & \bm{n\le} & \textbf{特殊性质} & \textbf{分值}\cr\hline
1 & 10 & \text{A} & 30 \cr\hline
2 & 10^3 & - & 20 \cr\hline
3 & 10^5 & \text{B} & 20 \cr\hline
4 & 10^5 & - & 30 \cr\hline
\end{array}
$$

**特殊性质** $\textbf{A}$：保证 $\theta\in[80,100);|x_i|,|y_i|\le 10$。  
**特殊性质** $\textbf{B}$：保证 $\theta=90$。

- 对于 $100\%$ 的数据，保证 $3\le n\le 10^5;|x_i|,|y_i|\le 10^4;\theta\in[1,179);\alpha\in[0.1,100]$。输入数据当中出现的浮点数均保留四位小数。


---

