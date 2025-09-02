---
title: "[集训队互测 2015] Marketing network"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11729
tag: ['2015', '集训队互测', '最短路']
---
# [集训队互测 2015] Marketing network
## 题目描述

“世界充满着各种 if，我们存在着的这个世界也不过是为数众多的 if 的结果中的一个，而未来则更是由于无限的 if 而混沌流动着的世界。”

在某一条世界线中，你可能正在经营一个跨国公司，想想是不是有点激动呢。在那一个世界中，你正被营销网络的设计问题所困扰。

你的跨国公司在 $n$ 个国家设立了销售网点，国家由 $1$ 到 $n$ 编号，这 $n$ 个国家由 $m$ 条双向航线连接。如果把国家看作结点把航线看作边，可以抽象成一个无向图。

你已经在其中的 $S$ 个国家设立了分公司。你会买下一些航线的 VIP 以加速你的商品运输。

无论这条世界线出了什么偏差，你是 OIer 这个事实是不会改变的，所以你对 VIP 航线购买方案有着苛刻的要求：

1. 以任意一个国家作为出发点，都无法只经过 VIP 航线且不经过重复的国家回到出发点。即购买的 VIP 航线形成原图的一个生成森林。
2. 从任意一个分公司出发都可以只经过 VIP 航线到达另一个分公司。

每条航线都有一个权值，表示购买该航线的 VIP 的费用。敏锐的你一定一眼发现了完成目标的最小总花费。但是这样不够任性不够土豪，这势必会影响公司未来的发展。于是机智的你决定求出总费用前 $k$ 小的 VIP 航线购买方案。

两个 VIP 航线购买方案被认为是不同的，当且仅当存在至少一条航线只在其中一个购买方案中被买为 VIP。

“if 只是单纯的 if 罢了。就算有这样一个存在着 good if 的平行世界，人类也不是能简单地跨过世界线，去到那里的。”

但是小小地遐想一下还是很美好的，所以就请你解决这个问题吧。

**简要题意：求出前 $k$ 小的生成森林，要求给定的 $S$ 个点在森林中两两可达。**
## 输入格式

第一行，四个正整数 $n, m, S, k$。

第二行，$S$ 个正整数，表示分公司所在的国家，保证读入的国家编号互不相同。

接下来 $m$ 行，每行三个正整数 $u_i，v_i，c_i$，表示国家 $u_i$ 与 $v_i$ 之间有一条费用为 $c_i$ 的航线。保证 $1 \leq u_i, v_i \leq n$，且 $u_i \neq v_i$。
## 输出格式

输出 $k$ 行，每行一个正整数，第 $i$ 行的正整数表示总费用第 $i$ 小的 VIP 航线购买方案的总费用。
## 样例

### 样例输入 #1
```
6 9 3 6
3 1 5
1 2 1
1 3 2
3 2 2
2 4 5
3 4 5
3 5 2
3 6 2
6 4 4
5 6 1
```
### 样例输出 #1
```
4
5
5
5
5
6
```
## 提示

### 数据范围

除题面样例外的，航线和分公司所在国家均是在 $n, m, S$ 固定的情况下均匀随机生成的。对于所有航线，$c_i$ 是从 $1$ 到 $100$ 的整数中均匀随机选取的。

保证一定存在至少 $k$ 种不同的 VIP 航线购买方案。

（本题洛谷测试点编号较为混乱，下方表格仅作各个测试点范围的大致参考，实际评测中测试点编号与表格无关）

| 测试点编号 | $n$ | $m$ | $S$ | $k$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1\sim 5$ | $=10$ | $=20$ | $=4$ | $=10$ |
| $6\sim 10$ | $=50$ | $=100$ | $=10$ | $=1$ |
| $11\sim 15$ | $=50$ | $=100$ | $=10$ | $=1$ |
| $16\sim 20$ | $=50$ | $=100$ | $=5$ | $=20$ |
| $21\sim 25$ | $=50$ | $=100$ | $=7$ | $=50$ |
| $26\sim 30$ | $=50$ | $=100$ | $=9$ | $=50$ |
| $31\sim 35$ | $=50$ | $=100$ | $=10$ | $=50$ |
| $36\sim 40$ | $=50$ | $=100$ | $=11$ | $=50$ |
| $41\sim 45$ | $=50$ | $=100$ | $=13$ | $=50$ |
| $46\sim 50$ | $=50$ | $=100$ | $=15$ | $=50$ |



---

---
title: "[KOI 2022 Round 2] 外环路"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12703
tag: ['点分治', '2022', '最短路', 'KOI（韩国）']
---
# [KOI 2022 Round 2] 外环路
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

KOI 城市由 $N$ 个十字路口和 $N - 1$ 条双向道路组成，任意两个不同的十字路口之间都可以仅通过道路到达。也就是说，城市的道路网络结构是一棵树。这些道路位于二维平面上，除了端点外互不相交。每条道路都有一个不小于 0 的整数权重，表示通过这条道路所需的时间。

KOI 城市在几十年前还是一个小村庄，随着人口流入和城市规模的迅速扩张，市长为了行政便利，为所有十字路口编号为 1 到 $N$。这个编号系统满足以下性质：

- 1 号十字路口是城市的中心，保证至少连接了两条道路。
- 各个十字路口的编号是以 1 号十字路口为根进行先序遍历（Preorder Traversal）所得到的一种顺序。
- 对于每个十字路口，设其直接相邻（即通过一条道路连接）的十字路口中编号最小的为基准，从该点出发按逆时针方向依次列出其相邻的十字路口编号，这些编号应是递增的。

随着 KOI 城市人口迅速增长，交通拥堵问题日益严重。为了解决这一问题，市长决定通过建设外环道路将交通设施最为薄弱的地区连接起来。

设所有仅连接一条道路的十字路口的编号按升序排列为 $\{v_1, v_2, \dots, v_k\}$，市长将为所有的 $1 \leq i \leq k$ 建设一条连接 $v_i$ 和 $v_{(i \bmod k) + 1}$ 的双向道路。每条道路的权重为不小于 0 的整数 $w_i$，这些权重将作为输入给出。

由于编号系统的特殊性，可以保证这些新增的外环道路在非端点处互不相交。

你打算为 KOI 城市构建一套导航系统。该系统需要回答 $Q$ 个查询，每个查询给出两个十字路口 $u$ 和 $v$，你需要输出从 $u$ 号十字路口到 $v$ 号十字路口所需的最短时间。这个最短时间是指从 $u$ 到 $v$ 所经过路径的所有道路权重之和的最小值。

请你编写程序，在给定城市道路结构和查询的前提下，快速回答所有 $Q$ 个查询。
## 输入格式

第一行包含一个整数 $N$，表示十字路口的数量。

接下来的 $N - 1$ 行，第 $i$ 行包含两个整数 $p_i$ 和 $c_i$，表示存在一条连接 $p_i$ 和 $i+1$ 的双向道路，权重为 $c_i$。

接下来一行包含一个整数 $k$，表示仅连接一条道路的十字路口的数量。

随后一行包含 $k$ 个整数 $w_1, w_2, \dots, w_k$，以空格分隔，其中 $w_i$ 是连接 $v_i$ 和 $v_{(i \bmod k)+1}$ 的新建道路的权重。

接下来一行包含一个整数 $Q$，表示查询数量。

接下来的 $Q$ 行，每行两个整数 $u, v$，表示一次从 $u$ 到 $v$ 的查询。
## 输出格式

共 $Q$ 行，每行一个整数，表示每个查询中 $u$ 到 $v$ 的最短路径长度。

## 样例

### 样例输入 #1
```
4
1 9
1 8
1 0
9 9 9
6
1 2
1 3
1 4
2 3
2 4
3 4
```
### 样例输出 #1
```
9
8
0
9
9
8
```
### 样例输入 #2
```
11
1 9
1 8
3 0
4 7
4 1
3 6
1 0
8 7
8 1
10 6
0 0 0 0 0 0
21
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 11
7 1
8 2
9 3
10 4
11 5
1 6
2 7
3 8
4 9
5 10
6 11
```
### 样例输出 #2
```
7
8
8
7
7
7
0
7
1
7
7
7
1
7
0
7
0
8
1
6
0
```
### 样例输入 #3
```
11
1 9
1 8
3 0
4 7
4 1
3 6
1 0
8 7
8 1
10 6
1000000000000 1000000000000
1000000000000 1000000000000
1000000000000 1000000000000
21
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 11
7 1
8 2
9 3
10 4
11 5
1 6
2 7
3 8
4 9
5 10
6 11
```
### 样例输出 #3
```
9
8
8
15
9
14
0
7
1
7
14
9
15
9
22
9
23
8
15
16
16
```
## 提示

**样例 1 说明**

![](https://cdn.luogu.com.cn/upload/image_hosting/fcuqax1l.png)

上面的地图对应于示例 1。示例 1 满足子任务 2、5、6 的约束条件。

**样例 2、3 说明**

![](https://cdn.luogu.com.cn/upload/image_hosting/5b0ae9y3.png)

上面的地图对应于示例 2 和示例 3。示例 2 的情况下，满足 $w_i = 0$；示例 3 的情况下，满足 $w_i = 10^{12}$。示例 2 满足子任务 4、5、6 的约束条件，示例 3 满足子任务 3、5、6 的约束条件。

请注意，示例 3 中从第 12 行开始的数列：

```
1000000000000 1000000000000 1000000000000 1000000000000 1000000000000 1000000000000
```

在实际中是作为一行输入给出的，但由于篇幅限制，在此被分成了多行显示。（本段内容在正式比赛中并未提供。）

**约束条件**

- $4 \leq N \leq 100\,000$
- $1 \leq p_i \leq i$
- $0 \leq c_i, w_i \leq 10^{12}$
- $1 \leq Q \leq 250\,000$
- $1 \leq u, v \leq N$ 且 $u \ne v$

**子任务**

1. （6 分）所有查询满足 $u = 1$
2. （8 分）对所有 $1 \leq i \leq N - 1$，$p_i = 1$
3. （5 分）对所有 $1 \leq i \leq N - 1$，$c_i \leq 10^6$，并且对所有 $1 \leq i \leq k$，$w_i = 10^{12}$
4. （15 分）对所有 $1 \leq i \leq k$，$w_i = 0$
5. （57 分）不存在连接 4 条及以上道路的十字路口
6. （9 分）无额外约束条件


---

---
title: "[GCJ 2020 #2] Emacs++"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13065
tag: ['2020', '最短路', '最近公共祖先 LCA', 'Google Code Jam']
---
# [GCJ 2020 #2] Emacs++
## 题目描述

In 2016's Distributed Code Jam, we introduced the Lisp++ language for Lisp fans who prefer a higher density of parentheses. Here is a reminder of how the language's syntax works:

A Lisp++ program is a string of balanced parentheses. More formally, a Lisp++ program consists of one of the following. (In this specification, C stands for some program code — not necessarily the same code each time.)

- `()` Literally, just an opening parenthesis and a closing parenthesis. We say that this `(` matches this `)`, and vice versa.
- `(C)` A program within a pair of enclosing parentheses. We say that this `(` matches this `)`, and vice versa.
- `CC` Two programs (not necessarily the same), back to back.

This year, we are pleased to announce Emacs++, a text viewer for Lisp++. Emacs++ displays a Lisp++ program of length K as a single long line with a cursor that you can move around. The cursor is a "block cursor" that is always located on one of the K characters in the program, rather than between characters.

At any point, you can perform one of the following three actions to move the cursor. (i represents the current position of the cursor, counting starting from 1 for the leftmost position.)

- Move the cursor one character to the left (or, if the cursor is already on the leftmost character, does nothing). This takes $L_i$ seconds.
- Move the cursor one character to the right (or, if the cursor is already on the rightmost character, does nothing). This takes $R_i$ seconds.
- Teleport the cursor to the parenthesis matching (as described above) the parenthesis that is the i-th character. This takes $P_i$ seconds.

We think Emacs++ will be simple for power users, but we still need to understand how efficient it is. We have a single Lisp++ program and list of Q queries about that program; each query consists of a start position $S_j$ and an end position $E_j$. To answer the j-th query, you must determine the smallest possible amount of time $N_j$ (in seconds) that it will take to take the cursor from position $S_j$ to position $E_j$, if you make optimal decisions.

Please output the sum of all of those $N_j$ values.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. The first line of a test case contains two integers $K$, which is the length of the Lisp++ program, and $Q$, which is the number of queries.

The second line of a test case contains a string $P$ of $K$ characters, each of which is either ( or ), representing a Lisp++ program (string of balanced parentheses), as described above.

The third, fourth, and fifth lines of a test case each contain $K$ integers. The $i$-th integers in these lines are the values $L_i$, $R_i$, and $P_i$, respectively, that are described above.

The sixth and seventh lines of a test case each contain $Q$ integers. The $j$-th integers in these lines are $S_j$ and $E_j$, respectively, that are described above.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the sum of the $N_j$ values that are described above.
## 样例

### 样例输入 #1
```
1
12 5
(()(((()))))
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
7 4 4 12 5
12 11 10 1 6
```
### 样例输出 #1
```
Case #1: 10
```
## 提示

**Sample Explanation**

In the sample case, which obeys the limits for Test Set 1, all of the time costs are the same ($1$ second per move). The shortest times for the queries are as follows:

1. Move right from $7$ five times to $12$ taking $5$ seconds.
2. Teleport from $4$ to $11$ taking $1$ second.
3. Teleport from $4$ to $11$, then move left to $10$ taking $2$ seconds.
4. Teleport from $12$ to $1$, taking $1$ second.
5. Move right from $5$ to $6$ taking $1$ second.

Thus, the sum of query times is $5+1+2+1+1 = 10$ seconds.

**Limits**

- $1 \leq T \leq 100$.
- $K = 10^5$ and $Q = 10^5$, for at most 9 test cases.
- $2 \leq K \leq 1000$ and $1 \leq Q \leq 1000$, in all other cases.
- length of $P = K$ $P$ is a string of balanced parentheses, as described above.
- $1 \leq S_j \leq K$, for all $j$.
- $1 \leq E_j \leq K$, for all $j$.

**Test Set 1 (12 Pts, Visible Verdict)**

- $L_i = 1$, for all $i$.
- $R_i = 1$, for all $i$.
- $P_i = 1$, for all $i$.

**Test Set 2 (23 Pts, Hidden Verdict)**

- $1 \leq L_i \leq 10^6$, for all $i$.
- $1 \leq R_i \leq 10^6$, for all $i$.
- $1 \leq P_i \leq 10^6$, for all $i$.


---

---
title: "【模板】k 短路 / [SDOI2010] 魔法猪学院"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P2483
tag: ['2010', '各省省选', '山东', 'O2优化', '最短路', '可并堆']
---
# 【模板】k 短路 / [SDOI2010] 魔法猪学院
## 题目背景

注：对于 $k$ 短路问题，A\* 算法的最坏时间复杂度是 $O(nk \log n)$ 的。虽然 A\* 算法可以通过本题原版数据，但可以构造数据，使得 A\* 算法在原题的数据范围内无法通过。事实上，存在使用可持久化可并堆的算法可以做到在 $O((n+m) \log n + k \log k)$ 的时间复杂度解决 $k$ 短路问题。详情见 [OI-Wiki](https://oi-wiki.org/graph/kth-path/)。
## 题目描述

iPig 在假期来到了传说中的魔法猪学院，开始为期两个月的魔法猪训练。经过了一周理论知识和一周基本魔法的学习之后，iPig 对猪世界的世界本原有了很多的了解：众所周知，世界是由元素构成的；元素与元素之间可以互相转换；能量守恒$\ldots$。


iPig 今天就在进行一个麻烦的测验。iPig 在之前的学习中已经知道了很多种元素，并学会了可以转化这些元素的魔法，每种魔法需要消耗 iPig 一定的能量。作为 PKU 的顶尖学猪，让 iPig 用最少的能量完成从一种元素转换到另一种元素$\ldots$等等，iPig 的魔法导猪可没这么笨！这一次，他给 iPig 带来了很多 $1$ 号元素的样本，要求 iPig 使用学习过的魔法将它们一个个转化为 $N$ 号元素，为了增加难度，要求每份样本的转换过程都不相同。这个看似困难的任务实际上对 iPig 并没有挑战性，因为，他有坚实的后盾$\ldots$现在的你呀！


注意，两个元素之间的转化可能有多种魔法，转化是单向的。转化的过程中，可以转化到一个元素（包括开始元素）多次，但是一但转化到目标元素，则一份样本的转化过程结束。iPig 的总能量是有限的，所以最多能够转换的样本数一定是一个有限数。具体请参看样例。
## 输入格式

第一行三个数 $N, M, E$，表示 iPig 知道的元素个数（元素从 $1$ 到 $N$ 编号），iPig 已经学会的魔法个数和 iPig 的总能量。

后跟 $M$ 行每行三个数 $s_i, t_i, e_i$ 表示 iPig 知道一种魔法，消耗 $e_i$ 的能量将元素 $s_i$ 变换到元素 $t_i$。
## 输出格式

一行一个数，表示最多可以完成的方式数。输入数据保证至少可以完成一种方式。

## 样例

### 样例输入 #1
```
4 6 14.9
1 2 1.5
2 1 1.5
1 3 3
2 3 1.5
3 4 1.5
1 4 1.5

```
### 样例输出 #1
```
3
```
## 提示

有意义的转换方式共 $4$ 种：

$1\to 4$，消耗能量 $1.5$。

$1\to 2\to 1\to 4$，消耗能量 $4.5$。

$1\to3\to4$，消耗能量 $4.5$。

$1\to2\to3\to4$，消耗能量 $4.5$。

显然最多只能完成其中的 $3$ 种转换方式（选第一种方式，后三种方式任选两个），即最多可以转换 $3$ 份样本。

如果将 $E=14.9$ 改为 $E=15$，则可以完成以上全部方式，答案变为 $4$。

### 数据规模

占总分不小于 $10\%$ 的数据满足 $N \leq 6,M \leq 15$。

占总分不小于 $20\%$ 的数据满足 $N \leq 100,M \leq 300,E\leq100$ 且 $E$ 和所有的 $e_i$ 均为整数（可以直接作为整型数字读入）。

所有数据满足 $2 \leq N \leq 5000$，$1 \leq M \leq 200000$，$1 \leq E \leq 10 ^ 7$，$1 \leq ei\leq E$，$E$ 和所有的 $e_i$ 为实数。

### 数据更新日志

- 2010/xx/xx：原版数据；
- 2018/03/02：@[kczno1](/user/9168) 添加了 [一组数据](/discuss/35616)；
- 2018/04/20：@[X_o_r](/user/25188) 添加了 [一组数据](/discuss/40205)；
- 2021/01/08：@[LeavingZ](/user/215697) 添加了 [两组数据](/discuss/291028)。


---

---
title: "[HNOI2014] 道路堵塞"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3238
tag: ['2014', '各省省选', '平衡树', '湖南', '最短路']
---
# [HNOI2014] 道路堵塞
## 题目背景

### 本题可能不存在正确解法，题解均已被 hack。
## 题目描述

A 国有 $N$ 座城市，依次标为 $1$ 到 $N$。同时，在这 $N$ 座城市间有 $M$ 条单向道路，每条道路的长度是一个正整数。现在，A 国交通部指定了一条从城市 $1$ 到城市 $N$ 的路径，并且保证这条路径的长度是所有从城市 $1$ 到城市 $N$ 的路径中最短的。不幸的是，因为从城市 $1$ 到城市 $N$ 旅行的人越来越多，这条由交通部指定的路径经常发生堵塞。现在 A 国想知道，这条路径中的任意一条道路无法通行时，由城市 $1$ 到 $N$ 的最短路径长度是多少。
## 输入格式

输入文件第一行是三个用空格分开的正整数 $N$、$M$ 和 $L$，分别表示城市数目、单向道路数目和交通部指定的最短路径包含多少条道路。按下来 $M$ 行，每行三个用空格分开的整数 $a$、$b$ 和 $c$，表示存在一条由城市 $a$ 到城市 $b$ 的长度为 $c$ 的单向道路。这 $M$ 行的行号也是对应道路的编号，即其中第 $1$ 行对应的道路编号为 $1$，第 $2$ 行对应的道路编号为 $2$，......，第 $M$ 行对应的道路编号为 $M$。最后一行为 $L$ 个用空格分开的整数 $\operatorname{sp}(1),\ldots,\operatorname{sp}(L)$，依次表示从城市 $1$ 到城市 $N$ 的由交通部指定的最短路径上的道路的编号。
## 输出格式

输出文件包含 $L$ 行，每行为一个整数，第 $i$ 行（$i = 1,2,\ldots,L$）的整数表示删去编号为 $\operatorname{sp}(i)$ 的道路后从城市 $1$ 到城市 $N$ 的最短路径长度。如果去掉后没有从城市 $1$ 到城市 $N$ 的路径，则输出 $-1$。
## 样例

### 样例输入 #1
```
4 5 2
1 2 2
1 3 2
3 4 4
3 2 1
2 4 3
1 5
```
### 样例输出 #1
```
6

6
```
## 提示

$100\%$ 的数据满足 $2 < N < 100000$，$1 < M < 200000$，$c \in [0, 10000] \cap \mathbb{Z}$。

数据已加强 By Vfleaking。

2023.4.8 添加两组 hack 数据。


---

---
title: "[AH2017/HNOI2017] 队长快跑"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3725
tag: ['2017', '各省省选', '安徽', '湖南', 'Special Judge', '排序', '最短路', '队列']
---
# [AH2017/HNOI2017] 队长快跑
## 题目描述

众所周知，在 P 国外不远处盘踞着巨龙大 Y。传说中，在远古时代，巨龙大 Y 将 P 国的镇国之宝窃走并藏在了其巢穴中，这吸引着整个 P 国的所有冒险家前去夺回，尤其是皇家卫士队的队长小 W。在 P 国量子科技实验室的帮助下，队长小 W 通过量子传输进入了巨龙大 Y 的藏宝室，并成功夺回了镇国之宝。但此时巨龙布下的攻击性防壁启动，将小 W 困在了美杜莎的迷宫当中。

被困在迷宫 $(0,0)$ 处的队长小 W 快速观察了美杜莎的迷宫的构造，发现迷宫的出口位于 $(p,q)$ 处。巨龙大 Y 在迷宫当中布置了 $n$ 火焰吐息机关，每个机关可以用三个参数 $(x,y,\theta)$ 表示，分别指明机关位于平面的坐标 $(x,y)$，以及火焰吐息的方向相对于 $x$ 正方向的倾角 $\theta$。巨龙强大的力量使得火焰吐息有无穷长，且队长小  W 不能通过被火焰吐息覆盖的射线（注意，机关所处的坐标若没有被其他火焰吐息覆盖，则是可以通过的）。同时，迷宫在沿 $x$ 负方向无穷远的地方放置了美杜莎之眼，使得队长小 W 必须倾向于向 $x$ 正方向行动（即队长小 W 的移动方向在 $x$ 正方向上的投影必须为正，不能是负数或零），否则队长小 W 将被瞬间石化而无法逃离。

心急如焚的队长小 W 需要趁着巨龙大 Y 还没将其抓住前逃离美杜莎的迷宫，所以他立马向 P 国智囊团求助，作为智囊团团长的你，一定可以帮队长小 W 找出安全逃至迷宫出口的最短道路。

## 输入格式

第一行为三个整数 $n,p,q$ 分别表示火焰吐息机关总数以及出口坐标。

接下来 $n$ 行，每行两个整数与一个实数 $(x,y,\theta)$ 分别表示机关所处的坐标以及火焰吐息的关于 $x$ 正方向的倾角。

## 输出格式

输出文件仅包含一行一个小数，表示最短道路的长度。当你的答案和标准答案的相对误差不超过 $10^{-8}$ 时（ 即 $\frac{|a-o|}{a}\leq10^{-8}$ 时， 其中 $a$ 是标准答案，$o$ 是输出）认为你的答案正确。

## 样例

### 样例输入 #1
```
7 20 -5
4 3 -2.875
5 7 -1.314
10 -2 0.666
16 1 -1.571
16 1 1.571
23 -3 -2.130
14 -5 3.073
```
### 样例输出 #1
```
33.3380422500
```
### 样例输入 #2
```
7 20 0
5 2 1.155
5 2 1.987
5 2 -1.571
11 -4 1.765
11 -4 1.377
15 -4 1.765
15 -4 1.377
```
### 样例输出 #2
```
24.2735704188
```
## 提示

【样例解释】

 ![](https://cdn.luogu.com.cn/upload/pic/5107.png) 

$30\%$ 的数据满足 $n\leq 300$；

$60\%$ 的数据满足 $n\leq 2000$；

$80\%$ 的数据满足 $n\leq 10^5$；

$100\%$ 的数据满足： $0 \leq n,p, |q|, |x|, |y| \leq 10^6； \theta \in [−\pi, \pi]$。
数据保证至少存在一条合法路径，且起点和终点均不会被火焰路径覆盖。



---

---
title: "[BJWC2018] 餐巾计划问题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4480
tag: ['2018', '网络流', '北京', '最短路', '队列']
---
# [BJWC2018] 餐巾计划问题
## 题目背景

**本题和网络流24题中的餐巾计划不为重题**
## 题目描述

一个餐厅在相继的 $n$ 天里，每天需用的餐巾数不尽相同。假设第 $i$ 天 $(i=1, 2, ..., n)$ 需要 $r_i$ 块餐巾。餐厅可以在任意时刻购买新的餐巾，每块餐巾的费用为 $p$ 。使用过的旧餐巾，则需要经过清洗才能重新使用。把一块旧餐巾送到清洗店A，需要等待 $m_1$ 天后才能拿到新餐巾，其费用为 $c_1$ ；把一块旧餐巾送到清洗店B，需要等待 $m_2$ 天后才能拿到新餐巾，其费用为 $c_2$ 。例如，将一块第 $k$ 天使用过的餐巾送到清洗店A清洗，则可以在第 $k+m_1$ 天使用。

请为餐厅合理地安排好 $n$ 天中餐巾使用计划，使总的花费最小。
## 输入格式

第一行，包含六个个正整数  $n, m_1, m_2, c_1, c_2, p$ 。

接下来输入 $n$ 行，每行包含一个正整数 $r_i$ 。
## 输出格式

输出一行，包含一个正整数，表示最小的总花费。
## 样例

### 样例输入 #1
```
4 1 2 2 1 3
8
2
1
6
```
### 样例输出 #1
```
35
```
## 提示

**【样例说明】**

第 1 天：买8块餐巾，花费24。送2块餐巾去清洗店A，6块餐巾去清洗店B。

第 2 天：取回2块清洗店A的餐巾，花费4。送1块餐巾去清洗店B。

第 3 天：取回6块清洗店B的餐巾，花费6。

第 4 天：取回1块清洗店B的餐巾，花费1。这样就用了最少的钱。


**【数据规模和约定】**

对于30%的数据，$1 \leq n \leq 5$ ，$1 \leq c_1, c_2, p \leq 5$ ， $1 \leq r_i \leq 5$ 。

对于50%的数据，$1 \leq n \leq 100$ ，$1 \leq r_i \leq 50$ 。

对于70%的数据，$1 \leq n \leq 5000$ 。

对于100%的数据，$1 \leq n \leq 200000$ ， $1 \leq m_1, m_2 \leq n$ ， $1 \leq c_1, c_2, p \leq 100$ ， $1 \leq r_i \leq 100$ 。


---

---
title: "[COCI 2017/2018 #4] Ceste"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4524
tag: ['2017', '排序', '最短路', 'COCI（克罗地亚）']
---
# [COCI 2017/2018 #4] Ceste
## 题目背景

**原题时限2.5s**
## 题目描述

There’s a country with N cities and M bidirectional roads. Driving on road i takes $T_i$ minutes,
and costs $C_i$ kunas (Croatian currency).

To make the arrival to the holiday destination as pleasant as possible, you want to make it
as fast and as cheap as possible. More specifically, you are in city 1 and want to minimize
the product of total money spent and total time spent (overall, with all roads you drove on) in
getting to a city from city 1. For each city (except city 1), output the required minimal product
or -1 if city 1 and that city aren’t connected.

## 输入格式

The first line of input contains numbers N (1 ≤ N ≤ 2000), the number of cities, and M (1 ≤ M
≤ 2000), the number of roads.

Each of the following M lines contains four numbers,$A_i,B_i,T_i,C_i,(1≤A_i,B_i≤N,1≤T_i,C_i≤2000)$ that denote there is a road connecting cities $A_i$ and $B_i$
, that it takes $T_i$ minutes to drive
on it, and it costs $C_i$ kunas.

It is possible that multiple roads exist between two cities, but there will never be a road that
connects a city with itself.

## 输出格式

You must output N - 1 lines. In the $i^{th}$
line, output the required minimal product in order to get
to city (i + 1), or -1 if cities 1 and (i + 1) aren’t connected.
## 样例

### 样例输入 #1
```
4 4
1 2 2 4
3 4 4 1
4 2 1 1
1 3 3 1

```
### 样例输出 #1
```
8
3
14
```
### 样例输入 #2
```
4 5
1 2 1 7
3 1 3 2
2 4 5 2
2 3 1 1
2 4 7 1
```
### 样例输出 #2
```
7
6
44
```
### 样例输入 #3
```
3 2
1 2 2 5
2 1 3 3
```
### 样例输出 #3
```
9
-1
```
## 提示

In test cases worth 40% of total points, it will hold $1 ≤ N, M, T_i, C_i ≤ 100$.

**Clarification of the second test case:**

In order to get to city 2, you need to drive on road 1, for that it takes 1 minute and 7 kunas, so the
required product is 7.

In order to get to city 3, you need to drive on road 2, for that it takes 3 minutes and 2 kunas, so the
required product is 6.

In order to get to city 4, you need to drive on roads 2, 4, 5, in that order, and for that it takes a total of
11 minutes and 4 kunas, so the required product is 44.
## 题目翻译

题目描述：

有一个无向图，给定 $n$ 个顶点和 $m$ 条边，第 $i$ 条边连接 $A_i$ 和 $B_i$ 两个点且有两个代价 $T_i$ 和 $C_i$。

从第 $i$ 个顶点经过一些边到第 $j$ 个顶点花费的代价为这些边的 $T$ 之和乘以 $C$ 之和。

问题是，对于每一个 $k(2 \le k \le n)$，求从1号点出发到 $k$ 号点花费的最小代价。

输入格式：

第一行两个整数 $n$ 和 $m$。

接下来 $m$ 行，每行包含4个正整数 $A_i,B_i,T_i,C_i$，表示一条连接 $A_i,B_i$ 的路,代价为 $T_i,C_i$。

输出格式：

输出 $n-1$ 行，每行一个正整数，第 $i$ 行的正整数表示从城市1到城市 $i+1$ 的最小代价。 

说明/提示：
对于 $40\%$ 的数据，满足 $1 \le n,m,T_i,C_i \le 100$。

对于 $100\%$ 的数据，满足 $1 \le n,m,T_i,C_i \le 2000,1 \le A_i,B_i \le n$。

样例2解释：

为了到达城市2，我们选择第一条道路，花费1T与7C，代价为7。

为了到达城市3，我们选择第二条道路，花费3T与2C，代价为6。

为了到达城市4，我们选择道路2，4，5，花费11T与4C，代价为44。


---

---
title: "[ZJOI2011] 营救皮卡丘"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4542
tag: ['2011', '各省省选', '浙江', '图论建模', '最短路', '费用流']
---
# [ZJOI2011] 营救皮卡丘
## 题目描述

皮卡丘被火箭队用邪恶的计谋抢走了！这三个坏家伙还给小智留下了赤果果的挑衅！为了皮卡丘，也为了正义，小智和他的朋友们义不容辞的踏上了营救皮卡丘的道路。

火箭队一共有$N$个据点，据点之间存在$M$条双向道路。据点分别从$1$到$N$标号。小智一行$K$人从真新镇出发，营救被困在$N$号据点的皮卡丘。为了方便起见，我们将真新镇视为$0$号据点，一开始$K$个人都在$0$号点。

由于火箭队的重重布防，要想摧毁$K$号据点，必须按照顺序先摧毁$1$到$K-1$号据点，并且，如果$K-1$号据点没有被摧毁，由于防御的连锁性，小智一行任何一个人进入据点$K$，都会被发现，并产生严重后果。因此，在$K-1$号据点被摧毁之前，任何人是不能够经过$K$号据点的。

为了简化问题，我们忽略战斗环节，小智一行任何一个人经过$K$号据点即认为$K$号据点被摧毁。被摧毁的据点依然是可以被经过的。

$K$个人是可以分头行动的，只要有任何一个人在$K-1$号据点被摧毁之后，经过$K$号据点，$K$号据点就被摧毁了。显然的，只要$N$号据点被摧毁，皮卡丘就得救了。

野外的道路是不安全的，因此小智一行希望在摧毁$N$号据点救出皮卡丘的同时，使得$K$个人所经过的道路的长度总和最少。

请你帮助小智设计一个最佳的营救方案吧！
## 输入格式

第一行包含三个正整数$N,M,K$。表示一共有$N+1$个据点，分别从$0$到$N$编号，以及$M$条无向边。一开始小智一行共$K$个人均位于$0$号点。 

接下来$M$行，每行三个非负整数，第i行的整数为$A_i$，$B_i$，$L_i$。表示存在一条从$A_i$号据点到$B_i$号据点的长度为$L_i$的道路。
## 输出格式

仅包含一个整数$S$，为营救皮卡丘所需要经过的最小的道路总和。
## 样例

### 样例输入 #1
```
3 4 2
0 1 1
1 2 1
2 3 100
0 3 1
```
### 样例输出 #1
```
3
```
## 提示

【样例说明】

小智和小霞一起前去营救皮卡丘。在最优方案中，小智先从真新镇前往1号点，接着前往2号据点。当小智成功摧毁2号据点之后，小霞从真新镇出发直接前往3号据点，救出皮卡丘。

对于100%的数据满足$N ≤ 150, M ≤ 20 000, 1 ≤ K ≤ 10, L_i ≤ 10 000$, 保证小智一行一定能够救出皮卡丘。

至于为什么$K ≤ 10$，你可以认为最终在小智的号召下，小智，小霞，小刚，小建，小遥，小胜，小光，艾莉丝，天桐，还有去日本旅游的黑猫警长，一同前去大战火箭队。


---

---
title: "封锁"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6158
tag: ['2020', '网络流', 'O2优化', '最短路', '最小割', '凸包', '叉积']
---
# 封锁
## 题目背景

震惊！zbw 竟从 B 城监狱逃出！

作为 B 城的警察局长，你必须在 zbw 逃出你的管辖范围之前抓住他。
## 题目描述

B 城可视为一个 $n \times n$ 的方阵，其中监狱在 $(1,1)$，B 城唯一出城的出口在 $(n,n)$。每两个相邻的点（横坐标之差的绝对值 $+$ 纵坐标之间的绝对值 $=1$）之间都有一条**无向的**道路（没有斜着的道路）。你需要在一些道路上部下防守，使得无论 zbw 怎么走，都至少会经过其中的一条道路。

在一条 $(i,j)$ 到 $(i,j+1)$ 的道路上部下防守的花费是 $r_{i,j}$，在一条 $(i,j)$ 到 $(i+1,j)$ 的道路上部下防守的花费是 $d_{i,j}$，同时，在道路上部下防守会对人民的生活造成影响，在一条 $(i,j)$ 到 $(i,j+1)$ 的道路上部下防守对人民的生活造成的影响是 $x_{i,j}$，在一条 $(i,j)$ 到 $(i+1,j)$ 的道路上部下防守对人民的生活造成的影响是 $y_{i,j}$。

定义总花费为 $w$ ，总影响为 $e$ ，作为一名优秀的警察局长，你需要最小化 $w \times e$。 
## 输入格式

第一行一个整数 $n$。

之后的 $n \times (n-1)$ 行，第 $i$ 行两个整数 $r_{i/n+1,(i-1)\bmod n+1}$， $x_{i/n+1,(i-1)\bmod n+1}$。

之后的 $n \times (n-1)$ 行，第 $i$ 行两个整数 $d_{i/n+1,(i-1)\bmod n+1}$ ，$y_{i/n+1,(i-1)\bmod n+1}$。

也就是说，先从上往下给从左往右给出竖边的信息，再从上往下给从左往右给出横边的信息。

如果不理解请见样例解释。

## 输出格式

一行一个整数，表示 $w \times e$ 的最小值。
## 样例

### 样例输入 #1
```
3
8 3
5 2
1 1
4 2
1 2
7 5
7 2
6 1
5 4
2 3
1 4 
4 3
```
### 样例输出 #1
```
49
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/bjd62iba.png)

如图，左上角为 $(1,1)$，右下角为 $(n,n)$，
其中蓝色数字表示 $r$,
红色数字表示 $x$,
黄色数字表示 $d$,
绿色数字表示 $y$。

最优方案为防守三条边，分别为：

$(2,2)-(2,3),(3,1)-(3,2),(3,2)-(3,3)$

三条边的边权分别是 $2,3$---$1,1$ ---$4,3$

答案为 $(1+2+4)\times (1+3+3)=49$


可以发现没有更优的做法。

**本题采用捆绑测试。**

|  Subtasks| $n$ |特殊性质  |分数
| :----------: | :----------: | :----------: |:----------: |
|  Subtask1| $n=2$ |无  |$5$
|  Subtask2| $n\leq400$ |数据随机  |$15$
|  Subtask3| $n\leq10$ |  无|$15$
|  Subtask4| $n\leq50$ | 无 |$30$
|  Subtask5| $n\leq400$ | 无 |$35$

对于所有数据 $1 \leq n \leq 400$，$0 \leq r_{i,j}, d_{i,j},x_{i,j} ,y_{i,j}  \leq 10^3$。

数据于2020/3/4加强，卡掉部分复杂度错误的做法。


---

---
title: "[CEOI 2014] The Wall"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6545
tag: ['2014', 'O2优化', 'CEOI（中欧）', '最短路']
---
# [CEOI 2014] The Wall
## 题目背景

CEOI2014 Day2 T3，译者：小粉兔
## 题目描述

Rectos 岛经常遭受洪水的泛滥和海盗的侵扰，所以 Rectos 的国王想要建造一堵城墙以保护岛上所有的村庄。

Rectos 是一个矩形岛屿，所以城墙的设计师将岛屿看作一个正方形网格。每个村庄都位于其中的某个方格中，并且首都村庄位于整座岛的西北角，也就是最左上角的方格中。

必须保证从外部（也就是整个网格的外部）在不越过城墙的条件下，是到达不了任何一个村庄的。

设计师计划城墙将只沿着网格线建造，更具体地说是按照如下方法：他将第一段城墙置于最左上角延伸出的两条网格线之一上，并且下一段城墙总是和上一段城墙首尾相连，不断重复这一过程直到又一次回到最左上角为止。这一过程可能会导致一段网格线上放置了大于一段的城墙，总而言之，城墙是沿着网格线上的一条连续闭曲线建造的。

地势测量表明，在每一段网格线上建造一段城墙都需要一定的花费。建造城墙的总花费就是建造每一段城墙的花费之和。如果在某一段网格线上建造了 $t$ 段城墙，则花费也要重复计算 $t$ 次。

国王想要花费尽量少的钱建好城墙。请你帮助国王，编写一个程序，给出村庄的位置以及每一段网格线上的建造花费，计算建造城墙所需最小的花费。
## 输入格式

第一行两个正整数 $n, m$，分别表示网格的行数和列数。  
接下来 $n$ 行，每行 $m$ 个数，每个数为 $0$ 或 $1$，若为 $0$ 则表示该格没有村庄，若为 $1$ 则表示该格有村庄，保证第 $1$ 行的第 $1$ 个数一定为 $1$。  
接下来 $n$ 行，每行 $m + 1$ 个非负整数，依次表示每一段竖直的网格线上的建造花费。  
接下来 $n + 1$ 行，每行 $m$ 个非负整数，依次表示每一段水平的网格线上的建造花费。
## 输出格式

输出一行一个数表示建造城墙的最小花费。
## 样例

### 样例输入 #1
```
3 3
1 0 0
1 0 0
0 0 1
1 4 9 4
1 6 6 6
1 2 2 9
1 1 1
4 4 4
2 4 2
6 6 6
```
### 样例输出 #1
```
38
```
### 样例输入 #2
```
3 3
1 0 1
0 0 0
0 1 0
2 1 1 3
5 6 1 1
2 1 1 3
2 1 1
3 4 1
4 1 1
5 1 2
```
### 样例输出 #2
```
22
```
## 提示

**【样例 #1 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/njtyjnbp.png)

**【样例 #2 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/568orkwb.png)

**【数据范围与提示】**

对于所有数据，保证 $1 \le n, m \le 400$，对于所有的建造花费 $v$，有 $1 \le v \le {10}^9$。

| 子任务编号 | 分值 | 特殊限制 |
| :-: | :-: | :-: |
| $1$ | $30$ | $n, m \le 40$ 且村庄的数量不超过 $10$ |
| $2$ | $30$ | $n, m \le 40$ |
| $3$ | $40$ | 无特殊限制 |


---

---
title: "[JOISC 2020] 治療計画"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7214
tag: ['2020', '线段树', '最短路', 'JOI（日本）']
---
# [JOISC 2020] 治療計画
## 题目背景

因为本题数据点过多，另外 $3$ 组数据请在 [这里](https://www.luogu.com.cn/problem/U127700) 测试。

JOI 村庄的村民们最近发生了 COVILLAGE-19 疫情！
## 题目描述

JOI 村庄有 $N$ 个房屋，编号为 $1$ 到 $N$，每个房屋住有一个村民，第 $i$ 个房屋居住编号为村民 $i$。

现在，这 $N$ 个房屋里的村民全部感染 COVILLAGE-19 病毒，有 $M$ 个治疗方案被提出，第 $i$ 个治疗方案描述为，在第 $T_i$ 天的晚上，编号在 $[L_i,R_i]$ 区间内的村民被治愈。

COVILLAGE-19 病毒还会继续传播，在某天早上，如果村民 $i$ 被感染，那么村民 $i+1$ 和村民 $i-1$ 也会被感染，因为病毒威力巨大，所以被治愈的村民有可能再次被感染。

您是 JOI 国的总理，您要选择一些方案使得 JOI 村庄所有村民全部被治愈，一天可以进行很多方案。

第 $i$ 个方案要花费 $C_i$，求最小花费。
## 输入格式

第一行两个整数 $N,M$ 代表村民数和方案数。  
接下来 $M$ 行每行四个整数 $T_i,L_i,R_i,C_i$ 代表一个治疗方案。
## 输出格式

一行一个整数代表最小花费。         
如果无法全部治愈，输出 $-1$。
## 样例

### 样例输入 #1
```
10 5
2 5 10 3
1 1 6 5
5 2 8 3
7 6 10 4
4 1 3 1
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
10 5
2 6 10 3
1 1 5 5
5 2 7 3
8 6 10 4
4 1 3 1
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
10 5
1 5 10 4
1 1 6 5
1 4 8 3
1 6 10 3
1 1 3 1
```
### 样例输出 #3
```
7
```
## 提示

#### 样例 1 解释

执行过程如下（红色为被病毒感染，绿色为治愈）：

1. 在第二天晚上，执行第 $1$ 个方案，情况如下：

$$\color{Red}1\ 2\ 3\ 4\color{Green}\ 5\ 6\ 7\ 8\ 9\ 10$$

2. 在第三天早上，村民 $5$ 被感染，情况如下：

$$\color{Red}1\ 2\ 3\ 4\ 5\color{Green}\ 6\ 7\ 8\ 9\ 10$$

3. 在第四天早上，村民 $6$ 被感染，情况如下：

$$\color{Red}1\ 2\ 3\ 4\ 5\ 6\color{Green}\ 7\ 8\ 9\ 10$$

4. 在第四天晚上，执行第 $5$ 个方案，情况如下：

$$\color{Green}1\ 2\ 3\color{Red}\ 4\ 5\ 6\color{Green}\ 7\ 8\ 9\ 10$$

5. 第五天早上，村民 $3,7$ 被感染，情况如下：

$$\color{Green}1\ 2\color{Red}\ 3\ 4\ 5\ 6\ 7\color{Green}\ 8\ 9\ 10$$

6. 在第五天晚上，执行第 $3$ 个方案，情况如下：

$$\color{Green}1\ 2\ 3\ 4\ 5\ 6\ 7\ 8\ 9\ 10$$

全部治愈，这三个方案花费为 $7$，为最小花费。

#### 样例 2 解释

无法使得所有村民全部治愈。

#### 子任务

|子任务|特殊性质|分数|
|:-:|:-:|:-:|
|$1$|$T_i=1$|$4$|
|$2$|$M \le 16$|$5$|
|$3$|$M \le 5000$|$30$|
|$4$|无|$61$|

对于 $100\%$ 的数据，$1 \le N,T_i,C_i \le 10^9$，$1 \le M \le 10^5$，$1 \le L_i \le R_i \le N$。

#### 说明

翻译自 [第１９回日本情報オリンピック　春季トレーニング合宿](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/index.html) [Day4 C 治療計画](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/day4/capital_city.pdf)。


---

---
title: "「Wdoi-1.5」旅人 1977"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8117
tag: ['洛谷原创', 'O2优化', '最短路', '洛谷月赛', '状压 DP']
---
# 「Wdoi-1.5」旅人 1977
## 题目背景

深邃的星空中划出了一道灿烂的弧线，而后又同这广袤境界溶为一体，二十世纪的旅行者，承载着期待与不安向着外太空飞去。这是一份来自一个遥远的小小世界的礼物。上面记载着我们的声音、我们的科学、我们的影像、我们的音乐、我们的思想和感情。我们正努力生活过我们的时代，进入你们的时代。或许人类将失去对它的联系，它也将像一个漂流瓶一样，向着宇宙深处孤独的走下去，直到被「另一个人」所捡起。而它为我们留下的最后一张「自拍」，也只是一个 $0.12$ 像素大的、淡蓝色的光点 —— 这是我们迄今所知的唯一家园。

$\kern{80pt}$![](https://cdn.luogu.com.cn/upload/image_hosting/qbelj85l.png)  
$$\\[-1em]\scriptscriptstyle\text{暗淡蓝点，旅行者 1 号，1990年 2 月 14 日}$$
「已经分不清现实与梦境了呢。」  
「或许，梦与现之间的境界，本就没有那么明晰。」

……

「真是的，莲子你不是自称亲近星光与月亮的嘛，怎么也不抬头看看。」

正欲向笔记本上添加几行，借以目视的月光陡然暗淡。眼前垂落的金色长发挡住了我的视线。轻咳了一声，抬起手在面前挥舞，把他们从视野中赶走，我转头看着后背。
眼前戴着白色帽子的少女便是我的同伴梅莉。我常常打趣她有着奇异的眼睛，可以看到我们所看不到的「境界」。尽管我自己的眼睛也十分特殊——我有着通过星光与月亮就知道我们现处何时何地的能力。忘了说了，我们是学生秘密社团『秘封俱乐部』，专门探寻科学世纪下的隐藏结界。  
在这个夏夜，我本着履行对她承诺的想法，来到野外，观察天体的运行。

「在想什么呢？」  
这个问题不好回答呢。不过，既然今天和梅莉约好出来观赏星空，那么，思路被引向人们曾经的探索和求知，便是十分自然的了。  
「唔，我在想，我们现今，科学世纪的起源。」  
「嗯？莲子你不是研究物理的吗，怎么突然思考其这种问题了？」  
梅莉把头朝右侧一歪，我指指天空，她随即坐在了一旁，把目光投向灿烂的星海。  
「唔，我在想，我们现今，科学世纪的起源。还记得我和你说过的那两位旅人吗？」  
「旅行者一号与旅行者二号？」  
「没错。直到如今都没有人为任何深空计划取名为旅行者。带着如此诗意而感性名称的它们代表的是人们对未来的期许与对真理的渴望。面对未知与迷茫，义无反顾冲向了星海。」 

梅莉站了起来，举起了双筒望远镜。她的身影在暗淡而幽静的夜色中来回移动，皎白得似有彩色光晕的月光从穹顶透过树叶与树枝的缝隙在她身上落下光斑，看着让人心醉。  

超新星爆发是恒星生命的终点，也是新生恒星生命的起点。谁能说科学已经到了尽头，无法解释的事物不存在呢？科学的核心在于那些被视为空花阳焰，藏在迷雾中的东西，而绝非那些狂妄自大的老头们所说，科学是我们掌握的一切已知。  
对我们而言，这是不言而喻的。我们追随那位初代社长的脚步，探寻遍布四处的结界，寻求隐藏在未知背后真理的一角，正是出于这样的信念。

晷刻渐移，点点星尘围绕着北极星作着圆周运动。仔细看的话，北极星也在微微运动。在我的视线前方，梅莉兴奋地对着从英仙座辐射而出，偶尔划过天穹的流星发出惊叹。我不禁思索起来，现在勾陈一作为最接近北天极的恒星行使着为旅人指点方向的责任，但在永恒的运动中，永远会有新的谜题，新的未知，新的探索等着我们去发现。  

物如此，事犹是，人亦然。前路永远有着未知的事物等着我们去探索。如果解明了所有的秘密，之后就会什么都不剩。知晓万物什么的，只不过是空空如也的虚无罢了。未知，才是驱动人类的原动力 $\scriptscriptstyle{}^{[{\color{grey}{1}}]}$。我们希冀着如同那两位先行者一般，作为开拓者，唤起根植于人们心中对未知的好奇与探索精神，并将它薪火相传。  
身虽位于苍穹一粟，心亦向往若尘繁星。  
身旁的梅莉靠在一棵树下，已经发出规律的鼾声，身体规律地微微起伏着。我伸手拨开她的手掌，撩开她垂下的头发，拿出她的笔记本。
>从夜晚走向清晨。  
从清晨走向夜晚。  
从现实走向梦境。  
从梦境走向现实。  
终有一天，我们会在梦中，邂逅那片未经观测的星空。$\scriptscriptstyle{}^{[{\color{grey}{2}}]}$

$\scriptscriptstyle{[1],[2]}\text{：引用自 }$ [here](https://bbs.nyasama.com/forum.php?mod=viewthread&tid=308054&page=2)
## 题目描述

深邃的星空可以被视作一张有向图，图上的节点就是点点恒星。点无点权，边有边权。图的点数为 $n$，边数为 $m$，图可能有重边自环。但保证至少有一条路径可以从 $s$ 走到 $t$（$s$、$t$ 在输入中给定）。第 $i$ 条有向边起点为 $u_i$，终点为 $v_i$，它的权值用一个有序三元组 $(l_i,r_i,w_i)$ 表示。

莲子要从点 $s$ 出发，经过了若干条边到达点 $t$。她带有一个初始值均为 $0$ 的长度为 $k$ 的数组 $a$，每次经过编号为 $i$ 的边，就会执行将 $a$ 数组的区间 $[l_i,r_i]$ 加 $w_i$ 的操作。她使用了一棵**带懒标记**的线段树来维护这一操作。线段树的写法会在接下来给出。

你需要构造一条从 $s$ 到 $t$ 的路径，满足达到结点 $t$ 时，其线段树上所有标记的和的最小。输出这个最小值。

以下是线段树的伪代码：（为了方便选手阅读，题目附件中给出了线段树的 C++ 源代码）

$$
\begin{array}{l}\hline\hline\\[-0.8em]
\textbf{Algorithm: }\text{SegTree}\\\hline\\[-0.5em]
\begin{array}{rl}
1& \mathbf{Input.} \text{ 长度为 $k$ 的 $a$ 数组，初始全为 $0$}\\
2& \mathbf{Output.} \text{ $a$ 数组进行若干次区间加操作后得到的结果}\\
3& \mathbf{Method.}\\
4& \mathrm{Add}(L,R,x)\\
5& \quad\mathrm{Add0}(L,R,x,root,1,k)\\
6& \mathrm{Add0}(L,R,x,u,l,r)\\
7& \quad\mathbf{if}\ L \le l\ \mathbf{and}\ r\le R\\
8& \quad\quad \mathrm{tag}(u) \gets \mathrm{tag}(u) + x\\
9& \quad\quad \mathbf{return}\\
10& \quad mid \gets \lfloor\frac{l+r} 2\rfloor\\
11& \quad \mathrm{tag}(\mathrm{lson}(u)) \gets \mathrm{tag}(\mathrm{lson}(u))+\mathrm{tag}(u)\\
12& \quad \mathrm{tag}(\mathrm{rson}(u)) \gets \mathrm{tag}(\mathrm{rson}(u))+\mathrm{tag}(u)\\
13& \quad \mathrm{tag}(u) \gets 0\\
14& \quad\mathbf{if}\ L \le mid\\
15& \quad\quad\mathrm{Add0}(L,R,x,\mathrm{lson}(u),l,mid)\\
16& \quad\mathbf{if}\ mid < R\\
17& \quad\quad\mathrm{Add0}(L,R,x,\mathrm{rson}(u),mid+1,r)\\
\end{array}\\\hline\hline
\end{array}
$$
## 输入格式

- 第一行五个整数 $n,m,k,s,t$。
- 接下来 $m$ 行，每行五个整数 $u_i,v_i,l_i,r_i,w_i$。
## 输出格式

- 共一行一个整数，表示沿着你构造的路径从 $s$ 到达 $t$ 后线段树上所有懒标记的权值之和。
## 样例

### 样例输入 #1
```
4 4 5 1 4
1 2 1 2 2
1 3 4 5 1
2 4 2 3 1
3 4 3 5 2
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
10 19 5 6 1
2 1 1 3 592
6 8 3 5 488
10 9 4 4 548
10 4 1 4 442
6 5 1 3 422
9 7 1 4 529
5 8 1 1 559
5 9 1 5 560
5 8 2 3 434
5 9 3 3 592
4 7 2 2 594
7 9 5 5 595
4 1 4 4 501
3 9 1 2 410
10 6 2 4 509
6 10 4 5 455
2 4 2 5 444
4 3 4 5 541
8 7 1 1 463

```
### 样例输出 #2
```
2295

```
## 提示

### 样例解释

#### 样例 \#1

![](https://cdn.luogu.com.cn/upload/image_hosting/npzajpom.png)

容易发现，样例 $1$ 中有且仅有两条可能的路径：$1\to 2\to 4$ 与 $1\to 3\to 4$。下面分别计算这两条路径最终 $\text{tag}$ 的权值和。

![](https://cdn.luogu.com.cn/upload/image_hosting/2fq7okad.png)

考虑画出这棵 $k=5$ 的线段树。

![](https://cdn.luogu.com.cn/upload/image_hosting/ys42i046.png)

走了边 $1\to 2$ 后，$[1,2]$ 节点被打上了权值为 $2$ 的 $\text{tag}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/02sqysh5.png)

走了 $2\to 4$ 后，$[2,2]$ 节点和 $[3,3]$ 节点被打上了值为 $1$ 的 $\text{tag}$；但是 $[1,2]$ 节点的标记进行了下推（因为使 $[2,3]$ 区间 $+1$ 的时候会访问到 $[1,2]$ 节点，而 $[1,2]\nsubseteq[2,3]$，故而发生标记下推），因此 $[1,1]$ 节点和 $[2,2]$ 节点的 $\text{tag}$ 分别加上了 $2$，最终成了如图所示的模样。

因此走到 $4$ 之后所有结点的 $\text{tag}$ 之和为 $2+3+1=6$。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/3va7fa03.png)

对于另外一条路径，首先对 $[4,5]$ 加上 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/o1cw3s03.png)

接着对 $[3,5]$ 加上 $2$。未发生带有 $\text{tag}$ 的节点的标记下推，因此最终的权值为 $2+3=5$。

由于 $6>5$，因而最终的答案为 $5$。

### 数据范围及约定

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|c|}\hline
\textbf{subtask}& \textbf{分值}& {\bm n\le} & {\bm m\le} & {\bm k\le} & \textbf{特殊性质} & \textbf{subtask 依赖}\cr\hline
1 & 10& 10 & 30 & 5 & - & -\cr\hline
2 & 5&30 & 30 & 12 & \textbf{AB} &-\cr\hline
3 & 20&30 & 500 & 12 & \textbf{B} &2 \cr\hline
4 & 15&200 & 3\times 10^3 & 25 & \textbf{B}&3\cr\hline
5 & 50&200 & 3\times 10^3 & 25 & - &4\cr\hline
\end{array}
$$

- **特殊性质** $\textbf{A}$：保证有且仅有一条从 $s$ 到 $t$ 的路径。
- **特殊性质** $\textbf{B}$：保证图中不存在环。

对于 $100\%$ 的数据，有 $1 \le s,t,u_i,v_i \leq n \leq 200$，$1 \leq m \leq 3\times 10^3$，$1 \leq l_i\le r_i \leq k \leq 25$，$1 \leq w_i \leq 10^3$。

### 提示

在附件中有两个版本的线段树。$\text{Lite}$ 版本**仅**包含了在本题中你会用到的下推标记的操作，而标准版则较为完整地支持区间加、区间求和。选手可根据自己的喜好使用。


---

