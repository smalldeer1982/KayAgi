---
title: "Subway tree systems"
layout: "post"
diff: 普及/提高-
pid: P10477
tag: ['深度优先搜索 DFS', '图遍历', '树的遍历']
---
# Subway tree systems
## 题目描述

Some major cities have subway systems in the form of a tree, i.e. between any pair of stations, there is one and only one way of going by subway. Moreover, most of these cities have a unique central station. Imagine you are a tourist in one of these cities and you want to explore all of the subway system. You start at the central station and pick a subway line at random and jump aboard the subway car. Every time you arrive at a station, you pick one of the subway lines you have not yet travelled on. If there is none left to explore at your current station, you take the subway line back on which you first came to the station, until you eventually have travelled along all of the lines twice,once for each direction. At that point you are back at the central station. Afterwards, all you remember of the order of your exploration is whether you went further away from the central station or back towards it at any given time, i.e. you could encode your tour as a binary string, where 0 encodes taking a subway line getting you one station further away from the central station, and 1 encodes getting you one station closer to the central station.

![](https://cdn.luogu.com.cn/upload/image_hosting/57sf9gvq.png)
## 输入格式

On the first line of input is a single positive integer n, telling the number of test scenarios to follow.Each test scenario consists of two lines, each containing a string of the characters '0' and '1' of length at most 3000, both describing a correct exploration tour of a subway tree system.
## 输出格式

exploration tours of the same subway tree system, or the text "different" if the two strings cannot be exploration tours of the same subway tree system.
## 样例

### 样例输入 #1
```
2
0010011101001011
0100011011001011
0100101100100111
0011000111010101
```
### 样例输出 #1
```
same
different
```
## 题目翻译

**【题目描述】**

一些主要城市的地铁系统采用树状结构，即在任何两个车站之间，只有一条且仅有一条地铁线路。此外，大多数这些城市都有一个独特的中央车站。想象一下，你是这些城市中的一名游客，你想要探索整个地铁系统。你从中央车站出发，随机选择一条地铁线路，跳上地铁列车。每当你到达一个车站，你就会选择一条你尚未乘坐过的地铁线路。如果在当前车站没有其他要探索的地铁线路了，你就会乘坐第一次到达该车站的地铁线路返回，直到最终你沿着所有的线路都行驶了两次，即每个方向都行驶了一次。在那时，你回到了中央车站。之后，你所记得的探索顺序只是在任何给定时间是否向中央车站更远或更近，也就是说，你可以将你的旅程编码为一个二进制字符串，其中 0 表示乘坐一条地铁线路使你离中央车站更远一站，而 1 表示使你离中央车站更近一站。

**【输入格式】**

输入的第一行是一个正整数 $n$，表示接下来要跟随的测试方案的数量。每个测试方案包括两行，每行包含一个长度最多为 $3000$ 的由字符 '0' 和 '1' 组成的字符串，描述了地铁树系统的正确探索旅程。

**【输出格式】**

对于每个测试方案，如果两个字符串可以表示相同地铁树系统的探索旅程，则输出 "same"；如果两个字符串不能表示相同地铁树系统的探索旅程，则输出 "different"。

翻译来自于：ChatGPT。


---

---
title: "[GESP202406 六级] 二叉树"
layout: "post"
diff: 普及/提高-
pid: P10722
tag: ['树形数据结构', '2024', '图遍历', '树的遍历', 'GESP']
---
# [GESP202406 六级] 二叉树
## 题目描述

小杨有⼀棵包含 $n$ 个节点的二叉树，且根节点的编号为 $1$。这棵二叉树任意⼀个节点要么是白色，要么是黑色。之后小杨会对这棵二叉树进行 $q$ 次操作，每次小杨会选择⼀个节点，将以这个节点为根的子树内所有节点的颜色反转，即黑色变成白色，白色变成黑色。

小杨想知道 $q$ 次操作全部完成之后每个节点的颜色。
## 输入格式

第⼀行一个正整数 $n$，表示二叉树的节点数量。

第二行 $(n-1)$ 个正整数，第 $i$（$1\le i\le n-1$）个数表示编号为 $(i+1)$ 的节点的父亲节点编号，数据保证是⼀棵二叉树。

第三行一个长度为 $n$ 的 $\texttt{01}$ 串，从左到右第 $i$（$1\le i\le n$）位如果为 $\texttt{0}$，表示编号为 $i$ 的节点颜色为白色，否则为黑色。

第四行⼀个正整数 $q$，表示操作次数。

接下来 $q$ 行每行⼀个正整数 $a_i$（$1\le a_i\le n$），表示第 $i$ 次操作选择的节点编号。
## 输出格式

输出一行一个长度为 $n$ 的 $\texttt{01}$ 串，表示 $q$ 次操作全部完成之后每个节点的颜色。从左到右第 $i$（$1\le i\le n$） 位如果为 $\texttt{0}$，表示编号为 $i$ 的节点颜色为白色，否则为黑色。
## 样例

### 样例输入 #1
```
6
3 1 1 3 4
100101
3
1
3
2
```
### 样例输出 #1
```
010000
```
## 提示

#### 样例解释

第一次操作后，节点颜色为：$\texttt{011010}$

第二次操作后，节点颜色为：$\texttt{000000}$

第三次操作后，节点颜色为：$\texttt{010000}$

#### 数据范围

| 子任务编号 | 得分 | $n$ | $q$ | 特殊条件 |
| :--: | :--: | :--: | :--: | :--: |
| $1$ |  $20$ | $\le 10^5$ | $\le 10^5$ |对于所有 $i\ge 2$，节点 $i$ 的父亲节点编号为 $i-1$
| $2$ |  $40$ | $\le 1000$ | $\le 1000$ | |
| $3$ | $40$ | $\le 10^5$ | $\le 10^5$ | |

对于全部数据，保证有 $n,q\le 10^5$。


---

---
title: "[CSP-J2022 山东] 部署"
layout: "post"
diff: 普及/提高-
pid: P11855
tag: ['图论', '2022', '山东', '图遍历', 'CSP-J 入门级']
---
# [CSP-J2022 山东] 部署
## 题目背景

受疫情影响，山东省取消了 CSP-J 2022 认证活动，并于次年三月重新命题，在省内补办比赛。
## 题目描述

“万里羽书来未绝，五关烽火昼仍传。” 

古时候没有现代信息化战争的技术，只能靠烽火传信和将军运筹帷幄的调兵遣将来取得战争的优势。

为了使消耗最低，现在 A 国已经在 $n$ 个城市之间建好了道路和行军部署渠道，使得这 $n$ 个城市都能互相到达且不存在环（即构成以 $1$ 号城市为根节点的树型结构）。每个城市都驻扎了一定数量的兵力。

为了清晰的描述问题，我们给这 $n$ 个城市进行 $1$ 到 $n$ 的编号，且 $1$ 号城市为树的根节点（数据保证：构成以 $1$ 号城市为根节点的一棵树）。初始时，第 $i$ 座城市拥有初始兵力 $a_{i}$。

现在为测试战争部署速度，将军进行了 $m$ 次测试，每次测试可能为以下两种命令的某一种：

`1 x y`（三个数间均用 1 个空格分开）：向 $x$ 号城市**和**以它为根的子树中的所有城市全部增兵 $y$ 的数量。

`2 x y`（三个数间均用 1 个空格分开）：向 $x$ 号城市**和**与它直接相连（含父结点和子结点）的城市全部增兵 $y$ 的数量。

$m$ 条命令发布出去后，将军喊来参谋，进行了 $q$ 次询问，每次询问第 $x$ 座城市的最终兵力情况。
该参谋就是小虾米，他又向你求助了，请你帮助他解决问题（$q$ 次询问的结果）。
## 输入格式

第一行一个正整数 $n$ 表示城市数量。

第二行一共 $n$ 个正整数 $a_{1},a_{2},\dots a_{n}$ 表示每座城市的初始兵力。

接下来 $n-1$ 行，每行两个整数 $x,y$，表示 $x$ 和 $y$ 城市之间有直接相连的道路。

接下来一行一个正整数 $m$，表示 $m$ 次命令。

接下来 $m$ 行，每行三个正整数 $p,x,y$ 表示两种命令其中一种，其中 $p=1$ 时表示第一种命令，$p=2$ 时表示第二种命令。

接下来一行一个正整数 $q$，表示 $q$ 次询问。

接下来 $q$ 行，每行一个正整数 $x$ ，表示询问编号为 $x$ 的城市最后的兵力值。
## 输出格式

一共 $q$ 行，每行一个正整数分别对应于每次询问的答案。
## 样例

### 样例输入 #1
```
5
1 2 3 4 5
1 2
1 3
2 4
3 5
4
1 1 2
2 2 3
1 3 3
2 5 1
4
1
2
3
4
```
### 样例输出 #1
```
6
7
9
9
```
### 样例输入 #2
```
4
1 1 1 1
1 2
1 3
1 4
1
1 1 1
2
1
2
```
### 样例输出 #2
```
2
2
```
## 提示

### 数据范围
对于 $30\%$ 的数据，$1\le n\le1000,1\le m\le1000$；

对于 $60\%$ 的数据，$1\le n\le10^{5},1\le m\le10^{5},1\le q\le10^{5}$；

其中 $10\%$ 的数据树是一条链，另外 $10\%$ 的数据只有 $1$ 操作，另外 $10\%$ 的数据只有 $2$ 操作。

对于 $100\%$ 的数据，数据保证给定的城市和道路能形成树，且 $1$ 号城市为根节点。$1\le n\le10^{6},1\le m\le10^{6},1\le q\le10^{6},1\le a_{i}\le10^{9},1\le x\le n,1\le y\le10$。


---

