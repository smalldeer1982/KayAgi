---
title: "[USTCPC 2025] 送温暖"
layout: "post"
diff: 省选/NOI-
pid: P12038
tag: ['二分', '2025', '背包 DP', '双指针 two-pointer', '折半搜索 meet in the middle', '高校校赛']
---
# [USTCPC 2025] 送温暖
## 题目描述

克露丝卡尔酱听说大家都是经验丰富的信息竞赛老手，轻松暴力踩标算。为了让大家都体验一下暴力踩标算的乐趣，所以克露丝卡尔酱准备了一道简单的送温暖题：

给定一个 $n$ 个点的树，点 $i$ 的点权为 $a_i$，你需要从中选出一个连通块，使得它们的点权和模 $M$ 的余数最大。克露丝卡尔酱想知道这个点权和模 $M$ 的余数最大是多少。
## 输入格式

第一行两个正整数 $n$ $(1\leqslant n \leqslant 33)$ 和 $M$ $(2\leqslant M \leqslant 10^9)$。

为了方便输入，我们输入时假定以 $1$ 为根，但是请注意这是一棵无根树。

第二行有 $n - 1$ 个整数，第 $i$ 个整数表示第 $i + 1$ 个点的父节点 $f_{i + 1}$ $(1\leqslant f_{i+1} < i+1)$。

第三行有 $n$ 个整数，$a_1, \cdots, a_n$ $(0 \leqslant a_i < M)$ 表示每个点的点权。
## 输出格式

共一个整数表示答案。
## 样例

### 样例输入 #1
```
6 10
1 2 3 4 5
7 7 7 7 7 7
```
### 样例输出 #1
```
8
```
## 提示

这棵树是一条链 `1 - 2 - 3 - 4 - 5 - 6`。最优解为选择一条长度为 4 的链（例如 `1 - 2 - 3 - 4` 或者 `2 - 3 - 4 - 5` 等等），此时答案为 $4 \times 7 \equiv 8\pmod {10}$。


---

---
title: "Life Lies in Movement"
layout: "post"
diff: 省选/NOI-
pid: P12499
tag: ['O2优化', '双指针 two-pointer', 'Ad-hoc', '洛谷比赛']
---
# Life Lies in Movement
## 题目背景

**在本题题目描述最后，我们提供了一份形式化题意**。

一个小镇马上要举行一场马拉松。
## 题目描述

这个小镇可以看作一个 $n$ 个点，$n-1$ 条边的无向树，每条边有正整数边权，每个点上都有一家住户。记 $\operatorname{dis}(u,v)$ 为 $u$ 到 $v$ 的简单路径的边权和。

主办方将选择一个起点 $u$ 和终点 $v$（需要保证 $u\neq v$），从 $u$ 到 $v$ 的简单路径就是本次比赛的赛道。届时，所有住户都会到赛道上去看比赛，第 $x$ 个点上的住户会到 $u\to v$ 简单路径上满足 $\operatorname{dis}(x,y)$ 最小的 $y$ 去（显然 $y$ 是唯一的），$\operatorname{dis}(y,v)$ 被称作这家住户的“激情值”，记作 $f(x,u,v)$。

设 $g(u,v)$ 表示所有住户的激情的平均值，即 $\frac{1}{n}\sum_{x=1}^nf(x,u,v)$，主办方认为，当 $g(u,v)\ge \frac{1}{2}\operatorname{dis}(u,v)+k$ 时，这场比赛是“成功的”。

现在给出常数 $k$，求有多少有序对 $(u,v)$ 使得比赛是“成功的”。

**形式化题意：**

给定一棵 $n$ 个点的带边权无向树。

设 $\operatorname{dis}(u,v)$ 表示从 $u$ 到 $v$ 的路径长度，$f(x,u,v)$ 表示 $u\to v$ 简单路径上离 $x$ 最近的一个点到 $v$ 的距离，$g(u,v)=\frac{1}{n}\sum_{x=1}^nf(x,u,v)$。

给定一个常数 $k$，求有多少有序对 $(u,v)$ 使得 $g(u,v)\ge \frac{1}{2}\operatorname{dis}(u,v)+k$。
## 输入格式

本题有多组测试数据，第一行输入一个正整数 $T$，代表数据组数。

对于每组数据，第一行输入两个数 $n,k$。

接下来 $n-1$ 行，每行三个数 $x,y,v$，代表有一条连结 $x,y$ 的，边权为 $v$ 的边，保证给出的是一棵树。
## 输出格式

对于每组数据，输出一行一个数字，代表答案。
## 样例

### 样例输入 #1
```
4
7 3
1 6 3
6 4 1
6 7 4
2 6 2
3 6 1
5 6 2
6 1
2 5 4
2 1 1
2 3 3
2 4 2
6 2 2
10 2
3 2 3
4 9 2
3 10 4
10 4 1
7 6 1
3 5 3
9 8 2
7 10 1
8 1 2
10 1
1 7 2
3 2 3
8 6 4
5 4 2
9 3 2
4 10 3
10 1 4
2 5 3
9 6 2

```
### 样例输出 #1
```
0
3
2
24
```
## 提示

#### 【数据范围】

对于所有数据，保证：
- $1\le T\le 10^4$
- $1\le n,\sum n\le 10^6$
- $1\le v,k\le10^6$

**本题采用打包测试**，各测试包描述如下：

| Subtask | $\sum n\le$ | 分值 |
| :----------: | :----------: | :----------: |
| $1$ | $500$ | $5$ |
| $2$ | $2000$ | $15$ |
| $3$ | $5000$ | $20$ |
| $4$ | $10^5$ | $20$ |
| $5$ | $3\times10^5$ | $20$ |
| $6$ | $10^6$ | $20$ |



---

---
title: "[NWRRC 2021] Day Streak"
layout: "post"
diff: 省选/NOI-
pid: P13631
tag: ['线段树', '2021', 'Special Judge', 'ICPC', '双指针 two-pointer', 'NWRRC']
---
# [NWRRC 2021] Day Streak
## 题目描述

Recently Deltaforces, a famous competitive programming website, added a lot of new visual information to user profiles. In particular, there is a maximum day streak --- the maximum number of days in a row with at least one problem solved. You decided that the maximum day streak in your profile does not accurately represent your training efforts. So you came up with a thought --- what if you could change the time zone in your profile to increase the maximum day streak?

Let's formalize this setting as follows. Suppose you have solved $n$ problems, and the $i$-th problem was solved at time $a_i$. There are $m$ time zones, numbered from $0$ to $m - 1$. The default time zone is $0$. If you decide to change your time zone to $t$, all solutions' timestamps increase by $t$: the problem solved at time $a_i$ is now considered to be solved at time $a_i + t$, for all $i$ simultaneously.

The problem solved at time $x$ is considered to be solved on day number $\lfloor \frac{x}{m} \rfloor$. Here $\lfloor v \rfloor$ means $v$ rounded down to the greatest integer less than or equal to $v$.

To display the maximum day streak, Deltaforces finds such $l$ and $r$ that you have solved at least one problem on each of days $l, l+1, \ldots, r$, and $r - l + 1$ is as large as possible. Then your maximum day streak is shown as $r - l + 1$.

Find the maximum day streak you can achieve by selecting a time zone.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 2 \cdot 10^5$). Description of the test cases follows.

The first line of each test case contains two integers $n$ and $m$ --- the number of solved problems and the number of time zones ($1 \le n \le 2 \cdot 10^5$; $1 \le m \le 10^9$). The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ --- distinct timestamps of your solutions, in chronological order ($0 \le a_1 < a_2 < \dotsb < a_n \le 10^9$).

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.
## 输出格式

For each test case, print two integers $s$ and $t$ --- the maximum day streak and any time zone that achieves it ($1 \le s \le n$; $0 \le t < m$).
## 样例

### 样例输入 #1
```
5
4 10
0 3 8 24
2 10
32 35
10 1
0 1 3 4 5 6 7 10 11 12
10 24
0 1 3 4 5 6 7 10 11 12
8 24
26 71 101 147 181 201 244 268
```
### 样例输出 #1
```
3 2
2 5
5 0
2 12
4 15
```
## 提示

In the first example test case, when you select time zone $2$, the timestamps of your solutions change to $2$, $5$, $10$, and $26$. It means the problems are now considered to be solved on days $0$, $0$, $1$, and $2$; that is a~$3$-day streak. Time zones $3$, $4$, and $5$ yield the same answer.

In the second example test case, timestamps of your solutions are $37$ and $40$ in time zone $5$, which corresponds to days $3$ and $4$. Time zones $6$ and $7$ also work.

In the third example test case, only one time zone exists, and your maximum day streak is $5$.

In the fourth example test case, you have solved many problems but in a short period of time, and you can't obtain more than a $2$-day streak.


---

---
title: "[USACO06FEB] Steady Cow Assignment G"
layout: "post"
diff: 省选/NOI-
pid: P2857
tag: ['贪心', '2006', '二分', 'USACO', '网络流', '枚举', '双指针 two-pointer']
---
# [USACO06FEB] Steady Cow Assignment G
## 题目描述

Farmer John's N (1 <= N <= 1000) cows each reside in one of B (1 <= B <= 20) barns which, of course, have limited capacity. Some cows really like their current barn, and some are not so happy.

FJ would like to rearrange the cows such that the cows are as equally happy as possible, even if that means all the cows hate their assigned barn.


Each cow gives FJ the order in which she prefers the barns.  A cow's happiness with a particular assignment is her ranking of her barn. Your job is to find an assignment of cows to barns such that no barn's capacity is exceeded and the size of the range (i.e., one more than the positive difference between the the highest-ranked barn chosen and that lowest-ranked barn chosen) of barn rankings the cows give their assigned barns is as small as possible.

## 输入格式

Line 1: Two space-separated integers, N and B


Lines 2..N+1: Each line contains B space-separated integers which are exactly 1..B sorted into some order. The first integer on line i+1 is the number of the cow i's top-choice barn, the second integer on that line is the number of the i'th cow's second-choice barn, and so on.


Line N+2: B space-separated integers, respectively the capacity of the first barn, then the capacity of the second, and so on. The sum of these numbers is guaranteed to be at least N.

## 输出格式

Line 1: One integer, the size of the minumum range of barn rankings the cows give their assigned barns, including the endpoints.

## 样例

### 样例输入 #1
```
6 4
1 2 3 4
2 3 1 4
4 2 3 1
3 1 2 4
1 3 4 2
1 4 2 3
2 1 3 2
```
### 样例输出 #1
```
2
```
## 提示

Explanation of the sample:




Each cow can be assigned to her first or second choice: barn 1 gets cows 1 and 5, barn 2 gets cow 2, barn 3 gets cow 4, and barn 4 gets cows 3 and 6.

## 题目翻译

有 $N$ 头牛，$B$ 个牛棚。告诉你每头牛心里牛棚的座次，即哪个牛棚他最喜欢，哪个第 $2$ 喜欢，哪个第 $3$ 喜欢，等等。但牛棚容量一定，所以每头牛分配到的牛棚在该牛心中的座次有高有低。现在求一种最公平的方法分配牛到牛棚，使所有牛中，所居牛棚的座次最高与最低的跨度最小。


---

---
title: "[LnOI2019] 第二代图灵机"
layout: "post"
diff: 省选/NOI-
pid: P5251
tag: ['线段树', '颜色段均摊（珂朵莉树 ODT）', '双指针 two-pointer']
---
# [LnOI2019] 第二代图灵机
## 题目背景

1989年，Abbi提出了一种抽象的计算模型 —— 第二代图灵机 (The 2nd Generation Turing Machine）。

所谓的第二代图灵机就是指一个抽象的机器，它有一条长度为$n$的纸带，纸带分成了$n$个小方格，每个方格有不同的**颜色**和不同的**数字**。

![avatar](https://cdn.luogu.com.cn/upload/pic/52955.png)

## 题目描述

第二代图灵的基本思想是用机器来模拟鹿们用纸笔进行数学运算的过程，他把这样的过程看作下列两种简单的动作：

1. 在纸带上的一格写数字.
2. 在纸带上的一段区间着色.

为了测试第二代图灵机的性能，Abbi提出了一种用于判定机器是否具有智能的试验方法，即图灵试验。

1. 求$[l,r]$中包含所有(一共$c$种)颜色，数字和最小的子区间的数字和。
2. 求$[l,r]$中没有重复颜色，数字和最大的子区间的数字和。

你需要为第二代图灵机编写算法，使他能通过所有的图灵试验。为保证试验的正确性，所有数据都是随机生成的。
## 输入格式

第一行输入两个正整数$n,m,c$，分表表示纸带长度，操作次数和颜色总数。

第二行$n$个非负整数，表示每个格子上的初始数字$a_i$。

第三行$n$个非负整数，表示每个格子上的颜色编号$b_i$。

接下来$m$行，对应每一次操作。

操作一格式：$1\quad x\quad y$，表示将第$x$位的数字改为$y$，保证$1≤y≤10000$.

操作二格式：$2\quad l\quad r\quad y$，表示将区间$[l,r]$的颜色全部改为$y$，保证$1≤y≤c$.

操作三格式：$3\quad l\quad r$，表示询问区间$[l,r]$中包含所有(一共$c$种)颜色，数字和最小的子区间的数字和。

操作四格式：$4\quad l\quad r$，表示询问区间$[l,r]$中没有重复颜色，数字和最大的子区间的数字和。
## 输出格式

对于操作三和操作四，输出一个整数，表示最小或最大的数字和。

对于操作三，若不存在满足条件的子区间，请输出$-1$。
## 样例

### 样例输入 #1
```
9 8 4
17 5 8 1 6 4 12 3 4
1 1 1 1 1 1 1 3 4
2 3 6 2
3 1 9
4 1 9
4 6 9
4 1 3
2 4 5 4
3 1 1
3 1 9
```
### 样例输出 #1
```
23
23
23
17
-1
23
```
## 提示

![avatar](https://cdn.luogu.com.cn/upload/pic/53113.png)

**由于数据规模较大，建议用以下方法读入一个正整数。**

```cpp
void read(int &x){
	char ch;
	while(ch = getchar(), ch < '!'); x = ch - 48;
	while(ch = getchar(), ch > '!') x = (x << 3) + (x << 1) + ch - 48;
}
```


---

---
title: "[USACO20DEC] Square Pasture G"
layout: "post"
diff: 省选/NOI-
pid: P7153
tag: ['数学', '2020', 'USACO', 'O2优化', '排序', '双指针 two-pointer']
---
# [USACO20DEC] Square Pasture G
## 题目描述

Farmer John 最大的牧草地可以被看作是一个由方格组成的巨大的二维方阵（想象一个巨大的棋盘）。现在，有 $N$ 头奶牛正占据某些方格（$1≤N≤200$）。

Farmer John 想要建造一个可以包围一块正方形区域的栅栏；这个正方形必须四边与 $x$ 轴和 $y$ 轴平行，最少包含一个方格。请帮助他求出他可以包围在这样的区域内的不同的奶牛子集的数量。注意空集应当被计算为答案之一。 
## 输入格式

输入的第一行包含一个整数 $N$。以下 $N$ 行每行包含两个空格分隔的整数，表示一头奶牛所在方格的坐标 $(x,y)$。所有 $x$ 坐标各不相同，所有 $y$ 坐标各不相同。所有 $x$ 与 $y$ 的值均在 $0…10^9$ 范围内。

注意尽管所有奶牛所在的方格坐标均非负，但围成的正方形区域可以包含坐标为负的方格。
## 输出格式

输出 FJ 可以包围的奶牛的子集数量。可以证明这个数量可以用 32 位有符号整数型存储。 
## 样例

### 样例输入 #1
```
4
0 2
2 3
3 1
1 0

```
### 样例输出 #1
```
14
```
### 样例输入 #2
```
16
17 4
16 13
0 15
1 19
7 11
3 17
6 16
18 9
15 6
11 7
10 8
2 1
12 0
5 18
14 5
13 2
```
### 样例输出 #2
```
420
```
## 提示

 - 测试点 1-5 中，所有奶牛所在的方格的坐标均小于 20 。
 - 测试点 6-10 中，$N≤20$。
 - 测试点 11-20 没有额外限制。

供题：Benjamin Qi 



---

---
title: "[COCI 2015/2016 #3] NEKAMELEONI"
layout: "post"
diff: 省选/NOI-
pid: P7230
tag: ['2015', '线段树', 'COCI（克罗地亚）', '双指针 two-pointer', '线段树分治']
---
# [COCI 2015/2016 #3] NEKAMELEONI
## 题目背景

> 「嘿，亲爱的！我要去给 $11$ 月 $28$ 日的 Croatian Open Competition In Informatics 出 T5。」      
> 「去吧，去吧……」 　　                       
> 「…」
> _____
> 「这题怎么样？」          
> 「唔……这太难了……会把那些小可爱难住的，换个简单些的吧……」           
> 于是可爱的出题人便出了这道题。
> ______
> 嘿！我会 $O(n^6)$ 的做法，$ n$ 的范围是什么？？
## 题目描述

给你一个 $n$ 个元素的数组。你需要处理 $q$ 个查询。

- 第一种查询需要你将数组中的第 $p$ 个数字改为 $v$。
- 第二种查询需要你确定当前数组中最短的连续子数组的长度，这个子数组必须要包含从 $1$ 到 $k$ 的所有数字。

## 输入格式

第一行，三个正整数 $n, k, m$。

第二行，$n$ 个正整数，用空格隔开，表示数组中的数。

接着，$m$ 行，表示 $m$ 个查询，每个查询有以下两种形式。
- $\texttt{1 p v}$：将数组中的第 $p$ 个数字改为 $v$。
- $\texttt{2}$：确定并输出当前数组中最短的连续子数组的长度，这个子数组必须要包含从 $1$ 到 $k$ 的所有数字。
## 输出格式

仅查询 $2$ 有输出。

对于每个查询 $2$，输出当前数组中最短的连续子数组的长度（这个子数组必须要包含从 $1$ 到 $k$ 的所有数字），若没有输出 $\texttt{-1}$。
## 样例

### 样例输入 #1
```
4 3 5
2 3 1 2
2
1 3 3
2
1 1 1
2

```
### 样例输出 #1
```
3
-1
4

```
### 样例输入 #2
```
6 3 6
1 2 3 2 1 1
2
1 2 1
2
1 4 1
1 6 2
2
```
### 样例输出 #2
```
3
3
4

```
## 提示

#### 数据范围及约定
- 对于 $30\%$ 的数据，$1\le n, m \le 5 \times 10 ^ 3$。
- 对于 $100\%$ 的数据，$1 \le n, m \le 10^5$，$1\le k \le 50$，$1 \le p \le n$，$1\le v \le k$。

#### 说明
翻译自 [COCI 2015-2016 #3 E NEKAMELEONI](https://hsin.hr/coci/archive/2015_2016/contest3_tasks.pdf)，满分 140。




---

---
title: "[JOISC 2021] 道路の建設案 (Road Construction) (Day2)"
layout: "post"
diff: 省选/NOI-
pid: P7561
tag: ['二分', '堆', '2021', '优先队列', 'K-D Tree', 'JOI（日本）', '双指针 two-pointer']
---
# [JOISC 2021] 道路の建設案 (Road Construction) (Day2)
## 题目背景

10s,2048M
## 题目描述

JOI 国是一个 $x\times y$ 的二维平面，王国里有 $n$ 个城镇，分别编号为 $1, 2, \cdots, n$，其中第 $i$ 个城镇的 **坐标** 为 $(x_i, y_i)$。

在 JOI 国，正计划修建连接两座城镇的路（下文简称：**「修路的项目」**），路有 $k$ 条。连接两个不同的城镇 $a$ 和 $b$ 将花费 $|x_a − x_b| + |y_a − y_b|$ 元。若有一条连接 $c$，$d$ 的路，则不需要也不可以在建一条连接 $d$，$c$ 的路，因为它们是相同的。

你要管理这个「修路的项目」，为了计算花费情况，你得弄明白连接一些城镇所需的花费。在这 $\dfrac{n\cdot(n-1)}{2}$ 条道路中，你想了解最便宜的 $k$ 条道路的花费。

给你城镇的坐标以及 $k$，请计算最便宜的 $k$ 条路所需要的钱。
## 输入格式

输入数据共 $n+1$ 行。

第一行，$2$ 个正整数 $n, k$，$n$ 表示城镇的数量，$k$ 含义见 **「题目描述」** 部分。

接下来的第 $2 \sim n+1$ 行，每行 $2$ 个正整数，分别是 $x_i$ 和 $y_i$，其中 $1\le i \le n$，表示第 $i$ 个城镇的坐标。
## 输出格式

输入数据共 $k$ 行。

对于第 $k$ 行，有一个整数表示第 $k$ 便宜的路需要的日元。
## 样例

### 样例输入 #1
```
3 2
-1 0
0 2
0 0

```
### 样例输出 #1
```
1
2

```
### 样例输入 #2
```
5 4
1 -1
2 0
-1 0
0 2
0 -2

```
### 样例输出 #2
```
2
2
3
3

```
### 样例输入 #3
```
4 6
0 0
1 0
3 0
4 0

```
### 样例输出 #3
```
1
1
2
3
3
4

```
### 样例输入 #4
```
10 10
10 -8
7 2
7 -8
-3 -6
-2 1
-8 6
8 -1
2 4
6 -6
2 -1

```
### 样例输出 #4
```
3
3
4
5
6
6
6
7
7
7

```
## 提示

#### 样例 #1 解释
有 $\dfrac{3 \times 2}{2} = 3$ 种方案。

- 城镇 $1 \to$ 城镇 $2$，$|(-1)-0|+|0-2| = 3$ 日元。
- 城镇 $1 \to$ 城镇 $3$，$|(-1)-0|+|0-0| = 1$ 日元。
- 城镇 $2 \to$ 城镇 $3$，$|0-0|+|2-0| = 2$ 日元。

将其进行排序为 $1,2,3$，所以输出是 $1$ 和 $2$。

本样例满足 Subtask $1, 4, 5, 6$。

#### 样例 #2 解释

有 $\dfrac{5 \times 4}{2} = 10$ 种方案。

将钱数排序后是 $2, 2, 3, 3, 3, 3, 4, 4, 4, 4$。

本样例满足 Subtask $1, 4, 5, 6$。

#### 样例 #3 解释

本样例满足 Subtask $1, 2, 4, 5, 6$。

#### 样例 #4 解释

本样例满足 Subtask $1, 4, 5, 6$。

#### 数据范围与约定

**本题采用 Subtask 计分法。**

| Subtask | 分值占比百分率 | $n$ | $k$ | $y_i$ |
| :----: | :----: | :----: | :----:| :----: |
| $1$ | $5\%$ | $\le 10^3$ | / | / |
| $2$ | $6\%$ | / | / | $=0$ |
| $3$ | $7\%$ | / | $=1$ | / |
| $4$ | $20\%$ | / | $\le 10$ | / |
| $5$ | $27\%$ |  / | $\le 10 ^ 5$ | / |
| $6$ | $35\%$ | / | / | / |

**注：斜线表示无特殊限制。**

对于 $100\%$ 的数据：
- $2 \le n \le 2.5 \times 10^5$；
- $1 \le k \le \min(2.5\times 10^5,\ \dfrac{n\cdot(n-1)}{2}$)；
- $-10^9 \le x_i, y_i \le 10^9$，且 $1 \le i \le n$；
- $(x_i,y_i)\not = (x_j, y_j)$ 且 $1 \le i < j \le n$。

#### 说明

本题译自 [第２０回日本情報オリンピック 2020/2021春季トレーニング合宿 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/index.html) [競技 2 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day2/2021-sp-d2-notice.pdf) [T2 日文题面](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day2/road_construction.pdf)。



---

---
title: "[WFOI - 02] I wanna escape the shadow（阴影）"
layout: "post"
diff: 省选/NOI-
pid: P8222
tag: ['洛谷原创', 'O2优化', '凸包', '旋转卡壳', '其它技巧', '洛谷月赛', '双指针 two-pointer']
---
# [WFOI - 02] I wanna escape the shadow（阴影）
## 题目背景

> Define adventure with death
>
> You are the shadow to my life

背景突然阴沉了下来，但是 kid 清楚，这是最黑暗的时刻，也是黎明之前...
## 题目描述

现在 kid 身处一个**圆心为 $(0,0)$，半径为 $r$ 的**圆中，并且学会了一种新的操作 `mklig(X,Y,Z)` 来消除黑暗，具体如下：

$X,Y,Z$ 是三个不同的点，作射线 $XY,ZY$，设两条射线与圆周交于 $d_1,d_2$，那么将 弧 $d_1d_2$，线段 $Yd_1,Yd_2$ 围成的区域照亮。

现在圆内有一些点，记 $S_{光}$ 是圆的半径为 $r$ 的时候被照亮的总面积，现在 kid 想知道在使 $\lim\limits_{r \to \infty} \dfrac{S_{光}}{\pi r^2}$ （可以理解为 r 无穷大时）最大时，最少需要多少次 `mklig` 操作。你只需要给出答案，剩下的操作就交给 €€£ 吧！

数据保证不存在三点共线。
## 输入格式

**本题有多组数据**

第一行一个整数 $T$，表示数据组数；

对于每组数据：

第一行一个正整数 $n$；

接下来 $n$ 行，每行两个整数，分别表示一个点的横纵坐标。
## 输出格式

共 $T$ 行，每行一个整数，表示答案。
## 样例

### 样例输入 #1
```
1
3
0 0
0 2
-1 1
```
### 样例输出 #1
```
3
```
## 提示

- ####  样例解释

![](https://s1.ax1x.com/2022/03/14/bXTM01.png)

**本题采用 Subtask 捆绑测试。**

- $\texttt{Subtask \#0 (30pts)}$：$n = 10^3$ 且数据随机；
- $\texttt{Subtask \#1 (30pts)}$：$n \le 5$ ；
- $\texttt{Subtask \#2 (40pts)}$：$n \le 10^6$；

对于每个测试点，保证 $T \le 5 ，\sum n\le 10^6$，点的坐标的绝对值不超过 $10^9$。


---

---
title: "「Wdoi-5」建立与摧毁的结界"
layout: "post"
diff: 省选/NOI-
pid: P8227
tag: ['贪心', '递归', '洛谷原创', '树形 DP', '洛谷月赛', '双指针 two-pointer']
---
# 「Wdoi-5」建立与摧毁的结界
## 题目背景

八云紫拥有操控境界程度的能力。作为其式神的八云蓝，同样拥有一定程度的操作境界的能力，而作为八云蓝的式神橙，却因为功力尚且不足，而无法对境界进行过多的干预了。

于是八云蓝打算教教橙，境界的用法。境界可以被抽象成一层一层的括号，操作境界本质上就是对括号序列进行修改。由于橙的能力尚且不足，因此只能进行一些简单的境界的建立与摧毁。

尽管如此，通过简单的操作，亦可以把一个境界转换为另外一个境界。为了给橙作为练习，蓝找来了两个境界的范本。将其中一个境界转换为另外一个境界的难度，就是橙需要施用能力的最小次数。但是由于境界实在太长，蓝决定写一个程序（？）来帮帮她计算出境界的难度。
## 题目描述

境界可以被抽象为由圆括号组成的括号序列。现做出如下定义：

- 定义 $D_i$ 为**嵌套括号序列**。其中 $D_0$ 为零阶嵌套括号序列，被定义为单组括号 $\verb!()!$；而 $D_k$ 则为 $k$ 阶嵌套括号序列（$k \geq 1$）定义为 $\verb!(!D_{k-1}\verb!)!$，即在 $D_{k-1}$ 的外层增添了一层括号。
- 定义 $F_i$ 为**平铺括号序列**。其中 $F_0$ 为零阶平铺括号序列，被定义为单组括号 $\verb!()!$；而 $F_k$ 则为 $k$ 阶平铺括号序列（$k \geq 1$），定义为 $\verb!()!F_{k-1}$，即在 $F_{k-1}$ 的左侧增添了一对括号。

例如，$\verb!((()))!$ 为 $D_2$，$\verb!()()()()!$ 为 $F_{3}$。

现在蓝给出了两个长度为 $n$ 的**合法**括号序列 $A$ 和 $B$。橙可以用以下操作对序列 $A$ 进行变换：

- 选择任意非负整数 $k$，选择括号序列的一个子串满足其为一个 $k$ 阶嵌套括号序列，然后将其变为 $k$ 阶平铺括号序列。
- 选择任意非负整数 $k$，选择括号序列的一个子串满足其为一个 $k$ 阶平铺括号序列，然后将其变为 $k$ 阶嵌套括号序列。

**提示说明**处有「合法括号序列」与「子串」的定义。

现在需要求出将序列 $A$ 变换为序列 $B$ 所需的最少操作数。可以证明，总存在一种操作方案能将序列 $A$ 变换为序列 $B$。
## 输入格式

- 第一行共有一个整数 $n$，表示 $A$ 与 $B$ 括号序列的长度。
- 接下来一行，共有 $n$ 个字符，描述括号序列 $A$。保证序列 $A$ 合法。
- 接下来一行，共有 $n$ 个字符，描述括号序列 $B$。保证序列 $B$ 合法。
## 输出格式

- 共一行，一个整数，表示将 $A$ 转换为 $B$ 需要的最少步数（可能为 $0$，也就是不进行任何操作）。
## 样例

### 样例输入 #1
```
14
((()())(()()))
()()()()()()()
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
14
((()())(()()))
(()())(()())()
```
### 样例输出 #2
```
10
```
## 提示

样例 $3$ 见下发的附件  $\textbf{\textit{border3.in/border3.ans}}$。  
样例 $4$ 见下发的附件  $\textbf{\textit{border4.in/border4.ans}}$。满足特殊性质 $\text{A}$（见下文）。  
样例 $5$ 见下发的附件  $\textbf{\textit{border5.in/border5.ans}}$。  

#### 样例 1 解释

- 第一步：$\texttt{((\underline{()()})(()()))}\to\texttt{((\underline{(())})(()()))}$。
- 第二步：$\texttt{(((()))(\underline{()()}))}\to\texttt{(((()))(\underline{(())}))}$。
- 第三步：$\texttt{(((()))\underline{((()))})}\to\texttt{(((()))\underline{()()()})}$。
- 第四步：$\texttt{(\underline{((()))}()()())}\to\texttt{(\underline{()()()}()()())}$。
- 第五步：$\texttt{(\underline{()()()()()()})}\to\texttt{(\underline{(((((())))))})}$。
- 第六步：$\texttt{\underline{((((((()))))))}}\to\texttt{\underline{()()()()()()()}}$。

可以证明，不存在更短的方案。

#### 提示

**合法括号序列**通过这样一个形式定义：

- $\verb!()!$ 是合法括号序列。
- 若 $A$ 是合法括号序列，那么 $\verb!(!A\verb!)!$ 是合法括号序列。
- 若 $A,B$ 均为合法括号序列，那么 $AB$ 是合法括号序列。

我们称 $A$ 是 $B$ 的**子串**，当且仅当删除 $B$ 开头若干个字符（可以不删除），再删除 $B$ 末尾若干个字符（可以不删除），剩下来的字符序列与 $A$ 完全相同。

#### 数据范围及约定

本题共有 $20$ 个测试点，每个测试点 $5$ 分。最终分数为所有测试点分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \bm{n\le } & \textbf{特殊性质} \cr\hline
1\sim 4 & 10 & - \cr\hline
5\sim 7 & 2\times 10^3 & \text{A} \cr\hline
8\sim 10 & 2\times 10^3 & - \cr\hline
11\sim 15 & 10^6 & \text{A} \cr\hline
16\sim 20 & 10^6 & - \cr\hline
\end{array}
$$

**特殊性质** $\textbf{A}$：保证 $B$ 是 $(n\div 2-1)$ 阶平铺括号序列。

#### 友情提醒

考虑到选手可能会用不同的方式进行字符串的读入，这里保证输入文件**每行末尾没有多余空格**，并且每行都以 `\n` 结尾（也就是说，不会出现多余的 `\r`）。


---

---
title: "「WHOI-2」D&D"
layout: "post"
diff: 省选/NOI-
pid: P8434
tag: ['动态规划 DP', '搜索', '数学', '二分', '洛谷原创', 'O2优化', '位运算', '双指针 two-pointer']
---
# 「WHOI-2」D&D
## 题目背景

有没有发现少了什么？

我们的 miku 决定出门逛街了。但是好巧不巧的就是她家里的装饰物少的可怜，并且只有一些数字可以作为装饰。

但是 miku 发现如果有若干个装饰物组成的数集 $A$，那么 $A$ 的子集 $f(A)$ 是最好看的（尽管不知道为什么）。所以就有了这道题。

但是因为看到了标题，所以聪明的你应该知道 miku 要去哪里了（误）。
## 题目描述

给定**不重**集合 $A$，定义其 _装饰子集_ 

$$f(A)=\{a\in A|\forall b\in A-\{a\},a|b\not= b \}$$

这里的 $\texttt{“|”}$ 表示按位或；这里 $b\in A-\{a\}$ 表示 $b\in A$ 且 $b\not=a$。

miku 有一个长度为 $n$ 的正整数序列 $a_i$。你要给这个序列连续地划分为若干个（至少一个）连续子串。要求这些连续子串元素所组成的**不重集合**的 _装饰子集_ 相同。

求方案数对 $10^9+7$ 取模。
## 输入格式

第一行一个正整数表示 $n$。

接下来长度为 $n$ 的正整数序列表示 $a_i$。
## 输出格式

一行一个正整数表示答案。
## 样例

### 样例输入 #1
```
10
1 2 3 4 5 5 4 3 2 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
9
1 2 2 1 1 1 2 2 1
```
### 样例输出 #2
```
16
```
## 提示

**【样例#1解释】** 可以证明，两种方法分别是：
$$[1,2,3,4,5,5,4,3,2,1]$$
$$[1,2,3,4,5],[5,4,3,2,1]$$

这里三个子集所组成的不重集合都是 $\{1,2,3,4,5\}$。它们的装饰子集都是 $\{3,5\}$。具体说明如下：

- $1:1|3=3$，故不属于。
- $2:2|3=3$，故不属于。
- $3:3|1=3,3|2=3,3|4=7,3|5=7$，故属于。
- $4:4|5=5$，故不属于。
- $5:5|1=5,5|2=7,5|3=7,5|4=5$，故属于。

---
**本题采用捆绑测试**

- $\text{subtask1(5pts)}:n\leq10$。
- $\text{subtask2(10pts)}:a_i\leq7$。
- $\text{subtask3(20pts)}:a_i=2^a+2^b$。其中 $a\not = b$。
- $\text{subtask4(20pts)}:a_i=2^a+2^b$。其中不保证 $a\not =b$。
- $\text{subtask5(10pts)}:$ 保证 $a_i$ 随机生成。
- $\text{subtask6(35pts)}:$ 无特殊限制。时限为 $3s$。

对于 $100\%$ 的数据，保证 $1\leq n\leq 3\times10^6,0\leq a_i\leq2\times 10^6$。


---

---
title: "[POI 2020/2021 R3] Suma liczb pierwszych"
layout: "post"
diff: 省选/NOI-
pid: P9407
tag: ['2020', 'POI（波兰）', 'Special Judge', '素数判断,质数,筛法', '双指针 two-pointer', '根号分治']
---
# [POI 2020/2021 R3] Suma liczb pierwszych
## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Suma liczb pierwszych](https://szkopul.edu.pl/problemset/problem/8brtPux-IyytS6rOoOR1cJTL/statement/)。

d2t3。
## 题目描述

给你一个数字 $n$，求 $l,r$，使 $[l,r]$ 区间内的所有质数之和等于 $n$。

如果有多解，任意一组均可；无解输出 `NIE`。
## 输入格式

一行一个正整数 $n$。
## 输出格式

如果有解，一行两个正整数 $l,r$，你的答案。

如果无解，输出 `NIE`。
## 样例

### 样例输入 #1
```
15

```
### 样例输出 #1
```
3 7

```
### 样例输入 #2
```
9992

```
### 样例输出 #2
```
4993 4999

```
### 样例输入 #3
```
100000000

```
### 样例输出 #3
```
NIE

```
### 样例输入 #4
```
1000000007

```
### 样例输出 #4
```
1000000007 1000000007

```
### 样例输入 #5
```
99999999996

```
### 样例输出 #5
```
295693 1693067

```
## 提示

对于所有数据，$1\leq n\leq 10^{11}$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $n\leq 10000$ | 15 |
| 2 | $n\leq 10^8$ | 20 |
| 3 | $n\leq 2\times 10^9$ | 40 |
| 4 |  | 25 |


---

