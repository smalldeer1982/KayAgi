---
title: "[TOIP 2023] 公路"
layout: "post"
diff: 提高+/省选-
pid: P11852
tag: ['2023', '双连通分量', '台湾']
---
# [TOIP 2023] 公路
## 题目描述

某國的公路網由 $n$ 個城鎮（編號 $1\sim n$）和 $m$ 條連接兩個相異城鎮的雙向公路組成，每條公路有其長度，以公里表示。最近該國流行起電動車，但是公路之間都沒有充電站，電動車只能在城鎮充電。該國交通部門官員十分擔心有些被觀光局規劃好的旅程會使電動車的續航力沒辦法走完一條公路，也因此，官員希望旅程中使用到的最長公路長度要盡量短，否則若有些電動車的實際續航力低於一段公路的長度，它們一定會在公路中間沒電。

對於一趟被規劃好的旅程，觀光局會為其決定好一個起點 $u$ 和終點 $v$，並找出 $\textbf{兩條}$ 由 $u$ 到 $v$ $\textbf{公路相互不重複}$ 的路徑，來做為一個完整的旅程規劃。例如下圖是一個 $n=7$、$m=9$ 的例子，點上標示城鎮的編號，邊上標示公路的長度。

![](https://cdn.luogu.com.cn/upload/image_hosting/cugaijat.png)

若要規劃城鎮 $1$ 到城鎮 $2$ 的旅程，可以採用以下兩條路徑：

- $1\to 2$ 以及 $1\to 3\to 2$

這兩條路徑中，所使用的到的最長公路長度是 $8$ 公里，但若採用以下兩條路徑：

- $1\to 2$ 以及 $1\to 3\to 5\to 2$

就可以將使用的最長公路長度降低至 $5$，也是使最長公路最短的選擇方式。而若要規劃城鎮 $1$ 到城鎮 $6$ 的旅程，可以採用以下兩條路徑：

- $1\to 3\to 6$ 以及 $1\to 2\to 5\to 3\to 4\to 6$

使用的最長公路長度是 $7$，同時也是使最長公路最短的選擇方式，注意到雖然這兩條路徑共用了同一個城鎮 $3$，但條件只要求「使用的公路不重複」，因此為一種滿足條件的路徑選擇方式。

一個旅程的兩條路徑所使用的最長公路愈短，則該旅程愈佳。今給定 $q$ 對起終點，請寫程式計算每對起終點之最佳旅程使用到的最長公路長度，或者回報不存在任何一種路徑的選擇方式。
## 样例

### 样例输入 #1
```
7 9
1 2 5
1 3 3
2 3 8
2 5 3
3 4 3
3 5 4
3 6 2
4 6 7
6 7 6
3
1 2
1 6
3 7
```
### 样例输出 #1
```
5
7
-1
```


---

---
title: "[GCJ Farewell Round #2] Railroad Maintenance"
layout: "post"
diff: 提高+/省选-
pid: P12954
tag: ['2023', '双连通分量', 'Google Code Jam']
---
# [GCJ Farewell Round #2] Railroad Maintenance
## 题目描述

You are in charge of the maintenance of a railroad network. The network consists of $\mathbf{N}$ stations and $\mathbf{L}$ train lines. Each train line serves a fixed list of stations bidirectionally (trains turn around in the first and last stations of the list). Transfers from one line to another in a station are possible, which means a trip in the network from station $a$ to station $b$ is possible if there is a list of train lines such that the first one serves station $a$, the last one serves station $b$, and for any consecutive pair of train lines in the list there is at least one station that they both serve.

The easiest way to do maintenance is to shut down entire lines, one at a time. However, some train lines may be essential. A train line is essential if removing it would make at least one trip between a pair of stations not possible.

Given the list of existing train lines, calculate how many of them are essential.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing two integers $\mathbf{N}$ and $\mathbf{L}$: the number of stations and train lines in the network. Then, $\mathbf{L}$ groups of 2 lines follow. The first line of the $i$-th group contains a single integer $\mathbf{K}_i$ the number of stations served by the $i$-th train line. The second line of the $i$-th group contains $\mathbf{K}_i$ integers $\mathbf{S}_{i,1}, \mathbf{S}_{i,2}, \ldots, \mathbf{S}_{i,\mathbf{K}_i}$ representing the stations served by the $i$-th train line.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the number of train lines that are essential.
## 样例

### 样例输入 #1
```
4
4 3
3
1 2 3
2
1 4
3
4 1 3
4 4
2
1 2
2
3 4
2
3 2
2
4 1
4 3
2
1 2
2
3 4
2
3 2
4 3
2
1 2
2
3 4
4
4 1 2 3
```
### 样例输出 #1
```
Case #1: 1
Case #2: 0
Case #3: 3
Case #4: 1
```
## 提示

**Sample Explanation**

In Sample Case #1, the first train line is essential because it is the only one serving station $2$. Since shutting any other line down would not make travel between at least one pair of stations impossible, they are not essential.

![](https://cdn.luogu.com.cn/upload/image_hosting/hstw804z.png)

In Sample Case #2, no line is essential.

![](https://cdn.luogu.com.cn/upload/image_hosting/iodjuwf1.png)

Sample Case #3 is similar to Sample Case #2, but missing the last train line. That makes all remaining train lines essential.

In Sample Case #4, the last train line is essential as there is no way to go from station $1$ to station $4$ without it. As in Sample Case #1, since this train line already connects every station, no other line is essential.

![](https://cdn.luogu.com.cn/upload/image_hosting/xcha3btp.png)

**Sample Explanation**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{K}_i \leq \mathbf{N}$ for all $i$.
- $1 \leq \mathbf{S}_{i,j} \leq \mathbf{N}$, for all $i, j$.
- $\mathbf{S}_{i,j} \neq \mathbf{S}_{i,j'}$, for all $i, j, j'$ such that $j \neq j'$ (Each train line serves a station at most once).

The trip between all pairs of stations is possible as per the definition above when no train line is shut down.

**Test Set 1 (9 Pts, Visible Verdict)**

- $2 \leq \mathbf{N} \leq 100$.
- $1 \leq \mathbf{L} \leq 100$.
- $\mathbf{K}_1 + \mathbf{K}_2 + \cdots + \mathbf{K}_\mathbf{L} \leq 200$.

**Test Set 2 (20 Pts, Visible Verdict)**

- $2 \leq \mathbf{N} \leq 10^5$.
- $1 \leq \mathbf{L} \leq 10^5$.
- $\mathbf{K}_1 + \mathbf{K}_2 + \cdots + \mathbf{K}_\mathbf{L} \leq 2 \times 10^5$.


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
title: "「EVOI-RD2」旅行家"
layout: "post"
diff: 提高+/省选-
pid: P7924
tag: ['O2优化', '双连通分量', '最近公共祖先 LCA', '差分']
---
# 「EVOI-RD2」旅行家
## 题目描述

小 A 是一个热衷于旅行的旅行家。有一天，他来到了一个城市，这个城市由 $n$ 个景点与 $m$ 条连接这些景点的道路组成。每个景点有一个**美观度** $a_i$。

定义一条**旅游路径**为两个景点之间的一条非严格简单路径，也就是点可以重复经过，而边不可以。

接下来有 $q$ 个旅游季，每个旅游季中，小 A 将指定两个顶点 $x$ 和 $y$，然后他将走遍 $x$ 到 $y$ 的**所有旅游路径**。 

所有旅游季结束后，小 A 会统计他所经过的所有景点的美观度之和（重复经过一个景点只统计一次美观度）。他希望你告诉他这个美观度之和。
## 输入格式

第一行两个正整数 $n,m$。

第二行 $n$ 个正整数 $a_i$，代表顶点 $i$ 的权值。

接下来 $m$ 行，每行 $2$ 个正整数，表示一条无向边的两个端点。

然后一个正整数 $q$，代表有 $q$ 个旅游季。

接下来 $q$ 行，每行 $2$ 个整数 $x,y$，表示指定的起点和终点。
## 输出格式

一行，一个整数表示最终的美观度总和。
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 2
2 3
1 4
4 3
3 5
3
1 2
1 4
1 3

```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
5 6
1 2 3 4 5
1 2
2 3
1 4
1 5
4 3
3 5
3
1 2
1 4
1 3

```
### 样例输出 #2
```
15
```
## 提示

**【数据规模与范围】**

**本题采用捆绑测试**

+ Subtask 1 (30 pts)：$3 \leq n \leq 500,m \leq 2 \times 10^5,q=200$。
+ Subtask 2 (30 pts)：$3 \leq n \leq 3 \times 10^5,m \leq 2 \times 10^6,q=10^6$。
+ Subtask 3 (40 pts)：$3 \leq n \leq 5 \times 10^5,m \leq 2 \times 10^6,q=10^6$。

对于 $100\%$ 的数据，保证 $3 \leq n \leq 5 \times  10^5$，$m \leq 2 \times 10^6$，$q=10^6$，$1 \leq a_i \leq 100$，且该图联通，没有重边和自环。

---

**对于题面的解释：**


![](https://cdn.luogu.com.cn/upload/image_hosting/a2oku1vq.png)

上图与样例无关。

如图，为城市的景点分布图，为无向图。  
假设 $6$ 号顶点为 $x$ 景点，$5$ 号顶点为 $y$ 景点。  
很显然，路径 $6 \rightarrow 2 \rightarrow 4 \rightarrow 5$ 和路径 $6 \rightarrow 2 \rightarrow 1 \rightarrow 3 \rightarrow 5$ 都是合法的，这两条路径满足了都是简单路径的条件，并且都是在一次旅游季中行走的。  
虽然 $6 \rightarrow 2$ 这条边经过了 $2$ 次，但仍旧是合法的，因为它们不是在一条路径中经过的。

简单来说，一次旅游季会走不定条路径，每条路径必须是简单路径，但是每条简单路径之间可以有重边。


---

