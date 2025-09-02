---
title: "BZOJ2162 男生女生"
layout: "post"
diff: 省选/NOI-
pid: P10598
tag: ['O2优化', '二分图', '容斥原理']
---
# BZOJ2162 男生女生
## 题目背景

题目来自原 BZOJ，我们承认题面及原数据的版权均属于原 BZOJ 或将题目授权给 BZOJ 使用的出题人。如果您是版权所有者且认为我们侵犯了您的权益，可联系我们。

---

雨荨的班主任安远老师是一个非常严厉的老师。到了大学，男生和女生之间难免会出现一些暧昧关系，但这样显然是影响学习的。所以作为艾利斯顿的一块招牌，安远老师当然要拒绝这种现象的出现以及繁衍。

所以每当安远老师发现一个男生和一个女生放学走在一起或者男女生之间互相传纸条等，他就会立马制止并且通知家长。他也要求所有男女生晚上八点之后必须关手机，并且不定期打电话检查。于是安远老师的学生都感慨：这货不是大学，不是大学。
## 题目描述

安远老师的学生里，一共有 $n$ 个男生和 $n$ 个女生，编号都以 $1\sim n$ 编号。有 $m$ 对男女生之间有暧昧关系。现在安远老师想找出这样一个男女生群体，每个男生都和每个女生之间有暧昧关系，并且男女生总数最大。注意，男生数目或者女生数目可以为 $0$。

如果有多个这样的群体，安远老师会选择男生最多的那个群体，因为他觉得男生会很不安分。如果这样的群体依然不唯一，他会选择任意一个。

接下来，安远老师从选出的这个群体的所有暧昧关系中，选出 $k$ 个进行调查，使得这个群体的所有男生和女生，都至少和其中的一对暧昧关系有关系（即是这个暧昧关系的男/女主人公）。安远老师想让你告诉他总方案数除以 $19921228$ 的余数是多少。
## 输入格式

输入的第一行包含两个正整数 $n$ 和 $k$，分别代表男生女生的个数，以及安远老师要选择的暧昧关系个数。

第二行为一个正整数 $m$，代表暧昧关系总个数。接下来 $m$ 行，每行两个整数，代表一对有暧昧关系的男女生编号。
## 输出格式

第一行有两个空格隔开的整数，代表选择的团体内男生和女生的个数。第二行有一个整数，代表选法除以 $19921228$ 的余数。
## 样例

### 样例输入 #1
```
3 2 
4
1 1
1 2
2 1
2 2
```
### 样例输出 #1
```
2 2
2
```
## 提示

对于所有数据，$1\leq n \leq 50$，$1\leq m,k \leq 2500$。同一对暧昧关系不会在输入中出现多次。


---

---
title: "异界之门"
layout: "post"
diff: 省选/NOI-
pid: P10610
tag: ['洛谷原创', 'Special Judge', 'O2优化', '二分图', '洛谷月赛']
---
# 异界之门
## 题目背景

跟随着线索，莲子来到了七夕坂。无暇欣赏此处的风景，高速运转着大脑的莲子，不断寻找异界的线索。翻转的地藏、奇异的裂缝、被隐匿的第五个季节……这个禁忌之中的世界，正向她揭晓着自己的秘密。

但莲子第一时间看到的只有梅莉，来不及思考，她一把抓住了梅莉的手——
## 题目描述

嗅觉敏锐的莲子察觉到，进入异界的方法一定和这些特别的地藏有所联系。她发现它们恰好构成了一棵形状特殊的树。

给定一棵 $n$ 个点的带点权的**有根**树，其根为 $1$，且点 $i$ 的点权为 $w_i$。**其满足对于任意两个深度相同的结点，它们的儿子数也相同**。

为了进入异界，莲子进行了一些操作来改变这棵树的点权：

1. 选择一条边，假设它连接了两点 $(u,v)$，设其中深度更高者为 $u$（即 $u$ 是 $v$ 的儿子），将 $w_u$ 加上 $w_v$。
2. 上述操作可以被执行任意多次，但是**不能重复选择同一条边**。

经过操作后，莲子求出了树的某个 [DFS 序列](https://oi-wiki.org/graph/dfs/)，并记录下了这个 DFS 序列所对应的点权序列 $c$（具体来说，$c_i$ 为 DFS 序过程中遍历到的第 $i$ 个点的点权）。

不幸的是，她突然忘记了她进行过哪些操作，也忘记了如何 DFS 这棵树，她希望你能还原出任意一组合法的操作方案与 DFS 序列。
## 输入格式

第一行一个整数 $n$。

对于接下来 $n$ 行：第 $i$ 行两个整数 $f_i,w_i$，其中 $f_i$ 代表点 $i$ 的父节点（特别的，$f_1=0$，对于其余节点有 $1\le f_i<i$），$w_i$ 代表点 $i$ 的权值。

接下来一行 $n$ 个整数描述序列 $c$，代表莲子的 DFS 序列所对应的点权序列 $c$。保证一定存在一种合法的操作方式和操作后的 DFS 方式得到序列 $c$。
## 输出格式

第一行一个整数 $m$，表示你进行的操作数。

接下来一行 $m$ 个数，第 $i$ 个数 $x_i$ 代表你在第 $i$ 次操作选择连接节点 $x_i$ 和其父节点 $f_{x_i}$ 的边进行操作。

接下来一行 $n$ 个数描述一个排列 $p$，其中 $p_i$ 代表你构造的 DFS 序列中遍历到的第 $i$ 个节点为点 $p_i$。
## 样例

### 样例输入 #1
```
4
0 1
1 2
2 3
3 4
1 3 5 9
```
### 样例输出 #1
```
3
3 4 2
1 2 3 4
```
### 样例输入 #2
```
5
0 1
1 -1
1 -1
2 3
3 4
1 0 3 0 3
```
### 样例输出 #2
```
3
2 5 3
1 2 4 3 5
```
### 样例输入 #3
```
4
0 1
1 2
1 3
1 4
1 4 3 3
```
### 样例输出 #3
```
1
2
1 4 2 3
```
### 样例输入 #4
```
5
0 1
1 1
1 1
2 1
3 1
1 2 2 2 3
```
### 样例输出 #4
```
4
2 4 5 3
1 3 5 2 4
```
## 提示

### 样例解释

#### 样例 \#1

![](https://cdn.luogu.com.cn/upload/image_hosting/ihq8vqnc.png)

其中一种可行的方案是依次操作边 $(2,3),(3,4),(1,2)$，操作后的树的点权序列为 $\{1,3,5,9\}$，选出的 DFS 序列为 $\{1,2,3,4\}$。

注意到该样例符合特殊性质 $\mathbf{A}$。

#### 样例 \#2

![](https://cdn.luogu.com.cn/upload/image_hosting/z14j0aeu.png)

其中一种可行的方案是依次操作边 $(1,2),(3,5),(1,3)$，操作后的树的点权序列为 $\{1,0,0,3,3\}$，选出的 DFS 序列为 $\{1,2,4,3,5\}$。
#### 样例 \#3

![](https://cdn.luogu.com.cn/upload/image_hosting/7livbzzu.png)

其中一种可行的方案是依次操作边 $(1,2)$，操作后的树的点权序列为 $\{1,3,3,4\}$，选出的 DFS 序列为 $\{1,4,2,3\}$。

注意到该样例符合特殊性质 $\mathbf{B}$。
#### 样例 \#4

![](https://cdn.luogu.com.cn/upload/image_hosting/9bopbeh3.png)

其中一种可行的方案是依次操作边 $(1,2),(2,4),(3,5),(1,3)$，操作后的树的点权序列为 $\{1,2,3,2,2\}$，选出的 DFS 序列为 $\{1,3,5,2,4\}$。

注意到该样例符合特殊性质 $\mathbf{C}$。

### 数据范围

**本题采用捆绑测试。**

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|}\hline
\textbf{Subtask} & \textbf{\textsf{分值}} & \bm{n\le } & \textbf{\textsf{特殊性质}}&\textbf{Subtask \textsf{依赖}}\cr\hline
1 & 10 & 6 & - &-\cr\hline
2 & 10 & 100 & \mathbf{A}&- \cr\hline
3 & 10 & 100 & \mathbf{B}&- \cr\hline
4 & 15 & 2\times 10^3 & \mathbf{C}&-  \cr\hline
5 & 15 & 2\times 10^3 & \mathbf{D}&-  \cr\hline
6 & 15 & 100 & -&1,2,3  \cr\hline
7 & 25 & 2\times 10^3 & -&1,2,3,4,5,6  \cr\hline
\end{array}
$$

特殊性质 $\mathbf{A}$：保证给出的树满足 $f_i=i-1$ ($i\ne 1$)。\
特殊性质 $\mathbf{B}$：保证给出的树满足 $f_i=1$ ($i\ne 1$)。\
特殊性质 $\mathbf{C}$：保证给出的树满足 $w_i=1$。\
特殊性质 $\mathbf{D}$：保证给出的树满足所有非叶节点儿子数不超过 $2$。

对于所有数据满足：$1\le n\le 2000$，$-10^8\le w_i\le 10^8$，$-10^{14}\le c_i\le 10^{14}$。


---

---
title: "[COTS 2024] 划分 Particija"
layout: "post"
diff: 省选/NOI-
pid: P10683
tag: ['2024', 'O2优化', '二分图', 'COCI（克罗地亚）']
---
# [COTS 2024] 划分 Particija
## 题目背景

译自 [Izborne Pripreme 2024 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2024/) D2T1。$\texttt{1s,512M}$。
## 题目描述



给定正整数 $ N $。

集合 $ \{1, 2, \ldots, N\} $ 的**划分**为由非空集合组成的集族，满足：
- $\forall 1\le i\le N$，$i$ 出现在**恰好一个**集合中。

例如，$\{\{1,3\},\{2,4\},\{5\}\}$ 是集合 $ \{1, 2, 3, 4, 5\} $ 的一个划分。

可以用数列 $ [x_1, x_2, \ldots, x_N ]$ 来表示划分。当且仅当 $ x_i = x_j $ 时，$ i $ 和 $ j $ 在同一个集合中。上面提到的划分 $\{\{1,3\},\{2,4\},\{5\}\}$ 可以由数列 $[1, 2, 1, 2, 3]$ 或者 $[5, 1, 5, 1, 4]$ 表示。

Patricija 拥有两个划分：第一个划分用数列 $ [a_1, a_2, \ldots, a_N] $ 表示，第二个划分用数列 $ [b_1, b_2, \ldots, b_N] $ 表示。

Patricija 想知道以下问题的答案：如果她使用这两个划分中的集合，来构造集合 $ \{1, 2, \ldots, N\} $ 的划分，至少需要多少个集合。


给定参数 $k\in \{0,1,2\}$，

- 当 $k=0$ 时，你需要回答原问题的答案。
- 当 $k=1$ 时，允许更改 $2N$ 个数字（$a_1,\cdots,a_N,b_1,\cdots,b_N$）中**至多**一个，**最小化**构造划分需要的最少集合数。
- 当 $k=2$ 时，允许更改 $2N$ 个数字（$a_1,\cdots,a_N,b_1,\cdots,b_N$）中**至多**一个，**最大化**构造划分需要的最少集合数。

请注意，你需要保证在你修改后，$\forall 1\le i\le N$，$1\le a_i,b_i\le N$。
## 输入格式


**本题单个测试点内有多组测试数据。**

第一行，两个整数 $T,k$，分别表示测试数据数量，以及参数。

接下来依次描述 $T$ 组测试数据：

对于每组测试数据，输入三行。

第一行，一个正整数 $N$，含义见题面；

第二行，$N$ 个正整数，依次表示 $a_1,a_2,\cdots,a_N$；

第三行，$N$ 个正整数，依次表示 $b_1,b_2,\cdots,b_N$。


## 输出格式


对于每组测试数据，输出一行一个整数，表示所求的答案。
## 样例

### 样例输入 #1
```
2 0
4 
1 1 2 3
1 2 3 3
7
1 1 1 1 2 3 4
1 2 3 4 4 4 4
```
### 样例输出 #1
```
2
4
```
### 样例输入 #2
```
3 1
4
1 1 2 3
1 2 3 3
4
1 1 1 1
1 2 3 3
7
1 1 1 1 2 3 4
1 2 3 4 4 4 4
```
### 样例输出 #2
```
2
1
2
```
### 样例输入 #3
```
3 2
4 
1 1 2 3
1 2 3 3
4
1 1 1 3
1 2 3 3
7
1 1 1 2 3 4 5
1 2 3 4 4 4 4
```
### 样例输出 #3
```
3
3
4
```
## 提示


#### 样例解释

样例 $1$ 解释：

对于第一组数据，第一个划分为 $\{\{1,2\},\{3\},\{4\}\}$，第二个划分为 $\{\{1\},\{2\},\{3,4\}\}$。选取 $\{1,2\},\{3,4\}$ 即可。

对于第二组数据，第一个划分为 $\{\{1,2,3,4\},\{5\},\{6\},\{7\}\}$，第二个划分为 $\{\{1\},\{2\},\{3\},\{4,5,6,7\}\}$。选取第一个划分或第二个划分即可。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le T\le 200\, 000$，$k\in \{0,1,2\}$；
- $1\le a_i,b_i\le N$；
- $1\le N,\sum N\le 200\, 000$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $7$  | $k=0,N\le 8,\sum 2^N\le 10^5$   |
| $2$  | $23$  | $k=0$  |
| $3$  | $15$  | $k=1,N\le 1\, 000,\sum N^2\le 10^6$ |
| $4$  | $16$  | $k=1$ |
| $5$  | $19$  | $k=2,N\le 1\, 000,\sum N^2\le 10^6$ |
| $6$  | $20$  | $k=2$ |




---

---
title: "运输规划"
layout: "post"
diff: 省选/NOI-
pid: P10919
tag: ['O2优化', '二分图', '树链剖分', '笛卡尔树']
---
# 运输规划
## 题目背景

你需要规划卡车的运输方案，为了让您更好地解决问题，**请仔细阅读题面。**
## 题目描述

有 $n$ 个城市，对于任意 $1 < i \leq n$ 满足第 $i$ 个城市与第 $i-1$ 个城市间有一条双向的道路，每个城市有一个对卡车高度的限制 $h_i$，代表只有高度小于等于 $h_i$ 的卡车可以从这个城市经过，现在有 $m$ 个城市 $S_{1},S_{2},...,S_{m}$ 各有**恰好**一个运输任务，任务要求**编号为 $i$ 且高度为 $h_{S_{i}}$ 的**卡车从城市 $S_{i}$ 出发**到达**任意一个有机场的城市，而有 $m$ 个城市有机场，分别为 $T_{1},T_{2},...,T_{m}$，对于一个合法的运输方案而言，需要保证每个卡车都到达一个机场且每个机场**恰好**有一辆卡车**抵达**。一个机场**可以**同时被多辆卡车**经过**。请注意，如果你无法经过某个城市，那么你也无法抵达这个城市。

记 $c_i$ 表示抵达位于城市 $T_i$ 的机场的的**卡车编号**，令数组 $F = \{c_1,c_2,...,c_m\}$，请你最小化 $F$ 的字典序并输出 $F$。

我们定义两个长度为 $len$ 的数组 $A,B$ 满足 $A$ 的字典序小于 $B$ 当且仅当存在 $0 \leq i < len$ 满足对于任意 $1 \leq j \leq i$ 满足 $A_j = B_j$ 且 $A_{i+1} < B_{i+1}$。

数据保证有解，保证**所有 $h_i$ 互不相同**，所有 $T_i$ 互不相同，所有 $S_i$ 互不相同。但是**可能会**存在 $i,j$ 满足 $S_i = T_j$。

## 输入格式

第一行两个数 $n,m$。

接下来一行 $n$ 个数表示 $h_1,h_2,...,h_n$。

再接下来一行 $m$ 个数表示 $S_{1},S_{2},...,S_{m}$。

再接下来一行 $m$ 个数表示 $T_{1},T_{2},...,T_{m}$。


## 输出格式

输出一行 $m$ 个数表示 $F$。
## 样例

### 样例输入 #1
```
10 3 
1 2 3 5 4 10 8 6 7 9
1 2 8
6 10 3

```
### 样例输出 #1
```
1 3 2
```
### 样例输入 #2
```
20 5
12 13 14 15 16 17 18 19 20 22 21 30 29 28 27 26 23 24 25 1
1 20 2 5 3 
10 12 11 9 13 

```
### 样例输出 #2
```
1 2 3 4 5
```
## 提示

**本题采用捆绑测试**。

| 子任务编号 | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $n,m \leq 50$ | $10$ |
| $2$ | 对于任意 $1 < i \leq n$ 满足 $h_i < h_{i-1}$ | $25$ |
| $3$ | $n,m \leq 10^3$ | $25$ |
| $4$ | 无特殊性质 | $40$ |

对于 $100\%$ 的数据保证 $1 \leq m \leq n \leq 2 \times 10^5,0 < h_i \leq 10^9$。



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
title: "[NERC 2022] Dominoes"
layout: "post"
diff: 省选/NOI-
pid: P12793
tag: ['2022', '二分图', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] Dominoes
## 题目描述

Dora likes to play with dominoes. She takes $n \times m$ table, marks some cells as occupied, and then tries to fill all unoccupied cells with $2 \times 1$ dominoes.

![](https://cdn.luogu.com.cn/upload/image_hosting/izci2rsk.png)

Her little brother Dani loves to play pranks on his older sister. So when she is away, he marks two more unoccupied cells as occupied. He wants to do it in such a way that it will be impossible to fill all unoccupied cells with dominoes.

Help Dani to count the number of ways he can select these two cells. Since Dani can only count to one million, if this number of ways is $x$, output $\min(x, 10^6)$.
## 输入格式

The first line contains integers $n$ and $m$ ($1\le n, m\le 1000$). Next $n$ lines contain $m$ characters each --- the initial state of the table. Character $\tt{\#}$ corresponds to an occupied cell, and character $\tt{.}$ corresponds to an unoccupied cell. It is guaranteed that there are at least two unoccupied cells, and that it is possible to fill all unoccupied cells with dominoes.
## 输出格式

Let $x$ be the number of ways Dani can mark two cells in such a way that it will be impossible to fill all unoccupied cells with dominoes. 

Print one integer $\min(x, 10^6)$.
## 样例

### 样例输入 #1
```
3 6
...#..
......
#...##
```
### 样例输出 #1
```
52
```
### 样例输入 #2
```
2 2
..
..
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
2 2
#.
#.
```
### 样例输出 #3
```
0
```


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
title: "[GCJ 2021 #2] Retiling"
layout: "post"
diff: 省选/NOI-
pid: P13038
tag: ['2021', '二分图', 'Google Code Jam']
---
# [GCJ 2021 #2] Retiling
## 题目描述

Cody-Jamal's latest artistic installment is a tiled kitchen floor that can be retiled to different patterns. The floor consists of a matrix of $\mathbf{R}$ rows and $\mathbf{C}$ columns of square tiles. Each tile is reversible, one side is magenta and the other one is green.

To retile the kitchen, there are two allowed operations:

* flip a tile, changing its visible color from magenta to green, or vice versa, and
* swap two adjacent tiles (horizontally or vertically, but not diagonally), without flipping either.

Viewing Cody-Jamal's artistic floor is free, but interacting with it is not. Performing a single flip operation costs $\mathbf{F}$ coins, and performing a single swap operation costs $\mathbf{S}$ coins.

You can see the current state of the floor and want to turn it into a particular pattern. What is the minimum amount of coins you need to spend to achieve your goal?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. The first line of a test case contains 4 integers: $\mathbf{R}$, $\mathbf{C}$, $\mathbf{F}$ and $\mathbf{S}$, the number of rows and columns of the floor, the cost in coins of flipping and the cost in coins of swapping, respectively. Then, $2 \cdot \mathbf{R}$ lines follow. The first $\mathbf{R}$ lines contain $\mathbf{C}$ characters each. The $j$-th character of the $i$-th of these lines represents the current state of the tile in the $i$-th row and $j$-th column. The character is $\mathsf{M}$ if the currently visible side is magenta and $\mathsf{G}$ otherwise. The last $\mathbf{R}$ lines also contain $\mathbf{C}$ characters each. The $j$-th character of the $i$-th of these lines represents the color you want for the tile in the $i$-th row and $j$-th column, using the same character code as for the current state.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the minimum amount of coins you need to spend to perform operations that allow you to change the tile colors from their current state to your intended one.
## 样例

### 样例输入 #1
```
2
2 4 1 1
MGMG
MMMG
GMGM
MMMM
3 3 1 1
MGG
GMG
MMM
MMM
MGM
MMG
```
### 样例输出 #1
```
Case #1: 3
Case #2: 4
```
### 样例输入 #2
```
1
1 5 1000 1
MGGGG
GGGMM
```
### 样例输出 #2
```
Case #1: 1003
```
## 提示

**Sample Explanation**

In Sample Case #1, there are 5 tiles that have a different color between the current and the desired states of the floor. Since each operation can change at most 2 tiles, at least 3 operations, costing 3 coins, are needed. One way to do it with exactly 3 coins is:

1. Swap the leftmost two tiles in the top row.
2. Swap the rightmost two tiles in the top row.
3. Flip the bottom right corner tile.

The picture below illustrates the states the floor goes through. The highlighted tile or tiles in each state are the ones being changed by the operation.

![](https://cdn.luogu.com.cn/upload/image_hosting/lnckx68s.png)

In Sample Case #2, there are 6 tiles that need changing. However, since only swaps can change two tiles at a time, solving it with 3 operations would require all of them to be swaps. There is no way to involve all 6 tiles in a single swap each, so we need at least 4 operations. One way to use exactly 4 operations is:

1. Swap the topmost two tiles in the middle column.
2. Flip the top right corner tile.
3. Swap the bottommost two tiles in the rightmost column.
4. Flip the middle tile of the leftmost column.

The picture below illustrates the states the floor goes through.

![](https://cdn.luogu.com.cn/upload/image_hosting/yholjw9b.png)

Sample Test Set 2 fits the limits of Test Set 2. It will not be run against your submitted solutions.

In the Sample Case for Test Set 2, flips are so expensive that we want to avoid them at all costs. We need at least one since our desired floor state has more magenta tiles than the current one, and swaps do not change that amount. We can do it optimally with just one flip like this:

1. Swap the leftmost two tiles.
2. Flip the rightmost tile.
3. Swap the second and third tiles from the left.
4. Swap the third and fourth tiles from the left.

The picture below illustrates all the states the floor goes through.


![](https://cdn.luogu.com.cn/upload/image_hosting/7c22w7hy.png)

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{R} \leq 10$.
- $1 \leq \mathbf{C} \leq 10$.

**Test Set 1 (11 Pts, Visible Verdict)**

- $\mathbf{F}=1$.
- $\mathbf{S}=1$.

**Test Set 2 (23 Pts, Hidden Verdict)**

- $1 \leq \mathbf{F} \leq 10^{6}$.
- $1 \leq \mathbf{S} \leq 10^{6}$.


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
title: "[GCJ 2017 #2] Shoot the Turrets"
layout: "post"
diff: 省选/NOI-
pid: P13174
tag: ['2017', 'Special Judge', '广度优先搜索 BFS', '二分图', 'Google Code Jam']
---
# [GCJ 2017 #2] Shoot the Turrets
## 题目描述

The fight to free the city from extraterrestrial invaders is over! People are happy that love and peace have returned.

The city is represented as a grid with $R$ rows and $C$ columns. Some cells on the grid are buildings (through which nobody can see, nobody can shoot, and nobody can walk), and some are streets (through which everybody can see, shoot and walk). Unfortunately, during the war, the now-defeated invaders set up automatic security turrets in the city. These turrets are only in streets (not in buildings). They pose a threat to the citizens, but fortunately, there are also some soldiers on the streets (not in buildings). Initially, no soldier is in the same place as a turret.

The invader turrets do not move. They are small, so they don't block sight and shooting. A soldier cannot walk through an active turret's cell, but can walk through it once it is destroyed. A turret can only see soldiers in the cells for which it has a horizontal or vertical line of sight. If a soldier enters such a cell, the turret does not fire. If a soldier attempts to exit such a cell (after entering it, or after starting in that cell), the turret fires. Luckily, a soldier can still shoot from that cell, and the turret will not detect that as movement. It means that none of your soldiers will actually die, because in the worst case they can always wait, motionless, for help (perhaps for a long time). Maybe you will have a chance to rescue them later.

Each soldier can make a total of $M$ unit moves. Each of these moves must be one cell in a horizontal or vertical direction. Soldiers can walk through each other and do not block the lines of sight of other soldiers or turrets. Each soldier also has one bullet. If a soldier has a turret in her horizontal or vertical line of sight, the soldier can shoot and destroy it. Each shot can only destroy one turret, but the soldiers are such excellent shooters that they can even shoot past one or several turrets or soldiers in their line of sight and hit another turret farther away!

You are given a map (with the soldier and turret positions marked). What is the largest number of turrets that the soldiers can destroy?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing the integer $C$ (the width of the map), $R$ (the height of the map) and $M$ (the number of unit moves each soldier can make). The next $R$ lines contain $C$ characters each, with . representing a street, # representing a building, S representing a soldier and T representing a turret.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the maximum number of turrets that it is possible to destroy. Then $y$ lines should follow: each should contain two integers $s_i$ and $t_i$ denoting that the $i$th thing that happens should be soldier $s_i$ destroying turret $t_i$ (you don't need to specify exactly how the soldier has to move). If multiple valid strategies exist, you may output any one of them.

Soldiers are numbered from 1, reading from left to right along the top row, then left to right along the next row down from the top, and so on, from top to bottom.
## 样例

### 样例输入 #1
```
4
2 2 1
#S
T.
2 6 4
.T
.T
.T
S#
S#
S#
5 5 4
.....
SS#.T
SS#TT
SS#.T
.....
3 3 8
S.#
.#.
#.T
```
### 样例输出 #1
```
Case #1: 1
1 1
Case #2: 3
3 3
1 1
2 2
Case #3: 3
1 2
2 1
6 3
Case #4: 0
```
## 提示

**Sample Explanation**

In Case #2, one of the possible solutions is to move soldier $3$ up three cells and shoot turret $3$. Then soldier $1$ can move up one cell and right one cell (to where turret $3$ was) and shoot past turret $2$ to destroy turret $1$. Finally, soldier $2$ can move up three cells and shoot turret $2$.

In Case #3, soldier $1$ can move up one cell, then right three cells and shoot turret $2$. Then soldier $2$ can move up one cell, then right three cells and shoot turret $1$. Finally, soldier $6$ can move down one cell, then right three cells and shoot turret $3$. Other soldiers have insufficient move range to shoot any other turrets.

In Case #4, the soldier cannot move to within the same row or column as the turret, so the turret cannot be destroyed.

**Limits**

- $1 \leq T \leq 100$.
- $0 \leq M < C \times R$.

**Small dataset (Test Set 1 - Visible)**

- Time limit: ~~30~~ 7.5 seconds.
- $1 \leq C \leq 30$.
- $1 \leq R \leq 30$.
- The number of S symbols is between $1$ and $10$.
- The number of T symbols is between $1$ and $10$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~60~~ 15 seconds.
- $1 \leq C \leq 100$.
- $1 \leq R \leq 100$.
- The number of S symbols is between $1$ and $100$.
- The number of T symbols is between $1$ and $100$.


---

---
title: "[GCJ 2016 #2] Freeform Factory"
layout: "post"
diff: 省选/NOI-
pid: P13201
tag: ['动态规划 DP', '图论', '2016', '二分图', 'Google Code Jam']
---
# [GCJ 2016 #2] Freeform Factory
## 题目描述

You have just built a brand new factory. Your factory has $\mathbf{N}$ different machines, and each machine needs to be operated by exactly one worker for the factory to function well.

You have also hired $\mathbf{N}$ workers to operate those machines. Since you were in a hurry when you hired them, you did not check whether they actually know how to operate your machines. Now you have finally asked them, and so you have the information on whether the i-th worker can operate the j-th machine, for each i and j.

In a typical working day, the workers will arrive at the factory in a random order, which can be different each day. As each worker arrives, they will find all machines that they know how to operate and that do not already have an operator. They will choose one of those at random and operate it for the whole working day. If all machines they know how to operate already have an operator, they will not work that day. Your goal is to make sure that all machines are being operated each working day, regardless of what order the workers arrive in and which machines they choose.

For example, suppose there are two workers $\mathrm{A}$ and $\mathrm{B}$, and two machines 1 and 2. Suppose that $\mathrm{A}$ knows how to operate 1 and 2, and $\mathrm{B}$ knows how to operate 1 but not 2. If worker $\mathrm{B}$ arrives first, he will pick machine 1, then when worker $\mathrm{A}$ arrives she will have to choose 2, and the factory will work well. However, if worker $\mathrm{A}$ arrives first, it might happen that she chooses to operate 1 on that day, and then when worker $\mathrm{B}$ arrives he does not have anything to do, leaving machine 2 without an operator, and causing your factory to waste a whole day!

As another example, suppose there are two workers $\mathrm{A}$ and $\mathrm{B}$, and two machines 1 and 2, and that $\mathrm{A}$ knows how to operate 1 but not 2, and $\mathrm{B}$ does not know how to operate anything. Then, regardless of the order in which the workers arrive, the factory will not be able to function well.

Before you open your factory, in order to guarantee that the factory will constantly function well, you can teach your workers how to operate machines. It costs one dollar to give a single worker a lesson on how to operate a single machine. Each lesson involves only one worker and only one machine, but you can teach any number of lessons to any number of workers, and the same worker can receive multiple lessons. You cannot make a worker forget how to operate a machine if they already know how to operate it.

For example, both examples above can be fixed by teaching worker $\mathrm{B}$ to operate machine 2. In that case each machine is guaranteed to have an operator every day, regardless of which order the workers arrive in and which machines they choose to operate when they have more than one possibility.

What is the minimum amount of dollars you need to spend on training workers to make sure the factory functions well every day?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with one line with an integer $\mathbf{N}$, the number of workers (and machines). This line is followed by $\mathbf{N}$ lines with a string of $\mathbf{N}$ characters each. The $\mathrm{j}$-th character on the i-th of those lines is 1 if the i-th worker knows how to operate the $\mathrm{j}$-th machine, and 0 otherwise.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $\mathrm{x}$ is the test case number (starting from 1), and $\mathrm{y}$ is a non-negative integer: the minimum amount of dollars you need to spend to make sure that all $\mathbf{N}$ machines will always have an operator.
## 样例

### 样例输入 #1
```
5
2
11
10
2
10
00
3
000
000
000
1
1
3
000
110
000
```
### 样例输出 #1
```
Case #1: 1
Case #2: 1
Case #3: 3
Case #4: 0
Case #5: 3
```
## 提示

**Sample Explanation**

Sample cases #1 and #2 are the ones described in the problem statement.

In sample case #3, nobody knows how to do anything! One optimal strategy is to teach worker A to operate machine 1, worker B to operate machine 2, and worker C to operate machine 3.

In sample case #4, no action is necessary. There is only one worker, and the worker already knows how to operate the one machine.

In sample case #5, worker B already knows how to operate machines 1 and 2. One optimal strategy is to teach worker A to operate machine 3, and make A the only worker who can operate that machine. But now we have to consider that B might operate either machine 1 or 2 upon arrival, so C needs to be able to operate the one not chosen by B. So C must be taught to operate both 1 and 2.

**Sample Explantion**

- $1 \leqslant \mathbf{T} \leqslant 100$.

**Small dataset (6 Pts, Test Set 1 - Visible)**

- $1 \leqslant \mathbf{N} \leqslant 4$.

**Large dataset (25 Pts, Test Set 2 - Hidden)**

- $1 \leqslant \mathbf{N} \leqslant 25$.


---

---
title: "[GDCPC 2024] 小班课"
layout: "post"
diff: 省选/NOI-
pid: P13358
tag: ['2024', '广东', 'Special Judge', '二分图', 'XCPC']
---
# [GDCPC 2024] 小班课
## 题目背景

数据、标程、题解等资源的获取：<https://gitlink.org.cn/thusaa/gdcpc2024>
## 题目描述

在 P 大学中，很多课程设立了小班课，学生可以自由根据需求选择小班课。当然，小班课的容量并不是无限的，并不是每个学生都能选上心仪的小班课。

本学期，共有 $n$ 名同学报名了 A 课程，该课程共设立了 $m$ 门小班课，第 $i$ 门小班课有容量 $b_i$。第 $i$ 名学生对小班课有一个意向度序列 $a_{i,1}\sim a_{i,k_i}$，其中 $a_{i,1}$ 表示意向度最高的课程，$a_{i,k_i}$ 表示意向度最低的课程。如果一门小班课 $j$ 不在这个序列里，那么说明学生 $i$ 无法参加第 $j$ 门小班课。

学生们按照 $1\sim n$ 的顺序进行选课，每次会选择优先度最高且未满的小班课，如果所有 $a_{i,1}\sim a_{i,k_i}$ 都已满，那么该学生不会选择任何小班课。

现在给出每个学生的意向度序列，请重排学生的顺序，使得选上小班课的学生最多。并构造方案。
## 输入格式

第一行一个正整数 $T(1\leq T\leq 500)$，表示数据组数。

对于每组数据，第一行两个正整数 $n,m(1\leq n,m\leq 500)$，即学生数量和小班课数量。

之后一行 $m$ 个非负整数 $b_i(0\leq b_i\leq 500)$，即每一门小班课的容量。

之后 $n$ 行，每行首先是一个非负整数 $k_i(0\leq k_i\leq m)$，之后是 $k_i$ 个两两不同的正整数 $a_{i,1}\sim a_{i,k_i}(1\leq a_{i,j}\leq m)$，表示意向度序列。

## 输出格式

对于每组数据，输出两行，第一行为一个整数 $ans$ 表示答案，之后一行 $n$ 个数，为一个 $1\sim n$ 的排列，表示构造的方案。如果有多种方案，输出任意一种即可。

## 样例

### 样例输入 #1
```
3
5 5
1 1 1 1 1
4 1 3 2 4
1 5
4 3 4 2 1
2 3 5
1 1
5 3
1 2 2
2 1 2
2 1 2
2 1 3
2 1 3
2 1 3
5 5
1 1 1 1 1
2 1 2
2 5 4
2 3 2
2 4 3
2 5 1
```
### 样例输出 #1
```
5
2 4 5 1 3
5
5 1 2 3 4
5
1 5 2 4 3
```
## 提示

对于第一组数据，按照给定的方案，学生 $2$ 首先选择 $5$，然后学生 $4$ 选择 $3$，学生 $5$ 选择 $1$，学生 $1$ 尝试选择 $1,5$ 但都已满员，所以最终选择 $2$，学生 $3$ 尝试选择 $3$ 但已满员，所以最终选择 $4$。该组数据的方案不唯一，例如，$\{2,5,4,3,1\}$ 也是一个可行解。

对于第二组数据，$\{1,2,3,4,5\}$ **不**是一个可行解，如果这样构造，那么学生 $1,2,3,4$ 会分别选择 $1,2,3,3$，这时对于学生 $5$，$1,3$ 都已满员，因此无法选择任何课程。


---

---
title: "[NWERC 2023] Isolated Island"
layout: "post"
diff: 省选/NOI-
pid: P13708
tag: ['图论', '计算几何', '2023', '平面图', '二分图', 'ICPC', 'Ad-hoc']
---
# [NWERC 2023] Isolated Island
## 题目描述

On a small island far far away, a handful of old men live isolated from the rest of the world.
The entire island is divided into plots of land by fences, and each old man owns
a single plot of land bounded by fences on all sides. (The region
outside all fences is the ocean.)
Each of the inhabitants needs fish to survive and the only place where they can fish is the ocean surrounding them.
Since not every plot of land is connected to the ocean,
some of the men might need to pass through the land of others before being able to fish.
The men can cross a single fence at a time, but cannot go through fenceposts or
locations where fences intersect.

Unfortunately, the old men are greedy.
They demand one fish each time a person wants to enter their land.
Since they do not want to lose too much fish to the others,
every old man chooses a route that minimizes the number of fish he has to pay to get to the ocean.

Over the years, this has led to rivalry between the old men.
Each man hates all other men who have to pay less than him to reach the ocean.
Two men only *like* each other if they have to pay the same amount of fish to reach the ocean.

|![](https://cdn.luogu.com.cn/upload/image_hosting/e253y5sb.png)|![](https://cdn.luogu.com.cn/upload/image_hosting/8aukzter.png)|![](https://cdn.luogu.com.cn/upload/image_hosting/ea4htdic.png)|
|:---:|:---:|:---:|

:::align{center}
Figure I.1: Illustrations of the first three Sample Inputs. In Sample Input 1, every man has direct access to the ocean, so they all like each other. In Sample Input 2, there does not exist a pair of neighbours who like each other, because the man living in the middle needs to pay one fish, whereas all of his neighbours do not have to pay any fish to reach the ocean. In Sample Input 3, there are six men, some of whom are friendly neighbours.
:::

The natural question which now occurs is:
are there some old men on this island who are neighbours (owning land on
opposite sides of a single fence) and like each other?
See Figure I.1 for two islands with opposite answers to this question.
## 输入格式

The input consists of:
- One line with an integer $n$ ($3 \le n \le 1000$), the number of fences.
- $n$ lines, each with four integers $x_1$, $y_1$, $x_2$, and $y_2$ ($\left|x_1\right|, \left|y_1\right|, \left|x_2\right|, \left|y_2\right|\leq 10^6$, $(x_1,y_1)\neq(x_2,y_2)$), indicating a straight fence between fenceposts at $(x_1,y_1)$ and $(x_2, y_2)$.

Note that fences may intersect internally, and that three or more fences may intersect in the same location.

It is guaranteed that any two fences intersect only in at most one point.
Furthermore, after crossing a single fence, one always ends up in a different region.
All regions together form a single island, where any region can be reached from any other region.

## 输出格式

If there exists a pair of neighbours who like each other, then output "$\texttt{yes}$". Otherwise, output "$\texttt{no}$".
## 样例

### 样例输入 #1
```
6
-3 -3 0 3
-3 -3 0 0
-3 -3 3 -3
0 0 0 3
0 0 3 -3
0 3 3 -3
```
### 样例输出 #1
```
yes
```
### 样例输入 #2
```
 6
-6 -3 0 3
0 3 6 -3
6 -3 -6 -3
-3 0 3 0
3 0 0 -3
0 -3 -3 0
```
### 样例输出 #2
```
no
```
### 样例输入 #3
```
8
0 1 2 1
2 2 0 0
1 2 1 0
1 0 2 1
0 0 2 0
1 2 2 2
0 1 0 0
2 2 2 0
```
### 样例输出 #3
```
yes
```
### 样例输入 #4
```
4
0 0 1 0
1 0 1 1
1 1 0 1
0 1 0 0
```
### 样例输出 #4
```
no
```


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
title: "[NOI2009] 变换序列"
layout: "post"
diff: 省选/NOI-
pid: P1963
tag: ['2009', 'NOI', '二分图']
---
# [NOI2009] 变换序列
## 题目描述

对于 $N$ 个整数 $0, 1, \cdots, N-1$，一个变换序列 $T$ 可以将 $i$ 变成 $T_i$，其中 $T_i \in \{ 0,1,\cdots, N-1\}$ 且 $\bigcup_{i=0}^{N-1} \{T_i\} = \{0,1,\cdots , N-1\}$。$\forall x,y \in  \{0,1,\cdots , N-1\}$，定义 $x$ 和 $y$ 之间的距离 $D(x,y)=\min\{|x-y|,N-|x-y|\}$。给定每个 $i$ 和 $T_i$ 之间的距离 $D(i,T_i)$，你需要求出一个满足要求的变换序列 $T$。如果有多个满足条件的序列，输出其中字典序最小的一个。

说明：对于两个变换序列 $S$ 和 $T$，如果存在 $p<N$，满足对于 $i=0,1,\cdots p-1$，$S_i=T_i$ 且 $S_p<T_p$，我们称 $S$ 比 $T$ 字典序小。
## 输入格式

第一行包含一个正整数 $N$，表示序列的长度。接下来的一行包含 $N$ 个整数 $D_i$，其中 $D_i$ 表示 $i$ 和 $T_i$ 之间的距离。
## 输出格式

如果至少存在一个满足要求的变换序列 $T$，则输出文件中包含一行 $N$ 个整数，表示你计算得到的字典序最小的 $T$；否则输出 `No Answer`（不含引号）。注意：输出文件中相邻两个数之间用一个空格分开，行末不包含多余空格。
## 样例

### 样例输入 #1
```
5
1 1 2 2 1

```
### 样例输出 #1
```
1 2 4 0 3
```
## 提示

- 对于 $30\%$ 的数据，满足：$N \le 50$；
- 对于 $60\%$ 的数据，满足：$N \le 500$；
- 对于 $100\%$ 的数据，满足：$N \le 10 ^ 4$。



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
title: "[HNOI2010] 平面图判定"
layout: "post"
diff: 省选/NOI-
pid: P3209
tag: ['2010', '并查集', '湖南', '2-SAT', '二分图']
---
# [HNOI2010] 平面图判定
## 题目描述

若能将无向图 $G=(V, E)$ 画在平面上使得任意两条无重合顶点的边不相交，则称 $G$ 是平面图。判定一个图是否为平面图的问题是图论中的一个重要问题。现在假设你要判定的是一类特殊的图，图中存在一个包含所有顶点的环，即存在哈密顿回路。

## 输入格式

输入文件的第一行是一个正整数 $T$，表示数据组数 (每组数据描述一个需要判定的图)。接下来从输入文件第二行开始有 $T$ 组数据，每组数据的第一行是用空格隔开的两个正整数 $N$ 和 $M$，分别表示对应图的顶点数和边数。紧接着的 $M$ 行，每行是用空格隔开的两个正整数 $u$ 和 $v$ $\left(1\leq u,v\leq N\right)$，表示对应图的一条边 $\left(u,v\right)$, 输入的数据保证所有边仅出现一次。每组数据的最后一行是用空格隔开的 $N$ 个正整数，从左到右表示对应图中的一个哈密顿回路：$V_1,V_2,…,V_N$，即对任意 $i\not=j$ 有 $V_i\not=V_j$ 且对任意 $1\leq i\leq N-1$ 有 $\left(V_i,V_{i+1}\right)\in E$ 及 $\left(V_1,V_N\right)\in E$。输入的数据保证 $100\%$ 的数据满足 $T\leq100,3\leq N\leq200,M\leq10000$。

## 输出格式

包含 $T$ 行，若输入文件的第 $i$ 组数据所对应图是平面图，则在第 $i$ 行输出 $\text{YES}$，否则在第 $i$ 行输出 $\text{NO}$，注意均为大写字母
## 样例

### 样例输入 #1
```
2
6 9
1 4
1 5
1 6
2 4
2 5
2 6
3 4
3 5
3 6
1 4 2 5 3 6
5 5
1 2
2 3
3 4
4 5
5 1
1 2 3 4 5
```
### 样例输出 #1
```
NO
YES
```
## 提示

感谢@hibiki 对题目进行修正

感谢@@Anguei  提供latex题面


---

---
title: "[HNOI2013] 消毒"
layout: "post"
diff: 省选/NOI-
pid: P3231
tag: ['搜索', '2013', '湖南', '枚举', '二分图']
---
# [HNOI2013] 消毒
## 题目描述


最近在生物实验室工作的小 T 遇到了大麻烦。 由于实验室最近升级的缘故，他的分格实验皿是一个长方体，其尺寸为 $a\times b\times c$。为了实验的方便，它被划分为 $a\times b\times c$ 个单位立方体区域，每个单位立方体尺寸为 $1\times 1\times 1$，并用 $(i,j,k)$ 标识一个单位立方体。这个实验皿已经很久没有人用了。现在，小 T 被导师要求将其中一些单位立方体区域进行消毒操作（每个区域可以被重复消毒）。

而由于严格的实验要求，他被要求使用一种特定的 F 试剂来进行消毒。 这种 F 试剂特别奇怪，每次对尺寸为 $x\times y\times z$ 的长方体区域（它由 $x\times y\times z$ 个单位立方体组成）进行消毒时，只需要使用 $\min(x,y,z)$ 单位的 F 试剂。F 试剂的价格不菲，这可难倒了小 T。

现在请你告诉他，最少要用多少单位的 F 试剂。
## 输入格式

**本题有多组数据。**

第一行是一个正整数 $D$，表示数据组数。

接下来是 $D$ 组数据，每组数据第一行是三个正整数 $a,b,c$ 表示实验皿的尺寸。

接下来会出现 $a$ 个 $b$ 行 $c$ 列的用空格隔开的 `01` 矩阵，`0` 表示对应的单位立方体不要求消毒，`1` 表示对应的单位立方体需要消毒：如，如果第 $1$ 个 `01` 矩阵的第 $2$ 行第 $3$ 列为 `1`，则表示单位立方体 $(1,2,3)$ 需要被消毒。
## 输出格式

$D$ 行，每行一个整数，表示对应实验皿最少要用多少单位的 F 试剂。
## 样例

### 样例输入 #1
```
1
4  4 4
1  0 1 1
0  0 1 1
0  0 0 0
0  0 0 0
0  0 1 1
1  0 1 1
0  0 0 0
0  0 0 0
0  0 0 0
0  0 0 0
1  0 0 0
0  0 0 0
0  0 0 0
0  0 0 0
0  0 0 0
1  0 0 0
```
### 样例输出 #1
```
3
```
## 提示

#### 样例 1 解释
对于区域 $(1,1,3)-(2,2,4)$ 和 $(1,1,1)-(4,4,1)$ 消毒，分别花费 $2$ 个单位和 $1$ 个单位的 F 试剂。

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1\le a,b,c\le 5\times 10^3$，$abc\le 5\times 10^3$，且 $1\le D\le 3$。



---

---
title: "[HAOI2017] 新型城市化"
layout: "post"
diff: 省选/NOI-
pid: P3731
tag: ['2017', '河南', '各省省选', '强连通分量', '二分图']
---
# [HAOI2017] 新型城市化
## 题目描述

Anihc 国有 $n$ 座城市。城市之间存在一些贸易合作关系，如果城市 $x$ 与城市 $y$ 之间存在贸易协定，那么城市 $x$ 和城市 $y$ 则是一对贸易伙伴（注意： $(x,y)$ 和 $(y,x)$ 是同一对城市）。

为了实现新型城市化，实现统筹城乡一体化以及发挥城市群辐射与带动作用，国家决定规划新型城市关系。一些城市能够被称为城市群的条件是：这些城市两两都是贸易伙伴。由于Anihc 国之前也一直很重视城市关系建设，所以可以保证在目前已存在的贸易合作关系的情况下 Anihc 的 $n$ 座城市可以恰好被划分为不超过两个城市群。

为了建设新型城市关系 Anihc 国想要选出两个之前并不是贸易伙伴的城市，使这两个城市成为贸易伙伴，并且要求在这两个城市成为贸易伙伴之后，最大城市群的大小至少比他们成为贸易伙伴之前的最大城市群的大小增加 $1$。

Anihc 国需要在下一次会议上讨论扩大建设新型城市关系的问题，所以要请你求出在哪些城市之间建立贸易伙伴关系可以使得这个条件成立，即建立此关系前后的最大城市群的大小至少相差 $1$。
## 输入格式

第一行 $2$ 个整数 $n,m$，表示城市的个数，目前还没有建立贸易伙伴关系的城市的对数。

接下来 $m$ 行，每行 $2$ 个整数 $x,y$ 表示城市 $x,y$ 之间目前还没有建立贸易伙伴关系。
## 输出格式

第一行 $1$ 个整数 $\text{ans}$，表示符合条件的城市的对数。

接下来 $\text{ans}$ 行，每行两个整数，表示一对可以选择来建立贸易伙伴关系的城市。对于一对城市 $x,y$，请先输出编号更小的那一个。最后城市对与城市对之间顺序请按照字典序从小到大输出。
## 样例

### 样例输入 #1
```
5 3
1 5
2 4
2 5
```
### 样例输出 #1
```
2
1 5
2 4
```
## 提示

数据点 $1$：$n\le 16$；

数据点 $2$：$n\le 16$；

数据点 $3\sim 5$：$n\le 100$；

数据点 $6$：$n\le 500$；

数据点 $7\sim10$：$n\le 10^4$。

对于所有的数据保证： $n \le 10^4,0 \le m \le \min(1.5\times 10^5,\dfrac{n(n-1)}{2})$。保证输入的城市关系中不会出现 $(x,x)$ 这样的关系，同一对城市也不会出现两次（无重边，无自环）。


---

---
title: "[JLOI2008] 将军"
layout: "post"
diff: 省选/NOI-
pid: P3882
tag: ['2008', '各省省选', '吉林', '图论建模', '二分图']
---
# [JLOI2008] 将军
## 题目描述

刘先生最近在学习国际象棋，使用一个叫 jloi-08 的游戏软件。在这个游戏里，不但可以和电脑普通地对弈，还可以学习著名的棋局，还有针对初学者的规则指导等丰富功能。但是…大小却要 1.4G T\_T。

言归正传，在这个软件里，为了让玩家更好地理解和运用各个棋子，有很多趣味的游戏，比如以下就是一个：

给出一个棋盘和一些棋子，让你把这些棋子摆放在棋盘上，使得两两不互相攻击。你的得分由你摆放上去的棋子的个数与种类有关。

这个游戏很复杂，刘先生老是玩不到高分。于是电脑便降低了难度，替刘先生摆上了一些棋子，最后只给你任意多个 bishop（教主）。

现在刘先生便要考一考你，在电脑给出的这张棋盘上，最多能放几个 bishop。

国际象棋中一共有 6 种棋子：

- king（国王）；
- queen（皇后）；
- bishop（教主）；
- knight（骑士）；
- rook（车）；
- pawn（步兵）。

各棋子的攻击范围如下：

- queen 可以攻击与它在同一行，同一列，同一条对角线的棋子；
- knight 的攻击范围如下图所示：

![](https://cdn.luogu.com.cn/upload/pic/2669.png)

- rook 攻击水平和垂直两条线上的所有格子；
- pawn 攻击前方两条斜线方向各一格(“前方”指 $x$ 递增的方向，$x$ 行 $y$ 列）；
- king 攻击周围 8 个方向各 1 格；
- bishop 攻击两条对角线上的所有格子。

除 knight 以外，所有棋子的攻击范围均会被别的棋子所阻挡。

可惜的是这个软件也不是顶优秀，给出的棋盘上的棋子可能互相会攻击，不过你不用理会这些，你只要保证你摆放的 bishop 不与它们以及不互相攻击就可以了。
## 输入格式

第一行是两个整数 $x,y$（$1 \leq x,y \leq 1024$）。

下面的 $x$ 行每行 $y$ 个字符表示棋盘。

其中：`K` – king，`Q` – queen，`B` – bishop，`N` – knight，`R` – rook，`P` – pawn，`.` – blank.
## 输出格式

仅一行一个数，表示最多能够摆放的 bishop 的个数。

## 样例

### 样例输入 #1
```
3 3
..N
...
...

```
### 样例输出 #1
```
2
```
## 提示

```plain
BBN
...
...
```

```plain
BBN
...
B..
```

虽然看上去下面的方法比上面的优秀，但是 N 被第三行的 B 攻击了。也就是说，你需要避免的有 2 种情况： 你摆放的 bishop 之间的互相攻击以及你摆放的 bishop 与预先摆放好的棋子之间的互相攻击；但不用考虑预先摆放好的棋子之间的互相攻击。



---

---
title: "[TJOI2014] 匹配"
layout: "post"
diff: 省选/NOI-
pid: P3967
tag: ['2014', '各省省选', '枚举', '二分图', '费用流', '天津']
---
# [TJOI2014] 匹配
## 题目描述

有 $N$ 个单身的男孩和 $N$ 个单身女孩，男孩 $i$ 和女孩 $j$ 在一起得到的幸福值为 $H_{i,j}$。

一个匹配即对这 $N$ 个男孩女孩的安排：每个男孩恰好有一个女朋友，每个女孩恰好有一个男朋友。

一个匹配的幸福值即这 $N$ 对男女朋友的幸福值的和。

经典的问题是计算幸福值最大的匹配，即完美匹配。然而完美匹配有时候并不唯一，你需要计算对于所有的完美匹配，其交集是什么。
## 输入格式

输入的第一行是一个正整数 $N$ 。

接下来是一个 $N\times N$ 大小的矩阵 $H$，$H_{i,j}$ 表示男孩 $i$ 和女孩 $j$ 在一起的幸福值。
## 输出格式

第一行输出完美匹配的幸福值，接下来是若干行，每一行是一对整数 $i$ 和 $j$，表示男孩 $i$ 和女孩 $j$ 在所有完美匹配的交集中，以 $i$ 的递增顺序输出。
## 样例

### 样例输入 #1
```
3
1 1 1
2 1 1
1 1 1
```
### 样例输出 #1
```
4
2 1
```
## 提示

- 对于 $30\%$ 的数据，$N \leq 30$；
- 对于 $100\%$ 的数据，$1\leq N \leq 80$，$0\leq H_{i,j}\leq 5\times10^3$。


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
title: "[BJOI2012] 连连看"
layout: "post"
diff: 省选/NOI-
pid: P4134
tag: ['2012', '各省省选', '北京', '二分图', '费用流']
---
# [BJOI2012] 连连看
## 题目描述

凡是考智商的题里面总会有这么一种消除游戏。不过现在面对的这关连连看可不是 QQ 游戏里那种考眼力的游戏。我们的规则是，给出一个闭区间 $[a,b]$ 中的全部整数，如果其中某两个数 $x$，$y$（$x>y$）的平方差 $x^2-y^2$ 是一个完全平方数 $z^2$，并且 $y$ 与 $z$ 互质，那么就可以将 $x$ 和 $y$ 连起来并且将它们一起消除，同时得到 $x+y$ 点分数。那么过关的要求就是，消除的数对尽可能多的前提下，得到足够的分数。快动手动笔算一算吧。
## 输入格式

只有一行，两个整数，分别表示 $a$，$b$。
## 输出格式

两个数，可以消去的对数，及在此基础上能得到的最大分数。

## 样例

### 样例输入 #1
```
1 15
```
### 样例输出 #1
```
2 34
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $1\le a,b\le100$。
- 对于 $100\%$ 的数据，保证 $1\le a,b\le1000$。


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
title: "[TJOI2018] 智力竞赛"
layout: "post"
diff: 省选/NOI-
pid: P4589
tag: ['2018', '二分', '各省省选', '二分图', '天津']
---
# [TJOI2018] 智力竞赛
## 题目描述

小豆报名参加智力竞赛，他带上了 $n$ 个好朋友作为亲友团一块来参加比赛。比赛规则如下：

一共有 $m$ 道题目，每个人都有 $1$ 次答题机会，每次答题为选择一道题目回答，在回答正确后，可以继续回答这个题目的后续题目，直到答错题目或者没有后续题目。

每个问题都会有一个价值，比赛最后参赛选手获得的奖励价值等价于该选手和他的亲友团没有回答的问题中的最低价值。

我们现在知道小豆和他的亲友团实力非常强，能够做出这次竞赛中的所有题目。

小豆想知道在知道题目和后续题目的条件下，他最大能获得的价值是多少？
## 输入格式

第一行有两个整数 $n,m$。（$n\leq50,m\leq500$）

接下来 $m$ 行，第 $i+1$ 行表示编号为 $i$ 的题目的题目信息，格式形如 $v_i,k_i,a_{i,1},a_{i,2},...,a_{i,k_i}$，其中 $v_i$ 表示该题目的价值，$k_i$ 表示这个题目的后续题目个数，$a_{i,1},a_{i,2},...,a_{i,k_i}$ 表示 $k_i$ 个后续题目的编号。
## 输出格式

如果全部题目都能答对，则输出 `AK`，否则输出小豆可以获得的最高奖励价值。
## 样例

### 样例输入 #1
```
1 3
1 0
2 1 3
3 0
```
### 样例输出 #1
```
AK
```
### 样例输入 #2
```
1 6
1 2 2 3
2 1 4
3 1 4
4 1 6
5 0
6 0
```
### 样例输出 #2
```
5
```
## 提示

对于 $10\%$ 的数据，有 $1<n,m\leq10$。

对于 $20\%$ 的数据，有 $1<n,m\leq100$。

对于 $100\%$ 的数据，有 $1<n\leq50,1<m\leq500,v_i\leq10^9,k_i,a_{i,j}\leq m$。


---

---
title: "[CEOI 2005] Depot Rearrangement"
layout: "post"
diff: 省选/NOI-
pid: P7684
tag: ['图论', '2005', 'Special Judge', 'CEOI（中欧）', '欧拉回路', '二分图', '构造']
---
# [CEOI 2005] Depot Rearrangement
## 题目描述

一家公司经营着 $N$ 个店铺，每个店铺都销售 $M$ 种不同的产品。该公司有一个大型仓库，产品在运送到商店之前在都会那里进行包装。每家商店将会收到相同数量的每种产品。因此，该公司将一定数量的相应产品分别包装到一个集装箱中，并用产品标识符标记该集装箱。产品由 $1$ 到 $M$ 的数字标识。因此，在包装结束后，仓库中将会有 $N×M$ 个集装箱，并且正好 $N$ 个集装箱贴有每个产品的对应标签。由于该仓库位于一个狭窄的建筑物内，所以集装箱排成了一排。但为了加快配送速度，仓库经理想要重新排列集装箱。由于将产品配送到商店是通过向每个商店发出一辆卡车来实现的，并且每辆卡车运载每种产品的一个集装箱，其合适的安排如下。该行最前部分 $M$ 个集装箱必须贴有不同的产品标签，该行的第二部分 $M$ 个集装箱必须贴有不同的产品标签，依此类推。不幸的是，在这一行的尽头只有一个空闲的地方可以放置一个集装箱。因此，必须通过依次拿起集装箱并将其移动到空闲位置来进行重新排列。重新排列后，空闲位置也必须在行的末尾。  
目标是通过最少的移动以实现所需的重新排列。  
现请您编写一个程序来计算需要最少移动多少次使得达成目标重排。
## 输入格式

第一行包含两个整数 $N$ 和 $M$。$N$ 是商店的数量，$M$ 是产品的数量。第二行包含 $N×M$ 个整数，即按初始顺序排列的集装箱标签。每个产品标识符 $x$ 在行中恰好出现 $N$ 次。
## 输出格式

第一行包含一个整数 $S$，这是达成集装箱所需排列所需的最小移动次数。以下 $S$ 行描述了重新排列。每行包含一对整数 $x$，$y$。一对 $x$，$y$ 描述了一个移动：位于 $x$ 位置的集装箱将移动到位置 $y$。位置由从 $1$ 到 $N×M+1$ 的数字标识；最初位置 $N×M+1$ 是空闲的（没有集装箱）。只有在移动之前位置 $y$ 是空闲的，从 $x$ 到 $y$ 的移动才是合法的。从 $x$ 移动到 $y$ 后，位置 $x$ 将是空闲的。
## 样例

### 样例输入 #1
```
5  6
4 1 3 1 6 5 2 3 2 3 5 6 2 1 4 5 6 4 1 3 2 4 5 5 1 2 3 4 6 6
```
### 样例输出 #1
```
8
9 31
18 9
10 18 
4 10
31 4
30 31
24 30
31 24
```
## 提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq N \leq 400$，$1 \leq M \leq 400$，$1 \leq x \leq M$。  
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2005 的 Depot Rearrangement。  
由 @[求学的企鹅](/user/271784) 翻译整理。  
Special Judge 感谢 @[abruce](/user/104324)。


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
title: "「EVOI-RD1」飞鸟和蝉"
layout: "post"
diff: 省选/NOI-
pid: P7863
tag: ['图论建模', '二分图', '费用流']
---
# 「EVOI-RD1」飞鸟和蝉
## 题目背景

你骄傲地飞远，我栖息的叶片。  
听不见的宣言，重复过很多年。  
沧海月的想念羽化我昨天，  
在我成熟的笑脸，  
你却未看过一眼。
## 题目描述

蝉 Charlie 要去寻找他的好朋友飞鸟了。 

具体来说，Charlie 和他的好朋友生活的地方可以看作一个 $n \times m$ 的网格，左上角为 $(1,1)$，右下角为 $(n,m)$。每个格子 $(i,j)$ 有一个海拔高度 $h_{i,j}$。Charlie 的目标是从他的家 $(x_0,y_0)$ 出发，不重不漏地经过网格中的每个格子**恰好一次**，**最终回到自己的家** $(x_0,y_0)$。Charlie 有两种移动方式：

1. 跳跃。用这种方式，Charlie 可以到达上下左右 $4$ 个相邻格子中**海拔严格低于当前格子**的一个格子。注意跳跃不消耗体力。  
2. 飞行。用这种方式，Charlie 可以从当前格子 $(x,y)$ 到达网格中**任意一个**格子 $(x',y')$，并消耗 $h_{x',y'}-h_{x,y}$ 个单位的体力。**注意飞行所消耗的体力值可以是负数**。  

Charlie 希望用尽量少的飞行次数完成目标，**在此前提下**再令消耗的体力最少。由于网格实在太大了，Charlie 希望你能帮助他。
## 输入格式

第一行四个整数，分别代表 $n,m,x_0,y_0$，含义如上所述。  
接下来 $n$ 行，每行 $m$ 个整数，第 $i$ 行第 $j$ 个数代表格子 $(i,j)$ 的海拔 $h_{i,j}$。
## 输出格式

一行两个整数，分别代表“飞行的最少次数”与“飞行次数最少的前提下消耗的最少体力值”。
## 样例

### 样例输入 #1
```
3 3 1 1
1 2 3
8 9 4
7 6 5
```
### 样例输出 #1
```
1 8
```
### 样例输入 #2
```
3 3 2 3
1 2 3
2 2 4
1 2 2
```
### 样例输出 #2
```
5 4
```
### 样例输入 #3
```
4 4 2 3
5 9 6 2
4 2 3 6
7 2 5 2
4 2 3 9
```
### 样例输出 #3
```
7 25
```
### 样例输入 #4
```
10 10 3 3
9 13 7 7 3 8 6 5 12 8
1 4 10 11 9 10 13 6 2 18
3 3 19 6 14 2 19 10 2 16
3 1 11 14 14 18 8 8 16 14
13 5 7 4 11 17 3 16 10 20
10 16 12 19 14 12 11 20 15 10
10 15 5 1 16 2 7 5 14 5
3 19 12 19 8 13 17 7 10 13
2 10 17 6 8 11 8 7 1 4
3 7 8 1 3 5 4 11 9 17
```
### 样例输出 #4
```
36 254
```
## 提示

**本题采用捆绑测试**

样例 1 解释：从 $(1,1)$ 飞到 $(2,2)$，再绕一圈即可。

样例 2 解释：一种最佳方案为：$(2,3)-(1,3)-(1,2)-(1,1)=(2,1)-(3,1)=(2,2)=(3,2)=(3,3)=(2,3)$，其中 $=$ 代表飞行。  

- Subtask 1 (10 pts)：满足 $1 \leq n,m \leq 3$。
- Subtask 2 (20 pts)：满足 $1 \leq n,m \leq 5$。
- Subtask 3 (20 pts)：保证至多有两种不同的海拔高度。 
- Subtask 4 (50 pts)：无特殊限制。

对于 $100\%$ 的数据：
- $1 \leq n,m \leq 50$。

- $1 \leq x_0 \leq n,1 \leq y_0 \leq m,1 \leq h_{i,j} \leq 10^9$。  

出题人：[冷月葬T魂](https://www.luogu.com.cn/user/340903)


---

---
title: "[湖北省选模拟 2023] 棋圣 / alphago"
layout: "post"
diff: 省选/NOI-
pid: P9542
tag: ['动态规划 DP', '图论', '2023', 'O2优化', '二分图', 'Ad-hoc', '湖北']
---
# [湖北省选模拟 2023] 棋圣 / alphago
## 题目描述

小 K 是一名棋手，厌倦了传统围棋之后，他发明了一种新式围棋。

新式围棋是一种单人游戏。这个游戏的棋盘是一张包含 $n$ 个顶点，$m$ 条边的无向连通图，并且不存在重边和自环。同时，每条边有一个权值，第 $i$ 条边的权值为 $w_i$。

游戏开始时，每个顶点上可能有一颗黑棋或者一颗白棋，或者什么也没有。**至少有一个顶点上没有棋子。** 接下来，玩家需要进行若干次操作。每次的操作形式如下：

首先，选定一个上面没有棋子的顶点 $u$。可以说明，在题目数据范围下，一定存在这样的顶点。

接下来，对于每一颗棋子，若它位于顶点 $v$，则玩家需任选一条从 $v$ 到 $u$ 的**简单路径**，并将这颗棋子沿着这条简单路径移动一步。形式化地，一条简单路径为一个顶点序列 $\{p_1,p_2 \ldots p_k\}$，满足 $p_1 = v$，$p_k = u$ ，$p_1,p_2 \ldots p_k$ **互不相同**，且 $p_i$ 和 $p_{i+1}$ 之间存在一条边。在操作之后，这颗棋子将被移动至顶点 $p_2$。

需要注意的是，虽然在游戏开始时每个顶点上至多存在一颗棋子，但在若干次操作之后一个顶点上可能有多个棋子。对于同一个顶点上的不同棋子，一次操作中选取的简单路径可以不同。

玩家可以在进行任意次操作（可以是 $0$ 次）之后进行**点目**，即结算游戏分数。对于每一对颜色不同的棋子，若它们所在的顶点之间由一条权值为 $w$ 的边直接相连，则称它们**围住了这条边**，会使玩家得到 $w$ 的**目数**。而一个玩家所得到的**目数**即所有棋子对产生的**目数**之和。

现小 K 给了你一张游戏开始时的棋盘，请你帮他求出在这张棋盘上最多可能得到的**目数**。
## 输入格式

输入共 $m+k+1$ 行。

第一行三个整数 $n,m,k$，分别表示点和边的数量，以及棋子的数量。

接下来 $k$ 行，每行两个整数 $x,c$，表示顶点 $x$ 上有一颗颜色为 $c$ 的棋子。其中 $c=0$ 表示一颗黑棋，$c=1$ 表示一颗白棋。

接下来 $m$ 行每行三个整数 $u,v,w$，表示图中有一条连接 $u$ 和 $v$ 的权值为 $w$ 的边。
## 输出格式

输出一行一个整数，为所求答案。
## 样例

### 样例输入 #1
```
3 2 2
1 0
2 1
1 2 1
2 3 2

```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
4 4 3
1 1
2 1
3 0
1 2 1
2 3 1
3 4 1
4 1 3
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
见选手目录下的 alphago/alphago3.in 与 alphago/alphago3.ans。
```
### 样例输出 #3
```
见选手目录下的 alphago/alphago3.in 与 alphago/alphago3.ans。
```
### 样例输入 #4
```
见选手目录下的 alphago/alphago4.in 与 alphago/alphago4.ans。
```
### 样例输出 #4
```
见选手目录下的 alphago/alphago4.in 与 alphago/alphago4.ans。
```
### 样例输入 #5
```
见选手目录下的 alphago/alphago5.in 与 alphago/alphago5.ans。
```
### 样例输出 #5
```
见选手目录下的 alphago/alphago5.in 与 alphago/alphago5.ans。
```
## 提示

### 样例 1 解释

对于第一组样例，可以选定顶点 $3$，然后将 $1$ 号点上的黑棋移动到顶点 $2$，将 $2$ 号点的黑棋移动到顶点 $3$，这样两颗棋子所在的顶点之间由一条边权为 $2$ 的边连接，产生的目数为 $2$。

### 子任务

对于所有测试数据，保证  $3 \leq n \leq 100$，$n-1 \leq m \leq \frac{n(n-1)}{2}$，$1 \leq k \leq n-1$，$0 \leq w_i \leq 10^5$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5iu3ldkx.png)


---

