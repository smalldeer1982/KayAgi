---
title: "「Daily OI Round 3」City Planning"
layout: "post"
diff: 省选/NOI-
pid: P10129
tag: ['网络流', '洛谷原创', 'O2优化', '最小割', '线性规划']
---
# 「Daily OI Round 3」City Planning
## 题目背景

只要不失去你的崇高，整个世界都会为你敞开。
## 题目描述

Provence-Alpes-Côte d'Azur 的管理者们遇上大麻烦了！他们邀请你来解决城市规划的问题。

这群管理者一共有 $t$ 人，并且这个地区一共有 $n$ 个城镇，第 $i$ 个城镇内部又有 $k_i$ 个村庄，通过 $p_i$ 条道路连接，第 $j$ 条道路双向连接第 $i$ 个城镇中的第 $u_{i,j}$ 和 $v_{i,j}$ 两个村庄，管理道路的人是第 $w_{i,j}$ 个，客流量是 $z_{i,j}$。

为了管理组内部的团结，保证每个人在同一个城镇最多管理 $1$ 条道路。

现在这些城镇中的村庄和村庄之间的道路都遭到了损坏，管理者们急于恢复这些城镇内的交通。这些城镇互相之间有 $m$ 条高铁，每条高铁连接了 $u,v$ 两个城镇，并且当初为了设计的优美，这 $n$ 个城镇和 $m$ 条高铁构成了一个**二分图**。

对于每个城镇 $i$，你都需要帮助管理组选择一个参数 $c_i(1 \le c_i \le k_i)$，修复一些村庄，编号在 $1 \sim c_i$ 之间的村庄都会被修复，如果道路的两端的村庄都修复了，那么这条道路就会自动修复。因此第 $i$ 个城镇中会产生 $b_{i,c_i}$ 的花费。

对于管理者 $i$ 来说，如果存在两条他在不同城镇管理的道路都没有被修复，并且这两条道路所属的城镇有高铁**直接连接**，你需要支付这两条道路的人流量的乘积来弥补损失，这样管理者 $i$ 才会高兴。（对于**任意**两条满足上述条件的道路你都需要弥补损失，而不是对于每个管理者只需要弥补一对道路的损失）

为了让管理组的成员都高兴并且给出的方案符合题目的要求（即 $1 \le c_i \le k_i$），你需要提前计算好自己至少需要支付多少钱以应对这一群管理者们的刁难。


## 输入格式

第一行三个整数 $n,m,t$ 表示城镇的数量，城镇间的高铁的数量和管理组人员的数量。

接下来 $m$ 行每行两个整数 $x,y$ 表示这条高铁连接的两个城镇的编号。

接下来 $n$ 组输入，对于第 $i$ 组输入，格式如下：

第一行两个整数 $k_i,p_i$ 表示第 $i$ 个城镇有 $k_i$ 个村庄，$p_i$ 条道路。

第二行 $k_i$ 个整数，第 $j$ 个整数表示当 $c=j$ 时的花费 $b_{i,j}$。

接下来 $p_i$ 行，每行四个整数 $u_{i,j},v_{i,j},w_{i,j},z_{i,j}$，表示有一条边连接 $i$ 号城镇的第 $u_{i,j}$ 个村庄和第 $v_{i,j}$ 个村庄，并且管理道路的人是第 $w_{i,j}$ 个，客流量为 $z_{i,j}$。
## 输出格式

一行一个整数表示让所有管理者都高兴的最小花费是多少。
## 样例

### 样例输入 #1
```
2 2 3
2 1
2 1
1 3
3
1 1 2 3
1 1 1 1
1 1 3 3
2 0
7 6
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
3 1 3
1 2
3 2
1 2 3
1 2 1 3
2 3 2 2
2 2
1 100
1 1 1 3
1 2 2 1
5 1
5 0 5 5 5
4 5 1 3
```
### 样例输出 #2
```
4
```
### 样例输入 #3
```
5 6 5
4 3
3 5
1 2
2 1
3 4
3 5
2 0
37 44
4 2
33 2 43 49
3 1 3 6
3 4 4 6
6 4
4 23 0 9 35 22
3 4 2 7
3 4 5 3
2 1 3 2
4 4 4 10
3 2
14 41 35
2 2 4 1
3 3 2 5
3 5
27 39 9
3 3 2 1
3 2 3 3
2 1 1 5
2 1 5 3
1 2 4 8
```
### 样例输出 #3
```
71
```
## 提示

#### 【样例解释 #1】

我们可以选择 $c_1=1,c_2=2$，那么花费就是 $b_{1,c_1}+b_{2,c_2}=3+6=9$，而没有一个管理员你需要讨好。

#### 【样例解释 #2】

我们可以选择 $c_1=1,c_2=1,c_3=2$，那么花费就是 $b_{1,c_1}+b_{2,c_2}+b_{3,c_3}=1+1=2$，但是管理员 $2$ 在城镇 $1$ 中管理的道路 $2 \to 3$ 不可能被修复，在城镇 $2$ 中管理的道路 $1 \to 2$ 不可能被修复，你就需要花费 $2 \times 1 = 2$ 的代价讨好管理员 $2$，总的代价就是 $4$。

你并不需要讨好管理员 $1$，哪怕他在城镇 $1$ 和 $3$ 中分别有一条道路不可能被修复，因为城镇 $1$ 和 $3$ 没有高铁相连，所以你不需要为此支付额外的资金。

#### 【数据范围】

对于全部数据保证：$1 \le n \le 50$，$1 \le k_i \le 100$，$0 \le p_i \le t$，$0 \le m \le 500$，$1 \le t \le 50$，$1 \le x,y \le n$，$x \ne y$，$0 \le b_{i,j} \le 10^9$，$1 \le u_{i,j},v_{i,j} \le k_i$，$1 \le w_{i,j} \le t$，$1 \le z_{i,j} \le 10^4$。

$n$ 个城镇和 $m$ 条高铁构成的图是一个二分图，每个管理员在同一个村庄管理的道路数量不超过 $1$。

**可能有连接同一对城镇的不同的高铁，不会出现自己连向自己的高铁。但城镇中的村庄可能会有自己连向自己的道路，也可能出现连接同一对村庄的不同的道路。**


---

---
title: "【烂题杯 Round 1】糖果色的梦"
layout: "post"
diff: 省选/NOI-
pid: P10889
tag: ['网络流', 'O2优化', '费用流', '线性规划']
---
# 【烂题杯 Round 1】糖果色的梦
## 题目描述

小 A 做了一个糖果色的梦，于是他打算买一些糖果送给他的 $n$ 个小朋友。

小 A 可以零售地购买糖果，也可以批发地购买糖果，他还可以批发地回收糖果。

- 零售地购买糖果：每次小 A 可以给一个小朋友购买一个糖果，这将会花费 $1$ 元；

- 批发地购买糖果：每次小 A 可以给连续且不少于 $k$ 个小朋友分别购买一个糖果，设小朋友的个数为 $l$，这将会花费 $l-B$ 元；

- 批发地回收糖果：每次小 A 可以给连续且不少于 $k$ 个小朋友分别收回一个糖果，这将会获得 $C$ 元；

第 $i$ 个小朋友都希望自己得到不少于 $a_i$ 个糖果。求小 A 满足所有小朋友的希望的最小代价。
## 输入格式

第一行输入两个正整数 $n$、$k$，表示小朋友数量、批发最少需要的小朋友数量。

接下来输入两个整数 $B$、$C$。

接下来一行 $n$ 个非负整数 $a_1,a_2,\cdots,a_n$，表示每个小朋友希望的糖果个数。
## 输出格式

输出一行一个整数，表示最小代价。
## 样例

### 样例输入 #1
```
4 2
1 1
1 2 3 4
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
10 5
1 3
1 1 4 5 1 4 1 9 19 81
```
### 样例输出 #2
```
124
```
## 提示

**样例 1 解释：**

我们给 $[1,2]$ 小朋友批发分别购买 $1$ 个糖果，代价为 $1$；给 $[3,4]$ 小朋友批发分别购买 $3$ 个糖果，代价为 $3$；给 $2$ 小朋友单独购买糖果，代价为 $1$；给 $4$ 小朋友单独购买糖果，代价为 $1$。总共代价为 $6$。

**数据范围：**

对于 $20\%$ 数据，满足 $1\le k\le n\le 10$。

对于 $40\%$ 数据，满足内存限制至少为 512 MB。

对于 $100\%$ 数据，满足 $1\le k\le n\le 1000$，$0\le B\le k$，$0\le C\le k-B$，$0\le a_i\le 10^9$。满足内存限制至少为 10 MB。


---

---
title: "[COTS 2019] 疏散 Sklonište"
layout: "post"
diff: 省选/NOI-
pid: P11225
tag: ['2019', '网络流', '二分图', 'COCI（克罗地亚）']
---
# [COTS 2019] 疏散 Sklonište
## 题目背景


译自 [Izborne Pripreme 2019 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2019/) D2T2。$\texttt{4s,0.5G}$。
## 题目描述


给定 $N$ 个点 $M$ 条边的无向连通图，边有边权。有 $K$ 个关键点 $A_1,A_2,\cdots,A_K$，**容量**为 $S_1,S_2,\cdots,S_K$。

图中的居民要疏散。也就是说，你需要构造一个序列 $B_1,B_2,\cdots,B_N$，使得：

- $\forall 1\le i\le N$，$1\le B_i\le K$；
- 对于 $1\le i\le K$，定义 $\displaystyle \mathrm{cnt}_i=\sum_{1\le j\le N} [B_j=i]$，也就是 $i$ 在 $B$ 序列中出现的次数。则 $\mathrm{cnt}_i\le S_i$。

定义序列 $B$ 的**疏散时间**为 $\displaystyle \max_{1\le i\le N} \operatorname{dist}(i,A_{B_i})$，其中 $\operatorname{dist}(u,v)$ 指图中 $u,v$ 间最短路的长度。

求出疏散时间的最小值。保证 $\sum_i S_i\ge N$。

## 输入格式


第一行，三个正整数 $N,M,K$；

接下来 $M$ 行，每行三个正整数 $u,v,w$，描述一条无向边 $(u,v)$，边权为 $w$。保证 $u\neq v$。

接下来 $K$ 行，每行两个正整数描述 $A_i,S_i$。

保证 $\sum_i S_i\ge N$。
## 输出格式


输出一行一个数，表示答案。
## 样例

### 样例输入 #1
```
5 5 2
1 2 1
1 3 3
2 3 4
3 4 1
4 5 1
1 10
4 2
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
7 8 3
1 2 5
2 3 3
3 4 5
1 4 1
4 5 7
5 6 2
6 7 1
4 7 4
3 3
7 3
6 2
```
### 样例输出 #2
```
5
```
## 提示


对于 $100\%$ 的数据，保证：
- $1\le N\le 10^5$；
- $N-1\le M\le 3\times 10^5$；
- $1\le K\le 17$；
- 给定图连通，无自环；
- $1\le w,S_i\le 10^9$；
- $1\le u,v,A_i\le N$；
- $S_i$ 两两不同；
- $\sum_i S_i\ge N$。


| 子任务编号 | $N\le $ | $M\le $ | $K\le$    | 得分 |  
| :--: | :--: |:--: |  :--: | :--: | 
| $ 1 $    | $ 100 $ |   $ 500 $   |  $5$ | $30$ |
| $ 2 $    | $ 10^5 $ |  $ 3\times 10^5 $   |  $10 $ | $30$ |
| $ 3 $    | $ 10^5 $ | $ 3\times 10^5 $   |  $17$ |  $40$ |


---

---
title: "[COCI 2024/2025 #2] 三角 / Trokuti"
layout: "post"
diff: 省选/NOI-
pid: P11433
tag: ['2024', '网络流', 'Special Judge', '随机化', 'COCI（克罗地亚）']
---
# [COCI 2024/2025 #2] 三角 / Trokuti
## 题目背景

译自 [COCI 2024/2025 #2](https://hsin.hr/coci/) T5。$\texttt{4s,0.5G}$。满分为 $120$。

## 题目描述


给定一张 $6n$ 个节点 $m$ 条边的无向图。保证这张图可以被**划分**成 $2n$ 个 $K_3$（大小为 $3$ 的完全图）。

求出这张图中的 $n$ 个 $K_3$，不能有重复顶点。
## 输入格式


**本题单个测试点内有多组测试数据。**

第一行，一个正整数 $T$，表示测试数据组数。

接下来描述 $T$ 组数据：

第一行，两个整数 $n,m$。

接下来 $m$ 行，每行两个正整数 $u,v$，表示图中的一条无向边。
## 输出格式

每组数据输出 $n$ 行，每行三个整数，表示 $K_3$ 的三个顶点。

## 样例

### 样例输入 #1
```
1
1 6
1 2
2 3
1 3
4 5
4 6
5 6
```
### 样例输出 #1
```
1 2 3
```
### 样例输入 #2
```
1
3 26
4 7
4 9
7 9
4 5
4 8
5 8
4 12
4 18
12 18
3 7
3 9
15 5
15 8
6 13
6 1
13 1
6 14
6 17
14 17
6 2
6 10
2 10
16 13
16 1
11 14
11 17
```
### 样例输出 #2
```
1 6 13
3 7 9
4 5 8
```
## 提示



对于 $100\%$ 的数据，保证：

- $1\le T\le 100$；
- $1\le n,\sum n\le 300$；  
- $0\le m\le 10^6$；
- $1\le u,v\le 6n$。


| 子任务编号 | $n,\sum n$ |  特殊性质 | 得分 |  
| :--: | :--: | :--: |:--: | 
| $ 1 $    | $\le 300$ | A |   $ 13 $   |  
| $ 2 $    | $=3$ | B |  $ 18 $   |  
| $ 3 $    | $=6$ | B |  $ 18 $   |  
| $ 4 $    | $\le 300$ |   |  $ 71 $   |  

- 特殊性质 A：$m=6n$。
- 特殊性质 B：$T=1$。


---

---
title: "[ROIR 2019] 配对 (Day 2)"
layout: "post"
diff: 省选/NOI-
pid: P11502
tag: ['2019', '网络流', 'Special Judge', 'ROIR（俄罗斯）']
---
# [ROIR 2019] 配对 (Day 2)
## 题目背景

翻译自 [ROIR 2019 D2T4](https://neerc.ifmo.ru/school/archive/2018-2019/ru-olymp-regional-2019-day2.pdf)。
## 题目描述

宇宙考古科学家在邻近星系的一颗行星上发现了 $n$ 件古代文物，并将它们编号为 $1$ 到 $n$。每件文物有 $k$ 个不同的参数，每个参数都是一个整数。文物 $i$ 的参数为 $a_{i, 1}, a_{i, 2}, \dots, a_{i, k}$。他们惊奇的发现，所有文物的第一个参数都是不同的，即对于所有 $i \neq j$，都有 $a_{i, 1} \neq a_{j, 1}$。但是，其他参数可能相同。

科学家们还发现了一段文字，根据这段文字，要激活文物，需要将它们按特定方案配对。称一个配对方案是有效的，当且仅当对于每个 $1\le t\le k$，可以确定一个数 $b_{t}$，使其在**每对文物**的第 $t$ 个参数值之间。也就是说，在这个配对方案中，对于所有配对的文物 $i$ 和 $j$，必须满足 $a_{i, t} \leq b_{t} \leq a_{j, t}$ 或 $a_{i, t} \geq b_{t} \geq a_{j, t}$。

现在，科学家们想知道这段文字是否解读正确。为此，你需要需要判断是否存在有效的配对方案，使得所有文物可以两两正确配对。如果可以，你还需要找到这样一个配对方案。
## 输入格式

第一行输入两个整数 $n$ 和 $k$，表示文物数量和参数数量。

接下来 $n$ 行，每行包含 $k$ 个整数 $a_{i, 1}, a_{i, 2}, \dots, a_{i, k}$，表示文物的参数。
## 输出格式

如果不存在有效的配对方式，输出 `NO`。

否则，第一行输出 `YES`。接下来 $\frac n 2$ 行，每行包含两个整数，表示配对的文物编号。每个文物只能出现一次。

如果有多个合法的配对方案，可以输出任意一个。
## 样例

### 样例输入 #1
```
6 2
8 6
1 5
6 3
3 1
4 7
7 2
```
### 样例输出 #1
```
YES
1 4
2 6
3 5
```
### 样例输入 #2
```
4 3
1 -1 -1
2 1 1
3 -1 1
4 1 -1
```
### 样例输出 #2
```
NO
```
## 提示

### 样例解释

样例 $1$ 中，一个合法的配对方案为 $(8, 6) - (3, 1), (1, 5) - (7, 2), (6, 3) - (4, 7)$。此时可以选择 $b_1=b_2=4$。

### 数据范围

数据中 Subtask 0 为样例。

| 子任务 | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $n\le10$ |
| $2$ | $7$ | $k=1$ |
| $3$ | $15$ | 对于任意 $t$，所有 $a_{i,t}$ 互不相同 |
| $4$ | $15$ | $k\le2$ |
| $5$ | $26$ | $n\le400$ |
| $6$ | $27$ | 无特殊性质 |

对于 $100\%$ 的数据，$2\le n\le2\times10^5$，$n$ 为偶数，$1\le k\le7$，$|a_{i,j}|\le10^9$，所有 $a_{i,1}$ 互不相同。




---

---
title: "[PA 2016] 任务排序 /  Szeregowanie zadań"
layout: "post"
diff: 省选/NOI-
pid: P11614
tag: ['2016', '网络流', '图论建模', 'PA（波兰）']
---
# [PA 2016] 任务排序 /  Szeregowanie zadań
## 题目背景


译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R5 Szeregowanie zadań [B] (SZE)。
## 题目描述


有 $n$ 个任务，编号 $1\sim n$。任务 $i$ 有三个参数 $p_i,c_i,k_i$，含义为：
- 这个任务必须在时刻 $p_i$（或者 $p_i$ 之后）开始执行；
- 这个任务需要 $c_i$ 单位时间；（意思是，它需要在处理器上运行的总时间为 $c_i$）
- 这个任务必须在时刻 $k_i$（或者 $k_i$ 之前）完成。

有 $m$ 个处理器用来执行任务。

一个处理器同一时间只能处理一个任务，一个任务同一时间只能在一个处理器上被处理。每个任务可以在处理时被中断任意次，可以在任意时刻（不一定是整数时刻）被中断，在中断后可以分配给另一个处理器处理。

是否存在一种策略可以满足所有要求？
## 输入格式


第一行两个正整数 $n,m$。

接下来 $n$ 行，每行三个整数 $p_i,k_i,c_i$，描述一个任务。

## 输出格式

如果存在，输出一行一个 $\texttt{TAK}$；否则输出一行一个 $\texttt{NIE}$。

## 样例

### 样例输入 #1
```
3 2
3 8 3
2 5 2
3 7 3
```
### 样例输出 #1
```
TAK
```
### 样例输入 #2
```
2 1
0 1 1
0 1 1
```
### 样例输出 #2
```
NIE
```
## 提示


- $1\le n,m\le 100$；
- $0\le p_i\lt k_i\le 10^6$；
- $1\le c_i\le k_i-p_i$。


---

---
title: "教辅的组成"
layout: "post"
diff: 省选/NOI-
pid: P1231
tag: ['网络流', '洛谷原创']
---
# 教辅的组成
## 题目背景

滚粗了的 HansBug 在收拾旧语文书，然而他发现了什么奇妙的东西。

## 题目描述

蒟蒻 HansBug 在一本语文书里面发现了一本答案，然而他却明明记得这书应该还包含一份练习题。然而出现在他眼前的书多得数不胜数，其中有书，有答案，有练习册。已知一个完整的书册均应该包含且仅包含一本书、一本练习册和一份答案，然而现在全都乱做了一团。许多书上面的字迹都已经模糊了，然而 HansBug 还是可以大致判断这是一本书还是练习册或答案，并且能够大致知道一本书和答案以及一本书和练习册的对应关系（即仅仅知道某书和某答案、某书和某练习册有可能相对应，除此以外的均不可能对应）。既然如此，HansBug 想知道在这样的情况下，最多可能同时组合成多少个完整的书册。


## 输入格式

第一行包含三个正整数 $N_1,N_2,N_3$，分别表示书的个数、练习册的个数和答案的个数。

第二行包含一个正整数 $M_1$，表示书和练习册可能的对应关系个数。

接下来 $M_1$ 行每行包含两个正整数 $x,y$，表示第 $x$ 本书和第 $y$ 本练习册可能对应。（$1\leq x \leq N_1$，$1 \leq y \leq N_2$）

第 $M_{1}+3$ 行包含一个正整数 $M_2$，表述书和答案可能的对应关系个数。

接下来 $M_2$ 行每行包含两个正整数 $x,y$，表示第 $x$ 本书和第 $y$ 本答案可能对应。（$1 \leq x \leq N_1$，$1 \leq y \leq N_3$）

## 输出格式

输出包含一个正整数，表示最多可能组成完整书册的数目。

## 样例

### 样例输入 #1
```
5 3 4
5
4 3
2 2
5 2
5 1
5 3
5
1 3
3 1
2 2
3 3
4 3

```
### 样例输出 #1
```
2
```
## 提示

样例说明：

如题，$N_1=5$，$N_2=3$，$N_3=4$，表示书有 $5$ 本、练习册有 $3$ 本、答案有 $4$ 本。

$M_1=5$，表示书和练习册共有 $5$ 个可能的对应关系，分别为：书 $4$ 和练习册 $3$ 、书 $2$ 和练习册 $2$ 、书 $5$ 和练习册 $2$ 、书 $5$ 和练习册 $1$ 以及书 $5$ 和练习册 $3$。

$M_2=5$，表示数和答案共有 $5$ 个可能的对应关系，分别为：书 $1$ 和答案 $3$、书 $3$ 和答案 $1$、书 $2$ 和答案 $2$、书 $3$ 和答案 $3$ 以及书 $4$ 和答案 $3$。

所以，以上情况的话最多可以同时配成两个书册，分别为：书 $2$ 练习册 $2$ 答案 $2$、书 $4$ 练习册 $3$ 答案 $3$。


数据规模：

![](https://cdn.luogu.com.cn/upload/image_hosting/srj2v9um.png)

对于数据点 $1,2,3$，$1\le M_1,M_2\leq 20$。

对于数据点 $4\sim 10$，$1\le M_1,M_2 \leq 20000$。



---

---
title: "餐巾计划问题"
layout: "post"
diff: 省选/NOI-
pid: P1251
tag: ['贪心', '网络流', 'O2优化', '费用流', '网络流与线性规划 24 题']
---
# 餐巾计划问题
## 题目描述

一个餐厅在相继的 $N$ 天里，每天需用的餐巾数不尽相同。假设第 $i$ 天需要 $r_i$ 块餐巾（$i = 1, 2, \dots, N$）。餐厅可以购买新的餐巾，每块餐巾的费用为 $p$ 分；或者把旧餐巾送到快洗部，洗一块需 $m$ 天，其费用为 $f$ 分；或者送到慢洗部，洗一块需 $n$ 天（$n \gt m$），其费用为 $s$ 分（$s \lt f$）。

每天结束时，餐厅必须决定将多少块脏的餐巾送到快洗部，多少块餐巾送到慢洗部，以及多少块保存起来延期送洗。但是每天洗好的餐巾和购买的新餐巾数之和，要满足当天的需求量。

试设计一个算法为餐厅合理地安排好 $N$ 天中餐巾使用计划，使总的花费最小。编程找出一个最佳餐巾使用计划。

## 输入格式

由标准输入提供输入数据。文件第 $1$ 行有 $1$ 个正整数 $N$，代表要安排餐巾使用计划的天数。

接下来的一行是餐厅在相继的 $N$ 天里，每天需用的餐巾数。

最后一行包含 $5$ 个正整数 $p, m, f, n, s$。$p$ 是每块新餐巾的费用；$m$ 是快洗部洗一块餐巾需用天数；$f$ 是快洗部洗一块餐巾需要的费用；$n$ 是慢洗部洗一块餐巾需用天数；$s$ 是慢洗部洗一块餐巾需要的费用。

## 输出格式

将餐厅在相继的 $N$ 天里使用餐巾的最小总花费输出。

## 样例

### 样例输入 #1
```
3
1 7 5 
11 2 2 3 1

```
### 样例输出 #1
```
134

```
## 提示

对于 $100 \%$ 的数据，$1 \le N \le 2 \times 10^3$，$1 \le r_i \le 10^7$，$1 \le p, f, s \le 10^4$。



---

---
title: "[NERC 2020] Button Lock"
layout: "post"
diff: 省选/NOI-
pid: P12901
tag: ['2020', '网络流', 'Special Judge', '费用流', 'ICPC', 'NERC/NEERC']
---
# [NERC 2020] Button Lock
## 题目描述

You are standing in front of the room with great treasures. The only thing stopping you is the door with a push-button combination lock. This lock has $d$ buttons with digits from $0$ to $d - 1$. Whenever you press a button, it stays pushed down. You can not pop back up just one button, but there is a "RESET" button --- pressing it pops up all other buttons. Initially, no buttons are pushed down.

The door instantly opens when some specific set of digits is pushed down. Sadly, you don't know the password for it. Having read the documentation for this specific lock, you found out that there are $n$ possible passwords for this particular lock.  

Find the shortest sequence of button presses, such that all possible passwords appear at least once during its execution. Any shortest correct sequence of button presses will be accepted.
## 输入格式

The first line contains two integers $d$ and $n$ ($1 \le d \le 10$; $1 \le n \le 2^d - 1$).
Next $n$ lines describe possible passwords. Each line contains a string $s_i$ of $d$ zeros and ones: for all $j$ from $1$ to $d$ the $j$-th character is $\tt{1}$ iff the button with the digit $j - 1$ must be pushed down.

All strings $s_i$ are different, and each string contains at least one $\tt{1}$.
## 输出格式

On the first line, print the number $k$ --- the minimum number of button presses.
On the second line, print $k$ tokens, describing the sequence. Whenever you press a button with a digit, print that digit. Whenever you press "RESET", print $\tt{R}$.
## 样例

### 样例输入 #1
```
2 2
10
11
```
### 样例输出 #1
```
2
0 1
```
### 样例输入 #2
```
3 4
001
111
101
011
```
### 样例输出 #2
```
6
2 0 R 1 2 0
```
## 提示

In the second example, the sequence $\tt{1 2 R 2 0 1}$ is also possible.


---

---
title: "[GCJ 2022 #2] Saving the Jelly"
layout: "post"
diff: 省选/NOI-
pid: P12995
tag: ['2022', '网络流', 'Special Judge', '二分图', 'Google Code Jam']
---
# [GCJ 2022 #2] Saving the Jelly
## 题目描述

Mr. Jolly teaches football (or soccer, for US speakers) to $\mathbf{N}$ children numbered from 1 to $\mathbf{N}$. He has taken to leaving sweets on the field where the games take place, one for each child. After the game is finished, each child can grab and eat one sweet as their reward.

The children are tired after games, so each child wants to grab the sweet closest to them (using Euclidean distance). This could lead to fights - if the same sweet is closest to two or more children. To avoid that, after the game all the children stop where they are, and Mr. Jolly calls out their names, one by one. When a child's name is called, they grab the closest sweet to them (out of the ones that weren't already grabbed, of course). In the case where two or more sweets are tied for the smallest distance, Mr. Jolly can decide which one the child grabs.

![](https://cdn.luogu.com.cn/upload/image_hosting/h3px6piy.png)

This has worked very well for Mr. Jolly for a while now, but today disaster struck! While laying out the sweets, Mr. Jolly accidentally dropped his blueberry jelly that he planned to eat after all the children go home. So now there are $\mathbf{N}$ children on the field, and $\mathbf{N}+1$ sweets. The sweets are numbered from 1 to $\mathbf{N}+1$, with sweet 1 being Mr. Jolly's blueberry jelly. Is there a way for Mr. Jolly to save his blueberry jelly by calling the children's names in such an order that the blueberry jelly is the one sweet left over?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test begins with a line containing a single integer, $\mathbf{N}$, the number of children on the field. The next $\mathbf{N}$ lines describe the positions of the children. Each of these lines contains two integers, $\mathbf{X}_{\mathbf{i}}$ and $\mathbf{Y}_{\mathbf{i}}$, representing the position of the $i$-th child after the game ends. Then there are $\mathbf{N}+1$ more lines that describe the positions of sweets after the game, where the first of the sweets is Mr. Jolly's blueberry jelly. Each of these lines contains two integers, $\mathbf{X}_{\mathbf{j}}$ and $\mathbf{Y}_{\mathbf{j}}$, representing the position of the $j$-th sweet.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is IMPOSSIBLE if there is no way Mr. Jolly can choose the children (and break ties for the closest sweet) to leave his blueberry jelly uneaten. Otherwise, if Mr. Jolly can save his blueberry jelly, $y$ is POSSIBLE. If Mr. Jolly can save his jelly, output $\mathbf{N}$ additional lines representing the order the children will go and which jellies they will pick. The $i$-th line should contain two integers $A_{i}$ and $B_{i}$ representing that child $A_{i}$ will go next and will pick sweet $B_{i}$. The sweet $B_{i}$ must be the closest (or tied for the closest) sweet to child $A_{i}$ when they go to pick their sweet.
## 样例

### 样例输入 #1
```
4
2
-3 0
-1 0
3 0
-2 -1
-2 1
1
0 0
1 1
2 2
3
10 0
-10 0
0 0
0 5
-1 0
5 0
0 -5
2
3 4
3 4
5 7
3 4
5 7
```
### 样例输出 #1
```
Case #1: POSSIBLE
2 2
1 3
Case #2: IMPOSSIBLE
Case #3: POSSIBLE
3 2
2 4
1 3
Case #4: POSSIBLE
1 2
2 3
```
## 提示

**Sample Explanation**

Sample Case #1 is illustrated in the image above. Notice that each child is equally close to each of the two non-blueberry-jelly sweets. In our solution, Mr. Jolly assigns the second sweet to the second child and the third sweet to the first child, successfully leaving the first sweet (the blueberry jelly) for himself.

In Sample Case #2, the sole child is closer to the blueberry jelly than to the other sweet, so Mr. Jolly cannot prevent his precious blueberry jelly from being eaten.

In Sample Case #3, we present one of many solutions; it is actually possible to call the children in any order.

In Sample Case #4, note that children might share the same position, sweets might share the same position, and children and sweets might share the same position.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $-10^{9} \leq \mathbf{X}_{\mathbf{i}} \leq 10^{9}$, for all $i$.
- $-10^{9} \leq \mathbf{Y}_{\mathbf{i}} \leq 10^{9}$, for all $i$.
- $-10^{9} \leq \mathbf{X}_{\mathbf{j}} \leq 10^{9}$, for all $j$.
- $-10^{9} \leq \mathbf{Y}_{\mathbf{j}} \leq 10^{9}$, for all $j$.

**Test Set 1 (10 Pts, Visible Verdict)**

- Time limit: 10 seconds.
- $1 \leq \mathbf{N} \leq 10$.

**Test Set 2 (18 Pts, Hidden Verdict)**

- Time limit: 45 seconds.
- $1 \leq \mathbf{N} \leq 1000$.


---

---
title: "[GCJ 2022 Finals] Slide Parade"
layout: "post"
diff: 省选/NOI-
pid: P13003
tag: ['2022', '网络流', 'Special Judge', '欧拉回路', '二分图', 'Google Code Jam']
---
# [GCJ 2022 Finals] Slide Parade
## 题目描述

Gooli is a huge company that owns $\mathbf{B}$ buildings in a hilly area, numbered 1 through $\mathbf{B}$. Six years ago, Gooli built slides that allowed employees to go from one building to another. Each slide allows anyone to go from the slide's origin building to the slide's destination building, but not the other way around. Gooli's CEO is very proud of their slides and wants to organize a parade through the slides. She has tasked Melek, Gooli's Head of Transportation and a problem-solving enthusiast, with designing the parade's route.

![](https://cdn.luogu.com.cn/upload/image_hosting/njzcunb7.png)

She has some requirements for the parade route in mind:

* It must start and end at building 1, where her office is located.
* It must visit each building the same number of times. Being in building 1 at the start of the route does not count as a visit.
* It must use each slide at least once.
* It must have at most $10^6$ steps.

Given the layout of buildings and slides, help Melek find a route that satisfies all of the CEO's requirements, if one exists.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing two integers $\mathbf{B}$ and $\mathbf{S}$: the number of buildings and slides, respectively. Then, $\mathbf{S}$ lines follow. The $i$-th of these lines contains two integers $\mathbf{U}_i$ and $\mathbf{V}_i$, indicating that the $i$-th slide goes from building $\mathbf{U}_i$ to building $\mathbf{V}_i$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1). If there is no route that fulfills all the requirements, $y$ must be `IMPOSSIBLE`. If there is, $y$ must be an integer between $\mathbf{S} + 1$ and $10^6 + 1$, inclusive, representing the length of one such route you want to exhibit. In that case, output another line containing $y$ integers $z_1$ $z_2$ $\dots$ $z_y$, where $z_j$ is the $j$-th building in your proposed route. Notice that $z_1 = z_y = 1$ and that each building must appear the same number of times among the $z_j$, except for building 1, which appears exactly one extra time.
## 样例

### 样例输入 #1
```
5
2 2
2 1
1 2
3 4
2 3
1 2
3 2
1 3
3 6
1 2
1 3
2 1
2 3
3 1
3 2
3 4
1 2
2 1
1 3
3 1
4 6
1 2
1 4
2 3
3 2
3 4
4 1
```
### 样例输出 #1
```
Case #1: 7
1 2 1 2 1 2 1
Case #2: IMPOSSIBLE
Case #3: 7
1 2 3 1 3 2 1
Case #4: IMPOSSIBLE
Case #5: 9
1 4 1 2 3 2 3 4 1
```
## 提示

**Sample Explanation**

In Sample Case #1, another acceptable parade route is one that goes from building 1 to building 2 and then back for a total of 2 steps.

![](https://cdn.luogu.com.cn/upload/image_hosting/udzlxptm.png)

In Sample Case #2, there are no slides leading to building 1, so no valid parade can exist.

![](https://cdn.luogu.com.cn/upload/image_hosting/pp27u0fj.png)

In Sample Case #3, the parade route the sample output exhibits goes through each building twice.

![](https://cdn.luogu.com.cn/upload/image_hosting/e7pjon34.png)

Sample Case #4 is pictured below.

![](https://cdn.luogu.com.cn/upload/image_hosting/ff4gi295.png)

Sample Case #5 is the one illustrated in the problem statement. In the parade route in the sample output, the slides from 2 to 3 and from 4 to 1 are used twice, but the rest of the slides are used only once each.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{U}_i \leq \mathbf{B}$, for all $i$.
- $1 \leq \mathbf{V}_i \leq \mathbf{B}$, for all $i$.
- $\mathbf{U}_i \neq \mathbf{V}_i$, for all $i$.
- $(\mathbf{U}_i, \mathbf{V}_i) \neq (\mathbf{U}_j, \mathbf{V}_j)$, for all $i \neq j$.

**Test Set 1 (11 Pts, Visible Verdict)**

- Time limit: 10 seconds.
- $2 \leq \mathbf{B} \leq 10$.
- $2 \leq \mathbf{S} \leq 10$.

**Test Set 2 (24 Pts, Hidden Verdict)**

- Time limit: 20 seconds.
- $2 \leq \mathbf{B} \leq 200$.
- $2 \leq \mathbf{S} \leq 5000$.



---

---
title: "[GCJ 2020 Qualification] Indicium"
layout: "post"
diff: 省选/NOI-
pid: P13052
tag: ['2020', '网络流', 'Special Judge', '二分图', 'Google Code Jam']
---
# [GCJ 2020 Qualification] Indicium
## 题目描述

Indicium means "trace" in Latin. In this problem we work with Latin squares and matrix traces.

A Latin square is an $\mathbf{N}$-by-$\mathbf{N}$ square matrix in which each cell contains one of $\mathbf{N}$ different values, such that no value is repeated within a row or a column. In this problem, we will deal only with "natural Latin squares" in which the $\mathbf{N}$ values are the integers between 1 and $\mathbf{N}$.

The trace of a square matrix is the sum of the values on the main diagonal (which runs from the upper left to the lower right).

Given values $\mathbf{N}$ and $\mathbf{K}$, produce any $\mathbf{N}$-by-$\mathbf{N}$ "natural Latin square" with trace $\mathbf{K}$, or say it is impossible. For example, here are two possible answers for $\mathbf{N}=3, \mathbf{K}=6$. In each case, the values that contribute to the trace are underlined.

$\begin{array}{llll}\underline{2} & 1 & 3 & \underline{3} \\3 & \underline{2} & 1 & 1 \\1 & 3 & \underline{2} & 2\end{array} \begin{array}{lll}1 & 2 \\ \underline{2} & 3 \\3 & \underline{1}\end{array}$

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each consists of one line containing two integers $\mathbf{N}$ and $\mathbf{K}$ : the desired size of the matrix and the desired trace.


## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is IMPOSSIBLE if there is no answer for the given parameters or POSSIBLE otherwise. In the latter case, output $\mathbf{N}$ more lines of $\mathbf{N}$ integers each, representing a valid "natural Latin square" with a trace of $\mathbf{K}$, as described above.
## 样例

### 样例输入 #1
```
2
3 6
2 3
```
### 样例输出 #1
```
Case #1: POSSIBLE
2 1 3
3 2 1
1 3 2
Case #2: IMPOSSIBLE
```
## 提示

**Sample Explanation**

Sample Case #1 is the one described in the problem statement.

Sample Case #2 has no answer. The only possible 2-by-2 "natural Latin squares" are as follows:

```
1 2 2 1
2 1 1 2
```

These have traces of 2 and 4, respectively. There is no way to get a trace of 3.

**Limits**

- $\mathrm{N} \leqslant \mathrm{K} \leqslant \mathrm{N}^{2}$.

**Test set 1 (7 Pts, Visible Verdict)**

- $\mathrm{T}=44$.
- $2 \leqslant \mathrm{N} \leqslant 5$.

**Test set 2 (25 Pts, Hidden Verdict)**

- $1 \leqslant \mathrm{T} \leqslant 100$.
- $2 \leqslant \mathrm{N} \leqslant 50$.


---

---
title: "[GCJ 2020 Finals] Replace All"
layout: "post"
diff: 省选/NOI-
pid: P13074
tag: ['2020', '网络流', '二分图', 'Google Code Jam']
---
# [GCJ 2020 Finals] Replace All
## 题目描述

Banana Rocks Inc is coming up with a revolutionary technology to perform the common edit operation "replace all". Their implementation replaces every occurrence of a character within a given text with another character. (If the character does not appear in the text, then the operation occurs but has no effect.)

For example, if the starting text is `CODEJAMWORLDFINALS` and an operation is performed to replace A with o, the new text would be `CODEJOMWORLDFINOLS`. If another operation is performed on that result to replace o with y, the final text would be `CYDEJYMWYRLDFINYLS`.

Unfortunately, the implementation is incomplete, so it can only perform replacements from a specific list of $\mathbf{N}$ pairs of characters. Also, even if a replacement of a specific character $c_1$ with another character $c_2$ is implemented, the reverse replacement of $c_2$ with $c_1$ may or may not be implemented.

You want to try all the implemented replacements. You are given some initial string $\mathbf{S}$ to use as the initial text. You can perform any number of replacements in sequential order: the first replacement is performed on $\mathbf{S}$, and the (i+1)-th replacement is performed on the result of performing the i-th replacement. The only requirement is that each implemented replacement is performed at least once during this process. There is no upper limit on how many times you may perform each replacement.

The allowed characters are decimal digits and uppercase and lowercase English alphabet letters. In this problem, uppercase and lowercase versions of the same letter are treated as distinct characters.

What is the maximum number of unique characters that can appear in a text that is the result of the last replacement performed?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of two lines. The first line contains a string $\mathbf{S}$ and an integer $\mathbf{N}$: the initial text and the number of implemented replacements. The second line contains $\mathbf{N}$ two-character strings $\mathbf{R}_1$, $\mathbf{R}_2$, ..., $\mathbf{R}_\mathbf{N}$, representing the implemented replacements. $\mathbf{A}_i$ and $\mathbf{B}_i$ are the first and second characters of $\mathbf{R}_i$, respectively. The i-th implemented replacement corresponds to replacing all occurrences of $\mathbf{A}_i$ with $\mathbf{B}_i$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where x is the test case number (starting from 1) and y is the maximum number of unique characters that can appear in a text that is the result of performing all implemented replacements to $\mathbf{S}$ one or more times each, in some order.
## 样例

### 样例输入 #1
```
4
CODEJAMWORLDFINALS 2
AO OY
xyz 3
xy zx yz
CJ 4
20 2O HC KS
AB 2
Ab bA
```
### 样例输出 #1
```
Case #1: 14
Case #2: 2
Case #3: 2
Case #4: 2
```
### 样例输入 #2
```
1
1234 5
12 2X X3 31 X2
```
### 样例输出 #2
```
Case #1: 4
```
## 提示

**Sample Explanation**

Sample Test Set 1 meets the limits for Test Set 1. Another sample case that does not meet those limits could appear in Test Set 2.

Sample Case #1 is the one in the statement. Notice that if we perform the replacements in the order mentioned in the statement, we get 13 different characters in the final text. If we perform them both once in the other order, however, we can get `CYDEJOMWYRLDFINOLS`, which has 14 different characters.

In Sample Case #2, one way to get 2 different characters in the final text is to perform the replacements in the order given from left to right, once each.

In Sample Case #3, none of the replacements affect the text at all, so it does not matter how we apply them. We will always be left with the original two letters. Notice that replacements can contain characters not appearing in the initial text, and the initial text can contain characters not appearing in the implemented replacements.

In Sample Case #4, remember that uppercase $\mathbf{B}$ is not the same character as lowercase $\mathbf{b}$.

In this additional sample case, one possibility is to perform the replacements in the following order: `X3 2X X2 2X 12 31`. This process goes through the following strings, starting with S: `1234 1234 1X34 1234 1X34 2X34 2X14`.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \text{length of } \mathbf{S} \leq 1000$, for all i.
- Each character of $\mathbf{S}$ is an uppercase or lowercase English alphabet letter or a decimal digit.
- $\mathbf{A}_i$ is an uppercase or lowercase English alphabet letter or a decimal digit, for all i.
- $\mathbf{B}_i$ is an uppercase or lowercase English alphabet letter or a decimal digit, for all i.
- $\mathbf{A}_i \neq \mathbf{B}_i$, for all i.
- $(\mathbf{A}_i, \mathbf{B}_i) \neq (\mathbf{A}_j, \mathbf{B}_j)$, for all $i \neq j$. (Each replacement is unique.)

**Test Set 1 (15 Pts, Visible Verdict)**

- $2 \leq \mathbf{N} \leq 62$.
- $\mathbf{B}_i \neq \mathbf{B}_j$, for all $i \neq j$.

**Test Set 2 (27 Pts, Hidden Verdict)**

- $2 \leq \mathbf{N} \leq 62 \times 61$.


---

---
title: "[GCJ 2018 Finals] Jurisdiction Restrictions"
layout: "post"
diff: 省选/NOI-
pid: P13153
tag: ['2018', '二分', '网络流', '最大流最小割定理', 'Google Code Jam']
---
# [GCJ 2018 Finals] Jurisdiction Restrictions
## 题目描述

The city of Gridtopia is a matrix of square cells ("blocks") with $R$ rows and $C$ columns; rows are numbered (starting from 1) from top to bottom, and columns are numbered (starting from 1) from left to right. The city is served by $S$ different police stations; the i-th station is in the block located in the $R_i$th row and the $C_i$th column, and no block contains more than one station.

Each station is only able to patrol blocks that are no more than $D_i$ blocks away from that station, either horizontally or vertically. That is, the i-th station can only patrol the block in row $R'$ and column $C'$ if $\max(|R' - R_i|, |C' - C_i|) \leq D_i$. Put another way, the i-th station can patrol only blocks within the square of side length $2D_i + 1$ centered on that station.

As the new police commissioner, you need to assign some blocks within the city to exactly one station that is able to patrol it. Blocks that contain stations and blocks that no station is able to patrol should not be assigned. All other blocks have to be assigned. Moreover, you must distribute this assignment load as evenly as possible among stations. Let $A_i$ denote the number of blocks assigned to the i-th station; then your goal is to minimize the difference between the maximum of all the $A_i$ values and the minimum of all of the $A_i$ values. If you make optimal assignments, what is the smallest possible difference?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each case begins with one line with three integers $R$, $C$, and $S$: respectively, the numbers of rows and columns in the grid of cells, and the number of stations. Then, there are $S$ more lines. The i-th of these has three integers $R_i$, $C_i$, and $D_i$: respectively, the row and column in which the i-th station is located, and the parameter that determines which blocks that station is able to patrol, as described above.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the difference described above.
## 样例

### 样例输入 #1
```
2
3 4 2
1 1 1
3 3 2
5 5 2
4 1 2
3 2 2
```
### 样例输出 #1
```
Case #1: 4
Case #2: 0
```
## 提示

In Sample Case #1, the city consists of a grid with 3 rows and 4 columns, with one station in the upper left block and one station in the block to the left of the lower right block. The first station can only patrol the three blocks that touch the edge or corner of its block; every other block is at a horizontal or vertical distance of more than 1 away. The second station can patrol any block in the grid (except for the blocks containing the stations). The difference in number of blocks assigned is minimized if you assign station 1 all three of the blocks it can patrol, and then assign the remaining seven blocks to station 2.

In Sample Case #2, one optimal strategy is to assign the blocks as follows. In this picture, $1$ represents station 1, $2$ represents station 2, $!$ represents a block assigned to station 1, $@$ represents a block assigned to station 2, and $.$ represents a block assigned to neither station (because neither station can patrol it). Notice that a station's assigned blocks do not need to form a single continuous area.

```
@@@@.
!!!@.
!2!@.
1!!@.
!@!@.
```

**Limits**

- $1 \leq T \leq 100.$
- $2 \leq S \leq 15.$
- $1 \leq R_i \leq R,$ for all $i.$
- $1 \leq C_i \leq C,$ for all $i.$
- For all $i \neq j,$ $R_i \neq R_j$ and/or $C_i \neq C_j.$ (No two stations are in the same block.)
- $1 \leq D_i < \max(R, C),$ for all $i.$

**Test set 1 (5 Pts, Visible)**

- $1 \leq R \leq 20.$
- $1 \leq C \leq 20.$

**Test set 2 (23 Pts, Hidden)**

- $1 \leq R \leq 10^9.$
- $1 \leq C \leq 10^9.$


---

---
title: "[GCJ 2015 #2] Bilingual"
layout: "post"
diff: 省选/NOI-
pid: P13226
tag: ['2015', '网络流', '最大流最小割定理', 'Google Code Jam']
---
# [GCJ 2015 #2] Bilingual
## 题目描述

Elliot's parents speak French and English to him at home. He has heard a lot of words, but it isn't always clear to him which word comes from which language! Elliot knows one sentence that he's sure is English and one sentence that he's sure is French, and some other sentences that could be either English or French. If a word appears in an English sentence, it must be a word in English. If a word appears in a French sentence, it must be a word in French.

Considering all the sentences that Elliot has heard, what is the minimum possible number of words that he's heard that must be words in both English and French?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each starts with a single line containing an integer $\mathbf{N}$. $\mathbf{N}$ lines follow, each of which contains a series of space-separated "words". Each "word" is made up only of lowercase characters a-z. The first of those $\mathbf{N}$ lines is a "sentence" in English, and the second is a "sentence" in French. The rest could be "sentences" in either English or French. (Note that the "words" and "sentences" are not guaranteed to be valid in any real language.)
## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the minimum number of words that Elliot has heard that must be words in both English and French.
## 样例

### 样例输入 #1
```
4
2
he loves to eat baguettes
il aime manger des baguettes
4
a b c d e
f g h i j
a b c i j
f g h d e
4
he drove into a cul de sac
elle a conduit sa voiture
il a conduit dans un cul de sac
il mange pendant que il conduit sa voiture
6
adieu joie de vivre je ne regrette rien
adieu joie de vivre je ne regrette rien
a b c d e
f g h i j
a b c i j
f g h d e
```
### 样例输出 #1
```
Case #1: 1
Case #2: 4
Case #3: 3
Case #4: 8
```
## 提示

**Sample Explanation**

In Case #1, Elliot knows for sure that the first sentence is in English and the second is in French, so there is no ambiguity; the only word that must be in both English and French is "baguettes".

In Case #2, the last two sentences could either be: English English, English French, French English, or French French. The second of those possibilities is the one that minimizes the number of words common to both languages; that set turns out to be d, e, i, and j.

**Limits**

- $1 \leq \mathbf{T} \leq 25$.
- Each word will contain no more than 10 characters.
- The two "known" sentences will contain no more than 1000 words each.
- The "unknown" sentences will contain no more than 10 words each.

**Small dataset**

- Time limit: ~~240~~ 5 seconds.
- $2 \leq \mathbf{N} \leq 20$.

**Large dataset**

- Time limit: ~~480~~ 10 seconds.
- $2 \leq \mathbf{N} \leq 200$.


---

---
title: "[GCJ 2009 Finals] Wi-fi Towers"
layout: "post"
diff: 省选/NOI-
pid: P13451
tag: ['2009', '网络流', '最小割', 'Google Code Jam']
---
# [GCJ 2009 Finals] Wi-fi Towers
## 题目描述

You are given a network of wireless towers. Each tower has a range and can send data to neighboring towers as long as the distance is less than or equal to the sending tower's range.

The towers are using an old communication protocol $A$, but there is a new, better protocol $B$ available. We are thinking about upgrading some towers to send data using protocol $B$ to achieve better bandwidth.

There is one important restriction: if a tower $T$ is using the new protocol $B$, every tower within $T$'s range must also be running protocol $B$, so that they can understand the data sent from $T$. The reverse is not necessary — towers running the new protocol $B$ can be sent data from towers using the old protocol $A$.

Your task is to select the best set of towers to upgrade from protocol $A$ to protocol $B$. There is some benefit to upgrading a tower, but there are also installation costs. So each tower will have a score, which can be positive or negative, which is the value of upgrading the tower. Choose the set of towers to upgrade in such a way that the total score of the upgraded towers is maximized.
## 输入格式

The first line contains the number of test cases, $T$. Each test case starts with the number of towers, $n$. The following $n$ lines each contain 4 integers: $x$, $y$, $r$, $s$. They describe a tower at coordinates $x$, $y$ having a range of $r$ and a score (value of updating to the new protocol) of $s$.

## 输出格式

For each test case, output:

Case #$X$: score

where $X$ is the test case number, starting from 1, and score is the total score for the best choice of towers.
## 样例

### 样例输入 #1
```
1
5
0 1 7 10
0 -1 7 10
5 0 1 -15
10 0 6 10
15 1 2 -20
```
### 样例输出 #1
```
Case #1: 5
```
## 提示

**Limits**

- $1 \leq T \leq 55$
- $-10000 \leq x, y \leq 10000$
- $1 \leq r \leq 20000$
- $-1000 \leq s \leq 1000$
- No two towers will have the same coordinates.

**Small dataset(3 Pts)**

- $1 \leq n \leq 15$

**Large dataset(25 Pts)**

- $1 \leq n \leq 500$



---

---
title: "[GCJ 2008 Finals] The Year of Code Jam"
layout: "post"
diff: 省选/NOI-
pid: P13490
tag: ['2008', '网络流', 'Google Code Jam']
---
# [GCJ 2008 Finals] The Year of Code Jam
## 题目描述

The year 2008 will be known as a year of change and transition, the start of a new era: we're talking, of course, about the new Google Code Jam format. The introduction of this contest has jammed so many great programming competitions together in a single year that people have started calling it *The Year of Code Jam*.

Sphinny, a passionate contestant, is looking at her calendar of the year and discovering that a great number of programming contests has been scheduled. She has marked every day of the year on the calendar in one of the three ways:

* White: She will not participate in a contest on this day. Either no contests are scheduled, or she has more important things to do (surely there are other good things in life!).
* Blue: She will definitely participate in a contest on this day.
* Question mark: There is a contest scheduled, but she has not decided yet whether she will participate.

Note: To simplify the problem, we'll assume that there is no concept of qualification: you don't have to participate in one contest to be eligible for another.

Being in a world that is somewhat different from ours, Sphinny's calendar has some features we must mention: It has $N$ months, and each month has exactly $M$ days.

The picture below depicts a calendar with 5 months, 8 days in each month, 15 blue days, and 5 question marks.

![](https://cdn.luogu.com.cn/upload/image_hosting/ln25sw62.png)

Looking at her beautiful calendar, Sphinny has decided that each day has up to 4 neighbors in the year: The previous day in the same month, the next day in the same month, the same day in the previous month, and the same day in the next month.

Sphinny wants to maximize her happiness from these contests, and she estimates the effect of the contests on her happiness as a summation of values for all the blue days. For each blue day, the value is computed as follows:

* The initial value is 4.
* For each blue neighbour the day has, decrease the value by 1.

You may think that Sphinny likes the contests, but participating on two consecutive days makes her a little tired. And for aesthetic reasons, participating on the same day in two consecutive months is also not so great.

Sphinny wants to plan her year now, and decide for every day with a question mark whether it should be white or blue. Her goal is simply to maximize the happiness value.

The following picture shows a solution for the example above. By changing two question marks to blue days, and the other three to white days, she can achieve a happiness value of 42.

![](https://cdn.luogu.com.cn/upload/image_hosting/d6qxnu8l.png)
## 输入格式

The first line in the input file contains the number of cases $T$. This is followed by $T$ cases in the following format.

The first line is of the form "$N$ $M$", where $N$ and $M$ are two numbers giving the number of months and the number of days per month.

The next $N$ lines each contain a string of length $M$. The $j$-th character in the $i$-th string is one of {'#', '.', '?'}, which gives the status of the $j$-th day in the $i$-th month. '#' indicates a blue day, '.' indicates a white day, and '?' indicates a day with a question mark.
## 输出格式

For each input case, you should output a line in the format:

Case #X: Y

where $X$ is the 1-based case number, and $Y$ is the maximum happiness value.
## 样例

### 样例输入 #1
```
2
3 3
.?.
.?.
.#.
5 8
.#...##.
.##..?..
.###.#.#
??#..?..
###?#...
```
### 样例输出 #1
```
Case #1: 8
Case #2: 42
```
## 提示

**Sample Explanation**

Note that the second sample is our example in the pictures above.

**Limits**

- $1 \leqslant T \leqslant 100.$

**Small dataset (7 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leqslant M, N \leqslant 15.$

**Large dataset (23 Pts, Test set 2 - Hidden)**

- Time limit: ~~120~~ 12 seconds.
- $1 \leqslant M, N \leqslant 50.$



---

---
title: "小M的作物"
layout: "post"
diff: 省选/NOI-
pid: P1361
tag: ['图论', '网络流', '最小割']
---
# 小M的作物
## 题目描述

小 M 在 MC 里开辟了两块巨大的耕地 $A$ 和 $B$（你可以认为容量是无穷），现在，小 P 有 $n$ 种作物的种子，每种作物的种子有 $1$ 个（就是可以种一棵作物），编号为 $1$ 到 $n$。

现在，第 $i$ 种作物种植在 $A$ 中种植可以获得 $a_i$ 的收益，在 $B$ 中种植可以获得 $b_i$ 的收益，而且，现在还有这么一种神奇的现象，就是某些作物共同种在一块耕地中可以获得额外的收益，小 M 找到了规则中共有 $m$ 种作物组合，第 $i$ 个组合中的作物共同种在 $A$ 中可以获得 $c_{1,i}$ 的额外收益，共同种在 $B$ 中可以获得 $c_{2,i}$ 的额外收益。

小 M 很快的算出了种植的最大收益，但是他想要考考你，你能回答他这个问题么？
## 输入格式

第一行一个整数 $n$，表示作物种数。

第二行 $n$ 个整数，表示 $a_i$。

第三行 $n$ 个整数，表示 $b_i$。

第四行一个整数 $m$，表示组合种数。

接下来 $m$ 行中，第 $i$ 行第一个整数 $k_i$，表示第 $i$ 个作物组合中的作物种数，接下来两个整数 $c_{1,i},c_{2,i}$，然后 $k_i$ 个整数，表示该组合中的作物编号。
## 输出格式

只有一行，包括一个整数，表示最大收益。
## 样例

### 样例输入 #1
```
3
4 2 1
2 3 2
1
2 3 2 1 2
```
### 样例输出 #1
```
11
```
## 提示

### 样例解释

 $A$ 耕地种作物 $1,2$，$B$ 耕地种作物 $3$，收益： $4+2+3+2=11$。

### 数据范围

对于 $100\%$ 的数据，$1 \le k < n \le 10^3$，$1 \le m \le 10^3$。题目当中出现的所有权值均为不大于 $1000$ 的非负整数。


---

---
title: "酒店之王"
layout: "post"
diff: 省选/NOI-
pid: P1402
tag: ['福建省历届夏令营', '网络流', '二分图']
---
# 酒店之王
## 题目描述

XX 酒店的老板想成为酒店之王，本着这种希望，第一步要将酒店变得人性化。由于很多来住店的旅客有自己喜好的房间色调、阳光等，也有自己所爱的菜，但是该酒店只有 $p$ 间房间，一天只有固定的 $q$ 道不同的菜，每个房间只能住一位客人，每道菜也只能给一位客人食用。

有一天来了 $n$ 个客人，每个客人说出了自己喜欢哪些房间，喜欢哪道菜。但是很不幸，可能做不到让所有顾客满意（满意的条件是住进喜欢的房间且吃到喜欢的菜）。

要怎么分配，能使最多顾客满意呢？
## 输入格式

第一行给出三个整数，分别表示表示 $n,p,q$。

之后 $n$ 行，每行 $p$ 个整数，只可能是 $0$ 或 $1$，第 $i$ 行第 $j$ 个数表示第 $i$ 个人喜不喜欢第 $j$ 个房间（$1$ 表示喜欢， $0$ 表示不喜欢）。

之后 $n$ 行，每行 $q$ 个整数，只可能是 $0$ 或 $1$，第 $i$ 行第 $j$ 个数表示第 $i$ 个人喜不喜欢第 $j$ 道菜（$1$ 表示喜欢， $0$ 表示不喜欢）。
## 输出格式

最大的顾客满意数。


## 样例

### 样例输入 #1
```
2 2 2
1 0
1 0
1 1
1 1

```
### 样例输出 #1
```
1
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n,p,q \leq 100$。


---

---
title: "[USACO05FEB] Secret Milking Machine G"
layout: "post"
diff: 省选/NOI-
pid: P1674
tag: ['2005', '二分', 'USACO', '网络流']
---
# [USACO05FEB] Secret Milking Machine G
## 题目描述

约翰正在制造一台新型的挤奶机，但他不希望别人知道。他希望尽可能久地隐藏这个秘密。他把挤奶机藏在他的农场里，使它不被发现。在挤奶机制造的过程中，他需要去挤奶机所在的地方 $T$ 次。他的农场里有秘密的地道，但约翰只在返回的时候用它。农场被划分成 $N$ 块区域，用 $1$ 到 $200$ 标号。这些区域被 $P$ 条道路连接，每条路有一个小于 $10^6$ 的长度 $L$。两块区域之间可能有多条道路连接。为了减少被发现的可能，约翰不会两次经过农场上的任何一条道路。当然了，他希望走最短的路。请帮助约翰寻找这 $T$ 次从仓库走到挤奶机所在地的路线。仓库是区域 $1$，挤奶机所在地是区域 $N$。我们现在要求的是约翰经过的这些道路中最长的路的长度最小是多少，当然他不能重复走某一条路。请注意，我们要求的不是最短的总路程长度，而是所经过的直接连接两个区域的道路中最长的道路的最小长度。数据保证约翰可以找到 $T$ 条没有重复的从仓库到挤奶机所在区域的路。
## 输入格式

第 $1$ 行是 $3$ 个整数 $N$、$P$ 和 $T$，用空格隔开。

第 $2$ 到 $P+1$ 行，每行包括 $3$ 个整数，$A_i$，$B_i$，$L_i$。表示区域 $A_i$、$B_i$ 之间有一条长度为 $L_i$ 的道路。
## 输出格式

输出只有一行，包含一个整数，即约翰经过的这些道路中最长的路的最小长度。
## 样例

### 样例输入 #1
```
7 9 2
1 2 2
2 3 5
3 7 5
1 4 1
4 3 1
4 5 7
5 7 1
1 6 3
6 7 3
```
### 样例输出 #1
```
5
```
## 提示

选择 $1-2-3-7$ 和 $1-6-7$ 两条路线．这些路线中最长路的最小长度是 $5$。

对于 $100\%$ 的数据满足：$2\le N\le 200$，$1\le P\le 4\times 10^4$，$1\le T\le 200$，每条路的长度 $\le 10^6$。


---

---
title: "方格取数加强版"
layout: "post"
diff: 省选/NOI-
pid: P2045
tag: ['网络流']
---
# 方格取数加强版
## 题目描述

给出一个 $n\times n$ 的矩阵,每一格有一个非负整数 $A_{i,j}$（$A_{i,j} \le 10^3$），现在从 $(1,1)$ 出发，可以往右或者往下走，最后到达 $(n,n)$，每达到一格，把该格子的数取出来，该格子的数就变成 $0$，这样一共走 $K$ 次，现在要求 $K$ 次所达到的方格的数的和最大。
## 输入格式

第一行两个数 $n,K$（$1 \le n \le 50$，$0 \le K \le 10$）。

接下来 $n$ 行，每行 $n$ 个数，分别表示矩阵的每个格子的数。
## 输出格式

一个数，为最大和。

## 样例

### 样例输入 #1
```
3 1
1 2 3
0 2 1
1 4 2
```
### 样例输出 #1
```
11
```
## 提示

每个格子中的数不超过 $1000$。


---

---
title: "[NOI2012] 美食节"
layout: "post"
diff: 省选/NOI-
pid: P2050
tag: ['2012', 'NOI', '网络流', '费用流']
---
# [NOI2012] 美食节
## 题目描述

CZ 市为了欢迎全国各地的同学，特地举办了一场盛大的美食节。

作为一个喜欢尝鲜的美食客，小 M 自然不愿意错过这场盛宴。他很快就尝遍了美食节所有的美食。然而，尝鲜的欲望是难以满足的。尽管所有的菜品都很可口，厨师做菜的速度也很快，小 M 仍然觉得自己桌上没有已经摆在别人餐桌上的美食是一件无法忍受的事情。于是小 M 开始研究起了做菜顺序的问题，即安排一个做菜的顺序使得同学们的等待时间最短。

小 M 发现，美食节共有 $n$ 种不同的菜品。每次点餐，每个同学可以选择其中的**一个菜品**。总共有 $m$ 个厨师来制作这些菜品。当所有的同学点餐结束后，菜品的制作任务就会分配给每个厨师。然后每个厨师就会同时开始做菜。**厨师们会按照要求的顺序进行制作，并且每次只能制作一人份**。

此外，小 M 还发现了另一件有意思的事情——虽然这 $m$ 个厨师都会制作全部的 $n$ 种菜品，但**对于同一菜品，不同厨师的制作时间未必相同**。他将菜品用 $1, 2, \ldots, n$ 依次编号，厨师用 $1, 2, \ldots, m$ 依次编号，将第 $j$ 个厨师制作第 $i$ 种菜品的时间记为 $t_{i,j}$。

小 M 认为：每个同学的等待时间为**所有厨师开始做菜起，到自己那份菜品完成为止**的时间总长度。换句话说，如果一个同学点的菜是某个厨师做的第 $k$ 道菜，则他的等待时间就是这个厨师制作前 $k$ 道菜的时间之和。而**总等待时间**为**所有同学的等待时间之和**。

现在，小 M 找到了所有同学的点菜信息——有 $p_i$ 个同学点了第 $i$ 种菜品（$i=1, 2, \ldots, n$）。他想知道的是最小的总等待时间是多少。

## 输入格式

输入文件的第 $1$ 行包含两个正整数 $n$ 和 $m$，表示菜品的种数和厨师的数量。

第 $2$ 行包含 $n$ 个正整数，其中第 $i$ 个数为 $p_i$，表示点第 $i$ 种菜品的人数。

接下来有 $n$ 行，每行包含 $m$ 个非负整数，这 $n$ 行中的第 $i$ 行的第 $j$ 个数为 $t_{i,j}$，表示第 $j$ 个厨师制作第 $i$ 种菜品所需的时间。

输入文件中每行相邻的两个数之间均由一个空格隔开，行末均没有多余空格。

## 输出格式

输出仅一行包含一个整数，为总等待时间的最小值。

## 样例

### 样例输入 #1
```
3 2 
3 1 1 
5 7 
3 6 
8 9
```
### 样例输出 #1
```
47
```
## 提示

厨师 $1$ 先制作 $1$ 份菜品 $2$，再制作 $2$ 份菜品 $1$。点这 $3$ 道菜的 $3$ 个同学的等待时间分别为 $3$，$3+5=8$，$3+5+5=13$。

厨师 $2$ 先制作 $1$ 份菜品 $1$，再制作 $1$ 份菜品 $3$。点这 $2$ 道菜的 $2$ 个同学的等待时间分别为 $7$，$7+9=16$。

总等待时间为 $3+8+13+7+16=47$。

虽然菜品 $1$ 和菜品 $3$ 由厨师 $1$ 制作更快，如果这些菜品都由厨师 $1$ 制作，总等待时间反而更长。如果按上述的做法，将 $1$ 份菜品 $1$ 和 $1$ 份菜品 $3$ 调整到厨师 $2$ 制作，这样厨师 $2$ 不会闲着，总等待时间更短。

可以证明，没有更优的点餐方案。

每组数据的 $n,m$ 和 $p$ 值如下：  

|测试点编号| $n$| $m$| $p$|   
|:------:|:----:|:----:|:----:|    
|$1$|$n = 5$| $m = 5$| $p = 10$|   
|$2$| $n = 40$| $m = 1$ |$p = 400$ |  
|$3$| $n = 40$| $m = 2$ |$p = 300$ |
|$4$| $n = 40$| $m = 40$| $p = 40$ |
|$5$| $n = 5$| $m = 40$| $p = 100$ |
|$6$| $n = 10$| $m = 50$| $p = 200$ |
|$7$| $n = 20$| $m = 60$| $p = 400$ |
|$8$| $n = 40$| $m = 80$| $p = 600$ |
|$9$| $n = 40$| $m = 100$| $p = 800$ |
|$10$| $n = 40$| $m = 100$| $p = 800$ |


对于 $100\%$ 的数据，$n \leq 40$，$m\leq 100$，$p\leq 800$，$t_{i,j}\leq 1000$（其中 $p = \sum p_i$）。



---

---
title: "[SCOI2007] 修车"
layout: "post"
diff: 省选/NOI-
pid: P2053
tag: ['2007', '四川', '各省省选', '网络流', '费用流']
---
# [SCOI2007] 修车
## 题目描述

同一时刻有 $N$ 位车主带着他们的爱车来到了汽车维修中心。

维修中心共有 $M$ 位技术人员，不同的技术人员对不同的车进行维修所用的时间是不同的。

现在需要安排这 $M$ 位技术人员所维修的车及顺序，使得顾客平均等待的时间最小。

说明：顾客的等待时间是指从他把车送至维修中心到维修完毕所用的时间。
## 输入格式

第一行有两个数 $M,N$，表示技术人员数与顾客数。

接下来 $N$ 行，每行 $M$ 个整数。第 $i+1$ 行第 $j$ 个数表示第 $j$ 位技术人员维修第 $i$ 辆车需要用的时间 $T_{i,j}$。
## 输出格式

最小平均等待时间，答案精确到小数点后 $2$ 位。
## 样例

### 样例输入 #1
```
2 2
3 2
1 4
```
### 样例输出 #1
```
1.50
```
## 提示

对于 $100\%$ 的数据，$2\le M\le 9$，$1\le N\le 60$，$1\le T\le 10^3$。


---

---
title: "[国家集训队] 部落战争"
layout: "post"
diff: 省选/NOI-
pid: P2172
tag: ['集训队互测', '网络流']
---
# [国家集训队] 部落战争
## 题目背景

lanzerb 的部落在 A 国的上部，他们不满天寒地冻的环境，于是准备向A国的下部征战来获得更大的领土。
## 题目描述

A 国是一个 $M\times N$ 的矩阵，其中某些地方是城镇，某些地方是高山深涧无人居住。lanzerb 把自己的部落分成若干支军队，他们约定：

每支军队可以从任意一个城镇出发，并只能从上往向下征战，不能回头。途中只能经过城镇，不能经过高山深涧。

如果某个城镇被某支军队到过，则其他军队不能再去那个城镇了。
每支军队都可以在任意一个城镇停止征战。

所有军队都很奇怪，他们走的方法有点像国际象棋中的马。不过马每次只能走 $1\times2$ 的路线，而他们只能走 $R\times C$ 的路线。

lanzerb 的野心使得他的目标是统一全国，但是兵力的限制使得他们在配备人手时力不从心。假设他们每支军队都能顺利占领这支军队经过的所有城镇，请你帮 lanzerb 算算至少要多少支军队才能完成统一全国的大业。
## 输入格式

第一行包含 $4$ 个整数 $M,N,R,C$，意义见问题描述。接下来 $M$ 行每行一个长度为 $N$ 的字符串。如果某个字符是 `.` 表示这个地方是城镇；如果这个字符是 `x` 则表示这个地方是高山深涧。
## 输出格式

输出一个整数，表示最少的军队个数。
## 样例

### 样例输入 #1
```
3 3 1 2
...
.x.
...
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5 4 1 1
....
..x.
...x
....
x...
```
### 样例输出 #2
```
5

```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1\le M,N\le 50,1\le R,C\le 10$。


---

---
title: "奶牛隐藏"
layout: "post"
diff: 省选/NOI-
pid: P2402
tag: ['福建省历届夏令营', '网络流']
---
# 奶牛隐藏
## 题目背景

这本是一个非常简单的问题，然而奶牛们由于下雨已经非常混乱，无法完成这一计算，于是这个任务就交给了你。(奶牛混乱的原因看题目描述)

## 题目描述

在一个农场里有 $n$ 块田地。某天下午，有一群牛在田地里吃草，他们分散在农场的诸多田地上，农场由 $m$ 条无向的路连接，每条路有不同的长度。

突然，天降大雨，奶牛们非常混乱，想要快点去躲雨。已知每个田地都建立有一个牛棚，但是每个牛棚只能容纳一定数量的牛躲雨，如果超过这个数量，那多出的牛只能去别的田地躲雨。奶牛们每移动 $1$ 的距离花费 $1$ 时间，奶牛们想知道它们全部都躲进牛棚，最少需要多少时间。(即最后一头奶牛最少要花多久才能躲进牛棚)。

## 输入格式

第一行有两个整数，分别代表田地数 $n$ 和道路数 $m$。

接下来 $n$ 行，每行两个整数，第 $(i + 1)$ 行的整数 $s_i, p_i$ 分别表示第 $i$ 块田地的牛的数量以及该田地的牛棚最多可以容纳多少牛。

接下来 $m$ 行，每行三个整数 $u, v, w$，代表存在一条长度为 $w$ 的连接 $u$ 和 $v$ 的道路。

## 输出格式

输出一行一个整数表示所有奶牛全都躲进牛棚所用的最少时间。如果无法使全部奶牛都躲进牛棚，输出 $-1$。

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

#### 样例输入输出 1 解释

$1$ 号点的两只牛直接躲进 $1$ 号牛棚，剩下的 $5$ 只中，$4$ 只跑去 $2$ 号点，还有一只沿 $1 \to 2 \to 3$ 躲进 $3$ 号点, $3$ 号点的 $2$ 只牛也直接躲进去，这样最慢的牛花费的时间是 $110$。

#### 数据规模与约定

对于 $100\%$ 的数据，保证：
- $1 \leq n \leq 200$，$1 \leq m \leq 1500$。
- $1 \leq u, v \leq n$，$1 \leq w \leq 10^{15}$，$1 \leq s_i, p_i \leq 10^{16}$。



---

---
title: "[SDOI2010] 星际竞速"
layout: "post"
diff: 省选/NOI-
pid: P2469
tag: ['2010', '各省省选', '网络流', '山东', '费用流']
---
# [SDOI2010] 星际竞速
## 题目描述

10 年一度的银河系赛车大赛又要开始了。作为全银河最盛大的活动之一，夺得这个项目的冠军无疑是很多人的梦想，来自杰森座 $\alpha$ 星的悠悠也是其中之一。

赛车大赛的赛场由 $N$ 颗行星和 $M$ 条双向星际航路构成，其中每颗行星都有一个不同的引力值。大赛要求车手们从一颗与这 $N$ 颗行星之间没有任何航路的天体出发，访问这 $N$ 颗行星每颗恰好一次，首先完成这一目标的人获得胜利。

由于赛制非常开放，很多人驾驶着千奇百怪的自制赛车来参赛。这次悠悠驾驶的赛车名为超能电驴，这是一部凝聚了全银河最尖端科技结晶的梦幻赛车。作为最高科技的产物，超能电驴有两种移动模式：高速航行模式和能力爆发模式。在高速航行模式下，超能电驴会展开反物质引擎，以数倍于光速的速度沿星际航路高速航行。在能力爆发模式下，超能电驴脱离时空的束缚，使用超能力进行空间跳跃——在经过一段时间的定位之后，它能瞬间移动到任意一个行星。

天不遂人愿，在比赛的前一天，超能电驴在一场离子风暴中不幸受损，机能出现了一些障碍：在使用高速航行模式的时候，只能由每个星球飞往引力比它大的星球，否则赛车就会发生爆炸。

尽管心爱的赛车出了问题，但是悠悠仍然坚信自己可以取得胜利。他找到了全银河最聪明的贤者——你，请你为他安排一条比赛的方案，使得他能够用最少的时间完成比赛。

## 输入格式

输入文件 starrace.in 的第一行是两个正整数 $N, M$。

第二行 $N$ 个数 $A_1,\cdots,A_N$，其中 $A_i$ 表示使用能力爆发模式到达行星 $i$ 所需的定位时间。

接下来 $M$ 行，每行 $3$ 个正整数 $u_i, v_i, w_i$，表示在编号为 $u_i$ 和 $v_i$ 的行星之间存在一条需要航行 $w_i$ 时间的星际航路。

输入数据已经按引力值排序，也就是编号小的行星引力值一定小，且不会有两颗行星引力值相同。

## 输出格式

输出文件 starrace.out 仅包含一个正整数，表示完成比赛所需的最少时间。

## 样例

### 样例输入 #1
```
3 3

1 100 100

2 1 10

1 3 1

2 3 1
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
3 3

1 2 3

1 2 100

1 3 100

2 3 100
```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
4 5

100 1000 10 100

1 2 100

2 3 100

4 3 100

1 3 20

2 4 20
```
### 样例输出 #3
```
230
```
## 提示

样例一说明：先使用能力爆发模式到行星 $1$，花费时间 $1$。

然后切换到高速航行模式，航行到行星 $2$，花费时间 $10$。

之后继续航行到行星 $3$ 完成比赛，花费时间 $1$。

虽然看起来从行星 $1$ 到行星 $3$ 再到行星 $2$ 更优，但我们却不能那样做，因为那会导致超能电驴爆炸。

【数据规模和约定】

对于 $30\%$ 的数据 $N\leq 20$，$M\leq 50$；

对于 $70\%$ 的数据 $N\leq 200$，$M\leq 4\times 10^3$；

对于 $100\%$ 的数据 $N\leq 800$，$M\leq 1.5\times 10^4$。

输入数据中的任何数都不会超过 $10^6$。

输入数据保证任意两颗行星之间至多存在一条航道，且不会存在某颗行星到自己的航道。



---

---
title: "[SCOI2007] 蜥蜴"
layout: "post"
diff: 省选/NOI-
pid: P2472
tag: ['模拟', '2007', '四川', '各省省选', '网络流']
---
# [SCOI2007] 蜥蜴
## 题目描述

在一个 $r$ 行 $c$ 列的网格地图中有一些高度不同的石柱，第 $i$ 行 $j$ 列的石柱高度为 $h_{i,j}$。

一些石柱上站着一些蜥蜴，你的任务是让尽量多的蜥蜴逃到边界外。

每行每列中相邻石柱的距离为 $1$，蜥蜴的跳跃距离是 $d$，即蜥蜴可以跳到**平面距离**不超过 $d$ 的任何一个石柱上。

石柱都不稳定，每次当蜥蜴跳跃时，所离开的石柱高度减 $1$（如果仍然落在地图内部，则到达的石柱高度不变）。

如果该石柱原来高度为 $1$，则蜥蜴离开后消失，以后其他蜥蜴不能落脚。

任何时刻不能有两只蜥蜴在同一个石柱上。
## 输入格式


#### 输入格式
输入第一行为三个整数 $r,c,d$，即地图的规模与最大跳跃距离。

接下来 $r$ 行每行 $c$ 个数字为石柱的初始状态，$0$ 表示没有石柱，否则表示石柱的初始高度 $h_{i,j}$。

接下来 $r$ 行每行 $c$ 个字符为蜥蜴位置，`L` 表示蜥蜴，`.` 表示没有蜥蜴。
## 输出格式

输出仅一行，包含一个整数，即无法逃离的蜥蜴总数的最小值。
## 样例

### 样例输入 #1
```
5 8 2
00000000
02000000
00321100
02000000
00000000
........
........
..LLLL..
........
........

```
### 样例输出 #1
```
1
```
## 提示

对于 $100\%$ 的数据满足：$1\le r,c\le20$，$1\le d\le 4$，$1\le h\le 3$。


---

---
title: "[ZJOI2010] 贪吃的老鼠"
layout: "post"
diff: 省选/NOI-
pid: P2570
tag: ['2010', '二分', '网络流', '浙江', 'Special Judge']
---
# [ZJOI2010] 贪吃的老鼠
## 题目描述

奶酪店里最近出现了 $m$ 只老鼠！它们的目标就是把生产出来的所有奶酪都吃掉。奶酪店中一天会生产 $n$ 块奶酪，其中第 $i$ 块的大小为 $p_i$，会在第 $r_i$ 秒被生产出来，并且必须在第 $d_i$ 秒之前将它吃掉。第 $j$ 只老鼠吃奶酪的速度为 $s_j$，因此如果它单独吃完第 $i$ 块奶酪所需的时间为 $p_i/s_j$。老鼠们吃奶酪的习惯很独特，具体来说：

1. 在任一时刻，一只老鼠最多可以吃一块奶酪；
2. 在任一时刻，一块奶酪最多被一只老鼠吃。

由于奶酪的保质期常常很短，为了将它们全部吃掉，老鼠们需要使用一种神奇的魔法来延长奶酪的保质期。将奶酪的保质期延长 $T$ 秒是指所有的奶酪的 $d_i$ 变成 $d_i+T$。同时，使用魔法的代价很高，因此老鼠们希望找到最小的 $T$ 使得可以吃掉所有的奶酪。
## 输入格式

输入文件的第一行包含一个整数 $K$，表示输入文件中数据的组数。

每组数据的第一行包含两个整数 $n$ 和 $m$，分别表示奶酪和老鼠的数量。接下来的 $n$ 行每行包含三个整数 $p_i,r_i,d_i$。最后 $m$ 行每行包含一个整数，表示 $s_j$。$p_i,r_i,d_i,s_j$ 的含义如上文所述。
## 输出格式

包含 $K$ 行，每行包含一个实数，表示你找到的最小的 $T$。你的答案和标准答案的绝对误差不应超过 $10^{-4}$。
## 样例

### 样例输入 #1
```
2
2 2
13 0 4
10 1 3
4
2
1 1
1 0 2
1

```
### 样例输出 #1
```
0.5
0

```
## 提示

### 样例说明

第一组数据中：

第 $0$ 到第 $1$ 秒：

第一只老鼠吃第一块奶酪；

第 $1$ 到第 $3.5$ 秒：

- 第一只老鼠吃第二块奶酪；
- 第二只老鼠吃第一块奶酪；

第 $3.5$ 到第 $4.5$ 秒：第一只老鼠吃第一块奶酪。

### 数据规模

$30\%$ 的数据中，$1 \le n,m \le 5$；

$100\%$ 的数据中，$1 \le K \le 5$，$1 \le n,m \le 30$，$1 \le p_i \le 10^5$，$0 \le r_i<d_i \le 10^7$，$1 \le s_j \le 10^5$。


---

---
title: "[ZJOI2010] 网络扩容"
layout: "post"
diff: 省选/NOI-
pid: P2604
tag: ['2010', '各省省选', '网络流', '浙江', '图论建模', '费用流']
---
# [ZJOI2010] 网络扩容
## 题目描述

给定一张有向图，每条边都有一个容量 $c$ 和一个扩容费用 $w$。这里扩容费用是指将容量扩大 $1$ 所需的费用。求： 

1. 在不扩容的情况下，$1$ 到 $n$ 的最大流；

2. 将 $1$ 到 $n$ 的最大流增加 $k$ 所需的最小扩容费用。
## 输入格式

第一行包含三个整数 $n,m,k$，表示有向图的点数、边数以及所需要增加的流量。

接下来的 $M$ 行每行包含四个整数 $u,v,c,w$，表示一条从$u$ 到 $v$，容量为 $c$，扩容费用为 $w$ 的边。
## 输出格式

输出文件一行包含两个整数，分别表示问题 $1$ 和问题 $2$ 的答案。
## 样例

### 样例输入 #1
```
5 8 2
1 2 5 8
2 5 9 9
5 1 6 2
5 1 1 8
1 2 8 7
2 5 4 9
1 2 1 1
1 4 2 1
```
### 样例输出 #1
```
13 19

```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n\le 100$。
- 对于 $100\%$ 的数据，保证 $1\le n\le 10^3$，$1\le m\le 5\times 10^3$，$1\le k\le 10$，$1 \leq u, v \leq n$，$1\le c,w\le 100$。


---

---
title: "[CTSC1999] 家园 / 星际转移问题"
layout: "post"
diff: 省选/NOI-
pid: P2754
tag: ['1999', '网络流', 'O2优化', '网络流与线性规划 24 题', 'CTSC/CTS']
---
# [CTSC1999] 家园 / 星际转移问题
## 题目描述

由于人类对自然资源的消耗，人们意识到大约在 2300 年之后，地球就不能再居住了。于是在月球上建立了新的绿地，以便在需要时移民。令人意想不到的是，2177 年冬由于未知的原因，地球环境发生了连锁崩溃，人类必须在最短的时间内迁往月球。

现有 $n$ 个太空站位于地球与月球之间，且有 $m$ 艘公共交通太空船在其间来回穿梭。每个太空站可容纳无限多的人，而太空船的容量是有限的，第 $i$ 艘太空船只可容纳  $h_i$ 个人。每艘太空船将周期性地停靠一系列的太空站，例如 $(1,3,4)$ 表示该太空船将周期性地停靠太空站 $134134134\dots$。每一艘太空船从一个太空站驶往任一太空站耗时均为 $1$。人们只能在太空船停靠太空站(或月球、地球)时上、下船。

初始时所有人全在地球上，太空船全在初始站。试设计一个算法，找出让所有人尽快地全部转移到月球上的运输方案。
## 输入格式

输入的第一行是三个用空格隔开的整数，分别代表太空站个数 $n$，太空船个数 $m$ 和地球上的人数 $k$。

第 $2$ 到第 $(m + 1)$ 行，每行给出一艘太空船的信息，第 $(i + 1)$ 行的第一个整数 $h_i$ 代表第 $i$ 艘太空船可容纳的人数。随后有一个整数 $r_i$，代表第 $i$ 艘太空船停靠的站点数。之后有 $r_i$ 个整数，依次代表该太空船停靠站点的编号 $S_{i, j}$，其中太空站自 $1$ 至 $n$ 编号，地球编号为 $0$，月球编号为 $-1$。
## 输出格式

输出一行一个整数，代表将所有人转移到月球上的最短用时。若无解则输出 $0$。
## 样例

### 样例输入 #1
```
2 2 1
1 3 0 1 2
1 3 1 2 -1

```
### 样例输出 #1
```
5
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证：

- $1 \leq n \leq 13$。
- $1 \leq m \leq 20$。
- $1 \leq k \leq 50$。
- $1 \leq r_i \leq n + 2$。
- $-1 \leq S_{i, j}\leq n$。


---

---
title: "太空飞行计划问题"
layout: "post"
diff: 省选/NOI-
pid: P2762
tag: ['网络流', 'Special Judge', 'O2优化', '网络流与线性规划 24 题']
---
# 太空飞行计划问题
## 题目描述

W 教授正在为国家航天中心计划一系列的太空飞行。每次太空飞行可进行一系列商业性实验而获取利润。现已确定了一个可供选择的实验集合 $ E = \{ E_1, E_2, \cdots, E_m \} $，和进行这些实验需要使用的全部仪器的集合 $ I = \{ I_1, I_2, \cdots, I_n \} $。实验 $ E_j $ 需要用到的仪器是 $ I $ 的子集 $ R_j \subseteq I $。

配置仪器 $ I_k $ 的费用为 $ c_k $ 美元。实验 $ E_j $ 的赞助商已同意为该实验结果支付 $ p_j $ 美元。W 教授的任务是找出一个有效算法，确定在一次太空飞行中要进行哪些实验并因此而配置哪些仪器才能使太空飞行的净收益最大。这里净收益是指进行实验所获得的全部收入与配置仪器的全部费用的差额。

对于给定的实验和仪器配置情况，编程找出净收益最大的试验计划。
## 输入格式

第 $ 1 $ 行有 $ 2 $ 个正整数 $ m $ 和 $ n $。$ m $ 是实验数，$ n $ 是仪器数。接下来的 $ m $ 行，每行是一个实验的有关数据。第一个数赞助商同意支付该实验的费用；接着是该实验需要用到的若干仪器的编号。最后一行的 $ n $ 个数是配置每个仪器的费用。
## 输出格式

第 $ 1 $ 行是实验编号，第 $ 2 $ 行是仪器编号，最后一行是净收益。

## 样例

### 样例输入 #1
```
2 3
10 1 2
25 2 3
5 6 7
```
### 样例输出 #1
```
1 2
1 2 3
17
```
## 提示

感谢 @FlierKing 提供 spj

$1 \leq n, m \leq 50 $

这道题数据是在 Windows 生成的，输入数据中所有的换行都是 `\r\n` 而不是 `\n`  
读入某实验需要用到的仪器编号的时候，可以这么读入。(感谢@zhouyonglong的提供)
```cpp
char tools[10000];
memset(tools,0,sizeof tools);
cin.getline(tools,10000);
int ulen=0,tool;
while (sscanf(tools+ulen,"%d",&tool)==1)//之前已经用scanf读完了赞助商同意支付该实验的费用
{//tool是该实验所需仪器的其中一个      
    //这一行，你可以将读进来的编号进行储存、处理，如连边。
    if (tool==0) 
        ulen++;
    else {
        while (tool) {
            tool/=10;
            ulen++;
        }
    }
    ulen++;
}
```


---

---
title: "最小路径覆盖问题"
layout: "post"
diff: 省选/NOI-
pid: P2764
tag: ['网络流', 'Special Judge', 'O2优化', '网络流与线性规划 24 题']
---
# 最小路径覆盖问题
## 题目描述

给定有向图 $G=(V,E)$ 。设 $P$ 是 $G$ 的一个简单路（顶点不相交）的集合。如果 $V$ 中每个定点恰好在 $P$ 的一条路上，则称 $P$ 是 $G$ 的一个路径覆盖。$P$ 中路径可以从 $V$ 的任何一个定点开始，长度也是任意的，特别地，可以为 $0$。$G$ 的最小路径覆盖是 $G$ 所含路径条数最少的路径覆盖。设计一个有效算法求一个 DAG（有向无环图）$G$ 的最小路径覆盖。

## 输入格式

第一行有两个正整数 $n$ 和 $m$。$n$ 是给定 DAG（有向无环图）$G$ 的顶点数，$m$ 是 $G$ 的边数。接下来的 $m$ 行，每行有两个正整数 $i$ 和 $j$ 表示一条有向边 $(i,j)$。
## 输出格式

从第一行开始，每行输出一条路径。文件的最后一行是最少路径数。

## 样例

### 样例输入 #1
```
11 12
1 2
1 3
1 4
2 5
3 6
4 7
5 8
6 9
7 10
8 11
9 11
10 11
```
### 样例输出 #1
```
1 4 7 10 11
2 5 8
3 6 9
3
```
## 提示

对于 $100\%$ 的数据，$1\leq n\leq 150$，$1\leq m\leq 6000$。

由 @FlierKing 提供 SPJ


---

---
title: "最长不下降子序列问题"
layout: "post"
diff: 省选/NOI-
pid: P2766
tag: ['动态规划 DP', '网络流', 'O2优化', '网络流与线性规划 24 题']
---
# 最长不下降子序列问题
## 题目描述

给定正整数序列 $x_1 \ldots, x_n$。

1. 计算其最长不下降子序列的长度 $s$。
2. 如果每个元素只允许使用一次，计算从给定的序列中最多可取出多少个长度为 $s$ 的不下降子序列。
3. 如果允许在取出的序列中多次使用 $x_1$ 和 $x_n$（其他元素仍然只允许使用一次），则从给定序列中最多可取出多少个**不同的**长度为 $s$ 的不下降子序列。

令 $a_1, a_2, \ldots, a_s$ 为构造 $S$ 时所使用的下标，$b_1, b_2, \ldots, b_s$ 为构造 $T$ 时所使用的下标。且 $\forall i \in [1,s-1]$，都有 $a_i \lt a_{i+1}$，$b_i \lt b_{i+1}$。则 $S$ 和 $T$ **不同**，当且仅当 $\exists i \in [1,s]$，使得 $a_i \neq b_i$。
## 输入格式

第一行有一个正整数 $n$，表示给定序列的长度。接下来的一行有 $n$ 个正整数$x_1, ..., x_n$。

## 输出格式

- 第 1 行是最长不下降子序列的长度 $s$。
- 第 2 行是可取出的长度为 $s$ 的不下降子序列个数。
- 第 3 行是允许在取出的序列中多次使用 $x_1$ 和 $x_n$ 时可取出的长度为 $s$ 的**不同的**不下降子序列个数。

## 样例

### 样例输入 #1
```
4
3 6 2 5
```
### 样例输出 #1
```
2
2
3
```
## 提示

$1 \le n\le 500$


---

---
title: "航空路线问题"
layout: "post"
diff: 省选/NOI-
pid: P2770
tag: ['网络流', 'Special Judge', 'O2优化', '网络流与线性规划 24 题']
---
# 航空路线问题
## 题目描述

给定一张航空图，图中顶点代表城市，边代表两城市间的直通航线，并且不存在任何两个城市在同一条经线上。现要求找出一条满足下述限制条件的且途经城市最多的旅行路线。

1. 从最西端城市出发，单向从西向东途经若干城市到达最东端城市，然后再单向从东向西飞回起点（可途经若干城市）。

2. 除起点城市外，任何城市只能访问一次。

对于给定的航空图，试设计一个算法找出一条满足要求的最佳航空旅行路线。
## 输入格式

输入的第一行是用空格隔开的两个整数，分别代表航空图的点数 $n$ 和边数 $v$。

第 $2$ 到第 $(n + 1)$ 行，每行一个字符串，第 $(i + 1)$ 行的字符串代表从西向东第 $i$ 座城市的名字 $s_i$。

第 $(n + 2)$ 到第 $(n + v + 1)$ 行，每行两个字符串 $x, y$，代表城市 $x$ 和城市 $y$ 之间存在一条直通航线。
## 输出格式

**本题存在 Special Judge**。

请首先判断是否存在满足要求的路线，若存在，请给出一种旅行的方案。

如果存在路线，输出格式为：

- 请在第一行输出一个整数 $m$，代表途径最多的城市数。
- 在第 $2$ 到第 $(m + 2)$ 行，每行一个字符串，第 $(i + 1)$ 行的字符串代表旅行路线第 $i$ 个经过的城市的名字。请注意第 $1$ 和第 $m$ 个城市必然是出发城市名。

否则请输出一行一个字符串 ``No Solution!``。
## 样例

### 样例输入 #1
```
8 9
Vancouver
Yellowknife
Edmonton
Calgary
Winnipeg
Toronto
Montreal
Halifax
Vancouver Edmonton
Vancouver Calgary
Calgary Winnipeg
Winnipeg Toronto
Toronto Halifax
Montreal Halifax
Edmonton Montreal
Edmonton Yellowknife
Edmonton Calgary
```
### 样例输出 #1
```
7
Vancouver
Edmonton
Montreal
Halifax
Toronto
Winnipeg
Calgary
Vancouver 
```
## 提示

**数据规模与约定**

对于 $100\%$ 的数据，保证 $1 \leq n < 100$，$1 \leq v \leq \frac{n \times (n - 1)}{2}$，$s_i$ 的长度不超过 $15$，且仅可能包含大小写字母与数字，$x, y$ 一定是输入中给出的城市名，且不会有同一组 $x, y$ 被给出两次。



---

---
title: "方格取数问题"
layout: "post"
diff: 省选/NOI-
pid: P2774
tag: ['网络流', 'O2优化', '深度优先搜索 DFS', '最小割', '网络流与线性规划 24 题']
---
# 方格取数问题
## 题目描述

有一个 $m$ 行 $n$ 列的方格图，每个方格中都有一个正整数。现要从方格中取数，使任意两个数所在方格没有公共边，且取出的数的总和最大，请求出最大的和。

## 输入格式

第一行是两个用空格隔开的整数，分别代表方格图的行数 $m$ 和列数 $n$。

第 $2$ 到第 $(m + 1)$ 行，每行 $n$ 个整数，第 $(i + 1)$ 行的第 $j$ 个整数代表方格图第 $i$ 行第 $j$ 列的的方格中的数字 $a_{i, j}$。
## 输出格式

输出一行一个整数，代表和最大是多少。
## 样例

### 样例输入 #1
```
3 3
1 2 3
3 2 3
2 3 1 
```
### 样例输出 #1
```
11
```
## 提示

**数据规模与约定**

对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 100$，$1 \leq a_{i, j} \leq 10^5$。

**提示**

请注意输入的第一行先读入 $m$ 再读入 $n$。


---

---
title: "[NOI2009] 植物大战僵尸"
layout: "post"
diff: 省选/NOI-
pid: P2805
tag: ['2009', 'NOI', '网络流', '图论建模', '拓扑排序', '最小割']
---
# [NOI2009] 植物大战僵尸
## 题目背景

Plants vs. Zombies（PVZ）是最近十分风靡的一款小游戏。Plants（植物）和 Zombies（僵尸）是游戏的主角，其中 Plants 防守，而 Zombies 进攻。该款游戏包含多种不同的挑战系列，比如 Protect Your Brain、Bowling 等等。其中最为经典的，莫过于玩家通过控制 Plants 来防守 Zombies 的进攻，或者相反地由玩家通过控制 Zombies 对 Plants 发起进攻。


## 题目描述

现在，我们将要考虑的问题是游戏中 Zombies 对 Plants 的进攻，请注意，本题中规则与实际游戏**有所不同**。游戏中有两种角色，Plants 和 Zombies，每个 Plant 有一个攻击位置集合，它可以对这些位置进行保护；而 Zombie 进攻植物的方式是走到植物所在的位置上并将其吃掉。

游戏的地图可以抽象为一个 $N$ 行 $M$ 列的矩阵，行从上到下用 $0$ 到 $N–1$ 编号，列从左到右用 $0$ 到 $M–1$ 编号；在地图的每个位置上都放有一个 $Plant$，为简单起见，我们把位于第 $r$ 行第 $c$ 列的植物记为 $P_{r, c}$。

Plants 分很多种，有「攻击类」「防守类」和「经济类」等等。为了简单的描述每个 Plant，定义 $\operatorname{Score}$ 和 $\operatorname{Attack}$ 如下：

* $\operatorname{Score}(P_{r, c})$ — Zombie 击溃植物 $P_{r, c}$ 可获得的能源。   
若 $\operatorname{Score}(P_{r, c})$ 为非负整数，则表示击溃植物 $P_{r, c}$ 可获得能源 $\operatorname{Score}(P_{r, c})$，若为负数表示击溃 $P_{r, c}$ 需要付出能源 $-\operatorname{Score}(P_{r, c})$。

* $\operatorname{Attack}(P_{r, c})$ — 植物 $P_{r, c}$ 能够对 Zombie 进行攻击的位置集合。

Zombies 必须从地图的右侧进入，且只能沿着水平方向进行移动。Zombies 攻击植物的唯一方式就是走到该植物所在的位置并将植物吃掉。因此 Zombies 的进攻总是从地图的右侧开始。也就是说，对于第 $r$ 行的进攻，Zombies 必须首先攻击 $P_{r, M-1}$；若需要对 $P_{r, c}$（$0 \le c < m - 1$）攻击，必须将 $P_{r,M-1}, P_{r, M-2} \cdots P_{r, c+1}$ 先击溃，并移动到位置 $(r, c)$ 才可进行攻击。

在本题的设定中，Plants 的攻击力是无穷大的，一旦 Zombie 进入某个 Plant 的攻击位置，该 Zombie 会被瞬间消灭，而该 Zombie 没有时间进行任何攻击操作。因此，即便 Zombie 进入了一个 Plant 所在的位置，但该位置属于其他植物的攻击位置集合，则 Zombie 会被瞬间消灭而所在位置的植物则安然无恙（在我们的设定中，Plant 的攻击位置不包含自身所在位置，否则你就不可能击溃它了）。

Zombies 的目标是对 Plants 的阵地发起进攻并获得最大的能源收入。每一次，你可以选择一个可进攻的植物进行攻击。本题的目标为，制定一套 Zombies 的进攻方案，选择进攻哪些植物以及进攻的顺序，从而获得最大的能源收入。
## 输入格式

第一行包含两个正整数 $N$ 和 $M$，分别表示地图的行数和列数。

接下来 $N \times M$ 行描述每个位置上植物的信息。第 $r \times M + c + 1$ 行按照如下格式给出植物 $P_{r, c}$ 的信息：

第一个整数为 $\operatorname{Score}(P_{r,c})$，第二个整数为集合 $\operatorname{Attack}(P_{r,c})$ 中的位置个数 $w$，接下来 $w$ 个位置信息 $(r', c')$，表示 $P_{r, c}$ 可以攻击位置第 $r'$ 行第 $c'$ 列。


## 输出格式

仅包含一个整数，表示可以获得的最大能源收入。注意，你也可以选择不进行任何攻击，这样能源收入为 $0$。
## 样例

### 样例输入 #1
```
3 2
10 0
20 0
-10 0
-5 1 0 0
100 1 2 1
100 0
```
### 样例输出 #1
```
25
```
## 提示

#### 数据规模与约定
- 对于 $20\%$ 的数据，保证 $ N, M \le 5$。
- 对于 $40\%$ 的数据，保证 $ N, M \le 10$。
- 对于 $100\%$ 的数据，保证 $1 \le N \le 20$，$1 \le M \le 30$，$-10^4 ≤ \operatorname{Score} \le 10^4$。

#### 说明
题面由 @syksykCCC 修改。


---

---
title: "时间表"
layout: "post"
diff: 省选/NOI-
pid: P2823
tag: ['2016', '福建省历届夏令营', '网络流', '福建']
---
# 时间表
## 题目背景

小 A 是一个电话服务中心的主管，他的团队有一大批人。他们团队中的每个人都会花费他们的时间参加会议和通过电话与客户通话，当然还有研究团队的项目也是要花费他们的时间的。

## 题目描述

他们中的每个人在每个小时只能在参加会议、和客户通话、研究项目三者中选择一个来进行。为了提高效率，每个小时必须完整地奉献到这一项工作中，不能中途改变。

小 A 所在的地方很奇怪，他们一个星期有 $D$ 天，从 $1$ 到 $D$ 标号。为了照顾员工的嗓子，第 $i$ 个人在每个星期最多能够与客户通话 $L_i$ 小时。

开会是已经计划好的事情，对于每个人他们需要在什么时间参加会议是确定的。这个电话服务中心每天要有 $H$ 个小时的时间是可以回复客户的电话的，为了简便，这 $H$ 个小时被从 $1$ 到 $H$ 标号。

对于每周的每个小时，有多少客户会连接到电话服务中心是已知的。因此，小 A 知道他在第 $i$ 天的第 $j$ 个小时必须安排 $R_{i,j}$ 个员工来和客户通话。如果第 $k$ 个人在第 $i$ 天的第 $j$ 个小时没有会议可以和客户通话，那么 $F_{k,i,j}$ 的值为 $1$，如果有会议则为 $0$。

再次说明，小  A的世界十分奇怪，他们除了每周可能不是 $7$ 天以外，每天也可能不是 $24$ 个小时。

小 A 需要为每个员工创建一个时间表。由于员工也需要吃饭和休息，每天都会有一个午休时间，这段时间是从 $L_{\text{T}_\text{begin}}$ 开始到 $L_{\text{T}_\text{end}}$ 结束（$L_{\text{T}_\text{begin}}$ 和 $L_{\text{T}_\text{end}}$ 也包含在内）。小 A 需要确保每个员工在这段时间内至少有一个小时是没有参加会议或与客户通话的，以便他们可以吃饭和休息，或者做自己想做的事情。

如果某个人在某个小时内没有会议也没有和客户通话，那他在这个小时就可以去研究公司项目，研究公司项目也算在工作时间之内。另外，他们有可能会去研究自己的项目，然而这是不算在工作时间内的。

小 A 想要知道，他是否有可能安排出这样一个时间表，并且满足：

- 每个人每天最多花费 $N$ 个小时在参加会议和客户通话上；
- 每个人每周最多花费 $L_i$ 个小时和客户通话；
- 每个人在午休时间至少有一个小时没有参加会议或和客户通话；
- 对于第 $i$ 天第 $j$ 个小时，恰好有 $R_{i,j}$ 个人可以与客户通话。

## 输入格式

第一行包含一个正整数 $T$，表示测试数据的组数。

每组数据第一行包含四个整数 $P, D, H, N$，分别表示团队的人数，每周需要工作的天数，每天电话服务中心可以响应客户电话的小时数，以及每天每个人的工作时长；

接下来一行包含 $P$ 个整数，第 $i$ 个表示 $L_i$；

再接下来一行包含两个整数$L_{\text{T}_\text{begin}}$ 和 $L_{\text{T}_\text{end}}$，表示午休时间段；

接下来 $D$ 行每行包含 $H$ 个整数，第 $i$ 行第 $j$ 个整数表示 $R_{i,j}$；

再接下来 $P$ 个块，每个块有 $D$ 行，每行包含 $H$ 个整数。第 $k$ 个块的第$i$ 行的第 $j$ 个数表示 $F_{k,i,j}$。

## 输出格式

共 $T$ 行，如果第 $i$ 组数据存在可行方案则输出 `Yes`，否则输出 `No`。

## 样例

### 样例输入 #1
```
2
2 2 3 2
4 1
2 3
0 1 1
0 1 0
1 1 1
1 1 1
1 1 1
1 0 1
2 2 3 2
4 1
2 3
0 1 2
0 1 0
1 1 1
1 1 1
1 1 1
1 0 1
```
### 样例输出 #1
```
Yes
No
```
## 提示

对于 $100\%$ 的数据满足有

$1 \leq T \leq 5,1 \leq N \leq H \leq 70$

$1 \leq D, P\leq 70,1 \leq L_i \leq N\times D, 0 \leq R_{i, j} \leq 15$

$0 \leq F_{k, i, j} \leq 1,1 \leq L_{\text{T}_\text{begin}} \leq L_{\text{T}_\text{end}} \leq N$。



---

---
title: "[HEOI2016/TJOI2016] 游戏"
layout: "post"
diff: 省选/NOI-
pid: P2825
tag: ['2016', '各省省选', '网络流', '河北', '连通块', '二分图', '天津']
---
# [HEOI2016/TJOI2016] 游戏
## 题目描述

在 2016 年，佳媛姐姐喜欢上了一款游戏，叫做泡泡堂。

简单的说，这个游戏就是在一张地图上放上若干个炸弹，看是否能炸到对手，或者躲开对手的炸弹。在玩游戏的过程中，小 H 想到了这样一个问题：当给定一张地图，在这张地图上最多能放上多少个炸弹能使得任意两个炸弹之间不会互相炸到。炸弹能炸到的范围是该炸弹所在的一行和一列，炸弹的威力可以穿透软石头，但是不能穿透硬石头。

给定一张 $ n \times m $ 的网格地图:其中 ``*`` 代表空地，炸弹的威力可以穿透，可以在空地上放置一枚炸弹。 ``x`` 代表软石头，炸弹的威力可以穿透，不能在此放置炸弹。``#`` 代表硬石头，炸弹的威力是不能穿透的，不能在此放置炸弹。例如：给出 $ 1 \times 4 $ 的网格地图 `` *xx*``，这个地图上最多只能放置一个炸弹。给出另一个$ 1 \times 4 $ 的网格地图 ``*x#*``，这个地图最多能放置两个炸弹。

现在小 H 任意给出一张 $ n \times m $ 的网格地图，问你最多能放置多少炸弹。
## 输入格式

第一行输入两个正整数 $ n, m $，$ n $ 表示地图的行数，$ m $ 表示地图的列数。

接下来输入 $ n $ 行 $ m $ 列个字符，代表网格地图。``*``的个数不超过 $ n \times m $ 个。
## 输出格式

输出一个整数 $ a $，表示最多能放置炸弹的个数。
## 样例

### 样例输入 #1
```
4 4
#***
*#**
**#*
xxx#
```
### 样例输出 #1
```
5
```
## 提示

$1 \leq n,m \leq 50$


---

---
title: "[USACO06FEB] Steady Cow Assignment G"
layout: "post"
diff: 省选/NOI-
pid: P2857
tag: ['贪心', '2006', '二分', 'USACO', '网络流', '枚举', '双指针 two-pointer']
---
# [USACO06FEB] Steady Cow Assignment G
## 题目描述

Farmer John's N (1 <= N <= 1000) cows each reside in one of B (1 <= B <= 20) barns which, of course, have limited capacity. Some cows really like their current barn, and some are not so happy.

FJ would like to rearrange the cows such that the cows are as equally happy as possible, even if that means all the cows hate their assigned barn.


Each cow gives FJ the order in which she prefers the barns.  A cow's happiness with a particular assignment is her ranking of her barn. Your job is to find an assignment of cows to barns such that no barn's capacity is exceeded and the size of the range (i.e., one more than the positive difference between the the highest-ranked barn chosen and that lowest-ranked barn chosen) of barn rankings the cows give their assigned barns is as small as possible.

## 输入格式

Line 1: Two space-separated integers, N and B


Lines 2..N+1: Each line contains B space-separated integers which are exactly 1..B sorted into some order. The first integer on line i+1 is the number of the cow i's top-choice barn, the second integer on that line is the number of the i'th cow's second-choice barn, and so on.


Line N+2: B space-separated integers, respectively the capacity of the first barn, then the capacity of the second, and so on. The sum of these numbers is guaranteed to be at least N.

## 输出格式

Line 1: One integer, the size of the minumum range of barn rankings the cows give their assigned barns, including the endpoints.

## 样例

### 样例输入 #1
```
6 4
1 2 3 4
2 3 1 4
4 2 3 1
3 1 2 4
1 3 4 2
1 4 2 3
2 1 3 2
```
### 样例输出 #1
```
2
```
## 提示

Explanation of the sample:




Each cow can be assigned to her first or second choice: barn 1 gets cows 1 and 5, barn 2 gets cow 2, barn 3 gets cow 4, and barn 4 gets cows 3 and 6.

## 题目翻译

有 $N$ 头牛，$B$ 个牛棚。告诉你每头牛心里牛棚的座次，即哪个牛棚他最喜欢，哪个第 $2$ 喜欢，哪个第 $3$ 喜欢，等等。但牛棚容量一定，所以每头牛分配到的牛棚在该牛心中的座次有高有低。现在求一种最公平的方法分配牛到牛棚，使所有牛中，所居牛棚的座次最高与最低的跨度最小。


---

---
title: "[USACO07OPEN] Dining G"
layout: "post"
diff: 省选/NOI-
pid: P2891
tag: ['动态规划 DP', '递推', '2007', 'USACO', '网络流']
---
# [USACO07OPEN] Dining G
## 题目描述

Cows are such finicky eaters. Each cow has a preference for certain foods and drinks, and she will consume no others.

Farmer John has cooked fabulous meals for his cows, but he forgot to check his menu against their preferences. Although he might not be able to stuff everybody, he wants to give a complete meal of both food and drink to as many cows as possible.

Farmer John has cooked F (1 ≤ F ≤ 100) types of foods and prepared D (1 ≤ D ≤ 100) types of drinks. Each of his N (1 ≤ N ≤ 100) cows has decided whether she is willing to eat a particular food or drink a particular drink. Farmer John must assign a food type and a drink type to each cow to maximize the number of cows who get both.

Each dish or drink can only be consumed by one cow (i.e., once food type 2 is assigned to a cow, no other cow can be assigned food type 2).

## 输入格式

Line 1: Three space-separated integers: N, F, and D


Lines 2..N+1: Each line i starts with a two integers Fi and Di, the number of dishes that cow i likes and the number of drinks that cow i likes. The next Fi integers  denote the dishes that cow i will eat, and the Di integers following that denote the drinks that cow i will drink.

## 输出格式

Line 1: A single integer that is the maximum number of cows that can be fed both food and drink that conform to their wishes

## 样例

### 样例输入 #1
```
4 3 3
2 2 1 2 3 1
2 2 2 3 1 2
2 2 1 3 1 2
2 1 1 3 3
```
### 样例输出 #1
```
3
```
## 提示

One way to satisfy three cows is:


Cow 1: no meal


Cow 2: Food #2, Drink #2


Cow 3: Food #1, Drink #1


Cow 4: Food #3, Drink #3


The pigeon-hole principle tells us we can do no better since there are only three kinds of food or drink. Other test data sets are more challenging, of course.

## 题目翻译

有 $F$ 种食物和 $D$ 种饮料，每种食物或饮料只能供一头牛享用，且每头牛只享用一种食物和一种饮料。现在有 $n$ 头牛，每头牛都有自己喜欢的食物种类列表和饮料种类列表，问最多能使几头牛同时享用到自己喜欢的食物和饮料。

对于全部数据，$1 \le f \le 100$，$1 \le d \le 100$，$1 \le n \le 100$。


---

---
title: "[USACO09MAR] Earthquake Damage 2 G"
layout: "post"
diff: 省选/NOI-
pid: P2944
tag: ['2009', 'USACO', '网络流', '图论建模', '最小割']
---
# [USACO09MAR] Earthquake Damage 2 G
## 题目描述

Wisconsin has had an earthquake that has struck Farmer John's farm! The earthquake has damaged some of the pastures so that they are unpassable. Remarkably, none of the cowpaths was damaged.

As usual, the farm is modeled as a set of P (1 <= P <= 3,000) pastures conveniently numbered 1..P which are connected by a set of C (1 <= C <= 20,000) non-directional cowpaths conveniently numbered 1..C. Cowpath i connects pastures a\_i and b\_i (1 <= a\_i <= P; 1 <= b\_i <= P). Cowpaths might connect a\_i to itself or perhaps might connect two pastures more than once.  The barn is located in pasture 1.

A total of N (1 <= N <= P) cows (in different pastures) sequentially contacts Farmer John via moobile phone with an integer message report\_j (2 <= report\_j <= P) that indicates that pasture report\_j is undamaged but that the calling cow is unable to return to the barn from pasture report\_j because she could not find a path that does not go through damaged pastures.

After all the cows report in, determine the minimum number of pastures that are damaged.

地震袭击了威斯康星州，一些牧场被摧毁了。

一共有 $P$ 个牧场。由 $C$ 条双向路连接。两个牧场间可能有多条路。一条路也可能连接相同的牧场。牛棚坐落在牧场 $1$。

$N\ (1 \le N \le P)$ 只奶牛打来了求救电话，说她们的农场没有被摧毁，但是已经无法到达牛棚。求出最少可能有多少牧场被摧毁。

## 输入格式

\* Line 1: Three space-separated integers: P, C, and N

\* Lines 2..C+1: Line i+1 describes cowpath i with two integers: a\_i and b\_i

\* Lines C+2..C+N+1: Line C+1+j contains a single integer: report\_j

## 输出格式

\* Line 1: One number, the minimum number of damaged pastures.

## 样例

### 样例输入 #1
```
5 5 2 
1 2 
2 3 
3 5 
2 4 
4 5 
4 
5 

```
### 样例输出 #1
```
1 

```
## 提示

Only pasture 2 being damaged gives such a scenario.



---

---
title: "[CQOI2009] 跳舞"
layout: "post"
diff: 省选/NOI-
pid: P3153
tag: ['贪心', '2009', '重庆', '各省省选', '网络流']
---
# [CQOI2009] 跳舞
## 题目描述

一次舞会有 $n$ 个男孩和 $n$ 个女孩。

每首曲子开始时，所有男孩和女孩恰好配成 $n$ 对跳交谊舞。每个男孩都不会和同一个女孩跳两首（或更多）舞曲。

有一些男孩女孩相互喜欢，而其他相互不喜欢（不会“单向喜欢”）。每个男孩最多只愿意和 $k$ 个不喜欢的女孩跳舞，而每个女孩也最多只愿意和 $k$ 个不喜欢的男孩跳舞。

给出每对男孩女孩是否相互喜欢的信息，舞会最多能有几首舞曲？
## 输入格式

第一行包含两个整数 $n$ 和 $k$。

以下 $n$ 行每行包含 $n$ 个字符，每个字符只可能是 `Y` 或 `N`。第 $(i + 1)$ 行的第 $j$ 个字符为 `Y` 当且仅当男孩 $i$ 和女孩 $j$ 相互喜欢。

## 输出格式

一行一个整数代表舞曲数目的最大值。
## 样例

### 样例输入 #1
```
3 0
YYY
YYY
YYY
```
### 样例输出 #1
```
3
```
## 提示

#### 数据规模与约定

- 对于 $100\%$ 的数据，保证 $1\leq n\leq 50$，$0\leq k\leq 30$。


---

---
title: "[CQOI2012] 交换棋子"
layout: "post"
diff: 省选/NOI-
pid: P3159
tag: ['2012', '重庆', '各省省选', '网络流', '费用流']
---
# [CQOI2012] 交换棋子
## 题目描述

有一个 $n$ 行 $m$ 列的黑白棋盘，你每次可以交换两个相邻格子（**相邻是指有公共边或公共顶点**）中的棋子，最终达到目标状态。要求第 $i$ 行第 $j$ 列的格子只能参与 $m_{i,j}$ 次交换。
## 输入格式

第一行包含两个整数 $n,m$。以下 $n$ 行为初始状态，每行为一个包含 $m$ 个字符的 $01$ 串，其中 $0$ 表示黑色棋子，$1$ 表示白色棋子。以下 $n$ 行为目标状态，格式同初始状态。以下 $n$ 行每行为一个包含 $m$ 个 $0\sim9$ 数字的字符串，表示每个格子参与交换的次数上限。

## 输出格式

输出仅一行，为最小交换总次数。如果无解，输出 $-1$。
## 样例

### 样例输入 #1
```
3 3
110
000
001
000
110
100
222
222
222
```
### 样例输出 #1
```
4
```
## 提示

### 数据规模与约定

对于 $100\%$ 的数据，$1\leq n,m\leq20$。


---

---
title: "[CQOI2014] 危桥"
layout: "post"
diff: 省选/NOI-
pid: P3163
tag: ['2014', '重庆', '各省省选', '网络流']
---
# [CQOI2014] 危桥
## 题目描述

Alice 和 Bob 居住在一个由 $N$ 座岛屿组成的国家，岛屿被编号为 $0$ 到 $N-1$。某些岛屿之间有桥相连，桥上的道路是双向的，但一次只能供一人通行。其中一些桥由于年久失修成为危桥，最多只能通行两次。

Alice 希望在岛屿 $a_1$ 和 $a_2$ 之间往返 $a_n$ 次（从 $a1$ 到 $a2$ 再从 $a2$ 到 $a1$ 算一次往返）。同时，Bob 希望在岛屿 $b_1$ 和 $b_2$ 之间往返 $b_n$ 次。这个过程中，所有危桥最多通行两次，其余的桥可以无限次通行。请问 Alice 和 Bob 能完成他们的愿望吗？

## 输入格式

本题有多组测试数据。

每组数据第一行包含七个空格隔开的整数，分别为$N$、$a_1$、$a_2$、$a_n$、$b_1$、$b_2$、$b_n$。  
接下来是一个 $N$ 行 $N$ 列的对称矩阵，由大写字母组成。矩阵的 $i$ 行 $j$ 列描述编号 $i-1$ 和 $j-1$ 的岛屿间的连接情况，若为 “`O`” 则表示有危桥相连：为 “`N`” 表示有普通的桥相连：为 “`X`” 表示没有桥相连。
## 输出格式

对于每组测试数据输出一行，如果他们都能完成愿望输出 “Yes”，否则输出 “No”（不含引号）。

## 样例

### 样例输入 #1
```
4 0 1 1 2 3 1
XOXX
OXOX
XOXO
XXOX
4 0 2 1 1 3 2
XNXO
NXOX
XOXO
OXOX

```
### 样例输出 #1
```
Yes
No

```
## 提示

对于所有数据，$4 \leq N\leq 50,\ 0 \leq a_1, a_2, b_1, b_2 \leq N-1,\ 1 \leq a_n, b_n \leq 50$。


---

---
title: "[CQOI2015] 网络吞吐量"
layout: "post"
diff: 省选/NOI-
pid: P3171
tag: ['2015', '重庆', '各省省选', '网络流', '最短路']
---
# [CQOI2015] 网络吞吐量
## 题目背景

路由是指通过计算机网络把信息从源地址传输到目的地址的活动，也是计算机网络设计中的重点和难点。网络中实现路由转发的硬件设备称为路由器。为了使数据包最快的到达目的地，路由器需要选择最优的路径转发数据包。例如在常用的路由算法 OSPF (开放式最短路径优先) 中，路由器会使用经典的 Dijkstra 算法计算最短路径，然后尽量沿最短路径转发数据包。

## 题目描述

现在，若已知一个计算机网络中各路由器间的连接情况，以及各个路由器的最大吞吐量（即每秒能转发的数据包数量），网络中的路由器使用 $1$ 到 $n$ 编号，假设所有数据包一定沿最短路径转发，试计算从路由器 $1$ 到路由器 $n$ 的网络的最大吞吐量。计算中忽略转发及传输的时间开销，不考虑链路的带宽限制，即认为数据包可以瞬间通过网络。路由器 $1$ 到路由器 $n$ 作为起点和终点，自身的吞吐量不用考虑，网络上也不存在将 $1$ 和 $n$ 直接相连的链路。

## 输入格式

输入的第一行是用空格隔开的两个整数，分别代表路由器的数量 $n$ 和链路的数量 $m$。

第 $2$ 到第 $(m + 1)$  行，每行三个整数 $u, v, w$，代表存在一条连结路由器 $u$ 和路由器 $v$  的距离为 $w$ 的双向链路。

第 $(m + 2)$ 到第 $(n + m + 1)$  行，每行一个整数，第 $(i + m + 1)$ 行的整数代表路由器 $i$ 的吞吐量 $c_i$。

## 输出格式

输出一行一个整数，代表网络的最大吞吐量。

## 样例

### 样例输入 #1
```
7 10
1 2 2
1 5 2
2 4 1
2 3 3
3 7 1
4 5 4
4 3 1
4 6 1
5 6 2
6 7 1
1
100
20
50
20
60
1
```
### 样例输出 #1
```
70
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq n \leq 500$，$1 \leq m \leq 10^5$，$1 \leq w, c_i \leq 10^9$。



---

---
title: "[HNOI2007] 紧急疏散EVACUATE"
layout: "post"
diff: 省选/NOI-
pid: P3191
tag: ['搜索', '2007', '二分', '网络流', '湖南']
---
# [HNOI2007] 紧急疏散EVACUATE
## 题目描述

发生了火警，所有人员需要紧急疏散！假设每个房间是一个N M的矩形区域。每个格子如果是'.'，那么表示这是一块空地；如果是'X'，那么表示这是一面墙，如果是'D'，那么表示这是一扇门，人们可以从这儿撤出房间。已知门一定在房间的边界上，并且边界上不会有空地。最初，每块空地上都有一个人，在疏散的时候，每一秒钟每个人都可以向上下左右四个方向移动一格，当然他也可以站着不动。疏散开始后，每块空地上就没有人数限制了（也就是说每块空地可以同时站无数个人）。但是，由于门很窄，每一秒钟只能有一个人移动到门的位置，一旦移动到门的位置，就表示他已经安全撤离了。现在的问题是：如果希望所有的人安全撤离，最短需要多少时间？或者告知根本不可能。

## 输入格式

输入文件第一行是由空格隔开的一对正整数N与M，3<=N <=20，3<=M<=20，以下N行M列描述一个N M的矩阵。其中的元素可为字符'.'、'X'和'D'，且字符间无空格。

## 输出格式

只有一个整数K，表示让所有人安全撤离的最短时间，如果不可能撤离，那么输出'impossible'（不包括引号）。

## 样例

### 样例输入 #1
```
5 5
XXXXX
X...D
XX.XX
X..XX
XXDXX
```
### 样例输出 #1
```
3
```
## 提示

2015.1.12新加数据一组，鸣谢1756500824

C++语言请用scanf("%s",s)读入！



---

---
title: "[HNOI2013] 切糕"
layout: "post"
diff: 省选/NOI-
pid: P3227
tag: ['2013', '网络流', '湖南', '最小割']
---
# [HNOI2013] 切糕
## 题目描述

经过千辛万苦小 A 得到了一块切糕，切糕的形状是长方体，小 A 打算拦腰将切糕切成两半分给小 B。出于美观考虑，小 A 希望切面能尽量光滑且和谐。于是她找到你，希望你能帮她找出最好的切割方案。

出于简便考虑，我们将切糕视作一个长 $P$、宽 $Q$、高 $R$ 的长方体点阵。我们将位于第 $z$ 层中第 $x$ 行、第 $y$ 列上的点称 $(x,y,z)$，它有一个非负的不和谐值 $v(x,y,z)$。一个合法的切面满足以下两个条件：

 - 与每个纵轴（一共有 $P\times Q$ 个纵轴）有且仅有一个交点。即切面是一个函数 $f(x,y)$，对于所有 $(x,y)(x\in [1,P],y\in[1,Q])$，我们需指定一个切割点 $f(x,y)$，且 $1\le f(x,y)\le R$。

 - 切面需要满足一定的光滑性要求，即相邻纵轴上的切割点不能相距太远。对于所有的 $1\le x,x'\le P$ 和 $1\le y,y'\le Q$，若 $|x-x'|+|y-y'|=1$，则 $|f(x,y)-f(x',y')| \le D$，其中 $D$ 是给定的一个非负整数。

可能有许多切面 $f$ 满足上面的条件，小 A 希望找出总的切割点上的不和谐值最小的那个。
## 输入格式

第一行是三个正整数 $P,Q,R$，表示切糕的长宽高。

第二行有一个非负整数 $D$，表示光滑性要求。

接下来是 $R$ 个 $P$ 行 $Q$ 列的矩阵，第 $z$ 个矩阵的第 $x$ 行第 $y$ 列是 $v(x,y,z)(1\le x\le P,1\le y\le Q,1\le z\le R)$。
## 输出格式

仅包含一个整数，表示在合法基础上最小的总不和谐值。
## 样例

### 样例输入 #1
```
2 2 2
1
6 1
6 1
2 6
2 6
```
### 样例输出 #1
```
6
```
## 提示

#### 输入输出样例 1 解释

最佳切面的 $f$ 为 $f(1,1)=f(2,1)=2,f(1,2)=f(2,2)=1$。

---
#### 数据规模与约定

对于 $100\%$ 的数据，$1 \leq P,Q,R\leq 40,0\le D\le R$，且给出的所有的不和谐值不超过 $1000$。


---

---
title: "[SCOI2014] 方伯伯运椰子"
layout: "post"
diff: 省选/NOI-
pid: P3288
tag: ['2014', '四川', '网络流', '负权环', '分数规划']
---
# [SCOI2014] 方伯伯运椰子
## 题目描述

四川的方伯伯为了致富，决定引进海南的椰子树。方伯伯的椰子园十分现代化，椰子园中有一套独特的交通系统。

现在用点来表示交通节点，边来表示道路。这样，方伯伯的椰子园就可以看作一个有  $N+2$ 个交通节点， $M$ 条边的有向无环图。 $N +1$ 号点为入口， $N +2$ 号点为出口。每条道路都有  $6$ 个参数， $u_i,v_i,a_i,b_i,c_i,d_i$。分别表示，该道路从  $u_i$ 号点通向  $v_i$ 号点，将它的容量压缩一次要  $a_i$ 的花费，容量扩大一次要  $b_i$ 的花费，该条道路当前的运输容量上限为  $c_i$，并且每单位运输量通过该道路要  $d_i$ 的费用。

在这个交通网络中，只有一条道路与起点相连。因为弄坏了这条道路就会导致整个交通网络瘫痪，聪明的方伯伯决定绝不对这条道路进行调整，也就是说，现在除了这条道路之外，对其余道路都可以进行调整。

有两种调整方式：

- 选择一条道路，将其进行一次压缩，这条道路的容量会下降  $1$ 单位。

- 选择一条道路，将其进行一次扩容，这条道路的容量会上升  $1$ 单位。

一条道路可以被多次调整。

由于很久以前，方伯伯就请过一个工程师，对这个交通网络进行过一次大的优化调整。所以现在所有的道路都被完全的利用起来了，即每条道路的负荷都是满的（每条道路的流量等于其容量）。

但方伯伯一想到自己的海南椰子会大丰收，就十分担心巨大的运输量下，会导致过多的花费。因此，方伯伯决定至少进行一次调整，调整之后，必须要保持每条道路满负荷，且总交通量不会减少。

设调整后的总费用是  $Y$，调整之前的总费用是  $X$。现在方伯伯想知道，最优调整比率是多少，即假设他进行了  $k$ 次调整， $\dfrac{X-Y}{k}$最大能是多少？

注：总费用 = 交通网络的运输花费 + 调整的花费
## 输入格式

第一行包含二个整数 $N$， $M$接下来 $M$行代表 $M$条边，表示这个交通网络每行六个整数，表示 $u_i,v_i,a_i,b_i,c_i,d_i$ 。

## 输出格式

一个浮点数，保留二位小数。表示答案，数据保证答案大于 $0$。
## 样例

### 样例输入 #1
```
5 10
1 5 13 13 0 412
2 5 30 18 396 148
1 5 33 31 0 39
4 5 22 4 0 786
4 5 13 32 0 561
4 5 3 48 0 460
2 5 32 47 604 258
5 7 44 37 75 164
5 7 34 50 925 441
6 2 26 38 1000 22
```
### 样例输出 #1
```
103.00
```
## 提示

对于所有数据，$1\le N\le 5\times 10^3$， $M\le 3\times10^3$， $1\le u_i,v_i\le N+2$， $0\le a_i,b_i\le 500$， $0\le c_i\le 10^4$， $0\le d_i\le 10^3$。


---

---
title: "[SDOI2013] 费用流"
layout: "post"
diff: 省选/NOI-
pid: P3305
tag: ['2013', '网络流', '山东', 'Special Judge']
---
# [SDOI2013] 费用流
## 题目描述

Alice 和 Bob 在图论课程上学习了最大流和最小费用最大流的相关知识。

> 最大流问题：给定一张有向图表示运输网络，一个源点 $S$ 和一个汇点 $T$ ，每条边都有最大流量。
> 
> 一个合法的网络流方案必须满足：
> 
> 1. 每条边的实际流量都不超过其最大流量且非负；
> 2. 除了源点 $S$ 和汇点 $T$ 之外，对于其余所有点，都满足该点总流入流量等于该点总流出流量；而 $S$ 点的净流出流量等于 $T$ 点的净流入流量，这个值也即该网络流方案的总运输量。
>
> 最大流问题就是对于给定的运输网络，求总运输量最大的网络流方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/20ipdo37.png)

上图表示了一个最大流问题。对于每条边，右边的数代表该边的最大流量，左边的数代表在最优解中，该边的实际流量。需要注意到，一个最大流问题的解可能不是唯一的。

对于一张给定的运输网络，Alice 先确定一个最大流，如果有多种解，Alice 可以任选一种；之后 Bob 在每条边上分配单位花费（单位花费必须是非负实数），要求所有边的单位花费之和等于 $P$。

总费用等于每一条边的实际流量乘以该边的单位花费。需要注意到，Bob 在分配单位花费之前，已经知道 Alice 所给出的最大流方案。现在 Alice 希望总费用尽量小，而 Bob 希望总费用尽量大。我们想知道，如果两个人都执行最优策略，最大流的值和总费用分别为多少。

## 输入格式

第一行三个整数 $N,M,P$。$N$ 表示给定运输网络中节点的数量，$M$ 表示有向边的数量，$P$ 的含义见问题描述部分。为了简化问题，我们假设源点 $S$ 是点 $1$，汇点 $T$ 是点 $N$。

接下来 $M$ 行，每行三个整数 $A,B,C$，表示有一条从点 $A$ 到点 $B$ 的有向边，其最大流量是 $C$。
## 输出格式

第一行一个整数，表示最大流的值。第二行一个实数，表示总费用。建议选手输出四位以上小数。

## 样例

### 样例输入 #1
```
3 2 1
1 2 10
2 3 15
```
### 样例输出 #1
```
10
10.0000
```
## 提示

**【样例说明】**

对于 Alice，最大流的方案是固定的。两条边的实际流量都为 $10$。

对于 Bob，给第一条边分配 $0.5$ 的费用，第二条边分配 $0.5$ 的费用。总费用为：$10\times 0.5+10\times 0.5=10$。可以证明不存在总费用更大的分配方案。

**【数据规模和约定】**

对于 $20\%$ 的测试数据，所有有向边的最大流量都是 $1$。

对于 $100\%$ 的测试数据，$N\le 100$，$M\le 1000$。

对于 $100\%$ 的测试数据：所有点的编号在 $1\sim N$ 范围内，$1 \le \text{每条边的最大流量} \le 50000$，$1\le P\le 10$，给定运输网络中不会有起点和终点相同的边。



---

---
title: "[SDOI2014] LIS"
layout: "post"
diff: 省选/NOI-
pid: P3308
tag: ['2014', '网络流', '山东', '最小割']
---
# [SDOI2014] LIS
## 题目描述

给定序列 $A$，序列中的每一项 $A_i$ 有删除代价 $B_i$ 和附加属性 $C_i$。请删除若干项，使得 $A$ 的最长上升子序列长度减少至少 $1$，且付出的代价之和最小，并输出方案。

如果有多种方案，请输出将删去项的附加属性排序之后，字典序最小的一种。

## 输入格式

输入包含多组数据。    

输入的第一行包含整数 $T$，表示数据组数。接下来 $4T$ 行描述每组数据。    

每组数据的第一行包含一个整数 $N$，表示 $A$ 的项数。

接下来三行，每行 $N$ 个整数 $A_1\sim A_n$，$B_1\sim B_n$，$C_1\sim C_n$，满足 $1\le A_i,B_i,C_i \le 10^9$，且 $C_i$ 两两不同。

## 输出格式

对每组数据，输出两行。第一行包含两个整数 $S,M$，依次表示删去项的代价和与数量；接下来一行 $M$ 个整数，表示删去项在 $A$ 中的的位置，按升序输出。

## 样例

### 样例输入 #1
```
1
6
3 4 4 2 2 3
2 1 1 1 1 2
6 5 4 3 2 1
```
### 样例输出 #1
```
4 3
2 3 6

```
## 提示

【样例说明】

删去 $(A_2,A_3,A_6),(A_1,A_6),(A_2,A_3,A_4,A_5)$ 等都是合法的方案，但$(A_2,A_3,A_6)$ 对应的 $C$ 值的字典序最小。

对于 $100\%$ 的数据，$1\le N\le 700$，$1\le T\le 5$。



---

---
title: "[SDOI2015] 星际战争"
layout: "post"
diff: 省选/NOI-
pid: P3324
tag: ['2015', '二分', '网络流', '山东', 'Special Judge']
---
# [SDOI2015] 星际战争
## 题目描述

$3333$ 年，在银河系的某星球上，X 军团和 Y 军团正在激烈地作战。

在战斗的某一阶段，Y 军团一共派遣了 $N$ 个巨型机器人进攻 X 军团的阵地，其中第 $i$ 个巨型机器人的装甲值为 $A_i$。当一个巨型机器人的装甲值减少到 $0$ 或者以下时，这个巨型机器人就被摧毁了。

X 军团有 $M$ 个激光武器，其中第 $i$ 个激光武器每秒可以削减一个巨型机器人 $B_i$ 的装甲值。激光武器的攻击是连续的。

这种激光武器非常奇怪，一个激光武器只能攻击一些特定的敌人。Y 军团看到自己的巨型机器人被 X 军团一个一个消灭，他们急需下达更多的指令。

为了这个目标，Y 军团需要知道 X 军团最少需要用多长时间才能将 Y 军团的所有巨型机器人摧毁。但是他们不会计算这个问题，因此向你求助。
## 输入格式

题面修理器
第一行，两个整数，N,M。

第二行，N个整数，A1,A2...AN。

第三行，M个整数，B1,B2...BM。

接下来的M行，每行N个整数，这些整数均为0或者1。这部分中的第i行的第j个整数为0表示第i个激光武器不可以攻击第j个巨型机器人，为1表示第i个激光武器可以攻击第j个巨型机器人。


专有名词（用,隔开）

第一行，两个整数，$N,M$。

第二行，$N$ 个整数，$A_1,A_2 \cdots A_N$。

第三行，$M$ 个整数，$B_1,B_2 \cdots B_M$。

接下来的 $M$ 行，每行 $N$ 个整数，这些整数均为 $0$ 或者 $1$。这部分中的第 $i$ 行的第 $j$ 个整数为 $0$ 表示第 $i$ 个激光武器不可以攻击第 $j$ 个巨型机器人，为 $1$ 表示第 $i$ 个激光武器可以攻击第 $j$ 个巨型机器人。

## 输出格式

一行，一个实数，表示 X 军团要摧毁 Y 军团的所有巨型机器人最少需要的时间。输出结果与标准答案的绝对误差不超过 $10^{-3}$ 即视为正确。

## 样例

### 样例输入 #1
```
2 2
3 10
4 6
0 1
1 1
```
### 样例输出 #1
```
1.300000
```
## 提示

**【样例说明1】**

战斗开始后的前 $0.5$ 秒，激光武器 $1$ 攻击 $2$ 号巨型机器人，激光武器 $2$ 攻击 $1$ 号巨型机器人。$1$ 号巨型机器人被完全摧毁，$2$ 号巨型机器人还剩余 $8$ 的装甲值；

接下来的 $0.8$ 秒，激光武器 $1$ 、 $2$ 同时攻击 $2$ 号巨型机器人。$2$ 号巨型机器人被完全摧毁。

**【数据范围】**

对于全部的数据，$1 \le N,M \le 50$，$1 \le A_i \le 10^5$，$1 \le B_i \le 1000$，输入数据保证 X 军团一定能摧毁 Y 军团的所有巨型机器人。

[spj]


---

---
title: "[ZJOI2011] 最小割"
layout: "post"
diff: 省选/NOI-
pid: P3329
tag: ['2011', '网络流', '浙江', '分治', '最小割']
---
# [ZJOI2011] 最小割
## 题目描述

小白在图论课上学到了一个新的概念——最小割，下课后小白在笔记本上写下了如下这段话： 

对于一个图，某个对图中结点的划分将图中所有结点分成两个部分，如果结点 $s$ 和 $t$ 不在同一个部分中，则称这个划分是关于 $s,t$ 的割。对于带权图来说，将所有顶点处在不同部分的边的权值相加所得到的值定义为这个割的容量，而 $s,t$ 的最小割指的是在关于 $s,t$ 的割中容量最小的割。

现给定一张无向图，小白有若干个形如“图中有多少个无序点对的最小割的容量不超过 $x$ ”的疑问，小蓝虽然很想回答这些问题，但小蓝最近忙着挖木块，于是作为小蓝的好友，你又有任务了。
## 输入格式

**本题有多组测试数据。**

第一行一个整数 $T$，表示测试数据组数。

对于每组测试数据，第一行两个整数 $n,m$，表示图的点数和边数。

接下来 $m$ 行，每行三个整数 $u,v,c$ 表示有一条权为 $c$ 的无向边 $(u,v)$。不保证图中无重边。

接下来一行一个整数 $q$ 表示询问的个数，下面 $q$ 行每行一个整数 $x$ 描述一组询问。
## 输出格式

对于每一组测试数据输出 $q$ 行，每行一个整数表示对应询问的答案。对于满足条件的点对 $(p,q)$ 和点对 $(q,p)$ 只应该在答案中统计一次。

**在两组测试数据之间需要输出一行空行。**
## 样例

### 样例输入 #1
```
1
5 0
1
0
```
### 样例输出 #1
```
10
```
## 提示

对于 $100 \%$ 的数据，$1 \leq T \leq 10$，$1 \leq n \leq 150$，$0 \leq m \leq 3000$，$0 \leq x \leq 2^{31}-1$，$0 \leq q \leq 30$。


---

---
title: "火星探险问题 "
layout: "post"
diff: 省选/NOI-
pid: P3356
tag: ['Special Judge', 'O2优化', '网络流与线性规划 24 题']
---
# 火星探险问题 
## 题目描述

火星探险队的登陆舱将在火星表面着陆，登陆舱内有多部障碍物探测车。登陆舱着陆后，探测车将离开登陆舱向先期到达的传送器方向移动。  

探测车在移动中还必须采集岩石标本。每一块岩石标本由最先遇到它的探测车完成采集。每块岩石标本只能被采集一次。岩石标本被采集后，其他探测车可以从原来岩石标本所在处通过。探测车不能通过有障碍的地面。  

本题限定探测车只能从登陆处沿着向南或向东的方向朝传送器移动，而且多个探测车可以在同一时间占据同一位置。如果某个探测车在到达传送器以前不能继续前进，则该车所采集的岩石标本将全部损失。


用一个 $p \times q$ 网格表示登陆舱与传送器之间的位置。登陆舱的位置在 
$(x_1,y_1)$ 处，传送器的位置在 $(x_py_q)$ 处。

$$\begin{bmatrix} (x_1,y_1) & (x_2,y_1) & \dots & (x_{p-1},y_1) & (x_p,y_1) \\ (x_1,y_2) & (x_2,y_2) & \dots & (x_{p-1},y_2) & (x_p,y_2) \\ \dots & \dots & \dots & \dots & \dots \\ (x_1,y_{q-1}) & (x_2,y_{q-1}) & \dots & (x_{p-1},y_{q-1}) & (x_p,y_{q-1}) \\ (x_1,y_q) & (x_2,y_q) & \dots & (x_{p-1},y_q) & (x_p,y_q) \end{bmatrix}$$

给定每个位置的状态，计算探测车的最优移动方案，使到达传送器的探测车的数量最多，而且探测车采集到的岩石标本的数量最多。

## 输入格式

第一行为探测车数 $n$，接下来两行分别为 $p,q$。  

接下来的 $q$ 行是表示登陆舱与传送器之间的位置状态的 $p \times q$ 网格。  
用三种数表示火星表面位置的状态：$0$ 表示平坦无障碍，$1$ 表示障碍，$2$ 表示石块。

## 输出格式

每行包含探测车号和一个移动方向，$0$ 表示向南移动，$1$ 表示向东移动。

## 样例

### 样例输入 #1
```
2
10
8
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 1 0 0 0
0 0 0 1 0 2 0 0 0 0
1 1 0 1 2 0 0 0 0 1
0 1 0 0 2 0 1 1 0 0
0 1 0 1 0 0 1 1 0 0
0 1 2 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0
```
### 样例输出 #1
```
1 1
1 1
1 1
1 1
1 0
1 0
1 1
1 1
1 1
1 1
1 0
1 0
1 1
1 0
1 0
1 0
2 1
2 1
2 1
2 1
2 0
2 0
2 0
2 0
2 1
2 0
2 0
2 1
2 0
2 1
2 1
2 1
```
## 提示

【数据范围】
对于 $100\%$ 的数据，$1 \le n,p,q \le 35$。



---

---
title: "最长k可重线段集问题"
layout: "post"
diff: 省选/NOI-
pid: P3357
tag: ['O2优化', '网络流与线性规划 24 题']
---
# 最长k可重线段集问题
## 题目描述

给定平面 $x-O-y$ 上 $n$ 个开线段组成的集合 $I$，和一个正整数 $k$ 。试设计一个算法，从开线段集合 $I$ 中选取出开线段集合 $S\subseteq I$ ,使得在 $x$ 轴上的任何一点 $p$，$S$ 中与直线 $x=p$ 相交的开线段个数不超过 $k$，且$\sum\limits_{z\in S}|z|$达到最大。这样的集合 $S$ 称为开线段集合 $I$ 的最长  $k$ 可重线段集。$\sum\limits_{z\in S}|z|$ 称为最长  $k$ 可重线段集的长度。

对于任何开线段 $z$，设其断点坐标为 $(x_0,y_0)$ 和 $(x_1,y_1)$，则开线段 $z$ 的长度 $|z|$ 定义为：
$$|z|=\lfloor\sqrt{(x_1-x_0)^2+(y_1-y_0)^2}\rfloor$$

对于给定的开线段集合 $I$ 和正整数 $k$，计算开线段集合 $I$ 的最长 $k$ 可重线段集的长度。

## 输入格式

文件的第一 行有 $2$ 个正整数 $n$ 和 $k$，分别表示开线段的个数和开线段的可重叠数。

接下来的 $n$ 行，每行有 $4$ 个整数，表示开线段的 $2$ 个端点坐标。

## 输出格式

程序运行结束时，输出计算出的最长 $k$ 可重线段集的长度。

## 样例

### 样例输入 #1
```
4 2
1 2 7 3
6 5 8 3
7 8 10 5
9 6 13 9 
```
### 样例输出 #1
```
17
```
## 提示

$1\leq n\leq 500$，$1 \leq k \leq 13$，坐标值在 `int` 范围内。



---

---
title: "最长k可重区间集问题"
layout: "post"
diff: 省选/NOI-
pid: P3358
tag: ['O2优化', '网络流与线性规划 24 题']
---
# 最长k可重区间集问题
## 题目描述

给定实直线 $\text{L}$ 上 $n$ 个开区间组成的集合 $\mathbf{I}$，和一个正整数 $k$，试设计一个算法，从开区间集合 $\mathbf{I}$ 中选取出开区间集合 $\mathbf{S}\subseteq\mathbf{I}$，使得在实直线 $\text{L}$ 上的任意一点 $x$，$\text{S}$ 中包含 $x$ 的开区间个数不超过 $k$，且 $\sum_{z\in\text{S}}\lvert z\rvert$ 达到最大（$\lvert z\rvert$ 表示开区间 $z$ 的长度）。

这样的集合 $\mathbf{S}$ 称为开区间集合 $\mathbf{I}$ 的最长 $k$ 可重区间集。$\sum_{z\in\text{S}}\lvert z\rvert$ 称为最长 $k$ 可重区间集的长度。

对于给定的开区间集合 $\mathbf{I}$ 和正整数 $k$，计算开区间集合 $\mathbf{I}$ 的最长 $k$ 可重区间集的长度。
## 输入格式

输入的第一行有 $2$ 个正整数 $n$ 和 $k$，分别表示开区间的个数和开区间的可重叠数。接下来的 $n$ 行，每行有 $2$ 个整数，表示开区间的左右端点坐标 $l,r$，数据保证 $l<r$。
## 输出格式

输出最长 $k$ 可重区间集的长度。
## 样例

### 样例输入 #1
```
4 2
1 7
6 8
7 10
9 13 
```
### 样例输出 #1
```
15
```
## 提示

对于 $100\%$ 的数据，$1\le n\le 500$，$1\le k\le 3$，$1 \le l < r \le 10^5$。


---

---
title: "拍照"
layout: "post"
diff: 省选/NOI-
pid: P3410
tag: ['网络流']
---
# 拍照
## 题目描述

小 B 有 $N$ 个下属，现小 B 要带着一些下属让别人拍照。

有 $M$ 个人，每个人都愿意付给小B一定钱来和 $N$ 个下属中的一些人进行合影。如果这一些下属没带齐那么就不能拍照，小B也不会得到钱。

注意：带下属不是白带的！！！对于每个下属，如果他带了那么小B需要给他一些钱，保证当他拍照时配合。
## 输入格式

第 $1$ 行有 $2$ 个正整数 $M$ 和 $N$（$0<M,N\le 100$）。接下来的 $M$ 行，每行是一个要求拍照的人的有关数据。第一个数是他同意支付该合影的费用；接着是该合影需要的若干下属的编号，以一个 $0$ 作为行的结束标记。最后一行的 $N$ 个数是带每个下属的费用。
## 输出格式

一个数，表示最大收益。小 B 可以一个人也不带。

## 样例

### 样例输入 #1
```
2 3
10 1 2 0
25 2 3 0
5 6 7
```
### 样例输出 #1
```
17
```
## 提示

对于 $10\%$ 的数据每个人都要求让全部 $N$ 个人合影。

对于 $30\%$ 的数据 $N\le15,M\le 15$。

另有 $10\%$ 的数据答案为 $0$。

对于 $50\%$ 的数据 $N\le 40,M\le 40$。

另有 $10\%$ 的数据每个人只愿意拍一个人。

对于 $100\%$ 的数据 $M,N\le100$，费用是 $[1,5\times 10^8]$ 间的整数。


---

---
title: "[POI 2005] KOS-Dicing"
layout: "post"
diff: 省选/NOI-
pid: P3425
tag: ['2005', 'POI（波兰）', '网络流', 'Special Judge', '生成树', '最小割']
---
# [POI 2005] KOS-Dicing
## 题目描述

Dicing is a two-player game and its outcome is fully random. Lately its popularity increases all over Byteotia. There is even a special club for dicing amateurs in the capital city of Byteotia. The club patrons take their time talking to each other and playing their favourite game with a randomly chosen opponent every once in a while. Everyone who wins the most games one day gains the title of the lucky chap. Sometimes it happens that the night at the club is a quiet one and only few games are played. It is a time when even one win can make you a lucky chap.

Once upon a time a most unlucky fellow, Byteasar, won the glorious title. He was so deeply shocked that he completely forgot how many games he had won. Now he is wondering how good his luck was and whether fortune finally smiled upon him - perhaps his luck changed for good? He knows exactly how many games and between whom were played that lucky night. However, he does not know the results. Byteasar desires to find out what is the smallest number of wins that could provide the title of the lucky chap. Be a good fellow and help him satisfy his curiosity!

TaskWrite a programme that:

for each game played reads from the standard input the pair of players who competed in it.

finds the smallest number $k$, such that a set of games' outcomes exists in which each player wins $k$ games at the most,writes the number $k$ and the results of games in the found set to the standard output.

Dicing 是一个两人玩的游戏,这个游戏在Byteotia非常流行. 甚至人们专门成立了这个游戏的一个俱乐部. 俱乐部的人时常在一起玩这个游戏然后评选出玩得最好的人.现在有一个非常不走运的家伙,他想成为那个玩的最好的人,他现在知道了所有比赛的安排,他想知道,在最好的情况下,他最少只需要赢几场就可以赢得冠军,即他想知道比赛以后赢的最多的那个家伙最少会赢多少场.

## 输入格式

In the first line of the standard input there is a pair of integers $n$ and $m$ separated by a single space, $1\le n\le 10000$, $0\le m\le 10000$; $n$ denotes the number of players, while $m$ is the number of games. The players are numbered from $1$ to $n$. In the following $m$ lines there are pairs of players' numbers depicting the sequence of games, separated by single spaces. One pair may occur many times in the sequence.

## 输出格式

The first line of the standard output should contain the determined number $k$. For each pair of players' numbers $a$, $b$ specified in the $i$'th line of the input, in the $i$'th line of the output the number $1$ should be written if the player no. $a$ wins against player no. $b$ in the found set of outcomes, or $0$ otherwise.

## 样例

### 样例输入 #1
```
4 4
1 2
1 3
1 4
1 2
```
### 样例输出 #1
```
1
0
0
0
1
```
## 题目翻译

描述

掷骰子是一种双人游戏，它的结果是完全随机的。最近它在整个Byteotia变得非常流行。在Byteotia的首都甚至有一个特别的掷骰子业余爱好者俱乐部。俱乐部的老主顾们花时间互相聊天并每隔一阵子就和一个随机选择的对手玩这他们最喜欢的游戏。一天中赢得最多游戏的人会得到“幸运者”头衔。有时晚上俱乐部很安静，只有很少的比赛。这是哪怕赢一场也能获得“幸运者”头衔的时间。

很久很久以前有一个很不走运的人，叫Byteasar，赢得了这个光荣的头衔。他被深深地震惊了以至于完全忘了他已经赢了多少场。现在他想知道他有多幸运，以及幸运之神是否最终会向他微笑——也许他的运气会变好？他确切地知道在那个幸运的晚上有多少场游戏以及是谁玩的。然而，他不知道结果。Byteasar希望查明至少要赢几场才能获得“幸运者”头衔。做个好人，帮他满足他的好奇心吧！

任务：写一个程序：

对于每场游戏从stdin读入这场游戏的一对玩家 找到最小的数k，使得存在一个游戏结果的集合，其中赢最多的玩家赢了k场。向stdout输出数k和找到的集合中游戏的结果

输入

stdin的第一行有一个一对由一个空格分开整数n和m (1 <= n, m <= 10000) 。n表示玩家数，m表示游戏数。玩家从1到n编号。在接下来的m行中有每场游戏的一对玩家的编号，由一个空格分开，描述了游戏的序列。一对玩家可能会在这个序列中多次出现。

输出

stdout的第一行应该包含一个确定的数k。对于在输入的第i行指定的一对玩家a, b，如果在找到的结果集合中a胜过b，则在输出的第i行输出1, 否则输出0.

感谢 @zyt1253679098  提供的翻译。


---

---
title: "[POI 2010] MOS-Bridges"
layout: "post"
diff: 省选/NOI-
pid: P3511
tag: ['2010', '二分', 'POI（波兰）', '网络流', 'Special Judge', '欧拉回路']
---
# [POI 2010] MOS-Bridges
## 题目描述

San Bytecisco is a beautifully situated coastal town.

It consists of ![](http://main.edu.pl/images/OI17/mos-en-tex.1.png) small, yet densely populated islands,  numbered from ![](http://main.edu.pl/images/OI17/mos-en-tex.2.png) to ![](http://main.edu.pl/images/OI17/mos-en-tex.3.png).

Certain islands are connected with bridges, used for (bidirectional)  road traffic.

Each pair of islands can be connected with at most one bridge.

The islands are connected in such a way that every island can be reached  from every other by using the bridges only.

Byteasar and Bytie are going for a bike trip in San Bytecisco.

The will start their ride at the island no. 1.

They intend to visit every island, while passing along every bridge once  and ending the trip where it began, i.e., the island no. 1.

Being quite seasoned riders, they expect some serious trouble from... the wind!

After all, it is very windy along the coast, and especially so on the bridges between  the islands. Obviously, depending on its speed and direction, the wind makes it  hard to cross the bridge in different extent for either direction.

For simplicity we will assume for every bridge and direction of crossing,  the opposing wind speed is constant.

Help Byteasar and Bytie to find a route as they desire that will in addition  be the least tiresome. Byteasar and Bytie agreed on the maximum opposing wind speed as  a measure of a route's tiresomeness.



## 输入格式

In the first line of the standard input there are two integers separated by a single space: $n$ and $m$ ($2 \le n \le 1000$, $1 \le m \le 2000$), denoting the number of islands and the number of bridges in San Bytecisco respectively. The islands are numbered from 1 to n, while the bridges from 1 to m. The following  lines specify the bridges. The line no.($n+1$)  contains four integers $a_i,b_i,l_i,p_i$ ($1\le l_i,p_i \le 1000$), separated by single spaces. These denote that the bridge no. $i$ connects the islands no. $a$ and $b$. The opposing wind speeds are  when one goes moves from  to , and  if one goes from $a$ to $b$.
## 输出格式

If there is no route satisfying the requirements of the daring two riders,   the first and only line of the standard output should hold the word NIE   (no in Polish).

Otherwise, the output should have two lines, specifying the least tiresome route   over San Bytecisco.

The first line should hold the maximum opposing wind speed for that route, i.e.,   the number we wish to minimize.

The second line should hold ![](http://main.edu.pl/images/OI17/mos-en-tex.28.png) integers, separated by single spaces, giving   the numbers of successive bridges one crosses on the least tiresome route.

Should there be more than one least tiresome route, your program can pick one   arbitrarily.

## 样例

### 样例输入 #1
```
4 4
1 2 2 4
2 3 3 4
3 4 4 4
4 1 5 4
```
### 样例输出 #1
```
4
4 3 2 1
```
## 提示

$2 \le n \le 1000$，$1 \le m \le 2000$，$1 \le a_i,b_i \le n$，$a_i \neq b_i$，$1 \le l_i,p_i \le 1000$

## 题目翻译

给定一个图，边有权值且正着走和逆着走有不同权值，在这个图上求一条最大边权最小的欧拉回路，从点  $1$ 出发，要求输出方案。

第一行包括两个整数  $n$ 和  $m$，分别代表点的个数和边的个数。接下来  $m$ 行每行包括  $4$ 个整数  $a,b,l,p$，分别代表边的两个端点和正着走的权值和逆着走的权值。

如果没有符合要求的路径输出 `NIE`，否则输出两行。第一行一个整数表示最小的权值，第二行  $m$ 个整数表示依次经过的边的编号。

Translated by @Schwarzkopf_Henkal 


---

---
title: "csh和zzy的战争"
layout: "post"
diff: 省选/NOI-
pid: P3652
tag: ['网络流', '洛谷原创']
---
# csh和zzy的战争
## 题目背景

（背景~~有点~~长，你可以选择读完，也可以选择跳过。）

公元 2040 年，csh 和 zzy 在丑国蛙谷展开了关于非线性配微分方程的正确性与否的相关辩论，史称第四次数学危机。两个人近千页的非人类学术性论文，使整个世界没有其他人听得懂他们在说什么，于是，以 csh 为首的 A 派科学家和以 zzy 为首的 B 派科学家展开了在多次对抗无果之后开始使用武装革命解决，进而引发了全球性的第三次世界大战。作为战争中立派的居润国不想卷入任何一方的斗争，只想喝完手中的咖啡，然而两方元首在多次对抛出橄榄枝无果之后，对居润国提出了一个要求：解决他们在战争中的运送物资问题，当然这个问题早就在 $10^0$ s 内被他们解决，但是居润国却不知道怎么办，而且也不能报上错误的答案，于是就求助了聪明的你们。
## 题目描述

现在有 $n$ 个货物发源地，里面是一些待运送的货物。前方有 $m$ 个中转小岛，而你的目的是将所有货物运到战争前沿的军事基地，其运送规则如下：

1. 小岛只能由特定的货物发源地发货，其中只有几个指定的小岛可以向军事基地发货。
2. 小岛与小岛之间有 $e$ 条航道，每条航道上有一个权值 $v$ 代表这条道路开通的代价，而两个小岛之间开通货运的代价 $K$ 是两个小岛之间的最短路径长度。
3. 每个小岛上同时最多不能超过 $w$ 个货物。
4. 每个小岛一次性至多对外运输 $d$ 个货物，小岛对每个目的地至多送货一次。
5. 有 $x$ 个特殊货物发源地（不包含在 $n$ 内）会运送 csh 和 zzy 两个人的一些私人的货物，这些货物会被任何一个小岛无条件接受和送出，即不受 3，4 法则的影响。
6. 整条航路的开发费用为每对小岛开通费用 $K$ 中的最大值 $V$。

请你寻找一个最小的 $V$ 使得所有货物都能按照要求运送到军事基地。
## 输入格式

第一行 $n$，$m$，$x$，$e$，分别表示货物发源地数目，小岛中转站数目，特殊货物发源地数目和航道数目，货物发源地和特殊货物发源地依次标号为 $1$，$2$，$ \dots $，$n+x$。

第二行是 $n+x$ 个数 $a_i$，分别每个货物发源地待发送的货物数量。

第三行是 $m$ 个数，分别表示小岛的限制存货量 $w$。

第四行也是 $m$ 个数，分别表示小岛的限制出货量 $d$。

接下来 $m$ 行，每行开头是一个数 $k$ ，表示有 $k$ 个货物发源地（包括特殊货物发源地）与小岛相连，然后是 $k$ 个数，分别表示货物发源地的编号，最后一个数表示小岛是否与军事基地相连，是则为$1$，否则为$0$。

接下来 $e$ 行，每行是三个数 $u$，$v$，$p$ 表示小岛 $u$，$v$ 之间航道的权值为 $p$。
## 输出格式

一个整数 $V$ ，表示使得所有货物都能按照要求运送到军事基地最小开通费用。
## 样例

### 样例输入 #1
```
2 3 1 1
2 2 2
4 4 4
2 1 1
1 1 1
1 2 1
1 3 1
2 3 4
```
### 样例输出 #1
```
4
```
## 提示

对于 $100\%$ 的数据， $n \le 3 \times 10^2$，$e \le 10^3$。

几个提示：[https://www.luogu.com.cn/discuss/47710](https://www.luogu.com.cn/discuss/47710)。


---

---
title: "[NOI2008] 志愿者招募"
layout: "post"
diff: 省选/NOI-
pid: P3980
tag: ['2008', 'NOI', '网络流', '图论建模', '线性规划']
---
# [NOI2008] 志愿者招募
## 题目描述

申奥成功后，布布经过不懈努力，终于成为奥组委下属公司人力资源部门的主管。布布刚上任就遇到了一个难题：为即将启动的奥运新项目招募一批短期志愿者。经过估算，这个项目需要 $n$ 天才能完成，其中第 $i$ 天至少需要 $a_i$ 个人。布布通过了解得知，一共有 $m$ 类志愿者可以招募。其中第 $i$ 类可以从第 $s_i$ 天工作到第 $t_i$ 天，招募费用是每人 $c_i$ 元。新官上任三把火，为了出色地完成自己的工作，布布希望用尽量少的费用招募足够的志愿者，但这并不是他的特长！于是布布找到了你，希望你帮他设计一种最优的招募方案。
## 输入格式

第一行包含两个整数 $n,m$，表示完成项目的天数和可以招募的志愿者的种类。接下来的一行中包含 $n$ 个非负整数，表示每天至少需要的志愿者人数。 接下来的 $m$ 行中每行包含三个整数 $s_i, t_i, c_i$，含义如上文所述。为了方便起见，我们可以认为每类志愿者的数量都是无限多的。保证存在可行的招募方案。
## 输出格式

仅包含一个整数，表示你所设计的最优方案的总费用。

## 样例

### 样例输入 #1
```
3 3
2 3 4
1 2 2
2 3 5
3 3 2
```
### 样例输出 #1
```
14
```
## 提示

$1\leq n\leq 1000$，$1\leq m\leq 10000$，题目中其他所涉及的数据均不超过 $2^{31}-1$。


---

---
title: "[ICPC-Beijing 2006] 狼抓兔子"
layout: "post"
diff: 省选/NOI-
pid: P4001
tag: ['2006', '网络流', '北京', '最小割', 'ICPC']
---
# [ICPC-Beijing 2006] 狼抓兔子
## 题目描述

现在小朋友们最喜欢的"喜羊羊与灰太狼"。话说灰太狼抓羊不到，但抓兔子还是比较在行的，而且现在的兔子还比较笨，它们只有两个窝，现在你做为狼王，面对下面这样一个网格的地形：

 ![](https://cdn.luogu.com.cn/upload/pic/11942.png) 

左上角点为 $(1,1)$，右下角点为 $(N,M)$（上图中 $N=3$，$M=4$）。有以下三种类型的道路：

1. $(x,y)\rightleftharpoons(x+1,y)$

2. $(x,y)\rightleftharpoons(x,y+1)$

3. $(x,y)\rightleftharpoons(x+1,y+1)$

道路上的权值表示这条路上最多能够通过的兔子数，道路是无向的。左上角和右下角为兔子的两个窝，开始时所有的兔子都聚集在左上角 $(1,1)$ 的窝里，现在它们要跑到右下角 $(N,M)$ 的窝中去，狼王开始伏击这些兔子。当然为了保险起见，如果一条道路上最多通过的兔子数为 $K$，狼王需要安排同样数量的 $K$ 只狼，才能完全封锁这条道路，你需要帮助狼王安排一个伏击方案，使得在将兔子一网打尽的前提下，参与的狼的数量要最小。因为狼还要去找喜羊羊麻烦。

## 输入格式

第一行两个整数 $N,M$，表示网格的大小。

接下来分三部分。

第一部分共 $N$ 行，每行 $M-1$ 个数，表示横向道路的权值。

第二部分共 $N-1$ 行，每行 $M$ 个数，表示纵向道路的权值。

第三部分共 $N-1$ 行，每行 $M-1$ 个数，表示斜向道路的权值。
## 输出格式

输出一个整数，表示参与伏击的狼的最小数量。

## 样例

### 样例输入 #1
```
3 4
5 6 4
4 3 1
7 5 3
5 6 7 8
8 7 6 5
5 5 5
6 6 6
```
### 样例输出 #1
```
14
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $3 \leq N,M \leq 1000$，所有道路的权值均为不超过 $10^6$ 的正整数。


---

---
title: "汽车加油行驶问题"
layout: "post"
diff: 省选/NOI-
pid: P4009
tag: ['图论', '网络流', 'O2优化', '最短路', '费用流', '网络流与线性规划 24 题']
---
# 汽车加油行驶问题
## 题目描述

给定一个 $N \times N$ 的方形网格，设其左上角为起点◎，坐标$(1,1)$，$X$ 轴向右为正， $Y$ 轴向下为正，每个方格边长为 $1$ ，如图所示。



 ![](https://cdn.luogu.com.cn/upload/pic/12156.png) 

一辆汽车从起点◎出发驶向右下角终点▲，其坐标为 $(N,N)$。


在若干个网格交叉点处，设置了油库，可供汽车在行驶途中加油。汽车在行驶过程中应遵守如下规则:


1. 汽车只能沿网格边行驶，装满油后能行驶 $K$ 条网格边。出发时汽车已装满油，在起点与终点处不设油库。

1. 汽车经过一条网格边时，若其 $X$ 坐标或 $Y$ 坐标减小，则应付费用 $B$ ，否则免付费用。

1. 汽车在行驶过程中遇油库则应加满油并付加油费用 $A$。

1. 在需要时可在网格点处增设油库，并付增设油库费用 $C$(不含加油费用$A$ )。

1. $N,K,A,B,C$ 均为正整数， 且满足约束: $2\leq N\leq 100,2 \leq K \leq 10$。


设计一个算法，求出汽车从起点出发到达终点所付的最小费用。

## 输入格式

文件的第一行是 $N,K,A,B,C$ 的值。


第二行起是一个$N\times N$ 的 $0-1$ 方阵,每行 $N$ 个值,至 $N+1$ 行结束。


方阵的第 $i$ 行第 $j$ 列处的值为 $1$ 表示在网格交叉点 $(i,j)$ 处设置了一个油库,为 $0$ 时表示未设油库。各行相邻两个数以空格分隔。

## 输出格式

程序运行结束时,输出最小费用。

## 样例

### 样例输入 #1
```
9 3 2 3 6
0 0 0 0 1 0 0 0 0
0 0 0 1 0 1 1 0 0
1 0 1 0 0 0 0 1 0
0 0 0 0 0 1 0 0 1
1 0 0 1 0 0 1 0 0
0 1 0 0 0 0 0 1 0
0 0 0 0 1 0 0 0 1
1 0 0 1 0 0 0 1 0
0 1 0 0 0 0 0 0 0
```
### 样例输出 #1
```
12
```
## 提示

$2 \leq n \leq 100,2 \leq k \leq 10$



---

---
title: "深海机器人问题"
layout: "post"
diff: 省选/NOI-
pid: P4012
tag: ['图论建模', '费用流', '网络流与线性规划 24 题']
---
# 深海机器人问题
## 题目描述

深海资源考察探险队的潜艇将到达深海的海底进行科学考察。


潜艇内有多个深海机器人。潜艇到达深海海底后，深海机器人将离开潜艇向预定目标移动。


深海机器人在移动中还必须沿途采集海底生物标本。沿途生物标本由最先遇到它的深海机器人完成采集。


每条预定路径上的生物标本的价值是已知的，而且生物标本只能被采集一次。


本题限定深海机器人只能从其出发位置沿着向北或向东的方向移动，而且多个深海机器人可以在同一时间占据同一位置。


用一个 $P\times Q$ 网格表示深海机器人的可移动位置。西南角的坐标为 $(0,0)$，东北角的坐标为 $(Q,P)$ 。



 ![](https://cdn.luogu.com.cn/upload/pic/12215.png) 

给定每个深海机器人的出发位置和目标位置，以及每条网格边上生物标本的价值。


计算深海机器人的最优移动方案， 使深海机器人到达目的地后，采集到的生物标本的总价值最高。


## 输入格式

文件的第 $1$ 行为深海机器人的出发位置数 $a$,和目的地数 $b$ 。


第 $2$ 行为 $P$ 和 $Q$ 的值。


接下来的 $P+1$ 行,每行有 $Q$ 个正整数,表示向东移动路径上生物标本的价值,行数据依从南到北方向排列。


再接下来的 $Q+1$ 行,每行有 $P$ 个正整数,表示向北移动路径上生物标本的价值,行数据依从西到东方向排列。


接下来的 $a$ 行，每行有三个正整数 $k,x,y$,表示有 $k$ 个深海机器人从 $(y,x)$ 位置坐标出发。


再接下来的 $b$ 行，每行有三个正整数 $r,x,y$ ,表示有 $r$ 个深海机器人可选择 $(y,x)$ 位置坐标作为目的地。

## 输出格式

输出采集到的生物标本的最高总价值.

## 样例

### 样例输入 #1
```
1 1
2 2
1 2
3 4
5 6
7 2
8 10
9 3
2 0 0
2 2 2
```
### 样例输出 #1
```
42
```
## 提示

$1\leq P,Q\leq15$


$1\leq a\leq 4$


$1\leq b\leq 6$



---

---
title: "数字梯形问题"
layout: "post"
diff: 省选/NOI-
pid: P4013
tag: ['O2优化', '图论建模', '费用流', '网络流与线性规划 24 题']
---
# 数字梯形问题
## 题目描述

给定一个由 $n$ 行数字组成的数字梯形如下图所示。



 ![](https://cdn.luogu.com.cn/upload/pic/12216.png) 

梯形的第一行有 $m$ 个数字。从梯形的顶部的 $m$ 个数字开始，在每个数字处可以沿左下或右下方向移动，形成一条从梯形的顶至底的路径。


分别遵守以下规则：


1. 从梯形的顶至底的 $m$ 条路径互不相交；

1. 从梯形的顶至底的 $m$ 条路径仅在数字结点处相交；

1. 从梯形的顶至底的 $m$  条路径允许在数字结点相交或边相交。

## 输入格式

第 $1$ 行中有 $2$ 个正整数 $m$ 和 $n$，分别表示数字梯形的第一行有 $m$ 个数字，共有 $n$ 行。接下来的 $n$ 行是数字梯形中各行的数字。

第 $1$ 行有 $m$ 个数字，第 $2$ 行有 $m+1$ 个数字，以此类推。

## 输出格式

将按照规则 $1$，规则 $2$，和规则 $3$ 计算出的最大数字总和并输出，每行一个最大总和。

## 样例

### 样例输入 #1
```
2 5
2 3
3 4 5
9 10 9 1
1 1 10 1 1
1 1 10 12 1 1
```
### 样例输出 #1
```
66
75
77
```
## 提示

$1\leq m,n \leq 20$



---

---
title: "[AHOI2014/JSOI2014] 支线剧情"
layout: "post"
diff: 省选/NOI-
pid: P4043
tag: ['2014', '各省省选', '网络流', '江苏', '安徽', '上下界网络流', '费用流']
---
# [AHOI2014/JSOI2014] 支线剧情
## 题目背景

宅男 JYY 非常喜欢玩 RPG 游戏，比如仙剑，轩辕剑等等。不过 JYY 喜欢的并不是战斗场景，而是类似电视剧一般的充满恩怨情仇的剧情。这些游戏往往都有很多的支线剧情，现在 JYY 想花费最少的时间看完所有的支线剧情。
## 题目描述

JYY 现在所玩的 RPG 游戏中，一共有 $N$ 个剧情点，由 $1$ 到 $N$ 编号，第 $i$ 个剧情点可以根据 JYY 的不同的选择，而经过不同的支线剧情，前往 $K_i$ 种不同的新的剧情点。当然如果为 $0$，则说明 $i$ 号剧情点是游戏的一个结局了。

JYY 观看一个支线剧情需要一定的时间。JYY 一开始处在 $1$ 号剧情点，也就是游戏的开始。显然任何一个剧情点都是从 $1$ 号剧情点可达的。此外，随着游戏的进行，剧情是不可逆的。所以游戏保证从任意剧情点出发，都不能再回到这个剧情点。由于 JYY 过度使用修改器，导致游戏的“存档”和“读档”功能损坏了，

所以 JYY 要想回到之前的剧情点，唯一的方法就是退出当前游戏，并开始新的游戏，也就是回到 $1$ 号剧情点。JYY 可以在任何时刻退出游戏并重新开始。不断开始新的游戏重复观看已经看过的剧情是很痛苦，JYY 希望花费最少的时间，看完所有不同的支线剧情。
## 输入格式

输入一行包含一个正整数 $N$。

接下来 $N$ 行，第 $i$ 行为 $i$ 号剧情点的信息；

第一个整数为 $K_i$，接下来 $K_i$ 个整数对，$b_{i,j}$ 和 $t_{i,j}$，表示从剧情点 $i$ 可以前往剧情点 $b_{i,j}$，并且观看这段支线剧情需要花费 $t_{i,j}$ 的时间。
## 输出格式

输出一行包含一个整数，表示 JYY 看完所有支线剧情所需要的最少时间。
## 样例

### 样例输入 #1
```
6
2 2 1 3 2
2 4 3 5 4
2 5 5 6 6
0
0
0
```
### 样例输出 #1
```
24
```
## 提示

### 样例解释

JYY 需要重新开始 $3$ 次游戏，加上一开始的一次游戏，$4$ 次游戏的进程是：

- $1 \to 2 \to 4$；
- $1 \to 2 \to 5$；
- $1 \to 3 \to 5$；
- $1 \to 3 \to 6$。

对于 $100\%$ 的数据满足 $N \le 300$，$0 \le K_i \le 50$，$1 \le T_{i,j} \le 300$，$\sum K_i \le 5000$。


---

---
title: "[JSOI2009] 游戏"
layout: "post"
diff: 省选/NOI-
pid: P4055
tag: ['2009', '各省省选', '网络流', '江苏', '二分图']
---
# [JSOI2009] 游戏
## 题目描述

小 AA 和小 YY 得到了《喜羊羊和灰太狼》的电影票，都很想去观看，但是电影票只有一张，于是他们用智力游戏决定胜负，赢得游戏的人可以获得电影票。

在 $N \times M$ 的迷宫中有一个棋子，小 AA 首先任意选择棋子放置的位置。然后，小 YY 和小 AA 轮流将棋子移动到相邻的格子里。游戏的规则规定，在一次游戏中，同一个格子不能进入两次，且不能将棋子移动到某些格子中去。当玩家无法继续移动棋子时，游戏结束，最后一个移动棋子的玩家赢得了游戏。

例如下图所示的迷宫，迷宫中 `.` 表示棋子可以经过的格子，而 `#` 表示棋子不可以经过的格子：

```cpp
                                 .##
                                 ...
                                 #.# 
```                                 
若小 AA 将棋子放置在 $(1,1)$，则小 AA 则无论如何都无法赢得游戏。

而若小 AA 将棋子放置在 $(3,2)$ 或 $(2,3)$，则小 AA 能够赢得游戏。例如，小 AA 将棋子放置在 $(3,2)$，小 YY 只能将它移动到 $(2,2)$，此时小 AA 再将棋子移动到 $(2,3)$，就赢得了游戏。

小 AA 和小 YY 都是绝顶聪明的小朋友，且从不失误。小 AA 到底能不能赢得这场游戏，从而得到珍贵的电影票呢？
## 输入格式

输入数据首先输入两个整数 $N,M$，表示了迷宫的边长。

接下来 $N$ 行，每行 $M$ 个字符，描述了迷宫。

## 输出格式

若小 AA 能够赢得游戏，则输出一行 `WIN`，然后输出所有可以赢得游戏的起始位置，按行优先顺序输出，每行一个。

否则输出一行 `LOSE`。

## 样例

### 样例输入 #1
```
3 3
.##
...
#.#
```
### 样例输出 #1
```
WIN
2 3
3 2
```
## 提示

- 对 $30\%$ 的数据，有 $n,m \leq 5$；
- 对 $100\%$ 的数据，有 $1 \leq n,m \leq 100$。



---

---
title: "[SDOI2016] 数字配对"
layout: "post"
diff: 省选/NOI-
pid: P4068
tag: ['贪心', '2016', '各省省选', '网络流', '山东', '二分图', '素数判断,质数,筛法']
---
# [SDOI2016] 数字配对
## 题目描述

有 $n$ 种数字，第 $i$ 种数字是 $a_i$、有 $b_i$ 个，权值是 $c_i$。

若两个数字 $a_i$、$a_j$ 满足，$a_i$ 是 $a_j$ 的倍数，且 $a_i/a_j$ 是一个质数，

那么这两个数字可以配对，并获得 $c_i \times c_j$ 的价值。

一个数字只能参与一次配对，可以不参与配对。

在获得的价值总和不小于 $0$ 的前提下，求最多进行多少次配对。
## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n$。

第三行 $n$ 个整数 $b_1,b_2,\cdots,b_n$。

第四行 $n$ 个整数 $c_1,c_2,\cdots,c_n$。
## 输出格式

一行一个数，最多进行多少次配对。
## 样例

### 样例输入 #1
```
3
2 4 8
2 200 7
-1 -2 1

```
### 样例输出 #1
```
4
```
## 提示

测试点 $1 \sim 3$： $n \leq 10 $， $a_i \leq 10 ^ 9 $ ， $b_i = 1 $，$ | c_i | \leq 10 ^ 5$；   

测试点 $4 \sim 5$： $n \leq 200 $， $a_i \leq 10 ^ 9 $ ， $b_i \leq 10 ^ 5  $，$c_i = 0$；

测试点 $6 \sim 10$： $n \leq 200 $， $a_i \leq 10 ^ 9 $ ， $b_i \leq 10 ^ 5$ ，$ | c_i | \leq 10 ^ 5$。


---

---
title: "[CQOI2016] 不同的最小割"
layout: "post"
diff: 省选/NOI-
pid: P4123
tag: ['2016', '重庆', '各省省选', '网络流', '分治', '最小割']
---
# [CQOI2016] 不同的最小割
## 题目描述

学过图论的同学都知道最小割的概念：对于一个图，某个对图中结点的划分将图中所有结点分成两个部分，如果结点 $s,t$ 不在同一个部分中，则称这个划分是关于 $s,t$ 的割。对于带权图来说，将所有顶点处在不同部分的边的权值相加所得到的值定义为这个割的容量，而 $s,t$ 的最小割指的是在关于 $s,t$ 的割中容量最小的割。

而对冲刺 NOI 竞赛的选手而言，求带权图中两点的最小割已经不是什么难事了。我们可以把视野放宽，考虑有 $N$ 个点的无向连通图中所有点对的最小割的容量，共能得到 $N(N-1)/2$ 个数值。这些数值中互不相同的有多少个呢？这似乎是个有趣的问题。
## 输入格式

第一行包含两个数 $N,M$，表示点数和边数。

接下来 $M$ 行，每行三个数 $u,v,w$，表示点 $u$ 和点 $v$ (从 $1$ 开始标号) 之间有一条权值是 $w$ 的边。
## 输出格式

第一行为一个整数，表示不同的最小割容量的个数。
## 样例

### 样例输入 #1
```
4 4
1 2 3
1 3 6
2 4 5
3 4 4
```
### 样例输出 #1
```
3
```
## 提示

$1\leq N\leq 850,1\leq M\leq 8500,1\leq w\leq 100000$。


---

---
title: "[NOI2006] 最大获利"
layout: "post"
diff: 省选/NOI-
pid: P4174
tag: ['2006', 'NOI', '网络流', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [NOI2006] 最大获利
## 题目描述

新的技术正冲击着手机通讯市场，对于各大运营商来说，这既是机遇，更是挑战。THU 集团旗下的 CS&T 通讯公司在新一代通讯技术血战的前夜，需要做太多的准备工作，仅就站址选择一项，就需要完成前期市场研究、站址勘测、最优化等项目。

在前期市场调查和站址勘测之后，公司得到了一共 $N$ 个可以作为通讯信号中转站的地址，而由于这些地址的地理位置差异，在不同的地方建造通讯中转站需要投入的成本也是不一样的，所幸在前期调查之后这些都是已知数据：建立第 $i$ 个通讯中转站需要的成本为 $P_i$（$1 \leq i \leq N$）。

另外公司调查得出了所有期望中的用户群，一共 $M$ 个。关于第 $i$ 个用户群的信息概括为 $A_i$，$B_i$ 和 $C_i$ ：这些用户会使用中转站 $A_i$ 和中转站 $B_i$ 进行通讯，公司可以获益 $C_i$。（$1 \leq i \leq M$，$1 \leq A_i, B_i \leq N$）

THU 集团的 CS&T 公司可以有选择的建立一些中转站（投入成本），为一些用户提供服务并获得收益（获益之和）。那么如何选择最终建立的中转站才能让公司的净获利最大呢？（净获利 = 获益之和 – 投入成本之和）

## 输入格式

输入文件中第一行有两个正整数 $N$ 和 $M$。

第二行中有 $N$ 个整数描述每一个通讯中转站的建立成本，依次为 $P_1 , P_2 , …,P_N$。

以下 $M$ 行，第 $i + 2$ 行的三个数 $A_i , B_i$ 和 $C_i$ 描述第 $i$ 个用户群的信息。

所有变量的含义可以参见题目描述。

## 输出格式

你的程序只要向输出文件输出一个整数，表示公司可以得到的最大净获利。

## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 2 3
2 3 4
1 3 3
1 4 2
4 5 3
```
### 样例输出 #1
```
4
```
## 提示

样例：选择建立 $1,2,3$ 号中转站，则需要投入成本 $6$，获利为 $10$，因此得到最大收益 $4$。

$100\%$ 的数据中：$N \leq 5\,000$，$M \leq50\,000$，$0 \leq C_i \leq 100$，$0 \leq P_i  \leq 100$。



---

---
title: "土地划分"
layout: "post"
diff: 省选/NOI-
pid: P4210
tag: ['网络流']
---
# 土地划分
## 题目描述

$Y$ 国有 $N$ 座城市，并且有 $M$ 条双向公路将这些城市连接起来，并且任意两个城市至少有一条路径可以互达。$Y$ 国的国王去世之后，他的两个儿子 A 和 B 都想成为新的国王，但他们都想让这个国家更加安定，不会用武力解决问题。于是他们想将这个国家分成两个小国家 A 国和 B 国。现在，A 拥有 $1$ 号城市，B 拥有 $N$ 号城市，其他的城市还尚未确定归属哪边（划分之后的国家内部城市可以不连通）。由于大家都想让国家变得更好，而某些城市的人民愿意国王的 A 儿子作为他们的领袖，而某些城市更看好 B，而为了交通的便捷，如果划分后的公路连接两个同一个国家的城市，那么更利于城市之间的交流。于是大臣们设计了一种对土地划分的评分机制，具体如下：对于城市 $i$，如果它划分给 A 国，将得到 $\mathit{VA}_i$ 的得分；划分给 B 国，将得到 $\mathit{VB}_i$ 的得分。对于一条公路 $i$，如果它连接两个 A 国的城市，将得到 $\mathit{EA}_i$ 的得分；连接两个 B 国的城市，将得到 $\mathit{EB}_i$ 的得分；否则，这条公路将失去意义，将扣除 $\mathit{EC}_i$ 的得分。现请你找到最优的土地划分，使得这种它的评分最高。
## 输入格式

第一行包含两个整数 $N$，$M$，含义如问题描述所示。接下来一行 $N-2$ 个非负整数，表示 $\mathit{VA}_2,\mathit{VA}_3,\cdots,\mathit{VA}_{N-1}$。接下来一行 $N-2$ 个非负整数，表示 $\mathit{VB}_2,\mathit{VB}_3,\cdots,\mathit{VB}_{N-1}$。接下来 $M$ 行，每行五个非负整数描述一条公路：$X,Y,\mathit{EA}_i,\mathit{EB}_i,\mathit{EC}_i$，含义如问题描述所示。
## 输出格式

输出有且仅有一个整数，表示最高评分。
## 样例

### 样例输入 #1
```
3 3 
8 
9 
1 2 2 6 2 
2 3 8 5 7 
1 3 9 4 1
```
### 样例输出 #1
```
11
```
## 提示

对于全部数据，$n \le 10^4$，$m \le 4\times 10^4$。

保证运算过程中及最终结果不超过 $32$ 位带符号整数类型的表示范围。



---

---
title: "[SCOI2015] 小凸玩矩阵"
layout: "post"
diff: 省选/NOI-
pid: P4251
tag: ['2015', '四川', '二分', '各省省选', '网络流', '二分图']
---
# [SCOI2015] 小凸玩矩阵
## 题目描述

小凸和小方是好朋友，小方给了小凸一个 $n$ × $m$ $(n \leq m)$ 的矩阵 $A$，并且要求小凸从矩阵中选出 $n$ 个数，其中任意两个数都不能在同一行或者同一列。现在小凸想知道，选出的 $n$ 个数中第 $k$ 大的数的最小值是多少。
## 输入格式

第 $1$ 行读入 $3$ 个整数 $n, m, k$。

接下来 $n$ 行，每一行有 $m$ 个数字，第 $i$ 行第 $j$ 个数字代表矩阵中第 $i$ 行第 $j$ 列的元素 $A_{i,j}$。
## 输出格式

输出包含一行，为选出的 $n$ 个数中第 $k$ 大数的最小值。
## 样例

### 样例输入 #1
```
2 3 1
1 2 4
2 4 1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3 4 2
1 5 6 6
8 3 4 3
6 8 6 3
```
### 样例输出 #2
```
3
```
## 提示

对于 $20$% 的数据， $1 \leq n \leq m \leq 9$

对于 $40$% 的数据， $1 \leq n \leq m \leq 22, 1 \leq n \leq 12$

对于 $100$% 的数据， $1 \leq k \leq n \leq m \leq 250, 1 \leq A_{i,j} \leq 10^9$


---

---
title: "士兵占领"
layout: "post"
diff: 省选/NOI-
pid: P4311
tag: ['网络流', '费用流']
---
# 士兵占领
## 题目描述

有一个 $M \times N$ 的棋盘，有的格子是障碍。现在你要选择一些格子来放置一些士兵，一个格子里最多可以放置一个士兵，障碍格里不能放置士兵。我们称这些士兵占领了整个棋盘当满足第 $i$ 行至少放置了 $L_i$ 个士兵，第 $j$ 列至少放置了 $C_j$ 个士兵。现在你的任务是要求使用最少个数的士兵来占领整个棋盘。
## 输入格式

第一行两个数 $M, N, K$ 分别表示棋盘的行数，列数以及障碍的个数。  
第二行有 $M$ 个数表示 $L_i$。  
第三行有 $N$ 个数表示 $C_i$。  
接下来有 $K$ 行，每行两个数 $X, Y$ 表示 $(X, Y)$ 这个格子是障碍。
## 输出格式

输出一个数表示最少需要使用的士兵个数。如果无论放置多少个士兵都没有办法占领整个棋盘，输出”JIONG!” (不含引号)
## 样例

### 样例输入 #1
```
4 4 4
1 1 1 1
0 1 0 3
1 4
2 2
3 3
4 3

```
### 样例输出 #1
```
4
```
## 提示

对于 $100 \%$ 的数据，$1 \le M, N \le 100$，$0 \le K \le M \cdot N$。


---

---
title: "文理分科"
layout: "post"
diff: 省选/NOI-
pid: P4313
tag: ['网络流', '图论建模', '最小割']
---
# 文理分科
## 题目描述

文理分科是一件很纠结的事情！（虽然看到这个题目的人肯定都没有纠结过）

小 P 所在的班级要进行文理分科。他的班级可以用一个 $n\times m$ 的矩阵进行描述，每个格子代表一个同学的座位。每位同学必须从文科和理科中选择一科。同学们在选择科目的时候会获得一个满意值。满意值按如下的方式得到：

- 如果第 $i$ 行第 $j$ 列的同学选择了文科，则他将获得 $art_{i,j}$ 的满意值，如果选择理科，将得到 $science_{i,j}$ 的满意值。

- 如果第 $i$ 行第 $j$ 列的同学选择了文科，并且他相邻（两个格子相邻当且仅当它们拥有一条相同的边）的同学全部选择了文科，则他会更开心，所以会增加 $same\text{\underline{ }}art_{i,j}$ 的满意值。

- 如果第 $i$ 行第 $j$ 列的同学选择了理科，并且他相邻的同学全部选择了理科，则增加 $same\text{\underline{ }}science_{i,j}$ 的满意值。

小 P 想知道，大家应该如何选择，才能使所有人的满意值之和最大。请告诉他这个最大值。
## 输入格式

输入第一行为两个正整数 $n,m$。  
接下来 $n$ 行 $m$ 个整数，第 $i$ 行第 $j$ 个整数表示 $art_{i,j}$；  
接下来 $n$ 行 $m$ 个整数，第 $i$ 行第 $j$ 个整数表示 $science_{i,j}$；  
接下来 $n$ 行 $m$ 个整数，第 $i$ 行第 $j$ 个整数表示 $same\text{\underline{ }}art_{i,j}$；  
接下来 $n$ 行 $m$ 个整数，第 $i$ 行第 $j$ 个整数表示 $same\text{\underline{ }}science_{i,j}$。
## 输出格式

输出为一个整数，表示最大的满意值之和。
## 样例

### 样例输入 #1
```
3 4
13 2 4 13
7 13 8 12
18 17 0 5
8 13 15 4
11 3 8 11
11 18 6 5
1 2 3 4 
4 2 3 2
3 1 0 4
3 2 3 2
0 2 2 1
0 2 4 4 
```
### 样例输出 #1
```
152
```
## 提示

### 样例说明

1 表示选择文科，0 表示选择理科，方案如下：

1  0  0  1

0  1  0  0

1  0  0  0

### 数据范围

$n,m\leq 100$，读入数据均 $\leq 500$。                                                                                                                                                              


---

---
title: "[国家集训队] 航班安排"
layout: "post"
diff: 省选/NOI-
pid: P4452
tag: ['2012', '集训队互测', '网络流', '费用流']
---
# [国家集训队] 航班安排
## 题目背景

1. wqs 爱好模拟飞行。
2. clj 开了一家神犇航空，由于 clj 还要玩游戏，所以公司的事务由你来打理。

注意：题目中只是用了这样一个背景，并不与真实 / 模拟飞行相符。
## 题目描述

神犇航空有 $K$ 架飞机，为了简化问题，我们认为每架飞机都是相同的。神犇航空的世界中有 $N$ 个机场，以 $0\cdots N-1$ 编号，其中 $0$ 号为基地机场，每天 $0$ 时刻起飞机才可以从该机场起飞，并不晚于 $T$ 时刻回到该机场。

一天，神犇航空接到了 $M$ 个包机请求，每个请求为在 $s$ 时刻从 $a$ 机场起飞，在恰好 $t$ 时刻到达 $b$ 机场，可以净获利 $c$。换言之，你只需要在 $s$ 时刻在 $a$ 机场选择提供一架飞机给请求方，那么这架飞机就会在 $t$ 时刻准时出现在 $b$ 机场，并且你将获得 $c$ 的净利润。

设计一种方案，使得总收益最大。
## 输入格式

第一行，$4$ 个正整数 $N,M,K,T$，如题目描述中所述；

以下 $N$ 行，每行 $N$ 个整数，描述一个 $N\times N$ 的矩阵 $t$，$t_{i,j}$ 表示从机场 $i$ 空载飞至机场 $j$，需要时间 $t_{i,j}$；

以下 $N$ 行，每行 $N$ 个整数，描述一个 $N\times N$ 的矩阵 $f$，$f_{i,j}$ 表示从机场 $i$ 空载飞至机场 $j$，需要费用 $f_{i,j}$；

以下 $M$ 行，每行 $5$ 个整数描述一个请求，依次为 $a,b,s,t,c$。
## 输出格式

　　仅一行，一个整数，表示最大收益。
## 样例

### 样例输入 #1
```
2 1 1 10
0 5
5 0
0 5
5 0
0 1 0 5 10
```
### 样例输出 #1
```
5
```
## 提示

对于 $10\%$ 的测试数据，$K=1$；

另有 $20\%$ 的测试数据，$K=2$；

对于全部的测试数据，$1\le N,M\le 200$，$1\le K\le 10$，$1\le T\le 3000$，$1\le t_{i,j}\le 200$，$f_{i,j}\le 2\times 10^3$，$0\le a,b<N$，$0\le s\le t\le T$，$0\le c\le 10000$，$t_{i,i}=f_{i,i}=0$，$t_{ij}\le t_{i,k}+t_{k,j}$，$f_{i,j}\le f_{i,k}+f_{k,j}$。


---

---
title: "王者之剑"
layout: "post"
diff: 省选/NOI-
pid: P4474
tag: ['网络流', '二分图', '最小割']
---
# 王者之剑
## 题目描述

![https://cdn.luogu.com.cn/upload/pic/17920.png](https://cdn.luogu.com.cn/upload/pic/17920.png)  

这是在阿尔托利亚·潘德拉贡成为英灵前的事情，她正要去拔出石中剑成为亚瑟王，在这之前她要去收集一些宝石。

宝石排列在一个 $n \times m$ 的网格中，每个网格中有一块价值为 $v_{i,j}$ 的宝石，阿尔托利亚·潘德拉贡可以选择自己的起点。

开始时刻为 $0$ 秒。以下操作，每秒按顺序执行。

1. 在第 $i$ 秒开始的时候，阿尔托利亚·潘德拉贡在方格 $(x,y)$ 上，她可以拿走 $(x, y)$ 中的宝石。
2. 在偶数秒，阿尔托利亚·潘德拉贡周围四格的宝石会消失。
3. 若阿尔托利亚·潘德拉贡第 $i$ 秒开始时在方格 $(x,y)$ 上，则在第 $i+1$ 秒可以立即移动到 $(x+1,y),(x,y+1),(x-1,y)$ 或 $(x, y- 1)$ 上，也可以停留在（$x,y)$ 上。


求阿尔托利亚·潘德拉贡最多可以获得多少价值的宝石
## 输入格式

第一行给出数字 $N,M$ 代表行列数 $N,M$ 均小于等于 $100$，宝石的价值不会超过 $10000$。下面 $N$ 行 $M$ 列用于描述数字矩阵。
## 输出格式

输出最多可以拿到多少价值宝石。
## 样例

### 样例输入 #1
```
2 2
1 2
2 1
```
### 样例输出 #1
```
4
```
## 提示

姚金宇的原创题。


---

---
title: "【模板】最大流 加强版 / 预流推进"
layout: "post"
diff: 省选/NOI-
pid: P4722
tag: ['网络流', 'O2优化', '优先队列', '队列']
---
# 【模板】最大流 加强版 / 预流推进
## 题目描述

给定 $n$ 个点，$m$ 条有向边，给定每条边的容量，求从点 $s$ 到点 $t$ 的最大流。
## 输入格式

第一行包含四个正整数 $n$、$m$、$s$、$t$，用空格分隔，分别表示点的个数、有向边的个数、源点序号、汇点序号。

接下来 $m$ 行每行包含三个正整数 $u_i$、$v_i$、$c_i$，用空格分隔，表示第 $i$ 条有向边从 $u_i$ 出发，到达 $v_i$，容量为 $c_i$。
## 输出格式

一个整数，表示 $s$ 到 $t$ 的最大流。
## 样例

### 样例输入 #1
```
7 14 1 7
1 2 5
1 3 6
1 4 5
2 3 2
2 5 3
3 2 2
3 4 3
3 5 3
3 6 7
4 6 5
5 6 1
6 5 1
5 7 8
6 7 7

```
### 样例输出 #1
```
14
```
### 样例输入 #2
```
10 16 1 2
1 3 2
1 4 2
5 2 2
6 2 2
3 5 1
3 6 1
4 5 1
4 6 1
1 7 2147483647
9 2 2147483647
7 8 2147483647
10 9 2147483647
8 5 2
8 6 2
3 10 2
4 10 2

```
### 样例输出 #2
```
8
```
## 提示

$1\leqslant n \leqslant 1200, 1\leqslant m \leqslant 120000, 1\leqslant c \leqslant 2^{31}-1$。

保证答案不超过 $2^{31}-1$。

常用网络流算法的复杂度为 $O(n^2 m)$，请尽量优化算法。

数据提供者：@negiizhao

（如果有人用 dinic 算法过掉了此题，请私信上传者）


---

---
title: "清理雪道"
layout: "post"
diff: 省选/NOI-
pid: P4843
tag: ['网络流', '上下界网络流']
---
# 清理雪道
## 题目描述

滑雪场坐落在 FJ 省西北部的若干座山上。

从空中鸟瞰，滑雪场可以看作一个有向无环图，每条弧代表一个斜坡（即雪道），弧的方向代表斜坡下降的方向。

你的团队负责每周定时清理雪道。你们拥有一架直升飞机，每次飞行可以从总部带一个人降落到滑雪场的某个地点，然后再飞回总部。从降落的地点出发，这个人可以顺着斜坡向下滑行，并清理他所经过的雪道。

由于每次飞行的耗费是固定的，为了最小化耗费，你想知道如何用最少的飞行次数才能完成清理雪道的任务。
## 输入格式

第一行一个整数 $n$ 代表滑雪场的地点的数量。

接下来的 $n$ 行，描述 $1$ 到 $n$ 号地点出发的斜坡。第 $i$ 行的第一个数为 $m_i$，后面共有 $m_i$ 个整数，由空格隔开，每个整数 $a_{i,j}$ 互不相同，代表从地点 $i$ 下降到地点 $a_{i,j}$ 的斜坡。

## 输出格式

一行一个整数，表示直升飞机的最少飞行次数。
## 样例

### 样例输入 #1
```
8
1 3
1 7
2 4 5
1 8
1 8
0
2 6 5
0
```
### 样例输出 #1
```
4
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，$2 \le  n \le 100$，$1\le m_i < n$ 且每个地点至少有一个斜坡与之相连。


---

---
title: "【模板】最小割树（Gomory-Hu Tree）"
layout: "post"
diff: 省选/NOI-
pid: P4897
tag: ['网络流', '深度优先搜索 DFS', '最小割']
---
# 【模板】最小割树（Gomory-Hu Tree）
## 题目背景

模板题。做本题之前请确保你会 Dinic 或 ISAP。如果你乱搞过了我请你抽烟。

根据惯例，网络流题不允许卡 Dinic/ISAP，但可以卡 EK，本题数据严格遵循上述条约。
## 题目描述

给定一个 $n$ 个点 $m$ 条边的无向连通图，多次询问两点之间的最小割。

两点间的最小割是这样定义的：原图的每条边有一个割断它的代价，你需要用最小的代价使得这两个点不连通。
## 输入格式

第一行两个数 $n,m$。

接下来 $m$ 行，每行 $3$ 个数 $u,v,w$，表示有一条连接 $u$ 与 $v$ 的无向边，割断它的代价为 $w$。

接下来这一行有一个整数$Q$，表示询问次数

接下来 $Q$ 行，每行两个数 $u,v$，你需要求出 $u$ 与 $v$ 之间的最小割

**注意：因为数据有误，给定图的真实点数应该是 $n+1$ 个，编号为 $0$ 到 $n$。**
## 输出格式

输出共 $Q$ 行，每行一个整数对应询问的答案
## 样例

### 样例输入 #1
```
4 5
1 2 2
2 3 2
4 2 3
4 3 1
1 3 1
3
1 4
2 4
2 3
```
### 样例输出 #1
```
3
4
4
```
## 提示

$1\le n\leq 500,\quad 0\le m\leq 1500,\quad 0\le Q\leq 10^5,\quad 0\leq w\leq 10^4,\quad u\neq v$


---

---
title: "逃生之路"
layout: "post"
diff: 省选/NOI-
pid: P4968
tag: ['2018', '网络流', 'O2优化', '费用流']
---
# 逃生之路
## 题目背景

还在茫茫宇宙中……
## 题目描述

还是这群生物 ccj，因为上次的打击太草率了，同时被他人侦测到了。在得知自己即将受到黑暗森林打击之后，选择逃离自己的家园。

他们的旅程计划在一条线上，其中，我们约定，一号点是他们的家园，有无限多个生物。每一个星球，都可以向之后连续的 $p$ 个星球进行转移。但由于每个星球的”体质“不同，每个星球所能接受的生物数量限定在一个范围 $[b,a]$ 之间。而且，由于星球本身资源匮乏，到达每一个星球都需要消耗星球一定的能源，补充飞船能源。并且又因为宇宙空间的复杂，所以这个能源是关于星球所接受生物数量的一个多项式。飞船年久失修，所以遇到任何星球必定前往去补充能源。

可惜这群生物有一个睿智的头领，他希望最终能有生物到达可以生存的星球，而且消耗的总能源要尽量少。那群生物对这个头领很失望，于是把任务丢给你。

请求出有生物到达可生存星球的情况下，最少的能源消耗是多少？

## 输入格式

第一行两个整数$n$和$p$，表示有$n$个星球（包括他们的家园和目的地），每次向后跳$p$个，保证 $p\le n-1$。

接下来有 $2\times n-2$ 行，偶数行有三个数字，$a_i$、$b_i$ 和 $f_i$，$i$ 从 $2$ 开始，表示第 $i$ 个星球能承载的生物数范围和这个星球是否能够生存，$f_i$ 为 $1$ 即能生存，$0$ 即为不能生存。

奇数行先有一个数字 $k$，表示这个多项式是  $k$ 次，接下来 $k+1$ 个整数，表示从高到低每一项的系数 $wi$。
## 输出格式

一个整数 $ans$ 表示花费最少的能源是多少，如果没有一个生物能到达，输出**"die"**（不包括引号）。
## 样例

### 样例输入 #1
```
3 1
5 2 0
2 30 17 28
5 1 1
2 47 56 -60
```
### 样例输出 #1
```
422

```
### 样例输入 #2
```
3 1
1 1 0
1 1 1
1 1 0
1 1 1
```
### 样例输出 #2
```
die
```
### 样例输入 #3
```
10 3
23 16 1
3 25 15 -27 47
43 38 0
3 19 35 40 -11
43 37 0
3 70 22 8 -28
41 36 0
3 86 -8 21 -59
39 33 1
3 83 37 -26 56
18 12 0
3 3 96 -75 43
50 43 0
3 85 -2 47 -36
48 41 1
3 36 -4 83 -61
14 8 1
3 33 13 35 -24

```
### 样例输出 #3
```
21071866

```
## 提示

**样例解释**

样例一中从 $1\to 2$ 两个ccj，$2\to 3$ 两个 ccj，$2\times 2\times 30+2\times 17+28+2\times 2\times 47+2\times 56-60=422$

样例二由于没有任何一个星球可以生存，故 die。

$2\le n\le 100\quad |w|\le 100\quad 1\le b\le a\le 100\quad 1\le k\le 5\quad 0\le p\le 10$。

保证多项式函数二阶导函数在 $x∈[1,100]$ 时恒大于 $0$。


---

---
title: "T'ill It's Over"
layout: "post"
diff: 省选/NOI-
pid: P5029
tag: ['线段树', '网络流', '图论建模']
---
# T'ill It's Over
## 题目背景

小正方形被黑暗之主碾成了粉末。

一切，就这么结束了吗？

就当大家都以为再无翻盘的希望时，

已经被净化的两个世界之树的部分，微微闪烁……
## 题目描述

小正方形被三角的力量复活了，它即将与黑暗之主展开最后的战斗。

小正方形最后的目标，就是净化黑暗之主。

黑暗之主的蜈蚣长度为 $n$，一开始每一节的光明程度为 $1$

当一节蜈蚣的光明程度达到一个指定的值 ($k$)，我们就视作这节蜈蚣被净化。

为了净化黑暗之主，小正方形准备了 $m$ 种方案，这些方案按本质上的不同大约可分为四种：

1. 将一节光明程度为 $a$ 的蜈蚣的光明程度 变为 $b$。（注意，$b$ 可能 $<=a$）

2. 将一节光明程度在 $a1$ 到 $a2$ 区间的蜈蚣的光明程度变为 $b1$

3. 将一节光明程度为 $a1$ 的蜈蚣的光明程度变为 $b1$ 到 $b2$ 区间的任意值。

4. 将一节光明程度在 $a1$ 到 $a2$ 区间的蜈蚣的光明程度变为 $b1$ 到 $b2$ 区间的任意值。

由于小正方形使用每种方案需要消耗一定程度的属性能量，因此每种方案都有一个独立的使用次数的上限，在一种方案中我们用 $l$ 来表示这个上限。

小正方形想要知道，自己最多能够净化几节黑暗之主的蜈蚣。
## 输入格式

第一行为三个正整数 $n$，$m$，$k$，表示黑暗之主蜈蚣身体的长度，小正方形的方案总数与上文所述的 $k$。

接下来 $m$行，每行开头为两个正整数 $op$,$l$，表示方案的种类与使用次数的上限，方案的输入方式如下：

若 $op = 1$，则接下来两个整数 $a$，$b$，意义如上文所述。

若 $op = 2$，则接下来三个整数 $a1$,$a2$,$b1$，意义如上文所述。

若 $op = 3$，则接下来三个整数 $a1$,$b1$,$b2$，意义如上文所述。

若 $op = 4$，则接下来四个整数 $a1$,$a2$,$b1$,$b2$，意义如上文所述。

数据保证，所有 $1 <= a,b,a1,b1,a2,b2 <= k$
## 输出格式

一行一个整数，表示最多能净化的节数。
## 样例

### 样例输入 #1
```
5 4 5
1 3 1 3
1 3 3 2
1 3 2 5
4 1 1 1 4 5
```
### 样例输出 #1
```
4
```
## 提示

首先使用方案1，2，3，将三节光明程度变为 $3$，接着再变为 $2$，再变为 $5$

然后使用方案 4，将一节的光明程度变为 $5$

对于 $10\%$ 的数据，$n = 1,op = 1$

对于另外 $10\%$ 的数据，$n = 1,op <= 3$

对于另外 $10\%$ 的数据，$n <= 10,op = 1$

对于另外 $20\%$ 的数据，$n <= 100,m <= 100,op = 1$

对于 $70\%$ 的数据，$n  <= 1000,m <= 1000,op <= 3,k <= 20000$

**对于前 $70\%$ 的数据，时限为 $500$ ms**

对于 $100\%$ 的数据，$n <= 10^7,m <= 20000,1 <= k <= 100000,1 <= l <= 10^5$

**对于后 $30\%$ 的数据，时限为 $8000$ ms**

**数据保证，操作为随机生成**


---

---
title: "Shoot the Bullet|东方文花帖|【模板】有源汇上下界最大流"
layout: "post"
diff: 省选/NOI-
pid: P5192
tag: ['上下界网络流']
---
# Shoot the Bullet|东方文花帖|【模板】有源汇上下界最大流
## 题目背景

Translated by @chen_zhe

幻想乡是一个被博丽大结界和虚幻与现实的境界所包围起来的一个美妙的地方。这里人和其他生物，例如妖怪、妖精等核平共处。

射命丸文（Syameimaru Aya）是一只鸦天狗，拥有操纵风的能力，已经活了千岁以上，是《文文。新闻》的主编，拥有着一本叫做《文花帖》的手账，记录幻想乡各地的大新闻。她不仅是天狗中速度最快的鸦天狗，思考能力非常强，以别人的几倍的思考速度思考，也拥有幻想乡最高等级的力量。

（译者内心 O.S.：远古的东方众都那么硬核科普的吗）

![](https://i.loli.net/2019/01/12/5c3970b446151.png)
## 题目描述

![](https://i.loli.net/2019/01/12/5c3971b885128.jpg)

（附注：文花帖8-8 西行寺幽幽子 「死蝶浮月」）

在接下来的 $n$ 天中，射命丸文将要拍摄幻想乡的少女的照片。并且要为第 $x$ 个少女拍摄至少 $G_x$ 张照片刊登在《文文。新闻》上。在第 $k$ 天的时候文文有 $C_k$ 位少女可以拍，且在这一天中对某个少女拍的照片数量 **必须** 在某个闭区间 $[L, R]$ 中。如果过少，文文就搞不出大新文；如果过多，就会有少女很安格瑞。

除此之外，因为拍照设备的原因，对于第 $i$ 天，每天的拍照数量不能超过 $D_i$ 张。在满足这些限定的条件下，文文希望拍到的照片尽可能地多。

由于文文需要去取材，因此她把这个任务交给了你，让你帮她去解决。
## 输入格式

本题有不定组数据，保证数据组数不超过 $10$。

第一行输入两个非负整数 $n$ 和 $m$，分别表示有 $n$ 天，有 $m$ 位少女。其中 $n \leq 365,m \leq 1000$。

接下来一行，有 $m$ 个整数 $G_0, G_1, \cdots, G_{m - 1}$。保证对于每一个 $G_x$，都满足 $G_x \in [0,10^5]$。

再接下来有 $n$ 段，第 $i$ 段的第一行有两个整数 $C _ i, D _ i\ (1 \leq C _ i \leq 300, 0 \leq D _ i \leq 30000)$。

接下来有 $C _ i$ 行，每一行有三个非负整数 $T,L,R\ (0 \leq T < m, 0 \leq L \leq R \leq 100)$，其中 $T$ 指的是少女的编号。**同一天中输入的少女编号可能有重复。**
## 输出格式

如果无法满足文文的需求，那么请输出 `-1`。

否则请输出在满足需求的情况下，文文最多能拍多少张照片。

注意每输出完一组数据之后，中间要空一行。
## 样例

### 样例输入 #1
```
2 3
12 12 12
3 18
0 3 9
1 3 9
2 3 9
3 18
0 3 9
1 3 9
2 3 9
```
### 样例输出 #1
```
36
```
### 样例输入 #2
```
2 3
12 12 12
3 18
0 3 9
1 3 9
2 3 9
3 18
0 3 9
1 3 9
2 3 9
2 3
12 12 12
3 18
0 3 9
1 3 9
2 3 9
3 18
0 3 9
1 3 9
2 3 9
```
### 样例输出 #2
```
36

36
```


---

---
title: "[JSOI2013] 打地鼠"
layout: "post"
diff: 省选/NOI-
pid: P5263
tag: ['2013', '各省省选', '网络流', '江苏', 'O2优化']
---
# [JSOI2013] 打地鼠
## 题目背景

JYY 特别喜欢到游戏厅玩打地鼠游戏——拿起两个锤子用力敲打不断冒出
来的地鼠。

打到不同的地鼠有不同的得分，JYY想知道怎样才能得到最高的分
数。
## 题目描述

游戏里一共会冒出来 $N$ 个地鼠，这些地鼠冒出来的位置都分布在一条直线
上。第 $i$ 个地鼠会在 $T_i$ 时刻在 $X_i$ 位置冒出来，打到第 $i$ 个地鼠的得分是 $P_i$。

当游戏开始时（也就是 0 时刻），JYY 左手的位置为 XLEFT，右手的位置为
XRIGHT。JYY的手的最大移动速度是 $V$（每单位时刻最多移动的距离为 V） 。

地鼠会在瞬间冒出来然后消失。如果在对应的时刻 JYY 的一只手恰好也在地鼠冒出来的位置，那么 JYY 就可以在瞬间完成击打动作并得到对应的分数,否则，JYY就只能错过这只地鼠了。

JYY两只手都拿着锤子，所以两只手是可以同时打地鼠的。

然而， 如果在游戏过程中 JYY的两只手交叉的话， JYY会感到很不舒服 （这
个动作确实很别扭，而且两只手可能会互相阻碍而影响移动速度） ，所以 JYY希
望在整个游戏过程中左手的位置 XLEFT永远严格小于右手的位置XRIGHT。JYY想知道，他最多能得多少分呢？
## 输入格式

第一行包含四个整数$N,~V,~XLEFT,~XRIGHT$；
接下来 $N$ 行，分别描述 $N$ 个可能出现的地鼠；
其中第 $i$ 行包含三个整数 $X_i$，$T_i$，$P_i$。
数据保证在同一个时刻不会有两个地鼠出现在同样的位置。
## 输出格式

输出一行一个整数，表示JYY最多能够得到的分数。
## 样例

### 样例输入 #1
```
3 10 150 250
100 20 123
201 10 67
202 10 45
```
### 样例输出 #1
```
190
```
## 提示

$1~\leq~N~\leq~3000,~1~\leq~XLEFT~<~XRIGHT~\leq~10^5,~1~\leq~T_i~\leq~10^5$

$1~\leq~P_i~\leq~10^5,~1~\leq~X_i~\leq~10^5,~1~\leq~V~\leq~10^4$


---

---
title: "[BJOI2016] 水晶"
layout: "post"
diff: 省选/NOI-
pid: P5458
tag: ['图论', '2016', '各省省选', '网络流', '北京', 'O2优化']
---
# [BJOI2016] 水晶
## 题目背景

不用惊慌，今天的题都不是小强出的。  

——融入了无数心血的作品，现在却不得不亲手毁掉，难以体会他的心情啊。

——那也是没有办法的事情，能量共振不消除的话…… 

望着已经被装上炸药的水晶，02放下了望远镜，看向了手中的共振分析报告。  

还是会有一些水晶，幸存下来的…… 也许吧。
## 题目描述

地图由密铺的六边形单元组成，每个单元与其他六个单元相邻。  

为了方便起见，我们用坐标 $(x,y,z)$ 描述一个单元的位置，表示从原点开始按如图所示的 $x,y,z$ 方向各走若干步之后到达的地方。  

有可能有两个坐标描述同一个单元，比如 $(1,1,1)$ 和 $(0,0,0)$ 描述的都是原点。

![](https://cdn.luogu.com.cn/upload/image_hosting/dd1hb5vv.png)

显然 $(x,y,z)$ 单元和 $(x+1,y,z)$，$(x-1,y,z)$ ，$(x,y+1,z)$，$(x,y-1,z)$，$(x,y,z+1)$，$(x,y,z-1)$ 相邻。  

有 $N$ 块水晶位于地图的单元内，第 $i$ 块水晶位于坐标 $(x_i, y_i, z_i)$ 所表示的单元中，并拥有 $c_i$ 的价值，每个单元内部可能会有多块水晶。  

地图中，有一些单元安装有能量源。如下图，任何满足 $x+y+z$ 是 $3$ 的整数倍的坐标所描述的单元内都安装有能量源。  

![](https://cdn.luogu.com.cn/upload/image_hosting/9x4o6dhs.png)

有能量源的单元中的水晶价值将会额外增加 $10\%$。如果三块水晶所在的单元满足特定排列，那么它们将会引发共振。 

共振分两种，$a$ 共振和 $b$ 共振。  

$a$ 共振：如果三块水晶所在的单元两两相邻地排成一个三角形，那么会引起 $a$ 共振。   

![](https://cdn.luogu.com.cn/upload/image_hosting/48uc3ey4.png)

图中每一个三角形表示这三个单元各有一块水晶将会发生一个 $a$ 共振。  

$b$ 共振：如果三块水晶所在的单元依次相邻地排成一条长度为 $2$ 的直线段，且正中间的单元恰好有能量源，那么会引起b共振。  

![](https://cdn.luogu.com.cn/upload/image_hosting/2b47zl09.png)

图中粉红色线段表示这三个单元各有一块水晶将会发生一个 $b$ 共振，黑色线段表示即使这三个单元有水晶也不会发生 $b$ 共振。  

现在你要炸掉一部分水晶，使得任何共振都不会发生的前提下，剩余水晶的价值总和最大。
## 输入格式

第一行一个正整数 $N$，表示水晶数量。  
接下来 $N$ 行，每行四个整数用空格分开的整数 $x_i,y_i,z_i,c_i$，表示一个水晶的位置和价值。  
有可能有水晶的位置重合。  
## 输出格式

一行一个实数，表示剩余水晶的价值总和，四舍五入保留 $1$ 位小数。
## 样例

### 样例输入 #1
```
4
0 0 0 11
1 0 0 5
0 1 0 7
0 0 -1 13
```
### 样例输出 #1
```
25.1
```
## 提示

【样例 $1$ 说明】   

四块水晶排成一个菱形，没有 $b$ 共振，有 $2$ 处 $a$ 共振，分别是 $1,2,4$ 号水晶和 $1,3,4$ 号水晶形成的三角形。 
因此，为了消除两处 $a$ 共振，有如下 $3$ 种方案：

1. 炸掉 $1$ 号水晶，留下 $2,3,4$ 号水晶，总剩余价值 $5+7+13=25$
2. 炸掉 $4$ 号水晶，留下 $1,2,3$ 号水晶，总剩余价值 $11 \times(1+10\%)+5+7=24.1$   
3. 炸掉 $2,3$ 号水晶，留下$1,4$ 号水晶，总剩余价值 $11 \times (1+10\%)+13=25.1$  

因此我们采用第三种方案，最大总剩余价值为$25.1$。    

【数据范围】  

$1\le N \le 50000$    
$1\le c_i \le 1000$   
$-1000 \le x_i,y_i,z_i \le 1000$   


---

---
title: "[CTSC2001] 终极情报网"
layout: "post"
diff: 省选/NOI-
pid: P5814
tag: ['2001', '网络流', '费用流', 'CTSC/CTS']
---
# [CTSC2001] 终极情报网
## 题目描述

在最后的诺曼底登陆战开始之前，盟军与德军的情报部门围绕着最终的登陆地点展开了一场规模空前的情报战。 这场情报战中，盟军的战术是利用那些潜伏在敌军内部的双重间谍，将假的登陆消息发布给敌军的情报机关的负责人。那些已经潜入敌后的间谍们都是盟军情报部的精英，忠实可靠；但是如何选择合适的人选，以及最佳的消息传递方法，才能保证假消息能够尽快而且安全准确地传递到德军指挥官们的耳朵里，成了困扰盟军情报部长的最大问题。他需要你的帮助。

以下是情报部长提供的作战资料：

在敌后一共潜伏着我方最优秀的 $N$ 名间谍，分别用数字 $1,2,\cdots,N$ 编号。在给定的作战时间内，任意两人之间至多只进行一次点对点的双人联系。 我将给你一份表格，表格中将提供任意两位间谍 $i$ 和 $j$ 之间进行联系的安全程度，用一个 $[0,1]$ 的实数 $S_{i,j}$ 表示；以及他们这次联系时，能够互相传递的消息的最大数目，用一个正整数表示 $M_{i,j}$（如果在表格中没有被提及，那么间谍 $i$ 和 $j$ 之间不进行直接联系）。 假消息从盟军总部传递到每个间谍手里的渠道也不是绝对安全，我们用 $[0,1]$ 的实数 $AS_j$ 表示总部与间谍 $j$ 之间进行联系的安全程度，$AM_j $  则表示总部和间谍 $j$ 之间进行联系时传递的消息的最大数目。对于不和总部直接联系的间谍，他的  $AM_j = 0$（而表格中给出的他的 $AS_j$ 是没有意义的）。 当然，假消息从间谍手中交到敌军的情报部官员的办公桌上的过程是绝对安全的，也即是说，间谍与敌军情报部门之间要么不进行直接联系，要么其联系的安全程度是 $1$（即完全可靠）。

现在情报部打算把 $K$ 条假消息“透露”到德军那里。消息先由总部一次性发给 $N$ 名间谍中的一些人，再通过他们之间的情报网传播，最终由这 $N$ 名间谍中的某些将情报送到德军手中。 对于一条消息，只有安全的通过了所有的中转过程到达敌军情报部，这个传递消息的过程才算是安全的；因此根据乘法原理，它的安全程度 $P$ 就是从总部出发，经多次传递直到到达德军那里，每一次传递该消息的安全程度的乘积。 而对于整个计划而言，只有当 $N$ 条消息都安全的通过情报网到达德军手中，没有一条引起怀疑时，才算是成功的。所以计划的可靠程度是所有消息的安全程度的乘积。 显然，计划的可靠性取决于这些消息在情报网中的传递方法。 我需要一个方案，确定消息应该从哪些人手中传递到哪些人手中，使得最终计划的可靠性最大。

你可以利用计算机，来求得这个最可靠的消息传递方案。
## 输入格式

输入包含了盟军的作战资料表格。

第一行包括两个整数 $N$ 和 $K$ ，分别是间谍的总人数和计划包含的消息总数。

第二行包括 $2N$ 个数，前 $N$ 个数是实数 $AS_1,AS_2,\cdots,AS_N$ （范围在 $[0,1]$ 以内）；后 $N$ 个数是整数 $AM_1,AM_2,\cdots,AM_N$ 。

第三行包含了 $N$ 个整数，其中第 $i$（$i = 1,2,\cdots,N$）个整数如果为 $0$ 表示间谍 $i$ 与德军情报部不进行联系，如果为 $1$ 则表示间谍 $i$ 与德军情报部进行联系。

第四行开始，每行包括 $4$ 个数，依次分别是：代表间谍编号的正整数 $i$ 和 $j$ ，间谍 $i$ 和 $j$ 联系的安全性参数 $S_{i,j}$ ( $[0,1]$ 范围内的实数)，以及 $i,j$ 之间传递的最大消息数 $M_{i,j}$ (每一行的 $i$ 均小于 $j$)。

最后的一行为 `-1 -1` ，表示输入数据的结束。
## 输出格式

输出只有一行。这一行中包含一个实数 $P$ ，给出的是整个计划的可靠程度 $P$ ，**保留 $5$ 位有效数字**（四舍五入）。

如果情报网根本不能将 $K$ 条消息传到德军手中，那么计划的可靠性为 $0$ 。

(你可以假定，如果计划存在，那么它的可靠性大于 $10^{-12}$)
## 样例

### 样例输入 #1
```
6 13
0.9 0.7 0.8 0 0 0 2 6 8 0 0 0
0 0 0 1 0 1
1 4 0.5 2
2 3 0.9 5
2 5 0.8 2
2 6 0.8 7
3 5 0.8 2
5 6 0.8 4
-1 -1

```
### 样例输出 #1
```
0.00021184

```
## 提示

$1 \le N,K \le 300$。


---

---
title: "[清华集训 2012] 最小生成树"
layout: "post"
diff: 省选/NOI-
pid: P5934
tag: ['2012', '网络流', '最小割', 'CTT（清华集训/北大集训）']
---
# [清华集训 2012] 最小生成树
## 题目描述

给定一个边带正权的连通无向图 $G=(V,E)$，其中 $N=|V|,M=|E|$，$N$ 个点从 $1$ 到 $N$ 依次编号，给定三个正整数 $u,v$ 和 $L(u\ne v)$，假设现在加入一条边权为 $L$ 的边 $(u,v)$，那么需要删掉最少多少条边，才能够使得这条边既可能出现在最小生成树上，也可能出现在最大生成树上？
## 输入格式

第一行包含用空格隔开的两个整数，分别为 $N$ 和 $M$；

接下来 $M$ 行，每行包含三个正整数 $u,v$ 和 $w$ 表示图 $G$ 存在一条边权为 $w$ 的边 $u,v$。

最后一行包含用空格隔开的三个整数，分别为 $u,v$ 和 $L$；

数据保证图中没有自环。
## 输出格式

输出一行一个整数表示最少需要删掉的边的数量。
## 样例

### 样例输入 #1
```
3 2
3 2 1
1 2 3
1 2 2

```
### 样例输出 #1
```
1
```
## 提示

#### 样例解释
我们只需把边 $(1,2)$ 删除即可，删除并加入新边之后，图中的生成树唯一。

#### 数据规模与约定
对于 $20\%$ 的数据满足 $N\leqslant10,M\leqslant20,L\leqslant20$；

对于 $50\%$ 的数据满足 $N\leqslant300,M\leqslant3000,L\leqslant200$；

对于 $100\%$ 的数据满足 $N\leqslant20000,M\leqslant200000,L\leqslant20000$。


---

---
title: "[RC-02] 开门大吉"
layout: "post"
diff: 省选/NOI-
pid: P6054
tag: ['网络流', 'Special Judge', 'O2优化', '最小割', '期望']
---
# [RC-02] 开门大吉
## 题目描述

$n$ 位选手去参加节目“开门大吉”。共有 $m$ 套题，每套题包含 $p$ 个题目，第 $i$ 位选手答对第 $j$ 套题中第 $k$ 道的概率为 $f_{i,j,k}$。

若一位选手答对第 $i$ 题，会在已得到奖励的基础上，再得到 $c_i$ 元奖励。选手总是从第一道开始，按顺序答题的。

同时，为了防止过多的选手做同一套题，还有 $y$ 条形如“第 $i$ 位选手的套题编号必须至少比第 $j$ 位的大 $k$”的限制。

你需要给每一位选手分配一套题（不同选手可以相同），使得所有人的期望奖励和最小。
## 输入格式

输入包含多组数据。第一行是一个整数 $T$，为数据组数。

对于每组数据，第一行四个整数 $n,m,p,y$。

接下来一行 $p$ 个整数，第 $i$ 个为 $c_i$。 

接下来 $m$ 个 $n\times p$ 的矩阵，第 $j$ 个矩阵中第 $i$ 行第 $k$ 个实数为 $f_{i,j,k}$。

接下来 $y$ 行，每行三个整数 $i,j,k$（$1\le i,j\le n$，$-m<k<m$），描述一条限制。
## 输出格式

对于每组数据，输出一个实数，为答案。无解输出 `-1`。

本题有 Special Judge，答案误差在 $5\times 10^{-4}$ 以内都算对。

由于 SPJ 敏感，请在每组数据末尾都输出一个换行符，并不要再输出其它字符。
## 样例

### 样例输入 #1
```
4
3 2 4 0
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
3 2 4 1
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
2 3 1
3 2 4 1
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
1 2 1
3 2 4 2
10 10 10 20
0.3 0.5 0.7 0.4
0.2 0.6 0.2 0.2
0.7 0.1 0.8 0.2
0.5 0.5 0.5 0.5
0.2 0.5 0.3 0.6
0.3 0.5 0.4 0.1
1 2 1
2 3 1
```
### 样例输出 #1
```
15.1460
18.5340
18.7560
-1
```
## 提示

【样例解释】

这里只解释第二组数据。

一共只有两套题，而第二个人的套题编号大于第三个人，因此第二个人一定是选第二套，第三个人选第一套。

第二个人选第二套，期望支出：$0.2\times (1-0.5)\times 10+0.2\times 0.5 \times (1-0.3) \times 20+0.2\times 0.5 \times 0.3\times (1-0.6)  \times 30+0.2\times 0.5 \times 0.3\times 0.6  \times 50=3.66$。

其他人的计算方法类似。

【数据范围】

**本题捆绑测试。**

对于所有数据，$1\le n,m,p\le 80$，$0\le y\le 10^3$，$0\le f_{i,j,k} \le 1$，$0\le c_i\le 10^5$，$1 \le T\le 50$。保证每个测试点的输入数据大小小于 $10\text{MB}$。

Subtask 1（20 pts）：$n,m,p,y\le 7$；

Subtask 2（20 pts）：$T\le 6$，$y=0$；

Subtask 3（20 pts）：$n,m,p\le 30$，$y\le 200$；

Subtask 4（20 pts）：$T=1$；

Subtask 5（20 pts）：$T\le 5$。


---

---
title: "[JSOI2015] 圈地"
layout: "post"
diff: 省选/NOI-
pid: P6094
tag: ['2015', '各省省选', '网络流', '江苏']
---
# [JSOI2015] 圈地
## 题目背景

JYY 在火星买了一大块矩形的地皮做房地产开发。由于地皮实在是太大了，JYY 把这块地皮划分成了 $N$ 行 $M$ 列的小方格，并在每一格中建造一栋房子。历时若干年，开发终于宣告结束，JYY 也可以把这些房子挂牌出售了。现在他找到了两位非同寻常的土豪买家：南南和强强。

麻烦的是，南南和强强是水火不容的。为了保证他们俩不发生矛盾，JYY 需要把卖给他们俩的房子用墙隔开。不过造墙是需要钱的，JYY 作为倒卖地皮的专家，自然想挣尽可能多的钱，因此他邀请到你帮他设计最优的出售方案。
## 题目描述

JYY 把这块地皮划分成了 $N$ 行 $M$ 列的矩形，且矩形的每一格中建造一栋房子。现在，南南和强强已经将他们的购买意见提交给了 JYY。对于每一栋房子，南南和强强已经给定了他们的出价（不想购买，或愿意以一定价格购买），并且由于他们已经协商好了各自的势力范围，因此不存在两个人同时想买一栋房子的情况。JYY 可以选择每一栋房子是否出售（因为不存在两个人同时想买一栋房子的情况，若 JYY 选择出售一栋房子，它的买家就是确定的）。房子卖给强强和南南以后，JYY 就能获得卖出房子出价的总和。

不过，作为售后服务，JYY 需要通过造墙（将两栋相邻的房子用一堵墙隔开）把两个人的房子完全隔开。所谓完全隔开，就是指造出的墙以及四周的边界将整个区域划分成若干个不连通的部分，每个部分里面只有一个人的房子。当然，造墙也是需要钱的，而且价格不菲。不过 JYY 当初在宣传时声称造墙完全免费，所以这部分钱只好由 JYY 自己出了。

JYY 请你为他规划每幢房子是否要卖出以及建造哪些围墙，才能使得卖房子的收益减去造围墙的花费最大。另外一个好消息是整个地皮的四周已经建好了墙，因此 JYY 可以利用这些建好的墙达到目的。下图就是用墙将区域划分成 $3$ 个不连通的部分的例子。格子中的数字代表出价（数字的含义参考输入格式），边上的数值代表造墙的价格。四周的墙（边界）本来就有，不需要 JYY 花额外的代价去建造。

![](https://cdn.luogu.com.cn/upload/image_hosting/t57031da.png)
## 输入格式

输入第一行包含两个用空格隔开的自然数 $N$ 和 $M$。

接下来 $N$ 行，每行 $M$ 个整数，第 $i$ 行第 $j$ 列的整数 $a$ 描述了位于 $(i,j)$ 房子的出售信息。如果 $a=0$，说明强强和南南都不想买这个位置上的房子；如果 $a>0$，说明强强想以价格 $a$ 买这个位置上的房子。如果 $a<0$，说明南南想以价格 $-a$ 买这个位置上的房子。

接下来 $N-1$ 行，每行 $M$ 个整数。第 $i$ 行第 $j$ 列的数表示第 $i$ 行第 $j$ 列的房子与第 $i+1$ 行第 $j$ 列的房子之间的墙的造价。

接下来 $N$ 行，每行 $M-1$ 个整数。第 $i$ 行第 $j$ 列的数表示第 $i$ 行第 $j$ 列的房子与第 $i$ 行第 $j+1$ 列的房子之间的墙的造价。

## 输出格式

输出仅有一行包含一个整数，表示 JYY 的最大收益。


## 样例

### 样例输入 #1
```
5 5
-3 7 0 0 0
8 0 7 -10 0
0 7 0 1 0
0 0 0 0 0
-8 0 0 2 10
4 50 50 1 50
50 50 1 9 50
50 50 1 1 50
2 50 50 50 50
2 50 50 50
50 50 1 1
50 1 8 1
50 50 50 50
1 50 50 50
```
### 样例输出 #1
```
48
```
## 提示

对于 $100\%$ 的数据，$1\leq N,M\leq 200$，任何价格都不超过 $1000$。


---

---
title: "[CEOI 2010] alliances (day1)"
layout: "post"
diff: 省选/NOI-
pid: P6517
tag: ['2010', '网络流', 'Special Judge', 'O2优化', 'CEOI（中欧）']
---
# [CEOI 2010] alliances (day1)
## 题目描述

在一个幻想世界里，有块矩形岛屿。这座岛屿被划分成了 $R$ 行 $C$ 列的方格。

有些方格无人居住，而有些方格被以下某一种生物占据：精灵，人类，矮人或者霍比特人。占据同一格子的生物在这一格子组成了一个村庄。

为了防止恶魔的袭击，他们需要结成联盟。定义**每个村庄相邻四个方向（上下左右）的村庄**为这个村庄的邻居。

每种生物分别要满足以下条件：

- 精灵：只需要与一个邻居结盟；
- 人类：需要与两个邻居结盟，且这两个邻居不能在上下或者左右方向；
- 矮人：需要与三个邻居结盟；
- 霍比特：需要与四个邻居结盟（即所有邻居）。

你的任务是确定岛上的所有村庄是否都能与相应数量的邻居结盟（即可能会出现一些邻居并没有结盟）。如果能，则输出联盟的结构。否则输出 `Impossible!`。

**注意：结盟的关系是双向的。**
## 输入格式

输入第一行两个整数 $r,c$。

接下来的 $r$ 行，每行 $c$ 个 $0\sim 4$ 之间的数字，描述岛屿的人口分布状态。

- 0：此地无村庄；
- 1：此地为精灵村庄；
- 2：此地为人类村庄；
- 3：此地为矮人村庄；
- 4：此地为霍比特村庄。

**可以注意的技巧：输入的数字对应该地所需的联盟数量。**
## 输出格式

如果无法全部结盟则输出 `Impossible!`。

否则，输出以下格式的地图：

每块地都作为一个 $3\times 3$ 的矩阵输出。如果该地无人居住，则输出全部输出为 `.`。如果该地有村庄，则在中心输出一个 `O`。如果这个村庄与一些村庄结盟，那么在 `O` 上下左右四个方格输出 `X` 来表示结盟。


对于每种生物，所有可能的输出格式如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/wdtqt6i9.png)

(elves 表示精灵，humans 表示人类，dwarves 表示矮人，hobbits 表示霍比特人）

**如果有多种方案，输出其中任意一种，本题使用 SPJ。**
## 样例

### 样例输入 #1
```
3 4
2 3 2 0
3 4 3 0
2 3 3 1
```
### 样例输出 #1
```
............
.OXXOXXO....
.X..X..X....
.X..X..X....
.OXXOXXO....
.X..X..X....
.X..X..X....
.OXXOXXOXXO.
............
```
### 样例输入 #2
```
1 2
2 1
```
### 样例输出 #2
```
Impossible!
```
## 提示

#### 数据规模与约定

- 对于 $55\%$ 的数据，保证 $\min(r,c)\le 10$；
- 对于另 $15\%$ 的数据，保证 $r\times c\le 20$；
- 对于另 $10\%$ 的数据，保证地图中只有无人区和人类；
- 对于 $100\%$ 的数据，保证 $1\le r,c\le 70$。

#### 说明

**题目译自 [CEOI 2010](http://ceoi2010.ics.upjs.sk/Contest/Tasks) day 1 *[T1 alliances](https://people.ksp.sk/~misof/ceoi2010/all-eng.pdf)***。

翻译版权为题目提供者 @[ShineEternal](https://www.luogu.com.cn/user/45475) 所有，未经许可禁止转载。




---

---
title: "[JDWOI-1] 蜀道难"
layout: "post"
diff: 省选/NOI-
pid: P7730
tag: ['网络流', '二分图', '费用流']
---
# [JDWOI-1] 蜀道难
## 题目背景

蜀道难，难于上青天…… 

蜀道之所以难，就是因为山路崎岖不平。
## 题目描述

小 K 和小 M 也模拟了蜀道难。在蜀道难中，有 $n$ 座山，每座山高度为 $h_i$。小 K 和小 M 有 $m$ 种魔法，每一次膜法可以把连续 $l_i$ 座山的高度抬高或压低 $1$，同时消耗 $c_i$ 点体力。

现在，小 K 和小 M 想让蜀道难的 $n$ 座山的高度不下降，这样蜀道就不难了。请问他们最少需消耗多少体力？

**注**：所有时候山的高度都不能为负。
## 输入格式

第一行两个整数 $n,m$，表示山的数量和膜法数量。

第二行 $n$ 个整数 $h_i$，表示山的高度。

接下来 $m$ 行，每行一个字符和两个整数 $w_i, l_i, c_i$，描述一种膜法（如果 $w_i$ 为 $+$，代表抬高；如果 $w_i$ 为 $-$，代表压低）。
## 输出格式

一行一个整数，表示最小消耗的体力。

如果无解，输出 $-1$。
## 样例

### 样例输入 #1
```
3 3
1 3 2
- 1 10
- 2 3
+ 1 1
```
### 样例输出 #1
```
1
```
## 提示

### 样例解释

使用 $1$ 体力值将第三座山升高 $1$。

### 数据范围

- 对于 $10\%$ 的数据，$1\leq n,m \leq 10$；
- 对于另外 $30\%$ 的数据，$1\leq n,m \leq 20$；
- 对于另外 $10\%$ 的数据，$m=1$；
- 对于所有的数据，$1\leq n, m \leq 200$，$1\leq l_i \leq n$，$1\leq h_i, c_i \leq 10^3$。


---

---
title: "[CSP-S 2021] 交通规划"
layout: "post"
diff: 省选/NOI-
pid: P7916
tag: ['2021', '网络流', 'O2优化', '最短路', '平面图', 'CSP-S 提高级']
---
# [CSP-S 2021] 交通规划
## 题目描述

给定一个平面上 $n$ 条水平直线和 $m$ 条垂直直线，它们相交形成 $n$ 行 $m$ 列的网格，从上到下第 $r$ 条水平直线和从左到右第 $c$ 条垂直直线之间的交点称为格点 $(r, c)$。网格中任意两个水平或垂直相邻的格点之间的线段称为一条边，每条边有一个非负整数边权。

进行 $T$ 次询问，每次询问形式如下：

给出 $k$（$T$ 次询问的 $k$ 可能不同）个附加点，每个附加点位于一条从网格边缘向外出发的射线上。所有从网格边缘向外出发的射线按左上-右上-右下-左下-左上的顺序依次编号为 $1$ 到 $2 n + 2 m$，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/iwajnac8.png)

对于每次询问，不同附加点所在的射线互不相同。每个附加点和最近的格点之间的线段也称为一条边，也有非负整数边权（注意，在角上的格点有可能和两个附加点同时相连）。

给定每个附加点的颜色（黑色或者白色），请你将网格内每个格点的颜色染成黑白二者之一，并使得所有两端颜色不同的边的边权和最小。请输出这个最小的边权和。
## 输入格式

第一行，三个正整数 $n, m, T$，分别表示水平、垂直直线的数量，以及询问次数。

接下来 $n - 1$ 行，每行 $m$ 个非负整数。其中第 $i$ 行的第 $j$ 个非负整数 ${x 1}_{i, j}$ 表示 $(i, j)$ 和 $(i + 1, j)$ 间的边权。

接下来 $n$ 行，每行 $m - 1$ 个非负整数。其中第 $i$ 行的第 $j$ 个非负整数 ${x 2}_{i, j}$ 表示 $(i, j)$ 和 $(i, j + 1)$ 间的边权。

接下来依次输入 $T$ 组询问。第 $i$ 组询问开头为一行一个正整数 $k_i$ 表示这次询问附加点的总数。接下来 $k_i$ 行每行三个非负整数。其中第 $j$ 行依次为 ${x 3}_{i, j}, p_{i, j}, t_{i, j}$ 表示第 $j$ 个附加点和相邻格点之间的边权、所在的射线编号以及附加点颜色（$0$ 为白色，$1$ 为黑色）。保证同一组询问内 $p_{i, j}$ 互不相同。

每行的多个整数由空格分隔。
## 输出格式

输出 $T$ 行，第 $i$ 行输出一个非负整数，表示第 $i$ 次询问染色之后两端颜色不同的边权和的最小值。
## 样例

### 样例输入 #1
```
2 3 1
9 4 7
3 8
10 5
2
19 3 1
17 9 0

```
### 样例输出 #1
```
12

```
### 样例输入 #2
```
见附件中的 traffic/traffic2.in
```
### 样例输出 #2
```
见附件中的 traffic/traffic2.ans
```
### 样例输入 #3
```
见附件中的 traffic/traffic3.in
```
### 样例输出 #3
```
见附件中的 traffic/traffic3.ans
```
### 样例输入 #4
```
见附件中的 traffic/traffic4.in
```
### 样例输出 #4
```
见附件中的 traffic/traffic4.ans
```
### 样例输入 #5
```
见附件中的 traffic/traffic5.in
```
### 样例输出 #5
```
见附件中的 traffic/traffic5.ans
```
## 提示

**【样例解释 #1】**

最优方案：$(1, 3), (1, 2), (2, 3)$ 为黑色；$(1, 1), (2, 1), (2, 2)$ 为白色。

**【数据范围】**

| 测试点编号 | $n, m \le$ | $k_i \le$ |
|:-:|:-:|:-:|
| $1 \sim 2$ | $5$ | $50$ |
| $3 \sim 5$ | $18$ | $2$ |
| $6 \sim 8$ | $18$ | $50$ |
| $9 \sim 10$ | $100$ | $2$ |
| $11 \sim 12$ | $100$ | $50$ |
| $13 \sim 16$ | $500$ | $2$ |
| $17 \sim 20$ | $500$ | $50$ |

对于所有数据，$2 \le n, m \le 500$，$1 \le T \le 50$，$1 \le k_i \le \min \{ 2 (n + m), 50 \}$，$1 \le \sum_{i = 1}^{T} k_i \le 50$，$0 \le x \le {10}^6$，$1 \le p \le 2 (n + m)$，$t \in \{ 0, 1 \}$。

保证对于每个 $i \in [1, T]$，$p_{i, j}$ 互不相同。

【感谢 hack 数据提供】  
@[\_Enthalpy](/user/42156)。


---

---
title: "『STA - R2』交朋友"
layout: "post"
diff: 省选/NOI-
pid: P9409
tag: ['网络流', 'O2优化']
---
# 『STA - R2』交朋友
## 题目背景

> 找呀找呀找朋友 找到一个好朋友 敬个礼呀握握手 你是我的好朋友
## 题目描述

幼儿园开学啦！  

在开学前，有的小朋友会准备一个毛绒玩具，可以分享给其他小朋友~  

具体的，一共有 $t$ 天，每天的座位表可以表示成一张无向图。每天**有毛绒玩具**的小朋友一定会选择一个在这一天和他坐在一起的小朋友，并把毛绒玩具送给他。 

但是老师规定，每个人只能有一个毛绒玩具。  

在这里，我们认为每天每个人会先送出玩具，再从别人那里接受。  

问初始时最多可以有多少小朋友有毛绒玩具。  

注意：这意味着一个合法的传递过程中不能出现存在小朋友送不出毛绒玩具或者存在小朋友拥有超过一个毛绒玩具的情况，一个初始局面是合法的当且仅当存在一种合法的传递过程。
## 输入格式

第一行两个正整数 $t,n$，表示天数和小朋友的数量。

后描述 $t$ 张图，表示每天的座位表：

每个描述的第一行是一个正整数 $m$ 表示边数。

后 $m$ 行每行两个正整数 $u,v$ 表示图中存在一条无向边 $(u,v)$。
## 输出格式

输出一行答案。
## 样例

### 样例输入 #1
```
1 2
1
1 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 5
4
1 2
1 3
1 4
1 5
4
1 2
2 3
3 4
4 5
4
1 5
5 2
2 4
4 3
```
### 样例输出 #2
```
2
```
## 提示

**样例解释**

样例 1 解释：满足条件的唯一方案为初始毛绒玩具位于 $1$ 和 $2$。

样例 2 解释：满足条件的一组方案为初始毛绒玩具位于 $1$ 和 $3$。

***
**数据范围**

**本题采用捆绑测试。**

$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline\hline
\textbf{Subtask} & \bm t\le & \bm{n,m}\le & \textbf{分值} \\\hline
\textsf{1} & 1 & 3\times 10^4 & 5 \\\hline
\textsf{2} & 10 & 2 & 5 \\\hline
\textsf{3} & 10 & 100 & 20 \\\hline
\textsf{4} & 10 & 3\times10^3& 70 \\\hline\hline
\end{array}
$$
对于 $100\%$ 的数据，$1\le t\le10$，$1\le n,m\le  3\times10^4$，但是注意 $t,n,m$ 的范围不会同时达到上界。

保证给出的每张图没有重边、自环。


---

---
title: "[EC Final 2021] Check Pattern is Good"
layout: "post"
diff: 省选/NOI-
pid: P9879
tag: ['2021', '网络流', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2021] Check Pattern is Good
## 题目描述

Prof. Shou is given an $n\times m$ board. Some cells are colored black, some cells are colored white, and others are uncolored.

Prof. Shou likes **check patterns**, so he wants to color all uncolored cells and maximizes the number of check patterns on the board.

$4$ cells forming a $2\times 2$ square are said to have the check pattern if they are colored in one of the following ways:

```plain
BW
WB
```

```plain
WB
BW
```

Here `W` ("wakuda" in Chewa language) means the cell is colored black and `B` ("biancu" in Corsican language) means the cell is colored white.
## 输入格式

The first line contains a single integer $T$ $(1\leq T \leq 10^4)$ denoting the number of test cases.

The first line of each test case contains two integers $n$ and $m$ ($1\le n, m\le 100$) denoting the dimensions of the board.

Each of the next $n$ lines contains $m$ characters. The $j$-th character of the $i$-th line represents the status of the cell on the $i$-th row and $j$-th column of the board. The character is `W` if the cell is colored black, `B` if the cell is colored white, and `?` if the cell is uncolored. 

It is guaranteed that the sum of $nm$ over all test cases is no more than $10^6$.
## 输出格式

For each test case, output a line containing the maximum number of check patterns on the board.

In the next $n$ lines, output the colored board in the same format as the input. The output board should satisfy the following conditions.

- It consists of only `B` and `W`.
- If a cell is already colored in the input, its color cannot be changed in the output.
- The number of check patterns equals the answer you print.

If there are multiple solutions, output any of them.
## 样例

### 样例输入 #1
```
3
2 2
??
??
3 3
BW?
W?B
?BW
3 3
BW?
W?W
?W?

```
### 样例输出 #1
```
1
WB
BW
1
BWB
WWB
BBW
4
BWB
WBW
BWB

```
## 题目翻译

#### 题目描述

教授 Shou 得到了一个 $(n \times m)$ 的棋盘。一些格子被涂成了黑色，一些被涂成了白色，还有一些没有上色。

教授 Shou 喜欢**棋盘图案**，所以他想给所有未上色的格子涂色，并最大化棋盘上的棋盘图案数量。

如果四个形成一个 $(2 \times 2)$ 方格的单元格以以下任一种方式上色，则说它们形成了一个棋盘图案：

`BW `

`WB`

或者

`WB `

`BW`

这里的 `W`（在奇瓦语中是“wakuda”，意为黑色）表示格子被涂成了黑色，而 `B`（在科西嘉语中是“biancu”，意为白色）表示格子被涂成了白色。

#### 输入格式

第一行包含一个整数 $T (1 \leq T \leq 10^4)$，表示测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $ m$ $(1 \leq n, m \leq 100)$，表示棋盘的尺寸。

接下来的 $n$ 行每行包含 $m$ 个字符。第 $i$ 行的第 $j$ 个字符表示棋盘上第 $i$ 行和第 $j$ 列的格子的状态。如果格子被涂成了黑色，则字符为 `W`；如果格子被涂成了白色，则字符为 `B`；如果格子未上色，则字符为 `?`。

保证所有测试用例中 $ n \times m $ 的总和不超过 $10^6$。

#### 输出格式

对于每个测试用例，输出一行，包含棋盘上的最大棋盘图案数量。

在接下来的 (n) 行中，以输入格式相同的方式输出上色后的棋盘。输出的棋盘应满足以下条件：

* 只包含 `B` 和 `W`。
* 如果输入中的格子已经上色，则在输出中不能改变其颜色。
* 棋盘图案的数量等于你打印的答案。

如果有多种解决方案，输出其中任何一种。


---

