---
title: "[WC2024] 水镜"
layout: "post"
diff: 省选/NOI-
pid: P10144
tag: ['线段树', '2024', '离线处理', 'WC']
---
# [WC2024] 水镜
## 题目描述

**提示**：我们在题目描述的最后提供了一份简要的、形式化描述的题面。

A 城是一座多雨的城市，山溪泉水众多。出于对水的喜爱，市民们在城市中央修建了一座大喷泉。

喷泉的水池中有一排 $n$ 个石柱，从左到右编号为 $1, 2, \cdots , n$，第 $i$ 个石柱的高度为 $h_i$。水池中有储水，水位 $L$ 为一个**正实数**。第 $i$ 个石柱会产生一个高度为 $h'_i = 2L - h_i$ 的像。若石柱在水面上方，像在水面下方；若石柱在水面下方，像在水面上方；若石柱顶端与水面重合，则像也与水面重合。

传说水中栖息着泉水精灵，每到满月之夜，它们就会在石柱上起舞，行动规则如下：

- 泉水精灵只能栖息在石柱顶端，或者石柱的像的顶端。即如果泉水精灵在石柱 $u$ 上，它的高度 $r_u$ 便只有 $h_u, h'_u$ 两种可能取值。
- 泉水精灵每次只能前往右侧相邻的石柱（或石柱的像）。
- 在移动过程中，泉水精灵的高度必须**严格单调递增**。

泉水精灵会选择一个石柱（或石柱的像）为起点，进行若干次移动后停止。这样的过程称为一次**舞蹈**。

A 城的雨季漫长，由于不规律的降雨，喷泉的水位可能会多次变化，舞蹈路径的可能性也随之改变。作为远道而来的旅人，你很想知道有多少种舞蹈是可能实现的。具体地，你需要计算有多少对 $(u, v)$（$1 ≤ u < v ≤ n$），满足存在一种水位 $L$，使得泉水精灵在一次舞蹈中，能从第 $u$ 个石柱（或它的像）出发，到达第 $v$ 个石柱（或它的像）。

**形式化的**：给定一个长度为 $n$ 的正整数序列 $h_1, h_2,\cdots , h_n$，求满足以下所有条件的
二元组 $(u, v)$ 的数量：
- $1 \le u < v \le n$，且 $u, v$ 为整数；
- 存在一个**正实数** $L$ 以及一个长度为 $(v - u + 1)$ 的序列 $r_u, r_{u+1},\cdots , r_v$ 满足以下
所有条件：
- $\forall u \le i \le v$，记 $h'_i = 2L - h_i$，则 $r_i \in \{h_i,h'_i\}$，特别地，当 $h_i = h'_i$ 时，$r_i = h_i$；
- $\forall u \le i < v, r_i < r_{i+1}$。

## 输入格式

输入的第一行包含一个正整数 $n$，表示石柱的个数。

输入的第二行包含 $n$ 个正整数 $h_1, h_2, \cdots , h_n$，表示石柱的高度。

## 输出格式

输出一行一个整数，表示符合题目描述的 $(u, v)$ 对数。
## 样例

### 样例输入 #1
```
4
1 3 2 4
```
### 样例输出 #1
```
6
```
## 提示

**样例 1 解释**

所有 $\binom{4}{2}=6$ 种 $(u, v)$ 都是可行的。
对于 $u = 1, v = 4$，可以选择 $L = 2.5$，则序列 $h'$
 为 $\{4, 2, 3, 1\}$，取序列 $r$ 为 $\{1, 2, 3, 4\}$
可以满足所有条件。

### 数据范围

对于所有测试数据：

- $2\le n\le 5\times 10^5$，
- $\forall 1\le i\le n,1\le h_i\le 10^{12}$。

| 测试点编号 | $n\le$ |
| :----------: | :----------: |
| $1\sim 2$ | $10$ |
| $3\sim 4$ | $100$ |
| $5\sim 6$ | $400$ |
| $7\sim 11$| $4000$ |
| $12\sim 13$ | $5\times 10^4$ |
| $14\sim 16$ | $10^5$ |
| $17\sim 19$ | $2\times 10^5$ |
| $20\sim 25$ | $5\times 10^5$ |



---

---
title: "时空轮回"
layout: "post"
diff: 省选/NOI-
pid: P11471
tag: ['O2优化', '哈希 hashing', '离线处理']
---
# 时空轮回
## 题目描述

在时空中有 $n$ 个**时空节点**，有 $n-1$ 条时空通道将所有时空节点连接成一个连通块，每条时空通道连接着两个时空节点。

你初始在 $1$ 号时空节点，你每次可以选择一条时空通道来穿梭到另一个时空节点，由于时空穿梭的特殊性，每条时空通道至多通过一次。

每个时空节点有一个**风景**，第 $i$ 个时空节点的风景为 $a_i$。一段**风景序列**由若干个风景构成，一个长度为 $k$ 的风景序列为 $a_{i_1}a_{i_2}\dots a_{i_k}$。你可以通过若干次时空穿梭经过若干时空节点，这些时空节点按照经过顺序构成了一个风景序列，记这个风景序列为**重现的风景**。

定义一个风景序列 A 在风景序列 B 中的出现次数为：最多将风景序列 B 分为多少个连续且不相交的部分，使得风景序列 A 是每个部分的**子串**。

你有 $q$ 段**留恋的风景**，每段留恋的风景是一个风景序列，记第 $i$ 段留恋的风景为 $s_i$，其长度为 $m_i$，记 $s_i$ 中的第 $j$ 个风景为 $s_{i,j}$。对于每段留恋的风景，你都需要从 $1$ 号时空节点出发进行时空穿梭，得到重现的风景，你需要求出该留恋的风景在重现的风景中的出现次数的最大值。

注：

- 每段留恋的风景所对应的重现的风景相互独立。
- 原序列中任意个连续的数字组成的序列称为该序列的子串。
## 输入格式

**本题有多组数据**。

第一行一个正整数 $T$，表示数据组数。

对于每组数据：

第一行 $2$ 个正整数 $n,q$。

第二行 $n$ 个正整数，第 $i$ 个正整数表示 $a_i$。

接下来 $n-1$ 行每行两个正整数 $u,v$，表示 $u$ 和 $v$ 之间存在一条时空通道。

接下来 $q$ 行，每行先输入一个正整数 $m_i$，然后输入 $m_i$ 个正整数，表示 $s_i$。
## 输出格式

对于每组数据：

输出 $q$ 行，表示每段留恋的风景对应的答案。
## 样例

### 样例输入 #1
```
2
8 8
1 2 8 1 1 2 2 1
1 2
1 3
2 4
2 5
2 6
4 7
4 8
1 1
2 1 1
2 1 2
2 2 1
2 2 2
3 1 2 2
4 1 2 2 1
2 1 8
5 2
1 2 1 2 1
1 2
2 3
3 4
4 5
3 1 2 1
2 1 1
```
### 样例输出 #1
```
3
1
2
1
1
1
0
1
1
0

```
## 提示

$1\le T\le10^5$，$1\le n,q,m_i\le10^5$，$1\le a_i,s_{i,j},u,v\le n$，$\sum n,\sum q,\sum m_i\le10^5$。

**注意本题不寻常的时空限制**。


---

---
title: "[NOISG 2023 Finals] Curtains"
layout: "post"
diff: 省选/NOI-
pid: P11536
tag: ['线段树', '2023', '分治', 'NOISG（新加坡）', '离线处理']
---
# [NOISG 2023 Finals] Curtains
## 题目描述

兔子 Benson 正要在飞机上组织表演！

Benson 有 $n$ 个舞台，由 $1\sim n$ 编号。他有 $m$ 个幕布，由 $1\sim m$ 编号。

幕布可以下降——第 $i$ 个幕布下降后，它会遮挡住编号在 $[l_i,r_i]$ 内的舞台。

Benson 将组织 $q$ 次演出，由 $1\sim q$ 编号。第 $i$ 场演出需要使用编号在 $[s_j,e_j]$ 内的舞台。对于每场演出，Benson 想知道，是否能下降某些幕布，**恰好**遮住表演所需的舞台。

**形式化地**：给定 $m$ 个区间 $[l_i,r_i]$，每次询问给定区间 $[s_j,e_j]$，查询是否能选择一些区间，使它们的并恰好为 $[s_j,e_j]$。
## 输入格式

第一行三个正整数 $n,m,q$，用空格隔开。

接下来 $m$ 行，每行两个整数 $l_i,r_i$，表示幕布能遮挡的舞台区间。

接下来 $q$ 行，每行两个整数 $s_j,e_j$，表示表演所需的舞台区间。

## 输出格式

对于每组询问，输出一行 `YES` 或 `NO`，表示是否能下降某些幕布，使其恰好遮住表演所需的舞台。
## 样例

### 样例输入 #1
```
6 2 3
1 2
3 4
1 3
1 4
1 5

```
### 样例输出 #1
```
NO
YES
NO

```
### 样例输入 #2
```
10 10 10
6 9
6 7
1 6
10 10
5 9
3 9
2 10
5 7
9 10
5 10
7 8
4 7
1 6
2 7
3 9
7 7
2 9
4 9
6 6
5 7

```
### 样例输出 #2
```
NO
NO
YES
NO
YES
NO
NO
NO
NO
YES

```
## 提示

#### 数据范围

| Subtask | 分值 | 特殊限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $0$ | 样例 |
| $1$ | $3$ | $n,m,q\leq 200$ |
| $2$ | $6$ | $n,m,q\leq 2000$ |
| $3$ | $15$ | $n\leq 2000$ |
| $4$ | $20$ | $s_j=1$ |
| $5$ | $36$ | $n,m,q\leq 10^5$ |
| $6$ | $20$ | 无 |

对于 $100\%$ 的数据：

- $1\leq n,m,q\leq 5\times 10^5$
- $1\leq l_i\leq r_i\leq n$
- $1\leq s_j\leq e_j\leq n$

注：由于洛谷限制，数据不完全按照原题分配子任务。


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
title: "[LNOI2014] LCA"
layout: "post"
diff: 省选/NOI-
pid: P4211
tag: ['2014', '线段树', '各省省选', '辽宁', '最近公共祖先 LCA', '树链剖分', '差分', '离线处理']
---
# [LNOI2014] LCA
## 题目描述

给出一个 $n$ 个节点的有根树（编号为 $0$ 到 $n-1$，根节点为 $0$）。

一个点的深度定义为这个节点到根的距离 $+1$。 

设 $dep[i]$ 表示点 $i$ 的深度，$\operatorname{LCA}(i, j)$ 表示 $i$ 与 $j$ 的最近公共祖先。 

有 $m$ 次询问，每次询问给出 $l, r, z$，求 $\sum_{i=l}^r dep[\operatorname{LCA}(i,z)]$ 。
## 输入格式

第一行 $2$ 个整数，$n, m$。

接下来 $n-1$ 行，分别表示点 $1$ 到点 $n-1$ 的父节点编号。

接下来 $m$ 行，每行 $3$ 个整数，$l, r, z$。
## 输出格式

输出 $m$ 行，每行表示一个询问的答案。每个答案对 $201314$ 取模输出。
## 样例

### 样例输入 #1
```
5 2
0
0
1
1
1 4 3
1 4 2
```
### 样例输出 #1
```
8
5
```
## 提示

### 数据范围及约定

- 对于 $20\%$ 的数据，$n\le 10000,m\le 10000$；
- 对于 $40\%$ 的数据，$n\le 20000,m\le 20000$；
- 对于 $60\%$ 的数据，$n\le 30000,m\le 30000$；
- 对于 $80\%$ 的数据，$n\le 40000,m\le 40000$；
- 对于 $100\%$ 的数据，$1\le n\le 50000,1\le m\le 50000$。


---

