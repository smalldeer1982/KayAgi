---
title: "『STA - R4』踱步"
layout: "post"
diff: 提高+/省选-
pid: P10119
tag: ['动态规划 DP', '单调队列', 'O2优化', '动态规划优化', '前缀和']
---
# 『STA - R4』踱步
## 题目描述

小 X 特别喜欢安静的环境，因为那可以让他心情愉悦。

现在给出 $N$ 分钟内每分钟屋内和屋外对小 X 的心情影响值，在这 $N$ 分钟内，小 X 可以从屋内踱步到屋外或是从屋外踱步到屋内**最多共** $K$ 次。（小 X 当且仅当每分钟初进行踱步，同一时刻至多踱步一次，并且踱步的时间忽略不计。第 $1$ 分钟初不可踱步，第 $N$ 分钟初可以踱步。但是在第 $1$ 分钟初可以自由选择初始状态）。

同时，过于频繁的改变会让小 X 心情烦躁，所以如果两次踱步的间隔**小于等于** $T$ 分钟，会对小 X 的心情额外造成 $P$ 点影响。（如果此次踱步是在第 $t_a$ 分钟初，上一次踱步是在第 $t_b$ 分钟初，那么这两次踱步的时间间隔为 $t_a - t_b$ 分钟）。

小 X 想知道自己的心情最好可以是多少，即第 $N$ 分钟末小 X 心情值的最大值。

若某一时刻小 X 的心情值为 $a$，之后小 X 的心情被影响了 $b$，那么在此之后小 X 的心情值将变为 $a + b$。
## 输入格式

**本题单个测试点内含有多组测试数据。**

第一行两个正整数 $\text{id},\text{TEST}$。其中 $\text{id}$ 代表 Subtask 编号，$\text{TEST}$ 代表测试数据组数。特别的，样例的 $\text{id}$ 为 $0$。

对于每组测试数据：

第一行为四个整数 $N, K, T, P$。

接下来 $N$ 行每行两个整数。其中第 $i$ 行的两个整数 $a_i, b_i$ 分别代表第 $i$ 分钟屋内和屋外对小 X 心情的影响值。
## 输出格式

对于每组测试数据，输出一行一个整数，代表第 $N$ 分钟末小 X 心情值的最大值。
## 样例

### 样例输入 #1
```
0 2
8 3 2 3
0 -2
5 -10
8 0
-10 -7
0 -3
-4 -9
-9 -3
-7 0
8 3 2 -6
9 6
9 -6
3 7
-4 3
8 -9
6 0
-10 9
-8 -4

```
### 样例输出 #1
```
5
36

```
### 样例输入 #2
```
0 1
12 3 2 -35771156
797235777 25138038
801541087 -405462832
936777370 -973167834
74493410 60154946
263320806 782480907
-940214410 805511853
806065179 463119365
-295177485 -112301429
-403964212 202831413
122359196 611468120
-555210139 549749508
793784715 -38433603

```
### 样例输出 #2
```
6706692096

```
### 样例输入 #3
```
0 1
5 2 1 -100
-44 -72
-36 -23
-4 0
-22 -1
-88 3

```
### 样例输出 #3
```
-65

```
## 提示

**【样例 #1 解释】**

对于第 $1$ 组数据，最优方案为初始时选择在屋内，分别在第 $4, 5, 7$ 分钟初进行踱步。

![](https://cdn.luogu.com.cn/upload/image_hosting/cx7tr8m2.png)

其中第 $2$ 次踱步与第 $1$ 次踱步之间的间隔为 $5 - 4 = 1$ 分钟，对小 $\text{X}$ 的心情产生 $3$ 的贡献，第 $3$ 次踱步与第 $2$ 次踱步之间的间隔为 $7 - 5 = 2$ 分钟，对小 X 的心情产生 $3$ 的贡献。

因此小 X 的心情值为

$$\left(0+5+8-7+0-4-3+0\right) + 6 = 5$$

前半部分为灰色格子的权值和，后半部分为两次频繁踱步产生的额外贡献，可以证明此方案最优。

**【样例 #2 解释】**

请注意答案可能超过 $32$ 位整型数字的范围。

**【样例 #3 解释】**

请注意答案可能为负数。


**【数据范围】**

对于 $100\%$ 的数据：

- $1 \le \text{TEST} \le 10^5$；
- $2 \le N \le 2 \times 10^5$；
- $1 \le K \le \min\left\{200, N\right\}$；
- $1 \le T \le \min\left\{2 \times 10^4, N\right\}$；
- $\left\lvert a_i \right\rvert,\left\lvert b_i \right\rvert,\left\lvert P \right\rvert \le 10^9$。
- $\sum N \cdot K \le 5 \times 10^7$。
- 保证单个测试点输入数据规模不超过 10 MB。

**本题采用捆绑测试。**

|Subtask 编号|数据范围|分值|依赖子任务|
|:--------:|:--------:|:--------:|:--------:|
|1|$N \le 20, \text{TEST} \le 10$|$5$||
|2|$\sum N^2K \le 5 \times 10^7$|$20$|$1$|
|3|$K \le 5, N \le 5 \times 10^4, \text{TEST} \le 10$|$15$||
|4|$P=-10^9, 0 \le \left\lvert a_i \right\rvert,\left\lvert b_i \right\rvert \le 100$|$30$||
|5|无特殊限制|$30$|$1,2,3,4$|


---

---
title: "「SMOI-R1」Game"
layout: "post"
diff: 提高+/省选-
pid: P10407
tag: ['动态规划 DP', '单调队列']
---
# 「SMOI-R1」Game
## 题目背景

myz 很喜欢玩一款病毒游戏。
## 题目描述

在这个游戏里，一开始有 $n$ 个病毒，每个病毒的危害值为 $1$。

每隔一段时间，病毒就会变异，会分裂成两个病毒，右边的病毒会比左边的病毒危害值多 $1$，变异过的病毒不会再变异。

每个病毒有个变异极限 $b_i$，当这个病毒变异到 $b_i$ 时，这个病毒就会停止变异。也就是说，第 $i$ 个病毒最后都会分裂成一个危害值为 $\{1,2,3,\ldots,b_i\}$ 的病毒序列，当所有病毒变异完时，游戏开始，最终变异完的序列是 $\{1,2,3,\ldots,b_1,1,2,3,\ldots,b_2,\ldots,1,2,3,\ldots,b_n\}$。

每次游戏，系统会选择一个区间，myz 需要把这个区间的病毒全部杀死，如果这个区间内的病毒的危害值的最大值是 $x$，那么 myz 需要花费 $x$ 的能量才能消灭它们。

因为不知道系统会选择哪个区间，myz 想知道每个区间需要消耗的**能量值之和**。

由于答案太大了，myz 想让你把答案对 $998244353$ 取模。
## 输入格式

第一行有一个整数 $n$，表示最开始有 $n$ 个病毒。

第二行有 $n$ 个整数，第 $i$ 个整数是 $b_i$，表示第 $i$ 个病毒的变异上限。
## 输出格式

一个整数，表示 myz 需要消耗的能量值之和，答案对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
2
2 3
```
### 样例输出 #1
```
33
```
## 提示

### 样例解释
第一个样例，病毒最后分裂成 $\{1,2,1,2,3\}$，区间  $[1,1],[1,2],[1,3],[1,4],[1,5],[2,2],[2,3],[2,4],[2,5],[3,3],[3,4],[3,5],[4,4],[4,5],[5,5]$ 的最小代价和就是 $1+2+2+2+3+2+2+2+3+1+2+3+2+3+3=33$。

### 数据范围
**本题采用捆绑测试**。

subtask 编号|$n\leq$|$b_i\leq$|特殊性质|分值
-|-|-|-|-
$1$|$10^2$|$10^2$|无|$20$
$2$|$10^4$|$10^2$|无|$20$
$3$|$10^6$|$10^9$|A|$20$
$4$|$10^6$|$10^9$|无|$40$

**特殊性质 A**： $b_1 \leq b_2 \leq \ldots \leq b_n$。

对于 $100\%$ 的数据，保证 $1\le n\le10^6$，$1\le b_i\le 10^9$。


---

---
title: "生日礼物"
layout: "post"
diff: 提高+/省选-
pid: P10478
tag: ['贪心', '优先队列']
---
# 生日礼物
## 题目描述

ftiasch 18 岁生日的时候，lqp18_31 给她看了一个神奇的序列 $A _ 1$, $A _ 2$, ..., $A _ N$。 她被允许选择不超过 $M$ 个连续的部分作为自己的生日礼物。

自然地，ftiasch 想要知道选择元素之和的最大值。你能帮助她吗?
## 输入格式

第 1 行，两个整数 $N$ ($1 \le  N \le 10 ^ {5}$ ) 和 $M$ ($0 \le M \le 10 ^ 5$)，表示序列的长度和可以选择的部分。 

第 2 行， $N$ 个整数 $A_1$, $A_2$, ..., $A_N$ ($0 \le \mid A_i\mid \le 10^4$)，表示序列。

## 输出格式

一个整数，表示最大的和。
## 样例

### 样例输入 #1
```
5 2
2 1 -2 3 -2
```
### 样例输出 #1
```
6
```


---

---
title: "[EPXLQ2024 fall round] 好排列"
layout: "post"
diff: 提高+/省选-
pid: P11413
tag: ['模拟', '堆', '优先队列', '链表']
---
# [EPXLQ2024 fall round] 好排列
## 题目背景

温昭雪喜欢构造排列。
## 题目描述

她的目标是构造一个由 $n$ 个数组成的排列 $A_1,A_2,\dots,A_n$，初始时 $A$ 中的所有元素都是 $0$。

接下来，对于数 $i$（$1 \le i \le n$），她通过下面方式由 $1$ 到 $n$ 确定其位置：

- 如果 $i=1$，将其放到最左侧。

- 如果 $i=2$，将其放到最右侧。

- 如果都不是，定义 $f_0(x)$ 表示 $x$ 左侧（包含 $x$，下同）的连续的 $0$ 的个数，$g_0(x)$ 为 $x$ 右侧的连续的 $0$ 的个数。特别地，如果 $x \le 0$ 或 $x > n$，$f_0(x)=g_0(x)=n+1$。
- 定义 $f_1(x)$ 表示 $x$ 左侧的连续非 $0$ 位置的个数，$g_1(x)$ 表示 $x$ 右侧的连续非 $0$ 位置的个数。特别地，如果 $x \le 0$ 或 $x > n$，$f_0(x)=g_0(x)=0$。
- 如果存在位置 $j$，使得 $\min(f_0(j), g_0(j)) > 1$，则选择位置 $j$ 最大化 $\min(f_0(j), g_0(j))$。如果有多个位置的值相同，选择 $j$ 较小的。
- 如果不存在这样的位置，则选择位置 $j$ 使得 $f_0(j)=1$ 并最小化 $f_1(j-1) + g_1(j+1)$。如果有多个位置的值相同，选择 $j$ 较小的。

温昭雪的幸运数字是 $k$。为了避免输出过多，她只想知道数字 $k$ 处于排列的什么位置。
## 输入格式

**本题单个测试点内有多组测试数据。**

输入第一行 $T$，表示数据组数。

以下 $T$ 行，每行两个正整数 $n,k$。
## 输出格式

输出 $T$ 行，每行一个正整数 $x$，表示排列长度为 $n$ 时，$A_x=k$。
## 样例

### 样例输入 #1
```
2
3 1
6 4
```
### 样例输出 #1
```
1
4

```
## 提示

### 样例解释

第一组测试数据对应的排列为 $\{1,3,2\}$。

第二组测试数据对应的排列为 $\{1,5,3,4,6,2\}$。

### 数据规模与约定


| 测试点编号 | $n$ | $k$ | $T$ | $\sum n$ | 特殊性质 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| $1,2$ | $\le 10$ | $\le 10$ | $\le 10$ | $\le 100$ | |
| $3,4$ | $\le 100$ | $\le 100$ | $\le 10$ | $\le 1000$ | |
| $5$ | $\le 1000$ | $\le 10$ | $\le 10$ | $\le 10^4$ | |
| $6,7$ | $\le 1000$ | $\le 1000$ | $\le 100$ | $\le 10^5$ |
| $8,9$ | $\le 10^4$ | $\le 10$ | $\le 100$ | $\le 10^5$ |
| $10 \sim 13$ | $\le 10^4$ | $\le 10^4$ | $\le 100$ | $\le 10^6$  | $n,k$ 均为奇数 |
| $14 \sim 17$ | $\le 10^4$ | $\le 10^4$ | $\le 100$ | $\le 10^6$ | $n,k$ 均为偶数 |
| $18,19$ | $\le 10^5$ | $\le 10$ | $\le 10$ | $\le 10^5$ | |
| $20,21$ | $\le 10^5$ | $\le 10^5$ | $\le 100$ | $\le 10^6$ | |
| $22\sim 25$ | $\le 10^6$ | $\le 10^6$ | $\le 100$ | $\le 10^6$ | |

对于奇数编号的测试点，内存限制为 $\text{512 MB}$；对于偶数编号的测试点，内存限制为 $\text{64 MB}$。

对于所有数据，保证 $1 \le k \le n \le 10^6, \sum n \le 10^6$。


---

---
title: "[蓝桥杯 2025 省 A] 扫地机器人"
layout: "post"
diff: 提高+/省选-
pid: P12145
tag: ['线段树', '单调队列', '2025', '树形 DP', '树的直径', 'ST 表', '基环树', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 A] 扫地机器人
## 题目描述

在一个含有 $n$ 个点 $n$ 条边的无重边无自环的连通无向图中，有一个扫地机器人在执行清扫作业。其中结点 $i$ 的标记 $t_i \in \{0,1\}$：如果为 $1$，则说明该结点需要进行清扫，扫地机器人在到达这个结点时会顺便进行清扫工作。机器人想知道，如果选定任意结点出发，每条边只能经过一次的话，最多能清扫多少个待清扫结点？
## 输入格式

输入的第一行包含一个正整数 $n$。

第二行包含 $n$ 个整数 $t_1, t_2, \cdots, t_n$，相邻整数之间使用一个空格分隔。

接下来 $n$ 行，每行包含两个正整数 $u_i, v_i$，用一个空格分隔，表示结点 $u_i$ 和结点 $v_i$ 之间有一条边。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
9
1 0 1 0 0 1 1 0 1
2 8
2 9
2 5
1 5
1 3
1 4
4 5
4 6
6 7
```
### 样例输出 #1
```
4
```
## 提示

### 样例说明
其中一种可行路线：$3 \rightarrow 1 \rightarrow 4 \rightarrow 6 \rightarrow 7$，清扫结点 $3, 1, 6, 7$（共 $4$ 个）。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n \leq 5000$；
- 对于所有评测用例，$1 \leq n \leq 500000$，$t_i \in \{0,1\}$，$1 \leq u_i, v_i \leq n$。


---

---
title: "[UTS 2024] Matrix"
layout: "post"
diff: 提高+/省选-
pid: P12561
tag: ['递推', '倍增', '单调队列', '2024', 'UOI（乌克兰）']
---
# [UTS 2024] Matrix
## 题目描述

You are given a matrix of size $n \times m$ consisting of elements $a_{i,j}$. 

We call a **triangle** on the matrix of size $k$ starting at point $(x;y)$ a set of points that can be reached from $(x;y)$ in no more than $k$ steps going either up or right. 

You are asked to find for each $(x;y)$ $(k \le x \le n, 1 \le y \le m-k+1)$ the following values:

- The maximal value in the triangle of size $k$ starting at point $(x;y)$;
- The number of occurrences of the maximal value in that triangle.
## 输入格式

The first line contains three integers $n$, $m$, and $k$ $(1 \le n,m \le 2\,000, 1 \le k \le \min(n,m))$ --- dimensions of the matrix and the size of the triangle.

The following $n$ lines contain $m$ integers $a_{i,j}$ $(0 \le a_{i,j} \le 10^6)$ --- description of the matrix.
## 输出格式

Print two matrices of size $(n-k+1)\times(m-k+1)$. 

The first matrix in position $(i;j)$ should contain the maximal value of a triangle of size $k$ starting at $(i+k-1;j)$.

The second matrix in position $(i;j)$ should contain the number of occurrences of the maximal value in the triangle of size $k$ starting at $(i+k-1;j)$.
## 样例

### 样例输入 #1
```
4 4 2
1 2 6 14
12 3 13 5
11 4 7 8
10 16 9 15
```
### 样例输出 #1
```
12 13 13 
12 7 13 
16 16 15 
1 1 1 
1 1 1 
1 1 1 
```
## 提示

- ($5$ points) $n,m \le 20$;
- ($10$ points) $n,m \le 100$;
- ($30$ points) $a_{i,j} \le 1$;
- ($35$ points) $n,m \le 1\,000$;
- ($20$ points) no additional restrictions.


---

---
title: "[KOI 2022 Round 2] 食事计划"
layout: "post"
diff: 提高+/省选-
pid: P12702
tag: ['贪心', '2022', '优先队列', 'KOI（韩国）']
---
# [KOI 2022 Round 2] 食事计划
## 题目背景

试题来源：<https://koi.or.kr/archives/>。中文翻译做了少量本土化修改。

按照[署名—非商业性使用—相同方式共享 4.0 协议国际版](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh-hans)进行授权。
## 题目描述

在 KOI 国家，铁柱所在的地方有 $N$ 个餐厅。每个餐厅只售卖一种食物，食物的类型通过整数 $A_i$ 来表示，$i$（$1 \leq i \leq N$）。

铁柱计划访问所有的餐厅，并为自己制定一个食事计划。铁柱的食事计划可以用从 $1$ 到 $N$ 的整数排列 $P$ 来表示。举例来说，如果 $P = [2, 4, 3, 1]$，这意味着铁柱将依次访问餐厅 2、4、3 和 1。

由于铁柱不希望连续吃相同类型的食物，所以在他的食事计划中，连续的两个餐厅必须提供不同类型的食物。也就是说，对于 $i = 1, 2, \dots, N-1$，$A_{P_i} \neq A_{P_{i+1}}$ 必须成立，而符合这一条件的食事计划被称为合法食事计划。

例如，假设 $N = 9$，且提供的食物类型是 $A = [1, 1, 1, 2, 2, 3, 3, 4, 3]$，则如果铁柱的食事计划是 $P = [3, 4, 1, 5, 6, 2, 7, 8, 9]$，那么计划中的每两个相邻餐厅的食物类型都不同，符合条件。

若铁柱的食事计划是 $P = [1, 4, 2, 5, 6, 3, 7, 8, 9]$，这也是一个合法的食事计划，并且是按字典顺序最前的合法计划。

然而，若食物类型是 $A = [1, 1, 1]$，无论怎样安排食事计划，都无法满足“连续两餐不同类型”的要求。

当给定 $N$ 个餐厅的食物类型时，如果无法制定合法的食事计划，则输出 -1；否则，输出字典序最前的合法食事计划。

## 输入格式

第一行给出整数 $N$，表示餐厅的数量。

第二行给出 $N$ 个整数 $A_1, A_2, \dots, A_N$，表示每个餐厅的食物类型。
## 输出格式

如果无法制定合法的食事计划，输出 -1。如果能够制定合法的食事计划，则输出字典序最前的合法食事计划 $P$，每个数之间用一个空格分隔。

## 样例

### 样例输入 #1
```
9
1 1 1 2 2 3 3 4 3
```
### 样例输出 #1
```
1 4 2 5 6 3 7 8 9
```
### 样例输入 #2
```
3
1 1 1
```
### 样例输出 #2
```
-1
```
## 提示

**约束条件**

- $1 \leq N \leq 300\,000$
- $1 \leq A_i \leq N$

**子任务**

1. （5 分）$N \leq 8$
2. （12 分）$N \leq 20$
3. （32 分）$N \leq 5\,000$
4. （51 分）无额外约束条件


---

---
title: "[USACO07MAR] Gold Balanced Lineup G"
layout: "post"
diff: 提高+/省选-
pid: P1360
tag: ['2007', 'USACO', '离散化', '进制', '前缀和', '队列']
---
# [USACO07MAR] Gold Balanced Lineup G
## 题目描述

神仙 $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 在许多方面都有着很强的能力。具体的说，他总共有 $m$ 种能力，并将这些能力编号为 $1 \sim m$。  

他的能力是一天一天地提升的，每天都会有一些能力得到一次提升，她对每天的能力提升都用一个数字表示，称之为能力提升数字，比如数字 $13$，转化为二进制为 $1101$，并且从右往左看，表示他的编号为 $1,3,4$ 的能力分别得到了一次提升。  

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 把每天表示能力提升的数字的记了下来，如果在连续的一段时间内，她的每项能力都提升了相同的次数，她就会称这段时间为一个均衡时期，比如在连续 $5$ 天内，她的每种能力都提升了 $4$ 次，那么这就是一个长度为 $5$ 的均衡时期。

于是，问题来了，给出 $\mathsf E \color{red} \mathsf{ntropyIncreaser}$ $n$ 天的能力提升数字，请求出均衡时期的最大长度。

## 输入格式

第一行有两个整数 $n,m$，表示有 $n$ 天，$m$ 种能力。　　

接下来有 $n$ 行，每行有一个整数，分别表示第 $1\sim n$ 天的能力提升数字。  

能力提升数字转化为二进制后，从右到左的每一位表示对应的能力是否在当天得到了一次提升。



## 输出格式

输出只有一个整数，表示长度最大的均衡时期的长度。

## 样例

### 样例输入 #1
```
7 3
7
6
7
2
1
4
2

```
### 样例输出 #1
```
4


```
## 提示

【数据范围】    
对于 $50\%$ 的数据，$1\le n \le 1000$。  
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le m \le 30$。

【样例解释】

每天被提升的能力种类分别为：

| 天数 | 提升的能力 |
| :-----------: | :-----------: |
| $1$ | $1,2,3$ |
| $2$ | $2,3$ |
| $3$ | $1,2,3$ |
| $4$ | $2$ |
| $5$ | $1$ |
| $6$ | $3$ |
| $7$ | $2$ |

第三天到第六天为长度最长的均衡时期，因为这四天每种能力分别提升了 $2$ 次。



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
title: "[USACO04DEC] Dividing the Path G"
layout: "post"
diff: 提高+/省选-
pid: P1545
tag: ['动态规划 DP', '2004', '线段树', 'USACO', '单调队列', '动态规划优化']
---
# [USACO04DEC] Dividing the Path G
## 题目描述

约翰的奶牛们发现山脊上的草特别美味。为了维持草的生长，约翰打算安装若干喷灌器。

为简化问题，山脊可以看成一维的数轴，长为 $L\ (1\le L\le 10^6)$，而且 $L$ 一定是一个偶数。每个喷灌器可以双向喷灌，并有确定的射程，该射程不短于 $A$，不长于 $B$，$A$，$B(1\le A\le B\le 10^3)$ 都是给出的正整数。它所在位置的两边射程内，都属它的灌溉区域。

现要求山脊的每一个区域都被灌溉到，而且喷灌器的灌溉区域不允许重叠。约翰有 $N(1\le N\le 10^3)$ 只奶牛，每一只都有特别喜爱的草区，第 $i$ 奶牛的草区是 $[S_i,E_i]$，不同奶牛的草区可以重叠。现要求，每只奶牛的草区仅被一个喷灌器灌溉。

注意：

1. 数轴 $L$ 从 $0$ 开始标记（即坐标范围 $0\sim L$）  
2. 喷灌器坐标和射程必须为整数，对于坐标为 $i$ 射程为 $x$ 的喷灌器，它的灌溉范围为 $[i-x,i+x]$。
3. 浇灌区间必须在山脊范围内。例如，不能在 $0$ 位置放一个半径为 $1$ 的浇灌器。

寻找最少需要的喷灌器数目。
## 输入格式

第一行两个整数 $N,L$。

第二行两个整数 $A,B$。

然后 $N$ 行每一行两个整数 $S_i,E_i$（$1\le S_i < E_i\le L$）。
## 输出格式

一行，输出所需的最少洒水器数量。如果无法为农夫约翰设计喷头配置，则输出 $-1$。
## 样例

### 样例输入 #1
```
2 8
1 2
6 7
3 6
```
### 样例输出 #1
```
3
```
## 提示

对于 $100\%$ 的数据，$1\le L\le 10^6$，$1\le A,B\le 10^3$，$1\le N\le 10^3$，$1\le S_i<E_i\le L$。

样例解释：

![](https://vj.csgrandeur.cn/d4313c41a71f91cdadfcba2601cf5034?v=1699442455)


---

---
title: "Sramoc问题"
layout: "post"
diff: 提高+/省选-
pid: P1602
tag: ['字符串', '搜索', '数学', '队列']
---
# Sramoc问题
## 题目描述

话说员工们整理好了筷子之后，就准备将快餐送出了，但是一看订单，都傻眼了:订单上没有留电话号码,只写了一个  $sramoc(k,m)$ 函数，这什么东西？什么意思？于是餐厅找来了资深顾问团的成员，YQ，SC，HQ，经过大量的查阅，大家获得了一些信息，$sramoc(k,m)$ 表示用数字 $0,1,2,\dots k-1$ 组成的正整数中能被 $m$ 整除的最小数。例如 $k=2,m=7$ 的时候，$sramoc(2,7)=1001$。自然电话号码就是 $1001$，为了尽快将快餐送出，电脑组的童鞋们埋头算起了这个齐葩的号码。。。
## 输入格式

第 $1$ 行为两个整数 $k,m$。
## 输出格式

仅 $1$ 行，那个电话号码（最小的数）。
## 样例

### 样例输入 #1
```
2 7

```
### 样例输出 #1
```
1001
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，$2\le k\le10$，$1\le m\le 10^3$。


---

---
title: "[HAOI2007] 修筑绿化带"
layout: "post"
diff: 提高+/省选-
pid: P2219
tag: ['2007', '河南', '各省省选', '平衡树', '单调队列', '队列']
---
# [HAOI2007] 修筑绿化带
## 题目描述

为了增添公园的景致，现在需要在公园中修筑一个花坛，同时在花坛四周修建一片绿化带，让花坛被绿化带围起来。

如果把公园看成一个 $M\times N$ 的矩形，那么花坛可以看成一个 $C\times D$ 的矩形，绿化带和花坛一起可以看成一个 $A\times B$ 的矩形。

如果将花园中的每一块土地的“肥沃度”定义为该块土地上每一个小块肥沃度之和，那么，绿化带的肥沃度为 $A\times B$ 块的肥沃度减去 $C\times D$ 块的肥沃度。

为了使得绿化带的生长得旺盛，我们希望绿化带的肥沃度最大。
## 输入格式

第一行有六个正整数 $M,N,A,B,C,D$。

接下来一个 $M\times N$ 的数字矩阵，其中矩阵的第 $i$ 行 $j$ 列元素为一个整数 $x_{i,j}$，表示该花园的第 $i$ 行第 $j$ 列的土地 “肥沃度”。
## 输出格式

一个正整数，表示绿化带的最大肥沃程度。

## 样例

### 样例输入 #1
```
4 5 4 4 2 2
20 19 18 17 16
15 14 13 12 11
10 9 8 7 6
5 4 3 2 1

```
### 样例输出 #1
```
132
```
## 提示

对于 $30\%$ 的数据，$1\leq M,N\leq 50$。

对于 $100\%$ 的数据，$1\leq M,N\leq 1000$，$1\leq A\leq M$，$1\leq B\leq N$，$1\leq C\leq A-2$，$1\leq D\leq B-2$，$1\leq x_{i,j}\leq 100$。


---

---
title: "[NOI2005] 瑰丽华尔兹"
layout: "post"
diff: 提高+/省选-
pid: P2254
tag: ['动态规划 DP', '2005', '单调队列', 'NOI', '队列']
---
# [NOI2005] 瑰丽华尔兹
## 题目背景

你跳过华尔兹吗？当音乐响起，当你随着旋律滑动舞步，是不是有一种漫步仙境的惬意？

众所周知，跳华尔兹时，最重要的是有好的音乐。但是很少有几个人知道，世界上最伟大的钢琴家一生都漂泊在大海上，他的名字叫丹尼・布德曼・T.D.・柠檬・1900，朋友们都叫他 1900。

1900 在 20 世纪的第一年出生在往返于欧美的邮轮弗吉尼亚号上。很不幸，他刚出生就被抛弃，成了孤儿。1900 孤独的成长在弗吉尼亚号上，从未离开过这个摇晃的世界。也许是对他命运的补偿，上帝派可爱的小天使艾米丽照顾他。可能是天使的点化，1900 拥有不可思议的钢琴天赋：从未有人教，从没看过乐谱，但他却能凭着自己的感觉弹出最沁人心脾的旋律。当 1900 的音乐获得邮轮上所有人的欢迎时，他才 8 岁，而此时，他已经乘着海轮往返欧美大陆 50 余次了。

虽说是钢琴奇才，但 1900 还是个孩子，他有着和一般男孩一样的好奇和调皮，只不过更多一层浪漫的色彩罢了：这是一个风雨交加的夜晚，海风卷起层层巨浪拍打着弗吉尼亚号，邮轮随着巨浪剧烈的摇摆。船上的新萨克斯手迈克斯・托尼晕船了，1900 招呼托尼和他一起坐到舞厅里的钢琴上，然后松开了固定钢琴的闸，于是，钢琴随着海轮的倾斜滑动起来。准确的说，我们的主角 1900…

## 题目描述

不妨认为舞厅是一个 $N$ 行 $M$ 列的矩阵，矩阵中的某些方格上堆放了一些家具，其他的则是空地。钢琴可以在空地上滑动，但不能撞上家具或滑出舞厅，否则会损坏钢琴和家具，引来难缠的船长。每个时刻，钢琴都会随着船体倾斜的方向向相邻的方格滑动一格，相邻的方格可以是向东、向西、向南或向北的。而艾米丽可以选择施魔法或不施魔法：如果不施魔法，则钢琴会滑动；如果施魔法，则钢琴会原地不动。

艾米丽是个天使，她知道每段时间的船体的倾斜情况。她想使钢琴在舞厅里滑行的路程尽量长，这样 1900 会非常高兴，同时也有利于治疗托尼的晕船。但艾米丽还太小，不会算，所以希望你能帮助她。

## 输入格式

输入文件的第一行包含 $5$ 个数 $N$, $M$, $x$, $y$ 和 $K$。$N$ 和 $M$ 描述舞厅的大小，$x$ 和 $y$ 为钢琴的初始位置；我们对船体倾斜情况是按时间的区间来描述的，且从 $1$ 开始计算时间，比如 “在 $[1, 3]$ 时间里向东倾斜，$[4, 5]$ 时间里向北倾斜”，因此这里的 $K$ 表示区间的数目。

以下 $N$ 行，每行 $M$ 个字符，描述舞厅里的家具。第 $i$ 行第 $j$ 列的字符若为 `.`，则表示该位置是空地；若为 `x`，则表示有家具。

以下 $K$ 行，顺序描述 $K$ 个时间区间，格式为：$s_i\ t_i\ d_i (1 \leq i \leq K)$。表示在时间区间 $[s_i, t_i]$ 内，船体都是向 $d_i$ 方向倾斜的。$d_i$ 为 $1$, $2$, $3$, $4$ 中的一个，依次表示北、南、西、东（分别对应矩阵中的上、下、左、右）。输入保证区间是连续的，即

$s_1 = 1$，$s_i = t_{i-1} + 1 (1 < i \leq K)$，$t_K = T$。
## 输出格式

输出文件仅有 $1$ 行，包含一个整数，表示钢琴滑行的最长距离 (即格子数)。

## 样例

### 样例输入 #1
```
4 5 4 1 3
..xx.
.....
...x.
.....
1 3 4
4 5 1
6 7 3
```
### 样例输出 #1
```
6
```
## 提示

钢琴的滑行路线：

 ![](https://cdn.luogu.com.cn/upload/pic/1307.png) 

钢琴在“×”位置上时天使使用一次魔法，因此滑动总长度为 $6$。

【数据范围】

$50\%$ 的数据中，$1\leq N, M\leq 200，T\leq 200$；

$100\%$ 的数据中，$1\leq N$, $M \leq 200$，$K \leq 200$，$T\leq 40000$。



---

---
title: "[HNOI2003] 操作系统"
layout: "post"
diff: 提高+/省选-
pid: P2278
tag: ['模拟', '2003', '各省省选', '湖南', '优先队列', '队列']
---
# [HNOI2003] 操作系统
## 题目描述

写一个程序来模拟操作系统的进程调度。假设该系统只有一个 CPU，每一个进程的到达时间，执行时间和运行优先级都是已知的。其中运行优先级用自然数表示，数字越大，则优先级越高。

如果一个进程到达的时候 CPU 是空闲的，则它会一直占用 CPU 直到该进程结束。除非在这个过程中，有一个比它优先级高的进程要运行。在这种情况下，这个新的（优先级更高的）进程会占用 CPU，而老的只有等待。

如果一个进程到达时，CPU 正在处理一个比它优先级高或优先级相同的进程，则这个（新到达的）进程必须等待。

一旦 CPU 空闲，如果此时有进程在等待，则选择优先级最高的先运行。如果有多个优先级最高的进程，则选择到达时间最早的。

## 输入格式

输入包含若干行，每一行有四个自然数（均不超过 $10^8$），分别是进程号，到达时间，执行时间和优先级。不同进程有不同的编号，不会有两个相同优先级的进程同时到达。输入数据已经按到达时间从小到大排序。输入数据保证在任何时候，等待队列中的进程不超过 $15000$ 个。

## 输出格式

按照进程结束的时间输出每个进程的进程号和结束时间。

## 样例

### 样例输入 #1
```
1 1 5 3 
2 10 5 1 
3 12 7 2 
4 20 2 3 
5 21 9 4 
6 22 2 4 
7 23 5 2 
8 24 2 4 

```
### 样例输出 #1
```
1 6
3 19
5 30
6 32
8 34
4 35
7 40
2 42

```


---

---
title: "[SCOI2010] 股票交易"
layout: "post"
diff: 提高+/省选-
pid: P2569
tag: ['动态规划 DP', '2010', '四川', '各省省选', '单调队列', '队列']
---
# [SCOI2010] 股票交易
## 题目描述

最近 $\text{lxhgww}$ 又迷上了投资股票，通过一段时间的观察和学习，他总结出了股票行情的一些规律。

通过一段时间的观察，$\text{lxhgww}$ 预测到了未来 $T$ 天内某只股票的走势，第 $i$ 天的股票买入价为每股 $AP_i$，第 $i$ 天的股票卖出价为每股 $BP_i$（数据保证对于每个 $i$，都有 $AP_i \geq BP_i$），但是每天不能无限制地交易，于是股票交易所规定第 $i$ 天的一次买入至多只能购买 $AS_i$ 股，一次卖出至多只能卖出 $BS_i$ 股。

另外，股票交易所还制定了两个规定。为了避免大家疯狂交易，股票交易所规定在两次交易（某一天的买入或者卖出均算是一次交易）之间，至少要间隔 $W$ 天，也就是说如果在第 $i$ 天发生了交易，那么从第 $i+1$ 天到第 $i+W$ 天，均不能发生交易。同时，为了避免垄断，股票交易所还规定在任何时间，一个人的手里的股票数不能超过 $\text{MaxP}$。

在第 $1$ 天之前，$\text{lxhgww}$ 手里有一大笔钱（可以认为钱的数目无限），但是没有任何股票，当然，$T$ 天以后，$\text{lxhgww}$ 想要赚到最多的钱，聪明的程序员们，你们能帮助他吗？


## 输入格式

输入数据第一行包括 $3$ 个整数，分别是 $T$，$\text{MaxP}$，$W$。

接下来 $T$ 行，第 $i$ 行代表第 $i-1$ 天的股票走势，每行 $4$ 个整数，分别表示 $AP_i,\ BP_i,\ AS_i,\ BS_i$。
## 输出格式

输出数据为一行，包括 $1$ 个数字，表示 $\text{lxhgww}$ 能赚到的最多的钱数。
## 样例

### 样例输入 #1
```
5 2 0
2 1 1 1
2 1 1 1
3 2 1 1
4 3 1 1
5 4 1 1

```
### 样例输出 #1
```
3
```
## 提示

- 对于 $30\%$ 的数据，$0\leq W<T\leq 50,1\leq\text{MaxP}\leq50$；
- 对于 $50\%$ 的数据，$0\leq W<T\leq 2000,1\leq\text{MaxP}\leq50$；
- 对于 $100\%$ 的数据，$0\leq W<T\leq 2000,1\leq\text{MaxP}\leq2000$；
- 对于所有的数据，$1\leq BP_i\leq AP_i\leq 1000,1\leq AS_i,BS_i\leq\text{MaxP}$。


---

---
title: "[USACO12MAR] Flowerpot S"
layout: "post"
diff: 提高+/省选-
pid: P2698
tag: ['2012', '二分', 'USACO', '单调队列']
---
# [USACO12MAR] Flowerpot S
## 题目描述

Farmer John has been having trouble making his plants grow, and needs your help to water them properly.  You are given the locations of N raindrops (1 <= N <= 100,000) in the 2D plane, where y represents vertical height of the drop, and x represents its location over a 1D number line:

 ![](https://cdn.luogu.com.cn/upload/pic/9174.png) 

Each drop falls downward (towards the x axis) at a rate of 1 unit per second.  You would like to place Farmer John's flowerpot of width W somewhere along the x axis so that the difference in time between the first raindrop to hit the flowerpot and the last raindrop to hit the flowerpot is at least some amount D (so that the flowers in the pot receive plenty of water).  A drop of water that lands just on the edge of the flowerpot counts as hitting the flowerpot. 

Given the value of D and the locations of the N raindrops, please compute the minimum possible value of W.

老板需要你帮忙浇花。给出 $N$ 滴水的坐标，$y$ 表示水滴的高度，$x$ 表示它下落到 $x$ 轴的位置。

每滴水以每秒 $1$ 个单位长度的速度下落。你需要把花盆放在 $x$ 轴上的某个位置，使得从被花盆接着的第 $1$ 滴水开始，到被花盆接着的最后 $1$ 滴水结束，之间的时间差至少为 $D$。

我们认为，只要水滴落到 $x$ 轴上，与花盆的边沿对齐，就认为被接住。给出 $N$ 滴水的坐标和 $D$ 的大小，请算出最小的花盆的宽度 $W$。
## 输入格式

第一行 $2$ 个整数 $N$ 和 $D$。

接下来 $N$ 行每行 $2$ 个整数，表示水滴的坐标 $(x,y)$。
## 输出格式

仅一行 $1$ 个整数，表示最小的花盆的宽度。如果无法构造出足够宽的花盆，使得在 $D$ 单位的时间接住满足要求的水滴，则输出 $-1$。
## 样例

### 样例输入 #1
```
4 5
6 3
2 4
4 10
12 15
```
### 样例输出 #1
```
2
```
## 提示

有 $4$ 滴水，$(6,3)$ ，$(2,4)$ ，$(4,10)$ ，$(12,15)$ 。水滴必须用至少 $5$ 秒时间落入花盆。花盆的宽度为 $2$ 是必须且足够的。把花盆放在 $x=4\dots6$ 的位置，它可以接到 $1$ 和 $3$ 水滴, 之间的时间差为 $10-3=7$ 满足条件。

**【数据范围】**

$40\%$ 的数据：$1 \le N \le 1000$ ，$1 \le D \le 2000$ 。

$100\%$ 的数据：$1 \le N \le 10 ^ 5$ ，$1 \le D \le 10 ^ 6$ ，$0\le x,y\le10^6$ 。


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
title: "[NOIP 2016 提高组] 蚯蚓"
layout: "post"
diff: 提高+/省选-
pid: P2827
tag: ['2016', '堆', 'NOIP 提高组', 'O2优化', '队列']
---
# [NOIP 2016 提高组] 蚯蚓
## 题目背景

NOIP2016 提高组 D2T2
## 题目描述

本题中，我们将用符号 $\lfloor c \rfloor$ 表示对 $c$ 向下取整，例如：$\lfloor 3.0 \rfloor = \lfloor 3.1 \rfloor = \lfloor 3.9 \rfloor = 3$。

蛐蛐国最近蚯蚓成灾了！隔壁跳蚤国的跳蚤也拿蚯蚓们没办法，蛐蛐国王只好去请神刀手来帮他们消灭蚯蚓。

蛐蛐国里现在共有 $n$ 只蚯蚓（$n$ 为正整数）。每只蚯蚓拥有长度，我们设第 $i$ 只蚯蚓的长度为 $a_i\,(i=1,2,\dots,n)$，并保证所有的长度都是非负整数（即：可能存在长度为 $0$ 的蚯蚓）。

每一秒，神刀手会在所有的蚯蚓中，准确地找到最长的那一只（如有多个则任选一个）将其切成两半。神刀手切开蚯蚓的位置由常数 $p$（是满足 $0 < p < 1$ 的有理数）决定，设这只蚯蚓长度为 $x$，神刀手会将其切成两只长度分别为 $\lfloor px \rfloor$ 和 $x - \lfloor px \rfloor$ 的蚯蚓。特殊地，如果这两个数的其中一个等于 $0$，则这个长度为 $0$ 的蚯蚓也会被保留。此外，除了刚刚产生的两只新蚯蚓，其余蚯蚓的长度都会增加 $q$（是一个非负整常数）。

蛐蛐国王知道这样不是长久之计，因为蚯蚓不仅会越来越多，还会越来越长。蛐蛐国王决定求助于一位有着洪荒之力的神秘人物，但是救兵还需要 $m$ 秒才能到来……（$m$ 为非负整数）

蛐蛐国王希望知道这 $m$ 秒内的战况。具体来说，他希望知道：

- $m$ 秒内，每一秒被切断的蚯蚓被切断前的长度（有 $m$ 个数）；
- $m$ 秒后，所有蚯蚓的长度（有 $n + m$ 个数）。

蛐蛐国王当然知道怎么做啦！但是他想考考你……
## 输入格式

第一行包含六个整数 $n,m,q,u,v,t$，其中：$n,m,q$ 的意义见【问题描述】；$u,v,t$ 均为正整数；你需要自己计算 $p=u / v$（保证 $0 < u < v$）；$t$ 是输出参数，其含义将会在【输出格式】中解释。

第二行包含 $n$ 个非负整数，为 $a_1, a_2, \dots, a_n$，即初始时 $n$ 只蚯蚓的长度。

同一行中相邻的两个数之间，恰好用一个空格隔开。

保证 $1 \leq n \leq 10^5$，$0 \leq m \leq 7 \times 10^6$，$0 < u < v \leq 10^9$，$0 \leq q \leq 200$，$1 \leq t \leq 71$，$0 \leq a_i \leq 10^8$。
## 输出格式

第一行输出 $\left \lfloor \frac{m}{t} \right \rfloor$ 个整数，按时间顺序，依次输出第 $t$ 秒，第 $2t$ 秒，第 $3t$ 秒，……被切断蚯蚓（在被切断前）的长度。

第二行输出 $\left \lfloor \frac{n+m}{t} \right \rfloor$ 个整数，输出 $m$ 秒后蚯蚓的长度；需要按从大到小的顺序，依次输出排名第 $t$，第 $2t$，第 $3t$，……的长度。

同一行中相邻的两个数之间，恰好用一个空格隔开。即使某一行没有任何数需要输出，你也应输出一个空行。

请阅读样例来更好地理解这个格式。
## 样例

### 样例输入 #1
```
3 7 1 1 3 1
3 3 2
```
### 样例输出 #1
```
3 4 4 4 5 5 6
6 6 6 5 5 4 4 3 2 2
```
### 样例输入 #2
```
3 7 1 1 3 2
3 3 2
```
### 样例输出 #2
```
4 4 5
6 5 4 3 2
```
### 样例输入 #3
```
3 7 1 1 3 9
3 3 2
```
### 样例输出 #3
```
//空行
2
```
## 提示

**样例解释 1**

在神刀手到来前：$3$ 只蚯蚓的长度为 $3,3,2$。

$1$ 秒后：一只长度为 $3$ 的蚯蚓被切成了两只长度分别为$1$ 和 $2$ 的蚯蚓，其余蚯蚓的长度增加了 $1$。最终 $4$ 只蚯蚓的长度分别为 $(1,2),4,3$。括号表示这个位置刚刚有一只蚯蚓被切断。

$2$ 秒后：一只长度为 $4$ 的蚯蚓被切成了 $1$ 和 $3$。$5$ 只蚯蚓的长度分别为：$2,3,(1,3),4$。

$3$ 秒后：一只长度为 $4$ 的蚯蚓被切断。$6$ 只蚯蚓的长度分别为：$3,4,2,4,(1,3)$。

$4$ 秒后：一只长度为 $4$ 的蚯蚓被切断。$7$ 只蚯蚓的长度分别为：$4,(1,3),3,5,2,4$。

$5$ 秒后：一只长度为 $5$ 的蚯蚓被切断。$8$ 只蚯蚓的长度分别为：$5,2,4,4,(1,4),3,5$。

$6$ 秒后：一只长度为 $5$ 的蚯蚓被切断。$9$ 只蚯蚓的长度分别为：$(1,4),3,5,5,2,5,4,6$。

$7$ 秒后：一只长度为 $6$ 的蚯蚓被切断。$10$ 只蚯蚓的长度分别为：$2,5,4,6,6,3,6,5,(2,4)$。所以，$7$ 秒内被切断的蚯蚓的长度依次为 $3,4,4,4,5,5,6$。$7$ 秒后，所有蚯蚓长度从大到小排序为 $6,6,6,5,5,4,4,3,2,2$。

**样例解释 2**

这个数据中只有 $t=2$ 与上个数据不同。只需在每行都改为每两个数输出一个数即可。

虽然第一行最后有一个 $6$ 没有被输出，但是第二行仍然要重新从第二个数再开始输出。

**样例解释 3**

这个数据中只有 $t=9$ 与上个数据不同。

注意第一行没有数要输出，但也要输出一个空行。


**数据范围**

![](https://cdn.luogu.com.cn/upload/pic/3458.png)



---

---
title: "[USACO07DEC] Best Cow Line G"
layout: "post"
diff: 提高+/省选-
pid: P2870
tag: ['字符串', '贪心', '2007', 'USACO', '队列']
---
# [USACO07DEC] Best Cow Line G
## 题目背景

*本题和 [2007 年 11 月月赛银组同名题目](/problem/P6140) 在题意上一致，唯一的差别是数据范围。*
## 题目描述

Farmer John 打算带领 $N$（$1 \leq N \leq 5 \times 10^5$）头奶牛参加一年一度的”全美农场主大奖赛“。在这场比赛中，每个参赛者必须让他的奶牛排成一列，然后带领这些奶牛从裁判面前依此走过。

今年，竞赛委员会在接受报名时，采用了一种新的登记规则：取每头奶牛名字的首字母，按照它们在队伍中的次序排成一列。将所有队伍的名字按字典序升序排序，从而得到出场顺序。

FJ 由于事务繁忙，他希望能够尽早出场。因此他决定重排队列。

他的调整方式是这样的：每次，他从原队列的首端或尾端牵出一头奶牛，将她安排到新队列尾部。重复这一操作直到所有奶牛都插入新队列为止。

现在请你帮 FJ 算出按照上面这种方法能排出的字典序最小的队列。
## 输入格式

第一行一个整数 $N$。

接下来 $N$ 行每行一个大写字母，表示初始队列。
## 输出格式

输出一个长度为 $N$ 的字符串，表示可能的最小字典序队列。

每输出 $80$ 个字母需要一个换行。
## 样例

### 样例输入 #1
```
6
A
C
D
B
C
B
```
### 样例输出 #1
```
ABCBCD
```


---

---
title: "[USACO09OPEN] Bovine Embroidery G"
layout: "post"
diff: 提高+/省选-
pid: P2950
tag: ['动态规划 DP', '递推', '2009', 'USACO', '单调队列']
---
# [USACO09OPEN] Bovine Embroidery G
## 题目描述

Bessie has taken up the detailed art of bovine embroidery. Cows embroider a cloth mounted in a circular hoop of integer radius d (1 <= d <= 50,000). They sew N (2 <= N <= 50,000) threads, each in a straight line from one point on the edge of the hoop to another point on the edge of the hoop (no two embroidered points share a location on the hoop's edge).

Being mathematically inclined, Bessie knows a formula of the form ax + by + c = 0 for each straight line piece of thread. Conveniently, a, b, and c are integers (-1,000,000 <= a <= 1,000,000; -1,000,000 <= b <= 1,000,000; -1,000,000 <= c <= 1,000,000). Even more

conveniently, no two threads coincide exactly.

Perhaps less conveniently, Bessie knows that her set of formula coefficients also includes a number of formulae for threads that do not appear to pass inside the hoop's circle. She regrets this greatly.

The origin (0,0) is in the precise middle of the hoop, so all points on the hoop's edge are distance d from the origin. At least one of the coefficients a and b is non-zero for each thread's formula.

Bovine embroidery is more highly regarded when the number of thread intersections is maximized. Help Bessie: count the number of pairs of threads that intersect on the cloth (i.e., within distance d of the origin). Note that if three threads happen to coincide at the same point, that would be three pairs of intersections. Four threads at the same point -> six pairs of intersections, etc.

Bessie学会了刺绣这种精细的工作。牛们在一片半径为d(1 <= d <= 50000)的圆形布上绣花. 它们一共绣了N (2 <= N <= 50000)条直线，每条直线连接布的边缘上的两个点(没有两条线通过边上同一个点)。

作为一只热爱数学的牛，Bessie 知道每条线的公式, ax + by + c = 0. a, b, 和 c 为整数(-1000000 <= a <= 1000000; -1000000 <= b <= 1000000; -1000000 <= c <= 1000000).没有两条线完全重合。

不幸的是, 一部分线不通过圆布的内部. 原点(0,0)在布的正中央, 所有边上的点离原点距离为d. 每条线的公式满足至少a,b中的一个非零. 对于牛来说，刺绣作品中线的交点越多，便越有价值。帮助Bessie计算在圆中相交的线的对数，也就是说交点与原点的距离小于d。注意如果三条线在圆内同一点相交,这算3对线。4线共点->6对线.

## 输入格式

\* Line 1: Two space-separated integers: N and d

\* Lines 2..N+1: Line i+1 describes thread i with three integers: a, b, and c

## 输出格式

\* Line 1: One integer, on a line by itself, that is the count of pairs of threads that intersect.

## 样例

### 样例输入 #1
```
2 1 
1 0 0 
0 1 0 

```
### 样例输出 #1
```
1 

```
## 提示

The two lines are x=0 and y=0. 

The two lines intersect at (0,0), which is clearly with 1 of the origin. 




---

---
title: "[USACO11OPEN] Odd degrees G"
layout: "post"
diff: 提高+/省选-
pid: P3022
tag: ['动态规划 DP', '2011', 'USACO', '单调队列', 'Special Judge']
---
# [USACO11OPEN] Odd degrees G
## 题目描述

The cows are being invaded! Their republic comprises N (1 <= N <= 50,000) towns that are connected by M (1 <= M <= 100,000) undirected paths between two towns A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i; no duplicate paths will occur). However the republic is not necessarily connected--there may be pairs of towns that are unable to reach each other through the paths.

The cows know their invaders plan to conduct an inventory of every path within their republic, so they are willing to shut down various paths to make it as difficult as possible for their invaders to do so.

Please help the cows find a way to shut down a subset of the paths such that each town has an odd number of remaining paths connected to it, or determine if no such subset exists.

For example, consider the following cow republic: 

1---2
\ /
3---4
If we keep the paths 1-3, 2-3, and 3-4, and remove the path 1-2, then towns 1, 2, and 4 will be an endpoint of exactly one path, whereas town 3 will be an endpoint of three paths:

1   2
\ /
3---4
## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..M+1: Line i+1 contains two space-separated integers: A\_i and B\_i

## 输出格式

\* Line 1: A single integer that is the number of paths to keep. If no subset exists output only a single line with the integer -1.

\* Lines 2..K+1: Each line contains an index of an path to keep, in the range 1..M. These indices must be pairwise distinct.

## 样例

### 样例输入 #1
```
4 4 
1 2 
2 3 
3 1 
3 4 

```
### 样例输出 #1
```
3 
2 
3 
4 

```
## 提示

感谢@cn：苏卿念 提供的Special Judge
## 题目翻译

## 题意
牛们正在被入侵。 有$N$个点，由$M$条无向边连接。 无向边从$A_i$到$B_i$。数据保证无重边，但不保证连通(即从一个点不一定能到达另一点)。

牛知道入侵他们的人正计划清点所有的边，所以他们想切掉一些边使入侵者的计划尽可能的困难

请找出一个方法，留下一些边，使每个点都只有奇数条边与之连接。并输出留下的边的方案。

下面是一个样例
```
1---2
 \ /
  3---4
我们把1——2那条边拆掉， 就会变成下图
1   2
 \ /
  3---4
对于每个点都只有奇数条边连接，符合题意
```
## 读入输出格式
 ### 读入格式
 * 第一行两个整数 $N$ 和 $M$
 * 第二到$M+1$行，每行描述一条边 有两个整数$A_i$和$B_i$
 ### 输出格式
 * 第一行一个整数 剩下边的数量，如果不可能请输出-1
 * 之后每一行一个数，边的编号(按输入顺序来)。

感谢@ToBiChi 提供翻译


---

---
title: "[USACO13JAN] Cow Lineup G"
layout: "post"
diff: 提高+/省选-
pid: P3069
tag: ['2013', 'USACO', '树状数组', '单调队列', '队列']
---
# [USACO13JAN] Cow Lineup G
## 题目描述

Farmer John's N cows (1 <= N <= 100,000) are lined up in a row.  Each cow is identified by an integer "breed ID" in the range 0...1,000,000,000; the breed ID of the ith cow in the lineup is B(i).  Multiple cows can share the same breed ID.

FJ thinks that his line of cows will look much more impressive if there is a large contiguous block of cows that all have the same breed ID.  In order to create such a block, FJ chooses up to K breed IDs and removes from his lineup all the cows having those IDs.  Please help FJ figure out the length of the largest consecutive block of cows with the same breed ID that he can create by doing this.

农夫约翰的N(1 <= N <= 100,000)只奶牛排成了一队，每只牛都用编上了一个“血统编号”，该编号为范围0...1,000,000,000的整数。血统相同的奶牛有相同的编号，也就是可能有多头奶牛是相同的"血统编号"。

约翰觉得如果连续排列的一段奶牛有相同的血统编号的话，奶牛们看起来会更具有威猛。为了创造这样的连续段，约翰最多能选出k种血统的奶牛，并把他们全部从队列中赶走。


请帮助约翰计算这样做能得到的由相同血统编号的牛构成的连续段的长度最大是多少？

## 输入格式

\* Line 1: Two space-separated integers: N and K.

\* Lines 2..1+N: Line i+1 contains the breed ID B(i). 


## 输出格式

\* Line 1: The largest size of a contiguous block of cows with

identical breed IDs that FJ can create.

## 样例

### 样例输入 #1
```
9 1 
2 
7 
3 
7 
7 
3 
7 
5 
7 

```
### 样例输出 #1
```
4 

```
## 提示

There are 9 cows in the lineup, with breed IDs 2, 7, 3, 7, 7, 3, 7, 5, 7. FJ would like to remove up to 1 breed ID from this lineup.


By removing all cows with breed ID 3, the lineup reduces to 2, 7, 7, 7, 7, 5, 7.  In this new lineup, there is a contiguous block of 4 cows with the same breed ID (7).



---

---
title: "[USACO13NOV] Pogo-Cow S"
layout: "post"
diff: 提高+/省选-
pid: P3089
tag: ['动态规划 DP', '2013', 'USACO', '单调队列', '枚举']
---
# [USACO13NOV] Pogo-Cow S
## 题目描述

In an ill-conceived attempt to enhance the mobility of his prize cow Bessie, Farmer John has attached a pogo stick to each of Bessie's legs. Bessie can now hop around quickly throughout the farm, but she has not yet learned how to slow down.

To help train Bessie to hop with greater control, Farmer John sets up a practice course for her along a straight one-dimensional path across his farm.  At various distinct positions on the path, he places N targets on which Bessie should try to land (1 <= N <= 1000).  Target i is located at position x(i), and is worth p(i) points if Bessie lands on it.  Bessie starts at the location of any target of her choosing and is allowed to move in only one direction, hopping from target to target.  Each hop must cover at least as much distance as the previous hop, and must land on a target.

Bessie receives credit for every target she touches (including the initial target on which she starts).  Please compute the maximum number of points she can obtain.

FJ给奶牛贝西的脚安装上了弹簧，使它可以在农场里快速地跳跃，但是它还没有学会如何降低速度。


FJ觉得让贝西在一条直线的一维线路上进行练习，他在不同的目标点放置了N (1 <= N <= 1000)个目标点，目标点i在目标点x(i)，该点得分为p(i)。贝西开始时可以选择站在一个目标点上，只允许朝一个方向跳跃，从一目标点跳到另外一个目标点，每次跳跃的距离至少和上一次跳跃的距离相等，并且必须跳到一个目标点。


每跳到一个目标点，贝西可以拿到该点的得分，请计算他的最大可能得分。

## 输入格式

\* Line 1: The integer N.

\* Lines 2..1+N: Line i+1 contains x(i) and p(i), each an integer in the range 0..1,000,000.

## 输出格式

\* Line 1: The maximum number of points Bessie can receive.

## 样例

### 样例输入 #1
```
6 
5 6 
1 1 
10 5 
7 6 
4 8 
8 10 

```
### 样例输出 #1
```
25 

```
## 提示

There are 6 targets.  The first is at position x=5 and is worth 6 points, and so on.


Bessie hops from position x=4 (8 points) to position x=5 (6 points) to position x=7 (6 points) to position x=10 (5 points).



---

---
title: "[USACO13NOV] No Change G"
layout: "post"
diff: 提高+/省选-
pid: P3092
tag: ['2013', 'USACO', '单调队列', '状压 DP']
---
# [USACO13NOV] No Change G
## 题目描述

Farmer John is at the market to purchase supplies for his farm.  He has in his pocket K coins (1 <= K <= 16), each with value in the range 1..100,000,000.  FJ would like to make a sequence of N purchases (1 <= N <= 100,000), where the ith purchase costs c(i) units of money (1 <= c(i) <= 10,000).  As he makes this sequence of purchases, he can periodically stop and pay, with a single coin, for all the purchases made since his last payment (of course, the single coin he uses must be large enough to pay for all of these).  Unfortunately, the vendors at the market are completely out of change, so whenever FJ uses a coin that is larger than the amount of money he owes, he sadly receives no changes in return!

Please compute the maximum amount of money FJ can end up with after making his N purchases in sequence.  Output -1 if it is impossible for FJ to make all of his purchases.

约翰到商场购物，他的钱包里有K(1 <= K <= 16)个硬币，面值的范围是1..100,000,000。

约翰想按顺序买 N个物品(1 <= N <= 100,000)，第i个物品需要花费c(i)块钱，(1 <= c(i) <= 10,000)。

在依次进行的购买N个物品的过程中，约翰可以随时停下来付款，每次付款只用一个硬币，支付购买的内容是从上一次支付后开始到现在的这些所有物品（前提是该硬币足以支付这些物品的费用）。不幸的是，商场的收银机坏了，如果约翰支付的硬币面值大于所需的费用，他不会得到任何找零。

请计算出在购买完N个物品后，约翰最多剩下多少钱。如果无法完成购买，输出-1

## 输入格式

\* Line 1: Two integers, K and N.

\* Lines 2..1+K: Each line contains the amount of money of one of FJ's coins.

\* Lines 2+K..1+N+K: These N lines contain the costs of FJ's intended purchases.

## 输出格式

\* Line 1: The maximum amount of money FJ can end up with, or -1 if FJ cannot complete all of his purchases.

## 样例

### 样例输入 #1
```
3 6 
12 
15 
10 
6 
3 
3 
2 
3 
7 

```
### 样例输出 #1
```
12 

```
## 提示

FJ has 3 coins of values 12, 15, and 10.  He must make purchases in sequence of value 6, 3, 3, 2, 3, and 7.


FJ spends his 10-unit coin on the first two purchases, then the 15-unit coin on the remaining purchases.  This leaves him with the 12-unit coin.



---

---
title: "[USACO15JAN] Cow Rectangles G"
layout: "post"
diff: 提高+/省选-
pid: P3117
tag: ['2015', 'USACO', '单调队列', '离散化', '前缀和', '扫描线']
---
# [USACO15JAN] Cow Rectangles G
## 题目描述

The locations of Farmer John's N cows (1 <= N <= 500) are described by distinct points in the 2D plane.  The cows belong to two different breeds: Holsteins and Guernseys.  Farmer John wants to build a rectangular fence with sides parallel to the coordinate axes enclosing only Holsteins, with no Guernseys (a cow counts as enclosed even if it is on the boundary of the fence).  Among all such fences, Farmer John wants to build a fence enclosing the maximum number of Holsteins.  And among all these fences, Farmer John wants to build a fence of minimum possible area.  Please determine this area.  A fence of zero width or height is allowable.

## 输入格式

The first line of input contains N.  Each of the next N lines describes a cow, and contains two integers and a character. The integers indicate a point (x,y) (0 <= x, y <= 1000) at which the cow is located. The character is H or G, indicating the cow's breed.  No two cows are located at the same point, and there is always at least one Holstein.

## 输出格式

Print two integers. The first line should contain the maximum number of Holsteins that can be enclosed by a fence containing no Guernseys, and second line should contain the minimum area enclosed by such a fence.
## 样例

### 样例输入 #1
```
5 
1 1 H 
2 2 H 
3 3 G 
4 4 H 
6 6 H 

```
### 样例输出 #1
```
2 
1 
```
## 题目翻译

### 题目描述

农夫约翰的 $N$ 头牛（$1 \leq N \leq 500$）的位置由二维平面上互不相同的点描述。这些牛分为两个品种：Holsteins 和 Guernseys。农夫约翰希望建造一个边与坐标轴平行的矩形围栏，仅包含 Holsteins 且不包含任何 Guernseys（即使牛位于围栏边界上也视为被包含）。在所有满足条件的围栏中，农夫约翰希望选择包含最多 Holsteins 的围栏。若存在多个这样的围栏，则选择其中面积最小的一个。请确定这个面积。允许围栏的宽度或高度为零。

### 输入格式

第一行输入包含 $N$。接下来的 $N$ 行每行描述一头牛，包含两个整数和一个字符。整数表示牛所在点的坐标 $(x, y)$（$0 \leq x, y \leq 1000$），字符为 H 或 G 表示牛的品种。没有两头牛位于同一位置，且至少存在一头 Holstein。

### 输出格式

输出两个整数。第一行应包含不包含任何 Guernseys 的围栏能包围的最大 Holsteins 数量，第二行应包含满足该条件的围栏的最小面积。


---

---
title: "仓鼠窝"
layout: "post"
diff: 提高+/省选-
pid: P3400
tag: ['单调队列', '洛谷原创', '洛谷月赛']
---
# 仓鼠窝
## 题目描述

萌萌哒的 Created equal 是一只小仓鼠，小仓鼠自然有仓鼠窝啦。

仓鼠窝是一个由 $n\times m$ 个格子组成的行数为 $n$、列数为 $m$ 的矩阵。小仓鼠现在想要知道，这个矩阵中有多少个子矩阵。

比如说有一个 $2\times 3$ 的矩阵，那么 $1\times 1$ 的子矩阵有 $6$ 个，$1\times 2$ 的子矩阵有 $4$ 个，$1\times 3$ 的子矩阵有 $2$ 个，$2\times 1$ 的子矩阵有 $3$ 个，$2\times 2$ 的子矩阵有 $2$ 个，$2\times 3$ 的子矩阵有 $1$ 个，所以子矩阵共有 $6+4+2+3+2+1=18$ 个。

可是仓鼠窝中有的格子被破坏了。现在小仓鼠想要知道，有多少个内部不含被破坏的格子的子矩阵。

## 输入格式

第一行两个正整数 $n$ 和 $m$，分别表示仓鼠窝的行数 $n$，列数 $m$。

接下来 $n$ 行，每行 $m$ 个数，每个数代表对应的格子，非 $0$ 即 $1$。若为 $0$，表示这个格子被破坏；反之代表这个格子是完好无损的。
## 输出格式

仅一个正整数，表示未被破坏的子矩阵的个数。

## 样例

### 样例输入 #1
```
3 4
1 1 1 1
1 0 1 1
1 1 0 1
```
### 样例输出 #1
```
26
```
## 提示

本题时限 $2\text{s}$，内存限制 $256\text{M}$，因新评测机速度较为接近 NOIP 评测机速度，请注意常数问题带来的影响。

|    数据编号     |     $n$       |     $m$      |        特殊性质        |
| :------------: | :-----------: | :----------: | :--------------------: |
|     $1, 2, 3$    |       $2$       |       $2$      |           无           |
|        $4$       |      $10$       |      $10$      |           无           |
|      $5, 6$      |      $2000$     |     $2000$     |   所有格子均未被破坏     |
|        $7$       |      $2500$     |     $3000$     |  有且仅有一个格子被破坏  |
|        $8$       |      $3000$     |     $2500$     |  有且仅有一个格子被破坏  |
|        $9$       |       $200$     |      $200$     |           无           |
|   $10, 11, 12$   |       $500$     |      $500$     |           无           |
|     $13, 14$     |      $1000$     |     $1000$     |           无           |
|       $15$       |      $1000$     |     $1500$     |           无           |
|       $16$       |      $2500$     |     $2500$     |           无           |
|       $17$       |      $2500$     |     $3000$     |           无           |
|       $18$       |      $3000$     |     $2500$     |           无           |
|     $19, 20$     |      $3000$     |     $3000$     |           无           |


---

---
title: "[POI 2005] SAM-Toy Cars"
layout: "post"
diff: 提高+/省选-
pid: P3419
tag: ['贪心', '2005', 'POI（波兰）', '优先队列', '队列']
---
# [POI 2005] SAM-Toy Cars
## 题目描述

Jasio 是一个只有三岁的小男孩，他喜欢玩玩具车。他有 $n$ 辆玩具车被保存在书架上。

架子上的玩具车 Jasio 拿不到，但地板上的他可以拿到。Jasio 的母亲会帮 Jasio 拿架子上的玩具车到地板上。

地板最多只能放 $k$ 辆玩具车。

当地板已经放了 $k$ 辆玩具车时，Jasio 的母亲都会从地板上先拿走一个玩具车放回书架，再拿来 Jasio 想要的玩具车。

现在 Jasio 一共想依次玩 $p$ 个玩具车，问 Jasio 的母亲最少需要拿几次玩具车。（只算拿下来的，不算拿上去的）
## 输入格式

第一行三个整数 $n,k$ 和 $p$。

接下来 $p$ 行，每一行有且仅有一个整数 $a_i$，表示 Jasio 想玩的玩具玩家车编号。
## 输出格式

输出一行一个整数，表示最少 Jasio 的母亲最少需要拿玩家车的次数。
## 样例

### 样例输入 #1
```
3 2 7
1
2
3
1
3
1
2
```
### 样例输出 #1
```
4
```
## 提示

对于 $100\%$ 的数据：$1\le k\le n\le 10^5$，$1\le p\le 5\times 10^5$，$1\le a_i\le n$。


---

---
title: "[POI 2005] LOT-A Journey to Mars"
layout: "post"
diff: 提高+/省选-
pid: P3422
tag: ['2005', '单调队列', 'POI（波兰）', '前缀和']
---
# [POI 2005] LOT-A Journey to Mars
## 题目背景

Byteazar 决定去火星参加一个空间站旅行。
## 题目描述

火星的所有空间站都位于一个圆上，Byteazar 在其中一个空间站登陆然后开始绕圈旅行。  

旅行需要耗费油料，一升油料只能跑 $1$ 米，每个空间站可以补给的油料都有所不同。 

Byteazar 每到一个空间站便可以把该空间站的油料全部拿走（他的油箱是没有容量限制的）。但是如果走到某个时候突然没油了那么旅行便失败了。

Byteazar 需要决定要在哪个地方登陆使得他能顺利访问完所有的空间站后回到他当初登陆的地方，他登陆后可以选择两个方向中的任意一个进行旅行。
## 输入格式

第一行一个整数 $n$，代表空间站数量，所有空间站由 $1$ 至 $n$ 进行标号。

之后 $n$ 行，每行两个整数 $p_i,d_i$，第 $i + 1$ 行描述了第 $i$ 号空间站的信息，其中 $p_i$ 表示该空间站可以补给的油量，$d_i$ 则指明了它到 $i+1$ 号空间站的距离，对于 $n$ 号空间站，$d_i$ 表示它和 $1$ 号空间站的距离。
## 输出格式

输出 $n$ 行，每行一个字符串 `TAK` 或 `NIE`。

若你认为在 $i$ 号空间站登陆是可行的，则需要在第 $i$ 行输出 `TAK`，否则输出 `NIE`。
## 样例

### 样例输入 #1
```
5
3 1
1 2
5 2
0 1
5 4

```
### 样例输出 #1
```
TAK
NIE
TAK
NIE
TAK
```
## 提示

### 数据规模与约定

对于 $100\%$ 的数据，$3\le n\le10^6$，$p_i\ge0$，$d_i>0$，$\sum d_i\le2\times10^9$。


---

---
title: "[POI 2009] ARC-Architects"
layout: "post"
diff: 提高+/省选-
pid: P3487
tag: ['2009', '单调队列', 'POI（波兰）']
---
# [POI 2009] ARC-Architects
## 题目描述

给定一个序列 $a_i$（$1\leq a_i\leq 10^9$）且 $1\leq i\le n$ 且 $n\leq  
 1.5\times 10^7$，和一个整数 $k$（$k\leq n$ 且 $k\leq 10^6$），求出 $a$ 的一个长度为 $k$ 的子序列 $a_{b_i}$ 满足：

1. $1\leq b_1\leq b_2\leq \ldots\leq b_k$
2. 在满足 $1$ 的情况下 $a_{b_1}, a_{b_2},\ldots , a_{b_k}$ 字典序最大。

## 输入格式

第一行一个数 $k$，以下一行，为序列 $a_i$。以一个单独的 $0$ 结束。

## 输出格式

$k$ 行，每行一个数，其中第 $i$ 行为 $a_{b_i}$。

## 样例

### 样例输入 #1
```
3
12 5 8 3 15 8 0
```
### 样例输出 #1
```
12
15
8
```
## 提示

本题原为交互题，为评测方便，需要将下面的代码粘贴到文件中。

将第一次输入改为 `=inicjuj()` 形式，将之后的每一次输入改为 `=wczytaj()` 形式，将输出改为 `wypisz(jakoscProjektu)` 形式（`jakoscProjektu` 代表你输出的数）。

```cpp
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAGIC_BEGIN -435634223
#define MAGIC_END -324556462

#define MIN_K 1
#define MAX_K 1000000
#define MAX_N 15000000
#define MIN_A 1
#define MAX_A 1000000000
#define MIN_TYP 1
#define MAX_TYP 3
#define MIN_PAR 0
#define MAX_PAR 1000000000

#define ERROR 0
#define CORRECT 1

#define unlikely(x) __builtin_expect(!!(x), 0)

static int init = 0; // czy zostala juz wywolana funkcja inicjuj()
static int lib_n; // ile biblioteka podala juz liczb
static int con_k; // ile zawodnik podal liczb

static int N, K, A, TYP, PAR; // parametry testu wczytywane z pliku
static int bre, len_sub, bou, is_end; // zmienne pomocnicze

static int rand2_status = 198402041;

static inline int rand2(int a, int b){
  rand2_status = rand2_status * 1103515245ll + 12345;
  int x = rand2_status;
  if (x < 0) x = -x; // -2^31 sie nie zdarza :D
  x >>= 1;
  x = a + x % (b - a + 1);
  return x;
}

/* test losowy */
static inline int random_test()
{
    return rand2(1, A);
}

/* test z dlugim podciagiem nierosnacym */
static inline int decreasing_test()
{
    int tmp;
    if(bre == 0) {
        bre = rand2(0, (N - lib_n + 1 - len_sub));
        tmp = A;
        A -= rand2(0, (A - 1) / len_sub);
        len_sub--;
    }
    else {
        bre--;
        tmp = rand2(1, A);
    }
    return tmp;
}

/* test z dlugim podciagiem niemalejacym */
static inline int increasing_test()
{
    return bou - decreasing_test();
}

static void finish(int res, const char com[])
{
    if(res == ERROR)
        printf("%s\n", com);
    exit(0);
}

/* Inicjuje dane wejsciowe i zwraca liczbe projektow */
int inicjuj()
{
    if(init == 1)
        finish(ERROR, "Program zawodnika moze wywolac funkcje inicjuj tylko raz!!!");
    init = 1;
    scanf("%d", &K);
    if (K > 0){
      TYP = 0;
      N = MAX_N + 2;
      return K;
    }
    int magic_begin, magic_end;
    scanf("%d%d", &magic_begin, &TYP);
    if(magic_begin != MAGIC_BEGIN || TYP < MIN_TYP || TYP > MAX_TYP)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    scanf("%d%d%d%d", &N, &K, &A, &PAR);
    if(N < 1 || N > MAX_N || N < K || K > MAX_K || A < MIN_A || A > MAX_A 
        || PAR < MIN_PAR || PAR > MAX_PAR)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    scanf("%d", &magic_end);
    if(magic_end != MAGIC_END)
        finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    con_k = 0;
    lib_n = 0;
    is_end = 0;
    if(TYP == 2 || TYP == 3) {
        len_sub = PAR;
        bre = 0;
    }
    if(TYP == 2)
        bou = A--;
    return K;
}

/* Sluzy do wczytania ciagu reprezentujacego jakosci projektow */
int wczytaj()
{
    if(unlikely(init == 0))
        finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    if(unlikely(lib_n > N || is_end == 1))
        finish(ERROR, "Program zawodnika wywolal funkcje wczytaj po otrzymaniu informacji o koncu ciagu!!!");
    if(unlikely(lib_n == N))
        return 0;
    lib_n++;
    switch (TYP) {
      case 0:
        scanf("%d", &A);
        if(A == 0)
          is_end = 1;
        return A;
        break;
      case 1: return random_test(); break;
      case 2: return increasing_test(); break;
      case 3: return decreasing_test(); break;
      default:
              finish(ERROR, "Nieznany typ testu");
    }
    return -1;
}

/* Sluzy do wypisania wyznaczonego podciagu */
void wypisz(int jakoscProjektu)
{
    if(init == 0)
        finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    printf("%d\n", jakoscProjektu);
    if(++con_k == K)
        finish(CORRECT, "");
}
```


---

---
title: "[POI 2014] PTA-Little Bird"
layout: "post"
diff: 提高+/省选-
pid: P3572
tag: ['动态规划 DP', '2014', '单调队列', 'POI（波兰）']
---
# [POI 2014] PTA-Little Bird
## 题目描述

In the Byteotian Line Forest there are $n$ trees in a row.

On top of the first one, there is a little bird who would like to fly over to the top of the last tree.

Being in fact very little, the bird might lack the strength to fly there without any stop.

If the bird is sitting on top of the tree no. i, then in a single flight leg it can fly toany of the trees no. $i+1,i+2,\cdots,i+k$, and then has to rest afterward.

Moreover, flying up is far harder to flying down.  A flight leg is tiresome if it ends in a tree at leastas high as the one where is started.  Otherwise the flight leg is not tiresome.

The goal is to select the trees on which the little bird will land so that the overall flight is leasttiresome, i.e., it has the minimum number of tiresome legs.

We note that birds are social creatures, and our bird has a few bird-friends who would also like to getfrom the first tree to the last one.  The stamina of all the birds varies,so the bird's friends may have different values of the parameter $k$.

Help all the birds, little and big!
## 输入格式

There is a single integer $n$ ($2\le n\le 1\ 000\ 000$) in the first line of the standard input:

the number of trees in the Byteotian Line Forest.

The second line of input holds $n$ integers $d_1,d_2,\cdots,d_n$ ($1\le d_i\le 10^9$)separated by single spaces: $d_i$ is the height of the i-th tree.

The third line of the input holds a single integer $q$ ($1\le q\le 25$): the number of birds whoseflights need to be planned.

The following $q$ lines describe these birds: in the $i$-th of these lines, there is an integer $k_i$ ($1\le k_i\le n-1$) specifying the $i$-th bird's stamina. In other words, the maximum number of trees that the $i$-th bird can pass before it has to rest is $k_i-1$.

## 输出格式

Your program should print exactly $q$ lines to the standard output.

In the $i$-th line, it should specify the minimum number of tiresome flight legs of the $i$-th bird.

## 样例

### 样例输入 #1
```
9
4 6 3 6 3 7 2 6 5
2
2
5

```
### 样例输出 #1
```
2
1

```
## 题目翻译

有 $n$ 棵树排成一排，第 $i$ 棵树的高度是 $d_i$。

有 $q$ 只鸟要从第 $1$ 棵树到第 $n$ 棵树。

当第 $i$ 只鸟在第 $j$ 棵树时，它可以飞到第 $j+1, j+2, \cdots, j+k_i$ 棵树。

如果一只鸟飞到一颗高度大于等于当前树的树，那么它的劳累值会增加 $1$，否则不会。

由于这些鸟已经体力不支，所以它们想要最小化劳累值。

### 输入格式

第一行输入 $n$。

第二行 $n$ 个数，第 $i$ 个数表示 $d_i$。

第三行输入 $q$。

接下来 $q$ 行，每一行一个整数，第 $i$ 行的整数为 $k_i$。

### 输出格式

共 $q$ 行，每一行输出第 $i$ 只鸟的最小劳累值。

### 数据范围

$1 \le n \le 10^6$，$1 \le d_i \le 10^9$，$1 \le q \le 25$，$1 \le k_i \le n - 1$。



---

---
title: "[POI 2015] WIL"
layout: "post"
diff: 提高+/省选-
pid: P3594
tag: ['动态规划 DP', '2015', '单调队列', 'POI（波兰）']
---
# [POI 2015] WIL
## 题目描述

给定一个长度为 $n$ 的序列，你有一次机会选中一段连续的长度不超过 $d$ 的区间，将里面所有数字全部修改为 $0$。请找到最长的一段连续区间，使得该区间内所有数字之和不超过 $p$。
## 输入格式

输入的第一行包含三个整数，分别代表 $n,p,d$。

第二行包含 $n$ 个整数，第 $i$ 个整数代表序列中第 $i$ 个数 $w_i$。
## 输出格式

包含一行一个整数，即修改后能找到的最长的符合条件的区间的长度。

## 样例

### 样例输入 #1
```
9 7 2
3 4 1 9 4 1 7 1 3
```
### 样例输出 #1
```
5
```
## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1 \le d \le n \le 2 \times 10^6$，$0 \le p \le 10^{16}$，$1 \leq w_i \leq 10^9$。

----

原题名称：Wilcze doły。


---

---
title: "[USACO17JAN] Cow Navigation G"
layout: "post"
diff: 提高+/省选-
pid: P3610
tag: ['2017', 'USACO', '广度优先搜索 BFS', '栈', '队列']
---
# [USACO17JAN] Cow Navigation G
## 题目描述

Bessie has gotten herself stuck on the wrong side of Farmer John's barn again, and since her vision is so poor, she needs your help navigating across the barn.

The barn is described by an $N \times N$ grid of square cells ($2 \leq N \leq 20$), some being empty and some containing impassable haybales. Bessie starts in the lower-left corner (cell 1,1) and wants to move to the upper-right corner (cell $N,N$). You can guide her by telling her a sequence of instructions, each of which is either "forward", "turn left 90 degrees", or "turn right 90 degrees". You want to issue the shortest sequence of instructions that will guide her to her destination. If you instruct Bessie to move off the grid (i.e., into the barn wall) or into a haybale, she will not move and will skip to the next command in your sequence.

Unfortunately, Bessie doesn't know if she starts out facing up (towards cell 1,2) or right (towards cell 2,1). You need to give the shortest sequence of directions that will guide her to the goal regardless of which case is true. Once she reaches the goal she will ignore further commands.


## 输入格式

The first line of input contains $N$.

Each of the $N$ following lines contains a string of exactly $N$ characters, representing the barn. The first character of the last line is cell 1,1. The last character of the first line is cell N, N.

Each character will either be an H to represent a haybale or an E to represent an empty square.

It is guaranteed that cells 1,1 and $N,N$ will be empty, and furthermore it is guaranteed that there is a path of empty squares from cell 1,1 to cell $N, N$.

## 输出格式

On a single line of output, output the length of the shortest sequence of directions that will guide Bessie to the goal, irrespective whether she starts facing up or right.

## 样例

### 样例输入 #1
```
3
EHE
EEE
EEE
```
### 样例输出 #1
```
9
```
## 题目翻译

### 题目描述

Bessie 又一次被困在了 Farmer John 的谷仓的错误一侧，由于她的视力很差，她需要你的帮助来穿过谷仓。

谷仓由一个 $N \times N$ 的方格网格描述（$2 \leq N \leq 20$），其中一些格子是空的，另一些则包含无法通过的干草堆。Bessie 从左下角（格子 1,1）开始，想要移动到右上角（格子 $N,N$）。你可以通过告诉她一系列指令来引导她，每条指令可以是“前进”、“向左转 90 度”或“向右转 90 度”。你需要给出最短的指令序列，以引导她到达目的地。如果你指示 Bessie 移动到网格外（即撞到谷仓墙壁）或进入干草堆，她将不会移动，并跳过你序列中的下一条指令。

不幸的是，Bessie 不知道她最初是面朝上（朝向格子 1,2）还是面朝右（朝向格子 2,1）。你需要给出一个最短的指令序列，无论她最初面朝哪个方向，都能引导她到达目标。一旦她到达目标，她将忽略后续的指令。

### 输入格式

输入的第一行包含 $N$。

接下来的 $N$ 行每行包含一个长度为 $N$ 的字符串，表示谷仓。最后一行的第一个字符是格子 1,1，第一行的最后一个字符是格子 $N,N$。

每个字符要么是 H 表示干草堆，要么是 E 表示空方格。

保证格子 1,1 和 $N,N$ 是空的，并且保证存在一条从格子 1,1 到格子 $N,N$ 的空方格路径。

### 输出格式

输出一行，表示无论 Bessie 最初面朝哪个方向，都能引导她到达目标的最短指令序列的长度。


---

---
title: "[APIO/CTSC2007] 数据备份"
layout: "post"
diff: 提高+/省选-
pid: P3620
tag: ['贪心', '2007', 'APIO', '优先队列', '差分', 'CTSC/CTS']
---
# [APIO/CTSC2007] 数据备份
## 题目描述

你在一家 IT 公司为大型写字楼或办公楼的计算机数据做备份。然而数据备份的工作是枯燥乏味的，因此你想设计一个系统让不同的办公楼彼此之间互相备份，而你则坐在家中尽享计算机游戏的乐趣。

已知办公楼都位于同一条街上。你决定给这些办公楼配对（两个一组）。每一对办公楼可以通过在这两个建筑物之间铺设网络电缆使得它们可以互相备份。

然而，网络电缆的费用很高。当地电信公司仅能为你提供 $K$ 条网络电缆，这意味着你仅能为 $K$ 对办公楼（或总计 $2K$ 个办公楼）安排备份。任一个办公楼都属于唯一的配对组（换句话说，这 $2K$ 个办公楼一定是相异的）。

此外，电信公司需按网络电缆的长度（公里数）收费。因而，你需要选择这 $K$ 对办公楼使得电缆的总长度尽可能短。换句话说，你需要选择这 $K$ 对办公楼，使得每一对办公楼之间的距离之和（总距离）尽可能小。

下面给出一个示例，假定你有 $5$ 个客户，其办公楼都在一条街上，如下图所示。这 $5$ 个办公楼分别位于距离大街起点 $1\rm km$, $3\rm km$, $4\rm km$, $6\rm km$ 和 $12\rm km$ 处。电信公司仅为你提供 $K=2$ 条电缆。

  ![](https://cdn.luogu.com.cn/upload/pic/4386.png) 

上例中最好的配对方案是将第 $1$ 个和第 $2$ 个办公楼相连，第 $3$ 个和第 $4$ 个办公楼相连。这样可按要求使用 $K=2$ 条电缆。第 $1$ 条电缆的长度是 $\rm 3km-1km = 2km$，第 2 条电缆的长度是 $\rm 6km―4km = 2 km$。这种配对方案需要总长 $4\rm km$ 的网络电缆，满足距离之和最小的要求。
## 输入格式

输入文件的第一行包含整数 $N$ 和 $K$，其中 $N$（$1\leq N \leq 10^5$）表示办公楼的数目，$K$（$\displaystyle 1\leq K \leq \frac{N}{2}$）表示可利用的网络电缆的数目。

接下来的 $N$ 行每行仅包含一个整数 $s$（$0\leq s \leq 10^9$）, 表示每个办公楼到大街起点处的距离。这些整数将按照从小到大的顺序依次出现。
## 输出格式

输出文件应当由一个正整数组成，给出将 $2K$ 个相异的办公楼连成 $K$ 对所需的网络电缆的最小总长度。
## 样例

### 样例输入 #1
```
5 2 
1 
3 
4 
6 
12 
```
### 样例输出 #1
```
4
```
## 提示

$30\%$ 的输入数据满足 $N\leq 20$。

$60\%$ 的输入数据满足 $N\leq 10^4$。


---

---
title: "开心派对小火车"
layout: "post"
diff: 提高+/省选-
pid: P3697
tag: ['贪心', '优先队列', '洛谷月赛']
---
# 开心派对小火车
## 题目描述

Aqours铁路公司旗下有N个站，编号1,2,..,N。

有各停（各站停车）电车特急电车两种。特急车会在$S_1,S_2,...,S_M (1=S_1<S_2 <...<S_M=N)$，一共M个车站停车。


相邻的两站(即编号为i的车站和编号为$i+1$的车站，而不是特急电车停车的相邻的两站)之间，各停电车要运行A分钟，特急需要B分钟。我们认为列车一直匀速运行，不考虑停车和加减速。


现在要加一种快速电车，要求其停站覆盖所有的特急电车的停站，而相邻的两站要运行C分钟。为了要快，决定刚好停K个站（$K>M$，包括特急的所有车站）。如果一个站可以停多种电车，那么旅客可以在这一站换乘。不过只能向前坐车，不能往回坐。


你需要设计一种快速列车的设站方案，要求旅客在T分钟**乘车时间（等车和换乘时间不计）**内，可以从1号站到尽可能多数量的站。你只需要告知能有几站可以达到。

## 输入格式

第一行3个整数，N，M，K，其意义已经在描述中给出。

第二行3个整数，A，B，C，其意义也已经在描述中给出。

第三行1个整数T，表示乘车时间。

接下来M行，每行一个整数。其中第i个整数为$S_i$

## 输出格式

一个整数，表示限定时间内能够达到的最多站的数量。

## 样例

### 样例输入 #1
```
10 3 5
10 3 5
30
1
6
10

```
### 样例输出 #1
```
8

```
## 提示

【样例解释】

可以设快速列车站为1/5/6/8/10。

2,3,4可以直接乘坐各停慢车，5可以乘坐快速列车，6,10可以乘坐特急列车，7可以到6转慢车，8可以到6传快速列车。9没办法在30分钟的乘车时间内到达

【数据范围】

对于20%的数据，$N \le 300, K-M=2, A \le 10^6 , T \le 10^9$

对于50%的数据，$N \le 1000$

对于100%的数据，$2 \le N \le 10^9, 2 \le M \le K \le 3000, 1 \le B < C < A \le 10^9, i \le T \le 10^{18}$



---

---
title: "[NOIP 2017 普及组] 跳房子"
layout: "post"
diff: 提高+/省选-
pid: P3957
tag: ['动态规划 DP', '2017', '二分', '单调队列', 'NOIP 普及组', '队列']
---
# [NOIP 2017 普及组] 跳房子
## 题目背景

NOIP2017 普及组 T4
## 题目描述

跳房子，也叫跳飞机，是一种世界性的儿童游戏，也是中国民间传统的体育游戏之一。

跳房子的游戏规则如下：

在地面上确定一个起点，然后在起点右侧画 $n$ 个格子，这些格子都在同一条直线上。每个格子内有一个数字（整数），表示到达这个 格子能得到的分数。玩家第一次从起点开始向右跳，跳到起点右侧的一个格子内。第二次再从当前位置继续向右跳，依此类推。规则规定：

玩家每次都必须跳到当前位置右侧的一个格子内。玩家可以在任意时刻结束游戏，获得的分数为曾经到达过的格子中的数字之和。

现在小 R 研发了一款弹跳机器人来参加这个游戏。但是这个机器人有一个非常严重的缺陷，它每次向右弹跳的距离只能为固定的 $d$。小 R 希望改进他的机器人，如果他花 $g$ 个金币改进他的机器人，那么他的机器人灵活性就能增加 $g$，但是需要注意的是，每 次弹跳的距离至少为 $1$。具体而言，当 $g<d$ 时，他的机器人每次可以选择向右弹跳的距离为 $d-g,d-g+1,d-g+2,\ldots,d+g-1,d+g$；否则当 $g \geq d$ 时，他的机器人每次可以选择向右弹跳的距离为 $1,2,3,\ldots,d+g-1,d+g$。

现在小 R 希望获得至少 $k$ 分，请问他至少要花多少金币来改造他的机器人。
## 输入格式

第一行三个正整数 $n,d,k$，分别表示格子的数目，改进前机器人弹跳的固定距离，以及希望至少获得的分数。相邻两个数 之间用一个空格隔开。

接下来 $n$ 行，每行两个整数 $x_i,s_i$，分别表示起点到第 $i$ 个格子的距离以及第 $i$ 个格子的分数。两个数之间用一个空格隔开。保证 $x_i$ 按递增顺序输入。
## 输出格式

共一行，一个整数，表示至少要花多少金币来改造他的机器人。若无论如何他都无法获得至少 $k$ 分，输出 $-1$。
## 样例

### 样例输入 #1
```
7 4 10
2 6
5 -3
10 3
11 -3
13 1
17 6
20 2
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
7 4 20
2 6
5 -3
10 3
11 -3
13 1
17 6
20 2
```
### 样例输出 #2
```
-1
```
## 提示

**样例 1 说明**

花费 $2$ 个金币改进后，小 R 的机器人依次选择的向右弹跳的距离分别为 $ 2, 3, 5, 3, 4,3$，先后到达的位置分别为 $2, 5, 10, 13, 17, 20$，对应 $ 1, 2, 3, 5, 6, 7$ 这 $6$ 个格子。这些格子中的数字之和 $ 15$ 即为小 R 获得的分数。

**样例 2 说明**

由于样例中 $7$ 个格子组合的最大可能数字之和只有 $18$，所以无论如何都无法获得 $20$ 分。

**数据规模与约定**

本题共 10 组测试数据，每组数据等分。

对于全部的数据满足 $1 \le n \le 5\times10^5$，$1 \le d \le2\times10^3$，$1 \le x_i, k \le 10^9$，$|s_i| < 10^5$。

对于第 $1, 2$ 组测试数据，保证 $n\le 10$。

对于第 $3, 4, 5$ 组测试数据，保证 $n \le 500$。

对于第 $6, 7, 8$ 组测试数据，保证 $d = 1$。


---

---
title: "[TJOI2013] 奖学金"
layout: "post"
diff: 提高+/省选-
pid: P3963
tag: ['贪心', '2013', '各省省选', '堆', '枚举', '优先队列', '可持久化线段树', '天津']
---
# [TJOI2013] 奖学金
## 题目背景

小张最近发表了一篇论文，有一个神秘人物要给小张学院发奖学金。
## 题目描述

小张学院有 $c$ 名学生，第 $i$ 名学生的成绩为 $a_i$，要获得的奖学金金额为 $b_i$。  
要从这 $c$ 名学生中挑出 $n$ 名学生发奖学金。这个神秘人物爱好奇特，他希望得到奖学金的同学的**成绩**的**中位数**尽可能大，但同时，他们的**奖学金总额**不能超过 $f$。

## 输入格式

第一行有三个整数，分别表示要挑出的学生人数 $n$，学生总人数 $c$ 和奖学金总额的最大值 $f$，**保证 $n$ 为奇数**。  

第 $2$ 到第 $(c + 1)$ 行，每行两个整数，第 $(i + 1)$ 行的整数依次表示第 $i$ 名学生的成绩 $a_i$ 和如果要给他发奖学金，则需要发的金额数 $b_i$。
## 输出格式

输出一行一个整数表示答案。如果无法满足神秘人的条件，请输出 $-1$。
## 样例

### 样例输入 #1
```
3 5 70
30 25
50 21
20 20
5 18
35 30

```
### 样例输出 #1
```
35
```
### 样例输入 #2
```
5 6 9
4 0
4 1
6 3
8 0
10 4
10 5

```
### 样例输出 #2
```
6
```
## 提示

### 样例 1 解释

选择成绩为 $5$，$35$，$50$ 的三名同学，奖金总额为 $18 + 30 + 21 = 69$。

### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n \leq 10^3$，$c \leq 2 \times 10^3$。
- 对于 $100\%$ 的数据，保证 $3 \leq n  \leq 10^5$，$n \leq c \leq 2 \times 10^5$，$0 \leq f \leq 2\times 10^9$，$0 \leq a_i \leq 2 \times 10^9$，$0 \leq b_i \leq 10^5$。


---

---
title: "[JXOI2017] 加法"
layout: "post"
diff: 提高+/省选-
pid: P4064
tag: ['贪心', '2017', '二分', '各省省选', '树状数组', '优先队列']
---
# [JXOI2017] 加法
## 题目描述

可怜有一个长度为 $n$ 的正整数序列 $A$，但是她觉得 $A$ 中的数字太小了，这让她很不开心。

于是她选择了 $m$ 个区间 $[l_i,r_i]$ 和两个正整数 $a,k$。她打算从这 $m$ 个区间里选出恰好 $k$ 个区间，并对每个区间执行一次区间加 $a$ 的操作。（每个区间最多只能选择一次）。

对区间 $[l,r]$ 进行一次加 $a$ 操作可以定义为对于所有 $i$ ∈ $[l,r]$，将 $A_i$ 变成 $A_i+a$。现在可怜想要知道怎么选择区间才能让操作后的序列的最小值尽可能的大，即最大化 $\min\{A_i\}$。
## 输入格式

第一行输入一个整数表示数据组数。

对于每组数据第一行输入四个整数 $n,m,k,a$。

第二行输入 $n$ 个整数描述序列 $A$。

接下来 $m$ 行每行两个整数 $l_i,r_i$ 描述每一个区间。数据保证所有区间两两不同。
## 输出格式

对于每组数据输出一个整数表示操作后序列最小值的最大值。

## 样例

### 样例输入 #1
```
1 
3 3 2 1
1 3 2
1 1
1 3
3 3
```
### 样例输出 #1
```
3
```
## 提示

选择给区间 $[1,1]$ 和 $[1,3]$ 加 $1$。

对于 $100\%$ 的数据，保证 $1\leq\sum n,\sum m\leq 2\times 10^5$，$1\leq T\leq 2\times 10^5$，$1\le k\le m$，$1\le a\le 100$，$1\le A_i\le 10^8$。


---

---
title: "[USACO18FEB] Snow Boots G"
layout: "post"
diff: 提高+/省选-
pid: P4269
tag: ['2018', '线段树', 'USACO', '并查集', '单调队列']
---
# [USACO18FEB] Snow Boots G
## 题目描述

It's winter on the farm, and that means snow! There are $N$ tiles on the path from the farmhouse to the barn, conveniently numbered $1 \dots N$, and tile $i$ is covered in $f_i$ feet of snow.
In his farmhouse cellar, Farmer John has $B$ pairs of boots, numbered $1 \dots B$. Some pairs are more heavy-duty than others, and some pairs are more agile than others. In particular, pair $i$ lets FJ step in snow at most $s_i$ feet deep, and lets FJ move at most $d_i$ forward in each step.

Farmer John starts off on tile $1$ and must reach tile $N$ to wake up the cows. Tile $1$ is sheltered by the farmhouse roof, and tile $N$ is sheltered by the barn roof, so neither of these tiles has any snow. Help Farmer John determine which pairs of snow boots will allow him to make the trek.
## 输入格式

The first line contains two space-separated integers $N$ and $B$ ($1 \leq N,B \leq 10^5$).
The second line contains $N$ space-separated integers; the $i$th integer is $f_i$, the depth of snow on tile $i$ ($0 \leq f_i \leq 10^9$). It's guaranteed that $f_1 = f_N = 0$.

The next $B$ lines contain two space-separated integers each. The first integer on line $i+2$ is $s_i$, the maximum depth of snow in which pair $i$ can step. The second integer on line $i+2$ is $d_i$, the maximum step size for pair $i$. It's guaranteed that $0 \leq s_i \leq 10^9$ and $1 \leq d_i \leq N-1$.
## 输出格式

The output should consist of $B$ lines. Line $i$ should contain a single integer: $1$ if Farmer John can trek from tile $1$ to tile $N$ wearing the $i$th pair of boots, and $0$ otherwise.
## 样例

### 样例输入 #1
```
8 7
0 3 8 5 6 9 0 0
0 5
0 6
6 2
8 1
10 1
5 3
150 7
```
### 样例输出 #1
```
0
1
1
0
1
1
1

```
## 提示

Problem credits: Dhruv Rohatgi
## 题目翻译

到冬天了，这意味着下雪了！从农舍到牛棚的路上有 $N$ 块地砖，方便起见编号为 $1 \dots N$，第 $i$ 块地砖上积了 $f_i$ 英尺的雪。
在 Farmer John 的农舍的地窖中，总共有 $B$ 双靴子，编号为 $1 \dots B$。其中某些比另一些结实，某些比另一些轻便。具体地说，第 $i$ 双靴子能够让 FJ 在至多 $s_i$ 英尺深的积雪中行走，能够让 FJ 每步至多前进 $d_i$。

Farmer John 从 $1$ 号地砖出发，他必须到达 $N$ 号地砖才能叫醒奶牛们。$1$ 号地砖在农舍的屋檐下，$N$ 号地砖在牛棚的屋檐下，所以这两块地砖都没有积雪。帮助 Farmer John 求出哪些靴子可以帮助他走完这段艰辛的路程。

**【输入格式】**

第一行包含两个空格分隔的整数 $N$ 和 $B$（$1 \leq N,B \leq 10^5$）。  
第二行包含$N$个空格分隔的整数；第 $i$ 个整数为 $f_i$，即 $i$ 号地砖的积雪深度（$0 \leq f_i \leq 10^9$）。输入保证 $f_1 = f_N = 0$。

下面 $B$ 行，每行包含两个空格分隔的整数。第 $i+2$ 行的第一个数为 $s_i$，表示第 $i$ 双靴子能够承受的最大积雪深度。第 $i+2$ 行的第二个数为 $d_i$，表示第 $i$ 双靴子的最大步长。输入保证 $0 \leq s_i \leq 10^9$ 以及 $1 \leq d_i \leq N-1$。

**【输出格式】**

输出包含 $B$ 行。第 $i$ 行包含一个整数：如果 Farmer John 能够穿着第 $i$ 双靴子从 $1$ 号地砖走到 $N$ 号地砖，为 $1$，否则为 $0$。



---

---
title: "[HAOI2008] 移动玩具"
layout: "post"
diff: 提高+/省选-
pid: P4289
tag: ['2008', '河南', '各省省选', '哈希 hashing', '进制', '队列']
---
# [HAOI2008] 移动玩具
## 题目描述

在一个4*4的方框内摆放了若干个相同的玩具，某人想将这些玩具重新摆放成为他心中理想的状态，规定移动时只能将玩具向上下左右四个方向移动，并且移动的位置不能有玩具，请你用最少的移动次数将初始的玩具状态移动到某人心中的目标状态。
## 输入格式

前4行表示玩具的初始状态，每行4个数字1或0，1表示方格中放置了玩具，0表示没有放置玩具。接着是一个空行。接下来4行表示玩具的目标状态，每行4个数字1或0，意义同上。
## 输出格式

一个整数，所需要的最少移动次数。
## 样例

### 样例输入 #1
```
1111
0000
1110
0010 

1010
0101
1010
0101
```
### 样例输出 #1
```
4
```


---

---
title: "[AHOI2007] 密码箱"
layout: "post"
diff: 提高+/省选-
pid: P4296
tag: ['2007', '各省省选', '安徽', '枚举', '优先队列']
---
# [AHOI2007] 密码箱
## 题目描述

在一次偶然的情况下，小可可得到了一个密码箱，听说里面藏着一份古代流传下来的藏宝图，只要能破解密码就能打开箱子，而箱子背面刻着的古代图标，就是对密码的提示。

经过艰苦的破译，小可可发现，这些图标表示一个数以及这个数与密码的关系。假设这个数是 $n$，密码为 $x$，那么可以得到如下表述： 密码 $x$ 大于等于 $0$，且小于 $n$，而 $x$ 的平方除以 $n$，得到的余数为 $1$。 小可可知道满足上述条件的 $x$ 可能不止一个，所以一定要把所有满足条件的 $x$ 计算出来，密码肯定就在其中。计算的过程是很艰苦的，你能否编写一个程序来帮助小可可呢？
## 输入格式

一行，一个数字 $n$（$1 \leq n \leq 2 \times 10^9$）。
## 输出格式

你的程序需要找到所有满足前面所描述条件的 $x$，如果不存在这样的 $x$，你的程序只需输出一行 `None`，否则请按照从小到大的顺序输出这些 $x$，每行一个数。
## 样例

### 样例输入 #1
```
12
```
### 样例输出 #1
```
1
5
7
11
```


---

---
title: "[IOI 2008] Island"
layout: "post"
diff: 提高+/省选-
pid: P4381
tag: ['动态规划 DP', '2008', 'IOI', 'O2优化', '树的直径', '栈', '队列', '基环树']
---
# [IOI 2008] Island
## 题目描述

你准备浏览一个公园，该公园由 $N$ 个岛屿组成，当地管理部门从每个岛屿 $i$ 出发向另外一个岛屿建了一座长度为 $L_i$ 的桥，不过桥是可以双向行走的。同时，每对岛屿之间都有一艘专用的往来两岛之间的渡船。相对于乘船而言，你更喜欢步行。你希望经过的桥的总长度尽可能长，但受到以下的限制：

- 可以自行挑选一个岛开始游览。
- 任何一个岛都不能游览一次以上。
- 无论任何时间，你都可以由当前所在的岛 $S$ 去另一个从未到过的岛 $D$。从 $S$ 到 $D$ 有如下方法：
  - 步行：仅当两个岛之间有一座桥时才有可能。对于这种情况，桥的长度会累加到你步行的总距离中。
  - 渡船：你可以选择这种方法，仅当没有任何桥和以前使用过的渡船的组合可以由 $S$ 走到 $D$ (当检查是否可到达时，你应该考虑所有的路径，包括经过你曾游览过的那些岛)。

注意，你不必游览所有的岛，也可能无法走完所有的桥。

请你编写一个程序，给定 $N$ 座桥以及它们的长度，按照上述的规则，计算你可以走过的桥的长度之和的最大值。
## 输入格式

第一行包含一个整数 $N$，即公园内岛屿的数目。

随后的 $N$ 行每一行用来表示一个岛。第 $i$ 行由两个以单空格分隔的整数，表示由岛 $i$ 筑的桥。第一个整数表示桥另一端的岛，第二个整数表示该桥的长度 $L_i$。你可以假设对于每座桥，其端点总是位于不同的岛上。
## 输出格式

仅包含一个整数，即可能的最大步行距离。
## 样例

### 样例输入 #1
```
7
3 8
7 2
4 2
1 4
1 9
3 4
2 3
```
### 样例输出 #1
```
24
```
## 提示

**样例解释**：

![样例图示](https://cdn.vijos.org/fs/c82895f1d6f84d5756610176662d6ee644c3e55e)

样例 $N=7$ 座桥，分别为 $(1-3), (2-7), (3-4), (4-1), (5-1), (6-3)$ 以及 $(7-2)$。注意连接岛 $2$ 与岛 $7$ 之间有两座不同的桥。

其中一个可以取得最大的步行距离的方法如下：

- 由岛 $5$ 开始。
- 步行长度为 $9$ 的桥到岛 $1$。
- 步行长度为 $8$ 的桥到岛 $3$。
- 步行长度为 $4$ 的桥到岛 $6$。
- 搭渡船由岛 $6$ 到岛 $7$。
- 步行长度为 $3$ 的桥到岛 $2$。

最后，你到达岛 $2$，而你的总步行距离为 $9+8+4+3=24$。

只有岛 $4$ 没有去。注意，上述游览结束时，你不能再游览这个岛。更准确地说：

- 你不可以步行去游览，因为没有桥连接岛 $2$ (你现在的岛) 与岛 $4$。
- 你不可以搭渡船去游览，因为你可由当前所在的岛 $2$ 到达岛 $4$。一个方法是：走 $(2-7)$ 桥，再搭你曾搭过的渡船由岛 $7$ 去岛 $6$，然后走 $(6-3)$ 桥，最后走 $(3-4)$ 桥。

**数据范围**：

对于 $100\%$ 的数据，$2\leqslant N\leqslant 10^6,1\leqslant L_i\leqslant 10^8$。



---

---
title: "[USACO10NOV] Buying Feed G"
layout: "post"
diff: 提高+/省选-
pid: P4544
tag: ['2010', 'USACO', '单调队列', '背包 DP', '队列']
---
# [USACO10NOV] Buying Feed G
## 题目描述

约翰开车来到镇上，他要带$K$吨饲料回家。运送饲料是需要花钱的，如果他的车上有$X$吨饲料，每公里就要花费$X^2$元，开车D公里就需要$D\times  X^2$元。约翰可以从$N$家商店购买饲料，所有商店都在一个坐标轴上，第$i$家店的位置是$X_i$，饲料的售价为每吨$C_i$元，库存为$F_i$。

约翰从坐标$X=0$开始沿坐标轴正方向前进，他家在坐标$X=E$上。为了带$K$吨饲料回家，约翰最少的花费是多少呢？假设所有商店的库存之和不会少于$K$。

举个例子，假设有三家商店，情况如下所示：

|坐标|$X=1$|$X=3$|$X=4$|$E=5$|
|:-:|:-:|:-:|:-:|:-:|
|库存|$1$|$1$|$1$|
|售价|$1$|$2$|$2$|

如果$K=2$，约翰的最优选择是在离家较近的两家商店购买饲料，则花在路上的钱是$1+4=5$，花在商店的钱是$2+2=4$，共需要$9$元。
## 输入格式

第$1$行:三个整数$K,E,N$ 第$2..N+1$行:第$i+1$行的三个整数代表,$X_i,F_i,C_i$.
## 输出格式

一个整数,代表最小花费
## 样例

### 样例输入 #1
```
2 5 3
3 1 2
4 1 2
1 1 1
```
### 样例输出 #1
```
9
```
## 提示

$1 \leq K \leq 10000 , 1 \leq E \leq 500 , 1 \leq N \leq 500$

$0 < Xi < E, 1 \leq Fi \leq 10000, 1 \leq C_i \leq 10^7$


---

---
title: "[USACO05DEC] Cleaning Shifts S"
layout: "post"
diff: 提高+/省选-
pid: P4644
tag: ['动态规划 DP', '递推', '2005', '线段树', 'USACO', '排序', '队列']
---
# [USACO05DEC] Cleaning Shifts S
## 题目描述

约翰的奶牛们从小娇生惯养，她们无法容忍牛棚里的任何脏东西。约翰发现，如果要使这群有洁癖的奶牛满意，他不得不雇佣她们中的一些来清扫牛棚，约翰的奶牛中有 $ N(1 \leq N \leq 10000) $ 头愿意通过清扫牛棚来挣一些零花钱。

由于在某个时段中奶牛们会在牛棚里随时随地地乱扔垃圾，自然地，她们要求在这段时间里，无论什么时候至少要有一头奶牛正在打扫。需要打扫的时段从某一天的第 $ M $ 秒开始，到第 $ E $ 秒结束 $ (0 \leq M \leq E \leq 86399) $。注意这里的秒是指时间段而不是时间点，也就是说，每天需要打扫的总时间是 $ E-M+1 $ 秒。

约翰已经从每头牛那里得到了她们愿意接受的工作计划：对于某一头牛，她每天都愿意在笫 $ T_1 \ldots T_2 $ 秒的时间段内工作 $ (M \leq T_1 \leq T_2 \leq E) $ ，所要求的报酬是 $ S $ 美元 $ (0 \leq S \leq 500000) $。与需打扫时段的描述一样，如果一头奶牛愿意工作的时段是每天的第 $ 10 \ldots 20 $ 秒，那她总共工作的时间是 $ 11 $ 秒，而不是 $ 10 $ 秒。

约翰一旦决定雇佣某一头奶牛，就必须付给她全额的工资，而不能只让她工作一段时间，然后再按这段时间在她愿意工作的总时间中所占的百分比来决定她的工资。现在请你帮约翰决定该雇佣哪些奶牛以保持牛棚的清洁，当然，在能让奶牛们满意的前提下，约翰希望使总花费尽量小。
## 输入格式

第 $ 1 $ 行： $ 3 $ 个正整数 $ N,M,E $ 。

第 $ 2 $ 到 $ N+1 $ 行：第 $ i+1 $ 行给出了编号为 $ i $ 的奶牛的工作计划，即 $ 3 $ 个正整数 $ T_1,T_2,S $ 。
## 输出格式

输出一个整数，表示约翰需要为牛棚清理工作支付的最少费用。如果清理工作不可能完成，那么输出 $ -1 $ 。
## 样例

### 样例输入 #1
```
3 0 4
0 2 3
3 4 2
0 0 1
```
### 样例输出 #1
```
5
```
## 提示

约翰有 $ 3 $ 头牛，牛棚在第 $ 0 $ 秒到第 $ 4 $ 秒之间需要打扫。 约翰雇佣前两头牛清扫牛棚，可以只花 $ 5 $ 美元就完成一整天的清扫。



---

---
title: "kry loves 2048"
layout: "post"
diff: 提高+/省选-
pid: P4829
tag: ['排序', '队列', '洛谷月赛']
---
# kry loves 2048
## 题目背景

kls是一个人赢。
## 题目描述

kls最近在玩一款类似2048的游戏，规则是这样的：

一开始，有$n$个方块，每个方块上有一个$1$到$m$的整数。

kls可以进行两种操作：

1. 选择两个数字相同的方块（不一定要相邻），将它们合并成一个数字为原来的两倍的方块；

2. 减小一个方块上的数字。

操作的次数没有限制，最终的得分为所有方块上的最大的数字。

因为kls要去陪妹子了，没有时间继续玩，他想让你帮忙计算一下，最多能得到多少分。
## 输入格式

因为数据可能很大，读入容易超时，所以kls给你们提供了一个c++的随机数生成器。

```cpp
void generate_array(int a[], int n, int m, int seed) {
    unsigned x = seed;
    for (int i = 0; i < n; ++i) {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        a[i] = x % m + 1;
    }
}
```

把这个函数复制到你的程序里。用一个足够大的数组，以及输入数据给出的$n$，$m$和$seed$作为参数，调用这个函数。然后这个数组里就是一开始的方块上的数字（下标从0开始）。

输入一行三个数$n,m,seed$，含义如上。
## 输出格式

一行一个数，表示最大得分。
## 样例

### 样例输入 #1
```
5 10 233
```
### 样例输出 #1
```
24
```
### 样例输入 #2
```
5 50 3
```
### 样例输出 #2
```
48
```
### 样例输入 #3
```
1000 1000 666
```
### 样例输出 #3
```
374784
```
## 提示

### 样例解释

样例1生成出来的数是 6 10 7 5 4。

样例2生成出来的数是 8 12 48 4 4。

### 数据范围

对于30%的数据，$n, m \le 10$；

对于60%的数据，$n, m \le 10^5$；

对于100%的数据，$n, m \le 10^7$，$1 \le seed \le 10^9$。


---

---
title: "OIer们的东方梦"
layout: "post"
diff: 提高+/省选-
pid: P4872
tag: ['洛谷原创', 'O2优化', '广度优先搜索 BFS', '优先队列', '队列']
---
# OIer们的东方梦
## 题目背景

**#11,#12 两组 Hack 数据由 uid=20285 提供**

OIer 们做~~魂魄妖~~梦都想去幻想乡玩一下。这一次，他们在睡~~古明地~~觉时在梦中穿越去了幻想乡，幻想乡有很多的少(ju)女(ruo)，但是他们被~~老太婆~~少女的美色~~和蒟蒻的美味~~所吸引，在幻想乡中迷失了方向。

勇敢的~~死肥宅~~少年啊，现在你手里有一份幻想乡人间之里的地图，你知道 OIer 们的位置，你可以远程给OIer们传递信息，请你带领迷路的 OIer 们走进回到现实生活的祭坛吧！
## 题目描述

给你一个 $N\times M$ 的地图，如图所示：              
```
5400000S01     
1111101101     
000003X301      
3111111101     
E000300031      
1111X30001     
```

其中有很多稀奇古怪的东西：  
     
* $S$ 表示出发点，$E$ 表示终点。      
* $0$ 表示空地，你想怎么走就怎么走，走一格需要 $1s$。            
* $1$ 表示墙，你无法通行（~~除非你受到了**风神少女**的庇护~~）。   
* $2$ 表示小妖怪，你需要 $3s$ 的时间去消灭小妖怪，才能经过该位置。（PS: 妖怪被消灭后只要离开当前格子立刻复活）  
* $3$ 表示大妖怪，你需要 $8s$ 的时间去消灭大妖怪，才能经过该位置。   
* $4$ 表示太阳花田，到达该位置可以获得太阳花，获得太阳花后遇到妖怪时可**直接**通过该妖怪的位置。  
* $5$ 表示楼观剑（科普君：楼观剑，英文名 $Louguan\ is\ very\ jian$，是妖怪做的剑，楼观剑斩不断的东西几乎没有)，到达该位置可以花费 $5s$ 获得它，获得它后可以砍墙砍妖怪将其变成空地（当然也可以不砍，砍墙砍妖怪不需要时间，楼观剑可以一直使用**不会损坏**，有了楼观剑依然可以使用隙间，但是楼观剑不能砍隙间~~和一点用都没有的麻薯，麻薯妖梦UUZ是一家嘛~~）       
* $M$ 表示麻薯（是 $mashu$ 不是 $mafu$~~不知道麻薯是什么的一把楼观剑给你砍过来~~)，碰到麻薯后你可以把它吃了(路人甲：那你为什么还要加这个东西? 出题人：有 $S$ 肯定要有 $M$ 啊。路人乙：我就是死外边，从隙间中跳下去，也不会吃麻薯！嗯~真香！）            
* $X$ 表示紫妈的隙间，碰到隙间后会传送至其他的任意一个隙间(数据**不**保证只有 0 或 2 个隙间，**就是说可以有很多隙间乱传**)，每次传送耗时 $1s$。(经过当前格子时可以不经过隙间)       
      
答案输出 OIer 们到达终点所需最短时间。如果无法到达，输出 "We want to live in the TouHou World forever"。     
翻译：此生无悔入东方，来世~~睡遍~~愿生幻想乡。   
    
**温馨提示：不排除存在可以往回走等稀奇古怪的最优走法**
## 输入格式

数据共有 $N+1$行。

第 $1$ 行输入 $N$ 和 $M$。  
第 $2$ 到 $N+1$ 行输入 $N\times M$ 的地图。
## 输出格式

一行，最短时间或者 "We want to live in the TouHou World forever"。
## 样例

### 样例输入 #1
```
6 10
5400000S01
1111101101
000003X301
3111111101
E000300031
1111X30001
```
### 样例输出 #1
```
16
```
### 样例输入 #2
```
5 10
S23323323X
2032332333
1202202202
1111111111
11111111XE
```
### 样例输出 #2
```
44
```
### 样例输入 #3
```
9 10
SX1X0X1X1X
2332332333
5205205200
XXXXXXXXXX
2222222222
3333333333
3333333333
XXXXXXXXXX
XXXXXXXXXE
```
### 样例输出 #3
```
3
```
## 提示

对于 $30\%$ 的数据，$1\leq N,M\leq 50$。       
对于 $50\%$ 的数据，$1\leq N,M\leq 100$。       
对于 $100\%$ 的数据，$1\leq N,M\leq 1000$。

保证有一组数据答案为 "We want to live in the TouHou World forever"，数据有梯度。

### 样例解释

**样例 1**：在 $7s$ 时到达楼观剑，在 $12s$ 时获得楼观剑，一路向下砍到达终点。                   
**样例 2**：在 $10s$ 时到达 $(3,3)$，在 $32s$ 时到达$(3,10)$，向上进入隙间后到达终点。          
**样例 3**：这个就不用解释了吧(出题人放飞自我)。


---

---
title: "PION贪吃蛇"
layout: "post"
diff: 提高+/省选-
pid: P4944
tag: ['模拟', '搜索', '队列']
---
# PION贪吃蛇
## 题目背景

NOIP2018原创模拟题 T3

NOIP DAY1 T3 or DAY 2 T2 难度

贪吃蛇大家都玩过吧，当然不同版本有不同规则。下面介绍PION贪吃蛇。
## 题目描述

![图A](https://cdn.luogu.com.cn/upload/pic/31298.png)

***表示方法：***

该题中贪吃蛇存在于一个n行m列的矩形中，用 ‘.’ 表示空地，用 '#’ 表示蛇身，用 ‘@’表示蛇头，用‘&’表示食物
例如：图一表示 $5*6$ 的矩形，有一条蛇，蛇长度为 $7$，有两个食物

***基本规则：***

1.蛇头每一秒就会移动一格，身体自然会跟着移动，用W表示向上，S表示向下，A表示向左，D表示向右

2.蛇每吃一个食物就长度就会加一，而增加的长度体现在食物所在的地方，你可以把吃食物理解成食物变成了蛇头，之前的蛇头变成了蛇身，这一秒不移动

例如：图二的三幅图展示了第一秒，第二秒，和第三秒的情况

3.蛇如果死亡，身体（包括头）一定会全部变成食物

4.PION贪吃蛇的蛇头碰到自己或别的蛇的身体就会死亡

例如：图三的三幅图展示了第二条蛇撞在别人身体上死亡的过程

5.蛇头撞在边界上也会引起死亡，但蛇头刚好现在边界上不会

例如：图四第二幅图虽然蛇头在边界上，但是只是刚好，如果此时进行D操作蛇就会死亡，如果进行W或S就不会

6.如果有操作使蛇头向相反方向运动，之后如果与身体重合蛇也会死亡（比如：图二第一幅图使用A操作,蛇就会死亡，此时在原地成为三个食物，你也可以理解为蛇下一秒不行动而自杀了）

7.两条蛇蛇头相撞，主动撞上的死亡

8.蛇的移动按编号由小到大进行（编号的含义见下文）

## 输入格式

第一行三个数 $n,m,k$ 表示 $n*m$ 的矩形，$k$ 表示操作次数

接下来 $n$ 行每行 $m$ 个字符，表示地图

再接下来 $c$ 行（注意：图中有几条蛇就有几行），每行 $k$ 个字符，表示有 $k$ 个操作（如果执行了某个操作蛇死了，就忽略后面的操作）

我们将蛇编号：按每条蛇蛇头的坐标从小到大编号为 $1，2，...，c$（越靠近上边的坐标越小，如果相同越靠近左边的坐标越小）

例如：图三第一幅图两条蛇的蛇头坐标分别为（$4,3）,（3,7）$所以较长的蛇编号为 $2$，较短的蛇编号为 $1$
## 输出格式

$c+1$ 行，输出 $k$ 次操作后每一条蛇的长度，编号；每一行第一个为长度，第二个数为编号

最后一行输出剩下食物的总个数

注意：输出按长度由大到小排序（长度相同按编号由小到大排序），死亡的蛇长度为 $0$
## 样例

### 样例输入 #1
```
5 7 6
.&...&.
..##@..
.&...&.
..##@..
.&...&.
DWAAAA
WDDDDD
```
### 样例输出 #1
```
5 1
0 2
7
```
### 样例输入 #2
```
9 9 4
.........
.#######.
.......#.
.@#.&@.#.
&.#.&&.#.
&&######.
.&.......
..@####..
.........
ASSD
ASDD
WASD
```
### 样例输出 #2
```
22 1
4 2
0 3
6
```
## 提示

***样例说明：***

![图B](https://cdn.luogu.com.cn/upload/pic/31357.png)

图五，图六展示了从第 $0$ 秒开始之后每一秒地图的状态，请看图理解（样例二图四有点小错误）

***数据范围：***

$10\%$ 数据满足 $n,m\leq 5,c=1,k\leq3$

$30\%$ 数据满足 $n,m\leq 10,c\leq 2,k\leq 5$

$50\%$ 数据满足 $n,m\leq 50,c\leq 5,k\leq 20$

$70\%$ 数据满足 $n,m\leq 100,c\leq 7,k\leq 50$

$100\%$ 数据满足 $n,m\leq 200,c\leq 20,k\leq 100$，且图中的蛇不会引起混淆（对于任意蛇头，最多只有一块蛇身于其相连，而蛇身最多为二连块）,且数据保证图中的蛇均可以判断身体与头的对应关系，不会造成蛇身形态多解


---

---
title: "经验"
layout: "post"
diff: 提高+/省选-
pid: P5032
tag: ['递归', 'O2优化', '优先队列', '队列']
---
# 经验
## 题目背景

[赛时答疑](https://www.luogu.org/discuss/show/80694)  

**简略版已经更新，时限改为500ms**

攒够经验附魔去~~

Steve在minecraft中总是会遇上难题：
他想要修理n本附魔书，每本附魔书的等级为ai，他总是不知道铁砧修理和经验值的机制。他便在mcwiki上搜索到了一些资料：
![](https://d1u5p3l4wpay3k.cloudfront.net/minecraft_zh_gamepedia/pChart4mw/e8160a1cad02998149d79c65237dc775.png)

----图为经验值与等级的关系，摘自mcwiki 

他看到这个图，就想：我等级升的越高，我所需要的经验值便越多，那么如果我等级刚好够铁砧修理的话，那我所耗费的经验不就越少了吗？他便继续搜索了下去，并将铁砧机制附在了下面,让你帮他解决问题：
## 题目描述

**累积惩罚：**

无论是重命名、修复、还是合并操作，其经验花费都会因其物品先前在铁砧上的操作而增加，这些额外增加的花费被称作“累积惩罚”。对于一件从未放上铁砧的物品，累积惩罚为0。

一个物品每次在铁砧上操作过后（不包括重命名），其累积惩罚都会先乘2再加1。如此一来，一个物品在操作过N次后累积惩罚是2^N-1。6次操作之后，累积惩罚是63级，此时生存模式下无法再作进一步的修复和附魔工作。31次操作后，惩罚等级是2147483647级，此时在任何模式下都不能再进行操作。

当合并两个物品时，玩家会同时受到两件物品的累积惩罚。合并后物品的累积惩罚根据先前两个物品中较高者计算。例如，合并两个累积惩罚分别是3级和15级的物品会额外花费18级的惩罚经验，而合并后的物品惩罚是31级（15*2+1）。

累积惩罚甚至会作用在不会磨损的物品上，譬如附魔书。因此，合并4本时运 I 的附魔书，会得到一本累积惩罚为3的时运 III 附魔书。

     累计操作数	      惩罚

         0	           0

         1	           1

         2	           3

         3	           7

         4	           15

         5	           31

使用合成方格进行的物品修复操作会移除所有累积惩罚，但也会丢失所有的魔咒。

**合并物品：**

铁砧界面中第一格/左边的物品称为目标物品；第二格/右边的物品称为牺牲物品——合并后会消失。如果牺牲物品附有魔咒，铁砧会同时试图将牺牲物品的附魔合并至目标物品上。无论目标物品上的魔咒是否产生实际变化，铁砧都将根据目标物品与牺牲物品上的魔咒收取玩家的等级耗费。

对于牺牲物品上的每个魔咒来说：如果目标物品也拥有相同的魔咒：

当牺牲物品的魔咒等级较高时，目标物品魔咒的等级将上升至牺牲物品上的等级。

当牺牲物品的魔咒等级相同时，目标物品上魔咒的等级将提升1级，除非其等级已为最高。    

当牺牲物品的魔咒等级较低时，目标物品上该魔咒的等级不变。
    
合并物品的总花费将是下列费用之和：

1.目标物品和牺牲物品的累积惩罚之和。

2.如果同时进行重命名，则额外产生重命名的费用。

3.如果目标物品耐久度未满，则耗费2级用于维修。

4.如果牺牲物品拥有魔咒，则产生附魔费用。

5.如果牺牲物品是一本附魔书，则不会产生维修费用，铁砧会尝试将书本上的魔咒合并至目标物品上。亦可同时对目标物品进行重命名。此时的附魔花费一般会少于合并两个类似物品的费用。

-----摘自mc wiki，稍作删改

**简略版：**  
给出附魔书，只有同等等级的才能合并。合并的代价为两本书的累计代价之和。合成后的书的累计代价为合成前最大代价的2倍加上1。求最高等级和最小花费（要求最高等级为第一关键字）,Steve因为开了挂，所以最高等级不限

现给出$n$本附魔书，每本附魔书有它的等级$ai$,问如何才能得到附魔书的最大等级$x$，在此基础上，请计算合成它消耗的最小等级$y$。（我们假设每本附魔书初始的累积惩罚为1）。

Steve很懒，他不想看上面的话，他只想要让你编写出一个程序计算出$x$与$y$。但Steve为了不外传，他只要求你输出$x$在模$y$意义下的乘法逆元$k$即可。如果没有，请输出$-1$.
## 输入格式

第一行为一个整数$n$

接下来$n$行，每行均有一个整数$ai$，表示每本附魔书的初始等级，不保证数据有序.
## 输出格式

一个整数$k$,表示$x$在模$y$意义下的乘法逆元,如果没有，请输出$-1$.  
PS：乘法逆元$k$也可以这样理解: $k$是使得 $kx\equiv1(mod$ $y)$的最小正整数
## 样例

### 样例输入 #1
```
5
1 1 2 3 4
```
### 样例输出 #1
```
-1
```
### 样例输入 #2
```
4
1 1 1 1
```
### 样例输出 #2
```
7
```
## 提示

**样例解释**
 
第一个样例：    
合并两个第一等级的，合并花费2经验，代价升为3  
再合并两个第二等级的，花费3+1=4经验，代价升为7  
再合并两个第三等级的，花费7+1=8经验，代价升为15  
最后合并两个第四等级的，花费15+1=16经验，代价升为31  

经验总花费：2+4+8+16=30，最大等级：5


对于第一个样例: $x=5$,$y=30$;

对于第二个样例: $x=3$,$y=10$;

**数据范围**

![]( https://cdn.luogu.com.cn/upload/pic/41547.png )

保证数据随机，$x$,$y$,$k$在long int范围内

**温馨提示**

本题读入量较大，请使用较快的读入方法，在此，提供一种快速读入的样式：(需包含头文件<cctype>)

```
#include<cctype>
inline void read(int &x){
     char ch=getchar();x=0;
     while(!isdigit(ch))   ch=getchar();
     while(isdigit(ch))   x=x*10+ch-'0',ch=getchar();
}
```


---

---
title: "[USACO19DEC] Meetings S"
layout: "post"
diff: 提高+/省选-
pid: P5835
tag: ['2019', '二分', 'USACO', '排序', '队列']
---
# [USACO19DEC] Meetings S
## 题目描述

有两个牛棚位于一维数轴上的点 $0$ 和 $L$ 处（$1 \leq L \leq 10^9$）。同时有 $N$ 头奶牛（$1 \leq N \leq 5 \times 10^4$）位于数轴上不同的位置（将牛棚和奶牛看作点）。每头奶牛 $i$ 初始时位于某个位置 $x_i$，并朝着正向或负向以一个单位每秒的速度移动，用一个等于 $1$ 或 $-1$ 的整数 $d_i$ 表示。每头奶牛还拥有一个在范围 $[1,10^3]$ 内的重量。所有奶牛始终以恒定的速度移动，直到以下事件之一发生：
- 如果奶牛 $i$ 移动到了一个牛棚，则奶牛 $i$ 停止移动。
- 当奶牛 $i$ 和 $j$ 占据了相同的点的时候，并且这一点不是一个牛棚，则发生了相遇。此时，奶牛 $i$ 被赋予奶牛 $j$ 先前的速度，反之亦然。注意奶牛可能在一个非整数点相遇。

令 $T$ 等于停止移动的奶牛（由于到达两个牛棚之一）的重量之和至少等于所有奶牛的重量之和的一半的最早时刻。请求出在时刻 $0 \ldots T$（包括时刻 $T$）之间发生的奶牛对相遇的总数。

## 输入格式

输入的第一行包含两个空格分隔的整数 $N$ 和 $L$。

以下 $N$ 行，每行包含三个空格分隔的整数 $w_i$，$x_i$ 以及 $d_i$。所有的位置 $x_i$ 各不相同，并且满足 $0<x_i<L$。
## 输出格式

输出一行，包含答案。
## 样例

### 样例输入 #1
```
3 5
1 1 1
2 2 -1
3 3 -1
```
### 样例输出 #1
```
2
```
## 提示

### 样例解释

在这个例子中，奶牛们按如下方式移动：

1. 第一和第二头奶牛于时刻 0.5 在位置 1.5 相遇。此时第一头奶牛拥有速度 -1，第二头奶牛拥有速度 1。
2. 第二和第三头奶牛于时刻 1 在位置 2 相遇。此时第二头奶牛拥有速度 −1，第三头奶牛拥有速度 1。
3. 第一头奶牛于时刻 2 到达左边的牛棚。
4. 第二头奶牛于时刻 3 到达左边的牛棚。
5. 由于到达牛棚的奶牛的总重量已经至少是所有奶牛的总重量的一半，这个过程此时终止。如果继续进行下去，第三头奶牛将会在时刻 4 到达右边的牛棚。

发生了恰好两次相遇。 

### 子任务

测试点 $2\sim 4$ 满足 $N\le 10^2$，并且对所有 $i$，$w_i=1$。

测试点 $5\sim 7$ 满足 $N\le 10^2$。

供题：Benjamin Qi


---

---
title: "[COCI 2018/2019 #1] Strah"
layout: "post"
diff: 提高+/省选-
pid: P7306
tag: ['2018', '单调队列', 'COCI（克罗地亚）']
---
# [COCI 2018/2019 #1] Strah
## 题目背景

任何人都会对某事感到害怕。有些怕黑，有些怕高，还有些惧怕 Vinnie Jones……
## 题目描述

Mirko 最害怕的是寻找合适的土地来种植草莓。他的土地可以用一个 $N \times M$ 的矩阵来表示。土地中有些田地适合种植草莓，而有些不适合，因为那里杂草丛生。

Mirko 正在寻找一块合适矩形。当土地中有一块矩形区域包含的所有田地均适合种植草莓，则该矩形被称为合适矩形。

Mirko 还对所有田地的潜力值感兴趣。一块田地的潜力值定义为包含该田地的合适矩形的个数。

求 Mirko 所有田地的潜力值之和。
## 输入格式

第一行输入正整数 $N,M$，表示土地的规模。

接下来的 $N$ 行，每行输入 $M$ 个字符。其中 `.` 表示该块田地适合种植草莓，而 `#` 表示不适合。
## 输出格式

输出 Mirko 所有田地的潜力值之和。
## 样例

### 样例输入 #1
```
2 3
.#.
..#
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
3 3
...
...
...
```
### 样例输出 #2
```
100
```
### 样例输入 #3
```
3 4
..#.
#...
...#
```
### 样例输出 #3
```
40
```
## 提示

#### 样例 1 解释

下列矩阵代表各个田地的潜力值。所有田地潜力值总和为 $8$。

|$2$|$0$|$1$|
| :----------: | :----------: | :----------: |
|$3$|$2$|$0$|

#### 数据规模与约定

对于 $20\%$ 的数据，$1 \le N,M \le 10$。

对于另外 $30\%$ 的数据，$1 \le N,M \le 300$。

对于 $100\%$ 的数据，$1 \le N,M \le 2000$。

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2018-2019](https://hsin.hr/coci/archive/2018_2019/) [CONTEST #1](https://hsin.hr/coci/archive/2018_2019/contest1_tasks.pdf)  _T4 Strah_。**


---

---
title: "Inferno"
layout: "post"
diff: 提高+/省选-
pid: P8945
tag: ['贪心', '单调队列', '2023', '洛谷原创', 'O2优化', '前缀和']
---
# Inferno
## 题目背景

> 我是幽灵。  
> 穿过悲惨之城，我落荒而逃。  
> 穿过永世凄苦，我远走高飞。

沿着阿尔诺河的堤岸，我夺路狂奔，气喘吁吁……左转上了卡斯特拉尼大街，一直朝北而行，始终隐蔽在乌菲兹美术馆的阴影之下。

但他们还是穷追不舍。

他们的脚步声越来越响，这些追捕者冷酷无情，不达目的绝不善罢甘休。

这么多年来，他们一直尾随着我。他们锲而不舍，是的我只能活在地下……被迫呆在炼狱之中……就像冥府的恶魔，时刻忍受地狱的煎熬。

> 我是幽灵。

如今浮生尘世，我举目北望，却看不到通往救赎的捷径——那高耸的亚平宁山脉挡住了黎明的第一缕阳光。
## 题目描述

罗伯特 · 兰登在洗下但丁死亡面具上的丙烯石膏后，在背面发现了一行字：

> 哦，有着稳固智慧的人啊，  
> 请注意这里的含义  
> 就藏在晦涩的序列面纱之下。

下面有一行由 $1,-1$ 组成的长度为 $n$ 的序列。面具经受了岁月的侵蚀，序列中有一些数已经模糊不清。幸运的是，面具下面有给出两条线索：

> 你只得往空缺的位置填 $k$ 个 $1$，其余填入 $-1$，需要最大化这个序列的最大子段和。

 > > **一个序列的最大子段和定义为，其在一段连续长度的区间内的最大和。形式化地，一个序列 $a$ 的最大子段和即为 $\max\limits_{l=1}^n\max\limits_{r=l}^n\left(\sum\limits_{i=l}^r a_i\right)$。**

罗伯特 · 兰登希望在瘟疫扩散之前找到有关的线索。于是他找到了你。

- - -

#### 【形式化题意】

给定一个只包含 $-1,0,1$ 的序列，求出往 $0$ 的位置上填 $k$ 个 $1$，其余填 $-1$ 后最大子段和的最大值。
## 输入格式

第一行两个正整数 $n,k$。

接下来一行 $n$ 个整数 $a_i\in\{-1,0,1\}$，其中 $0$ 表示数字模糊不清。
## 输出格式

一行一个正整数，表示可能的最大子段和。
## 样例

### 样例输入 #1
```
5 2
1 0 -1 0 0
```
### 样例输出 #1
```
2
```
## 提示

#### 【样例解释】

一种可行的方案是填入 $\{1,1,-1\}$，最大子段和为 $2$。

#### 【数据范围】


**本题开启捆绑测试。**

| $\text{SubTask}$ | 分值 | $n,k\le $ |
| :----------: | :----------: | :----------: |
| $0$ | $4$ | $20$ | 
| $1$ | $6$ | $200$ | 
| $2$ | $10$ | $5\times 10^3$ | 
| $3$ | $30$ | $5\times 10^5$ | 
| $4$ | $50$ | $10^7$ | 


对于 $100\%$ 的数据，$1\le n,k\le10^7$，$a_i\in \{-1,0,1\}$。保证 $k\le$ 序列中 $0$ 的个数。

**本题标程使用优化后的输入输出，在 O2 优化下最大点用时约 $350$ ms，足以通过此题。如果您自认为您的程序复杂度正确，却超出时间限制，请使用更优的输入输出方式，或者优化常数。**



---

