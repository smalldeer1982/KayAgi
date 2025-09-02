---
title: "[NICA #3] 图造构"
layout: "post"
diff: 提高+/省选-
pid: B3904
tag: ['图论', 'Special Judge', 'O2优化']
---
# [NICA #3] 图造构
## 题目描述

从一个 $n$ 个点的无向简单图 $S$（无自环无重边）可以通过以下步骤构造出另一个 $n$ 个点的无向简单图 $T$：

1. 初始 $T$ 中只有 $n$ 个点，没有任何边；
2. 选择 $S$ 中两个度数相同的点 $u,v$，然后在 $T$ 中连接 $u$ 和 $v$，同时将 $S$ 中的点 $u$ 以及 $u$ 连出去的边一同删去；
3. 重复步骤 $2$，直到 $S$ 中仅剩下一个点，此时得到的图 $T$ 即为构造出的图。

容易发现同样的一张无向简单图 $S$ 可能可以构造得出不同的图 $T$，并且我们还可以由构造出来的图 $T$ 继续构造图 $T'$ 等等。

现在给定两张点数相同的无向简单图 $S,T$，请你通过至少 $1$ 次且不超过 $3$ 次构造从 $S$ 构造出 $T$，**输入数据保证有解**。如果有多种方案，输出**任意一种**都会被判定为正确。

或者说你要做 $k(1\le k\le 3)$ 次构造 $S\to T_1\to T_2\to \cdots\to T_k$，满足 $T_k=T$。
## 输入格式

输入第一行一个整数 $n$，表示 $S$ 和 $T$ 中点的数量。

输入第二行一个整数 $m_S$，表示 $S$ 中边的数量。

接下来 $m_S$ 行每行两个整数 $u,v$，表示一条 $S$ 中的无向边。保证不存在重边和自环。

输入第 $m_S+3$ 行一个整数 $m_T$，表示 $T$ 中边的数量。

接下来 $m_T$ 行每行两个整数 $u,v$，表示一条 $T$ 中的无向边。同样地，保证不存在重边和自环。
## 输出格式

输出第一行一个整数 $k$，其中 $1\le k\le 3$，表示你使用的构造次数。

接下来你需要输出 $k(n-1)$ 行，每行两个整数 $u,v$，分别表示你这 $k$ 次构造的构造过程。

具体来说，对于某一次特定的构造过程，你需要输出 $n-1$ 行，表示题意中步骤 $2$ 中每次选择的两个点 $u,v$。
## 样例

### 样例输入 #1
```
3
3
1 2
2 3
3 1
2
1 2
2 3
```
### 样例输出 #1
```
1
1 2
2 3
```
## 提示

#### 样例 1 解释

初始 $T_1$ 有 $n$ 个点，没有边。

一开始 $S$ 中包含三条边 $(1,2),(2,3),(3,1)$，每个点的度数分别为 $d_1=d_2=d_3=2$。

选择 $1,2$ 这两个度数相同的点，然后将边 $(1,2)$ 加入 $T_1$，删除 $S$ 中的边 $(1,2),(3,1)$ 和点 $1$。

此时 $S$ 中包含一条边 $(2,3)$，每个点的度数分别为 $d_2=d_3=1$。

选择 $2,3$ 这两个度数相同的点，然后将边 $(2,3)$ 加入 $T_1$，删除 $S$ 中的边 $(2,3)$ 和点 $2$，并结束此次构造。

此时得到的 $T_1$ 中有两条边 $(1,2),(2,3)$，有 $T_1=T$ 满足条件。

#### 数据范围

对于所有数据，满足 $2\le n\le 10^5$，$1\le m_S,m_T\le 2\times 10^5$。


---

---
title: "「Cfz Round 3」Circle"
layout: "post"
diff: 提高+/省选-
pid: P10034
tag: ['动态规划 DP', '图论', '洛谷原创', 'Special Judge', 'O2优化', '背包 DP', '素数判断,质数,筛法', '构造', '洛谷月赛', '链表']
---
# 「Cfz Round 3」Circle
## 题目描述

给定一个长度为 $n$ 的 $\tt{01}$ 串 $S$ 和一个非负整数 $l$。

我们定义，对于一个 $1\sim n$ 的排列 $t$ 和非负整数 $k$：

$$f_{t,k}(i)=\begin{cases}i & k=0\\f_{t,k-1}(t_i) & k \neq 0\end{cases}$$

你需要构造一个 $1\sim n$ 的排列 $p$，满足：

- 对于任意一个不大于 $n$ 的正整数 $i$，都满足 $p_i \neq i$；
- 若 $S_i$ 为 $\tt1$，则 $f_{p,l}(i)=i$（若 $S_i$ 为 $\tt0$ 则没有限制）；

或报告无解。

其中，$1\sim n$ 的排列指满足所有不大于 $n$ 的正整数恰好出现一次的序列。
## 输入格式

**本题有多组测试数据。**

第一行输入一个整数 $T$，表示测试数据组数。

接下来依次输入每组测试数据。对于每组测试数据：

- 第一行输入两个整数 $n,l$。
- 第二行输入一个长度为 $n$ 的 $\tt{01}$ 串表示 $S$。
## 输出格式

对于每组数据，输出一行：

- 若存在满足条件的排列 $p$，则输出用空格分隔的 $n$ 个整数，表示你构造的排列 $p$；
- 若不存在满足条件的排列 $p$，则输出 $-1$。

**所有满足要求的输出均可通过。**
## 样例

### 样例输入 #1
```
4
5 3
10011
4 5
1000
5 6
11111
9 6
011111011
```
### 样例输出 #1
```
4 3 2 5 1
-1
5 4 2 3 1
3 1 2 6 4 5 9 7 8
```
## 提示

#### 「样例解释 #1」

对于第 $1$ 组数据，$f_{p,3}(1)=f_{p,2}(4)=f_{p,1}(5)=f_{p,0}(1)=1$，其余数同理，所以 $p$ 为 $\{4,3,2,5,1\}$ 时满足条件。

对于第 $2$ 组数据，可以证明不存在满足条件的排列 $p$。

对于第 $3$ 组数据，$\{2,1,4,5,3\}$ 等也为满足条件的排列 $p$。

#### 「数据范围」

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有数据，$1 \le T \le 100$，$2 \le n \le 5\times 10^5$，$0 \le l \le 10^{18}$，$\sum n \le 5\times 10^5$，保证 $S$ 中只包含 $\tt{0}$ 和 $\tt{1}$。

**只有你通过本题的所有测试点，你才能获得本题的分数。**


---

---
title: "[USACO24OPEN] Painting Fence Posts S"
layout: "post"
diff: 提高+/省选-
pid: P10278
tag: ['USACO', '2024', '图论建模', '差分']
---
# [USACO24OPEN] Painting Fence Posts S
## 题目背景

**注意：本题的时间限制和内存限制为 3 秒 和 512MB，分别为通常限制的 1.5 倍和 2 倍。**
## 题目描述

Farmer John 的 $N$ 头奶牛（$1\le N\le 10^5$）每头都喜欢日常沿围着牧场的栅栏散步。不幸的是，每当一头奶牛走过栅栏柱子时，她就会碰到它，这要求 Farmer John 需要定期重新粉刷栅栏柱子。

栅栏由 $P$ 根柱子组成（$4\le P\le 2\cdot 10^5$，$P$ 为偶数），每根柱子的位置是 FJ 农场地图上的一个不同的二维坐标点 $(x,y)$（$0\le x,y\le 10^9$）。每根柱子通过垂直或水平线段的栅栏连接到两根相邻的柱子，因此整个栅栏可以被视为各边平行于 $x$ 轴或 $y$ 轴的一个多边形（最后一根柱子连回第一根柱子，确保围栏形成一个包围牧场的闭环）。栅栏多边形是「规则的」，体现在栅栏段仅可能在其端点处重合，每根柱子恰好属于两个栅栏段，同时每两个在端点处相交的栅栏段都是垂直的。

每头奶牛的日常散步都有一个偏好的起始和结束位置，均为沿栅栏的某个点（可能在柱子处，也可能不在）。每头奶牛日常散步时沿着栅栏行走，从起始位置开始，到结束位置结束。由于栅栏形成闭环，奶牛有两条路线可以选择。由于奶牛是一种有点懒的生物，每头奶牛都会选择距离较短的方向沿栅栏行走。值得注意的是，这个选择总是明确的——不存在并列的情况！

一头奶牛会触碰一根栅栏柱子，当她走过这根柱子，或者当这根栅栏柱子是她散步的起点或终点时。请帮助 FJ 计算每个栅栏柱子每天所经历的触碰次数，以便他知道接下来要重新粉刷哪根柱子。

可以证明，给定所有柱子的位置，组成的栅栏仅有唯一的可能性。
## 输入格式

输入的第一行包含 $N$ 和 $P$。以下 $P$ 行的每一行包含两个整数，表示栅栏柱子的位置，没有特定的顺序。以下 $N$ 行的每一行包含四个整数 $x_1\ y_1\ x_2\ y_2$，表示一头奶牛的起始位置 $(x_1,y_1)$ 和结束位置 $(x_2,y_2)$。
## 输出格式

输出 $P$ 个整数，包含每个栅栏柱子所经历的触碰次数。
## 样例

### 样例输入 #1
```
5 4
3 1
1 5
3 5
1 1
2 1 1 5
1 5 3 4
3 1 3 5
2 1 2 1
3 2 3 3
```
### 样例输出 #1
```
1
2
2
1
```
### 样例输入 #2
```
2 8
1 1
1 2
0 2
0 3
0 0
0 1
2 3
2 0
1 1 2 1
1 0 1 3
```
### 样例输出 #2
```
1
0
0
0
1
1
1
2
```
### 样例输入 #3
```
1 12
0 0
2 0
2 1
1 1
1 2
3 2
3 3
1 3
1 4
2 4
2 5
0 5
2 2 0 2
```
### 样例输出 #3
```
1
1
1
1
1
0
0
0
0
0
0
0
```
## 提示

### 样例解释 1

柱子以如下方式由栅栏段连接：

$$
(3,1)\leftrightarrow(3,5)\leftrightarrow(1,5)\leftrightarrow(1,1)\leftrightarrow(3,1)
$$

各奶牛接触的柱子如下：

1. 柱子 $2$ 和 $4$。
2. 柱子 $2$ 和 $3$。
3. 柱子 $1$ 和 $3$。
4. 无。
5. 无。

### 测试点性质

- 测试点 $4-6$：$N,P\le 1000$。
- 测试点 $7-9$：所有位置均有 $0\le x,y\le 1000$。
- 测试点 $10-15$：没有额外限制。


---

---
title: "[NOIP 2009 提高组] 最优贸易"
layout: "post"
diff: 提高+/省选-
pid: P1073
tag: ['动态规划 DP', '搜索', '图论', '2009', 'NOIP 提高组', '最短路', '强连通分量']
---
# [NOIP 2009 提高组] 最优贸易
## 题目背景

本题原题数据极弱，Subtask 0 中的测试点为原题测试点，Subtask 1 中的测试点为 Hack 数据。
## 题目描述

$C$ 国有 $n$ 个大城市和 $m$ 条道路，每条道路连接这 $n$ 个城市中的某两个城市。任意两个城市之间最多只有一条道路直接相连。这 $m$ 条道路中有一部分为单向通行的道路，一部分为双向通行的道路，双向通行的道路在统计条数时也计为 $1$ 条。

$C$ 国幅员辽阔，各地的资源分布情况各不相同，这就导致了同一种商品在不同城市的价格不一定相同。但是，同一种商品在同一个城市的买入价和卖出价始终是相同的。

商人阿龙来到 $C$ 国旅游。当他得知同一种商品在不同城市的价格可能会不同这一信息之后，便决定在旅游的同时，利用商品在不同城市中的差价赚回一点旅费。设 $C$ 国 $n$ 个城市的标号从 $1\sim n$，阿龙决定从 $1$ 号城市出发，并最终在 $n$ 号城市结束自己的旅行。在旅游的过程中，任何城市可以重复经过多次，但不要求经过所有 $n$ 个城市。阿龙通过这样的贸易方式赚取旅费：他会选择一个经过的城市买入他最喜欢的商品――水晶球，并在之后经过的另一个城市卖出这个水晶球，用赚取的差价当做旅费。由于阿龙主要是来 $C$ 国旅游，他决定这个贸易只进行最多一次，当然，在赚不到差价的情况下他就无需进行贸易。

假设 $C$ 国有 $5$ 个大城市，城市的编号和道路连接情况如下图，单向箭头表示这条道路为单向通行，双向箭头表示这条道路为双向通行。

![](https://cdn.luogu.com.cn/upload/image_hosting/flre534z.png)

假设 $1\sim n$ 号城市的水晶球价格分别为 $4,3,5,6,1$。

阿龙可以选择如下一条线路：$1\to2\to3\to5$，并在 $2$ 号城市以 $3$ 的价格买入水晶球，在 $3$ 号城市以 $5$ 的价格卖出水晶球，赚取的旅费数为 $2$。

阿龙也可以选择如下一条线路：$1\to4\to5\to4\to5$，并在第 $1$ 次到达 $5$ 号城市时以 $1$ 的价格买入水晶球，在第 $2$ 次到达 $4$ 号城市时以 $6$ 的价格卖出水晶球，赚取的旅费数为 $5$。

现在给出 $n$ 个城市的水晶球价格，$m$ 条道路的信息（每条道路所连接的两个城市的编号以及该条道路的通行情况）。请你告诉阿龙，他最多能赚取多少旅费。
## 输入格式

第一行包含 $2$ 个正整数 $n$ 和 $m$，中间用一个空格隔开，分别表示城市的数目和道路的数目。

第二行 $n$ 个正整数，每两个整数之间用一个空格隔开，按标号顺序分别表示这 $n$ 个城市的商品价格。

接下来 $m$ 行，每行有 $3$ 个正整数 $x,y,z$，每两个整数之间用一个空格隔开。如果 $z=1$，表示这条道路是城市 $x$ 到城市 $y$ 之间的单向道路；如果 $z=2$，表示这条道路为城市 $x$ 和城市 $y$ 之间的双向道路。


## 输出格式

一个整数，表示最多能赚取的旅费。如果没有进行贸易，则输出 $0$。
## 样例

### 样例输入 #1
```
5 5 
4 3 5 6 1 
1 2 1 
1 4 1 
2 3 2 
3 5 1 
4 5 2 
```
### 样例输出 #1
```
5
```
## 提示

【数据范围】

输入数据保证 $1$ 号城市可以到达 $n$ 号城市。

对于 $10\%$ 的数据，$1\leq n\leq 6$。

对于 $30\%$ 的数据，$1\leq n\leq 100$。

对于 $50\%$ 的数据，不存在一条旅游路线，可以从一个城市出发，再回到这个城市。

对于 $100\%$ 的数据，$1\leq n\leq 100000$，$1\leq m\leq 500000$，$1\leq  x,y\leq  n$，$1\leq  z\leq  2$，$1\leq $ 各城市的编号 $\leq  n$。

水晶球价格 $\leq 100$。

NOIP 2009 提高组 第三题


---

---
title: "「SFMOI Round I」Strange Train Game"
layout: "post"
diff: 提高+/省选-
pid: P11146
tag: ['贪心', '并查集', '洛谷原创', 'O2优化', '图论建模', '线性基', '随机化', '洛谷月赛']
---
# 「SFMOI Round I」Strange Train Game
## 题目背景

[English statement](https://www.luogu.com.cn/problem/T512993). **You must submit your code at the Chinese version of the statement.**

SFM 团队又断网了，于是玩起了 Mini Metro，结果发现游戏更新了，列车要自己组装，于是有了这题。


## 题目描述

**提示**：我们在题目描述的最后提供了一份简要的、形式化描述的题面。

SFM 号列车由 $n$ 节车厢组成，编号为 $1\sim n$。每节车厢有一个舒适度 $a_i\in \{0,1\}$，$0$ 代表不舒适，$1$ 代表舒适。管理组想要让舒适的车厢的编号尽量小，也就是说，让 $a$ 的字典序最大。

为此，管理组运来了一辆 $n$ 节车厢的备用车，舒适度表示为 $b_i\in \{0,1\}$。共有 $m$ 个可进行的操作，第 $i$ 个操作的操作参数为 $l_i,r_i$，表示 $\forall l_i\le k\le r_i$，交换 $a_k,b_k$。

可以**从小到大依次**决定是否执行每个操作，但是一共有 $2^m$ 种方案，于是，管理组找来了你，帮忙选出一种最优的方案，最大化 $a$ 的字典序。只需要输出最终得到的 $a$ 即可。

**形式化地**：给定长度为 $n$ 的 $01$ 串 $a,b$，给定 $2m$ 个正整数 $l_i,r_i$。对于 $i=1,2,\cdots,m$，**依次**执行以下操作：
- 选择是否执行第 $i$ 次操作。
    - 如果执行，则对于 $k=l_i,l_{i}+1,\cdots,r_i$，交换 $a_k,b_k$。

最大化 $a$ 的字典序并输出最终的结果。

## 输入格式

第一行，两个正整数 $n,m$，表示字符串的长度和操作次数。

第二行，一个长度为 $n$ 的 $01$ 串 $a$。

第三行，一个长度为 $n$ 的 $01$ 串 $b$。

接下来 $m$ 行，每行两个正整数 $l_i,r_i$，描述第 $i$ 个操作。

## 输出格式

输出一行长度为 $n$ 的 $01$ 串，表示最优操作后的 $a$。

## 样例

### 样例输入 #1
```
10 5
0101011001
0101001110
5 10
2 6
1 10
6 6
3 4
```
### 样例输出 #1
```
0101011110
```
## 提示

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$1\le n,m\le 20$；
- Subtask 2（30 pts）：$l_i$ 互不相同，$a_i \ne b_i$；
- Subtask 3（30 pts）：$1 \le n ,m \le 10^3$；
- Subtask 4（20 pts）：无限制；

对于 $100\%$ 的数据，保证：
- $1\le n,m\le 2\times 10^5$；
- $1\le l_i\le r_i\le n$。


---

---
title: "「CMOI R1」图上交互题 / Constructive Minimum Xor Path"
layout: "post"
diff: 提高+/省选-
pid: P11170
tag: ['数学', '图论', '2024', '洛谷原创', 'Special Judge', 'O2优化', '构造', 'Ad-hoc']
---
# 「CMOI R1」图上交互题 / Constructive Minimum Xor Path
## 题目背景

2024 年 1 月 13 日 15:59:31，随着最后一发交互 J 题的提交出现了 Wrong Answer，小 G 的 EC-Final 比赛结束了，也意味着在 ICPC 生涯中第一次打铁。

痛定思痛，小 G 决定批量生产交互题给自己做。如何批量生产交互题？只要在一个数据结构中有若干个未知量 $a_i$，每次询问给定向量 $x$，交互库会返回关于 $a_i$ 的函数 $f(x)$，这样就能批量生产交互题了！

~~那为什么这题并不是交互题呢。~~
## 题目描述

给定一个 $n$ 个点，$m$ 条边的**无向图**。第 $i$ 条边 $(u_i,v_i)$ 有一个**未知边权** $a_i$。

对于任何一条**路径**，定义其**代价**如下：设路径为 $(p_0,p_1,...,p_k)$，其中要求 $(p_{i-1},p_i)$ 是无向图中的边，设其为第 $e_i$ 条边。那么路径的代价即为 $\bigoplus\limits_{i=1}^{k} a_{e_i}$。其中 $\bigoplus$ 表示异或。（该路径可以经过重复点和重复边，即 $p$ 和 $e$ 可以包含重复的数）



定义 $f(x,y)$ 为从 $x$ 到 $y$ 的所有路径中代价的**最小值**。特别地，当 $x=y$ 时，$f(x,y)=0$。

给定 $n,m$，再对于每条边 $(u_i,v_i)$ 给定 $f(u_i,v_i)$，你需要求出是否存在一组合法的 $a_i$，如果有解，你还需要构造一组解。
## 输入格式

第一行两个正整数 $n,m$。

第 $2\sim m+1$ 行每行两个正整数 $u_i,v_i$ 和一个非负整数 $f(u_i,v_i)$。

**请注意：本题并不保证图连通；可能会存在重边和自环。**
## 输出格式

如果不存在解，则仅输出 `No`。

否则，在第一行输出 `Yes`，在第二行输出 $m$ 个非负整数 $a_i$ 表示一组合法的解。

答案可能有很多组，此时输出任意一组解即可。你需要保证 输出的 $0\le a_i<2^{63}$。
## 样例

### 样例输入 #1
```
3 3
1 2 2
2 3 3
3 1 1
```
### 样例输出 #1
```
Yes
2 3 114514
```
### 样例输入 #2
```
1 1
1 1 1
```
### 样例输出 #2
```
No
```
## 提示

### 样例解释

答案输出的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/mq5jwia3.png)

考虑 $f(1,2)$：

+ 考虑路径 $1\rightarrow 2$，路径的代价为 $2$。

+ 考虑路径 $1\rightarrow 2\rightarrow 3\rightarrow 1\rightarrow 2$，路径的代价为 $2\oplus3\oplus114514\oplus2=114513$。

此外还存在其他路径，但可以证明不存在代价比 $2$ 更小的路径，故 $f(1,2)=2$。

### 数据范围

**本题采用捆绑测试。**

|$\text{Subtask}$ |特殊性质|分数|
|-:|-:|-:|
|$1$|保证有解|$20$|
|$2$|$m\le n+10$|$30$|
|$3$||$50$|

对于 $100\%$ 的数据，$1\le n,m\le 5\times 10^5$，$1\le u_i,v_i\le n$，$0\le f(u_i,v_i)<2^{31}$。


---

---
title: "词链"
layout: "post"
diff: 提高+/省选-
pid: P1127
tag: ['搜索', '图论']
---
# 词链
## 题目描述

如果单词 $X$ 的末字母与单词 $Y$ 的首字母相同，则 $X$ 与 $Y$ 可以相连成 $X.Y$。（注意：$X$、$Y$ 之间是英文的句号 `.`）。例如，单词 `dog` 与单词 `gopher`，则 `dog` 与 `gopher` 可以相连成 `dog.gopher`。

另外还有一些例子：
- `dog.gopher`
- `gopher.rat`
- `rat.tiger`
- `aloha.aloha`
- `arachnid.dog`

连接成的词可以与其他单词相连，组成更长的词链，例如：

`aloha.arachnid.dog.gopher.rat.tiger`

注意到，`.` 两边的字母一定是相同的。

现在给你一些单词，请你找到字典序最小的词链，使得每个单词在词链中出现且仅出现一次。注意，相同的单词若出现了 $k$ 次就需要输出 $k$ 次。
## 输入格式

第一行是一个正整数 $n$（$1 \le n \le 1000$），代表单词数量。

接下来共有 $n$ 行，每行是一个由 $1$ 到 $20$ 个小写字母组成的单词。
## 输出格式

只有一行，表示组成字典序最小的词链，若不存在则只输出三个星号 `***`。

## 样例

### 样例输入 #1
```
6
aloha
arachnid
dog
gopher
rat
tiger
```
### 样例输出 #1
```
aloha.arachnid.dog.gopher.rat.tiger
```
## 提示

- 对于 $40\%$ 的数据，有 $n \leq 10$；
- 对于 $100\%$ 的数据，有 $n \leq 1000$。



---

---
title: "[NOISG 2018 Prelim]  Island"
layout: "post"
diff: 提高+/省选-
pid: P11298
tag: ['数学', '图论', '2018', 'Special Judge', 'NOISG（新加坡）']
---
# [NOISG 2018 Prelim]  Island
## 题目背景

翻译自 [NOISG 2018 Prelim C. Island](https://github.com/noisg/sg_noi_archive/tree/master/2018_prelim)。

**本题已启用 Special Judge，满足题目条件的任何答案都将视为正确。保证 SPJ 用时不超过 $1$ 秒**。
## 题目描述

老鼠吱吱发现了一座小岛，这座小岛上的人以捕鱼为生，所以他们的 $n$ 所房子（标号为 $1$ 到 $n$）都在小岛的**边缘**，大家还需要交换各自的鱼，所以有些路在小岛的中间。

为了连接城镇，在岛的内部创建了 $m$ 个路口（标号为 $n+1$ 到 $n+m$）。为了最大限度地降低建设成本，这个岛上**只有 $n+m−1$ 条路**，这样任何两个城镇之间就有且仅有一条路。

换言之，道路网络可以**表示为一棵树**，有 $n$ 个叶子（代表 $n$  所房子）和 $m$ 个非叶子节点（代表 $m$ 个路口）。根据树的性质，这棵树有 $n+m−1$条边（代表 $n+m-1$ 条路）。

此外，**每个路口至少有三条路与之相连**，除了路口外，路不会与其他路相交，也没有桥梁或隧道（它们很贵）。以下是一个有 $37$ 所房子、$20$ 个路口和 $56$ 条道路的岛的参考图：

![](https://cdn.luogu.com.cn/upload/image_hosting/h32hwja1.png)

老鼠吱吱很喜欢这座小岛，但是因为某种原因，它的地图被吹走了。但是吱吱想规划它的行程，所以他想知道小岛房子的位置。

幸运的是，它记录了**每一条道路的起点和终点**的观察记录本还在，现在请你推出，共有几种不同的情况使得小岛房子的位置不同。

**注意小岛是环形的，经过旋转完全一样的顺序视为同一种顺序**。
## 输入格式

第一行两个整数 $n,m$。

接下来 $n+m-1$ 行，每行两个整数 $u,v$，表示这条道路的起点与终点。如 $u \leq n$，则起点是一所房子，否则是一个路口。对 $v$ 同理。
## 输出格式

若干行，第 $i$ 行两个整数 $a_i,b_i$。

假设你的答案由 $k$ 行构成。你的输出表示 答案 $P=a_1^{b_1}a_2^{b_2}\cdots a_k^{b_k}$（也可记作 $\prod_{j=1}^ka_j^{b_j}$）。

你的输出应满足以下要求：
- $0\leq k\leq 10^6$
- $1\leq a_i,b_i\leq 10^{18}$

**如果无解，请什么都不要输出**。
## 样例

### 样例输入 #1
```
5 2
1 7
3 7
6 2
7 4
6 7
5 6
```
### 样例输出 #1
```
3 1
4 1
```
### 样例输入 #2
```
5 1
6 1
6 2
6 3
6 4
6 5
```
### 样例输出 #2
```
3 1
2 3
```
### 样例输入 #3
```
6 3
7 1
7 2
8 3
8 4
9 5
9 6
7 8
9 8
```
### 样例输出 #3
```
24 1
```
## 提示

### 【样例 #1 解释】
有 $12$ 种合法的排列，如下图。

使用其他的方式（如 $4^1\times3^1$）也是可以的。

所有排列如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/847a8hm5.png)
### 【样例 #2 解释】
有 $24$ 种合法的排列，其中一种如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/xrc1rdel.png)

算出答案是 $5!=120$ 的很有可能是因为没有考虑旋转后一样的视为同一种方案的问题。
### 【样例 #3 解释】
有 $24$ 种合法的排列，其中一种如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/d7xgyycj.png)
### 【数据范围】
| $\text{Subtask}$ | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: |
| $0$ | $0$ | 样例 |
| $1$ | $7$ | $n+m\leq 2\times 10^5,m\leq1$ |
| $2$ | $20$ | $n+m\leq 2\times 10^5,m\leq10$ |
| $3$ | $31$ | $n+m\leq 10^3$ |
| $4$ | $42$ | $n+m\leq 2\times 10^5$ |

对于 $100\%$ 的数据：
- $2 \leq n,0\leq m$
- $n+m \leq 2\times10^5$


---

---
title: "[USACO24DEC] 2D Conveyer Belt S"
layout: "post"
diff: 提高+/省选-
pid: P11454
tag: ['图论', 'USACO', '2024']
---
# [USACO24DEC] 2D Conveyer Belt S
## 题目描述

Farmer John 的牛奶工厂可以用一个 $N\times N$（$1≤N≤1000$）的方阵来表示，其中的方格带有传送带。位置 $(a,b)$ 描述了位于从上往下第 $a$ 行、从左往右第 $b$ 列的方格。有 $5$ 种类型的方格：

- $\texttt{L}$ — 该方格是一个向左的传送带，每一单位时间会将所有物品向左移动一格。
- $\texttt{R}$ — 该方格是一个向右的传送带，每一单位时间会将所有物品向右移动一格。
- $\texttt{U}$ — 该方格是一个向上的传送带，每一单位时间会将所有物品向上移动一格。
- $\texttt{D}$ — 该方格是一个向下的传送带，每一单位时间会将所有物品向下移动一格。
- $\texttt{?}$ — Farmer John 还没有在该方格上建造传送带。
注意传送带也可以将物品移动到方阵外。一个方格 $c$ 是不可用的，当且仅当一个放置在方格 $c$ 上的物品将永远不会离开传送带方阵（即它会永远在方阵中移动）。

初始时，Farmer John 还没有开始建造传送带，所以所有方格都以 $\texttt{?}$ 开始。接下来的 $Q$（$1≤Q≤2⋅10^5$）天，从第 $1$ 天开始到第 $Q$ 天，Farmer John 将选择一个没有传送带的方阵并在该方阵上建造一个传送带。

具体地说，在第 $i$ 天，Farmer John 将在位置 $(r_i,c_i)$（$1≤r_i,c_i≤N$）建造一个类型 $t_i$（$t_i\in\{\texttt{L},\texttt{R},\texttt{U},\texttt{D}\}$）的传送带。输入保证在位置 $(r_i,c_i)$ 没有传送带。

每天过后，请帮助 Farmer John 求出他通过最优地在所有余下的没有传送带的方格上建造传送带可以达到的不可用方格的最小数量。
## 输入格式

输入的第一行包含 $N$ 和 $Q$。

以下 $Q$ 行，第 $i$ 行依次包含 $r_i$，$c_i$ 和 $t_i$。
## 输出格式

输出 $Q$ 行，每行包含 Farmer John 最优地在所有余下的没有传送带的方格上建造传送带时不可用方格的最小数量。
## 样例

### 样例输入 #1
```
3 5
1 1 R
3 3 L
3 2 D
1 2 L
2 1 U
```
### 样例输出 #1
```
0
0
0
2
3
```
### 样例输入 #2
```
3 8
1 1 R
1 2 L
1 3 D
2 3 U
3 3 L
3 2 R
3 1 U
2 1 D
```
### 样例输出 #2
```
0
2
2
4
4
6
6
9
```
### 样例输入 #3
```
4 13
2 2 R
2 3 R
2 4 D
3 4 D
4 4 L
4 3 L
4 2 U
3 1 D
4 1 R
2 1 L
1 1 D
1 4 L
1 3 D
```
### 样例输出 #3
```
0
0
0
0
0
0
0
0
11
11
11
11
13
```
## 提示

### 样例 #1 解释

第五天过后的传送带如下所示。

$$\begin{aligned}
\texttt{RL?}\\
\texttt{U??}\\
\texttt{?DL}\\
\end{aligned}
$$
一种在余下的方格上建造传送带的最优方案如下。

$$\begin{aligned}
\texttt{RLR}\\
\texttt{URR}\\
\texttt{LDL}\\
\end{aligned}
$$
在这种配置下，位于 $(1,1)$，$(1,2)$ 和 $(2,1)$ 的方格是不可用的。

### 样例 2 解释

第八天过后的传送带如下所示。

$$\begin{aligned}
\texttt{RLD}\\
\texttt{D?U}\\
\texttt{URL}\\
\end{aligned}
$$

无论 Farmer John 在中间建造何种传送带，所有方格都将是不可用的。

### 测试点性质

- 测试点 1-3：样例。
- 测试点 4-5：$N≤10$。
- 测试点 6-7：$N≤40$。
- 测试点 8-13：没有额外限制。


---

---
title: "[NOIP 2008 提高组] 双栈排序"
layout: "post"
diff: 提高+/省选-
pid: P1155
tag: ['图论', '2008', 'NOIP 提高组', '二分图']
---
# [NOIP 2008 提高组] 双栈排序
## 题目描述

Tom 最近在研究一个有趣的排序问题。如图所示，通过 $2$ 个栈 $S_1$ 和 $S_2$，Tom 希望借助以下 $4$ 种操作实现将输入序列升序排序。

![](https://cdn.luogu.com.cn/upload/image_hosting/gwxu91ud.png)

- 操作 $\verb!a!$：将第一个元素压入栈 $S_1$。
- 操作 $\verb!b!$：将 $S_1$ 栈顶元素弹出至输出序列。
- 操作 $\verb!c!$：将第一个元素压入栈 $S_2$。
- 操作 $\verb!d!$：将 $S_2$ 栈顶元素弹出至输出序列。


如果一个 $1\sim n$ 的排列 $P$ 可以通过一系列合法操作使得输出序列为 $(1,2,\cdots,n-1,n)$，Tom 就称 $P$ 是一个“可双栈排序排列”。例如 $(1,3,2,4)$ 就是一个“可双栈排序序列”，而 $(2,3,4,1)$ 不是。下图描述了一个将 $(1,3,2,4)$ 排序的操作序列：$\texttt {a,c,c,b,a,d,d,b}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jwdjwfee.png)

当然，这样的操作序列有可能有几个，对于上例 $(1,3,2,4)$，$\texttt{a,b,a,a,b,b,a,b}$ 是另外一个可行的操作序列。Tom 希望知道其中字典序最小的操作序列是什么。
## 输入格式

第一行是一个整数 $n$。

第二行有 $n$ 个用空格隔开的正整数，构成一个 $1\sim n$ 的排列。
## 输出格式

共一行，如果输入的排列不是“可双栈排序排列”，输出 `0`。

否则输出字典序最小的操作序列，每两个操作之间用空格隔开，行尾没有空格。
## 样例

### 样例输入 #1
```
4
1 3 2 4
```
### 样例输出 #1
```
a b a a b b a b
```
### 样例输入 #2
```
4
2 3 4 1
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
3
2 3 1
```
### 样例输出 #3
```
a c a b b d
```
## 提示

$30\%$ 的数据满足：$n\le10$。

$50\%$ 的数据满足：$n\le50$。

$100\%$ 的数据满足：$n\le1000$。

2021.06.17 加强 by [SSerxhs](https://www.luogu.com.cn/user/29826)。hack 数据单独分为一个 subtask 防止混淆。

noip2008 提高第四题


---

---
title: "【MX-X7-T5】[LSOT-3] 你的列车是生存战略"
layout: "post"
diff: 提高+/省选-
pid: P11564
tag: ['O2优化', '图论建模', '最短路', '梦熊比赛']
---
# 【MX-X7-T5】[LSOT-3] 你的列车是生存战略
## 题目背景

原题链接：<https://oier.team/problems/X7F>。

>啊啊 我搭上了那趟列车$\\$无论被业火灼烧多少次$\\$或是化作灰烬$\\$为何我要如此$\\$因为这是通往你的道路$\\$就算事与愿违也好$\\$还是听天由命也罢$\\$我将要改写这个世界$\\$
## 题目描述

Ringo 要带着企鹅罐乘坐列车前往命运所至之地寻找 Shyouma 并且完成命运换乘！

她可以通过乘坐列车在冰之世界的 $n$ 个车站中穿行，车站编号为 $1 \sim n$。

每一个车站都有两个标号，第 $i$ 个车站的标号分别为 $c_i$ 和 $d_i$。

冰之世界中一共有普通列车和特快列车两种列车。

- 任意两地之间都有一条**可以往返**的普通列车的线路，车站 $i$ 与车站 $j$ 之间的线路所花费的时间为 $\min(a_{c_i \mathbin{|} c_j},b_{d_i \mathbin{\&} d_j})$（$\mathbin{|}$ 表示按位或，$\mathbin{\&}$ 表示按位与）。**保证 $\boldsymbol{a}$ 单调不降，$\boldsymbol{b}$ 单调不升。**
- 特快列车一共有 $m$ 条线路，第 $i$ 条是从车站 $u_i$ **驶向**车站 $v_i$ 的**单向线路**，所花费的时间为 $w_i$。


Ringo 希望能更快找到 Shyouma，不然世界就要毁灭了！

Ringo 开始的时候在车站 $1$，但是她不知道命运所至之地到底在哪里。所以她想知道对于每一个车站，如果 Shyouma 在那里，她最少需要花多少时间到达 Shyouma 所在的位置。
## 输入格式

第一行，三个非负整数 $n, m, k$。其中 $k$ 表示 $c_i, d_i \in [0,2^k)$。

第二行，$n$ 个非负整数 $c_1, \ldots, c_n$。

第三行，$n$ 个非负整数 $d_1, \ldots, d_n$。

第四行，$2^k$ 个非负整数 $a_0, \ldots, a_{2^k - 1}$。

第五行，$2^k$ 个非负整数 $b_0, \ldots, b_{2^k - 1}$。

**保证 $\boldsymbol{a}$ 单调不降，$\boldsymbol{b}$ 单调不升。**

接下来 $m$ 行，第 $i$ 行三个非负整数 $u_i, v_i, w_i$。
## 输出格式

仅一行，$n$ 个整数，第 $i$ 个表示从车站 $1$ 到车站 $i$ 所花费的最少的时间。
## 样例

### 样例输入 #1
```
5 4 3
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5 7 7 8
8 7 6 5 4 3 2 1
1 2 5
2 3 4
3 4 2
4 5 3

```
### 样例输出 #1
```
0 4 4 6 7

```
### 样例输入 #2
```
40 40 5
31 30 28 30 30 24 31 16 28 24 16 28 31 24 17 31 31 28 5 16 4 16 24 9 8 16 28 28 24 30 16 28 24 31 16 2 16 28 28 24
24 7 21 15 16 18 30 15 23 24 29 12 2 14 11 0 5 27 10 23 11 28 27 21 1 1 28 21 11 18 31 23 1 18 23 22 22 9 1 4
0 102 102 102 102 102 260 260 260 260 601 601 601 601 601 601 601 601 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264 1264
108799 106048 100679 98235 95333 90350 80153 79411 70293 69091 64328 58817 55536 53256 42932 42687 41145 40487 40047 37901 32251 29823 26460 25786 21684 20508 19995 19172 18248 12890 12397 10740
38 27 0
17 3 3
26 8 12
12 11 14
1 23 8
4 7 6
18 36 18
1 33 6
38 18 8
19 38 17
24 21 4
31 16 18
26 4 8
5 31 1
6 28 4
9 10 7
26 7 7
8 37 19
40 29 4
24 9 0
15 6 19
39 12 18
33 39 8
10 34 0
39 30 3
28 25 5
19 13 9
6 2 0
1 20 10
19 17 8
15 26 18
17 13 18
33 40 8
40 22 15
15 28 0
17 35 10
24 5 13
18 14 19
40 22 2
6 32 13

```
### 样例输出 #2
```
0 630 993 619 889 630 618 611 876 883 46 32 991 1026 611 629 990 1007 982 10 880 16 8 876 616 611 999 611 18 17 611 643 6 883 611 1025 611 999 14 14

```
## 提示

> 生存戦略、しましょうか

**【样例解释 #1】**

Ringo 开始的时候就在车站 $1$，所以到车站 $1$ 最少的花费的时间为 $0$。

到车站 $2$ 的花费最少时间的路径为乘坐从 $1$ 到 $2$ 的普通列车，花费的时间为 $\min(a_{c_1 \mathbin{|} c_2},b_{d_1 \mathbin{\&} d_2})=\min(a_3,b_0)=\min(4,8)=4$。

到车站 $3$ 的花费最少时间的路径为乘坐从 $1$ 到 $3$ 的普通列车，花费的时间为 $4$。


到车站 $4$ 的花费最少时间的路径为乘坐从 $1$ 到 $3$ 的普通列车，花费的时间为 $4$，随后乘坐第 $3$ 条特快列车花费 $2$ 的时间从 $3$ 到 $4$，总花费时间为 $4+2=6$。


到车站 $5$ 的花费最少时间的路径为乘坐从 $1$ 到 $5$ 的普通列车，花费的时间为 $7$。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（10 分）：$n\le 1000$。
- 子任务 2（10 分）：$k=0$。
- 子任务 3（20 分）：$a_i=i$，$b_i=10^{18}$。
- 子任务 4（20 分）：$m=0$，$n \ge 2$，$c_{n-1}=d_{n-1}=0$，$c_n=d_n=2^k-1$。
- 子任务 5（20 分）：$n=m=2^k$。
- 子任务 6（20 分）：无特殊限制。

对于全部的数据，$1\le n\le 10^6$，$0\le m\le10^6$，$0\le k\le 14$，$0\le c_i,d_i< 2^k$，$0\le a_i,b_i,w_i\le 10^{18}$，$1\le u_i,v_i\le n$，$a$ 单调不降，$b$ 单调不升。


---

---
title: "[PA 2016] 卡牌 / Gra w karty"
layout: "post"
diff: 提高+/省选-
pid: P11604
tag: ['贪心', '2016', '图论建模', '二分图', 'Ad-hoc', 'PA（波兰）']
---
# [PA 2016] 卡牌 / Gra w karty
## 题目背景

译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R1 Gra w karty [A] (KAR)。$\texttt{1s,256M}$。

## 题目描述


Alice 和 Bob 各有 $n$ 张卡牌。每个人的卡牌都被编号为 $1\sim n$。

现在玩 $(n-1)$ 局游戏：每局游戏中，Alice 先弃掉 Bob 的一张牌，然后 Bob 再弃掉 Alice 的一张牌。

最终两人都只剩下一张牌。

有 $m$ 对关系，形如「若 Alice 最后剩下的牌为 $x$，Bob 最后剩下的牌为 $y$，则 Alice 胜/负 Bob」。特别地，未给出的关系为平局。

若双方都用最优策略游戏，Alice 最终会胜/负 Bob 还是平局？

「最佳策略」指的是：若有必胜策略，则选择必胜策略；否则若有平局策略，选择平局策略。
## 输入格式


**本题单个测试点内有多组测试数据。**

第一行，一个正整数 $T$。接下来描述 $T$ 组测试数据：

每组数据第一行，两个整数 $n,m$。

接下来 $m$ 行，每行两个正整数和一个字符 $x,w,y$，其中 $w\in \{\texttt{<},\texttt{>}\}$，$x,y$ 为正整数。
- 若 $w=\texttt{>}$，则表示「若 Alice 最后剩下的牌为 $x$，Bob 最后剩下的牌为 $y$，则 Alice 胜 Bob」；
- 若 $w=\texttt{<}$，则表示「若 Alice 最后剩下的牌为 $x$，Bob 最后剩下的牌为 $y$，则 Alice 负 Bob」。

保证不会出现自相矛盾的关系。

## 输出格式


输出 $T$ 行，每行一个字符串：
- 若 Alice 有必胜策略，输出 $\texttt{WYGRANA}$；
- 否则，若 Alice 有平局策略，输出 $\texttt{REMIS}$；
- 否则，输出 $\texttt{PRZEGRANA}$。

## 样例

### 样例输入 #1
```
3
5 5
5 > 5
1 > 5
3 > 5
4 > 5
2 > 5
2 2
1 > 1
1 > 2
1 1
1 < 1
```
### 样例输出 #1
```
WYGRANA
REMIS
PRZEGRANA
```
## 提示


- $1\le T\le 20$；
- $1\le n\le 10^5$；
- $0\le m\le 2\times 10^5$；
- $1\le x,y\le n$；
- $w\in \{\texttt{<},\texttt{>}\}$。

保证不会出现自相矛盾的关系，也不会重复给出一个关系。


---

---
title: "[IAMOI R1] 走亲访友"
layout: "post"
diff: 提高+/省选-
pid: P11762
tag: ['图论', 'Special Judge', '欧拉回路']
---
# [IAMOI R1] 走亲访友
## 题目背景

小 C 拉小 L 去走亲戚。
## 题目描述

小 C 共有 $n$ 个亲戚，某些亲戚家之间有 $m$ 条双向的道路，保证亲戚家之间两两可达。

小 C 要亲自去走亲戚。具体的，小 C 一开始在第 $s$ 个亲戚家。每次她可以前往一个与她现在的位置有道路相连的亲戚家。然而小 C 太有魅力了。每当她走过一条道路时，追求她的人便会从四面八方涌来，导致这条路堵车。当然，她也可以躲在车里面，收起她的迷人魅力，这样这条路就不会堵车了。

因为小 L 是路痴，所以小 C 希望最后剩下尽量少的 $n-1$ 条没有堵车的道路，并使得只保留着 $n-1$ 条道路后，亲戚家之间仍两两可达。

因为小 C 不想四处奔波这么久，所以最多只会走过 $k$ 条道路。

请你为她输出一种走亲戚的方案。

### 形式化题意

给定一个 $n$ 个点 $m$ 条边的简单无向连通图，你需要构造一组满足下面要求的路径：

+ 起点为 $s$，终点不限。

+ 对于走过的每一组边 $(u_i,v_i)$，你需要额外决定 $p_i\in\{0,1\}$，满足：

1. $p_i=0$ 表示删除这条边，**且不能再使用，即之后不能再次经过这条边**；$p_i=1$ 表示不删除这条边。

2. 如果 $i>1$，那么 $u_i=v_{i-1}$。**即使 $p_i=0$，也需要满足这条限制。**

+ 路径的长度不能超过 $k$。

+ 最后未删除的边组成一棵 $n$ 个节点的树。

特别的，一组边在被删除前可以经过多次。

若有多组满足条件的路径，可以输出任意一组。

可以证明在本题的限制条件下，一定存在合法的方案。
## 输入格式

第一行输入四个整数 $n,m,k$ 和 $s$。

接下来 $m$ 行每行输入整数 $u$ 和 $v$，表示第 $u$ 个亲戚家和第 $v$ 个亲戚家之间有一条双向道路。
## 输出格式

第一行输出一个整数，表示走过的道路的数量。

接下来若干行输出你的方案。具体的，每行输出两个整数。第一个整数表示道路的编号，第二个整数的值为 $0$ 或 $1$，若是 $0$ 表示让这条路堵车（删除这条边），若是 $1$ 表示让这条路保持畅通（保留这条边）。

如果有多种方案，任意输出一种也将被视为正确。
## 样例

### 样例输入 #1
```
5 5 10 4
1 3
2 5
2 3
4 5
1 5
```
### 样例输出 #1
```
2
4 1
2 0
```
## 提示

### 样例解释
![](https://cdn.luogu.com.cn/upload/image_hosting/qr0blgk5.png)

首先我们从第 $4$ 条道路后到达 $5$ 号亲戚家，再通过第 $2$ 条道路到达 $2$ 号亲戚，并让第 $2$ 条道路堵车。此时，只剩下 $n-1$ 条没有堵车的道路，并且亲戚家之间仍然两两可达。

对于以下输出：

```
2
4 1
5 0
```

或者以下输出：

```
3
4 1
2 1
3 0
```

也将视作正确。
### 数据范围

**本题采用捆绑测试**。

| Subtask | $n\le$ | $m$ | $k=$ | 分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $10$ | $\le 10$ | $100$ | $20$ |
| 2 | $100$ | $\le \frac{n(n-1)}{2}$ | $10^6$ | $10$ |
| 3 | $10^3$ | $=n$ | $n+m$ | $10$ |
| 4 | $10^3$ | $\le \frac{n(n-1)}{2}$ | $n^2$ | $20$ |
| 5 | $10^3$ | $\le \frac{n(n-1)}{2}$ | $n+m$ | $40$ |


对于 $100\%$ 的数据，$n-1\le m\le\dfrac{n(n-1)}{2}$，$1\le u,v \le n$，且图中无自环、重边。

后话：这并非此题的原版，而是改版。然而[原版](https://www.luogu.com.cn/problem/T565042)我们目前并没有想到做法，有思路可以联系 [Down_syndrome](https://www.luogu.com.cn/user/984018)。


---

---
title: "玛丽卡"
layout: "post"
diff: 提高+/省选-
pid: P1186
tag: ['图论', '枚举', '最短路']
---
# 玛丽卡
## 题目描述

麦克找了个新女朋友，玛丽卡对他非常恼火并伺机报复。

因为她和他们不住在同一个城市，因此她开始准备她的长途旅行。

在这个国家中每两个城市之间最多只有一条路相通，并且我们知道从一个城市到另一个城市路上所需花费的时间。

麦克在车中无意中听到有一条路正在维修，并且那儿正堵车，但没听清楚到底是哪一条路。无论哪一条路正在维修，从玛丽卡所在的城市都能到达麦克所在的城市。

玛丽卡将只从不堵车的路上通过，并且她将按最短路线行车。麦克希望知道在最糟糕的情况下玛丽卡到达他所在的城市需要多长时间，这样他就能保证他的女朋友离开该城市足够远。

编写程序，帮助麦克找出玛丽卡按最短路线通过不堵车道路到达他所在城市所需的最长时间（用分钟表示）。

## 输入格式

第一行有两个用空格隔开的数 $N$ 和 $M$，分别表示城市的数量以及城市间道路的数量。$1 \le N \le 1000$，$1 \le M \le N \times (N - 1)/2$。城市用数字 $1 \sim N$ 标识，麦克在城市 $1$ 中，玛丽卡在城市 $N$ 中。  

接下来的 $M$ 行中每行包含三个用空格隔开的数 $A,B,V$。其中 $1 \le A, B \le N$，$1 \le V \le 1000$。这些数字表示在 $A$ 和城市 $B$ 中间有一条双行道，并且在 $V$ 分钟内就能通过。
## 输出格式

一行，写出用分钟表示的最长时间，在这段时间中，无论哪条路在堵车，玛丽卡应该能够到达麦克处，如果少于这个时间的话，则必定存在一条路，该条路一旦堵车，玛丽卡就不能够赶到麦克处。
## 样例

### 样例输入 #1
```
5 7
1 2 8
1 4 10
2 3 9
2 4 10
2 5 1
3 4 7
3 5 10

```
### 样例输出 #1
```
27
```
## 提示

感谢 Imakf 提供的三组 hack 数据。


---

---
title: "[蓝桥杯 2024 国研究生组] 最短路"
layout: "post"
diff: 提高+/省选-
pid: P12319
tag: ['图论', '2024', '矩阵加速', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国研究生组] 最短路
## 题目描述

给定一个包含 $n$ 个点的图 $G$，用邻接矩阵 $A_{i,j}$ 表示，其中 $A_{i,j} = 0$ 表示无边，$A_{i,j} > 0$ 表示有边，$A_{i,j}$ 的值为边权。

给定 $m$ 次询问，每次询问你需要找出从 $a_i$ 到 $b_i$ 恰好经过 $c_i$ 条边的边权和最小的路径。对于每次询问，你可以选择某一条边，将其中的一次经过的边权整除 $2$（如果多次经过一条边，只有一次整除 $2$，其它次按原边权计算）。
## 输入格式

输入的第一行包含一个整数 $n$。

接下来 $n$ 行，每行包含 $n$ 个整数，表示邻接矩阵 $A_{i,j}$，相邻整数之间使用一个空格分隔。

接下来一行包含一个整数 $m$。

接下来 $m$ 行，每行包含 3 个整数 $a_i, b_i, c_i$ 表示一次询问，相邻整数之间使用一个空格分隔。
## 输出格式

输出 $m$ 行，每行包含一个整数依次表示每次询问的答案。如果有恰好经过 $c_i$ 条边的路径，输出路径的最小权值和。如果没有恰好经过 $c_i$ 条边的路径，输出 $-1$。
## 样例

### 样例输入 #1
```
3
0 1 1
0 1 0
1 0 0
4
2 1 1
1 2 2
1 3 3
3 1 4
```
### 样例输出 #1
```
-1
1
2
-1
```
## 提示

### 评测用例规模与约定

- 对于 $40\%$ 的评测用例，$m = 1$，$c_i \leq 50$；
- 另有 $10\%$ 的评测用例，$m \leq 100$，$c_i \leq 50$；
- 另有 $20\%$ 的评测用例，$m = 1$，$c_i < 2^{24}$；
- 对于所有评测用例，$1 \leq n \leq 50$，$1 \leq m \leq 1000$，$1 \leq a_i, b_i \leq n$，$1 \leq c_i \leq 10^9$，$0 \leq A_{i,j} \leq 10^9$。


---

---
title: "「CZOI-R3」数字变换"
layout: "post"
diff: 提高+/省选-
pid: P12407
tag: ['动态规划 DP', '图论', '洛谷原创', 'O2优化', '图论建模', '最短路', '洛谷比赛']
---
# 「CZOI-R3」数字变换
## 题目描述

你有一个长度为 $n$ 的序列 $x$ 和一个数 $a=p$。

序列 $x$ 的第 $i$ 个数具有一个花费序列 $w_{i,1},w_{i,2},\dots,w_{i,k}$。

你可以将 $a$ 变换成 $i$（$1\le i\le n$，$a$ 可以等于 $i$），**当前**是你的第 $j$ 次操作，则花费为 $w_{i,j} + 2\times(L-(x_a \mathbin{\&} x_i))$，其中 $\mathbin{\&}$ 是按位与，即 C++ 中的 `&`。

$L$ 是序列 $x$ 中所有数的最大值，即 $\max\limits_{1\le i\le n}x_i$。

你需要对所有 $1\le i\le n$ 求出**在第 $k$ 步操作结束时**将 $a$ 变成 $i$ 的**最小**花费。询问之间互相独立，每次询问不会影响其他次询问的答案。
## 输入格式

由于直接输入数据量过大，请使用以下方式读入数据：

第一行输入 $5$ 个整数 $n,p,k,c,seed$，其中 $c,seed$ 的意义在下文给出。

第二行输入 $c$ 个整数 $y_0,y_1,\dots,y_{c-1}$，其中 $y_i$ 的意义在下文给出。

读入后使用以下函数获得输入：

```cpp
int c, y[65536]; unsigned long long seed;
int get_rand(int mod)
{
    seed ^= seed << 14;
    seed ^= seed >> 7;
    seed ^= seed << 19;
    seed ^= seed << 23;
    return seed % mod;
}
void get_input()
{
    for (int i = 1; i <= n; i++) x[i] = y[get_rand(c)];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= k; j++) w[i][j] = get_rand(1000000);
}
```

你需要调用的是 `get_input` 函数。

**注意：此输入方式仅为减小输入量，标准解法并不依赖此输入方式。**
## 输出格式

共一行输出 $n$ 个正整数，第 $i$ 个表示将 $a$ 变成 $i$ 的最小花费。
## 样例

### 样例输入 #1
```
3 1 2 3 1025032617
1 2 3
```
### 样例输出 #1
```
730965 742898 1038257
```
## 提示

**【样例解释】**

$x = \{3, 1, 3\},w_1 = \{834731, 259456\},w_2 = \{471501, 271389\} ,w_3 = \{902700, 566748\},a=1,L=3$。

将 $a$ 变为 $2$ 的最优操作是第一次 $a\to 2$ 花费 $w_{2,1} + 2\times(3-3\& 1)= 471505$，第二次 $a\to 2$ 花费 $w_{2,2} + 2\times(3-1\& 1)= 271393$，总花费为 $742898$。

**【数据范围】**

- Subtask #1（$15\text{ pts}$）：$k = 1$，$x_i < 2^{12}$。
- Subtask #2（$25\text{ pts}$）：$c\le 10^3$（最多只有 $10^3$ 种不同的 $x_i$），$x_i < 2^{12}$。
- Subtask #3（$25\text{ pts}$）：$\max\{\text{popcount}(x_i)\} \le 5$。其中 $\text{popcount}(x_i)$ 表示 $x_i$ 在二进制下 $1$ 的个数。
- Subtask #4（$35\text{ pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 2 \times 10^5$，$1 \le k \le 10$，$0\le x_i<2^{16}$，$1 \le  p \le n$，$0\le w_{i,j}<10^6$。$1\le seed \le 2\times 10^9$，$1\le c \le 2^{16}$，$0 \le y_i < 2^{16}$。


---

---
title: "「FAOI-R6」魂灵之影"
layout: "post"
diff: 提高+/省选-
pid: P12604
tag: ['图论', '数论', '交互题', 'O2优化', '二分图']
---
# 「FAOI-R6」魂灵之影
## 题目背景

此题因撞题已移出 FAOI Round 6.

> Draw me to the light, let the curse be lifted  
We can rise above the roar  
With the bite of every devil  
We've felled before  
Drown them out  
Let the fog give way to clarity  
There is power in the strain of every drop I bleed  
I am the venom and the cure  
Take me  
Through the fear, through the heart that's broken  
Our world lies in wait for me  
Every tear, every scar left open  
This is the taming of the beast  
I'll end this war you started  
I'll stitch this wound with bloodshed  
You are my wicked victory  

<https://music.163.com/#/song?id=2672191019>
## 题目描述

给定一个无向**连通**图，边带权，可能存在重边自环。有 $q$ 次查询，每次给定 $x,y,z$，求所有以 $x$ 为起点，$y$ 为终点的路径（不要求为简单路径）中，边权和 $\bmod\ z$ 的最小值是多少。

### 交互方式

**本题为交互题，只支持 C++ 语言提交，并且不支持 C++14 (GCC 9)。**

你需要编写以下三个函数：

```cpp
void Ready(int T, int subtask_id)
```

该函数在每个测试点中仅会调用一次，两个参数表示该测试点的数据组数和子任务编号。样例的子任务编号为 $-1$。

```cpp
void Set(int n, int m, int q, vector <int> u, vector <int> v, vector <int> w)
```

在调用 `Ready` 之后，该函数会（在每个测试点中）被调用 $T$ 次，其中 $n,m$ 分别表示图的边数和点数。$u,v,w$ 的大小均为 $m$，$u[i],v[i],w[i]$ 表示图的一条边。

```cpp
int Go(int x, int y, int z)
```

每次调用 `Set` 之后，该函数会（在每组数据中）被调用 $q$ 次，每次调用表示一次查询。返回值应为本次查询的答案。

你可以直接以下发文件中的 `template.cpp` 为基础编写。
## 输入格式

**以下格式只对本地测试有效，但变量名的含义与实际评测相同。在实际评测中，请不要试图从标准输入（stdin）读取任何内容。**

**本题有多组数据。**

第一行两个非负整数 $T$ 和 $\text{subtask\_id}$，分别表示数据组数和 Subtask 编号。

特别地，样例满足 $\text{subtask\_id}=-1$。

对于每组数据：
- 第一行是空行。
- 第二行三个非负整数 $n,m,q$。
- 接下来 $m$ 行，每行三个非负整数 $u,v,w$，表示一条边。
- 接下来 $q$ 行，每行三个正整数 $x,y,z$，表示一次查询。
## 输出格式

**以下格式只对本地测试有效，但变量名的含义与实际评测相同。在实际评测中，请不要试图向标准输出（stdout）打印任何内容。**

对于每组数据：
- 第一行是空行。
- 下面 $q$ 行，每行一个非负整数，表示答案。
## 样例

### 样例输入 #1
```
2 -1
2 1 1
1 2 1
1 2 2
3 3 1
1 2 1
2 3 1
1 3 1
1 3 2
```
### 样例输出 #1
```
1
0
```
## 提示

#### 【样例解释】

对于第 $1$ 组数据的唯一一组询问，所有路径均形如 $1\to 2\to 1\to \dots \to 1\to 2$，可以证明所有路径的权值均为 $1$。

对于第 $2$ 组数据的唯一一组询问，路径 $1\to 2\to 3$ 权值为 $2\bmod 2=0$，路径 $1\to 3$ 的答案为 $1\bmod 2=1$，所以答案为 $0$。

#### 【数据范围】

对于 $100\%$ 的数据，$0\le T\le 1.5 \times 10^4$，$-1 \le \text{subtask\_id} \le 9$，$0\le n,m,q\le 10^6$，$1\le u,v,x,y\le n$，$0\le w\le 10^9$，$1\le z\le 10^9$，保证图连通。

请下载附件中的 `judge_result.jpeg` 以了解交互库所占用资源的规模。如果你不想下载附件的话，我们在这里用一句话概括一下：保证交互库的运行时间不超过 0.15 秒，占用的内存不超过 60 MB。

**本题开启子任务捆绑测试。**

- Subtask 0 - Subtask 4（10 pts）：$n,m,q,w,z\le 10$，$T \le 1.5 \times 10^4$。
  - Subtask 0（2 pts）：$n=0$。
  - Subtask 1（2 pts）：$n=1$。
  - Subtask 2（1 pts）：$n=2$，$m \le 3$。
  - Subtask 3（4 pts）：$n \le 4$，$m \le 6$，$w \le 8$。
  - Subtask 4（1 pts）：在 Subtask 0 - Subtask 4 下无特殊限制。
- Subtask 5 - Subtask 9（90 pts）：$n,m,q\le 10^6$，$w,z \le 10^9$，$T=1$。
  - Subtask 5（20 pts）：$n,m,q,w,z\le 100$。
  - Subtask 6（20 pts）：$n,m,q,w,z\le 10^3$。
  - Subtask 7（10 pts）：$w,z\le 5$。
  - Subtask 8（10 pts）：$w=1$。
  - Subtask 9（30 pts）：在 Subtask 5 - Subtask 9 下无特殊限制。


Idea：ppip，Solution：喵仔牛奶，Code：ppip，Data：035966_L3

[如何调试？](https://www.luogu.com.cn/paste/3x0kjgps)


---

---
title: "速度限制"
layout: "post"
diff: 提高+/省选-
pid: P1266
tag: ['图论']
---
# 速度限制
## 题目描述

在这个繁忙的社会中，我们往往不再去选择最短的道路，而是选择最快的路线。开车时每条道路的限速成为最关键的问题。不幸的是，有一些限速的标志丢失了，因此你无法得知应该开多快。一种可以辩解的解决方案是，按照原来的速度行驶。你的任务是计算两地间的最快路线。

你将获得一份现代化城市的道路交通信息。为了使问题简化，地图只包括路口和道路。每条道路是有向的，只连接了两条道路，并且最多只有一块限速标志，位于路的起点。两地 $A$ 和 $B$，最多只有一条道路从 $A$ 连接到 $B$。你可以假设加速能够在瞬间完成并且不会有交通堵塞等情况影响你。当然，你的车速不能超过当前的速度限制。

## 输入格式

第一行是 $3$ 个整数 $N$，$M$ 和 $D$（$2\leq N\leq 150$，$1\leq M\leq 22500$），表示道路的数目，用 $0 \sim N-1$ 标记。$M$ 是道路的总数，$D$ 表示你的目的地。

接下来的 $M$ 行，每行描述一条道路，每行有 $4$ 个整数 $A$（$0\leq A<N$），$B$（$0\leq B<N$），$V$ （$0\leq V\leq 500$）和 $L$（$1\leq L\leq 500$），这条路是从 $A$ 到 $B$ 的，速度限制是 $V$，长度为 $L$。如果 $V$ 是 $0$，表示这条路的限速未知。

如果 $V$ 不为 $0$，则经过该路的时间 $T=\frac{L}{V}$。否则 $T=\frac{L}{\text{Vold}}$，$\text{Vold}$ 是你到达该路口前的速度。开始时你位于 $0$ 点，并且速度为 $70$。

## 输出格式

输出文件仅一行整数，表示从 $0$ 到 $D$ 经过的城市。

输出的顺序必须按照你经过这些城市的顺序，以 $0$ 开始，以 $D$ 结束。仅有一条最快路线。

## 样例

### 样例输入 #1
```
6 15 1
0 1 25 68
0 2 30 50
0 5 0 101
1 2 70 77
1 3 35 42
2 0 0 22
2 1 40 86
2 3 0 23
2 4 45 40
3 1 64 14
3 5 0 23
4 1 95 8
5 1 0 84
5 2 90 64
5 3 36 40
```
### 样例输出 #1
```
0 5 2 3 1
```


---

---
title: "[NERC 2022] Amazing Trick"
layout: "post"
diff: 提高+/省选-
pid: P12790
tag: ['模拟', '图论', '2022', 'Special Judge', '置换', '随机化', '构造', 'ICPC', 'Ad-hoc', 'NERC/NEERC']
---
# [NERC 2022] Amazing Trick
## 题目描述

Alice is a magician and she creates a new trick. She has $n$ cards with different numbers from $1$ to $n$ written on them. First, she asks an audience member to shuffle the deck and put cards in a row. Let's say the $i$-th card from the left has the number $a_i$ on it. 

Then Alice picks two permutations $p$ and $q$. There is a restriction on $p$ and $q$ --- $\textbf{permutations can't have fixed points}$. Which means $\forall i: p_i \ne i\ and\ q_i \ne i$.

After permutations are chosen, Alice shuffles the cards according to them. Now the $i$-th card from the left is the card $a[p[q[i]]$. The trick is considered successful if $i$-th card from the left has the number $i$ on it after the shuffles.

Help Alice pick the permutations $p$ and $q$ or say it is not possible for the specific starting permutation $a$. 
## 输入格式

The first line of the input contains the number of tests $t$ ($1 \leq t \leq 10^5$). 

Each test is described in two lines. The first line contains one integer $n$ --- the number of cards ($1 \leq n \leq 10^5$). The second line contains $n$ integers $a_i$ --- the initial permutation of the cards ($1 \leq a_i \leq n$; $\forall i \neq j: a_i \neq a_j$). 

It is guaranteed that the sum of $n$ over all tests does not exceed $10^5$.
## 输出格式

Print the answer for each test case in the same order the cases appear in the input.

For each test case, print $\tt{Impossible}$ in a single line, if no solution exists.

Otherwise, print $\tt{Possible}$ in the first line, and in the following two lines print permutations $p$ and $q$.
## 样例

### 样例输入 #1
```
4
2
2 1
3
1 2 3
4
2 1 4 3
5
5 1 4 2 3
```
### 样例输出 #1
```
Impossible
Possible
3 1 2
2 3 1
Possible
3 4 2 1
3 4 2 1
Possible
4 1 2 5 3
3 1 4 5 2
```


---

---
title: "[GCJ 2022 Finals] Wonderland Chase"
layout: "post"
diff: 提高+/省选-
pid: P13001
tag: ['图论', '2022', '广度优先搜索 BFS', 'Google Code Jam']
---
# [GCJ 2022 Finals] Wonderland Chase
## 题目描述

Alice is trapped in Wonderland's labyrinth, being chased by the Queen of Hearts and her herald! The labyrinth is a set of $\mathbf{J}$ junctions numbered 1 through $\mathbf{J}$, connected by $\mathbf{C}$ bidirectional corridors.

Alice and the Queen of Hearts take turns making moves, and each knows the location of the other at all times. A move (by either of them) consists of either staying at the current junction or moving to another one that is connected to it by a corridor.

The Queen's herald, however, announces the next move the Queen makes in advance. That means that before anyone makes a move, he announces the Queen's first move. Then, Alice moves first. Then, each time the Queen moves, she must respect the previous announcement, and then decide her next move so the herald can announce it. Alice hears the announcements, so she always knows the Queen's next move before making her own.

![](https://cdn.luogu.com.cn/upload/image_hosting/5dctftu9.png)

If Alice and the Queen are at the same junction after either of them moves, then Alice is caught. Otherwise, the pursuit continues. After $10^{9}$ total moves (half of them for Alice and half for the Queen), if Alice and the Queen are not in the same junction, then the Queen will give up and Alice will be safe.

Alice chooses her moves optimally to escape. If she cannot escape, she chooses her moves to maximize the total number of moves until she is caught. The Queen chooses her moves optimally to try to catch Alice in as few total moves as possible.

Given the labyrinth's layout and the initial locations of both the Queen and Alice, find out whether Alice will be caught by the Queen and, if so, in how many moves.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing four integers $\mathbf{J}$, $\mathbf{C}$, $\mathbf{A}$, and $\mathbf{Q}$: the number of junctions, the number of corridors, the junction where Alice starts, and the junction where the Queen starts, respectively. Then, $\mathbf{C}$ lines follow. The $i$-th of these lines contains two integers $\mathbf{U}_i$ and $\mathbf{V}_i$, indicating that the $i$-th corridor bidirectionally connects junctions $\mathbf{U}_i$ and $\mathbf{V}_i$.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is `SAFE` if Alice can avoid being caught for $10^9$ total moves. Otherwise, $y$ is the total number of moves (including Alice's and the Queen's) that it takes for the Queen to catch Alice.
## 样例

### 样例输入 #1
```
4
5 5 5 1
1 2
1 3
2 4
3 4
4 5
5 5 5 2
1 2
1 3
2 4
3 4
4 5
3 1 2 3
1 3
2 1 1 2
1 2
```
### 样例输出 #1
```
Case #1: SAFE
Case #2: 4
Case #3: SAFE
Case #4: 2
```
## 提示

Sample Case #1 is the one pictured in the problem statement. Alice's optimal first move is to move to junction 4.

Sample Case #2 is the same as Sample Case #1 but the Queen starts at junction 2. The Queen can catch Alice by first announcing a move to junction 4. If Alice were to move to junction 4, she would be caught in 2 moves. Alice can evade capture for an extra 2 moves by staying put and waiting until the Queen then moves to junction 5 where she is located.

![](https://cdn.luogu.com.cn/upload/image_hosting/tbatx4qf.png)

In Sample Case #3, the Queen cannot reach Alice no matter what she does.

![](https://cdn.luogu.com.cn/upload/image_hosting/f4qvfxc7.png)

In Sample Case #4, the Queen can begin by announcing that she will move to Alice's current junction. Alice has to move before then. If Alice moves to where the Queen already is, she gets caught immediately; if Alice remains in place, then she gets caught when the Queen moves. The second option is better, since it requires 2 total moves (Alice's and the Queen's) instead of 1.

![](https://cdn.luogu.com.cn/upload/image_hosting/2ac9iwif.png)

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{A} \leq \mathbf{J}$.
- $1 \leq \mathbf{Q} \leq \mathbf{J}$.
- $\mathbf{A} \neq \mathbf{Q}$.
- $1 \leq \mathbf{U}_i < \mathbf{V}_i \leq \mathbf{J}$, for all $i$.
- $(\mathbf{U}_i, \mathbf{V}_i) \neq (\mathbf{U}_j, \mathbf{V}_j)$, for all $i \neq j$.

**Test Set 1 (Visible Verdict)**

- Time limit: 10 seconds.
- $2 \leq \mathbf{J} \leq 30$.
- $1 \leq \mathbf{C} \leq 60$.

**Test Set 2 (Hidden Verdict)**

- Time limit: 60 seconds.
- $2 \leq \mathbf{J} \leq 10^5$.
- $1 \leq \mathbf{C} \leq 2 \times 10^5$.


---

---
title: "[GCJ 2019 #2] Contransmutation"
layout: "post"
diff: 提高+/省选-
pid: P13118
tag: ['动态规划 DP', '图论', '2019', '拓扑排序', '强连通分量', 'Google Code Jam']
---
# [GCJ 2019 #2] Contransmutation
## 题目描述

Last year, we asked you to help us convert expensive metals into lead. (You do not need to know anything about the previous problem to solve this one.) But your country's leader is still greedy for more lead!

There are $\mathbf{M}$ metals known in the world; lead is metal number 1 on your periodic table. Your country's leader has asked you to use the metals in the treasury to make as much lead as possible.

For each metal (including lead), you know exactly one formula that lets you destroy one gram of that metal and create one gram each of two metals. (It is best not to think too much about the principle of mass conservation!) Note that it is possible that the formula for the i-th metal might produce the i-th metal as one of the products. The formulas do not work with partial grams. However, you can use each formula as often as you would like (or not at all), as long as you have a gram of the required ingredient.

If you make optimal choices, what is the largest number of grams of lead you can end up with, or is it unbounded? If it is not unbounded: since the output can be a really big number, we only ask you to output the remainder of dividing the result by the prime $10^9+7$ (that is, $1000000007$).
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each begins with one line with an integer $\mathbf{M}$: the number of metals known in the world. Then there are $\mathbf{M}$ more lines with two integers $\mathbf{R_{i1}}$ and $\mathbf{R_{i2}}$ each; the i-th of these lines, counting starting from 1, indicates that you can destroy one gram of metal i to create one gram of metal $\mathbf{R_{i1}}$ and one gram of metal $\mathbf{R_{i2}}$. Finally, there is one line with $\mathbf{M}$ integers $\mathbf{G_1}$, $\mathbf{G_2}$, ..., $\mathbf{G_M}$; $\mathbf{G_i}$ is the number of grams of metal i in the treasury. Lead is metal 1.

## 输出格式

For each test case, output one line containing `Case #x: y` where $x$ is the test case number (starting from 1). If there is no bound on the maximum amount of lead that can be produced, $y$ must be UNBOUNDED. Otherwise, $y$ must be the largest amount of lead, in grams, that you can end up with, modulo the prime $10^9+7$ (that is, $1000000007$).
## 样例

### 样例输入 #1
```
3
2
1 2
1 2
1 0
2
1 2
1 2
0 0
4
2 4
3 4
2 4
2 3
10 10 10 10
```
### 样例输出 #1
```
Case #1: UNBOUNDED
Case #2: 0
Case #3: 10
```
## 提示

**Sample Explanation**

In Sample Case #1, you have one formula that turns 1 gram of lead into 1 gram of lead and 1 gram of the second metal, and another formula that turns 1 gram of the second metal into 1 gram of lead and 1 gram of the second metal. You can alternate between these formulas to produce as much of both metals as you want.

Sample Case #2 has the same formulas as Sample Case #1, but you have no metals to start with!

In Sample Case #3, none of the formulas help you produce more lead, so you cannot end up with more lead than you started with.

**Limits**

- $1 \leq \mathbf{R_{i1}} < \mathbf{R_{i2}} \leq \mathbf{M}$, for all $i$.

**Test set 1 (7 Pts, Visible)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{M} \leq 10$.
- $0 \leq \mathbf{G_i} \leq 10$, for all $i$.

**Test set 2 (16 Pts, Hidden)**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{M} \leq 100$.
- $0 \leq \mathbf{G_i} \leq 10^9$, for all $i$.

**Test set 3 (6 Pts, Hidden)**

- $1 \leq \mathbf{T} \leq 5$.
- $2 \leq \mathbf{M} \leq 10^5$.
- $0 \leq \mathbf{G_i} \leq 10^9$, for all $i$.


---

---
title: "[GCJ 2017 #3] Good News and Bad News"
layout: "post"
diff: 提高+/省选-
pid: P13176
tag: ['搜索', '图论', '2017', 'Special Judge', '生成树', 'Google Code Jam']
---
# [GCJ 2017 #3] Good News and Bad News
## 题目描述

You would like to get your $F$ friends to share some news. You know your friends well, so you know which of your friends can talk to which of your other friends. There are $P$ such one-way relationships, each of which is an ordered pair $(A_i, B_i)$ that means that friend $A_i$ can talk to friend $B_i$. It does not imply that friend $B_i$ can talk to friend $A_i$; however, another of the ordered pairs might make that true.

For every such existing ordered pair $(A_i, B_i)$, you want friend $A_i$ to deliver some news to friend $B_i$. In each case, this news will be represented by an integer value; the magnitude of the news is given by the absolute value, and the type of news (good or bad) is given by the sign. The integer cannot be 0 (or else there would be no news!), and its absolute value cannot be larger than $F^2$ (or else the news would be just *too* exciting!). These integer values may be different for different ordered pairs.

Because you are considerate of your friends' feelings, for each friend, the sum of the values of all news given *by* that friend must equal the sum of values of all news given *to* that friend. If no news is given by a friend, that sum is considered to be 0; if no news is given to a friend, that sum is considered to be 0.

Can you find a set of news values for your friends to communicate such that these rules are obeyed, or determine that it is impossible?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each begins with one line with two integers $F$ and $P$: the number of friends, and the number of different ordered pairs of friends. Then, $P$ more lines follow; the $i$-th of these lines has two different integers $A_i$ and $B_i$ representing that friend $A_i$ can talk to friend $B_i$. Friends are numbered from 1 to $F$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is either IMPOSSIBLE if there is no arrangement satisfying the rules above, or, if there is such an arrangement, $P$ integers, each of which is nonzero and lies inside $[-F^2, F^2]$. The $i$-th of those integers corresponds to the $i$-th ordered pair from the input, and represents the news value that the first friend in the ordered pair will communicate to the second. The full set of values must satisfy the conditions in the problem statement.

If there are multiple possible answers, you may output any of them.
## 样例

### 样例输入 #1
```
5
2 2
1 2
2 1
2 1
1 2
4 3
1 2
2 3
3 1
3 4
1 2
2 3
3 1
2 1
3 3
1 3
2 3
1 2
```
### 样例输出 #1
```
Case #1: 1 1
Case #2: IMPOSSIBLE
Case #3: -1 -1 -1
Case #4: 4 -4 -4 8
Case #5: -1 1 1
```
## 提示

**Sample Explanation**

The sample output shows one possible set of valid answers. Other valid answers are possible.

In Sample Case #1, one acceptable arrangement is to have friend $1$ deliver news with value $1$ to friend $2$, and vice versa.

In Sample Case #2, whatever value of news friend $1$ gives to friend $2$, it must be nonzero. So, the sum of news values given to friend $2$ is not equal to zero. However, friend $2$ cannot give any news and so that value is $0$. Therefore, the sums of given and received news for friend $2$ cannot match, and the case is IMPOSSIBLE.

In Sample Case #3, each of friends $1, 2$, and $3$ can deliver news with value $-1$ to the one other friend they can talk to — an unfortunate circle of bad news! Note that there is a friend 4 who does not give or receive any news; this still obeys the rules.

In Sample Case #4, note that $-5\ 5\ 5\ -10$ would not have been an acceptable answer, because there are $3$ friends, and $|-10| > 3^2$.

In Sample Case #5, note that the case cannot be solved without using at least one negative value.

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq A_i \leq F$, for all $i$.
- $1 \leq B_i \leq F$, for all $i$.
- $A_i \neq B_i$, for all $i$. (A friend does not self-communicate.)
- $(A_i, B_i) \neq (A_j, B_j)$, for all $i \neq j$. (No pair of friends is repeated within a test case in the same order.)

**Small dataset (Test Set 1 - Visible)**

- Time limit: ~~20~~ 5 seconds.
- $2 \leq F \leq 4$.
- $1 \leq P \leq 12$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~40~~ 10 seconds.
- $2 \leq F \leq 1000$.
- $1 \leq P \leq 2000$.


---

---
title: "[GCJ 2016 #3] Forest University"
layout: "post"
diff: 提高+/省选-
pid: P13203
tag: ['图论', '2016', 'Special Judge', '图论建模', '概率论', '随机化', 'Google Code Jam']
---
# [GCJ 2016 #3] Forest University
## 题目描述

The Forest University offers its students $\mathbf{N}$ courses, which must all be taken to obtain the degree. The courses can only be taken one at a time - you must complete a course before starting another. Each course is either basic, which means one can take it without any prior knowledge, or advanced, in which case exactly one other course is its prerequisite.

A student must take the prerequisite for a course before taking the course, although they do not need to be taken immediately one after the other. A course might be the prerequisite for multiple other courses. There are no prerequisite cycles. Any sequence of the $\mathbf{N}$ courses that meets the rules for prerequisites is valid for obtaining the degree.

When you graduate, the university commemorates the sequence of courses you have taken by printing an abbreviated version of it on your graduation hat. More precisely, this abbreviated version is a string consisting of the first letter of the name of each course you have taken, in the order you have taken them. For example, if you have taken a Coding course and a Jamming course, in that order, your graduation hat will say `CJ`. It is considered trendy to have certain cool words as a substring of the string on one's graduation hat.

Consider all possible valid sequences in which the courses can be taken. For each cool word, you need to find the fraction of those sequences that have the cool word as a substring (at least once) of the string on the corresponding graduation hat. Note that we're interested in the fraction of possible course sequences, not the fraction of possible different graduation hat strings. (Since multiple courses may start with the same letter, there may be fewer possible strings than course sequences.)

Somewhat unusually for Code Jam, we are only looking for an approximate answer to this problem; pay careful attention to the output format.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of five lines, in this order, which contain the following:

1. the number $\mathbf{N}$ of courses.
2. $\mathbf{N}$ integers; the i-th of these integers gives the number of the prerequisite course for the i-th course, or 0 if the i-th course is basic. The courses are numbered from 1 to $\mathbf{N}$.
3. $\mathbf{N}$ uppercase English letters (without whitespace in between), with the i-th character giving the first letter of the i-th course's name.
4. the number $\mathbf{M}$ of cool words.
5. $\mathbf{M}$ cool words, each of which consists only of uppercase English letters.
## 输出格式

For each test case, output one line containing Case #x: $y_{1}$ $y_{2}$ $\ldots$ $y_{\mathbf{M}}$, where $\mathrm{x}$ is the test case number (starting from 1) and $y_{\mathrm{i}}$ is the fraction of valid course sequences that will have the i-th cool word as a substring of the string on the graduation hat.

$y_{\mathrm{i}}$ will be considered correct if it is within an absolute error of 0.03 of the correct answer. See the FAQ for an explanation of what that means, and what formats of real numbers we accept.
## 样例

### 样例输入 #1
```
2
2
0 1
CJ
4
CJ C D JC
3
0 1 0
BAA
3
AA AAB ABA
```
### 样例输出 #1
```
Case #1: 1.0 1.0 0.0 0.0
Case #2: 0.67 0.0 0.33
```
## 提示

**Sample Explanation**

The sample output displays one set of acceptable answers to the sample cases. Other answers are possible within the allowed precision.

In sample case #1, course 1 (C) is a basic course that is a prerequisite for the advanced course 2 (J). The only way to complete the courses is to take course 1 and then course 2. This creates the string CJ. So the cool words CJ, C, D, and JC are present as substrings in 1, 1, 0, and 0 out of 1 possible cases, respectively.

In sample case #2, the basic course 1 (B) is a prerequisite for the advanced course 2 (A), and course 3 (A) is another basic course. There are three possible ways of completing the courses:

1. take course 1, then course 2, then course 3 (string: BAA)
2. take course 1, then course 3, then course 2 (string: BAA)
3. take course 3, then course 1, then course 2 (string: ABA)

The cool words AA, AAB, and ABA are present as substrings in 2, 0, and 1 out of 3 possible cases, respectively.

**Limits**

**Small dataset (25 Pts, Test Set 1 - Visible)**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $1 \leqslant \mathbf{N} \leqslant 100$.
- $1 \leqslant \mathbf{M} \leqslant 5$.
- The length of each cool word is between 1 and 20.
- Each cool word consists of uppercase English letters only.
- There are no cycles formed by the prerequisites.


---

---
title: "[GCJ 2013 #2] Erdős–Szekeres"
layout: "post"
diff: 提高+/省选-
pid: P13296
tag: ['图论', '贪心', '2013', '图论建模', '构造', 'Google Code Jam']
---
# [GCJ 2013 #2] Erdős–Szekeres
## 题目描述

Given a list $X$, consisting of the numbers $(1, 2, \ldots, N)$, an increasing subsequence is a subset of these numbers which appears in increasing order, and a decreasing subsequence is a subset of those numbers which appears in decreasing order. For example, $(5, 7, 8)$ is an increasing subsequence of $(4, 5, 3, 7, 6, 2, 8, 1)$.

Nearly 80 years ago, two mathematicians, Paul Erdős and George Szekeres proved a famous result: $X$ is guaranteed to have either an increasing subsequence of length at least $\sqrt{N}$ or a decreasing subsequence of length of at least $\sqrt{N}$. For example, $(4, 5, 3, 7, 6, 2, 8, 1)$ has a decreasing subsequence of length 4: $(5, 3, 2, 1)$.

I am teaching a combinatorics class, and I want to "prove" this theorem to my class by example. For every number $X[i]$ in the sequence, I will calculate two values:

* $A[i]$: The length of the longest increasing subsequence of $X$ that includes $X[i]$ as its largest number.
* $B[i]$: The length of the longest decreasing subsequence of $X$ that includes $X[i]$ as its largest number.

The key part of my proof will be that the pair $(A[i], B[i])$ is different for every i, and this implies that either $A[i]$ or $B[i]$ must be at least $\sqrt{N}$ for some i. For the sequence listed above, here are all the values of $A[i]$ and $B[i]$:

| $i$ | $X[i]$ | $A[i]$ | $B[i]$ |
|:-:|:----:|:----:|:----:|
| 0 | 4    | 1    | 4    |
| 1 | 5    | 2    | 4    |
| 2 | 3    | 1    | 3    |
| 3 | 7    | 3    | 4    |
| 4 | 6    | 3    | 3    |
| 5 | 2    | 1    | 2    |
| 6 | 8    | 4    | 2    |
| 7 | 1    | 1    | 1    |

I came up with a really interesting sequence to demonstrate this fact with, and I calculated $A[i]$ and $B[i]$ for every $i$, but then I forgot what my original sequence was. Given $A[i]$ and $B[i]$, can you help me reconstruct $X$?

$X$ should consist of the numbers $(1, 2, \ldots, N)$ in some order, and if there are multiple sequences possible, you should choose the one that is lexicographically smallest. This means that $X[0]$ should be as small as possible, and if there are still multiple solutions, then $X[1]$ should be as small as possible, and so on.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, each consisting of three lines.

The first line of each test case contains a single integer $N$. The second line contains $N$ positive integers separated by spaces, representing $A[0], A[1], \dots, A[N-1]$. The third line also contains $N$ positive integers separated by spaces, representing $B[0], B[1], \dots, B[N-1]$.

## 输出格式

For each test case, output one line containing "Case #x: ", followed by $X[0], X[1], \dots X[N-1]$ in order, and separated by spaces.

## 样例

### 样例输入 #1
```
2
1
1
1
8
1 2 1 3 3 1 4 1
4 4 3 4 3 2 2 1
```
### 样例输出 #1
```
Case #1: 1
Case #2: 4 5 3 7 6 2 8 1
```
## 提示

**Limits**

* $1 \leq T \leq 30$.
* It is guaranteed that there is at least one possible solution for $X$.

**Small dataset (9 Pts, Test set 1 - Visible)**

* $1 \leq N \leq 20$.

**Large dataset (15 Pts, Test set 2 - Hidden)**

* $1 \leq N \leq 2000$.



---

---
title: "[GCJ 2012 Finals] Zombie Smash"
layout: "post"
diff: 提高+/省选-
pid: P13332
tag: ['图论', '2012', '最短路', 'Google Code Jam']
---
# [GCJ 2012 Finals] Zombie Smash
## 题目描述

You are playing Zombie Smash: a game where the objective is to smash zombies with your trusty Zombie Smasher as they pop out of graves at the graveyard. The graveyard is represented by a flat 2D grid. Each zombie will pop out of a grave at some $(X, Y)$ cell on the grid, stand in place for 1000 milliseconds (ms), and then disappear back into the grave. At most one zombie can stand around a grave at a time.

You can move to any one of the 8 cells adjacent to your location in 100ms; i.e., you can move North, East, South, West, NW, NE, SW, and SE of your current location. You may move through or stand on a cell even if it is currently occupied by a zombie. You can smash a zombie instantly once you reach the cell that the zombie is standing on, but once you smash a zombie it takes 750ms for your Zombie Smasher to recharge before you can smash another zombie. You may move around while Zombie Smasher is recharging. For example, immediately after smashing a zombie at $(0, 0)$:

* It will take 750ms to reach and smash a zombie at $(1, 1)$ or
* 2000ms to reach and smash a zombie at $(20, 20)$.

You start at cell $(0, 0)$ at the beginning of the game (time=0). After you play a level you would like to know how many zombies you could have smashed, if you had played optimally.

## 输入格式

The first line will contain a single integer $T$, the number of test cases. It is followed by $T$ test cases, each starting with a line containing a single integer $Z$, the number of zombies in the level.

The next $Z$ lines contain 3 space-separated integers each, representing the location and time at which a given zombie will appear and disappear. The $i^{th}$ line will contain the integers $X_i$, $Y_i$ and $M_i$, where:

* $X_i$ is the X coordinate of the cell at which zombie $i$ appears,
* $Y_i$ is the Y coordinate of the cell at which zombie $i$ appears,
* $M_i$ is the time at which zombie $i$ appears, in milliseconds after the beginning of the game. The time interval during which the zombie can smashed is inclusive: if you reach the cell at any time in the range $[M_i, M_i + 1000]$ with a charged Zombie Smasher, you can smash the zombie in that cell.

## 输出格式

For each test case, output one line containing "Case #$c$: $d$", where $c$ is the case number (starting from 1), and $d$ is the maximum number of zombies you could have smashed in this level.
## 样例

### 样例输入 #1
```
3
4
1 0 0
-1 0 0
10 10 1000
10 -10 1000
3
1 1 0
2 2 0
3 3 0
5
10 10 1000
-10 10 1000
10 -10 1000
-10 -10 1000
20 20 2000
```
### 样例输出 #1
```
Case #1: 3
Case #2: 2
Case #3: 2
```
## 提示

**Limits**

- $1 \leq T \leq 100.$
- $-1000 \leq X_i, Y_i \leq 1000.$
- $0 \leq M_i \leq 100000000 = 10^8.$
- Two zombies will never be in the same location at the same time. In other words, if one zombie appears at $(x, y)$ at time $t$, then any other zombie that appears at $(x, y)$ must appear at or before $(t - 1001)$, or at or after $(t + 1001)$.

**Test set 1 (7 Pts, Visible Verdict)**

- $1 \leq Z \leq 8.$

**Test set 2 (18 Pts, Hidden Verdict)**

- $1 \leq Z \leq 100.$



---

---
title: "[GCJ 2011 #2] A.I. War"
layout: "post"
diff: 提高+/省选-
pid: P13377
tag: ['图论', '2011', '广度优先搜索 BFS', 'bitset', 'Google Code Jam']
---
# [GCJ 2011 #2] A.I. War
## 题目背景

A.I. War is a real-time strategy game developed by Arcen Games. This problem was inspired by the game, but does not assume you have played it.

Arcen Games is the creator of A.I. War. Arcen Games does not endorse and has no involvement with Google Code Jam.
## 题目描述

You're facing an artificial intelligence in a deadly war for the future of the galaxy. In order to defeat the A.I., you will need to threaten its $home\ planet$. Some planets are connected to each other by wormholes; any planet may be connected to any number of other planets using the wormholes.

You begin by owning only your home planet. Each turn, you may conquer any planet you $threaten$. You threaten a planet if you don't own it, and it is connected by a wormhole to any of the planets you own. Once you have conquered a planet, you own it. As soon as you threaten the A.I.'s home planet, you may not conquer any more planets.

While attending the most important day in tactical school, you discovered two things about the A.I.:

* For each planet you conquer, the A.I. will become more powerful, because it will see you as a threat and produce more ships to defend itself.
* The A.I. will defend every planet you're currently threatening.

You have combined those two facts to create a strategy:

1. You will conquer planets until you threaten the A.I.'s home base.
2. If there are multiple ways of completing step 1, do it while conquering the $smallest$ possible number of planets.
3. If there are multiple ways of completing step 2, do it so that at the end you will threaten the $largest$ possible number of planets.

Given the planets and the wormholes, how many planets will you conquer and threaten on your way to the A.I.'s home base if you follow the strategy described above?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a single line containing two space-separated integers: $P$, the number of planets, and $W$, the number of wormholes. Your home planet is planet $0$, and the A.I.'s home planet is planet $1$.

The second line of each test case will contain $W$ space-separated pairs of comma-separated integers $x_{i}, y_{i}$. Each of these indicates that there is a two-way wormhole connecting planets $x_{i}$ and $y_{i}$.

## 输出格式

For each test case, output one line containing "Case #$x$: $c\ t$", where $x$ is the case number (starting from $1$), $c$ is the number of planets you conquer if you follow the above strategy, and $t$ is the number of planets you threaten at the end (including the A.I.'s home planet).
## 样例

### 样例输入 #1
```
4
2 1
0,1
3 3
0,1 1,2 0,2
5 5
0,4 0,2 2,4 1,2 1,4
7 9
0,6 0,2 0,4 2,4 3,4 2,3 3,5 4,5 1,5
```
### 样例输出 #1
```
Case #1: 0 1
Case #2: 0 2
Case #3: 1 2
Case #4: 2 4
```
## 提示

**Sample Explanation**

In the first case, you don't have to conquer anything, and you're already threatening the A.I.'s home planet.

In the third case, you can threaten the A.I.'s home planet after conquering only one planet. You end up threatening two planets, and there's an extra planet that isn't connected to anything.

In the fourth case, you can threaten the A.I.'s home planet by conquering planets $4$ and $5$. You end up threatening planets $6$, $2$, $3$ and $1$ (the A.I.'s home planet).

**Limits**

- $1 \leq T \leq 50$.
- $0 \leq x_{i} < y_{i} < P$.
- Each wormhole is unique: If $i \neq j$, then $(x_{i}, y_{i}) \neq (x_{j}, y_{j})$.
- There will be at least one way to reach the A.I.'s home planet from your home planet using a series of wormholes.

**Small dataset (10 Pts, Test set 1 - Visible)**

- $2 \leq P \leq 36$.
- $1 \leq W \leq 630$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (22 Pts, Test set 2 - Hidden)**

- $2 \leq P \leq 400$.
- $1 \leq W \leq 2000$.
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[GCJ 2011 #3] Perpetual Motion"
layout: "post"
diff: 提高+/省选-
pid: P13380
tag: ['图论', '2011', '二分图', '组合数学', 'Google Code Jam']
---
# [GCJ 2011 #3] Perpetual Motion
## 题目描述

Have you ever been to the Google Lemming Factory? It is a very unusual place. The floor is arranged into an $R \times C$ grid. Within each grid square, there is a conveyor belt oriented up-down, left-right, or along one of the two diagonals. The conveyor belts move either forwards or backwards along their orientations, and you can independently choose which of the two possible directions each conveyor belt should move in.

![](https://cdn.luogu.com.cn/upload/image_hosting/h69uk07b.png)

Currently, there is a single lemming standing at the center of each square. When you start the conveyor belts, each lemming will move in the direction of the conveyor belt he is on until he reaches the center of a new square. All these movements happen simultaneously and take exactly one second to complete. Afterwards, the lemmings will all be on new squares, and the process will repeat from their new positions. This continues forever, or at least until you turn off the conveyor belts.

- When a lemming enters a new square, he continues going in the direction he was already going until he reaches the center of that square. He will not be affected by the new conveyor belt until the next second starts.
- If a lemming moves off the edge of the grid, he comes back at the same position on the opposite side. For example, if he were to move diagonally up and left from the top-left square, he would arrive at the bottom-right square. By the miracle of science, this whole process still only takes 1 second.
- Lemmings never collide and can always move past each other without difficulty.

The trick is to choose directions for each conveyor belt so that the lemmings will keep moving forever without ever having two of them end up in the center of the same square at the same time. If that happened, they would be stuck together from then on, and that is not as fun for them.

Here are two ways of assigning directions to each conveyor belt from the earlier example:

![](https://cdn.luogu.com.cn/upload/image_hosting/8e7eapk7.png)

In both cases, we avoid ever sending two lemmings to the center of the same square at the same time.

Given an arbitrary floor layout, calculate $N$, the number of ways to choose directions for each conveyor belt so that no two lemmings will ever end up in the center of the same square at the same time. The answer might be quite large, so please output it modulo $1000003$.
## 输入格式

The first line of input gives the number of test cases, $T$. $T$ test cases follow. Each begins with a line containing positive integers $R$ and $C$.

This is followed by $R$ lines, each containing a string of $C$ characters chosen from "|-/\\". Each character represents the orientation of the conveyor belt in a single square:

* '|' represents a conveyor belt that can move up or down.
* '-' represents a conveyor belt that can move left or right.
* '/' represents a conveyor belt that can move up-right or down-left.
* '\\' represents a conveyor belt that can move up-left or down-right.
## 输出格式

For each test case, output one line containing "Case #$x$: $M$", where $x$ is the case number (starting from 1), and $M$ is the remainder when dividing $N$ by $1000003$.
## 样例

### 样例输入 #1
```
3
3 3
|-/
|||
--|
3 4
----
||||
\\//
4 4
|---
\-\|
\|||
|--\
```
### 样例输出 #1
```
Case #1: 2
Case #2: 0
Case #3: 16
```
## 提示

**Limits**

- $ 1 \leq T \leq 25. $

**Small dataset (5 Pts, Test set 1 - Visible)**

- $ 3 \leq R \leq 4. $
- $ 3 \leq C \leq 4. $
- Time limit: ~~30~~ 3 seconds.

**Large dataset (21 Pts, Test set 2 - Hidden)**

- $ 3 \leq R \leq 100. $
- $ 3 \leq C \leq 100. $
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[GCJ 2010 #2] Bacteria"
layout: "post"
diff: 提高+/省选-
pid: P13401
tag: ['图论', '2010', '广度优先搜索 BFS', '连通块', 'Google Code Jam']
---
# [GCJ 2010 #2] Bacteria
## 题目描述

A number of bacteria lie on an infinite grid of cells, each bacterium in its own cell.

Each second, the following transformations occur (all simultaneously):

1. If a bacterium has no neighbor to its north and no neighbor to its west, then it will die.
2. If a cell has no bacterium in it, but there are bacteria in the neighboring cells to the north and to the west, then a new bacterium will be born in that cell.

Upon examining the grid, you note that there are a positive, finite number of bacteria in one or more rectangular regions of cells.

Determine how many seconds will pass before all the bacteria die.

Here is an example of a grid that starts with 6 cells containing bacteria, and takes 6 seconds for all the bacteria to die. '1's represent cells with bacteria, and '0's represent cells without bacteria.

```
000010
011100
010000
010000
000000

000000
001110
011000
010000
000000

000000
000110
001100
011000
000000

000000
000010
000110
001100
000000

000000
000000
000010
000110
000000

000000
000000
000000
000010
000000

000000
000000
000000
000000
000000
```
## 输入格式

The input consists of:

- One line containing $C$, the number of test cases.

Then for each test case:

- One line containing $R$, the number of rectangles of cells that initially contain bacteria.
- $R$ lines containing four space-separated integers $X_1$ $Y_1$ $X_2$ $Y_2$. This indicates that all the cells with X coordinate between $X_1$ and $X_2$, inclusive, and Y coordinate between $Y_1$ and $Y_2$, inclusive, contain bacteria.

The rectangles may overlap.

North is in the direction of decreasing Y coordinate.

West is in the direction of decreasing X coordinate.
## 输出格式

For each test case, output one line containing "Case #$N$: $T$", where $N$ is the case number (starting from 1), and $T$ is the number of seconds until the bacteria all die.
## 样例

### 样例输入 #1
```
1
3
5 1 5 1
2 2 4 2
2 3 2 4
```
### 样例输出 #1
```
Case #1: 6
```
## 提示

**Limits**

- $1 \leq C \leq 100.$

**Small dataset (6 Pts, Test set 1 - Visible)**

- $1 \leq R \leq 10$
- $1 \leq X_1 \leq X_2 \leq 100$
- $1 \leq Y_1 \leq Y_2 \leq 100$

**Large dataset (25 Pts, Test set 2 - Hidden)**

- $1 \leq R \leq 1000$
- $1 \leq X_1 \leq X_2 \leq 1000000$
- $1 \leq Y_1 \leq Y_2 \leq 1000000$
- The number of cells initially containing bacteria will be at most $1000000$.



---

---
title: "地震逃生"
layout: "post"
diff: 提高+/省选-
pid: P1343
tag: ['搜索', '图论', '福建省历届夏令营', '栈']
---
# 地震逃生
## 题目描述

汶川地震发生时，四川\*\*中学正在上课，一看地震发生，老师们立刻带领 $x$ 名学生逃跑，整个学校可以抽象地看成一个有向图，图中有 $n$ 个点，$m$ 条边。$1$ 号点为教室，$n$ 号点为安全地带，每条边都只能容纳一定量的学生，超过楼就要倒塌，由于人数太多，校长决定让同学们分成几批逃生，只有第一批学生全部逃生完毕后，第二批学生才能从 $1$ 号点出发逃生，现在请你帮校长算算，每批最多能运出多少个学生，$x$ 名学生分几批才能运完。
## 输入格式

第一行三个整数 $n,m,x$；  
以下 $m$ 行，每行三个整数 $a,b,c$（$1\leq a,b\leq n$，$0\leq c\leq x$）描述一条边，分别代表从 $a$ 点到 $b$ 点有一条边，且可容纳 $c$ 名学生。
## 输出格式

两个整数，分别表示每批最多能运出多少个学生，$x$ 名学生分几批才能运完。如果无法到达目的地（$n$ 号点）则输出 `Orz Ni Jinan Saint Cow!`。
## 样例

### 样例输入 #1
```
6 7 7
1 2 1
1 4 2
2 3 1
4 5 1
4 3 1
3 6 2
5 6 1

```
### 样例输出 #1
```
3 3

```
## 提示

**【注释】**

比如有图

```plain
1 2 100
2 3 1
```

$100$ 个学生先冲到 $2$ 号点，然后一个一个慢慢沿 $2 \to 3$ 边走过去。

18 神牛规定这样是不可以的……

也就是说，每批学生必须同时从起点出发，并且同时到达终点。

**【数据范围】**

对于 $100 \%$ 的数据，$0 \le x < 2^{31}$，$1 \le n \le 200$，$1 \le m \le 2000$。


---

---
title: "[GCJ 2009 #1B] Square Math"
layout: "post"
diff: 提高+/省选-
pid: P13436
tag: ['数学', '图论', '2009', '数论', '广度优先搜索 BFS', 'Google Code Jam']
---
# [GCJ 2009 #1B] Square Math
## 题目描述

Say we have a square that has $W$ cells on each side and, therefore, $W^2$ cells total. Let's go further and fill each cell with one of the following:

* A digit from 0 to 9;
* The addition sign (+);
* The subtraction sign (-).

If, finally, we add a constraint that no 2 digits are horizontally or vertically adjacent and no 2 operators (+ or -) are horizontally or vertically adjacent, then our square can be called an "arithmetic square".

Square Math is the name of a puzzle where, given an arithmetic square, we start from any numeric cell and move either horizontally or vertically a cell at a time, finally ending in a numerical cell. The mathematical expression we get from the traversal is evaluated to get a single value. For example:

```
2+3
+4-
1+0
```

The above is a valid arithmetic square of size $W = 3$. If we start from "2", move horizontally right, then vertically down, we'll get "2+4", which gives a value of "6". If we further move horizontally right, then vertically up, we'll get "2+4-3", which is equal to "3".

In Square Math, there is no limit to how many times you can use a particular cell. It is perfectly legal to move from a cell to its neighbor, then back to the original cell. Given an arithmetic square and a list of queries, your task is to find a Square Math expression which evaluates to each query.
## 输入格式

The first line of input contains a single integer, $T$. $T$ test cases follow. The first line of each test case contains 2 integers, $W$ and $Q$. $W$ lines follow, each containing $W$ characters, representing the arithmetic square. Don't worry, all arithmetic squares in the input are well-formed. The following line contains a space separated list of $Q$ integers, representing the values which need to be computed by using Square Math (the queries). You can assume that all given values will have at least one possible Square Math solution.
## 输出格式

For each test case, begin output with "Case #$X$:" on a line by itself, where $X$ is the test case number, starting from 1. Then, for each query within the test case, print the Square Math expression which evaluates to the query on a line by itself.

In the case where there are multiple possible Square Math expressions, print the one that is shortest. If there is still a tie, print the lexicographically smallest expression. Remember that '+' is lexicographically smaller than '-'.
## 样例

### 样例输入 #1
```
2
5 3
2+1-2
+3-4+
5+2+1
-4-0-
9+5+1
20 30 40
3 2
2+1
+4+
5+1
2 20
```
### 样例输出 #1
```
Case #1:
1+5+5+9
3+4+5+9+9
4+9+9+9+9
Case #2:
2
5+5+5+5
```
## 提示

**Limits**

- $1 \leq T \leq 60$

**Small dataset**

- Time limit: ~~30~~ 3 seconds.
- $2 \leq W \leq 10$
- $1 \leq Q \leq 20$
- $1 \leq \text{each query} \leq 50$

**Large dataset**

- Time limit: ~~60~~ 12 seconds.
- $2 \leq W \leq 20$
- $1 \leq Q \leq 50$
- $1 \leq \text{each query} \leq 250$


---

---
title: "[USACO5.4] 奶牛的电信Telecowmunication"
layout: "post"
diff: 提高+/省选-
pid: P1345
tag: ['图论', 'USACO', '福建省历届夏令营', '网络流', '最小割']
---
# [USACO5.4] 奶牛的电信Telecowmunication
## 题目描述

农夫约翰的奶牛们喜欢通过电邮保持联系，于是她们建立了一个奶牛电脑网络，以便互相交流。这些机器用如下的方式发送电邮：如果存在一个由 $c$ 台电脑组成的序列$a_1,a_2,\cdots ,a_c$，且 $a_1$ 与 $a_2$ 相连，$a_2$ 与 $a_3$ 相连，等等。那么电脑 $a_1$ 和 $a_c$ 就可以互发电邮。

很不幸，有时候奶牛会不小心踩到电脑上，农夫约翰的车也可能碾过电脑，这台倒霉的电脑就会坏掉。这意味着这台电脑不能再发送电邮了，于是与这台电脑相关的连接也就不可用了。

有两头奶牛就想：如果我们两个不能互发电邮，至少需要坏掉多少台电脑呢？请注意，$c_1,c_2$ 不能被破坏。请编写一个程序为她们计算这个最小值。

以如下网络为例：

```plain
   1*
  /
 3 - 2*
```

这张图画的是有 $2$ 条连接的 $3$ 台电脑。我们想要在电脑 $1$ 和 $2$ 之间传送信息。电脑 $1$ 与 $3$，$2$ 与 $3$ 直接连通。如果电脑 $3$ 坏了，电脑 $1$ 与 $2$ 便不能互发信息了。
## 输入格式

第一行：四个由空格分隔的整数：$N,M,c_1,c_2$。$N$ 是电脑总数，电脑由 $1$ 到 $N$ 编号。$M$ 是电脑之间连接的总数。后面的两个整数 $c_1$ 和 $c_2$ 是上述两头奶牛使用的电脑编号。连接没有重复且均为双向的（即如果 $c_1$ 与 $c_2$ 相连，那么 $c_2$ 与 $c_1$ 也相连）。两台电脑之间至多有一条连接。电脑 $c_1$ 和 $c_2$ 不会直接相连。

第 $2$ 到 $M+1$ 行：接下来的 $M$ 行中，每行包含两台直接相连的电脑的编号。
## 输出格式

一行，一个整数，表示使电脑 $c_1$ 和 $c_2$ 不能互相通信需要坏掉的电脑数目的最小值。
## 样例

### 样例输入 #1
```
3 2 1 2
1 3
2 3
```
### 样例输出 #1
```
1

```
## 提示

对于 $100\%$ 的数据：$1\le N \le 100$，$1\le M \le 600$。


---

---
title: "[ICPC 2025 APC] Duplicates"
layout: "post"
diff: 提高+/省选-
pid: P13619
tag: ['2024', '图论建模', '二分图', '构造', 'ICPC']
---
# [ICPC 2025 APC] Duplicates
## 题目描述

我们称一个数字序列**含有重复元素**，如果序列中存在出现一次以上的元素。形式化地讲，一个序列 $(a_1, \dots, a_n)$ 含有重复元素，如果存在两个不等的下标 $i$ 和 $j$ 使得 $a_i = a_j$。

给定一个 $n \times n$ 的矩阵 $X$。$X$ 中的每个元素都是一个 $1$ 到 $n$ 之间（含两端）的整数。你可以将 $X$ 中零个或多个元素修改为 $1$ 到 $n$ 之间（含两端）的任意整数。不同的元素可以修改为不同的整数。

你的任务是通过修改 $X$ 中的元素，使得以下所有条件都成立：

* 对于每一行 $i$，序列 $(X_{i1}, X_{i2}, \dots, X_{in})$ 含有重复元素。
* 对于每一列 $j$，序列 $(X_{1j}, X_{2j}, \dots, X_{nj})$ 含有重复元素。

你需要计算达成此目标所需的**最小**修改次数。同时，找出一种可行的修改方案。对于每次修改，你需要指明修改的是哪个元素以及它的新值。请注意，当给定的矩阵 $X$ 已经满足上述条件时，所需的最小修改次数可以为零。
## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 1000$），代表测试用例的数量。之后是 $t$ 个测试用例。每个测试用例的格式如下。

一个测试用例的第一行包含一个整数 $n$（$3 \le n \le 100$）。
接下来的 $n$ 行，每行包含 $n$ 个整数。第 $i$ 行的第 $j$ 个整数代表 $X_{ij}$（$1 \le X_{ij} \le n$）。

在单个输入文件中，所有测试用例的 $n^2$ 的总和不超过 $10,000$。
## 输出格式

对于每个测试用例，按以下格式输出一组修改方案。

第一行输出一个整数 $m$，代表需要修改的元素的最小数量。
在接下来的 $m$ 行中，每行输出三个整数 $i, j, v$。这代表一次修改，即将元素 $X_{ij}$ 的值修改为 $v$。这三个整数都必须在 $1$ 和 $n$ 之间（含两端）。

如果存在多种解法，你可以输出其中任意一种。

## 样例

### 样例输入 #1
```
5
4
3 2 1 1
2 1 3 4
1 3 3 1
4 4 4 2
3
1 3 1
2 1 3
3 2 2
5
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
3
1 1 2
2 2 1
2 3 2
3
1 1 3
3 2 1
3 1 3
```
### 样例输出 #1
```
2
2 1 1
4 2 3
3
2 1 3
2 2 3
3 3 3
0
1
1 2 2
1
2 1 1
```
## 提示

**样例解释 #1**

在第一个测试用例中，修改后的矩阵如下所示。

$$
\begin{bmatrix}
3 & 2 & 1 & 1 \\
1 & 1 & 3 & 4 \\
1 & 3 & 3 & 1 \\
4 & 3 & 4 & 2 \\
\end{bmatrix}
$$


---

---
title: "城市环路"
layout: "post"
diff: 提高+/省选-
pid: P1453
tag: ['动态规划 DP', '图论', '基环树']
---
# 城市环路
## 题目描述

一座城市，往往会被人们划分为几个区域，例如住宅区、商业区、工业区等等。

B 市就被分为了以下的两个区域——城市中心和城市郊区。在这两个区域的中间是一条围绕 B 市的环路，环路之内便是 B 市中心。


整个城市可以看做一个 $n$ 个点，$n$ 条边的单圈图（保证图连通），唯一的环便是绕城的环路。保证环上任意两点有且只有 $2$ 条简单路径互通。图中的其它部分皆隶属城市郊区。

现在，有一位名叫 Jim 的同学想在 B 市开店，但是任意一条边的 $2$ 个点不能同时开店，每个点都有一定的人流量，第 $i$ 个点的人流量是 $p_i$，在该点开店的利润就等于 $p_i×k$，其中 $k$ 是一个常数。

Jim 想尽量多的赚取利润，请问他应该在哪些地方开店？

## 输入格式

第一行一个整数 $n$，代表城市中点的个数。城市中的 $n$ 个点由 $0 \sim n-1$ 编号。

第二行有 $n$ 个整数，第 $(i + 1)$ 个整数表示第 $i$ 个点的人流量 $p_i$。

接下来 $n$ 行，每行有两个整数 $u, v$，代表存在一条连接 $u$ 和 $v$ 的道路。

最后一行有一个实数，代表常数 $k$。

## 输出格式

输出一行一个实数代表答案，结果保留一位小数。
## 样例

### 样例输入 #1
```
4
1 2 1 5
0 1
0 2
1 2
1 3
2

```
### 样例输出 #1
```
12.0
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 100$。
- 另有 $20\%$ 的数据，保证环上的点不超过 $2000$ 个。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$1 \leq p_i \leq 10^4$，$0 \leq u, v < n$，$0 \leq k \leq 10^4$，$k$ 的小数点后最多有 $6$ 位数字。


---

---
title: "集合位置"
layout: "post"
diff: 提高+/省选-
pid: P1491
tag: ['图论', '优先队列', '最短路']
---
# 集合位置
## 题目描述

每次有大的活动，大家都要在一起“聚一聚”，不管是去好乐迪，还是避风塘，或者汤姆熊，大家都要玩的痛快。还记得心语和花儿在跳舞机上的激情与释放，还记得草草的投篮技艺是如此的高超，还记得狗狗的枪法永远是 S ……还有不能忘了，胖子的歌声永远是让我们惊叫的！！

今天是野猫的生日，所以想到这些也正常，只是因为是上学日，没法一起去玩了。但回忆一下那时的甜蜜总是一种幸福嘛。。。

但是每次集合的时候都会出现问题！野猫是公认的“路盲”，野猫自己心里也很清楚，每次都提前出门，但还是经常迟到，这点让大家很是无奈。后来，野猫在每次出门前，都会向花儿咨询一下路径，根据已知的路径中，总算能按时到了。

现在提出这样的一个问题：给出 $n$ 个点的坐标，其中第一个为野猫的出发位置，最后一个为大家的集合位置，并给出哪些位置点是相连的。野猫从出发点到达集合点，总会挑一条最近的路走，如果野猫没找到最近的路，他就会走第二近的路。请帮野猫求一下这条第二最短路径长度。

特别地，选取的第二短路径**不会重复经过同一条路**，即使可能重复走过同一条路多次路程会更短。
## 输入格式

第一行是两个整数 $n(1 \le n \le 200)$ 和 $m(1 \le m\le 10000)$，表示一共有 $n$ 个点和 $m$ 条路，以下 $n$ 行每行两个数 $x_i$，$y_i$，$(-500 \le x_i,y_i \le 500),$ 代表第 $i$ 个点的坐标，再往下的 $m$ 行每行两个整数 $p_j$，$q_j,(1 \le p_j,q_j \le n)$，表示两个点之间有一条路，数据没有重边，**可能有自环**。
## 输出格式

只有一行包含一个数，为第二最短路线的距离（保留两位小数），如果存在多条第一短路径，则答案就是第一最短路径的长度；如果不存在第二最短路径，输出 `-1`。
## 样例

### 样例输入 #1
```
3 3

0 0

1 1

0 2

1 2

1 3

2 3


```
### 样例输出 #1
```
2.83
```


---

---
title: "十字绣"
layout: "post"
diff: 提高+/省选-
pid: P1524
tag: ['图论']
---
# 十字绣
## 题目背景

考古学家发现了一块布，布上做有针线活，叫做“十字绣”，即交替地在布的两面穿线。

## 题目描述

布是一个 $n\times m$ 的网格，线只能在网格的顶点处才能从布的一面穿到另一面。每一段线都覆盖一个单位网格的两条对角线之一，而在绣的过程中，一针中连续的两段线必须分处布的两面。给出布两面的图案（实线代表该处有线，虚线代表背面有线），问最少需要几针才能绣出来？一针是指针不离开布的一次绣花过程。

![](https://cdn.luogu.com.cn/upload/image_hosting/vftfilbf.png)

## 输入格式

第一行两个数 $N$ 和 $M(1 \le N,M \le 200)$。

接下来 $N$ 行每行 $M$ 个数描述正面。

再接下来 $N$ 行每行 $M$ 个数描述反面。

每个格子的表示如下：

- $\verb!.!$ 表示空格；
- $\verb!/!$ 表示从右上角连到左下角的线；
- $\verb!\!$ 表示从左上角连到右下角的线；
- $\verb!X!$ 表示两条对角线交叉。
## 输出格式

一个数，最少要用的针数。

## 样例

### 样例输入 #1
```
4 5

.....

.\...

..\..

.....

.....

....\ 

.\X..

.....


```
### 样例输出 #1
```
4


```


---

---
title: "[USACO04DEC] Cow Ski Area G"
layout: "post"
diff: 提高+/省选-
pid: P1653
tag: ['图论', '2004', 'USACO', '强连通分量', 'Tarjan']
---
# [USACO04DEC] Cow Ski Area G
## 题目描述

约翰的表哥罗恩生活在科罗拉多州。他近来打算教他的奶牛们滑雪，但是奶牛们非常害羞，不敢在游人组织的度假胜地滑雪。没办法，他只好自己建滑雪场了。罗恩的雪场可以划分为 $W$ 列 $L$ 行 $(1\le W\le 500, 1\le L\le 500)$，每个方格有一个特定的高度 $H(0\le H\le 9999)$。奶牛可以在相邻方格间滑雪，而且不能由低到高滑。

为了保证任意方格可以互通，罗恩打算造一些直达缆车。缆车很强大，可以连接任意两个方格，而且是双向的。而且同一个方格也可以造多台缆车。但是缆车的建造费用贵得吓人，所以他希望造尽量少的缆车。那最少需要造多少台呢？
## 输入格式

第 $1$ 行：$W$，$L$。

接下来输入宽 $W$ 高 $L$ 的矩阵地图。
## 输出格式

输出最小需要的缆车数。
## 样例

### 样例输入 #1
```
9 3
1 1 1 2 2 2 1 1 1
1 2 1 2 3 2 1 2 1
1 1 1 2 2 2 1 1 1
```
### 样例输出 #1
```
3
```
## 提示

$1\le W,L\le 500$，$0\le H\le 9999$。


---

---
title: "最小密度路径"
layout: "post"
diff: 提高+/省选-
pid: P1730
tag: ['图论']
---
# 最小密度路径
## 题目描述

给出一张有 $N$ 个点 $M$ 条边的加权有向无环图，接下来有 $Q$ 个询问，每个询问包括 $2$ 个节点 $X$ 和 $Y$，要求算出从 $X$ 到 $Y$ 的一条路径，使得密度最小（密度的定义为，路径上边的权值和除以边的数量）。

## 输入格式

第一行包括两个整数 $N$ 和 $M$。

以下 $M$ 行，每行三个数字 $A,B,W$，表示从 $A$ 到 $B$ 有一条权值为 $W$ 的有向边。

再下一行有一个整数 $Q$。

以下 $Q$ 行，每行一个询问 $X$ 和 $Y$，如题意所诉。

## 输出格式

对于每个询问输出一行，表示该询问的最小密度路径的密度（保留 $3$ 位小数），如果不存在这么一条路径输出“OMG!”（不含引号）。

## 样例

### 样例输入 #1
```
3 3
1 3 5
2 1 6
2 3 6
2
1 3
2 3

```
### 样例输出 #1
```
5.000
5.500

```
## 提示

$1 \le N \le 50$，$1 \le M \le 1000$，$1\le W \le 10^5$，$1 \le Q \le 10^5$



---

---
title: "贪吃虫"
layout: "post"
diff: 提高+/省选-
pid: P1751
tag: ['模拟', '搜索', '图论', '深度优先搜索 DFS']
---
# 贪吃虫
## 题目背景

我们都知道一个很著名的游戏——贪吃蛇。它的一大特点是当前一个食物被吃掉后，后一个食物才会出现。今天我们要做的另一个游戏——贪吃虫也很类似。

## 题目描述

贪吃虫有 $k$ 条，在一棵有 $n$ 个节点的树上，每只虫子都在不同的节点上。第一个食物到来时，所有的 $k$ 只虫会从它们当前的位置出发，前往食物的位置。它们的移动遵循如下规则：

- 这棵树上的任何两个节点之间有且仅有一条路，所有的贪吃虫沿着唯一的路径前往食物所在的位置；
- 如果有一只贪吃虫到达了食物所在的位置，食物马上就被吃掉了；
- 如果有另外一只贪吃虫在某一只贪吃虫通往食物的道路上，那么距离食物较远的那只虫子会停止移动，停留在当前的节点上；
- 如果有多只虫子尝试进入同一个节点，只有编号最小的虫子能够到达，其它的贪吃虫停留在它们当前的位置上；
- 吃掉食物的那只虫子会停留在食物的位置上；
- 食物被吃掉之后会出现在树上的另外一个节点上。这时所有的贪吃虫会重新出发，尝试再一次吃掉食物。为了简化过程，我们假设从一个节点移动到相邻的节点需要花费一个单位时间。

## 输入格式

第 $1$ 行一个整数 $n$，表示树上的节点个数。

第 $2$ 至 $N$ 行，第 $i+1$ 行包含了一个两个整数 $:A_i,B_i$，表示从节点 $A_i$ 到节点 $B_i$ 有一条边直接相连。

第 $N+1$ 行有一个整数 $k$，表示树上贪吃虫的个数。

第 $N+2$ 至 $N+1+k$ 行，第 $N+1+i$ 行有一个整数 $P_i$，表示第 $i$ 只贪吃虫开始时的位置，任何两只贪吃虫的初始位置不相同。

第 $N+2+k$ 行：有一个整数 $h$，表示食物一共在树上出现了多少次。

接下来的 $h$ 行，每行一个整数，表示食物依次出现的位置。
## 输出格式

输出一共包含 $k$ 行，第 $i$ 行有两个整数 $C_i$ 和 $D_i$。分别表示第 $i$ 只贪吃虫最终停留的位置和这只贪吃虫吃到食物的次数。
## 样例

### 样例输入 #1
```
4

1 2

1 3

2 4

2

1

2

2

2

4
```
### 样例输出 #1
```
1 0

4 2


```
## 提示


### 数据范围及约定

对于全部数据，$1 \le n \le 5000$，$1 \le k \le 1000$，$k \le n$，$1 \le h \le 500$。


---

---
title: "天路"
layout: "post"
diff: 提高+/省选-
pid: P1768
tag: ['图论', '二分', '负权环']
---
# 天路
## 题目描述

“那是一条神奇的天路诶 ~~~，把第一个神犇送上天堂 ~~~ ”，XDM 先生唱着这首“亲切”的歌曲，一道猥琐题目的灵感在脑中出现了。

和 C_SUNSHINE 大神商量后，这道猥琐的题目终于出现在本次试题上了，旨在难到一帮大脑不够灵活的 OIer 们（JOHNKRAM 真的不是说你……）。

言归正传，小 $X$ 的梦中，他在西藏开了一家大型旅游公司，现在，他要为西藏的各个景点设计一组铁路线。但是，小 $X$ 发现，来旅游的游客都很挑剔，他们乘火车在各个景点间游览，景点的趣味当然是不用说啦，关键是路上。试想，若是乘火车一圈转悠，却发现回到了游玩过的某个景点，花了一大堆钱却在路上看不到好的风景，那是有多么的恼火啊。

所以，小 $X$ 为所有的路径定义了两个值，$V_i$ 和 $P_i$，分别表示火车线路的风景趣味度和乘坐一次的价格。现在小 $X$ 想知道，乘客从任意一个景点开始坐火车走过的一条回路上所有的 $V$ 之和与 $P$ 之和的比值的最大值。以便为顾客们推荐一条环绕旅游路线（路线不一定包含所有的景点，但是不可以存在重复的火车路线）。

于是，小 $X$ 梦醒之后找到了你……
## 输入格式

第一行两个正整数 $N,M$，表示有 $N$ 个景点，$M$ 条火车路线，火车路线是单向的。

以下 $M$ 行，每行 $4$ 个正整数，分别表示一条路线的起点，终点，$V$ 值和 $P$ 值。

注意，两个顶点间可能有多条轨道，但一次只能走其中的一条。
## 输出格式

一个实数，表示一条回路上最大的比值，保留 $1$ 位小数。

若没有回路，输出 $-1$。
## 样例

### 样例输入 #1
```
5 6

1 2 1 1

4 1 6 2

5 4 8 1

2 3 2 2

5 2 4 1

3 5 6 4
```
### 样例输出 #1
```
2.3
```
## 提示

对于 $30\%$ 的数据，$1 \le N \le 100$，$1 \le M \le 20$；

对于 $60\%$ 的数据，$1 \le N \le 3{,}000$，$1 \le M \le 2{,}000$；

对于 $100\%$ 的数据，$1 \le N \le 7{,}000$，$1 \le M \le 20{,}000$，$1 \le V_i,P_i \le 1{,}000$。

保证答案在 $200$ 以内。

![](https://cdn.luogu.com.cn/upload/image_hosting/e1ywdkfs.png)



---

---
title: "[ZJOI2006] 物流运输"
layout: "post"
diff: 提高+/省选-
pid: P1772
tag: ['动态规划 DP', '图论', '2006', '各省省选', '浙江', 'NOI 导刊', '最短路']
---
# [ZJOI2006] 物流运输
## 题目描述

物流公司要把一批货物从码头 A 运到码头 B。由于货物量比较大，需要 $n$ 天才能运完。货物运输过程中一般要转停好几个码头。  

物流公司通常会设计一条固定的运输路线，以便对整个运输过程实施严格的管理和跟踪。由于各种因素的存在，有的时候某个码头会无法装卸货物。这时候就必须修改运输路线，让货物能够按时到达目的地。  

但是修改路线是—件十分麻烦的事情，会带来额外的成本。因此物流公司希望能够订一个 $n$ 天的运输计划，使得总成本尽可能地小。

## 输入格式

第一行是四个整数 $n,m,k,e$。$n$ 表示货物运输所需天数，$m$ 表示码头总数，$k$ 表示每次修改运输路线所需成本，$e$ 表示航线条数。  

接下来 $e$ 行每行是一条航线描述，包括了三个整数，依次表示航线连接的两个码头编号以及航线长度。其中码头 A 编号为 $1$，码头 B 编号为 $m$。单位长度的运输费用为 $1$。航线是**双向**的。  

再接下来一行是一个整数 $d$，后面的 $d$ 行每行是三个整数 $p,a,b$。表示编号为 $p$ 的码头在 $[a,b]$ 天之内无法装卸货物。同一个码头有可能在多个时间段内不可用。但任何时间都存在至少一条从码头 A 到码头 B 的运输路线。

## 输出格式

包括了一个整数表示最小的总成本。  
总成本为 $n$ 天运输路线长度之和 $+ k \times$ 改变运输路线的次数。

## 样例

### 样例输入 #1
```
  5 5 10 8
  1 2 1
  1 3 3
  1 4 2
  2 3 2
  2 4 4
  3 4 1
  3 5 2
  4 5 2
  4
  2 2 3
  3 1 1
  3 3 3
  4 4 5

```
### 样例输出 #1
```
32
```
## 提示

【数据范围】
对于 $100\%$ 的数据，$1 \le n \le 100$，$1\le m \le 20$, $1 \le k \le 500$, $1 \le e \le 200$。

【样例输入说明】

![](https://cdn.luogu.com.cn/upload/image_hosting/4lcnync6.png)

上图依次表示第 $1$ 至第 $5$ 天的情况，阴影表示不可用的码头。

【样例输出说明】

前三天走 $1 \to 4 \to 5$，后两天走 $1 \to 3 \to 5$，这样总成本为 $(2+2)\times 3+(3+2)\times 2+10=32$。

\_NOI导刊2010提高（01）



---

---
title: "海滩防御"
layout: "post"
diff: 提高+/省选-
pid: P1783
tag: ['图论', '二分', '并查集', '最短路']
---
# 海滩防御
## 题目描述

WLP 同学最近迷上了一款网络联机对战游戏（终于知道为毛 JOHNKRAM 每天刷洛谷效率那么低了），但是他却为了这个游戏很苦恼，因为他在海边的造船厂和仓库总是被敌方派人偷袭。于是，WLP 动用了他那丰满且充实的大脑（或许更偏向前者），想出了一个好主意，他把海滩分成垂直于海岸线的若干列，在其中的几列上放置几个信号塔，试图来监视整个海滩。然而，WLP 是一个非常心急的人，他把信号塔建好后才发现还需给信号塔供能，它们才能投入使用（这不是废话么），它们都有一个工作半径，一个圆形区域里的所有敌人都逃不过它们的监视，不过，WLP 发现，敌人们非常狡猾，除非他将道路完全封死，否则 WLP 的敌人可以走过一条任意弯曲的路（不一定走整点，但是不会出第 $0$ 列和第 $N$ 列构成的边界）来偷他的东西。

于是，WLP 就思考了：到底需要给每个信号塔多大的工作半径，才能将从海滩到内地的路径完全封死呢？他再次动用了他那丰满且充实的大脑，想了一堂数学课，终于，还是没想出来。于是，他向 LZZ 神犇求助（额…… CSUNSHINE 的身份是不是暴露了）。

终于，在 WLP：“ %^!\*@#!\*(\*^!\*#@\$^&（此处省略无数卖萌场景）”的哀求下，LZZ 神犇写了一个程序，在一秒内就解决了问题。但是，邪恶的 LZZ 神犇决定要将这个难题共享给无数无辜的 OIer，所以，现在轮到你了。
## 输入格式

第一行两个整数 $N$ 和 $M$，表示海滩被 WLP 分成的列数 $0,1,2,\cdots,N$ 和信号塔个数。

第 $2$ 至第 $M+1$ 行，每行两个数 $X_i$，$Y_i$ 表示 $1,2,3,\cdots,M$ 号信号塔所在的列数和离开海滩的距离。
## 输出格式

一行一个实数，表示最小的工作半径，保留两位小数。

## 样例

### 样例输入 #1
```
5 5
1 5
3 5
5 5
4 30
2 15
```
### 样例输出 #1
```
1.00
```
### 样例输入 #2
```
100 2
30 50
90 100
```
### 样例输出 #2
```
39.05
```
## 提示

### 数据范围及约定

- 对于 $10\%$ 的数据：$1 \le M \le 10$，$1 \le Y_i \le 100$；
- 对于 $30\%$ 的数据：$1 \le M \le 50$，$1 \le Y_i \le 1,000$；
- 对于 $80\%$ 的数据：$1 \le M \le 500$，$1 \le Y_i \le 1,000$；
- 对于 $100\%$ 的数据：$1 \le M \le 800$，$1 \le N \le 1000$，$1 \le X_i \le N$，$1 \le Y_i \le 100,000$。

### 提示

注意，封锁海滩是指，敌人的深入程度是有限制的，若敌人绕过了所有的信号塔，并且可以长驱直入，那么就说明道路没有完全封锁。


---

---
title: "[JSOI2007] 重要的城市"
layout: "post"
diff: 提高+/省选-
pid: P1841
tag: ['动态规划 DP', '图论', '2007', '各省省选', '江苏']
---
# [JSOI2007] 重要的城市
## 题目描述

参加jsoi冬令营的同学最近发现，由于南航校内修路截断了原来通向计算中心的路，导致去的路程比原先增加了近一公里。而食堂门前施工虽然也截断了原来通向计算中心的路，却没有使路程增加，因为可以找到同样长度的路作替代。其实，问题的关键在于，路截断的地方是交通要点。

同样的情况也出现在城市间的交通中。某些城市如果出了问题，可能会引起其他很多城市的交通不便。另一些城市则影响不到别的城市的交通。jsoi冬令营的同学发现这是一个有趣的问题，于是决定研究这个问题。

他们认为这样的城市是重要的：如果一个城市c被破坏后，存在两个不同的城市a和b（a, b均不等于c），a到b的最短距离增长了（或不通），则城市c是重要的。

jsoi冬令营的同学面对着一张教练组交给他们的城市间交通图，他们希望能找出所有重要的城市。现在就请你来解决这个问题。

## 输入格式

第一行两个整数N,M,N为城市数，M为道路数

接下来M行，每行三个整数，表示两个城市之间的无向边，以及之间的路的长度

## 输出格式

一行，按递增次序输出若干的数，表示重要的城市。

## 样例

### 样例输入 #1
```
4 4
1 2 1
2 3 1
4 1 2
4 3 2
```
### 样例输出 #1
```
2

```
## 提示

30%的数据：$N\le 20$；

60%的数据：$N\le 100$；

100%的数据：$N\le 200,M\le \frac{N\times (N-1)}{2},0<c\le 10000$。c即路的长度。

保证不出现重边和自环

感谢@赵昕鹏 和@qq2477259579 提供程序


如果没有点的话需要输出一行

“No important cities.”

去掉引号



---

---
title: "[USACO08JAN] Telephone Lines S"
layout: "post"
diff: 提高+/省选-
pid: P1948
tag: ['搜索', '图论', '2008', '二分', 'USACO', 'NOI 导刊', '广度优先搜索 BFS']
---
# [USACO08JAN] Telephone Lines S
## 题目描述

Farmer John wants to set up a telephone line at his farm. Unfortunately, the phone company is uncooperative, so he needs to pay for some of the cables required to connect his farm to the phone system.

There are N (1 ≤ N ≤ 1,000) forlorn telephone poles conveniently numbered 1..N that are scattered around Farmer John's property; no cables connect any them. A total of P (1 ≤ P ≤ 10,000) pairs of poles can be connected by a cable; the rest are too far apart.

The i-th cable can connect the two distinct poles Ai and Bi, with length Li (1 ≤ Li ≤ 1,000,000) units if used. The input data set never names any {Ai, Bi} pair more than once. Pole 1 is already connected to the phone system, and pole N is at the farm. Poles 1 and N need to be connected by a path of cables; the rest of the poles might be used or might not be used.

As it turns out, the phone company is willing to provide Farmer John with K (0 ≤ K < N) lengths of cable for free. Beyond that he will have to pay a price equal to the length of the longest remaining cable he requires (each pair of poles is connected with a separate cable), or 0 if he does not need any additional cables.

Determine the minimum amount that Farmer John must pay.

多年以后，笨笨长大了，成为了电话线布置师。由于地震使得某市的电话线全部损坏，笨笨是负责接到震中市的负责人。该市周围分布着 $1\le N\le1000$ 根据 $1\cdots N$ 顺序编号的废弃的电话线杆，任意两根线杆之间没有电话线连接，一共有 $1\le p\le10000$ 对电话杆可以拉电话线。其他的由于地震使得无法连接。

第i对电线杆的两个端点分别是 $a_i$ ，$b_i$，它们的距离为 $1\le l_i\le1000000$。数据中每对 $(a_i,b_i)$ 只出现一次。编号为 $1$ 的电话杆已经接入了全国的电话网络，整个市的电话线全都连到了编号 $N$ 的电话线杆上。也就是说，笨笨的任务仅仅是找一条将 $1$ 号和 $N$ 号电线杆连起来的路径，其余的电话杆并不一定要连入电话网络。

电信公司决定支援灾区免费为此市连接 $k$ 对由笨笨指定的电话线杆，对于此外的那些电话线，需要为它们付费，总费用决定于其中最长的电话线的长度（每根电话线仅连接一对电话线杆）。如果需要连接的电话线杆不超过 $k$ 对，那么支出为 $0$。

请你计算一下，将电话线引导震中市最少需要在电话线上花多少钱？

## 输入格式

输入文件的第一行包含三个数字 $n,p,k$。

第二行到第 $p+1$ 行，每行分别都为三个整数 $a_i,b_i,l_i$。

## 输出格式

一个整数，表示该项工程的最小支出，如果不可能完成则输出 `-1`。

## 样例

### 样例输入 #1
```
5 7 1
1 2 5
3 1 4
2 4 8
3 2 3
5 2 9
3 4 7
4 5 6

```
### 样例输出 #1
```
4

```


---

---
title: "[NOIP 2013 提高组] 货车运输"
layout: "post"
diff: 提高+/省选-
pid: P1967
tag: ['图论', '贪心', '2013', '倍增', '并查集', 'NOIP 提高组', '生成树', '最近公共祖先 LCA']
---
# [NOIP 2013 提高组] 货车运输
## 题目背景

NOIP2013 提高组 D1T3
## 题目描述

A 国有 $n$ 座城市，编号从 $1$ 到 $n$，城市之间有 $m$ 条双向道路。每一条道路对车辆都有重量限制，简称限重。  

现在有 $q$ 辆货车在运输货物， 司机们想知道每辆车在不超过车辆限重的情况下，最多能运多重的货物。

## 输入格式

第一行有两个用一个空格隔开的整数 $ n,m$，表示 A 国有 $ n$ 座城市和 $m$ 条道路。  

接下来 $m$ 行每行三个整数 $x, y, z$，每两个整数之间用一个空格隔开，表示从 $x $ 号城市到 $ y $ 号城市有一条限重为 $z$ 的道路。    
注意： $x \neq y$，两座城市之间可能有多条道路 。

接下来一行有一个整数 $q$，表示有 $q$ 辆货车需要运货。

接下来 $q$ 行，每行两个整数 $x,y$，之间用一个空格隔开，表示一辆货车需要从 $x$ 城市运输货物到 $y$ 城市，保证 $x \neq y$

## 输出格式

共有 $q$ 行，每行一个整数，表示对于每一辆货车，它的最大载重是多少。  
如果货车不能到达目的地，输出 $-1$。

## 样例

### 样例输入 #1
```
4 3
1 2 4
2 3 3
3 1 1
3
1 3
1 4
1 3
```
### 样例输出 #1
```
3
-1
3
```
## 提示

对于 $30\%$ 的数据，$1 \le n < 1000$，$1 \le m < 10,000$，$1\le q< 1000$；

对于 $60\%$ 的数据，$1 \le n < 1000$，$1 \le m < 5\times 10^4$，$1 \le q< 1000$；

对于 $100\%$ 的数据，$1 \le n < 10^4$，$1 \le m < 5\times 10^4$，$1 \le q< 3\times 10^4 $，$0 \le z \le 10^5$。



---

---
title: "无向图三元环计数"
layout: "post"
diff: 提高+/省选-
pid: P1989
tag: ['图论', 'O2优化', '枚举']
---
# 无向图三元环计数
## 题目背景

无向图 $G$ 的三元环指的是一个 $G$ 的一个子图 $G_0$，满足 $G_0$ 有且仅有三个点 $u, v, w$，有且仅有三条边 $\langle u, v \rangle, \langle v, w \rangle, \langle w, u \rangle$。两个三元环 $G_1, G_2$ 不同当且仅当存在一个点 $u$，满足 $u \in G_1$ 且 $u \notin G_2$。
## 题目描述

给定一个 $n$ 个点 $m$ 条边的简单无向图，求其三元环个数。
## 输入格式

每个测试点有且仅有一组测试数据。

输入的第一行是用一个空格隔开的两个整数，分别代表图的点数 $n$ 和边数 $m$。

第 $2$ 到第 $(m + 1)$ 行，每行两个用空格隔开的整数 $u, v$，代表有一条连接节点 $u$ 和节点 $v$ 的边。
## 输出格式

输出一行一个整数，代表该图的三元环个数。
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
1
```
### 样例输入 #2
```
5 8
1 2
2 3
3 5
5 4
4 2
5 2
1 4
3 4

```
### 样例输出 #2
```
5
```
## 提示

**【样例 2 解释】**

共有 $5$ 个三元环，每个三元环包含的点分别是 $\{1, 2, 4\}, \{2, 3, 4\}, \{2, 3, 5\}, \{2, 4, 5\}, \{3, 4, 5\}$。

**【数据规模与约定】**

**本题采用多测试点捆绑测试，共有两个子任务**。

- Subtask 1（30 points）：$n \le 500$，$m \le {10}^3$。
- Subtask 2（70 points）：无特殊性质。

对于 $100\%$ 的数据，$1 \le n \le 10^5$，$1 \le m \le 2 \times {10}^5$，$1 \le u, v \le n$，给出的图不存在重边和自环，**但不保证图连通**。

**【提示】**

- 请注意常数因子对程序效率造成的影响。


---

---
title: "道路值守"
layout: "post"
diff: 提高+/省选-
pid: P2103
tag: ['搜索', '图论', 'O2优化']
---
# 道路值守
## 题目描述

Z-Kingdom 有着四通八达的现代化交通。时值独立庆典之际，随着来自周边国家旅客的日益增多，犯罪行为也悄无声息开始滋长起来。

特别任务支援科的警察们从总部收到了关于调查伪装在游客中的犯罪分子的请求。通过调查，他们得到了一张地图，记载了 Z-Kingdom 内每一条道路的长度。

显然，为了减少犯罪行为被发现的可能性，犯罪分子总是会选择最短的路径来行动。为了方便安排人手和推测犯罪分子采取的路线，他们希望得知任意两个地点之间，有多少条犯罪分子可能会选择的道路。

## 输入格式

第一行，包含两个整数 $N,M$，表示 Z-Kingdom 内的地点数和道路数。

接下来 $N$ 行，每行包含三个整数 $x,y,z$，表示道路连接的两个不同地点的标号，以及道路的长度。道路是双向的。

两个不同地点之间不会有超过一条道路。
## 输出格式

输出一行，包含 $\dfrac{N(N-1)}{2}$ 个整数  $C_{1,2},C_{1,3},\cdots,C_{1,N},C_{2,3},C_{2,4},\cdots,C_{2,N},\cdots,C_{N-1,N}$。

其中 $C_{x, y}$ 表示 x 号地点到 y 号地点之间有多少条犯罪分子可能会选择的道路。

## 样例

### 样例输入 #1
```
5 6
1 2 1
2 3 1
3 4 1
4 1 1
2 4 2
4 5 4
```
### 样例输出 #1
```
1 4 1 2 1 5 6 1 2 1
```
## 提示

【数据规模】

- 对于 $30\%$ 的数据，保证 $N \le 50$；
- 对于 $60\%$ 的数据，保证 $N \le 100$；
- 对于 $100\%$ 的数据，保证 $N \le 500$。



---

---
title: "HXY烧情侣"
layout: "post"
diff: 提高+/省选-
pid: P2194
tag: ['图论', '强连通分量']
---
# HXY烧情侣
## 题目描述

众所周知，HXY 已经加入了 FFF 团。现在她要开始喜（sang）闻（xin）乐（bing）见（kuang）地烧情侣了。

这里有 $n$ 座电影院，$n$ 对情侣分别在每座电影院里，然后电影院里都有汽油，但是要使用它需要一定的费用。$m$ 条单向通道连接相邻的两对情侣所在电影院。

HXY 有个绝技，如果她能从一个点开始烧，最后回到这个点，那么烧这条回路上的情侣的费用只需要该点的汽油费即可。并且每对情侣只需烧一遍，电影院可以重复去。然后她想花尽可能少的费用烧掉所有的情侣。

问：最少需要多少费用，并且当费用最少时的方案数是多少？由于方案数可能过大，所以请输出方案数对 $10^9+7$ 取模的结果。

（注：这里 HXY 每次可以从任何一个点开始走回路。就是说一个回路走完了，下一个开始位置可以任选。所以说不存在烧不了所有情侣的情况，即使图不连通，HXY 自行选择顶点进行烧情侣行动。且走过的道路可以重复走。）
## 输入格式

第一行一个正整数 $n$。   
第二行 $n$ 个正整数，表示每个点的汽油费 $w_i$。  
第三行一个正整数 $m$。  
接下来 $m$ 行，每行两个正整数 $x_i,y_i$，表示一条 $x_i \to y_i$ 的单向道路。
## 输出格式

输出一行两个整数，分别表示最小花费，和花费最小时的方案数。
## 样例

### 样例输入 #1
```
3
1 2 3
3
1 2
2 3
3 2
```
### 样例输出 #1
```
3 1

```
### 样例输入 #2
```
3
10 20 10
4
1 2
1 3
3 1
2 1

```
### 样例输出 #2
```
10 2

```
## 提示

对于 $30\%$ 的数据，$1\le n,m \le 20$；  
对于另外 $10\%$ 的数据，保证不存在回路；  
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le m \le 3\times 10^5$，$0\le w_i \le 10^9$。


---

---
title: "[USACO13OPEN] What's Up With Gravity S"
layout: "post"
diff: 提高+/省选-
pid: P2208
tag: ['模拟', '图论', '2013', 'USACO', '枚举', '分治', '广度优先搜索 BFS']
---
# [USACO13OPEN] What's Up With Gravity S
## 题目描述

Captain Bovidian is on an adventure to rescue her crew member, Doctor Beefalo.  Like all great adventures, this story plays out in a two dimensional N by M grid (1 <= N, M <= 500), representing a side view of the captain's world.  Some grid cells are empty while others are blocked and cannot be traversed.

Unfortunately, Captain Bovidian cannot jump.  She must obey the following rules of physics while traversing her world.

1) If there is no cell directly underneath Captain Bovidian (that is, if she is at the edge of the grid), then she flies out into space and fails her mission.

2) If the cell directly underneath Captain Bovidian is empty, then she falls into that cell.

3) Otherwise:

a) Captain Bovidian may move left or right if the corresponding cell exists and is empty.

b) Or, Captain Bovidian may flip the direction of gravity.

When Captain Bovidian changes the direction of gravity, the cell that's 'underneath' her (as mentioned in rules 1 and 2) toggles between the cell with one higher row index and the cell with one lower row index (the first row in the input has index 1, and the last row has index N). Initially, the cells with one higher row index are underneath Captain Bovidian.

Doctor Beefalo is lost somewhere in this world.  Help Captain Bovidian arrive at her cell using the least number of gravity flips as possible.  If it is impossible to reach Doctor Beefalo, please output -1.


Bovidian 船长正在拯救她的船员，Beefalo 博士。

和所有伟大的冒险故事一样，这个故事也是发生在一个2D平面上的。囧

这个平面是M\*N的格子组成的网格，代表着船长的世界的一个侧视图。

有些格子是空的，另一些则是实心的，并且不能直接通过。

很不幸的是，船长跳不起来。她必须遵守这个世界的特殊物理法则。

1）如果船长的正下方没有方块（换句话说，即使她正在网格的边缘），那么她就会掉入宇宙中，同时意味着冒险失败。

2）如果船长的正下方的方块是空的，那么她就会掉到这个方块，

3）在不满足1）与2）的情况下，船长可以做一下的事情：

a) 如果左边(或右边）的方格是空的，那么她可以走到那个格子。

b船长可以翻转重力的方向

当船长改变翻转重力的方向时，我们就改变船长”下方“的定义。

”下方“的定义只能是两种

(A)比船长位置所在的方格的列编号更大的格子，

(B)比船长位置所在的方格的列编号更小的格子,

一开始的时候，“下方”的定义是比船长位置所在方格的列编号更大的格子。

Beefalo博士正迷失在这个世界中的某一处，请帮助船长从起点到达博士的地方。

如果可以到达，请输出最少需要的翻转重力的次数。


如果不可以到达，请输出-1

## 输入格式

第1行输入两个整数 N,M

第2行到N+1行中，第i+1行则是代表船长世界的第i行。每行有M个字符。

其中","代表着一个空的格子，"#"代表着一个实心的格子，"C"代表着船长的位置，"D"代表着博士的位置。

## 输出格式

一行，输出一个整数。

如果船长可以到达，请输出最少需要的翻转重力的次数。

如果不可以到达，请输出-1

## 样例

### 样例输入 #1
```
5 5
#####
#...#
#...D
#C...
##.##
```
### 样例输出 #1
```
3
```
## 提示

输出解释：

首先，船长在（4,2），接着她翻转重力，到达（2,2）

接着她向右走走到（2,4），接着她第二次翻转重力，到达（4,4）

然后她继续向右走到（4,5），最后在翻转一次重力，到达博士所在的（3,5）



---

---
title: "[HNOI2001] 洗牌机"
layout: "post"
diff: 提高+/省选-
pid: P2227
tag: ['动态规划 DP', '2001', '各省省选', '网络流', '湖南', '图论建模']
---
# [HNOI2001] 洗牌机
## 题目描述

剀剀和凡凡有 $n$ 张牌（依次标号为 $1,2,\ldots,n$）和一台洗牌机。假设 $n$ 是奇数。洗牌机的功能是进行如下的操作：对所有位置 $i(1\le i\le n)$，如果位置 $i$ 上的牌是 $j$，而且位置 $j$ 上的牌是 $k$，那么通过洗牌机后位置 $i$ 上的牌将是 $k$。

剀剀首先写下数值 $1,2,\ldots,n$ 的一个随机排列：$a_1,a_2,\ldots,a_n$。然后他这样来排列牌的顺序：位置 $a_i$ 放置牌 $a_{i+1}$, （对于 $1\le i\le n-1$），而 $a_n$ 放置牌 $a_1$。这样排列后，牌的顺序就为 $x_1,x_2,\ldots ,x_n$。然后，他把这种顺序排列的牌放入洗牌机洗牌 $s$ 次，得到牌的顺序为 $p_1,p_2,\ldots,p_n$。现在，剀剀把牌的最后顺序和洗牌次数告诉凡凡，要凡凡猜出牌的最初顺序 $x_1,x_2,\ldots,x_n$。

## 输入格式

第一行为整数 $n$ 和 $s$。

第二行为牌的最终顺序  $p_1,p_2,\ldots,p_n$。
## 输出格式

为一行，即牌的最初顺序 $x_1,x_2,\ldots,x_n$。
## 样例

### 样例输入 #1
```
5 2          
4 1 5 3 2

```
### 样例输出 #1
```
2 5 4 1 3
```
## 提示

#### 数据规模与约定
对于 $100\%$ 的数据，保证 $1\le n,s\le 10^3$。

数据保证，从 $i=1$ 开始，设第 $i$ 张牌上数是 $j$，则赋值 $i=j$ 后继续此操作，最终会遍历所有牌。


---

---
title: "星际导航"
layout: "post"
diff: 提高+/省选-
pid: P2245
tag: ['图论']
---
# 星际导航
## 题目描述

$\text{sideman}$ 做好了回到 $\text{Gliese}$ 星球的硬件准备，但是 $\text{sideman}$ 的导航系统还没有完全设计好。为了方便起见，我们可以认为宇宙是一张有 $N$ 个顶点和 $M$ 条边的带权无向图，顶点表示各个星系，两个星系之间有边就表示两个星系之间可以直航，而边权则是航行的危险程度。

$\text{sideman}$ 现在想把危险程度降到最小，具体地来说，就是对于若干个询问 $(A, B)$，$\text{sideman}$ 想知道从顶点 $A$ 航行到顶点 $B$ 所经过的最危险的边的危险程度值最小可能是多少。作为 $\text{sideman}$ 的同学，你们要帮助 $\text{sideman}$ 返回家园，兼享受安全美妙的宇宙航行。所以这个任务就交给你了。
## 输入格式

第一行包含两个正整数 $N$ 和 $M$，表示点数和边数。

之后 $M$ 行，每行三个整数 $A$，$B$ 和 $L$，表示顶点 $A$ 和 $B$ 之间有一条边长为 $L$ 的边。顶点从 $1$ 开始标号。

下面一行包含一个正整数 $Q$，表示询问的数目。

之后 $Q$ 行，每行两个整数 $A$ 和 $B$，表示询问 $A$ 和 $B$ 之间最危险的边危险程度的可能最小值。
## 输出格式

对于每个询问， 在单独的一行内输出结果。如果两个顶点之间不可达， 输出 $\text{impossible}$。
## 样例

### 样例输入 #1
```
4 5
1 2 5
1 3 2
2 3 11
2 4 6
3 4 4
3
2 3
1 4
1 2

```
### 样例输出 #1
```
5
4
5

```
## 提示

对于 $40\%$ 的数据，满足 $N \leq 1000, M \leq 3000, Q \leq 1000$。

对于 $80\%$ 的数据，满足 $N \leq 10000, M \leq 10^5, Q \leq 1000$。

对于 $100\%$ 的数据，满足 $N \leq 10^5, M \leq 3 \times 10^5, Q \leq 10^5, L \leq 10^9$。数据不保证没有重边和自环。


---

---
title: "[国家集训队] 墨墨的等式"
layout: "post"
diff: 提高+/省选-
pid: P2371
tag: ['图论', '集训队互测', '最短路']
---
# [国家集训队] 墨墨的等式
## 题目描述

墨墨突然对等式很感兴趣，他正在研究 $\sum_{i=1}^n a_ix_i=b$ 存在非负整数解的条件，他要求你编写一个程序，给定 $n, a_{1\dots n}, l, r$，求出有多少 $b\in[l,r]$ 可以使等式存在非负整数解。
## 输入格式

第一行三个整数 $n,l,r$。

第二行 $n$ 个整数 $a_{1\dots n}$。

## 输出格式

一行一个整数，表示有多少 $b\in[l,r]$ 可以使等式存在非负整数解。

## 样例

### 样例输入 #1
```
2 5 10
3 5

```
### 样例输出 #1
```
5

```
## 提示

对于 $20\%$ 的数据，$n \le 5$，$r \le 10$。

对于 $40\%$ 的数据，$n \le 10$，$r \le 10^6$。

对于 $100\%$ 的数据，$n \le 12$，$0 \le a_i \le 5\times 10^5$，$1 \le l \le r \le 10^{12}$。



---

---
title: "课程"
layout: "post"
diff: 提高+/省选-
pid: P2417
tag: ['图论']
---
# 课程
## 题目描述

有 $n$ 个人与 $m$ 个教室。其中，可以在第 $i$ 个教室上课的学生有 $k_i$ 个，编号分别为 $p_{i,j}$。每个学生都有至少一个教室**可以**上课，并且每个学生**只能**在一个教室上课。

现在询问是否存在一种方案，使得每个教室里至少有一名学生。若可以满足要求，输出 `YES`，否则输出 `NO`。
## 输入格式

第一行是数据组数 $T$，满足 $T\leq 10$。

对于每一组数据，第一行是两个整数 $m,n$（注意输入顺序）。接下来 $m$ 行，第一个数是 $k_i$，后面 $k_i$ 个数 $p_{i,j}$ 表示第 $p_{i,j}$ 名学生可以在第 $i$ 个教室上课。

## 输出格式

每行一个字符串 `YES` 或 `NO`，表示是否存在一种方案满足对应的测试数据。
## 样例

### 样例输入 #1
```
2
3 3
3 1 2 3
2 1 2
1 1
3 3
2 1 3
2 1 3
1 1
```
### 样例输出 #1
```
YES
NO
```
## 提示

$n\leq 2\times 10^4,m\leq 2\times 10^4,T\leq 10$。


---

---
title: "债务清单"
layout: "post"
diff: 提高+/省选-
pid: P2428
tag: ['数学', '图论', '图遍历']
---
# 债务清单
## 题目描述

HZGD 刚刚带领着他的 $N$ 个学生参加完第 LXX 届 NOI。但他的学生发现他们本应该报销的费用还一直拖欠着，于是纷纷找 HZGD 要他给他们报销。不过麻烦的是，学生们总是成双成对的找他，并且只报告他们的债务总和，有的人可能来报告好几次。这让 HZGD 非常难办，他不知道是不是有些人会谎报债务，于是他希望能够列出一张债务清单。

## 输入格式

输入文件第一行包括两个正整数 $N$ 和 $M$，分别表示学生人数和向 HZGD 来报告的总次数，接下来 $M$ 行每行三个整数，分别为来报告的两个学生以及他们报告的债务总和。

## 输出格式

输出文件为一张 $N$ 行的债务清单，第 $i$ 行对应第 $i$ 个学生的债务数额，所有数额保留两位小数。如果无法列出这样一张清单，则输出 `IMPOSSIBLE`。对于有解的数据保证有唯一解。

## 样例

### 样例输入 #1
```
3 3
1 2 2
2 3 4
1 3 6

```
### 样例输出 #1
```
2.00
0.00
4.00

```
## 提示

对于 $30\%$ 的数据，有 $1 ≤ N ≤ 10,1 ≤ M ≤ 55$；

对于 $60\%$ 的数据，有 $1 ≤ N ≤ 100,1 ≤ M ≤ 1000$；

对于 $100\%$ 的数据，有 $1 ≤ N ≤ 1000,1 ≤ M ≤ 10^5$，所有输入数据不超过 $2\times 10^6$。



---

---
title: "[SCOI2012] 滑雪"
layout: "post"
diff: 提高+/省选-
pid: P2573
tag: ['图论', '2012', '四川', '各省省选', '排序', '生成树']
---
# [SCOI2012] 滑雪
## 题目描述

a180285 非常喜欢滑雪。他来到一座雪山，这里分布着 $m$ 条供滑行的轨道和 $n$ 个轨道之间的交点（同时也是景点），而且每个景点都有一编号 $i\space (1 \le i \le n)$ 和一高度 $h_i$。  

a180285 能从景点 $i$ 滑到景点 $j$ 当且仅当存在一条 $i$ 和 $j$ 之间的边，且 $i$ 的高度**不小于** $j$。与其他滑雪爱好者不同，a180285 喜欢用最短的滑行路径去访问尽量多的景点。如果仅仅访问一条路径上的景点，他会觉得数量太少。

于是 a18028 5拿出了他随身携带的时间胶囊。这是一种很神奇的药物，吃下之后可以立即回到上个经过的景点（不用移动也不被认为是 a180285 滑行的距离）。  

请注意，这种神奇的药物是可以连续食用的，即能够回到较长时间之前到过的景点（比如上上个经过的景点和上上上个经过的景点）。 现在，a180285站在 $1$ 号景点望着山下的目标，心潮澎湃。他十分想知道在不考虑时间胶囊消耗的情况下，以最短滑行距离滑到尽量多的景点的方案（即满足经过景点数最大的前提下使得滑行总距离最小）。你能帮他求出最短距离和景点数吗？

## 输入格式

输入的第一行是两个整数 $n,m$。
接下来一行有 $n$ 个整数 $h_i$，分别表示每个景点的高度。

接下来 $m$ 行，表示各个景点之间轨道分布的情况。每行三个整数 $u,v,k$，表示编号为 $u$ 的景点和编号为 $v$ 的景点之间有一条长度为 $k$ 的轨道。

## 输出格式

输出一行，表示 a180285 最多能到达多少个景点，以及此时最短的滑行距离总和。

## 样例

### 样例输入 #1
```
3 3 
3 2 1 
1 2 1 
2 3 1 
1 3 10 
```
### 样例输出 #1
```
3 2
```
## 提示

【数据范围】   
对于 $ 30\% $ 的数据，$ 1 \le n \le 2000 $；   
对于 $ 100\% $ 的数据，$ 1 \le n \le 10^5 $。


对于所有的数据，保证 $ 1 \le m \le 10^6 $ , $ 1 \le h_i \le 10^9 $ ，$ 1 \le k_i \le 10^9 $。



---

---
title: "Explorer"
layout: "post"
diff: 提高+/省选-
pid: P2632
tag: ['图论', '生成树']
---
# Explorer
## 题目背景

提示：本题数据较水，通过本题不代表程序/做法完全正确。
## 题目描述

给出两条直线，上面分别有 $n,m$ 个点，求这 $n+m$ 个点组成的最小生成树。

## 输入格式

输入包括 $5$ 行。 

第一行为 $n$ 和 $m$。

第二行为四个整数 $AX,AY,BX,BY$。

第三行为四个整数 $CX,CY,DX,DY$。 

第四行为 $n$ 个实数，代表在第一条直线上的n个点。对于某个点，用一个实数 $t$ 来表示该点的坐标为 $(AX\times t + BX \times (1 - t), AY \times t + BY \times (1 - t))$。 

第五行为 $m$ 个实数，代表第二条直线上的 $m$ 个点，表示方法同上。

## 输出格式

一行一个实数，为其最小生成树长度，四舍五入至三位小数。

## 样例

### 样例输入 #1
```
4 4 
0 0 10 10 
0 10 10 0 
0.1 0.3 0.6 0.8 
0.1 0.3 0.6 0.8
```
### 样例输出 #1
```
19.638
```
## 提示

$n,m \le 100000$，$AX,AY,BX,BY,CX,CY,DX,DY$ 的绝对值均小于等于 $10^5$，$0 \le t \le 1$。


------------
2024/2/8 添加一组 hack 数据。


---

---
title: "[NOIP 2015 提高组] 运输计划"
layout: "post"
diff: 提高+/省选-
pid: P2680
tag: ['图论', '2015', '二分', 'NOIP 提高组', '最近公共祖先 LCA', '树链剖分']
---
# [NOIP 2015 提高组] 运输计划
## 题目背景

NOIP2015 Day2T3
## 题目描述

公元 $2044$ 年，人类进入了宇宙纪元。

L 国有 $n$ 个星球，还有 $n-1$ 条双向航道，每条航道建立在两个星球之间，这 $n-1$ 条航道连通了 L 国的所有星球。

小 P 掌管一家物流公司， 该公司有很多个运输计划，每个运输计划形如：有一艘物流飞船需要从 $u_i$ 号星球沿最快的宇航路径飞行到 $v_i$ 号星球去。显然，飞船驶过一条航道是需要时间的，对于航道 $j$，任意飞船驶过它所花费的时间为 $t_j$，并且任意两艘飞船之间不会产生任何干扰。

为了鼓励科技创新， L 国国王同意小 P 的物流公司参与 L 国的航道建设，即允许小 P 把某一条航道改造成虫洞，飞船驶过虫洞不消耗时间。

在虫洞的建设完成前小 P 的物流公司就预接了 $m$ 个运输计划。在虫洞建设完成后，这 $m$ 个运输计划会同时开始，所有飞船一起出发。当这 $m$ 个运输计划都完成时，小 P 的物流公司的阶段性工作就完成了。

如果小 P 可以自由选择将哪一条航道改造成虫洞， 试求出小 P 的物流公司完成阶段性工作所需要的最短时间是多少？
## 输入格式

第一行包括两个正整数 $n, m$，表示 L 国中星球的数量及小 P 公司预接的运输计划的数量，星球从 $1$ 到 $n$ 编号。

接下来 $n-1$ 行描述航道的建设情况，其中第 $i$ 行包含三个整数 $a_i, b_i$ 和 $t_i$，表示第 $i$ 条双向航道修建在 $a_i$ 与 $b_i$ 两个星球之间，任意飞船驶过它所花费的时间为 $t_i$。  

接下来 $m$ 行描述运输计划的情况，其中第 $j$ 行包含两个正整数 $u_j$ 和 $v_j$，表示第 $j$ 个运输计划是从 $u_j$ 号星球飞往 $v_j$号星球。
## 输出格式

一个整数，表示小 P 的物流公司完成阶段性工作所需要的最短时间。
## 样例

### 样例输入 #1
```
6 3 
1 2 3 
1 6 4 
3 1 7 
4 3 6 
3 5 5 
3 6 
2 5 
4 5
```
### 样例输出 #1
```
11
```
## 提示

所有测试数据的范围和特点如下表所示

 ![](https://cdn.luogu.com.cn/upload/pic/1831.png) 

**请注意常数因子带来的程序效率上的影响。**

对于 $100\%$ 的数据，保证：$1 \leq a_i,b_i \leq n$，$0 \leq t_i \leq 1000$，$1 \leq u_i,v_i \leq n$。



---

---
title: "逃离"
layout: "post"
diff: 提高+/省选-
pid: P2691
tag: ['图论']
---
# 逃离
## 题目描述

**译自 CLRS Problem 26-1 Escape problem**

在一个 $n\times n$ 的网格中有 $m$ 个起始点 $(x_1, y_1),$ $(x_2, y_2),$ $\dots,$ $(x_m, y_m)$，试问：能否为这些结点分别找一条到边界的路径，且这 $m$ 条路径互不相交（即任意两条路径上没有一个相同的结点）。

![https://i.loli.net/2018/10/14/5bc2ec2948f8b.png](https://i.loli.net/2018/10/14/5bc2ec2948f8b.png)

黑点表示起始点，其他点用白点表示。找出的路径用加粗的线表示。图 (a) 存在符合条件的 $m$ 条路径，图 (b) 则不存在。


## 输入格式

第一行是一个整数，为 $n$ $(1\le n≤35)$。

第二行还是一个整数，为 $m(1\le m\le n^2)$。

以下 $m$ 行，第 $(i+2)$ 行包含两个整数 $x_i$ 和 $y_i$，表示第 $i$ 行第 $j$ 列的点是起始点。保证起始点坐标互不相同。
## 输出格式

只包括一行。若存在逃脱输出 `YES`，不存在逃脱输出 `NO`。
## 样例

### 样例输入 #1
```
6
10
2 2
2 4
2 6
3 1
3 2
3 4
3 6
4 2
4 4
4 6

```
### 样例输出 #1
```
YES
```


---

---
title: "[USACO4.1] 篱笆回路Fence Loops"
layout: "post"
diff: 提高+/省选-
pid: P2738
tag: ['搜索', '图论', 'USACO', '优先队列', '队列']
---
# [USACO4.1] 篱笆回路Fence Loops
## 题目描述

农夫布朗的牧场上的篱笆已经失去控制了。它们分成了1~200英尺长的线段。只有在线段的端点处才能连接两个线段，有时给定的一个端点上会有两个以上的篱笆。结果篱笆形成了一张网分割了布朗的牧场。布朗想将牧场恢复原样，出于这个考虑，他首先得知道牧场上哪一块区域的周长最小。 布朗将他的每段篱笆从1到N进行了标号（N=线段的总数）。他知道每段篱笆有如下属性：

该段篱笆的长度

该段篱笆的一端所连接的另一段篱笆的标号

该段篱笆的另一端所连接的另一段篱笆的标号

幸运的是，没有篱笆连接它自身。对于一组有关篱笆如何分割牧场的数据，写一个程序来计算出所有分割出的区域中最小的周长。

例如，标号1~10的篱笆由下图的形式组成（下面的数字是篱笆的标号）：

```cpp
           1
   +---------------+
   |\             /|
  2| \7          / |
   |  \         /  |
   +---+       /   |6
   | 8  \     /10  |
  3|     \9  /     |
   |      \ /      |
   +-------+-------+
       4       5
```    
上图中周长最小的区域是由2，7，8号篱笆形成的。

## 输入格式

第一行一个整数 $N$（$1 \leq N \leq 100$）；

第 $2$ 行到第 $3\times N+1$ 行：每三行为一组，共 $N$ 组信息：

每组信息的第 $1$ 行有 $4$ 个整数：$s$，这段篱笆的标号（$1\le s\le N$）；$L_s$，这段篱笆的长度（$1\le L_s\le255$）；$N1_s$（$1\le N1_s\le 8$）与本段篱笆的一端所相邻的篱笆的数量；$N2_s$（$1\le N2_s\le 8$）与本段篱笆的另一端所相邻的篱笆的数量。

每组信息的的第 $2$ 行有 $N1_s$ 个整数，分别描述与本段篱笆的一端所相邻的篱笆的标号。

每组信息的的第 $3$ 行有 $N2_s$ 个整数，分别描述与本段篱笆的另一端所相邻的篱笆的标号。`
## 输出格式

输出的内容为单独的一行，用一个整数来表示最小的周长。

## 样例

### 样例输入 #1
```
10
1 16 2 2
2 7
10 6
2 3 2 2
1 7
8 3
3 3 2 1
8 2
4
4 8 1 3
3
9 10 5
5 8 3 1
9 10 4
6
6 6 1 2 
5 
1 10
7 5 2 2 
1 2
8 9
8 4 2 2
2 3
7 9
9 5 2 3
7 8
4 5 10
10 10 2 3
1 6
4 9 5
```
### 样例输出 #1
```
12
```
## 提示

题目翻译来自NOCOW。

USACO Training Section 4.1



---

---
title: "有机化学之神偶尔会做作弊"
layout: "post"
diff: 提高+/省选-
pid: P2783
tag: ['图论', '强连通分量', '最近公共祖先 LCA']
---
# 有机化学之神偶尔会做作弊
## 题目背景

XS 中学化学竞赛组教练是一个酷爱炉石的人。

有一天他一边搓炉石一边监考，而你作为一个信息竞赛的大神也来凑热闹。

然而你的化竞基友却向你求助了。

“第 1354 题怎么做？”<--手语  他问道。
## 题目描述

你翻到那一题：给定一个烃，只含有单键（给初中生的一个理解性解释：就是一堆碳用横线连起来，横线都是单条的）。

然后炎魔之王拉格纳罗斯用他的火焰净化了一切环（？？？）。所有的环状碳都变成了一个碳，如图所示。

![环状碳变为一个碳](https://cdn.luogu.com.cn/upload/pic/2758.png)

然后指定多组碳，求出它们之间总共有多少碳，如图所示（和上图没有关系）。

![求出有多少碳](https://cdn.luogu.com.cn/upload/pic/2759.png)

但是因为在考试，所以你只能把这个答案用手语告诉你的基友。你决定用二进制来表示最后的答案，如图所示（不要在意，和题目没有什么没关系）。

![二进制手语](https://cdn.luogu.com.cn/upload/pic/2760.png)

### 题意简述

给你一个 $n$ 个点，$m$ 条边的无向图。把图中所有的环变为一个点，求变化后某两个点之间有多少个点。
## 输入格式

第一行两个整数 $n$，$m$。表示有 $n$ 个点，$m$ 根键。

接下来 $m$ 行每行两个整数 $u$，$v$ 表示 $u$ 号碳和 $v$ 号碳有一根键。

接下来一个整数 $tot$ 表示询问次数。

接下来 $tot$ 行每行两个整数，$a$，$b$ 表示询问的两个碳的编号。
## 输出格式

共 $tot$ 行，每行一个二进制数，表示答案。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
2
1 2
2 3

```
### 样例输出 #1
```
10
10
```
## 提示

两个碳不成环。

## 数据范围及约定

对于 $100\%$ 的数据，$1<n\le10 ^ 4$，$1<m\le5\times 10 ^ 4$。


---

---
title: "Protect the school"
layout: "post"
diff: 提高+/省选-
pid: P2811
tag: ['图论']
---
# Protect the school
## 题目背景

话说上回保安因为奶牛事件而搞得地位岌岌可危，所以他们决定好好看守这个学校，他们有一个计划。但是由于学校太大了，他们计划不好，所以找到上次帮他的你，请你解决他的苦难。然后他又可以开始了手机游戏之旅。

## 题目描述

学校有 $n$ 个检查点，由于保安懒得动脑筋，他们决定在这 $n$ 个检查点之间建立 $m$ 条通道，由于学校的懒政以及军事化管理，这些路是单向的，逆向通过会被处分。保安们人手不够（游戏任务太多），他们决定只挑选一些点来站岗，由于保安身怀绝技，可以瞬间通过任何他站岗点可以走到的路（瞬移到到任何连通的点）。每一个检查点有一个值表示这个点的困难程度。为了保护学校，请你帮他们出个主意，保证一旦有一个检查点发生事件，都能有保安瞬间抵达。但是为了舒服和管理便利，请你告诉他们在使用最少的保安数量的情况下最小的困难总和。

## 输入格式

第一行一个整数 $n$，代表检查点数量。

接下来一行 $n$ 个整数，代表困难程度。

接下来一行一个数 $m$，表示道路的数量。

接下来 $m$ 行每行两个整数 $u,v$ 代表 $u$ 到 $v$ 有一条单向通道。
## 输出格式

两个整数。

第一个整数表示最小困难和。第二个整数表示在保证最小困难和以及最少保安数量的条件下，可选的方案总数。

## 样例

### 样例输入 #1
```
5
31619 26195 18669 1198 178
4
2 4
3 5
1 2
4 1
```
### 样例输出 #1
```
20045 1
```
## 提示

$1 \le n \le 10 ^ 4,1 \le m \le 5 \times 10 ^ 4$，保证答案在 `int` 范围内。


---

---
title: "校园网络【[USACO]Network of Schools加强版】"
layout: "post"
diff: 提高+/省选-
pid: P2812
tag: ['图论', '强连通分量']
---
# 校园网络【[USACO]Network of Schools加强版】
## 题目背景

浙江省的几所 OI 强校的神犇发明了一种人工智能，可以 AC 任何题目，所以他们决定建立一个网络来共享这个软件。但是由于他们脑力劳动过多导致全身无力身体被♂掏♂空，他们来找你帮助他们。

## 题目描述

共有 $n$ 所学校 $(1 \leq n \leq 10000)$ 已知他们实现设计好的网络共 $m$ 条线路，为了保证高速，网络是单向的。现在请你告诉他们至少选几所学校作为共享软件的母机，能使每所学校都可以用上。再告诉他们至少要添加几条线路能使任意一所学校作为母机都可以使别的学校使用上软件。

## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行每行有若干个整数，用空格隔开。

第 $i+1$ 行，每行输入若干个非零整数 $x$，表示从 $i$ 到 $x$ 有一条线路。以 $0$ 作为结束标志。

## 输出格式

第一行一个整数，表示至少选几所学校作为共享软件的母机，能使每所学校都可以用上。

第二行一个整数，表示至少要添加几条线路能使任意一所学校作为母机都可以使别的学校使用上软件。
## 样例

### 样例输入 #1
```
5
2 0
4 0
5 0
1 0
0

```
### 样例输出 #1
```
2
2
```
## 提示

~~POJ 原题。数据扩大了 $100$ 倍。~~

~~$1 \leq $ 边数 $\leq 5000000$，$1 \leq n \leq 10000$ 。~~

实际上，$1 \leq n \leq 10000$，$1\le $ 边数 $\le 50000$。


---

---
title: "行路难【疑似 std 复杂度有误】"
layout: "post"
diff: 提高+/省选-
pid: P2832
tag: ['图论']
---
# 行路难【疑似 std 复杂度有误】
## 题目背景

小X来到了山区，领略山林之乐。在他乐以忘忧之时，他突然发现，开学迫在眉睫

## 题目描述

山区有 $n$ 座山。山之间有 $m$ 条羊肠小道，每条连接两座山，只能单向通过，并会耗费小 X 一定时间。

小 X 现在在 $1$ 号山，他的目的是 $n$ 号山，因为那里有火车站。

然而小 X 的体力是有限的。他每通过一条羊肠小道，就会变得更疲劳，导致他通过任意一条羊肠小道的时间都增加 $1$。
## 输入格式

第一行两个数，$n,m$。

第 $2$ 行到第 $m+1$ 行，每行 $3$ 个数 $A, B, C$，表示 $A$ 、 $B$ 之间有一条羊肠小道，可以让小 X 花费 $C$ 的时间从 $A$ 移动到 $B$。
## 输出格式


第一行一个数 $T$，表示小 X 需要的最短时间。

第二行若干个数，用空格隔开，表示小 X 的移动路线。例如，$[1, 4, 2, 5]$ 表示小 $X$ 从 $1$ 号山开始，移动到 $4$ 号山，再到 $2$ 号山，最后到 $5$ 号山。

## 样例

### 样例输入 #1
```
5 8
2 4 2
5 2 1
1 2 1
4 3 2
1 3 3
4 5 2
1 5 8
3 5 3

```
### 样例输出 #1
```
7
1 3 5 

```
## 提示

### 数据范围及约定

对于全部数据，$n \le 10^4$，$m \le 2\times 10^5$。

数据保证没有多条最短路径。


---

---
title: "[USACO06JAN] Redundant Paths G"
layout: "post"
diff: 提高+/省选-
pid: P2860
tag: ['图论', '2006', 'USACO', '强连通分量', '位运算']
---
# [USACO06JAN] Redundant Paths G
## 题目描述

In order to get from one of the F (1 <= F <= 5,000) grazing fields (which are numbered 1..F) to another field, Bessie and the rest of the herd are forced to cross near the Tree of Rotten Apples.  The cows are now tired of often being forced to take a particular path and want to build some new paths so that they will always have a choice of at least two separate routes between any pair of fields. They currently have at least one route between each pair of fields and want to have at least two. Of course, they can only travel on Official Paths when they move from one field to another.


Given a description of the current set of R (F-1 <= R <= 10,000) paths that each connect exactly two different fields, determine the minimum number of new paths (each of which connects exactly two fields) that must be built so that there are at least two separate routes between any pair of fields. Routes are considered separate if they use none of the same paths, even if they visit the same intermediate field along the way.


There might already be more than one paths between the same pair of fields, and you may also build a new path that connects the same fields as some other path.

## 输入格式

Line 1: Two space-separated integers: F and R




Lines 2..R+1: Each line contains two space-separated integers which are the fields at the endpoints of some path.

## 输出格式

Line 1: A single integer that is the number of new paths that must be built.

## 样例

### 样例输入 #1
```
7 7
1 2
2 3
3 4
2 5
4 5
5 6
5 7
```
### 样例输出 #1
```
2
```
## 提示

Explanation of the sample:




One visualization of the paths is:

![](https://cdn.luogu.com.cn/upload/image_hosting/cubnel5k.png)

Building new paths from 1 to 6 and from 4 to 7 satisfies the conditions.

![](https://cdn.luogu.com.cn/upload/image_hosting/rgguiytp.png)

Check some of the routes:

- 1 – 2:  1 –> 2 and 1 –> 6 –> 5 –> 2
- 1 – 4:  1 –> 2 –> 3 –> 4 and 1 –> 6 –> 5 –> 4
- 3 – 7:  3 –> 4 –> 7 and 3 –> 2 –> 5 –> 7

Every pair of fields is, in fact, connected by two routes.

It's possible that adding some other path will also solve the problem (like one from 6 to 7). Adding two paths, however, is the minimum.

## 题目翻译

为了从 $F(1 \le F \le 5000)$ 个草场中的一个走到另一个，贝茜和她的同伴们有时不得不路过一些她们讨厌的可怕的树．奶牛们已经厌倦了被迫走某一条路，所以她们想建一些新路，使每一对草场之间都会至少有两条相互分离的路径，这样她们就有多一些选择。

每对草场之间已经有至少一条路径．给出所有 $R\ (F-1 \le R \le 10000)$ 条双向路的描述，每条路连接了两个不同的草场，请计算最少的新建道路的数量，路径由若干道路首尾相连而成．两条路径相互分离，是指两条路径没有一条重合的道路．但是，两条分离的路径上可以有一些相同的草场．对于同一对草场之间，可能已经有两条不同的道路，你也可以在它们之间再建一条道路，作为另一条不同的道路。


---

---
title: "[USACO16DEC] Lasers and Mirrors G"
layout: "post"
diff: 提高+/省选-
pid: P3036
tag: ['搜索', '2016', 'USACO', '图论建模', '最短路']
---
# [USACO16DEC] Lasers and Mirrors G
## 题目描述

For some reason, Farmer John's cows always seem to be running laser light shows.

For their latest show, the cows have procured a large powerful laser -- so large,in fact, that they cannot seem to move it easily from the location where it was delivered. They would like to somehow send the light from the laser to the barn on the other side of FJ's property.  Both the laser and the barn can be considered to be located at points in the 2D plane on a map of FJ's farm.  The cows plan to point the laser so that it sends a beam of light out either horizontally or vertically (i.e.,  aligned with the x or y axes).  They will then bounce this beam off a number of mirrors to direct it to the barn.

On the farm there are $N$ fence posts ($1 \leq N \leq 100,000$) located at distinct 2D points (also distinct from the laser and the barn) at which the cows can mount mirrors.  The cows can choose not to mount a mirror on a fence post, in which case the laser would simply pass straight over the top of the post without changing direction.  If the cows do mount a mirror on a fence post, they align it diagonally like / or \ so that it will re-direct a horizontal beam of light in a vertical direction or vice versa.

Please compute the minimum possible number of mirrors the cows need to use in order to re-direct the laser to the barn.

## 输入格式

The first line of input contains 5 space-separated integers: $N, x_L, y_L, x_B, y_B$, where $(x_L, y_L)$ is the location of the laser and $(x_B, y_B)$ is the location of the barn.  All coordinates are between $0$ and $1,000,000,000$.

The next $N$ lines each contain the $x$ and $y$ locations of a fence post, both integers in the range $0 \ldots 1,000,000,000$.
## 输出格式

Please output the minimum number of mirrors needed to direct the laser to the barn, or -1 if this is impossible to do.
## 样例

### 样例输入 #1
```
4 0 0 7 2
3 2
0 2
1 6
3 0
```
### 样例输出 #1
```
1
```
## 题目翻译

### 题目描述

出于某种原因，Farmer John 的奶牛似乎总是在举办激光表演。

在它们的最新表演中，奶牛们获得了一台大型强力激光器——事实上，这台激光器太大，以至于它们无法轻易从交付地点移动它。它们希望以某种方式将激光器的光束发送到 Farmer John 的农场另一边的谷仓。激光器和谷仓都可以被视为位于 Farmer John 农场地图的二维平面中的点。奶牛们计划将激光器指向水平或垂直方向（即与 $x$ 轴或 $y$ 轴对齐），然后通过多次反射镜将光束引导到谷仓。

农场上有 $N$ 个栅栏柱（$1 \leq N \leq 100,000$），位于与激光器和谷仓不同的二维点上，奶牛们可以在这些栅栏柱上安装反射镜。奶牛们可以选择不在栅栏柱上安装反射镜，在这种情况下，激光器会直接穿过栅栏柱而不改变方向。如果奶牛们在栅栏柱上安装反射镜，它们会将其对角线对齐，例如 / 或 \，以便将水平光束重新定向为垂直方向，反之亦然。

请计算奶牛们将激光器引导到谷仓所需的最少反射镜数量。

### 输入格式

输入的第一行包含 $5$ 个用空格分隔的整数：$N, x_L, y_L, x_B, y_B$，其中 $(x_L, y_L)$ 是激光器的位置，$(x_B, y_B)$ 是谷仓的位置。所有坐标都在 $0$ 到 $1,000,000,000$ 之间。

接下来的 $N$ 行每行包含一个栅栏柱的 $x$ 和 $y$ 位置，这两个整数都在 $0 \ldots 1,000,000,000$ 范围内。

### 输出格式

请输出将激光器引导到谷仓所需的最少反射镜数量，如果无法实现，则输出 -1。


---

---
title: "[USACO14MAR] Counting Friends G"
layout: "post"
diff: 提高+/省选-
pid: P3104
tag: ['图论', '2014', '二分', 'USACO', '生成树']
---
# [USACO14MAR] Counting Friends G
## 题目描述

Farmer John's N cows (2 <= N <= 500) have joined the social network "MooBook".

Each cow has one or more friends with whom they interact on MooBook.  Just for fun, Farmer John makes a list of the number of friends for each of his cows, but during the process of writing the list he becomes distracted, and he includes one extra number by mistake (so his list contains N+1 numbers, instead of N numbers as he intended).

Please help Farmer John figure out which numbers on his list could have been the erroneous extra number.

FJ又有n(1<=n<=500)头奶牛都有一个或一个以上的朋友。FJ记录每头牛的朋友数，但他傻不小心混入了一个错的数字，请找出。

## 输入格式

\* Line 1: The integer N.

\* Lines 2..2+N: Line i+1 contains the number of friends for one of FJ's cows, or possibly the extra erroneous number.

## 输出格式

\* Line 1: An integer K giving the number of entries in FJ's list that could be the extra number (or, K=0 means that there is no number on the list whose removal yields a feasible pairing of friends).

\* Lines 2..1+K: Each line contains the index (1..N+1) within the input ordering of a number of FJ's list that could potentially be the extra number -- that is, a number that can be removed such that the remaining N numbers admit a feasible set of

friendships among the cows.  These lines should be in sorted order.

## 样例

### 样例输入 #1
```
4 
1 
2 
2 
1 
3 

```
### 样例输出 #1
```
3 
1 
4 
5 

```
## 提示

Farmer John has 4 cows.  Two cows have only 1 friend each, two cows have 2 friends each, and 1 cow has 3 friends (of course, one of these numbers is extra and does not belong on the list).


Removal of the first number in FJ's list (the number 1) gives a remaining list of 2,2,1,3, which does lead to a feasible friendship pairing -- for example, if we name the cows A..D, then the pairings (A,B), (A,C), (A,D), and (B,C) suffice, since A has 3 friends, B and C have 2 friends, and D has 1 friend.  Similarly, removing the other "1" from FJ's list also works, and so does removing the "3" from FJ's list.  Removal of either "2" from FJ's list does not work -- we can see this by the fact that the sum of the remaining numbers is odd, which clearly prohibits us from finding a feasible pairing.



---

---
title: "跳楼机"
layout: "post"
diff: 提高+/省选-
pid: P3403
tag: ['图论']
---
# 跳楼机
## 题目背景

DJL 为了避免成为一只咸鱼，来找 srwudi 学习压代码的技巧。

## 题目描述

Srwudi 的家是一幢 $h$ 层的摩天大楼。由于前来学习的蒟蒻越来越多，srwudi 改造了一个跳楼机，使得访客可以更方便的上楼。

经过改造，srwudi 的跳楼机可以采用以下四种方式移动：

1. 向上移动 $x$ 层；
2. 向上移动 $y$ 层；
3. 向上移动 $z$ 层；
4. 回到第一层。

一个月黑风高的大中午，DJL 来到了 srwudi 的家，现在他在 srwudi 家的第一层，碰巧跳楼机也在第一层。DJL 想知道，他可以乘坐跳楼机前往的楼层数。
## 输入格式

第一行一个整数 $h$，表示摩天大楼的层数。

第二行三个正整数，分别表示题目中的 $x, y, z$。
## 输出格式

一行一个整数，表示 DJL 可以到达的楼层数。

## 样例

### 样例输入 #1
```
15
4 7 9

```
### 样例输出 #1
```
9

```
### 样例输入 #2
```
33333333333
99005 99002 100000

```
### 样例输出 #2
```
33302114671

```
## 提示

可以到达的楼层有：$1,5,8,9,10,12,13,14,15$。

$1 \le h \le 2^{63}-1$，$1 \le x,y,z \le 10^5$。


---

---
title: "[POI 2011] SMI-Garbage"
layout: "post"
diff: 提高+/省选-
pid: P3520
tag: ['图论', '2011', 'POI（波兰）', 'Special Judge', '欧拉回路']
---
# [POI 2011] SMI-Garbage
## 题目描述

有一个可以看成无向图的城市，上面有 $n$ 个点和 $m$ 条边。

每一天，有若干辆垃圾车按照**环形**来跑一圈。并且，**对于一辆垃圾车，** 除了起点以外不能跑两次。

一条路有 $2$ 种状态：清洁的（用 `0` 表示）或不清洁的（用 `1` 表示）。每次垃圾车经过，都会改变这条路的状态。

因为有些路上的人不交垃圾清理费，所以市长想要那些路变得不清洁；除此之外的路要清洁。那么，如何安排垃圾车，才能使得市长目的达到呢？

By @[dengziyue](/user/387840)

感谢 @cn：苏卿念 提供SPJ
## 输入格式

输入的第一行包含两个空格分隔的正整数 $n$ 和 $m$ $（ 1 \leqslant n \leqslant 100000，1 \leqslant m \leqslant 1000000）$，表示图的点数和边数。

接下来 $m$ 行，每行包含四个空格分隔的正整数 $a,b,s,t $（ $1 \leqslant a \leqslant b \leqslant n $ , $s，t \in \lbrace0,1\rbrace$  ） ，表示一条联结结点 $a$ 与 $b$ 的边，初始颜色和目标颜色分别为 $s$ 与 $t$ 。

你可以认为若存在合法方案，则存在一个卡车经过总边数不超过 $5m$ 的方案。

对于 $60\%$ 分数的数据，有 $ m \leqslant 10000$。
## 输出格式

如果不存在合法方案，输出一行 `NIE`（波兰语「否」）；

否则按下列格式输出任意一种方案：

- 第一行包含一个整数 $k$，表示卡车行驶环路的总数；
- 接下来 $k$ 行，每行描述一条环路：
   - 首先是一个正整数 $k_i$ 表示环路经过的边数，后接一个空格；
  - 接下来 $ k_i + 1 $ 个空格分隔的整数，依次表示环路上结点的编号。
## 样例

### 样例输入 #1
```
6 8
1 2 0 1
2 3 1 0
1 3 0 1
2 4 0 0
3 5 1 1
4 5 0 1
5 6 0 1
4 6 0 1
```
### 样例输出 #1
```
2
3 1 3 2 1
3 4 6 5 4
```


---

---
title: "[POI 2013] MOR-Tales of seafaring"
layout: "post"
diff: 提高+/省选-
pid: P3556
tag: ['图论', '2013', 'POI（波兰）']
---
# [POI 2013] MOR-Tales of seafaring
## 题目描述

Young Bytensson loves to hang out in the port tavern, where he often    listens to the sea dogs telling their tales of seafaring.

Initially, he believed them all, however incredible they sounded.

Over time though, he became suspicious.

He has decided to write a program that will verify if there may be    any grain of truth in those tall stories.

Bytensson reasoned that while he cannot tell if the sailors indeed    weathered all those storms, he can at least find out if their travel    itineraries make sense.

This is a task for a programmer, which Bytensson, unfortunately, is not.

Help him out!

There are $n$ ports and $m$ waterways connecting them in the waters    frequented by the sailors Bytensson listened to.

If there is a waterway between two ports, then sailing from one to the    other is possible.  Any waterway can be sailed in both    directions.

Bytensson got to know $k$ seafaring tales.

Each tells of a sailor who began his journey in one port,    sailed a number of waterways, and ended up in another port,    which may have been the one he initially set sail from.

The sailor in question may have sailed through the same waterway    many times, each time in any direction.

给n个点m条边无向图，每次询问两个点之间是否有长度为d的路径（不一定是简单路径）

## 输入格式

In the first line of the standard input, there are three integers, $n$,$m$ and $k$ ($2\le n\le 5\ 000$, $1\le m\le 5\ 000$, $1\le k\le 1\ 000\ 000$).

These denote, respectively: the number of ports in the waters      frequented by the sailors who told Bytensson their stories,the number of waterways, and the number of tales.

The $m$ lines that follow specify the waterways.

A single waterway's description consists of a single line that contains two integers, $a$ and $b$ ($1\le a,b\le n$,$a\ne b$), separated by a single space; these specify the numbers of ports at the two ends of this particular waterway.

The $k$ lines that follow specify the tales that Bytensson has heard. A single tale's description consists of a single line with three integers,$s$,$t$,and $d$ ($1\le s,t\le n$,$1\le d\le 1\ 000\ 000\ 000$ ), separated by single spaces. These indicate that the tale's protagonist set sail from port no. $s$ , ended the journey in port no. $t$ , and sailed exactly $d$ times through various waterways.

## 输出格式

Your program should print exactly $k$ lines to the standard output; the $i$-th of them should contain the word TAK (Polish for yes) if the journey described in the $i$-th tale(in input order) could have taken place.

If it could not, then the line should contain the word NIE (Polish for no).

## 样例

### 样例输入 #1
```
8 7 4
1 2
2 3
3 4
5 6
6 7
7 8
8 5
2 3 1
1 4 1
5 5 8
1 8 10

```
### 样例输出 #1
```
TAK
NIE
TAK
NIE

```
## 提示

给n个点m条边无向图，每次询问两个点之间是否有长度为d的路径（不一定是简单路径）



---

---
title: "主主树"
layout: "post"
diff: 提高+/省选-
pid: P3701
tag: ['字符串', '网络流', '洛谷原创', '图论建模']
---
# 主主树
## 题目背景

byx 和诗乃酱都非常都非常喜欢种树。有一天，他们得到了两颗奇怪的树种，于是各自取了一颗回家种树，并约定几年后比一比谁种出来的树更加牛 X。
## 题目描述

很快，这棵树就开花结果了。byx 和诗乃酱惊讶的发现，这是一棵主主树，树上长满了主主和主主的朋友们。这棵树上一共有五种人，主主（$\verb!J!$），记记（$\verb!HK!$），高高（$\verb!W!$），王王（$\verb!E!$）和歪歪（$\verb!YYY!$）。他们发现，他们的主主树上的人数相同，都为 $N$。

 ![](https://cdn.luogu.com.cn/upload/image_hosting/0vklm8ow.png) 

研究发现，这五种人的输赢如上图所示（一样的人不能 PK），箭头指向输的人。至于为什么，留给同学们自己思考。

比赛如期进行。

byx 和诗乃酱要进行 $M$ 场比赛，每一场比赛他们会选出树上的两个人来比较看谁更牛 X。

第 $i$ 个人寿命为 $\text{Life}_i$ 秒，每次比完赛他们就会 $-1$s。当他们生命为 $0$s 时他们就不能再比赛了。

同时，当 $\verb!J!$ 的寿命为 $0$ 时，同一棵树上的 $\verb!YYY!$ 可以为他 $+1$s。每个 $\verb!YYY!$ 只能给每个 $\verb!J!$ 续一次。

那么问题来了：

现在给定 $N,M(1\le N\le 100,1\le M\le 1000)$，诗乃酱和 byx 每一个人所属种类（$\verb!J!,\verb!HK!,\verb!W!,\verb!YYY!$ 或 $\verb!E!$）以及每一个人的生命，生命不超过 $50$。请你算算 byx 最多能够赢得多少场比赛呢。

数据保证每一场一定都有人用。两个人之间只能比一场。
## 输入格式

第一行包含两个数 $N,M$，含义看上面。  

第二行 $N$ 个字串（$\verb!J!,\verb!HK!,\verb!W!,\verb!YYY!$ 或 $\verb!E!$），表示 byx 的人所属种类，用空格隔开。  

第三行 $N$ 个字串（$\verb!J!,\verb!HK!,\verb!W!,\verb!YYY!$ 或 $\verb!E!$），表示诗乃酱的人所属种类，用空格隔开。  

第四行 $N$ 个数，表示 byx 的人的生命。  

第五行 $N$ 个数，表示诗乃酱的人的生命。  
## 输出格式

一个数，byx 能赢的场次。
## 样例

### 样例输入 #1
```
3 3
J W YYY
J HK E
2 2 2
2 2 2

```
### 样例输出 #1
```
3

```
## 提示

第一场主主赢记记，第二场高高赢王王，第三场歪歪赢记记。



---

---
title: "[SHOI2012] 回家的路"
layout: "post"
diff: 提高+/省选-
pid: P3831
tag: ['图论', '2012', '各省省选', '上海', '最短路']
---
# [SHOI2012] 回家的路
## 题目背景

SHOI2012 D2T1

## 题目描述

2046 年 OI 城的城市轨道交通建设终于全部竣工，由于前期规划周密，建成后的轨道交通网络由$2n$条地铁线路构成，组成了一个$n$纵$n$横的交通网。如下图所示，这$2n$条线路每条线路都包含$n$个车站，而每个车站都在一组纵横线路的交汇处。


出于建设成本的考虑，并非每个车站都能够进行站内换乘，能够进行站内换乘的地铁站共有$m$个，在下图中，标上方块标记的车站为换乘车站。已知地铁运行 1 站需要 2 分钟，而站内换乘需要步行 1 分钟。Serenade 想要知道，在不中途出站的前提下，他从学校回家最快需要多少时间（等车时间忽略不计）。


![](https://cdn.luogu.com.cn/upload/pic/6547.png)

## 输入格式

第一行有两个整数$n,m$。

接下去$m$行每行两个整数$x,y$,表示第$x$条横向线路与第$y$条纵向线路的交

汇站是站内换乘站。

接下去一行是四个整数$x_1,y_1,x_2,y_2$。表示 Serenade 从学校回家时，在第 $x_1$条横向线路与第$y_1$条纵向线路的交汇站上车，在第$x_2$条横向线路与第$y_2$条纵向线路的交汇站下车。

## 输出格式

输出文件只有一行，即 Serenade 在合理选择线路的情况下，回家所需要的时间。如果 Serenade 无法在不出站换乘的情况下回家，请输出-1。

## 样例

### 样例输入 #1
```
2 1
1 2
1 1 2 2
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
6 9
2 1
2 5
3 2
4 4
5 2
5 6
6 1
6 3
6 4
1 1 4 6
```
### 样例输出 #2
```
27
```
### 样例输入 #3
```
6 10
2 1
2 5
3 2
4 4
5 2
5 6
6 1
6 3
6 4
6 6
1 1 4 6
```
### 样例输出 #3
```
26
```
## 提示

对于 30%的数据，$n\le 50,m\le 1000$；

对于 60%的数据，$n\le 500,m\le 2000$；

对于 100%的数据，$n\le 20000,m\le 100000$；



---

---
title: "圈的异或"
layout: "post"
diff: 提高+/省选-
pid: P3907
tag: ['数学', '图论']
---
# 圈的异或
## 题目描述

给出无向图G，边$(A_i,B_i)$ 的权是$C_i$，判断下列性质是否成立：

对于任意圈C，其边权的异或和是0

## 输入格式

第1 行，1 个整数T，表示数据的组数。

每组数据第1 行，2 个整数$N,M$，表示图G 点和边的数量。

M 行，每行3 个整数$A_i,B_i,C_i$

## 输出格式

对每个数据输出一行，“Yes” 或者“No”

## 样例

### 样例输入 #1
```
2
3 3
1 2 1
2 3 2
3 1 3
1 1
1 1 1
```
### 样例输出 #1
```
Yes
No
```
## 提示

• 对于50% 的数据，$N,M \le 20$

• 对于100% 的数据，$1 \le N,M \le 50 , 1 \le A_i,B_i \le N , 0 \le C_i < 2^{16}$



---

---
title: "[TJOI2013] 黄金矿工"
layout: "post"
diff: 提高+/省选-
pid: P3961
tag: ['2013', '各省省选', '排序', '背包 DP', '图论建模', '天津']
---
# [TJOI2013] 黄金矿工
## 题目描述

小 A 最近迷上了在上课时玩《黄金矿工》这款游戏。为了避免被老师发现，他必须小心翼翼，因此他总是输。

在输掉自己所有的金币后，他向你求助。每个黄金可以看做一个点（没有体积）。现在给出你 $N$ 个黄金的坐标，挖到它们所需要的时间以及它们的价值。有些黄金在同一条直线上，这时候你必须按顺序挖。你可以瞬间把钩子转到任意角度。

小 A 一开始在坐标 $(0,0)$，请你帮助小 A 算出在时间 $T$ 内他最多可以得到多少价值的金子。
## 输入格式

第一行两个整数 $N$ 和 $T$，表示黄金的个数和总时间。

接下来 $N$ 行，每行四个整数 $x$、$y$、$t$、$v$，分别表示黄金的坐标，挖到这个黄金的时间，以及这个黄金的价值。
## 输出格式

一个整数,表示你可以在 $T$ 时间内得到的最大价值。
## 样例

### 样例输入 #1
```
3 10
1 1 1 1
2 2 2 2
1 3 15 9
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3 10
1 1 13 1
2 2 2 2
1 3 4 7
```
### 样例输出 #2
```
7
```
## 提示

- 对于 $30\%$ 的数据，$0<T\le 4\times 10^3$；
- 对于 $100\%$ 的数据，$1\le N\le 200$，$0<T\le 4\times 10^4$。

保证 $0\le|x|\le 200$，$0<y≤200$，$0<t\le 200$，$0\le v\le 200$。


---

---
title: "孤岛营救问题"
layout: "post"
diff: 提高+/省选-
pid: P4011
tag: ['O2优化', '广度优先搜索 BFS', '图论建模', '进制', '网络流与线性规划 24 题', '状压 DP']
---
# 孤岛营救问题
## 题目描述

$1944$ 年，特种兵麦克接到国防部的命令，要求立即赶赴太平洋上的一个孤岛，营救被敌军俘虏的大兵瑞恩。瑞恩被关押在一个迷宫里，迷宫地形复杂，但幸好麦克得到了迷宫的地形图。迷宫的外形是一个长方形，其南北方向被划分为 $N$ 行，东西方向被划分为 $M$ 列，于是整个迷宫被划分为 $N\times M$ 个单元。每一个单元的位置可用一个有序数对(单元的行号，单元的列号)来表示。南北或东西方向相邻的 $2$ 个单元之间可能互通，也可能有一扇锁着的门，或者是一堵不可逾越的墙。迷宫中有一些单元存放着钥匙，并且所有的门被分成$P$ 类，打开同一类的门的钥匙相同，不同类门的钥匙不同。


大兵瑞恩被关押在迷宫的东南角，即 $(N,M)$ 单元里，并已经昏迷。迷宫只有一个入口，在西北角。也就是说，麦克可以直接进入 $(1,1)$ 单元。另外，麦克从一个单元移动到另一个相邻单元的时间为 $1$，拿取所在单元的钥匙的时间以及用钥匙开门的时间可忽略不计。


试设计一个算法，帮助麦克以最快的方式到达瑞恩所在单元，营救大兵瑞恩。

## 输入格式

第 $1$ 行有 $3$ 个整数，分别表示 $N,M,P$ 的值。

第 $2$ 行是 $1$ 个整数 $K$，表示迷宫中门和墙的总数。

第 $I+2$ 行$(1\leq I\leq K)$，有 $5$ 个整数，依次为$X_{i1},Y_{i1},X_{i2},Y_{i2},G_i$：

- 当 $G_i \geq 1$ 时，表示 $(X_{i1},Y_{i1})$ 单元与 $(X_{i2},Y_{i2})$ 单元之间有一扇第 $G_i$ 类的门

- 当 $G_i=0$ 时，表示 $(X_{i1},Y_{i1})$ 单元与 $(X_{i2},Y_{i2})$ 单元之间有一堵不可逾越的墙（其中，$|X_{i1}-X_{i2}|+|Y_{i1}-Y_{i2}|=1$，$0\leq G_i\leq P$）。

第 $K+3$ 行是一个整数 $S$，表示迷宫中存放的钥匙总数。

第 $K+3+J$  行$(1\leq J\leq S)$，有 $3$ 个整数，依次为 $X_{i1},Y_{i1},Q_i$：表示第 $J$ 把钥匙存放在 $(X_{i1},Y_{i1})$单元里，并且第 $J$ 把钥匙是用来开启第 $Q_i$ 类门的。（其中$1\leq Q_i\leq P$）。

输入数据中同一行各相邻整数之间用一个空格分隔。

## 输出格式

将麦克营救到大兵瑞恩的最短时间的值输出。如果问题无解，则输出 $-1$。

## 样例

### 样例输入 #1
```
4 4 9
9
1 2 1 3 2
1 2 2 2 0
2 1 2 2 0
2 1 3 1 0
2 3 3 3 0
2 4 3 4 1
3 2 3 3 0
3 3 4 3 0
4 3 4 4 0
2
2 1 2
4 2 1
```
### 样例输出 #1
```
14
```
## 提示

$|X_{i1}-X_{i2}|+|Y_{i1}-Y_{i2}|=1,0\leq G_i\leq P$

$1\leq Q_i\leq P$


$N,M,P\leq10, K<150,S\leq 14$



---

---
title: "[AHOI2014/JSOI2014] 骑士游戏"
layout: "post"
diff: 提高+/省选-
pid: P4042
tag: ['图论', '2014', '各省省选', '江苏', '安徽', '最短路']
---
# [AHOI2014/JSOI2014] 骑士游戏
## 题目背景

长期的宅男生活中，JYY 又挖掘出了一款 RPG 游戏。在这个游戏中 JYY 会扮演一个英勇的骑士，用他手中的长剑去杀死入侵村庄的怪兽。
## 题目描述

在这个游戏中，JYY 一共有两种攻击方式，一种是普通攻击，一种是法术攻击。两种攻击方式都会消耗 JYY 一些体力。采用普通攻击进攻怪兽并不能把怪兽彻底杀死，怪兽的尸体可以变出其他一些新的怪兽，注意一个怪兽可能经过若干次普通攻击后变回一个或更多同样的怪兽；而采用法术攻击则可以彻底将一个怪兽杀死。当然了，一般来说，相比普通攻击，法术攻击会消耗更多的体力值（但由于游戏系统 bug，并不保证这一点）。

游戏世界中一共有 $N$ 种不同的怪兽，分别由 $1$ 到 $N$ 编号，现在 $1$ 号怪兽入侵村庄了，JYY 想知道，最少花费多少体力值才能将所有村庄中的怪兽全部杀死呢？
## 输入格式

第一行包含一个整数 $N$。

接下来 $N$ 行，每行描述一个怪兽的信息；

其中第 $i$ 行包含若干个整数，前三个整数为 $S_i$，$K_i$ 和 $R_i$，表示对于 $i$ 号怪兽，普通攻击需要消耗 $S_i$ 的体力，法术攻击需要消耗 $K_i$ 的体力，同时 $i$ 号怪兽死亡后会产生 $R_i$ 个新的怪兽。表示一个新出现的怪兽编号。同一编号的怪兽可以出现多个。
## 输出格式

输出一行一个整数，表示最少需要的体力值。

## 样例

### 样例输入 #1
```
4
4 27 3 2 3 2
3 5 1 2
1 13 2 4 2
5 6 1 2
```
### 样例输出 #1
```
26
```
## 提示

首先用消耗 $4$ 点体力用普通攻击，然后出现的怪兽编号是 $2$，$2$ 和 $3$。花费 $10$ 点体力用法术攻击杀死两个编号为 $2$ 的怪兽。剩下 $3$ 号怪兽花费 $1$ 点体力进行普通攻击。此时村庄里的怪兽编号是 $2$ 和 $4$。最后花费 $11$ 点体力用法术攻击将这两只怪兽彻底杀死。一共花费的体力是 $4+5+5+1+5+6=26$。

对于所有数据 $2 \le N \le 2 \times 10^5$，$1 \le R_i,\sum R_i \le 10^6$，$1 \le K_i,S_i \le 5 \times 10^{14}$。



---

---
title: "[JSOI2010] 满汉全席"
layout: "post"
diff: 提高+/省选-
pid: P4171
tag: ['2010', '各省省选', '江苏', '图论建模', '2-SAT']
---
# [JSOI2010] 满汉全席
## 题目描述

满汉全席是中国最丰盛的宴客菜肴，有许多种不同的材料透过满族或是汉族的料理方式，呈现在数量繁多的菜色之中。由于菜色众多而繁杂，只有极少数博学多闻技艺高超的厨师能够做出满汉全席，而能够烹饪出经过专家认证的满汉全席，也是中国厨师最大的荣誉之一。世界满汉全席协会是由能够料理满汉全席的专家厨师们所组成，而他们之间还细分为许多不同等级的厨师。

为了招收新进的厨师进入世界满汉全席协会，将于近日举办满汉全席大赛，协会派遣许多会员当作评审员，为的就是要在参赛的厨师之中，找到满汉界的明日之星。

大会的规则如下：每位参赛的选手可以得到 $n$ 种材料，选手可以自由选择用满式或是汉式料理将材料当成菜肴。

大会的评审制度是：共有 $m$ 位评审员分别把关。每一位评审员对于满汉全席有各自独特的见解，但基本见解是，要有两样菜色作为满汉全席的标志。如某评审认为，如果没有汉式东坡肉跟满式的涮羊肉锅，就不能算是满汉全席。但避免过于有主见的审核，大会规定一个评审员除非是在认为必备的两样菜色都没有做出来的状况下，才能淘汰一位选手，否则不能淘汰一位选手。

换句话说，只要参赛者能在这两种材料的做法中，其中一个符合评审的喜好即可通过该评审的审查。如材料有猪肉，羊肉和牛肉时，有四位评审员的喜好如下表： 

```
评审一 评审二 评审三 评审四 
满式牛肉 满式猪肉 汉式牛肉 汉式牛肉 
汉式猪肉 满式羊肉 汉式猪肉 满式羊肉 
```

如参赛者甲做出满式猪肉，满式羊肉和满式牛肉料理，他将无法满足评审三的要求，无法通过评审。而参赛者乙做出汉式猪肉，满式羊肉和满式牛肉料理，就可以满足所有评审的要求。

但大会后来发现，在这样的制度下如果材料选择跟派出的评审员没有特别安排好的话，所有的参赛者最多只能通过部分评审员的审查而不是全部，所以可能会发生没有人通过考核的情形。

如有四个评审员喜好如下表时，则不论参赛者采取什么样的做法，都不可能通过所有评审的考核： 

```
评审一 评审二 评审三 评审四 
满式羊肉 满式猪肉 汉式羊肉 汉式羊肉 
汉式猪肉 满式羊肉 汉式猪肉 满式猪肉 
```

所以大会希望有人能写一个程序来判断，所选出的 $m$ 位评审，会不会发生没有人能通过考核的窘境，以便协会组织合适的评审团。
## 输入格式

第一行包含一个数字 $K$（$1\le K \le 50$），代表测试文件包含了 $K$ 组数据。

每一组测试数据的第一行包含两个数字 $n$ 跟 $m$（$n≤100$，$m≤1000$），代表有 $n$ 种材料，$m$ 位评审员。

为方便起见，舍弃做法的中文名称而给予编号，编号分别从 $1$ 到 $n$。

接下来的 $m$ 行，每行都代表对应的评审员所拥有的两个喜好，每个喜好由一个英文字母跟一个数字代表，如 $m1$ 代表这个评审喜欢第 $1$ 个材料透过满式料理做出来的菜，而 $h2$ 代表这个评审员喜欢第 $2$ 个材料透过汉式料理做出来的菜。
## 输出格式

每组测试数据输出一行，如果不会发生没有人能通过考核的窘境，输出 ```GOOD```；否则输出 ```BAD```（均为大写字母）。
## 样例

### 样例输入 #1
```
2
3 4
m3 h1
m1 m2
h1 h3
h3 m2
2 4
h1 m2
m2 m1
h1 h2
m1 h2
```
### 样例输出 #1
```
GOOD
BAD
```


---

---
title: "河城荷取的烟花"
layout: "post"
diff: 提高+/省选-
pid: P4277
tag: ['搜索', '图论', '枚举', '最短路']
---
# 河城荷取的烟花
## 题目背景

#宴会已经接近尾声
![](https://cdn.luogu.com.cn/upload/pic/15119.png)
## 题目描述

快乐的时光总是这么短暂，这场宴会终究将要闭幕。

为了给大家留下一个深刻而美好的印象，萃香拜托掌握着顶尖科技的河城荷取用她刚刚研制出的装置来点燃烟花。

这个装置由3部分构成——一些长度为1的绳子，一些长度为$\sqrt{ 2 }$的绳子，还有一块不能燃烧的木板。河城荷取将木板划分成长度为 1 的单元格，并标上坐标，之后将这些绳子摆在木板上连接成一个连通图(即绳子上的任意两点均可互相到达)。注意，这些绳子的两端必须放在单元格的顶点上，即长度为 1 的绳子只能放在单元格的某一边上，长度为$\sqrt{ 2 }$的绳子只能放在单元格的某一对角线上。

现在，河城荷取会在木板上任意一根绳子的端点处点火(不能从绳子的中间处点火)，点火后，火会沿着绳子向前燃烧（每根绳子都有自己的燃烧速度），并能点燃与它相接的其它绳子。

比如说下面这张图，河城荷取不能在 A 点点火，但在 C 点或 B点点火都是充许的。

![](https://cdn.luogu.com.cn/upload/pic/15120.png)

为了演出效果，河城荷取必须保证所有绳子都燃烧完的总时间最短，可是由于绳子的条数过多，所以河城荷取找到了你来帮忙，让你帮她求出最短的总时间是多少。

如果你能完成这个任务，你就会获得两个奖励——100分和观赏一场盛大的烟花盛宴！

## 输入格式

第一行为一个正整数n，表示绳子的条数

接下来n行每行 5 个数： X1 Y1 X2 Y2 T,其中（X1, Y1）和（X2, Y2）分别表示绳子两端的坐标，T表示这根绳子的燃烧时间，是指从绳子的某一端点火燃烧到另一端，燃完所需的时间。


## 输出格式

第一行一个实数t，保留 4 位小数，表示所有绳子完全燃烧的最少时间。
## 样例

### 样例输入 #1
```
1
0 0 1 1 1
```
### 样例输出 #1
```
1.0000
```
### 样例输入 #2
```
5
0 0 0 1 1
1 0 0 1 10
0 0 1 0 1
0 0 1 1 1
2 2 1 1 1
```
### 样例输出 #2
```
3.2500
```
## 提示

【样例一解释】:从任一端点火都行，燃烧时间都是 1

【样例二解释】:

在 (0,0)位置点火，绳子 1, 3 和 4 将被点燃，燃烧 0.5 分钟后，绳子 2 将被从中间点燃向两端燃烧，再过 0.5 分钟，绳子 1, 3, 4 将被完全燃烧，绳子5将被点燃并在 1分钟后燃烧完 (比绳子 2 早燃完)。

绳子 2 从中间向两端燃烧 0.5 分钟以后，变成两小段，每段的燃烧时间是 4.5
分钟。但因为此时两小段绳子的另一端也同时被点燃，燃烧速度变成原来的
两倍，还需 2.25 分钟的燃烧时间， 所以总时间： 1 + 2.25 = 3.25

【数据范围】:

![](https://cdn.luogu.com.cn/upload/pic/15213.png)


---

---
title: "[JSOI2010] 连通数"
layout: "post"
diff: 提高+/省选-
pid: P4306
tag: ['2010', '各省省选', '江苏', '枚举', '图论建模', '连通块', '强连通分量']
---
# [JSOI2010] 连通数
## 题目背景

本题数据过水，可前往 https://www.luogu.com.cn/problem/U143178 提交

$\text{upd 2022.8.4}$：已作为 Hack 数据合并进来。
## 题目描述

度量一个有向图连通情况的一个指标是连通数，指图中可达顶点对个的个数。

如图

![](https://cdn.luogu.com.cn/upload/image_hosting/8jviim6w.png)

顶点 $1$ 可达 $1, 2, 3, 4, 5$

顶点 $2$ 可达 $2, 3, 4, 5$

顶点 $3$ 可达 $3, 4, 5$

顶点 $4, 5$ 都只能到达自身。

所以这张图的连通数为 $14$。

给定一张图，请你求出它的连通数
## 输入格式

输入数据第一行是图顶点的数量，一个正整数 $N$。  
接下来 $N$ 行，每行 $N$ 个字符。第 $i$ 行第 $j$ 列的 `1` 表示顶点 $i$ 到 $j$ 有边，`0` 则表示无边。
## 输出格式

输出一行一个整数，表示该图的连通数。
## 样例

### 样例输入 #1
```
3
010
001
100
```
### 样例输出 #1
```
9
```
## 提示

对于 $100 \%$ 的数据，$1 \le N \le 2000$。


---

---
title: "[Code+#4] 最短路"
layout: "post"
diff: 提高+/省选-
pid: P4366
tag: ['图论建模', '最短路', '进制', 'Code+']
---
# [Code+#4] 最短路
## 题目背景

在北纬 91° ，有一个神奇的国度，叫做企鹅国。这里的企鹅也有自己发达的文明，称为企鹅文明。因为企鹅只有黑白两种颜色，所以他们的数学也是以二进制为基础发展的。

比如早在 $11101001$ 年前，他们就有了异或这样一个数学概念。如果你不知道异或是什么，请出门过墙左转到[这里](https://zh.wikipedia.org/wiki/%E9%80%BB%E8%BE%91%E5%BC%82%E6%88%96)。

再比如早在 $1000010$ 年前，他们的大科学家 Penguin. Tu 就提出了[图](https://zh.wikipedia.org/wiki/%E5%9B%BE_%28%E6%95%B0%E5%AD%A6%29#%E6%9C%89/%E7%84%A1_%E5%90%91%E5%9B%BE)和[最短路径](https://zh.wikipedia.org/wiki/%E6%9C%80%E7%9F%AD%E8%B7%AF%E9%97%AE%E9%A2%98)这样一些概念。
## 题目描述

企鹅国中有 $N$ 座城市，编号从 $1$ 到 $N$ 。

对于任意的两座城市 $i$ 和 $j$ ，企鹅们可以花费 $(i~\mathrm{xor}~j) \times C$ 的时间从城市 $i$ 走到城市 $j$ ，这里 $C$ 为一个给定的常数。

当然除此之外还有 $M$ 条单向的快捷通道，第 $i$ 条快捷通道从第 $F_i$​​ 个城市通向第 $T_i$​​ 个城市，走这条通道需要消耗 $V_i$​​ 的时间。

现在来自 **P**enguin **K**ingdom **U**niversity 的企鹅豆豆正在考虑从城市 $A$ 前往城市 $B$ 最少需要多少时间？
## 输入格式

从标准输入读入数据。

输入第一行包含三个整数 $N,M,C$ ，表示企鹅国城市的个数、快捷通道的个数以及题面中提到的给定的常数$C$。

接下来的 $M$ 行，每行三个正整数 $F_i,T_i,V_i$​ ($1 \leq F_i \leq N$,$1 \leq T_i \leq N ,1\leq V_i \leq 100$)，分别表示对应通道的起点城市标号、终点城市标号和通过这条通道需要消耗的时间。

最后一行两个正整数 $A,B$ $(1 \leq C \leq 100)$，表示企鹅豆豆选择的起点城市标号和终点城市标号。

## 输出格式

输出到标准输出。

输出一行一个整数，表示从城市 $A$ 前往城市 $B$ 需要的最少时间。

## 样例

### 样例输入 #1
```
4 2 1
1 3 1
2 4 4
1 4
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
7 2 10
1 3 1
2 4 4
3 6
```
### 样例输出 #2
```
34
```
## 提示

**样例1解释**

直接从 $1$ 走到 $4$ 就好了。

**样例2解释**

先从 $3$ 走到 $2$ ，再从 $2$ 通过通道到达 $4$ ，再从 $4$ 走到 $6$。

![0](https://cdn.luogu.com.cn/upload/pic/16868.png)

活泼可爱的出题人给大家留下了下面这张图。

![1](https://i.loli.net/2018/04/02/5ac1bb2333c22.jpg)

Credit: https://www.luogu.org/discuss/show/38908


---

---
title: "[USACO18OPEN] Milking Order G"
layout: "post"
diff: 提高+/省选-
pid: P4376
tag: ['2018', '二分', 'USACO', '图论建模', '拓扑排序']
---
# [USACO18OPEN] Milking Order G
## 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 10^5$），编号为 $1 \ldots N$，最近闲得发慌。因此，她们发展了一个与 Farmer John 每天早上为她们挤牛奶时的排队顺序相关的复杂社会阶层。

经过若干周的研究，Farmer John 对他的奶牛的社会结构总计进行了 $M$ 次观察（$1 \leq M \leq 50,000$）。每个观察结果都是某些奶牛的一个有序序列，表示这些奶牛应该按照序列中的顺序进行挤奶。例如，如果 Farmer John 的一次观察结果是序列 $2$、$5$、$1$，那么 Farmer John 应该在给奶牛 $5$ 挤奶之前的某个时刻给奶牛 $2$ 挤奶，并在给奶牛 $1$ 挤奶之前的某个时刻给奶牛 $5$ 挤奶。

Farmer John 的观察结果是按优先级排列的，因此他的目标是最大化 $X$ 的值，使得他的挤奶顺序能够符合前 $X$ 个观察结果描述的状态。当多种挤奶顺序都能符合前 $X$ 个状态时，Farmer John 遵循一个长期以来的传统——编号较小的奶牛的地位高于编号较大的奶牛，因此他会最先给编号最小的奶牛挤奶。更正式地说，如果有多个挤奶顺序符合这些状态，Farmer John 会采用字典序最小的那一个。挤奶顺序 $x$ 的字典序比挤奶顺序 $y$ 小，如果对于某个 $j$，$x_i = y_i$ 对所有 $i < j$ 成立，并且 $x_j < y_j$（即这两个挤奶顺序到某个位置之前完全相同，而在该位置上 $x$ 比 $y$ 小）。

请帮助 Farmer John 确定给奶牛挤奶的最佳顺序。
## 输入格式

第一行包含 $N$ 和 $M$。接下来的 $M$ 行，每行描述了一个观察结果。第 $i+1$ 行描述了观察结果 $i$，第一个数是观察结果中的奶牛数量 $m_i$，后面是一列 $m_i$ 个整数，给出这次观察中奶牛的顺序。所有 $m_i$ 的总和至多为 $200,000$。
## 输出格式

输出 $N$ 个空格分隔的整数，表示一个 $1 \ldots N$ 的排列，为 Farmer John 给他的奶牛们挤奶应该采用的顺序。
## 样例

### 样例输入 #1
```
4 3
3 1 2 3
2 4 2
3 3 4 1
```
### 样例输出 #1
```
1 4 2 3

```
## 提示

在这个例子中，Farmer John 有四头奶牛，他的挤奶顺序应该满足以下规则：奶牛 $1$ 在奶牛 $2$ 之前、奶牛 $2$ 在奶牛 $3$ 之前（第一个观察结果），奶牛 $4$ 在奶牛 $2$ 之前（第二个观察结果），奶牛 $3$ 在奶牛 $4$ 之前、奶牛 $4$ 在奶牛 $1$ 之前（第三个观察结果）。前两个观察结果可以同时被满足，但 Farmer John 不能同时满足所有规则，因为这会要求奶牛 $1$ 在奶牛 $3$ 之前，同时奶牛 $3$ 在奶牛 $1$ 之前。

这意味着总共有两种可能的挤奶顺序：$1\ 4\ 2\ 3$ 和 $4\ 1\ 2\ 3$，第一种是字典序较小的。

题目来源：Jay Leeds


---

---
title: "[FJOI2018] 所罗门王的宝藏"
layout: "post"
diff: 提高+/省选-
pid: P4578
tag: ['图论', '2018', '各省省选', '福建', '枚举']
---
# [FJOI2018] 所罗门王的宝藏
## 题目描述

据古代传说记载，所罗门王既是智慧的代表，又是财富的象征。他建立了强大而富有的国家，聚集了大批的黄金象牙和钻石，并把这些价值连城的珍宝藏在一个神秘的地方，这就是世人瞩目的“所罗门王的宝藏”。多少个世纪以来，人们一直在寻找这批早已失落的古代文明宝藏，寻找盛产黄金和钻石的宝地。曾经追寻所罗门王宝藏的冒险者们都一去不回，至今没人解开这个谜题。亨利男爵在一次幸运的旅途中意外地得到了三百年前一位葡萄牙贵族留下的写在羊皮卷上的所罗门王的藏宝图和一本寻宝秘籍。在这张藏宝图的诱惑下，亨利男爵邀请约翰上校和勇敢的猎象人夸特曼开始了寻找埋葬在黑暗地底的所罗门王宝藏的艰险历程。他们横穿渺无边际的沙漠和浓荫蔽日的原始森林，越过汹涌澎湃的激流险滩，翻越高耸入云的峻岭雪山，饱尝沙漠的酷热和冰雪严寒，在藏宝图的指引下来到非洲一个原始的神秘国度库库安纳。这里有残酷的人殉制度，有一个拥有一千个妻室的独眼暴君特瓦拉，有像兀鹫一般丑恶诡诈老而不死的女巫加古尔，还有美丽聪慧的绝代佳人弗拉塔。在这片陌生而又险象环生的土地上三位寻宝英雄历尽艰辛，终于在绝代佳人弗拉塔的帮助下在海底深处找到了珍藏这批价值连城宝藏的巨大的藏宝洞。然而在女巫加古尔的精心策划下，一场灭顶之灾正在悄悄逼近。

藏宝洞的洞门十分坚固且洞门紧闭，如果不知道开启洞门的秘密是无法打开藏宝洞的洞门。在藏宝洞的洞门一侧有一个奇怪的矩形密码阵列。根据寻宝秘籍的记载，在密码阵列每行的左侧和每列的顶端都有一颗红宝石按钮。每个按钮都可以向左或向右转动。每向左转动一次按钮，相应的行或列中数字都增 $1$。每向右转动一次按钮，相应的行或列中数字都减 $1$。在矩形密码阵列的若干特定位置镶嵌着绿宝石。只有当所有绿宝石位置的数字与藏宝图记载的密码完全相同，紧闭的洞门就会自动缓缓打开。女巫加古尔早已得知开门的秘密。为了阻止寻宝者打开洞门，女巫加古尔为开门的密码阵列设置了全 $0$ 的初始状态。试图打开洞门的寻宝者如果不能迅速转动按钮使所有绿宝石位置的数字与藏宝图记载的密码完全相同，就会自动启动藏宝洞玄妙的暗器机关，使寻宝者遭到灭顶攻击而死于非命。

您能帮助三位寻宝英雄顺利打开藏宝洞的洞门吗？

编程任务：对于给定的密码阵列，找到获得正确密码的红宝石按钮的转动序列。

## 输入格式

输入的第一行中有一个正整数 $T (T \le 5)$ 表示有 $T$ 组数据。每组数据的第一行有 $3$ 个正整数 $n,m$ 和 $k$，表示洞门密码阵列共有 $n$ 行和 $m$ 列，$0<n,m,k \le 1000$。各行从上到下依次编号为 $1,2,\ldots,n$；各列从左到右依次编号为 $1,2,\ldots,m$ 。接下来的 $k$ 行中每行有三个整数 $x,y,c$，分别表示第 $k$ 个绿宝石在密码阵列中的位置和密码，$x$ 为行号 $y$ 为列号，$c$ 为该位置处的密码。
## 输出格式

对于每组数据，用一行输出 ``Yes`` 或者 ``No``。输出 ``Yes`` 表示存在获得正确密码的红宝石按钮的转动序列。输出 ``No`` 则表示无法找到获得正确密码的红宝石按钮的转动序列。
## 样例

### 样例输入 #1
```
2
2 2 4
1 1 0
1 2 0
2 1 2
2 2 2
2 2 4
1 1 0
1 2 0
2 1 2
2 2 1
```
### 样例输出 #1
```
Yes
No
```
## 提示

对于 $100\%$ 的数据，$1 \le n, m, k \le 1000$，$k \le n \times m$，$|c| \le 1,000,000$。


---

---
title: "[BalticOI 2015] Network"
layout: "post"
diff: 提高+/省选-
pid: P4665
tag: ['图论', '贪心', '2015', 'Special Judge', '构造', 'BalticOI（波罗的海）']
---
# [BalticOI 2015] Network
## 题目描述

The government of Byteland has decided that it is time to connect their little country to the Internet, so that all citizens can participate in programming competitions and watch videos of cute cats. When it was time to build the network backbone of the country, they assigned the company Internet Optimists Inc. with connecting all the $N$ computers of Byteland. The connections were made as direct links between pairs of computers in such a way that any pair of computers are connected by a sequence of links.

Byteland is not a rich country by any means, so to minimize costs the network topology was built in the form of a tree (i.e. there are exactly $N-1$ direct links between computers). Far too late, it was realised that this solution suffers from a serious drawback. If just a single link is broken, the computers of Byteland will be partitioned so that some computers cannot communicate with each other! To improve the reliability of Byteland's network, it was decided that it should at least tolerate if a single link is broken. Your task is to help Internet Optimists Inc. to improve the network in a cheapest way. Given the network topology of Byteland (i.e. which $N-1$ pairs of computers are connected by direct links), find the minimum number of links that need to be added so that the network will still be connected if any single link is broken.
## 输入格式

The first line of input contains a positive integer $N$ ( $N \geq 3$ ) , the number of computers in Byteland. For simplicity, all computers are numbered from $1$ to $N$. Each of the following $N-1$ lines contains a pair of integers $a$ and $b$ ( $1\leq a,b \leq n,a \ne b$ ) that describes a direct link between computers $a$ and $b$.
## 输出格式

In the first line of output your program should write an integer $k$, the minimal number of links that should be added to the network. In each of the following $k$ lines your program should write a pair of integers $a$ and $b$ ( $1\leq a,b \leq n,a \ne b$ ) that denote the numbers of computers that should be connected by a link. The links can be written in any order. If there is more than one solution, your program should output any one of them.
## 样例

### 样例输入 #1
```
6
1 2
2 3
2 4
5 4
6 4
```
### 样例输出 #1
```
2
1 5
3 6
```
## 提示

$3 \le N \le 500000$
## 题目翻译

### 题目描述### 
拜特朗政府已经决定，现在是时候将他们的小国家与互联网连接起来，以便所有公民都能参加节目比赛，观看可爱猫的视频。当是时候建设这个国家的网络骨干时，他们给互联网乐观主义者公司分配了连接所有N个拜特兰德的电脑。这些连接是作为计算机对之间的直接连接，使任何一对计算机都通过一系列的链接连接起来。

拜特朗是一个发展中国家，因此，为了将成本降到最低，网络拓扑是以树的形式构建的(即有N−1个计算机之间的直接连接)。为时已晚，人们意识到这一解决方案存在严重缺陷。如果只有一个链接断了，那么拜特兰德的计算机就会被分割，这样一些计算机就不能互相通信了！为了提高拜特朗网络的可靠性，人们决定至少要容忍单个链路中断。你的任务是帮助互联网乐观主义者公司以最便宜的方式改进网络。给出了拜特朗的网络拓扑(即N−1个计算机对是通过直接链接连接的)，找到需要添加的最少数量的链接，以便如果任何单个链接中断，网络仍将被连接。

### 输入输出格式
#### 输入格式：
输入的第一行包含一个正整数N(N≥3)，表示拜特兰德的计算机数量。为了简单起见，所有的计算机都是从1到N。以下N−1行包含一对整数。a和b(1≤a, b≤n, a≠b)，它描述计算机之间的直接链接a和b.
#### 输出格式：
在输出的第一行只有一个整数k，表示应该添加到网络中的最少链接数量。在下列每一项中都有对整数。a和b(1≤a ,b≤n ,a≠b)表示应该通过链接连接的计算机数量。链接可以按任何顺序写入。如果有一个以上的解决方案，您的程序应该输出其中的任何一个。

感谢@找寻 提供翻译


---

---
title: "[Wind Festival] Running In The Sky"
layout: "post"
diff: 提高+/省选-
pid: P4742
tag: ['图论建模', '拓扑排序', '强连通分量']
---
# [Wind Festival] Running In The Sky
## 题目背景

$[Night - 20:02$ $P.M.]$

夜空真美啊……但是……快要结束了呢……
## 题目描述

一天的活动过后，所有学生都停下来欣赏夜空下点亮的风筝。$Curtis$ $Nishikino$想要以更近的视角感受一下，所以她跑到空中的风筝上去了(这对于一个妹子来说有点匪夷所思)! 每只风筝上的灯光都有一个亮度 $k_i$. 由于风的作用，一些风筝缠在了一起。但是这并不会破坏美妙的气氛，缠在一起的风筝会将灯光汇聚起来，形成更亮的光源！

$Curtis$ $Nishikino$已经知道了一些风筝间的关系，比如给出一对风筝$(a,b)$, 这意味着她可以从 $a$ 跑到 $b$ 上去，但是不能返回。

现在，请帮她找到一条路径(她可以到达一只风筝多次，但只在第一次到达时她会去感受上面的灯光), 使得她可以感受到最多的光亮。同时请告诉她这条路径上单只风筝的最大亮度，如果有多条符合条件的路径，输出能产生最大单只风筝亮度的答案。
## 输入格式

第一行两个整数 $n$ 和 $m$. $n$ 是风筝的数量, $m$ 是风筝间关系对的数量. 

接下来一行 $n$ 个整数 $k_i$.

接下来 $m$ 行, 每行两个整数 $a$ 和 $b$, 即$Curtis$可以从 $a$ 跑到 $b$.
## 输出格式

一行两个整数。$Curtis$在计算出的路径上感受到的亮度和，这条路径上的单只风筝最大亮度.
## 样例

### 样例输入 #1
```
5 5
8 9 11 6 7
1 2
2 3
2 4
4 5
5 2
```
### 样例输出 #1
```
41 11
```
## 提示

对于 $20\%$ 的数据, $0<n \le 5\times10^3, \ 0 < m \le 10^4$.

对于 $80\%$ 的数据, $0 < n \le 10^5, \ 0 < m \le 3\times10^5$.

对于 $100\%$ 的数据, $0<n\le2\times10^5,\ 0<m\le5\times10^5,\ 0<k\le200$.



---

---
title: "【模板】2-SAT"
layout: "post"
diff: 提高+/省选-
pid: P4782
tag: ['图论', 'Special Judge', 'O2优化', '2-SAT', '强连通分量']
---
# 【模板】2-SAT
## 题目描述

有 $n$ 个布尔变量 $x_1\sim x_n$，另有 $m$ 个需要满足的条件，每个条件的形式都是 「$x_i$ 为 `true` / `false` 或 $x_j$ 为 `true` / `false`」。比如 「$x_1$ 为真或 $x_3$ 为假」、「$x_7$ 为假或 $x_2$ 为假」。

2-SAT 问题的目标是给每个变量赋值使得所有条件得到满足。
## 输入格式

第一行两个整数 $n$ 和 $m$，意义如题面所述。

接下来 $m$ 行每行 $4$ 个整数 $i$, $a$, $j$, $b$，表示 「$x_i$ 为 $a$ 或 $x_j$ 为 $b$」($a, b\in \{0,1\}$)
## 输出格式

如无解，输出 `IMPOSSIBLE`；否则输出 `POSSIBLE`。

下一行 $n$ 个整数 $x_1\sim x_n$（$x_i\in\{0,1\}$），表示构造出的解。
## 样例

### 样例输入 #1
```
3 1
1 1 3 0
```
### 样例输出 #1
```
POSSIBLE
0 0 0
```
## 提示

$1\leq n, m\leq 10^6$ , 前 $3$ 个点卡小错误，后面 $5$ 个点卡效率。

由于数据随机生成，可能会含有（ 10 0 10 0）之类的坑，但按照最常规写法的写的标程没有出错，各个数据点卡什么的提示在标程里。


---

---
title: "[BJWC2012] 冻结"
layout: "post"
diff: 提高+/省选-
pid: P4822
tag: ['2012', '北京', '图论建模', '最短路']
---
# [BJWC2012] 冻结
## 题目背景

“我要成为魔法少女！”

“那么，以灵魂为代价，你希望得到什么？”

“我要将有关魔法和奇迹的一切，封印于卡片之中„„”

在这个愿望被实现以后的世界里，人们享受着魔法卡片（SpellCard，又名符卡）带来的便捷。

现在，不需要立下契约也可以使用魔法了！你还不来试一试？

比如，我们在魔法百科全书（Encyclopedia of Spells）里用“freeze”作为关键字来查询，会有很多有趣的结果。

例如，我们熟知的 Cirno，她的冰冻魔法当然会有对应的 SpellCard 了。当然，更加令人惊讶的是，居然有冻结时间的魔法，Cirno 的冻青蛙比起这些来真是小巫见大巫了。

这说明之前的世界中有很多魔法少女曾许下控制时间的愿望，比如 Akemi Homura、Sakuya Izayoi、……

当然，在本题中我们并不是要来研究历史的，而是研究魔法的应用。
## 题目描述

我们考虑最简单的旅行问题吧： 现在这个大陆上有 $N$ 个城市，$M$ 条双向的道路。城市编号为 $1$ ~ $N$，我们在 $1$ 号城市，需要到 $N$ 号城市，怎样才能最快地到达呢？

这不就是最短路问题吗？我们都知道可以用 Dijkstra、Bellman-Ford、Floyd-Warshall等算法来解决。

现在，我们一共有 $K$ 张可以使时间变慢 50%的 SpellCard，也就是说，在通过某条路径时，我们可以选择使用一张卡片，这样，我们通过这一条道路的时间 就可以减少到原先的一半。需要注意的是：

1. 在一条道路上最多只能使用一张 SpellCard。
2. 使用一张SpellCard 只在一条道路上起作用。
3. 你不必使用完所有的 SpellCard。

给定以上的信息，你的任务是：求出在可以使用这不超过 $K$ 张时间减速的 SpellCard 之情形下，从城市 $1$ 到城市 $N$ 最少需要多长时间。
## 输入格式

第一行包含三个整数：$N$、$M$、$K$。

接下来 $M$ 行，每行包含三个整数：$A_i$、$B_i$、$Time_i$，表示存在一条  $A_i$ 与 $B_i$ 之间的双向道路，在不使用 SpellCard 之前提下，通过它需要 $Time_i$ 的时间。
## 输出格式

输出一个整数，表示从 $1$ 号城市到 $N$ 号城市的最小用时。
## 样例

### 样例输入 #1
```
4 4 1 
1 2 4 
4 2 6 
1 3 8 
3 4 8 

```
### 样例输出 #1
```
7
```
## 提示

#### 样例 1 解释

在不使用 SpellCard 时，最短路为 $1 \to 2 \to 4$，总时间为 10。现在我们可以使用 1 次 SpellCard，那么我们将通过 $2 \to 4$ 这条道路的时间减半，此时总时间为7。

#### 数据规模与约定

对于 $100\%$ 的数据，保证：

- $1 \leq K \leq N \leq 50$，$M \leq 10^3$。
- $1 \leq A_i,B_i \leq N$，$2 \leq Time_i \leq 2 \times 10^3$。
- 为保证答案为整数，保证所有的 $Time_i$ 均为偶数。
- 所有数据中的无向图保证无自环、重边，且是连通的。


---

---
title: "帕秋莉的手环"
layout: "post"
diff: 提高+/省选-
pid: P4910
tag: ['数学', '图论', '递推', '矩阵加速', '斐波那契数列']
---
# 帕秋莉的手环
## 题目背景

帕秋莉是蕾米莉亚很早结识的朋友，现在住在红魔馆地下的大图书馆里。不仅擅长许多魔法，还每天都会开发出新的魔法。只是身体比较弱，因为哮喘，会在咏唱符卡时遇到麻烦。

她所用的属性魔法，主要是生命和觉醒的“木”，变化和活动的“火”，基础和不动的“土”，果实和丰收的“金”，寂静和净化的“水”，机动和攻击的“日”，被动和防御的“月”七种属性

没有窗户的图书馆或许充满了灰尘，不过她认为在书旁边才是自己，所以她不能从书的旁边离开。这样已经一百年了。
## 题目描述

经过数年魔法的沉淀，帕秋莉将她那浩瀚无边的魔法的一部分浓缩到了一些特质的珠子中。

由于帕秋莉爱好和平，她只把象征生命和觉醒的木属性魔法和果实和丰收的金属性魔法放入了珠子中。

她认为光要这些珠子没有什么用处，于是她想将这些珠子串成魔法手环，这样就好看多了。于是，她拿出来用来串这些珠子的线 - 雾雨灵径。

她将这些珠子串到一起之后发现了一些性质：一段雾雨灵径的颜色是由两边的珠子的属性决定的，当一段雾雨灵径连接的两个珠子中只要有一个是金属性的，那么这段雾雨灵径的颜色就为金色

帕秋莉想要一个全都是金色的手环，而且她还想知道一共有多少种方案。由于她还要研究新的魔法，她就把这件事交给了你。由于她的魔法浩瀚无边，她有无穷的珠子

她并不想看着好几十位的数字，于是你需要对 $1000000007$ 进行取模
## 输入格式

输入包含多组数据

第一行一个正整数 $T$ ，表示数据组数。

之后每组数据有一个 $n$ 代表木属性珠子和金属性珠子的总个数
## 输出格式

对于每组数据，输出取模后的方案数

## 样例

### 样例输入 #1
```
2
5
20
```
### 样例输出 #1
```
11
15127
```
### 样例输入 #2
```
3
9
99
999
```
### 样例输出 #2
```
76
281781445
445494875
```
### 样例输入 #3
```
5  
123
1234
12345
123456
1234567
```
### 样例输出 #3
```
528790589
200102666
537707871
262341000
534036342

```
## 提示

这里给出 $n = 5$ 时，样例的解释


使用 $1, 2, 3, 4, 5$ 来代表各个珠子

可行的方案是

$\{1, 3, 5\}, \{1, 2, 4\}, \{1, 3, 4\}, \{2, 3, 5\}, \{2, 4, 5\}$

$\{1, 2, 3, 4\}, \{1, 2, 3, 5\}, \{1, 2, 4, 5\}, \{1, 3, 4, 5\}, \{2, 3, 4, 5\}$

$\{1, 2, 3, 4, 5\}$



对于 $20\%$ 的数据，有 $1 \le n \le 10$ ；

对于 $40\%$ 的数据，有 $1 \le n \le 10^2$ ；

对于 $60\%$ 的数据，有 $1\le n \le 10^6$ ；

对于 $90\%$ 的数据，有 $1 \le n \le 10^9$ ；

对于全部的数据，有 $1\le T \le 10,  1\le n \le 10^{18}$


---

---
title: "【模板】树同构（[BJOI2015]树的同构）"
layout: "post"
diff: 提高+/省选-
pid: P5043
tag: ['图论', '2015', '各省省选', '北京', '哈希 hashing']
---
# 【模板】树同构（[BJOI2015]树的同构）
## 题目描述

树是一种很常见的数据结构。

我们把 $N$ 个点，$N-1$ 条边的连通无向图称为树。

若将某个点作为根，从根开始遍历，则其它的点都有一个前驱，这个树就成为有根树。

对于两个树 $T_1$ 和 $T_2$，如果能够把树 $T_1$ 的所有点重新标号，使得树 $T_1$ 和树 $T_2$ 完全相同，那么这两个树是同构的。也就是说，它们具有相同的形态。

现在，给你 $M$ 个无根树，请你把它们按同构关系分成若干个等价类。
## 输入格式

第一行，一个整数 $M$。

接下来 $M$ 行，每行包含若干个整数，表示一个树。第一个整数 $N$表示点数。接下来 $N$ 个整数，依次表示编号为 $1$ 到 $N$ 的每个点的父亲结点的编号。根节点父亲结点编号为 $0$。
## 输出格式

输出 $M$ 行，每行一个整数，表示与每个树同构的树的最小编号。
## 样例

### 样例输入 #1
```
4 
4 0 1 1 2 
4 2 0 2 3 
4 0 1 1 1 
4 0 1 2 3 
```
### 样例输出 #1
```
1 
1 
3 
1 
```
## 提示

编号为 $1, 2, 4$ 的树是同构的。编号为 $3$ 的树只与它自身同构。

对于 $100\%$ 的数据，$1\leq N,M\leq 50$。


---

---
title: "[MtOI2018] 刷题？作业狂魔！"
layout: "post"
diff: 提高+/省选-
pid: P5477
tag: ['图论', '2018', '洛谷原创', 'O2优化']
---
# [MtOI2018] 刷题？作业狂魔！
## 题目背景

在临听到暑假的尾声以后，神奇的 cz 终于发觉自己的作业不能完成了。

在他写完作业之前，你需要将他做作业的顺序告诉给他听，这样你们就可以一起玩了。  


## 题目描述

你拥有 $T$ 分钟的时间。

做作业的顺序可以根据重要度 $v_i$ 来排序，但可能这不是最佳方案。且每项作业可能不止有一项，所以每项作业还有一个数量 $c_i$，每项 $t_i$ 分钟可以完成。

而在做某作业之前可能要先写完某个作业，所以还给出 $M$ 个关系，每个关系包含两个数 $a$，$b$ ，代表 $a$ 是 $b$ 完成的前提，不存在 $a=b$ 的情况。

关系不排除环的情况，cz 不想重做一遍作业，只好不做在环上的作业。

当某作业做到一半但时间结束，则失去该作业重要度；当该作业只做了 $k$ 个，但 $k\leq c_i$ ,则得到 $k\times v_i$ 重要度 , 如果该作业没把 $c_i$ 个做完，则不得做其他作业。

可存在 $b$ 有多个 $a$，但请注意一个作业的 **一个** 前提被做了以后，该作业就可以被做了。但cz非常专注，他写完一个作业以后就必须写**以该作业为前提的**作业。
## 输入格式

输入共 $N+M+2$ 行

第 $1$ 行输入 $2$ 个正整数 $N,T$。

接下来共 $N$ 行输入，第 $i$ 行输入 $3$ 个正整数 $v_i,c_i,t_i$。

第 $N+2$ 行输入 $1$ 个正整数 $1$ 行。

接下来共 $M$ 行输入，意义同上。
## 输出格式

输出共 $1$ 行 $1$ 个数，表示价值（重要度）最大值。
## 样例

### 样例输入 #1
```
4 7
2 1 1
2 1 2
2 1 3
2 1 4
3
3 4
2 3
1 2
```
### 样例输出 #1
```
6
```
## 提示

### 子任务

对于 $100\%$ 的数据，$1<=N<=10000,1<=M<=100000$

其他值均在$long long$范围内。


### 题目来源

[MtOI2018 迷途の家の水题大赛](https://www.luogu.org/contest/11260) T1

出题人：Doubleen

56432


---

---
title: "【模板】Stoer-Wagner"
layout: "post"
diff: 提高+/省选-
pid: P5632
tag: ['图论', '最小割']
---
# 【模板】Stoer-Wagner
## 题目描述

定义无向图 $G$ 的最小割为：一个去掉后可以使 $G$ 变成两个连通分量，且边权和最小的边集的边权和。

给出一张无向图 $G$，求其最小割。
## 输入格式

第一行，两个数 $n,m$，表示点数与边数。

接下来 $m$ 行，每行三个正整数 $a_i,b_i,w_i$，表示 $a_i$ 到 $b_i$ 有一条边权为 $w_i$ 的边。
## 输出格式

一行，一个整数表示 $G$ 的最小割，如果图不联通，请输出 `0` 。
## 样例

### 样例输入 #1
```
4 6
1 2 5
1 3 1
2 4 1
3 4 2
2 3 1
1 4 2

```
### 样例输出 #1
```
4
```
## 提示

对于前 $20\%$ 的数据， $n\leq 10$。  
对于前 $40\%$ 的数据， $n\leq 100$。  
对于另外 $10\%$ 的数据，保证输入为一棵树。  
对于另外 $10\%$ 的数据，保证输入为一条链。  
对于 $100\%$ 的数据， $n\leq 600,m\leq \frac{n\times (n-1)}{2}$ ，保证 $\sum_{i=1}^{m}w_i \leq10^9$ 。

#### PS：想交 最大流/最小割树 的就省省吧。


---

---
title: "[CTSC1998] 罗杰游戏"
layout: "post"
diff: 提高+/省选-
pid: P5700
tag: ['动态规划 DP', '图论', '1998', '枚举', '最短路', 'CTSC/CTS']
---
# [CTSC1998] 罗杰游戏
## 题目背景

CTSC1998 D2T1

## 题目描述

罗杰游戏由一张棋盘和罗杰构成。棋盘由很多个小格组成，每个小格上刻有一个数字。其为 $-1$ 或 $0$ 至 $255$ 之间的一个数。罗杰是一个立方体，有六个面，每个面上分别有一个 $1$ 至 $6$ 之间的数字。

我们开始时把罗杰放在棋盘中的一个小格上，然后让其向前、后、左、右四个方向**翻滚**至邻近小格中。

游戏要求经过若干次翻滚后，让罗杰到达指定小格。

**罗杰不得进入标有 $-1$ 的小格，否则游戏结束**。

罗杰每进入一个小格后，将其顶面的数字同该小格的数字相乘，所得结果累加即得到罗杰的旅行费用。

开始时我们能看到罗杰的某些面上的数字，也可以指定当罗杰最终到达目的格时某些面上应出现的数字。对于**不确定的数字**，我们可以在**合法的基础上任意指定**。

**任务一**

罗杰只能向前或向右翻滚。

**任务二**

罗杰可以自由活动。
## 输入格式

输入文件的第一行是数字 $1$ 或 $2$ 。表示是任务一还是任务二。

文件的第二行是两个整数 $M$ 和 $N$ ，给出了棋盘的列数和行数。

接下来的 $N$ 行每行表示棋盘的一行，有 $M$ 个数，依次给出了该行上每列的数。

其后的两行分别给出了罗杰的出发点信息和到达点信息。

每行开始的两个正整数给出了该格子的列号和行号。

接下来的六个数字分别表示了罗杰的顶，底，前、后、左、右各面的数字。 $0$ 表示可以任意指定。


## 输出格式

输出文件的第一行给出罗杰的最小旅行费用。

如果罗杰不可能按要求到达目的地，则输出 $-1$ 。

否则其后每行给出罗杰的旅行情况：

从出发格到目的格，每行表示了罗杰的一个位置，

依次给出罗杰的当前旅行费用、所在格的列编号、行编号，以及罗杰6个面上的数字。

注意这时你的程序必须给出罗杰的完整信息，即各面上的数字不能为 $0$。
## 样例

### 样例输入 #1
```
2 
10 10
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1
1 1 1 9 8 7 6 5 4 1
1 1 9 8 7 6 5 4 1 1
1 1 8 7 6 5 4 1 1 1
1 1 7 6 5 4 1 1 1 1
1 1 6 5 4 1 1 1 1 1
1 1 5 4 1 1 1 1 1 1
1 1 4 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
3 3 0 0 0 0 0 0
8 8 0 0 0 0 0 0
```
### 样例输出 #1
```
44
0 3 3 6 5 3 1 2 4
3 3 2 3 1 5 6 2 4
5 4 2 2 4 5 6 1 3
6 5 2 1 3 5 6 4 2
10 6 2 4 2 5 6 3 1
13 7 2 3 1 5 6 2 4
15 8 2 2 4 5 6 1 3
16 9 2 1 3 5 6 4 2
20 10 2 4 2 5 6 3 1
26 10 3 6 5 4 2 3 1
28 10 4 2 4 6 5 3 1
29 9 4 1 3 6 5 2 4
34 9 5 5 6 1 3 2 4
38 8 5 4 2 1 3 5 6
41 8 6 3 1 4 2 5 6
43 8 7 2 4 3 1 5 6
44 8 8 1 3 2 4 5 6
```
## 提示

【数据范围】

$M \le 40$ , $N \le 40$  。


---

---
title: "[SHOI2002] 舞会"
layout: "post"
diff: 提高+/省选-
pid: P6268
tag: ['2002', '各省省选', '网络流', '上海', '图论建模', '二分图']
---
# [SHOI2002] 舞会
## 题目描述

某学校要召开一个舞会。已知学校所有 $n$ 名学生中，有些学生曾经互相跳过舞。当然跳过舞的学生一定是一个男生和一个女生。在这个舞会上，要求被邀请的学生中的任何一对男生和女生互相都不能跳过舞。求这个舞会最多能邀请多少个学生参加。
## 输入格式

输入的第一行是 $n$ 和 $m$ 。其中 $n$ 是可选的学生的总数， $m$ 是已知跳过舞的学生的对数 ( $n \leq 1000$ ， $m \leq 2000$ ）。

然后有 $m$ 行，每行包括两个非负整数，表示这两个编号的学生曾经跳过舞。学生的编号从 $0$ 号到 $n - 1$ 号。
## 输出格式

输出文件仅一行，为一个数字，即能够邀请的最多的学生数。
## 样例

### 样例输入 #1
```
8 6
0 2
2 3
3 5
1 4
1 6
3 1
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
20 5
5 2
4 3
18 17
0 11
13 3

```
### 样例输出 #2
```
16
```


---

---
title: "『MdOI R2』Odyssey"
layout: "post"
diff: 提高+/省选-
pid: P6381
tag: ['动态规划 DP', '数学', '图论', '拓扑排序', '素数判断,质数,筛法', '洛谷月赛']
---
# 『MdOI R2』Odyssey
## 题目背景

超越音速的极限，不及瑰丽多变的极光；

微弱的脉冲，开拓原本一片混沌的天地；

沉郁的蓝缓缓闪动，史诗的红迎接巅峰；

血色的夕阳尽头，是将夜的星辰；

夜半的满天星空，也会被来自地狱的硝烟掩盖；

炽红炼狱消逝，只金色遗迹永存。

在这里等待着每一位的，都是一段艰苦而璀璨的旅程。
## 题目描述

若正整数 $a$ 与 $b$ 满足：

- $a$ 与 $b$ 的积是一个正整数的 $k$ 次方，即存在正整数 $c$ 使得 $ab=c^k$。

那么我们称 $(a,b)$ 为一组**完美数对**。

---

有一个包含 $n$ 个结点和 $m$ 条边的**有向无环图**，这张图中的每条边都有权值和长度两个属性。

如果一条路径 $P$ 满足**以下条件之一**，则称其为一条**完美路径**：

- $P$ 中仅包含一条边。

- $P$ 从其起点开始依次为 $e_1, e_2, e_3, \ldots e_p$ 这 $p\ (p\ge 2)$ 条边，对于任意的 $1\leq i\leq p-1$，$e_i$ 的权值和 $e_{i+1}$ 的权值组成完美数对。

你需要求出图中最长完美路径的长度，一条路径的长度定义为这条路径上所有边的长度之和。
## 输入格式

第一行：三个整数 $n,m,k$，分别表示有向无环图的结点数、边数和完美数对的参数。

接下来 $m$ 行：每行四个整数 $u,v,w,l$，表示有一条权值为 $w$，长度为 $l$ 的有向边从 $u$ 连向 $v$。
## 输出格式

第一行：一个整数 $ans$，表示最长完美路径的长度。
## 样例

### 样例输入 #1
```
5 7 2
2 5 2 5
5 3 18 9
2 4 6 7
4 3 6 3
2 1 24 2
1 4 6 8
1 5 8 4
```
### 样例输出 #1
```
14
```
## 提示

【帮助与提示】  

为方便选手测试代码，本题额外提供两组附加样例供选手使用。  

[样例输入1](https://www.luogu.com.cn/paste/wx1lz6m2) [样例输出1](https://www.luogu.com.cn/paste/28xe7f0x)      

[样例输入2](https://www.luogu.com.cn/paste/efgwngs5) [样例输出2](https://www.luogu.com.cn/paste/5hcpoayt)   

----

【样例解释】

样例中给出的有向无环图如图所示，其中边上的红色数字为边的权值，黑色数字为边的长度：

![](https://cdn.luogu.com.cn/upload/image_hosting/w6x03ksd.png)

最长完美路径为 $2\to 5\to 3$，因为这两条边的权值 $2$ 和 $18$ 满足 $2\times 18=6^2$，是完美数对，此路径长度为 $5+9=14$。

此外，$2\to 1\to 4\to 3,\ \ 2\to 4\to 3,\ \ 1\to 5\to 3$ 等也是完美路径，但不是最长的。

图中，$2\to 1\to 5\to 3$ 长度为 $15$，是一条更长的路径，但它并不是完美路径，因为前两个边权 $24$ 和 $8$ 的乘积为 $192$，不是正整数的平方，即 $(24,8)$ 不是完美数对。

---

【数据范围】

**本题采用捆绑测试。**

对于 $100\%$ 的数据：$1\leq n\leq 10^5,\ \ 1\leq m\leq 2\times 10^5,\ \ 1\leq k\leq 10,\ \ 1\leq u,v\leq n,\ \ 1\leq w\leq 10^5,\ \ 1\leq l\leq 10^4$。

给出的图**不保证弱连通**，图中从一个点到另一个点**可能**存在多条边，但保证给出的图是有向无环图。

| 子任务编号 | $n\leq$ |     $m\leq$      | $w\leq$ | $k\leq$ |  特殊性质  | 分值 |
| :--------: | :-----: | :--------------: | :-----: | :-----: | :--------: | :--: |
| Subtask 1  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $1$   |     无     | $18$ |
| Subtask 2  |  $10$   |       $10$       |  $100$  |  $2$   |     无     | $12$ |
| Subtask 3  |  $600$  | $1.5\times 10^3$ | $10^3$  |   $2$   |     无     | $10$ |
| Subtask 4  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $2$   | $w$ 为素数 | $15$ |
| Subtask 5  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $2$   |     无     | $15$ |
| Subtask 6  |  $600$  | $1.5\times 10^3$ | $10^3$  |  $5$   |     无     | $10$ |
| Subtask 7  | $10^5$  |  $2\times 10^5$  | $10^5$  |  $10$   |     无     | $20$ |




---

---
title: "[YsOI2020] 幼儿园"
layout: "post"
diff: 提高+/省选-
pid: P6592
tag: ['图论', '二分', '可持久化线段树']
---
# [YsOI2020] 幼儿园
## 题目描述

Ysuperman 热爱在 TA 的幼儿园里散步，为了更方便散步， TA 把幼儿园抽象成 $n$ 个点，$m$ 条边的**有向图**。 散步得多了， TA 就给了每一条边**无与伦比**的亲密程度：$1,2,\cdots,m$，越大代表越亲密。 TA 也给了每一个点无与伦比的编号：$1,2,\cdots,n$，其中 $1$ 代表着幼儿园大门，但是每个**点是没有亲密程度的**。

接下来 $k$ 天，Ysuperman 每天会有一次散步计划。具体而言， TA 希望从 $x_i$ 号点出发，只经过**亲密程度属于区间 $[l_i,r_i]$ 的边**，走到幼儿园大门 $1$ 号点，期间经过的边的亲密程度必须**单调递减**，不然会因为 TA 有强迫症而不能回家。


Ysuperman 看着自己刚刚画的草稿脑子一团浆糊， TA 发现 TA 始终没有办法规划出这么多合理路线，现在 TA 想请你帮 TA 。具体而言，对于每一天的计划，如果可行，则输出 `1`，反之输出 `0`。

当然啦，有的时候 Ysuperman 很着急，需要你立马回复，有的时候 TA 可以等等你，先把所有问题问完再等你回复。
## 输入格式

第一行三个整数 $n,m,k,w$，分别表示节点个数、边个数、Ysuperman 的计划个数，和 Ysuperman 的焦急程度，此处的 $w$ 在后续输入中有用。

此后 $m$ 行的第 $i$ 行有两个整数 $u_i,v_i$，表示 Ysuperman 的幼儿园里有一条 $u_i$ 号点到 $v_i$ 号点的单向边，且**亲密程度为** $i$。

此后 $k$ 行的第 $i$ 行有三个整数 $x_i,l_i,r_i$，表示 Ysuperman 的第 $i$ 个计划。

此处如果 $w=0$，则 $x_i,l_i,r_i$ 为明文，可以直接使用。

如果 $w=1$，则 $x_i,l_i,r_i$ 为密文，你需要将它解密。解密操作是：令 $L$ 为之前所有询问的输出之和（没有询问过则为 $0$），你需要将 $x_i ,l_i,r_i$ 都异或 $L$。
## 输出格式

$k$ 行，每行只可能是 `1` 或 `0`，第 $i$ 行的数表示第 $i$ 个计划是否可行。
## 样例

### 样例输入 #1
```
5 7 5 0
3 2
1 2
4 3
5 4
3 1
5 3
5 1
3 1 4
1 2 2
5 5 6
4 5 7
2 1 7

```
### 样例输出 #1
```
0
1
1
0
0

```
### 样例输入 #2
```
5 12 10 0
4 2
4 2
5 3
3 3
1 5
1 4
4 4
2 4
5 3
1 5
2 2
4 1
4 3 5
4 2 3
1 4 5
3 1 8
3 1 4
3 5 5
2 1 12
4 10 12
2 5 5
1 1 3

```
### 样例输出 #2
```
0
0
1
0
0
0
0
1
0
1

```
### 样例输入 #3
```
5 12 10 1
4 2
4 2
5 3
3 3
1 5
1 4
4 4
2 4
5 3
1 5
2 2
4 1
4 3 5
4 2 3
1 4 5
2 0 9
2 0 5
2 4 4
3 0 13
5 11 13
0 7 7
3 3 1
```
### 样例输出 #3
```
0
0
1
0
0
0
0
1
0
1

```
## 提示

### 样例说明

#### 样例说明 $1$

![](https://cdn.luogu.com.cn/upload/image_hosting/wxji6w6f.png)

对于第 $2$ 条计划，Ysuperman 已经站在门口，所以计划可行。

对于第 $3$ 条计划，Ysuperman 只能通过路径 $5 \overset{6}{\rightarrow}3 \overset{5}{\rightarrow} 1$。（箭头上方数字表示的是边的亲密程度）。

其他计划都是不可行的。

#### 样例说明 $3$

样例三为加密后的样例二。

----

### 数据范围

**本题采用捆绑测试。**

| $\mathrm{subtask}$ |     $n$     |       $m$        |        $k$        |  特殊性质   | 分数  |
| :----------------: | :---------: | :--------------: | :---------------: | :---------: | :---: |
|        $1 $        |   $\le17$   |     $\le17$      | $\le 2\cdot 10^5$ |      /      | $ 5$  |
|        $2$         |  $\le500$   |     $\le500$     |     $\le500 $     |      /      | $17$  |
|        $3 $        | $\le 3000$  |   $\le 3000 $    |    $\le 3000 $    |      /      | $18 $ |
|       $ 4 $        |  $\le10^5$  | $\le2\cdot10^5$  |  $\le2\cdot10^5$  |   $v_i=1$   | $13$  |
|        $5 $        | $\le 10^5$  | $\le 2\cdot10^5$ |    $\le 10^5$     | $l_i=1,w=0$ | $ 7 $ |
|        $6$         | $\le10^5 $  | $\le2\cdot10^5$  |    $\le 10^5$     |   $w=0 $    | $13 $ |
|        $7$         | $ \le 10^5$ | $\le 2\cdot10^5$ | $\le 2\cdot10^5$  |      /      | $27$  |

对于 $100\%$ 的数据，满足 $1 \le n \le 10^5 ,1 \le m \le 2\cdot10^5 ,0 \le k \le 2\cdot10^5$。

$w\in\{0,1\},1 \le u_i,v_i \le n$。

$x_i,l_i,r_i$ 在解密后保证 $1\le x \le n ,1 \le l_i,r_i \le m $。

### 提示

**不保证不出现重边自环，不保证图联通**。


---

---
title: "[BalticOI 2015] File Paths"
layout: "post"
diff: 提高+/省选-
pid: P6843
tag: ['图论', '2015', '深度优先搜索 DFS', 'BalticOI（波罗的海）']
---
# [BalticOI 2015] File Paths
## 题目描述

一个文件 $\tt file$ 都需要在一个包含很多文件 $\tt dir1,dir2,\cdots,dirj$ 的目录中，这个文件的 absolute file path 为 $\tt/dir1/dir2/\cdots/dirj/file$，根目录用 $\tt /$ 表示，每一个放在根目录下的文件的 absolute file path 的形式为 $\tt /file$。

符号链接指向一个已被命名的目录，可以看作一个快捷方式，他可以放置在任意目录下，注意，符号链接不能指向文件。比如，我们在 $\tt /$ 下放一个指向 $\tt /$ 的符号链接 $\tt hello$，那么，$\tt /dir/file$，$\tt /hello/dir/file$，$\tt /hello/hello/dir/dile$ 都指向同一个文件 $\tt file$。另比如，我们在 $\tt /dir$ 下放一个指向 $\tt /$ 的符号链接 $\tt hi$，那么，$\tt /dir/file$，$\tt /dir/hi/dir/file$，$\tt /dir/hi/dir/hi/dir/file$ 都指向同一个文件 $\tt file$。符号链接指向上一层，下一层，甚至同层都可以，但是不允许 $\tt ./$，$\tt ../$，$\tt //$ 之类的操作。

现在想问，是否能通过引入一个长为 $s$ 的符号链接使得找到一个文件的 absolute file path 长度恰好为 $k$？
## 输入格式

第一行三个整数 $n,m,k$ 代表除根目录之外的目录数，文件数和要求等于的路径长度。        
第二行一个整数 $s$ 代表符号链接长。       
接下来 $n$ 行每行两个整数 $p_i,l_i$ 描述一个目录，这个目录编号为 $l_i$，父目录编号为 $p_i$。        
接下来 $m$ 行每行两个整数 $p_j,l_j$，描述一个文件，这个文件的长度为 $l_j$，父目录编号为 $p_j$。
## 输出格式

$m$ 行每行一个字符串代表是否能通过引入一个长为 $s$ 的符号链接使得找到编号为 $j$ 的文件的 absolute file path 长度恰好为 $k$，如果是的话输出 $\tt YES$，否则输出 $\tt NO$。
## 样例

### 样例输入 #1
```
2 4 22
2
0 1
1 5
2 13
2 10
1 4
0 7
```
### 样例输出 #1
```
YES
YES
YES
NO
```
## 提示

#### 样例 1 解释

假设符号链接名字为 $\tt LL$，目录名字为 $\tt a$，$\tt bbbbb$，文件名字为 $\tt ccccccccccccc$，$\tt dddddddddd$，$\tt eee$，$\tt fffffff$，根目录下包含目录 $\tt a$ 和文件 $\tt fffffff$，目录 $\tt a$ 下包含目录 $\tt bbbbb$ 和文件 $\tt eee$，目录 $\tt bbbbb$ 包含文件 $\tt ccccccccccccc$ 和 $\tt dddddddddd$。下面是形象化的表述：

```plain
/
|-- a
| |-- bbbbb
| | |-- ccccccccccccc
| | +-- dddddddddd
| +-- eeee
+-- fffffff
```

- 对于第 $1$ 个文件，满足条件的路径为 $\tt /a/bbbbb/ccccccccccccc$。
- 对于第 $2$ 个文件，满足条件的路径为 $\tt /a/LL/bbbbb/dddddddddd$。
- 对于第 $3$ 个文件，满足条件的路径为 $\tt /a/LL/a/LL/a/LL/a/eeee$。
- 对于第 $4$ 个文件，无满足条件的路径。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（33 pts）：$n,m \le 500$。
- Subtask 2（33 pts）：$n,m \le 3 \times 10^3$，符号链接最多被调用一次。
- Subtask 3（34 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le k,s \le 10^6$，$1\le m,n\le 3\times 10^3$。

#### 说明

翻译自 [BalticOI 2015 Day2 A File Paths](https://boi.cses.fi/files/boi2015_day2.pdf)。


---

---
title: "[USACO21JAN] Telephone G"
layout: "post"
diff: 提高+/省选-
pid: P7297
tag: ['USACO', '2021', '图论建模', '最短路']
---
# [USACO21JAN] Telephone G
## 题目描述

Farmer John 的 N 头奶牛，编号为 $1…N$，站成一行（$1≤N≤5⋅10^4$）。第 $i$ 头奶牛的品种编号为 $b_i$，范围为 $1\dots K$，其中 $1≤K≤50$。奶牛们需要你帮助求出如何最优地从奶牛 $1$ 传输一条信息到奶牛 $N$。

从奶牛 $i$ 传输信息到奶牛 $j$ 花费时间 $|i-j|$。然而，不是所有品种的奶牛都愿意互相交谈，如一个 $K\times K$ 的方阵 $S$ 所表示，其中如果一头品种 $i$ 的奶牛愿意传输一条信息给一头品种 $j$ 的奶牛，那么 $S_{ij}=1$，否则为 $0$。不保证 $S_{ij}=S_{ji}$，并且如果品种 $i$ 的奶牛之间不愿意互相交流时可以有 $S_{ii}=0$。

请求出传输信息所需的最小时间。 
## 输入格式

输入的第一行包含 $N$ 和 $K$。

下一行包含 $N$ 个空格分隔的整数 $b_1,b_2,\dots,b_N$。

以下 $K$ 行描述了方阵 $S$。每行包含一个由 $K$ 个二进制位组成的字符串，从上往下第 $i$ 个字符串的第 $j$ 位为 $S_{ij}$。 
## 输出格式

输出一个整数，为需要的最小时间。如果不可能从奶牛 $1$ 传输信息至奶牛 $N$，输出 $-1$。 
## 样例

### 样例输入 #1
```
5 4
1 4 2 3 4
1010
0001
0110
0100
```
### 样例输出 #1
```
6
```
## 提示

最优传输序列为 $1\to 4\to 3\t 5$。总时间为 $|1-4|+|4-3|+|3-5|=6$。

#### 测试点性质：

 - 测试点 1-5 满足 $N≤1000$。
 - 测试点 6-13 没有额外限制。

供题：Dhruv Rohatgi 


---

---
title: "[NOI Online 2021 入门组] 重力球"
layout: "post"
diff: 提高+/省选-
pid: P7473
tag: ['图论', '2021', '最短路', 'NOI Online']
---
# [NOI Online 2021 入门组] 重力球
## 题目描述

“重力球”游戏在一块 $n\times n$ 的正方形区域中进行，记从上往下第 $i$ 行，从左往右第 $j$ 列的位置为 $(i,j)$。

正方形区域中存在 $m$ 个障碍，第 $i$ 个障碍占据位置 $(x_i,y_i)$，此外，正方形区域的边界外都是障碍。

现在有两个小球，位置分别是 $(a,b)$ 和 $(c,d)$，在游戏中你可以进行如下操作：

- 指定上、下、左、右中的一个方向，将重力方向“切换”为这个方向。此时两个小球会同时向这个方向移动，直到碰到障碍。

你要用最少的操作次数使得两个小球到达同一个位置。

现有 $q$ 局游戏，每局游戏中只有小球的初始位置不同，而障碍位置是不变的，你需要对每局游戏都求出最小操作次数，或报告无解。
## 输入格式

第一行包含三个整数 $n,m,q$，分别表示矩形区域大小，障碍个数和游戏局数。

接下来 $m$ 行，每行包含两个整数 $x_i,y_i$，表示位置 $(x_i,y_i)$ 上有一个障碍。数据保证所有障碍所处的位置互不相同。

接下来 $q$ 行，每行四个整数 $a,b,c,d$，表示一局游戏中两个小球的初始位置，保证初始位置不存在障碍。
## 输出格式

输出共 $q$ 行，第 $i$ 行输出一个整数表示第 $i$ 局游戏需要的最小操作次数，如果无解则输出 `-1`。
## 样例

### 样例输入 #1
```
4 4 3
2 2
2 4
3 2
4 4
1 3 4 3
2 1 2 1
1 2 3 4
```
### 样例输出 #1
```
1
0
3
```
## 提示

### 样例 $1$ 解释

该样例中障碍分布如图中红叉所示。

第一组询问中只需将重力改向上（或改向下）即可使两球同时到达。

第二组询问中两球已经在同一位置故不需操作。

第三组询问中改变3 次重力的方向，依次改为向左、向下、向左，小球移动路线分别如图中粉色、橙色、棕色线所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7nngrov0.png)
### 数据范围与提示
对于 $20\%$ 的数据：$n,m\le 2$。

对于 $50\%$ 的数据：$n,m\le30$。

对于另外 $30\%$ 的数据：$q=1$。

对于 $100\%$ 的数据：$1\le n,m\le250，1\le q\le10^5，1\le x_i,y_i,a,b,c,d\le n$。

数据由 [SSerxhs](https://www.luogu.com.cn/user/29826) 提供。

数据参考了 小喵喵不喜欢计算几何 2020 ICPC 区域赛（南京）A 题的构造方案，在此表示感谢。


---

---
title: "[USACO21OPEN] Portals G"
layout: "post"
diff: 提高+/省选-
pid: P7528
tag: ['USACO', '2021', '图论建模', '生成树']
---
# [USACO21OPEN] Portals G
## 题目描述

Bessie 位于一个由 $N$ 个编号为 $1\dots N$ 的结点以及 $2N$ 个编号为 $1\cdots 2N$ 的传送门所组成的网络中。每个传送门连接两个不同的结点 $u$ 和 $v$（$u≠v$）。可能有多个传送门连接同一对结点。

每个结点 $v$ 与四个不同的传送门相连。与 $v$ 相连的传送门列表由 $p_v=[p_{v,1},p_{v,2},p_{v,3},p_{v,4}]$ 给出。

你的当前位置可以用有序对（当前结点，当前传送门）表示；即一个有序对 $(v,p_{v,i})$
，其中 $1\le v\le N$ 以及 $1\le i\le 4$。你可以使用以下任一操作来改变你的当前位置：

- 1. 由穿过当前传送门来改变当前结点。
- 2. 改变当前传送门。在每一个结点上，列表的前两个传送门是配对的，后两个传送门也是配对的。也就是说，如果你的当前位置是 $(v,p_{v,2})$，你可以转而使用传送门 $(v,p_{v,1})$，反之亦然。类似地，如果你的当前位置是 $(v,p_{v,3})$，你可以转而使用传送门 $(v,p_{v,4})$，反之亦然。没有其他改变传送门的方式（例如，你**不能**从传送门 $p_{v,2}$ 转去传送门 $p_{v,4}$ ）。

总共有 $4N$ 个不同的位置。不幸的是，并不一定每一个位置都可以从另外的每一个位置经过一系列操作而到达。所以，以 $c_v$ 哞尼的代价，你可以以任意顺序重新排列与 $v$ 相邻的传送门列表。在此之后，列表中的前两个传送门互相配对，同时后两个传送门也互相配对。

例如，如果你将与 $v$ 相邻的传送门以 $[p_{v,3},p_{v,1},p_{v,2},p_{v,4}]$ 的顺序重新排列，这意味着如果你位于结点 $v$ ，
- 如果你当前位于传送门 $p_{v,1}$ ，你可以转而使用传送门 $p_{v,3}$，反之亦然。
- 如果你当前位于传送门 $p_{v,2}$ ，你可以转而使用传送门 $p_{v,4}$，反之亦然。
你不再能够从传送门 $p_{v,1}$
转至传送门 $p_{v,2}$，或从传送门 $p_{v,3}$ 转至 $p_{v,4}$ ，反之亦然。

计算修改这一网络使得每一个位置都可以从另外的每一个位置到达所需要花费的哞尼的最小数量。输入保证存在至少一种修改网络的合法方式。 
## 输入格式

输入的第一行包含 $N$。

以下 $N$ 行每行描述一个结点。第 $v+1$ 行包含五个空格分隔的整数 $c_v,p_{v,1},p_{v,2},p_{v,3},p_{v,4}$。

输入保证对于每一个 $v$ ，$p_{v,1},p_{v,2},p_{v,3},p_{v,4}$ 各不相同，且每个传送门出现在**恰好两个结点**的邻接表中。 
## 输出格式

输出一行，包含修改这一网络使得每一个位置都可以从另外的每一个位置到达所需要花费的哞尼的最小数量。 
## 样例

### 样例输入 #1
```
5
10 1 4 8 9
11 1 2 5 6
12 9 10 2 3
3 4 3 6 7
15 10 8 7 5
```
### 样例输出 #1
```
13
```
## 提示

#### 样例解释

重新排列结点 $1$ 和 $4$ 的邻接表就已足够。这需要总计 $c_1+c_4=13$ 哞尼。我们可以使 $p_1=[1,9,4,8]$ 以及 $p_4=[7,4,6,3]$。 

#### 数据范围与约定

$2\le N\le 10^5$，$1\le c_v\le 10^3$。


---

---
title: "[COCI 2011/2012 #2] FUNKCIJA"
layout: "post"
diff: 提高+/省选-
pid: P7618
tag: ['动态规划 DP', '图论', '2011', 'COCI（克罗地亚）']
---
# [COCI 2011/2012 #2] FUNKCIJA
## 题目描述

Mirko 写了如下的函数：

（C++）

```cpp
int fun() {
    int ret = 0;
    for (int a = X1; a <= Y1; ++a)
         for (int b = X2; b <= Y2; ++b)
             ...
                 for (int <N-th> = XN; <N-th> <= YN; ++<N-th>)
                     ret = (ret + 1) % 1000000007;
    return ret;
}

```

（Pascal）

```pascal
function fun: longint;
var
  ret: longint;
  a, b, ... , y, z: longint;
begin
  ret := 0;
  for a := X1 to Y1 do
    for b := X2 to Y2 do
      ...
        for <N-th> := XN to YN do
          ret := (ret + 1) mod 1000000007;
  fun := ret;
end;
```

_<N-th>_ 表示第 $N$ 个小写字母。每个 $X_i$ 和 $Y_i$ 可能表示外层循环的变量名，也可能表示一个 $\le 10^5$ 的正整数。例如 $X_3$ 可以是 $a$，$b$，也可以是一个整数常量。$X_i$ 和 $Y_i$ 中至少有一个会是整数常量。

计算这个函数的返回值。
## 输入格式

输入的第一行包含一个正整数 $N$。

接下来 $N$ 行的第 $i$ 行每行包含用空格分隔的 $X_i,Y_i$。如果 $X_i$ 和 $Y_i$ 都是整数常量，那么 $X_i \le Y_i$。
## 输出格式

输出一行一个整数，表示函数的返回值。
## 样例

### 样例输入 #1
```
2
1 2
a 3
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
3
2 3
1 2
1 a
```
### 样例输出 #2
```
10
```
### 样例输入 #3
```
3
1 2
a 3
1 b
```
### 样例输出 #3
```
11
```
## 提示

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le N \le 26$。

#### 【说明】

本题分值按 COCI 原题设置，满分 $150$。

题目译自 **[COCI2011-2012](https://hsin.hr/coci/archive/2011_2012/) [CONTEST #2](https://hsin.hr/coci/archive/2011_2012/contest2_tasks.pdf)** ___T5 FUNKCIJA___。


---

---
title: "「EZEC-10」序列"
layout: "post"
diff: 提高+/省选-
pid: P7717
tag: ['动态规划 DP', '2021', 'O2优化', '深度优先搜索 DFS', '数位 DP', '图论建模', '字典树 Trie', '位运算']
---
# 「EZEC-10」序列
## 题目背景

> 精准的解析刻画，是应该首先尝试的突破口。

——command_block 《考前小贴士》
## 题目描述

请问有多少个不同的序列 $a$，满足：
1. $a$ 的长度为 $n$。
2. $a$ 中的元素均为不大于 $k$ 的非负整数。
3. 满足 $m$ 组形如 $(x_i,y_i,z_i)$ 且 $x_i<y_i$ 的限制，每组限制的意义为 $a_{x_i} \oplus a_{y_i} = z_i$ （$\oplus$ 表示按位异或运算）。

两个序列相同，当且仅当它们所有元素均相同。

请输出答案对 $10^9+7$ []($114514\times(114\times5\times14+((1+145)\times(1+4)+(1\times14+5-1+4)))+(114\times514+(11\times(451+4)+(-1+145+14)))$)取模的结果。
## 输入格式

输入共 $m+1$ 行：
- 第一行三个数，$n,m,k$。
- 接下来 $m$ 行，每行 $3$ 个数，$x_i,y_i,z_i$。
## 输出格式

输出仅一行，表示答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
3 1 2
1 2 1
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
5 1 12
1 2 3

```
### 样例输出 #2
```
26364
```
## 提示

【样例 $1$ 说明】

共有 $6$ 种序列：$\{0,1,0\},\{0,1,1\},\{0,1,2\},\{1,0,0\},\{1,0,1\},\{1,0,2\}$。

【数据规模与约定】

**本题采用捆绑测试。**

- Subtask 1（1 point）：$n=1$。
- Subtask 2（5 points）：$m=0$。
- Subtask 3（15 points）：$n,m,k\le 5$。
- Subtask 4（10 points）：$z_i=0$。
- Subtask 5（20 points）：$k\le 16$。
- Subtask 6（2 points）：数据随机。
- Subtask 7（47 points）：无特殊限制。

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^5$，$0 \le m \le 5 \times 10^5$，$0 \le z_i<2^{30}$，$1 \leq k< 2^{30}$，$1\le x_i,y_i\le n$。

【提示】

如果你不知道什么是异或，请点击[这里](https://baike.baidu.com/item/%E5%BC%82%E6%88%96#:~:text=%E5%BC%82%E6%88%96%E4%B9%9F%E5%8F%AB%E5%8D%8A,%E8%AE%A4%E4%BD%9C%E4%B8%8D%E8%BF%9B%E4%BD%8D%E5%8A%A0%E6%B3%95%E3%80%82&text=%E7%A8%8B%E5%BA%8F%E4%B8%AD%E6%9C%89%E4%B8%89%E7%A7%8D%E6%BC%94%E7%AE%97%E5%AD%90%EF%BC%9AXOR%E3%80%81eor%E3%80%81%E2%8A%95%E3%80%82)。


---

---
title: "「dWoi R2」Change / 改造"
layout: "post"
diff: 提高+/省选-
pid: P7845
tag: ['图论', '拓扑排序']
---
# 「dWoi R2」Change / 改造
## 题目背景

入间改造对人类生存繁殖有帮助的工具（~~就是性能工具，具体可以去看看弹丸论破 V3 自由时间与入间美兔的交谈，在这里不方便说吧，毕竟是 青 少 年 编 程 网 站~~）玩腻了，她发现了有一个很 符 合 她 胃 口 的东西，叫做 Galgame，于是她开始打一款叫做 Little Busters 的 Galgame，然后沉迷上了沙耶线最后的场景。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/vxy5rh6c.png)

## 题目描述

在经过 $99$ 次的 Replay 后，沙耶终于发现迷宫是一个有向无环图。为了保证最后一次 Replay 的趣味性，时风瞬给沙耶和理树安排了一个小游戏。

这张有向无环图 $G$ 有 $n$ 个点，$m$ 条边，每条边的长度为 $1$。设 $l_i$ 为初始点 $s$ 到第 $i$ 条边所指向的点 $u$ 的最短路，定义第 $i$ 条边的边权为 $p-l_i$。游戏步骤是这样的（所有选择都是按如下顺序进行，并且每个人的选择都是公开的）。

1. 理树站在点 $s$ 上。  
2. 时风瞬会随机选取一个点作为 $t$（$t$ 可以等于 $s$）。
3. 如果无法从 $s$ 到达 $t$，游戏直接结束。
3. 沙耶需要选择一条边。
4. 理树需要找到一条从 $s$ 到 $t$ 的路径。
5. 若沙耶选择的边在理树所选择的路径上，则理树就会将这条边的边权的钱给沙耶。

理树希望能少输钱，沙耶希望能多拿钱。若两方都采取最优策略，请问沙耶期望能得到多少钱。
## 输入格式

第一行四个整数 $n,m,s,p$，分别代表有向图点数，边数与理树站在的位置，以及题目中出现的 $p$。

接下来 $m$ 行每行两个整数 $u_i,v_i$ 描述一条边。
## 输出格式

一行一个整数代表答案。

请对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
8 8 1 10
1 2
1 3
1 4
2 5
3 5
5 6
6 7
6 8
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
3 2 1 3
1 2
1 3
```
### 样例输出 #2
```
332748119
```
## 提示

#### 样例 1 解释

比如 $t=6$ 时，沙耶应该选择连接 $5,6$ 的那条边；$t=8$ 时，沙耶仍然应该选择连接 $5,6$ 的那条边；$t=4$ 时，应该选择连接 $1,4$ 的那条边；$t=5$ 时，沙耶无论选择什么边都不会得到钱。

设 $res_u$ 表示 $t=u$ 时沙耶能获得的最大收益，我们有 $res=\{0,9,9,9,0,7,7,7\}$。

#### 样例 2 解释

设 $res_u$ 表示 $t=u$ 时沙耶能获得的最大收益，我们有 $res=\{0,2,2\}$。

---

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$n,m \le 5$；
- Subtask 2（20 pts）：$m=n-1$，$u_i<v_i$，$s=1$；
- Subtask 3（30 pts）：$n,m \le 10^3$；
- Subtask 4（40 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,m \le 5 \times 10^6$，$1 \le s \le n$，$1 \le u_i,v_i \le n$，$u_i \ne v_i$，$n\le p \le 10^9$。


---

---
title: "「SWTR-7」Scores（hard version）"
layout: "post"
diff: 提高+/省选-
pid: P7876
tag: ['模拟', '2021', 'Special Judge', 'O2优化', '图论建模', '图遍历', '构造', '洛谷月赛']
---
# 「SWTR-7」Scores（hard version）
## 题目背景

#### 本题是 Scores 的 hard 版本。注意题目限制与 [easy](https://www.luogu.com.cn/problem/P7873) 版本不同。

#### 请注意特殊的时空限制。
## 题目描述

小 A 的班上有 $n$ 个学生。最近他们进行了一场考试，共有 $m$ 个学科。第 $i$ 个学生第 $j$ 门学科的得分为**整数** $s_{i,j}\ (0\leq s_{i,j}\leq 100)$。

同学们很重视自己在班上的排名，所以他们经常会比较自己和别的同学的分数。如果一个学生 $i$ **至少有一门学科**的分数比 $j$ **高**，ta 就会觉得自己不比 $j$ 差；相反，如果 ta **每门学科**的分数都比 $j$ **低**，ta 就会觉得自己被 $j$ 吊打了。

实际上，**上述两种情况并不是严格意义上相反的**。但是喜好八卦的小 A 打听到了每两个同学之间的分数情况，他惊讶地发现：**一个同学 $i$ 要么被 $j$ 吊打，要么不比 $j$ 差。** 同时，**如果 $i,j$ 被同一个人吊打，或同时吊打同一个人，则他们之间也有一方被另一方吊打**。我们用一个矩阵 $a_{i,j}\ (i\neq j)$ 来描述小 A 知道的同学们之间的分数关系：$a_{i,j}=0$ 表示 $i$ 被 $j$ 吊打；$a_{i,j}=1$ 表示 $i$ 不比 $j$ 差。

小 A 想知道这种情况会不会发生，即是否存在这样一张 $n\times m$ 的成绩表 $s$ 满足矩阵 $a$ 所描述的分数关系，从而确定有没有撒谎的同学。如果存在 $s$，请先输出 $\texttt{YES}$，再**任意**输出一种符合要求的成绩表；否则输出 $\texttt{NO}$。

注意：这里所求的 $s$ 所需满足的条件是 $a$ 的限制，而**不只是**小 A 所发现的性质，因为**他发现的性质已经在给出的 $a$ 中体现**。
## 输入格式

**本题有多组数据。**

第一行一个整数 $t$，**表示该测试点编号**。  
第二行一个整数 $T$，**表示数据组数**。

对于每组数据：  
第一行两个整数 $n,m$。  
接下来 $n$ 行，每行 $n$ 个由空格隔开的 0 或 1 描述 $a$。第 $i+1$ 行第 $j$ 个数表示 $a_{i,j}$。

特别的，为了方便读入，**规定 $a_{i,i}=0$**。但你需要知道**它没有任何实际意义**。
## 输出格式

对于每组数据：

如果不存在满足条件的 $s$，输出一行字符串 $\texttt{NO}$。  
否则先输出一行字符串 $\texttt{YES}$，再输出 $n$ 行，每行 $m$ 个由空格隔开的整数，第 $i+1$ 行第 $j$ 个数表示 $s_{i,j}\ (0\leq s_{i,j}\leq 100)$。
## 样例

### 样例输入 #1
```
0
5
5 3
0 1 1 1 1
1 0 1 1 1
1 1 0 1 1
1 1 1 0 1
1 1 1 1 0
2 7
0 1
0 0
5 4
0 1 1 0 1
0 0 0 0 1
0 1 0 0 1
1 1 1 0 1
1 1 1 1 0
3 1
0 1 1
1 0 1
1 1 0
3 2
0 1 0
0 0 1
1 0 0
```
### 样例输出 #1
```
YES
100 99 97
98 100 99
95 97 100
0 98 100
99 99 99
YES
98 100 94 98 72 53 53
97 99 93 97 71 52 52
YES
90 80 70 60
50 40 30 20
60 50 40 30
100 90 80 70
40 60 80 100
NO
NO
```
## 提示

**「Special Judge」**

**本题使用 Special Judge。请认真阅读输出格式，输出格式有误可能导致 UKE 或 WA。**

SPJ 首先会判断你的第一行输出是否与答案相同。  
如果相同且答案为 $\texttt{YES}$，则 SPJ 会判断你的输出是否符合所有限制。  
如果有解且你输出 $\texttt{YES}$，但给出方案错误，你将获得该测试点 $50\%$ 的分数。

你需要满足的限制如下：  
- $0\leq s_{i,j}\leq 100$。
- 对于任意 $i,j\ (i\neq j)$，若 $a_{i,j}=0$，则对于任意 $k\ (1\leq k\leq m)$，有 $s_{i,k}<s_{j,k}$；若 $a_{i,j}=1$，则存在一个 $k\in [1,m]$，使得 $s_{i,k}>s_{j,k}$。

你需要注意的是，所有输出都应严格符合输出格式。如果你对答案的存在性判断正确，但是输出方案时 $s_{i,j}<0$ 或 $s_{i,j}>100$，SPJ 会判定为 WA，得 $0$ 分，而不是 $50\%\ \times$ 该测试点分数。

**「数据范围与约定」**

本题共有 6 个测试点。

- Testcase #0（1 point）：是样例。
- Testcase #1（10 points）：$n=1$。
- Testcase #2（10 points）：$m=1$。
- Testcase #3（30 points）：$m=2$。
- Testcase #4（20 points）：$a_{i,j}=1\ (i\neq j)$。
- Testcase #5（29 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,m\leq 100$，$a_{i,j}\in\{0,1\}$，$T=50$（除 Testcase #0）。  
对于 $a$ 的限制：若 $a_{i,j}=a_{i,k}=0$，则 $a_{j,k}$ 和 $a_{k,j}$ 中至少有一个为 $0$；若 $a_{i,k}=a_{j,k}=0$，则 $a_{i,j}$ 和 $a_{j,i}$ 中至少有一个为 $0$。  
对于所有测试点，**时间限制 500ms，空间限制 16MB。**

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) A2。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。


---

---
title: "[USACO22JAN] Cereal 2 S"
layout: "post"
diff: 提高+/省选-
pid: P8095
tag: ['USACO', '2022', '网络流', 'Special Judge', '图论建模', '构造']
---
# [USACO22JAN] Cereal 2 S
## 题目描述

Farmer John 的奶牛们的早餐最爱当然是麦片了！事实上，奶牛们的胃口是如此之大，每头奶牛一顿饭可以吃掉整整一箱麦片。

最近农场收到了一份快递，内有 $M$ 种不同种类的麦片（$2\le M\le 10^5$）。不幸的是，每种麦片只有一箱！$N$ 头奶牛（$1\le N\le 10^5$）中的每头都有她最爱的麦片和第二喜爱的麦片。给定一些可选的麦片，奶牛会执行如下的过程：

- 如果她最爱的麦片还在，取走并离开。

- 否则，如果她第二喜爱的麦片还在，取走并离开。

- 否则，她会失望地哞叫一声然后不带走一片麦片地离开。

当你最优地排列这些奶牛时，求饥饿的奶牛的最小数量。同时，求出任意一个可以达到此最小值的 $N$ 头奶牛的排列。

## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $M$。

对于每一个 $1\le i\le N$，第 $i$ 行包含两个空格分隔的整数 $f_i$ 和 $s_i$（$1\le f_i,s_i\le M$，且 $f_i\neq s_i$），为第 $i$ 头奶牛最喜爱和第二喜爱的麦片。
## 输出格式

输出饥饿的奶牛的最小数量，并输出任意一个可以达到此最小值的 $1\ldots N$ 的排列。如果有多个符合要求的排列，输出任意一个。
## 样例

### 样例输入 #1
```
8 10
2 1
3 4
2 3
6 5
7 8
6 7
7 5
5 8
```
### 样例输出 #1
```
1
1
3
2
8
4
6
5
7
```
## 提示

【样例解释】

在这个例子中，有 $8$ 头奶牛和 $10$ 种麦片。

注意我们对前三头奶牛独立于后五头奶牛求解，因为她们没有共同喜欢的麦片。

如果前三头奶牛按顺序 $[1,2,3]$ 进行选择，则奶牛 $1$ 会选择麦片 $2$，奶牛 $2$ 会选择麦片 $3$，奶牛 $3$ 会饥饿。

如果前三头奶牛按顺序 $[1,3,2]$ 进行选择，则奶牛 $1$ 会选择麦片 $2$，奶牛 $3$ 会选择麦片 $3$，奶牛 $2$ 会选择麦片 $4$；没有奶牛会饥饿。

当然，还存在其他排列使得前三头奶牛均不饥饿。例如，如果前三头奶牛按顺序 $[3,1,2]$ 选择，则奶牛 $3$ 会选择麦片 $2$，奶牛 $1$ 会选择麦片 $1$，奶牛 $2$ 会选择麦片 $3$；同样，奶牛 $[1,2,3]$ 均不会饥饿。

可以证明在后五头奶牛中，至少一头会饥饿。

【数据范围】

- $14$ 个测试点中的 $4$ 个测试点满足 $N,M\le 100$。

- $14$ 个测试点中的 $10$ 个测试点没有额外限制。

【说明】

本题采用自行编写的 [Special Judge](https://www.luogu.com.cn/paste/hi36jkwh)。如果对此有疑问或想要 hack，请[私信编写者](https://www.luogu.com.cn/chat?uid=137367)或[发帖](https://www.luogu.com.cn/discuss/lists?forumname=P8095)。


---

---
title: "[THUPC 2022 初赛] 最小公倍树"
layout: "post"
diff: 提高+/省选-
pid: P8207
tag: ['2022', 'O2优化', '图论建模', '生成树', 'THUPC']
---
# [THUPC 2022 初赛] 最小公倍树
## 题目背景

听说有人嫌题面描述都太长了。
## 题目描述

对于任意 $V\subset\mathbb{N}^*$，$|V|<+\infty$，构造一张无向完全图 $G=(V,E)$，其中 $(u, v)$ 的边权为 $u,v$ 的最小公倍数 $\mathrm{lcm}(u, v)$。称 $G$ 的最小生成树为 $V$ 的最小公倍树（LCT, Lowest Common Tree）。

现在给出 $L, R$，请你求出 $V={L, L+1, \cdots, R}$ 的最小公倍树 $LCT(V)$。
## 输入格式

输入仅一行，包括两个正整数 $L, R$。
## 输出格式

输出一个正整数，表示 $LCT(V)$ 的边权和。
## 样例

### 样例输入 #1
```
3 12
```
### 样例输出 #1
```
126
```
### 样例输入 #2
```
6022 14076
```
### 样例输出 #2
```
66140507445
```
### 样例输入 #3
```
13063 77883
```
### 样例输出 #3
```
3692727018161
```
### 样例输入 #4
```
325735 425533
```
### 样例输出 #4
```
1483175252352926
```
## 提示

【样例解释】

其中一种最小公倍树上的边为 $(3, 4), (3, 5), (3, 6), (3, 7), (4, 8), (3, 9), (5, 10), (3, 11), (3, 12)$。

【数据范围】

对于 $100%$ 的数据，保证 $1\le L\le R\le 10^6$，且 $R-L\le 10^5$。


---

---
title: "[COCI 2012/2013 #2] INFORMACIJE"
layout: "post"
diff: 提高+/省选-
pid: P8299
tag: ['图论', '2012', 'Special Judge', 'COCI（克罗地亚）']
---
# [COCI 2012/2013 #2] INFORMACIJE
## 题目背景

**本题分值按 COCI 原题设置，满分 $140$。**
## 题目描述

Mirko 很无聊，所以他拿起一张纸，写下了一个含有 $N$ 个元素的序列 $A$，$1\sim N$ 的所有正整数在其中恰好仅出现一次。然后，他拿了另外一张纸，写下了 $M$ 个关于 $A$ 的描述。

每个描述有两种方式：

- `1 x y v`：表示 $[x,y]$ 区间中最大的数为 $v$。

- `2 x y v`：表示 $[x,y]$ 区间中最小的数为 $v$。

随后 Slavko 来偷走了他的第一张纸。Mirko 感到绝望，他想要你找到满足这些描述的序列，不需要跟原序列完全相同。
## 输入格式

第一行两个整数 $N,M\ (1\le N\le 200, 0\le M\le 4\times 10^4)$，分别表示序列长度以及描述的数量。

接下来 $M$ 行每行一个描述。
## 输出格式

输出仅一行，一个满足所有描述的长为 $N$ 的序列，并且 $1\sim N$ 在其中出现并仅出现一次，用空格隔开。如无解，输出 $-1$。
## 样例

### 样例输入 #1
```
3 2
1 1 1 1
2 2 2 2
```
### 样例输出 #1
```
1 2 3
```
### 样例输入 #2
```
4 2
1 1 1 1
2 3 4 1
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
5 2
1 2 3 3
2 4 5 4

```
### 样例输出 #3
```
1 2 3 4 5
```


---

---
title: "「Wdoi-6」最澄澈的空与海"
layout: "post"
diff: 提高+/省选-
pid: P8346
tag: ['搜索', '图论', '洛谷原创', 'O2优化', '二分图', '洛谷月赛']
---
# 「Wdoi-6」最澄澈的空与海
## 题目背景

[![](https://cdn.luogu.com.cn/upload/image_hosting/hiekh6t5.png)](https://thwiki.cc/%E5%8D%AF%E9%85%89%E4%B8%9C%E6%B5%B7%E9%81%93_%EF%BD%9E_Retrospective_53_minutes.)

广重号载着二人向东飞驰。毫无噪音，毫无摇摆，只是一个劲向东飞驰。在“万景幕”装置之下，尽管是全地下的卯酉东海道，乘客们也能饱览美丽的富士山和太平洋的景色。

但是，从这列卯酉新干线『广重』上看到的极富日本风味的美丽情景，对于梅莉来说，只不过是无趣的视觉刺激罢了。高动态范围的影像也好，极富日本风味的情景也好，都敌不过真正的天空的颜色。

身与华落，心将香飞。即便肉体会像花朵一样终有一天凋落，但心却可以如花香一般飘往远方。

「梅莉，你看，天上的星星呦。」
## 题目描述

### 简要题意

给定 $2n$ 个点、$m$ 条边的[二分图](http://oi-wiki.com/graph/bi-graph/#_1)（可能有重边），左部点与右部点个数相同，判断其完美匹配数量是否**恰好**为 $1$。是则输出 `Renko`，否则输出 `Merry`。

> **注**：完美匹配是指，从边集中选出 $n$ 条边，这些边的顶点组成的点集恰好覆盖了所有的 $2n$ 个点。

---
### 原始题意

在夜里，莲子与梅莉来到了东京的海边，躺在沙滩上，欣赏着澄澈的天空与大海，数起了天上的星星。

在这些星星之中，有 $n$ 个星星 $\{a_i\}$，是莲子先发现的，被称为莲子星；而又有 $n$ 个星星 $\{b_i\}$，是梅莉先发现的，被称为梅莉星。由于她们心有灵犀，这两批星星之间**不存在交集**。  

她们发现，有一些莲子星，与一些梅莉星之间恰好存在运动关系。具体而言，这些关系一共有 $m$ 组，每一组关系形如 $(u_i,v_i)$，也就是说第 $u_i$ 颗莲子星与第 $v_i$ 颗梅莉星之间存在运动关系。这些运动关系有可能重复。

这让莲子和梅莉非常好奇。作为专攻超统一物理学的女大学生，莲子认为，如果认为这些星星的运动是**和谐**的，那么她应当能够从这 $m$ 个运动关系中，找出若干个运动关系，使得**每颗**星星**都被**这些运动关系**包含**的同时，不会有一颗星星**被包含在两个**运动关系之中。

然而，梅莉认为，**和谐**的运动可能是不存在的，更何况即使莲子找到了**和谐**的运动，莲子也无法确保这种和谐运动的**唯一性**。两种和谐运动不同，当且仅当选取出的两组运动关系中，存在至少一个运动关系，是不相同的。

因为意见不合，她们于是打情骂俏了一顿。莲子于是记下了她们所看到了星星和她们之间的运动关系，并且找到了已经证明了 P=NP 的你，希望你能告诉她们，最后是谁正确呢？
## 输入格式

第一行输入一个正整数 $T$ 表示数据组数，对于每一组数据：

- 第一行一个整数 $n$，代表莲子和梅莉每个人所先发现的星星的数量。
- 第二行一个整数 $m$，代表运动关系的数量。
- 接下来 $m$ 行，每行两个整数 $u_i,v_i$，表示第 $u_i$ 颗莲子星，与第 $v_i$ 颗梅莉星之间，存在运动关系。
## 输出格式

- 如果这些星星中存在唯一的和谐运动，输出 `Renko`。
- 如果这些星星中不存在和谐运动，或者有不唯一的和谐运动方式，输出 `Merry`。
## 样例

### 样例输入 #1
```
1
5
6
1 1
1 3
3 2
2 5
4 3
5 4
```
### 样例输出 #1
```
Renko
```
## 提示

### 样例解释

#### 样例 \#1

![](https://cdn.luogu.com.cn/upload/image_hosting/6skoily9.png)

如图所示，存在唯一的方案：$\{1\to 1,2\to 5,3\to 2,4\to 3,5\to 4\}$。

### 数据范围

**本题采用捆绑测试。**

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|}\hline
\textbf{Subtask} & \textbf{\textsf{分值}} & \bm{n\le } & \bm{m\le} & \textbf{\textsf{特殊性质}} & \textbf{Subtask \textsf{依赖}}\cr\hline
1 & 10 & 10 & 10 & - & - \cr\hline
2 & 20 & 300 & 4\times 10^4 & - & 1\cr\hline
3 & 20 & 10^5 & 5 \times 10^5 & \mathbf{A} & - \cr\hline
4 & 20 & 10^5 & 2 \times 10^5 & \mathbf{B} & - \cr\hline
5 & 30& 10^6 & 2\times 10^6 & - & 2,3,4 \cr\hline
\end{array}
$$

- 特殊性质 $\mathbf{A}$：保证对于第 $i$ 颗莲子星，与第 $i$ 颗梅莉星之间存在运动关系。
- 特殊性质 $\mathbf{B}$：保证 $m=2n-1$。

对于 $100\%$ 的数据，保证 $1 \le u_i,v_i\le n \le 10^6$，$1 \le m \le 2 \times 10^6$，$1 \leq T \leq 5$ 且对于每个测试点，$\sum m \leq 4 \times 10^6$。

对于 $\rm Subtask\ 5$，时间限制为 $3$ 秒。其它测试点时间限制为 $1$ 秒。


---

---
title: "[蓝桥杯 2020 国 AB] 出租车"
layout: "post"
diff: 提高+/省选-
pid: P8731
tag: ['2020', '图论建模', '最短路', '蓝桥杯国赛']
---
# [蓝桥杯 2020 国 AB] 出租车
## 题目背景

小蓝在 $L$ 市开出租车。
## 题目描述

$L$ 市的规划很规整，所有的路都是正东西向或者正南北向的，道路都可以看成直线段。东西向的道路互相平行, 南北向的道路互相平行，任何一条东西向道路垂直于任何一条南北向道路。

从北到南一共有 $n$ 条东西向道路，依次标号为 $H_{1}, H_{2}, \cdots, H_{n}$ 。从西到东 一共有 $m$ 条南北向的道路，依次标号为 $S_{1}, S_{2}, \cdots, S_{m}$ 。

每条道路都有足够长，每一条东西向道路和每一条南北向道路都相交，$H_{i}$ 与 $S_{j}$ 的交叉路口记为 $(i, j)$ 。

从 $H_{1}$ 和 $S_{1}$ 的交叉路口 $(1,1)$ 开始，向南遇到的路口与 $(1,1)$ 的距离分别 是 $h_{1}, h_{2}, \cdots, h_{n-1}$，向东遇到路口与 $(1,1)$ 的距离分别是 $w_{1}, w_{2}, \cdots, w_{m-1}$ 。

道路的每个路口都有一个红绿灯。

时刻 $0$ 的时候，南北向绿灯亮，东西向红灯亮，南北向的绿灯会持续一段时间（每个路口不同)，然后南北向变成红灯，东西向变成绿灯，持续一段时间后，再变成南北向绿灯，东西向红灯。

已知路口 $(i, j)$ 的南北向绿灯每次持续的时间为 $g_{i j}$, 东西向的绿灯每次持续的时间为 $r_{i j}$, 红绿灯的变换时间忽略。

当一辆车走到路口时，如果是绿灯，可以直行、左转或右转。如果是红灯，可以右转，不能直行或左转。如果到路口的时候刚好由红灯变为绿灯，则视为看到绿灯；如果刚好由绿灯变为红灯，则视为看到红灯。

每段道路都是双向道路，道路中间有隔离栏杆，在道路中间不能掉头, 只能在红绿灯路口掉头。掉头时不管是红灯还是绿灯都可以直接掉头。掉头的时间可以忽略。

小蓝时刻 $0$ 从家出发。今天，他接到了 $q$ 个预约的订单，他打算按照订单 的顺序依次完成这些订单，就回家休息。中途小蓝不准备再拉其他乘客。小蓝的家在两个路口的中点，小蓝喜欢用 $x_{1}, y_{1}, x_{2}, y_{2}$ 来表示自己家的位 置, 即路口 $\left(x_{1}, y_{1}\right)$ 到路口 $\left(x_{2}, y_{2}\right)$ 之间的道路中点的右侧, 保证两个路口相邻 (中间没有其他路口)。请注意当两个路口交换位置时，表达的是路的不同两边，路中间有栏杆，因此这两个位置实际要走比较远才能到达。

小蓝的订单也是从某两个路口间的中点出发，到某两个路口间的中点结束。小蓝必须按照给定的顺序处理订单，而且一个时刻只能处理一个订单，不能图省时间而同时接两位乘客，也不能揷队完成后面的订单。

小蓝只对 $L$ 市比较熟，因此他只会在给定的 $n$ 条东西向道路和 $m$ 条南北向道路上行驶，而且不会驶出 $H_{1}, H_{n}, S_{1}, S_{m}$ 这几条道路所确定的矩形区域 (可 以到边界。

小蓝行车速度一直为 $1$，乘客上下车的时间忽略不计。

请问，小蓝最早什么时候能完成所有订单回到家。
## 输入格式

输入第一行包含两个整数 $n, m$，表示东西向道路的数量和南北向道路的数 量。

第二行包含 $n-1$ 个整数 $h_{1}, h_{2}, \cdots, h_{n-1}$ 。

第三行包含 $m-1$ 个整数 $w_{1}, w_{2}, \cdots, w_{m-1}$ 。

接下来 $n$ 行, 每行 $m$ 个整数，描述每个路口南北向绿灯的时间，其中的第 $i$ 行第 $j$ 列表示 $g_{i j}$ 。

接下来 $n$ 行, 每行 $m$ 个整数，描述每个路口东西向绿灯的时间，其中的第 $i$ 行第 $j$ 列表示 $r_{i j}$ 。

接下来一行包含四个整数 $x_{1}, y_{1}, x_{2}, y_{2}$，表示小蓝家的位置在路口 $\left(x_{1}, y_{1}\right)$ 到路口 $\left(x_{2}, y_{2}\right)$ 之间的道路中点的右侧。

接下来一行包含一个整数 $q$，表示订单数量。

接下来 $q$ 行，每行描述一个订单，其中第 $i$ 行包含八个整数 $x_{i 1}, y_{i 1}, x_{i 2}, y_{i 2}$，$x_{i 3}, y_{i 3}, x_{i 4}, y_{i 4}$，表示第 $i$ 个订单的起点为路口 $\left(x_{i 1}, y_{i 1}\right)$ 到路口 $\left(x_{i 2}, y_{i 2}\right)$ 之间的道 路中点的右侧，第 $i$ 个订单的终点为路口 $\left(x_{i 3}, y_{i 3}\right)$ 到路口 $\left(x_{i 4}, y_{i 4}\right)$ 之间的道路中 点的右侧。 
## 输出格式

输出一个实数，表示小蓝完成所有订单最后回到家的最早时刻。四舍五入保留一位小数。
## 样例

### 样例输入 #1
```
2 3
200
100 400
10 20 10
20 40 30
20 20 20
20 20 20
2 1 1 1
1
2 2 1 2 1 2 1 3
```
### 样例输出 #1
```
1620.0
```
## 提示

**【样例说明】**

蓝有一个订单, 他的行车路线如下图所示。其中 $\mathrm{H}$ 表示他家的位置, $\mathrm{S}$ 表示订单的起点, $\mathrm{T}$ 表示订单的终点。小小明在最后回家时要在直行的红绿灯路 口等绿灯, 等待时间为 $20$。 

![](https://luogu.oss-cn-hangzhou.aliyuncs.com/upload/vjudge_pic/lanqiao/2022_09_30_334c51de49a3a8e7ba1bg-15.jpg)

**【评测用例规模与约定】**

对于 $20 \%$ 的评测用例, $1 \leq n, m \leq 5,1 \leq q \leq 10$ 。

对于 $50 \%$ 的评测用例, $1 \leq n, m \leq 30,1 \leq q \leq 30$ 。

对于所有评测用例, $1 \leq n, m \leq 100,1 \leq q \leq 30,1 \leq h_{1}<h_{2}<\cdots<h_{n-1} \leq$ $100000,1 \leq w_{1}<w_{2}<\cdots<w_{m-1} \leq 100000,1 \leq g_{i j} \leq 1000,1 \leq r_{i j} \leq 1000$, 给定的路口一定合法。 


---

---
title: "『GROI-R1』 继续深潜，为了同一个梦想"
layout: "post"
diff: 提高+/省选-
pid: P8973
tag: ['动态规划 DP', '数学', '图论', '线段树', '点分治', 'O2优化', '树形 DP']
---
# 『GROI-R1』 继续深潜，为了同一个梦想
## 题目背景

玘正在折叠床脚几件刚洗净的白衬衫，他注意到身后的声响，向右后转头看去。

以为是“外面的家伙”的他并没有刻意去遮掩自己的右眼——毕竟学院里的人不可能进来。

他看见了那个紫眸的少年；当然寒也看见了那一瞬间的鲜红。

「你什么都没看见。」

玘装作欣赏窗外的晚霞。
## 题目描述

「世上没有无价的情报，」玘露出一丝满意的微笑。

「你懂我的意思吧？」

寒收回手。

玘给出了他留给寒的题。

> 既然紫堇和彼岸花给予了我们异色的瞳孔，我们理所应当是连接在一起的。我称**一棵树上的一个点集是“连接的”**，当且仅当**树上存在一条链能够覆盖这个点集并且这个集合大小不小于 $2$**。我们是独一无二的，可是你知道，一棵树，总是连起来的啊。

「然后呢？」

「现在，你需要告诉我每个点被多少个这样的点集所包含。」


玘飘然而去。

湖底之城那封存已久的记忆，被彼岸花和紫堇的力量，揭开了封印的一角。
## 输入格式

第一行一个正整数 $n$ 表示这棵树有 $n$ 个点编号为 $1\sim n$。

接下来 $n-1$ 行，每行两个正整数 $u,v$ 描述一条边。
## 输出格式

为了防止输出量过大，本题采用以下的输出方式。

设 $ans_i$ 为包含 $i$ 号节点的连接的集合的个数对 $10^9+7$ 取模得到的值，你需要输出 $\operatorname{xor}_{i=1}^n ans_i\times i$ 的值。注意这里没有取模运算。
## 样例

### 样例输入 #1
```
4
1 2
2 3
2 4
```
### 样例输出 #1
```
18
```
## 提示

**样例解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/rl9wkbww.png)

**连接**的集合有以下一些：
- $\{1,2\}$
- $\{1,3\}$
- $\{1,4\}$
- $\{2,3\}$
- $\{2,4\}$
- $\{3,4\}$
- $\{1,2,3\}$
- $\{1,2,4\}$
- $\{2,3,4\}$

如 $\{1,3,4\}$ 就不是一个连接的集合，因为你找不出一条链使得 $\{1,3,4\}$ 为它的子集。

其中 $1,2,3,4$ 号节点分别在 $5,6,5,5$ 个集合中出现。通过计算可得 $\operatorname{xor}_{i=1}^n ans_i\times i=18$。

**数据范围**

**本题采用捆绑测试。**

| 子任务编号 | 数据范围 | 特殊性质 | 分值 | 时间限制 |
| :----------: | :----------: | :----------: | :----------: | :-: |
| $\text{Subtask1}$ | $n\le20$ | | $15$ | $\text{1s}$ |
| $\text{Subtask2}$ | $n\le100$ | | $15$  | $\text{1s}$ |
| $\text{Subtask3}$ | $n\le3\times 10^3$ | | $20$ | $\text{1s}$ |
| $\text{Subtask4}$ | $n\le5\times10^5$ | $\text{A}$ | $15$ | $\text{2s}$ |
| $\text{Subtask5}$ | $n\le5\times10^5$ | | $35$ | $\text{2s}$ |

特殊性质 $\text{A}$：保证树退化成一条链。


对于 $100\%$ 的数据 $1\le u,v\le n\le5\times10^5$。


---

---
title: "「SvR-2」1+2=3"
layout: "post"
diff: 提高+/省选-
pid: P9088
tag: ['贪心', '2023', '网络流', '洛谷原创', 'O2优化', '图论建模', '欧拉回路', '费用流', '洛谷月赛', 'Ad-hoc']
---
# 「SvR-2」1+2=3
## 题目描述

你有一些木棒，每个木棒左边有一个数，右边有一个数，数只有 $0,1,2$，你要将所有木棒拼起来，使相邻的数和为 $3$ 的对数最大。

例如，$1\text{ - }2$ 和 $1\text{ - }0$ 两个木棒，如果按 $1\text{ - }0,1\text{ - }2$ 这样拼，相邻的数和为 $3$ 的对数是 $0$；而按 $1\text{ - }{\underline\color{red}\textbf2},{\underline\color{red}\textbf1}\text{ - }0$ 这样拼相邻的数和为 $3$ 的对数是 $1$，因为 $2+1=3$。
## 输入格式

**本题有多组数据。**

输入的第一行一个正整数表示数据组数 $T$。

对于每组数据，一行 $9$ 个非负整数，分别表示 $0\text{ - }0,0\text{ - }1,0\text{ - }2,1\text{ - }0,1\text{ - }1,1\text{ - }2,2\text{ - }0,2\text{ - }1,2\text{ - }2$ 型木棒的个数。
## 输出格式

$T$ 行，每行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
4 1 3 4 7 7 9 10 3
6 3 6 4 3 4 5 6 6
6 10 7 1 4 2 6 4 2

```
### 样例输出 #1
```
31
23
19

```
## 提示

#### 数据规模与约定

对于全部数据，保证 $1\le T\le 10^5$，记 $a_{i,j}$ 表示 $i\text-j$ 木棒的个数，保证 $0\le a_{i,j}\le 10^9$。

**本题自动开启捆绑测试和 O2 优化。**

记 $sum$ 表示一个测试点中所有数据的所有 $a_{i,j}$ 之和。

| Subtask | $T$ | $sum$ | 特殊性质 |分值 |
| :------: | :------: | :------: | :------: | :------: |
| $1$ | $1 \leq T \leq 10$ | $1\le sum\le 10$ |无| $10 \operatorname{pts}$ |
| $2$ | $1 \leq T \leq 50$ | $1\le sum\le 80$ | 无|$20 \operatorname{pts}$ |
| $3$ | 无特殊限制 | 无特殊限制 |A| $15\operatorname{pts}$ |
| $4$ | 无特殊限制 | 无特殊限制 |B| $20 \operatorname{pts}$ |
| $5$ | $1\le T\le 1000$ | 无特殊限制 |C| $20 \operatorname{pts}$ |
| $6$ | 无特殊限制 | 无特殊限制 |无| $15 \operatorname{pts}$ |

特殊性质 A：$a_{i,j}$ 在 $[0,10^9]$ 中均匀随机生成。

特殊性质 B：所有 $a_{i,j}>0$。

特殊性质 C：所有 $a_{i,j}\le 100$。


---

---
title: "[USACO23OPEN] Custodial Cleanup G"
layout: "post"
diff: 提高+/省选-
pid: P9189
tag: ['搜索', '图论', 'USACO', '2023']
---
# [USACO23OPEN] Custodial Cleanup G
## 题目描述

Due to the disorganized structure of his mootels (much like motels but with
bovine rather than human guests), Farmer John has decided to take up the role of
the mootel custodian to restore order to the stalls.

Each mootel has $N$ stalls labeled $1$ through $N$ and $M$ corridors that connect pairs of stalls to each other
bidirectionally. The $i$ th stall is painted with color $C_i$ and initially has a
single key of color $S_i$ in it. FJ will have to rearrange the keys to appease
the cows and restore order to the stalls.

FJ starts out in stall $1$ without holding any keys and is allowed to repeatedly
do one of the following moves:
- Pick up a key in the stall he is currently in. FJ can hold multiple keys at
a time.
- Place down a key he is holding into the stall he is currently
in. A stall may hold multiple keys at a time.
- Enter stall $1$ by
moving through a corridor.
- Enter a stall other than stall $1$ by
moving through a corridor. He can only do this if he currently holds a key that
is the same color as the stall he is entering.

Unfortunately, it seems that the keys are not in their intended locations. To
restore order to FJ's mootel, the $i$th stall requires that a single key of
color $F_i$ is in it. It is guaranteed that $S$ is a permutation of $F$.

For $T$ different mootels, FJ starts in stall $1$ and needs
to place every key in its appropriate location, ending back in stall $1$. For
each of the $T$ mootels, please answer if it is possible to do this.
## 输入格式

The first line contains $T$, the number of mootels (test cases).

Each test case will be preceded by a blank line. Then, the first line 
of each test case contains two integers $N$ and $M$.

The second line of each test case contains $N$ integers. The $i$-th integer on
this line $C_i$ means that stall $i$ has color $C_i$.

The third line of each test case contains $N$ integers. The $i$-th integer on
this line $S_i$ means that stall $i$ initially holds a key of color $S_i$.

The fourth line of each test case contains $N$ integers. The $i$-th integer on
this line $F_i$ means that stall $i$ needs to have a key of color $F_i$ in it.

The next $M$ lines of each test case follow. The $i$-th of these lines contains
two distinct integers $u_i$ and $v_i$. This represents
that a corridor exists between stalls $u_i$ and $v_i$. No corridors are
repeated.

## 输出格式

For each mootel, output `YES` on a new line if there exists a way for FJ to return
a key of color $F_i$ to each stall $i$ and end back in stall $1$. Otherwise,
output `NO` on a new line.
## 样例

### 样例输入 #1
```
2

5 5
4 3 2 4 3
3 4 3 4 2
2 3 4 4 3
1 2
2 3
3 1
4 1
4 5

4 3
3 2 4 1
2 3 4 4
4 2 3 4
4 2
4 1
4 3

```
### 样例输出 #1
```
YES
NO

```
### 样例输入 #2
```
5

2 0
1 2
2 2
2 2

2 1
1 1
2 1
2 1
1 2

2 1
1 1
2 1
1 2
1 2

2 1
1 1
1 2
2 1
1 2

5 4
1 2 3 4 4
2 3 5 4 2
5 3 2 4 2
1 2
1 3
1 4
4 5

```
### 样例输出 #2
```
YES
YES
NO
YES
NO

```
## 提示

For the first test case of the first sample, here is a possible sequence of moves:

```
Current stall: 1. Keys held: []. Keys in stalls: [3, 4, 3, 4, 2]
(pick up key of color 3)
Current stall: 1. Keys held: [3]. Keys in stalls: [x, 4, 3, 4, 2]
(move from stall 1 to 2, allowed since we have a key of color C_2=3)
Current stall: 2. Keys held: [3]. Keys in stalls: [x, 4, 3, 4, 2]
(pick up key of color 4)
Current stall: 2. Keys held: [3, 4]. Keys in stalls: [x, x, 3, 4, 2]
(move from stall 2 to 1 to 4 to 5, allowed since we have keys of colors C_4=4 and C_5=3)
Current stall: 5. Keys held: [3, 4]. Keys in stalls: [x, x, 3, 4, 2]
(pick up key of color 2 and place key of color 3)
Current stall: 5. Keys held: [2, 4]. Keys in stalls: [x, x, 3, 4, 3]
(move from stall 5 to 4 to 1 to 3, allowed since we have keys of colors C_4=4 and C_3=2)
Current stall: 3. Keys held: [2, 4]. Keys in stalls: [x, x, 3, 4, 3]
(pick up key of color 3 and place key of color 4)
Current stall: 3. Keys held: [2, 3]. Keys in stalls: [x, x, 4, 4, 3]
(move from stall 3 to stall 2 and place key of color 3)
Current stall: 2. Keys held: [2]. Keys in stalls: [x, 3, 4, 4, 3]
(move from stall 2 to stall 1 and place key of color 2)
Current stall: 1. Keys held: []. Keys in stalls: [2, 3, 4, 4, 3]
```

For the second test case of the first sample, there exists no way for FJ to return a key of color
$F_i$ to each stall $i$ and end back at stall $1$.

$0 \le M \le 10^5$, $1 \le C_i, S_i, F_i, u_i, v_i \le N \le 10^5$.   
$1 \le T \le 100$, $1 \le \sum N \le 10^5$, $1 \le \sum M \le 2\cdot 10^5$.

- Test cases 3-6 satisfy $N,M\le 8$.
- Test cases 7-10 satisfy $C_i=F_i$.
- Test cases 11-18 satisfy no additional constraints.

## 题目翻译

### 题目描述

由于他的 mootels（类似于汽车旅馆，但住客是牛而不是人）结构混乱，农夫 John 决定担任 mootel 的管理员，以恢复牛栏的秩序。

每个 mootel 有 $N$ 个牛栏，编号为 $1$ 到 $N$，以及 $M$ 条双向连接的走廊。第 $i$ 个牛栏被涂成颜色 $C_i$，并且最初里面有一把颜色为 $S_i$ 的钥匙。FJ 需要重新安排钥匙的位置，以安抚奶牛并恢复牛栏的秩序。

FJ 从牛栏 $1$ 开始，手中没有任何钥匙，并且可以重复执行以下操作之一：
- 拾取当前所在牛栏中的一把钥匙。FJ 可以同时持有多个钥匙。
- 将手中持有的一把钥匙放入当前所在的牛栏。一个牛栏可以同时存放多把钥匙。
- 通过走廊进入牛栏 $1$。
- 通过走廊进入牛栏 $1$ 以外的其他牛栏。只有当 FJ 当前持有的钥匙颜色与目标牛栏的颜色相同时，才能执行此操作。

不幸的是，钥匙似乎并未放在它们应有的位置。为了恢复 FJ 的 mootel 的秩序，第 $i$ 个牛栏需要有一把颜色为 $F_i$ 的钥匙。保证 $S$ 是 $F$ 的一个排列。

对于 $T$ 个不同的 mootel，FJ 从牛栏 $1$ 开始，需要将每把钥匙放到其应有的位置，并最终回到牛栏 $1$。对于每个 mootel，请回答是否可能完成这一任务。

### 输入格式

第一行包含 $T$，表示 mootel 的数量（测试用例的数量）。

每个测试用例前有一个空行。然后，每个测试用例的第一行包含两个整数 $N$ 和 $M$。

每个测试用例的第二行包含 $N$ 个整数。第 $i$ 个整数 $C_i$ 表示牛栏 $i$ 的颜色为 $C_i$。

每个测试用例的第三行包含 $N$ 个整数。第 $i$ 个整数 $S_i$ 表示牛栏 $i$ 最初有一把颜色为 $S_i$ 的钥匙。

每个测试用例的第四行包含 $N$ 个整数。第 $i$ 个整数 $F_i$ 表示牛栏 $i$ 需要有一把颜色为 $F_i$ 的钥匙。

每个测试用例接下来的 $M$ 行，每行包含两个不同的整数 $u_i$ 和 $v_i$。这表示牛栏 $u_i$ 和 $v_i$ 之间有一条走廊。没有重复的走廊。

### 提示

对于第一个样例的第一个测试样例，以下是一种可能的操作序列。

```
当前牛栏：1。持有的钥匙：[]。牛栏中的钥匙：[3, 4, 3, 4, 2] （拾取颜色为 3 的钥匙）
当前牛栏：1。持有的钥匙：[3]。牛栏中的钥匙：[x, 4, 3, 4, 2] （从牛栏 1 移动到牛栏 2，允许，因为持有颜色为 C_2=3 的钥匙）
当前牛栏：2。持有的钥匙：[3]。牛栏中的钥匙：[x, 4, 3, 4, 2] （拾取颜色为 4 的钥匙）
当前牛栏：2。持有的钥匙：[3, 4]。牛栏中的钥匙：[x, x, 3, 4, 2] （从牛栏 2 移动到牛栏 1 到牛栏 4 到牛栏 5，允许，因为持有颜色为 C_4=4 和 C_5=3 的钥匙）
当前牛栏：5。持有的钥匙：[3, 4]。牛栏中的钥匙：[x, x, 3, 4, 2] （拾取颜色为 2 的钥匙并放下颜色为 3 的钥匙）
当前牛栏：5。持有的钥匙：[2, 4]。牛栏中的钥匙：[x, x, 3, 4, 3] （从牛栏 5 移动到牛栏 4 到牛栏 1 到牛栏 3，允许，因为持有颜色为 C_4=4 和 C_3=2 的钥匙）
当前牛栏：3。持有的钥匙：[2, 4]。牛栏中的钥匙：[x, x, 3, 4, 3] （拾取颜色为 3 的钥匙并放下颜色为 4 的钥匙）
当前牛栏：3。持有的钥匙：[2, 3]。牛栏中的钥匙：[x, x, 4, 4, 3] （从牛栏 3 移动到牛栏 2 并放下颜色为 3 的钥匙）
当前牛栏：2。持有的钥匙：[2]。牛栏中的钥匙：[x, 3, 4, 4, 3] （从牛栏 2 移动到牛栏 1 并放下颜色为 2 的钥匙）
当前牛栏：1。持有的钥匙：[]。牛栏中的钥匙：[2, 3, 4, 4, 3]
```

对于第一个样例的第二个测试用例，不存在一种方式让 FJ 将颜色为 $F_i$ 的钥匙放回每个牛栏 $i$ 并最终回到牛栏 $1$。

$0 \le M \le 10^5$，$1 \le C_i, S_i, F_i, u_i, v_i \le N \le 10^5$。  
$1 \le T \le 100$，$1 \le \sum N \le 10^5$，$1 \le \sum M \le 2 \cdot 10^5$。

- 测试用例 3-6 满足 $N, M \le 8$。
- 测试用例 7-10 满足 $C_i = F_i$。
- 测试用例 11-18 没有额外限制。


---

---
title: "[蓝桥杯 2023 省 A] 网络稳定性"
layout: "post"
diff: 提高+/省选-
pid: P9235
tag: ['图论', '贪心', '并查集', '2023', '生成树', '最近公共祖先 LCA', '蓝桥杯省赛']
---
# [蓝桥杯 2023 省 A] 网络稳定性
## 题目描述

有一个局域网，由 $n$ 个设备和 $m$ 条物理连接组成，第 $i$ 条连接的稳定性为 $w_i$。

对于从设备 $A$ 到设备 $B$ 的一条经过了若干个物理连接的路径，我们记这条路径的稳定性为其经过所有连接中稳定性最低的那个。

我们记设备 $A$ 到设备 $B$ 之间通信的稳定性为 $A$ 至 $B$ 的所有可行路径的稳定性中最高的那一条。

给定局域网中的设备的物理连接情况，求出若干组设备 $x_i$ 和 $y_i$ 之间的通信稳定性。如果两台设备之间不存在任何路径，请输出 $-1$。
## 输入格式

输入的第一行包含三个整数 $n,m,q$，分别表示设备数、物理连接数和询问数。

接下来 $m$ 行，每行包含三个整数 $u_i,v_i,w_i$，分别表示 $u_i$ 和 $v_i$ 之间有一条稳定性为 $w_i$ 的物理连接。

接下来 $q$ 行，每行包含两个整数 $x_i,y_i$，表示查询 $x_i$ 和 $y_i$ 之间的通信稳定性。
## 输出格式

输出 $q$ 行，每行包含一个整数依次表示每个询问的答案。
## 样例

### 样例输入 #1
```
5 4 3
1 2 5
2 3 6
3 4 1
1 4 3
1 5
2 4
1 3
```
### 样例输出 #1
```
-1
3
5
```
## 提示

【评测用例规模与约定】

对于 $30 \%$ 的评测用例，$n,q \leq 500$，$m \leq 1000$；

对于 $60 \%$ 的评测用例，$n,q \leq 5000$，$m \leq 10000$；

对于所有评测用例，$2 \leq n,q \leq 10^5$，$1 \leq m \leq 3 \times 10^5$，$1 \leq u_i,v_i,x_i,y_i \leq n$，$
1 \leq w_i \leq 10^6$，$u_i \neq v_i$，$x_i \neq y_i$。


---

---
title: "「DROI」Round 2 单图"
layout: "post"
diff: 提高+/省选-
pid: P9374
tag: ['图论', 'O2优化', '组合数学']
---
# 「DROI」Round 2 单图
## 题目背景

与其编写苍白无力的背景，不如出更有质量的题。
## 题目描述

我们称[简单有向图](https://www.luogu.com.cn/paste/4oz6fep2) $G,H$ **本质相同**，当且仅当：

- 对于任意点对 $(u,v)$，若在图 $G$ 中从 $u$ 出发能走到 $v$，则在图 $H$ 中从 $u$ 出发能走到 $v$。反之若在图 $H$ 中从 $u$ 出发能走到 $v$，则在图 $G$ 中从 $u$ 出发也能走到 $v$。

若对于简单有向图 $G$，不存在其他简单有向图 $H$ 与其本质相同，则我们称图 $G$ 为 **单图**。

$T$ 次询问，每次询问给定一个正整数 $n$，请你回答 $n$ 个点的**有标号**单图数。
## 输入格式

**本题采用多组输入。**

第一行输入两个整数 $T,mod$，表示数据组数与模数。

接下来 $T$ 行每行一个整数，表示这组数据的 $n$。
## 输出格式

输出 $T$ 行，第 $i$ 行表示第 $i$ 组数据的答案对 $mod$ 取模的值。
## 样例

### 样例输入 #1
```
5 998244353
1
3
5
12
888
```
### 样例输出 #1
```
1
16
986
328006912
535268381
```
## 提示

#### 数据范围

**「本题采用捆绑测试」** 

- $\operatorname{Subtask} 1(30\%)$：$T = 1$，$n \leq 5$。

- $\operatorname{Subtask} 2(50\%)$：$T \leq 10$。

- $\operatorname{Subtask} 3(20\%)$：无特殊限制。

对于 $100\%$ 的数据满足：$1 \leq T,n \leq 1000$，$1\leq mod \leq 10^9$。


#### 说明提示

这里给出一些例子来帮助理解单图的含义：

------------

![](https://cdn.luogu.com.cn/upload/image_hosting/kykl8fg8.png)[](https://www.luogu.com.cn/paste/0tbbkesd)

这是一张单图，可以证明不存在其他图与其本质相同。

------------

![](https://cdn.luogu.com.cn/upload/image_hosting/5appj8pr.png)

这不是一张单图，因为我们可以添加边 $(5,2)$ 构造出与其本质相同的图。

------------

![](https://cdn.luogu.com.cn/upload/image_hosting/wtsep329.png)

这不是一张单图，因为我们可以删去边 $(1,3)$ 构造出与其本质相同的图。




---

---
title: "[POI 2020/2021 R3] Droga do domu"
layout: "post"
diff: 提高+/省选-
pid: P9402
tag: ['图论', '2020', 'POI（波兰）', '图论建模', '最短路']
---
# [POI 2020/2021 R3] Droga do domu
## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Droga do domu](https://szkopul.edu.pl/problemset/problem/ZfS_tobZ_7xdR6D5s6Tegur3/statement/)。

d1t1。
## 题目描述

$n$ 个点，$m$ 条边，无重边自环，边有长度。

$1$ 号点是学校，$n$ 号点是家。

$s$ 条公交线路。公交逢点必停，且一个点不会停两次。在一条边上行驶的时间就是它的长度。给定了第一班公交发车时间和发车间隔。

在时刻 $t$ 从学校出发，至多换乘 $k$ 次，求最早什么时候到家。

只计算路上时间和等车时间。换乘时间不计。
## 输入格式

第一行：五个整数 $n,m,s,k,t$。

接下来 $m$ 行：每行三个整数 $a,b,c$，表示有一条边连接 $a,b$，长度为 $c$。

接下来 $2s$ 行：每两行描述一条公交线路：

- 第一行三个整数 $l,x,y$，表示它共停靠 $l$ 个点，第一班在时刻 $x$ 发车，每两班之间时间间隔为 $y$。
- 第二行 $l$ 个整数 $v_1,\dots,v_l$，依次为它停靠的 $l$ 个点。
## 输出格式

一行一个整数，答案。

如果不能到家，那么输出一行一个字符串 `NIE`。
## 样例

### 样例输入 #1
```
4 4 2 1 1
1 2 2
2 3 4
1 3 3
4 3 2
4 0 10
1 2 3 4
3 2 7
1 3 2

```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
10 45 17 10 123
1 2 1
1 3 100
1 4 100
1 5 100
1 6 100
1 7 100
1 8 100
1 9 100
1 10 100
2 3 1
2 4 100
2 5 100
2 6 100
2 7 100
2 8 100
2 9 100
2 10 100
3 4 1
3 5 100
3 6 100
3 7 100
3 8 100
3 9 100
3 10 100
4 5 1
4 6 100
4 7 100
4 8 100
4 9 100
4 10 100
5 6 1
5 7 100
5 8 100
5 9 100
5 10 100
6 7 1
6 8 100
6 9 100
6 10 100
7 8 1
7 9 100
7 10 100
8 9 1
8 10 100
9 10 1
2 0 1
1 2
2 0 1
1 3
2 0 1
2 3
2 0 1
2 4
2 0 1
3 4
2 0 1
3 5
2 0 1
4 5
2 0 1
4 6
2 0 1
5 6
2 0 1
5 7
2 0 1
6 7
2 0 1
6 8
2 0 1
7 8
2 0 1
7 9
2 0 1
8 9
2 0 1
8 10
2 0 1
9 10

```
### 样例输出 #2
```
132
```
### 样例输入 #3
```
见附件
```
### 样例输出 #3
```
1000000102
```
### 样例输入 #4
```
见附件
```
### 样例输出 #4
```
11100000071
```
## 提示

样例解释：![](https://cdn.luogu.com.cn/upload/image_hosting/9njsvc34.png)

对于全部数据，$2\leq n\leq 10000$，$1\leq m\leq 50000$，$1\leq s\leq 25000$，$0\leq k\leq 100$，$0\leq t\leq 10^9$，$1\leq c\leq 10^9$，$2\leq l\leq n$，$0\leq x\leq 10^9$，$1\leq y\leq 10^9$，$1\leq a,b,v\leq n$，$\sum l\leq 50000$。

| 子任务编号 | 限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $k=n$ | 20 |
| 2 | $v_i<v_{i+1}$ | 20 |
| 3 | $l=2$ | 20 |
| 4 | $t=0,x=0,y=1$ | 20 |
| 5 |  | 20 |



---

---
title: "「TFOI R1」Unknown Graph"
layout: "post"
diff: 提高+/省选-
pid: P9705
tag: ['网络流', 'Special Judge', 'O2优化', '图论建模']
---
# 「TFOI R1」Unknown Graph
## 题目背景

小 A 飘到了一个岛屿群里，这些岛屿都有单向桥相连接，没有两座桥连接的起始岛屿和终止岛屿都相同，更不会有桥连接一个岛屿。

但这里全是迷雾，小 A 在一个岛上只能看到这个岛与多少座桥相连。

小 A 想要知道整个岛屿群的形态，但是他并不会，所以找到了你。

如果有多种情况，你只需要告诉小 A 任意一种就行。
## 题目描述

有一张 $n$ 个节点的**无重边无自环的有向图**（可以不连通），每个节点的编号为 $1 \sim n$，你知道每个节点的入度和出度。

另外还有 $m$ 条限制，每条限制给定两个点 $x_{i}$ 和 $y_{i}$，表示图中不存在有向边 $(x_{i}, y_{i})$，请你求出一种满足要求的图的形态。

若有多种情况，输出任意一种即可，保证有解。
## 输入格式

第一行一个正整数 $n$ 表示节点数量。

第二行 $n$ 个整数 $a_{i}$，表示编号为 $i$ 的节点的入度为 $a_{i}$。

第三行 $n$ 个整数 $b_{i}$，表示编号为 $i$ 的节点的出度为 $b_{i}$。

第四行一个整数 $m$，表示限制个数。

对于接下来的 $m$ 行，每行两个正整数 $x_{i}, y_{i}$ 表示一组限制。
## 输出格式

第一行一个正整数 $k$ 表示满足限制的图有多少条边。

接下来 $k$ 行，每行两个正整数 $u_{i}$ 和 $v_{i}$ 表示编号为 $u_{i}$ 的结点和编号为 $v_{i}$ 的结点之间有一条有向边。
## 样例

### 样例输入 #1
```
4
2 3 2 3
2 3 2 3
1
1 3
```
### 样例输出 #1
```
10
1 2
2 1
2 3
3 2
2 4
4 2
4 1
1 4
4 3
3 4
```
## 提示

**本题采用捆绑测试**。

- Subtask 1（10 points）：$n \leqslant 10$。
- Subtask 2（10 points）：$n = 10^3$，$a_{i} = b_{i} = 1$，$m = 0$。
- Subtask 3（20 points）：$n \leqslant 100$。
- Subtask 4（60 points）：无特殊限制。

对于所有数据，$2 \leqslant n \leqslant 10^{3}$，$0 \leqslant a_{i}, b_{i} < n$，$1\leqslant \sum{a_i} \leqslant 10^{5}$，$0 \leqslant m \leqslant 5 \times 10^4$，$1 \leqslant x_i,y_i \leqslant n$。


---

---
title: "[POI 2023/2024 R1] Przyciski"
layout: "post"
diff: 提高+/省选-
pid: P9923
tag: ['图论', 'POI（波兰）', '2023', 'Special Judge', '构造']
---
# [POI 2023/2024 R1] Przyciski
## 题目背景

译自 [XXXI Olimpiada Informatyczna - I etap](https://sio2.mimuw.edu.pl/c/oi31-1/dashboard/) [Przyciski](https://sio2.mimuw.edu.pl/c/oi31-1/p/prz/)。
## 题目描述

一个 $n\times n$ 的方阵，里面有 $m$ 个按钮。

你需要按下若干个（至少一个）按钮，使得每行每列被按下的按钮个数奇偶性相同。
## 输入格式

第一行两个正整数 $n,m$。

接下来 $m$ 行，每行两个正整数，表示一个按钮的坐标。
## 输出格式

如果无解，输出一行 `NIE`。

如果有解，第一行输出 `TAK`，第二行输出一个正整数 $k$，表示按下按钮的个数，第三行输出若干个正整数，表示你按下的按钮的编号。
## 样例

### 样例输入 #1
```
3 6
1 1
1 2
2 2
3 1
3 2
3 3

```
### 样例输出 #1
```
TAK
4
1 2 4 5

```
### 样例输入 #2
```
9 1
1 1

```
### 样例输出 #2
```
NIE

```
### 样例输入 #3
```
见附件
```
### 样例输出 #3
```
TAK
4
1 2 10 11

```
### 样例输入 #4
```
见附件
```
### 样例输出 #4
```
TAK
4
1 2 100001 100002

```
## 提示

样例一解释：$R_1=2,R_2=0,R_3=2,C_1=C_2=2,C_3=0$。

对于所有的数据，$1\leq n\leq 100000$，$1\leq m\leq\min(n^2,500000)$。

| 子任务编号 | 附加限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $m\leq 20$ | 24 |
| 2 | 如果有解，保证存在偶数解 | 24 |
| 3 | 如果有解，保证存在奇数解 | 24 |
| 4 |  | 28 |

如果有解并且你指出有解但是构造错误，你能得到 $50\%$ 的分数。


---

