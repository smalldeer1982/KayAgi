---
title: "龙逐千灯幻"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10181
tag: ['线段树', '并查集', '洛谷原创', 'O2优化', '凸完全单调性（wqs 二分）', '洛谷月赛', '根号分治', '单调栈']
---
# 龙逐千灯幻
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/6w2vttoo.png)

龙年到，帆帆也举起了自己的彩龙灯，他自己也要变成大彩龙啦！
## 题目描述

帆帆一共有 $n$ 盏龙灯，第 $i$ 盏的颜色是 $a_i$。

帆帆认为一段区间 $[l,r]$ 的美观度 $f(l,r)$ 为 $a_l\cdots a_r$ 中的不同颜色个数。

帆帆准备带着自己的龙灯去玩，他一共计划去玩 $m$ 天，第 $i$ 天，他会带着自己的 $1\cdots x_i$ 号龙灯，但是他发现如果把很多龙灯装在一起，那么别人只会注意到其中有多少种不同的颜色。

因此帆帆准备把这 $x_i$ 个龙灯按照编号顺序分成恰好 $k_i$ 个区间，满足每盏灯恰好在一个区间内。

那么帆帆这次出行的美观度就为所有区间的美观度的和。

请你帮帮帆帆最大化每一次出行的美观度。


## 输入格式

第一行五个整数 $n,m,id,seed,limx$，分别代表序列长度，询问次数，以及 $\texttt{subtask}$ 编号（样例中的 $id=0$），随机数种子，以及一个和询问有关的参数 $limx$。

因为本题输入量过大，因此采用如下方式生成询问：

我们使用下面的代码生成一个伪随机数列：

```cpp
uint64_t PRG_state;
uint64_t get_number()
{
    PRG_state ^= PRG_state << 13;
    PRG_state ^= PRG_state >> 7;
    PRG_state ^= PRG_state << 17;
    return PRG_state;
}
int readW(int l,int r)
{
	return get_number()%(r-l+1)+l;
}
```

一开始 `PRG_state=seed`，你每次调用 `readW(l,r)` 会返回一个 $[l,r]$ 内的随机数。

第二行 $n$ 个整数，第 $i$ 个整数代表 $a_i$。

设 $x_i,k_i,c_i$ 表示第 $i$ 组询问需要的参数 $x,k,c$，其中 $c$ 的作用见输出格式，那么所有询问的参数可以用以下程序生成：

```cpp
for (int i = 1; i <= m; ++i) {
	x[i] = readW(limx, n);
	k[i] = readW(1, x[i]);
	c[i] = readW(0, 1e7);
}
```

注：**请不要在运行上述代码段获得各组询问的参数之前调用 `readW()` 函数，否则无法获得正确的询问信息。** 本题不需要利用该伪随机数生成器的特殊性质，你只需将  `get_number()` 视为一个每次调用独立且均匀随机地生成一个无符号 $64$ 位整数的生成器即可。本题也不需要优化伪随机数生成器的内部实现。
## 输出格式

为了减少输出量，我们使用如下方式进行信息压缩：

如果第 $i$ 组询问的答案为 $ans_i$，其生成参数为 $c_i$，那么你需要输出：

$$\bigoplus\limits_{i=1}^m(ans_i\times c_i)$$

其中 $\bigoplus $ 为异或运算，该值显然一定位于 `long long` 能表示的整数范围内。
## 样例

### 样例输入 #1
```
5 5 0 956144375 1
2 4 1 5 2 

```
### 样例输出 #1
```
21971409
```
### 样例输入 #2
```
10 10 0 478178732 1
2 2 1 1 2 1 2 1 2 1 

```
### 样例输出 #2
```
2834792
```
## 提示

### 【样例1解释】

询问分别是：

```
3 1 6121576
5 3 3089509
1 1 4506170
3 1 2821007
1 1 7941511
```

答案分别是:

```
3
5
1
3
1
```

对于第一组询问，要分成一个区间，那么就是 $[1,3]$，美观度就是 $f(1,3)=3$ 。

对于第二组询问，最优的方案是分成 $[1,3],[4,4],[5,5]$，美观度是 $f(1,3)+f(4,4)+f(5,5)=5$

后三个询问同理。

### 【样例2解释】

询问分别是：

```
8 4 6858024
3 2 236530
2 2 8140891
5 3 4562139
8 7 4749403
7 4 4319971
5 1 5063575
3 1 7343109
6 2 1566851
3 1 7959241
```

询问答案分别是：

```
7
3
2
5
8
7
2
2
4
2
```

### 【数据范围】

本题采用捆绑测试。

- 子任务一（$10$ 分）：$1 \leq n\leq 500$。
- 子任务二（$15$ 分）：$1\leq n\leq 3000$。
- 子任务三（$15$ 分）：$m=1$。
- 子任务四（$20$ 分）：$1\le a_i\le 30$。
- 子任务五（$20$ 分）：$1\leq n\leq 4\times 10^4$。
- 子任务六（$20$ 分）：无特殊限制。


对于 $100\%$ 的数据，$1 \leq n\leq 10^5$，$1\leq  m\leq 10^6$，$0\leq seed\leq 10^9$，$1\leq limx\leq n$，$1\leq a_i\leq n$。


---

---
title: "「RiOI-03」A Journey to the Moonlight（加强版）"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10286
tag: ['洛谷原创', '二分图', '生成函数', '快速数论变换 NTT']
---
# 「RiOI-03」A Journey to the Moonlight（加强版）
## 题目背景

本题相较于 [P9919](/problem/P9919) 扩大了数据范围。
## 题目描述

对于一个右部点为 $m$ 个的二分图 $G$，定义它的权值 $w(G)$ 如下：

- 选择一种匹配方案，标记第一个已匹配的右部点。如果不存在这样的点，那么标记第一个未匹配的右部点。
- 每次随机选择一个 $1,2,\cdots,m$ 的排列，当未匹配的右部点与被标记的点 **按标号顺序作为一个子段出现在排列中时** 停止操作。
- $w(G)$ 为在所有匹配方案中操作次数期望的 **最小值**。

将这个二分图 $G$ 定义为 **$k$ 合法** 的，当且仅当：

- 所有左部点的度数在 $k\sim \color{red}2$ 之间。
- 没有任意两个左部点，与其相邻的点组成的集合相同。

定义 $f(k,x)$ 为所有右部点 $x$ 个，左部点不进行区分的 $k$ 合法二分图 $G$ 的 $w(G)$ 之和。

给定 $n,k,a_{0\sim n}$，求 $\sum\limits^n_ia_if(k,i) \bmod998244353$。
## 输入格式

一行两个正整数，分别表示 $n,k$。

第二行 $n+1$ 个非负整数，分别表示 $a_{0\sim n}$。
## 输出格式

一行一个非负整数，表示答案。
## 样例

### 样例输入 #1
```
2 1
1 1 1
```
### 样例输出 #1
```
15
```
### 样例输入 #2
```
3 2
1 1 1 1
```
### 样例输出 #2
```
40
```
### 样例输入 #3
```
12 1
1 1 4 5 1 4 1 9 1 9 8 1 0
```
### 样例输出 #3
```
721168027
```
## 提示

约定一个左部点连接了编号为 $x,y$ 的右部点表示为 $(x,y)$。

#### 【样例 1 解释】

对于 $n=0,1$，答案显然为 $1,2$。

对于 $n=2$，可能的二分图为（用每个左部点的邻接点组成的元组表示）：

$()$

$(1),(2),(1,2)$

$\{(1),(2)\},\{(1,2),(2)\},\{(1,2),(1)\},\{(1,2),(1),(2)\}$

期望相同的二分图被分为一组。答案为 $\dfrac21+\dfrac21\times3+\dfrac22\times4=12$，输出 $1\times1+1\times2+1\times12=15$。

#### 【样例 2 解释】

对于 $n=0,1,2$，答案为 $1,1,4$。

对于 $n=3$，可能的二分图为（用每个左部点的邻接点组成的元组表示）：

$()$

$(1,2),(1,3),(2,3)$

$\{(1,2),(1,3)\},\{(1,2),(2,3)\},\{(1,3),(2,3)\}$

$\{(1,2),(2,3),(1,3)\}$

答案为 $\dfrac61+\dfrac61\times3+\dfrac62\times3+\dfrac66=34$。

#### 【数据范围】

对于 $100\%$ 的数据，$0\le n\le10^5$，$1\le k\le2$，$0\le a_i<998244353$。


---

---
title: "[COTS 2019] 挑战 Izazov"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11224
tag: ['2019', '网络流', 'Special Judge', '二分图', 'COCI（克罗地亚）']
---
# [COTS 2019] 挑战 Izazov
## 题目背景


译自 [Izborne Pripreme 2019 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2019/) D2T1。$\texttt{15s,0.5G}$。
## 题目描述


给定 $N\times M$ 的黑白矩阵。用尽可能少数量的矩形覆盖住所有黑色格子，要求：
- 每个黑色格子**恰好被一个**矩形覆盖；
- 任意两个矩形不重叠；
- 矩形不覆盖白色格子。

并输出方案。
## 输入格式

第一行，两个正整数 $N,M$。

接下来一个 $N\times M$ 的矩阵，每个位置是 $\texttt{C}$ 或者 $\texttt{B}$。其中，$\texttt{C}$ 代表黑色（克罗地亚语「crno」），$\texttt{B}$ 代表白色（克罗地亚语「bijelo」）。

## 输出格式


输出 $N$ 行，每行 $M$ 个数，表示你的方案：
- 未被覆盖的区域，用 $0$ 表示；
- 否则，设使用了 $K$ 个矩形，将矩形用 $1\sim K$ 标号后，对应位置用覆盖它的矩形编号表示。

每一行相邻的数要用空格隔开。
## 样例

### 样例输入 #1
```
4 5
CCBCB
CCBBB
CCCBB
CCCBB
```
### 样例输出 #1
```
1 1 0 2 0
1 1 0 0 0
3 3 3 0 0
3 3 3 0 0
```
### 样例输入 #2
```
7 5
CCCBB
BCBBB
BCCCB
BCCCB
CCCCC
BBBBB
BCCCB
```
### 样例输出 #2
```
1 1 1 0 0
0 2 0 0 0
0 3 3 3 0
0 3 3 3 0
4 4 4 4 4
0 0 0 0 0
0 5 5 5 0
```
### 样例输入 #3
```
5 11
BBCCCBCCCBC
BCCBCBBCCCC
CCCCBCCCCCC
BCBCCCBCCCB
CCCCBCBBCCB
```
### 样例输出 #3
```
0 0 1 1 1 0 2 2 2 0 3
0 4 4 0 5 0 0 6 6 6 3
7 7 7 7 0 8 8 6 6 6 3
0 9 0 10 10 10 0 6 6 6 0
11 11 11 11 0 12 0 0 13 13 0
```
## 提示



对于 $100\%$ 的数据，保证 $1\le N,M\le 500$。


| 测试点编号 | $N,M\le $    | 得分 |  
| :--: | :--: |:--: |  
| $ 1\sim 5 $    | $ 26 $ |   $ 25 $   |  
| $ 6\sim 10 $    | $ 100 $ |  $ 25 $   |  
| $ 11\sim 15 $    | $ 250 $ | $ 25 $   |  
| $ 16\sim 20 $    | $ 500 $ |$ 25 $   |  

【计分方式】

如果你输出的是最优解，得满分。

否则，设最优解用的矩形数量为 $A$，你的解用的矩形数量为 $B$，该测试点得分为 $0.75\cdot (A/B)^{10}\cdot 5$ 分。 


---

---
title: "[RMI 2024] 选区间 / Choose Interval"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11880
tag: ['贪心', '二分', '堆', '2024', 'Special Judge', 'RMI（罗马尼亚）']
---
# [RMI 2024] 选区间 / Choose Interval
## 题目描述

有一个**无限长**的数列 $A$，初始时 $A$ 中元素全为 $0$。

给定 $n$ 个区间 $[l_i,r_i]$，对于 $i=1,2,\ldots,n$，你需要执行以下的**一种**操作恰好一次：

1. $\forall j\in [l_i,r_i]$，令 $A_j\gets A_j+1$。
1. $\forall j \in \mathbb Z \land j\not\in [l_i,r_i]$，令 $A_j\gets A_j+1$。

构造一组方案，使得操作完后数列中最大值最小。



## 输入格式

第一行，一个正整数 $n$。

接下来 $n$ 行，第 $i$ 行两个正整数 $l_i,r_i$。
## 输出格式

第一行，一个正整数，表示最小化的最大值。

第二行输出一个长度为 $n$ 的 $\texttt{01}$ 串 $s$：

- $s_i=\texttt{0}$，表示对于 $i$ 选择操作 $\textcolor{red}{2}$；
- $s_i=\texttt{1}$，表示对于 $i$ 选择操作 $\textcolor{red}{1}$。
## 样例

### 样例输入 #1
```
5
10 10
6 6
1 7
2 5
2 7
```
### 样例输出 #1
```
2
11110
```
## 提示


#### 样例解释

另一种合法的输出为

```plain
2
11011
```

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le n\le 2\times 10^5$；
- $1\le l_i\le r_i\le 2n$。


| 子任务编号 | $n\le$ | 得分 |
| :-: | :-: | :-: |
| $1$ | $20$ | $7$ |
| $2$ | $150$ | $24$ |
| $3$ | $10^3$ | $21$ |
| $4$ | $5\times 10^4$ | $34$ |
| $5$ | $2\times 10^5$ | $14$ |




---

---
title: "[集训队互测 2024] 人间应又雪"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12483
tag: ['动态规划 DP', '二分', '集训队互测', '树状数组', '2024', '动态规划优化']
---
# [集训队互测 2024] 人间应又雪
## 题目描述

长度为 $n$ 的街道被积雪覆盖，将街道划分为 $n$ 段，第 $i$ 段的积雪量为 $a_i$，保证 $0\le a_i\le m$ 且 $a_i$ 为整数。

天依与言和要来清理积雪，每次清理有 $2$ 种选择。

+ 天依从位置 $1$ 走到位置 $x$，将积雪清理掉 $c$，再走回位置 $1$，同时，因为在雪地上移动，位置 $1\sim x$ 的积雪量减少 $1$，即 $\forall i\in[1,x-1],a_i:=a_i-1,a_x:=a_x-c-1$。
+ 言和从位置 $n$ 走到位置 $x$，将积雪清理掉 $c$，再走回位置 $n$，同时，因为在雪地上移动，位置 $x\sim n$ 的积雪量减少 $1$，即 $\forall i\in[x+1,n],a_i:=a_i-1,a_x:=a_x-c-1$。。

任意时刻，积雪量对 $0$ 取 $\max$。

天依与言和想知道，最少进行多少次清理后（**即最小化两人清理次数总和**），能将所有积雪清除，即 $\forall i\in [1,n],a_i=0$。
## 输入格式

**本题有多组测试数据。**

首先输入一行两个数 $T,tid$，$T$ 表示数据组数，$tid$ 表示子任务编号（样例的子任务编号为 $0$）。

对于每组数据：

第一行三个整数 $n,m,c$。

第二行 $n$ 个整数 $a_{1\sim n}$。
## 输出格式

对于每组数据，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
1 0
5 5 1
1 3 2 3 1
```
### 样例输出 #1
```
2
```
## 提示

### 样例解释 1

天依走到位置 $4$ 清理，积雪量变为 $[0,2,1,1,1]$。

言和走到位置 $2$ 清理，积雪量变为 $[0,0,0,0,0]$。

共 $2$ 次清理。

### 样例解释 2

见附加文件中的 `snow.in` 与 `snow.ans`。  
这个样例中有 $100$ 组 $n=10,m=10$ 的数据。

### 数据范围

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le n,m\le 5\times 10^5$，$\sum n,\sum m\le 10^6$，$0\le a_i\le m$，$0\le c\le 5\times 10^5$。

| 子任务编号 |        $n$         |        $m$         |            特殊限制             | 分值 | 子任务依赖 |
| :--------: | :----------------: | :----------------: | :-----------------------------: | :--: | :--------: |
|    $1$     | $\le 5\times 10^5$ | $\le 5\times 10^5$ |              $c=0$              | $2$  |            |
|    $2$     | $\le 5\times 10^5$ |      $\le 2$       |               无                | $3$  |            |
|    $3$     |      $\le 5$       |      $\le 5$       |            $T\le 10$            | $5$  |            |
|    $4$     |      $\le 50$      |      $\le 50$      |     $\sum n,\sum m\le 200$      | $10$ |    $3$     |
|    $5$     |     $\le 300$      |     $\le 300$      |     $\sum n,\sum m\le 600$      | $10$ |    $4$     |
|    $6$     |     $\le 2000$     |     $\le 2000$     |     $\sum n,\sum m\le 4000$     | $10$ |    $5$     |
|    $7$     | $\le 5\times 10^4$ | $\le 5\times 10^4$ | $c\le 20,\sum n,\sum m\le 10^5$ | $20$ |            |
|    $8$     | $\le 5\times 10^4$ | $\le 5\times 10^4$ |     $\sum n,\sum m\le 10^5$     | $15$ |   $6,7$    |
|    $9$     | $\le 5\times 10^5$ | $\le 5\times 10^5$ |            $c\le 20$            | $10$ |   $1,7$    |
|    $10$    | $\le 5\times 10^5$ | $\le 5\times 10^5$ |               无                | $15$ |  $2,8,9$   |


---

---
title: "[GCJ 2015 Finals] Taking Over The World"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13236
tag: ['图论', '2015', '二分', '网络流', '图论建模', 'Google Code Jam']
---
# [GCJ 2015 Finals] Taking Over The World
## 题目描述

You and your friend Pinky have a plan to take over the world. But first you need to disable a certain secret weapon.

It is hidden inside a twisted maze of passages (a graph) with one entrance. Pinky is going to be at the vertex with the secret weapon, disabling it. Meanwhile, a security team at the graph entrance will be alerted, and will run through the graph to try to get to Pinky in time to stop him. You are going to be slowing down the security team to give Pinky as much time as possible. It takes one unit of time to traverse any edge of the graph, but you can additionally "obstruct" up to $\mathbf{K}$ vertices. It takes one additional unit of time to traverse an obstructed vertex. You will choose to obstruct a set of vertices that slows down the security team by as much as possible.

If the security team will be starting at the graph entrance and is trying to get to the secret weapon vertex, how much time will it take them to get there? Note that you have to commit all your obstructions before the security guards start their journey, and the security guards will know which vertices you have obstructed and will choose an optimal path based on that information.

Obstructing the secret weapon vertex is not useful because that will not delay the guards any further after they have already caught Pinky. Obstructing the entrance, on the other hand, is obviously a good idea.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each one starts with a line containing $\mathbf{N}, \mathbf{M}$, and $\mathbf{K}$. The next $\mathbf{M}$ lines each contain a pair of vertices connected by an edge. Vertices are numbered from 0 (the entrance) to $\mathbf{N}-1$ (the secret weapon room). The first vertex will always be smaller than the second vertex, and no pair of vertices will appear more than once in the same test case. Edges are bi-directional -- the guards can travel along any edge in either direction.

## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the time it will take the security guards to get from the entrance to the secret weapon room.
## 样例

### 样例输入 #1
```
5
3 2 1
0 1
1 2
3 2 2
0 1
1 2
3 2 3
0 1
1 2
4 4 2
0 1
0 2
1 3
2 3
7 11 3
0 1
0 2
0 3
1 4
1 5
2 4
2 5
3 4
3 5
4 6
5 6
```
### 样例输出 #1
```
Case #1: 3
Case #2: 4
Case #3: 4
Case #4: 3
Case #5: 5
```
## 提示

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{N} \leq 100$.
- $1 \leq \mathbf{M} \leq \mathbf{N} \times (\mathbf{N} - 1) / 2$.
- $1 \leq \mathbf{K} \leq \mathbf{N}$.
- There will always be a path from room 0 to room $\mathbf{N} - 1$.

**Small dataset(7 Pts)**

- Time limit: ~~240~~ 5 seconds.
- It will not be possible to delay the guards by more than 2 time units, compared to the shortest unobstructed path length (using the given $\mathbf{K}$).

**Large dataset(29 Pts)**

- Time limit: ~~480~~ 10 seconds.
- No extra restrictions.


---

---
title: "[GCJ 2014 Finals] Allergy Testing"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13268
tag: ['动态规划 DP', '2014', '二分', '矩阵加速', '组合数学', 'Google Code Jam']
---
# [GCJ 2014 Finals] Allergy Testing
## 题目描述

Kelly is allergic to exactly one of $\mathrm{N}$ foods, but she isn't sure which one. So she decides to undergo some experiments to find out.

In each experiment, Kelly picks several foods and eats them all. She waits $\mathrm{A}$ days to see if she gets any allergic reactions. If she doesn't, she knows she isn't allergic to any of the foods she ate. If she does get a reaction, she has to wait for it to go away: this takes a total of $\mathrm{B}$ days (measured from the moment when she ate the foods).

To simplify her experimentation, Kelly decides to wait until each experiment is finished (after $\mathrm{A}$ or $\mathrm{B}$ days) before starting the next one. At the start of each experiment, she can choose the set of foods she wants to eat based on the results of previous experiments.

Kelly chooses what foods to eat for each experiment to minimize the worst-case number of days before she knows which of the $\mathrm{N}$ foods she is allergic to. How long does it take her in the worst case?
## 输入格式

The first line of the input gives the number of test cases, $\mathrm{T}$. $\mathrm{T}$ test cases follow. Each test case on a single line, containing three space-separated integers: $\mathrm{N}, \mathrm{A}$ and $\mathrm{B}$.

## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is the number of days it will take for Kelly to find out which food she is allergic to, in the worst case.
## 样例

### 样例输入 #1
```
3
4 5 7
8 1 1
1 23 32
```
### 样例输出 #1
```
Case #1: 12
Case #2: 3
Case #3: 0
```
## 提示

In the first sample case:
- First, Kelly eats foods #1 and #2.
- If she gets no reaction after 5 days, she eats food #3. 5 days after that, she will know whether she is allergic to food #3 or food #4.
- If she does get a reaction to the first experiment, then 7 days after the first experiment, she eats food #1. 5 days after that, she will know whether she is allergic to food #1 or food #2.

**Limits**

- $1 \leq T \leq 200$

**Small dataset(15 Pts)**
- Time Limit: ~~60~~ 3 seconds
- $1 \leq N \leq 10^{15}$
- $1 \leq A\leq B \leq 100$

**Large dataset(35 Pts)**
- Time Limit: ~~120~~ 5 seconds
- $1 \leq N \leq 10^{15}$
- $1 \leq A\leq B \leq 10^{12}$


---

---
title: "[GCJ 2013 Finals] X Marks the Spot"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13304
tag: ['计算几何', '2013', '二分', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2013 Finals] X Marks the Spot
## 题目描述

Fair King Tyrone and his four sons conquered the nation of Carrania. His four sons immediately started to squabble about dividing the land between the four of them. The main point of contention was the gold mines of Carrania - each son wanted to have no fewer gold mines than any other.

Fair King Tyrone soon got tired of the squabbling, especially when he learned the number of mines is $4N$, so dividing them should be easy. He gathered his sons, took a map, drew an X on it and declared each son would get one quarter of the nation, with borders defined by the X he drew.

Unfortunately, Fair King Tyrone is a bit shortsighted, and the map he drew on was not a map of Carrania. His first minister quickly hid the map, and now tries to draw an identical X on the map of Carrania so that each son gets the same number of gold mines. Unfortunately all sons saw King Tyrone draw the X, and know the borders should be two perpendicular straight lines - so the minister has to make them so.

Help him! Your task is to draw two perpendicular straight lines such that no gold mine lies on a border, and the borders divide the gold mines equally.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a number $N$, describing the number of gold mines each son should get. $4N$ lines follow, each containing two integers, being the coordinates $x_i$, $y_i$ of one of the gold mines. No three gold mines are co-linear.

## 输出格式

For each test case, output one line containing "Case #x: $x_a$ $y_a$ $x_b$ $y_b$", where $x$ is the case number (starting from 1), ($x_a$, $y_a$) are the coordinates of the point where the two borders intersect, and ($x_b$, $y_b$) are the coordinates of some other point on the X.

All coordinates must be between $-10^9$ and $10^9$, have at most 9 digits after the decimal point, and not use exponential notation. They must be exact: the resulting X will be drawn exactly at these coordinates. You should output IMPOSSIBLE instead if there is no good placement of borders.
## 样例

### 样例输入 #1
```
2
1
0 0
1 0
0 1
1 1
1
1 0
0 1
-1 0
0 -1
```
### 样例输出 #1
```
Case #1: 0.5 0.5 2 0.5
Case #2: 0 0 -3 -3
```
## 提示

**Limits**

- $1 \leq T \leq 20$
- $-10^6 \leq x_i, y_i \leq 10^6$

**Small dataset (10 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq N \leq 10$

**Large dataset (29 Pts, Test set 2 - Hidden)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq N \leq 2500$


---

---
title: "[OOI 2023] Gasoline prices / 油价"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13528
tag: ['线段树', '倍增', '二分', '并查集', '2023', '树链剖分', '哈希 hashing', 'Moscow Olympiad']
---
# [OOI 2023] Gasoline prices / 油价
## 题目背景

CF1801E
## 题目描述

伯利兰是一个由 $n$ 个城市组成的庞大国家。伯利兰的公路网络可以被看作是一棵有根树，也就是说全国一共有 $n - 1$ 条道路，并且任意两个城市之间都恰好有一条路径相连，且不会重复经过同一个城市。为了方便表示，每个城市 $i$ 都有一个固定的城市 $p_i$，它表示从城市 $i$ 出发前往城市 $1$ 时，首先要到达的城市。换句话说，如果将树的根设为城市 $1$，那么 $p_i$ 就是城市 $i$ 的父节点。

每个城市都有一个加油站。每个加油站的油价都有一个固定的区间，在这个区间内可以选择任意一个价格。城市 $i$ 的加油站油价可以是 $l_i$ 到 $r_i$ 之间的任意整数（包括两端）。

伯利兰的国王是个顾家的好父亲，他连续 $m$ 年每年都迎来了两位儿子的出生。国王的孩子们从小就参与国家事务，每年年末，他们会检查油价是否公平。自出生起，第 $i$ 年出生的两个孩子分别负责检查从城市 $a_i$ 到城市 $b_i$ 的路径，以及从城市 $c_i$ 到城市 $d_i$ 的路径上的油价。

检查的方式如下：两个孩子分别同时从城市 $a_i$ 和 $c_i$ 出发。第一个孩子沿着从 $a_i$ 到 $b_i$ 的路径前进，第二个孩子则沿着从 $c_i$ 到 $d_i$ 的路径前进。他们会依次检查：起点 $a_i$ 和 $c_i$ 的油价是否相同，然后检查路径上的第二个城市是否油价相同，依此类推，直到终点 $b_i$ 和 $d_i$ 的油价也要一致。保证从 $a_i$ 到 $b_i$ 的路径长度和从 $c_i$ 到 $d_i$ 的路径长度相同。

所有加油站都必须严格遵守法律，因此所有的油价检查都不能出现违规。请你帮助伯利兰的加油站计算，在 $m$ 年内，他们有多少种合法的油价设置方式。换句话说，对于每个 $i$ 从 $1$ 到 $m$，请计算在前 $i$ 年出生的所有王子进行检查后，所有检查都不出现违规，且每个加油站的油价在允许区间内的情况下，总共有多少种油价分配方案。由于答案可能很大，请对 $10^9 + 7$ 取模输出。

## 输入格式

第一行包含一个整数 $n$（$1 \le n \le 200\,000$），表示伯利兰的城市数量。

第二行包含 $n-1$ 个整数 $p_2,\ p_3,\ \ldots,\ p_n$（$1 \le p_i \le n$），其中 $p_i$ 表示从城市 $i$ 前往城市 $1$ 时的下一个城市编号。

接下来的 $n$ 行，每行两个整数 $l_i$ 和 $r_i$（$1 \le l_i \le r_i < 10^9+7$），表示第 $i$ 个城市加油站允许的油价区间。

再下一行包含一个整数 $m$（$1 \le m \le 200\,000$），表示国王有多少年每年出生两位儿子。

接下来的 $m$ 行，每行四个整数 $a_i, b_i, c_i, d_i$（$1 \le a_i, b_i, c_i, d_i \le n$），表示第 $i$ 年出生的两位王子分别要检查的两条路径。保证 $a_i$ 到 $b_i$ 的路径长度等于 $c_i$ 到 $d_i$ 的路径长度。

## 输出格式

输出 $m$ 行，每行一个整数。第 $i$ 行表示在前 $i$ 年出生的所有王子进行检查后，所有检查都不出现违规，且每个加油站油价在允许区间内的情况下，总共有多少种油价分配方案。结果对 $10^9 + 7$ 取模。

## 样例

### 样例输入 #1
```
5
1 1 2 2
2 4
1 3
1 3
2 4
4 4
4
1 1 2 2
1 2 2 1
3 4 4 3
3 4 3 5
```
### 样例输出 #1
```
18
18
4
0
```
### 样例输入 #2
```
8
1 2 3 4 5 8 6
3 7
2 6
3 8
5 10
5 8
2 9
3 8
6 8
4
1 3 7 6
4 1 5 7
1 7 7 1
1 8 2 7
```
### 样例输出 #2
```
720
120
120
1

```
## 提示

### 样例解释

以第一个样例为例：

- 在头两位王子出生后，城市 $1$ 和城市 $2$ 的油价必须相同。可以在允许的区间内为城市 $1$ 和 $2$ 选择相同的油价方式有 $2$ 种。剩下城市 $3$ 和 $4$ 的油价分别有 $3$ 种和 $3$ 种选择。总方案数为 $2 \times 3 \times 3 \times 1 = 18$。
- 第二对王子检查的是 $1-2$ 和 $2-1$，这要求城市 $1$ 和 $2$ 的油价一致，这个条件已经满足，因此方案数不变。
- 第三对王子检查的是 $3-1-2-4$ 和 $4-2-1-3$，这要求城市 $3$ 和 $4$ 的油价相同，城市 $1$ 和 $2$ 的油价也要相同。城市 $1$ 和 $2$ 已经一致，而城市 $3$ 和 $4$ 可以有 $2$ 种相同的油价选择。总方案数为 $2 \times 2 \times 1 = 6$。
- 第四对王子检查的是 $3-1-2-4$ 和 $3-1-2-5$，这要求城市 $4$ 和 $5$ 的油价一致，而城市 $3$ 和 $4$ 已经一致，因此 $3$、$4$、$5$ 三个城市的油价都要一致。城市 $3$ 的油价不能超过 $3$，城市 $5$ 的油价不能低于 $4$，因此不存在满足条件的方案，答案为 $0$。

### 评分说明

本题的数据分为 8 组。只有通过某一组全部测试点，且通过部分之前组全部测试点，才能获得该组分数。有些分组不要求通过样例测试点。“离线评测”表示该组的测试结果只会在比赛结束后公布。

| 组别 | 分值 | $n$ | $m$ | 必须通过的组 | 备注 |
|:----:|:----:|:---:|:---:|:------------:|:----:|
| 0    | 0    | --  | --  | --           | 样例测试点 |
| 1    | 12   | $n \le 300$ | $m \le 300$ | 0 |  |
| 2    | 10   | $n \le 3000$ | $m \le 3000$ | -- | $p_i = i - 1$ |
| 3    | 9    | $n \le 3000$ | $m \le 3000$ | 0, 1, 2 |  |
| 4    | 16   | --  | --  | 0 -- 3       | 所有检查路径的总长度不超过 $10^8$ |
| 5    | 10   | $n \le 100\,000$ | $m \le 100\,000$ | 2 | $p_i = i - 1$ |
| 6    | 12   | --  | --  | 2, 5         | $p_i = i - 1$ |
| 7    | 13   | $n \le 100\,000$ | $m \le 100\,000$ | 0 -- 3, 5 |  |
| 8    | 18   | --  | --  | 0 -- 7       | **离线评测** |


---

---
title: "[OOI 2023] 寻找假币"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13533
tag: ['二分', '2023', '交互题', 'Special Judge', '剪枝', 'Moscow Olympiad']
---
# [OOI 2023] 寻找假币
## 题目描述

**这是一个交互式问题。**

你面前有一批 $n$ 枚金币，其中有 $k$ 枚是假币。所有金币排成一行。第 $i$ 枚金币的理论重量为 $i$ 克。如果某枚金币是假币，它的重量为 $0$ 克。

禁止触碰金币，你唯一能进行的操作是选择某个 $1 \leq p \leq n$，称为称重操作，对前 $p$ 枚金币进行称重。你将得到这 $p$ 枚金币的真实总重量。

请你用尽量少的操作，找出哪 $k$ 枚金币是假币。你做的称重次数越少，得分越高，具体请见评分说明。

### 交互说明

每个测试包含 $t$ 局游戏，你需要在每局中找出哪些金币是假币。输入的第一行包含一个整数 $t$（$1 \leq t \leq 50$），表示游戏的局数。每局的交互格式如下。所有局结束后，你的程序应当终止。

每局开始时，给出两个整数 $n$ 和 $k$（$1 \leq n \leq 10^9$，$1 \leq k \leq \min(100, n)$）。此后你可以进行多次称重操作。

要进行一次称重操作，输出 `? p`（注意空格），表示你要称重前 $p$ 枚金币。你将获得一个整数 $a$。如果 $a = -1$，说明你已经超过了本局允许的最大称重次数，你的程序必须立即终止。每局最多允许 $3500$ 次称重。若 $a \geq 0$，则 $a$ 是金币 $1, 2, \ldots, p$ 的真实总重量。

当你确定了假币的位置后，输出 $!\ i_1\ i_2\ \ldots\ i_k$，其中 $1 \leq i_1, i_2, \ldots, i_k \leq n$ 且互不相同，表示你认为是假币的编号，顺序任意。此后你会收到一个整数 $a$。如果 $a = -1$，说明你的答案错误，你的程序必须立即终止。否则 $a = 1$，表示答案正确，你应继续进行下一局或终止（如果这是最后一局）。

注意，交互器是**自适应**的。并不保证每局假币的位置在游戏开始前就已确定。唯一保证的是，交互器给出的所有称重结果，在任何时刻都与某个假币集合相符。你的答案是正确的，如果它与所有你收到的称重结果一致，且不存在另一个假币集合也能与所有称重结果一致。

每次输出后请输出换行符，并刷新输出缓冲区。

如果你使用 Pascal 的 `writeln`，C++ 的 `cout << ... << endl`，Java 的 `System.out.println`，Python 的 `print`，C# 的 `Console.WriteLine`，则会自动刷新缓冲区，无需特殊处理。如果你使用其他输出方式，建议手动刷新。无论如何，每次输出都要换行。

## 样例

### 样例输入 #1
```
2
3 2

2

1
10 4

13

13

20

29

1
```
### 样例输出 #1
```


? 3

! 1 3


? 5

? 6

? 8

? 10

! 10 8 6 2

```
## 提示

### 样例解释

在第一局中，金币 $1$ 和 $3$ 是假币，因此实际重量为 $[0, 2, 0]$。只需一次称重即可得到总重量 $2$，据此可以唯一确定假币的位置。

在第二局中，金币 $2, 6, 8, 10$ 是假币，实际重量为 $[1, 0, 3, 4, 5, 0, 7, 0, 9, 0]$。通过称重结果可以唯一确定假币集合。

### 评分说明

本题测试点分为 6 组。设 $q$ 为你在一局中称重的次数。

前 5 组，每组有一个 $maxQ$，如果你在一局中 $q \leq maxQ$，则该测试点通过。只有通过某组全部测试点，且通过部分之前组全部测试点，才能获得该组分数。

第 6 组为部分分，单局得分为 $\min\left(50, \left\lfloor 50 \sqrt{\frac{k + 30}{q}} \right\rfloor\right)$。该组的总分为所有测试中单局得分的最小值。

注意：如果你在所有测试的所有局中都能做到 $q \leq k + 30$，则可获得 $100$ 分。

| 组别 | 分值 | $n$ | $k$ | $maxQ$ | 必须通过的组 | 备注 |
|:----:|:----:|:---:|:---:|:------:|:------------:|:----:|
| 0    | 0    | --  | --  | $3500$ | --           | 样例测试点 |
| 1    | 5    | $n \leq 1000$ | --   | $1000$ | 0           |      |
| 2    | 9    | $n \leq 1000$ | --   | $600$  | 0, 1        |      |
| 3    | 10   | --  | $k \leq 30$ | $1000$ | 0           |      |
| 4    | 13   | --  | $k = 3$ | $33$   | --           |      |
| 5    | 13   | --  | $k = 4$ | $34$   | --           |      |
| 6    | $\leq 50$ | -- | -- | $3500$ | --           | 部分分数 |



---

---
title: "[IOI 2025] Festival"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13538
tag: ['动态规划 DP', '二分', '2025', 'IOI', '交互题', 'Special Judge']
---
# [IOI 2025] Festival
## 题目描述

Nayra is at a festival playing a game where the grand prize is a trip to Laguna Colorado. The game consists of using tokens to buy coupons. Buying a coupon may result in additional tokens. The goal is to get as many coupons as possible.

She starts the game with $A$ tokens. There are $N$ coupons, numbered from $0$ to $N - 1$. Nayra has to pay $P[i]$ tokens ($0 \leq i < N$) to buy coupon $i$ (and she must have at least $P[i]$ tokens before the purchase). She can buy each coupon at most once.

Moreover, each coupon $i$ ($0 \leq i < N$) is assigned a **type**, denoted by $T[i]$, which is an integer **between $1$ and $4$**, inclusive. After Nayra buys coupon $i$, the remaining number of tokens she has gets multiplied by $T[i]$. Formally, if she has $X$ tokens at some point of the game, and buys coupon $i$ (which requires $X \geq P[i]$), then she will have $(X - P[i]) \cdot T[i]$ tokens after the purchase.

Your task is to determine which coupons Nayra should buy and in what order, to maximize the total number of **coupons** she has at the end. If there is more than one sequence of purchases that achieves this, you may report any one of them.

### Implementation Details

You should implement the following procedure:

```cpp
std::vector<int> max_coupons(int A, std::vector<int> P, std::vector<int> T)
```

- $A$: the initial number of tokens Nayra has.
- $P$: an array of length $N$ specifying the prices of the coupons.
- $T$: an array of length $N$ specifying the types of the coupons.
- This procedure is called exactly once for each test case.

The procedure should return an array $R$, which specifies Nayra's purchases as follows:

- The length of $R$ should be the maximum number of coupons she can buy.
- The elements of the array are the indices of the coupons she should buy, in chronological order. That is, she buys coupon $R[0]$ first, coupon $R[1]$ second, and so on.
- All elements of $R$ must be unique.

If no coupons can be bought, $R$ should be an empty array.
## 输入格式

Input format:

```
N A
P[0] T[0]
P[1] T[1]
...
P[N-1] T[N-1]
```
## 输出格式

Output format:

```
S
R[0] R[1] ... R[S-1]
```

Here, $S$ is the length of the array $R$ returned by `max_coupons`.
## 样例

### 样例输入 #1
```
4 13
4 1
500 3
8 3
14 4
```
### 样例输出 #1
```
3
2 3 0
```
### 样例输入 #2
```
2 9
6 2
5 3
```
### 样例输出 #2
```
2
0 1
```
### 样例输入 #3
```
3 1
2 4
5 3
7 1
```
### 样例输出 #3
```
0


```
## 提示

### Example 1

Consider the following call.

```cpp
max_coupons(13, [4, 500, 8, 14], [1, 3, 3, 4])
```

Nayra initially has $A = 13$ tokens. She can buy 3 coupons in the order shown below:

| Coupon bought | Coupon price | Coupon type | Number of tokens after the purchase |
| :-: | :-: | :-: | :-: |
| 2 | 8 | 3 | $(13 - 8) \cdot 3 = 15$ |
| 3 | 14 | 4 | $(15 - 14) \cdot 4 = 4$ |
| 0 | 4 | 1 | $(4 - 4) \cdot 1 = 0$ |

In this example, it is not possible for Nayra to buy more than 3 coupons, and the sequence of purchases described above is the only way in which she can buy 3 of them. Hence, the procedure should return $[2, 3, 0]$.

### Example 2

Consider the following call.

```cpp
max_coupons(9, [6, 5], [2, 3])
```

In this example, Nayra can buy both coupons in any order. Hence, the procedure should return either $[0, 1]$ or $[1, 0]$.

### Example 3

Consider the following call.

```cpp
max_coupons(1, [2, 5, 7], [4, 3, 1])
```

In this example, Nayra has one token, which is not enough to buy any coupons. Hence, the
procedure should return $[]$  (an empty array).

### Constraints

- $1 \leq N \leq 200000$
- $1 \leq A \leq 10^9$
- $1 \leq P[i] \leq 10^9$ for each $i$ such that $0 \leq i < N$.
- $1 \leq T[i] \leq 4$ for each $i$ such that $0 \leq i < N$.

### Subtasks

| Subtask | Score | Additional Constraints |
| :-: | :-: | :-: |
| 1 | 5 | $T[i] = 1$ for each $i$ such that $0 \leq i < N$. |
| 2 | 7 | $N \leq 3000; T[i] \leq 2$ for each $i$ such that $0 \leq i < N$. |
| 3 | 12 | $T[i] \leq 2$ for each $i$ such that $0 \leq i < N$. |
| 4 | 15 | $N \leq 70$ |
| 5 | 27 | Nayra can buy all $N$ coupons (in some order). |
| 6 | 16 | $(A - P[i]) \cdot T[i] < A$ for each $i$ such that $0 \leq i < N$. |
| 7 | 18 | No additional constraints. |


---

---
title: "「TPOI-5C」mαtrixing ωiθ μ"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13664
tag: ['线段树', 'O2优化', '树套树', '扫描线', '整体二分']
---
# 「TPOI-5C」mαtrixing ωiθ μ
## 题目背景

**本题禁止卡评测。**

![](https://cdn.luogu.com.cn/upload/image_hosting/qphit8fj.png?x-oss-process=image/resize,m_lfit,h_2170,w_2225)
## 题目描述

在东京的大雨后，天野阳菜给了 kele7 一个 $n$ 行 $m$ 列的矩阵 $A$。从上往下第 $i$ 行，从左往右第 $j$ 列的元素被称为 $A_{i,j}$。

kele7 喜欢删除矩阵。对于一个 $r$ 行 $c$ 列的矩阵 $B$，他会对它执行两种操作，同时会用**优雅值**衡量一个操作的优雅程度：

- 删除矩阵的某一行 $B_{i,1},\dots,B_{i,c}$，优雅值为 $\text{mex}_{j=1}^cB_{i,j}$。然后将第 $i+1\sim r$ 行往上平移一行，令 $r\leftarrow r-1$。
- 删除矩阵的某一列 $B_{1,i},\dots,B_{r,i}$，优雅值为 $\text{mex}_{j=1}^rB_{j,i}$。然后将第 $i+1\sim c$ 列往左平移一列，令 $c\leftarrow c-1$。

最终 kele7 要将矩阵内的元素全部删除（即 $r$ 或 $c$ 变为 $0$）。定义一种删除方案 $S$ 的权值 $f(S)$ 为其中所有操作的优雅值的**最小值**。定义矩阵 $B$ 的权值 $F(B)$ 为所有删除它的方案 $S$ 中 $f(S)$ 的**最大值**。

kele7 把这个题目给了 lzyqwq。lzyqwq 觉得还可以加上 $q$ 次查询，每次给出 $x_1,y_1,x_2,y_2$，你需要回答当矩阵 $B$ 为矩阵 $A$ 以 $A_{x_1,y_1}$ 为左上角元素、$A_{x_2,y_2}$ 为右下角元素的子矩阵时，$F(B)$ 的值。

一个集合 $M$ 的 $\operatorname{mex}(M)$ 定义为最小的没有在 $M$ 中出现的自然数。如 $\text{mex}\{1,2,3,4\}=0,\text{mex}\{0,1,3,4\}=2$。
## 输入格式

第一行三个正整数 $n,m,q$。

接下来 $n$ 行，每行 $m$ 个自然数。第 $i$ 行为 $A_{i,1},\dots,A_{i,m}$。

接下来 $q$ 行，每行四个整数 $x_1,y_1,x_2,y_2$ 表示一组询问。
## 输出格式

$q$ 行，每行一个自然数，表示一个询问的答案。
## 样例

### 样例输入 #1
```
5 5 5
0 1 0 1 2
3 2 0 1 4
5 4 3 0 1
0 2 0 3 1
0 0 0 1 2
1 1 5 5
2 2 4 4
1 2 4 5
3 2 4 4
1 2 2 3
```
### 样例输出 #1
```
2
1
2
1
1

```
## 提示

**【样例解释】**

以第一个询问为例。初始矩阵 $B$ 为：

$$\begin{bmatrix}0&1&0&1&2\\3&2&0&1&4\\5&4&3&0&1\\0&2&0&3&1\\0&0&0&1&2\end{bmatrix}$$

一种可行的删除方案如下。

先删除第二行，优雅值为 $5$，得到新的矩阵 $B$ 为：

$$\begin{bmatrix}0&1&0&1&2\\5&4&3&0&1\\0&2&0&3&1\\0&0&0&1&2\end{bmatrix}$$

再删除第二列，优雅值为 $3$，得到新的矩阵 $B$ 为：

$$\begin{bmatrix}0&0&1&2\\5&3&0&1\\0&0&3&1\\0&0&1&2\end{bmatrix}$$

再依次删除所有行，优雅值分别为 $3,2,2,3$。

因此这种删除方案的权值为 $2$。可以证明，不存在优雅值的最小值更大的删除方案，因此答案为 $2$。

**【数据范围】**

|$\text{Subtask}$|$n,m$     |$q$       |特殊性质      |分值  |
|:--------:|:--------:|:--------:|:--------:|:--:|
|$0$       |$n\times m\le3\times10^5$|$q=1$     |无         |$11$|
|$1$       |$\color{red}{n,m\le300}$|$q\le10^5$|^         |^   |
|$2$       |$n\times m\le10^5$|^         |^         |$20$|
|$3$       |$n\times m\le2\times10^5$|$q\le2\times10^5$|^         |$24$|
|$4$       |$n\times m\le3\times10^5$|$q\le3\times10^5$|$x_1=y_1=1$|$8$ |
|$5$       |^         |^         |无         |$26$|

对于 $100\%$ 的数据，满足 $1\le n\times m,q\le 3\times 10^5$，$0\le A_{i,j}\le 10^9$。


---

---
title: "[NOI2009] 描边"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1756
tag: ['计算几何', '高精度', '2009', 'NOI', '提交答案', 'Special Judge', '二分图']
---
# [NOI2009] 描边
## 题目描述

小 Z 是一位杰出的数学家。聪明的他特别喜欢研究一些数学小问题。

有一天，他在一张纸上选择了 $n$ 个点，并用铅笔将它们两两连接起来，构成 $\dfrac{n(n-1)}{2}$ 条线段。由于铅笔很细，可以认为这些线段的宽度为 $0$。

望着这些线段，小 Z 陷入了冥想中。他认为这些线段中的一部分比较重要，需要进行强调。因此小 Z 拿出了毛笔，将它们重新进行了描边。毛笔画在纸上，会形成一个半径为 $r$ 的圆。在对一条线段进行描边时，毛笔的中心（即圆心）将从线段的一个端点开始，沿着该线段描向另一个端点。下图即为在一张 $4$ 个点的图中，对其中一条线段进行描边强调后的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/h92i5d69.png)

现在，小 Z 非常想知道在描边之后纸面上共有多大面积的区域被强调，你能帮助他解答这个问题么？
## 输入格式

本题是一道提交答案型试题，所有的输入文件 `path1.in` $\sim$ `path10.in` 已在相应目录下。

输入文件请点击 [这里](http://pan.baidu.com/s/1gfeLZqz) 下载。

输入文件的第一行为一个正整数 $n$，表示选择的点的数目。

第二行至第 $n+1$ 行，其中：第 $i+1$ 行中为两个实数 $x_i,y_i$，表示点 $i$ 的坐标为 $(x_i,y_i)$。

第 $n+2$ 行为一个正整数 $m$，表示小 Z 认为比较重要的线段的条数。

第 $n+3$ 行至第 $n+m+2$ 行，每行有两个正整数 $a,b$，表示一条线段。其中 $a,b$ 两个数分别表示该线段的两个端点的编号。

第 $n+m+3$ 行中为一个实数 $r$，表示毛笔在纸上形成的圆的半径。

第 $n+m+4$ 行中为四个实数 $p_1,p_2,p_3,p_4$，即评分使用的参数。
## 输出格式

输出文件 `path*.out` 仅一行一个数，即为描边后被强调区域的总面积。
## 样例

### 样例输入 #1
```
2
1 1
1 2
1
1 2
1
0.00001 0.001 0.1 1

```
### 样例输出 #1
```
5.1415927
```
## 提示

每个测试点单独评分。

本题设有 $4$ 个评分参数 $p_1,p_2,p_3,p_4$（$p_1 \lt p_2 \lt p_3 \lt p_4$），已在输入文件中给出。

你的得分将按照如下规则给出：

- 若你的答案与标准答案相差不超过 $p_1$，则该测试点你将得到满分；
- 否则，若你的答案与标准答案相差不超过 $p_2$，则你将得到该测试点 $70\%$ 的分数；
- 否则，若你的答案与标准答案相差不超过 $p_3$，则你将得到该测试点 $40\%$ 的分数；
- 否则，若你的答案与标准答案相差不超过 $p_4$，则你将得到该测试点 $10\%$ 的分数；
- 否则，该测试点你的得分为 $0$。


---

---
title: "[NOI2011] 兔兔与蛋蛋游戏"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P1971
tag: ['2011', 'NOI', '深度优先搜索 DFS', '二分图']
---
# [NOI2011] 兔兔与蛋蛋游戏
## 题目描述

这些天，兔兔和蛋蛋喜欢上了一种新的棋类游戏。

这个游戏是在一个 $n$ 行 $m$ 列的棋盘上进行的。游戏开始之前，棋盘上有一个格子是空的，其它的格子中都放置了一枚棋子，棋子或者是黑色，或者是白色。

每一局游戏总是兔兔先操作，之后双方轮流操作，具体操作为：

* 兔兔每次操作时，选择一枚与空格相邻的白色棋子，将它移进空格。
* 蛋蛋每次操作时，选择一枚与空格相邻的黑色棋子，将它移进空格。

第一个不能按照规则操作的人输掉游戏。为了描述方便，下面将操作“将第x行第y列中的棋子移进空格中”记为 $M(x,y)$。

例如下面是三个游戏的例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/6wfmhuf2.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/j7vox6n7.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/er1t5wpb.png)

最近兔兔总是输掉游戏，而且蛋蛋格外嚣张，于是兔兔想请她的好朋友——你——来帮助她。她带来了一局输给蛋蛋的游戏的实录，请你指出这一局游戏中所有她“犯错误”的地方。

注意：

* 两个格子相邻当且仅当它们有一条公共边。
* 兔兔的操作是“犯错误”的，当且仅当，在这次操作前兔兔有必胜策略，而这次操作后蛋蛋有必胜策略。

## 输入格式

输入的第一行包含两个正整数 $n,m$。

接下来 $n$ 行描述初始棋盘。其中第 $i$ 行包含 $m$ 个字符，每个字符都是大写英文字母 `X`、大写英文字母 `O` 或点号 `.` 之一，分别表示对应的棋盘格中有黑色棋子、有白色棋子和没有棋子。其中点号 `.` 恰好出现一次。

接下来一行包含一个整数 $k$（$1\leq k\leq 1000$） ，表示兔兔和蛋蛋各进行了 $k$ 次操作。

接下来 $2k$ 行描述一局游戏的过程。其中第 $2i - 1$ 行是兔兔的第 $i$ 次操作（编号为 $i$ 的操作） ，第 $2i$ 行是蛋蛋的第 $i$ 次操作。每个操作使用两个整数 $x,y$ 来描述，表示将第 $x$ 行第 $y$ 列中的棋子移进空格中。

输入保证整个棋盘中只有一个格子没有棋子， 游戏过程中兔兔和蛋蛋的每个操作都是合法的，且最后蛋蛋获胜。

## 输出格式

输出文件的第一行包含一个整数 $r$，表示兔兔犯错误的总次数。

接下来 $r$ 行按递增的顺序给出兔兔“犯错误”的操作编号。其中第 $i$ 行包含一个整数 $a_i$ 表示兔兔第 $i$ 个犯错误的操作是他在游戏中的第 $a_i$ 次操作。


## 样例

### 样例输入 #1
```
1 6 
XO.OXO 
1 
1 2 
1 1 
```
### 样例输出 #1
```
1
1
```
### 样例输入 #2
```
3 3 
XOX 
O.O 
XOX 
4 
2 3 
1 3 
1 2 
1 1 
2 1 
3 1 
3 2 
3 3 
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
4 4 
OOXX 
OXXO 
OO.O 
XXXO 
2 
3 2 
2 2 
1 2 
1 3 
```
### 样例输出 #3
```
2
1
2
```
## 提示

对于 $100\%$ 的数据，$1\leq n\leq 40$，$1 \leq m\leq 40$，$1\leq k\leq 1000$。

|测试点编号|$n$|$m$|
|:-:|:-:|:-:|
|$1,2$|$n=1$|$1\leq m\leq 20$|
|$3$|$n=3$|$m=4$|
|$4,5$|$n=4$|$m=4$|
|$6,7$|$n=4$|$m=5$|
|$8$|$n=3$|$m=7$|
|$9\sim 14$|$n=2$|$1\leq m\leq 40$|
|$15,16$|$1\leq n\leq 16$|$1\leq m\leq 16$|
|$17\sim 20$|$1\leq n\leq 40$|$1\leq m\leq 40$|



---

---
title: "[USACO16OPEN] Bull in a China Shop P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3148
tag: ['模拟', '2016', '二分', 'USACO', 'O2优化', '哈希 hashing', '前缀和']
---
# [USACO16OPEN] Bull in a China Shop P
## 题目描述

Farmer John has decided his home needs more decoration. Visiting the local china shop, he finds a delicate glass cow figurine that he decides to purchase, knowing that it will fit perfectly on the mantel above his fireplace.

The shape of the cow figurine is described by an $N \times M$ grid of haracters like the one below ($3 \leq N, M \leq 500$), where lowercase letter characters are each part of the figurine (indicating different colors) and '.' characters are not.

```
...............
...............
x..x...........
xxxx...........
xxxxaaaaaaa...
.xx.aaaaaaaaa..
....aaaaaaa.aa.
....ll...ll....
....vv...vv....
...............
```

Unfortunately, right before FJ can make his purchase, a bull runs through the shop  and breaks not only FJ's figurine, but many of the other glass objects on the shelves as well!  FJ's figurine breaks into 3 pieces, which quickly becomelost  among $K$ total pieces lying on the ground ($4 \leq K \leq 100$).  Each ofthe $K$ pieces is described by a grid of characters, just like the originalfigurine.

Please help FJ determine how many sets of 3 pieces (out of the $K$ on the floor)could be glued back together to mend his broken figurine.

The pieces on the ground might have been flipped vertically or horizontally, orrotated by some multiple of 90 degrees. Therefore, given the original grid aswell as $K$ grids describing pieces, you want to find sets of 3 pieces that canbe joined together to form the original picture, allowing the pieces to betranslated, flipped, or rotated multiples of 90 degrees.  When thensuperimposed, the 3 pieces should exactly form the original picture, with eachcolored square in the original picture represented in exactly one of the pieces.
## 输入格式

The first line contains a single integer $K$. Following that will be $K + 1$ piece descriptions.  The first description will describe the original glass cow,the following $K$ descriptions will be of the broken pieces.

Each description begins with a line containing two integers $R$ and $C$ ($1 \le R, C \le 100$).  The following $R$ lines contain $C$ lowercase alphabet characters describing the color of each cell.  Each piece will be horizontally/vertically connected and have at least one non-empty cell.

## 输出格式

Output the number of triples $i, j, k$ ($i < j < k$) such that pieces $i$, $j$, and $k$ can be arranged to form the original glass cow.
## 样例

### 样例输入 #1
```
5
5 5
aaaaa
..a..
bbabb
..a..
aaaaa
3 5
..abb
..a..
aaaaa
5 2
a.
a.
aa
a.
a.
1 2
bb
1 5
bbabb
2 5
aaaaa
..a..
```
### 样例输出 #1
```
3
```
## 提示

The three solutions use pieces $(0, 1, 2)$, $(0, 2, 4)$, $(1, 3, 4)$.

Note that this problem has a time limit of 6 seconds per test case (and twice that  for Java and Python submissions).
## 题目翻译

### 题目描述

Farmer John 决定给他的家增添一些装饰。在当地的瓷器店里，他发现了一尊精致的玻璃牛雕像，决定购买它，因为它完美地适合放在壁炉上方的壁炉架上。

牛雕像的形状由一个 $N \times M$ 的字符网格描述（$3 \leq N, M \leq 500$），其中小写字母字符代表雕像的各个部分（表示不同的颜色），而 '.' 字符则不代表雕像部分。

```cpp
...............
...............
x..x...........
xxxx...........
xxxxaaaaaaa...
.xx.aaaaaaaaa..
....aaaaaaa.aa.
....ll...ll....
....vv...vv....
...............
```

不幸的是，就在 FJ 准备购买之前，一头公牛冲进了商店，不仅撞碎了 FJ 的雕像，还撞碎了许多其他货架上的玻璃制品！FJ 的雕像碎成了 3 块，并迅速混入了地上的 $K$ 块碎片中（$4 \leq K \leq 100$）。每一块碎片都由一个字符网格描述，就像原来的雕像一样。

请帮助 FJ 确定有多少组 3 块碎片（地上的 $K$ 块中）可以粘合在一起修复他破碎的雕像。

地上的碎片可能被垂直或水平翻转，或者旋转了 90 度的倍数。因此，给定原始网格以及描述碎片的 $K$ 个网格，你需要找到可以组合成原始图片的 3 块碎片，允许碎片被平移、翻转或旋转 90 度的倍数。当这 3 块碎片叠加在一起时，它们应该准确地形成原始图片，且原始图片中的每个彩色方块都恰好出现在一块碎片中。

### 输入格式

第一行包含一个整数 $K$。接下来是 $K + 1$ 个碎片的描述。第一个描述是原始玻璃牛的描述，接下来的 $K$ 个描述是破碎的碎片。

每个描述以两个整数 $R$ 和 $C$（$1 \le R, C \le 100$）开始。接下来的 $R$ 行包含 $C$ 个小写字母字符，描述每个单元格的颜色。每块碎片在水平/垂直方向上都是连通的，并且至少有一个非空单元格。

### 输出格式

输出满足条件的三元组 $i, j, k$（$i < j < k$）的数量，使得碎片 $i$、$j$ 和 $k$ 可以排列成原始玻璃牛。

### 说明/提示

三个解决方案使用了碎片 $(0, 1, 2)$、$(0, 2, 4)$ 和 $(1, 3, 4)$。

请注意，这个问题每个测试用例的时间限制为 6 秒（Java 和 Python 提交的时间限制为 12 秒）。


---

---
title: "[ZJOI2015] 醉熏熏的幻想乡"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P3347
tag: ['2015', '二分', '网络流', '浙江']
---
# [ZJOI2015] 醉熏熏的幻想乡
## 题目描述

傲娇少女幽香是一个很萌很萌的妹子，这些天幻想乡的大家都不知道为何还是拼命喝酒。很快酒就供不应求了，为了满足大家的需求，幽香决定在森林里酿酒。

经过调查，幽香发现森林里面有一些地方非常适合酿酒，有一些地方则非常适合存酒。幽香把这些适合酿酒的地方成为酿酒点，不妨认为有 $n$ 个酿酒点，从 $1$ 到 $n$ 标号。同时也有 $m$ 个适合存酒的地方，幽香将它们成为存酒点，从 $1$ 到 $m$ 标号。在一些酿酒点和存酒点之间存在通道，如果酿酒点 $i$ 到存酒点 $j$ 之间存在通道，那么 $i$ 生产的酒就可以被运输到 $j$。

但是在一个地方酿酒是需要消耗幽香的魔力的，由于存在管理上的因素，在酿酒点 $i$，制造 $x$ 升的酒，需要花费 $a_i\cdot x^2+b_i\cdot x$ 的魔力，注意 $x$ 不一定是一个非负整数，也可以是一个非负实数，同时在这个点最多只能制造 $c_i$ 升的酒。每个存酒点 $j$ 有一个容量 $d_j$，表示这个存酒点最多能存多少升的酒。

幽香打算存尽量多的酒，那么她需要再一些酿酒点生产一些酒并且通过通道将酒运送到存酒点。当然幽香想要节省自己的魔力，所以想让你帮忙算出在满足要求的情况下，最少花费的魔力是多少？
## 输入格式

第一行两个正整数 $n$，$m$，表示酿酒点和存酒点的数量。接下来 $n$ 行，第 $i$ 行三个数 $a_i$，$b_i$，$c_i$，表示在酿酒点 $i$ 制造酒的花费系数和上限。接下来一行 $m$ 个整数，一次为每个存酒点的 $d_i$ 值。接下来 $n$ 行，每行 $m$ 个数，其中第 $i$ 行第 $j$ 个表示酿酒点 $i$ 到存酒点 $j$ 有没有通道（$1$ 表示有，$0$ 表示没有）。
## 输出格式

输出第一行表示幽香最多能存多少升酒（注意这肯定是个整数，直接输出即可）。

输出第二行表示最小花费魔力，注意这肯定是一个有理数，化简后按照 $a/b$ 的形式输出（$0$输出 $0/1$）
## 样例

### 样例输入 #1
```
10 10
0 2 3
2 3 2
3 1 3
1 2 1
1 0 1
1 1 0
3 3 0
1 2 2
3 1 1
3 1 0
3 1 2 2 3 1 1 2 2 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
1 0 0 0 1 0 0 0 0 0
1 0 1 0 0 0 0 1 1 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0 1 0
```
### 样例输出 #1
```
8
42/1

```
## 提示

对于 $30\%$ 的数据：所有 $a_i=0$。

对于另 $30\%$ 的数据：最终答案的分母 $\leq 1000$。

对于 $100\%$ 的数据：$1\leq n\leq100$，$1\leq m\leq100$。

对于所有数据，$0\leq a_i,b_i,c_i,d_i\leq3$ 且都是整数。同时对于每个 $i$，$a_i+b_i>0$ 的通道的数量不超过 $1000$ 条。

非常神奇的是，对于所有数据存在一个正整数 $X\leq10^7$，使得存在一个最优解，使得所有路径上运送的酒的体积都是 $1/X$ 的倍数。


---

---
title: "[HEOI2016/TJOI2016] 字符串"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4094
tag: ['2016', '线段树', '二分', '各省省选', '河北', 'O2优化', '可持久化线段树', '后缀数组 SA', '天津']
---
# [HEOI2016/TJOI2016] 字符串
## 题目描述

佳媛姐姐过生日的时候，她的小伙伴从某东上买了一个生日礼物。生日礼物放在一个神奇的箱子中。箱子外边写了一个长为 $n$ 的字符串 $s$，和 $m$ 个问题。佳媛姐姐必须正确回答这 $m$ 个问题，才能打开箱子拿到礼物，升职加薪，出任 CEO，嫁给高富帅，走上人生巅峰。

每个问题均有 $a,b,c,d$ 四个参数，问你子串 $s[a..b]$ 的所有子串和 $s[c..d]$ 的最长公共前缀的长度的最大值是多少？佳媛姐姐并不擅长做这样的问题，所以她向你求助，你该如何帮助她呢？

## 输入格式

输入的第一行有两个正整数 $n,m$，分别表示字符串的长度和询问的个数。

接下来一行是一个长为 $n$ 的字符串。接下来 $m$ 行，每行有 $4$ 个数 $a,b,c,d$，表示询问 $s[a..b]$ 的所有子串和 $s[c..d]$ 的最长公共前缀的最大值。

## 输出格式

对于每一次询问，输出答案。

## 样例

### 样例输入 #1
```
5 5
aaaaa
1 1 1 5
1 5 1 1
2 3 2 3
2 4 2 3
2 3 2 4
```
### 样例输出 #1
```
1
1
2
2
2
```
## 提示

对于 $10\%$ 的数据，$1\le n,m\le 300$。

对于 $40\%$ 的数据，$1\le n,m\le 3,000$，字符串中仅有 `a`,`b`。

对于 $100\%$ 的数据，$1\le n,m\le 100,000$，字符串中仅有小写英文字母，$a\le b$，$c\le d$，$1\le a,b,c,d\le n$。



---

---
title: "[CTSC2008] 祭祀"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4298
tag: ['2008', '网络流', 'Special Judge', '二分图', '构造', 'CTSC/CTS']
---
# [CTSC2008] 祭祀
## 题目描述

在遥远的东方，有一个神秘的民族，自称 Y 族。他们世代居住在水面上，奉龙王为神。每逢重大庆典，Y 族都会在水面上举办盛大的祭祀活动。我们可以把 Y 族居住地水系看成一个由岔口和河道组成的网络。每条河道连接着两个岔口，并且水在河道内按照一个固定的方向流动。显然，水系中不会有环流（下图描述一个环流的例子）。

 ![](https://cdn.luogu.com.cn/upload/pic/15479.png)

由于人数众多的原因，Y 族的祭祀活动会在多个岔口上同时举行。出于对龙王的尊重，这些祭祀地点的选择必须非常慎重。准确地说，Y 族人认为，如果水流可以从一个祭祀点流到另外一个祭祀点，那么祭祀就会失去它神圣的意义。族长希望在保持祭祀神圣性的基础上，选择尽可能多的祭祀的地点。
## 输入格式

第一行包含两个用空格隔开的整数 $N$、$M$，分别表示岔口和河道的数目，岔口从 $1$ 到 $N$ 编号。

接下来 $M$ 行，每行包含两个用空格隔开的整数 $u$、$v$，描述一条连接岔口 $u$ 和岔口 $v$ 的河道，水流方向为自 $u$ 向 $v$。
## 输出格式

第一行包含一个整数 $K$，表示最多能选取的祭祀点的个数。

接下来一行输出一种可行的选取方案。对于每个岔口依次输出一个整数，如果在该岔口设置了祭祀点，那么输出一个 `1`，否则输出一个 `0`。应确保你输出的 `1` 的个数最多，且中间没有空格。

接下来一行输出，在选择最多祭祀点的前提下，每个岔口是否能够设置祭祀点。对于每个岔口依次输出一个整数，如果在该岔口能够设置祭祀点，那么输出一个 `1`，否则输出一个 `0`。

注意：多余的空格和换行可能会导致你的答案被判断为错误答案。
## 样例

### 样例输入 #1
```
4 4
1 2
3 4
3 2
4 2
```
### 样例输出 #1
```
2
1010
1011
```
## 提示

$N \le 100, M \le 1000$

在样例给出的水系中，不存在一种方法能够选择三个或者三个以上的祭祀点。包含两个祭祀点的测试点的方案有两种：

选择岔口 $1$ 与岔口 $3$（如样例输出第二行），选择岔口 $1$ 与岔口 $4$。

水流可以从任意岔口流至岔口 $2$。如果在岔口 $2$ 建立祭祀点，那么任意其他岔口都不能建立祭祀点但是在最优的一种祭祀点的选取方案中我们可以建立两个祭祀点，所以岔口 $2$ 不能建立祭祀点。对于其他岔口至少存在一个最优方案选择该岔口为祭祀点，所以输出为 `1011`。

感谢@ACdreamer 提供SPJ


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
title: "[CEOI 2017] Mousetrap"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4654
tag: ['动态规划 DP', '数学', '2017', '二分', 'CEOI（中欧）']
---
# [CEOI 2017] Mousetrap
## 题目描述

有一个有 $n$ 个房间和 $n-1$ 条走廊的迷宫，保证任意两个房间可以通过走廊互相到达，换句话说，这个迷宫的结构是一棵树。

一个老鼠被放进了迷宫，迷宫的管理者决定和老鼠做个游戏。

一开始，有一个房间被放置了陷阱，老鼠出现在另一个房间。老鼠可以通过走廊到达别的房间，但是会弄脏它经过的走廊。老鼠不愿意通过脏的走廊。

每个时刻，管理者可以进行一次操作：堵住一条走廊使得老鼠不能通过，或者擦干净一条走廊使得老鼠可以通过。然后老鼠会通过一条干净的并且没被堵住的走廊到达另一个房间。只有在没有这样的走廊的情况下，老鼠才不会动。一开始所有走廊都是干净的。管理者不能疏通已经被堵住的走廊。

现在管理者希望通过尽量少的操作将老鼠赶到有陷阱的房间，而老鼠则希望管理者的操作数尽量多。请计算双方都采取最优策略的情况下管理者需要的操作数量。

注意：管理者可以选择在一些时刻不操作。
## 输入格式

第一行三个空格隔开的正整数数 $n,t,m$。分别代表房间的个数，陷阱房的编号和老鼠起始房间的编号。

接下来 $n-1$ 行，每行两个空格隔开的整数 $a_i,b_i$​​，表示有一条走廊连接编号为 $a_i$ 和 $b_i$​​ 的房间。
## 输出格式

输出一行包含一个整数，表示双方都采取最优策略的情况下，管理者需要的操作数量。
## 样例

### 样例输入 #1
```
10 1 4
1 2
2 3
2 4
3 9
3 5
4 7
4 6
6 8
7 10
```
### 样例输出 #1
```
4
```
## 提示

**样例解释**

-    管理者先堵住房间 $4$ 和 $7$ 之间的走廊。
-    老鼠走到房间 $6$。房间 $4$ 和 $6$ 之间的走廊现在是脏的。
-    管理者堵住房间 $6$ 和 $8$ 之间的走廊。
-    老鼠不能动。
-    管理者清理房间 $4$ 和 $6$ 之间的走廊，房间 $4$ 和 $6$ 之间的走廊现在是干净的。
-    老鼠走到房间 $4$，房间 $4$ 和 $6$ 之间的走廊现在是脏的。
-    管理者堵住房间 $2$ 和 $3$ 之间的走廊。
-    老鼠走到房间 $2$，房间 $2$ 和 $4$ 之间的走廊现在是脏的。
-    管理者不进行操作。
-    老鼠走到房间 $1$。

这个过程中管理者总共进行了 $4$ 次操作。

**数据范围**

对于所有的数据，$1 \le n \le 10^6$。


---

---
title: "[JOI 2017 Final] 绳"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P5101
tag: ['贪心', '2017', '二分', 'JOI（日本）']
---
# [JOI 2017 Final] 绳
## 题目描述

**题目译自 [JOI 2017 Final](https://www.ioi-jp.org/joi/2016/2017-ho/) T5「[縄](https://www.ioi-jp.org/joi/2016/2017-ho/2017-ho.pdf) / [Rope](https://www.ioi-jp.org/joi/2016/2017-ho/2017-ho-en.pdf)」**

 JOI 小宝宝正拿着一根绳子玩。绳子可视为一条长度为 $N$ 的左右延伸的线段。绳子由 $N$ 根线连接而成，每根线的长度为 $1$，厚度为 $1$。绳子上的线共有 $M$ 种颜色，左数第 $i$ 根线 $(1\leqslant i\leqslant N)$ 的颜色为 $C_i(1\leqslant C_i\leqslant M)$。**绳子的左端点**意为左数第 $1$ 根线的左端点，**绳子的右端点**意为右数第 $1$ 根线的右端点。显然左数第 $i$ 根线 $(1\leqslant i\leqslant N)$ 的右端点 到 绳子的左端点 的距离为 $i$。

JOI 把绳子的长度缩短了。具体来说，JOI 反复地进行以下过程，直到绳长缩短至 $2$。

* 假设此时绳子的长度为 $L$。指定一个整数 $j(1\leqslant j<L)$，使绳子左数第 $j$ 根线成为绳子的左端点（最左的线），并折叠绳子。也就是说，
  - 如果 $j\leqslant \Large\frac{L}{2}$，则将左数第 $i$ 根线 $(1\leqslant i\leqslant j)$ 与左数第 $(2j-i+1)$ 根线拧成一股。此时，绳子原本的右端点仍是右端点，绳长变为 $L-j$。
  - 如果 $j> \Large\frac{L}{2}$，则将左数第 $i$ 根线 $(2j-L+1\leqslant i\leqslant j)$ 与左数第 $(2j-i+1)$ 根线拧成一股。此时，绳子原本的左端点变为右端点，绳长变为 $j$。
* 两条线的颜色相同才能拧成一股。在将两条线拧成一股前，可以任意改变线的颜色。将线染成其他颜色所需的费用 等于 线的厚度。颜色匹配后，两条线将被拧成一股，新的一股线的厚度 将为 两条线的厚度之和。

我们把绳长缩短至 $2$ 的绳子称为最终的绳子。JOI 希望使得将绳长缩短至 $2$ 所需的费用尽可能小。对于每种颜色，JOI 都想知道，在最终的绳子中包含这种颜色的情况下，将绳长缩短至 $2$ 所需的最小费用。

你的任务是帮 JOI 解决这个问题。
## 输入格式

第一行有两个整数 $N, M$，用空格分隔。  
第二行有 $N$ 个用空格分隔的整数 $C_1, C_2, \ldots, C_N$。  
输入的所有数的含义见题目描述。
## 输出格式

共 $M$ 行，第 $c$ 行 $(1\leqslant c\leqslant M)$ 有一个整数，表示在最终的绳子中包含颜色 $c$ 的情况下，将绳长缩短至 $2$ 所需的最小费用。
## 样例

### 样例输入 #1
```
5 3
1 2 3 3 2
```
### 样例输出 #1
```
2
1
1
```
### 样例输入 #2
```
7 3
1 2 2 1 3 3 3
```
### 样例输出 #2
```
2
2
2
```
### 样例输入 #3
```
10 3
2 2 1 1 3 3 2 1 1 2
```
### 样例输出 #3
```
3
3
4
```
## 提示

#### 样例解释 1
通过下述步骤，只需花费 $2$，就可以使得最终的绳子中包含颜色 $1$。
* 把左数第 $2$ 根线染成颜色 $1$。折叠绳子使得 原本到左端点的距离为 $1$ 的端点 变为 新的左端点。现在，从左往右数，线的颜色依次是 $1,$ $ 3,$ $ 3,$ $ 2$，厚度依次是 $2,$ $ 1,$ $ 1,$ $ 1$。
* 把左数第 $4$ 根线染成颜色 $1$。折叠绳子使得 原本到左端点的距离为 $2$ 的端点 变为 新的左端点。现在，从左往右数，线的颜色依次是 $3, 1$，厚度依次是 $2, 3$。

通过下述步骤，只需花费 $1$，就可以使得最终的绳子中包含颜色 $2$ 和 $3$。
* 折叠绳子使得 原本到左端点的距离为 $3$ 的端点 变为 新的左端点。现在，从左往右数，线的颜色依次是 $3,$ $ 2,$ $ 1$，厚度依次是 $2,$ $ 2,$ $ 1$。
* 把左数第 $3$ 根线染成颜色 $2$。折叠绳子使得 原本到左端点的距离为 $2$ 的端点 变为 新的左端点。现在，从左往右数，线的颜色依次是 $2, 3$，厚度依次是 $3, 2$。

#### 样例解释 2
通过下述步骤，只需花费 $2$，就可以使得最终的绳子中包含颜色 $1$。
* 折叠绳子使得 原本到左端点的距离为 $2$ 的端点 变为 新的左端点。
* 把左数第 $1$ 根线染成颜色 $1$。折叠绳子使得 原本到左端点的距离为 $1$ 的端点 变为 新的左端点。注意这次染色的费用为 $2$，因为此时左数第 $1$ 根线的厚度为 $2$。
* 折叠绳子使得 原本到左端点的距离为 $3$ 的端点 变为 新的左端点。
* 折叠绳子使得 原本到左端点的距离为 $1$ 的端点 变为 新的左端点。

#### 数据范围与提示
对于 $15\%$ 的数据，$N\leqslant 15, M\leqslant 10$。  
对于另外 $30\%$ 的数据，$N\leqslant 10^5, M\leqslant 10$。  
对于另外 $10\%$ 的数据，$N\leqslant 10^5, M\leqslant 500$。  
对于另外 $20\%$ 的数据，$N\leqslant 10^5, M\leqslant 5000$。  
对于所有数据，$2\leqslant N\leqslant 10^6, 1\leqslant M\leqslant N, 1\leqslant C_i\leqslant M(1\leqslant i\leqslant N)$，在初始状态的绳子上，颜色 $1, 2, \ldots, M$ 都至少出现了一次。


---

---
title: "[IOI 2000] 邮局 加强版 加强版"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6246
tag: ['2000', '二分', 'IOI', 'O2优化', '凸完全单调性（wqs 二分）', '栈']
---
# [IOI 2000] 邮局 加强版 加强版
## 题目背景

> 看到你时总是感觉清风徐徐,
>
> 本以为和你相识不会是偶遇,
>
> 奈何你犹如过客、化作秋雨,  
>
> 只是经过我生命的一瓢柳絮,
>
> 从不会真正有童话似的结局.
>
> 我静静地写尽这些躁言丑句,
> 
> 本以为可以稍稍地缓解抑郁.
>
> 却是徒增一场悲伤的脑补剧.
>
> 你问我为什么说这么多?
>
> 因为这题是加强版的 [IOI2000]邮局.
## 题目描述

高速公路旁边有 $n$ 个村庄。高速公路表示为整数轴，每个村庄的位置用单个整数坐标标识。两个位置之间的距离是其整数坐标差的绝对值。

现在要建立  $m$ 个邮局，邮局将建在一些，但不一定是所有的村庄中。为了建立邮局，应选择他们建造的位置，使每个村庄与其最近的邮局之间的距离总和最小。

你要编写一个程序，已知村庄的位置和邮局的数量，计算每个村庄和最近的邮局之间所有距离的最小可能的总和。
## 输入格式

第一行包含两个整数，分别表示村庄的数量 $n$ 和邮局的数量 $m$。

第二行共 $n$ 个整数，表示每个村庄的坐标，第 $i$ 个整数表示第 $i$ 个村庄的坐标 $a_i$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
5 2
0 1 2 3 4
```
### 样例输出 #1
```
3
```
## 提示

#### 数据规模与约定

本题共五个测试点，各测试点信息如下：

| 测试点编号 | $n = $ | $a_i \leq $ |
| :----------: | :-------: | :----: |
| 1 | $50000$ | $6 \times 10^4$ |
| 2 | $150000$ | $2 \times 10^5$ |
| 3 | $299998$ | $5 \times 10^5$ |
| 4 | $499998$ | $10^6$ |
| 5 | $499999$ | $2\times 10^6$ |

对于全部的测试点，保证 $1 \leq m \leq n \leq 5 \times 10^5$，$0 \leq a_i \leq 2\times 10^6$，且 $a_i$ 的值在对应范围内均匀随机。

保证最终答案不超过 $10^9$。



---

---
title: "不可视境界线[环版本]"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6455
tag: ['动态规划 DP', '计算几何', '二分', '单调队列', 'Special Judge', '分治', '随机调整', '凸完全单调性（wqs 二分）']
---
# 不可视境界线[环版本]
## 题目背景

- 原题 : [P5617 [MtOI2019]不可视境界线](https://www.luogu.com.cn/problem/P5617)

**附** : [关于本题的`SPJ`和数据的一些信息](https://www.luogu.com.cn/paste/tmwvh5vh)

若出现卡精度或数据出锅,吊打标算等情况,请联系出题人。
## 题目描述

有 $n$ 个半径为 $r$ 的圆,画在一个长度为 $L$ 的首尾相接的纸环上。

所有的圆心都在同一高度,可以看做在纸上画一个数轴然后卷起来,圆心的位置用这个数轴上的点描述。

如果无法理解纸环上圆的分布,可以查看样例解释以及子问题。

要求选出 $k$ 个圆,使得所有圆的并面积最大。

注意,您需要回答确切的选取方案而不是仅仅给出最大并面积。
## 输入格式

第一行包含四个整数 $n,k,r,L$ ,意义如题目所述。

第二行包含 $n$ 个整数,第 $i$ 个整数 $p[i]$ 描述了第 $i$ 个圆心在纸环上的位置(数轴上的坐标)。

对于 $2<i<n$ ,有 $p[i-1]<p[i]$。
## 输出格式

一行包含 $k$ 个整数,分别表示您选取的圆的编号,由`SPJ`来计算并面积。

您需要保证这些编号严格递增,并且在 $[1,n]$ 以内,否则被认为不合法而不得分。

与标准答案**相对误差**不超过 $10^{-9}$ ,**且绝对误差**不超过 $0.1$ 则认为正确。

通过估算,答案不会超过 $10^{12}$ 量级。
## 样例

### 样例输入 #1
```
5 3 10 30
0 7 14 21 28 
```
### 样例输出 #1
```
2 3 5 
```
### 样例输入 #2
```
10 3 10 65
0 7 15 24 30 36 41 49 57 63 
```
### 样例输出 #2
```
3 6 9
```
### 样例输入 #3
```
30 10 50 169
0 7 14 21 28 35 42 45 51 55 61 65 68 75 79 83 87 94 97 105 113 118 126 133 140 147 151 156 163 167 
```
### 样例输出 #3
```
3 5 8 11 15 19 21 24 27 30 
```
## 提示

**样例解释** : 

- **样例1** : 最终的并面积约为 $565.871835$。

圆的分布如图所示,其中, $⊙A$ 和 $⊙A2$ 是同一个圆, $⊙B$ 和 $⊙B2$ 是同一个圆。

可以视作向右平移 $L=30$ 个单位长度而得,事实上就相当于在纸环上绕了一圈回到起点。

由于是同一个圆,被红色部分覆盖的面积不能重复计算,最大的并面积即为蓝色部分的面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/g2dk0sqv.png)

- **样例2** : 最终的并面积约为 $942.477796$。

- **样例3** : 最终的并面积约为 $16817.058547$。

**数据范围与约定** :

| 子任务编号 | n | k | 时限 |
| :--: | :--: | :--: | :--: |
| 1 | $10$ | - | $\texttt{1s}$ |
| 2 | $100$ | - | $\texttt{1s}$ |
| 3 | $2000$ | - | $\texttt{1.6s}$ |
| 4 | $3\times 10^4$ | $100$ | $\texttt{2.2s}$ |
| 5 | $1\times 10^5$ | - | $\texttt{3s}$ |

时限在 `std` 耗时的两倍以上。

对于所有的数据, $n\leq 10^5$，$10\leq r\leq 2000$，$0\leq p[i]< L\leq 10^8$，$4r<L$，$3\leq k \leq n$。

表格中均为上界。注意,一些下界限制可能帮助省去了问题的某些边界情况。


---

---
title: "[ICPC 2014 WF] Messenger"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6897
tag: ['计算几何', '2014', '二分', 'Special Judge', 'ICPC']
---
# [ICPC 2014 WF] Messenger
## 题目描述

Misha needs to send packages to his friend Nadia. Both of them often travel across Russia, which is very large. So they decide to hire a messenger. Since the cost of the messenger service depends on the time it takes to deliver the package, they need your help to optimize a little bit.

Assume Misha and Nadia move on a two-dimensional plane, each visiting a sequence of places and moving along straight line segments from place to place. Your task is to find the shortest possible delivery time given their two paths.

Misha hands the package to the messenger at some point along his path. The messenger moves without delay along a straight line from the pick-up to intercept Nadia, who is traveling along her path. Misha, Nadia and the messenger move with a constant speed of $1$ distance unit per time unit. The delivery time is the time between Misha handing over the package and Nadia receiving it.
## 输入格式

The input consists of a single test case. The test case contains two path descriptions, the first for Misha and the second for Nadia. Each path description starts with a line containing an integer $n$, the number of places visited ($2 \leq n \leq 50\, 000$). This is followed by $n$ lines, each with two integers $x_ i$ and $y_ i$ specifying the coordinates of a place ($0 \leq x_ i, y_ i \leq 30\, 000$). Coordinates of the places are listed in the order in which they are to be visited, and successive places do not have the same coordinates.

Misha and Nadia start their journeys at the same time, visiting the places along their paths without stopping. The length of each path is at most $10^6$. The package must be picked up at the latest when Misha reaches his final place and it must be delivered at the latest when Nadia reaches her final place.
## 输出格式

Display the minimal time needed for delivery. Give the answer with an absolute error of at most $10^{-3}$ or a relative error of at most $10^{-5}$. If the package cannot be delivered, display impossible instead.
## 样例

### 样例输入 #1
```
2
0 0
0 10
2
4 10
4 0

```
### 样例输出 #1
```
4.00000

```
### 样例输入 #2
```
2
0 0
1 0
3
2 0
3 0
3 10

```
### 样例输出 #2
```
5.00000

```
## 提示

Time limit: 3000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

题目描述：  
平面上有两个移动的点 A,B，其中 A 想要向 B 发送一条信息。两个点会同时出发，各自沿着一个折线移动到终点为止。A 会在移动的途中发送一条信息，这条信息可以视作一个点 C，它会沿一条射线匀速运动，当 C 与 B 重合时，B 即可收到该信息。

A,B,C 的移动速度都是 1 单位长度每秒，A 最晚在它到达终点时发出信息，B 最晚需要在它到达终点时收到信息。令 $t_A$ 代表发送信息的时间，$t_B$ 代表接收信息的时间，那么你需要最小化 $t_B-t_A$ 的值。特别地，如果 B 无论如何都无法收到信息，你需要输出 `impossible`。

输入格式：

第一行包含一个整数 $n$，代表 A 经过折线的点数；  
下面 $n$ 行，每行输入两个整数 $x_i,y_i$，依次描述 A 所走折线的点。  
下面一行包含一个整数 $m$，B 过折线的点数；  
下面 $m$ 行，每行输入两个整数 $u_i,v_i$，描述 B 所走折线。

输出格式：

一行，输出一个实数，代表答案。若无法满足，则输出`impossible`。


---

---
title: "草地"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7274
tag: ['O2优化', '动态树 LCT', '整体二分']
---
# 草地
## 题目描述

给定一 $n \times m$ 的网格，其中每个格子均有颜色，可以为黑色或白色。

现可以进行若干次操作。一次操作中，你需选定上、下、左和右中的一个方向，然后，对于每个黑色的格子，若其指定方向上对应的位置不为网格的边界，则对应的那个格子变为黑色。

求：至少进行几次操作，才能使任意两个黑色格子八连通。八连通的定义可参考【提示/说明】部分。
## 输入格式

第一行两个整数 $n,m$（$1 \leq n,m \leq 10^3$），表示网格的大小。  
接下来 $n$ 行，每行一个长为 $m$ 的 01 字符串，第 $i$ 个串的第 $j$ 位为 $1$ 则表示第 $i$ 行 $j$ 列的格子是黑色，否则是白色。
## 输出格式

一行一个整数，最少的操作次数。
## 样例

### 样例输入 #1
```
5 4
1100
1000
0011
0000
0001
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
8 10
0000000011
0000000000
0000000000
0000000010
0000000000
0001010100
0000000000
0001000100
```
### 样例输出 #2
```
3
```
## 提示

----

**【样例解释 #1】**

对于第一组样例，一开始的网格如图（1）所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/7amyon0v.png)

（1）

进行一次操作，选择下方向，网格会变为图（2）所示的样子（标红的是新变为黑色的格子），此时任意两个黑格都八连通。

![](https://cdn.luogu.com.cn/upload/image_hosting/9aszlhed.png)

（2）

----

**【数据范围】**

**本题采用捆绑测试**

- Subtask 1（$10$ 分）：保证 $n, m\leq 3$。
- Subtask 2（$10$ 分）：保证 $n, m \leq 80$。
- Subtask 3（$5$ 分）：保证黑色格子的数量不超过 $20$。
- Subtask 4（$5$ 分）：保证 $m = 1$。
- Subtask 5（$25$ 分）：保证 $n, m \leq 300$。
- Subtask 6（$45$ 分）：没有特殊限制。

对于 $100 \%$ 的数据，保证 $1 \leq n,m \leq 10^3$，至少有一个黑色格子。

**八连通的定义**

两个黑色格子八连通，当且仅当在它们之间有公共顶点或公共边，或存在一个黑色格子同时与它们八连通。

用比较通俗的话说，就是它们在只能向周围相邻的八个格子行走，且只能经过黑色格子的条件下相互可达。


---

---
title: "[USACO21JAN] Minimum Cost Paths P"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7294
tag: ['二分', 'USACO', '2021', 'O2优化', '凸包', '单调栈', '组合优化', '保序回归']
---
# [USACO21JAN] Minimum Cost Paths P
## 题目描述

Farmer John 的牧草地可以看作是一个$N×M$（$2≤N≤10^9, 2≤M≤2⋅10^5$）的正方形方格组成的二维方阵（想象一个巨大的棋盘）。对于 $x∈[1,N],y∈[1,M]$，从上往下第 $x$ 行、从左往右第 $y$ 列的方格记为 $(x,y)$。此外，对于每一个 $y∈[1,M]$，第 $y$ 列拥有一个代价 $c_y$（$1≤c_y≤10^9$）。

Bessie 从方格 $(1,1)$ 出发。如果她现在位于方格 $(x,y)$，则她可以执行以下操作之一：

-  如果 $y<M$，Bessie 可以以 $x^2$ 的代价移动到下一列（$y$ 增加一）。
- 如果 $x<N$，Bessie 可以以 $c_y$ 的代价移动到下一行（$x$ 增加一）。 

给定 $Q$（$1≤Q≤2⋅10^5$）个独立的询问，每个询问给定 $(x_i,y_i)$（$x_i∈[1,N],y_i∈[1,M]$），计算 Bessie 从 $(1,1)$ 移动到 $(x_i,y_i)$ 的最小总代价。
## 输入格式

输入的第一行包含 $N$ 和 $M$。

第二行包含 $M$ 个空格分隔的整数 $c_1,c_2,…,c_M$。

第三行包含 $Q$。 

最后 $Q$ 行每行包含两个空格分隔的整数 $x_i$ 和 $y_i$。
## 输出格式

输出 $Q$ 行，为每个询问的答案。

注意本题计算中所使用的整数大小可能需要使用 64 位整数型（例如，C/C++ 中的 long long）。
## 样例

### 样例输入 #1
```
5 4
1 100 100 20
20
1 1
2 1
3 1
4 1
5 1
1 2
2 2
3 2
4 2
5 2
1 3
2 3
3 3
4 3
5 3
1 4
2 4
3 4
4 4
5 4
```
### 样例输出 #1
```
0
1
2
3
4
1
5
11
19
29
2
9
20
35
54
3
13
29
49
69
```
## 提示

#### 样例 1 解释

输出以方阵形式表示如下：

```
    1  2  3  4
  *--*--*--*--*
1 | 0| 1| 2| 3|
  *--*--*--*--*
2 | 1| 5| 9|13|
  *--*--*--*--*
3 | 2|11|20|29|
  *--*--*--*--*
4 | 3|19|35|49|
  *--*--*--*--*
5 | 4|29|54|69|
  *--*--*--*--*
```

#### 测试点性质：

 - 测试点 1-3 满足 $N,M≤2000$。
 - 测试点 4-8 满足 $c_2>c_3>⋯>c_M$。
 - 测试点 9-15 满足 $N≤2⋅10^5$。
 - 测试点 16-20 没有额外限制。

供题：Benjamin Qi 


---

---
title: "[THUSC 2017] 巧克力"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7450
tag: ['动态规划 DP', '2017', '二分', 'Special Judge', '随机化', 'THUSC']
---
# [THUSC 2017] 巧克力
## 题目描述

「人生就像一盒巧克力，你永远不知道吃到的下一块是什么味道。」

明明收到了一大块巧克力，里面有若干小块，排成 $n$ 行 $m$ 列。每一小块都有自己特别的图案 ，它们有的是海星，有的是贝壳，有的是海螺……其中还有一些因为挤压，已经分辨不出是什么图案了。明明给每一小块巧克力标上了一个美味值 $a_{i,j}$（$0\le a_{i,j}\le 10^6$），这个值越大，表示这一小块巧克力越美味。

正当明明咽了咽口水，准备享用美味时，舟舟神奇地出现了。看到舟舟恳求的目光，明明决定从中选出一些小块与舟舟一同分享。

舟舟希望这些被选出的巧克力是连通的（两块巧克力连通当且仅当他们有公共边），而且这些巧克力要包含至少 $k$（$1\le k\le 5$）种。而那些被挤压过的巧克力则是不能被选中的。

明明想满足舟舟的愿望，但他又有点「抠」，想将美味尽可能多地留给自己。所以明明希望选出的巧克力块数能够尽可能地少。如果在选出的块数最少的前提下，美味值的中位数（我们定义 $n$ 个数的中位数为第 $\left\lfloor\frac{n+1}{2}\right\rfloor$ 小的数）能够达到最小就更好了。

你能帮帮明明吗？
## 输入格式

每个测试点包含多组测试数据。

输入第一行包含一个正整数 $T$（$1\le T\le 5$），表示测试数据组数。

对于每组测试数据：

输入第一行包含三个正整数 $n,m$ 和 $k$；

接下来 $n$ 行，每行 $m$ 个整数，表示每小块的图案 $c_{i,j}$。若 $c_{i,j}=-1$ 表示这一小块受到过挤压，不能被选中；

接下来 $n$ 行，每行 $m$ 个整数，表示每个小块的美味值 $a_{i,j}$。
## 输出格式

输出共包括 $T$ 行，每行包含两个整数，用空格隔开，即最少的块数和最小的美味值中位数。

若对于某组测试数据，不存在任意一种合法的选取方案，请在对应行输出两个 $-1$。
## 样例

### 样例输入 #1
```
1
5 4 5
3 4 3 4
5 5 -1 5
-1 4 5 5
5 5 4 2
1 -1 2 4
1 3 1 1
3 2 3 3
4 4 4 5
8 9 9 5
7 2 6 3
```
### 样例输出 #1
```
9 5
```
## 提示

| 测试点编号 | $n,m$ 的限制 | $c_{i,j}$ 的限制 | 部分分说明 |
| :----------: | :----------: | :----------: | :----------: |
| 1 | $n=1,1\le m\le233$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le n\times m$ | $\text{A}$ |
| 2 | $1\le n\times m\le 20$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le n\times m$ | $\text{A}$ |
| 3~4 | $n=2,m=15$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le n\times m$ | $\text{A}$ |
| 5~6 | $1\le n\times m\le 30$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le n\times m$ | $\text{A}$ |
| 7~9 | $1\le n\times m\le 50$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le8$ | $\text{A}$ |
| 10 | $1\le n\times m\le 233$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le8$ | $\text{A}$ |
| 11~12 | $1\le n\times m\le 233$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le8$ | $\text{B}$ |
| 13~15 | $1\le n\times m\le 233$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le14$ | $\text{B}$ |
| 16~20 | $1\le n\times m\le 233$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le n\times m$ | $\text{B}$ |
| 21 | $1\le n\times m\le 233$ | $c_{i,j}=-1$ 或 $1\le c_{i,j}\le n\times m$ | 该测试点不计分。 |

$\text{A}$:若输出的最少块数均正确，但最小中位数存在错误，选手可以获得该测试点 $80\%$ 的分数。\
$\text{B}$:若输出的最少块数均正确，但最小中位数存在错误，选手可以获得该测试点 $60\%$ 的分数。


---

---
title: "「C.E.L.U-03」布尔"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7843
tag: ['倍增', 'O2优化', '2-SAT', '动态树 LCT', '整体二分']
---
# 「C.E.L.U-03」布尔
## 题目描述

给你 $n$ 个布尔变量和 $m$ 个限制，设 $s_i$ 为 $i$ 的取值。第 $i$ 个限制形如 $s_{u_i}$ 为 $x_i$ 则 $s_{v_i}$ 必须为 $y_i$，同时如果 $s_{v_i}$ 为 $y_i$ 则 $s_{u_i}$ 必须取 $x_i$。  
一共 $q$ 次询问，每次询问给出一个区间 $l,r$。求最少把 $l,r$ 划分成多少段连续的区间，使得每段里的限制都可以得到一组合法解。如果无论如何都无法得到合法解，输出 `-1`。
## 输入格式

第一行三个数，$n,m,q$。  
接下来 $m$ 行每行四个数，代表 $u_i,x_i,v_i,y_i$。  
接下来 $q$ 行每行两个数，代表 $l_i,r_i$。
## 输出格式

对于每个询问输出一个数作为答案，如果无法得到答案输出 `-1`。
## 样例

### 样例输入 #1
```
3 4 2
1 0 2 0
1 1 3 0
3 0 2 0
1 1 2 1
1 3
3 4
```
### 样例输出 #1
```
2
1
```
### 样例输入 #2
```
4 5 3
1 1 2 1
2 0 3 0
4 1 1 0
2 1 4 0
4 0 3 0
1 4
2 5
3 5
```
### 样例输出 #2
```
1
2
1
```
## 提示

**样例解释一**   
对于第一个询问，可以分成 $[1,2]$ 和 $3$ 两段。  
对于第二个询问，分成 $[3,4]$  一段。  

**样例解释二**   
对于第一个询问，分成 $[1,4]$  一段。  
对于第二个询问，可以分成 $[2,3]$ 和 $[4,5]$ 两段。  
对于第三个询问，分成 $[3,5]$  一段。  

| 数据编号| $n\leq$ | $m\leq$| $q\leq$|
|:---:|:---:|:---:|:---:|
|$1$|$30$|$100$|$300$|
|$2\sim 4$|$300$|$10^3$|$10^3$|
|$5\sim 7$|$10^4$|$5\times10^4$|$10^6$|  
|$8\sim 10$|$10^5$|$6\times10^5$|$10^6$|   

对于 $100\%$ 的数据，$1\le n\le10^5,1\le m\le6\times10^5,1\le q\le10^6,1\le u,v\le n,1\le l\le r\le m,x,y\in \{0,1\}$


---

---
title: "[JRKSJ R4] Salieri"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8147
tag: ['二分', '2022', '洛谷原创', 'O2优化', '可持久化线段树', '虚树', 'AC 自动机']
---
# [JRKSJ R4] Salieri
## 题目背景

![a358071f95cad1c8ccd29cc83a3e6709c83d518e.jpg](https://s2.loli.net/2021/12/24/Oi251TnFP7SflQp.jpg)  

~~【记得到番里面去把“萨列里谱不出莫扎特的曲子”这句话找到】~~ 最终还是没能找到，哪位看过《命运石之门0》的兄弟能帮我找找？
## 题目描述

Salieri 发现了 $n$ 种制作音乐的模式，他将第 $i$ 种模式表示为一个字符串 $s_i$，这种模式所带来的初始优美度为 $v_i$。  
Salieri 现在想制作 $m$ 首乐曲，每次他的灵感可以被表示成一个字符串 $S$。设 $cnt_i$ 为 $s_i$ 在 $S$ 中的出现次数，则采用 $i$ 模式制作的乐曲最终的优美度 $w_i=cnt_i\times v_i$。  
Salieri 当然希望制作出来的乐曲最终优美度越大越好，但是他发现此灵感下前 $k-1$ 优美的乐曲已经被 Mozart 制作过了，他只能制作第 $k$ 优美的乐曲。请你求出这个最终优美度。  

形式化题意：给出 $n$ 个字符串 $s_i$，每个字符串有一个权值 $v_i$。$m$ 次询问每次给出一个字符串 $S$ 和一个常数 $k$。设 $cnt_i$ 为 $s_i$ 在 $S$ 中的出现次数，求 $cnt_i\times v_i$ 第 $k$ 大的值。
## 输入格式

第一行两个数，$n,m$。  
接下来 $n$ 行每行一个字符串 $s_i$ 和一个数 $v_i$。  
接下来 $m$ 行每行一个字符串 $S$ 和一个数 $k$。
## 输出格式

每行一个数，代表答案。
## 样例

### 样例输入 #1
```
4 2
ab 2
a 2
ba 2
b 1
bbaba 2
aab 1
```
### 样例输出 #1
```
4
4
```
### 样例输入 #2
```
15 4
ba 18
cbc 74
aac 54
ba 77
a 66
c 96
cdb 47
dc 45
cb 62
db 88
dda 93
db 34
b 81
acd 100
da 80
bcaacbbdcbabcda 4
bccac 3
abdbaca 5
cbdaaaacaaca 3
```
### 样例输出 #2
```
124
66
77
108
```
## 提示

设 $L$ 为 $s$ 长度总和。

| $\text{Subtask}$|$n,m\le$|$L\le$|特殊性质| 分值 |
|:-:|:-:|:-:|:-:| :-: |
|$1$|$10^3$|$5\times10^3$|无| $10$ |
|$2$|$10^3$|$10^5$|无| $20$ |
|$3$|$10^5$|$5\times10^5$|$k=1$| $10$ |
|$4$|$3\times10^4$|$2\times10^5$|$k\le5$| $20$ |
|$5$|$3\times10^4$|$2\times10^5$|无|  $20$ | 
|$6$|$10^5$|$5\times10^5$|无|  $20$ |

对于 $100\%$ 的数据，$1\le n,m\le10^5$，$L\le5\times10^5$。

无论何时 $\sum |S|$ 与 $L$ 同阶，$s$ 和 $S$ 中只会出现 $\texttt a,\texttt b,\texttt c,\texttt d$ 四种字符，$v_i\le10^3$，$k\le n$。


![QQ截图20220128131353.png](https://s2.loli.net/2022/01/28/MJchEuxsF1QI46V.png)


---

---
title: "「EZEC-11」雪的魔法"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8182
tag: ['动态规划 DP', '2022', '洛谷原创', 'O2优化', '分治', '线性规划', '分块', '整体二分', '洛谷月赛']
---
# 「EZEC-11」雪的魔法
## 题目背景

Muxii 是一个雪魔法师。只要他挥起魔法棒，念出神秘的咒语，雪花就会从天而降，在地面上一点一点地积累起厚厚的雪层。正因 Muxii 魔力高超，上帝任命 Muxii 掌管整个世界的雪。

某天，上帝给 Muxii 下达了一个任务：他需要让一个长为 $n$ 的地面上下雪。其中，第 $i$ 个位置的积雪厚度需要达到 $a_i$（$a_i\ge0$，“达到 $a_i$” 指不能低于也不能超过 $a_i$）。然而，上帝不知道的是，Muxii 的能力有限，他每次施法只能让长度 $\le m$ 的区间内下雪 1s，使得这个区间内的积雪厚度增加 $1$。由于任务急迫，Muxii 想要知道，若要完成某些区间的任务，他至少要施法多少次。
## 题目描述

定义初始数列为每个数字都为 $0$ 的数列。

定义一次操作为将数列的一个区间中每一个数的值增加 $1$，规定该区间的长度不能超过 $m$。

给定一个长度为 $n$ 的数列 $a$，第 $i$ 个数为 $a_i$。

你需要回答 $q$ 次询问。每次询问给定 $l,r$，你需要回答将一个长度为 $r-l+1$ 的初始数列变为 $a$ 中的 $[l,r]$（即数列 $a_l$, $a_{l+1}$, $\cdots$, $a_r$）至少需要多少次操作。
## 输入格式

第一行三个整数 $n,m,q$。

第二行 $n$ 个整数，第 $i$ 个为 $a_i$。

接下来 $q$ 行，每行两个整数，表示 $l,r$。
## 输出格式

$q$ 行，每行一个整数，表示至少需要的操作次数。
## 样例

### 样例输入 #1
```
5 4 1
1 1 2 1 1
1 5
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
10 3 3
4 8 1 2 9 7 4 1 3 5
1 10
3 8
5 5
```
### 样例输出 #2
```
22
10
9
```
## 提示

**「样例 1 说明」**

一个长度为 $5$ 的初始数列为 $0$ $0$ $0$ $0$ $0$。

第一次操作为，将区间 $[1,3]$ 中每一个数，即第 $1$、$2$、$3$ 个数的值分别增加 $1$。经过该操作后，数列变为  $1$ $1$ $1$ $0$ $0$。

第二次操作为，将区间 $[3,5]$ 中每一个数，即第 $3$、$4$、$5$ 个数的值分别增加 $1$。经过该操作后，数列变为  $1$ $1$ $2$ $1$ $1$。

**「数据范围与约定」**

- Subtask 1（1 point）：$m=1$。
- Subtask 2（4 points）：$m=n$。
- Subtask 3（10 points）：$n,q\le300$。
- Subtask 4（10 points）：$n,q\le5\times10^3$。
- Subtask 5（15 points）：$m\le5$。
- Subtask 6（15 points）：$m\le100$。
- Subtask 7（20 points）：$n,q\le5\times10^4$。
- Subtask 8（25 points）：无特殊限制。

对于 $100\%$ 的数据，保证 $1\le m\le n\le10^5$，$1\le q\le10^5$，$0\le a_i\le10^9$，$1\le l\le r\le n$。


---

---
title: "[省选联考 2022] 最大权独立集问题"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8294
tag: ['各省省选', '2022', 'O2优化', '树形 DP', '凸完全单调性（wqs 二分）']
---
# [省选联考 2022] 最大权独立集问题
## 题目描述

小 E 喜欢出最大权独立集问题。

接下来，他还想了 $n$ 道最大权独立集问题。

小 E 有 $n$ 个 AI，编号为 $1 \sim n$。

开始时第 $i$ 个 AI 里面存有 $d_i$ 道小 E 事先出好的最大权独立集问题。

有些 AI 之间可以互相通信，对于所有的 $2 \leq i \leq n$ ，第 $i$ 个 AI 可以和第 $c_i$ 个 AI 互相通信。其中 $c_i < i$，且相同的 $c_i$ 出现不超过 $2$ 次。所以，这些 AI 连成了一个二叉树的形状。此外，其他对 AI 不可以互相通信。

小 E 需要暂时断开这些 AI 之间的连接。他只能逐一断开 AI 之间的连接。两个原本能够互相通信的 AI 在断开它们之间的连接之前，会互相交换存在里面的所有题目，具体请见样例。

小 E 希望在断掉所有连接之后，参与交换的题目数量最少。
他想叫你帮他解决这个问题，还说如果你成功解决了这个问题，那么在出那些最大权独立集问题的时候，他会帮你提交一份标程代码。
## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个整数，第 $i$ 个表示 $d_i$。

第三行 $n - 1$ 个正整数，第 $i$ 个表示 $c_{i+1}$。
## 输出格式

一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
2 1 3
1 1
```
### 样例输出 #1
```
7
```
## 提示

**【样例解释 #1】**

一种最优的方案是：断开 $1$ 号与 $2$ 号 AI 之间的连接，这样需要交换 $2 + 1 = 3$ 道题；然后断开 $1$ 号与 $3$ 号 AI 之间的连接，这样需要交换 $1 + 3 = 4$ 道题。所以答案是 $7$。

**【数据范围】**

保证 $1 \le c_i \le i$，且相同的 $c_i$ 最多出现两次。

保证 $1 \le d_i \le {10}^9$。

| 测试点编号 | $n \leq$ |
|:-:|:-:|
| $1 \sim 3$ | $10$ |
| $4 \sim 7$ | $100$ |
| $8 \sim 11$ | $500$ |
| $12 \sim 16$ | $1000$ |
| $17 \sim 25$ | $5000$ |


---

---
title: "「Wdoi-2」禁断之门对面，是此世还是彼世"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8544
tag: ['动态规划 DP', '二分', '洛谷原创', 'O2优化', '凸完全单调性（wqs 二分）', '洛谷月赛']
---
# 「Wdoi-2」禁断之门对面，是此世还是彼世
## 题目背景

或许是后户之国轻易不与外界联系，或许是神职所限，又或许是性格喜好的原因，摩多罗作为最初建立幻想乡的几位贤者之一，和其他贤者之间的联系并不频繁。其他如八云紫、茨木华扇等贤者均亲身走在幻想乡之中，而摩多罗却置身之外。

耗费神力发动全幻想乡级别的异变，看似规模宏大，其实并未对幻想乡造成真正的伤害，只是让一群笨蛋妖精狂躁了些而已。 

谁也不知道门后的秘神心中真正的想法。
## 题目描述

给定一场长度为 $n$ 的正整数序列 $a$ 和一个长度为 $m$ 的正整数序列 $b$。

现在蓝根据序列 $a$ 与序列 $b$ 构造了一个 $n$ 行 $m$ 列的正整数矩阵 $A$ 满足 $A_{i,j}=a_ib_j$，你需要构造 $n+1$ 行 $t$ 列的正整数矩阵 $B$ 满足以下条件：

- 矩阵的每个元素取值在 $[1,m]$ 间；
- 矩阵同一行的元素**两两**不相同；
- 矩阵的每列**相邻元素**不同；
- 在所有满足上面三项要求的矩阵中**最小化**下式：
$$f(B)=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{t}\sum\limits_{k=\min(B_{i,j},B_{i+1,j})}^{\max(B_{i,j},B_{i+1,j})}A_{i,k}$$

请输出构造出的 $B$ 矩阵的 $f(B)$ 的值模 $10^9+7$ 的结果。
## 输入格式

第一行三个整数 $n,m,t$。

接下来一行 $n$ 个整数 $a_1,a_2,\cdots a_n$，含义如题面中所述。

接下来一行 $m$ 个整数 $b_1,b_2,\cdots b_m$，含义如题面中所述。


## 输出格式

输出一行，表示构造出的 $B$ 矩阵的 $f(B)$ 的值模 $10^9+7$ 的结果。
## 样例

### 样例输入 #1
```
2 2 2
9 9
6 1
```
### 样例输出 #1
```
252
```
### 样例输入 #2
```
10 10 10
2 8 10 10 10 2 5 8 9 3
2 1 5 2 10 7 8 9 10 6

```
### 样例输出 #2
```
8040

```
## 提示

### 样例解释 1

根据题意，可以构造出矩阵 $A=\begin{bmatrix}54 & 9 \\ 54 & 9 \end{bmatrix}$。

你需要构造出的 $3$ 行 $2$ 列的矩阵 $B=\begin{bmatrix}1 & 2 \\ 2 & 1 \\ 1 & 2 \end{bmatrix}$，此时 $f(B)=252$ 为最小值

可以证明 $f(B)=252$ 为所有情况中，$f(B)$ 的最小值。

### 数据范围及约定

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|}\hline
\textbf{Subtask} & \bm{n \le } & \bm{m \le } & \bm{t \le } & \textbf{特殊性质} & \textbf{分值}\\\hline
1 & 10 & 10 & 10 & - & 5 \\\hline
2 & 100 & 100 & 100 & - & 5 \\\hline
3 & 10^3 & 10^3 & 10^3 & - & 15 \\\hline
4 & 5\times 10^4 & 5\times 10^4 & 5\times 10^4 & - & 30 \\\hline
5 & 5\times 10^5 & 5\times 10^5 & 5\times 10^5 & \textbf{A} & 10 \\\hline
6 & 5\times 10^5 & 5\times 10^5 & 5\times 10^5 & \textbf{B} & 10 \\\hline
7 & 5\times 10^5 & 5\times 10^5 & 5\times 10^5 & - & 25 \\\hline
\end{array}$$

- **特殊性质** $\textbf{A}$：保证 $a_i=1$；
- **特殊性质** $\textbf{B}$：保证 $m=t$。

对于全部数据，保证 $1\le a_i, b_i\le 10^9$，$1\le n, m, t\le 5\times 10^5 $，$t\le m$。保证数据有解。


---

---
title: "「DTOI-4」中位数"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P8978
tag: ['动态规划 DP', '二分', '单调队列', '2023', '洛谷原创', 'O2优化']
---
# 「DTOI-4」中位数
## 题目描述

给定一个长度为 $n$ 的整数序列 $a$，你可以进行以下操作不超过 $k$ 次：

- 选择一个区间 $[l, r]$ 满足 $1 \leq l \leq r \leq n$，并将 $[l, r]$ 中的所有数替换为这个区间的中位数。

你要使得操作后 $a$ 的**最小值最大**。

关于此处中位数的定义：对于一个长度为 $len$ 的序列，其中位数定义为该序列中第 $\lceil \frac{len}{2} \rceil$ 小的数。
## 输入格式

第一行，两个整数 $n, k$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$。
## 输出格式

一行，表示经过不超过 $k$ 次操作后序列最小值的最大值。
## 样例

### 样例输入 #1
```
10 2
2 8 3 2 5 7 10 4 9 7
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
30 3
1 0 1 0 1 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 0 0 0 0 1 1 0 0 0 0
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
31 3
1 0 1 0 1 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 0 0 0 0 1 1 0 0 0 0 1
```
### 样例输出 #3
```
1
```
## 提示

| $\textbf{Subtask}$ | $n$ | 分值 |
| :------: | :------: | :------: |
| $1$ | $1 \leq n \leq 10$ | $10 \operatorname{pts}$ |
| $2$ | $1 \leq n \leq 100$ | $10 \operatorname{pts}$ |
| $3$ | $1 \leq n \leq 10^3$ | $10 \operatorname{pts}$ |
| $4$ | $1 \leq n \leq 10^4$ | $20 \operatorname{pts}$ |
| $5$ | $1 \leq n \leq 10^5$ | $20 \operatorname{pts}$ |
| $6$ | 无特殊限制 | $30 \operatorname{pts}$ |

对于 $100\%$ 的数据，$1 \leq n \leq 4 \times 10^5$，$0 \leq k \leq n$，$0 \leq a_i \leq 10^9$。


---

---
title: "「RiOI-03」A Journey to the Moonlight"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P9919
tag: ['洛谷原创', 'O2优化', '二分图', '生成函数', '分块', '快速数论变换 NTT', '洛谷月赛']
---
# 「RiOI-03」A Journey to the Moonlight
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/hi1cu7o7.png)

（图片来自 phigros 曲绘，侵删。）

[加强版链接](/problem/P10286)

KDOI 的业务发展到月亮上了。但是月亮上网速很慢，他们需要解决网速问题。

KDOI 的工作人员研发了一种新型无线局域网模块 Wife（WIreless Fidelity Extend），每个模块最多连接两个用户，并且可以选择为其中一位客户提供 $1$ 单位带宽。不过，无论有多少个模块同时为一位客户提供带宽，他的总带宽永远是 $1$。

公司的员工都很懒，经常 ppt 一鸽就是一个月。因此，他们也懒得为 Wife 贴上标签，也就是所有模块间不做区分。另外，为了节省电费，不能有两个模块的工作客户范围完全相同。

现在有 $n$ 个用户购买了服务。当 Wife 系统正式启动时，鹿由器发现了一个问题：可能有些用户没有宽带可以使用！快斗现在手里没有 Wife，只能抢来一个，牺牲一个用户的利益，按一定顺序给所有包括有宽带的用户使用。然而，没有宽带的用户们要求很苛刻，只要没有给他们按注册顺序连续地提供宽带，他们就会威胁鹿由器退钱。

快斗已经忘了他们的注册时间了，只能随机选一个 $1\sim n$ 的排列来决定提供宽带的顺序。为了让尝试的次数尽量小，他会调整 Wife 连接的用户。他想知道，要让这些顾客平息愤怒，需要尝试的最小期望次数是多少。

特别的，Wife 有两种型号。型号 $1$ 可以选择只连接一位，型号 $2$ 则只能连接两个不同客户。你需要分别计算出这两种型号的答案。

快斗自己肯定~~不~~会做，所以他要让你求出所有 $i\in[0,n]$ 的结果 $ans_i$。考虑到你如果一个一个汇报会累死的，仁慈的鹿由器会给你数组 $a$，让你输出 $\sum a_i\times ans_i$。


## 题目描述

#### 【形式化题意】

对于一个右部点为 $m$ 个的二分图 $G$，定义它的权值 $w(G)$ 如下：

- 选择一种匹配方案，标记第一个已匹配的右部点。如果不存在这样的点，那么标记第一个未匹配的右部点。
- 每次随机选择一个 $1,2,\cdots,m$ 的排列，当未匹配的右部点与被标记的点 **按标号顺序作为一个子段出现在排列中时** 停止操作。
- $w(G)$ 为在所有匹配方案中操作次数期望的 **最小值**。

将这个二分图 $G$ 定义为 **$k$ 合法** 的，当且仅当：

- 所有左部点的度数在 $k\sim 2$ 之间。
- 没有任意两个左部点，与其相邻的点组成的集合相同。

定义 $f(k,x)$ 为所有右部点 $x$ 个，左部点不进行区分的 $k$ 合法二分图 $G$ 的 $w(G)$ 之和。

给定 $n,k,a_{0\sim n}$，求 $\sum\limits^n_ia_if(k,i) \bmod998244353$。
## 输入格式

一行两个正整数，分别表示 $n$ 与 Wife 的型号 $k$。

第二行 $n+1$ 个非负整数，分别表示 $a_{0\sim n}$。
## 输出格式

一行一个非负整数，表示答案。
## 样例

### 样例输入 #1
```
2 1
1 1 1
```
### 样例输出 #1
```
15
```
### 样例输入 #2
```
3 2
1 1 1 1
```
### 样例输出 #2
```
40
```
### 样例输入 #3
```
12 1
1 1 4 5 1 4 1 9 1 9 8 1 0
```
### 样例输出 #3
```
721168027
```
## 提示

约定一个左部点连接了编号为 $x,y$ 的右部点表示为 $(x,y)$。

#### 【样例 1 解释】

对于 $n=0,1$，答案显然为 $1,2$。

对于 $n=2$，可能的二分图为（用每个左部点的邻接点组成的元组表示）：

$()$

$(1),(2),(1,2)$

$\{(1),(2)\},\{(1,2),(2)\},\{(1,2),(1)\},\{(1,2),(1),(2)\}$

期望相同的二分图被分为一组。答案为 $\dfrac21+\dfrac21\times3+\dfrac22\times4=12$，输出 $1\times1+1\times2+1\times12=15$。

#### 【样例 2 解释】

对于 $n=0,1,2$，答案为 $1,1,4$。

对于 $n=3$，可能的二分图为（用每个左部点的邻接点组成的元组表示）：

$()$

$(1,2),(1,3),(2,3)$

$\{(1,2),(1,3)\},\{(1,2),(2,3)\},\{(1,3),(2,3)\}$

$\{(1,2),(2,3),(1,3)\}$

答案为 $\dfrac61+\dfrac61\times3+\dfrac62\times3+\dfrac66=34$。

#### 【数据范围】

对于 $100\%$ 的数据，$0\le n\le1.5\times10^4$，$1\le k\le2$，$0\le a_i<998244353$。

**本题开启捆绑测试**

|$\text{Subtask}$|$\text{Score}$|$n\le $|$k\ge$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$0$|$5$|$5$|$1$||
|$1$|$10$|$500$|$2$||
|$2$|$20$|$500$|$1$|$a_i\equiv\dfrac1{i!}$|
|$3$|$20$|$1.5\times10^4$|$2$|$a_i\equiv\dfrac1{i!}$|
|$4$|$45$|$1.5\times10^4$|$1$||


---

