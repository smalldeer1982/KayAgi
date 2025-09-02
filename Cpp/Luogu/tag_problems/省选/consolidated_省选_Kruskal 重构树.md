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
title: "[USACO17OPEN] Switch Grass P"
layout: "post"
diff: 省选/NOI-
pid: P3665
tag: ['2017', '线段树', 'USACO', 'Kruskal 重构树', '生成树']
---
# [USACO17OPEN] Switch Grass P
## 题目描述

Farmer John has recently been experimenting with cultivating different types of grass on his farm, realizing that different types of cows like different types of grass. However, he must be careful to ensure that different types of grass are planted sufficiently far away from each-other, in order to prevent them from being inextricably mixed.


FJ's farm consists of $N$ fields ($1 \leq N \leq 200,000$), where $M$ pairs of  fields are connected by bi-directional pathways ($1 \leq M \leq 200,000$).  Using these pathways, it is possible to walk from any field to any other field. Each pathway has an integer length in the range $1 \ldots 1,000,000$. Any pair of fields will be linked by at most one direct pathway.


In each field, FJ initially plants one of $K$ types of grass ($1 \leq K \leq N$). Over time, however, he might decide to switch the grass in some field to a different type. He calls this an "update"  peration. He might perform several updates over the course of time, which are all cumulative in nature.


After each update, FJ would like to know the length of the shortest path between two fields having different grass types. That is, among all pairs of fields having different grass types, he wants to know which two are closest. Ideally,

this number is large, so he can prevent grass of one type from mixing with grass of another type. It is guaranteed that the farm will always have at least two fields with different grass types.


In 30 percent of the input cases, each field will be directly connected to at most 10 pathways.



## 输入格式

The first line of input contains four integers, $N$, $M$, $K$, and $Q$, where $Q$ is the number of updates ($1 \leq Q \leq 200,000$).

The next $M$ lines describe the paths; each one contains three integers $A$, $B$, and $L$, indicating a path from field $A$ to field $B$ (both integers in the range $1 \ldots N$) of length $L$.

The next line indicates the initial type of grass growing in each field ($N$ integers in the range $1 \ldots K$).

Finally, the last $Q$ lines each describe an update, specified by two integers $A$ and $B$, where the grass in field $A$ is to be updated to type $B$.

## 输出格式

For each update, print the length of the shortest path between two fields with different types of grass, after the update is applied.

## 样例

### 样例输入 #1
```
3 2 3 4
1 2 3
2 3 1
1 1 2
3 3
2 3
1 2
2 2
```
### 样例输出 #1
```
1
3
3
1
```
## 题目翻译

### 题目描述

Farmer John 最近在他的农场尝试种植不同类型的草，发现不同类型的奶牛喜欢不同类型的草。然而，他必须小心确保不同类型的草种植得足够远，以防止它们不可分割地混合在一起。

FJ 的农场由 $N$ 块田地组成（$1 \leq N \leq 200,000$），其中 $M$ 对田地通过双向路径连接（$1 \leq M \leq 200,000$）。使用这些路径，可以从任何田地走到任何其他田地。每条路径的长度是一个在 $1 \ldots 1,000,000$ 范围内的整数。任何一对田地之间最多只有一条直接路径。

在每块田地中，FJ 最初种植了 $K$ 种草中的一种（$1 \leq K \leq N$）。然而，随着时间的推移，他可能会决定将某块田地的草更换为另一种类型。他称这种操作为“更新”操作。他可能会在一段时间内执行多次更新，这些更新都是累积性质的。

每次更新后，FJ 想知道种植不同草类型的两块田地之间的最短路径长度。也就是说，在所有种植不同草类型的田地对中，他希望知道哪两块田地最接近。理想情况下，这个数字应该较大，以便他可以防止一种类型的草与另一种类型的草混合。保证农场中始终至少有两块田地种植不同的草类型。

在 30% 的输入案例中，每块田地最多直接连接 10 条路径。

### 输入格式

输入的第一行包含四个整数 $N$、$M$、$K$ 和 $Q$，其中 $Q$ 是更新的次数（$1 \leq Q \leq 200,000$）。

接下来的 $M$ 行描述路径；每行包含三个整数 $A$、$B$ 和 $L$，表示从田地 $A$ 到田地 $B$（两者都是 $1 \ldots N$ 范围内的整数）的长度为 $L$ 的路径。

接下来的一行表示每块田地最初种植的草类型（$N$ 个 $1 \ldots K$ 范围内的整数）。

最后，最后的 $Q$ 行每行描述一个更新，由两个整数 $A$ 和 $B$ 指定，表示将田地 $A$ 的草更新为类型 $B$。

### 输出格式

对于每次更新，输出更新后种植不同草类型的两块田地之间的最短路径长度。


---

---
title: "[NOI2018] 归程"
layout: "post"
diff: 省选/NOI-
pid: P4768
tag: ['2018', '并查集', 'Kruskal 重构树', 'NOI', 'O2优化', '最短路', '可持久化']
---
# [NOI2018] 归程
## 题目描述

本题的故事发生在魔力之都，在这里我们将为你介绍一些必要的设定。

魔力之都可以抽象成一个 $n$ 个节点、$m$ 条边的无向连通图（节点的编号从 $1$ 至 $n$）。我们依次用 $l,a$ 描述一条边的**长度、海拔**。

作为季风气候的代表城市，魔力之都时常有雨水相伴，因此道路积水总是不可避免的。由于整个城市的排水系统连通，因此**有积水的边一定是海拔相对最低的一些边**。我们用**水位线**来描述降雨的程度，它的意义是：所有海拔**不超过**水位线的边都是**有积水**的。

Yazid 是一名来自魔力之都的 OIer，刚参加完 ION2018 的他将踏上归程，回到他温暖的家。Yazid 的家恰好在魔力之都的 $1$ 号节点。对于接下来 $Q$ 天，每一天 Yazid 都会告诉你他的出发点 $v$ ，以及当天的水位线 $p$。

每一天，Yazid 在出发点都拥有一辆车。这辆车由于一些故障不能经过有积水的边。Yazid 可以在任意节点下车，这样接下来他就可以步行经过有积水的边。但车会被留在他下车的节点并不会再被使用。
需要特殊说明的是，第二天车会被重置，这意味着：
- 车会在新的出发点被准备好。
- Yazid 不能利用之前在某处停放的车。

Yazid 非常讨厌在雨天步行，因此他希望在完成回家这一目标的同时，最小化他**步行经过的边**的总长度。请你帮助 Yazid 进行计算。

本题的部分测试点将强制在线，具体细节请见【输入格式】和【子任务】。
## 输入格式

单个测试点中包含多组数据。输入的第一行为一个非负整数 $T$，表示数据的组数。

接下来依次描述每组数据，对于每组数据：

第一行 $2$ 个非负整数 $n,m$，分别表示节点数、边数。

接下来 $m$ 行，每行 $4$ 个正整数 $u, v, l, a$，描述一条连接节点 $u, v$ 的、长度为 $l$、海拔为 $a$ 的边。
在这里，我们保证 $1 \leq u,v \leq n$。

接下来一行 $3$ 个非负数 $Q, K, S$ ，其中 $Q$ 表示总天数，$K \in {0,1}$ 是一个会在下面被用到的系数，$S$ 表示的是可能的最高水位线。

接下来 $Q$ 行依次描述每天的状况。每行 $2$ 个整数 $v_0,  p_0$ 描述一天：
- 这一天的出发节点为 $v = (v_0 + K \times \mathrm{lastans} - 1) \bmod n + 1$。    
- 这一天的水位线为 $p = (p_0 + K \times \mathrm{lastans}) \bmod (S + 1)$。    

其中 $\mathrm{lastans}$ 表示上一天的答案（最小步行总路程）。特别地，我们规定第 $1$ 天时 $\mathrm{lastans} = 0$。 
在这里，我们保证 $1 \leq v_0 \leq n$，$0 \leq p_0 \leq S$。

对于输入中的每一行，如果该行包含多个数，则用单个空格将它们隔开。
## 输出格式

依次输出各组数据的答案。对于每组数据：

- 输出 $Q$ 行每行一个整数，依次表示每天的最小步行总路程。
## 样例

### 样例输入 #1
```
1
4 3
1 2 50 1
2 3 100 2
3 4 50 1
5 0 2
3 0
2 1
4 1
3 1
3 2
```
### 样例输出 #1
```
0
50
200
50
150
```
### 样例输入 #2
```
1
5 5
1 2 1 2
2 3 1 2
4 3 1 2
5 3 1 2
1 5 2 1
4 1 3
5 1
5 2
2 0
4 0
```
### 样例输出 #2
```
0
2
3
1
```
## 提示

### 更多样例

更多样例请在附加文件中下载。

#### 样例 3

见附加文件中的 `return3.in` 与 `return3.ans`。

该样例满足海拔为一种，且不强制在线。

#### 样例 4

见附加文件中的 `return4.in` 与 `return4.ans`。

该样例满足图形态为一条链，且强制在线。

#### 样例 5

见附加文件中的 `return5.in` 与 `return5.ans`。

该样例满足不强制在线。

### 样例 1 解释

第一天没有降水，Yazid 可以坐车直接回到家中。

第二天、第三天、第四天的积水情况相同，均为连接 1，2 号节点的边、连接 3，4 号点的边有积水。

对于第二天，Yazid 从 2 号点出发坐车只能去往 3 号节点，对回家没有帮助。因此 Yazid 只能纯靠徒步回家。

对于第三天，从 4 号节点出发的唯一一条边是有积水的，车也就变得无用了。Yazid 只能纯靠徒步回家。

对于第四天，Yazid 可以坐车先到达 2 号节点，再步行回家。

第五天所有的边都积水了，因此 Yazid 只能纯靠徒步回家。

### 样例 2 解释

本组数据强制在线。

第一天的答案是 $0$，因此第二天的 $v=\left( 5+0-1\right)\bmod 5+1=5$，$p=\left(2+0\right)\bmod\left(3+1\right)=2$。

第二天的答案是 $2$，因此第三天的 $v=\left( 2+2-1\right)\bmod 5+1=4$，$p=\left(0+2\right)\bmod\left(3+1\right)=2$。

第三天的答案是 $3$，因此第四天的 $v=\left( 4+3-1\right)\bmod 5+1=2$，$p=\left(0+3\right)\bmod\left(3+1\right)=3$。

### 数据范围与约定

所有测试点均保证 $T\leq 3$，所有测试点中的所有数据均满足如下限制：

- $n\leq 2\times 10^5$，$m\leq 4\times 10^5$，$Q\leq 4\times 10^5$，$K\in\left\{0,1\right\}$，$1\leq S\leq 10^9$。
- 对于所有边：$l\leq 10^4$，$a\leq 10^9$。
- 任意两点之间都直接或间接通过边相连。

**为了方便你快速理解，我们在表格中使用了一些简单易懂的表述。在此，我们对这些内容作形式化的说明：**

- 图形态：对于表格中该项为 “一棵树” 或 “一条链” 的测试点，保证 $m = n-1$。除此之外，这两类测试点分别满足如下限制：
  - 一棵树：保证输入的图是一棵树，即保证边不会构成回路。
  - 一条链：保证所有边满足 $u + 1 = v$。
- 海拔：对于表格中该项为 “一种” 的测试点，保证对于所有边有 $a = 1$。
- 强制在线：对于表格中该项为 “是” 的测试点，保证 $K = 1$；如果该项为 “否”，则有 $K = 0$。
- 对于所有测试点，如果上述对应项为 “不保证”，则对该项内容不作任何保证。

$n$|$m$|$Q=$|测试点|形态|海拔|强制在线
-|-|-|-|-|-|-
$\leq 1$|$\leq 0$|$0$|1|不保证|一种|否
$\leq 6$|$\leq 10$|$10$|2|不保证|一种|否
$\leq 50$|$\leq 150$|$100$|3|不保证|一种|否
$\leq 100$|$\leq 300$|$200$|4|不保证|一种|否
$\leq 1500$|$\leq 4000$|$2000$|5|不保证|一种|否
$\leq 200000$|$\leq 400000$|$100000$|6|不保证|一种|否
$\leq 1500$|$=n-1$|$2000$|7|一条链|不保证|否
$\leq 1500$|$=n-1$|$2000$|8|一条链|不保证|否
$\leq 1500$|$=n-1$|$2000$|9|一条链|不保证|否
$\leq 200000$|$=n-1$|$100000$|10|一棵树|不保证|否
$\leq 200000$|$=n-1$|$100000$|11|一棵树|不保证|是
$\leq 200000$|$\leq 400000$|$100000$|12|不保证|不保证|否
$\leq 200000$|$\leq 400000$|$100000$|13|不保证|不保证|否
$\leq 200000$|$\leq 400000$|$100000$|14|不保证|不保证|否
$\leq 1500$|$\leq 4000$|$2000$|15|不保证|不保证|是
$\leq 1500$|$\leq 4000$|$2000$|16|不保证|不保证|是
$\leq 200000$|$\leq 400000$|$100000$|17|不保证|不保证|是
$\leq 200000$|$\leq 400000$|$100000$|18|不保证|不保证|是
$\leq 200000$|$\leq 400000$|$400000$|19|不保证|不保证|是
$\leq 200000$|$\leq 400000$|$400000$|20|不保证|不保证|是



---

---
title: "最小度限制生成树"
layout: "post"
diff: 省选/NOI-
pid: P5633
tag: ['图论', 'Kruskal 重构树', '凸完全单调性（wqs 二分）', '生成树']
---
# 最小度限制生成树
## 题目描述

给你一个有 $n$ 个节点，$m$ 条边的带权无向图，你需要求得一个生成树，使边权总和最小，且满足编号为 $s$ 的节点正好连了 $k$ 条边。
## 输入格式

第一行四个数：$n,m,s,k$

下面的 $m$ 行，每行三个整数：$u,v,w$，表示有一条 $u$ 连向 $v$ 权值为 $w$ 的边。
## 输出格式

输出一个数：满足要求的生成树的总边权。

可能会出现无解的情况，如果无解，则输出 `Impossible`。
## 样例

### 样例输入 #1
```
5 7 1 1
1 3 1
2 1 5
4 2 3
2 5 4
5 1 2
3 5 7
4 1 6
```
### 样例输出 #1
```
15
```
## 提示

### 数据范围

对于 $20\%$ 的数据，$n \le 10$，$m \le 30$。  
对于 $50\%$ 的数据，$n \le 1000$，$m \le 5000$。  
对于 $100\%$ 的数据，$1\leq s \leq n \le 5\times 10^4$，$1\leq m \le 5\times 10^5 $，$1\leq k \le 100$，$0\leq w\leq 3\times 10^4$。

### 注意

本题设有 hack 数据（Subtask $2$），计 $0$ 分，但若没有通过 hack 数据则不算通过本题。


---

---
title: "[ONTAK2010] Peaks 加强版"
layout: "post"
diff: 省选/NOI-
pid: P7834
tag: ['2010', '倍增', 'Kruskal 重构树', '深度优先搜索 DFS', '可持久化线段树']
---
# [ONTAK2010] Peaks 加强版
## 题目背景

原题链接：[P4197 Peaks](https://www.luogu.com.cn/problem/P4197)
## 题目描述

给定一张 $n$ 个点、$m$ 条边的无向图，第 $i$ 个点的权值为 $a_i$，边有边权。

有 $q$ 组询问，每组询问给定三个整数 $u, x, k$，求从 $u$ 开始只经过权值 $\leq x$ 的边所能到达的权值第 $k$ 大的点的权值，如果不存在输出 $-1$。

**本题强制在线。即：每次查询输入的是 $u', x', k'$，则 $u = (u' \operatorname{xor} \text{lastans}) \bmod n + 1$，$k$ 的解密方式与之相同，$x = x' \operatorname{xor} \text{lastans}$**。
## 输入格式

第一行，三个整数 $n, m, q$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$；

接下来 $m$ 行，每行三个整数 $s, t, w$，表示一条边的两个端点和权值；

接下来 $q$ 行，每行三个整数 $u', x', k'$。

**注意：处理第一组数据和无解时的 $\text{lastans} = 0$。**
## 输出格式

对于每组询问，输出一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
10 11 3
1 2 3 4 5 6 7 8 9 10
1 4 4
2 5 3
9 8 2
7 8 10
7 1 4
6 7 1
6 4 8
2 1 5
10 8 10
3 4 7
3 4 6
0 5 5
1 6 8
7 8 1
```
### 样例输出 #1
```
1
-1
8
```
## 提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq m, q \leq 5 \times 10^5$，$1 \leq s, t \leq n$，$1 \leq a_i, w \leq 10^9$，$0 \leq u', x', k' < 2^{31}$。


---

---
title: "[USACO23DEC] A Graph Problem P"
layout: "post"
diff: 省选/NOI-
pid: P9984
tag: ['线段树', 'USACO', '并查集', '2023', 'Kruskal 重构树', 'O2优化', '哈希 hashing', '启发式合并']
---
# [USACO23DEC] A Graph Problem P
## 题目描述

为了丰富自己的数学知识，Bessie 选修了一门图论课程，她发现她被下面的问题困住了，请帮帮她！

给出一张连通的无向图，包含编号为 $1\dots N$ 的节点和编号为 $1\dots M$（$2 \le N \le 2\cdot 10^5$，$N - 1 \le M \le 4 \cdot 10^5$）的边，下边的操作将被实施：

1. 假设集合 $S=\{v\}$，变量 $h=0$。
2. 当 $|S|<N$，重复执行：
	1. 仅有一个顶点在集合 $S$ 中的边中，找到编号最小的那条，编号记为 $e$。
    2. 将 $e$ 不在 $S$ 中的那个顶点加入集合 $S$。
    3. 将 $h$ 修改为 $10h+e$。
3. 返回 $h$ 对 $10^9+7$ 取模的值。

输出这个过程的全部返回值。
## 输入格式

第一行包含 $N$ 和 $M$。接下来 $M$ 行，每行包含第 $e$ 条边的顶点 $(a_e,b_e)$，保证图连通，没有重边。
## 输出格式

输出 $N$ 行，第 $i$ 行包含在节点 $i$ 开始过程的返回值。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
```
### 样例输出 #1
```
12
12
21
```
### 样例输入 #2
```
5 6
1 2
3 4
2 4
2 3
2 5
1 5
```
### 样例输出 #2
```
1325
1325
2315
2315
5132
```
### 样例输入 #3
```
15 14
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
```
### 样例输出 #3
```
678925929
678925929
678862929
678787329
678709839
678632097
178554320
218476543
321398766
431520989
542453212
653475435
764507558
875540761
986574081
```
## 提示

### 样例解释 2

考虑在 $i=3$ 开始执行。首先，选择 $2$ 号边，$S=\{3,4\}$，$h=2$。然后，选择 $3$ 号边，$S=\{2,3,4\}$，$h=23$。接着，选择 $1$ 号边，$S=\{1,2,3,4\}$，$h=231$。最后，选择 $5$ 号边，$S=\{1,2,3,4,5\}$，$h=2315$。因此，$i=3$ 的答案是 $2315$。

### 样例解释 3

确保答案对 $10^9+7$ 取模。

### 测试点性质

- 测试点 $4$ 满足 $N,M \le 2000$。
- 测试点 $5-6$ 满足 $N \le 2000$。
- 测试点 $7-10$ 满足 $N \le 10000$。
- 测试点 $11-14$ 满足对于所有边，有 $a_e+1=b_e$。
- 测试点 $15-23$ 没有额外限制。


---

