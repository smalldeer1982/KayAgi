---
title: "[CCC 2024 S4] Painting Roads"
layout: "post"
diff: 普及+/提高
pid: P10298
tag: ['图论', '2024', 'Special Judge', 'CCC（加拿大）', '生成树', '构造']
---
# [CCC 2024 S4] Painting Roads
## 题目描述

Kitchener 市的市长 Alanna 成功地改进了该市的道路规划。然而，来自 RedBlue 市的一位售货员仍然抱怨道路的颜色不够丰富。Alanna 的下一个任务就是粉刷一些道路。

Kitchener 市的道路规划可以表示为 $N$ 个十字路口和 $M$ 条道路，第 $i$ 条道路连接第 $u_i$ 个十字路口和第 $v_i$ 个十字路口。一开始所有道路都是灰色的。Alanna 想要把一些道路染成红色或者蓝色，满足以下条件：

- 对于每一条灰色道路，假设其连接十字路口 $u_i$ 和十字路口 $v_i$，一定存在一条从十字路口 $u_i$ 到十字路口 $v_i$ 的路径，满足路径上的道路颜色红色和蓝色交替出现，任何道路都不是灰色的。

为了降低城市的支出，Alanna 希望尽可能少地对道路进行染色。请帮助 Alanna 设计一个符合要求的染色方案。
## 输入格式

输入的第一行包含两个整数 $N$ 和 $M$（$1\leq N, M \leq 2 \times 10^5$）。

接下来 $M$ 行中的第 $i$ 行包含两个整数 $u_i$ 和 $v_i$ 表示存在一条连接十字路口 $u_i$ 和十字路口 $v_i$ 的道路（$1 \leq u_i, v_i \leq N$，$u_i \neq v_i$）。

任意两个十字路口之间至多存在一条道路。
## 输出格式

输出一个长度为 $M$ 的字符串，表示染色的方案。第 $i$ 个字符表示第 $i$ 条道路的颜色，`R` 表示红色，`B` 表示蓝色，`G` 表示灰色（未染色）。

注意你必须在满足条件的情况下最小化染色的道路数目。如果存在多个这样的染色方案，输出任意一个。
## 样例

### 样例输入 #1
```
5 7
1 2
2 4
5 2
4 5
4 3
1 3
1 4

```
### 样例输出 #1
```
BRGBBGG

```
### 样例输入 #2
```
4 2
1 2
3 4

```
### 样例输出 #2
```
BB

```
## 提示

**【样例 1 解释】**

十字路口以及有效的道路的示意图如下所示，该方案最小化了染色道路的数量。请注意，每条道路上的颜色显示为 R（红色）、B（蓝色）或 G（灰色）。

![](https://cdn.luogu.com.cn/upload/image_hosting/vwughkb3.png)

所有为染色的道路都满足条件：

- 第二条路标记为 $G_2$ 连接了十字路口 $2$ 和 $4$，路径 $2, 1, 4$ 上的道路被染上红色、蓝色。
- 第三条路标记为 $G_3$ 连接了十字路口 $5$ 和 $2$，路径 $5, 4, 1, 2$ 上的道路被染上红色、蓝色、红色。
- 第五条路标记为 $G_5$ 连接了十字路口 $4$ 和 $3$，路径 $4, 1, 3$ 上的道路被染上蓝色、红色。

**【样例 2 解释】**

请注意 Kitchener 的道路可能不是连通的。

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证 $1\leq N, M \leq 2 \times 10^5$，$1 \leq u_i, v_i \leq N$，$u_i \neq v_i$。

下面的表格显示了 $15$ 分的分配方案：

| 分值 | 附加条件 |
| :-: | :- |
| $2$ | 对任意 $1 \leq i < N$ 存在一条连接 $i$ 和 $i + 1$ 的道路（还可能存在其他道路） |
| $3$ | 图连通并且 $N = M$ |
| $3$ | 任何道路都不同时属于至少两个简单环（见下文定义） |
| $7$ | 无 |

定义：若用 $u \leftrightarrow v$ 表示一条连接 $u$ 和 $v$ 的道路，则称 $k \geq 3$ 且所有 $w_i$ 互不相同是序列 $w_1 \leftrightarrow w_2 \leftrightarrow \cdots \leftrightarrow w_k \leftrightarrow w_1$ 为简单环。


---

---
title: "「LAOI-12」MST?"
layout: "post"
diff: 普及+/提高
pid: P12375
tag: ['数学', '洛谷原创', 'O2优化', '生成树', '洛谷比赛']
---
# 「LAOI-12」MST?
## 题目背景

![](bilibili:BV1xw6mYEEaN)
## 题目描述

给定 $n,m$ 两个正整数，构造无重边**无自环**的一张连通无向图，共 $n$ 个结点和 $m$ 条边权分别为 $1\sim m$ 的边，使得其最小生成树的边权和最大。

你只需要输出最小生成树的边权和对 $998244353$ 取模的值即可。
## 输入格式

**本题有多组测试数据。**

第一行输入一个正整数 $T$，表示测试数据组数。

对于每组测试数据，共一行两个正整数 $n,m$。
## 输出格式

共 $T$ 行，对于每组数据输出最小生成树的边权和对 $998244353$ 取模的值即可。
## 样例

### 样例输入 #1
```
3
4 6
4 5
5 8
```
### 样例输出 #1
```
7
7
14
```
## 提示

### 样例解释

对于样例一中的第一组测试数据，构造如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/ngx4j1fr.png)

此时答案为 $1+2+4=7$。

### 数据范围

**本题采用捆绑测试。**

|子任务编号|$T$|$n$|特殊性质|分值|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$\le5$|$\le5$|无|$5$|
|$2$|$\le10^6$|$\le10^3$|无|$10$|
|$3$|$\le5$|$\le10^6$|无|$15$|
|$4$|$\le10^6$|$\le10^6$|无|$20$|
|$5$|$\le10^6$|$\le10^{18}$|$n=m$|$5$|
|$6$|$\le10^6$|$\le10^{18}$|无|$45$|

对于 $100\%$ 的测试数据，满足 $1\le T \le 10^6$，$4\le n\le m\le 10^{18}$，$m\le \frac{n\times(n-1)}{2}$。


---

---
title: "公路修建"
layout: "post"
diff: 普及+/提高
pid: P1265
tag: ['图论', '生成树']
---
# 公路修建
## 题目描述

某国有 $n$ 个城市，它们互相之间没有公路相通，因此交通十分不便。为解决这一“行路难”的问题，政府决定修建公路。修建公路的任务由各城市共同完成。

修建工程分若干轮完成。在每一轮中，每个城市选择一个与它最近的城市，申请修建通往该城市的公路。政府负责审批这些申请以决定是否同意修建。

政府审批的规则如下：

1. 如果两个或以上城市申请修建同一条公路，则让它们共同修建；
2. 如果三个或以上的城市申请修建的公路成环。如下图，A 申请修建公路 AB，B 申请修建公路 BC，C 申请修建公路 CA。则政府将否决其中最短的一条公路的修建申请； 
3. 其他情况的申请一律同意。

![](https://cdn.luogu.com.cn/upload/image_hosting/apng39qc.png)

一轮修建结束后，可能会有若干城市可以通过公路直接或间接相连。这些可以互相连通的城市即组成“城市联盟”。在下一轮修建中，每个“城市联盟”将被看作一个城市，发挥一个城市的作用。

当所有城市被组合成一个“城市联盟”时，修建工程也就完成了。

你的任务是根据城市的分布和前面讲到的规则，计算出将要修建的公路总长度。
## 输入格式

第一行一个整数 $n$，表示城市的数量。（$n \leq 5000$）

以下 $n$ 行，每行两个整数 $x$ 和 $y$，表示一个城市的坐标。（$-10^6 \leq x,y \leq 10^6$）

## 输出格式

一个实数，四舍五入保留两位小数，表示公路总长。（保证有唯一解）

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
6.47
```
## 提示

修建的公路如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/p0dtxt2l.png)


---

---
title: "兽径管理"
layout: "post"
diff: 普及+/提高
pid: P1340
tag: ['图论', '福建省历届夏令营', '排序', '生成树']
---
# 兽径管理
## 题目描述

约翰农场的牛群希望能够在 $N$ 个草地之间任意移动。草地的编号由 $1$ 到 $N$。草地之间有树林隔开。牛群希望能够选择草地间的路径，使牛群能够从任一 片草地移动到任一片其它草地。 牛群可在路径上双向通行。

牛群并不能创造路径，但是他们会保有及利用已经发现的野兽所走出来的路径（以下简称兽径）。每星期他们会选择并管理一些或全部已知的兽径当作通路。

牛群每星期初会发现一条新的兽径。他们接着必须决定管理哪些兽径来组成该周牛群移动的通路，使得牛群得以从任一草地移动到任一草地。牛群只能使用当周有被管理的兽径做为通路。

牛群希望他们管理的兽径长度和为最小。牛群可以从所有他们知道的所有兽径中挑选出一些来管理。牛群可以挑选的兽径与它之前是否曾被管理无关。

兽径决不会是直线，因此连接两片草地之间的不同兽径长度可以不同。 此外虽然两条兽径或许会相交，但牛群非常的专注，除非交点是在草地内，否则不会在交点换到另外一条兽径上。

在每周开始的时候，牛群会描述他们新发现的兽径。如果可能的话，请找出可从任何一草地通达另一草地的一组需管理的兽径，使其兽径长度和最小。

## 输入格式

输入的第一行包含两个用空白分开的整数 $N$ 和 $W$。$W$ 代表你的程序需要处理的周数。

以下每处理一周，读入一行数据，代表该周新发现的兽径，由三个以空白分开的整数分别代表该兽径的两个端点（两片草地的编号) 与该兽径的长度。一条兽径的两个端点一定不同。

## 输出格式

每次读入新发现的兽径后，你的程序必须立刻输出一组兽径的长度和，此组兽径可从任何一草地通达另一草地，并使兽径长度和最小。如果不能找到一组可从任一草地通达另一草地的兽径，则输出 $-1$。

## 样例

### 样例输入 #1
```
4 6	 	 
1 2 10	 	 
1 3 8	 	 
3 2 3	 	 
1 4 3	 	 
1 3 6	 	 
2 1 2	 	 

```
### 样例输出 #1
```
-1
-1
-1
14
12
8
```
## 提示

### 样例解释

对于每一周，

- 第一周时 $4$ 号草地不能与其他草地连通，输出 $-1$；
- 第二周时 $4$ 号草地不能与其他草地连通，输出 $-1$；
- 第三周时 $4$ 号草地不能与其他草地连通，输出 $-1$；
- 第四周时可以选择兽径 $(1,4,3),(1,3,8)$ 和 $(3,2,3)$；
- 第五周时可以选择兽径 $(1,4,3),(1,3,6)$ 和 $(3,2,3)$；
- 第六周时可以选择兽径 $(1,4,3),(2,1,2)$ 和 $(3,2,3)$。


### 数据范围及约定

对于全部数据，$1\le N\le 200$，$1 \le W \le 6000$，兽径的长度不超过 $10^4$ 且为正整数。


---

---
title: "[HNOI2006] 公路修建问题"
layout: "post"
diff: 普及+/提高
pid: P2323
tag: ['2006', '二分', '并查集', '各省省选', '湖南', 'Special Judge', '生成树']
---
# [HNOI2006] 公路修建问题
## 题目描述

OI island 是一个非常漂亮的岛屿，自开发以来，到这儿来旅游的人很多。然而，由于该岛屿刚刚开发不久，所以那里的交通情况还是很糟糕。所以，OIER Association 组织成立了，旨在建立 OI island 的交通系统。

OI island 有 $n$ 个旅游景点，不妨将它们从 $1$ 到 $n$ 标号。现在，OIER Association 需要修公路将这些景点连接起来。一条公路连接两个景点。公路有，不妨称它们为一级公路和二级公路。一级公路上的车速快，但是修路的花费要大一些。

OIER Association 打算修 $n-1$ 条公路将这些景点连接起来（使得任意两个景点之间都会有一条路径）。为了保证公路系统的效率， OIER Association 希望在这 $n-1$ 条公路之中，至少有 $k$ 条 $(0 \le k \le n-1)$ 一级公路。OIER Association 也不希望为一条公路花费的钱。所以，他们希望在满足上述条件的情况下，花费最多的一条公路的花费尽可能的少。

而你的任务就是，在给定一些可能修建的公路的情况下，选择 $n-1$ 条公路，满足上面的条件。
## 输入格式

文件第一行有三个数 $n(1 \le n \le 10000)$，$k(0 \le k \le n-1),m(n-1 \le m \le 20000)$，这些数之间用空格分开。$N$ 和 $k$ 如前所述，$m$ 表示有 $m$ 对景点之间可以修公路。

以下的 $m-1$ 行，每一行有 $4$ 个正整数 $a,b,c_1,c_2$，（$1 \le a,b \le n,a \ne b,1 \le c_2 \le c_1 \le 30000$），表示在景点 $a$ 与 $b$ 之间可以修公路，如果修一级公路，则需要 $c_1$ 的花费，如果修二级公路，则需要 $c_2$ 的花费。

**在实际评测时，将只会有 $m-1$ 行公路**

## 输出格式

输出第一行有一个数据，表示花费最大的公路的花费。

接下来的 $n-1$ 行，每行有两个正整数 $t$ 和 $p$，$t$ 和 $p$ 表示在输入的第 $t$ 对（按照输入的顺序，从 $1$ 开始标号）景点之间修建 $p$ 级公路。

$n-1$ 条公路的输出必须按 $t$ 的大小递增，如果有多个方案使花费最大的公路花费最小，那么输出任意一个都可以。
## 样例

### 样例输入 #1
```
4 2 5 
1 2 6 5
1 3 3 1
2 3 9 4
2 4 6 1
```
### 样例输出 #1
```
6 
1 1 
2 1 
4 1
```


---

---
title: "[USACO16DEC] Moocast G"
layout: "post"
diff: 普及+/提高
pid: P2847
tag: ['2016', '二分', 'USACO', '生成树']
---
# [USACO16DEC] Moocast G
## 题目描述

Farmer John's $N$ cows ($1 \leq N \leq 1000$) want to organize an emergency "moo-cast" system for broadcasting important messages among themselves.

Instead of mooing at each-other over long distances, the cows decide to equip themselves with walkie-talkies, one for each cow. These walkie-talkies each have a limited transmission radius, but cows can relay messages to one-another along a path consisting of several hops, so it is not necessary for every cow to be able to transmit directly to every other cow.

The cows need to decide how much money to spend on their walkie-talkies. If they spend $X$, they will each get a walkie-talkie capable of transmitting up to a distance of $\sqrt{X}$. That is, the squared distance between two cows must be at most $X$ for them to be able to communicate.

Please help the cows determine the minimum integer value of $X$ such that a broadcast from any cow will ultimately be able to reach every other cow.

## 输入格式

The first line of input contains $N$.

The next $N$ lines each contain the $x$ and $y$ coordinates of a single cow. These are both integers in the range $0 \ldots 25,000$.

## 输出格式

Write a single line of output containing the integer $X$ giving the minimum amount the cows must spend on walkie-talkies.

## 样例

### 样例输入 #1
```
4
1 3
5 4
7 2
6 1
```
### 样例输出 #1
```
17

```
## 提示

感谢@MrMorning 提供翻译

## 题目翻译

### 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 1000$）希望组织一个紧急的“哞播”系统，用于在它们之间广播重要消息。

为了避免在长距离上互相哞叫，奶牛们决定为自己配备对讲机，每头奶牛一个。这些对讲机每个都有一个有限的传输半径，但奶牛们可以通过多次跳跃的路径中继消息，因此并非每头奶牛都需要能够直接与其他每头奶牛通信。

奶牛们需要决定在对讲机上花费多少钱。如果它们花费 $X$，每头奶牛将获得一个能够传输到 $\sqrt{X}$ 距离的对讲机。也就是说，两头奶牛之间的平方距离必须不超过 $X$，它们才能通信。

请帮助奶牛们确定 $X$ 的最小整数值，使得从任何一头奶牛发出的广播最终能够到达其他所有奶牛。

### 输入格式

输入的第一行包含 $N$。

接下来的 $N$ 行每行包含一头奶牛的 $x$ 和 $y$ 坐标。这些坐标都是 $0 \ldots 25,000$ 范围内的整数。

### 输出格式

输出一行，包含整数 $X$，表示奶牛们在对讲机上必须花费的最小金额。


---

---
title: "[USACO13FEB] Tractor S"
layout: "post"
diff: 普及+/提高
pid: P3073
tag: ['搜索', '2013', '二分', 'USACO', '并查集', '排序', '生成树']
---
# [USACO13FEB] Tractor S
## 题目描述

One of Farmer John's fields is particularly hilly, and he wants to purchase a new tractor to drive around on it.  The field is described by an N x N grid of non-negative integer elevations (1 <= N <= 500).  A tractor capable of moving from one grid cell to an adjacent cell (one step north, east, south, or west) of height difference D costs exactly D units of money.

FJ would like to pay enough for his tractor so that, starting from some grid cell in his field, he can successfully drive the tractor around to visit at least half the grid cells in the field (if the number of total cells in the field is odd, he wants to visit at least half the cells rounded up).  Please help him compute the minimum cost necessary for buying a tractor capable of this task.

## 输入格式

\* Line 1: The value of N.

\* Lines 2..1+N: Each line contains N space-separated non-negative integers (each at most 1 million) specifying a row of FJ's field.





## 输出格式

\* Line 1: The minimum cost of a tractor that is capable of driving around at least half of FJ's field.



## 样例

### 样例输入 #1
```
5 
0 0 0 3 3 
0 0 0 0 3 
0 9 9 3 3 
9 9 9 3 3 
9 9 9 9 3 

```
### 样例输出 #1
```
3 

```
## 题目翻译

题目描述

FJ有块农田太崎岖了，他要买一辆新拖拉机才能在这里巡视。这块农田由N x N个格子的非负整数表示高度(1<=N<=500)。拖拉机从当前格子走到相邻格子（东、南、西、北四个方向）的代价为高度差D，则FJ驶过这两个格子的拖拉机最少也要值D块钱。

FJ愿意花足够的钱买一辆新的拖拉机使得他能以最小的高度差走遍所有格子的一半(如果格子总数是奇数，那么一半的值为四舍五入的值)。因为FJ很懒，所以他找到你帮他编程计算他最小需要花多少钱买到符合这些要求的拖拉机。

输入输出格式

输入格式：

第一行为一个整数N

第2到N+1行每行包含N个非负整数（不超过1,000,000），表示当前格子的高度。

输出格式：

共一行，表示FJ买拖拉机要花的最小价钱。


---

---
title: "[JSOI2010] 部落划分"
layout: "post"
diff: 普及+/提高
pid: P4047
tag: ['2010', '二分', '并查集', '各省省选', '江苏', '生成树']
---
# [JSOI2010] 部落划分
## 题目描述

聪聪研究发现，荒岛野人总是过着群居的生活，但是，并不是整个荒岛上的所有野人都属于同一个部落，野人们总是拉帮结派形成属于自己的部落，不同的部落之间则经常发生争斗。只是，这一切都成为谜团了——聪聪根本就不知道部落究竟是如何分布的。

不过好消息是，聪聪得到了一份荒岛的地图。地图上标注了 $n$ 个野人居住的地点（可以看作是平面上的坐标）。我们知道，同一个部落的野人总是生活在附近。我们把两个部落的距离，定义为部落中距离最近的那两个居住点的距离。聪聪还获得了一个有意义的信息——这些野人总共被分为了 $k$ 个部落！这真是个好消息。聪聪希望从这些信息里挖掘出所有部落的详细信息。他正在尝试这样一种算法：

对于任意一种部落划分的方法，都能够求出两个部落之间的距离，聪聪希望求出一种部落划分的方法，使靠得最近的两个部落尽可能远离。

例如，下面的左图表示了一个好的划分，而右图则不是。请你编程帮助聪聪解决这个难题。


![](https://cdn.luogu.com.cn/upload/pic/30573.png)
## 输入格式

输入文件第一行包含两个整数 $n$ 和 $k$，分别代表了野人居住点的数量和部落的数量。

接下来 $n$ 行，每行包含两个整数 $x$，$y$，描述了一个居住点的坐标。
## 输出格式

输出一行一个实数，为最优划分时，最近的两个部落的距离，精确到小数点后两位。
## 样例

### 样例输入 #1
```
4 2
0 0
0 1
1 1
1 0

```
### 样例输出 #1
```
1.00

```
### 样例输入 #2
```
9 3
2 2
2 3
3 2
3 3
3 5
3 6
4 6
6 2
6 3
```
### 样例输出 #2
```
2.00
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2 \leq k \leq n \leq 10^3$，$0 \leq  x, y \leq 10^4$。


---

---
title: "[USACO16FEB] Fenced In G"
layout: "post"
diff: 普及+/提高
pid: P6171
tag: ['贪心', '2016', 'USACO', '生成树']
---
# [USACO16FEB] Fenced In G
## 题目背景

*本题和 [白金组同名题目](/problem/P3141) 在题意上一致，唯一的不同是数据范围。*
## 题目描述

Farmer John 意识到他的奶牛最近患上了一种恐惧症（害怕过于开阔的空间）。为了减少放牧的恐惧，FJ 决定在牧场中建一些水平和竖直方向的栅栏来将牧场分成若干个小区域。

整个牧场是一个矩形，两个角的坐标分别为 $(0,0)$ 和 $(A,B)$。FJ 在 $a_1,\ldots ,a_n$ 这 $n$ 个两两不同的位置建造了竖直方向的栅栏，每个栅栏从 $(a_i,0)$ 到 $(a_i,B)$；FJ 在 $b_1,\ldots ,b_m$ 这 $m$ 个两两不同的位置建造了水平方向的栅栏，每个栅栏从 $(0,b_i)$ 到 $(A,b_i)$。竖直方向的栅栏和水平方向的栅栏两两相交，将整个牧场分割成 $(n+1)(m+1)$ 个区域。

不幸的是，FJ 忘记了在栅栏上开门，奶牛都只能被困在一个个的小区域里！他想通过去掉一些栅栏来解决这个问题。他一次可以选择两个相邻的区域，将隔离这两个区域的栅栏去掉。FJ 的目标是让奶牛能够抵达牧场的任意一个地方。

这是一个例子：

```plain
+---+--+
|   |  |
+---+--+
|   |  |
|   |  |
+---+--+
```

去掉一些栅栏后的效果是这样的：

```plain
+---+--+
|      |
+---+  +
|      |
|      |
+---+--+
```

为了降低工程量，FJ 当然希望拆除的栅栏长度最短。
## 输入格式

第一行四个整数 $A,B,n,m$，保证 $1 \leq n,m \leq 2000$，$1 \leq A,B \leq 10^9$。

接下来 $n$ 行，第 $i$ 行一个整数 $a_i$，保证 $0 \lt a_i \lt A$。

接下来 $m$ 行，第 $i$ 行一个整数 $b_i$，保证 $0 \lt b_i \lt B$。
## 输出格式

输出拆除栅栏的最小长度。**答案需要用 64 位带符号整数存储。**
## 样例

### 样例输入 #1
```
15 15 5 2
2
5
10
6
4
11
3
```
### 样例输出 #1
```
44
```


---

---
title: "[USACO22FEB] Moo Network G"
layout: "post"
diff: 普及+/提高
pid: P8191
tag: ['贪心', 'USACO', '2022', '生成树']
---
# [USACO22FEB] Moo Network G
## 题目描述

Farmer John's $N$ cows $(1≤N≤10^5)$ are spread far apart on his farm and would like to build a communication network so they can more easily exchange electronic text messages (all of which of course contain variations of "moo").

The ith cow is located at a distinct location $(x_i,y_i)$ where $0≤x_i≤10^6$ and $0≤y_i≤10$. The cost of building a communication link between cows $i$ and $j$ is the squared distance between them: $(x_i-x_j)^2+(y_i-y_j)^2$.

Please calculate the minimum cost required to build a communication network across which all the cows can communicate. Two cows can communicate if they are directly connected by a link, or if there is a sequence of links along which their message can travel.

**Note: the time limit for this problem is 4s, twice the default.**
## 输入格式

The first line of input contains $N$, and the next $N$ lines each describe the $x$ and $y$ coordinates of a cow, all integers.
## 输出格式

Please output the minimum cost of a network that will allow all cows to communicate. Note that this cost might be too large to fit into a 32-bit integer and may require use of 64-bit integers (e.g., "long long" integers in C++).
## 样例

### 样例输入 #1
```
10
83 10
77 2
93 4
86 6
49 1
62 7
90 3
63 4
40 10
72 0
```
### 样例输出 #1
```
660
```
## 提示

【数据范围】

- Test cases 2-3 satisfy $N≤1000$.
- Test cases 4-15 satisfy no additional constraints.
## 题目翻译

## 题目描述


农夫约翰有 $N$ 头牛（$1\le N\le10^5$） 它们在农场里分布的极其的远，因此希望你建立一个通讯网络，便于它们更容易地交换电子短信（当然，这些短信都包含 `moo` 的变形体，即数字）

第 $i$ 头牛位于位置 $(x_i，y_i)$ 其中 $0\le x\le 10^6$, $0\le y\le 10$. 在牛 $i$ 与牛 $j$ 之间建立通信链路的成本是它们之间的欧几里德距离的平方，即 $(x_i-x_j)^2+(y_i-y_j)^2$


请聪明的你构建一个所有奶牛都能交流的最低成本的通信网络。如果两头奶牛通过一条链接直接连接或者它们的信息可以沿着一条链接传播，那么认为他们可以通信。

#### 注意 此问题时间限制为4秒

## 输入格式
第一行输入为 $N$，接下来 $N$ 行分别描述奶牛的位置 $(x,y)$ 均为整数
## 输出格式
请输出允许所有奶牛通信的网络的最低成本。请注意，此开销可能太大，无法放入 32 位整数中，并且可能需要使用 64 位整数（例如，C++中的“long long”）。

### 说明/提示 

测试点 2~3 满足 $N\le1000$。

测试点 4~15 没有特殊限制。


---

---
title: "生成树"
layout: "post"
diff: 普及+/提高
pid: P9619
tag: ['数学', '生成树', 'Prüfer 序列']
---
# 生成树
## 题目背景

> 我们是未成熟的斗士 现在绝不认输
>
> 我们是未成熟的梦想家 现在绝不哭泣
## 题目描述

现给定一个无向完全图 $G(V,E)$ 和一个长度为 $|V|$ 的权值数组 $a$．$a_i$ 表示编号为 $i$ 的节点的权值．

定义一条边 $e(u,v)$ 的边值为 $val(e)$，满足 $val(e)=a_u\oplus a_v$，也就是边连接的两个节点的权值的异或和；定义 $G$ 的一个生成树 $T(V,E_t)$ 的权值为 $Val(T)$，满足 $Val(T)=\sum_{e\in E_t}val(e)$，也就是树上边的边权和．

您需要求出 $\sum_{T}Val(T)$．即 $G$ 中所有不同生成树的权值的和．

我们认为两棵生成树是不同的，当且仅当两棵树的边集 $E_t$ 不完全相同，即至少存在一条边，满足其仅属于两棵生成树中的其中一棵．
## 输入格式

包括两行．

第一行是一个整数 $n$，表示 $|V|$，即节点个数．

第二行是 $n$ 个整数，依次为 $a_1\sim a_n$．
## 输出格式

一行一个整数．表示你的答案对 $998244353$ 取模．
## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
6
1 1 4 5 1 4
```
### 样例输出 #2
```
19008
```
### 样例输入 #3
```
10
1 1 4 5 1 4 1 9 1 9
```
### 样例输出 #3
```
567022588
```
## 提示

### 样例 #1 说明：
考虑一共存在三个生成树 $\{1-2-3\},\{1-3-2\},\{3-1-2\}$．

它们的权值分别为 $(1\oplus 2)+(2\oplus 3)=4,(1\oplus 3)+(3\oplus 2)=3,(3\oplus 1)+(1\oplus 2)=5$．

有 $4+3+5=12$．

### 数据点约束
保证对于所有数据，$1\le n\le 10^6$，$0\le a_i\le 10^9$．
|测试点编号|数据范围|特殊性质|
|:-:|:-:|:-:|
|$1$||所有 $a_i$ 相等|
|$2\sim 5$|$n\le 4$||
|$6\sim 10$|$n\le 300$||
|$11\sim 12$|$n\le 5\times 10^4$|$a_i=[i=1]$|
|$11\sim 15$|$n\le 5\times 10^4$||
|$16\sim 20$|||


---

---
title: "[KMOI R1] 军事行动"
layout: "post"
diff: 普及+/提高
pid: P9709
tag: ['O2优化', '广度优先搜索 BFS', '生成树']
---
# [KMOI R1] 军事行动
## 题目背景

$$\blue{他们来了。}$$

$$\purple{集结军队，干掉他们，一个不留。}$$

$$\blue{是！}$$
## 题目描述

喵星边境局势愈发紧张，导致发生边境冲突。喵星军队总司令小袁立即对 $Y$ 星采取军事行动。

整个宇宙可以看作一个平面直角坐标系，城市 $1,2,\dots,n$ 的坐标分别为 $(x_1,y_1),(x_2,y_2),\dots(x_n,y_n)$。

现在小袁率领的**若干支**舰队（可以理解为小袁的军事力量是无限的）驻扎在边境要塞，城市 $1$ 处。他的舰队会进行以下移动：

- 如果舰队的坐标为 $(x,y)$，那么一天之后它可以移动到 $(x-1,y+2)$ 或 $(x+1,y+2)$ 或 $(x+2,y+1)$ 或 $(x-2,y+1)$ 或 $(x-1,y-2)$ 或 $(x+1,y-2)$ 或 $(x+2,y-1)$ 或 $(x-2,y-1)$ 处。

其中环绕在外的还有一条小行星带，当舰队的坐标  $(x,y)$ 且 $x\le 0$ 或 $y\le 0$ 或 $m < x$ 或 $m < y$ 时，舰队就会撞到小行星带。这是小袁所不想看到的。

现在小袁要攻打城市 $2,3,\dots,n$，每一次他都会从一个**已经占领**的城市（城市 $1$ 也算），派出舰队前往城市 $i$ 并攻打它，舰队**到达之后的第二天**城市 $i$ 就被攻占了。

特别的，小袁在一个舰队**前往攻打或攻打一个城市**的时候不会派出另外一支舰队，在**攻占一座城市后当天**可以立即派出另外一支舰队。

小袁想问，最少要花多少时间才能攻占所有的城市。

**攻打顺序可以不按照 $2,3\dots n$ 的顺序。**
## 输入格式

第一行一个整数 $n,m$，表示城市个数和小行星带的范围。

接下来 $n$ 行，每一行两个正整数 $(x_i,y_i)$，表示城市 $i$ 的坐标。**保证 $1\le x_i,y_i \le m$**。
## 输出格式

一个整数 $ans$，表示最少要花的时间。
## 样例

### 样例输入 #1
```
2 20
1 1
1 3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 150
1 2
2 4
4 3
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
10 10
1 4
2 3
2 6
3 6
10 3
1 5
4 2
5 3
2 8
9 2
```
### 样例输出 #3
```
23
```
### 样例输入 #4
```
查看附件的 example4.in
```
### 样例输出 #4
```
查看附件的 example4.out
```
## 提示

## 样例一解释：

舰队在第一天来到了 $(3,2)$ 的位置，第二天到达了城市 $2$ 的位置，第三天占领了城市 $2$。总共花了 $3$ 天。

## 样例二解释：

舰队在第一天到达了城市 $2$ 的位置，第二天占领了城市 $2$。第三天到达了城市 $3$ 的位置，第四天占领了城市 $3$。总共花了 $4$ 天。

## 数据范围

**本题采用 Subtask 捆绑测试。**

|子任务编号|  测试点编号| $n$ | $m$ |特殊性质|分值|
|:-----:| :----------: | :----------: | :----------: | :----------: |:---:|
|$1$| $1\sim2$ | $1\le n\le 7$ |$4\le m\le 7$|无|$10$|
|$2$| $3\sim7$ | $1\le n\le 200$ |$4\le m\le 70$|无|$25$|
|$3$| $8\sim9$ | $1\le n\le 150$ |$4\le m\le 150$|有|$15$|
|$4$| $10\sim20$ | $1\le n\le 2000$ |$4\le m\le 150$|无|$50$|

特殊性质：对于每一个 $1\le i\le n-1$，都有 $x_i = x_{i+1}$。

**数据严格保证不会有不同的城市拥有相同的坐标。**


---

