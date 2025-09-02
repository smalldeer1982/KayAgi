---
title: "「ALFR Round 2」B 篮球比赛"
layout: "post"
diff: 提高+/省选-
pid: P10586
tag: ['动态规划 DP', 'O2优化', '矩阵乘法']
---
# 「ALFR Round 2」B 篮球比赛
## 题目背景

![](https://nimg.ws.126.net/?url=http%3A%2F%2Fdingyue.ws.126.net%2F2023%2F0820%2F075e9bccj00rzoph900wkd000t200i6p.jpg&thumbnail=660x2147483647&quality=80&type=jpg)
## 题目描述

小山即将参加 $n$ 场篮球比赛，他有一个多项式函数 $f(x)=a_0+a_1x^1+a_2x^2+\dots+a_kx^k$ 与 $m$ 个和为 $1$ 的数 $p_1,p_2,p_3,\dots,p_m$。

他所在的球队有 $\dfrac{f(i)}{\sum_{j=1}^n f(j)}$ 的概率在第 $i$ 场比赛中取得**第一次**胜利，这意味着前面的 $i-1$ 场都输了。

接下来，如果第 $i$ 场比赛中小山所在球队取得了胜利，则对于 $1\le j\le m$，他们有 $p_j$ 的概率在第 $i+j$ 场比赛取得下一次胜利，这意味着如果 $j\gt1$，第 $i+1$ 场到第 $i+j-1$ 场都输了（若 $i+j>n$，则之后的比赛都输，没有再胜利）。

小山想知道他所在球队的期望胜利场数，你能帮帮他吗？

注意：在计算时，如果遇到分数（比如 $\dfrac{f(i)}{\sum_{j=1}^n f(j)}$），应使用分数取模形式。如果不知道什么是分数取模形式，参见 [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)。

为了方便你的计算，输入数据将直接给出 $p_i,a_i$ 对 $998244353$ 取模的结果。
## 输入格式

第一行 $3$ 个整数 $n, m, k$，含义如上所述。

第二行 $m$ 个整数，第 $i$ 个整数表示 $p_i$ 模 $998244353$ 的值。

第三行 $k + 1$ 个整数，第 $i$ 个整数表示 $a_{i - 1}$ 模 $998244353$ 的值。

**注意是先输入 $p$ 再输入 $a$。**
## 输出格式

一行一个数，表示答案模 $998244353$ 的值。
## 样例

### 样例输入 #1
```
4 3 3
598946612 898419918 499122177
998244308 79 998244317 5
```
### 样例输出 #1
```
319837492
```
## 提示

### 样例解释

在第一组样例中：$p_1=0.2,p_2=0.3,p_3=0.5$；$f(1)=3,f(2)=9,f(3)=3,f(4)=15$。胜利场数期望为 $1.2988$。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | $n=1$ |
| $1$ | $30$ | $n\le10^6$ |
| $2$ | $60$ | - |

对于 $100\%$ 的数据，$1\le n\le 10^{18}$，$1\le m,k \le 50$，保证 $\sum_{j=1}^n f(j)$ 不被 $998244353$ 整除。


---

---
title: "闪耀之塔"
layout: "post"
diff: 提高+/省选-
pid: P11410
tag: ['贪心', '矩阵乘法']
---
# 闪耀之塔
## 题目描述

闪耀之塔是一棵节点结点从 $1\sim 2^n -1$ 编号，以 $1$ 为根，共有 $n$ 层的满二叉树。

非叶子节点节点 $i$ 的左右儿子的编号分别为 $i\times2$ 和 $i \times 2 +1$。

多萝茜需要给这颗树上所有节点附上一个权值。

每个节点的权值取值范围为 $[1,2^n-1]$，且要保证互不相同。

定义 $S(u)$ 为 $u$ 节点的所有儿子的集合，$val_u$ 表示节点 $u$ 的权值。

每个节点有一个能量值 $f(u)$，其可表示为：

$$f(u)= val_u + \sum_{v\in S(u) }f(v) $$

她想知道在保证 $ \sum_{i = 1}^{2^n-1} f(i)$ 取得最大值时，对于编号为 $p$ 的节点其 $f(p)$ 的最大值是多少。
询问的答案需要对 $10^9+7$ 取模。
## 输入格式

第一行包含两个正整数 $n,q$，分别表示满二叉树的层数和询问的次数。

接下来包含 $q$ 组询问，每组数据的格式如下：

第一行包含一个整数 $k$，表示接下来输入的 01 串的长度。

第二行包含一个的 01 串，为 $p$ 的二进制表示，保证 01 串的首位为 $1$，$p$ 表示所询问的节点编号。
## 输出格式

对于每次询问：输出一行包含一个整数，表示询问的答案对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
2 1
2
11
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
10 3
4
1001
8
10110110
3
111
```
### 样例输出 #2
```
84582
5362
163710
```
## 提示

**【数据范围】**

对于所有测试数据，保证：

- $1 \leq k\leq n \leq 10^{12}$；
- $1 \leq q\leq 1000$；
- $1 \leq k\leq 10^4$。

| 测试点 | $n\leq$ | 特殊性质 |
| :----------: | :----------: | :----------: |
| $1$ | $2$ | 无 |
| $2$ | $10$ | 无 |
| $3\sim5$ | $5000$ | 无 |
| $6$ | $10^5$ | 无 |
| $7$ | $10^8$ | A |
| $8 \sim 10$ | $10^{12}$ | 无 |

特殊性质 A：保证任意一组的询问都有 $k = 1$。



---

---
title: "花园"
layout: "post"
diff: 提高+/省选-
pid: P1357
tag: ['福建省历届夏令营', '矩阵乘法', '状压 DP']
---
# 花园
## 题目描述

小 L 有一座环形花园，沿花园的顺时针方向，他把各个花圃编号为 $1 \sim n$。花园 $1$ 和 $n$ 是相邻的。

他的环形花园每天都会换一个新花样，但他的花园都不外乎一个规则：任意相邻 $m$ 个花圃中都只有不超过 $k$ 个 C 形的花圃，其余花圃均为 P 形的花圃。

例如，若 $n=10$ , $m=5$ , $k=3$ ，则

- `CCPCPPPPCC` 是一种不符合规则的花圃。
- `CCPPPPCPCP` 是一种符合规则的花圃。

请帮小 L 求出符合规则的花园种数对 $10^9+7$ 取模的结果。
## 输入格式

只有一行三个整数，分别表示 $n, m, k$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
10 5 3

```
### 样例输出 #1
```
458
```
### 样例输入 #2
```
6 2 1

```
### 样例输出 #2
```
18
```
## 提示

#### 数据规模与约定

- 对于 $40\%$ 的数据，保证 $n \le 20$。
- 对于 $60\%$ 的数据，保证 $m=2$。
- 对于 $80\%$ 的数据，保证 $n \le 10^5$；
- 对于 $100\%$ 的数据，保证 $2 \leq n \le 10^{15}$，$2 \leq m \leq \min(n, 5)$，$1 \leq k \lt m$。


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
title: "[ZJOI2005] 沼泽鳄鱼"
layout: "post"
diff: 提高+/省选-
pid: P2579
tag: ['2005', '各省省选', '浙江', '矩阵乘法', '构造']
---
# [ZJOI2005] 沼泽鳄鱼
## 题目描述

潘塔纳尔沼泽地号称世界上最大的一块湿地，它地位于巴西中部马托格罗索州的南部地区。每当雨季来临，这里碧波荡漾、生机盎然，引来不少游客。

为了让游玩更有情趣，人们在池塘的中央建设了几座石墩和石桥，每座石桥连接着两座石墩，且每两座石墩之间至多只有一座石桥。这个景点造好之后一直没敢对外开放，原因是池塘里有不少危险的食人鱼。

豆豆先生酷爱冒险，他一听说这个消息，立马赶到了池塘，想做第一个在桥上旅游的人。虽说豆豆爱冒险，但也不敢拿自己的性命开玩笑，于是他开始了仔细的实地勘察，并得到了一些惊人的结论：食人鱼的行进路线有周期性，这个周期只可能是 $2$、$3$ 或者 $4$ 个单位时间。每个单位时间里，食人鱼可以从一个石墩游到另一个石墩。每到一个石墩，如果上面有人它就会实施攻击，否则继续它的周期运动。如果没有到石墩，它是不会攻击人的。

借助先进的仪器，豆豆很快就摸清了所有食人鱼的运动规律，他要开始设计自己的行动路线了。每个单位时间里，他只可以沿着石桥从一个石墩走到另一个石墩，而不可以停在某座石墩上不动，因为站着不动还会有其它危险。如果豆豆和某条食人鱼在同一时刻到达了某座石墩，就会遭到食人鱼的袭击，他当然不希望发生这样的事情。

现在豆豆已经选好了两座石墩 $\mathrm{Start}$ 和 $\mathrm{End}$，他想从 $\mathrm{Start}$ 出发，经过 $K$ 个单位时间后恰好站在石墩 $\mathrm{End}$ 上。假设石墩可以重复经过（包括 $\mathrm{Start}$ 和 $\mathrm{End}$），他想请你帮忙算算，这样的路线共有多少种（当然不能遭到食人鱼的攻击）。
## 输入格式

输入文件共 $M + 2 + \mathrm{NFish}$ 行。

第一行包含五个正整数 $N,M,\mathrm{Start},\mathrm{End},K$，分别表示石墩数目、石桥数目、$\mathrm{Start}$ 石墩和 $\mathrm{End}$ 石墩的编号和一条路线所需的单位时间。石墩用 $0$ 到 $N-1$ 的整数编号。

第 $2$ 到 $M + 1$ 行，给出石桥的相关信息。每行两个整数 $x$ 和 $y$，$0 \leq x, y \leq N-1$，表示这座石桥连接着编号为 $x$ 和 $y$ 的两座石墩。

第 $M + 2$ 行是一个整数 $\mathrm{NFish}$，表示食人鱼的数目。

第 $M + 3$ 到 $M + 2 + \mathrm{NFish}$ 行，每行给出一条食人鱼的相关信息。每行的第一个整数是 $T$，$T = 2,3$ 或 $4$，表示食人鱼的运动周期。接下来有 $T$ 个数，表示一个周期内食人鱼的行进路线。

- 如果 $T=2$，接下来有 $2$ 个数 $P_0$ 和 $P_1$，食人鱼从 $P_0$ 到 $P_1$，从 $P_1$ 到 $P_0,\ldots$；

- 如果 $T=3$，接下来有 $3$ 个数 $P_0,P_1$ 和 $P_2$，食人鱼从 $P_0$ 到 $P_1$，从 $P_1$ 到 $P_2$，从 $P_2$ 到 $P_0,\ldots$；

- 如果 $T=4$，接下来有 $4$ 个数 $P_0,P_1,P_2$ 和 $P_3$，食人鱼从 $P_0$ 到 $P_1$，从 $P_1$ 到 $P_2$，从 $P_2$ 到 $P_3$，从 $P_3$ 到 $P_0,\ldots$。

豆豆出发的时候所有食人鱼都在自己路线上的 $P_0$ 位置，请放心，这个位置不会是 $\mathrm{Start}$ 石墩。
## 输出格式

输出路线的种数，因为这个数可能很大，你只要输出该数除以 $10000$ 的余数就行了。
## 样例

### 样例输入 #1
```
6 8 1 5 3

0 2

2 1

1 0

0 5

5 1

1 4

4 3

3 5

1

3 0 5 1


```
### 样例输出 #1
```
2
```
## 提示

对于 $100 \%$ 的数据，$1 \leq N \leq 50$，$1 \leq K \leq 2 \times 10^9$，$1 \leq \mathrm{NFish} \leq 20$。


---

---
title: "[USACO07NOV] Cow Relays G"
layout: "post"
diff: 提高+/省选-
pid: P2886
tag: ['动态规划 DP', '2007', 'USACO', '最短路', '矩阵乘法']
---
# [USACO07NOV] Cow Relays G
## 题目描述

For their physical fitness program, N (2 ≤ N ≤ 1,000,000) cows have decided to run a relay race using the T (2 ≤ T ≤ 100) cow trails throughout the pasture.

Each trail connects two different intersections (1 ≤ I1i ≤ 1,000; 1 ≤ I2i ≤ 1,000), each of which is the termination for at least two trails. The cows know the lengthi of each trail (1 ≤ lengthi  ≤ 1,000), the two intersections the trail connects, and they know that no two intersections are directly connected by two different trails. The trails form a structure known mathematically as a graph.

To run the relay, the N cows position themselves at various intersections (some intersections might have more than one cow). They must position themselves properly so that they can hand off the baton cow-by-cow and end up at the proper finishing place.

Write a program to help position the cows. Find the shortest path that connects the starting intersection (S) and the ending intersection (E) and traverses exactly N cow trails.

给出一张无向连通图，求S到E经过k条边的最短路。

## 输入格式

\* Line 1: Four space-separated integers: N, T, S, and E

\* Lines 2..T+1: Line i+1 describes trail i with three space-separated integers: lengthi , I1i , and I2i

## 输出格式

\* Line 1: A single integer that is the shortest distance from intersection S to intersection E that traverses exactly N cow trails.

## 样例

### 样例输入 #1
```
2 6 6 4
11 4 6
4 4 8
8 4 9
6 6 8
2 6 9
3 8 9
```
### 样例输出 #1
```
10
```
## 题目翻译

给定一张 $T$ 条边的无向连通图，求从 $S$ 到 $E$ 经过 $N$ 条边的最短路长度。
### 输入格式
第一行四个正整数 $N,T,S,E$ ，意义如题面所示。

接下来 $T$ 行每行三个正整数 $w,u,v$ ，分别表示路径的长度，起点和终点。
### 输出格式
一行一个整数表示图中从 $S$ 到 $E$ 经过 $N$ 条边的最短路长度。
### 数据范围
对于所有的数据，保证 $1\le N\le 10^6$，$2\le T\le 100$。

所有的边保证 $1\le u,v\le 1000$，$1\le w\le 1000$。


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
title: "[SDOI2017] 序列计数"
layout: "post"
diff: 提高+/省选-
pid: P3702
tag: ['2017', '各省省选', '山东', '素数判断,质数,筛法', '容斥原理', '矩阵乘法', '快速傅里叶变换 FFT']
---
# [SDOI2017] 序列计数
## 题目描述

Alice 想要得到一个长度为 $n$ 的序列，序列中的数都是不超过 $m$ 的正整数，而且这 $n$ 个数的和是 $p$ 的倍数。

Alice 还希望，这 $n$ 个数中，至少有一个数是质数。

Alice 想知道，有多少个序列满足她的要求。
## 输入格式

一行三个数，$n,m,p$。

## 输出格式

一行一个数，满足 Alice 的要求的序列数量，答案对 $20170408$ 取模。
## 样例

### 样例输入 #1
```
3 5 3
```
### 样例输出 #1
```
33
```
## 提示

对 $20\%$ 的数据，$1\leq n,m\leq100$。


对 $50\%$ 的数据，$1\leq m \leq 100$。


对 $80\%$ 的数据，$1\leq m\leq 10^6$。


对 $100\%$ 的数据，$1\leq n \leq 10^9,1\leq m \leq 2\times 10^7,1\leq p\leq 100$。


---

---
title: "[SCOI2009] 迷路"
layout: "post"
diff: 提高+/省选-
pid: P4159
tag: ['2009', '四川', '各省省选', '矩阵加速', '矩阵乘法']
---
# [SCOI2009] 迷路
## 题目背景

windy 在有向图中迷路了。
## 题目描述

该有向图有 $n$ 个节点，节点从 $1$ 至 $n$ 编号，windy 从节点 $1$ 出发，他必须恰好在 $t$ 时刻到达节点 $n$。

现在给出该有向图，你能告诉 windy 总共有多少种不同的路径吗？ 

答案对 $2009$ 取模。

注意：windy 不能在某个节点逗留，且通过某有向边的时间严格为给定的时间。



## 输入格式

第一行包含两个整数，分别代表 $n$ 和 $t$。

第 $2$ 到第 $(n + 1)$ 行，每行一个长度为 $n$ 的字符串，第 $(i + 1)$ 行的第 $j$ 个字符 $c_{i, j}$ 是一个数字字符，若为 $0$，则代表节点 $i$ 到节点 $j$ 无边，否则代表节点 $i$ 到节点 $j$ 的边的长度为 $c_{i, j}$。
## 输出格式

输出一行一个整数代表答案对 $2009$ 取模的结果。
## 样例

### 样例输入 #1
```
2 2
11
00
```
### 样例输出 #1
```
1


```
### 样例输入 #2
```
5 30
12045
07105
47805
12024
12345

```
### 样例输出 #2
```
852
```
## 提示

#### 样例输入输出 1 解释

路径为 $1 \to 1 \to 2$。

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n \leq 5$，$t \leq 30$。
- 对于 $100\%$ 的数据，保证 $2 \leq n \leq 10$，$1 \leq t \leq 10^9$。


---

---
title: "[TJOI2017] 可乐（数据加强版）"
layout: "post"
diff: 提高+/省选-
pid: P5789
tag: ['2017', '各省省选', '矩阵乘法', '天津']
---
# [TJOI2017] 可乐（数据加强版）
## 题目背景

[原题](https://www.luogu.org/problem/P3758) 数据很弱，这个加强版卡掉了暴力的 DP 做法，并且补充了原题题面中缺少的 $\LaTeX$ 。
## 题目描述

加里敦星球的人们特别喜欢喝可乐。因而，他们的敌对星球研发出了一个可乐机器人，并且放在了加里敦星球的 $1$ 号城市上。这个可乐机器人有三种行为： 停在原地，去下一个相邻的城市，自爆。它每一秒都会随机触发一种行为。现在给加里敦星球城市图，在第 $0$ 秒时可乐机器人在 $1$ 号城市，问经过了 $t$ 秒，可乐机器人的行为方案数是多少？
## 输入格式

第一行输入两个正整数 $N,M$ ，$N$ 表示城市个数，$M$ 表示道路个数。  

接下来 $M$ 行输入 $u,v$ ，表示 $u,v$ 之间有一条双向道路。

最后输入时间 $t$ 。
## 输出格式

输出可乐机器人的行为方案数，答案可能很大，请输出对 $2017$ 取模后的结果。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
2
```
### 样例输出 #1
```
8
```
## 提示

【数据规模与约定】  

对于 $20\%$ 的数据， $n,m\leq 30$ ， $t\leq 1000$ ；  

对于 $50\%$ 的数据， $t\leq 10^6$；  

对于 $100\%$ 的数据， $n,m\leq 100$ ， $ t\leq 10^9$ .

【样例解释】

$1$ -> 爆炸

$1$ -> $1$ -> 爆炸

$1$ -> $2$ -> 爆炸

$1$ -> $1$ -> $1$

$1$ -> $1$ -> $2$

$1$ -> $2$ -> $1$

$1$ -> $2$ -> $2$

$1$ -> $2$ -> $3$


---

---
title: "「EZEC-6」跳一跳"
layout: "post"
diff: 提高+/省选-
pid: P7385
tag: ['动态规划 DP', '矩阵乘法']
---
# 「EZEC-6」跳一跳
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/zq0mhuy7.png)

小 A 最近迷上了 “跳一跳” 这个游戏。
## 题目描述

小 A 玩的 “跳一跳” 规则如下：

1. 设定一个计数器 $\text{cnt}$，将其初始值设置为 $2$。
2. 若跳上下一个格子但没跳到其中心，加 $1$ 分，将 $\text{cnt}$ 重置为 $2$。
3. 若跳上下一个格子且跳到了其中心，加 $\text{cnt}$ 分，将 $\text{cnt}$ 翻倍。
4. 若下一个格子为特殊格 $x_i$ 且跳到了其中心，额外加 $y_i$ 分。
5. 终止条件为没跳上下一个格子或者跳完了所有格子。

已知共有 $n$ 个格子，编号 $1$ 到 $n$（不包含起始格）。

小 A 跳上下一个格子但**没跳到**其中心的概率为 $a\%$，跳上下一个格子且**跳到了**其中心的概率为 $b\%$，剩余 $(100-a-b)\%$ 为没跳上下一个格子的概率。

求他的期望得分，并对 $10^9+7$ 取模。
## 输入格式

第一行三个整数 $n,a,b$。

第二行一个整数 $m$，表示共有 $m$ 个特殊格。

后 $m$ 行每行两个整数 $x,y$，表示每个特殊格的编号及其额外的加分，保证 $x$ 均不相同。
## 输出格式

一个整数表示期望得分。
## 样例

### 样例输入 #1
```
3 0 100
0
```
### 样例输出 #1
```
14
```
### 样例输入 #2
```
3 100 0
0
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
3 0 0
0
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
3 0 100
3
1 10
2 10
3 10
```
### 样例输出 #4
```
44
```
### 样例输入 #5
```
114 5 14
3
14 15
92 65
100 100
```
### 样例输出 #5
```
190259152
```
## 提示

**【样例 1 解释】**

小 A 每次都会跳上下一个格子且跳到其中心，期望得分为 $2+4+8=14$ 分。

**【样例 2 解释】**

小 A 每次都会跳上下一个格子但没跳到其中心，期望得分为 $1+1+1=3$ 分。

**【样例 3 解释】**

小 A 不可能跳上下一个格子，期望得分为 $0$ 分。

**【样例 4 解释】**

小 A 每次都会跳上下一个格子且跳到其中心，期望得分为 $2+10+4+10+8+10=44$ 分。

**【数据规模与约定】**

**本题采用捆绑测试。**

下表中斜杠代表无特殊限制。

| 子任务 | 分值 | $n$ | $a$ | $b$ | $m$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $1$ | $=1$ | $=50$ | $=50$ | / |
| $2$ | $9$ | $\le 20$ | / | / | $=0$ |
| $3$ | $10$ | $\le 20$ | / | / | / |
| $4$ | $10$ | $\le 10^5$ | / | / | $=0$ |
| $5$ | $20$ | $\le 10^5$ | / | / | / |
| $6$ | $5$ | / | $=0$ | $=100$ | / |
| $7$ | $5$ | / | $=100$ | $=0$ | / |
| $8$ | $15$ | / | / | / | $=0$ |
| $9$ | $25$ | / | / | / | / |

对于 $100\%$ 的数据，$1\le n\le 10^{18}$，$0\le a,b,a+b\le 100$，$0\le m\le \min(n,10^5)$，$1\le x\le n$，$1\le y\le 100$。


---

---
title: "[THUSC 2017] 大魔法师"
layout: "post"
diff: 提高+/省选-
pid: P7453
tag: ['2017', '线段树', 'O2优化', '矩阵乘法', 'THUSC']
---
# [THUSC 2017] 大魔法师
## 题目描述

大魔法师小 L 制作了 $n$ 个魔力水晶球，每个水晶球有水、火、土三个属性的能量值。小 L 把这 $n$ 个水晶球在地上从前向后排成一行，然后开始今天的魔法表演。

我们用 $A_i,B_i,C_i$ 分别表示从前向后第 $i$ 个水晶球（下标从 $1$ 开始）的水、火、土的能量值。

小 L 计划施展 $m$ 次魔法。每次，他会选择一个区间 $[l,r]$，然后施展以下 $3$ 大类、$7$ 种魔法之一：

1. 魔力激发：令区间里每个水晶球中**特定属性**的能量爆发，从而使另一个**特定属性**的能量增强。具体来说，有以下三种可能的表现形式：

	- 火元素激发水元素能量：令 $A_i=A_i+B_i$。
	- 土元素激发火元素能量：令 $B_i=B_i+C_i$。
	- 水元素激发土元素能量：令 $C_i=C_i+A_i$。
	
    **需要注意的是，增强一种属性的能量并不会改变另一种属性的能量，例如 $A_i=A_i+B_i$ 并不会使 $B_i$ 增加或减少。**

2. 魔力增强：小 L 挥舞法杖，消耗自身 $v$ 点法力值，来改变区间里每个水晶球的**特定属性**的能量。具体来说，有以下三种可能的表现形式：

	- 火元素能量定值增强：令 $A_i=A_i+v$。
	- 水元素能量翻倍增强：令 $B_i=B_i\times v$。
	- 土元素能量吸收融合：令 $C_i=v$。
3. 魔力释放：小 L 将区间里所有水晶球的能量聚集在一起，融合成一个新的水晶球，然后送给场外观众。生成的水晶球每种属性的能量值等于区间内所有水晶球对应能量值的代数和。**需要注意的是，魔力释放的过程不会真正改变区间内水晶球的能量。**

值得一提的是，小 L 制造和融合的水晶球的原材料都是定制版的 OI 工厂水晶，所以这些水晶球有一个能量阈值 $998244353$。当水晶球中某种属性的能量值大于等于这个阈值时，能量值会自动对阈值取模，从而避免水晶球爆炸。

小 W 为小 L（唯一的）观众，围观了整个表演，并且收到了小 L 在表演中融合的每个水晶球。小 W 想知道，这些水晶球蕴涵的三种属性的能量值分别是多少。
## 输入格式

从标准输入读入数据。

我们将上述的 $7$ 种魔法，从上到下依次标号为 $1\sim7$。

输入的第一行包含一个整数 $n$（$1\le n\le 2.5\times 10^5$），表示水晶球个数。

接下来 $n$ 行，每行空格隔开的 $3$ 个整数，其中第 $i$ 行的三个数依次表示 $A_i,B_i,C_i$。

接下来一行包含一个整数 $m$（$1\le m\le2.5\times 10^5$），表示施展魔法的次数。

接下来 $m$ 行，每行 $3$ 或 $4$ 个数，格式为 `opt l r (v)`。其中 `opt` 表示魔法的编号，$l,r$ 表示施展魔法的区间（保证有 $l\le r$）。特别地，如果施展 $4\sim6$ 号魔法（魔力增强），则还有一个整数 $v$，表示小 L 消耗的法力值。
## 输出格式

输出到标准输出。

对每个 $7$ 号魔法（魔力释放），输出一行、空格隔开的 $3$ 个整数 `a b c`，分别表示此次融合得到的水晶球的水、火、土元素能量值。
## 样例

### 样例输入 #1
```
2
2 3 3
6 6 6
4
7 1 2
1 1 2
4 1 2 3
7 1 2
```
### 样例输出 #1
```
8 9 9
23 9 9
```
## 提示

$100\%$ 的数据，$n,m\le2.5\times 10^5,0\le A_i,B_i,C_i,v<998244353$

1. $10\%$ 的数据，$n\times m\le10^7$。
1. 另外 $10\%$ 的数据，每次魔法的区间均为 $[1,n]$。
1. 另外 $10\%$ 的数据，每次非询问魔法的影响区间均为 $[1,n]$，所有修改在询问之前。
1. 另外 $10\%$ 的数据，$\operatorname{opt}\in\{4,5,6,7\}$。
1. 另外 $15\%$ 的数据，$\operatorname{opt}\in\{1,2,7\}$。
  1. 另外 $15\%$ 的数据，$\operatorname{opt}\in\{1,2,3,5,7\}$。
1. 另外 $15\%$ 的数据，$n,m\le 10^5$。
1. 其他数据，无特殊约定。
#### 样例解释
以下展示每次施展魔法后，两个水晶球内的能量：
```
(2, 3, 3) (6, 6, 6)
(5, 3, 3) (12, 6, 6)
(8, 3, 3) (15, 6, 6)
(8, 3, 3) (15, 6, 6)
```


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
title: "[USACO22FEB] Cow Camp G"
layout: "post"
diff: 提高+/省选-
pid: P8190
tag: ['动态规划 DP', 'USACO', '2022', 'Special Judge', '期望', '矩阵乘法']
---
# [USACO22FEB] Cow Camp G
## 题目描述

To qualify for cow camp, Bessie needs to earn a good score on the last problem of the USACOW Open contest. This problem has $T$ distinct test cases $(2≤T≤10^3)$ weighted equally, with the first test case being the sample case. Her final score will equal the number of test cases that her last submission passes.
Unfortunately, Bessie is way too tired to think about the problem, but since the answer to each test case is either "yes" or "no," she has a plan! Precisely, she decides to repeatedly submit the following nondeterministic solution:
```
if input == sample_input:
  print sample_output
else:
  print "yes" or "no" each with probability 1/2, independently for each test case
```
Note that for all test cases besides the sample, this program may produce a different output when resubmitted, so the number of test cases that it passes will vary.

Bessie knows that she cannot submit more than $K$ $(1≤K≤10^9)$ times in total because then she will certainly be disqualified. What is the maximum possible expected value of Bessie's final score, assuming that she follows the optimal strategy?
## 输入格式

The only line of input contains two space-separated integers $T$ and $K$.
## 输出格式

The answer as a decimal that differs by at most $10^{−6}$ absolute or relative error from the actual answer.
## 样例

### 样例输入 #1
```
2 3
```
### 样例输出 #1
```
1.875
```
### 样例输入 #2
```
4 2
```
### 样例输出 #2
```
2.8750000000000000000
```
## 提示

【样例解释 1】

In this example, Bessie should keep resubmitting until she has reached 3 submissions or she receives full credit. Bessie will receive full credit with probability $\frac 78$ and half credit with probability $\frac 18$, so the expected value of Bessie's final score under this strategy is $\frac 78\cdot 2+\frac 18\cdot 1=\frac {15}{8}=1.875$. As we see from this formula, the expected value of Bessie's score can be calculated by taking the sum over $x$ of $p(x)\cdot x$, where $p(x)$ is the probability of receiving a score of $x$.

【样例解释 2】

Here, Bessie should only submit twice if she passes fewer than 3 test cases on her first try.

【数据范围】

- Test cases 3-6 satisfy $T≤25$ and $K≤100$.
- Test cases 7-9 satisfy $K≤10^6$.
- Test cases 10-17 satisfy no additional constraints.
## 题目翻译

### 题目描述

为了获得参加奶牛训练营的资格，Bessie 需要在 USACOW 公开赛的最后一题中取得好成绩。这道题有 $T$ 个独立的测试用例（$2 \leq T \leq 10^3$），权重相同，其中第一个测试用例是样例。她的最终得分将等于她最后一次提交通过的测试用例数量。

不幸的是，Bessie 太累了，无法思考这个问题，但由于每个测试用例的答案要么是“yes”，要么是“no”，她想到了一个计划！具体来说，她决定反复提交以下非确定性解决方案：

```
if input == sample_input:
    print sample_output
else:
    print "yes" or "no" each with probability 1/2, independently for each test case
```

注意，对于除样例之外的所有测试用例，这个程序在重新提交时可能会产生不同的输出，因此它通过的测试用例数量会有所不同。

Bessie 知道她总共不能提交超过 $K$ 次（$1 \leq K \leq 10^9$），否则她肯定会被取消资格。假设 Bessie 遵循最优策略，她的最终得分的最大可能期望值是多少？

### 输入格式

输入只有一行，包含两个用空格分隔的整数 $T$ 和 $K$。

### 输出格式

输出一个十进制数，表示答案，与实际答案的绝对误差或相对误差不超过 $10^{-6}$。

### 样例解释 1

在这个例子中，Bessie 应该继续重新提交，直到她提交了 3 次或获得了满分。Bessie 获得满分的概率是 $\frac{7}{8}$，获得一半分数的概率是 $\frac{1}{8}$，因此在这种策略下，Bessie 的最终得分的期望值是 $\frac{7}{8} \cdot 2 + \frac{1}{8} \cdot 1 = \frac{15}{8} = 1.875$。从这个公式可以看出，Bessie 得分的期望值可以通过对所有可能的得分 $x$ 求和 $p(x) \cdot x$ 来计算，其中 $p(x)$ 是获得得分 $x$ 的概率。

### 样例解释 2

在这里，Bessie 应该只在第一次尝试通过少于 3 个测试用例时才提交第二次。

### 数据范围

- 测试用例 3-6 满足 $T \leq 25$ 且 $K \leq 100$。
- 测试用例 7-9 满足 $K \leq 10^6$。
- 测试用例 10-17 没有额外限制。


---

---
title: "[COCI 2009/2010 #6] GREMLINI"
layout: "post"
diff: 提高+/省选-
pid: P8408
tag: ['2009', '矩阵乘法', 'COCI（克罗地亚）']
---
# [COCI 2009/2010 #6] GREMLINI
## 题目描述

有 $n$ 种小妖精，我们给这 $n$ 类小妖分别编号为 $1,\dots,n$。

$t$ 年前，一次事故造出了 $n$ 只小妖（视为刚出生的，而非成熟的），这些小妖的种类互不相同。

第 $i$ 种小妖出生后需要 $y_i$ 年成熟，成熟后会立即产下 $k_i$ 个蛋（小妖是无性繁殖的生物）然后死亡。将它的蛋编号为 $1.\dots,k$，其中，第 $j$ 个蛋需要 $h_{i,j}$ 年孵化，孵出的小妖的类型为 $g _ {i, j}$。

请问，现在和祖先关系最远的小妖到了多少代，不考虑暂未孵出的。假设祖先是 $1$ 代，其子辈为第 $2$ 代，孙辈为第 $3$ 代，以此类推。
## 输入格式

第一行：$n,t$。
接下来 $3n$ 行，每三行为一组。

每组的第一行：$k_i,y_i$。
每组的第二行：$g_{ i,1},\ldots,g_{i,k_i}$。
每组的第三行：$h_{ i,1},\ldots,h_{i,k_i}$。
## 输出格式

一行，一个整数，表示现在和祖先关系最远的小妖到了多少代。
## 样例

### 样例输入 #1
```
1 42
1 10
1
5
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
2 42
1 10
1
5
1 5
1
5
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
3 8
4 5
1 2 3 2
1 2 1 3
1 1
3
1
2 1
1 2
2 1
```
### 样例输出 #3
```
4
```
## 提示

**【样例 #2 解释】**

事故发生 $10$ 年后，最开始的那只小妖（$1$ 代）产下了一个蛋，然后死亡。事故发生 $15$ 年后，蛋孵化出了新的一只小妖（$2$ 代）。事故发生 $25$ 年后，$2$ 代小妖产下了一个蛋，然后死亡。事故发生 $30$ 年后，蛋孵化出了新的一只小妖（$3$ 代）。事故发生 $40$ 年后，$3$ 代小妖产下了一个蛋，然后死亡。事故发生 $42$ 年后，这个蛋仍未孵化，因此不计。

**【数据范围】**

$1 \le n \le 100,1 \le t \le 10^{15},1 \le k_i, y_i, h_{i,j} \le 1000,1 \le g_{i,j} \le n$。

本题分值按 COCI 原题设置，满分 $130$。


---

---
title: "[ICPC 2021 Nanjing R] Paimon Segment Tree"
layout: "post"
diff: 提高+/省选-
pid: P9844
tag: ['线段树', '2021', 'Special Judge', 'O2优化', '矩阵乘法', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Paimon Segment Tree
## 题目描述

Paimon just learns the persistent segment tree and decides to practice immediately. Therefore, Lumine gives her an easy problem to start:

Given a sequence $a_1, a_2, \cdots, a_n$ of length $n$, Lumine will apply $m$ modifications to the sequence. In the $i$-th modification, indicated by three integers $l_i$, $r_i$ ($1 \le l_i \le r_i \le n$) and $x_i$, Lumine will change $a_k$ to $(a_k + x_i)$ for all $l_i \le k \le r_i$.

Let $a_{i, t}$ be the value of $a_i$ just after the $t$-th operation. This way we can keep track of all historial versions of $a_i$. Note that $a_{i,t}$ might be the same as $a_{i,t-1}$ if it hasn't been modified in the $t$-th modification. For completeness we also define $a_{i, 0}$ as the initial value of $a_i$.

After all modifications have been applied, Lumine will give Paimon $q$ queries about the sum of squares among the historical values. The $k$-th query is indicated by four integers $l_k$, $r_k$, $x_k$ and $y_k$ and requires Paimon to calculate

$$\sum\limits_{i=l_k}^{r_k}\sum\limits_{j=x_k}^{y_k} a_{i, j}^2$$

Please help Paimon compute the result for all queries. As the answer might be very large, please output the answer modulo $10^9 + 7$.
## 输入格式

There is only one test case in each test file.

The first line of the input contains three integers $n$, $m$ and $q$ ($1 \le n, m, q \le 5 \times 10^4$) indicating the length of the sequence, the number of modifications and the number of queries.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($|a_i| < 10^9 + 7$) indicating the initial sequence.

For the following $m$ lines, the $i$-th line contains three integers $l_i$, $r_i$ and $x_i$ ($1 \le l_i \le r_i \le n$, $|x_i| < 10^9 + 7$) indicating the $i$-th modification.

For the following $q$ lines, the $i$-th line contains four integers $l_i$, $r_i$, $x_i$ and $y_i$ ($1 \le l_i \le r_i \le n$, $0 \le x_i \le y_i \le m$) indicating the $i$-th query.
## 输出格式

For each query output one line containing one integer indicating the answer modulo $10^9 + 7$.
## 样例

### 样例输入 #1
```
3 1 1
8 1 6
2 3 2
2 2 0 0

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
4 3 3
2 3 2 2
1 1 6
1 3 3
1 3 6
2 2 2 3
1 4 1 3
4 4 2 3

```
### 样例输出 #2
```
180
825
8

```
## 题目翻译

## 题目描述

派蒙刚刚学习了可持久化线段树，她想马上练习一下。因此，荧决定给她出一道简单的问题：

给定数列$a_1, a_2, \cdots, a_n$，并进行$m$次操作。操作包含3个参数$l_i$, $r_i$ ($1 \le l_i \le r_i \le n$) 和 $x_i$，代表对该序列第$l_i$到第$r_i$个元素加上$x_i$。

记$a_{i, t}$为$t$次操作后$a_i$的值。注意若$a_i$未被修改，则$a_{i,t}$的值与$a_{i,t-1}$相同。定义$a_{i, 0}$是$a_i$的初始值。


完成所有操作后，荧进行$q$次询问，询问包含4个整数$l_k$, $r_k$, $x_k$ and $y_k$，派蒙需要回答

$$\sum\limits_{i=l_k}^{r_k}\sum\limits_{j=x_k}^{y_k} a_{i, j}^2$$

请将答案对$10^9 + 7$取模后输出。

## 输入格式
每个测试点含一组测试数据。

第一行3个整数$n$,$m$,$q$ ($1 \le n, m, q \le 5 \times 10^4$) 分别表示数列的长度，操作的次数和询问的次数。

第2行$n$个整数 $a_1, a_2, \cdots, a_n$ ($|a_i| < 10^9 + 7$) ，表示原始数列。

接下来$m$行每行3个整数 $l_i$, $r_i$ $x_i$ ($1 \le l_i \le r_i \le n$, $|x_i| < 10^9 + 7$)，表示区间加操作。

接下来$q$行每行包含四个整数 $l_i$, $r_i$, $x_i$  $y_i$ ($1 \le l_i \le r_i \le n$, $0 \le x_i \le y_i \le m$)，表示询问。

## 输出格式

对每个询问单起一行输出答案模$10^9 + 7$的结果。


---

