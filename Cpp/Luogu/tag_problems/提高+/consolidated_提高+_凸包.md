---
title: "[XJTUPC 2025] 棱堡"
layout: "post"
diff: 提高+/省选-
pid: P12535
tag: ['计算几何', '2025', 'Special Judge', 'O2优化', '凸包', '高校校赛']
---
# [XJTUPC 2025] 棱堡
## 题目描述

棱堡（Bastion）是第一种仅靠直射火力而不存在攻击死角的堡垒。

![](https://cdn.luogu.com.cn/upload/image_hosting/ly4kphsw.png)

简单非退化多边形是由 $n$ ($n\ge 3$) 个顶点序列组成的闭合多边形 **区域**，满足以下条件：

- 顶点序列首尾相连，形成 $n$ 条边，构成平面紧致闭集（含所有边界和内部点）；
- $n$ 条边仅在顶点处相接且互不相交（相邻边在公共顶点外无其他交点）；
- $n$ 个顶点互不重合，且不位于任何非相邻边的内部，且任意三个连续的顶点不共线。

棱堡可以被视为由 $n$ 个点和 $n$ 条边组成的简单非退化多边形。对于多边形边上互异两点 $P$ 和 $Q$，我们定义点 $P$ 可以火力直射点 $Q$，当且仅当线段 $PQ$ 与多边形只交于 $P$ 和 $Q$ 两点。如下图所示，点 $A$ 和 $B$ 不能火力直射点 $X$，但是点 $C$ 可以。如果对于多边形边上一点 $P$，不存在多边形边上另外一点 $Q$ 使得点 $Q$ 可以火力直射 $P$，则我们称点 $P$ 为该多边形的火力盲区。

![](https://cdn.luogu.com.cn/upload/image_hosting/bz90r7zy.png)

我们称一个简单非退化多边形是棱堡，当且仅当其至多存在有限个点是火力盲区。给定一个简单非退化多边形，请判断其是否是一个棱堡。

形式化而言，给定一个简单非退化多边形，请判断其是否只有有限个位于多边形边上的点 $P$ 满足，不存在多边形边上的另外一点 $Q$，使得 $PQ$ 线段与多边形的交集只包含 $P$ 和 $Q$。
## 输入格式

输入包含多组测试用例。数据的第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$) 表示测试用例数。接下来描述每个测试用例。

每个测试用例的第一行包含一个整数 $n$ ($3 \leq n \leq 10^5$)，为多边形的边数。

接下来 $n$ 行，每行包含两个整数 $x_i$ 和 $y_i$ ($-10^9 \leq x_i, y_i \leq 10^9$)，描述多边形的一个顶点。

输入数据保证构成简单非退化多边形。顶点以逆时针顺序给出，即按顺序走过所有顶点后恰好逆时针旋转 $360^\circ$。按顶点的输入顺序依次连边（第 $i$ 个顶点连向第 $i + 1$ 个顶点，第 $n$ 个顶点连回第 $1$ 个顶点）。

保证所有测试用例的 $n$ 之和不超过 $2 \times 10^5$。
## 输出格式

对于每个测试用例，输出仅包含一行一个字符串，如果多边形是棱堡，输出 $\tt{YES}$，否则输出 $\tt{NO}$。答案对大小写不敏感。
## 样例

### 样例输入 #1
```
2
20
7 5
9 5
13 13
5 9
5 7
-5 7
-5 9
-13 13
-9 5
-7 5
-7 -5
-9 -5
-13 -13
-5 -9
-5 -7
5 -7
5 -9
13 -13
9 -5
7 -5
4
1 1
-1 1
-1 -1
1 -1
```
### 样例输出 #1
```
YES
NO
```


---

---
title: "[GCJ 2018 Qualification] Cubic UFO"
layout: "post"
diff: 提高+/省选-
pid: P13135
tag: ['数学', '计算几何', '2018', 'Special Judge', '凸包', 'Google Code Jam']
---
# [GCJ 2018 Qualification] Cubic UFO
## 题目描述

A mysterious cubic alien ship has appeared in the sky over Toronto! In this problem, Toronto is a plane in three-dimensional space that is parallel to the xz plane at $y = -3$ km. The alien ship is a solid cube with side length 1 km, centered at $(0 \text{ km}, 0 \text{ km}, 0 \text{ km})$, with its eight corners at $(\pm 0.5 \text{ km}, \pm 0.5 \text{ km}, \pm 0.5 \text{ km})$. The ship is casting an ominous shadow onto the plane; formally, the shadow is the orthogonal projection of the cube onto the plane. (We consider the sun to be a point infinitely far above the Toronto plane along the y-axis.)

The military is willing to tolerate the ship as long as the aliens meet their bureaucratic demand: the shadow must cover an area of the plane that is acceptably close to $\mathbf A \text{ km}^2$ (see the Output section for a precise definition). They have hired you, a geometric linguistics expert, to convey this demand to the aliens. In your communications so far, you have learned that the ship cannot change size, and the center of the ship cannot move, but the ship is able to rotate arbitrarily in place.

Please find a way that the aliens can rotate the ship so that the shadow's area is close to $\mathbf A$. Express your rotation using three points: the centers of any three non-pairwise-opposing faces.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow; each consists of one line with a rational $\mathbf{A}$, the desired area of the shadow, in $\mathrm{km}^{2}$, with exactly six digits after the decimal point.

It is guaranteed that there is always a way to rotate the ship in the desired manner for the values of $\mathbf{A}$ allowed in this problem.
## 输出格式

For each test case, first output one line containing `Case #x:`, where $x$ is the test case number (starting from 1). Then, output three more lines with three rational values each: the $x, y$, and $z$ coordinates of one of your three provided face-centers, as described above. You are welcome to use decimal (e.g., 0.000123456) or scientific notation (e.g., 1.23456e-4).

Your answer will be considered correct if and only if all of the following are true:

1. The distance (in $\mathrm{km}$ ) from each point to the origin must be between $0.5-10^{-6}$ and $0.5+10^{-6}$, inclusive.
2. The angles (in radians) between segments connecting the origin to each point must be between $\pi / 2-10^{-6}$ and $\pi / 2+10^{-6}$, inclusive.
3. The area of the shadow (in $\mathrm{km}^{2}$ ), computed by projecting all 8 vertices onto the $y=-3$ plane and finding the area of the convex hull of those projected points, must be between $\mathbf{A}-10^{-6}$ and $\mathbf{A}+$ $10^{-6}$, inclusive. We will compute the vertices as $+/-\mathbf{p}_{1}+/-\mathbf{p}_{2}+/-\mathbf{p}_{3}$ (that is, for each $\mathbf{p}_{i}$ we add either $\mathbf{p}_{i}$ or $-\mathbf{p}_{i}$ to the total using vector addition), where $\mathbf{p}_{1}, \mathbf{p}_{2}$, and $\mathbf{p}_{3}$ are the face-centers that you provide.

Please note that you might need to output more than 6 digits after the decimal point to safely pass the checks mentioned above. If there are multiple acceptable answers, you may output any one of them.
## 样例

### 样例输入 #1
```
2
1.000000
1.414213
```
### 样例输出 #1
```
Case #1:
0.5 0 0
0 0.5 0
0 0 0.5
Case #2:
0.3535533905932738 0.3535533905932738 0
-0.3535533905932738 0.3535533905932738 0
0 0 0.5
```
## 提示

In Sample Case #1, there is no need to rotate the cube at all; with two of its faces already parallel to the plane, the cube is already casting a shadow that is a square with side length $1$.

In Sample Case #2, one possible solution is to tell the aliens to give the cube a $45$ degree turn around the $x = y = 0$ line, creating a shadow that is a rectangle with dimensions of $1$ and $\sqrt 2$.

The following rough image shows the cubes and shadows for Sample Cases #1 and #2. The sun is shown for clarity, but remember that it is actually a point infinitely far away along the y-axis.

![](https://cdn.luogu.com.cn/upload/image_hosting/ylvi5a65.png)

**Limits**

- $1 \leqslant \mathrm{T} \leqslant 100$.

**Test set 1 (Visible)**

- $1.000000 \leqslant \mathrm{A} \leqslant 1.414213$

**Test set 2 (Hidden)**

- $1.000000 \leqslant \mathrm{A} \leqslant 1.732050$


---

---
title: "[GCJ 2015 #1A] Logging"
layout: "post"
diff: 提高+/省选-
pid: P13217
tag: ['计算几何', '2015', '凸包', '极角排序', 'Google Code Jam']
---
# [GCJ 2015 #1A] Logging
## 题目描述

A certain forest consists of $N$ trees, each of which is inhabited by a squirrel.

The **boundary** of the forest is the convex polygon of smallest area which contains every tree, as if a giant rubber band had been stretched around the outside of the forest.

Formally, every tree is a single point in two-dimensional space with unique coordinates $(X_i, Y_i)$, and the boundary is the convex hull of those points.

Some trees are **on the boundary** of the forest, which means they are on an edge or a corner of the polygon. The squirrels wonder how close their trees are to being on the boundary of the forest.

One at a time, each squirrel climbs down from its tree, examines the forest, and determines the minimum number of trees that would need to be cut down for its own tree to be on the boundary. It then writes that number down on a log.

Determine the list of numbers written on the log.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow; each consists of a single line with an integer $N$, the number of trees, followed by $N$ lines with two space-separated integers $X_i$ and $Y_i$, the coordinates of each tree. No two trees will have the same coordinates.

## 输出格式

For each test case, output one line containing "Case #$x$:", followed by $N$ lines with one integer each, where line $i$ contains the number of trees that the squirrel living in tree $i$ would need to cut down.
## 样例

### 样例输入 #1
```
2
5
0 0
10 0
10 10
0 10
5 5
9
0 0
5 0
10 0
0 5
5 5
10 5
0 10
5 10
10 10
```
### 样例输出 #1
```
Case #1:
0
0
0
0
1
Case #2:
0
0
0
0
3
0
0
0
0
```
## 提示

**Sample Explanation**

In the first sample case, there are four trees forming a square, and a fifth tree inside the square. Since the first four trees are already on the boundary, the squirrels for those trees each write down $0$. Since one tree needs to be cut down for the fifth tree to be on the boundary, the fifth squirrel writes down $1$.

**Limits**

- $-10^6 \leq X_i, Y_i \leq 10^6$.

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- $1 \leq T \leq 100$.
- $1 \leq N \leq 15$.

**Large dataset**

- Time limit: ~~480~~ 20 seconds.
- $1 \leq T \leq 14$.
- $1 \leq N \leq 3000$.


---

---
title: "[USACO5.1] 圈奶牛Fencing the Cows /【模板】二维凸包"
layout: "post"
diff: 提高+/省选-
pid: P2742
tag: ['计算几何', 'USACO', '分治', '凸包']
---
# [USACO5.1] 圈奶牛Fencing the Cows /【模板】二维凸包
## 题目背景

upd: 新增一组 hack 数据。
## 题目描述

农夫约翰想要建造一个围栏用来围住他的奶牛，可是他资金匮乏。他建造的围栏必须包括他的奶牛喜欢吃草的所有地点。对于给出的这些地点的坐标，计算最短的能够围住这些点的围栏的长度。
## 输入格式

输入数据的第一行是一个整数。表示农夫约翰想要围住的放牧点的数目 $n$。

第 $2$ 到第 $(n + 1)$ 行，每行两个实数，第 $(i + 1)$ 行的实数 $x_i, y_i$ 分别代表第 $i$ 个放牧点的横纵坐标。
## 输出格式

输出输出一行一个四舍五入保留两位小数的实数，代表围栏的长度。

## 样例

### 样例输入 #1
```
4
4 8
4 12
5 9.3
7 8
```
### 样例输出 #1
```
12.00
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$-10^6 \leq x_i, y_i \leq 10^6$。小数点后最多有 $2$ 位数字。


---

---
title: "[HNOI2008] 水平可见直线"
layout: "post"
diff: 提高+/省选-
pid: P3194
tag: ['计算几何', '2008', '湖南', '栈', '凸包']
---
# [HNOI2008] 水平可见直线
## 题目描述

在 $x-y$ 直角坐标平面上有 $n$ 条直线 $L_1,L_2,…L_n$，若在 $y$ 值为正无穷大处往下看，能见到 $L_i$ 的某个子线段，则称 $L_i$ 为可见的，否则 $L_i$ 为被覆盖的。
例如，对于直线:
$L_1:y=x$;
$L_2:y=-x$;
$L_3:y=0$;
则 $L_1$ 和 $L_2$ 是可见的，$L_3$ 是被覆盖的。给出 $n$ 条直线，表示成 $y=Ax+B$ 的形式($|A|,|B| \le 500000$)，且 $n$ 条直线两两不重合，求出所有可见的直线。
## 输入格式

第一行为 $N$ ($0<N<50000$)，接下来的 $N$ 行输入 $A_i,B_i$
## 输出格式

从小到大输出可见直线的编号，两两中间用空格隔开，最后一个数字后面也必须有个空格。
## 样例

### 样例输入 #1
```
3
-1 0
1 0
0 0
```
### 样例输出 #1
```
1 2
```


---

---
title: "[SHOI2012] 信用卡凸包"
layout: "post"
diff: 提高+/省选-
pid: P3829
tag: ['2012', '各省省选', '上海', '凸包']
---
# [SHOI2012] 信用卡凸包
## 题目背景

SHOI2012D1T2

## 题目描述

信用卡是一个矩形，唯四个角作了圆滑处理，使它们都是与矩形的两边相切的 1/4 圆，如下图所示。现在平面上有一些规格相同的信用卡，试求其凸包的周长。注意凸包未必是多边形，因为它可能包含若干段圆弧。

 ![](https://cdn.luogu.com.cn/upload/pic/6549.png) 


## 输入格式

输入的第一行是一个正整数 n，表示信用卡的张数。第二行包含三个实数 a, b, r，分别表示信用卡（圆滑处理前）竖直方向的长度、水平方向的长度，以及 1/4 圆的半径。

之后 n 行，每行包含三个实数 x, y, θ，分别表示一张信用卡中心（即对角线交点）的横、纵坐标，以及绕中心 逆时针旋转的 弧度。

## 输出格式

输出只有一行，包含一个实数，表示凸包的周长，四舍五入精确到小数点后2 位。

## 样例

### 样例输入 #1
```
2
6.0 2.0 0.0
0.0 0.0 0.0
2.0 -2.0 1.5707963268
```
### 样例输出 #1
```
21.66
```
### 样例输入 #2
```
3
6.0 6.0 1.0
4.0 4.0 0.0
0.0 8.0 0.0
0.0 0.0 0.0
```
### 样例输出 #2
```
41.60
```
### 样例输入 #3
```
3
6.0 6.0 1.0
4.0 4.0 0.1745329252
0.0 8.0 0.3490658504
0.0 0.0 0.5235987756
```
### 样例输出 #3
```
41.63
```
## 提示

样例1说明： ![](https://cdn.luogu.com.cn/upload/pic/6550.png)

本样例中的 2 张信用卡的轮廓在上图中用实线标出，如果视 1.5707963268为pi/2，那么凸包的周长为16+4sqrt(2)

样例2说明： ![](https://cdn.luogu.com.cn/upload/pic/6551.png)

样例3说明： ![](https://cdn.luogu.com.cn/upload/pic/6552.png)

其凸包的周长约为41.628267652。


本题可能需要使用数学库中的三角函数。不熟悉使用方法的选手，可以参考下面的程序及其输出结果：

```cpp
uses math;
const Pi = 3.141592653589793;
begin
writeln(sin(30.0 / 180.0 * Pi) : 0 : 10);
writeln(cos(60.0 / 180.0 * Pi) : 0 : 10);
writeln(tan(45.0 / 180.0 * Pi) : 0 : 10);
writeln(arcsin(1.0) : 0 : 10);
writeln(arccos(0.0) : 0 : 10);
writeln(arctan(1.0) : 0 : 10);
end.
```
```cpp
#include <iostream>
#include <math.h>
using namespace std;
const double Pi = 3.141592653589793;
int main()
{
cout.setf(ios::fixed);
cout.precision(10);
cout<<sin(30.0 / 180.0 * Pi)<<endl;
cout<<cos(60.0 / 180.0 * Pi)<<endl;
cout<<tan(45.0 / 180.0 * Pi)<<endl;
cout<<asin(1.0)<<endl;
cout<<acos(0.0)<<endl;
cout<<atan(1.0)<<endl;
return 0;
}
```
输出结果：0.5000000000

0.5000000000

1.0000000000

1.5707963268

1.5707963268

0.7853981634


数据范围：

 ![](https://cdn.luogu.com.cn/upload/pic/6553.png) 

![](https://cdn.luogu.com.cn/upload/pic/6554.png)



---

---
title: "[COCI 2020/2021 #5] Planine"
layout: "post"
diff: 提高+/省选-
pid: P7401
tag: ['2020', '凸包', 'COCI（克罗地亚）']
---
# [COCI 2020/2021 #5] Planine
## 题目描述

现有一座上下起伏的山。它可以抽象为一个包含 $n$（$n$ 为奇数）个点 $(x_i,y_i)$ 以及 $(x_1,-\inf)$ 与 $(x_n,-\inf)$ 的多边形。

对于所有满足 $i \neq 1$，$i \neq n$，$i \bmod 2=1$ 的整数 $i$，$(x_i,y_i)$ 都是山谷。

现要放置若干个高度为 $h$ 的点光源，使得所有的山谷都被照亮，即点光源与山谷的连线不经过山的内部。

求所需点光源的最少数量。
## 输入格式

第一行输入整数 $n,h$。

接下来的 $n$ 行，每行输入整数 $x_i,y_i$。

保证 $x_1 \lt x_2 \lt \cdots \lt x_n$ 且 $y_1 \lt y_2,y_2 \gt y_3,y_3 \lt y_4,\cdots,y_{n-1} \gt y_n$。
## 输出格式

输出所需点光源的最少数量。
## 样例

### 样例输入 #1
```
9 6
0 0
1 2
3 0
6 3
8 1
9 2
11 1
12 4
14 0
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
9 5
-5 2
-4 3
-2 1
0 4
2 2
3 3
4 1
5 2
6 1
```
### 样例输出 #2
```
2
```
## 提示

#### 样例 1 图解

![](https://cdn.luogu.com.cn/upload/image_hosting/6u2zqy65.png)

#### 样例 2 图解

![](https://cdn.luogu.com.cn/upload/image_hosting/e3mn6dt6.png)

#### 数据规模与约定

**本题采用捆绑测试**。

|Subtask|分值|数据范围及约定|
| :----------: | :----------: | :----------: |
|$1$|$20$|$y_2=y_4=\cdots=y_{n-1}$|
|$2$|$30$|$3 \le n \lt 2000$|
|$3$|$60$|无|

对于 $100\%$ 的数据，$3 \le n \lt 10^6$，$n \bmod 2=1$，$1 \le h \le 10^6$，$-10^6 \le x_i \le 10^6$，$0 \le y_i \lt h$，$x_1 \lt x_2 \lt \cdots \lt x_n$，$y_1 \lt y_2,y_2 \gt y_3,y_3 \lt y_4,\cdots,y_{n-1} \gt y_n$。

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2020-2021](https://hsin.hr/coci/) [CONTEST #5](https://hsin.hr/coci/contest5_tasks.pdf)  _T4 Planine_。**


---

---
title: "[SDCPC 2023] Computational Geometry"
layout: "post"
diff: 提高+/省选-
pid: P9568
tag: ['计算几何', '2023', '山东', 'Special Judge', 'O2优化', '凸包', 'XCPC']
---
# [SDCPC 2023] Computational Geometry
## 题目描述

Given a convex polygon $P$ with $n$ vertices, you need to choose three vertices of $P$, denoted as $a$, $b$ and $c$ in counter-clockwise order. There must be exactly $k$ edges from $b$ to $c$ in counter-clockwise order (that is to say, $a$ is not an endpoint of these $k$ edges).

Consider cutting through $P$ with segment $ab$ and $ac$. Let $Q$ be the polygon consisting of $ab$, $ac$ and the $k$ edges between $b$ and $c$. It's easy to see that this polygon has $(k + 2)$ edges.

Find the maximum possible area of $Q$.
 
Note that $ab$ and $ac$ can overlap with edges of $P$.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $k$ ($3 \le n \le 10^5$, $1 \le k \le n-2$) indicating the number of vertices of the convex polygon $P$ and the number of edges from $b$ to $c$ in counter-clockwise order.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($-10^9 \le x_i, y_i \le 10^9$) indicating the $x$ and $y$ coordinate of the $i$-th vertex of the convex polygon $P$. Vertices are given in counter-clockwise order. It's guaranteed that the area of the convex polygon is positive, and there are no two vertices with the same coordinate. It's possible that three vertices lie on the same line.

It's guaranteed that the sum of $n$ of all test cases will not exceed $10^5$.
## 输出格式

For each test case output one line containing one real number indicating the maximum possible area of $Q$. Your answer will be considered correct if its relative or absolute error is less than $10^{-9}$.
## 样例

### 样例输入 #1
```
3
3 1
0 0
1 0
0 1
8 3
1 2
3 1
5 1
7 3
8 6
5 8
3 7
1 5
7 2
3 6
1 1
3 1
7 1
8 1
5 6
4 6

```
### 样例输出 #1
```
0.500000000000
26.500000000000
20.000000000000

```
## 提示

For the first sample test case, $Q$ is the whole triangle. Its area is $0.5$.

The second and third sample test case are shown below.

![](https://cdn.luogu.com.cn/upload/image_hosting/vwd5087f.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/twyillv0.png)
## 题目翻译

**【题目描述】**

给定一个有 $n$ 个顶点的凸多边形 $P$，您需要选择 $P$ 的三个顶点，按逆时针顺序记为 $a$，$b$ 和 $c$。要求在 $b$ 沿逆时针方向到 $c$ 之间恰有 $k$ 条边（也就是说，$a$ 不是这 $k$ 条边的端点）。

考虑用线段 $ab$ 和 $ac$ 将 $P$ 割开。将由线段 $ab$，$ac$，以及 $b$ 和 $c$ 之间的 $k$ 条边围成的 $(k + 2)$ 边形记作 $Q$。

求 $Q$ 可能的最大面积。

注意，$ab$ 和 $ac$ 可以与 $P$ 的边重合。

**【输入格式】**

有多组测试数据。第一行输入一个整数 $T$ 表示测试数据组数。对于每组测试数据：

第一行输入两个整数 $n$ 和 $k$（$3 \le n \le 10^5$，$1 \le k \le n-2$），表示凸多边形 $P$ 的顶点数和 $b$ 沿逆时针方向到 $c$ 之间的边数。

对于接下来的 $n$ 行，第 $i$ 行输入两个整数 $x_i$ 和 $y_i$（$-10^9 \le x_i, y_i \le 10^9$），表示凸多边形 $P$ 第 $i$ 个顶点的 $x$ 坐标和 $y$ 坐标。顶点按逆时针顺序给出。保证凸多边形的面积为正，且没有顶点会重合。可能存在三个顶点位于同一条直线上的情况。

保证所有数据 $n$ 之和不超过 $10^5$。

**【输出格式】**

每组数据输出一行一个实数表示 $Q$ 的最大可能面积。只要您的答案的相对误差或绝对误差小于$10^{-9}$ 即视为正确。

**【样例解释】**

对于第一组样例数据，$Q$ 就是整个三角形，面积为 $0.5$.

第二和第三组样例数据解释如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/vwd5087f.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/twyillv0.png)


---

---
title: "[GDCPC 2023] Computational Geometry"
layout: "post"
diff: 提高+/省选-
pid: P9702
tag: ['计算几何', '2023', '广东', 'O2优化', '凸包', 'XCPC']
---
# [GDCPC 2023] Computational Geometry
## 题目描述

Given a convex polygon $P$ with $n$ vertices, you need to choose two vertices of $P$, so that the line connecting the two vertices will split $P$ into two smaller polygons $Q$ and $R$, both with positive area.

Let $d(Q)$ be the diameter of polygon $Q$ and $d(R)$ be the diameter of polygon $R$, calculate the minimum value of $(d(Q))^2 + (d(R))^2$.

Recall that the diameter of a polygon is the maximum distance between two points inside or on the border of the polygon.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($4 \le n \le 5 \times 10^3$) indicating the number of vertices of the convex polygon $P$.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($0 \le x_i, y_i \le 10^9$) indicating the $i$-th vertex of the convex polygon $P$. Vertices are given in counter-clockwise order. It's guaranteed that the area of the convex polygon is positive, and there are no two vertices with the same coordinate. It's possible that three vertices lie on the same line.

It's guaranteed that the sum of $n$ of all test cases will not exceed $5 \times 10^3$.
## 输出格式

For each test case output one line containing one integer indicating the answer.
## 样例

### 样例输入 #1
```
2
4
1 0
2 0
1 1
0 0
6
10 4
9 7
5 7
4 5
6 4
9 3
```
### 样例输出 #1
```
4
44
```
## 提示

The first sample test case is shown as follows. The diameter of smaller polygons are marked by red dashed segments. In fact, $(1, 0)$ and $(1, 1)$ are the only pair of vertices we can choose in this test case. You can't choose $(0, 0)$ and $(2, 0)$, or $(0, 0)$ and $(1, 1)$, because they can't split $P$ into two smaller polygons both with positive area.

![](https://cdn.luogu.com.cn/upload/image_hosting/6wue7ioc.png)

The second sample test case is shown as follows. The diameter of smaller polygons are marked by red dashed segments.

![](https://cdn.luogu.com.cn/upload/image_hosting/en9mocsw.png)
## 题目翻译

**【题目描述】**

给定一个有 $n$ 个顶点的凸多边形 $P$，您需要选择 $P$ 的两个顶点，并用一条同时穿过这两个顶点的直线，将 $P$ 分成两个面积均为正数的小多边形 $Q$ 和 $R$。

记 $d(Q)$ 表示多边形 $Q$ 的直径，$d(R)$ 表示多边形 $R$ 的直径，求 $(d(Q))^2 + (d(R))^2$ 的最小值。

请回忆：一个多边形的直径，指的是该多边形内部或边界上任意两点之间的距离的最大值。

**【输入格式】**

有多组测试数据。第一行输入一个整数 $T$ 表示测试数据组数。对于每组测试数据：

第一行输入一个整数 $n$（$4 \le n \le 5 \times 10^3$）表示凸多边形 $P$ 的顶点数量。

对于接下来 $n$ 行，第 $i$ 行输入两个整数 $x_i$ 和 $y_i$（$0 \le x_i, y_i \le 10^9$），表示凸多边形 $P$ 的第 $i$ 个顶点。顶点按逆时针顺序给出。保证该凸多边形面积为正，且没有顶点会重合。可能存在三个顶点位于同一条直线上的情况。

保证所有数据 $n$ 之和不超过 $5 \times 10^3$。

**【输出格式】**

每组数据输出一行一个整数表示答案。

**【样例解释】**

第一组样例数据如下图所示。小多边形的直径用红色虚线标出。事实上，顶点 $(1, 0)$ 和 $(1, 1)$ 是这一组数据中唯一能选择的一对顶点。您不能选择顶点 $(0, 0)$ 和 $(2, 0)$，或顶点 $(0, 0)$ 和 $(1, 1)$，因为它们无法将 $P$ 分成两个面积均为正数的小多边形。

![](https://cdn.luogu.com.cn/upload/image_hosting/6wue7ioc.png)

第二组样例数据如下图所示。小多边形的直径用红色虚线标出。

![](https://cdn.luogu.com.cn/upload/image_hosting/en9mocsw.png)


---

