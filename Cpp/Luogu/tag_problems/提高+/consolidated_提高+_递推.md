---
title: "「Daily OI Round 3」Xor Graph"
layout: "post"
diff: 提高+/省选-
pid: P10128
tag: ['递推', '洛谷原创', 'O2优化']
---
# 「Daily OI Round 3」Xor Graph
## 题目背景

在黎明来临之前，总要有人照亮黑暗。
## 题目描述

Xs_siqi 给了你 $2^n$ 个点，$x$ 到 $y$ 有**有向**边当且仅当 $x\operatorname{xor} y=2^k,k \in [0,n)$，且 $x>y$。其中，$\operatorname{xor}$ 表示按位异或，$k$ 为整数。令 $f_{x,y}$ 为 $x$ 点到 $y$ 点的不同路径数，求： 

$$\sum_{i=1}^{2^n}\sum_{j=1}^{2^n}f_{i,j}(i\neq j)$$

答案对 $998244353$ 取模。
## 输入格式

第一行，一个整数 $t$。

接下来 $2 \sim t+1$ 行，一行一个整数表示 $n$。
## 输出格式

共 $t$ 行，每行一个整数表示题目要求的方案数。
## 样例

### 样例输入 #1
```
4
2
3
50
999998
```
### 样例输出 #1
```
2
15
599192517
81627972
```
## 提示

#### 【样例解释 #1】

对于样例的第一组，$3$ 向 $1,2$ 连边，这样 $3$ 到 $1$ 是一个方案，$3$ 到 $2$ 是一个方案，一共有 $2$ 个方案。

#### 【数据范围】

对于全部数据保证：$1 \le t \le 10^6$，$1 \le n \le 10^7$。


---

---
title: "[NOIP 2005 普及组] 循环"
layout: "post"
diff: 提高+/省选-
pid: P1050
tag: ['模拟', '字符串', '高精度', '递推', '2005', 'NOIP 普及组']
---
# [NOIP 2005 普及组] 循环
## 题目描述

乐乐是一个聪明而又勤奋好学的孩子。他总喜欢探求事物的规律。一天，他突然对数的正整数次幂产生了兴趣。


众所周知，$2$ 的正整数次幂最后一位数总是不断的在重复 $2,4,8,6,2,4,8,6…$ 我们说 $2$ 的正整数次幂最后一位的循环长度是 $4$（实际上 $4$ 的倍数都可以说是循环长度，但我们只考虑最小的循环长度）。类似的，其余的数字的正整数次幂最后一位数也有类似的循环现象：

$$
\def\arraystretch{1.5}
\begin{array}{c|c|c}\hline
\textbf{数字}& \textbf{循环} & \textbf{循环长度} \cr\hline\hline
2 & 2,4,8,6 & 4\cr\hline
3 & 3,9,7,1 & 4\cr\hline
4 & 4,6 & 2\cr\hline
5 & 5 &  1\cr\hline
6 & 6 & 1\cr\hline
7 & 7,9,3,1 & 4\cr\hline
8 & 8,4,2,6 & 4\cr\hline
9 & 9,1 & 2\cr\hline
\end{array}
$$

这时乐乐的问题就出来了：是不是只有最后一位才有这样的循环呢？对于一个整数 $n$ 的正整数次幂来说，它的后 $k$ 位是否会发生循环？如果循环的话，循环长度是多少呢？

注意：

1. 如果 $n$ 的某个正整数次幂的位数不足 $k$，那么不足的高位看做是 $0$。
2. 如果循环长度是 $L$，那么说明对于任意的正整数 $a$，$n$ 的 $a$ 次幂和 $a+L$ 次幂的最后 $k$ 位都相同。

## 输入格式

共一行，包含两个整数 $n$ 和 $k$。$n$ 和 $k$ 之间用一个空格隔开，表示要求 $n$ 的正整数次幂的最后 $k$ 位的循环长度。
## 输出格式

一个整数，表示循环长度。如果循环不存在，输出 $-1$。
## 样例

### 样例输入 #1
```
32 2
```
### 样例输出 #1
```
4
```
## 提示

**【数据范围】**

对于 $30 \%$ 的数据，满足 $k \le 4$；  
对于$100 \%$ 的数据，满足 $1 \le n < {10}^{100}$，$1 \le k \le 100$。

**【题目来源】**

NOIP 2005 普及组第四题


---

---
title: "低价购买"
layout: "post"
diff: 提高+/省选-
pid: P1108
tag: ['动态规划 DP', '递推', '枚举']
---
# 低价购买
## 题目描述

“低价购买”这条建议是在奶牛股票市场取得成功的一半规则。要想被认为是伟大的投资者，你必须遵循以下的问题建议:“低价购买；再低价购买”。每次你购买一支股票,你必须用低于你上次购买它的价格购买它。买的次数越多越好!你的目标是在遵循以上建议的前提下，求你最多能购买股票的次数。你将被给出一段时间内一支股票每天的出售价，你可以选择在哪些天购买这支股票。每次购买都必须遵循“低价购买；再低价购买”的原则。写一个程序计算最大购买次数。

这里是某支股票的价格清单：

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|c|c|c|c|c|c|c|}\hline
\textsf{日期} & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & 9 & 10 & 11 & 12 \cr\hline
\textsf{价格} & 68 & 69 & 54 & 64 & 68 & 64 & 70 & 67 & 78 & 62& 98 & 87 \cr\hline
\end{array}$$

最优秀的投资者可以购买最多 $4$ 次股票，可行方案中的一种是：

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|}\hline
\textsf{日期} & 2 & 5 & 6 & 10 \cr\hline
\textsf{价格} & 69 & 68 & 64 & 62 \cr\hline
\end{array}
$$

## 输入格式

第一行共一个整数 $N\ (1  \le  N  \le 5000)$，股票发行天数

第二行一行 $N$ 个整数，是每天的股票价格。保证是大小不超过 $2^{16}$ 的正整数。

## 输出格式

输出共一行两个整数，分别为最大购买次数和拥有最大购买次数的方案数（数据保证 $ \le 2^{31}$）当二种方案“看起来一样”时（就是说它们构成的价格队列一样的时候）,这 $2$ 种方案被认为是相同的。

## 样例

### 样例输入 #1
```
12
68 69 54 64 68 64 70 67 78 62 98 87

```
### 样例输出 #1
```
4 2

```


---

---
title: "「FAOI-R9」决战黎明"
layout: "post"
diff: 提高+/省选-
pid: P12398
tag: ['贪心', '递推', '二分', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「FAOI-R9」决战黎明
## 题目背景

牢光是一个很会发明小游戏的人。

清风喜欢和明月玩棋。有一天，他玩了一款牢光发明的《智棋之决战黎明》，因为游戏的趣味而欲罢不能，可惜明月太聪明了，他总是被明月虐。于是，他决定把这个问题推给你让你帮他研究。
## 题目描述

一些概念的定义如下：

* 战线：棋子按照玩家给定的顺序排列的轨道，**棋子一旦落入战线，即必须在这个战线上行动**。

* 棋子等级：玩家给棋子赋予的等级，会且只会因为「对战」的结果产生变化。**初始时这个等级必须为正整数。**

* 对战：对于两个棋子的对战，当棋子等级相等时，两个棋子均被消除；当两个棋子等级不等时，等级大的棋子等级减少 $ 1 $，等级小的棋子被消除。在一次对战中，显然至少会消除掉 $ 1 $ 个棋子。

游戏流程如下：

* 初始时双方游戏积分均为 $ 0 $。

* **准备阶段**：双方玩家规定本方的棋子数量，每个棋子的棋子等级、所属战线和出场顺序。**注意可以在某条战线上不放置任何棋子。**

* **对战阶段**：对于每条战线，进行如下流程（注意这里「在场棋子」指**本条战线上**未被消除的棋子）：

  * 如果两方均没有在场的棋子，则这个战线的流程结束。

  * 如果一方已经没有在场的棋子，则另一方获得与在场棋子的等级之和相等的游戏积分，这个战线的流程结束。
  
  * 如果双方均有在场的棋子，则两方在场的出场顺序最靠前的棋子进行一次「对战」。

* **结算阶段**：当所有战线的流程结束后，两个玩家的游戏积分则为本次游戏的结果。

在本局游戏中，有 $ n $ 个战线。

明月已经完成了自己的准备阶段，但是清风在自己未完成准备时偷偷看到了明月的全部 $ n $ 个战线的准备方案。

请你帮助清风设计一种准备方案，使得清风的所有棋子的初始等级均为正整数且和不超过 $ m $，且游戏结束后明月的游戏积分最少，你只需要输出这个最少的积分量即可。

因为清风很爱玩，所以你总共要对于 $ T $ 轮各自独立的游戏给出答案。
## 输入格式

第一行两个整数 $ T,n $，代表数据组数和每局游戏的战线条数。

对于每组数据：

第一行一个整数 $ m $，代表本局游戏清风的棋子等级之和上限。

接下来 $ n $ 行的第 $ i $ 行，每行开头一个整数 $ l_i $ 代表这个战线明月排布的棋子数量，接下来 $ l_i $ 个整数，依次表示明月阵营出场的每个棋子的等级（$ l_i $ 个棋子的出场顺序即为它们的读入顺序）。
## 输出格式

对于每组数据，输出一行一个整数，代表题目要求的答案。
## 样例

### 样例输入 #1
```
5 1
2
2 1 1
2
3 1 1 1
3
4 4 3 2 1
7
5 4 3 6 2 1
101
10 10 100 10 100 10 10 10 100 10 10
```
### 样例输出 #1
```
0
1
7
6
260
```
### 样例输入 #2
```
3 2
10
1 7
3 1 5 1
14
8 4 3 2 1 4 3 2 1
8 4 3 2 1 4 3 2 1
13
5 4 3 8 7 1
6 3 5 4 3 2 1
```
### 样例输出 #2
```
4
9
14
```
## 提示

**【样例 1 解释】**

对于第一组数据，一种方案是清风派出初始等级为 $ 2 $ 的棋子一枚。

对战流程如下：

* 清风在场棋子等级分别为 $ \{2\} $，明月在场棋子等级分别为 $ \{1,1\} $，等级为 $ 2 $ 的清风棋子和等级为 $ 1 $ 的明月棋子对战，明月棋子被消除，清风棋子等级降为 $ 1 $。

* 清风在场棋子等级分别为 $ \{1\} $，明月在场棋子等级分别为 $ \{1\} $，双方均派出等级为 $ 1 $ 的棋子出战，均被消除。

* 双方均已无棋子，该条战线不影响双方积分。

因此，该种方案明月的积分为 $ 0 $。

**【数据规模与约定】**

**本题采用捆绑测试。**

对于每个测试点：

* $ 1 \le T \le 5 $；

* $ \bm{1 \le n \le 2} $，$ 1 \le l_i \le 10^5 $；

* $ 0 \le m \le 10^{18} $，明月的棋子等级均为正整数且不超过 $ 10^9 $。

| 子任务编号 | $ n $ | $ l_i $ | $ m $ | 明月棋子等级上限 | 分值 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| $ 1 $ | $ =1 $ | $ \le 5 $ | $ \le 10 $ | $ \le 5 $ | $ 8 $ |
| $ 2 $ | $ =1 $ | $ \le 300 $ | $ \le 300 $ | $ \le 5 $ | $ 16 $ |
| $ 3 $ | $ =1 $ | - | - | $ =1 $ | $ 4 $ |
| $ 4 $ | $ =1 $ | - | - | - | $ 24 $ |
| $ 5 $ | $ =2 $ | - | $ =0 $ | - | $ 4 $ |
| $ 6 $ | $ =2 $ | $ \le 300 $ | - | - | $ 8 $ |
| $ 7 $ | $ =2 $ | $ \le 5000 $ | - | - | $ 12 $ |
| $ 8 $ | $ =2 $ | - | - | - | $ 24 $ |


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
title: "[NOIP 2011 提高组] 观光公交"
layout: "post"
diff: 提高+/省选-
pid: P1315
tag: ['贪心', '递推', '2011', 'NOIP 提高组']
---
# [NOIP 2011 提高组] 观光公交
## 题目背景

感谢 @Transhumanist 提供的一组 Hack 数据
## 题目描述

风景迷人的小城 Y 市，拥有 $n$ 个美丽的景点。由于慕名而来的游客越来越多，Y 市特意安排了一辆观光公交车，为游客提供更便捷的交通服务。观光公交车在第 $0$ 分钟出现在 $1$ 号景点，随后依次前往 $2,3,4,\cdots,n$ 号景点。从第 $i$ 号景点开到第 $i+1$ 号景点需要 $D_i$ 分钟。任意时刻，公交车只能往前开，或在景点处等待。

设共有 $m$ 个游客，每位游客需要乘车 $1$ 次从一个景点到达另一个景点，第 $i$ 位游客在 $T_i$ 分钟来到景点 $A_i$，希望乘车前往景点 $B_i$（$A_i<B_i$）。为了使所有乘客都能顺利到达目的地，公交车在每站都必须等待需要从该景点出发的所有乘客都上车后才能出发开往下一景点。

假设乘客上下车不需要时间。一个乘客的旅行时间，等于他到达目的地的时刻减去他来到出发地的时刻。因为只有一辆观光车，有时候还要停下来等其他乘客，乘客们纷纷抱怨旅行时间太长了。于是聪明的司机 ZZ 给公交车安装了 $k$ 个氮气加速器，每使用一个加速器，可以使其中一个 $D_i-1$。对于同一个 $D_i$ 可以重复使用加速器，但是必须保证使用后 $D_i\ge0$。

那么 ZZ 该如何安排使用加速器，才能使所有乘客的旅行时间总和最小？
## 输入格式

第 $1$ 行是 $3$ 个整数 $n,m,k$，每两个整数之间用一个空格隔开。分别表示景点数、乘客数和氮气加速器个数。

第 $2$ 行是 $n-1$ 个整数，每两个整数之间用一个空格隔开，第 $i$ 个数表示从第 $i$ 个景点开往第 $i+1$ 个景点所需要的时间，即 $D_i$。

第 $3$ 行至 $m+2$ 行每行 $3$ 个整数 $T_i,A_i,B_i$，每两个整数之间用一个空格隔开。第 $i+2$ 行表示第 $i$ 位乘客来到出发景点的时刻，出发的景点编号和到达的景点编号。
## 输出格式

一个整数，表示最小的总旅行时间。

## 样例

### 样例输入 #1
```
3 3 2
1 4
0 1 3
1 1 2
5 2 3
```
### 样例输出 #1
```
10

```
## 提示

**【输入输出样例说明】**

对 $D_2$ 使用 $2$ 个加速器，从 $2$ 号景点到 $3$ 号景点时间变为 $2$ 分钟。

公交车在第 $1$ 分钟从 $1$ 号景点出发，第 $2$ 分钟到达 $2$ 号景点，第 $5$ 分钟从 $2$ 号景点出发，第 $7$ 分钟到达 $3$ 号景点。

第 $1$ 个旅客旅行时间 $7-0=7$ 分钟。

第 $2$ 个旅客旅行时间 $2-1=1$ 分钟。

第 $3$ 个旅客旅行时间 $7-5=2$ 分钟。

总时间 $7+1+2=10$ 分钟。

**【数据范围】**

对于 $10\%$ 的数据，$k=0$。

对于 $20\%$ 的数据，$k=1$。

对于 $40\%$ 的数据，$2 \le n \le 50$，$1 \le m \le 10^3$，$0 \le k \le 20$，$0 \le D_i \le 10$，$0 \le T_i \le 500$。

对于 $60\%$ 的数据，$1 \le n \le 100$，$1 \le m \le 10^3$，$0 \le k \le 100$，$0 \le D_i \le 100$，$0 \le T_i \le 10^4$。

对于 $100\%$ 的数据，$1 \le n \le 10^3$，$1 \le m \le 10^4$，$0 \le k \le 10^5$，$0 \le D_i \le 100$，$0 \le T_i \le 10^5$。


---

---
title: "[GDCPC 2024] 循环赛"
layout: "post"
diff: 提高+/省选-
pid: P13355
tag: ['数学', '递推', '2024', '广东', '分类讨论', 'XCPC']
---
# [GDCPC 2024] 循环赛
## 题目背景

数据、标程、题解等资源的获取：<https://gitlink.org.cn/thusaa/gdcpc2024>
## 题目描述

`T` 协会的主席大 `G` 决定选出一位小 `g` 继任 `T` 协会的主席之位。为了保证公平性，他任命小 `c` 担任监督。

考虑到 `T` 协会的小 `g` 们不是很多，小 `c` 决定通过最简单的方式决出胜者：让这 $n$ 个小 `g` 两两进行一场没有平局的对决，胜者获得一分，败者则不获得的分数。

在比赛结束、统计分数的时候，小 `c` 发现了关于本次 $\frac{n(n-1)}{2}$ 场对决的 “$z$-`gg` 定律”，即在任意 $z+1$ 个小 `g` 中，总存在一个小 `g` 能打败其余 $z$ 个小 `g`，**同时**存在另一个小 `g` 被其余 $z$ 个小 `g` 打败。

由于某些来自 `T` 协会的神秘因素，小 `c` 突然想知道在所有符合上述 “$z$-`gg` 定律” 的对决中，$n$ 个小 `g` **最少**有多少种不同的得分？由于小 `c` 忙(bu)于(shi)统(te)计(bie)数(cong)据(ming)，所以她决定将这个问题交给你来回答。
## 输入格式

本题有多组数据。

第一行包含一个整数 $T(1\le T\le 3\times 10^5)$ 表示数据组数。

接下来 $T$ 行，每行两个正整数 $n,z(1\le z<n\le 10^{18})$ 如题面所述。
## 输出格式

$T$ 行，每行一个正整数表示答案。
## 样例

### 样例输入 #1
```
5
2 1
3 1
3 2
4 1
4 3
```
### 样例输出 #1
```
2
1
3
2
4
```
### 样例输入 #2
```
6
7 1
7 2
7 3
7 4
7 5
7 6
```
### 样例输出 #2
```
1
7
7
7
5
3
```
## 提示

### 样例 1 解释

对 $n=2, z=1$，显然此时两个小 `g` 得分必然一个是 $1$，另一个是 $0$，故答案为 $2$。

对 $n=3, z=1$，`1=>2, 2=>3, 3=>1` （`a=>b` 表示 “a 打败 b”，下同）满足定律，且每个人得分均为 $1$ 分；

对 $n=3, z=2$，由对称性以及题设定律，不妨设 `1` 和 `3` 是 $3$ 个小 `g` 中的全胜和全败者，那么这场比赛必定为 `1=>2, 1=>3, 2=>3`，此时三人得分依次为 $2, 1, 0$，故答案为 $3$。

对 $n=4, z=1$，`1=>3, 1=>4, 2=>1, 2=>3, 3=>4, 4=>2` 中四人得分依次为 $2, 2, 1, 1$，并且由于四人得分之和 $\frac{4\times 3}{2}=6$ 不是 $4$ 的倍数，故四人得分不可能完全一致，故答案为 $2$。

对 $n=4, z=3$，仍设四人中全胜和全败者为 `1` 和 `4`，则此时 `2`、`3` 两人得分之和为 $6 - 3 - 0 = 3$，因此二者得分只能为 $2, 1$ 或者 $3, 0$；又显然不可能同时有两个得分为 $3$ 分者，故此时 `2` 和 `3` 的得分必为 $2, 1$，故答案为 $4$。

### 提示

本题并不难。


---

---
title: "Charlie的云笔记序列"
layout: "post"
diff: 提高+/省选-
pid: P1370
tag: ['动态规划 DP', '递推', '生成树']
---
# Charlie的云笔记序列
## 题目背景

Charlie 是 oiinhand 的忠实粉丝。他有使用 oih 云笔记记录自己的题解的习惯。只有一点一滴的积累才能留下自己的足迹。

oih 云笔记有什么特点吗？

oih 的站长 soha 表示，目前 oih2 的云笔记功能比较简陋，但是正在开发 oih3 中的新版云笔记功能将是世界上最适合 oier 的储藏笔记的工具。

首先，新版云笔记支持 markdown 功能，并且可以实时预览，插入公式图片都不是问题。实时自动保存，不用担心突然断电啊文档消失，而且不管在哪里都可以看！

其次，可以一键生成题解模板摘要，不用各种复制粘贴了，超省事！

再者，云笔记可以给其他同学分享自己的笔记，共同进步。写完了笔记，还可以一键向洛谷投稿呢！

然而 Charlie 最喜欢的功能是 oih 的题目收藏。现在他收藏了一系列题目，但是觉得不过瘾所以正在玩弄这个功能。
## 题目描述

某天，Charlie 将收藏的题目抽象为一个序列。$a=[a_1,a_2,a_3,\cdots,a_{n-1},a_n]$。

设 $a[l:r]$ 表示序列 ${a_i}$ 第 $l$ 个数到第 $r$ 个数之间的子串，其中 $1 \le l \le r \le n$。形式化地，$a[l:r]={a_l,a_{l+1},a_{l+2},\cdots,a_{r-1},a_r}$。比如说，$a=[9,8,0,3,2,1]$，那么 $a[2:5]=[8,0,3,2]$。

Charlie 对序列 $[a_i]$ 定义了一个函数 $F(l,r)$，表示序列 $a[l:r]$ 的本质不同的子序列个数。特别地，一个空序列也被当作一个本质不同的子序列。

序列 $a[l:r]$ 的子序列定义为 $[a_{i_1},a_{i_2},a_{i_3},\cdots,a_{i_{k-1}},a_{i_k}]$，其中 $l \le i_1<i_2<i3<\cdots<i_{k-1}<i_k \le r$。比如说，$a=[9,8,0,3,2,1]$，那么 $[8,3,2]$ 是 $a[2:5]=[8,0,3,2]$ 的一个子序列。

长度为 $n$ 的序列 $a$ 和长度为 $m$ 的序列 $b$ 被称作本质不同的，当且仅当 $n\neq m$，或存在 $i$，使得 $a_i \neq b_i$。反之，则称这 $2$ 个序列是本质相同的。比如说，$[9,8]$ 和 $[9,7]$ 是本质不同的，$[9,8]$ 和 $[9,8,7]$ 也是本质不同的，而 $[9,8]$ 和 $[9,8]$ 是本质相同的。

举个例子，设 $a=[1,9,9,8,0,3,2,1]$，那么 $F(1,3)=6$，因为 $a[1:3]=[1,9,9]$ 有 $6$ 个子序列：$[],[1],[9],[1,9],[9,9],[1,9,9]$。

现在 Charlie 想知道，$\sum _{1\le l\le r\le n} F(l,r)$ 的值是多少。由于这个数可能很大，请输出它对 $998244353$（$7\times 17\times 2^23+1$，一个质数）取模后的结果。
## 输入格式

第一行一个整数 $n$，表示序列 $a$ 的长度。

第二行包括 $n$ 个整数，表示 $a_1,a_2,a_3,\cdots a_{n-1},a_n$。
## 输出格式

一行，一个整数表示 $\sum _{1\le l\le r\le n} F(l,r)$ 的值对 $998244353$ 取模后的结果。

## 样例

### 样例输入 #1
```
8

1 9 9 8 0 3 2 1
```
### 样例输出 #1
```
814
```
## 提示

- 对于 $10\%$ 的数据，$1\le n \le 10$；
- 对于 $30\%$ 的数据，$1 \le n \le 100$；
- 对于 $50\%$ 的数据，$1\le n \le 1000$，$0 \le a_i \le 10^5$；
- 对于 $100\%$ 的数据，$1 \le n \le 10^5$，$|a_i| \le 10^9$。

oiinhand 3.0 正在开发中。

这将是 oiers 都需要的工具，它不仅集合了全网所有大型 OJ 的资源（题目、题解）而且针对用户还可以将自己在其他 OJ 评测过的代码储存下来，并且有超贴心的云笔记功能，帮助大家最大效率练习。

soha 借此地征求意见，有奖哦！<http://www.wenjuan.com/s/M7fqIv/>


---

---
title: "[NOI2013] 矩阵游戏"
layout: "post"
diff: 提高+/省选-
pid: P1397
tag: ['递推', '2013', 'NOI', '矩阵乘法', '线性递推']
---
# [NOI2013] 矩阵游戏
## 题目描述

婷婷是个喜欢矩阵的小朋友，有一天她想用电脑生成一个巨大的 $n$ 行 $m$ 列的矩阵（你不用担心她如何存储）。她生成的这个矩阵满足一个神奇的性质：若用 $F[i,j]$ 来表示矩阵中第 $i$ 行第 $j$ 列的元素，则 $F[i,j]$ 满足下面的递推式:

$$\begin{aligned}
F[1, 1] &= 1 \\
F[i, j] &=a\times F[i, j-1]+b, &j\neq 1 \\
F[i, 1] &=c\times F[i-1, m]+d, &i\neq 1 \\
\end{aligned}$$

递推式中 $a,b,c,d$ 都是给定的常数。

现在婷婷想知道 $F[n,m]$ 的值是多少，请你帮助她。由于最终结果可能很大，你只需要输出 $F[n,m]$ 除以 $10^9+7$ 的余数。

## 输入格式

包含一行有六个整数 $n,m,a,b,c,d$。意义如题所述。

## 输出格式

包含一个整数，表示 $F[n,m]$ 除以 $10^9+7$ 的余数。

## 样例

### 样例输入 #1
```
3 4 1 3 2 6

```
### 样例输出 #1
```
85

```
## 提示

【样例1说明】

样例中的矩阵为：

$$\begin{pmatrix}
 1 &  4 &  7 & 10 \\
26 & 29 & 32 & 35 \\
76 & 79 & 82 & 85 \\
\end{pmatrix}$$

### 数据范围

| 测试点编号 | 数据范围 |
| :-: | :-: |
| 1 | $1 \le n,m \le 10$；$1 \le a,b,c,d \le 1000$ |
| 2 | $1 \le n,m \le 100$；$1 \le a,b,c,d \le 1000$ |
| 3 | $1 \le n,m \le 10^3$；$1 \le a,b,c,d \le 10^9$ |
| 4 | $1 \le n,m \le 10^3$；$1 \le a,b,c,d \le 10^9$ |
| 5 | $1 \le n,m \le 10^9$；$1 \le a = c \le 10^9$；$1 \le b = d \le 10^9$ |
| 6 | $1 \le n,m \le 10^9$；$a = c = 1$；$1 \le b,d \le 10^9$ |
| 7 | $1 \le n,m,a,b,c,d \le 10^9$ |
| 8 | $1 \le n,m,a,b,c,d \le 10^9$ |
| 9 | $1 \le n,m,a,b,c,d \le 10^9$ |
| 10 | $1 \le n,m,a,b,c,d \le 10^9$ |
| 11 | $1 \le n,m \le 10^{1\,000}$；$a = c = 1$；$1 \le b,d \le 10^9$ |
| 12 | $1 \le n,m \le 10^{1\,000}$；$1 \le a = c \le 10^9$；$1 \le b = d \le 10^9$ |
| 13 | $1 \le n,m \le 10^{1\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 14 | $1 \le n,m \le 10^{1\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 15 | $1 \le n,m \le 10^{20\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 16 | $1 \le n,m \le 10^{20\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 17 | $1 \le n,m \le 10^{1\,000\,000}$；$a = c = 1$；$1 \le b,d \le 10^9$ |
| 18 | $1 \le n,m \le 10^{1\,000\,000}$；$1 \le a = c \le 10^9$；$1 \le b = d \le 10^9$ |
| 19 | $1 \le n,m \le 10^{1\,000\,000}$；$1 \le a,b,c,d \le 10^9$ |
| 20 | $1 \le n,m \le 10^{1\,000\,000}$；$1 \le a,b,c,d \le 10^9$ |


---

---
title: "[NOI2013] 快餐店"
layout: "post"
diff: 提高+/省选-
pid: P1399
tag: ['递推', '2013', '线段树', 'NOI', '深度优先搜索 DFS', '基环树']
---
# [NOI2013] 快餐店
## 题目描述

小 T 打算在城市 C 开设一家外送快餐店。送餐到某一个地点的时间与外卖店到该地点之间最短路径长度是成正比的，小 T 希望快餐店的地址选在离最远的顾客距离最近的地方。

快餐店的顾客分布在城市 C 的 $N$ 个建筑中，这 $N$ 个建筑通过恰好 $N$ 条双向道路连接起来，不存在任何两条道路连接了相同的两个建筑。任意两个建筑之间至少存在一条由双向道路连接而成的路径。小 T 的快餐店可以开设在任一建筑中，也可以开设在任意一条道路的某个位置上（该位置与道路两端的建筑的距离不一定是整数）。

现给定城市 C 的地图（道路分布及其长度），请找出最佳的快餐店选址，输出其与最远的顾客之间的距离。
## 输入格式

第一行包含一个整数 $N$，表示城市 C 中的建筑和道路数目。

接下来 $N$ 行，每行 $3$ 个整数，$A_i,B_i,L_i$（$1\leq i\leq N$，$L_i>0$），表示一条道路连接了建筑 $A_i$ 与 $B_i$，其长度为 $L_i$。

## 输出格式

输出仅包含一个实数，四舍五入保留**恰好一位小数**，表示最佳快餐店选址距离最远用户的距离。

注意：你的结果必须恰好有一位小数，小数位数不正确不得分。
## 样例

### 样例输入 #1
```
4 
1 2 1 
1 4 2 
1 3 2 
2 4 1

```
### 样例输出 #1
```
2.0 
```
### 样例输入 #2
```
5
1 5 100
2 1 77
3 2 80
4 1 64
5 3 41
```
### 样例输出 #2
```
109.0
```
## 提示

### 样例解释 1

![](https://cdn.luogu.com.cn/upload/image_hosting/r0dmxcgy.png)

### 样例解释 2

![](https://cdn.luogu.com.cn/upload/image_hosting/pf8eaowl.png)

### 数据范围

- 对于 $10\%$ 的数据，$N\leq 80$，$L_i=1$；
- 对于 $30\%$ 的数据，$N\leq 600$，$L_i\leq 100$；
- 对于 $60\%$ 的数据，$N\leq 2000$，$L_i\leq 10^9$；
- 对于 $100\%$ 的数据，$1\leq N\leq 10^5$，$1\leq L_i \leq 10^9$。


---

---
title: "[HAOI2008] 硬币购物"
layout: "post"
diff: 提高+/省选-
pid: P1450
tag: ['动态规划 DP', '数学', '递推', '2008', '河南', '各省省选', '容斥原理']
---
# [HAOI2008] 硬币购物
## 题目描述

共有 $4$ 种硬币。面值分别为 $c_1,c_2,c_3,c_4$。

某人去商店买东西，去了 $n$ 次，对于每次购买，他带了 $d_i$ 枚 $i$ 种硬币，想购买 $s$ 的价值的东西。请问每次有多少种付款方法。
## 输入格式

输入的第一行是五个整数，分别代表 $c_1,c_2,c_3,c_4, n$。

接下来 $n$ 行，每行有五个整数，描述一次购买，分别代表 $d_1, d_2, d_3, d_4,s$。
## 输出格式

对于每次购买，输出一行一个整数代表答案。
## 样例

### 样例输入 #1
```
1 2 5 10 2
3 2 3 1 10
1000 2 2 2 900

```
### 样例输出 #1
```
4
27

```
## 提示

#### 数据规模与约定

* 对于 $100\%$ 的数据，保证 $1 \leq c_i, d_i, s \leq 10^5$，$1 \leq n \leq 1000$。


---

---
title: "刷题比赛"
layout: "post"
diff: 提高+/省选-
pid: P1707
tag: ['递推', '倍增', '矩阵运算', '洛谷原创', '矩阵乘法', '线性递推']
---
# 刷题比赛
## 题目背景

nodgd 是一个喜欢写程序的同学，前不久洛谷 OJ 横空出世，nodgd 同学当然第一时间来到洛谷 OJ 刷题。   
于是发生了一系列有趣的事情，他就打算用这些事情来出题恶心大家……

## 题目描述

洛谷OJ当然算是好地方，nodgd 同学打算和朋友分享一下。于是他就拉上了他的朋友 Ciocio 和 Nicole 两位同学一起刷题。喜欢比赛的他们当然不放过这样一次刷题比赛的机会！

在第 $1$ 天 nodgd,Coicoi,Nicole 都只做了 $1$ 道题。

在第 $2$ 天 nodgd,Coicoi,Nicole 都只做了 $3$ 道题。

他们都有着严格的刷题规则，并且会在每一天都很遵守规则的刷一定量的题。

1、nodgd 同学第 $k+2$ 天刷题数量    
$$a_{k+2}=pa_{k+1}+qa_k+b_{k+1}+c_{k+1}+rk^2+tk+1$$

2、Ciocio 同学第 $k+2$ 天刷题数量      
$$b_{k+2}=ub_{k+1}+vb_k+a_{k+1}+c_{k+1}+w^k$$

3、Nicole 同学第 $k+2$ 天刷题数量    
$$c_{k+2} = xc_{k+1}+yc_k + a_{k+1} + b_{k+1} + z^k+k+2$$

（以上的字母 $p,q,r,t,u,v,w,x,y,z$ 都是给定的常数，并保证是正整数）

于是他们开始了长时间的刷题比赛！一共进行了 $n$ 天

但是时间是可贵的，nodgd 想快速知道第 $n$ 天每个人的刷题数量。  
不过 nodgd 同学还有大量的数学竞赛题、物理竞赛题、英语竞赛题、美术竞赛题、体育竞赛题…… 要做，就拜托你来帮他算算了。

由于结果很大，输出结果 $\bmod \space m$ 的值即可。

## 输入格式

第一行两个正整数 $n,m$。

第二行四个正整数 $p,q,r,t$。

第三行三个正整数 $u,v,w$。

第四行三个正整数 $x,y,z$。

## 输出格式

共三行，每行一个名字 + 一个空格 + 一个整数。  
依次是 nodgd,Ciocio,Nicole 和他们在第 $n$ 天刷题数量 $\bmod \space m$ 的值。

## 样例

### 样例输入 #1
```
4 10007
2 1 1 1
2 2 3
1 1 2
```
### 样例输出 #1
```
nodgd 74
Ciocio 80
Nicole 59
```
## 提示

对于 $100\%$ 的数据，$4\le n \le 10^{16}$，$2\le m \le 10^{16}$，$1\le p,q,r,t,u,v,w,x,y,z \le 100$。


---

---
title: "[NOI2009] 管道取珠"
layout: "post"
diff: 提高+/省选-
pid: P1758
tag: ['字符串', '动态规划 DP', '递推', '2009', 'NOI']
---
# [NOI2009] 管道取珠
## 题目描述

管道取珠是小 X 很喜欢的一款游戏。在本题中，我们将考虑该游戏的一个简单改版。游戏画面如图 1 所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7p4r2ip9.png)

游戏初始时，左侧上下两个管道分别有一定数量的小球（有深色球和浅色球两种类型），而右侧输出管道为空。每一次操作，可以从左侧选择一个管道，并将该管道中最右侧的球推入右边输出管道。

例如：我们首先从下管道中移一个球到输出管道中，将得到图 2 所示的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/xj1kay44.png)

假设上管道中有 $n$ 个球, 下管道中有 $m$ 个球，则整个游戏过程需要进行 $n+m$ 次操作，即将所有左侧管道中的球移入输出管道。最终 $n+m$ 个球在输出管道中从右到左形成输出序列。

爱好数学的小 X 知道，他共有 $\dbinom{n+m}{m}$ 种不同的操作方式，而不同的操作方式可能导致相同的输出序列。举个例子，对于图 3 所示的游戏情形：

![](https://cdn.luogu.com.cn/upload/image_hosting/0m1t5d3h.png)

我们用 A 表示浅色球，B 表示深色球。并设移动上管道右侧球的操作为 U，移动下管道右侧球的操作为 D，则共有 $\binom{2+1}{1}=3$ 种不同的操作方式，分别为 UUD，UDU，DUU；最终在输出管道中形成的输出序列（从右到左）分别为 BAB，BBA，BBA。可以发现后两种操作方式将得到同样的输出序列。

假设最终可能产生的不同种类的输出序列共有 $K$ 种，其中：第 $i$ 种输出序列的产生方式（即不同的操作方式数目）有 $a_i$ 个。聪明的小 X 早已知道，

$$
\sum a_i=\binom{n+m}{m}
$$

因此，小 X 希望计算得到：

$$
\sum a_i^2
$$

你能帮助他计算这个值么？由于这个值可能很大，因此只需要输出该值对 $1024523$ 取模后的结果。

## 输入格式

输入文件中的第一行为两个整数 $n,m$，分别表示上下两个管道中球的数目。

第二行中为一个长度为 $n$ 的字符串，表示上管道中从左到右球的类型。其中：A 表示浅色球，B 表示深色球。

第三行中为一个长度为 $m$ 的字符串，表示下管道中从左到右球的类型。

保证两个字符串都只包含 A,B 两个字母。
## 输出格式

输出一个整数，即为 $\sum a_i^2$ 对 $1024523$ 取模的结果。

## 样例

### 样例输入 #1
```
2 1
AB
B

```
### 样例输出 #1
```
5
```
## 提示

### 样例解释

样例对应图 3。

共有两种不同的输出序列形式，序列 BAB 有 $1$ 种产生方式，而序列 BBA 有 $2$ 种产生方式，因此答案为 $5$。

### 数据范围

- 对于 $30\%$ 的数据，满足 $m,n \leq 12$；
- 对于 $100\%$ 的数据，满足 $1 \leq m,n \leq 500$。


---

---
title: "淘汰赛制"
layout: "post"
diff: 提高+/省选-
pid: P1769
tag: ['动态规划 DP', '递推', '递归', 'NOI 导刊']
---
# 淘汰赛制
## 题目描述

淘汰赛制是一种极其残酷的比赛制度。$2^n$ 名选手分别标号 $1,2,3,\cdots,2^n-1,2^n$，他们将要参加 $n$ 轮的激烈角逐。每一轮中，将所有参加该轮的选手按标号从小到大排序后，第 $1$ 位与第 $2$ 位比赛，第 $3$ 位与第 $4$ 位比赛，第 $5$ 位与第 $6$ 位比赛……只有每场比赛的胜者才有机会参加下一轮的比赛（不会有平局）。这样，每轮将淘汰一半的选手。$n$ 轮过后，只剩下一名选手，该选手即为最终的冠军。

现在已知每位选手分别与其他选手比赛获胜的概率，请你预测一下谁夺冠的概率最大。
## 输入格式

第一行是一个整数 $n(1 \le n \le 10)$，表示总轮数。接下来 $2^n$ 行，每行 $2^n$ 个整数，第 $i$ 行第 $j$ 个是 $p_{i,j}$。（$0 \le p_{i_j} \le 100$，$p_{i,i}=0$，$p_{i,j}+p_{j,i}=100$），表示第 $i$ 号选手与第 $j$ 号选手比赛获胜的概率。
## 输出格式

输出只有一个整数 $c$，表示夺冠概率最大的选手编号（若有多位选手，输出编号最小者）。

## 样例

### 样例输入 #1
```
2
0 90 50 50
10 0 10 10
50 90 0 50
50 90 50 0

```
### 样例输出 #1
```
 1
```
## 提示

- $30\%$ 的数据满足 $n \le 3$；
- $100\%$ 的数据满足 $n \le 10$。

_NOI导刊 2010 提高（01）



---

---
title: "关灯"
layout: "post"
diff: 提高+/省选-
pid: P1805
tag: ['高精度', '递推', 'NOI 导刊', '线性递推']
---
# 关灯
## 题目描述

在某条道路上，有 $n$ 盏灯排成一排，它们有的是开着的，有的是关着的。

由于天马上就要亮了，上级给了你一个任务：把所有的灯都关掉。

只不过，这些灯都比较智能，不会被轻易关掉。它们的开或关遵循如下规则：

- 每一步只能开或关一盏灯。
- 编号为 $1$ 的灯可以随意开或关。
- 如果编号为 $1, 2, \cdots,k-1$ 的灯都关上了了，并且编号为 $k$ 的灯在开着，我们可以随意开或关第 $k+1$ 盏灯。

在关灯之前，请你计算：至少要多少步才能关上所有灯？
## 输入格式

第 $1$ 行一个整数 $n$，表示灯的个数。

第 $2$ 行有 $n$ 个整数，如果第 $i$ 个整数 $O_i=0$，表示第 $i$ 个盏灯初始的时候是关着的；如果 $O_i=1$，表示第 $i$ 盏灯初始的时候是开着的。
## 输出格式

共一行一个整数，表示最少需要多少步才能关上所有灯。

## 样例

### 样例输入 #1
```
4

1 0 1 0
```
### 样例输出 #1
```
6
```
## 提示

【输出解释】

- 初始状态 $1010$；
- 第 $1$ 步 $1110$；
- 第 $2$ 步 $0110$；
- 第 $3$ 步 $0100$；
- 第 $4$ 步 $1100$；
- 第 $5$ 步 $1000$；
- 第 $6$ 步 $0000$。

### 数据范围及约定

- 对于 $40\%$ 的数据，$n \le 30$；
- 对于 $70\%$ 的数据，$n \le 300$；
- 对于 $100\%$ 的数据，$n \le 1000$。


---

---
title: "遥控车"
layout: "post"
diff: 提高+/省选-
pid: P2030
tag: ['字符串', '高精度', '递推', '二分']
---
# 遥控车
## 题目描述

平平带着韵韵来到了游乐园，看到了 $n$ 辆漂亮的遥控车，每辆车上都有一个唯一的名字 name[i]。韵韵早就迫不及待地想玩名字是 $s$ 的遥控车。可是韵韵毕竟还小，她想象的名字可能是一辆车名字的前缀（也就是说能确定一个 $i$，使 $s$ 是 name[i] 的前缀），这时她就能玩第 $i$ 辆车；或者是一个无中生有的名字，即 $s$ 不是任何一辆车名字的前缀，这时候她什么也不能玩。

你需要完成下面的任务：

1. 韵韵想了 $m$ 个她想要的名字，请告诉她能玩多少次。

2. 由于管理员粗心的操作，导致每辆车的摆放位置都可能出现微小的差错，原来第 $i$ 辆车现在的位置可能是 $i-1$ 、 $i$ 、 $i+1$ 中的任意一个（第 $1$ 辆车的位置不可能是 $0$，第 $n$ 辆车的位置不可能是 $n+1$）。请你计算出共有多少种可能的排列。

注：数据保证当 $s$ 是 name[i] 的前缀时，$i$ 是唯一确定的。一辆车可以玩多次。
## 输入格式

第一行是 $2$ 个正整数 $n$ 、 $m$。

接下来 $n$ 行，每行 $1$ 个字符串 name[i]，表示第 $i$ 辆车的名字。接下来 $m$ 行，每行 $1$ 个字符串 $s$，表示韵韵想要的名字。
## 输出格式

第一行输出韵韵能玩的次数。第二行输出共有多少种可能的排列。

## 样例

### 样例输入 #1
```
4 4
Abcd
DeF
AAa
aBccc
Ab
AA
AbC
aBcc
```
### 样例输出 #1
```
3
5

```
## 提示

【注意】

对于题目涉及到的字符串严格区分大小写，且长度小于 $255$。

【数据范围】

对于 $20\%$ 的数据 $n \le 10,m \le 10$；

对于 $40\%$ 的数据 $n \le 1000$，$m \le 1000$；

对于 $100\%$ 的数据 $n \le 10000$，$m \le 10000$。


---

---
title: "[AHOI2009] 中国象棋"
layout: "post"
diff: 提高+/省选-
pid: P2051
tag: ['动态规划 DP', '递推', '2009', '各省省选', '安徽']
---
# [AHOI2009] 中国象棋
## 题目描述

这次小可可想解决的难题和中国象棋有关，在一个 $n$ 行 $m$ 列的棋盘上，让你放若干个炮（可以是 $0$ 个），使得没有一个炮可以攻击到另一个炮，请问有多少种放置方法。大家肯定很清楚，在中国象棋中炮的行走方式是：一个炮攻击到另一个炮，当且仅当它们在同一行或同一列中，且它们之间恰好 有一个棋子。你也来和小可可一起锻炼一下思维吧！

## 输入格式

一行包含两个整数 $n,m$，之间由一个空格隔开。

## 输出格式

总共的方案数，由于该值可能很大，只需给出方案数模 $9999973$ 的结果。

## 样例

### 样例输入 #1
```
1 3
```
### 样例输出 #1
```
7
```
## 提示


**样例说明**

除了 $3$ 个格子里都塞满了炮以外，其它方案都是可行的，所以一共有 $2 \times 2 \times 2-1=7$ 种方案。

**数据规模与约定**

- 对于 $30\%$ 的数据，$n$ 和 $m$ 均不超过 $6$。
- 对于 $50\%$ 的数据，$n$ 和 $m$ 至少有一个数不超过 $8$。
- 对于 $100\%$ 的数据，$1 \leq n,m \leq 100$。

题面修改：@syksykCCC。


---

---
title: "[JLOI2013] 卡牌游戏"
layout: "post"
diff: 提高+/省选-
pid: P2059
tag: ['动态规划 DP', '递推', '2013', '各省省选', '吉林']
---
# [JLOI2013] 卡牌游戏
## 题目描述

$N$ 个人坐成一圈玩游戏。一开始我们把所有玩家按顺时针从 $1$ 到 $N$ 编号。首先第一回合是玩家 $1$ 作为庄家。每个回合庄家都会随机（即按相等的概率）从卡牌堆里选择一张卡片，假设卡片上的数字为 $X$，则庄家首先把卡片上的数字向所有玩家展示，然后按顺时针从庄家位置数第 $X$ 个人将被处决(即退出游戏)。然后卡片将会被放回卡牌堆里并重新洗牌。被处决的人按顺时针的下一个人将会作为下一轮的庄家。那么经过 $N-1$ 轮后最后只会剩下一个人，即为本次游戏的胜者。现在你预先知道了总共有 $M$ 张卡片，也知道每张卡片上的数字。现在你需要确定每个玩家胜出的概率。

这里有一个简单的例子：

例如一共有 $4$ 个玩家，有四张卡片分别写着`3,4,5,6`.

第一回合，庄家是玩家 $1$ ，假设他选择了一张写着数字 $5$ 的卡片。那么按顺时针数 `1,2,3,4,1`，最后玩家 $1$ 被踢出游戏。

第二回合，庄家就是玩家 $1$ 的下一个人，即玩家 $2$.假设玩家 $2$ 这次选择了一张数字 $6$，那么 `2,3,4,2,3,4`，玩家 $4$ 被踢出游戏。

第三回合，玩家 $2$ 再一次成为庄家。如果这一次玩家 $2$ 再次选了 $6$，则玩家 $3$ 被踢出游戏，最后的胜者就是玩家 $2$。
## 输入格式

第一行包括两个整数 $N,M$ 分别表示玩家个数和卡牌总数。

接下来一行包含 $M$ 个整数，分别给出每张卡片上写的数字。
## 输出格式

输出一行包含 $N$ 个百分比形式给出的实数，四舍五入到两位小数。分别给出从玩家 $1$ 到玩家 $N$ 的胜出概率，每个概率之间用空格隔开，最后不要有空格。
## 样例

### 样例输入 #1
```
5 5
2 3 5 7 11

```
### 样例输出 #1
```
22.72% 17.12% 15.36% 25.44% 19.36%

```
### 样例输入 #2
```
4 4
3 4 5 6
```
### 样例输出 #2
```
25.00% 25.00% 25.00% 25.00%
```
## 提示

对于 $30\%$ 的数据，有 $1\le N\le 10$。

对于 $50\%$ 的数据，有 $1\le N\le 30$。

对于 $100\%$ 的数据，有 $1\le N\le 50$, $1\le M\le 50$, $1\le$ 每张卡片上的数字 $\le 50$。


---

---
title: "[HAOI2007] 上升序列"
layout: "post"
diff: 提高+/省选-
pid: P2215
tag: ['动态规划 DP', '贪心', '递推', '2007', '河南', '各省省选']
---
# [HAOI2007] 上升序列
## 题目描述

对于一个给定的 $S=\{a_1,a_2,a_3,…,a_n\}$ , 若有 $P=\{a_{x_1},a_{x_2},a_{x_3},…,a_{x_m}\}$ , 满足 $(x_1<x_2<…<x_m)$  且 $(a_{x_1}<a_{x_2}<…<a_{x_m})$ 。那么就称 $P$ 为 $S$ 的一个上升序列。如果有多个 $P$ 满足条件，那么我们想求字典序最小的那个。

任务：

给出 $S$ 序列，给出若干询问。对于第 $i$ 个询问，求出长度为 $L_i$ 的上升序列，如有多个，求出字典序最小的那个（即首先 $x_1$ 最小，如果不唯一，再看 $x_2$ 最小……），如果不存在长度为 $L_i$ 的上升序列，则打印 `Impossible`。

## 输入格式

第一行一个 $N$，表示序列一共有 $N$ 个元素。

第二行 $N$ 个数，为 $a_1, a_2 , \cdots , a_n$。

第三行一个 $M$，表示询问次数。下面接 $M$ 行每行一个数 $L$，表示要询问长度为 $L$ 的上升序列。

## 输出格式

对于每个询问，如果对应的序列存在，则输出，否则打印 `Impossible`。

## 样例

### 样例输入 #1
```
6
3 4 1 2 3 6
3
6
4
5

```
### 样例输出 #1
```
Impossible
1 2 3 6
Impossible

```
### 样例输入 #2
```
6
6 7 1 2 3 4
1
2

```
### 样例输出 #2
```
6 7
```
## 提示

$N \le 10000$，$M \le 1000$，保证数据随机。



---

---
title: "[SCOI2005] 最大子矩阵"
layout: "post"
diff: 提高+/省选-
pid: P2331
tag: ['动态规划 DP', '递推', '2005', '四川', '各省省选', '前缀和']
---
# [SCOI2005] 最大子矩阵
## 题目描述

这里有一个 $n \times m$ 的矩阵，请你选出其中 $k$ 个子矩阵，使得这个 $k$ 个子矩阵分值之和最大。

注意：选出的 $k$ 个子矩阵不能相互重叠。
## 输入格式

第一行为 $n,m,k$，接下来 $n$ 行描述矩阵每行中的每个元素的分值（每个元素的分值的绝对值不超过 $32767$）。
## 输出格式

只有一行为 $k$ 个子矩阵分值之和最大为多少。
## 样例

### 样例输入 #1
```
3 2 2

1 -3

2 3

-2 3


```
### 样例输出 #1
```
9
```
## 提示

对于 $100 \%$ 的数据，$1 \leq n \leq 100$，$1 \leq m \leq 2$，$1 \leq k \leq 10$。


---

---
title: "[NOI2014] 动物园"
layout: "post"
diff: 提高+/省选-
pid: P2375
tag: ['字符串', '递推', '2014', 'NOI', 'KMP 算法']
---
# [NOI2014] 动物园
## 题目描述

近日，园长发现动物园中好吃懒做的动物越来越多了。例如企鹅，只会卖萌向游客要吃的。为了整治动物园的不良风气，让动物们凭自己的真才实学向游客要吃的，园长决定开设算法班，让动物们学习算法。

某天，园长给动物们讲解 KMP 算法。

园长：“对于一个字符串 $S$，它的长度为 $L$。我们可以在 $O(L)$ 的时间内，求出一个名为 $\mathrm{next}$ 的数组。有谁预习了 $\mathrm{next}$ 数组的含义吗？”

熊猫：“对于字符串 $S$ 的前 $i$ 个字符构成的子串，既是它的后缀又是它的前缀的字符串中（它本身除外），最长的长度记作 $\mathrm{next}[i]$。”

园长：“非常好！那你能举个例子吗？”

熊猫：“例 $S$ 为 $\verb!abcababc!$，则 $\mathrm{next}[5]=2$。因为$S$的前$5$个字符为 $\verb!abcab!$，$\verb!ab!$ 既是它的后缀又是它的前缀，并且找不到一个更长的字符串满足这个性质。同理，还可得出 $\mathrm{next}[1] = \mathrm{next}[2] = \mathrm{next}[3] = 0$，$\mathrm{next}[4] = \mathrm{next}[6] = 1$，$\mathrm{next}[7] = 2$，$\mathrm{next}[8] = 3$。”

园长表扬了认真预习的熊猫同学。随后，他详细讲解了如何在 $O(L)$ 的时间内求出 $\mathrm{next}$ 数组。

下课前，园长提出了一个问题：“KMP 算法只能求出 $\mathrm{next}$ 数组。我现在希望求出一个更强大 $\mathrm{num}$ 数组一一对于字符串 $S$ 的前 $i$ 个字符构成的子串，既是它的后缀同时又是它的前缀，并且该后缀与该前缀不重叠，将这种字符串的数量记作 $\mathrm{num}[i]$。例如 $S$ 为 $\verb!aaaaa!$，则 $\mathrm{num}[4] = 2$。这是因为$S$的前 $4$ 个字符为 $\verb!aaaa!$，其中 $\verb!a!$ 和 $\verb!aa!$ 都满足性质‘既是后缀又是前缀’，同时保证这个后缀与这个前缀不重叠。而 $\verb!aaa!$ 虽然满足性质‘既是后缀又是前缀’，但遗憾的是这个后缀与这个前缀重叠了，所以不能计算在内。同理，$\mathrm{num}[1] = 0,\mathrm{num}[2] = \mathrm{num}[3] = 1,\mathrm{num}[5] = 2$。”

最后，园长给出了奖励条件，第一个做对的同学奖励巧克力一盒。听了这句话，睡了一节课的企鹅立刻就醒过来了！但企鹅并不会做这道题，于是向参观动物园的你寻求帮助。你能否帮助企鹅写一个程序求出$\mathrm{num}$数组呢？

特别地，为了避免大量的输出，你不需要输出 $\mathrm{num}[i]$ 分别是多少，你只需要输出所有 $(\mathrm{num}[i]+1)$ 的乘积，对 $10^9 + 7$ 取模的结果即可。

## 输入格式

第 $1$ 行仅包含一个正整数 $n$，表示测试数据的组数。  
随后 $n$ 行，每行描述一组测试数据。每组测试数据仅含有一个字符串 $S$，$S$ 的定义详见题目描述。数据保证 $S$ 中仅含小写字母。输入文件中不会包含多余的空行，行末不会存在多余的空格。

## 输出格式

包含 $n$ 行，每行描述一组测试数据的答案，答案的顺序应与输入数据的顺序保持一致。对于每组测试数据，仅需要输出一个整数，表示这组测试数据的答案对 $10^9+7$ 取模的结果。输出文件中不应包含多余的空行。

## 样例

### 样例输入 #1
```
3
aaaaa
ab
abcababc
```
### 样例输出 #1
```
36
1
32 
```
## 提示

测试点编号| 约定
-|-  
1| $n \le 5, L \le 50$  
2| $n \le 5, L \le 200$  
3| $n \le 5, L \le 200$  
4| $n \le 5, L \le 10,000$  
5| $n \le 5, L \le 10,000$  
6| $n \le 5, L \le 100,000$  
7| $n \le 5, L \le 200,000$   
8| $n \le 5, L \le 500,000$  
9| $n \le 5, L \le 1,000,000$  
10| $n \le 5, L \le 1,000,000$  



---

---
title: "[HAOI2011] problem a"
layout: "post"
diff: 提高+/省选-
pid: P2519
tag: ['动态规划 DP', '贪心', '递推', '2011', '河南', '各省省选']
---
# [HAOI2011] problem a
## 题目描述

一次考试共有 $n$ 个人参加，可能出现多个人成绩相同的情况。第 $i$ 个人说：“有 $a_i$ 个人成绩比我高，$b_i$ 个人成绩比我低。”

请求出最少有几个人没有说真话。
## 输入格式

输入的第一行是一个整数，代表参加考试的人数 $n$。

第 $2$ 到第 $(n + 1)$ 行，每行两个用空格隔开的整数，第 $(i + 1)$ 行的两个整数分别代表比第 $i$ 个人成绩高的人数 $a_i$ 和比第 $i$ 个人成绩低的人数 $b_i$。
## 输出格式

输出一行一个整数，代表最少有几个人没有说真话。
## 样例

### 样例输入 #1
```
3
2 0
0 2
2 2
```
### 样例输出 #1
```
1
```
## 提示

对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$0 \leq a_i, b_i \leq n$。


---

---
title: "[ZJOI2008] 生日聚会"
layout: "post"
diff: 提高+/省选-
pid: P2592
tag: ['动态规划 DP', '数学', '递推', '2008', '各省省选', '浙江']
---
# [ZJOI2008] 生日聚会
## 题目描述

今天是hidadz小朋友的生日，她邀请了许多朋友来参加她的生日party。 hidadz带着朋友们来到花园中，打算坐成一排玩游戏。为了游戏不至于无聊，就座的方案应满足如下条件：

对于任意连续的一段，男孩与女孩的数目之差不超过k。

很快，小朋友便找到了一种方案坐了下来开始游戏。hidadz的好朋友Susie发现，这样的就座方案其实是很多的，所以大家很快就找到了一种，那么到底有多少种呢？热爱数学的hidadz和她的朋友们开始思考这个问题……

假设参加party的人中共有n个男孩与m个女孩，你是否能解答Susie和hidadz的疑问呢？由于这个数目可能很多，他们只想知道这个数目除以12345678的余数。

## 输入格式

输入文件party.in仅包含一行共3个整数，分别为男孩数目n, 女孩数目m,  常数k。

## 输出格式

输出文件party.out应包含一行，为题中要求的答案。

## 样例

### 样例输入 #1
```
1 2 1
```
### 样例输出 #1
```
1
```
## 提示

对于30%的数据，n , m ≤ 20；

对于100%的数据, n , m ≤ 150，k ≤ 20。

    


---

---
title: "A*B Problem"
layout: "post"
diff: 提高+/省选-
pid: P2841
tag: ['数学', '高精度', '递推', '进制']
---
# A*B Problem
## 题目描述

给出一个数 $A$ ，你需要给出一个最小的数 $B$ ，使得 $A\times B$ 的结果只含有 $0$ 和 $1$ 。
## 输入格式

一个正整数 $A$。
## 输出格式

正整数 $B$ 和 $A\times B$ 的结果，两数之间用一个空格隔开。
## 样例

### 样例输入 #1
```
6
```
### 样例输出 #1
```
185 1110

```
## 提示

样例说明：$6\times 185=1110$。

对于 $30\%$ 的数据，$0<A<20$。

对于 $50\%$ 的数据，$0<A<100$。

对于 $70\%$ 的数据，$0<A<1000$。

对于 $100\%$ 的数据，$0<A<10^4$。



---

---
title: "[USACO07MAR] Cow Traffic S"
layout: "post"
diff: 提高+/省选-
pid: P2883
tag: ['动态规划 DP', '递推', '2007', 'USACO', '深度优先搜索 DFS']
---
# [USACO07MAR] Cow Traffic S
## 题目描述

The bovine population boom down on the farm has caused serious congestion on the cow trails leading to the barn. Farmer John has decided to conduct a study to find the bottlenecks in order to relieve the 'traffic jams' at milking time.

The pasture contains a network of M (1 ≤ M ≤ 50,000) one-way trails, each of which connects exactly two different intersections from the set of N (1 ≤ N ≤ 5,000) intersections conveniently numbered 1..N; the barn is at intersection number N. Each trail connects one intersection point to another intersection point with a higher number. As a result, there are no cycles and, as they say on the farm, all trails lead to the barn. A pair of intersection points might be connected by more than one trail.

During milking time rush hour, the cows start from their respective grazing locations and head to the barn. The grazing locations are exactly those intersection points with no trails connecting into them. Each cow traverses a 'path', which is defined as a sequence of trails from a grazing location to the barn.

Help FJ finding the busiest trail(s) by computing the largest number of possible paths that contain any one trail. The answer is guaranteed to fit in a signed 32-bit integer.

随着牛的数量增加，农场的道路的拥挤现象十分严重，特别是在每天晚上的挤奶时间。为了解决这个问题，FJ决定研究这个问题，以能找到导致拥堵现象的瓶颈所在。


牧场共有M条单向道路，每条道路连接着两个不同的交叉路口，为了方便研究，FJ将这些交叉路口编号为1..N,而牛圈位于交叉路口N。任意一条单向道路的方向一定是是从编号低的路口到编号高的路口，因此农场中不会有环型路径。同时，可能存在某两个交叉路口不止一条单向道路径连接的情况。


在挤奶时间到来的时候，奶牛们开始从各自的放牧地点回到牛圈。放牧地点是指那些没有道路连接进来的路口（入度为0的顶点）。


现在请你帮助fj通过计算从放牧点到达牛圈的路径数目来找到最繁忙的道路，即求出所有可行路径中通过某条道路的最大值（答案保证是不超过32位整数）。

## 输入格式

Line 1: Two space-separated integers: N and M.


Lines 2..M+1: Two space-separated intersection points.

## 输出格式

Line 1: The maximum number of paths passing through any one trail.

## 样例

### 样例输入 #1
```
7 7
1 3
3 4
3 5
4 6
2 3
5 6
6 7
```
### 样例输出 #1
```
4
```
## 提示

Here are the four possible paths that lead to the barn:


1 3 4 6 7


1 3 5 6 7


2 3 4 6 7


2 3 5 6 7



---

---
title: "[USACO07OPEN] Cheapest Palindrome G"
layout: "post"
diff: 提高+/省选-
pid: P2890
tag: ['字符串', '动态规划 DP', '递推', '2007', 'USACO']
---
# [USACO07OPEN] Cheapest Palindrome G
## 题目描述

Keeping track of all the cows can be a tricky task so Farmer John has installed a system to automate it. He has installed on each cow an electronic ID tag that the system will read as the cows pass by a scanner. Each ID tag's contents are currently a single string with length M (1 ≤ M ≤ 2,000) characters drawn from an alphabet of N (1 ≤ N ≤ 26) different symbols (namely, the lower-case roman alphabet).

Cows, being the mischievous creatures they are, sometimes try to spoof the system by walking backwards. While a cow whose ID is "abcba" would read the same no matter which direction the she walks, a cow with the ID "abcb" can potentially register as two different IDs ("abcb" and "bcba").

FJ would like to change the cows's ID tags so they read the same no matter which direction the cow walks by. For example, "abcb" can be changed by adding "a" at the end to form "abcba" so that the ID is palindromic (reads the same forwards and backwards). Some other ways to change the ID to be palindromic are include adding the three letters "bcb" to the begining to yield the ID "bcbabcb" or removing the letter "a" to yield the ID "bcb". One can add or remove characters at any location in the string yielding a string longer or shorter than the original string.

Unfortunately as the ID tags are electronic, each character insertion or deletion has a cost (0 ≤ cost ≤ 10,000) which varies depending on exactly which character value to be added or deleted. Given the content of a cow's ID tag and the cost of inserting or deleting each of the alphabet's characters, find the minimum cost to change the ID tag so it satisfies FJ's requirements. An empty ID tag is considered to satisfy the requirements of reading the same forward and backward. Only letters with associated costs can be added to a string.

## 输入格式

Line 1: Two space-separated integers: N and M


Line 2: This line contains exactly M characters which constitute the initial ID string


Lines 3..N+2: Each line contains three space-separated entities: a character of the input alphabet and two integers which are respectively the cost of adding and deleting that character.

## 输出格式

Line 1: A single line with a single integer that is the minimum cost to change the given name tag.

## 样例

### 样例输入 #1
```
3 4
abcb
a 1000 1100
b 350 700
c 200 800

```
### 样例输出 #1
```
900

```
## 提示

If we insert an "a" on the end to get "abcba", the cost would be 1000. If we delete the "a" on the beginning to get "bcb", the cost would be 1100. If we insert "bcb" at the begining of the string, the cost would be 350 + 200 + 350 = 900, which is the minimum.

## 题目翻译

### 题目描述
给定一个由 $n$ 个不同的小写字母构成的长 $m$ 的字符串 $s$。可以通过**在 $\bm{s}$ 的任意位置**增减字母将 $s$ 改为回文串。增减字母的花费不同，求最小花费。
### 输入格式
第 $1$ 行是两个整数 $n,m$。

第 $2$ 行是字符串 $s$。

接下 $n$ 行，每行一个字符 $c$ 和两个整数 $x,y$，表示添加一个 $c$ 的花费为 $x$，删除一个 $c$ 的花费为 $y$。
### 输出格式
只有 $1$ 行，表示最小花费。
### 数据范围
对于 $100\%$ 的数据，$1\le m\le2\times10^3,1\le n\le 26,0\le x,y\le 10^4$。

$\mathrm{by\ @}$[$\mathrm{Fish\_Know\_Forever}$](/user/663215)



---

---
title: "[USACO08FEB] Making the Grade G"
layout: "post"
diff: 提高+/省选-
pid: P2893
tag: ['动态规划 DP', '递推', '2008', 'USACO', 'O2优化']
---
# [USACO08FEB] Making the Grade G
## 题目描述

A straight dirt road connects two fields on FJ's farm, but it changes elevation more than FJ would like. His cows do not mind climbing up or down a single slope, but they are not fond of an alternating succession of hills and valleys. FJ would like to add and remove dirt from the road so that it becomes one monotonic slope (either sloping up or down).

You are given N integers A1, ... , AN (1 ≤ N ≤ 2,000) describing the elevation (0 ≤ Ai ≤ 1,000,000,000) at each of N equally-spaced positions along the road, starting at the first field and ending at the other. FJ would like to adjust these elevations to a new sequence B1, . ... , BN that is either nonincreasing or nondecreasing. Since it costs the same amount of money to add or remove dirt at any position along the road, the total cost of modifying the road is

|A1 - B1| + |A2 - B2| + ... + |AN - BN |Please compute the minimum cost of grading his road so it becomes a continuous slope. FJ happily informs you that signed 32-bit integers can certainly be used to compute the answer.

农夫约翰想改造一条路，原来的路的每一段海拔是$A_i$，修理后是 $B_i$，花费 $|A_i - B_i|$。我们要求修好的路是单调不升或者单调不降的。求最小花费。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 contains a single integer elevation: Ai

## 输出格式

\* Line 1: A single integer that is the minimum cost for FJ to grade his dirt road so it becomes nonincreasing or nondecreasing in elevation.

## 样例

### 样例输入 #1
```
7
1
3
2
4
5
3
9

```
### 样例输出 #1
```
3

```


---

---
title: "[USACO09MAR] Cleaning Up G"
layout: "post"
diff: 提高+/省选-
pid: P2943
tag: ['动态规划 DP', '递推', '2009', 'USACO', '枚举']
---
# [USACO09MAR] Cleaning Up G
## 题目描述

In the good old days, Farmer John served a boring cuisine comprising but a single type of cow food to his N (1 <= N <= 40000) prize dairy cows. Times change. Today he serves the herd a total of M (1 <= M <= N) different types of food (conveniently numbered 1..M).

The cows are picky. Cow i has a single food preference P\_i (1 <= P\_i <= M) and will eat only that favorite food.

Each day at feeding time FJ converts the barn into a tastefully lit cafeteria. The cows line up outside to enter the cafeteria in order of their previously-mentioned convenient index number.

Unfortunately, with so many types of food, cleaning up afterwards is very time-consuming. If Farmer John is serving K different types of food, it takes him K\*K units of time to clean the barn.

To save time, FJ serves the cows in contiguous groups from the line. After each group, he cleans up the barn and sets out the food for the next group (of course, he only sets out food that cows in the any given group will eat). Determine the minimum amount of total time FJ must spend cleaning the barn. Each group consists of the next contiguous group of cows from the line; each cow belongs to exactly one group; and the barn must be cleaned up after every group, including the last one.


## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..N+1: Line i+1 contains a single integer: P\_i

## 输出格式

\* Line 1: A single integer: the minimum amount of time FJ must spend cleaning the  barn.

## 样例

### 样例输入 #1
```
13 4 
1 
2 
1 
3 
2 
2 
3 
4 
3 
4 
3 
1 
4 

```
### 样例输出 #1
```
11 

```
## 提示

There are four types of food and thirteen cows in line. The first cow prefers type 1, the second type 2, the third type 1, etc.


The first four groups contain one cow each. The fifth group contains two cows who prefer food #2 (requiring one unit of time). The sixth group contains cows preferring foods 3, 4, 3, 4, 3 (and requires four units of time to clean). The last two groups contain one cow each. The total time is 11.

## 题目翻译

很久很久以前，约翰只会做一种食品；而现在约翰能给他的$N$ $(1 \leq N \leq 40000)$头奶牛供应$M$ $(1 \leq M \leq N)$种不同的食品。但奶牛们非常挑剔，$i$号奶牛只吃食品$P_i$ $(1 \leq P_i \leq M) $

每天，奶牛们按一定编号排队进自助餐厅用餐。不幸的是，这么多各类的食品会让清扫工作变得非常不方便。如果约翰在一次用餐中供应了$K$种食品，他之后就需要$K^2$的时间进行清扫。

为了减少清扫的时间，约翰决定把排好队的奶牛划分成若干组。每一组包含一段连续的奶牛。每一次，只让一组奶牛进入餐厅。这样，他可以让清扫所需的总用时变得最小。请计算这个最小用时。

### 样例解释：

如此划分：1\2\1\3\22\34343\1\4```


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
title: "[USACO10JAN] Cow Telephones G"
layout: "post"
diff: 提高+/省选-
pid: P2977
tag: ['贪心', '递推', '2010', 'USACO', '排序']
---
# [USACO10JAN] Cow Telephones G
## 题目描述

The cows have set up a telephone network, which for the purposes of this problem can be considered to be an unrooted tree of unspecified degree with N (1 <= N <= 100,000) vertices conveniently numbered 1..N. Each vertex represents a telephone switchboard, and each edge represents a telephone wire between two switchboards. Edge i is specified by two integers A\_i and B\_i the are the two vertices joined by edge i (1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i).

Some switchboards have only one telephone wire connecting them to another switchboard; these are the leaves of the tree, each of which is a telephone booth located in a cow field.

For two cows to communicate, their conversation passes along the unique shortest path between the two vertices where the cows are located. A switchboard can accomodate only up to K (1 <= K <= 10) simultaneous conversations, and there can be at most one conversation going through a given wire at any one time.

Given that there is a cow at each leaf of the tree, what is the maximum number of pairs of cows that can simultaneously hold

conversations? A cow can, of course, participate in at most one conversation.

```cpp
1   5          C1   C5 
|   |          ||   || 
2---4   -->    |2---4| 
|   |          ||   || 
3   6          C3   C6 
```
Consider this six-node telephone tree with K=1: 

There are four cows, located at vertices 1, 3, 5 and 6. If cow 1 talks to cow 3, and cow 5 talks to cow 6, then they do not exceed the maximum number of conversations per switchboard, so for this example the answer is 2 (for two pairs of cows talking simultaneously). 

奶牛们要建立一个电话网络，它们可以被认为是一个无根树（大概是个图吧。。。），里面N (1 <= N <= 100,000)个结点可以简便的编号为1...N。每一个结点代表一个电话交换机（类似开关），每条边代表一个连接两个电话交换机的电话线。边i是用两个整数A\_i和B\_i表示的，也就是该边连接着A\_i和B\_i两个电话交换机(1 <= A\_i <= N; 1 <= B\_i <= N; A\_i != B\_i).

一些电话交换机只有一根电话线；它们是这棵树的叶子结点，每个叶子结点只有一只牛。当两头牛在通话时，它们的对话沿着唯一的在两头牛所在结点的最短路径。

一个电话交换机只能忙于K(1 <= K <= 10)个同时的对话，而且每个电话线同一时间只能传送一个对话。

给出一个每个叶子结点都有一头牛的树， 问最多有多少对奶牛能在同一时间进行它们的对话？

## 输入格式

\* Line 1: Two space separated integers: N and K

\* Lines 2..N: Line i+1 contains two space-separated integers: A\_i and B\_i

## 输出格式

\* Line 1: The number of pairs of cows that can simultaneously hold conversations

## 样例

### 样例输入 #1
```
6 1 
1 2 
2 3 
2 4 
4 5 
4 6 

```
### 样例输出 #1
```
2 

```


---

---
title: "[HAOI2016] 放棋子"
layout: "post"
diff: 提高+/省选-
pid: P3182
tag: ['高精度', '递推', '2016', '河南']
---
# [HAOI2016] 放棋子
## 题目描述

给你一个 $N\times N$ 的矩阵，每行有一个障碍，数据保证任意两个障碍不在同一行，任意两个障碍不在同一列，要求你在这个矩阵上放 $N$ 枚棋子（障碍的位置不能放棋子），要求你放 $N$ 个棋子也满足每行只有一枚棋子，每列只有一枚棋子的限制，求有多少种方案。

## 输入格式

第一行一个 $N$，接下来一个 $N \times N$ 的矩阵。$N\leq 200$，0 表示没有障碍，1 表示有障碍。

## 输出格式

一个整数，即合法的方案数。

## 样例

### 样例输入 #1
```
2
0 1
1 0
```
### 样例输出 #1
```
1
```


---

---
title: "[HNOI2008] GT考试"
layout: "post"
diff: 提高+/省选-
pid: P3193
tag: ['递推', '2008', '湖南', '矩阵乘法', 'KMP 算法']
---
# [HNOI2008] GT考试
## 题目描述

阿申准备报名参加 GT 考试，准考证号为 $N$ 位数$X_1,X_2…X_n\ (0\le X_i\le 9)$，他不希望准考证号上出现不吉利的数字。
他的不吉利数字$A_1,A_2,\cdots, A_m\ (0\le A_i\le 9)$ 有 $M$ 位，不出现是指 $X_1,X_2\cdots X_n$ 中没有一段恰好等于 $A_1,A_2,\cdots ,A_m$，$A_1$ 和 $X_1$ 可以为 $0$。
## 输入格式

第一行输入 $N,M,K$ 接下来一行输入 $M$ 位的数。
## 输出格式

阿申想知道不出现不吉利数字的号码有多少种，输出模 $K$ 取余的结果。
## 样例

### 样例输入 #1
```
4 3 100
111
```
### 样例输出 #1
```
81
```
## 提示

### 数据范围及约定

对于全部数据，$N\leq10^9$，$M\leq 20$，$K\leq10000$。


---

---
title: "[HNOI2011] 数学作业"
layout: "post"
diff: 提高+/省选-
pid: P3216
tag: ['数学', '递推', '2011', '湖南', '矩阵乘法']
---
# [HNOI2011] 数学作业
## 题目描述

小 C 数学成绩优异，于是老师给小 C 留了一道非常难的数学作业题：

给定正整数 $n,m$，要求计算 $\text{Concatenate}(n) \bmod \ m$  的值，其中 $\text{Concatenate}(n)$ 是将 $1 \sim n$ 所有正整数 顺序连接起来得到的数。

例如，$n = 13$，$\text{Concatenate}(n) = 12345678910111213$。小 C 想了大半天终于意识到这是一道不可能手算出来的题目，于是他只好向你求助，希望你能编写一个程序帮他解决这个问题。


## 输入格式

一行两个正整数 $n,m$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
13 13
```
### 样例输出 #1
```
4
```
## 提示

【数据范围】

对于 $30\%$ 的数据，$1\le n \le 10^6$；  
对于 $100\%$ 的数据，$1\le n \le 10^{18}$，$1\le m \le 10^9$。

- 2023.4.20 添加一组 hack 数据。


---

---
title: "[POI 2005] AUT-The Bus"
layout: "post"
diff: 提高+/省选-
pid: P3431
tag: ['动态规划 DP', '递推', '2005', '树状数组', 'POI（波兰）']
---
# [POI 2005] AUT-The Bus
## 题目描述

The streets of Byte City form a regular, chessboardlike network - they are either north-south or west-east directed. We shall call them NS- and WE-streets. Furthermore, each street crosses the whole city. Every NS-street intersects every WE- one and vice versa. The NS-streets are numbered from $1$ to $n$, starting from the westernmost. The WE-streets are numbered from $1$ to $m$, beginning with the southernmost. Each intersection of the $i$'th NS-street with the $j$'th WE-street is denoted by a pair of numbers $(i,j)$ (for $1\le i\le n$, $1\le j\le m$).

There is a bus line in Byte City, with intersections serving as bus stops. The bus begins its itinerary by the $(1,1)$ intersection, and finishes by the $(n,m)$ intersection. Moreover, the bus may only travel in the eastern and/or northern direction.

There are passengers awaiting the bus by some of the intersections. The bus driver wants to choose his route in a way that allows him to take as many of them as possible. (We shall make an assumption that the interior of the bus is spacious enough to take all of the awaiting passengers, regardless of the route chosen.)TaskWrite a programme which:

reads from the standard input a description of the road network and the number of passengers waiting at each intersection,finds, how many passengers the bus can take at the most,writes the outcome to the standard output.

## 输入格式

The first line of the standard input contains three positive integers $n$, $m$ and $k$ - denoting the number of NS-streets, the number of WE-streets and the number of intersections by which the passengers await the bus, respectively ($1\le n\le 10^9$, $1\le m\le 10^9$, $1\le k\le 10^5$).

The following $k$ lines describe the deployment of passengers awaiting the bus, a single line per intersection. In the $(i+1)$'st line there are three positive integers $x_i$, $y_i$ and $p_i$, separated by single spaces, $1\le x_i\le n$,$1\le y_i\le m$,$1\le p_i\le 10^6$ . A triplet of this form signifies that by the intersection$(x_i,y_i)p_i$ passengers await the bus. Each intersection is described in the input data once at the most. The total number of passengers waiting for the bus does not exceed $1\ 000\ 000\ 000$.

## 输出格式

Your programme should write to the standard output one line containing a single integer - the greatest number of passengers the bus can take.

## 样例

### 样例输入 #1
```
8 7 11
4 3 4
6 2 4
2 3 2
5 6 1
2 5 2
1 5 5
2 1 1
3 1 1
7 7 1
7 4 2
8 6 2
```
### 样例输出 #1
```
11
```
## 题目翻译

Byte City 的街道形成了一个标准的棋盘网络，他们要么是北南走向要么就是西东走向。北南走向的路口从 $1$ 到 $n$ 编号, 西东走向的路从 $1$ 到 $m$ 编号。 每个路口用两个数 $(i,j)$ 表示 $(1 \le i \le n, 1 \le j \le m)$。 Byte City 里有一条公交线, 在某一些路口设置了公交站点。 公交车从 $(1, 1)$ 发车, 在 $(n, m)$ 结束。公交车只能往北或往东走。 现在有一些乘客在某些站点等车。 公交车司机希望在路线中能接到尽量多的乘客。帮他想想怎么才能接到最多的乘客。


---

---
title: "[POI 2012] SZA-Cloakroom"
layout: "post"
diff: 提高+/省选-
pid: P3537
tag: ['动态规划 DP', '递推', '2012', 'POI（波兰）']
---
# [POI 2012] SZA-Cloakroom
## 题目描述

The annual rich citizen's reunion is taking place in Byteotia.

They meet to boast about their incomes, Lebytene's shoes and other luxuries.

Naturally, not all these objects of pride are carried into the banquet - coats,  jackets, umbrellas and such are left in the cloakroom, and picked up upon leave.

Unfortunately for the well off, a gang of Byteotian thieves plans to break into  the cloakroom and steal part of the items stored therein.

At this very moment the gang's leader is examining the plans of the robbery put  forward by other gang members (they are a democratic lot!).

A plan typically looks as follows: the thieves break into the cloakroom at time $m_j$,  take items worth exactly $k_j$ and escape, where the whole heist takes them $s_j$ time.

The gang leader would first of all like to know which of these plans are feasible and which are not.

A plan is feasible if at time $m_j$ it is possible to collect items of total value $k_j$ in such a way  that up to the very $m_j+s_j$ moment no one shows up to retrieve any of the stolen goods  (in such event, they would notify security, and the robbery would fail).

In particular, if at time $m_j$ it is impossible to select items of exact total worth $k_j$,  then the plan is infeasible and consequently rejected.

Knowing the drop off and retrieval times for each item, determine which plans are feasible and which are not.

We assume that an item left in the cloakroom the moment a robbery starts can already be stolen (see the example).

## 输入格式

In the first line of the standard input there is a single integer $n$($1\le n\le 1\ 000$) denoting the number of items that will be left in the cloakroom.

Those items are described in the $n$ lines that follow.

Each of those lines consists of three integers $c_i$, $a_i$, and $b_i$ ($1\le c_i\le 1\ 000$, $1\le a_i<b_i\le 10^9$),  separated by single spaces, that denote respectively: the item's value, the moment it is left in the cloakroom,  and the moment it will be retrieved by the owner.

The next line holds an integer $p$ ($1\le p\le 1\ 000\ 000$),the number of plans the gang came up with. Each is specified in a separate line by three integers,$m_j$,$k_j$ and $s_j$($1\le m_j\le 10^9$,$1\le k_j\le 100\ 000$,$0\le s_j\le 10^9$), separated by single spaces, that denote respectively: the moment the thieves would enter the cloakroom, the value of goods they would like to steal, and the time the robbery would take them.

In test worth 16% of the total points $p\le 10$ holds in addition.

n some other tests, also worth 16% of the points, all the items have the same $a_i$ values.

In yet other tests, worth 24% of the points, all the queries share the same $s_j$ value.

## 输出格式

For each plan put forward by the gang determine if it is feasible, i.e., whether it is possible  to steal items of total worth exactly $k_j$ and escape before anyone asks for their belongings.

If the plan is feasible, your program should print the word TAK (Polish for yes) on the  standard output, otherwise it should print NIE (Polish for no).

## 样例

### 样例输入 #1
```
5
6 2 7
5 4 9
1 2 4
2 5 8
1 3 9
5
2 7 1
2 7 2
3 2 0
5 7 2
4 1 5
```
### 样例输出 #1
```
TAK
NIE
TAK
TAK
NIE
```
## 题目翻译


有 $n$ 件物品，每件物品有三个属性 $a_i, b_i, c_i\ (a_i<b_i)$。注意输入顺序为 $c_i, a_i, b_i$。

再给出 $q$ 个询问，每个询问由非负整数 $m, k, s$ 组成，问是否能够选出某些物品使得：

1. 对于每个选的物品 $i$，满足 $a_i\le m$ 且 $b_i>m+s$。
2. 所有选出物品的 $c_i$ 的和正好是 $k$。

$1\le n\le 1000$，$1\le a_i<b_i\le 10^9$，$1\le c_i\le 1000$。

$1\le q\le 10^6$，$1\le m\le 10^9$，$1\le k\le 10^5$，$0\le s\le 10^9$。


---

---
title: "[APIO2009] 采油区域"
layout: "post"
diff: 提高+/省选-
pid: P3625
tag: ['递推', '2009', 'APIO', '前缀和']
---
# [APIO2009] 采油区域
## 题目描述

Siruseri 政府决定将石油资源丰富的 Navalur 省的土地拍卖给私人承包商以 建立油井。被拍卖的整块土地为一个矩形区域，被划分为 $M \times N$ 个小块。 Siruseri 地质调查局有关于 Navalur 土地石油储量的估测数据。这些数据表示 为 $M \times N$ 个正整数，即对每一小块土地石油储量的估计值。 为了避免出现垄断，政府规定每一个承包商只能承包一个由 $K\times K$ 块相连的土地构成的正方形区域。 AoE 石油联合公司由三个承包商组成，他们想选择三块互不相交的 $K\times K$ 的 区域使得总的收益最大。 例如，假设石油储量的估计值如下：

```
1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 
1 8 8 8 8 8 1 1 1 
1 8 8 8 8 8 1 1 1 
1 8 8 8 8 8 1 1 1 
1 1 1 1 8 8 8 1 1 
1 1 1 1 1 1 8 8 8 
1 1 1 1 1 1 9 9 9 
1 1 1 1 1 1 9 9 9 
```

- 如果 $K = 2$，AoE 公司可以承包的区域的石油储量总和为 $100$；
- 如果 $K = 3$，AoE 公司可以承包的区域的石油储量总和为 $208$。

AoE 公司雇佣你来写一个程序，帮助计算出他们可以承包的区域的石油储量之和的最大值。

## 输入格式

输入第一行包含三个正整数 $M, N, K$，其中 $M$ 和 $N$ 是矩形区域的行数和列数，$K$ 是每一个承包商承包的正方形的大小（边长的块数）。接下来 $M$ 行，每行有 $N$ 个正整数表示这一行每一小块土地的石油储量的估计值。

## 输出格式

输出只包含一个正整数，表示 AoE 公司可以承包的区域的石油储量之和的最大值。

## 样例

### 样例输入 #1
```
9 9 3
1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 
1 8 8 8 8 8 1 1 1 
1 8 8 8 8 8 1 1 1 
1 8 8 8 8 8 1 1 1 
1 1 1 1 8 8 8 1 1 
1 1 1 1 1 1 8 8 8 
1 1 1 1 1 1 9 9 9 
1 1 1 1 1 1 9 9 9 
```
### 样例输出 #1
```
208
```
## 提示

数据保证 $K\le M$ 且 $K\le N$ 并且至少有三个 $K\times K$ 的互不相交的正方形区域。

其中 $30\%$ 的输入数据，$M, N \le 12$。所有的输入数据, $M, N\le 1500$。每一小块土地的石油储量的估计值是非负整数且小于等于 $500$。



---

---
title: "koishi的数学题"
layout: "post"
diff: 提高+/省选-
pid: P3708
tag: ['递推', '洛谷原创', '枚举', '前缀和', '洛谷月赛']
---
# koishi的数学题
## 题目描述

Koishi 在 Flandre 的指导下成为了一名数学大师，她想了一道简单的数学题。

输入一个整数 $n$，设 $\displaystyle f(x) = \sum_{i=1}^n x \bmod i$，你需要输出 $f(1), f(2), \ldots , f(n)$。

按照套路，Koishi 假装自己并不会做这道题，就来求你帮忙辣。
## 输入格式

一个正整数 $n$。

## 输出格式

一行用空格分隔的 $n$ 个整数 $f(1), f(2), \ldots , f(n)$。

## 样例

### 样例输入 #1
```
10

```
### 样例输出 #1
```
9 16 22 25 29 27 29 24 21 13

```
## 提示

对于 $20\%$ 的数据，$n \le 1000$。  
对于 $60\%$ 的数据，$n \le 10^5$。  
对于 $100\%$ 的数据，$1 \le n \le 10^6$。



---

---
title: "[TJOI2009] 排列计数"
layout: "post"
diff: 提高+/省选-
pid: P3867
tag: ['递推', '2009', '各省省选', 'O2优化', '枚举', '天津']
---
# [TJOI2009] 排列计数
## 题目描述

我们知道，1,2,...,N这个N个数的排列共有N!种情况。现在你的任务是，求出在这N!种排列中，任意相邻两数之差不超过K的排列共有多少个。

因为结果可能很大，你只需输出结果对1000000007取模后的值即可。

## 输入格式

输入文件只有一行，包含用空格隔开的两个数：N, K

## 输出格式

输出满足要求的排列个数对1000000007取模后的结果。

## 样例

### 样例输入 #1
```
4 2
```
### 样例输出 #1
```
12
```
## 提示

在30%的数据中，N ≤ 12

在100%的数据中，N ≤ 50，K ≤ 4

每个测试点时限10秒



---

---
title: "[TJOI2010] 天气预报"
layout: "post"
diff: 提高+/省选-
pid: P3873
tag: ['递推', '2010', '各省省选', '线性递推', '构造', '天津']
---
# [TJOI2010] 天气预报
## 题目描述

A 公司的天气预报系统的原理如下：用一个大于等于 $0$，小于等于 $4146$ 的整数来表示这一天的天气情况，在预测未来某一天的天气情况时，要根据此前 $n$ 天的天气情况来预测，如果用 $w_i$ 表示第 $i$ 天的天气情况（$i>n$），那么 $w_i=(a_1\times w_{i-1}+a_2\times w_{i-2}+\cdots+a_{n}\times w_{i-n})\mod4147$，其中 $a_1,a_2,\cdots ,a_n$ 是已知常数。现给出前 $n$ 天的天气情况，问第 $m$ 天的天气预测结果是什么。
## 输入格式

输入数据的第一行是两个正整数 $n$ 和 $m$，第二行有 $n$ 个非负整数，分别为 $w_n,w_{n-1},\cdots,w_1$。第三行又有 $n$ 个非负整数，分别表示 $a_1,a_2,\ldots,a_n$。
## 输出格式

输出一个整数，表示对第 $m$ 天的天气预测结果。
## 样例

### 样例输入 #1
```
2 3
4 5
6 7

```
### 样例输出 #1
```
59
```
## 提示

$1\le n\le 100$，$n<m\le10^7$，$0\le a_i,w_i\le 4146$。

每个测试点时限 1.5 秒


---

---
title: "[GDOI2014] 采集资源"
layout: "post"
diff: 提高+/省选-
pid: P3891
tag: ['动态规划 DP', '递推', '2014', '各省省选', '广东', '背包 DP']
---
# [GDOI2014] 采集资源
## 题目描述

魔兽争霸3中，战略资源的采集通过使用农民、苦工、小精灵以及寺僧来进行。

在魔兽争霸4的开发中，玻璃渣觉得这种模式太过单一，于是他们想添加更多的单位来使采集的模式更加丰富。

在新的模式中，玩家可以建造更多种类的“苦工”，不同的“苦工”的工作效率不同，同时，建造不同的“苦工”所需要的资源也是不一样的。

玻璃渣出品的游戏以追求平衡著称，所以为了测试这种新的模式的平衡性，他们设计了一套检测的方法：在各种族的起始资源相同时，测量达到某一资源数量的时间，如果相同则可以认为设计是平衡的。

他们将数据给你，希望你能测试出设计是否平衡。

## 输入格式

第一行三个数，N, M, T, 表示苦工的种类、开始时拥有的资源数量以及需要达到的资源的数量。

接下来N行，每行2个数A, B, 表示生产这种苦工所需要的资源，以及这个苦工的效率，效率即为单位时间内产生的资源的数量。

## 输出格式

一个数字，表示资源数量达到T时的最少时间。


注意：与魔兽争霸3不同，魔兽争霸4中，生产苦工不需要时间。并且资源的采集并不连续，亦即如果一个苦工的效率为2，他会在时间为1的时候收获2点资源，而并不会在时间为0.5的时候收获1点资源。

## 样例

### 样例输入 #1
```
1 1 8
1 1

```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
2 1 8
1 1
2 8

```
### 样例输出 #2
```
3
```
## 提示

对于30%的数据，N<=10, M, T <= 300

对于100%的数据，N<=100，M, T <= 1000, A, B <= 2^31

数据保证有解。



---

---
title: "[Code+#1] 可做题"
layout: "post"
diff: 提高+/省选-
pid: P4060
tag: ['动态规划 DP', '递推', 'O2优化', '枚举', '前缀和', '位运算', 'Code+']
---
# [Code+#1] 可做题
## 题目描述

qmqmqm希望给sublinekelzrip出一道可做题。于是他想到了这么一道题目：给一个长度为$n$的非负整数序列$a_i$,你需要计算其异或前缀和$b_i$,满足条件$b_1=a_1$,$b_i=b_{i-1}\ xor\ a_i(i \geq 2)$.

但是由于数据生成器出现了问题，他生成的序列$a$的长度特别长，并且由于内存空间不足，一部分$a_i$已经丢失了，只剩余$m$个位置的元素已知。现在qmqmqm找到你，希望你根据剩余的$a_i$,计算出所有可能的$a$序列对应的$b$序列中$\sum_{i=1}^n b_i$的最小值。

## 输入格式

输入第一行两个非负整数$n$,$m$,分别表示原始序列$a$的长度及剩余元素的个数。

之后$m$行，每行$2$个数$i$,$a_i$，表示一个剩余元素的位置和数值。

## 输出格式

输出一个整数表示可能的最小值。

## 样例

### 样例输入 #1
```
5 3
4 0
3 7
5 0
```
### 样例输出 #1
```
7
```
## 提示

### 样例解释

已知的$a$序列为：$X,X,7,0,0$,其中$X$表示这个位置丢失了。一种可能的$a$序列为$0,7,7,0,0$,对应的$b$序列为$0,7,0,0,0$,和最小为$7$。可以证明不存在和更小的情况。

 ![](https://cdn.luogu.com.cn/upload/pic/12823.png) 

注意未知的$a_i$可以超过已知$a_i$的范围。

保证输入中所有的$i$不同，且满足$1 \leq i \leq n$。

来自 CodePlus 2017 11 月赛，清华大学计算机科学与技术系学生算法与竞赛协会 荣誉出品。

Credit：idea/卢政荣 命题/卢政荣 验题/何昊天

Git Repo：https://git.thusaac.org/publish/CodePlus201711

感谢腾讯公司对此次比赛的支持。



---

---
title: "[AHOI2009] 同类分布"
layout: "post"
diff: 提高+/省选-
pid: P4127
tag: ['动态规划 DP', '搜索', '递推', '2009', '各省省选', '安徽', '枚举', '数位 DP']
---
# [AHOI2009] 同类分布
## 题目描述

给出两个数$a,b$，求出$[a,b]$中各位数字之和能整除原数的数的个数。

## 输入格式

一行，两个整数$a$和$b$

## 输出格式

一个整数，表示答案

## 样例

### 样例输入 #1
```
10 19
```
### 样例输出 #1
```
3
```
## 提示

对于所有的数据，$1 ≤ a ≤ b ≤ 10^{18}$



---

---
title: "[BJOI2012] 最多的方案"
layout: "post"
diff: 提高+/省选-
pid: P4133
tag: ['贪心', '递推', '2012', '各省省选', '北京', 'O2优化', '枚举', '斐波那契数列']
---
# [BJOI2012] 最多的方案
## 题目描述

第二关和很出名的斐波那契数列有关，地球上的 OIer 都知道：  
$$F_n = \begin{cases} 1 & (n \le 2) \\ F_{n-1}+F_{n-2} & (n \ge 3) \end{cases}$$ 
每一项都可以称为斐波那契数。  

现在给一个正整数 $n$，它可以写成一些斐波那契数的和的形式。如果我们要求不同的方案中不能有相同的斐波那契数，那么对一个 $n$ 最多可以写出多少种方案呢？

## 输入格式

只有一个整数 $n$。

## 输出格式

一个整数表示方案数。
## 样例

### 样例输入 #1
```
16
```
### 样例输出 #1
```
4
```
## 提示

Hint：16=3+13=3+5+8=1+2+13=1+2+5+8

【数据范围】   
对于 $30\%$ 的数据，$n \le 256$；  
对于 $100\%$ 的数据，$n \le 10^{18}$。



---

---
title: "[SCOI2009] 粉刷匠"
layout: "post"
diff: 提高+/省选-
pid: P4158
tag: ['动态规划 DP', '递推', '2009', '四川', '各省省选', '枚举', '背包 DP']
---
# [SCOI2009] 粉刷匠
## 题目描述

windy 有 $N$ 条木板需要被粉刷。 每条木板被分为 $M$ 个格子。 每个格子要被刷成红色或蓝色。

windy 每次粉刷，只能选择一条木板上一段连续的格子，然后涂上一种颜色。 每个格子最多只能被粉刷一次。

如果 windy 只能粉刷 $T$ 次，他最多能正确粉刷多少格子？

一个格子如果未被粉刷或者被粉刷错颜色，就算错误粉刷。


## 输入格式

第一行包含三个整数，$N,M,T$。

接下来有 $N$ 行，每行一个长度为 $M$ 的字符串，``0`` 表示红色，`1` 表示蓝色。

## 输出格式

包含一个整数，最多能正确粉刷的格子数。

## 样例

### 样例输入 #1
```
3 6 3
111111
000000
001100
```
### 样例输出 #1
```
16
```
## 提示

$30\%$ 的数据，满足 $1 \le N,M \le 10,0 \le T \le 100$ 。

$100\%$ 的数据，满足 $1 \le N,M \le 50,0 \le T \le 2500$ 


---

---
title: "[ZJOI2006] 皇帝的烦恼"
layout: "post"
diff: 提高+/省选-
pid: P4409
tag: ['贪心', '递推', '2006', '各省省选', '浙江', '中国剩余定理 CRT']
---
# [ZJOI2006] 皇帝的烦恼
## 题目描述

经过多年的杀戮，秦皇终于统一了中国。为了抵御外来的侵略，他准备在国土边境安置 $n$ 名将军。不幸的是这 $n$ 名将军羽翼渐丰，开始展露他们的狼子野心了。他们拒绝述职、拒绝接受皇帝的圣旨。

秦皇已经准备好了秘密处决这些无礼的边防大将。

不过为防兵变，他决定先授予这些将军一些勋章，为自己赢得战略时间。将军们听说他们即将被授予勋章都很开心，他们纷纷上书表示感谢。第 $i$ 个将军要求得到 $a_i$ 枚不同颜色的勋章。但是这些将军都很傲气，如果两个相邻的将军拥有颜色相同的勋章他们就会认为皇帝不尊重他们，会立即造反（编号为 $i$ 的将军和编号为 $i+1$ 的将军相邻；因为他们驻扎的边境可以类似看成一个圆形，所以编号 $1$ 和编号 $n$ 的将军也相邻）。

皇帝不得不满足每个将军的要求，但对他们的飞扬跋扈感到很气愤。于是皇帝决定铸造尽量少种类的勋章来满足这些狂妄者的要求。请问他至少要铸造多少种颜色的勋章？
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行每行一个整数 $a_i$，表示第 $i$ 个将军要求得到多少种勋章。
## 输出格式

输出一个整数，即最少需要多少种勋章。
## 样例

### 样例输入 #1
```
4
2
2
1
1
```
### 样例输出 #1
```
4
```
## 提示

$1 \leq n \leq 2 \times 10^4$，$1 \leq a_i  \leq 10^5$。


---

---
title: "收集邮票"
layout: "post"
diff: 提高+/省选-
pid: P4550
tag: ['递推', '期望']
---
# 收集邮票
## 题目描述

有 $n$ 种不同的邮票，皮皮想收集所有种类的邮票。唯一的收集方法是到同学凡凡那里购买，每次只能买一张，并且买到的邮票究竟是 $n$ 种邮票中的哪一种是等概率的，概率均为 $1/n$。但是由于凡凡也很喜欢邮票，所以皮皮购买第 $k$ 次邮票需要支付 $k$ 元钱。

现在皮皮手中没有邮票，皮皮想知道自己得到所有种类的邮票需要花费的钱数目的期望。
## 输入格式

一行，一个数字 $N$（$N \le 10000$）。
## 输出格式

输出要付出多少钱，保留二位小数。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
21.25
```


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
title: "猜数"
layout: "post"
diff: 提高+/省选-
pid: P4862
tag: ['递推', '斐波那契数列', '线性递推']
---
# 猜数
## 题目背景

Iris 和 Beryl 两人在玩一个猜数的游戏。
## 题目描述

游戏是这样进行的：给定一个正整数 $n$，Iris 在 $S=\{1,2,...,n\}$ 中选择一个数 $m$。  

然后，Iris 要如实回答 Beryl 的若干个问题，这些问题的形式是：“$m$ 是集合 $A$ 中的元素吗？”其中 $A\subseteq S$。   
如果Iris回答“是”，则 Beryl 要给 Iris $a$ 元钱；否则，Beryl 要给 Iris $b$ 元钱。（数据保证 $a>b$）

那么，Beryl 至少准备多少钱，就一定能确定 Iris 心中的数字呢？
## 输入格式

第一行：两个正整数 $a$ 和 $b$ 以及数据组数 $t$。   
接下来 $t$ 行，每行一个给定的正整数 $n$，意义如上所述。
## 输出格式

$t$ 行，表示对于每一组数据，Beryl 需要准备的最小钱数。
## 样例

### 样例输入 #1
```
2 1 2
3
6
```
### 样例输出 #1
```
3
5
```
### 样例输入 #2
```
5 3 1
3
```
### 样例输出 #2
```
8
```
## 提示

【样例1的第1组数据解释】 

Beryl先对集合 $\{1\}$ 进行询问，若得到的答案是“是”，则已经确定 Iris 选的数为 $1$，需要 $2$ 元。若得到的答案是“否”，则再对集合 $\{2\}$ 进行询问，显然运气最差要再花 $2$ 元，共 $3$ 元，故答案为 $3$ 元。   

----   

【数据范围】  

| 测试点编号 | $n$ |$t$| $a$,$b$ |
| :----------- | :----------- | :----------- | :----------- |
| 1 | $\leq 20$ | $\leq 10$ | $\leq 20$ |
| 2 | $\leq 20$ | $\leq 10$ | $\leq 20$ |
| 3 | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
| 4 | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
| 5 | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
| 6 | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
|7  | $\leq 2000$ | $\leq 100$ | $\leq 500$ |
| 8 | $\leq 10^{18}$ | $\leq 200$ | $a=2$,$b=1$ |
| 9 | $\leq 10^{18}$ | $\leq 200$ | $a=2$,$b=1$ |
| 10 | $\leq 10^{18}$ | $\leq 200$ | $a=2$,$b=1$ |




---

---
title: "hby与tkw的基情"
layout: "post"
diff: 提高+/省选-
pid: P4881
tag: ['数学', '线性递推', '逆元']
---
# hby与tkw的基情
## 题目背景

> 基情恒久远，一对永流传。

hby 和 tkw 是一对好基友，他们经常在一起做♂游♂戏 (/滑稽)。

## 题目描述

他们喜欢玩字符串游戏，尤其喜欢玩回文串。每次 hby 会给出一个数 $n$，那么 tkw 就需要给出 $Ans=\sum\limits_{i=1}^ni\times s[i]\times[i\bmod 2]$。其中 $s[i]$ 代表长度为 $i$ 的回文串的个数（只考虑小写字母），最后面是 bool 表达式

不过由于 tkw 最近学 ycz 找妹纸去了，于是他就将这个问题交给了你，如果你不能在 $1\rm s$ 内答出来，那么 hby 和 tkw 的基情将会破裂！~~（不过那样 tkw 就可以安心地找妹纸了）~~

由于答案会非常大，所以你只需要输出答案 $\bmod 10^9+7$ 的值即可
## 输入格式

第一行一个整数 $T$。

接下来 $T$ 行，每行一个数 $n$。
## 输出格式

共 $T$ 行，每行代表一个答案。
## 样例

### 样例输入 #1
```
2
1
3
```
### 样例输出 #1
```
26
2054
```
## 提示

对于 $10\%$的数据，$n\le 5$。

对于另外 $20\%$ 的数据，$\sum n\le 10^7$。

对于另外 $20\%$ 的数据，$T=1$。

对于 $100\%$ 的数据，$1\le T\le 5\times 10^5$，$1\le n\le 10^9$。


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
title: "咕咕咕"
layout: "post"
diff: 提高+/省选-
pid: P4996
tag: ['递推', '进制', '洛谷月赛', '状压 DP']
---
# 咕咕咕
## 题目描述

小 F 是一个能鸽善鹉的同学，他经常把事情拖到最后一天才去做，导致他的某些日子总是非常匆忙。

比如，时间回溯到了 2018 年 11 月 3 日。小 F 望着自己的任务清单：

1. 看 iG 夺冠；
2. 补月赛题的锅。

小 F 虽然经常咕咕咕，但他完成任务也是很厉害的，他一次性可以完成剩余任务的任一**非空子集**。比如，他现在可以选择以下几种中的一种：

1. 看 iG 夺冠；
2. 补月赛题的锅；
3. 一边看 iG 夺冠的直播，一边补锅。

当然，比赛实在是太精彩了，所以小 F 就去看比赛了。

不过，当金雨从天而降、IG 举起奖杯之时，小 F 突然心生愧疚——锅还没补呢！于是，小 F 的内心产生了一点歉意。

这时小 F 注意到，自己总是在某些情况下会产生歉意。每当他要检查自己的任务表来决定下一项任务的时候，如果当前他干了某些事情，但是没干另一些事情，那么他就会产生一定量的歉意——比如，无论他今天看没看比赛，只要没有补完月赛的锅，他都会在选择任务的时候产生 $1$ 点歉意。小 F 完成所有任务后，他这一天的歉意值等于他每次选择任务时的歉意之和。

过高的歉意值让小 F 感到不安。现在，小 F 告诉你他还有 $n$ 项任务，并告诉你在 $m$ 种情况中的一种 $\mathrm{state}_i$ 的情况下，小 F 会产生 $a_i$ 点歉意。请你帮忙计算一下，小 F 在那一天所有可能的完成所有任务方式的歉意值之和是多少。

由于答案可能很大，你只需要输出答案对 $998244353$ 取模即可。
## 输入格式

输入一行两个整数 $n, m$，表示有 $n$ 项任务，在 $m$ 种情况中下小 F 会产生歉意值。

输入接下来 $m$ 行，每行有一个长度为 $n$ 的 $0-1$ 串 $\mathrm{state}_i$ 和一个歉意值 $a_i$，$\mathrm{state}_{i, j}$ 为 $0/1$  表示第 $j$ 项任务此时没做 / 已经做了。

详情请参考样例和样例解释。
## 输出格式

输出一行一个整数，表示小 F 在那一天所有可能的完成任务方式的歉意值之和对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
2 2
00 1
10 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3 4
000 16
001 9
110 4
111 1
```
### 样例输出 #2
```
260
```
## 提示

#### 样例 1 解释：

$0-1$ 串中第一个数字表示小 F 看没看比赛，第二个数字表示小 F 补没补锅。

我们用 $\varnothing$ 表示小 F 什么都没干，$A$ 表示小 F 看了比赛，$B$ 表示小 F 补了锅，那么所有会产生愧疚的方式如下：

$\varnothing: 1$  
$\{A\}:1$

那么所有可能的选择如下：

$\varnothing\rightarrow\{A\}\rightarrow\{A,B\}:2$  
$\varnothing\rightarrow\{B\}\rightarrow\{A,B\}:1$  
$\varnothing\rightarrow\{A,B\}:1$

所以答案是 $2 + 1 + 1 = 4$。

#### 数据范围

保证出现的 $\mathrm{state}_i$ 互不相同。

对于所有数据，有 $1 \leq n \leq 20$, $1 \leq m \leq \min(2 ^ n, 10 ^ 5), 1 \leq a_i \leq 10 ^ 5$。

| Case | $n$ |
| :------:|:------: |
|1|$1$|
|2|$2$|
|3|$3$|
|4|$10$|
|5|$12$|
|6|$14$|
|7|$16$|
|8|$18$|
|9|$19$|
|10|$20$|



---

---
title: "长脖子鹿放置"
layout: "post"
diff: 提高+/省选-
pid: P5030
tag: ['数学', '递推', '枚举', '二分图']
---
# 长脖子鹿放置
## 题目背景

众周所知，在西洋棋中，我们有城堡、骑士、皇后、主教和长脖子鹿。
## 题目描述

如图所示，西洋棋的“长脖子鹿”，类似于中国象棋的马，但按照“目”字攻击，且没有中国象棋“别马腿”的规则。（因为长脖子鹿没有马腿）

![avatar](https://cdn.luogu.com.cn/upload/pic/37260.png)

给定一个$N * M$,的棋盘，有一些格子禁止放棋子。问棋盘上最多能放多少个不能互相攻击的长脖子鹿。

## 输入格式

输入的第一行为两个正整数$N$，$M$，$K$。其中$K$表示禁止放置长脖子鹿的格子数。

第$2$~第$K+1$行每一行为两个整数$X_i, Y_i$,表示禁止放置的格子。

不保证禁止放置的格子互不相同。

## 输出格式

一行一个正整数，表示最多能放置的长脖子鹿个数。
## 样例

### 样例输入 #1
```
2 2 1
1 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
/*额外提供一组数据*/
8 7 5
1 1
5 4
2 3
4 7
8 3
```
### 样例输出 #2
```
28
```
## 提示

**重要提示：请务必思考对图的遍历顺序对运行速度的影响**

对于$10$%的数据，  $1 ≤ N,M ≤ 5$

对于$30$%的数据，  $1 ≤ N,M ≤ 10$

对于$60$%的数据，  $1 ≤ N,M ≤ 50$

对于$80$%的数据，  $1 ≤ N,M ≤ 100$

对于$100$%的数据，$1 ≤ N,M ≤ 200$

数据已修正，有一些错误的算法（包括部分题解）将不能通过本题。

感谢@Alpha 指出问题


---

---
title: "随机数生成器"
layout: "post"
diff: 提高+/省选-
pid: P5147
tag: ['数学', '递推']
---
# 随机数生成器
## 题目描述

HKE最近编写了一个函数 $\text{rand}(l,r)$，其中 $l,r$ 为正整数且 $l \le r$。这个函数会等概率返回区间 $[l,r]$ 中任意一个正整数。然后，他又编写了一个函数：

```cpp
int work(int x){
    if(x==1) return 0;
    else return work(rand(1,x))+1;
}
```
这段代码用pascal写起来就是：
```pascal
function work(x:integer):integer;
begin
    if x=1 then exit(0);
    else exit(work(rand(1,x))+1);
end;
```
现在给定一个正整数 $n$，请问 $\text{work}(n)$ 的返回值的期望值是多少？

期望的定义：假设 $\text{work}(n)$ 返回的所有可能的值为 $x_1,x_2,\dots ,x_k$，它们出现的概率分别为 $p_1,p_2,\dots,p_k$，则期望为：

$$\mathbb{E}=\sum_{i=1}^{k}x_i p_i$$

## 输入格式

一个正整数 $n$

## 输出格式

一个实数，表示 $\text{work}(n)$ 的期望值。保留 $5$ 位小数。

## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
2.00000
```
### 样例输入 #2
```
3
```
### 样例输出 #2
```
2.50000
```
### 样例输入 #3
```
100000
```
### 样例输出 #3
```
13.09014
```
## 提示

【样例 $1$ 解释】  
$\text{work}(2)$ 有 $1/2$ 的概率返回 $1$，有 $1/4$ 的概率返回 $2$，有 $1/8$ 的概率返回 $3$ ……  
则期望为 $1/2+2/4+3/8+ \dots =2$

【数据范围】  
对于 $30\%$ 的数据，$n \le 9$；  
对于 $50\%$ 的数据，$n \le 1000$；  
对于 $70\%$ 的数据，$n \le 1000000$；  
对于 $100\%$ 的数据，$1\le n < 2^{31}$。



---

---
title: "「ACOI2020」学园祭"
layout: "post"
diff: 提高+/省选-
pid: P6042
tag: ['数学', '递推', '2020', '前缀和', '差分']
---
# 「ACOI2020」学园祭
## 题目背景

![T4](https://s2.ax1x.com/2020/01/12/lopWDS.md.png)

秋天，是学习之秋，食欲之秋，更是，学园祭之秋！随着时间流逝，学园祭也越来越近。终于等到这一天，可是没想到在冲绳岛上邂逅到女装的渚同学的勇次竟然来了！中村 莉櫻（Nakamura Rio）见到这个情况，忙给渚同学换上女装。没办法，勇次已经来了，于是渚同学鼓起勇气迈出了第一步。（为什么自顾自地加提示框啊喂！）
## 题目描述

莉櫻为了利用这个人傻钱多的少爷，尽全力提高消费额，努力地暗示渚同学。没办法，于是渚同学想了一下，提出了一个问题：

给出一个 $n$，定义：
$$
\Gamma(0)=1,\Gamma(n)={n!}
$$

$$
A_i^j=\frac{\Gamma(i)}{\Gamma(j)}
$$
求
$$
\sum_{i=1}^n \sum_{j=1}^i \sum_{k=1}^j \gcd(A_{i-j}^j \times \Gamma(j),A_{j-k}^k \times \Gamma(k)) 
$$

渚同学念着莉櫻举起的对话板上写的字：如果不能在规定时间回答出问题的话，就要把菜单全部买一遍哦！

尽管勇次钱多，但是他并不想吃得太多，因为这个问题有 $T$ 个小问题！

**由于答案可能太大，请将答案对 $10086001$ 取模。**
## 输入格式

**本题有多组数据**。

第一行一个整数 $T$，表示数据组数。

对于每组数据：

只有一行一个整数 $n$。
## 输出格式

对于每组数据，一行一个整数，表示问题的答案对 $10086001$ 取模后的值。
## 样例

### 样例输入 #1
```
5
1
2
3
4
5

```
### 样例输出 #1
```
1
4
10
20
36

```
## 提示

#### 数据范围
**本题采用捆绑测试**。

- Subtask 1（20 points）：$T \leq 10^3$，$n \leq 10^2$。   
- Subtask 2（30 points）：$T \leq 10^6$，$n \leq 5 \times 10^3$。  
- Subtask 3（50 points）：$T \leq 10^6$，$n \leq 10^6$。   

对于 $100\%$ 的数据，$1 \leq T,n \leq 10^6$。


---

---
title: "[CCC 2019] Triangle: The Data Structure"
layout: "post"
diff: 提高+/省选-
pid: P6648
tag: ['动态规划 DP', '递推', '2019', '倍增', 'CCC（加拿大）', 'ST 表']
---
# [CCC 2019] Triangle: The Data Structure
## 题目背景

在 Shuchong 的平行宇宙里，计算机学中的最重要的数据结构就是三角形。   
注：因为原数据包太大，故这题缩减了一些数据，具体缩减的数据点如下：

- Subtask 1：1 ~ 10
- Subtask 2：1 ~ 10

所以此题拥有的测试点为：

- Subtask 1：11 ~ 26
- Subtask 2：11 ~ 24

若想测试本题没有的测试点请到 [此处](https://www.luogu.com.cn/problem/U120704) 测试。
## 题目描述

大小为 $m$ 的一个三角形由 $m$ 行组成，第 $i$ 行包含 $i$ 个元素。   
并且，这些行必须排为等边三角形的形状。  
比如说，以下是一个 $m=4$ 的三角形。   
![](https://cdn.luogu.com.cn/upload/image_hosting/fdut4hrs.png)    
每个三角形还包含子三角形。   
比如说上面这个三角形，包含：
- $10$ 个大小为 $1$ 的三角形。
- $6$ 个大小为 $2$ 的三角形。
- $3$ 个大小为 $3$ 的三角形。

注意，每个三角形都是自身的子三角形。   
现在给定一个大小为 $n$ 的三角形，求对于每个大小为 $k$ 的子三角形，子三角形内几个数的最大值的和。
## 输入格式

第一行两个整数 $n,k$ 代表三角形的大小和要求的子三角形的大小。   
接下来 $n$ 行第 $i$ 行有 $i$ 个整数代表这个三角形。
## 输出格式

一行一个整数代表对于每个大小为 $k$ 的子三角形，子三角形内几个数的最大值的和。
## 样例

### 样例输入 #1
```
4 2
3
1 2
4 2 1
6 1 4 2
```
### 样例输出 #1
```
23
```
## 提示

#### 数据规模与约定

- Subtask 1（25 pts）：$n \le 1000$。
- Subtask 2（75 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le k \le n \le 3000$，$0 \le $ 三角形内每个数 $\le 10^9$。

#### 说明

**翻译自 [CCC 2019](https://cemc.math.uwaterloo.ca/contests/computing/2019/index.html) Senior T5 [Triangle: The Data Structure](https://cemc.math.uwaterloo.ca/contests/computing/2019/stage%201/seniorEF.pdf)。**   
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。


---

---
title: "「EZEC-4.5」子序列"
layout: "post"
diff: 提高+/省选-
pid: P6856
tag: ['递推', '线段树', '分块']
---
# 「EZEC-4.5」子序列
## 题目背景

作为唯一一道有背景的题，此题由出题人基于 @[Ecrade_](https://www.luogu.com.cn/user/322075) 的原创题“子集”拓展而来。

“子集”便是本题中 $k=n-1$ 的情况。
## 题目描述

给定一个有 $n$ 个元素的序列 $a$。

定义一个有 $x$ 个元素的序列 $s$ 的值为：
$$\sum \limits _{i=1} ^ x s_i \times \prod \limits _{i=1} ^ x s_i $$

将序列 $a$ 的一个有 $x$ 个元素的子序列表示为 $s = \{a_{p_1},a_{p_2},...,a_{p_x}\}$，其中 $p$ 为严格单调递增的序列，$1 \le p_1 \le p_x \le n$ 。

给定整数 $k$，定义序列 $a$ 的一个有 $x$ 个元素的合法的子序列 $s$ 需满足 $p_x - p_1 \le k$。

求序列 $a$ 的所有合法子序列的值之和对 $mod$ 取模的值。 
## 输入格式

第一行三个整数，$n,k,mod$ 。 

第二行 $n$ 个整数，$a_i$。 
## 输出格式

一行一个整数表示答案对 $mod$ 取模的值。 
## 样例

### 样例输入 #1
```
4 1 1000000007
1 2 3 4
```
### 样例输出 #1
```
150
```
### 样例输入 #2
```
3 2 114
2 3 4
```
### 样例输出 #2
```
65
```
### 样例输入 #3
```
12 8 10042020
1 1 4 5 1 4 1 9 1 9 8 10
```
### 样例输出 #3
```
2797740
```
## 提示

[大样例](https://www.luogu.com.cn/paste/5sg4ahwn)

### 【样例解释】：

样例1：

- 所有合法的子序列为 $\{1\}，\{2\}，\{3\}，\{4\}，\{1,2\}，\{2,3\}，\{3,4\}$ 

- 答案为 $1 \times 1 + 2 \times 2 + 3 \times 3 + 4 \times 4 + (1+2) \times 1 \times 2 + (2+3) \times 2 \times 3 + (3+4) \times 3 \times 4 = 150$


样例2：

- 所有合法的子序列为 $\{2\},\{3\},\{4\},\{2,3\},\{3,4\},\{2,4\},\{2,3,4\}$， 答案为 $ 407 \mod 114 = 65 $。  



### 【数据范围】：

| 数据点编号 | $ n\le$ | 特殊性质 |
| :----------: | :----------: | :----------: |
|$1\sim 4$ |$20$  |无 |
|$5\sim 11$ |$10^3$  |无|
|$12$ |$10^6$  |$k=0$  |
|$13\sim 14$ |$10^5$  |$a_i=1$|
|$15\sim 17$ |$10^5$  |$mod=10^9+7$|
|$18\sim 22$ |$10^5$  |无|
|$23\sim 25$ |$10^6$  |无 |

- 对于 $100\%$ 的数据，$0 \le k < n \le 10^6 , 1 \le a_i \le 10^9 , 1 \le mod \le 10^9+7$ 


---

---
title: "异位坍缩"
layout: "post"
diff: 提高+/省选-
pid: P7495
tag: ['递推', '2021', '矩阵运算', '概率论', '矩阵乘法']
---
# 异位坍缩
## 题目背景

>自然的法则隐藏在黑暗之中。

月光之下，菲欧娜和一群与她有着同样信仰的信徒们聚集在一起，等待着他们所信仰的神明降临。

「神明大人，我们愿意永远追随您。」
## 题目描述

神明想要测试他的信徒们是否忠诚，他决定用运气来进行测试。

神明事先准备了 $n$ 个问题，每个问题都有两种选择：**「相对激进的」** 和 **「相对保守的」**。神明已经定好了自己的选择。

为了考验他的信徒们，神明会在所有可行的问题选择方式中**等概率选出一种**（可行的选择方式指选出**连续的** $k$ 个问题，满足 $l\leq k\leq r$，其中 $l,r$ 给定），然后信徒们会依次对这 $k$ 个问题中的每个问题回答「相对激进的」或「相对保守的」。神明会根据自己的选择以及某个信徒的回答来判定这名信徒是否忠诚。

神明的判定方式是这样的：

+ 这是第一个问题：无论回答如何，神明都愿意相信这名信徒是忠诚的。
+ 这不是第一个问题：如果这名信徒的上一个回答与神明的选择相同，那么神明会需要他去对更先进的选择进行探索，因此这名信徒在这个问题的回答**不能比神明的选择更保守**；否则，神明会要求这名信徒服从于自己，在这个问题的回答**不能比神明的选择更激进**。

如果这名信徒的回答满足上述要求，那么这名信徒就是忠诚的。

现在，神明想要知道，如果信徒对每个问题都会**等概率回答「相对激进的」或「相对保守的」**，那么一名信徒有多大的概率会是忠诚的。他通过菲欧娜向你提出了这个问题，并要求你将结果对 $998244353$ 取模。如果你无法及时回答出，那么你就会失去神明的信任。

------------

#### 简要题意：

给定一个长度为 $n$ 的 01 串 $a$ 以及 $l,r(l\leq r)$。

对于两个长度均为 $k$ 的 01 串 $p,q$，我们认为 $q$ 对于 $p$ 是「忠诚的」，当且仅当 $p$ 和 $q$ 满足如下要求：

+ 对于任意 $1<i\leq k$，如果 $q_{i-1}=p_{i-1}$，那么 $q_i\geq p_i$，否则 $q_i\leq p_i$。

你需要求出如果**先等概率随机选出一个长度 $k$ 满足 $l\leq k\leq r$ 的 $a$ 的子串**，然后**再等概率随机出一个长度为 $k$ 的 01 串 $b$**，有多大的概率使得 $b$ 对于这个子串是「忠诚的」，结果对 $998244353$ 取模。
## 输入格式

第一行三个整数 $n,l,r$，意义如上。

第二行有一个长度为 $n$ 的字符串，表示 $a$。保证字符串只含字符 `0` 和 `1`。
## 输出格式

一行一个整数，表示结果。
## 样例

### 样例输入 #1
```
5 2 3
01101

```
### 样例输出 #1
```
338690049
```
### 样例输入 #2
```
17 4 13
10101110100101101

```
### 样例输出 #2
```
512357021
```
## 提示

#### 样例一解释：

我们用 $\left[l,r\right]$ 表示所选择的子串所在区间。

+ 选择 $\left[1,2\right]$，子串为 `01`，长度为 $2$，有 $3$ 个 01 串对这个子串是「忠诚的」，概率为 $\dfrac{3}{4}$。
+ 选择 $\left[1,3\right]$，子串为 `011`，长度为 $3$，有 $4$ 个 01 串对这个子串是「忠诚的」，概率为 $\dfrac{1}{2}$。
+ 选择 $\left[2,3\right]$，概率为 $\dfrac{3}{4}$。

+ 选择 $\left[2,4\right]$，概率为 $\dfrac{5}{8}$。
+ 选择 $\left[3,4\right]$，概率为 $\dfrac{3}{4}$。
+ 选择 $\left[3,5\right]$，概率为 $\dfrac{1}{2}$。
+ 选择 $\left[4,5\right]$，概率为 $\dfrac{3}{4}$。

结果为 $\dfrac{\dfrac{3}{4}+\dfrac{1}{2}+\dfrac{3}{4}+\dfrac{5}{8}+\dfrac{3}{4}+\dfrac{1}{2}+\dfrac{3}{4}}{7}=\dfrac{37}{56}$，取模意义下为 $338690049$。

------------

**本题采用捆绑测试**

+ Subtask 1 ( $1\%$ )：$n=1$。
+ Subtask 2 ( $13\%$ )：$n\leq100$。
+ Subtask 3 ( $3\%$ )：保证 $\forall1\leq i\leq n,a_i=0$。
+ Subtask 4 ( $3\%$ )：保证 $\forall1\leq i\leq n,a_i=1$。
+ Subtask 5 ( $20\%$ )：$n\leq10^3$。
+ Subtask 6 ( $15\%$ )：$l=r$。
+ Subtask 7 ( $20\%$ )：$n\leq 5\times 10^5$。
+ Subtask 8 ( $25\%$ )：无特殊限制。

对于所有数据，$1\leq n\leq5\times 10^6,1\leq l\leq r\leq n$。


---

---
title: "「Wdsr-2.7」天才⑨与数学递推式"
layout: "post"
diff: 提高+/省选-
pid: P7705
tag: ['递推', 'O2优化', '差分']
---
# 「Wdsr-2.7」天才⑨与数学递推式
## 题目描述

生活在雾之湖的冰精琪露诺，向来以智慧而著称。作为寺子屋的老学员，琪露诺可是对数学递推式了如指掌。

有一天，慧音老师想要考一考琪露诺。于是她写出了一个长度为 $m$ 的递推公式：

$$F_t=\sum_{i=1}^m K_i\times F_{t-i} \quad (t> m)$$

其中 $m,\{K_i\}$ 都是被给定的。不过，由于这个序列 $\{F_i\}$ 的初始 $m$ 项并没有被确定，所以可能存在无穷个满足这个递推式，但是初始 $m$ 项并不一致的递推数列。慧音打算选择其中 $q$ 个 $F$ ，来考考琪露诺对数列知识的掌握。

具体而言，慧音会依次告诉琪露诺，若干个 $\{F_i\}$ 的起始 $m$ 项。显然，这样就能生成无穷序列 $\{F_i\}$ 了。尽管如此，生成这么多序列并不好玩。于是慧音又创造了一个答案序列 $\{A_i\}$ ，满足初始时 $A_i=0$ 。

每当给出一个新的 $\{F_i\}$ ，慧音都要琪露诺使 $\{A_i\}$ 的第 $a,a+1,\cdots b-1,b$ 项分别加上 $F_1,F_2,F_3,\cdots,F_{b-a+1}$ 。

当然，慧音老师不想为难琪露诺，于是对于所有数字，只要输出其对 $p$ 取模的值即可。其中 $p$ 是一个被给定的常数。

---

形式化地讲述题面：给定 $n,q,m,p,\{K_1,K_2,\cdots ,K_m\}$ 。有 $q$ 次操作，每次给定一组 $a,b,\{G_1,G_2\cdots G_m\}$ ，求出无穷序列 $\{F_i\}$ ：

$$F_t=\begin{cases}
G_t & t\le m \cr
\sum_{i=1}^m K_iF_{t-i} & t>m
\end{cases}$$

然后令 $\forall i\in [a,b] ,A_i\gets A_i+F_{i-a+1}$ 。最后分别输出 $\{A_i\}$ 的前 $n$ 项对 $p$ 取模后的结果。
## 输入格式

- 第一行有四个正整数 $n,q,m,p$ ，含义如题面所示。

- 第二行有 $m$ 个整数 $\{K_1,K_2,\cdots ,K_m\}$ ，表示递推式中的系数。

- 接下来 $q$ 行，每行 $2+m$ 个整数 $a,b,\{G_1,G_2,\cdots G_m\}$ ，描述一次操作。
## 输出格式

- 共一行， $n$ 个整数，输出 $A_i \bmod p$ 的值。
## 样例

### 样例输入 #1
```
5 3 2 114514
1 1
1 3 1 1
2 5 1 1
1 5 2 0
```
### 样例输出 #1
```
3 2 5 4 7
```
### 样例输入 #2
```
20 5 4 1919810
2 5 4 3
1 20 1 1 1 1
5 12 7 6 1 2
2 18 9 0 0 1
9 11 5 4 4 1
10 14 1 0 0 0
```
### 样例输出 #2
```
1 10 1 1 22 75 221 850 3176 11706 43324 160379 586060 249707 351705 931555 619201 372869 1800119 1750063

```
## 提示

#### 样例解释

对于样例 $1$ ：

- 初始时， $\{A_i\}=\{0,0,0,0,0\}$ 。

- 第一步生成了一个 $\{F_i\}=\{1,1,2,3,5\}$ ，加至 $A_1,A_2,A_3$ ，此时 $\{A_i\}=\{1,1,2,0,0\}$ 。

- 第二步生成了一个 $\{F_i\}=\{1,1,2,3,5\}$ ，加至 $A_2,A_3,\cdots ,A_5$ ，此时 $\{A_i\}=\{1,2,3,2,3\}$ 。

- 第三步生成了一个 $\{F_i\}=\{2,0,2,2,4\}$ ，加至 $A_1,A_2,\cdots ,A_5$ ，此时 $\{A_i\}=\{3,2,5,4,7\}$ 。

对于样例 $2$ ，我们既没有一个绝妙的解释，又没有足够大的空间，于是我们写不下了。

#### 数据范围及约定

$$\def{\arraystretch}{1.5}\begin{array}{|c|c|c|c|c|}\hline
\textbf{Subtask} & \bm{n} & \bm{m} & \bm{q}& \textbf{分值}\cr\hline
1 & n\le  10^4 & m\le 10 & q\le 10^3 & 10 \cr\hline
2 & n\le  10^5 & m=1 & q\le 10^5  & 20\cr\hline
3 & n\le  10^5 & m=2 & q\le 10^5 & 20\cr\hline
4 & \text{无特殊限制} & \text{无特殊限制} & \text{无特殊限制}& 50 \cr\hline
\end{array}$$

- 对于 $100\%$ 的数据，满足 $ 1 \leq n\le 1\times 10^6;1\le q \leq 1.2 \times 10^5;1 \leq m \leq 15;1 \leq K_i,G_i,p \leq 10^8;1\le a\le b\le n$ 。


---

---
title: "「Stoi2033」世界未末日"
layout: "post"
diff: 提高+/省选-
pid: P7977
tag: ['递推', '博弈论', '二分', 'O2优化']
---
# 「Stoi2033」世界未末日
## 题目背景

注意：**利用提交反馈以套取数据的行为属于作弊**。

> 就算是世界要崩溃  
> 亲爱的我也绝不会落泪  
> 不放弃爱过的那种感觉  
> 珍惜着有你记忆的一切  
> 就算是世界要倾斜  
> 亲爱的我也绝不说离别  
> 尽管末日威胁再强烈  
> 有爱就不累  
> ——《世界未末日》
## 题目描述

Vinsta 和 Stella 有 $n$ 堆石子，第 $i$ 堆有 $s_i$ 个。

她们约定从 Vinsta 开始轮流操作，每次操作可以选择不少于 $1$ 堆且不超过 $k$ 堆的石子。对于第 $i$ 堆石子，可以选取两个实数 $a,b$ 满足：

- $a \times b=s_i$
- $a+b=c,c\in[1,s_i]\cap\Z$

并丢掉第 $i$ 堆的 $c$ 个石子，即 $s_i\leftarrow s_i-c$。不能操作者败，她们想要知道 Vinsta 是否有必胜策略。
## 输入格式

第一行共三个正整数： $n,k,S$，其中 $S=\max\{s_i\}$。

第二行共 $n$ 个正整数： $s_i$，表示初始时第 $i$ 堆的石子个数。
## 输出格式

输出共一行。有必胜策略输出 `YES`，否则输出 `NO`。
## 样例

### 样例输入 #1
```
7 1 13
2 3 4 5 7 10 11

```
### 样例输出 #1
```
YES

```
### 样例输入 #2
```
8 1 13
2 3 4 5 7 10 11 13

```
### 样例输出 #2
```
NO

```
### 样例输入 #3
```
7 2 100
19 26 8 17 11 45 14

```
### 样例输出 #3
```
YES

```
## 提示

### 数据范围

**本题采用捆绑测试。**

| Subtask | $1\le n \le$ | $1\le S \le$ | 分值 |
| :-: | :-: | :-: | :-: |
| $1$ | $300$ | $300$ | $7$ |
| $2$ | $300$ | $3 \times 10^7$ | $8$ |
| $3$ | $300$ | $3\times 10^{10}$ | $16$ |
| $4$ | $3\times 10^6$ | $3$ | $3$ |
| $5$ | $3\times 10^6$ | $3 \times 10^3$ | $3$ |
| $6$ | $3\times 10^6$ | $3 \times 10^7$ | $16$ |
| $7$ | $3\times 10^6$ | $3\times 10^{10}$ | $47$ |

对于 $100\%$ 的数据， $1 \le k \le n \le 3 \times 10^6$，$1 \le S \le 3 \times 10^{10}$。


---

---
title: "[JRKSJ R5] Jalapeno and Garlic"
layout: "post"
diff: 提高+/省选-
pid: P8850
tag: ['数学', '递推', '2022', '洛谷原创', '洛谷月赛']
---
# [JRKSJ R5] Jalapeno and Garlic
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/peaku0fe.png)
## 题目描述

一个 $n$ 个点的环，点有点权 $a$，编号依次从 $1\sim n$。点 $1$ 与点 $n$ 相邻。

你希望只存在一个 $x\in[1,n]$ 满足 $a_x\ne 0$。为此，你需要按下面流程进行操作：

1. 选定一个 $x$，表示最终使得 $a_x\ne 0$。**此后不能更改 $x$ 的选择。**
2. 进行若干次修改操作，每次操作你可以选定一个 $y\in[1,n]$，将 $a_y\gets a_y-1$。同时在与点 $y$ 相邻的两个点中**等概率选择**一个，其点权将被 $+1$。

你希望期望的修改次数最少，所以求在最优策略下的期望操作次数（操作 1 不计入）。
## 输入格式

第一行一个整数 $n$。\
第二行 $n$ 个整数表示 $a_{1\dots n}$。
## 输出格式

一个整数，表示答案。输出时答案对 $1004535809$ 取模。
## 样例

### 样例输入 #1
```
2
114514 1919810
```
### 样例输出 #1
```
114514
```
### 样例输入 #2
```
3
1 1 2
```
### 样例输出 #2
```
4
```
## 提示

### 样例 $1$ 解释

选定 $x=2$，进行 $114514$ 次操作，每次的 $y=1$。

### 数据规模

**本题采用捆绑测试。**

| $\text{Subtask}$ | $n\le$ |分值 |
| :----------: | :----------: |:----------: |
| $1$ | $2$ | $5$ |
| $2$ | $10^3$ | $20$ |
| $3$ | $10^4$ | $20$ |
| $4$ | $10^5$ | $20$ |
| $5$ | $10^6$ | $35$ |

对于 $100\%$ 的数据，$2\le n\le 10^6$，$0\le a_i<1004535809$。


---

---
title: "[THUPC 2023 初赛] 欺诈游戏"
layout: "post"
diff: 提高+/省选-
pid: P9142
tag: ['递推', '博弈论', '2023', 'O2优化', 'THUPC']
---
# [THUPC 2023 初赛] 欺诈游戏
## 题目背景

在《LIAR GAME》中，小 E 看到了一个有趣的游戏。
## 题目描述

这个游戏名叫《走私游戏》。游戏规则大概是这样的：一名玩家扮演走私者，一名玩家扮演检察官。走私者可以将 $x$ 日元（$x$ 为 $[0,n]$ 内的整数，由走私者决定）秘密放入箱子中，而检查官需要猜测箱子中的金额。假设检察官猜了 $y$（$y$ 也必须是整数）。如果 $x=y$，则走私失败，走私者一分钱也拿不到。如果 $x>y$，则走私成功，走私者可以从检查官那里拿走 $x$ 日元。如果 $x<y$，则走私失败，但是由于冤枉检察官需要赔付给走私者 $y/2$ 日元。游戏分有限回合进行。双方轮流做走私者和检察官。

可以证明，最优情况下每个回合走私者会采用同一种策略，检察官也会采用同一种策略。小 E 想知道在一个回合中，双方的最优策略分别是什么。
## 输入格式

一行一个正整数 $n$。
## 输出格式

输出两行，每行 $n+1$ 个数，其中第 $i$ 个表示放/猜 $i-1$ 日元的概率。

第一行输出走私者的策略，第二行输出检察官的策略。

你需要保证，在一方的策略不变的情况下，另一方无论如何改变自己的策略，都不能使自己的期望收益比原来多。

可以证明，这样的策略是唯一的。

答案对 $998244353$ 取模。
## 样例

### 样例输入 #1
```
1

```
### 样例输出 #1
```
665496236 332748118
332748118 665496236

```
## 提示

#### 样例解释 1

这 $4$ 个数分别为 $2/3,1/3,1/3,2/3$。

#### 子任务

保证 $1\le n \le 400000$。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。


---

---
title: "[ICPC 2021 Nanjing R] Xingqiu's Joke"
layout: "post"
diff: 提高+/省选-
pid: P9849
tag: ['数学', '递推', '2021', 'Special Judge', 'O2优化', '最大公约数 gcd', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Xingqiu's Joke
## 题目描述

Once again, Xingqiu hides Chongyun's ice cream into a box with a strange lock. Liyue's summer has been always very hot and Chongyun suffers more because of his excessive yang (positive) energy, so he needs that ice cream desperately.

![](https://cdn.luogu.com.cn/upload/image_hosting/2dtcr426.png)

There are two integers $a$ and $b$ on the lock. Chongyun can perform the following three types of operations any number of times:
- Minus $1$ from both $a$ and $b$;
- Plus $1$ to both $a$ and $b$;
- Divide both $a$ and $b$ by one of their common $\textbf{prime}$ factor (that is to say, divide them by a $\textbf{prime}$ $g$ where $a$ and $b$ are both divisible by $g$).

The box will be unlocked if either $a$ or $b$ or both become $1$. To help Chongyun gets the ice cream back as quickly as possible, please tell him the minimum number of operations needed to unlock the box.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 300$) indicating the number of test cases. For each test case:

The first and only line contains two integers $a$ and $b$ ($1 \le a, b \le 10^9$, $a \ne b$).
## 输出格式

For each test case output one line containing one integer indicating the minimum number of operations to make $a$ or $b$ or both equal $1$.
## 样例

### 样例输入 #1
```
5
4 7
9 8
32 84
11 35
2 1

```
### 样例输出 #1
```
2
7
5
4
0

```
## 提示

For the first sample test case, the optimal way is $(4, 7) \rightarrow (3, 6) \rightarrow (1, 2)$.

For the second sample test case, the optimal way is to apply the first type of operation $7$ times.

For the third sample test case, the optimal way is $(32, 84) \rightarrow (16, 42) \rightarrow (15, 41) \rightarrow (14, 40) \rightarrow (13, 39) \rightarrow (1, 3)$.

For the fourth sample test case, the optimal way is $(11, 35) \rightarrow (12, 36) \rightarrow (6, 18) \rightarrow (2, 6) \rightarrow (1, 3)$.
## 题目翻译

## 题目描述
有 $T$ 个盒子，每盒子上有一个锁，锁上有两个整数 $a$ 和 $b$。你可以对这个锁做若干次以下 3 种操作：

- $a$ 和 $b$ 分别减去 $1$
- $a$ 和 $b$ 分别增加 $1$
- $a$ 和 $b$ 分别除以它们共同的素数因子

如果 $a$ 或 $b$ 或两者都变为 $1$，盒子就会解锁。请你编写一个程序，计算每个盒子的锁打开的最少步骤数量。

## 输入格式
第一行输入一个整数 $T(1≤T≤300)$。

接下来 $T$ 行，每行输入 $a$ 和 $b$，表示每个盒子的锁的信息。

## 输出格式  

共输出 $T$ 行，每行输出对应盒子解锁的最少步骤。


---

