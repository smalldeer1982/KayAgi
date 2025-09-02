---
title: "BZOJ1278 向量 vector"
layout: "post"
diff: 省选/NOI-
pid: P10671
tag: ['计算几何', 'O2优化', '随机化']
---
# BZOJ1278 向量 vector
## 题目描述

一个二维向量 $(x,y)$ 的权定义为 $x^2+y^2$。已知一个由 $n$ 个二维向量组成的集合，求该集合的一个子集，使该子集中的向量和的权尽可能大。
## 输入格式

第 $1$ 行一个正整数 $n$，表示 $n$ 个向量。

下面 $n$ 行，每行 $2$ 个实数，表示 $n$ 个向量 $(x_i,y_i)$。
## 输出格式

输出 $1$ 个实数，即向量和最大的权，精确到小数点后 $3$ 位。
## 样例

### 样例输入 #1
```
3
1 1
1 0
0 -1
```
### 样例输出 #1
```
5.000
```
## 提示

数据保证，$1\leq n\leq 100000$。


---

---
title: "[Code+#6] 进阶法师"
layout: "post"
diff: 省选/NOI-
pid: P11441
tag: ['计算几何', 'Special Judge', '凸包', '叉积', '旋转卡壳', 'Code+']
---
# [Code+#6] 进阶法师
## 题目背景

搬运自 [Code+ 第 6 次网络赛](https://gitlink.org.cn/thusaa/codeplus6/)。
## 题目描述

传说在 $100000$ 年后，又有大量陨石即将撞击企鹅大陆。散布在企鹅大陆各个地点的进阶企鹅法师们张开法阵保护企鹅大陆。

法师站在一些固定的点，如果一个点与某两个法师连线形成的夹角大于等于 $90$ 度，那么这个点可以免于灾害。

每个法师的坐标可以使用一组非负整数 $\left(X, Y\right)$ 表示。不存在两个法师在同一个位置。

一想到这里，企鹅豆豆又想到一个问题——能被保护的区域的面积有大？
## 输入格式

输入的第一行包含一个正整数 $n$，表示法师人数，保证 $2 \le n \le 10^5$。

接下来 $n$ 行每行两个非负整数，表示一位法师的坐标位置。保证数值不超过 $10^9$。
## 输出格式

输出一个小数，表示被保护的区域的面积。如果你的输出与标算的答案的相对误差不超过 $10^{-7}$ 即被认为是正确的。
## 样例

### 样例输入 #1
```
2
0 0
0 2
```
### 样例输出 #1
```
3.14159265358979326666666666666233333333
```
### 样例输入 #2
```
3
0 1
3 0
2 2
```
### 样例输出 #2
```
10.353981582
```
## 提示

### 样例解释

**【样例 1】**

对于样例一，显然被保护面积是以这两点连线作为直径的圆形。根据圆的面积计算公式即可得出答案。而且你与标算的相对误差不超过 $10^{-7}$ 即被认为正确。

**【样例 3】**

见题目目录下的 `3.in` 与 `3.ans`。

### 数据范围

保证 $2 \le n \le 10^5$，$0\le X,Y\le 10^9$。


---

---
title: "三角形"
layout: "post"
diff: 省选/NOI-
pid: P1222
tag: ['计算几何']
---
# 三角形
## 题目描述

给出平面上的 $n$ 个等腰直角三角形。每个三角形用三个整数 $x,y,m$ 描述。一个三角形的三个顶点分别是 $(x,y),(x+m,y),(x,y+m)$。

你的任务是计算这些三角形覆盖的总面积。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行每行描述一个三角形，包括三个整数 $x_i,y_i,m_i$。
## 输出格式

输出文件仅包含一个实数，精确到小数点后一位，表示总面积。

## 样例

### 样例输入 #1
```
5
-5 -3 6
-1 -2 3
0 0 2
-2 2 1
-4 -1 2

```
### 样例输出 #1
```
24.5
```
## 提示

样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/5ti25vl7.png)

数据范围：$1\le n \le 2000$，$1 \le i \le n$，$-10^7 \le x_i,y_i \le 10^7$，$1\leq m_i \le 1000$。


---

---
title: "[ICPC 2022/2023 WF] Carl’s Vacation"
layout: "post"
diff: 省选/NOI-
pid: P12298
tag: ['计算几何', '2022', '2023', '三分', 'Special Judge', 'ICPC']
---
# [ICPC 2022/2023 WF] Carl’s Vacation
## 题目描述

Carl the ant is back! After traversing meandering paths (Problem A, 2004 World Finals) and wandering over octahedrons (Problem C, 2009 World Finals) it is time for a little vacation — time to see the sights! And where better to see the sights than at the tips of tall structures like, say, pyramids!! And where better to see tall pyramids but Egypt!!! (This is so exciting!!!!!)

After taking in the view from the tip of one pyramid, Carl would like to go to the tip of another. Since ants do not do particularly well in the hot sun, he wants to find the minimum distance to travel between the tips of these two pyramids, assuming he can only walk on the surfaces of the pyramids and the plane which the pyramids sit upon. The pyramids are, geometrically, right square pyramids, meaning the apex of the pyramid lies directly above the center of a square base.

![](https://cdn.luogu.com.cn/upload/image_hosting/t5j6zy9j.png)

Illustration of two pyramids corresponding to Sample Input 1. The black line shows the shortest path between their apexes.
## 输入格式

The first line of input contains five integers $x_1, y_1, x_2, y_2, h$ where $x_1, y_1, x_2, y_2$ ($-10^5 \le x_1, x_2, y_1, y_2 \le 10^5$ and $(x_1, y_1) \neq (x_2, y_2)$) define an edge of the first pyramid, with the body of the pyramid lying to the left of the directed vector from $(x_1, y_1)$ to $(x_2, y_2)$, and $h$ ($1 \le h \le 10^5$) is the height of the pyramid. The second line of input describes the second pyramid in the same format. The intersection of the bases of the two pyramids has $0$ area.
## 输出格式

Output the minimum distance Carl travels between the tips of the two pyramids. Your answer should have an absolute or relative error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
0 0 10 0 4
9 18 34 26 42

```
### 样例输出 #1
```
60.866649532

```


---

---
title: "[POI 2018 R3] 围栏 Fence"
layout: "post"
diff: 省选/NOI-
pid: P12767
tag: ['动态规划 DP', '计算几何', '2018', 'POI（波兰）']
---
# [POI 2018 R3] 围栏 Fence
## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5075)。
## 题目描述

**题目译自 [XXV Olimpiada Informatyczna — III etap](https://sio2.mimuw.edu.pl/c/oi25-3/dashboard/) [Ogrodzenie](https://szkopul.edu.pl/problemset/problem/guoc36QCEe4q47qruYB7HBV-/statement/)**

农夫 Bajtazar 刚购置了一块土地，上面生长着 $n$ 株植物。其中一些是果树，每年带来非负收益（果实价值不等）；另一些是杂草，只会造成损失（占用空间和阳光）。

Bajtazar 为每株植物估算了留下它的收益或损失。然而，拜托尼亚禁止破坏自然，他无法随意移除带来损失的植物。幸好，他需为土地建围栏，于是突发奇想：何必围住整块土地？只围住收益最大的部分即可！

Bajtazar 请你帮忙设计最优围栏。围栏需经济高效：他将选择部分植物，用弹性网固定于其上，围成的区域必须是面积大于 $0$ 的凸多边形。请帮助 Bajtazar 挑选支撑网的植物，最大化围栏内植物的收益总和。
## 输入格式

第一行包含一个整数 $n$ $(n \geq 3)$，表示土地上植物数量。

接下来的 $n$ 行描述各植物，第 $i$ 行包含三个整数 $x_i, y_i, v_i$ $(-10^9 \leq x_i, y_i \leq 10^9, -10^9 \leq v_i \leq 10^9)$，分别表示第 $i$ 株植物在直角坐标系中的位置 $(x_i, y_i)$ 及其收益（若 $v_i$ 为负则为损失）。保证任意三株植物不在同一直线上。
## 输出格式

输出一行，包含一个整数，表示围栏内植物可实现的最大收益总和。
## 样例

### 样例输入 #1
```
6
0 0 1
0 4 1
4 0 1
4 4 1
1 2 -1
2 6 -5
```
### 样例输出 #1
```
3
```
## 提示

**样例 1 解释**

图示展示了一种最大收益为 $3$ 的围栏设置。另一种同样最优的方案是固定网于点 $(0,0), (4,0), (4,4)$ 的植物。

![](https://cdn.luogu.com.cn/upload/image_hosting/yncytel8.png)

**附加样例**

1. $n=8$，围住所有植物最优。
2. $n=100, x_i=i, y_i=i^2 \bmod 101, v_i=50-i$，植物排列形似甲虫。
3. $n=300$，植物构成凸多边形顶点，每隔一株收益 $1$，另一株损失 $1$。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n \leq 20$              | $30$ |
| $2$    | $n \leq 100$             | $40$ |
| $3$    | $n \leq 300$             | $30$ |


---

---
title: "[GCJ 2019 Finals] Juggle Struggle: Part 1"
layout: "post"
diff: 省选/NOI-
pid: P13126
tag: ['计算几何', '2019', '分治', 'Google Code Jam']
---
# [GCJ 2019 Finals] Juggle Struggle: Part 1
## 题目描述

The first two paragraphs (not counting this one) of this problem and "Juggle Struggle: Part 2" are identical. The problems can otherwise be solved independently; you do not need to read or solve one in order to read or solve the other.

As manager of the Graceful Chainsaw Jugglers group, you have decided to spice the show up a bit. Instead of having each juggler individually juggle their own chainsaws, you want them to form pairs, with each pair throwing the chainsaws back and forth to each other. In this new performance, $2 \times \mathbf{N}$ jugglers will be on stage at the same time, arranged into $\mathbf{N}$ pairs, with each juggler belonging to exactly one pair.

You think the show will be more impressive if the chainsaws being juggled by different pairs of jugglers are at risk of collision. Let the stage be a two-dimensional plane, and let the straight line segment in that plane that connects the positions of two jugglers in a pair be called the pair's juggling path. When two juggling paths intersect, we say the chainsaws juggled by those pairs are at risk of collision. We call the spatial positions and the pairings of the jugglers an arrangement. An arrangement is magnificent if every two pairs of jugglers' chainsaws are at risk of collision.

After a lot of thinking and designing, you came up with a magnificent arrangement. You wrote down the positions of the jugglers on the stage and the pairings of the jugglers on a piece of paper. Unfortunately, a bad chainsaw throw cut the paper in half, and you have lost the half with the pairings. Since the stage decorations have already been designed based on the positions of the jugglers, those positions cannot be changed. The show's highly anticipated debut is a mere few hours away, so you need to find a magnificent arrangement that works! Given every juggler's position on a two-dimensional stage, find a pairing of them that yields a magnificent arrangement.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with one line containing a single integer $\mathbf{N}$, the number of pairs of jugglers. Then, $2 \times \mathbf{N}$ lines follow. The i-th of these lines contains two integers $\mathbf{X}_\mathbf{i}$ and $\mathbf{Y}_\mathbf{i}$, representing the coordinates of the position of the i-th juggler.

## 输出格式

For each test case, output one line containing Case #x: $j_1$ $j_2$ $\dots$ $j_{2 \times \mathbf{N}}$, representing that jugglers $i$ and $j_i$ are to be paired together, for every $i$. Notice that $j_{j_i} = i$ for every $i$.
## 样例

### 样例输入 #1
```
3
2
-1 -1
-1 1
1 1
1 -1
3
1 2
2 1
2 3
3 1
3 3
4 2
3
7 1
1 1
7 2
5 5
3 5
1 2
```
### 样例输出 #1
```
Case #1: 3 4 1 2
Case #2: 6 5 4 3 2 1
Case #3: 5 4 6 2 1 3
```
## 提示

**Sample Explanation**

In Sample Case #1, the jugglers' positions form a square. The only valid solution is to pair up jugglers 1 and 3, and pair up jugglers 2 and 4.

**Limits**

- $-10^9 \leq \mathbf{X}_\mathbf{i} \leq 10^9$, for all i.
- $-10^9 \leq \mathbf{Y}_\mathbf{i} \leq 10^9$, for all i.
- No three juggler positions are collinear. (Note that this also implies that no two jugglers are in the same position.)
- There exists at least one way to pair the jugglers such that the resulting arrangement is magnificent.

**Test set 1 (5 Pts, Visible)**

- Time limit: 20 seconds.
- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{N} \leq 100$.

**Test set 2 (30 Pts, Hidden)**

- Time limit: 60 seconds.
- $1 \leq \mathbf{T} \leq 10$.
- $2 \leq \mathbf{N} \leq 10^5$.


---

---
title: "[GCJ 2018 #3] Raise the Roof"
layout: "post"
diff: 省选/NOI-
pid: P13151
tag: ['计算几何', '2018', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2018 #3] Raise the Roof
## 题目描述

Anthropologists have learned something surprising about a certain ancient Greek society of geometers: they loved partying as much as they loved mathematics! In fact, they kept hosting larger and larger parties over the years, so they needed to raise the roof of their ballroom to keep the noise level tolerable.

We know that the roof of their ballroom was always supported by the tips of exactly three columns; these columns were infinitely thin line segments that originated on the floor and rose up perpendicular to the floor. Whenever the society wanted to raise the roof, they would begin by removing the existing roof. Then, they would build a new column in a location where there was not already a column. Finally, they would rest a new roof on the tips of the new column and the two most recently built of the previously existing columns. For mystical reasons, no three column bases were ever collinear, and no four column tips were ever coplanar.

Each roof was a convex polygon that was part of the plane defined by the three tips that supported it. For each column $c$ built before the supporting ones, the roof did not intersect $c$ at any point and was large enough to cover the space above $c$. The roof did not touch the floor. The different roofs did not necessarily all have the same shape.

On an archeological dig, you found all $N$ columns that the society ever built, but no roof. You want to determine a possible order in which the columns could have been built that is consistent with the rules above. A possible order is an ordering of the $N$ columns such that, for each prefix of length at least 4 of the ordering, there is a roof (convex polygon) that contains the tips of the last three columns in the prefix, and for each other column in the prefix with a tip at $(x, y, h)$ the roof contains a point $(x, y, z)$ with $z > h$.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with one line containing an integer $N$: the number of columns. Then, $N$ more lines follow; the $i$-th of these lines contains three integers $X_i$, $Y_i$, and $H_i$, representing the $X$ and $Y$ coordinates and height above the ground of the tip of the $i$-th column.

## 输出格式

For each test case, output one line containing `Case #x: y1 y2 ... yN`, where $x$ is the test case number (starting from 1), and each $y_i$ is a different integer between 1 through $N$. These represent a possible ordering of the columns, with $y_i$ being the index in the input of the $i$-th built column.

It is guaranteed that at least one valid answer always exists. If there are multiple possible answers, you may output any of them.
## 样例

### 样例输入 #1
```
3
5
-1 0 3
1 2 4
1 -2 4
3 1 3
3 -1 2
4
1 1 1
2 2 3
2 3 4
10 11 120
4
1 1 1
2 2 3
2 3 4
10 11 12
```
### 样例输出 #1
```
Case #1: 5 4 3 1 2
Case #2: 3 2 1 4
Case #3: 1 2 4 3
```
## 提示

**Sample Explanation**

The following pictures illustrate Sample Case #1.

![](https://cdn.luogu.com.cn/upload/image_hosting/cefuy1j7.png)

**Limits**

- $1 \leq T \leq 100$.
- $-10^6 \leq X_i \leq 10^6$, for all $i$.
- $-10^6 \leq Y_i \leq 10^6$, for all $i$.
- $1 \leq H_i \leq 10^6$, for all $i$.
- $(X_i, Y_i)$, $(X_j, Y_j)$, and $(X_k, Y_k)$ are not collinear, for all distinct $i, j, k$.
- $(X_i, Y_i, H_i)$, $(X_j, Y_j, H_j)$, $(X_k, Y_k, H_k)$, and $(X_l, Y_l, H_l)$ are not coplanar, for all distinct $i, j, k, l$.

**Test set 1 (7 Pts, Visible)**

- $4 \leq N \leq 10$.

**Test set 2 (19 Pts, Hidden)**

- $4 \leq N \leq 1000$.


---

---
title: "[GCJ 2017 Finals] Omnicircumnavigation"
layout: "post"
diff: 省选/NOI-
pid: P13182
tag: ['计算几何', '2017', 'Google Code Jam']
---
# [GCJ 2017 Finals] Omnicircumnavigation
## 题目描述

Intrepid globetrotter K, who may or may not be the author of this problem, has been traveling a lot lately. On one of her recent trips, she traveled from San Francisco to Frankfurt to Johannesburg to Abu Dhabi to Singapore to Tokyo and back to San Francisco. On this trip, she circumnavigated the Earth by traveling along a closed path that touches every meridian. In other words, for every possible longitude, there is at least one point along this path at that longitude.

K is not sure that this trip qualifies as being super awesome, however, since it would also be possible to circumnavigate the Earth by flying to the North Pole and then walking around it, which does not seem to be particularly difficult (other than the part about flying to the North Pole). So she has decided to come up with a more generalized definition of circumnavigation. The new concept is called omn circumnavigation — a closed path around the Earth (which we assume to be a sphere) that is a circumnavigation regardless of where one places the poles. In other words, an omn icircumnavigation is a closed path on the surface of a sphere that touches every possible hemisphere. (Touching the edge of a hemisphere is sufficient.) Equivalently, an omnicircumnavigation intersects every possible great circle — a circle of greatest possible diameter on the surface of a sphere.

You are given a sequence of $\mathbf{N}$ points on a sphere of radius $1$. You need to check whether a path connecting those points in order is an omn icircumnavigation. The path is formed by connecting each pair of successive points along the shortest possible surface route, and connecting the last point to the first one in the same way. No two successive points (including the pair of the last point and the first point) are collinear with the origin. (That is, they are not antipodes — polar opposites — and they do not represent the same point on the surface of the sphere.)
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each begins with one line containing $\mathbf{N}$, the number of cities visited by K. The next $\mathbf{N}$ lines contain three integers $\mathbf{X}_{\mathbf{i}}, \mathbf{Y}_{\mathbf{i}}$ and $\mathbf{Z}_{\mathbf{i}}$ each. The $i$-th point in the list is given by the coordinates $\left(\mathbf{X}_{\mathbf{i}} / \operatorname{sqrt}\left(\mathbf{X}_{\mathbf{i}}^{2}+\mathbf{Y}_{\mathbf{i}}^{2}+\mathbf{Z}_{\mathbf{i}}^{2}\right), \mathbf{Y}_{\mathbf{i}} / \operatorname{sqrt}\left(\mathbf{X}_{\mathbf{i}}^{2}+\mathbf{Y}_{\mathbf{i}}^{2}+\mathbf{Z}_{\mathbf{i}}^{2}\right), \mathbf{Z}_{\mathbf{i}} / \operatorname{sqrt}\left(\mathbf{X}_{\mathbf{i}}^{2}+\mathbf{Y}_{\mathbf{i}}^{2}+\mathbf{Z}_{\mathbf{i}}^{2}\right)\right)$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the case number and $y$ is either YES or NO depending on whether the route is an omnicircumnavigation or not.
## 样例

### 样例输入 #1
```
4
3
1 0 0
0 1 0
0 0 1
8
5 5 5
5 -5 5
-5 -5 5
-5 5 5
-5 5 -5
-5 -5 -5
5 -5 -5
5 5 -5
3
1 0 0
-1 1 0
-1 -1 0
5
1 0 0
-1 1 0
2 0 0
-2 2 0
-1 -1 0
```
### 样例输出 #1
```
Case #1: NO
Case #2: YES
Case #3: YES
Case #4: YES
```
## 提示

**Sample Explanation**

In Sample Case #1, the three points are the surface points of one octant of the sphere, and the path traces out that octant. There are many hemispheres that do not overlap that path at all.

In Sample Case #2, the eight points are the corners of a cube inscribed in the sphere; any hemisphere will contain at least some parts of that path. Note that dividing all values by 5 would produce an equivalent case (with the same set of points).

In Sample Case #3, the path is itself a great circle, and so every other great circle must intersect it somewhere.

Sample Case #4 uses the same three points as in Sample Case #3, except that the first two points are visited twice each. Note that a case may include multiple representations of the same point, and that a path may include the same points or connections more than once.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 200$.
- $-10^{6} \leqslant \mathbf{X}_{\mathbf{i}} \leqslant 10^{6}$, for all $i$.
- $-10^{6} \leqslant \mathbf{Y}_{\mathbf{i}} \leqslant 10^{6}$, for all $i$.
- $-10^{6} \leqslant \mathbf{Z}_{\mathbf{i}} \leqslant 10^{6}$, for all $i$.
- At least one of the values in $\left(\mathbf{X}_{\mathbf{i}}, \mathbf{Y}_{\mathbf{i}}, \mathbf{Z}_{\mathbf{i}}\right) \neq 0$, for all i. For all i, j such that $(i+1=j)$ or $(i=\mathbf{N}-1$ and $j=0)$, neither of $\left(\mathbf{X}_{\mathbf{i}}, \mathbf{Y}_{\mathbf{i}}, \mathbf{Z}_{\mathbf{i}}\right)$ and $\left(\mathbf{X}_{\mathbf{j}}, \mathbf{Y}_{\mathbf{j}}, \mathbf{Z}_{\mathbf{j}}\right)$ is an integer multiple of the other. (No two successive points, including the last and first, are antipodes or represent the same point on the sphere.)

**Small dataset (Test Set 1 - Visible)**

- Time limit: ~~60~~ 15 seconds.
- $3 \leqslant \mathbf{N} \leqslant 50$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~300~~ 75 seconds.
- $3 \leqslant \mathbf{N} \leqslant 5000$.


---

---
title: "[GCJ 2013 #3] Rural Planning [Unverified]"
layout: "post"
diff: 省选/NOI-
pid: P13299
tag: ['计算几何', '2013', 'Special Judge', '凸包', 'Google Code Jam']
---
# [GCJ 2013 #3] Rural Planning [Unverified]
## 题目描述

You have recently purchased a nice big farmyard, and you would like to build a fence around it. There are already N fence posts in your farmyard.

You will add lengths of fence in straight lines connecting the fence posts. Unfortunately, for reasons you don't fully understand, your lawyers insist you actually have to use all the fence posts, or things will go bad.

In this problem, the posts will be represented as points in a 2-dimensional plane. You want to build the fence by ordering the posts in some order, and then connecting the first with the second, second with third, and finally the last one with the first. The fence segments you create should be a polygon without self-intersections. That is, at each fence-post there are only two fence segments, and at every other point there is at most one fence segment.

Now that's easy, but you also actually want to preserve the fact your farmyard is big! It's not really fun to wall off most of your farmyard with the fences. So you would like to create the fence in such a way that the enclosed area is more than half of the maximum area you could enclose if you were allowed not to use all the posts.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. The first line of each test case contains the number $N$ of posts. The posts are numbered from $0$ to $N - 1$. Each of the next $N$ lines contains two integers $X_i$ and $Y_i$ separated by a single space: the coordinates of the $i$-th post.

## 输出格式

For each test case, output one line containing "Case #x: ", where $x$ is the case number (starting from 1), followed by $N$ distinct integers from $0$ to $N - 1$, separated by spaces. They are the numbers of the posts, in either clockwise or counter-clockwise direction, that you will use to build the fence. Note that the first and last posts are connected.

If there are multiple solutions, print any of them.
## 样例

### 样例输入 #1
```
3
4
1 2
2 0
0 0
1 1
5
0 0
1 1
2 2
0 2
2 0
3
0 0
1 0
0 1
```
### 样例输出 #1
```
Case #1: 0 1 2 3
Case #2: 0 1 4 2 3
Case #3: 0 2 1
```
## 提示

**Sample Explanation**

In the first test case, there are three polygons we can construct, and two of them have a large enough area — the ones described by sequences 0 1 2 3 and 0 2 1 3. The polygon described by 0 1 3 2 would be too small. In the second test case, we have make sure the polygon does not intersect itself, so, for instance, 0 1 2 3 4 or 0 1 3 4 2 would be bad. In the third case, any order describes the same triangle and is fine.

**Limits**

- The posts will be at $N$ unique points, and will not all lie on the same line.

**Small dataset (9 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq T \leq 100$
- $3 \leq N \leq 10$
- $-100 \leq X_i, Y_i \leq 100$

**Large dataset (13 Pts, Test set 2 - Hidden)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq T \leq 30$
- $3 \leq N \leq 1000$
- $-50000 \leq X_i, Y_i \leq 50000$


---

---
title: "[GCJ 2013 Finals] Graduation Requirements"
layout: "post"
diff: 省选/NOI-
pid: P13302
tag: ['计算几何', '2013', 'Google Code Jam']
---
# [GCJ 2013 Finals] Graduation Requirements
## 题目描述

Before graduating from Awesome Programmer University, students traditionally perform certain "graduation requirements". One of these is driving around a traffic circle backwards. For most people, this is crazy enough, but as an extra challenge, you want to see if you can go backwards around the traffic circle multiple times without stopping.

The traffic circle consists of $N$ intersections, spaced evenly around the circle. A car would normally enter the traffic circle at one intersection, and then every second, it will move to the next counter-clockwise intersection, until eventually it reaches its destination and leaves.

![](https://cdn.luogu.com.cn/upload/image_hosting/7n9mnm7z.png)

You have been watching cars enter and leave the traffic circle for $X$ seconds. For each car, you record the time it enters the circle, as well as the intersections it enters and leaves at. All cars are moving counter-clockwise at the rate of 1 intersection per second. Each car you watched exited the circle before coming back to the intersection it entered at. There are multiple lanes on the traffic circle, so multiple cars can occupy the same position at the same time.

If you had planned it just right, how long could you have driven clockwise in the traffic circle during this time? You must enter the circle at some integer time $\geq 0$, leave at time $\leq X$, and once you leave, you are not allowed to come back. When in the traffic circle, you must travel clockwise at the rate of 1 intersection per second. You want to play it safe (well, as safe as driving backwards on a traffic circle can be), so you must never touch or pass by another car. In particular, you cannot leave the circle at an intersection at which another car is entering at the same moment, and you cannot enter the circle at an intersection at which another car is leaving at the same moment. You can choose when and where to enter and leave the circle.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. The first line of any test case describes the number $C$ of cars you observed. The second line contains two integers, $X$ and $N$ — the time (in seconds) for which you observed the circle, and the number of intersections on the circle. Next $C$ lines describe the cars you have seen. Each of those lines contains three integers $s_i$, $e_i$ and $t_i$ — the intersection at which the car entered the circle, the intersection on which it left and the time at which it entered. The intersections are numbered from 1 to $N$, counterclockwise (that is, the intersection number 2 is the next intersection counterclockwise from number 1).

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1) and $y$ is the maximum number of seconds you can travel on the circle. Note that $y$ can be zero both in the case where you cannot enter the circle at all and in the case when you can enter it, but can't travel even one intersection.

Remember that you are required to enter the circle at a time expressed as an integer number of seconds — you must enter at an integer time, and thus arrive at each intersection at an integer time.
## 样例

### 样例输入 #1
```
5
1
3 4
1 4 0
6
3 5
5 2 0
5 1 2
1 3 0
1 2 2
2 3 0
3 4 0
3
2 3
1 3 0
2 1 0
3 2 0
0
6 4
1
2 3
1 3 0
```
### 样例输出 #1
```
Case #1: 1
Case #2: 2
Case #3: 0
Case #4: 6
Case #5: 0
```
## 提示

**Sample Explanation**

In the first sample case, we have one car, going as in the picture in the statement. There are a number of ways allowing us to travel backwards for one second — for instance, we can enter at intersection 1 at time 1 (we can't enter at time zero, because the other car is there), and travel to intersection 4 (we can't go on to intersection 3, as we would pass the other car which will be going from 3 to 4). Another option is to enter at intersection 4 at time 0, and travel to intersection 3 (and then exit).

![](https://cdn.luogu.com.cn/upload/image_hosting/btm6wugt.png)

In the second sample case, we can travel for two seconds by entering at intersection 5 at time 1, and traveling backwards to intersection 3. In the third sample case, we can't even enter the circle - there are cars at all intersections at every full second. In the fourth case there are no cars, so we can just enter the circle at any point at time 0 and travel round and round till time 6. In the fifth case we can enter the circle, but since there are only three intersections, we will always collide with the other car if we try to move to the next one.

Note: Driving against the direction of the traffic on a traffic circle is typically not a wise thing to do and may cause harm to you or other people. Google (and Google Code Jam in particular) encourages you not to try this.

**Limits**

- $1 \leq T \leq 100$
- $1 \leq s_i, e_i \leq N$
- $s_i \neq e_i$
- $0 \leq t_i$
- Each observed car leaves the circle at time $X$ or earlier.

**Small dataset (7 Pts, Test set 1 - Visible)**

- $3 \leq N \leq 10$
- $1 \leq X \leq 10$
- $0 \leq C \leq 10$

**Large dataset (18 Pts, Test set 2 - Hidden)**

- $3 \leq N \leq 10^{10}$
- $1 \leq X \leq 10^{10}$
- $0 \leq C \leq 1000$


---

---
title: "[GCJ 2013 Finals] Drummer"
layout: "post"
diff: 省选/NOI-
pid: P13303
tag: ['计算几何', '2013', 'Special Judge', '凸包', '旋转卡壳', 'Google Code Jam']
---
# [GCJ 2013 Finals] Drummer
## 题目描述

The drummer has a very important role in any band -- keeping the rhythm. If the drummer's rhythm is uneven, it can ruin the entire performance.

You are the lead singer of a very popular rock band, and you have a bit of a problem. Your drummer has just quit the band to become a professional video gamer. You need to find a new drummer immediately. Fortunately, there is no shortage of candidates. Everyone wants a chance to join your band. Your task is to find the best drummer among the candidates, and you want the person who can keep the most consistent rhythm.

Your plan is as follows. You will ask each candidate to audition individually. During the audition, the candidate will play one drum by striking it with a drum stick several times. Ideally, the time difference between consecutive strikes should be exactly the same, producing a perfect rhythm. In a perfect rhythm, the drum strikes will have time stamps that follow an arithmetic progression like this: $T_0$, $T_0 + K$, $T_0 + 2\times K$, $\dots$, $T_0 + (N - 1)\times K$.

In real life, of course, it is nearly impossible for a human to produce a perfect rhythm. Therefore, each candidate drummer will produce a rhythm that has an error $E$, such that each $T_i$ differs by at most $E$ from some perfect rhythm. Given a candidate's sequence of drum strikes, find the smallest possible $E$ among all perfect rhythms that the candidate might have been trying to play.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one consists of two lines and represents the audition of one candidate. The first line contains a single integer -- $N$. The next line contains $N$ integers separated by spaces -- the time stamps, in milliseconds, of the drum strikes played by the candidate. The time stamps are in increasing order.

## 输出格式

For each test case, output one line containing "Case #x: $E$", where $x$ is the case number (starting from 1) and $E$ is the smallest among all possible numbers that describe the error of the candidate's drum strike sequence.

Your answer will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer.
## 样例

### 样例输入 #1
```
3
2
10 70
4
0 10 19 30
6
2 5 10 15 20 24
```
### 样例输出 #1
```
Case #1: 0
Case #2: 0.5
Case #3: 0.75
```
## 提示

**Limits**

- $1 \leq T \leq 100.$

**Small dataset (9 Pts, Test set 1 - Visible)**

- Time limit: ~~60~~ 6 seconds.
- $2 \leq N \leq 10.$
- $0 \leq T_i \leq 100.$

**Large dataset (20 Pts, Test set 2 - Hidden)**

- Time limit: ~~120~~ 12 seconds.
- For 90% of the test cases, $2 \leq N \leq 1000.$
- For all test cases, $2 \leq N \leq 50000.$
- $0 \leq T_i \leq 10^6.$


---

---
title: "[GCJ 2012 Qualification] Hall of Mirrors"
layout: "post"
diff: 省选/NOI-
pid: P13314
tag: ['模拟', '计算几何', '2012', 'Google Code Jam']
---
# [GCJ 2012 Qualification] Hall of Mirrors
## 题目描述

You live in a 2-dimensional plane, and one of your favourite places to visit is the Hall of Mirrors. The Hall of Mirrors is a room (a 2-dimensional room, of course) that is laid out in a grid. Every square on the grid contains either a square mirror, empty space, or you. You have width 0 and height 0, and you are located in the exact centre of your grid square.

Despite being very small, you can see your reflection when it is reflected back to you exactly. For example, consider the following layout, where '#' indicates a square mirror that completely fills its square, '.' indicates empty space, and the capital letter 'X' indicates you are in the center of that square:

```
######
#..X.#
#.#..#
#...##
######
```

If you look straight up or straight to the right, you will be able to see your reflection.

Unfortunately in the Hall of Mirrors it is very foggy, so you can't see further than $D$ units away. Suppose $D=3$. If you look up, your reflection will be 1 unit away (0.5 to the mirror, and 0.5 back). If you look right, your reflection will be 3 units away (1.5 to the mirror, and 1.5 back), and you will be able to see it. If you look down, your reflection will be 5 units away and you won't be able to see it.

It's important to understand how light travels in the Hall of Mirrors. Light travels in a straight line until it hits a mirror. If light hits any part of a mirror but its corner, it will be reflected in the normal way: it will bounce off with an angle of reflection equal to the angle of incidence. If, on the other hand, the light would touch the corner of a mirror, the situation is more complicated. The following diagrams explain the cases:

In the following cases, light approaches a corner and is reflected, changing its direction:

![](https://cdn.luogu.com.cn/upload/image_hosting/u55batrx.png)

In the first two cases, light approached two adjacent mirrors at the point where they met. Light was reflected in the same way as if it had hit the middle of a long mirror. In the third case, light approached the corners of three adjacent mirrors, and returned in exactly the direction it came from.

In the following cases, light approaches the corners of one or more mirrors, but does not bounce, and instead continues in the same direction:

![](https://cdn.luogu.com.cn/upload/image_hosting/6wlefjn2.png)

This happens when light reaches distance 0 from the corner of a mirror, but would not have to pass through the mirror in order to continue in the same direction. In this way, a ray of light can pass between two mirrors that are diagonally adjacent to each other -- effectively going through a space of size 0. Good thing it's of size 0 too, so it fits!

In the final case, light approaches the corner of one mirror and is destroyed:

![](https://cdn.luogu.com.cn/upload/image_hosting/3lb0xedn.png)

The mirror was in the path of the light, and the ray of light didn't approach the corners of any other mirrors.

Note that light stops when it hits you, but it has to hit the exact centre of your grid square.

How many images of yourself can you see?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing three space-separated integers, $H$, $W$ and $D$. $H$ lines follow, and each contains $W$ characters. The characters constitute a map of the Hall of Mirrors for that test case, as described above.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1) and $y$ is the number of reflections of yourself you can see.
## 样例

### 样例输入 #1
```
6
3 3 1
###
#X#
###
3 3 2
###
#X#
###
4 3 8
###
#X#
#.#
###
7 7 4
#######
#.....#
#.....#
#..X..#
#....##
#.....#
#######
5 6 3
######
#..X.#
#.#..#
#...##
######
5 6 10
######
#..X.#
#.#..#
#...##
######
```
### 样例输出 #1
```
Case #1: 4
Case #2: 8
Case #3: 68
Case #4: 0
Case #5: 2
Case #6: 28
```
## 提示

**Sample Explanation**

In the first case, light travels exactly distance 1 if you look directly up, down, left or right.

In the second case, light travels distance $1.414\dots $ if you look up-right, up-left, down-right or down-left. Since light does not travel through you, looking directly up only shows you one image of yourself.

In the fifth case, while the nearby mirror is close enough to reflect light back to you, light that hits the corner of the mirror is destroyed rather than reflected.

**Limits**

- $1 \leq T \leq 100$.
- $3 \leq H, W \leq 30$.
- $1 \leq D \leq 50$.
- All characters in each map will be '#', '.', or 'x'.
- Exactly one character in each map will be 'x'.
- The first row, the last row, the first column and the last column of each map will be entirely filled with '#' characters.

**Test set 1 (15 Pts, Visible Verdict)**

- There will be no more than $2W + 2H - 4$ '#' characters.

**Test set 2 (25 Pts, Hidden Verdict)**

- The restriction from the Small dataset does not apply.


---

---
title: "[GCJ 2012 Finals] Twirling Towards Freedom"
layout: "post"
diff: 省选/NOI-
pid: P13335
tag: ['数学', '计算几何', '2012', 'Special Judge', '凸包', '旋转卡壳', 'Google Code Jam']
---
# [GCJ 2012 Finals] Twirling Towards Freedom
## 题目背景

> "I say we must move forward, not backward;
upward, not forward;    
> and always twirling, twirling, twirling towards freedom!"    
> — Former U.S. Presidential nominee Kodos.
## 题目描述

After hearing this inspirational quote from America's first presidential nominee from the planet Rigel VII, you have decided that you too would like to twirl (rotate) towards freedom. For the purposes of this problem, you can think of "freedom" as being as far away from your starting location as possible.

The galaxy is a two-dimensional plane. Your space ship starts at the origin, position $(0, 0)$. There are $N$ stars in the galaxy. Every minute, you can choose a star and rotate your space ship 90 degrees clockwise around the star. You may also choose to stay where you are.

How far away can you move from the origin after $M$ minutes?

![](https://cdn.luogu.com.cn/upload/image_hosting/3jmyptcf.png)

The image illustrates the first 3 rotations for a possible path in sample case 1. Note that this path is not necessarily a part of any optimal solution.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, beginning with two lines containing integers $N$ and $M$. The next $N$ lines each contain two integers, $X_i$ and $Y_i$, representing the locations of stars.

## 输出格式

For each test case, output one line containing "Case #$x$: $D$", where $x$ is the case number (starting from 1) and $D$ is the distance from the origin to the optimal final position. Answers with absolute or relative error no larger than $10^{-6}$ will be accepted.
## 样例

### 样例输入 #1
```
3
4
1
-2 4
1 -2
4 1
0 2
1
4
-5 0
2
5
-1 1
-2 2
```
### 样例输出 #1
```
Case #1: 6.3245553203
Case #2: 10.0000000000
Case #3: 6.3245553203
```
## 提示

**Limits**

- $1 \leq T \leq 100;$
- $-1000 \leq X_i \leq 1000;$
- $-1000 \leq Y_i \leq 1000.$
- No two stars will be at the same location.
- There may be a star at the origin.

**Test set 1 (10 Pts, Visible Verdict)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq N \leq 10.$
- $1 \leq M \leq 10.$

**Test set 2 (39 Pts, Hidden Verdict)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq N \leq 5000.$
- $1 \leq M \leq 10^8.$



---

---
title: "[GCJ 2010 #2] Grazing Google Goats"
layout: "post"
diff: 省选/NOI-
pid: P13402
tag: ['计算几何', '2010', 'Special Judge', '凸包', 'Google Code Jam']
---
# [GCJ 2010 #2] Grazing Google Goats
## 题目描述

Farmer John has recently acquired a nice herd of $N$ goats for his field. Each goat $i$ will be tied to a pole at some position $P_i$ using a rope of length $L_i$. This means that the goat will be able to travel anywhere in the field that is within distance $L_i$ of the point $P_i$, but nowhere else. (The field is large and flat, so you can think of it as an infinite two-dimensional plane.)

Farmer John already has the pole positions picked out from his last herd of goats, but he has to choose the rope lengths. There are two factors that make this decision tricky:

- The goats all need to be able to reach a single water bucket. Farmer John has not yet decided where to place this bucket. He has reduced the choice to a set of positions $\{Q_1, Q_2, \ldots, Q_M\}$, but he is not sure which one to use.
- The goats are ill-tempered, and when they get together, they sometimes get in noisy fights. For everyone's peace of mind, Farmer John wants to minimize the area $A$ that can be reached by all the goats.

Unfortunately, Farmer John is not very good at geometry, and he needs your help for this part!

For each bucket position $Q_j$, you should choose rope lengths so as to minimize the area $A_j$ that can be reached by every goat when the bucket is located at position $Q_j$. You should then calculate each of these areas $A_j$.

### Example

In the picture below, there are four blue points, corresponding to the pole positions: $P_1$, $P_2$, $P_3$, and $P_4$. There are also two red points, corresponding to the potential bucket positions: $Q_1$ and $Q_2$. You need to calculate $A_1$ and $A_2$, the areas of the two shaded regions.

![](https://cdn.luogu.com.cn/upload/image_hosting/mnv6gfis.png)
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing the integers $N$ and $M$.

The next $N$ lines contain the positions $P_1, P_2, \ldots, P_N$, one per line. This is followed by $M$ lines, containing the positions $Q_1, Q_2, \ldots, Q_M$, one per line.

Each of these $N + M$ lines contains the corresponding position's $x$ and $y$ coordinates, separated by a single space.

## 输出格式

For each test case, output one line containing "Case #$x$: $A_1$ $A_2$ ... $A_M$", where $x$ is the case number (starting from 1), and $A_1$ $A_2$ ... $A_M$ are the values defined above. Answers with a relative or absolute error of at most $10^{-6}$ will be considered correct.
## 样例

### 样例输入 #1
```
3
2 3
0 20
20 0
-20 10
40 20
0 19
4 2
0 0
100 100
300 0
380 90
400 100
1000 5
3 1
0 0
10 10
20 0
10 5
```
### 样例输出 #1
```
Case #1: 1264.9865911 1713.2741229 0.2939440
Case #2: 1518.9063729 1193932.9692206
Case #3: 0.0
```
## 提示

**Limits**

- All coordinates are integers between $-10,000$ and $10,000$.
- The positions $P_1, P_2, \ldots, P_N, Q_1, Q_2, \ldots, Q_M$ are all distinct and no three are collinear.

**Small dataset (7 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq T \leq 100$.
- $N = 2$.
- $1 \leq M \leq 10$.

**Large dataset (25 Pts, Test set 2 - Hidden)**

- Time limit: ~~120~~ 12 seconds.
- $1 \leq T \leq 10$.
- $2 \leq N \leq 5,000$.
- $1 \leq M \leq 1,000$.



---

---
title: "[CERC 2020] Roof Escape"
layout: "post"
diff: 省选/NOI-
pid: P13660
tag: ['计算几何', '2020', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2020] Roof Escape
## 题目描述

Escaping from the police over city roofs is often tricky and the gangsters have to be trained properly. To keep up with current AI trends in criminality, they are developing a general computerized model of escape paths.

In the model, the city area where the escape happens is modeled as a 3D grid made of rectangular cuboids with square bases forming a 2D grid on flat ground. Each cuboid represents a block of houses. Top face of a cuboid is called a roof. In the model, all distances between adjacent blocks are reduced to 0. The path of escaping gangsters is modeled as a polyline – a sequence of straight horizontal and vertical segments where the end point of one segment is the start point of the next segment. The basic path properties are:

- Each point on the path is on the surface of at least one block.
- No part of the path is in the interior of any block.
- The height of any point on the path is bigger than or equal to the lowest height of roofs of all blocks to which surface the point belongs.
- The path starts and ends in the center of a block roof.
- The sum over the lengths of horizontal segments of the path is minimum possible.

It may happen that two consecutive segments on the path share common points. This stems from the fact that the path models a real behavior of a person moving over physical obstacles. Thus an additional path rule also holds:

- Let $P$ be a point on the path. If there is a point $Q$ directly above $P$, and $Q$ belongs to at least two blocks, then the point $Q$ is on the path.

The total length of the escape path should be carefully calculated in the model.

![](https://cdn.luogu.com.cn/upload/image_hosting/4r0xxwq5.png)
## 输入格式

The first line of the input contains six positive integers $W, H, S_x, S_y, E_x, E_y$ ($1 \leq W \cdot H \leq 10^5$, $1 \leq S_x, E_x \leq W$, $1 \leq S_y, E_y \leq H$). $W$ and $H$ are even integers representing the dimensions of the grid base in meters, integers $S_x, S_y$ denote starting coordinates of the escape path and $E_x, E_y$ denote coordinates of the end.

Each of the next $H/2$ lines contains $W/2$ integers, the $i$-th integer on $j$-th line is the height of the corresponding block $T_{i,j}$ in meters ($0 \leq T_{i,j} \leq 10^3$).

Each grid block base is a square with dimensions of $2 \times 2$ meters in the model.
## 输出格式

Print the length of the escape path. The difference between the printed length and the exact length must be less than $10^{-4}$.
## 样例

### 样例输入 #1
```
8 8 1 7 7 1
2 3 2 0
2 1 1 2
1 2 0 0
0 0 0 1
```
### 样例输出 #1
```
14.485281374238
```
## 提示

The sample input with its solution is shown on the picture above.


---

---
title: "[NWERC 2023] Isolated Island"
layout: "post"
diff: 省选/NOI-
pid: P13708
tag: ['图论', '计算几何', '2023', '平面图', '二分图', 'ICPC', 'Ad-hoc']
---
# [NWERC 2023] Isolated Island
## 题目描述

On a small island far far away, a handful of old men live isolated from the rest of the world.
The entire island is divided into plots of land by fences, and each old man owns
a single plot of land bounded by fences on all sides. (The region
outside all fences is the ocean.)
Each of the inhabitants needs fish to survive and the only place where they can fish is the ocean surrounding them.
Since not every plot of land is connected to the ocean,
some of the men might need to pass through the land of others before being able to fish.
The men can cross a single fence at a time, but cannot go through fenceposts or
locations where fences intersect.

Unfortunately, the old men are greedy.
They demand one fish each time a person wants to enter their land.
Since they do not want to lose too much fish to the others,
every old man chooses a route that minimizes the number of fish he has to pay to get to the ocean.

Over the years, this has led to rivalry between the old men.
Each man hates all other men who have to pay less than him to reach the ocean.
Two men only *like* each other if they have to pay the same amount of fish to reach the ocean.

|![](https://cdn.luogu.com.cn/upload/image_hosting/e253y5sb.png)|![](https://cdn.luogu.com.cn/upload/image_hosting/8aukzter.png)|![](https://cdn.luogu.com.cn/upload/image_hosting/ea4htdic.png)|
|:---:|:---:|:---:|

:::align{center}
Figure I.1: Illustrations of the first three Sample Inputs. In Sample Input 1, every man has direct access to the ocean, so they all like each other. In Sample Input 2, there does not exist a pair of neighbours who like each other, because the man living in the middle needs to pay one fish, whereas all of his neighbours do not have to pay any fish to reach the ocean. In Sample Input 3, there are six men, some of whom are friendly neighbours.
:::

The natural question which now occurs is:
are there some old men on this island who are neighbours (owning land on
opposite sides of a single fence) and like each other?
See Figure I.1 for two islands with opposite answers to this question.
## 输入格式

The input consists of:
- One line with an integer $n$ ($3 \le n \le 1000$), the number of fences.
- $n$ lines, each with four integers $x_1$, $y_1$, $x_2$, and $y_2$ ($\left|x_1\right|, \left|y_1\right|, \left|x_2\right|, \left|y_2\right|\leq 10^6$, $(x_1,y_1)\neq(x_2,y_2)$), indicating a straight fence between fenceposts at $(x_1,y_1)$ and $(x_2, y_2)$.

Note that fences may intersect internally, and that three or more fences may intersect in the same location.

It is guaranteed that any two fences intersect only in at most one point.
Furthermore, after crossing a single fence, one always ends up in a different region.
All regions together form a single island, where any region can be reached from any other region.

## 输出格式

If there exists a pair of neighbours who like each other, then output "$\texttt{yes}$". Otherwise, output "$\texttt{no}$".
## 样例

### 样例输入 #1
```
6
-3 -3 0 3
-3 -3 0 0
-3 -3 3 -3
0 0 0 3
0 0 3 -3
0 3 3 -3
```
### 样例输出 #1
```
yes
```
### 样例输入 #2
```
 6
-6 -3 0 3
0 3 6 -3
6 -3 -6 -3
-3 0 3 0
3 0 0 -3
0 -3 -3 0
```
### 样例输出 #2
```
no
```
### 样例输入 #3
```
8
0 1 2 1
2 2 0 0
1 2 1 0
1 0 2 1
0 0 2 0
1 2 2 2
0 1 0 0
2 2 2 0
```
### 样例输出 #3
```
yes
```
### 样例输入 #4
```
4
0 0 1 0
1 0 1 1
1 1 0 1
0 1 0 0
```
### 样例输出 #4
```
no
```


---

---
title: "[SWERC 2023] Favourite dish"
layout: "post"
diff: 省选/NOI-
pid: P13798
tag: ['计算几何', '2023', '凸包', 'ICPC', '李超线段树']
---
# [SWERC 2023] Favourite dish
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/f4e13fe8cb3692d86fceaeba9e38456b9c240bed.png)

:::

France is a country of gastronomy. For a dish, both the taste and plating are important. Nevertheless, when different people evaluate a dish, some focus more on taste and some focus more on plating. At the Olympic Village dining hall, there are $N$ dishes, numbered from 1 to $N$; each dish has a score on its taste and a score on its plating. There are also $M$ persons, numbered from 1 to $M$; each person has a weight on taste and a weight on plating. One person's final score of a dish is the weighted average of the dish's scores on taste and plating.


The chefs at the Olympics want to provide everyone with their favourite dish on the evening of the closing ceremony. Your task is to calculate everyone's favourite dish. If multiple dishes tie for the highest score as a person's favourite, choose the one with the smallest number.


## 输入格式

Each line contains two space-separated integers. The first line contains the numbers $N$ and $M$. Then follow $N$ lines; the $k^\text{th}$ such line contains two integers $t_k$ and $p_k$, which are the scores of the dish $k$ on taste and on plating. Then come $M$ more lines; the $l^\text{th}$ such line contains two integers $T_l$ and $P_l$, which are the weights of person $l$ on taste and on plating.

**Limits**

- $1 \leq N \leq 500~000$;
- $1 \leq M \leq 500~000$;
- $0 \leq t_k \leq 1~000~000, 0 \leq p_k \leq 1~000~000$, and $(t_k, p_k) \neq (0, 0)$ for all $k \leq N$;
- $0 \leq T_l \leq 1~000~000, 0 \leq P_l \leq 1~000~000$, and $(T_l, P_l) \neq (0, 0)$ for all $l \leq M$;
- the $N$ pairs $(t_k, p_k)$ are pairwise distinct;
- the $M$ pairs $(T_l, T_l)$ are pairwise distinct.
## 输出格式

The output should contain $M$ lines. The $l^\text{th}$ such line should contain one number: the number of the favourite dish of person $l$.
## 样例

### 样例输入 #1
```
4 3
2 5
3 4
4 2
1 6
6 4
2 8
5 5
```
### 样例输出 #1
```
2
4
1
```
### 样例输入 #2
```
3 4
1 0
0 2
0 1
1 1
2 2
2 1
1 0
```
### 样例输出 #2
```
2
2
1
1
```
## 提示

**Sample Explanation 1**

Here is the score table for each person on each dish. Each person's favourite dish is indicated with a $^\ast$; person 3 has three tied favourite dishes, so we chose the first one.

|   | Dish | < | < | < |
|:-:|:-:|:-:|:-:|:-:|
| Person | 1 | 2 | 3 | 4 |
| 1 | $3.2$ | $3.4^\ast$ | $3.2$ | $3$ |
| 2 | $4.4$ | $3.8$ | $2.4$ | $5^\ast$ |
| 3 | $3.5^\ast$ | $3.5$ | $3$ | $3.5$ |

**Sample Explanation 2**


Here is the score table for each person on each dish. Each person's favourite dish is indicated with a $^\ast$.

|   | Dish | < | < |
|:-:|:-:|:-:|:-:|
| Person | 1 | 2 | 3 |
| 1 | $0.5$ | $1^\ast$ | $0.5$ |
| 2 | $0.5$ | $1^\ast$ | $0.5$ |
| 3 | $2/3^\ast$ | $2/3$ | $1/3$ |
| 4 | $1^\ast$ | $0$ | $0$ |



---

---
title: "【模板】旋转卡壳 | [USACO03FALL] Beauty Contest G"
layout: "post"
diff: 省选/NOI-
pid: P1452
tag: ['计算几何', '2003', 'USACO', '枚举', '凸包', '旋转卡壳']
---
# 【模板】旋转卡壳 | [USACO03FALL] Beauty Contest G
## 题目描述

给定平面上 $n$ 个点，求凸包直径。

## 输入格式

第一行一个正整数 $n$。   
接下来 $n$ 行，每行两个整数 $x,y$，表示一个点的坐标。保证所有点的坐标两两不同。
## 输出格式

输出一行一个整数，表示答案的平方。
## 样例

### 样例输入 #1
```
4
0 0
0 1
1 1
1 0

```
### 样例输出 #1
```
2
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$2\le n \le 50000$，$|x|,|y| \le 10^4$。

---

$\text{upd 2022.7.22}$：新增加四组 Hack 数据。


---

---
title: "[USACO16DEC] Lots of Triangles P"
layout: "post"
diff: 省选/NOI-
pid: P1715
tag: ['计算几何', '2016', 'USACO', '容斥原理', '分类讨论']
---
# [USACO16DEC] Lots of Triangles P
## 题目描述

Farmer John is thinking of selling some of his land to earn a bit of extra income. His property contains $N$ trees ($3 \leq N \leq 300$), each described by a point in the 2D plane, no three of which are collinear. FJ is thinking about selling triangular lots of land defined by having trees at their vertices; there are of course $L = \binom{N}{3}$ such lots he can consider, based on all possible triples of trees on his property.

A triangular lot has value $v$ if it contains exactly $v$ trees in its interior (the trees on the corners do not count, and note that there are no trees on the boundaries since no three trees are collinear). For every $v = 0 \ldots N-3$, please help FJ determine how many of his $L$ potential lots have value $v$.
## 输入格式

The first line of input contains $N$.

The following $N$ lines contain the $x$ and $y$ coordinates of a single tree; these are both integers in the range $0 \ldots 1,000,000$.
## 输出格式

Output $N-2$ lines, where output line $i$ contains a count of the number of lots having value $i-1$.
## 样例

### 样例输入 #1
```
7
3 6
17 15
13 15
6 12
9 1
2 7
10 19
```
### 样例输出 #1
```
28
6
1
0
0
```
## 题目翻译

### 题目描述

Farmer John 正在考虑出售他的一部分土地以赚取一些额外收入。他的财产包含 $N$ 棵树（$3 \leq N \leq 300$），每棵树由二维平面中的一个点描述，且任意三棵树不共线。FJ 正在考虑出售由三棵树作为顶点定义的三角形地块；显然，他可以考虑的此类地块数量为 $L = \binom{N}{3}$，基于他财产中所有可能的三棵树组合。

一个三角形地块的价值为 $v$，如果它的内部恰好包含 $v$ 棵树（顶点上的树不计入，且由于没有三棵树共线，边界上也没有树）。对于每个 $v = 0 \ldots N-3$，请帮助 FJ 确定他的 $L$ 个潜在地块中有多少个地块的价值为 $v$。

### 输入格式

输入的第一行包含 $N$。

接下来的 $N$ 行每行包含一棵树的 $x$ 和 $y$ 坐标；这些坐标都是 $0 \ldots 1,000,000$ 范围内的整数。

### 输出格式

输出 $N-2$ 行，其中第 $i$ 行输出价值为 $i-1$ 的地块数量。


---

---
title: "最小圆覆盖"
layout: "post"
diff: 省选/NOI-
pid: P1742
tag: ['计算几何', 'Special Judge']
---
# 最小圆覆盖
## 题目描述

给出 $N$ 个点，让你画一个最小的包含所有点的圆。
## 输入格式

第一行一个整数 $N$ 表示点的个数。

接下来 $N$ 行每行两个实数 $x_i,y_i$ 表示点的坐标。最多两位小数。
## 输出格式

第一行一个实数表示圆的半径。

第二行两个实数表示圆心的坐标。

本题开启 spj，您的答案与标准答案误差不超过 $10^{-9}$ 时，视为正确。
## 样例

### 样例输入 #1
```
6
8.0 9.0
4.0 7.5
1.0 2.0
5.1 8.7
9.0 2.0
4.5 1.0
```
### 样例输出 #1
```
5.0000000000
5.0000000000 5.0000000000
```
## 提示

对于 $100\%$ 的数据，$1\leq N\leq 10^5$，$|x_i|,|y_i|\leq 10^4$。

2022.2.26 添加 spj


---

---
title: "[NOI2011] 智能车比赛"
layout: "post"
diff: 省选/NOI-
pid: P1995
tag: ['动态规划 DP', '计算几何', '2011', 'NOI', 'Special Judge', '最短路']
---
# [NOI2011] 智能车比赛
## 题目描述

新一届智能车大赛在 JL 大学开始啦！比赛赛道可以看作是由 $n$ 个矩形区域拼接而成（如下图所示），每个矩形的边都平行于坐标轴，第 $i$ 个矩形区域的左下角和右上角坐标分别为 $(x_{i,1},y_{i,1})$ 和 $(x_{i,2},y_{i,2})$。

题目保证：$x_{i,1}<x_{i,2}=x_{i+1,1}$，且 $y_{i,1}< y_{i,2}$，相邻两个矩形一定有重叠在一起的边（如图中虚线所示），智能车可以通过这部分穿梭于矩形区域之间。

![](https://cdn.luogu.com.cn/upload/image_hosting/hu6cu53o.png)

选手们需要在最快的时间内让自己设计的智能车从一个给定的起点 $S$ 点到达一个给定的终点 $T$ 点，且智能车不能跑出赛道。假定智能车的速度恒为 $v$ 且转向不消耗任何时间，你能算出最快需要多少时间完成比赛么？

## 输入格式

输入的第一行包含一个正整数 $n$，表示组成赛道的矩形个数。

接下来 $n$ 行描述这些矩形，其中第 $i$ 行包含 $4$ 个整数 $x_{i,1}, y_{i,1}, x_{i,2}, y_{i,2}$，表示第 $i$ 个矩形左下角和右上角坐标分别为 $(x_{i,1}, y_{i,1})$ 和 $(x_{i,2}, y_{i,2})$。

接下来一行包含两个整数 $x_S, y_S$，表示起点坐标。

接下来一行包含两个整数 $x_T, y_T$，表示终点坐标。

接下来一行包含一个实数 $v$，表示智能车的速度。

## 输出格式

仅输出一个实数，至少精确到小数点后第六位，为智能车完成比赛的最快时间。

对于每个测试点，如果你的输出结果和参考结果相差不超过 $10^{-6}$，该测试点得满分，否则不得分。

## 样例

### 样例输入 #1
```
2  
1 1 2 2  
2 0 3 4  
1 1  
3 0  
1.0 
```
### 样例输出 #1
```
2.41421356
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/m6t1j6pf.png)


---

---
title: "[AHOI2012] 信号塔"
layout: "post"
diff: 省选/NOI-
pid: P2533
tag: ['计算几何', '2012', '各省省选', '安徽', '随机化']
---
# [AHOI2012] 信号塔
## 题目描述

在野外训练中，为了确保每位参加集训的成员安全，实时的掌握和收集周边环境和队员信息非常重要，集训队采用的方式是在训练所在地散布 $N$ 个小型传感器来收集并传递信息，这些传感器只与设在集训地中的信号塔进行通信，信号塔接收信号的覆盖范围是圆形，可以接收到所有分布在该集训区域内所有 $N$ 个小型传感器（包括在该圆形的边上）发出的信号。信号塔的功率与信号塔接收范围半径的大小成正比，因为是野外训练，只能使用事先储备好的蓄电设备，因此在可以收集所有传感器信息的基础上，还应使得信号塔的功率最小。小龙帮助教官确定了一种信号塔设置的方案，既可以收集到所有 $N$ 个传感器的信号，又可以保证这个信号塔的功率是最小的。同学们，你们知道，这个信号塔的信号收集半径有多大，它应该设置在何处吗?
## 输入格式

共 $N+1$ 行，第一行为正整数 $N$，表示队员个数。接下来 $N$ 行，每行两个实数用空格分开，分别是第 $i$ 个队员的坐标 $x_i$ 和 $y_i$ （$x_i,y_i$ 不超过双精度范围）。
## 输出格式

一行，共三个实数（中间用空格隔开），分别是信号塔的坐标，和信号塔覆盖的半径。
## 样例

### 样例输入 #1
```
5
1.200 1.200
2.400 2.400
3.800 4.500
2.500 3.100
3.900 1.300
```
### 样例输出 #1
```
2.50 2.85 2.10
```
## 提示

队员是否在边界上的判断应该符合他到圆心的距离与信号塔接受半径的差的绝对值小于 $10^{-6}$，最终结果保留 $2$ 位小数。

对于 $30\%$ 的数据，满足 $1\le N \le 10^4$  
对于 $70\%$ 的数据，满足 $1\le N \le 2\times10^4$  
对于 $100\%$ 的数据，满足 $1\le N \le 10^6$

本题存在 hack 数据，计 0 分。


---

---
title: "[ZJOI2008] Risk"
layout: "post"
diff: 省选/NOI-
pid: P2588
tag: ['动态规划 DP', '计算几何', '2008', '各省省选', '浙江']
---
# [ZJOI2008] Risk
## 题目描述

经过连续若干年的推广，Risk这个游戏已经风靡全国，成为大众喜闻乐见的重要娱乐方式。Risk这个游戏可以理解为一种简易的策略游戏，游戏者的目的是占领所有的土地。由于游戏规则的规定，只要两个国家相邻，就认为两个国家有交战的可能性。我们现在希望知道在当前的局面下，哪些国家之间有交战的可能性。注意，我们认为只有当两个国家的国界线有公共边的时候才认为相邻，若两个国家的领土只有公共点，则认为两个国家不相邻。

每一个国家的边界由一系列线段组成，保证这个边界是一个简单多边形，即严格不自交。为了定位每个国家的位置，我们还给出每个国家最庞大的一支军队的位置，保证这个位置一定出现在某一个形内，而不是出现在某条边界上。

## 输入格式

输入文件的第一行中包括两个整数n,m。分别表示地图上的国家数和描述国家的边界的线段的数量。1<=n<=600，1<=m<=4000。接下来n行，每行用一对数描述了某个国家的主力军队的坐标。接下来m行，每行有4个数x1,y1,x2,y2，（x1,y1）-(x2,y2)描述了一条国界线。所有点的坐标都是0-10000之间的整数。

保证输入的所有线段至多只会在线段交点处相交。整张地图上有且仅有一块面积无限的空白区域不属于任何国家。每一条国界线两侧的区域或者隶属于两个不同的国家，或者分隔了一个国家与那块无穷大的空白区域。即保证一条国界线两侧的区域不同时属于同一个国家或是同时都是空白区域。所有封闭区域内部包含且仅包含一支主力军队，表示了该区域的归属。

 ![](https://cdn.luogu.com.cn/upload/pic/1707.png) 

例如上图中第一行的数据是合法的。而第二行中的数据都是不合法的。左边的那幅图包含线段两侧都是空白区域；中间的图包含线段两侧区域同时属于同一个国家；右边的图中军队被布置在了国界线上，因此非法；此外若最右侧的图中若没有军队也是非法的。保证输入文件提供的数据都是合法的，你的程序不需要进行数据合法性的判定。

## 输出格式

输出文件包括n行，每行第一个数字x表示有x个国家可能与这个国家交战，接着在同一行中升序输出x个整数，表示可能与这个国家交战的国家的编号。国家按输入中给出的顺序从1到n编号。注意数字间严格以一个空格隔开，并且不要在行末输出多余的空白字符。

## 样例

### 样例输入 #1
```
4 12

3 2

11 8

12 17

1 19

0 0 10 0

10 0 20 0

20 0 20 10

20 10 20 20

20 20 10 20

10 20 0 20

0 20 0 10

0 10 0 0

10 0 10 10

0 10 10 10

20 10 10 10

10 20 10 10


```
### 样例输出 #1
```
2 2 4

2 1 3

2 2 4

2 1 3


```
### 样例输入 #2
```
4 16

170 13

24 88

152 49

110 130

60 60 140 60

140 60 140 140

140 140 60 140

60 140 60 60

0 0 200 0

200 0 200 200

200 200 0 200

0 200 0 0

40 40 160 40

160 40 160 160

160 160 40 160

40 160 40 40

20 20 180 20

180 20 180 180

180 180 20 180

20 180 20 20


```
### 样例输出 #2
```
1 2

2 1 3

2 2 4

1 3


```


---

---
title: "[ZJOI2008] 瞭望塔"
layout: "post"
diff: 省选/NOI-
pid: P2600
tag: ['计算几何', '2008', '各省省选', '浙江', '半平面交']
---
# [ZJOI2008] 瞭望塔
## 题目描述

致力于建设全国示范和谐小村庄的H村村长dadzhi，决定在村中建立一个瞭望塔，以此加强村中的治安。

我们将H村抽象为一维的轮廓。如下图所示

 
 ![](https://cdn.luogu.com.cn/upload/pic/1710.png) 

我们可以用一条山的上方轮廓折线(x1, y1), (x2, y2), …. (xn, yn)来描述H村的形状，这里x1 < x2 < …< xn。瞭望塔可以建造在[x1, xn]间的任意位置, 但必须满足从瞭望塔的顶端可以看到H村的任意位置。可见在不同的位置建造瞭望塔，所需要建造的高度是不同的。为了节省开支，dadzhi村长希望建造的塔高度尽可能小。

请你写一个程序，帮助dadzhi村长计算塔的最小高度。

## 输入格式

输入文件tower.in第一行包含一个整数n，表示轮廓折线的节点数目。接下来第一行n个整数, 为x1 ~ xn. 第三行n个整数，为y1 ~ yn。

## 输出格式

输出文件tower.out仅包含一个实数，为塔的最小高度，精确到小数点后三位。

## 样例

### 样例输入 #1
```
6

1 2 4 5 6 7

1 2 2 4 2 1


```
### 样例输出 #1
```
1.000
```
## 提示

对于60%的数据， N ≤ 60；

对于100%的数据， N ≤ 300，输入坐标绝对值不超过106，注意考虑实数误差带来的问题。



---

---
title: "[USACO10OPEN] Triangle Counting G"
layout: "post"
diff: 省选/NOI-
pid: P2992
tag: ['计算几何', '2010', 'USACO', '排序', '容斥原理']
---
# [USACO10OPEN] Triangle Counting G
## 题目描述

Bessie is standing guard duty after

the big bad wolf was spotted stalking

```cpp
cows over at Farmer Don's spread. 
Looking down from her guard tower in 
utter boredom, she's decided to 
perform intellectual exercises in 
```
order to keep awake.
After imagining the field as an X,Y

grid, she recorded the coordinates of

the N (1 <= N <= 100,000) 

conveniently numbered 1..N cows as

```cpp
X_i,Y_i (-100,000 <= X_i <= 100,000; 
-100,000 <= Y_i <= 100,000; 1 <= i <= 
N). She then mentally formed all possible triangles that could be made from subsets of the entire set of cow coordinates. She counts a triangle as 'golden' if it wholly contains the origin (0,0). The origin does not fall on the line between any pair of cows. Additionally, no cow is standing exactly on the origin. 
Given the list of cow locations, calculate the number of 'golden' triangles that contain the origin so Bessie will know if she's doing a good job. 
```
By way of example, consider 5 cows at these locations:
-5,0   0,2   11,2   -11,-6   11,-5

Below is a schematic layout of the field from Betsy's point of view:

```cpp
............|............ 
............*..........*. 
............|............ 
-------*----+------------ 
............|............ 
............|............ 
............|............ 
............|............ 
............|..........*. 
.*..........|............ 
............|............ 
```
All ten triangles below can be formed from the five points above:

By inspection, 5 of them contain the origin and hence are 'golden'.

在一只大灰狼偷偷潜入Farmer Don的牛群被群牛发现后，贝西现在不得不履行着她站岗的职责。从她的守卫塔向下瞭望简直就是一件烦透了的事情。她决定做一些开发智力的小练习，防止她睡着了。



想象牧场是一个X，Y平面的网格。她将N只奶牛标记为1…N (1 <= N <= 100,000)，每只奶牛的坐标为X\_i,Y\_i (-100,000 <= X\_i <= 100,000;-100,000 <= Y\_i <= 100,000; 1 <= i <=N)。然后她脑海里想象着所有可能由奶牛构成的三角形。如果一个三角形完全包含了原点(0,0)，那么她称这个三角形为“黄金三角形”。原点不会落在任何一对奶牛的连线上。另外，不会有奶牛在原点。

给出奶牛的坐标，计算出有多少个“黄金三角形”。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Each line contains two integers, the coordinates of a single cow: X\_i and Y\_i

## 输出格式

\* Line 1: A single line with a single integer that is the count of the number of times a triangle formed by the cow locations contains the origin

## 样例

### 样例输入 #1
```
5 
-5 0 
0 2 
11 2 
-11 -6 
11 -5 

```
### 样例输出 #1
```
5 

```


---

---
title: "[USACO12DEC] Crazy Fences S"
layout: "post"
diff: 省选/NOI-
pid: P3061
tag: ['计算几何', '2012', 'USACO']
---
# [USACO12DEC] Crazy Fences S
## 题目描述

After visiting a modern art museum, Farmer John decides to re-design his farm by moving all of the N (1 <= N <= 1000) fences between his pastures! Each fence is describe by a line segment in the 2D plane.  If two fences meet, they do so only at their endpoints.  Each fence touches exactly two other fences, one at both endpoints.

FJ has C cows (1 <= C <= 1000) on his farm.  Each cow resides at a point in the 2D plane that is not on any fence, and no two cows reside at the same point.  Two cows are said to be in the same community if one could walk to the other without touching any fences.  Please help FJ determine the size of the largest community.

 
在访问了一个现代美术馆后，约翰农夫决定移动n个在他的牧场之间的栅栏来


重新设计他的农场。每个栅栏用一个2D平面的线段来描述。两个栅栏只有在他们的端点才会相遇。每个栅栏在两个端点接触其他的两个栅栏。


约翰农夫有c头牛在他的农场。每头牛住在2D平面的不在任何栅栏的一个点，并且没有两头牛在同一个点。如果两头牛可以不接触任何栅栏地走到一起，他们就是在同一个社区。请确定最大的社区的牛的数量。

## 输入格式

\* Line 1: Two space-separated integers N and C.

\* Lines 2..1+N: Each line contains four integers: x1, y1, x2, y2, indicating a fence from point (x1,y1) to point (x2,y2).  All coordinates are integers in the range 0..1,000,000.

\* Lines 2+N..1+N+C: Each line contains two integers x and y describing the location of a cow.  All coordinates are integers in the range 0..1,000,000.

## 输出格式

\* Line 1: The number of cows in the largest community.

## 样例

### 样例输入 #1
```
10 4 
0 0 10 0 
10 0 10 10 
0 0 0 10 
10 10 0 10 
8 8 9 8 
9 8 8 9 
8 9 8 8 
2 7 3 2 
3 2 7 5 
7 5 2 7 
15 3 
1 4 
4 5 
7 1 

```
### 样例输出 #1
```
2 

```
## 提示

There are 10 fences and 4 cows.  The fences form a square containing two triangles.


Cows #2 and #4 belong to the same community.  Cows #1 and #3 are each members of a community of size 1.


感谢@kczno1 提供翻译



---

---
title: "[USACO15FEB] Fencing the Herd G"
layout: "post"
diff: 省选/NOI-
pid: P3122
tag: ['计算几何', '2015', 'USACO', 'cdq 分治', '凸包']
---
# [USACO15FEB] Fencing the Herd G
## 题目描述

Farmer John 需要你帮助他决定在哪里建造形状是一条无限长的直线的栅栏来限制他的牛的活动。他选出了几个可能的建造栅栏的位置，你需要帮助他判断哪些栅栏是有用的。一个栅栏是有用的当且仅当所有奶牛都在栅栏的同一侧。（如果有牛群在栅栏所在的直线上，那么栅栏是没用的），Farmer John 将会多次询问你一个栅栏是否有用，如果这个栅栏是有用的，需要输出 `YES`，反之输出 `NO`。

另外，Farmer John 也可能会带来一些新的奶牛加入这个牛群。一头牛加入之后，以后的所有询问中，这头牛也需要与其它的牛在栅栏的同一侧。

## 输入格式


第一行，两个正整数 $n,q$，表示初始时牛群的数量与询问个数；

后 $n$ 行，每行两个整数 $x,y$，表示一个牛群的初始位置；

后 $q$ 行，每行多个整数，表示一次询问，询问的格式如下：

- 1 $x$ $y$：表示一个新的牛群加入了牧场，驻留在 $(x,y)$ 上；
- 2 $A$ $B$ $C$：表示 Farmer John 询问栅栏 $Ax+By=C$ 是否有用。
## 输出格式

对于每个 $2$ 类型的询问，如果栅栏有用，输出 `YES`，否则输出 `NO`。

## 样例

### 样例输入 #1
```
3 4 
0 0 
0 1 
1 0 
2 2 2 3 
1 1 1 
2 2 2 3 
2 0 1 1 

```
### 样例输出 #1
```
YES 
NO 
NO 


```
## 提示

直线 $2x+2y=3$ 使得初始的三个牛群都在同侧；然而在该栅栏另一侧的牛群 $(1,1)$ 的加入使得它没有用了。

直线 $y=1$ 没用因为牛群 $(0,1)$，$(1,1)$ 恰好在它上面。

---

对于 $100\%$ 的数据，保证 $1\leq n\leq 10^5$，$1\leq q\leq 10^5$，所有牛群的坐标都各不相同且满足 $-10^9\leq x,y\leq 10^9$，$-10^9\leq A,B\leq 10^9$，$-10^{18}\leq C\leq 10^{18}$。

数据保证不存在栅栏满足 $A=B=0$。


---

---
title: "[HNOI2011] 数矩形"
layout: "post"
diff: 省选/NOI-
pid: P3217
tag: ['计算几何', '2011', '湖南', '枚举', '排序']
---
# [HNOI2011] 数矩形
## 题目描述

最近某歌手在研究自己的全球巡回演出计划，他将所有心仪的城市都用平面上的一个点来表示，并打算从中挑选出 4 个城市作为这次巡回演出的地点。

为了显示自己与众不同，他要求存在一个矩形使得挑选出的 4 个点恰好是这个矩形的 4 个顶点，并且希望这个矩形的面积最大。

这可急坏了其经纪人，于是他向全球歌迷征集方案，当然你这位歌迷一定不会错过这个机会。

## 输入格式

从文件input.txt中读入数据，输入文件的第一行是一个正整数$N$，表示平面上点的个数(即某歌手心仪的城市数)。接下来的$N$行，每行是由空格隔开的两个整数$X_i$和$Y_i$,表示其对应点的坐标。20%的数据满足$N\leq 500$，100%的数据满足$N\leq 1500$，$-10^8\leq X_i,Y_i\leq 10^8$，且输入数据保证答案存在。

## 输出格式

输出文件 output.txt 仅包含一个非负整数，表示最大的矩形面积。

## 样例

### 样例输入 #1
```
8
-2 3
-2 -1
0 3
0 -1
1 -1
2 1 
-3 1 
-2 1

```
### 样例输出 #1
```
10
```


---

---
title: "[POI 2005] AKC-Special Forces Manoeuvres"
layout: "post"
diff: 省选/NOI-
pid: P3428
tag: ['计算几何', '2005', 'POI（波兰）']
---
# [POI 2005] AKC-Special Forces Manoeuvres
## 题目描述

一个秘密组织正在沙漠中举行一次军事演习。本次演习的目标是拆除隐藏在沙漠中的一个炸弹。

演习的第一部分是空降作战。每个士兵**按照一定的顺序**从悬停在沙漠上空的直升机上跳下。着陆时，每个士兵都会停在他所在的着陆点。

每个空降兵都有一个生存半径。如果炸弹与他的距离小于或等于这个生存半径的话，空降兵便会牺牲自己引爆炸弹。指挥官希望能派出尽可能少的士兵，但他希望在**最坏情况下**至少有一个士兵能够生还。

整个沙漠可以抽象为一个平面，每个士兵的着陆点可以用一个坐标 $(x,y)$ 表示，他的生存半径我们设为 $r$。所有士兵的信息按照他们跳伞时的顺序给出，即第 $i$ 个士兵跳伞时，前 $i-1$ 个士兵都已经着陆。

你的任务是：从标准输入读入所有士兵的信息，输出最少需要派出的士兵数量。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，第 $i$ 行包含三个整数 $x_i,y_i,r_i$，代表第 $i$ 个士兵的着陆坐标为 $(x_i,y_i)$，生存半径为 $r_i$。
## 输出格式

如果无法让至少一个士兵生还的话，输出 `NIE`。

否则输出一个整数，代表至少需要派出的士兵数量。
## 样例

### 样例输入 #1
```
5
2 2 4
7 2 3
4 3 1
5 7 1
8 7 1
```
### 样例输出 #1
```
4
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/8xbga77o.png)

最坏情况下炸弹位于 $(5,3)$，前三个士兵都会被炸死，第四个士兵会生还。


---

---
title: "[POI 2007] OSI-Axes of Symmetry"
layout: "post"
diff: 省选/NOI-
pid: P3454
tag: ['字符串', '计算几何', '2007', 'POI（波兰）', 'KMP 算法']
---
# [POI 2007] OSI-Axes of Symmetry
## 题目描述

Little Johnny - a well-respected young mathematician - has a younger sister, Justina. Johnny likes hissister very much and he gladly helps her with her homework, but, like most scientific minds, he does mindsolving the same problems again. Unfortunately, Justina is a very diligent pupil, and so she asks Johnny toreview her assignments many times, for sake of certainty. One sunny Friday, just before the famous LongMay Weekend1 the math teacher gave many exercises consisting in finding the axes of symmetry of variousgeometric figures. Justina is most likely to spend considerable amount of time solving these tasks. LittleJohnny had arranged himself a trip to the seaside long time before, nevertheless he feels obliged to help hislittle sister. Soon, he has found a solution - it would be best to write a programme that wouldease checking Justina's solutions. Since Johnny is a mathematician, not a computer scientist, and you are hisbest friend, it falls to you to write it.

## Task

Write a programme that:

- reads the descriptions of the polygons from the standard input,

- determines the number of axes of symmetry for each one of them,

- writes the result to the standard output.


给定一个多边形，求对称轴数量。

## 输入格式

In the first line of the input there is one integer $t$ ($1 \le t \le 10$) - it is the number of polygons, for which the number of axes of symmetry is to be determined. Next, $t$ descriptions of the polygons follow. The first line of each description contains one integer $n$ ($3 \le n \le 100\ 000$) denoting the number of vertices of the polygon. In each of the following $n$ lines there are two integers $x$ and $y$ ($-100\ 000\ 000 \le x, y \le 100\ 000\ 000$) representing the coordinates of subsequent vertices of the polygon. The polygons need not be convex, but they have no self-intersections - any two sides have at most one common point - their common endpoint, if they actually share it. Furthermore, no pair of consecutive sides is parallel.

## 输出格式

Your programme should output exactly $t$ lines, with the $k$'th line containing a sole integer $n_k$ - the number of axes of symmetry of the $k$'th polygon.

## 样例

### 样例输入 #1
```
2
12
1 -1
2 -1
2 1
1 1
1 2
-1 2
-1 1
-2 1
-2 -1
-1 -1
-1 -2
1 -2
6
-1 1
-2 0
-1 -1
1 -1
2 0
1 1
```
### 样例输出 #1
```
4
2
```
## 题目翻译

### 题目描述

Johnny 是一位非常年轻的数学家，但他此刻正在为他妹妹的数学作业烦恼。

这个周末，他的妹妹需要完成一项作业，计算各种几何图形的对称轴数量。因为 Johnny 这个周末想要去海边旅行，所以他希望他的妹妹能尽快完成这项作业。

于是他找到了擅长编程的你，你一定能帮助他完成这项任务的！

### 输入格式

输入包含多组数据。

第一行包含一个整数 $t$，代表数据的组数。

对于每组数据，第一行一个整数 $n$，代表多边形的顶点数。

接下来 $n$ 行，每行两个整数 $x_i,y_i$，代表每个顶点的坐标。

输入中的第 $i$ 个顶点会与第 $i+1$ 个顶点连一条边。特别地，输入中的第 $n$ 个顶点会与第一个顶点连一条边。

输入给出的多边形**不保证**是凸多边形，但是保证任意两条边只会在端点处相交，且任意两条相邻的边不共线。

### 输出格式

对于每组数据，输出一行一个整数，即多边形对称轴的数量。

### 数据范围

$1 \leq t \leq 10$，$3 \leq n \leq 10^5$，$-10^8 \leq x_i,y_i \leq 10^8$。


---

---
title: "[POI 2008] TRO-Triangles"
layout: "post"
diff: 省选/NOI-
pid: P3476
tag: ['计算几何', '2008', 'POI（波兰）', '深度优先搜索 DFS', '叉积']
---
# [POI 2008] TRO-Triangles
## 题目描述

$n$ pairwise disjoint points in the plane are given ($n\ge 3$).

There are $\dfrac{n(n-1)(n-2)}{6}$ triangles whose    vertices are some pairwise different points among them    (including degenerate triangles, i.e. ones whose vertices are collinear).

We want to calculate the sum of areas of all the triangles with vertices    in the given points.

Those parts of the plane that belong to many triangles are to be calculated    multiple times. We assume that the area of degenerate triangles (i.e. those    with collinear vertices) is zero.

<Task>

Write a programme that:

reads from the standard input the coordinates of the points in the plane,                 determines the sum of the areas of all the triangles with vertices in       the given points,                  prints out the result to the standard output.



## 输入格式

In the first line of the standard input there is one integer $n$ ($3\le n\le 3000$) denoting the number of selected points.

Each of the following $n$ lines contains two integers $x_i$ and $y_i$ ($0\le x_i,y_i\le 10^4$) separated by a single space and denoting   the coordinates of the $i^\mathrm{th}$ point (for $i=1,2,\cdots,n$).

No pair (ordered) of coordinates appears more than once.

## 输出格式

In the first and only line of the standard output there should be one   real number equal to the sum of the areas of all the triangles with   vertices in the given points. The outcome should be printed out with   exactly one digit after dot and should not differ from the correct value   by more than $0.1$.

## 样例

### 样例输入 #1
```
5
0 0
1 2
0 2
1 0
1 1

```
### 样例输出 #1
```
7.0

```
## 题目翻译

给定平面上的一些点，求这些点能组成的所有三角形的面积之和。


---

---
title: "[POI 2009] WSP-Island"
layout: "post"
diff: 省选/NOI-
pid: P3493
tag: ['计算几何', '2009', 'POI（波兰）', 'Special Judge', '半平面交']
---
# [POI 2009] WSP-Island
## 题目描述

Byteasar is the king of Byteotia, an island in The Ocean of Happiness.

The island is a convex shape, and all the towns of Byteotia are located on the shore.

One of these towns is Byteburg, the famous capital of Byteotia.

Every pair of towns is connected by a road that goes along the line segment between the towns.

Some roads that connect different pairs of towns intersect - there is a crossroad at each such intersection.

Bitratio, Byteasar's rival to the throne, had hatched a sordid plot.

While Byteasar was travelling from the capital to an adjacent town, Bitratio's people seized Byteburg.

Now Byteasar has to return to Byteburg as soon as possible in order to restore his rule.

Unfortunately, some of the roads are controlled by Bitratio's guerrilla.

Byteasar cannot risk the use of such roads, he can however cross them at the crossroads.

Needless to say, he has to travel along the roads and hence turn only at the crossroads, for otherwise the journey would take far too long.

Byteasar's loyal servants have informed him which roads are safe.

Byteasar believes your loyalty, and thus entrusts you with a task to find the shortest safe route from the town he is currently in to Byteburg.

Byteotia岛屿是一个凸多边形。城市全都在海岸上。按顺时针编号1到n。任意两个城市之间都有一条笔直的道路相连。道路相交处可以自由穿行。有一些道路被游击队控制了，不能走，但是可以经过这条道路与未被控制的道路的交点。问从城市1到n的最短距离。

## 输入格式

In the first line of the standard input two integers ![](http://main.edu.pl/images/OI16/wsp-en-tex.1.png) and ![](http://main.edu.pl/images/OI16/wsp-en-tex.2.png) are given     (![](http://main.edu.pl/images/OI16/wsp-en-tex.3.png), ![](http://main.edu.pl/images/OI16/wsp-en-tex.4.png)),     separated by a single space,     that denote respectively: the number of towns and      the number of roads controlled by Bitratio's guerrilla.

Let us number the towns from ![](http://main.edu.pl/images/OI16/wsp-en-tex.5.png) to ![](http://main.edu.pl/images/OI16/wsp-en-tex.6.png) starting from Byteburg      and moving clockwise along the shore.

Bytesar is currently in the town no. ![](http://main.edu.pl/images/OI16/wsp-en-tex.7.png).

Each of the following ![](http://main.edu.pl/images/OI16/wsp-en-tex.8.png) lines holds a pair of integers ![](http://main.edu.pl/images/OI16/wsp-en-tex.9.png) and ![](http://main.edu.pl/images/OI16/wsp-en-tex.10.png)      (![](http://main.edu.pl/images/O…

## 输出格式

Your programme is to print out one floating point number     to the standard output:

the length of the shortest safe route leading from the town no. ![](http://main.edu.pl/images/OI16/wsp-en-tex.19.png)     to Byteburg.

The absolute difference between the number returned and the correct one  has to be at most ![](http://main.edu.pl/images/OI16/wsp-en-tex.20.png).

## 样例

### 样例输入 #1
```
6 9
-12 -10
-11 6
-4 12
6 14
16 6
18 -2
3 4
1 5
2 6
2 3
4 5
3 5
1 3
3 6
1 6

```
### 样例输出 #1
```
42.0000000000

```
## 提示

spj-
## 题目翻译

### 题目大意

Byteotia岛屿是一个凸多边形,城市全都在海岸上,按顺时针编号  $1$ 到  $n$ 。

任意两个城市之间都有一条笔直的道路相连。道路相交处可以自由穿行。

有一些道路被游击队控制了，不能走，但是可以经过这条道路与未被控制的道路的交点。

问从城市  $1$ 到  $n$ 的最短距离。

### 输入格式

第一行两个正整数  $n$ 和  $m$ 表示城市数和被控制的道路数。

接下来  $n$ 行，每行两个整数  $x,y$ 表示每个城市的坐标。

接下来  $m$ 行，每行两个整数  $u,v$ 。表示城市  $u$ 和  $v$ 之间的道路不能走，数据保证有解。

### 输入格式

输出一个实数，表示从  $1$ 到  $n$ 最短道路距离，误差在  $10^{-5}$ 以内均算正确。

### 数据范围和提示

 $3 \le n \le 10^5,1 \le m \le 10^6,|x|,|y| \le 10^6$

by Rainy7 & Piwry


---

---
title: "[CERC2016] 凸轮廓线 Convex Contour"
layout: "post"
diff: 省选/NOI-
pid: P3680
tag: ['字符串', '数学', '计算几何', '2016', 'Special Judge', '凸包']
---
# [CERC2016] 凸轮廓线 Convex Contour
## 题目描述

一些几何图形整齐地在一个网格图上从左往右排成一列。它们占据了连续的一段横行，每个位置恰好一个几何图形。每个图形是以下的三种之一：


1. 一个恰好充满单个格子的正方形。


2. 一个内切于单个格子的圆。


3. 一个底边与格子重合的等边三角形。


 ![](https://cdn.luogu.com.cn/upload/pic/4685.png) 

已知每个格子的边长都为 $1$，请求出这些几何图形的凸包的周长。
## 输入格式

第一行包含一个正整数 $n$，表示几何图形的个数。

第二行包含 $n$ 个字符，从左往右依次表示每个图形，`S` 表示正方形，`C` 表示圆形，`T` 表示等边三角形。

## 输出格式

输出一行一个实数，即凸包的周长。与答案的绝对或相对误差不超过 $10^{-6}$ 时被认为是正确的。
## 样例

### 样例输入 #1
```
4
TSTC
```
### 样例输出 #1
```
9.088434417

```
## 提示

对于 $100\%$ 的数据，$1 \le n \le 20$。


---

---
title: "[JSOI2010] 冷冻波"
layout: "post"
diff: 省选/NOI-
pid: P4048
tag: ['计算几何', '2010', '各省省选', '江苏', '枚举']
---
# [JSOI2010] 冷冻波
## 题目描述

WJJ喜欢“魔兽争霸”这个游戏。在游戏中，巫妖是一种强大的英雄，它的技能Frozen Nova每次可以杀死一个小精灵。我们认为，巫妖和小精灵都可以看成是平面上的点。

当巫妖和小精灵之间的直线距离不超过R，且巫妖看到小精灵的视线没有被树木阻挡（也就是说，巫妖和小精灵的连线与任何树木都没有公共点）的话，巫妖就可以瞬间杀灭一个小精灵。

在森林里有N个巫妖，每个巫妖释放Frozen Nova之后，都需要等待一段时间，才能再次施放。不同的巫妖有不同的等待时间和施法范围，但相同的是，每次施放都可以杀死一个小精灵。

现在巫妖的头目想知道，若从0时刻开始计算，至少需要花费多少时间，可以杀死所有的小精灵？

## 输入格式

输入文件第一行包含三个整数N、M、K(N,M,K<=200)，分别代表巫妖的数量、小精灵的数量和树木的数量。

接下来N行，每行包含四个整数x, y, r, t，分别代表了每个巫妖的坐标、攻击范围和施法间隔（单位为秒）。

再接下来M行，每行两个整数x, y，分别代表了每个小精灵的坐标。

再接下来K行，每行三个整数x, y, r，分别代表了每个树木的坐标。

输入数据中所有坐标范围绝对值不超过10000，半径和施法间隔不超过20000。

## 输出格式

输出一行，为消灭所有小精灵的最短时间（以秒计算）。如果永远无法消灭所有的小精灵，则输出-1。

## 样例

### 样例输入 #1
```
2 3 1
-100 0 100 3
100 0 100 5
-100 -10
100 10
110 11
5 5 10
```
### 样例输出 #1
```
5
```


---

---
title: "封兽鵺的激光游戏"
layout: "post"
diff: 省选/NOI-
pid: P4276
tag: ['模拟', '计算几何', '枚举']
---
# 封兽鵺的激光游戏
## 题目背景

#盛大的宴会已经开始
![](https://cdn.luogu.com.cn/upload/pic/15071.png)
## 题目描述

在你的帮助下，萃香终于在一天内送出了所有的请柬。

夜幕低垂，随着由河城荷取提供的烟花"嗖"的一声蹿上天际，这场盛大的宴会终于如期开始。

顷刻之间，偌大的会场就已经被大家的欢声笑语充满：萃香和勇仪把酒言欢，散发着醉醺醺的酒香；帕秋莉和爱丽丝拽着魔理沙的两只胳膊争论着先逛哪边；琪露诺和大妖精在地上写写画画钻研着数学难题......一切都显得和谐而美满。

可是，随着会场愈发热闹，宴会的举办者萃香总感觉还是少了些什么，转念一想，她方才发觉自己没有准备游戏活动。没有游戏的宴会又怎能叫做宴会？为了解决这个严重的问题，萃香放下了酒葫芦，找到了路边的封兽鵺请她帮忙。

这可愁死封兽鵺啦！只擅长搞事情和打马赛克的她苦思冥想，终于想出了一个好主意，于是她将自己的UFO翻出来一些，再找圣白莲借几束激光，而下面就是封兽鵺制定的游戏规则：

封兽鵺在平面上放置了一些实心的质量均匀的UFO(可视为凸多边形)，由于她的能力有限，所以这些UFO最多只有五条边。现在你可以从一给定点向任意方向发射一束激光(x轴正方向为0°，y轴正方形为90°，保证发射角度为两位小数，即激光从0°开始旋转，每次旋转0.01°)，激光碰到UFO的边界便会发生反射，且激光每反射一次能量便会增加w(初始能量为0)，这里要注意的是，每当一条边被激光打中过一次后便会失去反射的能力变成一条可以直接透过的边，这时候你的激光可以直接穿进UFO的内部从内部进行反射。

如果你还没有理解，封兽鵺已经贴心的为你准备了下面这张图：
![](https://cdn.luogu.com.cn/upload/pic/15112.png)

本来唯恐天下不乱的封兽鵺想让激光射出时能量最大，但是萃香担心会场被破坏而将"能量最大"改为"能量最接近一整数E"。同时为了保证游戏的难度，封兽鵺会在游戏开始前将每个UFO绕重心顺时针旋转k*90°。

现在，轮到了你参加这个游戏，如果你射出激光的角度与封兽鵺的答案相符，那么你就会获得两份奖励——100分和封兽鵺的写真集！

当然，拥有电脑的你当然不会一次一次去试，而是通过编程预先解决这个问题，然后真正实践的时候直接用最优解拔得头筹。
## 输入格式

第一行一个整数n，为UFO的数量。

之后n行每行一个整数m，随后有m个实数对x[i],y[i]表示按顺时针顺序给出的UFO的m个顶点。

之后n行每行一个整数k，表示将该UFO顺时针旋转k*90°。

第2n+2行两个整数w和E，分别为每次反射激光的能量增量及规定的接近量。

最后一行两个实数x0，y0表示激光的射出点。
## 输出格式

一个实数d，保留到两位小数，表示使激光出射能量最接近E的出射角度。(如果有多个解符合题意，请输出角度最小的那个)
## 样例

### 样例输入 #1
```
2
4 0 0 0 4 4 4 4 0
3 8 0 12 4 12 0
0 
0
1 2
5 5
```
### 样例输出 #1
```
300.97
```
## 提示

【样例解释】：

如图所示，当激光射出偏角为300.97度时恰好能反射两次，E1-2*w=2=E，符合题意
![](https://cdn.luogu.com.cn/upload/pic/15105.png)

#你需要特别注意的一些事:
1. 当一束激光碰到UFO顶点的时候不认为它们相撞
2. 多边形不会重叠，初始激光射出点不会在UFO上或UFO内
3. 不要在这里讲科学，所以激光可以射到UFO内部进行反射


【数据范围】：

![](https://cdn.luogu.com.cn/upload/pic/15115.png)

奖励：

![](https://cdn.luogu.com.cn/upload/pic/15074.png)

(没错就是zun绘写真集，如果你AC了此题就可以获得)



---

---
title: "[WC2010] 能量场"
layout: "post"
diff: 省选/NOI-
pid: P4293
tag: ['计算几何', '2010', 'Special Judge', '凸包', 'WC']
---
# [WC2010] 能量场
## 题目背景


官方spj：https://www.luogu.org/paste/03wjc4ne

spj provider: @hehezhou 
## 题目描述

物理学家栋栋最近在研究一个能量场。在这个能量场中有n个粒子，每个粒子都有两个属性：质量m和结合系数c。  

栋栋发现，在这个能量场中，每个粒子都有两极，N极和S极。两个粒子相遇时，符合“同极相斥，异极相吸”的原则，只能是一个粒子的N极和另一个粒子的S极连接到一起。当质量为ma，结合系数为ca的粒子a的N极与另一个质量为mb，结合系数为cb的粒子b的S极直接连接时，可以产生大小为  $m_a m_b (c_a - c_b)$  的结合能量。    

请解决以下两个问题：  
1. 在能量场的n个粒子中哪两个粒子直接连接的能量最大。  
2. 栋栋发明了一种方法，能选择其中的任意k个粒子p1, p2, …, pk，将pi的 N极与pi+1的S极连接(1 ≤ i < k)， pk的N极与p1的S极连接， 其中p1, p2, …, pk两两不同。k可以在1至n中任意取值，如使用栋栋的这种方法连接，选择哪些粒子可以得到最大的能量。
## 输入格式

第一行包含一个整数n，表示粒子的个数。 

 接下来n行，每行两个实数，第i+1行的两个实数表示第i个粒子的质量mi和结合系数ci。(0< mi, ci <10^5)
## 输出格式

第一行包含两个整数a, b，表示将粒子a的N极与粒子b的S极连接可以得到最大的能量。  

第二行包含一个整数k，表示第二问中要得到最大的能量需要多少个粒子。 第三行包含k个整数，表示p1, p2, …, pk，即第二问中的最优方案。
## 样例

### 样例输入 #1
```
4  
1.0 2.0 
3.0 1.0 
5.0 4.0 
2.0 2.0
```
### 样例输出 #1
```
3 2 
3  
1 3 2
```
## 提示

【样例说明】  
对于第一问，第三个粒子的N极与第二个粒子的S极连接，能得到的能量为$5\times3\times(4-1) = 45$。  

对于第二问，顺次连接1, 3, 2号粒子，能量为  $1\times5\times(2-4) + 5\times3\times(4-1) + 3\times1\times(1-2) = 32$。 

【数据规模】  

10%的数据，n ≤ 8； 

20%的数据，n ≤ 15； 

40%的数据，n ≤ 1 000；

50%的数据，n ≤ 5 000； 

100%的数据，n ≤ 50 000。 

【评分标准】  

此题可能有多解，如果用你的解产生的能量与参考答案的绝对误差或相对误差小于10–5，则得满分。否则不得分。  对于本题，每问的分数各占50%。如果你的输出任何一问的格式或结果不正确，则不得分；否则如果其中的一问正确，则得到该测试点50%的分数；如果两问都正确，得到该测试点100%的分数。


---

---
title: "[COCI 2009/2010 #6] XOR"
layout: "post"
diff: 省选/NOI-
pid: P4515
tag: ['计算几何', '2009', '容斥原理', 'COCI（克罗地亚）']
---
# [COCI 2009/2010 #6] XOR
## 题目描述

坐标系下有若干个等腰直角三角形，且每个等腰直角三角形的直角顶点都在左下方，两腰与坐标轴平行。被奇数个三角形覆盖的面积部分为灰色，被偶数个三角形覆盖的面积部分为白色，如下图所示。
![](https://cdn.luogu.com.cn/upload/pic/18669.png)
已知 $N$个等腰直角三角形的顶点坐标及腰长，求灰色部分面积。

Mirko and Slavko have built their own LED display. The display is initially
white. During each of the $N$ parts of the testing phase, Mirko attached three
electrodes to the display in such way that they formed a right isosceles
triangle. He noticed that, after attaching the electrodes, all pixels in the
enclosing triangle are inverted (white pixels become black, and black pixels
become white).

Watching Mirko play with the electrodes, Slavko observed interesting shapes
emerging on the screen. Mathematically inclined as he is, first thing that
crossed his mind was how to calculate total area covered by black pixels. Help
him by writing a program to do just that!
## 输入格式

输入第一行包含一个整数 $N$，表示等腰直角三角形数量。

接下来 $N$行，每行三个整数 $X, Y, R$，分别表示等腰直角三角形的顶点坐标 $(X, Y)$与腰长 $R$。

First line of input contains an integer $N(1 \leq N \leq 10)$, number of triangles
formed by Mirko's fiddling with electrodes. Each of the following $N$ lines
contains three integers $X, Y$ and $R (1 \leq X, Y, R \leq 10^6
)$, describing a triangle. $(X, Y)$ are the coordinates of the lower left corner of the triangle, while $R$ represents the length of the two sides of the triangle.
## 输出格式

输出包含一个实数，表示灰色部分面积。保留1位小数。

The first and only line of output should contain the area covered by black
pixels, rounded to one decimal place.
## 样例

### 样例输入 #1
```
3
1 1 2
7 1 6
5 3 4
```
### 样例输出 #1
```
24.0
```
### 样例输入 #2
```
5
5 5 99
5 5 99
5 5 99
5 5 99
5 5 99
```
### 样例输出 #2
```
4900.5
```
### 样例输入 #3
```
4
5 5 99
5 5 99
5 5 99
5 5 99
```
### 样例输出 #3
```
0.0
```
## 提示

$1 \leq N \leq 10, 1 \leq X, Y, R \leq 10^6$


---

---
title: "[CEOI 2011] Balloons"
layout: "post"
diff: 省选/NOI-
pid: P4697
tag: ['计算几何', '2011', 'Special Judge', 'CEOI（中欧）', '单调栈']
---
# [CEOI 2011] Balloons
## 题目描述

有 $n$ 个气球，他们一开始都是空的。

接下来，它们会按照从 $1$ 到 $n$ 的顺序依次充气，其中第 $i$ 个气球与地面在 $x_i$ 位置接触。

当气球碰到碰到前面的某个气球，或者达到半径最大限制时，就会停止充气。其中第 $i$ 个气球的半径最大限制为 $r_i$。

现在请你求出，每个气球最终半径是多少。
## 输入格式

第一行一个正整数 $n$，表示气球个数。

接下来 $n$ 行，每行两个空格隔开的整数 $x_i,r_i$。
## 输出格式

输出 $n$ 行，每行一个浮点数，第 $i$ 行的浮点数表示最终第 $i$ 个气球的半径。

你的答案会被判为正确，当且仅当与答案的绝对误差不超过 $10^{-3}$​​。
## 样例

### 样例输入 #1
```
3
0 9
8 1
13 7
```
### 样例输出 #1
```
9.000
1.000
4.694
```
## 提示

对于 $100\%$ 的数据，保证 $1\le n\le 200\ 000;0\le x_i\le 10^9;1\le r_i\le 10^9;x_1< x_2< \cdots < x_n$。


---

---
title: "[JSOI2016] 炸弹攻击2"
layout: "post"
diff: 省选/NOI-
pid: P5545
tag: ['计算几何', '2016', '各省省选', '江苏']
---
# [JSOI2016] 炸弹攻击2
## 题目背景

还记得那款题为炸弹攻击的塔防游戏吗？这款游戏出了续作，炸弹的威力大大加强了。
## 题目描述

游戏的地图是一个二维平面。JYY 的阵地位于$x$轴下方，而所有的敌人目前都位于$x$轴上方。

在 JYY 的阵地中有建有$T$个激光塔和$S$个发射源。其中第$i$个防御塔$T_i$的坐标为$(tx_i,ty_i)$，第$i$个发射源$S_i$的坐标为$(sx_i,sy_i)$。

地图上有$D$个敌人，第$i$个敌人$D_i$的坐标为$(dx_i,dy_i)$。

两座激光塔可以相互连接形成能量墙。发射源朝向敌人发出的能量如果穿过了能量墙，可以得到巨大的加强而变为超级射线并瞬间消灭敌人。

JYY 想知道他有多少种可以可以发出超级射线的攻击方案。

具体来说，一个可以发出超级射线的攻击方案为一个由四个点组成的集合：{$T_i,T_j,S_k,D_l$}，满足$1$$\leq$$i$$<$$j$$\leq$$T$$,$$1$$\leq$$k$$\leq$$S$$,$$1$$\leq$$l$$\leq$$D$，并且线段$T_iT_j$和线段$S_kD_l$相交。

游戏设定保证在这$T$$+$$D$$+$$S$个点中，不存在重点也不存在三点共线。
## 输入格式

第一行包含一个正整数$D$；

接下来$D$行，每行包含两个整数$dx_i,dy_i$，表示一个敌人的坐标；

第$D$$+$$1$行包含一个整数$S$；

接下来$S$行，每行包含两个整数$sx_i,sy_i$，表示一个发射源的坐标；

第$D$$+$$S$$+$$1$行包含一个整数$T$；

接下来$T$行，每行包含两个整数$(tx_i,ty_i)$，表示一个激光塔的坐标。
## 输出格式

输出一行一个整数，可以发出超级射线的攻击方案个数。
## 样例

### 样例输入 #1
```
3
1 12
10 30
30 10
1
10 -10
4
2 -11
9 -1
11 -1
15 -14
```
### 样例输出 #1
```
7
```
## 提示

对于$20$%的数据，满足$D,S,T$$\leq$$30$；

对于$50$%的数据，满足$D,S,T$$\leq$$150$；

对于$100$%的数据，满足$1$$\leq$$D,S,T$$\leq$$800$$,$$dy_i$$>$$0$$,$$sy_i$$,$$ty_i$$<$$0$，所有坐标绝对值不超过$10^9$。


---

---
title: "[BJ United Round #3] 观察星象"
layout: "post"
diff: 省选/NOI-
pid: P5549
tag: ['计算几何', '二分', '北京', 'Special Judge', '随机化']
---
# [BJ United Round #3] 观察星象
## 题目描述

EI 在用望远镜观察星星，星空中共有  $n$ 个星星，每个星星观察起来有一个二维直角坐标 $(x,y)$。  

他的望远镜如果定位在 $(x_0,y_0)$ 处，可以看到所有 $(x_0-x)^2 + (y_0-y)^2 \le r^2$ 的星星。  

望远镜的大小 $r$ 是可以调整的，EI 想知道如果他要至少看到 $m$ 个星星，至少需要把 $r$ 设置到多大？
## 输入格式

第一行两个正整数 $n,m$，表示星星的数量和要求看到的星星数量。  
接下来 $n$ 行，每行两个整数 $x,y$，表示一个星星的坐标。  
保证星星坐标两两不同。
## 输出格式

输出一行一个正实数，表示望远镜的最小半径。  
令你的答案为 $a$，标准答案为 $b$，若 $\frac{|a-b|}{\max(1,b)} \le 10^{-6}$  
( 即绝对误差或者相对误差不超过 $10^{-6}$ ) 即为正确。
## 样例

### 样例输入 #1
```
4 3
0 0
1 1
2 3
3 3
```
### 样例输出 #1
```
1.41421356
```
## 提示

| 子任务编号 | $n$ | $m$ | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leq 50$ | $\leq n$ | $10$ |
| $2$ | $\leq 200$ | $\leq n$ | $15$ |
| $3$ | $\leq 700$ | $\leq n$ | $15$ |
| $4$ | $\leq 2000$ | $= n$ | $20$ |
| $5$ | $\leq 2000$ | $\leq n$ | $40$ |


对于 $100\%$ 的数据，保证：  
$2 \le m \le n  \le 2000$  
$|x|,|y| \le 10^4$

By：EntropyIncreaser


---

---
title: "[CmdOI2019] 高塔与晶石"
layout: "post"
diff: 省选/NOI-
pid: P5571
tag: ['计算几何']
---
# [CmdOI2019] 高塔与晶石
## 题目背景

**温馨提示 : 请注意常数因子对程序效率带来的影响 + 本题特殊的空间限制**

几何王国之中，矗立着$n$座古老的高塔，传说，它们是这片净土的守护者。

随着几何学日新月异的发展，王国的繁荣引来了烈炎深处的恐怖：动点P。

驯服动点恶龙的英雄笛卡尔尚未出现，几何王国的领主决定固守静态几何的阵地。


## 题目描述

他得到了静态几何的三颗智慧晶石(里面当然是神级数学题啦)，并且可以把它们安放在高塔之中。

三颗安放着晶石的高塔，可以保护其围成的三角形内部不受侵入。

但是，如果晶石围成的三角型面积太大，防线将会十分容易被击破。

如果三角型面积太小，其中能够产生的几何能量又不足以维持晶石的运作。

经过几天的推算，领主在认为， $\binom{n}{3}$ 种做法中,面积第 $k$ **小**的方案是最合适的。

(三角形面积可以为 $0$)

他对这个结果很不放心，于是拜托单手虐爆无数几何题的你,来帮他计算这个面积具体是多少。
## 输入格式

第一行两个整数$n,k$，意义如题目所述。

后 $n$ 行，第 $i$ 行有两个数 $x_i,y_i$ ，表示 $i$ 号高塔的坐标。
## 输出格式

输出面积第 $k$ **小**方案对应面积的**2倍**，容易证明这一定是个整数。
## 样例

### 样例输入 #1
```
4 3
2 3
3 4
4 3
3 1
```
### 样例输出 #1
```
3
```
## 提示

| subtask编号 | 　n　 | 备注 | 分值 | 时限 |
| :--: | :--: | :--: | :--: | :--: |
| 1 | 200 | - | 15 | 1S |
| 2 | 500 | $k\leq10$ | 20 | 1S |
| 3 | 500 | $k\leq10000$ | 15 | 1S |
| 4 | 800 | - | 50 | 2S |

$1\leq x_i,y_i \leq 10^6$ , 所有坐标都是正整数 , 高塔的坐标不会重复。

**样例解释:**

![](https://cdn.luogu.com.cn/upload/image_hosting/y3is3hxv.png)


---

---
title: "[清华集训 2014] 文学"
layout: "post"
diff: 省选/NOI-
pid: P5928
tag: ['计算几何', '2015', '集训队互测', '凸包', '半平面交']
---
# [清华集训 2014] 文学
## 题目描述

巨酱和主席是一对好朋友。他们都很喜欢读书，经常一起阅读相关领域书籍，进行系统的学习。一天主席列出了一份列表，里面共 $p$ 本书，其中不乏《约翰克里斯多夫》，《名人传》等名著。作为一名在文学上有很高修养的知名青年，巨酱打算用尽量少的时间把这份列表中的所有书籍都读完。

作为一名文化人，巨酱阅读书籍的方式也与一般人不同。他使用一种叫做“批量阅读”的阅读方式。首先他根据自己的喜好，对每本书给出了个参数 $x,y$，其中 $i$ 本书的两个参数为 $x_i,y_i$。当然，由于巨酱独特的口味，可能有两本不同的书，它们的 $x,y$ 参数均相同。而每次阅读的时候，他会设置三个系数 $a, b, c$，所有满足 $a \times x+b \times y \leq c$ 的书籍都可以通过这次“批量阅读”读完，这次批量阅读总共需要 $w$ 的时间。
现在，巨酱有 $n$ 种 “批量阅读”的方案，第 $i$ 种“批量阅读”三个参数为 $a_i,b_i,c_i$，需要的时间为 $w_i$。现在巨酱打算从这 $n$ 种“批量阅读”中选出若干，使得巨酱可以用尽量少的时间读完所有的书。现在我们想知道，巨酱最少用多少时间？
## 输入格式

第一行两个正整数 $n,p$，分别表示“批量阅读”的方案数以及书的数量。

接下来 $n$ 行，每行四个整数，其中第 $i$ 行包含四个整数 $a_i,b_i,c_i,w_i$，表示第 $i$ 种“批量阅读”的方案。

接下来 $p$ 行，每行两个整数，其中第 $i$ 行包含两个整数 $x_i,y_i$，表示第 $i$ 本书的参数。
## 输出格式

一行一个整数，表示最少需要的时间。若无论如何也无法读完全部书籍，则输出 $−1$。
## 样例

### 样例输入 #1
```
4 3
-1 0 0 10
-1 -1 -1 2
-1 1 -1 2
-1 -2 -1 1
0 2
0 -2
1 0
```
### 样例输出 #1
```
3
```
## 提示

对于 $100\%$ 的测试数据，$1 \leq n,p \leq 100，−10^6 \leq a_i,b_i,c_i,x_i,y_i \leq 10^6， 0 \lt w_i \leq 10^6$，且保证对于任何一种“批量阅读”方案，其 $a_i$ 与 $b_i$ 不会同时为 $0$。且不存在 $i, j$（$i$ 不等于 $j$）使得 $a_i \times b_j=a_j \times b_i$。


---

---
title: "[CEOI 2008] Fence"
layout: "post"
diff: 省选/NOI-
pid: P5977
tag: ['动态规划 DP', '计算几何', '2008', 'CEOI（中欧）', '最短路', '凸包']
---
# [CEOI 2008] Fence
## 题目描述

在一个大小为 $1000\times 1000$ 的区域中，有 $n$ 个固定点, $m$ 棵树 。

现在你要建一个围栏来保护树，建它的费用为你选用的固定点的个数 $\times 20$ +你没有圈进围栏的树 $\times 111$。

现在希望这个值越小越好，求最小值。
## 输入格式

第一行给出 $n,m$。

接下来的 $n$ 行，给出固定的坐标。

接下来的 $m$ 行，给出树的坐标。
## 输出格式

输出最小费用。

## 样例

### 样例输入 #1
```
4 3
800 300
200 200
200 700
600 700
400 300
600 500
800 900
```
### 样例输出 #1
```
171
```
## 提示

对于 $100\%$ 的数据，$3\le N,M\le 100$。

----

## 样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/7vebu0t2.png)


---

---
title: "轴对称"
layout: "post"
diff: 省选/NOI-
pid: P6027
tag: ['计算几何', '2020', 'Special Judge']
---
# 轴对称
## 题目背景

小 W 学习了轴对称变换。
## 题目描述

小 W 觉得轴对称变换实在太好玩了，于是在平面上随机点了 $n$ 个点 $A_1,A_2,\cdots,A_n$，然后进行了一系列轴对称变换，得到了 $B_1,B_2,\cdots,B_n$ 这 $n$ 个点，其中 $A_1$ 得到 $B_1$，以此类推。

可是他突然忘记自己是怎么变换到的了，所以他请你帮他找到一组步数尽量少的合法的变换。
## 输入格式

第一行一个整数 $n$，表示点的个数。

接下来 $n$ 行，第 $i+1$ 行两个实数 $x,y$，表示 $A_i$ 的横、纵坐标。

接下来 $n$ 行，第 $i+n+1$ 行两个实数 $x,y$，表示 $B_i$ 的横、纵坐标。
## 输出格式

第一行一个整数 $k$ ，表示最少的步数。

接下来 $k$ 行，第 $i+1$ 行三个实数 $A,B,C$，表示第 $i$ 次轴对称变换的轴为直线 $Ax+By+C=0$。
## 样例

### 样例输入 #1
```
2
1.000000 1.000000
2.000000 2.000000
4.000000 4.000000
3.000000 3.000000

```
### 样例输出 #1
```
1
1.000000 1.000000 -5.000000
```
## 提示

## 样例解释
![](https://cdn.luogu.com.cn/upload/image_hosting/8msdygxi.png)
## 提示
对于直线 $Ax+By+C=0$，如果 $B$ 非零，那么它就是一次函数 $y=-\dfrac ABx-\dfrac CB$ 的图像；否则，它表示一条垂直于 $x$ 轴的直线 $x=-\dfrac CA$。

本题带有 $\text{SPJ}$。**因为某种原因，本题不提供** $\text{SPJ}$ **给选手。**

对于每个测试点，如果你的 $k$ 正确，则获得 $30\%$ 的分数；

接下来，我们将对 $A_1,A_2,\cdots,A_n$ 分别进行你给的 $k$ 次轴对称变换，记 $A_i$ 得到的点为 $C_i$。如果对于所有的 $i$，$B_i$ 与 $C_i$ 的 $x,y$ 坐标之差的绝对值都不超过 $10^{-2}$，则你获得 $100\%$ 的分数。

如果你只想输出 $k$，也请在后面随意输出一些值，防止 $\text{UKE}$。
## 数据范围

| 测试点编号 | $n=$ | 构造数据时翻折的次数 |
| ---------- | ---- | -------------------- |
| 1,2        | $1$  | $\le1$               |
| 3,4        | $2$  | $\le10$              |
| 5,6        | $5$  | $\le10^3$            |
| 7,8,9,10   | $10$ | $\le10^5$            |

对于所有数据，$1\le n\le10$，$|x|,|y|\le 10^5$。

所有数据点已经经过 $\text{SPJ}$ 验证无误。 

请保证你的输出中的所有 $A,B,C$ 满足 $|A|,|B|,|C|\le 10^5$。


---

---
title: "[NWRRC 2016] Integral Polygons"
layout: "post"
diff: 省选/NOI-
pid: P7039
tag: ['计算几何', '2016', '叉积', 'ICPC', '状压 DP']
---
# [NWRRC 2016] Integral Polygons
## 题目描述



Ingrid holds a polygon shop in a far away country. She sells only convex polygons with integer coordinates. Her customers prefer polygons that can be cut into two halves in a proper way, that is the cut should be straight  with starting and ending points in the polygon vertices and both halves should be non-empty and have integer areas. The more ways to cut the polygon in the proper way are -- the more expensive the polygon is.

For example, there are three ways to cut the left polygon in the proper way, and two ways for the right polygon.

![](https://cdn.luogu.com.cn/upload/image_hosting/fei0xc33.png)

The polygons in the shop are always of excellent quality, so the business is expanding. Now Ingrid needs some automatic tool to determine the number of ways to cut the polygon in the proper way. This is very important for her shop, since otherwise you will spend a lot of time on setting prices -- just imagine how much time would it take to set prices for a medium-sized van with polygons. Could you help Ingrid and write the tool for her?


## 输入格式



The first line of the input contains an integer $n$ -- the number of polygon vertices $(4 \le n \le 200 000)$ . $ Each$ of the following $n$ lines contains vertex coordinates: a pair of integers $x_{i}$ and $y_{i}$ per line $(-10^{9} \le x_{i}, y_{i} \le 10^{9}).  The$ specified polygon is convex and its vertices are specified in the order of traversal.


## 输出格式



Output a single integer $w$ -- the number of ways to cut the polygon in the proper way.


## 样例

### 样例输入 #1
```
5
7 3
3 5
1 4
2 1
5 0

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
4
1 1
3 1
5 5
1 3

```
### 样例输出 #2
```
2

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

按顺序给定一个凸多边形的  $n$ 个定点  $(x_i,y_i)$ ， $x_i,y_i\in[-10^9,10^9]$ 且为整数。

求满足条件的对角线数量，使得该对角线将多边形分成的两个部分的面积皆为整数。


---

---
title: "[COCI 2020/2021 #1] 3D Histogram"
layout: "post"
diff: 省选/NOI-
pid: P7164
tag: ['计算几何', '2020', 'COCI（克罗地亚）']
---
# [COCI 2020/2021 #1] 3D Histogram
## 题目背景

~~原题目背景其实是一个出毒瘤题的套路，有兴趣的同学可以去看看，这里懒得翻译了~~
## 题目描述

在一个三维直方图中，放入 $n$ 个三维块，这些三维块的宽度均为 $1$，且能使得在正面看是一个从左到右分别高度为 $a_i$ 的二维直方图，在上面看是一个从左到右分别高度为 $b_i$ 的二维直方图。

求在直方图中能放入的最大体积长方体的体积是多少，长方体的所有边均要与三维块的长宽高平行。
## 输入格式

第一行一个整数 $n$ 代表三维块数量。       
接下来 $n$ 行每行两个整数 $a_i,b_i$，如题目描述。
## 输出格式

一行一个整数代表能放入的最大长方体体积。
## 样例

### 样例输入 #1
```
5
5 3
4 4
2 1
3 2
1 5
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
6
3 1
2 1
2 2
2 3
1 1
2 2
```
### 样例输出 #2
```
8
```
### 样例输入 #3
```
5
15 19
5 6
1 13
3 7
1 2

```
### 样例输出 #3
```
285
```
## 提示

#### 样例 1 解释

描述的直方图如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/z2txhsvt.png)

能放入的最大长方体体积为 $2 \times 4 \times 3=24$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$1 \le n \le 2000$。
- Subtask 2（90 pts）：$1 \le n \le 2 \times 10^5$。

对于 $100\%$ 的数据，$1 \le a_i,b_i \le 10^6$。

**本题满分 $110$ 分。**

#### 说明

翻译自 [Croatian Open Competition in Informatics 2020 ~ 2021 Round 1 C 3D Histogram](https://hsin.hr/coci/archive/2020_2021/contest1_tasks.pdf)。


---

---
title: "雨水收集系统（2021 CoE-I E）"
layout: "post"
diff: 省选/NOI-
pid: P7397
tag: ['计算几何', '2021', 'Special Judge', '凸包', '半平面交']
---
# 雨水收集系统（2021 CoE-I E）
## 题目背景

Rain 市的环保部门为部分建筑的顶层安装了雨水收集装置，使得能够将雨水进行循环利用。雨水收集系统通过每栋建筑的顶层地面来收集雨水，利用特殊的管道将雨水集中引流到一个蓄水池中以待后续使用。环保部门计划根据降水量来估计蓄水池的容量大小以便进行设计制造。
## 题目描述

为了简化问题的处理，将每栋建筑的顶层视为一个边与坐标轴平行的矩形，使用矩形的一条对角线顶点坐标来表示该矩形。每次降雨时，降雨云沿着特定的方向以一定的速度做匀速运动，降雨云所经过的区域均会有雨水降落。将降雨云抽象为一个凸多边形，给定初始时降雨云的位置以及移动方向和速率，确定在某段时间内雨水收集系统能够接受降雨的面积大小。
## 输入格式

**输入包含多组测试数据**。

输入的第一行为一个整数 $T$，表示测试数据的组数，接下来共 $T$ 组数据，相邻两组测试数据之间有一个空行。每组测试数据的第一行为一个整数 $n$，表示建筑的数量。接下来 $n$ 行，每行四个整数，表示第 $i$ 栋建筑顶层所对应矩形的对角线顶点坐标。接下来一行是一个整数 $m$，表示降雨云对应凸多边形的顶点数目，接下来是 $m$ 个表示该凸多边形的顶点坐标（**不保证有序，即顶点可能不是按照顺时针或逆时针顺序给出，但给定的坐标点唯一地确定了表示降雨云的凸多边形**）：（$x_1$，$y_1$），（$x_2$，$y_2$），...，（$x_m$，$y_m$）。再接下来是起点 $s$（$x_s$，$y_s$）和终点 $e$（$x_e$，$y_e$）的坐标值，表示降雨云沿着从起点 $s$ 到终点 $e$ 的直线方向做平移运动。后续是一个整数 $v$，表示降雨云沿着直线方向的移动速率为 $v$ 单位距离/分钟，最后一行表示降雨的起始时间 $hh_{start}$ 时 $mm_{start}$ 分和结束时间  $hh_{end}$ 时 $mm_{end}$ 分，以 $24$ 小时计时法表示。
## 输出格式

输出在指定时间内能够接受降雨的建筑顶层面积之和，精确到小数点后一位。如果你的输出和参考输出绝对误差在$10^{-1}$之内，均认为正确。
## 样例

### 样例输入 #1
```
2

2
0 0 10 10
20 20 30 10
4
-10 8 -5 8 -5 13 -10 13
15 0 25 0
1
15:30 16:05

2
0 0 10 10
20 20 30 10
4
-10 8 -5 8 -5 13 -10 13
-5 8 19 1
1
15:30 16:30
```
### 样例输出 #1
```
50.0
60.5
```
## 提示

#### 样例说明

![](https://cdn.luogu.com.cn/upload/image_hosting/jf0ig9zb.png)

第一组测试数据，此组测试数据一共有 $2$ 栋建筑 $\operatorname{B_1}$ 和 $\operatorname{B_2}$，降雨云 $\operatorname{C}$ 为一个正方形（正方形的左下角位于坐标点（$-10$，$8$），边长为 $5$），降雨云沿着从起点（$15$，$0$）到终点（$25$，$0$）的方向匀速移动，移动速率为 $1$ 单位距离/分钟，降雨起始时间为 $15$ 时 $30$ 分，结束时间为 $16$ 时 $05$ 分，降雨时间为 $35$ 分钟，降雨云沿着箭头所示方向移动了 $35$ 单位距离。如上图所示，能够接受降雨的面积为阴影区域的面积，易知面积为 $50.0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/two4uh3q.png)
第二组测试数据，降雨云的移动方向不同，从起点（$-5$，$8$）到终点（$19$，$1$）的方向匀速移动，降雨时间为 $60$ 分钟，沿着箭头所示方向的移动距离为 $60$ 单位距离，其他条件相同，能够接受降雨的面积为上图中的阴影区域，其面积为 $60.5$。注意，第二组测试数据的示意图中，为了示意的方便，所绘制的降雨云“最终位置”并不是其实际的最终位置。

------------

#### 数据范围与约定

对于 $100\%$ 的数据，$1 \leq T \leq 10^3$，$1 \leq n \leq 50$，$3 \leq m \leq 100$，$0 \lt v \leq 100$。所有坐标值均为整数，位于闭区间 $[-10^5,10^5]$。

输入数据保证表示建筑顶层的矩形不会发生重叠。降雨的结束时间一定晚于起始时间。表示降雨云移动方向的起点 $s$ 和终点 $e$ 不同。


---

---
title: "[THUPC 2017] 气氛"
layout: "post"
diff: 省选/NOI-
pid: P7429
tag: ['计算几何', '2017', '线性代数', '高斯消元', 'THUPC']
---
# [THUPC 2017] 气氛
## 题目描述

北大街，在中国是一个非常常见的地名，比较著名的有上海北大街，西安北大街，成都北大街，太原北大街，中关村北大街等。

我们都知道，北的意思是自由民主，大的意思是兼收并蓄，所以住在北大街的人也性情迥异，我们假设在北大街住了 $n$ 个人。

有人向住在北大街的这 $n$ 个人提了 $n-1$ 个问题，比如：

「用不用筷子？」

「吃不吃红烧肉？」

「写代码用 tab 还是 space」

「大括号换不换行？」

「……」

根据每个人的回答，他会被分配一个 $n-1$ 维的零一坐标，也就是一个点。这样 $n$ 个点可以恰好构成一个 $n-1$ 维空间中的凸包。

北大街的居民认为，在这个多面体内，便是华夏；多面体之外，便是蛮夷。我们可以很容易的计算出华夏部分的广义凸包体积。

有一天，清华路的 B 君来北大街玩，听说了这个故事觉得很有趣，于是也试着给出了这 $n-1$ 个问题的答案，

清华路的 B 君，当然认为自己属于华夏，但是北大街表示在 $n-1$ 维空间中如果有 $n+1$ 个点的话，华夏部分的体积难以计算。

这下子气氛突然僵化。所以这个问题就留给你了，输入 $n-1$ 维度空间中的 $n+1$ 个点，求广义凸包的体积。

由于这个体积可能不是整数，你只需要输出体积乘以 $n-1$ 的阶乘，然后对 $10^9+7$ 取模的结果。
## 输入格式

从标准输入读入数据。

第一行一个整数 $T$ 表示组数，接下来是 $T$ 组数据

每组数据的第一行是一个整数 $n$ 。

接下来 $n+1$ 行，每行 $n-1$ 个整数，表示在 $n-1$ 维空间中的一个点。
## 输出格式

输出到标准输出。

对于每组数据，输出一行一个整数表示答案。

输入 $n+1$ 个点的凸包体积乘以 $n-1$ 的阶乘，然后对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
1
3
0 0
0 1
1 0
1 1
```
### 样例输出 #1
```
2
```
## 提示

$1\le t\le 100,3\le n\le35$

点的坐标一定是 $0$ 或者 $1$。
#### 版权信息
来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2017。


---

---
title: "[WFOI - 01] 循环节（circle）"
layout: "post"
diff: 省选/NOI-
pid: P8000
tag: ['计算几何', '洛谷原创', 'Special Judge', 'O2优化', '凸包', '旋转卡壳', '洛谷月赛']
---
# [WFOI - 01] 循环节（circle）
## 题目背景

简化题意：[$\texttt{Link}$](https://www.luogu.com.cn/paste/v7gqdh44)。

出题人注：これは非常に嫌な質問なので、あまり時間をかけたくない場合は、この質問を見る前に他の質問を終えることをお勧めします。
## 题目描述

给你一个坐标系上的点集 $a$，你需要找出一个子点集 $b$ 和一个向量 $x$，使得 $\exist\ z\in N^+,\{b\cup b+x\cup b+2x\cup\dots\cup b+zx=a\}$。

现在想让你求出任意一对 $b_0,x_0,z_0$，其中 $z_0$ 为所有满足条件的三元组中 $z$ 最大的，$b_0$ 中任意三点不共线，任意四点不构成梯形或平行四边形且 $b_0\cap b_0+x_0=\varnothing,b_0\cap b_0+2x_0=\varnothing,\dots,b_0\cap b+yx_0=\varnothing|{y\to+\infty}$。

其中 $b+x$ 的意思是，$b$ 中的所有点都平移向量 $x$ 后组成的点集。
## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行，每行 $2$ 个整数，表示一个点。
## 输出格式

输出共 $4$ 行：

第一行一个整数 $|b|$。

第二行 $|b|$ 个整数 $b_1,b_2,\dots,b_{|b|}$（对应编号）。

第三行两个整数 $x$。

第四行一个整数 $z$。
## 样例

### 样例输入 #1
```
4
0 0
0 1
1 0
1 1
```
### 样例输出 #1
```
2
1 3
0 1
1
```
### 样例输入 #2
```
3
0 0
0 1
1 0
```
### 样例输出 #2
```
3
1 2 3
0 0
0
```
## 提示

由于本题有样例解释也只是照着念一遍，并且相信既然您都做到这一题来了应该能读懂题目含义，所以本题不提供样例解释（~~其实是出题人懒~~）。

**本题采用 Subtask 捆绑测试。**
Subtask 编号 | 数据规模与约定
:-: | :-:
**Subtask #0($\text{20 pts}$)** | $1\le n\le10$；$-10\le x_i,y_i \le 10$
**Subtask #1($\text{20 pts}$)** | $1\le n\le10^3$
**Subtask #2($\text{30 pts}$)** | $z>1$
**Subtask #3($\text{30 pts}$)** | 无特殊限制

对于 $100\%$ 的数据，$1\le n\le10^5$，点的坐标范围 $\in\left(-10^9,10^9\right)$，数据保证有解。


---

---
title: "[THUPC 2022 初赛] 喵喵花園"
layout: "post"
diff: 省选/NOI-
pid: P8212
tag: ['计算几何', '2022', 'Special Judge', 'O2优化', '模拟退火', 'THUPC']
---
# [THUPC 2022 初赛] 喵喵花園
## 题目描述

喵喵是一只非常富有的猫咪，他在海淀区拥有一个大花园。

这个大花园是由一些旧栅栏为边界所形成的 $N$-gon（即具有 $N$ 边的多边形）。

由于圣诞节快到了，喵喵想用 $K$ 棵圣诞树来装饰一下花园。 同时，喵喵坚信找到一些好的位置来种树会给他带来好运。

作为一只好猫咪，他决定寻找最佳位置如下：

- 所有的树都应该在花园的边界上。
- 这些 $K$ 树应该平均划分花园的周长。
- 由树木形成的新凸面$K$-gon 的面积应尽可能小。

虽然喵喵比你有钱，但他没有你那么聪明。 因此，他给了你一些钱，让你帮他找出凸$K$-gon 的最小面积。
## 输入格式

第一行包含两个整数，$N$ 和 $K$，代表原本花园边界的顶点数和树的数量。

接下来的每行 $N$ 行包含两个整数 $x_i$ 和 $y_i$，表示花园边界顶点的坐标。

所有座标均为逆时针给出的。
## 输出格式

输出凸面 $K$-gon 的最小面积。 如果相对或绝对误差不超过 $10^{-8}$，则您的答案被认为是正确的。
## 样例

### 样例输入 #1
```
5 4
0 0
1 0
2 1
2 2
0 2
```
### 样例输出 #1
```
1.9892766953
```
### 样例输入 #2
```
3 3
0 0
1 0
0 1
```
### 样例输出 #2
```
0.1226170434
```
## 提示

【数据范围】

- $3 \le N, K \le 1000$；
- $-10^5 \le x_i, y_i \le 10^5$。


---

---
title: "[蓝桥杯 2013 国 A] 车轮轴迹"
layout: "post"
diff: 省选/NOI-
pid: P8610
tag: ['计算几何', '2013', '蓝桥杯国赛']
---
# [蓝桥杯 2013 国 A] 车轮轴迹
## 题目描述

栋栋每天骑自行车回家需要经过一条狭长的林荫道。道路由于年久失修，变得非常不平整。虽然栋栋每次都很颠簸，但他仍把骑车经过林荫道当成一种乐趣。

由于颠簸，栋栋骑车回家的路径是一条上下起伏的曲线，栋栋想知道，他回家的这条曲线的长度究竟是多长呢？更准确的，栋栋想知道从林荫道的起点到林荫道的终点，他的车前轮的轴（圆心）经过的路径的长度。

栋栋对路面进行了测量。他把道路简化成一条条长短不等的直线段，这些直线段首尾相连，且位于同一平面内。并在该平面内建立了一个直角坐标系，把所有线段的端点坐标都计算好。

假设栋栋的自行车在行进的过程中前轮一直是贴着路面前进的。

![](https://cdn.luogu.com.cn/upload/image_hosting/1vb89irr.png)

图 $1$ 给出了一个简单的路面的例子，其中蓝色实线为路面，红色虚线为车轮轴经过的路径。在这个例子中，栋栋的前轮轴从 $A$ 点出发，水平走到 $B$ 点，然后绕着地面的 $F$ 点到 $C$ 点（绕出一个圆弧），再沿直线下坡到 $D$ 点，最后水平走到 $E$ 点，在这个图中地面的坐标依次为：$(0,0),(2,0),(4,-1),(6,-1)$，前轮半径为 $1.50$，前轮轴前进的距离依次为：

$AB=2.0000$；弧长 $BC=0.6955$；$CD=1.8820$；$DE=1.6459$。

总长度为 $6.2233$。

![](https://cdn.luogu.com.cn/upload/image_hosting/z166vjw7.png)

图 $2$ 给出了一个较为复杂的路面的例子，在这个例子中，车轮在第一个下坡还没下完时（$D$ 点）就开始上坡了，之后在坡的顶点要从 $E$ 绕一个较大的圆弧到 $F$ 点。这个图中前轮的半径为 $1$，每一段的长度依次为：

$AB=3.0000$；弧长 $BC=0.9828$；$CD=1.1913$；$DE=2.6848$；弧长 $EF=2.6224$；$FG=2.4415$；$GH=2.2792$。

总长度为 $15.2021$。

现在给出了车轮的半径和路面的描述，请求出车轮轴轨迹的总长度。
## 输入格式

输入的第一行包含一个整数 $n$ 和一个实数 $r$，用一个空格分隔，表示描述路面的坐标点数和车轮的半径。

接下来 $n$ 行，每个包含两个实数，其中第 $i$ 行的两个实数 $x_i,y_i$ 表示描述路面的第 $i$ 个点的坐标。

路面定义为所有路面坐标点顺次连接起来的折线。给定的路面的一定满足以下性质：

* 第一个坐标点一定是 $(0,0)$；
* 第一个点和第二个点的纵坐标相同；
* 倒数第一个点和倒数第二个点的纵坐标相同；
* 第一个点和第二个点的距离不少于车轮半径；
* 倒数第一个点和倒数第二个点的的距离不少于车轮半径；
* 后一个坐标点的横坐标大于前一个坐标点的横坐标，即对于所有的 $i$，$x_{i+1}>x_i$。
## 输出格式

输出一个实数，四舍五入保留两个小数，表示车轮轴经过的总长度。

你的结果必须和参考答案一模一样才能得分。数据保证答案精确值的小数点后第三位不是 $4$ 或 $5$。
## 样例

### 样例输入 #1
```
4 1.50
0.00 0.00
2.00 0.00
4.00 -1.00
6.00 -1.00
```
### 样例输出 #1
```
6.22
```
### 样例输入 #2
```
6 1.00
0.00 0.00
3.00 0.00
5.00 -3.00
6.00 2.00
7.00 -1.00
10.00 -1.00
```
### 样例输出 #2
```
15.20
```
## 提示

对于 $20\%$ 的数据，$n=4$；

对于 $40\%$ 的数据，$n \le 10$；

对于 $100\%$ 的数据，$4 \le n \le 100$，$0.5 \le r \le 20.0$，$x_i \le 2000.0$，$-2000.0 \le y_i \le 2000.0$。

时限 1 秒, 64M。蓝桥杯 2013 年第四届国赛


---

---
title: "[ICPC 2020 Nanjing R] Interested in Skiing"
layout: "post"
diff: 省选/NOI-
pid: P9630
tag: ['计算几何', '2020', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Interested in Skiing
## 题目描述

Kotori is interested in skiing. The skiing field is an infinite strip going along $y$-axis on the 2-dimensional plane where all points $(x, y)$ in the field satisfies $-m \le x \le m$. When skiing, Kotori cannot move out of the field, which means that the absolute value of his $x$-coordinate should always be no more than $m$. There are also $n$ segments on the ground which are the obstacles and Kotori cannot move across the obstacles either.

Kotori will start skiing from $(0, -10^{10^{10^{10^{10}}}})$ (you can regard this $y$-coordinate as a negative infinity) and moves towards the positive direction of the $y$-axis. Her vertical (parallel to the $y$-axis) speed is always $v_y$ which cannot be changed, however she can control her horizontal (parallel to the $x$-axis) speed in the interval of $[-v_x, v_x]$. The time that Kotori changes her velocity can be neglected.

Your task is to help Kotori calculate the minimum value of $v_x^*$ that once $v_x>v_x^*$ she can safely ski through the skiing field without running into the obstacles.
## 输入格式

There is only one test case in each test file.

The first line of the input contains three positive integers $n$, $m$ and $v_y$ ($1 \le n \le 100$, $1 \le m \le 10^4$, $1 \le v_y \le 10$), indicating the number of obstacles, the half width of the skiing field and the vertical speed.

For the following $n$ lines, the $i$-th line contains four integers $x_1$, $y_1$, $x_2$ and $y_2$ ($-m \le x_1, x_2 \le m$, $-10^4 \le y_1, y_2 \le 10^4$, $x_1 \ne x_2$ or $y_1 \ne y_2$) indicating the $i$-th obstacle which is a segment connecting point $(x_1, y_1)$ and $(x_2, y_2)$, both inclusive (that is to say, these two points are also parts of the obstacle and cannot be touched). It's guaranteed that no two obstacles intersect with each other.
## 输出格式

Output one line containing one number indicating the minimum value of $v_x^*$. If it is impossible for Kotori to pass through the skiing field, output ``-1`` (without quotes) instead.

Your answer will be considered correct if and only if its absolute or relative error does not exceed $10^{-6}$.
## 样例

### 样例输入 #1
```
3 2 1
-2 0 1 0
-1 4 2 4
0 1 0 3
```
### 样例输出 #1
```
1.000000000000000
```
### 样例输入 #2
```
2 1 2
-1 0 1 0
1 1 0 1
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
2 3 7
-3 0 2 2
3 1 -2 17
```
### 样例输出 #3
```
1.866666666666666
```
### 样例输入 #4
```
1 100 1
-100 0 99 0

```
### 样例输出 #4
```
0.000000000000000
```
## 题目翻译

### 题目描述
Kotori 对滑雪很感兴趣。滑雪场是在二维平面上沿着 $y$ 轴无限延伸的直线，其中场中的所有点 $(x,y)$ 满足 $-m\le x\le m$。滑雪时，Kotori 不能离开场地，这意味着他的 $x$ 坐标的绝对值应该始终不超过 $m$。地面上也有 $n$ 个路段是障碍，Kotori 无法越过障碍。

Kotori 将从 $(0, -10^{10^{10^{10^{10}}}})$  开始滑雪（你可以将此 $y$ 坐标视为负无穷大），并朝着 $y$ 轴的正方向移动。她的垂直（平行于 $y$ 轴）速度始终是 $v_y$，此值不变，但是她可以在 $[-v_x, v_x]$ 的间隔内控制她的水平（平行于 $x$ 轴的）速度。Kotori 改变速度的时间可以忽略不计。

你的任务是帮助 Kotori 计算 $v_x^*$ 的最小值，即一旦 $v_x>v_x^*$，她就可以安全地穿过滑雪场而不会遇到障碍物。

### 输入格式

每个测试文件中只有一个测试用例。

输入的第一行包含三个正整数 $n, m$ 和 $v_y$（$1\le n\le 100$，$1\le m\le 10^4$，$1\le v_y\le 10$），分别表示障碍物的数量、滑雪场的半宽和垂直速度。

对于下面的 $n$ 行，第 $i$ 行包含四个整数 $x_1, y_1, x_2$ 和 $y_2$（$-m\le x_1, x_2\le m$，$-10^4\le y_1, y_2\le 10^4$，$x_1\ne x_2$ 或 $y_1\ne y_2$），这四个整数表示第 $i$ 个障碍物，该障碍物是连接点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 的线段，两者都包括在内（也就是说，这两个点也是障碍物的一部分，不能触摸）。保证没有两个障碍物相互交叉。

### 输出格式

输出一行，其中包含一个数字，表示 $v_x^*$ 的最小值。如果 Kotori 无法通过滑雪场，请输出 `-1`（不带引号）。

当且仅当其绝对或相对误差不超过 $10^{-6}$ 时，您的答案才会被认为是正确的。

------------

翻译来自 [fire_wolf](https://www.luogu.com.cn/user/690669)。


---

---
title: "[EC Final 2021] Two Walls"
layout: "post"
diff: 省选/NOI-
pid: P9875
tag: ['计算几何', '2021', 'O2优化', 'ICPC']
---
# [EC Final 2021] Two Walls
## 题目描述

Prof. Pang has bought a humanoid cleaning robot to clean his yard. The robot is not very sophisticated. It can either move forward or change its direction at a time, all controlled by Prof. Pang's controller.

Prof. Pang's yard is a 2D plane. The robot needs to move from its current location $A$ to the destination $B$ to fulfill some ``cleaning`` needs of Prof. Pang. However, there are two straight walls $CD$ and $EF$ in Prof. Pang's yard. Since the robot is clumsy, it will fall over if it touches any of the walls (even at endpoints).

Now that Prof. Pang is lazy, he wants to minimize the number of times the robot changes its direction. Can you help him?
## 输入格式

The first line contains a single integer $T$ ($1 \le T \le 10^5$) denoting the number of test cases.

For each test case, the first line contains two integers $x_A, y_A$, the coordinates of point $A$. The second line contains two integers $x_B, y_B$, the coordinates of point $B$.
The third line contains four integers $x_C, y_C, x_D, y_D$, the coordinates of point $C$ and $D$ which are the endpoints of the first wall. The fourth line contains four integers $x_E, y_E, x_F, y_F$, the coordinates of point $E$ and $F$ which are the endpoints of the second wall.

It is guaranteed that neither the current location $A$ nor the destination $B$ of the robot are on any of the walls. A wall may degenerate to a point. It can be proved that the robot can always move from $A$ to $B$ without touching any of the walls. All values lie within $[-10^9, 10^9]$.
## 输出格式

For each test case, print one number $d$ in one line, denoting the minimum number of turns.
## 样例

### 样例输入 #1
```
3
0 0
1 1
2 2 3 3
4 4 5 5
0 0
1 1
2 2 3 3
2 2 3 3
0 0
10 10
10 0 0 10
1 1 2 2
```
### 样例输出 #1
```
0
0
1
```
## 提示

The following are illustrations for the first sample and the third sample.

![](https://cdn.luogu.com.cn/upload/image_hosting/nuyvzg7a.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/diy78yex.png)
## 题目翻译

平面直角坐标系上有两点 $A$ 与 $B$，以及两面墙 $CD,EF$，墙可以视作线段。

请问从 $A$ 到 $B$ 在不碰到墙（端点也不可碰到）的情况下最少要转几次弯（转弯的度数可以任意决定）？


---

