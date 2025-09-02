---
title: "符卡对决"
layout: "post"
diff: 省选/NOI-
pid: P10268
tag: ['莫队', '并查集']
---
# 符卡对决
## 题目背景

灵梦正在和魔理沙进行符卡对决。

![Card](https://cdn.luogu.com.cn/upload/image_hosting/xu68nj8k.png)

> 永夜の报い，Pixiv76062895，作者是 minusT，侵删。
## 题目描述

灵梦一共有 $n$ 张符卡，每张卡都有一个能力值，对于第 $i$ 张卡，它的能力值为 $a_i$，现在她想从中选出两张符卡并使用它们，灵梦发现，如果她同时打出了两张符卡 $i, j$，这两张符卡造成的伤害将会是 $a_i\times a_j$。

这些符卡之间有能力的冲突，灵梦会告诉你这些符卡的兼容性，具体而言这些符卡之间有 $m$ 条关系，这些关系表明某两张符卡之间是兼容的，**注意**，如果符卡 $i, j$ 兼容且符卡 $j, k$ 兼容，那么符卡 $i, k$ 也是兼容的，如果打出的两张符卡之间不是兼容的，那么它们造成的伤害为 $0$。

她很好奇符卡之间的兼容性会造成什么样的影响，所以她会询问你 $q$ 次，每次告诉你一对正整数 $l, r$，意味着只有编号在区间 $[l, r]$ 内的关系才会生效。

灵梦不想把魔理沙虐得太惨，所以她会随机从所有符卡中选出两张**不同**的符卡来打出，她想知道每次询问造成的伤害的期望值对 $10^9 + 7$ 取模后是多少。
## 输入格式

第一行三个整数 $n, m, q$ 分别表示符卡总数，符卡间的关系总数，灵梦的询问次数。

接下来一行 $n$ 个正整数，第 $i$ 个表示 $a_i$。

接下来 $m$ 行，每行两个正整数 $u_i, v_i$，表示第 $u_i$ 张符卡与第 $v_i$ 张符卡是兼容的。

接下来 $q$ 行，每行两个正整数 $l_i, r_i$，表示灵梦询问的编号区间 $[l_i, r_i]$。
## 输出格式

一共 $q$ 行，第 $i$ 行一个整数，表示第 $i$ 次询问中，随机选择两张**不同**的符卡，造成伤害的期望值对 $10^9 + 7$ 取模后的结果。
## 样例

### 样例输入 #1
```
4 4 4
5 8 2 7 
3 1
1 4
3 2
1 4
2 4
1 2
2 3
3 3
```
### 样例输出 #1
```
500000012
833333349
500000012
666666674
```
### 样例输入 #2
```
14 16 15
1 2 7 3 2 4 6 2 5 7 2 4 3 3 
5 12
2 9
2 10
7 10
6 12
12 3
11 1
4 8
1 13
6 8
6 10
4 1
1 10
12 11
3 5
9 7
14 14
2 16
5 6
2 3
5 10
1 6
5 16
13 15
1 2
3 7
3 4
14 14
3 7
6 7
11 14
```
### 样例输出 #2
```
318681321
263736277
868131875
725274731
32967035
384615390
637362648
780219786
967032974
406593411
208791211
318681321
406593411
945054952
681318687
```
## 提示

#### 样例 1 解释

对于第三组询问，只有 $(1, 4), (2, 3)$ 两对符卡之间是兼容的。

如果选择的符卡是 $(1, 2)$，那么它们不兼容，伤害值为 $0$，这种情况的概率是 $\dfrac16$。

如果选择的符卡是 $(1, 3)$，那么它们不兼容，伤害值为 $0$，这种情况的概率是 $\dfrac16$。

如果选择的符卡是 $(1, 4)$，它们兼容，伤害值为 $a_1\times a_4 = 35$，这种情况的概率是 $\dfrac16$。

如果选择的符卡是 $(2, 3)$，它们兼容，伤害值为 $a_2\times a_3 = 16$，这种情况的概率是 $\dfrac16$。

如果选择的符卡是 $(2, 4)$，那么它们不兼容，伤害值为 $0$，这种情况的概率是 $\dfrac16$。

以此类推，最终的期望值是 $\dfrac{17}{2}$，其在模 $10^9 + 7$ 意义下等于 $500000012$。

#### 数据范围

**本题采用捆绑测试。**

对于所有数据，$1\le n, q\le 10^5, 1\le m\le 2n, 1\le a_i\le 10^9, 1\le l_i\le r_i\le m, 1\le u_i, v_i\le n$。

对于不同的子任务，我们如下约定：

| 子任务编号 | $n$         | $q$         | 特殊性质 | 子任务分值 |
| ---------- | ----------- | ----------- | -------- | ---------- |
| $0$        | $\le300$    | $\le300$    | 无       | $5$        |
| $1$        | $\le 2000$  | $\le 2000$  | A        | $10$       |
| $2$        | $\le 2000$  | $\le 2000$  | B        | $5$       |
| $3$        | $\le 2000$  | $\le 2000$  | 无       | $10$       |
| $4$        | $\le 30000$ | $\le 30000$ | 无       | $10$       |
| $5$        | $\le 50000$ | $\le 50000$ | A        | $10$       |
| $6$        | $\le 50000$ | $\le 50000$ | B        | $10$       |
| $7$        | $\le 50000$ | $\le 50000$ | 无       | $15$       |
| $8$        | $\le 10^5$  | $\le 10^5$  | 无       | $25$       |

- **特殊性质 A**：保证 $u_i = 1, v_i = i + 1, m = n - 1$。
- **特殊性质 B**：保证 $l_i = 1$。



---

---
title: "[AMPPZ2013] Bytehattan"
layout: "post"
diff: 省选/NOI-
pid: P10665
tag: ['图论', '并查集', 'O2优化']
---
# [AMPPZ2013] Bytehattan
## 题目描述

比特哈顿镇有 $n\times n$ 个格点，形成了一个网格图。一开始整张图是完整的。

有 $k$ 次操作，每次会删掉图中的一条边 $(u,v)$，你需要回答在删除这条边之后 $u$ 和 $v$ 是否仍然连通。
## 输入格式

第一行包含两个正整数 $n,k(2\leq n\leq 1500,1\leq k\leq 2n(n-1))$，表示网格图的大小以及操作的个数。

接下来 $k$ 行，每行包含两条信息，每条信息包含两个正整数 $a,b(1\leq a,b\leq n)$ 以及一个字符 $c$（$c$ 为 `N` 或者 `E`）。

如果 $c$ 为 `N`，表示删除 $(a,b)$ 到 $(a,b+1)$ 这条边；如果 $c$ 为 `E`，表示删除 $(a,b)$ 到 $(a+1,b)$ 这条边。

数据进行了加密，对于每个操作，如果上一个询问回答为 TAK 或者这是第一个操作，那么只考虑第一条信息，否则只考虑第二条信息。数据保证每条边最多被删除一次。
## 输出格式

输出 $k$ 行，对于每个询问，如果仍然连通，输出 TAK，否则输出 NIE。
## 样例

### 样例输入 #1
```
3 4
2 1 E 1 2 N
2 1 N 1 1 N
3 1 N 2 1 N
2 2 N 1 1 N
```
### 样例输出 #1
```
TAK
TAK
NIE
NIE
```
## 提示

数据保证，$2\leq n\leq 1500$，$1\leq k\leq 2n(n-1)$，$1\leq a,b\leq n$。


---

---
title: "[HBCPC2024] Colorful Tree"
layout: "post"
diff: 省选/NOI-
pid: P10866
tag: ['并查集', '2024', 'O2优化', 'XCPC', '湖北']
---
# [HBCPC2024] Colorful Tree
## 题目描述

You are given a tree with $n$ nodes numbered from $1$ to $n$ and $n - 1$ edges. Each node has a color. Initially, all of them are white. 

We are going to perform $q$ operations. In each operation, two vertices $u$ and $v$ will be given, and we will color black to the points along the simple path from $u$ to $v$ ($u,v$ inclusive). Note that a simple path in the tree is defined as a path that does not pass through any vertex more than once.

After each operation, you are required to determine the length of the longest simple path in the tree where all nodes on the path are the same color. The length of a path is defined as the number of nodes on the path.
## 输入格式

The first line contains a single integer $T$ ($1 \le T \le 100$) indicating the number of test cases.

For each test case, the first line contains two integers $n$ ($1 \le n \le 2\times 10^5$) and $q$ ($1 \le q \le 2\times 10^5$), indicating the number of nodes in the tree and the number of operations, respectively.

In the following $n-1$ lines, each contains two integers $u$ and $v$, representing an edge from vertex $u$ to $v$ in the tree.

Then follow $q$ lines, each contains two integers $u$ and $v$, representing an operation that colors black to the points along the path from vertex $u$ to $v$.

It is guaranteed that the sum of $n$ and $q$ of all the test cases in a test does not exceed $2\times 10^5$ respectively.
## 输出格式

For each test case, output $q$ lines, each line should contain an integer representing the length of the longest simple path in the tree where all nodes on the path are the same color after the corresponding operation.
## 样例

### 样例输入 #1
```
1
8 6
1 2
1 3
2 4
4 5
2 6
4 8
3 7
4 8
7 7
4 5
2 2
4 6
5 1
```
### 样例输出 #1
```
5
4
4
3
4
4
```
## 题目翻译

### 题目描述

给你一棵有 $n$ 个节点的树，节点编号从 $1$ 到 $n$，并且有 $n-1$ 条边。每个节点都有一个颜色。起初，所有节点的颜色都是白色。

我们将进行 $q$ 次操作。在每次操作中，会给出两个顶点 $u$ 和 $v$，然后我们将沿着从 $u$ 到 $v$ 的简单路径上的所有节点（包括 $u$ 和 $v$）染成黑色。注意，树中的简单路径定义为路径上的任意顶点都不会被重复经过。

在每次操作之后，你需要确定树中最长的简单路径，其路径上的所有节点的颜色相同。路径的长度定义为路径上的节点数目。

### 输入格式

第一行包含一个整数 $T$ ($1 \le T \le 100$)，表示测试用例的数量。

对于每个测试用例，第一行包含两个整数 $n$ ($1 \le n \le 2\times 10^5$) 和 $q$ ($1 \le q \le 2\times 10^5$)，分别表示树中节点的数量和操作的数量。

紧接着$^{(1)}$的 $n-1$ 行中，每行包含两个整数 $u$ 和 $v$，表示树中顶点 $u$ 和 $v$ 之间的一条边。

接下来 $q$ 行，每行包含两个整数 $u$ 和 $v$，表示将从顶点 $u$ 到顶点 $v$ 的路径上的所有节点染成黑色的操作。

保证一个测试中所有测试用例的 $n$ 和 $q$ 的总和均不超过 $2\times 10^5$。$^{(2)}$

注释：
- (1):也可以译为接下来，此处译者只是想区分下条的语句。
- (2)可以用以下数学表达式表示：

$$
\sum_{i=1}^{T} n_i \leq 2 \times 10^5 \quad \text{且} \quad \sum_{i=1}^{T} q_i \leq 2 \times 10^5
$$

其中 $n_i$ 和 $q_i$ 分别表示第 $i$ 个测试用例中的节点数量和操作数量。

### 输出格式

对于每个测试用例，输出 $q$ 行，每行应包含一个整数，表示在执行相应操作后，树中所有节点颜色相同的最长简单路径的长度。


翻译者：[Immunoglobules](https://www.luogu.com.cn/user/1066251)


---

---
title: "[PA 2016] 构树 / Reorganizacja"
layout: "post"
diff: 省选/NOI-
pid: P11606
tag: ['2016', '并查集', '递归', 'Special Judge', '构造', 'PA（波兰）']
---
# [PA 2016] 构树 / Reorganizacja
## 题目背景

译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R2 Reorganizacja [A] (REO)。$\texttt{1s,256M}$。

## 题目描述

构造一棵 $n$ 个节点的有根树，满足 $m$ 条限制，形如「$x$ 必须是 $y$ 的祖先」或者「$x$ 必须不是 $y$ 的祖先」。

## 输入格式


第一行，两个整数 $n,m$。

接下来 $m$ 行，每行两个正整数和一个字符 $x,y,c$。其中 $x,y$ 为正整数，$c\in \{\texttt{T},\texttt{N}\}$，$x\neq y$。
- 若 $c=\texttt{T}$，表示 $y$ 必须是 $x$ 的祖先；
- 否则，表示 $y$ 必须不是 $x$ 的祖先。

保证不会重复给出同一条信息。
## 输出格式


若无解，输出一行一个 $\texttt{NIE}$；

否则输出 $n$ 行，每行一个整数，表示 $i$ 号点的父亲。

- 特别地，若 $i$ 是根，则规定其父亲为 $0$。
## 样例

### 样例输入 #1
```
4 4
4 1 T
4 2 T
3 2 N
4 3 N
```
### 样例输出 #1
```
0
1
1
2
```
### 样例输入 #2
```
2 2
1 2 N
2 1 N
```
### 样例输出 #2
```
NIE
```
## 提示



- $1\le n\le 10^3$；
- $0\le m\le \min(n(n-1), 10^4)$；
- $1\le x,y\le n$，$x\neq y$。

保证不会重复给出同一条信息。


---

---
title: "[POI 2016 R2] 圣诞灯链 Christmas chain"
layout: "post"
diff: 省选/NOI-
pid: P12736
tag: ['2016', '倍增', '并查集', 'POI（波兰）']
---
# [POI 2016 R2] 圣诞灯链 Christmas chain
## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5032)。
## 题目描述

**题目译自 [XXIII Olimpiada Informatyczna — II etap](https://sio2.mimuw.edu.pl/c/oi23-2/dashboard/) [Świąteczny łańcuch](https://szkopul.edu.pl/problemset/problem/cSa80AKpjHR8FlWE4BCpLGT3/statement/)**

每年圣诞节，Bajtazar 都会用五彩缤纷的灯链装点他的家。今年，他决定亲自挑选灯链的颜色，打造一串独一无二的装饰。他对灯链的美学有特定要求：某些灯链片段的颜色排列需与另一些片段完全相同。同时，他的妻子希望今年的灯链尽量丰富多彩，也就是说，灯链应包含尽可能多的不同颜色。请帮助 Bajtazar 计算，他需要购买多少种颜色的灯泡。
## 输入格式

第一行包含两个整数 $n, m$ $(n \geq 2, m \geq 1)$，分别表示灯链中灯泡的数量和 Bajtazar 的美学要求数量。灯泡按顺序编号为 $1$ 至 $n$。

接下来的 $m$ 行描述美学要求，每行包含三个整数 $a_i, b_i, l_i$ $(1 \leq a_i, b_i, l_i; a_i \neq b_i; a_i, b_i \leq n - l_i + 1)$，表示灯链片段 $\{a_i, \ldots, a_i + l_i - 1\}$ 和 $\{b_i, \ldots, b_i + l_i - 1\}$ 应具有相同颜色。即，灯泡 $a_i$ 与 $b_i$ 颜色相同，$a_i + 1$ 与 $b_i + 1$ 颜色相同，依此类推，直至 $a_i + l_i - 1$ 与 $b_i + l_i - 1$。
## 输出格式

输出一个正整数 $k$，表示满足所有美学要求时，灯链中可包含的最大不同颜色数。
## 样例

### 样例输入 #1
```
10 3
1 6 3
5 7 4
3 8 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4 2
1 2 2
2 3 2
```
### 样例输出 #2
```
1
```
## 提示

**样例 1 解释**

设 $a, b, c$ 表示三种不同颜色的灯泡。一个满足 Bajtazar 及其妻子要求的灯链为 $\texttt{abacbababa}$。

**附加样例**

1. $n=2000, m=2$，要求片段 $\{1, \ldots, 1000\}$ 与 $\{1001, \ldots, 2000\}$ 相同，$\{1, \ldots, 500\}$ 与 $\{501, \ldots, 1000\}$ 相同，最大颜色数为 $500$。
2. $n=500000, m=499900$，第 $i$ 个要求为 $a_i=i, b_i=i+100, l_i=1$，最大颜色数为 $100$。
3. $n=80000, m=79995$，第 $i$ 个要求为 $a_i=i, b_i=i+2, l_i=4$，最大颜色数为 $2$。
4. $n=50000, m=25000$，第 $i$ 个要求为 $a_i=1, b_i=i+1, l_i=9$，灯链只能使用单一颜色。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n, m \leq 2000$         | $30$ |
| $2$    | $n, m \leq 500000$，所有 $l_i = 1$ | $20$ |
| $3$    | $n, m \leq 80000$        | $30$ |
| $4$    | $n, m \leq 500000$       | $20$ |


---

---
title: "[GCJ 2019 #3] Datacenter Duplex"
layout: "post"
diff: 省选/NOI-
pid: P13121
tag: ['2019', '并查集', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2019 #3] Datacenter Duplex
## 题目描述

Two companies, Apricot Rules LLC and Banana Rocks Inc., are sharing the same datacenter. The datacenter is a matrix of $\mathbf{R}$ rows and $\mathbf{C}$ columns, with each cell containing a single server tower. Each tower contains intellectual property belonging to exactly one of the two companies.

At first, they built walls on the edges between cells assigned to different companies. This allowed orthogonally adjacent cells belonging to the same company to remain connected. Also, two cells $\mathbf{x}$ and $\mathbf{y}$ are considered connected if $\mathbf{x}$ is connected to a cell that is, directly or indirectly, connected to $\mathbf{y}$. With this definition, it was possible that two cells assigned to the same company were not connected, which was unacceptable.

Both companies agreed to build narrow hallways running through cell corners that allow two diagonally adjacent cells to be connected directly. Let us write $(\mathbf{i}, \mathbf{j})$ to represent the cell at row $\mathbf{i}$ and column $\mathbf{j}$. At most one narrow hallway can be built through any given vertex, which means either $(\mathbf{i}, \mathbf{j})$ and $(\mathbf{i} + 1, \mathbf{j} + 1)$ can be connected, or $(\mathbf{i} + 1, \mathbf{j})$ and $(\mathbf{i}, \mathbf{j} + 1)$ can be connected, or neither pair, but not both. Of course, only hallways between cells assigned to the same company can be built.

Given a matrix where each cell is labeled $\mathbf{A}$ or $\mathbf{B}$ depending on which company it is assigned to, find a way to add connections through diagonal adjacencies such that all $\mathbf{A}$s are connected and all $\mathbf{B}$s are connected.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case begins with one line containing two integers $\mathbf{R}$ and $\mathbf{C}$, the number of rows and columns of the matrix representing the datacenter. Then, there are $\mathbf{R}$ more lines containing $\mathbf{C}$ characters each. The $\mathbf{j}$-th character on the $\mathbf{i}$-th of these lines $\mathbf{M}
## 输出格式

For each test case, first output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is `IMPOSSIBLE` if there is no way to assign the diagonal connections such that the $\mathbf{A}$ cells are connected and the $\mathbf{B}$ cells are connected, or `POSSIBLE` otherwise. Then, if you output `POSSIBLE`, output $\mathbf{R} - 1$ more lines of $\mathbf{C} - 1$ characters each. These characters must correspond to a valid arrangement as described in the statement above. The $\mathbf{j}$-th character of the $\mathbf{i}$-th of those lines must be $\backslash$ if cells $(\mathbf{i}, \mathbf{j})$ and $(\mathbf{i} + 1, \mathbf{j} + 1)$ are to be connected, / if cells $(\mathbf{i} + 1, \mathbf{j})$ and $(\mathbf{i}, \mathbf{j} + 1)$ are to be connected, or . if neither pair is to be connected.
## 样例

### 样例输入 #1
```
3
2 2
AB
BA
2 3
AAB
ABB
3 4
BBAA
BABA
BBAA
```
### 样例输出 #1
```
Case #1: IMPOSSIBLE
Case #2: POSSIBLE
..
Case #3: POSSIBLE
//\
.//
```
## 提示

**Sample Explanation**

In Sample Case #1, the pair of A cells and the pair of B cells need to be connected, but since both connections would have to cross the same vertex, at most one of the connections can exist.

In Sample Case #2, the cells are already connected in the required way in the input, so no additional connections are necessary. Note that you can add unnecessary valid connections, so another valid answer would be `//`, but `\.` would be wrong.

In Sample Case #3, there are also multiple solutions, one of which is displayed.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{C} \leq 100$.
- $\mathbf{M}_{\mathbf{i}, \mathbf{j}}$ = uppercase A or uppercase B, for all $\mathbf{i}$ and $\mathbf{j}$.
- $\mathbf{M}_{\mathbf{i}, \mathbf{j}}$ = uppercase A for at least one pair of $\mathbf{i}$ and $\mathbf{j}$.
- $\mathbf{M}_{\mathbf{i}, \mathbf{j}}$ = uppercase B for at least one pair of $\mathbf{i}$ and $\mathbf{j}$.

**Test set 1 (10 Pts, Visible)**

- $2 \leq \mathbf{R} \leq 4$.

**Test set 2 (13 Pts, Hidden)**

- $2 \leq \mathbf{R} \leq 100$.


---

---
title: "[GCJ 2017 #3] Mountain Tour"
layout: "post"
diff: 省选/NOI-
pid: P13177
tag: ['贪心', '2017', '并查集', 'Google Code Jam']
---
# [GCJ 2017 #3] Mountain Tour
## 题目描述

You are on top of Mount Everest, and you want to enjoy all the nice hiking trails that are up there. However, you know from past experience that climbing around on Mount Everest alone is bad — you might get lost in the dark! So you want to go on hikes at pre-arranged times with tour guides.

There are $\mathbf{C}$ camps on the mountain (numbered 1 through $\mathbf{C}$), and there are $2 \times \mathbf{C}$ one-way hiking tours (numbered 1 through $2 \times \mathbf{C}$). Each hiking tour starts at one camp and finishes at a different camp, and passes through no other camps in between. Mount Everest is sparsely populated, and business is slow; there are exactly 2 hiking tours departing from each camp, and exactly 2 hiking tours arriving at each camp.

Each hiking tour runs daily. Tours 1 and 2 start at camp 1, tours 3 and 4 start at camp 2, and so on: in general, tour $2 \times i - 1$ and tour $2 \times i$ start at camp $i$. The $i$-th hiking tour ends at camp number $\mathbf{E}_i$, leaves at hour $\mathbf{L}_i$, and has a duration of exactly $\mathbf{D}_i$ hours.

It is currently hour 0; the hours in a day are numbered 0 through 23. You are at camp number 1, and you want to do each of the hiking tours exactly once and end up back at camp number 1. You cannot travel between camps except via hiking tours. While you are in a camp, you may wait for any number of hours (including zero) before going on a hiking tour, but you can only start a hiking tour at the instant that it departs.

After looking at the tour schedules, you have determined that it is definitely possible to achieve your goal, but you want to do it as fast as possible. If you plan your route optimally, how many hours will it take you to finish all of the tours?

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each begins with one line with an integer $\mathbf{C}$: the number of camps. Then, $2 \times \mathbf{C}$ more lines follow. The $i$-th of these lines (counting starting from 1) represents one hiking tour starting at camp number $\text{floor}((i + 1) / 2)$, and contains three integers $\mathbf{E}_i$, $\mathbf{L}_i$, and $\mathbf{D}_i$, as described above. Note that this format guarantees that exactly two tours start at each camp.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the minimum number of hours that it will take you to achieve your goal, as described above.
## 样例

### 样例输入 #1
```
2
2
2 1 5
2 0 3
1 4 4
1 6 3
4
3 0 24
2 0 24
4 0 24
4 0 24
2 0 24
1 0 24
3 0 24
1 0 24
```
### 样例输出 #1
```
Case #1: 32
Case #2: 192
```
## 提示

In sample case #1, the optimal plan is as follows:

- Wait at camp 1 for an hour, until it becomes hour 1.
- Leave camp 1 at hour 1 to take the 5 hour hiking tour; arrive at camp 2 at hour 6.
- Immediately leave camp 2 at hour 6 to take the 3 hour hiking tour; arrive at camp 1 at hour 9.
- Wait at camp 1 for 15 hours, until it becomes hour 0 of the next day.
- Leave camp 1 at hour 0 to take the 3 hour hiking tour; arrive at camp 2 at hour 3.
- Wait at camp 2 for 1 hour, until it becomes hour 4.
- Leave camp 2 at hour 4 to take the 4 hour hiking tour; arrive at camp 1 at hour 8.

This achieves the goal in 1 day and 8 hours, or 32 hours. Any other plan takes longer.

In sample case #2, all of the tours leave at the same time and are the same duration. After finishing any tour, you can immediately take another tour. If we number the tours from 1 to 8 in the order in which they appear in the test case, one optimal plan is: $1, 5, 4, 7, 6, 2, 3, 8$.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{E}_i \leq \mathbf{C}$.
- $\mathbf{E}_i \neq \text{ceiling}(i / 2)$, for all $i$. (No hiking tour starts and ends at the same camp.)
- $\text{size of } \{j : \mathbf{E}_j = i\} = 2$, for all $j$. (Exactly two tours end at each camp.)
- $0 \leq \mathbf{L}_i \leq 23$.
- $1 \leq \mathbf{D}_i \leq 1000$.
- There is at least one route that starts and ends at camp 1 and includes each hiking tour exactly once.

**Small dataset (6 Pts, Test Set 1 - Visible)**

- $2 \leq \mathbf{C} \leq 15$.

**Large dataset (24 Pts, Test Set 2 - Hidden)**

- $2 \leq \mathbf{C} \leq 1000$.


---

---
title: "[GCJ 2012 #3] Havannah"
layout: "post"
diff: 省选/NOI-
pid: P13329
tag: ['2012', '二分', '并查集', 'Google Code Jam']
---
# [GCJ 2012 #3] Havannah
## 题目背景

Havannah was created by Christian Freeling and MindSports. MindSports and Christian Freeling do not endorse and have no involvement with Google Code Jam.
## 题目描述

Havannah is an abstract strategy board game created by Christian Freeling. Havannah is a game played on a hexagonal board with $S$ hexagons to each side. Each hexagon has two horizontal and four slanted edges. The hexagons are identified by pairs of integer values. The hexagon in the bottom corner of the board is $(1, 1)$. The hexagon adjacent to $(x, y)$ in the direction of a two-o'clock hand is $(x, y+1)$. The hexagon adjacent to $(x, y)$ in the direction of a ten-o'clock hand is $(x + 1, y)$. Here is an example board with $S = 5$:

![](https://cdn.luogu.com.cn/upload/image_hosting/oegdj7r3.png)

In the game of Havannah, each hexagon can be occupied by at most one stone. Stones once put on the board are never removed or moved. The goal of the game is to build from stones a connected set of stones of one of three kinds. The winning structures are:

- A **ring** that encircles one or more empty hexagons. That is, at least one of the inner hexagons must be empty. More specifically, there is an empty hexagon that is separated from the outermost boundary of the board by hexagons with stones. Note that this rule is different from the official game Havannah.
- A **bridge** that connects any two corners of the board.
- A fork that connects any three of the board's six edges. Corners do not count as part of either adjacent edge.

This picture shows examples of winning structures:

![](https://cdn.luogu.com.cn/upload/image_hosting/iar2seqk.png)

Your program should determine whether a sequence of moves of a single player builds a winning structure. If so, it should output the name of the structure and the number of the move that completed it. If a move completes multiple rings, connects more than two corners, or connects more than three edges, the structure is still considered a ring, a bridge, or a fork, respectively. But if a move completes structures of different kinds at once, your program should output the names of all of them. We are only interested in the first winning move: ignore all moves following the winning one. If there is no winning structure on the board after playing all the moves from the sequence, your program should output none.
## 输入格式

The first line of input gives the number of test cases, $T$. $T$ test cases follow. The first line of each test case contains two integers $S$ and $M$, the number of hexagons on each side of the board and the number of moves in the sequence, respectively. The next $M$ lines provide the sequence of moves, in order, where each line contains a space-separated pair $(x, y)$ of hexagon identifiers. All the moves in the sequence lie on the board of size $S$. In each test case, the board is initially empty and the moves do not repeat.
## 输出格式

For each test case, output one line containing "Case #$n$: " followed by one of:

* none
* bridge in move $k$
* fork in move $k$
* ring in move $k$
* bridge-fork in move $k$
* bridge-ring in move $k$
* fork-ring in move $k$
* bridge-fork-ring in move $k$

The cases are numbered starting from 1. The moves are numbered starting from 1.
## 样例

### 样例输入 #1
```
7
2 4
1 1
1 2
2 3
3 3
3 6
2 1
2 2
2 3
2 4
1 2
4 4
3 7
3 3
2 2
2 3
3 4
4 4
4 3
3 2
3 6
2 2
2 3
3 4
4 4
4 3
3 2
3 8
1 1
2 1
1 3
2 4
1 2
3 2
3 3
3 4
3 7
1 1
2 2
3 5
3 4
5 3
4 3
3 3
3 3
1 1
1 3
3 5
```
### 样例输出 #1
```
Case #1: bridge in move 2
Case #2: fork in move 5
Case #3: none
Case #4: ring in move 6
Case #5: bridge-fork in move 5
Case #6: bridge in move 7
Case #7: none
```
## 提示

**Limits**

**Test set 1 (8 Pts, Visible Verdict)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq T \leq 200$
- $2 \leq S \leq 50$
- $0 \leq M \leq 100$

**Test set 2 (12 Pts, Hidden Verdict)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq T \leq 20$
- $2 \leq S \leq 3000$
- $0 \leq M \leq 10000$


---

---
title: "[NOI2015] 品酒大会"
layout: "post"
diff: 省选/NOI-
pid: P2178
tag: ['2015', '并查集', 'NOI', '后缀数组 SA']
---
# [NOI2015] 品酒大会
## 题目描述

一年一度的“幻影阁夏日品酒大会”隆重开幕了。大会包含品尝和趣味挑战 两个环节，分别向优胜者颁发“首席品酒家”和“首席猎手”两个奖项，吸引了众多品酒师参加。


在大会的晚餐上，调酒师 Rainbow 调制了 $n$ 杯鸡尾酒。这 $n$ 杯鸡尾酒排成一行，其中第 $n$ 杯酒 ($1 ≤ i ≤ n$) 被贴上了一个标签 $s_i$ ，每个标签都是 $26$ 个小写 英文字母之一。设 $str(l, r)$ 表示第 $l$ 杯酒到第 $r$ 杯酒的 $r - l + 1$ 个标签顺次连接构成的字符串。若 $str(p, p_0) = str(q, q_0)$，其中 $1 ≤ p ≤ p_0 ≤ n$, $1 ≤ q ≤ q_0 ≤ n$, $p ≠ q$，$p_0-p+1 = q_0 - q + 1 = r$ ，则称第 $p$ 杯酒与第 $q$ 杯酒是“ $r$ 相似” 的。当然两杯“ $r$ 相似”($r > 1$)的酒同时也是“ $1$ 相似”、“ $2$ 相似”、……、“ $(r - 1)$ 相似”的。特别地，对于任意的 $1 ≤ p ,q ≤ n,p  ≠  q$，第 $p$ 杯酒和第 $q$ 杯酒都 是“ $0$ 相似”的。


在品尝环节上，品酒师 Freda 轻松地评定了每一杯酒的美味度，凭借其专业的水准和经验成功夺取了“首席品酒家”的称号，其中第 $i$ 杯酒 ($1 ≤ i ≤ n$) 的 美味度为 $a_i$ 。现在 Rainbow 公布了挑战环节的问题：本次大会调制的鸡尾酒有一个特点，如果把第 $p$ 杯酒与第 $q$ 杯酒调兑在一起，将得到一杯美味度为 $a_p\times a_q$ 的 酒。现在请各位品酒师分别对于 $r = 0,1,2,⋯,n-1$ ，统计出有多少种方法可以 选出 $2$ 杯“ $r$ 相似”的酒，并回答选择 $2$ 杯“$r$ 相似”的酒调兑可以得到的美味度的最大值。

## 输入格式

第 $1$ 行包含 $1$ 个正整数 $n$ ，表示鸡尾酒的杯数。

第 $2$ 行包含一个长度为 $n$ 的字符串 $S$，其中第 $i$ 个字符表示第 $i$ 杯酒的标签。

第 $3$ 行包含 $n$ 个整数，相邻整数之间用单个空格隔开，其中第 $i$ 个整数表示第 $i$ 杯酒的美味度 $a_i$ 。

## 输出格式

包括 $n$ 行。

第 $i$ 行输出 $2$ 个整数，中间用单个空格隔开。第 $1$ 个整 数表示选出两杯“ $(i - 1)$ 相似”的酒的方案数，第 2 个整数表示选出两杯 “ $(i - 1)$ 相似”的酒调兑可以得到的最大美味度。若不存在两杯“ $(i - 1)$ 相似” 的酒，这两个数均为 $0$ 。

## 样例

### 样例输入 #1
```
10
ponoiiipoi
2 1 4 7 4 8 3 6 4 7
```
### 样例输出 #1
```
45 56
10 56
3 32
0 0
0 0
0 0
0 0
0 0
0 0
0 0
```
### 样例输入 #2
```
12
abaabaabaaba
1 -2 3 -4 5 -6 7 -8 9 -10 11 -12

```
### 样例输出 #2
```
66 120
34 120
15 55
12 40
9 27
7 16
5 7
3 -4
2 -4
1 -4
0 0
0 0
```
## 提示

【样例说明 1】

用二元组 $(p, q)$ 表示第 $p$ 杯酒与第 $q$ 杯酒。

$0$ 相似：所有 $45$ 对二元组都是 $0$ 相似的，美味度最大的是 $8 × 7 = 56 $。

$1$ 相似： $(1,8) (2,4) (2,9) (4,9) (5,6) (5,7) (5,10) (6,7) (6,10) (7,10) $，最大的 $8 × 7 = 56$ 。

$2$ 相似： $(1,8) (4,9) (5,6)$ ，最大的 $4 × 8 = 32$ 。

没有 $3,4,5, ⋯ ,9$ 相似的两杯酒，故均输出 $0$ 。



 ![](https://cdn.luogu.com.cn/upload/pic/1508.png) 

【时限1s，内存512M】



---

---
title: "[HNOI2005] 分形"
layout: "post"
diff: 省选/NOI-
pid: P2316
tag: ['2005', '并查集', '各省省选', '湖南', '前缀和']
---
# [HNOI2005] 分形
## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1357.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/pic/1358.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/pic/1359.png)

## 样例

### 样例输入 #1
```
1 3 3

50000

0 0 0 0

150000 0 1 1

0 150000 1 1

3 5.497787 	  2 2.356194

3 1.570796 	  2 0.0

3 0.0         2 1.570796


```
### 样例输出 #1
```
175000

150000

200000


```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/1360.png)



---

---
title: "[USACO08OPEN] Cow Neighborhoods G"
layout: "post"
diff: 省选/NOI-
pid: P2906
tag: ['2008', 'USACO', '并查集', '平衡树', '生成树']
---
# [USACO08OPEN] Cow Neighborhoods G
## 题目描述

了解奶牛的人都知道奶牛是如何组成「奶牛社区」的。他们观察了 Farmer John 的 $N$ 头奶牛（编号为 $1 \sim N$），它们在 $X$ 和 $Y$ 坐标范围为 $1$ 的牧场上放牧，每头奶牛都在自己唯一的整数直线坐标上。

如果满足以下两个标准中的至少一个，则两头奶牛是邻居：

1. 两只奶牛的曼哈顿距离不超过 $C$，即 $|X_i - x_i| + |Y_i - y_i| \leq C$；
2. 两只奶牛有共同的邻居。即存在一只奶牛 $k$，使 $i$ 与 $k$，$j$ 与 $k$ 均同属一个群。

给定奶牛的位置和距离 $C$，确定「奶牛社区」的数量和最大的「奶牛社区」中的奶牛数量。

例如，考虑下面的牧场。 当 $C = 4$ 时，这个牧场有四个社区：左边的一个大社区，两个大小为 1 的社区，右边有一个巨大的社区，里面有 $60$ 头不同的奶牛。

```text
.....................................*.................
....*...*..*.......................***.................
......*...........................****.................
..*....*..*.......................*...*.******.*.*.....
........................*.............***...***...*....
*..*..*...*..........................*..*...*..*...*...
.....................................*..*...*..*.......
.....................................*..*...*..*.......
...*................*..................................
.*..*............................*.*.*.*.*.*.*.*.*.*.*.
.*.....*..........................*.*.*.*.*.*.*.*.*.*.*
....*..................................................
```
## 输入格式

第 $1$ 行包含两个用空格分隔的整数 $N, C$。

第 $2$ 到第 $N + 1$ 行每行包含两个用空格分隔的整数 $X_i, Y_i$，表示一头牛的坐标。

## 输出格式


共一行，为两个用空格分隔的整数，为「奶牛社区」的数量和最大的「奶牛社区」内牛的数量。
## 样例

### 样例输入 #1
```
4 2 
1 1 
3 3 
2 2 
10 10 

```
### 样例输出 #1
```
2 3 

```
## 提示

### 样例说明 #1

样例中有 $2$ 个社区，一个由前三头奶牛组成，另一个是最后一头奶牛。因此，最大的社区大小为 $3$。

### 数据范围与约定

对于 $100\%$ 的数据，$1 \leq N \leq 10^5$，$1 \leq C \leq 10^9$，$1 \leq X_i, Y_i \leq 10^9$，$X_i, Y_i$ 均为整数。


---

---
title: "[USACO09JAN] Safe Travel G"
layout: "post"
diff: 省选/NOI-
pid: P2934
tag: ['2009', 'USACO', '并查集', '最短路', '最近公共祖先 LCA']
---
# [USACO09JAN] Safe Travel G
## 题目描述

Gremlins have infested the farm. These nasty, ugly fairy-like

creatures thwart the cows as each one walks from the barn (conveniently located at pasture\_1) to the other fields, with cow\_i traveling to from pasture\_1 to pasture\_i. Each gremlin is personalized and knows the quickest path that cow\_i normally takes to pasture\_i. Gremlin\_i waits for cow\_i in the middle of the final cowpath of the quickest route to pasture\_i, hoping to harass cow\_i.

Each of the cows, of course, wishes not to be harassed and thus chooses an at least slightly  different route from pasture\_1 (the barn) to pasture\_i.

Compute the best time to traverse each of these new not-quite-quickest routes that enable each cow\_i that avoid gremlin\_i who is located on the final cowpath of the quickest route from pasture\_1 to

pasture\_i.

As usual, the M (2 <= M <= 200,000) cowpaths conveniently numbered 1..M are bidirectional and enable travel to all N (3 <= N <= 100,000) pastures conveniently numbered 1..N. Cowpath i connects pastures a\_i (1 <= a\_i <= N) and b\_i (1 <= b\_i <= N) and requires t\_i (1 <= t\_i <= 1,000) time to traverse. No two cowpaths connect the same two pastures, and no path connects a pasture to itself (a\_i != b\_i). Best of all, the shortest path regularly taken by cow\_i from pasture\_1 to pasture\_i is unique in all the test data supplied to your program.

By way of example, consider these pastures, cowpaths, and [times]:

```cpp
1--[2]--2-------+ 
|       |       | 
[2]     [1]     [3] 
|       |       | 
+-------3--[4]--4
```
``` 
TRAVEL     BEST ROUTE   BEST TIME   LAST PATH 
p_1 to p_2       1->2          2         1->2 
p_1 to p_3       1->3          2         1->3 
p_1 to p_4      1->2->4        5         2->4 
```
When gremlins are present:

```cpp
TRAVEL     BEST ROUTE   BEST TIME    AVOID 
p_1 to p_2     1->3->2         3         1->2 
p_1 to p_3     1->2->3         3         1->3 
p_1 to p_4     1->3->4         6         2->4 
```
For 20% of the test data, N <= 200. 

For 50% of the test data, N <= 3000. 

TIME LIMIT: 3 Seconds

MEMORY LIMIT: 64 MB
## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..M+1: Three space-separated integers: a\_i, b\_i, and t\_i

## 输出格式

\* Lines 1..N-1: Line i contains the smallest time required to travel from pasture\_1 to pasture\_i+1 while avoiding the final cowpath of the shortest path from pasture\_1 to pasture\_i+1. If no such path exists from pasture\_1 to pasture\_i+1, output -1 alone on the line.

## 样例

### 样例输入 #1
```
4 5 
1 2 2 
1 3 2 
3 4 4 
3 2 1 
2 4 3 

```
### 样例输出 #1
```
3 
3 
6 

```
## 题目翻译

**【题目描述】**

给定一张有 $n$ 个节点，$m$ 条边的无向图，对于任意的 $i$（$2\le i\le n$），请求出在不经过原来 $1$ 节点到 $i$ 节点最短路上最后一条边的前提下，$1$ 节点到 $i$ 节点的最短路。

特别地，保证 $1$ 到任何一个点 $i$ 的最短路都是唯一的。

保证图中没有重边和自环。

**【输入格式】**

第一行，两个整数 $n,m$。

之后 $m$ 行，每行三个整数 $a_i,b_i,t_i$ 表示有一条 $a_i$ 到 $b_i$，边权为 $t_i$ 的无向边。

**【输出格式】**

共 $n-1$ 行，第 $i$ 行表示 $1$ 到 $i+1$ 在不经过原来 $1$ 节点到 $i+1$ 节点最短路上最后一条边的前提下的最短路。如果最短路不存在，则在对应行输出 `-1`。

翻译贡献者：@[cryozwq](/user/282751)。


---

---
title: "[USACO13DEC] The Bessie Shuffle G"
layout: "post"
diff: 省选/NOI-
pid: P3098
tag: ['2013', 'USACO', '并查集', '广度优先搜索 BFS', '图论建模']
---
# [USACO13DEC] The Bessie Shuffle G
## 题目描述

Bessie is practicing her card tricks.  She has already mastered the Bessie- shuffle -- a shuffle on M (2 <= M <= 100,000) cards that reorganizes the cards so the i-th card from the top is now the P[i]-th card from the top.

Now Bessie is practicing shuffles on larger decks.  She has a deck of N cards (M <= N <= 1,000,000,000) conveniently labeled 1 to N.  She shuffles this deck by taking the first M cards and performing the Bessie-shuffle on them, placing the shuffled cards back on top of the deck.  She then removes the top card from the deck and places it face down.  She repeats this process, placing the top cards successively on top of each other, until she is out of cards.  When Bessie has less than M cards left, she no longer performs the Bessie-shuffle, but continues to place the top card on top of the others.

Bessie knows that the deck initially started in sorted order, with 1 on top, 2 next, and N on the bottom.  Given the description of the Bessie-shuffle, help Bessie compute which cards end up located at Q different specified positions (1 <= Q <= N, Q <= 5,000) in the deck.

50% of test cases will have N <= 100,000. 

贝西有一种独门的洗牌方法，称为 A 类洗牌法；

A 类洗牌法的具体过程：将一堆共 $M$（$2 \le M \le 10 ^ 5$）张从上到下编号 $1, 2, \cdots, M$ 的纸牌，从上到下第 $i$ 张牌洗到位置 $p _ i$。

例如，$M=3，p = \{3, 1, 2\}$，则执行一次 A 类洗牌法后，从上到下将变为 $2, 3, 1$，即牌 $1$ 放到位置 $3$，牌 $2$ 放到位置 $1$，牌 $3$ 放到位置 $2$。


贝西现在要练习另外一种洗牌方法，称为 B 类洗牌法。


B 类洗牌法的具体过程： 

有一堆 $N$（$M \le N \le 10 ^ 9$）张编号为 $1, 2, \cdots, N$ 的牌，并按从上到下 $1$ 到 $N$ 的顺序堆放。另有一个牌堆用来辅助洗牌，称为临时堆，开始时为空。

1. 将最上面 $M$ 张牌进行一次 A 类洗牌法；
2. 将最上面的一张牌放到临时堆的最上方；
3. 重复前两个操作，直到原先的堆没有牌为止。


以上过程中，当原先堆的牌不足 $M$ 张的时候，将不进行 A 类洗牌法，而是将最上面的牌依次放到临时堆上。


给定 $N, M$ 和排列 $p$。现在有 $Q$（$1 \le Q \le \min(N, 5000)$）个询问，请求出对其做一次 B 类洗牌法后临时堆中 $q _ i$ 位置上的牌的编号。

$50\%$ 的数据中，$N \le 10 ^ 5$。

## 输入格式

\* Line 1: A single line containing N, M and Q separated by a space.

\* Lines 2..1+M: Line i+1 indicates the position from the top, P[i], of the i-th card in the Bessie-shuffle (1 <= P[i] <= M).

\* Lines 2+M..1+M+Q: Line i+1+M contains a single integer q\_i

describing the i-th query.  You are to compute the label on the card located in position q\_i from the top (1 <= q\_i <= N).

## 输出格式

\* Lines 1..Q: On the i-th line, print a single integer indicating the card at position q\_i from the top.

## 样例

### 样例输入 #1
```
5 3 5 
3 
1 
2 
1 
2 
3 
4 
5 

```
### 样例输出 #1
```
4 
5 
3 
1 
2 

```
## 提示

Bessie has a deck of 5 cards initially ordered as [1, 2, 3, 4, 5].  Her shuffle is on 3 cards and has the effect of moving the top card to the bottom.  There are 5 queries querying each position in the deck.


The shuffle proceeds as:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (put 2 face down) 
[3, 1, 4, 5] -> [1, 4, 3, 5] (put 1 face down) 
[4, 3, 5] -> [3, 5, 4] (put 3 face down) 
[5, 4] (put 5 face down) 
[4] (put 4 face down) 
```
This produces the final order of [4, 5, 3, 1, 2]

贝西的五张牌刚开始顺序为 [1, 2, 3, 4, 5]。她一次洗三张牌，效果是将第一张牌放到底部。以上五个问题询问了每一张牌的位置。


洗牌的顺序是:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (将2正面向下放置)
[3, 1, 4, 5] -> [1, 4, 3, 5] (将1正面向下放置) 
[4, 3, 5] -> [3, 5, 4] (将3正面向下放置) 
[5, 4] (将5正面向下放置) 
[4] (将4正面向下放置) 
```
这就形成了最终的顺序：[4, 5, 3, 1, 2]



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
title: "[HNOI2012] 与非"
layout: "post"
diff: 省选/NOI-
pid: P3220
tag: ['2012', '并查集', '湖南', '位运算', '构造']
---
# [HNOI2012] 与非
## 题目背景

如果你能提供题面或者题意简述，请直接在讨论区发帖，感谢你的贡献。

## 题目描述

NAND（与非）是一种二元逻辑运算，其运算结果为真当且仅当两个输入的布尔值不全为真。NAND运算的真值表如下（1表示真，0表示假）:

 ![](https://cdn.luogu.com.cn/upload/pic/7851.png) 

两个非负整数的NAND是指将它们表示成二进制数，再在对应的二进制位进行NAND运算。由于两个二进制数的长度可能不等，因此一般约定一个最高位K，使得两个数的二进制表示都不 超过K位，不足K位的在高位补零。给定N个非负整数A1,A2......AN和约定位数K，利用NAND运算与括号，每个数可以使用任意次，请你求出范围[L,R]内可以被计算出的数有多少个。

## 输入格式

输入文件第一行是用空格隔开的四个正整数N，K，L和R，接下来的一行是N个非负整数A1,A2......AN，其含义如上所述。 100%的数据满足K<=60且N<=1000,0<=Ai<=2^k-1,0<=L<=R<=10^18

## 输出格式

仅包含一个整数，表示[L,R]内可以被计算出的数的个数

## 样例

### 样例输入 #1
```
3  3 1 4
3  4 5
```
### 样例输出 #1
```
4
```
## 提示

样例1中，(3 NAND 4) NAND (3 NAND 5) = 1，5 NAND 5 = 2，3和4直接可得。



---

---
title: "[HNOI2015] 实验比较"
layout: "post"
diff: 省选/NOI-
pid: P3240
tag: ['动态规划 DP', '数学', '2015', '并查集', '各省省选', '湖南']
---
# [HNOI2015] 实验比较
## 题目描述

小 D 被邀请到实验室，做一个跟图片质量评价相关的主观实验。

实验用到的图片集一共有 $N$ 张图片，编号为 $1$ 到 $N$。实验分若干轮进行，在每轮实验中，小 D 会被要求观看某两张随机选取的图片， 然后小 D 需要根据他自己主观上的判断确定这两张图片谁好谁坏，或者这两张图片质量差不多。 

用符号 ”$<$”、“$>$” 和 “$=$” 表示图片 $x$ 和 $y$（$x$、$y$ 为图片编号）之间的比较：如果上下文中 $x$ 和 $y$ 是图片编号，则 $x<y$ 表示图片 $x$「质量优于」$y$，$x>y$ 表示图片 $x$「质量差于」$y$，$x=y$ 表示图片 $x$ 和 $y$ 「质量相同」；也就是说，这种上下文中，“$<$”、“$>$”、“$=$” 分别是质量优于、质量差于、质量相同的意思；在其他上下文中，这三个符号分别是小于、大于、等于的含义。

图片质量比较的推理规则（在 $x$ 和 $y$ 是图片编号的上下文中）：
1. $x < y$ 等价于 $y > x$。
2. 若 $x < y$ 且 $y = z$，则 $x < z$。
3. 若 $x < y$ 且 $x = z$，则 $z < y$。
4. $x=y$ 等价于 $y=x$。
5. 若 $x=y$ 且 $y=z$，则 $x=z$。 

实验中，小 D 需要对一些图片对 $(x, y)$，给出 $x < y$ 或 $x = y$ 或 $x > y$ 的主观判断。小 D 在做完实验后， 忽然对这个基于局部比较的实验的一些全局性质产生了兴趣。

在主观实验数据给定的情形下，定义这 $N$ 张图片的一个合法质量序列为形如 “$x_1 R_1 x_2 R_2 x_3 R_3 …x_{N-1} R_{N-1} x_N$” 的串，也可看作是集合 $\{ x_i R_i x_{i+1}|1 \leq i \leq N-1 \}$，其中  $x_i$ 为图片编号，$x_1,x_2, \ldots ,x_N$ 两两互不相同（即不存在重复编号），$R_i$ 为 $<$ 或 $=$，「合法」是指这个图片质量序列与任何一对主观实验给出的判断不冲突。 

例如： 质量序列 $3 < 1 = 2$ 与主观判断 “$3 > 1$，$3 = 2$” 冲突（因为质量序列中 $3<1$ 且 $1=2$，从而 $3<2$，这与主观判断中的 $3=2$ 冲突；同时质量序列中的 $3<1$ 与主观判断中的 $3>1$ 冲突） ，但与主观判断 “$2 = 1$，$3 < 2$”  不冲突；因此给定主观判断 “$3>1$，$3=2$” 时，$1<3=2$ 和 $1<2=3$ 都是合法的质量序列，$3<1=2$ 和 $1<2<3$ 都是非法的质量序列。

由于实验已经做完一段时间了，小 D 已经忘了一部分主观实验的数据。对每张图片 $X_i$，小 D 都**最多**只记住了某一张质量不比 $X_i$ 好的另一张图片 $K_{X_i}$。这些小 D 仍然记得的质量判断一共有 $M$ 条（$0 \leq M \leq N$），其中第 $i$ 条涉及的图片对为 $(K_{X_i}, X_i)$，判断要么是 $K_{X_i} < X_i$，要么是 $K_{X_i} = X_i$，而且所有的 $X_i$ 互不相同。小 D 打算就以这 M 条自己还记得的质量判断作为他的所有主观数据。

现在，基于这些主观数据，我们希望你帮小 D 求出这 $N$ 张图片一共有多少个不同的合法质量序列。我们规定：如果质量序列中出现 “$x = y$”，那么序列中交换 $x$ 和 $y$ 的位置后仍是同一个序列。因此： $1<2=3=4<5$ 和 $1<4=2=3<5$ 是同一个序列， $1 < 2 = 3$ 和 $1 < 3 = 2$ 是同一个序列，而 $1 < 2 < 3$ 与 $1 < 2 = 3$ 是不同的序列，$1<2<3$ 和 $2<1<3$ 是不同的序列。

由于合法的图片质量序列可能很多， 所以你需要输出答案对 $10^9 + 7$ 取模的结果。
## 输入格式

第一行两个正整数 $N,M$，分别代表图片总数和小 $D$ 仍然记得的判断的条数；

接下来 $M$ 行，每行一条判断，每条判断形如「$x < y$」或者「$x = y$」。
## 输出格式

输出仅一行，包含一个正整数，表示合法质量序列的数目对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
5 4
1 < 2
1 < 3
2 < 4
1 = 5
```
### 样例输出 #1
```
5
```
## 提示

不同的合法序列共5个，如下所示：

- $1 = 5 < 2 < 3 < 4$ 
- $1 = 5 < 2 < 4 < 3$
- $1 = 5 < 2 < 3 = 4$ 
- $1 = 5 < 3 < 2 < 4$ 
- $1 = 5 < 2 = 3 < 4$

$100\%$ 的数据满足 $N \leq 100$。


---

---
title: "[HNOI2016] 最小公倍数"
layout: "post"
diff: 省选/NOI-
pid: P3247
tag: ['数学', '2016', '并查集', '湖南']
---
# [HNOI2016] 最小公倍数
## 题目描述

给定一张 $N$ 个顶点 $M$ 条边的无向图(顶点编号为 $1,2,\ldots,n$)，每条边上带有权值。所有权值都可以分解成 $2^a\times 3^b$ 的形式。

现在有 $q$ 个询问，每次询问给定四个参数 $u,v,a$ 和 $b$，请你求出是否存在一条顶点 $u$ 到 $v$ 之间的路径，使得路径依次经过的边上的权值的最小公倍数为 $2^a\times 3^b$。

注意：路径可以不是简单路径。

下面是一些可能有用的定义，如果与其它地方定义不同，在本题中以下面的定义为准：  

最小公倍数： $ k $ 个数 $ a_1 , a_2, \ldots, a_k $ 的最小公倍数是能被每个 $a_i$ 整除的最小正整数。

路径：顶点序列 $ P \colon P_1,P_2,\ldots,P_k $ 是一条路径，当且仅当 $k \geq 2$，且对于任意 $ 1 \leq i < k $ ，节点 $ P_i $ 和 $ P_{i+1} $ 之间都有边相连。 

简单路径：如果路径 $ P \colon P_1,P_2,\ldots,P_k $ 中，对于任意 $ 1 \leq s \neq t \leq k $ 都有 $ P_s \neq P_t $ ，那么称 $P$ 为简单路径。

## 输入格式

输入文件的第一行包含两个整数 $N$ 和 $M$，分别代表图的顶点数和边数。

接下来 $M$ 行，每行包含四个整数 $u,v,a,b$ 代表一条顶点 $u$ 和 $v$ 之间、权值为 $2^a\times 3^b$ 的边。

接下来一行包含一个整数 $q$，代表询问数。

接下来 $q$ 行，每行包含四个整数 $u,v,a$ 和 $b$，代表一次询问。询问内容请参见问题描述。

## 输出格式

对于每次询问，如果存在满足条件的路径，则输出一行 `Yes`，否则输出一行 `No`（注意：第一个字母大写，其余字母小写）。

## 样例

### 样例输入 #1
```
4 5
1 2 1 3
1 3 1 2
1 4 2 1
2 4 3 2
3 4 2 2
5
1 4 3 3
4 2 2 3
1 3 2 2
2 3 2 2
1 3 4 4
```
### 样例输出 #1
```
Yes 
Yes 
Yes 
No 
No
```
## 提示

$1\le n,q\le 5\times 10^4$，$1\leq m\leq 10^5$，$0\leq a,b\leq 10^9$。


---

---
title: "[SCOI2011] 飞镖"
layout: "post"
diff: 省选/NOI-
pid: P3277
tag: ['2011', '四川', '线段树', '并查集', '连通块']
---
# [SCOI2011] 飞镖
## 题目描述

飞镖是在欧洲颇为流行的一项运动。它的镖盘上分为20个扇形区域，分别标有1到20的分值，每个区域中有单倍、双倍和三倍的区域，打中对应的区域会得到分值乘以倍数所对应的分数。

例如打中18分里面的三倍区域，就会得到54分。

另外，在镖盘的中央，还有”小红心“和”大红心“，分别是25分和50分。

通常的飞镖规则还有一条，那就是在最后一镖的时候，必须以双倍结束战斗，才算获胜。也就是说，当还剩12分的时候，必须打中双倍的6才算赢，而打中单倍的12或者三倍的4则不算。

特别的，”大红心“也算双倍(双倍的25)。在这样的规则下，3镖能解决的最多分数是170分(两个三倍的20，最后用大红心结束)。

现在，lxhgww把原来的1到20分的分值变为了1到K分，同时把小红心的分数变为了M分(大红心是其双倍)，现在lxhgww想知道能否在3镖内（可以不一定用满3镖）解决X分。同样的，最后一镖必须是双倍（包括大红心）。

## 输入格式

输入的第一行是一个整数T，包括了T组数据。

第二行是5个整数，$A_1,B_1,C_1,D_1,K_1$，表示第一组数据的镖盘是从1到$K_1$分的，随后数据的镖盘由公式$K_i=(A_1K^2_{i-1}+B_1K_{i-1}+C_1)mod D_1 + 20$决定，其中第$i(1<i\le T)$组数据的镖盘是从1到$K_i$分的。

第三行是5个整数，$A_2,B_2,C_2,D_2,M_1$，表示第一组数据的小红心$M_1$分的，随后数据的镖盘由公式$M_i=(A_2M^2_{i-1}+B_2M_{i-1}+C_2)mod D_2 + 20$决定，其中第$i(1<i\le T)$组数据的小红心是$M_i$分。


第四行是5个整数，$A_3,B_3,C_3,D_3,X_1$，表示第一组数据需要解决的分数是$X_1$分的，随后数据的镖盘由公式$X_i=(A_3X^2_{i-1}+B_3X_{i-1}+C_3)mod D_3 + 20$决定，其中第$i(1<i\le T)$组数据需要解决的分数是$X_i$分。

## 输出格式

一行，包括一个数字，表示这T组数据中，能够被解决的数据数目。

## 样例

### 样例输入 #1
```
5
1 2 2 10 20
1 3 2 15 25
2 2 5 200 170
```
### 样例输出 #1
```
4
```
## 提示

对于30%的数据，保证$1\le T\le 20$,$20\le K1,M1,X1,D1,D2,D3\le 1000$

对于100%的数据，保证$1\le T\le 10^6$,$20\le K1,M1,X1,D1,D2,D3\le 10^9$

对于所有的数据，保证$0\le A1,B1,A2,B2,C2,A3,B3,C3 \le 10^9$



---

---
title: "[SCOI2013] 密码"
layout: "post"
diff: 省选/NOI-
pid: P3279
tag: ['字符串', '2013', '四川', '并查集', '各省省选']
---
# [SCOI2013] 密码
## 题目描述

Fish是一条生活在海里的鱼。有一天他很无聊，就到处去寻宝。他找到了位于海底深处的宫殿，但是一扇带有密码锁的大门却阻止了他的前进。

通过翻阅古籍，Fish 得知了这个密码的相关信息：

1. 该密码的长度为N。

2. 密码仅含小写字母。

3. 以每一个字符为中心的最长回文串长度。

4. 以每两个相邻字符的间隙为中心的最长回文串长度。

很快Fish 发现可能有无数种满足条件的密码。经过分析，他觉得这些密码中字典序最小的一个最有可能是答案，你能帮他找到这个密码么？

注意：对于两个串A和B，如果它们的前i个字符都相同，而A的第i+1个字符比B的第i+1个字符小，那么认为是则称密码A 的字典序小于密码B 的字典序，例如字符串abc 字典序小于字符串acb。如果密码A的字典序比其他所有满足条件的密码的字典序都小，则密码A是这些密码中字典序最小的一个。

## 输入格式

输入由三行组成。第一行仅含一个整数N，表示密码的长度。第二行包含N 个整数，表示以每个字符为中心的最长回文串长度。第三行包含N - 1 个整数，表示每两个相邻字符的间隙为中心的最长回文串长度。

## 输出格式

输出仅一行。输出满足条件的最小字典序密码。古籍中的信息是一定正确的，故一定存在满足条件的密码。

## 样例

### 样例输入 #1
```
3
1 1 1
0 0
```
### 样例输出 #1
```
abc

```
### 样例输入 #2
```
3
1 3 1
0 0
```
### 样例输出 #2
```
aba
```
### 样例输入 #3
```
3
1 3 1
2 2
```
### 样例输出 #3
```
aaa
```
## 提示

对于20% 的数据，1 <= n <= 100。

另有30% 的数据，1 <= n <= 1000。

最后50% 的数据，1 <= n <= 10^5。



---

---
title: "[SCOI2016] 萌萌哒"
layout: "post"
diff: 省选/NOI-
pid: P3295
tag: ['2016', '四川', '并查集', '枚举', 'ST 表']
---
# [SCOI2016] 萌萌哒
## 题目描述

一个长度为 $n$ 的大数，用 $S_1S_2S_3 \cdots S_n$表示，其中 $S_i$ 表示数的第 $i$ 位, $S_1$ 是数的最高位。告诉你一些限制条件，每个条件表示为四个数，$l_1,r_1,l_2,r_2$，即两个长度相同的区间，表示子串 $S_{l_1}S_{l_1+1}S_{l_1+2} \cdots S_{r_1}$ 与 $S_{l_2}S_{l_2+1}S_{l_2+2} \cdots S_{r_2}$ 完全相同。

比如 $n=6$ 时，某限制条件 $l_1=1,r_1=3,l_2=4,r_2=6$ ，那么 $123123$，$351351$ 均满足条件，但是 $12012$，$131141$ 不满足条件，前者数的长度不为 $6$ ，后者第二位与第五位不同。问满足以上所有条件的数有多少个。
## 输入格式

第一行两个数 $n$ 和 $m$，分别表示大数的长度，以及限制条件的个数。

接下来 $m$ 行，对于第 $i$ 行,有 $4$ 个数 $l_{i_1},r_{i_1},{l_{i_2}},r_{i_2}$，分别表示该限制条件对应的两个区间。

$1\le n\le 10^5$，$1\le m\le 10^5$，$1\le l_{i_1},r_{i_1},{l_{i_2}},r_{i_2}\le n$ ；并且保证 $ r_{i_1}-l_{i_1}=r_{i_2}-l_{i_2}$ 。

## 输出格式

一个数，表示满足所有条件且长度为 $n$ 的大数的个数，答案可能很大，因此输出答案模 $ 10^9+7 $ 的结果即可。

## 样例

### 样例输入 #1
```
4 2
1 2 3 4
3 3 3 3
```
### 样例输出 #1
```
90
```


---

---
title: "可持久化并查集"
layout: "post"
diff: 省选/NOI-
pid: P3402
tag: ['并查集', '可持久化']
---
# 可持久化并查集
## 题目描述

给定 $n$ 个集合，第 $i$ 个集合内初始状态下只有一个数，为 $i$。

有 $m$ 次操作。操作分为 $3$ 种：

 - `1 a b` 合并 $a,b$ 所在集合；

 - `2 k` 回到第 $k$ 次操作（执行三种操作中的任意一种都记为一次操作）之后的状态；

 - `3 a b` 询问 $a,b$ 是否属于同一集合，如果是则输出 $1$，否则输出 $0$。
## 输入格式

第一行两个整数，$n,m$。

接下来 $m$ 行，每行先输入一个数 $opt$。若 $opt=2$ 则再输入一个整数 $k$，否则再输入两个整数 $a,b$，描述一次操作。
## 输出格式

对每个操作 $3$，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5 6
1 1 2
3 1 2
2 0
3 1 2
2 1
3 1 2
```
### 样例输出 #1
```
1
0
1
```
## 提示

对于 $100\%$ 的数据，$1\le n\le 10^5$，$1\le m\le 2\times 10^5$，$1 \le a, b \le n$。


---

---
title: "[POI 2005] PUN-Points"
layout: "post"
diff: 省选/NOI-
pid: P3418
tag: ['2005', '并查集', 'POI（波兰）', '最短路']
---
# [POI 2005] PUN-Points
## 题目描述

A set of grid points in a plane (points whose both cartesian coordinates are integers) which we shall refer to as the pattern, as well as a group of other sets of grid points on the plane are given. We would like to know which of the sets are similar to the pattern, i.e. which of them can be transformed by rotations, translations, reflections and dilations so that they are identical to the pattern. For instance: the set of points $\{(0,0),(2,0),(2,1)\}$ is similar to the set $\{(6,1),(6,5),(4,5)\}$, it is however not similar to the set $\{(4,0),(6,0),(5,-1)\}$.

TaskWrite a programme which:

reads from the standard input the description of the pattern and the family of the investigated sets of points,determines which of the investigated sets of points are similar to the pattern,writes the outcome to the standard output.

题目描述：


给出一个包含平面上格点的集合（格点的定义是xy坐标均为整数），我们将其称作“模式集合”。


接下来给出另外的几个包含平面上点的集合。我们想要考察后面给出的哪些集合和“模式集合”是“相似”的，即：该集合可以通过 旋转，平移，翻转，和缩放 使得该集合和“模式集合”完全相同。


例：{(0,0),(2,0),(2,1)}这个集合和{(6,1),(6,5),(4,5)}这个集合是相似的，但和{(4,0),(6,0),(5,-1)}这个集合是不相似的。


任务：


写一个程序，使得


能从标准输入读取“模式集合”和需要考察（是否相似）的集合，判断哪些集合和“模式集合”相似，并将结果输出到标准输出


输入格式：


标准输入的第一行有一个整数 k (1<=k<=25000)，代表“模式集合”中的点数


接下来k行，每行两个数，用一个空格分隔，第i+1行的两个数分别代表“模式集合”中第i个点的x坐标和y坐标(-20000<=x,y<=20000)


“模式集合”中的点两两不同。


接下来一行一个整数n，代表有n个需要考察的集合


接下来有n个对需要考察的集合的描述：


每个描述的第一行包含一个整数l，代表该集合中的点数(1<=l<=25000)


接下来l行每行包含该集合中一个点的x坐标和y坐标，用一个空格分隔(-20000<=x,y<=20000，为整数)


包含在同一集合中的点两两不同。


输出格式：


你的程序应该向标准输出流输出n行，每行代表对于一个需要考察的集合的结果。


如果第i个需要考察的集合与“模式集合”相似，则第i行应包含单词TAK，即波兰语中的yes


否则第i行应包含单词NIE，即波兰语中的no

## 输入格式

In the first line of the standard input there is a single integer $k$ ($1\le k\le 25\ 000$) - the number of points the pattern consists of. In the following $k$ lines there are pairs of integers, separated by single spaces. The $(i+1)$'st line contains the coordinates of $i$'th point belonging to the pattern: $x_{i}$ and $y_{i}$ ($-20\ 000\le x_{i},y_{i} \le 20\ 000$). The points forming the pattern are pairwise different. In the next line there is the number of sets to be investigated: $n$ ($1\le n\le 20$). Next, there are $n$ descriptions of these sets. The description of each set begins with a line containing a single integer $l$ - the number of points belonging to that particular set($1\le l\le 25\ 000$).These points are described in the following lines, a single point per line. The description of a point consists of two integers separated by a single space - its coordinates $x$ and $y$ ($-20\ 000\le x,y\le 20\ 000$).The points which belong to the same set are pairwise different.

## 输出格式

Your programme should write to the standard output $n$ lines - one for each of the investigated sets of points. The $i$'th line should contain the word TAK (i.e. yes in Polish), if the $i$'th of the given sets of points is similar to the pattern, or the word NIE (i.e. no in Polish) if the set does not satisfy this condition.

## 样例

### 样例输入 #1
```
3
0 0
2 0
2 1
2
3
4 1
6 5
4 5
3
4 0
6 0
5 -1
```
### 样例输出 #1
```
TAK
NIE
```


---

---
title: "[POI 2007] POW-The Flood"
layout: "post"
diff: 省选/NOI-
pid: P3457
tag: ['贪心', '2007', '并查集', 'POI（波兰）']
---
# [POI 2007] POW-The Flood
## 题目描述

Byteburg, the capital of Byteotia, is a picturesque city situated in a valley in the midst of mountains. Unfortunately,  recent heavy rainfall has caused a flood - all the Byteburg is now completely under water. Byteasar,  the king of Byteotia, has summoned his most enlightened advisors, including you, to a council. After long  deliberations the council agreed to bring a few pumps, set them up in the flooded area and drain Byteburg.

The king has asked you to determine the minimum number of pumps sufficing to drain the city.

You are provided with a map of the city and the valley it is situated in. The map is in the shape of a $m\times n$ rectangle, divided into unitary squares. For each such square the map tells its height above sea level and alsowhether it is a part of Byteburg or not. The whole area depicted in the map is under water. Furthermore, it issurrounded by much higher mountains, making the outflow of water impossible. Obviously, there is no needto drain the area that does not belong to Byteburg.

Each pump can be placed in any unitary square depicted in the map. The pump will be drawing thewater until its square is completely drained. Of course, the communicating tubes principle makes its work,      so draining one square results in lowering the water level or complete draining of those squares from which      the water can flow down to the one with the pump. Water can flow only between squares with a common side      (or, more exact, squares whose projections onto horizontal plane have a common side, since the squares may       be at different level). Apart from that, the water obviously only flows down.

## Task

Write a programme that:

- reads description of the map from the standard input,

- determines the minimum number of pumps needed to drain whole Byteburg,

- writes out the outcome to the standard output.
## 输入格式

In the first line of the standard input there are two integers $m$ and $n$, separated by a single space, $1 \le n, m \le 1\ 000$. The following $m$ lines contain the description of the map. The $(i+1)$'th line describes the $i$'th row of unitary squares in the map. It contains $n$ integers $x_{i,1}, x_{i,2}, ..., x_{i_n}$, separated by single spaces,$-1\ 000 \le x_{i,j} \le 1\ 000$ ,$x_{i,j} \ne 1000$ . The number $x_{i,j}$ describes the $j$'th square of the $i$'th line. The ground level in this square is $|x_{i,j}|$ above sea level. If $x_{i,j} > 0$, then the square is part of Byteburg, otherwise it is outside the city. Notice, that the area of Byteburg need not be connected. In fact the city may have several separate parts.

## 输出格式

Your programme should write out one integer to the standard output - the minimum number of pumpsneeded to drain Byteburg.

## 样例

### 样例输入 #1
```
6 9
-2 -2 -1 -1 -2 -2 -2 -12 -3
-2 1 -1 2 -8 -12 2 -12 -12
-5 3 1 1 -12 4 -6 2 -2
-5 -2 -2 2 -12 -3 4 -3 -1
-5 -6 -2 2 -12 5 6 2 -1
-4 -8 -8 -10 -12 -8 -6 -6 -4
```
### 样例输出 #1
```
2
```
## 题目翻译

### 题目描述

**译自 POI 2007 Stage 2. Day 1「[The Flood](https://szkopul.edu.pl/problemset/problem/VutzcR1iPvGuYRGZgvNksmV1/site/?key=statement)」**

你有一张 $m \times n$ 的地图，地图上所有点都被洪水淹没了。你知道地图上每个网格的海拔高度，其中一部分点属于 Byteburg 城。你需要放置尽可能少的巨型抽水机，将 Byteburg 城从洪水中解救出来。巨型抽水机会抽干该格子的所有水，直到该格子不被洪水淹没为止。

水会在有公共边的格子间从高向低流动。

### 输入格式

第一行两个整数 $m,n$（$1 \le m,n \le 1000$）。

接下来 $m$ 行每行 $n$ 个整数 $x_{i1}, x_{i2}, \ldots, x_{in} (-1000 \le x_{ij} \lt 1000)$，表示地图。第 $i$ 行第 $j$ 列格子的海拔高度为 $\lvert x_{ij} \rvert$，且如果 $x_{ij} \gt 0$，则这个格子在 Byteburg 城内，否则在城外。不保证 Byteburg 城形成一个连通块。

### 输出格式

输出一行一个整数，表示最少需要的抽水机的数量。

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/6cal4wth.png)

翻译来自于 [LibreOJ](https://loj.ac/p/2654)。


---

---
title: "[APIO2008] 免费道路"
layout: "post"
diff: 省选/NOI-
pid: P3623
tag: ['2008', '并查集', 'APIO', 'Special Judge', '背包 DP', '生成树']
---
# [APIO2008] 免费道路
## 题目描述

 
新亚（New Asia）王国有 N 个村庄，由 M 条道路连接。其中一些道路是鹅卵石路，而其它道路是水泥路。保持道路免费运行需要一大笔费用，并且看上去 王国不可能保持所有道路免费。为此亟待制定一个新的道路维护计划。

国王已决定保持尽可能少的道路免费，但是两个不同的村庄之间都应该一条且仅由一条 且仅由一条免费道路的路径连接。同时，虽然水泥路更适合现代交通的需 要，但国王也认为走在鹅卵石路上是一件有趣的事情。所以，国王决定保持刚好 K 条鹅卵石路免费。

举例来说，假定新亚王国的村庄和道路如图 3(a)所示。如果国王希望保持两 条鹅卵石路免费，那么可以如图 3(b)中那样保持道路(1, 2)、(2, 3)、(3, 4)和(3, 5) 免费。该方案满足了国王的要求，因为：(1)两个村庄之间都有一条由免费道 路组成的路径；(2)免费的道路已尽可能少；(3)方案中刚好有两条鹅卵石道路 (2, 3)和(3, 4)

 ![](https://cdn.luogu.com.cn/upload/pic/4393.png) 

图 3: (a)新亚王国中村庄和道路的一个示例。实线标注的是水泥路，虚线标注 的是鹅卵石路。(b)一个保持两条鹅卵石路免费的维护方案。图中仅标出了免 费道路。


给定一个关于新亚王国村庄和道路的述以及国王决定保持免费的鹅卵石 道路数目，写一个程序确定是否存在一个道路维护计划以满足国王的要求，如果 存在则任意输出一个方案。

## 输入格式

输入第一行包含三个由空格隔开的整数：

N，村庄的数目(1≤N≤20,000)；

M，道路的数目(1≤M≤100,000)；

K，国王希望保持免费的鹅卵石道路数目(0≤K≤N - 1)。

此后 M 行述了新亚王国的道路，编号分别为 1 到 M。第(i+1)行述了第 i 条 道路的情况。用 3 个由空格隔开的整数述：

ui 和 vi，为第 i 条道路连接的两个村庄的编号，村庄编号为 1 到 N；

ci，表示第 i 条道路的类型。ci = 0 表示第 i 条道路是鹅卵石路，ci = 1 表 示第 i 条道路是水泥路。

输入数据保证一对村庄之间至多有一条道路连接

## 输出格式

如果满足国王要求的道路维护方案不存在，你的程序应该在输出第一行打印 no solution。 否则，你的程序应该输出一个符合要求的道路维护方案，也就是保持免费的 道路列表。按照输入中给定的那样输出免费的道路。如果有多种合法方案，你可 以任意输出一种。

## 样例

### 样例输入 #1
```
5 7 2 
1 3 0 
4 5 1 
3 2 0 
5 3 1 
4 3 0 
1 2 1 
4 2 1
```
### 样例输出 #1
```
3 2 0 
4 3 0 
5 3 1 
1 2 1 
```


---

---
title: "[APIO2011] 方格染色"
layout: "post"
diff: 省选/NOI-
pid: P3631
tag: ['数学', '2011', '并查集', 'APIO', '枚举', '位运算']
---
# [APIO2011] 方格染色
## 题目描述

Sam 和他的妹妹 Sara 有一个包含 $n \times m$ 个方格的表格。他们想要将其中的每个方格都染成红色或蓝色。出于个人喜好，他们想要表格中每个 $2 \times 2$ 的方形区域都包含奇数个（ $1$ 个或 $3$ 个）红色方格。例如，下面是一个合法的表格染色方案（`R` 代表红色，`B` 代表蓝色）：
```
B B R B R
R B B B B
R R B R B
```
可是昨天晚上，有人已经给表格中的一些方格染上了颜色！现在 Sam 和 Sara 非常生气。不过，他们想要知道是否可能给剩下的方格染上颜色，使得整个表格依然满足他们的要求。如果可能的话，满足他们要求的染色方案数有多少呢？
## 输入格式

输入的第一行包含三个整数 $n,m,k$，分别代表表格的行数，列数和已被染色的方格数目。

之后的 $k$ 行描述已被染色的方格。其中第i行包含三个整数 $x_i,y_i,c_i$，分表代表第 $i$ 个已被染色的方格的行编号、列编号和颜色。$c_i$ 为 $1$ 表示方格被染成红色，$c_i$ 为 $0$ 表示方格被染成蓝色。
## 输出格式

输出一个整数，表示可能的染色方案数 $w$ 对于 $10^9$ 取模后得到的值。

## 样例

### 样例输入 #1
```
3 4 3
2 2 1
1 2 0
2 3 1
```
### 样例输出 #1
```
8
```
## 提示

对于 $20\%$ 的测试数据，$n,m,k \leqslant 5$。

对于 $50\%$ 的测试数据，$n,m \leqslant 5000$，$k \leqslant 25$。

对于 $100\%$ 的测试数据，$2 \leqslant n,m \leqslant 10^5$，$0 \leqslant k \leqslant 10^5$，$1 \leqslant x_i \leqslant n$，$1 \leqslant y_i \leqslant m$，$\forall c_i \in \{0,1\}$。


---

---
title: "魔法"
layout: "post"
diff: 省选/NOI-
pid: P3767
tag: ['搜索', '线段树', '并查集', '洛谷原创', '分治', '洛谷月赛']
---
# 魔法
## 题目背景

小 Y 在 AK 曼哈顿 OI 之后，开始研究膜法。

一个精心构造的魔法阵可以产生强大的魔力，但是也有非常严苛的要求。

魔法阵的强度与咒语的数目相关，但是咒语太多可能会产生冲突，小Y当然会解决这个问题啦，但是他想考一考你。

## 题目描述

魔法阵由 $N$ 个枢纽组成。

每个枢纽可以有五种属性：金、木、水、火、土。它们之间满足相生相克的关系。

 ![](https://cdn.luogu.com.cn/upload/pic/5349.png) 

一开始，魔法阵中没有咒语。

每次，小 Y 会添加一条咒语，它会要求两个枢纽的属性满足相生/相克的关系。然后你需要回答：是否存在一种为每个枢纽分配一个属性的方案，满足所有的要求。

为了调整法阵，小 Y 有时候需要删除一条写过的咒语。

小 Y 觉得这个问题太简单了，于是他使用改变时间线的能力，让每一次操作在之前某一次操作后形成的魔法阵的基础上进行。
## 输入格式

第一行两个正整数 $N,M$，表示枢纽的个数和操作个数。

接下来 $M$ 行，每行四个数表示一次操作。

第一个数 $k$ 表示这次操作在第 $k$ 次操作结束后的魔法阵上进行，如果 $k=0$，则表示在初始的魔法阵上进行。

第二个数 $t$ 表示操作类型。

- $t=1$：接下来输入 $u,v$，表示加入一条咒语，要求 $u$ 生 $v$。

- $t=2$：接下来输入 $u,v$，表示加入一条咒语，要求 $u$ 克 $v$。

- $t=3$: 接下来输入 $x$，表示删除第 $x$ 次操作加入的咒语。
## 输出格式

对于每一次操作，如果操作后存在为每个枢纽分配一个属性的方案，满足所有的要求，输出 `excited`，否则输出 `naive`。

## 样例

### 样例输入 #1
```
3 6  
0 1 1 2  
1 1 2 3  
2 2 1 3  
2 1 3 1  
2 3 1  
5 1 3 1
```
### 样例输出 #1
```
excited  
excited  
excited  
naive  
excited  
excited  
```
## 提示

对于 $30\%$ 的数据，满足 $N,M\leq 100$;

对于另 $30\%$ 的数据，满足 $k_i=i-1$;

对于100%的数据，满足 $N,M \leq 100000, 0\leq k_i < i, u_i \neq v_i, 1 \leq u_i,v_i \leq N$，保证所有删除操作都合法。



---

---
title: "[USACO17DEC] A Pie for a Pie G"
layout: "post"
diff: 省选/NOI-
pid: P4083
tag: ['2017', '二分', 'USACO', '并查集', '图论建模', '最短路']
---
# [USACO17DEC] A Pie for a Pie G
## 题目描述

Bessie and Elsie have each baked $N$ pies ($1 \leq N \leq 10^5$). Each of the $2N$ pies has a tastiness value according to Bessie and a (possibly different) tastiness value according to Elsie.

Bessie is thinking about giving one of her pies to Elsie. If Elsie receives a pie from Bessie, she will feel obligated to give one of her pies to Bessie. So as to not appear stingy nor flamboyant, Elsie will try to pick a pie that is at least as tasty (in Elsie's eyes) as the pie she received, but no more than $D$ units tastier ($0 \leq D \leq 10^9$). Such a pie may not exist, in which case Elsie will adopt a pseudonym and exile herself to Japan.


But if Elsie does give Bessie a pie in return, Bessie will similarly try to give Elsie a pie which is at least as tasty but no more than $D$ units tastier (in Bessie's eyes) as the pie Elsie just gave her. Should this be impossible, Bessie too will exile herself. Otherwise she will give her chosen pie to Elsie. This cycle will continue until one of the cows is exiled, an unhappy outcome, or one of the cows receives a pie which she accords a tastiness value of $0$, in which case the gift exchange will end and both cows will be happy.


Note that a pie may not be gifted twice, nor can either cow return a pie gifted to her.


For each of the $N$ pies Bessie could select as her initial gift to Elsie, determine the minimum number of pies that could possibly be gifted in the resulting exchange before the cows are happy.

## 输入格式

The first line contains the two integers $N$ and $D$.

The next $2N$ lines contain two space-separated integers each, respectively denoting the value of a particular pie according to Bessie, and the value of that pie according to Elsie.


The first $N$ lines refer to Bessie's pies, and the remaining $N$ lines refer to Elsie's pies.


It is guaranteed that all tastiness values are in the range $[0,10^9]$.

## 输出格式

There should be $N$ lines in the output. Line $i$ should contain a single integer: the minimum number of pies that could be gifted in a happy gift exchange started with Bessie's pie $i$. If no gift exchange starting with pie $i$ is happy, then line $i$ should contain the single integer $-1$ instead.

## 样例

### 样例输入 #1
```
2 1
1 1
5 0
4 2
1 4
```
### 样例输出 #1
```
3
1

```
## 题目翻译

### 题目描述

Bessie 和 Elsie 各自烤了 $N$ 个派（$1 \leq N \leq 10^5$）。这 $2N$ 个派中的每一个都有一个由 Bessie 评定的美味值和一个（可能不同的）由 Elsie 评定的美味值。

Bessie 正在考虑将她的一只派送给 Elsie。如果 Elsie 收到了 Bessie 的派，她会觉得有义务回赠 Bessie 一只派。为了既不显得吝啬也不显得炫耀，Elsie 会尝试选择一只在她看来至少与收到的派一样美味，但不超过 $D$ 单位更美味的派（$0 \leq D \leq 10^9$）。如果这样的派不存在，Elsie 将采用一个化名并自我流放到日本。

但如果 Elsie 确实回赠了 Bessie 一只派，Bessie 也会类似地尝试送给 Elsie 一只在她看来至少与 Elsie 刚送给她的派一样美味，但不超过 $D$ 单位更美味的派。如果这不可能，Bessie 也会自我流放。否则，她会将她选择的派送给 Elsie。这个循环将继续，直到其中一头奶牛被流放（一个不愉快的结果），或者其中一头奶牛收到一只她评定美味值为 $0$ 的派，在这种情况下，礼物交换将结束，两头奶牛都会感到高兴。

请注意，一只派不能被赠送两次，任何一头奶牛也不能回赠她收到的派。

对于 Bessie 可以选择作为初始礼物送给 Elsie 的每一只派，确定在奶牛们感到高兴之前，可能被赠送的派的最小数量。

### 输入格式

第一行包含两个整数 $N$ 和 $D$。

接下来的 $2N$ 行每行包含两个用空格分隔的整数，分别表示某只派由 Bessie 评定的美味值和由 Elsie 评定的美味值。

前 $N$ 行描述 Bessie 的派，剩下的 $N$ 行描述 Elsie 的派。

保证所有美味值都在 $[0,10^9]$ 范围内。

### 输出格式

输出应包含 $N$ 行。第 $i$ 行应包含一个整数：如果以 Bessie 的第 $i$ 只派开始的礼物交换是高兴的，则输出可能被赠送的派的最小数量；否则输出 $-1$。


---

---
title: "[WC2005] 双面棋盘"
layout: "post"
diff: 省选/NOI-
pid: P4121
tag: ['2005', '线段树', '并查集', '生成树', '动态树 LCT', 'WC']
---
# [WC2005] 双面棋盘
## 题目描述

佳佳有一个 $n$ 行 $n$ 列的黑白棋盘，每个格子都有两面，一面白色，一面黑色。佳佳把棋盘平放在桌子上，因此每个格子恰好一面朝上，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/rcejbuct.png)

我们把每行从上到下编号为 $1$，$2$，$3$，……，$n$，各列从左到右编号为 $1$，$2$，$3$，……，$n$，则每个格子可以用棋盘坐标$(x, y)$表示。在上图中，有 $8$ 个格子黑色朝上，另外 $17$ 个格子白色朝上。

如果两个同色格子有一条公共边，我们称这两个同色格子属于同一个连通块。上图共有 $5$ 个黑色连通块和 $3$ 个白色连通块。

佳佳可以每分钟将一个格子翻转（即白色变成黑色，黑色变成白色），然后计算当前有多少个黑色连通块和白色连通块，你能算得更快吗？

## 输入格式

输入文件的第一行包含一个正整数 $n$，为格子的边长。以下 $n$ 行每行 $n$ 个整数，非 $0$ 即 $1$，表示初始状态。$0$ 表示白色，$1$ 表示黑色。  

下一行包含一个整数 $m$，表示操作的数目。以下 $m$ 行每行两个整数 $x$, $y$ ( $1 \le x,y \le n$ )，表示把坐标为 $(x, y)$ 的格子翻转。

## 输出格式

输出文件包含 $m$ 行，每行对应一个操作。该行包括两个整数 $b$, $w$，表示黑色区域和白色区域数目。

## 样例

### 样例输入 #1
```
5
0 1 0 0 0
0 1 1 1 0
1 0 0 0 1
0 0 1 0 0
1 0 0 0 0
2
3 2
2 3
```
### 样例输出 #1
```
4 3
5 2
```
## 提示

【样例说明】

翻转 $(3, 2)$ 之后，棋盘变为：

![](https://cdn.luogu.com.cn/upload/image_hosting/9oqt0zsv.png)

有 $4$ 个黑色区域和 $3$ 个白色区域

翻转 $(2, 3)$ 之后，棋盘变为：

![](https://cdn.luogu.com.cn/upload/image_hosting/f335hulm.png)

有 $5$ 个黑色区域和 $2$ 个白色区域

【数据范围】   
对于 $100\%$ 的数据，$1\le n \le 200$，$1\le m \le 10^4$。



---

---
title: "[AHOI2009] 最小割"
layout: "post"
diff: 省选/NOI-
pid: P4126
tag: ['2009', '并查集', '各省省选', '安徽', '强连通分量', '最小割']
---
# [AHOI2009] 最小割
## 题目描述

A,B两个国家正在交战，其中A国的物资运输网中有$N$个中转站，$M$条单向道路。设其中第$i (1≤i≤M)$条道路连接了$v_i,u_i$两个中转站，那么中转站$v_i$可以通过该道路到达$u_i$中转站，如果切断这条道路，需要代价$c_i$。

现在B国想找出一个路径切断方案，使中转站$s$不能到达中转站$t$，并且切断路径的代价之和最小。

小可可一眼就看出，这是一个求最小割的问题。但爱思考的小可可并不局限于此。现在他对每条单向道路提出两个问题：

- 问题一：是否存在一个最小代价路径切断方案，其中该道路被切断？
- 问题二：是否对任何一个最小代价路径切断方案，都有该道路被切断？

现在请你回答这两个问题。

## 输入格式

第一行有$4$个正整数，依次为$N,M,s,t$。

第$2$行到第$(M+1)$行每行$3$个正整数$v,u,c$，表示$v$中转站到$u$中转站之间有单向道路相连，单向道路的起点是$v$， 终点是$u$,切断它的代价是$c(1≤c≤100000)$。

注意:两个中转站之间可能有多条道路直接相连。 同一行相邻两数之间可能有一个或多个空格。

## 输出格式

对每条单向边，按输入顺序，依次输出一行，包含两个非$0$即$1$的整数，分别表示对问题一和问题二的回答(其中输出$1$表示是，输出$0$表示否)。 同一行相邻两数之间用一个空格隔开，每行开头和末尾没有多余空格。

## 样例

### 样例输入 #1
```
6 7 1 6
1 2 3
1 3 2
2 4 4
2 5 1
3 5 5
4 6 2
5 6 3
```
### 样例输出 #1
```
1 0
1 0
0 0
1 0
0 0
1 0
1 0
```
## 提示

设第$(i+1)$行输入的边为$i$号边，那么$\{1,2\},\{6,7\},\{2,4,6\}$是仅有的三个最小代价切割方案。它们的并是$\{1,2,4,6,7\}$，交是 $\{\varnothing \}$ 。

测试数据规模如下表所示

数据编号|N|M|数据编号|N|M
-|-|-|-|-|-
1|10|50|6|1000|20000
2|20|200|7|1000|40000
3|200|2000|8|2000|50000
4|200|2000|9|3000|60000
5|1000|20000|10|4000|60000



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
title: "[USACO18FEB] New Barns P"
layout: "post"
diff: 省选/NOI-
pid: P4271
tag: ['2018', 'USACO', '并查集', '连通块', '最近公共祖先 LCA', '树的直径', '动态树 LCT']
---
# [USACO18FEB] New Barns P
## 题目描述

给你一棵树，初始没有节点。你需要支持两种操作：  

- `B p` 表示新建一个节点，将它与 $p$  节点连接；若 $p=-1$，则表示不与其它节点相连  

- `Q k` 表示查询在 $k$ 节点所在的连通块中，距它最远的点的距离。这里距离的定义是两点间经过的边数。
## 输入格式

第一行一个正整数 $q$，表示操作个数。  
接下来 $q$ 行，每行表示一个操作。
## 输出格式

对于每个询问操作，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
7
B -1
Q 1
B 1
B 2
Q 3
B 2
Q 2
```
### 样例输出 #1
```
0
2
1

```
## 提示

【数据范围】  

对于 $100%$ 的数据，$1 \le q \le 10^5$。  
保证操作合法。

The example input corresponds to this network of barns:
```
  (1) 
    \   
     (2)---(4)
    /
  (3)
```
In query 1, we build barn number 1. In query 2, we ask for the distance of 1 to the farthest connected barn. Since barn 1 is connected to no other barns, the answer is 0. In query 3, we build barn number 2 and connect it to barn 1. In query 4, we build barn number 3 and connect it to barn 2. In query 5, we ask for the distance of 3 to the farthest connected barn. In this case, the farthest is barn 1, which is 2 units away. In query 6, we build barn number 4 and connect it to barn 2. In query 7, we ask for the distance of 2 to the farthest connected barn. All three barns 1, 3, 4 are the same distance away, which is 1, so this is our answer.

Problem credits: Anson Hu


---

---
title: "首都"
layout: "post"
diff: 省选/NOI-
pid: P4299
tag: ['搜索', '并查集', '剪枝', '动态树 LCT']
---
# 首都
## 题目描述

在 X 星球上有 $n$ 个国家，每个国家占据着 X 星球的一座城市，城市从 $1$ 至 $n$ 编号。由于国家之间是敌对关系，所以不同国家的两个城市是不会有公路相连的。

X 星球上战乱频发，如果 A 国打败了 B 国，那么 B 国将永远从这个星球消失，而 B 国的国土也将归 A 国管辖。A 国国王为了加强统治，会在 A 国和 B 国之间修建一条公路，即选择原 A 国的某个城市和 B 国某个城市，修建一条连接这两座城市的公路。

同样为了便于统治自己的国家，国家的首都会选在某个使得其他城市到它距离之和最小的城市，这里的距离是指需要经过公路的条数，如果有多个这样的城市，编号最小的将成为首都。

现在告诉你发生在 X 星球的战事，需要你处理一些关于国家首都的信息，具体地，有如下3种信息需要处理：

- `A x y`：表示某两个国家发生战乱，战胜国选择了 $x$ 城市和 $y$ 城市，在它们之间修建公路（保证其中城市一个在战胜国另一个在战败国）。
- `Q x`：询问当前编号为 $x$ 的城市所在国家的首都。
- `Xor`：询问当前所有国家首都编号的异或和。

## 输入格式

输入的第一行有两个整数，分别表示城市数 $n$ 和需要处理的信息数 $m$。

接下来 $m$ 行，每行首先有一个字符串 $op$，表示信息类型，后有若干个整数，其格式如【题目描述】所示。
## 输出格式

对于每个 `Q` 操作和 `Xor` 操作，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
10 10 
Xor 
Q 1 
A 10 1 
A 1 4 
Q 4 
Q 10 
A 7 6 
Xor 
Q 7 
Xor
```
### 样例输出 #1
```
11 
1 
1 
1 
2 
6 
2 

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 10^5$，$1 \leq m \leq 2 \times 10^5$，$1 \leq x, y \leq n$。


---

---
title: "[国家集训队] 飞飞侠"
layout: "post"
diff: 省选/NOI-
pid: P4473
tag: ['2011', '线段树', '并查集', '集训队互测', 'O2优化', '最短路']
---
# [国家集训队] 飞飞侠
## 题目背景

来源：国家集训队 2011 何朴藩
## 题目描述

飞飞国是一个传说中的国度，国家的居民叫做飞飞侠。飞飞国是一个 $N\times M$ 的矩形方阵，每个格子代表一个街区。

然而飞飞国是没有交通工具的。飞飞侠完全靠地面的弹射装置来移动。  

每个街区都装有弹射装置。使用弹射装置是需要支付一定费用的。而且每个弹射装置都有自己的弹射能力。  

我们设第 $i$ 行第 $j$ 列的弹射装置有 $A_{i,j}$ 的费用和 $B_{i,j}$ 的弹射能力。并规定有相邻边的格子间距离是 $1$。那么，任何飞飞侠都只需要在 $(i,j)$ 支付 $A_{i,j}$ 的费用就可以任意选择弹到距离不超过 $B_{i,j}$ 的位置了。如下图  
![https://cdn.luogu.com.cn/upload/pic/17919.png](https://cdn.luogu.com.cn/upload/pic/17919.png)  
（从红色街区交费以后可以跳到周围的任意蓝色街区。）  

现在的问题很简单。有三个飞飞侠，分别叫做 $X, Y, Z$。现在它们决定聚在一起玩，于是想往其中一人的位置集合。告诉你 $3$ 个飞飞侠的坐标，求往哪里集合大家需要花的费用总和最低。（费用相同时优先 $X$，次优先 $Y$）
## 输入格式

输入的第一行包含两个整数 $N$ 和 $M$，分别表示行数和列数。

接下来是 $2$ 个 $N\times M$ 的自然数矩阵，为 $B_{i,j}$ 和 $A_{i,j}$。

最后一行六个数，分别代表 $X, Y, Z$ 所在地的行号和列号。
## 输出格式

第一行输出一个字符 $X, Y$ 或者 $Z$。表示最优集合地点。

第二行输出一个整数，表示最小费用。

如果无法集合，只输出一行 `NO`。  
## 样例

### 样例输入 #1
```
4 4
0 0 0 0
1 2 2 0
0 2 2 1
0 0 0 0
5 5 5 5
5 5 5 5
5 5 5 5
5 5 5 5
2 1 3 4 2 2
```
### 样例输出 #1
```
Z
15
```
## 提示

对于 $20\%$ 的数据，$N, M\leq 10$，$B_{i,j}\leq 20$。 

对于 $40\%$ 的数据，$N, M \leq 100$，$B_{i,j}\leq 20$。

对于 $100\%$ 的数据，$1\leq N, M\leq 150$，$0\leq B_{i, j}\leq 10^9$，$0\leq A_{i, j}\leq 1000$。  


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
title: "Samcompu Loves Water"
layout: "post"
diff: 省选/NOI-
pid: P4865
tag: ['并查集', '枚举']
---
# Samcompu Loves Water
## 题目背景

Samcompu拥有大量的**"水"**资源！！
## 题目描述

Samcompu需要制定一个**水**计划。这个计划的主要目的就是为了避开老师监视的时间来水。

老师在中途会离开机房$T$次，第$i$次将会离开$tim_i$秒。Samcompu划水的时候可不是随便乱水的。他可是拥有**"水"**资源的。在他的库存中有$N$个可以水的网站。Samcompu拥有一种黑科技，他可以几乎不耗任何时间在网站与网站之间跳转并且把跳转的网页的信息秒存。也就是说，Samcompu并不需要在每一次跳转的时候花费时间去浏览网页。当然，这只局限于$N$个网站之间的$N-1$个跳转方式(保证每一个网站都可以跳转到另外的所有网站)。对于第$i$种跳转方式，第$u_i$个网站到第$v_i$个网站的跳转存在一个危险程度$w_i$，这个危险值可能会造成电脑卡死，如果Samcompu不能及时处理，那么就会**完美地**被老师发现。

值得一提的是，在被查水表很多次后，Samcompu总结出了一个规律：

老师走得越久，能够保证在被老师发现之前处理好电脑卡死的危险程度的上限就越高。简单来说，两者就是成正比的关系，比例系数为1。

可惜的是，Samcompu的黑科技并不稳定，在老师第$i$次离开的时候，第$K_i$个跳转方式就不可用了。

当然，每一次水都可以从任意一个网站开始，也可以从任意一个网站结束。

现在Samcompu想知道，对于第$i$次老师离开机房时，他能够有多少种不同的安全的水的方案。两种水的方案不同当且仅当这两种水的方案的第一个网站或者最后一个网站不同。

(补充说明: 一个安全的水的方案当且仅当当前是老师第$j$次离开教室时跳转的路径中不存在一个跳转方式$i$使得$tim_j \leqslant w_i$，每一次水完后不可用的跳转方式就会恢复。)
## 输入格式

第一行两个正整数$T$, $N$

接下来$N-1$行，每一行三个正整数$u_i$, $v_i$, $w_i$

接下来$T$行，每一行两个正整数$tim_i$, $K_i$
## 输出格式

$T$行，每行一个正整数表示有多少中安全的水的方案。
## 样例

### 样例输入 #1
```
3 5
1 2 1
1 3 2
3 4 1
3 5 3
1 1
2 2
3 3

```
### 样例输出 #1
```
0
4
6

```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/25960.png)

第一次连接1和2的边不可用，当前能经过的边的危险程度需要<1，并没有合法的方案。

第二次连接1和3的边不可用，当前能经过的边的危险程度需要<2，合法的方案有  (1,2)    (2,1)    (3,4)    (4,3)  共四种。

第三次连接3和4的边不可用，当前能经过的边的危险程度需要<3，合法的方案有  (1,2)    (1,3)    (2,1)    (2,3)    (3,1)    (3,2)  共六种。

提醒:本题计算答案按照点对的方式计算.也就是说,如果起点和终点一样,则只看做同一种方案.特别的,$(x,y)$和$(y,x)\ (x \neq y)$算作两种不同的方案.

数据范围：

Subtask 1(30 pts):

$$ T=1 \qquad 1 \leqslant K_i \leqslant N \leqslant 10^3 \qquad 1 \leqslant tim_i, w_i \leqslant 10^3 $$

Subtask 2(50 pts):

$$ 1 \leqslant T \leqslant 5*10^3 \qquad 1 \leqslant K_i \leqslant N \leqslant 10^4 \qquad 1 \leqslant tim_i, w_i \leqslant 10^3 $$

Subtask 3(20 pts):

$$ 1 \leqslant T \leqslant 10^4 \qquad 1 \leqslant K_i \leqslant N \leqslant 10^4 \qquad 1 \leqslant tim_i, w_i \leqslant 10^3 $$

数据保证不同的$K_i$最多只有$10^3$个。

温馨提醒：由于出题人数据比较毒瘤，所以请尽量卡常。


---

---
title: "断罪者"
layout: "post"
diff: 省选/NOI-
pid: P4971
tag: ['并查集', '优先队列', '可并堆']
---
# 断罪者
## 题目背景

**重阳节**的地狱……

四季映姬·亚玛萨那度（以下简称四季大人）是地狱的最高裁判长，她平时负责给死者定罪，判断让死者去地狱还是天界，或者别的什么地方。

四季大人当然可以轻松地给死者断罪，但是死者太多了，四季大人需要你帮她断罪，以便腾出时间让她对别人进行说教。
## 题目描述

人们的罪恶值$E$由人们**生前所做过的事**和他的**死亡方式**来决定。他们做过的**坏事**都会有一个罪恶值，这些坏事有可能会并入同一个集合，一个集合的罪恶值为该集合中罪恶值最大的坏事的罪恶值，而他们一生做过的事会**互相影响**，我们将他们生前做过的事分为4种，而最后的罪恶值$E$由其中**所有集合的罪恶值的和**决定。

1. 做坏事——有罪恶值，单独为一集合。  
2. 做好事——将一件坏事的罪恶值清零。
3. 忏悔——将指定集合中，最大罪恶值的事罪恶值减少。
4. 认清自己——将两个坏事集合合并。

而死亡方式可分为 *自然死亡* 、*事故死亡* 和 *自杀* 。

1. 自然死亡，没什么影响。
2. 事故死亡，可以免除最大罪恶的坏事集合。
3. 自杀，最大的坏事集合罪恶值翻倍。

## 输入格式

第一行三个输入 $T,W,K$，代表有 $T$ 个人等待断罪，$W$ 为死亡方式，与描述序号对应，$K$ 含义见输出格式。

接下来的 $T$ 组数据，每组数据第一行两个输入 $n,m$，代表他做过的坏事数量和其他事的数量。

第二行 $n$ 个输入，代表每件坏事的罪恶值。

第 $3$ 到第 $m+2$ 行，每行有三种输入可能。（请联系题目描述进行理解）

- $\verb!2 A!$：表示做好事，将坏事 $A$ 罪恶值**清零**。
- $\verb!3 A B!$：表示忏悔，指定集合为 $A$ 所在的集合，最大罪恶值的事减少 $B$，若最大罪恶值比 $B$ 小，则最大罪恶值的事罪恶值**清零**。**对于罪恶值相等的坏事，认为编号更小的更坏**。
- $\verb!4 A B!$： 表示认清自己，将 $B$ 所在集合与 $A$ 所在的集合合并。
## 输出格式

对于每一个人，一行输出一个字符串和一个整数。

若他的罪恶值为 $0$ 则输出 `Gensokyo`，若他的罪恶值大于 $K$ 则输出 `Hell`，否则输出 `Heaven`。再输出它的罪恶值。

## 样例

### 样例输入 #1
```
1 1 10
5 2
1 2 3 4 5
2 3
4 2 4
```
### 样例输出 #1
```
Heaven 10
```
### 样例输入 #2
```
2 2 8
5 4
4 8 7 5 6
4 2 4
2 2
4 2 3
3 3 2
3 2
5 1 2
2 2
3 3 2
```
### 样例输出 #2
```
Hell 9
Gensokyo 0
```
### 样例输入 #3
```
2 1 15
5 4
1 2 3 4 5
4 2 3
3 2 100
4 1 4
4 4 1
5 4
1 2 3 4 5
3 2 15
4 2 3
4 1 4
4 3 4
```
### 样例输出 #3
```
Heaven 11
Heaven 9
```
## 提示

### 样例 1 解释

一开始有五件坏事，罪恶值分别为 $1.2.3.4.5$，做好事之后，罪恶值分别为 $1.2.0.4.5$，认清自我后，只剩下四个集合，罪恶值分别是 $1.4.0.5$，由于是自然死亡，所以最后的罪恶值 $E=1+4+5=10 \le K \&\& E!=0$，因此输出 $Heaven$

### 样例 2 解释

对于样例2的第一组输入如下图，黑色椭圆代表一个集合，红色为罪恶值，下面为点的编号，由于是事故死亡，可以免去标号5的最大值，故罪恶值为$E=4+5$  
![](https://cdn.luogu.com.cn/upload/pic/72405.png)

### 说明

所有数据均在长整型范围内，对于所有数据，均有$m\le n$,$1\le K$，保证输入不存在负数。  
由于读入数据可能会很大，建议使用较快的读入。

> 约定 ① 对于合并两个集合的操作，至少有一个集合只有一件坏事；
> 约定 ② 这群人不会做好事。

| 测试点编号 |    T    |      n       |  时限  | 约定 |
|:-:|:-:|:-:|:-:|:-:|
|		  1   | $\le10$ |   $\le100$   | $1s$ | ①② |
|		  2   | $\le10$ |   $\le300$   | $1s$ | ①  |
|		  3   | $\le10$ |   $\le500$   | $1s$ |    |
|		  4   | $\le20$ |  $\le1000$   | $1s$ | ①② |
|		  5   | $\le20$ |  $\le3000$   | $1s$ | ①  |
|		  6   | $\le20$ |  $\le7000$   | $1s$ |    |
|		  7   | $\le30$ |  $\le10000$  | $1s$ | ①② |
|		  8   | $\le30$ |  $\le30000$  | $1s$ | ①  |
|		  9   | $\le30$ |  $\le50000$  | $1s$ |    |
|		 10   | $\le30$ |  $\le70000$  | $1s$ | ①② |
|		 11   | $\le10$ | $\le100000$  | $1s$ | ①  |
|		 12   | $\le10$ | $\le150000$  | $1s$ |    |
|		 13   | $\le10$ | $\le200000$  | $1s$ | ①② |
|		 14   | $\le10$ | $\le500000$  | $1s$ | ①  |
|		 15   | $\le10$ | $\le1000000$ | $2s$ |    |
|		 16   | $\le10$ | $\le1000000$ | $2s$ | ①② |
|		 17   | $\le10$ | $\le1000000$ | $2s$ | ①  |
|		 18   | $\le10$ | $\le2000000$ | $2s$ |    |
|		 19   | $\le10$ | $\le2000000$ | $2s$ |    |
|		 20   | $\le10$ | $\le2000000$ | $2s$ |    |
|		 21   | $1$ | $\le2000000$ | $2s$ |  路径压缩  |




---

---
title: "不围棋"
layout: "post"
diff: 省选/NOI-
pid: P4997
tag: ['模拟', '并查集', 'Special Judge', '连通块', '洛谷月赛']
---
# 不围棋
## 题目背景

「不围棋」是一种非常有趣的棋类游戏。

大家都知道，围棋的「气」是指一个棋子所在的联通块相邻的空格。两粒棋如果在棋盘上线段的两端就认为是相邻的，也就是在同一个连通块里。比如在图中，白子为四个独立的连通块，黑子构成一个连通块，绿色点是黑子连通块唯一的「气」：

![](https://cdn.luogu.com.cn/upload/pic/41011.png )

「提子」是指将没有「气」的棋子提出棋盘，在上图中，如果白方走绿点，那么就可以将黑子全部提走。

在围棋中，我们想尽量多地占领地盘、提走对方棋子。然而，不围棋恰恰相反——不围棋是一种非常和平的游戏，双方的走子不能产生任何提子，也就是说，**任何一次走子不能让棋盘上任何一个棋子所在的连通块没有气**。比如，白方在上图中不能走绿点。

在你的某一步棋后，对方无棋可走，那么你就赢了。
## 题目描述

小 F 对不围棋特别感兴趣，不过他经常输，所以他想做出一个 AI 来替他完成这局游戏。

不过造 AI 实在是太困难啦，小 F 千辛万苦写出来的 AI 被同学们的 AI 锤爆啦！

现在，他想请你帮他实现一个 AI 中一部分的功能——随机模拟，因为他相信你写的程序非常优秀，一定能优化他的 AI。

给你一个 $n \times n$ 的棋盘，上面或许已经有一些棋子了，但此时局面一定是合法的，即**不存在没有气的连通块**；此时轮到黑棋下棋，因此棋盘上**黑白棋子的数量一定是相等的**。

你的任务是，**依次**为黑棋和白棋**随意**指定一个可行的走子位置，直到某一步游戏无法进行，决出胜负为止。

在正式的不围棋比赛还存在一些禁手规则。不过由于小 F 玩的是一种棋盘大小可变的新型不围棋，我们只用考虑上面提到的气的规则就好。
## 输入格式

输入一行一个整数 $n$，表示棋盘大小。
输入接下来 $n$ 行，每行有一个长度为 $n$ 的字符串，表示第 $i$ 行的情况。

* `.` 表示空
* `X` 表示黑棋
* `O` 表示白棋

详细请参考样例。

输入保证，棋盘初始局面合法，`X` 与 `O` 数量相等。
## 输出格式

你需要输出至少一行，假设你输出了 $L$ 行，那么对于前 $L - 1$ 行，你应该输出两个用空格分隔的正整数表示下棋坐标 $x_i, y_i$，其中奇数行表示黑棋的行动，偶数行表示白棋的行动。$x$ 坐标为从上到下从 $1$ 到 $n$，$y$ 坐标为从左到右从 $1$ 到 $n$。

请在第 $L$ 行输出 `-1 -1`，表示此时第 $L$ 手执棋人已经无棋可走。

你的输出可能会很大，即使本题时限为 $3s$，也请你不要使用太慢的方法输出大量内容。

#### 评分方式：

本题启用 Special Judge，并且有部分分。我们将通过以下方式进行计分：

* 如果你输出格式错误，那么该测试点不得分。格式错误包括但不限于：输出了非数字内容；一行输出了超过或者少于两个正整数；输出的坐标在棋盘外；最后一行的输出不是 `-1 -1`。
* 如果你的输出格式正确，但是你的输出的第一行的答案就是不可接受的，那么该测试点不得分。例如：输出的坐标是黑棋不可以下的位置；黑棋有棋可走却输出了 `-1 -1`。
* 如果你的输出格式正确，并且你的前 $k(1 \leq k <L)$ 行输出是可以接受的，那么该测试点将至少得到 $s$ 分，其中 $s = \lfloor \lg k \rfloor + 1$，含义是 $k$ 在十进制表示下是一个 $s$ 位数。
* 如果你的输出完全正确，无论你输出了多少行，你都将得到 $10$ 分。

详情请参考样例解释。
## 样例

### 样例输入 #1
```
3
XXX
OOX
OO.
```
### 样例输出 #1
```
-1 -1
```
### 样例输入 #2
```
3
XOO
XO.
X..
```
### 样例输出 #2
```
2 3
-1 -1
```
## 提示

#### 样例 1 解释：

注意到将棋盘下满会让棋盘上所有连通块都没有气，所以黑棋是无棋可走的。

#### 样例 2 解释：

样例 2 还有两个正确的输出是这样的：
```
3 2
2 3
-1 -1
```
```
3 3
2 3
-1 -1
```
我们将棋盘表示出来：

![](https://cdn.luogu.com.cn/upload/pic/41216.png)

其中，黑棋是三个空格都可以走的。

* 如果黑棋走 $(2, 3)$，如图，此时白棋走任何位置都会提走相邻的黑棋，白棋无棋可走；
 ![](https://cdn.luogu.com.cn/upload/pic/41219.png)

* 如果黑棋走 $(3, 2)$，如图，此时白棋唯一可走的点是 $(2, 3)$，之后黑棋无棋可走；
 ![](https://cdn.luogu.com.cn/upload/pic/41218.png)

* 如果黑棋走 $(3, 3)$，如图，此时白棋唯一可走的点是 $(2, 3)$，之后黑棋无棋可走；
 ![](https://cdn.luogu.com.cn/upload/pic/41217.png)

这三种情况依次对应三个输出，输出任意一种可得到满分。

#### 评分规则解释：

为了解释评分规则，我们以样例 2 为例，对于以下几种输出：
```
I AK IOI
```
很不幸，因为您太强了，所以为了按住躁动的您，我们会给您 $0$ 分。

```
-1 -1
```
```
1 1
-1 -1
```
很不幸，你的第一行没有输出正确，得 $0$ 分。

```
3 3
-1 -1
```
你输出的前 $1$ 行是正确方案的一部分。由于 $1$ 是 $1$ 位数，恭喜你得到了整整 $1$ 分！

#### 数据范围：

![](https://cdn.luogu.com.cn/upload/pic/41855.png)


---

---
title: "[AHOI2013] 连通图"
layout: "post"
diff: 省选/NOI-
pid: P5227
tag: ['2013', '线段树', '并查集', '各省省选', '安徽', 'O2优化', '动态树 LCT']
---
# [AHOI2013] 连通图
## 题目描述

给定一个无向连通图和若干个小集合，每个小集合包含一些边，对于每个集合，你需要确定将集合中的边删掉后改图是否保持联通。集合间的询问相互独立

定义一个图为联通的当且仅当对于任意的两个顶点，都存在一条路径连接它们
## 输入格式

第一行为两个整数 $n,m$，代表无向图的点数和边数

下面 $m$ 行，包含两个整数 $u,v$，代表该边连接点 $u,v$。第 $i + 1$ 行的边的编号为 $i$。保证不存在重边和自环

下面一行包含一个整数 $k$，表示集合个数

下面 $k$ 行每行描述一个集合，每行的第一个数为集合中边的个数 $c$，后面 $c$ 个数代表集合内的边
## 输出格式

对于每个集合，输出一行代表去掉该集合中的边后图是否联通，如果联通输出 ``Connected``，否则输出 ``Disconnected``
## 样例

### 样例输入 #1
```
4 5
1 2
2 3
3 4
4 1
2 4
3
1 5
2 2 3
2 1 2
```
### 样例输出 #1
```
Connected
Disconnected
Connected
```
## 提示

$1~\leq~n,k~\leq~10^5$

$1~\leq~m~\leq~2~\times~10^5$

$1~\leq~c~\leq~4$


---

---
title: "最小mex生成树"
layout: "post"
diff: 省选/NOI-
pid: P5631
tag: ['线段树', '并查集', 'O2优化', '分治', '动态树 LCT']
---
# 最小mex生成树
## 题目背景

这是一道经典题。
## 题目描述

给定 $n$ 个点 $m$ 条边的无向连通图，边有边权。  

设一个自然数集合 $S$ 的 $\text{mex}$ 为：最小的、没有出现在 $S$ 中的自然数。  

现在你要求出一个这个图的生成树，使得其边权集合的 $\text{mex}$ 尽可能小。
## 输入格式

第一行输入两个正整数 $n,m$。

接下来 $m$ 行，每行 $3$ 个非负整数 $u,v,w$，表示 $u,v$ 之间有一条权值为 $w$ 的边。

## 输出格式

输出一行一个自然数，表示最小的 $\text{mex}$ 值。
## 样例

### 样例输入 #1
```
3 3
1 2 0
2 3 1
3 2 2

```
### 样例输出 #1
```
1
```
## 提示

【数据范围】   
- 对于 $20\%$ 的数据，$1\le n \le 100$，$1\le m \le 200$。
- 对于 $50\%$ 的数据，$1\le n \le 2000$，$1\le m \le 3000$。
- 对于 $80\%$ 的数据，$1\le n \le 10^5$，$1\le m \le 2\times 10^5$。
- 对于 $100\%$ 的数据，$1\le n \le 10^6$，$1\le m \le 2\times 10^6,0\le w \le 10^5$。

输入数据规模较大，建议使用高效的读入方式。


---

---
title: "【化学】实验"
layout: "post"
diff: 省选/NOI-
pid: P5881
tag: ['图论', '并查集', 'O2优化', '素数判断,质数,筛法']
---
# 【化学】实验
## 题目背景

小 Z 紧张地坐在了一张化学实验桌前，进行着化学实验。

教室里又传来了一阵哀叹声：

我…我好像又错了…我能再试一次吗?
## 题目描述

在她的面前，摆放着 $n$ 个试管。试管里装着不明液体。对于每种不明液体，有 $2$ 个已知的化学属性：$a$ 和 $b$。第 $i$ 种液体的两个属性值分别为 $a_i$ 和 $b_i$。

现在，老师给她布置了 $m$ 个实验。

对于每一次实验，有一个参照量 $x$（第 $i$ 次实验的参照量记作 $x_i$）。她需要把不明液体分成尽可能多的组，且满足：任意两种不同组的液体$i$和$j$， $\operatorname{gcsd(a_i,a_j)}$ 都不能大于 $x^2$。

其中 $\operatorname{gcsd}$ 代表他们的最大公约平方数。$k$是两个数的公约平方数，当且仅当满足以下两个条件：

- $k$ 为这两个数的公约数；

- $k$ 为完全平方数。

而最大公约平方数 $\operatorname{gcsd}$ 为所有满足条件的 $k$ 中的最大者。

形象的说， $\operatorname{gcsd}$ 可以理解成两个数的最大公约数的算术平方根的整数因式部分的平方。

例如：

求 $\operatorname{gcsd(24,64)}$，就是先求出 $24,64$ 的最大公约数，是 $8$ ，然后 $\sqrt 8=2\sqrt 2$，其整数因式是 $2$，所以 $\operatorname{gcsd(24,64)}=2^2=4$。

她还需要在分组数最多的情况下，使自己的实验得分最大。

实验得分的定义：对于每一种试剂，定义其得分 $c_i$ 为 $b_i$ 分解质因数之后最大的**指数**。

例如：$b_i=12=2^2\times 3^1$，$c_i=\max\{2,1\}=2$。

$b_i=90=2^1\times 3^2\times 5^1$，$c_i=\max\{1,2,1\}=2$。

而实验得分即为所有组内的 $c_i$ 的最大值之和。

当然，她的 $IQ$ 并不高，所以需要请求你的帮助。
## 输入格式

第一行两个整数 $n,m$。

第二行 $n$ 个整数 $a_{1\dots n}$。

第三行 $n$ 个整数 $b_{1\dots n}$。

第四行 $m$ 个整数 $x_{1\dots m}$。
## 输出格式

共 $m$ 行，对于第 $i$ 行，输出 $2$ 个整数：第 $i$ 次试验的组数和实验得分。
## 样例

### 样例输入 #1
```
5 5
36 72 4 9 16
2 4 6 8 10
2 3 4 5 6

```
### 样例输出 #1
```
3 5
4 7
4 7
4 7
5 8
```
## 提示

#### 样例解释 #1

$b_1=2=2^1,c_1=1$。

$b_2=4=2^2,c_2=2$。

$b_3=6=2^1\times 3^1,c_3=\max\{1,1\}=1$。

$b_4=8=2^3,c_4=3$。

$b_5=10=2^1\times 5^1,c_5=\max\{1,1\}=1$。

当 $x=2$ 时，可分为三组：$\{1,2,4\},\{3\},\{5\}$。

实验得分为$\max\{1,2,3\}+\max\{1\}+\max\{1\}=5$。

----------

#### 数据范围

**「本题采用捆绑测试」**

| subtask | $n\le$ | $m\le$ | $a_i \le$ | $b_i\le$ | $x \le$ | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |:-----------:|
| $1$ | $4$ | $6$ | $100$ | $4 \times 10^4$ | $100$ | $5$ |
| $2$ | $8$ | $7$ | $20$ | $10^3$ | $10$ | $5$ |
| $3$ |$20$ | $30$ | $50$ | $8 \times 10^3$ | $100$ | $10$ |
| $4$ |$100$ | $60$ | $100$ | $4 \times 10^4$ | $10^3$ | $10$ |
| $5$ |$5 \times 10^3$ | $110$ |  $10^3$| $10^5$ | $4 \times 10^3$ | $10$ |
| $6$ |$2 \times 10^4$ | $250$ | $3 \times 10^3$ | $10^6$ | $3 \times 10^3$ | $10$ |
| $7$ |$ 5 \times 10^4$| $10^3$ | $10^4$ | $2 \times 10^7$ | $1.5 \times 10^4$ | $15$ |
| $8$ |$10^5$  | $8 \times 10^3$ | $2 \times 10^4$ | $2 \times 10^7$ | $2.2 \times 10^4$ | $15$ |
| $9$ |$2 \times 10^5$  | $2 \times 10^5$ | $4 \times 10^4$ | $2 \times 10^7$ | $3 \times 10^4$ | $20$ |


对于 $100\%$ 的数据：

$1 \le n,m \le 2\times 10^5$，$2 \le a_i \le 4\times 10^4$，$2 \le b_i \le 2\times 10^7$，$2 \le x \le 3\times 10^4$。

我$\dots$我好像又错了$\dots$我能再试一次吗?


---

---
title: "[PA 2011] Hard Choice"
layout: "post"
diff: 省选/NOI-
pid: P6351
tag: ['2011', '并查集', 'PA（波兰）']
---
# [PA 2011] Hard Choice
## 题目描述

有一个 $n$ 个点，$m$ 条边的无向图。

有 $q$ 次询问，每次询问包含一个字符 $opt$ 和两个整数 $x,y$。

若 $opt$ 为 $Z$，表示一次删除操作，删去边 $x,y$，保证 $x,y$ 这条边之前没有被删除，但不保证图上存在边（也就是说，可能会删去所有的边）。

若 $opt$ 为 $P$，表示一次询问，询问 $x,y$ 之间是否有两条完全不同的路径，这里的完全不同指没有经过相同的边，但可以经过相同的点。
## 输入格式

第一行三个整数 $n,m,q$，意义同题面。

接下来 $m$ 行，每行两个数 $x,y$，表示 $x,y$ 之间存在一条无向边。

接下来 $q$ 行，每行包含一个字符 $opt$ 和两个整数 $x,y$，意义同题面。


## 输出格式

对于每一次 $opt$ 为 $P$ 的询问，如果存在两条完全不同的路径，输出一行一个字符串 TAK，否则输出一行一个字符串 NIE。
## 样例

### 样例输入 #1
```
7 8 7
1 2
1 3
1 4
2 3
3 4
3 7
7 4
5 6
Z 1 4
P 1 3
P 2 4
Z 1 3
P 1 3
Z 6 5
P 5 6

```
### 样例输出 #1
```
TAK
TAK
NIE
NIE
```
## 提示

$2\leq n\leq 10^5$，$1\leq m,q\leq 10^5$，保证输入数据合法且不存在重边和自环。


---

---
title: "[省选联考 2020 B 卷] 丁香之路"
layout: "post"
diff: 省选/NOI-
pid: P6628
tag: ['贪心', '2020', '并查集', '各省省选', '生成树', '欧拉回路']
---
# [省选联考 2020 B 卷] 丁香之路
## 题目描述

春暖花开，万物复苏，随着疫情的逐渐过去，Yazid 带着他的 $n$ 个好朋友来到 T 大校园参观游览。方便起见，我们将他们从 $1$ 至 $n$ 编号。

T 大校园的版图可以抽象成一张 $n$ 个顶点的无向图（顶点编号从 $1$ 至 $n$）。且对于任意两个不同顶点，设它们的编号分别为 $i, j(i\neq j)$，则它们之间有一条需要花费 $|i - j|$ 单位时间通过的无向边。

丁香花是 T 大的校花之一。时下正值丁香花盛开之际，校园内的 $m$ 条道路上都开有丁香花。Yazid 的朋友们对丁香花十分感兴趣，因此他们都希望遍历**所有**开有丁香花的 $m$ 条道路。

Yazid 的朋友们从顶点 $s$ 出发。其中，第 $i$ 个朋友希望以顶点 $i$ 为终点终止他的参观。与此同时，如上面所述，每个朋友都必须经过开着丁香花的 $m$ 条道路各至少一次。

Yazid 的朋友不想太过疲累，因此他们希望花尽可能少的时间来完成他们的目标。

请你计算 Yazid 的朋友们分别需要花费多少单位时间完成他们的目标。
## 输入格式

第一行 $3$ 个非负整数 $n, m, s$。保证 $1\le s\le n$；保证 $m\le \frac {n(n-1)}2$。

第 $2$ 行至第 $m+1$ 行，每行 $2$ 个整数 $u, v$，描述一条开有丁香花的，连接顶点 $u, v$ 的无向边。保证 $1\le u, v\le n$ 且 $u\neq v$；保证每条无向边至多被描述一次。

对于输入的所有行，用单个空格将行内的多个整数隔开。
## 输出格式

输出一行 $n$ 个用单个空格隔开的整数，其中第 $i$ 个整数描述 Yazid 的第 $i$ 个朋友完成目标所需花费的最少时间。

## 样例

### 样例输入 #1
```
4 3 1
1 2
4 2
3 1
```
### 样例输出 #1
```
6 7 8 7
```
### 样例输入 #2
```
6 0 2
```
### 样例输出 #2
```
1 0 1 2 3 4
```
### 样例输入 #3
```
5 4 1
1 2
3 4
4 5
3 5
```
### 样例输出 #3
```
8 7 6 7 8
```
## 提示

**样例解释 1**

第 $1$ 个朋友的一种最优路线是从 $1$ 出发依次途径 $2, 4, 3$，最终回到 $1$，消耗 $|1-2|+|2-4|+|4-3|+|3-1| = 6$ 单位时间。

第 $2$ 个朋友的一种最优路线是从 $1$ 出发依次途径 $2, 4, 3, 1$，最终来到 $2$，消耗 $7$ 单位时间。

第 $3$ 个朋友的一种最优路线是从 $1$ 出发依次途径 $2, 4, 1$，最终来到 $3$，消耗 $8$ 单位时间。

第 $4$ 个朋友的一种最优路线是从 $1$ 出发依次途径 $3, 1, 2$，最终来到 $4$，消耗 $7$ 单位时间。

**样例解释 2**

由于 $m = 0$，没有必经之路，因此每个朋友直接通过一条边直达目的地即可。


**数据范围与约定**

| 测试点编号  |  $n=$  | 其他特殊限制 |
| --------- | ---- | ---------- |
|  $1\sim 3$  |  $50$  |    $m=9$     |
|  $4\sim 6$  |  $50$  |    $m=15$    |
|  $7\sim 8$  |  $50$  |              |
| $9\sim 10$  | $300$  |              |
|    $11$     | $1600$ |    $m=0$     |
| $12\sim 14$ | $1600$ |    $m=1$     |
| $15\sim 17$ | $1600$ |              |
| $18\sim 20$ | $2500$ |              |


---

---
title: "[ONTAK2015] Bajtocja"
layout: "post"
diff: 省选/NOI-
pid: P8026
tag: ['2015', '并查集', '树上启发式合并', '哈希 hashing']
---
# [ONTAK2015] Bajtocja
## 题目描述

给定 $d$ 张无向图，每张图都有 $n$ 个点。一开始，在任何一张图中都没有任何边。接下来有 $m$ 次操作，每次操作会给出 $a, b, k$，意为在第 $k$ 张图中的点 $a$ 和点 $b$ 之间添加一条无向边。你需要在每次操作之后输出有序数对 $(a, b)$ 的个数，使得 $1 \leq a, b \leq n$，且 $a$ 点和 $b$ 点在 $d$ 张图中都连通。
## 输入格式

第一行，三个整数 $d, n, m$；

接下来 $m$ 行，每行三个整数 $a, b, k$。
## 输出格式

$m$ 行，每行一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
3 4 10
1 2 1
2 1 2
1 2 3
3 4 1
1 3 2
2 3 3
2 4 2
3 4 3
3 4 2
1 3 1
```
### 样例输出 #1
```
4
4
6
6
6
6
6
8
8
16
```
## 提示

对于 $100\%$ 的数据，$1 \leq d \leq 200$，$1 \leq n \leq5 \times 10^3$，$1\leq m \leq 10^6$，$1 \leq a, b \leq n$，$1 \leq k \leq d$。


---

---
title: "「DAOI R1」Fireworks"
layout: "post"
diff: 省选/NOI-
pid: P8288
tag: ['并查集', '树形 DP', '拓扑排序', '基环树']
---
# 「DAOI R1」Fireworks
## 题目背景

> 俯首，满城灯火交辉。
> 
> 回眸，漫天流星逆飞。
## 题目描述

人们以前通常会放烟花，而每个烟花都有它本身的美观度。

$ \texttt{Iratis} $ 想要在户外放烟花，但是有烟花之间有一些关系：

- 关系一：对于烟花 $ x $ ，有一个对应烟花 $ a_x $ ，若烟花 $ x $ 与烟花 $ a_x $ 一起燃放，就会使烟花 $ x $ 的美观度减少 $ b_x $ 。

- 关系二：有一些烟花是一个系列，必须同时燃放，其中有一个是主烟花，**每个烟花只会属于一个系列**。

特别地，若有一系列 $ S_1 $ （主烟花为 $ p_1 $ ） 。 $ p_1 $ 关系一所对应的烟花为系列 $ S_2 $ 中的烟花。而 $ S_1 $ 系列中的其他烟花与非 $ S_1,S_2 $ 系列中的烟花形成关系一。**那么对于这条关系一，它不会降低美观度。**

$ \texttt{Iratis} $ 家里有 $ n $ 个烟花，他希望选择其中的一些烟花燃放，使得这些**烟花的美观度总和**最大。
## 输入格式

第一行包含两个整数 $ n,m $，分别描述烟花的个数和和关系二的个数。

接下来 $ n $ 行，每行三个整数 $ v_i,a_i,b_i $ ，分别是这个烟花的美观度、关系一对应的烟花、关系一降低的美观度。

最后 $ m $ 行，每行先读入两个数 $ p_i,k_i $，然后是 $ k_i $ 个数，表示这 $ k_i $ 个烟花是一个系列，编号为 $ p_i $ 的烟花为主烟花。
## 输出格式

输出一行一个整数，表示烟花的美观度总和。
## 样例

### 样例输入 #1
```
3 0
2 2 1
2 3 1
2 1 1

```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4 1
3 2 1
3 1 3
3 4 2
3 3 2
1 2 1 3

```
### 样例输出 #2
```
7
```
## 提示

### 样例解释
#### 样例1解释

烟花 $ 1,2,3 $ 一起燃放，最大美观度为 $ 2+2+2-1-1-1=3 $ 。

#### 样例2解释

烟花 $ 1,3,4 $ 一起燃放。

由于 $ 1,3 $ 为同一系列且 $ 1 $ 为主烟花，所以 $ 3 $ 烟花的关系一不会生效。

故总的美观度为 $ 3 \times 3-2=7 $ 。

### 数据规模

**本题采用捆绑测试**

| Subtask | $ m $  | 分值 |
| :----------: | :----------: | :----------: |
| $ 0 $ | $ =0 $ | $ 30 $ |
| $ 1 $ | 无特殊限制 | $ 70 $ |

对于 $ 100\% $ 的数据，满足 $ 0 \leq m \leq n \leq 5 \times 10^5,0 \leq b_i \leq v_i \leq 10^{12},1 \leq a_i \leq n,a_i \neq i $ 。 


---

---
title: "「HGOI-1」Water"
layout: "post"
diff: 省选/NOI-
pid: P8485
tag: ['并查集', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「HGOI-1」Water
## 题目背景

$\text{uuku}$ 每天都给他的线段树浇水。但由于线段树是平面的，所以 $\text{uuku}$ 用一个二维的水桶给它浇水。
## 题目描述

水桶可以描述为一个 $h\times w$ 的竖直平面，其中 `.` 表示空格，`#` 表示挡板，保证除顶面外所有边界均有 `#`。

$\text{uuku}$ 给水桶装水的方式很奇特：他希望在装水完成的瞬间水不流动。即对于任意一格存在水的位置，其左右和下方均有水或者挡板。并且如果一格水的上方是空格，则称之为水平面，如果上方是挡板或者水桶外部，则称之为上界面。水形成的四连通块内的所有水平面都要一样高且所有上界面都应该不高于水平面（该条件即为在真空环境且存在重力时水不流动）。

从装水完成后开始计时，每秒都会进行一次扩展。每次扩展所有水平面都会向上方的空格**扩展一层**，并填充**高度小于等于新扩展层的**所有可达的空格（可以理解为仍满足 $\text{uuku}$ 的上述要求），这一切可以看作是瞬间完成的。

神奇的水会一直扩展，直到**所有可达的空格**均被水填满后停止扩展，即不存在水平面。

现在 $\text{uuku}$ 想知道，对于所有符合他要求的装水方案，所有水停止扩展所需时间的**平均值**是多少。

## 输入格式

第一行两个整数 $h$，$w$，表示水桶的高度和宽度。

接下来 $h$ 行，每行 $w$ 个字符，其中 `.` 表示空格，`#` 表示挡板。
## 输出格式

一行一个整数，表示 $\text{uuku}$ 给水桶装水需要的时间的平均值，由于答案可能很大，所以你只需要给出对 $998244353$ 取模以后的结果。
## 样例

### 样例输入 #1
```
3 9
#...#...#
#.#...#.#
#########
```
### 样例输出 #1
```
110916040
```
### 样例输入 #2
```
10 20
###...###....#######
##..#.####.##.######
##.##.####.#.#.#####
#.#..##..###.#.....#
#..##.#.#....###.#.#
####....#.##.#..##.#
##..###.#.#..#.##..#
###...#..##.##..##.#
#.#.#.##.##.##..####
####################
```
### 样例输出 #2
```
966268884
```
### 样例输入 #3
```
10 20
#####.######.####.##
####.#.#####.###.###
###.###.####.##.####
###.###.####.#.#####
##.#####.###..######
##.......###.#.#####
#..#####..##.##.####
#.#######.##.###.###
#.#######.##.####.##
####################
```
### 样例输出 #3
```
581693010
```
## 提示

#### 样例 1 解释

装水无需时间。

共有 $9$ 种情况（`*` 表示水）：

$1$：

```
#...#...#
#.#...#.#
#########
```
需要 $0\text{s}$。

$2$：

```
#...#...#
#*#...#.#
#########
```
需要 $1\text{s}$。

$3$：

```
#...#...#
#*#***#.#
#########
```
需要 $1\text{s}$。

$4$：

```
#...#...#
#*#***#*#
#########
```
需要 $1\text{s}$。

$5$：

```
#...#...#
#.#***#.#
#########
```

需要 $1\text{s}$。

$6$：

```
#...#...#
#.#***#*#
#########
```

需要 $1\text{s}$。

$7$：

```
#...#...#
#*#...#*#
#########
```

需要 $1\text{s}$。

$8$：

```
#...#...#
#.#...#*#
#########
```

需要 $1\text{s}$。

$9$：

```
#***#***#
#*#***#*#
#########
```

需要 $0\text{s}$。

因此期望为 $\dfrac{7}{9}\equiv 110916040(\bmod 998244353)$。

#### 数据范围

本题采用**捆绑测试**，共有 $5$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & h,w\le \cr\hline
1 & 10 &  10 \cr\hline
2 & 20 &  100 \cr\hline
3 & 20 &  500 \cr\hline
4 & 20 &  2000 \cr\hline
5 & 30 &  5000 \cr\hline
\end{array}
$$


对于 $100\%$ 的数据，$1 \le h,w \le 5000$。


---

---
title: "[JRKSJ R7] 月下缭乱"
layout: "post"
diff: 省选/NOI-
pid: P8936
tag: ['线段树', '并查集', '2023', '颜色段均摊（珂朵莉树 ODT）', '洛谷原创', 'O2优化']
---
# [JRKSJ R7] 月下缭乱
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/xkd5zhgk.png?x-oss-process=image)

轻快的音乐声坚定了你做一道简单题的决心。

（题目背景图片来自 Phigros 曲绘，如有侵权，请告知出题人。）
## 题目描述

你有一个长度为 $n$，初值全为 $0$ 的序列 $a$。

你有长为 $m$ 的操作序列，其中第 $i$ 次有三个参数 $l_i,r_i,x_i$，表示令 $\forall j\in[l_i,r_i] ,a_j\gets\max(a_j,x_i)$。

令 $\text{sol}(l,r)$ 表示依次操作第 $l$ 至第 $r$ 个操作后的 $a$ 序列。

你需要回答有多少对 $(l,r)$ 满足 $1\le l\le r\le m$ 且 $\text{sol}(l,r)=\text{sol}(1,m)$。

记 $f_i$ 为有多少 $i\le k\le m$ 满足 $\text{sol}(i,k)=\text{sol}(1,m)$，你还需要输出 $\displaystyle\bigoplus_{i=1}^m f_i\times i$ 与 $\displaystyle\sum_{i=1}^m f_i\times i$ 的值。

所有答案都需要对 $2^{32}$ 取模后输出。
## 输入格式

第一行两个整数 $n,m$。\
接下来 $m$ 行，每行三个整数 $l_i,r_i,x_i$，表示第 $i$ 个操作。
## 输出格式

一行三个整数表示答案。
## 样例

### 样例输入 #1
```
5 5
1 3 1
2 4 1
2 3 1
1 3 1
1 4 1

```
### 样例输出 #1
```
9 2 20
```
### 样例输入 #2
```
3 5
1 3 2
1 1 1
2 2 2
3 3 3
1 3 2

```
### 样例输出 #2
```
5 7 11
```
## 提示

Idea：cyffff，Solution：Ntokisq / abruce，Code：cyffff，Data：cyffff

**月下缭乱 - 月見静華 vs. LUNARiUM (Insane14.8)**

**本题输入输出文件较大，请使用恰当的输入输出方式。**

### 样例解释

对于样例 $1$，最终 $a$ 序列的值为 $\{1,1,1,1,0\}$。不难发现，进行 $[1,2],[1,3],[1,4],[2,4],[1,5],[2,5],$$[3,5],[4,5],[5,5]$ 内的操作都可以使得 $a$ 与进行所有操作后 $a$ 序列的值相同。答案为 $9$。$f$ 序列为 $\{4,2,1,1,1\}$。

对于样例 $2$，最终 $a$ 序列的值为 $\{2,2,3\}$。不难发现，进行 $[1,4],[1,5],[2,5],[3,5],[4,5]$ 内的操作都可以使得 $a$ 与进行所有操作后 $a$ 序列的值相同。答案为 $5$。$f$ 序列的值为 $\{2,1,1,1,0\}$。

### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n,m\le$ | 特殊限制 | $\text{Score}$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $100$ | 无 | $10$ |
| $2$ | $10^4$ | 无 | $20$ |
| $3$ | $3\times10^5$ | 保证 $l_i=r_i$ | $10$ |
| $4$ | $3\times10^5$ | 保证 $x_i=1$ | $10$ |
| $5$ | $3\times10^5$ | 无 | $20$ |
| $6$ | $10^6$ | 无 | $30$ |

对于 $100\%$ 的数据，$1\le n,m\le10^6$，$1\le l_i\le r_i\le n$，$1\le x_i\le m$。
### 特殊评分方式
本题开启子任务依赖，具体如下：
- 对于子任务 $i\in\{1,3,4\}$，您只需答对子任务 $i$ 即可获得子任务 $i$ 的分数。
- 对于子任务 $i\in\{2,5,6\}$，您需要答对所有 $j\in[1,i]$ 的子任务 $j$ 才能获得子任务 $i$ 的分数。


---

---
title: "『STA - R2』机场修建"
layout: "post"
diff: 省选/NOI-
pid: P9410
tag: ['并查集', 'O2优化', '分块', '根号分治']
---
# 『STA - R2』机场修建
## 题目背景

智利在修机场。  
## 题目描述

有 $n$ 个城市排成一列，最开始是互不连通的。  
每个城市初始都没有人口。  
会出现以下操作 / 查询共 $m$ 个：  

1. `1 x y` 开通城市 $x$ 和城市 $y$ 之间的双向航班。  
2. `2 l r a` 城市 $[l, r]$ 的人口数都 $+a$。  
3. `3 x` **如果**所有能够到达城市 $x$ 的人都来到城市 $x$，城市 $x$ 有多少人。  
## 输入格式

第一行两个数 $n, m$。  
接下来 $m$ 行，每行一个操作。  
## 输出格式

对于所有的操作 $3$ ，输出答案。  
## 样例

### 样例输入 #1
```
5 5
1 2 4
2 3 5 2
3 2
1 2 5
3 2
```
### 样例输出 #1
```
2
4
```
## 提示

**本题捆绑测试。**  
- Easy（5pts）：$1 \le n, m \le 2 \times 10^5$，且不存在操作 $1$。  
- Normal（10pts）：$1 \le n, m \le 1000$。  
- Hard（20pts）：$1 \le n, m \le 10^5$，且操作 $3$ 之后不存在操作 $2$。  
- Lunatic（30pts）：$1 \le n, m \le 5 \times 10^4$。 
- Overdrive（35pts）：$1 \le n, m \le 2 \times 10^5$。  

对于 $100\%$ 的数据，$1\le n,m\le 2\times 10^5$，$0 \le a \le 10^9$。保证答案在 64 位有符号整形表示的范围内。

![](https://cdn.luogu.com.cn/upload/image_hosting/dgqoqa8d.png)  
出于某些原因，给了较多的部分分。  


---

---
title: "『GROI-R2』 Beside You"
layout: "post"
diff: 省选/NOI-
pid: P9655
tag: ['并查集', '树上启发式合并', '洛谷原创', 'O2优化', '树形 DP', '最近公共祖先 LCA', '树论', '虚树', '洛谷月赛']
---
# 『GROI-R2』 Beside You
## 题目背景

記憶の森

始まりの謎 いつか

この未知の果てに告げ知らせて

——江口孝宏《Beside You》
## 题目描述

我相信所有读过这一段剧情的人都不想让别人也经历一样的痛苦，但是坦尼尔还是只能消失，对吗？

坦尼尔最后留下了一棵以 $1$ 为根的有根树，在树的每个结点上，都有一个记忆碎片。有的碎片表示着一个世界记忆的开始，而另外的碎片表示着一个世界记忆的终结。

这时，树上飞来了一只蝴蝶~~モリモリあつし~~。蝴蝶在树上飞舞的过程中，经过了一些结点。爱丽丝能确定蝴蝶经过的结点个数至少有 $2$ 个，但是她忘记了具体的点数。

爱丽丝发现，蝴蝶经过的所有点都是互相连通的。当她把目光朝向每一条经过点数大于 $1$ 的从连通块**深度最小的结点**通往**连通块的任意一个叶子结点**（一个点是连通块的叶子结点，当且仅当它在树上没有子结点，或者它在树上的任意子结点均不在该连通块内）的简单路径时，她发现这些路径上的记忆都是完整的。爱丽丝认为一条路径上的记忆是完整的，当且仅当这条路径上既没有出现一个世界的记忆**没开始就结束**（路径中途在没有未结束的记忆的时候，出现了表示记忆终结的碎片）的情况，也没有出现一个世界的记忆**开始之后没有终结**（路径结束之后还有没结束的记忆）的情况。

可惜她已经遗忘了蝴蝶经过了哪些点，所以你需要告诉她蝴蝶**最多**可能经过多少点。

**形式化题面**

给定一棵以 $1$ 为根的 $n$ 个节点的树 $T=(V,E)$，每个节点上的点权 $c_i$ 为一个**左括号或一个右括号**，节点编号为 $1\sim n$。

我们定义点集 $V'\subseteq V$ 合法，当且仅当 $|V'|>1$（**即 $V'$ 的大小大于 $1$**） 且 $\forall u,v \in V'$，从 $u$ 到 $v$ 的简单路径只经过 $V'$ 中的点。

同时我们定义 $E'\subseteq E$ 为能使得 $\forall u,v \in V'$，从 $u$ 到 $v$ 的简单路径，只经过 $E'$ 中的边的大小最小的边集。

定义一个合法点集 $V'$ 的根为 $V'$ 中深度最小的结点。

定义 $u$ 为合法点集 $V'$ 的叶子节点，当且仅当 $u$ 不是 $V'$ 的根，且满足 $v \in V', (u,v) \in E'$ 的 $v$ 的数量为 $1$。

求一个合法点集 $S$，**满足其根节点到其任意一个叶子的路径上，每个点的点权顺次相接为一个合法的括号序列**，并**最大化** $|S|$。

我们通过如下规则定义一个合法的括号序列：

- 空串（即长度为 $0$ 的串）是一个合法的括号序列。

- 若串 $\text{A,B}$ 都是合法的括号序列，则字符串 $\text{AB}$ （即将字符串 $\text{A}$ 与 $\text{B}$ 按顺序拼接起来）也是合法的括号序列。

- 若串 $\text{A}$ 是合法的括号序列，则字符串 $\text{(A)}$ 是一个合法的括号序列。

你需要输出符合要求的最大 $|S|$。
## 输入格式

第一行输入一个正整数 $n$ 表示树上结点个数。

第二行输入一个长度为 $n$ 的字符串 $c$。$c_i$ 为 ``(`` 表示这个结点上有一个标志着记忆开始的碎片，$c_i$ 为 ``)`` 表示这个结点上有一个标志着记忆终结的碎片。

接下来 $n-1$ 行，每行输入两个正整数 $u,v$，表示结点 $u,v$ 之间有一条边。
## 输出格式

输出一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3
())
1 2
1 3
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
8
()))())(
1 2
1 3
3 4
3 5
3 6
5 7
2 8
```
### 样例输出 #2
```
5
```
## 提示

**样例解释**

![](https://s1.ax1x.com/2023/08/07/pPEj56K.png)

蝴蝶经过的最大合法点集 $S$ 为 $\{1,2,3\}$。

![](https://s1.ax1x.com/2023/08/07/pPEv90g.png)

蝴蝶经过的最大合法点集 $S$ 为 $\{1,2,3,5,7\}$。

**数据范围**

**本题采用捆绑测试**。

| $\text{Subtask}$ | $n\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $20$ |  | $5$ |
| $2$ | $3000$ |  | $20$ |
| $3$ | $5\times10^5$ | $\text{A}$ | $15$  |
| $4$ | $5\times10^5$ | $\text{B}$ |  $10$ |
| $5$ | $2\times10^5$ |  | $15$ |
| $6$ | $5\times10^5$ |  | $35$ |

特殊性质 $\text{A}$：保证树退化成一条链（不保证 $1$ 号节点为其一个端点）。

特殊性质 $\text{B}$：保证原树上任意结点到叶子的路径上右括号数量不少于左括号数量。

对于 $100\%$ 的数据满足 $1\le n\le 5\times 10^5$，$1\le u,v \le n$，$c_i$ 为 ``(`` 或 ``)``。


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

