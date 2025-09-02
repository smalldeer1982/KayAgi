---
title: "[DTCPC 2024] 环"
layout: "post"
diff: 普及/提高-
pid: P10166
tag: ['贪心', '2024', '拓扑排序', '洛谷月赛']
---
# [DTCPC 2024] 环
## 题目背景

环
## 题目描述

给定无重边无自环的有向图 $G$ 和序列 $\{a_n\}$，每次可以花费 $a_i+a_j$ 的代价加上一条 $i\to j$ 的边，试花费最小代价使得可以找到 $k\geq 2$ 个不同的点 $p_1,p_2,\dots,p_k$，满足 $\forall i\in [1,k]$，都有一条 $p_i\to p_{i\bmod k+1}$ 的边。
## 输入格式

第一行两个整数 $n,m$（$2\le n\le 5 \times 10^5$，$n-1 \le m \le 10^6$），表示图的点数和边数。

第二行输入 $n$ 个整数，表示序列 $\{a_n\}$（$1\le a_i\le 10^9$）。

接下来 $m$ 行，每行两个整数 $u,v$（$1\le u,v\le n$），表示存在一条有向边 $u\to v$。
## 输出格式

一行一个整数表示最小代价。
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5 
1 2
2 3
3 4
1 5
5 4 
```
### 样例输出 #1
```
3
```


---

---
title: "[GESP样题 七级] 最长不下降子序列"
layout: "post"
diff: 普及/提高-
pid: P10287
tag: ['拓扑排序', 'GESP']
---
# [GESP样题 七级] 最长不下降子序列
## 题目描述

小杨有个包含 $n$ 个节点 $m$ 条边的有向无环图，其中节点的编号为 $1$ 到 $n$。

对于编号为 $i$ 的节点，其权值为 $w_i$。对于图中的一条路径，根据路径上的经过节点的先后顺序可以得到一个节点权值的序列，小杨想知道图中所有可能序列中最长不下降子序列的最大长度。

注：给定一个序列 $S$，其最长不下降子序列 $S'$ 是原序列中的如下子序列：整个子序列 $S'$ 单调不降，并且是序列中最长的单调不降子序列。例如，给定序列 $S = [11,12,13,9,8,17,19]$，其最长不下降子序列为 $S'=[11,12,13,17,19]$，长度为 $5$。
## 输入格式

第一行包含两个正整数 $n,m$，表示节点数和边数。 
 
第二行包含 $n$个正整数 $A_1, A_2, \dots A_n$，表示节点 $1$ 到 $n$ 的点权。  

之后 $m$ 行每行包含两个正整数 $u_i, v_i$，表示第 $i$ 条边连接节点 $u_i$ 和 $v_i$，方向为从 $u_i$ 到 $v_i$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5 4
2 10 6 3 1
5 2
2 3
3 1
1 4
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
6 11
1 1 2 1 1 2
3 2
3 1
5 3
4 2
2 6
3 6
1 6
4 6
1 2
5 1
5 4
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
6 11
5 9 10 5 1 6
5 4
5 2
4 2
3 1
5 3
6 1
4 1
4 3
5 1
2 3
2 1
```
### 样例输出 #3
```
4
```
## 提示

### 数据规模与约定

| 子任务 | 分值 | $n\le$ | $A_i \le$ | 特殊约定 |
| :-: | :-: | :-: | :-: | :-:|
| $1$ | $30$ | $10^3$ | $10$ | 输入的图是一条链 |
| $2$ | $30$ | $10^5$ | $2$ | 无 |
| $3$ | $40$ | $10^5$ | $10$ | 无|

对全部的测试数据，保证 $1 \leq n \leq 10^5$，$1 \leq m \leq 10^5$，$1 \leq A_i \leq 10$。



---

---
title: "可达性统计"
layout: "post"
diff: 普及/提高-
pid: P10480
tag: ['拓扑排序', '位运算']
---
# 可达性统计
## 题目描述

给定一张 $N$ 个点 $M$ 条边的有向无环图，分别统计从每个点出发能够到达的点的数量。
## 输入格式

第一行两个整数 $N,M$，接下来 $M$ 行每行两个整数 $x,y$，表示从 $x$ 到 $y$ 的一条有向边。
## 输出格式

输出共 $N$ 行，表示每个点能够到达的点的数量。
## 样例

### 样例输入 #1
```
10 10
3 8
2 3
2 5
5 9
5 9
2 3
3 9
4 8
2 10
4 9
```
### 样例输出 #1
```
1
6
3
3
2
1
1
1
1
1
```
## 提示

测试数据满足 $1 \le N,M \le 30000$，$1 \le x,y \le N$。


---

---
title: "旅行计划"
layout: "post"
diff: 普及/提高-
pid: P1137
tag: ['动态规划 DP', '图论', '递推', '排序', '拓扑排序']
---
# 旅行计划
## 题目描述

小明要去一个国家旅游。这个国家有 $N$ 个城市，编号为 $1$ 至 $N$，并且有 $M$ 条道路连接着，小明准备从其中一个城市出发，并只往东走到城市 $i$ 停止。

所以他就需要选择最先到达的城市，并制定一条路线以城市 $i$ 为终点，使得线路上除了第一个城市，每个城市都在路线前一个城市东面，并且满足这个前提下还希望游览的城市尽量多。

现在，你只知道每一条道路所连接的两个城市的相对位置关系，但并不知道所有城市具体的位置。现在对于所有的 $i$，都需要你为小明制定一条路线，并求出以城市 $i$ 为终点最多能够游览多少个城市。
## 输入格式

第一行为两个正整数 $N, M$。

接下来 $M$ 行，每行两个正整数 $x, y$，表示了有一条连接城市 $x$ 与城市 $y$ 的道路，保证了城市 $x$ 在城市 $y$ 西面。

## 输出格式

$N$ 行，第 $i$ 行包含一个正整数，表示以第 $i$ 个城市为终点最多能游览多少个城市。

## 样例

### 样例输入 #1
```
5 6
1 2
1 3
2 3
2 4
3 4
2 5

```
### 样例输出 #1
```
1
2
3
4
3

```
## 提示

均选择从城市 $1$ 出发可以得到以上答案。

- 对于 $20\%$ 的数据，$1\le N ≤ 100$；
- 对于 $60\%$ 的数据，$1\le N ≤ 1000$；
- 对于 $100\%$ 的数据，$1\le N ≤ 100000$，$1\le M ≤ 200000$。



---

---
title: "[NERC 2020 Online] Miser"
layout: "post"
diff: 普及/提高-
pid: P12862
tag: ['2020', '二分', '拓扑排序', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020 Online] Miser
## 题目描述

In some non-classical University, there is going to be an opening ceremony of the cafeteria in $n$ days. In front of the closed cafeteria, there is a sign with a number --- how many days are left before the opening.

For each day out of these $n$, the director of the cafeteria knows all the people who are coming to the University and are going to see the sign. The director has to choose a sign with a number each day, such that each person who is coming to the University sees that the number on the sign is decreasing. The director is a typical $\emph{miser}$ who spends as little money as possible and wants to order the minimum possible number of different signs. Your task is to help the director find this number.

Consider the first test case: person $1$ comes on days $1$, $2$ and $5$, and person $2$ comes on days $2$, $3$ and $4$. The director can order just four signs with numbers $1$, $2$, $3$ and $4$, to put a sign with $1$ on days $5$ and $4$, a sign with $2$ on day $3$, a sign with $3$ on day $2$, and a sign with $4$ on day $1$. Thus, person $1$ will see the signs $4$, $2$, and $1$ and person $2$ will see the signs $3$, $2$, and $1$.
## 输入格式

The first line of the input contains an integer $n$ --- the total number of days before the opening of the~cafeteria. The next $n$ lines contain the description of each day. The description starts with the positive integer $k$ --- the number of people that come to the University this day. This integer is followed by $k$ distinct integers --- the identifiers of the people that come.

The sum of all $k$ over all days does not exceed $10^5$. Identifiers of people are positive and do not exceed $10^5$.
## 输出格式

Output one integer --- the minimum possible number of different signs that have to be ordered.
## 样例

### 样例输入 #1
```
5
1 1
2 1 2
1 2
1 2
1 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5
1 1
1 1
1 1
1 1
1 1
```
### 样例输出 #2
```
5
```


---

---
title: "[GCJ 2022 Qualification] Chain Reactions"
layout: "post"
diff: 普及/提高-
pid: P12982
tag: ['2022', '拓扑排序', 'Google Code Jam']
---
# [GCJ 2022 Qualification] Chain Reactions
## 题目描述

Wile lives alone in the desert, so he entertains himself by building complicated machines that run on chain reactions. Each machine consists of $\mathbf{N}$ modules indexed $1, 2, \ldots, \mathbf{N}$. Each module may point at one other module with a lower index. If not, it points at the abyss.

Modules that are not pointed at by any others are called *initiators*. Wile can manually trigger initiators. When a module is triggered, it triggers the module it is pointing at (if any) which in turn may trigger a third module (if it points at one), and so on, until the chain would hit the abyss or an already triggered module. This is called a *chain reaction*.

Each of the $\mathbf{N}$ modules has a fun factor $\mathbf{F}_i$. The fun Wile gets from a chain reaction is the largest fun factor of all modules that triggered in that chain reaction. Wile is going to trigger each initiator module once, in some order. The overall fun Wile gets from the session is the sum of the fun he gets from each chain reaction.

For example, suppose Wile has 4 modules with fun factors $\mathbf{F}_1 = 60$, $\mathbf{F}_2 = 20$, $\mathbf{F}_3 = 40$, and $\mathbf{F}_4 = 50$ and module 1 points at the abyss, modules 2 and 3 at module 1, and module 4 at module 2. There are two initiators (3 and 4) that Wile must trigger, in some order.

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/v8jwu5d8)

As seen above, if Wile manually triggers module 4 first, modules 4, 2, and 1 will get triggered in the same chain reaction, for a fun of $\max(50, 20, 60) = 60$. Then, when Wile triggers module 3, module 3 will get triggered alone (module 1 cannot get triggered again), for a fun of 40, and an overall fun for the session of $60 + 40 = 100$.

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/94l7nhpi)

However, if Wile manually triggers module 3 first, modules 3 and 1 will get triggered in the same chain reaction, for a fun of $\max(40, 60) = 60$. Then, when Wile triggers module 4, modules 4 and 2 will get triggered in the same chain reaction, for a fun of $\max(50, 20) = 50$, and an overall fun for the session of $60 + 50 = 110$.

Given the fun factors and the setup of the modules, compute the maximum fun Wile can get if he triggers the initiators in the best possible order.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow, each described using 3 lines. Each test case starts with a line with a single integer $\mathbf{N}$, the number of modules Wile has. The second line contains $\mathbf{N}$ integers $\mathbf{F}_1, \mathbf{F}_2, \ldots, \mathbf{F}_\mathbf{N}$ where $\mathbf{F}_i$ is the fun factor of the $i$-th module. The third line contains $\mathbf{N}$ integers $\mathbf{P}_1, \mathbf{P}_2, \ldots \mathbf{P}_\mathbf{N}$. If $\mathbf{P}_i = 0$, that means module $i$ points at the abyss. Otherwise, module $i$ points at module $\mathbf{P}_i$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the maximum fun Wile can have by manually triggering the initiators in the best possible order.
## 样例

### 样例输入 #1
```
3
4
60 20 40 50
0 1 1 2
5
3 2 1 4 5
0 1 1 1 0
8
100 100 100 90 80 100 90 100
0 1 2 1 2 3 1 3
```
### 样例输出 #1
```
Case #1: 110
Case #2: 14
Case #3: 490
```
## 提示

**Sample Explanation**

Sample Case #1 is the one explained in the problem statement.

In Sample Case #2, there are $4$ initiators (modules $2$ through $5$), so there are $4$ chain reactions. Activating them in order $3, 5, 4, 2$ yields chains of fun $3, 5, 4, 2$ for an overall fun of $14$. Notice that we are summing the four highest fun numbers in the input, so there is no way to get more than that.

In Sample Case #3, an optimal activation order of the $5$ initiators is $4, 5, 7, 6, 8$.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{F}_i \leq 10^9$.
- $0 \leq \mathbf{P}_i \leq i - 1$, for all $i$.

**Test Set 1 (10 Pts, Visible Verdict)**

- Time limit: 5 seconds.
- $1 \leq \mathbf{N} \leq 10$.

**Test Set 2 (12 Pts, Visible Verdict)**

- Time limit: 5 seconds.
- $1 \leq \mathbf{N} \leq 1000$.

**Test Set 3 (5 Pts, Hidden Verdict)**

- Time limit: 10 seconds.
- $1 \leq \mathbf{N} \leq 100000$.


---

---
title: "最长路"
layout: "post"
diff: 普及/提高-
pid: P1807
tag: ['图论', 'NOI 导刊', '广度优先搜索 BFS', '拓扑排序']
---
# 最长路
## 题目描述

设 $G$ 为有 $n$ 个顶点的带权有向无环图，$G$ 中各顶点的编号为 $1$ 到 $n$，请设计算法，计算图 $G$ 中 $1, n$ 间的最长路径。
## 输入格式

输入的第一行有两个整数，分别代表图的点数 $n$ 和边数 $m$。

第 $2$ 到第 $(m + 1)$ 行，每行 $3$ 个整数 $u, v, w$（$u<v$），代表存在一条从 $u$ 到  $v$ 边权为 $w$ 的边。
## 输出格式

输出一行一个整数，代表 $1$ 到 $n$ 的最长路。

若 $1$ 无法到达 $n$，请输出 $-1$。
## 样例

### 样例输入 #1
```
2 1
1 2 1
```
### 样例输出 #1
```
1
```
## 提示

**【数据规模与约定】**

- 对于 $20\%$的数据，$n \leq 100$，$m \leq 10^3$。
- 对于 $40\%$ 的数据，$n \leq 10^3$，$m \leq 10^{4}$。
- 对于 $100\%$ 的数据，$1 \leq n \leq 1500$，$0 \leq m \leq 5 \times 10^4$，$1 \leq u, v \leq n$，$-10^5 \leq w \leq 10^5$。


---

---
title: "摄像头"
layout: "post"
diff: 普及/提高-
pid: P2712
tag: ['拓扑排序']
---
# 摄像头
## 题目描述

食品店里有 $n$ 个摄像头，这种摄像头很笨拙，只能拍摄到固定位置。现有一群胆大妄为的松鼠想要抢劫食品店，为了不让摄像头拍下他们犯罪的证据，他们抢劫前的第一件事就是砸毁这些摄像头。

为了便于砸毁摄像头，松鼠歹徒们把所有摄像头和摄像头能监视到的地方统一编号，一个摄像头能被砸毁的条件是该摄像头所在位置不被其他摄像头监视。

现在你的任务是帮松鼠们计算是否可以砸掉所有摄像头，如不能则输出还没砸掉的摄像头的数量。
## 输入格式

第 $1$ 行，一个整数 $n$，表示摄像头的个数。

第 $2$ 到 $n+1$ 行是摄像头的信息，包括：摄像头的位置 $x$，以及这个摄像头可以监视到的位置数 $m$，之后 $m$ 个数 $y$ 是此摄像头可以监视到的位置。(砸了这些摄像头之后自然这些位置就监视不到了)
## 输出格式

若可以砸掉所有摄像头则输出“ $\texttt{YES}$ ”，否则输出还没砸掉的摄像头的数量。（不带引号）
## 样例

### 样例输入 #1
```
5
1 1 2
2 1 1
3 1 7
4 1 1
5 0

```
### 样例输出 #1
```
2
```
## 提示

$1 \leq n \leq 100$。

$0 \leq m \leq 100$。

$0 \leq x,y \leq 500$。



---

---
title: "[USACO08JAN] Cell Phone Network G"
layout: "post"
diff: 普及/提高-
pid: P2899
tag: ['2008', 'USACO', '排序', '树形 DP', '拓扑排序']
---
# [USACO08JAN] Cell Phone Network G
## 题目描述

Farmer John has decided to give each of his cows a cell phone in hopes to encourage their social interaction. This, however, requires him to set up cell phone towers on his N (1 ≤ N ≤ 10,000) pastures (conveniently numbered 1..N) so they can all communicate.

Exactly N-1 pairs of pastures are adjacent, and for any two pastures A and B (1 ≤ A ≤ N; 1 ≤ B ≤ N; A ≠ B) there is a sequence of adjacent pastures such that A is the first pasture in the sequence and B is the last. Farmer John can only place cell phone towers in the pastures, and each tower has enough range to provide service to the pasture it is on and all pastures adjacent to the pasture with the cell tower.

Help him determine the minimum number of towers he must install to provide cell phone service to each pasture.

Farmer John 想让他的所有牛用上手机以便相互交流。他需要建立几座信号塔在 $N$ 块草地中。已知与信号塔相邻的草地能收到信号。给你 $N-1$ 个草地 $(A,B)$ 的相邻关系，问：最少需要建多少个信号塔能实现所有草地都有信号。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N: Each line specifies a pair of adjacent pastures with two space-separated integers: A and B

## 输出格式

\* Line 1: A single integer indicating the minimum number of towers to install

## 样例

### 样例输入 #1
```
5
1 3
5 2
4 3
3 5

```
### 样例输出 #1
```
2

```


---

---
title: "[USACO13FEB] Milk Scheduling S"
layout: "post"
diff: 普及/提高-
pid: P3074
tag: ['贪心', '2013', 'USACO', '枚举', '拓扑排序']
---
# [USACO13FEB] Milk Scheduling S
## 题目描述

Farmer John's N cows (1 <= N <= 10,000) are conveniently numbered 1..N. Each cow i takes T(i) units of time to milk.  Unfortunately, some cows must be milked before others, owing to the layout of FJ's barn.  If cow A must be milked before cow B, then FJ needs to completely finish milking A before he can start milking B.

In order to milk his cows as quickly as possible, FJ has hired a large number of farmhands to help with the task -- enough to milk any number of cows at the same time.  However, even though cows can be milked at the same time, there is a limit to how quickly the entire process can proceed due to the constraints requiring certain cows to be milked before others.  Please help FJ compute the minimum total time the milking process must take.

农民约翰有N头奶牛(1<=N<=10,000)，编号为1...N。每一头奶牛需要T(i)单位的时间来挤奶。不幸的是，由于FJ的仓库布局，一些奶牛要在别的牛之前挤奶。比如说，如果奶牛A必须在奶牛B前挤奶，FJ就需要在给奶牛B挤奶前结束给奶牛A的挤奶。


为了尽量完成挤奶任务，FJ聘请了一大批雇工协助任务——同一时刻足够去给任意数量的奶牛挤奶。然而，尽管奶牛可以同时挤奶，但仍需要满足以上的挤奶先后顺序。请帮助FJ计算挤奶过程中的最小总时间。

## 输入格式

\* Line 1: Two space-separated integers: N (the number of cows) and M (the number of milking constraints; 1 <= M <= 50,000).

\* Lines 2..1+N: Line i+1 contains the value of T(i) (1 <= T(i) <= 100,000).

\* Lines 2+N..1+N+M: Each line contains two space-separated integers A and B, indicating that cow A must be fully milked before one can start milking cow B.  These constraints will never form a cycle, so a solution is always possible.

## 输出格式

\* Line 1: The minimum amount of time required to milk all cows.

## 样例

### 样例输入 #1
```
3 1 
10 
5 
6 
3 2 

```
### 样例输出 #1
```
11 

```
## 提示

There are 3 cows.  The time required to milk each cow is 10, 5, and 6, respectively.  Cow 3 must be fully milked before we can start milking cow 2.


Cows 1 and 3 can initially be milked at the same time.  When cow 3 is finished with milking, cow 2 can then begin.  All cows are finished milking after 11 units of time have elapsed.



---

---
title: "最大食物链计数"
layout: "post"
diff: 普及/提高-
pid: P4017
tag: ['动态规划 DP', '搜索', '图论', '排序', '深度优先搜索 DFS', '拓扑排序']
---
# 最大食物链计数
## 题目背景

你知道食物链吗？Delia 生物考试的时候，数食物链条数的题目全都错了，因为她总是重复数了几条或漏掉了几条。于是她来就来求助你，然而你也不会啊！写一个程序来帮帮她吧。

## 题目描述

给你一个食物网，你要求出这个食物网中最大食物链的数量。

（这里的“最大食物链”，指的是**生物学意义上的食物链**，即**最左端是不会捕食其他生物的生产者，最右端是不会被其他生物捕食的消费者**。）

Delia 非常急，所以你只有 $1$ 秒的时间。

由于这个结果可能过大，你只需要输出总数模上 $80112002$ 的结果。

## 输入格式

第一行，两个正整数 $n、m$，表示生物种类 $n$ 和吃与被吃的关系数 $m$。

接下来 $m$ 行，每行两个正整数，表示被吃的生物A和吃A的生物B。

## 输出格式

一行一个整数，为最大食物链数量模上 $80112002$ 的结果。

## 样例

### 样例输入 #1
```
5 7
1 2
1 3
2 3
3 5
2 5
4 5
3 4
```
### 样例输出 #1
```
5
```
## 提示

各测试点满足以下约定：

 ![](https://cdn.luogu.com.cn/upload/pic/12011.png) 

【补充说明】

数据中不会出现环，满足生物学的要求。（感谢 @AKEE ）



---

---
title: "[USACO17DEC] The Bovine Shuffle S"
layout: "post"
diff: 普及/提高-
pid: P4089
tag: ['2017', 'USACO', '拓扑排序']
---
# [USACO17DEC] The Bovine Shuffle S
## 题目描述

Convinced that happy cows generate more milk, Farmer John has installed a giant disco ball in his barn and plans to teach his cows to dance!

Looking up popular cow dances, Farmer John decides to teach his cows the "Bovine Shuffle". The Bovine Shuffle consists of his $N$ cows ($1 \leq N \leq 100,000$) lining up in a row in some order, then performing successive "shuffles", each of which potentially re-orders the cows. To make it easier for his cows to locate themselves, Farmer John marks the locations for his line of cows with positions $1 \ldots N$, so the first cow in the lineup will be in position 1, the next in position 2, and so on, up to position $N$.


A shuffle is described with $N$ numbers, $a_1 \ldots a_N$, where a cow in position $i$ moves to position $a_i$ during the shuffle (and so, each $a_i$ is in the range $1 \ldots N$). Every cow moves to its new location during the shuffle. Unfortunately, all the $a_i$'s are not necessarily distinct, so multiple cows might try to move to the same position during a shuffle, after which they will move together for all remaining shuffles.


Farmer John notices that some positions in his lineup contain cows in them no matter how many shuffles take place. Please help him count the number of such positions.


## 输入格式

The first line of input contains $N$, the number of cows. The next line contains the $N$ integers $a_1 \ldots a_N$.

## 输出格式

Please output the number of positions that will always contain cows, no matter how many shuffles take place.

## 样例

### 样例输入 #1
```
4
3 2 1 3
```
### 样例输出 #1
```
3

```
## 题目翻译

### 题目描述

Farmer John 坚信快乐的奶牛能产更多的奶，因此他在谷仓里安装了一个巨大的迪斯科球，并计划教他的奶牛跳舞！

在查阅了流行的奶牛舞蹈后，Farmer John 决定教他的奶牛“Bovine Shuffle”。Bovine Shuffle 包括他的 $N$ 头奶牛（$1 \leq N \leq 100,000$）以某种顺序排成一行，然后进行连续的“洗牌”，每次洗牌可能会重新排列奶牛的顺序。为了让奶牛更容易找到自己的位置，Farmer John 为他的奶牛队伍标记了位置 $1 \ldots N$，因此队伍中的第一头奶牛位于位置 1，第二头位于位置 2，依此类推，直到位置 $N$。

一次洗牌由 $N$ 个数字 $a_1 \ldots a_N$ 描述，其中位于位置 $i$ 的奶牛在洗牌期间移动到位置 $a_i$（因此，每个 $a_i$ 都在 $1 \ldots N$ 范围内）。每头奶牛在洗牌期间都会移动到它的新位置。不幸的是，所有的 $a_i$ 不一定互不相同，因此多只奶牛可能会在洗牌期间尝试移动到同一位置，之后它们将在所有剩余的洗牌中一起移动。

Farmer John 注意到，无论进行多少次洗牌，他的队伍中某些位置始终会有奶牛。请帮助他计算这样的位置数量。

### 输入格式

输入的第一行包含 $N$，表示奶牛的数量。第二行包含 $N$ 个整数 $a_1 \ldots a_N$。

### 输出格式

请输出无论进行多少次洗牌，始终会有奶牛的位置数量。


---

---
title: "[USACO20FEB] Timeline G"
layout: "post"
diff: 普及/提高-
pid: P6145
tag: ['图论', '2020', 'USACO', '拓扑排序', '差分约束']
---
# [USACO20FEB] Timeline G
## 题目描述

Bessie 在过去的 $M$ 天内参加了 $N$ 次挤奶。但她已经忘了她每次挤奶是在哪个时候了。

对于第 $i$ 次挤奶，Bessie 记得它不早于第 $S_i$ 天进行。另外，她还有 $C$ 条记忆，每条记忆形如一个三元组 $(a,b,x)$，含义是第 $b$ 次挤奶在第 $a$ 次挤奶结束至少 $x$ 天后进行。

现在请你帮 Bessie 算出在满足所有条件的前提下，每次挤奶的最早日期。

保证 Bessie 的记忆没有错误，这意味着一定存在一种合法的方案，使得：

- 第 $i$ 次挤奶不早于第 $S_i$ 天进行，且不晚于第 $M$ 天进行；
- 所有的记忆都得到满足；
## 输入格式

第一行三个整数 $N,M,C$。保证 $1 \leq N,C \leq 10^5$，$2 \leq M \leq 10^9$。

接下来一行包含 $N$ 个整数 $S_1, S_2 , \ldots, S_n$，保证 $\forall 1 \leq i \leq n$，都满足 $1 \leq S_i \leq M$。

下面 $C$ 行每行三个整数 $a,b,x$，描述一条记忆。保证 $a \neq b$，且 $1 \leq x \leq M$。
## 输出格式

输出 $N$ 行，每行一个整数，第 $i$ 行的数表示第 $i$ 次挤奶的最早日期。
## 样例

### 样例输入 #1
```
4 10 3
1 2 3 4
1 2 5
2 4 2
3 4 4
```
### 样例输出 #1
```
1
6
3
8
```
## 提示

- 测试点 $2 \sim 4$ 满足 $N,C \leq 10^3$。
- 测试点 $5 \sim 10$ 没有特殊限制。


---

---
title: "「UOI-R1」智能推荐"
layout: "post"
diff: 普及/提高-
pid: P8893
tag: ['O2优化', '拓扑排序']
---
# 「UOI-R1」智能推荐
## 题目背景

数据已加强。
## 题目描述

现在有 $N$ 道题。

天数的编号从 $0$ 开始，每一天你可以做若干道题，你只能做以前推荐过的或者当天推荐的题（每道题只可以做一次）。第一天，智能推荐会推荐 $p$ 道题。

推荐规则如下：

对于第 $i$ 道题，如果有可能被推荐的话，就会有一个题目集合 $s_i$。当且仅当你把 $s_i$ 中每一道题都做出来并且其中有一道题是当天做的，那么下一天就会推荐第 $i$ 题。

你想做完第 $K$ 道题，问至少第几天你才能满足愿望？

## 输入格式

第一行三个整数 $N,K,p$，含义如题目所述。

第二行 $p$ 个整数，表示第一天推荐的题的题号。

第三行一个整数 $R$，表示有 $R$ 条推荐规则。

接下来 $R$ 行，每行包含一条规则，每行格式如下：

一个整数 $v_i$，表示要推荐的题的题号。接着一个整数 $s_i$，表示要使得这道题被推荐，一共要做的题目数量。接下来 $s_i$ 个整数 $p_i$，表示要做的每道题。

## 输出格式

一个整数表示最少第几天才能满足愿望。

如无论如何，第 $K$ 题都无法完成，则输出 `-1`。

## 样例

### 样例输入 #1
```
5 5 2
1 2
3
3 2 1 2
4 3 1 2 3
5 3 1 3 4
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
1 1 1
1
0
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
7 7 2
1 2
2
3 2 1 2
6 2 1 2
```
### 样例输出 #3
```
-1
```
### 样例输入 #4
```
见文件附件的 rec4.in
```
### 样例输出 #4
```
见文件附件的 rec4.ans
```
## 提示

**【样例解释 #1】**

第 $0$ 天推了第 $1,2$ 题，都做了。

第 $1$ 推了第 $3$ 题，做了。

第 $2$ 推了第 $4$ 题，做了。

第 $3$ 推了第 $5$ 题，也就是第 $K$ 题，做了。

第 $3$ 天即可做完第 $K$ 题目。

**【样例解释 #2】**

第 $0$ 天推了第 $1$ 题，也就是第 $K$ 题，做了。
第 $0$ 天就做完了。

**【数据范围】**

以下记 $\left| s_i \right|$ 表示推荐规则中第 $i$ 条规则中，如果 $v_i$ 被推荐，要做的所有题。

对于 $30\%$ 的数据，保证 $1 \leq N \leq 100$。

对于 $50\%$ 的数据，保证没有环。

对于 $100\%$ 的数据，保证 $1 \le K,s_i,p_i,v_i \le N \le 5\times 10^3$，$0 \leq R \leq 5 \times 10^3$。$|s_i|$ 互不相同，且对于每一个 $|s_i|$ 都有 $p_i$ 互不相同，$v_i$ 互不相同。



---

