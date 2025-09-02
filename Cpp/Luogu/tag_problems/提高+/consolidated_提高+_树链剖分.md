---
title: "BZOJ3252 攻略"
layout: "post"
diff: 提高+/省选-
pid: P10641
tag: ['贪心', '线段树', 'O2优化', '可并堆', '树链剖分']
---
# BZOJ3252 攻略
## 题目背景

众所周知，桂木桂马是攻略之神，开启攻略之神模式后，他可以同时攻略 $k$ 部游戏。

今天他得到了一款新游戏《XX 半岛》，这款游戏有 $n$ 个场景，某些场景可以通过不同的选择支到达其他场景。所有场景和选择支构成树状结构：开始游戏时在根节点（共通线），叶子节点为结局。每个场景有一个价值，现在桂马开启攻略之神模式，同时攻略 $k$ 次该游戏，问他观赏到的场景的价值和最大是多少？（同一场景观看多次是不能重复得到价值的）

>“为什么你还没玩就知道每个场景的价值呢？”  
>“我已经看到结局了。”
## 题目描述

给定一个有 $n$ 个结点的树，树有点权且点权为正整数。现选取 $k$ 条从根结点出发到叶子结点的简单路径，求这些路径的并集上所有结点的点权之和的最大值。
## 输入格式

第一行两个正整数 $n,k$。

第二行输入 $n$ 个正整数 $w_i$，表示每个结点的点权。

第三行输入 $n-1$ 行，每行 $2$ 个正整数 $u,v$，表示结点 $u$ 是结点 $v$ 的父亲。
## 输出格式

输出一个正整数，表示答案。
## 样例

### 样例输入 #1
```
5 2
4 3 2 1 1
1 2
1 5
2 3
2 4
```
### 样例输出 #1
```
10
```
## 提示

对于所有数据，保证 $1\leq n\leq 2\times 10^5$，$1\leq w_i\leq 2^{31}-1$。


---

---
title: "「CZOI-R1」三角形与树"
layout: "post"
diff: 提高+/省选-
pid: P10799
tag: ['数学', '倍增', '树状数组', 'O2优化', '最近公共祖先 LCA', '树链剖分']
---
# 「CZOI-R1」三角形与树
## 题目背景

CaiZi 讨厌三角形，但是他喜欢树。

2024.8.15 Update：增加了一组 hack 数据。
## 题目描述

给定一颗有 $n$ 个点的树，节点编号为 $1\sim n$，每个点有点权，开始时点 $i$ 的点权为 $a_i$。共有 $q$ 次操作。
1. 将点 $x$ 到点 $y$ 的简单路径上的点的点权**异或** $k$。
1. 判断能否在点 $x$ 到点 $y$ 的简单路径上选 $3$ 个**不同点**，并以这 $3$ 个点的点权为边长构成**三角形**。特别的，如果无法选出 $3$ 个点，也视为不能构成**三角形**。

点 $x$ 到点 $y$ 的简单路径：点 $x$ 到点 $y$ 不重复走过任何一条边的路径。其上的所有点为这条路径上所有的点，**包括**点 $x$ 和点 $y$。

**保证任何时刻不会有任何一个点的点权为 $0$。**
## 输入格式

第一行输入 $2$ 个整数 $n,q$，分别表示这棵树点的个数、操作的个数。

第二行输入 $n$ 个整数 $a_i$，表示开始时点 $i$ 的点权。

接下来 $n-1$ 行，每行输入 $2$ 个整数 $u,v$，表示这棵树的一条边。

接下来 $q$ 行，每行先输入 $1$ 个整数 $s$，表示操作类型。
- 若 $s=1$，则再输入 $3$ 个整数 $u,v,w$，表示一次修改操作。
- 若 $s=2$，则再输入 $2$ 个整数 $u,v$，表示一次询问操作。
## 输出格式

对于每次询问操作，若能满足条件输出 $1$，否则输出 $0$，无需空格或换行。
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 2
1 3
2 4
2 5
2 1 2
2 3 4
1 3 5 4
2 2 3
2 1 5
```
### 样例输出 #1
```
0110
```
## 提示

**【样例解释】**

第 $1$ 次操作时简单路径上的点权少于 $3$ 个。  
第 $2$ 次操作时简单路径上的点权分别为 $1,2,3,4$。  
第 $3$ 次操作后点 $1\sim n$ 的点权分别为 $5,6,7,4,1$。  
第 $4$ 次操作时简单路径上的点权分别为 $5,6,7$。  
第 $5$ 次操作时简单路径上的点权分别为 $1,5,6$。

**【数据范围】**

**本题采用捆绑测试**。
- Subtask #1（$8\text{ pts}$）：$n,q\le3\times10^3$。
- Subtask #2（$8\text{ pts}$）：保证这棵树是一朵菊花。
- Subtask #3（$20\text{ pts}$）：每次修改操作时 $x=y$。
- Subtask #4（$24\text{ pts}$）：保证这棵树是一条链。
- Subtask #5（$40\text{ pts}$）：无特殊性质。**依赖 Subtask #1 到 Subtask #4。**

对于 $100\%$ 的数据，$1\le u,v\le n\le10^5$，$1\le q\le10^5$，$s\in\{1,2\}$，$1\le a_i,w\le 2^{31}-1$。


---

---
title: "DerrickLo's City (UBC002C)"
layout: "post"
diff: 提高+/省选-
pid: P12180
tag: ['线段树', 'O2优化', '树链剖分']
---
# DerrickLo's City (UBC002C)
## 题目背景

DerrickLo 看到了一个 $n \le 7.5 \times 10^5$ 的题，并且发现很多人写了 $O(n^2)$ 过了。于是他想写 $O(n\log^3n)$，但是挂了。于是将原题的序列改成了树。

注：以上故事是将出题人的名字换成 DerrickLo 得到的。

---

The English statement is provided [here](https://www.luogu.com.cn/problem/U538685). **You must submit your solution only in the Chinese version.**

## 题目描述

DerrickLo 在游戏中掌控着一个城市。这个城市内的团体间并不是非常的和谐，因此需要通过开会来增进关系。

已知这个组织所在的城市被分为了 $n$ 个镇，每一个镇上恰好有一个团体。其中编号为 $1$ 的镇上分布着团体 $1$，$2$ 号镇上有团体 $2$，等等。这 $n$ 个镇通过 $n-1$ 条路径相连，两两可以互相到达。

每次开会，DerrickLo 会指定一个区间 $[l, r]$，邀请编号在 $[l, r]$ 之间的团体来开会。由于团体比较分散，因此他还需要指定一个开会地址 $p$。因为团体的关系比较僵硬，所以前往开会的团体去 $p$ 的途中，不能到达别的与会团体所在的镇。

由于 DerrickLo 刚接触这个游戏，操作不太熟悉，确定 $p$ 的任务就交给你了。

## 输入格式

第一行两个正整数 $n, q$，表示镇的数量，会议个数。

接下来 $n-1$ 行，每行两个正整数 $a_i, b_i$，表示 $a_i$ 镇 和 $b_i$ 镇之间有道路直接相连。

接下来 $q$ 行，每行两个整数 $l_i, r_i$，表示此次由编号在 $[l_i, r_i]$ 之间的团体与会。

## 输出格式

对于每一个会议，单独输出一行。如果能够选出这个地点，则输出 `Yes`，否则输出 `No`。

## 样例

### 样例输入 #1
```
6 2
1 2
1 3
2 4
2 5
1 6
3 5
2 4

```
### 样例输出 #1
```
Yes
No

```
## 提示

对于第一个会议，$1, 2, 6$ 镇均可作为参会点。

对于第二个会议，无论选哪里作为参会点，$2, 4$ 两团体均会有一方经过另一镇。

### 数据范围

$1 \le n, q \le 10^5$。

保证道路 $(a_i, b_i)$ 使得任意两镇可互相到达。

$1 \le l_i \le r_i \le n$。



---

---
title: "[eJOI 2024] 糖果售卖 / Sweets"
layout: "post"
diff: 提高+/省选-
pid: P12361
tag: ['线段树', '2024', 'eJOI（欧洲）', '树链剖分']
---
# [eJOI 2024] 糖果售卖 / Sweets
## 题目背景

Sandu 高中毕业后成为了一名糖果商人！


## 题目描述

在一座城市中有 $N$ 个市场，还有 $N-1$ 条道路连接他们。这些市场和道路构成了一个树形结构。每一天开始时，Sandu 都会来到 $1$ 号市场，开始售卖糖果。

每个市场都有技能值和困难度。当你来到这个市场时，你的技能值会增加这个市场的技能值；然后，如果你的技能值大于等于这个市场的困难度，你就可以成功售卖糖果。初始时，每座市场的技能值都是 $0$。

由于这座城市十分繁忙，所以在接下来的 $Q$ 天中，每一天都会发生一次事件，用 $u_j$ 和 $x_j$ 来描述，表示第 $u_j$ 座市场的技能值增加了 $x_j$。

在这 $Q$ 天里，每一天 Sandu 都会带着 $0$ 技能值来到市场 $1$，然后选择一个市场 $k$。然后，他会沿着从 $1$ 到 $k$ 的路径访问路径上的每一座市场（包括 $1$ 和 $k$）并尝试售卖糖果。注意：无论 Sandu 是否售卖糖果成功，他都会一直向下访问，直到到达 $k$。

现在 Sandu 想请你求出，对于每一天，他最多可以在多少个市场卖出糖果。
## 输入格式

第一行，两个整数 $N,Q$；

第二行 $N-1$ 个整数 $p_2,p_3,\dots,p_N$，其中 $p_i$ 表示 $i$ 号市场的父节点。**特别地，保证 $p_i < i$。**

第三行 $n$ 个整数 $t_1,t_2,\dots,t_n$，表示每座市场的困难度。

接下来 $Q$ 行，每行两个整数 $u_j,v_j$。
## 输出格式

输出 $Q$ 行，每行一个整数，表示每一天的答案。
## 样例

### 样例输入 #1
```
12 5
1 1 3 3 1 6 7 1 9 10 11
1 2 6 3 5 4 6 5 2 3 4 5
1 1
1 1
3 2
6 3
9 6
```
### 样例输出 #1
```
1
2
2
3
5
```
### 样例输入 #2
```
5 4
1 2 3 4
1 2 5 6 7
1 1
1 2
1 1
1 2

```
### 样例输出 #2
```
1
2
2
4
```
### 样例输入 #3
```
5 5
1 1 1 1
1 2 3 4 5
4 4
2 2
5 5
1 1
3 3
```
### 样例输出 #3
```
1
1
1
2
2
```
## 提示

**【数据范围】**

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$7$|对于 $1<i\le n$，有 $p_i=1$；$N,Q\le2000$|
|$2$|$8$|$N,Q\le2000,p_i=i-1$|
|$3$|$17$|$p_i=i-1$|
|$4$|$12$|$N,Q\le2000$|
|$5$|$21$|$u_j=1$|
|$6$|$24$|$N,Q\le10^5$|
|$7$|$11$|无|

对于 $100\%$ 的数据，$1\le N,Q\le5\times10^5,0 \le t_i\le10^9,1\le x_j\le10^9,1\le u_j\le N$。


---

---
title: "BZOJ3589 动态树"
layout: "post"
diff: 提高+/省选-
pid: P12693
tag: ['线段树', '树链剖分']
---
# BZOJ3589 动态树
## 题目描述

别忘了这是一棵动态树，每时每刻都是动态的。

小明要求你在这棵树上维护两种事件：

- 事件 0：这棵树长出了一些果子，即某个子树中的每个节点都会长出 $k$ 个果子。
- 事件 1：小明希望你求出几条树枝上的果子数。一条树枝其实就是一个从某个节点到根的路径的一段。

每次小明会选定一些树枝，让你求出在这些树枝上的节点的果子数的和。注意，树枝之间可能会重合，这时重合的部分的节点的果子只要算一次。
## 输入格式

第一行一个整数 $n$，即节点数。

接下来 $n - 1$ 行，每行两个数字 $u, v$。表示果子 $u$ 和果子 $v$ 之间有一条直接的边。节点从 $1$ 开始编号。

再接下来一个整数 $Q$，表示事件。

最后 $Q$ 行，每行开头要么是 $0$，要么是 $1$。

如果是 $0$，表示这个事件是事件 $0$。这行接下来的 $2$ 个整数 $u, delta$ 表示以 $u$ 为根的子树中的每个节点长出了 $delta$ 个果子。

如果是 $1$，表示这个事件是事件 $1$。这行接下来一个整数 $k$，表示这次询问涉及 $k$ 个树枝。接下来 $k$ 对整数 $u_k, v_k$，每个树枝从节点 $u_k$ 到节点 $v_k$。由于果子数可能非常多，请输出这个数模 $2^{31}$ 的结果。
## 输出格式

对于每个事件 $1$，输出询问的果子数。
## 样例

### 样例输入 #1
```
5
1 2
2 3
2 4
1 5
3
0 1 1
0 2 3
1 2 3 1 1 4
```
### 样例输出 #1
```
13
```
## 提示

对于 $100\%$ 的数据，$1 \leq n \leq 2 \times 10^5$，$1 \leq Q \leq 2 \times 10^5$，$k = 5$。

生成每个树枝的过程是这样的：先在树中随机找一个节点，然后在这个节点到根的路径上随机选一个节点，这两个节点就作为树枝的两端。


---

---
title: "[POI 2017 R3] 披萨配送员 Pizza delivery"
layout: "post"
diff: 提高+/省选-
pid: P12753
tag: ['贪心', '2017', 'POI（波兰）', '树链剖分']
---
# [POI 2017 R3] 披萨配送员 Pizza delivery
## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5061)。
## 题目描述

**题目译自 [XXIV Olimpiada Informatyczna — III etap](https://sio2.mimuw.edu.pl/c/oi24-3/dashboard/) [Dostawca pizzy](https://szkopul.edu.pl/problemset/problem/q_HBwDECevrQ2iQh1wT6ssx2/statement/)**

拜托城是一座风景如画的城市，拥有 $n$ 个路口，通过 $n-1$ 条双向道路相连。每路口旁有一户人家，其中之一是 Bajtazar 的披萨店。拜托城的居民酷爱披萨，每日清晨，Bajtazar 烘焙 $n-1$ 张披萨，挨家挨户送达（除自家外）。

为避免披萨冷却，Bajtazar 为配送车配备了尖端加热器，但其耗能极高，他希望尽量缩短使用时间。他的策略是：装载若干披萨，开启加热器，送至部分住户，送完最后一张后关闭加热器，返回披萨店。他最多愿意进行 $k$ 次配送，想知道送完所有披萨所需的最短加热器运行时间。

加热器在停留期间（Bajtazar 送披萨上门时）的运行时间可忽略。
## 输入格式

第一行包含两个正整数 $n, k$，分别表示拜托城的路口数量和 Bajtazar 最多愿意进行的配送次数。路口编号为 $1$ 至 $n$，披萨店位于路口 $1$。

接下来的 $n-1$ 行描述路网，第 $i$ 行包含三个正整数 $a_i, b_i, c_i$ $(a_i, b_i \leq n, a_i \neq b_i)$，表示路口 $a_i$ 和 $b_i$ 间有一条双向道路，单向通行需 $c_i$ 分钟。路网保证任意两路口间可达（不一定直接）。
## 输出格式

输出一行，包含一个整数，表示 Bajtazar 配送所有披萨所需的最短加热器运行时间（分钟）。
## 样例

### 样例输入 #1
```
7 3
1 2 5
2 3 11
2 4 2
5 2 6
1 6 1
7 1 1
```
### 样例输出 #1
```
34
```
## 提示

**样例 1 解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/5ybl7frg.png)

Bajtazar 进行三次配送：$1 \rightarrow 2 \rightarrow 4 \rightarrow 2 \rightarrow 5 \rightsquigarrow 1$（加热器运行 $15$ 分钟），$1 \rightarrow 2 \rightarrow 3 \rightsquigarrow 1$（$16$ 分钟），$1 \rightarrow 6 \rightarrow 1 \rightarrow 7 \rightsquigarrow 1$（$3$ 分钟）。

**附加样例**

1. $n=15, k=3$，小型完全二叉树，通往叶子的道路通行时间 $6$ 分钟，其余道路 $1$ 分钟。
2. $n=2000, k=100$，披萨店直达所有路口，大型随机通行时间。
3. $n=50000, k=1000$，披萨店直达两个路口，其中之一可达其余所有路口，所有通行时间为 $1$。

所有测试数据满足 $n \geq 2, k \geq 1, 1 \leq c_i \leq 1000000$。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n, k \leq 10$           | $12$ |
| $2$    | $n, k \leq 2000$         | $24$ |
| $3$    | $n, k \leq 100000$ 且 $n \cdot k \leq 4000000$ | $28$ |
| $4$    | $n, k \leq 100000$       | $36$ |


---

---
title: "[GCJ 2020 Finals] Pack the Slopes"
layout: "post"
diff: 提高+/省选-
pid: P13070
tag: ['2020', '线段树', '树链剖分', 'Google Code Jam']
---
# [GCJ 2020 Finals] Pack the Slopes
## 题目描述

You are trying to organize a group of skiers. The skiers are taking a trip to a large mountain, which has been rented for the day.

There are $\mathbf{N}$ rest points numbered from 1 to $\mathbf{N}$ on the mountain, and they are connected by $\mathbf{N}-1$ slopes. Each slope starts at some rest point and goes directly to another rest point, with no intermediate slopes or rest points. A slope can be traversed in only one direction.

Each skier starts at the summit rest point and traverses a slope to reach another rest point. From there, the skier can traverse another slope to reach another rest point, and so on. Once a skier reaches their destination rest point, they stop skiing for the day and head to the ski lodge for hot cocoa. The destination rest point cannot be the summit rest point. However, notice that a skier's destination rest point can be the start of zero or more slopes; that is, a skier does not necessarily have to keep using available slopes until there are none available: they can always walk carefully down the rest of the mountain! For all rest points, there is exactly one sequence of slopes that a skier can use to reach it from the summit rest point.

Each slope can accommodate only a certain total number of skiers in a day, after which the snow gets too choppy to ski. In addition, the ski resort can charge or reward each skier for each slope that they ski on. Each slope may have a different price, and each skier must pay the price for each slope they ski on. A slope's price can be positive, zero, or even negative; a negative price represents a bounty awarded for testing that slope. As the organizer, you pay all the slope prices and collect all the bounties on behalf of your group of skiers. Notice that if multiple skiers use the same slope, you pay that slope's price or collect the slope's bounty multiple times. The sum of all costs you pay minus the sum of all bounties you collect is the total expense for the trip. The expense can be positive, zero, or negative. A negative expense means that you actually made money on the trip!

As the organizer, you want to figure out the maximum number of skiers that you can put on the mountain. Also, you would like to figure out the minimum possible expense for a trip with that maximum number of skiers.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. The first line of a test case contains a single integer $\mathbf{N}$: the number of rest points on the mountain.

Each of the final $\mathbf{N}-1$ lines of a test case describes a slope via four integers $\mathbf{U_i}$, $\mathbf{V_i}$, $\mathbf{S_i}$, and $\mathbf{C_i}$. These are the slope's starting rest point, the slope's ending rest point, the maximum number of skiers the slope can accommodate, and the slope's price per skier, respectively.

The summit rest point where the skiers start from is always numbered 1.
## 输出格式

For each test case, output one line containing `Case #x: y z`, where $x$ is the test case number (starting from 1), $y$ is the maximum number of skiers, and $z$ is the minimum expense for having $y$ skiers ski at least one slope each.
## 样例

### 样例输入 #1
```
2
4
1 2 2 5
1 3 2 5
3 4 1 -2
7
4 7 2 2
1 3 5 5
1 4 2 -1
3 2 3 -2
3 5 2 -1
3 6 2 2
```
### 样例输出 #1
```
Case #1: 4 18
Case #2: 7 15
```
## 提示

**Sample Explanation**

In Sample Case #1, we can send one skier to rest point 4, one skier to rest point 3, and two skiers to rest point 2.

In Sample Case #2, we can send three skiers to rest point 2, two skiers to rest point 5, and two skiers to rest point 4.

Notice that the first slope listed in a test case does not need to start at the summit rest point, and that slopes can have $\mathbf{U_i} > \mathbf{V_i}$.

**Limits**

- $1 \leqslant \mathbf{U_i} \leqslant \mathbf{N}$, for all $i$.
- $2 \leqslant \mathbf{V_i} \leqslant \mathbf{N}$, for all $i$. (No slope can end at the summit rest point.)
- $\mathbf{U_i} \neq \mathbf{V_i}$, for all $i$.
- $1 \leqslant \mathbf{S_i} \leqslant 10^5$, for all $i$.
- $-10^5 \leqslant \mathbf{C_i} \leqslant 10^5$, for all $i$.
- There is exactly one sequence of slopes that a skier can use to reach rest point $r$ from the summit rest point, for all $r$.

**Test Set 1 (10 Pts, Visible Verdict)**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $2 \leqslant \mathbf{N} \leqslant 1000$.

**Test Set 2 (22 Pts, Hidden Verdict)**

- $\mathbf{T} = 17$.
- $2 \leqslant \mathbf{N} \leqslant 10^5$.


---

---
title: "[国家集训队] 旅游"
layout: "post"
diff: 提高+/省选-
pid: P1505
tag: ['集训队互测', '树链剖分']
---
# [国家集训队] 旅游
## 题目背景

Ray 乐忠于旅游，这次他来到了 T 城。T 城是一个水上城市，一共有 $n$ 个景点，有些景点之间会用一座桥连接。为了方便游客到达每个景点但又为了节约成本，T 城的任意两个景点之间有且只有一条路径。换句话说， T 城中只有 $n-1$ 座桥。

Ray 发现，有些桥上可以看到美丽的景色，让人心情愉悦，但有些桥狭窄泥泞，令人烦躁。于是，他给每座桥定义一个愉悦度 $w$，也就是说，Ray 经过这座桥会增加 $w$ 的愉悦度，这或许是正的也可能是负的。有时，Ray 看待同一座桥的心情也会发生改变。

现在，Ray 想让你帮他计算从 $u$ 景点到 $v$ 景点能获得的总愉悦度。有时，他还想知道某段路上最美丽的桥所提供的最大愉悦度，或是某段路上最糟糕的一座桥提供的最低愉悦度。

## 题目描述

给定一棵 $n$ 个节点的树，边带权，编号 $0 \sim n-1$，需要支持五种操作：

- `C i w` 将输入的第 $i$ 条边权值改为 $w$；
- `N u v` 将 $u,v$ 节点之间的边权都变为相反数；
- `SUM u v` 询问 $u,v$ 节点之间边权和；
- `MAX u v` 询问 $u,v$ 节点之间边权最大值；
- `MIN u v` 询问 $u,v$ 节点之间边权最小值。

保证任意时刻所有边的权值都在 $[-1000,1000]$ 内。

## 输入格式

第一行一个正整数 $n$，表示节点个数。  
接下来 $n-1$ 行，每行三个整数 $u,v,w$，表示 $u,v$ 之间有一条权值为 $w$ 的边，描述这棵树。      
然后一行一个正整数 $m$，表示操作数。  
接下来 $m$ 行，每行表示一个操作。

## 输出格式

对于每一个询问操作，输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
3
0 1 1
1 2 2
8
SUM 0 2
MAX 0 2
N 0 1
SUM 0 2
MIN 0 2
C 1 3
SUM 0 2
MAX 0 2
```
### 样例输出 #1
```
3
2
1
-1
5
3
```
## 提示

【数据范围】  

对于 $100\%$ 的数据，$1\le n,m \le 2\times 10^5$。

2020.02.04 修正了一点数据的错误  
2020.03.14 加入了一组 hack 数据  
2020.11.26 加入了一组 hack 数据 By @_Leaving


---

---
title: "[NOI2015] 软件包管理器"
layout: "post"
diff: 提高+/省选-
pid: P2146
tag: ['树形数据结构', '2015', '线段树', 'NOI', '深度优先搜索 DFS', '树链剖分']
---
# [NOI2015] 软件包管理器
## 题目背景

Linux 用户和 OSX 用户一定对软件包管理器不会陌生。通过软件包管理器，你可以通过一行命令安装某一个软件包，然后软件包管理器会帮助你从软件源下载软件包，同时自动解决所有的依赖（即下载安装这个软件包的安装所依赖的其它软件包），完成所有的配置。Debian/Ubuntu 使用的 apt-get，Fedora/CentOS 使用的 yum，以及 OSX 下可用的 homebrew 都是优秀的软件包管理器。  

## 题目描述

你决定设计你自己的软件包管理器。不可避免地，你要解决软件包之间的依赖问题。如果软件包 $a$ 依赖软件包 $b$，那么安装软件包 $a$ 以前，必须先安装软件包 $b$。同时，如果想要卸载软件包 $b$，则必须卸载软件包 $a$。

现在你已经获得了所有的软件包之间的依赖关系。而且，由于你之前的工作，除 $0$ 号软件包以外，在你的管理器当中的软件包都会依赖一个且仅一个软件包，而 $0$ 号软件包不依赖任何一个软件包。且依赖关系不存在环（即不会存在 $m$ 个软件包 $a_1,a_2, \dots , a_m$，对于 $i<m$，$a_i$ 依赖 $a_{i+1}$，而 $a_m$ 依赖 $a_1$ 的情况）。

现在你要为你的软件包管理器写一个依赖解决程序。根据反馈，用户希望在安装和卸载某个软件包时，快速地知道这个操作实际上会改变多少个软件包的安装状态（即安装操作会安装多少个未安装的软件包，或卸载操作会卸载多少个已安装的软件包），你的任务就是实现这个部分。

注意，安装一个已安装的软件包，或卸载一个未安装的软件包，都不会改变任何软件包的安装状态，即在此情况下，改变安装状态的软件包数为 $0$。

## 输入格式

第一行一个正整数 $n$，表示软件包个数，从 $0$ 开始编号。  
第二行有 $n-1$ 个整数，第 $i$ 个表示 $i$ 号软件包依赖的软件包编号。  
然后一行一个正整数 $q$，表示操作个数，格式如下：  

- `install x` 表示安装 $x$ 号软件包
- `uninstall x` 表示卸载 $x$ 号软件包

一开始所有软件包都是未安装的。  

对于每个操作，你需要输出这步操作会改变多少个软件包的安装状态，随后应用这个操作（即改变你维护的安装状态）。
## 输出格式

输出 $q$ 行，每行一个整数，表示每次询问的答案。
## 样例

### 样例输入 #1
```
7
0 0 0 1 1 5
5
install 5
install 6
uninstall 1
install 4
uninstall 0
```
### 样例输出 #1
```
3
1
3
2
3
```
### 样例输入 #2
```
10
0 1 2 1 3 0 0 3 2
10
install 0
install 3
uninstall 2
install 7
install 5
install 9
uninstall 9
install 4
install 1
install 9
```
### 样例输出 #2
```
1
3
2
1
3
1
1
1
0
1
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/1504.png)  
一开始所有软件包都处于未安装状态。

安装 $5$ 号软件包，需要安装 $0,1,5$ 三个软件包。

之后安装 $6$ 号软件包，只需要安装 $6$ 号软件包。此时安装了 $0,1,5,6$ 四个软件包。

卸载 $1$ 号软件包需要卸载 $1,5,6$ 三个软件包。此时只有 $0$ 号软件包还处于安装状态。

之后安装 $4$ 号软件包，需要安装 $1,4$ 两个软件包。此时 $0,1,4$ 处在安装状态。最后，卸载 $0$ 号软件包会卸载所有的软件包。

【数据范围】  
![](https://cdn.luogu.com.cn/upload/pic/1505.png)


---

---
title: "[ZJOI2008] 树的统计"
layout: "post"
diff: 提高+/省选-
pid: P2590
tag: ['2008', '线段树', '各省省选', '浙江', '树链剖分']
---
# [ZJOI2008] 树的统计
## 题目描述

一棵树上有 $n$ 个节点，编号分别为 $1$ 到 $n$，每个节点都有一个权值 $w$。

我们将以下面的形式来要求你对这棵树完成一些操作：

I. `CHANGE u t` : 把结点 $u$ 的权值改为 $t$。

II. `QMAX u v`: 询问从点 $u$ 到点 $v$ 的路径上的节点的最大权值。

III. `QSUM u v`: 询问从点 $u$ 到点 $v$ 的路径上的节点的权值和。

注意：从点 $u$ 到点 $v$ 的路径上的节点包括 $u$ 和 $v$ 本身。
## 输入格式

输入文件的第一行为一个整数 $n$，表示节点的个数。

接下来 $n-1$ 行，每行 $2$ 个整数 $a$ 和 $b$，表示节点 $a$ 和节点 $b$ 之间有一条边相连。

接下来一行 $n$ 个整数，第 $i$ 个整数 $w_i$ 表示节点 $i$ 的权值。

接下来 $1$ 行，为一个整数 $q$，表示操作的总数。

接下来 $q$ 行，每行一个操作，以 `CHANGE u t` 或者 `QMAX u v` 或者 `QSUM u v` 的形式给出。

## 输出格式

对于每个 `QMAX` 或者 `QSUM` 的操作，每行输出一个整数表示要求输出的结果。
## 样例

### 样例输入 #1
```
4
1 2
2 3
4 1
4 2 1 3
12
QMAX 3 4
QMAX 3 3
QMAX 3 2
QMAX 2 3
QSUM 3 4
QSUM 2 1
CHANGE 1 5
QMAX 3 4
CHANGE 3 6
QMAX 3 4
QMAX 2 4
QSUM 3 4

```
### 样例输出 #1
```
4
1
2
2
10
6
5
6
5
16

```
## 提示

对于 $100 \%$ 的数据，保证 $1\le n \le 3\times 10^4$，$0\le q\le 2\times 10^5$。

中途操作中保证每个节点的权值 $w$ 在 $-3\times 10^4$ 到 $3\times 10^4$ 之间。


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
title: "[USACO11DEC] Grass Planting G"
layout: "post"
diff: 提高+/省选-
pid: P3038
tag: ['2011', '线段树', 'USACO', '树链剖分']
---
# [USACO11DEC] Grass Planting G
## 题目描述

Farmer John has N barren pastures (2 <= N <= 100,000) connected by N-1 bidirectional roads, such that there is exactly one path between any two pastures.  Bessie, a cow who loves her grazing time, often complains about how there is no grass on the roads between pastures.  Farmer John loves Bessie very much, and today he is finally going to plant grass on the roads.  He will do so using a procedure consisting of M steps (1 <= M <= 100,000).

At each step one of two things will happen:

- FJ will choose two pastures, and plant a patch of grass along each road in between the two pastures, or,

- Bessie will ask about how many patches of grass on a particular road, and Farmer John must answer her question.

Farmer John is a very poor counter -- help him answer Bessie's questions!

## 输入格式

\* Line 1: Two space-separated integers N and M

\* Lines 2..N: Two space-separated integers describing the endpoints of a road.

\* Lines N+1..N+M: Line i+1 describes step i. The first character of the line is either P or Q, which describes whether or not FJ is planting grass or simply querying. This is followed by two space-separated integers A\_i and B\_i (1 <= A\_i, B\_i <= N) which describe FJ's action or query.

## 输出格式

\* Lines 1..???: Each line has the answer to a query, appearing in the same order as the queries appear in the input.

## 样例

### 样例输入 #1
```
4 6 
1 4 
2 4 
3 4 
P 2 3 
P 1 3 
Q 3 4 
P 1 4 
Q 2 4 
Q 1 4 

```
### 样例输出 #1
```
2 
1 
2 


```
## 题目翻译

给出一棵有 $n$ 个节点的树，有 $m$ 个如下所示的操作：

- 将两个节点之间的 **路径上的边** 的权值均加一。

- 查询两个节点之间的 **那一条边** 的权值，保证两个节点直接相连。

初始边权均为 0。

**【输入格式】**

第一行两个整数 $n,m$，含义如上。

接下来 $n-1$ 行，每行两个整数 $u,v$，表示 $u,v$ 之间有一条边。

接下来 $m$ 行，每行格式为 `op u v`，$op=\texttt{P}$ 代表第一个操作，$op=\texttt{Q}$ 代表第二个操作。

**【输出格式】**

若干行。对于每个查询操作，输出一行整数，代表查询的答案。

**【数据范围】**

对于 $100\%$ 的数据，$2\le n\le 10^5$，$1\le m\le 10^5$。


---

---
title: "[HAOI2015] 树上操作"
layout: "post"
diff: 提高+/省选-
pid: P3178
tag: ['2015', '河南', '线段树', '深度优先搜索 DFS', '树链剖分']
---
# [HAOI2015] 树上操作
## 题目描述

有一棵点数为 $N$ 的树，以点 $1$ 为根，且树有点权。然后有 $M$ 个操作，分为三种：
- 操作 $1$：把某个节点 $x$ 的点权增加 $a$。
- 操作 $2$：把某个节点 $x$ 为根的子树中所有点的点权都增加 $a$。
- 操作 $3$：询问某个节点 $x$ 到根的路径中所有点的点权和。

## 输入格式

第一行包含两个整数 $N,M$。表示点数和操作数。  
接下来一行 $N$ 个整数，表示树中节点的初始权值。  
接下来 $N-1$ 行每行两个正整数 $\mathit{from},\mathit{to}$， 表示该树中存在一条边 $(\mathit{from},\mathit{to})$。  
再接下来 $M$ 行，每行分别表示一次操作。其中第一个数表示该操作的种类，之后接这个操作的参数。

## 输出格式

对于每个询问操作，输出该询问的答案。答案之间用换行隔开。

## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 2
1 4
2 3
2 5
3 3
1 2 1
3 5
2 1 2
3 3
```
### 样例输出 #1
```
6
9
13
```
## 提示

对于 $100\%$ 的数据，$1\le N,M\le10^5$，且所有输入数据的绝对值都不会超过 $10^6$。



---

---
title: "【模板】重链剖分/树链剖分"
layout: "post"
diff: 提高+/省选-
pid: P3384
tag: ['树链剖分']
---
# 【模板】重链剖分/树链剖分
## 题目描述

如题，已知一棵包含 $N$ 个结点的树（连通且无环），每个节点上包含一个数值，需要支持以下操作：

- `1 x y z`，表示将树从 $x$ 到 $y$ 结点最短路径上所有节点的值都加上 $z$。

- `2 x y`，表示求树从 $x$ 到 $y$ 结点最短路径上所有节点的值之和。

- `3 x z`，表示将以 $x$ 为根节点的子树内所有节点值都加上 $z$。

- `4 x` 表示求以 $x$ 为根节点的子树内所有节点值之和
## 输入格式

第一行包含 $4$ 个正整数 $N,M,R,P$，分别表示树的结点个数、操作个数、根节点序号和取模数（**即所有的输出结果均对此取模**）。

接下来一行包含 $N$ 个非负整数，分别依次表示各个节点上初始的数值。

接下来 $N-1$ 行每行包含两个整数 $x,y$，表示点 $x$ 和点 $y$ 之间连有一条边（保证无环且连通）。

接下来 $M$ 行每行包含若干个正整数，每行表示一个操作。
## 输出格式

输出包含若干行，分别依次表示每个操作 $2$ 或操作 $4$ 所得的结果（**对 $P$ 取模**）。
## 样例

### 样例输入 #1
```
5 5 2 24
7 3 7 8 0 
1 2
1 5
3 1
4 1
3 4 2
3 2 2
4 5
1 5 1 3
2 1 3
```
### 样例输出 #1
```
2
21
```
## 提示

**【数据规模】**

对于 $30\%$ 的数据： $1 \leq N \leq 10$，$1 \leq M \leq 10$；

对于 $70\%$ 的数据： $1 \leq N \leq {10}^3$，$1 \leq M \leq {10}^3$；

对于 $100\%$ 的数据： $1\le N \leq {10}^5$，$1\le M \leq {10}^5$，$1\le R\le N$，$1\le P \le 2^{30}$。所有输入的数均在 `int` 范围内。

**【样例说明】**

树的结构如下：

![](https://cdn.luogu.com.cn/upload/pic/2319.png)

各个操作如下：

![](https://cdn.luogu.com.cn/upload/pic/2320.png)

故输出应依次为 $2$ 和 $21$。


---

---
title: "[SHOI2012] 魔法树"
layout: "post"
diff: 提高+/省选-
pid: P3833
tag: ['2012', '线段树', '倍增', '各省省选', '上海', '最近公共祖先 LCA', '树链剖分']
---
# [SHOI2012] 魔法树
## 题目背景

SHOI2012 D2T3

## 题目描述

Harry Potter 新学了一种魔法：可以改变树上的果子个数。满心欢喜的他找到了一个巨大的果树，来试验他的新法术。

这棵果树共有 $N$ 个节点，其中节点 $0$ 是根节点，每个节点 $u$ 的父亲记为 $fa[u]$，保证有 $fa[u] < u$ 。初始时，这棵果树上的果子都被 Dumbledore 用魔法清除掉了，所以这个果树的每个节点上都没有果子（即 $0$ 个果子）。

不幸的是，Harry 的法术学得不到位，只能对树上一段路径的节点上的果子个数统一增加一定的数量。也就是说，Harry 的魔法可以这样描述：`A u v d` 。表示将点 $u$ 和 $v$ 之间的路径上的所有节点的果子个数都加上 $d$。

接下来，为了方便检验 Harry 的魔法是否成功，你需要告诉他在释放魔法的过程中的一些有关果树的信息：`Q u`。表示当前果树中，以点 $u$ 为根的子树中，总共有多少个果子？

## 输入格式

第一行一个正整数 $N (1 \leq N \leq 100000)$，表示果树的节点总数，节点以 $0,1,\dots,N - 1$ 标号，$0$ 一定代表根节点。

接下来 $N - 1$ 行，每行两个整数 $a,b (0 \leq a < b < N)$，表示 $a$ 是 $b$ 的父亲。

接下来是一个正整数 $Q(1 \leq Q \leq 100000)$，表示共有 $Q$ 次操作。

后面跟着 $Q$ 行，每行是以下两种中的一种：

1. `A u v d`，表示将 $u$ 到 $v$ 的路径上的所有节点的果子数加上 $d$。保证 $0 \leq u,v < N,0 < d < 100000$

2. `Q u`，表示询问以 $u$ 为根的子树中的总果子数，注意是包括 $u$ 本身的。

## 输出格式

对于所有的 `Q` 操作，依次输出询问的答案，每行一个。答案可能会超过 $2^{32}$ ，但不会超过 $10^{15}$ 。

## 样例

### 样例输入 #1
```
4
0 1
1 2
2 3
4
A 1 3 1
Q 0
Q 1
Q 2
```
### 样例输出 #1
```
3
3
2
```


---

---
title: "部落冲突"
layout: "post"
diff: 提高+/省选-
pid: P3950
tag: ['线段树', '最近公共祖先 LCA', '树链剖分', '动态树 LCT']
---
# 部落冲突
## 题目背景

在一个叫做 Travian 的世界里，生活着各个大大小小的部落。其中最为强大的是罗马、高卢和日耳曼。他们之间为了争夺资源和土地，进行了无数次的战斗。期间诞生了众多家喻户晓的英雄人物，也留下了许多可歌可泣的动人故事。

![](http://img4.dwstatic.com/coc/1602/320370032694/1456415099616.jpg)

其中，在大大小小的部落之间，会有一些道路相连，这些道路是 Travian 世界里的重要枢纽，简单起见，你可以把这些部落与部落之间相连的道路看作一颗树，可见每条道路对于 Travian 世界的重要程度。有了这些道路，建筑工人就可以通过这些道路进行友好外交啦。

然而，事情并不会像想象的那样美好，由于资源的匮乏，相邻的部落（由一条道路相连的部落）之间经常会发生大大小小的冲突事件，更有甚者，会升级为部落之间的大型战争。

为了避免误伤，每当两个相邻的部落之间发生大型战争之时，这两个部落间的道路是不允许通行的，对于一些强大的部落，甚至能与多个相邻的部落同时开战，同样的，这些战争地带的道路十分危险，是不可通行的。

天下之势，分久必合，当两个部落经历了不打不相识的苦战之后，他们可以签订停战协议（暂时停战，以后依旧可能再次开战），这样，两个部落之间的道路又会重新恢复为可通行状态，建筑工人们又可以经过此地购买最新的大本营设计图纸来强大自己的部落了。

为了简单起见，我们把各大战争事件按发起的时间顺序依次编号（最先发起的战争编号就为 $1$，第二次战争编号就为 $2$，以此类推），当两个部落停战之时，则会直接告诉你这场战争的编号，然后这场战争就载入了史册，不复存在了，当然，这并不会影响到其他战争的编号。

建筑工人十分讨厌战争，因为战争，想从一个部落到另一个部落进行友好交流的建筑工人可能就此白跑一趟。所以，在他们出发之前，都会向你问问能不能到达他们想去的部落。

## 题目描述

简单起见，你就是要处理下面三件事，所有的事件都是按照时间顺序给出的。

1. `Q p q` 从第 $p$ 个部落出发的建筑工人想知道能否到达第 $q$ 个部落了，你要回答的便是 `Yes` / `No`，注意**大小写**。

2. `C p q` 第 $p$ 个部落与第 $q$ 个部落开战了，保证他们一定是相邻的部落，且目前处于停战（未开战）状态。

3. `U x` 第 $x$ 次发生的战争结束了，它将永远的被载入史册，不复存在（保证这个消息不会告诉你多次）

## 输入格式

第一行两个数 $n$ 和 $m$， $n$ 代表了一共有 $n$ 个部落，$m$ 代表了以上三种事件发生的总数。

接下来的 $n - 1$ 行，每行两个数 $p, q$，代表了第 $p$ 个部落与第 $q$ 个部落之间有一条道路相连。

接下来的 $m$ 行，每行表示一件事，详见题目描述。
## 输出格式

每行一个 `Yes` 或者 `No`，表示从第 $p$ 个部落出发的建筑工人能否到达第 $q$ 个部落。
## 样例

### 样例输入 #1
```
5 9
1 2
2 3
3 4
4 5
Q 1 4
C 2 1
C 4 3
Q 3 1
Q 1 5
U 1
U 2
C 4 3
Q 3 4
```
### 样例输出 #1
```
Yes
No
No
No
```
### 样例输入 #2
```
10 10
1 2
1 3
3 4
3 5
1 6
3 7
1 8
2 9
5 10
C 8 1
Q 6 1
C 2 1
Q 2 10
U 1
C 9 2
C 7 3
U 3
Q 6 7
Q 1 10
```
### 样例输出 #2
```
Yes
No
No
Yes
```
### 样例输入 #3
```
20 20
1 2
1 3
2 4
1 5
1 6
4 7
1 8
2 9
5 10
1 11
2 12
7 13
1 14
1 15
11 16
4 17
3 18
18 19
8 20
Q 13 5
C 14 1
C 16 11
U 1
U 2
C 20 8
Q 7 1
C 7 4
Q 17 17
Q 1 6
C 16 11
C 2 1
Q 16 2
U 3
U 5
U 6
C 2 1
C 6 1
C 13 7
C 11 1

```
### 样例输出 #3
```
Yes
Yes
Yes
Yes
No

```
## 提示

对于 $30\%$ 的数据，$n, m\leq 6\times10^3$。

对于另 $30\%$ 的数据，保证部落之间的地理关系是一条链，且 $i$ 与 $i + 1$ 之间有一条道路。

对于另 $30\%$ 的数据，$n, m\leq 10^5$。

对于 $100\%$ 的数据，$1\leq n, m\leq 3\times10^5$。



---

---
title: "[HEOI2016/TJOI2016] 树"
layout: "post"
diff: 提高+/省选-
pid: P4092
tag: ['搜索', '2016', '线段树', '并查集', '各省省选', '河北', '树链剖分', '天津']
---
# [HEOI2016/TJOI2016] 树
## 题目描述

在 2016 年，佳媛姐姐刚刚学习了树，非常开心。现在他想解决这样一个问题：给定一颗有根树，根为 $1$ ，有以下两种操作：

1. 标记操作：对某个结点打上标记。（在最开始，只有结点 $1$ 有标记，其他结点均无标记，而且对于某个结点，可以打多次标记。）

2. 询问操作：询问某个结点最近的一个打了标记的祖先。（这个结点本身也算自己的祖先）

你能帮帮她吗?

## 输入格式

第一行两个正整数 $N$ 和 $Q$ 分别表示节点个数和操作次数。

接下来 $N-1$ 行，每行两个正整数 $u,v \,\, (1 \leqslant u,v \leqslant n)$ 表示 $u$ 到 $v$ 有一条有向边。

接下来 $Q$ 行，形如 `oper num` ，`oper`  为 `C` 时表示这是一个标记操作, `oper` 为 `Q` 时表示这是一个询问操作。
## 输出格式

输出一个正整数，表示结果

## 样例

### 样例输入 #1
```
5 5 
1 2 
1 3 
2 4 
2 5 
Q 2 
C 2 
Q 2 
Q 5 
Q 3
```
### 样例输出 #1
```
1
2
2
1
```
## 提示

$30\%$ 的数据，$1 \leqslant N, Q \leqslant 1000$ ；

$70\%$ 的数据，$1 \leqslant N, Q \leqslant 10000$ ；

$100\%$ 的数据，$1 \leqslant N, Q \leqslant 100000$ 。


---

---
title: "Qtree1"
layout: "post"
diff: 提高+/省选-
pid: P4114
tag: ['线段树', '树链剖分']
---
# Qtree1
## 题目背景

**数据规模和 spoj 上有所不同**。
## 题目描述

给定一棵 $n$ 个节点的树，有两种操作：  
- `CHANGE i t` 把第 $i$ 条边的边权变成 $t$  
- `QUERY a b` 输出从 $a$ 到 $b$ 的路径上最大的边权。当 $a=b$ 时，输出 $0$  
## 输入格式

第一行是一个整数 $n$，表示节点个数。  
第二行到第 $n$ 行每行输入三个整数 $u,v,w$ ，分别表示 $u$ 与 $v$ 有一条边，边权是 $w$。  
第 $n+1$ 行开始，一共有不定数量行，每一行先包含一个字符串，分别有以下三种可能：  

- `CHANGE`  接下来包含两个整数 $x, t$ ，表示一次修改操作。  
- `QUERY`  接下来包含两个正整数 $a, b$ ， 表示一次查询操作。  
- `DONE`  表示输入结束。

## 输出格式

对于每个 `QUERY` 操作，输出一行一个数，表示 $a,b$ 的路径上最大的边权。  
## 样例

### 样例输入 #1
```
3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE
```
### 样例输出 #1
```
1
3
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 10^5$。
- $1 \leq u, v, a, b \leq n$，$1 \leq x < n$。
- $1 \leq w, t \leq 2^{31} - 1$。
- 操作次数不大于 $3 \times 10^5$。


---

---
title: "Qtree3"
layout: "post"
diff: 提高+/省选-
pid: P4116
tag: ['线段树', 'O2优化', '枚举', '树链剖分', '分块']
---
# Qtree3
## 题目描述

给出 $N$ 个点的一棵树（$N-1$ 条边），节点有白有黑，初始全为白。

有两种操作：

`0 i`：改变某点的颜色（原来是黑的变白，原来是白的变黑）。

`1 v`：询问 $1$ 到 $v$ 的路径上的第一个黑点，若无，输出 $-1$。
## 输入格式

第一行 $N$，$Q$，表示 $N$ 个点和 $Q$ 个操作。

第二行到第 $N$ 行 $N-1$ 条无向边。

再之后 $Q$ 行，每行一个操作 `0 i` 或者 `1 v`。
## 输出格式

对每个 `1 v` 操作输出结果

## 样例

### 样例输入 #1
```
9 8
1 2
1 3
2 4
2 9
5 9
7 9
8 9
6 8
1 3
0 8
1 6
1 7
0 2
1 9
0 2
1 9 
```
### 样例输出 #1
```
-1
8
-1
2
-1
```
## 提示

对于 $1/3$ 的数据有 $N=5000,Q=400000$。

对于 $1/3$ 的数据有 $N=10000,Q=300000$。

对于 $1/3$ 的数据有 $N=100000, Q=100000$。

此外，有$1 \le i,v \le N$。


---

---
title: "月下“毛景树”"
layout: "post"
diff: 提高+/省选-
pid: P4315
tag: ['线段树', '最近公共祖先 LCA', '树链剖分']
---
# 月下“毛景树”
## 题目背景

毛毛虫经过及时的变形，最终逃过的一劫，离开了菜妈的菜园。 毛毛虫经过千山万水，历尽千辛万苦，最后来到了小小的绍兴一中的校园里。
## 题目描述



爬啊爬~爬啊爬~~毛毛虫爬到了一颗小小的“毛景树”下面，发现树上长着他最爱吃的毛毛果~~~ “毛景树”上有 $N$ 个节点和 $N-1$ 条树枝，但节点上是没有毛毛果的，毛毛果都是长在树枝上的。但是这棵“毛景树”有着神奇的魔力，他能改变树枝上毛毛果的个数：

- `Change k w`：将第k条树枝上毛毛果的个数改变为 $w$ 个。
- `Cover u v w`：将节点 $u$ 与节点 $v$ 之间的树枝上毛毛果的个数都改变为 $w$ 个。
- `Add u v w`：将节点 $u$ 与节点 $v$ 之间的树枝上毛毛果的个数都增加 $w$ 个。

由于毛毛虫很贪，于是他会有如下询问：

-  `Max u v`：询问节点 $u$ 与节点 $v$ 之间树枝上毛毛果个数最多有多少个。

## 输入格式

第一行一个正整数 $N$。

接下来 $N-1$ 行，每行三个正整数 $U_i,V_i$ 和 $W_i$，第 $i+1$ 行描述第 $i$ 条树枝。表示第 $i$ 条树枝连接节点 $U_i$ 和节点 $V_i$，树枝上有 $W_i$ 个毛毛果。 接下来是操作和询问，以 `Stop` 结束。

## 输出格式

对于毛毛虫的每个询问操作，输出一个答案。

## 样例

### 样例输入 #1
```
4
1 2 8
1 3 7
3 4 9
Max 2 4
Cover 2 4 5
Add 1 4 10
Change 1 16
Max 2 4
Stop
```
### 样例输出 #1
```
9
16
```
## 提示

对于全部数据，$1\le N\le 10^5$，操作和询问数目不超过 $10^5$。

保证在任意时刻，所有树枝上毛毛果的个数都不会超过 $10^9$ 个。



---

---
title: "[USACO18OPEN] Disruption P"
layout: "post"
diff: 提高+/省选-
pid: P4374
tag: ['2018', '线段树', 'USACO', '树链剖分']
---
# [USACO18OPEN] Disruption P
## 题目描述

Farmer John 自豪于他所经营的交通发达的农场。这个农场由 $N$ 块牧场（$2 \leq N \leq 50,000$）组成，$N-1$ 条双向道路将它们连接起来，每条道路的长度均为 $1$ 单位。Farmer John 注意到，从任何一块牧场到另一块牧场，都能通过一组合适的道路到达。

尽管 FJ 的农场现在是连通的，他担心如果有一条道路被阻断会发生什么，因为这会将农场分为两个不相交的牧场集合，奶牛们只能在每个集合内移动而不能在集合间移动。于是 FJ 又建造了 $M$ 条额外的双向道路（$1 \leq M \leq 50,000$），每条道路的长度都是一个至多为 $10^9$ 的正整数。奶牛们仍然可以使用原有的道路进行移动，除非其中的某些被阻断。

如果某条原有的道路被阻断，农场就会被分为两块不相交的区域，那么 FJ 会从他的额外修建的道路中选择一条能够重建这两块区域连通性的道路，取代原来的那条，从而使奶牛们又可以从任何一块牧场去往另一块牧场。

对于农场上每一条原有的道路，帮助 FJ 选出最短的替代道路。
## 输入格式

输入的第一行包含 $N$ 和 $M$。接下来的 $N-1$ 行，每行用整数 $p$ 和 $q$ 描述了一条原有的道路，其中 $p \neq q$ 是这条道路连接的两块牧场（在 $1 \ldots N$ 范围内）。剩下的 $M$ 行，每行用三个整数 $p$、$q$ 和 $r$ 描述了一条额外的道路，其中 $r$ 是这条道路的长度。任何两块牧场之间至多只有一条道路。
## 输出格式

对原有的 $N-1$ 条道路的每一条，按照它们在输入中出现的顺序，输出如果这条道路被阻断的话，能够重新连接农场的最短替代道路的长度。如果不存在合适的替代道路，输出 $-1$。
## 样例

### 样例输入 #1
```
6 3
1 2
1 3
4 1
4 5
6 5
2 3 7
3 6 8
6 4 5
```
### 样例输出 #1
```
7
7
8
5
5
```
## 提示

供题：Brian Dean


---

---
title: "最短距离"
layout: "post"
diff: 提高+/省选-
pid: P4949
tag: ['最近公共祖先 LCA', '树链剖分', '基环树']
---
# 最短距离
## 题目描述

给出一个 $n$ 个点 $n$ 条边的无向连通图。

你需要支持两种操作：

1. 修改 第 $x$  条边的长度为 $y$ ；

2. 查询 点 $x$ 到点 $y$ 的最短距离。

共有 $m$ 次操作。
## 输入格式

输入共 $n+m+1$ 行：

第 $1$ 行，包含两个正整数 $n,m$，表示点数即边数，操作次数。

第 $2$ 行到第 $n+1$ 行，每行包含三个正整数 $x,y,z$，表示 $x$ 与 $y$ 间有一条长度为 $z$ 的边。

第 $n+2$ 到 $n+m+1$ 行，每行包含三个正整数 $op,x,y$，表示操作种类，操作的参数（含义见【题目描述】）。
## 输出格式

对于每次操作 $2$ 输出查询的结果。
## 样例

### 样例输入 #1
```
4 5
1 2 11
1 3 12
2 3 13
1 4 15
2 2 3
1 2 1
2 2 3
2 2 4
2 3 4
```
### 样例输出 #1
```
13
12
26
16
```
## 提示

![Luogu](https://cdn.luogu.com.cn/upload/pic/37934.png)  

对于 $100\%$ 的数据，保证 $z\in [0,5000]$。


---

---
title: "[USACO19DEC] Milk Visits G"
layout: "post"
diff: 提高+/省选-
pid: P5838
tag: ['2019', 'USACO', '树链剖分']
---
# [USACO19DEC] Milk Visits G
## 题目描述

Farmer John 计划建造 $N$ 个农场，用 $N-1$ 条道路连接，构成一棵树（也就是说，所有农场之间都互相可以到达，并且没有环）。每个农场有一头奶牛，品种为 $1$ 到 $N$ 之间的一个整数 $T_i$。

Farmer John 的 $M$ 个朋友经常前来拜访他。在朋友 $i$ 拜访之时，Farmer John 会与他的朋友沿着从农场 $A_i$ 到农场 $B_i$ 之间的唯一路径行走（可能有 $A_i = B_i$）。除此之外，他们还可以品尝他们经过的路径上任意一头奶牛的牛奶。由于 Farmer John 的朋友们大多数也是农场主，他们对牛奶有着极强的偏好。他的每个朋友都只喝某种特定品种的奶牛的牛奶。任何 Farmer John 的朋友只有在他们访问时能喝到他们偏好的牛奶才会高兴。

请求出每个朋友在拜访过后是否会高兴。


## 输入格式

输入的第一行包含两个整数 $N$ 和 $M$。

第二行包含 $N$ 个空格分隔的整数 $T_1,T_2,\ldots, T_N$。第 $i$ 个农场内的奶牛的品种用 $T_i$ 表示。

以下 $N-1$ 行，每行包含两个不同的整数 $X$ 和 $Y$（$1 \leq X, Y \leq N$），表示农场 $X$ 与 $Y$ 之间有一条边。

以下 $M$ 行，每行包含整数 $A_i$，$B_i$，以及$C_i$。$A_i$ 和 $B_i$ 表示朋友 $i$ 拜访时行走的路径的端点，$C_i$（$1\le C_i\le N$）表示这个朋友喜欢的牛奶的奶牛品种。
## 输出格式

输出一个长为 $M$ 的二进制字符串。如果第 $i$ 个朋友会感到高兴，则字符串的第 $i$ 个字符为 `1`，否则为 `0`。
## 样例

### 样例输入 #1
```
5 5
1 1 2 1 2
1 2
2 3
2 4
1 5
1 4 1
1 4 2
1 3 2
1 3 1
5 5 1
```
### 样例输出 #1
```
10110
```
### 样例输入 #2
```
6 4
1 2 3 3 3 3
1 2
2 3
3 4
2 5
5 6
4 6 1
4 6 2
4 6 3
4 6 4
```
### 样例输出 #2
```
0110
```
## 提示

测试点性质：

测试点 $2$ 为以下第二个样例。

测试点 $3$ 满足 $N\le 10^3$，$M\le 2\cdot 10^3$。

测试点 $4\sim 7$ 满足 $C_i\le 10$。

对于 $100\%$ 的数据，$1 \leq N \leq 10^5$，$1 \leq M \leq 10^5$。

供题：Spencer Compton


---

---
title: "[USACO19FEB] Cow Land G"
layout: "post"
diff: 提高+/省选-
pid: P6098
tag: ['2019', '线段树', 'USACO', '树链剖分']
---
# [USACO19FEB] Cow Land G
## 题目背景

Cow Land 是一个特殊的奶牛游乐园，奶牛们可以在那里漫步，吃美味的草，并参观不同的景点（尤其过山车特别受欢迎）。
## 题目描述

Cow Land 总共有 $ N $ 个不同的景点（ $ 2 \leq N \leq 10^5 $ ）。 一共有 $ n-1 $ 条道路连接任意两个景点，这意味着任意两个景点间只有一条简单路径。

每个景点 $ i $ 都有一个享受值 $ e_i $ ，这个值可能会改变。因为一些景点在早上更有吸引力，而其他景点在下午则更能吸引游客。

从景点 $ i $ 到景点 $ j $ 的奶牛们可以欣赏从景点 $ i $ 到景点 $ j $ 的路上的所有景观。这条路线的享受值为景点 $ i $ 到景点 $ j $ 的路上的所有景点（包括景点 $ i $ 和景点 $ j $ ）的享受值按位进行异或运算的结果。

请帮助奶牛确定他们前往 Cow Land 旅行时计划的路线的享受值。
## 输入格式

输入的第一行包含两个整数， $ N,Q $（$1 \leq Q \leq 10^5$）。

接下来一行包含 $ N $ 个整数，其中第 $ i $ 个整数 $ e_i $ 代表景点 $ i $ 的享受值。

接下来 $ N-1 $ 行，每行包含两个整数 $ a,b $ ，表示景点 $ a $ 和景点 $ b $ 之间有一条道路相连。

最后 $ Q $ 行，每行包含 3 个整数，表示一个操作，具体内容如下：

1. `1 i v`，表示将 $ e_i $ 修改为 $ v $ 。
2. `2 i j`，表示询问从景点 $ i $ 到景点 $ j $ 的路线的享受值为多少。
## 输出格式

对于每个 2 操作，输出对应查询的结果。
## 样例

### 样例输入 #1
```
5 5
1 2 4 8 16
1 2
1 3
3 4
3 5
2 1 5
1 1 16
2 3 5
2 1 5
2 1 3

```
### 样例输出 #1
```
21
20
4
20

```
## 提示

子任务：对于 $ 50\% $ 的数据，没有修改操作。


---

---
title: "[ONTAK2015] Związek Harcerstwa Bajtockiego"
layout: "post"
diff: 提高+/省选-
pid: P8025
tag: ['2015', '最近公共祖先 LCA', '树链剖分']
---
# [ONTAK2015] Związek Harcerstwa Bajtockiego
## 题目描述

给定一棵 $n$ 个点的无根树，相邻的点之间的距离为 $1$，一开始你位于 $m$ 点。之后你将依次收到 $k$ 个指令，每个指令包含两个整数 $d$ 和 $t$，你需要沿着最短路在 $t$ 步之内（包含 $t$ 步）走到 $d$ 点，如果不能走到，则停在最后到达的那个点。请在每个指令之后输出你所在的位置。
## 输入格式

第一行，三个整数 $n, m, k$；

接下来 $n - 1$ 行，每行两个整数 $x, y$，表示一条树边；

接下来 $k$ 行，每行两个整数 $d, t$，表示一条指令。
## 输出格式

一行，$k$ 个整数，表示执行对应指令后你所在的位置。
## 样例

### 样例输入 #1
```
3 1 2
1 2
2 3
3 4
1 1
```
### 样例输出 #1
```
3 2
```
## 提示

对于 $100\%$ 的数据，$1 \leq m \leq n \leq 10^6$，$1 \leq k \leq 10^6$，$1 \leq x, y, d \leq n$，$0 \leq t \leq 10^9$。


---

---
title: "[NAPC-#1] rStage5 - Hard Conveyors"
layout: "post"
diff: 提高+/省选-
pid: P9432
tag: ['O2优化', '最近公共祖先 LCA', '树链剖分']
---
# [NAPC-#1] rStage5 - Hard Conveyors
## 题目背景

**本题新增两组 hack 数据。**

---
![](https://cdn.luogu.com.cn/upload/image_hosting/bp1ypbgf.png)

更硬，所以可能就更脆，所以更容易被击破（确信）。

您只花了两个小时就秒掉了正城 s1~s10，来秒逆城了。
## 题目描述

**本题与 Stage5 的区别是合法路径定义不同**（简要题意中加粗部分不同）。~~（其实还有：样例不同，数据不同，部分分不同。）~~

### 【简要题意】

给定一棵 $n$ 个节点的无根树以及树上的 $k$ 个关键节点，边有边权（即边的长度）。$q$ 次询问，每次给出 $s,t$，问从 $s$ 到 $t$ 且经过**至少一个**关键节点的路径的最短长度。
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
7 6 2
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
2 2
```
### 样例输出 #1
```
8
3
7
6
2
0
```
## 提示

### 【数据范围】

upd at `2023-6-25`：新增了两组 hack 数据，将其置于 $\text{Sub}\textsf6$ 中，不记分数。

**本题采用捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c|c}
\textbf{Subtask} & \text{测试点编号} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1&1\sim2 & k=n & 5 \r
\textsf2&16\sim20 &k=1,n\leqslant10^3,q\leqslant10^3 & 15 \r
\textsf3&21\sim25 & n\leqslant10^3,q\leqslant10^3 & 15 \r
\textsf4&3\sim7 & q=1 & 15 \r
\textsf5&8\sim15 & - & 50 \r
\textsf6&26\sim27 & - & 0 \r
\end{array}
$$

对于 $100\%$ 的数据，$1\leqslant n\leqslant 10^5$，$1\leqslant q\leqslant 10^5$，$1\leqslant k\leqslant n$，$1\leqslant w\leqslant 10^4$，$1\leqslant u,v,s,t\leqslant n$。

### 【样例解释 #1】
![](https://cdn.luogu.com.cn/upload/image_hosting/3hvr33bz.png)

图中加粗节点表示关键点。

对于每组询问，以下为一种最优路径（最优路径可能有多条）：
1. $2\to1\to3$。
2. $2\to1$。
3. $7\to1\to2\to1$。
4. $4\to3\to5$。
5. $6\to2\to6$。
6. $2$（合法路径可以不经过任何边，此时路径长为 $0$）。


---

