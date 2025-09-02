---
title: "[中山市赛 2024/科大国创杯小学组 2023] 六形棋/海克斯"
layout: "post"
diff: 普及/提高-
pid: B4186
tag: ['搜索', '2023', '2024', '安徽', '广东', '连通块', '科创活动', '小学活动', '科大国创杯']
---
# [中山市赛 2024/科大国创杯小学组 2023] 六形棋/海克斯
## 题目背景

本题题面为 2024 年中山市赛版本，在输出格式上与 2023 年安徽省科大国创杯小学组略有区别。
## 题目描述

Jimmy 和 Chen 在下一种奇怪的棋，叫做六形棋。

棋盘由 $N \times N$ 个六边形格子构成，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ir3oamly.png)

当棋盘上的两个六边形格子有一条边重合的时候，我们称两个格子是互相连通的。将从上往下第 $i$ 行、从左到右第 $j$ 个格子称为 $(i, j)$。对于一个不在边界上的格子 $(i, j)$，它和 $(i, j + 1)$，$(i, j - 1)$，$(i + 1, j)$，$(i + 1, j - 1)$，$(i - 1, j)$，$(i - 1, j + 1)$ 这 $6$ 个格子互相连通，而边界上的格子只与上述格子中未出界的格子互相连通。

六形棋的游戏规则如下：两人轮流下棋，Jimmy 先手，Jimmy 每次选一个空的格子下一个红色棋子，接下来 Chen 每次选一个空的格子下一个蓝色棋子，依次类推。如果最后 Jimmy 将上下两条红色的边界用红色棋子连通了，那么 Jimmy 胜；相反，如果 Chen 将左右两条蓝色边界用蓝色棋子连通了，那么 Chen 胜。

接下来给出若干个六形棋的棋盘，请你判断每一局是 Jimmy 胜，还是 Chen 胜，还是目前未分出胜负（容易证明，不可能两人都达到获胜条件）。
## 输入格式

本题输入有多组测试数据。

第一行一个正整数 $T$，代表他们下了 $T$ 盘棋。

每组数据的第一行为一个正整数 $N$，代表棋盘的大小。

每组数据的第 $2 \sim N + 1$ 行，每行 $N$ 个 $-1, 0, 1$ 中的整数，第 $i + 1$ 行的第 $j$ 个整数代表格子 $(i, j)$ 的状态，如果为 $-1$ 则该格子中为蓝色棋子，如果为 $0$ 则该格子为空，如果为 $1$ 则该格子中为红色棋子。
## 输出格式

输出共 $T$ 行，每行一个字符串，表示输入的棋盘对应的局面：如果 Jimmy 胜，则输出 $\tt{Jimmy}$；如果 Chen 胜，则输出 $\tt{Chen}$；如果目前未分出胜负，则输出 $\tt{yet}$。注意：$\tt{Jimmy}$ 和 $\tt{Chen}$ 的首字母都需要大写。
## 样例

### 样例输入 #1
```
3
4
0 1 0 -1
0 -1 1 0
-1 -1 1 0
0 0 1 0
4
0 1 1 -1
0 -1 1 0
-1 -1 1 0
0 0 1 0
4
0 1 -1 -1
0 -1 1 1
-1 -1 1 0
0 0 1 0
```
### 样例输出 #1
```
yet
Jimmy
Chen
```
## 提示

### 样例解释

在第一个棋盘中，不存在将上下边界连通的红色棋子序列，也不存在将左右边界连通蓝色棋子序列，故目前未分出胜负。

在第二个棋盘中，上下两个边界由 $(1, 3),(2, 3),(3, 3),(4, 3)$ 这些红色棋子连通了，所以 Jimmy 获胜了。

在第三个棋盘中，左右两个边界由 $(3, 1),(2, 2),(1, 3),(1, 4)$ 这些蓝色棋子连通了，所以 Chen 获胜了。

### 数据范围

- 对于 $20\%$ 的数据，保证 $1 \leq N \leq 3$。
- 对于另外 $40\%$ 的数据，保证给出的棋局已经分出胜负。
- 对于 $100\%$ 的数据，保证 $1 \leq T \leq 10$，$1 \leq N \leq 100$。


---

---
title: "[蓝桥杯青少年组国赛 2022] 翻卡片"
layout: "post"
diff: 普及/提高-
pid: B4297
tag: ['2022', '枚举', '连通块', '蓝桥杯青少年组']
---
# [蓝桥杯青少年组国赛 2022] 翻卡片
## 题目描述

小蓝在玩翻卡片游戏，每张卡片一面写着大写字母 `A`，另一面写着大写字母 `B`。首先将卡片排成一个 $N \times N$ 的矩阵。有的卡片是 `A` 面朝上，有的卡片是 `B` 面朝上。

现给定 $N$ 的值，及 $N \times N$ 矩阵中每张卡片的状态，请你帮助小蓝挑选一张 `B` 面的卡，翻转成 `A` 面，使得翻转后的上、下、左、右四个方向相连的 `A` 面卡片最多，并将相连最多的卡片数量输出。

例如：$N=3$，$3 \times 3$ 的矩阵中的卡片状态如下：

| A | B | B |
|---|---|---|
| A | B | A |
| B | A | B |

选择第二行第二列的那张 `B` 面卡片，翻转为 `A` 面，可以使翻转后四个方向相连的 `A` 面卡片最多，为 $5$ 张。

| A | B | B |   | A | B | B |
|---|---|---|---|---|---|---|
| A | B | A | $\rightarrow$ | A | A | A |
| B | A | B |   | B | A | B |
## 输入格式

第一行输入一个正整数 $N$（$2 \leq N \leq 50$），表示矩阵的行数和列数。

第二行开始输入 $N$ 行，每行输入 $N$ 个字符（`A` 或者 `B`），表示矩阵中卡片状态，字符之间以一个空格隔开。
## 输出格式

输出一个整数，表示翻转后相连的 `A` 面卡片的最大数量。
## 样例

### 样例输入 #1
```
3
A B B
A B A
B A B
```
### 样例输出 #1
```
5
```


---

---
title: "[USTCPC 2025] 图上交互题 2 / Constructive Minimum Mex Path"
layout: "post"
diff: 普及/提高-
pid: P12041
tag: ['图论', '并查集', '2025', 'Special Judge', '连通块', '构造', '高校校赛']
---
# [USTCPC 2025] 图上交互题 2 / Constructive Minimum Mex Path
## 题目背景

USTCPC 设置 3s 时限为了使得 python 通过。洛谷改为 1s 时限。

2024 年 1 月 13 日 15:59:31，随着最后一发交互 J 题的提交出现了 Wrong Answer，小 G 的 EC-Final 比赛结束了，也意味着在 ICPC 生涯中第一次打铁。

克露丝卡尔酱想要帮助她的同学小 G！她打算批量生产交互题给小 G 做。如何批量生产交互题？只要在一个数据结构中有若干个未知量 $a_i$，每次询问给定向量 $x$，交互库会返回关于 $a_i$ 的函数 $f(x)$，这样就能批量生产交互题了！

~~为什么题目名里有 2 呢？~~
## 题目描述

给定一个 $n$ 个点，$m$ 条边的**无向图**。第 $i$ 条边 $(u_i,v_i)$ 有一个**未知边权** $a_i$。

对于任何一条**路径**，定义其**代价**如下：设路径为 $(p_0,p_1,...,p_k)$，其中要求 $(p_{i-1},p_i)$ 是无向图中的边，设其为第 $e_i$ 条边。那么路径的代价即为 $\mathop{\text{mex}}\limits_{i=1}^{k} a_{e_i}$。（该路径可以经过重复点和重复边，即 $p$ 和 $e$ 可以包含重复的数）

$\text{mex}$ 是一种定义域为一个非负整数的可重集合，函数值为非负整数的映射，定义为集合内最小未在集合内出现过的非负整数。

定义 $f(x,y)$ 为从 $x$ 到 $y$ 的所有路径中代价的**最小值**。特别地，当 $x=y$ 时，$f(x,y)=0$。

给定 $n,m$，再对于每条边 $(u_i,v_i)$ 给定 $f(u_i,v_i)$，你需要求出是否存在一组合法的 $a_i$，如果有解，你还需要构造一组解。
## 输入格式

第一行两个正整数 $n,m$ $(1\le n,m\le 10^5)$。

第 $2\sim m+1$ 行每行两个正整数 $u_i,v_i$ $(1\le u_i,v_i\le n)$ 和一个非负整数 $f(u_i,v_i)$ $(0\le f(u_i,v_i)<2^{31})$。

**请注意：本题并不保证图连通；可能会存在重边和自环。**
## 输出格式

如果不存在解，则仅输出 `No`。

否则，在第一行输出 `Yes`，在第二行输出 $m$ 个非负整数 $a_i$ 表示一组合法的解。

答案可能有很多组，此时输出任意一组解即可。你需要保证 输出的 $0\le a_i<2^{31}$。

你可以以任意的大小写形式输出 `Yes` 或 `No`。例如，`yEs`，`yes`，`Yes` 和 `YES` 都将被视为肯定的回复。
## 样例

### 样例输入 #1
```
4 4
1 2 0
2 3 0
3 1 0
3 4 1
```
### 样例输出 #1
```
Yes
0 1 2 0
```
### 样例输入 #2
```
1 1
1 1 114514
```
### 样例输出 #2
```
NO
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/z3pthk3a.png)

考虑 $f(1,2)$：

+ 考虑路径 $1\rightarrow 2$，路径的代价为 $\text{mex}\{0\}=1$。
+ 考虑路径 $1\rightarrow 2\rightarrow 3\rightarrow 1\rightarrow 2$，路径的代价为 $\text{mex}\{0,1,2,0\}=3$。
+ 考虑路径 $1\rightarrow 3\rightarrow 2$，路径的代价为 $\text{mex}\{1,2\}=0$。

此外还存在其他路径，但可以证明不存在代价比 $0$ 更小的路径，故 $f(1,2)=0$。


---

---
title: "[COCI 2020/2021 #2] Odasiljaci"
layout: "post"
diff: 普及/提高-
pid: P13427
tag: ['2020', '二分', '并查集', 'Special Judge', '生成树', '连通块', 'COCI（克罗地亚）']
---
# [COCI 2020/2021 #2] Odasiljaci
## 题目描述

Sadly, this is the last time Sean will play James Bond.

His mission is to network $n$ antennas that are scattered across a vast desert, which can be represented as a 2D plane. He will set the transmission radius of each antenna to be the same non negative real number $r$. The range of an antenna is defined as the set of all points whose distance to the antenna is at most $r$. If ranges of two antennas have a common point, those antennas can directly communicate. Also, if antennas $A$ and $B$ can communicate, as well as antennas $B$ and $C$, then antennas $A$ and $C$ are also able to communicate, through antenna $B$.

Sean wants to network the antennas, i.e. make possible for every two antennas to communicate. Since $M$ has limited his spending for this mission, and larger radii require more money, Sean will choose the smallest possible radius $r$. Help him solve this problem!
## 输入格式

The first line contains an integer $n$ ($1 \leq n \leq 1000$), the number of antennas.

Each of the following $n$ lines contains integers $x_i$ and $y_i$ ($0 \leq x_i, y_i \leq 10^9$), coordinates of the $i$-th antenna.
## 输出格式

Output the minimal radius.

Your answer will be considered correct if its absolute or relative error doesn't exceed $10^{-6}$.
## 样例

### 样例输入 #1
```
2
1 1
2 2
```
### 样例输出 #1
```
0.7071068
```
### 样例输入 #2
```
7
2 3
3 4
4 5
0 1
3 1
4 2
1 5
```
### 样例输出 #2
```
1.4142135
```
### 样例输入 #3
```
4
2020 20
20 2020
2020 2020
20 20
```
### 样例输出 #3
```
1000.0000000
```
## 提示

Clarification of the second example:

![](https://cdn.luogu.com.cn/upload/image_hosting/dxxoyzwk.png)


---

---
title: "[GCPC 2024] Alien Attack 2"
layout: "post"
diff: 普及/提高-
pid: P13716
tag: ['并查集', '2024', '连通块', 'ICPC']
---
# [GCPC 2024] Alien Attack 2
## 题目描述

Aliens are visiting Earth and, as usual, they plan to abduct humans for their experiments.
In the past, alien abductions have caused a lot of press coverage and wild speculation on Earth.
Luckily for them, most people do not believe these stories and think that aliens are not real.

:::align{center}
![](https://upload.wikimedia.org/wikipedia/commons/0/0d/Rocket_USA_Battery_Operated_Tin_UFO_Mars_Explorer_Close_Up.jpg)

A representative of the Galactic Committee for Person Captures.

By D J Shin on [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Rocket_USA_Battery_Operated_Tin_UFO_Mars_Explorer_Close_Up.jpg)

:::

In order to keep a low profile in the future, the Galactic Committee for Person Captures (GCPC) has established rules for abductions.
Besides a lot of boring paperwork, the aliens have to prepare the abduction carefully.
While they can make multiple trips (in fact, alien travel is so fast in practice that this is not a limitation at all),
they must be smart about it so that their secret is not revealed to humans. If aliens want to abduct a person,
they are required to abduct all of their friends at the same time, so that no one notices that their friend is missing when they want to hang out.
Of course, friendships on planet Earth are bidirectional, that is if Alice is a friend of Bob, then Bob is also a friend of Alice.

In preparation for the trip, the aliens have observed their targets and started taking note of all their friendships.
In total, they must abduct $n$ people, including their friends.
Now, they want to book a starship at their local dealership and wonder how much space they need to abduct all $n$ people.
A starship's storage space is measured in terms of the number of people that can be transported simultaneously.
What is the minimum storage space required to abduct all $n$ people?

## 输入格式

The input consists of:
- One line with two integers $n$ and $m$ ($1\leq n\leq 2 \cdot 10^5$, $0\leq m\leq 2 \cdot 10^5$), the number of people and the total number of friendships between them.
- $m$ lines, each with two integers $i$ and $j$ ($1\leq i < j\leq n$), denoting a friendship between persons $i$ and $j$.


The people are numbered from $1$ to $n$. It is guaranteed that no friendship is listed multiple times.

## 输出格式

Output the minimum storage space needed to abduct all people.
## 样例

### 样例输入 #1
```
5 3
1 2
2 3
4 5
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 0
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
8 8
1 2
2 3
3 4
1 4
1 5
2 6
3 7
4 8
```
### 样例输出 #3
```
8
```


---

---
title: "[USACO05MAR] Out of Hay S"
layout: "post"
diff: 普及/提高-
pid: P1547
tag: ['图论', '贪心', '2005', 'USACO', '并查集', '生成树', '连通块']
---
# [USACO05MAR] Out of Hay S
## 题目描述

Bessie 计划调查 $N$（$2 \leq N \leq 2\,000$）个农场的干草情况，它从 $1$ 号农场出发。农场之间总共有 $M$（$1 \leq M \leq 10^4$）条双向道路，所有道路的总长度不超过 $10^9$。有些农场之间存在着多条道路，所有的农场之间都是连通的。

Bessie 希望计算出该图中最小生成树中的最长边的长度。

## 输入格式

第一行两个整数 $N,M$。

接下来 $M$ 行，每行三个用空格隔开的整数 $A_i,B_i,L_i$，表示 $A_i,B_i$ 之间有一条道路，长度为 $L_i$。
## 输出格式

一个整数，表示最小生成树中的最长边的长度。

## 样例

### 样例输入 #1
```
3 3
1 2 23
2 3 1000
1 3 43
```
### 样例输出 #1
```
43
```


---

---
title: "[POI 2005] SKA-Piggy Banks"
layout: "post"
diff: 普及/提高-
pid: P3420
tag: ['2005', '并查集', 'POI（波兰）', '连通块']
---
# [POI 2005] SKA-Piggy Banks
## 题目描述

Byteazar the Dragon 拥有 $N$ 个小猪存钱罐。每一个存钱罐能够用相应的钥匙打开或者被砸开。Byteazar 已经将钥匙放入到一些存钱罐中。现在已知每个钥匙所在的存钱罐，Byteazar 想要买一辆小汽车，而且需要打开所有的存钱罐。然而，他想要破坏尽量少的存钱罐，帮助 Byteazar 去决策最少要破坏多少存钱罐。
## 输入格式


第一行包括一个整数 $N$ ($1\le N\le 1000000$)，表示 Byteazar the Dragon 拥有的存钱罐的数量。

存钱罐（包括它们对应的钥匙）从 $1$ 到 $N$ 编号。

接下来有 $N$ 行：第 $i+1$ 行包括一个整数 $x$，表示第 $i$ 个存钱罐对应的钥匙放置在了第 $x$ 个存钱罐中。

## 输出格式

仅一行：包括一个整数，表示能打开所有存钱罐的情况下，需要破坏的存钱罐的最少数量。

## 样例

### 样例输入 #1
```
4
2
1
2
4
```
### 样例输出 #1
```
2
```


---

