---
title: "[USACO24DEC] Maximize Minimum Difference P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11460
tag: ['数学', 'USACO', '2024', '分类讨论']
---
# [USACO24DEC] Maximize Minimum Difference P
## 题目描述

**注意：本题的时间限制为 4 秒，通常限制的 2 倍。**

哞！你被给定了一个整数 $N$（$2\le N\le 2000$）。考虑 $[0,1,2\dots, N-1]$ 的所有排列 $p=[p_0,p_1,\dots, p_{N-1}]$。令 $f(p)=\min_{i=0}^{N-2}|p_i-p_{i+1}|$ 表示 $p$ 中任意两个连续元素之间的最小绝对差值，并令 $S$ 表示所有达到 $f(p)$ 最大可能值的 $p$ 的集合。

你还被给定了 $K$（$0\le K\le N$）个限制，形式为 $p_i=j$（$0\le i,j<N$）。计算 $S$ 中满足所有限制的排列数量，对 $10^9+7$ 取模。
## 输入格式

输入的第一行包含 $T$ 和 $N$（$1\le TN\le 2\cdot 10^4$），表示你需要求解 $T$ 个独立的测试用例，每个测试用例指定一组不同的限制。

每个测试用例的第一行包含 $K$，以下 $K$ 行，每行包含 $i$ 和 $j$。输入保证

相同的 $i$ 在同一测试用例中不会出现超过一次。
相同的 $j$ 在同一测试用例中不会出现超过一次。
## 输出格式

对于每个测试用例输出一行，包含答案模 $10^9+7$ 的余数。

## 样例

### 样例输入 #1
```
3 4
0
1
1 1
2
0 2
2 3
```
### 样例输出 #1
```
2
0
1
```
### 样例输入 #2
```
9 11
2
0 5
6 9
3
0 5
6 9
1 0
4
0 5
6 9
1 0
4 7
5
0 5
6 9
1 0
4 7
2 6
6
0 5
6 9
1 0
4 7
2 6
9 3
7
0 5
6 9
1 0
4 7
2 6
9 3
5 2
8
0 5
6 9
1 0
4 7
2 6
9 3
5 2
7 4
9
0 5
6 9
1 0
4 7
2 6
9 3
5 2
7 4
3 1
10
0 5
6 9
1 0
4 7
2 6
9 3
5 2
7 4
3 1
8 10
```
### 样例输出 #2
```
6
6
1
1
1
1
1
1
1
```
### 样例输入 #3
```
10 11
0
1
3 8
2
3 8
5 7
3
3 8
5 7
4 2
4
3 8
5 7
4 2
10 6
5
3 8
5 7
4 2
10 6
8 10
6
3 8
5 7
4 2
10 6
8 10
1 9
7
3 8
5 7
4 2
10 6
8 10
1 9
7 5
8
3 8
5 7
4 2
10 6
8 10
1 9
7 5
2 3
9
3 8
5 7
4 2
10 6
8 10
1 9
7 5
2 3
6 0
```
### 样例输出 #3
```
160
20
8
7
2
1
1
1
1
1
```
### 样例输入 #4
```
5 987
3
654 321
543 210
432 106
2
654 321
543 210
1
654 321
1
0 493
0
```
### 样例输出 #4
```
0
538184948
693625420
932738155
251798971
```
## 提示

样例 1 解释：

$f(p)$ 的最大值为 $2$，且 $S=\{[2,0,3,1], [1,3,0,2]\}$。

样例 2 解释：

$p=[5, 0, 6, 1, 7, 2, 9, 4, 10, 3, 8]$ 在所有测试用例中都应当被计算在内。


样例 3 解释：

$p=[4, 9, 3, 8, 2, 7, 0, 5, 10, 1, 6]$ 在所有测试用例中都应当被计算在内。

样例 4 解释：


确保输出答案对 $10^9+7$ 取模。

- 测试点 $5$：$N=15$。
- 测试点 $6$：$N=2000$。
- 测试点 $7\sim 9$：对于所有测试用例，均存在限制 $p_0=\lfloor N/2\rfloor$。
- 测试点 $10\sim 13$：对于所有测试用例，均存在某个限制 $p_i = j$，其中 $j$ 等于 $\lfloor N/2\rfloor$。
- 测试点 $14\sim 20$：没有额外限制。





---

---
title: "【MX-X7-T7】[LSOT-3] 魔女与推理的轮舞曲"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11566
tag: ['O2优化', '最大公约数 gcd', '线性基', '构造', 'Ad-hoc', '分类讨论', '梦熊比赛']
---
# 【MX-X7-T7】[LSOT-3] 魔女与推理的轮舞曲
## 题目背景

原题链接：<https://oier.team/problems/X7H>。

>魔女展示了空着的左手。$\\$
把左手握上，向着那边，嘿嘿嘿。$\\$
然后打开右拳，手心里有个糖球。$\\$
那么，这是魔法呢？还是戏法呢？
## 题目描述

黄金乡中，贝阿朵和战人在新的棋盘上展开的红蓝论战，这个棋盘的规则与之前的有所不同。

具体地说，有初始全 $0$ 的一个 $n\times m$ 的棋盘（格子数为 $n\times m$），可以在棋盘上使用红色真实和蓝色真实。红色真实和蓝色真实都各代表一个矩形，分别是 $a\times b$ 和 $c\times d$，使用红色真实或蓝色真实，要选择棋盘上一个格子，然后将以这个格子为左上角的那个使用的真实所对应的矩形内的所有格子异或 $1$（如果超出棋盘则不能选择此格子）。

贝阿朵想测试一些规则是否符合她的心意，所以她会问你对于某个规则，通过使用任意次红色真实与蓝色真实可以构筑出多少种不同的棋盘。

由于答案可能过大，你仅需输出对 $10^9+7$ 取模的结果即可，贝阿朵可以通过使用魔法来复原结果。
## 输入格式

第一行，一个正整数 $T$，表示贝阿朵想要测试的规则数量。

接下来 $T$ 行，每行六个正整数 $n, m, a, b, c, d$，含义与题目中的一致。
## 输出格式

对于每个贝阿朵想测试的规则，一行，一个非负整数，表示棋盘可能数对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
10
100 100 715 1129 123 654
3 3 1 1 2 2
4 4 2 2 3 3
4 3 4 3 3 2
20 50 15 12 10 7
50 20 33 11 25 3
107151129 147744151 715 715 1129 1129
23456 54321 1992 725 12347 7913
10000000 10000000 2222 444 3333 555
10000000 10000000 7130713 4237018 7812367 1245634

```
### 样例输出 #1
```
1
512
4096
32
248906884
412057510
710040542
936321181
222744797
17474728

```
## 提示

> 没有爱，就看不见。

**【样例解释】**

对于第一种规则，无法使用红色真实或蓝色真实，故只有全是 $0$ 一种情况。

对于第二种规则，每个格子都可以独立地取 $0$ 或 $1$，故答案为 $2^{3\times 3}=512$。

对于第三种规则，一种可能的局面是：

```
1100
1011
0100
0100
```

生成方式为选择第一行第一个格子使用红色真实，选择第二行第二个格子使用蓝色真实，选择第三行第三个格子使用红色真实。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（3 分）：$a\mid c$，$b\mid d$。
- 子任务 2（4 分）：$\sum n\times m\le 20$。
- 子任务 3（16 分）：$\sum n\times m\le 1000$。
- 子任务 4（17 分）：$a=b$，$c=d$。
- 子任务 5（19 分）：$a,b,c,d$ 中任意两个数的 $\gcd$ 都为 $1$。
- 子任务 6（20 分）：$100\times(a+b+c+d)\le  \min (n,m)$。
- 子任务 7（21 分）：无特殊性质。

对于全部的数据，$1\le T\le10^6$，$1\le n,m,a,b,c,d \le 10^9$。


---

---
title: "[PA 2016] 台球 / Bilard Hilberta"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11612
tag: ['动态规划 DP', '数学', '2016', '递归', '分治', '分类讨论', 'PA（波兰）']
---
# [PA 2016] 台球 / Bilard Hilberta
## 题目背景

译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R5 Bilard Hilberta [A] (HIL)。

## 题目描述


考虑如下的 Hilbert 曲线：

$n$ 阶的 Hilbert 曲线的大小为 $2^{n+1}\times 2^{n+1}$。这里，$n\ge 1$。

$n=1$ 时的曲线在下图中给出，而 $n\gt 1$ 时的曲线由四个 $(n-1)$ 阶的曲线组成。左下角的曲线被顺时针旋转了 $90^\circ$，而右下角的曲线则被逆时针旋转了 $90^\circ$，而且在左上与左下、左上与右上、右上与右下的曲线的相接处添加了长度为 $2$ 的额外曲线将它们连为一体。

下图中从左至右分别展示了 $n=1,2,3$ 时的曲线。

![](https://cdn.luogu.com.cn/upload/image_hosting/ynfo38pq.png)

令左下角的坐标为 $(0,0)$，右下角的坐标为 $(2^{n+1},0)$，右上角坐标为 $(2^{n+1},2^{n+1})$。

将球视为质点。球从 $(1,0)$ 出发，其速度矢量 $\boldsymbol{v}=(1,1)$。撞到边缘或者曲线上之后，它会反弹，这里的碰撞是**完全弹性碰撞**，也就是垂直于撞击面的速度分量反向，平行于撞击面的速度分量不变。可以证明撞到的一定是一个面，没有撞到角的情况。

$m$ 次询问，每次问球出发 $t_i$ 秒后，球的位置。
## 输入格式



第一行两个正整数 $n,m$。

接下来 $m$ 行，第 $i$ 行只有一个整数 $t_i$，描述一次询问。
## 输出格式

输出 $m$ 行，每行两个整数表示球的位置。

## 样例

### 样例输入 #1
```
3 2
1
42
```
### 样例输出 #1
```
2 1
3 14
```
## 提示


#### 样例解释

在【题目描述】的图中已经给出。

#### 数据范围

- $1\le n\le 30$；
- $1\le m\le 10^5$；
- $0\lt t_1\lt t_2\lt \ldots \lt t_m\lt 2^{2(n+1)}$。


---

---
title: "[USACO25FEB] Transforming Pairs P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11846
tag: ['数学', 'USACO', '2025', '最大公约数 gcd', '分类讨论']
---
# [USACO25FEB] Transforming Pairs P
## 题目描述

回答 $Q$（$1\le Q\le 10^5$）个独立查询，每个查询的形式如下：

给定四个整数 $a$，$b$，$c$，$d$（$-10^{18}\le a,b,c,d\le 10^{18}$）。在一次操作中，你可以执行 $a\mathrel{+}=b$，或 $b\mathrel{+}=a$。求将 $(a,b)$ 转变为 $(c,d)$ 所需要的最小操作次数，或者如果不可能完成，输出 $-1$。
## 输入格式

输入的第一行包含 $Q$。

以下 $Q$ 行，每行包含四个整数 $a$，$b$，$c$，$d$。
## 输出格式

每行输出一个查询的答案。

## 样例

### 样例输入 #1
```
4
5 -3 -1 -3
5 3 5 2
5 3 8 19
5 3 5 3
```
### 样例输出 #1
```
2
-1
3
0
```
## 提示

样例 1 解释：

第一个查询：$(5,-3)\to (2,-3)\to (-1,-3)$。

第二个查询：不可能。

第三个查询：$(5,3) \to (8, 3) \to (8, 11) \to (8, 19)$。

第四个查询：不需要任何操作。


- 测试点 $2$：$|a|, |b|, |c|,|d|\le 10$。
- 测试点 $3$：$a,b\ge 0$。
- 测试点 $4$：$a \geq 0 \geq b$。
- 测试点 $5$：$a \leq 0 \leq b$。
- 测试点 $6$：$a,b\le 0$。
- 测试点 $7$：$c,d\ge 0$。
- 测试点 $8$：$c \geq 0 \geq d$。
- 测试点 $9$：$c \leq 0 \leq d$。
- 测试点 $10$：$c,d\le 0$。
- 测试点 $11\sim 14$：$Q \leq 10^3$。
- 测试点 $15\sim 19$：没有额外限制。


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
title: "[UOI 2025] Simple Task"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12551
tag: ['2025', 'Special Judge', '分类讨论', 'UOI（乌克兰）']
---
# [UOI 2025] Simple Task
## 题目描述

We call a non-empty sequence of positive integers *strange* if the sum of its elements is a prime number.

You are given an array $a$ of length $n$, **consisting of prime numbers**. You are also given an integer $k$.

Split the array $a$ into $k$ **non-empty** subsequences$^1$ such that each element of the array $a$ belongs to exactly one of them, and the number of *strange* subsequences among the formed ones is minimized.

In this problem, each test contains several sets of input data. You need to solve the problem independently for each such set.

**Note that there is no block "without additional constraints" in this problem.**
## 输入格式

The first line contains one integer $T$ $(1\le T\le 10^5)$ --- the number of sets of input data. The description of the input data sets follows.

In the first line of each input data set, two integers $n$, $k$ $(1 \le k \le n \le 10^5)$ are given --- the length of the array $a$ and the number of subsequences into which it needs to be split.

In the second line of each input data set, $n$ prime numbers $a_1, a_2, \ldots, a_n$ $(2\le a_i\le 10^5, a_i\le a_{i+1})$ are given --- the elements of the array $a$.

It is guaranteed that the sum of $n$ across all input data sets of one test does not exceed $10^5$.
## 输出格式

For each set of input data, output the optimal partition in the following format:

- In the first line, output one integer $m$ --- the number of *strange* subsequences among the formed ones;
- In each of the next $k$ lines, output integers $s_i$ and $b_1, b_2, \ldots, b_{s_i}$ $(1\le s_i\le n)$ --- the number of elements in the corresponding subsequence of the partition and the elements themselves.

Subsequences and their elements may be output in any order.

If there are multiple correct answers, any of them is allowed.
## 样例

### 样例输入 #1
```
4
3 1
5 5 13
4 2
2 3 5 7
5 3
3 3 5 5 13
6 5
2 2 2 3 3 3
```
### 样例输出 #1
```
1
3 13 5 5
0
2 2 7
2 3 5
1
1 13
2 3 3
2 5 5
4
1 2
1 2
1 2
1 3
2 3 3
```
## 提示

$^1$ A sequence $c$ is called a subsequence of an array $b$ if it is possible to remove a certain number of elements from the array $b$ (possibly zero) so that the sequence $c$ is formed.

### Scoring

- ($2$ points): $T \leq 20$, $k=1$;
- ($5$ points): $n \leq 4$, $a_i \leq 10^4$ for all $1\le i\le n$;
- ($8$ points): $T \leq 20$, $n \leq 10$, $a_i \leq 10^4$ for all $1\le i\le n$;
- ($4$ points): $n$ --- even, $a_i > 2$ for all $1\le i\le n$;
- ($18$ points): $n$ --- odd, $a_i > 2$ for all $1\le i\le n$;
- ($10$ points): $2\cdot k \ge n + 1$;
- ($29$ points): $n$ --- even;
- ($24$ points): $n$ --- odd.


---

---
title: "序列游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12695
tag: ['高精度', '博弈论', '2014', '多项式', '提交答案', '排序', '置换', '凸包', '其它技巧', '位运算', '快速数论变换 NTT', '分类讨论', '湖北']
---
# 序列游戏
## 题目背景

出题人：VFleaKing & hjy96
## 题目描述

从前有一天 hjy 在机房里愉快地刷题，但是他绞尽脑汁也只会写暴力，因此他想起了什么题都能够一眼秒的你，请你来帮助他 AC 吧！由于 hjy 现在心情比较糟，所以不想告诉你题面，请你根据他写的暴力程序推测题面，并帮他 AC。幸运的是我们并不是一无所知：我们知道这个程序的输入是两个整数序列。

我们给出 prog.exe，这是 hjy 写的暴力。你可以给这个程序一些输入，来推测他的用途。

我们给出 20 个输入文件 game1 ~ 20.in，请你写一个程序计算出对应的正确答案 game1 ~ 20.out。
## 输入格式

第一行有一个正整数 algoNum。表示算法编号。

第二行有一个正整数 $n$。表示序列长度。

第三行包括 $n$ 个用空格隔开的整数用来表示序列 $a[1], a[2], \dots, a[n]$。

第四行包括 $n$ 个用空格隔开的整数用来表示序列 $b[1], b[2], \dots, b[n]$。
## 输出格式

请根据 prog.exe 进行推测。

## 提示

为降低难度，操作相似的测试点相邻（有各别例外）。

运行 prog.exe 的方式为在命令行里输入

```
prog.exe <input> <output>
```

用来指定 prog 的输入和输出的文件位置。例如

```
prog.exe prog1.in prog1.out
```
prog.exe 会检测输入数据的合法性。如果数据不合法 prog.exe 会报错并不会产生输出。

当然我们还提供了 linux 版的 prog。运行方式为
```
./prog <input> <output>
```
注意 prog.exe 是个暴力程序，对于大数据它会跑得非常慢。

数据规模见输入文件。下表为原题的测试点分数，在洛谷上每个测试点 5 分。

| 数据编号 | 分值 |
| --- | --- |
| 1 | $2$ |
| 2 | $4$ |
| 3 | $7$ |
| 4 | $8$ |
| 5 | $9$ |
| 6 | $10$ |
| 7 | $20$ |
| 8 | $45$ |
| 9 | $10$ |
| 10 | $15$ |
| 11 | $5$ |
| 12 | $35$ |
| 13 | $10$ |
| 14 | $20$|
| 15 | $25$ |
| 16 | $10$ |
| 17 | $15$ |
| 18 | $30$ |
| 19 | $10$ |
| 20 | $10$ |


---

---
title: "[USACO21FEB] Minimizing Edges P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7417
tag: ['贪心', 'USACO', '2021', 'O2优化', '分类讨论']
---
# [USACO21FEB] Minimizing Edges P
## 题目描述

Bessie 有一个连通无向图 $G$。$G$ 有 $N$ 个编号为 $1\ldots N$ 的结点，以及 $M$ 条边（$2\le N\le 10^5, N-1\le M\le \frac{N^2+N}{2}$）。$G$ 有可能包含自环（一个结点连到自身的边），但不包含重边（连接同一对结点的多条边）。

令 $f_G(a,b)$ 为一个布尔函数，对于每一个 $1\le a\le N$ 和 $0\le b$，如果存在一条从结点 $1$ 到结点 $a$ 的路径恰好经过了 $b$ 条边，则函数值为真，否则为假。如果一条边被经过了多次，则这条边会被计算相应的次数。

Elsie 想要复制 Bessie。具体地说，她想要构造一个无向图 $G'$，使得对于所有的 $a$ 和 $b$，均有 $f_{G'}(a,b)=f_G(a,b)$。

Elsie 想要进行最少数量的工作，所以她想要构造最小可能的图。所以，你的工作是计算 $G'$ 的边数的最小可能值。

每个输入包含 $T$（$1\le T\le 5\cdot 10^4$）组独立的测试用例。保证所有测试用例中的 $N$ 之和不超过 $10^5$，且所有测试用例中的 $M$ 之和不超过 $2\cdot 10^5$。

## 输入格式

输入的第一行包含 $T$，为测试用例的数量。

每个测试用例的第一行包含两个整数 $N$ 和 $M$。

每个测试用例的以下 $M$ 行每行包含两个整数 $x$ 和 $y$（$1\le x\le y\le N$），表示 $G$ 中存在一条连接 $x$ 与 $y$ 的边。

为提高可读性，相邻的测试用例之间用一个空行隔开。
## 输出格式

对每个测试用例，输出一行，为 $G'$ 中的边数的最小可能值。
## 样例

### 样例输入 #1
```
2

5 5
1 2
2 3
2 5
1 4
4 5

5 5
1 2
2 3
3 4
4 5
1 5
```
### 样例输出 #1
```
4
5
```
### 样例输入 #2
```
7

8 10
1 2
1 3
1 4
1 5
2 6
3 7
4 8
5 8
6 7
8 8

10 11
1 2
1 5
1 6
2 3
3 4
4 5
4 10
6 7
7 8
8 9
9 9

13 15
1 2
1 5
1 6
2 3
3 4
4 5
6 7
7 8
7 11
8 9
9 10
10 11
11 12
11 13
12 13

16 18
1 2
1 7
1 8
2 3
3 4
4 5
5 6
6 7
8 9
9 10
9 15
9 16
10 11
11 12
12 13
13 14
14 15
14 16

21 22
1 2
1 9
1 12
2 3
3 4
4 5
5 6
6 7
7 8
7 11
8 9
8 10
12 13
13 14
13 21
14 15
15 16
16 17
17 18
18 19
19 20
20 21

20 26
1 2
1 5
1 6
2 3
3 4
4 5
4 7
6 8
8 9
8 11
8 12
8 13
8 14
8 15
8 16
8 17
9 10
10 18
11 18
12 19
13 20
14 20
15 20
16 20
17 20
19 20

24 31
1 2
1 7
1 8
2 3
3 4
4 5
5 6
6 7
6 9
8 10
10 11
10 16
10 17
10 18
10 19
10 20
11 12
12 13
13 14
14 15
15 16
15 17
15 18
15 19
15 20
15 21
15 22
15 23
15 24
21 22
23 24
```
### 样例输出 #2
```
10
11
15
18
22
26
31
```
## 提示

#### 样例 1 解释

在第一个测试用例中，Elsie 可以通过从 $G$ 中移除 $(2,5)$ 来构造得到 $G'$。或者，她也可以构造一张包含以下边的图，因为她并未被限制只能从 $G$ 中移除边：

```
1 2
1 4
4 3
4 5
```

Elsie 显然不能得到比 $N-1$ 更优的解，因为 $G'$ 一定也是连通的。

#### 样例 2 解释

在以上这些测试用例中，Elsie 都不能做得比 Bessie 更优。

#### 测试点性质：

 - 对于另外 $5\%$ 的数据，满足 $N\le 5$。
 - 对于另外 $10\%$ 的数据，满足 $M=N$。
 - 对于另外 $20\%$ 的数据，如果并非对于所有的 $b$ 均有 $f_G(x,b)=f_G(y,b)$，则存在 $b$ 使得 $f_G(x,b)$ 为真且 $f_G(y,b)$ 为假。
 - 对于另外 $30\%$ 的数据，满足 $N\le 10^2$。   
 - 对于另外 $25\%$ 的数据，没有额外限制。

供题：Benjamin Qi


---

---
title: "[集训队互测 2022] 心跳排列图"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9054
tag: ['动态规划 DP', '贪心', '集训队互测', '2022', 'Special Judge', 'O2优化', '构造', 'Ad-hoc', '分类讨论']
---
# [集训队互测 2022] 心跳排列图
## 题目背景

下发文件见附件。
## 题目描述

注：本题中所有序列下标均从 1 开始。

机器人心脏的跳动，排列成图是什么样的？

你有一个算法竞赛机器人，每分钟心跳 $n$ 次，第 $i$ 次心跳的强度为 $a_i$。这里，$a_1\sim a_n$ 恰为 $1\sim n$ 的一个排列。

设 $A_i$ 为序列 $a$ 删除第 $i$ 个元素后得到的序列，即 $A_i=[a_1,\dots,a_{i-1},a_{i+1},\dots,a_n]$。

对于元素互不相同的序列 $p$，设 $G(p)$ 为一个无向图，有 $|p|$ 个点，编号为 $1\sim |p|$。对于每对正整数 $1\le i\lt j\le |p|$，若 $\forall k\in [i,j]\cap \mathbb{Z}$，都有 $p_k\in [\min(p_i,p_j),\max(p_i,p_j)]$，则 $G(p)$ 中 $i$ 号点和 $j$ 号点有一条边。设 $F(p)$ 为 $G(p)$ 中 $1$ 号点到 $|p|$ 号点的最短路长度，这里一条路径长度定义为其边数。

设 $f(a)=[F(A_1),F(A_2),\dots,F(A_n)]$。

给定长度为 $n$ 的序列 $[b_1,\dots,b_n]$，请你求出任意一个 $1\sim n$ 的排列 $a$，使得 $f(a)=b$。**保证有解。**

在某些子任务中，算法竞赛机器人小 G 会给你一些“提示”：设 $G_0=G(a)$，设 $path_0$ 为 $G_0$ 中某条 $1$ 到 $n$ 的最短路经过的点构成的集合，设 $path_j$ 为 $G(A_j)$ 中某条起始点到结束点的最短路经过的点构成的集合（注意，为了方便，这里给出的 $path_j$ 中点的编号仍然沿用原图中点的编号，参见样例 2）。则小 G 有可能会额外告诉你所有 $path_j$（包括 $path_0$），也有可能只告诉你 $path_0$，也有可能不给你提示，详见输入格式。

保证给出的提示是正确的，也即一定存在一个满足所有提示的排列。

下发文件中有 `checker.cpp`，你可以用它来检查自己的输出是否正确。用法是 `./checker input output output`，`input` 和 `output` 分别为输入文件和你的输出。同时还下发了 `testlib.h`，请将其和 checker 置于同一目录下来编译 checker。
## 输入格式

第一行两个正整数，为子任务编号 $S$ 以及数据组数 $T$。

接下来 $T$ 组数据，每组数据格式为：第一行一个正整数 $n$，第二行 $n$ 个正整数 $b_1,\dots,b_n$。

**特别地，**

1. 若 $S=5$，每组数据还会输入 $n+1$ 行，这 $n+1$ 行里第 $i$ 行是一个长度为 $n$ 的 01 串 $c_i$，$c_{i,j}=[j\in path_{i-1}]$。
2. 若 $S=6$，每组数据还会输入第三行，包含一个长度为 $n$ 的 01 串 $c$，$c_i=[i\in path_0]$。

注意：

1. 即使你的程序不需要用到提示，在 $S=5$ 或 $S=6$ 时你仍然需要读入数组 $c$。
2. 对于一种输入的 $b$，符合条件的 $a$ 可能不唯一，进而 $c$ 可能也不唯一。**不要求**你的输出符合我们给出的 $c$ 的限制，只要符合 $b$ 的限制即视为正确。

同一行输入的不同变量用一个空格隔开。
## 输出格式

对于每组数据输出一行 $n$ 个正整数，为你求出的排列 $a$。
## 样例

### 样例输入 #1
```
9 11
4
2 2 1 1
4
2 2 2 2
4
2 1 1 2
7
5 5 4 4 4 5 5
7
1 3 2 2 2 2 4
7
3 3 2 4 4 5 3
8
2 2 3 5 3 3 3 4
8
5 4 4 4 4 6 6 5
8
4 4 4 2 4 4 2 3
9
4 7 5 5 5 5 3 4 4
9
3 4 4 4 4 4 4 4 6
```
### 样例输出 #1
```
1 2 4 3
2 1 4 3
1 3 2 4
3 1 7 2 6 4 5
3 1 6 4 2 5 7
2 3 1 6 4 7 5
5 6 3 1 7 4 2 8
1 8 2 7 3 5 6 4
6 3 2 7 4 5 1 8
5 8 6 3 7 1 9 2 4
2 9 3 1 8 5 7 6 4
```
### 样例输入 #2
```
5 1
4
2 2 1 1
1011
0111
1011
1001
1010
```
### 样例输出 #2
```
1 2 4 3
```
### 样例输入 #3
```
6 1
4
2 2 1 1
1011
```
### 样例输出 #3
```
1 2 4 3
```
## 提示

**样例 1 解释**

考虑样例中的第一组数据。一组解是 $a=[1,2,4,3]$。$A_1,A_2,A_3,A_4$ 分别为 $[2,4,3],[1,4,3],[1,2,3],[1,2,4]$。$G(A_1),G(A_2),G(A_3),G(A_4)$ 四个图中的边分别为：

- $G(A_1)$：$(1,2),(2,3)$。因此 $F(A_1)=2$。
- $G(A_2)$：$(1,2),(2,3)$。因此 $F(A_2)=2$。
- $G(A_3)$：$(1,2),(1,3),(2,3)$。因此 $F(A_3)=1$。
- $G(A_4)$：$(1,2),(1,3),(2,3)$。因此 $F(A_4)=1$。

所以 $f(a)=[2,2,1,1]$，符合输入。

符合输入的 $a$ 不唯一，比如 $a=[4,3,1,2]$ 也是正确的。

**样例 2 解释**

该样例的排列和第一个样例中第一组数据是相同的，但本样例存在子任务 5 的提示。注意在给出 $path_j$ 时仍然沿用原编号，例如删去 $1$ 后，新的最短路经过的点编号为 $2\to 3\to 4$。

**样例 3 解释**

该样例的排列和第一个样例中第一组数据是相同的，但本样例存在子任务 6 的提示。

**数据范围**

对于所有数据：$1\le T\le 4\times 10^4,4\le n\le 10^5,\sum n\le 5\times 10^5$。

- 子任务 1（$7$ 分）$T\le 250,n\le 7$。
- 子任务 2（$5$ 分）$b_i=1$。
- 子任务 3（$10$ 分）$n\ge 90000$，保证存在一组解满足 $a_1=1,a_n=n$。
- 子任务 4（$7$ 分）$n\ge 90000$，保证存在一组解满足 $a_2=1,a_{n-1}=n$。
- 子任务 5（$15$ 分）$n\le 100,\sum n^3\le 3\times 10^6$，存在所有 $path_j$ 的提示。
- 子任务 6（$15$ 分）$n\le 100,\sum n^3\le 3\times 10^6$，存在 $path_0$ 的提示。
- 子任务 7（$15$ 分）$n=100,T=3$，共 5 个测试点，输入生成方式是随机一个 $a$ 再求出 $f(a)$ 作为输入。
- 子任务 8（$25$ 分）$n\le 100,\sum n^3\le 3\times 10^6$。
- 子任务 9（$1$ 分）无特殊限制。


---

---
title: "「GMOI R2-T4」电子木鱼"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9201
tag: ['洛谷原创', 'O2优化', '动态树 LCT', '扫描线', '基环树', '洛谷月赛', '分类讨论']
---
# 「GMOI R2-T4」电子木鱼
## 题目背景

运营电子资本，招聘赛博佛祖，积累虚拟功德。

功德无量，随喜赞叹。

111
## 题目描述

给你 $n$，表示一共有 $n$ 位赛博佛祖，编号依次为 $1 \sim n$。

第 $i\ (1 \leq i \leq n)$ 位赛博佛祖可以对应为一个二元组 $\langle S_i, d_i \rangle$，其中 $S$ 在任意时刻均为 $\{1, 2, 3, \dots, m\}$ 的一个子集（可以为空），而 $d_i$ 为 $1 \sim m$ 间的整数。

如果在某一时刻，存在一位赛博佛祖的 $S_i$ 为空集，佛祖会感到很开心而给你加功德。具体地，他会敲响第 $d_i$ 个木鱼，并 **在下一时刻同时** 影响所有的 $n$ 位赛博佛祖（包括他自己）。对第 $j(1 \leq j \leq n)$ 位赛博佛祖，如果 $d_i \in S_j$，那么将从 $S_j$ 内删去 $d_i$；否则向 $S_j$ 内加入 $d_i$。如果有多位赛博佛祖的 $S_i$ 为空集，取编号最小的 $i$ 为你加功德。

现在作为电子资本家的你，想要功德无量。你想知道，最少再请来几位赛博佛祖，可以使得你的这些佛祖们 **源源不断地** 为你加功德。假设这个答案是 $s$（可以为 $0$），那么新的佛祖们的编号依次为 $(n+1) \sim (n+s)$。

**因为你是个资本家，有时候你不想请那么多佛祖**。所以你有许多组询问，对于一组 $l, r$，设 $f(l, r)$ 表示如果初始只有 $[l, r]$ 之间的佛祖，答案将会是多少，注意，每组询问相互独立，上一次添加的佛祖不会延续到以后的询问中。

为了避免太多的输出，你只需要输出： 

$$\sum\limits_{l=1}^n\sum\limits_{r=l}^n f(l,r)\times2^l$$

即可，答案对 $10^9 + 7$ 取模。
## 输入格式

第一行，两个整数 $n, m$。

接下来 $n$ 行，第 $i$ 行首先一个整数描述 $d_i$，接着一个长度为 $m$ 的 $\texttt{01}$ 字符串表示 $S_i$。如果第 $j$ 个字符为 $1$，表示 $j \in S_i$；否则 $j \notin S_i$。
## 输出格式

一行，表示最终答案取模后的值。
## 样例

### 样例输入 #1
```
4 3
1 010
2 001
3 000
3 001
```
### 样例输出 #1
```
52
```
### 样例输入 #2
```
5 4
1 1000
4 0100
1 0000
2 0001
2 0000
```
### 样例输出 #2
```
128
```
## 提示

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 0（10 pts）：$n \leq 10$，$m \leq 5$。
- Subtask 1（10 pts）：$n \leq 300$，$m \leq 10$。
- Subtask 2（15 pts）：$n \leq 1024$，$m \leq 10$。保证每个 $S_i$ 均不同。
- Subtask 3（15 pts）：$n \leq 10^4$。
- Subtask 4（10 pts）：每个 $S_i$ 均在 $2^m$ 种情况中等概率随机生成，$d_i$ 均在 $m$ 种情况中等概率随机生成。
- Subtask 5（40 pts）：无特殊限制。

对于所有数据，保证 $1 \leq n \leq 10^5$，$1 \leq m \leq 17$。


---

---
title: "[POI 2020/2021 R3] Surowa zima"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9404
tag: ['模拟', '贪心', '2020', '平衡树', 'POI（波兰）', '构造', '分类讨论']
---
# [POI 2020/2021 R3] Surowa zima
## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Surowa zima](https://szkopul.edu.pl/problemset/problem/QCCQf92wAoWAOoJ3tHoypvp3/statement/)。

d1t3。
## 题目描述

有一条长 $l$ 米的道路（数轴）。路上有 $n$ 个充电站。每天整条路上（坐标 $[0,l]$）都会落满雪。

有一台机器能扫雪。充一次电可以扫至多 $k$ 米的雪。扫雪是和移动同时进行的，详见样例解释。机器一秒能移动一米，充电不消耗时间。

简单来说，**移动不扫雪不消耗电，需要一秒；移动并扫雪消耗最大电量的 $\bold{\frac1k}$，需要一秒；扫雪必须移动。**

给出每天机器的初始位置，机器初始没电，问每天清除所有雪的最少时间。终点任意。

带修，即充电站可能损坏或修好（第一天之前都是好的），但保证每天都至少有一个好的充电站（所以不会无解）。
## 输入格式

第一行四个整数 $n,l,k,d$。

第二行 $n$ 个整数 $x_1,x_2,\dots,x_n$，表示充电站的位置，保证 $0\leq x_1<x_2<\dots<x_n\leq l$。

接下来 $3d$ 行，描述 $d$ 天的事件：

- 第一行三个整数 $z,u,p$，分别表示昨晚修好的充电站数量，损坏的数量，和机器的初始位置。
- 第二行 $z$ 个整数，表示被修好的充电站编号。
- 第三行 $u$ 个整数，表示损坏的充电站编号。
## 输出格式

$d$ 行，每行一个整数，表示每天的答案。
## 样例

### 样例输入 #1
```
3 5 2 1
2 3 5
0 1 3

2

```
### 样例输出 #1
```
9

```
### 样例输入 #2
```
5 12 1 5
1 3 6 9 11
0 1 1

1
1 1 3
1
2
1 1 6
2
3
1 1 9
3
4
1 1 11
4
5

```
### 样例输出 #2
```
33
33
36
33
33

```
### 样例输入 #3
```
11 100 1 26
0 10 20 30 40 50 60 70 80 90 100
0 5 0

2 4 6 8 10
5 6 4
2 4 6 8 10
1 3 5 7 9 11
6 5 8
1 3 5 7 9 11
2 4 6 8 10
5 6 12
2 4 6 8 10
1 3 5 7 9 11
6 5 16
1 3 5 7 9 11
2 4 6 8 10
5 6 20
2 4 6 8 10
1 3 5 7 9 11
6 5 24
1 3 5 7 9 11
2 4 6 8 10
5 6 28
2 4 6 8 10
1 3 5 7 9 11
6 5 32
1 3 5 7 9 11
2 4 6 8 10
5 6 36
2 4 6 8 10
1 3 5 7 9 11
6 5 40
1 3 5 7 9 11
2 4 6 8 10
5 6 44
2 4 6 8 10
1 3 5 7 9 11
6 5 48
1 3 5 7 9 11
2 4 6 8 10
5 6 52
2 4 6 8 10
1 3 5 7 9 11
6 5 56
1 3 5 7 9 11
2 4 6 8 10
5 6 60
2 4 6 8 10
1 3 5 7 9 11
6 5 64
1 3 5 7 9 11
2 4 6 8 10
5 6 68
2 4 6 8 10
1 3 5 7 9 11
6 5 72
1 3 5 7 9 11
2 4 6 8 10
5 6 76
2 4 6 8 10
1 3 5 7 9 11
6 5 80
1 3 5 7 9 11
2 4 6 8 10
5 6 84
2 4 6 8 10
1 3 5 7 9 11
6 5 88
1 3 5 7 9 11
2 4 6 8 10
5 6 92
2 4 6 8 10
1 3 5 7 9 11
6 5 96
1 3 5 7 9 11
2 4 6 8 10
5 6 100
2 4 6 8 10
1 3 5 7 9 11

```
### 样例输出 #3
```
1090
1096
1098
1092
1094
1100
1094
1092
1098
1096
1090
1096
1098
1092
1094
1100
1094
1092
1098
1096
1090
1096
1098
1092
1094
1100

```
### 样例输入 #4
```
见附件
```
### 样例输出 #4
```
见附件
```
### 样例输入 #5
```
见附件
```
### 样例输出 #5
```
1000000000000000000
2001007996000

```
## 提示

样例解释：$3\rightarrow2_{充电}\Rightarrow0\rightarrow2_{充电}\Rightarrow4\rightarrow5_{充电}\Rightarrow4$。$\rightarrow$ 表示移动，$\Rightarrow$ 表示移动并扫雪。

对于所有数据，$1\leq n\leq 250000$，$1\leq l\leq 10^9$，$1\leq k\leq l$，$1\leq d\leq 250000$，$\sum z,\sum u\leq 500000$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $l\leq 12$，$d\leq 50$ | 10 |
| 2 | $l\leq 500$，$d\leq 50$，$k=1$ | 12 |
| 3 | $l\leq 5000000$，$d\leq 20$ | 8 |
| 4 | $z=u=0$ | 8 |
| 5 | $z,u\leq 100$，$k\leq 50$ | 20 |
| 6 | $k=1$ | 18 |
| 7 |  | 24 |



---

