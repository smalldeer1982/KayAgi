---
title: "点和线"
layout: "post"
diff: 提高+/省选-
pid: P1153
tag: ['计算几何']
---
# 点和线
## 题目描述

平面上有一些点，你可以用直线将两点连接起来。那么有多少种方法可以把这些点连续地连起来，使得任何两个线都不交叉。

显然，三个点只有一种方法。四个点最多只有 $3$ 种方法。写一个程序计算方法总数。

## 输入格式

每一行是一个点的坐标，坐标值是整数，中间用一个空格隔开。最后一个坐标是原点。任意三点不在一条直线上。
## 输出格式

输出方案总数。

## 样例

### 样例输入 #1
```
100 -10
-200 0
45 7
0 0

```
### 样例输出 #1
```
3

```
## 提示

最多只有 $10$  个点。

- 必须从一个点出发，途径所有点回到起点的路径才会被统计。

- 两个方案不相同当且仅当围成的简单多边形不同。


---

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
title: "[GCJ 2020 #1B] Blindfolded Bullseye"
layout: "post"
diff: 提高+/省选-
pid: P13057
tag: ['计算几何', '2020', '二分', '交互题', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2020 #1B] Blindfolded Bullseye
## 题目描述

Gary has a large square wall that is exactly $2 \times 10^{9}$ nanometers tall and $2 \times 10^{9}$ nanometers wide. Gary has a dartboard placed on the wall. The dartboard is circular and its radius is between A and B nanometers, inclusive. The dartboard is fully contained within the wall, but it may touch its edges. The center of the dartboard is an integer number of nanometers from each edge of the wall.

Gary invited his friend Mika over to play an interesting game. Gary blindfolds Mika and challenges her to throw a dart at the center of the dartboard. To help her, whenever Mika throws a dart at the wall, Gary will tell her whether the dart hit the dartboard.

Mika does not know where on the wall the dartboard is, but since Mika is very skilled at darts, she can throw darts with nanometer precision. That is, she can aim and hit exactly any point that is an integer number of nanometers away from each edge of the wall. Immediately after throwing each dart, Gary tells her whether she hit the center of the dartboard, some other part of it, or missed it completely and hit the bare wall.

Can you help Mika hit the center of the dartboard, without throwing more than 300 darts?

### Interactive Protocol

Initially, your program should read a single line containing three integers $\mathbf{T}$, $\mathbf{A}$ and $\mathbf{B}$, indicating the number of test cases and the inclusive minimum and maximum values for the dartboard's radius, in nanometers, respectively. (Notice that $\mathbf{A}$ and $\mathbf{B}$ are the same for every test case within a test set.) Then, you need to process $\mathbf{T}$ test cases.

We represent the points that darts can be aimed at as pairs $(x, y)$, where $x$ and $y$ are integers between $-10^{9}$ and $10^{9}$, inclusive. The pair $(x, y)$ is the point that is $x + 10^{9}$ nanometers away from the left edge of the wall and $y + 10^{9}$ nanometers away from the bottom edge of the wall. Point $(0, 0)$ is therefore at the exact center of the wall.

For each test case, there is a secretly chosen radius $R$ for the dartboard, and a secretly chosen center of the dartboard $(X, Y)$. $R$, $X$, and $Y$ are integers chosen for each test case by the judges in a designed (not random) way, within the limits. For each test case you need to process up to 300 exchanges with the judge. Your program represents Mika and the judge program represents Gary. Each exchange consists of Mika (your program) choosing where to throw a dart and Gary (the judging program) giving information about that position.

The $i$-th exchange consists of your program first outputting a single line containing two integers $X_{i}$ and $Y_{i}$, both between $-10^{9}$ and $10^{9}$, inclusive, and the judge responding with a single line containing either:

* `CENTER` if $X_{i} = X$ and $Y_{i} = Y$
* `HIT` if $0 < (X - X_{i})^{2} + (Y - Y_{i})^{2} \leq R^{2}$
* `MISS` in all other cases.

After sending CENTER, the judge will start waiting for the first exchange of the next test case, if there is any.

If you output a line that is incorrectly formatted or with an out of bounds value, the judge will respond with a single line containing WRONG. If 300 exchanges occur (including 300 responses from the judge) without you receiving CENTER, or if you ever receive WRONG, the judge will finish all communication, wait for your own program to also finish, and give a Wrong Answer verdict. After sending the $T$-th CENTER, on the other hand, the judge will finish all communication, wait for your own program to finish, and give a Correct verdict. If, while waiting for your program to finish, time or memory limits are exceeded, the corresponding verdict will be assigned instead. (Note that verdicts are not messages sent to your program.)
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```

```
### 样例输出 #1
```

```
## 提示

**Sample Explanation**

The following sample interaction uses the limits of Test Set 1.

```
  // The following reads 20 into t and 999999995 into a and b.
  t, a, b = readline_int_list()
  // The judge secretly picks R = 999999995 (it had no choice) and X = -1,
  // Y = 3 (it did have a choice here). (Note: the actual Test Set 1 will
  // not necessarily use the values in this example.)
  // We try to throw at the upper left corner of the wall, and the dartboard
  // does not overlap with that point.
  printline -1000000000 1000000000 to stdout
  flush stdout
  r = readline_string()  // reads MISS.
  // We try to throw at the center of the wall. That does hit the dartboard,
  // but not the center.
  printline 0 0 to stdout
  flush stdout
  r = readline_string()  // reads HIT.
  // We make a super lucky choice and throw at the center of the dartboard.
  printline -1 3 to stdout
  flush stdout
  r = readline_string()  // reads CENTER.
  // The judge begins the next test case. It secretly picks R = 999999995
  // and X = 5, Y = 5.
  // We accidentally throw a dart out of the allowed range.
  printline -1234567890 1234567890 to stdout
  flush stdout
  r = readline_string()  // reads WRONG.
  exit  // exits to avoid an ambiguous TLE error.
```

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our [interactive runner](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py) for that.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 20$.
- $\mathbf{A} \leqslant \mathbf{R} \leqslant \mathbf{B}$.
- $-10^{9} + \mathbf{R} \leqslant \mathbf{X} \leqslant 10^{9} - \mathbf{R}$.
- $-10^{9} + \mathbf{R} \leqslant \mathbf{Y} \leqslant 10^{9} - \mathbf{R}$.

**Test set 1 (3 Pts, Visible Verdict)**

- $\mathbf{A} = \mathbf{B} = 10^{9} - 5$.

**Test set 2 (12 Pts, Visible Verdict)**

- $\mathbf{A} = \mathbf{B} = 10^{9} - 50$.

**Test set 3 (19 Pts, Hidden Verdict)**

- $\mathbf{A} = 10^{9} / 2$.
- $\mathbf{B} = 10^{9}$.


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
title: "[GCJ 2009 #2] Watering Plants"
layout: "post"
diff: 提高+/省选-
pid: P13443
tag: ['数学', '计算几何', '2009', '二分', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2009 #2] Watering Plants
## 题目描述

In your greenhouse, you have a number of plants which you need to water.

Each of the plants takes up an area which is a circle. No two of the plants overlap or touch each other.

You are going to buy two sprinklers. Each of the sprinklers will spray everything within a circle of radius $R$ with water.

One of the sprinklers will run in the morning, and one will run at night. For you to be satisfied that a plant will get enough water, either the whole area of the plant must be watered in the morning, or the whole area of the plant must be watered at night. So each of the circles representing a plant must be completely in one or both of the two circles representing the area the sprinklers can water.

Given the location and radius of each of the plants, find the minimum radius $R$ so that it is possible to place the two sprinklers to water all the plants. The sprinklers will be installed on the ceiling, so a sprinkler's position can be inside the area of a plant.
## 输入格式

* One line containing an integer $C$, the number of test cases in the input file.

For each test case, there will be:

* One line containing $N$, where $N$ is the number of plants you have.
* $N$ lines, one for each plant, containing three integers "$X$ $Y$ $R$", where $(X, Y)$ are the coordinates of the center of the plant, and $R$ is the radius of the plant.

## 输出格式

For each test case:

* One line containing the string "Case #$x$: $R$" where $x$ is the number of the test case, starting from 1, and $R$ is the minimum radius of the sprinklers.

Any answer with absolute or relative error of at most $10^{-5}$ will be accepted.
## 样例

### 样例输入 #1
```
2
3
20 10 2
20 20 2
40 10 3
3
20 10 3
30 10 3
40 10 3
```
### 样例输出 #1
```
Case #1: 7.000000
Case #2: 8.000000
```
## 提示

**Sample Explanation**

In the first case, a sprinkler of radius at least 7 centered at $(20,15)$ will water the first two plants. A sprinkler of radius at least 3 will water the plant at $(40,10)$.

In the second case, one of the two sprinklers will need a radius of at least 8. Note that the plant at $(30,10)$ must be covered entirely by one of the two sprinklers.

**Limits**

- $1 \leq X \leq 1000$
- $1 \leq Y \leq 1000$
- $1 \leq R \leq 100$

**Small Input(5 Pts)**

- Time limit: ~~30~~ 6 seconds.
- $1 \leq C \leq 10$
- $1 \leq N \leq 3$

**Large Input(25 Pts)**

- Time limit: ~~60~~ 12 seconds.
- $1 \leq C \leq 30$
- $1 \leq N \leq 40$



---

---
title: "[GCJ 2008 Qualification] Fly Swatter"
layout: "post"
diff: 提高+/省选-
pid: P13456
tag: ['数学', '计算几何', '2008', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2008 Qualification] Fly Swatter
## 题目描述

What are your chances of hitting a fly with a tennis racquet?

To start with, ignore the racquet's handle. Assume the racquet is a perfect ring, of outer radius $R$ and thickness $t$ (so the inner radius of the ring is $R - t$).

The ring is covered with horizontal and vertical strings. Each string is a cylinder of radius $r$. Each string is a chord of the ring (a straight line connecting two points of the circle). There is a gap of length $g$ between neighbouring strings. The strings are symmetric with respect to the center of the racquet i.e. there is a pair of strings whose centers meet at the center of the ring.

The fly is a sphere of radius $f$. Assume that the racquet is moving in a straight line perpendicular to the plane of the ring. Assume also that the fly's center is inside the outer radius of the racquet and is equally likely to be anywhere within that radius. Any overlap between the fly and the racquet (the ring or a string) counts as a hit.
## 输入格式

One line containing an integer $N$, the number of test cases in the input file.

The next $N$ lines will each contain the numbers $f$, $R$, $t$, $r$ and $g$ separated by exactly one space. Also the numbers will have exactly 6 digits after the decimal point.

## 输出格式

$N$ lines, each of the form "Case #$k$: $P$", where $k$ is the number of the test case and $P$ is the probability of hitting the fly with a piece of the racquet.

Answers with a relative or absolute error of at most $10^{-6}$ will be considered correct.
## 样例

### 样例输入 #1
```
5
0.250000 1.000000 0.100000 0.010000 0.500000
0.250000 1.000000 0.100000 0.010000 0.900000
0.000010 10000.000000 0.000010 0.000010 1000.000000
0.400000 10000.000000 0.000010 0.000010 700.000000
1.000000 100.000000 1.000000 1.000000 10.000000
```
### 样例输出 #1
```
Case #1: 1.000000
Case #2: 0.910015
Case #3: 0.000000
Case #4: 0.002371
Case #5: 0.573972
```
## 提示

- $f$, $R$, $t$, $r$ and $g$ will be positive and smaller or equal to 10000.
- $t < R$
- $f < R$
- $r < R$

**Small dataset (5 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 30$
- The total number of strings will be at most 60 (so at most 30 in each direction).

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 100$
- The total number of strings will be at most 2000 (so at most 1000 in each direction).



---

---
title: "[SWERC 2023] Break a leg!"
layout: "post"
diff: 提高+/省选-
pid: P13799
tag: ['计算几何', '2023', 'ICPC', '双指针 two-pointer']
---
# [SWERC 2023] Break a leg!
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/a2628cf785edc53f8245d1203533bdfe5a5f491a.png)

:::

For the first time, breakdance will be featured in the Olympics. And you get to participate! Well, you get to participate to the jury... More precisely, you get to build the table in front of which the jury will be seated: still, that is an impressive feat, congratulations!


Actually, the top of the table is already built: it is plane, has constant width and constant density, and its shape consists in the interior of an $N$-sided non-crossing polygon $P_1 P_2 \dots P_N$ in which no three vertices are collinear (i.e., no line goes through three vertices or more). You have three table legs of same length and negligible width. Your task is to place them at distinct corners of the table so that the table remains stable when standing on these legs. In other words, you must choose three vertices $P_i$, $P_j$ and $P_k$ of the polygon such that the centre of gravity of the polygon lies in the interior of the triangle $P_i P_j P_k$ (and not on its boundary).


In how many different ways can you do this? If two ways of placing legs differ only by a permutation
of the legs, they are not counted as different ways.
## 输入格式

The first line contains the number $N$. Then follow $N$ lines: the $i^\text{th}$ of these lines contains two space-separated integers $x_i$ and $y_i$, which are the $x$-coordinate and the $y$-coordinate of the vertex $P_i$.

**Limits**
	
- $3 \leq N \leq 100~000$;
- $-1~000~000 \leq x_i \leq 1~000~000$ and $-1~000~000 \leq y_i \leq 1~000~000$ for all $i \leq N$;
- whenever $1 \leq i < j < k \leq N$, the vertices $P_i$, $P_j$ and $P_k$ are not collinear;
- the polygonal shape $P_1 P_2 \dots P_N$ is non-crossing.


## 输出格式

The output should contain a single line, consisting of a single integer: the number of ways of placing legs such that the table remains stable.
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
0
```
### 样例输入 #2
```
4
0 0
5 0
6 6
0 5
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
5
0 0
2 0
2 20
1 1
0 20
```
### 样例输出 #3
```
5
```


---

---
title: "平面最近点对（加强版）"
layout: "post"
diff: 提高+/省选-
pid: P1429
tag: ['计算几何', '递归', '分治']
---
# 平面最近点对（加强版）
## 题目背景

[P7883](/problem/P7883) 平面最近点对（加强加强版）
## 题目描述

给定平面上 $n$ 个点，找出其中的一对点的距离，使得在这 $n$ 个点的所有点对中，该距离为所有点对中最小的

## 输入格式

第一行：$n$ ，保证 $2\le n\le 200000$ 。

接下来 $n$ 行：每行两个实数：$x\ y$ ，表示一个点的行坐标和列坐标，中间用一个空格隔开。

## 输出格式

仅一行，一个实数，表示最短距离，精确到小数点后面 $4$ 位。
## 样例

### 样例输入 #1
```
3
1 1
1 2
2 2
```
### 样例输出 #1
```
1.0000
```
## 提示

数据保证 $0\le x,y\le 10^9$


---

---
title: "独眼兔"
layout: "post"
diff: 提高+/省选-
pid: P1863
tag: ['计算几何', 'NOI 导刊']
---
# 独眼兔
## 题目描述

太郎有一只特殊的兔子，它只有一只左眼，所以当它移动时是不能向右转弯的。一天，太郎跟独眼兔做一个游戏，太郎在平面内放了 $n$ 个萝卜，每个萝卜有个位置 $(x_i,y_i)$，且任意两个萝卜的 $x_i$，$y_i$ 都是不相同的，独眼兔要去吃这些萝卜。设萝卜 $A(x_i,y_i)$ 是所有萝卜中最小的，那独眼兔会从 $(0,y_i)$ 出发，走向萝卜 $A$，然后开始吃萝卜。当它吃完一个萝卜后，独眼兔会确定下一个萝卜作为目标，然后径直向萝卜走去，当然当它移动的时候是不能向右转弯的。独眼兔还有一个特点，它走过的路径上会留下特殊的气味，所以独眼兔不希望它将要走的路与前面它走过的路相交。太郎想知道独眼兔如何才能吃到最多的萝卜。
## 输入格式

第一行是个整数 $n$；

接下来 $n$ 行，每行两个整数。第 $i+1$ 行表示第 $i$ 号萝卜的位置 $(x_i,y_i)$。
## 输出格式

一行，输出最多能吃到的萝卜数，后面输出吃萝卜的顺序。
## 样例

### 样例输入 #1
```
10
4 5
9 8
5 9
1 7
3 2
6 3
10 10
8 1
2 4
7 6

```
### 样例输出 #1
```
10 8 7 3 4 9 5 6 2 1 10
```
## 提示

- $40\%$ 的数据，$n\le100$；
- $100\%$ 的数据，$n\le1000$，$0\lt x_i\le10^4$，$0\lt y_i\le10^4$。


---

---
title: "城墙"
layout: "post"
diff: 提高+/省选-
pid: P2116
tag: ['计算几何']
---
# 城墙
## 题目描述

有一次，一个贪婪的国王命令他的骑士在他的城堡外修建一堵围墙，要求围墙离城堡的最近距离不能少于 $L$。

城堡是一个 $n$ 边形，国王非常吝啬，不愿意多花建一米的围墙，多建的话他会杀掉负责修建的骑士。

请你帮助这个倒霉的骑士，帮他求出最少需要修建多长的围墙。
## 输入格式

第一行两个整数 $n$，$L$ 表示多边形的边数和最小距离。

接下里 $n$ 行，每行两个整数，表示多边形上的点的坐标。
## 输出格式

一行一个整数，即最小的围墙长度，四舍五入到整数。
## 样例

### 样例输入 #1
```
9 100
200 400
300 400
300 300
400 300
400 400
500 400
500 200
350 200
200 200
```
### 样例输出 #1
```
1628
```
## 提示

#### 数据规模与约定
- 对于 $100\%$ 的数据，保证 $3\le n\le1000$，$1\le L\le1000$，$-10^4\leq x_i,y_i\leq 10^4$。


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
title: "[HNOI2012] 三角形覆盖问题"
layout: "post"
diff: 提高+/省选-
pid: P3219
tag: ['计算几何', '2012', '各省省选', '平衡树', '湖南', '枚举']
---
# [HNOI2012] 三角形覆盖问题
## 题目描述

二维平面中，给定   N个等腰直角三角形（每个三角形的两条直角边分别平行于坐标轴，斜边从左上到右下）。我们用三个非负整数( x, y, d)来描述这样一个三角形，三角形三个顶点的坐标 分别为(x, y), (x + d, y)和(x, y +     d)。要求计算这   N个三角形所覆盖的总面积。例如，下图有 3 个三角形，覆盖的总面积为 11.0。

![](https://cdn.luogu.com.cn/upload/image_hosting/1459ccln.png)

## 输入格式

输入文件第一行为一个正整数N，表示三角形的个数。

接下来的 N行每行有用空格隔开的三个非负整数，x, y, d，描述一个三角形的顶点坐标，分别为(x, y), (x + d, y), ( x, y+d)，其中 x, y, d 满足0<= x, y, d<=1000000。



## 输出格式

仅包含一行，为一个实数  S，表示所有三角形所覆盖的总面积，输出恰好保留一位小数。输入数据保证  S<=2^31 。

## 样例

### 样例输入 #1
```
3
1 1 4
2 0 2
3 2 2
```
### 样例输出 #1
```
11.0
```
## 提示

对于50%的数据，1<=  N<=500；  
100%的数据，1<=N<=10000。


---

---
title: "[HAOI2014] 穿越封锁线"
layout: "post"
diff: 提高+/省选-
pid: P3738
tag: ['计算几何', '2014', '河南', '各省省选']
---
# [HAOI2014] 穿越封锁线
## 题目描述

某敌占区是一个封闭的多边形，用相邻的顶点集合 $P_1(x_1,y_1)$，$P_2(x_2,y_2)$，$\cdots$，$P_n(x_n,y_n)$ 表示。

我方侦察员 ZDM-007 要穿越敌占区的封锁线，为了安全起见，ZDM-007 行走的路线垂直于 X 坐标轴，从南向北穿越。

现在已知侦察员 ZDM-007 所处的位置，你能算出他在穿越封锁线时，其路线在敌占区内的总长度？

![](https://cdn.luogu.com.cn/upload/pic/5207.png)

## 输入格式

第一行：$n$ 表示多边形顶点的个数

接下来 $n$ 行：$x_i,x_i$ 表示多边形的顶点坐标。（按逆时针顺序给出）

最后一行：$X,Y$ 表示侦察员初始时所处的位置。

## 输出格式

侦察员穿越封锁线时，在敌占区内的总长度。（输出仅保留整数部分）

## 样例

### 样例输入 #1
```
7 
0 1 
2 0
4 1
2 2 
4 3 
2 4 
0 3 
3 -1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
4
10 100
10 0
100 0
100 100
100 -80
```
### 样例输出 #2
```
0
```
## 提示

【约束条件】

$3\le n\le 50,0\le x_i,y_i\le1000,0\le X \le1000,-100\le Y < 0$。


---

---
title: "李彬的几何"
layout: "post"
diff: 提高+/省选-
pid: P3744
tag: ['数学', '贪心', '计算几何', 'Special Judge', '枚举', '叉积']
---
# 李彬的几何
## 题目背景

李彬有一个凸多边形(不知道什么是凸多边形的同学可以查百度百科)P。

## 题目描述

P 有 n 个顶点p1,p2 ,p3 ,…,pn 。顶点 pi在 2 维平面上的坐标为( xi,yi )。这些顶点是按照顺时针顺序给出的。

李彬可以指定一个实数 D，然后将每个顶点最多移动 D 个单位距离。现在李彬想知道，如果他想使这个凸多边形不再是凸多边形，那么 D 的最小值是多少。

## 输入格式

第一行给出 1 个整数 n。

接下来 n 行，每行给出一个顶点，给出两个整数，分别是这个顶点的 xi和 yi。保证以顺时针顺序给出，并且形成一个严格的凸多边形。

## 输出格式

输出一个实数 D，代表使这个凸多边形不再凸的最小 D 值。

设你的答案为 a,标准答案为 b,只有当 a,b 满足$\frac{|a-b|}{max(1,b)} \le 10^{-4}$的时候，你是对的。

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
0.3535533906

```
### 样例输入 #2
```
6
5 0
10 0
12 -4
10 -8
5 -8
3 -4
```
### 样例输出 #2
```
1.0000000000

```
## 提示

对于 100%的数据，4<=n<=1000 ,-10^9<=xi,yi<=10^9。



---

---
title: "幽幽子吃西瓜"
layout: "post"
diff: 提高+/省选-
pid: P3788
tag: ['计算几何', '洛谷原创']
---
# 幽幽子吃西瓜
## 题目背景

 ![](https://cdn.luogu.com.cn/upload/pic/5575.png) 

西行寺幽幽子是冥界的亡灵，她是一个标准的吃货，现在她的面前摆着一个妖梦替她准备的大西瓜。

## 题目描述

妖梦费了好大的劲为幽幽子准备了一个大西瓜，甚至和兔子铃仙打了一架。现在妖梦闲来无事，就蹲在一旁看幽幽子吃西瓜。西瓜可以看作一个标准的球体，瓜皮是绿色的，瓜瓤是红色的，瓜皮的厚度可视为0。妖梦恰好以正视的角度看着这个西瓜。幽幽子是一个吃货，妖梦一走神，自己背后的刀就不见了，而西瓜也被切掉了一块。幽幽子切西瓜时刀面始终垂直于桌面，并且切下的一块在俯视图中正好是一个以西瓜中心为顶点，半径为西瓜半径的扇形。如图所示，是一种满足条件的情况

俯视:

 ![](https://cdn.luogu.com.cn/upload/pic/5576.png) 

正视:

 ![](https://cdn.luogu.com.cn/upload/pic/5577.png) 

妖梦看着红红绿绿的西瓜，忽然陷入思考，红色的西瓜瓤占整个西瓜可视面积的百分之多少呢？但她对几何一窍不通，于是想问问幽幽子，但幽幽子正抱着切下来的西瓜大吃特吃，没有理会妖梦。于是她想让你来帮她解决这个问题。

为了方便描述问题，我们为俯视图建立一个平面极坐标系，极点在俯视图圆形(扇形)的正中央，极轴方向竖直向下。极轴所对应的角度为0度，角度逆时针依次增加，直到转一圈又回到极轴。因此角度范围是[0,360)。幽幽子会切掉西瓜从a°到b°的这一整块。

## 输入格式

第一行一个整数T，表示数据组数。

接下来T行每行两个整数a,b。表示切掉范围的起始角度和终止角度。若a>b，则切掉的角度为[a,360)∪[0,b]这一范围。

## 输出格式

T行，每行一个实数后跟一个百分号“%”，表示被切掉一部分的西瓜的正视图(平行投影)中，红色的西瓜瓤占西瓜总可视面积的百分比。在此题中，妖梦的视野方向平行于俯视图的极轴，并且极轴射线指向妖梦。

输出的实数四舍五入保留一位小数，你的答案被判作正确，当且仅当与标准答案完全相同。

## 样例

### 样例输入 #1
```
2
90 270
315 45
```
### 样例输出 #1
```
0.0%
70.7%
```
## 提示

样例说明:

第一个样例中，切掉的西瓜恰好在背面，在妖梦的角度看起来与未切过的西瓜并无区别，因此输出0%。第二个样例中，切掉了从315°~45°这一部分,经过计算，得到答案为sqrt(2)/2，化成小数得到0.707,即70.7%

本题目共有10个测试点。

对于第1个测试点，a,b∈{0,90,180,270}。

对于第2个测试点，270<=a<=359,0<=b<=90。

对于第3,4个测试点，180<=a<=359,0<=b<=179。

对于全部测试点，0<=a,b<=359,a≠b。

1<=T<=10000

命题人:orangebird



---

---
title: "[NOI2004] 降雨量"
layout: "post"
diff: 提高+/省选-
pid: P4273
tag: ['计算几何', '2004', 'NOI']
---
# [NOI2004] 降雨量
## 题目描述

M 国是个多雨的国家，尤其是 P 城，频繁的降雨给人们的出行带来了不少麻烦。为了方便行人雨天过马路，有关部门在每处人行横道的上空都安装了一种名为“自动伞”的装置。（如图 $1$ 所示）
![](https://cdn.luogu.com.cn/upload/image_hosting/109hsm74.png)
每把自动伞都可以近似地看作一块长方形的板，厚度不计。这种伞有相当出色的吸水能力，落到上面的雨水都会完全被伞顶的小孔吸入，并通过管道运走。不下雨时，这些伞闲置着。一旦下雨，它们便立刻开始作匀速率直线往返运动：从马路的一边以固定的速率移动到另一边，再从另一边以相同的速率返回，如此往复，直到雨停为止。任何时刻自动伞都不会越过马路的边界。有了自动伞，下雨天没带伞的行人只要躲在伞下行走，就不会被雨淋着了。

由于自动伞的大小有限，当需要使用自动伞过马路的人比较多时，一把自动伞显然是不够的，所以有关部门在几处主要的人行横道上空安装了多把自动伞。每把自动伞的宽度都等于人行横道的宽度，高度各不相同，长度不一定相同，移动速率也不一定相同。

现在已知一处人行横道的详细情况，请你计算从开始下雨到 $T$ 秒钟后的这段时间内，一共有多少体积的雨水降落到人行横道上。
## 输入格式

第一行有四个整数 $N$，$W$，$T$，$V$。$N$ 表示自动伞的数目，$W$ 表示马路的宽度，$T$ 表示需要统计从开始下雨到多长时间后的降雨情况，$V$ 表示单位面积单位时间内的降雨体积。

为了描述方便，我们画出了一个如图 $2$ 所示的天空中五把伞的剖面图，取马路左边界为原点，取向右为 $x$ 轴正方向，取向上为 $y$ 轴正方向，建立平面直角坐标系。这样，每把自动伞都可以看作平面上的一条线段。

![](https://cdn.luogu.com.cn/upload/image_hosting/5z9mrtlz.png)

接下来的 $N$ 行，每行用三个整数描述一把自动伞。第一个数 $x$ 是伞的初始位置，用它左端点的横坐标表示。第二个数 $l$ 是伞的长度，即 $x$ 方向上的尺寸。第三个数 $v$ 是伞的速度，$v$ 的大小表示移动的速率。如果 $v > 0$，表示开始时伞向右移动；如果 $v < 0$，表示开始时伞向左移动；如果 $v = 0$，表示伞不动。
## 输出格式

输出文件只包含一个实数，表示从开始下雨到 $T$ 秒钟后，一共有多少体积的
水降落到人行横道上。输出结果精确到小数点后第二位。
## 样例

### 样例输入 #1
```
2 4 3 10
0 1 1
3 1 -1
```
### 样例输出 #1
```
65.00
```
## 提示

【约定】

○ 雨点均匀地匀速竖直下落

○ 自动伞和马路两者都是水平的

○ 自动伞的宽度和人行横道的宽度相等，都等于 $1$

○ $N \leq 10$

○ $W \leq 100$

○ $T \leq 100$

○ $V \leq 50$

○ 所有自动伞的往返次数之和不超过 $250$，一来一回算一个往返。



---

---
title: "GodFly求解法向量"
layout: "post"
diff: 提高+/省选-
pid: P4894
tag: ['数学', '计算几何', 'Special Judge', '向量']
---
# GodFly求解法向量
## 题目背景

“遇到函数无脑求导，遇到几何无脑建系。”是铁头娃的公共特征。

作为喜欢建系的一个铁头娃，$GodFly$经常需要计算法向量。
## 题目描述

定义平面$\alpha$内有两相交向量$\overrightarrow a=(x_1,y_1,z_1)$，$\overrightarrow b=(x_2,y_2,z_2)$，若$\overrightarrow z=(x,y,z)$为平面$\alpha$的法向量，则：

![](https://cdn.luogu.com.cn/upload/pic/30949.png)

现给出$\overrightarrow a$及$\overrightarrow b$的坐标，求出一个法向量$\overrightarrow z$，并输出其坐标。

**SPJ已更新**
## 输入格式

本题有多组数据；对于每组数据，一行六个数，分别为$x_1,y_1,z_1,x_2,y_2,z_2$。
## 输出格式

对于每组数据，三个数，$x,y,z$，之间用空格隔开。

**每组数据之间用空行隔开。**

**法向量的坐标不可都为$0$。**
## 样例

### 样例输入 #1
```
1 2 3 3 2 1
```
### 样例输出 #1
```
1 -2 1
```
## 提示

**【数据范围】**

所有坐标（包括答案）均在$32$位**整数**范围内。

对于$30$%的数据，只有单组输入；

对于$100$%的数据，输入组数$<=5*10^4$，且输入的坐标均为绝对值不超过$5*10^4$的正整数；

样例数据在**data.zip\vector\**中。

**【提示】**

本题有$Special$ $Judge$，输出任意一组解即可。


---

---
title: "[USACO19OPEN] Cow Steeplechase II S"
layout: "post"
diff: 提高+/省选-
pid: P5428
tag: ['计算几何', '2019', '二分', 'USACO', '叉积']
---
# [USACO19OPEN] Cow Steeplechase II S
## 题目描述

在过去，Farmer John曾经构思了许多新式奶牛运动项目的点子，其中就包括奶牛障碍赛，是奶牛们在赛道上跑越障碍栏架的竞速项目。他之前对推广这项运动做出的努力结果喜忧参半，所以他希望在他的农场上建造一个更大的奶牛障碍赛的场地，试着让这项运动更加普及。

Farmer John为新场地精心设计了 $ N $ 个障碍栏架，编号为 $ 1 \ldots 
 N $ （ $ 2 \leq N \leq 10^5 $ ），每一个栏架都可以用这一场地的二维地图中的一条线段来表示。这些线段本应两两不相交，包括端点位置。

不幸的是，Farmer John在绘制场地地图的时候不够仔细，现在发现线段之间出现了交点。然而，他同时注意到只要移除一条线段，这张地图就可以恢复到预期没有相交线段的状态（包括端点位置）。

请求出Farmer John为了恢复没有线段相交这一属性所需要从他的计划中删去的一条线段。如果有多条线段移除后均可满足条件，请输出在输入中出现最早的线段的序号。
## 输入格式

输入的第一行包含 $ N $ 。余下 $ N $ 行每行用四个整数 $ x_1,y_1,x_2,y_2 $ 表示一条线段，均为至多 $ 10^9 $ 的非负整数。这条线段的端点为 $ (x_1,y_1) $ 和 $ (x_2,y_2) $ 。所有线段的端点各不相同。
## 输出格式

输出在输入中出现最早的移除之后可以使得余下线段各不相交的线段序号。
## 样例

### 样例输入 #1
```
4
2 1 6 1
4 0 1 5
5 6 5 5
2 7 1 3
```
### 样例输出 #1
```
2
```
## 提示

注意：由于线段端点坐标数值的大小，在这个问题中你可能需要考虑整数类型溢出的情况。


---

---
title: "[CTSC1998] 监视摄像机"
layout: "post"
diff: 提高+/省选-
pid: P5696
tag: ['计算几何', '1998', '半平面交', 'CTSC/CTS']
---
# [CTSC1998] 监视摄像机
## 题目背景

CTSC1998 D1T2

一个著名的仓库管理公司 SERKOI 请你的公司为其安装一套闭路监视系统。

由于 SERKOI 财力有限,每个房间只能安装一台摄像机作监视用，不过它的镜头可以向**任意方向**旋转。
## 题目描述

我们的问题是确定摄像机的位置，以确保房间的每一个角落都能被它监视到。

例如，图一和图二是某两个房间的示意图，每个房间用一个封闭的多边形表示。

![](https://cdn.luogu.com.cn/upload/image_hosting/arcbvz22.png)

图中的每条边表示一面墙。

对于图一所示的房间，我们将摄像机安置在标黑点的位置就能满足要求；

而对于图二所示的房间，无论将摄像机安置在哪里都无法使其满足要求。
 
写一个程序，对于给定的房间示意图，判断是否有可能在这个房间中的某一位置安置**一台**摄像机，使其能监视到这个房间的**任何一个**角落。
## 输入格式

输入文件包含一个或多个房间示意图的描述信息。

每个描述信息的第一行是一一个正整数 $n$，表示该房间的示意图为一个 $n$ 边形。

以下 $n$ 行每行包括用空格符隔开的两个整数 $x,y$，依次为这个 $n$ 边形的按顺时针方向排列的 $n$ 个顶点在直角坐标系中的横纵坐标。

$n=0$ 表示输入文件结束。
## 输出格式

对于每个房间，首先输出一行该房间的编号信息 `Room #k:`，$k$ 按照输入次序从 $1$ 开始计数。

下一行是判断结果，如果摄像机在房间中某处安置能满足条件，输出 `Surveillance is possible.`，否则输出 `Surveillance is impossible.`

每两个房间的输出结果之间用一个空行隔开。
## 样例

### 样例输入 #1
```
4
0 0
0 1
1 1
1 0
8
0 0 
3 0
4 3
2 2
3 4
4 4
4 5
0 5
0

```
### 样例输出 #1
```
Room #1:
Surveillance is possible.

Room #2:
Surveillance is impossible.

```
## 提示

【数据范围】

$4 \leq n \leq 100$，$-1000 \leq x,y \leq 1000$。


---

---
title: "「SWTR-3」Plane Mirrors"
layout: "post"
diff: 提高+/省选-
pid: P5859
tag: ['计算几何', '线段树', 'O2优化']
---
# 「SWTR-3」Plane Mirrors
## 题目背景

小 $\mathrm{A}$ 在学物理。

老师在讲“平面镜成像”这个物理现象。

但老师讲课太无聊，所以他就睡着了。
## 题目描述

小 $\mathrm{A}$ 梦见自己站在了一个平台上，在他的周围有一些平面镜，我们假定他的位置为 $(0,0)$。

他发现，每个平面镜都有一个初始不透明度，记做 $v_i$。

下文中，我们定义：

- 一个射线的“不透明度”为：该射线穿过的所有平面镜的初始不透明度之和。

- 一个平面镜的“视觉不透明度”为：所有**从 $(0,0)$ 发出**且**经过该平面镜**的射线的不透明度最大值。

小 $\mathrm{A}$ 突然发现自己能够控制这些平面镜，于是就有了下面这道题目。

小 $\mathrm{A}$ 需要你完成以下操作：

`1 x1 y1 x2 y2 v`：变出一个两端分别在 $(x_1,y_1),(x_2,y_2)$，初始不透明度为 $v$ 的平面镜。

`2 d`：摧毁第 $d$ 个变出来的平面镜，保证未被摧毁。

`3 x y`：设 $\mathrm{A=(0,0),B=(x,y)}$，询问射线 $\mathrm{AB}$ 的不透明度。

`4 d`：询问第 $d$ 个平面镜的视觉不透明度，如已被摧毁则输出 `oops!`。
## 输入格式

第一行，一个整数 $n$，表示操作次数。

接下来 $n$ 行，第 $i$ 行先是一个整数 $opt$，然后：

- 如果 $opt=1$，五个整数 $x_1,y_1,x_2,y_2,v$。

- 如果 $opt=3$，两个整数 $x,y$。

- 否则一个整数 $d$。
## 输出格式

对于每一个 $3,4$ 询问，输出一行答案。
## 样例

### 样例输入 #1
```
11
1 -1 2 2 -1 7
1 2 2 -1 0 10
1 2 1 1 -1 17
3 5 4
3 -99999 0
3 -3 6
3 1 -1
4 2
2 1
4 2
4 1

```
### 样例输出 #1
```
7
10
17
17
17
10
oops!
```
## 提示

---

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/f7i3u2l6.png)

如图，蓝色代表射线，红色代表平面镜。

对于第 $1$ 次询问：可以看出射线只穿过了平面镜 $1$，答案为 $7$。

对于第 $2$ 次询问：可以看出射线只穿过了平面镜 $2$，答案为 $10$。

对于第 $3$ 次询问：可以看出射线穿过了平面镜 $1,2$，答案为 $7+10=17$。

对于第 $4$ 次询问，可以看出射线穿过了平面镜 $3$，答案为 $17$。

对于第 $5$ 次询问，可以看出穿过平面镜 $2$ 的不透明度最大的射线为 $(0,0)(2,2)$（射线不唯一），穿过了平面镜 $1,2$，答案为 $7+10=17$。

对于第 $6$ 次询问，可以看出穿过平面镜 $2$ 的不透明度最大的射线为 $(0,0)(2,2)$（射线不唯一），穿过了平面镜 $2$，答案为 $10$。

对于第 $7$ 次询问，因为平面镜 $1$ 已被摧毁，所以输出 `oops!`。

---

### 数据范围与约定

测试点编号|$n\leq$|特殊性质
:-:|:-:|:-:
$1-4$|$1000$|$x,y$ 绝对值小于 $10^3$ 且**没有 $4$ 询问**
$5-8$|$2\times 10^5$|所有 $y$ 相等
$9-12$|$2\times 10^5$|$x\ge 0$
$13-20$|$2\times 10^5$|无

对于 $100\%$ 的数据，有 $1\leq n\leq 2\times 10^5$，$1\leq v\leq 10^3$ 且 $0\leq |x|,|y|\leq 10^5$。

保证平面镜的总数不会超过 $10^5$。

保证所有平面镜不会穿过 $(0,0)$，但**不保证**平面镜会退化成一个点。

保证所有 $3$ 询问 $(x,y)\neq(0,0)$。

---

对于所有测试点，时间限制 $2\mathrm{s}$，空间限制 $128\mathrm{MB}$。


---

---
title: "[ICPC 2019 WF] Beautiful Bridges"
layout: "post"
diff: 提高+/省选-
pid: P6252
tag: ['计算几何', '2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Beautiful Bridges
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。

## 题目描述

What connects us all? Well, it is often bridges. Since ancient times, people have been building bridges for roads, for trains, for pedestrians, and as aqueducts to transport water. It is humanity's way of not taking inconvenient geography for an answer.

The company Arch Bridges Construction (ABC) specializes in—you guessed it—the construction of arch bridges. This classical style of bridge is supported by pillars that extend from the ground below the bridge. Arches between pillars distribute the bridge's weight onto the adjacent pillars.

The bridges built by ABC often have pillars spaced at irregular intervals. For aesthetic reasons, ABC's bridges always have semicircular arches, as illustrated in Figure B.1. However, while a bridge arch can touch the ground, it cannot extend below the ground. This makes some pillar placements impossible.

![](https://cdn.luogu.com.cn/upload/image_hosting/r95zwobd.png)

Given a ground profile and a desired bridge height $h$, there are usually many ways of building an arch bridge. We model the ground profile as a piecewise-linear function described by $n$ key points $(x_1, y_1),(x_2, y_2), \dots ,(x_n, y_n)$, where the $x-\text{coordinate}$ of a point is the position along the bridge, and the $y-\text{coordinate}$ is the elevation of the ground above sea level at this position along the bridge. The first and last pillars must be built at the first and last key points, and any intermediate pillars can be built only at these key points. The cost of a bridge is the cost of its pillars (which is proportional to their heights) plus the cost of its arches (which is proportional to the amount of material used). So a bridge with $k$ pillars of heights $h_1, \dots , h_k$ that are separated by horizontal distances $d_1, \dots , d_{k - 1}$ has a total cost of
$$\alpha \cdot \sum_{i = 1}^{k} h_i + \beta \cdot \sum_{i = 1}^{k - 1} d_i^2$$
for some given constants $\alpha$ and $\beta$. ABC wants to construct each bridge at the lowest possible cost.
## 输入格式

The first line of input contains four integers $n, h, \alpha, and \beta$, where $n$ ($2 \leq n \leq 10^4$) is the number of points describing the ground profile, $h$ ($1 \leq h \leq 10^5$) is the desired height of the bridge above sea level, and $\alpha, \beta$ ($1 \leq \alpha, \beta \leq 10^4$) are the cost factors as described earlier. Then follow $n$ lines, the $i^{\text{th}}$ of which contains two integers $x_i, y_i$ ($0 \leq x_1 < x_2 < . . . < x_n \leq 10^5$ and $0 \leq yi < h$), describing the ground profile.
## 输出格式

Output the minimum cost of building a bridge from horizontal position $x_1$ to $x_n$ at height $h$ above sea level. If it is impossible to build any such bridge, output `impossible`.
## 样例

### 样例输入 #1
```
5 60 18 2
0 0
20 20
30 10
50 30
70 20
```
### 样例输出 #1
```
6460
```
### 样例输入 #2
```
4 10 1 1
0 0
1 9
9 9
10 0
```
### 样例输出 #2
```
impossible
```
## 提示

Source: ICPC 2019 World Finals.
## 题目翻译

给定一个地形剖面图，用 $n$（$n≤10^4$）个点描述，点 $i$ 和点 $i+1$ 之间有直线连接的地面。

你需要建一座拱桥，连接点 $1$ 和点 $n$，桥面的高度为 $h$。

你可以在桥中间建若干个柱子，以分配重量，柱子只能恰好建在给出的 $n$ 个点上（点 $1$ 和点 $n$ 上必须有柱子）。

相邻的两根柱子之间需要建一个半圆形的拱，准确地说，拱的半径为两根柱子之间的距离的一半，并且与两根柱子和桥面相切。

拱可以与地面相切，但不能相交。

同时，桥的花费与柱子高度和拱面积有关，具体地，给出两个参数 $α$ 和 $β$，则花费为：

$$\alpha \cdot \sum_{i = 1}^{k} h_i + \beta \cdot \sum_{i = 1}^{k - 1} d_i^2$$

其中 $k$ 为柱子数量，$h_i$ 为第 $i$ 个柱子的高度，$d_i$ 为第 $i$ 个柱子到第 $i+1$ 个柱子的距离。

问是否可以建出桥，若可以，问最小花费，否则输出
`impossible` 。


---

---
title: "[BalticOI 2005] Polygon"
layout: "post"
diff: 提高+/省选-
pid: P6711
tag: ['计算几何', '2005', '二分', 'Special Judge', 'BalticOI（波罗的海）']
---
# [BalticOI 2005] Polygon
## 题目描述

给定一个凸包的每条边的长度，求这个凸包。
## 输入格式

第一行一个整数 $N$ 代表点数。       
接下来 $N$ 行每行一个整数 $a_i$ 代表一条边的长度，其中 $a_i$ 代表第 $i$ 个点与第 $i+1$ 个点之间的边的长度，$a_n$ 代表第 $n$ 个点与第 $1$ 个点之间的边的长度。
## 输出格式

$N$ 行每行两个实数 $x_i,y_i$ 代表一个点的坐标。（需要满足 $|x_i|,|y_i| \le 10^7$）     
如果有多组解任意输出一组即可。            
如果无解输出 `NO SOLUTION`。

**注意请按照逆时针输出输出凸包上的点。**          
虽然原题说顺时针或逆时针顺序输出皆可，但是在本题中 **请严格按照逆时针方向输出**。         
不一定必须按照编号的顺序输出，比如说点 $P_1\to P_2 \to P_3$ 是逆时针顺序，那么按照 $P_2 \to P_3 \to P_1$  也可。
## 样例

### 样例输入 #1
```
4
7
4
5
4 
```
### 样例输出 #1
```
0.5 2.5
7.5 2.5
4.5 6.5
0.5 6.5 
```
## 提示

#### 样例说明

对于样例 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/7bbhlpom.png)

#### 数据规模与约定

对于 $100\%$ 的数据，$3 \le  N \le 1000$，$1 \le a_i \le 10^4$。

**本题使用 Special Judge。**

感谢 spj 作者 @[tiger2005](https://www.luogu.com.cn/user/60864)。

#### 说明

翻译自 [BalticOI 2005 Day2 C Polygon](https://boi.cses.fi/files/boi2005_day2.pdf)。


---

---
title: "[ICPC 2014 WF] Crane Balancing"
layout: "post"
diff: 提高+/省选-
pid: P6894
tag: ['数学', '计算几何', '2014', 'ICPC']
---
# [ICPC 2014 WF] Crane Balancing
## 题目描述

Wherever there is large-scale construction, you will find cranes that do the lifting. One hardly ever thinks about what marvelous examples of engineering cranes are: a structure of (relatively) little weight that can lift much heavier loads. But even the best-built cranes may have a limit on how much weight they can lift.

The Association of Crane Manufacturers (ACM) needs a program to compute the range of weights that a crane can lift. Since cranes are symmetric, ACM engineers have decided to consider only a cross section of each crane, which can be viewed as a polygon resting on the $x$-axis.

![](https://cdn.luogu.com.cn/upload/image_hosting/2lyejm47.png)

   Figure 1: Crane cross section 

Figure 1 shows a cross section of the crane in the first sample input. Assume that every $1 \times 1$ unit of crane cross section weighs 1 kilogram and that the weight to be lifted will be attached at one of the polygon vertices (indicated by the arrow in Figure 1). Write a program that determines the weight range for which the crane will not topple to the left or to the right.
## 输入格式

The input consists of a single test case. The test case starts with a single integer $n$ ($3 \le n \le 100$), the number of points of the polygon used to describe the crane’s shape. The following $n$ pairs of integers $x_ i, y_ i$ ($-2\, 000 \le x_ i \le 2\, 000, 0 \le y_ i \le 2\, 000$) are the coordinates of the polygon points in order. The weight is attached at the first polygon point and at least two polygon points are lying on the $x$-axis.
## 输出格式

Display the weight range (in kilograms) that can be attached to the crane without the crane toppling over. If the range is $[a,b]$, display $\lfloor a \rfloor $ .. $\lceil b \rceil $. For example, if the range is $[1.5,13.3]$, display 1 .. 14. If the range is $[a,\infty )$, display $\lfloor a \rfloor $ .. inf. If the crane cannot carry any weight, display unstable instead.
## 样例

### 样例输入 #1
```
7
50 50
0 50
0 0
30 0
30 30
40 40
50 40

```
### 样例输出 #1
```
0 .. 1017

```
### 样例输入 #2
```
7
50 50
0 50
0 0
10 0
10 30
20 40
50 40

```
### 样例输出 #2
```
unstable

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

无论哪里有大规模的施工，您都会发现起重机可以起重。人们几乎从未想过工程起重机的奇妙例子是什么：一种（相对）重量很小的结构，可以举起更重的负载。但即使是最好的起重机也可能对它们可以举起的重量有限制。

起重机制造商协会（ACM）需要一个程序来计算起重机可以提升的重量范围。由于起重机是对称的，ACM工程师决定只考虑每台起重机的横截面，这可以看作是一个多边形，位于x-轴。

图1显示了第一个样本输入中起重机的横截面。

假设每个1×1单位起重机横截面重1公斤，要提升的重量将附着在其中一个多边形顶点（如图1中的箭头所示）。编写一个程序，确定起重机不会向左或向右倾倒的重量范围。

输入由单个测试用例组成。测试用例以单个整数n开头,用于描述起重机形状的多边形的点数。以下n对整数是按顺序排列的点的坐标。权重附着在第一个多边形点上，并且至少有两个多边形点位于x-轴。

输出格式

显示可在起重机不倒塌的情况下连接到起重机的重量范围（以千克为单位）。如果范围是 [a,b], 显示⌊a⌋ .. ⌈b⌉. 例如，如果范围是[1.5,13.3], 显示 1 ..14. 如果范围是[a,∞), 显示⌊a⌋ .. inf. 如果起重机不能承载任何重量，请显示unstable.


说明/提示

时间限制： 1000 ms， 内存限制： 1048576 kB.

2014年国际大学生编程大赛（ACM-ICPC）世界总决赛


---

---
title: "[BalticOI 1996] A SQUARE AND A CIRCLE (Day 1)"
layout: "post"
diff: 提高+/省选-
pid: P7651
tag: ['计算几何', 'BalticOI（波罗的海）', '1996']
---
# [BalticOI 1996] A SQUARE AND A CIRCLE (Day 1)
## 题目描述

一个平面上有一个正方形和一个圆，给定正方形的两个相对顶点的坐标和圆的圆心坐标和半径，求这个正方形和这个圆的公共面积。
## 输入格式

前两行包含正方形的两个相对顶点的坐标 （$x_1,y_1$）和（$x_2,y_2$），第三行包含圆心坐标（$x_3,y_3$）和半径 $r$，为实数。
## 输出格式

输出两个图形的公共面积，小数点后两位。
## 样例

### 样例输入 #1
```
0 5.0
10.00 -5
3.0 1 4.00
```
### 样例输出 #1
```
46.64
```
## 提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$-1200.00 \le x_i,y_i \le 1200.00$，$0 < r \le 200.00$。
#### 分值说明  
本题分值按 BOI 原题设置，**满分** $30$ 。
#### 题目说明  
来源于 Baltic Olympiad in Informatics 1996 的 [Day 1:A SQUARE AND A CIRCLE](https://boi.cses.fi/files/boi1996_day1.pdf) 。  
由 @[求学的企鹅](/user/271784) 翻译整理。


---

---
title: "「PMOI-5」棋盘"
layout: "post"
diff: 提高+/省选-
pid: P8154
tag: ['计算几何', 'Special Judge', '枚举', '构造']
---
# 「PMOI-5」棋盘
## 题目描述

给定一个无限大的棋盘（可以看做平面直角坐标系）和黑白子各 $n$ 颗，要求将黑白子不重叠地摆在棋盘的整点上，使得**恰好**存在 $n$ 条直线使得：

- 其穿过且**仅**穿过黑白子**共** 4 颗。

- 其按顺序穿过黑，白，白，黑子。

给出任意一种方案即可。
## 输入格式

输入数据仅一行，为题目中所述的 $n$。
## 输出格式

如果无法构造出方案，则输出 `NO`。

否则输出 $2n+1$ 行：第一行输出 `YES`。第 $2\sim n+1$ 行每行两个整数，为白子坐标 $x_i,y_i$。第 $n+2\sim 2n+1$ 行每行两个整数，为黑子坐标 $x_j,y_j$。

你需要保证 $-5\times 10^5\le x_i,y_i,x_j,y_j\le 5\times 10^5$。
## 样例

### 样例输入 #1
```
1
```
### 样例输出 #1
```
NO
```
### 样例输入 #2
```
7
```
### 样例输出 #2
```
YES
2 4
2 6
4 6
5 4
6 4
6 2
4 2
0 6
2 8
6 6
8 2
6 0
3 0
2 2

```
## 提示

【样例解释】

样例 2 解释：（输出按顺序为点 $A\sim N$（点 $A\sim G$ 为白子，点 $H\sim N$ 为黑子），直线如图所示）。

![](https://cdn.luogu.com.cn/upload/image_hosting/zyo823p8.png)

【数据范围】

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$n\equiv 0 \pmod{7}$；
- Subtask 2（20 pts）：$40\le n\le 400$；
- Subtask 3（30 pts）：$1\le n\le 9$；
- Subtask 4（40 pts）：无特殊限制。

对于 $100\%$ 的数据，$1\le n\le 10^3$。

[SPJ地址](https://www.luogu.com.cn/paste/eamtmrw5)

使用方法：编译为 `checker.exe` 后命令行同一目录下输入 ```checker.exe chessboard.in chessboard.out chessboard.ans```

需要搭配 `testlib.h` 一起使用，[testlib下载地址](https://github.com/MikeMirzayanov/testlib)。

如果发现 SPJ 出锅了请找出题人。


---

---
title: "[蓝桥杯 2013 国 B] 农场阳光"
layout: "post"
diff: 提高+/省选-
pid: P8608
tag: ['计算几何', '2013', '蓝桥杯国赛']
---
# [蓝桥杯 2013 国 B] 农场阳光
## 题目描述

X 星球十分特殊，它的自转速度与公转速度相同，所以阳光总是以固定的角度照射。

最近，X 星球为发展星际旅游业，把空间位置出租给 Y 国游客来晒太阳。每个租位是漂浮在空中的圆盘形彩云（圆盘与地面平行）。当然，这会遮挡住部分阳光，被遮挡的土地植物无法生长。

本题的任务是计算某个农场宜于作物生长的土地面积有多大。
## 输入格式

输入数据的第一行包含两个整数 $a,b$，表示某农场的长和宽分别是 $a$ 和 $b$，此时，该农场的范围是由坐标 $(0,0,0),(a,0,0),(a,b,0),(0,b,0)$ 围成的矩形区域。

第二行包含一个实数 $g$，表示阳光照射的角度。简单起见，我们假设阳光光线是垂直于农场的宽的，此时正好和农场的长的夹角是 $g$ 度，此时，空间中的一点 $(x,y,z)$ 在地面的投影点应该是 $(x+z \times \ctg(g),y,0)$，其中 $\ctg(g)$ 表示 $g$ 度对应的余切值。

第三行包含一个非负整数 $n$，表示空中租位个数。

接下来 $n$ 行，描述每个租位。其中第 $i$ 行包含 $4$ 个整数 $x_i,y_i,z_i,r_i$，表示第 $i$ 个租位彩云的圆心在 $(x_i,y_i,z_i)$ 位置，圆半径为 $r_i$。
## 输出格式

要求输出一个实数，四舍五入保留两位有效数字，表示农场里能长庄稼的土地的面积。
## 样例

### 样例输入 #1
```
10 10
90.0
1
5 5 10 5
```
### 样例输出 #1
```
21.46
```
### 样例输入 #2
```
8 8
90.0
1
4 4 10 5
```
### 样例输出 #2
```
1.81

```
### 样例输入 #3
```
20 10
45.0
2
5 0 5 5
8 6 14 6
```
### 样例输出 #3
```
130.15
```
## 提示

时限 1 秒, 64M。蓝桥杯 2013 年第四届国赛


---

---
title: "[蓝桥杯 2016 国 B] 广场舞"
layout: "post"
diff: 提高+/省选-
pid: P8645
tag: ['计算几何', '2016', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2016 国 B] 广场舞
## 题目描述

LQ 市的市民广场是一个多边形，广场上铺满了大理石的地板砖。

地板砖铺得方方正正，就像坐标轴纸一样。

以某四块砖相接的点为原点，地板砖的两条边为两个正方向，一块砖的边长为横纵坐标的单位长度，则所有横纵坐标都为整数的点都是四块砖的交点（如果在广场内）。

广场的砖单调无趣，却给跳广场舞的市民们提供了绝佳的参照物。每天傍晚，都会有大批市民前来跳舞。

舞者每次都会选一块完整的砖来跳舞，两个人不会选择同一块砖，如果一块砖在广场边上导致缺角或者边不完整，则没人会选这块砖。

（广场形状的例子参考图）

![](https://cdn.luogu.com.cn/upload/image_hosting/kjgaxse9.png)

现在，告诉你广场的形状，请帮 LQ 市的市长计算一下，同一时刻最多有多少市民可以在广场跳舞。
## 输入格式

输入的第一行包含一个整数 $n$，表示广场是 $n$ 边形的（因此有 $n$ 个顶点）。

接下来 $n$ 行，每行两个整数，依次表示 $n$ 边形每个顶点的坐标（也就是说广场边缘拐弯的地方都在砖的顶角上。数据保证广场是一个简单多边形。
## 输出格式

输出一个整数，表示最多有多少市民可以在广场跳舞。
## 样例

### 样例输入 #1
```
5
3 3
6 4
4 1
1 -1
0 4
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
3 3
```
### 样例输出 #2
```
4
```
## 提示

**【样例说明】**

广场如图所示，一共有 $7$ 块完整的地板砖，因此最多能有 $7$ 位市民一起跳舞。

**【数据规模与约定】**

对于 $30\%$ 的数据，$n$ 不超过 $100$，横纵坐标的绝对值均不超过 $100$。

对于 $50\%$ 的数据，$n$ 不超过 $1000$，横纵坐标的绝对值均不超过 $1000$。

对于 $100\%$ 的数据，$n$ 不超过 $1000$，横纵坐标的绝对值均不超过 $10^8$。

时限 1 秒, 256M。蓝桥杯 2016 年第七届


---

---
title: "[蓝桥杯 2020 省 A2] 荒岛探测"
layout: "post"
diff: 提高+/省选-
pid: P8718
tag: ['计算几何', '2020', 'Special Judge', '蓝桥杯省赛']
---
# [蓝桥杯 2020 省 A2] 荒岛探测
## 题目描述

科学家小蓝来到了一个荒岛, 准备对这个荒岛进行探测考察。

小蓝使用了一个超声定位设备来对自己进行定位。为了使用这个设备，小蓝需要在不同的点分别安装一个固定的发射器和一个固定的接收器。小蓝手中还有一个移动设备。定位设备需要从发射器发射一个信号到移动设备, 移动设备收到后马上转发，最后由接收器接收，根据这些设备之间传递的时间差就能计算出移动设备距离发射器和接收器的两个距离，从而实现定位。

小蓝在两个位置已经安装了发射器和接收器, 其中发射器安装在坐标 $\left(x_{A},y_{A}\right)$，接收器安装在坐标 $\left(x_{B},y_{B}\right)$ 。小蓝的发射器和接收器可能在岛上，也可能不在岛上。

小蓝的定位设备设计有些缺陷, 当发射器到移动设备的距离加上移动设备 到接收器的距离之和大于 $L$ 时, 定位设备工作不正常。当和小于等于 $L$ 时，定位设备工作正常。为了安全，小蓝只在定位设备工作正常的区域探测考察。

已知荒岛是一个三角形, 三个顶点的坐标分别为 $\left(x_{1}, y_{1}\right)$，$\left(x_{2},y_{2}\right)$，$\left(x_{3},y_{3}\right)$。

请计算，小蓝在荒岛上可以探测到的面积有多大。
## 输入格式

输入的第一行包含五个整数, 分别为 $x_{A}$，$y_{A}$，$x_{B}$，$y_{B}$，$L$。

第二行包含六个整数, 分别为 $x_{1}$，$y_{1}$，$x_{2}$，$y_{2}$，$x_{3}$，$y_{3}$。
## 输出格式

输出一行, 包含一个实数, 四舍五入保留 $2$ 位小数，表示答案。

考虑到计算中的误差，只要你的输出与参考输出相差不超过 $0.01$ 即可得分。 
## 样例

### 样例输入 #1
```
10 6 4 12 12
0 2 13 2 13 15

```
### 样例输出 #1
```
39.99

```
## 提示

**【样例说明】**

荒岛的形状和定位设备工作正常的区域如下图所示, 蓝色的三角形表示荒岛, 红色的曲线围成的区域为定位设备工作正常的区域。

![](https://luogu.oss-cn-hangzhou.aliyuncs.com/upload/vjudge_pic/lanqiao/2022_09_30_7ff7a90fd65c5962b43dg-14.jpg)

当输出为 $39.98、39.99$ 或 $40.00$ 时可以得分。

**【评测用例规模与约定】**

对于所有评测用例, 保证发射器的两个坐标不同, $-1000 \leq x_{A}, y_{A}, x_{B}, y_{B} \leq$ $1000,-1000 \leq x_{1}, y_{1}, x_{2}, y_{2}, x_{3}, y_{3} \leq 1000,-1000 \leq L \leq 1000$ 。 

蓝桥杯 2020 第二轮省赛 A 组 I 题。


---

---
title: "[蓝桥杯 2022 省 A] 扫描游戏"
layout: "post"
diff: 提高+/省选-
pid: P8777
tag: ['模拟', '计算几何', '2022', '排序', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 A] 扫描游戏
## 题目描述

有一根围绕原点 $O$ 顺时针旋转的棒 $OA$，初始时指向正上方（Y 轴正向）。平面中有若干物件，第 $i$ 个物件的坐标为 $\left(x_{i}, y_{i}\right)$，价值为 $z_{i}$。当棒扫到某个物件时，棒的长度会瞬间增长 $z_{i}$，且物件瞬间消失（棒的顶端恰好碰到物件也视为扫到)，如果此时增长完的棒又额外碰到了其他物件，也按上述方式消去（它和上述那个点视为同时消失）。

如果将物件按照消失的时间排序，则每个物件有一个排名，同时消失的物件排名相同，请输出每个物件的排名，如果物件永远不会消失则输出 $-1$。
## 输入格式

输入第一行包含两个整数 $n$、$L$，用一个空格分隔，分别表示物件数量和棒的初始长度。

接下来 $n$ 行每行包含第三个整数 $x_{i}, y_{i}, z_{i}$。

注意存在 $(x_{i}, y_{i})=(0,0)$ 的情况，这些点视为一开始就立刻被碰到。
## 输出格式

输出一行包含 $n$ 整数，相邻两个整数间用一个空格分隔，依次表示每个物件的排名。
## 样例

### 样例输入 #1
```
5 2
0 1 1
0 3 2
4 3 5
6 8 1
-51 -33 2
```
### 样例输出 #1
```
1 1 3 4 -1
```
## 提示

对于 $30 \%$ 的评测用例，$1 \leq n \leq 500$ ；

对于 $60 \%$ 的评测用例，$1 \leq n \leq 5000$;

对于所有评测用例，$1 \leq n \leq 2\times10^5,-10^{9} \leq x_{i}, y_{i} \leq 10^{9}, 1 \leq L, z_{i} \leq 10^{9}$ 。 

样蓝桥杯 2022 省赛 A 组 H 题。


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
title: "[ICPC 2021 Macao R] Laser Trap"
layout: "post"
diff: 提高+/省选-
pid: P9658
tag: ['计算几何', '2021', 'O2优化', '叉积', 'ICPC', '双指针 two-pointer', '澳门']
---
# [ICPC 2021 Macao R] Laser Trap
## 题目描述

BaoBao is playing the famous game $\textit{Elden Ring}$ these days. It's an open-world game in which you can control your character to travel from places to places. However, your character could also enter a trap and you need to figure out how to escape. Right now, BaoBao's character is stuck in a 2-dimensional plane with deadly lasers. There are $n$ laser generators (each can be regarded as a point) shooting laser beams between every pair of them (so there are $\frac{n(n-1)}{2}$ laser beams in total). The beams start and end at generator points and do not stretch to infinity.

Starting at point $(0,0)$, BaoBao wants to escape to point $(10^{10^{10^{10^{10}}}}, 10^{10^{10^{10^{10}}}})$ without touching any laser beam or generator. In order to do so, BaoBao can ask her friend DreamGrid to remove any number of laser generators, together with any laser beam that starts or ends at these generators. Output the minimum number of laser generators that need to be erased for the escape.

Note that BaoBao does not need to move in a specific direction to escape. Her escaping route can even be a curve if necessary.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^6$) indicating the number of laser generators.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($-10^9 \le x_i, y_i \le 10^9$) indicating the location of the $i$-th laser generator.

It is guaranteed that no two generators coincide, and no laser beam or generator will touch $(0,0)$.

It is also guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing one integer indicating the minimum number of generators that need to be removed.
## 样例

### 样例输入 #1
```
3
2
1 0
2 0
3
1 0
0 1
-1 -1
5
2 -1
1 2
-1 2
-2 -1
0 -2
```
### 样例输出 #1
```
0
1
2
```
## 提示

The second and the third sample test cases are shown below. Solid dots and lines represent the remaining laser generators and beams, while hollow dots and dashed lines represent the removed laser generators and beams. The arrow is the escaping route.

![](https://cdn.luogu.com.cn/upload/image_hosting/b0sz7cm0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/dwcsdmj6.png)
## 题目翻译

一直角坐标系中，BaoBao 在原点位置，平面上有 $n$ 个发射装置，任意两个发射器之间都有激光束，共 $(n-1) \times n / 2$ 条激光，BaoBao 的朋友可以去除任何发射器，问最少去除多少发射器，能使 BaoBao不会被激光所伤还能从 $(0,0)$ 逃逸到 $\left(10^{10^{10^{10^{10}}}}, 10^{10^{10^{10^{10}}}}\right)$。

tip.发射器不会重合，也不会存在激光束穿过 $(0,0)$。


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

