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
title: "【模板】最大团/最大独立集"
layout: "post"
diff: 省选/NOI-
pid: P12371
tag: ['搜索', 'Special Judge', '深度优先搜索 DFS', '剪枝', '折半搜索 meet in the middle']
---
# 【模板】最大团/最大独立集
## 题目描述

给定一个无向图 $G$，你需要对其分别求出：

- $G$ 的一组最大团。
- $G$ 的最大团个数。
- $G$ 的一组最大独立集。
- $G$ 的最大独立集个数。

$G$ 的最大团为 $G$ 的最大完全子图，完全图为各点间两两均有连边的图。

$G$ 的最大独立集为 $G$ 的最大零子图，零图为各点间两两均没有边的图。
## 输入格式

第一行两个正整数 $n$ 和 $m$，分别表示图 $G$ 的节点个数以及无向边条数。

接下来 $m$ 行，每行两个数 $u,v$ 表示一条无向边连接的两个节点。

图可能会有重边，不会有自环。
## 输出格式

第一行两个整数 $a,b$，分别表示图 $G$ 的最大团大小（即最大团的节点个数）以及最大团个数。

第二行 $a$ 个整数，表示最大团的点集。

第三行两个整数 $p,q$，分别表示图 $G$ 的最大独立集大小（即最大独立集的节点个数）以及最大独立集个数。

第四行 $p$ 个整数，表示最大独立集的点集。

如果有多个满足要求的点集，输出任意一组即可。
## 样例

### 样例输入 #1
```
6 7
1 2
2 3
3 4
4 1
3 5
5 4
2 6
```
### 样例输出 #1
```
3 1
3 4 5
3 2
1 3 6
```
## 提示

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/tjj1sy0t.png)

图 $G$ 的最大团分别为 $\{3,4,5\}$。

图 $G$ 的最大独立集分别为 $\{1,3,6\},\{1,5,6\}$。

### 数据范围

对于全部数据：$1\leq n\leq 50$，$0\leq m\leq 1225$，$1\leq u,v\leq n$。


---

---
title: "[GCPC 2023] Highway Combinatorics"
layout: "post"
diff: 省选/NOI-
pid: P13673
tag: ['2023', '数论', 'Special Judge', 'Fibonacci 数列', '随机化', 'ICPC', '折半搜索 meet in the middle']
---
# [GCPC 2023] Highway Combinatorics
## 题目描述

You are the new minister of transport in Berland.
Recently, you allowed free parking on a two lane road segment of $200$ metres length.
Since then, that road segment has constantly been jammed by parked cars due to some
genius drivers who had the idea to park their cars across both lanes...

![](https://cdn.luogu.com.cn/upload/image_hosting/x81bkouf.png)

:::align{center}
Jam caused by parking bus, [Nevermind2](https://commons.wikimedia.org/wiki/File:Moscow_traffic_congestion.JPG)
:::


However, this is not your concern.
You are more interested in parking some of your own cars on the road segment while it is empty.
More specifically, you want to park some of your cars in such a way that the number of different ways to fill the remaining empty space with cars is congruent to your lucky number $n$ modulo $10^9+7$.

![](https://cdn.luogu.com.cn/upload/image_hosting/ntad7154.png)

:::align{center}
Figure H.1: Visualization of Sample Output 1.
:::

Each car has a size of $1\times2$ metres, each of the two lanes is $1$ metre wide and $200$ metres long. You own more than $200$ cars which you could park on the road segment.

## 输入格式

The input consists of:
- One line with one integer $n$ ($0\leq n<10^9+7$), the desired number of possible ways to fill the road modulo $10^9+7$.

It can be proven that at least one valid solution exists for each possible value of $n$.

## 输出格式

Output the state of the two lanes in two lines.
Print "$\texttt{\#}$" for an occupied spot and "$\texttt{.}$" for an empty spot. Note that the two lines should have the same length of at least $1$ metre and at most $200$ metres, and the occupied spots must correspond to some parked cars. If your solution uses a road segment shorter than $200$ metres, the remaining part of the road segment is assumed to be blocked by parked cars. 
## 样例

### 样例输入 #1
```
10
```
### 样例输出 #1
```
##..#.......
....#.##....
```
### 样例输入 #2
```
27
```
### 样例输出 #2
```
...##........
........##...
```


---

---
title: "[GCPC 2024] Jigsaw Present"
layout: "post"
diff: 省选/NOI-
pid: P13725
tag: ['2024', 'Special Judge', 'ICPC', '折半搜索 meet in the middle']
---
# [GCPC 2024] Jigsaw Present
## 题目描述

Julia is preparing a present for James. She will give him some of her $n$ jigsaw puzzles, where puzzle $i$ ($1 \leq i \leq n$) consists of $x_i$ pieces and has a difficulty $y_i$ (can be negative if the puzzle is very easy).

![](https://cdn.luogu.com.cn/upload/image_hosting/okr7isdn.png)

James is already very excited and would like to know in advance what he will get. Therefore, he used some of his criminal energy to gather information about the gift. In particular, he has managed to obtain an encrypted message containing the total difficulty and total number of pieces of all the puzzles that he will receive. 

Now he wonders whether it is worth spending some more time to decrypt the message. After all, it might be that this information is not enough to uniquely determine his gift. Since he was never good at these computer thingies, James asked for your assistance. Help him find out whether it is worth decrypting the message or not. If the answer is negative, you have to find two distinct gifts that result in the same encrypted message.

## 输入格式

The input consists of
- One line with an integer $n$ ($2 \leq n \leq 4\,096$), the number of puzzles that Julia owns.
- $n$ lines, the $i$th of which contains two integers $x_i$ and $y_i$ ($1 \leq x_i \leq 4\,096$, $\left|y_i\right| \leq 4\,096$), the number of pieces of puzzle $i$ and the difficulty of puzzle $i$.
## 输出格式

If James can uniquely determine his gift, then print "$\texttt{yes}$". Otherwise, you should print "$\texttt{no}$" followed by two lines,
  where each line contains the description of a present. The description of a present should start with an
  integer $k$, the number of puzzles, followed by $k$ distinct integers, the indices of the puzzles. 

  Note that the two presents have to be distinct, meaning that there should be at least one puzzle that is contained 
  in one present but not the other.

  If there are multiple presents that result in the same encrypted message, you can print any of them.
## 样例

### 样例输入 #1
```
5
2 -1
3 2
3 1
1 -3
1 1
```
### 样例输出 #1
```
no
3 2 4 5
2 1 3
```
### 样例输入 #2
```
4
2 -1
3 2
3 1
1 -3
```
### 样例输出 #2
```
yes
```
## 提示

In the first sample case, the first present consists of puzzles $2$, $4$, and $5$. The total number of pieces is $3 + 1 + 1 = 5$ and the total difficulty is $2 + (-3) + 1 = 0$. 
The second present consists of puzzles $1$ and $3$. The total number of pieces is $2 + 3 = 5$ and the total difficulty is $(-1) + 1 = 0$.
Thus, if James only knows the total number of pieces and the total difficulty, he cannot recover his present. So it is not worth to decode the message.

In the second sample case, no matter what gift Julia prepares, if James knows the total number of pieces and the total difficulty, he can recover his present. So he should decode the message.


---

---
title: "[USACO22DEC] Breakdown P"
layout: "post"
diff: 省选/NOI-
pid: P8906
tag: ['USACO', '2022', '最短路', '均摊分析', '折半搜索 meet in the middle']
---
# [USACO22DEC] Breakdown P
## 题目描述

Farmer John 的农场可以用一个带权有向图表示，道路（边）连接不同的结点，每条边的权值是通过道路所需的时间。每天，Bessie 喜欢从牛棚（位于结点 $1$）经过恰好 $K$ 条道路前往草地（位于结点 $N$），并希望在此限制下尽快到达草地。然而，在某些时候，道路停止维护，一条一条地开始破损，变得无法通行。帮助 Bessie 求出每一时刻从牛棚到草地的最短路径！

形式化地说，我们从一个 $N$ 个结点（$1 \le N \le 300$）和 $N^2$ 条边的带权有向完全图开始：对于 $1 \le i,j \le N$ 的每一对 $(i,j)$ 存在一条边（注意存在 $N$ 个自环）。每次移除一条边后，输出从 $1$ 到 $N$ 的所有路径中经过恰好 $K$ 条边（不一定各不相同）的路径的最小权值（$2 \le K \le 8$）。注意在第 $i$ 次移除后，该图还剩下 $N^2-i$ 条边。

路径的权值定义为路径上所有边的权值之和。注意一条路径可以包含同一条边多次或同一个结点多次，包括结点 $1$
和 $N$。
## 输入格式

输入的第一行包含 $N$ 和 $K$。

以下 $N$ 行每行包含 $N$ 个整数。第 $i$ 行的第 $j$ 个整数为 $w_{ij}(1 \le w_{ij} \le 10^8)$。

以下 $N^2$ 行，每行包含两个整数 $i$ 和 $j$（$1 \le i,j \le N$）。每对整数出现恰好一次。 
## 输出格式

输出 $N^2$ 行，为每一次移除后经过 $K$ 条边的路径的最小权值。如果不存在经过 $K$ 条边的路径则输出 $-1$。 
## 样例

### 样例输入 #1
```
3 4
10 4 4
9 5 3
2 1 6
3 1
2 3
2 1
3 2
2 2
1 3
3 3
1 1
1 2
```
### 样例输出 #1
```
11
18
22
22
22
-1
-1
-1
-1
```
## 提示

### 样例 1 解释

第一次移除后，最短的经过 $4$ 条边的路径为：

$$1 \rightarrow 2 \rightarrow 3 \rightarrow 2 \rightarrow 3$$

第二次移除后，最短的经过 $4$ 条边的路径为：

$$1 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 3$$

第三次移除后，最短的经过 $4$ 条边的路径为：

$$1 \rightarrow 3 \rightarrow 3 \rightarrow 3 \rightarrow 3$$

六次移除后，不再存在经过 $4$ 条边的路径。 

### 测试点性质

 - 对于 $2 \le T \le 14$，测试点 $T$ 满足 $K=\lfloor \dfrac{T+3}{2} \rfloor$。 


---

