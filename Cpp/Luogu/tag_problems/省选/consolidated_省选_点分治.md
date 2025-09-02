---
title: "『SpOI - R1』Lamborghini (Demo)"
layout: "post"
diff: 省选/NOI-
pid: P10795
tag: ['点分治', '树上启发式合并', 'Kruskal 重构树', 'O2优化', '线段树合并']
---
# 『SpOI - R1』Lamborghini (Demo)
## 题目描述

给你一棵无根树，每个点 $i$ 有两个属性 $t_i,v_i$。

定义有向路径 $i\to j$ 的 $f_{i,j}$ 为：

- 若 $i\to j$ 上 $t_x$ 最小的点为 $x$ 且 $v_j\leq v_x\leq v_i$，则 $f_{i,j}=x$。
- 否则，$f_{i,j}=0$。

求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n f_{i,j}$。
## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个以空格分隔的整数，第 $i$ 项表示点 $i$ 的 $t_i$。

第三行 $n$ 个以空格分隔的整数，第 $i$ 项表示点 $i$ 的 $v_i$。

接下来 $n-1$ 行，每行两个整数 $a,b$，表示一条树边 $a\leftrightarrow b$。
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3
1 2 3
1 3 5
1 2
2 3
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
5
1 3 5 8 10
1 5 3 2 8
2 1
3 1
4 1
5 3
```
### 样例输出 #2
```
22
```
## 提示

#### 样例 #1 解释

- $f(1,1)=1$。
- $f(1,2)=0$。
- $f(1,3)=0$。
- $f(2,1)=1$。
- $f(2,2)=2$。
- $f(2,3)=0$。
- $f(3,1)=1$。
- $f(3,2)=2$。
- $f(3,3)=3$。

故 $\sum\limits_{i=1}^3\sum\limits_{j=1}^3 f(i,j)=10$。

### 数据范围

**本题开启子任务捆绑与子任务依赖。**

对于 $100\%$ 的数据，$t$ 互不相同，$1\leq n\leq 10^5$，$1\leq t_i,v_i\leq 10^9$。

| Subtask | $n\leq$ | $t_i,v_i\leq$ | 特殊性质 | 得分 | 子任务依赖 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 1 | $300$ | $10^5$ | 无 | $15$ | 无 |
| 2 | $5000$ | $10^5$ | 无 | $15$ | 1 |
| 3 | $10^5$ | $10^9$ | $A$ | $15$ | 无 |
| 4 | $10^5$ | $10^9$ | $B$ | $15$ | 无 |
| 5 | $10^5$ | $10^9$ | 无 | $40$ | 1,2,3,4 |

特殊性质 $A$：**钦定 $1$ 号节点为树的根**，对于任意点对 $(x,y)$ 且 $x\neq y$，若 $x$ 是 $y$ 的祖先，则 $t_x<t_y$。

特殊性质 $B$：$\forall i\in[1,n),a_i=i,b_i=i+1$。


---

---
title: "[COTS 2023] 三元图 Graf"
layout: "post"
diff: 省选/NOI-
pid: P10829
tag: ['点分治', '2023', 'O2优化', 'COCI（克罗地亚）', '圆方树']
---
# [COTS 2023] 三元图 Graf
## 题目背景

译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D1T1。$\texttt{2s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）
## 题目描述


对于非负整数 $k$，我们递归地给出 $k-{}$三元图的定义。

- $k-{}$三元图是无向图。
- 对于 $k=0$，$k-{}$三元图 是一个仅包含 $1$ 个节点和 $0$ 条边的图。
- 对于 $k\gt 0$，$k-{}$三元图由三个 $(k-1)-{}$三元图组合而成。具体地说，在这三个 $(k-1)-{}$三元图中各选择一个节点，然后在这三个节点之间两两连边，得到的就是 $k-{}$三元图。

下图展示了一张 $3-{}$三元图。

![](https://cdn.luogu.com.cn/upload/image_hosting/fyidau35.png)


给定无向图 $G$，判断它是否是 $k-{}$三元图。


## 输入格式


第一行，两个正整数，$N,M$，表示 $G$ 的点数和边数。

接下来 $M$ 行，每行两个正整数 $u,v$，表示 $G$ 中的一条边 $(u,v)$。
## 输出格式


如果 $G$ 是 $k-{}$三元图，输出 $\texttt{da}$（克罗地亚语「是」）；否则输出 $\texttt{ne}$（克罗地亚语「否」）。
## 样例

### 样例输入 #1
```
3 3
1 2
2 3
3 1
```
### 样例输出 #1
```
da
```
### 样例输入 #2
```
9 12
1 2
2 3
3 1
3 4
4 5
3 5
5 6
6 7
7 5
7 8
9 8
7 9
```
### 样例输出 #2
```
ne
```
### 样例输入 #3
```
9 12
1 2
2 3
3 1
4 5
5 6
6 4
7 8
8 9
9 7
1 7
7 4
4 1
```
### 样例输出 #3
```
da
```
## 提示


#### 样例解释

样例 $3$ 解释：这是一张 $2-{}$三元图。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le N\le 200\, 000$，$0\le M\le 300\, 000$；
- $1\le u,v\le N$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $15$  | $N \leq 10$，$M\le 20$   |
| $2$  | $20$  | $N \leq 1000$，$M\le 2000$  |
| $3$  | $15$  | 满足特殊性质 |
| $4$  | $50$  | 无额外约束 |

特殊性质：若 $G$ 是 $k-{}$三元图，保证每一步选择的 $3$ 个节点在之前已经被选中过。换句话说，总是选中「中间的节点」。



---

---
title: "[KTSC 2024 R2] 病毒"
layout: "post"
diff: 省选/NOI-
pid: P11241
tag: ['点分治', '2024', '交互题', 'KOI（韩国）']
---
# [KTSC 2024 R2] 病毒
## 题目背景

**请用 C++14 或 C++17 提交本题**

你需要在代码开头加入如下代码：

```cpp
#include<vector>
std::vector<long long> find_spread(int N, int M, std::vector<int> A, std::vector<int> B, std::vector<int> P, std::vector<int> D, std::vector<int> C);
```
## 题目描述

**题目译自 [2024년도 국제정보올림피아드 대표학생 선발고사 - 2차 선발고사](https://www.ioikorea.kr/archives/ioitst/2024/)  T4 「[바이러스](https://assets.ioikorea.kr/ioitst/2024/2/virus/virus_statement.pdf)」**

由于上次新冠疫情的严重影响，KOI 城市决定为未来可能发生的疫情做好充分准备。为此，KOI 城市希望分析当前城市结构对病毒的脆弱程度。

KOI 城市由 $N$ 个地点和 $N-1$ 条双向道路组成，任意两个不同的地点都可以通过这些道路互相到达。也就是说，城市的道路网络是一个树结构。每个地点用 $0$ 到 $N-1$ 的不同整数表示。由于城市的道路网络是树结构，对于任意两个地点 $u$ 和 $v$，从 $u$ 到 $v$ 的唯一简单路径上的边数定义为 $u$ 和 $v$ 之间的距离。

KOI 城市有 $M$ 名居民。对于每个 $j$ $(0 \leq j \leq M-1)$，第 $j$ 个人住在 $P[j]$ 号地点，并且可以到达距离 $P[j]$ 不超过 $D[j]$ 的地点。

KOI 城市的病毒学家们建立了一个模型来模拟病毒在两个人之间的传播过程。对于每个 $0 \leq v \leq N-1$，第 $v$ 号地点的传播时间用一个正整数 $C[v]$ 表示。假设第 $j$ 个人在时间 $t$ 首次感染病毒，并且第 $k$ 个人从第 $j$ 个人那里接收到病毒。如果存在一个地点 $w$，使得 $w$ 号地点与 $P[j]$ 号地点的距离不超过 $D[j]$，且 $w$ 号地点与 $P[k]$ 号地点的距离不超过 $D[k]$，那么 $w$ 号地点就是传播的媒介。

如果没有这样的传播媒介，第 $k$ 个人不会直接从第 $j$ 个人那里感染病毒（当然，他可能通过其他人间接感染）。如果存在传播媒介，那么在所有可能的传播媒介中，选择传播时间最短的地点 $x$。如果第 $k$ 个人在时间 $t+C[x]$ 之前没有感染病毒，那么他将在时间 $t+C[x]$ 被第 $j$ 个人感染。病毒以这种方式在所有不同的两个人之间传播。

在上述模型下，KOI 城市的研究人员希望计算当第 $0$ 个人在时间 $0$ 感染病毒时，其他人何时感染病毒。你需要计算对于每个 $0 \leq j \leq M-1$，第 $j$ 个人首次感染病毒的时间。如果第 $j$ 个人没有感染病毒，则记录为 $-1$。

你需要实现以下函数：

```cpp
std::vector<long long> find_spread(int N, int M, std::vector<int> A, std::vector<int> B, std::vector<int> P, std::vector<int> D, std::vector<int> C);
```

- `N`：KOI 城市的地点数量。
- `M`：KOI 城市的居民数量。
- `A, B`：长度为 $N-1$ 的数组。对于每个 $i$ $(0 \leq i \leq N-2)$，存在一条连接 $A[i]$ 和 $B[i]$ 的道路。每条道路在两个数组中只出现一次。
- `P, D`：长度为 $M$ 的数组。对于每个 $j$ $(0 \leq j \leq M-1)$，第 $j$ 个人住在 $P[j]$ 号地点，并且可以到达距离 $P[j]$ 不超过 $D[j]$ 的地点。
- `C`：长度为 $N$ 的数组。对于每个 $v$ $(0 \leq v \leq N-1)$，第 $v$ 号地点的传播时间为 $C[v]$。
- 该函数返回一个长度为 $M$ 的数组 $T$。对于每个 $j$ $(0 \leq j \leq M-1)$，如果第 $j$ 个人感染病毒，$T[j]$ 表示他首次感染病毒的时间；如果没有感染，则为 $-1$。
- 该函数在每个测试用例中只会被调用一次。

## 输入格式

示例评测程序按以下格式读取输入：

- 第 $1$ 行：$N\,M$
- 第 $2+i$ $(0 \leq i \leq N-2)$ 行：$A[i]\,B[i]$
- 第 $1+N+j$ $(0 \leq j \leq M-1)$ 行：$P[j]\,D[j]$
- 第 $1+N+M$ 行：$C[0]\,C[1]\,\ldots\,C[N-1]$
## 输出格式

示例评测程序按以下格式输出：

- 第 $1+j$ $(0 \leq j \leq M-1)$ 行：函数 `find_spread` 返回的数组的第 $j$ 个元素
## 提示

对于所有输入数据，满足：

- $1 \leq N \leq 10^5$
- $1 \leq M \leq 10^5$
- 对于所有 $i$ $(0 \leq i \leq N-2)$，$0 \leq A[i], B[i] \leq N-1, A[i] \neq B[i]$
- 对于所有 $j$ $(0 \leq j \leq M-1)$，$0 \leq P[j], D[j] \leq N-1$
- 对于所有 $v$ $(0 \leq v \leq N-1)$，$1 \leq C[v] \leq 10^{9}$

详细子任务附加限制及分值如下表所示。

| 子任务 | 分值 | 附加限制 |
| :-: | :-: | :-: |
| $1$ | $5$ | $N \leq 500, M \leq 500$；<br>对于所有 $i$ $(0 \leq i \leq N-2)$，$A[i]=i, B[i]=i+1$ |
| $2$ | $8$ | $N \leq 5000, M \leq 5000$；<br>对于所有 $i$ $(0 \leq i \leq N-2)$，$A[i]=i, B[i]=i+1$ |
| $3$ | $27$ | 对于所有 $i$ $(0 \leq i \leq N-2)$，$A[i]=i, B[i]=i+1$ |
| $4$ | $5$ | $N \leq 500, M \leq 500$ |
| $5$ | $8$ | $N \leq 5000, M \leq 5000$ |
| $6$ | $47$ | 无附加限制 |


---

---
title: "[集训队互测 2024] 串联"
layout: "post"
diff: 省选/NOI-
pid: P12491
tag: ['点分治', '集训队互测', '2024']
---
# [集训队互测 2024] 串联
## 题目描述

给定一棵树，每个点有两个权值 $a_i,b_i$。对于树上的一条简单路径，若这条路径上 $b$ 之和乘上 $a$ 的最小值大于等于一个常数 $V$，那么这条路径被称作一条好的路径。

即：对于一条简单路径，设 $p_1,p_2,\dots,p_k$ 为路径上的点。这条简单路径是好的，当且仅当 $\min_{i=1}^k a_{p_i} \times \sum_{i=1}^k b_{p_i}\ge V$。

求所有好的路径中，$\sum b$ 的最小值。
## 输入格式

第一行两个整数 $n,V$。

接下来 $n$ 行每行两个整数 $a_i,b_i$。

接下来 $n−1$ 行每行两个整数 $x_i,y_i$，表示一条树边。
## 输出格式

一行一个整数表示答案。
## 样例

### 样例输入 #1
```
10 100
4 8
7 6
4 6
5 5
4 4
7 4
5 4
8 8
5 5
6 4
1 8
1 2
2 3
2 6
10 9
4 1
4 9
5 7
5 4
```
### 样例输出 #1
```
25
```
## 提示

### 子任务

对于所有测试点均满足 $1\leq V\leq 10^{18},1\leq a_i,b_i\leq 10^9$。数据保证有解。

| Subtask |    $n\leq$    |           特殊性质           | 分值 |
| :-----: | :-----------: | :--------------------------: | :--: |
|   $1$   | $2\times10^3$ |             $/$              | $15$ |
|   $2$   |    $10^4$     |             $/$              | $15$ |
|   $3$   | $2\times10^5$ |    存在一个点度数为 $n-1$    | $15$ |
|   $4$   | $2\times10^5$ | 第 $i$ 条边连接 $i$ 和 $i+1$ | $15$ |
|   $5$   | $5\times10^4$ |             $/$              | $20$ |
|   $6$   | $2\times10^5$ |             $/$              | $20$ |


---

---
title: "[KOI 2024 Round 2] 分数竞赛"
layout: "post"
diff: 省选/NOI-
pid: P12653
tag: ['点分治', '2024', 'KOI（韩国）']
---
# [KOI 2024 Round 2] 分数竞赛
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

KOI 公园由编号从 $1$ 到 $N$ 的 $N$ 个地点组成，地点之间通过 $N-1$ 条道路相连。第 $i$ 条道路连接 $U_i$ 号地点和 $V_i$ 号地点，具有权值 $W_i$（$1 \le i \le N-1$）。

KOI 公园中的任意两个地点都可以通过这些道路相互到达，也就是说，这是一棵树结构。

KOI 公园即将举行一场分数竞赛，其规则如下：

- 总共有 $N - 1$ 名选手，每人从起点出发，沿着一条简单路径（即不重复经过任何地点）前往除起点以外的一个不同终点。
- 每名选手起始分数为 0。
- 每经过一条道路，选手便会获得该道路的分数（可以是负数）。
- 选手可以在任意时刻将当前分数归零，包括到达终点之后。

最大化某位选手最终得分的一个策略是：**每当当前得分为负时，立刻将其归零**。我们称这种策略为**最优策略**。所有选手都会采用此策略。

对于每一个起点 $i$（$1 \le i \le N$），设在 $i$ 为起点时，所有选手在遵循最优策略后最终得分的总和为 $S_i$，所有选手将分数归零的总次数为 $C_i$。

例如，考虑下图所示的 KOI 公园结构，当 $1$ 号地点为起点时：

![](https://cdn.luogu.com.cn/upload/image_hosting/wsiwv8mw.png)

- 前往 $2$ 号地点的选手经过 $-1$ 分的道路，到达后归零，最终得分为 0。
- 前往 $3$ 号地点的选手经过 $+2$ 分的道路，最终得分为 2。
- 前往 $4$ 号地点的选手先经过 $-1$ 分到达 $2$ 号，再归零，然后经过 $+2$ 分到达 $4$，最终得分为 2。
- 前往 $5$ 号地点的选手先经过 $+2$ 分到达 $3$ 号，再经过 $-3$ 分到达 $5$，在 $5$ 号归零，最终得分为 0。
- 前往 $6$ 号地点的选手先经过 $+2$ 分到达 $3$ 号，再经过 $-1$ 分到达 $6$，最终得分为 1。

因此，$S_1 = 5$，$C_1 = 3$。

请编写程序，计算每个起点 $i$ 的 $S_i$ 和 $C_i$。
## 输入格式

第一行输入一个整数 $N$。  
接下来的 $N-1$ 行中，第 $i$ 行输入三个整数 $U_i\ V_i\ W_i$，表示第 $i$ 条道路的两端节点及其权值。
## 输出格式

若只计算 $S_1, \ldots, S_N$：

- 第一行输出整数 0。
- 第二行输出 $S_1\ S_2\ \ldots\ S_N$，以空格分隔。

若同时计算 $S_1, \ldots, S_N$ 和 $C_1, \ldots, C_N$：

- 第一行输出整数 1。
- 第二行输出 $S_1\ S_2\ \ldots\ S_N$，以空格分隔。
- 第三行输出 $C_1\ C_2\ \ldots\ C_N$，以空格分隔。
## 样例

### 样例输入 #1
```
6
1 2 -1
1 3 2
2 4 2
3 5 -3
3 6 -1
```
### 样例输出 #1
```
1
5 5 6 8 6 6
3 5 2 0 6 6
```
### 样例输入 #2
```
10
5 10 5
4 7 5
1 6 1
8 9 5
9 4 1
6 7 0
5 1 0
2 9 3
4 3 3
```
### 样例输出 #2
```
1
51 75 71 47 51 47 47 91 51 91
0 0 0 0 0 0 0 0 0 0
```
### 样例输入 #3
```
10
8 1 -2
10 5 -2
10 6 1
3 8 3
10 8 3
4 6 4
9 8 -5
9 7 5
6 2 -4
```
### 样例输出 #3
```
1
24 23 40 48 21 23 24 24 24 21
11 12 2 0 12 4 1 3 9 4
```
## 提示

**约束条件**

- 所有输入值均为整数。
- $2 \le N \le 300\,000$
- $1 \le U_i, V_i \le N \quad (1 \le i \le N - 1)$
- $-10^7 \le W_i \le 10^7 \quad (1 \le i \le N - 1)$

**子任务**

1. （2 分）$N \le 1\,000$  
2. （6 分）$0 \le W_i \le 5$  
3. （20 分）$0 \le W_i \le 5$ 或 $W_i \le -1\,000\,000$  
4. （4 分）$U_i = 1,\ V_i = i+1$  
5. （10 分）$U_i = i,\ V_i = i+1$  
6. （16 分）$U_i = \left\lfloor \frac{i+1}{2} \right\rfloor,\ V_i = i+1$  
7. （18 分）与三条及以上道路直接相连的地点最多有两个  
8. （24 分）无额外约束

~~若仅计算 $S_1, \ldots, S_N$，可获得该子任务一半的分数。详细请参考输出格式说明。  
**若计算了 $S_1, \ldots, S_N$ 和 $C_1, \ldots, C_N$，但 $C$ 值不准确，即使 $S$ 正确，也无法得分。**~~

在洛谷上需要正确输出正确的 $S_1, \ldots, S_N$ 和 $C_1, \ldots, C_N$ 才可以获得分数。

翻译由 ChatGPT-4o 完成


---

---
title: "[KOI 2021 Round 2] 美食推荐"
layout: "post"
diff: 省选/NOI-
pid: P12730
tag: ['动态规划 DP', '倍增', '点分治', '2021', 'KOI（韩国）']
---
# [KOI 2021 Round 2] 美食推荐
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

KOI 国有 $N$ 个城市。每个城市编号从 1 到 $N$。

KOI 国的结构很特别，把城市看作图的顶点、道路看作无向边，则这个国家的结构可以表示为一个包含 $N$ 个顶点的**树**。树是一个无环的连通图。

KOI 国共有 $M$ 家美食餐厅，每家餐厅编号从 1 到 $M$。某些城市可能没有餐厅，也可能有两个以上的餐厅，请特别注意这一点。

第 $i$ 家餐厅（$1 \leq i \leq M$）位于城市 $c_i$，配送范围为距离不超过 $d_i$ 的城市，且其客户偏好度为 $g_i$。

第 $i$ 家餐厅可以向从城市 $c_i$ 出发，经过至多 $d_i$ 条道路所能到达的所有城市配送。即，第 $i$ 家餐厅的配送范围为：

$$
R_i = \{ j \mid d(c_i, j) \leq d_i \}
$$

其中，$d(a, b)$ 表示从城市 $a$ 到城市 $b$ 之间的最短路径长度（即需要经过的最少道路数）。

你是一名外卖推荐平台的运营者。为了避免服务重叠，你希望从 $M$ 家餐厅中选出一个子集 $S$，满足以下条件：

- 对于任意城市 $p$，它不能同时被 $S$ 中的两个或多个餐厅包含在其配送范围内。也就是说，对于 $S$ 中任意不同的两家餐厅 $i$ 和 $j$，都有 $R_i \cap R_j = \emptyset$。

请从所有满足上述条件的子集 $S$ 中，选出客户偏好度总和最大的一个，并输出该最大值。

## 输入格式

第一行包含两个整数 $N$ 和 $M$，中间用一个空格分隔。

接下来的 $N-1$ 行中，每行包含两个整数 $a$ 和 $b$，表示城市 $a$ 和城市 $b$ 之间有一条道路相连。

接下来的 $M$ 行中，每行包含三个整数 $c_i$、$d_i$ 和 $g_i$，表示第 $i$ 家餐厅所在城市、配送距离上限与客户偏好度。

## 输出格式

输出一个整数，表示满足条件的餐厅集合中客户偏好度之和的最大值。

## 样例

### 样例输入 #1
```
8 5
1 2
2 3
3 4
4 5
5 6
4 7
4 8
3 2 40
6 0 5
8 0 5
2 1 16
5 1 32
```
### 样例输出 #1
```
53
```
## 提示

**约束条件**

- 所有输入数据均为整数。
- $1 \leq N \leq 10^5$
- $1 \leq M \leq 10^5$
- 对于所有 $i$（$1 \leq i \leq M$），满足 $0 \leq d_i \leq N - 1$，$1 \leq g_i \leq 10^9$

**子任务**

1. （9 分）对于 $1 \leq i \leq N - 1$，城市 $i$ 与城市 $i+1$ 之间有一条道路相连。
2. （11 分）$N, M \leq 20$
3. （17 分）$N, M \leq 2\,000$
4. （10 分）$N \leq 2\,000$
5. （8 分）对于 $2 \leq i \leq N$，城市 $\lfloor i/2 \rfloor$ 与城市 $i$ 之间有一条道路相连。
6. （12 分）图中度数大于等于 3 的顶点最多只有一个。
7. （33 分）无额外约束条件。


---

---
title: "[CERC 2022] Bandits"
layout: "post"
diff: 省选/NOI-
pid: P13805
tag: ['点分治', '2022', 'ICPC', 'CERC']
---
# [CERC 2022] Bandits
## 题目描述

There is a kingdom with $N$ villages and $N - 1$ bidirectional roads that allow the citizens to travel between any pair of villages following a path consisting of one or more roads. The $i$-th road connects villages $A_i$ and $B_i$ and has length $C_i$.

The king has noticed an increasing number of complaints about bandits attacking the merchants travelling along the roads in the kingdom. He has tasked his advisor with solving this problem by hiring loyal groups of thugs that will act as security agencies. Each such security contract guarantees security of all roads in a radius of $R_j$ from the village $X_j$ with the group’s headquarters. A road is protected by the contract if it is part of a path of length at most $R_j$ from $X_j$ to some other village. Some roads may be protected by several contracts and are therefore more secure.

Write a program that will process queries about new contracts and answer queries about the security of individual roads, that is the number of contracts currently securing that road.
## 输入格式

The first line contains the number of villages $N$. The roads connecting these villages are described in the following $N - 1$ lines. The description of each road consists of space-separated integers $A_i$, $B_i$ and $C_i$, which represent a road of length $C_i$ between villages $A_i$ and $B_i$. The villages are numbered from 1 to $N$.

Next line contains the number of queries $Q$. The following $Q$ lines describe the queries. The query that represents a new security contract starts with character '+' and is followed by the headquarters village $X_j$ and security radius $R_j$. The query about the security of some road starts with character '?' and is followed by the number $Y_j$ of that road. The roads are numbered from 1 to $N - 1$ in order in which they are given in the input.
## 输出格式

Process the queries in the given order and for every query of type '?' output one line with the current number of contracts securing the road $Y_j$.
## 样例

### 样例输入 #1
```
7
1 2 4
4 2 7
5 1 3
3 6 4
1 6 9
2 7 1
7
+ 2 6
? 3
? 1
+ 6 14
? 1
? 2
? 3
```
### 样例输出 #1
```
0
1
2
0
1
```
## 提示

### Input limits

* $1 \leq N, Q \leq 10^5$
* $0 \leq C_i, R_j \leq 10^9$


---

---
title: "[ZJOI2007] 捉迷藏"
layout: "post"
diff: 省选/NOI-
pid: P2056
tag: ['2007', '各省省选', '点分治', '浙江']
---
# [ZJOI2007] 捉迷藏
## 题目描述

Jiajia 和 Wind 是一对恩爱的夫妻，并且他们有很多孩子。某天，Jiajia、Wind 和孩子们决定在家里玩捉迷藏游戏。他们的家很大且构造很奇特，由 $N$ 个屋子和 $N-1$ 条双向走廊组成，这 $N-1$ 条走廊的分布使得任意两个屋子都互相可达。 


游戏是这样进行的，孩子们负责躲藏，Jiajia 负责找，而 Wind 负责操纵这 $N$ 个屋子的灯。在起初的时候，所有的灯都没有被打开。每一次，孩子们只会躲藏在没有开灯的房间中，但是为了增加刺激性，孩子们会要求打开某个房间的电灯或者关闭某个房间的电灯。为了评估某一次游戏的复杂性，Jiajia 希望知道可能的最远的两个孩子的距离（即最远的两个关灯房间的距离）。 

我们将以如下形式定义每一种操作： 

- C(hange) i 改变第 $i$ 个房间的照明状态，若原来打开，则关闭；若原来关闭，则打开。 
- G(ame) 开始一次游戏，查询最远的两个关灯房间的距离。
## 输入格式

第一行包含一个整数 $N$，表示房间的个数，房间将被编号为 $1,2,3…N$ 的整数。

接下来 $N-1$ 行每行两个整数 $a$, $b$，表示房间 $a$ 与房间 $b$ 之间有一条走廊相连。

接下来一行包含一个整数 $Q$，表示操作次数。接着 $Q$ 行，每行一个操作，如上文所示。
## 输出格式

对于每一个操作 Game，输出一个非负整数，表示最远的两个关灯房间的距离。若只有一个房间是关着灯的，输出 `0`；若所有房间的灯都开着，输出 `-1`。
## 样例

### 样例输入 #1
```
8
1 2
2 3
3 4
3 5
3 6
6 7
6 8
7
G
C 1
G
C 2
G
C 1
G
```
### 样例输出 #1
```
4
3
3
4
```
## 提示

对于$20\%$的数据， $N \leq 50$, $M\leq 100$； 

对于$60\%$的数据， $N \leq 3000$, $M \leq 10000$； 

对于$100\%$的数据， $N \leq 100000$, $M \leq 500000$。 



---

---
title: "树上游戏"
layout: "post"
diff: 省选/NOI-
pid: P2664
tag: ['点分治']
---
# 树上游戏
## 题目描述

lrb 有一棵树，树的每个节点有个颜色。给一个长度为 $n$ 的颜色序列，定义 $s(i,j)$ 为 $i$ 到 $j$ 的颜色数量。以及

$$sum_i=\sum_{j=1}^n s(i, j)$$

现在他想让你求出所有的 $sum_i$。

## 输入格式

第一行为一个整数 $n$，表示树节点的数量。


第二行为 $n$ 个整数，分别表示 $n$ 个节点的颜色 $c_1,c_2\ldots c_n$。


接下来 $n-1$ 行，每行为两个整数 $x,y$，表示 $x$ 和 $y$ 之间有一条边。
## 输出格式

输出 $n$ 行，第 $i$ 行为 $sum_i$。

## 样例

### 样例输入 #1
```
5
1 2 3 2 3
1 2
2 3
2 4
1 5
```
### 样例输出 #1
```
10
9
11
9
12
```
## 提示

$$sum_1=s(1,1)+s(1,2)+s(1,3)+s(1,4)+s(1,5)=1+2+3+2+2=10$$
$$sum_2=s(2,1)+s(2,2)+s(2,3)+s(2,4)+s(2,5)=2+1+2+1+3=9$$
$$sum_3=s(3,1)+s(3,2)+s(3,3)+s(3,4)+s(3,5)=3+2+1+2+3=11$$
$$sum_4=s(4,1)+s(4,2)+s(4,3)+s(4,4)+s(4,5)=2+1+2+1+3=9$$
$$sum_5=s(5,1)+s(5,2)+s(5,3)+s(5,4)+s(5,5)=2+3+3+3+1=12$$


对于 $40\%$ 的数据，$n\leq 2000$。

对于 $100\%$ 的数据，$1\leq n,c_i\leq 10^5$。



---

---
title: "[USACO12NOV] Balanced Trees G"
layout: "post"
diff: 省选/NOI-
pid: P3060
tag: ['2012', 'USACO', '点分治']
---
# [USACO12NOV] Balanced Trees G
## 题目描述

Fascinated by his experience with balanced parentheses so far, Farmer John is curious if you can help him solve one final problem.  As it turns out, FJ's farm is in the shape of a giant tree of N pastures (1 <= N <= 40,000), each of which he has labeled with either ( or ).  For example:

'('--'('--')'--'('--')' 

|         |

')'       ')'--'('--'(' 

|              |

')'            '('--')'--')'--')'--'(' 

Recall that since his farm is a tree, this means that certain pairs of pastures are connected by corridors so that there is one unique path between any given pair of pastures.  FJ believes that some of these paths represent balanced strings of parentheses.  In particular, he would like to know, among all such balanced strings represented by paths through the tree, what is the maximum nesting depth one can find.  The nesting depth of a balanced string of parentheses is the maximum, over all prefixes of the string, of the excess number of ('s within the prefix.  For example, the string ()()() has nesting depth 1, but the string ((()))() has nesting depth 3, as we can see clearly if we count excess ('s for every prefix of the string: 

((()))() 

12321010

For the example farm above, the deepest string is ((())) with a depth of 3, and can be obtained by taking the path from A to B below:

```cpp
'('--'('--')'--'('--')' 
|         | 
')'       ')'--'('--'(' < A 
|              | 
')'            '('--')'--')'--')'--'(' 
^C                            ^B 
```
Note that this is different than the longest balanced string; for instance (())(()), starting at A and ending at C, has length 8.

Your task is to output the nesting depth of the deepest balanced path in the tree.

给出一棵树，每个结点上有一个括号。问在所有括号平衡的路径中，最大嵌套层数为多少。

## 输入格式

\* Line 1: A single integer N, the number of nodes in the tree.

\* Lines 2..N: Line i+1: A single integer p\_(i+1) (1 <= p\_(i+1) <= i), denoting an edge between nodes i+1 and p\_{i+1} in the tree.

\* Lines N+1..2N: Line N+i: Either ( or ), the label of node i.

## 输出格式

\* Line 1: A single integer, giving the maximum nesting depth of a balanced path.

## 样例

### 样例输入 #1
```
15 
1 
2 
1 
4 
4 
6 
7 
5 
9 
9 
11 
12 
13 
14 
( 
) 
) 
( 
) 
) 
( 
) 
( 
( 
( 
) 
) 
) 
( 

```
### 样例输出 #1
```
3 

```
## 提示

This is the example from the problem description, with the following node labels:

1'('--4'('--6')'--7'('--8')' 

|     |

2')'  5')'--9'('--10'(' 

|           |

3')'       11'('--12')'--13')'--14')'--15'(' 




---

---
title: "[ZJOI2015] 幻想乡战略游戏"
layout: "post"
diff: 省选/NOI-
pid: P3345
tag: ['2015', '线段树', '点分治', '浙江']
---
# [ZJOI2015] 幻想乡战略游戏
## 题目背景

## 警告，滥用本题者将被封号。
## 题目描述

傲娇少女幽香正在玩一个非常有趣的战略类游戏，本来这个游戏的地图其实还不算太大，幽香还能管得过来，但是不知道为什么现在的网游厂商把游戏的地图越做越大，以至于幽香一眼根本看不过来，更别说和别人打仗了。

在打仗之前，幽香现在面临一个非常基本的管理问题需要解决。

整个地图是一个树结构，一共有 $n$ 块空地，这些空地被 $n-1$ 条带权边连接起来，使得每两个点之间有一条唯一的路径将它们连接起来。

在游戏中，幽香可能在空地上增加或者减少一些军队。同时，幽香可以在一个空地上放置一个补给站。如果补给站在点 $u$ 上，并且空地 $v$ 上有 $d_v$ 个单位的军队，那么幽香每天就要花费 $d_v \times \text{dist}(u,v)$ 的金钱来补给这些军队。由于幽香需要补给所有的军队，因此幽香总共就要花费为 $\sum (d_v \times \text{dist}(u,v))$（其中 $1 \leq v \leq N$）的代价，$\text{dist}(u,v)$ 表示 $u$ 和 $v$ 在树上的距离（唯一路径的权和）。

因为游戏的规定，幽香只能选择一个空地作为补给站。在游戏的过程中，幽香可能会在某些空地上制造一些军队，也可能会减少某些空地上的军队，进行了这样的操作以后，出于经济上的考虑，幽香往往可以移动他的补给站从而省一些钱。但是由于这个游戏的地图是在太大了，幽香无法轻易的进行最优的安排，你能帮帮她吗？

你可以假定一开始所有空地上都没有军队。
## 输入格式

第一行两个数 $n$ 和 $Q$ 分别表示树的点数和幽香操作的个数，其中点从 $1$ 到 $n$ 标号。

接下来 $n-1$ 行，每行三个正整数 $a,b,c$，表示 $a$ 和 $b$ 之间有一条边权为 $c$ 的边。

接下来 $Q$ 行，每行两个数 $u,e$，表示幽香在点 $u$ 上放了 $e$ 单位个军队（如果 $e<0$，就相当于是幽香在 $u$ 上减少了 $|e|$ 单位个军队，说白了就是 $d_u←d_u+e$）。

数据保证任何时刻每个点上的军队数量都是非负的。
## 输出格式

对于幽香的每个操作，输出操作完成以后，每天的最小花费，也即如果幽香选择最优的补给点进行补给时的花费。

## 样例

### 样例输入 #1
```
10 5
1 2 1
2 3 1
2 4 1
1 5 1
2 6 1
2 7 1
5 8 1
7 9 1
1 10 1
3 1
2 1
8 1
3 1
4 1
```
### 样例输出 #1
```
0
1
4
5
6
```
## 提示

对于所有数据，$1\le c\le 10^3$，$0\le |e| \le 10^3$，$1\le n\le10^5$，$ 1\le Q\le10^5$ 。

非常神奇的是，对于所有数据，这棵树上的点的度数都不超过 $20$。


---

---
title: "小清新数据结构题"
layout: "post"
diff: 省选/NOI-
pid: P3676
tag: ['点分治', '洛谷原创', 'O2优化', '树链剖分', '动态树 LCT', '洛谷月赛']
---
# 小清新数据结构题
## 题目背景

**本题时限2s，内存限制256M**

## 题目描述

在很久很久以前，有一棵n个点的树，每个点有一个点权。

现在有q次操作，每次操作是修改一个点的点权或指定一个点，询问以这个点为根时每棵子树点权和的平方和。

（题目不是很好懂，没看太懂的可以看看样例解释）

## 输入格式

第一行两个整数n、q。

接下来n-1行每行两个整数a和b，表示树中a与b之间有一条边，保证给出的边不会重复。

接下来一行n个整数，第i个整数表示第i个点的点权。

接下来q行每行两或三个数，如果第一个数为1，那么接下来有两个数x和y，表示将第x个点的点权修改为y，如果第一个数为2，那么接下来有一个数x，表示询问以x为根时每棵子树点权和的平方和。

## 输出格式

对于每个询问输出答案。

## 样例

### 样例输入 #1
```
4 5
1 2
2 3
2 4
4 3 2 1
2 2
1 1 3
2 3
1 2 4
2 4
```
### 样例输出 #1
```
121
140
194
```
## 提示

##### 样例解释

这是一个菊花图，2与1、3、4间有边。

一开始每个点点权分别为4、3、2、1。

第一个询问以2为根，1、3、4子树中都只有本身一个点，2子树中有所有点，那么1、3、4子树中的点权和就分别是自己的点权4、2、1，2子树中的点权和就是4+3+2+1=10，$4^2+2^2+1^1+10^2=121$。

接下来将第一个点点权修改为3，每个点点权分别为3、3、2、1。

第二个询问以3为根，1、4子树中只有自己，2子树中有1、2、4，3子树中有所有点，1、4子树点权和就是自己的点权3、1，2子树点权和就是3+3+1=7，3子树点权和为3+3+2+1=9，$3^2+1^2+7^2+9^2=140$。

接下来把第二个点点权修改为4，每个点点权分别为3、4、2、1。

第三个询问以4为根，1、3子树点权和就是3和2，2子树点权和就是3+4+2=9，4子树点权和为3+4+2+1=10，$3^2+2^2+9^2+10^2=194$。

##### 数据范围

对于10%的数据，$n,q \leq 2000$。

对于40%的数据，$n,q \leq 60000$。

对于另外30%的数据，保证每次询问的根都为1。

对于100%的数据，$1 \leq n,q \leq 200000$，$-10 \leq$输入的每个点权$\leq 10$。

建议使用输入优化~~，虽然标程没加读入优化也能过~~



---

---
title: "[BJOI2017] 树的难题"
layout: "post"
diff: 省选/NOI-
pid: P3714
tag: ['2017', '各省省选', '点分治', '单调队列', '分治', '深度优先搜索 DFS']
---
# [BJOI2017] 树的难题
## 题目描述

给你一棵 $n$ 个点的无根树。

树上的每条边具有颜色。一共有 $m$ 种颜色，编号为 $1$ 到 $m$，第 $i$ 种颜色的权值为 $c_i$。

对于一条树上的简单路径，路径上经过的所有边按顺序组成一个颜色序列，序列可以划分成若干个相同颜色段。定义路径权值为颜色序列上每个同颜色段的颜色权值之和。

请你计算，经过边数在 $l$ 到 $r$ 之间的所有简单路径中，路径权值的最大值。
## 输入格式

第一行，四个整数 $n, m, l, r$。

第二行，$m$ 个整数 $c_1, c_2, \ldots, c_m$，由空格隔开，依次表示每个颜色的权值。

接下来 $n-1$ 行，每行三个整数 $u, v, c$，表示点 $u$ 和点 $v$ 之间有一条颜色为 $c$ 的边。
## 输出格式

输出一行，一个整数，表示答案。

## 样例

### 样例输入 #1
```
5 3 1 4
-1 -5 -2
1 2 1
1 3 1
2 4 2
2 5 3
```
### 样例输出 #1
```
-1
```
### 样例输入 #2
```
8 4 3 4
-7 9 6 1
1 2 1
1 3 2
1 4 1
2 5 1
5 6 2
3 7 1
3 8 3
```
### 样例输出 #2
```
11
```
## 提示

### 样例解释 1
颜色权值均为负，最优路径为 $(1, 2)$ 或 $(1, 3)$。

### 样例解释 2
最优路径为 $(3, 1, 2, 5, 6)$，其颜色序列为 $(2, 1, 1, 2)$。

### 数据范围
| 测试点编号 | $n$ | $m$ | 特殊限制 |
|-|-|-|-|
| $1$ | $=10^3$ | $\le n$ | 无特殊限制 |
| $2$ | $=10^4$ | $=2$ | 无特殊限制 |
| $3$ | $=10^5$ | $\le n$ | 所有点的度数不超过 $2$ |
| $4$ | $=2\times10^5$ | $\le n$ | 所有点的度数不超过 $2$ |
| $5$ | $=10^5$ | $=10$ | $l=1$，$r=n-1$ |
| $6$ | $=2\times10^5$ | $\le n$ | $l=1$，$r=n-1$ |
| $7$ | $=10^5$ | $=50$ | 无特殊限制 |
| $8$ | $=10^5$ | $\le n$ | 无特殊限制 |
| $9$ | $=2\times 10^5$ | $=100$ | 无特殊限制 |
| $10$ | $=2\times 10^5$ | $\le n$ | 无特殊限制 |

对于 $100\%$ 的数据，$1 \leq n, m \leq 2 \times 10^5$，$1 \leq l \leq r \leq n$，$\mid c_i \mid \leq 10^4$。保证树上至少存在一条经过边数在 $l$ 到 $r$ 之间的路径。


---

---
title: "曼哈顿计划E"
layout: "post"
diff: 省选/NOI-
pid: P3727
tag: ['点分治', '洛谷原创', '枚举', '分治', '深度优先搜索 DFS']
---
# 曼哈顿计划E
## 题目背景

1942 年 6 月，美国开始实施利用核裂变反应来研制原子弹的计划，亦称曼哈顿计划。后来两颗原子弹在广岛和长崎爆炸，世界见证了核武器的威力，并在它的威胁下颤抖不已。2200 年，dedsec 组织利用美国军方的网络安全漏洞渗入了美国的和武器系统，并密谋使用隐藏在曼哈顿的核武器储备毁灭世界。然而 dedsec 的一名成员 Badboy17 反对这一计划，她把这一计划告知了艾登。为了拯救他的家人，避免地球变为废土，艾登不得不再次发挥他的黑客能力拯救世界。

![](https://cdn.luogu.com.cn/upload/pic/5119.png)

## 题目描述

艾登尝试黑入 dedsec 的系统并取得控制权，然而 dedsec 有所反应并予以反击。

dedsec 的网络可以看做是一个 $n$ 个点 $n-1$ 条边的连通图（一棵树），每个节点有一个稳定值。

艾登可以选择网络中上的一条链，并对那一条链上的节点进行破解（把这一条链从树上拆下来）。

假设这一条链长度为 $m$，现在你会得到 $m$ 个节点。

然后艾登要和 dedsec 开始攻防战，双方轮流行动，每次可以从任意一个稳定值大于 $0$ 的节点里依照计算规则进行一些操作，操作后，稳定值不能小于 $0$，否则计算机会爆炸，最后不能进行操作的一方算作失败

由于 dedsec 占据了防守的地理优势，dedsec 先进行操作


艾登虽然精于黑客技术，但他的手机没电了。现在他把这个消息告诉了你，希望你帮他拯救世界，所以你需要写一个程序，来帮你判断是否存在一种方式，艾登可以取胜。当然，dedsec 的防守可能完美无缺，艾登根本无法取胜，你只好跑到 shelter 里去当试验品。

## 输入格式

输入包含多组测试数据，输入第一行包含一个整数 $T$，表示数据组数。

对于每组测试数据，第一行一个整数 $n$，表示有 $n$ 个点。

第二行至第 $n$ 行，每行两个整数 $u,v$，表示网络中有一条边连接 $u,v$。

第 $n+1$ 行 $n$ 个整数 $w$，第 $w_i$ 表示 $i$ 号节点的稳定值。

第 $n+2$ 行一个整数 $k$，描述操作的规则：

- 如果 $k=1$，你可以减少任意正整数的稳定值。
- 如果 $k=2$，接下来一行一个正整数 $s$，表示双方每次可以减少 $s$ 的非负整数幂的稳定值。
- 如果 $k=3$，接下来一行一个正整数 $s$，表示双方每次可以减少大于等于 $s$ 的稳定值。
- 如果 $k=4$，表示双方每次可以减少任意正整数的稳定值，或者把一个稳定值数量大于等于 $2$ 的节点分裂成两个，分开后的两个节点的稳定值之和等于原来的节点（比如 $7$ 分成 $3+4$）。
- 如果 $k=5$，双方都不能进行操作。

## 输出格式

对于每一组测试数据，输出一行：

如果存在一种方式，你可以获胜，输出 `Mutalisk ride face how to lose?`。

如果不存在一种方式可以取胜，输出 `The commentary cannot go on!`。

## 样例

### 样例输入 #1
```
1
3
1 2
2 3
1 2 3
1
```
### 样例输出 #1
```
Mutalisk ride face how to lose?
```
### 样例输入 #2
```
1
3
1 2
2 3
1 2 4
1
```
### 样例输出 #2
```
The commentary cannot go on!
```
## 提示

|测试点|$n\le$|$k$|$w_i\le$|
|:-:|:-:|:-:|:-:|
|$1$|$50$|$1$|$10^3$|
|$2$|$3\times 10^4$|$1$|$10^3$|
|$3$|$300$|$3$|$10^6$|
|$4$|$10^3$|$4$|$10^6$|
|$5$|$3\times 10^4$|$1$|$10^9$|
|$6$|$3\times 10^4$|$2$|$10^9$|
|$7$|$3\times 10^4$|$3$|$10^9$|
|$8$|$3\times 10^4$|$3$|$10^9$|
|$9$|$3\times 10^4$|$4$|$10^9$|
|$10$|$3\times 10^4$|$4$|$10^9$|

对于 $100\%$ 的数据，$T\le 5$。

保证输入均为正整数



---

---
title: "Qtree4"
layout: "post"
diff: 省选/NOI-
pid: P4115
tag: ['点分治', '堆', 'O2优化', '分治', '树链剖分']
---
# Qtree4
## 题目背景

#欢迎提供更强的数据，本题目支持无限加数据（可私信，百度网盘地址）

#数据范围和spoj略有不同

## 题目描述

给出一棵边带权的节点数量为n的树，初始树上所有节点都是白色。有两种操作：

C x，改变节点x的颜色，即白变黑，黑变白

A，询问树中最远的两个白色节点的距离，这两个白色节点可以重合(此时距离为0)。

## 输入格式

In the first line there is an integer N (N <= 100000)

In the next N-1 lines, the i-th line describes the i-th edge: a line with three integers a b c denotes an edge between a, b of value c (-1000 <= c <= 1000)

In the next line, there is an integer Q denotes the number of instructions (Q <= 200000)

In the next Q lines, each line contains an instruction "C a" or "A"

## 输出格式

For each "A" operation, write one integer representing its result. If there is no white node in the tree, you should write "They have disappeared.".

## 样例

### 样例输入 #1
```
3
1 2 1
1 3 1
7
A
C 1
A
C 2
A
C 3
A
```
### 样例输出 #1
```
2
2
0
They have disappeared.
```


---

---
title: "[IOI 2011] Race"
layout: "post"
diff: 省选/NOI-
pid: P4149
tag: ['2011', '点分治', '递归', 'IOI', 'O2优化', '分治']
---
# [IOI 2011] Race
## 题目描述

给一棵树，每条边有权。求一条简单路径，权值和等于 $k$，且边的数量最小。
## 输入格式

第一行包含两个整数 $n,k$，表示树的大小与要求找到的路径的边权和。

接下来 $n-1$ 行，每行三个整数 $u_i,v_i,w_i$，代表有一条连接 $u_i$ 与 $v_i$，边权为 $w_i$ 的无向边。

**注意：点从 $0$ 开始编号**。
## 输出格式

输出一个整数，表示最小边数量。

如果不存在这样的路径，输出 $-1$。
## 样例

### 样例输入 #1
```
4 3
0 1 1
1 2 2
1 3 4
```
### 样例输出 #1
```
2
```
## 提示

对于 $100\%$ 的数据，保证 $1\leq n\leq 2\times10^5$，$0\leq k,w_i\leq 10^6$，$0\leq u_i,v_i<n$。


---

---
title: "[USACO18JAN] Cow at Large P"
layout: "post"
diff: 省选/NOI-
pid: P4183
tag: ['2018', 'USACO', '点分治', '分治']
---
# [USACO18JAN] Cow at Large P
## 题目描述

Cornered at last, Bessie has gone to ground in a remote farm. The farm consists of $N$ barns ($2 \leq N \leq 7 \cdot 10^4$) and $N-1$ bidirectional tunnels between barns, so that there is a unique path between every pair of barns. Every barn which has only one tunnel is an exit. When morning comes, Bessie will surface at some barn and attempt to reach an exit.

But the moment Bessie surfaces at some barn, the law will be able to pinpoint her location. Some farmers will then start at various exit barns, and attempt to catch Bessie. The farmers move at the same speed as Bessie (so in each time step, each farmer can move from one barn to an adjacent barn). The farmers know where Bessie is at all times, and Bessie knows where the farmers are at all times. The farmers catch Bessie if at any instant a farmer is in the same barn as Bessie, or crossing the same tunnel as Bessie. Conversely, Bessie escapes if she reaches an exit barn strictly before any farmers catch her.


Bessie is unsure at which barn she should surface. For each of the $N$ barns, help Bessie determine the minimum number of farmers who would be needed to catch Bessie if she surfaced there, assuming that the farmers distribute themselves optimally among the exit barns.


Note that the time limit for this problem is slightly larger than the default: 4 seconds for C/C++/Pascal, and 8 seconds for Java/Python.

## 输入格式

The first line of the input contains $N$. Each of the following $N-1$ lines specify two integers, each in the range $1 \ldots N$, describing a tunnel between two barns.

## 输出格式

Please output $N$ lines, where the $i$th line of output tells the minimum number of farmers necessary to catch Bessie if she surfaced at the $i$th barn.

## 样例

### 样例输入 #1
```
7
1 2
1 3
3 4
3 5
4 6
5 7
```
### 样例输出 #1
```
3
1
3
3
3
1
1
```
## 题目翻译

### 题目描述

Bessie 被逼到了绝境，躲进了一个偏远的农场。这个农场由 $N$ 个谷仓（$2 \leq N \leq 7 \cdot 10^4$）和 $N-1$ 条双向隧道组成，因此每对谷仓之间都有一条唯一的路径。每个只有一个隧道的谷仓都是一个出口。当早晨来临时，Bessie 会从某个谷仓出现，并试图到达一个出口。

但是，当 Bessie 从某个谷仓出现时，执法人员会立即定位到她的位置。一些农民会从各个出口谷仓出发，试图抓住 Bessie。农民和 Bessie 的移动速度相同（因此在每个时间步中，每个农民可以从一个谷仓移动到相邻的谷仓）。农民们始终知道 Bessie 的位置，而 Bessie 也始终知道农民们的位置。如果农民和 Bessie 在同一谷仓或同时穿过同一条隧道，农民就会抓住 Bessie。相反，如果 Bessie 在农民抓住她之前严格地到达一个出口谷仓，她就能逃脱。

Bessie 不确定她应该从哪个谷仓出现。对于每个谷仓，请帮助 Bessie 确定如果她从该谷仓出现，假设农民们最优地分布在出口谷仓中，抓住她所需的最少农民数量。

请注意，本题的时间限制略高于默认值：C/C++/Pascal 为 4 秒，Java/Python 为 8 秒。

### 输入格式

输入的第一行包含 $N$。接下来的 $N-1$ 行每行包含两个整数，范围在 $1 \ldots N$ 之间，描述一条连接两个谷仓的隧道。

### 输出格式

请输出 $N$ 行，其中第 $i$ 行表示如果 Bessie 从第 $i$ 个谷仓出现，抓住她所需的最少农民数量。


---

---
title: "快递员"
layout: "post"
diff: 省选/NOI-
pid: P4886
tag: ['点分治', '递归', 'O2优化', '树链剖分', '洛谷月赛']
---
# 快递员
## 题目描述

Bob 的城市里有 $n$ 个邮递站，由于经济考虑，这些邮递站被 $n - 1$ 条带权无向边相连。即：这 $n$ 个邮递站构成了一棵树。

Bob 正在应聘一个快递员的工作，他需要送 $m$ 个商品，第 $i$ 个商品需要从 $u$ 送到 $v$。由于 Bob 不能带着商品走太长的路，所以对于一次送货，他需要先从快递中心到 $u$，再从 $u$ 回到快递中心，再从快递中心到 $v$，最后从 $v$ 返回快递中心。换句话说，如果设快递中心是 $c$ 号点，那么他的路径是 $c \rightarrow u \rightarrow c \rightarrow v \rightarrow c$。

现在 Bob 希望确定一个点作为快递中心，使得他送货所需的最长距离最小。显然，这个最长距离是个偶数，你只需要输出最长距离除以 $2$ 的结果即可。
## 输入格式

第一行输入两个数 $n, m$，意义如上。

接下来 $n-1$ 行，每行三个数 $u_i, v_i, w_i$，表示一条连接 $u_i, v_i$，长度为 $w_i$ 的边。

接下来 $m$ 行，每行两个整数 $u_i, v_i$，表示商品的起止位置。
## 输出格式

一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3 1
1 2 1
2 3 1
1 3

```
### 样例输出 #1
```
2
```
## 提示

对于 $25\%$ 的数据，满足 $1 \leq n, m \leq 1000$。

对于 $100\%$ 的数据，满足 $1 \leq n, m \leq 10^5, 1 \leq w_i \leq 1000$。


---

---
title: "Shopping"
layout: "post"
diff: 省选/NOI-
pid: P6326
tag: ['点分治', '单调队列', 'O2优化', '背包 DP']
---
# Shopping
## 题目描述

马上就是小苗的生日了，为了给小苗准备礼物，小葱兴冲冲地来到了商店街。商店街有 $n$ 个商店，并且它们之间的道路构成了一棵树的形状。

第 $i$ 个商店只卖第 $i$ 种物品，小苗对于这种物品的喜爱度是 $w_i$，物品的价格为 $c_i$，物品的库存是 $d_i$。但是商店街有一项奇怪的规定：如果在商店 $u,v$ 买了东西，并且有一个商店 $p$ 在 $u$ 到 $v$ 的路径上，那么必须要在商店 $p$ 买东西。小葱身上有 $m$ 元钱，他想要尽量让小苗开心，所以他希望最大化小苗对买到物品的喜爱度之和。

这种小问题对于小葱来说当然不在话下，但是他的身边没有电脑，于是他打电话给同为OI选手的你，你能帮帮他吗？


## 输入格式

输入第一行一个正整数 $T$ ，表示测试数据组数。

对于每组数据，

第一行两个正整数 $n,m$  。

第二行 $n$ 个非负整数 $w_1,w_2...w_n$ 。

第三行 $n$ 个正整数 $c_1,c_2...c_n$ 。

第四行 $n$ 个正整数 $d_1,d_2...d_n$ 。

接下来 $n-1$ 行每行两个正整数 $u,v$ 表示 $u$ 和 $v$之间有一条道路。
## 输出格式

输出共 $T$ 行，每行一个整数，表示最大的喜爱度之和。
## 样例

### 样例输入 #1
```
1
3 2
1 2 3
1 1 1
1 2 1
1 2
1 3
```
### 样例输出 #1
```
4
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1\leq n\le 500$，$1\le m\le 4000$，$1\le T \le 5$，$0\le w_i\le 4000$，$1 \leq c_i \leq m$，$1\le d_i\le 2000$。

#### 说明

题目来源：BZOJ4182。


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
title: "『JROI-1』 关系树"
layout: "post"
diff: 省选/NOI-
pid: P6589
tag: ['2020', '二分', '点分治', '平衡树', 'O2优化']
---
# 『JROI-1』 关系树
## 题目背景

小 L 有许多喜欢的游戏角色，他把这些游戏角色按照一定的关系联系起来。这些游戏角色和他们之间的关系构成了一棵树，小 L 把这棵树称之为「关系树」。
## 题目描述

关系树是由 $n$ 个点和 $n-1$ 条无向边组成的一棵树。

对于一张给定的图 $G$，定义图 $G$ 对于点集 $E$ 的 **顶点导出子图** 为点集 $E$ 和所有的 **两个端点都属于 $E$** 且属于原图 $G$ 的边组成的图。

定义一张图是 **整洁的**，当且仅当图中任意两点 $u,v$，$u$ 和 $v$ **不连通** 或 **距离不超过** $k$。

小 L 想要知道对于一组 $l,r(l \leq r)$，有多少对 $(a,b)$，满足 $l\leq a\leq b\leq r$，且所有序号在 $a$ 和 $b$ 之间（包括 $a,b$）的点组成的顶点导出子图是 **整洁的**。不仅如此，他还想问你所有的区间长度（即 $b-a+1$）之和。

因为小 L 喜欢问问题，所以你一共需要回答 $q$ 组询问。
## 输入格式

第一行有三个整数 $n$，$q$，$k$，意义如上。

接下来 $n-1$ 行，每行两个整数 $u$，$v$，描述一条边。

接下来 $q$ 行，每行两个整数 $l$，$r$，表示一组询问。
## 输出格式

$q$ 行，每行两个整数，依次为满足的 $(a,b)$ 组数和所有的区间长度之和。
## 样例

### 样例输入 #1
```
5 3 2
1 2
1 5
4 5
3 5
1 3
2 5
1 5
```
### 样例输出 #1
```
6 10
10 20
14 30
```
## 提示

#### 样例 1 解释

形成的关系树如图

![](https://cdn.luogu.com.cn/upload/image_hosting/zb12y5mq.png)

满足的 $(a,b)$ 有 $(1,1),(1,2),(1,3),(1,4),(2,2),(2,3),(2,4),(2,5),(3,3),(3,4),(3,5),(4,4),(4,5),(5,5)$。

三组询问的答案依次为 $6,10$，$10,20$，$14,30$。

--------------------------------

#### 数据规模与约定

**本题采用捆绑测试**。

+ Subtask 1 ( $10\%$ )：$n\leq 2000$。
+ Subtask 2 ( $30\%$ )：$n\leq 2\times 10^4$，形成的关系树为一条链。
+ Subtask 3 ( $60\%$ )：$n\leq 2\times 10^4$。
+ Subtask 4 ( 加强版数据，时限 $4.5s$ )：无特殊限制。

对于 $100\%$ 的测试点，保证 $1\leq n \leq 8\times 10^4$，$1\leq q \leq 10^5$，$0\leq k <n$，$1\leq u,v,l,r \leq n$。


---

---
title: "[省选联考 2020 B 卷] 消息传递"
layout: "post"
diff: 省选/NOI-
pid: P6626
tag: ['2020', '各省省选', '点分治']
---
# [省选联考 2020 B 卷] 消息传递
## 题目描述

给定一个包含 $n$ 个人（从 $1$ 到 $n$ 编号）的树形社交网络。如果一个人在某天收到了一条消息，则下一天他会将消息传递给所有与他有直接社交关系的人。

现在有 $m$ 次询问，每次询问假定第 $0$ 天 $x$ 号人收到了一条消息，请你计算第 $k$ 天时新收到此条消息的人数（即第 $k$ 天前收到过此条消息的人不计入其中）。不同询问间互不影响。
## 输入格式

**本题包含多组测试数据。**

第一行一个整数 $T$，为测试数据组数。

对于每组测试数据：

第一行两个数 $n,m$ 分别表示树形社交网络的人数和询问的数量。

接下来 $n - 1$ 行，每行两个数 $a, b$，表示 $a$ 号人和 $b$ 号人之间有直接社交关系。保证输入的是树形社交网络。

接下来 $m$ 行，每行两个数 $x, k$，意义见题目描述。

## 输出格式

对于每组测试数据：输出 $m$ 行，每行一个数表示询问的答案。

## 样例

### 样例输入 #1
```
1
4 2
1 2
2 3
3 4
1 1
2 2
```
### 样例输出 #1
```
1
1
```
## 提示

**样例解释**

第一个询问，第一天新收到消息的人只有 $2$ 号。
第二个询问，第一天新收到消息的人有 $1$、$3$ 号，第二天新收到消息的人有 $4$ 号。

**数据范围与约定**

对于测试点 $1$：$1\le n, m\le 10$。  
对于测试点 $2$：$1\le n, m\le 100$。  
对于测试点 $3$：$1\le n, m\le 1000$。  
对于测试点 $4\sim6$：$1\le n, m\le 10^5, k\le 20$。  
对于测试点 $7\sim10$：$1\le n, m\le 10^5$。  
对于所有测试点：$1\le T\le 5, 1\le x\le n, 0\le k < n$。


---

---
title: "[JOISC 2020] 首都"
layout: "post"
diff: 省选/NOI-
pid: P7215
tag: ['2020', '倍增', '点分治', 'JOI（日本）']
---
# [JOISC 2020] 首都
## 题目背景

JOI 国是一个庞大的国度。
## 题目描述

JOI 国拥有 $N$ 个城镇，编号为 $1$ 到 $N$，这些城镇由 $N-1$ 条双向道路连接。

JOI 国还拥有 $K$ 个城市，编号为 $1$ 到 $K$，第 $i$ 个城镇属于第 $C_i$ 个城市。

现在 JOI 国的总理 JOI 君 114514 世要挑选一个城市作为首都，从首都中的任一个城镇到达另一个首都中的城镇可以只经过首都中的城镇，但这明显是不合理的。

所以 JOI 君 114514 世要进行合并城市，合并城市 $x$ 和城市 $y$ 就会把城市 $y$ 里的所有小镇归为城市 $x$。

求能找到首都的最小合并次数。
## 输入格式

第一行两个整数 $N,K$ 代表城镇数和城市数。    
接下来 $N-1$ 行每行两个整数 $u,v$ 代表一条双向边。   
接下来 $N$ 行第 $i$ 行一个整数 $C_i$ 代表第 $i$ 个城镇属于第 $C_i$ 个城市。
## 输出格式

一行一个整数代表最小的合并次数。
## 样例

### 样例输入 #1
```
6 3
2 1
3 5
6 2
3 4
2 3
1
3
1
2
3
2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
8 4
4 1
1 3
3 6
6 7
7 2
2 5
5 8
2
4
3
1
1
2
3
4
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
12 4
7 9
1 3
4 6
2 4
10 12
1 2
2 10
11 1
2 8
5 3
6 7
3
1
1
2
4
3
3
2
2
3
4
4
```
### 样例输出 #3
```
2
```
## 提示

#### 样例 1 解释

可以将城市 $1$ 和 $3$ 合并，然后选择城市 $1$ 作为首都。

#### 子任务

|子任务|特殊性质|分数|
|:-:|:-:|:-:|
|$1$|$N \le 20$|$1$|
|$2$|$N \le 2000$|$10$|
|$3$|每个城镇最多与两个城镇相连|$30$|
|$4$|无|$59$|

对于 $100\%$ 的数据，$1 \le K,u,v \le N \le 2 \times 10^5$，保证从任何一个城镇出发都能到达其他城镇，$1 \le C_i \le K$。

#### 说明

翻译自 [第１９回日本情報オリンピック　春季トレーニング合宿](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/index.html) [Day4 A 首都](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/day4/capital_city.pdf)。


---

---
title: "[BalticOI 2021] Inside information (Day1)"
layout: "post"
diff: 省选/NOI-
pid: P8123
tag: ['点分治', '2021', 'BalticOI（波罗的海）']
---
# [BalticOI 2021] Inside information (Day1)
## 题目描述

有 $N$ 个服务器，第 $i$ 个服务器存储着第 $i$ 块数据，现在有若干种操作：

- `S a b` 第 $a$ 个服务器与第 $b$ 个服务器共享数据，即这两个服务器同时拥有这两个服务器本身拥有的数据块的和，并自动去重（可以理解为数据块之并）。
- `Q a d` 查询第 $a$ 个服务器是否拥有第 $d$ 块数据。
- `C a` 查询存储数据块 $a$ 的服务器数量。

S 操作有 $N-1$ 次，如果把共享看做连边，那么最后将形成以 $N$ 个服务器为点的一棵树；Q 操作和 C 操作一共有 $K$ 次。

求对于每个 Q 操作和 C 操作返回的结果。
## 输入格式

第一行两个整数 $N,K$ 代表服务器个数和操作个数。

接下来 $N+K-1$ 行每行代表一个操作。
## 输出格式

$K$ 行：

- 对于 Q 操作，输出 `yes` 或 `no` 代表是否拥有第 $d$ 块数据；
- 对于 C 操作，输出一个整数代表服务器数量。
## 样例

### 样例输入 #1
```
6 9
S 1 2
S 1 3
S 3 4
Q 5 1
S 4 5
S 1 6
Q 5 1
Q 1 5
C 1
C 2
C 3
C 4
C 5
C 6
```
### 样例输出 #1
```
no
yes
no
6
6
5
3
2
2
```
### 样例输入 #2
```
4 4
S 1 2
S 1 3
S 3 4
Q 2 1
Q 2 2
Q 2 3
Q 2 4
```
### 样例输出 #2
```
yes
yes
no
no
```
## 提示

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$N \le 4000$。
- Subtask 2（5 pts）：第 $1$ 个服务器与第 $2,3,\cdots,N$ 个服务器共享数据。
- Subtask 3（10 pts）：如果 $|A-B|=1$，那么第 $A$ 个服务器和第 $B$ 个服务器共享数据。
- Subtask 4（20 pts）：如果 $A<B$ 且 $2A=B$ 或 $2A+1=B$，那么第 $A$ 个服务器和第 $B$ 个服务器共享数据。
- Subtask 5（25 pts）：每个服务器最多与 $5$ 个服务器共享数据。
- Subtask 6（35 pts）：无特殊限制。

对于 $100\%$  的数据，$1 \le N,K \le 1.2 \times 10^5$。

#### 说明

翻译自 [BalticOI 2021 Day1 B Inside information](https://boi.cses.fi/files/boi2021_day1.pdf)。


---

---
title: "[YsOI2022] 淀粉树"
layout: "post"
diff: 省选/NOI-
pid: P8949
tag: ['点分治', '洛谷原创', 'Special Judge', '构造']
---
# [YsOI2022] 淀粉树
## 题目背景

Ysuperman 教大家淀粉质和淀粉树。
## 题目描述

Ysuperman 定义一棵**有根树** $S$ 是树 $T$ 的一棵淀粉树当且仅当 $S$ 满足如下两个条件（记 $s_i$ 表示 $S$ 中以 $i$ 为根的子树中所有点构成的点集）：

1. $S$ 与 $T$ 点数相同（不妨设为 $n$）且编号为 $1\sim n$。
1. 对于 $S$ 中任意一个有儿子的点 $i$，对于其任意一个儿子 $j$，满足在 $T$ 中 $i$ 与 $s_j$ 中至少一个点有直接连边。

容易发现一棵树 $T$ 的淀粉树可能有很多棵。

Ysuperman 现在给定 $n$ 以及两棵点编号 $1\sim n$ 的树 $T$ 和树 $S$，设树 $S$ 中度数最大的点的度数为 $d$，TA 需要你进行至少一次且不超过 $d$ 次操作，每次操作把 $T$ 替换成它的任意一棵淀粉树，使得最终 $T$ 变成 $S$。

请注意，这里给定的 $S$ 是没有给定根的，你只需要满足最后 $T$ 的连边情况和 $S$ 相同我们就认为 $T$ 变成了 $S$。

输入保证存在至少一组解。
## 输入格式

第一行两个数 $n,d$，保证 $d$ 等于 $S$ 中度数最大的点的度数。

接下来 $n-1$ 行每行两个数 $u,v$ 表示 $T$ 中 $u,v$ 有连边。保证形成一棵树。

接下来 $n-1$ 行每行两个数 $u,v$ 表示 $S$ 中 $u,v$ 有连边。保证形成一棵树。
## 输出格式

为了方便检验，Ysuperman 需要你按照有根树的形式输出答案。

答案第一行一个正整数 $k(1\le k\le d)$ 表示你进行的操作数。

接下来 $k$ 行第 $i$ 行 $n$ 个整数表示你进行第 $i$ 次操作后 $T$ 变成的有根树中 $1\sim n$ 各个点的父亲编号，根的父亲编号规定为 $0$，**请保证你输出树的根是淀粉树的根**。
## 样例

### 样例输入 #1
```
5 3
1 2
1 3
3 4
3 5
3 2
3 4
3 5
1 2
```
### 样例输出 #1
```
1
2 3 0 3 3
```
## 提示

#### 样例 1 解释

这是 $T$：

![](https://cdn.luogu.com.cn/upload/image_hosting/5qlv4q4t.png)

这是 $S$：

![](https://cdn.luogu.com.cn/upload/image_hosting/xoyaon7y.png)

该输出仅对 $T$ 进行了一次操作，即将 $T$ 变成了下面这棵有根树：

![](https://cdn.luogu.com.cn/upload/image_hosting/0kozi468.png)

这棵有根树是 $T$ 的一棵淀粉树，理由如下：

1. 对于 $2$ 的儿子 $1$，在 $T$ 中 $2$ 与 $s_1=\{1\}$ 中的 $1$ 有直接连边。
2. 对于 $3$ 的儿子 $2$，在 $T$ 中 $3$ 与 $s_2=\{1,2\}$ 中的 $1$ 有直接连边。
3. 对于 $3$ 的儿子 $4$，在 $T$ 中 $3$ 与 $s_4=\{4\}$ 中的 $4$ 有直接连边。
4. 对于 $3$ 的儿子 $5$，在 $T$ 中 $3$ 与 $s_5=\{5\}$ 中的 $5$ 有直接连边。

最终得到的有根树和 $S$ 的连边情况相同，所以这份输出将被判定为正确。

#### 数据范围

子任务 $1$（$20$ 分），满足 $n\le 6$。

子任务 $2$（$20$ 分），满足 $d=2$。

子任务 $3$（$20$ 分），满足 $T$ 可以只进行一次操作即可变成 $S$ 且 $n\le 447$。

子任务 $4$（$20$ 分），满足 $n\le 2000$。

子任务 $5$（$20$ 分），无特殊限制。

对于所有数据，满足 $2\le n\le 10^5$，$d\times n\le 2\times 10^5$。

#### 提示

附件下发了本题 checker。


---

