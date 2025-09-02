---
title: "Airport Express"
layout: "post"
diff: 提高+/省选-
pid: UVA11374
tag: ['枚举', '最短路']
---

# Airport Express

## 题目描述

在$Iokh$市中，机场快线是市民从市内去机场的首选交通工具。机场快线分为经济线和商业线两种，线路、速度和价钱都不同。你有一张商业线车票，可以坐一站商业线，而其他时候只能乘坐经济线。假设换乘时间忽略不计，你的任务是找一条去机场最快的线路。

## 输入格式

输入包含多组数据。每组数据第一行为$3$个整数$N, S$和$E(2 \leq N \leq 500, 1 \leq S, E \leq 100)$，即机场快线中的车站总数，起点和终点（即机场所在站）编号。下一行包含一个整数$M(1 \leq M \leq 1000)$，即经济线的路段条数。以下$M$行每行3个整数$X, Y, Z(1 \leq X, Y \leq N, 1 \leq Z \leq 100)$，表示可以乘坐经济线在车站$X$和车站$Y$之间往返，其中单程需要$Z$分钟。下一行为商业线的路段条数$K(1 \leq K \leq 1000)$，以下$K$行是这些路段的描述，格式同经济线。所有路段都是双向的，但有可能必须使用商业车票才能到达机场。保证最优解唯一。

## 输出格式

对于每组数据，输出$3$行。第一行按访问顺序给出经过的各个车站（包括起点和终点），第二行是换乘商业线的车站编号（如果没有商业线车票，输出`Ticket Not Used`），第三行是总时间。

**注意**：输出时，每两组数据之间要加一个空行。并且不会过滤行末空格。

Translated by @andyli

## 样例 #1

### 输入

```
4 1 4
4
1 2 2
1 3 3
2 4 4
3 4 5
1
2 4 3
```

### 输出

```
1 2 4
2
5
```



---

---
title: "K Smallest Sums"
layout: "post"
diff: 提高+/省选-
pid: UVA11997
tag: ['数学', '最短路', '队列']
---

# K Smallest Sums

## 题目描述

有一个 $k \times k$ 的矩阵，在每行任取一个位置，把这些位置的元素相加的到一个值，求前 $k$ 小的值。

## 输入格式

多组数据。

每组第一行是整数 $k$。

第 $2$ 到 $k+1$ 行中的第 $i+1$ 行有 $k$ 个整数，第 $j$ 个表示 $a_{i,j}$。

## 输出格式

每行 $k$ 个整数，表示答案。

## 说明/提示

对于 $100\%$ 的数据，$2 \leq k \leq 750$。

## 样例 #1

### 输入

```
3
1 8 5
9 2 5
10 7 6
2
1 1
1 2
```

### 输出

```
9 10 12
2 2
```



---

---
title: "理想路径 Ideal Path"
layout: "post"
diff: 提高+/省选-
pid: UVA1599
tag: ['广度优先搜索 BFS', '最短路', '队列']
---

# 理想路径 Ideal Path

## 题目描述

## 本题有多组数据


# 理想路径（Ideal Path, NEERC 2010, UVa1599）

给定一个$n$个点$m$条边的无向图，每条边上都涂有1种颜色。求点$1$到点$n$的一条路径，**使得经过的边数最少**，在此前提下，经过边的颜色序列最小。可能有自环与重边。输入保证至少存在一条连接$1$和$n$的道路。

## 输入格式

输入共$m+1$行：

第一行$2$个空格整数：$n$和$m$。

以后$m$行，每行空格隔开的$3$个整数$a_i,b_i,c_i$，表示在$a_i,b_i$之间有一条颜色为$c_i$的道路。

## 输出格式

输出共两行：

第一行$1$个正整数$k$，表示$1$到$n$至少需要经过$k$条边。

第二行包含$k$个空格隔开的正整数，表示从$1$到$n$依次经过的边的**颜色**。

## 输入输出样例：
### 输入样例：
```
4 6
1 2 1
1 3 2
3 4 3
2 3 1
2 4 4
3 1 1
```
### 输出样例：
```
2
1 3
```
### 输入输出样例解释：
路径依次如下：

$1\rightarrow3$，颜色为$1$（最后输入的那条）；

$3\rightarrow4$，颜色为$3$。

## 说明/提示

$2\leq n \leq 10^5, 1 \leq m \leq 2 \times 10^5,1\leq c_i \leq 10^9$。

对于任意$i \in [1,m]$有$1 \leq a_i,b_i \leq n$。

注：对于两个长度为$k$的序列$a,b$，当存在$i \in [1,k]$使$a_i < b_i$，且对于任意$j \in [1,i)$都有$a_j = b_j$时，$a<b$。

原文：A sequence (a1, a2, . . . , ak) is lexicographically smaller than a sequence (b1, b2, . . . , bk) if there
exists i such that ai < bi
, and aj = bj for all j < i.

感谢@Sparky_14145 提供的翻译



---

---
title: "Abbott的复仇 Abbott's Revenge"
layout: "post"
diff: 提高+/省选-
pid: UVA816
tag: ['广度优先搜索 BFS', '图论建模', '最短路']
---

# Abbott的复仇 Abbott's Revenge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=757

[PDF](https://uva.onlinejudge.org/external/8/p816.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/815d09b7103ad071de9d9f7869315aa2585ea85b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/4939e773b1884a681cdc9dbd1fe1251df58b072b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA816/9ff2bb3a862e6ca3e356ecb98a558f994c9d7f5d.png)

## 样例 #1

### 输入

```
SAMPLE
3 1 N 3 3
1 1 WL NR *
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0
NOSOLUTION
3 1 N 3 2
1 1 WL NR *
1 2 NL ER *
2 1 SL WR NFR *
2 2 SR EL *
0
END
Figure 1: An Example Walk-Through
Arrow Maz
```

### 输出

```
SAMPLE
(3,1) (2,1) (1,1) (1,2) (2,2) (2,3) (1,3) (1,2) (1,1) (2,1)
(2,2) (1,2) (1,3) (2,3) (3,3)
NOSOLUTION
No Solution Possible
```



---

