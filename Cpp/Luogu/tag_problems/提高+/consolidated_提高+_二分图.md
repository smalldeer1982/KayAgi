---
title: "[JRKSJ R8] +1-1"
layout: "post"
diff: 提高+/省选-
pid: P10572
tag: ['2024', '洛谷原创', 'O2优化', '二分图', '洛谷月赛']
---
# [JRKSJ R8] +1-1
## 题目描述

给你 $n$ 个点 $m$ 条边的无向图，每个结点上有一个字符 `(` 或者 `)`。

有 $q$ 次查询，每次查询给出 $x,y$，你需要判断是否存在一条从 $x$ 到 $y$ 的路径（不需要保证是简单路径）满足将路径上的点上的字符顺次写下来得到的字符串是合法括号串。
## 输入格式

第一行三个整数 $n,m,q$。

第二行一个只包含 `(` 和 `)` 的长度为 $n$ 的字符串表示结点 $1\dots n$ 上的字符。

下面 $m$ 行，每行两个整数 $u,v$ 表示图上的一条边。

下面 $q$ 行，每行两个整数 $x,y$。
## 输出格式

一个长度为 $q$ 的 01 串，第 $i$ 个字符表示第 $i$ 次询问的答案，1 表示存在这样的路径，0 表示不存在这样的路径。
## 样例

### 样例输入 #1
```
5 6 5
((())
1 2
1 3
2 3
3 4
4 5
2 4

1 2
3 4
1 4
1 5
2 5

```
### 样例输出 #1
```
01111
```
## 提示

合法括号串的定义：

* 空字符串是合法括号串
* 若 $A,B$ 是合法括号串，则 $AB$ 是合法括号串
* 若 $A$ 是合法括号串，则 $(A)$ 是合法括号串
* 除此之外的其他字符串均不是合法括号串

如 `()`、`(()())` 是合法括号串，`(()`、`())(` 不是合法括号串。

### 样例解释

**为了方便观察，输入的边和询问之间有一个换行。但数据中并不存在这个换行。**

![](https://cdn.luogu.com.cn/upload/image_hosting/x2lp3c7m.png)

其中 $1,2,3$ 号点的字符是 `(`，$4,5$ 号点的字符是 `)`。

$1\to 2$：显然，合法括号串不可能以 `(` 结尾。\
$3\to 4$：路径 $3\to 4$ 表示的字符串是 `()`。\
$1\to 4$：路径 $1\to 3\to 2\to 4\to 5\to 4$ 表示的字符串是 `((()))`。\
$1\to 5$：路径 $1\to 2\to 4\to 5$ 表示的字符串是 `(())`。\
$2\to 5$：路径 $2\to 3\to 4\to 5$ 表示的字符串是 `(())`。

### 数据规模与约定

本题采用捆绑测试。

- Subtask 1（20 pts）：$n,q\leq 500$，$m \leq 800$；
- Subtask 2（30 pts）：图是森林；
- Subtask 3（20 pts）：$q\le 10$；
- Subtask 4（30 pts）：无特殊限制。

对于所有数据，满足 $1\le n,q\le 5\times 10^5$，$0\le m\le \min(\frac{n\times(n-1)}{2},5\times 10^5)$，$1\le u,v,x,y\le n$，保证给出的图无重边、无自环。


---

---
title: "[ZJOI2007] 矩阵游戏"
layout: "post"
diff: 提高+/省选-
pid: P1129
tag: ['2007', '各省省选', '递归', '网络流', '浙江', '二分图']
---
# [ZJOI2007] 矩阵游戏
## 题目描述

小 Q 是一个非常聪明的孩子，除了国际象棋，他还很喜欢玩一个电脑益智游戏――矩阵游戏。矩阵游戏在一个 $n \times n$ 黑白方阵进行（如同国际象棋一般，只是颜色是随意的）。每次可以对该矩阵进行两种操作：

- 行交换操作：选择矩阵的任意两行，交换这两行（即交换对应格子的颜色）。
- 列交换操作：选择矩阵的任意两列，交换这两列（即交换对应格子的颜色）。

游戏的目标，即通过若干次操作，使得方阵的主对角线(左上角到右下角的连线)上的格子均为黑色。

对于某些关卡，小 Q 百思不得其解，以致他开始怀疑这些关卡是不是根本就是无解的！于是小 Q 决定写一个程序来判断这些关卡是否有解。

## 输入格式

**本题单测试点内有多组数据**。

第一行包含一个整数 $T$，表示数据的组数，对于每组数据，输入格式如下：

第一行为一个整数，代表方阵的大小 $n$。
接下来 $n$ 行，每行 $n$ 个非零即一的整数，代表该方阵。其中 $0$ 表示白色，$1$ 表示黑色。
## 输出格式

对于每组数据，输出一行一个字符串，若关卡有解则输出 `Yes`，否则输出 `No`。
## 样例

### 样例输入 #1
```
2
2
0 0
0 1
3
0 0 1
0 1 0
1 0 0

```
### 样例输出 #1
```
No
Yes

```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 7$。
- 对于 $50\%$ 的数据，保证 $n \leq 50$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 200$，$1 \leq T \leq 20$。



---

---
title: "[NOIP 2008 提高组] 双栈排序"
layout: "post"
diff: 提高+/省选-
pid: P1155
tag: ['图论', '2008', 'NOIP 提高组', '二分图']
---
# [NOIP 2008 提高组] 双栈排序
## 题目描述

Tom 最近在研究一个有趣的排序问题。如图所示，通过 $2$ 个栈 $S_1$ 和 $S_2$，Tom 希望借助以下 $4$ 种操作实现将输入序列升序排序。

![](https://cdn.luogu.com.cn/upload/image_hosting/gwxu91ud.png)

- 操作 $\verb!a!$：将第一个元素压入栈 $S_1$。
- 操作 $\verb!b!$：将 $S_1$ 栈顶元素弹出至输出序列。
- 操作 $\verb!c!$：将第一个元素压入栈 $S_2$。
- 操作 $\verb!d!$：将 $S_2$ 栈顶元素弹出至输出序列。


如果一个 $1\sim n$ 的排列 $P$ 可以通过一系列合法操作使得输出序列为 $(1,2,\cdots,n-1,n)$，Tom 就称 $P$ 是一个“可双栈排序排列”。例如 $(1,3,2,4)$ 就是一个“可双栈排序序列”，而 $(2,3,4,1)$ 不是。下图描述了一个将 $(1,3,2,4)$ 排序的操作序列：$\texttt {a,c,c,b,a,d,d,b}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jwdjwfee.png)

当然，这样的操作序列有可能有几个，对于上例 $(1,3,2,4)$，$\texttt{a,b,a,a,b,b,a,b}$ 是另外一个可行的操作序列。Tom 希望知道其中字典序最小的操作序列是什么。
## 输入格式

第一行是一个整数 $n$。

第二行有 $n$ 个用空格隔开的正整数，构成一个 $1\sim n$ 的排列。
## 输出格式

共一行，如果输入的排列不是“可双栈排序排列”，输出 `0`。

否则输出字典序最小的操作序列，每两个操作之间用空格隔开，行尾没有空格。
## 样例

### 样例输入 #1
```
4
1 3 2 4
```
### 样例输出 #1
```
a b a a b b a b
```
### 样例输入 #2
```
4
2 3 4 1
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
3
2 3 1
```
### 样例输出 #3
```
a c a b b d
```
## 提示

$30\%$ 的数据满足：$n\le10$。

$50\%$ 的数据满足：$n\le50$。

$100\%$ 的数据满足：$n\le1000$。

2021.06.17 加强 by [SSerxhs](https://www.luogu.com.cn/user/29826)。hack 数据单独分为一个 subtask 防止混淆。

noip2008 提高第四题


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
title: "「FAOI-R6」魂灵之影"
layout: "post"
diff: 提高+/省选-
pid: P12604
tag: ['图论', '数论', '交互题', 'O2优化', '二分图']
---
# 「FAOI-R6」魂灵之影
## 题目背景

此题因撞题已移出 FAOI Round 6.

> Draw me to the light, let the curse be lifted  
We can rise above the roar  
With the bite of every devil  
We've felled before  
Drown them out  
Let the fog give way to clarity  
There is power in the strain of every drop I bleed  
I am the venom and the cure  
Take me  
Through the fear, through the heart that's broken  
Our world lies in wait for me  
Every tear, every scar left open  
This is the taming of the beast  
I'll end this war you started  
I'll stitch this wound with bloodshed  
You are my wicked victory  

<https://music.163.com/#/song?id=2672191019>
## 题目描述

给定一个无向**连通**图，边带权，可能存在重边自环。有 $q$ 次查询，每次给定 $x,y,z$，求所有以 $x$ 为起点，$y$ 为终点的路径（不要求为简单路径）中，边权和 $\bmod\ z$ 的最小值是多少。

### 交互方式

**本题为交互题，只支持 C++ 语言提交，并且不支持 C++14 (GCC 9)。**

你需要编写以下三个函数：

```cpp
void Ready(int T, int subtask_id)
```

该函数在每个测试点中仅会调用一次，两个参数表示该测试点的数据组数和子任务编号。样例的子任务编号为 $-1$。

```cpp
void Set(int n, int m, int q, vector <int> u, vector <int> v, vector <int> w)
```

在调用 `Ready` 之后，该函数会（在每个测试点中）被调用 $T$ 次，其中 $n,m$ 分别表示图的边数和点数。$u,v,w$ 的大小均为 $m$，$u[i],v[i],w[i]$ 表示图的一条边。

```cpp
int Go(int x, int y, int z)
```

每次调用 `Set` 之后，该函数会（在每组数据中）被调用 $q$ 次，每次调用表示一次查询。返回值应为本次查询的答案。

你可以直接以下发文件中的 `template.cpp` 为基础编写。
## 输入格式

**以下格式只对本地测试有效，但变量名的含义与实际评测相同。在实际评测中，请不要试图从标准输入（stdin）读取任何内容。**

**本题有多组数据。**

第一行两个非负整数 $T$ 和 $\text{subtask\_id}$，分别表示数据组数和 Subtask 编号。

特别地，样例满足 $\text{subtask\_id}=-1$。

对于每组数据：
- 第一行是空行。
- 第二行三个非负整数 $n,m,q$。
- 接下来 $m$ 行，每行三个非负整数 $u,v,w$，表示一条边。
- 接下来 $q$ 行，每行三个正整数 $x,y,z$，表示一次查询。
## 输出格式

**以下格式只对本地测试有效，但变量名的含义与实际评测相同。在实际评测中，请不要试图向标准输出（stdout）打印任何内容。**

对于每组数据：
- 第一行是空行。
- 下面 $q$ 行，每行一个非负整数，表示答案。
## 样例

### 样例输入 #1
```
2 -1
2 1 1
1 2 1
1 2 2
3 3 1
1 2 1
2 3 1
1 3 1
1 3 2
```
### 样例输出 #1
```
1
0
```
## 提示

#### 【样例解释】

对于第 $1$ 组数据的唯一一组询问，所有路径均形如 $1\to 2\to 1\to \dots \to 1\to 2$，可以证明所有路径的权值均为 $1$。

对于第 $2$ 组数据的唯一一组询问，路径 $1\to 2\to 3$ 权值为 $2\bmod 2=0$，路径 $1\to 3$ 的答案为 $1\bmod 2=1$，所以答案为 $0$。

#### 【数据范围】

对于 $100\%$ 的数据，$0\le T\le 1.5 \times 10^4$，$-1 \le \text{subtask\_id} \le 9$，$0\le n,m,q\le 10^6$，$1\le u,v,x,y\le n$，$0\le w\le 10^9$，$1\le z\le 10^9$，保证图连通。

请下载附件中的 `judge_result.jpeg` 以了解交互库所占用资源的规模。如果你不想下载附件的话，我们在这里用一句话概括一下：保证交互库的运行时间不超过 0.15 秒，占用的内存不超过 60 MB。

**本题开启子任务捆绑测试。**

- Subtask 0 - Subtask 4（10 pts）：$n,m,q,w,z\le 10$，$T \le 1.5 \times 10^4$。
  - Subtask 0（2 pts）：$n=0$。
  - Subtask 1（2 pts）：$n=1$。
  - Subtask 2（1 pts）：$n=2$，$m \le 3$。
  - Subtask 3（4 pts）：$n \le 4$，$m \le 6$，$w \le 8$。
  - Subtask 4（1 pts）：在 Subtask 0 - Subtask 4 下无特殊限制。
- Subtask 5 - Subtask 9（90 pts）：$n,m,q\le 10^6$，$w,z \le 10^9$，$T=1$。
  - Subtask 5（20 pts）：$n,m,q,w,z\le 100$。
  - Subtask 6（20 pts）：$n,m,q,w,z\le 10^3$。
  - Subtask 7（10 pts）：$w,z\le 5$。
  - Subtask 8（10 pts）：$w=1$。
  - Subtask 9（30 pts）：在 Subtask 5 - Subtask 9 下无特殊限制。


Idea：ppip，Solution：喵仔牛奶，Code：ppip，Data：035966_L3

[如何调试？](https://www.luogu.com.cn/paste/3x0kjgps)


---

---
title: "队员分组"
layout: "post"
diff: 提高+/省选-
pid: P1285
tag: ['动态规划 DP', 'Special Judge', '二分图']
---
# 队员分组
## 题目描述

有 $n$ 个人从 $1$ 至 $n$ 编号，相互之间有一些认识关系，你的任务是把这些人分成两组，使得：

- 每个人都被分到其中一组。
- 每个组都至少有一个人。
- 一组中的每个人都认识其他同组成员。

在满足上述条件的基础上，要求两组成员的人数之差（绝对值）尽可能小。请构造一种可行的方案。

请注意，$x$ 认识 $y$ 不一定说明 $y$ 认识 $x$；$x$ 认识 $y$ 且 $y$ 认识 $z$ 不一定说明 $x$ 认识 $z$。即认识关系是单向且不可传递的。
## 输入格式

输入的第一行是一个整数，代表总人数 $n$。

第 $2$ 到第 $(n + 1)$ 行，每行有若干个互不相同的整数，以 $0$ 结尾，第 $(i + 1)$ 行的第 $j$ 个整数 $a_{i, j}$（$0$ 除外）代表第 $i$ 个人认识 $a_{i, j}$。
## 输出格式

**本题存在 Special Judge**。

如果无解，请输出一行一个字符串 `No solution`。

如果有解，请输出两行整数，分别代表两组的成员。每行的第一个整数是该组的人数，后面**以升序**若干个整数代表该组的成员编号，数字间用空格隔开。
## 样例

### 样例输入 #1
```
5
2 3 5 0
1 4 5 3 0
1 2 5 0
1 2 3 0
4 3 2 1 0

```
### 样例输出 #1
```
3 1 3 5
2 2 4

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $2 \leq n \leq 100$，$1 \leq a_{i, j} \leq n$。

#### 说明

由 @zhouyonglong 提供 SPJ。




---

---
title: "[GCJ 2018 #2] Costume Change"
layout: "post"
diff: 提高+/省选-
pid: P13147
tag: ['2018', '二分图', 'Google Code Jam']
---
# [GCJ 2018 #2] Costume Change
## 题目描述

Supervin is a well-known choreographer. Today is the $N$-th anniversary of his choreography career. To celebrate it, he is planning a dance on a stage that is a square grid of size $N$ by $N$. Exactly one dancer will stand in each grid cell.

Each dancer will wear a costume; each costume has a single color, and is made out of either wool or cotton as its material. Supervin has $N$ colors to choose from when designing the costumes for his dancers, indexed from 1 to $N$.

Each dancer wants to feel special. If two or more dancers share a row or column and also have costumes of the same color and material, they will no longer feel special.

Supervin wants all of his dancers to feel special. Therefore, Supervin is prepared to change the color and/or material of dancers' costumes so that no dancer shares a row or column with another dancer with the same costume (same color and same material). What is the minimum number of dancers whose costumes must be changed in order to make this happen? (Note that a change to both the color and material of a costume still counts as only one change.)
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each begins with one line containing an integer $N$: the side length (in unit cells) of the square grid of dancers. Then, $N$ lines follow; each contains $N$ non-zero integers $A_{i,j}$. The $j$-th value on the $i$-th line represents the costume of the dancer in the $i$-th row and $j$-th column of the grid. The magnitude of the value gives the color and the sign of the value gives the material (- for wool, + for cotton).

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the minimum number of dancers whose costumes must be changed, as described above.
## 样例

### 样例输入 #1
```
4
2
1 2
2 1
2
1 1
2 1
2
1 2
1 2
2
2 2
-2 2
```
### 样例输出 #1
```
Case #1: 0
Case #2: 1
Case #3: 2
Case #4: 1
```
## 提示

**Sample Explanation**

In Sample Case #1, no costumes need to be changed, since no dancer shares a row or column with another dancer with the same costume.

In Sample Case #2, one optimal solution is to change the value of $\mathbf A$ into the following (bold indicates changed values):

```
  1 -2
  2 1
```

Other optimal solutions are possible. Note that changing both the color and the material of a dancer's costume only counts as one change.

In Sample Case #3, one optimal solution is to change the value of $\mathbf A$ into the following (bold indicates changed values):

```
  1 2
  2 1
```

Other optimal solutions are possible.

In Sample Case #4, one optimal solution is to change the value of $\mathbf A$ into the following (bold indicates changed values):

```
  2 -2
  -2 2
```

Other optimal solutions are possible.

**Limits**

- $1 \leq T \leq 100$.
- $-N \leq A_{i,j} \leq N$, for all $i, j$.
- $A_{i,j} \neq 0$, for all $i, j$.

**Test set 1 (7 Pts, Visible)**

- $2 \leq N \leq 4$.

**Test set 2 (17 Pts, Hidden)**

- $2 \leq N \leq 100$.


---

---
title: "[GCJ 2017 Finals] Dice Straight"
layout: "post"
diff: 提高+/省选-
pid: P13179
tag: ['2017', '二分图', 'Google Code Jam']
---
# [GCJ 2017 Finals] Dice Straight
## 题目描述

You have a special set of $N$ six-sided dice, each of which has six different positive integers on its faces. Different dice may have different numberings.

You want to arrange some or all of the dice in a row such that the faces on top form a straight (that is, they show consecutive integers). For each die, you can choose which face is on top.

How long is the longest straight that can be formed in this way?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with one line with $N$, the number of dice. Then, $N$ more lines follow; each of them has six positive integers $D_{ij}$. The $j$-th number on the $i$-th of these lines gives the number on the $j$-th face of the $i$-th die.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the length of the longest straight that can be formed.
## 样例

### 样例输入 #1
```
3
4
4 8 15 16 23 42
8 6 7 5 30 9
1 2 3 4 55 6
2 10 18 36 54 86
2
1 2 3 4 5 6
60 50 40 30 20 10
3
1 2 3 4 5 6
1 2 3 4 5 6
1 4 2 6 5 3
```
### 样例输出 #1
```
Case #1: 4
Case #2: 1
Case #3: 3
```
## 提示

**Sample Explanation**

In sample case #1, a straight of length $4$ can be formed by taking the $2$ from the fourth die, the 3 from the third die, the $4$ from the first die, and the $5$ from the second die.

In sample case #2, there is no way to form a straight larger than the trivial straight of length $1$.

In sample case #3, you can take a $1$ from one die, a $2$ from another, and a $3$ from the remaining unused die. Notice that this case demonstrates that there can be multiple dice with the same set of values on their faces.

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq D_{ij} \leq 10^6$ for all $i, j$.

**Small dataset (10 Pts, Test Set 1 - Visible)**

- Time limit: ~~60~~ 15 seconds.
- $1 \leq N \leq 100$.

**Large dataset (15 Pts, Test Set 2 - Hidden)**

- Time limit: ~~120~~ 30 seconds.
- $1 \leq N \leq 50000$.
- The sum of $N$ across all test cases $\leq 200000$.


---

---
title: "[GCJ 2016 #1B] Technobabble"
layout: "post"
diff: 提高+/省选-
pid: P13194
tag: ['2016', '二分图', 'Google Code Jam']
---
# [GCJ 2016 #1B] Technobabble
## 题目描述

Every year, your professor posts a blank sign-up sheet for a prestigious scientific research conference on her door. If a student wants to give a lecture at the conference, they choose a two-word topic that is not already on the sheet and write it on the sheet. Once the deadline has passed, the professor has one of her grad students put the topics in a random order, to avoid biasing for or against students who signed up earlier. Then she presents the topics to you for review.

Since the snacks at the conference are excellent, some students try to fake their way into the conference. They choose the first word of some topic already on the sheet and the second word of some topic already on the sheet, and combine them (putting the first word first, and the second word second) to create a new "topic" (as long as it isn't already on the sheet). Since your professor is open-minded, sometimes this strategy actually works!

The fakers are completely unoriginal and can't come up with any new first or second words on their own; they must use existing ones from the sheet. Moreover, they won't try to use an existing first word as their own second word (unless the word also already exists on the sheet as a second word), or vice versa.

You have a list of all $\mathbf{N}$ of the submitted topics, in some arbitrary order; you don't know the order in which they were actually written on the sheet. What's the largest number of them that could have been faked?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each consists of one line with an integer $\mathbf{N}$, followed by $\mathbf{N}$ lines, each of which represents a different topic and has two strings of uppercase English letters: the two words of the topic, in order.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is an integer: the largest number of topics that could have possibly been faked.
## 样例

### 样例输入 #1
```
3
3
HYDROCARBON COMBUSTION
QUAIL BEHAVIOR
QUAIL COMBUSTION
3
CODE JAM
SPACE JAM
PEARL JAM
2
INTERGALACTIC PLANETARY
PLANETARY INTERGALACTIC
```
### 样例输出 #1
```
Case #1: 1
Case #2: 0
Case #3: 0
```
## 提示

In sample case #1, one possibility is that the topics were added to the sheet in this order:
```
QUAIL BEHAVIOR (real)
HYDROCARBON COMBUSTION (real)
QUAIL COMBUSTION (fake)
```

There is no scenario in which more than one of the topics can be fake.

In sample case #2, all of the topics must be real. Whatever order they were written in, at no point would it have been possible to use existing words to create a new topic that was not already on the list.

In sample case #3, neither topic can be fake. For example, if `INTERGALACTIC PLANETARY` had been the first and only topic written on the sheet, a faker could only have used `INTERGALACTIC` as the first word of a new topic and could only have used `PLANETARY` as the second word of a new topic... but the only topic that the faker could have formed would have been `INTERGALACTIC PLANETARY`, which would have been off limits since it was already on the sheet. So `PLANETARY INTERGALACTIC` must have also been a real topic.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $1 \leqslant \text{length of each word} \leqslant 20$.
- No topic is repeated within a case.

**Small dataset (14 Pts, Test Set 1 - Visible)**

- $1 \leqslant \mathbf{N} \leqslant 16$.

**Large dataset (30 Pts, Test Set 2 - Hidden)**

- $1 \leqslant \mathbf{N} \leqslant 1000$.


---

---
title: "[GCJ 2011 #3] Perpetual Motion"
layout: "post"
diff: 提高+/省选-
pid: P13380
tag: ['图论', '2011', '二分图', '组合数学', 'Google Code Jam']
---
# [GCJ 2011 #3] Perpetual Motion
## 题目描述

Have you ever been to the Google Lemming Factory? It is a very unusual place. The floor is arranged into an $R \times C$ grid. Within each grid square, there is a conveyor belt oriented up-down, left-right, or along one of the two diagonals. The conveyor belts move either forwards or backwards along their orientations, and you can independently choose which of the two possible directions each conveyor belt should move in.

![](https://cdn.luogu.com.cn/upload/image_hosting/h69uk07b.png)

Currently, there is a single lemming standing at the center of each square. When you start the conveyor belts, each lemming will move in the direction of the conveyor belt he is on until he reaches the center of a new square. All these movements happen simultaneously and take exactly one second to complete. Afterwards, the lemmings will all be on new squares, and the process will repeat from their new positions. This continues forever, or at least until you turn off the conveyor belts.

- When a lemming enters a new square, he continues going in the direction he was already going until he reaches the center of that square. He will not be affected by the new conveyor belt until the next second starts.
- If a lemming moves off the edge of the grid, he comes back at the same position on the opposite side. For example, if he were to move diagonally up and left from the top-left square, he would arrive at the bottom-right square. By the miracle of science, this whole process still only takes 1 second.
- Lemmings never collide and can always move past each other without difficulty.

The trick is to choose directions for each conveyor belt so that the lemmings will keep moving forever without ever having two of them end up in the center of the same square at the same time. If that happened, they would be stuck together from then on, and that is not as fun for them.

Here are two ways of assigning directions to each conveyor belt from the earlier example:

![](https://cdn.luogu.com.cn/upload/image_hosting/8e7eapk7.png)

In both cases, we avoid ever sending two lemmings to the center of the same square at the same time.

Given an arbitrary floor layout, calculate $N$, the number of ways to choose directions for each conveyor belt so that no two lemmings will ever end up in the center of the same square at the same time. The answer might be quite large, so please output it modulo $1000003$.
## 输入格式

The first line of input gives the number of test cases, $T$. $T$ test cases follow. Each begins with a line containing positive integers $R$ and $C$.

This is followed by $R$ lines, each containing a string of $C$ characters chosen from "|-/\\". Each character represents the orientation of the conveyor belt in a single square:

* '|' represents a conveyor belt that can move up or down.
* '-' represents a conveyor belt that can move left or right.
* '/' represents a conveyor belt that can move up-right or down-left.
* '\\' represents a conveyor belt that can move up-left or down-right.
## 输出格式

For each test case, output one line containing "Case #$x$: $M$", where $x$ is the case number (starting from 1), and $M$ is the remainder when dividing $N$ by $1000003$.
## 样例

### 样例输入 #1
```
3
3 3
|-/
|||
--|
3 4
----
||||
\\//
4 4
|---
\-\|
\|||
|--\
```
### 样例输出 #1
```
Case #1: 2
Case #2: 0
Case #3: 16
```
## 提示

**Limits**

- $ 1 \leq T \leq 25. $

**Small dataset (5 Pts, Test set 1 - Visible)**

- $ 3 \leq R \leq 4. $
- $ 3 \leq C \leq 4. $
- Time limit: ~~30~~ 3 seconds.

**Large dataset (21 Pts, Test set 2 - Hidden)**

- $ 3 \leq R \leq 100. $
- $ 3 \leq C \leq 100. $
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[GCJ 2009 #2] Stock Charts"
layout: "post"
diff: 提高+/省选-
pid: P13442
tag: ['2009', '二分图', 'Google Code Jam']
---
# [GCJ 2009 #2] Stock Charts
## 题目描述

You're in the middle of writing your newspaper's end-of-year economics summary, and you've decided that you want to show a number of charts to demonstrate how different stocks have performed over the course of the last year. You've already decided that you want to show the price of $n$ different stocks, all at the same $k$ points of the year.

A simple chart of one stock's price would draw lines between the points $(0, \text{price}_0)$, $(1, \text{price}_1)$, ..., $(k-1, \text{price}_{k-1})$, where $\text{price}_i$ is the price of the stock at the $i$th point in time.

In order to save space, you have invented the concept of an overlaid chart. An overlaid chart is the combination of one or more simple charts, and shows the prices of multiple stocks (simply drawing a line for each one). In order to avoid confusion between the stocks shown in a chart, the lines in an overlaid chart may not cross or touch.

Given a list of $n$ stocks' prices at each of $k$ time points, determine the minimum number of overlaid charts you need to show all of the stocks' prices.
## 输入格式

The first line of input will contain a single integer $T$, the number of test cases. After this will follow $T$ test cases on different lines, each of the form:

$n$ $k$

$\text{price}_{0,0}$ $\text{price}_{0,1}$ ... $\text{price}_{0,k-1}$

$\text{price}_{1,0}$ $\text{price}_{1,1}$ ... $\text{price}_{1,k-1}$

...

$\text{price}_{n-1,0}$ $\text{price}_{n-1,1}$ ... $\text{price}_{n-1,k-1}$

Where $\text{price}_{i,j}$ is an integer, the price of the $i$th stock at time $j$.

## 输出格式

For each test case, a single line containing "Case #$X$: $Y$", where $X$ is the number of the test-case (1-indexed) and $Y$ is the minimum number of overlaid charts needed to show the prices of all of the stocks.
## 样例

### 样例输入 #1
```
3
3 4
1 2 3 4
2 3 4 6
6 5 4 3
3 3
5 5 5
4 4 6
4 5 4
5 2
1 1
2 2
5 4
4 4
4 1
```
### 样例输出 #1
```
Case #1: 2
Case #2: 3
Case #3: 2
```
## 提示

**Limits**

- $1 \leq T \leq 100$
- $2 \leq k \leq 25$
- $0 \leq \text{price}_{i,j} \leq 1000000$

**Small Input**

- Time limit: ~~20~~ 2 seconds.
- $1 \leq n \leq 16$

**Large Input**

- Time limit: ~~30~~ 3 seconds.
- $1 \leq n \leq 100$



---

---
title: "[GCJ 2008 #3] No Cheating"
layout: "post"
diff: 提高+/省选-
pid: P13472
tag: ['2008', '二分图', 'Google Code Jam']
---
# [GCJ 2008 #3] No Cheating
## 题目描述

A local high school is going to hold a final exam in a big classroom. However, some students in this school are always trying to see each other's answer sheet during exams!

The classroom can be regarded as a rectangle of $M$ rows by $N$ columns of unit squares, where each unit square represents a seat.

The school principal decided to set the following rule to prevent cheating: Assume a student is able to see his left, right, upper-left, and upper-right neighbors' answer sheets. The assignment of seats must guarantee that nobody's answer sheet can be seen by any other student.

![](https://cdn.luogu.com.cn/upload/image_hosting/9h75fz4n.png)

As in this picture, it will not be a good idea to seat anyone in A, C, D, or E because the boy in the back row would be able to see their answer sheets. However, if there is a girl sitting in B, he will not be able to see her answer sheet.

Some seats in the classroom are broken, and we cannot put a student in a broken seat.

The principal asked you to answer the following question: What is the maximum number of students that can be placed in the classroom so that no one can cheat?
## 输入格式

The first line of input gives the number of cases, $C$. $C$ test cases follow. Each case consists of two parts.

The first part is a single line with two integers $M$ and $N$: The height and width of the rectangular classroom.

The second part will be exactly $M$ lines, with exactly $N$ characters in each of these lines. Each character is either a '.' (the seat is not broken) or 'x' (the seat is broken, lowercase x).

## 输出格式

For each test case, output one line containing "Case #$X$: $Y$", where $X$ is the case number, starting from 1, and $Y$ is the maximum possible number of students that can take the exam in the classroom.
## 样例

### 样例输入 #1
```
4
2 3
...
...
2 3
x.x
xxx
2 3
x.x
x.x
10 10
....x.....
..........
..........
..x.......
..........
x...x.x...
.........x
...x......
........x.
.x...x....
```
### 样例输出 #1
```
Case #1: 4
Case #2: 1
Case #3: 2
Case #4: 46
```
## 提示

**Limits**

- $C=20$

**Small dataset (10 Pts, Test set 1 - Visible)**

- $1 \leqslant M \leqslant 10$
- $1 \leqslant N \leqslant 10$

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $1 \leqslant M \leqslant 80$
- $1 \leqslant N \leqslant 80$


---

---
title: "[GCJ 2008 APAC SemiFinal] Modern Art Plagiarism"
layout: "post"
diff: 提高+/省选-
pid: P13477
tag: ['2008', '二分图', 'Google Code Jam']
---
# [GCJ 2008 APAC SemiFinal] Modern Art Plagiarism
## 题目描述

You have pictures of two sculptures. The sculptures consist of several solid metal spheres, and some rubber pipes connecting pairs of spheres. The pipes in each sculpture are connected in such a way that for any pair of spheres, there is exactly one path following a series of pipes (without repeating any) between those two spheres. All the spheres have the same radius, and all the pipes have the same length.

You suspect that the smaller of the two sculptures was actually created by simply removing some spheres and pipes from the larger one. You want to write a program to test if this is possible.

The input will contain several test cases. One sculpture is described by numbering the spheres consecutively from $1$, and listing the pairs of spheres which are connected by pipes. The numbering is chosen independently for each sculpture.

## 输入格式

- One line containing an integer $C$, the number of test cases in the input file.

For each test case, there will be:

- One line containing the integer $N$, the number of spheres in the large sculpture.
- $N-1$ lines, each containing a pair of space-separated integers, indicating that the two spheres with those numbers in the large sculpture are connected by a pipe.
- One line containing the integer $M$, the number of spheres in the small sculpture.
- $M-1$ lines, each containing a pair of space-separated integers, indicating that the two spheres with those numbers in the small sculpture are connected by a pipe.

## 输出格式

- $C$ lines, one for each test case in the order they occur in the input file, containing "Case #$X$: YES" if the small sculpture in case $X$ could have been created from the large sculpture in case $X$, or "Case #$X$: NO" if it could not. ($X$ is the number of the test case, between $1$ and $C$.)
## 样例

### 样例输入 #1
```
2
5
1 2
2 3
3 4
4 5
4
1 2
1 3
1 4
5
1 2
1 3
1 4
4 5
4
1 2
2 3
3 4
```
### 样例输出 #1
```
Case #1: NO
Case #2: YES
```
## 提示

**Sample Explanation**

In the first case, the large sculpture has five spheres connected in a line, and the small sculpture has one sphere that has three other spheres connected to it. There's no way the smaller sculpture could have been made by removing things from the larger one.

In the second case, the small sculpture is four spheres connected in a line. These can match the larger sculpture's spheres in the order $2-1-4-5$.

**Limits**

**Small dataset (7 Pts, Test set 1 - Visible)**

- $1 \leq C \leq 100$
- $2 \leq N \leq 8$
- $1 \leq M < N$

**Large dataset (25 Pts, Test set 2 - Hidden)**

- $1 \leq C \leq 50$
- $2 \leq N \leq 100$
- $1 \leq M < N$


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
title: "[SWERC 2023] Supporting everyone"
layout: "post"
diff: 提高+/省选-
pid: P13793
tag: ['2023', '二分图', 'ICPC']
---
# [SWERC 2023] Supporting everyone
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/9b693d641063096ae32c5b06333b6fdf2138d3da.png)

:::

Alice is attending a sport event with many national teams and one thing is important to her: supporting every country.


There are $N$ countries represented and she has two ways to support a country: either have the flag drawn on her or have a pin with the name of the country. Alice has a list containing, for each country, the colours needed to make its flag. A total of $M$ colours that may appear across all flags and, in Alice&#39;s list, each colour is conveniently represented as an integer between $1$ and $M$.


Each crayon and pin cost $1$, but her budget is tight... Can you help her find the minimum she can spend to support everyone?
## 输入格式

The first line contains the two space-separated numbers $N$ and $M$.
Then follow $2N$ lines, grouped in pairs; the $(2i-1)^{\text{th}}$ and $2i^{\text{th}}$ lines represent the $i^{\text{th}}$ country.
More precisely, the $(2i-1)^{\text{th}}$ line contains a single integer $k_i$: the number of colours in the flag of the $i^{\text{th}}$ country.
Then, the $2i^{\text{th}}$ line contains $k_i$ space-separated numbers $c_{i,1}, c_{i,2}, \dots , c_{i,k_i}$; these are the colours in the flag of the $i^{\text{th}}$ country.


**Limits**
	
- $1 \leq N \leq 1\,000$;
- $1 \leq M \leq 100$;
- $1 \leq k_i \leq M$ for all $i \leq N$;
- $1 \leq c_{i,j} \leq M$ for all $i \leq N$ and $j \leq k_i$;
- for all $i \leq N$, the $M$ colour numbers 


## 输出格式

The output should contain a single line, consisting of a single number: the minimum amount Alice can spend on crayons and pins to represent every country.
## 样例

### 样例输入 #1
```
7 6
3
1 4 5
3
1 4 5
3
1 4 5
3
3 4 5
3
3 4 5
3
3 4 5
3
2 5 6
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
8 12
2
7 9
12
1 2 3 4 5 6 7 8 9 10 11 12
2
7 9
2
7 9
3
3 4 11
2
7 9
2
7 9
2
7 9
```
### 样例输出 #2
```
4
```
## 提示

**Sample Explanation 1**

The three first countries could be France, the Netherlands, and the Czech Republic, all represented by
blue (1), white (4), and red (5). The three next countries could be Italy, Hungary, and Bulgaria, with
green (3), white (4) and red (5). The last one could be Germany, with black (2), red (5), and yellow (6).
The minimum cost is 5: we buy four (blue, green, white, and red) crayons and one pin (for Germany).


**Sample Explanation 2**

We can buy two crayons for the colours 7 and 11 and buy two pins for a total cost of 4. All six countries
with flag colours 7 (red) and 11 (white) could be Canada, Indonesia, Japan, Malta, Monaco, and Poland.
The flag of Belize has 12 colours, including red and white, and the fifth country could be Botswana.


---

---
title: "[CERC 2022] Combination Locks"
layout: "post"
diff: 提高+/省选-
pid: P13806
tag: ['2022', '二分图', 'ICPC', 'CERC']
---
# [CERC 2022] Combination Locks
## 题目描述

Alice and Bob are playing with combination locks. Each of them has a combination lock that consists of $N$ rotating discs with digits 0 to 9 engraved on them. Their friend Charlie doesn’t have a lock and has devised a game to keep them occupied. He will keep track of whether the corresponding digits of their locks match and will describe the current situation with a difference pattern string $S$. The $j$-th character of $S$ is either '=' or '.' and indicates whether the $j$-th digits in Alice's and Bob's locks match or not, respectively.

Charlie will officiate the game, while Alice and Bob take turns with Alice starting first. On each move, a player has to change one digit of their combination lock. As Charlie only keeps track of the difference patterns, this pattern has to change for a move to be valid. He is also rather superstitious and has brought a list of patterns $P_i$ that must not appear during the game. Charlie's main task is to enforce the rule that no difference pattern repeats during the course of the game. The player who can't make a move loses the game.

Write a program that will determine the winner of the game if both players play optimally.
## 输入格式

The first line contains the number of test cases $T$. Each test case starts with a line containing two space-separated integers $N$ and $C$. This is followed by two lines that describe the starting configuration of Alice's and Bob's combination lock. A lock configuration is a string of $N$ digits. The following $C$ lines describe Charlie's superstitious patterns $P_i$. The superstitious list doesn't contain duplicates and it is guaranteed that the difference pattern of the starting lock configurations is not on the superstitious list.
## 输出格式

For every test case output one line with the name of the winner.
## 样例

### 样例输入 #1
```
3
2 2
12
89
=.
==
3 1
204
101
.==
3 2
000
000
...
==.
```
### 样例输出 #1
```
Alice
Bob
Bob
```
## 提示

### Comment

In the first example, the only move for Alice is to change the second digit from 2 to 9. Any other move is invalid because it doesn't change the difference pattern or because it would result in a superstitious pattern. Bob doesn't have a valid move, therefore Alice wins.

### Input limits

* $1 \leq T \leq 20$
* $1 \leq N \leq 10$
* $0 \leq C \leq 1000$


---

---
title: "[国家集训队] 稳定婚姻"
layout: "post"
diff: 提高+/省选-
pid: P1407
tag: ['强连通分量', 'Tarjan', '二分图']
---
# [国家集训队] 稳定婚姻
## 题目描述

我们已知 $n$ 对夫妻的婚姻状况，称第 $i$ 对夫妻的男方为 $B_i$，女方为 $G_i$。若某男 $B_i$ 与某女 $G_j$ 曾经交往过（无论是大学，高中，亦或是幼儿园阶段，$i \le j$），则当某方与其配偶（即 $B_i$ 与 $G_i$ 或 $B_j$ 与 $G_j$）感情出现问题时，他们有私奔的可能性。不妨设 $B_i$ 和其配偶 $G_i$ 感情不和，于是 $B_i$ 和 $G_j$ 旧情复燃，进而 $B_j$ 因被戴绿帽而感到不爽，联系上了他的初恋情人 $G_k$ ……一串串的离婚事件像多米诺骨牌一般接踵而至。若在 $B_i$ 和 $G_i$ 离婚的前提下，这 $2n$ 个人最终依然能够结合成 $n$ 对情侣，那么我们称婚姻 $i$ 为不安全的，否则婚姻 $i$ 就是安全的。

给定所需信息，你的任务是判断每对婚姻是否安全。
## 输入格式

第一行为一个正整数 $n$，表示夫妻的对数；

以下 $n$ 行，每行包含两个字符串，表示这 $n$ 对夫妻的姓名（先女后男），由一个空格隔开；

第 $n+2$ 行包含一个正整数 $m$，表示曾经相互喜欢过的情侣对数；

以下 $m$ 行，每行包含两个字符串，表示这 $m$ 对相互喜欢过的情侣姓名（先女后男），由一个空格隔开。
## 输出格式

输出文件共包含 $n$ 行，第 $i$ 行为 `Safe`（如果婚姻 $i$ 是安全的）或 `Unsafe`（如果婚姻 $i$ 是不安全的）。

## 样例

### 样例输入 #1
```
2
Melanie Ashley
Scarlett Charles
1
Scarlett Ashley
```
### 样例输出 #1
```
Safe
Safe
```
### 样例输入 #2
```
2
Melanie Ashley
Scarlett Charles
2
Scarlett Ashley
Melanie Charles
```
### 样例输出 #2
```
Unsafe
Unsafe
```
## 提示

对于 $20\%$ 的数据，$n \le 20$；

对于 $40\%$ 的数据，$n \le 100$，$m \le 400$；

对于 $100\%$ 的数据，所有姓名字符串中只包含英文大小写字母，大小写敏感，长度不大于 $8$，保证每对关系只在输入文件中出现一次，输入文件的最后 $m$ 行不会出现未在之前出现过的姓名，这 $2n$ 个人的姓名各不相同，$1 \le n \le 4000$，$0 \le m \le 20000$。


---

---
title: "运动员最佳匹配问题"
layout: "post"
diff: 提高+/省选-
pid: P1559
tag: ['搜索', '剪枝', '二分图', '状压 DP']
---
# 运动员最佳匹配问题
## 题目描述

羽毛球队有男女运动员各 $n$ 人。给定 $2$ 个 $n \times n$ 矩阵 $P$ 和 $Q$。$P_{i,j}$ 是男运动员 $i$ 和女运动员 $j$ 配对组成混合双打的男运动员竞赛优势；$Q_{i,j}$ 是女运动员 $i$ 和男运动员 $j$ 配合的女运动员竞赛优势。

但是，由于技术配合和心理状态等各种因素影响，$P_{i,j}$ 不一定等于 $Q_{j,i}$。男运动员 $i$ 和女运动员 $j$ 配对组成混合双打的男女双方竞赛优势为 $\bm{P_{i,j} \times Q_{j,i}}$。

现在，请你设计一个算法，计算男女运动员最佳配对法，使各组男女双方竞赛优势的总和达到最大。

## 输入格式

第一行有 $1$ 个正整数 $n$ $(1 \le n \le 20)$。接下来的 $2n$ 行，每行 $n$ 个数。前 $n$ 行是 $P$，后 $n$ 行是 $Q$。
## 输出格式

将计算出的男女双方竞赛优势的总和的最大值输出。
## 样例

### 样例输入 #1
```
3

10 2 3

2 3 4

3 4 5

2 2 2

3 5 3

4 5 1
```
### 样例输出 #1
```
52
```


---

---
title: "[SCOI2010] 连续攻击游戏"
layout: "post"
diff: 提高+/省选-
pid: P1640
tag: ['2010', '四川', '并查集', '各省省选', '二分图']
---
# [SCOI2010] 连续攻击游戏
## 题目描述

lxhgww 最近迷上了一款游戏，在游戏里，他拥有很多的装备，每种装备都有 $2$ 个属性，这些属性的值用 $[1,10000]$ 之间的数表示。当他使用某种装备时，他只能使用该装备的某一个属性。并且每种装备最多只能使用一次。游戏进行到最后，lxhgww 遇到了终极 boss，这个终极 boss 很奇怪，攻击他的装备所使用的属性值必须从 $1$ 开始连续递增地攻击，才能对 boss 产生伤害。也就是说一开始的时候，lxhgww 只能使用某个属性值为 $1$ 的装备攻击 boss，然后只能使用某个属性值为 $2$ 的装备攻击 boss，然后只能使用某个属性值为 $3$ 的装备攻击 boss……以此类推。现在 lxhgww 想知道他最多能连续攻击 boss 多少次？
## 输入格式

输入的第一行是一个整数 $N$，表示 lxhgww 拥有 $N$ 种装备接下来 $N$ 行，是对这 $N$ 种装备的描述，每行 $2$ 个数字，表示第 $i$ 种装备的 $2$ 个属性值。
## 输出格式

输出一行，包括 $1$ 个数字，表示 lxhgww 最多能连续攻击的次数。
## 样例

### 样例输入 #1
```
3
1 2
3 2
4 5

```
### 样例输出 #1
```
2
```
## 提示

对于 $30\%$ 的数据，保证 $N \le 10^3$。

对于 $100\%$ 的数据，保证 $N \le 10^6$。


---

---
title: "[ZJOI2009] 假期的宿舍"
layout: "post"
diff: 提高+/省选-
pid: P2055
tag: ['2009', '各省省选', '网络流', '浙江', '二分图']
---
# [ZJOI2009] 假期的宿舍
## 题目描述

学校放假了……有些同学回家了，而有些同学则有以前的好朋友来探访，那么住宿就是一个问题。

比如 A 和 B 都是学校的学生，A 要回家，而 C 来看B，C 与 A 不认识。我们假设每个人只能睡和自己直接认识的人的床。那么一个解决方案就是 B 睡 A 的床而 C 睡 B 的床。而实际情况可能非常复杂，有的人可能认识好多在校学生，在校学生之间也不一定都互相认识。

我们已知一共有 $n$ 个人，并且知道其中每个人是不是本校学生，也知道每个本校学生是否回家。问是否存在一个方案使得所有不回家的本校学生和来看他们的其他人都有地方住。

## 输入格式

第一行一个数 $T$ 表示数据组数。接下来 $T$ 组数据，每组数据第一行一个数 $n$ 表示涉及到的总人数。

接下来一行 $n$ 个数，第 $i$ 个数表示第 $i$ 个人是否是在校学生 ($0$ 表示不是，$1$ 表示是)。再接下来一行 $n$ 个数，第 $i$ 个数表示第 $i$ 个人是否回家 ($0$ 表示不回家，$1$ 表示回家，注意如果第 $i$ 个人不是在校学生，那么这个位置上的数是一个随机的数，你应该在读入以后忽略它)。

接下来 $n$ 行每行 $n$ 个数，第 $i$ 行第 $j$ 个数表示 $i$ 和 $j$ 是否认识 ($1$ 表示认识，$0$ 表示不认识，第 $i$ 行 $i$ 个的值为 $0$，但是显然自己还是可以睡自己的床)，认识的关系是相互的。

## 输出格式

对于每组数据，如果存在一个方案则输出 `^_^`，否则输出`T_T`。（注意输出的都是半角字符，即三个符号的 ASCII 码分别为 $94,84,95$）

## 样例

### 样例输入 #1
```
1
3
1 1 0
0 1 0
0 1 1
1 0 0
1 0 0
```
### 样例输出 #1
```
^_^
```
## 提示

对于 $30\%$ 的数据满足 $1 \le n \le 12$。

对于 $100\%$ 的数据满足 $1 \le n \le 50$，$1 \le T \le 20$。



---

---
title: "座位安排"
layout: "post"
diff: 提高+/省选-
pid: P2071
tag: ['二分图']
---
# 座位安排
## 题目背景

公元二零一四年四月十七日，小明参加了省赛，在一路上，他遇到了许多问题，请你帮他解决。

## 题目描述

已知车上有 $N$ 排座位，有 $2N$ 个人参加省赛，每排座位只能坐两人，且每个人都有自己想坐的排数，问最多使多少人坐到自己想坐的位置。
## 输入格式

第一行，一个正整数 $N$。

第二行至第 $2N+1$ 行，每行两个正整数 $S_{i, 1},S_{i, 2}$，为每个人想坐的排数。
## 输出格式

一个非负整数，为最多使得多少人满意。

## 样例

### 样例输入 #1
```
4
1 2
1 3
1 2
1 3
1 3
2 4
1 3
2 3

```
### 样例输出 #1
```
7
```
## 提示

对于 $10\%$ 的数据，$n \le 10$；

对于 $30\%$ 的数据，$n \le 50$；

对于 $60\%$ 的数据，$n \le 200$；

对于 $100\%$ 的数据，$n \le 2000$。


---

---
title: "[HNOI2006] 超级英雄"
layout: "post"
diff: 提高+/省选-
pid: P2319
tag: ['2006', '各省省选', '湖南', 'Special Judge', '二分图']
---
# [HNOI2006] 超级英雄
## 题目描述

现在电视台有一种节目叫做超级英雄，大概的流程就是每位选手到台上回答主持人的几个问题，然后根据回答问题的多少获得不同数目的奖品或奖金。主持人问题准备了若干道题目，只有当选手正确回答一道题后，才能进入下一题，否则就被淘汰。为了增加节目的趣味性并适当降低难度，主持人总提供给选手几个“锦囊妙计”，比如求助现场观众，或者去掉若干个错误答案（选择题）等等。


这里，我们把规则稍微改变一下。假设主持人总共有m道题，选手有n种不同的“锦囊妙计”。主持人规定，每道题都可以从两种“锦囊妙计”中选择一种，而每种“锦囊妙计”只能用一次。我们又假设一道题使用了它允许的锦囊妙计后，就一定能正确回答，顺利进入下一题。现在我来到了节目现场，可是我实在是太笨了，以至于一道题也不会做，每道题只好借助使用“锦囊妙计”来通过。如果我事先就知道了每道题能够使用哪两种“锦囊妙计”，那么你能告诉我怎样选择才能通过最多的题数吗？

## 输入格式

输入的第一行是两个正整数 $n$ 和 $m$ ($0 < n < 1001, 0 < m < 1001$)表示总共有 n 种“锦囊妙计”，编号为 $0 \sim n-1$，总共有 $m$ 个问题。


以下的m行，每行两个数，分别表示第 $m$ 个问题可以使用的“锦囊妙计”的编号。

**注意**，每种编号的“锦囊妙计”只能使用一次，同一个问题的两个“锦囊妙计”可能一样。

## 输出格式

输出的第一行为最多能通过的题数 $p$，接下来 $p$ 行，每行为一个整数，第 $i$ 行表示第 $i$ 题使用的“锦囊妙计的编号”。


如果有多种答案，那么任意输出一种，本题使用 Special Judge 评判答案。

## 样例

### 样例输入 #1
```
5 6
3 2
2 0
0 3
0 4
3 2
3 2
```
### 样例输出 #1
```
4
3
2
0
4
```
## 提示

感谢@zhouyonglong 提供special Judge



---

---
title: "[SDOI2006] 仓库管理员的烦恼"
layout: "post"
diff: 提高+/省选-
pid: P2457
tag: ['2006', '各省省选', '山东', '二分图', '费用流']
---
# [SDOI2006] 仓库管理员的烦恼
## 题目描述

仓库管理员M最近一直很烦恼，因为他的上司给了他一个艰难的任务：让他尽快想出一种合理的方案，把公司的仓库整理好。

已知公司共有n个仓库和n种货物，由于公司进货时没能很好的归好类，使得大部分的仓库里面同时装有多种货物，这就给搬运工作人员搬运货物时带来了很多的麻烦。

仓库管理员M的任务就是设计一种合理的方案，把仓库里面的货物重新整理，把相同的货物放到同一个仓库，以便于日后的管理，在整理过程中肯定需要把某些货物从一个仓库搬运到另一个仓库，已知每一次搬运货物所付出的代价等于搬运该货物的重量。

编程任务：

请你帮助仓库管理员M设计搬运方案，使得把所有的货物归好类：使每种货物各自占用一个仓库，或者说每个仓库里只能放一种货物。同时要求搬运货物时所付出的所有的总的代价最小。

## 输入格式

第一行为n (1 <= n <= 150)，仓库的数量。

以下为仓库货物的情况。第i+1行依次为第i个仓库中n种货物的数量x(0 <= x <= 100)。

## 输出格式

把所有的货物按要求整理好所需的总的最小代价。

## 样例

### 样例输入 #1
```
4
62 41 86 94 
73 58 11 12 
69 93 89 88 
81 40 69 13 

```
### 样例输出 #1
```
650
```
## 提示

样例说明：方案是：第1种货物放到仓库2中；第2种货物放到仓库3中；第3种货物放到仓库4中；第4种货物放到仓库1中



---

---
title: "[USACO11NOV] Cow Steeplechase G"
layout: "post"
diff: 提高+/省选-
pid: P3033
tag: ['2011', 'USACO', '二分图']
---
# [USACO11NOV] Cow Steeplechase G
## 题目描述

Farmer John has a brilliant idea for the next great spectator sport: Cow Steeplechase! As everyone knows, regular steeplechase involves a group of horses that race around a course filled with obstacles they must jump over. FJ figures the same contest should work with highly-trained cows, as long as the obstacles are made short enough.

In order to design his course, FJ makes a diagram of all the N (1 <= N <= 250) possible obstacles he could potentially build. Each one is represented by a line segment in the 2D plane that is parallel to the horizontal or vertical axis. Obstacle i has distinct endpoints (X1\_i, Y1\_i) and (X2\_i, Y2\_i) (1 <= X1\_i, Y1\_i, X2\_i, Y2\_i <= 1,000,000,000). An example is as follows:

```cpp

   --+-------   
-----+-----
  ---+---     |
     |     |  |
   --+-----+--+-   |
     |     |  |  | |
     |   --+--+--+-+-
           |  |  | |
              |
```
FJ would like to build as many of these obstacles as possible, subject to the constraint that no two of them intersect. Starting with the diagram above, FJ can build 7 obstacles:

```cpp

   ----------   
-----------
  -------     |
           |  |
           |  |    |
           |  |  | |
           |  |  | |
           |  |  | |
              |

```
Two segments are said to intersect if they share any point in common, even an endpoint of one or both of the segments.  FJ is certain that no two horizontal segments in the original input diagram will intersect, and that similarly no two vertical segments in the input diagram will intersect.

Please help FJ determine the maximum number of obstacles he can build.

给出 $N$ 条**平行于坐标轴**的线段，要你选出尽量多的线段使得这些线段两两没有交点（顶点也算）。横的与横的，竖的与竖的线段之间保证没有交点，输出最多能选出多少条线段。

## 输入格式

\* Line 1: A single integer: N.

\* Lines 2..N+1: Line i+1 contains four space-separated integers representing an obstacle: X1\_i, Y1\_i, X2\_i, and Y2\_i.

## 输出格式

\* Line 1: The maximum number of non-crossing segments FJ can choose.

## 样例

### 样例输入 #1
```
3 
4 5 10 5 
6 2 6 12 
8 3 8 5 

```
### 样例输出 #1
```
2 

```
## 提示

There are three potential obstacles. The first is a horizontal segment connecting (4, 5) to (10, 5); the second and third are vertical segments connecting (6, 2) to (6, 12) and (8, 3) to (8, 5).


The optimal solution is to choose both vertical segments.



---

---
title: "分配问题"
layout: "post"
diff: 提高+/省选-
pid: P4014
tag: ['深度优先搜索 DFS', '二分图', '费用流', '网络流与线性规划 24 题']
---
# 分配问题
## 题目描述

有 $n$ 件工作要分配给 $n$ 个人做。第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{ij}$ 。试设计一个将 $n$ 件工作分配给 $n$ 个人做的分配方案，使产生的总效益最小或最大。

## 输入格式

文件的第一行有 $1$ 个正整数 $n$，表示有 $n$ 件工作要分配给 $n$ 个人做。

接下来的 $n$ 行中，每行有 $n$ 个整数 $c_{i,j}$，表示第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{i,j}$。

## 输出格式

两行分别输出最小总效益和最大总效益。

## 样例

### 样例输入 #1
```
5
2 2 2 1 2
2 3 1 2 4
2 0 1 1 1
2 3 4 3 3
3 2 1 2 1
```
### 样例输出 #1
```
5
14
```
## 提示

$1 \leq n \leq 50, 0 \le c _ {i, j} \le 100$。

一个人只能修一个工件。


---

---
title: "[TJOI2013] 攻击装置"
layout: "post"
diff: 提高+/省选-
pid: P4304
tag: ['2013', '各省省选', '网络流', '二分图', '天津']
---
# [TJOI2013] 攻击装置
## 题目描述

给定一个 01 矩阵，其中你可以在 0 的位置放置攻击装置。每一个攻击装置 $(x,y)$ 都可以按照“日”字攻击其周围的 $8$ 个位置 $(x-1,y-2)$，$(x-2,y-1)$，$(x+1,y-2)$，$(x+2,y-1)$，$(x-1,y+2)$，$(x-2,y+1)$，$(x+1,y+2)$，$(x+2,y+1)$。

求在装置互不攻击的情况下，最多可以放置多少个装置。
## 输入格式

第一行一个整数 $N$，表示矩阵大小为 $N \times N$。

接下来 $N$ 行每一行一个长度 $N$ 的 01 串，表示矩阵。
## 输出格式

一个整数，表示在装置互不攻击的情况下最多可以放置多少个装置。
## 样例

### 样例输入 #1
```
3
010
000
100
```
### 样例输出 #1
```
4
```
## 提示

对于 $30\%$ 的数据，保证 $N \le 50$。

对于 $100\%$ 的数据，保证 $N \le 200$。


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
title: "[NOI Online #1 提高组] 序列"
layout: "post"
diff: 提高+/省选-
pid: P6185
tag: ['2020', '并查集', '二分图', 'NOI Online']
---
# [NOI Online #1 提高组] 序列
## 题目背景

## 由于本题数据较难构造，所以无法保证卡掉所有错误做法。


## 题目描述

小 D 有一个长度为 $n$ 的整数序列 $a_{1 \dots n}$，她想通过若干次操作把它变成序列 $b_i$。

小 D 有 $m$ 种可选的操作，第 $i$ 种操作可使用三元组 $(t_i,u_i,v_i)$ 描述：若 $t_i=1$，则她可以使 $a_{u_i}$ 与 $a_{v_i}$ 都加一或都减一；若 $t_i=2$，则她可以使 $a_{u_i}$ 减一、$a_{v_i}$ 加一，或是 $a_{u_i}$ 加一、$a_{v_i}$ 减一，因此当 $u_i=v_i$ 时，这种操作相当于没有操作。

小 D 可以以任意顺序执行操作，且每种操作都可进行无限次。现在给定序列与所有操作，请你帮她判断是否存在一种方案能将 $a_i$ 变为 $b_i$。题目保证两个序列长度都为 $n$。若方案存在请输出 `YES`，否则输出 `NO`。
## 输入格式

本题输入文件包含多组数据。

第一行一个正整数 $T$ 表示数据组数。对于每组数据：

第一行两个整数 $n,m$，表示序列长度与操作种数。

第二行 $n$ 个整数表示序列 $a_i$。

第三行 $n$ 个整数表示序列 $b_i$。

接下来 $m$ 行每行三个整数 $t_i,u_i,v_i$，第 $i$ 行描述操作 $i$。

注意：同一个三元组 $(t_i,u_i,v_i)$ 可能在输入中出现多次。
## 输出格式

对于每组数据输出一行一个字符串 `YES` 或 `NO` 表示答案。
## 样例

### 样例输入 #1
```
3
1 1
1
3
1 1 1
2 3
1 2
4 5
1 1 2
2 1 2
1 1 2
3 3
1 2 3
5 5 4
1 1 2
1 1 3
2 2 3
```
### 样例输出 #1
```
YES
YES
YES
```
## 提示

#### 样例 1 解释

第一组数据：使用一次操作 $1$。  
第二组数据：使用三次操作 $1$。  
第三组数据：使用三次操作 $1$，令 $a_1,a_2$ 都增加 $3$，再使用一次操作 $2$，令 $a_1,a_3$ 都增加 $1$。

---

#### 数据范围与提示

对于测试点 $1 \sim 5$：$n=2$，$m=1$，$a_i,b_i \le 99$，$u_1 \ne v_1$，$t_1=1$。  
对于测试点 $6 \sim 10$：$n=2$，$m=1$，$a_i,b_i \le 99$，$u_1 \ne v_1$，$t_1=2$。  
对于测试点 $11 \sim 12$：$n=2$，$a_i,b_i \le 99$，$u_i \ne v_i$。  
对于测试点 $13 \sim 16$：$t_i=2$。  
对于测试点 $17$：$n,m \le 20$。  
对于测试点 $18$：$n,m \le 10^3$。  
对于所有测试点：$1 \le T \le 10$，$1 \le n,m \le 10^5$，$1 \le a_i,b_i \le 10^9$，$t_i \in \{1,2\}$，$1\le u_i,v_i \le n$。


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
title: "[USACO05NOV] Asteroids G"
layout: "post"
diff: 提高+/省选-
pid: P7368
tag: ['2005', 'USACO', '网络流', '二分图']
---
# [USACO05NOV] Asteroids G
## 题目描述

贝茜想在 $N\times N$ 的网格中驾驶她的宇宙飞船。网格中有 $K$ 个小行星。要使驾驶过程愉快，就必须把这些小行星全部消除。

贝茜有一个武器，可以以一个单位代价消除一行或一列的全部小行星。贝茜想问你，要把所有小行星都消除的最小代价是多少。
## 输入格式

第一行两个整数 $N,K$。

接下来 $K$ 行，每行输入 $x_i,y_i$，表示第 $i$ 个小行星在网格的坐标。
## 输出格式

一行一个整数，表示把所有小行星消除的最小代价。
## 样例

### 样例输入 #1
```
3 4
1 1
1 3
2 2
3 2


```
### 样例输出 #1
```
2
```
## 提示

#### 样例解释：

样例的图为（`X` 为小行星）：

```text
X.X
.X.
.X.
```

贝茜可以分别消除第一行和第二列的小行星。

---

#### 数据范围：

对于 $100\%$ 的数据，$1 \leq N \leq 500$，$1 \leq K \leq N \times N$。


---

---
title: "「Wdoi-6」最澄澈的空与海"
layout: "post"
diff: 提高+/省选-
pid: P8346
tag: ['搜索', '图论', '洛谷原创', 'O2优化', '二分图', '洛谷月赛']
---
# 「Wdoi-6」最澄澈的空与海
## 题目背景

[![](https://cdn.luogu.com.cn/upload/image_hosting/hiekh6t5.png)](https://thwiki.cc/%E5%8D%AF%E9%85%89%E4%B8%9C%E6%B5%B7%E9%81%93_%EF%BD%9E_Retrospective_53_minutes.)

广重号载着二人向东飞驰。毫无噪音，毫无摇摆，只是一个劲向东飞驰。在“万景幕”装置之下，尽管是全地下的卯酉东海道，乘客们也能饱览美丽的富士山和太平洋的景色。

但是，从这列卯酉新干线『广重』上看到的极富日本风味的美丽情景，对于梅莉来说，只不过是无趣的视觉刺激罢了。高动态范围的影像也好，极富日本风味的情景也好，都敌不过真正的天空的颜色。

身与华落，心将香飞。即便肉体会像花朵一样终有一天凋落，但心却可以如花香一般飘往远方。

「梅莉，你看，天上的星星呦。」
## 题目描述

### 简要题意

给定 $2n$ 个点、$m$ 条边的[二分图](http://oi-wiki.com/graph/bi-graph/#_1)（可能有重边），左部点与右部点个数相同，判断其完美匹配数量是否**恰好**为 $1$。是则输出 `Renko`，否则输出 `Merry`。

> **注**：完美匹配是指，从边集中选出 $n$ 条边，这些边的顶点组成的点集恰好覆盖了所有的 $2n$ 个点。

---
### 原始题意

在夜里，莲子与梅莉来到了东京的海边，躺在沙滩上，欣赏着澄澈的天空与大海，数起了天上的星星。

在这些星星之中，有 $n$ 个星星 $\{a_i\}$，是莲子先发现的，被称为莲子星；而又有 $n$ 个星星 $\{b_i\}$，是梅莉先发现的，被称为梅莉星。由于她们心有灵犀，这两批星星之间**不存在交集**。  

她们发现，有一些莲子星，与一些梅莉星之间恰好存在运动关系。具体而言，这些关系一共有 $m$ 组，每一组关系形如 $(u_i,v_i)$，也就是说第 $u_i$ 颗莲子星与第 $v_i$ 颗梅莉星之间存在运动关系。这些运动关系有可能重复。

这让莲子和梅莉非常好奇。作为专攻超统一物理学的女大学生，莲子认为，如果认为这些星星的运动是**和谐**的，那么她应当能够从这 $m$ 个运动关系中，找出若干个运动关系，使得**每颗**星星**都被**这些运动关系**包含**的同时，不会有一颗星星**被包含在两个**运动关系之中。

然而，梅莉认为，**和谐**的运动可能是不存在的，更何况即使莲子找到了**和谐**的运动，莲子也无法确保这种和谐运动的**唯一性**。两种和谐运动不同，当且仅当选取出的两组运动关系中，存在至少一个运动关系，是不相同的。

因为意见不合，她们于是打情骂俏了一顿。莲子于是记下了她们所看到了星星和她们之间的运动关系，并且找到了已经证明了 P=NP 的你，希望你能告诉她们，最后是谁正确呢？
## 输入格式

第一行输入一个正整数 $T$ 表示数据组数，对于每一组数据：

- 第一行一个整数 $n$，代表莲子和梅莉每个人所先发现的星星的数量。
- 第二行一个整数 $m$，代表运动关系的数量。
- 接下来 $m$ 行，每行两个整数 $u_i,v_i$，表示第 $u_i$ 颗莲子星，与第 $v_i$ 颗梅莉星之间，存在运动关系。
## 输出格式

- 如果这些星星中存在唯一的和谐运动，输出 `Renko`。
- 如果这些星星中不存在和谐运动，或者有不唯一的和谐运动方式，输出 `Merry`。
## 样例

### 样例输入 #1
```
1
5
6
1 1
1 3
3 2
2 5
4 3
5 4
```
### 样例输出 #1
```
Renko
```
## 提示

### 样例解释

#### 样例 \#1

![](https://cdn.luogu.com.cn/upload/image_hosting/6skoily9.png)

如图所示，存在唯一的方案：$\{1\to 1,2\to 5,3\to 2,4\to 3,5\to 4\}$。

### 数据范围

**本题采用捆绑测试。**

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|}\hline
\textbf{Subtask} & \textbf{\textsf{分值}} & \bm{n\le } & \bm{m\le} & \textbf{\textsf{特殊性质}} & \textbf{Subtask \textsf{依赖}}\cr\hline
1 & 10 & 10 & 10 & - & - \cr\hline
2 & 20 & 300 & 4\times 10^4 & - & 1\cr\hline
3 & 20 & 10^5 & 5 \times 10^5 & \mathbf{A} & - \cr\hline
4 & 20 & 10^5 & 2 \times 10^5 & \mathbf{B} & - \cr\hline
5 & 30& 10^6 & 2\times 10^6 & - & 2,3,4 \cr\hline
\end{array}
$$

- 特殊性质 $\mathbf{A}$：保证对于第 $i$ 颗莲子星，与第 $i$ 颗梅莉星之间存在运动关系。
- 特殊性质 $\mathbf{B}$：保证 $m=2n-1$。

对于 $100\%$ 的数据，保证 $1 \le u_i,v_i\le n \le 10^6$，$1 \le m \le 2 \times 10^6$，$1 \leq T \leq 5$ 且对于每个测试点，$\sum m \leq 4 \times 10^6$。

对于 $\rm Subtask\ 5$，时间限制为 $3$ 秒。其它测试点时间限制为 $1$ 秒。


---

---
title: "[ICPC 2022 Xi'an R] Cells Coloring"
layout: "post"
diff: 提高+/省选-
pid: P9359
tag: ['2022', '网络流', 'O2优化', '二分图', 'ICPC']
---
# [ICPC 2022 Xi'an R] Cells Coloring
## 题目描述

You are given an $n \times m$ grid. Some of the cells are obstacles, the others are empty. Choose a non-negative integer $k$ and color all empty cells with $k+1$ colors $0, 1, 2, \ldots k$. You can not color two cells in the same row or same column with the same **non-zero** color. 

You are given two non-negative integers $c$ and $d$. For a coloring plan, define $z$ as the number of the cells with color $0$. Define the cost of the plan is $ck+dz$.

Find the minimum cost.
## 输入格式

The first line contains four integers $n$, $m$ ($1\leq n, m\leq 250$), $c$ and $d$ ($0\leq c, d\leq 10 ^ 9$).

The $i$-th line of the next $n$ lines contains a string of $m$ characters. The $j$-th character is `*` if the cell in the $i$-th row and the $j$-th column is an obstacle. The $j$-th character is `.` if the cell in the $i$-th row and the $j$-th column is empty.
## 输出格式

Output a line with a single number, representing the answer.
## 样例

### 样例输入 #1
```
3 4 2 1
.***
*..*
**..

```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
3 4 1 2
.***
*..*
**..

```
### 样例输出 #2
```
2
```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem B.

**Author**: csy2005.
## 题目翻译

### 题目描述

给定一个 $n\times m$ 的网格。一些格子是障碍，其它格子是空的。选择一个非负整数 $k$，并用 $k + 1$ 种颜色 $0, 1, \ldots, k$ 给空格子染色。不能有同一行或同一列的两个格子被染成了相同的 **非零** 颜色。

给定两个非负整数 $c, d$。对于一组染色方案，定义 $z$ 表示染成颜色 $0$ 的格子数量，则该方案的代价为 $ck + dz$。

求出最小代价。

$1\leq n, m \leq 250$，$0\leq c, d\leq 10 ^ 9$。

### 输入格式

第一行四个整数 $n, m, c, d$。

接下来 $n$ 行，每行一个长度为 $m$ 的字符串。字符串的第 $j$ 个字符为 `*` 表示第 $i$ 行第 $j$ 列的格子为障碍，为 `.` 表示为空。

### 输出格式

输出一行一个整数表示答案。




---

