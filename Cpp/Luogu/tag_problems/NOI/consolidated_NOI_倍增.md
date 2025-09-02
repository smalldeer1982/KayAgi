---
title: "[USACO24FEB] Infinite Adventure P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10198
tag: ['倍增', 'USACO', '2024', 'O2优化']
---
# [USACO24FEB] Infinite Adventure P
## 题目背景

**注意：本题的内存限制为 512MB，通常限制的 2 倍。**
## 题目描述

Bessie 正在计划一次在 $N$（$1\le N\le 10^5$）个城市的大陆上的无尽冒险。每个城市 $i$ 都有一个传送门以及循环周期 $T_i$。所有 $T_i$ 均为 $2$ 的幂，且 $T_1+\cdots+T_N\le 10^5$。如果你在日期 $t$ 进入城市 $i$ 的传送门，那么你会立即从城市 $c_{i,t\bmod T_i}$ 的传送门出来。

Bessie 的旅行有 $Q$（$1\le Q\le 5\cdot 10^4$）个计划，每个计划由一个元组 $(v,t,\Delta)$ 组成。在每个计划中，她将于日期 $t$ 从城市 $v$ 出发。然后，她将执行以下操作 $\Delta$ 次：她将进入当前城市的传送门，然后等待一天。对于她的每一个计划，她想要知道她最终会在哪个城市。
## 输入格式

输入的第一行包含两个空格分隔的整数：结点的数量 $N$，以及询问的数量 $Q$。

第二行包含 $N$ 个空格分隔的整数：$T_1,T_2,\ldots,T_N$（$1\le T_i$，$T_i$ 是 $2$ 的幂，且 $T_1+\cdots+T_N\le 10^5$）。

对于 $i=1,2,\ldots,N$，第 $i+2$ 行包含 $T_i$ 个空格分隔的正整数，为 $c_{i,0},\ldots,c_{i,T_{i−1}}$（$1\le c_i,t\le N$）。

对于 $j=1,2,…,Q$，第 $j+N+2$ 行包含三个空格分隔的正整数 $v_j,t_j,\Delta_j$（$1\le v_j\le N$，$1\le t_j\le 10^{18}$，且 $1\le \Delta_j\le 10^{18}$），表示第 $j$ 个询问。 
## 输出格式

输出 $Q$ 行。第 $j$ 行包含第 $j$ 个询问的答案。 
## 样例

### 样例输入 #1
```
5 4
1 2 1 2 8
2
3 4
4
2 3
5 5 5 5 5 1 5 5
2 4 3
3 3 6
5 3 2
5 3 7
```
### 样例输出 #1
```
2
2
5
4
```
### 样例输入 #2
```
5 5
1 2 1 2 8
2
3 4
4
2 3
5 5 5 5 5 1 5 5
2 4 3
3 2 6
5 3 2
5 3 7
5 3 1000000000000000000
```
### 样例输出 #2
```
2
3
5
4
2
```
## 提示

### 样例解释 1

Bessie 的前三次冒险会如下进行：

- 在第一次冒险中，她于时刻 $4$ 从城市 $2$ 出发，于时刻 $5$ 到达城市 $3$，于时刻 $6$ 到达城市 $4$，于时刻 $7$ 到达城市 $2$。
- 在第二次冒险中，她于时刻 $3$ 从城市 $3$ 出发，于时刻 $4$ 到达城市 $4$，于时刻 $5$ 到达城市 $2$，于时刻 $6$ 到达城市 $4$，于时刻 $7$ 到达城市 $2$，于时刻 $8$ 到达城市 $4$，于时刻 $9$ 到达城市 $2$。
- 在第三次冒险中，她于时刻 $3$ 从城市 $5$ 出发，于时刻 $4$ 到达城市 $5$，于时刻 $5$ 到达城市 $5$。

### 测试点性质

- 测试点 $3$：$\Delta_j\le 2\cdot 10^2$。
- 测试点 $4-5$：$N,\sum T_j\le 2\cdot 10^3$。
- 测试点 $6-8$：$N,\sum T_j\le 10^4$。
- 测试点 $9-18$：没有额外限制。


---

---
title: "[JOI 2024 Final] 路网服务 2"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10209
tag: ['贪心', '倍增', '2024', 'JOI（日本）']
---
# [JOI 2024 Final] 路网服务 2
## 题目描述

JOI 市有一个由 $H$ 条东西向的无限长道路和 $W$ 条南北向的道路组成的网格状道路网。从北边数第 $i\ (1 \leq i \leq H)$ 条的东西向的道路和从西边数第 $j\ (1 \leq j \leq W)$ 条的南北向的道路相交的地方称作交叉点 $(i, j)$。

现在，由于道路年久失修，一部分道路被封锁了。具体的封锁情况如下：

- 如果 $A_{i, j}=0\ (1 \leq i \leq H,1 \leq j \leq W-1)$，则从北边数第 $i$ 条的东西向的道路的，交叉点 $(i, j)$ 和交叉点 $(i, j+1)$ 之间的部分就是封锁的；如果 $A_{i, j}=1$ 则是可以通行的。
- 如果 $B_{i, j}=0\ (1 \leq j \leq W,1 \leq i \leq H-1)$ 从西边数第 $j$ 条的南北向的道路的，交叉点 $(i, j)$ 和交叉点 $(i+1, j)$ 之间的部分就是封锁的；如果 $B_{i, j}=1$ 就是可以通行的。
- 道路的其他部分，即 $H \times W$ 个交叉点外面的部分都是封锁的。

JOI 市的市长 K 理事长决定制定一个道路维修计划。维修计划由大于等于 $0$ 次维修构成。一次维修时选择一个满足的整数 $i\ (1 \leq i \leq H)$，然后进行以下的操作：


对于**所有**满足 $1 \leq j \leq W-1$ 的整数 $j$，如果从北边数第 $i$ 条的东西向的道路的，交叉点 $(i, j)$ 和交叉点 $(i, j+1)$ 之间的部分是封锁的话，将其变成可以通行的。这个过程总共需要 $C_{i}$ 天。其中，$C_{i}$ 为 $1$ 或 $2$。

维修计划里包含的多次维修不能同时进行。因此，维修计划的执行所需要的天数是维修计划里包含的所有维修所需要的天数的总和。

为了让市里的重要设施之间能够互相通行，K 理事长向你提出了 $Q$ 个问题。第 $k\ (1 \leq k \leq Q)$ 个问题是这样的：

是否存在一个维修计划，能够让 $T_{k}$ 个交叉点 $(X_{k, 1}, Y_{k, 1}),(X_{k, 2}, Y_{k, 2}), \ldots ,(X_{k, T_{k}}, Y_{k, T_{k}})$ 之间，只通过可以通行的道路互相通行。如果存在的话，执行这样的维修计划最少需要多少天。

给定道路网的封锁情况，各条道路的维修所需要的天数，K 理事长的问题的内容，编写一个程序来回答 K 理事长的所有问题。
## 输入格式

第一行包含三个整数 $H,W,Q$。

接下来 $H$ 行，每行包含一个长度为 $W-1$ 的字符串，表示 $A_{i,1},A_{i,2},\ldots ,A_{i,W-1}$。

接下来 $H-1$ 行，每行包含一个长度为 $W$ 的字符串，表示 $B_{i,1},B_{i,2},\ldots ,B_{i,W}$。

接下来一行包含 $H$ 个用空格分隔的整数 $C_1,C_2,\ldots ,C_H$。

接下来有 $Q$ 个询问，每个询问用以下形式给出：

第一行包含一个整数 $T_k$。  
接下来 $T_k$ 行每行包含两个整数 $X_{k,i},Y_{k,i}$。
## 输出格式

输出 $Q$ 行，第 $k$ 行 $(1 \leq k \leq Q)$ 里，如果存在一个维修计划，能够让 $T_{k}$ 个交叉点 $(X_{k, 1}, Y_{k, 1}),(X_{k, 2}, Y_{k, 2}), \ldots ,(X_{k, T_{k}}, Y_{k, T_{k}})$ 之间互相通行，就输出执行这样的维修计划最少需要多少天。否则输出 $-1$。
## 样例

### 样例输入 #1
```
4 3 4
00
00
00
00
100
001
000
1 1 1 1
2
1 1
3 3
2
3 1
1 2
2
2 3
3 3
2
4 2
3 2
```
### 样例输出 #1
```
1
3
0
-1
```
### 样例输入 #2
```
4 4 4
100
110
011
010
0010
1001
0101
1 1 1 1
2
1 2
3 1
2
1 4
4 1
2
3 2
1 2
2
4 3
1 1
```
### 样例输出 #2
```
1
3
2
2
```
### 样例输入 #3
```
7 3 3
10
00
00
10
00
01
00
110
101
011
001
110
100
1 1 1 1 1 1 1
3
7 2
3 1
3 2
3
3 1
6 3
2 3
7
2 2
1 3
7 3
5 2
1 2
7 2
3 1
```
### 样例输出 #3
```
3
2
4
```
### 样例输入 #4
```
4 3 3
00
00
10
00
110
011
001
1 2 2 2
2
1 1
3 1
2
4 3
2 1
2
4 1
1 3
```
### 样例输出 #4
```
1
2
5
```
### 样例输入 #5
```
7 3 2
01
00
00
00
00
10
01
100
110
011
001
101
001
1 1 2 1 1 2 2
3
7 2
1 3
5 1
5
1 1
2 2
3 1
2 3
4 2
```
### 样例输出 #5
```
4
1
```
## 提示

对于所有输入数据，满足：

- $2 \leq H$
- $2 \leq W$
- $H \times W \leq 10^6$
- $1 \leq Q \leq 10^5$
- $A_{i, j}$ 为 $0$ 或 $1\ (1 \leq i \leq H, 1 \leq j \leq W-1)$
- $B_{i, j}$ 为 $0$ 或 $1\ (1 \leq i \leq H-1,1 \leq j \leq W)$
- $C_{i}$ 为 $1$ 或 $2\ (1 \leq i \leq H)$
- $2 \leq T_{k}\ (1 \leq k \leq Q)$
- $T_{1}+T_{2}+\cdots+T_{Q} \leq 2\times 10^5$
- $1 \leq X_{k, l} \leq H\ (1 \leq k \leq Q, 1 \leq l \leq T_{k})$
- $1 \leq Y_{k, l} \leq W\ (1 \leq k \leq Q, 1 \leq l \leq T_{k})$
- $(X_{k, 1}, Y_{k, 1}),(X_{k, 2}, Y_{k, 2}), \ldots,(X_{k, T_{k}}, Y_{k, T_{k}})$ 各不相同 $(1 \leq k \leq Q)$

详细子任务附加限制及分值如下表所示。

|子任务|	附加限制|	分值|
| :-: | :-: | :-:|
|1|	$C_{i}=1\ (1 \leq i \leq H), Q \leq 5, T_{k}=2\ (1 \leq k \leq Q), A_{i, j}=0\ (1 \leq i \leq H, 1 \leq j \leq W-1)$|	$10$|
|2|$	C_{i}=1\ (1 \leq i \leq H), Q \leq 5, T_{k}=2\ (1 \leq k \leq Q)$|	$6$
|3|	$C_{i}=1\ (1 \leq i \leq H), Q \leq 5$|	$15$|
|4|	$C_{i}=1\ (1 \leq i \leq H), T_{k}=2\ (1 \leq k \leq Q)$|	$11$|
|5|	$C_{i}=1\ (1 \leq i \leq H)$|	$6$|
|6|	$Q \leq 5$|	$12$|
|7|	$T_{k}=2\ (1 \leq k \leq Q)$|	$26$|
|8|	无附加限制	|$14$|


---

---
title: "[JOIST 2025] 展览会 3 / Exhibition 3"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11983
tag: ['贪心', '线段树', '倍增', '2025', 'JOI（日本）']
---
# [JOIST 2025] 展览会 3 / Exhibition 3
## 题目描述

JOI 美术馆计划近期举办一场绘画展览。馆方拥有编号为 $1$ 至 $N$ 的 $N$ 幅画作，其中画作 $i$（$1 \leq i \leq N$）的**美观值**为 $A_i$。在展览中这些画作将排成一行展示，但具体排列顺序尚未确定。

共有 $M$ 家杂志将对展览进行报道。这些杂志按影响力从大到小依次编号为 $1$ 至 $M$。每家杂志将发布展览中某一连续段画作的摄影照片。具体来说，杂志 $j$（$1 \leq j \leq M$）将发布排列中从左数第 $L_j, L_j + 1, \ldots, R_j$ 幅画作的照片。杂志 $j$（$1 \leq j \leq M$）报道的**吸引力**定义为该杂志所覆盖画作的最大美观值。

JOI 君作为 JOI 美术馆的馆长，希望通过排列画作使得这些杂志的报道更具吸引力，从而吸引更多参观者。由于影响力更大的杂志能触达更多受众，他优先希望提升更具影响力杂志的报道吸引力。

具体而言，设 $b_j$ 为杂志 $j$（$1 \leq j \leq M$）报道的吸引力，则 JOI 君希望排列画作，使得序列 $b = (b_1, b_2, \ldots, b_M)$ 的字典序最大化。

> 在这里，对于不同的数列 $ b = (b_1, b_2, \ldots, b_M) $ 和 $ b' = (b'_1, b'_2, \ldots, b'_M) $，所谓“$ b $ 在字典序上大于 $ b' $”，是指存在满足 $ b_k \neq b'_k $ 的最小下标 $ k $（$ 1 \leq k \leq M $），且对于该 $ k $ 有 $ b_k > b'_k $。

请编写一个程序，根据待展览画作的信息和报道展览的杂志信息，计算当画作排列使序列 $b = (b_1, b_2, \ldots, b_M)$ 字典序最大化时，每家杂志报道的吸引力。
## 输入格式

> $N$ $M$\
> $A_1$ $A_2$ $\cdots$ $A_n$\
> $L_1$ $R_1$\
> $L_2$ $R_2$\
> $\vdots$\
> $L_M$ $R_M$
## 输出格式

输出 $M$ 行，第 $i$ 行的正整数为 $b_i$。
## 样例

### 样例输入 #1
```
4 4
1 2 1 2
1 1
2 3
4 4
3 4
```
### 样例输出 #1
```
2
2
1
2
```
### 样例输入 #2
```
4 8
1 2 3 4
1 2
2 3
4 4
1 1
2 4
3 3
3 3
4 4
```
### 样例输出 #2
```
4
4
3
2
4
1
1
3
```
### 样例输入 #3
```
12 10
6 2 2 5 2 5 2 3 3 3 2 2
3 5
10 12
12 12
2 4
8 9
10 11
1 3
7 9
9 10
10 11
```
### 样例输出 #3
```
6
5
5
6
5
3
6
5
5
3
```
## 提示

### 样例解释

#### 样例 $1$ 解释


重排后每张画的美观值为 $[2,1,2,1]$，得到 $b=[2,2,1,2]$，可以证明是最优解。

该样例满足子任务 $1\sim 3,5,6$ 的限制。

#### 样例 $2$ 解释

该样例满足子任务 $1\sim 6$ 的限制。

#### 样例 $3$ 解释

该样例满足子任务 $1,2,6$ 的限制。


### 数据范围
- $1 ≤ N ≤ 10^5$；
- $1 ≤ M ≤ 10^5$；
- $1 ≤ A_i ≤ N$；
- $1 ≤ L_j ≤ R_j ≤ N$；
- 输入的都是整数。

### 子任务
- $\text{Subtask 1 (19 pts)}$：$N,M\le 400$；
- $\text{Subtask 2 (9 pts)}$：$N\le 400$；
- $\text{Subtask 3 (19 pts)}$：$A_i\le 5$；
- $\text{Subtask 4 (12 pts)}$：$A_i=i$；
- $\text{Subtask 5 (17 pts)}$：$\forall 1\le k\le N$，满足 $A_i=k$ 的 $i$ 至多只有 $5$ 个。
- $\text{Subtask 6 (24 pts)}$：无额外限制。


---

---
title: "[OOI 2024] Burenka and Pether"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13508
tag: ['线段树', '倍增', '2024', '分块', 'Moscow Olympiad']
---
# [OOI 2024] Burenka and Pether
## 题目描述

Once upon a time, the princess of Burlyandia, Burenka, decided to please her friend ReLu. Knowing that ReLu shares her interest in cryptocurrency, Burenka decided to create her own blockchain cryptocurrency called $\texttt{Pether}$.

After taking courses and training from an expert coach in personal growth in cybersecurity, Burenka decided that the currency $\texttt{Pether}$ should be protected in the best possible way. As a result, due to incredibly complex and convoluted restrictions, not all users can exchange $\texttt{Pether}$ with each other.

The structure of the $\texttt{Pether}$ blockchain currency is indeed complex and convoluted. All users are numbered with integers from $1$ to $n$. Each user is assigned a $\textbf{unique}$ identifier $a_{i}$. Also, the currency has a security parameter $d$.

User $i$ can directly transfer currency to user $j$ only if $i < j$ and $a_i < a_j$. But that's not enough! Direct currency transfer between users occurs through a chain of transactions involving some number of intermediate users. During each transaction, the number of each subsequent intermediate user (including the last user $j$) must increase, but not by more than $d$. Also, all intermediate users except $i$ and $j$ must have an identifier strictly less than $a_i$.

More formally, user $i$ can directly transfer cryptocurrency to user $j$ if the following conditions are met:
- It is satisfied that $i < j$
- It is satisfied that $a_{i} < a_{j}$
- There exists a sequence of intermediate users $x$ of length $k$ such that:
    - $i = x_1 < x_2 < \ldots < x_{k-1} < x_{k} = j$
    - For all $1 \le t \le k - 1$, it is true that $x_{t + 1} - x_{t} \le d$
    - For all $2 \le t \le k - 1$, it is true that $a_{x_t} < a_{i}$

Burenka asks you, her acquaintance programmer, to understand this system and find out for some pairs of users how to transfer $\texttt{Pether}$ to each other.

You need to answer $q$ queries. In each query, you need to determine whether there is a sequence of direct currency transfers (possibly through intermediate users) that allows transferring $\texttt{Pether}$ from user $u_i$ to user $v_i$. In some queries, it is also necessary to minimize the number of direct currency transfers in the process of sending currency from $u_i$ to $v_i$. Please note that it is not necessary to minimize the number of transactions during each direct transfer.
## 输入格式

The first line contains three integers $n$, $d$, and $g$ $(1 \leq n, d \leq 300\,000, 0 \leq g \leq 12)$ --- the number of users, the security parameter, and the test group number.

The second line contains $n$ integers $a_1,\ a_2,\ \ldots,\ a_n$ $(1 \leq a_{i} \leq n)$ --- user identifiers. It is guaranteed that all numbers $a_i$ are $\textbf{distinct}$.

The third line contains a single integer $q$ $(1 \leq q \leq 300\,000)$ --- the number of queries.

The next $q$ lines contain three integers each $t_{i},\ u_{i},\ v_{i}$ $(t_{i}\in \{1, 2\}, 1 \leq u_{i} < v_{i} \leq n)$, where $u_i$ is the user who should transfer the currency, and $v_i$ is the user who should receive the currency. If $t_i = 1$, then it is necessary to determine whether it is possible to transfer the currency, and if $t_i = 2$, then it is also necessary to minimize the number of direct currency transfers.
## 输出格式

Output $q$ lines, where the $i$-th line should contain the answer to the $i$-th query.

If it is not possible to transfer the currency from user $u_i$ to user $v_i$, then output 0 as the answer to the $i$-th query. Otherwise, if $t_i = 1$, output 1, and if $t_i = 2$, output the minimum number of direct currency transfers required to transfer $\texttt{Pether}$ from $u_i$ to $v_i$.
## 样例

### 样例输入 #1
```
6 1 0
2 1 3 4 5 6
6
2 1 3
2 1 2
1 1 4
2 1 5
2 1 6
1 2 6
```
### 样例输出 #1
```
1
0
1
3
4
1
```
### 样例输入 #2
```
6 2 0
1 2 3 4 5 6
6
2 1 5
2 2 5
2 1 6
2 2 6
2 1 4
2 2 4
```
### 样例输出 #2
```
2
2
3
2
2
1
```
### 样例输入 #3
```
10 2 0
2 1 4 3 5 6 8 7 10 9
10
2 1 5
1 2 5
2 3 5
2 1 9
2 5 8
2 3 9
2 1 8
1 1 2
2 3 8
2 1 9
```
### 样例输出 #3
```
2
1
1
4
2
3
3
0
2
4
```
## 提示

### Note

In the first example, the following direct transfers between users are possible:

![](https://cdn.luogu.com.cn/upload/image_hosting/znmqxem4.png)

In the first query, user with index $1$ can directly transfer $\texttt{Pether}$ to user with index $3$, making 2 transactions through intermediate user 2.

In the second query, a direct transfer between users with indices $1$ and $2$ is not possible, as $a_{1} = 2 > a_{2} = 1$.

In the third query, it is possible to transfer the currency from user $1$ to user $4$ with two direct transfers, first transferring the currency from user $1$ to user $3$, and then from $3$ to $4$. Since $t_3 = 1$, it is only necessary to determine the possibility of transferring the currency, so the answer to the query is 1.

In the fourth query, it is possible to manage with three direct transfers: from $1$ to $3$, from $3$ to $4$, and from $4$ to $5$.

In the second example, the following direct transfers between users are possible:

![](https://cdn.luogu.com.cn/upload/image_hosting/zzagqjxa.png)

In the third example, the following direct transfers between users are possible:

![](https://cdn.luogu.com.cn/upload/image_hosting/uj5b2pnx.png)

### Scoring

The tests for this problem consist of twelve groups. Points for each group are given only if all tests of the group and all tests of the required groups are passed. Please note that passing the example tests is not required for some groups. $\textbf{Offline-evaluation}$ means that the results of testing your solution on this group will only be available after the end of the competition.

| Group | Points | Additional constraints | < | < |Required groups | Comment |
|:-----:|:------:|:----------------------:|:-:|:-:|:---------------:|:-------:|
|       |        | $n$ | $q$ | $v_i, a_n, t_i$ | | |
| 0 | 0 | -- | -- | -- | -- | Examples. |
| 1 | 10 | $n \le 100$ | $q \le 100$ | -- | -- | |
| 2 | 7 | $n \le 1000$ | -- | -- | 1 | |
| 3 | 14 | -- | -- | $a_n = n, v_i = n$ | -- | |
| 4 | 10 | -- | $q = 1$ | $v_i = n$ | -- | |
| 5 | 9 | -- | -- | $v_i = n$ | 3, 4 | |
| 6 | 7 | -- | -- | $t_i=2$ | -- | The answer does not exceed $10$ |
| 7 | 7 | -- | -- | $t_i=2$ | 1, 6 | The answer does not exceed $150$ |
| 8 | 13 | -- | -- | $t_i = 1$ | -- | |
| 9 | 10 | $n \le 50\,000$ | $q \le 50\,000$ | -- | 1 | |
| 10 | 4 | $n \le 100\,000$ | $q \le 100\,000$ | -- | 1, 9 | |
| 11 | 4 | $n \le 200\,000$ | $q \le 200\,000$ | -- | 1, 9, 10 | |
| 12 | 5 | -- | -- | -- | 0--11 | **Offline-evaluation.** |



---

---
title: "[OOI 2023] Gasoline prices / 油价"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13528
tag: ['线段树', '倍增', '二分', '并查集', '2023', '树链剖分', '哈希 hashing', 'Moscow Olympiad']
---
# [OOI 2023] Gasoline prices / 油价
## 题目背景

CF1801E
## 题目描述

伯利兰是一个由 $n$ 个城市组成的庞大国家。伯利兰的公路网络可以被看作是一棵有根树，也就是说全国一共有 $n - 1$ 条道路，并且任意两个城市之间都恰好有一条路径相连，且不会重复经过同一个城市。为了方便表示，每个城市 $i$ 都有一个固定的城市 $p_i$，它表示从城市 $i$ 出发前往城市 $1$ 时，首先要到达的城市。换句话说，如果将树的根设为城市 $1$，那么 $p_i$ 就是城市 $i$ 的父节点。

每个城市都有一个加油站。每个加油站的油价都有一个固定的区间，在这个区间内可以选择任意一个价格。城市 $i$ 的加油站油价可以是 $l_i$ 到 $r_i$ 之间的任意整数（包括两端）。

伯利兰的国王是个顾家的好父亲，他连续 $m$ 年每年都迎来了两位儿子的出生。国王的孩子们从小就参与国家事务，每年年末，他们会检查油价是否公平。自出生起，第 $i$ 年出生的两个孩子分别负责检查从城市 $a_i$ 到城市 $b_i$ 的路径，以及从城市 $c_i$ 到城市 $d_i$ 的路径上的油价。

检查的方式如下：两个孩子分别同时从城市 $a_i$ 和 $c_i$ 出发。第一个孩子沿着从 $a_i$ 到 $b_i$ 的路径前进，第二个孩子则沿着从 $c_i$ 到 $d_i$ 的路径前进。他们会依次检查：起点 $a_i$ 和 $c_i$ 的油价是否相同，然后检查路径上的第二个城市是否油价相同，依此类推，直到终点 $b_i$ 和 $d_i$ 的油价也要一致。保证从 $a_i$ 到 $b_i$ 的路径长度和从 $c_i$ 到 $d_i$ 的路径长度相同。

所有加油站都必须严格遵守法律，因此所有的油价检查都不能出现违规。请你帮助伯利兰的加油站计算，在 $m$ 年内，他们有多少种合法的油价设置方式。换句话说，对于每个 $i$ 从 $1$ 到 $m$，请计算在前 $i$ 年出生的所有王子进行检查后，所有检查都不出现违规，且每个加油站的油价在允许区间内的情况下，总共有多少种油价分配方案。由于答案可能很大，请对 $10^9 + 7$ 取模输出。

## 输入格式

第一行包含一个整数 $n$（$1 \le n \le 200\,000$），表示伯利兰的城市数量。

第二行包含 $n-1$ 个整数 $p_2,\ p_3,\ \ldots,\ p_n$（$1 \le p_i \le n$），其中 $p_i$ 表示从城市 $i$ 前往城市 $1$ 时的下一个城市编号。

接下来的 $n$ 行，每行两个整数 $l_i$ 和 $r_i$（$1 \le l_i \le r_i < 10^9+7$），表示第 $i$ 个城市加油站允许的油价区间。

再下一行包含一个整数 $m$（$1 \le m \le 200\,000$），表示国王有多少年每年出生两位儿子。

接下来的 $m$ 行，每行四个整数 $a_i, b_i, c_i, d_i$（$1 \le a_i, b_i, c_i, d_i \le n$），表示第 $i$ 年出生的两位王子分别要检查的两条路径。保证 $a_i$ 到 $b_i$ 的路径长度等于 $c_i$ 到 $d_i$ 的路径长度。

## 输出格式

输出 $m$ 行，每行一个整数。第 $i$ 行表示在前 $i$ 年出生的所有王子进行检查后，所有检查都不出现违规，且每个加油站油价在允许区间内的情况下，总共有多少种油价分配方案。结果对 $10^9 + 7$ 取模。

## 样例

### 样例输入 #1
```
5
1 1 2 2
2 4
1 3
1 3
2 4
4 4
4
1 1 2 2
1 2 2 1
3 4 4 3
3 4 3 5
```
### 样例输出 #1
```
18
18
4
0
```
### 样例输入 #2
```
8
1 2 3 4 5 8 6
3 7
2 6
3 8
5 10
5 8
2 9
3 8
6 8
4
1 3 7 6
4 1 5 7
1 7 7 1
1 8 2 7
```
### 样例输出 #2
```
720
120
120
1

```
## 提示

### 样例解释

以第一个样例为例：

- 在头两位王子出生后，城市 $1$ 和城市 $2$ 的油价必须相同。可以在允许的区间内为城市 $1$ 和 $2$ 选择相同的油价方式有 $2$ 种。剩下城市 $3$ 和 $4$ 的油价分别有 $3$ 种和 $3$ 种选择。总方案数为 $2 \times 3 \times 3 \times 1 = 18$。
- 第二对王子检查的是 $1-2$ 和 $2-1$，这要求城市 $1$ 和 $2$ 的油价一致，这个条件已经满足，因此方案数不变。
- 第三对王子检查的是 $3-1-2-4$ 和 $4-2-1-3$，这要求城市 $3$ 和 $4$ 的油价相同，城市 $1$ 和 $2$ 的油价也要相同。城市 $1$ 和 $2$ 已经一致，而城市 $3$ 和 $4$ 可以有 $2$ 种相同的油价选择。总方案数为 $2 \times 2 \times 1 = 6$。
- 第四对王子检查的是 $3-1-2-4$ 和 $3-1-2-5$，这要求城市 $4$ 和 $5$ 的油价一致，而城市 $3$ 和 $4$ 已经一致，因此 $3$、$4$、$5$ 三个城市的油价都要一致。城市 $3$ 的油价不能超过 $3$，城市 $5$ 的油价不能低于 $4$，因此不存在满足条件的方案，答案为 $0$。

### 评分说明

本题的数据分为 8 组。只有通过某一组全部测试点，且通过部分之前组全部测试点，才能获得该组分数。有些分组不要求通过样例测试点。“离线评测”表示该组的测试结果只会在比赛结束后公布。

| 组别 | 分值 | $n$ | $m$ | 必须通过的组 | 备注 |
|:----:|:----:|:---:|:---:|:------------:|:----:|
| 0    | 0    | --  | --  | --           | 样例测试点 |
| 1    | 12   | $n \le 300$ | $m \le 300$ | 0 |  |
| 2    | 10   | $n \le 3000$ | $m \le 3000$ | -- | $p_i = i - 1$ |
| 3    | 9    | $n \le 3000$ | $m \le 3000$ | 0, 1, 2 |  |
| 4    | 16   | --  | --  | 0 -- 3       | 所有检查路径的总长度不超过 $10^8$ |
| 5    | 10   | $n \le 100\,000$ | $m \le 100\,000$ | 2 | $p_i = i - 1$ |
| 6    | 12   | --  | --  | 2, 5         | $p_i = i - 1$ |
| 7    | 13   | $n \le 100\,000$ | $m \le 100\,000$ | 0 -- 3, 5 |  |
| 8    | 18   | --  | --  | 0 -- 7       | **离线评测** |


---

---
title: "[WC2013] 平面图"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4073
tag: ['图论', '计算几何', '2013', '倍增', '平衡树', '枚举', '生成树', 'WC']
---
# [WC2013] 平面图
## 题目描述

在一个平面中有 $n$ 个顶点和 $m$ 条直线段，第 $i$ 个顶点的坐标为 $(x_i, y_i)$， 第 $j$ 条直线段连接顶点 $u_j$ 和顶点 $v_j$，权值为 $h_j$， 除顶点 $u_j$ 和 $v_j$ 外直线段 $j$ 不经过其他的顶点。任意两条直线段如果存在公共点，则该公共点一定是一个顶点，此时这两条直线段都会连接这个顶点。对于任意的两个顶点 $x$ 和 $y$，总是可以找到一顶点序列 $a_1,a_2,\cdots,a_k$ 使得 $a_1=x$，$a_k=y$ 且对于任意 $1\le i< k$ 满足 $a_i$ 和 $a_{i+1}$ 被一条直线段直接连接。

这 $m$ 条直线段将整个平面分成了若干个区域，其中只有一个区域是无穷大的，其余均是有界的，我们称无穷大的区域为禁区。

现在给出 $q$ 次询问，每次给定平面中的任意两个不是顶点且分别不在任意一条直线段上的点 $A$ 和 $B$，请画一条曲线连接 $A$ 和 $B$，要求曲线不能经过禁区以及任何顶点，并使得穿过的直线段中权值最大的尽可能小。你需要对每次询问回答这个值最小为多少。

## 输入格式

第一行有两个正整数 $n,m$，分别表示顶点数和直线段数。

接下来 $n$ 行，每行两个整数，这部分中第 $i$ 行（总第 $i+1$ 行）的两个整数 $x_i,y_i$ 为顶点 $i$ 的坐标。

接下来 $m$ 行，每行三个正整数 $u,v,h$，表示有一条直线段连接顶点 $u$ 和顶点 $v$，权值为 $h$。其中 $u\neq v$。

接下来的一行，有一个正整数 $q$，表示询问数量。

接下来 $q$ 行，每行四个实数 $A_x,A_y,B_x,B_y$， 表示一组两个点的坐标分别为 $(A_x, A_y)$ 和 $(B_x, B_y)$ 的询问。

## 输出格式

输出 $q$ 行，每行一个正整数，依次表示每个询问的答案。特别的，若不需要跨过任何一条边即可到达，请输出 $0$；若不存在合法的曲线，请输出 $-1$。

## 样例

### 样例输入 #1
```
9 12
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
1 2 10
2 3 10
3 6 10
6 9 10
9 8 10
8 7 10
7 4 10
4 1 10
2 5 3
5 8 2
5 6 4
4 5 1
3
1.5 1.5 2.5 2.5
1.5 2.5 2.5 1.5
0.5 0.5 1.5 1.5
```
### 样例输出 #1
```
2
3
-1
```
## 提示

【样例说明】

![QQ20180112214336.png](https://cdn.luogu.com.cn/upload/image_hosting/228djzaq.png)

【数据规模与约定】

本题共设有 $10$ 个测试点，每个测试点的规模与特征如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/2l8u3hkb.png)

对于全部数据，均满足 $5$ ≤ $n$, $m$, $q$ ≤ $100,000$，所有直线段的权值不会超过 $10^9$。所有询问坐标均为不超过 $10^7$ 的实数，且保证是 $0.5$ 的整数倍。



---

---
title: "[八省联考 2018] 制胡窜"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4384
tag: ['字符串', '2018', '线段树', '倍增', '各省省选', '后缀自动机 SAM']
---
# [八省联考 2018] 制胡窜
## 题目描述

对于一个字符串 $s$，我们定义 $|s|$ 表示 $s$ 的长度。

接着，我们定义 $s_i$ 表示 $s$ 中第 $i$ 个字符，$s_{l,r}$ 表示由 $s$ 中从左往右数，第 $l$ 个字符到第 $r$ 个字符依次连接形成的字符串。特别的，如果 $l \gt r$，或者 $l \notin [1, |s|]$，或者 $r \notin [1, |s|]$，我们可以认为 $s_{l,r}$ 为空串。

给定一个长度为 $n$ 的仅由数字构成的字符串 $s$，现在有 $q$ 次询问，第 $k$ 次询问会给出 $s$ 的一个子串 $s_{l,r}$，请你求出有多少对 $(i, j)$，满足 $1 \leq i \lt j \leq n$，$i + 1 < j$，且 $s_{l,r}$ 出现在 $s_{1,i}$ 中或 $s_{i+1,j-1}$中或 $s_{j,n}$ 中。
## 输入格式

输入的第一行是两个整数，分别表示字符串长度 $n$ 和询问次数 $q$。

第二行有一个长度为 $n$ 的只包含数字字符的字符串，表示 $s$。

接下来 $q$ 行，每行两个正整数 $l$ 和 $r$，表示此次询问的子串是 $s_{l,r}$。
## 输出格式

对于每个询问，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5 2
00100
1 2
1 3

```
### 样例输出 #1
```
5
1
```
## 提示

|    测试点    |     $n$     |     $q$     |               其它约定                |
| :----------: | :-------: | :-------: | :-----------------------------------: |
|     $1$      |   $=50$   |  $=100$   |                  无                   |
|  $2 \sim 3$  |  $=300$   |  $=300$   |                  无                   |
|  $4 \sim 5$  |  $=2000$  |  $=3000$  |                  无                   |
|  $6 \sim 9$  | $=100000$ | $=100000$ | $\sum \lvert s_{l,r} \rvert \le 10^6$ |
| $10 \sim 12$ | $=30000$  | $=50000$  |                  无                   |
|     $13$     | $=100000$ | $=100000$ |            $s$ 中只有 $0$             |
| $14 \sim 20$ | $=100000$ | $=300000$ |                  无                   |


对于所有测试数据，$1 \le n \le 10^5$，$1 \le q \le 3 \times 10^5$，$1 \le l \le r \le n$，$s$ 中只有数字字符。


---

---
title: "多项式反三角函数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5265
tag: ['倍增', 'O2优化', '构造', '快速数论变换 NTT']
---
# 多项式反三角函数
## 题目描述

给定一个 $n-1$ 次多项式 $A(x)$，求一个 $\bmod{\:x^n}$ 下的多项式 $F(x)$，满足 $F(x)\equiv\text{asin}\:A(x)$ 或 $F(x)\equiv\text{atan}\:A(x)$。

所有运算在 $\bmod\ 998244353$ 意义下进行。
## 输入格式

第一行 **两个** 整数 $n,type$，若 $type=0$ 代表求 $\text{asin}$，若 $type=1$ 代表求 $\text{atan}$；

第二行 $n$ 个整数，依次表示多项式的系数 $a_0,a_1,\cdots,a_{n-1}$。

保证 $a_0=0$。
## 输出格式

输出一行 $n$ 个整数，表示答案多项式中的系数 $f_0,f_1,\cdots,f_{n-1}$。
## 样例

### 样例输入 #1
```
8 0
0 4 2 6 1 5 3 7
```
### 样例输出 #1
```
0 4 2 665496252 17 399297879 332748370 570426983
```
### 样例输入 #2
```
8 1
0 4 2 6 1 5 3 7
```
### 样例输出 #2
```
0 4 2 665496220 998244322 399297839 332748518 570424795
```
## 提示

对于 $100\%$ 的数据：$n\leq10^5$，$a_i\in[0,998244352]\cap\mathbb{Z}$。

前 $5$ 个点 $type=0$，后 $5$ 个点 $type=1$。


---

---
title: "【模板】快速阶乘算法"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5282
tag: ['数学', '倍增', 'O2优化', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 【模板】快速阶乘算法
## 题目背景

有一天，NaCly_Fish 无意间看到一种高效求阶乘模大质数的算法，但是她太菜，并不会写。  
于是她就暴力造了数据，请您帮忙写出 std 吧。  

什么，您问为什么不保证模数可以 NTT？  
那样的话就可能被打表水过，或者答案就爆 int 了。

反正您是神仙，肯定能秒掉这题。
## 题目描述

给你正整数 $n$，和一个质数 $p$，你需要求出：  
$$ n! \text{ mod } p$$  
有 $T$ 组数据。
## 输入格式

第一行一个正整数 $T$，表示数据组数。  
接下来 $T$  行，每行两个正整数 $n,p$，意义如题目描述。
## 输出格式

输出 $T$ 行，表示每组数据的答案。
## 样例

### 样例输入 #1
```
4
16777216 998244353
72267859 998244353
2333333 19260817
1919810 2147481811
```
### 样例输出 #1
```
789885751
569626621
16351109
1416439247
```
## 提示

### 数据范围：  

对于 $10\%$ 的数据：$p = 998244353$   
对于另外 $10\%$ 的数据：$p = 1004535809$   
对于 $100\%$ 的数据：$1\le n < p \le 2^{31}-1$，$1 \le T \le 5$    
保证 $p$ 为质数。

【提示】   
请确保你的算法时间复杂度不高于 $\Theta(\sqrt n \log n)$，时限为 std 的十倍以上。


---

---
title: "A/B Problem（高精度除法）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5432
tag: ['数学', '倍增', 'O2优化', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# A/B Problem（高精度除法）
## 题目描述

给你两个正整数 $a,b$，求 $\lfloor a/b \rfloor$。  
为了卡掉一些乱搞做法，你需要对答案进行如下处理：  
设答案为 $r$，构造一个多项式 $F(x)$：

$$ F(x) = \sum\limits_{i=0}^{\lfloor \lg r \rfloor} (\lfloor 10^{-i}r \rfloor \bmod 10) \cdot x^i$$

简单地说，就是从 $r$ 的低位到高位，每一位对应 $F(x)$ 一项的系数。

设 $F(x)$ 的最高非零次数为 $n$，你需要求出一个 $n$ 次多项式 $G(x)$，使得：  
$$ F(x) \cdot G(x) \equiv 1 \pmod{x^{n+1}}$$   
将 $G(x)$ 的系数对 $998244353$ 取模，然后升幂输出 $G(x)$ 的系数即可。

保证满足条件的 $G(x)$ 存在。
## 输入格式

两行，每行一个正整数，分别为 $a$ 和 $b$。
## 输出格式

输出一行 $n+1$ 个整数，为 $G(x)$ 的系数
## 样例

### 样例输入 #1
```
19260817
114514
```
### 样例输出 #1
```
873463809 93585408 943652865 
```
## 提示

**【样例解释】**

$\left\lfloor \dfrac{19260817}{114514} \right\rfloor = 168$。

由此构造出的多项式 $F(x)=x^2+6x+8$  
求出来对应的 $G(x)$ 就是 $943652865x^2 + 93585408x +  873463809$。

**【数据范围】**

对于 $100 \%$ 的数据，$1\le b \le a \le 10^{200000}$。


---

---
title: "调和级数求和"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5702
tag: ['数学', '倍增', 'O2优化', '快速傅里叶变换 FFT']
---
# 调和级数求和
## 题目描述

给定 $n,p$，求：

$$\sum_{i=1}^n \frac 1i $$

对 $p$ 取模的值。

如果你不知道怎么对分数取模，可以看[这题](https://www.luogu.com.cn/problem/P2613)。  
保证答案在模 $p$ 意义下存在。

为了方便你的计算，这里将给出 $p$ 的最小原根 $g$。
## 输入格式

输入第一行一个正整数 $T$，表示数据组数。  
接下来 $T$ 行，每行三个正整数 $n,p,g$。
## 输出格式

输出 $T$ 行，每行一个整数表示答案。
## 样例

### 样例输入 #1
```
5
998007 998244353 3
19260817 998244353 3
274829164 998244353 3
792846153 998244353 3
1924762 899678209 7
```
### 样例输出 #1
```
429767635
632288905
445668022
128133635
3097708
```
## 提示

【数据范围】  
对于 $30\%$ 的数据，$1\le n \le 10^6$；  
对于 $100\%$ 的数据，$1 \le n < p < 2^{30}$，$1\le T \le 20$。  
保证 $p$ 为质数，且 $p-1$ 可以被 $2^{19}$ 整除。

注：时限为 std 的三倍，如果过不去请确认时间复杂度正确，并优化常数。


---

---
title: "「ACOI2020」修学旅行"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6043
tag: ['数学', '2020', '倍增', 'O2优化', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 「ACOI2020」修学旅行
## 题目背景

![T5](https://s2.ax1x.com/2020/01/12/loS0Wq.md.png)

第一学期开学没多久，E 班的各位就要去修学旅行了！
## 题目描述

现在，六个人 赤羽 業，杉野 友人，奧田 愛美，茅野 楓，神崎 有希子，潮田 渚 为一组，他们将在京都进行一次暗杀旅行。他们的目标仍然是狙击杀老师。政府同时派来了职业狙击手 赤红之眼。但是完成任务的同时，他们想让快乐度尽量的高。

聪明的神崎 有希子（Kanzaki Yukiko）终于求出了快乐度的表达式，令人感到震惊的是，快乐度竟然和旅行景点个数和暗杀杀老师次数有关！

假设他们经过了 $n$ 个景点，暗杀了 $m$ 次杀老师，且定义：

$$
\Gamma(a,b)=\left\{
    \begin{aligned}
    & 1,a>b&\\
    &  \prod_{i=a}^b i,a \le b&\\
    \end{aligned}
    \right.
$$

那么快乐度为：

$$
\sum_{i=0}^m \lgroup \frac{\sqrt{\sum_{j=0}^i (C_i^j)^2C_{n+2i-j}^{2i}}}{\Gamma(n+1,n+i)} \times \Gamma(n-i+1,n) \rgroup 
$$

**我们保证** $\frac{\sqrt{\sum_{j=0}^i (C_i^j)^2C_{n+2i-j}^{2i}}}{\Gamma(n+1,n+i)} \times \Gamma(n-i+1,n)$ **是一个整数。**

现在他们有 $T$ 个问题想要问你，如果他们经过了 $n$ 个景点并且暗杀 $m$ 次杀老师，能否告诉他们快乐度呢？

**由于答案可能太大，请将答案对 $998244353$ 取模。**
## 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示数据组数。

对于每组数据：

只有一行两个整数 $n$ 和 $m$。
## 输出格式

对于每组数据，只有一行一个整数，表示他们经过了 $n$ 个景点，暗杀了 $m$ 次杀老师的快乐度对 $998244353$ 取模后的值。

#### 样例有更新
## 样例

### 样例输入 #1
```
5
5 3
7 3
9 6
100 50
44 22


```
### 样例输出 #1
```
26
64
466
41441083
461961723

```
## 提示

#### 数据范围

**本题采用捆绑测试**。

- Subtask 1（10 points）：$T \leq 10$，$n,m \leq 10$。     
- Subtask 2（20 points）：$T \leq 100$，$n,m \leq 5 \times 10^4$。      
- Subtask 3（30 points）：$T \leq 50$，$n,m \leq 9 \times 10^8$。  
- Subtask 4（40 points）：数据无特殊限制。  

对于 $100\%$ 的数据，$m \leq n$，$1 \leq T \le 10^2$，$1 \leq n,m \leq 9 \times 10^8$。

---
#### 提示

**第三个子任务中的测试点时限 2S，第四个子任务中的测试点时限 5S。**


---

---
title: "【模板】整式递推"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6115
tag: ['数学', '倍增', 'O2优化', '矩阵加速', '矩阵乘法', '快速傅里叶变换 FFT']
---
# 【模板】整式递推
## 题目背景

话说上次菜菜的 NaCly\_Fish 想教后辈做常系数线性齐次递推，奈何智商不够，见识短浅，被机房同学轮番吊打。

之后她又听说了整式递推这种东西，便去请教中国队长 $\mathsf E \color{red}\mathsf{ntropyIncreaser}$。然而 $\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 觉得这个东西太简单了，只回应了一句：“你不看候选队论文么？”

NaCly\_Fish 终于找来论文，但她完全看不懂。于是她只能找又强又热心的你来教她这个问题。
## 题目描述

对于无限数列 $a$，已知 $\forall n \ge m$ 都满足
$$\sum_{k=0}^m a_{n-k} P_k(n) = 0$$
其中 $P_k$ 为不超过 $d$ 次的多项式。  
给定所有 $P_k$ 的系数，和 $\{ a_i \}_{i=0}^{m-1} $，求 $a_n$。

由于答案可能很大，所以要对 $998244353$ 取模。
## 输入格式

第一行三个正整数 $n,m,d$。  
第二行 $m$ 个非负整数，表示 $\{ a_i \}_{i=0}^{m-1} $。  
接下来 $m+1$ 行，每行 $d+1$ 个非负整数；第 $k+3$ 行由低到高地给出 $P_k$ 的系数。 
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
5 2 1
1 0
998244352 0
998244352 1
998244352 1
```
### 样例输出 #1
```
44
```
### 样例输入 #2
```
233 2 3
1 0
998244352 0 0 0
0 998244349 4 0
0 8 998244337 8
```
### 样例输出 #2
```
193416411
```
### 样例输入 #3
```
114514 7 7
1 9 8 2 6 4 7
9 1 8 2 7 6 5 3
2 8 4 6 2 9 4 5
1 9 2 6 0 8 1 7
1 9 1 9 8 1 0 7
1 1 4 5 1 4 4 4
4 4 4 4 4 4 4 4
9 9 8 2 4 4 3 5
1 9 8 6 0 6 0 4
```
### 样例输出 #3
```
565704112
```
## 提示

【样例一解释】  
这里的递推式就是 $a_n \equiv (n-1)(a_{n-1}+a_{n-2}) \pmod{998244353}$，容易计算得 $a_5 \equiv 44 \pmod{998244353}$。

【数据范围】  
对于 $30\%$ 的数据，$1\le n \le 10^6$。  
对于 $100\%$ 的数据，$1\le m,d \le 7$，$1 \le n \le 6 \times 10^8$。

所有输入不超过 $6 \times 10^8$。  
$\forall x \in [m,n] \cap \mathbb Z \text{ s.t. } P_0(x) \not \equiv 0 \pmod{998244353}$。

欢迎加入 $\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 粉丝群：747262201


---

---
title: "鬼故事 加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6358
tag: ['数学', '递推', '倍增', 'O2优化', '快速傅里叶变换 FFT']
---
# 鬼故事 加强版
## 题目描述

[原题链接](https://www.luogu.com.cn/problem/P5126)

给定 $l,r,k$，求：
$$\sum_{i=l}^r \prod_{j=i}^{i+k-1}f_j$$
其中 $f_0= 0$，$f_1 = 1$，$f_n = f_{n-1}+f_{n-2} \ (n \geq 2)$。  
作为良心（迫真）出题人，你只需要将答案对 $998244353$ 取模。


## 输入格式

输入一行三个正整数 $l,r,k$。
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
233 888 251
```
### 样例输出 #1
```
60539267
```
### 样例输入 #2
```
11451 45149 8100
```
### 样例输出 #2
```
728539702
```
### 样例输入 #3
```
114514 233333 101010
```
### 样例输出 #3
```
830578369
```
### 样例输入 #4
```
198245 285628 157293
```
### 样例输出 #4
```
121742791
```
## 提示

【数据范围】     
对于 $30\%$ 的数据，$1\le k \le 1000$；  
对于 $70\%$ 的数据，$1\le k \le 10^5$；  
对于 $100\%$ 的数据，$1\le k \le 5 \times 10^5$，$1\le l \le r \le 10^{18}$。

**请注意常数优化。**

由于 $l,r$ 开到高精度范围也没什么意义，因此这里就改为 $10^{18}$ 了。


---

---
title: "[IOI 2020] 植物比较"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6829
tag: ['2020', '线段树', '倍增', 'IOI', '交互题']
---
# [IOI 2020] 植物比较
## 题目背景

**这是一道交互题**。

本题仅支持 C++ 系列语言，提交时不需要包含 `plant.h` 头文件。
## 题目描述

植物学家 Hazel 参观过新加坡植物园的一个特别展览。在这次展览中，有 $n$ 棵 **高度互不相同** 的植物，它们排成了一个圆。这些植物按顺时针方向从 $0$ 到 $n-1$ 编号，植物 $n-1 $ 与植物 $0$ 是相邻的。

对于每棵植物 $i\ (0 \le i \le n-1$)，Hazel 将它与顺时针方向的后 $k-1$ 棵植物进行比较，记录下数值 $r[i]$ 以表示这 $k-1$ 棵植物中有多少棵的高度大于植物 $i$。因此，每个 $r[i]$ 的数值是由某段连续 $k$ 棵植物的相对高度决定的。

例如，假设 $n=5$，$k=3$，$i=3$。植物 $3$ 顺时针方向的后 $k-1=2$ 棵植物是植物 $4$ 和植物 $0$。如果植物 $4$ 比植物 $3$ 高，且植物 $0$ 比植物 $3$ 矮，那么 Hazel 将会记录 $r[3]=1$。

你可以假设 Hazel 记录的数值 $r[i]$ 都是正确的。也就是说，这些植物至少存在一组互不相同的高度符合 Hazel 所记录的数值。

本题要求你比较 $q$ 对植物的高度。由于你没有机会参观这次展览，你仅有的信息来源是 Hazel 的笔记本，其中记录了 $k$ 和序列 $r[0],\ldots, r[n-1]$ 的值。

对于每对需要比较的植物 $x$ 和 $y$（$x$ 和 $y$ 不同），判定它们符合以下哪种情况：

- 植物 $x$ 一定比植物 $y$ 高：对于任意一组符合数组 $r$ 且互不相同的高度 $h[0],\ldots h[n-1]$，都有 $h[x] > h[y]$。
- 植物 $x$ 一定比植物 $y$ 矮：对于任意一组符合数组 $r$ 且互不相同的高度 $h[0],\ldots h[n-1]$，都有 $h[x]<h[y]$。
- 该比较没有定论：以上两种情况都不成立。

#### 实现细节

要求你实现以下函数：
```cpp
void init(int k, std::vector<int> r)
```
- $k$：决定每个 $r[i]$ 数值的连续植物的棵数。
- $r$：一个大小为 $n$ 的数组，其中 $r[i]$ 是植物 $i$ 顺时针方向的后 $k-1$ 棵植物中比它高的棵数。
- 该函数恰好被调用一次，且在对 `compare_plants` 的任何调用前。
```cpp
int compare_plants(int x, int y)
```
- $x,y$ ：待比较的植物的编号。
- 该函数应该返回：
	- $1$，如果植物 $x$ 一定比植物 $y$ 高，
	- $-1$，如果植物 $x$ 一定比植物 $y$ 矮，
	- $0$，如果该比较没有定论。
- 该函数恰好被调用 $q$ 次。
## 提示

#### 样例说明

#### 例 1

考虑以下调用：
```cpp
init(3, [0, 1, 1, 2])
```
假设评测程序调用了 `compare_plants(0, 2)`。由 $r[0]=0$ 可以推断植物 $2$ 不比植物 $0$ 高，因此该调用应该返回 $1$。

假设评测程序接下来调用了 `compare_plants(1, 2)`。由于对每组符合以上条件的植物高度，都有植物 $1$ 比物 $2$ 矮，因此该调用应该返回 $-1$。

#### 例 2

考虑以下调用：
```cpp
init(2, [0, 1, 0, 1])
```
假设评测程序调用了 `compare_plants(0, 3)`。由 $r[3]=1$ 可以推断植物 $0$ 比植物 $3$ 高，因此该调用应该返回 $1$。

假设评测程序接下来调用了 `compare_plants(1, 3)`。两组高度 $[3,1,4,2]$ 和 $[3,2,4,1]$ 都符合 Hazel 的观测记录，由于在第一种情况中植物 $1$ 比植物 $3$ 矮，而在第二种情况中它比植物 $3$ 高，因此该调用应该返回 $0$。

#### 约束条件

- $2\le k\le n\le 200\ 000$
- $1\le q\le 200\ 000$
- $0 \le r[i]\le k-1$（对所有 $0 \le i \le n-1$）
- $0\le x<y\le n-1$
- 存在一组或多组 **互不相同的高度** 符合数组 $r$ 记录的情况

#### 子任务

1. （5 分）$k=2$
2. （14 分）$n \le 5000,2 \cdot k > n$
3. （13 分）$2 \cdot k > n$
4. （17 分）每次 `compare_plants` 调用的正确答案是 $1$ 或 $-1$
5. （11 分）$n\le 300, q\le \frac{n\cdot (n-1)}{2}$
6. （15 分）每次调用 `compare_plants` 时有 $x=0$
7. （25 分）没有附加约束条件

#### 评测程序示例

评测程序示例以如下格式读取输⼊数据：

第 $1$ 行：$n\ k\ q$     
第 $2$ 行：$r[0]\ r[1]\ \cdots\ r[n-1]$        
第 $3+i\ (0\le i\le q-1)$ 行：$x\ y$，表⽰第 $i$ 次调用 `compare_plants` 时的参数

评测程序示例以如下格式打印你的答案：

第 $1+i\ (0\le i\le q-1)$ 行：第 $i$ 次调用 `compare_plants` 的返回值


---

---
title: "「C.E.L.U-03」布尔"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7843
tag: ['倍增', 'O2优化', '2-SAT', '动态树 LCT', '整体二分']
---
# 「C.E.L.U-03」布尔
## 题目描述

给你 $n$ 个布尔变量和 $m$ 个限制，设 $s_i$ 为 $i$ 的取值。第 $i$ 个限制形如 $s_{u_i}$ 为 $x_i$ 则 $s_{v_i}$ 必须为 $y_i$，同时如果 $s_{v_i}$ 为 $y_i$ 则 $s_{u_i}$ 必须取 $x_i$。  
一共 $q$ 次询问，每次询问给出一个区间 $l,r$。求最少把 $l,r$ 划分成多少段连续的区间，使得每段里的限制都可以得到一组合法解。如果无论如何都无法得到合法解，输出 `-1`。
## 输入格式

第一行三个数，$n,m,q$。  
接下来 $m$ 行每行四个数，代表 $u_i,x_i,v_i,y_i$。  
接下来 $q$ 行每行两个数，代表 $l_i,r_i$。
## 输出格式

对于每个询问输出一个数作为答案，如果无法得到答案输出 `-1`。
## 样例

### 样例输入 #1
```
3 4 2
1 0 2 0
1 1 3 0
3 0 2 0
1 1 2 1
1 3
3 4
```
### 样例输出 #1
```
2
1
```
### 样例输入 #2
```
4 5 3
1 1 2 1
2 0 3 0
4 1 1 0
2 1 4 0
4 0 3 0
1 4
2 5
3 5
```
### 样例输出 #2
```
1
2
1
```
## 提示

**样例解释一**   
对于第一个询问，可以分成 $[1,2]$ 和 $3$ 两段。  
对于第二个询问，分成 $[3,4]$  一段。  

**样例解释二**   
对于第一个询问，分成 $[1,4]$  一段。  
对于第二个询问，可以分成 $[2,3]$ 和 $[4,5]$ 两段。  
对于第三个询问，分成 $[3,5]$  一段。  

| 数据编号| $n\leq$ | $m\leq$| $q\leq$|
|:---:|:---:|:---:|:---:|
|$1$|$30$|$100$|$300$|
|$2\sim 4$|$300$|$10^3$|$10^3$|
|$5\sim 7$|$10^4$|$5\times10^4$|$10^6$|  
|$8\sim 10$|$10^5$|$6\times10^5$|$10^6$|   

对于 $100\%$ 的数据，$1\le n\le10^5,1\le m\le6\times10^5,1\le q\le10^6,1\le u,v\le n,1\le l\le r\le m,x,y\in \{0,1\}$


---

---
title: "[IOI 2021] 地牢游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8522
tag: ['倍增', '2021', 'IOI', '交互题']
---
# [IOI 2021] 地牢游戏
## 题目背景

**滥用本题评测将被封号**

**由于技术限制，请不要使用 C++ 14 (GCC 9) 提交本题。**

这是一道交互题，你只需要实现代码中要求的函数。

你的代码不需要引用任何额外的头文件，也不需要实现 `main` 函数。
## 题目描述

Robert 正在设计一款新的电脑游戏。游戏中有一位英雄、$n$ 个敌人和 $n + 1$ 个地牢。敌人从 $0$ 到 $n - 1$ 编号，地牢从 $0$ 到 $n$ 编号。敌人 $i$（$0 \le i \le n - 1$）处在地牢 $i$，其能力值为 $s[i]$。地牢 $n$ 里没有敌人。

英雄一开始进入地牢 $x$，初始能力值为 $z$。每次英雄进入地牢 $i$（$0 \le i \le n - 1$）时，都需要面对敌人 $i$，且会发生以下情况中的一种：

如果英雄的能力值大于等于敌人 $i$ 的能力值 $s[i]$，那么英雄会胜出。这使得英雄的能力值增加 $s[i]$（$s[i] \ge 1$）。这种情况下，下一步英雄将会进入地牢 $w[i]$（$w[i] > i$）。

否则英雄会战败，这使得英雄的能力值增加 $p[i]$（$p[i] \ge 1$）。在这种情况下，下一步英雄将会进入地牢 $l[i]$。

注意 $p[i]$ 可能会小于、等于、大于 $s[i]$，$l[i]$ 可能会小于、等于、大于 $i$。无论对战结果如何，敌人 $i$ 始终处在地牢 $i$，且能力值为 $s[i]$。

当英雄进入地牢 $n$ 的时候，游戏结束。可以看出无论英雄的起始地牢和初始能力值如何，游戏一定会在有限次对战之后结束。

Robert 希望你通过 $q$ 次模拟来对游戏进行测试。对于每次模拟，Robert 输入英雄的起始地牢 $x$ 和初始能力值 $z$。你需要做的是对于每次模拟给出游戏结束时英雄的能力值。
## 输入格式

你要实现以下函数：
```cpp
void init(int n, int[] s, int[] p, int[] w, int[] l)
```
- $n$：敌人的数量。
$s$、$p$、$w$、$l$：长度为 $n$ 的序列。对于每一个 $i$（$0 \le i \le n - 1$）：
  + $s[i]$ 是敌人 $i$ 的能力值，也是击败敌人 $i$ 后英雄增加的能力值。
  + $p[i]$ 是英雄被敌人 $i$ 击败后增加的能力值。
  + $w[i]$ 是英雄击败敌人 $i$ 后进入的下一个地牢的编号。
  + $l[i]$ 是英雄被敌人 $i$ 击败后进入的下一个地牢的编号。
- 恰好调用此函数一次，且发生在任何对如下的 simulate 函数的调用之前。
```cpp
int64 simulate(int x, int z)
```
- $x$：英雄的起始地牢编号。
- $z$：英雄的初始能力值。
- 假设英雄的起始地牢编号为 $x$，初始能力值为 $z$，函数的返回值是相应情况下游戏结束时英雄的能力值。
- 恰好调用此函数 $q$ 次。
## 样例

### 样例输入 #1
```
3 2
2 6 9
3 1 2
2 2 3
1 0 1
0 1
2 3
```
### 样例输出 #1
```
24
25
```
## 提示

对于所有数据：

- $1 \le n \le 400 \, 000$
- $1 \le q \le 50 \, 000$
- $1 \le s[i], p[i] \le {10}^7$（对于所有的 $0 \le i \le n - 1$）
- $0 \le l[i], w[i] \le n$（对于所有的 $0 \le i \le n - 1$）
- $w[i] > i$（对于所有的 $0 \le i \le n - 1$）
- $0 \le x \le n - 1$
- $1 \le z \le {10}^7$

子任务	|分值|特殊限制
:-:|:-:|:-:
$0$|$0$|样例
$1$|	$11$|	$n \le 50 \, 000$，$q \le 100$，$s[i], p[i] \le 10 \, 000$（对于所有的 $0 \le i \le n - 1$）
$2$|	$26$|	$s[i] = p[i]$（对于所有的 $0 \le i \le n - 1$）
$3$|	$13$|	$n \le 50 \, 000$，所有的敌人拥有相同的能力值，即 $s[i] = s[j]$，对于所有的 $0 \le i, j \le n - 1$
$4$|	$12$|	$n \le 50 \, 000$，所有的 $s[i]$ 至多有 $5$ 种不同的数值
$5$|	$27$|	$n \le 50 \, 000$
$6$|	$11$|	没有额外的约束条件


---

