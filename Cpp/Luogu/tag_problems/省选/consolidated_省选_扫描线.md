---
title: "[BalticOI 2024] Tiles"
layout: "post"
diff: 省选/NOI-
pid: P10763
tag: ['线段树', '平衡树', '2024', '扫描线', 'BalticOI（波罗的海）']
---
# [BalticOI 2024] Tiles
## 题目背景

翻译自 [BalticOI 2024 Day2 T2](https://boi2024.lmio.lt/tasks/d2-tiles-statement.pdf)。
## 题目描述

有一个存在 $N$ 个顶点的大教堂，顶点坐标依次为 $(x_i,y_i)$，对于每个 $1 \leq i < N$，存在一条 $i$ 与 $i+1$ 之间的边，此外，还存在一条 $N$ 到 $1$ 的边。

大教堂每条边都与 $x$ 轴或 $y$ 轴平行。此外，大教堂是一个简单多边形，即：

- 每个顶点恰好由两条边相交
- 任何一对边只能在顶点处相交

你有无数块 $2 \times 2$ 的瓷砖，你希望用这些瓷砖覆盖大教堂的大部分区域，具体来说，你想选择一条垂直线，并覆盖该线左侧的大教堂部分。对于任何整数 $k$，设 $L_k$ 为包含 $x$ 坐标等于 $k$ 的点的垂直线。对 $L_k$ 左侧大教堂部分的覆盖，是指在平面上放置一定数量的瓷砖，使得：

- 多边形内部且 $x$ 坐标小于 $k$ 的每个点都被某块瓷砖覆盖
- 多边形外部或 $x$ 坐标大于 $k$ 的点都不被任何瓷砖覆盖
- 瓷砖的内部不重叠

大教堂中任何顶点的最小 $x$ 坐标为 $0$。我们设 $M$ 为大教堂中任何顶点的最大 $x$ 坐标。

请你求出最大的满足条件的 $k\ (0 \leq k \leq M)$，根据定义，一定存在答案为 $0$。
## 输入格式

第一行两个整数 $N,M$。

接下来 $N$ 行，每行两个整数 $(x_i,y_i)$。这些顶点按照顺时针或逆时针顺序给出。
## 输出格式

输出一个答案 $k$。
## 样例

### 样例输入 #1
```
14 6
0 1
0 3
2 3
2 4
0 4
0 6
3 6
3 7
4 7
6 7
6 5
3 5
3 2
3 1

```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
4 3
0 0
0 3
3 3
3 0
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
18 9
0 2
2 2
2 1
4 1
4 0
9 0
9 2
4 2
4 4
7 4
7 3
9 3
9 6
4 6
4 5
2 5
2 4
0 4
```
### 样例输出 #3
```
6
```
## 提示

| 子任务编号 | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: |
| $1$ | $N=4$ | $4$ |
| $2$ | $N \leq 6$ | $9$ |
| $3$ | $x_N=0,y_N=0$，对于 $1 \leq i \leq N-2$，$x_i \leq x_{i+1},y_i \geq y_{i+1}$ | $11$ |
| $4$ | $M \leq 1000$ 且 $y_i \leq 1000$ | $19$ |
| $5$ | $y_i$ 都为偶数 | $22$ |
| $6$ | $x_i$ 都为偶数 | $25$ |
| $7$ | 无特殊性质 | $10$ |

对于所有数据，$4 \leq N \leq 2 \times 10^5$，$1 \leq M \leq 10^9$，$0 \leq y_i \leq 10^9$，$\min(\{x_i\}) = 0,\max(\{x_i\}) = M$。

对于样例一，下面是对于 $k=2$ 的覆盖。

![](https://cdn.luogu.com.cn/upload/image_hosting/q9qi2e3b.png)

可以发现这是最大的情况了。

对于样例二，没有正值 $k$，使得 $L_k$ 左侧的教堂部分可以用瓷砖覆盖。

对于样例三，图示如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/6kpbkvbn.png)


---

---
title: "「KDOI-10」超级演出"
layout: "post"
diff: 省选/NOI-
pid: P11191
tag: ['线段树', '2024', '洛谷原创', 'O2优化', '扫描线', '洛谷月赛', '根号分治']
---
# 「KDOI-10」超级演出
## 题目背景

[English Statement](https://www.luogu.com.cn/problem/T519360). You must submit your code at the Chinese version of the statement.

**本场比赛所有题目从标准输入读入数据，输出到标准输出。**
## 题目描述

巡准备了一场超级演出。舞台和候场室可以看作一个包含 $n$ 个点 $m$ 条边的有向图，并且这个图当中没有环，也就是说，这是一张有向无环图（DAG）。

舞台为 $1$ 号节点，**保证所有节点均有到达节点 $\bm 1$ 的路径**。其余的节点均为候场室，每个候场室恰有一个剧团进行等待。

巡可以对一个候场室 $u$ 发布出场命令：

- 如果这个候场室的剧团还没有出场，并且存在一条 $u\to 1$ 的路径上没有其余候场的剧团。那么这个剧团就会沿着这条路径到达舞台进行演出，随后退场。注意：**一个剧团退场后不会重新回到候场室。**
- 否则，这个命令被认为是无效的。

巡有一个命令序列 $a_1,a_2,\dots,a_k$ 和 $q$ 次询问，每次给出一个区间 $[l,r]$。巡想要知道如果依次对候场室 $a_l,a_{l+1},\dots,a_r$ 发布出场命令后，候场室还会剩下多少剧团等待演出。

注意：每次询问相互独立，也就是说，每次询问之前，每个候场室都恰有一个剧团进行等待。

## 输入格式

从标准输入读入数据。

输入的第一行包含一个正整数 $c$，表示测试点编号。$c=0$ 表示该测试点为样例。

第二行包含四个正整数 $n,m,k,q$，表示图的点数，边数，序列长度，和询问次数。

接下来 $m$ 行，每行两个正整数 $u,v$，表示一条从 $u$ 到 $v$ 的有向边。保证无自环，无重边。

接下来的一行，$k$ 个正整数 $a_1,a_2,\dots,a_k$。

接下来 $q$ 行，每行两个正整数 $l,r$，表示一次询问的区间。
## 输出格式

输出到标准输出。

$q$ 行，每行一个非负整数，表示一次询问的答案。
## 样例

### 样例输入 #1
```
0
5 5 5 4
2 1
3 1
5 1
4 2
4 3
2 4 4 3 5
1 2
1 5
3 5
2 3

```
### 样例输出 #1
```
2
0
2
4

```
## 提示

**【样例 1 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/2a4qed7w.png)

如图：

- 当询问 $l=1,r=2$ 时：
	- 发布出场命令 $a_1=2$。$2$ 沿着 $2\to 1$ 出场。
   - 发布出场命令 $a_2=4$。$4$ 沿着 $4\to 2\to 1$ 出场。
   
   此时余下 $3,5$ 两个剧团，输出 $2$。
   
- 当询问 $l=2,r=3$ 时：
	- 发布出场命令 $a_2=4$。找不到 $4\to 1$ 的且路上没有别的剧团的路线，该指令被认为无效。
   - 发布出场命令 $a_3=4$。找不到 $4\to 1$ 的且路上没有别的剧团的路线，该指令被认为无效。
   
   此时余下 $2,3,4,5$ 四个剧团，输出 $4$。
  
**【样例 2】**

见选手目录下的 `show/show2.in` 与 `show/show2.ans`。

这个样例满足测试点 $1,2$ 的限制条件。

**【样例 3】**

见选手目录下的 `show/show3.in` 与 `show/show3.ans`。

这个样例满足测试点 $5\sim 8$ 的限制条件。

**【样例 4】**

见选手目录下的 `show/show4.in` 与 `show/show4.ans`。

这个样例满足测试点 $9\sim 11$ 的限制条件。

**【样例 5】**

见选手目录下的 `show/show5.in` 与 `show/show5.ans`。

这个样例满足测试点 $12,13$ 的限制条件。


**【样例 6】**

见选手目录下的 `show/show6.in` 与 `show/show6.ans`。

这个样例满足测试点 $18,19$ 的限制条件。

***

**【数据范围】**

对于全部的测试数据，保证：

- $1\leq n,k,q\leq2\times10^5$；
- $1\leq m\leq4\times10^5$；
- $1\leq v<u\leq n$，且不存在两组相同的 $(u,v)$；
- 对于任意 $1\le i\le k$，$2\leq a_i\leq n$；
- 对于每组询问，$1\leq l\leq r\leq k$；
- 输入构成一张有向无环图，且所有节点均存在到达节点 $1$ 的路径。

| 测试点 | $n,k,q\leq$ | $m\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|
| $1,2$ | $300$ | $600$ | 无 |
| $3,4$ | $2\,000$ | $4\,000$ | A |
| $5\sim 8$ | $2\,000$ | $4\,000$ | 无 |
| $9\sim 11$ | $2\times10^5$ | $4\times10^5$ | A |
| $12,13$ | $2\times10^5$ | $4\times10^5$ | BC |
| $14,15$ | $2\times10^5$ | $4\times10^5$ | C |
| $16,17$ | $2\times10^5$ | $4\times10^5$ | BD |
| $18,19$ | $2\times10^5$ | $4\times10^5$ | D |
| $20\sim 22$ | $2\times10^5$ | $4\times10^5$ | B |
| $23\sim 25$ | $2\times10^5$ | $4\times10^5$ | 无 |

- 特殊性质 A：图退化为一棵内向树，也就是说，除节点 $1$ 外，每个点恰有一条出边，节点 $1$ 没有出边；
- 特殊性质 B：保证对于每组询问，$r=k$；
- 特殊性质 C：保证对于任意 $1\leq i< j\leq k$，$a_i\neq a_j$；
- 特殊性质 D：保证每个点的入度和出度均不超过 $30$。


---

---
title: "[GCJ 2021 Finals] Cutting Cake"
layout: "post"
diff: 省选/NOI-
pid: P13043
tag: ['数学', '高精度', '2021', '扫描线', 'Google Code Jam']
---
# [GCJ 2021 Finals] Cutting Cake
## 题目描述

Today is your and your twin sibling's birthday. To celebrate, you got a rectangular cake to share. The cake is decorated with $\mathbf{N}$ triangular patches of icing (which may overlap). All the icing patches were created with the same triangular mold, so they have the same shape and orientation. Although you and your twin are very similar, your tastes in icing are much different. This difference is formalized by each of you having a different enjoyment value for each patch of icing. Specifically, your enjoyment value for eating the entire $i$-th patch of icing is $\mathbf{A}_i$, and your twin's is $\mathbf{B}_i$. If someone eats part of a patch, they get enjoyment proportional to the eaten area. For example, if you eat $\frac{2}{3}$ of the area of the $i$-th icing patch, you would get $\frac{2\mathbf{A}_i}{3}$ enjoyment from it. Note that there may be some flavors of icing that you or your twin do not enjoy, so the $\mathbf{A}_i$ and/or $\mathbf{B}_i$ values can be negative.

![](https://cdn.luogu.com.cn/upload/image_hosting/bb02prmd.png)

You will cut the cake into two rectangular pieces by making a single vertical cut (parallel to the Y-axis). After cutting the cake, you will eat the left piece and your twin will eat the right piece. Your total enjoyment is the sum of the enjoyment you get from all icing to the left of the cut. Similarly, your twin's enjoyment is the sum of the enjoyment they get from all icing to the right of the cut.

To be as fair as possible, you want to cut the cake such that the absolute value of the difference between your total enjoyment and your twin's total enjoyment is as small as possible. Given the $\mathbf{N}$ triangular icing patches on a rectangular cake, what is the minimum possible absolute value of the difference between your and your twin's total enjoyments you can get?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing three positive integers, $\mathbf{N}$, $\mathbf{W}$, and $\mathbf{H}$, representing the number of icing patches on the cake and the width and height of the top of the cake, respectively. The bottom-left corner of the cake is located at $(0,0)$ and the top-right corner is at $(\mathbf{W}, \mathbf{H})$. Then, a line describing the icing patch mold follows. This line contains four integers: $\mathbf{P}$, $\mathbf{Q}$, $\mathbf{R}$, and $\mathbf{S}$. The icing patch mold is a triangle with vertices at $(0,0)$, $(\mathbf{P}, \mathbf{Q})$, and $(\mathbf{R}, \mathbf{S})$. Then, $\mathbf{N}$ lines follow. The $i$-th of these lines contains four integers $\mathbf{X}_i$, $\mathbf{Y}_i$, $\mathbf{A}_i$, and $\mathbf{B}_i$. The $i$-th patch is a triangle with vertices at $(\mathbf{X}_i, \mathbf{Y}_i)$, $(\mathbf{X}_i + \mathbf{P}, \mathbf{Y}_i + \mathbf{Q})$, and $(\mathbf{X}_i + \mathbf{R}, \mathbf{Y}_i + \mathbf{S})$. You would get $\mathbf{A}_i$ enjoyment from eating it and your twin would get $\mathbf{B}_i$ enjoyment.
## 输出格式

For each test case, output one line containing `Case #x: y/z`, where $x$ is the test case number (starting from 1) and $\frac{y}{z}$ is the minimum absolute value of the difference between your and your twin's total enjoyment that can be achieved with a single vertical cut as an irreducible fraction (that is, $z$ must be positive and of minimum possible value).
## 样例

### 样例输入 #1
```
4
1 5 5
3 -1 2 2
1 2 -10 5
2 100000000 50000000
80000000 0 40000000 40000000
5000001 2500000 500 -501
15000000 5000000 501 -400
2 10 10
0 2 4 2
2 2 -4 5
4 6 -6 5
3 622460462 608203753
486076103 36373156 502082214 284367873
98895371 126167607 823055173 -740793281
26430289 116311281 -398612375 -223683435
46950301 278229490 766767410 -550292032
```
### 样例输出 #1
```
Case #1: 5/1
Case #2: 288309900002019999899/320000000000000000
Case #3: 37/4
Case #4: 216757935773010988373334129808263414106891/187470029508637421883991794137967
```
## 提示

**Sample Explanation**

In Sample Case #1, there is a single icing patch. The optimal cut is to the left of the patch. You will eat no icing and receive 0 enjoyment. Your twin will eat all of the icing patch and receive 5 enjoyment from it. The absolute value of the difference between your and your twin's enjoyments is $|0 - 5| = 5$.

![](https://cdn.luogu.com.cn/upload/image_hosting/0l7tbto8.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/nfrgziry.png)

In Sample Case #2, there are two icing patches. The optimal cut is at $X = 15099999.99$. Notice that the numerator and denominator of the answer can get very large.

![](https://cdn.luogu.com.cn/upload/image_hosting/wer6hjfq.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/bjelfqv7.png)

In Sample Case #3, there are two icing patches. The optimal cut is at $X = 4$. You will eat 75% of the first icing patch and receive $-3$ enjoyment from it. Your twin will eat 25% of the first icing patch and all of the second icing patch getting $5 \cdot 0.25 + 5 = 6.25$ enjoyment. The absolute value of the difference between your and your twin's enjoyments is $|-3 - 6.25| = 9.25 = \frac{37}{4}$.

Notice that cutting at $X = 1$ would give you $0$ enjoyment and your twin $10$ enjoyment. While both of those values are greater than the corresponding enjoyment when cutting at $X = 4$, the difference between them is $10 > 9.25$, which means cutting at $X = 4$ is preferable anyway.

![](https://cdn.luogu.com.cn/upload/image_hosting/x0dpaoy4.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/kgtk2lkh.png)

In Sample Case #4, there are three icing patches. The optimal cut is at $X \approx 521241077.6027$.

**Test Set 1 (20 Pts, Visible Verdict)**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{N} \leq 100$.
- $3 \leq \mathbf{W} \leq 10^{9}$.
- $3 \leq \mathbf{H} \leq 10^{9}$.
- $-10^{9} \leq \mathbf{A}_{i} \leq 10^{9}$, for all $i$.
- $-10^{9} \leq \mathbf{B}_{i} \leq 10^{9}$, for all $i$.
- $0 \leq \mathbf{P} \leq 10^{9}$.
- $-10^{9} \leq \mathbf{Q} \leq 10^{9}$.
- $0 \leq \mathbf{R} \leq 10^{9}$.
- $-10^{9} \leq \mathbf{S} \leq 10^{9}$.
- The three vertices of the mold $(0, 0)$, $(\mathbf{P}, \mathbf{Q})$, and $(\mathbf{R}, \mathbf{S})$ are not collinear.
- The three vertices of each triangular icing patch are strictly inside the cake's borders. Formally:
  - $1 \leq \mathbf{X}_{i} \leq \mathbf{W} - \max(\mathbf{P}, \mathbf{R}) - 1$, for all $i$, and
  - $\max(0, -\mathbf{Q}, -\mathbf{S}) + 1 \leq \mathbf{Y}_{i} \leq \mathbf{H} - \max(0, \mathbf{Q}, \mathbf{S}) - 1$, for all $i$.



---

---
title: "[GCJ 2020 #3] Recalculating"
layout: "post"
diff: 省选/NOI-
pid: P13069
tag: ['2020', '线段树', '扫描线', 'Google Code Jam']
---
# [GCJ 2020 #3] Recalculating
## 题目描述

You are working for the Driverless Direct Delivery Drone Directions Design Division of Apricot Rules LLC. The company is about to take its first drone "Principia" to market. You are tasked with designing backup systems for Principia, in case it loses access to its primary geolocation systems (like GPS), but it still needs a way to get directions. Principia is designed for use on a flat region; formally, the region is a Cartesian plane in which the coordinates are in meters. One or more points on this plane are drone repair centers. No two drone repair centers are at the same location.

Principia has a system that can retrieve the relative locations of drone repair centers that are within an $L_1$ distance (which is also known as Manhattan distance) of at most $\mathbf{D}$ meters of its location. The information retrieved is a set of repair center locations relative to Principia's current location. For example: "there is a repair center 4 meters north and 3.5 meters west, and another one 2.5 meters east". Notice that the information does not identify repair centers; it gives their locations relative to Principia.

You quickly realized that there may be points on the map where this information may not be enough for Principia to uniquely determine its current location. This is because there might be two (or more) different points from which the information looks the same. Points with this property are called non-distinguishable, while all other points are called distinguishable.

Formally, the information retrieved by Principia when located at point $(x, y)$ is $\text{Info}(x, y) :=$ the set of all points $(z - x, w - y)$, where $(z, w)$ is the location of a repair center and $|z - x| + |w - y| \leq \mathbf{D}$. Here $|z - x|$ and $|w - y|$ denote the absolute values of $z - x$ and $w - y$, respectively. A point $(x_1, y_1)$ is non-distinguishable if and only if there exists another point $(x_2, y_2)$ such that $\text{Info}(x_1, y_1) = \text{Info}(x_2, y_2)$.

For example, suppose $\mathbf{D} = 4$ and there are repair centers at points $(0, 0)$ and $(5, 0)$. The point $(0, 0)$ is non-distinguishable because $\text{Info}(0, 0) = \{(0, 0)\} = \text{Info}(5, 0)$. This means that point $(5, 0)$ is also non-distinguishable. On the other hand, $\text{Info}(3.5, 0.1) = \{(-3.5, -0.1), (1.5, -0.1)\}$ is not equal to the information from any other point, which means that point $(3.5, 0.1)$ is distinguishable. The following picture illustrates the regions of distinguishable points (in red) and non-distinguishable points (in blue):

![](https://cdn.luogu.com.cn/upload/image_hosting/lejki1zk.png)

Principia is deployed to a point that is chosen uniformly at random from the set of all points that are within $\mathbf{D}$ meters (using $L_1$ distance) of at least one repair center — that is, the set of all points $(x, y)$ such that $\text{Info}(x, y)$ is non-empty. The probability of that choice belonging to a given continuous set of points $S$ is proportional to the number of square meters of $S$'s area. In the example above, each red square has an area of 4.5 square meters, while each blue section has an area of 23 square meters. Therefore, the probability of Principia being deployed within each red square is $4.5 / (3 \times 4.5 + 2 \times 23)$ and the probability of it being deployed within each blue section is $23 / (3 \times 4.5 + 2 \times 23)$. Since the border between adjacent differently-colored sections has area equal to 0, the probability of Principia being deployed exactly on the border is exactly 0.

Given the locations of all repair centers, what is the probability that the point to which Principia is deployed is distinguishable?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing two integers $\mathbf{N}$ and $\mathbf{D}$ representing (respectively) the number of repair centers and the maximum $L_1$ distance from which Principia can retrieve information from a repair center, as described above. Then, $\mathbf{N}$ lines follow. The $i$-th of these contains two integers $\mathbf{X_i}$ and $\mathbf{Y_i}$ representing the coordinates of the $i$-th repair center. The unit of measurement for all coordinates and $\mathbf{D}$ is meters.

## 输出格式

For each test case, output one line containing `Case #x: y z`, where $x$ is the test case number (starting from 1) and $y$ and $z$ are non-negative integers. The fraction $y/z$ must represent the probability of Principia being at a distinguishable location, if one is chosen uniformly at random from all locations that are within $\mathbf{D}$ meters of at least one repair center (using $L_1$ distance). If there are multiple acceptable values for $y$ and $z$, choose the one such that $z$ is minimized.
## 样例

### 样例输入 #1
```
4
2 4
0 0
5 0
2 1
0 0
5 0
2 4
0 0
4 4
2 4
0 0
5 1
```
### 样例输出 #1
```
Case #1: 27 119
Case #2: 0 1
Case #3: 0 1
Case #4: 1 5
```
### 样例输入 #2
```
1
3 4
0 0
1 1
2 3
```
### 样例输出 #2
```
Case #1: 101 109
```
## 提示

**Sample Explanation**

Sample Test Set 1 meets the limits for Test Set 1. Another sample case that does not meet those limits could appear in any of the other test sets.

Sample Case #1 is described and depicted in the statement.

The points in the middle red region are all distinguishable points because they are the only points that retrieve information from both repair centers, and each point in that region retrieves a distinct set of information.

The points in the left and right red region each receive information from only one repair center, but that information is always unique, so these are all distinguishable points. For example, if Principia knows it is $3$ meters east of a repair center, it can be sure it is not $3$ meters east of the repair center at $(0, 0)$, because then it would have retrieved information from both repair centers. So it must be $3$ meters east of the repair center at $(5, 0)$.

The points in the blue regions are all non-distinguishable points. Choose any point in one of those regions, and consider the information that Principia would get from that point. It contains only the one repair center in range. But, there is a corresponding point in the other blue region from which Principia would get exactly the same information.

As explained above, the probability of Principia being deployed to one of the red sections is $4.5/59.5$, so the total probability of it being deployed to any of them is $3\times 4.5/59.5 = 27/119$.

The following picture illustrates Sample Case #2. There is no way to retrieve information from more than one repair center, so every point close enough to one of them is non-distinguishable; the same information is retrieved from an equivalent point near the other one. Remember that $z$ (the denominator) must be minimal, so $0\ 1$ is the only acceptable answer.

![](https://cdn.luogu.com.cn/upload/image_hosting/uxwv3yho.png)

The following picture illustrates Sample Case #3. Notice that the border between the two blue squares consists of distinguishable points. However, since its area is $0$, the probability of Principia being deployed there is $0$. All other points where Principia can be deployed are non-distinguishable.

![](https://cdn.luogu.com.cn/upload/image_hosting/sh8ma8rw.png)

The following picture illustrates Sample Case #4.

![](https://cdn.luogu.com.cn/upload/image_hosting/ibxhmn7j.png)

The following picture illustrates the additional case.

![](https://cdn.luogu.com.cn/upload/image_hosting/0hdmx3av.png)

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{D} \leq 10^7$.
- $-10^9 \leq \mathbf{X_i} \leq 10^9$, for all $i$.
- $-10^9 \leq \mathbf{Y_i} \leq 10^9$, for all $i$.
- $(\mathbf{X_i}, \mathbf{Y_i}) \neq (\mathbf{X_j}, \mathbf{Y_j})$ for all $i \neq j$. (No two repair centers share the same location.)

**Test Set 1 (6 Pts, Visible Verdict)**

- Time limit: 20 seconds.
- $\mathbf{N} = 2$.

**Test Set 2 (11 Pts, Visible Verdict)**

- Time limit: 60 seconds.
- $2 \leq \mathbf{N} \leq 10$.

**Test Set 3 (15 Pts, Visible Verdict)**

- Time limit: 120 seconds.
- For 6 cases, $\mathbf{N} = 1687$.
- For $\mathbf{T}-6$ cases, $2 \leq \mathbf{N} \leq 100$.


---

---
title: "[FJCPC 2025] 帕累托前沿"
layout: "post"
diff: 省选/NOI-
pid: P13094
tag: ['2025', '福建', 'cdq 分治', '扫描线', 'XCPC']
---
# [FJCPC 2025] 帕累托前沿
## 题目描述

给出 $n$ 个二元组 $(x_i,y_i)$，你需要回答 $q$ 个询问，每个询问给出闭区间 $[l,r]$，请回答满足以下条件的整数 $j$ 数量：

- $l\leq j\leq r$；

- 不存在 $l\leq k\leq r, k\neq j$，使得 $x_k\geq x_j$ 且 $y_k\geq y_j$。
## 输入格式

第一行两个正整数 $n,q$（$1\leq n,q\leq 10^6$），分别表示二元组数量和询问数量。

第二行 $n$ 个非负整数 $x_1,x_2,\dots,x_n$（$0\le x_i\le 10^6$）。

第三行 $n$ 个非负整数 $y_1,y_2,\dots,y_n$（$0\le y_i\le 10^6$）。

接下来 $q$ 行，每行两个正整数 $l,r$（$1\leq l\leq r\leq n$），表示询问的区间。
## 输出格式

对于每个询问，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
8 7
1 9 7 8 0 7 2 3
19 20 5 6 1 14 9 5
1 8
3 7
2 6
4 4
5 7
3 8
6 7
```
### 样例输出 #1
```
1
2
1
1
1
2
1
```
## 提示

对于询问 $1$，满足条件的整数为 $2$。

对于询问 $2$，满足条件的整数为 $4$、$6$。

对于询问 $3$，满足条件的整数为 $2$。

对于询问 $4$，满足条件的整数为 $4$。

对于询问 $5$，满足条件的整数为 $6$。

对于询问 $6$，满足条件的整数为 $4$、$6$。

对于询问 $7$，满足条件的整数为 $6$。


---

---
title: "[GCJ 2012 Finals] Xeno-archaeology"
layout: "post"
diff: 省选/NOI-
pid: P13334
tag: ['数学', '2012', '扫描线', '分类讨论', 'Google Code Jam']
---
# [GCJ 2012 Finals] Xeno-archaeology
## 题目描述

Long ago, an alien civilization built a giant monument. The floor of the monument looked like this:

```
###############
#.............#
#.###########.#
#.#.........#.#
#.#.#######.#.#
#.#.#.....#.#.#
#.#.#.###.#.#.#
#.#.#.#.#.#.#.#
#.#.#.###.#.#.#
#.#.#.....#.#.#
#.#.#######.#.#
#.#.........#.#
#.###########.#
#.............#
###############
```

Each '#' represents a red tile, and each '.' represents a blue tile. The pattern went on for miles and miles (you may, for the purposes of the problem, assume it was infinite). Today, only a few of the tiles remain. The rest have been damaged by methane rain and dust storms. Given the locations and colours of the remaining tiles, can you find the center of the pattern?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one starts with a line containing $N$, the number of remaining tiles. The next $N$ lines each contain $X_i$, $Y_i$, and the tile colour (either '#' or '.').

## 输出格式

For each test case, output one line containing "Case #$c$: $X$ $Y$", where $c$ is the case number (starting from 1) and ($X$, $Y$) is the location of the center of the pattern. If there is more than one possible answer, output the ($X$, $Y$) closest to (0, 0) in Manhattan distance (the distance in $x$, plus the distance in $y$). If there are still ties, output the one with the largest $X$. If there are still ties after that, output the one with the largest $Y$. If there is no possible answer, output "Case #$c$: Too damaged".
## 样例

### 样例输入 #1
```
6
1
0 0 .
1
0 0 #
3
0 0 #
0 1 #
1 0 #
5
50 30 #
49 30 #
49 31 #
49 32 #
50 32 #
2
-98 0 #
99 50 .
4
88 88 .
88 89 .
89 88 .
89 89 .
```
### 样例输出 #1
```
Case #1: 0 0
Case #2: 1 0
Case #3: 1 1
Case #4: 50 31
Case #5: 1 0
Case #6: Too damaged
```
## 提示

**Limits**

- $1 \leq T \leq 50.$
- The list of coordinates in each test case will not contain duplicates.

**Test set 1 (12 Pts, Visible Verdict)**

- $1 \leq N \leq 100.$
- $-100 \leq X_i \leq 100.$
- $-100 \leq Y_i \leq 100.$

**Test set 2 (33 Pts, Hidden Verdict)**

- $1 \leq N \leq 1000.$
- $-10^{15} \leq X_i \leq 10^{15}.$
- $-10^{15} \leq Y_i \leq 10^{15}.$


---

---
title: "芳权多"
layout: "post"
diff: 省选/NOI-
pid: P13841
tag: ['线段树', '扫描线']
---
# 芳权多
## 题目描述

Yuki 有一个长度为 $n$ 且只包含小写字母的字符串 $s$，其下标从 $1$ 开始。

定义一次修改为对 $s$ **同时**进行下面的两种操作：

- 将 $s$ 中所有为 $\texttt{he}$ 的子串替换为 $\texttt{she}$；
- 将 $s$ 中所有为 $\texttt{his}$ 的子串替换为 $\texttt{her}$。

例如，对 $\texttt{hihehishe}$ 进行一次操作后，该字符串会变为 $\texttt{hishehershe}$。

现有 $q$ 次询问，第 $i$ 次询问给出两个参数 $k_i,x_i$，你需要求出对 $s$ 进行 $k_i$ 次修改后 $s$ 的第 $x_i$ 个字符，或报告不存在第 $x_i$ 个字符。询问之间互相独立。
## 输入格式

**本题有多组测试数据。**

输入的第一行包含两个整数 $c,T$，分别表示测试点编号和测试数据组数。样例满足 $c=0$。

接下来依次输入每组测试数据。对于每组测试数据：

- 第一行两个正整数 $n,q$。
- 第二行一个长度为 $n$ 的字符串 $s$。
- 接下来 $q$ 行，第 $i$ 行两个正整数 $k_i,x_i$。
## 输出格式

对于每组测试数据，输出 $q$ 行，第 $i$ 行包含一个字符：

- 若对 $s$ 进行 $k_i$ 次修改后 $s$ 中存在第 $x_i$ 个字符，则输出该字符；
- 若对 $s$ 进行 $k_i$ 次修改后 $s$ 中不存在第 $x_i$ 个字符，则输出 $\texttt{0}$。
## 样例

### 样例输入 #1
```
0 1
9 3
hihehishe
1 7
1 12
2 10
```
### 样例输出 #1
```
e
0
r
```
## 提示

### 样例 1 解释

在该组样例的唯一一组测试数据中，$s=\texttt{hihehishe}$。

对 $s$ 进行一次修改后，$s$ 会变为 $\texttt{hishehershe}$，此时 $s$ 中的第 $7$ 个字符为 $\texttt{e}$ 且不存在第 $12$ 个字符。

对 $s$ 进行两次修改后，$s$ 会变为 $\texttt{hersheshersshe}$，此时 $s$ 中的第 $10$ 个字符为 $\texttt{r}$。

### 数据范围

对于所有测试数据，保证：

- $1 \le T \le 5$；
- $1 \le n,q \le 2\times10^5$；
- $s$ 中只包含小写字母；
- $1 \le k_i,x_i \le 10^9$。

|测试点编号|$n \le$|$q \le$|$k_i \le$|特殊性质|
|:---:|:---:|:---:|:---:|:---:|
|$1$|$200$|$2\times10^5$|$200$|AB|
|$2$|$200$|$2\times10^5$|$200$|A|
|$3$|$200$|$2\times10^5$|$200$|无|	
|$4$|$2000$|$2\times10^5$|$10^9$|AB|
|$5$|$2000$|$2\times10^5$|$10^9$|A|
|$6,7$|$2000$|$2\times10^5$|$10^9$|无|	
|$8$|$2\times10^5$|$2\times10^5$|$10^9$|AB|
|$9$|$2\times10^5$|$2\times10^5$|$10^9$|A|
|$10,11$|$2\times10^4$|$2\times10^4$|$10^9$|C|	
|$12$|$2\times10^5$|$2\times10^5$|$10^9$|C|	
|$13,14$|$2\times10^4$|$2\times10^4$|$10^9$|D|	
|$15$|$2\times10^5$|$2\times10^5$|$10^9$|D|	
|$16\sim18$|$2\times10^4$|$2\times10^4$|$10^9$|无|	
|$19,20$|$2\times10^5$|$2\times10^5$|$10^9$|无|	

- 特殊性质 A：若 $s_i=\texttt{i}$ 且 $i \ne n$，则 $s_{i+1} \ne \texttt{h}$。
- 特殊性质 B：若 $s_i=\texttt{i}$ 且 $i \ne n$，则 $s_{i+1} \ne \texttt{s}$。
- 特殊性质 C：保证任意时刻 $s$ 中 $\texttt{he}$ 子串的数量不大于 $3$。
- 特殊性质 D：保证 $k_i$ 都相同。


---

---
title: "篱莘龙"
layout: "post"
diff: 省选/NOI-
pid: P13842
tag: ['线段树', '扫描线']
---
# 篱莘龙
## 题目描述

Yuki 家里养着 $n$ 只奶龙，第 $i$ 只奶龙的攻击力为 $a_i$，防御力为 $b_i$。

对于第 $i$ 只奶龙和第 $j$ 只奶龙（$i\ne j$），如果 $a_i>b_j$，则第 $i$ 只奶龙会攻击第 $j$ 只奶龙。

你需要对于每个不大于 $n$ 的正整数 $k$ 求出，在第 $1$ 只奶龙到第 $k$ 只奶龙中，最多可以选择多少只奶龙，使得这些奶龙中不存在某只奶龙会攻击另一只奶龙。
## 输入格式

第一行包含一个正整数 $c$，表示测试点编号。样例满足 $c=0$。

第二行包含一个正整数 $n$。

接下来 $n$ 行，第 $i$ 行包含两个正整数 $a_i,b_i$。保证所有 $a_i,b_i$ 互不相同。
## 输出格式

输出 $n$ 行，第 $i$ 行包含一个整数，表示 $k=i$ 时的答案。
## 样例

### 样例输入 #1
```
0
3
1 6
3 2
5 4
```
### 样例输出 #1
```
1
2
2
```
## 提示

### 样例 1 解释

- $k=1$ 时显然只能选择第一只奶龙。
- $k=2$ 时可以选择前两只奶龙。
- $k=3$ 时，如果选择全部奶龙，则第三只奶龙会攻击第二只奶龙。所以答案最多为 $2$。

### 数据范围

对于所有测试数据，保证：

- $1 \le n \le 10^6$；
- $1 \le a_i,b_i \le 2n$，所有 $a_i,b_i$ 互不相同。

| 测试点编号  |     $n\le$     | 特殊性质 |
| :---------: | :------------: | :------: |
|     $1$     |      $20$      |    无    |
|  $2\sim 3$  |     $400$      |    无    |
|     $4$     |     $2000$     |    B     |
|  $5\sim 6$  |     $2000$     |    无    |
|     $7$     |     $10^5$     |    B     |
|     $8$     |     $10^5$     |    C     |
| $9\sim 11$  |     $10^5$     |    无    |
|    $12$     |     $10^6$     |    A     |
|    $13$     |     $10^6$     |    B     |
|    $14$     |     $10^6$     |    C     |
| $15\sim 17$ | $5\times 10^5$ |    无    |
| $18\sim 20$ |     $10^6$     |    无    |

- 特殊性质 A：保证 $a_i> b_i$。
- 特殊性质 B：保证 $a_i< b_i$。
- 特殊性质 C：保证只有不超过 $100$ 只奶龙满足 $a_i>b_i$。


---

---
title: "[USACO21OPEN] United Cows of Farmer John P"
layout: "post"
diff: 省选/NOI-
pid: P7530
tag: ['线段树', 'USACO', '2021', '扫描线']
---
# [USACO21OPEN] United Cows of Farmer John P
## 题目描述

农夫约翰合牛国（The United Cows of Farmer John，UCFJ）将要选派一个代表队参加国际牛学奥林匹克（International bOvine olympIad，IOI）。

有 $N$ 头奶牛参加了代表队选拔。她们站成一行，奶牛 $i$ 的品种为 $b_i$。

代表队将会由包含至少三头奶牛的连续区间组成——也就是说，对于满足 $1\le l<r\le N$ 且 $r−l\ge 2$ 的奶牛 
$l\dots r$。选定区间内的三头奶牛将会被指定为领队。出于法律原因，最边上的两头奶牛必须是领队。此外，为了避免种内冲突，每一名领队都必须与代表队的其他成员（包括领队）品种不同。

请帮助 UCFJ 求出（由于纳税原因）他们可以选派参加 IOI 的代表队的方法数。如果两个代表队拥有不同的成员或不同的领队，则被认为是不同的。 
## 输入格式

输入的第一行包含 $N$。

第二行包含 $N$ 个整数 $b_1,b_2,\dots,b_N$，均在范围 $[1,N]$ 之间。
## 输出格式

输出一行一个整数表示可能的代表队的数量。
## 样例

### 样例输入 #1
```
7
1 2 3 4 3 2 5
```
### 样例输出 #1
```
9
```
## 提示

#### 样例解释

每一代表队对应以下的一组领队：

$$(1,2,3),(1,2,4),(1,3,4),(1,4,7),(2,3,4),(4,5,6),(4,5,7),(4,6,7),(5,6,7).$$

#### 数据范围与约定

$1\le N\le 2\times 10^5$


---

---
title: "[JRKSJ R4] risrqnis"
layout: "post"
diff: 省选/NOI-
pid: P8146
tag: ['2022', '颜色段均摊（珂朵莉树 ODT）', '洛谷原创', 'O2优化', '分块', '扫描线', '根号分治']
---
# [JRKSJ R4] risrqnis
## 题目背景

![114514](https://cdn.luogu.com.cn/upload/image_hosting/0rezlv6r.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

**本题时间限制较长，请勿滥用评测资源。**
## 题目描述

给你一个长度为 $n$ 的序列 $a$，有 $q$ 次操作，初始有 $m$ 个空集 $S$，共有两种操作，如下：

- `1 l r k`，将 $l\sim r$ 加入集合 $S_k$，即 $S_k\gets S_k\cup\{x|l\le x\le r\}$；
- `2 l r k`，查询对于所有 $l\le i\le r$ 的 $a_i$ 中有多少个在集合 $S_k$ 中，即查询 $\displaystyle\sum_{i=l}^r[a_i\in S_k]$。
## 输入格式

输入均为非负整数。

第一行 $3$ 个数 $n,q,m$。\
第二行 $n$ 个数，其中第 $i$ 个数表示 $a_i$。\
接下来 $q$ 行，每行 $4$ 个数表示一次操作。
## 输出格式

输出均为非负整数。

对于每个 `2` 操作，输出一行表示答案。
## 样例

### 样例输入 #1
```
5 10 2
5 4 3 2 1
2 1 5 1
2 1 5 2
1 2 3 1
1 2 3 2
2 1 4 1
2 1 4 2
1 1 4 1
1 1 4 2
2 1 5 1
2 3 5 2
```
### 样例输出 #1
```
0
0
2
2
4
3
```
## 提示

### 数据规模
| $\text{Subtask}$ | $n,q\le$ | $m\le$ | 分值 | $\text{Time Limit}$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $10^6$ | $1$ | $30$ | $1500\text{ ms}$ |
| $2$ | $5\times 10^3$ | $3\times 10^5$ | $15$ | $1000\text{ ms}$ |
| $3$ | $10^5$ | $10^5$ | $15$ | $1500\text{ ms}$ |
| $4$ | $3\times 10^5$ | $10^9$ | $40$ | $3000\text{ ms}$ |

对于 $100\%$ 的数据，$1\le n,q\le 10^6$，$1\le m\le 10^9$，$1\le a_i\le 10^9$。

操作 $1$ 中 $1\le l\le r\le 10^9$，操作 $2$ 中 $1\le l\le r\le n$。所有操作中 $1\le k\le m$。

**没有一个 $\text{Subtask}$ 取到所有数据范围的最大值，各个 $\text{Subtask}$ 都有自己的限制。请阅读数据范围表。**

**本题输入文件较大，请使用恰当的读入方式。**
****

深夜，上条当麻的手机响起了收信声。随即，他来到了邮件所写的地方。第七学区的铁桥。

上条到达的时候，发信人早已经等在那了。

「御坂吗……？」

「你忘记的东西。」

她说着丢了什么过来。上条单手接住，发现那是个青娃的手机挂件。他沉入北水洋的时候这东西就应该不见了啊。它用来系到手机上的挂绳当初都粉碎了，现在却换成了其他颜色的绳子。

「好不容易找回来的，别再弄丢了哦。」

「不好意思。」

上条道了声谢，将它再次系到了手机上。

见状，美琴微微一笑。

那是似乎终于把什么东西回归原状而松了一口气的表情。

「我想你这个家伙应该不会一直呆在一个地方的吧…接下来该不会你又要去哪？」 

「算是吧。」

上条叹了口气。

「老实说虽然我一副淡定的表情，但实际上我也对究竟发生了什么一头雾水，只知道元凶的名字而已。不过这场骚动已经波及到了学园都市，而正在追查学园都市的我也被卷入其中，被我追查的学园都市同样被卷入……所以我也没办法置之不理了。」

美琴找他似乎就只是为了送挂饰而已。上条将手机放进了口袋。

既然没有了话题，那也只能分别了。

「再见了。」上条说道。

转身背对着美琴，准备离开铁桥，

准备离开这个由科学常识构筑的学园都市，大步迈向外面的领域，而少年的手，却被美琴抓住了。 

确确实实地，紧紧拉住想要飘然离开的少年。

在静止的上条耳边，传来了美琴的声音。

「但，这次你不会是一个人了。」 




---

