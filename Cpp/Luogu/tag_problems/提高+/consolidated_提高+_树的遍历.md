---
title: "[OOI 2024] Evidence Board"
layout: "post"
diff: 提高+/省选-
pid: P13503
tag: ['贪心', '2024', 'Special Judge', '树的遍历', 'Moscow Olympiad']
---
# [OOI 2024] Evidence Board
## 题目描述

Volodya dreams of becoming a detective. Therefore, Volodya often reads books that tell incredible stories of solving crimes. Studying the next case, Volodya came across interesting details of the investigation.

There were a total of $n$ suspected persons in the case. The evidence board contains all $n$ persons. Initially, there were no connections between them.

During the investigation, new connections between suspected persons emerged one after another. Each connection linked two persons that previously had no connection with each other, even indirectly through several other persons.

Let's consider what happened when a connection between persons $A$ and $B$ emerged. In addition to the names of the persons, each connection had three parameters: $c_A$ --- the strength of the evidence against $A$, $c_B$ --- the strength of the evidence against $B$, and $w_{AB}$ --- the total strength of the evidence of connection. For natural reasons, the strength of the evidence of connection could not exceed the sum of strengths of the evidence against $A$ and $B$. That means that for each connection, it was $\textbf{necessarily}$ that $w_{AB} \leq c_A + c_B$. Upon receiving such connection, the detectives drew a line on the board between the images of persons $A$ and $B$, assigning the $w_{AB}$ to this line. Also, a sticker with the number $c_A$ was placed on the image of person $A$, and a sticker with the number $c_B$ was placed on $B$. If there were already other stickers on the image, the new sticker was placed on top of the old ones.

The case was solved exactly at the moment when all the suspected persons were linked through $n-1$ connections. After solving the crime, the board was placed in the museum in its original form.

Inspired by this approach, Volodya visited that museum and studied the evidence board in detail. Volodya noticed that the image of person $v$ contained stickers with numbers $c_{v,1}, \ldots, c_{v,deg_v}$ numbered $\textbf{from top to bottom}$. Here, $deg_v$ denotes the number of connections associated with person $v$. Also, Volodya remembered that the $i$-th connection was between persons $a_i$ and $b_i$ and had evidence strength $w_i$. Unfortunately the connections were arbitrarily numbered, and their numbers did not necessarily correspond to the order in which they appeared during the investigation.

Due to the confusion with the numbers of connections, the information on the board did not help to restore the process of the investigation. Now Volodya needs to restore any possible chronological order in which the connections could have emerged for the detectives. This task is too difficult for him, so he asks your help. It is also possible that the museum falsified information, and a suitable order does not exist.
## 输入格式

The first line of the input contains two integers $n$ and $g$ ($2 \le n \le 200\,000$, $0 \le g \le 9$) --- the number of suspected persons in the case and the test group number.

The next $n - 1$ lines describe the connections. The $i$-th line contains three integers $a_i$, $b_i$, and $w_i$ ($1 \le a_i, b_i \le n$, $1 \le w_i \le 10^9$, $a_i \neq b_i$) --- the persons connected by the $i$-th connection and the total strength of the $i$-th connection. It is guaranteed that connections link all persons together.

The next $n$ lines describe the numbers written on the stickers. The $i$-th line contains $deg_i$ integers $c_{i, 1}, \ldots, c_{i, deg_i}$ ($0 \le c_{i, j} \le 10^9$) --- the numbers written on the stickers on the image of the $i$-th person from top to bottom. $deg_i$ equals the number of connections associated with person $i$.
## 输出格式

If there is no suitable chronological order for the restoration of connections according to the conditions of the problem, output $\tt{No}$ (without quotes) on a single line.

Otherwise, on the first line output $\tt{Yes}$ (without quotes). On the second line, output $n - 1$ numbers --- a suitable chronological order of connections to emerge. The connections are numbered from $1$ to $n-1$ in the same order as they are given in the input. If there are multiple possible orders, output any of them.
## 样例

### 样例输入 #1
```
5 0
1 2 3
1 3 1
3 4 12
3 5 6
0 4
2
6 1 3
8
3
```
### 样例输出 #1
```
Yes
1 4 2 3
```
### 样例输入 #2
```
7 0
1 2 4
2 3 4
3 4 4
4 5 4
5 6 4
6 7 4
2
1 2
2 3
1 2
3 2
1 2
179
```
### 样例输出 #2
```
Yes
5 1 2 3 6 4
```
### 样例输入 #3
```
4 0
1 2 7
1 3 6
1 4 5
3 2 1
5
4
3
```
### 样例输出 #3
```
No
```
## 提示

### Note

In the first example, one of the possible orders is $[1, 4, 2, 3]$. In chronological order, the first connection links $A = 1$ and $B = 2$, $c_A = 4, c_B = 2, w_{AB} = 3$, $3 \leq 2 + 4$ --- the evidence is correct. The second connection links $A = 3$ and $B = 5$, $c_A = 3, c_B = 3, w_{AB} = 6$, $6 \leq 3 + 3$ --- the evidence is correct. The third connection links $A = 1$ and $B = 3$, $c_A = 0, c_B = 1, w_{AB} = 1$, $1 \leq 0 + 1$ --- the evidence is correct. The fourth connection links $A = 3$ and $B = 4$, $c_A = 6, c_B = 8, w_{AB} = 12$, $12 \leq 6 + 8$ -- the evidence is correct. For a better understanding, refer to the illustration.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/fyo2kfnk.png)
:::

### Scoring

The tests for this problem consist of nine groups. Points for each group are given only if all tests of the group and all tests of the required groups are passed. Please note that passing the example tests is not required for some groups. $\textbf{Offline-evaluation}$ means that the results of testing your solution on this group will only be available after the end of the competition.

| Group | Points | Additional constraints | < | Required Groups | Comment |
|:-----:|:------:|:----------------------:|:--:|:---------------:|:-------:|
|       |        | $n$ | $a_i, b_i, c_i, w_i$ | | |
| 0 | 0 | -- | -- | -- | Examples. |
| 1 | 10 | $n \le 10$ | -- | 0 | -- |
| 2 | 15 | -- | $a_i = i, b_i = i+1$ for all $i$ | -- | -- |
| 3 | 8 | -- | $a_i = 1, b_i = i+1$ for all $i$ | -- | -- |
| 4 | 9 | -- | $a_i \leq 2, b_i = i+1$ for all $i$ | 3 | -- |
| 5 | 7 | $n \le 1000$ | $c_{i,1} \leq c_{i,2} \leq \ldots \leq c_{i, deg_i}$ for all $i$ | -- | -- |
| 6 | 7 | $n \le 1000$ | $c_{i, j} = 0$ for all $1 \le i \le n$ and $j \geq 2$ | -- | -- |
| 7 | 17 | -- | $\displaystyle\sum_{v=1}^{n} \displaystyle\sum_{i=1}^{deg_v} c_{v,i} = \displaystyle\sum_{i=1}^{n-1} w_i$ | -- | -- |
| 8 | 16 | $n \le 1000$ | -- | 0, 1, 5, 6 | -- |
| 9 | 11 | -- | -- | 0 -- 8 | **Offline-evaluation** |



---

---
title: "[CERC 2021] Airline"
layout: "post"
diff: 提高+/省选-
pid: P13763
tag: ['2021', '树形 DP', '树的遍历', 'ICPC', 'CERC']
---
# [CERC 2021] Airline
## 题目描述

An airline company offers regular flights involving $n$ different airports. Each flight links two airports directly (i.e. without stopping at any other airport) and allows travel in both directions. The flights are arranged such that for any choice of starting airport $s$ and destination airport $t$, there exists exactly one sequence of flights between the two airports without visiting any airport more than once. The number of flights in this sequence is called the distance between $s$ and $t$.

Were the airline to add another flight, say between airports $x$ and $y$, it is possible that for some pairs $(s, t)$, another, shorter sequence of flights from $s$ to $t$ would form. The more pairs affected, the more promising the new connection between $x$ and $y$ is considered to be. The airline is asking you to help them evaluate several possible additions $(x, y)$ with respect to this criterion.
## 输入格式

An airline company offers regular flights involving $n$ different airports. Each flight links two airports directly (i.e. without stopping at any other airport) and allows travel in both directions. The flights are arranged such that for any choice of starting airport $s$ and destination airport $t$, there exists exactly one sequence of flights between the two airports without visiting any airport more than once. The number of flights in this sequence is called the distance between $s$ and $t$.

Were the airline to add another flight, say between airports $x$ and $y$, it is possible that for some pairs $(s, t)$, another, shorter sequence of flights from $s$ to $t$ would form. The more pairs affected, the more promising the new connection between $x$ and $y$ is considered to be. The airline is asking you to help them evaluate several possible additions $(x, y)$ with respect to this criterion.
## 输出格式

Output $q$ lines; in the $i$-th line, output the number of pairs $(s, t)$ such that $1 \leq s < t \leq n$ and the distance between airports $s$ and $t$ would decrease if the original network of $n - 1$ flights were supplemented by a direct flight connection between the airports $x_i$ and $y_i$.
## 样例

### 样例输入 #1
```
8 2
1 5
5 2
7 3
3 8
6 4
4 5
6 3
5 7
2 6
```
### 样例输出 #1
```
10
4
```
## 提示

### Input limits

* $2 \leq n \leq 10^6$
* $1 \leq q \leq 10^5$
* $1 \leq u_i \leq n; 1 \leq v_i \leq n; u_i \neq v_i$
* $1 \leq x_i \leq n; 1 \leq y_i \leq n; x_i \neq y_i$
* $\sum_{i=1}^{q} d_i \leq 10^7$, where $d_i$ is the distance between $x_i$ and $y_i$ in the original flight network.



---

---
title: "[USACO20FEB] Delegation G"
layout: "post"
diff: 提高+/省选-
pid: P6147
tag: ['2020', 'USACO', '数论', '树的遍历']
---
# [USACO20FEB] Delegation G
## 题目描述

Farmer John 有 $N$ 个牧场，这些牧场通过 $N-1$ 条道路连接，形成了一个树形结构。

但在 28 年的经营后（译者注：USACO 创办于 1992 年），FJ 觉得处理树上问题非常辣手，他认为一条链上的问题更加简单。

因此他决定将整棵树划分为若干条链，将每一条链的管理权授予一位工人。为了避免可能的争端，他希望所有链的长度均相同。

FJ 现在想知道，对于每一个满足 $1 \leq K \leq N-1$ 的 $K$，是否存在一种划分方案，使得整棵树被划分成若干条链，且每条链的长度都**恰好**是 $K$。
## 输入格式

第一行一个整数 $N$（$1 \leq N \leq 10^5$）。

接下来 $N-1$ 行，每行两个整数 $u,v$（$1 \leq u,v \leq N$），描述一条连接 $u,v$ 的道路。
## 输出格式

输出一个长度 $N-1$ 的 0/1 串。第 $i$ 位的值为 $1$ 当且仅当存在一种划分方案，使得整棵树被划分成若干条链，且每条链的长度都恰好是 $i$，否则第 $i$ 位的值为 $0$。
## 样例

### 样例输入 #1
```
13
1 2
2 3
2 4
4 5
2 6
6 7
6 8
8 9
9 10
8 11
11 12
12 13
```
### 样例输出 #1
```
111000000000
```
## 提示

### 样例解释

$K=1,2,3$ 时都存在一种合法的划分方案。

$K=3$ 时的一种划分方案如下：

$13-12-11-8, 10-9-8-6, 7-6-2-3, 5-4-2-1$

### 子任务

- 测试点 $2 \sim 4$ 满足**最多**有一个点的度数大于 $2$。
- 测试点 $5 \sim 8$ 满足 $N \leq 10^3$。
- 测试点 $9 \sim 15$ 没有特殊限制。


---

---
title: "[NAPC-#1] Stage5 - Conveyors"
layout: "post"
diff: 提高+/省选-
pid: P9433
tag: ['O2优化', '树的遍历', '最近公共祖先 LCA']
---
# [NAPC-#1] Stage5 - Conveyors
## 题目背景

>![](https://cdn.luogu.com.cn/upload/image_hosting/4wcng8qe.png)
>
>— rs8
## 题目描述

### 【简要题意】

给定一棵 $n$ 个节点的无根树以及树上的 $k$ 个关键节点，边有边权（即边的长度）。$q$ 次询问，每次给出 $s,t$，问从 $s$ 到 $t$ 且经过至少一次**每个**关键节点的路径的最短长度。

### 【原始题意】

在某一面 kid 又遇到了往返跑关卡。Really popular apparently.

关卡给 kid 留下的空间形状是一棵无向带权树，边权即边的长度。这棵树有 $n$ 个节点，其中有 $k$ 个点上各**恰**有一个发光小球，kid 经过有小球的点（称为关键点）时就可以收集小球。kid 从 $s$ 点出发，当他收集到全部 $k$ 个小球时，传送门就会在 $t$ 点出现。

想速通的 kid 想知道他从 $s$ 点出发收集到全部 $k$ 个小球并进入位于 $t$ 点的传送门所需要走的最小时间（其实也就是路径长度，因为 kid 的速度恒定）。

但是 Geezer 很狡猾，塔内这一面被复制成了 $q$ 层，每层的 $s$ 和 $t$ 还可能有变动。kid 慌了，忙找到你求助。
## 输入格式

第一行三个正整数 $n, q, k$，表示树的节点个数，询问次数和关键节点个数。

接下来 $n-1$ 行，每行三个正整数 $u, v, w$，表示树中存在边 $(u, v)$，边权为 $w$。保证输入构成一棵树。

接下来一行 $k$ 个两两不同的正整数，表示关键节点的编号。

接下来 $q$ 行，每行两个正整数 $s, t$，表示一次询问。
## 输出格式

对于每次询问输出一行一个非负整数，表示此次询问的最短合法路径长度。

注意，合法路径可以不经过任何边，此时路径长为 $0$。
## 样例

### 样例输入 #1
```
7 5 2
1 2 3
1 3 5
3 4 2
3 5 4
2 6 1
1 7 1
2 3
2 3
2 1
7 1
4 5
6 6
```
### 样例输出 #1
```
8
13
17
22
18
```
## 提示

### 【数据范围】

**本题采用捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c|c}
\textbf{Subtask} & \text{测试点编号} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1&1\sim14 & n\leqslant15,\mathbf R& 18 \r
\textsf2&15\sim20 & q=1 & 18 \r
\textsf3&46\sim48 & s=t,k=n & 6 \r
\textsf4&21\sim25 & k=n & 18 \r
\textsf5&26\sim30 & \mathbf A & 18 \r
\textsf6&31\sim45 & - & 22 \r
\end{array}
$$
友情提醒：$\text{Subtask }\textsf1$ 并没有限制 $q$ 的范围。

- 特殊性质 $\mathbf R$：保证树随机生成（对于 $i\ge2$，在 $[1,i)$ 内随机选择一个点和 $i$ 连边，边权在一固定区间内均匀随机生成）。
- 特殊性质 $\mathbf A$：定义 $f(x)$ 表示存在 $i,j\in[1,n]$（可能 $i=j$） 且 $i,j$ 均为关键点，使得 $x$ 在 $i$ 到 $j$ 的最短路径上；那么对每次询问保证 $f(s)$ 和 $f(t)$ 均成立。

对于 $100\%$ 的数据，$1\leqslant n\leqslant 10^5$，$1\leqslant q\leqslant 10^5$，$1\leqslant k\leqslant n$，$1\leqslant w\leqslant 10^4$，$1\leqslant u,v,s,t\leqslant n$。

### 【样例解释 #1】
![](https://cdn.luogu.com.cn/upload/image_hosting/3hvr33bz.png)

图中加粗节点表示关键点。

对于每组询问，以下为一种最优路径（最优路径可能有多条）：
1. $2\to1\to3$。
2. $2\to1\to3\to1$。
3. $7\to1\to2\to1\to3\to1$。
4. $4\to3\to1\to2\to1\to3\to5$。
5. $6\to2\to1\to3\to1\to2\to6$。


---

