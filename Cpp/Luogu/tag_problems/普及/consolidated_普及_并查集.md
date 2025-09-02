---
title: "修复公路"
layout: "post"
diff: 普及/提高-
pid: P1111
tag: ['二分', '并查集', '排序']
---
# 修复公路
## 题目背景

A 地区在地震过后，连接所有村庄的公路都造成了损坏而无法通车。政府派人修复这些公路。
## 题目描述

给出 A 地区的村庄数 $N$，和公路数 $M$，公路是双向的。并告诉你每条公路的连着哪两个村庄，并告诉你什么时候能修完这条公路。问最早什么时候任意两个村庄能够通车，即最早什么时候任意两条村庄都存在至少一条修复完成的道路（可以由多条公路连成一条道路）。
## 输入格式

第 $1$ 行两个正整数 $N,M$。

下面 $M$ 行，每行 $3$ 个正整数 $x,y,t$，告诉你这条公路连着 $x,y$ 两个村庄，在时间 $t$ 时能修复完成这条公路。
## 输出格式

如果全部公路修复完毕仍然存在两个村庄无法通车，则输出 $-1$，否则输出最早什么时候任意两个村庄能够通车。
## 样例

### 样例输入 #1
```
4 4
1 2 6
1 3 4
1 4 5
4 2 3
```
### 样例输出 #1
```
5
```
## 提示

$1\leq x, y\leq N \le 10 ^ 3$，$1\leq M, t \le 10 ^ 5$。


---

---
title: "[PA 2015] 人赢 / Mistrzostwa"
layout: "post"
diff: 普及/提高-
pid: P11811
tag: ['图论', '2015', '并查集', 'Special Judge', 'PA（波兰）']
---
# [PA 2015] 人赢 / Mistrzostwa
## 题目背景

译自 [PA 2015](https://sio2.mimuw.edu.pl/c/pa-2015-1/p/) R2.
## 题目描述

给定一张 $n$ 个点 $m$ 条边的**简单**（无重边自环的）无向图 $G=(V,E)$。其中节点编号 $1\sim n$。

给定正整数 $d$。选出一个最大的点集 $S\subseteq V$，满足：

- $\forall u\in S$，$\displaystyle \sum_{v\in S} [(u,v)\in E]\ge d$。换句话说，$u$ 向 $S$ 内点至少连了 $d$ 条边。
- $S$ 的导出子图（induced subgraph）是连通的。

你需要构造一个 $S$ 使得 $|S|$ 取到最大值，或者报告无解。

点集 $V'\subseteq V$ 的导出子图定义为 $G'=(V',E')$，其中 $E'=\{(u,v)\in E: u\in V'\land v\in V'\}$。

## 输入格式

第一行，三个正整数 $n,m,d$。

接下来 $m$ 行，每行两个正整数 $u,v$，表示 $(u,v)\in E$。
## 输出格式

如果符合条件的 $S$ 不存在，输出一行一个 $\texttt{NIE}$。

否则，第一行输出 $|S|$，第二行**升序**输出 $S$ 中节点的编号。
## 样例

### 样例输入 #1
```
4 4 2
1 2
2 3
3 4
4 2
```
### 样例输出 #1
```
3
2 3 4
```
### 样例输入 #2
```
3 2 2
1 2
2 3
```
### 样例输出 #2
```
NIE
```
## 提示

- $1\le d\lt n\le 2\times 10^5$；
- $1\le m\le 2\times 10^5$。
- 给定的图无重边自环。



---

---
title: "口袋的天空"
layout: "post"
diff: 普及/提高-
pid: P1195
tag: ['图论', '并查集', '生成树']
---
# 口袋的天空
## 题目背景

小杉坐在教室里，透过口袋一样的窗户看口袋一样的天空。

有很多云飘在那里，看起来很漂亮，小杉想摘下那样美的几朵云，做成棉花糖。

## 题目描述

给你云朵的个数 $N$，再给你 $M$ 个关系，表示哪些云朵可以连在一起。

现在小杉要把所有云朵连成 $K$ 个棉花糖，一个棉花糖最少要用掉一朵云，小杉想知道他怎么连，花费的代价最小。

## 输入格式

第一行有三个数 $N,M,K$。

接下来 $M$ 行每行三个数 $X,Y,L$，表示 $X$ 云和 $Y$ 云可以通过 $L$ 的代价连在一起。



## 输出格式

对每组数据输出一行，仅有一个整数，表示最小的代价。

如果怎么连都连不出 $K$ 个棉花糖，请输出 `No Answer`。

## 样例

### 样例输入 #1
```
3 1 2
1 2 1

```
### 样例输出 #1
```
1
```
## 提示

对于 $30\%$ 的数据，$1 \le N \le 100$，$1\le M \le 10^3$；

对于 $100\%$ 的数据，$1 \le N \le 10^3$，$1 \le M \le 10^4$，$1 \le K \le 10$，$1 \le X,Y \le N$，$0 \le L<10^4$。



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
title: "[蓝桥杯 2024 省 B 第二场] 传送阵"
layout: "post"
diff: 普及/提高-
pid: P12123
tag: ['并查集', '2024', '蓝桥杯省赛']
---
# [蓝桥杯 2024 省 B 第二场] 传送阵
## 题目描述

小蓝在环球旅行时来到了一座古代遗迹，里面并排放置了 $n$ 个传送阵，进入第 $i$ 个传送阵会被传送到第 $a_i$ 个传送阵前，并且可以随时选择退出或者继续进入当前传送阵。

小蓝为了探寻传送阵中的宝物，需要选择一个传送阵进入，然后连续进入之后的传送阵。小蓝希望尽可能多地进入传送门以便搜索宝物，同时他可以使用一次魔法，从某个传送阵 $j$ 走到相邻的（第 $j - 1$ 或第 $j + 1$ 个）传送阵，请问小蓝最多能到达多少个不同的传送阵？一个传送阵可多次进入，但在计算答案时只算一个。
## 输入格式

输入的第一行包含一个正整数 $n$。

第二行包含 $n$ 个正整数 $a_1, a_2, \dots , a_n$，相邻整数之间使用一个空格分隔。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
5
2 1 5 4 3
```
### 样例输出 #1
```
4
```
## 提示

### 样例说明

小蓝的路径可以是：$1 \to 2 \to 3 \to 5$。其中 $2 \to 3$ 使用魔法。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n \leq 1000$；
- 对于所有评测用例，$1 \leq n \leq 10^6$，且 $a$ 是 $1$ 至 $n$ 的一个排列。


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
title: "营救"
layout: "post"
diff: 普及/提高-
pid: P1396
tag: ['图论', '二分', '并查集', '福建省历届夏令营', '最短路', '生成树']
---
# 营救
## 题目背景

“咚咚咚……”“查水表！”原来是查水表来了，现在哪里找这么热心上门的查表员啊！小明感动得热泪盈眶，开起了门……
## 题目描述

妈妈下班回家，街坊邻居说小明被一群陌生人强行押上了警车！妈妈丰富的经验告诉她小明被带到了 $t$ 区，而自己在 $s$ 区。

该市有 $m$ 条大道连接 $n$ 个区，一条大道将两个区相连接，每个大道有一个拥挤度。小明的妈妈虽然很着急，但是不愿意拥挤的人潮冲乱了她优雅的步伐。所以请你帮她规划一条从 $s$ 至 $t$ 的路线，使得经过道路的拥挤度最大值最小。
## 输入格式

第一行有四个用空格隔开的 $n$，$m$，$s$，$t$，其含义见【题目描述】。

接下来 $m$ 行，每行三个整数 $u, v, w$，表示有一条大道连接区 $u$ 和区 $v$，且拥挤度为 $w$。

**两个区之间可能存在多条大道**。
## 输出格式

输出一行一个整数，代表最大的拥挤度。
## 样例

### 样例输入 #1
```
3 3 1 3
1 2 2
2 3 1
1 3 3
```
### 样例输出 #1
```
2

```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n\leq 10$。
- 对于 $60\%$ 的数据，保证 $n\leq 100$。
- 对于 $100\%$ 的数据，保证 $1 \leq n\leq 10^4$，$1 \leq m \leq 2 \times 10^4$，$w \leq 10^4$，$1 \leq s, t \leq n$。且从 $s$ 出发一定能到达 $t$ 区。

--- 

#### 样例输入输出 1 解释

小明的妈妈要从 $1$ 号点去 $3$ 号点，最优路线为 $1$->$2$->$3$。


---

---
title: "搭配购买"
layout: "post"
diff: 普及/提高-
pid: P1455
tag: ['并查集', '背包 DP', '强连通分量']
---
# 搭配购买
## 题目描述

明天就是母亲节了，电脑组的小朋友们在忙碌的课业之余挖空心思想着该送什么礼物来表达自己的心意呢？听说在某个网站上有卖云朵的，小朋友们决定一同前往去看看这种神奇的商品，这个店里有 $n$ 朵云，云朵已经被老板编号为 $1,2,3,...,n$，并且每朵云都有一个价值，但是商店的老板是个很奇怪的人，他会告诉你一些云朵要搭配起来买才卖，也就是说买一朵云则与这朵云有搭配的云都要买，电脑组的你觉得这礼物实在是太新奇了，但是你的钱是有限的，所以你肯定是想用现有的钱买到尽量多价值的云。
## 输入格式

第一行输入三个整数，$n,m,w$，表示有 $n$ 朵云，$m$ 个搭配和你现有的钱的数目。

第二行至 $n+1$ 行，每行有两个整数， $c_i,d_i$，表示第 $i$ 朵云的价钱和价值。

第 $n+2$ 至 $n+1+m$ 行 ，每行有两个整数 $u_i,v_i$。表示买第 $u_i$ 朵云就必须买第 $v_i$ 朵云,同理，如果买第 $v_i$ 朵就必须买第 $u_i$ 朵。
## 输出格式

一行，表示可以获得的最大价值。
## 样例

### 样例输入 #1
```
5 3 10
3 10
3 10
3 10
5 100
10 1
1 3
3 2
4 2

```
### 样例输出 #1
```
1

```
## 提示

- 对于 $30\%$ 的数据，满足 $1 \le n \le 100$；
- 对于 $50\%$ 的数据，满足 $1 \le n, w \le 10^3$，$1 \le m \le 100$；
- 对于 $100\%$ 的数据，满足 $1 \le n, w \le 10^4$，$0 \le m \le 5 \times 10^3$。


---

---
title: "村村通"
layout: "post"
diff: 普及/提高-
pid: P1536
tag: ['并查集', '生成树']
---
# 村村通
## 题目描述

某市调查城镇交通状况，得到现有城镇道路统计表。表中列出了每条道路直接连通的城镇。市政府 "村村通工程" 的目标是使全市任何两个城镇间都可以实现交通（但不一定有直接的道路相连，只要相互之间可达即可）。请你计算出最少还需要建设多少条道路？
## 输入格式

输入包含若干组测试数据，每组测试数据的第一行给出两个用空格隔开的正整数，分别是城镇数目 $n$ 和道路数目 $m$ ；随后的 $m$ 行对应 $m$ 条道路，每行给出一对用空格隔开的正整数，分别是该条道路直接相连的两个城镇的编号。简单起见，城镇从 $1$ 到 $n$ 编号。

注意：两个城市间可以有多条道路相通。

**在输入数据的最后，为一行一个整数 $0$，代表测试数据的结尾。**
## 输出格式

对于每组数据，对应一行一个整数。表示最少还需要建设的道路数目。

## 样例

### 样例输入 #1
```
4 2
1 3
4 3
3 3
1 2
1 3
2 3
5 2
1 2
3 5
999 0
0

```
### 样例输出 #1
```
1
0
2
998

```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \le n < 1000$ 。


---

---
title: "[USACO3.1] 最短网络 Agri-Net"
layout: "post"
diff: 普及/提高-
pid: P1546
tag: ['图论', '贪心', 'USACO', '并查集', '生成树']
---
# [USACO3.1] 最短网络 Agri-Net
## 题目背景

Farmer John 被选为他们镇的镇长！他其中一个竞选承诺就是在镇上建立起互联网，并连接到所有的农场。当然，他需要你的帮助。

## 题目描述

FJ 已经给他的农场安排了一条高速的网络线路，他想把这条线路共享给其他农场。为了用最小的消费，他想铺设最短的光纤去连接所有的农场。

你将得到一份各农场之间连接费用的列表，你必须找出能连接所有农场并所用光纤最短的方案。每两个农场间的距离不会超过 $10^5$。
## 输入格式

第一行农场的个数 $N$（$3 \leq N \leq 100$）。

接下来是一个 $N \times N$ 的矩阵，表示每个农场之间的距离。理论上，他们是 $N$ 行，每行由 $N$ 个用空格分隔的数组成，实际上，由于每行 $80$ 个字符的限制，因此，某些行会紧接着另一些行。当然，对角线将会是 $0$，因为不会有线路从第 $i$ 个农场到它本身。
## 输出格式

只有一个输出，其中包含连接到每个农场的光纤的最小长度。

## 样例

### 样例输入 #1
```
4
0 4 9 21
4 0 8 17
9 8 0 16
21 17 16 0
```
### 样例输出 #1
```
28
```
## 提示

题目翻译来自NOCOW。

USACO Training Section 3.1



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
title: "亲戚"
layout: "post"
diff: 普及/提高-
pid: P1551
tag: ['并查集']
---
# 亲戚
## 题目背景

若某个家族人员过于庞大，要判断两个是否是亲戚，确实还很不容易，现在给出某个亲戚关系图，求任意给出的两个人是否具有亲戚关系。

## 题目描述

规定：$x$ 和 $y$ 是亲戚，$y$ 和 $z$ 是亲戚，那么 $x$ 和 $z$ 也是亲戚。如果 $x$，$y$ 是亲戚，那么 $x$ 的亲戚都是 $y$ 的亲戚，$y$ 的亲戚也都是 $x$ 的亲戚。
## 输入格式

第一行：三个整数 $n,m,p$，（$n,m,p \le 5000$），分别表示有 $n$ 个人，$m$ 个亲戚关系，询问 $p$ 对亲戚关系。

以下 $m$ 行：每行两个数 $M_i$，$M_j$，$1 \le M_i,~M_j\le n$，表示 $M_i$ 和 $M_j$ 具有亲戚关系。

接下来 $p$ 行：每行两个数 $P_i,P_j$，询问 $P_i$ 和 $P_j$ 是否具有亲戚关系。
## 输出格式

$p$ 行，每行一个 `Yes` 或 `No`。表示第 $i$ 个询问的答案为“具有”或“不具有”亲戚关系。
## 样例

### 样例输入 #1
```
6 5 3
1 2
1 5
3 4
5 2
1 3
1 4
2 3
5 6
```
### 样例输出 #1
```
Yes
Yes
No
```


---

---
title: "集合"
layout: "post"
diff: 普及/提高-
pid: P1621
tag: ['搜索', '数学', '并查集', '枚举', '素数判断,质数,筛法']
---
# 集合
## 题目描述

Caima 给你了所有 $[a,b]$ 范围内的整数。一开始每个整数都属于各自的集合。每次你需要选择两个属于不同集合的整数，如果这两个整数拥有大于等于 $p$ 的公共质因数，那么把它们所在的集合合并。

重复如上操作，直到没有可以合并的集合为止。

现在 Caima 想知道，最后有多少个集合。
## 输入格式

一行，共三个整数 $a,b,p$，用空格隔开。
## 输出格式

一个数，表示最终集合的个数。

## 样例

### 样例输入 #1
```
10 20 3
```
### 样例输出 #1
```
7
```
## 提示

#### 样例 1 解释

对于样例给定的数据，最后有 $\{10,20,12,15,18\},\{13\},\{14\},\{16\},\{17\},\{19\},\{11\}$ 共 $7$ 个集合，所以输出应该为 $7$。

#### 数据规模与约定
- 对于 $80\%$ 的数据，$1 \leq a \leq b \leq 10^3$。
- 对于 $100%$ 的数据，$1 \leq a \leq b \leq 10^5,2 \leq p \leq b$。




---

---
title: "炸铁路"
layout: "post"
diff: 普及/提高-
pid: P1656
tag: ['模拟', '搜索', '图论', '并查集', '洛谷原创', '最短路', 'Tarjan']
---
# 炸铁路
## 题目描述

A 国派出将军 uim，对 B 国进行战略性措施，以解救涂炭的生灵。

B 国有 $n$ 个城市，这些城市以铁路相连。任意两个城市都可以通过铁路直接或者间接到达。

uim 发现有些铁路被毁坏之后，某两个城市无法互相通过铁路到达。这样的铁路就被称为 key road。

uim 为了尽快使该国的物流系统瘫痪，希望炸毁铁路，以达到存在某两个城市无法互相通过铁路到达的效果。

然而，只有一发炮弹（A 国国会不给钱了）。所以，他能轰炸哪一条铁路呢？

## 输入格式

第一行 $n,m\ (1 \leq n\leq 150$，$1 \leq m \leq 5000)$，分别表示有 $n$ 个城市，总共 $m$ 条铁路。

以下 $m$ 行，每行两个整数 $a, b$，表示城市 $a$ 和城市 $b$ 之间有铁路直接连接。

## 输出格式

输出有若干行。

每行包含两个数字 $a,b$，其中 $a<b$，表示 $\lang a,b\rang$ 是 key road。

请注意：输出时，所有的数对 $\lang a,b\rang$ 必须按照 $a$ 从小到大排序输出；如果$a$ 相同，则根据 $b$ 从小到大排序。

## 样例

### 样例输入 #1
```
6 6
1 2
2 3
2 4
3 5
4 5
5 6
```
### 样例输出 #1
```
1 2
5 6
```


---

---
title: "过家家"
layout: "post"
diff: 普及/提高-
pid: P1682
tag: ['并查集', '广度优先搜索 BFS']
---
# 过家家
## 题目描述

有 $2n$ 个小学生来玩过家家游戏，其中有 $n$ 个男生，编号为 $1$ 到 $n$，另外 $n$ 个女生，编号也是 $1$ 到 $n$。每一个女生可以选择一个和她不吵嘴的男生来玩，除此之外，如果编号为 $X$ 的女生的朋友（也是女生，且编号为 $Y$）不和编号为 $Z$ 的男生吵嘴，那么 $X$ 也可以选择 $Z$。此外，朋友关系是可以传递的，比如 $a$ 和 $b$ 是朋友，$b$ 和 $c$ 是朋友，那么我们可以认为 $a$ 和 $c$ 也是朋友。注意，一个男生可以被多个女生选择为玩伴。

当每一位女生都选择了玩伴，那么他们会开始新一轮游戏。在每一轮后，每个女生都会开始去找一个新的男生做玩伴（以前没选过）。而且每一个女生最多能强制 $k$ 个男生接受，无论他们以前是否吵嘴。

现在你的任务就是确定这 $2n$ 个小学生最多能玩几轮游戏。

## 输入格式

第一行有四个整数 $n,m,k,f$（$3 \le n \le 250$，$0 < m < n^{2}$，$0 \le f < n$）。

$n$ 表示有 $2n$ 个小学生，其中 $n$ 个男生 $n$ 个女生。

接下来 $m$ 行，每行包含两个数字 $a,b$ 表示编号为 $a$ 的女生和编号为 $b$ 的男生从没吵嘴过。

再接下来 $f$ 行，每行包含两个数字 $c,d$ 表示编号为 $c$ 的女生和编号为 $d$ 的女生是朋友。

## 输出格式

对于每组数据，输出一个整数，表示 $2n$ 个小学生最多能玩几轮。

## 样例

### 样例输入 #1
```
4 5 1 2
1 1
2 3
3 2
4 2
4 4
1 4
2 3

```
### 样例输出 #1
```
3

```


---

---
title: "Color the Axis"
layout: "post"
diff: 普及/提高-
pid: P1840
tag: ['并查集', 'NOI 导刊']
---
# Color the Axis
## 题目描述

在一条数轴上有 $n$ 个点，分别是 $1,2,\ldots,n$。一开始所有的点都被染成黑色。接着我们进行 $m$ 次操作，第 $i$ 次操作将 $[l_i,r_i]$ 这些点染成白色。请输出每个操作执行后剩余黑色点的个数。
## 输入格式

输入一行为 $n$ 和 $m$。下面 $m$ 行每行两个数 $l_i$，$r_i$。
## 输出格式

输出 $m$ 行，为每次操作后剩余黑色点的个数。
## 样例

### 样例输入 #1
```
10 3   
3 3   
5 7   
2 8     
```
### 样例输出 #1
```
9     
6     
3
```
## 提示

- 对于 $30\%$ 的数据，有 $1\le n\le2000$，$1\le m\le2000$；
- 对于 $100\%$ 的数据，有 $1\le l_i\le r_i\le n\le 2\times 10^5$，$1\le m\le 2\times10^5$。


---

---
title: "无线通讯网"
layout: "post"
diff: 普及/提高-
pid: P1991
tag: ['图论', '并查集', '生成树']
---
# 无线通讯网
## 题目描述

国防部计划用无线网络连接若干个边防哨所。2 种不同的通讯技术用来搭建无线网络；

每个边防哨所都要配备无线电收发器；有一些哨所还可以增配卫星电话。

任意两个配备了一条卫星电话线路的哨所（两边都有卫星电话）均可以通话，无论他们相距多远。而只通过无线电收发器通话的哨所之间的距离不能超过 $D$，这是受收发器的功率限制。收发器的功率越高，通话距离 $D$ 会更远，但同时价格也会更贵。

收发器需要统一购买和安装，所以全部哨所只能选择安装一种型号的收发器。换句话说，每一对哨所之间的通话距离都是同一个 $D$。你的任务是确定收发器必须的最小通话距离 $D$，使得每一对哨所之间至少有一条通话路径（直接的或者间接的）。

## 输入格式

第一行，$2$ 个整数 $S$ 和 $P$，$S$ 表示可安装的卫星电话的哨所数，$P$ 表示边防哨所的数量。

接下里 $P$ 行，每行两个整数 $x，y$ 描述一个哨所的平面坐标 $(x, y)$，以 km 为单位。

## 输出格式

第一行，$1$ 个实数 $D$，表示无线电收发器的最小传输距离，精确到小数点后两位。

## 样例

### 样例输入 #1
```
2 4
0 100
0 300
0 600
150 750

```
### 样例输出 #1
```
212.13

```
## 提示

### 数据范围及约定

- 对于 $20\%$ 的数据：$P = 2，S = 1$；
- 对于另外 $20\%$ 的数据：$P = 4，S = 2$；
- 对于 $100\%$ 的数据保证：$1 ≤ S ≤ 100$，$S < P ≤ 500$，$0 ≤ x,y ≤ 10000$。



---

---
title: "朋友"
layout: "post"
diff: 普及/提高-
pid: P2078
tag: ['并查集', '递归']
---
# 朋友
## 题目背景

小明在 A 公司工作，小红在 B 公司工作。
## 题目描述

这两个公司的员工有一个特点：一个公司的员工都是同性。

A 公司有 $N$ 名员工，其中有 $P$ 对朋友关系。B 公司有 $M$ 名员工，其中有 $Q$ 对朋友关系。朋友的朋友一定还是朋友。

每对朋友关系用两个整数 $(X_i,Y_i)$ 组成，表示朋友的编号分别为 $X_i,Y_i$。男人的编号是正数，女人的编号是负数。小明的编号是 $1$，小红的编号是 $-1$。

大家都知道，小明和小红是朋友，那么，请你写一个程序求出两公司之间，通过小明和小红认识的人最多一共能配成多少对情侣（包括他们自己）。
## 输入格式

输入的第一行，包含 $4$ 个空格隔开的正整数 $N,M,P,Q$。

之后 $P$ 行，每行两个正整数 $X_i,Y_i$。

之后 $Q$ 行，每行两个负整数 $X_i,Y_i$。
## 输出格式

输出一行一个正整数，表示通过小明和小红认识的人最多一共能配成多少对情侣（包括他们自己）。
## 样例

### 样例输入 #1
```
4 3 4 2
1 1
1 2
2 3
1 3
-1 -2
-3 -3

```
### 样例输出 #1
```
2
```
## 提示

对于 $30 \%$ 的数据，$N,M \le 100$，$P,Q \le 200$；

对于 $80 \%$ 的数据，$N,M \le 4 \times 10^3$，$P,Q \le 10^4$；

对于 $100 \%$ 的数据，$N,M \le 10^4$，$P,Q \le 2 \times 10^4$。


---

---
title: "一中校运会之百米跑"
layout: "post"
diff: 普及/提高-
pid: P2256
tag: ['字符串', '并查集']
---
# 一中校运会之百米跑
## 题目背景

在一大堆秀恩爱的 \*\* 之中，来不及秀恩爱的苏大学神踏着坚定（？）的步伐走向了 $100$ 米跑的起点。这时苏大学神发现，百米赛跑的参赛同学实在是太多了，连体育老师也忙不过来。这时体育老师发现了身为体育委员的苏大学神，便来找他帮忙。

可是苏大学神需要热身，不然跑到一半就会抽（筋）、于是他就找到了你。。。如果你帮助体育老师解决了问题，老师就会给你 $5$ 个积分。
## 题目描述

假设一共有 $N$（$2\leq N\leq 2\times 10^4$）个参赛选手。（尼玛全校学生都没这么多吧）

老师会告诉你这 $N$ 个选手的名字。

接着会告诉你 $M$（$1\leq M\leq 10^6$）句话，即告诉你学生 A 与学生 B 在同一个组里。

如果学生 A 与学生 B 在同一组里，学生 B 与学生 C 也在同一组里，就说明学生 A 与学生 C 在同一组。

然后老师会问你 $K$（$1\leq K\leq 10^6$）句话，即学生 X 和学生 Y 是否在同一组里。

若是则输出 `Yes.`，否则输出 `No.`。
## 输入格式

第一行输入 $N$ 和 $M$。

接下来 $N$ 行输入每一个同学的名字。

再往下 $M$ 行每行输入两个名字，且保证这两个名字都在上面的 $N$ 行中出现过，表示这两个参赛选手在同一个组里。

再来输入 $K$。

接下来输入 $K$ 个体育老师的询问。
## 输出格式

对于每一个体育老师的询问，输出 `Yes.` 或 `No.`。
## 样例

### 样例输入 #1
```
10 6
Jack
Mike
ASDA
Michel
brabrabra
HeHe
HeHE
papapa
HeY
Obama
Jack Obama
HeHe HeHE
brabrabra HeHe
Obama ASDA
papapa Obama
Obama HeHE
3
Mike Obama
HeHE Jack
papapa brabrabra

```
### 样例输出 #1
```
No.
Yes.
Yes.

```


---

---
title: "[SCOI2005] 繁忙的都市"
layout: "post"
diff: 普及/提高-
pid: P2330
tag: ['图论', '2005', '四川', '并查集', '各省省选', '生成树']
---
# [SCOI2005] 繁忙的都市
## 题目描述

城市 C 是一个非常繁忙的大都市，城市中的道路十分的拥挤，于是市长决定对其中的道路进行改造。城市 C 的道路是这样分布的：城市中有 $n$ 个交叉路口，有些交叉路口之间有道路相连，两个交叉路口之间最多有一条道路相连接。这些道路是双向的，且把所有的交叉路口直接或间接的连接起来了。每条道路都有一个分值，分值越小表示这个道路越繁忙，越需要进行改造。但是市政府的资金有限，市长希望进行改造的道路越少越好，于是他提出下面的要求：

1. 改造的那些道路能够把所有的交叉路口直接或间接的连通起来。
1. 在满足要求 1 的情况下，改造的道路尽量少。
1. 在满足要求 1、2 的情况下，改造的那些道路中分值最大的道路分值尽量小。

任务：作为市规划局的你，应当作出最佳的决策，选择哪些道路应当被修建。
## 输入格式

第一行有两个整数 $n,m$ 表示城市有 $n$ 个交叉路口，$m$ 条道路。

接下来 $m$ 行是对每条道路的描述，$u, v, c$ 表示交叉路口 $u$ 和 $v$ 之间有道路相连，分值为 $c$。
## 输出格式

两个整数 $s, \mathit{max}$，表示你选出了几条道路，分值最大的那条道路的分值是多少。
## 样例

### 样例输入 #1
```
4 5
1 2 3
1 4 5
2 4 7
2 3 6
3 4 8

```
### 样例输出 #1
```
3 6
```
## 提示

### 数据范围及约定

对于全部数据，满足 $1\le n\le 300$，$1\le c\le 10^4$，$1 \le m \le 8000$。


---

---
title: "[NOIP 2015 提高组] 信息传递"
layout: "post"
diff: 普及/提高-
pid: P2661
tag: ['图论', '2015', '并查集', 'NOIP 提高组']
---
# [NOIP 2015 提高组] 信息传递
## 题目背景

NOIP2015 Day1T2
## 题目描述

有 $n$ 个同学（编号为 $1$ 到 $n$）正在玩一个信息传递的游戏。在游戏里每人都有一个固定的信息传递对象，其中，编号为 $i$ 的同学的信息传递对象是编号为 $T_i$ 的同学。

游戏开始时，每人都只知道自己的生日。之后每一轮中，所有人会同时将自己当前所知的生日信息告诉各自的信息传递对象（注意：可能有人可以从若干人那里获取信息，但是每人只会把信息告诉一个人，即自己的信息传递对象）。当有人从别人口中得知自己的生日时，游戏结束。请问该游戏一共可以进行几轮？
## 输入格式

输入共 $2$ 行。

第一行包含 $1$ 个正整数 $n$，表示 $n$ 个人。

第二行包含 $n$ 个用空格隔开的正整数 $T_1,T_2,\cdots,T_n$，其中第 $i$ 个整数 $T_i$ 表示编号为 $i$ 的同学的信息传递对象是编号为 $T_i$ 的同学，$T_i\leq n$ 且 $T_i\neq i$。
## 输出格式

共一行一个整数，表示游戏一共可以进行多少轮。
## 样例

### 样例输入 #1
```
5
2 4 2 3 1
```
### 样例输出 #1
```
3
```
## 提示

**样例 1 解释：**

![](https://cdn.luogu.com.cn/upload/image_hosting/3ca5zl3c.png)

游戏的流程如图所示。当进行完第 $3$ 轮游戏后，$4$ 号玩家会听到 $2$ 号玩家告诉他自己的生日，所以答案为 $3$。当然，第 $3$ 轮游戏后，$2$ 号玩家、 $3$ 号玩家都能从自己的消息来源得知自己的生日，同样符合游戏结束的条件。

- 对于 $30\%$ 的数据，$n\le 200$；
- 对于 $60\%$ 的数据，$n\le 2500$；
- 对于 $100\%$ 的数据，$n\le 2\times 10^5$。



---

---
title: "家谱"
layout: "post"
diff: 普及/提高-
pid: P2814
tag: ['字符串', '搜索', '图论', '线性数据结构', '并查集']
---
# 家谱
## 题目背景

现代的人对于本家族血统越来越感兴趣。

## 题目描述

给出充足的父子关系，请你编写程序找到某个人的最早的祖先。

## 输入格式

输入由多行组成，首先是一系列有关父子关系的描述，其中每一组父子关系中父亲只有一行，儿子可能有若干行，用 `#name` 的形式描写一组父子关系中的父亲的名字，用 `+name` 的形式描写一组父子关系中的儿子的名字；接下来用 `?name` 的形式表示要求该人的最早的祖先；最后用单独的一个 `$` 表示文件结束。
## 输出格式

按照输入文件的要求顺序，求出每一个要找祖先的人的祖先，格式为：本人的名字 $+$ 一个空格 $+$ 祖先的名字 $+$ 回车。
## 样例

### 样例输入 #1
```
#George
+Rodney
#Arthur
+Gareth
+Walter
#Gareth
+Edward
?Edward
?Walter
?Rodney
?Arthur
$
```
### 样例输出 #1
```
Edward Arthur
Walter Arthur
Rodney George
Arthur Arthur
```
## 提示

规定每个人的名字都有且只有 $6$ 个字符，而且首字母大写，且没有任意两个人的名字相同。最多可能有 $10^3$ 组父子关系，总人数最多可能达到 $5 \times 10^4$ 人，家谱中的记载不超过 $30$ 代。


---

---
title: "局域网"
layout: "post"
diff: 普及/提高-
pid: P2820
tag: ['图论', '并查集', '生成树']
---
# 局域网
## 题目背景

某个局域网内有 $n$ 台计算机，由于搭建局域网时工作人员的疏忽，现在局域网内的连接形成了回路，我们知道如果局域网形成回路那么数据将不停的在回路内传输，造成网络卡的现象。因为连接计算机的网线本身不同，所以有一些连线不是很畅通，我们用 $f(i,j)$ 表示 $i,j$ 之间连接的畅通程度，$f(i,j)$ 值越小表示 $i,j$ 之间连接越通畅，$f(i,j)$ 为 $0$ 表示 $i,j$ 之间无网线连接。
## 题目描述

现在需要解决回路问题，我们将除去一些连线，使得网络中没有回路，**不改变原图节点的连通性**，并且被除去网线的 $\sum f(i,j)$ 最大，请求出这个最大值。
## 输入格式

第一行两个正整数 $n,k$。

接下来的 $k$ 行每行三个正整数 $i,j,m$ 表示 $i,j$ 两台计算机之间有网线联通，通畅程度为 $m$。
## 输出格式

一个正整数， $\sum f(i,j)$ 的最大值。
## 样例

### 样例输入 #1
```
5 5
1 2 8
1 3 1
1 5 3
2 4 5
3 4 2

```
### 样例输出 #1
```
8
```
## 提示

对于全部数据，保证 $1\le n \le 100$，$1\le f(i,j)\le 1000$。



---

---
title: "[USACO16OPEN] Closing the Farm S"
layout: "post"
diff: 普及/提高-
pid: P3144
tag: ['贪心', '2016', 'USACO', '并查集']
---
# [USACO16OPEN] Closing the Farm S
## 题目背景

*本题和 [金组同名题目](/problem/P6121) 在题意上一致，唯一的不同是数据范围。*
## 题目描述

FJ 和他的奶牛们正在计划离开小镇做一次长的旅行，同时 FJ 想临时地关掉他的农场以节省一些金钱。

这个农场一共有被用 $M$ 条双向道路连接的 $N$ 个谷仓（$1 \leq N,M \leq 3000$）。为了关闭整个农场，FJ 计划每一次关闭掉一个谷仓。当一个谷仓被关闭了，所有的连接到这个谷仓的道路都会被关闭，而且再也不能够被使用。

FJ 现在正感兴趣于知道在每一个时间（这里的“时间”指在每一次关闭谷仓之前的时间）时他的农场是否是“全连通的”——也就是说从任意的一个开着的谷仓开始，能够到达另外的一个谷仓。注意自从某一个时间之后，可能整个农场都开始不会是“全连通的”。
## 输入格式

输入第一行两个整数 $N,M$。

接下来 $M$ 行，每行两个整数 $u,v$（$1 \leq u,v \leq N$），描述一条连接 $u,v$ 两个农场的路。

最后 $N$ 行每行一个整数，表示第 $i$ 个被关闭的农场编号。
## 输出格式

输出 $N$ 行，每行包含 `YES` 或 `NO`，表示某个时刻农场是否是全连通的。

第一行输出最初的状态，第 $i$ 行（$2 \leq i \leq N$）输出第 $i-1$ 个农场被关闭后的状态。
## 样例

### 样例输入 #1
```
4 3
1 2
2 3
3 4
3
4
1
2
```
### 样例输出 #1
```
YES
NO
YES
YES
```


---

---
title: "【模板】并查集"
layout: "post"
diff: 普及/提高-
pid: P3367
tag: ['并查集', 'O2优化']
---
# 【模板】并查集
## 题目背景

自 2025 年 1 月 21 日，本题测试数据范围更新，详见：<https://www.luogu.com.cn/discuss/1045596>

这意味着现存题解的代码可能无法通过本题，管理组将会在 2025 年 2 月处理。
## 题目描述

如题，现在有一个并查集，你需要完成合并和查询操作。

## 输入格式

第一行包含两个整数 $N,M$ ,表示共有 $N$ 个元素和 $M$ 个操作。

接下来 $M$ 行，每行包含三个整数 $Z_i,X_i,Y_i$ 。

当 $Z_i=1$ 时，将 $X_i$ 与 $Y_i$ 所在的集合合并。

当 $Z_i=2$ 时，输出 $X_i$ 与 $Y_i$ 是否在同一集合内，是的输出 
 `Y` ；否则输出 `N` 。
## 输出格式

对于每一个 $Z_i=2$ 的操作，都有一行输出，每行包含一个大写字母，为 `Y` 或者 `N` 。 
## 样例

### 样例输入 #1
```
4 7
2 1 2
1 1 2
2 1 2
1 3 4
2 1 4
1 2 3
2 1 4
```
### 样例输出 #1
```
N
Y
N
Y

```
## 提示

对于 $15\%$ 的数据，$N \le 10$，$M \le 20$。

对于 $35\%$ 的数据，$N \le 100$，$M \le 10^3$。

对于 $50\%$ 的数据，$1\le N \le 10^4$，$1\le M \le 2\times 10^5$。

对于 $100\%$ 的数据，$1\le N\le 2\times 10^5$，$1\le M\le 10^6$，$1 \le X_i, Y_i \le N$，$Z_i \in \{ 1, 2 \}$。


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

---
title: "[NOIP 2017 提高组] 奶酪"
layout: "post"
diff: 普及/提高-
pid: P3958
tag: ['搜索', '2017', '并查集', 'NOIP 提高组', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [NOIP 2017 提高组] 奶酪
## 题目背景

NOIP2017 提高组 D2T1
## 题目描述

现有一块大奶酪，它的高度为 $h$，它的长度和宽度我们可以认为是无限大的，奶酪中间有许多半径相同的球形空洞。我们可以在这块奶酪中建立空间坐标系，在坐标系中，奶酪的下表面为 $z = 0$，奶酪的上表面为 $z = h$。

现在，奶酪的下表面有一只小老鼠 Jerry，它知道奶酪中所有空洞的球心所在的坐标。如果两个空洞相切或是相交，则 Jerry 可以从其中一个空洞跑到另一个空洞，特别地，如果一个空洞与下表面相切或是相交，Jerry 则可以从奶酪下表面跑进空洞；如果一个空洞与上表面相切或是相交，Jerry 则可以从空洞跑到奶酪上表面。

位于奶酪下表面的 Jerry 想知道，在不破坏奶酪的情况下，能否利用已有的空洞跑 到奶酪的上表面去?

空间内两点 $P_1(x_1,y_1,z_1)$、$P2(x_2,y_2,z_2)$ 的距离公式如下：


$$\mathrm{dist}(P_1,P_2)=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2+(z_1-z_2)^2}$$

## 输入格式

每个输入文件包含多组数据。

第一行，包含一个正整数 $T$，代表该输入文件中所含的数据组数。

接下来是 $T$ 组数据，每组数据的格式如下： 第一行包含三个正整数 $n,h,r$，两个数之间以一个空格分开，分别代表奶酪中空洞的数量，奶酪的高度和空洞的半径。

接下来的 $n$ 行，每行包含三个整数 $x,y,z$，两个数之间以一个空格分开，表示空洞球心坐标为 $(x,y,z)$。

## 输出格式

 $T$ 行，分别对应 $T$ 组数据的答案，如果在第 $i$ 组数据中，Jerry 能从下表面跑到上表面，则输出 `Yes`，如果不能，则输出 `No`。

## 样例

### 样例输入 #1
```
3 
2 4 1 
0 0 1 
0 0 3 
2 5 1 
0 0 1 
0 0 4 
2 5 2 
0 0 2 
2 0 4
```
### 样例输出 #1
```
Yes
No
Yes
```
## 提示

【输入输出样例 $1$ 说明】

 ![](https://cdn.luogu.com.cn/upload/pic/10860.png) 

第一组数据,由奶酪的剖面图可见：

第一个空洞在 $(0,0,0)$ 与下表面相切；

第二个空洞在 $(0,0,4)$ 与上表面相切；

两个空洞在 $(0,0,2)$ 相切。

输出 `Yes`。

 
第二组数据,由奶酪的剖面图可见：

两个空洞既不相交也不相切。

输出 `No`。

 
第三组数据,由奶酪的剖面图可见：

两个空洞相交，且与上下表面相切或相交。

输出 `Yes`。

【数据规模与约定】

对于 $20\%$ 的数据，$n = 1$，$1 \le h$，$r \le  10^4$，坐标的绝对值不超过 $10^4$。

对于 $40\%$ 的数据，$1 \le n \le 8$，$1 \le h$，$r \le 10^4$，坐标的绝对值不超过 $10^4$。

对于 $80\%$ 的数据，$1 \le n \le 10^3$，$1 \le h , r \le 10^4$，坐标的绝对值不超过 $10^4$。

对于 $100\%$ 的数据，$1 \le n \le 1\times 10^3$，$1 \le h , r \le 10^9$，$T \le 20$，坐标的绝对值不超过 $10^9$。


---

---
title: "[USACO19OPEN] Fence Planning S"
layout: "post"
diff: 普及/提高-
pid: P5429
tag: ['模拟', '2019', 'USACO', '并查集', '深度优先搜索 DFS']
---
# [USACO19OPEN] Fence Planning S
## 题目描述

Farmer John 的 $ N $ 头奶牛，编号为 $ 1 \ldots N $ （ $ 2 \leq N \leq 10^5 $ ），拥有一种围绕“哞网”，一些仅在组内互相交流却不与其他组进行交流的奶牛小组，组成的复杂的社交网络。

每头奶牛位于农场的二维地图上的不同位置 $ (x,y) $ ，并且我们知道有 $ M $ 对奶牛( $ 1 \leq M<10^5 $ )会相互哞叫。两头相互哞叫的奶牛属于同一哞网。

为了升级他的农场，Farmer John 想要建造一个四边与 $ x $ 轴和 $ y $ 轴平行的长方形围栏。Farmer John 想要使得至少一个哞网完全被围栏所包围（在长方形边界上的奶牛计为被包围的）。请帮助 Farmer John 求出满足他的要求的围栏的最小可能周长。有可能出现这一围栏宽为 $0$ 或高为 $0$ 的情况。
## 输入格式

输入的第一行包含 $ N $ 和 $ M $ 。以下 $ N $ 行每行包含一头奶牛的 $ x $ 坐标和 $ y $ 坐标（至多 $ 10^8 $ 的非负整数）。以下 $ M $ 行每行包含两个整数 $ a $ 和 $ b $ ，表示奶牛 $ a $ 和 $ b $ 之间有哞叫关系。每头奶牛都至少存在一个哞叫关系，并且输入中不会出现重复的哞叫关系。
## 输出格式

输出满足 Farmer John 的要求的围栏的最小周长。
## 样例

### 样例输入 #1
```
7 5
0 5
10 5
5 0
5 10
6 7
8 6
8 4
1 2
2 3
3 4
5 6
7 6
```
### 样例输出 #1
```
10
```


---

---
title: "[USACO18JAN] MooTube S"
layout: "post"
diff: 普及/提高-
pid: P6111
tag: ['搜索', '2018', 'USACO', '并查集', '深度优先搜索 DFS']
---
# [USACO18JAN] MooTube S
## 题目背景

*本题与 [金组同名题目](/problem/P4185) 在题意上一致，唯一的差别是数据范围。*
## 题目描述

在业余时间，Farmer John 创建了一个新的视频共享服务，他将其命名为 MooTube。在 MooTube 上，Farmer John 的奶牛可以录制，分享和发现许多有趣的视频。他的奶牛已经发布了 $N$ 个视频（$1 \leq N \leq 5000$），为了方便将其编号为  $1 \ldots N$ 。然而，FJ 无法弄清楚如何帮助他的奶牛找到他们可能喜欢的新视频。

FJ 希望为每个 MooTube 视频创建一个“推荐视频”列表。这样，奶牛将被推荐与他们已经观看过的视频最相关的视频。

FJ 设计了一个“相关性”度量标准，顾名思义，它确定了两个视频相互之间的相关性。他选择 $N-1$ 对视频并手动计算其之间的相关性。然后，FJ 将他的视频建成一棵树，其中每个视频是节点，并且他手动将 $N-1$ 对视频连接。为了方便，FJ 选择了 $N-1$ 对，这样任意视频都可以通过一条连通路径到达任意其他视频。 FJ 决定将任意一对视频的相关性定义为沿此路径的任何连接的最小相关性。

Farmer John 想要选择一个 $K$ 值，以便在任何给定的 MooTube 视频旁边，推荐所有其他与该视频至少有 $K$ 相关的视频。然而，FJ 担心会向他的奶牛推荐太多的视频，这可能会分散他们对产奶的注意力！因此，他想设定适当的 $K$ 值。 Farmer John希望得到您的帮助，回答有关 $K$ 值的推荐视频的一些问题。
## 输入格式

第一行输入包含 $N$ 和 $Q$（$1 \leq Q \leq 5000$）。

接下来的 $N-1$ 行描述了 FJ 手动比较的一对视频。 每行包括三个整数  $p_i$，$q_i$ 和 $r_i$（$1 \leq p_i, q_i \leq N$，$1 \leq r_i \leq 10^9$），表示视频 $p_i$ 和 $q_i$ 已连接并且相关性为 $r_i$。

接下来的 $Q$ 行描述了 Farmer John 的 $Q$ 个问题。每行包含两个整数，$k_i$ 和 $v_i$（$1 \leq k_i \leq 10^9$，$1 \leq v_i \leq N$），表示 FJ 的第 $i$ 个问题询问中当 $K = k_i$ 时，第 $v_i$ 个视频推荐列表中将推荐的视频数。
## 输出格式

输出 $Q$ 行。在第 $i$ 行，输出 FJ 的第 $i$ 个问题的答案。
## 样例

### 样例输入 #1
```
4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1
```
### 样例输出 #1
```
3
0
2
```


---

---
title: "选择题"
layout: "post"
diff: 普及/提高-
pid: P6691
tag: ['图论', '2020', '并查集', 'O2优化', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# 选择题
## 题目背景

小 L 喜欢逻辑推理。

一天，他在一本由英国哲士沃·协德编写的《我也不知道为什么要叫这个名字的一本有关逻辑学的书》中翻到了一道奇特的问题，但他并不会做。他知道你善于用程序解决问题，于是决定让你来帮助他完成这些问题。
## 题目描述

这是一道有 $n$ 个选项的选择题，每个选项的内容都很独特。第 $i$ 个选项的内容的形式如下：

+ 第 $a_i$ 个选项是正确/错误的

小 L 认为这种题目的答案不一定是唯一的，所以他想问题这道题有多少种合法的答案（可以全部正确或全部错误）。他还想问你这么多答案中，正确选项最多和最少的答案分别有多少个正确选项。

当然，如果这道题不存在合法的答案，你可以直接回答小 L `No answer`。
## 输入格式

第一行有一个正整数 $n$，表示选项个数。

接下来 $n$ 行，每行有两个整数 $a_i,opt_i$，描述一个选项。其中当 $opt_i=1$ 时，表示这个选项的内容为 **第 $a_i$ 个选项是正确的**；当 $opt_i=0$ 时，表示这个选项的内容为 **第 $a_i$ 个选项是错误的**。
## 输出格式

如果没有答案满足这道选择题，输出`No answer`。

否则输出三行，每行一个正整数，分别为合法答案数及正确选项最多和最少的答案分别有多少个正确选项。其中合法答案数要对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
4
2 1
4 0
1 1
2 0
```
### 样例输出 #1
```
2
3
1
```
### 样例输入 #2
```
10
4 1
7 0
2 0
3 1
7 1
5 0
9 1
10 1
8 0
1 1
```
### 样例输出 #2
```
No answer
```
## 提示

对于样例一，一共有下面 $2$ 种正确答案：

+ 第 $1,2,3$ 个选项是正确的。
+ 第 $4$ 个选项是正确的。

其中正确选项最多的答案有 $3$ 个选项正确，正确选项最少的答案有 $1$ 个选项正确。

### 数据范围
对于 $10\%$ 的数据，$n\leq 10$。  
对于 $30\%$ 的数据，$n\leq 100$。  
对于 $60\%$ 的数据，$n\leq 10^3$。  
对于 $100\%$ 的数据，$n\leq 10^6,1\leq a_i\leq n,i\neq a_i,opt_i\in\{0,1\}$。


---

---
title: "[蓝桥杯 2017 国 C] 合根植物"
layout: "post"
diff: 普及/提高-
pid: P8654
tag: ['2017', '并查集', '蓝桥杯国赛']
---
# [蓝桥杯 2017 国 C] 合根植物
## 题目描述

w 星球的一个种植园，被分成 $m \times n$ 个小格子（东西方向 $m$ 行，南北方向 $n$ 列）。每个格子里种了一株合根植物。

这种植物有个特点，它的根可能会沿着南北或东西方向伸展，从而与另一个格子的植物合成为一体。

如果我们告诉你哪些小格子间出现了连根现象，你能说出这个园中一共有多少株合根植物吗？
## 输入格式

第一行，两个整数 $m$，$n$，用空格分开，表示格子的行数、列数（$1<m,n<1000$）。

接下来一行，一个整数 $k$，表示下面还有 $k$ 行数据 $(0<k<10^5)$。

接下来 $k$ 行，每行两个整数 $a$，$b$，表示编号为 $a$ 的小格子和编号为 $b$ 的小格子合根了。

格子的编号一行一行，从上到下，从左到右编号。

比如：$5 \times 4$ 的小格子，编号：

```
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 16
17 18 19 20
```
## 输出格式

一行一个整数，表示答案
## 样例

### 样例输入 #1
```
5 4
16
2 3
1 5
5 9
4 8
7 8
9 10
10 11
11 12
10 14
12 16
14 18
17 18
15 19
19 20
9 13
13 17
```
### 样例输出 #1
```
5
```
## 提示

## 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/9q0xulxh.png)

时限 1 秒, 256M。蓝桥杯 2017 年第八届国赛


---

---
title: "[蓝桥杯 2019 省 A] 修改数组"
layout: "post"
diff: 普及/提高-
pid: P8686
tag: ['2019', '并查集', '蓝桥杯省赛']
---
# [蓝桥杯 2019 省 A] 修改数组
## 题目描述

给定一个长度为 $N$ 的数组 $A=[A_1,A_2, \cdots A_N]$，数组中有可能有重复出现的整数。

现在小明要按以下方法将其修改为没有重复整数的数组。小明会依次修改 $A_2,A_3, \cdots ,A_N$。

当修改 $A_i$ 时，小明会检查 $A_i$ 是否在 $A_1$ ∼ $A_{i-1}$ 中出现过。如果出现过，则小明会给 $A_i$ 加上 $1$；如果新的 $A_i$ 仍在之前出现过，小明会持续给 $A_i$ 加 $1$，直到 $A_i$ 没有在 $A_1$ ∼ $A_{i-1}$ 中出现过。

当 $A_N$ 也经过上述修改之后，显然 $A$ 数组中就没有重复的整数了。

现在给定初始的 $A$ 数组，请你计算出最终的 $A$ 数组。
## 输入格式

第一行包含一个整数 $N$。

第二行包含 $N$ 个整数 $A_1,A_2, \cdots ,A_N$。
## 输出格式

输出 $N$ 个整数，依次是最终的 $A_1,A_2, \cdots ,A_N$。
## 样例

### 样例输入 #1
```
5
2 1 1 3 4
```
### 样例输出 #1
```
2 1 3 4 5
```
## 提示

对于 $80\%$ 的评测用例，$1 \le N \le 10000$。

对于所有评测用例，$1 \le N \le 10^5$，$1 \le A_i \le 10^6$。

蓝桥杯 2019 年省赛 A 组 H 题。


---

---
title: "[SNCPC2019] Grid with Arrows"
layout: "post"
diff: 普及/提高-
pid: P9641
tag: ['2019', '并查集', 'O2优化', '陕西', 'XCPC']
---
# [SNCPC2019] Grid with Arrows
## 题目描述

BaoBao has just found a grid with $n$ rows and $m$ columns in his left pocket, where the cell in the $j$-th column of the $i$-th row (indicated by $(i, j)$) contains an arrow (pointing either upwards, downwards, leftwards or rightwards) and an integer $a_{i, j}$.

BaoBao decides to play a game with the grid. He will first select a cell as the initial cell and tick it. After ticking a cell (let's say BaoBao has just ticked cell $(i, j)$), BaoBao will go on ticking another cell according to the arrow and the integer in cell $(i, j)$.

- If the arrow in cell $(i, j)$ points upwards, BaoBao will go on ticking cell $(i-a_{i, j}, j)$ if it exists.
- If the arrow in cell $(i, j)$ points downwards, BaoBao will go on ticking cell $(i+a_{i, j}, j)$ if it exists.
- If the arrow in cell $(i, j)$ points leftwards, BaoBao will go on ticking cell $(i, j-a_{i, j})$ if it exists.
- If the arrow in cell $(i, j)$ points rightwards, BaoBao will go on ticking cell $(i, j+a_{i, j})$ if it exists.

If the cell BaoBao decides to tick does not exist, or if the cell is already ticked, the game ends.

BaoBao is wondering if he can select a proper initial cell, so that he can tick every cell in the grid exactly once before the game ends. Please help him find the answer.

## 输入格式

There are multiple test cases. The first line contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n \times m \le 10^5$), indicating the number of rows and columns of the grid.

For the following $n$ lines, the $i$-th line contains a string $s_i$ consisting of lowercased English letters ($|s_i| = m$, $s_{i, j} \in \{\text{`u' (ascii: 117)}, \text{`d' (ascii: 100)}, \text{`l' (ascii: 108)}, \text{`r'(ascii: 114)}\}$), where $s_{i, j}$ indicates the direction of arrow in cell $(i, j)$.

- If $s_{i, j} = \text{`u'}$, the arrow in cell $(i, j)$ points upwards.
- If $s_{i, j} = \text{`d'}$, the arrow in cell $(i, j)$ points downwards.
- If $s_{i, j} = \text{`l'}$, the arrow in cell $(i, j)$ points leftwards.
- If $s_{i, j} = \text{`r'}$, the arrow in cell $(i, j)$ points rightwards.

For the following $n$ lines, the $i$-th line contains $m$ integers $a_{i, 1}, a_{i, 2}, \dots, a_{i, m}$ ($1 \le a_{i, j} \le \max(n, m)$), where $a_{i, j}$ indicates the integer in cell $(i, j)$.

It's guaranteed that the sum of $n \times m$ of all test cases does not exceed $10^6$.
## 输出格式

For each test case output one line. If BaoBao can find a proper initial cell, print ``Yes`` (without quotes), otherwise print ``No`` (without quotes).

## 样例

### 样例输入 #1
```
2
2 3
rdd
url
2 1 1
1 1 2
2 2
rr
rr
1 1
1 1
```
### 样例输出 #1
```
Yes
No
```
## 提示

For the first sample test case, BaoBao can select cell $(1, 2)$ as the initial cell, so that he can tick all the cells exactly once in the following order: $(1, 2), (2, 2), (2, 3), (2, 1), (1, 1), (1, 3)$.

For the second sample test case, BaoBao can only tick at most $2$ cells no matter which cell is selected as the initial cell.

## 题目翻译

**【题目描述】**

宝宝刚刚在他的左口袋里发现了一个 $n$ 行 $m$ 列的网格，其中第 $i$ 行第 $j$ 列的单元格（表示为 $(i, j)$）包含一个箭头（指向上、下、左或右）和一个整数 $a_{i, j}$。

宝宝决定用这个网格玩一个游戏。他首先会选择一个单元格作为初始单元格并标记它。在标记一个单元格之后（假设宝宝刚刚标记了单元格 $(i, j)$），宝宝将根据单元格 $(i, j)$ 中的箭头和整数继续标记另一个单元格。

- 如果单元格 $(i, j)$ 中的箭头指向上方，宝宝将继续标记单元格 $(i-a_{i, j}, j)$，如果该单元格存在的话。
- 如果单元格 $(i, j)$ 中的箭头指向下方，宝宝将继续标记单元格 $(i+a_{i, j}, j)$，如果该单元格存在的话。
- 如果单元格 $(i, j)$ 中的箭头指向左方，宝宝将继续标记单元格 $(i, j-a_{i, j})$，如果该单元格存在的话。
- 如果单元格 $(i, j)$ 中的箭头指向右方，宝宝将继续标记单元格 $(i, j+a_{i, j})$，如果该单元格存在的话。
如果宝宝决定标记的单元格不存在，或者该单元格已经被标记，游戏结束。

宝宝想知道他是否可以选择一个合适的初始单元格，以便在游戏结束前恰好标记网格中的每一个单元格一次。请帮助他找到答案。

**【输入格式】**

有多个测试用例。第一行包含一个整数 $T$，表示测试用例的数量。对于每个测试用例：

第一行包含两个整数 $n$ 和 $m$ ($1 \le n \times m \le 10^5$)，表示网格的行数和列数。

接下来的 $n$ 行中，第 $i$ 行包含一个字符串 $s_i$，由小写英文字母组成（$|s_i| = m$，$s_{i, j} \in \{\text{`u' (ascii: 117)}, \text{`d' (ascii: 100)}, \text{`l' (ascii: 108)}, \text{`r'(ascii: 114)}\}$），其中 $s_{i, j}$ 表示单元格 $(i, j)$ 中箭头的方向。

- 如果 $s_{i, j} = \text{`u'}$，单元格 $(i, j)$ 中的箭头指向上方。
- 如果 $s_{i, j} = \text{`d'}$，单元格 $(i, j)$ 中的箭头指向下方。
- 如果 $s_{i, j} = \text{`l'}$，单元格 $(i, j)$ 中的箭头指向左方。
- 如果 $s_{i, j} = \text{`r'}$，单元格 $(i, j)$ 中的箭头指向右方。

接下来的 $n$ 行中，第 $i$ 行包含 $m$ 个整数 $a_{i, 1}, a_{i, 2}, \dots, a_{i, m}$ ($1 \le a_{i, j} \le \max(n, m)$)，其中 $a_{i, j}$ 表示单元格 $(i, j)$ 中的整数。

保证所有测试用例的 $n \times m$ 之和不超过 $10^6$。

**【输出格式】**

对于每个测试用例输出一行。如果宝宝可以找到一个合适的初始单元格，输出 “Yes”（不含引号），否则输出 “No”（不含引号）。

**【样例解释】**

对于第一个示例测试用例，宝宝可以选择单元格 $(1, 2)$ 作为初始单元格，这样他可以按以下顺序恰好打勾所有单元格：$(1, 2), (2, 2), (2, 3), (2, 1), (1, 1), (1, 3)$。

对于第二个示例测试用例，无论选择哪个单元格作为初始单元格，宝宝最多只能打勾 2 个单元格。

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

