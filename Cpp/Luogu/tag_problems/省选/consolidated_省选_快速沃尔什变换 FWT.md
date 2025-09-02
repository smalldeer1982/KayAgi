---
title: "[USACO24DEC] All Pairs Similarity P"
layout: "post"
diff: 省选/NOI-
pid: P11458
tag: ['USACO', '2024', '容斥原理', '快速沃尔什变换 FWT', '状压 DP']
---
# [USACO24DEC] All Pairs Similarity P
## 题目描述

**注意：本题的内存限制为 512MB，通常限制的 2 倍。**

Farmer John 的 $N$（$1\le N\le 5\cdot 10^5$）头奶牛都被分配了一个长度为 $K$ 的非全零位串（$1\le K\le 20$）。不同的奶牛可能被分配到相同的位串。

两个位串的 Jaccard 相似度定义为它们的按位与的结果中 $\texttt{1}$ 的数量除以它们的按位或的结果中 $\texttt{1}$ 的数量。例如，位串 $\texttt{11001}$ 和 $\texttt{11010}$ 的 Jaccard 相似度为 $2/4$。

对于每头奶牛，输出她的位串与每头奶牛（包括她自己）的位串的 Jaccard 相似度之和，对 $10^9+7$ 取模。具体地说，如果总和等于一个有理数 $a/b$，其中 $a$ 和 $b$ 是互质的整数，则输出范围 $[0,10^9+7)$ 内的唯一整数 $x$，使得 $bx-a$ 被 $10^9+7$ 整除。
## 输入格式

输入的第一行包含 $N$ 和 $K$。

以下 $N$ 行每行包含一个整数 $i\in (0,2^K)$，表示一头奶牛分配到了 $i$ 的 $K$ 位二进制表示。
## 输出格式

对于每头奶牛输出一行，包含所求的总和，对 $10^9+7$ 取模。

## 样例

### 样例输入 #1
```
4 2
1
1
2
3
```
### 样例输出 #1
```
500000006
500000006
500000005
500000006
```
## 提示

奶牛们分配到了以下的位串：$[\texttt{01}, \texttt{01}, \texttt{10}, \texttt{11}]$。

对于第一头奶牛，总和为 $\text{sim}(1,1)+\text{sim}(1,1)+\text{sim}(1,2)+\text{sim}(1,3)=1+1+0+1/2\equiv 500000006\pmod{10^9+7}$。

第二头奶牛的位串与第一头奶牛相同，所以她的总和也与第一头奶牛相同。

对于第三头奶牛，总和为 $\text{sim}(2,1)+\text{sim}(2,1)+\text{sim}(2,2)+\text{sim}(2,3)=0+0+1+1/2\equiv 500000005\pmod{10^9+7}$。

- 测试点 $2\sim 15$：对于每一个 $K\in \{10,15,16,17,18,19,20\}$ 有两个测试点。


---

---
title: "[集训队互测 2015] 胡策的统计"
layout: "post"
diff: 省选/NOI-
pid: P11734
tag: ['2015', '集训队互测', '快速沃尔什变换 FWT', '集合幂级数，子集卷积']
---
# [集训队互测 2015] 胡策的统计
## 题目描述

在 OI 界，有一位无人不知无人不晓，OI 水平前无古人后无来者的胡策，江湖人称一眼秒题胡大爷！

今天胡策在研究无向图的连通性。对于一个无向图定义它的连通值为该图连通块数的阶乘。

为了研究连通值的性质，胡策随手画了一个 $n$ 个结点的简单无向图 $G$，结点分别编号为 $1, \dots, n$，他想统计出 $G$ 的所有生成子图的连通值之和。

胡策当然会做啦！但是他想考考你。你只用输出结果对 $998244353$ （$7 \times 17 \times 2^{23} + 1$，一个质数） 取模后的结果。

简单无向图即无重边无自环的无向图。生成子图即原图中删去若干条边（可以是 $0$ 条）后形成的图。
## 输入格式

第一行两个整数 $n, m$，表示 $G$ 的结点数和边数。保证 $n \geq 1，m \geq 0$。

接下来 $m$ 行，每行两个整数 $v, u$，表示 $v$ 号结点和 $u$ 号结点之间有一条无向边。保证 $1 \leq v, u \leq n$，保证没有重边和自环。
## 输出格式

一行，一个整数表示答案。
## 样例

### 样例输入 #1
```
6 13
1 2
1 3
2 3
1 4
4 2
3 4
5 2
3 5
5 4
6 2
6 3
6 4
6 5
```
### 样例输出 #1
```
16974
```
## 提示

| 测试点编号 | $n \leq$ | 特殊限制 |
| :----------: | :----------: | :----------: |
| $1$ | $6$ | 无 |
| $2$ | $10$ | 无 |
| $3$ | $10$ | 无 |
| $4$ | $17$ | 无 |
| $5$ | $17$ | 无 |
| $6$ | $17$ | 无 |
| $7$ | $20$ | $G$ 为完全图 |
| $8$ | $20$ | 无 |
| $9$ | $20$ | 无 |
| $10$ | $20$ | 无 |



---

---
title: "「LAOI-9」多维空间中的游戏"
layout: "post"
diff: 省选/NOI-
pid: P11897
tag: ['多项式', 'O2优化', '快速沃尔什变换 FWT', '单位根反演']
---
# 「LAOI-9」多维空间中的游戏
## 题目描述

小 $\mathbf A$ 和小 $\mathbf B$ 正在玩一个有趣的游戏。

游戏将在一个 $\underbrace{2\times2\times2\times\cdots\times2}_{k 个 2}$ 的 $k$ 维空间中进行。最小的节点的坐标为 $(\underbrace{0,0,0,\cdots,0}_{k个0})$，最大的节点的坐标为 $(\underbrace{1,1,1,\cdots,1}_{k个1})$。

下面是 $k=3$ 时的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/2khrowsw.png)

小 $\mathbf A$ 和小 $\mathbf B$ 各执一枚 $k$ 维空间中的点。

小 $\mathbf A$ 和小 $\mathbf B$ 轮流操作，小 $\mathbf A$ 先手。

定义一个维度为可操作的，当且仅当两个点中存在至少一个点在这个维度上的坐标不为 $0$。然后，操作方可以将两个点的某个可操作的维度的坐标置为 $0$。

如图，这是一个合法的操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/8ajfdwcm.png)

这也是一个合法的操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/65f0tcaa.png)

但是这不是一个合法的操作，因为两个点在这个维度上的坐标均为 $0$：

![](https://cdn.luogu.com.cn/upload/image_hosting/f00hqo6l.png)

无法操作者输。

相信大家一定发现了，我们可以将任意一个坐标编码为一个二进制数。例如对于坐标 $(0,1,1,1,0,0,1,0)$，可以编码为 $\tt 01110010$，对应十进制数 $114$。

小 $\mathbf A$ 和 $\mathbf B$ 将进行 $q$ 轮游戏。两人绝顶聪明，都想要自己赢。每一轮双方点的位置将会随机生成，进一步地，生成到编码为 $x$ 的坐标的概率为 $p_x$。

由于小 $\mathbf A$ 先手，所以每轮她们将会划定一个可落子区域 $[l,r]$，其他区域则为不可落子区域。如果小 $\mathbf A$ **初始**的点坐标编码后的值在区间 $[l,r]$ 外，则将会判为小 $\mathbf B$ 胜。（此规则对小 $\mathbf B$ 不生效，也就是即使小 $\mathbf B$ 初始的点坐标编码后的值在区间 $[l,r]$ 外，也不会直接判为小 $\mathbf A$ 胜）

现在对于第 $i$ 轮，可落子区域为 $[l_i,r_i]$，小 $\mathbf B$ 会有 $a_i$ 个询问，每个询问为当她的点被随机到编号为 $x$ 的坐标，且小 $\mathbf A$ 的点按照 $p$ 的概率随机生成时，她的胜率为多少。答案对 $998244353$ 取模。
## 输入格式

第一行一个正整数 $c$ 表示子任务编号，特殊地，样例的编号为 $0$。

接下来一行一个正整数 $t$ 表示数据读入输出方法。当 $t=1$ 时，你需要在下一行接着读入一个整数 $seed$ 表示随机种子。

接下来一行一个正整数 $k$ 表示维度数。

接下来一行 $2^k$ 个非负整数 $p_0,p_1,\cdots,p_{2^{k}-1}$ 表示生成到编码为 $x$ 的坐标的概率为 $p_x$。

接下来一行一个正整数 $q$ 表示游戏轮数。

接下来 $q$ 组询问，对于第 $i$ 组询问（下标从 $1$ 开始）：

每组询问第一行三个整数，表示 $a_i,l_i,r_i$。

当 $t=0$ 时，接下来一行 $a_i$ 个整数 $x_{i,1},x_{i,2},\cdots,x_{i,a_i}$，表示每次小 $\mathbf B$ 的询问。

当 $t=1$ 时，接下来小 $\mathbf B$ 的第 $j$ 个询问（下标从 $1$ 开始）$x_{i,j}$ 为 $seed\times i\times j\times 50007\bmod (2^k)$。

对于 C++ 选手，我们下发了一份数据读入模板 `down.cpp`，您只需要完善其中的代码部分即可。
## 输出格式

当 $t=0$ 时，对于第 $i$ 组询问输出一行 $a_i$ 个整数，表示这组询问所有答案模 $998244353$ 后的值。

当 $t=1$ 时，对于每组询问输出一行一个整数，表示这组询问所有答案模 $998244353$ 后的异或和。
## 样例

### 样例输入 #1
```
0
0
2
0 1 998244351 2
2
1 2 3
2
2 0 1
2 3
```
### 样例输出 #1
```
3
1 1
```
### 样例输入 #2
```
0
1
50007
3
1 2 3 4 5 6 7 998244326
1
2 0 7
```
### 样例输出 #2
```
0
```
## 提示

### 样例 1 解释

对于第一组询问，当小 $\mathbf A$ 的点在编号为 $1$ 的坐标时，由于超出了可落子区域，小 $\mathbf B$ 胜；当小 $\mathbf A$ 的点在编号为 $2$ 的坐标时，小 $\mathbf A$ 胜；当小 $\mathbf A$ 的点在编号为 $3$ 的坐标时，小 $\mathbf B$ 胜。

故在模意义下，小 $\mathbf B$ 的胜率：$1+2=3$。

### 样例 2 解释

解码后，$x_{1,1}=1,x_{1,2}=2$，答案分别为 $18,18$，异或和为 $0$。

**本题目采用捆绑测试**。

| 子任务编号 | $k\le$ | $q\le$ | $a_i\le$ | 时间限制 | 特殊性质 | 分值 |
| :--------: | :----: | :----: | :------: | :------: | :------: | :--: |
|    $0$     |  $5$   |  $30$  |   $30$   |   1 秒   |   样例    | $0$  |
|    $1$     |  $1$   |  $30$  |   $30$   |   1 秒   |          | $5$  |
|    $2$     |  $2$   |  $30$  |   $30$   |   1 秒   |          | $5$  |
|    $3$     |  $10$  | $300$  |  $100$   |   1 秒   |          | $20$ |
|    $4$     |  $15$  | $100$  | $2^{15}$ |   1 秒   |  $t=1$   | $20$ |
|    $5$     |  $16$  | $1000$ |  $100$   |   1 秒   |          | $10$ |
|    $6$     |  $16$  | $2000$ |  $3000$  |   1 秒   |  $t=1$   | $10$ |
|    $7$     |  $16$  | $3000$ | $2^{15}$ |   2 秒   |  $t=1$   | $30$ |

对于 $100\%$ 数据，满足 $1\le k\le 16,1\le q\le 3000,0\le p_i<998244353,1\le a_i\le 2^{15},0\le l_i\le r_i< 2^k,0\le x_{i,j}< 2^k,t\in\{0,1\},0\le seed\le 50007$。保证 $\sum_{i=0}^{2^k-1}p_i\equiv1\pmod{998244353}$。

本题输入输出量大，请使用较快的输入输出方式。


---

---
title: "集合幂级数 exp"
layout: "post"
diff: 省选/NOI-
pid: P12230
tag: ['快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', '集合幂级数，子集卷积']
---
# 集合幂级数 exp
## 题目描述

给定一个集合幂级数 $F(x)$，保证 $[x^{\varnothing}]F(x)=0$。定义 $x$ 的乘法为子集卷积，你需要对所有 $S\subseteq\{1,2,\cdots,n\}$ 求出 $[x^S]e^{F(x)}$ 对 $998244353$ 取模后的值。

如果你仍不清楚题意，可以阅读题面最后的提示部分。
## 输入格式

第一行一个正整数 $n$。

接下来一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]F(x)$，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 输出格式

输出一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]e^{F(x)}$ 对 $998244353$ 取模后的值，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 样例

### 样例输入 #1
```
2
0 1 2 3
```
### 样例输出 #1
```
1 1 2 5
```
### 样例输入 #2
```
4
0 11 83 73 34 53 72 57 81 92 10 31 44 33 93 10
```
### 样例输出 #2
```
1 11 83 986 34 427 2894 38772 81 983 6733 87643 2798 38232 238499 3459260
```
## 提示

#### 【数据范围】

对于所有数据，保证 $1\le n\le 20$，$[x^S]F(x)\in[0,998244353)\cap\mathbb Z$，$[x^{\varnothing}]F(x)=0$。

本题有 $20$ 个测试点，第 $i$ 个测试点满足 $n=i$。

#### 【提示】

假设 $F(x)=\sum_S f_Sx^S$，那么 $[x^S]F(x)=f_S$。

在本题中，$x$ 的乘法被定义为子集卷积，即：
$$x^S\cdot x^T=\begin{cases}0&S\cap T\neq\varnothing\\x^{S\cup T}&\text{otherwise}\end{cases}$$

根据泰勒展开，有：
$$e^{F(x)}=\sum_{n\ge 0}\frac{F^n(x)}{n!}$$


---

---
title: "集合幂级数 ln"
layout: "post"
diff: 省选/NOI-
pid: P12231
tag: ['快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', '集合幂级数，子集卷积']
---
# 集合幂级数 ln
## 题目描述

给定一个集合幂级数 $F(x)$，保证 $[x^{\varnothing}]F(x)=1$。定义 $x$ 的乘法为子集卷积，可以证明存在一个 $G(x)$ 满足 $e^{G(x)}=F(x)$，你需要对 $S\subseteq\{1,2,\cdots,n\}$ 求出 $[x^S]G(x)$ 对 $998244353$ 取模后的值。

如果你仍不清楚题意，可以阅读题面最后的提示部分。
## 输入格式

第一行一个正整数 $n$。

接下来一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]F(x)$，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 输出格式

输出一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]G(x)$ 对 $998244353$ 取模后的值，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 样例

### 样例输入 #1
```
2
1 2 3 4
```
### 样例输出 #1
```
0 2 3 998244351
```
### 样例输入 #2
```
4
1 8 3 9 2 0 1 8 7 0 0 1 7 3 4 1
```
### 样例输出 #2
```
0 8 3 998244338 2 998244337 998244348 78 7 998244297 998244332 274 998244346 171 60 998242876
```
## 提示

#### 【数据范围】

对于所有数据，保证 $1\le n\le 20$，$[x^S]F(x)\in[0,998244353)\cap\mathbb Z$，$[x^{\varnothing}]F(x)=1$。

本题有 $20$ 个测试点，第 $i$ 个测试点满足 $n=i$。

#### 【提示】

假设 $F(x)=\sum_S f_Sx^S$，那么 $[x^S]F(x)=f_S$。

在本题中，$x$ 的乘法被定义为子集卷积，即：
$$x^S\cdot x^T=\begin{cases}0&S\cap T\neq\varnothing\\x^{S\cup T}&\text{otherwise}\end{cases}$$

根据泰勒展开，有：
$$e^{F(x)}=\sum_{n\ge 0}\frac{F^n(x)}{n!}$$

可以证明本题答案唯一。


---

---
title: "集合幂级数求逆"
layout: "post"
diff: 省选/NOI-
pid: P12232
tag: ['快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', '集合幂级数，子集卷积']
---
# 集合幂级数求逆
## 题目描述

给定一个集合幂级数 $F(x)$，保证 $[x^{\varnothing}]F(x)\neq 0$。定义 $x$ 的乘法为子集卷积，可以证明存在一个 $G(x)$ 满足 $F(x)G(x)=1$，你需要对 $S\subseteq\{1,2,\cdots,n\}$ 求出 $[x^S]G(x)$ 对 $998244353$ 取模后的值。

如果你仍不清楚题意，可以阅读题面最后的提示部分。
## 输入格式

第一行一个正整数 $n$。

接下来一行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]F(x)$，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 输出格式

输出行 $2^n$ 个非负整数，第 $i$ 个整数表示 $[x^S]G(x)$ 对 $998244353$ 取模后的值，其中 $a\in S$ 当且仅当 $(i-1)$ 二进制下从低到高第 $a$ 位为 $1$。
## 样例

### 样例输入 #1
```
2
1 2 3 4
```
### 样例输出 #1
```
1 998244351 998244350 8
```
### 样例输入 #2
```
4
1 1 4 5 1 4 1 9 1 9 8 1 0 1 2 3
```
### 样例输出 #2
```
1 998244352 998244349 3 998244352 998244351 7 11 998244352 998244346 0 73 2 19 998244345 998244164
```
## 提示

#### 【数据范围】

对于所有数据，保证 $1\le n\le 20$，$[x^S]F(x)\in[0,998244353)\cap\mathbb Z$，$[x^{\varnothing}]F(x)\neq 0$。

本题有 $20$ 个测试点，第 $i$ 个测试点满足 $n=i$。

#### 【提示】

假设 $F(x)=\sum_S f_Sx^S$，那么 $[x^S]F(x)=f_S$。

在本题中，$x$ 的乘法被定义为子集卷积，即：
$$x^S\cdot x^T=\begin{cases}0&S\cap T\neq\varnothing\\x^{S\cup T}&\text{otherwise}\end{cases}$$

可以证明本题答案唯一。


---

---
title: "[NERC 2022] Game of Questions"
layout: "post"
diff: 省选/NOI-
pid: P12796
tag: ['2022', 'Special Judge', '快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', 'ICPC', '状压 DP', 'NERC/NEERC']
---
# [NERC 2022] Game of Questions
## 题目描述

Genie is taking part in an intellectual game. The game consists of $n$ questions, and there are $m$ participants numbered from $1$ to $m$. Genie is the participant number $1$.

For each question $i$ and participant $j$, it is known whether the participant will answer the question correctly or not.

The goal of the game is to be the last participant staying in the game.

The game is conducted as follows. First, all $n$ questions get shuffled uniformly at random (all $n!$ permutations are equally likely). Then, the questions are asked one by one. Each participant answers the question. If all participants still in the game answer the question correctly, or if all of them answer the question incorrectly, nothing happens. Otherwise, those participants who answer the question incorrectly lose and leave the game.

After all $n$ questions are asked, all participants who are still in the game are declared to be the winners.

What is the probability that Genie will win the game?
## 输入格式

The first line contains two integers $n$ and $m$ --- the number of questions and the number of participants ($1 \le n \le 2 \cdot 10^5$; $2 \le m \le 17$).

The $i$-th of the next $n$ lines contains $m$ characters $s_{i, 1}, s_{i, 2}, \ldots, s_{i, m}$. Character $s_{i, j}$ is $\tt{1}$ if participant $j$ answers question $i$ correctly or $\tt{0}$ otherwise.
## 输出格式

Print the probability that Genie will win the game. Your answer will be considered correct if its absolute or relative error does not exceed $10^{-9}$.
## 样例

### 样例输入 #1
```
1 5
11010
```
### 样例输出 #1
```
1.0000000000000000
```
### 样例输入 #2
```
3 3
011
101
110
```
### 样例输出 #2
```
0.3333333333333333
```
### 样例输入 #3
```
6 4
1011
0110
1111
0110
0000
1101
```
### 样例输出 #3
```
0.1666666666666667
```
## 提示

In the first example, there is a single question and Genie will answer it correctly, thus winning the game (along with participants $2$ and $4$).

In the second example, one participant will leave after the first asked question, and another participant will leave after the second asked question. Each participant will win with probability $\frac{1}{3}$.


---

---
title: "[HAOI2015] 按位或"
layout: "post"
diff: 省选/NOI-
pid: P3175
tag: ['2015', '河南', 'Special Judge', '容斥原理', '快速沃尔什变换 FWT']
---
# [HAOI2015] 按位或
## 题目描述

刚开始你有一个数字 $0$，每一秒钟你会随机选择一个 $[0,2^n-1]$ 的数字，与你手上的数字进行或（C++,C 的 `|`，pascal 的 `or`）操作。选择数字 $i$ 的概率是 $p_i$。保证 $0\leq p_i \leq 1$，$\sum p_i=1$ 。问期望多少秒后，你手上的数字变成 $2^n-1$。

## 输入格式

第一行输入 $n$ 表示 $n$ 个元素，第二行输入 $2^n$ 个数，第 $i$ 个数表示选到 $i-1$ 的概率。

## 输出格式

仅输出一个数表示答案，绝对误差或相对误差不超过 $10^{-6}$ 即可算通过。如果无解则要输出 `INF`。
## 样例

### 样例输入 #1
```
2
0.25 0.25 0.25 0.25
```
### 样例输出 #1
```
2.6666666667
```
## 提示

对于 $100\%$ 的数据，$n\leq 20$。

以下为 spj 源代码。

```cpp
//liuchenrui 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#define AC {fclose(fstd),fclose(fuser);return 0;}
#define WA {fclose(fstd),fclose(fuser);return 1;}
#define PE {fclose(fstd),fclose(fuser);return 5;}
#define eps 1e-6
int main(int const argc, char*const argv[]){
    FILE *fstd,*fuser;
    fstd=fopen(argv[2],"r");
    fuser=fopen(argv[3],"r");
    //fstd=fopen("x1.in","r");
    //fuser=fopen("x2.in","r");
    char s[30],t[30];
    if(fscanf(fuser,"%s",s+1)==-1)WA;
    fscanf(fstd,"%s",t+1);
    if(s[1]=='I' && t[1]=='I')AC;
    if(s[1]=='I' || t[1]=='I')WA;
    double p,q;
    sscanf(s+1,"%lf",&p);
    sscanf(t+1,"%lf",&q);
    if(fabs(p-q)<eps)AC
    else{
        if(fabs(p-q)/q<eps)AC;
        if(fabs(q-p)/q<eps)AC;
        if(fabs(p-q)/p<eps)AC;
        if(fabs(q-p)/p<eps)AC;
    }
    WA;
}

```


---

---
title: "【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)"
layout: "post"
diff: 省选/NOI-
pid: P4717
tag: ['快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT']
---
# 【模板】快速莫比乌斯/沃尔什变换 (FMT/FWT)
## 题目描述

给定长度为 $2^n$ 两个序列 $A,B$，设 

$$C_i=\sum_{j\oplus k = i}A_j \times B_k$$

分别当 $\oplus$ 是 or, and, xor 时求出 $C$。
## 输入格式

第一行，一个整数 $n$。  
第二行，$2^n$ 个数 $A_0, A_1, \ldots, A_{2^n-1}$。  
第三行，$2^n$ 个数 $B_0, B_1, \ldots, B_{2^n-1}$。

## 输出格式

三行，每行 $2^n$ 个数，分别代表 $\oplus$ 是 or, and, xor 时 $C_0, C_1, \ldots, C_{2^n-1}$ 的值 $\bmod\ 998244353$。

## 样例

### 样例输入 #1
```
2
2 4 6 8
1 3 5 7

```
### 样例输出 #1
```
2 22 46 250
88 64 112 56
100 92 68 60

```
## 提示

$1 \le n \le 17$。


---

---
title: "[Cnoi2019] 人形演舞"
layout: "post"
diff: 省选/NOI-
pid: P5387
tag: ['博弈论', '2019', '快速沃尔什变换 FWT']
---
# [Cnoi2019] 人形演舞
## 题目背景

由于出题人都退役了, 所以题目背景咕咕咕~了.
## 题目描述

Cirno 与 Marisa 之间有一个博弈:

首先给定 一个 **有序整数序列** $V$, 所有的数字都是在 $[1, m]$ 之间。

每次一个人可以选取 $x \in V, y \in [1, x]$, 且 $ x \oplus y \in [0, x)$ , 然后把  $x$ 变为 $x \oplus y$。

$\oplus$ 表示按位异或。

当一个人不能操作时, 则视作失败。

假定 Cirno 和 Marisa 都使用最优策略。

现在 Cirno 想知道自己先手时获胜的方案数对 $998244353$ 取模后是多少。

## 输入格式

一行，两个整数 $|V|, m$
## 输出格式

一行，表示答案.
## 样例

### 样例输入 #1
```
4 5
```
### 样例输出 #1
```
312
```
## 提示

对于 100% 的数据，$|V| \le 10^{18}, m \le 10^6$。

采用捆绑测试。


---

---
title: "【模板】子集卷积"
layout: "post"
diff: 省选/NOI-
pid: P6097
tag: ['O2优化', '快速沃尔什变换 FWT', '快速莫比乌斯变换 FMT', '集合幂级数，子集卷积']
---
# 【模板】子集卷积
## 题目背景

这是一道模板题。
## 题目描述

给定两个长度为 $2^n$ 的序列 $a_0,a_1,\cdots,a_{2^n-1}$ 和 $b_0,b_1,\cdots,b_{2^n-1}$，你需要求出一个序列 $c_0,c_1,\cdots,c_{2^n-1}$，其中 $c_k$ 满足：

$$c_k=\sum_{\substack{{i \& j=0}\\{i~\mid~ j=k}}} a_i b_j$$

其中$~\mid~$表示按位或，$\&$表示按位与。

答案对 $10^9+9$ 取模。
## 输入格式

第一行输入一个正整数 $n$ ，表示集合的大小。

第二行有 $2^n$ 个整数，描述了 $a$。

第三行有 $2^n$ 个整数，描述了 $b$。
## 输出格式

输出一行 $2^n$ 个整数，表示 $c$。
## 样例

### 样例输入 #1
```
2
1 0 2 1
2 0 2 1
```
### 样例输出 #1
```
2 0 6 3
```
## 提示

对于所有数据，$1\le n\le 20$，$0\le a_i,b_i< 10^9+9$。


---

---
title: "[省选联考 2022] 卡牌"
layout: "post"
diff: 省选/NOI-
pid: P8292
tag: ['各省省选', '2022', 'O2优化', '容斥原理', '快速沃尔什变换 FWT']
---
# [省选联考 2022] 卡牌
## 题目描述

小 A 有 $n$ 张卡牌，编号为 $1, 2, \ldots, n$。每张卡牌上写着一个正整数，第 $i$ 张卡牌上的正整数为 $s_i$。

现在有 $m$ 轮游戏，第 $i$ 轮游戏会给出 $c_i$ 个质数，小 A 需要选择任意多张卡牌，使得这些卡牌上面的正整数的乘积能被该轮游戏给出的每个质数整除。

这当然难不倒小 A，于是他开始思考一个更难的问题，对于每一轮游戏，他有多少种卡牌的选法。

这给小 A 整不会了，于是他只能来求助你，你只需要告诉他答案模 $998244353$ 的值即可。两种选法 A 和 B 互不相同当且仅当存在一张卡牌在 A 中被选择但在 B 中未被选择或者存在一张卡牌在 B 中被选择但在 A 中未被选择。注意：牌面上的数字相同但编号不相同的两张卡牌被视为不同的卡牌。
## 输入格式

第一行一个正整数 $n$，表示卡牌数量。

第二行 $n$ 个正整数 $s_i$，表示每张卡牌上写的数字。

第三行一个正整数 $m$，表示游戏轮数。

接下来 $m$ 行，每行第一个正整数 $c_i$，表示该轮游戏给出的质数个数，接下来 $c_i$ 个质数 $p_{i, j}$，表示该轮游戏给出的所有质数。数据保证 $\sum_i c_i \le 18000$，即所有 $c_i$ 之和不超过 $18000$。
## 输出格式

输出 $m$ 行，每行一个整数，第 $i$ 行表示第 $i$ 轮游戏的方案数模 $998244353$ 的值。
## 样例

### 样例输入 #1
```
5
10 2 10 5 46
4
2 2 5
2 2 23
1 3
1 23
```
### 样例输出 #1
```
27
16
0
16
```
### 样例输入 #2
```
见附件中的 card/card2.in
```
### 样例输出 #2
```
见附件中的 card/card2.ans
```
## 提示

**【样例解释 #1】**

第一轮游戏：除了以下 $5$ 种方案外其它方案都可行：什么都不选、选 $2$、选 $5$、选 $46$、选 $2$ 和 $46$。所以答案为 $2^5 - 5 = 27$。

第二轮游戏：只要选了 $46$，其它卡牌选不选均可，所以答案为 $2^4 = 16$。

**【数据范围】**

对于 $100 \%$ 的数据，$1 \le n \le {10}^6$，$1 \le s_i \le 2000$，$1 \le m \le 1500$，$1 \le c_i, \sum_i c_i \le 18000$，$2 \le p_{i, j} \le 2000$。

| 测试点 | $n \le$ | $m \le$ | $\sum_i c_i \le$ | 其他限制 |
|:-:|:-:|:-:|:-:|:-:|
| $1 \sim 2$ | $10$ | $10$ | $20$ | $s_i \le 30$ |
| $3 \sim 5$ | $10$ | $20$ | $50$ | 无 |
| $6 \sim 8$ | ${10}^6$ | $1500$ | $10000$ | $s_i \le 30$ |
| $9 \sim 11$ | $10000$ | $1000$ | $5000$ | $s_i \le 500$ |
| $12 \sim 13$ | $1000$ | $100$ | $1000$ | 无 |
| $14 \sim 17$ | $5000$ | $600$ | $7000$ | 无 |
| $18 \sim 20$ | ${10}^6$ | $1500$ | $18000$ | 无 |


---

---
title: "[USACO23FEB] Problem Setting P"
layout: "post"
diff: 省选/NOI-
pid: P9131
tag: ['USACO', '2023', '快速沃尔什变换 FWT', '状压 DP']
---
# [USACO23FEB] Problem Setting P
## 题目描述

**Note: The memory limit for this problem is 512MB, twice the default.**

Farmer John created $N(1 \le N \le 10^5)$ problems. He then recruited $M (1 \le M \le 20)$ test-solvers, each of which rated every problem as "easy" or "hard."

His goal is now to create a problemset arranged in increasing order of difficulty, consisting of some subset of his $N$ problems arranged in some order. There must exist no pair of problems such that some test-solver thinks the problem later in the order is easy but the problem earlier in the order is hard.

Count the number of distinct nonempty problemsets he can form, modulo $10^9+7$. 
## 输入格式

The first line contains $N$ and $M$.

The next $M$ lines each contain a string of length $N$. The $i$-th character of this string is `E` if the test-solver thinks the ith problem is easy, or `H` otherwise. 
## 输出格式

The number of distinct problemsets FJ can form, modulo $10^9+7$. 
## 样例

### 样例输入 #1
```
3 1
EHE
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
10 6
EHEEEHHEEH
EHHHEEHHHE
EHEHEHEEHH
HEHEEEHEEE
HHEEHEEEHE
EHHEEEEEHE
```
### 样例输出 #2
```
33
```
## 提示

### Explanation for Sample 1

The nine possible problemsets are as follows:

$[1]$  
$[1,2]$  
$[1,3]$  
$[1,3,2]$  
$[2]$  
$[3]$  
$[3,1]$  
$[3,2]$  
$[3,1,2]$  

Note that the order of the problems within the problemset matters. 

### SCORING

 - Inputs $3-4$: $M=1$
 - Inputs $5-14$: $M \le 16$
 - Inputs $15-22$: No additional constraints.
## 题目翻译

Farmer John 出了 $n$ 道题，聘了 $m$ 个验题人来品鉴难度。

难度只有简单（`E`）和困难（`H`）两种。

Farmer John 将从中选出若干道（**至少一道**），并以一定顺序排列，使得前一道题目中任意一个觉得此题困难的验题人也觉得后面一道题目困难。

回答有多少种选出来并排列的方案，对 $10^9+7$ 取模。

$1\le n\le10^5$，$1\le m\le20$。


---

