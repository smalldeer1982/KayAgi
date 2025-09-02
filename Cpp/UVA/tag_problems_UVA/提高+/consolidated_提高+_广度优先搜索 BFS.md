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
title: "Solitaire"
layout: "post"
diff: 提高+/省选-
pid: UVA1724
tag: ['搜索', '广度优先搜索 BFS', '折半搜索 meet in the middle']
---

# Solitaire

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=859&page=show_problem&problem=4862

[PDF](https://uva.onlinejudge.org/external/17/p1724.pdf)

## 样例 #1

### 输入

```
4 4 4 5 5 4 6 5
2 4 3 3 3 6 4 6
```

### 输出

```
YES
```



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

