---
title: "[USACO24FEB] Bessla Motors G"
layout: "post"
diff: 提高+/省选-
pid: P10193
tag: ['贪心', 'USACO', '2024', 'O2优化', '最短路']
---
# [USACO24FEB] Bessla Motors G
## 题目背景

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。本题的内存限制为 512MB，通常限制的 2 倍。**
## 题目描述

为了推广他的贝斯拉（Bessla）电动拖拉机系列，Farmer John 希望展示贝斯拉的充电网络。他已标记了地图上 $N$（$2\le N\le 5\cdot 10^4$）个编号为 $1\ldots N$ 的兴趣点，其中前 $C$（$1\le C<N$）个是充电站，其余为旅游目的地。这些兴趣点之间由 $M$（$1 \le M \le 10^5$）条双向道路连接，其中第 $i$ 条连接不同的点 $u_i$ 和 $v_i$（$1\le u_i,v_i\le N$）且长度为 $l_i$ 英里（$1\le l_i\le 10^9$）。

贝斯拉一次充电最多可行驶 $2R$英里（$1\le R\le 10^9$），使之可以到达一个充电站 $R$ 英里范围内的任何目的地。一个目的地被称之为交通便利的，如果可以从至少 $K$（$1\le K\le 10$）个不同的充电站到达目的地。你的任务是帮助 Farmer John 确定交通便利的旅游目的地的集合。 
## 输入格式

输入的第一行包含五个空格分隔的整数 $N$，$M$，$C$，$R$ 和 $K$。以下 $M$ 行，每行包含三个空格分隔的整数 $u_i$，$v_i$ 和 $l_i$，其中 $u_i\neq v_i$。

充电站的编号为 $1,2,\ldots,C$。其余兴趣点均为旅游目的地。 
## 输出格式

首先输出一行，包含交通便利的旅游目的地的数量。然后升序输出所有交通便利的旅游目的地，每个一行。
## 样例

### 样例输入 #1
```
3 3 1 4 1
1 2 3
1 3 5
2 3 2
```
### 样例输出 #1
```
1
2
```
### 样例输入 #2
```
4 3 2 101 2
1 2 1
2 3 100
1 4 10
```
### 样例输出 #2
```
2
3
4
```
### 样例输入 #3
```
4 3 2 100 2
1 2 1
2 3 100
1 4 10
```
### 样例输出 #3
```
1
4

```
## 提示

### 样例解释 1

我们在 $1$ 有一个充电站。从这个充电站出发，我们可以到达 $2$（因为它与 $1$ 的距离为 $3$），但不能到达 $3$（因为它与 $1$ 的距离为 $5$）。因此，只有点 $2$ 是交通便利的。

### 样例解释 2

我们在 $1$ 和 $2$ 有充电站，点 $3$ 和 $4$ 均位于 $1$ 和 $2$ 的 $101$ 距离内。因此，点 $3$ 和 $4$ 都是交通便利的。

### 测试点性质

- 测试点 $4-5$：$K=2$，$N\le 500$ 且 $M\le 1000$。
- 测试点 $6-7$：$K=2$。
- 测试点 $8-15$：没有额外限制。


---

---
title: "[蓝桥杯 2023 国 A] 迷宫探险"
layout: "post"
diff: 提高+/省选-
pid: P10422
tag: ['2023', '最短路', '蓝桥杯国赛', '状压 DP']
---
# [蓝桥杯 2023 国 A] 迷宫探险
## 题目描述

勇士小蓝准备去遥远的 LQ 迷宫探险，拿到迷宫中的宝藏。迷宫可以看做是一个具有 $N$ 个顶点(顶点编号为 $0\sim N-1$) 和 $M$ 条边的无向图，其中每个顶点上都有一只怪物，每只怪物都具有一定的攻击力，每条边都具有一个权重 $w$ 表示小蓝经过边时消耗的时间。

想要拿到迷宫宝藏，小蓝需要从 $0$ 号顶点出发对地图进行探险，在经过顶点时可以对怪物进行击杀，小蓝具有必杀技，能保证一招就击败怪物，但在小蓝对某个怪物进行击杀时，与这个怪物所在结点相邻接的结点上仍存活着的怪物会对小蓝发起一次攻击(注意，不包括小蓝正在击杀的怪物)，小蓝会减少对应攻击力大小的血量。当小蓝击杀完所有怪物并且到达顶点 $N-1$，并且此时小蓝的血量大于 $0$，那么小蓝才可以获得迷宫宝藏。

注意，小蓝的必杀技很快，因此在击杀怪物时可以视为不消耗时间；一个怪物只需要被击杀一次就会消失，只有在小蓝击杀怪物时，与其相邻接的结点上的怪物才会对小蓝发起一次攻击。

如果小蓝可以获得迷宫宝藏，请你输出所需要的最小时间。否则输出 $-1$ 即可。
## 输入格式

输入的第一行包含三个整数 $N, M, HP$，相邻的整数之间使用一个空格分隔，分别表示顶点数、无向边数以及小蓝初始时侯的血量。

第二行包含 $N$ 个整数，相邻的整数之间使用一个空格分隔，其中第 $i(0\le i\le N-1)$ 个整数表示编号为 $i$ 的顶点上的怪物的攻击力大小;

接下来 $M$ 行，每行包含三个整数 $u, v, w$ 表示在顶点 $u$ 和 $v$ 之间存在一条权重为 $w$ 的无向边。
## 输出格式

输出一行包含一个整数表示答案，若小蓝无论如何也无法获得迷宫宝藏，则输出 $-1$。
## 样例

### 样例输入 #1
```
3 2 10
2 10 5
0 1 1
1 2 2

```
### 样例输出 #1
```
5

```
## 提示

**【样例解释 1】**

小蓝初始在 $0$ 号点，下一步移动到 $1$ 号点，耗费时间 $10$。

击杀 $1$ 号点的怪物，将会受到 $0$、$2$ 号怪物的攻击，血量减少 $7$，剩余血量为 $3$。

移动到 $0$ 号点，耗费时间 $10$，接着击杀 $0$ 号怪物，不会受到攻击。

移动到 $1$ 号点，再继续移动到 $2$ 号点，耗费时间 $30$，此时击杀 $2$ 号怪物，不会受到攻击，击杀完毕后小蓝剩余 $3$ 血量，满足题目要求，总计耗费时间为 $50$。

**【评测用例规模与约定】**

对于 $40\%$ 的评测用例，$1\le N\le 10$；  
对于所有评测用例，$1\le N\le 15$，$1\le M\le N^2$，$1\le HP\le 100$，$1\le \text{怪物攻击力} \le 10$，$1\le w\le 10$。


---

---
title: "[NOIP 2009 提高组] 最优贸易"
layout: "post"
diff: 提高+/省选-
pid: P1073
tag: ['动态规划 DP', '搜索', '图论', '2009', 'NOIP 提高组', '最短路', '强连通分量']
---
# [NOIP 2009 提高组] 最优贸易
## 题目背景

本题原题数据极弱，Subtask 0 中的测试点为原题测试点，Subtask 1 中的测试点为 Hack 数据。
## 题目描述

$C$ 国有 $n$ 个大城市和 $m$ 条道路，每条道路连接这 $n$ 个城市中的某两个城市。任意两个城市之间最多只有一条道路直接相连。这 $m$ 条道路中有一部分为单向通行的道路，一部分为双向通行的道路，双向通行的道路在统计条数时也计为 $1$ 条。

$C$ 国幅员辽阔，各地的资源分布情况各不相同，这就导致了同一种商品在不同城市的价格不一定相同。但是，同一种商品在同一个城市的买入价和卖出价始终是相同的。

商人阿龙来到 $C$ 国旅游。当他得知同一种商品在不同城市的价格可能会不同这一信息之后，便决定在旅游的同时，利用商品在不同城市中的差价赚回一点旅费。设 $C$ 国 $n$ 个城市的标号从 $1\sim n$，阿龙决定从 $1$ 号城市出发，并最终在 $n$ 号城市结束自己的旅行。在旅游的过程中，任何城市可以重复经过多次，但不要求经过所有 $n$ 个城市。阿龙通过这样的贸易方式赚取旅费：他会选择一个经过的城市买入他最喜欢的商品――水晶球，并在之后经过的另一个城市卖出这个水晶球，用赚取的差价当做旅费。由于阿龙主要是来 $C$ 国旅游，他决定这个贸易只进行最多一次，当然，在赚不到差价的情况下他就无需进行贸易。

假设 $C$ 国有 $5$ 个大城市，城市的编号和道路连接情况如下图，单向箭头表示这条道路为单向通行，双向箭头表示这条道路为双向通行。

![](https://cdn.luogu.com.cn/upload/image_hosting/flre534z.png)

假设 $1\sim n$ 号城市的水晶球价格分别为 $4,3,5,6,1$。

阿龙可以选择如下一条线路：$1\to2\to3\to5$，并在 $2$ 号城市以 $3$ 的价格买入水晶球，在 $3$ 号城市以 $5$ 的价格卖出水晶球，赚取的旅费数为 $2$。

阿龙也可以选择如下一条线路：$1\to4\to5\to4\to5$，并在第 $1$ 次到达 $5$ 号城市时以 $1$ 的价格买入水晶球，在第 $2$ 次到达 $4$ 号城市时以 $6$ 的价格卖出水晶球，赚取的旅费数为 $5$。

现在给出 $n$ 个城市的水晶球价格，$m$ 条道路的信息（每条道路所连接的两个城市的编号以及该条道路的通行情况）。请你告诉阿龙，他最多能赚取多少旅费。
## 输入格式

第一行包含 $2$ 个正整数 $n$ 和 $m$，中间用一个空格隔开，分别表示城市的数目和道路的数目。

第二行 $n$ 个正整数，每两个整数之间用一个空格隔开，按标号顺序分别表示这 $n$ 个城市的商品价格。

接下来 $m$ 行，每行有 $3$ 个正整数 $x,y,z$，每两个整数之间用一个空格隔开。如果 $z=1$，表示这条道路是城市 $x$ 到城市 $y$ 之间的单向道路；如果 $z=2$，表示这条道路为城市 $x$ 和城市 $y$ 之间的双向道路。


## 输出格式

一个整数，表示最多能赚取的旅费。如果没有进行贸易，则输出 $0$。
## 样例

### 样例输入 #1
```
5 5 
4 3 5 6 1 
1 2 1 
1 4 1 
2 3 2 
3 5 1 
4 5 2 
```
### 样例输出 #1
```
5
```
## 提示

【数据范围】

输入数据保证 $1$ 号城市可以到达 $n$ 号城市。

对于 $10\%$ 的数据，$1\leq n\leq 6$。

对于 $30\%$ 的数据，$1\leq n\leq 100$。

对于 $50\%$ 的数据，不存在一条旅游路线，可以从一个城市出发，再回到这个城市。

对于 $100\%$ 的数据，$1\leq n\leq 100000$，$1\leq m\leq 500000$，$1\leq  x,y\leq  n$，$1\leq  z\leq  2$，$1\leq $ 各城市的编号 $\leq  n$。

水晶球价格 $\leq 100$。

NOIP 2009 提高组 第三题


---

---
title: "[EC Final 2020] City Brain"
layout: "post"
diff: 提高+/省选-
pid: P10819
tag: ['贪心', '2020', '三分', 'Special Judge', 'O2优化', '最短路', 'ICPC']
---
# [EC Final 2020] City Brain
## 题目描述

Prof. Pang works for the City Brain program of Capital Grancel. The road network of Grancel can be represented by an undirected graph. Initially, the speed limit on each road is $1$m/s. Prof. Pang can increase the speed limit on a road by $1$m/s with the cost of $1$ dollar. Prof. Pang has $k$ dollars. He can spend any nonnegative integral amount of money on each road. If the speed limit on some road is $a$m/s, it takes $1/a$ seconds for anyone to go through the road in either direction.

After Prof. Pang spent his money, Prof. Du starts to travel from city $s_1$ to city $t_1$ and Prof. Wo starts to travel from city $s_2$ to city $t_2$. Help Prof. Pang to spend his money wisely to minimize the sum of minimum time of Prof. Du's travel and Prof. Wo's travel. It is guaranteed that $s_1$ and $t_1$ are connected by at least one path and that $s_2$ and $t_2$ are connected by at least one path.
## 输入格式

The first line contains three integers $n$, $m$, $k$ ($1\le n \le 5000$, $0\le m \le 5000$, $0\le k\le 10^9$) separated by single spaces denoting the number of vertices, the number of edges in the graph and the number of dollars Prof. Pang has.

Each of the following $m$ lines contains two integers $a$, $b$ ($1\le a, b\le n, a\neq b$) separated by a single space denoting the two endpoints of one road. There can be multiple roads between the same pair of cities.

The following line contains four integers $s_1$, $t_1$, $s_2$, $t_2$ ($1\le s_1, t_1, s_2, t_2\le n$) separated by single spaces denoting the starting vertices and ending vertices of Prof. Du and Prof. Wo's travels.
## 输出格式

Output one decimal in the only line -- the minimum sum of Prof. Du's travel time and Prof. Wo's travel time. The answer will be considered correct if its absolute or relative error does not exceed $10^{-9}$.
## 样例

### 样例输入 #1
```
6 5 1
1 2
3 2
2 4
4 5
4 6
1 5 3 6
```
### 样例输出 #1
```
5.000000000000
```
### 样例输入 #2
```
1 0 100
1 1 1 1
```
### 样例输出 #2
```
0.000000000000
```
### 样例输入 #3
```
4 2 3
1 2
3 4
1 2 3 4
```
### 样例输出 #3
```
0.833333333333
```


---

---
title: "[NOISG 2023 Finals] Airplane"
layout: "post"
diff: 提高+/省选-
pid: P11535
tag: ['2023', '最短路', 'NOISG（新加坡）']
---
# [NOISG 2023 Finals] Airplane
## 题目描述

兔子 Benson 正要启动飞机！

有 $n$ 块 Benson 可以飞入的区域，由 $1\sim n$ 编号。受地形限制，进入第 $i$ 块区域时，需要保证飞机的高度不低于 $a_i$。保证 $a_1=a_n=0$。

此外，由于风况复杂而 Benson 的经验尚不充足（毕竟他是只兔子），他只能在某些特定的航线上双向飞行。具体地，有 $m$ 条航线，由 $1\sim m$ 编号，其中第 $i$ 条航线 $u_j,v_j$ 表示 Benson 可以在这两块区域间直接飞行。

Benson 发现，他可以通过在直接的航线上飞行，使得这些区域两两可达。

现在，Benson 在 $1$ 号区域，高度为 $0$。他希望降落在 $n$ 号区域，高度自然也为 $0$。每一分钟，Benson 可以跨过一条航线或不移动，并**同时**使飞机的高度上升 $1$、下降 $1$ 或保持不变。注意，当他到达 $i$ 区域时，必须保证飞机的高度不低于 $a_i$。

Benson 想知道，从 $1$ 号区域出发，在 $n$ 号区域降落，所需的最小时间。
## 输入格式

第一行两个正整数 $n, m$，用空格隔开。

接下来一行 $n$ 个整数 $a_1, a_2,\cdots, a_n$，表示区域的高度限制。

接下来 $m$ 行，每行两个正整数 $u_j,v_j$，表示一条在 $u_j,v_j$ 间的双向航线。
## 输出格式

一行一个整数，表示 Benson 所需的最小时间。
## 样例

### 样例输入 #1
```
3 2
0 2 0
1 2
2 3

```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
11 12
0 0 0 0 0 0 2 2 1 5 0
1 2
2 3
3 4
4 5
5 6
6 11
1 7
7 8
8 9
9 11
1 10
10 11

```
### 样例输出 #2
```
5
```
## 提示

#### 样例 #1 解释

Benson 从 $1$ 出发，在 $3$ 降落，总共需要 $4$ 分钟：

- 第 $1$ 分钟，Benson 不移动，同时高度从 $0$ 变为 $1$；
- 第 $2$ 分钟，从 $1$ 移动到 $2$，同时高度从 $1$ 变为 $2$；
- 第 $3$ 分钟，从 $2$ 移动到 $3$，同时高度从 $2$ 变为 $1$；
- 第 $4$ 分钟，Benson 不移动，同时高度从 $1$ 变为 $0$。

#### 数据范围

| Subtask | 分值 | 特殊限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $0$ | 样例 |
| $1$ | $22$ | $m=n-1,u_j=j,v_j=j+1$ |
| $2$ | $10$ | $n\leq 2000$，$m\leq 4000$，$a_i\leq 2000$ |
| $3$ | $31$ | $n\leq 2000$，$m\leq 4000$ |
| $4$ | $37$ | 无 |

对于 $100\%$ 的数据：

- $1\leq n\leq 2\times 10^5$
- $1\leq m\leq 4\times 10^5$
- $0\leq a_i\leq 10^8$，$a_1=a_n=0$
- $1\leq u_j,v_j\leq n$，$u_j\ne v_j$


---

---
title: "【MX-X7-T5】[LSOT-3] 你的列车是生存战略"
layout: "post"
diff: 提高+/省选-
pid: P11564
tag: ['O2优化', '图论建模', '最短路', '梦熊比赛']
---
# 【MX-X7-T5】[LSOT-3] 你的列车是生存战略
## 题目背景

原题链接：<https://oier.team/problems/X7F>。

>啊啊 我搭上了那趟列车$\\$无论被业火灼烧多少次$\\$或是化作灰烬$\\$为何我要如此$\\$因为这是通往你的道路$\\$就算事与愿违也好$\\$还是听天由命也罢$\\$我将要改写这个世界$\\$
## 题目描述

Ringo 要带着企鹅罐乘坐列车前往命运所至之地寻找 Shyouma 并且完成命运换乘！

她可以通过乘坐列车在冰之世界的 $n$ 个车站中穿行，车站编号为 $1 \sim n$。

每一个车站都有两个标号，第 $i$ 个车站的标号分别为 $c_i$ 和 $d_i$。

冰之世界中一共有普通列车和特快列车两种列车。

- 任意两地之间都有一条**可以往返**的普通列车的线路，车站 $i$ 与车站 $j$ 之间的线路所花费的时间为 $\min(a_{c_i \mathbin{|} c_j},b_{d_i \mathbin{\&} d_j})$（$\mathbin{|}$ 表示按位或，$\mathbin{\&}$ 表示按位与）。**保证 $\boldsymbol{a}$ 单调不降，$\boldsymbol{b}$ 单调不升。**
- 特快列车一共有 $m$ 条线路，第 $i$ 条是从车站 $u_i$ **驶向**车站 $v_i$ 的**单向线路**，所花费的时间为 $w_i$。


Ringo 希望能更快找到 Shyouma，不然世界就要毁灭了！

Ringo 开始的时候在车站 $1$，但是她不知道命运所至之地到底在哪里。所以她想知道对于每一个车站，如果 Shyouma 在那里，她最少需要花多少时间到达 Shyouma 所在的位置。
## 输入格式

第一行，三个非负整数 $n, m, k$。其中 $k$ 表示 $c_i, d_i \in [0,2^k)$。

第二行，$n$ 个非负整数 $c_1, \ldots, c_n$。

第三行，$n$ 个非负整数 $d_1, \ldots, d_n$。

第四行，$2^k$ 个非负整数 $a_0, \ldots, a_{2^k - 1}$。

第五行，$2^k$ 个非负整数 $b_0, \ldots, b_{2^k - 1}$。

**保证 $\boldsymbol{a}$ 单调不降，$\boldsymbol{b}$ 单调不升。**

接下来 $m$ 行，第 $i$ 行三个非负整数 $u_i, v_i, w_i$。
## 输出格式

仅一行，$n$ 个整数，第 $i$ 个表示从车站 $1$ 到车站 $i$ 所花费的最少的时间。
## 样例

### 样例输入 #1
```
5 4 3
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5 7 7 8
8 7 6 5 4 3 2 1
1 2 5
2 3 4
3 4 2
4 5 3

```
### 样例输出 #1
```
0 4 4 6 7

```
### 样例输入 #2
```
40 40 5
31 30 28 30 30 24 31 16 28 24 16 28 31 24 17 31 31 28 5 16 4 16 24 9 8 16 28 28 24 30 16 28 24 31 16 2 16 28 28 24
24 7 21 15 16 18 30 15 23 24 29 12 2 14 11 0 5 27 10 23 11 28 27 21 1 1 28 21 11 18 31 23 1 18 23 22 22 9 1 4
0 102 102 102 102 102 260 260 260 260 601 601 601 601 601 601 601 601 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264
108799 106048 100679 98235 95333 90350 80153 79411 70293 69091 64328 58817 55536 53256 42932 42687 41145 40487 40047 37901 32251 29823 26460 25786 21684 20508 19995 19172 18248 12890 12397 10740
38 27 0
17 3 3
26 8 12
12 11 14
1 23 8
4 7 6
18 36 18
1 33 6
38 18 8
19 38 17
24 21 4
31 16 18
26 4 8
5 31 1
6 28 4
9 10 7
26 7 7
8 37 19
40 29 4
24 9 0
15 6 19
39 12 18
33 39 8
10 34 0
39 30 3
28 25 5
19 13 9
6 2 0
1 20 10
19 17 8
15 26 18
17 13 18
33 40 8
40 22 15
15 28 0
17 35 10
24 5 13
18 14 19
40 22 2
6 32 13

```
### 样例输出 #2
```
0 630 993 619 889 630 618 611 876 883 46 32 991 1026 611 629 990 1007 982 10 880 16 8 876 616 611 999 611 18 17 611 643 6 883 611 1025 611 999 14 14

```
## 提示

> 生存戦略、しましょうか

**【样例解释 #1】**

Ringo 开始的时候就在车站 $1$，所以到车站 $1$ 最少的花费的时间为 $0$。

到车站 $2$ 的花费最少时间的路径为乘坐从 $1$ 到 $2$ 的普通列车，花费的时间为 $\min(a_{c_1 \mathbin{|} c_2},b_{d_1 \mathbin{\&} d_2})=\min(a_3,b_0)=\min(4,8)=4$。

到车站 $3$ 的花费最少时间的路径为乘坐从 $1$ 到 $3$ 的普通列车，花费的时间为 $4$。


到车站 $4$ 的花费最少时间的路径为乘坐从 $1$ 到 $3$ 的普通列车，花费的时间为 $4$，随后乘坐第 $3$ 条特快列车花费 $2$ 的时间从 $3$ 到 $4$，总花费时间为 $4+2=6$。


到车站 $5$ 的花费最少时间的路径为乘坐从 $1$ 到 $5$ 的普通列车，花费的时间为 $7$。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（10 分）：$n\le 1000$。
- 子任务 2（10 分）：$k=0$。
- 子任务 3（20 分）：$a_i=i$，$b_i=10^{18}$。
- 子任务 4（20 分）：$m=0$，$n \ge 2$，$c_{n-1}=d_{n-1}=0$，$c_n=d_n=2^k-1$。
- 子任务 5（20 分）：$n=m=2^k$。
- 子任务 6（20 分）：无特殊限制。

对于全部的数据，$1\le n\le 10^6$，$0\le m\le10^6$，$0\le k\le 14$，$0\le c_i,d_i< 2^k$，$0\le a_i,b_i,w_i\le 10^{18}$，$1\le u_i,v_i\le n$，$a$ 单调不降，$b$ 单调不升。


---

---
title: "玛丽卡"
layout: "post"
diff: 提高+/省选-
pid: P1186
tag: ['图论', '枚举', '最短路']
---
# 玛丽卡
## 题目描述

麦克找了个新女朋友，玛丽卡对他非常恼火并伺机报复。

因为她和他们不住在同一个城市，因此她开始准备她的长途旅行。

在这个国家中每两个城市之间最多只有一条路相通，并且我们知道从一个城市到另一个城市路上所需花费的时间。

麦克在车中无意中听到有一条路正在维修，并且那儿正堵车，但没听清楚到底是哪一条路。无论哪一条路正在维修，从玛丽卡所在的城市都能到达麦克所在的城市。

玛丽卡将只从不堵车的路上通过，并且她将按最短路线行车。麦克希望知道在最糟糕的情况下玛丽卡到达他所在的城市需要多长时间，这样他就能保证他的女朋友离开该城市足够远。

编写程序，帮助麦克找出玛丽卡按最短路线通过不堵车道路到达他所在城市所需的最长时间（用分钟表示）。

## 输入格式

第一行有两个用空格隔开的数 $N$ 和 $M$，分别表示城市的数量以及城市间道路的数量。$1 \le N \le 1000$，$1 \le M \le N \times (N - 1)/2$。城市用数字 $1 \sim N$ 标识，麦克在城市 $1$ 中，玛丽卡在城市 $N$ 中。  

接下来的 $M$ 行中每行包含三个用空格隔开的数 $A,B,V$。其中 $1 \le A, B \le N$，$1 \le V \le 1000$。这些数字表示在 $A$ 和城市 $B$ 中间有一条双行道，并且在 $V$ 分钟内就能通过。
## 输出格式

一行，写出用分钟表示的最长时间，在这段时间中，无论哪条路在堵车，玛丽卡应该能够到达麦克处，如果少于这个时间的话，则必定存在一条路，该条路一旦堵车，玛丽卡就不能够赶到麦克处。
## 样例

### 样例输入 #1
```
5 7
1 2 8
1 4 10
2 3 9
2 4 10
2 5 1
3 4 7
3 5 10

```
### 样例输出 #1
```
27
```
## 提示

感谢 Imakf 提供的三组 hack 数据。


---

---
title: "[CCC 2025 Senior] 熔岩路 / Floor is Lava"
layout: "post"
diff: 提高+/省选-
pid: P11860
tag: ['2025', 'CCC（加拿大）', '最短路']
---
# [CCC 2025 Senior] 熔岩路 / Floor is Lava
## 题目背景

译自 CCC 2025 Senior T4。本题满分为 $15$。

## 题目描述


你被困在一个炽热的地牢中。

地牢由 $n$ 个房间组成，房间编号 $1\sim n$。这些房间通过 $m$ 条**双向**隧道相连，第 $i$ 条**双向**隧道连接房间 $a_i$ 和 $b_i$，且地板被温度为 $c_i$ 的熔岩覆盖。  

为了穿越熔岩隧道，你穿着一双耐热靴子，初始**冷却等级**为 $0$。当你经过温度为 $c$ 的熔岩时，靴子的冷却等级必须**恰好**为 $c$，否则会被烫伤/冻伤。

幸运的是，当你站在一个房间里时，你可以调整靴子的冷却等级，每次增加或减少 $d$ 需要支付 $d$ 枚金币。  

你从房间 $1$ 出发，目标是到达房间 $n$。到出口所需的最小金币花费是多少？

## 输入格式


第一行，两个正整数 $n,m$。

接下来 $m$ 行，每行三个正整数 $a_i,b_i,c_i$。

数据保证：任意一对房间之间只有至多一条隧道，从房间 $1$ 可以到达任意一个其他的房间。
## 输出格式

输出一行一个非负整数，表示答案。

## 样例

### 样例输入 #1
```
5 7
1 2 3
2 3 2
1 3 6
3 4 3
4 5 7
2 4 1
2 5 10
```
### 样例输出 #1
```
9
```
## 提示


#### 样例解释



![](https://cdn.luogu.com.cn/upload/image_hosting/mpdmjywj.png)

地牢的构造如上图所示。

按照 $1\to 2\to 3\to 4\to 5$ 的路线花费为 $|3-0|+|2-3|+|3-2|+|4-3|=9$，可以证明是最优的。

#### 子任务

对于 $100\%$ 的数据，保证：

- $1\le n,m\le 2\times 10^5$；
- $1\le a_i,b_i\le n$；
- $a_i\neq b_i$；
- $1\le c_i\le 10^9$；
- 任意一对房间之间只有至多一条隧道;
- 从房间 $1$ 可以到达任意一个其他的房间。

---

- $\text{Subtask 0(0 points)}$：样例。
- $\text{Subtask 1(2 points)}$：$m=n-1$。
- $\text{Subtask 2(4 points)}$：$1\le c_i\le 10$。
- $\text{Subtask 3(4 points)}$：每个房间至多连着 $5$ 条隧道。
- $\text{Subtask 4(5 points)}$：无特殊限制。


---

---
title: "[蓝桥杯 2023 省 Java B] 魔法阵"
layout: "post"
diff: 提高+/省选-
pid: P12332
tag: ['动态规划 DP', '2023', '最短路', '蓝桥杯省赛']
---
# [蓝桥杯 2023 省 Java B] 魔法阵
## 题目描述

魔法师小蓝为了营救自己的朋友小 Q，来到了敌人布置的魔法阵。魔法阵可以看作是一幅具有 $N$ 个结点 $M$ 条边的无向图，结点编号为 $0, 1, 2, \dots, N-1$，图中没有重边和自环。敌人在每条边上都布置了陷阱，每条边都有一个伤害属性 $w$，每当小蓝经过一条边时就会受到这条边对应的 $w$ 的伤害。小蓝从结点 $0$ 出发，沿着边行走，想要到达结点 $N-1$ 营救小 $Q$。

小蓝有一种特殊的魔法可以使用，假设一条路径按照顺序依次经过了以下 $L$ 条边 $e_1, e_2, ..., e_L$（可以出现重复的边），那么期间小蓝受到的总伤害就是 $P = \displaystyle \sum_{i=1}^{L} w(e_i)$，$w(e_i)$ 表示边 $e_i$ 的伤害属性。如果 $L \geq K$，那么小蓝就可以从这 $L$ 条边当中选出连续出现的 $K$ 条边 $e_c, e_{c+1}, \dots, e_{c+K-1}$ 并免去在这 $K$ 条边行走期间所受到的伤害，即使用魔法之后路径总伤害变为 $P' = P - \displaystyle \sum_{i=c}^{c+K-1} w(e_i)$。注意必须恰好选出连续出现的 $K$ 条边，所以当 $L < K$ 时无法使用魔法。

小蓝最多只可以使用一次上述的魔法，请问从结点 $0$ 出发到结点 $N-1$ 受到的最小伤害是多少？题目保证至少存在一条从结点 $0$ 到 $N-1$ 的路径。
## 输入格式

第一行输入三个整数，$N, K, M$，用空格分隔。接下来 $M$ 行，每行包含三个整数 $u, v, w$，表示结点 $u$ 与结点 $v$ 之间存在一条伤害属性为 $w$ 的无向边。
## 输出格式

输出一行，包含一个整数，表示小蓝从结点 $0$ 到结点 $N-1$ 受到的最小伤害。
## 样例

### 样例输入 #1
```
4 2 3
0 1 2
1 2 1
2 3 4
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
2 5 1
0 1 1
```
### 样例输出 #2
```
0
```
## 提示

### 样例说明

- 样例 $1$，存在路径：$0 \rightarrow 1 \rightarrow 2 \rightarrow 3$，$K = 2$，如果在 $0 \rightarrow 1 \rightarrow 2$ 上使用魔法，那么答案就是 $0 + 0 + 4 = 4$；如果在 $1 \rightarrow 2 \rightarrow 3$ 上使用魔法，那么答案就是 $2 + 0 + 0 = 2$。再也找不到比 $2$ 还小的答案了，所以答案就是 $2$。
- 样例 $2$，存在路径：$0 \rightarrow 1 \rightarrow 0 \rightarrow 1 \rightarrow 0 \rightarrow 1$，$K = 5$，这条路径总计恰好走了 $5$ 条边，所以正好可以用魔法消除所有伤害，答案是 $0$。

### 评测用例规模与约定

- 对于 $30\%$ 的评测用例，$1 \leq N \leq 20$。
- 对于 $50\%$ 的评测用例，$1 \leq N \leq 100$。
- 对于 $100\%$ 的评测用例，$1 \leq N \leq 1000$，$1 \leq M \leq \frac{N \times (N - 1)}{2}$，$1 \leq K \leq 10$，$0 \leq u, v \leq N - 1$，$1 \leq w \leq 1000$。


---

---
title: "「CZOI-R3」数字变换"
layout: "post"
diff: 提高+/省选-
pid: P12407
tag: ['动态规划 DP', '图论', '洛谷原创', 'O2优化', '图论建模', '最短路', '洛谷比赛']
---
# 「CZOI-R3」数字变换
## 题目描述

你有一个长度为 $n$ 的序列 $x$ 和一个数 $a=p$。

序列 $x$ 的第 $i$ 个数具有一个花费序列 $w_{i,1},w_{i,2},\dots,w_{i,k}$。

你可以将 $a$ 变换成 $i$（$1\le i\le n$，$a$ 可以等于 $i$），**当前**是你的第 $j$ 次操作，则花费为 $w_{i,j} + 2\times(L-(x_a \mathbin{\&} x_i))$，其中 $\mathbin{\&}$ 是按位与，即 C++ 中的 `&`。

$L$ 是序列 $x$ 中所有数的最大值，即 $\max\limits_{1\le i\le n}x_i$。

你需要对所有 $1\le i\le n$ 求出**在第 $k$ 步操作结束时**将 $a$ 变成 $i$ 的**最小**花费。询问之间互相独立，每次询问不会影响其他次询问的答案。
## 输入格式

由于直接输入数据量过大，请使用以下方式读入数据：

第一行输入 $5$ 个整数 $n,p,k,c,seed$，其中 $c,seed$ 的意义在下文给出。

第二行输入 $c$ 个整数 $y_0,y_1,\dots,y_{c-1}$，其中 $y_i$ 的意义在下文给出。

读入后使用以下函数获得输入：

```cpp
int c, y[65536]; unsigned long long seed;
int get_rand(int mod)
{
    seed ^= seed << 14;
    seed ^= seed >> 7;
    seed ^= seed << 19;
    seed ^= seed << 23;
    return seed % mod;
}
void get_input()
{
    for (int i = 1; i <= n; i++) x[i] = y[get_rand(c)];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= k; j++) w[i][j] = get_rand(1000000);
}
```

你需要调用的是 `get_input` 函数。

**注意：此输入方式仅为减小输入量，标准解法并不依赖此输入方式。**
## 输出格式

共一行输出 $n$ 个正整数，第 $i$ 个表示将 $a$ 变成 $i$ 的最小花费。
## 样例

### 样例输入 #1
```
3 1 2 3 1025032617
1 2 3
```
### 样例输出 #1
```
730965 742898 1038257
```
## 提示

**【样例解释】**

$x = \{3, 1, 3\},w_1 = \{834731, 259456\},w_2 = \{471501, 271389\} ,w_3 = \{902700, 566748\},a=1,L=3$。

将 $a$ 变为 $2$ 的最优操作是第一次 $a\to 2$ 花费 $w_{2,1} + 2\times(3-3\& 1)= 471505$，第二次 $a\to 2$ 花费 $w_{2,2} + 2\times(3-1\& 1)= 271393$，总花费为 $742898$。

**【数据范围】**

- Subtask #1（$15\text{ pts}$）：$k = 1$，$x_i < 2^{12}$。
- Subtask #2（$25\text{ pts}$）：$c\le 10^3$（最多只有 $10^3$ 种不同的 $x_i$），$x_i < 2^{12}$。
- Subtask #3（$25\text{ pts}$）：$\max\{\text{popcount}(x_i)\} \le 5$。其中 $\text{popcount}(x_i)$ 表示 $x_i$ 在二进制下 $1$ 的个数。
- Subtask #4（$35\text{ pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 2 \times 10^5$，$1 \le k \le 10$，$0\le x_i<2^{16}$，$1 \le  p \le n$，$0\le w_{i,j}<10^6$。$1\le seed \le 2\times 10^9$，$1\le c \le 2^{16}$，$0 \le y_i < 2^{16}$。


---

---
title: "[GCJ 2012 Finals] Zombie Smash"
layout: "post"
diff: 提高+/省选-
pid: P13332
tag: ['图论', '2012', '最短路', 'Google Code Jam']
---
# [GCJ 2012 Finals] Zombie Smash
## 题目描述

You are playing Zombie Smash: a game where the objective is to smash zombies with your trusty Zombie Smasher as they pop out of graves at the graveyard. The graveyard is represented by a flat 2D grid. Each zombie will pop out of a grave at some $(X, Y)$ cell on the grid, stand in place for 1000 milliseconds (ms), and then disappear back into the grave. At most one zombie can stand around a grave at a time.

You can move to any one of the 8 cells adjacent to your location in 100ms; i.e., you can move North, East, South, West, NW, NE, SW, and SE of your current location. You may move through or stand on a cell even if it is currently occupied by a zombie. You can smash a zombie instantly once you reach the cell that the zombie is standing on, but once you smash a zombie it takes 750ms for your Zombie Smasher to recharge before you can smash another zombie. You may move around while Zombie Smasher is recharging. For example, immediately after smashing a zombie at $(0, 0)$:

* It will take 750ms to reach and smash a zombie at $(1, 1)$ or
* 2000ms to reach and smash a zombie at $(20, 20)$.

You start at cell $(0, 0)$ at the beginning of the game (time=0). After you play a level you would like to know how many zombies you could have smashed, if you had played optimally.

## 输入格式

The first line will contain a single integer $T$, the number of test cases. It is followed by $T$ test cases, each starting with a line containing a single integer $Z$, the number of zombies in the level.

The next $Z$ lines contain 3 space-separated integers each, representing the location and time at which a given zombie will appear and disappear. The $i^{th}$ line will contain the integers $X_i$, $Y_i$ and $M_i$, where:

* $X_i$ is the X coordinate of the cell at which zombie $i$ appears,
* $Y_i$ is the Y coordinate of the cell at which zombie $i$ appears,
* $M_i$ is the time at which zombie $i$ appears, in milliseconds after the beginning of the game. The time interval during which the zombie can smashed is inclusive: if you reach the cell at any time in the range $[M_i, M_i + 1000]$ with a charged Zombie Smasher, you can smash the zombie in that cell.

## 输出格式

For each test case, output one line containing "Case #$c$: $d$", where $c$ is the case number (starting from 1), and $d$ is the maximum number of zombies you could have smashed in this level.
## 样例

### 样例输入 #1
```
3
4
1 0 0
-1 0 0
10 10 1000
10 -10 1000
3
1 1 0
2 2 0
3 3 0
5
10 10 1000
-10 10 1000
10 -10 1000
-10 -10 1000
20 20 2000
```
### 样例输出 #1
```
Case #1: 3
Case #2: 2
Case #3: 2
```
## 提示

**Limits**

- $1 \leq T \leq 100.$
- $-1000 \leq X_i, Y_i \leq 1000.$
- $0 \leq M_i \leq 100000000 = 10^8.$
- Two zombies will never be in the same location at the same time. In other words, if one zombie appears at $(x, y)$ at time $t$, then any other zombie that appears at $(x, y)$ must appear at or before $(t - 1001)$, or at or after $(t + 1001)$.

**Test set 1 (7 Pts, Visible Verdict)**

- $1 \leq Z \leq 8.$

**Test set 2 (18 Pts, Hidden Verdict)**

- $1 \leq Z \leq 100.$



---

---
title: "[GCJ 2010 #3] Fence"
layout: "post"
diff: 提高+/省选-
pid: P13404
tag: ['2010', '广度优先搜索 BFS', '最短路', 'Google Code Jam']
---
# [GCJ 2010 #3] Fence
## 题目描述

We are looking into building a very long fence. We have already found a nice place to build it, and all that remains is to collect the materials.

From local hardware stores, we can buy unlimited numbers of wooden boards, each of which can come in a variety of different lengths. To avoid waste, we want to make sure that the total length of these boards is exactly equal to the length of the fence we are trying to build.

Given the length of the fence, and the possible board lengths that we can use, what is the minimum number of boards that we need to purchase in order to get exactly the right length?

Beware: the fence is going to be very long!
## 输入格式

The first line of the input file contains the number of cases, $T$. $T$ test cases follow.

Each test case consists of two lines. The first line contains space-separated integers $L$ and $N$. These represent the total length of the fence, and the number of different board lengths that can be purchased. The second line contains $N$ space-separated integers $B_1$, $B_2$, ..., $B_N$, representing all the possible board lengths.

## 输出格式

For each test case, output one line containing "Case #$x$: $M$", where $x$ is the case number (starting from 1) and $M$ is as follows:

- If it is possible to purchase one or more boards so that their total length is exactly equal to $L$, then $M$ should be the minimum number of boards required to do this.
- Otherwise, $M$ should be the string "IMPOSSIBLE".
## 样例

### 样例输入 #1
```
2
10000000001 3
23 51 100
10000000001 3
100 52 22
```
### 样例输出 #1
```
Case #1: 100000004
Case #2: IMPOSSIBLE
```
## 提示

**Sample Explanation**

In the first example, the optimal strategy is to use $2$ boards of length $23$, $5$ boards of length $51$, and $99999997$ boards of length $100$. Of course, you could use just $100000001$ boards of length $100$ to get a total greater than $L$, but that is not allowed.

In the second example, it is only possible to get even lengths.

**Limits**

- $1 \leq T \leq 50$.
- $10^{10} \leq L \leq 10^{18}$.
- $1 \leq N \leq 100$.

**Small dataset (7 Pts, Test set 1 - Visible)**

- $1 \leq B_i \leq 100$.

**Large dataset (22 Pts, Test set 2 - Hidden)**

$1 \leq B_i \leq 100000$.



---

---
title: "[GCJ 2008 #3] Portal"
layout: "post"
diff: 提高+/省选-
pid: P13471
tag: ['2008', '广度优先搜索 BFS', '最短路', 'Google Code Jam']
---
# [GCJ 2008 #3] Portal
## 题目描述

Portal$^{\text{TM}}$ is a first-person puzzle/platform game developed and published by Valve Software. The idea of the game was to create two portals on walls and then jump through one portal and come out the other. This problem has a similar idea but it does not assume you have played Portal.

For this problem you find yourself in a $R$ by $C$ grid. Additionally there is a delicious cake somewhere else in the grid. You're very hungry and wish to arrive at the cake with as few moves as possible. You can move north, south, east or west to an empty cell. Additionally, you have the ability to create portals on walls.

To help you get to the cake you have a portal gun which can shoot two types of portals, a yellow portal and a blue portal. A portal is created by shooting your portal gun either north, south, east or west. This emits a ball of energy that creates a portal on the first wall it hits. Note that for this problem shooting the portal gun does not count as a move. If you fire your portal gun at the cake, the energy ball will go right through it.

After creating a yellow portal and a blue portal, you can move through the yellow portal to arrive at the blue portal or vice versa. Using these portals you may be able to reach the cake even faster! You can only use portals after you create both a yellow and a blue portal.

Consider the following grid:

![](https://cdn.luogu.com.cn/upload/image_hosting/tz8ceyn5.png)

Gray cells represent walls, white cells represent empty cells, and the red circle indicates your position.

Suppose you shoot a blue portal east. The portal is created on the first wall it hits, resulting in:

![](https://cdn.luogu.com.cn/upload/image_hosting/rzvxatnz.png)

Now suppose you shoot a yellow portal south:

![](https://cdn.luogu.com.cn/upload/image_hosting/b3pvr2mg.png)

Next you move south once:

![](https://cdn.luogu.com.cn/upload/image_hosting/4ogui6pq.png)

Now comes the interesting part. If you move south one more time you go through the yellow portal to the blue portal:

![](https://cdn.luogu.com.cn/upload/image_hosting/k1k8ybii.png)

There can only be one yellow portal and one blue portal at any time. For example if you attempt to create a blue portal to the west the other blue portal will disappear:

![](https://cdn.luogu.com.cn/upload/image_hosting/u3zzj14r.png)

A portal disappears only when another portal of the same color is fired.

Note that the portals are created on one side of the wall. If a wall has a portal on its east side you must move into the wall from the east to go through the portal. Otherwise you'll be moving into a wall, which is improbable.

Finally, you may not put two portals on top of each other. If you try to fire a portal at a side of a wall that already has a portal, the second portal will fail to form.

Given the maze, your initial position, and the cake's position, you want to find the minimum number of moves needed to reach the cake if it is possible. Remember that shooting the portal gun does not count as a move.
## 输入格式

The first line of input gives the number of cases, $N$. $N$ test cases follow.

The first line of each test case will contain the integers $R$ and $C$ separated by a space. $R$ lines follow containing $C$ characters each, representing the map:

* . indicates an empty cell;
* \# indicates a wall;
* o indicates your starting position; and
* x indicates the cake's position.

There will be exactly one o and one x character per case.

Cells outside of the grid are all walls and you may use them to create portals.
## 输出格式

For each test case you should output one line containing "Case #$X$: $Y$" (quotes for clarity) where $X$ is the number of the test case and $Y$ is the minimum number of moves needed to reach the cake or "THE CAKE IS A LIE" (quotes for clarity) if the cake cannot be reached.
## 样例

### 样例输入 #1
```
3
4 7
.O..##.
.#.....
.#.####
.#...X.
5 5
O....
.....
.....
.....
....X
1 3
O#X
```
### 样例输出 #1
```
Case #1: 4
Case #2: 2
Case #3: THE CAKE IS A LIE
```
## 提示

**Sample Explanation**

Here is the sequence of moves for the first case (note that shooting the portal gun does not count as a move):

- Move one step east.
- Shoot a blue portal north.
- Shoot a yellow portal south.
- Move one step north through the blue portal.
- Shoot a blue portal east.
- Move one step south through the yellow portal.
- Move one step west.
- Eat your delicious and moist cake.

Portal$^{\text{TM}}$ is a trademark of Valve Inc. Valve Inc. does not endorse and has no involvement with Google Code Jam.

**Small dataset (10 Pts, Test set 1 - Visible)**

- $N=200$
- $1 \leqslant R, C \leqslant 8$

**Large dataset (15 Pts, Test set 2 - Hidden)**

- $N=50$
- $1 \leqslant R, C \leqslant 15$



---

---
title: "[KOI 2025 #1] 木槿花开了"
layout: "post"
diff: 提高+/省选-
pid: P13515
tag: ['2025', '最短路', 'KOI（韩国）']
---
# [KOI 2025 #1] 木槿花开了
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

KOI 村庄由 $N$ 个建筑和 $M$ 条道路组成。

建筑从 1 到 $N$ 编号，每个建筑可能有也可能没有窗户。对于 $1 \le i \le N$ 的每个 $i$，如果第 $i$ 个建筑有窗户，则 $c_i=1$，如果没有窗户，则 $c_i=0$。规定第 1 个建筑和第 $N$ 个建筑没有窗户，即 $c_1 = c_N = 0$。

道路从 1 到 $M$ 编号，每条道路都是连接一个起始建筑和一个到达建筑的单向通道。对于 $1 \le j \le M$ 的每个 $j$，第 $j$ 条道路从建筑 $x_j$ 开始，到建筑 $y_j$ 结束，通过这条道路需要花费恰好 $t_j$ 秒。因为是单向道路，所以不能逆向行驶（即，从建筑 $y_j$ 移动到建筑 $x_j$）。

在 KOI 村庄，Hankook 和 Jeong-ul 打算玩一个基于“木槿花开了”游戏改编的以下游戏。

游戏开始时，Jeong-ul 在 1 号建筑。Jeong-ul 的目标是在不被 Hankook 的视线发现一次的情况下，尽可能快地到达 $N$ 号建筑。相反，Hankook 的目标是在 Jeong-ul 到达 $N$ 号建筑之前找到他。

Hankook 睁着眼时可以看到整个 KOI 村庄，但无法看到没有窗户的建筑内部。也就是说，Hankook 只能看到有窗户的建筑内部和所有道路。

Hankook 从游戏开始（0 秒）时起，周期性地重复以下动作：
*   首先，闭上眼睛恰好 $a$ 秒。
*   紧接着，睁开眼睛并观察村庄恰好 $b$ 秒。
*   此过程无限重复。

我们可以将上述过程用数学公式严格地表达如下：
*   我们定义“从游戏开始时经过的时间”为 $t$（以秒为单位）。
*   当时间 $t = k(a+b) + l$ 时（其中 $k$ 为非负整数， $l$ 为满足 $0 \le l < a+b$ 的实数）：
    *   如果 $0 \le l < a$，Hankook 闭着眼睛。
    *   如果 $a \le l < a+b$，Hankook 睁着眼睛。
*   也就是说，对于非负整数 $k$，Hankook 闭眼的时间是闭区间 $[k(a+b), k(a+b)+a]$，睁眼的时间是开区间 $(k(a+b)+a, (k+1)(a+b))$。

Jeong-ul 从游戏开始的时刻（0 秒）起，可以随时开始移动，并且在建筑内部（无论是否有窗户）等待和移动都是自由的，不消耗时间。从建筑出来或进入建筑内部也不消耗时间。如果 Jeong-ul 开始沿着某条道路移动，他必须花费该道路所需的确切时间来移动，并且在移动过程中不能在道路上停下或等待。移动结束后，他将到达道路的终点建筑。

Jeong-ul 被 Hankook 发现的基准如下：
*   在 Hankook 睁着眼的时候，如果 Jeong-ul 位于道路上或在有窗户的建筑内部，他会立即被发现，游戏随之结束。因此，在 Hankook 睁着眼的时间段内，Jeong-ul 必须位于没有窗户的建筑内。
*   在 Hankook 闭着眼的时候，无论 Jeong-ul 在哪里，都绝对不会被发现。
*   请注意，如果 Jeong-ul 进入没有窗户的建筑的时刻，恰好是 Hankook 开始睁眼的瞬间；或者他进入道路开始移动的时刻，恰好是 Hankook 开始闭眼的瞬间，则不会被发现。

在这些条件下，请编写一个程序，判断 Jeong-ul 是否有可能在不被 Hankook 发现一次的情况下安全到达 $N$ 号建筑，如果可能，计算 Jeong-ul 到达 $N$ 号建筑所需的最短时间（以秒为单位）。
## 输入格式

第一行给出两个整数 $N$ 和 $M$，以空格分隔。

接下来的 $M$ 行给出道路的信息。其中第 $j$ ($1 \le j \le M$) 行包含三个整数 $x_j, y_j, t_j$，以空格分隔。

再下一行给出 $N$ 个整数 $c_1, c_2, \cdots, c_N$，以空格分隔。

最后一行给出两个整数 $a, b$，以空格分隔。
## 输出格式

如果无论 Jeong-ul 如何移动都无法到达 $N$ 号建筑，则输出 `-1`。

否则，输出 Jeong-ul 到达 $N$ 号建筑所需的最短时间（以秒为单位）。可以证明，这个值总是一个整数。
## 样例

### 样例输入 #1
```
4 4
1 2 3
1 3 4
2 4 3
3 4 1
0 0 0 0
3 8
```
### 样例输出 #1
```
14
```
### 样例输入 #2
```
4 4
1 2 3
1 3 4
2 4 3
3 4 1
0 1 1 0
3 8
```
### 样例输出 #2
```
-1
```
## 提示

### 样例 1 解释

随着时间的推移，Jeong-ul 和 Hankook 可以按如下方式行动：

*   0 秒 - 3 秒：Hankook 闭着眼睛。Jeong-ul 在 0 秒时进入 1 号道路（1 号建筑 → 2 号建筑），并于 3 秒时到达 2 号建筑。
*   3 秒 - 11 秒：Hankook 在 3 秒时睁开眼睛。Jeong-ul 在 2 号建筑一直停留到 11 秒。
*   11 秒 - 14 秒：Hankook 在 11 秒时闭上眼睛。Jeong-ul 在 11 秒时进入 3 号道路（2 号建筑 → 4 号建筑），并于 14 秒时到达 4 号建筑。

由于 Jeong-ul 没有比 14 秒更快到达 4 号建筑的方法，因此应当输出 14。

### 样例 2 解释

由于除 1 号和 4 号建筑外的所有建筑都有窗户，Jeong-ul 必须在 Hankook 睁开眼睛之前（即，在 $a=3$ 秒内）到达 4 号建筑。但是，Jeong-ul 不可能在 3 秒内到达 4 号建筑。因此，应当输出 `-1`。

### 限制条件

*   给定的所有数都是整数。
*   $3 \le N \le 2000$
*   $3 \le M \le 4000$
*   对于每个 $1 \le j \le M$ 的 $j$，有 $1 \le x_j, y_j \le N, x_j \ne y_j, 1 \le t_j \le 100,000$。
*   对于 $1 \le j < k \le M$ 的任意 $j, k$，有 $(x_j, y_j) \ne (x_k, y_k)$。也就是说，所有道路的起点和终点对都是唯一的。
*   对于 $2 \le i \le N-1$ 的每个 $i$，$c_i \in \{0, 1\}$。
*   $c_1 = c_N = 0$。即，1 号建筑和 $N$ 号建筑没有窗户。
*   $1 \le a, b \le 10^9$。

### 子任务

1.  (12 分) $N \le 5, M \le 10$。
2.  (19 分) 对于 $2 \le i \le N-1$ 的每个 $i$，$c_i=1$。
3.  (31 分) 对于 $1 \le j \le M$ 的每个 $j$，$t_j=1$。
4.  (27 分) $M=N-1$。并且，对于 $1 \le j \le N-1$ 的每个 $j$，$x_j = j, y_j = j+1$。
5.  (61 分) 无附加限制条件。


---

---
title: "[OOI 2023] The way home / 回家的路"
layout: "post"
diff: 提高+/省选-
pid: P13534
tag: ['动态规划 DP', '2023', '最短路', 'Moscow Olympiad']
---
# [OOI 2023] The way home / 回家的路
## 题目背景

CF1801D
## 题目描述

著名魔术师博里斯·布迪尼在 X 国旅行，这个国家共有 $n$ 个城市。不幸的是，他在编号为 $1$ 的城市遭遇了盗窃。现在，布迪尼需要踏上回家的旅程，目标是回到编号为 $n$ 的城市。

他打算乘坐飞机返家。全国共有 $m$ 个航班，第 $i$ 个航班从城市 $a_i$ 飞往城市 $b_i$，票价为 $s_i$ 卢布。要搭乘某个航班，布迪尼必须身处起点城市 $a_i$，并且手中至少有 $s_i$ 卢布（这些钱在登机时会被扣除）。

被盗后，他仅剩 $p$ 卢布。但他并未气馁！在任意城市 $i$，他都可以随时举办魔术表演，每场表演能赚 $w_i$ 卢布。

请帮助布迪尼判断，他是否能够回到家乡。如果可以，求出他至少需要举办多少场表演。
## 输入格式

第一行包含四个整数 $n$、$m$、$p$ 和 $g$（$2 \le n \le 800$，$1 \le m \le 3000$，$0 \le p \le 10^9$，$0 \le g \le 6$），分别表示城市数量、航班数量、初始卢布数和测试组编号。

第二行包含 $n$ 个整数 $w_1, w_2, \ldots, w_n$（$1 \le w_i \le 10^9$），表示在每个城市举办一场表演能获得的收入。

接下来 $m$ 行，每行三个整数 $a_i$、$b_i$ 和 $s_i$（$1 \le a_i, b_i \le n$，$1 \le s_i \le 10^9$），表示第 $i$ 个航班的起点、终点和票价。

## 输出格式

输出一个整数，表示布迪尼至少需要举办的表演场数。如果无法回家，输出 $-1$。

## 样例

### 样例输入 #1
```
4 4 2 0
7 4 3 1
1 2 21
3 2 6
1 3 8
2 4 11
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
4 4 10 0
1 2 10 1
1 2 20
2 4 30
1 3 25
3 4 89
```
### 样例输出 #2
```
24
```
### 样例输入 #3
```
4 4 7 0
5 1 6 2
1 2 5
2 3 10
3 4 50
3 4 70
```
### 样例输出 #3
```
10
```
### 样例输入 #4
```
4 1 2 0
1 1 1 1
1 3 2
```
### 样例输出 #4
```
-1
```
## 提示

### 样例解释

在第一个样例中，布迪尼最优策略是在第一个城市举办 $4$ 场表演，此时他共有 $2 + 7 \times 4 = 30$ 卢布，然后依次乘坐 $1 \to 3 \to 2 \to 4$ 的航班，花费 $6 + 8 + 11 = 25$ 卢布。

在第二个样例中，布迪尼最优策略是在第一个城市举办 $15$ 场表演，飞到第 $3$ 个城市后再举办 $9$ 场表演，然后前往第 $4$ 个城市。

### 评分说明

本题测试数据分为 6 组。只有通过某一组的全部测试点，且通过部分之前组的全部测试点后，才能获得该组分数。有些分组不要求通过样例测试点。**离线评测**表示该组的测试结果会在比赛结束后公布。

| 组别 | 分值 | $n$ | $m$ | $s_i$ | $w_i$ | 必须通过的组 | 备注 |
|:----:|:----:|:---:|:---:|:-----:|:-----:|:------------:|:----:|
| 0    | 0    | --  | --  | --    | --    | --           | 样例测试点 |
| 1    | 14   | --  | --  | --    | $w_i=1$ | --        |        |
| 2    | 13   | --  | $m = n - 1$ | --    | --    | --           | $a_i = i$，$b_i = i + 1$ |
| 3    | 17   | $n \le 10$ | --  | --    | --    | 0            |        |
| 4    | 19   | $n \le 100$ | -- | $s_i \le 100$ | -- | 0        |        |
| 5    | 21   | $n \le 100$ | -- | --    | --    | 0, 3, 4      |        |
| 6    | 16   | --  | --  | --    | --    | 0--5         | **离线评测** |


---

---
title: "「WWOI R1」WSM 游戏"
layout: "post"
diff: 提高+/省选-
pid: P13563
tag: ['O2优化', '广度优先搜索 BFS', '最短路', '状压 DP']
---
# 「WWOI R1」WSM 游戏
## 题目背景

[$\texttt{WSM}$](https://gitblock.cn/Projects/769996) 是一款冒险游戏，WSM 是这个游戏的主角。
## 题目描述

有一个由 $n$ 行 $m$ 列格子构成的地图。WSM 要从地图的左上角坐标为 $(1,1)$ 的格子出发，到达坐标为 $(a,b)$ 的格子。 

地图上有 $k$ 个带有密码的锁和 $t$ 个带有密码的钥匙。  
当 WSM 到达密码为 $r$ 的钥匙所在的格子，密码为 $r$ 的锁就会立刻消失。     
任何一个时刻，WSM 都必须在地图内，且所处的格子必须**没有锁**。  
如果某个格子中既有密码为 $r$ 的锁又有密码为 $r$ 的钥匙，那么 WSM 可以进入到这个格子。  

地图上还存在着 $p$ 个普通道具和 $q$ 个魔法物品。WSM 可以消耗步数来使用地图上的普通道具和魔法物品。所有的道具和魔法物品均可重复使用。  

---

道具很原始，WSM 只能使用和自己在同一格的道具。  
假设 WSM 当前位置为 $(x,y)$，使用道具后移动到 $(x',y')$。  
|道具编号|移动后位置|
|:-:|:-:|
$1$|WSM 向上走一格，即 $(x',y')=(x-1,y)$|
$2$|WSM 向下走一格，即 $(x',y')=(x+1,y)$|
$3$|WSM 向左走一格，即 $(x',y')=(x,y-1)$|
$4$|WSM 向右走一格，即 $(x',y')=(x,y+1)$|

---

魔法物品很脆弱，当 WSM 和某一个魔法物品处在同一格时，这个魔法物品会**永久消失**。   
魔法物品很强大，WSM 可以使用地图上任意一个魔法物品。  
假设 WSM 当前位置为 $(x,y)$，魔法物品的位置为 $(x_0,y_0)$，使用魔法物品后移动到 $(x',y')$。  
|魔法物品编号|移动后位置|
|:-:|:-:|
$1$|$\frac{x+x'}{2}=x_0$，$\frac{y+y'}{2}=y_0$|
$2$|$x'=x$，$\frac{y+y'}{2}=y_0$|
$3$|$\frac{x+x'}{2}=x_0$，$y'=y$|


WSM 每一步可以使用一个道具或一个魔法物品。请问至少需要多少步才能从坐标为 $(1,1)$ 的格子到达坐标为 $(a,b)$ 的格子？
## 输入格式

第一行输入四个整数 $n,m,a,b$。  
第二行输入四个整数 $k,t,p,q$。  
接下来 $k$ 行，每行输入三个整数 $x,y,r$，表示坐标 $(x,y)$ 的格子上有密码为 $r$ 的锁。  
接下来 $t$ 行，每行输入三个整数 $x,y,r$，表示坐标 $(x,y)$ 的格子上有密码为 $r$ 的钥匙。  
接下来 $p$ 行，每行输入三个整数 $x,y,id$，表示坐标 $(x,y)$ 的格子上有编号为 $id$ 的道具。  
接下来 $q$ 行，每行输入三个整数 $x,y,id$，表示坐标 $(x,y)$ 的格子上有编号为 $id$ 的魔法物品。
## 输出格式

输出一个整数，表示 WSM 所需的最小步数，如果无法到达则输出 `-1`。
## 样例

### 样例输入 #1
```
2 2 2 2
0 0 8 0
1 2 4
1 1 2
2 2 1
1 1 4
2 2 4
2 1 4
1 2 3
2 1 1
```
### 样例输出 #1
```
2
```
## 提示

### 【样例 $1$ 解释】
  
花费最小步数的路线为：

$\def\f#1{\xrightarrow{\bf 道具#1}} (1,1) \f{2} (2,1) \f{4} (2,2)$。


### 【数据范围】

**本题采用捆绑测试。**

请注意：任意一个格子内可能**同时存在**多个锁、钥匙、道具和魔法道具。

对于所有测试数据，保证：
* $1\le n,m\le400$，$1\le a\le n$，$1\le b\le m$。
* $1\le k \le 10^3$，$0\le t\le 3$，$1\le p\le 5\times 10^5$，$0\le q\le 3$。
* 对于所有的锁、钥匙、道具、魔法物品，均有 $1\le x\le n$，$1\le y\le m$。
* 对于所有的锁，均有 $1\le r\le 10^9$。
* 对于所有的钥匙，均有 $1\le r\le 10^9$。
* 对于所有的道具，均有 $id\in\{1,2,3,4\}$。
* 对于所有的魔法物品，均有 $id\in\{1,2,3\}$。

| 子任务编号 |$n,m\le$|$k\le$|$t\le$|$p\le$|$q\le$|分数|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$2$|$0$|$0$|$13$|$0$|$10$|
|$2$|$10$|^|^|$300$|$3$|$10$|
|$3$|^|$100$|$3$|^|^|$20$|
|$4$|$400$|$0$|$0$|$5\times10^5$|$0$|$10$|
|$5$|^|$3$|$3$|^|$3$|$25$|
|$6$|^|$10^3$|^|^|^|$25$|


---

---
title: "集合位置"
layout: "post"
diff: 提高+/省选-
pid: P1491
tag: ['图论', '优先队列', '最短路']
---
# 集合位置
## 题目描述

每次有大的活动，大家都要在一起“聚一聚”，不管是去好乐迪，还是避风塘，或者汤姆熊，大家都要玩的痛快。还记得心语和花儿在跳舞机上的激情与释放，还记得草草的投篮技艺是如此的高超，还记得狗狗的枪法永远是 S ……还有不能忘了，胖子的歌声永远是让我们惊叫的！！

今天是野猫的生日，所以想到这些也正常，只是因为是上学日，没法一起去玩了。但回忆一下那时的甜蜜总是一种幸福嘛。。。

但是每次集合的时候都会出现问题！野猫是公认的“路盲”，野猫自己心里也很清楚，每次都提前出门，但还是经常迟到，这点让大家很是无奈。后来，野猫在每次出门前，都会向花儿咨询一下路径，根据已知的路径中，总算能按时到了。

现在提出这样的一个问题：给出 $n$ 个点的坐标，其中第一个为野猫的出发位置，最后一个为大家的集合位置，并给出哪些位置点是相连的。野猫从出发点到达集合点，总会挑一条最近的路走，如果野猫没找到最近的路，他就会走第二近的路。请帮野猫求一下这条第二最短路径长度。

特别地，选取的第二短路径**不会重复经过同一条路**，即使可能重复走过同一条路多次路程会更短。
## 输入格式

第一行是两个整数 $n(1 \le n \le 200)$ 和 $m(1 \le m\le 10000)$，表示一共有 $n$ 个点和 $m$ 条路，以下 $n$ 行每行两个数 $x_i$，$y_i$，$(-500 \le x_i,y_i \le 500),$ 代表第 $i$ 个点的坐标，再往下的 $m$ 行每行两个整数 $p_j$，$q_j,(1 \le p_j,q_j \le n)$，表示两个点之间有一条路，数据没有重边，**可能有自环**。
## 输出格式

只有一行包含一个数，为第二最短路线的距离（保留两位小数），如果存在多条第一短路径，则答案就是第一最短路径的长度；如果不存在第二最短路径，输出 `-1`。
## 样例

### 样例输入 #1
```
3 3

0 0

1 1

0 2

1 2

1 3

2 3


```
### 样例输出 #1
```
2.83
```


---

---
title: "跑路"
layout: "post"
diff: 提高+/省选-
pid: P1613
tag: ['动态规划 DP', '倍增', '最短路']
---
# 跑路
## 题目描述

小 A 的工作不仅繁琐，更有苛刻的规定，要求小 A 每天早上在 $6:00$ 之前到达公司，否则这个月工资清零。可是小 A 偏偏又有赖床的坏毛病。于是为了保住自己的工资，小 A 买了一个空间跑路器，每秒钟可以跑 $2^k$ 千米（$k$ 是任意自然数）。当然，这个机器是用 `longint` 存的，所以总跑路长度不能超过 `maxlongint` 千米。小 A 的家到公司的路可以看做一个有向图，小 A 家为点 $1$，公司为点 $n$，每条边长度均为一千米。小 A 想每天能醒地尽量晚，所以让你帮他算算，他最少需要几秒才能到公司。数据保证 $1$ 到 $n$ 至少有一条路径。
## 输入格式

第一行两个整数 $n,m$，表示点的个数和边的个数。

接下来 $m$ 行每行两个数字 $u,v$，表示一条 $u$ 到 $v$ 的边。
## 输出格式

一行一个数字，表示到公司的最少秒数。
## 样例

### 样例输入 #1
```
4 4
1 1
1 2
2 3
3 4

```
### 样例输出 #1
```
1
```
## 提示

**【样例解释】**

$1 \to 1 \to 2 \to 3 \to 4$，总路径长度为 $4$ 千米，直接使用一次跑路器即可。

**【数据范围】**

$50\%$ 的数据满足最优解路径长度 $\leq 1000$；

$100\%$ 的数据满足 $2\leq n \leq 50$，$m \leq 10 ^ 4$，最优解路径长度 $\leq$ `maxlongint`。


---

---
title: "[ZJOI2006] 物流运输"
layout: "post"
diff: 提高+/省选-
pid: P1772
tag: ['动态规划 DP', '图论', '2006', '各省省选', '浙江', 'NOI 导刊', '最短路']
---
# [ZJOI2006] 物流运输
## 题目描述

物流公司要把一批货物从码头 A 运到码头 B。由于货物量比较大，需要 $n$ 天才能运完。货物运输过程中一般要转停好几个码头。  

物流公司通常会设计一条固定的运输路线，以便对整个运输过程实施严格的管理和跟踪。由于各种因素的存在，有的时候某个码头会无法装卸货物。这时候就必须修改运输路线，让货物能够按时到达目的地。  

但是修改路线是—件十分麻烦的事情，会带来额外的成本。因此物流公司希望能够订一个 $n$ 天的运输计划，使得总成本尽可能地小。

## 输入格式

第一行是四个整数 $n,m,k,e$。$n$ 表示货物运输所需天数，$m$ 表示码头总数，$k$ 表示每次修改运输路线所需成本，$e$ 表示航线条数。  

接下来 $e$ 行每行是一条航线描述，包括了三个整数，依次表示航线连接的两个码头编号以及航线长度。其中码头 A 编号为 $1$，码头 B 编号为 $m$。单位长度的运输费用为 $1$。航线是**双向**的。  

再接下来一行是一个整数 $d$，后面的 $d$ 行每行是三个整数 $p,a,b$。表示编号为 $p$ 的码头在 $[a,b]$ 天之内无法装卸货物。同一个码头有可能在多个时间段内不可用。但任何时间都存在至少一条从码头 A 到码头 B 的运输路线。

## 输出格式

包括了一个整数表示最小的总成本。  
总成本为 $n$ 天运输路线长度之和 $+ k \times$ 改变运输路线的次数。

## 样例

### 样例输入 #1
```
  5 5 10 8
  1 2 1
  1 3 3
  1 4 2
  2 3 2
  2 4 4
  3 4 1
  3 5 2
  4 5 2
  4
  2 2 3
  3 1 1
  3 3 3
  4 4 5

```
### 样例输出 #1
```
32
```
## 提示

【数据范围】
对于 $100\%$ 的数据，$1 \le n \le 100$，$1\le m \le 20$, $1 \le k \le 500$, $1 \le e \le 200$。

【样例输入说明】

![](https://cdn.luogu.com.cn/upload/image_hosting/4lcnync6.png)

上图依次表示第 $1$ 至第 $5$ 天的情况，阴影表示不可用的码头。

【样例输出说明】

前三天走 $1 \to 4 \to 5$，后两天走 $1 \to 3 \to 5$，这样总成本为 $(2+2)\times 3+(3+2)\times 2+10=32$。

\_NOI导刊2010提高（01）



---

---
title: "海滩防御"
layout: "post"
diff: 提高+/省选-
pid: P1783
tag: ['图论', '二分', '并查集', '最短路']
---
# 海滩防御
## 题目描述

WLP 同学最近迷上了一款网络联机对战游戏（终于知道为毛 JOHNKRAM 每天刷洛谷效率那么低了），但是他却为了这个游戏很苦恼，因为他在海边的造船厂和仓库总是被敌方派人偷袭。于是，WLP 动用了他那丰满且充实的大脑（或许更偏向前者），想出了一个好主意，他把海滩分成垂直于海岸线的若干列，在其中的几列上放置几个信号塔，试图来监视整个海滩。然而，WLP 是一个非常心急的人，他把信号塔建好后才发现还需给信号塔供能，它们才能投入使用（这不是废话么），它们都有一个工作半径，一个圆形区域里的所有敌人都逃不过它们的监视，不过，WLP 发现，敌人们非常狡猾，除非他将道路完全封死，否则 WLP 的敌人可以走过一条任意弯曲的路（不一定走整点，但是不会出第 $0$ 列和第 $N$ 列构成的边界）来偷他的东西。

于是，WLP 就思考了：到底需要给每个信号塔多大的工作半径，才能将从海滩到内地的路径完全封死呢？他再次动用了他那丰满且充实的大脑，想了一堂数学课，终于，还是没想出来。于是，他向 LZZ 神犇求助（额…… CSUNSHINE 的身份是不是暴露了）。

终于，在 WLP：“ %^!\*@#!\*(\*^!\*#@\$^&（此处省略无数卖萌场景）”的哀求下，LZZ 神犇写了一个程序，在一秒内就解决了问题。但是，邪恶的 LZZ 神犇决定要将这个难题共享给无数无辜的 OIer，所以，现在轮到你了。
## 输入格式

第一行两个整数 $N$ 和 $M$，表示海滩被 WLP 分成的列数 $0,1,2,\cdots,N$ 和信号塔个数。

第 $2$ 至第 $M+1$ 行，每行两个数 $X_i$，$Y_i$ 表示 $1,2,3,\cdots,M$ 号信号塔所在的列数和离开海滩的距离。
## 输出格式

一行一个实数，表示最小的工作半径，保留两位小数。

## 样例

### 样例输入 #1
```
5 5
1 5
3 5
5 5
4 30
2 15
```
### 样例输出 #1
```
1.00
```
### 样例输入 #2
```
100 2
30 50
90 100
```
### 样例输出 #2
```
39.05
```
## 提示

### 数据范围及约定

- 对于 $10\%$ 的数据：$1 \le M \le 10$，$1 \le Y_i \le 100$；
- 对于 $30\%$ 的数据：$1 \le M \le 50$，$1 \le Y_i \le 1,000$；
- 对于 $80\%$ 的数据：$1 \le M \le 500$，$1 \le Y_i \le 1,000$；
- 对于 $100\%$ 的数据：$1 \le M \le 800$，$1 \le N \le 1000$，$1 \le X_i \le N$，$1 \le Y_i \le 100,000$。

### 提示

注意，封锁海滩是指，敌人的深入程度是有限制的，若敌人绕过了所有的信号塔，并且可以长驱直入，那么就说明道路没有完全封锁。


---

---
title: "[USACO3.3] 亚瑟王的宫殿"
layout: "post"
diff: 提高+/省选-
pid: P1930
tag: ['搜索', 'USACO', '枚举', '广度优先搜索 BFS', '最短路']
---
# [USACO3.3] 亚瑟王的宫殿
## 题目描述

很久以前，亚瑟王和他的骑士习惯每年元旦去庆祝他们的友谊。为了纪念上述事件， 我们把这些故事看作是一个棋盘游戏。有一个国王和若干个骑士被放置在一个由许多方格 组成的棋盘上，没有两个骑士在同一个方格内。

这个例子是标准的 $8\times 8$ 棋盘。

![](https://cdn.luogu.com.cn/upload/image_hosting/bvjh9o2q.png)

国王可以移动到任何一个相邻的方格，从下图中黑子位置到下图中白子位置前提是他 不掉出棋盘之外。

![](https://cdn.luogu.com.cn/upload/image_hosting/joj1exif.png)

一个骑士可以从下图中黑子位置移动到下图中白子位置(走“日”字形） 但前提是他 不掉出棋盘之外。

![](https://cdn.luogu.com.cn/upload/image_hosting/vf9vuque.png)

在游戏中，玩家可在每个方格上放不止一个棋子，假定方格足够大，任何棋子都不会 阻碍到其他棋子正常行动。

玩家的任务就是把所有的棋子移动到同一个方格里——用最小的步数。为了完成这个 任务，他必须按照上面所说的规则去移动棋子。另外，玩家可以选择一个骑士跟国王从他们两个相遇的那个点开始一起行动，这时他们按照骑士的行动规则行动，其他的单独骑士则自己一直走到集中点。骑士和国王一起走的时候，只算一个人走的步数。

请计算他们集中在一起的最小步数，而且玩家必须自己找出这个集中点。当然，这些 棋子可以在棋盘的任何地方集合。

## 输入格式

第一行：两个用空格隔开的整数：$R,C$ 分别为棋盘行和列的长。不超过 $26$ 列，$40$ 行。

第二行到结尾：输入文件包含了一些有空格隔开的字母 / 数字对，一行有一个或以上。第一对为国王的位置，接下来是骑士的位置。可能没有骑士，也可能整个棋盘都是骑士。行从 $1$ 开始，列从大写字母 $A$ 开始。
## 输出格式

单独一行表示棋子集中在一个方格的最小步数。

## 样例

### 样例输入 #1
```
8 8
D 4 
A 3 A 8 
H 1 H 8 

```
### 样例输出 #1
```
10
```
## 提示

### 样例解释

他们集中在 $\tt B5$。

- 骑士 $1$：$\tt A3\to B5$（$1$ 步）。
- 骑士 $2$：$\tt A8\to C7\to B5$（$2$ 步）。
- 骑士 $3$：$\tt H1\to G3\to F5\to D4$，此时国王开始与这个骑士一起走，$\to \tt B5$（$4$ 步）
- 骑士 $4$：$\tt H8\to F7\to D6\to B5$（$3$ 步）。

$1+2+4+3=10$ 步。

题目翻译来自 NOCOW。

USACO Training Section 3.3


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
title: "[国家集训队] 墨墨的等式"
layout: "post"
diff: 提高+/省选-
pid: P2371
tag: ['图论', '集训队互测', '最短路']
---
# [国家集训队] 墨墨的等式
## 题目描述

墨墨突然对等式很感兴趣，他正在研究 $\sum_{i=1}^n a_ix_i=b$ 存在非负整数解的条件，他要求你编写一个程序，给定 $n, a_{1\dots n}, l, r$，求出有多少 $b\in[l,r]$ 可以使等式存在非负整数解。
## 输入格式

第一行三个整数 $n,l,r$。

第二行 $n$ 个整数 $a_{1\dots n}$。

## 输出格式

一行一个整数，表示有多少 $b\in[l,r]$ 可以使等式存在非负整数解。

## 样例

### 样例输入 #1
```
2 5 10
3 5

```
### 样例输出 #1
```
5

```
## 提示

对于 $20\%$ 的数据，$n \le 5$，$r \le 10$。

对于 $40\%$ 的数据，$n \le 10$，$r \le 10^6$。

对于 $100\%$ 的数据，$n \le 12$，$0 \le a_i \le 5\times 10^5$，$1 \le l \le r \le 10^{12}$。



---

---
title: "[SDOI2009] 地图复原"
layout: "post"
diff: 提高+/省选-
pid: P2407
tag: ['2009', '各省省选', '山东', '最短路']
---
# [SDOI2009] 地图复原
## 题目描述

很久以前，有一个传说中的“EWF”部族，他们世代生活在一个N×M的矩形大地上。虽然，生活的地区有高山、有沼泽，但通过勤劳勇敢，渐渐地，他们在自己的地盘上修筑了一条回路。

后来，“EWF”部族神秘地消失了。不过，考古学家在那片他们曾经生活过的地方找到了一份地图。地图是N×M的矩阵，左上角的坐标为(0, 0)，右下角的坐标为(N, M)。矩阵中的每个格子，表示高山、沼泽、平地、房屋或是道路其中之一。如果一个格子表示道路，那么经过这个格子的道路要么是直走，要么是拐弯。如下图，左边2幅表示直走格子的，右边4幅表示需要拐弯的格子。一个表示道路的格子只能表示下列情况之一。

 ![](https://cdn.luogu.com.cn/upload/pic/1588.png) 

可是，由于地图的年代久远，考古学家虽然能分清一个格子代表的地形，可对于道路的标记，考古学家们只能分清这一格是表示直走的还是拐弯的。现在，他们求助于你，希望你能帮助他们复原这份“EWF”部族的地图。

## 输入格式

输入文件recover.in的第一行包含两个用空格分隔的正整数N和M，分别表示地图的高和长。

接下来一个N行M列的矩阵描述地图，矩阵中没有多余字符。

大写“S”表示直走的道路，大写“T”表示拐弯的道路，点“.”表示高山、沼泽、平地和房屋。

## 输出格式

输出文件recover.out包含2N-1行，每行2M-1个字符，描述了这条回路。

所有第2i+1行的2j+1个字符为小写字母o，表示了矩阵的第i行第j列的格子的中心(i, j)。

若回路包含了(i, j)到(i, j+1)或(i, j+1)到(i, j)的一条路径，则第2i+1行的第2j+2个字符为减号“-”（ASCII码为45）；

若回路包含了(i, j)到(i+1, j)或(i+1, j)到(i, j)的一条路径，则第2i+2行的第2j+1个字符为竖线“|”（ASCII码为124）。

其它以上未说明位置上的字符为空格（ASCII码为32）。

输入数据保证至少存在一个合法解，故你的输出应有且仅有一条回路。如果存在多组答案，请输出任意一组。

## 样例

### 样例输入 #1
```
3 4
TST.
S.TT
TSST

```
### 样例输出 #1
```
o-o-o o
|   |  
o o o-o
|     |
o-o-o-o

```
## 提示

对于20%的数据，有N ≤ 10；

对于40%的数据，有1 ≤ N, M ≤ 80；

对于40%的数据，输入没有“.”,且N, M > 10；

对于100%的数据，满足1 ≤ N, M ≤ 800。



---

---
title: "[SDOI2010] 大陆争霸"
layout: "post"
diff: 提高+/省选-
pid: P2446
tag: ['2010', '各省省选', '山东', '最短路']
---
# [SDOI2010] 大陆争霸
## 题目背景

在一个遥远的世界里有两个国家：位于大陆西端的杰森国和位于大陆东端的克里斯国。两个国家的人民分别信仰两个对立的神：杰森国信仰象征黑暗和毁灭的神曾·布拉泽，而克里斯国信仰象征光明和永恒的神斯普林·布拉泽。

幻想历 $8012$ 年 $1$ 月，杰森国正式宣布曾·布拉泽是他们唯一信仰的神，同时开始迫害在杰森国的信仰斯普林·布拉泽的克里斯国教徒。

幻想历 $8012$ 年 $3$ 月 $2$ 日，位于杰森国东部小镇神谕镇的克里斯国教徒发动起义。

幻想历 $8012$ 年 $3$ 月 $7$ 日，神谕镇的起义被杰森国大军以残酷手段镇压。

幻想历 $8012$ 年 $3$ 月 $8$ 日，克里斯国对杰森国宣战。由数十万大军组成的克里斯军团开至两国边境，与杰森军团对峙。

幻想历 $8012$ 年 $4$ 月，克里斯军团攻破杰森军团防线进入神谕镇，该镇幸存的克里斯国教徒得到解放。

战争随后进入胶着状态，旷日持久。战况惨烈，一时间枪林弹雨，硝烟弥漫，民不聊生。
## 题目描述

幻想历 $8012$ 年 $5$ 月 $12$ 日深夜，斯普林·布拉泽降下神谕：“Trust me, earn eternal life.”克里斯军团士气大增。作为克里斯军团的主帅，你决定利用这一机会发动奇袭，一举击败杰森国。具体地说，杰森国有 $N$ 个城市，由 $M$ 条单向道路连接。神谕镇是城市 $1$ 而杰森国的首都是城市 $N$。你只需摧毁位于杰森国首都的曾·布拉泽大神殿，杰森国的信仰，军队还有一切就都会土崩瓦解，灰飞烟灭。

为了尽量减小己方的消耗，你决定使用自爆机器人完成这一任务。唯一的困难是，杰森国的一部分城市有结界保护，不破坏掉结界就无法进入城市。而每个城市的结界都是由分布在其他城市中的一些结界发生器维持的，如果想进入某个城市，你就必须破坏掉维持这个城市结界的所有结界发生器。

现在你有无限多的自爆机器人，一旦进入了某个城市，自爆机器人可以瞬间引爆，破坏一个目标（结界发生器，或是杰森国大神殿），当然机器人本身也会一起被破坏。你需要知道：摧毁杰森国所需的最短时间。

## 输入格式

第一行两个正整数 $N,M$。

接下来 $M$ 行，每行三个正整数 $u_i,v_i,w_i$，表示有一条从城市 $u_i$ 到城市 $v_i$ 的单向道路，自爆机器人通过这条道路需要 $w_i$ 的时间。

之后 $N$ 行，每行描述一个城市。首先是一个正整数 $l_i$，维持这个城市结界所使用的结界发生器数目。之后 $l_i$ 个 $1\ldots N$ 之间的城市编号，表示每个结界发生器的位置。如果 $l_i=0$，则说明该城市没有结界保护，保证 $l_1 = 0$ 。
## 输出格式

仅包含一个正整数 ，击败杰森国所需的最短时间。
## 样例

### 样例输入 #1
```
6 6
1 2 1
1 4 3
2 3 1
2 5 2
4 6 2
5 3 2
0
0
0
1 5
0
2 3 5
```
### 样例输出 #1
```
5
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/1590.png)

![](https://cdn.luogu.com.cn/upload/pic/1591.png)

对于 $20\%$ 的数据，满足 $N\leq 15$，$M≤50$；

对于 $50\%$ 的数据，满足 $N\leq 500$，$M\leq 6\times 10^3$；

对于 $100\%$ 的数据，满足 $1\leq N\leq 3\times 10^3$，$1\leq M\leq 7\times 10^4$，$1\leq w_i\leq 10^8$。

输入数据保证一定有解，且不会存在维持某个城市结界的结界发生器在这个城市内部。

连接两个城市的道路可能不止一条，也可能存在一个城市自己到自己的道路。


---

---
title: "[USACO06NOV] Roadblocks G"
layout: "post"
diff: 提高+/省选-
pid: P2865
tag: ['2006', 'USACO', '最短路']
---
# [USACO06NOV] Roadblocks G
## 题目描述

Bessie has moved to a small farm and sometimes enjoys returning to visit one of her best friends. She does not want to get to her old home too quickly, because she likes the scenery along the way. She has decided to take the second-shortest rather than the shortest path. She knows there must be some second-shortest path.

The countryside consists of R (1 ≤ R ≤ 100,000) bidirectional roads, each linking two of the N (1 ≤ N ≤ 5000) intersections, conveniently numbered 1..N. Bessie starts at intersection 1, and her friend (the destination) is at intersection N.

The second-shortest path may share roads with any of the shortest paths, and it may backtrack i.e., use the same road or intersection more than once. The second-shortest path is the shortest path whose length is longer than the shortest path(s) (i.e., if two or more shortest paths exist, the second-shortest path is the one whose length is longer than those but no longer than any other path).

## 输入格式

Line 1: Two space-separated integers: N and R


Lines 2..R+1: Each line contains three space-separated integers: A, B, and D that describe a road that connects intersections A and B and has length D (1 ≤ D ≤ 5000)

## 输出格式

Line 1: The length of the second shortest path between node 1 and node N

## 样例

### 样例输入 #1
```
4 4
1 2 100
2 4 200
2 3 250
3 4 100
```
### 样例输出 #1
```
450
```
## 提示

Two routes: 1 -> 2 -> 4 (length 100+200=300) and 1 -> 2 -> 3 -> 4 (length 100+250+100=450)

## 题目翻译

贝茜把家搬到了一个小农场，但她常常回到 FJ 的农场去拜访她的朋友。贝茜很喜欢路边的风景，不想那么快地结束她的旅途，于是她每次回农场，都会选择第二短的路径，而不象我们所习惯的那样，选择最短路。  
贝茜所在的乡村有 $R(1\le R \le 10^5)$ 条双向道路，每条路都联结了所有的 $N(1\le N\le 5000)$ 个农场中的某两个。贝茜居住在农场 $1$，她的朋友们居住在农场 $N$（即贝茜每次旅行的目的地）。  
贝茜选择的第二短的路径中，可以包含任何一条在最短路中出现的道路，并且，一条路可以重复走多次。当然咯，第二短路的长度必须严格大于最短路（可能有多条）的长度，但它的长度必须不大于所有除最短路外的路径的长度。


---

---
title: "[USACO07JAN] Problem Solving G"
layout: "post"
diff: 提高+/省选-
pid: P2876
tag: ['动态规划 DP', '贪心', '2007', 'USACO', '最短路']
---
# [USACO07JAN] Problem Solving G
## 题目描述

In easier times, Farmer John's cows had no problems. These days, though, they have problems, lots of problems; they have P (1 ≤ P ≤ 300) problems, to be exact. They have quit providing milk and have taken regular jobs like all other good citizens. In fact, on a normal month they make M (1 ≤ M ≤ 1000) money.

Their problems, however, are so complex they must hire consultants to solve them. Consultants are not free, but they are competent: consultants can solve any problem in a single month. Each consultant demands two payments: one in advance (1 ≤ payment ≤ M) to be paid at the start of the month problem-solving is commenced and one more payment at the start of the month after the problem is solved (1 ≤ payment ≤ M). Thus, each month the cows can spend the money earned during the previous month to pay for consultants. Cows are spendthrifts: they can never save any money from month-to-month; money not used is wasted on cow candy.

Since the problems to be solved depend on each other, they must be solved mostly in order. For example, problem 3 must be solved before problem 4 or during the same month as problem 4.

Determine the number of months it takes to solve all of the cows' problems and pay for the solutions.


## 输入格式

Line 1: Two space-separated integers: M and P.


Lines 2..P+1: Line i+1 describes problem i with two space-separated integers: Bi and Ai. Bi is the payment to the consult BEFORE the problem is solved; Ai is the payment to the consult AFTER the problem is solved.


## 输出格式

Line 1: The number of months it takes to solve and pay for all the cows' problems.

## 样例

### 样例输入 #1
```
100 5
40 20
60 20
30 50
30 50
40 40
```
### 样例输出 #1
```
6
```
## 提示

|      | Avail | Probs  | Before  | After   | Candy  |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
|Month | Money | Solved | Payment | Payment | Money  |
| 1    | 0     | -none- | 0       | 0       | 0      |
| 2    | 100   | 1, 2   | 40+60   | 0       | 0      |
| 3    | 100   | 3, 4   | 30+30   | 20+20   | 0      |
| 4    | 100   | -none- | 0       | 50+50   | 0      |
| 5    | 100   | 5      | 40      | 0       | 60     |
| 6    | 100   | -none- | 0       | 40      | 60     |
## 题目翻译

在经济状况较好的时候，FJ 的奶牛没有任何问题。但如今，它们有 $P$（$1 \le P \le 300$）个问题。他们不再提供牛奶，而是像所有其他好公民一样找到了固定的工作。事实上，在一个正常的月份，他们赚了 $M$（$1 \le M \le 1000$）元钱。 

然而，他们的问题非常复杂，他们必须聘请顾问来解决。咨询师不是免费的，但他们很有能力。咨询师可以在一个月内解决任何问题。每个咨询师要求两次付款，一次是在开始解决问题的月初提前支付 $a_i$ 元（$1 \le a_i \le M$），另一次是在问题解决后的月初再支付 $b_i$ 元（$1 \le b_i \le M$），这样奶牛每个月就可以用上个月赚的钱来支付咨询师的费用。

由于所要解决的问题是相互依存的，所以它们必须基本上按顺序解决。例如，问题 $3$ 必须在问题 $4$ 之前解决，或者在问题 $4$ 的同一个月内解决。 

确定解决奶牛所有问题所需的月数，并支付解决方案的费用。

注意：奶牛不会存钱，每个月赚到的钱没有用完就会消失。


---

---
title: "[USACO07NOV] Telephone Wire G"
layout: "post"
diff: 提高+/省选-
pid: P2885
tag: ['动态规划 DP', '2007', 'USACO', '最短路']
---
# [USACO07NOV] Telephone Wire G
## 题目描述

Farmer John's cows are getting restless about their poor telephone service; they want FJ to replace the old telephone wire with new, more efficient wire. The new wiring will utilize N (2 ≤ N ≤ 100,000) already-installed telephone poles, each with some heighti meters (1 ≤ heighti ≤ 100). The new wire will connect the tops of each pair of adjacent poles and will incur a penalty cost C × the two poles' height difference for each section of wire where the poles are of different heights (1 ≤ C ≤ 100). The poles, of course, are in a certain sequence and can not be moved.

Farmer John figures that if he makes some poles taller he can reduce his penalties, though with some other additional cost. He can add an integer X number of meters to a pole at a cost of X2.

Help Farmer John determine the cheapest combination of growing pole heights and connecting wire so that the cows can get their new and improved service.

给出若干棵树的高度，你可以进行一种操作：把某棵树增高h，花费为h\*h。


操作完成后连线，两棵树间花费为高度差\*定值c。


求两种花费加和最小值。

## 输入格式

\* Line 1: Two space-separated integers: N and C

\* Lines 2..N+1: Line i+1 contains a single integer: heighti

## 输出格式

\* Line 1: The minimum total amount of money that it will cost Farmer John to attach the new telephone wire.

## 样例

### 样例输入 #1
```
5 2
2
3
5
1
4
```
### 样例输出 #1
```
15
```


---

---
title: "[USACO07NOV] Cow Relays G"
layout: "post"
diff: 提高+/省选-
pid: P2886
tag: ['动态规划 DP', '2007', 'USACO', '最短路', '矩阵乘法']
---
# [USACO07NOV] Cow Relays G
## 题目描述

For their physical fitness program, N (2 ≤ N ≤ 1,000,000) cows have decided to run a relay race using the T (2 ≤ T ≤ 100) cow trails throughout the pasture.

Each trail connects two different intersections (1 ≤ I1i ≤ 1,000; 1 ≤ I2i ≤ 1,000), each of which is the termination for at least two trails. The cows know the lengthi of each trail (1 ≤ lengthi  ≤ 1,000), the two intersections the trail connects, and they know that no two intersections are directly connected by two different trails. The trails form a structure known mathematically as a graph.

To run the relay, the N cows position themselves at various intersections (some intersections might have more than one cow). They must position themselves properly so that they can hand off the baton cow-by-cow and end up at the proper finishing place.

Write a program to help position the cows. Find the shortest path that connects the starting intersection (S) and the ending intersection (E) and traverses exactly N cow trails.

给出一张无向连通图，求S到E经过k条边的最短路。

## 输入格式

\* Line 1: Four space-separated integers: N, T, S, and E

\* Lines 2..T+1: Line i+1 describes trail i with three space-separated integers: lengthi , I1i , and I2i

## 输出格式

\* Line 1: A single integer that is the shortest distance from intersection S to intersection E that traverses exactly N cow trails.

## 样例

### 样例输入 #1
```
2 6 6 4
11 4 6
4 4 8
8 4 9
6 6 8
2 6 9
3 8 9
```
### 样例输出 #1
```
10
```
## 题目翻译

给定一张 $T$ 条边的无向连通图，求从 $S$ 到 $E$ 经过 $N$ 条边的最短路长度。
### 输入格式
第一行四个正整数 $N,T,S,E$ ，意义如题面所示。

接下来 $T$ 行每行三个正整数 $w,u,v$ ，分别表示路径的长度，起点和终点。
### 输出格式
一行一个整数表示图中从 $S$ 到 $E$ 经过 $N$ 条边的最短路长度。
### 数据范围
对于所有的数据，保证 $1\le N\le 10^6$，$2\le T\le 100$。

所有的边保证 $1\le u,v\le 1000$，$1\le w\le 1000$。


---

---
title: "[USACO09DEC] Cow Toll Paths G"
layout: "post"
diff: 提高+/省选-
pid: P2966
tag: ['2009', 'USACO', '排序', '最短路']
---
# [USACO09DEC] Cow Toll Paths G
## 题目描述

Like everyone else, FJ is always thinking up ways to increase his revenue. To this end, he has set up a series of tolls that the cows will pay when they traverse the cowpaths throughout the farm.

The cows move from any of the $N (1 \leq N \leq 250)$ pastures conveniently numbered $1...N$ to any other pasture over a set of $M (1 \leq M \leq 10,000) $bidirectional cowpaths that connect pairs of different pastures $A_j$ and $B_j (1 \leq A_j \leq N; 1 \leq B_j \leq N)$. FJ has assigned a toll $L_j (1 \leq L_j \leq 100,000)$ to the path connecting pastures $A_j$ and $B_j$.

While there may be multiple cowpaths connecting the same pair of pastures, a cowpath will never connect a pasture to itself. Best of all, a cow can always move from any one pasture to any other pasture by following some sequence of cowpaths.

In an act that can only be described as greedy, FJ has also assigned a toll $C_i (1 \leq C_i \leq 100,000)$ to every pasture. The cost of moving from one pasture to some different pasture is the sum of the tolls for each of the cowpaths that were traversed plus a **single additional toll** that is the maximum of all the pasture tolls encountered along the way, including the initial and destination pastures.

The patient cows wish to investigate their options. They want you to write a program that accepts $K (1 \leq K \leq 10,000)$ queries and outputs the minimum cost of trip specified by each query. Query $i$ is a pair of numbers $s_i$ and $t_i (1 \leq s_i \leq N; 1 \leq t_i \leq N; s_i \neq t_i)$ specifying a starting and ending pasture.

Consider this example diagram with five pastures:

The 'edge toll' for the path from pasture $1$ to pasture $2$ is $3$. Pasture $2$'s 'node toll' is $5$.

To travel from pasture $1$ to pasture $4$, traverse pastures $1$ to $3$ to $5$ to $4$. This incurs an edge toll of $2+1+1=4$ and a node toll of $4$ (since pasture $5$'s toll is greatest), for a total cost of $4+4=8$.

The best way to travel from pasture $2$ to pasture $3$ is to traverse pastures $2$ to $5$ to $3$. This incurs an edge toll of $3+1=4$ and a node toll of $5$, for a total cost of $4+5=9$.

给定一个 $n$ 点 $m$ 边的双向图，第 $i$ 条道路连接了 $u_i$ 与 $v_i$，边权为 $w_i$，第 $i$ 个点的点权为 $c_i$。

给定 $q$ 组询问，第 $i$ 组询问求从 $s_i$ 到 $t_i$ 的路径的边权之和与点权的最大值的和的最小值。

**可能有重边，但保证无自环。**
## 输入格式

-  Line $1$: Three space separated integers: $N$, $M$, and $K$

- Lines $2..N+1$: Line $i+1$ contains a single integer: $C_i$

- Lines $N+2..N+M+1$: Line $j+N+1$ contains three space separated integers: $A_j$, $B_j$, and $L_j$

- Lines $N+M+2..N+M+K+1$: Line $i+N+M+1$ specifies query $i$ using two space-separated integers: $s_i$ and $t_i$

第一行三个整数 $n,m,q$ 代表点数，边数与询问数。   
接下来 $n$ 行每行一个整数 $c_i$ 代表第 $i$ 个点的点权。    
接下来 $m$ 行每行三个整数 $u_i,v_i,w_i$ 代表第 $i$ 条边从 $u_i$ 连到 $v_i$ 边权为 $w_i$。   
接下来 $q$ 行每行两个整数 $s_i,t_i$ 代表第 $i$ 组询问求从 $s_i$ 到 $t_i$ 的边权之和与点权的最大值的和的最小值。

## 输出格式

- Lines $1..K$: Line $i$ contains a single integer which is the lowest cost of any route from $s_i$ to $t_i$

$q$ 行每行一个整数，代表第 $i$ 组询问的结果。
## 样例

### 样例输入 #1
```
5 7 2 
2 
5 
3 
3 
4 
1 2 3 
1 3 2 
2 5 3 
5 3 1 
5 4 1 
2 4 3 
3 4 4 
1 4 
2 3 

```
### 样例输出 #1
```
8 
9 

```
## 提示

对于 $100\%$ 的数据，$1 \le n \le 250$，$1 \le m \le 10^4$，$1 \le q \le 10^4$。


---

---
title: "[USACO10DEC] Big Macs Around the World G"
layout: "post"
diff: 提高+/省选-
pid: P3001
tag: ['2010', 'USACO', 'Special Judge', '最短路']
---
# [USACO10DEC] Big Macs Around the World G
## 题目描述

Bessie is studying her favorite subject, Macroeconomics, in cowllege. For her final project, she will be presenting research on exchange rates between countries around the world.


In order to make her presentation more lively, she would like to show the relative prices of Big Macs around the world, despite their rather unsavory contents. To illustrate, suppose that Bessie would like to find smallest value of a Big Mac in a country given its value in some initial country and exchange rates from which other country's values can be calculated (as illustrated below):




```cpp
* A Big Mac is worth 60 dollars in the United States 
* The exchange rate from US dollars to Canadian dollars is 0.2 Canadian dollars per US dollar 
* The exchange rate from US dollars to British Pounds is 5.00 British Pounds per US Dollar 
* The exchange rate from British Pounds to Canadian dollars is 0.5 Canadian dollars per British Pound 
* The exchange rate between Canadian dollars to US dollars is 5.00 US dollars per Canadian dollar and Bessie would like to find the smallest possible value of a Big Mac in Canada that can be obtained by exchanging currencies. There are two ways: 
* Going from US dollars directly to Canada dollars would yield a burger worth 60.00 US dollars * 0.2 Canadian dollars / US dollar = 12.00 Canadian dollars 
* Going from US dollars to British Pounds to Canadian dollars would yield a burger worth 60.00 US$ * 5.00 GBP / 1 US$ * 0.5 C$ / 1 GBP = 150.00 C$ (Canadian dollars). 
```
Bessie would choose the former option, since she would much rather pay 12.00 Canadian dollars instead of 150.00 Canadian dollars for a Big Mac in Canada. 

Bessie has N (1 <= N <= 2,000) countries conveniently labeled 1 to N that she would like to consider along with a list of M (1 <= M <= 25,000) exchange rates e_ij (0.1 < e_ij <= 10), each between countries i and j (1 <= i <= N; 1 <= j <= N). 

Given the value V (1 <= V <= 1,000,000,000,000), which is not necessarily an integer, of the Big Mac in her starting country A (1 <= A <= N), help her find the smallest possible value of a Big Mac in country B (1 <= B <= N; B != A) after a series of currency conversions. If there is no minimum, output 0. 

It is guaranteed that the answer is, if not 0, between 1 and 10^15.

It is also guaranteed that, for any country's currency, it is possible to get to any other country's currency.




## 输入格式

Line 1: Five space-separated numbers: N, M, V, A, B

Lines 2..M+1: Three space-separated numbers: i, j, e\_ij

## 输出格式

Line 1: A single positive number, the price of the Big Mac, with absolute or relative error at most 10^-6. If there is no minimum, output 0.
## 样例

### 样例输入 #1
```
3 4 60 1 2 
1 2 0.2 
1 3 5 
3 2 0.5 
2 1 5 

```
### 样例输出 #1
```
12.00 

```
## 题目翻译

### 题目描述

Bessie 正在学习她最喜欢的科目宏观经济学，作为她最后一门学科，她将对世界各种货币的汇率进行研究。

为了让她的演讲更加生动，她会展示一个叫做 BM 的商品在全世界的相对价格。举个例子，Bessie 会通过其他国家的汇率去找到一件 BM 在一个国家的最小价值。

- 一件 BM 在美国值 $60$ 美元；
- 美元与加拿大元的汇率为 $1$ 美元换 $0.2$ 加拿大元（$1:0.2$）。
- 美元与英镑的汇率为 $1$ 美元换 $5$ 英镑（$1:5$）。
- 英镑与加拿大元的汇率为 $1$ 英镑换 $0.5$ 加拿大元（$1:0.5$）。
- 加拿大元与美元的汇率是 $5$ 美元换一加拿大元（$5:1$），Bessie 有两种方法通过货币兑换在加拿大这个国家找到一件 BM 的最低价值：

1. 拿着美元直接去加拿大，通过汇率得出一件 BM 只要 $12$ 加拿大元；
2. 拿着美元去英国，兑换为英镑后再去加拿大，得出一件 BM 要 $150$ 加拿大元。

Bessie 会选择前一种方案因为她更乐意为在加拿大买一件 BM 支付 $12$ 加元而不是 $150$ 加元。

Bessie 有 $N(1\leq N\leq 2000)$ 个国家的信息和 $M(1\leq M\leq25000)$ 种汇率，在 $i,j$ 国间的汇率表示为 $e_{ij}(0.1\leq e_{ij}\leq 10)$。

给你一个值 $V(1\leq V\leq 10^{12})$，$V$ 不一定是一个整数。$V$ 是 BM 在起始国家 A 的价格，帮助 Bessie 寻找到在 B 国 BM 最低的价格，如果不存在，则输出 $0$。

据保证答案小于 $10^{15}$，也保证所有国家都可以通过汇率将钱币转为别的国家的。

### 输入格式

第 $1$ 行：五个数：$N,M,V,A,B$，分别一个空格隔开。

第 $2$ 到 $M+1$ 行：三个数 $i,j,e_{ij}$，分别一个空格隔开。

### 输出格式

一行：BM 在 B 国的最低价格，精确到 $10^{-6}$。如果没有最小值，输出 $0$。

**注意，本题的汇率是单向的**。

感谢 @JJYZ\_cbh 的耐心翻译



---

---
title: "[USACO16DEC] Lasers and Mirrors G"
layout: "post"
diff: 提高+/省选-
pid: P3036
tag: ['搜索', '2016', 'USACO', '图论建模', '最短路']
---
# [USACO16DEC] Lasers and Mirrors G
## 题目描述

For some reason, Farmer John's cows always seem to be running laser light shows.

For their latest show, the cows have procured a large powerful laser -- so large,in fact, that they cannot seem to move it easily from the location where it was delivered. They would like to somehow send the light from the laser to the barn on the other side of FJ's property.  Both the laser and the barn can be considered to be located at points in the 2D plane on a map of FJ's farm.  The cows plan to point the laser so that it sends a beam of light out either horizontally or vertically (i.e.,  aligned with the x or y axes).  They will then bounce this beam off a number of mirrors to direct it to the barn.

On the farm there are $N$ fence posts ($1 \leq N \leq 100,000$) located at distinct 2D points (also distinct from the laser and the barn) at which the cows can mount mirrors.  The cows can choose not to mount a mirror on a fence post, in which case the laser would simply pass straight over the top of the post without changing direction.  If the cows do mount a mirror on a fence post, they align it diagonally like / or \ so that it will re-direct a horizontal beam of light in a vertical direction or vice versa.

Please compute the minimum possible number of mirrors the cows need to use in order to re-direct the laser to the barn.

## 输入格式

The first line of input contains 5 space-separated integers: $N, x_L, y_L, x_B, y_B$, where $(x_L, y_L)$ is the location of the laser and $(x_B, y_B)$ is the location of the barn.  All coordinates are between $0$ and $1,000,000,000$.

The next $N$ lines each contain the $x$ and $y$ locations of a fence post, both integers in the range $0 \ldots 1,000,000,000$.
## 输出格式

Please output the minimum number of mirrors needed to direct the laser to the barn, or -1 if this is impossible to do.
## 样例

### 样例输入 #1
```
4 0 0 7 2
3 2
0 2
1 6
3 0
```
### 样例输出 #1
```
1
```
## 题目翻译

### 题目描述

出于某种原因，Farmer John 的奶牛似乎总是在举办激光表演。

在它们的最新表演中，奶牛们获得了一台大型强力激光器——事实上，这台激光器太大，以至于它们无法轻易从交付地点移动它。它们希望以某种方式将激光器的光束发送到 Farmer John 的农场另一边的谷仓。激光器和谷仓都可以被视为位于 Farmer John 农场地图的二维平面中的点。奶牛们计划将激光器指向水平或垂直方向（即与 $x$ 轴或 $y$ 轴对齐），然后通过多次反射镜将光束引导到谷仓。

农场上有 $N$ 个栅栏柱（$1 \leq N \leq 100,000$），位于与激光器和谷仓不同的二维点上，奶牛们可以在这些栅栏柱上安装反射镜。奶牛们可以选择不在栅栏柱上安装反射镜，在这种情况下，激光器会直接穿过栅栏柱而不改变方向。如果奶牛们在栅栏柱上安装反射镜，它们会将其对角线对齐，例如 / 或 \，以便将水平光束重新定向为垂直方向，反之亦然。

请计算奶牛们将激光器引导到谷仓所需的最少反射镜数量。

### 输入格式

输入的第一行包含 $5$ 个用空格分隔的整数：$N, x_L, y_L, x_B, y_B$，其中 $(x_L, y_L)$ 是激光器的位置，$(x_B, y_B)$ 是谷仓的位置。所有坐标都在 $0$ 到 $1,000,000,000$ 之间。

接下来的 $N$ 行每行包含一个栅栏柱的 $x$ 和 $y$ 位置，这两个整数都在 $0 \ldots 1,000,000,000$ 范围内。

### 输出格式

请输出将激光器引导到谷仓所需的最少反射镜数量，如果无法实现，则输出 -1。


---

---
title: "[USACO12OPEN] Unlocking Blocks S"
layout: "post"
diff: 提高+/省选-
pid: P3053
tag: ['贪心', '2012', 'USACO', '枚举', '最短路']
---
# [USACO12OPEN] Unlocking Blocks S
## 题目描述

A little-known fact about cows is that they love puzzles! For Bessie's birthday, Farmer John gives her an interesting mechanical puzzle for her to solve.  The puzzle consists of three solid objects, each of which is built from 1x1 unit squares glued together.  Each of these objects is a "connected" shape,  in the sense that you can get from one square on the object to any other square on the object by stepping north, south, east, or west, through squares on the object.

An object can be moved by repeatedly sliding it either north, south, east, or west one unit.  The goal of the puzzle is to move the objects so that they are separated -- where their bounding boxes no longer share any positive overlap with each-other.  Given the shapes and locations of the three objects, your task is to help Bessie decide what is the minimum number of individual slides required to separate the objects.

![](https://cdn.luogu.com.cn/upload/image_hosting/flelqdzu.png)


## 输入格式

\* Line 1: Three space-separated integers: N1, N2, and N3, describing respectively the number of unit squares making up objects 1, 2, and 3.

\* Lines 2..1+N1: Each of these lines describes the (x,y) location of the south-west corner of single square that is part of object 1.  All coordinates lie in the range 0..9.

\* Lines 2+N1..1+N1+N2: Each of these lines describes the (x,y) location of the south-west corner of single square that is part of object 2.  All coordinates lie in the range 0..9.

\* Lines 2+N1+N2..1+N1+N2+N3: Each of these lines describes the (x,y) location of the south-west corner of single square that is part of object 3.  All coordinates lie in the range 0..9.


第1行：三个整数N1,N2,N3，表示组成模块1,2,3的小正方体数目。


第2行到第N1+1行：读入一对坐标（x，y），每对坐标表示组成模块1的一个小正方体西南角落的位置。所有坐标在0..9之间。


第N1+2行到第N1+N2+1行：读入一对坐标（x，y），每对坐标表示组成模块2的一个小正方体西南角落的位置。所有坐标在0..9之间。


第N1+N2+2行到第N1+N2+N3+…

## 输出格式

\* Line 1: The minimum number of moves necessary to separate the three objects, or -1 if the objects cannot be separated.

## 样例

### 样例输入 #1
```
12 3 5 
0 0 
1 0 
2 0 
3 0 
3 1 
0 1 
0 2 
0 3 
0 4 
1 4 
2 4 
3 4 
2 1 
2 2 
1 2 
2 3 
3 3 
4 3 
4 4 
4 2 

```
### 样例输出 #1
```
5 

```
## 提示

Object 1 is made from 12 squares, object 2 is made from 3 squares, and object 3 is made from 5 squares.  The shapes of the objects are those in the figure above.


If we slide object 3 to the east by one position, then slide object 2 north by one position, then slide object 1 west by three positions, then the bounding boxes of the three objects will no longer share any overlap in common.

模块1由12块小正方体制造，模块2由3块小正方体制造，模块3由5块小正方体制造。最后的图像在如上。（吃图？！）

```cpp
A：模块1方块 B：模块2方块 C：模块3方块 *：啥都木有
A A A A C
A * C C C
A B B * C
A * B A *
A A A A *
```
假如我们把模块3向东移一个单位，然后把模块2向北移一个单位，然后把模块1向西移三个单位，就满足了条件。

感谢 @姚起龙 提供翻译

## 题目翻译


奶牛们一个鲜为人知的事实是它们爱解谜！Bessie生日时农夫约翰给了她一个有趣的机械锁给她解决。锁由三个模块构成，每一个模块都由1x1的小立方体粘连而成。每一个模块都是一个“连通”的模型，那么，你就可以通过在模型上的小正方体间向北、南、东或西走而从模型的一个小正方形到达模型上的任何其他小正方形。


一个模块可以多次向东西南北滑动一个单位。拼图的目标是滑动模块使其分离——即使它们的边界框不再有任何重叠。给定三个模块的形状与位置，请你帮助Bessie找到达到目标需要的最小滑动次数。


---

---
title: "[USACO14FEB] Secret Code S"
layout: "post"
diff: 提高+/省选-
pid: P3102
tag: ['字符串', '搜索', '2014', 'USACO', '最短路']
---
# [USACO14FEB] Secret Code S
## 题目描述

Farmer John has secret message that he wants to hide from his cows; the message is a string of length at least 2 containing only the characters A..Z.

To encrypt his message, FJ applies a sequence of "operations" to it, where an operation applied to a string S first shortens S by removing either some (but not all) of the initial characters or some (but not all) of the final characters from S, after which the original string S is attached either at the beginning or end.  For example, a single operation to the string ABC could result in eight possible strings:

AABC
ABABC
BCABC
CABC
ABCA
ABCAB
ABCBC
ABCC
Given the final encrypted string, please count the number of possible ways FJ could have produced this string using one or more repeated operations applied to some source string.  Operations are treated as being distinct even if they give the same encryption of FJ's message.  For example, there are four distinct separate ways to obtain AAA from AA.

Print your answer out modulo 2014.

农民约翰收到一条的消息，记该消息为长度至少为2，只由大写字母组成的字符串S，他通过一系列操作对S进行加密。


他的操作为，删除S的前面或者后面的若干个字符（但不删光整个S），并将剩下的部分连接到原字符串S的前面或者后面。如对于S=‘ABC’，共有8总可能的操作结果：


AABC

ABABC

BCABC

CABC

ABCA

ABCAB

ABCBC

ABCC

给出加密后的目标字符串，请计算共有多少种加密的方案。


对于同字符的字符串，加密方案不止一种，比如把AA加密成AAA，共有4种加密方案。将你的答案mod 2014后输出。

## 输入格式

\* Line 1: A single encrypted string of length at most 100.

## 输出格式

\* Line 1: The number of ways FJ could have produced this string with one or more successive operations applied to some initial string of length at least 2, written out modulo 2014.  If there are no such ways, output zero.

## 样例

### 样例输入 #1
```
ABABA 

```
### 样例输出 #1
```
8 

```
## 提示

Here are the different ways FJ could have produced ABABA:

1. Start with ABA -> AB+ABA

2. Start with ABA -> ABA+BA

3. Start with AB -> AB+A -> AB+ABA

4. Start with AB -> AB+A -> ABA+BA

5. Start with BA -> A+BA -> AB+ABA

6. Start with BA -> A+BA -> ABA+BA

7. Start with ABAB -> ABAB+A

8. Start with BABA -> A+BABA



---

---
title: "[USACO14OPEN] Dueling GPSs S"
layout: "post"
diff: 提高+/省选-
pid: P3106
tag: ['2014', 'USACO', '最短路']
---
# [USACO14OPEN] Dueling GPSs S
## 题目描述

Farmer John has recently purchased a new car online, but in his haste he accidentally clicked the "Submit" button twice when selecting extra features for the car, and as a result the car ended up equipped with two GPS navigation systems!  Even worse, the two systems often make conflicting decisions about the route that FJ should take.

The map of the region in which FJ lives consists of N intersections (2 <= N <= 10,000) and M directional roads (1 <= M <= 50,000).  Road i connects intersections A\_i (1 <= A\_i <= N) and B\_i (1 <= B\_i <= N). Multiple roads could connect the same pair of intersections, and a bi-directional road (one permitting two-way travel) is represented by two separate directional roads in opposite orientations.  FJ's house is located at intersection 1, and his farm is located at intersection N.  It is possible to reach the farm from his house by traveling along a series of directional roads.

Both GPS units are using the same underlying map as described above; however, they have different notions for the travel time along each road. Road i takes P\_i units of time to traverse according to the first GPS unit, and Q\_i units of time to traverse according to the second unit (each travel time is an integer in the range 1..100,000).

FJ wants to travel from his house to the farm.  However, each GPS unit complains loudly any time FJ follows a road (say, from intersection X to intersection Y) that the GPS unit believes not to be part of a shortest route from X to the farm (it is even possible that both GPS units can complain, if FJ takes a road that neither unit likes).

Please help FJ determine the minimum possible number of total complaints he can receive if he chooses his route appropriately.  If both GPS units complain when FJ follows a road, this counts as +2 towards the total.

## 输入格式

\* Line 1: The integers N and M.

Line i describes road i with four integers: A\_i B\_i P\_i Q\_i.

## 输出格式

\* Line 1: The minimum total number of complaints FJ can receive if he routes himself from his house to the farm optimally.

## 样例

### 样例输入 #1
```
5 7 
3 4 7 1 
1 3 2 20 
1 4 17 18 
4 5 25 3 
1 2 10 1 
3 5 4 14 
2 4 6 5 

```
### 样例输出 #1
```
1 

```
## 提示

There are 5 intersections and 7 directional roads.  The first road connects from intersection 3 to intersection 4; the first GPS thinks this road takes 7 units of time to traverse, and the second GPS thinks it takes 1 unit of time, etc.


If FJ follows the path 1 -> 2 -> 4 -> 5, then the first GPS complains on the 1 -> 2 road (it would prefer the 1 -> 3 road instead).  However, for the rest of the route 2 -> 4 -> 5, both GPSs are happy, since this is a shortest route from 2 to 5 according to each GPS.

## 题目翻译

Farmer John 最近在网上购买了一台新车，然而当他给这台新车挑选额外设备时他不小心快速地点击了“提交” 按钮两次，因此这台新车配备了两台 GPS 导航系统！更糟糕的是，两台系统对 Farmer John 的出行路线经常做出相互冲突的决定。

Farmer John 居住的区域包含 $N$ 个结点（$2 \le N \le 10000$）和 $M$ 条有向道路（$1 \le M \le 50000$）。第 $i$ 条道路从 $A_i$ 连向 $B_i$（$1 \le A_i, B_i \le N$）。多条道路可能连接同样一对结点，而一条双向道路是由两条单独的反向的道路来表示的。 Farmer John 的家在结点 $1$，他的农场在结点 $N$。数据保证从家出发经过一系列有向道路可以到达农场。

两台 GPS 系统的内置地图都如上所描述。然而，它们对通过每条道路所需时间的预计是不同的。第一台和第二台 GPS 系统预测通过道路 $i$ 需要花费的时间分别为 $P_i$ 和 $Q_i$ 个单位时间（通过每条道路所需时间是一个在 $[1, 10^5]$ 内的整数）。

Farmer John 想要从他的家去往农场。然而，当 Farmer John 通过了一条道路（假设是从 $X$ 到 $Y$），而一台 GPS 系统认为这条道路不是从 $X$ 前往农场的最短路径中的一部分时，这台 GPS 系统就会大声抱怨（如果两台 GPS 系统都认为该条道路都不是最短路径的一部分时，两台系统会同时抱怨）。

请帮助 Farmer John 求出，如果 Farmer John 合理地选择出行路线，两台 GPS 系统抱怨次数总和的最小值。如果 Farmer John 通过了一条路时两台 GPS 系统同时抱怨，那么抱怨次数增加 $2$。


---

---
title: "[USACO14DEC] Piggy Back S"
layout: "post"
diff: 提高+/省选-
pid: P3110
tag: ['2014', 'USACO', '广度优先搜索 BFS', '最短路']
---
# [USACO14DEC] Piggy Back S
## 题目描述

Bessie and her sister Elsie graze in different fields during the day, and in the evening they both want to walk back to the barn to rest. Being clever bovines, they come up with a plan to minimize the total amount of energy they both spend while walking.

Bessie spends B units of energy when walking from a field to an adjacent field, and Elsie spends E units of energy when she walks to an adjacent field.  However, if Bessie and Elsie are together in the same field, Bessie can carry Elsie on her shoulders and both can move to an adjacent field while spending only P units of energy (where P might be considerably less than B+E, the amount Bessie and Elsie would have spent individually walking to the adjacent field).  If P is very small, the most energy-efficient solution may involve Bessie and Elsie traveling to a common meeting field, then traveling together piggyback for the rest of the journey to the barn.  Of course, if P is large, it may still make the most sense for Bessie and Elsie to travel

separately.  On a side note, Bessie and Elsie are both unhappy with the term "piggyback", as they don't see why the pigs on the farm should deserve all the credit for this remarkable form of

transportation.

Given B, E, and P, as well as the layout of the farm, please compute the minimum amount of energy required for Bessie and Elsie to reach the barn.


## 输入格式

INPUT: (file piggyback.in) 

The first line of input contains the positive integers B, E, P, N, and M.  All of these are at most 40,000.  B, E, and P are described above. N is the number of fields in the farm (numbered 1..N, where N >= 3), and M is the number of connections between fields.  Bessie and Elsie start in fields 1 and 2, respectively.  The barn resides in field N. 

The next M lines in the input each describe a connection between a pair of different fields, specified by the integer indices of the two fields.  Connections are bi-directional.  It is always possible to travel from field 1 to field N, and field 2 to field N, along a series of such connections.

## 输出格式

OUTPUT: (file piggyback.out) 

A single integer specifying the minimum amount of energy Bessie and

Elsie collectively need to spend to reach the barn.  In the example

shown here, Bessie travels from 1 to 4 and Elsie travels from 2 to 3

to 4.  Then, they travel together from 4 to 7 to 8.

## 样例

### 样例输入 #1
```
4 4 5 8 8 
1 4 
2 3 
3 4 
4 7 
2 5 
5 6 
6 8 
7 8 
```
### 样例输出 #1
```
22 

```
## 题目翻译

Bessie 和 Elsie 在不同的区域放牧，他们希望花费最小的能量返回谷仓。从一个区域走到一个相连区域，Bessie 要花费 $B$ 单位的能量，Elsie要花费 $E$ 单位的能量。

如果某次他们两走到同一个区域，Bessie 可以背着 Elsie 走路，花费 $P$ 单位的能量走到另外一个相连的区域。当然，存在 $P>B+E$ 的情况。

相遇后，他们可以一直背着走，也可以独立分开。

Bessie 从 $1$ 号区域出发，Elsie 从 $2$ 号区域出发，两个人都要返回到位于 $n$ 号区域的谷仓。

### 输入格式

第一行输入 5 个整数 $B,E,P,n,m$。$B,E,P$ 的含义如上文所述。
$n$ 表示农场中区域的数量，$m$ 表示连接两个区域的道路的数量。

接下来 $m$ 行，每行两个整数 $x,y$，描述一条 $x$ 区域和 $y$ 区域之间的双向边。数据保证图是连通的。

### 输出格式

一行一个整数，表示 Bessie 和 Elsie 能量花费总和的最小值。

### 数据范围

$1 \leq B,E,P,n,m \leq 4 \times 10^4$。

#### 样例解释：
Bessie 从 1 走到 4，Elsie 从 2 走到 3 再走到 4。然后，两个人一起从 4 走到 7，再走到 8。


---

---
title: "[USACO15JAN] Cow Routing S"
layout: "post"
diff: 提高+/省选-
pid: P3115
tag: ['2015', 'USACO', '最短路']
---
# [USACO15JAN] Cow Routing S
## 题目描述

Tired of the cold winter weather on her farm, Bessie the cow plans to fly to a warmer destination for vacation. Unfortunately, she discovers that only one airline, Air Bovinia, is willing to sell tickets to cows, and that these tickets are somewhat complicated in structure.

Air Bovinia owns N planes (1 <= N <= 1000), each of which flies on a specific "route" consisting of two or more cities.  For example, one plane might fly on a route that starts at city 1, then flies to city 5, then flies to city 2, and then finally flies to city 8. No city appears multiple times in a route. If Bessie chooses to utilize a route, she can board at any city along the route and then disembark at any city later along the route. She does not need to board at the first city or disembark at the last city. Each route has a certain cost, which Bessie must pay if she uses any part of the route, irrespective of the number of cities she visits along the route. If Bessie uses a route multiple times during her travel (that is, if she leaves the route and later comes back to use it from antoher city), she must pay for it each time it is used.

Bessie would like to find the cheapest way to travel from her farm (in city A) to her tropical destination (city B). Please help her decide what is the minimum cost she must pay, and also the smallest number of individual flights she must use take to achieve this minimum cost.

## 输入格式

The first line of input contains A, B, and N, separated by spaces.

The next 2N lines describe the available routes, in two lines per route. The first line contains the cost of using the route (an integer in the range 1..1,000,000,000), and the number of cities along the route (an integer in the range 1..100).  The second line contains a list of the cities in order along the route.  Each city is identified by an integer in the range 1..1000. Note that the cost of an itinerary can easily add up to more than can fit into a 32-bit integer, so you should probably use 64-bit integers (e.g., "long long" integers in C/C++).

## 输出格式

Output the minimum cost of an itinerary that Bessie can use to travel from city A to city B, as well as the minimum number of individual flights required to achieve this minimum cost. If there is no solution, output "-1 -1" (quotes for clarity) on a single line.

## 样例

### 样例输入 #1
```
3 4 3 
3 5 
1 2 3 4 5 
2 3 
3 5 4 
1 2 
1 5 

```
### 样例输出 #1
```
2 2 

```
## 题目翻译

### 题目描述

Bessie 对她农场那寒冷的天气感到厌烦，于是她准备坐飞机到一个更温暖的地方度假。不幸的是，她发现只有一个航空公司：Air Bovinia，愿意卖票给牛，并且这些票的结构有些复杂。

Air Bovinia 拥有 $n$ 架飞机，每架飞机都有一个经过两个及以上的城市的特殊航线。举个例子：一架飞机可以从城市 $1$ 出发，然后飞往城市 $5$，再飞到城市 $2$，最后飞到城市 $8$。注意**航线是单向的**。任何城市都不会在同一条航线上出现多次。如果 Bessie 选择了一条航线，那么她可以从航线上的任意一个城市上飞机，然后在途中任意一个城市下飞机。他不必从航线的起点上飞机，再从航线的终点下飞机。每条航线都有一个确定的花费，只要它搭乘了这个航班，她就必须支付这个航班的全额花费，不论她途经了几个城市。如果 Bessie 多次搭乘了某个航班，那么每次搭乘 Bessie 都必须支付航班的花费。

Bessie 想要找到从她农场所在的城市（城市 $A$）到她目的地所在城市（城市 $B$）最便宜的路线。请你告诉她他最少要花多少钱，并告诉她在此基础上她最少要**经过几段航线**，也即经过的城市数量 $-1$（包括起点和终点）。

### 输入格式

第一行三个整数 $A,B,n$。

接下来 $2n$ 行，每两行描述一次航班。第一行包括航线的花费 $cost$ 与经过的城市数 $len$。第二行 $len$ 个整数，表示航班依次经过的城市。

### 输出格式

一行两个整数，输出 Bessie 旅行最少要花的钱以及在此基础上最少的经过航线数量。

如果 Bessie 不能从她的农场到达她的目的地，则输出 `-1 -1`。

### 数据范围

$1\le n\le 1000$，$1\le cost\le 10^9$，$1\le len\le 100$。城市的编号均不超过 $1000$。

可能需要开 `long long`。



---

---
title: "[USACO15OPEN] Bessie's Birthday Buffet S"
layout: "post"
diff: 提高+/省选-
pid: P3125
tag: ['动态规划 DP', '2015', 'USACO', '最短路']
---
# [USACO15OPEN] Bessie's Birthday Buffet S
## 题目描述

For Bessie the cow’s birthday, Farmer John has given her free reign over one of his best fields to eat grass.

The field is covered in $N$ patches of grass ($1 \le N \le 1000$), conveniently numbered $1\ldots N$, that each have a distinct quality value.  If Bessie eats grass of quality $Q$, she gains $Q$ units of energy.  Each patch is connected to up to 10 neighboring patches via bi-directional paths, and it takes Bessie $E$ units of energy to move between adjacent patches ($1 \le E \le 1,000,000$).

Bessie can choose to start grazing in any patch she wishes, and she wants to stop grazing once she has accumulated a maximum amount of energy.

Unfortunately, Bessie is a picky bovine, and once she eats grass of a certain quality, she’ll never eat grass at or below that quality level again!  She is still happy to walk through patches without eating their grass; in fact, she might find it beneficial to walk through a patch of high-quality grass without eating it, only to return later for a tasty snack.

Please help determine the maximum amount of energy Bessie can accumulate.
## 输入格式

The first line of input contains $N$ and $E$.  Each of the remaining $N$ lines describe a patch of grass.  They contain two integers $Q$ and $D$ giving the quality of the patch (in the range $1\ldots 1,000,000$) and its number of neighbors.  The remaining $D$ numbers on the line specify the neighbors.
## 输出格式

Please output the maximum amount of energy Bessie can accumulate.
## 样例

### 样例输入 #1
```
5 2
4 1 2
1 3 1 3 4
6 2 2 5
5 2 2 5
2 2 3 4
```
### 样例输出 #1
```
7
```
## 提示

Bessie starts at patch 4 gaining 5 units of energy from the grass there. She then takes the path to patch 5 losing 2 units of energy during her travel. She refuses to eat the lower quality grass at patch 5 and travels to patch 3 again losing 2 units of energy.  Finally she eats the grass at patch 3 gaining 6 units of energy for a total of 7 energy.

Note that the sample case above is different from test case 1 when you submit.
## 题目翻译

### 题目描述

为了庆祝奶牛 Bessie 的生日，Farmer John 允许她在他最好的草地上自由吃草。

这片草地被划分为 $N$ 块草皮（$1 \le N \le 1000$），编号为 $1\ldots N$，每块草皮都有一个独特的质量值。如果 Bessie 吃了质量为 $Q$ 的草，她会获得 $Q$ 单位的能量。每块草皮通过双向路径与最多 10 个相邻草皮相连，Bessie 在相邻草皮之间移动需要消耗 $E$ 单位的能量（$1 \le E \le 1,000,000$）。

Bessie 可以选择从任意一块草皮开始吃草，她希望在积累最大能量后停止吃草。

不幸的是，Bessie 是一头挑剔的牛，一旦她吃了某种质量的草，她就再也不会吃质量等于或低于该水平的草了！她仍然乐意在不吃草的情况下穿过草皮；事实上，她可能会发现穿过一块高质量草皮而不吃草是有益的，只是为了稍后再回来享用美味的小吃。

请帮助确定 Bessie 能够积累的最大能量。

### 输入格式

输入的第一行包含 $N$ 和 $E$。接下来的 $N$ 行描述每块草皮。每行包含两个整数 $Q$ 和 $D$，分别表示草皮的质量（范围为 $1\ldots 1,000,000$）和它的邻居数量。该行剩下的 $D$ 个数字指定了邻居的编号。

### 输出格式

请输出 Bessie 能够积累的最大能量。

### 说明/提示

Bessie 从草皮 4 开始，获得 5 单位的能量。然后她沿着路径移动到草皮 5，在移动过程中消耗了 2 单位的能量。她拒绝吃草皮 5 上质量较低的草，并继续移动到草皮 3，再次消耗了 2 单位的能量。最后，她吃了草皮 3 上的草，获得了 6 单位的能量，总共积累了 7 单位的能量。

请注意，上述样例与提交时的测试用例 1 不同。


---

---
title: "[SCOI2011] 糖果"
layout: "post"
diff: 提高+/省选-
pid: P3275
tag: ['2011', '四川', '各省省选', '最短路', '差分约束']
---
# [SCOI2011] 糖果
## 题目描述

幼儿园里有 $N$ 个小朋友，$\text{lxhgww}$ 老师现在想要给这些小朋友们分配糖果，要求每个小朋友都要分到糖果。但是小朋友们也有嫉妒心，总是会提出一些要求，比如小明不希望小红分到的糖果比他的多，于是在分配糖果的时候，$\text{lxhgww}$ 需要满足小朋友们的 $K$ 个要求。幼儿园的糖果总是有限的，$\text{lxhgww}$ 想知道他至少需要准备多少个糖果，才能使得每个小朋友都能够分到糖果，并且满足小朋友们所有的要求。
## 输入格式

输入的第一行是两个整数 $N$，$K$。接下来 $K$ 行，表示这些点需要满足的关系，每行 $3$ 个数字，$X$，$A$，$B$。

+ 如果 $X=1$， 表示第 $A$ 个小朋友分到的糖果必须和第 $B$ 个小朋友分到的糖果一样多；
+ 如果 $X=2$， 表示第 $A$ 个小朋友分到的糖果必须少于第 $B$ 个小朋友分到的糖果；
+ 如果 $X=3$， 表示第 $A$ 个小朋友分到的糖果必须不少于第 $B$ 个小朋友分到的糖果；
+ 如果 $X=4$， 表示第 $A$ 个小朋友分到的糖果必须多于第 $B$ 个小朋友分到的糖果；
+ 如果 $X=5$， 表示第 $A$ 个小朋友分到的糖果必须不多于第 $B$ 个小朋友分到的糖果；
## 输出格式

输出一行，表示 $\text{lxhgww}$ 老师至少需要准备的糖果数，如果不能满足小朋友们的所有要求，就输出 $-1$。
## 样例

### 样例输入 #1
```
5 7
1 1 2
2 3 2
4 4 1
3 4 5
5 4 5
2 3 5
4 5 1
```
### 样例输出 #1
```
11
```
## 提示

对于 $30\%$ 的数据，保证 $N\leq100$

对于 $100\%$ 的数据，保证 $N\leq100000$

对于所有的数据，保证 $K\leq100000, 1\leq X\leq5, 1\leq A, B\leq N$

---

$\text{upd 2022.7.6}$：新添加 $21$ 组 [Hack 数据](https://www.luogu.com.cn/discuss/454051)。


---

---
title: "[POI 2009] WIE-Hexer"
layout: "post"
diff: 提高+/省选-
pid: P3489
tag: ['动态规划 DP', '2009', 'POI（波兰）', '最短路']
---
# [POI 2009] WIE-Hexer
## 题目描述

Byteasar has become a hexer - a conqueror of monsters.

Currently he is to return to his hometown Byteburg. The way home, alas, leads through a land full of beasts. Fortunately the habitants, forced to fight the monsters for centuries, have mastered the art of blacksmithery - they are now capable of making special swords that are very efficient against the beasts.

The land Byteasar wanders through is quite vast: many towns lie there, and many roads connect them.

These roads do not cross outside the towns (mostly because some of them are underground passages).

Byteasar has gathered all practical information about the land (all hexers like to know these things).

He knows what kind of monsters he may come across each of the roads and how much time he needs to walk it down.

He also knows in which villages there are blacksmiths and against what kinds of monsters the swords that they make work.

Byteasar wants to get back to Byteburg as soon as possible.

As a hexer he is quite ashamed that he does not know the best route, and that he has no sword on him at the moment.

Help him find the shortest path to Byteburg such that whenever he could meet some king of monster, previously he would have a chance to get an appropriate sword to fight the beast.

You need not worry about the number or weight of the swords - every hexer is as strong as an ox, so he can carry (virtually) unlimited number of equipment, swords in particular.

## 输入格式

The first line of the standard input holds four integers: $n,m,p,k$ ($1\le n\le 200,0\le m\le 3000,1\le p\le 13,0\le k\le n$),separated by single spaces, that denote respectively:

the number of towns, the number of roads connecting them,the number of different kinds of monsters and the number of blacksmiths.

The towns are numbered from $1$ to $n$ in such a way that $n$ is Byteburg's number and $1$ is the number of the village which Byteasar starts in. The monster kinds are numbered from $1$ to $p$.

In the following $k$ lines the profiles of successive blacksmiths are given,one per line. The $(i+1)$-st line holds the integers $w_i,q_i,r_{i,1}<r_{i,2}<...<r_{i,q_i}$($1\le w_i\le n,1\le q_i\le p,1\le r_{i,j}\le p$),separated by single spaces, that denote respectively: the number of town in which the blacksmith lives, the number of different kinds of monsters against which his swords are efficient, and the kinds of monsters themselves (in increasing order). Note that a town may have more than one blacksmith.

Then $m$ lines with roads' descriptions follow.The $(k+i+1)$-th line holds the integers$v_i,w_i,t_i,s_i,u_{i,1}<u_{i,2}<...<u_{i,s_i}$($1\le v_i<w_i\le n,1\le t_i\le 500,0\le s_i\le p,1\le u_{i,j}\le p$)separated by single spaces, that denote respectively: the towns that the road connects, the time needed to walk down the road (same in both directions), the number of different kinds of monsters that may appear on that road, and finally the kinds of monsters themselves (in increasing order). No two roads connect the same pair of towns.

## 输出格式

Your programme is to print out one integer to the standard output -  the minimum summary time required to reach Byteburg.

Should reaching Byteburg be impossible, the number should be $-1$.

## 样例

### 样例输入 #1
```
6 7 4 2
2 1 2
3 2 1 3
1 2 2 0
2 3 9 0
1 4 2 1 2
2 5 3 0
4 5 5 2 2 3
4 6 18 0
5 6 3 2 1 2

```
### 样例输出 #1
```
24

```
## 题目翻译

大陆上有 $n$ 个村庄，$m$ 条双向道路，$p$ 种怪物，$k$ 个铁匠，每个铁匠会居住在一个村庄里，你到了那个村庄后可以让他给你打造剑，每个铁匠打造的剑都可以对付一些特定种类的怪物。

每条道路上都可能出现一些特定种类的怪物，每条道路都有一个通过所需要的时间，现在要从 $1$ 走到 $n$，初始的时候你没有剑，要求在经过一条道路的时候，对于任意一种可能出现在这条道路上的的怪物，你都有已经有至少一把剑可以对付他，求从$1$ 走到 $n$ 的最短时间（打造剑不需要时间）



---

---
title: "[USACO17FEB] Why Did the Cow Cross the Road I G"
layout: "post"
diff: 提高+/省选-
pid: P3659
tag: ['2017', 'USACO', '广度优先搜索 BFS', '深度优先搜索 DFS', '最短路']
---
# [USACO17FEB] Why Did the Cow Cross the Road I G
## 题目描述

Why did the cow cross the road? Well, one reason is that Farmer John's farm simply has a lot of roads, making it impossible for his cows to travel around without crossing many of them.

FJ's farm is arranged as an $N \times N$ square grid of fields ($3 \leq N \leq 100$), with a set of $N-1$ north-south roads and $N-1$ east-west roads running through the interior of the farm serving as dividers between the fields. A tall fence runs around the external perimeter, preventing cows from leaving the farm. Bessie the cow can move freely from any field to any other adjacent field (north, east, south, or west), as long as she carefully looks both ways before crossing the road separating the two fields. It takes her $T$ units of time to cross a road ($0 \leq T \leq 1,000,000$).

One day, FJ invites Bessie to visit his house for a friendly game of chess. Bessie starts out in the north-west corner field and FJ's house is in the south-east corner field, so Bessie has quite a walk ahead of her. Since she gets hungry along the way, she stops at every third field she visits to eat grass (not including her starting field, but including possibly the final field in which FJ's house resides). Some fields are grassier than others, so the amount of time required for stopping to eat depends on the field in which she stops.

Please help Bessie determine the minimum amount of time it will take to reach FJ's house.
## 输入格式

The first line of input contains $N$ and $T$. The next $N$ lines each contain $N$ positive integers (each at most 100,000) describing the amount of time required to eat grass in each field. The first number of the first line is the north-west corner.

## 输出格式

Print the minimum amount of time required for Bessie to travel to FJ's house.
## 样例

### 样例输入 #1
```
4 2
30 92 36 10
38 85 60 16
41 13 5 68
20 97 13 80
```
### 样例输出 #1
```
31
```
## 提示

The optimal solution for this example involves moving east 3 squares (eating the "10"), then moving south twice and west once (eating the "5"), and finally moving south and east to the goal.
## 题目翻译

### 题目描述

奶牛为什么要过马路？其中一个原因是 Farmer John 的农场有很多道路，使得他的奶牛在四处走动时不可避免地要穿过许多道路。

FJ 的农场被安排成一个 $N \times N$ 的方形网格田地（$3 \leq N \leq 100$），其中有 $N-1$ 条南北向的道路和 $N-1$ 条东西向的道路穿过农场内部，作为田地之间的分隔。农场外部有一圈高高的围栏，防止奶牛离开农场。奶牛 Bessie 可以自由地从任何田地移动到相邻的田地（北、东、南或西），只要她在穿过分隔两块田地的道路时小心地左右看看。她穿过一条道路需要花费 $T$ 单位时间（$0 \leq T \leq 1,000,000$）。

有一天，FJ 邀请 Bessie 去他家进行一场友好的国际象棋比赛。Bessie 从西北角的田地出发，而 FJ 的家在东南角的田地，因此 Bessie 需要走很长一段路。由于她在路上会感到饥饿，她会在每经过第三个田地时停下来吃草（不包括她的起始田地，但可能包括最终到达的 FJ 家的田地）。有些田地的草比其他田地更茂盛，因此停下来吃草所需的时间取决于她停下的田地。

请帮助 Bessie 确定她到达 FJ 家所需的最少时间。

### 输入格式

输入的第一行包含 $N$ 和 $T$。接下来的 $N$ 行每行包含 $N$ 个正整数（每个数不超过 100,000），描述了每个田地中吃草所需的时间。第一行的第一个数是西北角的田地。

### 输出格式

输出 Bessie 到达 FJ 家所需的最少时间。

### 说明/提示

这个例子的最优解是向东移动 3 个方格（吃“10”），然后向南移动两次，向西移动一次（吃“5”），最后向南和向东移动到目的地。


---

---
title: "[CTSC2000] 冰原探险"
layout: "post"
diff: 提高+/省选-
pid: P3716
tag: ['2000', '枚举', '广度优先搜索 BFS', '最短路', 'CTSC/CTS']
---
# [CTSC2000] 冰原探险
## 题目描述

传说中，南极有一片广阔的冰原，在冰原下藏有史前文明的遗址。整个冰原被横竖划分成了很多个大小相等的方格。在这个冰原上有 $N$ 个大小不等的矩形冰山，这些巨大的冰山有着和南极一样古老的历史。

每个矩形冰山至少占据一个方格，且其必定完整地占据方格。冰山和冰山之间不会重叠，也不会有边或点相连。以下两种情况均是不可能出现的：

![](https://cdn.luogu.com.cn/upload/pic/5096.png)

$\text{ACM}$ 探险队在经过多年准备之后决定在这个冰原上寻找遗址。根据他们掌握的资料，在这个冰原上一个大小为一格的深洞中，藏有一个由史前人类制作的开关。而唯一可以打开这个开关的是一个占据接近一格的可移动的小冰块。显然，在南极是不可能有这样小的独立冰块的，所以这块冰块也一定是史前文明的产物。他们在想办法把这个冰块推到洞里去，这样就可以打开一条通往冰原底部的通道，发掘史前文明的秘密。冰块的起始位置与深洞的位置均不和任何冰山相邻。

这个冰原上的冰面和冰山都是完全光滑的，轻轻的推动冰块就可以使这个冰块向前滑行，直到撞到一座冰山就在它的边上停下来。冰块可以穿过冰面上所有没有冰山的区域，也可以从两座冰山之间穿过（见下图）。冰块只能沿网格方向推动。


 ![](https://cdn.luogu.com.cn/upload/pic/5097.png) 

请你帮助他们以最少的推动次数将冰块推入深洞中。

## 输入格式

输入文件第一行为冰山的个数 $N$ ，第二行为冰块开始所在的方格坐标 $X_{1}$ , $Y_{1}$ ，第三行为深洞所在的方格坐标 $X_{2}, Y_{2}$ ，以下 $N$ 行每行有四个数，分别是每个冰山所占的格子左上角和右下角坐标 $X_{i_{1}}, Y_{i_{1}}, X_{i_{2}}, Y_{i_{2}}$ 
## 输出格式

输出文件包含一个整数，为最少推动冰块的次数。如果无法将冰块推入深洞中，则输出 $0$ 。
## 样例

### 样例输入 #1
```
2
1 1
5 5
1 3 3 3
6 2 8 4
```
### 样例输出 #1
```
3
```
## 提示

$1 \leq N \leq 4000$

样例解释：移动方案如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/y6sx7ya7.png)


---

---
title: "[AHOI2017初中组] guide"
layout: "post"
diff: 提高+/省选-
pid: P3720
tag: ['2017', '安徽', '最短路']
---
# [AHOI2017初中组] guide
## 题目描述

农场主John最近在网上买了一辆新车，在购买汽车配件时，John不小心点了两次“提交”按钮。导致汽车上安装了两套GPS系统，更糟糕的是John在使用GPS导航时，两套系统常常给出不同的路线。从地图上看，John居住的地区有N(2 ≤ N ≤ 100,000)个十字路口和M(1 ≤ M ≤ 500,000)条限定通行方向的道路。第i条道路连接路口 A\_i (1 ≤ A\_i ≤ N)和B\_i (1 ≤ B\_i ≤ N)，两个路口之间可能连接有多条道路。允许双向通⾏的道路是将两条单向通⾏的道路隔开所形成的。


John的家在路口1位置，农场在路口N的位置。John可以沿着⼀系列单向道路从家驾车到农场。所有GPS系统的底层地图信息都是⼀样的，区别仅在于对每一条道路的通⾏时间计算不同。对于第i条道路第一套GPS系统计算通行时间为P\_i个单位时间，而第二套GPS系统则给出Q\_i个单位时间。（所有道路的通行时间都是范围在1到100，000之间的整数）John想要驾车从家到农场。可是，一路上GPS系统总是不厌其烦的提醒John（请从路口X开往路口Y），这是由于John选取了某套GPS系统建议的路径，而另一套GPS系统则认为这不是从路口X到农场的最短路径。我们称之为GPS系统的抱怨。


请你计算一下如果John选择合适的路径到达农场能听到的最少GPS系统的抱怨数 。如果John经过某条道路两套GPS系统都发出抱怨，则抱怨总数加2。

## 输入格式

第一行，两个整数N和M。

接下来M行，其中第i行描述了道路i的信息，A\_i B\_i P\_i Q\_i。

## 输出格式

一个整数，表示John一路上能听到的最小抱怨数。

## 样例

### 样例输入 #1
```
5 7 3 4 7 1
1 3 2 20
1 4 17 18
4 5 25 3
1 2 10 1
3 5 4 14
2 4 6 5
```
### 样例输出 #1
```
1
```


---

---
title: "萃香抱西瓜"
layout: "post"
diff: 提高+/省选-
pid: P3786
tag: ['洛谷原创', '最短路', '进制', '状压 DP']
---
# 萃香抱西瓜
## 题目背景

 ![](https://cdn.luogu.com.cn/upload/pic/5565.png) 

伊吹萃香 (Ibuki Suika) 正在魔法之森漫步，突然，许多西瓜 (Suika) 从四周飞来，划出了绚丽的轨迹。虽然阵势有点恐怖，但她还是决定抱走一些西瓜。

## 题目描述

萃香所处的环境被简化为一个长为 $h$，宽为 $w$ 的网格平面。$X$ 坐标范围为 $[1,w]$，$Y$ 坐标范围为 $[1,h]$。

她初始时（第 $1$ 个时刻）站在坐标为 $(sx,sy)$ 的方格。

西瓜可能在任意一个方格出现，在每个时间单位，它们可能向任何一个方向移动，也可能静止不动。西瓜的位置和移动的轨迹是已知的。西瓜的总数为 $n$ 个，但只有 $m$ 个西瓜可以被萃香抱走，因为其他都太大了，可能会砸伤她。

整个过程会持续 $T$ 个时刻。萃香希望可以抱走全部的 $m$ 个西瓜，并且在任何时候避免与任何一个过大的西瓜处在同一位置。抱走的方式为在某个时刻，与该西瓜处于同一位置。另外，由于萃香不愿耗费过多体力到处乱跑，她每个时刻可以选择静止不动，也可以选择移动到相邻的四个格子之一，只要不越出环境边界。如果选择移动到相邻格子，则算作移动了一次。第 $1$ 个时刻萃香刚站定，无法移动。

在每个时刻，如果萃香选择移动，可以认为萃香与西瓜同时从原来的位置移到了新的位置，没有先后顺序。

萃香想要知道，不被任何一个大西瓜砸中，并得到所有的m个小西瓜的情况下，最少需要移动多少次。

## 输入格式

第一行五个整数 $h,w,T,sx,sy$ ，含义见题目描述。

第二行两个整数 $n,m$，含义见题目描述。

接下来 $n$ 段数据，每一段描述了一个西瓜的出现位置，时间，移动方式，是否可以被抱走等内容，具体如下:

首先一行，两个整数 $t1,t2$，表示西瓜在 $t1$ 时刻出现，$t2$ 时刻消失。若 $t2=T+1$，表示西瓜在最后一个时刻也不消失。保证西瓜至少存在一个时刻。

接下来一行一个整数 $a$，只能为 $0$ 或 $1$，$0$ 表示这个西瓜需要避开，$1$ 表示这个西瓜需要抱走。数据保证需要抱走的西瓜恰好有 $m$ 个。

接下来 $t2-t1$ 行，每一行两个整数 $x,y$，顺序描述了从 $t1$ 时刻到 $t2-1$ 时刻，该西瓜的坐标。西瓜的移动不一定是连续的，并且是一瞬间完成的，所以无需考虑萃香是否站在了移动路径上。

## 输出格式

如果萃香在整个 $T$ 时刻内无法避免被大西瓜砸中或者无法收集到所有 $m$ 个小西瓜，输出 $-1$，否则输出一个整数，表示萃香需要移动的最少次数。

## 样例

### 样例输入 #1
```
5 5 10 3 3
1 1
1 11
1
3 4
5 2
3 5
1 1
5 4
3 4
2 1
1 1
1 1
5 5
```
### 样例输出 #1
```
1
```
## 提示


### 样例说明
第 $2 \sim 4$ 个时刻萃香站着不动，在第 $6$ 个时刻，西瓜出现在萃香旁边，萃香移动到 $(3,4)$ 位置即可抱走这个西瓜。

### 数据范围和提示

本题采用捆绑测试。

Subtask $1$：具有特殊性质 A 和 B；

Subtask $2 \sim 3$：仅具有特殊性质 A；

Subtask $4 \sim 5$：仅具有特殊性质 B；

Subtask $6 \sim 10$：不具有任何一个特殊性质。

特殊性质 A：对于所有西瓜，均满足 $t1=1,t2=T+1$。
所有西瓜全程都静止在原地，不会发生移动。

特殊性质 B：$m=0$。

对于全部子任务，满足：

$1 \le x \le w,1 \le y \le h$

$1\le n \le 20,
0 \le m \le 10,
m \le n$

$1 \le h,w \le 5,
1 \le T \le 100,
1 \le t1 \le T,
2 \le t2 \le T+1,
t1< t2$


保证一个位置不会同时出现两个或两个以上西瓜。


---

---
title: "[SHOI2012] 回家的路"
layout: "post"
diff: 提高+/省选-
pid: P3831
tag: ['图论', '2012', '各省省选', '上海', '最短路']
---
# [SHOI2012] 回家的路
## 题目背景

SHOI2012 D2T1

## 题目描述

2046 年 OI 城的城市轨道交通建设终于全部竣工，由于前期规划周密，建成后的轨道交通网络由$2n$条地铁线路构成，组成了一个$n$纵$n$横的交通网。如下图所示，这$2n$条线路每条线路都包含$n$个车站，而每个车站都在一组纵横线路的交汇处。


出于建设成本的考虑，并非每个车站都能够进行站内换乘，能够进行站内换乘的地铁站共有$m$个，在下图中，标上方块标记的车站为换乘车站。已知地铁运行 1 站需要 2 分钟，而站内换乘需要步行 1 分钟。Serenade 想要知道，在不中途出站的前提下，他从学校回家最快需要多少时间（等车时间忽略不计）。


![](https://cdn.luogu.com.cn/upload/pic/6547.png)

## 输入格式

第一行有两个整数$n,m$。

接下去$m$行每行两个整数$x,y$,表示第$x$条横向线路与第$y$条纵向线路的交

汇站是站内换乘站。

接下去一行是四个整数$x_1,y_1,x_2,y_2$。表示 Serenade 从学校回家时，在第 $x_1$条横向线路与第$y_1$条纵向线路的交汇站上车，在第$x_2$条横向线路与第$y_2$条纵向线路的交汇站下车。

## 输出格式

输出文件只有一行，即 Serenade 在合理选择线路的情况下，回家所需要的时间。如果 Serenade 无法在不出站换乘的情况下回家，请输出-1。

## 样例

### 样例输入 #1
```
2 1
1 2
1 1 2 2
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
6 9
2 1
2 5
3 2
4 4
5 2
5 6
6 1
6 3
6 4
1 1 4 6
```
### 样例输出 #2
```
27
```
### 样例输入 #3
```
6 10
2 1
2 5
3 2
4 4
5 2
5 6
6 1
6 3
6 4
6 6
1 1 4 6
```
### 样例输出 #3
```
26
```
## 提示

对于 30%的数据，$n\le 50,m\le 1000$；

对于 60%的数据，$n\le 500,m\le 2000$；

对于 100%的数据，$n\le 20000,m\le 100000$；



---

---
title: "ことりのおやつ（小鸟的点心）"
layout: "post"
diff: 提高+/省选-
pid: P3946
tag: ['最短路']
---
# ことりのおやつ（小鸟的点心）
## 题目描述

这是2017年的冬天。（又到了白色相簿的季节2333）

![滑雪鸟](https://db.loveliv.es/png/navi/476/0)

滑完雪之后，ことり突然想吃点心啦！于是她去了甜品店。

日本的冬天经常下雪。不幸的是，今天也是这样，每秒钟雪的厚度会增加q毫米。

秋叶原共有n个地点，编号从1到n。每个地点在开始的时候的积雪高度为hi。

有m条**双向**道路连接这些地点，它们的长度分别为wi米。

雪太大，公共交通系统已经停摆了，所以ことり得走路回家。她走路的速度是1m/s。

为了方便地图的绘制，秋叶原的道路规划使得每条道路严格地连接两个不同的地点，并且不会有两条道路连接的地点相同。

每个地点都有一个极限雪高li，单位是毫米，如果到达这个地点的时候，这里的雪的高度高于li则会被困在这个点走不出去，无法成功地走到ことり家。

点心店这个地点的编号是s，ことり家的编号是t。

不考虑点心店和ことり家的雪。

ことり想在g秒内回到家吃点心，越快越好。如果在g秒之内，ことり无法到家，或者她被困在路上了，那么ことり会把wtnap变成她的点心( ・ 8 ・ )

## 输入格式

第1行6个整数，空格隔开，分别代表n，m，s，t，g，q。

以下n行，每行2个整数，空格隔开，分别表示这个地点的hi和li。

以下m行，每行3个整数，空格隔开，分别表示这条路连接的两个地点u, v和这条路的长度wi。

## 输出格式

输出1行1个整数，表示到达ことり家的最短用时。

如果wtnap变成了ことり的点心那么输出"wtnap wa kotori no oyatsu desu!"

输出时不含引号。

## 样例

### 样例输入 #1
```
2 1 1 2 10 1
1 10
3 10
1 2 6
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
5 6 2 5 10 1
1 10
1 10
1 10
1 10
1 10
1 5 9
1 3 9
2 4 1
2 5 9
3 4 1
3 5 6
```
### 样例输出 #2
```
8
```
### 样例输入 #3
```
5 6 2 5 10 1
1 10
1 10
10 10
1 10
1 10
1 5 9
1 3 9
2 4 1
2 5 11
3 4 1
3 5 6

```
### 样例输出 #3
```
wtnap wa kotori no oyatsu desu!
```
## 提示

对于0%的数据，与样例一模一样；  
对于40%的数据，q = 0。  
对于上一行中50%的数据，所有wi < li。  
对于100%的数据，1 ≤ s, t ≤ n;  0 ≤ g, q ≤ 10^9; 0 ≤ wi ≤ li ≤ 10^9。

![](https://cdn.luogu.com.cn/upload/pic/9826.png)



---

---
title: "[NOIP 2017 提高组] 逛公园"
layout: "post"
diff: 提高+/省选-
pid: P3953
tag: ['搜索', '2017', 'NOIP 提高组', '记忆化搜索', '最短路']
---
# [NOIP 2017 提高组] 逛公园
## 题目背景

NOIP2017 D1T3
## 题目描述

策策同学特别喜欢逛公园。公园可以看成一张 $N$ 个点 $M$ 条边构成的有向图，且没有 自环和重边。其中 $1$ 号点是公园的入口，$N$ 号点是公园的出口，每条边有一个非负权值， 代表策策经过这条边所要花的时间。

策策每天都会去逛公园，他总是从 $1$ 号点进去，从 $N$ 号点出来。

策策喜欢新鲜的事物，它不希望有两天逛公园的路线完全一样，同时策策还是一个 特别热爱学习的好孩子，它不希望每天在逛公园这件事上花费太多的时间。如果 $1$ 号点 到 $N$ 号点的最短路长为 $d$，那么策策只会喜欢长度不超过 $d + K$ 的路线。

策策同学想知道总共有多少条满足条件的路线，你能帮帮它吗？

为避免输出过大，答案对 $P$ 取模。

如果有无穷多条合法的路线，请输出 $-1$。

## 输入格式

第一行包含一个整数 $T$, 代表数据组数。

接下来 $T$ 组数据，对于每组数据： 第一行包含四个整数 $N,M,K,P$，每两个整数之间用一个空格隔开。


接下来 $M$ 行，每行三个整数 $a_i,b_i,c_i$，代表编号为 $a_i,b_i$ 的点之间有一条权值为 $c_i$ 的有向边，每两个整数之间用一个空格隔开。

## 输出格式

输出文件包含 $T$ 行，每行一个整数代表答案。

## 样例

### 样例输入 #1
```
2
5 7 2 10
1 2 1
2 4 0
4 5 2
2 3 2
3 4 1
3 5 2
1 5 3
2 2 0 10
1 2 0
2 1 0
```
### 样例输出 #1
```
3
-1


```
## 提示

【样例解释1】


对于第一组数据，最短路为 $3$。 $1\to 5, 1\to 2\to 4\to 5, 1\to 2\to 3\to 5$ 为 $3$ 条合法路径。


【测试数据与约定】

对于不同的测试点，我们约定各种参数的规模不会超过如下


测试点编号　　|$T$　　　|$N$　　　|$M$　　　|$K$　　　|是否有 $0$ 边
-|-|-|-|-|-
$1$|$5$|$5$|$10$|$0$|否
$2$|$5$|$10^3$|$2\times 10^3$|$0$|否
$3$|$5$|$10^3$|$2\times 10^3$|$50$|否
$4$|$5$|$10^3$|$2\times 10^3$|$50$|否
$5$|$5$|$10^3$|$2\times 10^3$|$50$|否
$6$|$5$|$10^3$|$2\times 10^3$|$50$|是
$7$|$5$|$10^5$|$2\times 10^5$|$0$|否
$8$|$3$|$10^5$|$2\times 10^5$|$50$|否
$9$|$3$|$10^5$|$2\times 10^5$|$50$|是
$10$|$3$|$10^5$|$2\times 10^5$|$50$|是


对于 $100\%$ 的数据，$1 \le P \le 10^9$，$1 \le a_i,b_i \le N$，$0 \le c_i \le 1000$。

数据保证：至少存在一条合法的路线。

---

- 2019.8.30 增加了一组 hack 数据 by @skicean
- 2022.7.21 增加了一组 hack 数据 by @djwj233


---

---
title: "[AHOI2014/JSOI2014] 骑士游戏"
layout: "post"
diff: 提高+/省选-
pid: P4042
tag: ['图论', '2014', '各省省选', '江苏', '安徽', '最短路']
---
# [AHOI2014/JSOI2014] 骑士游戏
## 题目背景

长期的宅男生活中，JYY 又挖掘出了一款 RPG 游戏。在这个游戏中 JYY 会扮演一个英勇的骑士，用他手中的长剑去杀死入侵村庄的怪兽。
## 题目描述

在这个游戏中，JYY 一共有两种攻击方式，一种是普通攻击，一种是法术攻击。两种攻击方式都会消耗 JYY 一些体力。采用普通攻击进攻怪兽并不能把怪兽彻底杀死，怪兽的尸体可以变出其他一些新的怪兽，注意一个怪兽可能经过若干次普通攻击后变回一个或更多同样的怪兽；而采用法术攻击则可以彻底将一个怪兽杀死。当然了，一般来说，相比普通攻击，法术攻击会消耗更多的体力值（但由于游戏系统 bug，并不保证这一点）。

游戏世界中一共有 $N$ 种不同的怪兽，分别由 $1$ 到 $N$ 编号，现在 $1$ 号怪兽入侵村庄了，JYY 想知道，最少花费多少体力值才能将所有村庄中的怪兽全部杀死呢？
## 输入格式

第一行包含一个整数 $N$。

接下来 $N$ 行，每行描述一个怪兽的信息；

其中第 $i$ 行包含若干个整数，前三个整数为 $S_i$，$K_i$ 和 $R_i$，表示对于 $i$ 号怪兽，普通攻击需要消耗 $S_i$ 的体力，法术攻击需要消耗 $K_i$ 的体力，同时 $i$ 号怪兽死亡后会产生 $R_i$ 个新的怪兽。表示一个新出现的怪兽编号。同一编号的怪兽可以出现多个。
## 输出格式

输出一行一个整数，表示最少需要的体力值。

## 样例

### 样例输入 #1
```
4
4 27 3 2 3 2
3 5 1 2
1 13 2 4 2
5 6 1 2
```
### 样例输出 #1
```
26
```
## 提示

首先用消耗 $4$ 点体力用普通攻击，然后出现的怪兽编号是 $2$，$2$ 和 $3$。花费 $10$ 点体力用法术攻击杀死两个编号为 $2$ 的怪兽。剩下 $3$ 号怪兽花费 $1$ 点体力进行普通攻击。此时村庄里的怪兽编号是 $2$ 和 $4$。最后花费 $11$ 点体力用法术攻击将这两只怪兽彻底杀死。一共花费的体力是 $4+5+5+1+5+6=26$。

对于所有数据 $2 \le N \le 2 \times 10^5$，$1 \le R_i,\sum R_i \le 10^6$，$1 \le K_i,S_i \le 5 \times 10^{14}$。



---

---
title: "[SCOI2009] 最长距离"
layout: "post"
diff: 提高+/省选-
pid: P4162
tag: ['2009', '四川', '各省省选', '剪枝', '最短路']
---
# [SCOI2009] 最长距离
## 题目描述

windy 有一块矩形土地，被分为 $N\times M$ 块 $1\times 1$ 的小格子。 有的格子含有障碍物。 如果从格子 A 可以走到格子 B，那么两个格子的距离就为两个格子中心的欧几里德距离。 如果从格子 A 不可以走到格子 B，就没有距离。如果格子 X 和格子 Y 有公共边，并且 X 和 Y 均不含有障碍物，就可以从 X 走到 Y。 如果 windy 可以移走 $T$ 块障碍物，求所有格子间的最大距离。保证移走 $T$ 块障碍物以后，至少有一个格子不含有障碍物。

## 输入格式

第一行包含三个整数，$N,M,T$。 接下来有 $N$ 行，每行一个长度为 $M$ 的字符串，`0` 表示空格子，`1` 表示该格子含有障碍物。

## 输出格式

包含一个浮点数，保留 $6$ 位小数。

## 样例

### 样例输入 #1
```
3 3 0
001
001
110
```
### 样例输出 #1
```
1.414214
```
### 样例输入 #2
```
4 3 0
001
001
011
000
```
### 样例输出 #2
```
3.605551
```
### 样例输入 #3
```
3 3 1
001
001
001

Sample Output
```
### 样例输出 #3
```
2.828427
```
## 提示

- $20\%$ 的数据，满足  $1 \le N,M \le 30 $，$ 0 \le T \le 0 $。
- $40\%$ 的数据，满足  $1 \le N,M \le 30 $，$ 0 \le T \le 2 $。
- $100\%$ 的数据，满足 $1 \le N,M \le 30 $，$ 0 \le T \le 30$。



---

---
title: "河城荷取的烟花"
layout: "post"
diff: 提高+/省选-
pid: P4277
tag: ['搜索', '图论', '枚举', '最短路']
---
# 河城荷取的烟花
## 题目背景

#宴会已经接近尾声
![](https://cdn.luogu.com.cn/upload/pic/15119.png)
## 题目描述

快乐的时光总是这么短暂，这场宴会终究将要闭幕。

为了给大家留下一个深刻而美好的印象，萃香拜托掌握着顶尖科技的河城荷取用她刚刚研制出的装置来点燃烟花。

这个装置由3部分构成——一些长度为1的绳子，一些长度为$\sqrt{ 2 }$的绳子，还有一块不能燃烧的木板。河城荷取将木板划分成长度为 1 的单元格，并标上坐标，之后将这些绳子摆在木板上连接成一个连通图(即绳子上的任意两点均可互相到达)。注意，这些绳子的两端必须放在单元格的顶点上，即长度为 1 的绳子只能放在单元格的某一边上，长度为$\sqrt{ 2 }$的绳子只能放在单元格的某一对角线上。

现在，河城荷取会在木板上任意一根绳子的端点处点火(不能从绳子的中间处点火)，点火后，火会沿着绳子向前燃烧（每根绳子都有自己的燃烧速度），并能点燃与它相接的其它绳子。

比如说下面这张图，河城荷取不能在 A 点点火，但在 C 点或 B点点火都是充许的。

![](https://cdn.luogu.com.cn/upload/pic/15120.png)

为了演出效果，河城荷取必须保证所有绳子都燃烧完的总时间最短，可是由于绳子的条数过多，所以河城荷取找到了你来帮忙，让你帮她求出最短的总时间是多少。

如果你能完成这个任务，你就会获得两个奖励——100分和观赏一场盛大的烟花盛宴！

## 输入格式

第一行为一个正整数n，表示绳子的条数

接下来n行每行 5 个数： X1 Y1 X2 Y2 T,其中（X1, Y1）和（X2, Y2）分别表示绳子两端的坐标，T表示这根绳子的燃烧时间，是指从绳子的某一端点火燃烧到另一端，燃完所需的时间。


## 输出格式

第一行一个实数t，保留 4 位小数，表示所有绳子完全燃烧的最少时间。
## 样例

### 样例输入 #1
```
1
0 0 1 1 1
```
### 样例输出 #1
```
1.0000
```
### 样例输入 #2
```
5
0 0 0 1 1
1 0 0 1 10
0 0 1 0 1
0 0 1 1 1
2 2 1 1 1
```
### 样例输出 #2
```
3.2500
```
## 提示

【样例一解释】:从任一端点火都行，燃烧时间都是 1

【样例二解释】:

在 (0,0)位置点火，绳子 1, 3 和 4 将被点燃，燃烧 0.5 分钟后，绳子 2 将被从中间点燃向两端燃烧，再过 0.5 分钟，绳子 1, 3, 4 将被完全燃烧，绳子5将被点燃并在 1分钟后燃烧完 (比绳子 2 早燃完)。

绳子 2 从中间向两端燃烧 0.5 分钟以后，变成两小段，每段的燃烧时间是 4.5
分钟。但因为此时两小段绳子的另一端也同时被点燃，燃烧速度变成原来的
两倍，还需 2.25 分钟的燃烧时间， 所以总时间： 1 + 2.25 = 3.25

【数据范围】:

![](https://cdn.luogu.com.cn/upload/pic/15213.png)


---

---
title: "[Code+#4] 最短路"
layout: "post"
diff: 提高+/省选-
pid: P4366
tag: ['图论建模', '最短路', '进制', 'Code+']
---
# [Code+#4] 最短路
## 题目背景

在北纬 91° ，有一个神奇的国度，叫做企鹅国。这里的企鹅也有自己发达的文明，称为企鹅文明。因为企鹅只有黑白两种颜色，所以他们的数学也是以二进制为基础发展的。

比如早在 $11101001$ 年前，他们就有了异或这样一个数学概念。如果你不知道异或是什么，请出门过墙左转到[这里](https://zh.wikipedia.org/wiki/%E9%80%BB%E8%BE%91%E5%BC%82%E6%88%96)。

再比如早在 $1000010$ 年前，他们的大科学家 Penguin. Tu 就提出了[图](https://zh.wikipedia.org/wiki/%E5%9B%BE_%28%E6%95%B0%E5%AD%A6%29#%E6%9C%89/%E7%84%A1_%E5%90%91%E5%9B%BE)和[最短路径](https://zh.wikipedia.org/wiki/%E6%9C%80%E7%9F%AD%E8%B7%AF%E9%97%AE%E9%A2%98)这样一些概念。
## 题目描述

企鹅国中有 $N$ 座城市，编号从 $1$ 到 $N$ 。

对于任意的两座城市 $i$ 和 $j$ ，企鹅们可以花费 $(i~\mathrm{xor}~j) \times C$ 的时间从城市 $i$ 走到城市 $j$ ，这里 $C$ 为一个给定的常数。

当然除此之外还有 $M$ 条单向的快捷通道，第 $i$ 条快捷通道从第 $F_i$​​ 个城市通向第 $T_i$​​ 个城市，走这条通道需要消耗 $V_i$​​ 的时间。

现在来自 **P**enguin **K**ingdom **U**niversity 的企鹅豆豆正在考虑从城市 $A$ 前往城市 $B$ 最少需要多少时间？
## 输入格式

从标准输入读入数据。

输入第一行包含三个整数 $N,M,C$ ，表示企鹅国城市的个数、快捷通道的个数以及题面中提到的给定的常数$C$。

接下来的 $M$ 行，每行三个正整数 $F_i,T_i,V_i$​ ($1 \leq F_i \leq N$,$1 \leq T_i \leq N ,1\leq V_i \leq 100$)，分别表示对应通道的起点城市标号、终点城市标号和通过这条通道需要消耗的时间。

最后一行两个正整数 $A,B$ $(1 \leq C \leq 100)$，表示企鹅豆豆选择的起点城市标号和终点城市标号。

## 输出格式

输出到标准输出。

输出一行一个整数，表示从城市 $A$ 前往城市 $B$ 需要的最少时间。

## 样例

### 样例输入 #1
```
4 2 1
1 3 1
2 4 4
1 4
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
7 2 10
1 3 1
2 4 4
3 6
```
### 样例输出 #2
```
34
```
## 提示

**样例1解释**

直接从 $1$ 走到 $4$ 就好了。

**样例2解释**

先从 $3$ 走到 $2$ ，再从 $2$ 通过通道到达 $4$ ，再从 $4$ 走到 $6$。

![0](https://cdn.luogu.com.cn/upload/pic/16868.png)

活泼可爱的出题人给大家留下了下面这张图。

![1](https://i.loli.net/2018/04/02/5ac1bb2333c22.jpg)

Credit: https://www.luogu.org/discuss/show/38908


---

---
title: "[COCI 2017/2018 #3] Portal"
layout: "post"
diff: 提高+/省选-
pid: P4442
tag: ['贪心', '2017', '最短路', 'COCI（克罗地亚）']
---
# [COCI 2017/2018 #3] Portal
## 题目描述

The protagonist of this task, Chell, must solve a new puzzle GLaDOS has come up with.

Chell is in a room whose layout that can be represented as a matrix of dimensions N rows and M columns. Each field can be one of the following:

- Obstructed field - there is a wall in it (denoted as ‘#’),
- The field where Chell is initially (denoted as ‘C’),
- The field where Chell must get to in order to solve the puzzle (denoted as ‘F’), or
- An empty field (denoted as ‘.’).

Chell is carrying a so-called portal gun, a gun with which you can create portals in the walls.

In each move, she can do one of the following:
- Move to an adjacent field using one move up, down, left or right (she cannot move to the field with a wall in it). This move lasts one unit of time.
- Create a portal in the wall by turning towards a wall, not necessarily an adjacent one, in the direction up, down, left or right and shooting. The portal will be created only on the side of the wall it was hit from. In each moment, **at most two portals can be active**​. If a new portal is being created in the moment when two portals are already active, the one that was created earlier will disappear. It is not possible to create a new portal at the position of another existing portal. This move lasts a negligible
amount of time, i.e. zero amounts of time.
- If she’s at a field that is adjacent to a wall and there’s a portal on her side of the wall, she can step into the portal and exit to a non-obstructed field with another portal. This move is possible if there are two active portals and lasts one unit of time.

Chell wants to know the minimal amount of time it takes for her to solve the puzzle, i.e. to reach the field denoted as ‘F’.

**Please note**: The room will always have walls on the sides, and letters ‘C’ and ‘F’ will appear only once in the matrix.

## 输入格式

The first line of input contains the positive integers N and M (4 ≤ N, M ≤ 500), the numbers from the task.

Each of the following N lines contains M characters that describe the layout of the room.

## 输出格式

You must output the minimal amount of time it takes to solve the puzzle, or “nemoguce” (without quotation marks, Croatian for impossible) if it is not possible to solve it.

## 样例

### 样例输入 #1
```
4 4
####
#.F#
#C.#
####

```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 8
########
#.##..F#
#C.##..#
#..#...#
#.....##
########

```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
4 5
#####
#C#.#
###F#
#####

```
### 样例输出 #3
```
nemoguce

```
## 提示

In test cases worth 50% of total points, it will hold 4 ≤ N, M ≤ 15.

**Clarification​ ​of​ ​the​ ​second​ ​test​ ​case:**

The puzzle can be solved in 8 moves, illustrated in the pictures below.

In the first move, we turn towards the left wall, shoot and create a portal that appears on the wall in the $3^{rd}$ row and $1^{st}$ column (coordinates (3,1)) from the right side.

In the second move, we create a portal from the upper side of the wall at coordinates (6,2).

In the third move, we step into the portal at coordinates (3,1) and exit at coordinates (5,2) - a
non-obstructed field with the second portal.

In the fourth move, we turn right and create a portal from the left side of the wall at coordinates (5,7).
Since there are already two portals, the one at field (3,1) disappears.

In the fifth move, we step into the portal at coordinates (6,2) and exit at coordinates (5,6) with the
second portal.

In the sixth move, we create a new portal from the lower side of the wall at coordinates (1,6), making
the portal at coordinates (6,2) disappear.

In the seventh move, we step into the portal at coordinates (5,7) and exit at coordinates (2,6).
Finally, in the eighth move, we move one place to the right to end the game.

The portal creation in moves 1, 2, 4 and 6 lasts zero amounts of time, whereas the rest of the move
last one unit of time, so the total time needed to solve the puzzle is 4 units of time.

![](https://cdn.luogu.com.cn/upload/pic/17512.png)
## 题目翻译

题目大意:

给定一个矩阵，每个格子由下列字母表示：

●有障碍的区域表示为‘#’

● 初始位置表示为‘C’

● 目标位置表示为 ‘F’

● 空白区域表示为‘.’

可以进行三种操作：
●走到上下左右相邻的格子，不能走到有墙的区域上，消耗一个单位时间。

●在墙壁上创建传送门，用枪向上、向下、向左，向右直射向着墙壁。传送门会在被击中的墙的一侧产生。在每一时刻，最多两个传送门可以是活动的。如果在已有两个传送门的基础上再射击创建了一个新的，那么较早创建的门将消失。这个射击消耗的时间可忽略。

●如果她在一个靠近墙的地方，墙上有一个传送门，她可以进入，到达另一个门外的无障碍区域出来，需要消耗一个单位时间。

求到达目的地“F”所需的最少时间


---

---
title: "灰化肥，会挥发"
layout: "post"
diff: 提高+/省选-
pid: P4772
tag: ['广度优先搜索 BFS', '最短路', '状压 DP']
---
# 灰化肥，会挥发
## 题目背景

Farmer Justin 有一大堆会发黑和挥发的灰化肥呢！！！
## 题目描述

在 Farmer Justin 的农场中有许多灰化肥，它们都堆积在A仓库里。为了方便施肥，Farmer Justin 需要修一些公路使得他能用拖拉机把这些灰化肥拉到其他仓库里。由于 Farmer Justin 及其懒惰，所以他只想一次拉完所有的灰化肥送到其他仓库里。但是灰化肥见光易挥发，所以 Farmer Justin 需要尽快把这些灰化肥拉完。现在告诉你Farmer Justin农场的构成地图，请你帮帮他计划一条**从 A 仓库出发**走完所有仓库的方案吧！由于Farmer Justin 非常的讨厌浪费时间，所以你只需要告诉他最短的距离和走过所有农场的顺序。（注意：拖拉机走的时候是四联通的。）
## 输入格式

第一行三个正整数 $R,C,N$ 分别表示地图大小和仓库数量。
下面给出一个 $R$ 行 $C$ 列的地图，其中 `.` 表示空地，可以修建公路；`*` 表示是 Farmer Justin 的农业区，不可以修建公路；用大写字母表示仓库编号。
## 输出格式


第一行一个正整数表示最短的距离。

第二行表示拖拉机走过仓库的方案（由仓库编号组成的字符串）。若有多种方案，输出字典序最小的方案。

数据保证有解。
## 样例

### 样例输入 #1
```
5 5 3
A.**C
*....
B*...
.**..
.....
```
### 样例输出 #1
```
16
ACB
```
## 提示

对于全部数据，$ 1 \leqslant R,C \leqslant 500 $，$ 1 \leqslant N \leqslant 16 $。


---

---
title: "[BJWC2012] 冻结"
layout: "post"
diff: 提高+/省选-
pid: P4822
tag: ['2012', '北京', '图论建模', '最短路']
---
# [BJWC2012] 冻结
## 题目背景

“我要成为魔法少女！”

“那么，以灵魂为代价，你希望得到什么？”

“我要将有关魔法和奇迹的一切，封印于卡片之中„„”

在这个愿望被实现以后的世界里，人们享受着魔法卡片（SpellCard，又名符卡）带来的便捷。

现在，不需要立下契约也可以使用魔法了！你还不来试一试？

比如，我们在魔法百科全书（Encyclopedia of Spells）里用“freeze”作为关键字来查询，会有很多有趣的结果。

例如，我们熟知的 Cirno，她的冰冻魔法当然会有对应的 SpellCard 了。当然，更加令人惊讶的是，居然有冻结时间的魔法，Cirno 的冻青蛙比起这些来真是小巫见大巫了。

这说明之前的世界中有很多魔法少女曾许下控制时间的愿望，比如 Akemi Homura、Sakuya Izayoi、……

当然，在本题中我们并不是要来研究历史的，而是研究魔法的应用。
## 题目描述

我们考虑最简单的旅行问题吧： 现在这个大陆上有 $N$ 个城市，$M$ 条双向的道路。城市编号为 $1$ ~ $N$，我们在 $1$ 号城市，需要到 $N$ 号城市，怎样才能最快地到达呢？

这不就是最短路问题吗？我们都知道可以用 Dijkstra、Bellman-Ford、Floyd-Warshall等算法来解决。

现在，我们一共有 $K$ 张可以使时间变慢 50%的 SpellCard，也就是说，在通过某条路径时，我们可以选择使用一张卡片，这样，我们通过这一条道路的时间 就可以减少到原先的一半。需要注意的是：

1. 在一条道路上最多只能使用一张 SpellCard。
2. 使用一张SpellCard 只在一条道路上起作用。
3. 你不必使用完所有的 SpellCard。

给定以上的信息，你的任务是：求出在可以使用这不超过 $K$ 张时间减速的 SpellCard 之情形下，从城市 $1$ 到城市 $N$ 最少需要多长时间。
## 输入格式

第一行包含三个整数：$N$、$M$、$K$。

接下来 $M$ 行，每行包含三个整数：$A_i$、$B_i$、$Time_i$，表示存在一条  $A_i$ 与 $B_i$ 之间的双向道路，在不使用 SpellCard 之前提下，通过它需要 $Time_i$ 的时间。
## 输出格式

输出一个整数，表示从 $1$ 号城市到 $N$ 号城市的最小用时。
## 样例

### 样例输入 #1
```
4 4 1 
1 2 4 
4 2 6 
1 3 8 
3 4 8 

```
### 样例输出 #1
```
7
```
## 提示

#### 样例 1 解释

在不使用 SpellCard 时，最短路为 $1 \to 2 \to 4$，总时间为 10。现在我们可以使用 1 次 SpellCard，那么我们将通过 $2 \to 4$ 这条道路的时间减半，此时总时间为7。

#### 数据规模与约定

对于 $100\%$ 的数据，保证：

- $1 \leq K \leq N \leq 50$，$M \leq 10^3$。
- $1 \leq A_i,B_i \leq N$，$2 \leq Time_i \leq 2 \times 10^3$。
- 为保证答案为整数，保证所有的 $Time_i$ 均为偶数。
- 所有数据中的无向图保证无自环、重边，且是连通的。


---

---
title: "[USACO18DEC] Fine Dining G"
layout: "post"
diff: 提高+/省选-
pid: P5122
tag: ['2018', 'USACO', '最短路']
---
# [USACO18DEC] Fine Dining G
## 题目描述

漫长的一天结束了，饥困交加的奶牛们准备返回牛棚。

农场由 $N$ 片牧场组成（$2\le N\le 5\times 10^4$），方便起见编号为 $1\dots N$。所有奶牛都要前往位于牧场 $N$ 的牛棚。其他 $N-1$ 片牧场中每片有一头奶牛。奶牛们可以通过 $M$ 条无向的小路在牧场之间移动（$1\le M\le 10^5$）。第i条小路连接牧场 $a_i$ 和 $b_i$，通过需要时间 $t_i$。每头奶牛都可以经过一些小路回到牛棚。

由于饥饿，奶牛们很乐于在他们回家的路上停留一段时间觅食。农场里有 $K$ 个有美味的干草捆，第 $i$ 个干草捆的美味值为 $y_i$。每头奶牛都想要在她回牛棚的路上在某一个干草捆处停留，但是她这样做仅当经过这个干草捆使她回牛棚的时间增加不超过这个干草捆的美味值。注意一头奶牛仅仅“正式地”在一个干草捆处因进食而停留，即使她的路径上经过其他放有干草捆的牧场；她会简单地无视其他的干草捆。
## 输入格式

输入的第一行包含三个空格分隔的整数 $N$，$M$ 和 $K$。以下 $M$ 行每行包含三个整数 $a_i$，$b_i$ 和 $t_i$，表示牧场 $a_i$ 和 $b_i$ 之间有一条需要 $t_i$ 时间通过的小路（$a_i$ 不等于 $b_i$，$t_i$ 为不超过 $10^4$ 的正整数）。

以下 $K$ 行，每行以两个整数描述了一个干草捆：该干草捆所在牧场的编号，以及它的美味值（一个不超过 $10^9$ 的正整数）。同一片牧场中可能会有多个干草捆。
## 输出格式

输出包含 $N-1$ 行。如果牧场 $i$ 里的奶牛可以在回牛棚的路上前往某一个干草捆并且在此进食，则第 $i$ 行为一个整数 $1$，否则为一个整数 $0$。
## 样例

### 样例输入 #1
```
4 5 1
1 4 10
2 1 20
4 2 3
2 3 5
4 3 2
2 7
```
### 样例输出 #1
```
1
1
1
```
## 提示

在这个例子中，牧场 $3$ 里的奶牛可以停留进食，因为她回去的时间仅会增加 $6$（从 $2$ 增加到 $8$），而这个增加量并没有超过干草捆的美味值 $7$。牧场 $2$ 里的奶牛显然可以吃掉牧场 $2$ 里的干草，因为这并不会导致她的最佳路径发生变化。对于牧场 $1$ 里的奶牛是一个有趣的情况，因为看起来她的最佳路径（$10$）可能会因为前去进食而有过大的增加量。然而，确实存在一条路径使得她可以前去干草捆处停留：先到牧场 $4$，然后去牧场 $2$（吃草），然后回到牧场 $4$。


---

---
title: "[CTSC1998] 罗杰游戏"
layout: "post"
diff: 提高+/省选-
pid: P5700
tag: ['动态规划 DP', '图论', '1998', '枚举', '最短路', 'CTSC/CTS']
---
# [CTSC1998] 罗杰游戏
## 题目背景

CTSC1998 D2T1

## 题目描述

罗杰游戏由一张棋盘和罗杰构成。棋盘由很多个小格组成，每个小格上刻有一个数字。其为 $-1$ 或 $0$ 至 $255$ 之间的一个数。罗杰是一个立方体，有六个面，每个面上分别有一个 $1$ 至 $6$ 之间的数字。

我们开始时把罗杰放在棋盘中的一个小格上，然后让其向前、后、左、右四个方向**翻滚**至邻近小格中。

游戏要求经过若干次翻滚后，让罗杰到达指定小格。

**罗杰不得进入标有 $-1$ 的小格，否则游戏结束**。

罗杰每进入一个小格后，将其顶面的数字同该小格的数字相乘，所得结果累加即得到罗杰的旅行费用。

开始时我们能看到罗杰的某些面上的数字，也可以指定当罗杰最终到达目的格时某些面上应出现的数字。对于**不确定的数字**，我们可以在**合法的基础上任意指定**。

**任务一**

罗杰只能向前或向右翻滚。

**任务二**

罗杰可以自由活动。
## 输入格式

输入文件的第一行是数字 $1$ 或 $2$ 。表示是任务一还是任务二。

文件的第二行是两个整数 $M$ 和 $N$ ，给出了棋盘的列数和行数。

接下来的 $N$ 行每行表示棋盘的一行，有 $M$ 个数，依次给出了该行上每列的数。

其后的两行分别给出了罗杰的出发点信息和到达点信息。

每行开始的两个正整数给出了该格子的列号和行号。

接下来的六个数字分别表示了罗杰的顶，底，前、后、左、右各面的数字。 $0$ 表示可以任意指定。


## 输出格式

输出文件的第一行给出罗杰的最小旅行费用。

如果罗杰不可能按要求到达目的地，则输出 $-1$ 。

否则其后每行给出罗杰的旅行情况：

从出发格到目的格，每行表示了罗杰的一个位置，

依次给出罗杰的当前旅行费用、所在格的列编号、行编号，以及罗杰6个面上的数字。

注意这时你的程序必须给出罗杰的完整信息，即各面上的数字不能为 $0$。
## 样例

### 样例输入 #1
```
2 
10 10
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1
1 1 1 9 8 7 6 5 4 1
1 1 9 8 7 6 5 4 1 1
1 1 8 7 6 5 4 1 1 1
1 1 7 6 5 4 1 1 1 1
1 1 6 5 4 1 1 1 1 1
1 1 5 4 1 1 1 1 1 1
1 1 4 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
3 3 0 0 0 0 0 0
8 8 0 0 0 0 0 0
```
### 样例输出 #1
```
44
0 3 3 6 5 3 1 2 4
3 3 2 3 1 5 6 2 4
5 4 2 2 4 5 6 1 3
6 5 2 1 3 5 6 4 2
10 6 2 4 2 5 6 3 1
13 7 2 3 1 5 6 2 4
15 8 2 2 4 5 6 1 3
16 9 2 1 3 5 6 4 2
20 10 2 4 2 5 6 3 1
26 10 3 6 5 4 2 3 1
28 10 4 2 4 6 5 3 1
29 9 4 1 3 6 5 2 4
34 9 5 5 6 1 3 2 4
38 8 5 4 2 1 3 5 6
41 8 6 3 1 4 2 5 6
43 8 7 2 4 3 1 5 6
44 8 8 1 3 2 4 5 6
```
## 提示

【数据范围】

$M \le 40$ , $N \le 40$  。


---

---
title: "[JSOI2015] 地铁线路"
layout: "post"
diff: 提高+/省选-
pid: P6096
tag: ['2015', '各省省选', '江苏', '最短路']
---
# [JSOI2015] 地铁线路
## 题目描述

JSOI 王国的地铁又涨价了！正在 JSOI 旅游的 JYY 非常不开心。这次票价改革后，乘客并不是按照乘坐的距离收费，而是按照换乘次数进行收费的！JYY 也要按此更新他的线路搜索软件了。JYY 心想，在支付同样票价的前提下，岂不
是坐的站数越多，自己就赚的越多嘛！于是 JYY 希望开发一个线路搜索软件，使得自己总能够“赚”的最多！

JSOI 地铁一共有 $N$ 条线路 $S$ 个车站。第 $i$ 条地铁线路包含 $L_i$ 个站。所有地铁线路都是一条从首发站到终点站的直线型线路（不存在例如北京地铁 2 号线或者 10 号线那样奇葩的环线）。同时，每一条地铁线路都是双向运行的。如果有不同的线路经过同一个地铁站，那么乘客就可以在那个地铁站进行换乘。根据 JSOI 地铁的最新收费方式，每当乘客进入一列正在运行的地铁列车，都需要支付 $1$ 的费用。因此，假设乘客一共换乘了 $x$ 次，那么就需要总共支付 $x+1$ 的乘车费用。由于地铁线路都是双向运行的，因此在任意一站都可以换乘该线地铁反方向运行的列车。不过，需要注意的是，即使是换乘同样线路的反方向列车，也是需要付费的（因为总是需要先下车，再重新上车的）。

JYY现在要从 $A$ 站坐地铁前往 $B$ 站。假设对于任意一条地铁线路，相邻两站间地铁的运行时间均为 $1$ 分钟，并且列车停站和换乘均不耗时间，JYY想知道

1. 他最少需要支付的票价是多少钱；
2. 在支付最少票价的前提下，他最多可以乘坐多少分钟的地铁。
## 输入格式

第一行包含两个正整数 $N$ 和 $S$。

第二行包含 $S$ 个由空格隔开的字符串，表示 $S$ 个站点的站名。

接下来 $N$ 行，每行描述一条地铁线路。对于其中第 $i$ 行，首先包含一个正整数 $L_i$，接下来 $L_i$ 个字符串，表示这条地铁线路上的站点名称。一条线路允许多次停靠同一个站点。

第 $N+3$ 行，包含两个不同的字符串 $A$ 和 $B$，表示 JYY 目前在 $A$ 站，希望坐地铁前往 $B$ 站。
## 输出格式

第一行包含一个整数 $C$，表示 JYY 最少需要支付的乘车费用。

第二行包含一个整数 $T$，表示 JYY 在花费 $C$ 的前提下，可以乘坐地铁的最长时间。

如果不存在两个站点之间的路线，第一行输出`-1`，第二行输出 `0`。
## 样例

### 样例输入 #1
```
2 5
A B C D E
4 A B C D
3 C D E
A D
```
### 样例输出 #1
```
1
3
```
## 提示

对于 $100\%$ 的数据，$2\leq N\leq 4\times 10^5$，$S\leq 3\times 10^5$，$\sum L_i\leq 8\times 10^5$。

保证输入所有字符串的长度不超过 $40$，且仅包含字母、数字以及横线 `-`。


---

---
title: "[eJOI 2019] Awesome Arrowland Adventure"
layout: "post"
diff: 提高+/省选-
pid: P6233
tag: ['2019', 'eJOI（欧洲）', '最短路']
---
# [eJOI 2019] Awesome Arrowland Adventure
## 题目描述

你现在在一个大小为 $m$ 行（行编号从 $0$ 开始，从上往下一直到 $m-1$） $n$ （列编号从 $0$ 开始，从左往右一直到 $n-1$）列的矩阵中。你的初始位置为 $(0,0)$。（$(r,c)$ 表示矩阵中第 $r$ 行，第 $c$ 列的位置）

你需要走到位置 $(m-1,n-1)$ 处。这个矩阵非常神奇——在矩阵的某些格子上有一个箭头。 箭头只可能有四种方向：北（向上），东（向右），南（向下），西（向左）。箭头分布在整个矩阵之上，形成了箭头矩阵。

当你在某一个位置时，假如这个位置不在矩形（左上角 $(0,0)$，右下角 $(m-1,n-1)$）范围内或这个位置没有箭头，那么你会一直停留于此，永远无法到达终点。如果此处有箭头，那么你将会向这个箭头的方向走一格。

但显然，你不一定能够在初始的箭头矩阵上找到一条从 $(0,0)$ 到 $(m-1,n-1)$ 的路径。为了找到这样一条路径，你可以一次将箭头矩阵中某一个箭头 ***顺时针*** 旋转 $90$ 度。通过几次的旋转，你可能会找到一条路径。

请你判断是否可以通过旋转来得到一条从 $(0,0)$ 到 $(m-1,n-1)$ 的路径，如果有，求出最小需要的旋转次数。
## 输入格式

第一行：两个整数 $m,n$ ，表示矩阵的大小；

接下来 $m$ 行，每行一个长度为 $n$ 的字符串，表示箭头矩阵中这一行的箭头的信息。字符串只可能包含 $5$ 种字符：`W`，`E`，`N`，`S`，`X`。它们分别表示：西，东，北，南，没有箭头。
## 输出格式

如果没有可以找到路径的旋转方案，输出 ```-1```；

如果有，输出一个整数表示需要旋转的最少次数。
## 样例

### 样例输入 #1
```
3 3
EES
SSW
ESX
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 3
EES
SSW
EEX
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
3 4
EXES
WSNS
XNNX
```
### 样例输出 #3
```
4
```
## 提示

#### 样例解释

【样例 1 解释】
- 一个可行的解是，将位置 $(1,2)$ 的 ```W``` 旋转 $3$ 次变成 ```S```。

【样例 2 解释】
- 不需要任何旋转就可以。

【样例 3 解释】
- 在 $(0,0)$ 处旋转 $1$ 次，在 $(1,0)$ 处旋转 $2$ 次，在 $(2,1)$ 处旋转 $1$ 次。

---
#### 数据规模与约定

**本题采用多测试点捆绑测试，共有 $5$ 个子任务**。

- Subtask 1（10 points）：$m=1$，且输入的字符矩阵只包含 ```E``` 或 ```X```。
- Subtask 2（12 points）：$m=1$。
- Subtask 3（12 points）：$n=m=3$。
- Subtask 4（16 points）：$m=2$。
- Subtask 5（50 points）：无特殊限制。

对于 全部的测试点，保证 $1\le m,n\le 500$。

---

#### 说明

原题来自：[eJOI2019](https://www.ejoi2019.si) Problem F [Awesome Arrowland Adventure](https://www.ejoi2019.si/static/media/uploads/tasks/adventure-isc(1).pdf)

题面翻译：@[```_Wallace_```](https://www.luogu.com.cn/user/61430)（如果觉得这个翻译令人谔谔，欢迎提供新翻译）


---

---
title: "[USACO05MAR] Ombrophobic Bovines 发抖的牛"
layout: "post"
diff: 提高+/省选-
pid: P6768
tag: ['2005', '二分', 'USACO', '最短路']
---
# [USACO05MAR] Ombrophobic Bovines 发抖的牛
## 题目描述

FJ 的牛们非常害怕淋雨，那会使他们瑟瑟发抖。他们打算安装一个下雨报警器，并且安排了一个撤退计划。他们需要计算最少的让所有牛进入雨棚的时间。  
牛们在农场的 $F$ 个田地上吃草。有 $P$ 条双向路连接着这些田地。路很宽，无限量的牛可以通过。田地上有雨棚，雨棚有一定的容量，牛们可以瞬间从这块田地进入这块田地上的雨棚。  
请计算最少的时间，让每只牛都进入雨棚。
## 输入格式

第 $1$ 行：两个整数 $F$ 和 $P$；  
第 $2$ 到 $F+1$ 行：第 $i+1$ 行有两个整数描述第 $i$ 个田地，第一个表示田地上的牛数，第二个表示田地上的雨棚容量。两个整数都在 $0$ 和 $1000$ 之间。  
第 $F+2$ 到 $F+P+1$ 行：每行三个整数描述一条路，分别是起点终点，及通过这条路所需的时间（在 $1$ 和 $10^9$ 之间）。
## 输出格式

一个整数，表示最少的时间。如果无法使牛们全部进入雨棚，输出 $-1$。
## 样例

### 样例输入 #1
```
3 4
7 2
0 4
2 6
1 2 40
3 2 70
2 3 90
1 3 120

```
### 样例输出 #1
```
110
```
## 提示

对于 $100\%$ 的数据：$1\le F\le 200$，$1\le P\le 1500$。


---

---
title: "[JOI 2020 Final] オリンピックバス"
layout: "post"
diff: 提高+/省选-
pid: P6880
tag: ['2020', '最短路', 'JOI（日本）']
---
# [JOI 2020 Final] オリンピックバス
## 题目描述

给定一个 $N$ 点 $M$ 边的有向图，每条边从 $U_i$ 指向 $V_i$，经过这条边的代价为 $C_i$。

点编号为 $1$ 到 $N$。

我们可以翻转一条边，即让他从 $U_i$ 指向 $V_i$ 变为从 $V_i$ 指向 $U_i$，这时会有 $D_i$ 的代价产生。

你要从点 $1$ 到点 $N$，再从点 $N$ 回到点 $1$，你想知道，通过翻转一条边，或者不翻转，能得到的最小代价和为多少？
## 输入格式

第一行两个整数 $N,M$ 代表点数和边数。

接下来 $M$ 行每行四个整数 $U_i,V_i,C_i,D_i$ 代表一条边。
## 输出格式

一行一个整数代表最小代价和。无解输出 $-1$。
## 样例

### 样例输入 #1
```
4 5
1 2 4 4
1 3 2 1
4 3 1 2
4 1 6 1
2 4 2 5
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
4 10
1 2 4 4
1 2 4 4
1 3 2 1
1 3 2 1
4 3 1 2
4 3 1 2
4 1 6 1
4 1 6 1
2 4 2 5
2 4 2 5
```
### 样例输出 #2
```
10
```
### 样例输入 #3
```
4 4
1 2 0 4
1 3 0 1
4 3 0 2
4 1 0 1
```
### 样例输出 #3
```
2
```
### 样例输入 #4
```
4 5
1 2 4 4
1 3 2 4
4 3 1 5
4 1 6 1
2 4 2 5
```
### 样例输出 #4
```
12
```
### 样例输入 #5
```
4 5
2 1 4 4
1 3 2 1
4 3 1 2
4 3 6 1
2 4 2 5
```
### 样例输出 #5
```
-1
```
## 提示

### 样例 1 解释

最优解为翻转第二条边，总代价为：

- 翻转的代价 $1$。
- 从点 $1$ 到点 $N$ 再返回的最短路径 $1 \to 2 \to 4 \to 3 \to 1$，代价为 $4+2+1+2=9$。

### 样例 4 解释

不一定需要翻转某条边。

### 样例 5 解释

从点 $4$ 到点 $3$ 的边有两条。

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$M \le 1000$。
- Subtask 2（11 pts）：$M$ 为偶数，且 $U_{2i}=U_{2i-1}$，$V_{2i}=V_{2i-1}$，$C_{2i}=C_{2i-1}$。
- Subtask 3（21 pts）：$C_i=0$。
- Subtask 4（63 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $2 \le N \le 200$。
- $1 \le M \le 5 \times 10^4$。
- $1 \le U_i \le N$。
- $1 \le V_i \le N$。
- $U_i \ne V_i$。
- $0 \le C_i \le 10^6$。
- $0 \le D_i \le 10^9$。

### 说明

翻译自 [第 19 回日本情報オリンピック　本選](https://www.ioi-jp.org/joi/2019/2020-ho/index.html) [D オリンピックバス](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t4.pdf)。


---

---
title: "[COCI 2015/2016 #3] DOMINO"
layout: "post"
diff: 提高+/省选-
pid: P7231
tag: ['2015', '网络流', '最短路', '费用流', '前缀和', 'COCI（克罗地亚）']
---
# [COCI 2015/2016 #3] DOMINO
## 题目背景

「誕生日おめでとう！!」

小 M 收到了他女朋友的生日祝福和一份礼物。
## 题目描述

小 M 的女朋友送小 M 了一张 $n \times n$ 的表格作为生日礼物，在表格的每个单元格中都写有一个非负整数。

不幸的是，有些单元格里数字太大了，小 M 不喜欢它们，所以他将在表格上面放置 $k$ 张骨牌，将覆盖那些数字太大的单元格。

更准确地说，小 M 按照以下规则放置骨牌。

- 骨牌为 $1\times 2$ 的矩形，不能拆开放置。
- 骨牌不重叠（但可以接触）。
- 所有可见（未覆盖）字段的总和需要尽可能的小。

您的任务是确定最小可见区域的数字的总和。数据保证可防止 $k$ 个骨牌且无重叠。
## 输入格式

第一行，$2$ 个正整数 $n,k$，$n$ 表示表格的尺寸， $k$ 表示骨牌的数量。

接下来 $n$ 行，每一行都有 $n$ 个整数 $a_i$。这些 $n \times n$ 的数字的数字描述了 Mirko 的表格。
## 输出格式

一行一个整数，最小可见区域的数字的总和。
## 样例

### 样例输入 #1
```
3 1
2 7 6
9 5 1
4 3 8

```
### 样例输出 #1
```
31
```
### 样例输入 #2
```
4 2
1 2 4 0
4 0 5 4
0 3 5 1
1 0 4 1

```
### 样例输出 #2
```
17
```
## 提示

#### 数据规模及约定
对于 $100\%$ 的数据，$1\le n \le 2 \times 10 ^ 3$，$1\le k \le 8$，$0 \le a_i \le 10 ^ 3$。

#### 说明
翻译自 [COCI 2015-2016 #3 F DOMINO](https://hsin.hr/coci/archive/2015_2016/contest3_tasks.pdf)，满分 160。


---

---
title: "[USACO21JAN] Telephone G"
layout: "post"
diff: 提高+/省选-
pid: P7297
tag: ['USACO', '2021', '图论建模', '最短路']
---
# [USACO21JAN] Telephone G
## 题目描述

Farmer John 的 N 头奶牛，编号为 $1…N$，站成一行（$1≤N≤5⋅10^4$）。第 $i$ 头奶牛的品种编号为 $b_i$，范围为 $1\dots K$，其中 $1≤K≤50$。奶牛们需要你帮助求出如何最优地从奶牛 $1$ 传输一条信息到奶牛 $N$。

从奶牛 $i$ 传输信息到奶牛 $j$ 花费时间 $|i-j|$。然而，不是所有品种的奶牛都愿意互相交谈，如一个 $K\times K$ 的方阵 $S$ 所表示，其中如果一头品种 $i$ 的奶牛愿意传输一条信息给一头品种 $j$ 的奶牛，那么 $S_{ij}=1$，否则为 $0$。不保证 $S_{ij}=S_{ji}$，并且如果品种 $i$ 的奶牛之间不愿意互相交流时可以有 $S_{ii}=0$。

请求出传输信息所需的最小时间。 
## 输入格式

输入的第一行包含 $N$ 和 $K$。

下一行包含 $N$ 个空格分隔的整数 $b_1,b_2,\dots,b_N$。

以下 $K$ 行描述了方阵 $S$。每行包含一个由 $K$ 个二进制位组成的字符串，从上往下第 $i$ 个字符串的第 $j$ 位为 $S_{ij}$。 
## 输出格式

输出一个整数，为需要的最小时间。如果不可能从奶牛 $1$ 传输信息至奶牛 $N$，输出 $-1$。 
## 样例

### 样例输入 #1
```
5 4
1 4 2 3 4
1010
0001
0110
0100
```
### 样例输出 #1
```
6
```
## 提示

最优传输序列为 $1\to 4\to 3\t 5$。总时间为 $|1-4|+|4-3|+|3-5|=6$。

#### 测试点性质：

 - 测试点 1-5 满足 $N≤1000$。
 - 测试点 6-13 没有额外限制。

供题：Dhruv Rohatgi 


---

---
title: "[NOI Online 2021 入门组] 重力球"
layout: "post"
diff: 提高+/省选-
pid: P7473
tag: ['图论', '2021', '最短路', 'NOI Online']
---
# [NOI Online 2021 入门组] 重力球
## 题目描述

“重力球”游戏在一块 $n\times n$ 的正方形区域中进行，记从上往下第 $i$ 行，从左往右第 $j$ 列的位置为 $(i,j)$。

正方形区域中存在 $m$ 个障碍，第 $i$ 个障碍占据位置 $(x_i,y_i)$，此外，正方形区域的边界外都是障碍。

现在有两个小球，位置分别是 $(a,b)$ 和 $(c,d)$，在游戏中你可以进行如下操作：

- 指定上、下、左、右中的一个方向，将重力方向“切换”为这个方向。此时两个小球会同时向这个方向移动，直到碰到障碍。

你要用最少的操作次数使得两个小球到达同一个位置。

现有 $q$ 局游戏，每局游戏中只有小球的初始位置不同，而障碍位置是不变的，你需要对每局游戏都求出最小操作次数，或报告无解。
## 输入格式

第一行包含三个整数 $n,m,q$，分别表示矩形区域大小，障碍个数和游戏局数。

接下来 $m$ 行，每行包含两个整数 $x_i,y_i$，表示位置 $(x_i,y_i)$ 上有一个障碍。数据保证所有障碍所处的位置互不相同。

接下来 $q$ 行，每行四个整数 $a,b,c,d$，表示一局游戏中两个小球的初始位置，保证初始位置不存在障碍。
## 输出格式

输出共 $q$ 行，第 $i$ 行输出一个整数表示第 $i$ 局游戏需要的最小操作次数，如果无解则输出 `-1`。
## 样例

### 样例输入 #1
```
4 4 3
2 2
2 4
3 2
4 4
1 3 4 3
2 1 2 1
1 2 3 4
```
### 样例输出 #1
```
1
0
3
```
## 提示

### 样例 $1$ 解释

该样例中障碍分布如图中红叉所示。

第一组询问中只需将重力改向上（或改向下）即可使两球同时到达。

第二组询问中两球已经在同一位置故不需操作。

第三组询问中改变3 次重力的方向，依次改为向左、向下、向左，小球移动路线分别如图中粉色、橙色、棕色线所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7nngrov0.png)
### 数据范围与提示
对于 $20\%$ 的数据：$n,m\le 2$。

对于 $50\%$ 的数据：$n,m\le30$。

对于另外 $30\%$ 的数据：$q=1$。

对于 $100\%$ 的数据：$1\le n,m\le250，1\le q\le10^5，1\le x_i,y_i,a,b,c,d\le n$。

数据由 [SSerxhs](https://www.luogu.com.cn/user/29826) 提供。

数据参考了 小喵喵不喜欢计算几何 2020 ICPC 区域赛（南京）A 题的构造方案，在此表示感谢。


---

---
title: "[JDWOI-2] 抢救实验数据"
layout: "post"
diff: 提高+/省选-
pid: P7733
tag: ['O2优化', '最短路']
---
# [JDWOI-2] 抢救实验数据
## 题目背景

某大型实验中心的一个实验室发生了毒气泄露，现在实验员想要抢救实验数据。
## 题目描述

实验中心可以看做一个 $n$ 个点 $m$ 条边的无向联通图。  
所有实验员每秒可以走到一个相邻的实验室并**收集**其中的数据，毒气每秒会蔓延到所有的相邻实验室。
当一个实验员**回到了大厅 $s$**，我们称他**抢救**了数据。  
实验员不能进入有毒气的实验室（如果他和毒气在同一秒进入实验室也不行）。  
**大厅周围有严格的保护措施，不会被毒气蔓延。（具体可以参考样例二）**  
现在所有实验员都在大厅 $s$，毒气泄露的实验室为点 $t$。假如有**足够多**的实验员同时出发，请问最多能抢救多少个实验室的数据？
## 输入格式

第一行两个正整数 $n,m$，表示实验中心的点数和边数。  
第二至 $m+1$ 行每行两个正整数 $u,v$，代表 $u,v$ 实验室之间有一条边。  
第 $m+2$ 行两个正整数 $s,t$，表示大厅和毒气泄露点。
## 输出格式

一行一个整数，表示最多能抢救多少个的实验室的数据。
## 样例

### 样例输入 #1
```
4 3
1 2
2 3
3 4
1 4
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
6 7
1 2
2 3
3 1
4 5
5 6
6 4
1 4
1 4
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
15 14
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
3 11
11 12
12 13
13 14
14 15
1 10
```
### 样例输出 #3
```
6
```
## 提示

**请注意常数因子带来的程序效率上的影响。**

【样例解释一】  
只有 2 号实验室可以到达并回来。

【样例解释二】  
因为大厅是坚不可摧的，所以 5,6 两个实验室会被毒气蔓延到，而 2,3 两个实验室永远不会被蔓延到。

【样例解释三】  
可以被抢救的点为：2,3,4,5,11,12。

【数据范围】  
**本题采用捆绑测试**。  
对于 $10\%$ 的数据，$2 \leq n,m \leq 20$；  
对于 $30\%$ 的数据，$2 \leq n \leq 2000,1 \leq m \leq 10000$；  
对于 $70\%$ 的数据，$2 \leq n \leq 2 \times 10^5$；  
对于 $100\%$ 的数据，$2 \leq n,m \leq 5 \times 10^6$。

由于读入量很大，这里提供 std 使用的快读模板（提交时需要选择 C++11 及以上)
```cpp
char gc() {
  static char now[1 << 20], *S, *T;
  if (T == S) {
    T = (S = now) + std::fread(now, 1, 1 << 20, stdin);
    if (T == S) return EOF;
  }
  return *S++;
}
template <typename T>
void Read(T &x) {
  x = 0;
  char c = gc();
  while (c < '0' || c > '9') c = gc();
  x = c - '0';
  while ((c = gc()) >= '0' && c <= '9') x = x * 10 + c - '0';
}
template <typename T, typename... Args>
void Read(T &x, Args &... args) {
  Read(x);
  Read(args...);
}
```
使用方法：`Read(n, m)` 或 `Read(x, y, z)` 等，可以读入任意个数，但是不能与 `std::cin` 和 `std::scanf` 一起使用。读入完成后 Windows 系统按 Ctrl+Z，Linux 系统按 Ctrl+D 结束。


---

---
title: "[POI 2003] Sums"
layout: "post"
diff: 提高+/省选-
pid: P8060
tag: ['2003', 'POI（波兰）', '最短路', '中国剩余定理 CRT']
---
# [POI 2003] Sums
## 题目描述

我们给定一个整数集合 $A$。考虑一个非负整数集合 $A'$，所有属于 $A'$ 的集合的数 $x$ 满足当且仅当能被表示成一些属于 $A$ 的元素的和（数字可重复）。

比如，当 $A = \{2,5,7\}$，属于 $A'$ 的数为：$0$（$0$ 个元素的和），$2$，$4$（$2 + 2$）和 $12$（$5 + 7$ or $7 + 5$ or $2 + 2 + 2 + 2 + 2 + 2$）；但是元素 $1$ 和 $3$ 不属于 $A'$。
## 输入格式

第一行有一个整数 $n$，代表集合 $A$ 的元素个数。接下来每行一个数 $a_i$ 描述一个元素。$A = \{a_1,a_2,...,a_n\}$。

接下来一个整数 $k$，然后每行一个整数，分别代表 $b_1,b_2,...,b_k$。
## 输出格式

输出 $k$ 行。如果 $b_i$ 属于 $A'$，第 $i$ 行打印 `TAK`，否则打印 `NIE`。
## 样例

### 样例输入 #1
```
3
2
5
7
6
0
1
4
12
3
2
```
### 样例输出 #1
```
TAK
NIE
TAK
TAK
NIE
TAK
```
## 提示

对于所有数据，$1 \le n \le 5 \times 10^3$，$1 \le k \le 10^4$，$1 \le a_1 < a_2 < ... < a_n \le 5 \times 10^4$，$0 \le b_i \le 10^9$。


---

---
title: "[蓝桥杯 2020 国 AB] 出租车"
layout: "post"
diff: 提高+/省选-
pid: P8731
tag: ['2020', '图论建模', '最短路', '蓝桥杯国赛']
---
# [蓝桥杯 2020 国 AB] 出租车
## 题目背景

小蓝在 $L$ 市开出租车。
## 题目描述

$L$ 市的规划很规整，所有的路都是正东西向或者正南北向的，道路都可以看成直线段。东西向的道路互相平行, 南北向的道路互相平行，任何一条东西向道路垂直于任何一条南北向道路。

从北到南一共有 $n$ 条东西向道路，依次标号为 $H_{1}, H_{2}, \cdots, H_{n}$ 。从西到东 一共有 $m$ 条南北向的道路，依次标号为 $S_{1}, S_{2}, \cdots, S_{m}$ 。

每条道路都有足够长，每一条东西向道路和每一条南北向道路都相交，$H_{i}$ 与 $S_{j}$ 的交叉路口记为 $(i, j)$ 。

从 $H_{1}$ 和 $S_{1}$ 的交叉路口 $(1,1)$ 开始，向南遇到的路口与 $(1,1)$ 的距离分别 是 $h_{1}, h_{2}, \cdots, h_{n-1}$，向东遇到路口与 $(1,1)$ 的距离分别是 $w_{1}, w_{2}, \cdots, w_{m-1}$ 。

道路的每个路口都有一个红绿灯。

时刻 $0$ 的时候，南北向绿灯亮，东西向红灯亮，南北向的绿灯会持续一段时间（每个路口不同)，然后南北向变成红灯，东西向变成绿灯，持续一段时间后，再变成南北向绿灯，东西向红灯。

已知路口 $(i, j)$ 的南北向绿灯每次持续的时间为 $g_{i j}$, 东西向的绿灯每次持续的时间为 $r_{i j}$, 红绿灯的变换时间忽略。

当一辆车走到路口时，如果是绿灯，可以直行、左转或右转。如果是红灯，可以右转，不能直行或左转。如果到路口的时候刚好由红灯变为绿灯，则视为看到绿灯；如果刚好由绿灯变为红灯，则视为看到红灯。

每段道路都是双向道路，道路中间有隔离栏杆，在道路中间不能掉头, 只能在红绿灯路口掉头。掉头时不管是红灯还是绿灯都可以直接掉头。掉头的时间可以忽略。

小蓝时刻 $0$ 从家出发。今天，他接到了 $q$ 个预约的订单，他打算按照订单 的顺序依次完成这些订单，就回家休息。中途小蓝不准备再拉其他乘客。小蓝的家在两个路口的中点，小蓝喜欢用 $x_{1}, y_{1}, x_{2}, y_{2}$ 来表示自己家的位 置, 即路口 $\left(x_{1}, y_{1}\right)$ 到路口 $\left(x_{2}, y_{2}\right)$ 之间的道路中点的右侧, 保证两个路口相邻 (中间没有其他路口)。请注意当两个路口交换位置时，表达的是路的不同两边，路中间有栏杆，因此这两个位置实际要走比较远才能到达。

小蓝的订单也是从某两个路口间的中点出发，到某两个路口间的中点结束。小蓝必须按照给定的顺序处理订单，而且一个时刻只能处理一个订单，不能图省时间而同时接两位乘客，也不能揷队完成后面的订单。

小蓝只对 $L$ 市比较熟，因此他只会在给定的 $n$ 条东西向道路和 $m$ 条南北向道路上行驶，而且不会驶出 $H_{1}, H_{n}, S_{1}, S_{m}$ 这几条道路所确定的矩形区域 (可 以到边界。

小蓝行车速度一直为 $1$，乘客上下车的时间忽略不计。

请问，小蓝最早什么时候能完成所有订单回到家。
## 输入格式

输入第一行包含两个整数 $n, m$，表示东西向道路的数量和南北向道路的数 量。

第二行包含 $n-1$ 个整数 $h_{1}, h_{2}, \cdots, h_{n-1}$ 。

第三行包含 $m-1$ 个整数 $w_{1}, w_{2}, \cdots, w_{m-1}$ 。

接下来 $n$ 行, 每行 $m$ 个整数，描述每个路口南北向绿灯的时间，其中的第 $i$ 行第 $j$ 列表示 $g_{i j}$ 。

接下来 $n$ 行, 每行 $m$ 个整数，描述每个路口东西向绿灯的时间，其中的第 $i$ 行第 $j$ 列表示 $r_{i j}$ 。

接下来一行包含四个整数 $x_{1}, y_{1}, x_{2}, y_{2}$，表示小蓝家的位置在路口 $\left(x_{1}, y_{1}\right)$ 到路口 $\left(x_{2}, y_{2}\right)$ 之间的道路中点的右侧。

接下来一行包含一个整数 $q$，表示订单数量。

接下来 $q$ 行，每行描述一个订单，其中第 $i$ 行包含八个整数 $x_{i 1}, y_{i 1}, x_{i 2}, y_{i 2}$，$x_{i 3}, y_{i 3}, x_{i 4}, y_{i 4}$，表示第 $i$ 个订单的起点为路口 $\left(x_{i 1}, y_{i 1}\right)$ 到路口 $\left(x_{i 2}, y_{i 2}\right)$ 之间的道 路中点的右侧，第 $i$ 个订单的终点为路口 $\left(x_{i 3}, y_{i 3}\right)$ 到路口 $\left(x_{i 4}, y_{i 4}\right)$ 之间的道路中 点的右侧。 
## 输出格式

输出一个实数，表示小蓝完成所有订单最后回到家的最早时刻。四舍五入保留一位小数。
## 样例

### 样例输入 #1
```
2 3
200
100 400
10 20 10
20 40 30
20 20 20
20 20 20
2 1 1 1
1
2 2 1 2 1 2 1 3
```
### 样例输出 #1
```
1620.0
```
## 提示

**【样例说明】**

蓝有一个订单, 他的行车路线如下图所示。其中 $\mathrm{H}$ 表示他家的位置, $\mathrm{S}$ 表示订单的起点, $\mathrm{T}$ 表示订单的终点。小小明在最后回家时要在直行的红绿灯路 口等绿灯, 等待时间为 $20$。 

![](https://luogu.oss-cn-hangzhou.aliyuncs.com/upload/vjudge_pic/lanqiao/2022_09_30_334c51de49a3a8e7ba1bg-15.jpg)

**【评测用例规模与约定】**

对于 $20 \%$ 的评测用例, $1 \leq n, m \leq 5,1 \leq q \leq 10$ 。

对于 $50 \%$ 的评测用例, $1 \leq n, m \leq 30,1 \leq q \leq 30$ 。

对于所有评测用例, $1 \leq n, m \leq 100,1 \leq q \leq 30,1 \leq h_{1}<h_{2}<\cdots<h_{n-1} \leq$ $100000,1 \leq w_{1}<w_{2}<\cdots<w_{m-1} \leq 100000,1 \leq g_{i j} \leq 1000,1 \leq r_{i j} \leq 1000$, 给定的路口一定合法。 


---

---
title: "[THUPC 2023 决赛] 百合"
layout: "post"
diff: 提高+/省选-
pid: P9377
tag: ['2023', 'O2优化', '最短路', 'THUPC']
---
# [THUPC 2023 决赛] 百合
## 题目背景

葡萄藤上开不出百合花。
## 题目描述

你落在一个巨大的葡萄架上，上面一共有 $2^k$ 朵百合花和 $m$ 条葡萄藤。其中，百合花编号为 $0$ 到 $2^k-1$ 的整数，第 $i$ 条葡萄藤连接了编号为 $x_i, y_i$ 的百合花。

你可以花费 $c_i$ 的时间通过第 $i$ 条葡萄藤，也就是从 $x_i$ 走到 $y_i$，或者反过来；还可以花费 $a_k$ 的时间从 $x$ 闪现到 $y$，其中 $x, y$ 是任意两朵百合花，$k$ 是它们在二进制表示下不同的比特数。例如，$3$ 的二进制表示是 $011$，$5$ 的二进制表示是 $101$，它们有两位不同，因此从 $3$ 闪现到 $5$ 花费的时间是 $a_2$。

假设你恰好落在编号为 $s$ 的百合花上，求从 $s$ 出发到每一朵百合花所需要的最短时间。
## 输入格式

第一行包含三个正整数 $k,m,s$，其含义如题目描述。

第二行包含 $k$ 个非负整数 $a_i$，表示通道花费的时间。

第 $3$ 至第 $(m+2)$ 行每行三个非负整数 $x_i,y_i,c_i$。
## 输出格式

输出一行 $2^k$ 个数 $D_i$（$0 \leq i \leq 2^k-1$），空格隔开，其中 $D_i$ 表示从 $s$ 到 $i$ 的最短时间。
## 样例

### 样例输入 #1
```
3 6 2
17 14 11 
0 2 3
4 2 9
2 2 1
2 2 6
7 0 5
4 2 9

```
### 样例输出 #1
```
3 14 0 17 9 11 17 8

```
## 提示

**【数据范围】**

对于所有测试数据，$1 \le k \leq 17$，$1 \le m \leq 2 \times 10^5$，$0 \leq s,x_i,y_i \leq 2^k - 1$，$0 \le a_i, c_i \leq 2^{30} - 1$。

**【题目来源】**


来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）决赛。

题解等资源可在 [https://github.com/THUSAAC/THUPC2023](https://github.com/THUSAAC/THUPC2023) 查看。


---

---
title: "[POI 2020/2021 R3] Droga do domu"
layout: "post"
diff: 提高+/省选-
pid: P9402
tag: ['图论', '2020', 'POI（波兰）', '图论建模', '最短路']
---
# [POI 2020/2021 R3] Droga do domu
## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Droga do domu](https://szkopul.edu.pl/problemset/problem/ZfS_tobZ_7xdR6D5s6Tegur3/statement/)。

d1t1。
## 题目描述

$n$ 个点，$m$ 条边，无重边自环，边有长度。

$1$ 号点是学校，$n$ 号点是家。

$s$ 条公交线路。公交逢点必停，且一个点不会停两次。在一条边上行驶的时间就是它的长度。给定了第一班公交发车时间和发车间隔。

在时刻 $t$ 从学校出发，至多换乘 $k$ 次，求最早什么时候到家。

只计算路上时间和等车时间。换乘时间不计。
## 输入格式

第一行：五个整数 $n,m,s,k,t$。

接下来 $m$ 行：每行三个整数 $a,b,c$，表示有一条边连接 $a,b$，长度为 $c$。

接下来 $2s$ 行：每两行描述一条公交线路：

- 第一行三个整数 $l,x,y$，表示它共停靠 $l$ 个点，第一班在时刻 $x$ 发车，每两班之间时间间隔为 $y$。
- 第二行 $l$ 个整数 $v_1,\dots,v_l$，依次为它停靠的 $l$ 个点。
## 输出格式

一行一个整数，答案。

如果不能到家，那么输出一行一个字符串 `NIE`。
## 样例

### 样例输入 #1
```
4 4 2 1 1
1 2 2
2 3 4
1 3 3
4 3 2
4 0 10
1 2 3 4
3 2 7
1 3 2

```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
10 45 17 10 123
1 2 1
1 3 100
1 4 100
1 5 100
1 6 100
1 7 100
1 8 100
1 9 100
1 10 100
2 3 1
2 4 100
2 5 100
2 6 100
2 7 100
2 8 100
2 9 100
2 10 100
3 4 1
3 5 100
3 6 100
3 7 100
3 8 100
3 9 100
3 10 100
4 5 1
4 6 100
4 7 100
4 8 100
4 9 100
4 10 100
5 6 1
5 7 100
5 8 100
5 9 100
5 10 100
6 7 1
6 8 100
6 9 100
6 10 100
7 8 1
7 9 100
7 10 100
8 9 1
8 10 100
9 10 1
2 0 1
1 2
2 0 1
1 3
2 0 1
2 3
2 0 1
2 4
2 0 1
3 4
2 0 1
3 5
2 0 1
4 5
2 0 1
4 6
2 0 1
5 6
2 0 1
5 7
2 0 1
6 7
2 0 1
6 8
2 0 1
7 8
2 0 1
7 9
2 0 1
8 9
2 0 1
8 10
2 0 1
9 10

```
### 样例输出 #2
```
132
```
### 样例输入 #3
```
见附件
```
### 样例输出 #3
```
1000000102
```
### 样例输入 #4
```
见附件
```
### 样例输出 #4
```
11100000071
```
## 提示

样例解释：![](https://cdn.luogu.com.cn/upload/image_hosting/9njsvc34.png)

对于全部数据，$2\leq n\leq 10000$，$1\leq m\leq 50000$，$1\leq s\leq 25000$，$0\leq k\leq 100$，$0\leq t\leq 10^9$，$1\leq c\leq 10^9$，$2\leq l\leq n$，$0\leq x\leq 10^9$，$1\leq y\leq 10^9$，$1\leq a,b,v\leq n$，$\sum l\leq 50000$。

| 子任务编号 | 限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $k=n$ | 20 |
| 2 | $v_i<v_{i+1}$ | 20 |
| 3 | $l=2$ | 20 |
| 4 | $t=0,x=0,y=1$ | 20 |
| 5 |  | 20 |



---

---
title: "[EC Final 2022] Chase Game"
layout: "post"
diff: 提高+/省选-
pid: P9724
tag: ['2022', 'O2优化', '最短路', 'ICPC']
---
# [EC Final 2022] Chase Game
## 题目描述

Prof. Shou is being chased by Prof. Pang on an undirected unweighted simple graph. Initially, Prof. Shou is at vertex $1$. His destination is vertex $n$. Prof. Pang is at vertex $k$.

In each second, Prof. Shou may choose an adjacent vertex and walk to that vertex. Then Prof. Shou is attacked by Prof. Pang. The damage of this attack is equal to $d-dis$ where $d$ is Prof. Pang's attack range and $dis$ is the distance (number of edges in the shortest path) between Prof. Shou and Prof. Pang on the graph. However, when $dis$ is greater than or equal to $d$, Prof. Pang cannot deal any positive damage. In this case, instead of attacking with non-positive damage, he will teleport to the vertex where Prof. Shou is and then deal $d$ damage. (When $dis$ is less than $d$, Prof. Pang will stay at his current vertex.)

Please find the minimum sum of damage Prof. Shou will take to reach vertex $n$ from vertex $1$. Prof. Shou will take the last attack at vertex $n$.
## 输入格式

The first line contains $4$ integers $n, m, k, d$ ($2\le n\le 10^5, n-1\le m\le 2\times 10^5, 1\le k\le n, 1\le d\le 2\times 10^5$).

Each of the next $m$ lines contains two integers $a, b$ ($1\le a, b\le n, a \ne b$) representing an edge of the graph. The edges are distinct. ($a\ b$ and $b\ a$ represents the same edge. Thus, only one of these two lines may appear in the input.)

It is guaranteed that the graph is connected.
## 输出格式

Output one integer representing the answer in one line.
## 样例

### 样例输入 #1
```
5 5 3 1
1 2
2 4
4 5
1 3
3 5

```
### 样例输出 #1
```
2

```
### 样例输入 #2
```
13 17 12 3
1 2
2 3
3 4
4 13
5 13
7 8
7 9
7 10
7 11
7 6
12 7
1 8
8 9
9 10
10 11
11 6
6 13

```
### 样例输出 #2
```
7

```
## 题目翻译

**【题目描述】**

Shou 教授被 Pang 教授在一个无向无权简单图上追赶。最初，Shou 教授在顶点 $1$。他的目的地是顶点 $n$。Pang 教授在顶点 $k$。

每秒钟，Shou 教授可以选择一个相邻的顶点并走向该顶点。然后，Shou 教授会受到 Pang 教授的攻击。此次攻击的伤害等于 $d-dis$，其中 $d$ 是 Pang 教授的攻击范围，$dis$ 是图上从 Shou 教授到 Pang 教授的距离（最短路径上的边数）。然而，当 $dis$ 大于或等于 $d$ 时，Pang 教授无法造成任何正伤害。在这种情况下，他将不会使用非正的伤害攻击，而是会传送到 Shou 教授所在的顶点，然后造成 $d$ 伤害。（当 $dis$ 小于 $d$ 时，Pang 教授将停留在当前顶点。）

请找出 Shou 教授从顶点 $1$ 到顶点 $n$ 所需的最小伤害总和。Shou 教授将在顶点 $n$ 处受到最后一次攻击。

**【输入格式】**

第一行包含 $4$ 个整数 $n, m, k, d$ ($2\le n\le 10^5, n-1\le m\le 2\times 10^5, 1\le k\le n, 1\le d\le 2\times 10^5$)。

接下来的 $m$ 行中，每行包含两个整数 $a, b$ ($1\le a, b\le n, a \ne b$)，表示图的一条边。边是不同的。($a\ b$ 和 $b\ a$ 表示相同的边。因此，在输入中只会出现这两行中的一行。)

保证图是连通的。

**【输出格式】**

输出一行整数，表示答案。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

