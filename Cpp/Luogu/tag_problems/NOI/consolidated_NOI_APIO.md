---
title: "[APIO2025] Hack!"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12541
tag: ['2025', 'APIO', '交互题', 'Special Judge', '构造', '大步小步算法 BSGS']
---
# [APIO2025] Hack!
## 题目描述

It has been an hour into a Codeforces contest, when you notice that another contestant in your room has solved a problem using an `unordered_set`. Time to hack!

You know that `unordered_set` uses a hash table with $n$ buckets, which are numbered from $0$ to $n-1$. Unfortunately, you do not know the value of $n$ and wish to recover it.

When you insert an integer $x$ into the hash table, it is inserted to the $(x \bmod n)$-th bucket. If there are $b$ elements in this bucket prior to the insertion, this will cause $b$ hash collisions to occur.

By giving $k$ distinct integers $x[0], x[1], \dots, x[k-1]$ to the interactor, you can find out the total number of hash collisions that had occurred while creating an `unordered_set` containing the numbers. However, feeding this interactor $k$ integers in one query will incur a cost of $k$.

For example, if $n = 5$, feeding the interactor with $x = [2, 15, 7, 27, 8, 30]$ would cause 4 collisions in total:

| Operation               | New collisions | Buckets                     |
|-------------------------|----------------|-----------------------------|
| initially               | $-$            | $[], [], [], [], []$        |
| insert $x[0] = 2$       | $0$            | $[], [], [2], [], []$       |
| insert $x[1] = 15$      | $0$            | $[15], [], [2], [], []$     |
| insert $x[2] = 7$       | $1$            | $[15], [], [2, 7], [], []$  |
| insert $x[3] = 27$      | $2$            | $[15], [], [2, 7, 27], [], []$ |
| insert $x[4] = 8$       | $0$            | $[15], [], [2, 7, 27], [8], []$ |
| insert $x[5] = 30$      | $1$            | $[15, 30], [], [2, 7, 27], [8], []$ |

Note that the interactor creates the hash table by inserting the elements in order into an initially empty `unordered_set`, and a new empty `unordered_set` will be created for each query. In other words, all queries are independent.

Your task is to find the number of buckets $n$ using a total cost of at most $1\,000\,000$.

### Implementation details

You should implement the following procedure:

```cpp
int hack()
```

- This procedure should return an integer – the hidden value of $n$.
- For each test case, the grader may call this function more than once. Each call should be processed as a separately new scenario.

Within this procedure, you may call the following procedure:

```cpp
long long collisions(std::vector<long long> x)
```

- $x$: an array of distinct numbers, where $1 \leq x[i] \leq 10^{18}$ for each $i$.
- This function returns the number of collisions created by inserting the elements of $x$ to an `unordered_set`.
- This procedure can be called multiple times. The sum of length of $x$ over all calls within one call to `hack()` must not exceed $1\,000\,000$.

**Note**: Since the procedure `hack()` will be called more than once, contestants need to pay attention to the impact of the remaining data of the previous call on the current call, especially the state stored in global variables.

The cost limit of $1\,000\,000$ applies to each test case. In general, if there are $t$ calls to `hack()`, you may use a total cost of no more than $t \times 1\,000\,000$, with each individual call to `hack()` using a cost no more than $1\,000\,000$.

The interactor is not adaptive, i.e. the values of $n$ are fixed before the start of interaction.
## 提示

### Example

Suppose, there are 2 multitests. The grader will make a following call:

```cpp
hack()
```

Let's say, within the function, you make following calls:

| Call                          | Returned value |
|-------------------------------|----------------|
| `collisions([2, 15, 7, 27, 8, 30])` | $4$            |
| `collisions([1, 2, 3])`             | $0$            |
| `collisions([10, 20, 30, 40, 50])` | $10$           |

After that, if you find that the value of $n$ is $5$, the procedure `hack()` should return $5$.

Then grader will make another call:

```cpp
hack()
```

Let's say, within the function, you make following calls:

| Call              | Returned value |
|-------------------|----------------|
| `collisions([1, 3])` | $1$            |
| `collisions([2, 4])` | $1$            |

The only $n$ which satisfies the queries is $2$. So, the procedure `hack()` should return $2$.

### Constraints

- $1 \leq t \leq 10$, where $t$ is the number of multitests.
- $2 \leq n \leq 10^9$
- $1 \leq x[i] \leq 10^{18}$ for each call to `collisions()`.

### Subtasks

1. (8 points) $n \leq 500\,000$
2. (17 points) $n \leq 1\,000\,000$
3. (75 points) No additional constraints.

In the last subtask, you can get partial score. Let $q$ be the maximum total cost among all invocations of `hack()` over every test case of the subtask. Your score for this subtask is calculated according to the following table:

| Condition                      | Points |
|--------------------------------|--------|
| $1\,000\,000 < q$              | $0$    |
| $110\,000 < q \leq 1\,000\,000$ | $75 \cdot \log_{50} \left( \frac{10^6}{q - 90000} \right)$ |
| $q \leq 110\,000$              | $75$   |

If, in any of the test cases, the calls to the procedure `collisions()` do not conform to the constraints described in Implementation Details, or the number returned by `hack()` is incorrect, the score of your solution for that subtask will be $0$.

### Sample Grader

The sample grader reads the input in the following format:

- line 1: $t$

Then, $t$ lines follow, each containing a value of $n$:

- line 1: $n$

For each test case, let $m$ be the return value of `hack()`, and $c$ be the total cost of all queries. The sample grader prints your answer in the following format:

- line 1: $m \, c$


---

---
title: "[APIO2025] Permutation Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12542
tag: ['博弈论', '2025', 'APIO', '交互题', 'Special Judge', 'Ad-hoc', '分类讨论']
---
# [APIO2025] Permutation Game
## 题目描述

Alice and Bob are childhood friends, and they love playing intellectual games. Today, they are playing a new game on graphs.

The game set contains a **connected** graph with $m$ vertices, numbered from $0$ to $m-1$, and $e$ edges, numbered from $0$ to $e-1$. The $i$-th edge connects vertices $u[i]$ and $v[i]$.

The game set also contains a permutation $p[0], p[1], \ldots, p[n-1]$ of length $n$, where $m \leq n$. Permutation is an array in which each number from $0$ to $n-1$ appears exactly once, in some order. The **score** of permutation $p$ is the number of indices $i$ such that $p[i] = i$.

The game will last for at most $10^{100}$ turns. In each turn, the following happens:

1. If Alice decides to end the game, the game stops.
2. Otherwise, Alice chooses **distinct indices** $t[0], t[1], \ldots, t[m-1]$, where $0 \leq t[i] < n$. Note that, the game does **not** require $t[0] < t[1] < \ldots < t[m-1]$.
3. Bob chooses an index $0 \leq j < e$ of the edges of the graph and swaps $p[t[u[j]]]$ and $p[t[v[j]]]$.

Alice wishes to maximize the final score of the permutation while Bob wishes to minimize the final score of the permutation.

Your task is to help Alice and play against Bob, whose moves are simulated by grader.

Let's define *optimal score* as the final score of the permutation if both Alice and Bob play optimally.

You will need to determine the optimal score of the permutation and then play the game with Bob to achieve **at least** that optimal score after some turns.

**Note that Alice's strategy should work no matter what moves Bob makes, including if Bob makes unoptimal moves.**

### Implementation details

You should implement the following procedure:

```cpp
int Alice(int m, int e, std::vector<int> u, std::vector<int> v,
    int n, std::vector<int> p)
```

- `m`: the number of vertices in the graph.
- `e`: the number of edges in the graph.
- `u` and `v`: arrays of length `e` describing the edges of the graph.
- `n`: the length of the permutation.
- `p`: an array of length `n` describing the permutation.

This procedure is called exactly once.
This procedure should return an integer – the optimal score of the game.
Within this procedure, you may call the following procedure:

```cpp
int Bob(std::vector<int> t)
```

- `t`: an array of size `m`, containing distinct indices, where $0 \leq t[i] < n$ and $t[i] \neq t[j]$ for any $i \neq j$.
This function returns a single integer `j` which satisfies $0 \leq j < e$.
This procedure can be called multiple times.

## 提示

### Example

Consider the following call:

```cpp
Alice(5, 6, [4, 0, 3, 1, 4, 2], [2, 2, 0, 2, 0, 3], 
10, [8, 2, 7, 6, 1, 5, 0, 9, 3, 4])
```

The graph is as follows:

![](https://cdn.luogu.com.cn/upload/image_hosting/lo1c6nt9.png)

and `p` is initially `[8, 2, 7, 6, 1, 5, 0, 9, 3, 4]`.
Given the constraints above, we can prove that the optimal score of the permutation is `1`.

Suppose, Alice makes the following 4 moves:

| Argument of `t` to Bob | Return value of Bob | Corresponding indices of `p` | `p` after the swap by Bob |
|------------------------|---------------------|-----------------------------|---------------------------|
| `[3, 1, 5, 2, 0]`      | `5`                 | `5, 2`                      | `[8, 2, 5, 6, 1, 7, 0, 9, 3, 4]` |
| `[9, 3, 7, 2, 1]`      | `0`                 | `1, 7`                      | `[8, 9, 5, 6, 1, 7, 0, 2, 3, 4]` |
| `[5, 6, 7, 8, 9]`      | `1`                 | `5, 7`                      | `[8, 9, 5, 6, 1, 2, 0, 7, 3, 4]` |
| `[7, 5, 2, 3, 6]`      | `3`                 | `5, 2`                      | `[8, 9, 2, 6, 1, 5, 0, 7, 3, 4]` |

Note that Alice and Bob not necessarily making the optimal moves. These moves are shown purely for demonstration purposes. Also note that Alice could finish the game immediately, as the initial score of the permutation is already `1`.

After Alice has performed all the moves above, the actual score of the permutation is `3` ($p[2] = 2$, $p[5] = 5$, $p[7] = 7$). Finally, the function `Alice()` will return `1` – the optimal score of the permutation.

**Note that even though Alice has achieved a score of 3 by playing with Bob, you would get 0 points if the return value of `Alice()` was 3 instead of 1.**

### Constraints

- $2 \leq m \leq 400$
- $m - 1 \leq e \leq 400$
- $0 \leq u[i], v[i] < m$
- $m \leq n \leq 400$
- $0 \leq p[i] < n$
- The graph is connected, contains no self-loops or multiple edges.
- $p$ is a permutation, i.e. $p[i] \neq p[j]$ for any $i \neq j$.

### Subtasks

1. (6 points) $m = 2$
2. (6 points) $e > m$
3. (10 points) $e = m - 1$
4. (24 points) $e = m = 3$
5. (24 points) $e = m = 4$
6. (30 points) $e = m$

For each subtask, you can get partial score. Let $r$ be the maximum ratio of $\frac{k}{n}$ among all test cases of a subtask, where $k$ is the number of turns (i.e. calls to `Bob()`). Then, your score for that subtask is multiplied by the following number:

| Condition       | Multiplier                     |
|-----------------|--------------------------------|
| $12 \leq r$     | $0$                            |
| $3 < r < 12$    | $1 - \log_{10}(r - 2)$         |
| $r \leq 3$      | $1$                            |

In particular, if you solve the problem within $3n$ turns, you get full points for that subtask. Using more than $12n$ turns results in getting 0 for that subtask (shown as `Output isn't correct`).

### Sample Grader

The sample grader reads the input in the following format:

- line 1: $m$ $e$
- line 2 + $i$ ($0 \leq i \leq e - 1$): $u[i]$ $v[i]$
- line 2 + $e$: $n$
- line 3 + $e$: $p[0]$ $p[1]$ $\ldots$ $p[n - 1]$

The sample grader prints the output in the following format:

- line 1: final permutation $p$
- line 2: return value of `Alice()`
- line 3: actual score of final permutation
- line 4: the number of turns



---

---
title: "[APIO2012] 苦无"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3635
tag: ['2012', 'APIO']
---
# [APIO2012] 苦无
## 题目描述

苦无(Kunai)是一种忍者使用的形状像刀的武器，忍者通过投掷苦无攻击对 手。 现在有 $N$ 名忍者聚集在一块 $H$ 行 $W$ 列的棋盘式的广场上。每个忍者都站在 其所在方块的中心处，任何两个忍者都不在同一个方块上。每个忍者都拿着一个 苦无，面朝上、下、左、右四个方向中的一个方向站着。在时刻 $0$，所有忍者同 时向其所朝向的方向投掷苦无。

每个苦无将会一直保持其初始的方向，并以单位速度飞行。如果某个时刻一 个位置上多于一个的苦无，它们将会相撞并且消失。苦无特别小，可以看成质点。 同时，由于忍者的移动速度特别快，他们不会被苦无击中。

在下面的例子中，我们用箭头来表示苦无，而箭头的方向即为苦无的方向。 在这些图中，所有的苦无都会相撞后消失。

  ![](https://cdn.luogu.com.cn/upload/pic/4414.png) 

在下面的图中，两个粗线箭头表示的苦无不会相撞。其中在第二个和第三个 图中，其中一个粗线表示的苦无会与细线表示的苦无相撞后消失，因此不会撞上 另一个粗线表示的苦无。

  ![](https://cdn.luogu.com.cn/upload/pic/4415.png) 

你的任务是计算经过足够长的时间之后，在这个 $W × H$ 的广场中有多少格 子被苦无经过。

## 输入格式

第一行包含两个被空格隔开的整数 $W$, $H$，表示广场的尺寸为 $W$ 列 $H$ 行。 第二行包含一个整数 $N$，表示忍者的数量。

接下来 $N$ 行中，第 $i$ 行有三个以空格分隔的整数 $X_i, Y_i, D_i$, 表示第 $i$ 个忍者 处在从左往右的 $X_i$ 列、从上往下的第 $Y_i$ 行，任何两个忍者不在同一个位置。第 $i$ 个忍者面向的方向由 $D_i$ 表示，分别为： 

- $D_i = 0$，表示忍者向右；
- $D_i = 1$，表示忍者向上； 
- $D_i = 2$，表示忍者向左； 
- $D_i = 3$，表示忍者向下。

## 输出格式

输出一个整数，表示经过足够长的时间之后，在这个 $W × H$ 的广场中被苦 无经过被苦无经过的格子数量。

## 样例

### 样例输入 #1
```
5 4 
5 
3 3 2 
3 2 0 
4 2 2 
5 4 1 
1 1 3 
```
### 样例输出 #1
```
11
```
## 提示

对于全部数据，忍者数 $1 ≤ N ≤ 10^5$，列数 $1 ≤ W ≤ 10^9$，行数 $1 ≤ H ≤ 10^9$；
坐标范围 $1 ≤ X_i ≤ W$，$1 ≤ Y_i ≤ H$。

 
- 在 $10\%$ 的数据中，$N ≤ 1000$, $W ≤ 1000$, $H ≤ 1000$。
- 在 $40\%$ 的数据中，$N ≤ 1000$。



---

---
title: "[APIO2016] 烟火表演"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3642
tag: ['2016', 'APIO', '可并堆', '可持久化', '凸包']
---
# [APIO2016] 烟火表演
## 题目描述

烟花表演是最引人注目的节日活动之一。在表演中,所有的烟花必须同时爆炸。为了确保安全，烟花被安置在远离开关的位置上，通过一些导火索与开关相连。导火索的连接方式形成一棵树，烟花是树叶，如图所示。火花从开关出发，沿导火索移动。每当火花抵达一个分叉点时，它会扩散到与之相连的所有导火索，继续燃烧。导火索燃烧的速度是一个固定常数。图中展示了六枚烟花 $\{E_1, E_2, \dots, E_6\}$ 的连线布局，以及每根导火索的长度。图中还标注了当在时刻 $0$ 从开关点燃火花时，每一发烟花的爆炸时间。


 ![](https://cdn.luogu.com.cn/upload/pic/4429.png) 

Hyunmin 为烟花表演设计了导火索的连线布局。不幸的是，在他设计的布局中，烟花不一定同时爆炸。我们希望修改一些导火索的长度，让所有烟花在同一时刻爆炸。例如，为了让图中的所有烟花在时刻 $13$ 爆炸，我们可以像下图中左边那样调整导火索长度。类似地，为了让图中的所有烟花在时刻 $14$ 爆炸，我们可以像下图中右边那样调整长度。

 ![](https://cdn.luogu.com.cn/upload/pic/4430.png) 

修改导火索长度的代价等于修改前后长度之差的绝对值。例如，将上面那副图中布局修改为下面那副图的左边布局的总代价为 $6$，而修改为右边布局的总代价为 $5$。

导火索的长度可以被减为 $0$，同时保持连通性不变。

给定一个导火索的连线布局，你需要编写一个程序，去调整导火索长度，让所有的烟花在同一时刻爆炸，并使得代价最小。

## 输入格式

所有的输入均为正整数。令 $N$ 代表分叉点的数量，$M$ 代表烟花的数量。分叉点从 $1$ 到 $N$ 编号，编号为 $1$ 的分叉点是开关。烟花从 $N + 1$ 到 $N + M$ 编号。

输入第一行为 $N, M$。后面 $N + M - 1$ 行，第 $i$ 行两个整数 $P_{i + 1}, C_{i + 1}$。其中 $P_i$ 满足 $1 \leq P_i < i$，代表和分叉点或烟花 $i$ 相连的分叉点。$C_i$ 代表连接它们的导火索长度（$1 \leq C_i \leq 10^9$）除开关外，每个分叉点和多于 $1$ 条导火索相连，而每发烟花恰好与 $1$ 条导火索相连。

## 输出格式

输出调整导火索长度，让所有烟花同时爆炸，所需要的最小代价。

## 样例

### 样例输入 #1
```
4 6
1 5
2 5
2 8
3 3
3 2
3 3
2 9
4 4
4 3
```
### 样例输出 #1
```
5
```
## 提示

【数据规模】

子任务 1（7 分）：$N = 1$，$1 \leq M \leq 100$。

子任务 2（19 分）：$1 \leq N+M \leq 300$，且开关到任一烟花的距离不超过 $300$。

子任务 3（29 分）：$1 \leq N+M \leq 5000$。

子任务 4（45 分）：$1 \leq N+M \leq 300000$。



---

---
title: "[APIO2017] 斑斓之地"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3776
tag: ['2017', 'APIO']
---
# [APIO2017] 斑斓之地
## 题目背景

本题原为交互题，这里采用传统题形式进行评测。
## 题目描述

在很久以前的黄金时代，澳大利亚的土地是矩形的，它可以被划分成 $R$ 行 $C$ 列的网格状，行的编号从北到南依次为 $1$ 到 $R$ ，列的编号从西到东依次为 $1$ 到 $C$，$(r,c)$ 表示第 $r$ 行第 $c$ 列的土地。一天，伟大的彩虹蛇从 $(s_r,s_c)$ 出发在澳大利亚的土地上移动，彩虹蛇连续进行了 $M$ 次移动，每次它会向正北 (`N`)、正南 (`S`)、正东 (`E`) 或正西 (`W`) 方向移动一格，其经过的所有的格子（包括起点和终点）都会变成河流。保证在任一时刻，彩虹蛇都不会离开这片 $R$ 行 $C$ 列的矩形土地。

数百万年之后，你想购买一块矩形区域纪念伟大的彩虹蛇。你想给所购买矩形区域内每一块不是河流的格子都染上颜色，要求相邻的格子颜色必须相同，两个格子相邻当且仅当两个格子有一条公共边，你所购买区域之外的格子无须染色。

现在给出彩虹蛇 $M$ 次移动的方向，你有 $Q$ 个购买矩形区域的方案，问每个方案最多能够将土地染上多少种不同的颜色。
## 输入格式

第一行：四个整数 $R$，$C$，$M$ 和 $Q$；

第二行：两个整数 $s_r$ 和 $s_c$；

第三行: 一个包含 $M$ 个字符的字符串 $S$，每个字符是 `N`、`S`、`E`、`W` 之一（如果 $M=0$ 则此行留空）；

第四到 $Q+3$ 行: 每行四个整数 $a_r,a_c,b_r$ 和 $b_c$，表示你购买的土地范围，左上角是 $(a_r,a_c)$，右下角是 $(b_r,b_c)$。
## 输出格式

对于每个询问做出回答，输出最多能够将土地染上多少种不同的颜色。
## 样例

### 样例输入 #1
```
6 4 9 4
3 3
NWESSWEWS
2 3 2 3
3 2 4 4
5 3 6 4
1 2 5 3
```
### 样例输出 #1
```
0
2
1
3
```
## 提示

### 样例解释

样例对应下图，其中蓝色代表河流。

![](https://cdn.luogu.com.cn/upload/image_hosting/1mhty5m8.png)

### 数据范围

对于所有测试数据，$0\le M\le 10^5$，并且 $R,C,Q\ge 1$，对于每个购买矩形土地的方案，都有 $1 \le a_r \le b_r \le R, 1 \le a_c \le b_c \le C$。

详细子任务分值及附加条件如下表。

|子任务编号|分值|$R$|$C$|$Q$|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$11$|$R\le 50$|$C\le 50$|$Q\le 1000$|
|$2$|$12$|$R=2$|$C\le 2\times 10^5$|$Q\le 10^5$|
|$3$|$24$|$R\le 2\times 10^5$|$C\le 2\times 10^5$|$Q=1$|
|$4$|$27$|$R\le 1000$|$C\le 1000$|$Q\le 10^5$|
|$5$|$26$|$R\le 2\times 10^5$|$C\le 2\times 10^5$|$Q\le 10^5$|



---

---
title: "[APIO2018] 选圆圈"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4631
tag: ['搜索', '2018', 'APIO', '剪枝']
---
# [APIO2018] 选圆圈
## 题目描述

在平面上，有 $n$ 个圆，记为 $c_1, c_2,...,c_n$ 。我们尝试对这些圆运行这个算法：

1. 找到这些圆中半径最大的。如果有多个半径最大的圆，选择编号最小的。记为 $c_i$。
2. 删除 $c_i$ 及与其有交集的所有圆。两个圆有交集当且仅当平面上存在一个点，这个点同时在这两个圆的圆周上或圆内。（原文直译：如果平面上存在一个点被这两个圆所包含，我们称这两个圆有交集。一个点被一个圆包含，当且仅当它位于圆内或圆周上。）
3. 重复上面两个步骤直到所有的圆都被删除。

![QQ20180525194902.png](https://cdn.luogu.com.cn/upload/pic/19974.png)

当 $c_i$ 被删除时，若循环中第 $1$ 步选择的圆是 $c_j$，我们说 $c_i$ 被 $c_j$ 删除。对于每个圆，求出它是被哪一个圆删除的。
## 输入格式

第一行包含一个整数 $n$，表示开始时平面上圆的数量。

接下来 $n$ 行，每行包含三个整数 $x_i, y_i, r_i$ 依次描述圆 $c_i$ 圆心的 $x$ 坐标、$y$ 坐标和它的半径。
## 输出格式

输出一行，包含 $n$ 个整数 $a_1, a_2, ..., a_n$，其中 $a_i$ 表示圆 $c_i$ 是被圆 $c_{a_i}$ 删除的。
## 样例

### 样例输入 #1
```
11
9 9 2
13 2 1
11 8 2
3 3 2
3 12 1
12 14 1
9 8 5
2 8 2
5 2 1
14 4 2
14 14 1

```
### 样例输出 #1
```
7 2 7 4 5 6 7 7 4 7 6
```
## 提示

**提示**

题目描述中的图片对应了样例一中的情形。

**子任务（注：这里给出的子任务与本题在这里的最终评测无关，仅供参考）**

- Subtask 1(points: $7$): $n \leq 5000$
- Subtask 2(points: $12$): $n \leq 3 × 10^5$，对于所有的圆 $y_i = 0$
- Subtask 3(points: $15$): $n \leq 3 × 10^5$，每个圆最多和一个其他圆有交集
- Subtask 4(points: $23$): $n \leq 3 × 10^5$，所有的圆半径相同
- Subtask 5(points: $30$): $n \leq 10^5$
- Subtask 6(points: $13$): $n \leq 3 × 10^5$

所有数据均满足：$-10^9 ≤ x_i, y_i ≤ 10^9, 1 ≤ r_i ≤ 10^9$。


---

---
title: "[APIO2018] 新家"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4632
tag: ['2018', '线段树', '二分', '离散化', 'APIO']
---
# [APIO2018] 新家
## 题目背景

**警告！滥用本题者封号！请勿多次重复提交！**
## 题目描述

五福街是一条笔直的道路，这条道路可以看成一个数轴，街上每个建筑物的坐标都可以用一个整数来表示。小明是一位时光旅行者，他知道在这条街上，在过去现在和未来共有 $n$个商店出现。第 $i$个商店可以使用四个整数 $x_i, t_i, a_i, b_i$描述，它们分别表示：商店的坐标、商店的类型、商店开业的年份、商店关闭的年份。

小明希望通过时光旅行，选择一个合适的时间，住在五福街上的某个地方。他给出了一份他可能选择的列表，上面包括了 $q$个询问，每个询问用二元组 （坐标，时间）表示。第 $i$对二元组用两个整数 $l_i, y_i$描述，分别表示选择的地点 $l_i$和年份 $y_i$。

现在，他想计算出在这些时间和地点居住的生活质量。他定义居住的不方便指数为：在居住的年份，离居住点最远的商店类型到居住点的距离。类型 $t$的商店到居住点的距离定义为：在指定的年份，类型 $t$的所有营业的商店中，到居住点距离最近的一家到居住点的距离。我们说编号为 $i$的商店在第 $y$年在营业当且仅当 $a_i ≤ y ≤ b_i$ 。注意，在某些年份中，可能在五福街上并非所有 $k$种类型的商店都有至少一家在营业。在这种情况下，不方便指数定义为 $-1$。

你的任务是帮助小明求出每对（坐标，时间）二元组居住的不方便指数。
## 输入格式

第一行包含三个整数 $n, k$和 $q$ ，分别表示商店的数量、商店类型的数量和（坐标，时间）二元组的数量。$(1 \leq n, q \leq 3×10^5, 1 ≤ k ≤ n)$。

接下来 $n$行，每行包含四个整数 $x_i, t_i, a_i$ 和 $b_i$用于描述一家商店，意义如题面所述$(1 ≤ x_i, a_i, b_i ≤ 10^8, 1 ≤ t_i ≤ k, a_i ≤ b_i)$。

接下来 $q$行，每行包含两个整数 $l_i$和 $y_i$ ，表示一组（坐标，时间）查询$(1 ≤ l_i, y_i ≤ 10^8)$。
## 输出格式

输出一行，包含 $q$个整数，依次表示对于 $q$组（坐标，时间）询问求出的结果。
## 样例

### 样例输入 #1
```
4 2 4
3 1 1 10
9 2 2 4
7 2 5 7
4 1 8 10
5 3
5 6
5 9
1 10

```
### 样例输出 #1
```
4
2
-1
-1

```
### 样例输入 #2
```
2 1 3
1 1 1 4
1 1 2 6
1 3
1 5
1 7
```
### 样例输出 #2
```
0
0
-1

```
### 样例输入 #3
```
1 1 1
100000000 1 1 1
1 1

```
### 样例输出 #3
```
99999999

```
## 提示

**提示**

在第一个样例中，有 4 家商店，共 2 种类型，还有 4 个询问。

- 对于第一个询问：小明在第 3 年住在坐标为 5 的地方。这一年中，编号为 1 和 2 的商店在营业，到编号为 1 的商店的距离为 2 ，到编号为 2 的商店距离为 4 ，所以最大距离为$4$。
- 对于第二个询问：小明在第 6 年住在坐标为 5 的地方。这一年中，编号为 1 和 3 的商店在营业，到编号为 1 的商店的距离为 2 ，到编号为 3 的商店距离为 2 ，所以最大距离为$2$。
- 对于第三个询问：小明在第 9 年住在坐标为 5 的地方。这一年中，编号为 1 和 4 的商店在营业，它们的类型都为 1，没有类型为 2 的商店在营业，所以答案为 $-1$。
- 同样的情况出现在第四个询问中。

在第二个样例中，有 2 家商店，共 1 种类型，还有三个询问。 两家商店的类型都是 1 。在所有的询问中，小明均住在坐标为 1 的地方。 在前两个询问中，至少有一个商店在营业，所以答案为 $0$ ，在第三个询问中，两个商店都不在营业，所以答案为 $-1$ 。

在第三个样例中，有 1 家商店和 1 个询问，两者之间的距离是 $99999999$ 。


**子任务（注：这里给出的子任务与本题在这里的最终评测无关，仅供参考）**

- Subtask 1(points: $5$): $n, q \leq 400$
- Subtask 2(points: $7$): $n, q \leq 6 × 10^4, k \leq 400$
- Subtask 3(points: $10$): $n, q \leq 3 × 10^5$，对于所有的商店 $a_i = 1, b_i = 10^8$
- Subtask 4(points: $23$): $n, q \leq 3 × 10^5$，对于所有的商店 $a_i = 1$
- Subtask 5(points: $35$): $n, q \leq 6 × 10^4$
- Subtask 6(points: $20$): $n, q \leq 3 × 10^5$



---

---
title: "[APIO2021] 六边形领域"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7598
tag: ['2021', 'APIO', '交互题', 'Special Judge', 'O2优化']
---
# [APIO2021] 六边形领域
## 题目背景

本题只支持 C++ 提交，提交时不需要包含 `hexagon.h` 头文件，只需要将附件中的 `hexagon.h` 中的内容粘贴到代码的开头即可。
## 题目描述

对于一个用六边形无限平铺的平面，Pak Dengklek 站在其中一个格子上，并称该格子为初始格子。如果六边形平铺中的两个格子有公共边，则称它们是相邻的格子。对于一步移动，Pak Dengklek 可以从一个格子向六个可能的方向（从 $1$ 到 $6$ 编号，如下图所示）移动到与其相邻的格子上。

![](https://cdn.luogu.com.cn/upload/image_hosting/cojdvvvr.png)

对于某个由 $N$ 次行动构成的行动序列，Pak Dengklek 可以用其产生的路径（对应一个按序访问的格子序
列）构造一个领域。其中第 $i$ 次行动由移动方向 $D[i]$ 和在该方向上的移动步数 $L[i]$ 组成，并且该路径应有如下性质：

- 路径是 _封闭_ 的，这意味着在格子序列中，起点格子与终点格子（即初始格子）相同。
- 路径是 _简单_ 的，这意味着在格子序列中，除了初始格子访问过恰好两次（起点和终点分别访问一
次），其他格子只能被访问至多一次。
- 路径是 _暴露_ 的，这意味着在格子序列中，每个格子与至少一个不在序列中出现过的非 _内部格子_ 相邻。
    - 如果一个格子不在格子序列中出现过，并且从它出发，在不经过格子序列中任何格子的情况下，（通过若干步移动） 只能访问到有限个格子，我们就称该格子是 _内部格子_ 。

下图是一个符合上述条件的路径例子。其中：

- $1$ 号格子（粉色）是初始格子。
- 被编号的格子（淡蓝色）组成格子序列，编号代表它被访问的顺序。
- 被标上叉号的格子（深蓝色）是 _内部格子_。

![](https://cdn.luogu.com.cn/upload/image_hosting/znccjlim.png)

构造出的领域只包含所有路径上的格子和内部格子。领域中格子 $c$ 的距离定义为：在只经过领域中包含格子的情况下，从初始格子出发到达 $c$ 所需要的最少移动步数。领域中一个格子的分数定义为 $A+d \times B$，其中 $A$ 和 $B$ 是 Pak Dengklek 给定的常数，$d$ 是该格子在领域中的距离。下图给出了用上示路径构成的领域中每个格子的距离。

![](https://cdn.luogu.com.cn/upload/image_hosting/u9gjh0n6.png)

请帮助 Pak Dengklek 计算，用给出的行动序列构成的领域中，所有格子的分数之和。由于总分数值可能很大，最终结果对 ${10}^9+7$ 取模。

你需要实现下列函数：

`int draw_territory(int N, int A, int B, int[] D, int[] L)`

- $N$：行动序列中行动的次数。
- $A,B$：分数计算中的常数。
- $D$：大小为 $N$ 的数组，其中 $D[i]$ 表示第 $i$ 次行动的方向。
- $L$：大小为 $N$ 的数组，其中 $L[i]$ 表示第 $i$ 次行动的移动步数。
- 函数应该返回用给出的行动序列所构成的领域中，所有格子的分数总和对 ${10}^9+7$ 取模后的值。
- 该函数将被调用恰好一次。
## 输入格式

示例测试程序按如下格式读取输入数据：

- 第 $1$ 行：$N$ $A$ $B$
- 第 $2+i$（$0 \le i \le N-1$）行：$D[i]$ $L[i]$
## 输出格式

示例测试程序按如下格式输出你的答案：

- 第 $1$ 行：`draw_territory` 的返回值。
## 样例

### 样例输入 #1
```
17 2 3
1 2 3 4 5 4 3 2 1 6 2 3 4 5 6 6 1
1 2 2 1 1 1 1 2 3 2 3 1 6 3 3 2 1
```
### 样例输出 #1
```
1003
```
## 提示

**【样例解释】**

考虑下列调用：

```plain
draw_territory(17, 2, 3,
			   [1, 2, 3, 4, 5, 4, 3, 2, 1, 6, 2, 3, 4, 5, 6, 6, 1],
			   [1, 2, 2, 1, 1, 1, 1, 2, 3, 2, 3, 1, 6, 3, 3, 2, 1])
```

该行动序列和上述题面中给出的例子相同。下表列出了该领域中所有可能的距离值所对应的分数。

| 距离值 | 格子数 | 每个格子分数 | 总分数 |
|:-:|:-:|:-:|:-:|
|$0$|$1$|$2+0 \times 3=2$|$1 \times 2=2$|
|$1$|$4$|$2+1 \times 3=5$|$4 \times 5=20$|
|$2$|$5$|$2+2 \times 3=8$|$5 \times 8=40$|
|$3$|$6$|$2+3 \times 3=11$|$6 \times 11=66$|
|$4$|$4$|$2+4 \times 3=14$|$4 \times 14=56$|
|$5$|$3$|$2+5 \times 3=17$|$3 \times 17=51$|
|$6$|$4$|$2+6 \times 3=20$|$4 \times 20=80$|
|$7$|$4$|$2+7 \times 3=23$|$4 \times 23=92$|
|$8$|$5$|$2+8 \times 3=26$|$5 \times 26=130$|
|$9$|$3$|$2+9 \times 3=29$|$3 \times 29=87$|
|$10$|$4$|$2+10 \times 3=32$|$4 \times 32=128$|
|$11$|$5$|$2+11 \times 3=35$|$5 \times 35=175$|
|$12$|$2$|$2+12 \times 3=38$|$2 \times 38=76$|

总分数值为 $2+20+40+66+56+51+80+92+130+87+128+175+76=1003$。

因此，`draw_territory` 应该返回 $1003$。

**【数据范围】**

- $3 \le N \le 2\times {10}^5$。
- $0 \le A,B \le {10}^9$。
- $1 \le D[i] \le 6$（$0 \le i \le N-1$）。
- $1 \le L[i]$（$0 \le i \le N-1$）。
- $L$ 中的元素之和不超过 ${10}^9$。
- 给出的行动序列所对应的路径一定是 _封闭_、_简单_ 和 _暴露_ 的。

**【子任务】**

1. （3 分）：$N=3$，$B=0$。
2. （6 分）：$N=3$。
3. （11 分）：$L$ 中的元素之和不超过 $2000$。
4. （12 分）：$B=0$，$L$ 中的元素之和不超过 $2\times {10}^5$。
5. （15 分）：$B=0$。
6. （19 分）：$L$ 中的元素之和不超过 $2\times {10}^5$。
7. （18 分）：$L[i]=L[i+1]$（$0 \le i \le N-2$）。
8. （16 分）：无附加限制。


---

---
title: "[APIO2021] 雨林跳跃"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7599
tag: ['2021', 'APIO', '交互题', 'Special Judge', 'O2优化']
---
# [APIO2021] 雨林跳跃
## 题目背景

本题只支持 C++ 提交，不支持 C++14 (GCC 9)，提交时不需要包含 jumps.h 头文件，只需要将附件中的 jumps.h 中的内容粘贴到代码的开头即可。

由于洛谷的测试点限制，本题只能评测其中的 100 组数据。
## 题目描述

在苏门答腊岛的热带雨林中，有 $N$ 棵树排成一排，从左到右依次用 $0$ 到 $N-1$ 进行编号，其中 $i$ 号树的高度为 $H[i]$，且所有树的高度**互不相同**。

Pak Dengklek 正在训练一只猩猩，让她能够从一棵树上跳到另一棵树上。对于一次跳跃，猩猩可以从一棵树，向左或向右跳到比当前这棵树高的第一棵树上。形式化地，如果猩猩当前在 $x$ 号树，那么当且仅当满足下列条件之一时，她能够跳到 $y$ 号树上：

- $y$ 是满足 $H[z]>H[x]$ 的所有 $z$ 中比 $x$ 小的最大非负整数；或者：
- $y$ 是满足 $H[z]>H[x]$ 的所有 $z$ 中比 $x$ 大的最小非负整数。

Pak Dengklek 有 $Q$ 个跳跃计划，每个计划用四个整数 $A$，$B$，$C$ 和 $D$（$A \le B<C \le D$）来描述。对于每个计划，Pak Dengklek 想知道猩猩是否能够从某棵树 $s$（$A \le s \le B$）出发，经过若干次跳跃，到达某棵树 $e$（$C \le e \le D$）。若该计划可行，Pak Dengklek 还想知道可行方案中猩猩需要的最少跳跃次数。

你需要实现下列函数：

`void init(int N, int[] H)`

- $N$：树的数量。
- $H$：大小为 $N$ 的数组，$H[i]$ 表示 $i$ 号树的高度。
- 该函数在第一次 `minimum_jumps` 的调用前，将会被调用恰好一次。

`int minimum_jumps(int A, int B, int C, int D)`

- $A,B$：可以用作起点的树的编号范围。
- $C,D$：可以用作终点的树的编号范围。
- 该函数需要返回可行方案中猩猩需要的最少跳跃次数，或者返回 $-1$ 表示该计划不可行。
- 该函数将被调用恰好 $Q$ 次。
## 输入格式

示例测试程序按如下格式读取输入数据：

- 第 $1$ 行：$N$ $Q$
- 第 $2$ 行：$H[0]$ $H[1]$ $\cdots$ $H[N-1]$
- 第 $3+i$（$0 \le i \le Q-1$）行：$A$ $B$ $C$ $D$，表示第 $i$ 次 `minimum_jumps` 调用的参数。
## 输出格式

示例测试程序按如下格式输出你的答案：

- 第 $1+i$（$0 \le i \le Q-1$）行：第 $i$ 次 `minimum_jumps` 调用的返回值。
## 样例

### 样例输入 #1
```
7 3
3 2 1 6 4 5 7
4 4 6 6
1 3 5 6
0 1 2 2

```
### 样例输出 #1
```
2
1
-1

```
## 提示

**【样例解释】**

考虑如下调用： 

`init(7, [3, 2, 1, 6, 4, 5, 7])`

在初始化完成后，考虑如下调用：

`minimum_jumps(4, 4, 6, 6)`

该计划意味着猩猩必须从 $4$ 号树（高度为 $4$）出发，并到达 $6$ 号树（高度为 $7$）。

一种跳跃次数最少的可行方案为：先跳到 $3$ 号树（高度为 $6$），再跳到 $6$ 号树。

另一种方案为：先跳到 $5$ 号树（高度为 $5$），再跳到 $6$ 号树。

因此，`minimum_jumps` 应该返回 $2$。

考虑另一个调用：

`minimum_jumps(1, 3, 5, 6)`

该计划意味着猩猩必须从 $1$ 号树（高度为 $2$），$2$ 号树（高度为 $1$），或 $3$ 号树（高度为 $6$）之一出发，并最终到达 $5$ 号树（高度为 $5$）或者 $6$ 号树（高度为 $7$）。

唯一一种跳跃次数最少的可行方案为：从 $3$ 号树出发，直接跳到 $6$ 号树。

因此，`minimum_jumps` 应该返回 $1$。

考虑另一个调用：

`minimum jumps(0, 1, 2, 2)`

该计划意味着猩猩必须从 $0$ 号树（高度为 $3$）或者 $1$ 号树（高度为 $2$）出发，并最终到达 $2$ 号树（高度为 $1$）。

由于 $2$ 号树是高度最低的树，所以无法从其他树上跳到 $2$ 号树。

因此，`minimum_jumps` 应该返回 $-1$。

**【数据范围】**

- $2 \le N \le 2 \times {10}^5$。
- $1 \le Q \le {10}^5$。
- $1 \le H[i] \le N$（$0 \le i \le N - 1$）。
- $H[i]\ne H[j]$（$0 \le i<j \le N - 1$）。
- $0 \le A \le B<C \le D \le N - 1$。

**【子任务】**

1. （4 分）：$H[i]=i+1$（$0 \le i \le N-1$）。
2. （8 分）：$N,Q \le 200$。
3. （13 分）：$N,Q \le 2000$。
4. （12 分）：$Q \le 5$。
5. （23 分）：$A=B$，$C=D$。
6. （21 分）：$C=D$。
7. （19 分）：无附加限制。


---

---
title: "[APIO2022] 火星"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8374
tag: ['2022', 'APIO', '交互题', 'Special Judge', 'O2优化']
---
# [APIO2022] 火星
## 题目背景

本题只支持 C++ 提交，提交时不需要包含 `mars.h` 头文件，只需要将附件中的 `mars.h` 中的内容粘贴到代码的开头即可。

请使用 C++14、C++17 等语言，**而不是 C++14 (GCC 9)**，因为一些未知原因这个语言下 SPJ 会 CE。

**【注】：洛谷暂不支持题面中所说的评测方式，我实现了一个洛谷支持的简易版本的交互库，但不能对传递数据进行有效限制，请各位自觉。**


## 题目描述

你们晓得，法老们是最先去过外太空的人。他们发射过首次登陆行星图特摩斯一世（Thutmus I，现在一般叫它火星）的飞船。行星的表面可以建模成由方形单元构成的 $(2n + 1) \times (2n + 1)$ 网格，其中每个单元中或者为陆地、或者为水域。对于第 $i$ 行第 $j$ 列（$0 \le i, j \le 2 \cdot n$）的单元，如果单元中为陆地，则其状态表示为 $s[i][j] = \texttt{1}$；如果单元中为水域，则表示为 $s[i][j] = \texttt{0}$。

如果在两个陆地单元之间存在某条仅由陆地单元构成的路径，而且路径中每两个连续的前后单元都有公共边，则称这两个陆地单元是连通的。行星上的岛屿被定义为两两连通的陆地单元的极大集合。

飞船的任务是统计该行星上岛屿的数量。然而，考虑到飞船的上古电脑，这事儿并不容易。电脑的内存储器 $h$ 以一个 $(2n + 1) \times (2n + 1)$ 的二维数组的形式存储数据，且数组的每个位置上可以保存长度为 $100$ 的字符串，串中的每个字母为 $\texttt{0}$（ASCII 码 $48$）或 $\texttt{1}$（ASCII 码 $49$）。初始时，存储器的每个位置的第 $0$ 位记录的是上述网格中每个单元的状态，即 $h[i][j][0] = s[i][j]$（对所有 $0 \le i, j \le 2 \cdot n$）。$h$ 中的其他位在初始时都被置为 $\texttt{0}$（ASCII 码 $48$）。

在处理存储器中的数据时，电脑只能访问存储器中的 $3 \times 3$ 区块，并且改写该区块左上角位置的值。说得更正式一点，电脑可以访问 $h[i \dots i + 2][j \dots j + 2]$（$0 \le i, j \le 2 \cdot (n - 1)$）中的值，并且改写 $h[i][j]$ 中的值。在
下文中，该过程被叫做**处理单元** $(i, j)$。

为了解决电脑能力的局限，法老们搞出了下面的套路：

- 电脑可以分成 $n$ 个阶段来操作存储器。
- 在阶段 $k$（$0 \le k \le n - 1$），令 $m = 2 \cdot (n - k - 1)$， 电脑将对所有的 $0 \le i, j \le m$，按照 $i$ 的升序以及每个 $i$ 上 $j$ 的升序，处理单元 $(i, j)$。换句话说，电脑将按照如下顺序处理这些单元：$(0, 0), (0, 1),\cdots , (0, m), (1, 0), (1, 1),\cdots , (1, m),\cdots , (m, 0), (m, 1),\cdots , (m, m)$。
- 在最后一个阶段（$k = n - 1$），电脑仅处理单元 $(0, 0)$。该阶段结束后，写入到 $h[0][0]$ 的值应该等于行星上的岛屿数量，而且该值应以字符串的形式表示成二进制，其中最低有效位对应于字符串的首字符。

下图给出了电脑操作某个 $5 \times 5$（$n = 2$）存储器的方式。蓝色单元表示该单元正在被改写，而着色的单元则表示被处理的子数组。

在阶段 $0$，电脑将以如下顺序处理下面的子数组：

![](https://cdn.luogu.com.cn/upload/image_hosting/m33yffaa.png)

在阶段 $1$，电脑将仅处理一个子数组：

![](https://cdn.luogu.com.cn/upload/image_hosting/inav002a.png)

你的任务是给出一个方法，让电脑能在给定的操作方式下，统计出行星图特摩斯一世上的岛屿数量。

## 实现细节

你需要实现下面的函数：

```cpp
string process(string[][] a, int i, int j, int k, int n)
```

- $a$：一个 $3 \times 3$ 数组，表示正在被处理的子数组。特别说明，有 $a = h[i \dots i + 2][j \dots j + 2]$，这里 $a$ 中的每个元素均为长度恰好为 $100$ 的字符串，而且串中的字符为 $\texttt{0}$（ASCII 码 $48$）或 $\texttt{1}$（ASCII 码 $49$）。
- $i, j$：电脑当前正在处理的单元的行号和列号。
- $k$：当前阶段的序号。
- $n$：阶段总数，同时也是行星表面的大小，此时行星表面包含 $(2n + 1) \times (2n + 1)$ 个单元。
- 该函数应返回一个长度为 $100$ 的二进制表示字符串。返回值将保存在电脑存储器中的 $h[i][j]$ 处。
- $k = n - 1$ 时，是该函数的最后一次调用。在此次调用中，函数应以字符串的形式返回行星上的岛屿数量的二进制表示，其最低有效位对应下标 $0$ 处的字符（二进制字符串的首字符），次低有效位对应下标 $1$ 处的字符，以此类推。
- 该函数必须独立于任何的静态或全局变量，且其返回值应仅依赖于传递给该函数的参数。

每个测试用例包括 $T$ 个独立的场景（也就是说，不同的行星表面情形）。你的函数在每个场景上的行为，必须与这些场景的顺序无关，因为对同一场景的 `process` 函数调用可能不是连续发生的。但是，可以确保对每个场景，会按照题面所描述的顺序来调用函数 `process`。

此外，对每个测试用例，你的程序可能会同时运行多个实例。内存限制和 CPU 用时限制将施加在所有这些实例的总和上。任何故意在这些实例之间偷偷传递数据的行为，都将被认定为作弊，选手可能会因此被取消比赛资格。

**【注】：洛谷暂不支持这种评测方式，我实现了一个洛谷支持的简易版本的交互库，但不能对传递数据进行有效限制，请各位自觉。**

特别说明，在调用函数 `process` 时保存在静态或全局变量中的信息，不保证在下次调用时可以读出。
## 输入格式

评测程序示例读取如下格式的输入：

- 第 $1$ 行：$T$。
- 第 $i$ 个区块（$0 \le i \le T - 1$）：该区块表示第 $i$ 个场景。
	- 第 $1$ 行：$n$。
	- 第 $2 + j$ 行（$0 \le j \le 2 ⋅ n$）：$s[j][0]\ s[j][1]\ \dots\ s[j][2 \cdot n]$。
## 输出格式

评测程序示例将按照如下格式打印出结果：

- 第 $1 + i$ 行（$0 \le i \le T - 1$）：在第 $i$ 个场景上，函数 `process` 最后一次的返回值的十进制表示。
## 样例

### 样例输入 #1
```
1
1
1 0 0
1 1 0
0 0 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
1
2
1 1 0 1 1
1 1 0 0 0
1 0 1 1 1
0 1 0 0 0
0 1 1 1 1
```
### 样例输出 #2
```
4
```
## 提示

## 例子

### 例 $1$

考虑 $n=1$ 的样例，其中 $s$ 如下所示：

```text
'1' '0' '0'
'1' '1' '0'
'0' '0' '1'
```

在本例中，行星表面包括 $3 \times 3$ 个单元，其中有 $2$ 个岛屿。对函数 `process` 的调用至多只有 $1$ 个阶段。

在阶段 $0$，评测程序将调用函数 `process` 恰好一次：

```cpp
process([["100","000","000"],["100","100","000"],["000","000","100"]],0,0,0,1)
```

注意这里仅展示了 $h$ 中每个元素的前 $3$ 位。

该函数应返回 $\texttt{0100}\dots$（省略的位全部为零），这里二进制的 $\dots 0010$ 等于十进制的 $2$。注意，这里省略了 $96$ 个零并用 $\dots$ 来代替。

### 例 $2$

考虑 $n=2$ 的样例，其中 $s$ 如下所示：

```text
'1' '1' '0' '1' '1'
'1' '1' '0' '0' '0'
'1' '0' '1' '1' '1'
'0' '1' '0' '0' '0'
'0' '1' '1' '1' '1'
```

在本例中，行星表面包括 $5 \times 5$ 个单元，其中有 $4$ 个岛屿。对函数 `process` 的调用至多只有 $2$ 个阶段。

在阶段 $0$，评测程序将调用函数 `process` 恰好一次：

```cpp
process([["100","100","000"],["100","100","000"],["100","000","100"]],0,0,0,2)
process([["100","000","100"],["100","000","000"],["000","100","100"]],0,1,0,2)
process([["000","100","100"],["000","000","000"],["100","100","100"]],0,2,0,2)
process([["100","100","000"],["100","000","100"],["000","100","000"]],1,0,0,2)
process([["100","000","000"],["000","100","100"],["100","000","000"]],1,1,0,2)
process([["000","000","000"],["100","100","100"],["000","000","000"]],1,2,0,2)
process([["100","000","100"],["000","100","000"],["000","100","100"]],2,0,0,2)
process([["000","100","100"],["100","000","000"],["100","100","100"]],2,1,0,2)
process([["100","100","100"],["000","000","000"],["100","100","100"]],2,2,0,2)
```

假定上面调用得到的返回值分别为 $\texttt{011},\texttt{000},\texttt{000},\texttt{111},\texttt{111},\texttt{011},\texttt{110},\texttt{010},\texttt{111}$，被省略的位均为零。因此，在阶段 $0$ 结束后，$h$ 将保存有如下的值：

```text
"011", "000", "000", "100", "100"
"111", "111", "011", "000", "000"
"110", "010", "111", "100", "100"
"000", "100", "000", "000", "000"
"000", "100", "100", "100", "100"
```

在阶段 $1$，评测程序将调用函数 `process` 一次：

```cpp
process([["011","000","000"],["111","111","011"],["110","010","111"]],0,0,1,2)
```

最后，本次函数调用应返回 $\texttt{0010000}\dots$（被省略的位均为零），这里二进制的 $\dots 0000100$ 等于十进制的 $4$。注意这里省略了 $93$ 个零并用 $\dots$ 来代替。

## 约束条件

- $1\le T\le 10$。
- $1\le n\le 20$。
- $s[i][j]$ 为 $\texttt{0}$（ASCII 码 $48$）或 $\texttt{1}$（ASCII 码 $49$）（对所有 $0\le i,j\le 2\cdot n$）。
- $h[i][j]$ 的长度恰好为 $100$（对所有 $0\le i,j\le 2\cdot n$）。
- $h[i][j]$ 中的每个字符均为 $\texttt{0}$（ASCII 码 $48$）或 $\texttt{1}$（ASCII 码 $49$）（对所有 $0\le i,j\le 2\cdot n$）。

对函数 `process` 的每次调用，都有：

- $0\le k\le n-1$。
- $0\le i,j\le 2\cdot (n-k-1)$。

## 子任务

1. （$6$ 分）$n\le 2$。
2. （$8$ 分）$n\le 4$。
3. （$7$ 分）$n\le 6$。
4. （$8$ 分）$n\le 8$。
5. （$7$ 分）$n\le 10$。
6. （$8$ 分）$n\le 12$。
7. （$10$ 分）$n\le 14$。
8. （$24$ 分）$n\le 16$。
9. （$11$ 分）$n\le 18$。
10. （$11$ 分）$n\le 20$。


---

---
title: "[APIO2022] 游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8375
tag: ['2022', 'APIO', '交互题', 'Special Judge', 'O2优化']
---
# [APIO2022] 游戏
## 题目背景

本题只支持 C++ 提交，提交时不需要包含 `game.h` 头文件，只需要将附件中的 `game.h` 中的内容粘贴到代码的开头即可。
## 题目描述

法老们发现了标号从 $0$ 到 $n - 1$ 的 $n$ 个星球，并且在它们之间建立了一个**单向传输系统**。在这个传输系统中，每个传送器连接一个起始星球和一个目的星球。当游客从一个起始星球使用传送器，就可以到达对应的目的星球。需要注意的是，起始星球和目的星球有可能是同一个星球。我们使用 $(u, v)$ 表示一个起始于星球 $u$ 到达星球 $v$ 的传送器。

为了促进传输系统的广泛使用，法老们设计了一个供游客们在乘坐传送系统时可以进行的游戏。一名游客可以从任一星球出发。标号 $0, 1,\dots , k - 1$（$k \le n$）的星球被称为**特殊星球**。当游客每次进入一个特殊星球，就可以获得一枚邮票。

目前，对于每个星球 $i$（$0 \le i \le k - 2$），都建立了一个传送器 $(i, i + 1)$。这 $k - 1$ 个传送器叫做**起始传送器**。

传送器随着时间不断建立。随着传送器的建立，一名游客也许有可能获得无穷多枚邮票。准确来说，这种情况会在存在一个满足如下条件的星球序列 $w[0], w[1],\dots , w[t]$ 时发生：

- $1 \le t$。
- $0 \le w[0] \le k - 1$。
- $w[t] = w[0]$。
- 对于每个星球 $i$（$0 \le i \le t - 1$），存在一个传送器 $(w[i], w[i + 1])$。

注意一名游客能够使用起始传送器和任何一个目前已经建立的传送器。

你的任务是，帮助法老验证在每次加入新的传送器后，一位游客是否能够拿到无穷多枚邮票。

## 实现细节

你需要实现下述函数：

```cpp
init(int n, int k)
```

- $n$：星球数量。
- $k$：特殊星球数量。
- 这个函数只会被调用一次，早于任何一次 `add_teleporter` 调用。

```cpp
int add_teleporter(int u, int v)
```

- $u$ 和 $v$：被加入传送器的起始和目的星球。
- 这个函数至多被调用 $m$ 次（$m$ 的取值范围参阅“约束条件”部分的内容）。
- 如果当传送器 $(u, v)$ 被加入后游客能够获得无穷多枚邮票，函数需要返回 $1$。否则，这个函数应该返回 $0$。
- 一旦函数返回了 $1$，你的程序将会被终止。
## 输入格式

评测程序示例按照如下的格式读取输入数据：

- 第 $1$ 行：$n\ m\ k$。
- 第 $2 + i$ 行（$0 \le i \le m - 1$）：$u[i]\ v[i]$。

评测程序示例首先调用 `init`，然后按照 $i = 0, 1,\dots , m - 1$ 的顺序调用 `add_teleporter`：$u = u[i]$ 和 $v = v[i]$。
## 输出格式

程序需要打印多次调用 `add_teleporter` 中首次返回 $1$ 的调用索引（$0$ 到 $m - 1$，包含 $0$ 和 $m - 1$）；当所有 `add_teleporter` 调用中都返回 $0$ 时，你的程序需要返回 $m$。

如果某次 `add_teleporter` 调用返回了 $0$ 和 $1$ 之外的整数，评测程序示例会打印 $-1$，你的程序会被马上终止。
## 样例

### 样例输入 #1
```
6 5 3
3 4
5 0
4 5
5 3
1 4
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
4 1 2
1 1
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
4 3 2
1 3
2 0
3 2
```
### 样例输出 #3
```
2
```
## 提示

## 例子

### 例 $1$

考虑下面的函数调用：

```cpp
init(6, 3)
```

在这个例子里，有 $6$ 个星球和 $3$ 个特殊星球，标号为 $0,1,2$ 的星球是特殊星球。起始传送器是 $(0,1)$ 和 $(1,2)$。

假设评测程序执行下述调用：

- (0) `add_teleporter(3, 4)`：应该返回 $0$。
- (1) `add_teleporter(5, 0)`：应该返回 $0$。
- (2) `add_teleporter(4, 5)`：应该返回 $0$。
- (3) `add_teleporter(5, 3)`：应该返回 $0$。
- (4) `add_teleporter(1, 4)`：在这种情况下，是可能获得无穷多枚邮票的。例如，游客可以从星球 $0$ 出发，按照 $1, 4, 5, 0, 1, 4, 5, 0,\dots$ 这个顺序进行。因此，函数需要返回 $1$，进一步你的程序会被终止。

下图对于这个例子进行了说明。特殊星球和起始传送器都使用粗体字表示。通过 `add_teleporter` 加入的传送器，按照顺序被标记为 $0$ 到 $4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/q80oy4px.png)

### 例 $2$

考虑下面的函数调用：

```cpp
init(4, 2)
```

在这个例子里，有 $4$ 个星球和 $2$ 个特殊星球。标号为 $0$ 和 $1$ 星球是特殊星球。起始传送器是 $(0, 1)$。

假设评测程序执行下述调用：

- `add_teleporter(1, 1)`：当加入传送器 $(1, 1)$ 后，我们就能够获得无穷多枚邮票。例如，游客从星球 $1$ 出发，可以使用传送器 $(1, 1)$ 到达星球 $1$ 无限次。因此，函数需要返回 $1$，然后你的程序被终止。

附件包里还包含了另一个样例输入输出。

## 约束条件

- $1\le n\le 3\times 10^5$；
- $1\le m\le 5\times 10^5$；
- $1\le k\le n$。

对于每次调用 `add_teleporter` 函数：

- $0\le u\le n-1$ 和 $0\le v\le n-1$；
- 在传送器 $(u,v)$ 加入之前，不会有从星球 $u$ 到星球 $v$ 的传送器。

## 子任务

1. （$2$ 分）$n=k$，$n\le 100$，$m\le 300$；
2. （$10$ 分）$n\le 100$，$m\le 300$。
3. （$18$ 分）$n\le 10^3$，$m\le 5\times 10^3$。
4. （$30$ 分）$n\le 3\times 10^4$，$m\le 5\times 10^4$，$k\le 10^3$。
5. （$40$ 分）没有额外的约束条件。


---

