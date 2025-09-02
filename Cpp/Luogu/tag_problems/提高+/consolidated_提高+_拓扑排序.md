---
title: "[GCJ 2022 #3] Mascot Maze"
layout: "post"
diff: 提高+/省选-
pid: P12999
tag: ['贪心', '2022', 'Special Judge', '拓扑排序', 'Google Code Jam']
---
# [GCJ 2022 #3] Mascot Maze
## 题目描述

The Google Coding Competitions team is setting up a new theme park. As in any good theme park, we want to have actors dressed up as mascots to interact with visitors. Because we are in a rush to open, we decided to use the letters from CODE JAM, KICK START, and HASH CODE as mascots, for a total of 13 different mascots (the letters `ACDEHIJKMORST`).

The park's only attraction is a maze that has a set of $\mathbf{N}$ rooms numbered from 1 to $\mathbf{N}$. Each room has a left exit and a right exit. Each exit takes the visitor to another room. Exits cannot be used in reverse; for example, if room 2 has an exit to room 3, you cannot go back from room 3 to room 2 unless room 3 also happens to have an exit to room 2.

![](https://cdn.luogu.com.cn/upload/image_hosting/8fuhdtgj.png)

We want to place exactly one of our 13 mascots in each room. Each letter may be present in zero, one, or more rooms of the maze. To increase variety, we want to place mascots so that any three (not necessarily distinct) rooms that a visitor can visit consecutively have three different mascots.

Can you help us choose a mascot for each room such that this goal is met, or let us know that it cannot be done?

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of 3 lines. The first line contains a single integer $\mathbf{N}$, representing the number of rooms in the maze. The second line contains $\mathbf{N}$ integers $\mathbf{L}_1, \mathbf{L}_2, \ldots, \mathbf{L}_\mathbf{N}$, representing that the left exit from room $i$ leads to room $\mathbf{L}_i$. The third and last line contains $\mathbf{N}$ integers $\mathbf{R}_1, \mathbf{R}_2, \ldots, \mathbf{R}_\mathbf{N}$, representing that the right exit from room $i$ leads to room $\mathbf{R}_i$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is `IMPOSSIBLE` if there is no way to assign mascots while obeying the rules explained above. Otherwise, $y$ is an $\mathbf{N}$ character long string. The $i$-th character of $y$ should be an uppercase letter from the set `ACDEHIJKMORST`, representing that you wish to assign that mascot to the $i$-th room.
## 样例

### 样例输入 #1
```
4
3
2 1 1
3 3 2
6
3 1 4 1 2 3
5 3 5 2 4 5
20
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 1 1
3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 20 2
19
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 1 1
3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 19 3
```
### 样例输出 #1
```
Case #1: IMPOSSIBLE
Case #2: TSHIRT
Case #3: HCJKSHCJKSHCJKSHCJKS
Case #4: CODEJAMROCKSTHEMOST
```
## 提示

**Sample Explanation**

Sample Case #1 is the image in the problem statement. It is possible to visit rooms 1, 2, and 1 consecutively (which visits room 1 twice), so the case is impossible.

Sample Case #2 has the following layout (blue arrows represent the left exits and red arrows represent the right exits):

![](https://cdn.luogu.com.cn/upload/image_hosting/ykiviiry.png)

One of many valid answers is to assign mascots as indicated. Notice that although we do not need to assign two $\tau$ mascots in this case, we have done so in a way that does not break the rules.

Sample Cases #3 and #4 are possible, but require the use of multiple copies of some mascots.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $\mathbf{L}_i \neq i$, for all $i$. $\mathbf{R}_i \neq i$, for all $i$. $1 \leq \mathbf{L}_i < \mathbf{R}_i \leq \mathbf{N}$, for all $i$.

**Test Set 1 (12 Pts, Visible Verdict)**

- Time limit: 20 seconds.
- $3 \leq \mathbf{N} \leq 100$.

**Test Set 2 (13 Pts, Hidden Verdict)**

- Time limit: 45 seconds.
- $3 \leq \mathbf{N} \leq 10^5$.


---

---
title: "[GCJ 2019 #2] Contransmutation"
layout: "post"
diff: 提高+/省选-
pid: P13118
tag: ['动态规划 DP', '图论', '2019', '拓扑排序', '强连通分量', 'Google Code Jam']
---
# [GCJ 2019 #2] Contransmutation
## 题目描述

Last year, we asked you to help us convert expensive metals into lead. (You do not need to know anything about the previous problem to solve this one.) But your country's leader is still greedy for more lead!

There are $\mathbf{M}$ metals known in the world; lead is metal number 1 on your periodic table. Your country's leader has asked you to use the metals in the treasury to make as much lead as possible.

For each metal (including lead), you know exactly one formula that lets you destroy one gram of that metal and create one gram each of two metals. (It is best not to think too much about the principle of mass conservation!) Note that it is possible that the formula for the i-th metal might produce the i-th metal as one of the products. The formulas do not work with partial grams. However, you can use each formula as often as you would like (or not at all), as long as you have a gram of the required ingredient.

If you make optimal choices, what is the largest number of grams of lead you can end up with, or is it unbounded? If it is not unbounded: since the output can be a really big number, we only ask you to output the remainder of dividing the result by the prime $10^9+7$ (that is, $1000000007$).
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each begins with one line with an integer $\mathbf{M}$: the number of metals known in the world. Then there are $\mathbf{M}$ more lines with two integers $\mathbf{R_{i1}}$ and $\mathbf{R_{i2}}$ each; the i-th of these lines, counting starting from 1, indicates that you can destroy one gram of metal i to create one gram of metal $\mathbf{R_{i1}}$ and one gram of metal $\mathbf{R_{i2}}$. Finally, there is one line with $\mathbf{M}$ integers $\mathbf{G_1}$, $\mathbf{G_2}$, ..., $\mathbf{G_M}$; $\mathbf{G_i}$ is the number of grams of metal i in the treasury. Lead is metal 1.

## 输出格式

For each test case, output one line containing `Case #x: y` where $x$ is the test case number (starting from 1). If there is no bound on the maximum amount of lead that can be produced, $y$ must be UNBOUNDED. Otherwise, $y$ must be the largest amount of lead, in grams, that you can end up with, modulo the prime $10^9+7$ (that is, $1000000007$).
## 样例

### 样例输入 #1
```
3
2
1 2
1 2
1 0
2
1 2
1 2
0 0
4
2 4
3 4
2 4
2 3
10 10 10 10
```
### 样例输出 #1
```
Case #1: UNBOUNDED
Case #2: 0
Case #3: 10
```
## 提示

**Sample Explanation**

In Sample Case #1, you have one formula that turns 1 gram of lead into 1 gram of lead and 1 gram of the second metal, and another formula that turns 1 gram of the second metal into 1 gram of lead and 1 gram of the second metal. You can alternate between these formulas to produce as much of both metals as you want.

Sample Case #2 has the same formulas as Sample Case #1, but you have no metals to start with!

In Sample Case #3, none of the formulas help you produce more lead, so you cannot end up with more lead than you started with.

**Limits**

- $1 \leq \mathbf{R_{i1}} < \mathbf{R_{i2}} \leq \mathbf{M}$, for all $i$.

**Test set 1 (7 Pts, Visible)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{M} \leq 10$.
- $0 \leq \mathbf{G_i} \leq 10$, for all $i$.

**Test set 2 (16 Pts, Hidden)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{M} \leq 100$.
- $0 \leq \mathbf{G_i} \leq 10^9$, for all $i$.

**Test set 3 (6 Pts, Hidden)**

- $1 \leq \mathbf{T} \leq 5$.
- $2 \leq \mathbf{M} \leq 10^5$.
- $0 \leq \mathbf{G_i} \leq 10^9$, for all $i$.


---

---
title: "[SDOI2009] Elaxia的路线"
layout: "post"
diff: 提高+/省选-
pid: P2149
tag: ['2009', '各省省选', '山东', '拓扑排序', '最短路']
---
# [SDOI2009] Elaxia的路线
## 题目描述

最近，Elaxia 和 w** 的关系特别好，他们很想整天在一起，但是大学的学习太紧张了，他们必须合理地安排两个人在一起的时间。

Elaxia 和 w** 每天都要奔波于宿舍和实验室之间，他们 希望在节约时间的前提下，一起走的时间尽可能的长。

现在已知的是 Elaxia 和 w** 所在的宿舍和实验室的编号以及学校的地图：  
地图上有 $n$ 个路口，$m$ 条路，经过每条路都需要一定的时间。 具体地说，就是要求无向图中，两对点间最短路的最长公共路径。

## 输入格式

第一行两个正整数 $n,m$，表示点数和边数。
  
第二行四个正整数 $x_1,y_1,x_2,y_2$，分别表示 Elaxia 的宿舍和实验室及 w** 的宿舍和实验室的标号。

接下来 $m$ 行，每行三个整数 $u,v,w$，表示 $u,v$之间有一条边，需要 $w$ 的时间经过。
## 输出格式

一行一个整数表示答案。（即最长公共路径的长度）

## 样例

### 样例输入 #1
```
9 10
1 6 7 8
1 2 1
2 5 2
2 3 3
3 4 2
3 9 5
4 5 3
4 6 4
4 7 2
5 8 1
7 9 1
```
### 样例输出 #1
```
3
```
## 提示

【数据范围】    
对于 $30\%$ 的数据，$1\le n \le 100$；   
对于 $60\%$ 的数据，$1\le n \le 1000$；   
对于 $100\%$ 的数据，$1\le n \le 1500$，$1 \leq m \leq 3 \times 10^5$，$1\le w \le 10^4$，输入数据保证没有重边和自环。



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
title: "[HNOI2015] 菜肴制作"
layout: "post"
diff: 提高+/省选-
pid: P3243
tag: ['贪心', '2015', '湖南', '排序', '拓扑排序']
---
# [HNOI2015] 菜肴制作
## 题目描述

知名美食家小 A 被邀请至 ATM 大酒店，为其品评菜肴。ATM 酒店为小 A 准备了 $n$ 道菜肴，酒店按照为菜肴预估的质量从高到低给予 $1$ 到 $n$ 的顺序编号，预估质量最高的菜肴编号为 $1$。

由于菜肴之间口味搭配的问题，某些菜肴必须在另一些菜肴之前制作，具体的，一共有 $m$ 条形如 $i$ 号菜肴必须先于 $j$ 号菜肴制作的限制，我们将这样的限制简写为 $(i,j)$。

现在，酒店希望能求出一个最优的菜肴的制作顺序，使得小 A 能尽量先吃到质量高的菜肴：

也就是说，

1. 在满足所有限制的前提下，$1$ 号菜肴尽量优先制作。

2. 在满足所有限制，$1$ 号菜肴尽量优先制作的前提下，$2$ 号菜肴尽量优先制作。

3. 在满足所有限制，$1$ 号和 $2$ 号菜肴尽量优先的前提下，$3$ 号菜肴尽量优先制作。

4. 在满足所有限制，$1$ 号和 $2$ 号和 $3$ 号菜肴尽量优先的前提下，$4$ 号菜肴尽量优先制作。

5. 以此类推。

例 1：共 $4$ 道菜肴，两条限制 $(3,1)$、$(4,1)$，那么制作顺序是 $3,4,1,2$。

例 2：共 $5$ 道菜肴，两条限制 $(5,2)$、$(4,3)$，那么制作顺序是 $1,5,2,4,3$。

例 1 里，首先考虑 $1$，因为有限制 $(3,1)$ 和 $(4,1)$，所以只有制作完 $3$ 和 $4$ 后才能制作 $1$，而根据 3，$3$ 号又应尽量比 $4$ 号优先，所以当前可确定前三道菜的制作顺序是 $3,4,1$；接下来考虑 $2$，确定最终的制作顺序是 $3,4,1,2$。

例 $2$ 里，首先制作 $1$ 是不违背限制的；接下来考虑 $2$ 时有 $(5,2)$ 的限制，所以接下来先制作 $5$ 再制作 $2$；接下来考虑 $3$ 时有 $(4,3)$ 的限制，所以接下来先制作 $4$ 再制作 $3$，从而最终的顺序是 $1,5,2,4,3$。现在你需要求出这个最优的菜肴制作顺序。无解输出 `Impossible!`（首字母大写，其余字母小写）
## 输入格式

第一行是一个正整数 $t$，表示数据组数。接下来是 $t$ 组数据。对于每组数据：第一行两个用空格分开的正整数 $n$ 和 $m$，分别表示菜肴数目和制作顺序限制的条目数。接下来 $m$ 行，每行两个正整数 $x,y$，表示 $x$ 号菜肴必须先于 $y$ 号菜肴制作的限制。
## 输出格式

输出文件仅包含 $t$ 行，每行 $n$ 个整数，表示最优的菜肴制作顺序，或者 `Impossible!` 表示无解。

## 样例

### 样例输入 #1
```
3
5 4
5 4
5 3
4 2
3 2
3 3
1 2
2 3
3 1
5 2
5 2
4 3
```
### 样例输出 #1
```
1 5 3 4 2 

Impossible! 

1 5 2 4 3
```
## 提示

**【样例解释】**

第二组数据同时要求菜肴 $1$ 先于菜肴 $2$ 制作，菜肴 $2$ 先于菜肴 $3$ 制作，菜肴 $3$ 先于菜肴 $1$ 制作，而这是无论如何也不可能满足的，从而导致无解。

**【数据范围】**

$100\%$ 的数据满足 $n,m\le 10^5$，$1\le t\le 3$。

$m$ 条限制中可能存在完全相同的限制。


---

---
title: "[USACO18OPEN] Milking Order G"
layout: "post"
diff: 提高+/省选-
pid: P4376
tag: ['2018', '二分', 'USACO', '图论建模', '拓扑排序']
---
# [USACO18OPEN] Milking Order G
## 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 10^5$），编号为 $1 \ldots N$，最近闲得发慌。因此，她们发展了一个与 Farmer John 每天早上为她们挤牛奶时的排队顺序相关的复杂社会阶层。

经过若干周的研究，Farmer John 对他的奶牛的社会结构总计进行了 $M$ 次观察（$1 \leq M \leq 50,000$）。每个观察结果都是某些奶牛的一个有序序列，表示这些奶牛应该按照序列中的顺序进行挤奶。例如，如果 Farmer John 的一次观察结果是序列 $2$、$5$、$1$，那么 Farmer John 应该在给奶牛 $5$ 挤奶之前的某个时刻给奶牛 $2$ 挤奶，并在给奶牛 $1$ 挤奶之前的某个时刻给奶牛 $5$ 挤奶。

Farmer John 的观察结果是按优先级排列的，因此他的目标是最大化 $X$ 的值，使得他的挤奶顺序能够符合前 $X$ 个观察结果描述的状态。当多种挤奶顺序都能符合前 $X$ 个状态时，Farmer John 遵循一个长期以来的传统——编号较小的奶牛的地位高于编号较大的奶牛，因此他会最先给编号最小的奶牛挤奶。更正式地说，如果有多个挤奶顺序符合这些状态，Farmer John 会采用字典序最小的那一个。挤奶顺序 $x$ 的字典序比挤奶顺序 $y$ 小，如果对于某个 $j$，$x_i = y_i$ 对所有 $i < j$ 成立，并且 $x_j < y_j$（即这两个挤奶顺序到某个位置之前完全相同，而在该位置上 $x$ 比 $y$ 小）。

请帮助 Farmer John 确定给奶牛挤奶的最佳顺序。
## 输入格式

第一行包含 $N$ 和 $M$。接下来的 $M$ 行，每行描述了一个观察结果。第 $i+1$ 行描述了观察结果 $i$，第一个数是观察结果中的奶牛数量 $m_i$，后面是一列 $m_i$ 个整数，给出这次观察中奶牛的顺序。所有 $m_i$ 的总和至多为 $200,000$。
## 输出格式

输出 $N$ 个空格分隔的整数，表示一个 $1 \ldots N$ 的排列，为 Farmer John 给他的奶牛们挤奶应该采用的顺序。
## 样例

### 样例输入 #1
```
4 3
3 1 2 3
2 4 2
3 3 4 1
```
### 样例输出 #1
```
1 4 2 3

```
## 提示

在这个例子中，Farmer John 有四头奶牛，他的挤奶顺序应该满足以下规则：奶牛 $1$ 在奶牛 $2$ 之前、奶牛 $2$ 在奶牛 $3$ 之前（第一个观察结果），奶牛 $4$ 在奶牛 $2$ 之前（第二个观察结果），奶牛 $3$ 在奶牛 $4$ 之前、奶牛 $4$ 在奶牛 $1$ 之前（第三个观察结果）。前两个观察结果可以同时被满足，但 Farmer John 不能同时满足所有规则，因为这会要求奶牛 $1$ 在奶牛 $3$ 之前，同时奶牛 $3$ 在奶牛 $1$ 之前。

这意味着总共有两种可能的挤奶顺序：$1\ 4\ 2\ 3$ 和 $4\ 1\ 2\ 3$，第一种是字典序较小的。

题目来源：Jay Leeds


---

---
title: "[Wind Festival] Running In The Sky"
layout: "post"
diff: 提高+/省选-
pid: P4742
tag: ['图论建模', '拓扑排序', '强连通分量']
---
# [Wind Festival] Running In The Sky
## 题目背景

$[Night - 20:02$ $P.M.]$

夜空真美啊……但是……快要结束了呢……
## 题目描述

一天的活动过后，所有学生都停下来欣赏夜空下点亮的风筝。$Curtis$ $Nishikino$想要以更近的视角感受一下，所以她跑到空中的风筝上去了(这对于一个妹子来说有点匪夷所思)! 每只风筝上的灯光都有一个亮度 $k_i$. 由于风的作用，一些风筝缠在了一起。但是这并不会破坏美妙的气氛，缠在一起的风筝会将灯光汇聚起来，形成更亮的光源！

$Curtis$ $Nishikino$已经知道了一些风筝间的关系，比如给出一对风筝$(a,b)$, 这意味着她可以从 $a$ 跑到 $b$ 上去，但是不能返回。

现在，请帮她找到一条路径(她可以到达一只风筝多次，但只在第一次到达时她会去感受上面的灯光), 使得她可以感受到最多的光亮。同时请告诉她这条路径上单只风筝的最大亮度，如果有多条符合条件的路径，输出能产生最大单只风筝亮度的答案。
## 输入格式

第一行两个整数 $n$ 和 $m$. $n$ 是风筝的数量, $m$ 是风筝间关系对的数量. 

接下来一行 $n$ 个整数 $k_i$.

接下来 $m$ 行, 每行两个整数 $a$ 和 $b$, 即$Curtis$可以从 $a$ 跑到 $b$.
## 输出格式

一行两个整数。$Curtis$在计算出的路径上感受到的亮度和，这条路径上的单只风筝最大亮度.
## 样例

### 样例输入 #1
```
5 5
8 9 11 6 7
1 2
2 3
2 4
4 5
5 2
```
### 样例输出 #1
```
41 11
```
## 提示

对于 $20\%$ 的数据, $0<n \le 5\times10^3, \ 0 < m \le 10^4$.

对于 $80\%$ 的数据, $0 < n \le 10^5, \ 0 < m \le 3\times10^5$.

对于 $100\%$ 的数据, $0<n\le2\times10^5,\ 0<m\le5\times10^5,\ 0<k\le200$.



---

---
title: "[COCI 2016/2017 #1] Cezar"
layout: "post"
diff: 提高+/省选-
pid: P6286
tag: ['字符串', '2016', 'Special Judge', '拓扑排序', '字典树 Trie', 'COCI（克罗地亚）']
---
# [COCI 2016/2017 #1] Cezar
## 题目描述

Mirko 想对 $n$ 个单词进行加密。加密过程是这样的：

1.  选择一个英文字母表的排列作为密钥。
2.  将单词中的 `a` 替换为密钥中的第一个字母，`b` 替换为密钥中的第二个字母……以此类推。

例如，以 `qwertyuiopasdfghjklzxcvbnm` 作为密钥对 `cezar` 加密后，将得到 `etmqk`。

他希望，将所有单词加密并按字典序升序排列后，最初的第 $a_i$ 个单词位于第 $i$ 位。请你判断，这能否实现。如果能，请给出任意一种可行的密钥。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，每行一个字符串，表示待加密的单词。

最后一行 $n$ 个整数，表示 $a_i$。
## 输出格式

**本题使用 Special Judge**。

如果 Mirko 的要求不能实现，输出 `NE`。

否则，输出 `DA`。接下来一行输出任意一种可行的密钥。
## 样例

### 样例输入 #1
```
2
ab
bc
2 1 
```
### 样例输出 #1
```
DA
bacdefghijklmnopqrstuvwxyz 
```
### 样例输入 #2
```
3
abc
bcd
add
1 2 3 
```
### 样例输出 #2
```
NE 
```
### 样例输入 #3
```
3
bbb
ccc
ddd
2 3 1 
```
### 样例输出 #3
```
DA
adbcefghijklmnopqrstuvwxyz 
```
## 提示

#### 【样例解释】

**样例 1 解释**

以 `bacdefghijklmnopqrstuvwxyz` 为密钥加密后，得到：

- `ba`
- `ac`

字典序升序排列后，得到：

- `ac`
- `ba`

原先的第一个单词在第二位，第二个单词在第一位。符合要求。

**样例 3 解释**

以 `adbcefghijklmnopqrstuvwxyz`  为密钥加密后，得到：

- `ddd`
- `bbb`
- `ccc`

字典序升序排列后，得到：

- `bbb`
- `ddd`
- `ccc`

原先的第一个单词在第二位，第二个单词在第三位，第三个单词在第一位。符合要求。

---

#### 数据规模与约定

对于 $100\%$ 的数据，$2\le n\le 100$，$1 \leq a_i \leq n$。

所有单词的长度不超过 $100$，且只包含小写字母。

------------

#### 说明

**题目译自 [COCI2016-2017](https://hsin.hr/coci/archive/2016_2017/) [CONTEST #1](https://hsin.hr/coci/archive/2016_2017/contest1_tasks.pdf) _T3 Cezar_**。


---

---
title: "『MdOI R2』Odyssey"
layout: "post"
diff: 提高+/省选-
pid: P6381
tag: ['动态规划 DP', '数学', '图论', '拓扑排序', '素数判断,质数,筛法', '洛谷月赛']
---
# 『MdOI R2』Odyssey
## 题目背景

超越音速的极限，不及瑰丽多变的极光；

微弱的脉冲，开拓原本一片混沌的天地；

沉郁的蓝缓缓闪动，史诗的红迎接巅峰；

血色的夕阳尽头，是将夜的星辰；

夜半的满天星空，也会被来自地狱的硝烟掩盖；

炽红炼狱消逝，只金色遗迹永存。

在这里等待着每一位的，都是一段艰苦而璀璨的旅程。
## 题目描述

若正整数 $a$ 与 $b$ 满足：

- $a$ 与 $b$ 的积是一个正整数的 $k$ 次方，即存在正整数 $c$ 使得 $ab=c^k$。

那么我们称 $(a,b)$ 为一组**完美数对**。

---

有一个包含 $n$ 个结点和 $m$ 条边的**有向无环图**，这张图中的每条边都有权值和长度两个属性。

如果一条路径 $P$ 满足**以下条件之一**，则称其为一条**完美路径**：

- $P$ 中仅包含一条边。

- $P$ 从其起点开始依次为 $e_1, e_2, e_3, \ldots e_p$ 这 $p\ (p\ge 2)$ 条边，对于任意的 $1\leq i\leq p-1$，$e_i$ 的权值和 $e_{i+1}$ 的权值组成完美数对。

你需要求出图中最长完美路径的长度，一条路径的长度定义为这条路径上所有边的长度之和。
## 输入格式

第一行：三个整数 $n,m,k$，分别表示有向无环图的结点数、边数和完美数对的参数。

接下来 $m$ 行：每行四个整数 $u,v,w,l$，表示有一条权值为 $w$，长度为 $l$ 的有向边从 $u$ 连向 $v$。
## 输出格式

第一行：一个整数 $ans$，表示最长完美路径的长度。
## 样例

### 样例输入 #1
```
5 7 2
2 5 2 5
5 3 18 9
2 4 6 7
4 3 6 3
2 1 24 2
1 4 6 8
1 5 8 4
```
### 样例输出 #1
```
14
```
## 提示

【帮助与提示】  

为方便选手测试代码，本题额外提供两组附加样例供选手使用。  

[样例输入1](https://www.luogu.com.cn/paste/wx1lz6m2) [样例输出1](https://www.luogu.com.cn/paste/28xe7f0x)      

[样例输入2](https://www.luogu.com.cn/paste/efgwngs5) [样例输出2](https://www.luogu.com.cn/paste/5hcpoayt)   

----

【样例解释】

样例中给出的有向无环图如图所示，其中边上的红色数字为边的权值，黑色数字为边的长度：

![](https://cdn.luogu.com.cn/upload/image_hosting/w6x03ksd.png)

最长完美路径为 $2\to 5\to 3$，因为这两条边的权值 $2$ 和 $18$ 满足 $2\times 18=6^2$，是完美数对，此路径长度为 $5+9=14$。

此外，$2\to 1\to 4\to 3,\ \ 2\to 4\to 3,\ \ 1\to 5\to 3$ 等也是完美路径，但不是最长的。

图中，$2\to 1\to 5\to 3$ 长度为 $15$，是一条更长的路径，但它并不是完美路径，因为前两个边权 $24$ 和 $8$ 的乘积为 $192$，不是正整数的平方，即 $(24,8)$ 不是完美数对。

---

【数据范围】

**本题采用捆绑测试。**

对于 $100\%$ 的数据：$1\leq n\leq 10^5,\ \ 1\leq m\leq 2\times 10^5,\ \ 1\leq k\leq 10,\ \ 1\leq u,v\leq n,\ \ 1\leq w\leq 10^5,\ \ 1\leq l\leq 10^4$。

给出的图**不保证弱连通**，图中从一个点到另一个点**可能**存在多条边，但保证给出的图是有向无环图。

| 子任务编号 | $n\leq$ |     $m\leq$      | $w\leq$ | $k\leq$ |  特殊性质  | 分值 |
| :--------: | :-----: | :--------------: | :-----: | :-----: | :--------: | :--: |
| Subtask 1  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $1$   |     无     | $18$ |
| Subtask 2  |  $10$   |       $10$       |  $100$  |  $2$   |     无     | $12$ |
| Subtask 3  |  $600$  | $1.5\times 10^3$ | $10^3$  |   $2$   |     无     | $10$ |
| Subtask 4  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $2$   | $w$ 为素数 | $15$ |
| Subtask 5  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $2$   |     无     | $15$ |
| Subtask 6  |  $600$  | $1.5\times 10^3$ | $10^3$  |  $5$   |     无     | $10$ |
| Subtask 7  | $10^5$  |  $2\times 10^5$  | $10^5$  |  $10$   |     无     | $20$ |




---

---
title: "「SWTR-5」Chain"
layout: "post"
diff: 提高+/省选-
pid: P6651
tag: ['动态规划 DP', 'O2优化', '拓扑排序', '容斥原理']
---
# 「SWTR-5」Chain
## 题目描述

给定 $n$ 个点，$m$ 条边的有向无环图。不保证图连通。

$q$ 次询问，每次给出 $k$ 和 $k$ 个互不相同的数 $c_i$，求出如果去掉这 $k$ 个点，整个有向无环图将剩余多少条链。答案对 $10^9+7$ 取模。**每次询问独立。**

- “链”的定义是：我们设一条长度为 $p$ 的链的路径为 $w_0\to w_1\to\cdots\to w_{p-1}\to w_p$，则应满足 $w_0$ 入度为 $0$，$w_p$ 出度为 $0$。你可以将其理解为一条食物链。

- 两条链是“不同的”，当且仅当它们的长度不同，或者经过的点集不同。

- **需要特别注意的是，删去某些点后新产生的链不计入答案。** 例如 $1\to 2\to 3\to 4$ 一图中，有 $1$ 条链 $1\to 2\to 3\to 4$。如果去掉 $2$ 号点，则剩余 $0$ 条链。
## 输入格式

第一行两个整数 $n,m$，分别表示点的个数和边的条数。

接下来 $m$ 行，每行两个整数 $u,v(u\neq v)$，表示 $u\to v$ 有一条有向边。

第 $m+2$ 行一个整数 $q$，表示询问个数。

接下来 $q$ 行：  
- 每行先是一个整数 $k$，表示去掉的点的个数。
- 接下来 $k$ 个整数 $c_i$，表示去掉的点的编号。
## 输出格式

共 $q$ 行，每行表示该次询问答案对 $10^9+7$ 取模后的值。
## 样例

### 样例输入 #1
```
7 14
3 2
4 5
2 5
2 6
3 1
3 5
3 7
3 6
6 4
1 4
6 5
1 6
7 2
7 4
7
3 2 4 6
2 4 6
2 2 5
2 1 4
0
1 4
1 6
```
### 样例输出 #1
```
1
3
0
6
13
7
5
```
### 样例输入 #2
```
233 1
1 2
6
0
1 10
2 10 40
1 1
1 2
2 1 2
```
### 样例输出 #2
```
232
231
230
231
231
231
```
## 提示

「样例 $1$ 说明」

DAG 如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2gbdoemh.png)

询问 $1$：如果去掉 $2,4,6$，则剩余 $1$ 条链：$3\to 5$。

询问 $2$：如果去掉 $4,6$，则剩余 $3$ 条链：$3\to 5$，$3\to 2\to 5$，$3\to 7\to 2\to 5$。

询问 $7$：如果去掉 $6$，则剩余 $5$ 条链：$3\to 5$，$3\to 2\to 5$，$3\to 7\to 2\to 5$，$3\to 1\to 4\to 5$，$3\to 7\to 4\to 5$。

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（1 point）：给定的图是一条链。
- Subtask 2（14 points）：$n,q\leq 10$。
- Subtask 3（20 points）：$q\leq 10^3$。
- Subtask 4（17 points）：$k=1$。
- Subtask 5（18 points）：$k=2$。
- Subtask 6（30 points）：无特殊限制。

对于 $100\%$ 的数据：$2\leq n\leq 2\times 10^3$，$1\leq m\leq \min(\frac{n\times(n-1)}{2},2\times 10^4)$，$1\leq q\leq 5\times 10^5$。  
所有询问满足：$1\leq \sum k\leq 2\times 10^6$，$0\leq k\leq \min(n,15)$，$1\leq c_i\leq n$。保证 $c_i$ 互不相同。

**本题轻微卡常，请注意 IO 优化。**

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) D。  
idea & solution：[Alex_Wei](https://www.luogu.com.cn/user/123294)。


---

---
title: "[CSP-S2020] 函数调用"
layout: "post"
diff: 提高+/省选-
pid: P7077
tag: ['动态规划 DP', '数学', '2020', '拓扑排序', 'CSP-S 提高级']
---
# [CSP-S2020] 函数调用
## 题目描述

函数是各种编程语言中一项重要的概念，借助函数，我们总可以将复杂的任务分解成一个个相对简单的子任务，直到细化为十分简单的基础操作，从而使代码的组织更加严密、更加有条理。然而，过多的函数调用也会导致额外的开销，影响程序的运行效率。

某数据库应用程序提供了若干函数用以维护数据。已知这些函数的功能可分为三类：

1. 将数据中的指定元素加上一个值；
2. 将数据中的每一个元素乘以一个相同值；
3. **依次**执行若干次函数调用，保证不会出现递归（即不会直接或间接地调用本身）。

在使用该数据库应用时，用户可一次性输入要调用的函数序列（一个函数可能被调用多次），在**依次**执行完序列中的函数后，系统中的数据被加以更新。某一天，小 A 在应用该数据库程序处理数据时遇到了困难：由于频繁而低效的函数调用，系统在执行操作时进入了无响应的状态，他只好强制结束了数据库程序。为了计算出正确数据，小 A 查阅了软件的文档，了解到每个函数的具体功能信息，现在他想请你根据这些信息帮他计算出更新后的数据应该是多少。
## 输入格式

第一行一个正整数 $n$，表示数据的个数。  
第二行 $n$ 个整数，第 $i$ 个整数表示下标为 $i$ 的数据的初始值为 $a_i$。  
第三行一个正整数 $m$，表示数据库应用程序提供的函数个数。函数从 $1 \sim m$ 编号。  
接下来 $m$ 行中，第 $j$（$1 \le j \le m$）行的第一个整数为 $T_j$，表示 $j$ 号函数的类型：

1. 若 $T_j = 1$，接下来两个整数 $P_j, V_j$ 分别表示要执行加法的元素的下标及其增加的值；
2. 若 $T_j = 2$，接下来一个整数 $V_j$ 表示所有元素所乘的值；
3. 若 $T_j = 3$，接下来一个正整数 $C_j$ 表示 $j$ 号函数要调用的函数个数，  
  随后 $C_j$ 个整数 $g^{(j)}_1, g^{(j)}_2, \ldots , g^{(j)}_{C_j}$ 依次表示其所调用的函数的编号。

第 $m + 4$ 行一个正整数 $Q$，表示输入的函数操作序列长度。  
第 $m + 5$ 行 $Q$ 个整数 $f_i$，第 $i$ 个整数表示第 $i$ 个执行的函数的编号。
## 输出格式

一行 $n$ 个用空格隔开的整数，按照下标 $1 \sim n$ 的顺序，分别输出在执行完输入的函数序列后，数据库中每一个元素的值。**答案对** $\boldsymbol{998244353}$ **取模。**
## 样例

### 样例输入 #1
```
3
1 2 3
3
1 1 1
2 2
3 2 1 2
2
2 3

```
### 样例输出 #1
```
6 8 12
```
### 样例输入 #2
```
10
1 2 3 4 5 6 7 8 9 10
8
3 2 2 3
3 2 4 5
3 2 5 8
2 2
3 2 6 7
1 2 5
1 7 6
2 3
3
1 2 3
```
### 样例输出 #2
```
36 282 108 144 180 216 504 288 324 360

```
### 样例输入 #3
```
见附件中的 call/call3.in
```
### 样例输出 #3
```
见附件中的 call/call3.ans
```
## 提示

**【样例 #1 解释】**

$1$ 号函数功能为将 $a_1$ 的值加一。$2$ 号函数功能为所有元素乘 $2$。$3$ 号函数将先调用 $1$ 号函数，再调用 $2$ 号函数。

最终的函数序列先执行 $2$ 号函数，所有元素的值变为 $2, 4, 6$。

再执行 $3$ 号函数时，先调用 $1$ 号函数，所有元素的值变为 $3, 4, 6$。再调用 $2$ 号函数，所有元素的值变为 $6, 8, 12$。

**【数据范围】**

| 测试点编号 | $n, m, Q \le$ | $\sum C_j$ | 其他特殊限制 |
| :----------: | :----------: | :----------: | :----------: |
| $1 \sim 2$ | $1000$ | $= m - 1$ | 函数调用关系构成一棵树 |
| $3 \sim 4$ | $1000$ | $\le 100$ | 无 |
| $5 \sim 6$ | $20000$ | $\le 40000$ | 不含第 $2$ 类函数或不含第 $1$ 类函数 |
| $7$ | $20000$ | $= 0$ | 无 |
| $8 \sim 9$ | $20000$ | $= m - 1$ | 函数调用关系构成一棵树 |
| $10 \sim 11$ | $20000$ | $\le 2 \times 10^5$ | 无 |
| $12 \sim 13$ | $10^5$ | $\le 2 \times 10^5$ | 不含第 $2$ 类函数或不含第 $1$ 类函数 |
| $14$ | $10^5$ | $= 0$ | 无 |
| $15 \sim 16$ | $10^5$ | $= m - 1$ | 函数调用关系构成一棵树 |
| $17 \sim 18$ | $10^5$ | $\le 5 \times 10^5$ | 无 |
| $19 \sim 20$ | $10^5$ | $\le 10^6$ | 无 |

对于所有数据：$0 \le a_i \le 10^4$，$T_j \in \{1,2,3\}$，$1 \le P_j \le n$，$0 \le V_j \le 10^4$，$1 \le g^{(j)}_k \le m$，$1 \le f_i \le m$。


---

---
title: "「dWoi R2」Change / 改造"
layout: "post"
diff: 提高+/省选-
pid: P7845
tag: ['图论', '拓扑排序']
---
# 「dWoi R2」Change / 改造
## 题目背景

入间改造对人类生存繁殖有帮助的工具（~~就是性能工具，具体可以去看看弹丸论破 V3 自由时间与入间美兔的交谈，在这里不方便说吧，毕竟是 青 少 年 编 程 网 站~~）玩腻了，她发现了有一个很 符 合 她 胃 口 的东西，叫做 Galgame，于是她开始打一款叫做 Little Busters 的 Galgame，然后沉迷上了沙耶线最后的场景。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/vxy5rh6c.png)

## 题目描述

在经过 $99$ 次的 Replay 后，沙耶终于发现迷宫是一个有向无环图。为了保证最后一次 Replay 的趣味性，时风瞬给沙耶和理树安排了一个小游戏。

这张有向无环图 $G$ 有 $n$ 个点，$m$ 条边，每条边的长度为 $1$。设 $l_i$ 为初始点 $s$ 到第 $i$ 条边所指向的点 $u$ 的最短路，定义第 $i$ 条边的边权为 $p-l_i$。游戏步骤是这样的（所有选择都是按如下顺序进行，并且每个人的选择都是公开的）。

1. 理树站在点 $s$ 上。  
2. 时风瞬会随机选取一个点作为 $t$（$t$ 可以等于 $s$）。
3. 如果无法从 $s$ 到达 $t$，游戏直接结束。
3. 沙耶需要选择一条边。
4. 理树需要找到一条从 $s$ 到 $t$ 的路径。
5. 若沙耶选择的边在理树所选择的路径上，则理树就会将这条边的边权的钱给沙耶。

理树希望能少输钱，沙耶希望能多拿钱。若两方都采取最优策略，请问沙耶期望能得到多少钱。
## 输入格式

第一行四个整数 $n,m,s,p$，分别代表有向图点数，边数与理树站在的位置，以及题目中出现的 $p$。

接下来 $m$ 行每行两个整数 $u_i,v_i$ 描述一条边。
## 输出格式

一行一个整数代表答案。

请对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
8 8 1 10
1 2
1 3
1 4
2 5
3 5
5 6
6 7
6 8
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
3 2 1 3
1 2
1 3
```
### 样例输出 #2
```
332748119
```
## 提示

#### 样例 1 解释

比如 $t=6$ 时，沙耶应该选择连接 $5,6$ 的那条边；$t=8$ 时，沙耶仍然应该选择连接 $5,6$ 的那条边；$t=4$ 时，应该选择连接 $1,4$ 的那条边；$t=5$ 时，沙耶无论选择什么边都不会得到钱。

设 $res_u$ 表示 $t=u$ 时沙耶能获得的最大收益，我们有 $res=\{0,9,9,9,0,7,7,7\}$。

#### 样例 2 解释

设 $res_u$ 表示 $t=u$ 时沙耶能获得的最大收益，我们有 $res=\{0,2,2\}$。

---

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$n,m \le 5$；
- Subtask 2（20 pts）：$m=n-1$，$u_i<v_i$，$s=1$；
- Subtask 3（30 pts）：$n,m \le 10^3$；
- Subtask 4（40 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,m \le 5 \times 10^6$，$1 \le s \le n$，$1 \le u_i,v_i \le n$，$u_i \ne v_i$，$n\le p \le 10^9$。


---

---
title: "[USACO22JAN] Minimizing Haybales P"
layout: "post"
diff: 提高+/省选-
pid: P8099
tag: ['线段树', '二分', 'USACO', '2022', '拓扑排序']
---
# [USACO22JAN] Minimizing Haybales P
## 题目描述

Bessie 感到无聊，于是又在 Farmer John 的牛棚里制造麻烦。FJ 有 $N$（$1 \le N \le 10^5$）堆草堆。对于每个 $i \in [1,N]$，第 $i$ 堆草堆有 $h_i$（$1 \le h_i \le 10^9$）的草。Bessie 不想让任何的草倒下来，所以她唯一可以执行的操作为：

- 如果两个相邻的草堆的高度相差不超过 $K$（$1 \le K \le 10^9$），她可以交换这两堆草堆。

Bessie 在一系列这样的操作之后可以得到的的字典序最小的高度序列是什么？
## 输入格式

输入的第一行包含 $N$ 和 $K$。第 $i+1$ 行包含第 $i$ 堆草堆的高度。
## 输出格式

输出 $N$ 行，第 $i$ 行包含答案中第 $i$ 堆草堆的高度。
## 样例

### 样例输入 #1
```
5 3
7
7
3
6
2
```
### 样例输出 #1
```
6
7
7
2
3
```
## 提示

【样例解释】

一种 Bessie 可以交换草堆的方式如下：

```plain
   7 7 3 6 2
-> 7 7 6 3 2
-> 7 7 6 2 3
-> 7 6 7 2 3
-> 6 7 7 2 3
```

【数据范围】

- 所有测试点的 $10\%$ 满足 $N \le 100$。
- 所有测试点的另外 $20\%$ 满足 $N \le 5000$。
- 其余 $70\%$ 的测试点没有额外限制。

供题：Daniel Zhang，Benjamin Qi


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

---
title: "[YsOI2023] 广度优先遍历"
layout: "post"
diff: 提高+/省选-
pid: P9534
tag: ['洛谷原创', 'Special Judge', 'O2优化', '广度优先搜索 BFS', '拓扑排序', '最近公共祖先 LCA', '洛谷月赛']
---
# [YsOI2023] 广度优先遍历
## 题目背景

Ysuperman 模板测试的图论题。

【数据删除】
## 题目描述

今天的模板测试是无向图上的广度优先遍历，【数据删除】马上写好了代码：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn = 100005;
vector<int> G[maxn];
queue<int> q;
int pa[maxn];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(pa, -1, sizeof pa);
    q.push(1);
    pa[1] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : G[u])
        {
            if (pa[v] != -1)
                continue;
            pa[v] = u;
            q.push(v);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << pa[i];
        if (i != n)
            cout << " ";
    }
    cout << endl;
    return 0;
}
```

如你所见，这份代码会输入一个 $n$ 个点 $m$ 条边的无向图，并且求出这张图以 $1$ 为根的一棵“广度优先遍历树”，最后输出所有点的父亲节点编号。

不过值得注意的是，这棵“广度优先遍历树”的具体形态和“边的输入顺序”有关，也就是说，不同的输入顺序可能会得到不同的父亲节点编号。

现在【数据删除】告诉了你 $n,m$、这 $m$ 条边以及在某个“边输入顺序”情况下他的代码的输出，你需要还原出这个“边输入顺序”。如果有多种边输入顺序对应的都是这样的输出，你**只需要输出其中任意一种**即可。

特别的，保证有解，且无向图连通，无自环（但是有可能有重边）。
## 输入格式

第一行两个正整数 $n,m$ 分别表示无向图的点数和边数。

接下来 $m$ 行每行两个整数 $u,v$ 表示存在 $u$ 与 $v$ 之间存在一条无向边。

最后一行 $n$ 个整数表示【数据删除】代码的输出。（由题意可知他输出的是某个“边输入顺序”情况下他得到的“广度优先遍历树”中 $1\sim n$ 这些节点的父亲节点编号）
## 输出格式

输出包含 $m$ 行，每行两个整数 $u,v$ 表示 $u$ 和 $v$ 之间存在一条无向边，你的输出顺序表示你给出的“边输入顺序”。

请注意，你需要保证如果输入给出的图中 $u,v$ 间连了 $k$ 条边，那么你给出的图中 $u,v$ 间也要连有 $k$ 条边。

如果有多种“边输入顺序”合法，**输出其中任意一种都会被判断为正确**。另外，由于是无向边，所以你输出的**一条边两个点的排列顺序对答案判定没有影响**。
## 样例

### 样例输入 #1
```
4 4
2 1
1 3
2 4
4 3
0 1 1 3
```
### 样例输出 #1
```
1 3
3 4
1 2
2 4

```
### 样例输入 #2
```
8 9
7 8
6 1
5 4
7 1
4 1
3 7
2 6
7 5
2 4
0 6 7 1 4 1 1 7
```
### 样例输出 #2
```
6 2
7 3
4 5
1 6
7 8
1 4
1 7
2 4
5 7
```
## 提示

#### 样例 1 解释

直接运行【数据删除】的代码即可。

如果不改变边输入顺序，将下面数据输入【数据删除】的代码：

```
4 4
2 1
1 3
2 4
4 3
```

他的代码跑出来结果如下：

```
0 1 1 2
```

如果按照样例 1 输出给出的顺序，即，将下面数据输入他的代码：

```
4 4
1 3
3 4
1 2
2 4
```

输出为：

```
0 1 1 3
```

#### 数据范围

对于前 $10\%$ 的数据，满足 $n\le 8$，$m\le 10$。

对于前 $40\%$ 的数据，满足 $n\le 1000$，$m\le 2000$。

另有 $10\%$ 的数据，满足 $m=n-1$。

对于 $100\%$ 的数据，满足 $1\le n\le 10^5$，$1\le m\le 2\times 10^5$。

#### 提示

为什么有可能会有重边，因为懒得去重了，这个家伙出图论题就是懒得判重边的（）

附件下发了本题 checker。


---

