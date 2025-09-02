---
title: "[COTS 2022] 游戏 M"
layout: "post"
diff: 提高+/省选-
pid: P10875
tag: ['2022', 'O2优化', 'Tarjan', 'COCI（克罗地亚）']
---
# [COTS 2022] 游戏 M
## 题目背景

译自 [Izborne Pripreme 2022 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2022/) D2T2。$\texttt{3s,0.5G}$。
## 题目描述


有一张 $N$ 个节点的无向图，依次向图中添加 $M$ 条边。

有 $Q$ 个询问，每次询问给定 $u,v$，问：至少添加前多少条边，才能使得 $u,v$ 间没有割边（换言之，割去任意一条边，都不影响 $u,v$ 的连通性）。特别地，如果 $u,v$ 始终不连通或者始终有割边，则输出 $-1$。

## 输入格式

第一行，两个整数 $N,M$，含义见题面；

接下来 $M$ 行，第 $i$ 行包含两个整数 $s_i,t_i$，表示第 $i$ 条边为 $(s_i,t_i)$。

第 $(M+2)$ 行，一个整数 $Q$，含义见题面；

接下来 $Q$ 行，每行两个整数 $u,v$，描述一个询问。
## 输出格式


输出 $Q$ 行，每行一个整数，表示询问的答案。
## 样例

### 样例输入 #1
```
3 3
1 2
2 3
3 1
1
1 2
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 4
1 2
1 2
2 3
2 3
3
1 2
2 3
3 1
```
### 样例输出 #2
```
2
4
4
```
### 样例输入 #3
```
6 7
1 2
2 3
3 4
2 5
3 5
4 5
1 3
5
1 3
2 3
4 5
1 4
2 6
```
### 样例输出 #3
```
7
5
6
7
-1
```
## 提示


对于 $100\%$ 的数据，保证：

- $2\le N \le 3\times 10^5$，$0\le M\le 3\times 10^5$，$1\le Q\le 3\times 10^5$；
- $s_i\neq t_i$，$u\neq v$；
- $1\le u,v,s_i,t_i\le N$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $10$  | $Q=1$  |
| $2$  | $20$  | $2\mid M$，$(s_{2i-1},t_{2i-1})=(s_{2i},t_{2i})$  |
| $3$  | $30$  | $N,M\le 5\, 000$ |
| $4$  | $40$  | 无额外约束 |


---

---
title: "[国家集训队] 稳定婚姻"
layout: "post"
diff: 提高+/省选-
pid: P1407
tag: ['强连通分量', 'Tarjan', '二分图']
---
# [国家集训队] 稳定婚姻
## 题目描述

我们已知 $n$ 对夫妻的婚姻状况，称第 $i$ 对夫妻的男方为 $B_i$，女方为 $G_i$。若某男 $B_i$ 与某女 $G_j$ 曾经交往过（无论是大学，高中，亦或是幼儿园阶段，$i \le j$），则当某方与其配偶（即 $B_i$ 与 $G_i$ 或 $B_j$ 与 $G_j$）感情出现问题时，他们有私奔的可能性。不妨设 $B_i$ 和其配偶 $G_i$ 感情不和，于是 $B_i$ 和 $G_j$ 旧情复燃，进而 $B_j$ 因被戴绿帽而感到不爽，联系上了他的初恋情人 $G_k$ ……一串串的离婚事件像多米诺骨牌一般接踵而至。若在 $B_i$ 和 $G_i$ 离婚的前提下，这 $2n$ 个人最终依然能够结合成 $n$ 对情侣，那么我们称婚姻 $i$ 为不安全的，否则婚姻 $i$ 就是安全的。

给定所需信息，你的任务是判断每对婚姻是否安全。
## 输入格式

第一行为一个正整数 $n$，表示夫妻的对数；

以下 $n$ 行，每行包含两个字符串，表示这 $n$ 对夫妻的姓名（先女后男），由一个空格隔开；

第 $n+2$ 行包含一个正整数 $m$，表示曾经相互喜欢过的情侣对数；

以下 $m$ 行，每行包含两个字符串，表示这 $m$ 对相互喜欢过的情侣姓名（先女后男），由一个空格隔开。
## 输出格式

输出文件共包含 $n$ 行，第 $i$ 行为 `Safe`（如果婚姻 $i$ 是安全的）或 `Unsafe`（如果婚姻 $i$ 是不安全的）。

## 样例

### 样例输入 #1
```
2
Melanie Ashley
Scarlett Charles
1
Scarlett Ashley
```
### 样例输出 #1
```
Safe
Safe
```
### 样例输入 #2
```
2
Melanie Ashley
Scarlett Charles
2
Scarlett Ashley
Melanie Charles
```
### 样例输出 #2
```
Unsafe
Unsafe
```
## 提示

对于 $20\%$ 的数据，$n \le 20$；

对于 $40\%$ 的数据，$n \le 100$，$m \le 400$；

对于 $100\%$ 的数据，所有姓名字符串中只包含英文大小写字母，大小写敏感，长度不大于 $8$，保证每对关系只在输入文件中出现一次，输入文件的最后 $m$ 行不会出现未在之前出现过的姓名，这 $2n$ 个人的姓名各不相同，$1 \le n \le 4000$，$0 \le m \le 20000$。


---

---
title: "[USACO04DEC] Cow Ski Area G"
layout: "post"
diff: 提高+/省选-
pid: P1653
tag: ['图论', '2004', 'USACO', '强连通分量', 'Tarjan']
---
# [USACO04DEC] Cow Ski Area G
## 题目描述

约翰的表哥罗恩生活在科罗拉多州。他近来打算教他的奶牛们滑雪，但是奶牛们非常害羞，不敢在游人组织的度假胜地滑雪。没办法，他只好自己建滑雪场了。罗恩的雪场可以划分为 $W$ 列 $L$ 行 $(1\le W\le 500, 1\le L\le 500)$，每个方格有一个特定的高度 $H(0\le H\le 9999)$。奶牛可以在相邻方格间滑雪，而且不能由低到高滑。

为了保证任意方格可以互通，罗恩打算造一些直达缆车。缆车很强大，可以连接任意两个方格，而且是双向的。而且同一个方格也可以造多台缆车。但是缆车的建造费用贵得吓人，所以他希望造尽量少的缆车。那最少需要造多少台呢？
## 输入格式

第 $1$ 行：$W$，$L$。

接下来输入宽 $W$ 高 $L$ 的矩阵地图。
## 输出格式

输出最小需要的缆车数。
## 样例

### 样例输入 #1
```
9 3
1 1 1 2 2 2 1 1 1
1 2 1 2 3 2 1 2 1
1 1 1 2 2 2 1 1 1
```
### 样例输出 #1
```
3
```
## 提示

$1\le W,L\le 500$，$0\le H\le 9999$。


---

---
title: "[SDOI2010] 所驼门王的宝藏"
layout: "post"
diff: 提高+/省选-
pid: P2403
tag: ['2010', '各省省选', '山东', '拓扑排序', '强连通分量', 'Tarjan']
---
# [SDOI2010] 所驼门王的宝藏
## 题目描述

在宽广的非洲荒漠中，生活着一群勤劳勇敢的羊驼家族。被族人恭称为“先知”的 AlpacaL.Sotomon 是这个家族的领袖，外人也称其为“所驼门王”。所驼门王毕生致力于维护家族的安定与和谐，他曾亲自率军粉碎河蟹帝国主义的野蛮侵略，为族人立下赫赫战功。所驼门王一生财宝无数，但因其生性节俭低调，他将财宝埋藏在自己设计的地下宫殿里，这也是今天 Henry Curtis 故事的起点。Henry 是一个爱财如命的贪婪家伙，而又非常聪明，他费尽心机谋划了这次盗窃行动，破解重重机关后来到这座地下宫殿前。

整座宫殿呈矩阵状，由 $R \times C$ 间矩形宫室组成，其中有 $N$ 间宫室里埋藏着宝藏，称作藏宝宫室。宫殿里外、相邻宫室间都由坚硬的实体墙阻隔，由一间宫室到达另一间只能通过所驼门王独创的移动方式——传送门。所驼门王为这 $N$ 间藏宝宫室每间都架设了一扇传送门，没有宝藏的宫室不设传送门，所有的宫室传送门分为三种：

1. “横天门”：由该门可以传送到同行的任一宫室；
2. “纵寰门”：由该门可以传送到同列的任一宫室；
3. “任意门”：由该门可以传送到以该门所在宫室为中心周围 $8$ 格中任一宫室（如果目标宫室存在的话）。

深谋远虑的 Henry 当然事先就搞到了所驼门王当年的宫殿招标册，书册上详细记录了每扇传送门所属宫室及类型。而且，虽然宫殿内外相隔，但他自行准备了一种便携式传送门，可将自己传送到殿内任意一间宫室开始寻宝，并在任意一间宫室结束后传送出宫。整座宫殿只许进出一次，且便携门无法进行宫室之间的传送。不过好在宫室内传送门的使用没有次数限制，每间宫室也可以多次出入。

现在 Henry 已经打开了便携门，即将选择一间宫室进入。为得到尽多宝藏，他希望安排一条路线，使走过的不同藏宝宫室尽可能多。请你告诉 Henry 这条路线最多行经不同藏宝宫室的数目。
## 输入格式

第一行给出三个正整数 $N,R,C$。

以下 $N$ 行，每行给出一扇传送门的信息，包含三个正整数 $x_i,y_i,T_i$，表示该传送门设在位于第 $x_i$ 行第 $y_i$ 列的藏宝宫室，类型为 $T_i$。$T_i$ 是一个 $1 \sim 3$ 间的整数，$1$ 表示可以传送到第 $x_i$ 行任意一列的“横天门”，$2$ 表示可以传送到任意一行第 $y_i$ 列的“纵寰门”，$3$ 表示可以传送到周围 $8$ 格宫室的“任意门”。

保证 $1 \le x_i \le R$，$1 \le y_i \le C$，所有的传送门位置互不相同。
## 输出格式

输出只有一个正整数，表示你确定的路线所经过不同藏宝宫室的最大数目。

## 样例

### 样例输入 #1
```
10 7 7
2 2 1
2 4 2
1 7 2
2 7 3
4 2 2
4 4 1
6 7 3
7 7 1
7 5 2
5 2 1
```
### 样例输出 #1
```
9
```
## 提示

数据规模和约定：

![](https://cdn.luogu.com.cn/upload/pic/1594.png)



---

---
title: "[HAOI2010] 软件安装"
layout: "post"
diff: 提高+/省选-
pid: P2515
tag: ['动态规划 DP', '2010', '河南', '各省省选', '强连通分量', 'Tarjan']
---
# [HAOI2010] 软件安装
## 题目描述

现在我们的手头有 $N$ 个软件，对于一个软件 $i$，它要占用 $W_i$ 的磁盘空间，它的价值为 $V_i$。我们希望从中选择一些软件安装到一台磁盘容量为 $M$ 计算机上，使得这些软件的价值尽可能大（即 $V_i$ 的和最大）。

但是现在有个问题：软件之间存在依赖关系，即软件 $i$ 只有在安装了软件 $j$（包括软件 $j$ 的直接或间接依赖）的情况下才能正确工作（软件 $i$ 依赖软件 $j$)。幸运的是，一个软件最多依赖另外一个软件。如果一个软件不能正常工作，那么它能够发挥的作用为 $0$。


我们现在知道了软件之间的依赖关系：软件 $i$ 依赖软件 $D_i$。现在请你设计出一种方案，安装价值尽量大的软件。一个软件只能被安装一次，如果一个软件没有依赖则 $D_i=0$，这时只要这个软件安装了，它就能正常工作。
## 输入格式

第 1 行：$N,M(0\leq N\leq 100, 0\leq M\leq 500)$

第 2 行：$W_1,W_2, ... W_i, ..., W_n (0\leq W_i\leq M)$

第 3 行：$V_1, V_2, ..., V_i, ..., V_n  (0\leq V_i\leq 1000)$

第 4 行：$D_1, D_2, ..., D_i, ..., D_n (0\leq D_i\leq N, D_i≠i)$
## 输出格式

一个整数，代表最大价值。

## 样例

### 样例输入 #1
```
3 10
5 5 6
2 3 4
0 1 1
```
### 样例输出 #1
```
5
```


---

---
title: "[USACO09FEB] Surround the Islands S"
layout: "post"
diff: 提高+/省选-
pid: P2941
tag: ['2009', 'USACO', '并查集', '枚举', 'Tarjan']
---
# [USACO09FEB] Surround the Islands S
## 题目描述

Farmer John has bought property in the Caribbean and is going to try to raise dairy cows on a big farm composed of islands. Set in his ways, he wants to surround all the islands with fence.

Each island in the farm has the shape of a polygon. He fences the islands one side at a time (between a consecutive pair of vertices) and proceeds clockwise around a given island with his fencing

operations. Since he wants to fence all the islands, he must at some point travel to any other islands using a boat.

He can start fencing at any vertex and, at any vertex he encounters, travel to some vertex on another island, fence all the way around it, and then IMMEDIATELY return back to the same vertex on the original island using the same path he traveled before. Each boat trip has a cost defined by a supplied matrix.

The islands are described by a set of N (3 <= N <= 500) pairs of vertices V1,V2 (1 <= V1 <= N; 1 <= V2 <= N) although you must figure out how to assemble them into islands. The vertices are conveniently numbered 1..N.

The cost of traveling by boat between each pair of vertices is given by a symmetric cost matrix whose elements fall in the range 0..1000.

What is the minimum cost of surrounding the islands with the fence?
## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Each line describes an island's border with two space-separated integers: V1 and V2

\* Lines N+2..2\*N+1: Line i-N-1 contains N integers that describe row i of the cost matrix: Row\_i

## 输出格式

\* Line 1: A single integer that specifies the minimum cost of building the fence

## 样例

### 样例输入 #1
```
12 
1 7 
7 3 
3 6 
6 10 
10 1 
2 12 
2 9 
8 9 
8 12 
11 5 
5 4 
11 4 
0 15 9 20 25 8 10 13 17 8 8 7 
15 0 12 12 10 10 8 15 15 8 8 9 
9 12 0 25 20 18 16 14 13 7 12 12 
20 12 25 0 8 13 14 15 15 10 10 10 
25 10 20 8 0 16 20 18 17 18 9 11 
8 10 18 13 16 0 10 9 11 10 8 12 
10 8 16 14 20 10 0 18 20 6 16 15 
13 15 14 15 18 9 18 0 5 12 12 13 
17 15 13 15 17 11 20 5 0 22 8 10 
8 8 7 10 18 10 6 12 22 0 11 12 
8 8 12 10 9 8 16 12 8 11 0 9 
7 9 12 10 11 12 15 13 10 12 9 0 

```
### 样例输出 #1
```
30 

```
## 提示

1        10            4

xxxxxxx              x

xxxxxxxxx            xxxx

7 xxxxxxxxxxx 6        xxxxxxx

xxxxxxxxxxx       11 xxxxxxxxxx 5

xxxxxxx

xxx
3         12 xxxxxxx 2

xxxxxxxx

xxxxxxxx

xxxxxxxxx

xxxxxxxxx

xxxxxxxxxx

xxxxxxxxxx

8 xxxxxxxxxx 9

The example describes three islands: {1,7,3,6,10}, {4,5,11} and {2,9,8,12}. The travel costs are provided as a matrix. For example, the travel cost from vertex 1 to 2 is 15.


There is more than one solution. One is: FJ starts from vertex 3 then 7 and stops at 1, travels to 11 followed by 4,5,11. He then returns back to 1, and travels to 12 followed by 2,9,8,12. Finally, he returns back to 1 and continues with 10,6,3,7. The costs are 8 \* 2 = 16 for traveling from 1 to 11 and returning back, and 7 \* 2 = 14 for traveling from 1 to 12 and back -- a total cost of 30.

## 题目翻译

**【题目描述】**

Farmer John 在加勒比海购置了一片地产，准备在由一系列岛屿组成的农场上养奶牛。 出于他的意愿，他要把所有的岛屿都用篱笆围上。  
每个岛都是多边形的。每一次，FJ 会给多边形的一个边（即相邻的两个顶点之间）装上篱笆。对于整个岛屿，他会按照顺时针顺序装上篱笆。由于他想要给所有的岛屿都装上篱笆，某些时候，他必须从一个岛屿坐船到另一个岛屿去。  
FJ 可以从任何一个顶点开始装篱笆，也可以从任何一个顶点坐船到另一个岛的某个顶点上，从这个顶点开始把该岛屿的篱笆全都装好，然后**马上**坐船原路返回。保证任意两个顶点间都有航线。在任意两个顶点之间坐船的费用会在一个矩阵中给出。  
所有的岛屿由给定的 $N$ 对顶点 $V_1$，$V_2$ 描述（即：给定顶点 $V_1$ 与 $V_2$ 相邻）。每个顶点具体属于哪个岛屿**不会**在输入中给出。所有顶点由 $1$ 到 $N$ 标号。  
在顶点间坐船旅行的费用由一个 $N \times N$ 的矩阵给出。保证两个岛屿间两个方向的旅行费用相等且不会超过 $1000$。   
请求出 FJ 把篱笆装完所需要的最小花费。

**【输入格式】**

第 $1$ 行：包含一个整数 $N$，含义见题目描述。  
第 $2$ 至第 $N+1$ 行：每行包含两个整数 $V_1$ 和 $V_2$，表示这两个顶点在同一个岛屿上且相邻。  
第 $N+2$ 行至第 $2N+1$ 行：每行包含 $N$ 个整数，第 $i-N-1$ 行的第 $j$ 个整数表示从 $i$ 号顶点坐船到第 $j$ 号顶点的花费。

**【输出格式】**

一行一个整数，表示 FJ 把篱笆装完所需要的最小花费。

**【说明/提示】**

对于所有数据，保证：

+ $3 \leq n \leq 500$
+ $1 \leq V_1,V_2 \leq N$
+ 任意两个顶点之间的旅行花费 $\leq 1000$


---

---
title: "[USACO15JAN] Grass Cownoisseur G"
layout: "post"
diff: 提高+/省选-
pid: P3119
tag: ['2015', 'USACO', '拓扑排序', '强连通分量', 'Tarjan']
---
# [USACO15JAN] Grass Cownoisseur G
## 题目描述

In an effort to better manage the grazing patterns of his cows, Farmer John has installed one-way cow paths all over his farm. The farm consists of N fields, conveniently numbered 1..N, with each one-way cow path connecting a pair of fields. For example, if a path connects from field X to field Y, then cows are allowed to travel from X to Y but not from Y to X.

Bessie the cow, as we all know, enjoys eating grass from as many fields as possible. She always starts in field 1 at the beginning of the day and visits a sequence of fields, returning to field 1 at the end of the day. She tries to maximize the number of distinct fields along her route, since she gets to eat the grass in each one (if she visits a field multiple times, she only eats the grass there once).

As one might imagine, Bessie is not particularly happy about the one-way restriction on FJ's paths, since this will likely reduce the number of distinct fields she can possibly visit along her daily route.  She wonders how much grass she will be able to eat if she breaks the rules and follows up to one path in the wrong direction. Please compute the maximum number of distinct fields she can visit along a route starting and ending at field 1, where she can follow up to one path along the route in the wrong direction.  Bessie can only travel backwards at most once in her journey.  In particular, she cannot even take the same path backwards twice.
## 输入格式

The first line of input contains N and M, giving the number of fields and the number of one-way paths (1 <= N, M <= 100,000). 

The following M lines each describe a one-way cow path.  Each line contains two distinct field numbers X and Y, corresponding to a cow path from X to Y.  The same cow path will never appear more than once.
## 输出格式

A single line indicating the maximum number of distinct fields Bessie can visit along a route starting and ending at field 1, given that she can follow at most one path along this route in the wrong direction.
## 样例

### 样例输入 #1
```
7 10 
1 2 
3 1 
2 5 
2 4 
3 7 
3 5 
3 6 
6 5 
7 2 
4 7 


```
### 样例输出 #1
```
6 

```
## 提示

SOLUTION NOTES:

Here is an ASCII drawing of the sample input:

```cpp
v---3-->6
7   | \ |
^\  v  \|
| \ 1   |
|   |   v
|   v   5
4<--2---^
```

Bessie can visit pastures 1, 2, 4, 7, 2, 5, 3, 1 by traveling backwards on the path between 5 and 3.  When she arrives at 3 she cannot reach 6 without following another backwards path.
## 题目翻译

### 题目描述

为了更好地管理牛群的放牧路线，Farmer John 在他的农场中安装了若干单向牛道。农场由 $N$ 块草场组成，编号为 $1$ 到 $N$，每条单向牛道连接一对草场。例如，若存在一条从草场 $X$ 到 $Y$ 的路径，则牛可以从 $X$ 前往 $Y$，但不能从 $Y$ 返回 $X$。

众所周知，Bessie 喜欢尽可能多地品尝不同草场的牧草。她每天从草场 $1$ 出发，访问一系列草场后返回草场 $1$。她试图最大化沿途经过的不同草场数量（重复访问的草场只算一次）。

由于单向路径的限制，Bessie 担心这会减少她每日路线中可以访问的草场数量。她想知道如果她违反规则，在路线中最多逆向通过某条道路一次，最多能品尝多少草场的牧草。请计算她从草场 $1$ 出发并返回的情况下，最多能访问的不同草场数量。注意 Bessie 在整个旅程中最多只能逆向通过一条道路，且同一条路径不能逆向两次。

### 输入格式

第一行包含两个整数 $N$ 和 $M$，表示草场数量和单向牛道数量（$1 \leq N, M \leq 100,000$）。

接下来 $M$ 行每行描述一条单向牛道，包含两个不同的整数 $X$ 和 $Y$，表示从 $X$ 到 $Y$ 的单向路径。保证每条路径不会重复出现。

### 输出格式

输出一行，表示 Bessie 在最多逆向通过一条道路的情况下，从草场 $1$ 出发并返回时能访问的最大不同草场数量。

### 说明/提示

**样例解析：**

以下是样例输入的 ASCII 图示：

```
v---3-->6
7   | \ |
^\  v  \|
| \ 1   |
|   |   v
|   v   5
4<--2---^
```

Bessie 可以通过逆向路径 $5\to 3$ 访问草场 $1, 2, 4, 7, 2, 5, 3, 1$。到达草场 $3$ 后，若不再次逆向其他路径则无法前往 $6$。


---

---
title: "[HNOI2012] 矿场搭建"
layout: "post"
diff: 提高+/省选-
pid: P3225
tag: ['2012', '湖南', '深度优先搜索 DFS', 'Tarjan', '双连通分量']
---
# [HNOI2012] 矿场搭建
## 题目描述

煤矿工地可以看成是由隧道连接挖煤点组成的无向图。为安全起见，希望在工地发生事故时所有挖煤点的工人都能有一条出路逃到救援出口处。于是矿主决定在某些挖煤点设立救援出口，使得无论哪一个挖煤点坍塌之后，其他挖煤点的工人都有一条道路通向救援出口。

请写一个程序，用来计算至少需要设置几个救援出口，以及不同最少救援出口的设置方案总数。

## 输入格式

输入文件有若干组数据。

每组数据的第一行是一个正整数 $N\ (N \le 500)$，表示工地的隧道数。

接下来的 $N$ 行每行是用空格隔开的两个整数 $S$ 和 $T$，表示挖煤点 $S$ 与挖煤点 $T$ 由隧道直接连接。

输入数据以 $0$ 结尾。
## 输出格式

对于每组数据，输出一行。

第 $i$ 行组数据以 $\verb!Case i: !$ 开始（注意大小写，$\verb!Case!$ 与 $\verb!i!$ 之间有空格，$\verb!i!$ 与 $\verb!:!$ 之间无空格，$\verb!:!$ 之后有空格）。

其后是用空格隔开的两个正整数，第一个正整数表示对于第 $i$ 组输入数据至少需要设置几个救援出口，第二个正整数表示对于第 $i$ 组输入数据不同最少救援出口的设置方案总数。

输入数据保证答案小于 $2^{64}$。输出格式参照以下输入输出样例。

## 样例

### 样例输入 #1
```
9
1 3
4 1
3 5
1 2
2 6
1 5
6 3
1 6
3 2
6
1 2
1 3
2 4
2 5
3 6
3 7
0
```
### 样例输出 #1
```
Case 1: 2 4
Case 2: 4 1
```
## 提示

### 样例解释

- Case 1 的四组解分别是 $(2,4)$，$(3,4)$，$(4,5)$，$(4,6)$；
- Case 2 的一组解为 $(4,5,6,7)$。

### 数据范围及约定

对于每组数据，设 $m$ 为各组 $S, T$ 中最大值，则有：

- $1 \le m \le 10^3$；
- 各组 $S, T$ 构成的集合 $V = [1, m] \cap \mathbb Z$。
- $V$ 中任意两点连通。


---

---
title: "[POI 2008] BLO-Blockade"
layout: "post"
diff: 提高+/省选-
pid: P3469
tag: ['2008', 'POI（波兰）', 'Tarjan', '双连通分量']
---
# [POI 2008] BLO-Blockade
## 题目描述

There are exactly $n$ towns in Byteotia.

Some towns are connected by bidirectional roads.

There are no crossroads outside towns, though there may be bridges,    tunnels and flyovers. Each pair of towns may be connected by at most    one direct road. One can get from any town to any other-directly    or indirectly.

Each town has exactly one citizen.

For that reason the citizens suffer from loneliness.

It turns out that each citizen would like to pay a visit to    every other citizen (in his host's hometown), and do it    exactly once. So exactly $n\cdot (n-1)$ visits should take place.

That's right, should.

Unfortunately, a general strike of programmers, who    demand an emergency purchase of software, is under way.

As an act of protest, the programmers plan to block one town of    Byteotia, preventing entering it, leaving it, and even passing through.

As we speak, they are debating which town to choose so that    the consequences are most severe.

Task    Write a programme that:

reads the Byteotian road system's description from the            standard input,           for each town determines, how many visits could take place            if this town were not blocked by programmers,           writes out the outcome to the standard output.


## 输入格式

In the first line of the standard input there are two positive    integers: $n$ and $m$ ($1\le n\le 100\ 000$, $1\le m\le 500\ 000$) denoting the number of towns and roads, respectively.

The towns are numbered from 1 to $n$.

The following $m$ lines contain descriptions of the roads.

Each line contains two integers $a$ and $b$ ($1\le a<b\le n$) and    denotes a direct road between towns numbered $a$ and $b$.

## 输出格式

Your programme should write out exactly $n$ integers to the standard    output, one number per line. The $i^{th}$ line should contain the number    of visits that could not take place if the programmers blocked the town    no. $i$.

## 样例

### 样例输入 #1
```
5 5
1 2
2 3
1 3
3 4
4 5

```
### 样例输出 #1
```
8
8
16
14
8

```
## 题目翻译

B 城有 $n$ 个城镇（从 $1$ 到 $n$ 标号）和 $m$ 条双向道路。

每条道路连结两个不同的城镇，没有重复的道路，所有城镇连通。


把城镇看作节点，把道路看作边，容易发现，整个城市构成了一个无向图。

请你对于每个节点 $i$ 求出，把与节点 $i$ 关联的所有边去掉以后（不去掉节点 $i$ 本身），无向图有多少个有序点 $(x,y)$，满足 $x$ 和 $y$ 不连通。

**【输入格式】**

第一行包含两个整数 $n$ 和 $m$。

接下来 $m$ 行，每行包含两个整数 $a$ 和 $b$，表示城镇 $a$ 和 $b$ 之间存在一条道路。

**【输出格式】**

输出共 $n$ 行，每行输出一个整数。

第 $i$ 行输出的整数表示把与节点 $i$ 关联的所有边去掉以后（不去掉节点 $i$ 本身），无向图有多少个有序点 $(x,y)$，满足 $x$ 和 $y$ 不连通。

**【数据范围】**

$n\le 100000$，$m\le500000$。


---

---
title: "[TJOI2008] 通讯网破坏"
layout: "post"
diff: 提高+/省选-
pid: P3854
tag: ['2008', '各省省选', 'Tarjan', '天津']
---
# [TJOI2008] 通讯网破坏
## 题目背景

由于争夺资源引起的矛盾冲突，$A$ 国和 $B$ 国进入了战争一触即发的状态。现在 $A$ 国的间谍机构设法得到了 $B$ 国的通讯网络布置情况，其中每个城市可以看作一个点，在某些点之间有无向边，表示这些城市之间可以进行双向的直接通讯。$A$ 国打算先发制人，通过核武器毁灭某个中间城市 $M$，一举切断B国某两个重要城市 $S$ , $T$ 之间的联系，即从图中删除掉 $M$ 点之后，$S$ 和 $T$ 变得不连通。但是由于 $B$ 国的防御力量也很强大，这样的核打击只能成功进行一次且只能毁灭一个城市。

## 题目描述

现在 $A$ 国的首脑提出了很多种作战策略，作为 $A$ 国的首席计算机科学家，你的任务是编写一个程序决定这些策略可行与否。

## 输入格式

输入文件的第一行为两个整数 $N$ 和 $M$，表示 $B$ 国的城市数和可以直接通讯的城市对数目。接下来的 $M$ 行，每行包括两个整数 $C_i$ 和 $D_i$，$1\leq C_i,D_i \leq N$ 且 $C_i \neq D_i$，表示城市 $C_i$ 和 $D_i$ 之间可以直接通讯。输入数据保证每对 $(C_i,D_i)$ 最多出现一次。

接下来一行是一个整数 $Q$，表示 $A$ 国首脑作出的策略数。接下来的 $Q$ 行，每行包括三个整数 $S_i,T_i,M_i$（$1 \leq S_i,T_i,M_i\leq N$，且 $M_i,S_i,T_i$ 三个数互不相等）表示这个策略的内容是通过毁灭 $M_i$ 来切断 $S_i$ 和 $T_i$ 之间的联系。

## 输出格式

输出 $Q$ 行，表示对应的策略可行与否。如果毁灭 $M_i$ 以后，$S_i$ 和 $T_i$ 之间不能通讯，说明此策略可行，则应在第 $i$ 行输出 $\mathtt{yes}$，否则输出 $\mathtt{no}$。

## 样例

### 样例输入 #1
```
5 6
1 2
1 3
2 3
3 4
3 5
4 5
3
1 5 3
1 5 4
4 5 3

```
### 样例输出 #1
```
yes
no
no

```
## 提示

对于 $30\%$ 的数据，$1 \leq N \leq 100,1 \leq Q \leq 100$。

对于 $100\%$ 的数据，$1 \leq N \leq 20000,1\leq M\leq 100000,1 \leq Q \leq 100000$。

输入数据保证原图的任意两点是连通的。



---

---
title: "[ZJOI2004] 嗅探器"
layout: "post"
diff: 提高+/省选-
pid: P5058
tag: ['2004', '各省省选', '浙江', 'Tarjan', '双连通分量']
---
# [ZJOI2004] 嗅探器
## 题目描述

某军搞信息对抗实战演习，红军成功地侵入了蓝军的内部网络。

蓝军共有两个信息中心，红军计划在某台中间服务器上安装一个嗅探器，从而能够侦听到两个信息中心互相交换的所有信息。

但是蓝军的网络相当的庞大，数据包从一个信息中心传到另一个信息中心可以不止有一条通路。

现在需要你尽快地解决这个问题，应该把嗅探器安装在哪个中间服务器上才能保证所有的数据包都能被捕获？
## 输入格式

输入文件的第一行一个整数 $n$，表示蓝军网络中服务器的数目。

接下来若干行是对蓝军网络的拓扑结构描述，每行是两个整数 $i,j$ 表示编号为 $i$ 和编号为 $j$ 的两台服务器间存在双向连接。

服务器的编号从 $1$ 开始，一行两个 $0$ 表示网络的拓扑结构描述结束，再接下来是两个整数 $a,b$ 分别表示两个中心服务器的编号。
## 输出格式

输出满足条件的服务器编号。如果有多个解输出编号最小的一个，如果找不到任何解，输出 `No solution`。
## 样例

### 样例输入 #1
```
5
2 1
2 5
1 4
5 3
2 3
5 1
0 0
4 2
```
### 样例输出 #1
```
1
```
## 提示

对于 $100\%$ 的数据，$1\le n\le 2 \times 10^5$，边数不超过 $5 \times 10^5$。


---

---
title: "[CEOI 2005] Critical Network Lines"
layout: "post"
diff: 提高+/省选-
pid: P7687
tag: ['2005', 'Special Judge', 'CEOI（中欧）', 'Tarjan']
---
# [CEOI 2005] Critical Network Lines
## 题目描述

一个通信网络包含若干个节点，以及若干条直接连接这些节点的双向**通信线路**。已知所研究的通信网络是连通的，即：任意一对节点之间都存在（若干条**通信线路**首尾相接而成的）**通信路径**。

一些节点会向所有节点（包括它自己）提供 $A$ 类型服务，还有一些节点会向所有节点（包括它自己）提供 $B$ 类型服务。一个节点可能会同时提供两种类型的服务。每个节点都必须要访问这两种服务。

当一条**通信线路**断开时，可能会出现某个节点不能访问某种服务的情况。（即：存在某个节点以及某种服务，使得不存在任何提供该类型服务，且与该节点连通的节点）我们称会造成这种情况的**通信线路**为**关键通信线路**。

你的任务是，写一个程序计算有多少条**关键通信线路**，并求出每条**关键通信线路**所连接的两个端点。
## 输入格式

输入第一行包含四个整数 $N,M,K,L$。其中，$N \; (1 \le N \le 10^5)$ 表示通信网络的节点数，$M \; (1 \le M \le 10^6)$ 表示通信网络的**通信线路**数，$K \; (1 \le K \le N)$ 表示提供 $A$ 类型服务的节点数，$L \; (1 \le L \le N)$ 表示提供 $B$ 类型服务的节点数。节点编号为 $1$ 到 $N$。

第二行包含 $K$ 个整数，表示提供 $A$ 类型服务的节点编号。

第三行包含 $L$ 个整数，表示提供 $B$ 类型服务的节点编号。

接下来 $M$ 行，每行包含两个整数 $p,q \; (1 \le p,q \le N,p \neq q)$，表示一条**通信线路**的两个端点的编号。保证任意两个节点之间至多只有一条**通信线路**。
## 输出格式

输出第一行包含一个整数 $S$，表示**关键通信线路**的数量。

接下来 $S$ 行，每行包含两个整数 $p,q$，表示一条**关键通信线路**所连接的两个端点的编号。

**关键通信线路**的顺序任意，每一条**关键通信线路**所连接的两个端点的顺序也任意。
## 样例

### 样例输入 #1
```
9 10 3 4
2 4 5
4 9 8 3
1 2
4 1
2 3
4 2
1 5
5 6
6 7
6 8
7 9
8 7
```
### 样例输出 #1
```
3
3 2
5 6
7 9
```
## 提示

本题为 CEOI2005 D2T2，原题面请见：[Critical Network Lines](http://ceoi.inf.elte.hu/ceoi2005/download/tasks/day2/net.htm)。

感谢 @[wsyhb](https://www.luogu.com.cn/user/145355) 提供的 Special Judge！


---

---
title: "「TAOI-1」椎名真昼"
layout: "post"
diff: 提高+/省选-
pid: P9220
tag: ['博弈论', 'O2优化', '拓扑排序', '强连通分量', 'Tarjan']
---
# 「TAOI-1」椎名真昼
## 题目背景

**请注意赛后题目添加了多测。因此请将您的赛时代码进行修改后再提交。**
## 题目描述

你正在看轻小说，突然你的家长走了进来，于是你假装在写 OI 题目。

Alice 和 Bob 正在玩一款游戏，给定一个有向图，每个点初始有一个颜色（黑或白）。

双方轮流进行操作，Alice 先手，每次操作选定一个节点，将所有从该点开始，能到达的点（包括自身）颜色翻转。如果某次操作后所有节点都变为白色，则进行该次操作的人胜利。

假如双方都采用最优策略使得自己胜利，或者如果自己无法胜利，使得对方无法胜利。

给你节点的初始状态，请你求出最终的胜者，亦或者，没有胜者。

---

定义点 $u$ 能到达点 $v$，当且仅当存在数列 $(a_1,a_2,a_3,\cdots,a_k)$，其中 $k \ge 1$，使得 $\forall i \in [1,k)$，存在有向边 $a_i \to a_{i+1}$，且 $a_1=u$，$a_k=v$。
## 输入格式

**本题有多组测试数据。**

第一行一个正整数 $T$，代表数据组数。

对于每组测试数据：

第一行两个整数 $n, m$，代表图的点数，边数。

第二行 $n$ 个整数，代表每个点开始时的颜色。$1$ 代表黑色，$0$ 代表白色。

接下来 $m$ 行，每行两个整数 $u, v$ 代表一条从 $u \to v$ 的边。
## 输出格式

对于每组测试数据：

如果最后 Alice 胜利，输出 `A`。

如果最后 Bob 胜利，输出 `B`。

如果双方（在对方的阻止下）都无法胜利，输出 `N`。

您无需输出空格或换行符。
## 样例

### 样例输入 #1
```
2
2 1
1 0
2 1
3 2
1 0 1
1 2
2 3
```
### 样例输出 #1
```
AN
```
## 提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 1（5 points）：$n \leq 2$，$m \leq 1$，$T=1$。
- Subtask 2（15 points）：$n \leq 5$，$m \leq 8$，$T=1$。
- Subtask 3（25 points）：保证所有点的初始颜色相同。
- Subtask 4（55 points）：无特殊限制。

对于所有测试数据，$1 \leq n \leq 10^5$，$1 \leq m \leq 2 \times 10^5$，$1 \le T \le 15$。

### 样例解释

在第一组数据中，Alice 可以先手对节点 $1$ 进行操作。操作后所有节点变为白色。

在第二组数据中，双方都没有必胜的方法，因此双方会互相拖延对方阻止对方获胜。

---

「据说如果无论如何都输出 `N` 的话，有 $45\%$ 的几率能够得到正确答案？」

「怎么可能，不会真的有人造出这么蠢的数据吧……」


---

