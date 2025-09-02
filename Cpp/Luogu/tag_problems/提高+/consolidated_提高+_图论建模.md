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

