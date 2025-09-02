---
title: "[IOI 1994] The Buses"
layout: "post"
diff: 普及+/提高
pid: P10489
tag: ['IOI', 'O2优化', '深度优先搜索 DFS']
---
# [IOI 1994] The Buses
## 题目背景

0x29 搜索 总结与练习
## 题目描述

A man arrives at a bus stop at 12:00. He remains there during 12:00-12:59. The bus stop is used by a number of bus routes. The man notes the times of arriving buses. The times when buses arrive are given.

-  Buses on the same route arrive at regular intervals from 12:00 to 12:59 throughout the entire hour.
- Times are given in whole minutes from 0 to 59.
- Each bus route stops at least 2 times.
- The number of bus routes in the test examples will be <=17.
- Buses from different routes may arrive at the same time.
- Several bus routes can have the same time of first arrival and/or time interval. If two bus routes have the same starting time and interval, they are distinct and are both to be presented.

Find the schedule with the fewest number of bus routes that must stop at the bus stop to satisfy the input data. For each bus route, output the starting time and the interval.

## 输入格式

Your program is to read from standard input. The input contains a number n (n <= 300) telling how many arriving buses have been noted, followed by the arrival times in ascending order.
## 输出格式

Your program is to write to standard output. The output contains one integer, which is the fewest number of bus routes.
## 样例

### 样例输入 #1
```
17
0 3 5 13 13 15 21 26 27 29 37 39 39 45 51 52 53
```
### 样例输出 #1
```
3
```
## 题目翻译

**【题目描述】**

一个人在 12:00 到达一个公交车站。他在 12:00 到 12:59 期间一直待在那里。这个公交车站被多条公交线路使用。这个人记录了公交车到达的时间。给出了公交车到达的时间。

- 同一条路线的公交车在整个小时内从 12:00 到 12:59 以固定的时间间隔到达。
- 时间以整分钟给出，从 0 到 59。
- 每条公交线路至少停靠 2 次。
- 测试示例中的公交线路数量将 $\leq 17$。
- 不同路线的公交车可能同时到达。
- 几条公交线路的首次到达时间和/或时间间隔可能相同。如果两条公交线路的起始时间和间隔相同，则它们是不同的，并且都需要呈现。

找出满足输入数据的必须停靠在公交车站的公交线路数量最少的时间表。对于每条公交线路，输出起始时间和间隔。

**【输入格式】**

你的程序需要从标准输入中读取。输入包含一个数字 $n$（$n \leq 300$），表示已经记录的到达公交车的数量，后跟按升序排列的到达时间。

**【输出格式】**

你的程序需要写入标准输出。输出包含一个整数，即最少的公交线路数量。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[IOI 2000] 邮局（原始版）"
layout: "post"
diff: 普及+/提高
pid: P10967
tag: ['2000', 'IOI', 'O2优化']
---
# [IOI 2000] 邮局（原始版）
## 题目描述

高速公路旁边有一些村庄。高速公路表示为整数轴，每个村庄的位置用单个整数坐标标识。没有两个在同样地方的村庄。两个位置之间的距离是其整数坐标差的绝对值。

邮局将建在一些，但不一定是所有的村庄中。为了建立邮局，应选择他们建造的位置，使每个村庄与其最近的邮局之间的距离总和最小。

你要编写一个程序，已知村庄的位置和邮局的数量，计算每个村庄和最近的邮局之间所有距离的最小可能的总和。
## 输入格式

第一行包含两个整数：第一个是村庄 $V$ 的数量，第二个是邮局的数量 $P$。

第二行包含 $V$ 个整数。这些整数是村庄的位置。
## 输出格式

第一行包含一个整数 $S$，它是每个村庄与其最近的邮局之间的所有距离的总和。
## 样例

### 样例输入 #1
```
10 5
1 2 3 6 7 9 11 22 44 50
```
### 样例输出 #1
```
9
```
## 提示

数据保证，$1 \le V \le 300$，$1 \le P \le 30$，$P \le V$，$1 \le X \le 10000$。


---

---
title: "[IOI 1994] 时钟 The Clocks"
layout: "post"
diff: 普及+/提高
pid: P1213
tag: ['搜索', '2001', 'USACO', 'IOI', '剪枝', '进制']
---
# [IOI 1994] 时钟 The Clocks
## 题目描述

考虑将如此安排在一个 $3 \times 3$ 行列中的九个时钟:

```plain
|-------|   |-------|   |-------|
|       |   |       |   |   |   |
|---o   |   |---o   |   |   o   |
|       |   |       |   |       |
|-------|   |-------|   |-------|
    A           B           C

|-------|   |-------|   |-------|
|       |   |       |   |       |
|   o   |   |   o   |   |   o   |
|   |   |   |   |   |   |   |   |
|-------|   |-------|   |-------|
    D           E           F

|-------|   |-------|   |-------|
|       |   |       |   |       |
|   o   |   |   o---|   |   o   |
|   |   |   |       |   |   |   |
|-------|   |-------|   |-------|
    G           H           I
```

目标要找一个最小的移动顺序将所有的指针指向 $12$ 点。下面原表格列出了 $9$ 种不同的旋转指针的方法，每一种方法都叫一次移动。  
选择 $1 \sim 9$ 号移动方法，将会使在表格中对应的时钟的指针顺时针旋转 
 $90$ 度。


|移动方法  | 受影响的时钟 |
| :----------: | :----------: |
| 1 | ABDE |
| 2 | ABC |
| 3 | BCEF |
| 4 | ADG |
| 5 | BDEFH |
| 6 | CFI |
| 7 | DEGH |
| 8 | GHI |
| 9 | EFHI |

例子：

```plain
9 9 12       9 12 12        9 12 12        12 12 12        12 12 12
6 6 6   5 -> 9  9  9   8 -> 9  9  9   4 -> 12  9  9   9 -> 12 12 12
6 3 6        6  6  6        9  9  9        12  9  9        12 12 12
```

**但这可能不是正确的方法，请看下文。**

## 输入格式

输入三行，每行三个正整数，表示一个时钟的初始时间，数字的含意和上面第一个例子一样。

## 输出格式

单独的一行包括一个用空格分开的将所有指针指向 $12$ 点的最短移动顺序的列表。

如果有多种方案，输出那种使其连接起来的数字最小的方案。（举例来说 $5\ 2\ 4\ 6 < 9\ 3\ 1\ 1$）。

## 样例

### 样例输入 #1
```
9 9 12
6 6 6
6 3 6 

```
### 样例输出 #1
```
4 5 8 9

```
## 提示

题目翻译来自NOCOW。

USACO Training Section 1.4



---

---
title: "[IOI 1998 ] [USACO5.5] 矩形周长Picture"
layout: "post"
diff: 普及+/提高
pid: P1856
tag: ['1998', '线段树', 'USACO', 'IOI', '扫描线']
---
# [IOI 1998 ] [USACO5.5] 矩形周长Picture
## 题目背景

墙上贴着许多形状相同的海报、照片。它们的边都是水平和垂直的。每个矩形图片可能部分或全部的覆盖了其他图片。所有矩形合并后的边长称为周长。

## 题目描述

编写一个程序计算周长。

![](https://cdn.luogu.com.cn/upload/image_hosting/2eo4hzl6.png)

如图 $1$ 所示 $7$ 个矩形。

![](https://cdn.luogu.com.cn/upload/image_hosting/buk96amj.png)

如图 $2$ 所示，所有矩形的边界。所有矩形顶点的坐标都是整数。

## 输入格式

输入文件的第一行是一个整数 $N$，表示有多少个矩形。接下来 $N$ 行给出了每一个矩形左下角坐标和右上角坐标。
## 输出格式

输出文件只有一个正整数，表示所有矩形的周长。

## 样例

### 样例输入 #1
```
7
-15 0 5 10
-5 8 20 25
15 -4 24 14
0 -6 16 4
2 15 10 22
30 10 36 20
34 0 40 16
```
### 样例输出 #1
```
228
```
## 提示

### 数据范围及约定

对于全部数据，$1 \le N<5000$，所有坐标的数值范围都在 $-10^4$ 到 $10^4$ 之间。


---

---
title: "[USACO3.2] 魔板 Magic Squares"
layout: "post"
diff: 普及+/提高
pid: P2730
tag: ['搜索', 'USACO', 'IOI']
---
# [USACO3.2] 魔板 Magic Squares
## 题目背景

在成功地发明了魔方之后，鲁比克先生发明了它的二维版本，称作魔板。这是一张有 $8$ 个大小相同的格子的魔板：

$1\quad2\quad3\quad4$

$8\quad7\quad6\quad5$

## 题目描述

我们知道魔板的每一个方格都有一种颜色。这 $8$ 种颜色用前 $8$ 个正整数来表示。可以用颜色的序列来表示一种魔板状态，规定从魔板的左上角开始，沿顺时针方向依次取出整数，构成一个颜色序列。对于上图的魔板状态，我们用序列 $\{1,2,3,4,5,6,7,8\}$ 来表示。这是基本状态。

这里提供三种基本操作，分别用大写字母 $\text A$，$\text B$，$\text C$ 来表示（可以通过这些操作改变魔板的状态）：

$\text A$：交换上下两行；

$\text B$：将最右边的一列插入最左边；

$\text C$：魔板中央四格作顺时针旋转。

下面是对基本状态进行操作的示范：

$\text A$：

$8\quad7\quad6\quad5$

$1\quad2\quad3\quad4$



$\text B$：

$4\quad1\quad2\quad3$

$5\quad8\quad7\quad6$

$\text C$：

$1\quad7\quad2\quad4$

$8\quad6\quad3\quad5$

对于每种可能的状态，这三种基本操作都可以使用。

你要编程计算用最少的基本操作完成基本状态到目标状态的转换，输出基本操作序列。

## 输入格式

只有一行，包括 $8$ 个整数 $a_1,a_2\cdots a_8(1\leq a_1,a_2\cdots a_8\leq8)$，用空格分开，不换行，表示目标状态。

## 输出格式

第一行包括一个整数，表示最短操作序列的长度。

第二行在字典序中最早出现的操作序列，用字符串表示，除最后一行外，每行输出 $60$ 个字符。

## 样例

### 样例输入 #1
```
2 6 8 4 5 7 3 1 
```
### 样例输出 #1
```
7 
BCABCCB
```
## 提示

题目翻译来自 NOCOW。

USACO Training Section 3.2



---

---
title: "[USACO5.3] 校园网Network of Schools"
layout: "post"
diff: 普及+/提高
pid: P2746
tag: ['2001', 'USACO', 'IOI', '强连通分量', 'Tarjan']
---
# [USACO5.3] 校园网Network of Schools
## 题目描述

一些学校连入一个电脑网络。那些学校已订立了协议：每个学校都会给其它的一些学校分发软件（称作“接受学校”）。注意即使 $B$ 在 $A$ 学校的分发列表中，$A$ 也不一定在 $B$ 学校的列表中。

你要写一个程序计算，根据协议，为了让网络中所有的学校都用上新软件，必须接受新软件副本的最少学校数目（子任务 A）。更进一步，我们想要确定通过给任意一个学校发送新软件，这个软件就会分发到网络中的所有学校。为了完成这个任务，我们可能必须扩展接收学校列表，使其加入新成员。计算最少需要增加几个扩展，使得不论我们给哪个学校发送新软件，它都会到达其余所有的学校（子任务 B）。一个扩展就是在一个学校的接收学校列表中引入一个新成员。
## 输入格式

输入文件的第一行包括一个正整数 $N$，表示网络中的学校数目。学校用前 $N$ 个正整数标识。

接下来 $N$ 行中每行都表示一个接收学校列表（分发列表），第 $i+1$ 行包括学校 $i$ 的接收学校的标识符。每个列表用 $0$ 结束，空列表只用一个 $0$ 表示。
## 输出格式

你的程序应该在输出文件中输出两行。

第一行应该包括一个正整数，表示子任务 A 的解。

第二行应该包括一个非负整数，表示子任务 B 的解。
## 样例

### 样例输入 #1
```
5
2 4 3 0
4 5 0
0
0
1 0
```
### 样例输出 #1
```
1
2
```
## 提示

$2 \le N \le 100$。

题目翻译来自NOCOW。

USACO Training Section 5.3



---

---
title: "[IOI 1998] Polygon"
layout: "post"
diff: 普及+/提高
pid: P4342
tag: ['动态规划 DP', '1998', 'IOI', '区间 DP']
---
# [IOI 1998] Polygon
## 题目描述

Polygon is a game for one player that starts on a polygon with $N$ vertices, like the one in Figure 1, where $N=4$. Each vertex is labelled with an integer and each edge is labelled with either the symbol `+` (addition) or the symbol `*` (product). The edges are numbered from $1$ to $N$.

![](https://cdn.luogu.com.cn/upload/pic/16086.png)

On the first move, one of the edges is removed. Subsequent moves involve the following steps: 
- pick an edge $E$ and the two vertices $V_1$ and $V_2$ that are linked by $E$; and 
- replace them by a new vertex, labelled with the result of performing the operation indicated in $E$ on the labels of $V_1$ and $V_2$.

The game ends when there are no more edges, and its score is the label of the single vertex remaining. 

Consider the polygon of Figure 1. The player started by removing edge 3. After that, the player picked edge 1, then edge 4, and, finally, edge 2. The score is 0. 

![](https://cdn.luogu.com.cn/upload/pic/16088.png)

Write a program that, given a polygon, computes the highest possible score and lists all the edges that, if removed on the first move, can lead to a game with that score. 

## 输入格式

Your program is to read from standard input. The input describes a polygon with N vertices. It contains two lines. On the first line is the number N. The second line contains the labels of edges 1, ..., N, interleaved with the vertices' labels (first that of the vertex between edges 1 and 2, then that of the vertex between edges 2 and 3, and so on, until that of the vertex between edges N and 1), all separated by one space. An edge label is either the letter t (representing +) or the letter x (representing *). 

3 <= N <= 50 


For any sequence of moves, vertex labels are in the range [-32768,32767]. 

## 输出格式

Your program is to write to standard output. On the first line your program must write the highest score one can get for the input polygon. On the second line it must write the list of all edges that, if removed on the first move, can lead to a game with that score. Edges must be written in increasing order, separated by one space.

## 样例

### 样例输入 #1
```
4
t -7 t 4 x 2 x 5

```
### 样例输出 #1
```
33
1 2
```
## 题目翻译

# 题目可能有些许修改，但大意一致

多边形是一个玩家在一个有n个顶点的多边形上的游戏，如图所示，其中n＝4。每个顶点用整数标记，每个边用符号+（加）或符号*（乘积）标记。

![](https://cdn.luogu.org/upload/pic/16086.png)

第一步，删除其中一条边。随后每一步： 

选择一条边连接的两个顶点V1和V2，用边上的运算符计算V1和V2得到的结果来替换这两个顶点。 

游戏结束时，只有一个顶点，没有多余的边。

如图所示，玩家先移除编号为3的边。之后，玩家选择计算编号为1的边，然后计算编号为4的边，最后，计算编号为2的边。结果是0。

![](https://cdn.luogu.org/upload/pic/16088.png)

（翻译者友情提示：这里每条边的运算符旁边的数字为边的编号，不拿来计算）

编写一个程序，给定一个多边形，计算最高可能的分数。

## 输入格式

输入描述一个有n个顶点的多边形，它包含两行。第一行是数字n，为总边数。

第二行描述这个多边形，一共有2n个读入，每两个读入中第一个是字符，第二个是数字。

第一个字符为第一条边的计算符号(t代表相加，x代表相乘)，第二个代表顶点上的数字。首尾相连。 

3 < = n < = 50

对于任何一系列的操作，顶点数字都在[-32768,32767]的范围内。

## 输出格式

第一行，输出最高的分数。在第二行，它必须写出所有可能的被清除后的边仍能得到最高得分的列表，必须严格递增。

感谢@2016c01 提供的翻译


---

---
title: "[IOI 2007] Miners 矿工配餐"
layout: "post"
diff: 普及+/提高
pid: P4401
tag: ['2007', 'IOI']
---
# [IOI 2007] Miners 矿工配餐
## 题目描述

现有两个煤矿，每个煤矿都雇用一组矿工。采煤工作很辛苦，所以矿工们需要良好饮食。每当一辆食品车到达煤矿时，矿工们便会产出一定数量的煤。

有三种类型的食品车：肉车，鱼车和面包车。
矿工们喜欢变化的食谱。如果提供的食品能够不断变化，他们的产煤量将会增加。每当一个新的食品车到达煤矿时，矿工们就会比较这种新的食品和前两次（或者少于两次，如果前面运送食品的次数不足两次）的食品，并且：

- 如果这几次食品车都是同一类型的食品，则矿工们产出一个单位的煤。
- 如果这几次食品车中有两种不同类型的食品，则矿工们产出两个单位的煤。
- 如果这几次食品车中有三种不同类型的食品，则矿工们产出三个单位的煤。

预先已知食品车的类型及其被配送的顺序。通过确定哪车食品送到哪个煤矿可以影响产煤量。食品车不能被拆分，每个食品车必须被全部送到一个或另一个煤矿。两个煤矿也并不要求接收相同数量的食品车（事实上，也允许将所有食品车都送到一个煤矿）。

给出食品车的类型及其被配送的顺序，要求你写一个程序，确定哪个食品车应被送到煤矿 $1$，哪个食品车应被送到煤矿 $2$，以使得两个煤矿的产煤量的总和最大。
## 输入格式

输入的第一行包含一个整数 $N (1 ≤ N ≤ 100 000)$,  表示食品车的数目。

第二行包含一个由 $N$ 个字符组成的字符串，按照配送顺序依次表示食品车配送的食品的类型。每个字符是以下三个大写字母之一：`M`（表示肉类），`F`（表示鱼类）或 `B`（表示面包）。
## 输出格式

输出一个整数，表示最大的总产煤量。
## 样例

### 样例输入 #1
```
6
MBMFFB
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
16
MMBMBBBBMMMMMBMB
```
### 样例输出 #2
```
29
```
## 提示

在样例 $1$ 中，可以按照如下的顺序运送食品车：煤矿 $1$，煤矿 $1$，煤矿 $2$，煤矿 $2$，煤矿 $1$，煤矿 $2$，依次产生的产煤量为 $1, 2, 1, 2, 3$ 和 $3$ 个单位，一共是 $12$ 个单位。

还有其它运送方式也能产生上述最大总和的产煤量。


---

---
title: "[IOI 2011] ricehub"
layout: "post"
diff: 普及+/提高
pid: P5844
tag: ['2011', 'IOI']
---
# [IOI 2011] ricehub
## 题目描述

乡间有一条笔直而长的路称为“米道”。沿着这条米道上$R$  块稻田，每块稻田的坐标均为一个 $1$ 到 $L$ 之间(含 $1$ 和 $L$ )的整数。这些稻田按照坐标以不减的顺序给出，即对于 $0 \le i < R$，稻田 $i$ 的坐标 $X[i]$ 满足 $1 \le X[0] \le \cdots \le X[R-1] \le L$。

注意：可能有多块稻田位于同一个坐标上。

我们计划建造一个米仓用于储存尽可能多的稻米。和稻田一样，米仓将建在米道上，其坐标也是一个 $1$ 到 $L$ 之间的整数（含 $1$ 和 $L$）。这个米仓可以建在满足上述条件的任一个位置上，包括那些原来已有一个或多个稻田存在的位置。

在收获季节，每一块稻田刚好出产一滿货车的稻米。为了将这些稻米运到米仓，需要雇用一位货车司机来运米。司机的收费是每一满货车运送一个单位的距离收取 $1$ 元。換言之，将稻米从特定的稻田运到米仓的费用在数值上等于稻田坐标与米仓坐标之差的绝对值。

不幸的是，今年预算有限，我们至多只能花费 $B$ 元运费。你的任务是要帮我们找出一个建造米仓的位置，可以收集到尽可能多的稻米。
## 输入格式

第一行 三个整数 $R,L,B$；

接下来 $R$ 行 每行一个整数 表示 $X[i]$。
## 输出格式

一个整数，表示最多稻米数
## 样例

### 样例输入 #1
```
5 20 6
1
2
10
12
14
```
### 样例输出 #1
```
3
```
## 提示

对于 $100\%$ 的数据，$1 \le R \le 10^5$，$1 \le L \le 10^9$，$ 0 \le B \le 2 \times 10^{15}$。


---

---
title: "[IOI 2005] mea"
layout: "post"
diff: 普及+/提高
pid: P5847
tag: ['2005', 'IOI']
---
# [IOI 2005] mea
## 题目描述

考虑一个非递减的整数序列 $S_1,\cdots,S_{n+1}$ ($S_i \le S{i+1}$，$1 \le i \le n$)。 序列 $M_1 \cdots M_n$ 是定义在序列 $S$ 的基础上，关系式为 $M_i = \frac{S_i + S_{i+1}}{2  }$（$1 \le i < n$）, 序列 $M$ 叫做序列 $S$ 的平均数序列。


例如序列 $1,2,2,4$ 的平均数序列为 $1.5,2,3$. 注意到平均数序列中的元素可能为小数。但是本题的任务只是处理平均数序列都为整数的情况。 

给出一个 $n$ 个数字的非递减的整数序列 $M_1,M_2,\cdots,M_n$。请你计算出：序列 $S_1,\cdots,S_{n+1}$ 的平均序列是 $M_1,\cdots,M_n$。 求满足以上条件的序列 $S$ 的总个数。

任务：从标准输入文件中读入一个非递减的整数序列。计算出平均序列是给出序列的整数序列的总个数。把计算结果写到标准输出文件中。
## 输入格式

输入文件的第一行包含一个整数 $n$ （$ 2 \le n \le 5 \times 10^6$）。

接下来的 $n$ 行包含了这个给出的整数序列 $M_1,\cdots,M_n$。第 $i+1$ 行包含一个整数 $M_i$ ( $1 \le m_i \le 10^9$)。
## 输出格式

输出文件仅一行，即所求答案。
## 样例

### 样例输入 #1
```
3
2
5
9

```
### 样例输出 #1
```
4

```
## 提示

**样例说明**

一共存在 $4$ 种序列，它们的平均数序列都是 $2,3,9$。这四种序列如下：
- $2,2,8,10$
- $1,3,7,11$
- $0,4,6,12$
- $-1,5,5,13$

**数据范围**

对于 $50\%$ 的数据，$2 \le n \le 1000$，$1 \le M_i \le 2 \times 10^4$；

对于 $100\%$ 的数据，$2 \le n \le 5 \times 10^6$，$1 \le M_i \le 10^9$。


---

---
title: "[IOI 2014] game 游戏"
layout: "post"
diff: 普及+/提高
pid: P5884
tag: ['2014', 'IOI', 'Special Judge']
---
# [IOI 2014] game 游戏
## 题目描述

健佳是一个喜欢做游戏的小男生。当有人问问题时，他更喜欢通过玩游戏的方式作答，而不是直接回答。健佳碰到了他的朋友梅玉，跟她讲了台湾的航空网。在台湾有 $n$ 个城市（编号为 $0,\cdots,n−1$），其中有些城市之间有航线。每个航线连接两个城市，并且是双向的。

梅玉问健佳，是否任意两个城市之间都可以坐飞机互达（直接或间接），健佳不想直接回答，而是要通过做游戏的方式来告诉她。梅玉可以问"城市 $u$ 和 $v$ 之间有直接航线吗？"，健佳会立刻直接回答该问题。梅玉会询问每对城市恰好一次，因此总计会有 $r = \frac{n (n−1)}{2}$ 个问题。如果由前 $i$（$i<r$）个问题的答案可以推断出整个航空网是否连通，也就是说，是否任意一对城市之间都可以坐飞机互达（直接或间接），梅玉就获胜。否则意味着她需要知道全部 $r$ 个回答，此时健佳获胜。

为了让游戏更好玩，他们俩同意，健佳可以不要管台湾的真实航空网，而是可以随着游戏的进展而编造航空网，也就是根据梅玉此前的提问来决定此后如何作答。你的任务是，通过决定健佳如何回答，来帮助他赢得游戏。
## 输入格式

- 第 $1$ 行：一个正整数 $n$，代表城市数量。
- 余下 $r$ 行：每行包含两个整数 $u$ 和 $v$，表示对城市 $u$ 和 $v$ 的提问。
## 输出格式

- 共 $r$ 行，对于每次梅玉的提问，你必须回答在城市 $v$ 和 $u$ 之间是否有直接航线。具体而言，返回值 $1$ 表示有，$0$ 表示没有。
## 样例

### 样例输入 #1
```
4
0 3
1 0
0 2
3 1
1 2
2 3

```
### 样例输出 #1
```
0
1
0
1
0
1

```
## 提示

**子任务及数据规模**

| 子任务 | 分值 | $n$ |
| :----------: | :----------: | :----------: |
| $1$ | $15$ | $n=4$ |
| $2$ | $27$ | $4 \le n \le 80$ |
| $3$ | $58$ | $4 \le n \le 1500$ |



---

---
title: "[IOI 2013] dreaming 梦想"
layout: "post"
diff: 普及+/提高
pid: P5895
tag: ['2013', 'IOI']
---
# [IOI 2013] dreaming 梦想
## 题目描述

天地之初，IOI 尚在遥远的梦想之中。

Serpent(水蛇) 生活的地方有 $N$ 个水坑，编号为 $0，\cdots，N - 1$，有 $M$ 条双向小路连接
这些水坑。每两个水坑之间至多有一条路径（路径包含一条或多条小路）相互连接，有些水坑之间根本无法互通(即 $M ≤ N-1$ )。Serpent 走过每条小路需要一个固定的天数，不同的小路需要的天数可能不同。

Serpent 的朋友袋鼠希望新修 $N - M - 1$ 条小路，让Serpent 可以在任何两个水坑间游走。袋鼠可以在任意两个水坑之间修路，Serpent 通过每条新路的时间都是 $L$ 天。

袋鼠希望找到一种修路方式使得修路之后 Serpent 在每两个水坑之间游走的最长时间最短。

**举例说明**

![](https://cdn.luogu.com.cn/upload/image_hosting/3ahroenu.png)


上图中有 $12$ 个水坑 $8$ 条小路 ($N = 12 , M = 8$)。假如 $L = 2$，即 Serpent 通过任何一条新路都需要 $2$ 天。那么，袋鼠可以修建 $3$ 条新路：
- 水坑 $1$ 和水坑 $2$ 之间；
- 水坑 $1$ 和水坑 $6$ 之间；
- 水坑 $4$ 和水坑 $10$ 之间。

![](https://cdn.luogu.com.cn/upload/image_hosting/udp17aas.png)

上图显示了修路后的最终状态。从水坑 $0$ 走到水坑 $11$ 的时间最长，需要 $18$ 天。这是最佳结果，无论袋鼠如何选择修路方式，总会存在一些水坑对，Serpent 需要 $18$ 天或者更长时间从其中一个走到另一个。
## 输入格式

- 第 $1$ 行: $N$ 表示水坑的数目，$M$ 表示原本存在的小路的数目，$L$ 表示 Serpent 通过新修的路径的时间。
- 第 $2,\cdots, M + 1$ 行: $A[i]$，$B[i]$，$T[i]$。$A$，$B$，$T$ 分别为三个包含 $M$ 个元素的数组，分别表示每条小路的两个端点和通过这条小路的时间。例如，第 $i$ 条小路连接水坑 $A[i-1]$ 和水坑 $B[i-1]$，通过这条小路的时间是 $T[i-1]$ 天。


例如：题目中的例子应该表示为以下格式

```
12 8 2
0 8 4
8 2 2
2 7 4
5 11 3
5 1 7
1 3 1
1 9 5
10 6 3
```
## 输出格式

如上所述，表示游走于两个距离最远的水坑之间所需的时间
## 样例

### 样例输入 #1
```
12 8 2
0 8 4
8 2 2
2 7 4
5 11 3
5 1 7
1 3 1
1 9 5
10 6 3

```
### 样例输出 #1
```
18

```
## 提示

对于 $100\%$ 的数据，$1 \le N \le 10^5$，$0 \le M \le N-1$，$0 \le A[i],B[i] \le N-1$，$1 \le T[i] \le 10^4$，$1 \le L \le 10^4$。


---

---
title: "[IOI 1995] 铺放矩形块"
layout: "post"
diff: 普及+/提高
pid: P5917
tag: ['2001', 'IOI']
---
# [IOI 1995] 铺放矩形块
## 题目描述

给定 $ 4 $ 个矩形块，找出一个最小的封闭矩形将这 $ 4 $ 个矩形块放入，但不得相互重叠。所谓最小矩形指该矩形面积最小。

所有 $ 4 $ 个矩形块的边都与封闭矩形的边相平行。

可能存在满足条件且有着同样面积的各种不同的封闭矩形， 你应该输出所有这些封闭矩形的边长。

## 输入格式

输入文件共有 $ 4 $ 行。每一行用两个正整数来表示一个给定的矩形块的两个边长。矩形块的每条边的边长范围最小是 $ 1 $，最大是 $ 50 $。
## 输出格式

输出文件的总行数为解的总数加 $ 1 $。第一行是一个整数， 代表封闭矩形的最小面积（子任务 $ A $）。接下来的每一行都表示一个解，由数 $ P $ 和数$ Q $ 来表示，并且 $ P \leq Q $（子任务 $ B $）。这些行必须根据 $ P $ 的大小按升序排列，$ P $ 小的行在前，大的在后。且所有行都应是不同的。
## 样例

### 样例输入 #1
```
1 2
2 3
3 4
4 5
```
### 样例输出 #1
```
40
4 10
5 8
```


---

---
title: "[IOI 2004] Phidias 菲迪亚斯神"
layout: "post"
diff: 普及+/提高
pid: P5924
tag: ['2004', 'IOI']
---
# [IOI 2004] Phidias 菲迪亚斯神
## 题目背景

有名的希腊雕刻神菲迪亚斯正在为他下一座雄伟的雕像作准备。
## 题目描述

为了这座雕像他需要大小为 $W_1\times H_1,W_2\times H_2, ...,W_N \times H_N$ 的矩形大理石板。

最近菲迪亚斯获得一块矩形大理石块。菲迪亚斯想把这块石板切成所需要的大小。

石板或是石板所切割出的部分都可以由垂直(或水平)方向纵贯(或是横贯)加以切割到底成为两块矩形石板，同时切割出的这两块矩形石板都必须具有整数的宽度与高度。

石板只能以此种方法加以切割，同时石板不能粘合成较大石板。

因为石板具有花纹，所以石板也不能旋转。

如果菲迪亚斯切割出一块 $A\times B$ 的石板，则此石板不能被当成 $B\times A$ 的石板使用，除非 $A$ 等于 $B$。对每一种所需石板大小菲迪亚斯可切割出零或更多块石板。如果当所有的切割完成时，一块产生出的石板并不是任何所需要的大小，则此石板成为废料。

菲迪亚斯想知道如何切割最初的石板，才能让所产生的废料最少。

例如，下图中的原始石板宽度为 $21$ 且高度为 $11$，而所需石板大小为 $10\times4,6\times 2, 7\times5$ 及 $15\times 10$, 则最小废料总面积为 $10$。下图同时画出最小废料总面积为 $10$ 的切割方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/s48ydewh.png)

你的工作是写一个程序由给定的原始石板大小及所需要的各种石板大小计算出最小的废料总面积。
## 输入格式

第一行为两个整数。

第一个整数 $W$ 为原始石板的宽度，第二个整数 $H$ 为原始石板的高度。

第二行为一个整数 $N$，代表所需石板种类数目。以下 $N$ 行为各种所需石板的大小。

每一行为两个整数，第一个整数为所需石板宽度 $W_i$，第二个整数为所需石板宽度 $H_i$ 。

## 输出格式

为一行且仅包含一个整数，代表最小废料总面积。
## 样例

### 样例输入 #1
```
21 11
4
10 4
6 2
7 5
15 10
```
### 样例输出 #1
```
10
```
## 提示

对于 $100\%$ 的数据，$1\le W,H\le600$，$0\le N\le 200$，$1 \le W_i \le W$，$1 \le H_i \le H$。




---

