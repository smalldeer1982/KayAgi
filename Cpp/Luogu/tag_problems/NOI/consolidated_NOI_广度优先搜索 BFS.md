---
title: "[GCJ Farewell Round #4] Hey Google, Drive!"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12963
tag: ['2023', '广度优先搜索 BFS', 'Google Code Jam']
---
# [GCJ Farewell Round #4] Hey Google, Drive!
## 题目描述

The Google Assistant and Android Auto teams are collaborating on a new prototype car that can be driven via voice commands. The early prototype works through a phone connected to a car simulator. Unfortunately, one of the early testers dropped their phone in the toilet, damaging the microphone and making it harder to use the new feature. Since they do not want to miss out on the opportunity, they want your help to use it anyway.

The early prototype moves on a simple grid of $\mathbf{R}$ rows and $\mathbf{C}$ columns and only understands 4 very simple voice commands: north, south, east, and west. Each command makes the car try to move exactly one cell in the corresponding direction. Because of the microphone issues, however, the system may mishear and interchange north and south, and separately, east and west. That means that a command of north may make the car move north or south, a command of south may make the car move south or north, and similarly both commands east and west may make the car move east or west when issued. In all cases, both movement options can happen with equal probability $(1 / 2)$.

The tester set up a driving grid such that each cell can contain either a wall, a hazard, or be empty. If a command would make the car move into a wall, or outside the grid, it does nothing instead. If a command makes the car move into a hazard, the car cannot execute any more commands.

The tester has marked some empty cells of the grid as interesting starts and others as interesting finishes. A pair of an interesting start and an interesting finish is drivable if there is a strategy to drive the car through voice commands from the start that makes it end at the finish with probability at least $1-10^{-100}$. A strategy can choose which command to issue and when to stop depending on the outcome of the previous commands. Notice that if the car moves into a hazard it stops moving, so it cannot make it to the finish. The tester wants your help finding the list of all drivable pairs.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing two integers $\mathbf{R}$ and $\mathbf{C}$, the number of rows and columns of the grid. Then, $\mathbf{R}$ lines follow containing a string of $\mathbf{C}$ characters each. The $j$-th character on the $i$-th of these lines $\mathbf{G}_{\mathbf{i}, \mathbf{j}}$ represents the grid in the $i$-th row and $j$-th column as follows:

*   A period (. ) represents an uninteresting empty cell.
*   A hash symbol (#) represents a cell containing a wall.
*   An asterisk (*) represents a cell containing a hazard.
*   An English lowercase letter (a through z) represents an empty cell that is an interesting start.
*   An English uppercase letter (A through z) represents an empty cell that is an interesting finish.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is NONE if there are no drivable pairs. Otherwise, $y$ must be a series of 2 character strings separated by spaces, representing all drivable pairs with the start letter first and the finish letter second, in alphabetical order.
## 样例

### 样例输入 #1
```
4
1 2
aZ
4 4
a..c
**.*
.Y.#
bX#Z
2 2
a*
*Z
2 7
a*bcd*.
...*F#.
```
### 样例输出 #1
```
Case #1: aZ
Case #2: aY bX bY cY
Case #3: NONE
Case #4: dF
```
## 提示

**Sample Explanation**

In Sample Case #1, simply repeating the west command until reaching the finish is a viable strategy. Each time there is a $1 / 2$ probability of reaching the finish and a $1 / 2$ probability of staying in the same place. Thus, the probability of not reaching the finish in $10^{101}$ or fewer steps is $2^{-10^{101}}<10^{-10^{100}}$.

In Sample Case #2 a similar strategy as in Sample Case #1 can be used to get the car from any position in the top row (1) to any other with probability as high as desired, and similarly for all non-wall positions in the third row from the top (2). Analogously, but using the south command, the car can move between non-wall positions on the third column from the left (3).

From both a and c we can use (1) to get to the third column from the left, then (3) to get right next to $\mathrm{Y}$ and then (2) to get to $\mathrm{Y}$ making both $\mathrm{aY}$ and $\mathrm{cY}$ drivable. Notice, however, that safely using the north or south commands from the third row can only be done in the third column, or otherwise the car may go into a hazard. Therefore, there is no safe way to move the car from the third to the fourth row, making $\mathrm{aX}$ and $\mathrm{cX}$ not drivable.

From $\mathrm{b}$, however, the car can use a similar strategy to get to $\mathrm{x}$, and from $\mathrm{x}$ the car can get to $\mathrm{Y}$ by using the north or south command repeatedly (and stop when reaching $\mathrm{Y}$, never risking going into the hazard above).

Finally, the finish $\mathrm{z}$ is completely isolated, so it cannot be part of a drivable pair.

In Sample Case #3, every path from the interesting start to the interesting finish goes through a hazard, which makes the pair not drivable.

In Sample Case #4, only the interesting start $\mathrm{d}$ has a viable strategy to get to the finish $\mathrm{F}$.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $\mathbf{G}_{\mathbf{i}, \mathbf{j}}$ is either a period (.), a hash symbol (#), an asterisk (*) or a lowercase or uppercase English letter, for all $i, j$.
- The set $\left\{\mathbf{G}_{\mathbf{i}, \mathbf{j}}\right.$ for all $\left.i, j\right\}$ contains at least 1 lowercase and at least 1 uppercase English letter.
- Each lowercase and uppercase letter appears at most once among all $\mathbf{G}_{\mathbf{i}, \mathbf{j}}$.

**Test Set 1 (5 Pts, Visible Verdict)**

- $1 \leq \mathbf{R} \leq 20$.
- $1 \leq \mathbf{C} \leq 20$.

**Test Set 2 (17 Pts, Hidden Verdict)**

- $1 \leq \mathbf{R} \leq 100$.
- $1 \leq \mathbf{C} \leq 100$.


---

---
title: "[GCJ 2016 Finals] Map Reduce"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13209
tag: ['贪心', '2016', 'Special Judge', '广度优先搜索 BFS', '构造', 'Ad-hoc', 'Google Code Jam']
---
# [GCJ 2016 Finals] Map Reduce
## 题目描述

Ben the brilliant video game designer is trying to design maps for his upcoming augmented-reality mobile game. Recently, he has created a map which is represented as a matrix of $\mathbf{R}$ rows and $\mathbf{C}$ columns. The map consists of a bunch of `.` characters representing empty squares, a bunch of `#` characters representing impassable walls, a single start position represented by `S` and a single finish position represented by `F`. For example, the map could look like:

```
#############
#S..#..##...#
###.##..#.#F#
#...##.##.###
#.#.........#
#############
```

In Ben's game, a path is a sequence of steps (up, down, left or right) to go from one cell to another while not going through any impassable walls.

Ben considers a good map to have the following properties:

- There is a path between any two empty squares (including the start and finish positions).
- To preserve structural integrity, impassable walls must meet at edges and not just corners. For every $2 \times 2$ region in the map, if the region contains exactly two walls, then those walls are either in the same row or the same column. In other words, there is no $2 \times 2$ region where the walls are in one of these two configurations:
  ```
  #.   .#
  .#   #.
  ```
- The boundary consists of only impassable walls. A cell is considered part of the boundary if it is in the uppermost/lowermost rows or if it is in the leftmost/rightmost columns.

The distance of the shortest path is the minimum number of steps required to reach the finish position from the start position. For instance, the shortest path in the above example takes $17$ steps.

Being such a clever mapmaker, Ben realized that he has created a map that is too hard for his friends to solve. He would like to reduce its difficulty by removing some of the impassable walls. In particular, he wants to know whether it is possible to remove zero or more impassable walls from his map such that the shortest path from start to finish takes exactly $\mathbf{D}$ steps, and that the resulting map is still good. Note that it is not enough to simply find a path with $\mathbf{D}$ steps; $\mathbf{D}$ must be the number of steps in the shortest path.

For example, if $\mathbf{D} = 15$, we could remove the impassable wall directly below the finish position to get a good solution.

```
#############
#S..#..##...#
###.##..#.#F#
#...##.##.#.#
#.#.........#
#############
```

There is no solution if $\mathbf{D}=5$.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing three space-separated integers $\mathbf{R}$, $\mathbf{C}$ and $\mathbf{D}$: the number of rows and columns in the map, and the desired number of steps in the shortest path from start to finish after possibly removing impassable walls. $\mathbf{R}$ lines follow, each consisting of $\mathbf{C}$ characters (either ., #, S or F) representing Ben's map.

It is guaranteed that the map is good, as described in the problem statement.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the word POSSIBLE or IMPOSSIBLE, depending on whether the shortest path can be made equal to $\mathbf{D}$ by removing some number of walls such that the map is still good. If it is possible, output $\mathbf{R}$ more lines containing $\mathbf{C}$ characters each, representing the new map. In your output, replace the # characters for removed walls (if any) with . characters.

If multiple solutions are possible, you may output any of them.
## 样例

### 样例输入 #1
```
3
6 13 15
#############
#S..#..##...#
###.##..#.#F#
#...##.##.###
#.#.........#
#############
5 8 3
########
#S.....#
####...#
#F.....#
########
4 10 11
##########
#S#...#.F#
#...#...##
##########
```
### 样例输出 #1
```
Case #1: POSSIBLE
#############
#S..#..##...#
###.##..#.#F#
#...##.##.#.#
#.#.........#
#############
Case #2: IMPOSSIBLE
Case #3: POSSIBLE
##########
#S#...#.F#
#...#...##
##########
```
## 提示

**Sample Explanation**

The sample output displays one set of answers to the sample cases. Other answers may be possible.

Sample case #1 is the example in the problem statement.

In sample case #2, it is possible to remove walls to make the distance of the shortest path either 2 or 4, for example. However, there is no way to make the distance of the shortest path exactly 3.

In sample case #3, the shortest path already takes 11 steps to begin with, so there is no need to reduce the difficulty of the map.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- Each test case contains exactly one $\mathbf{S}$ and exactly one $\mathbf{F}$.
- The input file is at most 3MB in size.

**Small dataset (Test Set 1 - Visible)**

- Time limit: ~~60~~ 15 seconds.
- $3 \leq \mathbf{R} \leq 40$.
- $3 \leq \mathbf{C} \leq 40$.
- $1 \leq \mathbf{D} \leq 1600$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~300~~ 75 seconds.
- $3 \leq \mathbf{R} \leq 1000$.
- $3 \leq \mathbf{C} \leq 1000$.
- $1 \leq \mathbf{D} \leq 10^6$.
- NOTE: The Large output breaks the usual cap on Code Jam output size, but you can upload it as normal.


---

---
title: "[POI 2013] CEN-Price List"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3547
tag: ['2013', 'POI（波兰）', '广度优先搜索 BFS']
---
# [POI 2013] CEN-Price List
## 题目描述

Railway has always been the most popular mean of transport in Byteotia.

Out of $n$ towns in the land, $m$ pairs are connected by track segments    belonging to Byteotian State Railways (BSR).

The tracks do not cross outside of towns, and may lead through picturesque    bridges and somewhat less picturesque tunnels.

The ticket for travelling between any two towns    directly connected by rail costs $a$ bythalers.

Currently the transportation market in Byteotia is changing.

As of now, BSR faces a new competitor: Byteotian Airlines (BA).

BA plans to operate flights between some pairs of towns.

Since Byteotian railways are quite comfortable, the BA board has decided to    operate flights only between pairs of towns that are not directly    connected by rail.  Due to economy, BA will fly only between towns    for which the cheapest railway connection requires exactly one change.

The ticket for each such flight is going to cost $b$ bythalers.

To help Byteotian citizens in planning their trips, the Byteotian    Ministry for Transport (BMT) has decided to issue leaflets specifying the    cheapest routes between all possible towns.  A sequence of an    arbitrary number of direct railway or airplane connections is    called a route.  A BMT officer by the name of Byteasar has been    commissioned with the task of preparing the price list for the leaflets.

Could you help him in writing a program that will determine the right    prices?

Let us clarify that all the connections in Byteotia, both by railway and    airplane, are bidirectional.

## 输入格式

The first line of the standard input contains five integers,$n$,$m$,$k$,$a$ and $b$ ($2\le n\le 100\ 000$, $\le m\le 100\ 000$, $1\le k\le n$, $1\le a,b\le 1\ 000$),      separated by single spaces.

The numbers $n$ and $m$ denote the number of towns and the number of      direct railway connections in Byteotia, respectively.

For simplicity, we number the towns in Byteotia from $1$ to $n$. The other numbers denote:$k$ - the number of the source town for which the connection prices are to be determined;$a$ - the price of a direct railway connection;$b$ - the price of a direct airplane connection.

Each of the following $m$ lines contains a pair of integers $u_i$ and $v_i$($1\le u_i,v_i\le n$,$u_i\ne v_i$ for $i=1,2,\cdots,m$), separated by a single space, specifying the number of towns directly connected by tracks.


You may assume that all towns are reachable by railway from the town no. $k$.

## 输出格式

Your program should print $n$ lines to the standard output.

The line no. $i$ (for $i=1,2,\cdots,n$) should contain a single integer:

the cost of the cheapest route from town no. $k$ to town no. $i$.

Among those, the line no. $k$ should contain the number $0$.

## 样例

### 样例输入 #1
```
5 5 1 3 2
1 2
2 3
3 4
4 5
3 1

```
### 样例输出 #1
```
0
3
3
2
5

```
## 提示



------------

2024/2/4 添加了一部分来自 bzoj 的数据。
## 题目翻译

给定一个 $n$ 个点 $m$ 条边的无向图，边权均为 $a$。

现在将原来图中满足最短路等于 $2a$ 所有的点对 $(x,y)$ 之间加一条长度为 $b$ 的无向边。

给定 $k$，求点 $k$ 到所有点的最短路是多少。



---

---
title: "[USACO17DEC] Push a Box P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4082
tag: ['2017', 'USACO', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [USACO17DEC] Push a Box P
## 题目描述

**题目译自 [USACO 2017 December Contest, Platinum](http://usaco.org/index.php?page=dec17results) Problem 2. [Push a Box](http://usaco.org/index.php?page=viewproblem2&cpid=769)**

一个谷仓是一个 $N \times M$ 的矩形网格，有一些网格里有干草。 Bessie 站在其中一个格子内，还有一个格子里有一个大木箱。 Bessie 不能和大木箱在一个格子里，也不能和干草在一个格子里。

如果她不与干草在同一个格子，她就可以往自己旁边的四个方向（东西南北）移动，如果她想移动到有木箱的格子里，那个木箱就会被她推一格（只要木箱的那个方向还有空间），如果没有空间，那 Bessie 就不能移动了。

给你谷仓的布局（空格子，干草以及木箱位置）以及 Bessie 的出发位置和箱子要被推到的位置，请你帮忙计算 Bessie 能不能把木箱推到指定位置。
## 输入格式

第一行有三个数 $N,M,Q$，其中 $N$ 是谷仓的行数，$M$ 是列数，$Q$ 是询问数。

接下来 $N$ 行是谷仓的初始布局，其中 `.` 代表空格子， `#` 代表干草格子， `A` 代表 Bessie 的初始位置， `B` 是木箱的初始位置。

接下来 $Q$ 行，每行一个坐标 $(R,C)$ ，代表第 $R$ 行第 $C$ 行。对于每行，你要输出 Bessie 是否有可能把箱子推到这个位置。
## 输出格式

$Q$ 行，每行一个答案，如果 Bessie 能走到，输出 `YES` ，否则输出 `NO` 。
## 样例

### 样例输入 #1
```
5 5 4
##.##
##.##
A.B..
##.##
##.##
3 2
3 5
1 3
5 3
```
### 样例输出 #1
```
NO
YES
NO
NO
```
## 提示

对于 $100\%$ 的数据，保证 $1\leq N,M \leq 1500$，$1\leq Q\leq 50000$。


---

---
title: "孤舟蓑笠翁"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4730
tag: ['搜索', 'O2优化', '广度优先搜索 BFS']
---
# 孤舟蓑笠翁
## 题目背景

![Background](https://i.loli.net/2018/07/04/5b3cc42f57e64.png)

出于保护鱼类的目的，最优秀的渔翁才能在洞庭湖继续捕鱼。经过层层选拔，洞庭湖上只剩下孤舟蓑笠翁。以前跟其他渔翁一起钓鱼、打牌、切磋武艺，而如今只剩孤单一人，蓑笠翁不禁黯然神伤。选拔被淘汰，如今他们都去哪里了呢？大概回家种田养猪了吧。
## 题目描述

![Description](https://i.loli.net/2018/07/04/5b3cc3f0cd5f5.png)

蓑笠翁现在闲暇时在练的武术名为"左右互搏术"，相传是周伯通首创的武功。

练功时，蓑笠翁的双手在某竖直平面内运动，以该平面上某点作为坐标原点，向右为 $x$ 轴正方向，向上为 $y$ 轴正方向建立直角坐标系。那么该平面内的一个点就可以用坐标 $(x, y)$ 来表示。

该武功有 $n$ 个可停顿点，分别为 $p_1 = (x_1, y_1), p_2 = (x_2, y_2), \ldots, p_n = (x_n, y_n)$。我们可以将蓑笠翁练功的过程分成一秒一秒来看，第 $i$ 秒时，双手都处于可停顿点上。而第 $i$ 秒末双手进行移动，移动到其它可停顿点上。（当然也可以不移动）

左右互搏术中，有 $k$ 种绝招。第 $i$ 种绝招为：左手处于 $v_i$ 号可停顿点，右手处于 $u_i$ 号可停顿点，则可以发动绝招。

练武功也有禁忌，在两只手停顿的时候，如果两只手的曼哈顿距离小于 $d_{min}$，则容易走火入魔。如果两只手的曼哈顿距离大于 $d_{max}$，则蓑笠翁的胳膊显然快被扯断了。所以假设左手在 $l$ 号停顿点，右手在 $r$ 号停顿点，则需要满足 $d_{min} \leq |x_l - x_r| + |y_l - y_r| \leq d_{max}$。

从一个停顿点移动到另一个停顿点也有讲究，而且对于左右手还不一样。有 $m$ 个移动条件，每个移动条件形如：左手在 $a$ 号停顿点时能移动到 $b$ 号停顿点且在 $b$ 号停顿点时也能移动到 $a$ 号停顿点，或右手在 $a$ 号停顿点时能移动到 $b$ 号停顿点且在 $b$ 号停顿点时也能移动到 $a$ 号停顿点。对于某一秒末，蓑笠翁的手没那么快，所以每只手至多只能进行移动一次。上面未提到的移动方式均为非法。

蓑笠翁希望能发动连击。即先发动第 $i$ 种绝招，经过 $t$ 秒的移动后，又发动了第 $j$ 种绝招，且 $i \neq j$。

给出 $p_1, \ldots , p_n$，$v_1, \ldots v_k$，$u_1, \ldots , u_k$，$d_{min}$，$d_{max}$，和 $m$ 个移动条件，现在蓑笠翁想知道，发动第 $i$ 种绝招之后，最少经过多少秒的移动后能发动某个编号不为 $i$ 的绝招，即发动连击的最短耗时。请对于每个 $1 \leq i \leq k$ 输出答案。
## 输入格式

![Input](https://i.loli.net/2018/07/04/5b3ce144d752b.png)

第一行两个正整数 $n,m$。

第二行两个非负整数 $d_{min}, d_{max}$。保证 $d_{min} \leq d_{max}$。

接下来 $n$ 行，这 $n$ 行中的第 $i$ 行每行两个正整数 $x, y$ 表示 $i$ 号停顿点的坐标。

接下来的一行一个正整数 $k$ 。

接下来 $k$ 行，这 $k$ 行中的第 $i$ 行每行两个正整数 $v, u$ 表示 $i$ 号绝招。左手处于 $v$ 号可停顿点，右手处于 $u$ 号可停顿点时能发动该绝招。保证 $1 \leq v, u \leq n$，不会有两个绝招完全相同，保证 $v, u$ 的曼哈顿距离不小于 $d_{min}$ 不大于 $d_{max}$。

接下来 $m$ 行，每行三个正整数 $a, b, type$，若 $type = 0$ 则表示左手在 $a$ 号停顿点时能移动到 $b$ 号停顿点且在 $b$ 号停顿点时也能移动到 $a$ 号停顿点，若 $type = 1$ 则表示右手在 $a$ 号停顿点时能移动到 $b$ 号停顿点且在 $b$ 号停顿点时也能移动到 $a$ 号停顿点。保证 $1 \leq a, b \leq n$，$type \in \{0, 1\}$。
## 输出格式

![Output](https://i.loli.net/2018/07/04/5b3cc520d9fa0.png)

$k$ 行，第 $i$ 行表示第 $i$ 个绝招发动一次连击的最短耗时。

如果无论如何都无法连击，请输出 $-1$。
## 样例

### 样例输入 #1
```
5 5
1 6
3 2
9 2
7 3
7 8
4 9
3
5 4
1 3
1 2
1 2 0
2 5 0
1 5 1
1 3 1
3 4 1
```
### 样例输出 #1
```
2
2
-1
```
### 样例输入 #2
```
6 14
2 7
3 10
8 9
3 4
6 5
3 10
6 7
4
6 2
1 2
5 2
3 6
5 2 0
4 5 1
2 3 1
5 4 0
1 2 1
1 4 0
6 4 1
5 4 1
4 6 0
1 5 0
4 1 0
6 4 0
5 5 0
1 2 0
```
### 样例输出 #2
```
2
1
1
-1
```
## 提示

**【样例解释】**

![Explain](https://i.loli.net/2018/07/04/5b3cc62a913ae.png)

**对于样例一的解释**　对于绝招 $1$，可以先同时将左手移动到 $2$ 号可停顿点，右手移动到 $3$ 号可停顿点，这样耗时 $1 \textrm{ s}$，再将左手移动到 $1$ 号可停顿点，右手不动，这样可以发动绝招 $2$，共用时 $2 \textrm{ s}$。对于绝招 $2$ 可以把刚才的过程反过来，发动绝招 $1$。对于绝招 $3$，无论如何右手都无法移动，不能发动任何绝招，故输出 $-1$。

**对于样例二的解释**　不解释。

**【数据范围】**

![Constraint](https://i.loli.net/2018/07/04/5b3cc6528795b.png)

其中 $20 \%$ 的数据，$n \leq 50$，$m \leq 100$，$k \leq 100$。  
另有 $30 \%$ 的数据，$n \leq 500$，$m \leq 2000$，$k \leq 10000$，$d_{min} = 0$，$d_{max} = 10000$。  
对于 $100 \%$ 的数据，$n \leq 1000$，$m \leq 4000$，$1 \leq x_i, y_i \leq 1000$，$0 \leq d_{min} \leq d_{max} \leq {10}^9$。


---

---
title: "『MdOI R2』Little Goth"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6385
tag: ['字符串', '动态规划 DP', '贪心', '后缀自动机 SAM', 'O2优化', '广度优先搜索 BFS', '动态树 LCT', '分块', '后缀树', '洛谷月赛']
---
# 『MdOI R2』Little Goth
## 题目背景

小 M 和小 B 是一对好朋友，她们很喜欢爬山。
## 题目描述

山可以抽象为一个长为 $n$ 的字符串 $S$，串中仅包含小写字母。

对于一个字符串 $S$，我们定义 $|S|$ 表示串的长度，$S_{L\ldots R}$ 表示由 $S$ 中从左往右数，第 $L$ 个字符到第 $R$ 个字符依次连接形成的字符串。

小 M 一开始的位置是 $i$，她想要到达位置在 $k$ 处的山顶，而小 B 则要帮助她。为此，她们需要进行一系列操作。

她们**必须**在所有操作之前使用**一次**位于 $p$ 处的传送法阵，通过施展法术，可以使小 B 的位置变为任意满足 $j \geq i$ 且 $S_{i \ldots j} = S_{p \ldots p + (j-i)}$ 的 $j$。但同时，她们需要付出 $n-j$ 的代价。保证这样的 $j$ 存在。

之后，假设小 M ，小 B 的位置分别为 $i$ 和 $j$，她们可以任意次进行下列操作中的一种：

- 让小 M 爬，即令 $i=i+1$ 或 $i = i-1$。如果这一步操作之后 $i>j$，则 令 $j=i$。

- 让小 B 爬，即令 $j=j+1$ 或 $j=j-1$。如果这一步操作之后 $i>j$，则令 $i=j$。

- 使用螺旋升天，具体而言，选择两个下标 $l$ 和 $r$，满足 $S_{l \ldots r} = S_{i \ldots j}$，然后令 $i=l,j=r$。

出于某些原因，任何一次操作结束后，需要保证 $1 \leq i , j \leq n$。进行一次上述任意一种操作，都需要付出 $1$ 的代价。

爬山是很累的，因此她们想知道，至少需要付出多少代价才能让小 M 到达山顶，也就是让 $i=k$。又因为她们很喜欢爬山，她们有很多组询问要问你。
## 输入格式

第一行两个整数，$n$ 和 $q$，表示串 $S$ 的长度和询问的个数。

第二行一个长度为 $n$ 的字符串 $S$，仅包含小写字母。

接下来 $q$ 行，每行三个整数 $i,p$ 和 $k$，表明小 M 的位置，传送法阵位置和山顶的位置。
## 输出格式

共 $q$ 行，第 $i$ 行一个整数，表示对于第 $i$ 个询问给定的 $i,p$ 和 $k$，至少需要付出多少代价，才能让小 M 到达山顶，也就是，让小 M 的位置 $i=k$。
## 样例

### 样例输入 #1
```
8 2
dacdaaaa
5 8 1
1 4 5
```
### 样例输出 #1
```
5
8
```
## 提示

【帮助与提示】

为方便选手测试代码，本题额外提供一组附加样例供选手使用。

[样例输入](https://www.luogu.com.cn/paste/j7u8z9ir) [样例输出](https://www.luogu.com.cn/paste/fh19p0a4)

--------
【样例解释】

对于样例的第一组询问，使用传送法术时，只能令 $j=5$，付出 $8-5=3$ 的代价。之后，首先使用一次第三种操作，选择 $l=2,r=2$，令 $i=l,j=r$，然后使用一次第一种操作，令 $i-1$，即可使 $i=k$，一共付出 $5$ 的代价。

对于第二组询问，可以选择 $j=2$，付出 $8-2=6$ 的代价，然后使用一次第三种操作，选取 $l=4,r=5$ 并使 $i=l,j=r$，然后进行一次第一种操作，令 $i+1$ 即可使 $i=k$。一共付出 $8$ 的代价。

---

【数据范围】

**本题采用捆绑测试。**

对于全部数据，保证 $1 \leq n,q \leq 3\times 10^4$，$S$ 中仅包含小写字母。

| 子任务编号 |      $n\leq$      |     $q \leq$      |      特殊性质       | 分值 | 时间限制 |
| :--------: | :---------------: | :---------------: | :-----------------: | :--: | :------: |
| Subtask 1  |       $15$        |       $15$        |         无          | $3$  |    1s    |
| Subtask 2  |       $80$        |       $80$        |         无          | $14$ |    1s    |
| Subtask 3  |  $2 \times 10^4$  |  $2 \times 10^4$  |   $S$ 中仅包含`a`   | $8$  |    3s    |
| Subtask 4  |  $2 \times 10^4$  |  $2 \times 10^4$  |        $S_1$        | $7$ |    3s    |
| Subtask 5  |       $400$       |       $400$       |         无          | $9$  |    1s    |
| Subtask 6  |  $2\times 10^4$   |  $2 \times 10^4$  | 所有询问的 $k$ 相同 | $10$ |    3s    |
| Subtask 7  |      $10^3$       |      $10^3$       |         无          | $10$ |    2s    |
| Subtask 8  | $1.5 \times 10^4$ | $1.5 \times 10^4$ |         无          | $11$ |    3s    |
| Subtask 9  |  $3 \times 10^4$  |  $3 \times 10^4$  |         无          | $28$ |    3s    |



性质 $S_1$ 是，对于给定的 $p$，满足条件的 $j$ 唯一。




---

---
title: "[USACO21JAN] Paint by Letters P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7295
tag: ['图论', 'USACO', '并查集', '2021', 'cdq 分治', '广度优先搜索 BFS', '平面图欧拉公式', '前缀和', '栈', '分块']
---
# [USACO21JAN] Paint by Letters P
## 题目描述

Bessie 最近收到了一套颜料。画布可以用一个 $N×M$ 的矩形方阵表示，其中行从上往下编号为 $1…N$，列从左往右编号为 $1…M$（$1≤N,M≤1000$）。被涂色的方格的颜色可以用一个 `A` 到 `Z` 的大写字母表示。初始时，所有方格均未被涂色，每个方格至多只能被涂色一次。

Bessie 指定了每个方格她所希望的颜色。她一笔可以将一些组成连通分量的方格涂上颜色，也就是说这些方格之间可以通过相邻方格互相到达。如果两个方格有公共边则认为它们是相邻的。

例如，$3×3$ 的画布

```
AAB
BBA
BBB
```

可以用如下四笔完成涂色：

```
...    ..B    AAB    AAB    AAB
... -> ... -> ... -> BB. -> BBA
...    ...    ...    BBB    BBB
```

使用少于四笔不可能得到最终结果。

作为一名先锋派艺术家，Bessie 只会对这个画布中的一个子矩形进行涂色。现在，她正在考虑 $Q$
个候选子矩形（$1≤Q≤1000$），每一候选给定四个整数 $x_1$、$y_1$、$x_2$ 和 $y_2$，表示由第 $x_1$ 行到第 $x_2$ 行及第 $y_1$ 列到第 $y_2$ 列的所有方格组成的子矩形。

对于每个候选子矩形，将所有子矩形内的方格都涂上所希望的颜色，并且子矩形外的方格均不涂色，最少需要涂多少笔？注意在这个过程中 Bessie 并没有真正进行任何的涂色，所以对于每个候选的回答是独立的。

注意：本题每个测试点的时间限制为默认限制的 1.5 倍，且内存限制为默认限制的 2 倍，为 512MB。 
## 输入格式

输入的第一行包含 $N$、$M$ 和 $Q$。

以下 $N$ 行每行包含一个由 $M$ 个大写字母组成的字符串，表示画布每行所希望的颜色。

以下 $Q$ 行每行包含四个空格分隔的整数 $x_1,y_1,x_2,y_2$，表示一个候选子矩形（$1≤x_1≤x_2≤N$, $1≤y_1≤y_2≤M$）。
## 输出格式

对于 $Q$ 个候选子矩形的每一个，输出一行，包含答案。
## 样例

### 样例输入 #1
```
4 8 9
ABBAAAAA
ABAAAABA
CAADABBA
AAAAAAAA
1 1 4 8
3 5 3 8
1 3 2 4
1 4 2 5
1 1 3 3
4 4 4 4
2 6 4 8
3 5 4 6
1 6 3 8
```
### 样例输出 #1
```
6
3
2
1
4
1
3
2
2
```
## 提示

#### 样例 1 解释

第一个候选由整个画布组成，可以用六笔完成涂色。

第二个候选的子矩形所希望的颜色为

```
ABBA
```

可以用三笔完成涂色。注意，尽管在考虑整个画布时方格 $(3,5)$ 和 $(3,8)$ 可以用一笔涂上颜色 $A$，但如果仅考虑子矩形内的方格则并非如此。 

#### 测试点性质：

 - 测试点 1-2 满足 $N,M≤50$。
 - 测试点 3-5 中，画布不包含由单一颜色所组成的环。也就是说，不存在由不同方格所组成的序列 $c_1,c_2,c_3,…,c_k$ 满足以下条件：
   - $k>2$
   - 所有的 $c_1,…,c_k$ 颜色相同。
   - 对于所有的 $1≤i<k$，$c_i$ 与 $c_i+1$ 相邻。
   - $c_k$ 与 $c_1$ 相邻。
   注意，问题描述中的 3×3 画布包含单一颜色所组成的环（左下角的四个 B）。
 - 测试点 6-8 中，每个由相同期望颜色的方格组成的连通分量均能够被一个四边平行于坐标轴的两行两列的正方形所包含。问题描述中的 $3×3$ 画布不符合这一性质（由五个 B 组成的连通分量不能被一个两行两列的正方形包含）。
 - 测试点 9-11 中，每个由相同期望颜色的方格组成的连通分量均能够被一个四边平行于坐标轴的三行三列的正方形所包含。问题描述中的 $3×3$ 画布符合这一性质。
 - 测试点 12-20 没有额外限制。

供题：Andi Qu 


---

