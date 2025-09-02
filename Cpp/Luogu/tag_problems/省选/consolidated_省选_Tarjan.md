---
title: "[THUPC 2024 决赛] 转化"
layout: "post"
diff: 省选/NOI-
pid: P10544
tag: ['动态规划 DP', '2024', 'Tarjan', 'THUPC']
---
# [THUPC 2024 决赛] 转化
## 题目描述

有 $n$ 种物品和 $m$ 种转化方式。第 $i$ 种转化方式可以将一个第 $a_i$ 种物品转化成 $k_i$ 个互不相同的物品，其中第 $j$ 个的种类是 $b_{i,j}$。同一种转化方式可以使用任意多次。

你有一些物品。你想知道，对于每一种特定的物品 $d$，你用这些你所拥有的物品可以分别转化出最多多少个该种物品。

## 输入格式

第一行两个正整数 $n,m$。

第二行 $n$ 个非负整数，其中第 $i$ 个为 $c_i$，表示你拥有的第 $i$ 种物品的数量。

接下来 $m$ 行，其中第 $i$ 行表示第 $i$ 种转化方式。

转化方式的格式为：一行 $k_i+2$ 个正整数，其中第一个为 $a_i$，第二个为 $k_i$，之后为 $k_i$ 个互不相同的正整数 $b_{i,1},b_{i,2},\cdots,b_{i,k_i}$​​。

保证 $1\le n \le 100$，$1\le m \le 1000$。

保证 $1\le a_i,k_i,b_{i,j} \le n$。

保证 $0\le c_i \le 1000$。
## 输出格式

输出 $n$ 行，其中第 $d$ 行表示第 $d$ 种物品最多能有多少个。如果可以任意多，即对于任意的 $N$ 都存在一种方案使得有超过 $N$ 个第 $d$ 种物品，输出 `infinity`。

## 样例

### 样例输入 #1
```
4 4
1 0 0 0
1 2 2 4
1 1 3
2 1 4
3 1 4

```
### 样例输出 #1
```
1
1
1
2

```
## 提示

不使用任何转化方式，可以得到一个物品 $1$。

使用一次第一种转化方式，可以把物品 $1$ 变成物品 $2$ 和物品 $4$。这样可以得到一个物品 $2$。

使用一次第二种转化方式，可以把物品 $1$ 变成物品 $3$。这样可以得到一个物品 $3$。

使用一次第一种转化方式，可以把物品 $1$ 变成物品 $2$ 和物品 $4$。然后再使用一次第三种转化方式，可以把物品 $2$ 变成物品 $4$。这样可以得到两个物品 $4$。

可以证明这四种方案分别是当 $d=1,2,3,4$ 时的最优方案。

**来源与致谢**

来自 THUPC2024（2024年清华大学学生程序设计竞赛暨高校邀请赛）决赛。感谢 THUSAA 的提供的题目。

数据、题面、标程、题解等请参阅 THUPC 官方仓库 <https://thusaac.com/public>


---

---
title: "Retribution"
layout: "post"
diff: 省选/NOI-
pid: P12704
tag: ['2023', 'O2优化', 'Tarjan']
---
# Retribution
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/ij24f1iy.png?x-oss-process=image)

## 题目描述

给你一个 $n\times m$ 的棋盘，每个格点上标有一个字符 $c_{i,j}\in\{\texttt{U},\texttt{D},\texttt{L},\texttt{R}\}$，分别代表上、下、左、右。在一个格点可以移动到一个与它相邻的格点，但移动方向**不能**与当前所在格点上的字符所代表的方向相同且不能移出棋盘。

给出 $q$ 次询问，每次询问给出两个格点 $s,t$，询问能否从格点 $s$ 通过若干次移动到达格点 $t$。
## 输入格式

为避免输入数据过大，本题使用特殊的读入方式。**请使用 `C++11` 及以上的语言进行编写与提交。**

第一行四个正整数 $n,m,q,seed$，其中 $seed$ 为输入参数。

接下来 $n$ 行，每行 $m$ 个字符描述棋盘。

```cpp
mt19937_64 R;
inline void init(int seed){
    R=mt19937_64(seed);
}
inline int get(int l,int r){
    uniform_int_distribution<int> distribution(l,r);
    return distribution(R);
}
```

你需要在你的代码中加入此段代码，初始化时调用 `init(seed);`

接下来 $q$ 次调用 `int a=get(1,n),b=get(1,m),x=get(1,n),y=get(1,m);`，其中 $a,b,x,y$ 分别描述 $s,t$ 的位置 $(a,b),(x,y)$，表示一次询问。
## 输出格式

输出一行 $q$ 个字符，第 $i$ 个字符为 $0$ 表示第 $i$ 个询问中 $s$ 无法到达 $t$，为 $1$ 则表示第 $i$ 个询问中 $s$ 可以到达 $t$。
## 样例

### 样例输入 #1
```
2 3 6 0
RLD
RLU
2 1 1 3
2 2 1 3
2 3 1 1
2 3 1 2
1 2 2 3
1 3 2 3
```
### 样例输出 #1
```
010111
```
### 样例输入 #2
```
3 3 5 0
DRU
ULU
DRD
1 1 1 3
1 3 1 1
3 1 2 1
2 3 2 1
1 1 1 1
```
### 样例输出 #2
```
01111
```
### 样例输入 #3
```
2 3 6 10000001
RLD
RLU
```
### 样例输出 #3
```
111001
```
## 提示


**Retribution - Kry.exe & nm-y (Insane 16.2)**

### 样例解释

**为了便于阅读，对于样例 1 和样例 2，直接输入了询问而不使用特殊方式读入。**

对于样例 1 第一次询问，格点 $(2,1)$ 无法移动出第 $1$ 列。

对于样例 1 第四次询问，格点 $(2,3)$ 可以移动到 $(2,2)$ 从而移动到 $(1,2)$。

对于样例 1 第六次询问，格点 $(1,3)$ 可以依次移动到 $(1,2),(2,2),(2,3)$。

### 数据规模

本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | $m\le$ | $q\le$ | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $100$ | $100$ | $10^3$ | $10$ |
| $2$ | $3$ | $500$ | $2\times10^5$ | $20$ |
| $3$ | $300$ | $300$ | $2\times10^5$ | $20$ |
| $4$ | $1500$ | $1500$ | $10^6$ | $50$ |

对于所有数据，保证 $1\le n,m\le 1.5\times10^3$，$1\le q\le 10^6$，$c_{i,j}\in\{\texttt{U},\texttt{D},\texttt{L},\texttt{R}\}$，$1\le a,x\le n$，$1\le b,y\le m$，$0\le s<2^{31}$。

### 子任务依赖

本题开启所有合理的子任务依赖。


---

---
title: "[CERC 2022] Money Laundering"
layout: "post"
diff: 省选/NOI-
pid: P13813
tag: ['2022', 'Special Judge', 'Tarjan', '高斯消元', 'ICPC', 'CERC']
---
# [CERC 2022] Money Laundering
## 题目描述

Consider a company $A$ that made a $100 \, \text{€}$ of profit this year. The company's owners are Ivan with $52.8\%$ ownership share and Robi with a $47.2\%$ ownership share. Naturally, the profits are shared proportionally to the shares with Ivan receiving $52.8 \, \text{€}$ and Robi $47.2 \, \text{€}$.

They will have to pay tax on the received profits, but would like to avoid doing so, if at all possible. Sadly, the ownership structure of their company is too simple and it's easily discoverable how much profits each of them received.

For the next year, they prepare a plan. They make a shell company $B$ and change the ownership shares. Ivan now only owns $1\%$ of company $A$, Robi only $2\%$, the company $B$ owns a $49\%$ share of $A$ and $A$ owns $48\%$ of itself. Company $B$ has a similar ownership structure: $70\%$ ownership share belongs to $B$ itself, $25\%$ to $A$, $3\%$ to Ivan and $2\%$ to Robi.

Looking naively, Ivan and Robi have very small ownership shares. However, we are interested in the ownership shares of ultimate beneficial owners, the persons who will ultimately profit, which are Ivan and Robi in our case. We wish to determine their ultimate ownership shares, which turn out to be approximately equal to what they were before the introduction of $B$.

Ultimate ownership shares can be determined as follows: let the company $A$ have $100 \, \text{€}$ of profit and $B$ have $0 \, \text{€}$. The profits are paid out to all direct owners in proportion to their ownership share. However, since $A$ and $B$ are partial owners of themselves, they receive a part of the profit. To determine the ultimate share of the ultimate beneficial owners, we repeat the procedure – any profits that $A$ and $B$ receive are paid out again, with Ivan and Robi getting a share, as well as $A$ and $B$. This is repeated ad infinitum until (theoretically, after an infinite number of steps) all money is paid out to the ultimate beneficial owners, and the ratio of the final sums received by Ivan and Robi is by definition equal to their ultimate share of $A$.

For a given structure of companies, determine the shares of the ultimate beneficial owners. However, the companies do not form a random network of ownership, but are structured in industrial sectors. Companies within sectors may form arbitrary ownership structures, but this is not true for companies in different sectors. If companies $P$ and $Q$ belong to different sectors, it cannot happen that

- $P$ would own a (potentially indirect) share of $Q$ and
- $Q$ would own a (potentially indirect) share of $P$.

One or none of these statements could be true, but not both.
## 输入格式

The first line contains two space-separated integers $c$ and $p$, representing the number of companies and number of persons, respectively. Then $c$ lines follow, and $i$-th of them contains the description of $i$-th company. The line contains an integer $k_i$, the number of owners, and then $k_i$ entries of the form $o_{i,j} : p_{i,j}$, where $o_{i,j}$ is the designation of the $j$-th owner (person or company) and $p_{i,j}$ is their share in percentages. The share will have exactly one decimal place.
## 输出格式

Output the ultimate ownership shares of all persons in all companies. The $i$-th line should include shares of all persons in the $i$-th company, including persons with no share. The share is between 0 and 1. Shares in a line should be separated by a space. The answer will be considered correct if its absolute or relative error is less than $10^{-4}$.
## 样例

### 样例输入 #1
```
2 2
2 P1:50.1 P2:49.9
2 P1:23.4 P2:76.6
```
### 样例输出 #1
```
0.501000 0.499000
0.234000 0.766000
```
### 样例输入 #2
```
2 2
2 P1:50.0 P2:50.0
3 P1:20.0 P2:30.0 C1:50.0
```
### 样例输出 #2
```
0.500000 0.500000
0.450000 0.550000
```
### 样例输入 #3
```
2 2
4 P1:1.0 P2:2.0 C2:49.0 C1:48.0
4 C2:70.0 C1:25.0 P1:3.0 P2:2.0
```
### 样例输出 #3
```
0.528358 0.471642
0.540299 0.459701
```
### 样例输入 #4
```
3 2
5 P1:1.0 P2:2.0 C2:49.0 C1:38.0 C3:10.0
4 C2:70.0 C1:25.0 P1:3.0 P2:2.0
2 P1:20.0 P2:80.0
```
### 样例输出 #4
```
0.373228 0.626772
0.411024 0.588976
0.2 0.8
```
## 提示

### Input limits

- $1 \leq c, p \leq 10^3$
- $1 \leq \sum_{i=1}^{n} k_i \leq 10^4$
- $o_{i,j}$ can have two forms: $\text{Px}$ or $\text{Cy}$, indicating that the owner is the $x$-th person or $y$-th company, respectively. It is guaranteed that $1 \leq x \leq p$, and $1 \leq y \leq c$ holds.
- $k_i \geq 1$
- $0 < p_{i,j} \leq 100$
- $\sum_{j=1}^{k_i} p_{i,j} = 100$
- The identifiers $\{o_{i,j}\}_{j=1}^{k_i}$ are unique, i.e. each owner is listed at most once.
- The number of companies belonging to each sector is less than 10.
- Each company has at least one ultimate beneficial owner. For example, a scheme where $A$ would own a $100\%$ of $B$ and $B$ a $100\%$ of $A$ is forbidden.



---

---
title: "[HNOI2006] 潘多拉的宝盒"
layout: "post"
diff: 省选/NOI-
pid: P2321
tag: ['搜索', '2006', '各省省选', '湖南', '广度优先搜索 BFS', 'Tarjan']
---
# [HNOI2006] 潘多拉的宝盒
## 题目描述

 ![](https://cdn.luogu.com.cn/upload/pic/1372.png) 

![](https://cdn.luogu.com.cn/upload/pic/1373.png)

## 输入格式

 ![](https://cdn.luogu.com.cn/upload/pic/1374.png) 

![](https://cdn.luogu.com.cn/upload/pic/1375.png)

## 输出格式

输出一行一个数$t$，表示最长升级序列的长度。

## 样例

### 样例输入 #1
```
4
1  1
0
0  0
2  1
0
1  1
0  0
3  1
0
1  1
2  2
0  0
4  1
0
1  1
2  2
3  3
0  0
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3
1  1
0
0  0
3  1
0
0  1
2  0
1  2
9  1
0
0  1
2  3
4  5
6  7
8  0
1  2
3  4
5  6
7  8
```
### 样例输出 #2
```
3
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/1380.png)



---

---
title: "[POI 2006] PRO-Professor Szu"
layout: "post"
diff: 省选/NOI-
pid: P3436
tag: ['动态规划 DP', '2006', 'POI（波兰）', '拓扑排序', 'Tarjan']
---
# [POI 2006] PRO-Professor Szu
## 题目描述

某大学校内有一栋主楼，还有 $n$ 栋住宅楼。这些楼之间由一些单向道路连接，但是任意两栋楼之间可能有多条道路，也可能存在起点和终点为同一栋楼的环路。存在住宅楼无法到达主楼的情况。

现在有一位古怪的教授，他希望每天去主楼上班的路线不同。

一条上班路线中，每栋楼都可以访问任意多次。我们称两条上班路线是**不同的**，当且仅当两条路线中存在一条路是不同的（两栋楼之间的多条道路被视为是不同的道路）。

现在教授希望知道，从哪些住宅楼前往主楼的上班路线数最多。
## 输入格式

第一行两个整数 $n,m$，分别为大学内住宅楼的数量和道路的数量。大学内所有住宅楼编号为 $1 \sim n$，主楼编号为 $n+1$。

接下来 $m$ 行，第 $i$ 行两个整数 $u_i,v_i$，代表大学内存在一条从 $u_i$ 号楼到 $v_i$ 号楼的道路。
## 输出格式

第一行：如果存在一栋楼到主楼的上班路线数超过了 $36500$，输出 `zawsze`。否则输出一个整数，代表从一栋住宅楼前往主楼的最多上班路线数。

第二行：输出一个整数 $p$，代表有多少栋住宅楼能使前往主楼的上班路线数最大化。特别地，如果最大上班路线数超过了 $36500$，那么这一行请输出能使上班路线数超过 $36500$ 的住宅楼的数量。

第三行：按编号从小到大的顺序输出 $p$ 个整数，代表能使前往主楼的上班路线最大化的住宅楼的编号。特别地，如果最大上班路线数超过了 $36500$，那么这一行请输出所有能使上班路线数超过 $36500$ 的住宅楼的编号。
## 样例

### 样例输入 #1
```
3 5
1 2
1 3
2 3
3 4
3 4
```
### 样例输出 #1
```
4
1
1
```
## 题目翻译

$1 \leq n,m \leq 10^6$，$1 \leq u_i,v_i \leq n+1$。


---

---
title: "[POI 2012] FES-Festival"
layout: "post"
diff: 省选/NOI-
pid: P3530
tag: ['2012', 'POI（波兰）', 'Tarjan', '差分约束']
---
# [POI 2012] FES-Festival
## 题目背景

在 Byteburg 举办了一场慈善活动，你是其中一个筹款人。不幸的是，你错过了一些有趣的活动，包括一场越野赛。

谜题爱好者 Byteasar 承诺：如果你能解开他的谜题，他会捐一大笔钱。
## 题目描述

你不知道越野赛的结果，但 Byteasar 会告诉你部分信息。现在，他要你答出：所有参赛者最多能达到多少种不同的成绩，而不违背他给的条件。（他们中的一些人可能平局，也就是同时到达终点，这种情况只算有一种成绩）。

Byteasar 告诉你，所有参赛者的成绩都是整数秒。他还会为你提供了一些参赛者成绩的关系。具体是：他会给你一些数对 $(A, B)$，表示 $A$ 的成绩正好比 $B$ 快 $1$ 秒；他还会给你一些数对 $(C, D)$，表示 $C$ 的成绩不比 $D$ 慢。而你要回答的是：所有参赛者最多能达到多少种不同的成绩，而不违背他给的条件。

请你编程解决这个谜题。
## 输入格式

第一行有三个整数 $n, m_{1}, m_{2}$，分别表示选手人数、数对 $(A, B)$ 的数目、数对 $(C, D)$ 的数目。

接下来 $m_1$ 行，每行两个整数 $a_{i}, b_{i}$（$a_{i} \ne b_{i}$）。这表示选手 $a_{i}$ 的成绩恰比 $b_{i}$ 小 $1$ 秒。

接下来 $m_{2}$ 行，每行两个整数 $c_{i}, d_{i}$（$c_{i} \ne d_{i}$）。这表示选手 $c_{i}$ 的成绩不比 $d_{i}$ 的成绩差（也就是花的时间不会更多）。
## 输出格式

如果有解，输出一行一个整数，表示所有选手最多能拿到的成绩的种数。  
如果无解，输出 `NIE`。
## 样例

### 样例输入 #1
```
4 2 2
1 2
3 4
1 4
3 1

```
### 样例输出 #1
```
3

```
## 提示

答案为 $3$，情况为：$t_3=1, t_1=t_4=2, t_2=3$。  
（$t_i$ 表示参赛者 $i$ 花的时间）

**【数据范围】**

对于 $15\%$ 的数据，$n \le 10$。  
对于 $100\%$ 的数据，$2 \le n \le 600$，$1 \le m_{1} + m_{2} \le {10}^5$。


---

---
title: "[COCI 2007/2008 #1] STAZA"
layout: "post"
diff: 省选/NOI-
pid: P6335
tag: ['动态规划 DP', '2007', 'O2优化', 'Tarjan', '双连通分量', '仙人掌', 'COCI（克罗地亚）']
---
# [COCI 2007/2008 #1] STAZA
## 题目描述

一场自行车比赛将在一个国家举行。全国的交通网络由 $n$ 个城市组成，编号为 $1\sim n$，由 $m$ 条双向道路连接。我们定义以下术语：

- 一条路线是一系列道路，当且仅当这些道路每条都从上一条道路的结束城市出发。

- 一条简单路线是指一条不经过一个城市一次以上的道路。

- 环是一条起点与终点相同的简单路线。

对于任意两个城市之间，保证至少有一条路线，且每条整个交通系统中的每条道路最多是一个环的一部分。


你的任务是找到满足以下两个约束条件的最长路线：

- 路线可以从任何城市开始，但必须在城市 $1$ 结束。

- 这条路线可以多次访问同一个城市，但不能经过同一条道路超过一次。

请你输出最长的路线的长度。
## 输入格式

输入第一行为两个整数 $n,m$，表示城市的数量和道路的数量。

接下来的 $m$ 行，每行两个整数 $a,b$，描述一条连接 $a,b$ 的双向道路。

保证不会出现两个城市直接由多条道路连接。
## 输出格式

输出最长路线的长度。
## 样例

### 样例输入 #1
```
4 3
1 2
1 3
2 4
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
6 6
1 2
1 3
2 4
3 4
3 5
5 6
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
5 6
1 2
2 3
3 4
4 5
5 3
3 1
```
### 样例输出 #3
```
6
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le n\le 10^4$，$1\le m\le 2n-2$，$1\le a,b\le n$。

#### 说明

**题目译自 [COCI2007-2008](https://hsin.hr/coci/archive/2007_2008/) [CONTEST #1](https://hsin.hr/coci/archive/2007_2008/contest1_tasks.pdf) *T6 STAZA***


---

---
title: "[PA 2010] Riddle"
layout: "post"
diff: 省选/NOI-
pid: P6378
tag: ['2010', '2-SAT', 'Tarjan', 'PA（波兰）']
---
# [PA 2010] Riddle
## 题目描述

$n$ 个点 $m$ 条边的无向图被分成 $k$ 个部分。每个部分包含一些点。

请选择一些关键点，使得每个部分**恰**有一个关键点，且每条边**至少**有一个端点是关键点。
## 输入格式

第一行三个整数 $n,m,k$。

接下来 $m$ 行，每行两个整数 $a,b$，表示有一条 $a,b$ 间的边。

接下来 $k$ 行，每行第一个整数为 $w$，表示这个部分有 $w$ 个点；接下来 $w$ 个整数，为在这个部分中的点的编号。
## 输出格式

若可能选出请输出 `TAK`，否则输出 `NIE`。
## 样例

### 样例输入 #1
```
6 5 2
1 2
3 1
1 4
5 2
6 2
3 3 4 2
3 1 6 5
```
### 样例输出 #1
```
TAK
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1\le k,w\le n\le 10^6$，$\sum w=n$，$1\le a,b\le n$，$0\le m\le 10^6$。


---

---
title: "「EZEC-1」越狱"
layout: "post"
diff: 省选/NOI-
pid: P6436
tag: ['搜索', '图论', '二分', '最短路', 'Tarjan', '最近公共祖先 LCA']
---
# 「EZEC-1」越狱
## 题目背景

由于监狱长 PF 的疏忽，罪犯小 E 找到了机会越狱。

然而，不学无术的小 E 不懂得保密。PF 很快发现了他的计划，并对他展开了追捕。

因为小 E 自己造船，而狱长 PF 坐的是官方的船，所以在每条航道上的表现不一样，通过时间可能不同。具体见输入格式。

为了不饿肚子，小 E 准备买一个包来装食物。
## 题目描述

小 E 的逃跑路线可以被看作是在 $n$ 个岛屿上，这些岛屿由 $n-1$ 条航线两两相连。

每个岛上都有足够的补给。**假设他每在海上航行一天，就要花费一个单位的食物**。黑心老板规定，**能装 $k$ 单位的食物的背包将会卖 $k$ 万元**。

PF 可以命令在任意两个**通过时间不超过 $d$**，**并且岛 $v$ 到岛 $u$ 的航线上至少有 $q$ 个岛屿**（**不包括 $u$ 和 $v$**）的岛屿 $u$ 与 $v$ 之间建立一条双向航线，通过这条航线的时间为 $\left\lfloor \dfrac{time(u \to v)}{2}\right\rfloor$。由于经济问题，**他只能建造一条额外的航线**。

小 E 可以根据官方给出的航线（**包括新增的航线**）确认 PF 到每个岛上的**最短时间**。

PF 将会在 $t$ 时发现小 E 逃走并开始追击。

为了节省钱，同时逃脱 PF 的追捕，小 E 想请你帮他编一个程序，计算最小的 $k$，使得他能够顺利逃脱到至少 $l$ 个岛屿。

**补给不需要时间，中途抓住也算抓住，同时到达则不算。**

**在岛屿上进行补给不需要时间，可以无限进行补给，只要背包装得下。**

题意概括：

有两个人 $a$，$b$ 和一颗 $n$ 个节点组成的树，$a$ 比 $b$早出发 $t$ 秒。如果两个节点之间通过时间不超过 $d$ 则 $b$ 可以在这两点之间建一条通过时间为 $\left\lfloor \dfrac{time(u \to v)}{2}\right\rfloor$ 的线路，求一个方案使 $a$ 至少到 $l$ 个点的最短时间不比 $b$ 长，并在此基础下要求岛屿之间距离最大值尽量小。
## 输入格式

第一行五个整数，$n,t,d,l,q$，表示岛屿的数量，PF 发现的时间，建立航线要求的通过时间范围，至少要到达的岛屿数量，以及建立航线所要求的中间岛屿的数量。他们的出发点均为点 $1$ 。

接下来 $n-1$ 行，每行四个整数 $u,v,p_i,e_i$，表示岛屿 $u$ 和岛屿 $v$ 之间有一条道路。$p_i$ 表示小 E 走这条航线的时间，$e_i$ 表示 PF 走这条航线的时间。**航线为双向** 。
## 输出格式

若有解，输出共两行。

第一行一个整数 $k$，表示最小能够逃脱所需要的钱数（单位：万元）。

第二行一个整数 $r$，表示用 $k$ 万元买背包时的能跑到的岛屿数量（ $1$ 号岛也算在内）。

若无解，只需输出 "no solution" (引号不需要输出)。
## 样例

### 样例输入 #1
```
5 3 20 4 2
1 2 5 5
2 3 5 5
2 4 7 10
1 5 4 1
```
### 样例输出 #1
```
7
4
```
### 样例输入 #2
```
5 2 6 3 2
1 2 5 3
2 3 8 6
1 4 8 2
2 5 4 6
```
### 样例输出 #2
```
5
3
```
### 样例输入 #3
```
5 0 23 4 1
1 2 21 26
1 3 14 16
3 4 4 5
1 5 19 18
```
### 样例输出 #3
```
no solution
```
## 提示

【样例解释】

样例 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/sc3vdm8k.png)

对于样例 $1$，最后能到的点为 $1,2,4,5$，最小花费为 $7$。由于狱长 PF 从点 $3\to 5$ 要经过点为 $5\to1\to2\to3$，满足中间的点数 $\ge q$，故狱长 PF 可以连边点 $3$ 和点 $5$。如果狱长 PF 选择连边 $5\to3$，那么到点 $3$ 的时间为 $3+1+ \left\lfloor \dfrac{1+5+5}{2}\right\rfloor = 9$。而小 E 到点 $3$ 的最短时间为 $5 + 5 = 10$，不满足条件，故无论 $k$ 的大小，点 $3$ 都是不可到达的。


------------

【数据范围】

| 测试点编号 | $n\le$ | $t\le$ | $p_i,e_i\le$ |    $d\le$    | 时间限制| 空间限制 |特点|
| :----------: | :----------: | :----------: | :----------: | :----------: |:-----: | :----------: |:----------: |
|$1$ | $10$ | $50$ | $50$ | $50$ |$1s$ | $128M$ |加边操作 不影响答案|
|$2$ | $16$ | $50$ | $50$ | $50$ |$1s$ | $128M$ |无|
| $3,4$ | $500$ | ${500}$ | ${500}$ |$500$ | $1s$ |  $128M$ |加边操作 不影响答案|
| $5$ | $500$ | ${500}$ | ${500}$ |${500}$ | $1s$ |  $128M$ |$q = 0$|
| $6,7$ | $500$ | ${500}$ | ${500}$ |${500}$ | $1s$ |  $128M$ |无|
| $8$ | $\small{2.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ | $1s$ | $128M$ |加边操作 不影响答案|
| $9,10$ | $\small{2.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ | $1s$ | $128M$ |$q = 0$|
| $11 \sim 14$ | $\small{2.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ | $1s$ | $128M$ |无|
| $15$ | $\small{2.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ | $1s$ | $256M$ |无|
| $16$ | $\small{7.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ |  $2s$ | $256M$ |无|
| $17$ | $\small{7.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ |  $1s$ | $256M$ |无|
| $18 \sim 20$ | $\small{7.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ |  $3s$ |$512M$ |无|

对于 $100 \%$ 的数据，$n\le 7.5\times 10^3$，$1\le l\le n$，$0\le t \le 10^8$，$0 \le u_i<v_i \le n$，$1\le p_i,e_i,d\le 10^8$，$0\le q\le 20$。

**保证可能新建立的双向航线方案数不超过 $5 \times 10^6$**。



---

---
title: "边三连通分量"
layout: "post"
diff: 省选/NOI-
pid: P6658
tag: ['图论', '深度优先搜索 DFS', 'Tarjan']
---
# 边三连通分量
## 题目背景

对于一张无向图 $G = (V, E)$。

- 我们称两个点 $u, v ~ (u, v \in V, u \neq v)$ 是边三连通的，当且仅当存在三条从 $u$ 出发到达 $v$ 的，相互没有公共边的路径。
- 我们称一个点集 $U ~ (U \subseteq V)$ 是边三连通分量，当且仅当对于任意两个点 $u', v' ~ (u', v' \in U, u' \neq v')$ 都是边三连通的。
- 我们称一个边三连通分量 $S$ 是极大边三连通分量，当且仅当不存在 $u \not \in S$ 且 $u \in V$，使得 $S \cup \{u\}$ 也是边三连通分量。
## 题目描述

给出一个 $n$ 个点，$m$ 条边的无向图 $G = (V, E)$，$V = \{1, 2, \ldots, n\}$，请求出其所有的极大边三连通分量。
## 输入格式

第一行输入两个整数 $n, m$，表示点数、边数。

接下来 $m$ 行，每行输入两个数 $u, v$，表示图上的一条边。
## 输出格式

第一行输出一个整数 $s$，表示极大边三连通分量个数。

接下来输出 $s$ 行，每行若干整数，表示一个极大边三连通分量内所有点。

对于单个极大边三连通分量，请将点按照标号升序输出。对于所有极大边三连通分量，请按照点集内编号最小的点升序输出。
## 样例

### 样例输入 #1
```
4 5
1 3
1 2
4 1
3 2
3 4
```
### 样例输出 #1
```
3
1 3
2
4
```
### 样例输入 #2
```
17 29
1 2
1 10
1 10
2 3
2 8
3 4
3 5
4 6
4 6
5 6
5 6
5 7
7 8
7 11
7 12
7 17
7 17
8 9
9 10
11 12
11 17
12 13
12 16
13 14
13 15
13 16
14 15
14 16
15 16
```
### 样例输出 #2
```
7
1 10
2 8
3 4 5 6
7 11 17
9
12
13 14 15 16
```
## 提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/eqpng8sy.png)

如图，$1 \to 3$ 共有 $(1, 2, 3)$，$(1, 3)$，$(1, 4, 3)$ 三条路径，它们互相都没有相交的边。因此 $1$ 与 $3$ 在同一个边三连通分量中。

由于 $2$，$4$ 点度都只有 $2$，不可能有三条边不相交的到其它点的路径，因此它们自己形成边三联通分量。

---

#### 数据范围

- 对于 $30\%$ 的数据，$n \le 100$，$m \le 200$。
- 对于 $50\%$ 的数据，$n \le 1000$，$m \le 2000$。
- 对于 $80\%$ 的数据，$n \le 10 ^ 5$，$m \le 2 \times 10 ^ 5$。
- 对于 $100\%$ 的数据，$1 \le n, m \le 5 \times 10 ^ 5$，$1 \le u, v \le n$。可能有重边和自环。

---

#### 来源

题目搬运自 [Three-Edge-Connected Components](https://judge.yosupo.jp/problem/three_edge_connected_components)。


---

---
title: "[NOIP2022] 建造军营"
layout: "post"
diff: 省选/NOI-
pid: P8867
tag: ['2022', 'NOIP 提高组', 'O2优化', '树形 DP', '强连通分量', 'Tarjan', '容斥原理']
---
# [NOIP2022] 建造军营
## 题目描述

A 国与 B 国正在激烈交战中，A 国打算在自己的国土上建造一些军营。

A 国的国土由 $n$ 座城市组成，$m$ 条双向道路连接这些城市，使得**任意两座城市均可通过道路直接或间接到达**。A 国打算选择一座或多座城市（**至少一座**），并在这些城市上各建造一座军营。

众所周知，军营之间的联络是十分重要的。然而此时 A 国接到情报，B 国将会于不久后袭击 A 国的一条道路，但具体的袭击目标却无从得知。如果 B 国袭击成功，这条道路将被切断，可能会造成 A 国某两个军营无法互相到达，这是 A 国极力避免的。因此 A 国决定派兵看守若干条道路（**可以是一条或多条，也可以一条也不看守**)，A 国有信心保证被派兵看守的道路能够抵御 B 国的袭击而不被切断。

A 国希望制定一个建造军营和看守道路的方案，使得 B 国袭击的无论是 A 国的哪条道路，都不会造成某两座军营无法互相到达。现在，请你帮 A 国计算一下可能的建造军营和看守道路的方案数共有多少。由于方案数可能会很多，你只需要输出其对 $1,000,000,007\left(10^{9}+7\right)$ 取模的值即可。两个方案被认为是不同的，当且仅当存在至少一 座城市在一个方案中建造了军营而在另一个方案中没有，或者存在至少一条道路在一个 方案中被派兵看守而在另一个方案中没有。

## 输入格式

第一行包含两个正整数 $n,m$，分别表示城市的个数和双向道路的数量。

接下来 $m$ 行，每行包含两个正整数 $u_{i},v_{i}$，描述一条连接 $u_{i}$ 和 $v_{i}$ 的双向道路。保证没有重边和自环。
## 输出格式

输出一行包含一个整数，表示建造军营和看守道路的方案数对 $1,000,000,007\left(10^{9}+ 7\right)$ 取模的结果。
## 样例

### 样例输入 #1
```
2 1
1 2
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
4 4
1 2
2 3
3 1
1 4
```
### 样例输出 #2
```
184
```
### 样例输入 #3
```
见附加文件里的 barrack/barrack3.in
```
### 样例输出 #3
```
见附加文件里的 barrack/barrack3.ans
```
### 样例输入 #4
```
见附加文件里的 barrack/barrack4.in
```
### 样例输出 #4
```
见附加文件里的 barrack/barrack4.ans
```
## 提示

### 样例 1 解释

A 国有两座城市，一条道路连接他们。所有可能的方案如下：

- 在城市 $1$ 建军营, 不看守这条道路;
- 在城市 $1$ 建军营, 看守这条道路;
- 在城市 $2$ 建军营, 不看守这条道路;
- 在城市 $2$ 建军营, 看守这条道路;
- 在城市 $1,2$ 建军营, 看守这条道路。

### 数据规模与约定

对所有数据，保证 $1 \leq n \leq 5 \times 10^5$，$n - 1 \leq m \leq 10^6$，$1 \leq u_i, v_i \leq n$，$u_i \neq v_i$。

各测试点的信息如下

|测试点编号 | $n \leq $ | $m \leq $| 特殊条件 |
| :-: | :-: | :-: | :-: |
| $1 \sim 3$ | $8$ | $10$ | 无 |
| $4 \sim 7$ | $16$ | $25$ | 无 |
| $8 \sim 9$ | $3000$ | $5000$ | 无 |
| $10 \sim 11$ | $5 \times 10^5$ | $10^6$ | 特殊性质 $\mathrm{A}$ |
| $12 \sim 14$ | $5 \times 10^5$ | $10^6$ | $m = n - 1$ |
| $15 \sim 16$ |  $5 \times 10^5$ | $10^6$ | $m = n$ |
| $17 \sim 20$ | $5 \times 10^5$ | $10^6$ | 无 |

特殊性质 $\mathrm{A}$：保证 $m=n-1$ 且第 $i$ 条道路连接城市 $i$ 与 $i+1$。 


---

