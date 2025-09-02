---
title: "[集训队互测 2023] 傅里叶与交通系统"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10003
tag: ['贪心', '计算几何', '集训队互测', '2023', 'Special Judge', 'O2优化', '凸包']
---
# [集训队互测 2023] 傅里叶与交通系统
## 题目背景

傅里叶荣升巴黎市交通部长。新官上任三把火，傅里叶决定重构巴黎市的交通系统。
## 题目描述

巴黎市的地图可以看成一个无限大的二维平面。傅里叶在上面修建了 $n$ 条传送带：第 $i$ 条传送带修建于 $x\in[p_{i-1},p_i),y\in\mathbb R$ 的区域中。对于 $x<p_0$ 或者 $x\geq p_n$ 的部分，傅里叶没有修建传送带。

当一个人处于第 $i$ 个传送带的区域内时，他会受传送带影响强制以 $v_i$ 单位长度每秒的速度向 $y$ 坐标增加的方向移动。$v_i$ 可能为负，此时其 $y$ 坐标会以相应的速度减小。

在位于未修建传送带的区域上时，$y$ 坐标不会受到传送带的影响。

除了受传送带带动以外，这个人自己也可以移动。为了避免在速度不同的传送带间移动时出现跌倒事故，傅里叶委托麦克斯韦设计了脚底附有钢板的鞋子，并且在传送带上安装了强力磁铁。穿上这种鞋子后，你将只能 **沿着与某条坐标轴平行，可能与坐标轴同向或反向** 的方向，以不超过 $V$ 单位长度每秒的速度移动。有了这种鞋子，**在从一个传送带移动到另一个传送带时，先前的速度不会被继承，这个人将立刻按照新传送带的移动速度来移动**（自然，自身的移动还是可以同步进行的）。

**个人的运动与传送带的运动是叠加的**。

**在任意时刻，这个人都可以自由调整其运动的速率、方向；可以通过不断在极小间隔内切换方向以达到近似斜向移动的效果，甚至动态调整速率、方向达成近似曲线运动的效果；但是其任意时刻都只能有平行于坐标轴、不超过 $V$ 的瞬时速率。**

**就算在没有铺设传送带的位置上，这个人仍然可以靠他的自由意志移动，不过还是只能沿坐标轴方向以不超过 $V$ 单位长度每秒移动**（问就是麦克斯韦的靴子已经成为概念级装备了）。

现在，傅里叶想知道他的交通系统究竟有多么伟大。因此，他向你提出了 $q$ 组询问，每次询问如果有一个人要从 $(x_1,y_1)$ 走到 $(x_2,y_2)$，最少需要多少时间。因为傅里叶是唯一真神，所以他当然不会设计一个有缺陷的交通系统，因此所有的 $v_i$ 的绝对值均严格小于 $V$，进而总是可以从一个位置走到另一处。（虽然这将会导致就算在最优情况下，通过传送带系统到达目的地的时间也无法小于原本的一半，更多的时候反倒更慢了，但是谁让他是交通部长，而你只是他手下的一个雇员呢？）
## 输入格式

第一行三个整数 $n,q,V$，表示传送带数目、询问个数以及人的移动速度。

下一行 $n+1$ 个整数 $p_0,p_1,\dots,p_n$，表示传送带的边界信息。

下一行 $n$ 个整数 $v_1,v_2,\dots,v_n$，表示每个传送带的速率。

接下来 $q$ 行，每行四个整数 $x_1,y_1,x_2,y_2$，表示此次询问的起讫点。
## 输出格式

对于每次询问，输出一行一个实数，表示此次移动所需的最小时长，单位为秒。你需要保证输出与标准答案的相对或绝对误差不超过 $10^{-5}$。

- 如果你怀疑你的代码中出现了较大的精度误差，可以尝试使用更多整数和分数以规避浮点数运算，从而减少误差。
## 样例

### 样例输入 #1
```
1 2 10
-5 5
5
-10 -20 10 20
10 20 -10 -20
```
### 样例输出 #1
```
4.3333333333
6.5
```
### 样例输入 #2
```
1 4 10
-5 5
5
10 -10 10 10
10 10 10 -10
10 -50 10 50
10 50 10 -50
```
### 样例输出 #2
```
2
2
7.6666666667
10
```
### 样例输入 #3
```
5 5 10
-10 -5 0 5 10 15
9 -4 7 -6 2
-1 0 -9 -100
-7 0 7 10
9 0 -3 20
12 0 -17 -30
2 0 19 39
```
### 样例输出 #3
```
8.085714
1.815789
2.382353
4.987500
3.988235
```
## 提示

样例 #4，#5 详见附件。

------------

样例 #1 的解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/u2vazpfo.png)

第一问中，上图是一种极优的行走方式。蓝色区域是传送带所在区域，在其上时我们以 $(3,12)$ 每秒的速度移动（其中自身移动的速度是 $(3,7)$，也即可以看作是三成时间沿着 $x$ 轴正方向、七成时间沿着 $y$ 轴正方向移动；在极短时间内不停切换，可以达成如上图中斜线行走的效果；$(3,7)$ 的自身行走与 $(0,5)$ 的传送带运转叠加成为 $(3,12)$ 的速度向量）。

![](https://cdn.luogu.com.cn/upload/image_hosting/wqjsdrte.png)

第二问中，上图是一种极优的行走方案。

需要注意的是，这两问中能达成最少时间的行走方案不止图中给出的两种。

对于所有数据，均满足 $n,q\leq1.5\times10^5$，$-5\times10^5\leq p_0<p_1<p_2<\dots<p_n\leq5\times10^5$，$ |x_1|,|y_1|,|x_2|,|y_2|\leq5\times10^5$，$0\leq|v_i|<V\leq5\times10^5$。

------------

- Subtask 1（5 分）：保证 $n=0$。
- Subtask 2（10 分）：保证 $n,q\leq1000$。
- Subtask 3（10 分）：保证对于所有询问，$x_1=p_0,x_2=p_n$。
- Subtask 4（10 分）：保证所有询问的 $x_1$ 全都相等，所有询问的 $x_2$ 全都相等（但不保证 $x_1=x_2$）。
- Subtask 5（15 分）：保证 $v_i$ 单调不降，且询问的 $x_1\leq x_2$。
- Subtask 6（15 分）：保证存在 $i$ 使得 $p_i=x_1=x_2$。（但并不保证所有询问的 $i$ 都相同）
- Subtask 7（15 分）：保证除 $n,q,V$ 外，其它值都在合法范围内独立随机得到（$p$ 的随机方式是随机 $n+1$ 个不等的 $[-5\times10^5,5\times10^5]$ 中的值并排序）。
- Subtask 8（15 分）：保证 $n,q\leq5\times10^4$。
- Subtask 9（10 分）：无特殊限制。 


---

---
title: "【MX-X1-T6】「KDOI-05」简单的图上问题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10718
tag: ['图论', '计算几何', '平衡树', 'O2优化', '平面图', '平面图欧拉公式', '梦熊比赛']
---
# 【MX-X1-T6】「KDOI-05」简单的图上问题
## 题目背景

原题链接：<https://oier.team/problems/X1F>。
## 题目描述

给你一个 $n$ 个点 $m$ 条边的边双连通图，并且给定了每个点的坐标，保证每条边不相交或者只在端点处重合。

给定 $k$ 个图上的简单环 $C_1,C_2,\dots,C_k$，定义 $G_i$ 为只考虑 $C_i$ 内部的点和边所组成的图。

对 $S\subseteq\{1,2,\dots,k\},S=\{s_1,s_2,\dots,s_t\}$，定义 $f(S)$ 表示所有 $G_{s_i}$ 交的连通块数量。

有 $q$ 个询问，每次给出一个 $z$，输出 $\sum_{S\subseteq\{1,2,\dots,k\},|S|=z}f(S)$。对 $998244353$ 取模。
## 输入格式

第一行三个正整数表示 $n,m,k$。

接下来 $n$ 行，每行两个整数 $(x_i,y_i)$ 表示第 $i$ 个点的坐标。保证所有 $1\leq i<j\leq n$，都有 $x_i\neq x_j,y_i\neq y_j$。

接下来 $m$ 行，每行两个正整数 $u_i,v_i$，表示一条连接 $(u_i,v_i)$ 的无向边。

接下来 $k$ 行，每行第一个正整数 $l_i$ 表示环的大小，接下来 $l_i$ 个正整数 $C_{i,1},C_{i,2},\dots,C_{i,l_i}$ 表示一个原图的简单环，保证 $C_{i,j}$ 按顺序连接可以得到原图上的一个环。

接着一行一个正整数表示 $q$。

最后 $q$ 行，每行一个正整数表示询问的 $z_i$。
## 输出格式

输出 $q$ 行，每行一个整数表示 $\sum_{S\subseteq\{1,2,\dots,k\},|S|=z}f(S)$ 对 $998244353$ 取模后的值。
## 样例

### 样例输入 #1
```
4 5 3
1 1
3 2
2 3
4 4
1 2
1 3
1 4
2 4
3 4
3 1 2 4
3 1 3 4
4 1 2 4 3
3
1
2
3

```
### 样例输出 #1
```
3
3
1
```
### 样例输入 #2
```
8 15 5
4 4
5 8
2 7
10 9
1 10
3 5
8 2
7 6
2 1
3 1
3 2
4 1
4 2
5 2
5 3
5 4
6 1
6 3
7 1
7 4
8 1
8 4
8 7
3 1 8 4 
3 1 6 3 
3 7 8 4 
4 8 1 7 4 
3 1 2 3 
5
1
2
3
4
5
```
### 样例输出 #2
```
5
8
5
1
0
```
## 提示

**【样例解释 \#1】**

样例 $1$ 的数据如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7v424onc.png)

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | 分值 | $n\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|
| $1$ | $15$ | $10$ | 无 |
| $2$ | $30$ | $1000$ | 无 |
| $3$ | $30$ | $4\times10^4$ | 保证平面图是一个凸包的三角剖分 |
| $4$ | $15$ | $4\times10^4$ | 无 |
| $5$ | $10$ | $10^5$ | 无 |

对于 $100\%$ 的数据：$1\leq n,\sum l_i\leq10^5$，$1\leq m\leq 3n-6$，$3\leq l_i$，$0\leq |x_i|,|y_i|\leq 10^9$，$1\leq q\leq 20$，$1\leq u_i,v_i\leq n$，$u_i\neq v_i$，$1\leq z_i\leq k$。保证所有 $1\leq i<j\leq n$，都有 $x_i\neq x_j,y_i\neq y_j$。保证每条边不相交或者只在端点处重合，保证图是一个边双连通分量。


---

---
title: "[NHSPC 2023] D. 共同子凸包"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11905
tag: ['计算几何', '2023', 'O2优化', '台湾']
---
# [NHSPC 2023] D. 共同子凸包
## 题目描述

在數學上，一個點集合 $S$ 的**凸包** (convex hull) 定義為包含 $S$ 的最小凸集合，記作 $\operatorname{Conv}(S)$。在平面上，若 $S$ 為非空有限點集合，則 $\operatorname{Conv}(S)$ 為一包含內部與邊界的最小凸多邊形，或其退化形式。另一方面，設 $E_1$ 與 $E_2$ 為平面上的兩個點集合。若存在某個二維向量 $\mathbf{v}$，滿足
$$P \in E_1 \iff P+\mathbf{v} \in E_2,$$
則稱 $E_1$ 與 $E_2$ 經過平移後重合。

現給定平面上的有限點集合 $S_1$ 與 $S_2$，並考慮它們的非空子集合 $T_1\subseteq S_1$ 與 $T_2\subseteq S_2$。已知子凸包 $\operatorname{Conv}(T_1)$ 與子凸包 $\operatorname{Conv}(T_2)$ 面積皆大於 $0$ 且經過平移後重合，請求出 $\operatorname{Conv}(T_1)$ 所有可能的面積。

以下展示兩個子凸包平移後重合的例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/0272ygh4.png)
## 输入格式

> $n$ $m$   
> $x_1$ $y_1$   
> $x_2$ $y_2$   
> $\vdots$   
> $x_n$ $y_n$   
> $\xi_1$ $\eta_1$   
> $\xi_2$ $\eta_2$   
> $\vdots$   
> $\xi_m$ $\eta_m$

* $n$ 代表 $S_1$ 的集合大小。
* $m$ 代表 $S_2$ 的集合大小。
* $x_i, y_i$ 代表 $S_1$ 包含點 $(x_i, y_i)$。
* $\xi_i, \eta_i$ 代表 $S_2$ 包含點 $(\xi_i, \eta_i)$。
## 输出格式

> $k$   
> $a_1$   
> $a_2$   
> $\vdots$   
> $a_k$

* $k$ 代表若子凸包 $\operatorname{Conv}(T_1)$ 與子凸包 $\operatorname{Conv}(T_2)$ 經過平移後重合，$\operatorname{Conv}(T_1)$ 所有可能的非 $0$ 面積數。
* $a_i$ 為一整數，代表 $\operatorname{Conv}(T_1)$ 所有可能的非 $0$ 面積中，第 $i$ 小的數的**兩倍**。
## 提示

### 測資限制

* $3 \le n \le 40$。
* $3 \le m \le 40$。
* $0 \le x_i \le 20$。
* $0 \le y_i \le 20$。
* $0 \le \xi_i \le 20$。
* $0 \le \eta_i \le 20$。
* 對任意 $i, j \in \{1, 2, \ldots, n\}$，若 $i \ne j$，則 $(x_i, y_i) \ne (x_j, y_j)$。
* 對任意 $i, j \in \{1, 2, \ldots, m\}$，若 $i \ne j$，則 $(\xi_i, \eta_i) \ne (\xi_j, \eta_j)$。
* 輸入的數皆為整數。

### 評分說明

本題共有四組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | $7$ | 所有可能的非 $0$ 面積必能從 $T_1$ 與 $T_2$ 中各選 $3$ 個點得到 |
| 2 | $23$ | $n+m \le 30$ |
| 3 | $41$ | $S_1 = S_2$ |
| 4 | $29$ | 無額外限制 |


---

---
title: "[NERC 2020] Fiber Shape"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12905
tag: ['计算几何', '2020', 'Special Judge', '微积分', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] Fiber Shape
## 题目描述

Imagine a board with $n$ pins put into it, the $i$-th pin is located at $(x_i, y_i)$. 
For simplicity, we will restrict the problem to the case where the pins are placed in vertices of a convex polygon.

Then, take a non-stretchable string of length $l$, and put it around all the pins. Place a pencil inside the string and draw a curve around the pins, trying to pull the string in every possible direction. The picture below shows an example of a string tied around the pins and pulled by a pencil (a point $P$).

![](https://cdn.luogu.com.cn/upload/image_hosting/ej1gx8wa.png)

Your task is to find an area inside this curve. Formally, for a given convex polygon $S$ and a length $l$ let's define a $\emph{fiber shape}$ $F(S, l)$ as a set of points $t$ such that the perimeter of the convex hull of $S \cup \{t\}$ does not exceed $l$. Find an area of $F(S, l)$.
## 输入格式

The first line contains two integers $n$ and $l$ ($3 \le n \le 10^4$; $1 \le l \le 8 \cdot 10^5$) --- the number of vertices of the polygon $S$ and the length of the string. Next $n$ lines contain integers $x_i$ and $y_i$ ($-10^5 \le x_i, y_i \le 10^5$) --- coordinates of polygon's vertices in counterclockwise order. All internal angles of the polygon are strictly less than $\pi$. The length $l$ exceeds the perimeter of the polygon by at least $10^{-3}$.
## 输出格式

Output a single floating-point number --- the area of the fiber shape $F(S, l)$. Your answer will be considered correct if its absolute or relative error doesn't exceed $10^{-6}$. 
## 样例

### 样例输入 #1
```
3 4
0 0
1 0
0 1
```
### 样例输出 #1
```
3.012712585980357
```
### 样例输入 #2
```
4 5
0 0
1 0
1 1
0 1
```
### 样例输出 #2
```
5.682061989789656
```
### 样例输入 #3
```
5 17
0 0
2 -1
3 0
4 3
-1 4
```
### 样例输出 #3
```
37.719371276930820
```
## 提示

The following pictures illustrate the example tests.

![](https://cdn.luogu.com.cn/upload/image_hosting/lcmvxklh.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/nyr1k7a8.png)


---

---
title: "[GCJ 2022 Finals] Triangles"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13005
tag: ['贪心', '计算几何', '2022', 'Special Judge', '构造', 'Google Code Jam']
---
# [GCJ 2022 Finals] Triangles
## 题目描述

You are given a set $P$ of $\mathbf{N}$ distinct points in the two-dimensional plane. You want to find a maximum set of triangles such that:

*   Each vertex of a triangle in your set is a point from $P$ and each point in $P$ is a vertex of at most one triangle in your set.
*   Each triangle in your set has positive area (i.e., its 3 vertices are not collinear).
*   For any two sides of triangles in your set, their intersection is either empty or an endpoint of one of them.
*   For any two triangles in your set, the intersection of the areas strictly inside those triangles is either empty or equal to one of them.

For example, the set of triangles depicted below meets the definition above.

![](https://cdn.luogu.com.cn/upload/image_hosting/jxq6yve2.png)

On the other hand, each pair of a yellow and a red triangle in the picture below does not meet the definition.

![](https://cdn.luogu.com.cn/upload/image_hosting/oyhps85j.png)
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing a single integer $\mathbf{N}$. Then, $\mathbf{N}$ lines follow. The $i$-th of these lines contains two integers $\mathbf{X}_i$ and $\mathbf{Y}_i$ representing the coordinates of the $i$-th point.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the maximum size of a set of triangles with the desired properties. Then, output $y$ more lines. The $j$-th of those lines must contain $p_j$ $q_j$ $r_j$ representing that the $j$-th triangle in your proposed set has the $p_j$-th, $q_j$-th, and $r_j$-th points in the input as vertices. Points in the input are numbered starting from 1.
## 样例

### 样例输入 #1
```
3
9
8 2
10 2
2 0
0 5
2 3
10 4
10 0
8 3
2 4
7
0 0
0 3
3 0
0 1
1 0
1 1
2 2
3
0 0
0 1
0 2
```
### 样例输出 #1
```
Case #1: 3
3 4 5
1 7 9
6 2 8
Case #2: 2
2 3 1
6 5 4
Case #3: 0
```
## 提示

Sample Case #1 is illustrated below. Notice that there are other valid ways to construct a maximum number of triangles.

![](https://cdn.luogu.com.cn/upload/image_hosting/x975q63y.png)

Sample Case #2 is illustrated below. As before, there are other valid ways to construct 2 triangles.

![](https://cdn.luogu.com.cn/upload/image_hosting/7ca1oxq2.png)

In Sample Case #3, the 3 given points are collinear, so it is not possible to make a valid triangle with them.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $-10^9 \leq \mathbf{X}_i \leq 10^9$, for all $i$.
- $-10^9 \leq \mathbf{Y}_i \leq 10^9$, for all $i$.
- $(\mathbf{X}_i, \mathbf{Y}_i) \neq (\mathbf{X}_j, \mathbf{Y}_j)$, for all $i \neq j$.

**Test Set 1 (8 Pts, Visible Verdict)**

- $3 \leq \mathbf{N} \leq 12$.

**Test Set 2 (42 Pts, Hidden Verdict)**

- $3 \leq \mathbf{N} \leq 3000$.


---

---
title: "[GCJ 2021 #3] Fence Design"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13041
tag: ['计算几何', '2021', 'Special Judge', '分治', '凸包', 'Google Code Jam']
---
# [GCJ 2021 #3] Fence Design
## 题目描述

You are hired as a temporary employee of the Fence Construction Company and have been tasked with finishing the design of the fencing for a field. Each fence must run in a straight line between two poles. Each pole occupies a single point and the location of each pole is fixed. No three poles are collinear. Fences cannot intersect each other, except possibly at their endpoints (the poles).

The design was started by someone else, but they quit the project after adding exactly two fences. You need to finish their design. To impress your bosses and clients, you want the design to have as many fences as possible, regardless of their lengths.

Given the positions of the poles and the already-built fences, please find a way to add as many fences as possible such that no pair of fences (new or existing) intersect each other, except possibly at their endpoints (the poles).
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a single line containing an integer $\mathbf{N}$, indicating the number of poles. Then, $\mathbf{N}$ lines follow. The $i$-th of these lines contains two integers $\mathbf{X}_i$ and $\mathbf{Y}_i$, representing the X and Y coordinates of the $i$-th pole's position. The last two lines for each test case represent the two existing fences. These two lines contain two integers each: $\mathbf{P}_k$ and $\mathbf{Q}_k$, representing that the $k$-th existing fence runs between the $\mathbf{P}_k$-th and the $\mathbf{Q}_k$-th pole (poles are numbered starting from 1).

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the maximum number of fences that can be added to the design (not including the existing ones). Then, output $y$ more lines. Each line must contain two distinct integers $i$ and $j$ (both between 1 and $\mathbf{N}$, inclusive), representing a different fence that connects the $i$-th and $j$-th poles. No pair of the $y + 2$ fences (the existing fences as well as the ones you have added) may overlap, except possibly at their endpoints.
## 样例

### 样例输入 #1
```
2
4
0 0
0 1
1 1
1 0
1 2
3 4
5
0 0
0 1
1 1
1 0
2 3
1 2
3 5
```
### 样例输出 #1
```
Case #1: 3
1 4
2 3
4 2
Case #2: 6
5 4
2 4
5 2
1 4
4 3
3 2
```
## 提示

**Sample Explanation**

The following pictures show the poles and fences in the given samples. The fences with the wider blue line on them are the existing ones, and the rest show the way of adding a maximum number of fences shown in the sample output.

![](https://cdn.luogu.com.cn/upload/image_hosting/j0yr6b9n.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/is24xybt.png)

**Limits**

- $1 \leq \mathbf{T} \leq 50$.
- $-10^9 \leq \mathbf{X}_i \leq 10^9$, for all $i$.
- $-10^9 \leq \mathbf{Y}_i \leq 10^9$, for all $i$.
- $(\mathbf{X}_i, \mathbf{Y}_i) \neq (\mathbf{X}_j, \mathbf{Y}_j)$, for all $i \neq j$.
- $1 \leq \mathbf{P}_k < \mathbf{Q}_k \leq \mathbf{N}$, for all $k$.
- The existing fences do not intersect, except possibly at their endpoints.
- No three poles are collinear.

**Test Set 1 (11 Pts, Visible Verdict)**

- Time limit: 60 seconds.
- $4 \leq \mathbf{N} \leq 100$.

**Test Set 2 (19 Pts, Hidden Verdict)**

- Time limit: 90 seconds.
- $4 \leq \mathbf{N} \leq 10^5$.


---

---
title: "[GCJ 2020 Finals] Musical Cords"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13073
tag: ['计算几何', '2020', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2020 Finals] Musical Cords
## 题目描述

Lauren is trying to play the most beautiful notes possible using a harp. The harp is a circle with a radius of $\mathbf{R}$ centimeters. To play a note, a cord must be attached to the harp in a way that connects two different attachment points on the perimeter of the circle. Lauren then plucks this cord to play a note.

There are $\mathbf{N}$ attachment points on the perimeter of the circular harp at which a cord can be attached. The $i$-th such attachment point is at a location that is $\mathbf{D}_i$ nanodegrees (a nanodegree is $10^{-9}$ degrees) clockwise around the perimeter of the circular harp, starting from the rightmost point on the perimeter.

Not all attachment points use the same technology to properly fix the cords onto them. The $i$-th attachment point requires $\mathbf{L}_i$ centimeters of cord to be used for attaching. A cord fixed between two different attachment points $i$ and $j$ needs to be exactly $\mathbf{L}_i + \mathbf{L}_j + \text{distance}(i, j)$ centimeters long. By $\text{distance}(i, j)$ we mean the length of the geometric chord connecting the $i$-th and $j$-th attachment points, that is, the Euclidean distance between the two points.

Lauren thinks that notes sound better when they come from longer cords. What are the $\mathbf{K}$ longest cords that can be used with Lauren's harp?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. The first line of a test case contains three integers: $\mathbf{N}$, $\mathbf{R}$ and $\mathbf{K}$: the number of attachment points, the radius of the circular harp in centimeters, and the number of lengths of cords that Lauren is interested in knowing.

The next $\mathbf{N}$ lines describe the attachment points. The $i$-th of these lines contains two integers, $\mathbf{D}_i$ and $\mathbf{L}_i$, which describe the position (in number of nanodegrees clockwise from the rightmost point of the harp) and length of cord in centimeters needed at the $i$-th attachment point.

## 输出格式

For each test case, output one line containing Case #x: $y_1$ $y_2$ ... $y_{\mathbf{K}}$, where $x$ is the test case number (starting from 1), and $y_n$ is the $n$-th value in the list of lengths of all $\mathbf{N} \times (\mathbf{N}-1)/2$ cords that can be used in Lauren's harp, sorted in non-increasing order.

Each $y_n$ will be considered correct if it is within an absolute or relative error of $10^{-9}$ of the correct answer. See the FAQ for an explanation of what that means, and what formats of real numbers we accept.
## 样例

### 样例输入 #1
```
2
5 2 1
0 3
1234567890 3
3154510113 3
180000000000 3
359999999999 3
5 10 1
90000000000 8
180000000000 7
260000000000 9
260000000001 1
260000000002 1
```
### 样例输出 #1
```
Case #1: 10.0000000000
Case #2: 36.9238939618
```
### 样例输入 #2
```
1
6 1 10
0 10
15000000000 1
30000000000 1
45000000000 1
60000000000 1
75000000000 1
```
### 样例输出 #2
```
Case #1: 12.2175228580 12.0000000000 11.7653668647 11.5176380902 11.2610523844 3.0000000000 2.7653668647 2.7653668647 2.5176380902 2.5176380902
```
## 提示

**Sample Explanation**

Sample Test Set 1 meet the limits for Test Set 1. Another sample case that does not meet those limits could appear in Test Set 2.

Note: the $\mathbf{L}_i$ values in these sample cases for Test Set 1 were chosen for ease of understanding and were not randomly generated. Your solution will be run against these sample cases and must pass them.

In Sample Case #1, all of the attachment points have the same value, so we should pick the pair connected by the longest chord, which in this case is a horizontal diameter of the circle that has a length of 4 centimeters. So the total length needed is $4 + 3 + 3 = 10$ centimeters.

In Sample Case #2, the fourth and fifth points are extremely close to the third point, but have much smaller $\mathbf{L}$ values. We can effectively rule them out and focus on the possible connections among the first three points, as follows:

- first and second points: length $10\sqrt{2} + 8 + 7 \approx 29.142136$.
- first and third points: length $\approx 19.923894 + 8 + 9 \approx 36.923894$.
- second and third points: length $\approx 12.855726 + 7 + 9 \approx 28.855726$.

Using the first and third points gives us the greatest total length.

Sample Test Set 2: Notice that there are three possible pairs of points tied for producing the 9th longest cord. Also, it is fine if lines connecting different pairs of points intersect, since Lauren will only be playing one note at a time.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $\mathbf{N} = 150000$ in at most 10 cases.
- $5 \leq \mathbf{N} \leq 10^4$ in all cases with $\mathbf{N} \neq 150000$.
- $1 \leq \mathbf{R} \leq 10^9$.
- $0 \leq \mathbf{D}_1$.
- $\mathbf{D}_i < \mathbf{D}_{i+1}$, for all $i$.
- $\mathbf{D}_N < 360 \times 10^9$.

**Test Set 1 (15 Pts, Visible Verdict)**

- $\mathbf{L}_i$ is chosen independently and uniformly at random between 1 and $10^9$, inclusive, for each $i$.
- $\mathbf{K} = 1$.

**Test Set 2 (27 Pts, Hidden Verdict)**

- $1 \leq \mathbf{L}_i \leq 10^9$, for all $i$.
- (There is no guarantee as to how each $\mathbf{L}_i$ is generated.)
- $\mathbf{K} = 10$.


---

---
title: "[GCJ 2019 #3] Napkin Folding"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13122
tag: ['计算几何', '2019', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2019 #3] Napkin Folding
## 题目描述

Chalk has been actively traveling the world with his friends taking pictures in all the coolest places. Most recently, he made his way to Europe, where he studied the history of [napkin folding](https://en.wikipedia.org/wiki/Napkin_folding). Ever since, Chalk has been collecting a wide variety of napkins to practice the art of napkin folding.

Chalk's napkins can be defined as [simple polygons](https://en.wikipedia.org/wiki/Simple_polygon). A simple polygon is a polygon in which no edges intersect except for adjacent edges which meet at their shared vertex. Each vertex of the polygon is on exactly two edges.

Chalk folds his napkins by first drawing a *folding pattern* on them. A folding pattern is a set of $\mathbf{K}-1$ line segments which are drawn on the napkin. Each line segment connects two points with rational coordinates on the border of the polygon defining the napkin and is fully contained in the polygon. No two line segments in a folding pattern may touch or overlap, except possibly at common endpoints. A folding pattern of $\mathbf{K}-1$ line segments splits the napkin into $\mathbf{K}$ polygonal regions. Two points are in the same region if there exists some continuous line (not necessarily straight) between them which does not intersect any edge of the polygon or any line segment in the folding pattern — even at endpoints.

Chalk is only interested in *neat folding patterns*. A folding pattern is *neat* if any two regions that are adjacent to the same folding line segment $F$ are [symmetric](https://en.wikipedia.org/wiki/Symmetry) with respect to $F$. This means that folding the napkin along that line segment would result in the two regions lining up perfectly.

The following picture illustrates a neat folding pattern with $\mathbf{K}=8$ regions.

![](https://cdn.luogu.com.cn/upload/image_hosting/ta6vzkcp.png)

Chalk has been successfully folding his collection of napkins using neat folding patterns. But he has some napkins in his collection that he has not been able to find a neat folding pattern for. For each of those napkins, Chalk needs your help to find a neat folding pattern with $\mathbf{K}$ regions or determine that no such neat folding pattern exists.

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing two integers $\mathbf{N}$ and $\mathbf{K}$: the number of points in the polygon defining Chalk's napkin and the number of regions to split the napkin into with a neat folding pattern containing $\mathbf{K}-1$ line segments.

The polygon defining the napkin is represented as a list of the $\mathbf{N}$ vertices, as encountered when traveling along the perimeter of the polygon in the clockwise direction, with the first vertex being chosen arbitrarily. The next $\mathbf{N}$ lines represent that list. The $\mathbf{i}$-th of these contains two integers $\mathbf{X}_{\mathbf{i}}$ and $\mathbf{Y}_{\mathbf{i}}$, indicating that the $\mathbf{i}$-th point is located at $(\mathbf{X}_{\mathbf{i}}, \mathbf{Y}_{\mathbf{i}})$ in two-dimensional space.

## 输出格式

For each test case, output one line containing Case #$x$: $y$, where $x$ is the test case number (starting from 1) and $y$ is `POSSIBLE` if it is possible to make a neat folding pattern with $\mathbf{K}$ regions and `IMPOSSIBLE` otherwise.

If it is possible to make a neat folding pattern with $\mathbf{K}$ regions, output $\mathbf{K}-1$ more lines listing the segments of a neat folding pattern with $\mathbf{K}$ regions, in any order. Each line should represent a different segment as $\mathbf{A}_{\mathbf{x}}$ $\mathbf{A}_{\mathbf{y}}$ $\mathbf{B}_{\mathbf{x}}$ $\mathbf{B}_{\mathbf{y}}$, where $(\mathbf{A}_{\mathbf{x}}, \mathbf{A}_{\mathbf{y}})$ and $(\mathbf{B}_{\mathbf{x}}, \mathbf{B}_{\mathbf{y}})$ are the two endpoints of the segment, in any order. Each of $\mathbf{A}_{\mathbf{x}}$, $\mathbf{A}_{\mathbf{y}}$, $\mathbf{B}_{\mathbf{x}}$, and $\mathbf{B}_{\mathbf{y}}$ should be in the form $\mathbf{N}/\mathbf{D}$ where $\mathbf{N}$ and $\mathbf{D}$ are positive integers (written with no leading zeroes) sharing no common prime factors, and representing the rational number $\mathbf{N}/\mathbf{D}$. There must be no whitespace between $\mathbf{N}$ and /, or between / and $\mathbf{D}$.
## 样例

### 样例输入 #1
```
4
4 2
1 1
1 2
2 2
2 1
3 2
1 1
1 2
2 1
8 2
1 3
3 5
5 5
4 4
7 3
5 1
4 2
3 1
8 2
1 3
3 5
4 4
5 5
7 3
5 1
4 2
3 1
```
### 样例输出 #1
```
Case #1: POSSIBLE
1/1 2/1 2/1 1/1
Case #2: POSSIBLE
1/1 1/1 3/2 3/2
Case #3: IMPOSSIBLE
Case #4: POSSIBLE
1/1 3/1 7/1 3/1
```
### 样例输入 #2
```
1
10 8
4 1
3 1
2 2
2 3
1 3
1 4
2 4
3 3
3 2
4 2
```
### 样例输出 #2
```
Case #1: POSSIBLE
3/1 1/1 4/1 2/1
3/1 1/1 3/1 2/1
2/1 2/1 3/1 2/1
2/1 2/1 3/1 3/1
2/1 3/1 3/1 3/1
2/1 3/1 2/1 4/1
1/1 3/1 2/1 4/1
```
## 提示

**Sample Explanation**

Note: Sample 2 is not valid for Test set 1. Only Sample 1 will be tested prior to running Test set 1 (the same way samples normally are). Moreover, Sample 2 will not be tested prior to running Test set 2.

For Sample Case #1, a neat folding pattern with $\mathbf{K}=2$ can be drawn using any of the 4 dashed lines:

![](https://cdn.luogu.com.cn/upload/image_hosting/bm3282e7.png)

For Sample Case #2, a neat folding pattern with $\mathbf{K}=2$ can be drawn as follows:

![](https://cdn.luogu.com.cn/upload/image_hosting/hvx1riz3.png)

For Sample Case #3, there are no neat folding patterns:

![](https://cdn.luogu.com.cn/upload/image_hosting/adkogxsq.png)

For Sample Case #4, there are two possible neat folding patterns with $\mathbf{K}=2$:

![](https://cdn.luogu.com.cn/upload/image_hosting/j4v71qhu.png)

For the test set 2 sample case, a neat folding pattern with $\mathbf{K}=8$ can be drawn as follows:

![](https://cdn.luogu.com.cn/upload/image_hosting/vqrcukau.png)

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $3 \leq \mathbf{N} \leq 200$.
- $1 \leq \mathbf{X}_{\mathbf{i}} \leq 1000$, for all $\mathbf{i}$.
- $1 \leq \mathbf{Y}_{\mathbf{i}} \leq 1000$, for all $\mathbf{i}$.
- The $\mathbf{N}$ points are given in clockwise order.
- No two adjacent edges of the polygon are collinear.
- The polygon is a simple polygon with strictly positive area.
- No two edges intersect except for adjacent edges at their shared endpoint.

**Test set 1 (4 Pts, Visible)**

- $\mathbf{K}=2$.

**Test set 2 (39 Pts, Hidden)**

- $2 \leq \mathbf{K} \leq 10$.


---

---
title: "[GCJ 2019 Finals] Juggle Struggle: Part 2"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13127
tag: ['计算几何', '2019', '凸包', 'Google Code Jam']
---
# [GCJ 2019 Finals] Juggle Struggle: Part 2
## 题目描述

The first two paragraphs (not counting this one) of this problem and "Juggle Struggle: Part 1" are identical. The problems can otherwise be solved independently; you do not need to read or solve one in order to read or solve the other.

As manager of the Graceful Chainsaw Jugglers group, you have decided to spice the show up a bit. Instead of having each juggler individually juggle their own chainsaws, you want them to form pairs, with each pair throwing the chainsaws back and forth to each other. In this new performance, $2 \times \mathbf{N}$ jugglers will be on stage at the same time, arranged into $\mathbf{N}$ pairs, with each juggler belonging to exactly one pair.

You think the show will be more impressive if the chainsaws being juggled by different pairs of jugglers are at risk of collision. Let the stage be a two-dimensional plane, and let the straight line segment in that plane that connects the positions of two jugglers in a pair be called the pair's juggling path. When two juggling paths intersect, we say the chainsaws juggled by those pairs are at risk of collision. We call the spatial positions and the pairings of the jugglers an arrangement. An arrangement is magnificent if every two pairs of jugglers' chainsaws are at risk of collision. That is, for the arrangement to be magnificent, each of the $\mathbf{N}$ juggling path segments must intersect each of the other $\mathbf{N}-1$ juggling path segments (but these intersections do not necessarily all have to be in the same place).

After some last minute fixes, you have what you think is a magnificent arrangement. Given the rush to put it together, you want to write a checker that can determine whether it is indeed magnificent. If it is not, then at most 25 juggler pairs fail to intersect every other pair. You want your checker to report a list of all those juggler pairs for inspection.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with one line containing a single integer $\mathbf{N}$, the number of pairs of jugglers. Then, $\mathbf{N}$ lines follow. The i-th of these lines contains four integers $\mathbf{X}_\mathbf{i}$, $\mathbf{Y}_\mathbf{i}$, $\mathbf{X'}_\mathbf{i}$, $\mathbf{Y'}_\mathbf{i}$. ($\mathbf{X}_\mathbf{i}$, $\mathbf{Y}_\mathbf{i}$) and ($\mathbf{X'}_\mathbf{i}$, $\mathbf{Y'}_\mathbf{i}$) are the coordinates of the positions of the two jugglers comprising the i-th juggler pair.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $y$ is uppercase MAGNIFICENT if the input represents a magnificent arrangement. Otherwise, $y$ should be a strictly increasing list of integers. Integer $i$ should be on that list if and only if the juggling path of the $i$-th juggler pair fails to intersect at least one other juggling path.
## 样例

### 样例输入 #1
```
4
2
-1 -1 -1 1
1 1 1 -1
2
-1 -1 1 1
-1 1 1 -1
4
1 2 4 2
2 1 3 1
2 4 3 0
3 3 2 3
3
1 1 2 2
3 7 4 8
8 3 9 3
```
### 样例输出 #1
```
Case #1: 1 2
Case #2: MAGNIFICENT
Case #3: 1 2 4
Case #4: 1 2 3
```
## 提示

**Sample Explanation**

- In Sample Case #1, there are only two pairs, and their paths do not cross.
- In Sample Case #2, the arrangement is magnificent: every pair's path crosses every other pair's path.
- In Sample Case #3, only pair 3's path crosses every other pair's path.

**Limits**

- $-10^9 \leq \mathbf{X}_\mathbf{i} \leq 10^9$, for all $i$.
- $-10^9 \leq \mathbf{Y}_\mathbf{i} \leq 10^9$, for all $i$.
- $-10^9 \leq \mathbf{X'}_\mathbf{i} \leq 10^9$, for all $i$.
- $-10^9 \leq \mathbf{Y'}_\mathbf{i} \leq 10^9$, for all $i$.
- No three juggler positions are collinear. (Note that this also implies that no two jugglers are in the same position.)
- For all but up to 25 pairs of jugglers, their juggling paths intersect all $\mathbf{N} - 1$ other juggling paths.
- Note: There may or may not exist a way to pair the jugglers such that the resulting arrangement is magnificent.

**Test set 1 (5 Pts, Visible)**

- Time limit: 20 seconds.
- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{N} \leq 100$.

**Test set 2 (30 Pts, Hidden)**

- Time limit: 45 seconds.
- $1 \leq \mathbf{T} \leq 13$.
- $2 \leq \mathbf{N} \leq 10^5$.


---

---
title: "[GCJ 2013 Finals] X Marks the Spot"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13304
tag: ['计算几何', '2013', '二分', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2013 Finals] X Marks the Spot
## 题目描述

Fair King Tyrone and his four sons conquered the nation of Carrania. His four sons immediately started to squabble about dividing the land between the four of them. The main point of contention was the gold mines of Carrania - each son wanted to have no fewer gold mines than any other.

Fair King Tyrone soon got tired of the squabbling, especially when he learned the number of mines is $4N$, so dividing them should be easy. He gathered his sons, took a map, drew an X on it and declared each son would get one quarter of the nation, with borders defined by the X he drew.

Unfortunately, Fair King Tyrone is a bit shortsighted, and the map he drew on was not a map of Carrania. His first minister quickly hid the map, and now tries to draw an identical X on the map of Carrania so that each son gets the same number of gold mines. Unfortunately all sons saw King Tyrone draw the X, and know the borders should be two perpendicular straight lines - so the minister has to make them so.

Help him! Your task is to draw two perpendicular straight lines such that no gold mine lies on a border, and the borders divide the gold mines equally.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a number $N$, describing the number of gold mines each son should get. $4N$ lines follow, each containing two integers, being the coordinates $x_i$, $y_i$ of one of the gold mines. No three gold mines are co-linear.

## 输出格式

For each test case, output one line containing "Case #x: $x_a$ $y_a$ $x_b$ $y_b$", where $x$ is the case number (starting from 1), ($x_a$, $y_a$) are the coordinates of the point where the two borders intersect, and ($x_b$, $y_b$) are the coordinates of some other point on the X.

All coordinates must be between $-10^9$ and $10^9$, have at most 9 digits after the decimal point, and not use exponential notation. They must be exact: the resulting X will be drawn exactly at these coordinates. You should output IMPOSSIBLE instead if there is no good placement of borders.
## 样例

### 样例输入 #1
```
2
1
0 0
1 0
0 1
1 1
1
1 0
0 1
-1 0
0 -1
```
### 样例输出 #1
```
Case #1: 0.5 0.5 2 0.5
Case #2: 0 0 -3 -3
```
## 提示

**Limits**

- $1 \leq T \leq 20$
- $-10^6 \leq x_i, y_i \leq 10^6$

**Small dataset (10 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq N \leq 10$

**Large dataset (29 Pts, Test set 2 - Hidden)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq N \leq 2500$


---

---
title: "三角形面积并 加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13338
tag: ['计算几何', '平衡树', 'Special Judge', '微积分']
---
# 三角形面积并 加强版
## 题目背景

[原题链接](https://www.luogu.com.cn/problem/P4406)
## 题目描述

给定 $n$ 个非退化三角形 $\triangle A_i B_i C_i\ (1 \leq i \leq n)$，你的任务是计算这些三角形的并集面积。

一个三角形是**非退化**的，当且仅当它具有非零面积，即三角形的三个顶点 $A_i,B_i,C_i$ 是不同的且不共线。换句话说，点 $A_i,B_i,C_i$ 不在同一条直线上，由这三点构成的三角形不是退化的。

三角形的**并集面积**是至少被其中一个三角形覆盖的总面积。形式化地，三角形的并集面积是由这些三角形所占区域的并集所形成的区域的面积：
$$
\text{Area}\left(\bigcup_{i=1}^n S_i\right)
$$
其中 $S_i$ 表示三角形 $\triangle A_i B_i C_i$ 所占的几何区域，$\text{Area}(S_i)$ 是该区域的面积。$\bigcup_{i=1}^n S_i$ 表示至少被其中一个三角形覆盖的区域。

## 输入格式

每个测试文件中仅包含一个测试用例。

第一行包含一个整数 $n\ (1 \leq n \leq 10^3)$，表示三角形的数量。

接下来的 $n$ 行，每行包含六个整数 $x_1\ y_1\ x_2\ y_2\ x_3\ y_3\ (0 \leq |x|, |y| \leq 10^6)$，表示三角形 $\triangle A_i B_i C_i$ 的三个顶点的坐标。

## 输出格式

输出一个实数，表示这些三角形的并集面积。你的答案的绝对误差或相对误差应小于 $10^{-6}$。当你的答案为 $a$，评测机的答案为 $b$，则当 $\frac{|a-b|}{\max(1,|b|)} \leq 10^{-6}$ 时答案被接受。
## 样例

### 样例输入 #1
```
2
1 1 2 7 8 8
1 1 2 7 8 8
```
### 样例输出 #1
```
17.50000000000000000000
```
### 样例输入 #2
```
4
2 1 7 4 4 10
4 6 3 3 5 3
9 6 7 12 11 8
9 2 1 6 11 10
```
### 样例输出 #2
```
48.75833209115131640239
```
## 提示

样例 2 图示：

![样例 2](https://cdn.luogu.com.cn/upload/image_hosting/vwry2al7.png)

对于子任务 1，输入数据满足 $1 \leq n \leq 100$，且 $0 \leq |x|, |y| \leq 10^3$。该子任务可用于测试算法的正确性。完成子任务 1 将获得总分的 $50\%$。

对于子任务 2，输入数据满足 $1 \leq n \leq 10^3$，且 $0 \leq |x|, |y| \leq 10^6$。完成子任务 2 将获得剩余 $50\%$ 的分数。

提示：求解三角形的并集面积是一个经典的 3SUM-hard 问题。你需要实现一个时间复杂度为 $\mathcal{O}(V^2 \log V)$ 的算法，其中 $V$ 为顶点总数。


---

---
title: "[GCJ 2010 Finals] Ninjutsu"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13411
tag: ['动态规划 DP', '计算几何', '2010', 'Google Code Jam']
---
# [GCJ 2010 Finals] Ninjutsu
## 题目描述

Ninjutsu is the martial art of the mysterious Japanese assassins, ninja. As a beginner in the practice of ninjutsu, your first task is to master the use of the grappling hook.

A grappling hook is a technologically-advanced device consisting of a hook tied to some (very strong and very thin) rope. Proper use of a grappling hook involves throwing the hook at a target and hoping that it catches.

This time, it did! You are now hooked onto a target that is located at $(0, 0)$. Your rope extends to the left, and you're at the end of it; when you jump, you will start swinging counter-clockwise around the target. There are other targets located to the right and above $(0, 0)$, at $(x_i, y_i)$ with $x_i \geq 0$ and $y_i \geq 0$. When an interior point of the rope (not either end) contacts one or more targets, the rope will bend around the target closest to its moving end. Ignore your starting velocity; because you are a ninja, it is fast enough that you will continue bending around targets until you are spinning around a single one.

Your rope currently has length $R$, but you may choose to cut it down to any shorter length $r$ (including non-integers) before you start swinging. As such, you will start at $(-r, 0)$ and swing down (counter-clockwise) toward $(0, -r)$.

What is the maximum number of bends you can put into the rope with one swing? A bend happens when your rope touches a target and then rotates some non-zero number of degrees around that target. The rope will always remain perfectly straight (again, this is possible because you are a ninja), except at bends.

### Example

![](https://cdn.luogu.com.cn/upload/image_hosting/vz7mq0hg.png)

In the example above, there are 6 points:

* $(0, 0)$,
* $(3, 1)$,
* $(12, 4)$,
* $(14, 5)$,
* $(13, 7)$, and
* $(7, 10)$.

You have a rope of length $24$. If you do not cut the rope, then you will bend around point $(12, 4)$, then around point $(14, 5)$, then around point $(13, 7)$, and finally, you will be stuck orbiting point $(7, 10)$ with about $0.1705$ units of rope remaining. This amounts to a total of $4$ bends. Although you touch point $(3, 1)$, it does not contribute a bend because it is collinear with the points $(0, 0)$ and $(12, 4)$.

If, however, you cut the rope by $0.18$ units, you will not have enough length to reach point $(7, 10)$ and will instead follow the path

$(0, 0)$--$(12, 4)$--$(14, 5)$--$(13, 7)$--$(12, 4)$--$(14, 5)$

and will end up orbiting point $(14, 5)$ with about $1.3004$ units of rope remaining. This path amounts to $5$ bends, in total, and is an optimal solution.

![](https://cdn.luogu.com.cn/upload/image_hosting/yp5e2kds.png)

Case #1 in the sample input below represents this example.
## 输入格式

The input will start with a line containing $T$, the number of test cases to follow. Each test case will start with two integers together on a line: $N$ and $R$. The next $N$ lines will each contain a pair of integers -- $x_i$ and $y_i$ -- the coordinates of the targets, starting with the target at $(0, 0)$.

## 输出格式

For each test case, output a line of the form "Case #$C$: $k$", where $C$ is the 1-based case number, and $k$ is the maximum number of bends that can be made in the rope in one swing.
## 样例

### 样例输入 #1
```
6
6 24
0 0
3 1
12 4
14 5
13 7
7 10
2 1
0 0
2 0
2 1
0 0
1 0
2 10
0 0
4 0
3 50
0 0
9 0
10 0
3 12
0 0
3 0
3 4
```
### 样例输出 #1
```
Case #1: 5
Case #2: 0
Case #3: 0
Case #4: 2
Case #5: 12
Case #6: 3
```
## 提示

**Limits**

- $1 \leq T \leq 100$
- All target coordinates are integers.
- All targets will be at different locations.
- The first target listed will be located at $(0, 0)$.
- There will be at least one value of $r$ that gives an optimal solution and has the property that a rope of length $r - 0.999999$ also gives the same solution (the same sequence of bends).

**Small dataset (11 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 10$
- $1 \leq R \leq 1,000$
- $0 \leq x_i \leq 1,000$
- $0 \leq y_i \leq 1,000$

**Large dataset (23 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 1,000$
- $1 \leq R \leq 10^9$
- $0 \leq x_i \leq 10^9$
- $0 \leq y_i \leq 10^9$


---

---
title: "[GCJ 2009 Finals] Lights"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13453
tag: ['计算几何', '2009', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2009 Finals] Lights
## 题目描述

In a big, square room there are two point light sources: one is red and the other is green. There are also $n$ circular pillars.

Light travels in straight lines and is absorbed by walls and pillars. The pillars therefore cast shadows: they do not let light through. There are places in the room where no light reaches (black), where only one of the two light sources reaches (red or green), and places where both lights reach (yellow). Compute the total area of each of the four colors in the room. Do not include the area of the pillars.
## 输入格式

* One line containing the number of test cases, $T$.

Each test case contains, in order:

* One line containing the coordinates $x$, $y$ of the red light source.
* One line containing the coordinates $x$, $y$ of the green light source.
* One line containing the number of pillars $n$.
* $n$ lines describing the pillars. Each contains 3 numbers $x$, $y$, $r$. The pillar is a disk with the center $(x, y)$ and radius $r$.

The room is the square described by $0 \leq x, y \leq 100$. Pillars, room walls and light sources are all disjoint, they do not overlap or touch.
## 输出格式

For each test case, output:

```
Case #X:
black area
red area
green area
yellow area
```

where $X$ is the test case number, starting from 1, and each area is a real number.

Any answer with absolute or relative error of at most $10^{-5}$ will be accepted.
## 样例

### 样例输入 #1
```
1
5 50
95 50
1
50 50 10
```
### 样例输出 #1
```
Case #1:
0.7656121
1437.986
1437.986
6809.104
```
## 提示

**Limits**

- All input numbers are integers.
- $1 \leq T \leq 15$
- $0 \leq x, y \leq 100$
- $1 \leq r \leq 49$

**Small dataset(21 Pts)**

- Time limit: ~~20~~ 5 seconds.
- $0 \leq n \leq 1$

**Large dataset(45 Pts)**

- Time limit: ~~90~~ 30 seconds.
- $0 \leq n \leq 50$


---

---
title: "[NWRRC 2023] H-Shaped Figures"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13588
tag: ['计算几何', '树状数组', '2023', 'ICPC', '极角排序', 'NWRRC']
---
# [NWRRC 2023] H-Shaped Figures
## 题目描述

After a huge success of the last year's "K-Shaped Figures" problem, we've come up with an innovative "H-Shaped Figures" problem for this year. And we have some plans for the next 24 years.

Let's say that three segments $PQ$, $a$, and $b$ on a plane form an H-shaped figure if:

- point $P$ lies strictly inside segment $a$, and segments $PQ$ and $a$ are not collinear;
- point $Q$ lies strictly inside segment $b$, and segments $PQ$ and $b$ are not collinear;
- segments $a$ and $b$ do not have common points.

![](https://cdn.luogu.com.cn/upload/image_hosting/5qwh7w8x.png)

You are given the coordinates of points $P$ and $Q$, along with $n$ candidate segments for $a$ and $b$. Note that some of the given segments may coincide, but they should still be treated as different segments.

Find the number of possible ways to choose one of the given $n$ segments as $a$ and another one as $b$ to form an H-shaped figure along with the given segment $PQ$.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first line of each test case contains four integers $x_P, y_P, x_Q, y_Q$, denoting the coordinates of points $P$ and $Q$ ($-10^9 \le x_P, y_P, x_Q, y_Q \le 10^9$). Points $P$ and $Q$ do not coincide.

The second line contains a single integer $n$, denoting the number of candidate segments ($2 \le n \le 2 \cdot 10^5$).

The $i$-th of the following $n$ lines contains four integers $x_{i,1}, y_{i,1}, x_{i,2}, y_{i,2}$, denoting the coordinates of the endpoints of the $i$-th segment ($-10^9 \le x_{i,1}, y_{i,1}, x_{i,2}, y_{i,2} \le 10^9$). All segments have positive lengths.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.
## 输出格式

For each test case, print the number of ways to form an H-shaped figure using the given segment $PQ$ and two of the candidate segments.
## 样例

### 样例输入 #1
```
1
0 0 4 0
8
0 0 2 1
-1 -1 2 2
3 3 5 -3
0 2 6 -1
2 -2 5 1
-1 1 3 -3
-1 0 2 0
-1 -1 2 2
```
### 样例输出 #1
```
6
```


---

---
title: "[GCPC 2024] Fair Fruitcake Fragmenting"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13721
tag: ['计算几何', '2024', 'Special Judge', 'ICPC', '双指针 two-pointer']
---
# [GCPC 2024] Fair Fruitcake Fragmenting
## 题目描述

Frida's birthday is just coming up, and as her best friend, you obviously baked a cake for her.
Since you know that Frida loves rotational symmetry, you thought to bake a cake that
looks the same from above when rotated by $180^\circ$.
Of course, you could have simply baked a boring round cake, but without a perfectly round cake tin, this sounds easier than done.
Therefore, you decided to bake a cake whose shape can be described by straight line segments.

![](https://cdn.luogu.com.cn/upload/image_hosting/j4oo5c4y.png)

:::align{center}

Figure F.1: Visualization of Sample Input 2. The swirly cake looking like an S can be cut into the red and blue part with a single cut.

:::

However, after you are done with your cake, you notice that you also want to cut the cake into two equal pieces, one for Frida and one for yourself.
More precisely, you wonder if it is possible to cut the cake along an infinite line such that it splits into exactly two
parts of equal weight.
You can assume that the cake has uniform density and height.
## 输入格式

The input consists of:
- One line containing an *even* integer $n$ ($4 \leq n\leq 10^5$), the number of points needed to describe the cake's shape.
- $n$ lines, each containing two integers $x$, $y$ ($0\leq x,y \leq 10^6$), the $x$ and $y$ coordinates of a point on the border of the cake's shape.

The following additional guarantees are given for the shape of the cake:
- The cake has a $180^\circ$ rotational symmetry.
- The points are given in counterclockwise order.
- No three consecutive points are collinear.
- The shape is simple (no segments intersect and only consecutive segments touch at their ends).
## 输出格式

Output two different points on the desired line as $x_1/c_1$ $y_1/d_1$ $x_2/c_2$ $y_2/d_2$, where $|x_i|$, $|y_i|$, $|c_i|$ and $|d_i|$ are integers and at most $10^9$, and $x_i/c_i$} is the first coordinate of point $i$ and $y_i/d_i$ is the second ($1\leq i\leq2$). If the denominator of a fraction is $1$ you may output only the numerator. Fractions do not have to be reduced. If there is no such line, output "$\texttt{impossible}$" instead.

It can be shown that if there is a line as desired, it is possible to represent it in the given format.
## 样例

### 样例输入 #1
```
4
0 0
2 0
2 2
0 2
```
### 样例输出 #1
```
1 1 1337/42 3141/1000
```
### 样例输入 #2
```
20
7 1
8 2
8 5
7 6
4 6
4 4
3 4
3 7
6 7
7 8
2 8
1 7
1 4
2 3
5 3
5 5
6 5
6 2
3 2
2 1
```
### 样例输出 #2
```
11 13 -2 -4
```
### 样例输入 #3
```
10
11 5
10 2
12 6
2 2
7 3
1 1
2 4
0 0
10 4
5 3
```
### 样例输出 #3
```
impossible
```


---

---
title: "[NOI2009] 描边"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1756
tag: ['计算几何', '高精度', '2009', 'NOI', '提交答案', 'Special Judge', '二分图']
---
# [NOI2009] 描边
## 题目描述

小 Z 是一位杰出的数学家。聪明的他特别喜欢研究一些数学小问题。

有一天，他在一张纸上选择了 $n$ 个点，并用铅笔将它们两两连接起来，构成 $\dfrac{n(n-1)}{2}$ 条线段。由于铅笔很细，可以认为这些线段的宽度为 $0$。

望着这些线段，小 Z 陷入了冥想中。他认为这些线段中的一部分比较重要，需要进行强调。因此小 Z 拿出了毛笔，将它们重新进行了描边。毛笔画在纸上，会形成一个半径为 $r$ 的圆。在对一条线段进行描边时，毛笔的中心（即圆心）将从线段的一个端点开始，沿着该线段描向另一个端点。下图即为在一张 $4$ 个点的图中，对其中一条线段进行描边强调后的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/h92i5d69.png)

现在，小 Z 非常想知道在描边之后纸面上共有多大面积的区域被强调，你能帮助他解答这个问题么？
## 输入格式

本题是一道提交答案型试题，所有的输入文件 `path1.in` $\sim$ `path10.in` 已在相应目录下。

输入文件请点击 [这里](http://pan.baidu.com/s/1gfeLZqz) 下载。

输入文件的第一行为一个正整数 $n$，表示选择的点的数目。

第二行至第 $n+1$ 行，其中：第 $i+1$ 行中为两个实数 $x_i,y_i$，表示点 $i$ 的坐标为 $(x_i,y_i)$。

第 $n+2$ 行为一个正整数 $m$，表示小 Z 认为比较重要的线段的条数。

第 $n+3$ 行至第 $n+m+2$ 行，每行有两个正整数 $a,b$，表示一条线段。其中 $a,b$ 两个数分别表示该线段的两个端点的编号。

第 $n+m+3$ 行中为一个实数 $r$，表示毛笔在纸上形成的圆的半径。

第 $n+m+4$ 行中为四个实数 $p_1,p_2,p_3,p_4$，即评分使用的参数。
## 输出格式

输出文件 `path*.out` 仅一行一个数，即为描边后被强调区域的总面积。
## 样例

### 样例输入 #1
```
2
1 1
1 2
1
1 2
1
0.00001 0.001 0.1 1

```
### 样例输出 #1
```
5.1415927
```
## 提示

每个测试点单独评分。

本题设有 $4$ 个评分参数 $p_1,p_2,p_3,p_4$（$p_1 \lt p_2 \lt p_3 \lt p_4$），已在输入文件中给出。

你的得分将按照如下规则给出：

- 若你的答案与标准答案相差不超过 $p_1$，则该测试点你将得到满分；
- 否则，若你的答案与标准答案相差不超过 $p_2$，则你将得到该测试点 $70\%$ 的分数；
- 否则，若你的答案与标准答案相差不超过 $p_3$，则你将得到该测试点 $40\%$ 的分数；
- 否则，若你的答案与标准答案相差不超过 $p_4$，则你将得到该测试点 $10\%$ 的分数；
- 否则，该测试点你的得分为 $0$。


---

---
title: "[JLOI2014] 镜面通道"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3260
tag: ['计算几何', '2014', '吉林', '最小割']
---
# [JLOI2014] 镜面通道
## 题目描述

在一个二维平面上，有一个镜面通道，由镜面 $AC, BD$ 组成，$AC, BD$ 长度相等，且都平行于 $x$ 轴，$B$ 位于 $(0,0)$。

通道中有 $n$ 个外表面为镜面的光学元件，光学元件 $\alpha$ 为圆形，光学元件 $\beta$ 为矩形（这些元件可以与其他元件和通道有交集，具体看下图）。光线可以在 $AB$ 上任一点以任意角度射入通道，光线不会发生削弱。当出现元件与元件，元件和通道刚好接触的情况视为光线无法透过（比如两圆相切）。

现在给出通道中所有元件的信息（$\alpha$ 元件包括圆心坐标和半径 $x_i, y_i, r_i$，$\beta$ 元件包括左下角和右上角坐标 $x_1, y_1, x_2, y_2$）

![](https://cdn.luogu.com.cn/upload/pic/17612.png)

如上图，$S$ 到 $T$ 便是一条合法线路。

![](https://cdn.luogu.com.cn/upload/pic/17613.png)

当然，显然存在光线无法透过的情况，现在交给你一个艰巨的任务，请求出至少拿走多少个光学元件后，存在一条光线线路可以从 $CD$ 射出。

下面举例说明：

![](https://cdn.luogu.com.cn/upload/pic/17614.png) 

现在假设，取走中间那个矩形，那么就可以构造出一条穿过通道的光路，如图中的 $S$ 到 $T$。

## 输入格式

第一行包含两个整数，$x, y$，表示 $C$ 点坐标。

第二行包含一个数字 $n$，表示有 $n$ 个光学元件。

接下来 $n$ 行第一个数字如果是 $1$，表示元件 $\alpha$，后面会有三个整数 $x_i, y_i, r_i$ 分别表示圆心坐标和半径。第一个数字如果是 $2$，表示元件 $\beta$，后面会有四个整数 $x_1, y_1, x_2, y_2$ 分别表示左下角和右上角坐标。（矩形都平行，垂直于坐标轴）
## 输出格式

输出包含一行，至少需要拿走的光学元件个数 $m$。

## 样例

### 样例输入 #1
```
1000 100
6
1 500 0 50
2 10 10 20 100
2 100 10 200 100
2 300 10 400 100
2 500 10 600 100
2 700 0 800 100
```
### 样例输出 #1
```
2
```
## 提示

$x\leq 10^5$，$y\leq 1000$，$n\leq 300$。



---

---
title: "[SDOI2013] 逃考"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3297
tag: ['计算几何', '2013', '山东', '半平面交']
---
# [SDOI2013] 逃考
## 题目描述

髙考又来了，对于不认真读书的来讲真不是个好消息为了小杨能在家里认真读书，他的亲戚决定驻扎在他的家里监督他学习，有爷爷奶奶、外公外婆、大舅、大嫂、阿姨 ......。

小杨实在是忍无可忍了，这种生活跟监狱有什么区别！为了他亲爱的小红，为了他的 dota， 他决定越狱！

假设小杨的家是个 $n\times m$ 的矩阵，左下角坐标为（$0,0)$，右上角坐标为（$x_1,y_1)$。小杨有 $n$ 个亲戚，驻扎在矩阵里（位置不同，且不在矩阵的边上）。小杨家里的每个地方都被亲戚监控着，而且只被距离最近的亲戚监控：

也就是说假设小杨所在的位置是（$3,3)$, 亲戚 $A$ 在（$3,0)$，A 距离小杨距离是 $3$；亲戚 $B$ 在（$6,7),$ 则 $B$ 距离小杨距离是 $5$。距离 $A<$ 距离 $B$，所以（$3,3)$ 位置由 $A$ 监控。

如果“最近距离”出现同时有几个亲戚，那么那个位置同时被那几个亲戚监控。

给出小杨的坐标（$x_0,y_0)$。因为被发现的人数越少，越狱成功的机会越大，所以小杨需要你设计一条越狱路线到达矩形的边上，且被发现的人数最少。

小杨做的方向是任意的，也就是说路线上的任意位置 $H$ 需要是实数。

保证一开始小杨只被一个亲戚监控着。
## 输入格式

第一行一个正整数 $t \le 3$ 表示数据个数。

接下来 $t$ 个数据：

第一行 $n$ 表示亲戚个数。

第二行 $4$ 个正整数表示举行右上角坐标 $(x_1,y_1)$ 和小杨的坐标 $(x_0,y_0)$。

接下来 $n$ 行，每行 $2$ 个正整数表示一个亲戚的位置。
## 输出格式

每个数据一个正整数表示越狱被发现人数的最小值

## 样例

### 样例输入 #1
```
2
4
10 10 5 5
5 6
3 5
7 5
5 3
17
14 12 7 6
7 11
6 9
7 7
1 10
2 20
1 6
2 6
1 1
2 2
5 1
5 2
13 1
12 2
12 7
13 7
12 11
13 11
```
### 样例输出 #1
```
1
2
```
## 提示

数据解释 :。

第一个数据，小杨直接往上走，只被 $(5,6)$ 监控过。

第二个数据，小杨被 $(7,7)$ 监控 - 走到 $(9,9)$ 被 $(7,11)$ 监控，然后直接往上走。

数据规模 :

前 $50\%$ 数据, $n \le 200$。

其余数据 $n \le 600$。


---

---
title: "[SDOI2014] 里面还是外面"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3316
tag: ['计算几何', '2014', '山东']
---
# [SDOI2014] 里面还是外面
## 题目背景

upd：

- 数据更新：现在选取了原题的总共 10 个测试点，并删除了其中两个不符合题意的。
## 题目描述

Alice 给出了平面上的一个简单 $N$-多边形。所谓简单 $N$-多边形，包括 $N$ 个给定的端点，和连接相邻点的直线段。特别的，我们认为 1 号点与 $N$ 号点相邻。

对于边界上不同的直线段，保证它们只会在公共端点处相交。有的时候 Alice 会指着平面上一个点，然后问 Bob：“这个点是在多边形的里面呢，还是外面呢，还是在边界上呢？”

这个时候，如果她所指的点是多边形的一个顶点或者在多边形某条边的边界上，都将被认为是在多边形的边界上。还有的时候，Alice 为了加大难度，会删除连接 $a$ 和 $b$ 的边，并插入新的点 $c$（新插入的点保证不与任何已有的端点重合，也不在任何边界上），然后新增 $a$ 到 $c$ 的边与 $b$ 到 $c$ 的边，从而得到一个新的简单多边形。

Alice 保证这样的操作得到的新图形总是简单多边形。Bob 要做的，就是准确回答出 Alice 的提问。而实际上，Alice 的每一次提问都将由 Bob 上一次的回答决定，虽然这个回答是唯一的，但却意味着如果 Bob 不能回答出前一个问题，就不能拿到 Alice 的下一个问题。

不过，Alice 对多边形的修改确实事先准备好的。详细来说：Alice 的每一次修改命令可以看作是一个六元组：$\langle x_a, y_a, x_b, y_b, x_c, y_c \rangle$ 表示删除了坐标位置 $(x_a, y_a)$ 与坐标位置 $(x_b, y_b)$ 的点之间的连边，并插入新的点 $(x_c, y_c)$。

这里我们保证坐标为 $(x_a, y_a)$ 的点与坐标为 $(x_b, y_b)$ 的点总是存在的。因为 Alice 保证了所有出现的点（这包括了询问点）的坐标都是非负整数，且都小于 $10^9$，且多边形中（这不包括询问点）任意两个点的 $x$ 坐标不同，$y$ 坐标也不同。所以每一次询问 Alice 将给出 7 个非负整数：$r$，$x_{\text{in}}$，$y_{\text{in}}$，$x_{\text{out}}$，$y_{\text{out}}$，$x_{\text{bd}}$，$y_{\text{bd}}$。而 Alice 这一次询问真正要询问的点 $(X, Y)$ 的坐标将由上一次询问的点 $(x_0, y_0)$ 与上一次询问的回答而决定。例如，若上一次询问的点在多边形外，则：
$$
X = (r \times x_0 + x_{\text{out}}) \bmod 10^9
$$
$$
Y = (r \times y_0 + y_{\text{out}}) \bmod 10^9
$$
对于第一次询问，我们假设 $x_0 = y_0 = 0$，也就是说将 $(0,0)$ 考虑为前一次的询问。
## 输入格式

输入文件的第一行有一个整数 $N$，表示初始时多边形的点数。

之后 $N$ 行，每行一对非负整数 $x$ 和 $y$（$0 \leq x, y < 10^9$）。按照某一顺序依次描述了多边形的所有顶点的坐标，并编号为 1 到 $N$。这里我们只认为，对于平面上的一点 $(10^{100}, 10^{100})$ 一定是处在多边形以外的。之后一行有一个整数 $Q$，表示总的操作次数。

之后 $Q$ 行，每行第一个数字 $p$，如果 $p=0$ 则表示询问；如果 $p=1$ 则表示修改。
- 对于询问，之后给出了 7 个非负整数，它们是：$r$，$x_{\text{in}}$，$y_{\text{in}}$，$x_{\text{out}}$，$y_{\text{out}}$，$x_{\text{bd}}$，$y_{\text{bd}}$
- 对于修改，之后给出了 6 个整数，它们是：$x_a$，$y_a$，$x_b$，$y_b$，$x_c$，$y_c$
## 输出格式

对于每一次询问操作，单独输出一行且只包含一个字符串，它或者是 `in`、或者是 `out`、或者是 `bd`（均为小写字符），分别表示询问点在多边形的内、外或边界。

## 样例

### 样例输入 #1
```
6
249999999 499999998
583333331 83333333
83333333 333333332
333333332 999999996
833333330 749999997
499999998 833333330
12
0 1 872826049 679758020 472526437 270998755 15447952 502239247
1 833333330 749999997 499999998 833333330 916666663 666666664
1 833333330 749999997 916666663 666666664 416666665 916666663
0 1 371653715 747730364 409617871 21996163 118531999 759280767
1 249999999 499999998 583333331 83333333 666666664 166666666
0 1 195920917 488293591 322952040 262793733 678458193 506876149
0 1 203963007 782710007 391614158 831643205 340800821 896322422
0 1 498571077 461554269 765704840 973009111 152064733 114249255
1 499999998 833333330 249999999 499999998 999999996 583333331
0 1 159294077 702544938 787871788 619972292 941209243 950700951
0 1 791254252 411705638 382076333 263993056 306662346 47793905
0 1 13359599 513224793 415037020 28305143 48117026 34994422
```
### 样例输出 #1
```
out
out
in
in
out
out
out
in
```
## 提示

对于 100% 的数据：$N \leq 50000$，$Q \leq 50000$，所有坐标非负且均小于 $10^9$，而 $r$ 或者为 1 或者为 0。


---

---
title: "[WC2013] 平面图"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4073
tag: ['图论', '计算几何', '2013', '倍增', '平衡树', '枚举', '生成树', 'WC']
---
# [WC2013] 平面图
## 题目描述

在一个平面中有 $n$ 个顶点和 $m$ 条直线段，第 $i$ 个顶点的坐标为 $(x_i, y_i)$， 第 $j$ 条直线段连接顶点 $u_j$ 和顶点 $v_j$，权值为 $h_j$， 除顶点 $u_j$ 和 $v_j$ 外直线段 $j$ 不经过其他的顶点。任意两条直线段如果存在公共点，则该公共点一定是一个顶点，此时这两条直线段都会连接这个顶点。对于任意的两个顶点 $x$ 和 $y$，总是可以找到一顶点序列 $a_1,a_2,\cdots,a_k$ 使得 $a_1=x$，$a_k=y$ 且对于任意 $1\le i< k$ 满足 $a_i$ 和 $a_{i+1}$ 被一条直线段直接连接。

这 $m$ 条直线段将整个平面分成了若干个区域，其中只有一个区域是无穷大的，其余均是有界的，我们称无穷大的区域为禁区。

现在给出 $q$ 次询问，每次给定平面中的任意两个不是顶点且分别不在任意一条直线段上的点 $A$ 和 $B$，请画一条曲线连接 $A$ 和 $B$，要求曲线不能经过禁区以及任何顶点，并使得穿过的直线段中权值最大的尽可能小。你需要对每次询问回答这个值最小为多少。

## 输入格式

第一行有两个正整数 $n,m$，分别表示顶点数和直线段数。

接下来 $n$ 行，每行两个整数，这部分中第 $i$ 行（总第 $i+1$ 行）的两个整数 $x_i,y_i$ 为顶点 $i$ 的坐标。

接下来 $m$ 行，每行三个正整数 $u,v,h$，表示有一条直线段连接顶点 $u$ 和顶点 $v$，权值为 $h$。其中 $u\neq v$。

接下来的一行，有一个正整数 $q$，表示询问数量。

接下来 $q$ 行，每行四个实数 $A_x,A_y,B_x,B_y$， 表示一组两个点的坐标分别为 $(A_x, A_y)$ 和 $(B_x, B_y)$ 的询问。

## 输出格式

输出 $q$ 行，每行一个正整数，依次表示每个询问的答案。特别的，若不需要跨过任何一条边即可到达，请输出 $0$；若不存在合法的曲线，请输出 $-1$。

## 样例

### 样例输入 #1
```
9 12
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
1 2 10
2 3 10
3 6 10
6 9 10
9 8 10
8 7 10
7 4 10
4 1 10
2 5 3
5 8 2
5 6 4
4 5 1
3
1.5 1.5 2.5 2.5
1.5 2.5 2.5 1.5
0.5 0.5 1.5 1.5
```
### 样例输出 #1
```
2
3
-1
```
## 提示

【样例说明】

![QQ20180112214336.png](https://cdn.luogu.com.cn/upload/image_hosting/228djzaq.png)

【数据规模与约定】

本题共设有 $10$ 个测试点，每个测试点的规模与特征如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/2l8u3hkb.png)

对于全部数据，均满足 $5$ ≤ $n$, $m$, $q$ ≤ $100,000$，所有直线段的权值不会超过 $10^9$。所有询问坐标均为不超过 $10^7$ 的实数，且保证是 $0.5$ 的整数倍。



---

---
title: "[WC2012] 记忆中的水杉树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4125
tag: ['计算几何', '2012', '线段树', 'Special Judge', '拓扑排序', 'WC']
---
# [WC2012] 记忆中的水杉树
## 题目描述

江苏省常州高级中学是一所百年名校，这里萦绕着无数人难以忘怀的回忆。

Will 记得，在他小的时候，常州高级中学改建以前，学校里有一片高大的水杉林，每到水杉落叶之时，针状的叶子会像毯子一样盖在地上，走在上面浪漫而又闲适。那时，Will 和同学们还喜欢用这些针叶，在水杉树下，玩“取叶子”的游戏。 

游戏一开始，大家先将 $n$ 片针叶平铺在地上。接着，每一轮可以有一个同学选择一片针叶，按水平或者垂直方向将针叶移走（也就是平移到无穷远处）——当然，前提是移动过程中不被任何尚未移走的针叶所阻碍。如果某一轮针叶的移动会被阻碍，那么这次移动就是非法的，是不被允许的。

$n$ 轮过后，当针叶都被移走时，游戏也就结束了。 针叶并不是任何时刻都可以被移动的。当针叶很多的时候，判断每一轮中一片针叶是否可以按一个特定的方向移动是一件很麻烦的事情。 现在我们将地面抽象为平面直角坐标系，$n$ 片针叶抽象为平面上 $n$ 条互不相交的线段，并将其从 $1$ 到 $n$ 编号，Will 还将给出每一轮游戏中，他想要移动的针叶编号以及移动方向，请你帮助他：

1. 找出最早的一次非法移动出现在哪一轮；

2. 给出一个合法的移动方案完成这个游戏。

注意：在线段移动时仅端点接触不会造成阻碍，具体请参见样例。

## 输入格式

输入文件的第一行包含一个正整数 $n$，表示针叶的数量。

接下来 $n$ 行，每行 $4$ 个整数，描述针叶的位置信息。其中第 $i$ 行的整数为 $a_i$，$b_i$，$c_i$，$d_i$，表示编号为 $i$ 的针叶所抽象成的线段的端点为$(a_i, b_i)$和$(c_i, d_i)$。

接下来 $n$ 行，每行 $2$ 个整数，描述移动操作。其中第 $i$ 行的整数为 $p_i$，$q_i$，表示第 $i$ 轮移动的针叶编号为 $p_i$，方向为 $q_i$。其中 $q_i$为一个 $0$ 到 $3$ 之间的整数，$0$ 表示向左平移（即 $x$ 轴负方向） ，$1$ 表示向上平移（即 $y$ 轴正方向） ，$2$ 表示向右平移，$3$ 表示向下平移。

输入数据保证：

- 所有线段长度为正，两两之间没有公共点，且不存在垂直或者水平的线段;
- $p_1$ 到 $p_n$ 恰好组成一个 $1$ 到 $n$ 的排列；
- Will 所给出的移动操作中一定存在非法移动；
- $n$ 轮均合法的移动操作总是存在的。

## 输出格式

输出文件一共包含 $n+1$ 行。

输出的第一行包含一个 $1$ 到 $n$ 之间的整数，表示最早出现非法移动的是哪一轮。

接下来 $n$ 行，每行两个整数，内容同输入格式所述，描述一个合法的移动序列。

## 样例

### 样例输入 #1
```
5 
2 5 5 8 
2 1 3 5 
5 2 6 5 
7 0 4 2 
3 1 4 0 
2 0 
3 0 
4 0 
1 2 
5 1 
```
### 样例输出 #1
```
3 
2 0 
3 0 
4 3 
1 2 
5 1 
```
### 样例输入 #2
```
4
-1 1 2 3
13 5 9 8
10 10 15 14
10 17 0 20
3 1
2 1
1 1

4 1
```
### 样例输出 #2
```
2
4 1
3 1
2 1
1 1
```
## 提示

【样例说明】

在 Will 给出的移动方案的第 $3$ 轮中，编号为 $4$ 的针叶向左移动会被编号为 $5$ 的针叶阻碍。

【数据范围】

具体数据范围见下表。

![](https://cdn.luogu.com.cn/upload/image_hosting/y7thkctp.png)

对于一个测试点：

如果非法移动判断正确，但是给出的方案错误，可以得到 $5$ 分。此时会提示：`An invalid move in step`

如果非法移动判断错误，但是给出的方案正确，可以得到 $5$ 分。此时会提示：`Negative error detection!`

如果非法移动的判断与给出方案均正确，则可以得到 $10$ 分；

否则，得 $0$ 分。

 如果程序的输出格式不正确，将被直接判作输出格式不正确，将被直接判作 $0$ 分。



---

---
title: "[NOI2005] 月下柠檬树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4207
tag: ['计算几何', '2005', '递归', 'NOI', '积分']
---
# [NOI2005] 月下柠檬树
## 题目描述

李哲非常非常喜欢柠檬树，特别是在静静的夜晚，当天空中有一弯明月温柔地照亮地面上的景物时，他必会悠闲地坐在他亲手植下的那棵柠檬树旁，独自思索着人生的哲理。

李哲是一个喜爱思考的孩子，当他看到在月光的照射下柠檬树投在地面上的影子是如此的清晰，马上想到了一个问题：树影的面积是多大呢？

李哲知道，直接测量面积是很难的，他想用几何的方法算，因为他对这棵柠檬树的形状了解得非常清楚，而且想好了简化的方法。

李哲将整棵柠檬树分成了 $n$ 层，由下向上依次将层编号为 $1,2,...,n$。从第 $1$ 到 $n-1$ 层，每层都是一个圆台型，第 $n$ 层(最上面一层)是圆锥型。对于圆台型， 其上下底面都是水平的圆。对于相邻的两个圆台，上层的下底面和下层的上底面重合。第 $n$ 层(最上面一层)圆锥的底面就是第 $n-1$ 层圆台的上底面。所有的底面 的圆心(包括树顶)处在同一条与地面垂直的直线上。李哲知道每一层的高度为 $h_1,h_2,...,h_n$，第 $1$ 层圆台的下底面距地面的高度为 $h_0$，以及每层的下底面的圆的半径 $r_1,r_2,...,r_n$。李哲用熟知的方法测出了月亮的光线与地面的夹角为 $\mathrm{alpha}$。

![](https://cdn.luogu.com.cn/upload/pic/13770.png)

为了便于计算，假设月亮的光线是平行光，且地面是水平的，在计算时忽略树干所产生的影子。李哲当然会算了，但是他希望你也来练练手。
## 输入格式

第一行包含一个整数 $n$ 和一个实数 $\mathrm{alpha}$，表示柠檬树的层数和月亮 的光线与地面夹角（单位为弧度）。

第二行包含 $n+1$ 个实数 $h_0,h_1,h_2,...,h_n$ 表示树离地的高度和每层的高度。

第三行包含 $n$ 个实数 $r_1,r_2,...,r_n$ 表示柠檬树每层下底面的圆的半径。

同一行相邻的两个数之间用一个空格分隔。

输入的所有实数的小数点后可能包含一至十位有效数字。
## 输出格式

输出一个实数，表示树影的面积，四舍五入保留两位小数。
## 样例

### 样例输入 #1
```
2  0.7853981633 
10.0  10.00  10.00 
4.00  5.00
```
### 样例输出 #1
```
171.97
```
## 提示

对于 $10 \%$ 的数据，$n \leq 1$；

对于 $30 \%$ 的数据，$n \leq 2$；

对于 $60 \%$ 的数据，$n \leq 20$；

对于 $100 \%$ 的数据，$1 \leq n \leq 500$，$0.3 < \mathrm{alpha} < \frac{\pi}{2}$，$0 < h_i \leq 100$，$0 < r_i \leq 100$。


---

---
title: "[SCOI2015] 小凸想跑步"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4250
tag: ['计算几何', '2015', '四川', '各省省选', '半平面交']
---
# [SCOI2015] 小凸想跑步
## 题目描述

小凸晚上喜欢到操场跑步，今天他跑完两圈之后，他玩起了这样一个游戏。

操场是个凸 $n$ 边形， $n$ 个顶点按照逆时针从 $0$ ∼ $n - 1$ 编号。现在小凸随机站在操场中的某个位置，标记为 $p$ 点。将 $p$ 点与 $n$ 个顶点各连一条边，形成 $n$ 个三角形。如果这时 $p$ 点， $0$ 号点， $1$ 号点形成的三角形的面
积是 $n$ 个三角形中最小的一个，小凸则认为这是一次正确站位。

现在小凸想知道他一次站位正确的概率是多少。
## 输入格式

第 $1$ 行包含 $1$ 个整数 $n$, 表示操场的顶点数和游戏的次数。

接下来有 $n$ 行，每行包含 $2$ 个整数 $x_i, y_i$，表示顶点的坐标。

输入保证按逆时针顺序输入点，所有点保证构成一个凸多边形。所有点保证不存在三点共线。
## 输出格式

输出 $1$ 个数，正确站位的概率，保留 $4$ 位小数。
## 样例

### 样例输入 #1
```
5
1 8
0 7
0 0
8 0
8 8

```
### 样例输出 #1
```
0.6316
```
## 提示

对于 $30$% 的数据， $3 \leq n \leq 4, 0 \leq x, y \leq 10$

对于 $100$% 的数据， $3 \leq n \leq 10^5, -10^9 \leq x, y \leq 10^9$


---

---
title: "[COCI 2009 Final Exam#2] Dvapravca"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4385
tag: ['计算几何', '2009', '线段树', '排序', 'COCI（克罗地亚）']
---
# [COCI 2009 Final Exam#2] Dvapravca
## 题目描述

给定平面上的$N$个点$,$其中有一些是红的$,$其他是蓝的

现在让你找一对平行线$,$在满足在平行线之间没有蓝点$,$并且平行线不经过任何一个点的情况下$,$使得被夹在平行线之间的红色点个数最多

给出的点没有三点共线的情况$,$平行线可以不平行坐标轴
## 输入格式

第一行一个整数$N$表示总点数

接下来$N$行每行两个整数和一个字符$R$或者$B$表示点的坐标和颜色
## 输出格式

一个整数表示最多红点数量
## 样例

### 样例输入 #1
```
4
0 0 R
0 1 B
1 1 R
1 0 B
```
### 样例输出 #1
```
2
```
## 提示

$N\le10^3,|x_i|,|y_i|\le10^9$


---

---
title: "【模板】三维凸包"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4724
tag: ['计算几何', '三维计算几何']
---
# 【模板】三维凸包
## 题目描述

给出空间中 $n$ 个点，求凸包表面积。
## 输入格式

第一行一个整数 $n$，表示点数。

接下来 $n$ 行，每行三个实数 $x, y, z$ 描述坐标。

## 输出格式

输出凸包表面积，保留 $3$ 位小数。
## 样例

### 样例输入 #1
```
4 
0 0 0
1 0 0
0 1 0
0 0 1
```
### 样例输出 #1
```
2.366
```
## 提示

$4 \le n \le 2000$


---

---
title: "[BalkanOI 2011] timeismoney"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5540
tag: ['图论', '计算几何', '2011', '生成树', 'BalkanOI（巴尔干半岛）']
---
# [BalkanOI 2011] timeismoney
## 题目描述

给出一个 $n$ 个点 $m$ 条边的无向图，第 $i$ 条边有两个权值 $a_i$ 和 $b_i$ 。

求该图的一棵生成树 $T$ ，使得

$$\left(\sum_{e\in T}a_e\right)\times\left(\sum_{e\in T}b_e\right)$$

最小。
## 输入格式

第一行两个正整数 $n,m$ 。

下 $m$ 行，每行 $4$ 个整数 $u_i,v_i,a_i,b_i$ ，表示第 $i$ 条边连接  $u_i$ 和 $v_i$ ，权值为 $a_i$ 和 $b_i$ 。

点的编号为 $0\sim n-1$ 。
## 输出格式

假设你求出的生成树为 $T$ ，你需要输出一行两个整数，分别为 $\displaystyle\sum_{e\in T}a_e$ 和 $\displaystyle\sum_{e\in T}b_e$ 。

如果有多解，请输出 $\displaystyle\sum_{e\in T}a_e$ 最小的那个。
## 样例

### 样例输入 #1
```
4 5
0 1 1 2
0 2 2 3
0 3 1 5
1 3 3 4
2 3 1 3
```
### 样例输出 #1
```
3 10
```
## 提示

对于 $100\%$ 的数据，$1\leq n\leq 200,1\leq m\leq 10000,0\leq a_i,b_i\leq 255$ 。


---

---
title: "[MtOI2019] 不可视境界线"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5617
tag: ['动态规划 DP', '数学', '计算几何', '2019', '洛谷原创', 'Special Judge', 'O2优化', '洛谷月赛']
---
# [MtOI2019] 不可视境界线
## 题目背景

「爆ぜろリアル！弾けろシナプス！パニッシュメント......ディス、ワールド！」  
「爆裂吧，现实！粉碎吧，精神！放逐这个世界！」  

## 题目描述

Rikka 坚信，她的父亲在「不可视境界线」中，等待着她的到来。在 Rikka 的梦里，「不可视境界线」出现了，那是 $n$ 个圆组成的图形。

具体地，有一个平面直角坐标系，坐标系的 $x$ 轴上有 $n$ 个点，第 $i$ 个点的坐标为 $(x_i,0)$。

Rikka 以每一个点作为圆心，作了 $n$ 个半径为 $r$ 的圆。她本想让你帮她计算这 $n$ 个圆的面积并，但是这个问题太简单了。

在一番思考后，Rikka 想让你计算出选出 $k$ 个圆后（即删除 $n-k$ 个圆），圆的面积并的最大值。

对于所有数据，有 $n,k\leq 10^5$，$r\leq 10^4$，$0\leq x_i\leq 10^9$，$x_i$ 为整数且不重复。保证输入的 $x_i$ 单调递增。

因为答案太大了，Rikka 考虑到你的电脑无法保持高精度，所以只要你的答案与标准答案的 **相对误差** 小于 $5\times 10^{-8}$，你的答案即被视为是正确的。

经过误差分析，本题保证使用原生 `cmath` 函数不会出错，请注意控制程序精度误差。

## 输入格式

共 $2$ 行。

第 $1$ 行输入 $3$ 个整数 $n$，$k$，$r$。

第 $2$ 行输入 $n$ 个整数 $x_1\ldots x_n$。

## 输出格式

一行 $1$ 个实数，表示所求答案，保证答案小于 $10^{14}$。

## 样例

### 样例输入 #1
```
8 5 2
1 3 7 11 15 21 27 33
```
### 样例输出 #1
```
62.83185307
```
### 样例输入 #2
```
8 5 8
1 3 7 11 15 21 27 33
```
### 样例输出 #2
```
686.19551835
```
## 提示

#### 样例解释 1

显然，可以选出 $5$ 个不相交的半径为 $2$ 的圆。

### 子任务

对于 $100\%$ 的数据，$n,k\leq 10^5$，$r\leq 10^4$，$0\leq x_i\leq 10^9$。

本题采用捆绑测试，共有 $7$ 个子任务，各子任务的分值和限制如下：

子任务 $1$（$11$ 分）：$k=n$。

子任务 $2$（$13$ 分）：$n,k,r \leq 100$。

子任务 $3$（$6$ 分）：$n,k \leq 1000$，$r\leq 20$。

子任务 $4$（$15$ 分）：$n,k,r \leq 2000$，保证数据随机生成。

子任务 $5$（$23$ 分）：$r\leq 20$。

子任务 $6$（$12$ 分）：$k\leq 20$，$x_n \leq kr$。

子任务 $7$（$20$ 分）：无特殊限制。

### 题目来源

[MtOI2019 Extra Round](https://www.luogu.org/contest/22840) T5

出题人：disangan233

验题人：suwAKow，_sys



---

---
title: "「SWTR-4」Taking a Walk"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6214
tag: ['计算几何', '线段树', 'Special Judge', 'O2优化', '可持久化线段树', '可持久化']
---
# 「SWTR-4」Taking a Walk
## 题目背景

小 A 喜欢在广场上散步。

有一次在小 A 散步的时候，由于思考得过于投入，他不小心撞在了电线杆上。

于是就有了这道题目（当然是假的）。
## 题目描述

小 A 和 好友小 Y 站在一个平面上，他们的初始坐标分别是 $(Ax_0,Ay_0)$ 和 $(Bx_0,By_0)$。

当然，站着实在是太无聊了，所以他们会不停地移动。

准确来说，小 A 共有 $n$ 次移动，小 Y 共有 $m$ 次移动。

小 A 在第 $At_{i-1}$ 到第 $At_i$ 时刻会从 $(Ax_{i-1},Ay_{i-1})$ **匀速直线运动**到 $(Ax_i,Ay_i)$。

小 Y 在第 $Bt_{i-1}$ 到第 $Bt_i$ 时刻会从 $(Bx_{i-1},By_{i-1})$ **匀速直线运动**到 $(Bx_i,By_i)$。

- $At_0=Bt_0=0$。

小 A 还有 $q$ 次询问： 每次询问给出一个浮点数 $c$ 和一个整数 $f$，请求出他们第 $f$ 次相距 $c$ 的时刻。

- **特殊的，如果他们之间相距 $c$ 的时刻有无数个**，输出 `-2.33`。

- **特殊的，如果 $f$ 大于他们之间相距 $c$ 的次数**，输出 `-4.66`。

- 如果不满足上面两个条件，输出他们第 $f$ 次相距 $c$ 的时刻。

## 输入格式

第一行，三个整数 $n,m,q$ —— $n$ 表示小 A 的移动次数，$m$ 表示小 Y 的移动次数，$q$ 表示询问次数。

第二行，四个两位浮点数 $Ax_0,Ay_0,Bx_0,By_0$ —— 表示小 A 和小 Y 的初始坐标。

接下来 $n$ 行，第 $i$ 行三个两位浮点数 $Ax_i,Ay_i,At_i$ —— 意义见题目描述。

接下来 $m$ 行，第 $i$ 行三个两位浮点数 $Bx_i,By_i,Bt_i$ —— 同上。

接下来 $q$ 行，每行一个两位浮点数 $c$ 和一个整数 $f$ —— 描述一个询问。
## 输出格式

共 $q$ 个浮点数，表示每个询问的答案。
## 样例

### 样例输入 #1
```
3 3 10
0.00 0.00 0.00 1.00
-1.00 -1.00 0.20
10.00 10.00 0.41
-4.56 -1.23 1.00
-2.00 -1.00 0.40
-10.00 -10.00 0.41
9.87 6.54 1.00
0.00 1
1.00 1
5.00 1
5.00 3
5.00 4
10.00 2
10.00 6
28.28 1
28.28 2
28.29 1
```
### 样例输出 #1
```
-4.66
-2.33
0.26970954
0.83836048
-4.66
0.65792852
-4.66
0.40999665
0.41005730
-4.66
```
## 提示

**「Special Judge」**

**本题使用 Special judge。**

如果你的输出与正确答案的**相对误差或绝对误差**不超过 $10^{-7}$，将会获得该测试点的满分，否则不得分。**建议输出至少 $8$ 位小数**。

请不要输出除了题目要求以外的数字，否则可能获得 UKE。

保证没有答案为 $0$ 的情况。

SPJ 如下：

```
#include "testlib.h"
#define double long double
const double eps=1e-7;
bool Equal(double x,double y){
	return abs(x-y)<=eps||abs((x-y)/y)<=eps;
}
int main(int argc, char* argv[]){
    registerTestlibCmd(argc, argv);
    int n=inf.readInt(),m=inf.readInt(),q=inf.readInt();
    for(int i=1;i<=q;i++){
    	double x=ouf.readDouble(),y=ans.readDouble();
    	if(!Equal(x,y))quitf(_wa,"On line %d the answer is wrong: expected = %.8LF, found = %.8LF",i,y,x);
	}
	quitf(_ok, "The answer is correct."); 
	return 0;
}
```

**「数据范围与约定」**

**本题使用捆绑测试。**

Subtask 编号 | $n,m\leq$ | $q\leq$ | 得分
:-: | :-: | :-: | :-:
$1$ | $5\times 10^2$ | $10^3$ | $10$
$2$ | $2\times 10^4$ | $2\times 10^4$ | $20$
$3$ | $4\times 10^4$ | $5\times 10^4$ | $30$
$4$ | $8\times 10^4$ | $3\times 10^5$ | $40$

对于 $100\%$ 的数据，有 $1\leq n,m\leq 8\times 10^4$，$1\leq q\leq 3\times 10^5$，$At_n=Bt_m\leq 6\times 10^4$，$1\leq f\leq m+n$，$0\leq c\leq 3\times 10^4$。

为保证极端数据下的精度，所有坐标的绝对值不大于 $10^4$。

保证 $At_i<At_{i+1}$，$Bt_i<Bt_{i+1}$，一次移动的时间不超过 $6\times 10^2$。**不保证**某次移动没有改变位置。

**请注意精度误差。**

**「时间 & 空间限制」**

对于第 $1$ 个子任务，时限 $\rm{1s}$；其余子任务时限 $\rm{2.5s}$。

对于第 $1$ 个子任务，空限 $\rm{128MB}$；其余子任务空限 $\rm{256MB}$。

**为了卡掉错解，出题人放短了时限，但时限仍在 std 的 $2$ 倍以上。**

**std 轻微卡常，请注意 I/O/常数优化。**

**本题开启自动 O2 优化。**

**「来源」**

[Sweet Round 04](https://www.luogu.com.cn/contest/26414) F。  
idea & std：[Alex_Wei](https://www.luogu.com.cn/user/123294)。


---

---
title: "平面欧几里得最小生成树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6362
tag: ['计算几何', 'Special Judge', 'O2优化', '分治', '生成树', '凸包']
---
# 平面欧几里得最小生成树
## 题目描述

平面上有 $n$ 个点，第 $i$ 个点坐标为 $(x_i, y_i)$。连接 $i, j$ 两点的边权为 $\sqrt{(x_i - x_j) ^ 2 + (y_i - y_j) ^ 2}$。求最小生成树的边权之和。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，每行输入两个整数 $x_i, y_i$。
## 输出格式

输出一行一个实数，表示答案。

当你的答案与标准输出的绝对误差或相对误差在 $10^{-6}$  内时，就会被视为正确。
## 样例

### 样例输入 #1
```
4
0 0
1 2
-1 2
0 4
```
### 样例输出 #1
```
6.472136
```
## 提示

#### 样例解释 1

该样例中，最小生成树如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/p0dtxt2l.png)

边权之和为 $2 \sqrt{5} + 2 \approx 6.47213595500$。

---

#### 数据规模与约定

- 对于 $50\%$ 的数据，$n \le 5000$。
- 对于 $100\%$ 的数据，$3 \le n \le 10 ^ 5$，$\lvert x_i \rvert, \lvert y_i \rvert \le 10 ^ 5$。


---

---
title: "不可视境界线[环版本]"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6455
tag: ['动态规划 DP', '计算几何', '二分', '单调队列', 'Special Judge', '分治', '随机调整', '凸完全单调性（wqs 二分）']
---
# 不可视境界线[环版本]
## 题目背景

- 原题 : [P5617 [MtOI2019]不可视境界线](https://www.luogu.com.cn/problem/P5617)

**附** : [关于本题的`SPJ`和数据的一些信息](https://www.luogu.com.cn/paste/tmwvh5vh)

若出现卡精度或数据出锅,吊打标算等情况,请联系出题人。
## 题目描述

有 $n$ 个半径为 $r$ 的圆,画在一个长度为 $L$ 的首尾相接的纸环上。

所有的圆心都在同一高度,可以看做在纸上画一个数轴然后卷起来,圆心的位置用这个数轴上的点描述。

如果无法理解纸环上圆的分布,可以查看样例解释以及子问题。

要求选出 $k$ 个圆,使得所有圆的并面积最大。

注意,您需要回答确切的选取方案而不是仅仅给出最大并面积。
## 输入格式

第一行包含四个整数 $n,k,r,L$ ,意义如题目所述。

第二行包含 $n$ 个整数,第 $i$ 个整数 $p[i]$ 描述了第 $i$ 个圆心在纸环上的位置(数轴上的坐标)。

对于 $2<i<n$ ,有 $p[i-1]<p[i]$。
## 输出格式

一行包含 $k$ 个整数,分别表示您选取的圆的编号,由`SPJ`来计算并面积。

您需要保证这些编号严格递增,并且在 $[1,n]$ 以内,否则被认为不合法而不得分。

与标准答案**相对误差**不超过 $10^{-9}$ ,**且绝对误差**不超过 $0.1$ 则认为正确。

通过估算,答案不会超过 $10^{12}$ 量级。
## 样例

### 样例输入 #1
```
5 3 10 30
0 7 14 21 28 
```
### 样例输出 #1
```
2 3 5 
```
### 样例输入 #2
```
10 3 10 65
0 7 15 24 30 36 41 49 57 63 
```
### 样例输出 #2
```
3 6 9
```
### 样例输入 #3
```
30 10 50 169
0 7 14 21 28 35 42 45 51 55 61 65 68 75 79 83 87 94 97 105 113 118 126 133 140 147 151 156 163 167 
```
### 样例输出 #3
```
3 5 8 11 15 19 21 24 27 30 
```
## 提示

**样例解释** : 

- **样例1** : 最终的并面积约为 $565.871835$。

圆的分布如图所示,其中, $⊙A$ 和 $⊙A2$ 是同一个圆, $⊙B$ 和 $⊙B2$ 是同一个圆。

可以视作向右平移 $L=30$ 个单位长度而得,事实上就相当于在纸环上绕了一圈回到起点。

由于是同一个圆,被红色部分覆盖的面积不能重复计算,最大的并面积即为蓝色部分的面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/g2dk0sqv.png)

- **样例2** : 最终的并面积约为 $942.477796$。

- **样例3** : 最终的并面积约为 $16817.058547$。

**数据范围与约定** :

| 子任务编号 | n | k | 时限 |
| :--: | :--: | :--: | :--: |
| 1 | $10$ | - | $\texttt{1s}$ |
| 2 | $100$ | - | $\texttt{1s}$ |
| 3 | $2000$ | - | $\texttt{1.6s}$ |
| 4 | $3\times 10^4$ | $100$ | $\texttt{2.2s}$ |
| 5 | $1\times 10^5$ | - | $\texttt{3s}$ |

时限在 `std` 耗时的两倍以上。

对于所有的数据, $n\leq 10^5$，$10\leq r\leq 2000$，$0\leq p[i]< L\leq 10^8$，$4r<L$，$3\leq k \leq n$。

表格中均为上界。注意,一些下界限制可能帮助省去了问题的某些边界情况。


---

---
title: "Run Away"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6505
tag: ['计算几何', 'Special Judge', '凸包', '线段相交']
---
# Run Away
## 题目描述

平面直角坐标系内有一个矩形，左下角坐标为 $(0, 0)$，右上角为 $(w, h)$，边平行于坐标轴。

矩形内有 $n$ 个已知点，第 $i$ 个点坐标为 $(x_i, y_i)$。

请找到矩形内一点，使得这个点到最近的已知点距离最远。输出这个距离的值即可。
## 输入格式

第一行输入三个整数 $w, h, n$。

接下来 $n$ 行，每行输入两个整数 $x_i, y_i$。
## 输出格式

输出一行一个实数，表示最近距离的最大值。

当你的答案与标准输出的绝对误差或相对误差在 $10^{-6}$ 内时，就会被视为正确。
## 样例

### 样例输入 #1
```
100 100 4
10 10
10 90
90 10
90 90

```
### 样例输出 #1
```
56.5685424949

```
### 样例输入 #2
```
3000 3000 4
1200 85
63 2500
2700 2650
2990 100

```
### 样例输出 #2
```
1601.8805541731

```
## 提示

#### 样例解释 1

所求点坐标为 $(50, 50)$，到已知最近点的距离为 $40 \sqrt{2} \approx 56.568542494923802$。

---

#### 数据范围

- 对于 $50\%$ 的数据，$n \le 50$。
- 对于 $100\%$ 的数据，$1 \le w, h \le 10\ 000$，$3 \le n \le 1000$，$0 \le x_i \le w$，$0 \le y_i \le h$。

输入数据中可能有重点。

---

来源：IOI 2006 国家集训队论文「王栋 —— 浅析平面 voronoi 图的构造及应用」。


---

---
title: "[ICPC 2014 WF] Messenger"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6897
tag: ['计算几何', '2014', '二分', 'Special Judge', 'ICPC']
---
# [ICPC 2014 WF] Messenger
## 题目描述

Misha needs to send packages to his friend Nadia. Both of them often travel across Russia, which is very large. So they decide to hire a messenger. Since the cost of the messenger service depends on the time it takes to deliver the package, they need your help to optimize a little bit.

Assume Misha and Nadia move on a two-dimensional plane, each visiting a sequence of places and moving along straight line segments from place to place. Your task is to find the shortest possible delivery time given their two paths.

Misha hands the package to the messenger at some point along his path. The messenger moves without delay along a straight line from the pick-up to intercept Nadia, who is traveling along her path. Misha, Nadia and the messenger move with a constant speed of $1$ distance unit per time unit. The delivery time is the time between Misha handing over the package and Nadia receiving it.
## 输入格式

The input consists of a single test case. The test case contains two path descriptions, the first for Misha and the second for Nadia. Each path description starts with a line containing an integer $n$, the number of places visited ($2 \leq n \leq 50\, 000$). This is followed by $n$ lines, each with two integers $x_ i$ and $y_ i$ specifying the coordinates of a place ($0 \leq x_ i, y_ i \leq 30\, 000$). Coordinates of the places are listed in the order in which they are to be visited, and successive places do not have the same coordinates.

Misha and Nadia start their journeys at the same time, visiting the places along their paths without stopping. The length of each path is at most $10^6$. The package must be picked up at the latest when Misha reaches his final place and it must be delivered at the latest when Nadia reaches her final place.
## 输出格式

Display the minimal time needed for delivery. Give the answer with an absolute error of at most $10^{-3}$ or a relative error of at most $10^{-5}$. If the package cannot be delivered, display impossible instead.
## 样例

### 样例输入 #1
```
2
0 0
0 10
2
4 10
4 0

```
### 样例输出 #1
```
4.00000

```
### 样例输入 #2
```
2
0 0
1 0
3
2 0
3 0
3 10

```
### 样例输出 #2
```
5.00000

```
## 提示

Time limit: 3000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

题目描述：  
平面上有两个移动的点 A,B，其中 A 想要向 B 发送一条信息。两个点会同时出发，各自沿着一个折线移动到终点为止。A 会在移动的途中发送一条信息，这条信息可以视作一个点 C，它会沿一条射线匀速运动，当 C 与 B 重合时，B 即可收到该信息。

A,B,C 的移动速度都是 1 单位长度每秒，A 最晚在它到达终点时发出信息，B 最晚需要在它到达终点时收到信息。令 $t_A$ 代表发送信息的时间，$t_B$ 代表接收信息的时间，那么你需要最小化 $t_B-t_A$ 的值。特别地，如果 B 无论如何都无法收到信息，你需要输出 `impossible`。

输入格式：

第一行包含一个整数 $n$，代表 A 经过折线的点数；  
下面 $n$ 行，每行输入两个整数 $x_i,y_i$，依次描述 A 所走折线的点。  
下面一行包含一个整数 $m$，B 过折线的点数；  
下面 $m$ 行，每行输入两个整数 $u_i,v_i$，描述 B 所走折线。

输出格式：

一行，输出一个实数，代表答案。若无法满足，则输出`impossible`。


---

---
title: "[ICPC 2014 WF] Wire Crossing"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6903
tag: ['计算几何', '2014', '平面图', 'ICPC']
---
# [ICPC 2014 WF] Wire Crossing
## 题目描述

Moore’s Law states that the number of transistors on a chip will double every two years. Amazingly, this law has held true for over half a century. Whenever current technology no longer allowed more growth, researchers have come up with new manufacturing technologies to pack circuits even denser. In the near future, this might mean that chips are constructed in three dimensions instead two. But for this problem, two dimensions will be enough.

A problem common to all two-dimensional hardware design (for example chips, graphics cards, motherboards, and so on) is wire placement. Whenever wires are routed on the hardware, it is problematic if they have to cross each other. When a crossing occurs special gadgets have to be used to allow two electrical wires to pass over each other, and this makes manufacturing more expensive.

Our problem is the following: you are given a hardware design with several wires already in place (all of them straight line segments). You are also given the start and end points for a new wire connection to be added. You will have to determine the minimum number of existing wires that have to be crossed in order to connect the start and end points. This connection need not be a straight line. The only requirement is that it cannot cross at a point where two or more wires already meet or intersect.

  ![](https://vj.z180.cn/df2653f5a1b23d354dbe2e33d6438ea6?v=1602904232) 

   Figure 1: First sample input 

Figure 1 shows the first sample input. Eight existing wires form five squares. The start and end points of the new connection are in the leftmost and rightmost squares, respectively. The black dashed line shows that a direct connection would cross four wires, whereas the optimal solution crosses only two wires (the curved blue line).
## 输入格式

The input consists of a single test case. The first line contains five integers $m, x_0, y_0, x_1, y_1$, which are the number of pre-existing wires ($m \le 100$) and the start and end points that need to be connected. This is followed by $m$ lines, each containing four integers $x_ a, y_ a, x_ b, y_ b$ describing an existing wire of non-zero length from $(x_ a, y_ a)$ to $(x_ b,y_ b)$. The absolute value of each input coordinate is less than $10^5$. Each pair of wires has at most one point in common, that is, wires do not overlap. The start and end points for the new wire do not lie on a pre-existing wire.
## 输出格式

Display the minimum number of wires that have to be crossed to connect the start and end points.
## 样例

### 样例输入 #1
```
8 3 3 19 3
0 1 22 1
0 5 22 5
1 0 1 6
5 0 5 6
9 0 9 6
13 0 13 6
17 0 17 6
21 0 21 6

```
### 样例输出 #1
```
2

```
### 样例输入 #2
```
1 0 5 10 5
0 0 10 10

```
### 样例输出 #2
```
0

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

#### 题意简述
给定出发点，终止点和平面上的 $m$ 条线段，线段用两个端点表示，

求从出发点到终止点的连线(形状任意)最少要与线段相交多少次，多次经过一条线段要多次计数。

数据保证任意两条线段最多只有一个交点，注意连线不能经过交点，且线段可能是斜线。

坐标的绝对值不超过 $10^5$


---

---
title: "[W1] 推"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7101
tag: ['计算几何', 'O2优化', '组合数学']
---
# [W1] 推
## 题目背景

一个”点集“为一个二维平面上的整点组成的**多重**集合。  
可以从一个点集构造一个三角形当且仅当这个三角形的所有顶点在该点集里面。  
从一个点集 $S$ 里可以构造恰好 $|S|^3$ 个三角形。（可能一些三角形会退化为一条面积为 0 的线段）
## 题目描述

有一个点集，初始为空集。  
有 $N$ 个操作，在每一个操作，会从这个点集插入或删除一个点。每一步完成后，询问这个点集可构造的所有三角形面积 *__八次方__* 之和。

所有询问答案都可以表示为 $a/b$，其中 $a$ 和 $b$ 互质。输出 $a\cdot b^{-1}\pmod{998244353}$。
## 输入格式

第一行一个正整数 $N$，表示接下来的步骤个数。  
接下来 $N$ 行，每一行三个正整数 $t,x,y$。  
如果 $t=1$，则插入 $(x,y)$ 这个点；如果 $t=2$ 则删除 $(x,y)$ 这个点。
## 输出格式

一共 $N$ 行，第 $i$ 行一个正整数，表示第 $i$ 个步骤完成之后的询问答案。
## 样例

### 样例输入 #1
```
7
1 0 0
1 0 1
1 2 0
2 2 0
1 4 0
2 4 0
1 6 0
```
### 样例输出 #1
```
0
0
1
0
256
0
6561
```
### 样例输入 #2
```
5
1 0 0
1 0 1
1 1 0
1 1 1
2 0 1
```
### 样例输出 #2
```
0
0
994344961
982646785
994344961
```
## 提示

对于 $10\%$ 的数据，$N\le10$；  
对于 $30\%$ 的数据，$N\le10^3$；  
对于另外 $10\%$ 的数据，没有删除步骤；  
对于 $100\%$ 的数据，$1\le N\le10^5,0\le x,y<998244353$，任何删除的点都保证原来存在。


---

---
title: "[THUSC 2017] 宇宙广播"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7455
tag: ['计算几何', '2017', '提交答案', 'Special Judge', '高斯消元', 'THUSC']
---
# [THUSC 2017] 宇宙广播
## 题目描述

威摄纪元公元 2233 年，人类掌握了一项新的科技：基于量子力学原理，在地球表面上的宇宙广播能够超光速地将信号传播到这个点坐标所在的、与地球相切的平面中。

自从万有引力号广播了坐标之后，它带着人类文明的种子，远离太阳系飞向了宇宙深处。

DX3906 星系黑域纪元公元 3333 年，万有引力号找到了一个十分庞大的 X 星系，直径数光年，其中有 3 个适合人类居住的星球，分布在 X 星系不同的角落中。经过商讨之后，万有引力号的部分成员选择留在这三个星球上定居。

对于定居的人类而言，实时通讯是十分必要的，因此一千一百年前发明的那套装置在这时候就派上了用场。显然，三个星球能够互相通讯，当且仅当三个宇宙广播的工作切平面完全重合。

现在，星球球长阿米巴找到了善于编程的你，希望你能够通过编程计算得出所有能够建立宇宙广播的方案。

在你承担了这个任务之后，你在心里说了一句，「这算啥，我 ygg 分分钟搞定」，然而善于读心的阿米巴马上把你叫了回来，语重心长的跟你说，人类文明还要延续，把 $K$ 维空间的 $K$ 个星球的建站方案一起解决了。球长也没太为难你，只要你求 $K\le10$ 的情况，这是因为宇宙加上时间维之后是 $11$ 维的。

当你用 $3$ 分钟写完程序之后，阿米巴看了看，送给你一张二向箔——因为你没有在程序里考虑到这个情况。

给定坐标维数 $K\ge2$，以及在 $K$ 维坐标下的 $K$ 个球（**可退化成点**，即半径可以为零），求出这 $K$ 个球的**所有公切面**。

数据保证不会出现无解或无穷多组解的情况，但不保证所有球都是相离的。

以下是一些定义：

- 距离：在 $K$ 维空间中，设有两个点 $A(a_0,a_1,...,a_{K-1}),B(b_0,b_1,...,b_{K-1})$，则 $AB$ 之间的距离 $|AB|=\sqrt{\sum_{i=0}^{K-1}(a_i-b_i)^2}$；

- 球：在 $K$ 维空间中，与定点 $A$ 的距离为常数 $r$ 的点集，并同时称点 $A$ 为球心，$r$ 为该球半径；

  当 $K=2$ 时，即为大家在中学所熟知的圆。

- 超平面：到 $K$ 维空间中某两个点 $A,B$ 距离相等的点集；在 $K$ 维空间中，超平面的维数为 $K-1$；

	当 $K=2$ 时，即为大家在中学所熟知的直线（垂直平分线）。

- 球的切平面：一个超平面 $P$ 与球 $A$ 有且仅有一个交点；

- 球的公切面：一个超平面 $P$ 是所有球的切平面。
## 输入格式

这是一道提交答案题，共有8组输入数据，这些数据命名为 1.in ~ 8.in。

每个测试点中包含多组数据。对于每个测试点：

- 第一行：测试点包含的数据组数 $T$，保证 $T\le10$。
- 对于每组数据：
	- 第一行：坐标维数 $K$，保证 $2\le K\le10$。
	- 接下来 $K$ 行，每行 $K+1$ 个实数。第 $i$ 行的前 $K$ 个数代表第 $i$ 个球的球心所在的坐标，第 $K+1$ 个数代表第 $i$ 个球的半径。
## 输出格式

对于每组输入数据，你需要提交相应的输出文件 1.out ~ 8.out。

对于每个测试点的每组数据：

- 第一行，一个正整数  $S$，表示在这组数据中你总共找到了 $S$ 组切平面。如果没找到任何一组解，**请务必输出 $0$，否则将会影响后续数据的评分，造成的后果由选手自行承担**；
- 接下来 $S\times K$ 行，每行 $K$ 个小数，对于相对的第 $S(i-1)+j$ 行，表示在输出的第 $i$ 个解中，**对应输入**的第 $j$ 个球上的切点坐标；
- 最后一行，输出一个空行；

**在输出文件的最后，你可以添加任意内容，这不会影响你的得分。我们建议你在此处写一些有意义的内容（如简要方法），以便于我们在考后进行统计分析。单个输出文件大小不得超过 4M。**
## 样例

### 样例输入 #1
```
见附加文件中的 0.in
```
### 样例输出 #1
```
见附加文件中的 0.ans
```
## 提示

#### 评分标准
- 解的输出顺序没有要求。在一组解中，记输出答案为 $A(a_0,a_1,...,a_{K-1})$，如果存在一组标准答案 $B(b_0,b_1,...,b_{K-1})$，满足 $\sum_{i=0}^{K-1}|A_iB_i|^2\le10^{-12}$，那么这一组输出答案将会被判定为正确。
- 在每个测试点的同一组数据中，我们会统计被匹配上的标准答案的公切面的个数，每个标准答案只会被匹配至多一次，输出重复的公切面不倒扣分。第 $i$ 组数据回答正确的比例为被匹配上的标准答案的个数除以标准答案的总个数，记为 $rate_i$。
- 对于每个测试点的评分方式：
	1. 如果你的输出格式不合法，或者参数不符合题目约定，或者某一组的答案个数超过该组标准答案个数的两倍以上（不含两倍），则得0分；
      1. 在不违背上述条件的情况下，算对其中任何一组数据的任何一个解就至少有一分；并且所有的答案都算对了，才能得
      1. 在不违背上述条件的情况下，记共有 $T$ 组数据，$rate_i$ 为第 $i$ 组数据回答正确的比例，$score$ 为这个测试点的分值，则 $Yourscore=\frac{score}{T}\times\sum_{i=1}^T\sqrt{rate_i}$ 在不违背以上原则的情况下四舍五入输出，即 $Yourscore\in[1,score-1]$。
各测试点分值不同，具体如下表所示：

| 测试点 | $K\le$ | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $2$ | $5$ |
| 2 | $2$ | $15$ |
| 3 | $3$ | $11$ |
| 4 | $3$ | $14$ |
| 5 | $3$ | $16$ |
| 6 | $4$ | $7$ |
| 7 | $4$ | $9$ |
| 8 | $10$ | $23$ |



---

---
title: "[JSOI2016] 炸弹攻击1 - 数据加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8061
tag: ['计算几何', '2016', '各省省选', '江苏', 'Special Judge', '扫描线']
---
# [JSOI2016] 炸弹攻击1 - 数据加强版
## 题目背景

JYY 最近迷上了一款塔防游戏，在游戏里 JYY 除了建设建筑，还可以使用炸弹对屏幕上的敌人进行范围杀伤。
## 题目描述

游戏地图可以简单认为是一个二维平面。JYY 建造了 $N $ 个建筑，每个建筑都是一个圆，其中第 $i$ 个建筑的圆心位于 $(x_i,y_i)$ 且半径为 $r_i$。地图上一共有 $M$ 个敌人，一个敌人可以近似看成一个平面上的点，其中第 $i$ 个敌人位于 $(p_i,q_i)$。JYY 可以使用一枚可以设置半径的炸弹，可以设置一个不超过 $R$ 的范围，然后选择平面上的一个点引爆，范围内的所有敌人全部消灭。

当然，由于炸弹威力巨大，如果爆炸范围接触到 JYY 的建筑，那么 JYY 的建筑也会受到损伤。（注：如果炸弹的爆炸范围仅接触到了 JYY 建筑的边界，则不会对 JYY 的建筑造成损伤；如果敌人出现在了爆炸范围的边界，则该敌人被消灭）JYY 可以自由控制炸弹的爆炸地点和爆炸半径。作为一个保守的玩家，他希望在保证自己建筑毫发无损的情况下，消灭尽量多的敌人。
## 输入格式

第一行包含三个非负整数，分别为 $N,M,R$；

接下来 $N$ 行，每行三个整数，其中第 $i$ 行 $x_i,y_i,r_i$，表示第 $i$ 个建筑的位置和半径。数据保证所有建筑不相交（但是有可能边界接触）；

接下来 $M$ 行，每行两个整数，其中第 $i$ 行为 $p_i,q_i$，表示第 $i$ 个敌人的位置。任意两个敌人的位置不同，且敌人不会出现在建筑里。
## 输出格式

输出一行一个整数，表示 JYY 最多可以消灭的敌人数量。
## 样例

### 样例输入 #1
```
1 3 3
0 0 1
3 3
-3 3
3 -3
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
1 5 3
0 0 1
3 3
-3 3
3 -3
3 0
0 3
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
4 10 100
0 0 3
10 0 3
10 10 3
0 10 3
0 4
0 5
0 6
5 3
5 -3
5 5
6 7
3 6
10 4
8 4
```
### 样例输出 #3
```
5
```
## 提示

对于 $100\%$ 的数据，满足 $1\leq N\leq 10$，$1\leq M\leq 2000$，$1\leq R,r_i\leq 2\times 10^4$，$|p_i|,|q_i|,|x_i|,|y_i|\leq 2\times 10^4$。

数据来源于 NAIPC 2015 Problem A - Area of Effect，并有部分自造新数据。


---

---
title: "[THUPC 2023 初赛] 乱西星上的空战"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9141
tag: ['模拟', '计算几何', '2023', 'O2优化', 'THUPC']
---
# [THUPC 2023 初赛] 乱西星上的空战
## 题目背景

众所周知，在乱西星的现代战争中，制空权是很重要的。为此，人们发展出了无人机技术——遗憾的是，由于乱西星的算法水平和各种意义上的通讯水平实在太落后了，所以这些无人机只能采用各自独立的傻瓜式战斗模式，这些模式不含任何随机因素，因此一场傻瓜式无人机空战总是几乎能在开始前就被预测到结果。

总而言之，乱西星上正在相互战争的 |\\| 国和 () 国的傻瓜式无人机战斗机编队在其边境交界处的空域遭遇了，现在两国军方希望你能预测这一空战的结果。
## 题目描述

### 空域与时刻

由于乱西星的神秘物理法则，乱西星的时间和空间并不是连续的；若认为遭遇战开始的时刻是第 $1$ 时刻，那么对于任意的第 $k\in \N$ 个时刻，在这一时刻开始和结束时，一个物体（无人机或导弹）只能在形如 $(x,y,z)\in\mathbb Z^3$ 的位置（即空域内的整点）上。

### 无人机

由于空域相比无人机要大得多，因此我们可以将无人机视为一个质点（尽管他们实际上长得和地球上的一般意义上的飞机十分相似）。

#### 飞行状态

在每个时刻，一架无人机的飞行状态可以用以下三组参数描述：

1. 当前时刻所在的坐标 $\vec p=(x,y,z)\in\mathbb Z^3$；
2. 当前时刻的飞行方向向量 $\vec{d},\|\vec d\|=1$；
   - 其中， $\|\vec{v}\|$ 表示向量 $\vec v$ 的长度：设 $\vec{v}=(v_x,v_y,v_z)$，则 $\|\vec{v}\|=\sqrt{v_x^2+v_y^2+v_z^2}$。
   - 你可以简单地将 $\vec d$ 理解为机头指向的方向。
3. 当前时刻的无人机升力线方向 $\vec u,\|\vec u\|=1,\vec u\bot \vec d$；
   - 你可以简单的将 $\vec u$ 理解为飞机所在平面的、从机腹指向机背的单位法向量。
   - 此时，$\vec d$ 和 $\vec u$ 可以唯一确定一个“左手向” $\vec l=\vec u\times \vec d$。

#### 飞行性能

不严格地讲，一般而言，一架飞机通常有三个操作轴，即俯仰、滚转和偏航：俯(负杆)和仰(正杆)分别对应飞机机头向下和向上（即保持 $\vec l$ 不变）；滚转即飞机以飞行方向为中轴线旋转（即保持 $\vec d$ 不变）；偏航则为飞机机头向左或者向右（即保持 $\vec u$ 不变）。由于无人机的特殊设计，其**没有偏航**轴，只能进行俯仰和滚转——容易看出，即使仅进行俯仰和滚转，一架无人机也能随意地改变 $\vec d$ 和 $\vec u$ （在保持 $\|\vec u\|=\|\vec d\|=1,\vec u\bot \vec d$ 的前提下）。

以上的俯仰(正杆或负杆)、滚转操作，以及直线飞行，及其复合统称“机动”。

由于无人机型号差异，一架无人机的飞行性能可以用以下三组参数描述（为方便起见，在本节中，对进行一次机动前的飞行状态对应参数为 $\vec p=(x,y,z),\vec d,\vec u,\vec l$，进行一次机动后的飞行状态对应的参数为 $\vec p'=(x',y',z'),\vec d',\vec u',\vec l'$）：

1. 正杆率 $\theta_u\in(\dfrac\pi4,\dfrac\pi2)$ 和负杆率 $\theta_d\in(\dfrac\pi4,\dfrac \pi2)$；
   - 若无人机**仅进行正杆**机动，则必须有 $\vec p=\vec p',\vec l=\vec l',\vec u\cdot \vec d'\ge 0$；此时，进行一次这样的机动花费的时间是 $\dfrac{\angle(\vec d,\vec d')}{\theta_u}$。
   - 若无人机**仅进行负杆**机动，则必须有 $\vec p=\vec p',\vec l=\vec l',\vec u\cdot \vec d'\le 0$；此时，进行一次这样的机动花费的时间是 $\dfrac{\angle(\vec d,\vec d')}{\theta_d}$。
2. 滚转率 $\gamma\in(\dfrac\pi4,\dfrac \pi 2)$；
   - 若无人机**仅进行滚转**机动，则必须有 $\vec p=\vec p',\vec d=\vec d'$；此时，进行一次这样的机动花费的时间是 $\dfrac{\angle(\vec u,\vec u')}{\gamma}$。
3. 飞行极速 $v_{m}>0$；
   - 若无人机**仅进行直线飞行**，则必须有 $\vec d=\vec d',\vec u=\vec u'$；此时，花费的时间是 $\dfrac{\|\vec p'-\vec p\|}{v_m}$。

#### 合法位移

在每个时刻，若一架无人机可以从 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 这一飞行状态，严格按照**滚转**、**俯仰**(正杆或负杆)和**直线飞行**的顺序进行机动，使飞行状态变为 $\vec p'=(x',y',z')\not=\vec p,\vec d',\vec u',\vec l'$，满足 $\vec d'//(\vec p'-\vec p)$，并且各机动花费的时间之和不超过 $1$，则称这是一次(无人机的)合法的综合机动。

如果一架无人机可以从 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 通过一次合法的综合机动，使飞行状态变为 $\vec p'=(x',y',z')\not=\vec p,\vec d',\vec u',\vec l'$，并且在所有使飞行状态变为 $\vec p''=\vec p',\vec d'',\vec u'',\vec l''$ 的合法综合机动中，总用时是最短的，则称之为一次（无人机的）合法位移（或称该位移合法）。此时，无人机会沿直线从 $\vec p$ 移动到 $\vec p'$。如无特殊指明，下文中“位移”均默认(应当为)合法位移。

#### 眼镜蛇机动

在每个时刻，无论无人机飞行性能如何，无人机总是可以通过眼镜蛇机动，从 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 这一飞行状态，变为 $\vec p'=\vec p,\vec d'=\vec u,\vec u'=-\vec d,\vec l'=\vec l$ 这一飞行状态。注意，这种机动不被视为合法机动。

#### 其它参数

除此之外，一架无人机还具有以下参数：

1. 无人机编号（简称“编号”）；
   - 保证任意两架无人机编号不同。
2. 所在阵营（简称“阵营”）；
   - 所在阵营必须是|\\| 国或者是 () 国中之一，并且双方互称敌方阵营。

#### 坠毁

一架无人机坠毁，当且仅当其符合下列条件之一：

1. 在某激活的导弹位移过程中，与该导弹的距离不大于导弹的空爆距离（详见下文）。
2. 在某导弹位移结束后，与该导弹位置重合（从而导弹直接命中无人机导致坠毁，下同）。
3. 在无人机位移过程中，存在至少一枚激活的导弹，与其距离不大于该导弹的空爆距离。
4. 在无人机位移结束后，存在至少一枚导弹所在位置与其位置重合。
5. 在无人机位移结束后，存在另一架无人机与其坐标相同（从而发生碰撞导致双双坠毁）。

无人机坠毁后将立即消失，此后不会发射导弹，也不会导致其它无人机坠毁。但无人机已经发射的导弹不会立刻消失或爆炸。

此时也称无人机被摧毁。

### 空空红外制导导弹

类似的，一枚空空红外制导导弹（下文简称“导弹”）也可视为一质点，并且同样可以描述其飞行状态和飞行性能。

#### 飞行状态

由于导弹无所谓上下左右，因此仅需要以下两组参数以描述一个导弹的飞行状态：

1. 当前时刻所在的坐标 $\vec p=(x,y,z)\in\Z^3$；
2. 当前时刻的飞行方向向量 $\vec{d},\|\vec d\|=1$；
   - 你可以简单地将 $\vec d$ 理解为导弹弹头指向的方向。

#### 飞行性能

同样由于一枚导弹无所谓上下左右，因此其不存在俯仰、滚转和偏航轴，其向各个方向改变 $\vec d$ 的性能是相同的，此时统称仅改变 $\vec d$ 的操作为 "偏航"。其与直线飞行及复合统称“机动”。

因此一枚导弹的飞行性能可以用以下两组参数描述（为方便起见，在本节中，对进行一次机动前的飞行状态对应参数为 $\vec p=(x,y,z),\vec d$，进行一次机动后的飞行状态对应的参数为 $\vec p'=(x',y',z'),\vec d'$）：

1. 偏航率 $\theta_r\in(\dfrac\pi4,\dfrac\pi2)$；
   - 若导弹**仅进行偏航**机动，则必须有 $\vec p=\vec p'$；此时，进行一次这样的机动花费的时间是 $\dfrac{\angle(\vec d,\vec d')}{\theta_r}$；
2. 飞行极速 $v_m>0$；
   - 若导弹**仅进行直线飞行**，则必须有 $\vec d=\vec d'$；此时，花费的时间是 $\dfrac{\|\vec p'-\vec p\|}{v_m}$。

#### 合法位移

在每个时刻，若一枚导弹可以从 $\vec p=(x,y,z),\vec d$ 这一飞行状态，严格按照**偏航**和**直线飞行**的顺序进行机动，使飞行状态变为 $\vec p'=(x',y',z')\not=\vec p,\vec d'$，满足 $\vec d//(\vec p'-\vec p)$，并且各机动花费的时间之和不超过 $1$，则称这是一次(导弹的)合法位移（或称该位移合法）。此时，导弹会沿直线从 $\vec p$ 移动到 $\vec p'$。如无特殊指明，下文中“位移”均（应当）默认为合法位移。

#### 其它参数

除此之外，一枚导弹还具有以下参数：

1. 保险距离 $d_s>0$ 和激活状态；
   - 导弹被发射后立即处于未激活状态。
   - 每个时刻结束时，若导弹处于未激活状态，并且发射该导弹的无人机已坠毁，或者与发射该导弹的无人机的距离大于保险距离 $d_s$ 时，进入激活状态。此后将保持激活状态，并称该导弹被激活，或称其为一枚激活的导弹。
2. 空爆距离 $d_p>0$；
   - 每次导弹位移过程中，当一枚激活的导弹与任一无人机（包括发射该导弹的无人机）距离不大于 $d_p$ 时，该导弹会进入可空爆状态（详见下文“可空爆”）。
   - 每次无人机位移过程中，若存在一无人机与一枚激活的导弹距离不大于 $d_p$ 时，该导弹也会进入可空爆状态。
3. 最大锁定角 $\beta_s\in(\dfrac\pi4,\dfrac\pi2)$；
   - 任意时刻，一枚飞行状态为 $\vec p=(x,y,z),\vec d$、最大锁定角的导弹能锁定到 $\vec p'$ 处的无人机，当且仅当 $\vec d\cdot(\vec p'-\vec p)>0$，并且 $\angle(\vec d,\vec p'-\vec p)\le \beta_s$。
   - 此时称该无人机能被该导弹锁定，或称其在导弹的锁定范围内。
   - 称 $\angle(\vec d,\vec p'-\vec p)$ 为锁定角。
4. 制导时长 $t_z>0$；
   - 若导弹在第 $k$ 个时刻被发射，则到第 $k+t_z$ 个时刻结束时，若导弹仍未爆炸，则导弹会立刻消失（见“爆炸、消失与可空爆”）。此时称导弹超过制导时长。

#### 爆炸、消失与可空爆

一枚导弹在符合下列全部条件时，会立刻爆炸并消失：

1. 在导弹位移开始前，导弹处于激活状态；

2. 符合以下条件之一：
   
   1. 在该导弹位移过程中，存在一架位于 $\vec q$ 的无人机，使 $\min_{\lambda\in[0,1]}\|\lambda \vec p+(1-\lambda)\vec p'-\vec q\|\le d_p$，其中  $\vec p,\vec p'$ 为导弹本次位移的起点和终点。
      
      - 此时，所有这样的无人机都会被该导弹摧毁。同时，一架无人机可能同时被若干枚导弹摧毁。
   
   2. 在无人机位移过程中，存在一架无人机，记其从位置 $\vec q$ 位移到 $\vec q'$ ，满足 $\min_{\lambda\in[0,1]}\|\lambda \vec q+(1-\lambda)\vec q'-\vec p\|\le d_p$，其中 $\vec p$ 为导弹此时的位置。
      
      - 此时，所有这样的无人机都会被该导弹摧毁。同时，该导弹也可能同时摧毁若干这样的无人机。

此时，称该导弹可空爆，或该导弹进入可空爆状态。

一枚导弹在符合下列条件之一时，不会发生爆炸，但是会在当前时刻结束时消失：

1. 导弹脱锁（见下文“导弹脱锁”），并且在当前时刻开始时已被激活；

2. 导弹超过制导时长；

3. 导弹未激活，并且导弹位移结束后与一无人机位置重合；
   
   - 此时，该无人机会被这枚导弹摧毁。同时，一架无人机可能同时被若干枚导弹摧毁。

4. 导弹未激活，无人机位移结束后，该导弹与一无人机位置重合。
   
   - 此时，该无人机会被这枚导弹摧毁。同时，一枚导弹可能同时摧毁若干这样的无人机。

### 无人机视野、雷达搜索与导弹锁定

#### 无人机视野

任意时刻，一架飞行状态为 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 的无人机能够发现一架位于 $\vec p'=(x',y',z')$ 的无人机，当且仅当 $\vec d\cdot(\vec p'-\vec p)> 0$；此时称 $\vec p'$ 处的无人机在 $\vec p$ 处无人机的视野内。

#### 无人机机载雷达搜索范围

一架无人机的机载雷达（下文简称“雷达”）的扫描范围可以用以下两个参数描述：

1. 水平扫描范围 $L_x\in\N^+$ 和垂直扫描范围 $H_y\in\N^+$；
   - 任意时刻，一架飞行状态为 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 、雷达扫描范围为 $L_x,H_y$ 的无人机的能够扫描到一架位于 $\vec p'$ 的无人机，当且仅当，$\vec d\cdot(\vec p'-\vec p)>0$ 并且 $\exist x,y,s.t.\ |x|\le L_x,|y|\le H_y$ 且 $[\vec p'-(\vec p+x\vec l+y\vec u)]//\vec d$。
   - 即若以 $\vec p$ 为原点、以 $\vec l$ 和 $\vec u$ 为 $X,Y$ 轴建一平面 $\alpha=\alpha(\vec p;\vec l,\vec u)$，则  $\vec p'$ 在这一平面上的投影 $\vec r=P(\vec p';\alpha)$ 应当落在 $[-L_x,L_x]\times [-H_y,H_y]$ 中。
   - 此时称 $\vec p'$ 处的无人机在 $\vec p$ 处无人机雷达扫描范围内。

#### 导弹脱锁

当无人机位移结束后，若一枚导弹选定的目标已坠毁，或其不能被该导弹锁定，则称该导弹脱锁，或处于脱锁状态。

此后将一直保持脱锁状态，无论是否此前选定的无人机是否重新可以被导弹锁定。

### 无人机选定目标策略

任意时刻，无人机（简称"本机"，下同）按下述策略选择目标无人机。

1. 若本机视野内无敌方阵营无人机（简称“敌机”，下同），则本机无选定目标；
2. 否则，若上一时刻本机选择的无人机仍位于本机视野内，则本机仍选定该目标；
3. 否则，若存在至少一架敌机处于本机雷达扫描范围内，则选取其中与本机距离最近的；若与本机距离最近的敌机不唯一，则选取编号最小的。
4. 否则，对视野内的处于 $\vec p'$ 的敌机，记 $\alpha=\alpha(\vec p;\vec l,\vec u),\vec r=P(\vec p';\alpha)=(r_x,r_y)$，则选取 $\min\{|r_x-L_x|,|r_x+L_x|\}+\min\{|r_y-H_y|,|r_y+H_y|\}$ 最小的。若有多个最小值，则同样选择编号最小的。

### 飞行策略

#### 无人机飞行策略

设无人机飞行状态是 $\vec p=(x,y,z),\vec d,\vec u,\vec l$，其飞行极速为 $v_m$，机载雷达扫描范围为 $L_x,H_y$。

1. 若无人机有位于 $\vec p'$ 的选定目标：
   1. 若无人机能够合法地位移到某个位置，使敌机现在的位置 $\vec p'$ 仍处于本机的视野内，则无人机会合法地移动到飞行状态 $\vec q=(x_q,y_q,z_q),\vec d_q,\vec u_q,\vec l_q$，使敌机现在的位置 $\vec p'$ 仍处于本机视野内，且 $\|\vec p'-\vec q\|$ 最小。
      1. 若有多个这样的位置，记 $\alpha_q=\alpha(\vec q;\vec l_q,\vec u_q),\vec r_q=P(\vec p';\alpha_q)=(r_{qx},r_{qy})$，则优先选取使 $\vec r_q=(r_{qx},r_{qy})\in[-L_x,L_x]\times [-H_y,H_y]$ 的位置；
         1. 若仍有多个这样的位置，则选取使 $\|\vec r_q\|=\sqrt{r_{qx}^2+r_{qy}^2}$ 最小的；
         2. 若仍有多个这样的位置，则选取 $\vec q$ 字典序最小的。
      2. 若不存在这样的 $\vec r_q$，则选取使 $\min\{|r_{qx}-L_x|,|r_{qx}+L_x|\}+\min\{|r_{qy}-H_y|,|r_{qy}+H_y|\}$ 最小的；
         1. 若仍有多个这样的位置，则选取 $\vec q$ 字典序最小的。
   2. 否则，无人机会合法地移动到某个位置 $\vec q$，使 $\|\vec q-\vec p-v_m\vec d\|$ 最小；
      1. 若有多个这样的位置，则选取 $\vec q$ 字典序最小的。
2. 否则，无人机通过眼镜蛇机动，将飞行状态变为 $\vec p=(x,y,z),\vec u,-\vec d,\vec l$。

保证在上述1.的情况下，无人机总能合法地移动到某个位置。

#### 导弹飞行策略

设导弹当前时刻飞行状态 $\vec p,\vec d$，其选定的敌机飞行状态为 $\vec p',\vec d',\vec u',\vec l'$；

若上一时刻结束时，导弹未脱锁，则记 $\vec q'$ 为敌机根据其飞行策略，下一时刻会移动到的位置。

若导弹能合法位移到 $\vec q'$，则导弹会直接位移到 $\vec q'$。

否则，导弹会合法地位移到能使敌机位移后的位置 $\vec q'$ 处于锁定范围内的位置 $\vec q$ ，且 $\|\vec q-\vec q'\|$ 最小。

1. 若有多个这样的 $\vec q$，则选取位移后锁定角最小的；
2. 若仍有多种可能，则选取 $\vec q$ 字典序最小的。

若不存在这样的位置，或者上个时刻结束时，导弹已经脱锁，则导弹会合法地位移到某个位置 $\vec q$，使 $\|\vec q-\vec p-v_m\vec d\|$ 最小。

保证导弹总能合法地移动到某个位置。

### 无人机发射导弹规则

一飞行状态为 $\vec p=(x,y,z),\vec d,\vec u,\vec l$ 的无人机（简称"本机"）向**被本机选定**的、处于 $\vec p'$ 的目标无人机（简称“敌机”）发射导弹的规则为：

在每个时刻开始时，若选定的敌机已处于本机雷达扫描范围内，且当前不存在由本机发射且未爆炸（或消失）的导弹，则向敌机发射一初始飞行状态为 $\vec p,\vec d=\dfrac{\vec p'-\vec p}{\|\vec p'-\vec p\|}$ 的未激活的导弹，该导弹选定敌机。

### 同一时刻内各事件发生顺序

1. 所有无人机选定目标，并确定当前时刻内的飞行策略；
2. 所有能发射导弹的无人机发射导弹；
3. 所有导弹确定飞行策略并位移，该过程中部分无人机可能被摧毁；
4. 所有可空爆的导弹爆炸并消失；
5. 所有无人机按 1. 中确定的飞行策略位移，该过程中部分无人机可能被摧毁；
6. 所有可空爆的导弹爆炸并消失；
7. 所有位置相同的无人机发生碰撞并坠毁。
8. 所有超过制导时长和脱锁且已激活的导弹消失。
9. 所有可激活的导弹被激活。

### 任务

给定空域开始时（即第 $1$ 时刻开始时），各无人机的飞行性能与状态、导弹的飞行性能，假定这场空战会持续 $T$ 个时刻，双方指挥官希望你能按时间顺序依次给出每个时刻发生的所有重要事件。
## 输入格式

第一行两个正整数 $n,T$ ，表示共有 $2n$ 架无人机，模拟前 $T$ 个时刻。其中，前 $n$ 架阵营是 |\\| 国，后 $n$ 架阵营是 () 国。

接下来有 $2n$ 组数据，每一组包含若干行，其中第 $i$ 组描述了编号为 $i$ 的无人机。

在每组数据中：

第一行三个整数表示 $\vec p\in\mathbb Z^3$；保证所有的 $\vec p$ 两两不同，且坐标的绝对值不超过 $100$。

第二行六个整数依次表示无人机的 $\vec d,\vec u$，保证 $\vec d,\vec u\in S_v$；

- 其中， $S_v=\{(1,0,0),(-1,0,0),(0,1,0),(0,-1,0),(0,0,1),(0,0,-1)\}$；

第三行六个实数依次表示无人机的 $\theta_u,\theta_d,\gamma,v_m,L_x,H_y$；

第四行五个实数和一个正整数依次表示导弹的 $\theta_r,v_m,d_s,d_p,\beta_s,t_z$。
## 输出格式

输出 $T$ 组数据，第 $i$ 组数据表示第 $i$ 个时刻发生的重要事件。

在每组数据中：

第一行三个非负整数 $p_1,p_2,p_3$ ，表示在这个时刻的导弹位移过程中被摧毁的无人机数量、在这个时刻的无人机位移过程中被摧毁的无人机数量、这个时刻结束时，有多少组无人机因位置相同而两两碰撞坠毁。

接下来 $p_1$ 行，每行形如 $id_0\ k\ id_1\ id_2\ \cdots\ id_k$，表示编号为 $id_0$ 的无人机在这个时刻的导弹位移过程中被摧毁，并且在该过程中摧毁该无人机的导弹共有 $k$ 枚，分别来自编号为 $id_1,id_2,\cdots,id_k$ 的无人机。

为保证输出唯一，这 $p_1$ 行中的每一行内，$id_1,\dots,id_k$ 应当从小到大输出，行之间按 $id_0$ 从小到大输出。

接下来 $p_2$ 行，每行形如 $id_0\ k\ id_1\ id_2\ \cdots\ id_k$，表示编号为 $id_0$ 的无人机在这个时刻的无人机位移过程中被摧毁，并且在该过程中摧毁该无人机的导弹共有 $k$ 枚，分别来自编号为 $id_1,id_2,\cdots,id_k$ 的无人机。

为保证输出唯一，这 $p_2$ 行中的每一行内，$id_1,\dots,id_k$ 应当从小到大输出，行之间按 $id_0$ 从小到大输出。

接下来 $p_3$ 行，每行形如 $k\ id_1\ id_2\ \dots id_k$，表示该时刻结束时，有 $k$ 架无人机位置相同 ，它们的编号是 $id_1,...,id_n$。

为保证输出唯一，这 $p_3$ 行中的每一行内，$id_1,\dots,id_k$ 应当从小到大输出，行之间按 $id_1$ 从小到大输出，并且每个编号出现至多一次。
## 样例

### 样例输入 #1
```
1 1
0 0 0
1 0 0 0 0 1
1 1 1 4 1 1
1 3 1 1 1 1
8 0 0
-1 0 0 0 0 1
1 1 1 4 1 1
1 3 1 1 1 1

```
### 样例输出 #1
```
0 0 1
2 1 2

```
### 样例输入 #2
```
1 4
0 0 0
1 0 0 0 0 1
1 1 1 3 1 1
1 15 3 2 1 10
60 0 0
-1 0 0 0 0 1
1 1 1 3 1 1
1 15 3 2 1 10

```
### 样例输出 #2
```
0 0 0
0 0 0
0 0 0
0 2 0
1 1 2
2 1 1

```
## 提示

#### 样例解释 1

在第 $1$ 时刻，两架飞机于 $(4,0,0)$ 处相撞。

#### 样例解释 2

在第 $4$ 时刻，两枚导弹分别摧毁了敌机。

#### 数据范围

$T,n\le 100,3\le v_m\le 20$；

$v_m>10$ 的无人机和导弹总数不超过 $10$；

$\theta_u,\theta_d,\gamma,\theta_r,\beta_s\in(\dfrac\pi4,\dfrac\pi2)$；

$1\le d_s,d_p\le 20,1\le t_z\le 100$；

$|x|,|y|,|z|\le 100$；

$1\le L_x,H_y\le 100$。

所有输入的实数精确到小数点后不超过 $6$ 位。

最初时，$\vec p$ 两两不同。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。


---

---
title: "三色"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9685
tag: ['计算几何', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 三色
## 题目背景

我的心脏还在跳动着啊。
## 题目描述

给定 $n$ 个三元组 $(a_i,b_i,c_i)$。$q$ 次询问，每次给定一个集合 $S$，查询是否存在实数三元组 $(p,q,r)$ 满足：对于所有满足 $pa_i+qb_i+r>0$ 的 $i$，其 $c_i$ 构成的集合恰好为 $S$。
## 输入格式

第一行输入一个整数 $T$，代表数据组数。

对于每组数据，第一行输入三个数 $n,q,k$，其中 $k=|S|$。

接下来 $n$ 行，每行输入三个整数 $a_i,b_i,c_i$。

接下来 $q$ 行，第 $i$ 行输入 $k$ 个整数 $s_{i,1},s_{i,2},\dots,s_{i,k}$，代表第 $i$ 组询问中 $S$ 的元素。保证元素不重复。
## 输出格式

对于每组数据，输出一行一个长为 $q$ 的字符串 $R$，对于第 $i$ 组询问，若答案为存在，则 $R_i$ 为 $\tt 1$，否则为 $\tt 0$。
## 样例

### 样例输入 #1
```
3
5 2 1
3 0 1
-2 2 2
1 -3 3
-2 -1 4
0 0 5
2
5
5 4 2
3 0 1
-2 2 2
1 -3 3
-2 -1 4
0 0 5
2 3
2 4
5 1
3 5
5 6 3
3 0 1
-2 2 2
1 -3 3
-2 -1 4
0 0 5
3 5 4
2 5 3
4 2 1
2 4 3
3 1 2
3 1 4
```
### 样例输出 #1
```
10
0110
100101
```
## 提示

### 数据规模与约定

对于所有数据，$1\le n,\sum n\le 10^5$，$1\le q,\sum q \le 3\times 10^5$，$1\le k\le 3$，$1\le c_i,s_{i,j}\le n$，$|a_i|,|b_i|\le 10^9$。

对于任意 $i\neq j$，保证 $(a_i,b_i)\neq (a_j,b_j)$，且不存在 $(p,q)$ 和三个不同的下标 $i,j,k$ 满足 $pa_i+qb_i=pa_j+qb_j=pa_k+qb_k$。

### 子任务

| # | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: |
| 0 | 样例 | 0 |
| 1 | $n\le 3$ | 2 |
| 2 | $k=1$ | 11 |
| 3 | $\sum n^2\le 10^6$ | 23 |
| 4 | $k=2$ | 29 |
| 5 | $k=3$ | 35 |


---

---
title: "[ICPC 2020 Shanghai R] Wowoear"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9819
tag: ['计算几何', '2020', '上海', 'Special Judge', 'O2优化', '线段相交', 'ICPC']
---
# [ICPC 2020 Shanghai R] Wowoear
## 题目描述

Wowo is a solo adventurer who completed many dangerous journeys on his own foot in forests, deserts and even glaciers. The Shanghai ICPC (Shanghai Invitational Contest on Programmable Cheating) committee invited Wowo as a tester of their new running trial.

The trial can be described as a 2D simple polyline $(p_1,\ldots, p_n)$. In other words, the trial consists of $n-1$ line segments $(p_1, p_2),\ldots, (p_{n-1}, p_n)$. The line segments do not intersect with each other except that two consecutive line segments $(p_i, p_{i+1})$ and $(p_{i+1}, p_{i+2})$ intersect at the point $p_{i+1}$. Any two consecutive segments have different directions. The committee wants Wowo to run from $p_1$ to $p_n$ along the line segments $(p_1,p_2),\ldots, (p_{n-1}, p_n)$ in order.

However, Wowo has a smart device that can hack the committee's system for an interval of time. Wowo is able to choose $2$ points $a, b$ on the trial and run directly from $a$ to $b$ along the line segment $(a, b)$. Each of these $a$ and $b$ can be some $p_i$ ($1\le i\le n$) and can be some point on some line segment $(p_i, p_{i+1})$ ($1\le i<n$) as well. Before reaching $a$ and after reaching $b$, Wowo has to run along the original trial. Wowo does not want to be caught cheating, so he decided that the line segment $(a, b)$ should not intersect or touch any line segment of the trial at any point other than $a$ and $b$. Help Wowo to choose $a$ and $b$ wisely and output the shortest distance Wowo need to run from $p_1$ to $p_n$ using his smart cheating device.
## 输入格式

The first line includes a single integer $n$ indicating the number of points on the running trial ($2\le n\le 200$).

The $i+1$-th line ($1\le i\le n$) contains two integers $x$ and $y$ separated by a single space indicating the coordinates of $p_i$ ($-1000\le x, y\le 1000$).

It is guaranteed that the line segments do not intersect with each other except that two consecutive line segments $(p_i, p_{i+1})$ and $(p_{i+1}, p_{i+2})$ intersect at the point $p_{i+1}$. In other words, $(p_i, p_{i+1})\cap (p_{j}, p_{j+1})=\left\{\begin{array}{cc}\emptyset & i\neq j-1\\ \{p_{j}\} & i = j-1\end{array}\right.$ holds for any integers $i, j$ satisfying $1\le i< j<n$. Here $(s, t)$ represents all points on the line segment from $s$ to $t$ including $s$ and $t$.

It is guaranteed that each line segment has nonzero length. In other words, $p_i\neq p_{i+1}$ for any integer $i\in [1, n)$.

It is guaranteed that adjacent line segments are not collinear. In other words, for any integer $i\in [1,n-2]$ and any real number $\lambda$, $p_i - p_{i+1}$ is $\textbf{not}$ equal to $\lambda(p_{i+1}-p_{i+2})$.
## 输出格式

Output the shortest distance Wowo needs to run. Your answer will be considered correct if its absolute or relative error does not exceed $10^{-6}$.
## 样例

### 样例输入 #1
```
5
0 0
1 10
2 0
3 10
4 0
```
### 样例输出 #1
```
22.099751242242
```
## 题目翻译

### 题目描述
Wowo 是一位单人冒险家，他曾独自一人在森林、沙漠甚至冰川中完成过许多危险的旅程。ICPC（上海市可编程作弊邀请赛）组委会邀请 Wowo 作为新的跑步测试员。

该试验可描述为二维简单折线 $(p_1,\ldots, p_n)$。换句话说，试验由 $n-1$ 条线段 $(p_1, p_2),\ldots, (p_{n-1}, p_n)$ 组成。除了两个连续的线段 $(p_i, p_{i+1})$ 和 $(p_{i+1}, p_{i+2})$ 相交于点 $p_{i+1}$ 外，其他线段互不相交。任何两条连续的线段都有不同的方向。委员会希望 Wowo 从 $p_1$ 到 $p_n$ 依次沿着线段 $(p_1,p_2),\ldots, (p_{n-1}, p_n)$ 运行。

然而，Wowo 拥有一个智能设备，可以在一段时间内侵入委员会的系统。Wowo 能够在试验中选择 $2$ 点 $a, b$ ，并沿着线段 $(a, b)$ 直接从 $a$ 跑到 $b$ 。其中每个 $a$ 和 $b$ 都可以是某个 $p_i$ （$1\le i\le n$）。($1\le i\le n$) ，也可以是线段 $(p_i, p_{i+1})$ 上的某一点。($1\le i \le n$)上的某一点。在到达 $a$ 之前和 $b$ 之后，Wowo 必须沿着原来的试验路线运行。沃沃不想被发现作弊，所以他决定线段 $(a, b)$ 不能与试验中的任何线段相交，也不能接触到 $a$ 和 $b$ 以外的任何点。请帮助 Wowo 明智地选择 $a$ 和 $b$ ，并利用他的智能作弊装置输出 Wowo 需要从 $p_1$ 跑到 $p_n$ 的最短距离
### 输入格式

第一行包含一个整数 $n$ ，表示运行试验中的点数（ $2\le n\le 200$ ）。

第 $i+1$（$1\le i\le n$）行包含两个整数 $x$ 和 $y$，中间用一个空格隔开，表示 $p_i$（$-1000\le x, y\le 1000$）的坐标。

除了两条连续的线段 $(p_i, p_{i+1})$ 和 $(p_{i+1}, p_{i+2})$ 相交于点 $p_{i+1}$ 之外，其他线段保证互不相交。换句话说，对于满足 $1 \le i\lt j \lt n$ 的任何整数 $i, j$，$(p_i, p_{i+1})\cap (p_{j}, p_{j+1})=\left\{\begin{array}{cc}\emptyset & i\neq j-1\\ \{p_{j}\} & i = j-1\end{array}\right.$ 都成立。这里的 $(s, t)$ 代表从 $s$ 到 $t$ 的线段上的所有点，包括 $s$ 和 $t$。
可以保证每条线段的长度都不为零。换句话说，$p_i\neq p_{i+1}$ 满足任意整数 $i\in [1, n)$。

保证相邻线段不相交。换句话说，对于任意整数 $i\in [1,n-2]$ 和任意实数 $\lambda$，$p_i - p_{i+1}$ 不**等于**$\lambda(p_{i+1}-p_{i+2})$。
### 输出格式
输出 Wowo 需要运行的最短距离。如果答案的绝对误差或相对误差不超过 $10^{-6}$，则认为答案正确。  
Translation by [nightwatch_ryan](/user/961351)


---

---
title: "[ICPC 2021 Nanjing R] Paimon Polygon"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9845
tag: ['计算几何', '2021', 'Special Judge', 'O2优化', '凸包', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Paimon Polygon
## 题目描述

Paimon just puts $(n+1)$ distinct points on the plane, one of which is a special point $O=(0,0)$, and denote the group of remaining points as $\mathbb{S}$.

We call a point set $\mathbb{U}$ $\textit{strict convex set}$, if and only if $|\mathbb{U}| \ge 3$ and all the points from $\mathbb{U}$ lie exactly on the convex hull built from $\mathbb{U}$, with no three points lying on the same line.

You should divide $\mathbb{S}$ into two sets $\mathbb{A}$ and $\mathbb{B}$ so that:
- $\mathbb{A} \cap \mathbb{B}=\emptyset$.
- $\mathbb{A} \cup \mathbb{B}=\mathbb{S}$.
- $|\mathbb{A}| \ge 2, |\mathbb{B}| \ge 2$.
- The point set $\mathbb{A} \cup \{O\}$ is a $\textit{strict convex set}$, and denote its convex hull as $C_{\mathbb{A} \cup \{O\}}$.
- The point set $\mathbb{B} \cup \{O\}$ is a $\textit{strict convex set}$, and denote its convex hull as $C_{\mathbb{B} \cup \{O\}}$.
- The outlines(edges) of $C_{\mathbb{A} \cup \{O\}}$ and $C_{\mathbb{B} \cup \{O\}}$ only intersect at point $O$. That is, only one point $O$ satisfies that it lies both on the outlines of $C_{\mathbb{A} \cup \{O\}}$ and $C_{\mathbb{B} \cup \{O\}}$.

Please help Paimon to maximize the sum of the perimeters of these two convex hulls. That is, find a valid division $\mathbb{A}$ and $\mathbb{B}$ which maximizes $(L(C_{\mathbb{A} \cup \{O\}}) + L(C_{\mathbb{B} \cup \{O\}}))$, where $L(\text{polygon})$ means the perimeter of that polygon.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains one integer $n$ ($4 \le n \le 5 \times 10^5$) indicating the number of points in $\mathbb{S}$.

For the following $n$ lines, the $i$-th line contains two integers $x_i$ and $y_i$ ($-10^9 \le x_i, y_i \le 10^9$, $(x_i, y_i) \ne (0, 0)$) indicating the location of the $i$-th point in $\mathbb{S}$.

It's guaranteed that the points given in the same test case are pairwise different. However, there may be three points lying on the same line.

It's also guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing a number indicating the maximum total perimeter. If there does not exist a valid division output `0` instead.

Your answer will be accepted if the relative or absolute error is less than $10^{-6}$.
## 样例

### 样例输入 #1
```
3
4
0 3
3 0
2 3
3 2
5
4 0
5 -5
-4 -2
1 -2
-5 -2
4
0 1
1 0
0 2
1 1

```
### 样例输出 #1
```
17.2111025509
36.6326947621
0.0000000000

```
## 提示

A valid division (left) and an invalid division (right) of the first sample test case are shown below.

![](https://cdn.luogu.com.cn/upload/image_hosting/v17tmtdh.png)
## 题目翻译

## 题目描述

派蒙在平面上放置了$n+1$个互异的点，其中有一特殊点$O=(0,0)$，并记其余点为$\mathbb{S}$。

我们称一个点集 $\mathbb{U}$ 为$\textit{strict convex set}$，当且仅当点集中点的个数大于等于3（$|\mathbb{U}| \ge 3$）且$\mathbb{U}$中的所有点位于$\mathbb{U}$构成的凸包上，且任意三点不共线。


你需要将$\mathbb{S}$划分为两个集合 $\mathbb{A}$ 和$\mathbb{B}$，使其满足
- $\mathbb{A} \cap \mathbb{B}=\emptyset$.
- $\mathbb{A} \cup \mathbb{B}=\mathbb{S}$.
- $|\mathbb{A}| \ge 2, |\mathbb{B}| \ge 2$.

- 点集 $\mathbb{A} \cup \{O\}$ 是 $\textit{strict convex set}$，并记它的凸包为$C_{\mathbb{A} \cup \{O\}}$。
- 点集 $\mathbb{B} \cup \{O\}$是 $\textit{strict convex set}$，并记它的凸包为 $C_{\mathbb{B} \cup \{O\}}$。
- $C_{\mathbb{A} \cup \{O\}}$和 $C_{\mathbb{B} \cup \{O\}}$ 的轮廓 仅在 $O$相交。 这也就是说，仅有点$O$既在$C_{\mathbb{A} \cup \{O\}}$的轮廓上，又在$C_{\mathbb{B} \cup \{O\}}$的轮廓上。
  
请协助派蒙计算出这两个凸包周长之和的最大值。
这也就是说，找到一个合法的划分方案$\mathbb{A}$ 和 $\mathbb{B}$，使得 $(L(C_{\mathbb{A} \cup \{O\}}) + L(C_{\mathbb{B} \cup \{O\}}))$最大，其中$L(\text{polygon})$代表多边形的周长。 

## 输入格式

多组测试数据，第一行给出数据组数 $T$。

第一行给出一个整数 $n$ ($4 \le n \le 5 \times 10^5$) ，表示 $\mathbb{S}$ 中点的个数。

接下来$n$行，第$i$行 包含两个整数 $x_i$ 和 $y_i$ ($-10^9 \le x_i, y_i \le 10^9$, $(x_i, y_i) \ne (0, 0)$) 表示 $\mathbb{S}$ 中第 $i$个点的坐标。

保证同一组测试数据中的点互异，但可能存在三点共线。

保证 所有测试数据中$n$之和不超过 $10^6$.

## 输出格式

每组测试数据单起一行输出一个整数，表示两个凸包的周长之和的最大值。如不存在合法的划分方案，输出`0`。
与标准答案的相对或绝对误差小于 $10^{-6}$的答案会被视作正确答案。


---

---
title: "[ICPC 2018 Qingdao R] Mirror"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9892
tag: ['计算几何', '2018', 'Special Judge', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Mirror
## 题目描述

There is a non-transparent obstacle and a single-sided mirror in an infinite two-dimensional plane. The obstacle can be represented as a triangle and the mirror can be represented as a $\textbf{directional}$ line segment pointing from $(x_{m,1}, y_{m,1})$ to $(x_{m,2}, y_{m,2})$, with the right side being reflective.

There are $m$ stones at point $(x_1,y_1)$ and DreamGrid would like to move all the stones to point $(x_2,y_2)$. The following constraints must be satisfied:

- DreamGrid can only carry one stone each time.
- Once DreamGrid picks up a stone, he can only put it down at point $(x_2,y_2)$.
- Let $L$ be the path DreamGrid walked, then for each point $p$ on $L$, DreamGrid should see all the stones directly or through the mirror.

Note that:

- If some part of the line vision is inside the obstacle (it's ok that the line vision passes a point or edge of the obstacle), it's considered, that DreamGrid cannot see the stone with this line of vision.
- If one of the two endpoints of the mirror is on the line of vision, it's considered, that DreamGrid can see the stone both in the mirror and through the mirror.
- The reflection process is governed by laws of physics --- the angle of incidence is equal to the angle of reflection. The incident ray is in the same half-plane as the reflected ray, relative to the mirror.
- If the line of vision is parallel to the mirror, reflection doesn't take place, and the mirror isn't regarded as an obstacle.
- DreamGrid cannot move into the obstacle but can move on the edges or the vertices of the obstacle.
- DreamGrid cannot move through the mirror but can move on the mirror. Note that if DreamGrid is on the line segment of the mirror other than the two endpoints, he can only see the side he comes from, and cannot see through the mirror.

DreamGrid would like to know the shortest distance to move all stones from $(x_1,y_1)$ to $(x_2, y_2)$.
## 输入格式

There are multiple test cases. The first line of input is an integer $T$ (about 100), indicates the number of test cases. For each test case:

The first line contains one integer $m$ ($1 \le m \le 10^6$), indicating the number of stones.

The second line contains four integers $x_1$, $y_1$, $x_2$ and $y_2$, indicating the start point and the target point.

The third line contains four integers $x_{m,1}$, $y_{m,1}$, $x_{m,2}$ and $y_{m,2}$, indicating the coordinates of the mirror.

Each of the next $3$ lines has two integers $x_i$ and $y_i$, indicating the coordinates of the vertices of the obstacle.

All the coordinates will not exceed $100$ in absolute value. Both the start point and target point are outside the obstacle and the mirror. The mirror and the obstacle have no points in common.

It is guaranteed that no three points are collinear.
## 输出格式

For each test case, output a real number indicating the shortest distance, or output $-1$ if DreamGrid cannot move all the stones under the constraints.

Your answer will be considered correct if and only if the absolute error or relative error of your answer is less than $10^{-6}$.
## 样例

### 样例输入 #1
```
2
2
-2 0 2 0
-3 3 3 3
0 1
-3 -2
3 -2
2
-2 0 2 0
-3 3 -1 3
0 1
-3 -2
3 -2
```
### 样例输出 #1
```
13.416407864999
-1
```
## 提示

We now welcome our special guest Mashiro, who heartily donates this problem to our problemset, to explain the sample test cases for us using her sketch book.

![](https://cdn.luogu.com.cn/upload/image_hosting/wsxbrf43.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/d2bpz78p.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/nfhakntz.png)

$\textit{(Image from pixiv. ID: 32084305)}$

In the figures above, we indicate the start point as point $A$ and the target point as point $B$. The mirror is indicated by the line segment pointing from $M1$ to $M2$, with the right side being reflective.

For the first sample test case, the optimal path is $A \to C \to B \to C \to A \to C \to B$.

For the second sample test case, as DreamGrid cannot see $A$ from $B$, it's impossible to move all the two stones from $A$ to $B$ while following the constraints in the problem description.

## 题目翻译

### 题目描述

在一个无限二维平面上包含一个不透明障碍物和一个单面镜子。障碍物被表示为一个三角形，而镜子被表示为一个从点 $(x_{m,1}, y_{m,1})$ 指向 $(x_{m,2}, y_{m,2})$ 的有方向的线段，线段的右侧是反射面。

有 $m$ 个石头位于点 $(x_1,y_1)$，DreamGrid 希望将所有石头移动到点 $(x_2,y_2)$。需要满足以下条件：

DreamGrid 每次只能携带一个石头。
一旦 DreamGrid 拿起一个石头，他只能将其放置在点 $(x_2,y_2)$。

设 $L$ 为 DreamGrid 走过的路径，对于路径上的每一个点 $p$，DreamGrid 必须能直接或通过镜子看到所有的石头。

**注意：**

如果视线的某部分在障碍物内（视线穿过障碍物的点或边界是允许的），则认为 DreamGrid 无法通过这条视线看到石头。

如果镜子的一个端点在视线上，认为 DreamGrid 既可以在镜子中看到石头，也可以透过镜子看到石头。

反射过程遵循物理规律：入射角等于反射角。入射光线和反射光线在镜子的同一侧。

如果视线与镜子平行，则不发生反射，镜子不被视为障碍物。
DreamGrid 不能移动进入障碍物，但可以在障碍物的边缘或顶点上移动。

DreamGrid 不能穿过镜子移动，但可以在镜子上移动。注意，如果 DreamGrid 在镜子的线段上（不包括两个端点），他只能看到他来的那一侧，并且不能透过镜子看到。
DreamGrid 想要知道移动所有石头从 $(x_1,y_1)$ 到 $(x_2, y_2)$ 的最短距离。

### 输入格式

输入包括多个测试用例。第一行是一个整数 $T$（大约 100），表示测试用例的数量。对于每个测试用例：

第一行包含一个整数 $m$（$1 \le m \le 10^6$），表示石头的数量。

第二行包含四个整数 $x_1$, $y_1$, $x_2$ 和 $y_2$，表示起始点和目标点。

第三行包含四个整数 $x_{m,1}$, $y_{m,1}$, $x_{m,2}$ 和 $y_{m,2}$，表示镜子的坐标。

接下来的 $3$ 行，每行包含两个整数 $x_i$ 和 $y_i$，表示障碍物顶点的坐标。

所有坐标的绝对值不超过 $100$。起始点和目标点都在障碍物和镜子之外。镜子和障碍物没有公共点。

保证没有三个点是共线的。

### 输出格式

输出对于每个测试用例，输出一个实数表示最短距离，如果 DreamGrid 无法在约束条件下移动所有石头，则输出 $-1$。

如果你的答案的绝对误差或相对误差小于 $10^{-6}$，则认为你的答案是正确的。


---

---
title: "[THUPC 2024 初赛] 勇闯末日塔"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9972
tag: ['计算几何', '2024', 'Special Judge', 'THUPC']
---
# [THUPC 2024 初赛] 勇闯末日塔
## 题目背景

安宁顷刻今将逝，末日黑云伺隙来。宿命无情何所惧？越其止境冀花开。

为了执行毁灭世界的疯狂计划，一位占用了已死之人躯壳的神秘男子在这颗蓝色的星球上创造出了无数末日塔。这些末日塔会散发出浓密的以太射线，对末日塔附近的几乎所有生物进行精神控制，只有受到特殊加护的人才能免受以太射线控制。

一些受到加护的义勇队对这些末日塔进行了调查，其结果显示：这些末日塔组成了复杂的以太传输网络，持续不断地从大地中吸收以太，并将以太传输到位于帝国的中枢塔。

一队持有特殊加护的英雄决定闯入其中一些末日塔，以期彻底调查并尝试破坏这些末日塔。英雄们破坏掉进入的末日塔后，以太传输网络就会受到影响，因此大家希望选择一些末日塔，将其破坏后能使得网络的最大传输容量降到最低。

作为勇闯末日塔小队的先锋，你再次阅读了小队目前所掌握的所有信息。这次大胆的行动计划最终能否拯救这个世界，眼下恐怕谁都无法事先料定。但为了这颗星球的未来，我们只能放手一搏。
## 题目描述

星球的表面是一个中心位于 $(0, 0, 0)$，半径为 $R$ 的完美球面。星球表面上共有 $N$ 座末日塔，这些令人毛骨悚然的塔构成了以太传输网络的所有节点。

- 末日塔的高度远小于星球半径，因此我们认为第 $i (1 \le i \le N)$ 座塔是球面上的一个点 $\left(x_i, y_i, z_i\right)$。第 $i$ 座塔的以太传输效率为 $q_i$。
- 保证 $N$ 座末日塔的位置两两不同。在这 $N$ 座末日塔中，$s$ 号塔是以太吸收点，$t$ 号塔是位于帝国的中枢塔；这两座塔的以太浓度显著高于其它的末日塔，因此只能闯入这两座塔之外的末日塔。

$N$ 座末日塔之间共有 $M$ 条传输通道。第 $j (1 \le j \le M)$ 条传输通道连接 $u_j, v_j$ 两座末日塔，让它们可以互相传输以太。

- 传输通道是双向的，但单位时间内以太的流向必须是单向的。
- 为了节省不必要的成本，传输通道的两端不会连接相同的塔，也不会有两条传输通道连接相同的末日塔对。
- 为了降低传输距离，第 $i$ 条传输通道沿着 $u_j$ 和 $v_j$ 所在的大圆的劣弧铺设，故其**长度** $r_j$ 为两座末日塔在星球表面的球面距离。为了避免传输通道的互相干扰，**对于任意一条传输通道所对应的劣弧，其他传输通道所对应的劣弧只会在该劣弧的两端点上与该劣弧相交**。保证由同一条传输通道相连的两座末日塔的位置不是对跖点关系。
  - 如果不知道大圆、劣弧、球面距离和对跖点是什么，可以参考题面最后的提示部分。

受到传输效率和通道长度的影响，每条传输通道有各自传输以太的容量上限。

- 具体而言，每个单位时间内，第 $j$ 条传输通道的**容量上限**为 $\frac{Kq_{u_j} q_{v_j}}{r_j^2}$，其中 $K$ 是给定的常数，$q_{u_j}, q_{v_j}$ 为该传输通道两端的塔的传输效率，$r_j$ 为这条传输通道的长度。

整张以太传输网络需要将 $s$ 号塔吸收的以太沿着传输通道传输到 $t$ 号塔，并使得单位时间内的以太传输量最大。为此，传输网络会自动确定一个以太传输方案，在满足所有传输通道容量上限的前提下，最大化这一传输量。

- 换句话说，如果将末日塔看作图上的点，传输通道看作边，而传输通道的容量上限对应每条边的容量，那么以太的传输方案应该恰好为 $s$ 到 $t$ 的最大流。

虽然没有任何人能保证闯入末日塔之后就一定能将其破坏，但作为勇闯末日塔小队的先锋，你还是想在出发之前计算一下，如果成功破坏了所有将要闯入的末日塔，传输网络单位时间的最大传输量将会降至多少。

- 如果成功破坏了选择的末日塔，与其相连的所有传输通道的容量都将降至 $0$，其余传输通道容量不发生变化；此时传输网络会自动调节至一个在新的网络中传输量最大的新方案。
- 在最理想的情况下，小队将有机会调查并破坏 $L$ 座末日塔。因此，需要事先选择 $L$ 座末日塔（均不能是 $s$ 或 $t$），使得当这 $L$ 座末日塔都被成功破坏时，传输网络的新的传输方案的以太传输量尽可能地小。
## 输入格式

输入的第一行包括五个正整数 $N, M, L, s, t$（$3\le N\le 500$，$2\le M\le \frac{N(N-1)}{2}$，$1\le L\le \min\{8,N-2\}$，$1\le s, t\le N$），分别表示该传输网络包含的末日塔数量，传输通道数量，有机会闯入的末日塔数量，最主要的以太吸收塔的编号和中枢塔的编号。

输入的第二行包括两个实数 $R, K$（$1\le R\le 10^3$，$1\le K\le 10^3$），分别表示星球的半径和计算以太容量时用到的常数。

接下来 $N$ 行，每行三个实数 $a_i, b_i, q_i$（$0\le a_i\le 1$，$0\le b_i< 2$，$1\le q_i \le 10^3$），描述第 $i$ 座末日塔的信息，其中 $q_i$ 表示第 $i$ 座末日塔的传输能力， $a_i$ 和 $b_i$ 共同描述末日塔的位置：令 $\theta_i = \pi a_i$，$\varphi_i = \pi b_i$（如果你习惯使用角度制而不是弧度制，可以将 $\pi$ 改为 $180^\circ$），则 $\left(x_i, y_i, z_i\right) = \left(R \sin\theta_i \cos\varphi_i, R\sin\theta_i \sin\varphi_i, R\cos\theta_i\right)$。保证末日塔的位置各不相同。

最后 $M$ 行，每行两个正整数 $u_i, v_i$（$1\le u_i, v_i\le N$），表示一条传输通道连接的两座末日塔的编号。保证同一条传输通道连接的两座末日塔不相同且不互为对跖点，没有两条传输通道连接的是相同的末日塔对，且传输网络是连通的。

保证输入的所有实数保留到小数点后第 $4$ 位。
## 输出格式

输出一个实数，表示如果成功破坏了将要闯入的末日塔，新的传输网络单位时间的最大传输量。当你的输出与标准输出的相对误差或绝对误差不超过 $10^{-6}$ 时，我们认为你的输出是正确的。
## 样例

### 样例输入 #1
```
6 11 1 1 6
1.0000 1.0000
1.0000 0.0000 10.0000
0.7500 0.2500 6.0000
0.5000 0.0000 1.0000
0.5000 0.5000 1.0000
0.2500 0.2500 6.0000
0.0000 0.0000 10.0000
1 2
1 3
1 4
2 3
2 4
3 4
3 5
3 6
4 5
4 6
5 6

```
### 样例输出 #1
```
8.105694691387022

```
## 提示

### 样例 \#1 解释

以太传输网络如下图所示。图中蓝色球面即为星球表面；紫色点为各末日塔，其中 $P_i$ 对应输入的第 $i$ 座末日塔；黄色的线表示各传输通道。

![样例 1 示意图](https://cdn.luogu.com.cn/upload/image_hosting/4bynt5dl.png)

原来的传输网络单位时间最大传输量为 $188/\pi^2$。破坏第 $2$ 个末日塔或第 $5$ 个末日塔都能使新的传输网络单位时间的最大传输量降至 $80/\pi^2$，而破坏第 $3$ 个末日塔或第 $4$ 个末日塔只能使新的传输网络单位时间的最大传输量降至 $94/\pi^2$，所以应该选择第 $2$ 个或第 $5$ 个末日塔尝试破坏。


---

