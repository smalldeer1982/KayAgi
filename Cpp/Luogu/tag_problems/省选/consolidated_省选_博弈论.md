---
title: "[COTS 2022] 点组 Točkice"
layout: "post"
diff: 省选/NOI-
pid: P10876
tag: ['博弈论', '2022', 'O2优化', '凸包', 'COCI（克罗地亚）']
---
# [COTS 2022] 点组 Točkice
## 题目背景

译自 [Izborne Pripreme 2022 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2022/) D2T3。$\texttt{1s,0.5G}$。
## 题目描述


二维平面上画了 $N$ 个点 $(x_i,y_i)$，其中任意三点不共线。

从 A 开始，AB 两人轮流玩游戏：

- 选择两个点 $(x_i,y_i),(x_j,y_j)$（$i\neq j$）。若连接这两点的线段不与之前的线段相交，则在两点间连一条线段。
- 不能操作的玩家负。

需要注意的是：**线段可以在顶点处相交**（即可以共用一个顶点）。

A 和 B 都绝顶聪明，请你判断鹿死谁手。

## 输入格式

第一行，一个整数 $N$；

接下来 $N$ 行，每行两个整数 $x_i,y_i$。
## 输出格式

如果 A（先手）胜，输出 `Alenka`；否则输出 `Bara`。
## 样例

### 样例输入 #1
```
4
0 0
0 10
10 0
10 10
```
### 样例输出 #1
```
Alenka
```
### 样例输入 #2
```
5
2 1
1 3
6 4
3 5
5 2
```
### 样例输出 #2
```
Alenka
```
### 样例输入 #3
```
4
4 2
2 4
2 2
1 1
```
### 样例输出 #3
```
Bara
```
## 提示


对于 $100\%$ 的数据，保证：

- $1\le N\le 10^5$；
- $1\le x_i,y_i\le 10^6$；
- 任意三点不共线。

| 子任务编号 | 分值 | $N\le$ |
|:-----:|:------:|:-------:|
| $1$  | $13$  | $7$  |
| $2$  | $17$  | $300$  |
| $3$  | $21$  | $1\, 000$ |
| $4$  | $49$  | $10^5$ |


---

---
title: "【MX-S4-T3】「yyOI R2」youyou 的序列 II"
layout: "post"
diff: 省选/NOI-
pid: P11219
tag: ['博弈论', '线段树', '树状数组', 'O2优化', '梦熊比赛']
---
# 【MX-S4-T3】「yyOI R2」youyou 的序列 II
## 题目背景

原题链接：<https://oier.team/problems/S4C>。
## 题目描述

给定一个长度为 $n$ 的非负整数序列 $a$，初始时所有数均被标记为**蓝色**，youyou 和 yy 轮流对序列 $a$ 进行操作，由 youyou 开始。

- 如果当前是 youyou 的回合，那么他可以选择一个长度至多为 $c_1$ 的区间，如果该区间内所有数的和小于等于 $w_1$，则标记该区间所有数为**红色**。

- 如果当前是 yy 的回合，那么他可以选择一个长度至多为 $c_2$ 的区间，如果该区间内所有数的和大于 $w_2$，则标记该区间所有数为**蓝色**。

如果当前操作方没有可操作的区间，他将跳过本回合。

定义 youyou 胜利即是在游戏任意时刻，所有数都被标记为红色。定义 yy 胜利则是在 $10^{51971}$ 个回合内，youyou 无法胜利。两者都会以最优策略进行游戏。

但是他们认为这个游戏太简单了，于是决定上上强度。

现在给定 $q$ 个操作，对于每个操作给定三个数 $opt,x,y$。

- 如果 $opt$ 为 $1$，表示将 $a_x$ 增加 $y$（$0\le y \le 10^9$）。
- 如果 $opt$ 为 $2$，表示 youyou 和 yy 将在区间 $[x,y]$ 所形成的序列上进行一轮游戏。

对于每个 $opt=2$ 的操作，请你求出在区间 $[x,y]$ 所形成的序列上进行游戏，youyou 能否获得胜利。如果 youyou 能胜利，输出 ```cont```；否则，输出 ```tetris```。

## 输入格式

第一行，六个整数 $n,q,c_1,c_2,w_1,w_2$，其中 $n$ 为序列长度，$q$ 为操作个数，$c_1,c_2,w_1,w_2$ 的定义在题目描述中给出。

第二行，$n$ 个整数 $a_1, a_2, \ldots, a_n$。

接下来 $q$ 行，每行三个整数 $opt,x,y$，表示一个操作，操作的定义在上面已给出。
## 输出格式

对于每一个 $opt=2$ 的操作，输出一行表示答案。

## 样例

### 样例输入 #1
```
5 3 4 2 2 3
1 0 0 1 1
2 1 5
1 3 3
2 1 5
```
### 样例输出 #1
```
cont
tetris

```
### 样例输入 #2
```
8 6 10 3 5 2
0 1 0 0 1 0 0 1
2 1 7
1 4 2
2 5 7
1 5 1
1 7 2
2 1 8
```
### 样例输出 #2
```
cont
cont
tetris

```
## 提示

**【样例解释 #1】**

第一次游戏在序列 $[1,0,0,1,1]$ 上进行。

回合 $1$：youyou 将区间 $[1,3]$ 内的数染红。

回合 $2$：yy 没有可操作的区间，**跳过**了本回合。

回合 $3$：youyou 将区间 $[4,5]$ 内的数染红。

此时所有数都被染红，youyou 获胜，输出  ```cont```。

第二次游戏在序列 $[1,0,3,1,1]$ 上进行。

容易发现，此时 youyou 无法获胜，输出 ```tetris```。


**【样例 #3】**

见附件中的 ```seq/seq3.in``` 与 ```seq/seq3.ans```。

该组样例满足测试点 $5\sim 8$ 的约束条件。

**【样例 #4】**

见附件中的 ```seq/seq4.in``` 与 ```seq/seq4.ans```。

该组样例满足测试点 $9\sim10$ 的约束条件。

**【样例 #5】**

见附件中的 ```seq/seq5.in``` 与 ```seq/seq5.ans```。

该组样例满足测试点 $11\sim 14$ 的约束条件。

**【数据范围】**

本题共 $20$ 个测试点，每个 $5$ 分。

|  测试点编号  |          $n$          |         $q$         |  特殊性质  |
| :----------: | :-------------------: | :-----------------: | :--------: |
|  $1\sim 4$   |       $\le10^2$       | $\le 3 \times 10^2$ | A |
|  $5 \sim 8$  |       $\le10^3$       | $\le 3 \times 10^3$ | B |
| $9 \sim 10$  |       $\le10^4$       | $\le 3 \times 10^4$ | C |
| $11 \sim 14$ |     $\le  10 ^ 5$     | $\le 3 \times 10^5$ | D |
| $15\sim 20$  | $\le 3 \times 10 ^ 5$ | $\le 3 \times 10^5$ |     无     |

特殊性质 A：$c_2 > n$，$w_2 = 0$。  
特殊性质 B：$w_1 \le w_2$。  
特殊性质 C：$c_1 \le c_2$。  
特殊性质 D：$c_1,c_2 \le 10^3$。

对于全部数据，保证：
- $1\le n,q,c_1,c_2\le 3\times10^5$。
- $0\le a_i,w_1,w_2\le 10^9$。
- $opt\in \{1,2\}$。
- 对于 $opt=1$ 的操作，$1\leq x\leq n$，$0\leq y\leq 10^9$。
- 对于 $opt=2$ 的操作，$1\leq x\leq y\leq n$。
- 至少有一个 $2$ 类操作。


---

---
title: "【MX-X7-T6】[LSOT-3] 棋盘"
layout: "post"
diff: 省选/NOI-
pid: P11565
tag: ['动态规划 DP', '博弈论', 'O2优化', 'Ad-hoc', '分类讨论', '梦熊比赛']
---
# 【MX-X7-T6】[LSOT-3] 棋盘
## 题目背景

原题链接：<https://oier.team/problems/X7G>。

现在有一个序列。

这个序列第 $1$ 项为 $0$，第 $2$ 项为 $1$，第 $3$ 项为 $1$，第 $4$ 项为 $3$。

现在 [@lxwtr](https://www.luogu.com.cn/discuss/875194) 问你第 $n$ 项的值为多少。
## 题目描述

Alice 和 Bob 找到了一个棋盘。棋盘可以看成一个数轴，初始时在原点处有 $n$ 个棋子。令 $a_i$ 表示数轴下标为 $i$ 的位置的棋子数量（原点 $i=0$），操作者每次会找到最小的满足 $a_i\ge 2$ 的 $i$，令 $a_i$ 减去 $2$ 并选择令 $a_{i+1}$ 加上 $1$ 或令 $a_{i+2}$ 加上 $1$。由 Alice 先手，二人轮流操作。操作者必须操作，如果无法找到这样的 $i$ 则立即结束游戏。

Alice 希望二人的总操作次数最少，Bob 希望二人的总操作次数最多，二人都是绝对聪明的。二人一共进行了 $T$ 次游戏，你希望知道每次游戏最终二人一共会进行多少次操作。
## 输入格式

第一行，一个正整数 $T$，表示进行的游戏次数。

接下来 $T$ 行，每行一个正整数 $n$，表示每次游戏开始时，原点的棋子个数。
## 输出格式

共 $T$ 行，第 $i$ 行一个非负整数，表示第 $i$ 次游戏最终二人一共会进行多少次操作。
## 样例

### 样例输入 #1
```
6
1
2
3
4
100
100000

```
### 样例输出 #1
```
0
1
1
3
95
99989

```
## 提示

**【样例解释】**

对于第一次游戏，原点棋子数为 $1$，无法进行操作。

对于第二次游戏，可以恰好进行一次操作之后使得 $a_1=1$ 或 $a_2=1$。无论哪一种都无法继续操作。

对于第三次游戏，类似第二次游戏，额外在原点留下了一个棋子。

对于第四次游戏，第一次操作无论 Alice 操作后将棋子放在哪个位置，Bob 都可以放在那个位置，这样 Alice 会再进行一次操作。总共 $3$ 次操作。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（5 分）：$n\le16$。
- 子任务 2（6 分）：$n\le 50$。
- 子任务 3（14 分）：$n\le 200$。
- 子任务 4（20 分）：$n\le 5000$。
- 子任务 5（21 分）：$n\le 10^5$。
- 子任务 6（34 分）：无特殊性质。

对于全部的数据，$1\le T\le 500$，$1\le n\le 10^{18}$。


---

---
title: "[UOI 2021] 数字图"
layout: "post"
diff: 省选/NOI-
pid: P12576
tag: ['博弈论', '2021', '拓扑排序', 'UOI（乌克兰）']
---
# [UOI 2021] 数字图
## 题目描述

瓦西里和彼得里克发现了一个数字图——这是一个连通的有向图，每个顶点上都标有一个数字。

两人急需一个数字，于是决定在图上游玩一个游戏。他们将棋子放在编号为 1 的顶点上。每一回合可以选择以下两种操作之一：
1. 结束游戏并获得当前顶点上的数字；
2. 沿着有向边将棋子移动到相邻顶点。

如果游戏进行到 $10^{100}$ 回合仍未结束，则自动终止并获得当前顶点上的数字。

瓦西里先手，他希望最大化最终获得的数字；而彼得里克则希望最小化这个数字。假设双方都采取最优策略，求游戏结束时他们将获得的数字。
## 输入格式

第一行包含两个整数 $n$ 和 $m$（$1 \leq n \leq 250\,000$，$1 \leq m \leq 500\,000$）——分别表示图的顶点数和边数。

第二行包含 $n$ 个整数 $a_i$（$1 \leq a_i \leq 10^9$）——表示每个顶点上的数字。

接下来的 $m$ 行，每行包含两个整数 $x$ 和 $y$（$1 \leq x, y \leq n$），表示存在一条从顶点 $x$ 指向 $y$ 的有向边。
## 输出格式

输出一个整数，表示在双方都采取最优策略时，游戏结束时获得的数字。
## 样例

### 样例输入 #1
```
4 4
1 10 4 5
1 2
2 3
2 4
3 1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
2 2
1 2
1 2
2 1
```
### 样例输出 #2
```
1
```
## 提示

第一个样例的图示如图 1 所示，顶点标注格式为"顶点编号（数字）"：

![](https://cdn.luogu.com.cn/upload/image_hosting/ssfvk5ca.png)
1. 瓦西里先手，可以选择立即结束游戏或移动到顶点 2。最优选择是移动。
2. 彼得里克回合，最优选择是移动到顶点 3。
3. 最后如果瓦西里移动到顶点 1，彼得里克会结束游戏获得数字 1，因此瓦西里会选择直接结束游戏获得数字 4。

第二个样例的图示如图 2 所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/9crldhqu.png)

双方将交替移动 $10^{100}$ 步，最终棋子停留在顶点 1。

### 评分标准

1. （$6$ 分）给定的图是一条所有边同向的直线；
2. （$8$ 分）给定的图是一棵以顶点 1 为根的树，所有边方向从根向下；
3. （$14$ 分）给定的图是一个环；
4. （$26$ 分）$1 \leq a_i \leq 2$；
5. （$46$ 分）无额外限制。

翻译由 DeepSeek V3 完成


---

---
title: "[GCJ 2020 Finals] Adjacent and Consecutive"
layout: "post"
diff: 省选/NOI-
pid: P13071
tag: ['博弈论', '2020', '记忆化搜索', 'Google Code Jam']
---
# [GCJ 2020 Finals] Adjacent and Consecutive
## 题目描述

Two players, A and B, are playing a game. The game uses $\mathbf{N}$ tiles numbered 1 through $\mathbf{N}$, and a board consisting of a single horizontal row of $\mathbf{N}$ empty cells.

Players alternate turns, with Player A going first. On a turn, a player picks an unused tile and an empty cell and places the tile in the cell. At the end of the game, Player A wins if there are two tiles with consecutive numbers in adjacent cells (regardless of who put them there). Otherwise, Player B wins. For example, final boards of 1 2 3 4 and 4 1 3 2 are examples of wins for Player A, and a final board of 3 1 4 2 is an example of a win for Player B. (Notice that consecutive numbers may appear in either order.)

You just watched two players play a game, but you could not understand their strategy. They may not have played rationally! You decide to compare their moves against an optimal strategy.

A winning state is a state of the game from which the player whose turn it is can guarantee a win if they play optimally, regardless of what the opponent does. A mistake is a move made while in a winning state that results in the opponent having a winning state on their next turn. (Notice that it is not possible to make a mistake on the last turn of the game, since if the last turn begins with a winning state for that player, it must be because that player's only move results in a win.)

Given the $\mathbf{N}$ moves, count the number of mistakes made by each player.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each case begins with one line containing an integer $\mathbf{N}$: the number of tiles in the game (which is also the number of turns, and the number of cells on the board).

Then, $\mathbf{N}$ more lines follow. The $i$-th of these (counting starting from 1) has two integers $\mathbf{M_i}$ and $\mathbf{C_i}$. Respectively, these represent the tile chosen on the $i$-th turn, and the index of the cell (counting from 1 at the left end to $\mathbf{N}$ at the right end) where that tile is placed.

Note that it is Player A's turn whenever $i$ is odd, and Player B's turn whenever $i$ is even.
## 输出格式

For each test case, output one line containing `Case #x: a b`, where $x$ is the test case number (starting from 1), $a$ is the total number of mistakes made by Player A, and $b$ is the total number of mistakes made by Player B.
## 样例

### 样例输入 #1
```
3
6
2 2
3 5
4 3
6 6
1 4
5 1
4
4 1
1 3
3 4
2 2
4
3 1
2 2
4 3
1 4
```
### 样例输出 #1
```
Case #1: 2 1
Case #2: 0 0
Case #3: 0 0
```
## 提示

**Sample Explanation**

Notice that any game always begins in a winning state for Player A. For example, Player A can play tile 2 in cell 2 (i.e. the second cell from the left). No matter what Player B does on their turn, at least one of tiles 1 and 3 will be unused, and at least one of cells 1 and 3 will be empty. Then Player A can play one of those tiles in one of those cells, and this secures a win for Player A regardless of what happens in the rest of the game.

In Sample Case #1, the game plays out as follows:

* _ _ _ _ _ _. This is a winning state for Player A, as explained above.
* Turn 1: Player A plays tile 2 in cell 2.
* _ 2 _ _ _ _. This is not a winning state for Player B, as explained above; Player B cannot guarantee a win, regardless of their remaining choices in the game.
* Turn 2: Player B plays tile 3 in cell 5.
* _ 2 _ _ 3 _. This is a winning state for Player A; for example, they could play tile 1 in cell 3.
* Turn 3: Player A plays tile 4 in cell 3.
* _ 2 4 _ 3 _. This is a winning state for Player B; for example, they could play tile 5 in cell 1, and then they would be guaranteed to win no matter what Player A did. So Player A's last move was a mistake!
* Turn 4: Player B plays tile 6 in cell 6.
* _ 2 4 _ 3 6. This is a winning state for Player A, since Player A could play tile 1 in cell 1. So Player B's last move was a mistake!
* Turn 5: Player A plays tile 1 in cell 4.
* _ 2 4 1 3 6. This is a winning state for Player B, so Player A's last move was a mistake!
* Turn 6: Player B plays tile 5 in cell 1.
* 5 2 4 1 3 6. The game is over, and Player B has won.

In total, Player A made 2 mistakes and Player B made 1 mistake.

In Sample Case #2, although some of the moves may look risky, neither player made a mistake as defined in this problem. Player A never gave up a winning state to Player B, and Player B had no opportunity to make a mistake because they were never in a winning state.

In Sample Case #3, notice that even though the outcome of the game is determined after the second move (since that move creates a pair of adjacent and consecutive tiles), all tiles must be placed in each game. Moreover, although the second move assures Player A's victory, it is not a mistake for Player B because Player B was not in a winning state at the time.

**Limits**

- $1 \leq T \leq 100.$
- $1 \leq M_i \leq N,$ for all $i.$
- $M_i \neq M_j,$ for all $i \neq j.$
- $1 \leq C_i \leq N,$ for all $i.$
- $C_i \neq C_j,$ for all $i \neq j.$

**Test Set 1 (10 Pts, Visible Verdict)**

- $4 \leq N \leq 10.$

**Test Set 2 (32 Pts, Hidden Verdict)**

- $4 \leq N \leq 50.$


---

---
title: "[GCJ 2019 #1C] Bacterial Tactics"
layout: "post"
diff: 省选/NOI-
pid: P13114
tag: ['博弈论', '2019', 'SG 函数', 'Google Code Jam']
---
# [GCJ 2019 #1C] Bacterial Tactics
## 题目描述

Becca and Terry are microbiologists who have a friendly rivalry. When they need a break from their research, they like to play a game together. The game is played on a matrix of unit cells with $\mathbf{R}$ rows and $\mathbf{C}$ columns. Initially, each cell is either empty, or contains radioactive material.

On each player's turn, if there are no empty cells in the matrix, that player loses the game. Otherwise, they choose an empty cell and place a colony of bacteria there. Bacteria colonies come in two types: H (for "horizontal") and V (for "vertical").

* When a type H colony is placed into an empty cell, it occupies that cell (making it non-empty), and also tries to spread into the cell immediately to the west (if there is one) and the cell immediately to the east (if there is one).
* When a type V colony is placed into an empty cell, it occupies that cell (making it non-empty), and also tries to spread into the cell immediately to the south (if there is one) and the cell immediately to the north (if there is one).

Whenever a colony (of either type) tries to spread into a cell:

* If the cell contains radioactive material, the colony mutates and the player who placed the colony loses the game.
* If that cell is empty, the colony occupies that cell (making it non-empty), and then the rule above is triggered again (i.e. the colony will try to spread further).
* If the cell already contains bacteria (of any type), the colony does not spread into that cell.

Notice that it may be possible that all of a player's available moves would cause them to lose the game, and so they are doomed. See the sample case explanations below for examples of how the game works.

Becca makes the first move, and then the two players alternate moves until one of them loses the game. If both players play optimally, who will win? And, if Becca will win, how many distinct winning opening moves does she have? (Two opening moves are distinct if and only if they either use different cells, or different kinds of colony, or both.)

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each case begins with one line containing two integers $\mathbf{R}$ and $\mathbf{C}$: the number of rows and columns, respectively, in the matrix. Then, there are $\mathbf{R}$ more rows of $\mathbf{C}$ characters each. The j-th character on the i-th of these lines represents the j-th column of the i-th row of the matrix. Each character is either . (an empty cell) or # (a cell with radioactive material).

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1), and $y$ is an integer: either 0 if Becca will not win, or, if Becca will win, the number of distinct winning opening moves she can make, as described above.
## 样例

### 样例输入 #1
```
5
2 2
..
.#
4 4
.#..
..#.
#...
...#
3 4
#.##
....
#.##
1 1
.
1 2
##
```
### 样例输出 #1
```
Case #1: 0
Case #2: 0
Case #3: 7
Case #4: 2
Case #5: 0
```
## 提示

**Sample Explanation**

In Sample Case #1, Becca cannot place an H colony in the southwest empty cell or a V colony in the northeast empty cell, because those would spread onto a radioactive cell and Becca would lose. She has only two possible strategies that do not cause her to lose immediately:

1. Place an H colony in the northwest or northeast empty cells. The colony will also spread to the other of those two cells.
2. Place a V colony in the northwest or southwest empty cell. The colony will also spread to the other of those two cells.

If Becca chooses strategy 1, Terry can place a V colony in the southwest empty cell. If Becca chooses strategy 2, Terry can place an H colony in the northeast empty cell. Either way, Becca has no empty cells to choose from on her next turn, so she loses and Terry wins.

In Sample Case #2, any of Becca's opening moves would cause a mutation.

In Sample Case #3, five of Becca's possible opening moves would cause a mutation, but the other seven are winning. She can place an H colony in any of the cells of the second row, or she can place a V colony in any of the cells of the second column. In either case, she leaves two disconnected sets of 1 or 2 cells each. In each of those sets, only one type of colony can be played, and playing it consumes all of the empty cells in that set. So, whichever of those sets Terry chooses to consume, Becca can consume the other, leaving Terry with no moves.

In Sample Case #4, both of Becca's two distinct possible opening moves are winning.

In Sample Case #5, Becca has no possible opening moves.

**Limits**

$1 \leq \mathbf{T} \leq 100$.

**Test set 1 (Visible)**

- $1 \leq \mathbf{R} \leq 4$.
- $1 \leq \mathbf{C} \leq 4$.

**Test set 2 (Hidden)**

- $1 \leq \mathbf{R} \leq 15$.
- $1 \leq \mathbf{C} \leq 15$.


---

---
title: "[GCJ 2010 #1A] Number Game"
layout: "post"
diff: 省选/NOI-
pid: P13392
tag: ['博弈论', '2010', 'Google Code Jam']
---
# [GCJ 2010 #1A] Number Game
## 题目描述

Arya and Bran are playing a game. Initially, two positive integers $A$ and $B$ are written on a blackboard. The players take turns, starting with Arya. On his or her turn, a player can replace $A$ with $A - k \times B$ for any positive integer $k$, or replace $B$ with $B - k \times A$ for any positive integer $k$. The first person to make one of the numbers drop to zero or below loses.

For example, if the numbers are initially $(12, 51)$, the game might progress as follows:

- Arya replaces $51$ with $51 - 3 \times 12 = 15$, leaving $(12, 15)$ on the blackboard.
- Bran replaces $15$ with $15 - 1 \times 12 = 3$, leaving $(12, 3)$ on the blackboard.
- Arya replaces $12$ with $12 - 3 \times 3 = 3$, leaving $(3, 3)$ on the blackboard.
- Bran replaces one $3$ with $3 - 1 \times 3 = 0$, and loses.

We will say $(A, B)$ is a winning position if Arya can always win a game that starts with $(A, B)$ on the blackboard, no matter what Bran does.

Given four integers $A_1$, $A_2$, $B_1$, $B_2$, count how many winning positions $(A, B)$ there are with $A_1 \leq A \leq A_2$ and $B_1 \leq B \leq B_2$.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow, one per line. Each line contains the four integers $A_1$, $A_2$, $B_1$, $B_2$, separated by spaces.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from 1), and $y$ is the number of winning positions $(A, B)$ with $A_1 \leq A \leq A_2$ and $B_1 \leq B \leq B_2$.
## 样例

### 样例输入 #1
```
3
5 5 8 8
11 11 2 2
1 6 1 6
```
### 样例输出 #1
```
Case #1: 0
Case #2: 1
Case #3: 20
```
## 提示

**Limits**

- $1 \leqslant T \leqslant 100.$
- $1 \leqslant A_1 \leqslant A_2 \leqslant 1,000,000.$
- $1 \leqslant B_1 \leqslant B_2 \leqslant 1,000,000.$

**Small dataset (16 Pts, Test set 1 - Visible)**

- Time limit: ~~30~~ 3 seconds.
- $A_2 - A_1 \leqslant 30.$
- $B_2 - B_1 \leqslant 30.$

**Large dataset (25 Pts, Test set 2 - Hidden)**

- Time limit: ~~90~~ 9 seconds.
- $A_2 - A_1 \leqslant 999,999.$
- $B_2 - B_1 \leqslant 999,999.$
- No additional constraints.



---

---
title: "[SDOI2011] 黑白棋"
layout: "post"
diff: 省选/NOI-
pid: P2490
tag: ['动态规划 DP', '递推', '博弈论', '2011', '各省省选', '山东', '排列组合']
---
# [SDOI2011] 黑白棋
## 题目描述

小 A 和小 B 又想到了一个新的游戏。

这个游戏是在一个 $1 \times n$ 的棋盘上进行的，棋盘上有 $k$ 个棋子，一半是黑色，一半是白色。

最左边是白色棋子，最右边是黑色棋子，相邻的棋子颜色不同。

![](https://cdn.luogu.com.cn/upload/image_hosting/dmv5zoyy.png)

小 A 可以移动白色棋子，小 B 可以移动黑色的棋子，其中白色不能往左，黑色不能往右。他们每次操作可以移动 $1$ 到 $d$ 个棋子。

每当移动某一个棋子时，这个棋子不能跨越两边的棋子，当然也不可以出界。当谁不可以操作时，谁就失败了。

小 A 和小 B 轮流操作，现在小 A 先移动，有多少种初始棋子的布局会使他胜利呢？

## 输入格式

输入三个数 $n,k,d$。

## 输出格式

输出小 A 胜利的方案总数。答案对 $10^9+7$ 取模。

## 样例

### 样例输入 #1
```
10 4 2
```
### 样例输出 #1
```
182
```
## 提示

- 对于 $30\%$ 的数据，有 $k=2$。
- 对于 $100\%$ 的数据，有 $1 \leq d \leq k \leq n \leq 10^4$，$k$ 为偶数，$k \leq 100$。



---

---
title: "[ZJOI2009] 染色游戏"
layout: "post"
diff: 省选/NOI-
pid: P2594
tag: ['递推', '博弈论', '2009', '各省省选', '浙江', '素数判断,质数,筛法', 'SG 函数']
---
# [ZJOI2009] 染色游戏
## 题目描述

一共n × m 个硬币，摆成n × m 的长方形。dongdong 和xixi 玩一个游戏， 每次可以选择一个连通块，并把其中的硬币全部翻转，但是需要满足存在一个 硬币属于这个连通块并且所有其他硬币都在它的左上方(可以正左方也可以正 上方)，并且这个硬币是从反面向上翻成正面向上。dongdong 和xixi 轮流操作。 如果某一方无法操作，那么他(她) 就输了。dongdong 先进行第一步操作，假 设双方都采用最优策略。问dongdong 是否有必胜策略。

## 输入格式

第一行一个数T，表示他们一共玩T 局游戏。接下来是T 组游戏描述。每 组游戏第一行两个数n;m，接下来n 行每行m 个字符，第i 行第j 个字符如 果是“H” 表示第i 行第j 列的硬币是正面向上，否则是反面向上。第i 行j 列 的左上方是指行不超过i 并且列不超过j 的区域。

## 输出格式

对于每局游戏，输出一行。如果dongdong 存在必胜策略则输出“-\_-”(不含 引号) 否则输出“=\_=”(不含引号)。(注意输出的都是半角符号，即三个符号 ASCII 码分别为45,61,95)

## 样例

### 样例输入 #1
```
3
2 3
HHH
HHH
2 3
HHH
TTH
2 1
T
H
```
### 样例输出 #1
```
=_=
-_-
-_-
```
## 提示

对于40% 的数据，满足1 ≤ n;m ≤ 5。

对于100% 的数据，满足1 ≤ n;m ≤ 100，1 ≤ T ≤ 50。



---

---
title: "[ZJOI2009] 取石子游戏"
layout: "post"
diff: 省选/NOI-
pid: P2599
tag: ['数学', '博弈论', '2009', '各省省选', '浙江']
---
# [ZJOI2009] 取石子游戏
## 题目描述

在研究过 Nim 游戏及各种变种之后，Orez 又发现了一种全新的取石子游戏，这个游戏是这样的：

有 $n$ 堆石子，将这 $n$ 堆石子摆成一排。游戏由两个人进行，两人轮流操作，每次操作者都可以从最左或最右的一堆中取出若干颗石子，可以将那一堆全部取掉，但不能不取，不能操作的人就输了。

Orez 问：对于任意给出一个初始一个局面，是否存在先手必胜策略。
## 输入格式

文件的第一行为一个整数 $T$，表示有 $T$ 组测试数据。对于每组测试数据：

第一行为一个整数 $n$，表示有 $n$ 堆石子。

第二行为 $n$ 个整数 $a_1, a_2, \ldots , a_n$，依次表示每堆石子的数目。
## 输出格式

对于每组测试数据仅输出一个整数 $0$ 或 $1$。其中 $1$ 表示有先手必胜策略，$0$ 表示没有。
## 样例

### 样例输入 #1
```
1
4
3 1 9 4

```
### 样例输出 #1
```
0

```
## 提示

对于 $30 \%$ 的数据，$n \le 5$，$a_i \le {10}^5$。  
对于 $100 \%$ 的数据，$1 \le T \le 10$，$1 \le n \le 1000$，$1 \le a_i \le {10}^9$。


---

---
title: "[HNOI2007] 分裂游戏"
layout: "post"
diff: 省选/NOI-
pid: P3185
tag: ['博弈论', '2007', '湖南', '枚举']
---
# [HNOI2007] 分裂游戏
## 题目描述

聪聪和睿睿最近迷上了一款叫做分裂的游戏。

该游戏的规则是： 共有 $n$ 个瓶子， 标号为 $0, 1, \ldots, n-1$，第 $i$ 个瓶子中装有 $p_i$ 颗巧克力豆，两个人轮流取豆子，每一轮每人选择 $3$ 个瓶子，标号为 $i,j,k$, 并要保证 $i \lt j, j \leq k$，且第 $i$ 个瓶子中至少要有 $1$ 颗巧克力豆，随后这个人从第 $i$ 个瓶子中拿走一颗豆子并在 $j,k$ 中各放入一粒豆子（$j$ 可能等于 $k$） 。如果轮到某人而他无法按规则取豆子，那么他将输掉比赛。胜利者可以拿走所有的巧克力豆！

两人最后决定由聪聪先取豆子，为了能够得到最终的巧克力豆，聪聪自然希望赢得比赛。他思考了一下，发现在有的情况下，先拿的人一定有办法取胜，但是他不知道对于其他情况是否有必胜策略，更不知道第一步该如何取。他决定偷偷请教聪明的你，希望你能告诉他，在给定每个瓶子中的最初豆子数后是否能让自己得到所有巧克力豆，他还希望你告诉他第一步该如何取，并且为了必胜，第一步有多少种取法？ 

## 输入格式

输入文件第一行是一个整数 $t$，表示测试数据的组数。

每组测试数据的第一行是瓶子的个数 $n$，接下来的一行有 $n$ 个由空格隔开的非负整数，表示每个瓶子中的豆子数。
## 输出格式

对于每组测试数据，输出包括两行，第一行为用一个空格两两隔开的三个整数，表示要想赢得游戏，第一步应该选取的 $3$ 个瓶子的编号 $i,j,k$，如果有多组符合要求的解，那么输出字典序最小的一组。如果无论如何都无法赢得游戏，那么输出用一个空格两两隔开的三个 $-1$。

第二行表示要想确保赢得比赛，第一步有多少种不同的取法。
## 样例

### 样例输入 #1
```
2
4
1 0 1 5000
3
0 0 1
```
### 样例输出 #1
```
0 2 3
1
-1 -1 -1
0
```
## 提示

$1 \leq t \leq 10$，$2 \leq n \leq 21$，$0 \leq p_i \leq 10^4$，


---

---
title: "[POI 2009] KAM-Pebbles"
layout: "post"
diff: 省选/NOI-
pid: P3480
tag: ['博弈论', '2009', 'POI（波兰）']
---
# [POI 2009] KAM-Pebbles
## 题目描述

Johny and Margaret are playing "pebbles". Initially there is a certain number of pebbles on a table, grouped in $n$ piles. The piles are next to each other, forming a single row. The arrangement of stones satisfies an additional property that each pile consists of at least as many pebbles as the one to the left (with the obvious exception of the leftmost pile). The players alternately remove any number of pebbles from a single pile of their choice. They have to take care, though, not to make any pile smaller than the one left to it. In other words, the piles have to satisfy the initial property after the move as well. When one of the players cannot make a move (i.e. before his move there are no more pebbles on the table), he loses. Johny always starts, to compensate for Margaret's mastery in this game.

In fact Margaret is so good that she always makes the best move, and wins the game whenever she has a chance. Therefore Johny asks your help - he would like to know if he stands a chance of beating Margaret with a particular initial arrangement. Write a programme that determines answers to Johny's inquiries.

## 输入格式

In the first line of the standard input there is a single integer $u$ ($1\le u\le 10$) denoting the number of initial pebble arrangements to analyse.

The following $2u$ lines contain descriptions of these arrangements; each one takes exactly two lines.

The first line of each description contains a single integer $n$, $1\le n\le 1000$  - the number of piles.

The second line of description holds  non-negative integers  separated by single spaces and denoting the numbers of pebbles in successive piles, left to right.

These numbers satisfy the following inequality $a_1\le a_2\le \cdots \le a_n$.


The total number of pebbles in any arrangement does not exceed $1000$.

## 输出格式

Precisely $n$ lines should be printed out on the standard output.

The $i$-th of these lines (for $1\le i\le u$) should hold the word TAK (yes in Polish), if Johny can win starting with the $i$-th initial arrangement given in the input, or the word NIE (no in Polish), if Johny is bound to lose that game, assuming optimal play of Margaret.

## 样例

### 样例输入 #1
```
2
2
2 2
3
1 2 4

```
### 样例输出 #1
```
NIE
TAK

```
## 题目翻译

有 $N$ 堆石子，除了第一堆外，每堆石子个数都不少于前一堆的石子个数。两人轮流操作每次操作可以从一堆石子中移走任意多石子，但是要保证操作后仍然满足初始时的条件谁没有石子可移时输掉游戏。问先手是否必胜。

### 输入格式

多组输入，第一行一个整数 $u$ 代表数据组数（$1\le u\le 10$）

接下来共 $2u$ 行，每两行代表一组数据：

第一行只有一个整数 $n$（$1\le n\le 1000$），表示石子堆数；

第二行有 $n$ 个整数用空格隔开，第 $i$ 个整数 $a_i$ 表示第 $i$ 堆的石子个数，保证 $a_1\le a_2\le a_3\le \cdots\le a_n$。

对于每组数据，保证石子总数不超过 $10000$。

### 输出格式

输出 $u$ 行，如果第 $i$ 组数据先手必胜，输出 `TAK`，否则输出 `NIE`。



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
title: "[yLOI2020] 牵丝戏"
layout: "post"
diff: 省选/NOI-
pid: P7097
tag: ['动态规划 DP', '博弈论', '2020', 'O2优化', '背包 DP']
---
# [yLOI2020] 牵丝戏
## 题目背景

> 风雪依稀秋白发尾， 灯火葳蕤，揉皱你眼眉。  
> 假如你舍一滴泪，假如老去我能陪。  
> 烟波里成灰，也去得完美。 

——银临 & Aki阿杰《牵丝戏》
## 题目描述

扶苏和扶咕咕最近在玩一款叫做「ddt」的游戏，因为玩「ddt」时一直在循环《牵丝戏》，所以想到牵丝戏就想到了这个游戏。

为了简化问题，我们认为这是一款一对一回合制游戏。双方玩家各有一个属性，被称为 delay 值，简称 $d$ 值。$d$ 值会根据回合中玩家使用的道具类型和数量来进行相应的增加。我们定义玩家 $x$ 的回合为玩家 $x$ 从发动攻击到结束的整个过程。**在玩家 $x$ 的回合中，只有玩家 $x$ 可以使用道具和发动攻击，并且玩家 $x$ 一定会发动攻击**。当一个玩家的回合结束以后，下一回合将是两个玩家中 $d$ 值**较小**的玩家的回合。当两个玩家的 $d$ 值相同时，因为扶苏氪金很多，下一回合一定是**扶苏的回合**。

这款游戏共有 $m$ 种道具，第 $i$ 种道具会将本回合的伤害增加**不计算其他道具的原始伤害**的 $\frac{k_i}{10^5}$ 倍，同时会增加 $p_i$ 点 $d$ 值。每回合**每种道具只能使用一次，本回合的道具不会对下回合产生伤害增益效果**。同时，每回合结束以后，发动攻击的玩家一定会增加 $w$ 点 $d$ 值。

而使用道具是受到双方 $d$ 值差限制的。具体的，任何回合所使用的道具应该满足本回合结束以后双方 $d$ 值（包括发动攻击的玩家一定增加的 $w$ 点 $d$ 值）之差的绝对值**不超过** $100$。一个显然的事实是，只要保证了 $w \le 100$，玩家就一定存在一种选择道具的方法（包括不选择），来满足这个限制。

例如，在扶咕咕的回合中，若她的原始伤害 $t=10^5$，初始时 $d$ 值 $d_0=3$，规定 $w=2$，她使用了两个道具，$k_1=114$，$k_2=514$，$p_1=19$，$p_2=81$，那么本回合她造成的伤害为 

$$t + t \times k_1 + t \times k_2 = 10^5 + 114 + 514 =  100628$$

她回合结束后的 $d$ 值为

$$d_0 + w + p_1 + p_2 = 3 + 2 + 19 + 81 = 105$$

而假如下回合还是她的回合，并且她没有使用道具，那么她下回合造成的伤害为 

$$t =  100000$$

她下回合结束后的 $d$ 值为 

$$105 + w = 105 + 2 = 107$$

现在扶苏和扶咕咕正在对战。给定游戏的道具列表，和他们的原始伤害、 $d$ 值。游戏一共会进行 $n$ 回合，不妨认为无论造成多大的伤害，双方都不会死亡。请你最大化「扶苏对扶咕咕造成的伤害 - 扶咕咕对扶苏造成的伤害」这个差的值。

当然，扶咕咕也会尽可能最大化「她对扶苏造成伤害 - 扶苏对她造成伤害」的值。不妨认为扶苏是 yLOI 世界中最聪明的男孩子，扶咕咕是 yLOI 世界中最聪明的女孩子，也就是**他们都会选择最优的策略来使用道具而不会出错**，题目所求即为在这种情况下伤害差的最大值。
## 输入格式

第一行有一个整数，表示该测试点所在的子任务编号 $T$。   
第二行有三个整数，分别表示游戏的回合数 $n$，游戏的装备数 $m$ 以及每回合固定增加的 $d$ 值 $w$。   
第三行有 $m$ 个整数，第 $i$ 个整数表示 $k_i$。   
第四行有 $m$ 个整数，第 $i$ 个整数表示 $p_i$。   
第五行有四个整数，依次表示扶苏的初始伤害 $x_a$，扶咕咕的初始伤害 $x_b$，扶苏的初始 $d$ 值 $d_a$，扶咕咕的初始 $d$ 值 $d_b$。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
0
3 2 1
50 1
20 100
100000 200000 2 3
```
### 样例输出 #1
```
-52
```
## 提示

### 样例 1 解释

- 第一回合开始前，扶苏 $d$ 值为 $2$，扶咕咕 $d$ 值为 $3$，第一回合由扶苏出手。扶苏不使用道具，伤害为 $100000$，$d$ 值增加 $1$，总伤害差为 $100000$。
- 第一回合结束后，双方 $d$ 值均为 $3$，第二回合由扶苏出手。扶苏使用第一个道具，伤害为 $100050$，$d$ 值增加 $21$，总伤害差为 $200050$。
- 第二回合结束后，扶苏 $d$ 值为 $24$，扶咕咕 $d$ 值为 $3$，第三回合由扶咕咕出手。扶咕咕使用 $1$ 、 $2$ 两个道具，伤害为 $200102$，$d$ 值增加 $121$，总伤害差为 $-52$。这回合结束后，双方 $d$ 值差恰好为 $100$，符合要求。

### 数据规模与约定


**本题采用多测试点捆绑测试**。

- 子任务 $1$（$5$ 分）：保证 $n=0$。
- 子任务 $2$（$10$ 分）：保证 $m=0$。
- 子任务 $3$（$15$ 分）：保证 $n,m \le 5$。
- 子任务 $4$（$20$ 分）：保证 $n \le 3$。
- 子任务 $5$（$20$ 分）：保证 $m \le 10$。
- 子任务 $6$（$30$ 分）：无特殊约定。

对于全部的测试点，保证 $0 \le n \le 10^3$，$0 \le m \le 10^5$，$1 \le p_i,w \le 100$，$1 \le x_a,x_b,k_a,d_a,d_b \le 10^9$，$x_a$ 与 $x_b$ 是 $10^5$ 的倍数，$1 \le |d_a-d_b| \le 100$。

### 提示

共有 4 个样例文件，请见附加文件中的 opera.zip。  
对于样例 2，满足 $m = 0$。  
对于样例 3，满足 $n \leq 3$。


---

---
title: "「EZEC-6」象棋"
layout: "post"
diff: 省选/NOI-
pid: P7387
tag: ['博弈论']
---
# 「EZEC-6」象棋
## 题目背景

> 万籁停吹奏
$\newline$支颐听秋水问蜉蝣
$\newline$既玄冥不可量北斗
$\newline$却何信相思最温柔

## 题目描述

象棋将会由两个玩家进行游玩，其中红方为先手，黑方为后手。象棋里有很多种棋子，PF 对其中的“炮”情有独钟，炮的操作为：如果任意一方的某个炮和对方的某个炮之间的位置上**有且仅有一个炮**，那么这一方可以将对方的炮移出棋盘，并将他的炮移到对方的炮的位置。

PF 厌倦了传统象棋的玩法，因此他拿出了一张 $1$ 行 $n$ 列的棋盘。棋盘上的每个位置都有且仅有一个炮，每个炮都隶属于红方或黑方。对于每个回合，操作方可以进行一次操作，也可以不进行操作，然后将操作权交给对手。若双方均同意结束或者无棋可动，游戏结束。


游戏将进行 $T$ 局。每一局 PF 都是红方。定义游戏的胜利条件为一方的剩余的炮的数量大于对方。他想知道，若双方均使用最佳策略，他是否有必胜策略。
## 输入格式

第一行一个整数 $T$，表示测试数据的数量。

对于每组数据，第一行一个整数 $n$，表示棋盘大小。

接下来一行一个字符串，其中第 $i$ 个整数 $a_i$ 表示第 $i$ 个棋子的种类，其中 $1$ 表示红方的炮， $0$ 表示黑方的炮。
## 输出格式

输出共 $T$ 行，若第 $i$ 组有必胜策略，输出 `WIN`，若为平局输出 `TIE`，否则输出 `LOSE`。
## 样例

### 样例输入 #1
```
4
3
101
5
01100
5
01110
4
1000
```
### 样例输出 #1
```
WIN
TIE
WIN
LOSE
```
## 提示

**由于本题输入量较大，请使用较快的读入方法。**

**【数据范围】**

**本题采用捆绑测试。**

|子任务编号|$T\le$|$n\le$|$\sum n\le$|分值|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$20$|$3$|$60$|$5$|
|$2$|$10^3$|$6$|$6\times10^3$|$10$|
|$3$|$10^5$|$15$|$1.5\times10^6$|$15$|
|$4$|$200$|$200$|$500$|$20$|
|$5$|$10^5$|$10^6$|$2\times10^6$|$25$|
|$6$|$10^5$|$10^7$|$2\times10^7$|$25$|

对于 $100\%$ 的数据， $1\le T \le 10^5$，$1 \le n \le 10^7$，$\sum n \le 2\times 10^7$，$a \in \{0,1\}$。

**【样例解释】**

对于第一组数据，没有任何棋子能够移动，而棋面红棋子数大于黑棋，故先手有必胜策略。

对于第二组数据，一种平局的变化如下：

```cpp
0 1 1* 0 0*
0 1 0 1
```	

对于第三组数据，双方的最佳策略有如下两种可能：
```cpp
0 1 1* 1 0*
0* 1 1* 1
1 0 1
```

```cpp
0* 1 1* 1 0
1 1* 1 0*
1 0 1
```
两种结果均为红炮剩余数量多，故红棋必胜。

对于第四组数据，红棋只有一种操作可行：

```cpp
1* 0 0* 0
0 1 0
```
无棋可走后黑炮数量更多。




---

---
title: "「Stoi2031」蒲公英的约定（vol.1）"
layout: "post"
diff: 省选/NOI-
pid: P7490
tag: ['数学', '博弈论', '期望', 'SG 函数']
---
# 「Stoi2031」蒲公英的约定（vol.1）
## 题目背景

> 一起长大的约定 那样清晰 拉过勾的我相信 说好要一起旅行 是你如今 唯一坚持的任性 ——《蒲公英的约定》
## 题目描述

清和如在玩游戏。她们有 $n$ 丛 **蒲公英**，每丛分别有 $s_i$ 朵。这些 **蒲公英** 有一个神奇的性质：有一个给定的常数 $\sigma \in (0,1)$，$x$ 朵 **蒲公英** 会分出 $\lfloor \sigma x \rfloor$ 朵为一组，剩下 $x-\lfloor \sigma x \rfloor$ 朵继续分组，直到分出的组没有 **蒲公英** 即 $\lfloor \sigma x \rfloor=0$ 为止。她们称这种现象为 **任性**。现在她们的每丛 **蒲公英** 都有 **任性** 的现象。她们的游戏规则如下：从清开始，两人轮流进行 **旅行**。一次 **旅行** 为选择一丛 **蒲公英** 并吹散这一丛的第一组中的若干朵 **蒲公英**，至少要吹一朵，至多吹的朵数为第一组的朵数，即不能吹散除第一组外的 **蒲公英**。当第一组为空时，其下一组成为第一组。若这一丛只剩下一组 **蒲公英**，这一丛不能再被选定。每丛 **蒲公英** 都不能被选定时，游戏结束，当前轮到的人落败。她们想知道如果清第一次 **旅行** 时等概率选择其中一丛可吹散的 **蒲公英** 再等概率选择吹散的朵数后两人都按最优策略操作，那么清的胜率 $x \bmod 20190816170251$ 的值将会是多少。

与 vol.2 的区别是，**蒲公英** 在被吹散一部分后 **不会** 重新分组。
## 输入格式

第一行两个正整数 $id,n$，其中 $id$ 表示 Subtask 编号。

第二行 $n$ 个正整数，第 $i$ 个表示 $s_i$。

若 $id>3$，第三行输入两个正整数 $p,q$ 表示 $\sigma=\dfrac{p}{q}$。
## 输出格式

一行一个整数，表示清的胜率 $x \bmod{20190816170251}$。
## 样例

### 样例输入 #1
```
4 3
1 1 1
1 6

```
### 样例输出 #1
```
0

```
### 样例输入 #2
```
6 3
1 7 3
1 3

```
### 样例输出 #2
```
5047704042563

```
## 提示

#### 简述版题意：

有 $n$ 丛 **蒲公英**，第 $i$ 丛有 $s_i$ 朵。给定实数 $\sigma$，每丛会分为若干组，第 $j$ 组有 $t_j$ 朵，且满足 $t_j=\left\lfloor \sigma\left(s_i - \sum\limits_{k=1}^{j-1}t_k\right) \right\rfloor$，当 $t_j=0$ 时不再分组。两人轮流操作，每次操作可以选择一丛 **蒲公英**，并选择一个整数 $c \in t_j$，从这丛 **蒲公英** 中吹散 $c$ 朵，将 $t_j$ 变为 $t_j-c$，其中 $j$ 为操作之前这丛 **蒲公英** 中满足 $t_j \neq 0$ 的最小正整数。必须至少吹一朵，不能操作者败。求先手第一步等概率选择任意一丛可操作的 **蒲公英** 再等概率选择吹散的朵数后两人都采取最优策略时先手的胜率 $x \bmod{20190816170251}$ 的值。

#### 样例解释：

对于样例 $1$，清无法操作，胜率为 $0$。

对于样例 $2$，初始局面为 $\{0;1\},\{2,1,1,1,0;2\},\{1,0;2\}$，清可以选择第 $2$ 丛并在两种操作中选择吹散 $2$ 朵变成 $\{0;1\},\{1,1,1,0;2\},\{1,0;2\}$，选择第 $3$ 丛没有可取胜的策略，且第 $1$ 丛不能选择，总胜率为 $\dfrac{\frac{1}{2}+0}{2}=\dfrac{1}{4}$。

#### 数据范围：

**本题采用捆绑测试，各个 Subtask 的分数与限制如下。**

| Subtask No. | $n \le$ | $s_i \le$ | $\sigma$ 限制 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{2}+1}{3}$ | $10$ |
| $2$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{3}+1}{5}$ | $10$ |
| $3$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{5}-1}{2}$ | $10$ |
| $4$ | $100$ | $1$ | 无 | $3$ |
| $5$ | $100$ | $100$ | $\sigma=\dfrac{1}{2}$ | $7$ |
| $6$ | $100$ | $10^6$ | 无 | $13$ |
| $7$ | $3 \times 10^5$ | $10^{10}$ | $\sigma \ge \dfrac{1}{2}$ | $47$ |

对于 $100\%$ 的数据，$1 \le n \le 3 \times 10^5,1 \le s_i \le 10^{10},1 \le p<q \le 10^9$。

**本题读入量较大，可以选择使用比赛描述中的快速读入模板以加快读入速度。**


---

---
title: "「Stoi2031」蒲公英的约定（vol.2）"
layout: "post"
diff: 省选/NOI-
pid: P7491
tag: ['数学', '博弈论', '期望', 'SG 函数']
---
# 「Stoi2031」蒲公英的约定（vol.2）
## 题目背景

> 一起长大的约定 那样清晰 拉过勾的我相信 说好要一起旅行 是你如今 唯一坚持的任性 ——《蒲公英的约定》
## 题目描述

清和如在玩游戏。她们有 $n$ 丛 **蒲公英**，每丛分别有 $s_i$ 朵。这些 **蒲公英** 有一个神奇的性质：有一个给定的常数 $\sigma \in (0,1)$，$x$ 朵 **蒲公英** 会分出 $\lfloor \sigma x \rfloor$ 朵为一组，剩下 $x-\lfloor \sigma x \rfloor$ 朵继续分组，直到分出的组没有 **蒲公英** 即 $\lfloor \sigma x \rfloor=0$ 为止。她们称这种现象为 **任性**。现在她们的每丛 **蒲公英** 都有 **任性** 的现象。她们的游戏规则如下：从清开始，两人轮流进行 **旅行**。一次 **旅行** 为选择一丛 **蒲公英** 并吹散这一丛的第一组中的若干朵 **蒲公英**，至少要吹一朵，至多吹的朵数为第一组的朵数，即不能吹散除第一组外的 **蒲公英**。当第一组为空时，其下一组成为第一组。若这一丛只剩下一组 **蒲公英**，这一丛不能再被选定。每丛 **蒲公英** 都不能被选定时，游戏结束，当前轮到的人落败。她们想知道如果清第一次 **旅行** 时等概率选择其中一丛可吹散的 **蒲公英** 再等概率选择吹散的朵数后两人都按最优策略操作，那么清的胜率 $x \bmod{20190816170251}$ 的值将会是多少。

与 vol.1 的区别是，**蒲公英** 在被吹散一部分后 **会** 重新分组。
## 输入格式

第一行两个正整数 $id,n$，其中 $id$ 表示 Subtask 编号。

第二行 $n$ 个正整数，第 $i$ 个表示 $s_i$。

若 $id>3$，第三行输入两个正整数 $p,q$ 表示 $\sigma=\dfrac{p}{q}$。
## 输出格式

一行一个整数，表示清的胜率 $x \bmod{20190816170251}$。
## 样例

### 样例输入 #1
```
4 3
1 1 1
1 6

```
### 样例输出 #1
```
0

```
### 样例输入 #2
```
6 3
1 7 3
1 3

```
### 样例输出 #2
```
15143112127689

```
## 提示

#### 简述版题意：

有 $n$ 丛 **蒲公英**，第 $i$ 丛有 $s_i$ 朵。给定实数 $\sigma$，两人轮流操作，每次操作可以选择一丛 **蒲公英**，并选择一个整数 $c \in (0,\sigma s]$，从这丛 **蒲公英** 中吹散 $c$ 朵，其中 $s$ 为操作之前这丛 **蒲公英** 的朵数。必须至少吹一朵，不能操作者败。求先手第一步等概率选择任意一丛可操作的 **蒲公英** 再等概率选择吹散的朵数后两人都采取最优策略时先手的胜率 $x \bmod{20190816170251}$ 的值。

#### 样例解释：

对于样例 $1$，清无法操作，胜率为 $0$。

对于样例 $2$，清可以选择第 $2$ 丛并在两种操作中选择吹散 $2$ 朵变成 $1,5,3$，或选择第 $3$ 丛并选择唯一的操作变成 $1,7,2$，且第 $1$ 丛不能选择，总胜率为 $\dfrac{\frac{1}{2}+1}{2}=\dfrac{3}{4}$。

#### 数据范围：

**本题采用捆绑测试，各个 Subtask 的分数与限制如下。**

| Subtask No. | $n \le$ | $s_i \le$ | $\sigma$ 限制 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{2}+1}{3}$ | $10$ |
| $2$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{3}+1}{5}$ | $10$ |
| $3$ | $3 \times 10^5$ | $10^{10}$ | $\sigma=\dfrac{\sqrt{5}-1}{2}$ | $10$ |
| $4$ | $100$ | $1$ | 无 | $3$ |
| $5$ | $100$ | $100$ | $\sigma=\dfrac{1}{2}$ | $7$ |
| $6$ | $100$ | $10^6$ | 无 | $13$ |
| $7$ | $3 \times 10^5$ | $10^{10}$ | $\sigma \ge \dfrac{1}{2}$ | $47$ |

对于 $100\%$ 的数据，$1 \le n \le 3 \times 10^5,1 \le s_i \le 10^{10},1 \le p<q \le 10^9$。

**本题读入量较大，可以选择使用比赛描述中的快速读入模板以加快读入速度。**


---

---
title: "「C.E.L.U-03」100%不公平的游戏"
layout: "post"
diff: 省选/NOI-
pid: P7841
tag: ['博弈论', 'O2优化', '树形 DP']
---
# 「C.E.L.U-03」100%不公平的游戏
## 题目背景

今天 ice 出去玩了。原准备与 Alice 玩游戏的 Bob 只能和 Al 玩一场博弈游戏。
## 题目描述

这个游戏是在树上进行的。Bob 先手。Bob 和 Al 轮流进行以下操作，首先无法操作者判负。

- 在树上标记一条未被标记过的边。满足在每一次操作之后，存在一条简单路径遍历所有标记过的边。注意：这条简单路径**可以经过未标记过的边**。

如果给定的树对于 Bob 有必胜方案，输出 `Play now`，否则输出 `Restart`。
## 输入格式

本题多测，第一行输入一个整数表示数据组数 $T$。

对于每组测试数据，第一行输入一个整数 $n$ 表示树的节点数。

接下来 $n-1$ 行，每行输入两个整数 $u,v$ 表示 $(u,v)$ 是树上的一条边。
## 输出格式

对于每组测试数据，输出一个字符串，大小写敏感。
## 样例

### 样例输入 #1
```
2
9
9 5
2 1
9 8
3 2
5 6
7 9
4 3
5 2
3
1 2
2 3
```
### 样例输出 #1
```
Play now
Restart
```
### 样例输入 #2
```
附加两组样例详见
https://www.luogu.com.cn/paste/b6mh7ido
```
### 样例输出 #2
```
附加两组样例详见
https://www.luogu.com.cn/paste/b6mh7ido
```
## 提示

**样例数据也可见附件** $\textbf{\textit{game.in}/\textit{game.out}}$。

### 样例解释 1

**第一组数据：**

先手选择边 $(2,5)$ 必胜：  
若后手选择 $(1,2)$，先手选择 $(5,6)$ 可以获胜。  
若后手选择 $(2,3)$，先手选择 $(5,9)$ 可以获胜。  
若后手选择 $(3,4)$，先手选择 $(5,9)$ 可以获胜。  
若后手选择 $(5,6)$，先手选择 $(1,2)$ 可以获胜。  
若后手选择 $(5,9)$，先手选择 $(3,4)$ 可以获胜。  
若后手选择 $(7,9)$，先手选择 $(2,3)$ 可以获胜。  
若后手选择 $(8,9)$，先手选择 $(3,4)$ 可以获胜。  
综上，无论后手选那一条边，都不会获得胜利。  

**第二组数据：**

先手不存在必胜策略：  
若先手选择 $(1,2)$，后手选择 $(2,3)$ 获胜。  
若先手选择 $(2,3)$，后手选择 $(1,2)$ 获胜。


### 样例解释 2

各组数据详见下图，其中前两组数据与样例一相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/imht95gt.png)

---

### 数据范围

$2\leq n\leq5\times10^5$

$1\leq T\leq10^4$

$\sum n\leq1.5\times10^6$

数据保证给定的图是一棵树。

### 子任务  
1. （8分）$n\leq6$。
2. （18分）$n\leq12,T\leq10$。
3. （6分） $n\leq28,T\leq10$。
4. （8分）$n\leq200,T\leq10$。
5. （30分）$n\leq2000,T\leq10$。
6. （6分）最多存在两个节点度数大于 $2$。
7. （12分）树的形态是一棵完全二叉树。
8. （12分）无特殊性质。


---

---
title: "「Wdoi-6」另一侧的月"
layout: "post"
diff: 省选/NOI-
pid: P8347
tag: ['博弈论', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「Wdoi-6」另一侧的月
## 题目背景

[![](https://cdn.luogu.com.cn/upload/image_hosting/ikxrpn7c.png)](https://thwiki.cc/%E5%A4%A7%E7%A9%BA%E9%AD%94%E6%9C%AF_%EF%BD%9E_Magical_Astronomy.)

「人类的梦想之一，月面旅行对一般人也终于成为可能！」   
「从下个月起日本各个旅行公司将开始展开旅行」   

然而，月球的表面，有着将月之都与荒凉的无生命星球隔开的一道结界。只要这道结界存在，人们只能看到石头罢了。

而月面旅行的费用，也绝不是身为大学生的莲子与梅莉二人所能承担的。但是，她们想要探寻的是，被结界所包裹的，有着高度发达文明的月之都。

这，便是另一侧的月。梅莉她看见了。兔子在捣药，身着华美的服装，优雅地在天空中起舞的天女。

「我说莲子啊。如果月面旅行太贵实在不行的话，我们要不要试着想点别的办法去月球呢？」
## 题目描述

### 简要题意

给定 $n$ 个节点的树（保证 $n\ge 2$），Hifuu 和 Luna 交替操作，前者先手。每回合操作者选择一个节点，将「该节点」和「所有与该节点相连的边」删除，形成若干个连通块，操作者再从中保留一个连通块。如果该回合结束后只剩下一个节点，则该回合的操作者失败，另一个人胜利。问谁存在必胜策略。

-----
### 原始题意

但是，月之都是有结界保护的，也就是说莲子与梅莉若是想要用一些方式完成月球旅行，势必要突破这层结界。

月之都的结界是由 $n$ 个节点，$n-1$ 条灵能输送渠道构成的连通的结构，其中节点编号为 $1 \sim n$。结界有一个中枢控制系统，以提防外界的人闯入结界，抵达月之都。莲子和梅莉便需要与这个控制系统进行一些交互，才能进入月之都。

具体而言，莲子梅莉，和中枢控制系统是交替进行操作的，其中莲子梅莉是**先手**。操作方可以任意选择结界上的一个节点，将连向这个节点的**所有**灵能输送渠道全部断绝，同时废弃这个节点。这也就意味着，这会把结界分为若干**组**节点，每一组节点之间没有灵能输送渠道，而组内的节点由灵能输送渠道相连。在这些节点组中，操作者可以任意保留**一组**节点，将另外所有节点**全部废弃**，即，之后再也无法操作这些被废弃的节点了。

在这样的规则之下，若操作结束后，最后只剩下一个节点，那么操作者失败，另一个人取得胜利。现在莲子和梅莉希望知道，在这样的规则之下，她们是否存在一种必定能够抵达月之都的策略？
## 输入格式

本题多组数据。第一行输入一个正整数 $T$，表示数据组数。对于每一组数据：

- 第一行有一个正整数 $n$。
- 接下来 $n-1$ 行，每行两个正整数 $u_i,v_i$。表示一条连接节点 $u_i$ 和 $v_i$ 的双向的灵能输送渠道。
## 输出格式

对于每一组数据，输出莲子和梅莉是否能够到达月之都。具体而言，若她们存在必定能到达月之都的策略，则输出 $\texttt{Hifuu}$，否则输出 $\texttt{Luna}$。
## 样例

### 样例输入 #1
```
1
5
2 4
1 2
3 1
5 2
```
### 样例输出 #1
```
Hifuu
```
### 样例输入 #2
```
1
11
1 2
1 3
1 4
2 5
2 6
4 7
5 8
5 9
9 10
9 11
```
### 样例输出 #2
```
Hifuu
```
### 样例输入 #3
```
1
2
1 2
```
### 样例输出 #3
```
Luna
```
## 提示

### 样例解释

#### 样例 \#1

![](https://cdn.luogu.com.cn/upload/image_hosting/9zcd72k1.png)

图 $1$ 是结界。图 $2$、图 $3$ 展示了一种莲子和梅莉可能的一种必胜策略：选择节点 $2$，然后保留 $\{1,3\}$ 所处的连通块，那么中枢控制系统无论是选择节点 $1$ 还是 $3$ 都必输。

#### 样例 \#2

![](https://cdn.luogu.com.cn/upload/image_hosting/djzwnoxz.png)

---

### 数据范围

**本题采用捆绑测试。**

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|}\hline
\textbf{Subtask} & \textbf{\textsf{分值}} & \bm{n\le } & \textbf{\textsf{特殊性质}} & \textbf{Subtask \textsf{依赖}}\cr\hline
1 & 15 & 8 & - & - \cr\hline
2 & 20 & 10^5 & \mathbf{A} & -\cr\hline
3 & 20 & 10^5 & \mathbf{B} & - \cr\hline
4 & 15 & 10^3 & - & 1 \cr\hline
5 & 30 & 10^5 & - & 2,3,4 \cr\hline
\end{array}
$$

- 特殊性质 $\mathbf{A}$：保证存在一个点度数为 $n-1$。
- 特殊性质 $\mathbf{B}$：保证 $n=2^k-1,k \in \N^*$。且树的形态是完全二叉树。

对于 $100\%$ 的数据：$1 \leq T \leq 5$，$2 \le n \le 10^5$，输入数据构成一棵树。


---

---
title: "觅光 | Searching for Hope (hard ver.)"
layout: "post"
diff: 省选/NOI-
pid: P8968
tag: ['暴力数据结构', '博弈论', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 觅光 | Searching for Hope (hard ver.)
## 题目背景

**这是本题的困难版本。两个版本在 $\bm{100 \%}$ 数据范围的唯一区别是关于 $\bm{n}$ 的限制。此版本中 $\bm{n \le {10}^6}$。**

---

有梦中所向往的地方，也有现实中可望不可触及的远方。

我们正等待无数次的希望，新的纪元，生命不曾奏响终章。

顷刻间颠覆中的一切，天空坠落到海底，死死卡住呼吸者的全部。羽翼裹满刺骨的海水，悲伤到从此遗忘呼吸的意义。

明明与空气只隔着毫厘，却不想再尝试去呼吸。我开始明白，悲伤到了极点，也许不会流泪

神明借着生的名义，捏造出灰暗的真理。



泪水模糊眼眶，身躯坠进天空，泛白的天光，不得已照亮这一日的希望。
## 题目描述

现在有一棵 $n$ 个节点的有根二叉树。

凡人与神明在这棵树上进行一个游戏。凡人需要从根投下若干个球，每个球带 $1$ 单位正电荷或带 $1$ 单位负电荷。

树上每一个点有容量，第 $i$ 个点可以容纳 $c_i$ 个球。初始每一个点容纳的球数为 $0$。我们称一个点被充满当且仅当它容纳的球的个数等于它的容量。

每一次一个球下落到一个点时：

- 如果该点没有孩子节点或者所有孩子节点上都已经充满球，则停止，该点容纳的球的个数 $+1$；
- 如果该点恰有一个孩子节点未充满，则向那个孩子下落；
- 如果有 $2$ 个孩子节点均未充满：
	- 如果左侧子树中所有球的电荷代数和大于右侧子树所有球的电荷代数和，则如果当前球带正电则向右下落，否则向左下落；
   - 如果左侧子树中所有球的电荷代数和小于右侧子树所有球的电荷代数和，则如果当前球带正电则向左下落，否则向右下落；
   - 如果左侧子树中所有球的电荷代数和等于右侧子树所有球的电荷代数和，则由神明决定向哪个方向下落。

其中，电荷代数和指的是正电荷的数量减去负电荷的数量。

在游戏开始前，双方约定目标点 $u$。在一个回合中，凡人选择这次投下的球的电性，神明按上述规则控制球的下落过程。当 $u$ 被充满时，游戏结束。

凡人希望游戏回合数尽量少，神明希望游戏回合数尽量多。假设双方足够聪明。

对所有：$1\leq u\leq n$，求游戏轮数 $r_u$。
## 输入格式

第一行，一个正整数 $n$。

第二行，$n-1$ 个整数 $f_2, f_3, \ldots, f_n$，其中 $f_i$ 代表 $i$ 的父亲的编号。

第三行，$n$ 个整数 $c_1, c_2, \ldots, c_n$。
## 输出格式

输出一行，$n$ 个整数 $r_1, r_2, \ldots, r_n$。
## 样例

### 样例输入 #1
```
5
1 1 2 2
1 1 1 1 1

```
### 样例输出 #1
```
5 4 2 3 3
```
## 提示

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n \le$ | 分值 |
| :----------: | :----------: | :----------: |
| 4 | ${10}^5$ | 33 |
| 5 | ${10}^6$ | 67 |

对于 $100\%$ 的数据，$2 \le n \le {10}^6$，满足树是以 $1$ 为根的二叉树，$1 \le f_i < i$，$1 \le c_i \le {10}^{12}$。

---

**【提示】**

本题最大 I/O 量达到 20 MiB，请注意 I/O 效率。


---

---
title: "[THUPC 2023 初赛] 公平合作"
layout: "post"
diff: 省选/NOI-
pid: P9138
tag: ['动态规划 DP', '博弈论', '倍增', '2023', 'Special Judge', 'O2优化', 'THUPC']
---
# [THUPC 2023 初赛] 公平合作
## 题目描述

在大地的尽头，一座灰白的灯塔矗立在漫长的海岸线上。这一片海域海流复杂、礁石嶙峋，却又是不少航线的必经之路。若没有如此高耸而明亮的灯塔为过路的船只照亮航路，或许会有更多不幸的生命葬身海底。为了看管好这一座海上明灯，一批训练有素的守望人轮流值守于此。日复一日的工作枯燥乏味却又不能有丝毫闪失，紧绷的神经直到下一班守望人到来才得以放松。

在电力普及之前，灯塔通常使用煤油灯为过往的水手指引前行的方向。每次为这座灯塔添加燃油时，需要两位守望人各自搬运一个容积为 $L$ 的油桶；而每次轮到 Y 和 S 所在的班组照料这座灯塔时，总是由 Y 和 S 负责为灯塔加油。将煤油搬运至灯室时，如果不装满油桶，对灯塔的正常运转也没有太大影响，无非是需要多来回搬运几趟。但是，如果两位守望人都想着偷懒，问题恐怕就不只是多几趟那么简单。Y 和 S 想到了一个好办法：互相为对方的油桶装油。

灯塔里有 $N$ 个用于将储存的煤油转移到油桶中的容器，其中第 $i$ 个容器的容积为 $a_i$。Y 和 S 先想办法决定由谁先装油。两人先后装油；轮到其中一位守望人装油时，这位守望人每次从所有容器中等概率地随机选出一个容器，将其装满油，并全部倒入对方的油桶中。两位守望人都可以在操作任意多次（可以是 0 次）后结束装油，但后手必须等先手结束后才能开始装油。Y 和 S 先后装完煤油后，两人会比一下谁把对方的油桶装得更满，再各自把自己的油桶搬运到灯室。但是，如果有谁某次选出一个容器后，把对方的油桶装满了，但容器里还有没倒出的煤油，那么这位倒霉的守望人就必须把两个油桶都独自搬到灯室——这也算是为单调的生活平添了几分乐趣。显然，如果先手某次随机选中的容器会使得油桶溢出，那么后手可以往先手的油桶里面装任意量的煤油，然后幸灾乐祸；因此我们约定：当先手溢出时，必定由先手搬两个油桶。

现在只剩下了一个问题：当 Y 和 S 都采取最优策略，使得对方搬的煤油尽可能地比自己多的时候，先手搬的煤油不多于后手的概率是多大？
## 输入格式

输入的第一行包括两个正整数 $N$ 和 $L$，分别表示转移用的容器数量和油桶的容积。

输入的第二行包括 $N$ 个正整数 $a_1, \cdots, a_N$，分别表示每个转移用的容器的容积。
## 输出格式

输出一个实数，表示先手搬的煤油不多于后手的概率。当你的输出与标准输出的绝对误差不超过 $10^{-6}$ 时，我们认为你的输出是正确的。
## 样例

### 样例输入 #1
```
2 4
1 2
```
### 样例输出 #1
```
0.687500000000000000

```
### 样例输入 #2
```
见附件中的 2.in
```
### 样例输出 #2
```
见附件中的 2.out
```
### 样例输入 #3
```
见附件中的 3.in
```
### 样例输出 #3
```
见附件中的 3.out
```
## 提示

#### 样例解释 1

可以证明，此时先手的策略一定是装满对方的油桶，且装满时必胜。经过若干次随机抽取后，能恰好将对方的油桶装满的概率为：

$$
\left(\frac{1}{2}\right)^2 + \binom{3}{1}\left(\frac{1}{2}\right)^3 + \left(\frac{1}{2}\right)^4 = \frac{11}{16}=0.6875
$$

#### 数据范围

对于 $100\%$ 的数据，保证 $1\le N\le 2\times 10^3$，$1\le L\le 10^9$，$1\le a_i\le 2\times 10^3$。

#### 题目来源

来自 2023 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2023）初赛。

题解等资源可在 <https://github.com/THUSAAC/THUPC2023-Pre> 查看。


---

---
title: "[省选联考 2023] 过河卒"
layout: "post"
diff: 省选/NOI-
pid: P9169
tag: ['博弈论', '各省省选', '2023', 'O2优化', '广度优先搜索 BFS', '拓扑排序']
---
# [省选联考 2023] 过河卒
## 题目背景

棋盘上有一个过河卒，需要走到底线。卒行走的规则是可以向左移动一格，向右移动一格或者向前移动一格。同时在棋盘上有两个另一方的棋子，需要拦截这个卒走到底线。这两个棋子的走法和帅一致，可以走到前后左右四个方向上相邻的格子。因此本题可以称为“帅拦过河卒”。
## 题目描述

有一个 $n$ 行 $m$ 列的棋盘。我们用 $(i,j)$ 表示第 $i$ 行第 $j$ 列的位置。棋盘上有一些 障碍，还有一个黑棋子和两个红棋子。

游戏的规则是这样的: 红方先走，黑方后走，双方轮流走棋。红方每次可以选择一个红棋子，向棋盘的相邻一格走一步。具体而言，假设红方选择的这个棋子位置在 $(i,j)$，那么它可以走到 $(i-1,j),(i+1,j),(i,j-1),(i,j+1)$ 中的一个，只要这个目的地在棋盘内且没有障碍且没有红方的另一个棋子。

黑方每次可以将自己的棋子向三个方向之一移动一格。具体地，假设这个黑棋子位置在 $(i,j)$，那么它可以走到 $(i-1,j),(i,j-1),(i,j+1)$ 这三个格子中的一个，只要这个目的地在棋盘内且没有障碍。

在一方行动之前，如果发生以下情况之一，则立即结束游戏，按照如下的规则判断胜负（列在前面的优先）：

- 黑棋子位于第一行。此时黑方胜。

- 黑棋子和其中一个红棋子在同一个位置上。此时进行上一步移动的玩家胜。

- 当前玩家不能进行任何合法操作。此时对方胜。

现在假设双方采用最优策略，不会进行不利于自己的移动。也就是说:

- 若存在必胜策略，则会选择所有必胜策略中，不论对方如何操作，本方后续获胜所需步数最大值最少的操作。
- 若不存在必胜策略，但存在不论对方如何行动，自己都不会落败的策略，则会选择任意一种不败策略。
- 若不存在不败策略，则会选择在所有策略中，不论对方如何操作，对方后续获胜所需步数最小值最大的操作。

如果在 $100^{100^{100}}$ 个回合之后仍不能分出胜负，则认为游戏平局。请求出游戏结束时双方一共移动了多少步，或者判断游戏平局。
## 输入格式

**本题有多组测试数据**。

输入的第一行包含两个整数 $\text{id},T$，分别表示测试点编号和数据组数。特别地，样例的 $\text{id}$ 为 $0$。

接下来包含 $T$ 组数据，每组数据的格式如下：

第一行包含两个正整数 $n,m$，表示棋盘的行数和列数。

接下来 $n$ 行，每行包含一个长度为 $m$ 的字符串，其中第 $i$ 行的第 $j$ 个字符表示棋盘上 $(i,j)$ 这个位置的状态。

在这些字符中：$\texttt{'.'}$ 表示空位；$\texttt{'\#'}$ 表示障碍物；$\texttt{'X'}$ 表示黑棋；$\texttt{'O'}$ 表示红棋。

保证黑棋恰好有一个，红棋恰好有两个，且黑棋不在第一行。
## 输出格式

对于每组数据，输出一行字符串。

如果游戏平局，请输出一行 $\texttt{"Tie"}$。

如果红方胜，请输出一行 $\texttt{"Red t"}$。其中 $\texttt{t}$ 为游戏结束时双方移动的步数之和。显然这应该是一个奇数。

如果黑方胜，请输出一行 $\texttt{"Black t"}$。其中 $\texttt{t}$ 为游戏结束时双方移动的步数之和。显然这应该是一个偶数。

注意，请输出双引号内的字符串，不包含双引号。
## 样例

### 样例输入 #1
```
0 5
4 5
...#O
.#..#
#O#..
.#..X
3 3
#.#
O.O
.X.
3 3
O..
.#X
.O.
5 5
.....
.....
..O..
#..#.
O#.X.
9 9
...######
.#.......
.#######.
.#.#.....
.#O#.####
.#.#.....
.#######.
.#X......
.O.......

```
### 样例输出 #1
```
Black 0
Black 2
Black 2
Tie
Red 75

```
### 样例输入 #2
```
见附件中的 zu/zu2.in
```
### 样例输出 #2
```
见附件中的 zu/zu2.ans
```
## 提示

**【样例 1 解释】**

第一组数据，红方第一步没有可行的移动，所以黑方胜。

第二组数据，无论第一步红方怎么移动，黑方都可以在下一步让黑棋子与红棋子在同一个位置。

第三组数据，无论第一步红方怎么移动，黑方都可以将自己的棋子往上移动一枚来达成胜利。

第四组数据，有一个红棋子不能动。另一个红棋子可以在第三行移动来防止黑棋子进入第一行。黑棋子也可以一直在第五行移动。如果红棋子到达第五行，黑棋子可以选择从另一边逃走。

第五组数据，在最后一行的那个红棋子可以从左边绕一圈抓住黑棋子。注意另一个红棋子可以移动。

**【样例 2 解释】**

这个样例中的每一组数据都满足测试点 $5$ 到 $13$ 中某一个测试点的限制。

**【子任务】**

对于所有的数据，保证：$1 \leq T \leq 10$，$2 \leq n \leq 10$，$1 \leq m \leq 10$，$\text{id}$ 等于测试点编号。

对于每组数据保证：棋盘上的黑棋恰好有一个，红棋恰好有两个，且黑棋不在第一 行。

- 测试点 $1 \sim 4$：保证要么平局，要么红方在开始时无法移动。

- 测试点 $5 \sim 6$：保证 $n \geq 4$ 。保证棋盘上第 $n-1$ 行的每一个格子都是障碍物，且 棋盘上其他行没有障碍物。保证黑棋在前 $n-2$ 行，有一个红棋在前 $n-2$ 行，另一个红棋在第 $n$ 行。

- 测试点 $7 \sim 9$：保证 $m=1$。

- 测试点 $10 \sim 13$：保证要么平局，要么存在策略可以在 $9$ 步之内结束游戏。

- 测试点 $14 \sim 20$：无特殊限制。


---

---
title: "『PG2』猪棋"
layout: "post"
diff: 省选/NOI-
pid: P9898
tag: ['博弈论', '交互题', 'Special Judge']
---
# 『PG2』猪棋
## 题目背景

交互库绝顶聪明。
## 题目描述

猪棋的规则：

在一个 $1000\times 1000$ 的棋盘上，两人分别执黑棋白棋轮流执子，每次可以在当前没有子的不同位置将两颗子分别放下（有序），如果一颗子放下时出现有 $(x,y),(x+1,y),(x,y+1),(x+1,y+1)$ 的四个位置棋子颜色均相同则执此颜色者获胜。

你将扮演先手，在 $100$ 步内战胜交互库扮演的后手，保证有解。

对于每轮，你可以选择两个坐标 $(x_1,y_1)$ 与 $(x_2,y_2)$ 落子，你首先需要保证 $1\leq x_1,y_1,x_2,y_2\leq 1000$，你其次需要保证没人曾在 $(x_1,y_1)$ 落子，如果此时你获胜了判定结束且你获胜，否则你还需保证没人曾经在 $(x_2,y_2)$ 落子,如果此时你获胜了判定结束且你获胜，否则交互库将返回一组 $x_1,y_1,x_2,y_2$ 表示他在 $(x_1,y_1),(x_2,y_2)$ 落子，保证 $(x_1,y_1)\neq (x_2,y_2),1\leq x_1,y_1,x_2,y_2\leq 1000$，如果此时交互库获胜判定结束且你输了,否则判定棋盘上是否已经有 $400$ 颗子，如果是你获得平局，否则进入你的新一轮。

## 输入格式

你每轮结束后从**标准输入**中输入四个整数，代表评测机返回的结果。
## 输出格式

每轮开始时，你需要向**标准输出**输出四个 $[1,1000]$ 中的整数，**然后清空缓冲区**。

你可以使用如下语句来清空缓冲区：

- 对于 C/C++：`fflush(stdout)`；
- 对于 C++：`std::cout << std::flush`；
- 对于 Java：`System.out.flush()`；
- 对于 Python：`stdout.flush()`；
- 对于 Pascal：`flush(output)`；
- 对于其他语言，请自行查阅对应语言的帮助文档。

特别的，对于 C++ 语言，在输出换行时如果你使用 `std::endl` 而不是 `'\n'`，也可以自动刷新缓冲区。



## 提示

共 $5$ 个测试点，在测试点中如果你获胜且每步都满足 $6\leq x,y\leq 994$ 你将获得 $100$ 分，否则获胜你将获得 $50$ 分，你输了将获得 $0$ 分，平局获得 $30$ 分，总分数取测试点最小值。

本题输入输出参考 $0$ 分程序：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
int x,y,xx,yy;


signed main()
{
    int i,j,k;
    n=100;
    while(n--)
    {
        cout<<rand()%1000+1<<' '<<rand()%1000+1<<endl;
        cout<<rand()%1000+1<<' '<<rand()%1000+1<<endl;
        cin>>x>>y>>xx>>yy;
    }
    return 0;
}
```



---

