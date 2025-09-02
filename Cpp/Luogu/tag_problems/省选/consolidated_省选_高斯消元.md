---
title: "[PA 2019 Final] 数图 / Grafy"
layout: "post"
diff: 省选/NOI-
pid: P11817
tag: ['递推', '2019', '组合数学', '容斥原理', '生成函数', '高斯消元', 'PA（波兰）']
---
# [PA 2019 Final] 数图 / Grafy
## 题目背景

译自 PA 2019 Final。$\texttt{5s,256M}$。


本题数据为自造。

std: joke3579，validator & generator: Starrykiller。

加强版：P11821。**请勿提交 OEIS 题解。**
## 题目描述

求出 $n$ 个节点的满足以下条件的**有标号有向简单图**的数量：

- $\forall 1\le i\le n$，$\operatorname{deg_{out}}(i)=\operatorname{deg_{in}}(i)=2$。

这里，$\operatorname{deg_{out}}(u)$ 指节点 $u$ 的出度，$\operatorname{deg_{in}}(u)$ 指节点 $u$ 的入度。

你只需要输出答案对给定大素数 $p$ 取模后的结果。


注意我们是对**有标号**的「有向简单图」计数。也就是说，这张图中无重边自环。注意 $u\to v$ 和 $v\to u$ 同时出现是允许的。



## 输入格式

一行两个正整数 $n,p$。
## 输出格式

一行一个非负整数，表示答案。
## 样例

### 样例输入 #1
```
4 1000000007
```
### 样例输出 #1
```
9
```
## 提示

- $3\le n\le 500$；
- $10^8+7\le p\le 10^9+7$，$p$ 为素数。




---

---
title: "[USTCPC 2025] Algorithm Duel"
layout: "post"
diff: 省选/NOI-
pid: P12044
tag: ['2025', 'Special Judge', '线性代数', '高斯消元', '线性基', '构造', '高校校赛', 'bitset']
---
# [USTCPC 2025] Algorithm Duel
## 题目背景

考虑到评测机性能差异，改为 1s 时限。USTCPC 时限为 3s。
## 题目描述

Algorithm Duel （在线算法题单挑）是大家非常喜欢的活动之一。而这样的团建活动称为  Algorithm Duel 团建活动（以下简称**团建活动**）。

社团群内共有 $n$ 位群友。克露丝卡尔酱从题库中挑选了 $m=3n-3$ 道题目，**每位群友都有至少其中的一些题没有做过**。①

一场**标准的团建活动**定义如下：对于 $m$ 道题目中的任意一道题目，有偶数位群友没有做过这道题目，这样他们能两两配对举行 Algorithm Duel。

克露丝卡尔酱很遗憾地发现无论从 $n$ 位群友挑选任何非空子集，都不能进行一场**标准的团建活动**。②

但是，她还是非常想举办一场 Algorithm Duel 团建活动，她作为活动负责人只能亲自加入该场活动。为了尽可能保证活动的公正性，她可以任意选择 $n\sim m-n+1$ 道题目给一位群友送分（即这些题目可以有奇数位位群友没有做过这道题目）。这样的活动称为**非标准的团建活动**。

好了，现在请帮助她决定应该邀请哪些群友参加这场活动能成为一场**非标准的团建活动**吧？应该能有解的，不是吗？
## 输入格式

第一行一个整数 $n(2\le n\le 1000)$。$m=3n-3$。

接下来 $n$ 行长度为 $m$ 的 01 串 $s$。**若 $s_j=1$ 则表示编号为 $i$ 的群友没有做过题目 $j$；$s_j=0$ 则表示编号为 $i$ 的群友做过题目 $j$**。

保证输入的数据满足题面中①②的条件。
## 输出格式

输出的第一行一个正整数 $k(1\le k\le n)$，表示邀请的群友的数目。

输出的第二行 $k$ 个正整数 $x_1,x_2,\dots,x_k$，表示邀请了编号为 $x_1,x_2,\dots x_k$ 的群友参加活动。

要求 $1\le x_i\le n$ 且 $x_i$ 两两不同。
## 样例

### 样例输入 #1
```
2
011
110
```
### 样例输出 #1
```
2
1 2
```
### 样例输入 #2
```
4
110000000
001100000
000011000
000000111
```
### 样例输出 #2
```
2
3 4
```
## 提示

对于样例 $1$，邀请所有群友后，有题目 $1$ 和 $3$ 两道题目只有奇数个群友没有做过。$n=2$ 时，**非标准的团建活动**必须恰好 $2$ 道题目有奇数个群友没有做过，满足条件。


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
title: "计算电压"
layout: "post"
diff: 省选/NOI-
pid: P2011
tag: ['字符串', '数学', '高斯消元']
---
# 计算电压
## 题目背景

相信不少人轻松灭掉 1，2 两题（蒟蒻无视此句） ，我相信，大家对物理也是很有兴趣的（众人：我们对揍人也是很有兴趣的） ，那么，再奉上 100 分给 Physicaler 们。
## 题目描述

现给定一个电阻网络，已知其中每条边上的电阻，和若干个点和负极之间的电压（电源电压不变） ，现在求任意两点之间的电压。
## 输入格式

第一行四个正整数 $n,m,k,q$，表示有 $n$ 个节点（可能是几个点用导线相连接，与一个点等价，编号为 $1$ 至 $n$，$0$ 号节点为电源负极），$m$ 个定值电阻（每个定值电阻连接两个点），电源正极有 $k$ 个接口，有 $q$ 个询问。

接下来 $k$ 行，每行两个正整数，表示这个正极的编号与该接线柱与电源负极之间的电压 $u_i$。

再接下来 $m$ 行，每行三个正整数 $v_i,w_i,r_i$，表示节点 $v_i$ 与 $w_i$ 之间有一条阻值为 $r_i$ 的电阻丝。

再接下来 $q$ 行，每行两个正整数 $a_i,b_i$，表示要求 $a_i$ 与 $b_i$ 之间的电压。
## 输出格式

一共 $q$ 行，每行一个实数表示 $a_i$ 与 $b_i$ 之间的电压（保留两位小数）。若 $a_i$ 点电压小于 $b_i$ 点电压，输出负值。
## 样例

### 样例输入 #1
```
3 5 1 3

1 18

1 2 6

1 3 2

2 3 6

3 0 6

2 0 2

1 0

2 3

1 2


```
### 样例输出 #1
```
18.00

-6.00

12.00


```
## 提示

【数据范围】

对于 $10\%$ 的数据，$1\le q\le 10$；

对于 $20\%$ 的数据，$1\le n\le 10$，且保证电路为串联、并联或混联；

对于 $40\%$ 的数据，$1\le n\le 40$，$k\le 5$；

对于 $100\%$ 的数据，$1\le k\le n\le 200$，$1\le m\le 2\times 10^5$，$1\le r_i,u_i\le 10^4$，$1\le q\le 10^6$。

【时空限制】

时间限制：1.00s，空间限制：125.00MB。

【样例解释】

如图所示。

![样例解释](https://cdn.luogu.com.cn/upload/pic/722.png)


---

---
title: "[USACO10HOL] Driving Out the Piggies G"
layout: "post"
diff: 省选/NOI-
pid: P2973
tag: ['2010', 'USACO', 'Special Judge', 'O2优化', '高斯消元']
---
# [USACO10HOL] Driving Out the Piggies G
## 题目描述

The Cows have constructed a randomized stink bomb for the purpose of driving away the Piggies. The Piggy civilization consists of N (2 <= N <= 300) Piggy cities conveniently numbered 1..N connected by M (1 <= M <= 44,850) bidirectional roads specified by their distinct endpoints A\_j and B\_j (1 <= A\_j <= N; 1 <= B\_j <= N). Piggy city 1 is always connected to at least one other city.

The stink bomb is deployed in Piggy city 1. Each hour (including the first one), it has a P/Q (1 <= P <= 1,000,000; 1 <= Q <=

1,000,000; P <= Q) chance of polluting the city it occupies. If it does not go off, it chooses a random road out of the city and follows it until it reaches a new city.  All roads out of a city are equally likely to be chosen.

Because of the random nature of the stink bomb, the Cows are wondering which cities are most likely to be polluted. Given a map of the Piggy civilization and the probability that the stink bomb detonates in a given hour, compute for each city the probability that it will be polluted.

For example, suppose that the Piggie civilization consists of two cities connected together and that the stink bomb, which starts in city 1, has a probability of 1/2 of detonating each time it enters a city:

1--2
We have the following possible paths for the stink bomb (where the last entry is the ending city):

1: 1
2: 1-2
3: 1-2-1

4: 1-2-1-2

5: 1-2-1-2-1

etc.
To find the probability that the stink bomb ends at city 1, we can add up the probabilities of taking the 1st, 3rd, 5th, ... paths above (specifically, every odd-numbered path in the above list). The probability of taking path number k is exactly (1/2)^k - the bomb must not remain in its city for k - 1 turns (each time with a probability of 1 - 1/2 = 1/2) and then land in the last city

(probability 1/2). 

So our probability of ending in city 1 is represented by the sum 1/2 + (1/2)^3 + (1/2)^5 + ... . When we sum these terms infinitely, we will end up with exactly 2/3 as our probability, approximately 0.666666667. This means the probability of landing in city 2 is 1/3, approximately 0.333333333. 

Partial feedback will be provided for your first 50 submissions. 
## 输入格式

\* Line 1: Four space separated integers: N, M, P, and Q

\* Lines 2..M+1: Line i+1 describes a road with two space separated integers: A\_j and B\_j

## 输出格式

\* Lines 1..N: On line i, print the probability that city i will be destroyed as a floating point number. An answer with an absolute error of at most 10^-6 will be accepted (note that you should output at least 6 decimal places for this to take effect).

## 样例

### 样例输入 #1
```
2 1 1 2 
1 2 

```
### 样例输出 #1
```
0.666666667 
0.333333333 

```
## 提示

感谢 @[Alpha](https://www.luogu.com.cn/user/87058) 贡献 Special Judge。
## 题目翻译

奶牛们已经制造了一种随机的臭弹，目的是驱赶小猪们。小猪文明由 $N$（$2 \leq N \leq 300$）个小猪城市构成，这些城市通过 $M$（$1 \leq M \leq 44,850$）条双向道路连接，具体的端点为 $A_j$ 和 $B_j$（$1 \leq A_j \leq N; 1 \leq B_j \leq N$）。小猪城市 1 总是与至少一个其他城市相连。

臭弹在小猪城市 1 部署。每个小时（包括第一个小时），它有 $P/Q$（$1 \leq P \leq 1,000,000; 1 \leq Q \leq 1,000,000; P \leq Q$）的概率污染它所处的城市。如果它没有爆炸，它会随机选择一条离开该城市的道路并沿着这条道路行进，直到到达一个新城市。所有离开一个城市的道路被选择的概率是相等的。

由于臭弹的随机特性，奶牛们想知道哪些城市最有可能被污染。给定小猪文明的地图和臭弹在某一小时内引爆的概率，计算每个城市被污染的概率。

例如，假设小猪文明由两个城市相连，并且臭弹在进入每个城市时都有 $1/2$ 的引爆概率：

$$
1--2
$$

我们有以下臭弹的可能路径（最后一项为结束城市）：

1: 1  
2: 1-2  
3: 1-2-1  
4: 1-2-1-2  
5: 1-2-1-2-1  
等。

要找出臭弹最终在城市 1 的概率，我们可以将上述第 1、3、5... 条路径的概率相加（具体来说，是上面列表中的每条奇数编号路径）。路径编号为 $k$ 的概率恰好为 $(1/2)^k$ —— 弹药在城市中必须停留 $k-1$ 回合（每次概率为 $1 - 1/2 = 1/2$），然后到达最后一个城市（概率为 $1/2$）。

因此我们在城市 1 的概率表示为和：

$$
\frac{1}{2} + \left(\frac{1}{2}\right)^3 + \left(\frac{1}{2}\right)^5 + \ldots
$$

当我们无限地求和这些项时，最终得到的概率正好是 $\frac{2}{3}$，约为 $0.666666667$。这意味着在城市 2 的概率是 $\frac{1}{3}$，约为 $0.333333333$。


---

---
title: "[CQOI2014] 和谐矩阵"
layout: "post"
diff: 省选/NOI-
pid: P3164
tag: ['2014', '重庆', '各省省选', 'Special Judge', '高斯消元']
---
# [CQOI2014] 和谐矩阵
## 题目描述

我们称一个由 $0$ 和 $1$ 组成的矩阵是和谐的，当且仅当每个元素都有偶数个相邻的 $1$。一个元素相邻的元素包括它本身，及他上下左右的 $4$ 个元素（如果存在）。给定矩阵的行数和列数，请计算并输出一个和谐的矩阵。注意：所有元素为 $0$ 的矩阵是不允许的。

## 输入格式

输入一行，包含两个空格分隔的整数 $m$ 和 $n$，分别表示矩阵的行数和列数。

## 输出格式

输出包含 $m$ 行，每行 $n$ 个空格分隔整数（$0$ 或 $1$），为所求矩阵。测试数据保证有解。

## 样例

### 样例输入 #1
```
4 4
```
### 样例输出 #1
```
0 1 0 0
1 1 1 0
0 0 0 1
1 1 0 1


```
## 提示

数据范围

$1\le n,m\le 40$。

感谢@miaomiao 提供spj。



---

---
title: "[HNOI2011] XOR和路径"
layout: "post"
diff: 省选/NOI-
pid: P3211
tag: ['2011', '湖南', '期望', '高斯消元', '位运算']
---
# [HNOI2011] XOR和路径
## 题目描述

给定一个无向连通图，其节点编号为 $1$ 到 $N$，其边的权值为非负整数。试求出一条从 $1$ 号节点到 $N$ 号节点的路径，使得该路径上经过的边的权值的“XOR 和”最大。该路径可以重复经过某些节点或边，当一条边在路径中出现多次时，其权值在计算“XOR 和”时也要被重复计算相应多的次数。


直接求解上述问题比较困难，于是你决定使用非完美算法。具体来说，从 $1$ 号节点开始，以相等的概率，随机选择与当前节点相关联的某条边，并沿这条边走到下一个节点，重复这个过程，直到走到 $N$ 号节点为止，便得到一条从 $1$ 号节点到 $N$ 号节点的路径。显然得到每条这样的路径的概率是不同的并且每条这样的路径的“XOR 和”也不一样。现在请你求出该算法得到的路径的“XOR 和”的期望值。
## 输入格式

输入文件的第一行是用空格隔开的两个正整数 $N$ 和 $M$，分别表示该图的节点数和边数。紧接着的 $M$ 行，每行是用空格隔开的三个非负整数 $u,v$ 和 $w$。$(1\le u,v\le N$，$0\le w\le 10^9)$，表示该图的一条边 $(u,v)$，其权值为 $w$。输入的数据保证图连通。

## 输出格式

输出文件仅包含一个实数，表示上述算法得到的路径的“XOR 和”的期望值，要求保留三位小数。（建议使用精度较高的数据类型进行计算）

## 样例

### 样例输入 #1
```
2 2
1 1 2
1 2 3
```
### 样例输出 #1
```
2.333
```
## 提示

### 样例解释

有 $\dfrac{1}{2}$ 的概率直接从 $1$ 号节点走到 $2$ 号节点，该路径的“XOR和”为 $3$；有 $\dfrac{1}{4}$ 的概率从 $1$ 号节点走一次 $1$ 号节点的自环后走到 $2$ 号节点，该路径的“XOR和”为 $1$；有 $\dfrac{1}{8}$ 的概率从 $1$ 号节点走两次 $1$ 号节点的自环后走到 $2$ 号节点，该路径的“XOR和”为 $3$…依此类推，可知“XOR和”的期望值为：$\dfrac{3}{2}+\dfrac{1}{4}+\dfrac{3}{8}+\dfrac{1}{16}+\dfrac{3}{32}+\cdots=\dfrac{7}{3}$，约等于 $2.333$。

### 数据范围

- $30\%$ 的数据满足 $N\le 30$。  
- $100\%$ 的数据满足 $2\le N\le 100$，$M\le 10000$，但是图中可能有重边或自环。


---

---
title: "[HNOI2013] 游走"
layout: "post"
diff: 省选/NOI-
pid: P3232
tag: ['2013', '湖南', '期望', '高斯消元']
---
# [HNOI2013] 游走
## 题目描述

给定一个 $n$ 个点 $m$ 条边的无向连通图，顶点从 $1$ 编号到 $n$，边从 $1$ 编号到 $m$。 

小 Z 在该图上进行随机游走，初始时小 Z 在 $1$ 号顶点，每一步小 Z 以相等的概率随机选择当前顶点的某条边，沿着这条边走到下一个顶点，获得等于这条边的编号的分数。当小 Z 到达 $n$ 号顶点时游走结束，总分为所有获得的分数之和。 现在，请你对这 $m$ 条边进行编号，使得小 Z 获得的总分的期望值最小。
## 输入格式

第一行是两个整数，分别表示该图的顶点数 $n$ 和边数 $m$。

接下来 $m$ 行每行两个整数 $u,v$，表示顶点 $u$ 与顶点 $v$ 之间存在一条边。 
## 输出格式

输出一行一个实数表示答案，保留三位小数。
## 样例

### 样例输入 #1
```
3 3
2 3
1 2
1 3
```
### 样例输出 #1
```
3.333
```
## 提示

#### 样例输入输出 1 解释

边 $(1,2)$ 编号为 $1$，边 $(1,3)$ 编号 $2$，边 $(2,3)$ 编号为 $3$。

---

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n\leq 10$。
- 对于 $100\%$ 的数据，保证 $2\leq n \leq 500$， $1 \leq m \leq 125000$，$1 \leq u, v \leq n$，给出的图无重边和自环，且从 $1$ 出发可以到达所有的节点。


---

---
title: "[JLOI2015] 装备购买"
layout: "post"
diff: 省选/NOI-
pid: P3265
tag: ['2015', '吉林', '高斯消元', '线性基', '向量']
---
# [JLOI2015] 装备购买
## 题目描述

脸哥最近在玩一款神奇的游戏，这个游戏里有 $n$ 件装备，每件装备有 $m$ 个属性，用向量 $\mathbf{z_i}=(a_1, \ldots ,a_j, \ldots , a_m)$ 表示 ($1 \leq i \leq n, \ 1 \leq j \leq m$)，每个装备需要花费 $c_i$，现在脸哥想买一些装备，但是脸哥很穷，所以总是盘算着怎样才能花尽量少的钱买尽量多的装备。对于脸哥来说，如果一件装备的属性能用购买的其他装备组合出（也就是说脸哥可以利用手上的这些装备组合出这件装备的效果），那么这件装备就没有买的必要了。

严格的定义是，如果脸哥买了 $\mathbf{z_{i_1}}, \ldots , \mathbf{z_{i_p}}$这 $p$ 件装备，那么对于任意待决定的 $\mathbf{z_h}$，不存在 $b_1, \ldots ,b_p$使得 $b_1\mathbf{z_{i_1}} + \ldots + b_p\mathbf{z_{i_p}} = \mathbf{z_h}$
​​ （$b_i$均是实数），那么脸哥就会买 $\mathbf{z_h}$，否则 $\mathbf{z_h}$ 对脸哥就是无用的了，自然不必购买。

举个例子，$\mathbf{z_1}=(1, 2, 3), \ \mathbf{z_2}=(3, 4, 5), \ \mathbf{z_h}=(2, 3, 4), \ b_1 =\frac{1}{2}, \ b_2 =\frac{1}{2}$，就有 $b_1\mathbf{z_1} + b_2\mathbf{z_2} = \mathbf{z_h}$ ，那么如果脸哥买了 $\mathbf{z_1}$和 $\mathbf{z_2}$ 就不会再买 $\mathbf{z_h}$了。

脸哥想要在买下最多数量的装备的情况下花最少的钱，你能帮他算一下吗？
## 输入格式

第一行两个数 $n,m$。接下来 $n$ 行，每行 $m$ 个数，其中第 $i$ 行描述装备 $i$ 的各项属性值。接下来一行 $n$ 个数，其中 $c_i$ 表示购买第 $i$ 件装备的花费。
## 输出格式

一行两个数，第一个数表示能够购买的最多装备数量，第二个数表示在购买最多数量的装备的情况下的最小花费。
## 样例

### 样例输入 #1
```
3 3
1 2 3
3 4 5
2 3 4
1 1 2
```
### 样例输出 #1
```
2 2
```
## 提示

如题目中描述，选择装备 $1$ 装备 $2$，装备 $1$ 装备 $3$，装备 $2$ 装备 $3$ 均可，但选择装备 $1$ 和装备 $2$ 的花费最小，为 $2$。

对于 $100\%$ 的数据 $,1 \le n,m \le 500$，$0 \le a_j \le 1000$。


---

---
title: "[CTSC2012] 电阻网络"
layout: "post"
diff: 省选/NOI-
pid: P4020
tag: ['递推', '2012', 'Special Judge', '高斯消元', 'CTSC/CTS']
---
# [CTSC2012] 电阻网络
## 题目描述

给定一个树型电网，树中的每条边上有一个电阻$R_i$，电阻值均为10000Ω。下图为一个包含4个节点的树型电路情况：

![图1](https://i.loli.net/2018/10/03/5bb46c0c587be.png)

树中的所有叶子节点（度为1的节点称为叶子）都接地，每条线上都接地，每条线上都附有10000Ω的电阻，最终形成的电网如下图所示：

![图2](https://i.loli.net/2018/10/03/5bb46c0c72576.png)

现有如下两种操作：

`C u v w`：表示在边`<u,v>`上串联一个电源，电源的大小为$w$伏，电源位于靠近节点$u$一侧（如下图所示），电源负极指向$u$。注意同一条边上可以串联多个电源。

![图3](https://i.loli.net/2018/10/03/5bb46c0c6a122.png)

`Q u` ：表示询问点$u$当前的电压，此是指对地。

如对上图进行`C 2 4 5`操作后，网络变为：

![图4](https://i.loli.net/2018/10/03/5bb46c0c86064.png)

此时每个节点上的电压见上图的标注。

## 输入格式

输入文件 circuit.in 的第一行包含两个整数 $N,M$，分别表示树的节点数和操作个数。接下来 $N-1$ 行，每行两个数 $u,v$，表示有一条连接节点 $u,v$ 的边，这条边上恰好包含一个电阻。

接下来 $M$ 行，每行一个命令，格式见题目描述。

## 输出格式

输出文件为 circuit.out。对于每个 `Q` 命令，输出一个数表示此刻该点的电压值。你可以输出任意多位的小数，只要你的答案和标准答案相差不超过 `10^(-3)` 就算合法。

## 样例

### 样例输入 #1
```
4 3
1 2
2 3
2 4
Q 2
C 2 4 5
Q 2
```
### 样例输出 #1
```
0.0000000000
-1.6666666666
```
## 提示

【样例说明】

对于第一个询问，由于原图中没有电源，所以没有电流，所有点的电压都相

等（否则如果有 U i >U j ，则就有 i 流向 j 的电流，与没有电源矛盾）,都等于地电

压 0V。

之后在<2,4>中加一个 5V 的电源，得到的新图见题目描述。

整理后可以发现，新图的形式是串联(电源,R 2 +10000,并联(R 1 +10000,

R 3 +10000))，由此可以得到新图的总电阻为:

R 2 +10000+1/(1/(R 3 +10000)+1/(R 1 +10000))=30000 Ω.

所以流过节点 4 的电流就是 5/30000A，所以 U 4 =5/3V。U 2 =U 4 +R 2 \*I-5=-5/3V，由

于 U 1 和 U 3 形式对称，由分压关系可知 U 1 =U 3 =U 2 \*10000/(10000+10000)=-5/6V。

【数据规模】

30%的数据保证 N,M ≤ 30

60%的数据保证 N,M ≤ 3000

100%的数据保证 3 ≤ N,M ≤ 50000，1 ≤ u,v ≤ n，1 ≤ w ≤ 10，树中最长链的长

度不超过 50。



---

---
title: "[HEOI2015] 小 Z 的房间"
layout: "post"
diff: 省选/NOI-
pid: P4111
tag: ['2015', '各省省选', '河北', '生成树', '素数判断,质数,筛法', '高斯消元']
---
# [HEOI2015] 小 Z 的房间
## 题目描述

你突然有了一个大房子，房子里面有一些房间。事实上，你的房子可以看做是一个包含 $n\times m$ 个格子的格状矩形，每个格子是一个房间或者是一个柱子。在一开始的时候，相邻的格子之间都有墙隔着。

你想要打通一些相邻房间的墙，使得所有房间能够互相到达。在此过程中，你不能把房子给打穿，或者打通柱子（以及柱子旁边的墙）。同时，你不希望在房子中有小偷的时候会很难抓，所以你希望任意两个房间之间都只有一条通路。现在，你希望统计一共有多少种可行的方案，答案对 $10^9$ 取模。

## 输入格式

第一行两个整数 $n,m$。

接下来 $n$ 行，每行 $m$ 个字符 `.` 或 `*`，其中 `.` 代表房间，`*` 代表柱子。

## 输出格式

一行一个整数，表示合法的方案数对 $10^9$ 取模后的值。
## 样例

### 样例输入 #1
```
2 2
..
..

```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
2 2
*.
.*

```
### 样例输出 #2
```
0

```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，$n,m \le 3$。
- 对于 $50\%$ 的数据，$n,m \le 5$。
- 有 $40\%$ 的数据，$\min(n,m) \le 3$。
- 有 $30\%$ 的数据，不存在柱子。
- 对于 $100\%$ 的数据，$1 \le n,m \le 9$。



---

---
title: "[JSOI2008] 最小生成树计数"
layout: "post"
diff: 省选/NOI-
pid: P4208
tag: ['2008', '并查集', '各省省选', '江苏', '生成树', '素数判断,质数,筛法', '高斯消元']
---
# [JSOI2008] 最小生成树计数
## 题目描述

现在给出了一个简单无向加权图。你不满足于求出这个图的最小生成树，而希望知道这个图中有多少个不同的最小生成树。（如果两棵最小生成树中至少有一条边不同，则这两个最小生成树就是不同的）。由于不同的最小生成树可能很多，所以你只需要输出方案数对 $31011$ 的模就可以了。
## 输入格式

第一行包含两个数，$n$ 和 $m$，其中 $1 \le n \le 100$，$1 \le m \le 1000$，表示该无向图的节点数和边数。每个节点用 $1 \sim n$ 的整数编号。

接下来的 $m$ 行，每行包含两个整数：$a,b,c$，表示节点 $a,b$ 之间的边的权值为 $c$，其中 $1 \le c \le 10^9$。

数据保证不会出现自回边和重边。注意：具有相同权值的边不会超过 $10$ 条。
## 输出格式

输出不同的最小生成树有多少个。你只需要输出数量对 $31011$ 的模就可以了。
## 样例

### 样例输入 #1
```
4 6
1 2 1
1 3 1
1 4 1
2 3 2
2 4 1
3 4 1
```
### 样例输出 #1
```
8

```
## 提示

### 数据范围及约定

对于全部数据，$1 \le n \le 100$，$1 \le m \le 1000$，$1\leq c_i\leq 10^9$。


---

---
title: "[SHOI2014] 概率充电器"
layout: "post"
diff: 省选/NOI-
pid: P4284
tag: ['2014', '各省省选', '上海', '连通块', '条件概率', '期望', '高斯消元']
---
# [SHOI2014] 概率充电器
## 题目描述

著名的电子产品品牌 SHOI 刚刚发布了引领世界潮流的下一代电子产品——概率充电器：

“采用全新纳米级加工技术，实现元件与导线能否通电完全由真随机数决定！SHOI 概率充电器，您生活不可或缺的必需品！能充上电吗？现在就试试看吧！”

SHOI 概率充电器由 $n-1$ 条导线连通了 $n$ 个充电元件。进行充电时，每条导线是否可以导电以概率决定，每一个充电元件自身是否直接进行充电也由概率决定。随后电能可以从直接充电的元件经过通电的导线使得其他充电元件进行间接充电。

作为 SHOI 公司的忠实客户，你无法抑制自己购买 SHOI 产品的冲动。在排了一个星期的长队之后终于入手了最新型号的 SHOI 概率充电器。你迫不及待地将 SHOI 概率充电器插入电源——这时你突然想知道，进入充电状态的元件个数的期望是多少呢？
## 输入格式

第一行一个整数 $n$。概率充电器的充电元件个数。充电元件由 $1 \sim n$ 编号。

之后的 $n-1$ 行每行三个整数 $a, b, p$，描述了一根导线连接了编号为 $a$ 和 $b$ 的充电元件，通电概率为 $p\%$。

第 $n+2$ 行 $n$ 个整数 $q_i$。表示 $i$ 号元件直接充电的概率为 $q_i\%$。
## 输出格式

输出一行一个实数，为能进入充电状态的元件个数的期望，四舍五入到小数点后 6 位小数。
## 样例

### 样例输入 #1
```
3
1 2 50
1 3 50
50 0 0
```
### 样例输出 #1
```
1.000000
```
### 样例输入 #2
```
5
1 2 90
1 3 80
1 4 70
1 5 60
100 10 20 30 40
```
### 样例输出 #2
```
4.300000
```
## 提示

对于 $30\%$ 的数据，$n \leq 5 \times 10^3$。

对于 $100\%$ 的数据，$n \leq 5 \times 10^5$，$0 \leq p,q_i \leq 100$。


---

---
title: "随机漫游"
layout: "post"
diff: 省选/NOI-
pid: P4321
tag: ['动态规划 DP', '图论', 'O2优化', '期望', '高斯消元']
---
# 随机漫游
## 题目描述

H 国有 $N$ 个城市

在接下来的 $M$ 天，小 c 都会去找小 w，但是小 c 不知道小 w 的具体位置，所以小 c 决定每次随机找一条路走，直到遇到了小 w 为止

小 c 知道小 w 只有可能是在 $c_1, c_2.. c_n$ 这 $n$ 个城市中的一个，小 c 想知道在最坏情况下，小 c 遇到小 w 期望要经过多少条道路

H 国所有的边都是无向边，两个城市之间最多只有一条道路直接相连，没有一条道路连接相同的一个城市

任何时候，H 国不存在城市 $u$ 和城市 $v$ 满足从 $u$ 无法到达 $v$
## 输入格式

输入第 1 行一个正整数$N, E$，分别表示 H 国的城市数与边的数量

输入第 2 行至第 $E+1$ 行，每行两个正整数 $u, v$，分别表示城市 $u$ 到城市 $v$ 有一条道路

输入第 $E+2$ 行一个正整数 $M$

输入第 $E+3$ 行至第 $E+M+2$ 行每行 $n+2$ 个正整数，第一个正整数为 $n$，接下来 $n$ 个互不相同的正整数 $c_i$，最后一个正整数 $s$ 表示小 c 所在的城市
## 输出格式

输出共 $M$ 行，每行一个正整数 $r$ 表示答案

如果你计算出来的期望为 $\frac{q}{p}$，其中$p, q$互质，那么你输出的 $r$ 满足 $r\times p \equiv q(\mathrm{mod}\ 998244353)$，
且$0\leq r < 998244353$，可以证明这样的 $r$是唯一的
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
3
2 1 2 1		
3 1 2 3 1
1 3 1
```
### 样例输出 #1
```
1
4
4
```
## 提示

$H$ 国的道路构成一条链，所以最坏情况下就是小 w 在深度最大的点上(以小 c 所在的城市为根)

对于第一天，小 c 所在的城市为 1，深度最大的点为 2，城市 1 只能到达城市 2，期望经过 1 条道路到达

对于第二天，小 c 所在的城市为 1，深度最大的点为 3，计算的期望经过 4 条道路到达

第三天同第二天

最坏情况也就是说经过所有 $n$ 个可能的城市至少一遍

subtask1 : 10分，$N = 4, M = 12$

subtask2 : 15分，$N =10, M = 100000$

subtask3 : 15分，$N = 18, M = 1$

subtask4 : 10分，$N = 18, M = 99995$，图是一条链

subtask5 : 10分，$N = 18, M = 99996$，所有的 $s$ 都相同

subtask6 : 15分，$N = 18, M = 99997$，$E = N-1$

subtask7 : 15分，$N = 18, M = 99998$，所有的 $s$ 都相同

subtask8 : 10分，$N = 18, M = 99999$

对于所有数据 : $1\leq N\leq 18, 1\leq M\leq 100000, 1\leq E\leq \frac{N(N-1)}{2}$


---

---
title: "[JSOI2009] 有趣的游戏"
layout: "post"
diff: 省选/NOI-
pid: P6125
tag: ['字符串', '动态规划 DP', '2009', '高斯消元', 'AC 自动机']
---
# [JSOI2009] 有趣的游戏
## 题目描述

小阳阳发明了一个有趣的游戏：有 $n$ 个玩家，每个玩家都有一个长度为 $l$ 的字母序列，任何两个玩家的字母序列不同。共有 $m$ 种不同的字母，所有的字母序列都由这 $m$ 种字母构成。为了方便，我们取大写字母的前 $m$ 个字母。   
例如 $m=3,l=4,\texttt{ABAA}$ 和 $\texttt{CBCA}$ 是两个合法的字母序列。       
现在由小阳阳来操控一台神奇的机器，每个时刻机器会随机产生一个字母，其中第 $i$ 种字母随机出来的概率为 $\dfrac{p_i}{q_i}$ ，显然 $\sum \limits_{k=1}^m \dfrac{p_i}{q_i}=1$。  
这样 $T$ 个时刻后机器会产生一个长度为 $T$ 的字母序列。  
如果某个时刻某个玩家发现自己的字母序列在机器产生的字母序列中出现了，“出现”的定义是玩家的字母序列是机器产生的字母序列中连续的一段，那么我们称这个玩家获胜，游戏结束。       
现在小阳阳感兴趣的一个问题是，每个玩家分别有多大的概率能获得这场游戏的胜利呢？  
## 输入格式

第一行有三个正整数 $n,l,m$ 表示有 $n$ 个人，每个字母的序列长度均为 $l$，共有 $m$ 个字母。   
接下来 $m$ 行，每行有两个非负整数 $p, q$，表示随机到第 $i$ 个字母的概率为 $\frac{p}{q}$。   
接下来 $n$ 行，每行有一个长度为 $l$ 的字母序列，表示第 $i$ 个人的字母序列。
## 输出格式

包含 $n$ 行，每行一个实数，表示第 $i$ 个人获胜的概率，输出结果四舍五入到两位小数。 
## 样例

### 样例输入 #1
```
3 2 2
1 2
1 2
AB
BA
AA
```
### 样例输出 #1
```
0.25
0.50
0.25
```
### 样例输入 #2
```
3 4 2
1 2
1 2
AABA
ABAA
BAAA
```
### 样例输出 #2
```
0.31
0.33
0.37
```
## 提示

$1 \leq n,l,m \leq 10$，$0 \leq p_i \leq q_i \leq 10$ 且 $\gcd(p,q) = 1$。


---

---
title: "[JSOI2012] 始祖鸟"
layout: "post"
diff: 省选/NOI-
pid: P6126
tag: ['2012', '各省省选', '江苏', 'Special Judge', '高斯消元']
---
# [JSOI2012] 始祖鸟
## 题目描述

最近，进香河地带出现了一家“始祖鸟专卖店”，然而这并不只是一时的心血来潮。         
                         
早在远古时期，进香河地带就以其秀美的环境和适宜的温度吸引了成群的始祖鸟。始祖鸟是一种团结的鸟类，它们总是通过各种方式来增强种群内部的交流，聚会则是其中之一。因为聚会不但可以增强朋友之间的友谊，而且可以认识新的朋友。        
                             
现在有 $N$ 只始祖鸟，我们从 $1$ 开始编号。对于第 $i$ 只始祖鸟，有 $M_i$ 个认识的朋友，它们的编号分别是 $F_{i,1}，F_{i,2}，…，F_{i,M_i}$。朋友的认识关系是单向的，也就是说如果第$s$只始祖鸟认识第 $t$ 只始祖鸟，那么第 $t$ 只始祖鸟不一定认识第 $s$ 只始祖鸟。        
   
聚会的地点分为两处，一处在上游，一处在下游。对于每一处聚会场所，都必须满足对于在这个聚会场所中的始祖鸟，有恰好有偶数个自己认识的朋友与之在同一个聚会场所中。当然，每一只始祖鸟都必须在两处聚会场所之一。         
       
现在需要你给出一种安排方式。你只需要给出在上游的始祖鸟编号，如果有多组解，请输出任何一组解。 
## 输入格式

输入数据包含 $N+1$ 行，第一行是数字 $N$，代表始祖鸟的个数。       
接下来 $N$ 行，第 $i+1$ 行的第一个数字是 $M_i$，表示第 $i$ 只鸟的朋友个数。之后有 $M_i$ 个数字依次为 $F_{i,1},F_{i,2},…,F_{i,M_i}$ 表示第$i$只始祖鸟朋友的标号。 
## 输出格式

输出数据包含 $2$ 行，第一行有一个非负整数 $k$，表示在上游参加聚会的始祖鸟个数。第二行有 $k$ 个正整数，表示在这个 $k$ 只始祖鸟的编号，你可以以任意顺序输出这些编号。如果无法满足要求，只输出一行`Impossible`。 
## 样例

### 样例输入 #1
```
5
3 2 3 4
2 1 3
4 2 1 4 5
2 1 3
1 3
```
### 样例输出 #1
```
3
1 2 3
```
## 提示

#### 数据规模与约定

- 对于$100\%$的数据，$1 \le N \le 2000$。


---

---
title: "【模板】Matrix-Tree 定理"
layout: "post"
diff: 省选/NOI-
pid: P6178
tag: ['图论', '矩阵树定理', '生成树', '高斯消元']
---
# 【模板】Matrix-Tree 定理
## 题目描述

给定一张 $n$ 个结点 $m$ 条边的带权图（可能为无向图，可能为有向图）。

定义其一个生成树 $T$ 的权值为 $T$ 中所有边权的乘积。

求其所有不同生成树的权值之和，对 $10^9+7$ 取模。

---

注意：

1. 本题中，有向图的生成树指的是 **以 $1$ 为根的外向树**；

2. 两棵生成树 $T_1,T_2$ 不同，当且仅当存在存在一条边 $e$，满足 $e\in T_1,\ \ e\notin T_2$。
## 输入格式

第一行：三个整数 $n,m,t$，分别表示图的结点数量，边的数量和图的类型（$t=0$ 时为无向图，$t=1$ 时为有向图）。

接下来 $m$ 行：每行三个整数 $u,v,w$。

如果 $t=0$，表示 $u,v$ 之间有一条权值为 $w$ 的无向边；

如果 $t=1$，表示从 $u$ 到 $v$ 有一条权值为 $w$ 的有向边。
## 输出格式

第一行：一个整数 $ans$，表示给定的图的生成树权值和对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
5 8 0
2 3 1
1 2 3
4 5 1
4 2 2
3 5 2
3 4 3
3 4 1
3 3 5

```
### 样例输出 #1
```
144

```
### 样例输入 #2
```
5 9 1
1 2 3
3 2 1
1 3 1
2 4 2
3 5 1
4 3 4
3 5 1
5 4 1
4 4 6

```
### 样例输出 #2
```
72

```
## 提示

【样例 $1$ 解释】

样例 $1$ 中的无向图如左图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/pxtx9z5a.png)

右图为其一个权值为 $3\times 1\times 2\times 3=18$ 的生成树的例子。

---

【样例 $2$ 解释】

样例 $2$ 中的有向图如左图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/4276yln3.png)

右图为其一个权值为 $1\times 1\times 1\times 2=2$ 的生成树（以 $1$ 为根的外向树）的例子。

---

【数据范围】

对于 $100\%$ 的数据：$1\leq n\leq 300,\ \ 1\leq m\leq 10^5,\ \ t\in \{0,1\},\ \ 1\leq u,v\leq n,\ \ 1\leq w\leq 10^9$。

对于测试点 $1,2,3,4,5,6$，$t=0$；对于测试点 $7,8,9,10,11$，$t=1$。

图中 **可能** 存在重边和自环，重边算作多条边。


---

---
title: "【模板】LGV 引理"
layout: "post"
diff: 省选/NOI-
pid: P6657
tag: ['LGV 引理', '容斥原理', '高斯消元']
---
# 【模板】LGV 引理
## 题目描述

这是一道模板题。

有一个 $n\times n$ 的棋盘，左下角为 $(1,1)$，右上角为 $(n,n)$，若一个棋子在点 $(x,y)$，那么走一步只能走到 $(x+1,y)$ 或 $(x,y+1)$。

现在有 $m$ 个棋子，第 $i$ 个棋子一开始放在 $(a_i,1)$，最终要走到 $(b_i,n)$。问有多少种方案，使得每个棋子都能从起点走到终点，且对于所有棋子，走过路径上的点互不相交。输出方案数 $\bmod\ 998244353$ 的值。

两种方案不同当且仅当存在至少一个棋子所经过的点不同。
## 输入格式

**本题有多组数据**

第一行一个整数 $T$，表示该测试点的数据组数。

对于每组数据：

第一行两个整数 $n,m$，分别表示棋盘的大小和起点终点的数量。

接下来 $m$ 行，每行 $2$ 个整数 $a_i,b_i$，其意义已在题目描述中说明。
## 输出格式

对于每一组数据，输出一行一个整数表示方案数 $\bmod\ 998244353$ 的值。
## 样例

### 样例输入 #1
```
3
3 2
1 2
2 3
5 2
1 3
3 5
10 5
3 5
4 7
5 8
7 9
9 10
```
### 样例输出 #1
```
3
155
2047320
```
## 提示

- 对于 $30\%$ 的数据，$n\leq 100$，$m\leq 8$。 

- 对于 $100\%$ 的数据，$T\leq5$，$2\leq n\leq10^6$，$1\leq m\leq100$，$1\leq a_1\leq a_2\leq \dots\leq a_m\leq n$，$1\leq b_1\leq b_2\leq \dots\leq b_m\leq n$。


---

---
title: "[THUPC 2017] 气氛"
layout: "post"
diff: 省选/NOI-
pid: P7429
tag: ['计算几何', '2017', '线性代数', '高斯消元', 'THUPC']
---
# [THUPC 2017] 气氛
## 题目描述

北大街，在中国是一个非常常见的地名，比较著名的有上海北大街，西安北大街，成都北大街，太原北大街，中关村北大街等。

我们都知道，北的意思是自由民主，大的意思是兼收并蓄，所以住在北大街的人也性情迥异，我们假设在北大街住了 $n$ 个人。

有人向住在北大街的这 $n$ 个人提了 $n-1$ 个问题，比如：

「用不用筷子？」

「吃不吃红烧肉？」

「写代码用 tab 还是 space」

「大括号换不换行？」

「……」

根据每个人的回答，他会被分配一个 $n-1$ 维的零一坐标，也就是一个点。这样 $n$ 个点可以恰好构成一个 $n-1$ 维空间中的凸包。

北大街的居民认为，在这个多面体内，便是华夏；多面体之外，便是蛮夷。我们可以很容易的计算出华夏部分的广义凸包体积。

有一天，清华路的 B 君来北大街玩，听说了这个故事觉得很有趣，于是也试着给出了这 $n-1$ 个问题的答案，

清华路的 B 君，当然认为自己属于华夏，但是北大街表示在 $n-1$ 维空间中如果有 $n+1$ 个点的话，华夏部分的体积难以计算。

这下子气氛突然僵化。所以这个问题就留给你了，输入 $n-1$ 维度空间中的 $n+1$ 个点，求广义凸包的体积。

由于这个体积可能不是整数，你只需要输出体积乘以 $n-1$ 的阶乘，然后对 $10^9+7$ 取模的结果。
## 输入格式

从标准输入读入数据。

第一行一个整数 $T$ 表示组数，接下来是 $T$ 组数据

每组数据的第一行是一个整数 $n$ 。

接下来 $n+1$ 行，每行 $n-1$ 个整数，表示在 $n-1$ 维空间中的一个点。
## 输出格式

输出到标准输出。

对于每组数据，输出一行一个整数表示答案。

输入 $n+1$ 个点的凸包体积乘以 $n-1$ 的阶乘，然后对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
1
3
0 0
0 1
1 0
1 1
```
### 样例输出 #1
```
2
```
## 提示

$1\le t\le 100,3\le n\le35$

点的坐标一定是 $0$ 或者 $1$。
#### 版权信息
来自 THUPC（THU Programming Contest，清华大学程序设计竞赛）2017。


---

---
title: "既见君子"
layout: "post"
diff: 省选/NOI-
pid: P7437
tag: ['O2优化', '生成树', '线性代数', '高斯消元', '状压 DP']
---
# 既见君子
## 题目背景

友情客串：wygz（无忧公主）

wygz 每次从进校到机房，都要尽量避开“屠夫”老师。然而，有一天，她忽然发现一些门上居然贴了“请勿从此门进出”的标签！
## 题目描述

校园可以抽象成一张 $n$ 个点 $m$ 条无向边（可能有重边，无自环）的**连通**无向图，点从 $1$ 标号到 $n$。校门在 $1$ 号点，而机房在 $n$ 号点，屠老师的办公室在点 $z$（$z\ne 1,n$）。

然而，工作人员（~~其实是樱初音~~）封锁了其中的 $m-n+1$ 条边，使得剩余的图（包括所有点以及剩余的边）仍然连通，此时任意两点之间有且仅有一条简单路径。工作人员会**等概率地**选择一种封锁方案。（若 $m=n-1$ 则不封锁任何边，保持不变）

wygz 当然不希望屠老师的办公室出现在她的必经之路上。她希望你算出从校门到机房的路径**必须**经过屠老师的办公室的概率。答案对 $998244353$ 取模。
## 输入格式

第一行三个正整数 $n$、$m$ 和 $z$，表示点数、边数和屠老师的办公室的位置。

以下 $m$ 行，每行两个正整数 $u$、$v$，表示一条连接 $u$ 和 $v$ 的无向边。
## 输出格式

一行一个非负整数，表示答案对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
4 5 2
1 2
1 3
2 3
2 4
3 4
```
### 样例输出 #1
```
374341633
```
### 样例输入 #2
```
6 8 4
1 2
1 3
2 3
2 4
2 5
4 5
4 6
5 6
```
### 样例输出 #2
```
374341633
```
## 提示

#### 样例解释：
样例 #1：生成树共 $8$ 个，有 $5$ 个满足 $1$ 到 $4$ 经过 $2$。$\dfrac 5 8\equiv 374341633\pmod {998244353}$。

样例 #2：生成树共 $24$ 个，有 $15$ 个满足 $1$ 到 $6$ 经过 $4$。$\dfrac {15} {24}\equiv 374341633\pmod {998244353}$。

#### 数据范围：

| 数据点编号 | $n$ | $m$ |
| :----------: | :----------: | :----------: |
| $1$ | $=3$ | $\le 5$ |
| $2$ | $=3$ | $\le 10^5$ |
| $3,4$ | $=7$ | $\le 15$ |
| $5,6$ | $=7$ | $\le 10^5$ |
| $7$ | $=20$ | $=n-1$ |
| $8,9$ | $=20$ | $=n$ |
| $10,11,12$ | $=18$ | $\le 10^5$ |
| $13,14,15,16$ | $=19$ | $\le 10^5$ |
| $17,18,19,20$ | $=20$ | $\le 10^5$ |

对 $100\%$ 的数据，$3\le n\le 20$，$n-1\le m\le 10^5$，$z\ne 1$ 且 $z\ne n$。

**数据保证输入的图的生成树个数模 $998244353$ 非零。**


---

---
title: "【模板】特征多项式"
layout: "post"
diff: 省选/NOI-
pid: P7776
tag: ['线性代数', '高斯消元']
---
# 【模板】特征多项式
## 题目背景

这是一道模板题。
## 题目描述

给出 $n$ 和一个 $n\times n$ 的矩阵 $A$，在模 $998244353$ 意义下求其特征多项式。
## 输入格式

第一行一个正整数 $n$。\
接下来 $n$ 行每行 $n$ 个非负整数，表示矩阵 $A$。
## 输出格式

输出一行 $n+1$ 个正整数，表示其特征多项式 $p_A(x)$ 从低到高的系数。
## 样例

### 样例输入 #1
```
3
1 2 3
4 5 6
7 8 9
```
### 样例输出 #1
```
0 998244335 998244338 1 
```
## 提示

对于一个 $n\times n$ 的矩阵 $A$，设其特征多项式为 $p_A(x)$，满足
$$p_A(x)=\det(xI_n-A)$$
其中，$I_n$ 为一个 $n\times n$ 的单位矩阵。

对于 $10\%$ 的数据，$1\le n\le 5$；\
对于 $40\%$ 的数据，$1\le n\le 50$；\
对于另外 $10\%$ 的数据，$\forall1\le i\le n,1\le j\le i-1,A_{i,j}=0$，即 $A$ 为上三角矩阵；\
对于另外 $20\%$ 的数据，$\forall1\le i\le n,1\le j\le i-2,A_{i,j}=0$，即 $A$ 为上海森堡矩阵；\
对于 $100\%$ 的数据，$1\le n\le 500$，$A_{i,j}\in[0,998244352]$。


---

---
title: "追寻 | Pursuit of Dream"
layout: "post"
diff: 省选/NOI-
pid: P8967
tag: ['动态规划 DP', '洛谷原创', 'O2优化', '排列组合', '期望', '高斯消元', '洛谷月赛']
---
# 追寻 | Pursuit of Dream
## 题目背景

“遇到自己喜欢的人或事情的时候，千万不要放弃”

“要一直追寻下去…”

“因为即使成功希望渺茫，也有可能”

有谁和我说过这句话，脑海中忽然闪过一下，被当做无用的激励一同忘却了。现在想要回忆，却总也记不起来。

好不容易来人间一趟，那就别留下遗憾。

房檐落下的雨滴有规律的敲着石砖，那夜的雨声中，却也悄无声息了。

逆着风吹干眼泪，说不出口的痛越藏越多，腐烂在肚子里，却又不知道彼此心知且肚明，所以无法孕育出美好的结局，只会是恋者相残的戏码不停上演。

---

 看见了漫天星野坠落在你的眼底，从此甘愿在那海底般低压的梦境中堕落。

三千尺星空的光辉映照不出那人的身影，璀璨中徒留神明思故人；那人却散入了或许碎散的星辰大海，让神明寻觅了一生。

那些无法兑现的渴望，会日渐荒芜，然后梦境会失去生机，裂缝中会蔓出黑暗，泪无葬身之地。

是神明告诉我的，可是我不信，因为没有时间还等着我空想了。

神明还说，人死了以后，提前离开的亲人都会在另外一个世界等你。

其实，我也会想，这一定就是另外一个世界。
## 题目描述

在 $n$ 维空间中有一个梦想。这梦想坐落在 $(d_1, d_2, \ldots, d_n)$ 的地方。而你从 $(0, 0, \ldots, 0)$ 开始，开启寻梦的旅程。

你的步伐轻缓，每一步只能走一个单位长度。你并不知道你的梦想位于哪里，所以你只能随机选择 $n$ 个正方向中的一个，然后向这个方向走一步。也就是说，在 $[1, n]$ 中均匀随机选择一个正整数 $h$，然后，使你在第 $h$ 维的坐标变成原来的坐标加一。

然而，天有不测风云。在你走每一步的过程中，你会有 $p = \sum_{i = 1}^k p_i$ 的概率散入天际，并开始一段新的旅程。你会在 $k$ 个地点中的一个重新开始这段旅程，其中第 $i$ 个地点的坐标是 $(a_{i,1}, a_{i,2}, \ldots, a_{i,n})$，从这里重新开始的概率为 $p_i$。

那么，期望下，你离到达这个梦想还需要多少步呢？
## 输入格式

第一行，两个正整数 $n,k$。

第二行，$n$ 个非负整数 $d_1, d_2, \ldots, d_n$。

接下来 $k$ 行，第 $i$ 行 $n + 1$ 个整数 $a_{i, 1}, a_{i, 2}, \ldots, a_{i, n}, x_i$，每行最后一个整数 $x_i$ 表示 $p_i=x_i\times 10^{-8}$。

输入的 $x_i$ 保证了 $p_i > 0$ 且 $p < 1$。

保证每个 $x_i$ 在所有可能的组合中等概率随机生成。
## 输出格式

一行，一个整数，表示答案对 $998244353$ 取模的结果。

如果你不知道如何进行实数取模：可以说明答案一定是有限的，且是有理数，设它的最简分数形式为 $\frac{p}{q}$。如果存在一个整数 $x$ 满足 $x \cdot q \equiv p \pmod{998244353}$ 且 $0 \le x < 998244353$，那么你只需输出 $x$ 的值即可。

由于保证了 $x_i$ 是随机生成的，可以说明以接近 $1$ 的概率答案在模意义下存在。事实上，一个当 $x_i$ 尚不确定时以合理地高的概率给出正确答案的算法足以通过本题，考察复杂的模意义下的有理数的处理不是我们的本意。
## 样例

### 样例输入 #1
```
2 1
1 1
0 0 50000000

```
### 样例输出 #1
```
14

```
### 样例输入 #2
```
2 1
1 2
0 0 20000000

```
### 样例输出 #2
```
291154624

```
### 样例输入 #3
```
3 3
2 3 4
2 1 0 30000000
1 2 3 19000000
2 3 4 1000000

```
### 样例输出 #3
```
430536142

```
## 提示

**【样例解释 \#1】**

这是你的一种追寻梦想的方式：

你从 $(0,0)$ 出发，走一步到 $(1,0)$，再走一步到 $(2,0)$，再走一步到 $(3,0)$，但是在路上散入天际，从 $(0,0)$ 重新开始旅程。

然后继续从 $(0,0)$ 出发，走一步到 $(0,1)$，再走一步到 $(1,1)$，但是在路上散入天际，从 $(0,0)$ 重新开始旅程。

接着从 $(0,0)$ 出发，走一步到 $(1,0)$，再走一步到 $(1,1)$，找到了你的梦想。

在这种情况下，你需要 $7$ 步到达这个梦想。发生这种情况的概率是 $4^{-7}$。

---

**【样例解释 \#2】**

答案为 $\frac{505}{24} \approx 21.041667$。  
不难验证 $291154624 \times 24 \equiv 505 \pmod{998244353}$，故应输出 $291154624$。

---

**【样例解释 \#3】**

答案为 $\frac{1399505}{21519} \approx 65.035782$。

---

**【数据范围】**

**本题采用捆绑测试且使用子任务依赖。**

| 子任务编号 | 特殊限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $n=1$，$k=1$ | 11 |
| 2 | $n=1$ | 12 |
| 3 | $k=1$ | 12 |
| 4 | $n=2$，$1 \le d_1 \cdot d_2 \le 200$ | 13 |
| 5 | $k \le 200$ | 22 |
| 6 | 无特殊限制 | 30 |

对于 $100 \%$ 的数据：

- $1 \le n \le 100$，$1 \le k \le 10000$。
- $d_i \ge 0$，$\sum_i d_i \le 10^7$。
- $0 \le a_{i, j} \le {10}^7$。
- $x_i \ge 1$，$\sum_i x_i < {10}^8$。此即保证了 $p_i > 0$ 和 $p < 1$。
- 保证存在一个 $i \in [1, k]$ 使得对于每个 $j \in [1, n]$ 均有 $a_{i,j} \le d_j$。
- 保证每个 $(a_{i, 1}, a_{i, 2}, \ldots, a_{i, n})$ 作为空间中的点互不相同。
- 保证每个 $x_i$ 在所有可能的组合中等概率随机生成。

---

**【提示】**

由于保证了 $x_i$ 是随机生成的，可以说明以接近 $1$ 的概率答案在模意义下存在。事实上，一个当 $x_i$ 尚不确定时以合理地高的概率给出正确答案的算法足以通过本题，考察复杂的模意义下的有理数的处理不是我们的本意。

样例中的 $x_i$ 不是随机生成的，仅为理解题意所用。


---

