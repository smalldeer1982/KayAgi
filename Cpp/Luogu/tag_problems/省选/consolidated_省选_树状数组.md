---
title: "「Daily OI Round 3」War"
layout: "post"
diff: 省选/NOI-
pid: P10130
tag: ['线段树', '树状数组', '洛谷原创', 'O2优化']
---
# 「Daily OI Round 3」War
## 题目背景

《赤壁之战》是一款开放世界冒险游戏，这意味着从你踏入提瓦特的第一刻起，只要合理规划自己的体力，不论翻山越岭、还是横渡江河，总有办法见到新的风景。
## 题目描述

有 $n$ 条船，船编号为 $1$ 至 $n$。每条船上有 $m$ 个士兵，士兵编号为 $1$ 至 $m$。

开始时，有若干组船由铁索相连。具体的关系给出如下：

给出 $s$ 组关系，形如 $l_1,r_1,l_2,r_2$，表示 $\forall k \in [0,r_1-l_1]$，第 $l_1+k$ 条船与第 $l_2+k$ 条船相连，保证 $r_1-l_1+1=r_2-l_2+1$ 且 $l_1 < l_2$。

保证 $\forall p \in [1,n]$，最多存在一组关系使得 $l_2 \le p \le r_2$。

然后有 $q$ 个操作，操作如下（操作按照时间先后顺序编号为 $1 \sim q$）：

操作 $1$：向编号为 $p$ 的船的 $[L,R]$ 区间的士兵发射一支火箭。这样操作之后，这个区间的所有士兵都会着火。由于铁锁连环的缘故，所有与 $p$ 直接相连或间接相连的船的 $[L,R]$ 区间的士兵都会着火。注意，士兵可能着火多次。

操作 $2$：撤回编号为 $p$ 的操作，保证这个操作必定是操作 $1$。**保证不会多次撤回同一个操作，并且以后的询问都不考虑已经撤销的操作所带来的影响。**

操作 $3$：询问船 $p$ 上区间为 $[L,R]$ 的士兵是否全部着火。如果全部着火请输出 `Yes`，否则输出 `No`。
## 输入格式

第一行四个整数分别是 $n,m,s,q$，含义如题所示。

接下来 $s$ 行，每行四个整数，表示一个铁索关系。

接下来 $q$ 行，表示操作。

每行第一个整数 $op$ 表示操作种类。

- 若 $op=1$，你需要输入三个整数 $p,L,R$，并按照题目要求执行操作 $1$。

- 若 $op=2$，你需要输入一个整数 $p$，并按照题目要求执行操作 $2$。

- 若 $op=3$，你需要输入三个整数 $p,L,R$，并按照题目要求执行操作 $3$。
## 输出格式

若干行，表示每个 $3$ 操作的答案。

**温馨提示：全部输出 `No` 或者 `Yes` 会得到 $0\text{ pts}$ 的高分。**
## 样例

### 样例输入 #1
```
10 20 2 9
1 5 2 6
7 9 8 10
1 4 1 5
3 6 2 3
2 1
3 6 2 3
1 10 2 7
1 9 3 6
2 6
1 7 8 13
3 8 2 12
```
### 样例输出 #1
```
Yes
No
Yes
```
### 样例输入 #2
```
10 10 2 10
1 1 2 2
1 1 8 8
1 2 1 8
1 6 7 8
1 8 7 8
1 9 6 7
3 8 3 3
2 4
1 5 7 8
3 3 3 3
3 6 3 3
2 3
```
### 样例输出 #2
```
Yes
No
No
```
## 提示

#### 【样例解释 #1】

首先给出了两条关系式，第一条表示了 $1$ 与 $2$，$2$ 与 $3$，$3$ 与 $4$，$4$ 与 $5$，$5$ 与 $6$ 的船是相连的。第二条表示了 $7$ 与 $8$，$8$ 与 $9$，$9$ 与 $10$ 的船是相连的。

第一个操作向第 $4$ 条船的 $1$ 到 $5$ 号士兵发射火箭，因为 $1$ 到 $6$ 号船是相连的，所以 $1$ 到 $6$ 号船上的 $1$ 到 $5$ 号士兵都着火了。

第二个操作询问第一条船的 $2$ 到 $3$ 号是否着火。显然着火了，所以输出 `Yes`。

第三个操作撤回了第一个操作，所以所有士兵操作后都没有着火。

第四个操作询问第一条船的 $2$ 到 $3$ 号是否着火。显然没有着，所以输出 `No`。

第五个操作将十号船的 $[2,7]$ 士兵着火，第六个操作将九号船的 $[3,6]$ 着火。然后第七个操作撤回了第六个操作。注意：目前，第七到十号船的 $[2,7]$ 的士兵是着火的。

第八号操作将七号船的 $[8,13]$ 着火，第九个操作询问是否 $[2,12]$ 全部着火。显然此时已经全部着火了。

#### 【数据范围】

对于全部数据保证：$1 \le n\leq 10^9$，$1 \le m\leq 5\times 10^5$，$0 \le q\leq 10^5$，$0 \le s\leq 200$。


---

---
title: "BZOJ4361 isn"
layout: "post"
diff: 省选/NOI-
pid: P10592
tag: ['动态规划 DP', '树状数组', 'O2优化', '容斥原理']
---
# BZOJ4361 isn
## 题目背景

题目来自原 BZOJ，我们承认题面及原数据的版权均属于原 BZOJ 或将题目授权给 BZOJ 使用的出题人。如果您是版权所有者且认为我们侵犯了您的权益，可联系我们。
## 题目描述

给出一个长度为 $n$ 的序列 $a_1,a_2,\dots a_n$。如果序列 $a$ 不是非降的，你必须从中删去一个数。

这一操作将被不断执行，直到 $A$ 非降为止。求有多少种不同的操作方案。操作方案不同当且仅当删除的顺序或次数不同。答案对 $10^9+7$ 取模。
## 输入格式

第一行输入一个正整数 $n$，表示序列长度。

第二行输入 $n$ 个正整数 $a_i$，表示序列。
## 输出格式

一行一个整数，表示答案对 $10^9+7$ 取模的值。
## 样例

### 样例输入 #1
```
4
1 7 5 3
```
### 样例输出 #1
```
18
```
## 提示

对于 $100\%$ 的数据，$1\leq n\leq 2\times 10^3$，$0\leq a_i \leq 2^{31}-1$。


---

---
title: "[COTS 2021] 赛狗游戏 Tiket"
layout: "post"
diff: 省选/NOI-
pid: P11197
tag: ['树状数组', '2021', 'cdq 分治', 'O2优化', 'COCI（克罗地亚）']
---
# [COTS 2021] 赛狗游戏 Tiket
## 题目背景

Rebirth.

译自 [Izborne Pripreme 2021 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2021/) D2T3。$\texttt{1s,0.5G}$。

## 题目描述

有三个人在观看赛狗游戏。

三个人都猜测了狗冲过终点的顺序，即 $P_i$ 表示第 $i$ 只冲过终点的狗的编号。我们假设没有平局。

有 $N$ 条狗，因此 $P_i$ 构成一个 $1\sim N$ 的排列。不妨记第 $j$ 个人猜测的排列为 $P(j)$。

此外，最终狗冲过终点的顺序构成排列 $T$。

计算满足以下条件的数对 $(a,b)$ 的数量：

- 在 $T$ 中，$a$ 在 $b$ 前面；
- $\forall 1\le j\le 3$，要么 $a$ 在所有的 $P(j)$ 中都在 $b$ 前面，要么 $b$ 在所有的 $P(j)$ 中都在 $a$ 前面。

## 输入格式

第一行，一个正整数 $N$。

第二行，$N$ 个正整数描述 $T$。

接下来三行，第 $j$ 行 $N$ 个正整数，描述 $P(j)$。
## 输出格式

输出一行一个整数，即答案。
## 样例

### 样例输入 #1
```
3
2 3 1
1 2 3
1 2 3
2 3 1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
4
3 1 2 4
4 3 2 1
1 2 3 4
1 2 4 3
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
5
1 3 2 4 5
4 3 5 2 1
4 3 1 2 5
1 2 4 3 5
```
### 样例输出 #3
```
3
```
## 提示


#### 样例解释

样例 $1$ 解释：只有 $(2,3)$ 满足条件。


#### 数据范围


对于 $100\%$ 的数据，保证：

- $2\le N\le 5\times 10^5$；
- $\forall 1\le j\le 3$，$P(j)$ 构成一个 $1\sim N$ 的排列。
- $T$ 构成一个 $1\sim N$ 的排列。


| 子任务编号 | $N\le $ |  特殊性质   | 得分 |  
| :--: | :--: | :--: | :--: |  
| $ 1 $    | $ 5\, 000 $    |  无  | $ 7 $   |  
| $ 2 $    | $ 5\times 10^5 $   |  有 | $ 8 $   |  
| $ 3 $    | $ 5\times 10^4$ | 无  | $ 29 $   |  
| $ 4 $    | $ 5\times 10^5 $  |  无 | $ 56 $   |  

特殊性质：$P(1)=P(2)$。也就是说前两个人猜的排列是一样的。


---

---
title: "[JOIG 2024] 感染シミュレーション / Infection Simulation"
layout: "post"
diff: 省选/NOI-
pid: P11203
tag: ['线段树', '树状数组', '2024', 'O2优化', 'JOI（日本）']
---
# [JOIG 2024] 感染シミュレーション / Infection Simulation
## 题目描述

昨天，$N$ 位顾客光顾了 EGOI 自助餐厅。顾客编号从 $1$ 到 $N$，顾客 $i(1\le i\le N)$ 到达时间为 $L_i$，离开时间为 $R_i$。今天，我们发现有一位顾客来店时感染了目前在 JOI 国流行的新型传染病 X。

传染病 X 的**传染性**用整数 $x$ 表示。具体来说，对于 $1\le i\le N$，当顾客 $i$ 与一个或多个感染者同时进入餐厅的累计总时间至少达到 $x$ 时，顾客 $i$ 就会成为新感染者。

现在，由于 JOI 国采取了严格的感染控制措施，因此必须确定感染者人数。然而，问题在于调查组并不知道哪些人感染了传染病，而代表传染性的整数 $x$ 的值也是未知数。

因此，EGOI 自助餐厅经理理惠决定对于 $Q$ 种情况，分别求出最终会有多少顾客被感染。在第 $j(1\le j\le Q)$ 种情况下，最初只有顾客 $P_j$ 受到感染，传染性为 $X_j$。

根据到店顾客的信息，求出每种情况下最终的感染人数。注意，即使受感染的人数是在他们离开餐厅时被感染的，也应包括在内。此外，还假定一旦顾客感染了传染病 X，他就不能再被感染。
## 输入格式

第一行输入一个整数 $N$。

接下来 $N$ 行，每行两个整数 $L_i,R_i$。

接下来一行输入一个整数 $Q$。

接下来 $Q$ 行，每行两个整数 $P_i,X_i$。
## 输出格式

输出 $Q$ 行，第 $j(1\le j\le Q)$ 行一个整数表示第 $j$ 种情况下的最终感染人数。
## 样例

### 样例输入 #1
```
4
10 40
20 80
45 60
70 95
1
1 15
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
8
0 30
0 90
0 80
0 60
0 20
0 40
0 70
0 50
3
1 30
1 40
4 50
```
### 样例输出 #2
```
7
1
5
```
### 样例输入 #3
```
5
0 10
0 10
0 10
0 10
0 10
4
1 9
1 10
1 11
1 1000000000
```
### 样例输出 #3
```
5
5
1
1
```
### 样例输入 #4
```
7
38 61
13 27
10 54
22 56
49 75
27 47
70 99
1
3 10
```
### 样例输出 #4
```
6
```
### 样例输入 #5
```
10
10 20
11 21
13 23
16 26
20 30
25 35
31 41
38 48
46 56
80 90
4
1 3
1 6
1 8
1 10
```
### 样例输出 #5
```
8
5
3
1
```
### 样例输入 #6
```
7
10 54
38 61
13 27
22 56
49 75
27 47
70 99
5
1 3
1 6
1 9
1 12
1 15
```
### 样例输出 #6
```
7
6
6
6
4
```
### 样例输入 #7
```
7
38 61
13 27
10 54
22 56
49 75
27 47
70 99
5
1 10
2 10
3 10
4 10
5 10
```
### 样例输出 #7
```
4
6
6
5
2
```
## 提示

#### 【样例解释 #1】

在第 $1$ 个询问中，初始的感染者是顾客 $1$，传染性为 $15$，因此感染的传播方式如下

- 在时间 $10$，顾客 $1$ 到达餐厅；
- 在时间 $20$，顾客 $2$ 到达餐厅；
- 在时间 $35$，顾客 $2$ 与顾客 $1$ 同时出现在餐厅累计时间为 $15$，顾客 $2$ 被感染；
- 在时间 $40$，顾客 $1$ 离开餐厅；
- 在时间 $45$，顾客 $3$ 到达餐厅；
- 在时间 $60$，顾客 $3$ 与顾客 $2$ 同时出现在餐厅累计时间为 $15$，顾客 $3$ 被感染；与此同时，顾客 $3$ 离开餐厅；
- 在时间 $70$，顾客 $4$ 到达餐厅；
- 在时间 $80$，顾客 $2$ 离开餐厅；
- 在时间 $95$，顾客 $4$ 与顾客 $2$ 同时出现在餐厅累计时间为 $10$，因此顾客 $4$ 未感染；与此同时，顾客 $4$ 离开餐厅。

最终顾客 $1,2,3$ 被感染，共 $3$ 人，故第 $1$ 个询问答案为 $3$。

该样例满足子任务 $4,5,6,8,9,10$ 的限制。

#### 【样例解释 #2】

- 在第 $1$ 个询问中，$7$ 个顾客 $1,2,3,4,6,7,8$ 最终被感染，答案为 $7$。
- 在第 $2$ 个询问中，$1$ 个顾客 $1$ 最终被感染，答案为 $1$。
- 在第 $3$ 个询问中，$5$ 个顾客 $2,3,4,7,8$ 最终被感染，答案为 $5$。

该样例满足子任务 $2,3,4,5,6,10$ 的限制。

#### 【样例解释 #3】

该样例满足子任务 $1,2,3,5,6,8,10$ 的限制。

#### 【样例解释 #4】

该样例满足子任务 $4,5,6,9,10$ 的限制。

#### 【样例解释 #5】

该样例满足子任务 $4,5,6,7,8,9,10$ 的限制。

#### 【样例解释 #6】

该样例满足子任务 $4,5,6,7,8,10$ 的限制。

#### 【样例解释 #7】

该样例满足子任务 $4,5,6,7,9,10$ 的限制。

#### 【数据范围】

- $1\le N\le 10^5$；
- $0\le L_i<R_i\le 10^9(1\le i\le N)$；
- $1\le Q\le 10^5$；
- $1\le P_j\le N(1\le j\le Q)$；
- $1\le X_j\le 10^9(1\le j\le Q)$。

#### 【子任务】

1. （$2$ 分）$L_i=0(1\le i\le N)$，$R_i=10(1\le i\le N)$，$Q\le 5$；
2. （$3$ 分）$L_i=0(1\le i\le N)$，$Q\le 5$；
3. （$6$ 分）$L_i=0(1\le i\le N)$；
4. （$10$ 分）$N\le 500$，$Q\le 5$，$R_i\le 500(1\le i\le N)$，$X_j\le 500(1\le j\le Q)$；
5. （$11$ 分）$N\le 500$，$Q\le 5$；
6. （$16$ 分）$Q\le 5$；
7. （$13$ 分）$P_j=1(1\le j\le Q)$，$L_1<L_2<\cdots<L_N$，$R_1<R_2<\cdots<R_N$；
8. （$14$ 分）$P_j=1(1\le j\le Q)$；
9. （$15$ 分）$R_i-L_i(1\le i\le N)$ 的最小值大于或等于 $X_j(1\le j\le Q)$ 的最大值；
10. （$10$ 分）无附加限制。


---

---
title: "【MX-S4-T3】「yyOI R2」youyou 的序列 II"
layout: "post"
diff: 省选/NOI-
pid: P11219
tag: ['博弈论', '线段树', '树状数组', 'O2优化', '梦熊比赛']
---
# 【MX-S4-T3】「yyOI R2」youyou 的序列 II
## 题目背景

原题链接：<https://oier.team/problems/S4C>。
## 题目描述

给定一个长度为 $n$ 的非负整数序列 $a$，初始时所有数均被标记为**蓝色**，youyou 和 yy 轮流对序列 $a$ 进行操作，由 youyou 开始。

- 如果当前是 youyou 的回合，那么他可以选择一个长度至多为 $c_1$ 的区间，如果该区间内所有数的和小于等于 $w_1$，则标记该区间所有数为**红色**。

- 如果当前是 yy 的回合，那么他可以选择一个长度至多为 $c_2$ 的区间，如果该区间内所有数的和大于 $w_2$，则标记该区间所有数为**蓝色**。

如果当前操作方没有可操作的区间，他将跳过本回合。

定义 youyou 胜利即是在游戏任意时刻，所有数都被标记为红色。定义 yy 胜利则是在 $10^{51971}$ 个回合内，youyou 无法胜利。两者都会以最优策略进行游戏。

但是他们认为这个游戏太简单了，于是决定上上强度。

现在给定 $q$ 个操作，对于每个操作给定三个数 $opt,x,y$。

- 如果 $opt$ 为 $1$，表示将 $a_x$ 增加 $y$（$0\le y \le 10^9$）。
- 如果 $opt$ 为 $2$，表示 youyou 和 yy 将在区间 $[x,y]$ 所形成的序列上进行一轮游戏。

对于每个 $opt=2$ 的操作，请你求出在区间 $[x,y]$ 所形成的序列上进行游戏，youyou 能否获得胜利。如果 youyou 能胜利，输出 ```cont```；否则，输出 ```tetris```。

## 输入格式

第一行，六个整数 $n,q,c_1,c_2,w_1,w_2$，其中 $n$ 为序列长度，$q$ 为操作个数，$c_1,c_2,w_1,w_2$ 的定义在题目描述中给出。

第二行，$n$ 个整数 $a_1, a_2, \ldots, a_n$。

接下来 $q$ 行，每行三个整数 $opt,x,y$，表示一个操作，操作的定义在上面已给出。
## 输出格式

对于每一个 $opt=2$ 的操作，输出一行表示答案。

## 样例

### 样例输入 #1
```
5 3 4 2 2 3
1 0 0 1 1
2 1 5
1 3 3
2 1 5
```
### 样例输出 #1
```
cont
tetris

```
### 样例输入 #2
```
8 6 10 3 5 2
0 1 0 0 1 0 0 1
2 1 7
1 4 2
2 5 7
1 5 1
1 7 2
2 1 8
```
### 样例输出 #2
```
cont
cont
tetris

```
## 提示

**【样例解释 #1】**

第一次游戏在序列 $[1,0,0,1,1]$ 上进行。

回合 $1$：youyou 将区间 $[1,3]$ 内的数染红。

回合 $2$：yy 没有可操作的区间，**跳过**了本回合。

回合 $3$：youyou 将区间 $[4,5]$ 内的数染红。

此时所有数都被染红，youyou 获胜，输出  ```cont```。

第二次游戏在序列 $[1,0,3,1,1]$ 上进行。

容易发现，此时 youyou 无法获胜，输出 ```tetris```。


**【样例 #3】**

见附件中的 ```seq/seq3.in``` 与 ```seq/seq3.ans```。

该组样例满足测试点 $5\sim 8$ 的约束条件。

**【样例 #4】**

见附件中的 ```seq/seq4.in``` 与 ```seq/seq4.ans```。

该组样例满足测试点 $9\sim10$ 的约束条件。

**【样例 #5】**

见附件中的 ```seq/seq5.in``` 与 ```seq/seq5.ans```。

该组样例满足测试点 $11\sim 14$ 的约束条件。

**【数据范围】**

本题共 $20$ 个测试点，每个 $5$ 分。

|  测试点编号  |          $n$          |         $q$         |  特殊性质  |
| :----------: | :-------------------: | :-----------------: | :--------: |
|  $1\sim 4$   |       $\le10^2$       | $\le 3 \times 10^2$ | A |
|  $5 \sim 8$  |       $\le10^3$       | $\le 3 \times 10^3$ | B |
| $9 \sim 10$  |       $\le10^4$       | $\le 3 \times 10^4$ | C |
| $11 \sim 14$ |     $\le  10 ^ 5$     | $\le 3 \times 10^5$ | D |
| $15\sim 20$  | $\le 3 \times 10 ^ 5$ | $\le 3 \times 10^5$ |     无     |

特殊性质 A：$c_2 > n$，$w_2 = 0$。  
特殊性质 B：$w_1 \le w_2$。  
特殊性质 C：$c_1 \le c_2$。  
特殊性质 D：$c_1,c_2 \le 10^3$。

对于全部数据，保证：
- $1\le n,q,c_1,c_2\le 3\times10^5$。
- $0\le a_i,w_1,w_2\le 10^9$。
- $opt\in \{1,2\}$。
- 对于 $opt=1$ 的操作，$1\leq x\leq n$，$0\leq y\leq 10^9$。
- 对于 $opt=2$ 的操作，$1\leq x\leq y\leq n$。
- 至少有一个 $2$ 类操作。


---

---
title: "[COTS 2017] 盗道 Krimošten"
layout: "post"
diff: 省选/NOI-
pid: P11286
tag: ['2017', '二分', '树状数组', 'COCI（克罗地亚）']
---
# [COTS 2017] 盗道 Krimošten
## 题目背景

译自 [Izborne Pripreme 2017 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2017/) D1T2。$\texttt{4s,0.5G}$。

库纳（Kuna）是克罗地亚的货币单位。
## 题目描述


海岸线上有一排房子，从西到东标号 $1\sim n$。第 $i$ 座房子内有 $a_i$ 库纳。

有 $m$ 个窃贼要行窃。第 $i$ 个窃贼初始囊中有 $c_i$ 库纳，他将依次对编号为 $l_i,l_i+1,\cdots, r_i$ 的房子行窃。

盗亦有道，窃贼们践行盗之道。当窃贼对编号为 $j$ 的房子行窃时，令他囊中有 $k$ 库纳：

- 若 $k\lt a_j$，则窃贼将 $1$ 库纳收入囊中，即 $k\gets k+1$；
- 若 $k=a_j$，无事发生；
- 若 $k\gt a_j$，则窃贼拿出 $1$ 库纳赠给房主，即 $k\gets k-1$。

对于每个窃贼，求出他最后囊中会有多少库纳。

需要注意的是，**每个窃贼的行窃是独立的，不互相影响**。换句话说，可以认为一个窃贼行窃结束后，（在下一个窃贼行窃前）房子会恢复到初始状态。
## 输入格式


第一行，两个正整数 $n,m$;

第二行，$n$ 个非负整数 $a_1,a_2,\cdots,a_n$;

接下来 $m$ 行，每行三个整数 $l_i,r_i,c_i$。
## 输出格式

对于每个询问，输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
10 3
3 5 5 4 3 6 10 0 4 7
2 10 9
6 6 2
2 8 4
```
### 样例输出 #1
```
6
3
4
```
### 样例输入 #2
```
8 5
2 3 0 9 2 6 0 6
5 6 8
3 4 7
3 8 8
8 8 7
6 7 9
```
### 样例输出 #2
```
6
7
6
6
7
```
## 提示



对于 $100\%$ 的数据，保证：

- $1\le n\le 5\times 10^5$；
- $0\le a_i,c_i\le 10^6$；
- $1\le l_i\le r_i\le n $。


| 子任务编号 | $n\le $ |  $m\le $ |得分 |  
| :--: | :--: | :--: | :--: |  
| $ 1 $    | $ 10^3 $    |  $10^3$ |  $ 7 $   |  
| $ 2 $    | $ 5\times 10^4 $   |  $10^5$ |  $ 48 $   |  
| $ 3 $    | $ 5\times 10^5 $ | $5\times 10^5$ | $ 45 $   |  

再次提醒，**每个窃贼的行窃是独立的，不互相影响**。


---

---
title: "[COTS 2016] 搜索树 Jelka"
layout: "post"
diff: 省选/NOI-
pid: P11306
tag: ['2016', '线段树', '倍增', '树状数组', '树的遍历', '树链剖分', 'COCI（克罗地亚）']
---
# [COTS 2016] 搜索树 Jelka
## 题目背景

译自 [Izborne Pripreme 2016 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2016/) D2T1。$\texttt{1s,0.5G}$。

## 题目描述


给定一棵 $n$ 个点的二叉树，点有点权，其中 $1$ 号点为根节点。

$m$ 次操作修改某个点的点权。在每次修改后询问：这棵树上有多少个节点的子树（包含自身）是二叉搜索树（BST）？

我们给定 BST 的定义：

- 含有一个节点的树是 BST。
- 对于大于一个节点的树，它是 BST 当且仅当：
	- 根节点的左子树为空，或者左子树是二叉搜索树，且左子树内所有点的点权均**不大于**根节点的点权；
   - 根节点的右子树为空，或者右子树是二叉搜索树，且右子树内所有点的点权均**不小于**根节点的点权。


## 输入格式


第一行，两个正整数 $n,m$。

接下来 $n$ 行，每行两个整数 $l_i,r_i$，表示 $i$ 号点的左儿子和右儿子编号。
- 特别地，若不存在，则为 $0$。

接下来一行，$n$ 个整数 $a_1,\cdots,a_n$，表示每个点的点权。

接下来 $m$ 行，每行两个整数 $x,v$，表示一次操作 $a_x\gets v$。

## 输出格式

输出 $m$ 行 $m$ 个整数，表示答案。

## 样例

### 样例输入 #1
```
6 5
2 3
4 0
5 6
0 0
0 0
0 0
4 1 3 2 2 5
3 3
2 2
3 5
5 4
6 1
```
### 样例输出 #1
```
4
5
5
6
4
```
### 样例输入 #2
```
8 10
4 5
8 0
0 0
3 7
0 6
0 0
2 0
0 0
7 0 9 3 6 0 6 2
3 0
4 0
8 2
2 3
7 6
1 6
5 7
6 9
1 1
1 7
```
### 样例输出 #2
```
3
3
3
6
6
6
6
8
7
8
```
## 提示


#### 样例解释

样例 $1$ 解释如图所示。

其中节点内的数字表示 BST 权值，节点外的数字表示节点编号。

![](https://cdn.luogu.com.cn/upload/image_hosting/yabnaj75.png)

#### 数据范围

对于 $100\%$ 的数据，保证：
- $1\le n,m\le 2\times 10^5$；
- $0\le a_i,v\le 10^9$；
- 操作和树的形态均合法。


| 子任务编号 | $n,m\le  $ | 特殊性质 | 得分 |  
| :--: | :--: | :--: | :--: |
| $ 1 $    | $ 5\, 000$    |  | $ 16 $   |  
| $ 2 $    | $ 2\times 10^5 $   | A |  $ 24 $   |  
| $ 3 $    | $ 2\times 10^5$ | | $ 60 $   |  

特殊性质 A：$\forall 1\le i\le n$，$l_i=0\lor r_i=0$。




---

---
title: "[迷宫寻路 Round 3] 游戏"
layout: "post"
diff: 省选/NOI-
pid: P11627
tag: ['贪心', '线段树', '平衡树', '树状数组', 'O2优化', '树的遍历']
---
# [迷宫寻路 Round 3] 游戏
## 题目描述

小 L 正在玩游戏，游戏地图是一颗 $n$ 个节点的树，定义一条树上路径的长度为路径上所有边的边权之和，路径可以重复经过点和边。特别的，若路径不包含任何边，则其长度为 $0$。

小 L 会选择一个点作为必经点 $t$，接着，小 L 会设置每条边的边权，使得边的边权构成一个 $1$ 到 $n-1$ 的**排列**。

定义：小 L 的得分为 $\sum_{1 \leq u,v \leq n} \operatorname{dist}(u,v)$，其中 $\operatorname{dist}(u,v)$ 为在经过必经点 $t$ 的前提下，长度**最小的**从 $u$ 到 $v$ 的路径的长度。

小 L 希望最大化自己的得分，请你解答以下问题：

第一问：求他得分的**最大值**对 $998244353$ 取模的值。

第二问：求若要最大化他的得分，小 L 应该选择的必经点 $t$ 和小 L 每条边应设置的边权。

## 输入格式

一行一个整数 $n$，表示节点数。

接下来 $n-1$ 行，每行两个整数 $u,v$ 表示树上一条连接点 $u$ 和点 $v$ 的边。
## 输出格式

输出共三行。

第一行一个整数，表示【小 L 得分的最大值】对 $998244353$ 取模的值。

第二行一个整数，表示小 L 应该选择的必经点 $t$，如有多种 $t$ 符合题意，请输出最小的 $t$。

第三行 $n-1$ 个整数，**按边的输入顺序**依次给出小 L 每条边应设置的边权。如有多种答案，请输出边权的字典序最小的答案。

注意：在小 L 得分最大的前提下，请首先最小化 $t$，其次最小化边权的字典序。

这里“边权的字典序”是指按边的输入顺序将边的边权看作一个排列，这个排列的字典序。
## 样例

### 样例输入 #1
```
5
1 2
1 3
2 4
2 5
```
### 样例输出 #1
```
280
3
3 4 1 2
```
### 样例输入 #2
```
7
5 1
1 7
6 2
2 1
4 5
3 2
```
### 样例输出 #2
```
1106
4
5 1 2 4 6 3
```
### 样例输入 #3
```
10
3 6
7 3
8 10
5 9
9 1
4 8
1 8
2 3
6 10
```
### 样例输出 #3
```
5240
5
4 1 6 9 8 2 7 3 5
```
### 样例输入 #4
```
10
1 2
1 3
3 4
3 5
2 6
6 7
7 8
8 9
9 10
```
### 样例输出 #4
```
5660
10
4 3 1 2 5 6 7 8 9
```
### 样例输入 #5
```
20
5 18
16 11
6 15
7 14
8 7
10 20
3 4
14 6
9 8
18 11
17 4
11 10
4 11
2 13
13 12
12 15
15 20
19 9
1 8
```
### 样例输出 #5
```
79480
19
1 2 14 16 17 12 3 15 18 7 4 11 9 5 8 10 13 19 6
```
### 样例输入 #6
```
10
7 8
3 2
6 7
2 10
8 3
4 1
9 2
1 3
5 7

```
### 样例输出 #6
```
4340
5
8 6 1 2 7 3 4 5 9 
```
### 样例输入 #7
```
见附件
```
### 样例输出 #7
```
见附件
```
## 提示

**本题采用捆绑测试。**

对于所有数据，$1\le n\le 10^5$。

| 子任务编号 | $n\leq$ | 特殊性质 1 | 特殊性质 2 | 分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $50$ | 否 | 否 | $10$ |
| $1$ | $1000$ | 否 | 否 | $20$ |
| $2$ | $10^5$ | 是 | 否 | $10$ |
| $3$ | $10^5$ | 否 | 是 | $10$ |
| $4$ | $10^5$ | 否 | 否 | $50$ |

特殊性质 1：存在一个对点重标号的方案，使得第 $i$ 条边为 $(1,i+1)$。

特殊性质 2：存在一个对点重标号的方案，使得第 $i$ 条边为 $(i,i+1)$。



---

---
title: "「ZHQOI R1」树图"
layout: "post"
diff: 省选/NOI-
pid: P11956
tag: ['树状数组', 'O2优化', '树的直径', '树论', '洛谷比赛']
---
# 「ZHQOI R1」树图
## 题目背景

树的生成图的生成树的生成图的生成树的生成图的生成树的生成图的生成树的生成图的生成树……
## 题目描述

定义一棵树 $T$ 的生成图 $G$ 为一个无向完全图，其中点 $i$ 与点 $j$ 的边权为 $T$ 中 $i$ 和 $j$ 的距离。

定义一棵树 $T$ 的 $f(T)$ 为 $T$ 的生成图的最大生成树的边权和。

你有一棵以 $1$ 为根的树 $T$，边权全为 $1$，有 $q$ 次操作，每次加一个叶子。你需要在操作前及每次操作后求出 $f(T)$。
## 输入格式

第一行，两个整数 $n,q$。

后 $n-1$ 行，每行两个数 $u,v$，表示一条连接 $u,v$ 的边。

后 $q$ 行，其中第 $i$ 行一个整数 $x$，表示在编号为 $x$ 的点下挂一个编号为 $n+i$ 的点。
## 输出格式

输出 $q+1$ 行，表示操作前及每次操作后的 $f(T)$。
## 样例

### 样例输入 #1
```
6 5
1 2
1 3
1 4 
2 5
2 6
4
3
7
6
8
```
### 样例输出 #1
```
13
19
23
33
41
47
```
## 提示

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据：$1\le n,q\le 2\times 10^5$，保证刚开始给的是一棵树。

| 子任务编号 | $n\le $ | $q\le $ | 特殊性质 | 分数 |
| :-: | :-: | :-: | :-: | :-: |
| 1          | $100$   | $100$   | 无       | $10$ |
| 2          | $2000$  | $2000$  | 无       | $10$ |
| 3          | $2\times 10^5$  | $5$     | 无       | $10$ |
| 4          | $2\times 10^5$  | $2\times 10^5$  | A        | $10$ |
| 5          | $2\times 10^5$  | $2\times 10^5$  | B        | $10$ |
| 6          | $2\times 10^5$  | $2\times 10^5$  | C        | $10$ |
| 7          | $10^5$  | $10^5$  | 无        | $10$ |
| 8          | $2\times 10^5$  | $2\times 10^5$  | 无       | $30$ |

特殊性质 A：保证树一直是一条链。

特殊性质 B：保证每次操作的叶子的父亲都是 $1$。

特殊性质 C：保证树均匀随机生成，每次加的点的父亲从已有的点中均匀随机生成。


---

---
title: "DerrickLo's Brackets (UBC002E)"
layout: "post"
diff: 省选/NOI-
pid: P12182
tag: ['树状数组', 'O2优化']
---
# DerrickLo's Brackets (UBC002E)
## 题目背景

The English statement is provided [here](https://www.luogu.com.cn/problem/U525259). **You must submit your solution only at the Chinese version.**
## 题目描述

DerrickLo 有一个长度为 $n$ 的正整数序列 $a$，以及一个长度为 $n$ 的仅含有 `(` 与 `)` 的字符序列 $t$。他现在要根据这两个序列生成 $q$ 组括号序列，具体地，他会选择两个在 $[1,n]$ 中的正整数 $l,r$ 且 $l\le r$ 并对一个初始为空的字符串 $S$ 进行如下操作：

- 从小到大枚举每个在 $[l,r]$ 之间的正整数 $i$，将 $a_i$ 个 $t_i$ 加到 $S$ 的末尾。

他希望你能在每次他生成了一个括号序列 $S$ 后告诉他 $S$ 的最长合法匹配子串的大小。

合法匹配串的定义如下：

- 空串是合法匹配串。
- 若 $A$ 是合法匹配串，则 $(A)$ 为合法匹配串。
- 若 $A,B$ 都是合法匹配串，则 $AB$ 为合法匹配串。
- 除此以外的所有字符串都不是合法匹配串。
## 输入格式

第一行，两个正整数 $n,q$。

第二行，$n$ 个正整数表示 $a$。

第三行，一个字符串表示 $t$。

接下来 $q$ 行，每行两个正整数表示一次生成中的 $l,r$。
## 输出格式

$q$ 行，每行一个正整数表示答案。
## 样例

### 样例输入 #1
```
3 2
2 3 1
()(
1 3
2 3
```
### 样例输出 #1
```
4
0
```
## 提示

**样例说明**

第一次生成的括号序列为 `(()))(`，它的最长合法匹配子串为 `(())`。

第二次生成的括号序列为 `)))(`，它的最长合法匹配子串为空串。

**数据范围**

$1\le n,q\le 10^6$，$1\le a_i\le 10^9$，每次生成中的 $l,r$ 满足 $1\le l\le r\le n$，$t$ 仅由 `(` 与 `)` 组成。除 $t$ 外所有输入数据为整数。


---

---
title: "[UTS 2024] Remove Node"
layout: "post"
diff: 省选/NOI-
pid: P12563
tag: ['线段树', '树状数组', '2024', 'UOI（乌克兰）']
---
# [UTS 2024] Remove Node
## 题目描述

You have a rooted tree with $n$ vertices, each assigned a value $a_x$. The root is node $1$. 

You can perform operations where you merge two adjacent nodes $x$ and $y$ into a single node $z$, with the value of $z$ being equal to the minimum value between the two nodes. This operation changes edges connected to $x$ or $y$ to be connected to $z$. The cost of this operation is $|a_x - a_y|$. The total cost of multiple operations is the sum of individual operation costs.

For queries, you have two types:
- $1\ x\ y$: This updates the value of node $x$ to $y$.
- $2\ x$: This asks for the minimum cost of operations to reduce the subtree rooted at $x$ to just one node.
## 输入格式

The first line contains a single integer $n$ $(1 \le n \le 200\,000)$, the number of vertices.

The second line contains $n$ integers $a_1, a_2, \dots, a_n$ $(1 \le a_i \le 10^9)$, representing the assigned values of each node.

The third line contains $n-1$ integers $p_2, p_3, \dots, p_n$ ($1 \leq p_i \leq n$), representing the parent of each node.

The fourth line contains one integer $q$ $(1 \le q \le 200\,000)$, representing the total number of queries.

The following $q$ lines each contain a query:

Either $1\ x\ y$ ($1 \leq x \leq n$, $1\leq y \leq 10^9$), or $2\ x$ ($1\leq x \leq n$).
## 输出格式

On each line of the input, you need to print the result of a query of type $2$, in the same order as the order from the input.
## 样例

### 样例输入 #1
```
7
4 7 9 7 4 1 2
1 1 3 2 3 2
1
2 1
```
### 样例输出 #1
```
11
```
### 样例输入 #2
```
7
6 6 5 1 6 6 4
1 1 2 3 3 3
3
2 1
1 1 1
2 1
```
### 样例输出 #2
```
7
11
```
## 提示

- ($4$ points) $n \le 1000, q=1$;
- ($13$ points) $q=1$;
- ($15$ points) the tree is a chain and there are only queries of the second type;
- ($24$ points) there are only queries of the second type;
- ($12$ points) $p_i=1$;
- ($32$ points) no additional constraints.


---

---
title: "[NAC 2025] Humans vs AI"
layout: "post"
diff: 省选/NOI-
pid: P12624
tag: ['线段树', '树状数组', '2025', '分治', 'ST 表', 'ICPC', 'NAC']
---
# [NAC 2025] Humans vs AI
## 题目描述

In the world of rising AI, James is scared of losing his job. So, when his boss asks him to evaluate a new AI model to see how well it performs compared to humans, he wants to make it look as bad as possible.

To test the AI, James conducts a sequence of $N$ trials where a human and an AI are
given the same task and then scored based on their performance on the task. 
He is then going to send the results of some non-empty contiguous subsequence of these trials to his boss and quietly delete the rest.

Let $a_i$ and $h_i$ be the performance of the AI and human on trial $i$, respectively. James's boss evaluates the AI on a sequence of trials by calculating two total scores: one for the humans, and one for the AI. Both scores are initially $0$. For each trial $i$ where $h_i \geq a_i$, the boss awards the humans $h_i-a_i$ points. For each trial where $h_i < a_i$, the AI earns $a_i-h_i$ points.
If the humans' total score is greater than or equal to the AI's total score times some constant $k$ (to account for humans needing food, water, and a desk), James's boss declares that the humans outperform the AI.

James plans to send his chosen subsequence of test results through email to his boss. There is, however, one complication: since AI is already all-knowing and all-pervasive, it intercepts this email and may swap the value of $h_i$ and $a_i$ for one trial $i$ of its choice. (It doesn't want to swap more than one trial result---James might notice!)

Count how many non-empty contiguous subsequences of trial results James could send his boss with the guarantee that humans will be declared to outperform the AI, even if the AI swaps the result of up to one trial.
## 输入格式

The first line of input contains two space-separate integers: $N$ ($1 \leq N \leq 2 \cdot 10^5$), the total number of trials James conducted, and $k$ ($1 \leq k \leq 100$), the multiplier James's boss will apply to the AI's total score to determine whether humans outperform AI.

The second line contains $N$ space-separated integers $h_1, h_2, \ldots, h_N$ ($0 \leq h_i \leq 10^6$), the performance of the humans on each of the $N$ trials.

The third line contains $N$ space-separated integers $a_1, a_2, \ldots, a_N$ ($0 \leq a_i \leq 10^6$), the performance of the AI on the $N$ trials.
## 输出格式

Print the number of non-empty contiguous trial subsequences for which James's boss would declare that humans outperform AI, even if the AI swaps the result of up to one trial.
## 样例

### 样例输入 #1
```
10 2
3 5 7 6 8 6 4 5 2 6
2 4 6 5 4 3 3 6 3 4
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
7 1
4 3 2 1 7 6 5
4 2 3 1 7 6 5
```
### 样例输出 #2
```
11
```


---

---
title: "[JOI Open 2025] 冒泡排序机 / Bubble Sort Machine"
layout: "post"
diff: 省选/NOI-
pid: P12865
tag: ['树状数组', '2025', '排序', '可持久化线段树', 'JOI（日本）']
---
# [JOI Open 2025] 冒泡排序机 / Bubble Sort Machine
## 题目背景

译自 [JOI Open 2025](https://contests.ioi-jp.org/open-2025/index.html) T1「[Bubble Sort Machine](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/cm7aghex)」/ 「[バブルソート機](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/gkrcwais)」。

## 题目描述


JOI 君——一名算法工程师，开发了冒泡排序机。

冒泡排序机操作长为 $N$ 的整数序列 $a=(a_1,a_2,\ldots,a_N)$。为了让机器能工作，给定 $A_i$ 作为 $a_i$（$1\le i\le N$）的初值。每当机器上的**按钮壹**被按下时，机器会按照如下方式修改序列 $a$：

> 对于 $i=1,2,\ldots,N-1$（按此顺序），若 $a_i\gt a_{i+1}$，交换 $a_i,a_{i+1}$ 的值。

为了使冒泡排序机更博人眼球，JOI 君决定加入以下功能：

> 当**按钮贰**被按下时，给定整数 $l,r$ 作为输入（须满足 $1\le l\le r\le N$），机器会输出 $a_{l}+a_{l+1}+\cdots+a_r$ 的值。

给定整数序列的初值和冒泡排序机的操作序列，编程计算按钮贰的输出值。

## 输入格式


输入格式如下所示：

> $N$ \
> $A_1$ $A_2$ $\cdots$ $A_N$ \
> $Q$ \
> $(\text{Query }1)$ \
> $(\text{Query }2)$ \
> $\vdots$ \
> $(\text{Query }Q)$

这里，$Q$ 指的是冒泡排序机的操作数。每个 $(\text{Query }j)$（$1\le j\le Q$）由若干个空格分隔的数字组成。令 $T_j$ 为 $(\text{Query }j)$ 的首个数字。这行的内容为以下二者之一：

- 若 $T_j=1$，这行再没有其他整数了。这意味着冒泡排序机的第 $j$ 次操作按下了按钮壹。
- 若 $T_j=2$，接下来还有两个整数，依次是 $L_j,R_j$。这意味着冒泡排序机的第 $j$ 次操作按下了按钮贰，给定的输入为 $L_j,R_j$。
## 输出格式


对每个按下按钮贰的操作［意思是，对每个满足 $T_j=2$ 的 $j$（$1\le j\le Q$）］，输出一行一个整数，表示冒泡排序机的输出。你的输出应与询问的顺序相符。
## 样例

### 样例输入 #1
```
4
5 3 5 2
6
2 1 3
1
2 1 1
2 2 4
1
2 1 2
```
### 样例输出 #1
```
13
3
12
5
```
### 样例输入 #2
```
5
1 1 2 1 2
5
2 2 3
1
2 2 4
1
2 2 4
```
### 样例输出 #2
```
3
4
4
```
## 提示


### 样例解释

#### 样例 $1$ 解释

初值为 $a_1=5,a_2=3,a_3=5,a_4=2$，$a=(5,3,5,2)$。接下来在冒泡排序机上操作：

1. 按下按钮贰，输入 $l=1,r=3$。机器输出 $a_1+a_2+a_3=13$。
2. 按下按钮壹。对 $i=1,2,3$，按此顺序进行如下操作：
    - $i=1$：由于 $a_1\gt a_2$，交换二者的值，操作后 $a=(3,5,5,2)$。
    - $i=2$：由于并没有 $a_2\gt a_3$，不操作 $a$。
    - $i=3$：由于 $a_3\gt a_4$，交换二者的值，操作后 $a=(3,5,2,5)$。
3. 按下按钮贰，输入 $l=1,r=1$。机器输出 $a_1=3$。
3. 按下按钮贰，输入 $l=2,r=4$。机器输出 $a_2+a_3+a_4=12$。
5. 按下按钮壹。对 $i=1,2,3$，按此顺序进行如下操作：
    - $i=1$：由于并没有 $a_1\gt a_2$，不操作 $a$。
    - $i=2$：由于 $a_2\gt a_3$，交换二者的值，操作后 $a=(3,2,5,5)$。
    - $i=3$：由于并没有 $a_3\gt a_4$，不操作 $a$。
6. 按下按钮贰，输入 $l=1,r=2$。机器输出 $a_1+a_2=5$。

样例 $1$ 满足子任务 $1,5,6$ 的限制。

#### 样例 $2$ 解释

样例 $2$ 满足子任务 $1,3,5,6$ 的限制。


### 数据范围

- $2\le N\le 500\, 000$；
- $1\le A_i\le 10^9\, (1\le i\le N)$；
- $1\le Q\le 500\, 000$；
- $T_j\in \{1,2\}\, (1\le j\le Q)$；
- 若 $T_j=2$，有 $1\le L_j\le R_j\le N\, (1\le j\le Q)$；
- 输入的值都是整数。

### 子任务

- $\text{Subtask 1 (5 pts)}$：满足 $T_j=1$ 的 $j\,(1\le j\le Q)$ 至多有 $10$ 个；
- $\text{Subtask 2 (11 pts)}$：$N,Q\le 150\, 000$，当 $T_j=2$ 时 $L_j=R_j=1\, (1\le j\le Q)$；
- $\text{Subtask 3 (15 pts)}$：$N,Q\le 150\, 000$，$1\le A_i\le 2\, (1\le i\le N)$；
- $\text{Subtask 4 (23 pts)}$：$N,Q\le 150\, 000$，当 $T_j=2$ 时 $L_j=R_j\, (1\le j\le Q)$；
- $\text{Subtask 5 (29 pts)}$：$N,Q\le 150\, 000$；
- $\text{Subtask 6 (17 pts)}$：无额外限制。




---

---
title: "[CERC 2022] Insertions"
layout: "post"
diff: 省选/NOI-
pid: P13812
tag: ['树状数组', '2022', 'KMP 算法', 'ICPC', 'CERC']
---
# [CERC 2022] Insertions
## 题目描述

We are given three strings, $s$, $t$ and $p$. We will denote the length of a string by vertical bars, thus $|s|$ is the length of $s$ and so on. If we insert $t$ into $s$ at position $k$, where $0 \leq k \leq |s|$, the result is a new string consisting of the first $k$ characters of $s$, followed by the entirety of $t$, and finally followed by the remaining $|s| - k$ characters of $s$. We would like to select $k$ so that the resulting new string will contain the largest possible number of occurrences of $p$ as a substring.

Thus, for example, inserting $t = \text{aba}$ into $s = \text{ab}$ at position $k = 0$ results in the string $\text{abaab}$; at $k = 1$, in the string $\text{aabab}$; and at $k = 2$, in the string $\text{ababa}$. If we are interested in occurrences of $p = \text{aba}$, then the best position to insert $t$ into $s$ is $k = 2$, where we get two occurrences: $\text{ababa}$ and $\text{ababa}$ (as this example shows, occurrences of $p$ are allowed to overlap). If, on the other hand, we were interested in occurrences of $p = \text{aa}$, then the best choices of $k$ would be $k = 0$ and $k = 1$, which result in one occurrence of $p$, whereas $k = 2$ results in 0 occurrences of $p$.

## 输入格式

The first line contains the string $s$, the second line the string $t$, and the third line the string $p$.
## 输出格式

Output one line containing the following four integers, separated by spaces:

1. The maximum number of occurrences of $p$ we can get after inserting $t$ into $s$ at position $k$, if we choose the position $k$ wisely.
2. The number of different $k$'s (from the range $0, 1, \ldots, |s|$) where this maximum number of occurrences of $p$ is attained.
3. The minimum value of $k$ where the maximum number of occurrences of $p$ is attained.
4. The maximum value of $k$ where the maximum number of occurrences of $p$ is attained.
## 样例

### 样例输入 #1
```
ab
aba
aba
```
### 样例输出 #1
```
2 1 2 2
```
### 样例输入 #2
```
abaab
aba
ababa
```
### 样例输出 #2
```
1 3 1 5
```
### 样例输入 #3
```
eeoeo
eoe
eeo
```
### 样例输出 #3
```
2 3 1 4
```
## 提示

### Comment

The first of these three examples is the one discussed earlier in the problem statement

### Input limits

- $1 \leq |s| \leq 10^5$
- $1 \leq |t| \leq 10^5$
- $1 \leq |p| \leq 10^5$
- All the strings consist only of lowercase letters of the English alphabet.


---

---
title: "[SDOI2009] 虔诚的墓主人"
layout: "post"
diff: 省选/NOI-
pid: P2154
tag: ['数学', '2009', '各省省选', '树状数组', '山东', '排列组合']
---
# [SDOI2009] 虔诚的墓主人
## 题目描述

小W是一片新造公墓的管理人。公墓可以看成一块 $N×M$ 的矩形，矩形的每个格点，要么种着一棵常青树，要么是一块还没有归属的墓地。

当地的居民都是非常虔诚的基督徒，他们愿意提前为自己找一块合适墓地。为了体现自己对主的真诚，他们希望自己的墓地拥有着较高的虔诚度。

一块墓地的虔诚度是指以这块墓地为中心的十字架的数目。一个十字架可以看成中间是墓地，墓地的正上、正下、正左、正右都有恰好 $k$ 棵常青树。

形式化地，对于一个坐标为 $(x, y)$ 的墓地，以其为中心的十字架个数是这样的长度为 $4k$ 的二元组序列 $[(x_{1,1},y_{1,1}),\allowbreak(x_{1,2},y_{1,2}),\allowbreak\cdots,(x_{1,k},y_{1,k}),\allowbreak(x_{2,1},y_{2,1}),\allowbreak(x_{2,2},y_{2,2}),\allowbreak\cdots,(x_{2,k},y_{2,k}),\allowbreak(x_{3,1},y_{3,1}),\allowbreak(x_{3,2},y_{3,2}),\allowbreak\cdots,(x_{3,k},y_{3,k}),\allowbreak(x_{4,1},y_{4,1}),\allowbreak(x_{4,2},y_{4,2}),\allowbreak\cdots,(x_{4,k},y_{4,k})]$ 的方案数：

- 每一个二元组对应着一棵常青树的坐标；
- $x_{1,1}<x_{1,2}<\cdots< x_{1,k}<x$ 且 $y_{1,1}=y_{1,2}=\cdots=y_{1,k}=y$；
- $x<x_{2,1}<x_{2,2}<\cdots< x_{2,k}$ 且 $y_{2,1}=y_{2,2}=\cdots=y_{2,k}=y$；
- $y_{3,1}<y_{3,2}<\cdots< y_{3,k}<y$ 且 $x_{3,1}=x_{3,2}=\cdots=x_{3,k}=x$；
- $y<y_{4,1}<y_{4,2}<\cdots< y_{4,k}$ 且 $x_{4,1}=x_{4,2}=\cdots=x_{4,k}=x$。

小W希望知道他所管理的这片公墓中所有墓地的虔诚度总和是多少。
## 输入格式

第一行包含两个用空格分隔的正整数 $N$ 和 $M$，表示公墓的宽和长，因此这个矩形公墓共有 $(N+1) ×(M+1)$ 个格点，左下角的坐标为 $(0, 0)$，右上角的坐标为 $(N, M)$。

第二行包含一个正整数 $W$，表示公墓中常青树的个数。

第三行起共 $W$ 行，每行包含两个用空格分隔的非负整数 $x_i$ 和 $y_i$，表示一棵常青树的坐标。输入保证没有两棵常青树拥有相同的坐标。

最后一行包含一个正整数 $k$，意义如题目所示。
## 输出格式

输出仅包含一个非负整数，表示这片公墓中所有墓地的虔诚度总和。为了方便起见，答案对 $2{,}147{,}483{,}648$ 取模。
## 样例

### 样例输入 #1
```
5 6

13

0 2

0 3

1 2

1 3

2 0

2 1

2 4

2 5

2 6

3 2

3 3

4 3

5 2

2
```
### 样例输出 #1
```
6
```
## 提示

图中，以墓地 $(2, 2)$ 和 $(2, 3)$ 为中心的十字架各有 $3$ 个，即它们的虔诚度均为 $3$。其他墓地的虔诚度为 $0$。

 ![](https://cdn.luogu.com.cn/upload/pic/1589.png) 

对于 $30\%$ 的数据，满足 $1 ≤ N, M ≤ 10^3$。

对于 $60\%$ 的数据，满足 $1 ≤ N, M ≤ 10^6$。

对于 $100\%$ 的数据，满足 $1 ≤ N, M ≤ 10^9$，$0 ≤ x_i ≤ N$，$0 ≤ y_i ≤ M$，$1 ≤ W ≤ 10^5$，$1 ≤ k ≤ 10$。

存在 $50\%$ 的数据，满足 $1 ≤ k ≤ 2$。

存在 $25\%$ 的数据，满足 $1 ≤ W ≤ 10^4$。


---

---
title: "[HNOI2005] 数三角形"
layout: "post"
diff: 省选/NOI-
pid: P2315
tag: ['2005', '各省省选', '树状数组', '湖南', '枚举']
---
# [HNOI2005] 数三角形
## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1355.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/pic/1356.png)

## 输出格式

输出文件output.txt中仅包含一个整数T，表示有多少个三角形的边界都没有被删除。

## 样例

### 样例输入 #1
```
5

1 1 1

1 1 0 1 1 0

1 1 1 1 1 1 1 0 1

1 0 1 1 1 1 0 1 1 1 1 1

0 1 1 1 1 1 0 1 1 1 1 1 0 1 1


```
### 样例输出 #1
```
19
```


---

---
title: "[SDOI2011] 拦截导弹"
layout: "post"
diff: 省选/NOI-
pid: P2487
tag: ['动态规划 DP', '2011', '各省省选', '树状数组', '山东', 'Special Judge', '分治']
---
# [SDOI2011] 拦截导弹
## 题目描述

某国为了防御敌国的导弹袭击，发展出一种导弹拦截系统。但是这种导弹拦截系统有一个缺陷：虽然它的第一发炮弹能够到达任意的高度、并且能够拦截任意速度的导弹，但是以后每一发炮弹都不能高于前一发的高度，其拦截的导弹的飞行速度也不能大于前一发。某天，雷达捕捉到敌国的导弹来袭。由于该系统还在试用阶段，所以只有一套系统，因此有可能不能拦截所有的导弹。

在不能拦截所有的导弹的情况下，我们当然要选择使国家损失最小、也就是拦截导弹的数量最多的方案。但是拦截导弹数量的最多的方案有可能有多个，如果有多个最优方案，那么我们会随机选取一个作为最终的拦截导弹行动蓝图。

我方间谍已经获取了所有敌军导弹的高度和速度，你的任务是计算出在执行上述决策时，每枚导弹被拦截掉的概率。

## 输入格式



第一行包含一个正整数 $n$，表示敌军导弹数量。

下面 $n$ 行按顺序给出了敌军所有导弹信息。第 $i+1$
 行包含两个正整数 $h_i$ 和 $v_i$，分别表示第 $i$ 枚导弹的高度和速度。
## 输出格式



输出包含两行。

第一行为一个正整数，表示最多能拦截掉的导弹数量；

第二行包含 $n$ 个 $0$ 到 $1$ 之间的实数，第 $i$ 个数字表示第 $i$ 枚导弹被拦截的概率（你可以保留任意多位有效数字）。
## 样例

### 样例输入 #1
```
4
3 30
4 40
6 60
3 30

```
### 样例输出 #1
```
2
0.33333 0.33333 0.33333 1.00000

```
## 提示



保证总方案数不超过 C++ 中 double 类型的存储范围。

### 数据范围及约定

- 均匀分布着约 $30\%$ 的数据，所有 $v_i$ 均相等；
- 均匀分布着约 $50\%$ 的数据，满足 $1\le h_i,v_i\le 1000$。
- 对于 $30\%$ 的数据，满足 $1\le n\le 1000$；
- 对于 $100\%$ 的数据，$1\le n\le 5\times 10^4$，$1\le h_i,v_i\le 10^9$。

### 评分标准

对于每个测试点，若输出的第一行与标准输出相同，则得到该测试点 $40\%$ 的分数，若输出文件的第二行的每个数与标准输出的误差均不大于 $10^{-4}$，则得到该测试点 $60\%$ 的分数，两项相加作为该测试点总得分。


---

---
title: "[CQOI2011] 动态逆序对"
layout: "post"
diff: 省选/NOI-
pid: P3157
tag: ['2011', '重庆', '各省省选', '树状数组', 'cdq 分治', '可持久化线段树']
---
# [CQOI2011] 动态逆序对
## 题目描述

对于序列 $a$，它的逆序对数定义为集合  
$$\{(i,j)| i<j \wedge a_i > a_j \}$$
中的元素个数。  

现在给出 $1\sim n$ 的一个排列，按照某种顺序依次删除 $m$ 个元素，你的任务是在每次删除一个元素**之前**统计整个序列的逆序对数。

## 输入格式

第一行包含两个整数 $n$ 和 $m$，即初始元素的个数和删除的元素个数。  
以下 $n$ 行，每行包含一个 $1 \sim n$ 之间的正整数，即初始排列。  
接下来 $m$ 行，每行一个正整数，依次为每次删除的元素。

## 输出格式

输出包含 $m$ 行，依次为删除每个元素之前，逆序对的个数。

## 样例

### 样例输入 #1
```
5 4
1
5
3
4
2
5
1
4
2
```
### 样例输出 #1
```
5
2
2
1
```
## 提示

【数据范围】   
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le m \le 50000$。

【样例解释】  
删除每个元素之前的序列依次为：  
$$1,5,3,4,2$$  
$$1,3,4,2$$  
$$3,4,2$$  
$$3,2$$  


---

---
title: "[SCOI2014] 方伯伯的玉米田"
layout: "post"
diff: 省选/NOI-
pid: P3287
tag: ['动态规划 DP', '2014', '四川', '树状数组', 'O2优化']
---
# [SCOI2014] 方伯伯的玉米田
## 题目描述

方伯伯在自己的农田边散步，他突然发现田里的一排玉米非常的不美。这排玉米一共有 $N$ 株，它们的高度参差不齐。方伯伯认为单调不下降序列很美，所以他决定先把一些玉米拔高，再把破坏美感的玉米拔除掉，使得剩下的玉米的高度构成一个单调不下降序列。方伯伯可以选择一个区间，把这个区间的玉米全部拔高 $1$ 单位高度，他可以进行最多 $K$ 次这样的操作。拔玉米则可以随意选择一个集合的玉米拔掉。问能最多剩多少株玉米，来构成一排美丽的玉米。
## 输入格式

第一行包含两个整数 $n, K$，分别表示这排玉米的数目以及最多可进行多少次操作。第二行包含 $n$ 个整数，第 $i$ 个数表示这排玉米，从左到右第 $i$ 株玉米的高度 $a_i$。
## 输出格式

输出一个整数，最多剩下的玉米数。

## 样例

### 样例输入 #1
```
3 1
2 1 3
```
### 样例输出 #1
```
3
```
## 提示

$100\%$ 的数据满足：$2 \le N \lt 10^4 $，$2 \le K \le 500$，$1 \leq a_i \leq 5000$。


---

---
title: "[POI 2007] TET-Tetris Attack"
layout: "post"
diff: 省选/NOI-
pid: P3460
tag: ['贪心', '2007', '树状数组', 'POI（波兰）', 'Special Judge', '栈']
---
# [POI 2007] TET-Tetris Attack
## 题目描述

一种名为 *Tetris Attack* 的猜谜游戏风靡 Byteotia。游戏本身非常复杂，因此我们只介绍它的简化规则：

玩家拥有一个有 $2n$ 个元素的栈，一个元素放置在另一个元素上，这样一个组合有 $n$ 个不同的符号标记。对于每个符号，栈中恰好有两个元素用一个符号标记。

玩家可以交换两个相邻元素，即互换他们的位置。交换后，如果有两个相邻的元素标有相同的符号，则将他们都从栈中删除。然后，位于其上方的所有元素都会掉落下来，并且可以造成再次删除。

玩家的目标是以最少的移动次数清空堆栈。请你编写一个程序，找出最少的移动次数及方案。
## 输入格式

第一行一个整数 $n$。

接下来的 $2n$ 行里给出了栈的初始内容，第 $i+1$ 行包含一个整数 $a_i$（$1 \leq a_i \leq n $），表示从底部数起第 $i$ 个元素所标记的符号（每个符号都在栈中出现正好两次）。

最初不存在相邻的两个元素符号相同的情况，保证有不超过 $10^6$ 次操作的方案。
## 输出格式

第一行一个整数 $m$ ，表示最小的移动次数。

接下来 $m$ 行，每行输出一个数。

第 $i + 1$ 行输出 $p_i$，即表示玩家在第 $i$ 步时选择交换 $p_i$ 与 $p_{i+1}$。

如果存在多个方案，则输出其中任何一个。
## 样例

### 样例输入 #1
```
5
5
2
3
1
4
1
4
3
5
2
```
### 样例输出 #1
```
2
5
2
```
## 提示

$1 \le n \le 50000$


---

---
title: "[POI 2011] MET-Meteors"
layout: "post"
diff: 省选/NOI-
pid: P3527
tag: ['2011', '二分', '树状数组', 'POI（波兰）', 'O2优化', '整体二分', '离线处理']
---
# [POI 2011] MET-Meteors
## 题目描述

Byteotian Interstellar Union (BIU) has recently discovered a new planet in a nearby galaxy.  The planet is unsuitable for colonisation due to strange  meteor showers, which on the other hand make it an exceptionally interesting  object of study.

The member states of BIU have already placed space stations close to the  planet's orbit.  The stations' goal is to take samples of the rocks flying by.

The BIU Commission has partitioned the orbit into $m$ sectors, numbered  from $1$ to $m$, where the sectors $1$ and $m$ are adjacent.  In each sector  there is a single space station, belonging to one of the $n$ member states.

Each state has declared a number of meteor samples it intends to gather before  the mission ends.  Your task is to determine, for each state, when it can  stop taking samples, based on the meter shower predictions for the years to  come.



## 输入格式

The first line of the standard input gives two integers, $n$ and $m$ ($1\le n,m\le 300\ 000$), separated by a single space, that denote,respectively, the number of BIU member states and the number of sectors    the orbit has been partitioned into.

In the second line there are $m$ integers $o_i$ ($1\le o_i\le n$),separated by single spaces, that denote the states owning stations in    successive sectors.

In the third line there are $n$ integers $p_i$ ($1\le p_i\le 10^9$),separated by single spaces, that denote the numbers of meteor samples that the successive states intend to gather.

In the fourth line there is a single integer $k$ ($1\le k\le 300\ 000$) that denotes the number of meteor showers predictions. The following $k$ lines specify the (predicted) meteor showers chronologically. The $i$-th of these lines holds three integers $l_i,r_i,a_i$ (separated by single spaces), which denote that a meteor shower is expected in sectors $l_i,l_{i+1},...,r_i$(if $l_i\le r_i$) or sectors $l_i,l_{i+1},...,m,1,...,r_i$ (if $l_i>r_i$) , which should provide each station in those sectors with $a_i$ meteor samples ($1\le a_i\le 10^9$).

## 输出格式

Your program should print $n$ lines on the standard output.

The $i$-th of them should contain a single integer $w_i$, denoting the number of shower after which the stations belonging to the $i$-th state are    expected to gather at least $p_i$ samples, or the word NIE (Polish for no) if that state is not expected to gather enough samples in the foreseeable future.

## 样例

### 样例输入 #1
```
3 5
1 3 2 1 3
10 5 7
3
4 2 4
1 3 1
3 5 2
```
### 样例输出 #1
```
3
NIE
1
```
## 题目翻译

Byteotian Interstellar Union 

有 $n​$ 个成员国。现在它发现了一颗新的星球，这颗星球的轨道被分为 $m​$ 份（第 $m​$ 份和第 $1​$ 份相邻），第 $i​$ 份上有第 $a_i​$ 个国家的太空站。

这个星球经常会下陨石雨。BIU 已经预测了接下来 $k$ 场陨石雨的情况。

BIU 的第 $i$ 个成员国希望能够收集 $p_i$ 单位的陨石样本。你的任务是判断对于每个国家，它需要在第几次陨石雨之后，才能收集足够的陨石。

#### 输入格式

第一行是两个数 $n,m$。

第二行有 $m$ 个数，第 $i$ 个数 $o_i$ 表示第 $i$ 段轨道上有第 $o_i$ 个国家的太空站。

第三行有 $n$ 个数，第 $i$ 个数 $p_i$ 表示第 $i$ 个国家希望收集的陨石数量。

第四行有一个数 $k$，表示 BIU 预测了接下来的 $k$ 场陨石雨。 接下来 $k$ 行，每行有三个数 $l_i,r_i,a_i$ ，表示第 $k$ 场陨石雨的发生地点在从 $l_i$ 顺时针到 $r_i$ 的区间中（如果 $l_i \leq r_i$，则是 $l_i, l_i + 1 
\cdots, r_i$，否则就是 $l_i, l_i + 1, 
\cdots m - 1, m, 1, 2, \cdots r_i$），向区间中的每个太空站提供 $a_i$ 单位的陨石样本。

#### 输出格式

输出 $n$ 行。第 $i$ 行的数 $w_i$ 表示第 $i$ 个国家在第 $w_i$ 波陨石雨之后能够收集到足够的陨石样本。如果到第 $k$ 波结束后仍然收集不到，输出 `NIE`。

#### 数据范围

$1\le n,m,k\le 3\cdot10^5$；

$1\le p_i,a_i\le 10^9$；


---

---
title: "[POI 2014] ZAL-Freight"
layout: "post"
diff: 省选/NOI-
pid: P3580
tag: ['动态规划 DP', '2014', '二分', '树状数组', 'POI（波兰）']
---
# [POI 2014] ZAL-Freight
## 题目描述

The train stations in Upper Bytown and Lower Bytown are connected with a single track rail link.

It takes the train $s$ minutes to travel between them in either direction.

However, the trains departing a station have to be spaced at least one minute apart.

Moreover, at all times, all the trains on the rail link have to go in the same direction.

According to the timetable at our disposal, $n$ cargo trains destined for Lower Bytown are to pass  through the Upper Bytown.  They are to be loaded with goods in Lower Bytown and then return to  Upper Bytown.  For simplicity, we assume that loading the goods on the train takes virtually no time.

We are to determine the minimum possible time of the last train returning to Upper Bytown.

有两个城镇，从A到B需要的时间为S，然后有N辆列车需要从A到B再回来，任何时刻铁路上只能有向着同一个方向前进的列车，然后每辆列车有一个从A出发的最早出站时间，问所有列车全部回到A站的最早时间

## 输入格式

The first line of the standard input contains two integers $n$, $s$($1\le n\le 1\ 000\ 000$, $1\le s\le 10^9$),    separated by a single space, that specify the number of trains and the one-way travel time respectively.

The second line contains $n$ integers $t_1,t_2,\cdots,t_n$ ($0\le t_1\le t_2\le\cdots\le t_n\le 10^9$),separated by a single space, that specify the arrival times of successive trains at the Upper Bytown station.

## 输出格式

Your program should print out a single line with a single integer to the standard output:

the minimum possible time of the last train returning to Upper Bytown.

## 样例

### 样例输入 #1
```
3 4
1 8 11

```
### 样例输出 #1
```
20

```
## 提示



## 题目翻译

Upper Bytown和Lower Bytown的火车站通过一条轨道铁路连接。

沿任何一个方向在它们之间行驶都需要s分钟。

但是，离开车站的火车必须至少间隔一分钟。

而且，在任何时候，铁路上的所有列车都必须朝同一方向行驶。

根据我们的时间表，前往下拜镇的n列货运列车将通过上拜镇。 他们将在下拜敦装载货物，然后返回上拜敦。 为简单起见，我们假设将货物装载到火车上几乎不需要时间。

我们将确定最后一班火车返回Upper Bytown的最短时间。

**两个车站发车都必须至少间隔一分钟。**


---

---
title: "[POI 2015] LOG"
layout: "post"
diff: 省选/NOI-
pid: P3586
tag: ['2015', '树状数组', 'POI（波兰）']
---
# [POI 2015] LOG
## 题目描述

维护一个长度为 $n$ 的序列，一开始都是 $0$，支持以下两种操作：

1. `U k a` 将序列中第 $k$ 个数修改为 $a$。
2. `Z c s` 在这个序列上，每次选出 $c$ 个正数，并将它们都减去 $1$，询问能否进行 $s$ 次操作。

每次询问独立，即每次询问不会对序列进行修改。

## 输入格式

第一行包含两个正整数 $n,m$，分别表示序列长度和操作次数。

接下来 $m$ 行为 $m$ 个操作。
## 输出格式

包含若干行，对于每个 `Z` 询问，若可行，输出 `TAK`，否则输出 `NIE`。
## 样例

### 样例输入 #1
```
3 8
U 1 5
U 2 7
Z 2 6
U 3 1
Z 2 6
U 2 2
Z 2 6
Z 2 1

```
### 样例输出 #1
```
NIE
TAK
NIE
TAK

```
## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1\leq n,m\leq 10^6$，$1\leq k,c\leq n$，$0\leq a\leq 10^9$，$1\leq s\leq 10^9$。

----

原题名称：Logistyka。


---

---
title: "[POI 2015] TRZ"
layout: "post"
diff: 省选/NOI-
pid: P3590
tag: ['2015', '线段树', '树状数组', 'POI（波兰）']
---
# [POI 2015] TRZ
## 题目描述

给定一个长度为 $n$ 的仅包含 $\texttt B$、$\texttt C$、$\texttt S$ 三种字符的字符串，请找到最长的一段连续子串，使得这一段要么只有一种字符，要么有多种字符，但是没有任意两种字符出现次数相同。
## 输入格式

第一行包含一个正整数 $n$（$1\leq n\leq 10^6$），表示字符串的长度。

第二行一个长度为 $n$ 的字符串。
## 输出格式

包含一行一个正整数，即最长的满足条件的子串的长度。
## 样例

### 样例输入 #1
```
9
CBBSSBCSC
```
### 样例输出 #1
```
6
```
## 提示

**【样例解释】**

选择 $\texttt {BSSBCS}$ 这个子串。

----

原题名称：Trzy wieże。


---

---
title: "富金森林公园"
layout: "post"
diff: 省选/NOI-
pid: P3616
tag: ['线段树', '树状数组', '离散化', '概率论', '洛谷月赛']
---
# 富金森林公园
## 题目描述

博艾的富金森林公园里有一个长长的富金山脉，山脉是由一块块巨石并列构成的，编号从 $1$ 到 $N$ 。每一个巨石有一个海拔高度。而这个山脉又在一个盆地中，盆地里可能会积水，积水也有一个海拔高度，所有**严格低于**这个海拔高度的巨石，就会在水面下隐藏。


由于地壳运动，巨石的海拔高度可能会随时变化，每次一块的巨石会变成新的海拔高度。当然，水面的高度也会随时发生变化。


因为有这样奇妙的地质奇观，吸引了很多游客来游玩。uim 作为一个游客，可以告诉你此时水位海拔，你得告诉他，能看到有几个连续露出水面的部分。（与水面持平我们也认为是露出）
## 输入格式

第一行两个整数 $N$ 和 $M$,分别表示 $N$ 块石头，$M$ 个询问。

接下来一行，$N$ 个整数 $A_i$ 表示每个巨石的初始海拔。

接下来 $M$ 行，每行有两个或者三个数，每一行如果第一个数是 `1`，那么后面跟一个 $B_j$，表示水面海拔。如果第一个数是 `2`，后面跟两个整数，$C_j$ 和 $D_j$，表示编号 $C_j$ 的巨石海拔变为 $D_j$。
## 输出格式

对于每个 `1` 询问，给出一个整数答案，也就是露出了几部分的山峰。
## 样例

### 样例输入 #1
```
5 4
8 6 3 5 4
1 5
2 4 1
1 5
1 3
```
### 样例输出 #1
```
2
1
2
```
## 提示

$10\%$ 的数据，$N,M<=2000$。

另外 $30\%$ 的数据， 只有 `1` 的询问。

$100\%$ 的数据，$1<=N,M<=200000,1<=A_i,B_j,D_j<=10^9$，一定有 `1` 询问。



---

---
title: "[USACO17FEB] Why Did the Cow Cross the Road II P"
layout: "post"
diff: 省选/NOI-
pid: P3657
tag: ['2017', 'USACO', '树状数组', '离散化', '枚举']
---
# [USACO17FEB] Why Did the Cow Cross the Road II P
## 题目背景

*本题与 [金组同名题目](/problem/P6119) 在题意上一致，唯一的差别是数据范围。*
## 题目描述

Farmer John 饲养了 $N$ 种奶牛，编号从 $1$ 到 $N$。一些品种的奶牛和其他奶牛间相处良好，事实证明，如果两个品种的奶牛编号分别为 $a,b$，当 $|a-b| \leq 4$ 时，这两个品种的奶牛能友好相处，否则不能友好相处。

一条长长的道路贯穿整个农场，道路的左侧有 $N$ 个牧场（每个品种的奶牛恰好占据一个牧场），道路的右侧也有 $N$ 个牧场（每个品种的奶牛恰好占据一个牧场）。为了让奶牛们安全穿过马路，Farmer John 希望能在马路上画出一些人行道（牛行道？），要求这些人行道满足如下条件：

1. 人行道从左侧的某个牧场出发，连接到右侧的某个牧场；
2. 人行道连接的两个牧场的奶牛要能友好相处；
3. 人行道不能在道路中间相交；
4. 每个牧场只能与一条人行道相连。

你需要帮 FJ 求出最多能有多少条人行道。
## 输入格式

输入第一行一个整数 $N$（$1 \leq N \leq 10^5$）。

接下来 $N$ 行，每行一个整数 $a_i$，代表道路左侧第 $i$ 个牧场的奶牛品种编号。

接下来 $N$ 行，每行一个整数 $b_i$，代表道路右侧第 $i$ 个牧场的奶牛品种编号。
## 输出格式

输出最多能画多少条人行道。
## 样例

### 样例输入 #1
```
6
1
2
3
4
5
6
6
5
4
3
2
1
```
### 样例输出 #1
```
5

```


---

---
title: "[USACO17FEB] Why Did the Cow Cross the Road III P"
layout: "post"
diff: 省选/NOI-
pid: P3658
tag: ['2017', 'USACO', '树状数组', 'cdq 分治']
---
# [USACO17FEB] Why Did the Cow Cross the Road III P
## 题目描述

Farmer John is continuing to ponder the issue of cows crossing the road through his farm, introduced in the preceding two problems. He realizes now that the threshold for friendliness is a bit more subtle than he previously considered -- breeds $a$ and $b$ are now friendly if $|a - b| \leq K$, and unfriendly otherwise.
Given the orderings of fields on either side of the road through FJ's farm, please count the number of unfriendly crossing pairs of breeds, where a crossing pair of breeds is defined as in the preceding problems.


## 输入格式

The first line of input contains $N$ ($1 \leq N \leq 100,000$) and $K$ ($0 \leq K < N$). The next $N$ lines describe the order, by breed ID, of fields on one side of the road; each breed ID is an integer in the range $1 \ldots N$. The last $N$ lines describe the order, by breed ID, of the fields on the other side of the road. Each breed ID appears exactly once in each ordering.

## 输出格式

Please output the number of unfriendly crossing pairs of breeds.


## 样例

### 样例输入 #1
```
4 1
4
3
2
1
1
4
2
3
```
### 样例输出 #1
```
2
```
## 提示

In this example, breeds 1 and 4 are unfriendly and crossing, as are breeds 1 and 3.


## 题目翻译

### 题目描述

Farmer John 继续思考奶牛穿过他农场道路的问题，这个问题在前两个问题中已经介绍过。他现在意识到，友好度的阈值比他之前考虑的要微妙一些——现在，品种 $a$ 和 $b$ 是友好的当且仅当 $|a - b| \leq K$，否则就是不友好的。给定 FJ 农场道路两侧田地的品种顺序，请计算不友好的交叉品种对的数量，其中交叉品种对的定义与前两个问题相同。

### 输入格式

输入的第一行包含 $N$ ($1 \leq N \leq 100,000$) 和 $K$ ($0 \leq K < N$)。接下来的 $N$ 行描述了道路一侧田地的品种顺序；每个品种 ID 是一个在 $1 \ldots N$ 范围内的整数。最后的 $N$ 行描述了道路另一侧田地的品种顺序。每个品种 ID 在每个顺序中恰好出现一次。

### 输出格式

请输出不友好的交叉品种对的数量。

### 说明/提示

在这个例子中，品种 1 和 4 是不友好的且交叉的，品种 1 和 3 也是不友好的且交叉的。


---

---
title: "[ZJOI2017] 树状数组"
layout: "post"
diff: 省选/NOI-
pid: P3688
tag: ['2017', '线段树', '各省省选', '树状数组', '浙江']
---
# [ZJOI2017] 树状数组
## 题目描述

漆黑的晚上，九条可怜躺在床上辗转反侧。难以入眠的她想起了若干年前她的一次悲惨的 OI 比赛经历。那是一道基础的树状数组题。

给出一个长度为 $n$ 的数组 $A$，初始值都为 $0$，接下来进行 $m$ 次操作，操作有两种：

* $1\ x$，表示将 $A_x$  变成 $(A_x + 1) \bmod 2$。
* $2\ l\ r$，表示询问 $(\sum_{i=l}^r A_i) \bmod 2$。

尽管那个时候的可怜非常的 simple，但是她还是发现这题可以用树状数组做。当时非常 young 的她写了如下的算法：

![](https://cdn.luogu.com.cn/upload/pic/4744.png)

其中 $\mathrm{lowbit}(x)$ 表示数字 $x$ **最低**的非 $0$ 二进制位，例如 $\text{lowbit}(5) = 1, \text{lowbit}(12) = 4$。进行第一类操作的时候就调用 $\mathrm{Add}(x)$，第二类操作的时候答案就是 $\mathrm{Query}(l, r)$。

如果你对树状数组比较熟悉，不难发现可怜把树状数组写错了：**$\text{Add}$ 和 $\text{Find}$ 中 $x$  变化的方向反了**。因此这个程序在最终测试时华丽的爆 0 了。

然而奇怪的是，在当时，这个程序通过了出题人给出的大样例——这也是可怜没有进行对拍的原因。

现在，可怜想要算一下，这个程序回答对每一个询问的概率是多少，这样她就可以再次的感受到自己是一个多么非的人了。然而时间已经过去了很多年，即使是可怜也没有办法完全回忆起当时的大样例。幸运的是，她回忆起了大部分内容，唯一遗忘的是每一次第一类操作的 $x$ 的值，因此她假定这次操作的 $x$ 是在 $[l_i, r_i]$  范围内**等概率随机**的。

具体来说，可怜给出了一个长度为 $n$ 的数组 $A$，初始为 $0$，接下来进行了 $m$ 次操作：

* $1\ l\ r$，表示在区间 $[l, r]$ 中等概率选取一个 $x$ 并执行 $\text{Add}(x)$ 。

* $2\ l\ r$，表示询问执行 $\text{Query}(l, r)$ 得到的结果是正确的概率是多少。
## 输入格式

第一行输入两个整数 $n,m$。

接下来 $m$ 行每行描述一个操作，格式如题目中所示。

## 输出格式

对于每组询问，输出一个整数表示答案。如果答案化为最简分数后形如 $\frac x y$，那么你只需要输出 $x\times y^{-1} \bmod 998244353$ 后的值（即输出答案模 $998244353$）。
## 样例

### 样例输入 #1
```
5 5
1 3 3
2 3 5
2 4 5
1 1 3
2 2 5
```
### 样例输出 #1
```
1
0
665496236
```
## 提示

#### 样例说明

在进行完 $\mathrm{Add}(3)$ 之后，$A$ 数组变成了 $[0, 1, 1, 0, 0]$。所以前两次询问可怜的程序答案都是 $1$，因此第一次询问可怜一定正确，第二次询问可怜一定错误。

#### 数据范围

| 测试点编号 |        $n$         |              $m$               |      其他约定      |
| :--------: | :----------------: | :----------------------------: | :----------------: |
|    $1$     |      $\le 5$       |            $\le 10$            |         无         |
|    $2$     |      $\le 50$      |      $\le 50$      |         无         |
|    $3$     |      $\le 50$      |      $\le 50$      |         无         |
|    $4$     | $\le 3\times 10^3$ | $\le 3\times 10^3$ |         无         |
|    $5$     | $\le 3\times 10^3$ | $\le 3\times 10^3$ |         无         |
|    $6$     |       $10^5$       |       $10^5$       | 所有询问都在修改后 |
|    $7$     |       $10^5$       |       $10^5$       | 所有询问都在修改后 |
|    $8$     |       $10^5$       |       $10^5$       |         无         |
|    $9$     |       $10^5$       |       $10^5$       |         无         |
|    $10$    |       $10^5$       |       $10^5$       |         无         |


对于 $100\%$ 的数据，保证 $1\leq l\leq r\leq n$。

更新：2018/05/13 @larryzhong 提供了 5 组强的数据。


---

---
title: "[TJOI2017] 异或和"
layout: "post"
diff: 省选/NOI-
pid: P3760
tag: ['2017', '各省省选', '树状数组', '进制', '前缀和', '天津']
---
# [TJOI2017] 异或和
## 题目描述

在加里敦中学的小明最近爱上了数学竞赛，很多数学竞赛的题都是与序列的连续和相关的。  所以对于一个序列，求出它们所有的连续和来说，小明觉得十分的简单。  

但今天小明遇到了一个序列和的难题，这个题目不仅要求你快速的求出所有的连续和（即子串和），还要快速的求出这些连续和的异或值。  

小明很快的就求出了所有的连续和，但是小明要考考你，在不告诉连续和的情况下，让你快速求是序列所有连续和的异或值。

## 输入格式

第一行输入一个 $n$，表示这序列的数序列。

第二行输入 $n$ 个非负整数 $a_1,a_2 \dots a_n$ 代表这个序列。
## 输出格式

输出这个序列所有的连续和的异或值。

## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
0
```
## 提示

【样例解释】

序列 $[1,2,3]$ 有 $6$ 个连续和，它们分别是 $1,2,3,3,5,6$，而 $1 \text{ xor } 2 \text{ xor } 3 \text{ xor } 3 \text{ xor } 5 \text{ xor } 6 = 0$。

【数据范围】

- 对于 $20\%$ 的数据，$1\le n \le 100$；
- 对于 $100\%$ 的数据，$1\le n \le 10^5$，$\sum a_i \le 10^6$。



---

---
title: "【模板】三维偏序（陌上花开）"
layout: "post"
diff: 省选/NOI-
pid: P3810
tag: ['树状数组', 'cdq 分治', 'O2优化', '分治', '排序', '整体二分', 'K-D Tree']
---
# 【模板】三维偏序（陌上花开）
## 题目背景

这是一道模板题，可以使用 bitset，CDQ 分治，KD-Tree 等方式解决。
## 题目描述

有 $ n $ 个元素，第 $ i $ 个元素有 $ a_i,b_i,c_i $ 三个属性，设 $ f(i) $ 表示满足 $ a_j \leq a_i $ 且 $ b_j \leq b_i $ 且 $ c_j \leq c_i $ 且 $ j \ne i $ 的 $j$ 的数量。

对于 $ d \in [0, n) $，求 $ f(i) = d $ 的数量。
## 输入格式

第一行两个整数 $ n,k $，表示元素数量和最大属性值。

接下来 $ n $ 行，每行三个整数 $ a_i ,b_i,c_i $，分别表示三个属性值。
## 输出格式

$ n $ 行，第 $ d + 1 $ 行表示 $ f(i) = d $ 的 $ i $ 的数量。
## 样例

### 样例输入 #1
```
10 3
3 3 3
2 3 3
2 3 1
3 1 1
3 1 2
1 3 1
1 1 2
1 2 2
1 3 2
1 2 1

```
### 样例输出 #1
```
3
1
3
0
1
0
1
0
0
1

```
## 提示

$ 1 \leq n \leq 10^5$，$1 \leq a_i, b_i, c_i \le k \leq 2 \times 10^5 $。



---

---
title: "aaa被续"
layout: "post"
diff: 省选/NOI-
pid: P3925
tag: ['线段树', '树状数组', '洛谷原创', 'O2优化', '树链剖分', '洛谷月赛']
---
# aaa被续
## 题目背景

HansBug持续无聊ing

## 题目描述

由于aaa没有完成HansBug的任务。所以HansBug开始计划着如何续aaa。

现在HansBug手里有 $ N $个aaa，每个aaa有一个码力值。一共存在 $ N - 1 $条连接两个aaa的边，故这 $ N $个aaa构成一棵**有根树**，根为1号aaa。

现在HansBug想要续了这 $ N $个aaa。HansBug所采用的策略是，对于第 $ i$个aaa，先让他和他的各级子aaa们~~乖乖♂站好~~成一队，然后依次续掉。

经过长期对于aaa码力值的研究，HansBug发现，**对于每一队aaa**，设有 $n$个，码力值依次为$ v_i $，则续了队伍里的第 $ i $个aaa所能获得的码力值为 $ v_1 + v_2 + \cdots + v_i $。


然而，aaa之间的关系树相当的复杂，HansBug的智商早已不够用，于是这个任务就交给了你。不过HansBug知道，任何一个aaa都不会有超过5个的直接子aaa

HansBug想要知道在每次排♂队方法最优的情况下，续了这些aaa最多可以获得的码力值~~，事成之后分给你100000 % 10点码力值~~。

## 输入格式

第一行包含一个正整数 $ N $，表示aaa的个数。

接下来 $ N-1 $行，每行包含两个正整数 $ u, v$，代表第 $u $个aaa和第 $ v $个aaa之间存在从属关系（最高级别的aaa编号为 $ 1$）

最后一行包含 $ N $个非负整数，依次代表第 $ i $个aaa的码力值。

## 输出格式

输出包含一个整数，打表HansBug续掉全部的aaa之后最多能获得的码力值。

**由于结果较大，所以请对 $ 1000000007 $ 取模 （$ {10} ^ 9 + 7 $）**

## 样例

### 样例输入 #1
```
5
5 3
1 2
1 5
4 5
3 9 10 4 7 

```
### 样例输出 #1
```
189

```
## 提示

**样例解释：**

 ![](https://cdn.luogu.com.cn/upload/pic/7980.png) 

故续了5个aaa所得的最大总码力值为：118 + 9 + 10 + 4 + 48 = 189

**对1000000007取模后得到答案189**


**数据范围：**

对于30%的数据：$ 1 \leq N \leq 3 \cdot {10}^3 $

对于50%的数据：$ 1 \leq N \leq 2 \cdot {10}^4 $

对于70%的数据：$ 1 \leq N \leq {10}^5 $

对于100%的数据：$ 1 \leq N \leq 5 \cdot {10}^5 $

对于每一个aaa的码力值 $ a_i $，保证 $ 0 \leq a_i \leq {10}^8 $



---

---
title: "SAC E#1 - 一道简单题 Sequence2"
layout: "post"
diff: 省选/NOI-
pid: P3928
tag: ['线段树', '树状数组', '离散化', '洛谷原创', 'O2优化', '洛谷月赛']
---
# SAC E#1 - 一道简单题 Sequence2
## 题目背景

小强和阿米巴是好朋友。

## 题目描述

小强喜欢数列。有一天，他心血来潮，写下了三个长度均为n的数列。

阿米巴也很喜欢数列。但是他只喜欢其中一种，波动数列。


阿米巴把他的喜好告诉了小强。小强便打算找出这三个数列内的最长波动数列。

也就是说，如果我们将三个数列记做a[n][3]，他必须要构造一个二元组序列：<p[i], q[i]>，使得对于任何 i>1 有：

p[i] > p[i-1]

若q[i] = 0，a[p[i]][q[i]] >= a[p[i-1]][q[i-1]]

若q[i] = 1，a[p[i]][q[i]] <= a[p[i-1]][q[i-1]]

若q[i] = 2，只要保持段内同向即可（就是对于连续的一段q[i]=2，要么都有a[p[i]][q[i]] >= a[p[i-1]][q[i-1]]，要么都有a[p[i]][q[i]] <= a[p[i-1]][q[i-1]]）。

小强希望这个二元组序列尽可能长。


提示：当q[i] != q[i-1]时，数列的增减性由q[i]而非q[i-1]决定。


**清晰版题目描述**


小强拿到一个3×n的数组，要在每一列选一个数（或者不选），满足以下条件：


1.如果在第一行选，那它必须大于等于上一个数

2.如果在第二行选，那么必须小于等于上一个数

3.如果在第三行选，对于连续的一段在第三行选的数，必须满足方向相同（都小于等于上一个数或者都大于等于上一个数）

## 输入格式

输入包含4行。

第一行一个数n，表示数列长度。

第2、3、4行，每行n个整数，分别表示三个数列。

## 输出格式

输出仅包含一个整数，即最长波动数列的长度。

## 样例

### 样例输入 #1
```
6
1 2 3 6 5 4
5 4 3 7 8 9
1 2 3 6 5 4

```
### 样例输出 #1
```
6
```
## 提示

对于20%的数据，n <= 10， m <= 1000

对于60%的数据，n <= 1000,  m <= 1000

对于100%的数据， n <= 100000， m <= 1000000000

其中m = max|a[i]|

样例解释：

取第三行1 2 3（增），然后取第1行6（增），然后取第三行5 4（减），长度为6。



---

---
title: "[Ynoi Easy Round 2016] 炸脖龙 I"
layout: "post"
diff: 省选/NOI-
pid: P3934
tag: ['2016', '线段树', '树状数组', 'O2优化', '枚举', '洛谷月赛', 'Ynoi']
---
# [Ynoi Easy Round 2016] 炸脖龙 I
## 题目背景

备餐时光，软泞蜥獾

草地中钻孔，日晷下打转

波若歌鹦苟延残喘，迷途绿龟嚎哮迷茫

“当心炸脖龙，我的孩子！

那锋爪利颚，能挠钩撕咬！

注意秋布秋布鸟，你需回避，

那暴躁冒烟恶怪大毛怪！”

手持宝剑鸣真理之语：寻觅强敌豪壮永不息——于噹噹树下稍事休憩，伫立良久，深陷思绪。

当思绪纷乱杂绪之际，炸脖龙双目如烔炬，从阴暗密林奔跃闯出，一路悲鸣低吟时啭啼！

一，二！一，二！一刺再刺，真理之语将敌斩成糜！

取其首级，置之死地，

伴随胜利，驰马归疾。

“真当是你把怪龙斩于马下？

奋勇吾儿！

来我怀里！奔走相告！衣锦还乡！

父喜不自禁窃鸣得意

波若歌鹦苟延残喘，

迷途绿龟嚎哮迷茫，

备餐时光，软泞蜥獾

草地中钻孔，日晷下打转

波若歌鹦苟延残喘，

迷途绿龟嚎哮迷茫”

——《炸脖龙之诗》

![](https://cdn.luogu.com.cn/upload/pic/21111.png)

我喊了出来...却不成人话

只能，像在水中一边融化一边下沉的方糖一样...

失去自己的轮廓...一直沉向最低处

想要爬上去的子午

维持自己是自己的连续体...

溶解的渐渐七零八落的意识...

失去了用来挣扎的双手

失去了用来挣扎的双臂

向下，

向下，

一直沉下去

向着意识的底层

沉陷下去的自我...

逐渐消失的世界...

我看到了世界

失落的...世界...

![](https://cdn.luogu.com.cn/upload/pic/21112.png)

```plain

   回归天空的话我就可以成为      了

  开什么玩笑，你才不是什么      ！

  吵死了！吵死了！我是      ！而且生来就是！

就是因为这个家伙我才失去      的资格的！

 呜呜呜，由岐姐姐，由岐姐姐！

  ...怎么会...由岐姐...

 卓司！你这家伙！

        吵死了吵死了！像你这样的普通人懂些什么！

   由岐的血慢慢在冰凉的水泥地上扩散开来

   抱在怀里的      在渐渐地流出来        本应成为      而出生

的我的被      妨碍了！

不出生的话我就没法拯救是这个世界！

            所以预言者说能当世界回归天空的此处就是尽头

   只要      回归天空的话！

 我有这么可怕吗？

              因为我是要对一切生物下达审判的存在！

       因为哥哥是凡人呢

    凡人与天才

                            救世主

   世界

                    救世主

                回天之门

  要死的是你！

            我不会死               不会死       诅咒你

       要死的是羽咲

         只要羽咲死了

                  间宫              皆

                                    守           由

                         岐

                                间宫羽咲

                          可能性

                                    和镜

                     终

                   终之空

                     空

```

![](https://cdn.luogu.com.cn/upload/pic/21113.png)

一个婴儿出生了

谁的？

不知道


虽然不知道...
但确实有一个婴儿出生了

嗯...那个婴儿在哭...

呜嘎，呜嘎，地哭着...

听到这个哭声大家都笑了

大家都在为婴儿祝福

母亲也是...

父亲也是...

并且其他人也是...

为那个婴儿的出生...

衷心祝福

世界充满着生命的祝福

但是

但不是这样的

在那里

我

我一个人在那里恐惧着

非常恐惧...

要说为什么的话...

因为那是在对世界进行诅咒

没错...

他在诅咒着那个世界，那个刚出生的婴儿

诅咒着自己的出生

我

我当场全身僵硬

在大家的笑容之中

在祝福之中

独自一人...

我啊...

我摇摇晃晃地...

接近那个婴儿

然后想要让那个婴儿停止哭泣

我想着必须要那样做才行

为什么呢？

我自己也不明白...

那是

那是，自从出生以来

就悲惨地活到今天的我能做到的

我能做到的

唯一的

唯一的赎罪啊。

![](https://cdn.luogu.com.cn/upload/pic/21114.png)

让我在这里了结了你吧…间宫卓司

这里是终之空的下面吧…这不刚好吗

跟我们的终结很相称不是吗…

这里，是只对你而言的，终结的天空…

这里就是终焉之地…

![](https://cdn.luogu.com.cn/upload/pic/21115.png)

“不行！绝对不行！”

…为什么…跟过来了…

![](https://cdn.luogu.com.cn/upload/pic/21116.png)

预定…调和吗…

原来如此…看来不管怎样对于你来说…我都已经毫无任何价值了对吧…

竟然被这家伙打倒了…真是没办法呐…

这也是现实吗…

那就接受吧…

![](https://cdn.luogu.com.cn/upload/pic/21117.png)

不知为何，我好像看到了在夜空中挺立的向日葵…

只有一瞬间…

那株向日葵…

好像在某个地方…

向日葵…

跟羽咲一起…

是啊…

我是哥哥啊…

要是…能再多当当她的哥哥就好了……

![](https://cdn.luogu.com.cn/upload/pic/21119.png)

咦……

刚才的…

那个是…那片风景…

是吗…那片风景…

我也是知道的啊…

在坡道途中的向日葵…

蔚蓝的天空和向日葵。

漂浮着大大的云朵…

羽咲戴着大大的帽子…

然后跟我走在一起…

走着走着…

为了…

两人一起…

爬上那个坡道…

因为…那个坡道的前面有很漂亮的景色…
## 题目描述

您正在打 galgame，然后您觉得这个 gal 不知所云，于是您弃坑了，开始写数据结构题：

给一个长为 $n$ 的序列，$m$ 次操作，每次操作：

1. 区间 $[l,r]$ 加 $x$；
2. 对于区间 $[l,r]$，查询：

$$a[l]^{a[l+1]^{a[l+2]^{\dots ^{a[r]}}}} \mod p$$
## 输入格式

第一行两个整数 $n,m$ 表示序列长度和操作数。

接下来一行，$n$ 个整数表示这个序列。

接下来 $m$ 行，可能是以下两种操作之一：

- $1\ l\ r\ x$ 表示区间 $[l,r]$ 加上 $x$；
- $2\ l\ r\ p$ 表示对区间 $[l,r]$ 进行一次查询，模数为 $p$。
## 输出格式

对于每个询问，输出一个数表示答案。
## 样例

### 样例输入 #1
```
6 4
1 2 3 4 5 6
2 1 2 10000007
2 2 3 5
1 1 4 1
2 2 4 10

```
### 样例输出 #1
```
1
3
1
```
### 样例输入 #2
```
5 5
2 3 3 3 3
1 1 1 530739835
2 1 1 8356089
2 1 4 5496738
1 1 2 66050181
1 2 4 138625417

```
### 样例输出 #2
```
4306230
697527

```
## 提示

Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477

对于100%的数据，$n , m \le 500000$ , 序列中每个数在$[1,2\cdot 10^9]$内，$p \le 2 \cdot 10^7 $, 每次加上的数在$[0,2\cdot 10^9]$内

共10组数据



---

---
title: "[NOIP 2017 提高组] 列队"
layout: "post"
diff: 省选/NOI-
pid: P3960
tag: ['2017', '线段树', '平衡树', '树状数组', 'NOIP 提高组']
---
# [NOIP 2017 提高组] 列队
## 题目背景

NOIP2017 D2T3
## 题目描述

`Sylvia` 是一个热爱学习的女孩子。

前段时间，`Sylvia` 参加了学校的军训。众所周知，军训的时候需要站方阵。

Sylvia 所在的方阵中有 $n \times m$ 名学生，方阵的行数为 $n$，列数为 $m$。

为了便于管理，教官在训练开始时，按照从前到后，从左到右的顺序给方阵中 的学生从 $1$ 到 $n \times m$ 编上了号码（参见后面的样例）。即：初始时，第 $i$ 行第 $j$ 列 的学生的编号是 $(i-1)\times m + j$。

然而在练习方阵的时候，经常会有学生因为各种各样的事情需要离队。在一天 中，一共发生了 $q$ 件这样的离队事件。每一次离队事件可以用数对 $(x,y) (1 \le x \le n, 1 \le y \le m)$ 描述，表示第 $x$ 行第 $y$ 列的学生离队。

在有学生离队后，队伍中出现了一个空位。为了队伍的整齐，教官会依次下达 这样的两条指令：


1. 向左看齐。这时第一列保持不动，所有学生向左填补空缺。不难发现在这条 指令之后，空位在第 $x$ 行第 $m$ 列。
2. 向前看齐。这时第一行保持不动，所有学生向前填补空缺。不难发现在这条 指令之后，空位在第 $n$ 行第 $m$ 列。


教官规定不能有两个或更多学生同时离队。即在前一个离队的学生归队之后， 下一个学生才能离队。因此在每一个离队的学生要归队时，队伍中有且仅有第 $n$ 行 第 $m$ 列一个空位，这时这个学生会自然地填补到这个位置。

因为站方阵真的很无聊，所以 `Sylvia` 想要计算每一次离队事件中，离队的同学 的编号是多少。

注意：每一个同学的编号不会随着离队事件的发生而改变，在发生离队事件后 方阵中同学的编号可能是乱序的。

## 输入格式

输入共 $q+1$ 行。

第一行包含 $3$ 个用空格分隔的正整数 $n, m, q$，表示方阵大小是 $n$ 行 $m$ 列，一共发 生了 $q$ 次事件。

接下来 $q$ 行按照事件发生顺序描述了 $q$ 件事件。每一行是两个整数 $x, y$，用一个空 格分隔，表示这个离队事件中离队的学生当时排在第 $x$ 行第 $y$ 列。

## 输出格式

按照事件输入的顺序，每一个事件输出一行一个整数，表示这个离队事件中离队学生的编号。

## 样例

### 样例输入 #1
```
2 2 3 
1 1 
2 2 
1 2 
```
### 样例输出 #1
```
1
1
4

```
## 提示

【输入输出样例 $1$ 说明】

$$\begin{matrix}
\begin{bmatrix}
1 & 2 \\
3 & 4 \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
 & 2 \\
3 & 4 \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 &  \\
3 & 4 \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 & 4 \\
3 &  \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 & 4 \\
3 & 1 \\
\end{bmatrix} \\[1em]
\begin{bmatrix}
2 & 4 \\
3 & 1 \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 & 4 \\
3 &  \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 & 4 \\
3 &  \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 & 4 \\
3 &  \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 & 4 \\
3 & 1 \\
\end{bmatrix}\\[1em]
\begin{bmatrix}
2 & 4 \\
3 & 1 \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 &  \\
3 & 1 \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 &  \\
3 & 1 \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 & 1 \\
3 &  \\
\end{bmatrix} & \Rightarrow & 
\begin{bmatrix}
2 & 1 \\
3 & 4 \\
\end{bmatrix}
\end{matrix}$$


列队的过程如上图所示，每一行描述了一个事件。 在第一个事件中，编号为 $1$ 的同学离队，这时空位在第一行第一列。接着所有同学 向左标齐，这时编号为 $2$ 的同学向左移动一步，空位移动到第一行第二列。然后所有同 学向上标齐，这时编号为 $4$ 的同学向上一步，这时空位移动到第二行第二列。最后编号为 $1$ 的同学返回填补到空位中。

【数据规模与约定】

| 测试点编号 | $n$ | $m$ | $q$ | 其他约定 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1\sim 6$ | $\le 10^3$ | $\le 10^3$ | $\le 500$ | 无 |
| $7\sim 10$ | $\le 5\times 10^4$ | $\le 5\times 10^4$ | $\le 500$ | 无 |
| $11\sim 12$ | $=1$ | $\le 10^5$ | $\le 10^5$ | 所有事件 $x=1$ |
| $13\sim 14$ | $=1$ | $\le 3\times 10^5$ | $\le 3\times 10^5$ | 所有事件 $x=1$ |
| $15\sim 16$ | $\le 3\times 10^5$ | $\le 3\times 10^5$ | $\le 3\times 10^5$ | 所有事件 $x=1$ |
| $17\sim 18$ | $\le 10^5$ | $\le 10^5$ | $\le 10^5$ | 无 |
| $19\sim 20$ | $\le 3\times 10^5$ | $\le 3\times 10^5$ | $\le 3\times 10^5$ | 无 |

数据保证每一个事件满足 $1 \le x \le n,1 \le y \le m$。



---

---
title: "我永远喜欢珂朵莉~"
layout: "post"
diff: 省选/NOI-
pid: P3987
tag: ['平衡树', '树状数组', '深度优先搜索 DFS', '洛谷月赛']
---
# 我永远喜欢珂朵莉~
## 题目背景

http://sukasuka-anime.com/

戒不掉的珂毒

出不动的分块

 ![](https://cdn.luogu.com.cn/upload/pic/11191.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/11192.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/11193.png) 

哦对了有没有想买BD的珂学家啊？支持一下墨鱼吧~

或者有没有人想来手办众筹啊？

## 题目描述

给珂朵莉一个长为 $n$ 的非负数序列 $a$，支持以下两个操作：

- $\verb!1 l r x!$：把区间 $[l,r]$ 中所有 $x$ 的倍数除以 $x$。
- $\verb!2 l r!$：查询区间 $[l,r]$ 内元素的和。

珂朵莉很可爱，所以你要帮珂朵莉写这个题。

## 输入格式

第一行两个数表示 $n,m$。

第二行 $n$ 个非负整数表示 $a_i$。

之后 $m$ 行每行一个操作：

- $\verb!1 l r x!$：把区间 $[l,r]$ 中所有 $x$ 的倍数除以 $x$。
- $\verb!2 l r!$：查询区间 $[l,r]$ 内元素的和。

## 输出格式

对于每次询问，输出一行一个数表示答案。

## 样例

### 样例输入 #1
```
5 3
1 2 3 4 5
2 1 5
1 1 5 2
2 1 5
```
### 样例输出 #1
```
15
12
```
## 提示

### 数据范围及约定

$1 \le n , m \le 10^5$，$0 \le a_i \le 5\times 10^5$，$1 \le x \le 5\times 10^5$。



---

---
title: "[SHOI2013] 发牌"
layout: "post"
diff: 省选/NOI-
pid: P3988
tag: ['模拟', '2013', '线段树', '各省省选', '平衡树', '树状数组', '上海', '可持久化线段树']
---
# [SHOI2013] 发牌
## 题目描述

在一些扑克游戏里，如德州扑克，发牌是有讲究的。一般称呼专业的发牌手为荷官。荷官在发牌前，先要销牌（burn card）。所谓销牌，就是把当前在牌库顶的那一张牌移动到牌库底，它用来防止玩家猜牌而影响游戏。

假设一开始，荷官拿出了一副新牌，这副牌有 $N$ 张不同的牌，编号依次为 $1$ 到 $N$。由于是新牌，所以牌是按照顺序排好的，从牌库顶开始，依次为 $1,2,\cdots,N$，$N$ 号牌在牌库底。为了发完所有的牌，荷官会进行 $N$ 次发牌操作，在第 $i$ 次发牌之前，他会连续进行 $R_i$ 次销牌操作，$R_i$ 由输入给定。请问最后玩家拿到这副牌的顺序是什么样的？

举个例子，假设 $N=4$，则一开始的时候，牌库中牌的构成顺序为 $1,2,3,4$。

- 假设 $R_1=2$，则荷官应该连销两次牌，将 $1$ 和 $2$ 放入牌库底，再将 $3$ 发给玩家。目前牌库中的牌顺序为 $4,1,2$。
- 假设 $R_2=0$，荷官不需要销牌，直接将 $4$ 发给玩家，目前牌库中的牌顺序为 $1,2$。
- 假设 $R_3=3$，则荷官依次销去了 $1,2,1$，再将 $2$ 发给了玩家。目前牌库仅剩下一张牌 $1$。
- 假设 $R_4=2$，荷官在重复销去两次 $1$ 之后，还是将 $1$ 发给了玩家，这是因为 $1$ 是牌库中唯一的一张牌。
## 输入格式

第一行，一个整数 $N$，表示牌的数量。

第二行到第 $N+1$ 行，在第 $i+1$ 行，有一个整数 $R_i$。

## 输出格式

共 $N$ 行，第 $i$ 行有一个整数，表示玩家收到的第 $i$ 张牌的编号。
## 样例

### 样例输入 #1
```
4
2
0
3
2
```
### 样例输出 #1
```
3
4
2
1
```
## 提示

#### 数据规模与约定

对于 $100 \%$ 的数据，$0 \le R_i < N$。  

| 测试点编号 | $N=$ | 测试点编号 | $N=$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $5\times 10^3$ | $6$ | $3\times 10^5$ |
| $2$ | $10^4$ |  $7$ | $4\times 10^5$ |
| $3$ | $5\times 10^4$ | $8$ | $5\times 10^5$ |
| $4$ | $10^5$ | $9$ | $6\times 10^5$ |
| $5$ | $2\times 10^5$ | $10$ | $7\times 10^5$ |


---

---
title: "小 Y 和地铁"
layout: "post"
diff: 省选/NOI-
pid: P4005
tag: ['模拟', '搜索', '2017', '树状数组', 'O2优化', '枚举', '模拟退火', 'CTT（清华集训/北大集训）']
---
# 小 Y 和地铁
## 题目描述

小 Y 是一个爱好旅行的 OIer。一天，她来到了一个新的城市。由于不熟悉那里的交通系统，她选择了坐地铁。

她发现每条地铁线路可以看成平面上的一条曲线，不同线路的交点处一定会设有换乘站 。通过调查得知，没有线路是环线，也没有线路与自身相交。任意两条不同的线路只会在若干个点上相交，没有重合的部分，且没有三线共点的情况。即，如图所示的情况都是不存在的：

 ![](https://cdn.luogu.com.cn/upload/pic/12055.png) 

小 Y 坐着地铁 $0$ 号线，路上依次经过了 $n$ 个换乘站。她记下了每个换乘站可以换乘的线路编号，发现每条线路与她所乘坐的线路最多只有 $2$ 个换乘站。现在小 Y 想知道，除掉她经过的换乘站以外，这个城市里最少有几个换乘站。只有你告诉她正确的答案，她才会答应下次带你去玩呢。

## 输入格式

**请注意本题有多组输入数据。**

输入数据的第一行是一个整数 $T$，表示输入数据的组数。接下来依次给出每组数据。

对于每组数据，第一行是一个整数 $n$，表示小 Y 经过的换乘站的数目。第二行为 $n$ 个用空格隔开的整数，依次表示每个换乘站的可以换乘的线路编号。这些编号都在 $1\sim n$ 之内。

## 输出格式

对于每组输入数据，输出一行一个整数，表示除掉这 $n$ 个换乘站之外，最少有几个换乘站。

## 样例

### 样例输入 #1
```
4 4
1 2 1 2
8
1 2 3 4 1 2 3 4
5
5 4 3 3 5
8
1 2 3 4 1 3 2 4
```
### 样例输出 #1
```
0 
0 
0 
1
```
## 提示

【样例 1 解释】

对于样例的前两组数据，一种可能的最优答案如下图所示。

 ![](https://cdn.luogu.com.cn/upload/pic/12053.png) 

【子任务】

一共有 $50$ 个测试点，每个测试点 $2$ 分。你只有在答案完全正确时才能得到该测试点的全部分数，否则不得分。

对于所有测试点，以及对于样例， $1 \leq T \leq 100$, $1 \leq n \leq 44$。对于每个测试点， $n$ 的范围如下表：

![](https://cdn.luogu.com.cn/upload/pic/12054.png)



---

---
title: "[Code+#2] 火锅盛宴"
layout: "post"
diff: 省选/NOI-
pid: P4032
tag: ['树状数组', '优先队列', '队列', 'Code+']
---
# [Code+#2] 火锅盛宴
## 题目背景

SkyDec 和 YJQQQAQ 都是 Yazid 的好朋友。他们都非常喜欢吃火锅。有一天，他们聚在一起，享受一场火锅盛宴。
## 题目描述

在这场火锅盛宴中，有一个麻辣浓汤锅底的火锅和 $n$ 种食物，每种食物数量都是无限的。我们用 $1$ 至 $n$ 将这些食材编号。

每种食物煮熟所需要的时间不同，第 $i$ 种食物煮熟需要 $s_i$ 单位时间。这表示如果你在第 $T$ 个时刻将一个食物 $i$ 下到火锅里，那么它会在第 $T+s_i$ 个时刻被煮熟，并且此后一直会延续被煮熟的状态，直到它被拿走为止。

Yazid 和 YJQQQAQ 的口味不同：YJQQQAQ 觉得所有食物的好吃程度都是相同的；而 Yazid 则觉得没有两种食材的好吃程度是相同的，并且，巧合的是，编号越小的食物 Yazid 越喜欢吃。可怜的 SkyDec 由于不能吃辣，所以只能帮 Yazid 和 YJQQQAQ 煮食物。

整个火锅盛宴持续 $10^9$ 单位时间。在整个盛宴中，三位好朋友除了谈笑风生之外，最重要的事当然就是吃东西了。在任意整数时刻，都有可能发生下列 $4$ 种事件中的任意一种，我们用 $0$ 至 $3$ 之间的整数 $op$ 描述事件类型：

- $0\ id$：表示 SkyDec 往火锅里下了一个编号为 $id$ 的食物。
- $1$：Yazid 在锅内搜寻熟了的且最喜欢吃的食物，并拿走一个这种食物。特别地，如果锅里没有熟了的食物，那么 Yazid 会很愤怒。
- $2\ id$：YJQQQAQ 在锅内搜寻编号为 $id$ 的食物：
   - 如果锅里不存在该种食物，则 YJQQQAQ 会很愤怒；
   - 如果锅里存在熟了的该食物，则 YJQQQAQ 会取走一个并食用；
   - 如果锅里只有未煮熟的该种食物，那么 YJQQQAQ 会希望知道最接近煮熟的该种食物（即锅内存在时间最长的该种食物）还需要多少时间被煮熟。
- $3\ l\ r$：馋涎欲滴的 SkyDec 想知道，锅里编号在 $[l,r]$ 之间的且熟了的食物总共有多少个。
## 输入格式

从标准输入读入数据。

本题包含多组数据，输入的第一行为一个正整数 $T$，表示数据组数。接下来依次描述每组数据，对于每组数据：

第一行一个正整数 $n$，表示食物的种类数。

第二行 $n$ 个用空格隔开的正整数 $s_1,s_2,\cdots, s_n$，描述每种食物煮熟需要的时间。

第三行一个正整数 $Q$，表示事件的数目。

接下来 $Q$ 行，每行若干个用空格隔开的非负整数，描述一个事件。先是两个整数 $t,op$，分别表示发生事件的时间以及事件的类型。

- 如果 $op=0$ 或 $op=2$，则接下来 $1$ 个正整数 $id$，意义见题目描述；
- 如果 $op=1$，则接下来没有其他数；
- 如果 $op=3$，则接下来 $2$ 个正整数 $l,r$，意义见题目描述。

数据保证 $t$ 按输入顺序严格递增。

## 输出格式

对于每个 $op\neq 0$ 的操作，输出一行表示答案。对于不同的 $op$，需要输出的内容如下：

- 对于 $op=1$，如果 Yazid 成功取走食物，则输出他取走食物的编号；否则输出 $\text{``\texttt{Yazid is angry.}''}\!\!$（不含引号，下同）。
- 对于 $op=2$，如果 YJQQQAQ 成功取走食物，则输出 $\!\!\text{``\texttt{Succeeded!}''}\!\!$；否则，如果锅里有未煮熟的该类食物，输出最接近煮熟的该种食物还需要多少时间被煮熟；否则，输出 $\!\!\text{``\texttt{YJQQQAQ is angry.}''}\!$。
- 对于 $op=3$，输出锅内编号在指定范围内的熟食的数量。
## 样例

### 样例输入 #1
```
1
2
1 100
10
1 0 2
2 0 1
3 2 1
4 2 2
5 2 1
200 0 1
201 3 1 2
202 1
203 1
204 1
```
### 样例输出 #1
```
Succeeded!
97
YJQQQAQ is angry.
2
1
2
Yazid is angry.
```
## 提示

对于所有数据，保证$ T\leq 4$，保证 $n\leq 100,000$，$Q\leq 500,000$，$1\leq s_i\leq 10^8$，$1\leq t\leq 10^9$，$op\in\{0, 1, 2, 3\}$，$1\leq id\leq n$，$1\leq l\leq r\leq n$。数据保证 $t$ 按输入顺序严格递增。

来自 CodePlus 2017 12 月赛，清华大学计算机科学与技术系学生算法与竞赛协会 荣誉出品。

Credit：idea/王聿中 命题/王聿中 验题/吕时清，杨景钦

Git Repo：https://git.thusaac.org/publish/CodePlus201712

感谢腾讯公司对此次比赛的支持。



---

---
title: "奇数国"
layout: "post"
diff: 省选/NOI-
pid: P4140
tag: ['数学', '2014', '线段树', '树状数组', '素数判断,质数,筛法', '逆元', 'CTT（清华集训/北大集训）']
---
# 奇数国
## 题目描述

在一片美丽的大陆上有 $100\,000$ 个国家，记为 $1$ 到 $100\,000$。这里经济发达，有数不尽的账房，并且每个国家有一个银行。

某大公司的领袖在这 $100\,000$ 个银行开户时都存了 $3$ 大洋，他惜财如命，因此会不时地派小弟 GFS 清点一些银行的存款或者让 GFS 改变某个银行的存款。

该村子在财产上的求和运算等同于我们的乘法运算，也就是说领袖开户时的存款总和为 $3^{100000}$。这里发行的软妹面额是最小的 $60$ 个素数（$p_1=2,p_2=3,\ldots, p_{60}=281$），任何人的财产都只能由这 $60$ 个基本面额表示，即设某个人的财产为 $fortune$（正整数），则 $fortune=p_1^{k_1} \times p_2^{k_2} \times \ldots p_{60}^{k_{60}}$。

领袖习惯将一段编号连续的银行里的存款拿到一个账房去清点，为了避免 GFS 串通账房叛变，所以他不会每次都选择同一个账房。GFS 跟随领袖多年已经摸清了门路,知道领袖选择账房的方式。如果领袖选择清点编号在 $[a,b]$ 内的银行财产，他会先对 $[a,b]$ 的财产求和（记为 $product$），然后在编号属于 $[1,product]$ 的账房中选择一个去清点存款，检验自己计算是否正确同时也检验账房与 GFS 是否有勾结。GFS 发现如果某个账房的编号 $number$ 与 $product$ 相冲，领袖绝对不会选择这个账房。

怎样才算与 $product$ 不相冲呢？若存在整数 $x,y$ 使得 $number \times x+product \times y=1$，那么我们称 $number$ 与 $product$ 不相冲，即该账房有可能被领袖相中。当领袖又赚大钱了的时候，他会在某个银行改变存款，这样一来相同区间的银行在不同的时候算出来的 $product$ 可能是不一样的，而且领袖不会在某个银行的存款总数超过 $10^6$。

现在 GFS 预先知道了领袖的清点存款与变动存款的计划，想请你告诉他，每次清点存款时领袖有多少个账房可以供他选择，当然这个值可能非常大，GFS 只想知道对 $19\,961\,993$ 取模后的答案。
## 输入格式

第一行一个整数 $x$ 表示领袖清点和变动存款的总次数。

接下来 $x$ 行，每行 $3$ 个整数 $a_i,b_i,c_i$。$a_i$ 为 $0$ 时表示该条记录是清点计划，领袖会清点 $b_i$ 到 $c_i$ 的银行存款，你需要对该条记录计算出 GFS 想要的答案。$a_i$ 为 $1$ 时表示该条记录是存款变动，你要把银行 $b_i$ 的存款改为 $c_i$，不需要对该记录进行计算。

## 输出格式

对于每个询问，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
6
0 1 3
1 1 5
0 1 3
1 1 7
0 1 3
0 2 3
```
### 样例输出 #1
```
18
24
36
6


```
## 提示

### 样例解释

- 初始化每个国家存款都为 $3$；
- $1$ 到 $3$ 的 $product$ 为 $27$，$[1,27]$ 与 $27$ 不相冲的有 $18$ 个数；
- $1$ 的存款变为 $5$；
- $1$ 到 $3$ 的 $product$ 为 $45$，$[1,45]$ 与 $45$ 不相冲的有 $24$ 个数；
- $1$ 的存款变为 $7$；
- $1$ 到 $3$ 的 $product$ 为 $63$，$[1,63]$ 与 $63$ 不相冲的有 $36$个数；
- $2$ 到 $3$ 的 $product$ 为 $9$，$[1,9]$ 与 $9$ 不相冲的有 $6$ 个数。

### 数据范围

所有数据均满足：$x \geq 1$，$c_i -b_i \geq 0$。

| 子任务编号 | 分值 |    $x \leq$     | $c_i - b_i \leq$ | 特殊性质 |
| :--------: | :--: | :-------------: | :--------------: | :------: |
|    $1$     | $20$ |     $10^4$      |      $100$       |    有    |
|    $2$     | $30$ | $5 \times 10^4$ |      $10^4$      |    无    |
|    $3$     | $50$ |     $10^5$      |      $10^5$      |    无    |

特殊性质指：所有 $product \leq 10^{18}$。


---

---
title: "[Violet] 天使玩偶/SJY摆棋子"
layout: "post"
diff: 省选/NOI-
pid: P4169
tag: ['树状数组', 'cdq 分治', '分治', '剪枝']
---
# [Violet] 天使玩偶/SJY摆棋子
## 题目描述


Ayu 在七年前曾经收到过一个天使玩偶，当时她把它当作时间囊埋在了地下。而七年后 的今天，Ayu 却忘了她把天使玩偶埋在了哪里，所以她决定仅凭一点模糊的记忆来寻找它。

我们把 Ayu 生活的小镇看作一个二维平面坐标系，而 Ayu 会不定时地记起可能在某个点 $(x, y)$ 埋下了天使玩偶；或者 Ayu 会询问你，假如她在 $(x,y)$，那么她离近的天使玩偶可能埋下的地方有多远。

因为 Ayu 只会沿着平行坐标轴的方向来行动，所以在这个问题里我们定义两个点之间的距离为 $\operatorname{dist}(A,B)=|A_x-B_x|+|A_y-B_y|$。其中 $A_x$ 表示点 $A$ 的横坐标，其余类似。

## 输入格式

第一行包含两个整数 $n$ 和 $m$，在刚开始时，Ayu 已经知道有 $n$ 个点可能埋着天使玩偶， 接下来 Ayu 要进行 $m$ 次操作。

接下来 $n$ 行，每行两个非负整数 $(x_i,y_i)$，表示初始 $n$ 个点的坐标。

再接下来 $m$ 行，每行三个非负整数 $t,x_i,y_i$。

* 如果 $t=1$，则表示 Ayu 又回忆起了一个可能埋着玩偶的点 $(x_i,y_i)$。
* 如果 $t=2$，则表示 Ayu 询问如果她在点 $(x_i,y_i)$，那么在已经回忆出来的点里，离她近的那个点有多远
## 输出格式

对于每个 $t=2$ 的询问，在单独的一行内输出该询问的结果。
## 样例

### 样例输入 #1
```
2 3 
1 1 
2 3 
2 1 2 
1 3 3 
2 4 2
```
### 样例输出 #1
```
1 
2
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据 保证 $1 \leq n,m\leq 3 \times 10^5$，$0 \leq x_i,y_i \leq 10^6$。


---

---
title: "[CTSC2008] 网络管理"
layout: "post"
diff: 省选/NOI-
pid: P4175
tag: ['2008', '线段树', '平衡树', '树状数组', '树链剖分', '可持久化线段树', 'CTSC/CTS']
---
# [CTSC2008] 网络管理
## 题目描述

M 公司是一个非常庞大的跨国公司，在许多国家都设有它的下属分支机构或部门。为了让分布在世界各地的 $n$ 个部门之间协同工作，公司搭建了一个连接整个公司的通信网络。  

该网络的结构由 $n$ 个路由器和 $n-1$ 条高速光缆组成。每个部门都有一个专属的路由器，部门局域网内的所有机器都联向这个路由器，然后再通过这个通信子网与其他部门进行通信联络。该网络结构保证网络中的任意两个路由器之间都存在一条直接或间接路径以进行通信。   

高速光缆的数据传输速度非常快，以至于利用光缆传输的延迟时间可以忽略。但是由于路由器老化，在这些路由器上进行数据交换会带来很大的延迟。而两个路由器之间的通信延迟时间则与这两个路由器通信路径上所有路由器中最大的交换延迟时间有关。  

作为 M 公司网络部门的一名实习员工，现在要求你编写一个简单的程序来监视公司的网络状况。该程序能够随时更新网络状况的变化信息（路由器数据交换延迟时间的变化），并且根据询问给出两个路由器通信路径上延迟第 $k$ 大的路由器的延迟时间。
****
【任务】   
你的程序从输入文件中读入 $n$ 个路由器和 $n-1$ 条光缆的连接信息，每个路由器初始的数据交换延迟时间 $t_i$，以及 $q$ 条询问（或状态改变）的信息。并依次处理这 $q$ 条询问信息，它们可能是：

1. 由于更新了设备，或者设备出现新的故障，使得某个路由器的数据交换延迟时间发生了变化。

2. 查询某两个路由器 $a$ 和 $v$ 之间的路径上延迟第 $k$ 大的路由器的延迟时间。

## 输入格式

第一行为两个整数 $n$ 和 $q$，分别表示路由器总数和询问的总数。

第二行有 $n$ 个整数，第 $i$ 个数表示编号为i的路由器初始的数据延迟时间 $t_i$。

紧接着 $n-1$ 行，每行包含两个整数 $x$ 和 $y$。表示有一条光缆连接路由器 $x$ 和路由器 $y$。

紧接着是 $q$ 行，每行三个整数 $k,a,b$。

如果 $k=0$，则表示路由器 $a$ 的状态发生了变化，它的数据交换延迟时间由 $t_a$ 变为 $b$。

如果 $k>0$，则表示询问 $a$ 到 $b$ 的路径上所经过的所有路由器（包括 $a$ 和 $b$）中延迟第 $k$ 大的路由器的延迟时间。注意 $a$ 可以等于 $b$，此时路径上只有一个路由器。

## 输出格式

对于每一个第二种询问（即 $k>0$ ），输出一行。  
包含一个整数为相应的延迟时间。如果路径上的路由器不足 $k$ 个，则输出信息 `invalid request!`。

## 样例

### 样例输入 #1
```
5 5
5 1 2 3 4
3 1
2 1
4 3
5 3
2 4 5
0 1 2
2 2 3
2 1 4
3 3 5
```
### 样例输出 #1
```
3
2
2
invalid request!
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n,q \le 80000$，$0 \le k \le n$，任意一个路由器在任何时刻都满足延迟时间小于 $10^8$。




---

---
title: "旅行规划"
layout: "post"
diff: 省选/NOI-
pid: P4192
tag: ['树状数组', '前缀和', '分块']
---
# 旅行规划
## 题目描述

OIVillage 是一个风景秀美的乡村，为了更好的利用当地的旅游资源，吸引游客，推动经济发展，xkszltl 决定修建了一条铁路将当地 $n$ 个最著名的景点连接起来，让游客可以通过火车从铁路起点（1 号景点）出发，依次游览每个景区。为了更好的评价这条铁路，xkszltl 为每一个景区都赋予了一个美观度，而一条旅行路径的价值就是它所经过的景区的美观度之和。不过，随着天气与季节的变化，某些景点的美观度也会发生变化。

xkszltl 希望为每位旅客提供最佳的旅行指导，但是由于游客的时间有限，不一定能游览全部景区，然而他们也不希望旅途过于短暂，所以每个游客都希望能在某一个区间内的车站结束旅程，而 xkszltl 的任务就是为他们选择一个终点使得旅行线路的价值最大。可是当地的景点与前来观光的旅客实在是太多了，xkszltl 无法及时完成任务，于是找到了准备虐杀 NOI2011 的你，希望你能帮助他完成这个艰巨的任务。

## 输入格式

第一行给出一个整数 $n$，接下来一行给出 $n$ 个景区的初始美观度。

第三行给出一个整数 $m$，接下来 $m$ 行每行为一条指令：

1. `0 x y k`：表示将 $x$ 到 $y$ 这段铁路边上的景区的美观度加上k；

2. `1 x y`：表示有一名旅客想要在 $x$ 到 $y$ 这段（含 $x$ 与 $y$）中的某一站下车，你需要告诉他最大的旅行价值。

## 输出格式

对于每个询问，输出一个整数表示最大的旅行价值。

## 样例

### 样例输入 #1
```
5
1 8 -8 3 -7
3
1 1 5
0 1 3 6
1 2 4
```
### 样例输出 #1
```
9
22
```
## 提示

$n,m \leq 100000$。


---

---
title: "[TJOI2013] 最长上升子序列"
layout: "post"
diff: 省选/NOI-
pid: P4309
tag: ['2013', '线段树', '各省省选', '平衡树', '树状数组', '天津']
---
# [TJOI2013] 最长上升子序列
## 题目描述

给定一个序列，初始为空。现在我们将 $1$ 到 $N$ 的数字插入到序列中，每次将一个数字插入到一个特定的位置。每插入一个数字，我们都想知道此时最长上升子序列长度是多少？
## 输入格式

第一行一个整数 $N$，表示我们要将 $1$ 到 $N$ 插入序列中。

接下是 $N$ 个数字，第 $k$ 个数字 $X_k$，表示我们将 $k$ 插入到位置 $X_k(0\le X_k\le k-1,1\le k\le N)$

## 输出格式

$N$ 行，第 $i$ 行表示 $i$ 插入 $X_i$ 位置后序列的最长上升子序列的长度是多少。
## 样例

### 样例输入 #1
```
3
0 0 2
```
### 样例输出 #1
```
1
1
2
```
## 提示

$100\%$ 的数据 $n\le10^5$。


---

---
title: "[BalkanOI 2007] Mokia 摩基亚"
layout: "post"
diff: 省选/NOI-
pid: P4390
tag: ['2007', '树状数组', '分治', '排序', 'BalkanOI（巴尔干半岛）']
---
# [BalkanOI 2007] Mokia 摩基亚
## 题目描述

摩尔瓦多的移动电话公司摩基亚（Mokia）设计出了一种新的用户定位系统。和其他的定位系统一样，它能够迅速回答任何形如 “用户 C 的位置在哪？” 的问题，精确到毫米。但其真正高科技之处在于，它能够回答形如 “给定区域内有多少名用户？” 的问题。

在定位系统中，世界被认为是一个 $w\times w$ 的正方形区域，由 $1\times 1$ 的方格组成。每个方格都有一个坐标 $(x, y)$，$1\leq x,y\leq w$。坐标的编号从 $1$ 开始。对于一个 $4\times 4$ 的正方形，就有 $1\leq x\leq 4$，$1\leq y\leq 4$（如图）：

![](https://cdn.luogu.com.cn/upload/pic/17271.png)

请帮助 Mokia 公司编写一个程序来计算在某个矩形区域内有多少名用户。
## 输入格式

有三种命令，意义如下：

|命令|参数|意义|
|:-:|:-:|:-:|
|$0$|$w$|初始化一个全零矩阵。本命令仅开始时出现一次。|
|$1$|$x\ y\ a$|向方格 $(x, y)$ 中添加 $a$ 个用户。$a$ 是正整数。|
|$2$|$x_1\ y_1\ x_2\ y_2$|查询 $x_1\leq x\leq x_2$，$y_1\leq y\leq y_2$ 所规定的矩形中的用户数量。|
|$3$|无参数|结束程序。本命令仅结束时出现一次。|

输入共若干行，每行有若干个整数，表示一个命令。
## 输出格式

对所有命令 $2$，输出一个一行整数，即当前询问矩形内的用户数量。
## 样例

### 样例输入 #1
```
0 4
1 2 3 3
2 1 1 3 3
1 2 2 2
2 2 2 3 4
3
```
### 样例输出 #1
```
3
5

```
## 提示

#### 数据规模与约定


对于 $100\%$ 的数据，保证：
- $1\leq w\leq 2\times 10 ^ 6$。
- $1\leq x_1\leq x_2\leq w$，$1\leq y_1\leq y_2\leq w$，$1\leq x,y\leq w$，$0<a\leq 10000$。
- 命令 $1$ 不超过 $160000$ 个。
- 命令 $2$ 不超过 $10000$ 个。


---

---
title: "[AHOI2013] 作业"
layout: "post"
diff: 省选/NOI-
pid: P4396
tag: ['2013', '莫队', '各省省选', '树状数组', '安徽', '分块']
---
# [AHOI2013] 作业
## 题目描述

此时己是凌晨两点，刚刚做了 Codeforces 的小 A 掏出了英语试卷。英语作业其实不算多，一个小时刚好可以做完。然后是一个小时可以做完的数学作业，接下来是分别都是一个小时可以做完的化学，物理，语文……小 A 压力巨大。

这时小 A 碰见了一道非常恶心的数学题，给定了一个长度为 $n$ 的数列和若干个询问，每个询问是关于数列的区间表示数列的第 $l$ 个数到第 $r$ 个数)，首先你要统计该区间内大于等于 $a$，小于等于 $b$ 的数的个数，其次是所有大于等于 $a$，小于等于 $b$ 的，且在该区间中出现过的数值的个数。

小 A 望着那数万的数据规模几乎绝望，只能向大神您求救，请您帮帮他吧。
## 输入格式

第一行两个整数 $n,m$

接下来 $n$ 个不超过 $10^5$ 的正整数表示数列

接下来 $m$ 行，每行四个整数 $l,r,a,b$，具体含义参见题意。

## 输出格式

输出 $m$ 行，分别对应每个询问，输出两个数，分别为在 $l$ 到 $r$ 这段区间中大小在 $[a,b]$ 中的数的个数，以及大于等于 $a$，小于等于 $b$ 的，且在该区间中出现过的数值的个数（具体可以参考样例）。

## 样例

### 样例输入 #1
```
3 4
1 2 2
1 2 1 3
1 2 1 1
1 3 1 3
2 3 2 3
```
### 样例输出 #1
```
2 2
1 1
3 2
2 1
```
## 提示

$N\leq 100000,M\leq 100000$，读入的数字均为 $[1,10^5]$ 内的正整数。


---

---
title: "[BJOI2018] 二进制"
layout: "post"
diff: 省选/NOI-
pid: P4428
tag: ['2018', '线段树', '各省省选', '树状数组', '北京', 'O2优化', '构造']
---
# [BJOI2018] 二进制
## 题目描述

pupil 发现对于一个十进制数，无论怎么将其的数字重新排列，均不影响其是不是$3$ 的倍数。他想研究对于二进制，是否也有类似的性质。

于是他生成了一个长为$n$ 的二进制串，希望你对于这个二进制串的一个子区间，能求出其有多少位置不同的连续子串，满足在重新排列后（可包含前导$0$）是一个$3$ 的倍数。

两个位置不同的子区间指开始位置不同或结束位置不同。

由于他想尝试尽量多的情况，他有时会修改串中的一个位置，并且会进行多次询问。
## 输入格式

输入第一行包含一个正整数$n$，表示二进制数的长度。

之后一行$n$ 个空格隔开的整数，保证均是$0$ 或$1$，表示该二进制串。

之后一行一个整数$m$ ，表示询问和修改的总次数。

之后m 行每行为```1 i```，表示pupil 修改了串的第$i$ 个位置（$0$ 变成$1$ 或$1$ 变成$0$ ），或```2 l r```，表示pupil 询问的子区间是$[l,r]$。

串的下标从$1$ 开始。
## 输出格式

对于每次询问，输出一行一个整数表示对应该询问的结果。
## 样例

### 样例输入 #1
```
4
1 0 1 0
3
2 1 3
1 3
2 3 4
```
### 样例输出 #1
```
2
3
```
## 提示

###样例解释

对于第一个询问，区间$[2,2]$ 只有数字$0$，是$3$ 的倍数，区间$[1,3]$ 可以重排成$011_{(2)} = 3_{(10)}$，是$3$ 的倍数，其他区间均不能重排成$3$ 的倍数。

对于第二个询问，全部三个区间均能重排成$3$ 的倍数（注意$00$ 也是合法的）。

###数据范围

对于$20\%$ 的数据，$1 \leq n,m \leq 100$。

对于$50\%$ 的数据，$1 \leq n,m \leq 5000$。

对于$100\%$ 的数据，$1 \leq n,m \leq 100000$，$l \leq r$。



---

---
title: "[BJWC2018] 第k大斜率"
layout: "post"
diff: 省选/NOI-
pid: P4479
tag: ['2018', '树状数组', '离散化', '北京']
---
# [BJWC2018] 第k大斜率
## 题目描述

在平面直角坐标系上，有 $n$ 个不同的点。任意两个不同的点确定了一条直线。请求出所有斜率存在的直线按斜率从大到小排序后，第 $k$ 条直线的斜率为多少。

为了避免精度误差，请输出斜率向下取整后的结果。（例如：$\lfloor 1.5 \rfloor = 1$，$\lfloor -1.5 \rfloor = -2$）。
## 输入格式

第一行，包含两个正整数 $n$ 和 $k$。  
接下来 $n$ 行，每行包含两个整数 $x_i, y_i$，表示每个点的横纵坐标。
## 输出格式

输出一行，包含一个整数，表示第 $k$ 大的斜率向下取整的结果。
## 样例

### 样例输入 #1
```
4 1
-1 -1
2 1
3 3
1 4
```
### 样例输出 #1
```
2
```
## 提示

**【样例说明】**

符合要求的直线的斜率分别为 $-3, -\frac{1}{2}, \frac{2}{3}, 1, 2, \frac{5}{2}$ 。

**【数据规模和约定】**

令 $M$ 为所有斜率存在的直线的数量 。

对于 $10 \%$ 的数据，$1 \le n \le 10$。  
对于 $20 \%$ 的数据，$1 \le n \le 100$，$|x_i|, |y_i| \le {10}^3$。  
对于 $30 \%$ 的数据，$1 \le n \le 1000$。  
对于 $40 \%$ 的数据，$1 ≤ n ≤ 5000$。  
对于另 $20 \%$ 的数据，满足 $k = 1$ 。  
对于另 $20 \%$ 的数据，满足 $1 \le x_i, y_i \le {10}^3$。  
对于 $100 \%$ 的数据，$1 \le n \le 100000$，$1 \le k \le M$，$|x_i|, |y_i| \le {10}^8$。


---

---
title: "[SHOI2011] 改进代码"
layout: "post"
diff: 省选/NOI-
pid: P4635
tag: ['2011', '各省省选', '树状数组', '上海', '差分']
---
# [SHOI2011] 改进代码
## 题目描述

 PP 写了两段对数组进行操作的代码。

对于 Pascal 选手，两段代码分别如下： 

```
procedure operate1(l, r, c : longint);
var
    i : longint;
begin
    for i := l to r do
        a[i] := (a[i] + c) mod p;
end;

procedure operate2(l, r : longint);
var
    i, cnt : longint;
begin
    cnt := 0;
    for i := l to r - 1 do
        if a[i] > a[i + 1]
            then cnt := cnt + 1;
    writeln(cnt);
end;
```

对于 C / C++ 选手，两段代码分别如下：

```cpp
void operate1(int l, int r, int c)
{
    int i;
    for (i = l; i <= r; ++i)
        a[i] = (a[i] + c) % p;
}

void operate2(int l, int r)
{
    int i, cnt = 0;
    for (i = l; i < r; ++i)
        if (a[i] > a[i + 1])
            ++ cnt;
    printf("%d\n", cnt);
}
```

于是，主程序就可以通过调用这两个子程序对数组 $a_i$​​ 进行操作，下面是示例代码。

对于 Pascal 选手，代码如下：

```
begin
    operate1(1, 4, 3);
    operate1(4, 7, 4);
    operate2(1, 7);
end.
```

对于 C / C++ 选手，代码如下：

```
int main()
{
    operate1(1, 4, 3);
    operate1(4, 7, 4);
    operate2(1, 7);
}
```

但是 QQ 觉得 PP 的程序效率太低了，他想请你优化 PP 的代码。即，对于一段只包含 ``operate1`` 、 ``operate2`` 两种语句的主程序以及运行之前数组 $a_i$​​ 的初始值，请你计算出他的输出。
## 输入格式

输入的第一行包含 $3$ 个整数 $n,m,p$ 。其中 $n$ 是操作中 $l,r$ 的上界， $m$ 是主程序中的语句数， $p$ 是程序中的常数 $p$ 的值。

接下去 $n$ 行每行一个整数，依次是 $a_1,a_2,…,a_n$ 的初始化的值。输入保证这些值都在 $0,1,…,p-1$ 之中。

接下去 $m$ 行每行依次描述主程序的一行代码。每一行的格式为下面两者之一：

-    ``1 l r c`` : 表示代码 ``operate1(l, r, c);`` 。

-    ``2 l r`` : 表示代码 ``operate2(l, r);`` 。


## 输出格式

输出即为输入对应的程序的输出。
## 样例

### 样例输入 #1
```
7 3 7
2
5
3
0
3
1
2
1 1 4 3
1 4 7 4
2 1 7
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5 5 2
1
0
0
1
0
2 1 4
2 1 5
1 3 5 1
2 1 4
2 1 3
```
### 样例输出 #2
```
1
2
2
1
```
## 提示

**数据范围与提示**

测试点 $1$：$n \le 1000,m \le 2000$。

测试点 $2 \sim 3$：$n \le 100000$,$m \le 200000$,$c \le 1$,$a_i \le 100000$,$p>500000$。

测试点 $4$：$n \le 100000,m \le 200000,l=1,r=n$。

测试点 $5 \sim 6$：$n \le 100000,m \le 200000$ 且对于所有 ``operate1`` 的参数都有 $l=1,r=n$。

测试点 $7 \sim 10$：$n \le 100000,m \le 200000$。

保证 $1 \le l \le r \le n,0 \le c \le 10^8,p \le 10^6$​​.


---

---
title: "[IOI 2007] pairs 动物对数"
layout: "post"
diff: 省选/NOI-
pid: P4648
tag: ['2007', '树状数组', 'IOI', '枚举', '前缀和']
---
# [IOI 2007] pairs 动物对数
## 题目描述

Mirko 和 Slavko 正在玩动物玩具的游戏。 首先，他们要在下图给出的三种玩具模板中选择一种。三种模板分别由一维、二维和三维的网格点（在图中用圆圈表示）组成。 

![](https://cdn.luogu.com.cn/upload/pic/20672.png )

接下来Mirko 把 $N$ 个小动物玩具放到选中的模板的网格点上。

动物玩具可以走一步到达与它相邻的网格点上（在图中相邻的点之间有一条小短线相连）。两个网格点之间的距离定义为**从一个网格点到另一个网格点所需要移动的最小步数**。

如果两个动物之间的距离小于等于$D$，则它们之间可以互相听见。Slavko 的任务是计算在模板上有多少对动物可以互相听得见。

给定模板的类型、所有动物的位置以及数字$D$，写一个程序计算有多少对动物可以互相听得见。 
## 输入格式

输入的第一行按顺序给出四个整数： 
- 模板类型 $B (1 \leq B \leq 3)$; 
- 玩具动物的数目 $N (1 \leq N \leq 100 000)$; 
- 动物之间可以互相听得见的最大距离$D (1 \leq D \leq 100 000 000)$; 
- 模板的大小 $M$ ( 即在输入中允许的最大的坐标值):  当 $B=1$ 时, $M$ 最大是 $75 000 000$. 当 $B=2$时, $M$ 最大是 $75 000$. 当 $B=3$时, $M$ 最大是 $75$.

接下来的$N$ 行每行包含$B$ 个整数，整数之间用空格隔开，表示一个动物玩具的坐标。坐标的取值范围是$1$ 到 $M$ ( 包括$M$ )。

每个网格点可以同时包含多个动物玩具。 
## 输出格式

输出应该包括一个整数，表示可以互相听得见的玩具动物的对数。

注意：使用64 位整数类型计算和输出结果 (在 C/C++ 中用```long long```, 在Pascal 中用```int64``` ) 。 
## 样例

### 样例输入 #1
```
1 6 5 100 
25 
50 
50 
10 
20 
23 
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
2 5 4 10 
5 2 
7 2 
8 4 
6 5 
4 4 
```
### 样例输出 #2
```
8
```
### 样例输入 #3
```
3 8 10 20 
10 10 10 
10 10 20 
10 20 10 
10 20 20 
20 10 10 
20 10 20 
20 20 10 
20 20 20 
```
### 样例输出 #3
```
12
```
## 提示

在30分的测试数据中, 动物数目 $N$ 最多是 $1 000$。

如果成功通过了某一种模板（一维、二维或者三维）的全部测试数据，将会得到至少30分。

对于input 1的解释： 假设动物按给出的顺序编号为$1$到$6$。$4$对互相能够听得到的动物分别是:
- 1-5 ( 距离是5)
- 1-6 ( 距离是2)
- 2-3 ( 距离是0)
- 5-6 ( 距离是3)

对于input 2 的解释：$8$对动物分别是:
- 1-2 ( 距离是2)
- 1-4 ( 距离是4)
- 1-5 ( 距离是3)
- 2-3 ( 距离是3)
- 2-4 ( 距离是4)
- 3-4 ( 距离是3)
- 3-5 ( 距离是4)
- 4-5 ( 距离是3)


---

---
title: "[Wind Festival] Energy Center"
layout: "post"
diff: 省选/NOI-
pid: P4743
tag: ['平衡树', '树状数组', 'O2优化', '枚举']
---
# [Wind Festival] Energy Center
## 题目背景

$[Noon - 12:13$ $P.M.]$

$Curtis$ $Nishikino$看到大家为晚会准备地如此认真，~~可爱的~~她也做起了志愿者！
## 题目描述

$Curtis$ $Nishikino$来到了风筝节的能源中心，大家正在为晚会做准备. 这里共有 $N$ 台设备. 当然，由于计划的调整，可能会随时发生增删设备的操作. 但设备的总数不会超过$10^4$. 随时记录设备的数量也是志愿者的工作之一.

每台设备都有一些属性，比如设备$i$, 对于她拥有的每个属性, 比如属性$j$, 都会有一个给定的值, 记为$value_{ij}$.但属性是共有的, 这意味着即便一台设备没有某个属性, 也只会使她这个属性的值为$0$. 属性的数量是$M$. 注意属性的编号是从$0$到$M-1$.

现在志愿者们正尝试将一部分相邻设备联系在一起，效果如下：

- 对于从$j$到$k$的设备, 最终效果$i$的值为 $\sum_{p=j}^{k}value_{pi}$.

志愿者需要$Curtis$帮忙，但做计算太麻烦了，$Curtis$ $Nishikino$也希望你能帮帮她.
## 输入格式

第一行两个整数 $n$ 和 $m$.

接下来 $n$ 行, 第一个整数 $k_i$,这意味着设备 $i$ 有 $k_i$ 个属性. 后面是 $2\times k$ 个整数, $x_j$ 和 $y_j$, 这意味着 $value_{ix_j}=y_j$.

下面是一个整数 $q$, 即 $q$ 个操作. 每项操作都是如下之一:

$I$ $x$ :在设备 $x$ 后插入一台设备, 下面有一行描述信息，像初始化一样.

$D$ $x$:丢弃第 $x$ 台设备.

$QA$ :询问设备总数.

$QS$ $l$ $r$: 询问连接设备 $l$ 到 $r$ 的效果.

输入数据保证合法.
## 输出格式

对于每个 $QA$, 输出一行一个整数.

对于每个 $QS$, 输出一行 $m$ 个整数, 如果属性 $i$ 的值是 $0$, 在那个位置输出 $0$ 即可.

###### 注意！

请在完成所有操作后输出一行额外的 "end" (不包含双引号).
## 样例

### 样例输入 #1
```
4 4
4 0 1 1 2 2 2 3 1
2 0 1 2 1
0
2 1 2 3 1
5
QA
I 2 
2 1 1 3 2
QS 2 4
QA
QS 1 1
```
### 样例输出 #1
```
4
1 1 1 2
5
1 2 2 1
end
```
## 提示

对于 $15\%$ 的数据, $0 < N \le 10^3\ , \ 0<M \le 10\ , \ 0 < q \le 10^3$.

对于额外的 $5\%$ 数据, $0<N \le 10^4\ , \ 0<M \le 200\ , \ 0 < q \le 10^4$, 保证没有 $QS$ 操作.

对于 $100\%$ 的数据, $0<N \le 10^4\ ,\ 0<M \le 200\ , \ 0<q\le10^4$.


---

---
title: "[IOI 2018] werewolf 狼人"
layout: "post"
diff: 省选/NOI-
pid: P4899
tag: ['2018', '树状数组', 'IOI', 'O2优化', '深度优先搜索 DFS', '可持久化线段树']
---
# [IOI 2018] werewolf 狼人
## 题目背景

本题为交互题，但在此请提交**完整程序**。
## 题目描述

在日本的茨城县内共有 $N$ 个城市和 $M$ 条道路。这些城市是根据人口数量的升序排列的，依次编号为 $0$ 到 $N - 1$。每条道路连接两个不同的城市，并且可以双向通行。由这些道路，你能从任意一个城市到另外任意一个城市。

你计划了 $Q$ 个行程，这些行程分别编号为 $0$ 至 $Q - 1$。第 $i(0 \leq i \leq Q - 1)$ 个行程是从城市 $S_i$ 到城市 $E_i$。

你是一个狼人。你有两种形态：**人形**和**狼形**。在每个行程开始的时候，你是人形。在每个行程结束的时候，你必须是狼形。在行程中，你必须要变身（从人形变成狼形）恰好一次，而且只能在某个城市内（包括可能是在 $S_i$ 或 $E_i$ 内）变身。

狼人的生活并不容易。当你是人形时，你必须避开人少的城市，而当你是狼形时，你必须避开人多的城市。对于每一次行程 $i(0 \leq i \leq Q - 1)$，都有两个阈值 $L_i$ 和 $R_i(0 \leq L_i \leq R_i \leq N - 1)$，用以表示哪些城市必须要避开。准确地说，当你是人形时，你必须避开城市 $0, 1, \ldots , L_i - 1$ ；而当你是狼形时，则必须避开城市 $R_i + 1, R_i + 2, \ldots , N - 1$。这就是说，在行程 $i$ 中，你必须在城市 $L_i, L_i + 1, \ldots , R_i$ 中的其中一个城市内变身。

你的任务是，对每一次行程，判定是否有可能在满足上述限制的前提下，由城市 $S_i$ 走到城市 $E_i$。你的路线可以有任意长度。
## 输入格式

输入的第一行包含三个正整数 $N, M, Q$，其意义见题目描述。

接下来 $M$ 行，每行包含两个非负整数。在这 $M$ 行中，第 $j$ 行的两个非负整数分别表示 $X_{j - 1}, Y_{j - 1}$，即编号为 $j - 1$ 的道路连接的两个城市的编号。

接下来 $Q$ 行，每行包含四个非负整数。在这 $Q$ 行中，第 $i$ 行的四个非负整数分别表示 $S_{i - 1}, E_{i - 1}, L_{i - 1}, R_{i - 1}$，即编号为 $i - 1$ 的行程的起点城市编号、终点城市编号以及两个阈值。
## 输出格式

输出包含 $Q$ 行，每行包含一个非 $0$ 即 $1$ 的整数。第 $i$ 行的整数表示对于编号为 $i - 1$ 的行程，是否能从城市 $S_{i - 1}$ 走至城市 $E_{i - 1}$，若能够，那么输出整数为 $1$；若不能，那么输出整数为 $0$。
## 样例

### 样例输入 #1
```
6 6 3
5 1
1 2
1 3
3 4
3 0
5 2
4 2 1 2
4 2 2 2
5 4 3 4

```
### 样例输出 #1
```
1
0
0

```
### 样例输入 #2
```
10 9 10
6 7
1 5
8 0
2 9
9 4
2 7
8 5
6 0
3 4
4 9 0 9
8 1 8 9
1 8 1 8
8 3 5 5
8 9 3 9
0 1 0 2
9 0 6 6
1 7 1 8
9 4 5 6
9 5 0 9

```
### 样例输出 #2
```
1
1
1
0
1
1
0
1
0
1

```
## 提示

**限制条件**

- $2 \leq N \leq 200, 000$
- $N - 1 \leq M \leq 400, 000$
- $1 \leq Q \leq 200, 000$
- 对于每个 $0 \leq j \leq M - 1$
    - $0 \leq X_j \leq N - 1$
    - $0 \leq Y_j \leq N - 1$
    - $X_j \neq Y_j$
- 你可以通过道路由任意一个城市去另外任意一个城市。
- 每一对城市最多只由一条道路直接连起来。换言之，对于所有 $0 \leq j < k \leq M - 1$，都有 $(X_j, Y_j) \neq (X_k, Y_k)$ 和 $(Y_j, X_j) \neq (X_k, Y_k)$
- 对于每个 $0 \leq i \leq Q - 1$
    - $0 \leq L_i \leq S_i \leq N - 1$
    - $0 \leq E_i \leq R_i \leq N - 1$
    - $S_i \neq E_i$
    - $L_i \leq R_i$

**子任务**

- 1.（7 分）$N \leq 100$，$M \leq 200$，$Q \leq 100$。
- 2.（8 分）$N \leq 3, 000$，$M \leq 6, 000$，$Q \leq 3, 000$。
- 3.（34 分）$M = N - 1$ 且每个城市最多与两条路相连（所有城市是以一条直线的形式连起来）。
- 4.（51 分）没有附加限制。


---

---
title: "排队"
layout: "post"
diff: 省选/NOI-
pid: P4901
tag: ['树状数组', 'O2优化', '前缀和', '斐波那契数列']
---
# 排队
## 题目背景

$CYJian$班的这个队形...是梯形么??

$\color{white}\text{信息竞赛班的女生能有多少??}$
## 题目描述

教官觉得$CYJian$班上的队形~~不是很美观~~很不美观..所以教官决定要重排一下队形..

教官先让所有同学按照学号排好序站成一列,然后每一次把当前队列第1,2,3,5,8,13...(差不多就是斐波那契数列了..)个人拉出来,直到没有人能拉出来为止..然后这些人组成一行,排到上一行的后面..

举个栗子,如果一共有10个人,大概就是这样子的:(加粗表示当前选到的人)

1: **1** **2** **3** 4 **5** 6 7 **8** 9 10

取走后: 4 6 7 9 10

2: **4** **6** **7** 9 **10**

取走后: 9

3: **9**

最后的队形长这样:

第一行: 1 2 3 5 8

第二行: 4 6 7 10

第三行: 9

(教官排的队形当然得说好看了..)

我们现在定义一行的美观度: 这一行所有人学号的乘积能分解的质因子的个数..(~~特别的~~,1分解质因子不能得到任何质因子,所以个数为0)

比如第二行,$4 \times 6 \times 7 \times 10=1680=2 \times 2 \times 2 \times 2 \times 3 \times 5 \times 7 \rightarrow 7$

年级一共有$T$个班级,每一个班级都要排一次队形..

现在给出第$i$个班级人数$N_i$和一个正整数$K_i$,需要你求出第$i$个班级排队形后第$K_i$行的队伍的美观度..

特别的,如果排的队形中没有第$K_i$行则输出-1..
## 输入格式

第一行一个正整数$T$..

接下来$T$行每行两个正整数$N_i$和$K_i$..

变量的意义详见题面描述..
## 输出格式

$T$行,每行一个正整数表示所求的美观度..
## 样例

### 样例输入 #1
```
3
10 2
12 2
1 2

```
### 样例输出 #1
```
7
7
-1

```
## 提示

$Subtask$ $1$($30$ $pts$): $ K_i = 1, 1 \leqslant N_i, T \leqslant 1000 $

$Subtask$ $2$($30$ $pts$): $ 1 \leqslant K_i \leqslant 100 \ \ \ \  1 \leqslant N_i \leqslant 10000  \ \ \ \  1 \leqslant T \leqslant 5000  $

$Subtask$ $3$($40$ $pts$): $ 1 \leqslant K_i \leqslant 10000 \ \ \ \ \  1 \leqslant N_i \leqslant 5*10^6 \ \ \ \ \  1 \leqslant T \leqslant 10^6 $

数据不保证存在全是-1的测试点..

注意:**本题捆绑测试**


---

---
title: "帕秋莉的魔导书"
layout: "post"
diff: 省选/NOI-
pid: P4915
tag: ['线段树', '树状数组', 'Special Judge', '前缀和']
---
# 帕秋莉的魔导书
## 题目背景

帕秋莉有一个巨大的图书馆，里面有数以万计的书，其中大部分为魔导书。
## 题目描述

魔导书是一种需要钥匙才能看得懂的书，然而只有和书写者同等或更高熟练度的人才能看得见钥匙。因此，每本魔导书都有它自己的等级 $a_i$，同时它也有自己的知识程度为 $w_i$，现在我们想要知道，一个等级为 $b_i$ 的生物(...)，可以从这些魔导书中得到多少知识。

然而不幸的是，每个生物并不知道自己确切的等级，只有一个等级的大致范围，你需要计算出这个生物获得知识程度的期望值。

## 输入格式

第一行两个正整数 $n,m$ 代表起始书的个数，以及操作的个数。

以下 $n$ 行，每行两个正整数 $a_i$ 和 $w_i$，代表每本书的等级以及知识程度。

接下来的 $m$ 行，每行 $2$ 或 $3$ 个正整数。

操作 1：格式：`1 x y`。含义：求等级为 $[x, y]$ 的生物能获得的期望知识程度。

操作 2：格式：`2 x y`。含义：图书馆又收入了一本等级为 $x$，知识程度为 $y$ 的魔导书。
## 输出格式

输出包含若干行实数，即为所有操作 1 的结果，答案保留四位小数。
## 样例

### 样例输入 #1
```
5 5
1 1
2 1
3 1
4 1
5 1
1 2 5
1 1 5
1 3 5
2 1 5
1 1 2
```
### 样例输出 #1
```
3.5000
3.0000
4.0000
6.5000

```
## 提示

对于 $30\%$ 的数据，保证 $1\le $ 所有输入的数字 $\le 10^3$。

对于 $100\%$ 的数据，保证 $1\le n,m\le 10^5$，对于其他数字，保证在 $32$ 位带符号整数范围内（保证运算中所有的数均在 $-2^{63}\sim 2^{63}-1$ 内）。


---

---
title: "宝藏"
layout: "post"
diff: 省选/NOI-
pid: P5152
tag: ['树状数组']
---
# 宝藏
## 题目背景

此题为改编题，特别鸣谢倪星宇同学。

一群海盗抢到了许多宝藏，准备埋在自己的山洞里。

## 题目描述

海盗的山洞是一个n×n的方格，每个方格都可以储存很多宝藏。所有方格初始时是空的。海盗头头决定把这些宝藏藏在某些矩形区域里，同时了解某些矩阵区域里宝藏数量的奇偶性。但是宝藏实在太多了，他整理得眼花缭乱，所以他找到了你来帮忙。

## 输入格式

第一行两个正整数n,m，表示方格的大小与操作的数量。

下面m行有两种操作：

（1）P x1 y1 x2 y2 k a1 b1 a2 b2……ak bk，表示在(x1,y1)到(x2,y2)这段矩形区域中加入b1种a1物品，b2种a2物品……bk种ak物品

（2）Q  x1 y1 x2 y2，表示询问(x1,y1)到(x2,y2)这段矩形区域中所有物品的奇偶性

## 输出格式

对于每种操作Q，输出一行字符串。该字符串长度为30，由'1'与'2'组成。若第k种物品数量为**偶数**，则该字符串从左到右第k位为'1'，否则为'2'。字符之间没有空格。

（注意是偶1奇2）

## 样例

### 样例输入 #1
```
5 5
P 1 1 5 5 3 1 1 2 1 3 1
Q 1 1 5 5
Q 1 1 4 3
P 1 1 5 5 3 1 2 2 1 3 2
Q 1 2 3 4
```
### 样例输出 #1
```
222111111111111111111111111111
111111111111111111111111111111
212111111111111111111111111111
```
## 提示

30%的数据，n≤300，m≤300；

100%的数据，n≤2500，m≤50000，1≤x1≤x2≤n，1≤y1≤y2≤n，1≤ak≤30，1≤bk≤100；



---

---
title: "[USACO18DEC] Sort It Out P"
layout: "post"
diff: 省选/NOI-
pid: P5156
tag: ['2018', 'USACO', '树状数组']
---
# [USACO18DEC] Sort It Out P
## 题目描述

FJ 有 $N$（$1 \leq N \leq 10^5$）头奶牛（分别用 $1 \ldots N$ 编号）排成一行。FJ 喜欢他的奶牛以升序排列，不幸的是现在她们的顺序被打乱了。在过去，FJ 曾经使用一些诸如“冒泡排序”的开创性算法来使他的奶牛排好序，但今天他想偷个懒。取而代之，他会每次对着一头奶牛叫道“按顺序排好”。当一头奶牛被叫到的时候，她会确保自己在队伍中的顺序是正确的（从她的角度看来）。当有一头紧接在她右边的奶牛的编号比她小，她们就交换位置。然后，当有一头紧接在她左边的奶牛的编号比她大，她们就交换位置。这样这头奶牛就完成了“按顺序排好”，在这头奶牛看来左边的奶牛编号比她小，右边的奶牛编号比她大。

FJ 想要选出这些奶牛的一个子集，然后遍历这个子集，依次对着每一头奶牛发号施令（按编号递增的顺序），重复这样直到所有 $N$ 头奶牛排好顺序。例如，如果他选出了编号为 $\{2,4,5\}$ 的奶牛的子集，那么他会喊叫奶牛 $2$，然后是奶牛 $4$，然后是奶牛 $5$。如果 $N$ 头奶牛此时仍未排好顺序，他会再次对着这几头奶牛喊叫，如果有必要的话继续重复。

由于 FJ 不确定哪些奶牛比较专心，他想要使得这个子集最小。此外，他认为 $K$ 是个幸运数字。请帮他求出满足重复喊叫可以使得所有奶牛排好顺序的最小子集之中字典序第 $K$ 小的子集。

我们称 $\{1, \ldots ,N\}$ 的一个子集 $S$ 在字典序下小于子集 $T$，当 $S$ 的所有元素组成的序列（按升序排列）在字典序下小于 $T$ 的所有元素组成的序列（按升序排列）。例如，$\{1,3,6\}$ 在字典序下小于 $\{1,4,5\}$。
## 输入格式

输入的第一行包含一个整数 $ N $ 。第二行包含一个整数 $ K $ （ $ 1 \leq K \leq 10^{18} $ ）。第三行包含 $ N $ 个空格分隔的整数，表示从左到右奶牛的编号。

保证存在至少 $ K $ 个符合要求的子集。
## 输出格式

第一行输出最小子集的大小。接下来输出字典序第 $ K $ 小的最小子集中奶牛的编号，每行一个数，升序排列。
## 样例

### 样例输入 #1
```
4 1
4 2 1 3

```
### 样例输出 #1
```
2
1
4

```
## 提示

开始的时候序列为 $ \mathtt{\:4\:\; 2\:\; 1\:\; 3\:} $ 。在FJ喊叫编号为 $ 1 $ 的奶牛之后，序列变为 $ \mathtt{\:1\:\; 4\:\; 2\:\; 3\:} $ 。在FJ喊叫编号为 $ 4 $ 的奶牛之后，序列变为 $ \mathtt{\:1\:\; 2\:\; 3\:\; 4\:} $ 。在这个时候，序列已经完成了排序。

## 子任务

对于占总分 $ 3/16 $ 的测试数据， $ N \leq 6 $ ，并且 $ K=1 $ 。

对于另外的占总分 $ 5/16 $ 的测试数据， $ K=1 $ 。

对于另外的占总分 $ 8/16 $ 的测试数据，没有其他限制。


---

---
title: "【XR-3】系统设计"
layout: "post"
diff: 省选/NOI-
pid: P5537
tag: ['字符串', '线段树', '二分', '树状数组', 'O2优化', '哈希 hashing']
---
# 【XR-3】系统设计
## 题目描述

小 X 需要你设计一个系统。

这个系统首先需要输入一棵 $n$ 个点的有根树和一个长度为 $m$ 的序列 $a$，接下来需要实现 $q$ 个操作。

操作分两种：

1. `1 x l r` 表示设定起点为有根树的节点 $x$，接下来依次遍历 $l \sim r$。当遍历到 $i$ 时，从当前节点走向它的编号第 $a_i$ 小的儿子。如果某一时刻当前节点的儿子个数小于 $a_i$，或者已经遍历完 $l \sim r$，则在这个点停住，并输出这个点的编号，同时停止遍历。
2. `2 t k` 表示将序列中第 $t$ 个数 $a_t$ 修改为 $k$。
## 输入格式

第一行 $3$ 个正整数 $n,m,q$，分别表示树的点数、序列的长度和操作个数。

第二行 $n$ 个整数 $f_{1 \dots n}$，其中 $f_i$ 表示点 $i$ 在树中的父亲节点编号，特别地，设根节点为 $rt$，则 $f_{rt} = 0$。

第三行 $m$ 个正整数 $a_{1 \dots m}$，表示序列 $a$。

接下来 $q$ 行，每行描述一个操作。

**数据范围：**

- $1 \le n,m,q \le 5 \times 10 ^ 5$。
- $1 \le a_i \le n$。
- 对于操作 $1$，保证 $1 \le x \le n$，$1 \le l \le r \le m$。
- 对于操作 $2$，保证 $1 \le t \le m$，$1 \le k \le n$。
## 输出格式

对于每个操作 $1$，一行一个正整数，表示答案。
## 样例

### 样例输入 #1
```
6 6 10
0 1 2 2 1 5
1 2 2 1 2 1
1 1 1 3
1 5 2 6
1 6 5 6
1 2 3 5
1 2 4 4
2 2 1
1 1 1 6
1 1 2 4
2 1 2
1 1 1 5

```
### 样例输出 #1
```
4
5
6
4
3
3
4
6

```
## 提示

本题读入、输出量较大，请使用[读入、输出优化](https://oi-wiki.org/misc/io/)。

【样例说明】

第一个操作为 `1 1 1 3`，即 $1 \rightarrow 2 \rightarrow 4$，因此答案为 $4$。

第九个操作后，序列变为 `2 1 2 1 2 1`。

第十个操作为 `1 1 1 5`，即 $1 \rightarrow 5 \rightarrow 6$，因此答案为 $6$。


---

---
title: "圣剑护符"
layout: "post"
diff: 省选/NOI-
pid: P5556
tag: ['树状数组', '树链剖分', '线性基']
---
# 圣剑护符
## 题目背景

小L和小K正在研究传说中的圣剑。

“所谓圣剑，是封入了各种护符并将其固定为刀剑外形的一种东西。据说一旦用咒力线把护符们接合在一起，就会产生复杂的相互干涉作用。”
## 题目描述

小L和小K面前的圣剑由 $n$ 块护符组成，分别编号为 $1,2,\ldots , n$ ，有 $n-1$ 条咒力线连接两块护符，形成了一个树形结构。

经过小L和小K的长时间的研究，他们发现护符之间的相互作用并不复杂。每块护符都有一个属性值，第 $i$ 块护符的属性值记为 $v_i$ 。这个值的每个二进制位上的 $0$ 或 $1$ 表示这块护符是否拥有特定属性。所有属性值中相同的二进制位对应的是相同的属性。

对于一系列护符（护符的集合），对于每种特定属性，统计其中包含这一属性的护符数量，如果为偶数，则这一系列护符形成了干涉，最终的属性值对应的二进制位上为 $0$ ，如果为奇数则干涉后剩下了一块护符的影响，对应的二进制位为 $1$ 。也就是说， **护符集合的属性值为单个护符的属性值的异或和** 。 **空集的属性值定义为 $0$** 。

现在，小L想知道，如果取出两块护符 $x,y$ 间的简单路径上的所有护符，能否找到两个不相等的子集，使得两个子集的属性值相同（注意到空集也是路径上所有护符集合的子集）。同时，小K还会将两块护符间的路径上的所有护符取出进行调整，将所有这些护符的属性值在某些相同二进制位上进行修改（即 $0$ 变为 $1$ ， $1$ 变为 $0$ ），可以看做是将所有这些护符的属性值异或上了一个值。
## 输入格式

输入的第一行为两个整数 $n,q$ ，分别表示护符的数量和小L和小K的操作的数量。

下一行有 $n$ 个整数，第 $i$ 个数表示第 $i$ 块护符的属性值 $v_i$ 。

接下来的 $n-1$ 行，每行有两个整数 $x,y$ ，表示有一条咒力线连接了 $x,y$ 两块护符。保证形成一个树形结构。

接下来的 $q$ 行，每行一个操作，形式如下：

1.  `Update x y z` ：将编号分别为 $x,y$ 的两块护符间的简单路径上的所有护符的属性值异或上一个值 $z$ 。

2. `Query x y` ： 判断对于编号分别为 $x,y$ 的两块护符间的简单路径上的护符的集合，是否存在两个不相等的子集，使得两个子集的属性值相同。
## 输出格式

对于每个 `Query` 操作，输出一行 `YES` 或 `NO` 。
## 样例

### 样例输入 #1
```
2 3
3 4
1 2
Query 1 2
Update 2 2 7
Query 2 1
```
### 样例输出 #1
```
NO
YES
```
## 提示

由于某种原因，本题将采用 **捆绑测试** 。只有通过一个子任务内的所有测试点，才能得到该子任务的全部分数，否则得 $0$ 分。

$Subtask\#1$ ： $20pts$ ， $x,y$ 在树上的距离小于等于 $5$ 。

$Subtask\#2$ ： $40pts$ ， $n,q\le 5000,0\le v_i,z\le 2^{10}$

$Subtask\#3$ ： $40pts$ ，无特殊限制。

对于 $100\%$ 的数据，有 $1\le n,q\le 10^5,1\le x,y\le n,0\le v_i,z< 2^{30}$



---

---
title: "失昼城的守星使"
layout: "post"
diff: 省选/NOI-
pid: P5559
tag: ['线段树', '树状数组', 'O2优化', '树链剖分']
---
# 失昼城的守星使
## 题目背景

> 月伏潮汐生，星染万屿寂，无晦明之变化者，是为失昼。   ————《失昼城手札·起源》

失昼城四面环海，建城于7325年前。

失昼城没有黑夜白天的变化，一轮明月自建城伊始就挂在天空，故名失昼。


失昼城城主月凌霜，掌控着失昼城的守星塔，守星塔在终日无昼的失昼城中作为照明的灯塔，一直是城里人们的精神寄托，她的另一个身份是失昼城的守星使，比起作为城主，月凌霜更喜欢守着守星塔。

失昼城的特殊环境导致其空间异常不稳定，根据失昼城城史记载，七千多年历史的失昼城，其和平的时间总共不超过三百年，其他大部分时间失昼城局部地区都在空间风暴的笼罩之下，依托于特殊空间存在的守星塔，同时兼具着向人们传递信息的功能，在不稳定的空间影响下，这是唯一能够维持信号稳定的方法。


## 题目描述

失昼城共由$N$座岛屿组成，由$N-1$条传递信息的空间通道联通。

作为失昼城的守星使，月凌霜具有部署守星塔的能力，具体而言，为了依靠特殊空间波动向每个有居民居住的岛屿传递消息，月凌霜可以任意数量地部署守星塔，每座岛屿只能部署一座守星塔，**但是同一时刻所有部署的守星塔必须依靠空间通道连成一条链**。

失昼城常年受到空间风暴的困扰，常常会出现某座岛屿遭受空间风暴，岛上全体居民被迫离开岛屿，此时，**守星塔不再需要向该地传输消息**，等到空间风暴散去，居民重新回到这里，**守星塔才需要恢复向该地的信息传输**。

由于空间波动的干扰，守星塔传递消息必须依靠联通岛屿的空间通道完成，具体而言，如果一座守星塔要向一座岛屿传递消息，**其消耗的能量为该座守星塔所处的岛屿到需要接收消息的岛屿的所有空间通道能耗总和**，当然，如果一座守星塔向自身所处的岛屿发送消息，则不需要消耗能量，守星塔对岛屿传递消息的信号波动互相独立，也就是说，**每座守星塔对于每座岛屿的能量传输互不干扰**。

作为城主兼守星使，月凌霜近期正在研究怎样部署守星塔才能使消息传递所消耗的能量最小，现在月凌霜已经找到了记载失昼城七千多年来空间风暴的爆发情况和当时失昼城的守星塔部署的资料，由于历史过于久远，每次能量的消耗情况已经不得而知，现在月凌霜希望你帮助她还原这些史料，具体详见输入格式。
## 输入格式

第一行三个数$N,Q,Type$，表示失昼城岛屿数量，月凌霜的询问个数以及该数据点的特殊性质，$Type$在二进制下，若第$i-1$位为$1$，则表示存在特殊性质$i$。

接下来$N-1$行，每行三个数$u_{i},v_{i},w_{i}$表示岛屿$u$和岛屿$v$之间存在一条双向空间通道，消息经过这条空间通道需要消耗能量为$w_i$。

接下来一行$N$个数，由$0,1$两个数字构成，表示第$i$个岛屿在失昼城建城之时是否存在空间风暴，$0$表示存在空间风暴，$1$表示不存在，同时我们认为，**如果一个岛屿不存在空间风暴，那么它一定会吸引人们聚居，若存在空间风暴，则不会有人们在该岛屿居住**。

最后$Q$行，每行表示一个事件，具体如下：

$1$  $x$：对于岛屿$x$，若原本该岛屿没有空间风暴，则空间风暴产生，岛上全体居民撤出该岛，否则表示该岛屿空间风暴散去，人们重新回到这里居住。

$2$  $x$  $y$：月凌霜向你提出一个询问，询问若此时部署守星塔在$x$到$y$的简单路径上，则向**所有有居民的岛屿**传递一次消息所需要的能量消耗之和**最小**为多少。一座守星塔可以同时向多座岛屿传递消息，也可以不向任何岛屿传递消息。
## 输出格式

输出$Q$行，每行一个数，表示该次询问的答案。
## 样例

### 样例输入 #1
```
5 2 0
1 2 2
1 3 3
4 3 2
5 3 7
0 1 1 0 1
2 2 4
2 4 3
```
### 样例输出 #1
```
7
12
```
### 样例输入 #2
```
6 3 0
2 1 3
3 1 5
4 1 2
6 4 8
4 5 9
1 1 1 0 0 1
2 1 1
1 5
2 3 6
```
### 样例输出 #2
```
18
12
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/74843.png)

特殊性质$1$：$v_{i}=u_{i}+1$

特殊性质$2$：月凌霜所有的询问的$x$和$y$相同。

特殊性质$3$：月凌霜所有的询问的$x=1$。

对于所有的$w_{i}$，保证$0$<=$w_{i}$<=$10^{5}$

对于$100\%$的数据，保证$n,m\leq 200000,0\leq Type\leq 7$.

样例1解释：

![](https://cdn.luogu.com.cn/upload/pic/74831.png)

初始图像如左图。

对于第一个询问如中图，有$2,3,5$有居民，所以$ans_2=ans_3=0,ans_5=7.$所以$ans=7$.

对于第二组询问如右图，$ans_2=2+3=5,ans_3=0,ans_5=7,$,因此$ans=7+5=12$.

样例2解释：

![](https://cdn.luogu.com.cn/upload/pic/74836.png)

初始图如左上。

询问$1$点如图右上，存在$1,2,3,6$有居民。
$ans_1=0,ans_2=3,ans_3=5,ans_6=8+2=10.$因此$ans=3+5+10=18$

1操作后所有有居民点如左下。

接下来的操作图为右下，同上有$ans_1=0,ans_2=3,ans_3=0,ans_5=9,ans_6=0$,所以$ans=3+9=12$.


---

---
title: "[COCI 2015] Divljak"
layout: "post"
diff: 省选/NOI-
pid: P5840
tag: ['2015', '线段树', '树状数组', 'AC 自动机', '差分', 'COCI（克罗地亚）']
---
# [COCI 2015] Divljak
## 题目描述

Alice 有 $n$ 个字符串 ${S}_1, {S}_2, \ldots, {S}_n$，Bob 有一个字符串集合 ${T}$，一开始集合是空的。

接下来会发生 $q$ 个操作，操作有两种形式：

1. `1 P`：Bob 往自己的集合里添加了一个字符串 ${P}$。
2. `2 x`：Alice 询问 Bob，集合 ${T}$ 中有多少个字符串包含串 ${S}_x$（我们称串 ${A}$ 包含串 ${B}$，当且仅当 ${B}$ 是 ${A}$ 的子串）。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，第 $i$ 行一个字符串 ${S}_i$。

接下来一行一个整数 $q$。

接下来 $q$ 行，每行一个操作。
## 输出格式

对每个 `2 x` 操作，一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3
a
bc
abc
5
1 abca
2 1
1 bca
2 2
2 3

```
### 样例输出 #1
```
1
2
1

```
## 提示

对于 $100\%$ 的数据，$1 \leq n,q \leq 10^5$，字符串由小写字母构成，$S$ 和 $P$ 的总长分别 $\le 2 \times 10^6$。



---

---
title: "[USACO20JAN] Springboards G"
layout: "post"
diff: 省选/NOI-
pid: P6007
tag: ['动态规划 DP', '2020', 'USACO', '树状数组', '动态规划优化']
---
# [USACO20JAN] Springboards G
## 题目描述

Bessie 在一个仅允许沿平行于坐标轴方向移动的二维方阵中。她从点 $(0,0)$ 出发，想要到达 $(N,N)$（$1 \leq N \leq 10^9$）。为了帮助她达到目的，在方阵中有 $P$（$1 \leq P \leq 10^5$）个跳板。每个跳板都有其固定的位置 $(x_1,y_1)$，如果 Bessie 使用它，会落到点 $(x_2,y_2)$。

Bessie 是一个过程导向的奶牛，所以她仅允许她自己向上或向右行走，从不向左或向下。类似地，每个跳板也设置为不向左或向下。Bessie 需要行走的距离至少是多少？
## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $P$。

以下 $P$ 行每行包含四个整数 $x_1,y_1,x_2,y_2$，其中 $x_1 \leq x_2$ 且 $y_1 \leq y_2$。

所有跳板的位置和目标位置均不相同。
## 输出格式

输出一个整数，为 Bessie 到达点 $(N,N)$ 需要行走的最小距离。
## 样例

### 样例输入 #1
```
3 2
0 1 0 2
1 2 2 3
```
### 样例输出 #1
```
3
```
## 提示

### 样例解释

Bessie 的最佳路线为：

- Bessie 从 (0,0) 走到 (0,1)（1 单位距离）。
- Bessie 跳到 (0,2)。
- Bessie 从 (0,2) 走到 (1,2)（1 单位距离）。
- Bessie 跳到 (2,3)。
- Bessie 从 (2,3) 走到 (3,3)（1 单位距离）。

Bessie 总共走过的路程为 3 单位距离。

### 子任务

- 测试点 $2 \sim 5$ 满足 $P \leq 1000$。
- 测试点 $6 \sim 15$ 没有额外限制。


---

---
title: "【模板】点分树 | 震波"
layout: "post"
diff: 省选/NOI-
pid: P6329
tag: ['点分治', '树状数组', 'O2优化']
---
# 【模板】点分树 | 震波
## 题目背景

模板题，没有 $rap$ 。
## 题目描述

在一片土地上有 $n$ 个城市，通过 $n-1$ 条无向边互相连接，形成一棵树的结构，相邻两个城市的距离为 $1$，其中第 $i$ 个城市的价值为 $value_i$。

不幸的是，这片土地常常发生地震，并且随着时代的发展，城市的价值也往往会发生变动。

接下来你需要在线处理 $m$ 次操作：

`0 x k` 表示发生了一次地震，震中城市为 $x$，影响范围为 $k$，所有与 $x$ 距离不超过 $k$ 的城市都将受到影响，该次地震造成的经济损失为所有受影响城市的价值和。

`1 x y` 表示第 $x$ 个城市的价值变成了 $y$ 。

为了体现程序的在线性，操作中的 $x$、$y$、$k$ 都需要异或你程序上一次的输出来解密，如果之前没有输出，则默认上一次的输出为 $0$ 。


## 输入格式

第一行包含两个正整数 $n$ 和 $m$ 。

第二行包含 $n$ 个正整数，第 $i$ 个数表示 $value_i$ 。

接下来 $n-1$ 行，每行包含两个正整数 $u$、$v$，表示 $u$ 和 $v$ 之间有一条无向边。

接下来 $m$ 行，每行包含三个数，表示 $m$ 次操作。
## 输出格式

包含若干行，对于每个询问输出一行一个正整数表示答案。
## 样例

### 样例输入 #1
```
8 1
1 10 100 1000 10000 100000 1000000 10000000
1 2
1 3
2 4
2 5
3 6
3 7
3 8
0 3 1
```
### 样例输出 #1
```
11100101
```
## 提示

#### 数据规模与约定

对于 $100 \%$ 的数据，有 $1\leq n,m\leq 10^5, 1\leq u,v,x\leq n, 1\leq value_i,y\leq 10^4,0\leq k\leq n-1$ 。

upd：样例范围与题目真实数据范围不同，以提示中给出的数据范围为准。

#### 说明
题目来源：BZOJ3730。


---

---
title: "「StOI-1」小Z的旅行"
layout: "post"
diff: 省选/NOI-
pid: P6375
tag: ['线段树', '树状数组', '期望']
---
# 「StOI-1」小Z的旅行
## 题目描述

一块空地，有$n$座山，每座山有一个高度值$h$。小Z在最高的山上，要去最低的山。

他有如下移动方案：

$1.$ 移动到一座比当前山低的山；

$2.$ 移动到和当前山一样高的山（不可停留在当前山），对于每一高度只能执行一次该方案（即不可以连续 $3$ 次或以上到达同一高度的山）。

每次移动都会耗费体力值，耗费的体力值为两座山的水平距离（若从第 $i$ 座山移动到第 $j$ 座山，则耗费 |$i-j$| 点体力值）。

小Z**每次**若有多种方案移动，则会**等概率**选择任意一种，求耗费体力值的期望对 $998,244,353$ 取余后的结果。
## 输入格式

第一行一个正整数 $n$ ，表示山的个数。
接下来一行 $n$ 个正整数，表示每座山的高度。
## 输出格式

一个整数，表示最终答案对 $998,244,353$ 取余后的结果。
## 样例

### 样例输入 #1
```
4
1 3 3 7

```
### 样例输出 #1
```
332748121
```
### 样例输入 #2
```
3
1 3 2
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
10
1 2 2 2 4 3 2 6 5 9
```
### 样例输出 #3
```
384244861
```
## 提示

---

#### 样例1解释

取模前值为 $\frac{10}{3}$。

有如下方案（数字代表山的编号）：

1. $(4,1)$ 概率 $\frac{1}{3}$ ， 耗费体力值 $3$ ；

2. $(4,3,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $3$ ；

3. $(4,2,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $3$ ；

4. $(4,3,2,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $3$ ； 

5. $(4,2,3,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $5$ 。

---

#### 数据范围

对于 $50$% 的数据：$1 ≤ n ≤ 1000$，$1 ≤ h ≤ 10^{9}$；  
对于 $100$% 的数据：$1 ≤ n ≤ 500000$，$1 ≤ h ≤ 10^{9}$。

所有数据：最低和最高的山高度唯一。


---

---
title: "[省选联考 2020 A/B 卷] 冰火战士"
layout: "post"
diff: 省选/NOI-
pid: P6619
tag: ['2020', '线段树', '二分', '各省省选', '树状数组', '离散化']
---
# [省选联考 2020 A/B 卷] 冰火战士
## 题目背景

A 卷 D1T1，B 卷 D1T3。

时限 3s，内存 512MB。
## 题目描述

一场比赛即将开始。

每位战士有两个属性：温度和能量，有两派战士：冰系战士的技能会对周围造成降温冰冻伤害，因而要求场地温度不低于他的自身温度才能参赛；火系战士的技能会对周围造成升温灼烧伤害，因而要求场地温度不高于他的自身温度才能参赛。

当场地温度确定时，双方能够参赛的战士分别排成一队。冰系战士按自身温度从低到高排序，火系战士按自身温度从高到低排序，温度相同时能量大的战士排在前面。首先，双方的第一位战士之间展开战斗，两位战士消耗相同的能量，能量少的战士将耗尽能量退出比赛，而能量有剩余的战士将继续和对方的下一位战士战斗（能量都耗尽则双方下一位战士之间展开战斗）。如此循环，直至某方战士队列为空，比赛结束。

你需要寻找最佳场地温度：使冰火双方消耗总能量最高的温度的最高值。

现在，比赛还处于报名阶段，目前还没有任何战士报名，接下来你将不断地收到报名信息和撤回信息。其中，报名信息包含报名战士的派系和两个属性，撤回信息包含要撤回的报名信息的序号。每当报名情况发生变化（即收到一条信息）时，你需要立即报出当前局面下的最佳场地温度，以及该场地温度下双方消耗的总能量之和是多少。若当前局面下无论何种温度都无法开展比赛（某一方没有战士能参赛），则只要输出 `Peace`。
## 输入格式

第一行一个数 $Q$，表示信息的数量。

接下来 $Q$ 行，每行为 `1 t x y` $(t \in \{0, 1\}$，$x$ 和 $y$ 都是正整数 $)$ 或 `2 k`（$k$ 是正整数）：

`1 t x y` 表示一条报名信息，$t = 0$ 时报名战士是冰系，$t = 1$ 时报名战士是火系，$x$ 表示战士的自身温度，$y$ 表示战士的能量。

`2 k` 表示一条撤回信息，撤回的是第 $k$ 条信息。被撤回的信息一定是报名信息，已被撤回的信息不会再次被撤回。
## 输出格式

共 $Q$ 行，每行有两个用空格隔开的正整数，分别表示当前局面下的最佳温度和该温度下冰火双方消耗的总能量之和。
## 样例

### 样例输入 #1
```
8
1 1 103 150
1 0 100 100
1 1 102 150
1 0 103 300
2 1
1 1 101 100
1 1 104 350
1 0 100 400
```
### 样例输出 #1
```
Peace
103 200
103 200
103 300
102 200
102 200
104 700
102 1000
```
## 提示

#### 样例 1 解释
为说明方便，约定：若第 $k$ 条信息是报名信息，则该条报名信息对应战士 $k$。样例中含有战士 $1,2,3,4,6,7,8$，由于第 $5$ 条是撤回信息，所以没有战士 $5$。

下面逐个解释每个输出：

1. 只有火系战士：战士 $1$，无法比赛，输出 `Peace`。
2. 温度为 $100 \sim 103$ 都能消耗最多的能量 $200$：战士 $1$ 对阵战士 $2$ 消耗能量 $200$，最佳温度为 $103$。
3. 温度为 $100 \sim 103$ 都能消耗最多的能量 $200$：战士 $1$ 对阵战士 $2$ 消耗能量 $200$，最佳温度为 $103$。
4. 温度 $103$ 能消耗最多的能量 $300$：首先，战士 $1$ 对阵战士 $2$ 消耗能量 $200$；然后，战士 $1$ 对阵战士 $4$ 消耗能量 $100$，最佳温度为 $103$。
5. 从现在起战士 $1$ 不再存在。温度 $100 \sim 102$ 能消耗最多的能量 $200$：战士 $2$ 对阵战士 $3$ 消耗能量 $200$，最佳温度为 $102$。

#### 样例 2

见附加文件中 `icefire2.in` 与 `icefire2.ans`。

#### 数据范围

$10\%$ 的数据：$Q \leq 100$，$x \leq 10^3$。

另有 $20\%$ 的数据：$Q \leq 10^4$，$x \leq 5000$，不存在撤回信息，且输入的 $x$ 按顺序不降。

$60\%$ 的数据（包含上述 $20\%$，下同）：$Q \leq 2 \times 10^5$，$x \leq 2 \times 10^5$。

$90\%$ 的数据：$Q \leq 2 \times 10^6$，$x \leq 2 \times 10^6$。

$100\%$ 的数据：$1 \leq Q \leq 2 \times 10^6$，$1 \leq x \leq 2 \times 10^9$，所有 $y$ 之和不超过 $2 \times 10^9$，保证不存在 $t, x, y$ 完全相同的两个战士。


---

---
title: "「StOI-2」独立集"
layout: "post"
diff: 省选/NOI-
pid: P6799
tag: ['动态规划 DP', '树状数组', 'O2优化']
---
# 「StOI-2」独立集
## 题目描述

一棵由 $n$ 个点组成的无根树，给定 $m$ 条树上的路径，请求出由这 $m$ 条路径组成的`独立集`方案总数。

由于这个答案可能很大，您只需求出它对 $998,244,353$ 取模的结果即可。

所谓`独立集`，就是一个路径集合，满足这个集合中**不存在**一对在树上有交点的路径。特殊的，空集和只包括一条路径的集合也是独立集。


## 输入格式

第一行两个正整数，$n$ 和 $m$ ，表示点数和路径数。    
接下来 $n-1$ 行，每行两个正整数 $u_{i}$ 和 $v_{i}$ ，表示树的每条边。   
接下来 $m$ 行，每行两个正整数 $a_{i}$ 和 $b_{i}$ ，表示给定的每条路径。
## 输出格式

输出一个正整数，表示最终的答案。
## 样例

### 样例输入 #1
```
5 3
1 2
2 3
2 4
1 5
1 5
2 3
2 4
```
### 样例输出 #1
```
6
```
## 提示

**请注意常数因子对程序执行效率的影响**

## 样例解释


总共有 $2^3=8$ 个集合。

有两个集合 { {2,3} ，{2,4} } 与 { {1,5} ，{2,3} ，{2,4} } 不符合要求。

故样例答案为 $8-2=6$ 。

## 数据范围

对于 $10\%$ 的数据：$1 \leq n \leq 10$ ，$1 \leq m \leq 10$。   
对于 $20\%$ 的数据：$1 \leq n \leq 100$ ，$1 \leq m \leq 100$ 。   
对于另 $30\%$ 的数据：$1 \leq m \leq 15$ 。   
对于另 $10\%$ 的数据：$1 \leq n,m \leq 10^{5}$。    
对于另 $20\%$ 的数据：$u_{i}=i,v_{i}=i+1$。   
对于 $100\%$ 的数据：$1\leq n,m \leq 5 \times 10^{5}$ 。


---

---
title: "[COCI 2016/2017 #3] Zoltan"
layout: "post"
diff: 省选/NOI-
pid: P6885
tag: ['动态规划 DP', '2016', '树状数组', 'COCI（克罗地亚）']
---
# [COCI 2016/2017 #3] Zoltan
## 题目描述

Marton 的朋友 Cero 有一个由 $N$ 个正整数组成的数组。

首先 Cero 会在黑板上写下这个数组中的第一个数字。接下来他会在之前写下的所有数的左边或者右边写下一个数字。重复以上操作得到一个序列。

请注意，根据上述方法构造出的两个序列相同**当且仅当每一个数字写下的顺序完全相同**。例如，$1,1$ 可能和 $1,1$ 不同，前者的第二个数在第一个数的左边，后者的第二个数在第一个数的右边。

求这些数组成的所有序列中，最长严格递增子序列长度的最大值 $M$，以及所有最长严格递增子序列长度等于 $M$ 的序列中，最长严格递增子序列个数的总和。考虑到答案可能很大，Marton 只想知道这个数对 $10^9+7$ 取模的值。
## 输入格式

第一行包含一个正整数 $N$。

接下来的一行包含 $N$ 个正整数，表示按顺序给出的这个数组的各个元素。
## 输出格式

仅一行，输出这个最长的子序列长度以及总个数模上 $10^9+7$ 的值。
## 样例

### 样例输入 #1
```
2
1 1 
```
### 样例输出 #1
```
1 4 
```
### 样例输入 #2
```
4
2 1 3 4 
```
### 样例输出 #2
```
4 1
```
## 提示

### 样例解释

#### 样例 1 解释

Cero 可以构造 $2$ 个不同的序列，$1,1$ 和 $1,1$。

显然最长的严格上升子序列长度为 $1$，有 $4$ 个子序列满足。

#### 样例 2 解释

最长的严格上升子序列长度为 $4$，只有 $1,2,3,4$ 满足。
 
### 数据规模与约定

对于 $30\%$ 的数据，满足 $N\le 20$。

对于 $50\%$ 的数据，满足 $N\le 10^3$。

对于 $100\%$ 的数据，满足 $N\le 2\times10^5$，数组中的每个元素 $\le10^9$。

### 说明

**题目译自 [COCI2016-2017](https://hsin.hr/coci/archive/2016_2017/) [CONTEST #3](https://hsin.hr/coci/archive/2016_2017/contest3_tasks.pdf) _T5 Zoltan_**。

样例 1,2 的解释非官方。


---

---
title: "[NOI1998] 免费的馅饼"
layout: "post"
diff: 省选/NOI-
pid: P7302
tag: ['动态规划 DP', '1998', '线段树', '树状数组', 'NOI']
---
# [NOI1998] 免费的馅饼
## 题目描述

SERKOI 最新推出了一种叫做“免费馅饼”的游戏：游戏在一个舞台上进行。舞台的宽度为 $w$ 格（从左到右依次用 $1$ 到 $w$ 编号），游戏者占一格。开始时游戏者可以站在舞台的任意位置，手里拿着一个托盘。下图为天幕的高度为 $4$ 格时某一个时刻游戏者接馅饼的情景。

![](https://cdn.luogu.com.cn/upload/image_hosting/1gcg9awi.png)

游戏开始后，从舞台天幕顶端的格子中不断出现馅饼并垂直下落。游戏者左右移动去接馅饼。游戏者每秒可以向左或向右移动一格或两格，也可以站在原地不动。

当馅饼在某一时刻恰好到达游戏者所在的格子中，游戏者就收集到了这块馅饼。当馅饼落在一个游戏者不在的格子里时该馅饼就消失。

写一个程序，帮助我们的游戏者收集馅饼，使得所收集馅饼的分数之和最大。
## 输入格式

第一行是用空格隔开的两个正整数，分别给出了舞台的宽度 $w$ 和馅饼的个数 $n$。

接下来 $n$ 行，每一行给出了一块馅饼的信息。

由三个正整数组成，分别表示了每个馅饼落到舞台上的时刻 $t_i$，掉到舞台上的格子的编号 $p_i$，以及分值 $v_i$。

游戏开始时刻为 $0$。

输入文件中同一行相邻两项之间用一个空格隔开。

输入数据中可能存在两个馅饼的 $t_i$ 和 $p_i$ 都一样。
## 输出格式

一个数，表示游戏者获得的最大总得分。
## 样例

### 样例输入 #1
```
3 4
1 2 3
5 2 3
6 3 4
1 1 5
 
```
### 样例输出 #1
```
12
```
## 提示

对于 $100\%$ 的数据，$1 \leq w \leq 10^8$，$1 \leq n \leq 10^5$，$1\leq t_i \leq 10^8$，$1\leq p_i \leq w$，$1\leq v_i \leq 1000$。


---

---
title: "[THUPC 2017] 天天爱射击"
layout: "post"
diff: 省选/NOI-
pid: P7424
tag: ['2017', '树状数组', '可持久化线段树', '可持久化', '分块', '整体二分', 'THUPC']
---
# [THUPC 2017] 天天爱射击
## 题目描述

小 C 爱上了一款名字叫做《天天爱射击》的游戏。如图所示，这个游戏有一些平行于 $x$ 轴的木板。现在有一些子弹，按顺序沿着 $y$ 轴方向向这些木板射去。第 $i$ 块木板被 $S_i$ 个子弹贯穿以后，就会碎掉消失。一个子弹可以贯穿其弹道上的全部木板，特别的，如果一个子弹触碰到木板的边缘，也视为贯穿木板。

小 C 现在知道了游戏中 $n$ 块木板位置，以及知道了 $m$ 个子弹射击位置。现在问你每个子弹射出去以后，有多少木板会碎掉？
## 输入格式

从标准输入读入数据。

第一行两个整数 $n$ 和 $m$，表示木板数量和子弹数量。其中 $1\le n,m\le 2\times 10^5$。

接下来 $n$ 行，每行三个整数 $x_1,x_2,s$，表示每块木板的左端点 $x$ 坐标、右端点 $x$ 坐标，以及贯穿多少次会碎掉。其中保证 $1\le x_1\le x_2\le2\times 10^5,1\le s\le 2\times 10^5$。

接下来 $m$ 行，每行一个整数 ，表示每个子弹的 $x$ 坐标。子弹按照发射顺序给出。其中保证 $1\le x\le2\times 10^5$。
## 输出格式

输出到标准输出。

$m$ 行，每行一个整数。表示每颗子弹射出去后，有多少木板碎掉。
## 样例

### 样例输入 #1
```
3 2
1 3 1
2 4 2
3 4 1
2
3
```
### 样例输出 #1
```
1
2
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/ocqlbnl3.png)
#### 版权信息
来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2017。

$\text{upd}2021.7.6$：感谢 @[jiangbowen](https://www.luogu.com.cn/user/366807) 提供的一组 hack 数据，不计分，但若不通过 hack 数据则不算通过此题。


---

---
title: "[CCO 2021] Swap Swap Sort"
layout: "post"
diff: 省选/NOI-
pid: P7828
tag: ['树状数组', '2021', 'CCO（加拿大）', '根号分治']
---
# [CCO 2021] Swap Swap Sort
## 题目描述

你有一个长度为 $n$ 的序列，每项都是不超过 $k$ 的正整数。

你的朋友发明了一个排序算法，可以根据一个 $1 \sim k$ 的排列对序列进行排序，排序后序列中任意两个不相等的数的相对位置与排列中的相对位置相同。他的算法只使用了邻项交换的操作，且总是保证操作次数最少。为了方便描述，他将这个 $1 \sim k$ 的排列称为目标排列。

例如，序列为 $[1, 4, 2, 1, 2]$，目标排列为 $[4, 1, 2, 3]$，排序后为 $[4, 1, 1, 2, 2]$。

你对你朋友的排序算法在目标排列不同时执行 swap 的次数很感兴趣。为了研究其中的规律，你一开始将目标排列设置为 $1 \sim k$，并以此进行 $q$ 次操作，每次操作交换目标排列中相邻的两个数的位置。每次交换后，你想知道如果用他的排序算法对原序列进行排序会执行 swap 的次数。
## 输入格式

第一行，三个整数 $n, k, q$。

第二行，$n$ 个正整数 $a_1, a_2, \cdots, a_n$，表示原序列。

接下来 $q$ 行，每行一个正整数 $b$，表示交换目标排列中的第 $b$ 和第 $b + 1$ 个数。
## 输出格式

对于每次询问，输出一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
5 4 3
1 4 2 1 2
3
2
1
```
### 样例输出 #1
```
4
2
2
```
## 提示

#### 数据范围
**由于官方数据包过大，本题只节选了官方数据的 $\frac{20}{27}$。**

对于 $\frac{4}{27}$ 的数据，$1 \leq n, q \leq 5 \times 10^3$；

对于另外 $\frac{4}{27}$ 的数据，$1 \leq q \leq 100$；

对于另外 $\frac{7}{54}$ 的数据，$1 \leq k \leq 500$；

对于 $100\%$ 的数据，$1 \leq n, k \leq 10^5$，$1 \leq q \leq 10^6$，$1 \leq a_i \leq k$，$1 \leq b < k$。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D1T1


---

---
title: "[Cnoi2021] 绀珠传说"
layout: "post"
diff: 省选/NOI-
pid: P8108
tag: ['动态规划 DP', '树状数组', '2021', 'O2优化']
---
# [Cnoi2021] 绀珠传说
## 题目背景

Cirno 编写了一款新的游戏「绀珠传说 ~ Tales of Cyansis Pearl」。


游戏示例（样例 #1）:

![](https://cdn.luogu.com.cn/upload/image_hosting/pxvo35po.png)
## 题目描述

游戏规则如下:

初始有一个 $n\times n$ 的网格，每个格子内有一颗绀珠。

绀珠共有 $n$ 种颜色，每种颜色的恰有 $n$ 颗，**均匀随机**地分布在 $n\times n$ 的网格中。

每次玩家可以在网格的底端一行选取若干个连续相同颜色的绀珠并将其消除。

消除后，上层绀珠会受重力影响下落。

玩家重复上述操作直至绀珠全部被消除。游戏结束。

现在，Cirno 给定你游戏绀珠传说的一个**均匀随机**的初始局面，求完成游戏的最小步数。
## 输入格式

第一行，一个整数 $n$。

以下 $n$ 行，每行 $n$ 个整数，整数的范围为 $[1,n]$。

保证每个整数出现次数恰好为 $n$。
## 输出格式

一行，一个整数表示最小步数。
## 样例

### 样例输入 #1
```
3
1 1 2
2 3 1
3 2 3
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
5
2 1 4 4 2
2 5 5 1 3
4 1 3 5 1
3 2 5 3 5
1 4 4 2 3
```
### 样例输出 #2
```
15
```
## 提示

对于 $100\%$ 的数据保证 $1 \le n \le 1000$。保证数据**随机生成**。


---

---
title: "[USACO22OPEN] Up Down Subsequence P"
layout: "post"
diff: 省选/NOI-
pid: P8277
tag: ['动态规划 DP', 'USACO', '树状数组', '2022', '动态规划优化']
---
# [USACO22OPEN] Up Down Subsequence P
## 题目描述

Farmer John 的 $N$ 头奶牛（$2 \leq N \leq 3\cdot 10^5$），编号为 $1 \ldots N$，排列成 $1\ldots N$ 的一个排列 $p_1,p_2,\ldots,p_N$。另外给定一个长为 $N-1$ 的字符串，由字母 U 和 D 组成。请求出最大的 $K\le N-1$，使得存在 $p$ 的一个子序列 $a_0,a_1,\ldots,a_{K}$，满足对于所有 $1\le j\le K$，当字符串中第 $j$ 个字母是 U 时 $a_{j - 1} < a_j$，当字符串中的第 $j$ 个字母是 D 时 $a_{j - 1} > a_j$。

## 输入格式

输入的第一行包含 $N$。

第二行包含 $p_1,p_2,\ldots,p_N$。

最后一行包含给定的字符串。
## 输出格式

输出 $K$ 的最大可能值。
## 样例

### 样例输入 #1
```
5
1 5 3 4 2
UDUD
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
5
1 5 3 4 2
UUDD
```
### 样例输出 #2
```
3
```
## 提示

【样例解释 1】

我们可以选择 $[a_0,a_1,a_2,a_3,a_4]=[p_1,p_2,p_3,p_4,p_5]$；整个排列与给定的字符串相一致。

【样例解释 2】

我们可以选择 $[a_0,a_1,a_2,a_3]=[p_1,p_3,p_4,p_5]$。

【测试点性质】

- 测试点 3-4 满足 $N\le 500$。
- 测试点 5-8 满足 $N\le 5000$。
- 测试点 9-12 中，字符串中的 U 均在 D 之前。
- 测试点 13-22 没有额外限制。



---

---
title: "[USACO22DEC] Palindromes P"
layout: "post"
diff: 省选/NOI-
pid: P8908
tag: ['数学', 'USACO', '树状数组', '2022', '均摊分析']
---
# [USACO22DEC] Palindromes P
## 题目描述

农夫约翰合牛国（The United Cows of Farmer John，UCFJ）正在参加一年一度的蹄球锦标赛！UCFJ 队的 $N(1 \le N \le 7500)$ 头奶牛以微弱优势击败了 Farmer Nhoj 的队伍，赢得了蹄球比赛的金牌。

奶牛们已经为颁奖典礼排好了队。她们希望 FJ 拍摄 $\dfrac{N(N+1)}{2}$ 张合影，为队伍的每个连续子段拍摄一张。

然而，FJ，作为球队的主帅，对于奶牛们应该如何列队十分讲究。具体地说，他拒绝为一个子段拍照，除非它形成一个**回文串**，即对于所有不超过子段长度的正整数 $i$，从子段左端开始的第 $i$ 头奶牛的品种必须与从子段右端开始的第 $i$ 
头奶牛的品种相同。每头奶牛的品种是更赛牛（Guernsey）或荷斯坦牛（Holstein）之一。

对于队伍的 $\dfrac{N(N+1)}{2}$ 个连续子段的每一个，计算将该子段重新排列成回文串所需的最小换位次数（如果不可能这样做则为 $−1$）。单次换位是在子序列中取两头相邻的奶牛并交换。输出所有这些次数之和。

注意对每个连续子段所需的换位次数是独立计算的（奶牛们会在照片拍摄之间返回她们的起始位置）。 
## 输入格式

输入队伍，用一个长为 $N$ 的字符 $\texttt{G}$ 和 $\texttt{H}$ 组成的字符串表示。 
## 输出格式

输出队伍的所有 $\dfrac{N(N+1)}{2}$ 个连续子段的前述数量之和。 
## 样例

### 样例输入 #1
```
GHHGGHHGH
```
### 样例输出 #1
```
12
```
## 提示

### 样例 1 解释

前四个连续子段是 $\texttt{G}$，$\texttt{GH}$，$\texttt{GHH}$ 和 $\texttt{GHHG}$。$\texttt{G}$ 和 $\texttt{GHHG}$ 都已经是回文串，因此它们对总和的贡献为 $0$。$\texttt{GHH}$ 可以使用一次换位重新排列成回文串，因此它对总和的贡献为 $1$。$\texttt{GH}$ 不能使用任意次数的换位重新排列成回文串，因此它对总和的贡献为 $−1$。

$\texttt{HHGG}$ 是另一个对总和有贡献的连续子段。这个子段可以使用两次换位重新排列成回文串。 

### 测试点性质

除样例外有十五个测试点，满足 $N \in \{ 100,200,500,1000,2000,5000,5000,5000,5000,5000,7500,7500,7500,7500,7500\}$ 各一。


---

---
title: "[北大集训 2021] 经典游戏"
layout: "post"
diff: 省选/NOI-
pid: P8994
tag: ['树状数组', '2021', 'O2优化', '分治', '树链剖分', '字典树 Trie', 'SG 函数']
---
# [北大集训 2021] 经典游戏
## 题目背景

CTT2021 D4T2
## 题目描述

某天，`C` 和 `K` 觉得很无聊，于是决定玩一个经典小游戏：

在一棵有 $n$ 个结点的有根树上，标号为 $i$ 的节点上有 $a_i$ 个棋子。游戏时玩家轮流操作，每次可以将任意一个节点 $u$ 上的一个棋子放置到任意一个点 $v \in U(u)$上，其中 $U(u)=subtree\{u\}\setminus\{u\}$ ，表示 $u$ 的子树内（不包含 $u$ 本身）的点组成的集合。不能进行操作者失败。

而 `C` 和 `K` 作为 `P**` 和 `T**` 的在读学生，这种一眼就能找出必胜策略的游戏实在是索然无味，于是两人觉得，每个人给自己一个特殊能力可能会比较有趣：

`C` 在开始游戏之前，**可以选择**将当前树的树根 $R$ 换到与 $R$ 相邻的任意一个点 $R^{\prime}$ 上。定义两个点相邻当且仅当这两个点有边直接相连。

`K` 在开始游戏之前，**必须选择**树上的一个节点，在上面加上一颗棋子。

`C` 和 `K` 决定玩 $m$ 局游戏。每局游戏的流程如下：

1. 游戏开始前，`C` 和 `K` 会商量好，先在标号为 $x$ 的节点上放上一个棋子，然后将树根设为 $y$。
2. 之后 `C` 可以选择是否发动特殊能力，`C` 决策完之后 `K` 可以选择是否发动特殊能力。
3. 特殊能力的决策结束后，会在这棵树上进行一局 `C` 先手、`K` 后手的游戏。游戏完成后会将树上棋子的状态**还原到流程 `1` 结束后的状态**。

`C` 觉得这个游戏可以出成一个简单题，于是他决定考考你：`C` 在每局游戏的第二步的时候，有多少种决策方式使得不管 `K` 如何进行特殊能力的操作，开始游戏时都存在**必胜策略**？两种决策方式不同，**当且仅当**两种决策**更换的树根** $R^{\prime}$ **不同**，或者**两者中仅有一个没有发动特殊能力**。

## 输入格式

第一行包括一个整数，表示该测试点所在的子任务的分数。你可以使用这个信息判断该测试点满足的特殊性质。特别的，下发样例中此行使用 $0$ 代替。

第二行包含两个用空格隔开的正整数 $n, m$，表示树的节点数目以及游戏的轮数。树上的节点从 $1$ 到 $n$ 编号。

接下来 $n-1$ 行，每行包含两个用空格隔开的正整数 $u_i,v_i$，满足 $1 \le u_i,v_i \le n$，表示编号为 $u_i$ 和 $v_i$ 的节点之间有边直接相连。

接下来一行包含 $n$ 个用空格隔开的整数 $a_1,a_2,\ldots,a_n$，满足 $0 \leq a_1,a_2,\ldots,a_n \leq 10^9$。

接下来 $m$ 行，每行包含两个用空格隔开的正整数 $x, y$ 描述一局游戏，满足 $1 \le x,y \le n$。

## 输出格式


你需要输出 $m$ 行，其中第 $i$ 行应当包含一个非负整数 $x$ 表示第 $i$ 局游戏中，`C` 存在多少种使用特殊能力的决策方案，使得 `C` 在这局游戏中存在必胜策略。注意，**不使用特殊能力**也是一种**可能可行**的决策方案。

## 样例

### 样例输入 #1
```
0
5 2
1 2
1 3
2 4
2 5
1 0 1 0 1
2 2
4 4
```
### 样例输出 #1
```
2
1

```
### 样例输入 #2
```
0
10 10
6 3
7 4
8 2
2 1
9 1
1 3
3 4
4 5
5 10
0 0 1 1 1 0 1 1 0 0 
8 3
2 3
7 10
7 3
6 7
8 5
9 8
2 10
5 4
3 9

```
### 样例输出 #2
```
1
1
0
1
1
1
0
0
2
1

```
## 提示

| 子任务分数 | $1\le n,m\le$ | $\max\{a_1,a_2,\dots,a_n\}\le$ |              特殊性质              |
| :--------: | :-----------: | :----------------------------: | :--------------------------------: |
|    $16$    |      $5$      |              $1$               |                 无                 |
|    $15$    |     $300$     |              $1$               |                 无                 |
|    $14$    |    $5000$     |             $10^9$             |                 无                 |
|    $13$    |   $100000$    |             $10^9$             |        保证给出的树是一条链        |
|    $12$    |   $100000$    |             $10^9$             | 保证给出的树存在一个点度数为 $n-1$ |
|    $11$    |   $100000$    |             $10^9$             |   保证 $m$ 次游戏初始给定根一致    |
|    $10$    |   $500000$    |             $10^9$             |                 无                 |
|    $9$     |   $1000000$   |             $10^9$             |                 无                 |





---

---
title: "「GMOI R2-T3」粒子环游"
layout: "post"
diff: 省选/NOI-
pid: P9200
tag: ['数学', '线段树', '二分', '树状数组', '洛谷原创', 'O2优化', '枚举', '洛谷月赛']
---
# 「GMOI R2-T3」粒子环游
## 题目背景

热爱珂学的小 Z 正在进行一项无聊的实验。
## 题目描述

实验室中有一个由 $n$ 个实验腔连接而成的环形轨道，其中第 $i$ 个实验腔顺时针连向第 $i+1$ 个实验腔（特别的，第 $n$ 个实验腔连向第 $1$ 个实验腔）。同时还有一个标号为 $n+1$ 的新建实验腔要接入这个环形轨道。它可以接在任意两个原本相连的实验腔之间。

第 $i$ 个实验腔可以将带电荷量为 $Q$ 的粒子运输到它的下一个实验腔，这个过程花费的能量为 $\vert Q \vert \times c_i$。除此之外，第 $i$ 个实验腔本身就存储了量为 $e_i$ 的电荷（电荷量有正负）。由于众所周知的电荷守恒定律，第 $n+1$ 个实验腔储存的电荷量与前 $n$ 个实验腔储存的总电荷量的代数和为 $0$。

小 Z 有一个原本不带电的粒子。等到第 $n+1$ 个实验腔接入轨道后，他要任选一个实验腔（包括第 $n+1$ 个）作为出发点，将粒子放入，并使之在实验腔的能量驱动下顺时针环游一周回到出发点。粒子每到达一个实验腔（包括出发点），它所带电荷量就会变成原来所带的电荷量和这个实验腔所储存的电荷量的代数和。

**注意：电荷量会先加上实验腔所含电荷量，再计算能量贡献。**

现在，小 Z 想知道，在所有接入新建实验腔并选定出发点的方案中，粒子环游一周所需的能量最少为多少？
## 输入格式

第一行为一个正整数 $n$ ，表示环形轨道原有实验腔数。

第二行有 $n+1$ 个非负整数，依次表示 $c_1,c_2,...,c_{n+1}$。

第三行有 $n$ 个整数，依次表示 $e_1,e_2,...,e_{n}$。
## 输出格式

输出共一行，包括一个数，表示粒子环游一周所需的最少能量。
## 样例

### 样例输入 #1
```
3
1 3 2 2
3 -5 1
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
12
4 7 7 8 8 4 5 5 9 10 1 1 10 
0 -5 7 8 1 -1 -6 8 2 4 10 8 
```
### 样例输出 #2
```
509
```
## 提示

样例 $1$ 解释：一种最优方案为将 $4$ 号实验腔接在 $3$ 号实验腔与 $1$ 号实验腔之间，以 $4$ 号实验腔为出发点，花费能量为 $ 1\times 2\ +\ 4\times 1\ + \vert -1 \vert \times 3 \ +\ 0 \times 2 =9$。

**本题采用 Subtask 捆绑测试。**

| Subtask | $n\le$ | $c_i\le$ | $\vert e_i\vert$ | 特殊性质 | 对应测试点 | 总分 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $300$ | $100$ | $100$ | $-$ | $1\sim 5$ | $10$ |
| $1$ | $10^3$ | $10^3$ | $10^3$ | $\bf A$ | $6\sim 7$ | $5$ |
| $2$ | $10^4$ | $10^4$ | $10^4$ | $-$ | $8\sim12$ | $15$ |
| $3$ | $10^5$ | $10^5$ | $10^5$ | $\bf B$ | $13\sim 16$ | $10$ |
| $4$ | $2.5\times 10^5$ | $10^5$ |$10^5$ | $-$ | $17\sim 25$ | $60$ |

特殊性质 $\bf A$：对于所有的 $i\in[1,n+1](i\in \Z)$，满足 $c_i=0$。

特殊性质 $\bf B$：对于所有的 $i\in[1,n+1](i\in \Z)$，满足 $c_i=1$。

对于 $100\%$ 的数据，$1\le n\le 2.5\times 10^5$，$0\le c_i\le 10^5$，$0\le |e_i|\le 10^5$。

保证答案在 long long 范围内。


---

---
title: "「DROI」Round 2  进制与操作"
layout: "post"
diff: 省选/NOI-
pid: P9376
tag: ['莫队', '树状数组', 'O2优化', '可持久化线段树', '随机化']
---
# 「DROI」Round 2  进制与操作
## 题目背景

与其编写苍白无力的背景，不如出更有质量的题。
## 题目描述

定义数 $x$ 在 $B$ 进制下的一次操作为以下两种操作中的任意一种：

- 令 $x \rightarrow \lfloor \dfrac{x}{B} \rfloor$。

- 令 $x \rightarrow x \times B + t $。其中 $t \in [0,B-1]$。

现给定长度为 $n$ 的序列 $A$。$m$ 次询问，每次询问形如：

- `l r B` 表示询问将序列 $A$ 中下标在 $[l,r]$ 之内的数在 $B$ 进制下操作，至少多少次才能将所有数变为相同（注：每次操作是对**一个数**进行操作）。

**询问间相互独立，即操作不会真的进行。**


## 输入格式

第一个两个整数，分别表示 $n,m$。

第二行一行 $n$ 个数，表示序列 $A$。

接下来 $m$ 行，每行三个数，分别表示这次询问的 $l,r,B$。
## 输出格式

输出共 $m$ 行，其中第 $i$ 行表示第 $i$ 次询问的答案。
## 样例

### 样例输入 #1
```
5 5
7 6 5 8 9
1 3 2
2 5 2
4 4 6
3 5 4
1 5 3
```
### 样例输出 #1
```
5
8
0
5 
10
```
### 样例输入 #2
```
8 4
10 14 7 11 19 13 7 18 
1 7 4
3 8 2
1 4 4
1 4 2

```
### 样例输出 #2
```
15
18
8
11

```
## 提示

### 样例解释

对于样例一，五次询问分别将区间内所有数变为 $3$、$4$、$8$、$4$、$6$ 是一种最优操作。

------------

### 数据范围 

**「本题采用捆绑测试」**

- $\operatorname{Subtask} 1(10\%)$：$n,m \leq 1000$。

- $\operatorname{Subtask} 2(20\%)$：保证所有询问 $B=2$。

- $\operatorname{Subtask} 3(40\%)$：$n,m \leq 3 \times 10^4$。

- $\operatorname{Subtask} 4(30\%)$：无特殊限制。

对于 $100\%$ 的数据：$1 \leq n,m \leq 10^5$，$2 \leq A_i,B \leq 10^8$。



---

---
title: "「TAOI-2」Ciallo～(∠・ω< )⌒★"
layout: "post"
diff: 省选/NOI-
pid: P9576
tag: ['二分', '树状数组', '洛谷原创', 'O2优化', '哈希 hashing', '洛谷月赛']
---
# 「TAOI-2」Ciallo～(∠・ω< )⌒★
## 题目背景

柚子厨差不多得了。

~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)

![](https://cdn.luogu.com.cn/upload/image_hosting/0nqiwonz.png)
## 题目描述

小 δ 喜欢造词。他学习了一种造词方法。

首先，他拥有一个「模板串」，设为 $s$。然后他会选择一对 $1 \le l \le r \le |s|$，将 $s$ 的第 $l$ 至 $r$ 个字符删掉，把两边的字符串拼起来，他设得到的这个新字符串为 $s'$。

接下来，他会选择一对新的 $1 \le l' \le r' \le |s'|$，然后设 $s'$ 的第 $l'$ 至 $r'$ 个字符组成的字符串为 $s''$。他所造出的这个词就是 $s''$。

例如，如果「模板串」为 $s=\texttt{cciaohalloo}$，那么一种造词方法是，选择 $l=5$，$r=7$，得到 $s'=\texttt{ccialloo}$，然后选择 $l'=2$，$r'=7$，得到 $s''=\texttt{ciallo}$。

现在小 δ 有一个「目标串」 $t$，他想知道有多少种不同的方案，可以使用「模板串」$s$ 造出单词 $t$。定义两种方案相同当且仅当选择的 $l,r,l',r'$ 均相同。
## 输入格式

共两行，分别为字符串 $s$ 和 $t$。
## 输出格式

共一行，代表造出「目标串」$t$ 的方案数。
## 样例

### 样例输入 #1
```
aabbaaba
aba
```
### 样例输出 #1
```
23
```
### 样例输入 #2
```
ciaohallo
ciallo
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
babacbbaababbacbababbabbbaaabaabababbabbabababba
ababab
```
### 样例输出 #3
```
1535
```
### 样例输入 #4
```
sssssssssssssssssssssssssssssssssssss
sss
```
### 样例输出 #4
```
15470
```
### 样例输入 #5
```
abcbbbcbcbcbacbacbaaabcbcbcbaabacbca
cb
```
### 样例输出 #5
```
3995
```
## 提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 0（6 points）：$|s| \le 400$，$|t| \le 200$。
- Subtask 1（10 points）：$|s| \le 700$，$|t| \le 300$。
- Subtask 2（10 points）：$\forall i,j,s_i=t_j$。
- Subtask 3（10 points）：$|t|=1$。
- Subtask 4（20 points）：$|s| \le 10^4$，$|t| \le 3 \times 10^3$。
- Subtask 5（14 points）：$|t|=2$。
- Subtask 6（30 points）：无特殊限制。

对于所有测试数据，$1 \le |s| \le 4 \times 10^5$，$1 \le |t| \le 2 \times 10^5$。$s,t$ 只包含小写英文字母。


---

---
title: "「Cfz Round 1」Wqs Game"
layout: "post"
diff: 省选/NOI-
pid: P9580
tag: ['树状数组', '洛谷原创', 'O2优化', '线性基', '洛谷月赛', '单调栈']
---
# 「Cfz Round 1」Wqs Game
## 题目背景

『博』和『奕』喜欢博弈，尤其喜欢 wqs 带权博弈。
## 题目描述

wqs 带权博弈在一个数列 $\{a_i\}$ 上进行，对应有一个 $01$ 串 $\{b_i\}$。

1. 若 $b_i=0$，则 $a_i$ 这个数字是属于『博』的；
2. 若 $b_i=1$，则 $a_i$ 这个数字是属于『奕』的。

游戏规则是，每次给定一个区间 $[l,r]$，从 $a_l$ 到 $a_r$，拥有这个数的人**依次**决定选该数或者不选，两个人都会采用**最优策略**。

因为『博』很强大，她会让着『奕』，于是博弈的规则是，如果最后两个人选的数**按位异或和不为零**，则『奕』获胜，否则『博』获胜。

注意每个人**能看到**对方的选数情况，可以选**多个**数（只要这个数是自己的），最后计算两个人选数的总**异或**和。

对于任意区间 $[l,r]$，若『奕』获胜，则 $w(l,r)=1$，否则 $w(l,r)=0$。

每次查询 $\sum\limits_{l=L}^R\sum\limits_{r=l}^Rw(l,r)$ 的值，对 $2^{32}$ 取模。

由于输入输出量过大，对于 $tp\ne 0$ 的测试点，选手需要自行生成数列 $a_i$ 和询问区间 $[L,R]$，并用特殊方式输出答案。

注意正解**不依赖**特殊的输入输出方式。
## 输入格式

第一行三个正整数 $n,q,tp$，表示数列长度，天数以及每天局数，以及读入方式。

第二行一个长度为 $n$ 的字符串，表示 $01$ 串 $\{b_i\}$；

若 $tp=0$，则第三行 $n$ 个正整数，表示数列 $\{a_i\}$，接下来 $q$ 行，每行两个正整数 $L,R$，表示询问  $\sum\limits_{l=L}^R\sum\limits_{r=l}^Rw(l,r)$ 对 $2^{32}$ 取模的值。

否则，令 `Sd` 初值为 $tp$，`Cnt` 初值为 $0$，先使用函数 `GetA` 依次生成 $a_i$，再使用函数 `GetLR` 依次生成 $L,R$，具体方式以代码形式后附。
## 输出格式

若 $tp=0$ 则输出 $q$ 行，每行一个正整数，表示该询问的答案。

否则，令 $ans_i$ 为第 $i$ 次询问的答案，你需要输出 $(ans_i\times i)\bmod 2^{32}$ 的**按位异或和**。
## 样例

### 样例输入 #1
```
3 2 0
100
3 1 2
1 3
2 3
```
### 样例输出 #1
```
2
0
```
### 样例输入 #2
```
5 2 0
10100
2 7 6 3 5
1 5
2 4
```
### 样例输出 #2
```
8
4
```
### 样例输入 #3
```
20 100 8551679995685981130
11001000000000000000
```
### 样例输出 #3
```
1673
```
## 提示

#### 【样例解释 #1】

只有 $w(1,1)=w(1,2)=1$。

对于区间 $[1,3]$，如果『奕』选第一个数，则『博』选后两个数，否则『博』不选，于是『博』获胜。

注意是从左往右依次选取，『博』在选后两个数之前能够知道『奕』是否选了第一个数。

#### 【样例解释 #2】

只有 $w(1,1)=w(1,2)=w(1,3)=w(1,4)=w(2,3)=w(2,4)=w(3,3)=w(3,4)=1$。

#### 【样例解释 #3】

由于本样例 $tp\ne 0$，所以你需要使用特殊方式输入输出。

#### 【数据范围】

对于所有数据，$1\le n\le5\times10^5,1\le q\le 1.5\times10^6,0<a_i<2^{60},1\le L\le R\le n,0\le tp<2^{64}$。

| 子任务编号 | 分值 |    $n\le$     |     $q\le$      |  $tp$  |  $a_i<$  | 特殊性质 |
| :--------: | :--: | :-----------: | :-------------: | :----: | :------: | :------: |
|    $1$     | $6$  |     $20$      |      $100$      |  $=0$  | $2^{60}$ |    有    |
|    $2$     | $7$  |     $100$     |     $10^3$      |  $=0$  | $2^{10}$ |    有    |
|    $3$     | $8$  |     $700$     |     $10^3$      |  $=0$  | $2^{10}$ |    无    |
|    $4$     | $9$  |    $3000$     |     $10^5$      |  $=0$  | $2^{60}$ |    无    |
|    $5$     | $14$ | $3\times10^4$ |     $10^5$      |  $=0$  | $2^{20}$ |    无    |
|    $6$     | $17$ | $2\times10^5$ | $1.5\times10^6$ | $\ge1$ | $2^{60}$ |    有    |
|    $7$     | $19$ | $5\times10^5$ | $1.5\times10^6$ | $\ge1$ | $2^{60}$ |    有    |
|    $8$     | $20$ | $5\times10^5$ | $1.5\times10^6$ | $\ge1$ | $2^{60}$ |    无    |

特殊性质：序列 $b_i$ 中最多有 $10$ 个 $0$。

#### 【备注】

数据生成方式：

```cpp
using ul=unsigned long long;
using ui=unsigned int;
ui Ans,ans;
ul Sd,Cnt;
ul Rd(){Sd^=Sd<<19,Sd^=Sd>>12,Sd^=Sd<<29;return Sd^=++Cnt;}
void GetA(ul &a){a=Rd()%((1ull<<60)-2)+1;}
void GetLR(int &l,int &r){
    l=Rd()%n+1,r=Rd()%n+1;
    if(l>r)swap(l,r);
}
int main(){
    //read n,q,tp,b[i]
    if(tp){
        Sd=tp,Cnt=0;
        for(int i=1;i<=n;++i)GetA(a[i]);
        for(int qi=1;qi<=q;++qi){
            GetLR(l,r);
            //sol
            Ans^=ans*qi;
        }
        printf("%u\n",Ans);
	}
}
```


---

---
title: "「RiOI-03」网格"
layout: "post"
diff: 省选/NOI-
pid: P9917
tag: ['树状数组', '洛谷原创', 'O2优化', '洛谷月赛', '分类讨论']
---
# 「RiOI-03」网格
## 题目背景

2022 年某次集训讲课，课件中出现了一道以 MLE 真名首字母严格顺序作为输入变量的题目。MLE 就想在自己的题目里用 [vectorwyx](https://www.luogu.com.cn/user/238408) 的首字母当输入变量，于是就有了这道题。

可惜如今 [vectorwyx](https://www.luogu.com.cn/user/238408) 已经退役了，人生有梦，各自精彩。

## 题目描述

**请仔细阅读本题数据范围。**

给定一个 $n\times n$ 的正方形网格，一共有 $n$ 行，$n$ 列，初始时所有网格均为红色。有 $n$ 组询问，每次询问会把一整行或一整列的颜色全部染成红色或白色，每次询问后输出所有红色网格的周长，而且询问之间不独立。
## 输入格式

第一行为一个正整数 $n$；

接下来的 $n$ 行，每行三个正整数 $w,y,x$。$w$ 表示颜色，$w=1$ 表示染成红色，$w=0$ 表示染成白色。$y$ 表示行或列，$y=1$ 表示把第 $x$ 行全部染色，$y=0$ 表示把第 $x$ 列全部染色。
## 输出格式

一共有 $n$ 行，每行一个整数，表示每次修改后的红色部分周长。
## 样例

### 样例输入 #1
```
5
0 0 3
0 1 2
0 1 4
1 0 2
1 1 4
```
### 样例输出 #1
```
28
32
36
36
32

```
## 提示

### 样例解释

[样例图片解释](https://www.luogu.com.cn/paste/rvrhouei)

### 数据范围

对于 $100\%$ 的数据，$3\leq n \leq 10^6 $，$1<x<n$。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|} \hline
\textbf{\textsf{\#}}  & \bm{{n\le}} & \textbf{\textsf{特殊性质}} & \textbf{\textsf{\#}}  & \bm{{n\le}} & \textbf{\textsf{特殊性质}}\cr\hline
1  & 5 & - & 
11  & 10^5 & - \cr\hline
2  & 100 & - & 
12  & 10^5 & - \cr\hline
3  & 100 & - & 
13  & 10^5 & - \cr\hline
4  & 2000 & \textbf{A} & 
14  & 10^5 & - \cr\hline
5  & 2000 & \textbf{B} & 
15  & 10^6 & - \cr\hline
6  & 2000 & - & 
16  & 10^6 & - \cr\hline
7  & 10^5 & \textbf{AB} & 
17  & 10^6 & - \cr\hline
8  & 10^5 & \textbf{B} & 
18  & 10^6 & - \cr\hline
9  & 10^5 & \textbf{A} & 
19  & 10^6 & - \cr\hline
10  & 10^5 & - & 
20  & 10^6 & - \cr\hline
\end{array}
$$

- 特殊性质 $\bf A$：保证 $w=0$。
- 特殊性质 $\bf B$：保证 $y=0$。


---

