---
title: "[信息与未来 2024] AI 机器人"
layout: "post"
diff: 省选/NOI-
pid: B3983
tag: ['模拟', '搜索', '2024', '矩阵运算', '江苏', '分治', '记忆化搜索', '矩阵加速', '信息与未来']
---
# [信息与未来 2024] AI 机器人
## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/27icb51c.png)

在 $n$ 行 $m$ 列的矩形空间中有一个机器人。矩形空间的每一个格子要么是平地（用半角点号 `.` 表示），要么是障碍物 （用井号表示 `#`）。以下是一个 $n = 3, m = 7$ 的例子：

```
...#...
...#...
.......
```

初始时,机器人位于矩形的左上角 （第一行、第一列）。每一时刻，机器人可以遵照程序执行 `U`（Up，向上）、`L` （Left，向左）、 `D` （Down，向下）、`R` （Right，向右） 四种指令中的一个，尝试向某个方向移动一格；如果移动的目标格子超出了边界或是障碍物，则保持原地不动，例如执行程序：

`LLLRRRRRRRRRDDDDRRRRRRRRR`

后，机器人会从空间的左上角移动到右下角。Dr. X 扩展了机器人程序的表达能力,引入了循环。给定程序 `P`，`(P)n` 相当于把程序 `P`“复制粘贴”$n$ 次。循环可以嵌套。例如，在足够大且无阻挡的空间中执行程序：

`(R(DRUL)7)5`

会重复 $5$ 次执行“向右移动一格、转圈 $7$ 次”，而如果机器人在 $n = 1, m = 2$ 的空间中执行上述程序，就会表现为“左右横跳”。

Dr. X 还给机器人装备了人工智能，对于某些指定的循环，机器人可以由深度神经网络自主决定循环的次数（$0$ 次或任意多次），用星号 `*` 表示，例如

`(DR(R)*)3`

外层循环会执行 $3$ 次，由于循环“复制粘贴”的特性，每次向下向右移动一格后，机器人可以根据自己的想法向右移动 $0$ 格或任意多格。人工智能循环也可以嵌套，根据循环“先外层后里层”的执行顺序，总是先确定外层人工智能循环的执行次数，再按照“复制粘贴”的规则执行内层循环代码。

人工智能模块使机器人的行为变得难以预测。给定一个机器人程序，Dr. X 想知道，哪些格子是机器人在执行程序过程中绝无可能经过的（即无论机器人如何选择循环执行的次数，都不会经过）？这样他可以在这些格子上安装监控，并在观察到机器人行为失控的时候及时制止。
## 输入格式

输入第一行两个空格分隔的整数 $n$ 和 $m$，代表矩形空间的大小为 $n$ 行、$m$ 列。

接下来 $n$ 行，每行 $m$ 个字符，描述了矩形空间。其中半角点号为平地、井号为障碍物。

输入最后一行是一个字符串，为机器人执行的程序。程序由 $\tt{U/L/D/R}$、圆括号、正整数、星号组成。输入程序保证合法：圆括号总是正确配对，且之后紧跟一个正整数或一个星号。除此之外，程序中所有的字符都是 $\tt{U,L,D}$ 或 $\tt{R}$。机器人初始时位于左上角，输入保证左上角不是障碍物。**固定次数循环的次数总是在 $1$ 到 $9$ 之间。**
## 输出格式

输出 $n$ 行，每行 $m$ 个字符，按顺序输出矩形空间中每个格子的计算结果。如果是障碍物格子，输出井号 `#`。如果是机器人选择适当的循环次数可以到达的平地格子，输出加号 `+`。否则输出半角点号 `.`。
## 样例

### 样例输入 #1
```
3 7
...#...
...#...
.......
LLLRRRRRRRRRDDDDRRRRRRRRR
```
### 样例输出 #1
```
+++#...
..+#...
..+++++
```
### 样例输入 #2
```
3 7
...#...
##.....
.......
(R(DRUL)7)5
```
### 样例输出 #2
```
+++#...
##+++++
..+++++
```
### 样例输入 #3
```
3 7
.......
.#####.
.......
(R)*(D)*
```
### 样例输出 #3
```
+++++++
+#####+
+.....+
```
## 提示

对于 $30\%$ 的数据，输入程序不含星号 `*` 且在 $10^5$ 步内终止。

对于另外 $30\%$ 的数据，输入程序中不含星号 `*`。

对于 $100\%$ 的数据，$1 \leq n, m \leq 10$，且输入程序的长度不超过 $1000$。

>本题原始满分为 $20\text{pts}$。


---

---
title: "[NAC 2025] Entrapment [Can't Judge Yet]"
layout: "post"
diff: 省选/NOI-
pid: P12622
tag: ['搜索', '2025', '交互题', 'Special Judge', '记忆化搜索', 'ICPC', 'NAC']
---
# [NAC 2025] Entrapment [Can't Judge Yet]
## 题目描述

 _Entrapment_  is an asymmetric two-player game that is played on a $3\times 3$ square grid. The two players are called the Runner and the Trapper. The grid squares are numbered from $1$ to $9$ as depicted below:

$$\begin{array}{|c|c|c|}
    \hline
    1 & 2 & 3 \\
    \hline
    4 & 5 & 6 \\
    \hline
    7 & 8 & 9 \\
    \hline
\end{array}$$

Before starting the game, the players agree on the number of rounds that the game will last, and on the starting state of the game board. Up to $8$ of the grid squares can be marked as _unavailable_. The players also choose who will be the Runner and who will be the Trapper. The Runner then secretly chooses a starting square from among those that are available (i.e., are not marked as unavailable) but does not tell the Trapper their choice.

Each of the game rounds consists of the following steps, in order:

- The Trapper publicly chooses some subset of the available squares (the empty set is allowed) and asks the Runner, "Are you currently in any of these squares?"
- The Runner answers truthfully whether or not they are in any of the chosen squares.
- The Trapper publicly chooses exactly one available square. That square becomes unavailable for the rest of the game. (The Runner might currently reside in that square; if so, nothing special happens.)
- The Runner secretly moves from their current square to an available orthogonally-adjacent square. If no such square exists, the Runner announces that they are trapped and the Trapper wins the game.

If the Runner has not been trapped by the end of the last round, they prove to the Trapper that they answered all questions truthfully by revealing their choice of starting square and the move that they made during each round. The Runner then wins the game.

Because the Runner's initial choice of square is secret, as are all of their subsequent moves, the Runner is allowed to "cheat" by not truly committing to a square.  At the end of the game, if the Runner can produce a choice of starting square and subsequent moves that do not result in being trapped and are consistent with the answers to the Trapper's questions during each round, that is enough for the Runner to win the game.
## 输入格式

### Interaction

This is an interactive problem. Given the number of game rounds and the set of squares that are initially marked unavailable, determine whether the
Runner or the Trapper would win assuming optimal play, and then prove it by
playing as that role against the judge. The judge will obey all game rules, but may or may not play optimally.

Interaction starts by reading a line of $2$ space-separated integers $R$ and $U$
($1 \leq R \leq 9$, $0 \leq U \leq 8$, $R + U \leq 9$): the
number of rounds in the game and the number of squares that are unavailable at the start of the game.

Next, if $U>0$, read a line of $U$ space-separated integers $s$ ($1 \leq s \leq 9$): the labels of the squares that are unavailable at the start of the game. Please refer to the diagram above for how the squares in the grid are labeled. The $U$ labels are guaranteed to be distinct.

Determine whether the Runner or Trapper would win the game with optimal play, given the starting board and number of game rounds. Print a line of output with the string $\texttt{Runner}$ if the runner wins with optimal play, and the string $\texttt{Trapper}$ otherwise. You will play as that role for the rest of the game; please see the appropriate section below for further instructions on how to interact with the judge in that role.

**For the Runner**, repeat the following steps $R$ times:

- Read a line of input with a single integer $N$: the size of the subset of available squares that the Trapper has chosen to ask about. $N$ is guaranteed to be between $0$ and the number of available squares left on the board, inclusive.
- If $N>0$, read a line of $N$ space-separated integers $\ell$ ($1 \leq \ell \leq 9$) listing the labels of the squares in the Trapper's chosen subset. The labels are guaranteed to be distinct and all of the chosen squares are guaranteed to be available.
- Print a line of output containing either the string $\texttt{Yes}$ or the string $\texttt{No}$. The former informs the trapper that you are currently in one of the chosen squares; the latter informs the trapper that you are not.
- Read a line with a single integer $i$ ($1 \leq i \leq 9$),  the label of the square that the Trapper marks as unavailable. It is guaranteed that square $i$ is a formerly-available square.
- Print a line with the string $\texttt{Free}$ to inform the Trapper that you have secretly moved to an orthogonally-adjacent available square and are ready to proceed to the next round. If there are no orthogonally-adjacent squares available, you must print $\texttt{Trapped}$ instead and exit; your submission will be judged incorrect for having failed to elude the Trapper.

After you have played $R$ rounds of the game according to the protocol above, print a line with $R+1$ space-separated integers. The first integer is the label of your chosen starting square; each of the next $R$ integers are the labels of the squares onto which you moved at the end of each of the $R$ rounds. Your moves must be legal and must be consistent with the answers you gave to the Trapper's queries during each round of play. After printing this line, your program must exit.

**For the Trapper**, repeat the following steps $R$ times:

- Print a line with a single integer $N$: the size of the subset of available squares that you would like to ask the Runner about.
- If $N>0$, print a line of $N$ space-separated integers listing the available squares to ask the Runner about. You may list the labels in any order, but the labels must be distinct and must refer to available squares.
- Read a line of input containing a single string: $\texttt{Yes}$ if the Runner is in one of your chosen squares, or $\texttt{No}$ otherwise.
- Print a line with a single integer $i$: the square that you are marking unavailable. The label $i$ must be a valid currently-available square.
- Read a line with a single string: $\texttt{Free}$ if the Runner has moved to an available square, or $\texttt{Trapped}$ if they were unable to do so. After reading the word $\texttt{Trapped}$, you have won the game, and your program must exit. If you read the word $\texttt{Free}$ at the end of the $R$th round, your program must also exit, though your submission will be judged incorrect since you have failed to trap the Runner.

The judge is guaranteed to answer all questions truthfully.

**Do not forget to flush the output stream after each line that you print** and to cleanly exit after the interaction is done. Please also make sure that you follow the above interaction protocol exactly regarding what information to print on which line of output: for example, if the protocol requires you to print a list of space-separated integers on a single line, the judge **will not** accept each integer on its own line.

If the judge receives invalid or unexpected input, it will print $-1$ and then immediately exit. Your program must detect this error report and cleanly exit in order to receive a Wrong Answer verdict. If your program blocks waiting for further interaction from the judge, or tries to interpret the $-1$ as a game move, you may receive a different rejected verdict (such as Time Limit Exceeded or Runtime Error) instead of Wrong Answer.

You have been provided with a command-line tool for local testing. The tool has comments at the top to explain its use.
## 输出格式

See Interaction.
## 样例

### 样例输入 #1
```
3 6
1 2 3 7 8 9



Yes

Free

No

Trapped
```
### 样例输出 #1
```


Trapper
2
4 5

5

0

6
```
### 样例输入 #2
```
2 0

7
3 1 2 8 9 4 5

5

4
4 6 7 8

7
```
### 样例输出 #2
```

Runner


Yes

Free


Yes

Free
5 4 1
```


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
title: "[JLOI2014] 天天酷跑"
layout: "post"
diff: 省选/NOI-
pid: P3257
tag: ['动态规划 DP', '搜索', '2014', '吉林', '记忆化搜索']
---
# [JLOI2014] 天天酷跑
## 题目描述

在游戏天天酷跑中，最爽的应该是超级奖励模式了吧，没有一切障碍，可以尽情的吃金币，现在请你控制游戏角色来获得尽可能多的分数。游戏界面离散为一个长度为 $1 \sim n$，高度为 $1 \sim m$（初始点为 $(0,1)$）的矩阵图。每个格子上都有收益 $(-1 \sim 1000)$，$-1$ 表示该点不能通过。游戏角色从起点一路奔跑向终点，中途可以跳跃来获得更高的分数，在空中还能进行连跳。

游戏开始前你可以设定跳跃的高度，以及能连跳的次数，初始跳跃高度为 $1$，连跳数为 $1$（最多为 $5$），升级跳跃高度和连跳都需要一定的花费。跳跃高度设定完后游戏角色每次跳跃高度都将固定，连跳必须在下落过程中可以使用。所有操作都将在整点上完成，需要保证设定完的跳跃高度及连跳数，无法跳出游戏高度上限。

![](https://cdn.luogu.com.cn/upload/pic/17609.png) 

从 $(1,1)$ 点用一次跳跃，一次经过 $(2,2),(3,3),(4,2),(5,1)$。

以下是连跳数为 $2$ 连跳，跳跃高度为 $2$ 的跳跃方案：

![](https://cdn.luogu.com.cn/upload/pic/17610.png)

从 $(1,1)$ 起跳，依次经过 $(2,2),(3,3),(4,2)$ 再使用连跳，经过 $(5,3),(6,4),(7,3),(8,2),(9,1)$。

![](https://cdn.luogu.com.cn/upload/pic/17611.png)
## 输入格式

第一行四个整数 $n,m,cost_1,cost_2$。$n,m$ 如题意所示，$cost_1,cost_2$ 分别表示每升一级跳跃高度，连跳数所需的花费。

接下来 $m$ 行，每行 $n$ 个数。第 $i$ 行第 $j$ 个数表示地图中高度为 $i$，长度在第 $j$ 列处的收益。

## 输出格式

如果无法跑出终点线，就输出 `mission failed`，否则输出一行三个数，分别表示最大收益；及最大收益时，最小的连跳数；最大收益，最小连跳数时，最小的跳跃高度。

## 样例

### 样例输入 #1
```
7 4 6 10
9 4 7 7 4 3 2
18 8 9 4 15 12 4
19 2 4 7 10 18 12
8 1 13 14 16 0 14
```
### 样例输出 #1
```
67 1 2
```
## 提示

对于 $20 \%$ 的数据，满足 $m=2$，$1 \le n \le 10 ^ 5$。

对于另外 $80 \%$ 的数据，$1 \le n \le 10000$，$2 < m \le 20$，其中有 $20\%$ 的数据保证 $2 < n \le 10$，$1 \le m \le 10$。


---

---
title: "[POI 2015] PUS"
layout: "post"
diff: 省选/NOI-
pid: P3588
tag: ['2015', '线段树', 'POI（波兰）', 'Special Judge', '记忆化搜索', '拓扑排序']
---
# [POI 2015] PUS
## 题目描述

给定一个长度为 $n$ 的正整数序列 $a$，每个数都在 $1$ 到 $10^9$ 范围内，告诉你其中 $s$ 个数，并给出 $m$ 条信息，每条信息包含三个数 $l,r,k$ 以及接下来 $k$ 个正整数，表示 $a_l, a_{l+1}, \ldots, a_{r-1}, a_r$ 里这 $k$ 个数中的任意一个都比任意一个剩下的 $r-l+1-k$ 个数大（严格大于，即没有等号）。

请任意构造出一组满足条件的方案，或者判断无解。
## 输入格式

第一行包含三个正整数 $n,s,m$（$1 \leq s \leq n  \leq 10^5$，$1 \leq m \leq 2 \times 10^5$）。接下来 $s$ 行，每行包含两个正整数 $p_i,d_i$,表示已知 $a_{p_i}=d_i$，保证 $p_i$ 递增。

接下来 $m$ 行,每行一开始为三个正整数 $l_i,r_i,k_i$）$1 \leq l_i < r_i \leq n$，$1 \leq k_i \leq r_i-l_i$），接下来 $k_i$ 个正整数 $x_1..x_2...x_{k_i}$（$l_i \leq x_1 < x_2 < ... < x_{k_i} \leq r_i$），表示这 $k_i$ 个数中的任意一个都比任意一个剩下的 $r_i-l_i+1-k_i$ 个数大。（$\sum k \leq 3 \times 10^5$）
## 输出格式

若无解，则输出 `NIE`。否则第一行输出 `TAK`，第二行输出 $n$ 个正整数，依次输出序列 $a$ 中每个数。
## 样例

### 样例输入 #1
```
5 2 2
2 7
5 3
1 4 2 2 3
4 5 1 4
```
### 样例输出 #1
```
TAK
6 7 1000000000 6 3
```
### 样例输入 #2
```
3 2 1
2 3
3 5
1 3 1 2

```
### 样例输出 #2
```
NIE

```
### 样例输入 #3
```
2 1 1
1 1000000000
1 2 1 2
```
### 样例输出 #3
```
NIE

```
## 提示

原题名称：Pustynia。

本题另外提供两组额外样例，可以在附件中下载。


---

---
title: "[APIO2013] 机器人"
layout: "post"
diff: 省选/NOI-
pid: P3638
tag: ['搜索', '2013', 'APIO', '记忆化搜索', '队列']
---
# [APIO2013] 机器人
## 题目描述

VRI（Voltron 机器人学会）的工程师建造了 n 个机器人。任意两个兼容的机 器人站在同一个格子时可以合并为一个复合机器人。

我们把机器人用 1 至 n 编号（n ≤ 9）。如果两个机器人的编号是连续的，那 么它们是兼容的，可以合并成一个复合机器人。最初这 n 个机器人各自都只有唯 一的编号。而一个由两个或以上的机器人合并构成的复合机器人拥有两个编号， 分别是构成它的所有机器人中最小和最大的编号。

例如，2 号机器人只可以与 1 号或 3 号机器人合并。若 2 号机器人与 3 号机 器人合并，可构成编号为 2-3 的复合机器人。如果编号为 2-3 的复合机器人与编 号为 4-6 的复合机器人合并，可构成编号为 2-6 的复合机器人。当所有机器人合 并以后则构成 1-n 复合机器人。

工程师把这 n 个机器人放在了一个封闭的房间中，房间四周均是墙。该房间 被划分成 w × h 个方格。有些方格有障碍物，机器人不可经过或停留；其余方格 允许多个机器人停留，同时允许机器人经过。任何时候一个机器人只占用一个方 格。初始时刻，所有机器人均在不同的方格中。

这些原始的机器人不会自发地移动。它们只有被工程师沿 x 轴或 y 轴推动 后，才会沿推动的方向不断向前直线移动，直至碰到障碍物或墙停止移动。停止 移动后，它会扫描当前的格子是否存在可以与它合并的机器人，如果有，则合并 并继续检查，直至不能再合并为止。工程师只能沿水平向左、水平向右、竖直向 上、竖直向下四个方向推动机器人，并且，在机器人尚未停止移动时，不允许推 动其它机器人，因此任何时刻，房间中都只能有一个机器人移动。

为了帮助机器人转向，工程师在一些格子中放置了转向器。具体地说，转向 器分为顺时针转向器（右转器）和逆时针转向器（左转器），顺时针转向器可以 使到达该格子的机器人沿顺时针方向转向 90°；逆时针转向器可以使到达该格 子的机器人沿逆时针方向转向 90°。

现在，我们将告诉你初始时刻房间内的信息。请你计算工程师最少共计需要 推动机器人多少次，才能把所有的 n 个机器人全部合并（如果可能的话）。

## 输入格式

你的程序必须从标准输入读入。

输入的第 1 行包含 3 个整数 n、w 和 h，用 空格隔开。

输入文件中接下来的 h 行描述初始时刻房间内的信息，每行包含 w 个字符。 这 w × h 个字符中每一个表示房间中的一个格子，意义如下：

‘1’至‘9’：表示该方格中有一个机器人，编号为这个数字；

‘x’：表示该方格有障碍物；

‘A’：表示该方格中有一个逆时针转向器；

‘C’：表示该方格中有一个顺时针转向器；

‘.’：表示该方格为空地。

## 输出格式

你的程序必须输出到标准输出。输出仅一个整数，表示最少需要推动的次数。 若不能使所有机器人全部合并，输出-1。

## 样例

### 样例输入 #1
```
4 10 5 
1.........
AA...x4...
..A..x....
2....x....
..C.3.A...
```
### 样例输出 #1
```
5
```
## 提示

第一步：向右推动 3 号机器人，当它碰到转向器后会向上继续移动，直至碰 到墙壁停止移动。

第二步：向上推动 4 号机器人，当它碰到墙壁后停止移动，与 3 号机器人合 并，构成 3-4 号机器人

第三步：向上推动 2 号机器人，当它碰到转向器后会向左移动，由于左侧为 墙壁，故停留在原地。

第四步：向右推动 2 号机器人，由于它在一个转向器上，故它会向上移动， 直至碰到墙壁停止移动，与 1 号机器人合并，构成 1-2 号机器人。

第五步：向左推动 3-4 号机器人，当它碰到墙壁后停止移动，与 1-2 号机器 人合并，构成 1-4 号机器人。


我们将使用以下 4 类输入测例测试你的程序。

1. （10 分）测例满足 n = 2，w ≤ 10 且 h ≤ 10，没有任何转向器。

2. （20 分）测例满足 n = 2，w ≤ 10 且 h ≤ 10。

3. （30 分）测例满足 n ≤ 9，w ≤ 300 且 h ≤ 300。

4. （40 分）测例满足 n ≤ 9，w ≤ 500 且 h ≤ 500。



---

---
title: "[BJOI2017] 机动训练"
layout: "post"
diff: 省选/NOI-
pid: P3713
tag: ['动态规划 DP', '搜索', '2017', '各省省选', '记忆化搜索']
---
# [BJOI2017] 机动训练
## 题目背景

> AM 4:45
>
> 又是晴朗的好天气。
>
> AM 5:00
>
> 不要嘛，再睡一会
>
> AM 5:05
>
> 呜……欺负人
## 题目描述

睡眼朦胧的菜酱 (?) 已经被二爷拉起来晨跑了。而这个时间你在做什么呢？

咳咳，言归正传，最近菜酱的训练遇到了点小麻烦。

凌晨绕格瑞赛亚岛跑一圈是基本，在那之后，菜酱还要接受严格的机动训练。所谓机动训练，就是在紧急情况 (?) 下，高速且隐蔽地从位置 $s$ 移动到位置 $t$ 的训练。一般来说，$s$ 和 $t$ 是根据二爷的心情随机决定的，但是由于菜酱已经熟悉了地形，每次总是能找到不太费劲的路径，二爷决定增大难度。所谓增大难度，其实就是指定整条路径，这样菜酱就没办法抄近道了。当然，由于是为了实战而进行的训练，二爷也不会随便乱指定路径，至少不会故意绕路。然后发生的问题就是，如何才能「随机」一整条路径出来？二爷统计了全岛所有的合法路径，打算每次在这个表格里随机抽一条出来。但是很快二爷发现，许多路径所经过的地形是完全相同的，这类路径的训练会更加有用。于是二爷修改了随机策略，地形较为常见的路径权重会变得更大。

一次偶然的机会，菜酱看到了二爷的随机策略，并发动技能「过目不忘 (?)」记了下来。现在你要帮菜酱分析数据。

为什么是你？当然是因为否则就会被菜酱爆头 (并不)。

整个岛可以看作一片 $m\times n$ 的区域，每个格子有自己的地形。

一条路径由一系列八连通的格子组成，两个格子八连通当且仅当这两个格子拥有公共的顶点。

定义一条“机动路径”如下：

1. 它是一条不自交的路径，即路径上任意两个格子都不是同一个。
2. 它的起点和终点处于不同位置，换言之这条路径至少包含 $2$ 个格子。
3. 从起点开始，任何一步只能向不远离终点的方向移动，这里不远离指的是 $x$ 和 $y$ 两个方向都不远离。

举例说明：

```plain
.....t    ......    .---.
-++...    ---...    .-s-.
-s+...    -s+..t    .-+-.
---...    ---...    ..t..
```

图中加号和减号标明了与 $s$ 八连通的所有格子，其中加号是“不远离 $t$”的方向。

因此可以看出，如下路径是机动路径：

```plain
++++++t    ......+t    .......t
+......    .....++.    ......+.
+......    ..++++..    ...+++..
s......    s++.....    s+++....
```

而如下路径不是机动路径：

```plain
\../---t    .......t    .s.
|--.....    ....../.    /..
|.......    s..../..    \..
s.......    .\--/...    .t.
```

需要注意的是，某些不合法的路径甚至比机动路径还要短，这是因为机动路径不是按照长度来定义的。

接下来定义一条机动路径的地形，岛上的地形由一个矩阵给出，如：

```plain
.**.
*..*
*..*
.**.
```

那么，一条机动路径的地形序列就是它所经过的地形排成一列，如：

```plain
s-\.
...\
...|
...t
```

地形序列就是 `.****.`。

每条机动路径的权重就是与之拥有相同地形序列的机动路径数量之和，例如与这条路径拥有相同地形序列的路径有

```plain
./-t    t...    ...s    s-\.    ./-s    s...    ...t    t-\.
/...    |...    ...|    ...\    /...    |...    ...|    ...\
|...    \...    .../    ...|    |...    \...    .../    ...|
s...    .\-s    t-/.    ...t    t...    .\-t    s-/.    ...s
```

共 $8$ 条，注意回文时正反算两条，以及自己也算一条。

所以这条机动路径的权重是 $8$，同时所有这 $8$ 条机动路径的权重都是 $8$。

现在你需要统计所有的机动路径权重之和。

如果对这种统计方式没有直观的感受，可以查看样例说明。

## 输入格式

第一行两个整数 $m,n$，表示岛的大小。

接下来 $m$ 行，每行 $n$ 个字符，表示岛的地形。
## 输出格式

仅一个数，表示所有机动路径的权重之和。

由于这个数可能很大，你只需要输出它对 $10^9+9$ 取模的结果。
## 样例

### 样例输入 #1
```
2 2
.*
*.
```
### 样例输出 #1
```
72
```
### 样例输入 #2
```
2 3
.*.
*.*
```
### 样例输出 #2
```
418
```
### 样例输入 #3
```
4 4
abba
baab
baab
abba
```
### 样例输出 #3
```
44512
```
## 提示

### 样例解释 1
用中括号括起来的一些数对表示一条机动路径，坐标先行后列：

- 地形序列 `.*`：$[(1, 1), (1, 2)],\ [(1, 1), (2, 1)],\ [(2, 2), (2, 1)],\ [(2, 2), (1, 2)]$，共 $4$ 条，每条权重为 $4$，计 $16$。
- 地形序列 `*.`：$[(1, 2), (1, 1)],\ [(2, 1), (1, 1)],\ [(2, 1), (2, 2)],\ [(1, 2), (2, 2)]$，共 $4$ 条，每条权重为 $4$，计 $16$。
- 地形序列 `..`：$[(1, 1), (2, 2)],\ [(2, 2), (1, 1)]$，共 $2$ 条，每条权重为 $2$，计 $4$。
- 地形序列 `**`：$[(1, 2), (2, 1)],\ [(2, 1), (1, 2)]$，共 $2$ 条，每条权重为 $2$，计 $4$。
- 地形序列 `.*.`：$[(1, 1), (1, 2), (2, 2)],\ [(1, 1), (2, 1), (2, 2)],\ [(2, 2), (2, 1), (1, 1)],\ [(2, 2), (1, 2), (1, 1)]$，共 $4$ 条，每条权重为 $4$，计 $16$。
- 地形序列 `*.*`：$[(1, 2), (1, 1), (2, 1)],\ [(2, 1), (1, 1), (1, 2)],\ [(1, 2), (2, 2), (2, 1)],\ [(2, 1), (2, 2), (1, 2)]$，共 $4$ 条，每条权重为 $4$，计 $16$。

共计 $16+16+4+4+16+16=72$。

### 样例解释 2
- 地形序列 `.*`：$7$ 条，每条权重为 $7$，计 $49$。
- 地形序列 `*.`：$7$ 条，每条权重为 $7$，计 $49$。
- 地形序列 `..`：$4$ 条，每条权重为 $4$，计 $16$。
- 地形序列 `**`：$4$ 条，每条权重为 $4$，计 $16$。
- 地形序列 `..*`：$2$ 条，每条权重为 $2$，计 $4$。
- 地形序列 `.*.`：$10$ 条，每条权重为 $10$，计 $100$。
- 地形序列 `.**`：$2$ 条，每条权重为 $2$，计 $4$。
- 地形序列 `*..`：$2$ 条，每条权重为 $2$，计 $4$。
- 地形序列 `*.*`：$10$ 条，每条权重为 $10$，计 $100$。
- 地形序列 `**.`：$2$ 条，每条权重为 $2$，计 $4$。
- 地形序列 `.*.*`：$6$ 条，每条权重为 $6$，计 $36$。
- 地形序列 `*.*.`：$6$ 条，每条权重为 $6$，计 $36$。

共计 $49+49+16+16+4+100+4+4+100+4+36+36=418$。

### 数据范围

- 对于 $10\%$ 的数据，$m\times n \le 4$。
- 对于 $30\%$ 的数据，$m, n \le 5$。
- 对于 $60\%$ 的数据，$m, n \le 10$。
- 另有 $20\%$ 的数据，所有地形均相同。
- 对于 $100\%$ 的数据，$1 \le m, n \le 30$，字符集由大小写字母，数字和 `.` `*` 构成。


---

---
title: "朋也与光玉"
layout: "post"
diff: 省选/NOI-
pid: P4962
tag: ['搜索', '剪枝', '记忆化搜索', '状压 DP']
---
# 朋也与光玉
## 题目背景

> 一つ一つの光は小さくでも、たくさん集まればきっととても不思議な大きな力になるはず。 

渚的离世、汐的离去...朋也的人生几乎陷入了一片黑暗。

但是，这会是结束吗？

![](https://i.loli.net/2018/10/04/5bb5f64297c70.jpg)
## 题目描述

光坂小镇是一个由 $n$ 个点（编号为 $1$ ~ $n$），$m$ 条有向边构成的图，每个节点上都有一个光玉，光玉共有 $k$ 种，编号为 $0$ ~ $k-1$。

为了使一切改变，朋也需要找齐全部的 $k$ 种光玉。他可以从任意一个节点出发，在图上任意行走，但不会经过同一个节点两次，每碰到一个光玉便会将其收集，收集到 $k$ 个光玉后，即经过了 $k$ 个节点后，便不会继续收集。请设计一种方案，使得朋也能够收集全部的 $k$ 种光玉，且走过的路径长度最短。

换句话说，每个点一个颜色，找到一条最短的点数为 $k$ 、恰好经过全部 $k$ 种颜色的路径。你需要求出这条路径的长度。
## 输入格式

第一行，三个正整数 $n,\ m,\ k$，分别代表节点个数、边的条数、光玉的种类数。

第二行，共 $n$ 个正整数 $a_1$ ~ $a_n$，其中 $a_i$ 代表 $i$ 号节点的光玉种类编号。

接下来 $m$ 行，每行三个正整数 $u_i,\ v_i,\ w_i$，表示 $u_i$ 到 $v_i$ 有一条长度为 $w_i$ 的有向边。
## 输出格式

输出一行，若有解则输出一个正整数表示满足条件的最短路径的长度，若无解则输出"Ushio!"（不含引号）
## 样例

### 样例输入 #1
```
8 19 3
1 2 0 1 1 1 2 0
3 1 4
3 2 2
1 4 1
7 4 10
5 4 7
4 2 5
5 6 4
4 7 3
8 5 10
3 6 8
8 1 10
5 2 10
6 7 3
4 3 9
6 2 5
4 8 10
3 8 3
1 7 8
1 3 9
```
### 样例输出 #1
```
11
```
### 样例输入 #2
```
5 6 3
0 1 1 2 2
1 2 3
2 3 2
1 4 2
5 2 1
1 3 4
5 4 1
```
### 样例输出 #2
```
Ushio!
```
### 样例输入 #3
```
6 13 3
2 2 2 1 0 2
1 4 4
3 4 8
5 3 2
4 5 6
2 3 2
1 3 3
1 2 4
3 1 4
6 3 6
3 2 6
2 1 6
4 2 9
5 2 1
```
### 样例输出 #3
```
7
```
## 提示

$2\le n\le 100$，$1\le m\le n(n-1)$，$2\le k\le 13$，$1\le w_i\le 10^7$

保证图中没有重边、自环。

## 样例解释

样例一，$3\rightarrow 6\rightarrow 7$ 为一组最优解。

样例二，无解。

样例三，最优解为 $4\rightarrow 5\rightarrow 2$。


---

---
title: "[CCO 2021] Weird Numeral System"
layout: "post"
diff: 省选/NOI-
pid: P7829
tag: ['2021', 'Special Judge', 'CCO（加拿大）', '记忆化搜索', '数位 DP', '进制']
---
# [CCO 2021] Weird Numeral System
## 题目描述

Alice 正在思考一个关于 $k$ 进制整数的问题。

普通的 $k$ 进制可以将整数 $n$ 表示为 $d_{m - 1} d_{m - 2} \cdots d_0$，且满足：

1. $0 \leq d_i < k$；
2. $n = \displaystyle\sum_{i = 0}^{m - 1} d_i k^i$。

然而，普通的 $k$ 进制整数对于 Alice 来说太简单了，Alice 更喜欢奇怪的 $k$ 进制整数。它与普通 $k$ 进制整数的差别仅仅在于将 $0 \leq d_i < k$ 换成了 $d_i \in a$，其中 $a$ 为一个长为 $D$ 的数列。

现在有一组固定的 $a_1, a_2, \cdots, a_D$，Alice 想要将 $q$ 个十进制整数 $n_1, n_2, \cdots, n_q$ 全部转化为奇怪的 $k$ 进制整数，这种问题显然更适合写程序来解决。
## 输入格式

第一行，四个整数 $k, q, D, M$；

第二行，$D$ 个整数 $a_1, a_2, \cdots, a_D$；

接下来 $q$ 行，每行一个整数 $n_i$。
## 输出格式

$q$ 行，第 $i$ 行表示 $n_i$ 转化后的结果，按幂次从高到低的顺序输出每一位，两个位之间用单个空格间隔。当 $a_i$ 中包含 $0$ 时，你转化的结果可以包含前导零，但最好不要太多；当 $n_i = 0$ 时，你转化的结果也不能为空。如果有多种方案可以随便输出一种，如果无法转化输出 `IMPOSSIBLE`。
## 样例

### 样例输入 #1
```
3 3 3 1
-1 0 1
15
8
-5
```
### 样例输出 #1
```
1 -1 -1 0
1 0 -1
-1 1 1
```
### 样例输入 #2
```
10 1 3 2
0 2 -2
17
```
### 样例输出 #2
```
IMPOSSIBLE
```
## 提示

**本题由 @[Leasier](https://www.luogu.com.cn/user/201007) 提供 SPJ。**
#### 数据范围
对于 $100\%$ 的数据，$2 \leq k \leq 10^6$，$1 \leq q \leq 5$，$1 \leq D \leq 801$，$1 \leq M \leq 400$，$-M \leq a_i \leq M$，$-10^{18} \leq n_i \leq 10^{18}$。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D1T2


---

---
title: "挑战 NPC IV"
layout: "post"
diff: 省选/NOI-
pid: P9838
tag: ['动态规划 DP', '数学', '洛谷原创', 'O2优化', '记忆化搜索', '位运算', '洛谷月赛']
---
# 挑战 NPC IV
## 题目背景

要是什么都和 NPC 问题一样简单就好了啊。
## 题目描述

小 A 想为小 B 写一首情诗。他现在想出了 $n$ 个句子，每个句子的优美度分别为 $1, 2 \dots n$。小 A 需要按照一定的顺序将他们组合起来，拼成一首完整的诗。换句话说，小 A 需要重新排列这 $n$ 个句子，形成一个 $1 \sim n$ 的排列 $p_1, p_2\dots p_n$；第 $i$ 行诗句的优美度就是原先第 $p_i$ 个句子的优美度，也就是 $p_i$。

不过，由于小 A 是位 OIer，所以他的文采并不是很稳定。他实际上会严重高估自己诗句的优美程度。若一条诗句在小 A 眼里的优美度为 $x$，那么小 B 认为它的优美度是 **$x$ 在二进制表示下最低位的 $1$ 的位置**。其中，小 B 认为最低位的位置是 $1$，次低位为 $2$，以此类推。也就是说，小 B 眼中的优美度 $f(x)$ 为 $1 + \log_2 \operatorname{lowbit}(x)$。

小 A 知道，小 B 拿到诗后，只会选取诗的一段来看，而她感受到的优美度是所有她读到的诗句之和。具体的，若诗有 $n$ 句，则小 B 会在 $[1, n]$ 的所有长度 $> 0$ 的区间中抽取一个 $[l, r]$，感受到 $\displaystyle\sum_{l \leq i \leq r}f(p_i)$ 的优美度。小 A 为了衡量一首诗的优美度，决定将一首诗的总优美度定义为 **所有情况下小 B 感受到的优美度之和**。

照理来说，总优美度最大的组合方式必然是最好的。遗憾的是，在小 A 的精密计算下，他发现，只有他选择总优美度恰好为 **第 $k$ 小** 的情诗时，他才最有可能和小 B 走到一起。于是，小 A 想要知道，对于 $n!$ 首本质不同的诗，第 $k$ 小可能的总优美度是多少。两首诗本质相同当且仅当原排列 $p_1 \dots p_n$ 相同。

小 A 发现这是一个 NPC 问题，他只好来向你求助了。由于总优美度过于巨大，你只需要帮他求出答案对 $998244353$ 取模后的结果。

特别的，小 A 写了 $q$ 组诗句，所以你需要分别回答他的 $q$ 个问题。
## 输入格式

从标准输入中读入数据。

第一行一个正整数 $q$，表示诗句的组数。

对于每组数据，仅一行两个正整数 $n, k$ 描述小 A 的问题。
## 输出格式

输出到标准输出。

对于每组诗句，输出一行一个整数，表示第 $k$ 小的总优美度对 $998244353$ 取模后的结果。
## 样例

### 样例输入 #1
```
2
3 2
3 6
```
### 样例输出 #1
```
13
14

```
### 样例输入 #2
```
5
4 1
4 10
4 16
4 20
4 24
```
### 样例输出 #2
```
32
34
36
36
38
```
### 样例输入 #3
```
10
1000000000000000000 1000000000000000000
1145141919810 19260817998244353
15 131413141314
36 93930322810121243
172 354354645654567654
666 233
1048576 2147483648
1000000007 1000000009
99824 44353
10 1
```
### 样例输出 #3
```
36226088
846277092
1096
12356
1239174
70731494
274614617
511280969
625722816
330
```
## 提示

#### 【样例 1 解释】

例如，当 $p = [1, 3, 2]$ 时，小 B 眼中每句诗的优美度分别为 $[1, 1, 2]$。那么：

- 当 $l = 1$，$r = 1$ 时，优美度之和为 $1$。
- 当 $l = 2$，$r = 2$ 时，优美度之和为 $1$。
- 当 $l = 3$，$r = 3$ 时，优美度之和为 $2$。
- 当 $l = 1$，$r = 2$ 时，优美度之和为 $1 + 1 = 2$。
- 当 $l = 2$，$r = 3$ 时，优美度之和为 $1 + 2 = 3$。
- 当 $l = 1$，$r = 3$ 时，优美度之和为 $1 + 1 + 2 = 4$。

所以 $p = [1, 3, 2]$ 的总优美度为 $1 + 1 + 2 + 2 + 3 + 4 = 13$。

对于所有 $3! = 6$ 个排列 $p$，其总优美度从小到大排序后分别为 $13, 13, 13, 13, 14, 14$，因此当 $k = 2$ 与 $k = 6$ 时答案分别为 $13$ 和 $14$。

---

#### 【样例 2】

见附件下的 $\verb!npc/npc2.in!$ 与 $\verb!npc/npc2.ans!$。

---

#### 【样例 3】

见附件下的 $\verb!npc/npc3.in!$ 与 $\verb!npc/npc3.ans!$。

---

#### 【数据范围】

**本题各测试点时间限制不相同。具体地，每个点的时间限制为 $\max(q\times 0.5, 2)\ \rm{s}$**。

| 测试点编号 | $n$ | $k \leq$ | $q = $ |
| :--------: | :-: | :------: | :----: |
| $1 \sim 3$ | $\leq 10$ | $n!$ | $2$ |
| $4 \sim 8$ | $\leq 10^3$ | $2$ | $7$ |
| $9 \sim 13$ | $\in [10^5, 10^6]$ | $\min(10^{18}, n!)$ | $7$ |
| $14 \sim 17$ | $\leq 10^6$ | $\min(10^{18}, n!)$ | $7$ |
| $18 \sim 25$ | $\leq 10^{18}$ | $\min(10^{18}, n!)$ | $10$|

对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^{18}$，$1 \leq k \leq \min(10^{18}, n!)$，$1 \leq q\le 10$。


---

