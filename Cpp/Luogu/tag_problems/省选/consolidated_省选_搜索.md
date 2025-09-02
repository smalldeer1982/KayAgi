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
title: "「CMOI R1」mex1"
layout: "post"
diff: 省选/NOI-
pid: P11171
tag: ['数学', '2024', '洛谷原创', 'Special Judge', 'O2优化', '深度优先搜索 DFS', '剪枝', '构造']
---
# 「CMOI R1」mex1
## 题目背景

小 U 对于从一个集合映射到一个数的函数很感兴趣，而 $\text{mex}$ 是一个很好的例子。

$\text{mex}(S)$ 指的是在集合 $S$ 中没有出现过的最小非负整数。
## 题目描述

多组数据。

每组数据，给定 $c$，要求构造序列 $a_1,a_2,...,a_n\in [0,2\times 10^9]$ 满足 

$$\sum\limits_{S\neq \emptyset,S\subseteq \{1,2,...,n\}}\text{mex}(a_{S_1},a_{S_2},...,a_{S_{|S|}})=c$$


其中要求 $1\le n\le40$。可以证明在该题的数据范围内如果存在解，则在 $1\le n\le 40$ 时一定存在解。
## 输入格式

第一行一个整数，数据组数 $T$。

之后 $T$ 行每行一个非负整数 $c$。
## 输出格式

对于每组数据：

如果无解，则仅输出一行一个整数 $-1$。

否则，第一行输出一个正整数 $n$。

第二行输出 $n$ 个非负整数 $a_1,a_2,...,a_n$。
## 样例

### 样例输入 #1
```
5
120
8128
248
0
5
```
### 样例输出 #1
```
7
1 9 1 9 8 1 0
13
1 1 4 5 1 4 1 9 1 9 8 1 0
8
1 2 3 9 0 7 3 8
7
1 2 3 9 7 3 8
-1
```
## 提示

### 样例解释

我有一个绝妙的解释，可惜这里写不下。

### 数据范围

$id$ 为 $\text{subtask}$ 编号。

|$id$|特殊性质|分数|$id$|特殊性质|分数|
|-:|-:|-:|-:|-:|-:|
|$1$|$c\le10$|$3$|$6$|$c\le1\times 10^6$|$15$|
|$2$|$c\le30$|$6$|$7$|$T\le 10$|$5$|
|$3$|$c\le500$|$6$|$8$|$T\le 5\times 10^4$|$15$|
|$4$|$c\le2\times 10^3$|$5$|$9$|$T\le 8\times 10^4$|$10$|
|$5$|$c\le1\times 10^5$|$20$|$10$||$15$|

对于 $100\%$ 的数据，$T\le 10^5$，$0\le c\le 2\times 10^9$。

### 提示

由于部分 STL 的常数较大，如果认为你的时间复杂度没有问题却 TLE，请不要使用 STL。

请注意输出效率，这里提供一种快写模板（请不要用以下代码输出负数）：

```cpp
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
```


---

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
title: "[NOI2013] 树的计数"
layout: "post"
diff: 省选/NOI-
pid: P1232
tag: ['递推', '2013', 'NOI', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [NOI2013] 树的计数
## 题目描述

我们知道一棵有根树可以进行深度优先遍历（DFS）以及广度优先遍历（BFS）来生成这棵树的 DFS 序以及 BFS 序。两棵不同的树的 DFS 序有可能相同，并且它们的 BFS 序也有可能相同，例如下面两棵树的 DFS 序都是 `1 2 4 5 3`，BFS 序都是 `1 2 3 4 5`。

![](https://cdn.luogu.com.cn/upload/image_hosting/kagmha60.png)

现给定一个 DFS 序和 BFS 序，我们想要知道，符合条件的有根树中，树的高度的平均值。即，假如共有 $K$ 棵不同的有根树具有这组 DFS 序和 BFS 序，且他们的高度分别是 $h_1, h_2, \ldots, h_K$，那么请你输出：

$$
\frac{h_1+h_2+\ldots+h_K}K
$$
## 输入格式

第一行包含 $1$ 个正整数 $n$，表示树的节点个数。

第二行包含 $n$ 个正整数，是一个 $1 \ldots n$ 的排列，表示树的 DFS 序。

第三行包含 $n$ 个正整数，是一个 $1 \ldots n$ 的排列，表示树的 BFS 序。

输入保证至少存在一棵树符合给定的两个序列。
## 输出格式

输出 $1$ 个实数，四舍五入保留恰好三位小数，表示树高的平均值。
## 样例

### 样例输入 #1
```
5 
1 2 4 5 3 
1 2 3 4 5

```
### 样例输出 #1
```
3.500

```
## 提示

如果输出文件的答案与标准输出的差不超过 $0.001$，则将获得该测试点上的分数，否则不得分。

### 数据范围

- 对于 $20\%$ 的测试数据，满足：$n \le 10$；
- 对于 $40\%$ 的测试数据，满足：$n \le 100$；
- 对于 $85\%$ 的测试数据，满足：$n \le 2 \times 10^3$；
- 对于 $100\%$ 的测试数据，满足：$2 \le n \le 2 \times 10^5$。


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
title: "拼字游戏"
layout: "post"
diff: 省选/NOI-
pid: P1277
tag: ['搜索', 'Special Judge']
---
# 拼字游戏
## 题目描述

有一个未知的 $4 \times 4$ 的拼盘 $M$，它的每个元素都是正整数。给出 $4$ 行元素的总和，$4$ 列元素的总和以及两条对角线元素总和。另外还给出了拼盘中任意 $4$ 个位置的元素值，它们的位置在输入文件中给定。

编写一个程序求出拼盘中另外 $12$ 个位置的正整数的值，要求这些元素的行之和，列之和以及对角线之和与输入文件中给定的值相一致。

## 输入格式

输入文件包含用空格隔开的 $22$ 个正整数。

前四个数字分别表示四行中每一行元素的总和，接下来的 $4$ 个数字分别表示 $4$ 列中每列元素的总和。接下来的数字表示主对角线元素的总和，即 $M(0, 0)+M(1,1)+M(2, 2)+M(3, 3)$。然后的数字（第 $10$ 个数字）表示逆对角线上元数之和，即 $M(0, 3)+M(1, 2)+M(2, 1)+M(3, 0)$ 。剩下的部分还包含 $12$ 个数字，被分成三个一组的形式 $i,j,k$。表示 $M(i,j)=k$。

你可以假设任何行对角线或列之和不会超过 $300$。另外还可假设对于给定的输入文件总是存在解决方案。

## 输出格式

输出文件应包含按 $4 \times 4$ 的形式输出的 $16$ 个数字，同一行的四个数字用一个空个隔开。注意：对于给定的输入文件，可能有一个以上可能的解决方案。任何一个方案都是可接受的。

## 样例

### 样例输入 #1
```
130 120 172 140 157 93 144 168 66 195 0 1 15 1 3 49 2 2 16 3 0 33
```
### 样例输出 #1
```
22 15 28 65
49 1 21 49
53 76 16 27
33 1 79 27

```
## 提示

- 对于 $10\%$ 的数据，任何行，列或对角线之和不会超过 $20$；
- 对于 $30\%$ 的数据，任何行，列或对角线之和不会超过 $80$；
- 对于 $60\%$ 的数据，任何行，列或对角线之和不会超过 $200$；
- 对于 $100\%$ 的数据，任何行，列或对角线之和不会超过 $300$。

感谢 @Jomoo 的贡献。


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
title: "[GCJ 2019 Finals] Go To Considered Helpful"
layout: "post"
diff: 省选/NOI-
pid: P13128
tag: ['动态规划 DP', '2019', '广度优先搜索 BFS', 'Google Code Jam']
---
# [GCJ 2019 Finals] Go To Considered Helpful
## 题目描述

Marlin is a fish who lost his son and is trying to find him. Fortunately, he ran into Cynthia, a turtle, as she swam around with her brothers, Wally and Seymour. Cynthia knows exactly where Marlin needs to go, and she can be very precise in giving directions. While Marlin is smart and can follow them perfectly, keeping track of a long list of directions can be problematic. Cynthia needs to find a way to make the list of directions short.

Marlin lives in a matrix of $\mathbf{R}$ rows and $\mathbf{C}$ columns. Some cells of the matrix are dangerous and cannot be entered. Marlin and his son are currently in different non-dangerous cells. Marlin's son never moves to a different cell. Cynthia decided to give Marlin directions in the form of a program consisting of a list of instructions, each on a single line. Each instruction is of one of 5 types:

* $\mathbf{N}$: move one cell North (up),
* $\mathbf{S}$: move one cell South (down),
* $\mathbf{W}$: move one cell West (left),
* $\mathbf{E}$: move one cell East (right), and
* $\mathbf{G}(\mathbf{i})$: jump to the i-th line of the instruction list (counting starting from 1).

After executing a line with any of the first 4 instructions, Marlin jumps to the next line on the list if there is one. If there is no next line, Marlin just stands still forever.

For example, if Marlin were following the program

1. $\mathbf{N}$
2. $\mathbf{E}$
3. $\mathbf{G}(6)$
4. $\mathbf{S}$
5. $\mathbf{G}(1)$
6. $\mathbf{W}$
7. $\mathbf{G}(4)$

he would move North (line 1), then East (2), then jump to line 6 without physically moving (3), then move West (6), then jump to line 4 (7), then move South (4), then jump to line 1 (5), then move North (1), etc.

If at any point Marlin and his son are at the same cell, they will be reunited and Marlin will no longer follow any instructions. Cynthia the turtle wants to find out the smallest number of lines in a program that would get Marlin to the same cell as his son, without him ever going into a dangerous cell or moving outside of the matrix boundaries. All $\mathbf{G}$ instructions must jump to existing lines in the program.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing $\mathbf{R}$ and $\mathbf{C}$, the number of rows and columns in the matrix. Then, $\mathbf{R}$ lines follow containing a string of $\mathbf{C}$ characters each. The $j$-th character of the $i$-th of these lines $\mathbf{A}_{ij}$ represents the cell in the $i$-th row and $j$-th column of the matrix. The character is $\#$ if the cell is dangerous, an uppercase $\mathbf{M}$ if the cell is the one Marlin is currently at, an uppercase $\mathbf{N}$ if the cell is the one Marlin's son is currently at and $\mathbf{.}$ if the cell is an unoccupied non-dangerous cell.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is $\text{IMPOSSIBLE}$ if there is no program that would get Marlin to his son under the conditions explained above, or the smallest number of instructions in such a program.
## 样例

### 样例输入 #1
```
5
2 5
N...#
....M
2 5
N#...
...#M
5 5
N..##
#.###
#...#
##.##
##..M
5 5
..N##
#.###
#...#
##.##
##..M
3 3
#M#
###
#N#
```
### 样例输出 #1
```
Case #1: 4
Case #2: 7
Case #3: 5
Case #4: 6
Case #5: IMPOSSIBLE
```
## 提示

**Sample Explanation**

Below are some shortest programs for each of the possible sample case.

- Sample Case #1:
```
1: W
2: N
3: S
4: G(1)
```
or
```
1: W
2: N
3: W
4: G(3)
```

- Sample Case #2:
```
1: N
2: W
3: W
4: S
5: W
6: W
7: N
```
- Sample Case #3:
```
1: W
2: W
3: N
4: N
5: G(2)
```
- Sample Case #4:
```
1: W
2: W
3: N
4: N
5: E
6: G(1)
```

**Sample Explanation**

- $1 \leq \mathbf{T} \leq 100$.
- $\mathbf{A}_{ij}$ is either $\#$, $\mathbf{.}$, uppercase $\mathbf{M}$ or uppercase $\mathbf{N}$, for all $i$ and $j$.
- $\mathbf{A}_{ij} = \mathbf{M}$ for exactly one pair of $i$ and $j$.
- $\mathbf{A}_{ij} = \mathbf{N}$ for exactly one pair of $i$ and $j$.

**Test set 1 (19 Pts, Visible)**

- Time limit: 30 seconds.
- $1 \leq \mathbf{R} \leq 10$.
- $1 \leq \mathbf{C} \leq 10$.

**Test set 2 (30 Pts, Hidden)**

- Time limit: 120 seconds.
- For at most 10 test cases:
  - $1 \leq \mathbf{R} \leq 100$.
  - $1 \leq \mathbf{C} \leq 100$.
- For the remaining test cases:
  - $1 \leq \mathbf{R} \leq 50$.
  - $1 \leq \mathbf{C} \leq 50$.


---

---
title: "[GCJ 2017 #2] Shoot the Turrets"
layout: "post"
diff: 省选/NOI-
pid: P13174
tag: ['2017', 'Special Judge', '广度优先搜索 BFS', '二分图', 'Google Code Jam']
---
# [GCJ 2017 #2] Shoot the Turrets
## 题目描述

The fight to free the city from extraterrestrial invaders is over! People are happy that love and peace have returned.

The city is represented as a grid with $R$ rows and $C$ columns. Some cells on the grid are buildings (through which nobody can see, nobody can shoot, and nobody can walk), and some are streets (through which everybody can see, shoot and walk). Unfortunately, during the war, the now-defeated invaders set up automatic security turrets in the city. These turrets are only in streets (not in buildings). They pose a threat to the citizens, but fortunately, there are also some soldiers on the streets (not in buildings). Initially, no soldier is in the same place as a turret.

The invader turrets do not move. They are small, so they don't block sight and shooting. A soldier cannot walk through an active turret's cell, but can walk through it once it is destroyed. A turret can only see soldiers in the cells for which it has a horizontal or vertical line of sight. If a soldier enters such a cell, the turret does not fire. If a soldier attempts to exit such a cell (after entering it, or after starting in that cell), the turret fires. Luckily, a soldier can still shoot from that cell, and the turret will not detect that as movement. It means that none of your soldiers will actually die, because in the worst case they can always wait, motionless, for help (perhaps for a long time). Maybe you will have a chance to rescue them later.

Each soldier can make a total of $M$ unit moves. Each of these moves must be one cell in a horizontal or vertical direction. Soldiers can walk through each other and do not block the lines of sight of other soldiers or turrets. Each soldier also has one bullet. If a soldier has a turret in her horizontal or vertical line of sight, the soldier can shoot and destroy it. Each shot can only destroy one turret, but the soldiers are such excellent shooters that they can even shoot past one or several turrets or soldiers in their line of sight and hit another turret farther away!

You are given a map (with the soldier and turret positions marked). What is the largest number of turrets that the soldiers can destroy?
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case begins with a line containing the integer $C$ (the width of the map), $R$ (the height of the map) and $M$ (the number of unit moves each soldier can make). The next $R$ lines contain $C$ characters each, with . representing a street, # representing a building, S representing a soldier and T representing a turret.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the maximum number of turrets that it is possible to destroy. Then $y$ lines should follow: each should contain two integers $s_i$ and $t_i$ denoting that the $i$th thing that happens should be soldier $s_i$ destroying turret $t_i$ (you don't need to specify exactly how the soldier has to move). If multiple valid strategies exist, you may output any one of them.

Soldiers are numbered from 1, reading from left to right along the top row, then left to right along the next row down from the top, and so on, from top to bottom.
## 样例

### 样例输入 #1
```
4
2 2 1
#S
T.
2 6 4
.T
.T
.T
S#
S#
S#
5 5 4
.....
SS#.T
SS#TT
SS#.T
.....
3 3 8
S.#
.#.
#.T
```
### 样例输出 #1
```
Case #1: 1
1 1
Case #2: 3
3 3
1 1
2 2
Case #3: 3
1 2
2 1
6 3
Case #4: 0
```
## 提示

**Sample Explanation**

In Case #2, one of the possible solutions is to move soldier $3$ up three cells and shoot turret $3$. Then soldier $1$ can move up one cell and right one cell (to where turret $3$ was) and shoot past turret $2$ to destroy turret $1$. Finally, soldier $2$ can move up three cells and shoot turret $2$.

In Case #3, soldier $1$ can move up one cell, then right three cells and shoot turret $2$. Then soldier $2$ can move up one cell, then right three cells and shoot turret $1$. Finally, soldier $6$ can move down one cell, then right three cells and shoot turret $3$. Other soldiers have insufficient move range to shoot any other turrets.

In Case #4, the soldier cannot move to within the same row or column as the turret, so the turret cannot be destroyed.

**Limits**

- $1 \leq T \leq 100$.
- $0 \leq M < C \times R$.

**Small dataset (Test Set 1 - Visible)**

- Time limit: ~~30~~ 7.5 seconds.
- $1 \leq C \leq 30$.
- $1 \leq R \leq 30$.
- The number of S symbols is between $1$ and $10$.
- The number of T symbols is between $1$ and $10$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~60~~ 15 seconds.
- $1 \leq C \leq 100$.
- $1 \leq R \leq 100$.
- The number of S symbols is between $1$ and $100$.
- The number of T symbols is between $1$ and $100$.


---

---
title: "[GCJ 2014 Finals] Paradox Sort"
layout: "post"
diff: 省选/NOI-
pid: P13267
tag: ['贪心', '2014', '深度优先搜索 DFS', 'Google Code Jam']
---
# [GCJ 2014 Finals] Paradox Sort
## 题目描述

Vlad likes candies. You have a bag of different candies, and you're going to let Vlad keep one of them. You choose an order for the candies, then give them to Vlad one at a time. For each candy Vlad receives (after the first one), he compares the candy he had to the one he was just given, keeps the one he likes more, and throws the other one away.

You would expect that for any order you choose, Vlad will always end up with his favorite candy. But this is not the case! He does not necessarily have a favorite candy. We know for any pair of candies which one he will prefer, but his choices do not necessarily correspond to a simple ranking. He may choose Orange when offered Orange and Lemon, Banana when offered Orange and Banana, and Lemon when offered Lemon and Banana!

There is a particular candy you want Vlad to end up with. Given Vlad's preferences for each pair of candies, determine if there is an ordering such that Vlad will end up with the right candy. If there is, find the lexicographically-smallest such ordering.
## 输入格式

The first line of the input gives the number of test cases, $\mathrm{T}$. $\mathrm{T}$ test cases follow. Each test case will start with a line containing the integers $\mathrm{N}$ and $\mathrm{A}$, separated by a space. $\mathrm{N}$ is the number of candies, and $\mathrm{A}$ is the number of the candy we want Vlad to finish with. The candies are numbered from 0 to $\mathrm{N}-1$. The next $\mathrm{N}$ lines each contains $\mathrm{N}$ characters. Character $\mathrm{j}$ of line $\mathrm{i}$ will be 'Y' if Vlad prefers candy $\mathrm{i}$ to candy $\mathrm{j}$, 'N' if Vlad prefers candy $\mathrm{j}$ to candy $\mathrm{i}$, and '-' if $\mathrm{i}=\mathrm{j}$. Note that if $\mathrm{i} \neq \mathrm{j}$, the $\mathrm{j}$ th character of the $\mathrm{i}$ th row must be different from the $\mathrm{i}$ th character of the $\mathrm{j}$ th row.

## 输出格式

For each test case output "Case #x: ", where $\mathrm{x}$ is the case number, followed by either "IMPOSSIBLE" or a space-separated list of the lexicographically-smallest ordering of candies that leaves Vlad with $\mathrm{A}$.
## 样例

### 样例输入 #1
```
3
2 0
-Y
N-
2 0
-N
Y-
4 3
-YNN
N-YY
YN-Y
YNN-
```
### 样例输出 #1
```
Case #1: 0 1
Case #2: IMPOSSIBLE
Case #3: 1 2 0 3
```
## 提示

**Limits**

- $1 \leqslant \mathrm{T} \leqslant 100$.

**Small dataset(4 Pts)**

- Time limit: ~~60~~ 3 seconds.
- $1 \leqslant \mathrm{N} \leqslant 10$.

**Large dataset(28 Pts)**

- Time limit: ~~120~~ 5 seconds.
- $1 \leqslant \mathrm{N} \leqslant 100$.


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
title: "拆分数列"
layout: "post"
diff: 省选/NOI-
pid: P1415
tag: ['字符串', '动态规划 DP', '搜索', '洛谷原创']
---
# 拆分数列
## 题目描述

给出一列数字，需要你添加任意多个逗号将其拆成若干个严格递增的数。如果有多组解，则输出使得最后一个数最小的同时，字典序最大的解（即先要满足最后一个数最小；如果有多组解，则使得第一个数尽量大；如果仍有多组解，则使得第二个数尽量大，依次类推……）。

## 输入格式

共一行，为初始的数字。

## 输出格式

共一行，为拆分之后的数列。每个数之间用逗号分隔。行尾无逗号。

## 样例

### 样例输入 #1
```
3456
```
### 样例输出 #1
```
3,4,5,6
```
### 样例输入 #2
```
3526
```
### 样例输出 #2
```
3,5,26
```
### 样例输入 #3
```
3546
```
### 样例输出 #3
```
35,46
```
### 样例输入 #4
```
0001
```
### 样例输出 #4
```
0001
```
### 样例输入 #5
```
100000101
```
### 样例输出 #5
```
100,000101
```
## 提示


### 数据范围及约定

记输入的字符串的长度为 $l$。

- 对于 $10\%$ 的数据，$l \le 5$；
- 对于 $30\%$ 的数据，$l \le 15$；
- 对于 $50\%$ 的数据，$l \le 50$；
- 对于 $100\%$ 的数据，$l \le 500$。

### 题目来源

lzn 改编


---

---
title: "[NOI2008] 假面舞会"
layout: "post"
diff: 省选/NOI-
pid: P1477
tag: ['图论', '2008', 'NOI', '深度优先搜索 DFS', '最大公约数 gcd']
---
# [NOI2008] 假面舞会
## 题目描述

一年一度的假面舞会又开始了，栋栋也兴致勃勃的参加了今年的舞会。

今年的面具都是主办方特别定制的。每个参加舞会的人都可以在入场时选择一个自己喜欢的面具。每个面具都有一个编号，主办方会把此编号告诉拿该面具的人。

为了使舞会更有神秘感，主办方把面具分为 $k$（$k\geq 3$）类，并使用特殊的技术将每个面具的编号标在了面具上，只有戴第 $i$ 类面具的人才能看到戴第 $i+1$  类面具的人的编号，戴第 $k$ 类面具的人能看到戴第 $1$ 类面具的人的编号。

参加舞会的人并不知道有多少类面具，但是栋栋对此却特别好奇，他想自己算出有多少类面具，于是他开始在人群中收集信息。

栋栋收集的信息都是戴第几号面具的人看到了第几号面具的编号。如戴第 $2$ 号面具的人看到了第 $5$ 号面具的编号。栋栋自己也会看到一些编号，他也会根据自己的面具编号把信息补充进去。

由于并不是每个人都能记住自己所看到的全部编号，因此，栋栋收集的信息不能保证其完整性。现在请你计算，按照栋栋目前得到的信息，至多和至少有多少类面具。由于主办方已经声明了 $k\geq 3$，所以你必须将这条信息也考虑进去。

## 输入格式

第一行包含两个整数 $n, m$，用一个空格分隔，$n$ 表示主办方总共准备了多少个面具，$m$ 表示栋栋收集了多少条信息。接下来 $m$ 行，每行为两个用空格分开的整数 $a, b$，表示戴第 $a$ 号面具的人看到了第 $b$ 号面具的编号。相同的数对 $a, b$ 在输入文件中可能出现多次。

## 输出格式

包含两个数，第一个数为最大可能的面具类数，第二个数为最小可能的面具类数。如果无法将所有的面具分为至少 $3$ 类，使得这些信息都满足，则认为栋栋收集的信息有错误，输出两个 `-1`。

## 样例

### 样例输入 #1
```
6 5
1 2
2 3
3 4
4 1
3 5
```
### 样例输出 #1
```
4 4

```
### 样例输入 #2
```
3 3
1 2
2 1
2 3
```
### 样例输出 #2
```
-1 -1

```
## 提示

- 对于 $50\%$ 的数据，满足 $n \leq 300$，$m \leq 10^3$；
- 对于 $100\%$ 的数据，满足 $n \leq 10^5$，$m \leq 10^6$。



---

---
title: "[USACO07FEB] Lilypad Pond G"
layout: "post"
diff: 省选/NOI-
pid: P1606
tag: ['图论', '2007', 'USACO', '广度优先搜索 BFS', '最短路']
---
# [USACO07FEB] Lilypad Pond G
## 题目描述

FJ has installed a beautiful pond for his cows' aesthetic enjoyment and exercise.

The rectangular pond has been partitioned into square cells of M rows and N columns (1 ≤ M ≤ 30; 1 ≤ N ≤ 30). Some of the cells have astonishingly sturdy lilypads; others have rocks; the remainder are just beautiful, cool, blue water.

Bessie is practicing her ballet moves by jumping from one lilypad to another and is currently located at one of the lilypads. She wants to travel to another lilypad in the pond by jumping from one lilypad to another.

Surprising only to the uninitiated, Bessie's jumps between lilypads always appear as a chess-knight's move: one move in one direction and then two more in the orthogonal direction (or perhaps two in one direction and then one in the orthogonal direction).

Farmer John is observing Bessie's ballet drill and realizes that sometimes she might not be able to jump to her destination lilypad because intermediary lilypads are missing.

Ever thrifty, he wants to place additional lilypads so she can complete her quest (perhaps quickly, perhaps by using a large number of intermediate lilypads). Of course, lilypads cannot be placed where rocks already intrude on a cell.

Help Farmer John determine the minimum number of additional lilypads he has to place, and in how many ways he can place that minimum number.

## 输入格式

第一行两个用空格分开的整数 $M$ 和 $N$。

第二行到 $M+1$ 行，第 $i+1$ 行有 $N$ 个用空格分开的整数，描述了池塘第 $i$ 行的状态：

- $0$ 为水，$1$ 为莲花，$2$ 为岩石，$3$ 为贝西所在的起点，$4$ 为贝西想去的终点。
## 输出格式

第一行一个整数，需要增加的最少莲花数；如果无解，输出 $-1$。

第二行输出放置这些莲花的方案数量，保证这个数字可用一个 $64$ 位的有符号整数，表示。

特别地，如果第一行是 $-1$，不要输出第二行。
## 样例

### 样例输入 #1
```
4 5
1 0 0 0 0
3 0 0 0 0
0 0 2 0 0
0 0 0 4 0

```
### 样例输出 #1
```
2
3

```
## 提示

### 样例解释

池塘分成四行五列，贝西的起点在第二行第一列，想去的终点在第四行第四列，池塘里一共有三朵莲花和一块石头。

最少需要两朵莲花，有三种方式可以放置，

如下 $\verb!X!$ 所示：

$$\begin{bmatrix}
\verb!10000! \\
\verb!30X00! \\
\verb!00200! \\
\verb!0X040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!30000! \\
\verb!0X200! \\
\verb!00040! \\
\end{bmatrix},\begin{bmatrix}
\verb!10X00! \\
\verb!3000X! \\
\verb!00200! \\
\verb!00040! \\
\end{bmatrix}
$$
## 题目翻译

为了让奶牛们娱乐和锻炼，农夫约翰建造了一个美丽的池塘。这个长方形的池子被分成了 $M$ 行 $N$ 列个方格（$1 \le M,N \le 30$）。一些格子是坚固得令人惊讶的莲花，还有一些格子是岩石，其余的只是美丽、纯净、湛蓝的水。

贝西正在练习芭蕾舞，她站在一朵莲花上，想跳到另一朵莲花上去，她只能从一朵莲花跳到另一朵莲花上，既不能跳到水里，也不能跳到岩石上。

贝西的舞步很像象棋中的马步：每次总是先横向移动一格，再纵向移动两格，或先纵向移动两格，再横向移动一格。最多时，贝西会有八个移动方向可供选择。

约翰一直在观看贝西的芭蕾练习，发现她有时候不能跳到终点，因为中间缺了一些荷叶。于是他想要添加几朵莲花来帮助贝西完成任务。一贯节俭的约翰只想添加最少数量的莲花。当然，莲花不能放在石头上。

请帮助约翰确定必须要添加的莲花的最少数量，以及有多少种放置这些莲花的方法。


---

---
title: "埃及分数"
layout: "post"
diff: 省选/NOI-
pid: P1763
tag: ['搜索', 'Special Judge', '迭代加深搜索']
---
# 埃及分数
## 题目描述

**来源：BIO 1997 Round 1 [Question 3](http://www.olympiad.org.uk/papers/1997/bio/bio97r1q3.html)**

在古埃及，人们使用单位分数的和（形如 $\dfrac{1}{a}$ 的，$a$ 是自然数）表示一切有理数。如：$\dfrac{2}{3} = \dfrac{1}{2} + \dfrac{1}{6}$，但不允许 $\dfrac{2}{3} = \dfrac{1}{3} + \dfrac{1}{3}$，因为加数中有相同的。对于一个分数 $\dfrac{a}{b}$，表示方法有很多种，但是哪种最好呢？首先，加数少的比加数多的好，其次，加数个数相同的，最小的分数越大越好。如：
$$
\begin{aligned}
\frac{19}{45} &= \frac{1}{3} + \frac{1}{12} + \frac{1}{180}\\
\frac{19}{45} &= \frac{1}{3} + \frac{1}{15} + \frac{1}{45}\\
\frac{19}{45} &= \frac{1}{3} + \frac{1}{18} + \frac{1}{30}\\
\frac{19}{45} &= \frac{1}{4} + \frac{1}{6} + \frac{1}{180}\\
\frac{19}{45} &= \frac{1}{5} + \frac{1}{6} + \frac{1}{18}\\
\end{aligned}
$$
最好的是最后一种，因为 $\dfrac{1}{18}$ 比 $\dfrac{1}{180}, \dfrac{1}{45}, \dfrac{1}{30}$ 都大。  
注意，可能有多个最优解。如：
$$
\begin{aligned}
\frac{59}{211} &= \frac{1}{4} + \frac{1}{36} + \frac{1}{633} + \frac{1}{3798}\\
\frac{59}{211} &= \frac{1}{6} + \frac{1}{9} + \frac{1}{633} + \frac{1}{3798}\\
\end{aligned}
$$
由于方法一与方法二中，最小的分数相同，因此二者均是最优解。

给出 $a,b$，编程计算最好的表达方式。保证最优解满足：最小的分数 $\ge \cfrac{1}{10^7}$。 

## 输入格式

一行两个整数，分别为 $a$ 和 $b$ 的值。
## 输出格式

输出若干个数，自小到大排列，依次是单位分数的分母。
## 样例

### 样例输入 #1
```
19 45
```
### 样例输出 #1
```
5 6 18
```
## 提示

$1 \lt a \lt b \lt 1000$


---

---
title: "魔法指纹"
layout: "post"
diff: 省选/NOI-
pid: P1822
tag: ['模拟', '广度优先搜索 BFS']
---
# 魔法指纹
## 题目描述

对于任意一个至少两位的正整数 $n$，按如下方式定义 $\mathrm{magic}(n)$：将 $n$ 按十进制顺序写下来，依次对相邻两个数写下差的绝对值。这样，得到了一个新数，去掉前导 $0$，则定义为 $\mathrm{magic}(n)$。特别地，若 $n$ 为一位数，则 $mag_ic(n)=n$。

例如：$\mathrm{magic}(5913)=482$，$\mathrm{magic}(1198)=081=81$，$\mathrm{magic}(666)=00=0$。

对任意一个数 $n$，反复迭代计算 $\mathrm{magic}$ 值直到 $n$ 变成一个一位数，可以得到一个序列 $[n,\mathrm{magic}(n),\mathrm{magic}(\mathrm{magic}(n)),\cdots]$。最后的这个值称为数 $n$ 的 $\mathrm{magic}$ 指纹。

例如，对于 $n=5913$，我们得到序列：$[5913,482,46,2]$。所以 $5913$ 的 $\mathrm{magic}$ 指纹为 $2$。

若一个数的 $\mathrm{magic}$ 指纹为 $7$，则认为这个数是个幸运数。

现在，给定 $A,B$，计算出 $[A,B]$ 中有多少个数是幸运数。
## 输入格式

输入两行，每行一个数。第一行是 $A$，第二行表示 $B$。

## 输出格式

输出 $[A,B]$ 中有多少个数是幸运数。

## 样例

### 样例输入 #1
```
1
9
```
### 样例输出 #1
```
1

```
## 提示

### 数据范围及约定

- 对于 $30\%$ 数据，$B \le 10^4$。
- 对于 $100\%$ 数据，$0<A \le B \le 10^9$。



---

---
title: "[NOI2010] 航空管制"
layout: "post"
diff: 省选/NOI-
pid: P1954
tag: ['贪心', '2010', 'NOI', 'Special Judge', '深度优先搜索 DFS', '优先队列']
---
# [NOI2010] 航空管制
## 题目描述

世博期间，上海的航空客运量大大超过了平时，随之而来的航空管制也频频发生。最近，小 X 就因为航空管制，连续两次在机场被延误超过了两小时。对此，小 X 表示很不满意。

在这次来烟台的路上，小 X 不幸又一次碰上了航空管制。于是小 X 开始思考关于航空管制的问题。

假设目前被延误航班共有 $n$ 个，编号为 $1$ 至 $n$。机场只有一条起飞跑道，所有的航班需按某个顺序依次起飞（称这个顺序为起飞序列）。定义一个航班的起飞序号为该航班在起飞序列中的位置，即是第几个起飞的航班。

起飞序列还存在两类限制条件：

- 第一类（最晚起飞时间限制）：编号为 $i$ 的航班起飞序号不得超过 $k_i$。

- 第二类（相对起飞顺序限制）：存在一些相对起飞顺序限制 $(a,b)$，表示航班 $a$ 的起飞时间必须早于航班 $b$，即航班 $a$ 的起飞序号必须小于航班 $b$ 的起飞序号。

小 X 思考的第一个问题是，若给定以上两类限制条件，是否可以计算出一个可行的起飞序列。第二个问题则是，在考虑两类限制条件的情况下，如何求出每个航班在所有可行的起飞序列中的最小起飞序号。

## 输入格式

第一行包含两个正整数 $n$ 和 $m$，$n$ 表示航班数目，$m$ 表示第二类限制条件（相对起飞顺序限制）的数目。

第二行包含 $n$ 个正整数 $k_1,k_2,\cdots,k_n$。

接下来 $m$ 行，每行两个正整数 $a$ 和 $b$，表示一对相对起飞顺序限制 $(a,b)$，其中 $1\leq a,b\leq n$，表示航班 $a$ 必须先于航班 $b$ 起飞。
## 输出格式

第一行包含 $n$ 个整数，表示一个可行的起飞序列，相邻两个整数用空格分隔。输入数据保证至少存在一个可行的起飞序列。如果存在多个可行的方案，输出任意一个即可。

第二行包含 $n$ 个整数 $t_1,t_2,\cdots,t_n$，其中 $t_i$ 表示航班 $i$ 可能的最小起飞序号，相邻两个整数用空格分隔。
## 样例

### 样例输入 #1
```
5 5
4 5 2 5 4
1 2
3 2
5 1
3 4
3 1

```
### 样例输出 #1
```
3 5 1 4 2
3 4 1 2 1

```
### 样例输入 #2
```
5 0
3 3 3 5 5

```
### 样例输出 #2
```
3 2 1 5 4
1 1 1 4 4

```
## 提示

### 样例解释

在样例 $1$ 中：

起飞序列 $3\ 5\ 1\ 4\ 2$ 满足了所有的限制条件，所有满足条件的起飞序列有：

$$
\begin{aligned}
3\ 4\ 5\ 1\ 2\\
3\ 5\ 1\ 2\ 4\\
3\ 5\ 1\ 4\ 2\\
3\ 5\ 4\ 1\ 2\\
5\ 3\ 1\ 2\ 4\\
5\ 3\ 1\ 4\ 2\\
5\ 3\ 4\ 1\ 2
\end{aligned}
$$

由于存在 $(5,1)$ 和 $(3,1)$ 两个限制，航班 $1$ 只能安排在航班 $5$ 和 $3$ 之后，故最早起飞时间为 $3$，其他航班类似。

在样例 $2$ 中：

虽然航班 $4,5$ 没有相对起飞顺序限制，但是由于航班 $1,2,3$ 都必须安排在前 $3$ 个起飞，所以 $4,5$ 最早只能安排在第 $4$ 个起飞。

### 数据范围

对于 $30\%$ 数据：$n\leq 10$。

对于 $60\%$ 数据：$n\leq 500$。

对于 $100\%$ 数据：$n\leq 2\times 10^3,m\leq 10^4$。

感谢 @FlierKing 提供 spj



---

---
title: "[NOIP 2013 提高组] 华容道"
layout: "post"
diff: 省选/NOI-
pid: P1979
tag: ['搜索', '图论', '2013', 'NOIP 提高组']
---
# [NOIP 2013 提高组] 华容道
## 题目背景

NOIP2013 提高组 D2T3
## 题目描述

`小 B` 最近迷上了华容道，可是他总是要花很长的时间才能完成一次。于是，他想到用编程来完成华容道：给定一种局面， 华容道是否根本就无法完成，如果能完成， 最少需要多少时间。

`小 B` 玩的华容道与经典的华容道游戏略有不同，游戏规则是这样的：

1.   在一个 $n \times m$ 棋盘上有 $ n \times m$ 个格子，其中有且只有一个格子是空白的，其余 $ n \times m-1$ 个格子上每个格子上有一个棋子，每个棋子的大小都是 $1 \times 1$ 的；
2.  有些棋子是固定的，有些棋子则是可以移动的；
3.  任何与空白的格子相邻（有公共的边）的格子上的棋子都可以移动到空白格子上。   

游戏的目的是把某个指定位置可以活动的棋子移动到目标位置。

给定一个棋盘，游戏可以玩 $q$ 次，当然，每次棋盘上固定的格子是不会变的， 但是棋盘上空白的格子的初始位置、 指定的可移动的棋子的初始位置和目标位置却可能不同。第 $i$ 次玩的时候， 空白的格子在第 $EX_i$ 行第 $EY_i$ 列，指定的可移动棋子的初始位置为第 $SX_i$ 行第 $SY_i$列，目标位置为第 $TX_i$ 行第 $TY_i$ 列。

假设 `小 B` 每秒钟能进行一次移动棋子的操作，而其他操作的时间都可以忽略不计。请你告诉 `小 B` 每一次游戏所需要的最少时间，或者告诉他不可能完成游戏。

## 输入格式

第一行有 $3$个整数，每两个整数之间用一个空格隔开，依次表示 $ n,m,q$；

接下来的 $n$ 行描述一个 $ n \times m$ 的棋盘，每行有 $ m $ 个整数，每两个整数之间用一个空格隔开，每个整数描述棋盘上一个格子的状态，$0$ 表示该格子上的棋子是固定的，$1$ 表示该格子上的棋子可以移动或者该格子是空白的。  

接下来的 $q$ 行，每行包含 $6$ 个整数依次是 $EX_i,EY_i,SX_i,SY_i,TX_i,TY_i$，每两个整数之间用一个空格隔开，表示每次游戏空白格子的位置，指定棋子的初始位置和目标位置。

## 输出格式

共 $ q$ 行，每行包含 $1$ 个整数，表示每次游戏所需要的最少时间，如果某次游戏无法完成目标则输出 $−1$。

## 样例

### 样例输入 #1
```
3 4 2
0 1 1 1
0 1 1 0
0 1 0 0
3 2 1 2 2 2
1 2 2 2 3 2
```
### 样例输出 #1
```
2
-1
```
## 提示

**输入输出样例说明**

棋盘上划叉的格子是固定的，红色格子是目标位置，圆圈表示棋子，其中绿色圆圈表示目标棋子。

1.   第一次游戏，空白格子的初始位置是 $(3,2)$（图中空白所示），游戏的目标是将初始位置在 $(1, 2)$ 上的棋子（图中绿色圆圈所代表的棋子）移动到目标位置 $(2, 2)$（图中红色的格子）上。

移动过程如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/n0q385tw.png)

2.  第二次游戏，空白格子的初始位置是 $(1, 2)$（图中空白所示），游戏的目标是将初始位置在 $(2, 2)$ 上的棋子（图中绿色圆圈所示）移动到目标位置  $(3, 2)$ 上。

![](https://cdn.luogu.com.cn/upload/image_hosting/aq9apos0.png)

要将指定块移入目标位置，必须先将空白块移入目标位置，空白块要移动到目标位置，必然是从位置 $(2,2)$ 上与当前图中目标位置上的棋子交换位置，之后能与空白块交换位置的只有当前图中目标位置上的那个棋子，因此目标棋子永远无法走到它的目标位置， 游戏无法完成。

**数据范围**

对于 $ 30\%$ 的数据，$1 ≤ n, m ≤ 10,q = 1$；

对于 $60\%$ 的数据，$1 ≤ n, m ≤ 30,q ≤ 10$；

对于 $100\%$ 的数据，$1 ≤ n, m ≤ 30,q ≤ 500$。



---

---
title: "[SDOI2009] 晨跑"
layout: "post"
diff: 省选/NOI-
pid: P2153
tag: ['2009', '各省省选', '山东', '深度优先搜索 DFS', '费用流']
---
# [SDOI2009] 晨跑
## 题目描述

Elaxia 最近迷恋上了空手道，他为自己设定了一套健身计划，比如俯卧撑、仰卧起坐等等，不过到目前为止，他坚持下来的只有晨跑。 

现在给出一张学校附近的地图，这张地图中包含 $N$ 个十字路口和 $M$ 条街道，Elaxia 只能从 一个十字路口跑向另外一个十字路口，街道之间只在十字路口处相交。

Elaxia 每天从寝室出发跑到学校，保证寝室编号为 $1$，学校编号为 $N$。 

Elaxia 的晨跑计划是按周期（包含若干天）进行的，由于他不喜欢走重复的路线，所以在一个周期内，每天的晨跑路线都不会相交（在十字路口处），寝室和学校不算十字路口。

Elaxia 耐力不太好，他希望在一个周期内跑的路程尽量短，但是又希望训练周期包含的天数尽量长。

除了练空手道，Elaxia 其他时间都花在了学习和找 MM 上面，所有他想请你帮忙为他设计 一套满足他要求的晨跑计划。

可能存在 $1\rightarrow n$ 的边。这种情况下，这条边只能走一次。
## 输入格式

第一行两个整数 $N,M$，表示十字路口数和街道数。 

接下来 $M$ 行，每行 $3$ 个数 $a,b,c$，表示路口 $a$ 和路口 $b$ 之间有条长度为 $c$ 的街道（单向）。
## 输出格式

一行两个整数，最长周期的天数和满足最长天数的条件下最短的路程度。
## 样例

### 样例输入 #1
```
7 10
1 2 1
1 3 1
2 4 1
3 4 1
4 5 1
4 6 1
2 5 5
3 6 6
5 7 1
6 7 1
```
### 样例输出 #1
```
2 11

```
## 提示

- 对于 $30\%$ 的数据，$N\le 20$，$M \le 120$。
- 对于 $100\%$ 的数据，$N\le 200$，$M\le 2\times 10^4,1\le c\le 10^4$。


---

---
title: "[HAOI2007] 覆盖问题"
layout: "post"
diff: 省选/NOI-
pid: P2218
tag: ['贪心', '2007', '河南', '二分', '各省省选', '深度优先搜索 DFS']
---
# [HAOI2007] 覆盖问题
## 题目描述

某人在山上种了 $N$ 棵小树苗。冬天来了，温度急速下降，小树苗脆弱得不堪一击，于是树主人想用一些塑料薄膜把这些小树遮盖起来，经过一番长久的思考，他决定 用 $3$ 个 $L \times L$ 的正方形塑料薄膜将小树遮起来。我们不妨将山建立一个平面直角坐标系，设第 $i$ 棵小树的坐标为 $(X_i,Y_i)$ ，$3$ 个 $L \times L$ 的正方形的边要求平行于坐标轴，一个点如果在正方形的边界上，也算作被覆盖。当然，我们希望塑料薄膜面积越小越好，即求 $L$ 最小值。
## 输入格式

接下来有 $N$ 行，第 $i+1$ 行有 $2$ 个整数 $X_i,Y_i$，表示第 $i$ 棵树的坐标，保证不会有 $2$ 个树的坐标相同。
## 输出格式

一行，输出最小的 $L$ 值。

## 样例

### 样例输入 #1
```
4

0 1

0 -1

1 0

-1 0


```
### 样例输出 #1
```
1
```
## 提示

对于 $100\%$ 的数据，$-1,000,000,000 \le X_i,Y_i \le 1,000,000,000。$

对于 $30\%$ 的数据，$N \le 100。$

对于 $50\%$ 的数据，$N \le 2000。$

对于 $100\%$ 的数据，$N \le 20000。$


---

---
title: "[HNOI2003] 多边形"
layout: "post"
diff: 省选/NOI-
pid: P2283
tag: ['模拟', '贪心', '2003', '各省省选', '湖南', '深度优先搜索 DFS']
---
# [HNOI2003] 多边形
## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1330.png)

## 输入格式

输入文件名：input.txt

输入文件第一行是一个自然数N，表示多边形的顶点数。N不超过1500。之后N行每行两个整数(用空格分开)，依次表示多边形的每个顶点的坐标。

## 输出格式

输出文件名：output.txt

输出文件仅1行，是阴影部分的面积，保留2位小数。

## 样例

### 样例输入 #1
```
5									

0 0

0 6

6 6

6 0

3 3


```
### 样例输出 #1
```
9.00
```


---

---
title: "[HNOI2006] 潘多拉的宝盒"
layout: "post"
diff: 省选/NOI-
pid: P2321
tag: ['搜索', '2006', '各省省选', '湖南', '广度优先搜索 BFS', 'Tarjan']
---
# [HNOI2006] 潘多拉的宝盒
## 题目描述

 ![](https://cdn.luogu.com.cn/upload/pic/1372.png) 

![](https://cdn.luogu.com.cn/upload/pic/1373.png)

## 输入格式

 ![](https://cdn.luogu.com.cn/upload/pic/1374.png) 

![](https://cdn.luogu.com.cn/upload/pic/1375.png)

## 输出格式

输出一行一个数$t$，表示最长升级序列的长度。

## 样例

### 样例输入 #1
```
4
1  1
0
0  0
2  1
0
1  1
0  0
3  1
0
1  1
2  2
0  0
4  1
0
1  1
2  2
3  3
0  0
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
3
1  1
0
0  0
3  1
0
0  1
2  0
1  2
9  1
0
0  1
2  3
4  5
6  7
8  0
1  2
3  4
5  6
7  8
```
### 样例输出 #2
```
3
```
## 提示

![](https://cdn.luogu.com.cn/upload/pic/1380.png)



---

---
title: "[NOI2011] 阿狸的打字机"
layout: "post"
diff: 省选/NOI-
pid: P2414
tag: ['字符串', '树形数据结构', '2011', 'NOI', '深度优先搜索 DFS', 'AC 自动机']
---
# [NOI2011] 阿狸的打字机
## 题目描述

阿狸喜欢收藏各种稀奇古怪的东西，最近他淘到一台老式的打字机。打字机上只有 $28$ 个按键，分别印有 $26$ 个小写英文字母和 `B`、`P` 两个字母。经阿狸研究发现，这个打字机是这样工作的：

* 输入小写字母，打字机的一个凹槽中会加入这个字母(这个字母加在凹槽的最后)。
* 按一下印有 `B` 的按键，打字机凹槽中最后一个字母会消失。
* 按一下印有 `P` 的按键，打字机会在纸上打印出凹槽中现有的所有字母并换行，但凹槽中的字母不会消失。

例如，阿狸输入 `aPaPBbP`，纸上被打印的字符如下：

```
a
aa
ab
```

我们把纸上打印出来的字符串从 $1$ 开始顺序编号，一直到 $n$。打字机有一个非常有趣的功能，在打字机中暗藏一个带数字的小键盘，在小键盘上输入两个数 $(x,y)$（其中 $1\leq x,y\leq n$），打字机会显示第 $x$ 个打印的字符串在第 $y$ 个打印的字符串中出现了多少次。

阿狸发现了这个功能以后很兴奋，他想写个程序完成同样的功能，你能帮助他么？

## 输入格式

输入的第一行包含一个字符串，按阿狸的输入顺序给出所有阿狸输入的字符。

第二行包含一个整数 $m$，表示询问个数。

接下来 $m$ 行描述所有由小键盘输入的询问。其中第 $i$ 行包含两个整数 $x, y$，表示第 $i$ 个询问为 $(x, y)$。

## 输出格式

输出 $m$ 行，其中第 $i$ 行包含一个整数，表示第 $i$ 个询问的答案。

## 样例

### 样例输入 #1
```
aPaPBbP
3
1 2
1 3
2 3
```
### 样例输出 #1
```
2
1
0
```
## 提示

### 数据范围

对于 $100\%$ 的数据，$1\leq n\leq 10^5$，$1\leq m\leq10^5$，第一行总长度 $\leq 10^5$。

|测试点|$n$ 的规模|$m$ 的规模|字符串长度|第一行长度|
|:-:|:-:|:-:|:-:|:-:|
|$1,2$|$1\leq n\leq 100$|$1\leq m\leq 10^3$| - |$\leq 100$|
|$3,4$|$1\leq n\leq 10^3$|$1\leq m\leq 10^4$|单个长度 $\leq 10^3$，总长度 $\leq 10^5$|$\leq 10^5$|
|$5\sim 7$|$1\leq n\leq 10^4$|$1\leq m\leq 10^5$|总长度 $\leq 10^5$|$\leq 10^5$|
|$8\sim 10$|$1\leq n\leq 10^5$|$1\leq m\leq 10^5$| - |$\leq 10^5$|




---

---
title: "[SDOI2010] 捉迷藏"
layout: "post"
diff: 省选/NOI-
pid: P2479
tag: ['搜索', '2010', '各省省选', '递归', '山东', '枚举']
---
# [SDOI2010] 捉迷藏
## 题目背景

iPig 在大肥猪学校刚上完了无聊的猪文课，天资聪慧的 iPig 被这门对他来说无比简单的课弄得非常寂寞，为了消除寂寞感，他决定和他的好朋友 giPi（鸡皮）玩一个更加寂寞的游戏——捉迷藏。但是，他们觉得，玩普通的捉迷藏没什么意思，还是不够寂寞，于是，他们决定玩寂寞无比的螃蟹版捉迷藏。

## 题目描述

螃蟹版捉迷藏，顾名思义，就是说他们在玩游戏的时候只能沿水平或垂直方向走。

一番寂寞的剪刀石头布后，他们决定 iPig 去捉 giPi。由于他们都很熟悉大肥猪学校的地形了，所以 giPi 只会躲在大肥猪学校内 $N$ 个隐秘地点之一，显然 iPig 也只会在那 $N$ 个地点内找 giPi。

游戏一开始，他们从这 $N$ 个隐秘地点之中选定一个地点，iPig 保持不动，然后 giPi 用 $30$ 秒的时间逃离现场（显然，giPi 不会呆在原地）。然后 iPig 会随机地去找 giPi，直到找到为止。

由于 iPig 很懒，所以他总是走最短的路径，而且，他选择起始点不是随便选的，他想找一个地点，使得该地点到（除了这个地点以外的）最远的地点和最近的地点的距离差最小。iPig现在想知道这个距离差最小是多少。

由于 iPig 现在手上没有电脑，所以不能编程解决这个如此简单的问题，所以他马上打了个电话，要求你帮他解决这个问题。iPig 告诉了你大肥猪学校的 $N$ 个隐秘地点的坐标，请你编程求出 iPig 的问题。
## 输入格式


第 $1$ 行：一个整数 $N$；

接下来 $N$ 行：每行两个整数 $X_i,Y_i$，表示第 $i$ 个地点的坐标。
## 输出格式

一个整数，为距离差的最小值。

## 样例

### 样例输入 #1
```
4
0 0
1 0
0 1
1 1

```
### 样例输出 #1
```
1
```
## 提示

$30\%$ 的数据中，$2\le N\le 10^3$；

$100\%$ 的数据中，$2\le N\le 10^5$，$0\le X_i,Y_i\le 10^9$。

数据保证点不重合。


---

---
title: "[SDOI2011] 迷宫探险"
layout: "post"
diff: 省选/NOI-
pid: P2489
tag: ['动态规划 DP', '搜索', '2011', '各省省选', '山东']
---
# [SDOI2011] 迷宫探险
## 题目背景

[](https://paste.ubuntu.com/p/H4h73F2h87/)
## 题目描述

这是一个单人游戏。

游戏开始时，玩家控制的人物出生在迷宫的某个位置，玩家的目标是控制人物走到迷宫的某个出口（出口可能有多个）。

迷宫里有 $k$ 类陷阱（用  `A`,`B`,`C`……表示，相同字母代表相同类型的陷阱），每类陷阱可能是有害的或无害的，而在游戏开始时玩家并不知道哪些陷阱是有害的，哪些是无害的。

同一类陷阱的状态相同，即用同一个字母标志的陷阱要么全部有害，要么全部无害，不会发生一部分有害而另一部分无害的情况。任何陷阱状态的组合都有一个发生概率，考虑下例：

当 $k=2$ 时，迷宫内共有两类陷阱，分别用 `A` 和 `B` 表示，陷阱状态的组合共有 $4$ 种：-
- `A` 是无害陷阱，`B` 是无害陷阱。
- `A` 是有害陷阱，`B` 是无害陷阱；
- `A` 是无害陷阱，`B` 是有害陷阱；
- `A` 是有害陷阱，`B` 是有害陷阱；

下列表格是一个合法的概率表格：

|  | `A` 是无害陷阱 | `A` 是有害陷阱 |
| -----------: | -----------: | -----------: |
| **`B` 是无害陷阱** | $36\%$ | $24\%$ |
| **`B` 是有害陷阱** | $24\%$ | $16\%$ |

当 $k=3$ 时，会有 $8$ 种不同的陷阱状态组合，如果我们依然坚持使用概率表格，那么这个表格将会是三维的（$2\times 2 \times 2$，每一维对应着一类陷阱）。当 $k\ge 3$ 时，这将使得题目难以描述。因此我们使用一个大小为 $2^{k}$ 的数组 $p$ 来描述每种情况发生的可能性，$p$ 的下标范围为 $0\sim 2^{k}-1$。

$p$ 是这样生成的：

对于每个可能的陷阱状态组合，考虑所有 $k$ 类陷阱，令 $1$ 表示某个陷阱有害，$0$ 表示某个陷阱无害，把 `A` 作为二进制数的第 $0$ 位（从右边开始计数），`B` 作为第 $1$ 位，`C` 作为第 $2$ 位……通过以上操作，我们可以得到一个 $k$ 位的二进制数，把它转化成十进制后，$2^{k}$ 种陷阱状态的组合将会与整数 $0\sim2^{k}-1$ 一一对应。

设 $S = \displaystyle\sum_{i=0}^{2^k-1} p_i$，则陷阱状态组合 $i$ 出现的概率为 $\dfrac {p_{i}} {S}$。

上述表格对应的一个合法数组 $p$ 为 $36,24,24,16$。

当然同一个概率表格可能会对应多个数组 $p$（事实上有无数个数组 $p$ 能够迎合表格数据），例如上述表格同时也对应着下面的数组 $p$：$72,48,48,32$。

玩家控制的人物初始情况下有 $H$ 点生命，当人物踏上某个陷阱时，如果这个陷阱是有害的，那么会损失 $1$ 点生命，否则这个陷阱是无害的，不损失生命。无论上述哪种情况发生，玩家会立刻得到这个陷阱的信息（有害或无害）。一旦生命小于等于 $0$，玩家控制的人物会立刻死亡。

迷宫可以看作 $m\times n$ 的方格地图，每个元素可能是：
- `.`：表示这是平地，可以通过；
- `#`：表示这是墙，不能通过；
- `A`，`B` ，`C`……：表示这是一个陷阱；
- `$`：表示这是起点，地图中有且仅有一个；
- `@`：表示这是终点，地图中可以有多个，也可以一个也没有。

人物可以向上下左右四个方向行走，不可以走对角线，也不可以走出地图。

给定 $m\times n$ 的地图、$k$、$h$ 以及大小为 $2^{k}$ 的概率数组。你的任务是求出在执行最优策略时，人物能活着走出迷宫的概率。
## 输入格式

第一行包含 $4$ 个整数，分别表示 $m,n,k,H$；

下面 $m$ 行每行 $n$ 个字符描述迷宫地图；

最后一行包含 $2^{k}$ 个非负整数描述数组 $p$，数组下标从 $0$ 开始。
## 输出格式

仅包含一个数字，表示在执行最优策略时，人物活着走出迷宫的概率。四舍五入保留 $3$ 位小数。
## 样例

### 样例输入 #1
```
4 3 2 1

.$.

A#B

A#B

.@.

30 30 20 20
```
### 样例输出 #1
```
0.600
```
### 样例输入 #2
```
4 3 2 2

.$.

A#B

A#B

.@.

30 30 20 20
```
### 样例输出 #2
```
0.800
```
### 样例输入 #3
```
4 3 2 3

.$.

A#B

A#B

.@.

30 30 20 20
```
### 样例输出 #3
```
1.000
```
### 样例输入 #4
```
4 3 3 2

.$.

A#B

A#C

@@@

143 37 335 85 95 25 223 57
```
### 样例输出 #4
```
0.858
```
## 提示

**【样例说明 1】**

向右边走，经过 `B` ，`B` 为有害陷阱的概率为 $\frac {(20+20)}{(30+30+20+20)}=0.4$，若 `B` 为有害陷阱那么人物就死掉了，游戏失败，否则玩家得知 `B` 是无害陷阱，继续经过另一个 `B` 达到终点，胜利的概率为 $0.6$。

**【样例说明 2】**

向左边走，经过 `A`，`A` 为有害陷阱的概率为 $\frac {(30+30)} {(30+30+20+20)}=0.5$。若 `A` 为有害陷阱，那么损失一点生命，转到右边尝试 `B` ，要想成功到达终点，此时 `B` 必须为无害陷阱，而在 `A`是有害陷阱的前提下，`B` 是无害陷阱的概率是 $\frac {30}{(30+20)}=0.6$，故这种情况发生的概率为 $0.5\times 0.6=0.3$。若 `A`是无害陷阱，玩家可以控制人物连续通过两个 `A` 到达终点，这种情况发生的概率 $0.5$。所以答案为 $0.3+0.5=0.8$。 


**【样例说明 3】**

玩家控制的人物有 $3$ 点生命，但最多只需要经过两个陷阱，所以任意选左路
或右路走过去就可以到达终点了。

**【数据范围与约定】**

|测试点编号  | $m$ | $n$ | $k$ | $H$ |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| $1$ | $29$ | $28$ | $5$ | $1$ |
| $2$ | $28$ | $20$ | $4$ | $1$ |
| $3$ | $25$ | $30$ | $1$ | $1$ |
| $4$ | $25$ | $30$ | $1$ | $2$ |
| $5$ | $25$ | $30$ | $1$ | $3$ |
| $6$ | $5$ | $5$ | $4$ | $4$ |
| $7$ | $12$ | $11$ | $4$ | $5$ |
| $8$ | $19$ | $17$ | $5$ | $3$ |
| $9$ | $23$ | $25$ | $5$ | $4$ |
| $10$ | $30$ | $29$ | $5$ | $5$ |

对于 $100\%$ 的数据，$1\le m\leq 30$，$1\le n\leq 29$，$k\leq 5$，$H\leq 5$，$0\leq p_i\leq 10^5$，且至少有一个 $p_i\gt0$ 。


---

---
title: "[AHOI2005] 穿越磁场"
layout: "post"
diff: 省选/NOI-
pid: P2537
tag: ['2005', '各省省选', '离散化', '安徽', '广度优先搜索 BFS', '最短路']
---
# [AHOI2005] 穿越磁场
## 题目描述

探险机器人在Samuel星球上寻找一块奇特的矿石，然而此时它陷入了一片神秘的磁场区域，动弹不得。

探险空间站立刻扫描了这片区域，绘制出该区域的磁场分布平面图。这片区域中分布了N个磁场，每个磁场呈正方形，且边与坐标轴平行。

例如下图中，存在3个磁场，白点表示机器人的位置，黑点表示矿石的位置：

 ![](https://cdn.luogu.com.cn/upload/pic/1642.png) 

科学家们分析平面图，进一步发现：这些磁场为大小不一的正方形，可能相交，甚至覆盖，但是它们的边缘不会重合，顶点也不会重合。

例如下面的两种情形是不会出现的：

 ![](https://cdn.luogu.com.cn/upload/pic/1643.png) 

科学家们给探险机器人启动了磁力罩，这样它就可以在磁场中自由穿越了。

初始时，探险机器人和所有矿石都不在任何磁场的边缘。由于技术限制，在穿越过程中机器人只能够水平或垂直移动，且不能够沿着磁场的边缘行动。

由于磁力罩的能量有限，科学家们希望探险机器人穿越尽量少的磁场边缘采集到这块矿石。例如上图中，探险机器人最少需要穿越两次磁场边缘。

现在小联请你编写程序，帮助科学家们设计探险机器人的路线，统计探险机器人最少需要穿越多少次磁场边缘。

## 输入格式

第一行有一个整数N，表示有N个磁场（1 < N < 100）。随后有N行，每行有三个整数X、Y、C（0 < X ,Y ,C < 10000），表示一个磁场左下角坐标为（X,Y），边长为C。接下来有一行，共有四个整数SX, SY, TX, TY，表示机器人初始坐标为（SX, SY），矿石坐标为（TX，TY）（其中，1 < SX, SY, TX, TY < 10000）。

## 输出格式

单行输出一个整数，表示机器人最少需要穿越多少次磁场边缘。

## 样例

### 样例输入 #1
```
2
1 3 3 
2 1 4
0 0 3 4
```
### 样例输出 #1
```
2
```


---

---
title: "[SCOI2008] 城堡"
layout: "post"
diff: 省选/NOI-
pid: P2538
tag: ['动态规划 DP', '搜索', '2008', '四川', '各省省选', '基环树']
---
# [SCOI2008] 城堡
## 题目背景

2008NOI四川省选

## 题目描述

在一个国家里，有 $n$ 个城市（编号为 $0$ 到 $n-1$）。这些城市之间有 $n$ 条双向道路相连（编号为 $0$ 到 $n-1$），其中编号为 $i$ 的道路连接了城市 $i$ 和城市 $r_i$（一条道路可以连接一个城市和它自身），长度为 $d_i$。$n$ 个城市中有 $m$ 个拥有自己城堡，可以抵御敌人侵略。如果没有城堡的城市遭受攻击，则离它最近的城堡将派兵前往救援。

你的任务是在不超过 $k$ 个没有城堡的城市中建立城堡，使得所有城市中“离最近城堡的距离”的最大值尽量小。换句话说，若令 $dist(c)$ 表示城市 $c$ 的最近城堡离它的距离，则你的任务是让 $\max\{dist(c)\}$ 尽量小。

输入数据保证存在方案使得对于每个城市，至少有一个城堡能够到达。
## 输入格式

输入第一行为三个正整数 $n, m, k$。第二行包含 $n$ 个整数 $r_0,r_1,\ldots,r_{n-1}$。第三行包含 $n$ 个整数 $d_0,d_1,\ldots,d_{n-1}$。第四行包含 $m$ 个各不相同的 $0$ 到 $n-1$ 之间的整数，分别为 $m$ 个城堡所在的城市编号。
## 输出格式

输出仅一行，包含一个整数，即 $\max\{dist(c)\}$ 的最小值。
## 样例

### 样例输入 #1
```
5 0 1
1 2 3 4 0
1 1 1 1 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
3 1 1
1 2 0
1 2 3
2
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
2 1 1  
0 1  
1 1  
1 
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
10 3 3
0 2 0 0 2 2 8 3 8 7
10 9 1 8 1 3 7 2 8 1
3 4 6
```
### 样例输出 #4
```
3
```
### 样例输入 #5
```
2 0 1
1 0
5 10
```
### 样例输出 #5
```
5
```
## 提示

$100\%$ 的数据满足: $2\leq n\leq 50$，$1\leq d_i\leq 10^6$，$0\leq m\leq n-k$。


---

---
title: "[NOIP 2015 提高组] 斗地主 加强版"
layout: "post"
diff: 省选/NOI-
pid: P2540
tag: ['2015', 'NOIP 提高组', '深度优先搜索 DFS', '剪枝']
---
# [NOIP 2015 提高组] 斗地主 加强版
## 题目描述

牛牛最近迷上了一种叫斗地主的扑克游戏。斗地主是一种使用黑桃、红心、梅花、方片的 $A$ 到 $K$ 加上大小王的共 $54$ 张牌来进行的扑克牌游戏。在斗地主中，牌的大小关系根据牌的数码表示如下：$3<4<5<6<7<8<9<10<J<Q<K<A<2<\text{小王}<\text{大王}$，而花色并不对牌的大小产生影响。每一局游戏中，一副手牌由 $n$ 张牌组成。游戏者每次可以根据规定的牌型进行出牌，首先打光自己的手牌一方取得游戏的胜利。

现在，牛牛只想知道，对于自己的若干组手牌，分别最少需要多少次出牌可以将它们打光。请你帮他解决这个问题。

需要注意的是，本题中游戏者每次可以出手的牌型与一般的斗地主相似而略有不同。具体规则如下：

 ![](https://cdn.luogu.com.cn/upload/pic/1827.png) 

**在此题中认为两个王不能组成对子牌**。

## 输入格式

第一行包含用空格隔开的 $2$ 个正整数 $T,n$，表示手牌的组数以及每组手牌的张数。

接下来 $T$ 组数据，每组数据 $n$ 行，每行一个非负整数对 $a_i,b_i$，表示一张牌，其中 $a_i$ 表示牌的数码，$b_i$ 表示牌的花色，中间用空格隔开。特别的，我们用 $1$ 来表示数码 $A$，$11$ 表示数码 $J$，$12$ 表示数码 $Q$，$13$ 表示数码 $K$；黑桃、红心、梅花、方片分别用 $1-4$ 来表示；小王的表示方法为 `0 1`，大王的表示方法为 `0 2`。
## 输出格式

共 $T$ 行，每行一个整数，表示打光第 $i$ 手牌的最少次数。

## 样例

### 样例输入 #1
```
1 8
7 4
8 4
9 1
10 4
11 1
5 1
1 4
1 1
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
1 17
12 3
4 3
2 3
5 4
10 2
3 3
12 2
0 1
1 3
10 1
6 2
12 1
11 3
5 2
12 4
2 2
7 2
```
### 样例输出 #2
```
6
```
## 提示

#### 样例 1 说明

共有 $1$ 组手牌，包含 $8$ 张牌：方片 $7$，方片 $8$，黑桃 $9$，方片 $10$，黑桃 $J$，黑桃 $5$，方片 $A$ 以及黑桃 $A$。可以通过打单顺子（方片 $7$，方片 $8$，黑桃 $9$，方片 $10$，黑桃 $J$），单张牌（黑桃 $5$）以及对子牌（黑桃 $A$ 以及方片 $A$）在 $3$ 次内打光。

#### 数据范围与提示

对于前 $20$ 个测试点， 我们约定手牌组数 $T$ 与张数 $n$ 的规模如下：

 ![](https://cdn.luogu.com.cn/upload/pic/1828.png) 

数据不保证所有的手牌都是随机生成的。



---

---
title: "[AHOI2002] 黑白瓷砖"
layout: "post"
diff: 省选/NOI-
pid: P2561
tag: ['搜索', '数学', '2002', '各省省选', '安徽', '置换']
---
# [AHOI2002] 黑白瓷砖
## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1685.png) 

![](https://cdn.luogu.com.cn/upload/pic/1686.png)

## 输入格式

一行，一个正整数 $n$，$n \leq 20$ 。

## 输出格式

以一行的形式输出问题的解 $s$ (解的位数不超过 $200$ 位)。

## 样例

### 样例输入 #1
```
1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
2
```
### 样例输出 #2
```
4
```


---

---
title: "[ZJOI2012] 小蓝的好友"
layout: "post"
diff: 省选/NOI-
pid: P2611
tag: ['2012', '各省省选', '平衡树', '浙江', '深度优先搜索 DFS', '栈']
---
# [ZJOI2012] 小蓝的好友
## 题目背景

终于到达了这次选拔赛的最后一题，想必你已经厌倦了小蓝和小白的故事。

为了回馈各位比赛选手，此题的主角是贯穿这次比赛的关键人物——小蓝的好友。

在帮小蓝确定了旅游路线后，小蓝的好友也不会浪费这个难得的暑假。

与小蓝不同，小蓝的好友并不想将时间花在旅游上，而是盯上了最近发行的即时战略游戏——SangoCraft。

但在前往通关之路的道路上，一个小游戏挡住了小蓝的好友的步伐。
## 题目描述


“国家的战争其本质是抢夺资源的战争”是整款游戏的核心理念，这个小游戏也不例外。

简单来说，用户需要在一块 $R\times C$ 的长方形土地上选出一块子矩形。

而系统随机生成了 $N$ 个资源点，第 $i$ 个资源点的坐标为 $(x_i,y_i)$。

位于用户所选的长方形土地上的资源点越多，给予用户的奖励也越多。

悲剧的是，小蓝的好友虽然拥有着极其优秀的能力，但同时也有着极差的 RP，小蓝的好友所选的区域总是没有一个资源点。

终于有一天，小蓝的好友决定投诉这款游戏的制造厂商，为了搜集证据，小蓝的好友想算出至少包含一个资源点的区域的数量。

具体的说，你需要计算有多少个四元组 $(LB,DB,RB,UB)$ 满足 $1\le LB\le RB\le R,1\le DB\le UB\le C$ ，且存在一个 $i$ 使得 $LB\le x_i\le RB,DB\le y_i\le UB$ 均成立。

作为小蓝的好友，这自然是你分内之事。
## 输入格式

第一行三个正整数 $R,C,N$。

接下来有 $N$ 行，每行包含两个整数 $x_i,y_i$，表示第 $i$ 个资源点的坐标。
## 输出格式

一行一个整数，表示至少包含一个资源点的区域的数量。
## 样例

### 样例输入 #1
```
5 5 4
1 2
2 3
3 5
4 1

```
### 样例输出 #1
```
139
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，$N\le 50$。
- 对于 $40\%$ 的数据，$N\le 2\times 10^3$。
- 对于 $100\%$ 的数据，$1\le R,C\le 4\times 10^4$，$1\le N\le 10^5$，题目保证资源点的位置两两不同，且位置为随机生成。


---

---
title: "白金莲花池"
layout: "post"
diff: 省选/NOI-
pid: P2644
tag: ['搜索']
---
# 白金莲花池
## 题目背景

为了让奶牛们娱乐和锻炼，农夫约翰建造了一个美丽的池塘。这个长方形的池子被分成了 $M$ 行 $N$ 列个方格（$1≤M,N≤30$）。一些格子是坚固得令人惊讶的莲花，还有一些格子是岩石，其余的只是美丽、纯净、湛蓝还可能掩藏着宝藏的水。

贝西正在练习芭蕾舞，她站在一朵莲花上，想跳到另一朵莲花上去，她只能从一朵莲花跳到另一朵莲花上，既不能跳到水里，也不能跳到岩石上。

贝西的舞步很像象棋中的马步：每次总是先横向移动一格，再纵向移动两格，或先纵向移动两格，再横向移动一格。最多时，贝西会有八个移动方向可供选择。

约翰一直在观看贝西的芭蕾练习，发现她有时候不能跳到终点，因为中间缺了一些荷叶。于是他想要添加几朵莲花来帮助贝西完成任务，当然莲花不能种在岩石上。

## 题目描述

但是！约翰在种植莲花的时候发现了一件很有趣的事，有些格子是不能直接种植莲花的，原因是……实不相瞒，无法直接种植莲花的格子的泥土中大部分都是货真价实的铂金，正是它们妨碍了莲花的正常生长！而恰好约翰刚刚学到了铂金的开采方法，也有相关的开采工具，而且他还发现开采铂金后的格子就可以正常地种植莲花，不必担心泥土缺失的问题。（由于贝西迫切地想练习，所以约翰不会开采不打算种莲花的铂金格子）

开采铂金很累，就像是种植莲花一样累，它们都会消耗掉约翰 $1$ 点体力（也就是说想把铂金格子变成莲花格子需要 $2$ 点体力），约翰最初有 $P$ 点体力来种植莲花或开采铂金。

请帮助约翰计算至少需要消耗多少体力才能帮助贝西完成任务，这个数字记作 $S$，以及有多少种消耗这些体力的方法能帮助贝西完成任务，这个数字记作 $W_S$；铂金当然是越多越好，请计算在消耗 $S$ 点体力帮助贝西完成任务的同时最多能开采多少铂金，这个数字记作 $G$，以及消耗 $S$ 点体力开采 $G$ 块铂金帮助贝西完成任务的方法数，这个数字记作 $W_G$。

若在 $P$ 点体力内无法帮助到贝西，那么只输出 `-1`。

若在 $S$ 点体力内无法开采铂金，那么第二行只输出 `-1`。
## 输入格式

第一行：三个用空格分开的整数：$P$，$M$ 和 $N$

第二行到 $M+1$ 行：第 $i+1$ 行有 $N$ 个用空格分开的整数，描述了池塘第 $i$ 行的状态：

$0$ 为水，$1$ 为莲花，$2$ 为岩石，$3$ 为贝西所在的起点，$4$ 为贝西想去的终点，$5$ 为铂金的埋藏地。
## 输出格式


第一行：用空格分隔开 $S$ 和 $W_S$（两个整数，需要最少消耗的体力及方案数；如果无法帮助，输出 `-1`。）

第二行：用空格分隔开 $G$ 和 $W_G$（两个整数，在消耗最少的前提下开采最多的铂金数及方案数，若在 $S$ 点体力内无法开采铂金，第二行输出 `-1`。）

如果第一行是 `-1`，不要输出第二行。

保证输出的数字不会超过 `long long`。
## 样例

### 样例输入 #1
```
4 5 6
0 0 0 1 0 0
2 0 0 2 0 0
0 0 5 0 0 0
3 0 0 0 4 0
0 0 2 0 0 0
```
### 样例输出 #1
```
2 2
1 1
```
### 样例输入 #2
```
3 3 2
3 5
4 2
0 1
```
### 样例输出 #2
```
-1
```
## 提示

约翰可以用开采到的铂金小赚一笔，但如果用多余的体力开采铂金而不往上种莲花的话贝西会很生气！



---

---
title: "[USACO5.5] 贰五语言Two Five"
layout: "post"
diff: 省选/NOI-
pid: P2750
tag: ['动态规划 DP', '2001', 'USACO', 'IOI', '深度优先搜索 DFS']
---
# [USACO5.5] 贰五语言Two Five
## 题目描述

有一种奇怪的语言叫做“贰五语言”。它的每个单词都由A～Y这25个字母各一个组成。但是，并不是任何一种排列都是一个合法的贰五语言单词。贰五语言的单词必须满足这样一个条件：把它的25个字母排成一个5\*5的矩阵，它的每一行和每一列都必须是递增的。比如单词ACEPTBDHQUFJMRWGKNSXILOVY，它排成的矩阵如下所示：

A C E P T

B D H Q U

F J M R W

G K N S X

I L O V Y

因为它的每行每列都是递增的，所以它是一个合法的单词。而单词YXWVUTSRQPONMLKJIHGFEDCBA则显然不合法。 由于单词太长存储不便，需要给每一个单词编一个码。编码方法如下：从左到右，再从上到下，可以由一个矩阵的得到一个单词，再把单词按照字典顺序排序。比如，单词ABCDEFGHIJKLMNOPQRSTUVWXY的编码为1，而单词ABCDEFGHIJKLMNOPQRSUTVWXY的编码为2。

现在，你需要编一个程序，完成单词与编码间的转换。

## 输入格式

第一行为一个字母N或W。N表示把编码转换为单词，W表示把单词转换为编码。

若第一行为N，则第二行为一个整数，表示单词的编码。若第一行为W，则第二行为一个合法的单词。

## 输出格式

每行一个整数或单词。

## 样例

### 样例输入 #1
```
N
2
```
### 样例输出 #1
```
ABCDEFGHIJKLMNOPQRSUTVWXY
```
### 样例输入 #2
```
W 
ABCDEFGHIJKLMNOPQRSUTVWXY
```
### 样例输出 #2
```
2
```
## 提示

题目翻译来自NOCOW。

USACO Training Section 5.5



---

---
title: "方格取数问题"
layout: "post"
diff: 省选/NOI-
pid: P2774
tag: ['网络流', 'O2优化', '深度优先搜索 DFS', '最小割', '网络流与线性规划 24 题']
---
# 方格取数问题
## 题目描述

有一个 $m$ 行 $n$ 列的方格图，每个方格中都有一个正整数。现要从方格中取数，使任意两个数所在方格没有公共边，且取出的数的总和最大，请求出最大的和。

## 输入格式

第一行是两个用空格隔开的整数，分别代表方格图的行数 $m$ 和列数 $n$。

第 $2$ 到第 $(m + 1)$ 行，每行 $n$ 个整数，第 $(i + 1)$ 行的第 $j$ 个整数代表方格图第 $i$ 行第 $j$ 列的的方格中的数字 $a_{i, j}$。
## 输出格式

输出一行一个整数，代表和最大是多少。
## 样例

### 样例输入 #1
```
3 3
1 2 3
3 2 3
2 3 1 
```
### 样例输出 #1
```
11
```
## 提示

**数据规模与约定**

对于 $100\%$ 的数据，保证 $1 \leq n, m \leq 100$，$1 \leq a_{i, j} \leq 10^5$。

**提示**

请注意输入的第一行先读入 $m$ 再读入 $n$。


---

---
title: "[USACO07DEC] Sightseeing Cows G"
layout: "post"
diff: 省选/NOI-
pid: P2868
tag: ['搜索', '2007', '二分', 'USACO', '最短路', '分数规划']
---
# [USACO07DEC] Sightseeing Cows G
## 题目描述

Farmer John has decided to reward his cows for their hard work by taking them on a tour of the big city! The cows must decide how best to spend their free time.

Fortunately, they have a detailed city map showing the L (2 ≤ L ≤ 1000) major landmarks (conveniently numbered 1.. L) and the P (2 ≤ P ≤ 5000) unidirectional cow paths that join them. Farmer John will drive the cows to a starting landmark of their choice, from which they will walk along the cow paths to a series of other landmarks, ending back at their starting landmark where Farmer John will pick them up and take them back to the farm. Because space in the city is at a premium, the cow paths are very narrow and so travel along each cow path is only allowed in one fixed direction.

While the cows may spend as much time as they like in the city, they do tend to get bored easily. Visiting each new landmark is fun, but walking between them takes time. The cows know the exact fun values Fi (1 ≤ Fi ≤ 1000) for each landmark i.

The cows also know about the cowpaths. Cowpath i connects landmark L1i to L2i (in the direction L1i -> L2i ) and requires time Ti (1 ≤ Ti ≤ 1000) to traverse.

In order to have the best possible day off, the cows want to maximize the average fun value per unit time of their trip. Of course, the landmarks are only fun the first time they are visited; the cows may pass through the landmark more than once, but they do not perceive its fun value again. Furthermore, Farmer John is making the cows visit at least two landmarks, so that they get some exercise during their day off.

Help the cows find the maximum fun value per unit time that they can achieve.

## 输入格式

\* Line 1: Two space-separated integers: L and P

\* Lines 2..L+1: Line i+1 contains a single one integer: Fi

\* Lines L+2..L+P+1: Line L+i+1 describes cow path i with three space-separated integers: L1i , L2i , and Ti

## 输出格式

\* Line 1: A single number given to two decimal places (do not perform explicit rounding), the maximum possible average fun per unit time, or 0 if the cows cannot plan any trip at all in accordance with the above rules.

## 样例

### 样例输入 #1
```
5 7
30
10
10
5
10
1 2 3
2 3 2
3 4 5
3 5 2
4 5 5
5 1 3
5 2 2
```
### 样例输出 #1
```
6.00
```
## 题目翻译

给你一张 $n$ 点 $m$ 边的有向图，第 $i$ 个点点权为 $F_i$，第 $i$ 条边边权为 $T_i$。

找一个环，设环上的点组成的集合为 $S$，环的边组成的集合为 $E$，最大化 $\dfrac{\sum_{u\in S}F_u}{\sum_{e\in E}T_e}$。

数据范围：$1\leq n,F_i,T_i\leq 10^3$，$1\leq m\leq 5\times10^3$。


---

---
title: "[USACO13DEC] The Bessie Shuffle G"
layout: "post"
diff: 省选/NOI-
pid: P3098
tag: ['2013', 'USACO', '并查集', '广度优先搜索 BFS', '图论建模']
---
# [USACO13DEC] The Bessie Shuffle G
## 题目描述

Bessie is practicing her card tricks.  She has already mastered the Bessie- shuffle -- a shuffle on M (2 <= M <= 100,000) cards that reorganizes the cards so the i-th card from the top is now the P[i]-th card from the top.

Now Bessie is practicing shuffles on larger decks.  She has a deck of N cards (M <= N <= 1,000,000,000) conveniently labeled 1 to N.  She shuffles this deck by taking the first M cards and performing the Bessie-shuffle on them, placing the shuffled cards back on top of the deck.  She then removes the top card from the deck and places it face down.  She repeats this process, placing the top cards successively on top of each other, until she is out of cards.  When Bessie has less than M cards left, she no longer performs the Bessie-shuffle, but continues to place the top card on top of the others.

Bessie knows that the deck initially started in sorted order, with 1 on top, 2 next, and N on the bottom.  Given the description of the Bessie-shuffle, help Bessie compute which cards end up located at Q different specified positions (1 <= Q <= N, Q <= 5,000) in the deck.

50% of test cases will have N <= 100,000. 

贝西有一种独门的洗牌方法，称为 A 类洗牌法；

A 类洗牌法的具体过程：将一堆共 $M$（$2 \le M \le 10 ^ 5$）张从上到下编号 $1, 2, \cdots, M$ 的纸牌，从上到下第 $i$ 张牌洗到位置 $p _ i$。

例如，$M=3，p = \{3, 1, 2\}$，则执行一次 A 类洗牌法后，从上到下将变为 $2, 3, 1$，即牌 $1$ 放到位置 $3$，牌 $2$ 放到位置 $1$，牌 $3$ 放到位置 $2$。


贝西现在要练习另外一种洗牌方法，称为 B 类洗牌法。


B 类洗牌法的具体过程： 

有一堆 $N$（$M \le N \le 10 ^ 9$）张编号为 $1, 2, \cdots, N$ 的牌，并按从上到下 $1$ 到 $N$ 的顺序堆放。另有一个牌堆用来辅助洗牌，称为临时堆，开始时为空。

1. 将最上面 $M$ 张牌进行一次 A 类洗牌法；
2. 将最上面的一张牌放到临时堆的最上方；
3. 重复前两个操作，直到原先的堆没有牌为止。


以上过程中，当原先堆的牌不足 $M$ 张的时候，将不进行 A 类洗牌法，而是将最上面的牌依次放到临时堆上。


给定 $N, M$ 和排列 $p$。现在有 $Q$（$1 \le Q \le \min(N, 5000)$）个询问，请求出对其做一次 B 类洗牌法后临时堆中 $q _ i$ 位置上的牌的编号。

$50\%$ 的数据中，$N \le 10 ^ 5$。

## 输入格式

\* Line 1: A single line containing N, M and Q separated by a space.

\* Lines 2..1+M: Line i+1 indicates the position from the top, P[i], of the i-th card in the Bessie-shuffle (1 <= P[i] <= M).

\* Lines 2+M..1+M+Q: Line i+1+M contains a single integer q\_i

describing the i-th query.  You are to compute the label on the card located in position q\_i from the top (1 <= q\_i <= N).

## 输出格式

\* Lines 1..Q: On the i-th line, print a single integer indicating the card at position q\_i from the top.

## 样例

### 样例输入 #1
```
5 3 5 
3 
1 
2 
1 
2 
3 
4 
5 

```
### 样例输出 #1
```
4 
5 
3 
1 
2 

```
## 提示

Bessie has a deck of 5 cards initially ordered as [1, 2, 3, 4, 5].  Her shuffle is on 3 cards and has the effect of moving the top card to the bottom.  There are 5 queries querying each position in the deck.


The shuffle proceeds as:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (put 2 face down) 
[3, 1, 4, 5] -> [1, 4, 3, 5] (put 1 face down) 
[4, 3, 5] -> [3, 5, 4] (put 3 face down) 
[5, 4] (put 5 face down) 
[4] (put 4 face down) 
```
This produces the final order of [4, 5, 3, 1, 2]

贝西的五张牌刚开始顺序为 [1, 2, 3, 4, 5]。她一次洗三张牌，效果是将第一张牌放到底部。以上五个问题询问了每一张牌的位置。


洗牌的顺序是:

```plain
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (将2正面向下放置)
[3, 1, 4, 5] -> [1, 4, 3, 5] (将1正面向下放置) 
[4, 3, 5] -> [3, 5, 4] (将3正面向下放置) 
[5, 4] (将5正面向下放置) 
[4] (将4正面向下放置) 
```
这就形成了最终的顺序：[4, 5, 3, 1, 2]



---

---
title: "[HNOI2007] 紧急疏散EVACUATE"
layout: "post"
diff: 省选/NOI-
pid: P3191
tag: ['搜索', '2007', '二分', '网络流', '湖南']
---
# [HNOI2007] 紧急疏散EVACUATE
## 题目描述

发生了火警，所有人员需要紧急疏散！假设每个房间是一个N M的矩形区域。每个格子如果是'.'，那么表示这是一块空地；如果是'X'，那么表示这是一面墙，如果是'D'，那么表示这是一扇门，人们可以从这儿撤出房间。已知门一定在房间的边界上，并且边界上不会有空地。最初，每块空地上都有一个人，在疏散的时候，每一秒钟每个人都可以向上下左右四个方向移动一格，当然他也可以站着不动。疏散开始后，每块空地上就没有人数限制了（也就是说每块空地可以同时站无数个人）。但是，由于门很窄，每一秒钟只能有一个人移动到门的位置，一旦移动到门的位置，就表示他已经安全撤离了。现在的问题是：如果希望所有的人安全撤离，最短需要多少时间？或者告知根本不可能。

## 输入格式

输入文件第一行是由空格隔开的一对正整数N与M，3<=N <=20，3<=M<=20，以下N行M列描述一个N M的矩阵。其中的元素可为字符'.'、'X'和'D'，且字符间无空格。

## 输出格式

只有一个整数K，表示让所有人安全撤离的最短时间，如果不可能撤离，那么输出'impossible'（不包括引号）。

## 样例

### 样例输入 #1
```
5 5
XXXXX
X...D
XX.XX
X..XX
XXDXX
```
### 样例输出 #1
```
3
```
## 提示

2015.1.12新加数据一组，鸣谢1756500824

C++语言请用scanf("%s",s)读入！



---

---
title: "[HNOI2008] 神奇的国度"
layout: "post"
diff: 省选/NOI-
pid: P3196
tag: ['2008', '湖南', '广度优先搜索 BFS', '哈希 hashing', '弦图']
---
# [HNOI2008] 神奇的国度
## 题目描述

K国是一个热衷三角形的国度,连人的交往也只喜欢三角原则.他们认为三角关系:即AB相互认识,BC相互认识,CA相互认识,是简洁高效的.为了巩固三角关系,K国禁止四边关系,五边关系等等的存在.

所谓N边关系,是指N个人 A1A2...An之间仅存在N对认识关系:(A1A2)(A2A3)...(AnA1),而没有其它认识关系.比如四边关系指ABCD四个人 AB,BC,CD,DA相互认识,而AC,BD不认识.全民比赛时,为了防止做弊，规定任意一对相互认识的人不得在一队，国王相知道，最少可以分多少支队。

## 输入格式

第一行两个整数N，M。1<=N<=10000,1<=M<=1000000.表示有N个人，M对认识关系. 接下来M行每行输入一对朋友

## 输出格式

输出一个整数，最少可以分多少队

## 样例

### 样例输入 #1
```
4 5
1 2
1 4
2 4
2 3
3 4
```
### 样例输出 #1
```
3
```
## 提示

一种方案(1,3)(2)(4)



---

---
title: "[HNOI2009] 最小圈"
layout: "post"
diff: 省选/NOI-
pid: P3199
tag: ['2009', '各省省选', '湖南', '深度优先搜索 DFS', '分数规划']
---
# [HNOI2009] 最小圈
## 题目描述

考虑带权有向图 $G=(V,E)$ 以及 $w:E\rightarrow \R$，每条边 $e=(i,j)$（$i\neq j$，$i, j\in V$）的权值定义为 $w_{i,j}$。设 $n=|V|$。

$c=(c_1,c_2,\cdots,c_k)$（$c_i\in V$）是 $G$ 中的一个圈当且仅当 $(c_i,c_{i+1})$（$1\le i<k$）和 $(c_k,c_1)$ 都在 $E$ 中。称 $k$ 为圈 $c$ 的长度，同时记 $c_{k+1}=c_1$，并定义圈 $c=(c_1,c_2,\cdots,c_k)$ 的平均值为
$$
\mu(c)= \frac 1 k \sum\limits_{i=1}^{k} w_{c_i,c_{i+1}}
$$
即 $c$ 上所有边的权值的平均值。设 $\mu'(G)=\min_c\mu(c)$ 为 $G$ 中所有圈 $c$ 的平均值的最小值。

给定图 $G=(V,E)$ 以及 $w:E\rightarrow \R$，求出 $G$ 中所有圈 $c$ 的平均值的最小值 $\mu'(G)$。

## 输入格式

第一行两个正整数，分别为 $n$ 和 $m$，并用一个空格隔开。其中 $n=|V|$，$m=|E|$ 分别表示图中有 $n$ 个点 和 $m$ 条边。

接下来 $m$ 行，每行三个数 $i,j,w_{i,j}$，表示有一条边 $(i,j)$ 且该边的权值为 $w_{i,j}$，注意边权可以是实数。输入数据保证图 $G=(V,E)$ 连通，存在圈且有一个点能到达其他所有点。

## 输出格式

一个实数 $\mu'(G)$，要求精确到小数点后 $8$ 位。

## 样例

### 样例输入 #1
```
4 5
1 2 5
2 3 5
3 1 5
2 4 3
4 1 3
```
### 样例输出 #1
```
3.66666667
```
### 样例输入 #2
```
2 2
1 2 -2.9
2 1 -3.1
```
### 样例输出 #2
```
-3.00000000
```
## 提示

对于 $100\%$ 的数据，$2\leq n\le 3000$，$1\leq m\le 10000$，$|w_{i,j}| \le 10^7$，$1\leq i, j\leq n$ 且 $i\neq j$。

------------
提示：本题存在 $O(nm)$ 的做法，但是 $O(nm\log n)$ 的做法也可以通过。


---

---
title: "[HNOI2011] 任务调度"
layout: "post"
diff: 省选/NOI-
pid: P3212
tag: ['搜索', '2011', '各省省选', '湖南', '随机化']
---
# [HNOI2011] 任务调度
## 题目描述


有 $n$ 个任务和两台机器 A 与 B。每个任务都需要既在机器 A 上执行，又在机器 B 上执行，

第 $i$ 个任务需要在机器 A 上执行时间 $a_i$，且需要在机器 B 上执行时间 $b_i$。最终的目标是所有任务在 A 和 B 上都执行完，且希望执行完所有任务的总时间尽量少。当然问题没有这么简单，有些任务对于先在机器 A 上执行还是先在机器 B 上执行有一定的限制。据此可将所有任务分为三类：

1. 任务必须先在机器 A 上执行完然后再在机器 B 上执行。
2. 任务必须先在机器 B 上执行完然后再在机器 A 上执行。
3. 任务没有限制，既可先在机器 A 上执行，也可先在机器 B 上执行。

现在给定每个任务的类别和需要在机器 A 和机器 B 上分别执行的时间，问使所有任务都能按规定完成所需要的最少总时间是多少。
## 输入格式

输入的第一行只有一个正整数 $n$，表示任务的个数。

接下来的 $n$ 行，每行是用空格隔开的三个正整数 $t_i,a_i,b_i$，分别表示第 $i$ 个任务的类别（类别 $1$，$2$，$3$ 的定义如上）以及第 $i$ 个任务需要在机器 A 和机器 B 上分别执行的时间。
## 输出格式

输出仅包含一个正整数，表示所有任务都执行完所需要的最少总时间。
## 样例

### 样例输入 #1
```
3
3 5 7
1 6 1 
2 2 6

```
### 样例输出 #1
```
14
```
## 提示

#### 样例 1 解释

一种最优任务调度方案为：

机器 A 上执行的各任务依次安排如下：

任务 $1\ (0\to 5)$，任务 $2\ (5\to 11)$, 任务 $3\ (11\to 13)$；

机器 B 上执行的各任务依次安排如下：

任务 $3\ (0 \to 6)$, 任务 $1\ (6 \to 13)$, 任务 $2\ (13 \to14)$，

这样，所有任务都执行完所需要的总时间为 $14$。

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1\le n\le 20$，$1\le a_i\le 10^3$，$1\le t_i\le 3$，并保证 $t_i=3$ 的 $i$ 不超过 $10$ 个。


---

---
title: "[HNOI2013] 数列"
layout: "post"
diff: 省选/NOI-
pid: P3228
tag: ['搜索', '2013', '湖南', '队列']
---
# [HNOI2013] 数列
## 题目描述

小 $T$ 最近在学着买股票，他得到内部消息：$F$ 公司的股票将会疯涨。股票每天的价格已知是正整数，并且由于客观上的原因，最多只能为 $N$。在疯涨的 $K$ 天中小 $T$ 观察到：除第一天外每天的股价都比前一天高，且高出的价格（即当天的股价与前一天的股价之差）不会超过 $M$，$M$ 为正整数。并且这些参数满足 $M(K-1)<N$。小 $T$ 忘记了这 $K$ 天每天的具体股价了，他现在想知道这 $K$ 天的股价有多少种可能。
## 输入格式

只有一行用空格隔开的四个数：$N$ 、 $K$ 、 $M$ 、 $P$。对 $P$ 的说明参见后面“输出格式”中对 $P$ 的解释。输入保证 $20\%$ 的数据 $M,N,K,P \le 20000$，保证 $100\%$ 的数据 $M,K,P \le 10^9$，$N \le 10^{18}$。
## 输出格式

仅包含一个数，表示这 $K$ 天的股价的可能种数对于 $P$ 的模值。【输入输出样例】

## 样例

### 样例输入 #1
```
7 3 2 997

```
### 样例输出 #1
```
16

```
## 提示

**样例解释**  

输出样例的 $16$ 表示输入样例的股价有 $16$ 种可能：

{1，2，3}，{1，2，4}，{1，3，4}，{1，3，5}， {2，3，4}，{2，3，5}，{2，4，5}，{2，4，6}， {3，4，5}，{3，4，6}，{3，5，6}，{3，5，7}，{4，5，6}，{4，5，7}，{4，6，7}，{5，6，7}


---

---
title: "[HNOI2013] 消毒"
layout: "post"
diff: 省选/NOI-
pid: P3231
tag: ['搜索', '2013', '湖南', '枚举', '二分图']
---
# [HNOI2013] 消毒
## 题目描述


最近在生物实验室工作的小 T 遇到了大麻烦。 由于实验室最近升级的缘故，他的分格实验皿是一个长方体，其尺寸为 $a\times b\times c$。为了实验的方便，它被划分为 $a\times b\times c$ 个单位立方体区域，每个单位立方体尺寸为 $1\times 1\times 1$，并用 $(i,j,k)$ 标识一个单位立方体。这个实验皿已经很久没有人用了。现在，小 T 被导师要求将其中一些单位立方体区域进行消毒操作（每个区域可以被重复消毒）。

而由于严格的实验要求，他被要求使用一种特定的 F 试剂来进行消毒。 这种 F 试剂特别奇怪，每次对尺寸为 $x\times y\times z$ 的长方体区域（它由 $x\times y\times z$ 个单位立方体组成）进行消毒时，只需要使用 $\min(x,y,z)$ 单位的 F 试剂。F 试剂的价格不菲，这可难倒了小 T。

现在请你告诉他，最少要用多少单位的 F 试剂。
## 输入格式

**本题有多组数据。**

第一行是一个正整数 $D$，表示数据组数。

接下来是 $D$ 组数据，每组数据第一行是三个正整数 $a,b,c$ 表示实验皿的尺寸。

接下来会出现 $a$ 个 $b$ 行 $c$ 列的用空格隔开的 `01` 矩阵，`0` 表示对应的单位立方体不要求消毒，`1` 表示对应的单位立方体需要消毒：如，如果第 $1$ 个 `01` 矩阵的第 $2$ 行第 $3$ 列为 `1`，则表示单位立方体 $(1,2,3)$ 需要被消毒。
## 输出格式

$D$ 行，每行一个整数，表示对应实验皿最少要用多少单位的 F 试剂。
## 样例

### 样例输入 #1
```
1
4  4 4
1  0 1 1
0  0 1 1
0  0 0 0
0  0 0 0
0  0 1 1
1  0 1 1
0  0 0 0
0  0 0 0
0  0 0 0
0  0 0 0
1  0 0 0
0  0 0 0
0  0 0 0
0  0 0 0
0  0 0 0
1  0 0 0
```
### 样例输出 #1
```
3
```
## 提示

#### 样例 1 解释
对于区域 $(1,1,3)-(2,2,4)$ 和 $(1,1,1)-(4,4,1)$ 消毒，分别花费 $2$ 个单位和 $1$ 个单位的 F 试剂。

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $1\le a,b,c\le 5\times 10^3$，$abc\le 5\times 10^3$，且 $1\le D\le 3$。



---

---
title: "[HNOI2015] 接水果"
layout: "post"
diff: 省选/NOI-
pid: P3242
tag: ['2015', '湖南', '深度优先搜索 DFS', '最近公共祖先 LCA', '树套树']
---
# [HNOI2015] 接水果
## 题目描述

风见幽香非常喜欢玩一个叫做 osu! 的游戏，其中她最喜欢玩的模式就是接水果。由于她已经 DT FC 了 The big black，她觉得这个游戏太简单了，于是发明了一个更加难的版本。

首先有一个地图，是一棵由 $n$ 个顶点，$n-1$ 条边组成的树。

这颗树上有 $p$ 个盘子，每个盘子实际上是一条路径，并且每个盘子还有一个权值。第 $i$ 个盘子就是顶点 $a_i$ 到顶点 $b_i$ 的路径（由于是树，所以从 $a_i$ 到 $b_i$ 的路径是唯一的），权值为 $c_i$。

接下来依次会有 $q$ 个水果掉下来，每个水果本质上也是一条路径，第 $i$ 个水果是从顶点 $u_i$ 到顶点 $v_i$ 的路径。

幽香每次需要选择一个盘子去接当前的水果：一个盘子能接住一个水果，当且仅当盘子的路径是水果的路径的子路径。这里规定：从 $a$ 到 $b$ 的路径与从 $b$ 到 $a$ 的路径是同一条路径。

当然为了提高难度，对于第 $i$ 个水果，你需要选择能接住它的所有盘子中，权值第 $k_i$ 小的那个盘子，每个盘子可重复使用（没有使用次数的上限：一个盘子接完一个水果后，后面还可继续接其他水果，只要它是水果路径的子路径）。幽香认为这个游戏很难，你能轻松解决给她看吗？

## 输入格式

第一行三个数 $n$ 和 $p$ 和 $q$，表示树的大小和盘子的个数和水果的个数。

接下来 $n-1$ 行，每行两个数 $a,b$，表示树上的 $a$ 和 $b$ 之间有一条边。树中顶点按 $1$ 到 $n$ 标号。

接下来 $p$ 行，每行三个数 $a,b,c$，表示路径为 $a$ 到 $b$、权值为 $c$ 的盘子，其中 $a \neq b$。

接下来 $q$ 行，每行三个数 $u,v,k$，表示路径为 $u$ 到 $v$ 的水果，其中 $u \neq v$，你需要选择第 $k$ 小的盘子，第 $k$ 小一定存在。

## 输出格式

对于每个果子，输出一行表示选择的盘子的权值。

## 样例

### 样例输入 #1
```
10 10 10
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
3 2 217394434
10 7 13022269
6 7 283254485
6 8 333042360
4 6 442139372
8 3 225045590
10 4 922205209
10 8 808296330
9 2 486331361
4 9 551176338
1 8 5
3 8 3
3 8 4
1 8 3
4 8 1
2 3 1
2 3 1
2 3 1
2 4 1
1 4 1
```
### 样例输出 #1
```
442139372 
333042360 
442139372 
283254485 
283254485 
217394434 
217394434 
217394434 
217394434 
217394434
```
## 提示

对于 $100\%$ 的数据，$1\leq n,p,q \leq4\times 10^4$，$0 \le c \le 10^9$。



---

---
title: "[HNOI2016] 矿区"
layout: "post"
diff: 省选/NOI-
pid: P3249
tag: ['2016', '湖南', '枚举', '深度优先搜索 DFS', '生成树']
---
# [HNOI2016] 矿区
## 题目描述

平面上的矿区划分成了若干个开发区域。

简单地说，你可以将矿区看成一张连通的平面图，平面图划分为了若干平面块，每个平面块即为一个开发区域，平面块之间的边界必定由若干整点(坐标值为整数的点)和连接这些整点的线段组成。每个开发区域的矿量与该开发区域的面积有关：具体而言，面积为 $ s $ 的开发区域的矿量为 $ s^2 $。

现在有 $ m $ 个开采计划。每个开采计划都指定了一个由若干开发区域组成的多边形，一个开采计划的优先度被规定为矿量的总和÷开发区域的面积和；例如，若某开采计划指定两个开发区域，面积分别为 $ a $ 和 $ b $，则优先度为 $ (a^2+b^2)/(a+b) $。由于平面图是按照划分开发区域边界的点和边给出的，因此每个开采计划也只说明了其指定多边形的边界，并未详细指明是哪些开发区域（但很明显，只要给出了多边形的边界就可以求出是些开发区域）。

你的任务是求出每个开采计划的优先度。为了避免精度问题，你的答案必须按照分数的格式输出，即求出分子和分母，且必须是最简形式（分子和分母都为整数，而且都消除了最大公约数；例如，若矿量总和是 $ 1.5 $，面积和是 $ 2 $，那么分子应为 $ 3 $，分母应为 $ 4 $；又如，若矿量和是 $ 2 $，面积和是 $ 4 $，那么分子应为 
 $ 1 $，分母应为 $ 2 $）。

由于某些原因，你必须依次对每个开采计划求解（即下一个开采计划会按一定格式加密，加密的方式与上一个开采计划的答案有关）。具体的加密方式见输入格式。
## 输入格式

第一行三个正整数 $ n, m, k $，分别描述平面图中的点和边，以及开采计划的个数。  

接下来 $ n $ 行，第 $ i $ 行 ( $ i = 1, 2, \cdots , n $)有两个整数 $x_i, y_i$,  表示点 $ i $ 的坐标为 $(x_i, y_i)$。  

接下来 $ m $ 行，第 $ i $ 行有两个正整数 $a, b$，表示点 $ a $ 和 $ b $ 之间有一条边。  

接下来一行若干个整数，依次描述每个开采计划。每个开采计划的第一个数 $ c $ 指出该开采计划由开发区域组成的多边形边界上的点的个数为 $ d=(c+P) \bmod n \mathrel{+} 1 $；接下来 $ d $ 个整数，按逆时针方向描述边界上的每一个点：设其中第 $ i $ 个数为 $ z_i $，则第 $ i $ 个点的编号为 $(z_i+P)\bmod n \mathrel{+} 1$。其中 $ P $ 是上一个开采计划的答案中分子的值；对于第 $ 1 $ 个开采计划，$ P = 0 $。
## 输出格式

对于每个开采计划，输出一行两个正整数，分别描述分子和分母。

## 样例

### 样例输入 #1
```
9 14 5
0 0
1 0
2 0
0 1
1 1
2 1
0 2
1 2
2 2
1 2
2 3
5 6
7 8
8 9
1 4
4 7
5 8
3 6
6 9
4 8
1 5
2 6
6 8
3 3 0 4 7 1 3 4 6 4 8 0 4 3 6 2 3 8 0 4 6 2 5 0 4 5 7 6 3
```
### 样例输出 #1
```
1 1 
1 2 
1 1 
9 10 
3 4
```
## 提示

### 样例解释

输入文件给出的 $9$ 个点和 $14$ 条边描述的平面图如下所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/cg70enmo.png)

第一个开采计划，输入的第 $1$ 个值为 $3$，所以该开采计划对应的多边形有 $(3+0)\bmod 8+1=4$ 个点，将接下的 $4$ 个数 $3,0,4,7$，分别代入 $(z_i+0)\bmod n+1$ 得到 $4$ 个点的编号为 $4,1,5,8$。计算出第一个开采计划的分子为 $1$，分母为 $1$。

类似地，可计算出余下开采计划的多边形的点数和点的编号：第二个开采计划对应的多边形有 $3$ 个点，编号分别为 $5,6,8$。第三个开采计划对应的多边形有 $6$ 个点，编号分别为 $1,2,6,5,8,4$。第四个开采计划对应的多边形有 $5$ 个点，编号分别为 $1,2,6,8,4$。第五个开采计划对应的多边形有 $6$ 个点，编号分别为 $1,5,6,8,7,4$。

### 数据范围及约定


对于 $ 100 \% $ 的数据，$ n, k \leq 2 \times 10^5, \  m \leq 3n-6, \  |x_i|, |y_i| \leq 3×10^4$。

所有开采计划的 $ d $ 之和不超过 $2 \times 10^6$。保证任何开采计划都包含至少一个开发区域，且这些开发区域构成一个连通块。

保证所有开发区域的矿量和不超过 $ 2^{63}-1 $。

保证平面图中没有多余的点和边。

保证数据合法。由于输入数据量较大，建议使用读入优化。





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
title: "[JLOI2015] 战争调度"
layout: "post"
diff: 省选/NOI-
pid: P3262
tag: ['搜索', '2015', '各省省选', '吉林', '枚举', '深度优先搜索 DFS']
---
# [JLOI2015] 战争调度
## 题目描述

脸哥最近来到了一个神奇的王国，王国里的公民每个公民有两个下属或者没有下属，这种关系刚好组成一个 $n$ 层的完全二叉树。公民 $i$ 的下属是 $2i$ 和 $2i +1$。最下层的公民即叶子节点的公民是平民，平民没有下属，最上层的是国王，中间是各级贵族。

现在这个王国爆发了战争，国王需要决定每一个平民是去种地以供应粮食还是参加战争，每一个贵族（包括国王自己）是去管理后勤还是领兵打仗。一个平民会对他的所有直系上司有贡献度，若一个平民 $i$ 参加战争，他的某个直系上司 $j$ 领兵打仗，那么这个平民对上司的作战贡献度为 $w_{ij}$。若一个平民 $i$ 种地，他的某个直系上司 $j$ 管理后勤，那么这个平民对上司的后勤贡献度为 $f_{ij}$，若 $i$ 和 $j$ 所参加的事务不同，则没有贡献度。为了战争需要保障后勤，国王还要求不多于 $m$ 个平民参加战争。

国王想要使整个王国所有贵族得到的贡献度最大，并把这件事交给了脸哥。但不幸的是，脸哥还有很多 deadline 没有完成，他只能把这件事又转交给你。你能帮他安排吗？
## 输入格式

第一行两个数 $n,m$。

接下来 $2^{n-1}$ 行，每行 $n-1$ 个数，第 $i$ 行表示编号为 $2^{n-1}-1+ i$ 的平民对其 $n-1$ 个直系上司的作战贡献度，其中第一个数表示对第一级直系上司，即编号为 $\frac{2^{n-1}-1+ i}{2}$ 的贵族的作战贡献度 $w_{ij}$，依次往上。

接下来 $2^{n-1}$ 行，每行 $n-1$ 个数，第 $i$ 行表示编号为 $2^{n-1}-1+ i$ 的平民对其 $n-1$ 个直系上司的后勤贡献度，其中第一个数表示对第一级直系上司，即编号为 $\frac{2^{n-1}-1+ i}{2}$ 的贵族的后勤贡献度 $f_{ij}$ ，依次往上。
## 输出格式

一行一个数表示满足条件的最大贡献值。
## 样例

### 样例输入 #1
```
3 4
503 1082
1271 369
303 1135
749 1289
100 54
837 826
947 699
216 389
```
### 样例输出 #1
```
6701
```
## 提示

对于 $100 \%$ 的数据，$2 \leq n \leq 10, \ m \leq 2^{n-1}, \ 0 \leq w_{ij}, f_{ij} \leq 2000$。


---

---
title: "[SCOI2011] 地板"
layout: "post"
diff: 省选/NOI-
pid: P3272
tag: ['动态规划 DP', '2011', '四川', 'O2优化', '广度优先搜索 BFS', '进制']
---
# [SCOI2011] 地板
## 题目描述

lxhgww 的小名叫“小 L”，这是因为他总是很喜欢 L 型的东西。

小 L 家的客厅是一个 $r\times c$ 的矩形，现在他想用 L 型的地板来铺满整个客厅，客厅里有些位置有柱子，不能铺地板。

现在小 L 想知道，用 L 型的地板铺满整个客厅有多少种不同的方案？

需要注意的是，如下图所示，L 型地板的两端长度可以任意变化，但不能长度为 $0$。

![](https://cdn.luogu.com.cn/upload/pic/4636.png)

铺设完成后，客厅里面所有没有柱子的地方都必须铺上地板，但同一个地方不能被铺多次。
## 输入格式

输入的第一行包含两个整数，$r$ 和 $c$，表示客厅的大小。

接着是 $r$ 行，每行 $c$ 个字符，字符要么是 `_`，要么是 `*`，`_` 表示对应的位置是空的，必须铺地板；`*` 表示对应的位置有柱子，不能铺地板。
## 输出格式

输出一行，包含一个整数，表示铺满整个客厅的方案数。由于这个数可能很大，只需输出它除以 $20110520$ 的余数。
## 样例

### 样例输入 #1
```
2 2
*_
__
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
3 3
 ___
 _*_
 ___
```
### 样例输出 #2
```
8
```
## 提示

#### 数据规模与约定
| 测试点编号 | 数据限制 |
| :----------: | :----------: |
| $1\sim 2$ | $1\le r\times c\le 25$ |
| $3\sim 5$ | $1\le r\times c\le 100$ 并且 （$r=2$ 或者 $c=2$） |
| $6\sim 10$ | $1\le r\times c\le 100$ |


---

---
title: "[SCOI2011] 棘手的操作"
layout: "post"
diff: 省选/NOI-
pid: P3273
tag: ['2011', '四川', '线段树', '深度优先搜索 DFS', '连通块']
---
# [SCOI2011] 棘手的操作
## 题目描述

有 $N$ 个节点，标号从 $1$ 到 $N$，这 $N$ 个节点一开始相互不连通。第i个节点的初始权值为 $a_i$，接下来有如下一些操作：
- `U x y`: 加一条边，连接第 $x$ 个节点和第 $y$ 个节点；
- `A1 x v`: 将第 $x$ 个节点的权值增加 $v$；
- `A2 x v`: 将第 $x$ 个节点所在的连通块的所有节点的权值都增加 $v$；
- `A3 v`: 将所有节点的权值都增加 $v$；
- `F1 x`: 输出第 $x$ 个节点当前的权值；
- `F2 x`: 输出第 $x$ 个节点所在的连通块中，权值最大的节点的权值；
- `F3`: 输出所有节点中，权值最大的节点的权值。
## 输入格式

输入的第一行是一个整数 $N$，代表节点个数。接下来一行输入 $N$ 个整数，$a_1,a_2,\dots,a_N$，代表 $N$ 个节点的初始权值。

再下一行输入一个整数 $Q$，代表接下来的操作数。

最后输入 $Q$ 行，每行的格式如题目描述所示。
## 输出格式

对于操作 `F1 x`,`F2 x`,`F3`，输出对应的结果，每个结果占一行。
## 样例

### 样例输入 #1
```
3
0 0 0
8
A1 3 -20
A1 2 20
U 1 3
A2 1 10
F1 3
F2 3
A3 -10
F3
```
### 样例输出 #1
```
-10
10
10
```
## 提示

对于 $30\%$ 的数据，保证 $N\le 100，Q\le 10000$；

对于 $80\%$ 的数据，保证 $N\le 100000$，$Q\le 100000$；

对于 $100\%$ 的数据，保证 $N\le 300000$，$Q\le 300000$；

对于所有的数据，保证输入合法，并且 $-1000\le v,a_1,a_2,\dots,a_N \le 1000$。


---

---
title: "[SCOI2013] 火柴棍数字"
layout: "post"
diff: 省选/NOI-
pid: P3283
tag: ['2013', '四川', '深度优先搜索 DFS', '容斥原理']
---
# [SCOI2013] 火柴棍数字
## 题目描述

Fish是一条生活在海里的鱼，有一天他很无聊，于是他去捡了人类扔进海里的垃圾，打算用这些来玩些什么。

他从捡回来的垃圾堆里找到了不少火柴棍，便把这些火柴棍拼成了一个长度为n 的十进制数，每个数字的拼法如下图所示

注意：每个数字占据的宽度和摆放方式是固定的，故以下情况均不合法。 ![](https://cdn.luogu.com.cn/upload/pic/4633.png)

 ![](https://cdn.luogu.com.cn/upload/pic/4634.png) 

拼完之后他好累，感觉再也不会拼了。他对拼出来的数大小不满意，希望通过移动一些火柴棍的位置来把这个数变得尽量大。

由于太累，他只能最多移动k 根火柴棍。而且由于数字的最低位放在墙边，他不能在该数的低位后面添加数字，但他可以在该数的前面添加数字。

你能帮他算出他移动火柴棍之后的数最大能是多大吗？

注意：火柴棍对于Fish 来说是很贵重的物品，所以不允许折断或丢弃火柴棍。

注意：火柴头的方向不影响数字的辨识，例如下面几种情况都是数字1

![](https://cdn.luogu.com.cn/upload/pic/4635.png)

## 输入格式

输入仅含一行，分别是长度为n 的十进制数x 和最多移动火柴棍的数量k。x 没有前导零。

## 输出格式

输出仅一行，表示移动火柴棍之后的最大数。

## 样例

### 样例输入 #1
```
3 2

```
### 样例输出 #1
```
17
```
### 样例输入 #2
```
3 3
```
### 样例输出 #2
```
71
```
## 提示

对于30% 的数据，1 <= n <= 10，0 <= k <= 10。

对于100% 的数据，1 <= n <= 500，0 <=k <=3500。



---

---
title: "[SCOI2016] 背单词"
layout: "post"
diff: 省选/NOI-
pid: P3294
tag: ['贪心', '2016', '四川', '深度优先搜索 DFS', '字典树 Trie']
---
# [SCOI2016] 背单词
## 题目描述

Lweb 面对如山的英语单词，陷入了深深的沉思：我怎么样才能快点学完，然后去玩三国杀呢？这时候睿智的凤老师从远处飘来，他送给了 Lweb 一本计划册和一大缸泡椒，他的计划册是长这样的：

| 序号    | 单词 |
| ------- | ---- |
| $1$     |      |
| $2$     |      |
| $\dots$ |      |
| $n-1$    |      |
| $n$     |      |

然后凤老师告诉 Lweb ，我知道你要学习的单词总共有 $n$ 个，现在我们从上往下完成计划表，对于一个序号为 $x$ 的单词（序号 $1,\dots ,x-1$ 都已经被填入）：

1. 如果存在一个单词是它的后缀，并且当前没有被填入表内，那他需要吃 $n \times n$ 颗泡椒才能学会；
2. 当它的所有后缀都被填入表内的情况下，如果在 $1,\dots,x-1$ 的位置上的单词都不是它的后缀，那么你吃 $x$ 颗泡椒就能记住它；
3. 当它的所有后缀都被填入表内的情况下，如果 $1,\dots,x-1$ 的位置上存在是它后缀的单词，所有是它后缀的单词中，序号最大为 $y$，那么你只要吃 $x-y$ 颗泡椒就能把它记住。

Lweb 是一个吃到辣辣的东西会暴走的奇怪小朋友，所以请你帮助 Lweb ，寻找一种最优的填写单词方案，使得他记住这 $n$ 个单词的情况下，吃最少的泡椒。

形式化题意：

你需要为 $n$ 个字符串排列一个顺序，每个字符串都会产生一定代价。

对于一个字符串 $s$，其所在位置为 $x$：

1. 如果存在至少一个其他字符串是 $s$ 后缀，且这个字符串的位置在 $s$ 后面， $s$ 将产生 $n \times n$ 的代价。

2. 如果不存在其他字符串是 $s$ 的后缀，则 $s$ 产生 $x$ 的代价。

3. 如果所有是 $s$ 后缀的字符串的位置都在 $s$ 的前面，若这些字符串的位置的最大值为 $y$ ， 则 $s$ 产生 $x-y$ 的代价。

为 $n$ 个字符串排列一个顺序，使总代价最小。
## 输入格式

输入一个整数 $n$ ，表示 Lweb 要学习的单词数。

接下来 $n$ 行，每行有一个单词（由小写字母构成，且保证任意单词两两互不相同）。
## 输出格式

Lweb 吃的最少泡椒数。
## 样例

### 样例输入 #1
```
2
a
ba
```
### 样例输出 #1
```
2
```
## 提示

$1\le n\le100000$，所有字符的长度总和 $1\le \sum|S| \le510000$。


---

---
title: "[SDOI2013] 森林"
layout: "post"
diff: 省选/NOI-
pid: P3302
tag: ['2013', '线段树', '山东', '深度优先搜索 DFS', '可持久化线段树']
---
# [SDOI2013] 森林
## 题目描述

小 Z 有一片森林，含有 $N$ 个节点，每个节点上都有一个非负整数作为权值。初始的时候，森林中有 $M$ 条边。

小Z希望执行 $T$ 个操作，操作有两类：

 - `Q x y k` 查询点 $x$ 到点 $y$ 路径上所有的权值中，第 $k$ 小的权值是多少。此操作保证点 $x$ 和点 $y$ 连通，同时这两个节点的路径上至少有 $k$ 个点。
 - `L x y` 在点 $x$ 和点 $y$ 之间连接一条边。保证完成此操作后，仍然是一片森林。

为了体现程序的在线性，我们把输入数据进行了加密。设 $lastans$ 为程序上一次输出的结果，初始的时候 $lastans$ 为 $0$。

对于一个输入的操作 `Q x y k`，其真实操作为 `Q x^lastans y^lastans k^lastans`。

对于一个输入的操作 `L x y`，其真实操作为 `L x^lastans y^lastans`。其中 `^` 运算符表示异或，等价于 Pascal 中的 `xor` 运算符。

请写一个程序来帮助小 Z 完成这些操作。
## 输入格式

第一行包含一个正整数 $\mathrm{testcase}$，表示当前测试数据的测试点编号。

第二行包含三个整数 $N,M,T$，分别表示节点数、初始边数、操作数。

第三行包含 $N$ 个非负整数表示 $N$ 个节点上的权值。

接下来 $M$ 行，每行包含两个整数 $x$ 和 $y$，表示初始的时候，点 $x$ 和点 $y$ 之间有一条无向边。

接下来 $T$ 行，每行描述一个操作，格式为 `Q x y k` 或者 `L x y`，其含义见题目描述部分。
## 输出格式

对于每一个第一类操作，输出一个非负整数表示答案。
## 样例

### 样例输入 #1
```
1
8 4 8
1 1 2 2 3 3 4 4
4 7
1 8
2 4
2 1
Q 8 7 3
Q 3 5 1
Q 10 0 0
L 5 4
L 3 2
L 0 7
Q 9 2 5
Q 6 1 6
```
### 样例输出 #1
```
2 
2
1
4
2
```
## 提示

**样例解释**

对于第一个操作 `Q 8 7 3`，此时 $lastans=0$，所以真实操作为 `Q 8^0 7^0 3^0`，也即 `Q 8 7 3`。点 $8$ 到点 $7$ 的路径上一共有 $5$ 个点，其权值为 $4\ 1\ 1\ 2\ 4$。这些权值中，第三小的为 $2$，输出 $2$，$lastans$ 变为 $2$。

对于第二个操作 `Q 3 5 1` ，此时 $lastans=2$，所以真实操作为 `Q 3^2 5^2 1^2`，也即 `Q 1 7 3`。点 $1$ 到点 $7$ 的路径上一共有 $4$ 个点，其权值为 $1\ 1\ 2\ 4$ 。这些权值中，第三小的为 $2$，输出 $2$，$lastans$ 变为 $2$。之后的操作类似。

-----
**数据范围**

| 测试点编号  | $N,M,T$ 的上界 |  `L` 操作   |  `Q` 操作  | 形态 |
| :---------: | :------------: | :---------: | :--------: | :--: |
|     $1$     |      $20$      |     N/A     |    N/A     | N/A  |
|     $2$     |     $200$      |     N/A     |    N/A     | N/A  |
|  $3\sim 4$  | $4\times 10^4$ | 无 `L` 操作 |    N/A     |  链  |
|  $5\sim 6$  | $8\times 10^4$ | 无 `L` 操作 |    N/A     |  链  |
|  $7\sim 9$  | $8\times 10^4$ | 无 `L` 操作 | 保证 $k=1$ | N/A  |
| $10\sim 11$ | $4\times 10^4$ |     N/A     | 保证 $k=1$ | N/A  |
| $12\sim 13$ | $8\times 10^4$ |     N/A     | 保证 $k=1$ | N/A  |
| $14\sim 15$ | $4\times 10^4$ | 无 `L` 操作 |    N/A     | N/A  |
| $16\sim 17$ | $8\times 10^4$ | 无 `L` 操作 |    N/A     | N/A  |
|    $18$     | $4\times 10^4$ |     N/A     |    N/A     | N/A  |
| $19\sim 20$ | $8\times 10^4$ |     N/A     |    N/A     | N/A  |

注：N/A 表示没有特殊性。

对于 $100\%$ 的测试数据，所有节点的编号在 $1\sim N$ 的范围内。节点上的权值 $\le 10^9$。$M<N$。


---

---
title: "[SDOI2015] 寻宝游戏"
layout: "post"
diff: 省选/NOI-
pid: P3320
tag: ['2015', '山东', '深度优先搜索 DFS', '最近公共祖先 LCA', '虚树']
---
# [SDOI2015] 寻宝游戏
## 题目描述

小 B 最近正在玩一个寻宝游戏，这个游戏的地图中有 $N$ 个村庄和 $N-1$ 条道路，并且任何两个村庄之间有且仅有一条路径可达。游戏开始时，玩家可以任意选择一个村庄，瞬间转移到这个村庄，然后可以任意在地图的道路上行走，若走到某个村庄中有宝物，则视为找到该村庄内的宝物，直到找到所有宝物并返回到最初转移到的村庄为止。

小 B 希望评测一下这个游戏的难度，因此他需要知道玩家找到所有宝物需要行走的最短路程。但是这个游戏中宝物经常变化，有时某个村庄中会突然出现宝物，有时某个村庄内的宝物会突然消失，因此小 B 需要不断地更新数据，但是小 B 太懒了，不愿意自己计算，因此他向你求助。为了简化问题，我们认为最开始时所有村庄内均没有宝物。
## 输入格式

第一行，两个整数 $N,M$，其中 $M$ 为宝物的变动次数。

接下来的 $N-1$ 行，每行三个整数 $x,y,z$，表示村庄 $x,y$ 之间有一条长度为 $z$ 的道路。

接下来的 $M$ 行，每行一个整数 $t$，表示一个宝物变动的操作。若该操作前村庄 $t$ 内没有宝物，则操作后村庄内有宝物；若该操作前村庄 $t$ 内有宝物，则操作后村庄内没有宝物。
## 输出格式

$M$ 行，每行一个整数，其中第 $i$ 行的整数表示第 $i$ 次操作之后玩家找到所有宝物需要行走的最短路程。若只有一个村庄内有宝物，或者所有村庄内都没有宝物，则输出 `0`。
## 样例

### 样例输入 #1
```
4 5
1 2 30
2 3 50
2 4 60
2
3
4
2
1
```
### 样例输出 #1
```
0
100
220
220
280
```
## 提示

- 对于 $10\%$ 的数据，$1 \leq N \leq 100, 1 \leq M \leq 100$；
- 对于 $20\%$ 的数据，$1 \leq N \leq 1000, 1 \leq M \leq 1000$；
- 对于另外 $15\%$ 的数据，每个村庄最多成为两条道路的端点；
- 对于 $100\%$ 的数据，$1 \leq N \leq 100000,\ 1 \leq M \leq 100000,\ 1 \leq z \leq 10^9$。


---

---
title: "[ZJOI2014] 璀灿光华"
layout: "post"
diff: 省选/NOI-
pid: P3342
tag: ['2014', '浙江', '枚举', '广度优先搜索 BFS', '图论建模']
---
# [ZJOI2014] 璀灿光华
## 题目描述

金先生有一个女朋友没名字。她勤劳勇敢、智慧善良。金先生很喜欢她。为此，金先生用 $a^3$ 块 $1\times 1 \times 1$ 的独特的水晶制作了一个边长为 $a$ 的水晶立方体，他要将这个水晶立方体送给他见过最单纯善良的她。

由于水晶立方体太太，不好运送，金先生还是将它拆开来送出。他相信拼好这个水晶立方难不倒聪明的她。

没名字收到了礼物后果然不一会儿就根据说明将水晶立方体拼好了。没名字发现，有 $n$ 块水晶在漆黑安静的夜晚会随机以等概率向上下左右前后六个方向的一个发出穿透光。被光照到的水晶显得格外好看。没名字给每一块不会发光的水晶定义了一个好看程度。水晶立方体在夜晚中的好看程度就是每块被光照到的水晶的好看程度之和。没名字想知道，水晶立方体在夜晚中的好看程度的最小值和最大值。
## 输入格式

第一行是 $a$，表示水晶立方体的边长。
接下来 $a^3$ 行，每行若干整数。
第一个数 $g_i$ 表示第 $i$ 块水晶的好看程度。如果 $g_i=0$，代表这块水晶会发光。接下来 $3\sim 6$ 个整数，代表与这块水晶有共同面的水晶编号。
## 输出格式

两个整数，代表水晶立方体在夜晚好看程度的最小值与最大值。
## 样例

### 样例输入 #1
```
2
0 7 2 3
0 8 1 4
4 5 4 1
8 6 3 2
16 3 6 7
32 4 5 8
1 1 8 5
2 2 7 6
```
### 样例输出 #1
```
0 12
```
## 提示

对于所有数据，$1<a\leq 70$，$g_i<10^6$，$n\leq 8$。



---

---
title: "[POI 2006] ZAB-Frogs"
layout: "post"
diff: 省选/NOI-
pid: P3438
tag: ['2006', '二分', '单调队列', 'POI（波兰）', '广度优先搜索 BFS']
---
# [POI 2006] ZAB-Frogs
## 题目描述

A scourge of frogs destroying all the crop has started in Byteotia. A farmer named Byteasar has decided to fight the vermin with peculiar "scarefrogs", that he has set up at certain points of his field. While moving from one place to another, every frog tries to keep as far of them as possible, i.e. maximizes the distance to the closest scarefrog.

The field that belongs to Byteasar has rectangular shape. The frogs leap in directions parallel to the field's sides and their leaps are unitary (of length 1). The scarefrogs-distance, for a given frog's route, is the minimum of all distances from all scarefrogs at all inter-leap-points of the route.

Byteasar already knows the most common starting and destination points of the frogs' routes, therefore he experiments with various deployments of the scarefrogs. He asks you for help, namely he would like you to write a programme that calculates the maximum (over all routes) scarefrogs-distance for a given deployment of scarefrogs - which we call in short the frogshold distance.

TaskWrite a programme that:

reads from the standard input the size of the field, the coordinates of the screfrogs and the source and target position of a frog,determines the frogshold distance (the maximum scarefrogs-distance a frog may achieve while still being able to reach the target point)writes the square of this number to the standard output.

给定一个网格图，其中有一些坏点，要求使起点到终点的路径上的所有点到离该点最近的坏点的最小距离距离最大，求这个最大值。

## 输入格式

The first line of the input contains two integers: $w_x$ and $w_y$ separated by a single space - the breadth and length of the field ($2 \le w_x, w_y \le 1000$). The second line of the input contains four integers: $p_x$, $p_y$, $k_x$ and $k_y$ separated by single spaces; $(p_x, p_y)$ is the initial position of the frog, $(k_x, k_y)$is the target (final) position of the frog ($1 \le p_x, k_x \le w_x$, $1 \le p_y, k_y \le w_y$). The third line of the standard input contains one integer $n$ - these are the coordinates of the ith scarefrog ($1 \le n \le w_x \cdot w_y$). No two scarefrogs occupy the same position and none of them is at the point $(p_x, p_y)$ nor $(k_x, k_y)$.

## 输出格式

In the first and only line of the standard output one integer should be written, namely the square of the frogshold distance. If the frog cannot avoid leaping directly on some scarefrog the result is 0.

## 样例

### 样例输入 #1
```
5 5
1 1 5 5
2
3 3
4 2
```
### 样例输出 #1
```
4
```


---

---
title: "[POI 2006] SZK-Schools"
layout: "post"
diff: 省选/NOI-
pid: P3440
tag: ['2006', 'POI（波兰）', '深度优先搜索 DFS', '最小割']
---
# [POI 2006] SZK-Schools
## 题目描述

B 国境内有 $n$ 所学校，每所学校都有一个 $1 \sim n$ 的编号。

由于管理过于宽松，可能存在两个学校同时用一个编号的情况，当然也存在一个编号没有学校用的情况。

现在国王决定重新给所有学校编号，使得任意两个学校的编号不同。

当然，改变编号是一个很繁重的工作，学校不希望自己的编号改变太多。每个学校都有一个可以接受的新编号区间 $[a,b]$，以及改变编号的单位成本 $k$。如果一个学校的旧编号为 $m$，新编号为 $m'$，那么给这个学校改变编号的成本即为 $k \times |m'-m|$。

现在你需要告诉国王完成编号更新的最低成本是多少，或者说明这是不可能的。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，每行四个整数 $m_i,a_i,b_i,k_i$，代表 $i$ 号学校的旧编号为 $m_i$，新编号的范围为 $[a_i,b_i]$，改变编号的单位成本为 $k_i$。
## 输出格式

如果不存在一种方案，使得任意两个学校的编号不同，输出 `NIE`。

否则输出一个整数，代表最小成本。
## 样例

### 样例输入 #1
```
5
1 1 2 3
1 1 5 1
3 2 5 5
4 1 5 10
3 3 3 1
```
### 样例输出 #1
```
9
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le a_i \le m_i \le b_i \le n \le 200$，$1\le k_i \le 1000$。


---

---
title: "[POI 2007] ODW-Weights"
layout: "post"
diff: 省选/NOI-
pid: P3462
tag: ['搜索', '贪心', '2007', 'POI（波兰）', '进制']
---
# [POI 2007] ODW-Weights
## 题目描述

While moving to a new compound the Byteotian Institute of Experimental Physics has encountered a logisticalproblem - the transfer of its vast collection of precision weights turned out to be non-trivial.

The Institute has a certain number of containers of limited strength at its disposal. As many weightsas possible are to be put into the containers, the remaining ones will be discarded. There is no limit onthe number of weights to be put in a container apart from the requirement of not exceeding its strength. Acontainer may also be empty.

Any two weights in the Institute have a peculiar property: the mass of one of them is an integer multipleof the mass of the other. Particularly, they may have the same mass.

TaskWrite a programme which:

reads the durabilities of the containers and masses of the weights from the standard input,        determines the maximal number of weights that can be put in the containers,        writes the outcome to the standard output.

## 输入格式

The first line of the standard input contains two integers $n$ and $m$($1\le n,m\le 100\ 000$), separated by a singlespace, denoting respectively: the number of containers and the number of weights. The second line of thestandard input consists of $n$ integers $w_i$ ($1\le w_i\le 1\ 000\ 000\ 000$ for $1\le i\le n$), separated by single spaces,denoting the strengths of containers in milligrammes. In the third line there are $m$ integers $m_j$($1\le m_j\le 1\ 000\ 000\ 000$) for $1\le j\le m$), separated by single spaces, denoting masses of the weights in milligrammes.

## 输出格式

The first and only line of the standard output should contain a single integer -the maximal number ofweights that can be placed in the containers without exceeding their durability.

## 样例

### 样例输入 #1
```
2 4
13 9
4 12 2 4
```
### 样例输出 #1
```
3
```
## 题目翻译

在 byteotian 公司搬家的时候，他们发现他们的 $m$ 个大量的精密砝码的搬运是一件恼人的工作。公司有 $n$ 个固定容量的容器可以装这些砝码。他们想装尽量多的砝码以便搬运，并且丢弃剩下的砝码。

每个容器可以装的砝码数量没有限制，但是他们能够装的总重量不能超过每个容器的限制。第 $i$ 个容器允许装下的砝码总重为 $w_i$。一个容器也可以不装任何东西。

此外，这些砝码有一个特征。对于任意两个砝码 $i,j$，它们的重量成倍数关系，即 $m_i\mid m_j$ 或者 $m_j\mid m_i$ 或者两者都成立（即重量相等）。


---

---
title: "[POI 2008] TRO-Triangles"
layout: "post"
diff: 省选/NOI-
pid: P3476
tag: ['计算几何', '2008', 'POI（波兰）', '深度优先搜索 DFS', '叉积']
---
# [POI 2008] TRO-Triangles
## 题目描述

$n$ pairwise disjoint points in the plane are given ($n\ge 3$).

There are $\dfrac{n(n-1)(n-2)}{6}$ triangles whose    vertices are some pairwise different points among them    (including degenerate triangles, i.e. ones whose vertices are collinear).

We want to calculate the sum of areas of all the triangles with vertices    in the given points.

Those parts of the plane that belong to many triangles are to be calculated    multiple times. We assume that the area of degenerate triangles (i.e. those    with collinear vertices) is zero.

<Task>

Write a programme that:

reads from the standard input the coordinates of the points in the plane,                 determines the sum of the areas of all the triangles with vertices in       the given points,                  prints out the result to the standard output.



## 输入格式

In the first line of the standard input there is one integer $n$ ($3\le n\le 3000$) denoting the number of selected points.

Each of the following $n$ lines contains two integers $x_i$ and $y_i$ ($0\le x_i,y_i\le 10^4$) separated by a single space and denoting   the coordinates of the $i^\mathrm{th}$ point (for $i=1,2,\cdots,n$).

No pair (ordered) of coordinates appears more than once.

## 输出格式

In the first and only line of the standard output there should be one   real number equal to the sum of the areas of all the triangles with   vertices in the given points. The outcome should be printed out with   exactly one digit after dot and should not differ from the correct value   by more than $0.1$.

## 样例

### 样例输入 #1
```
5
0 0
1 2
0 2
1 0
1 1

```
### 样例输出 #1
```
7.0

```
## 题目翻译

给定平面上的一些点，求这些点能组成的所有三角形的面积之和。


---

---
title: "[POI 2009] BAJ-The Walk of Bytie-boy"
layout: "post"
diff: 省选/NOI-
pid: P3485
tag: ['动态规划 DP', '2009', 'POI（波兰）', 'Special Judge', '广度优先搜索 BFS']
---
# [POI 2009] BAJ-The Walk of Bytie-boy
## 题目背景

[English Edition](/paste/9lmt83m9)
## 题目描述

给出一张 $n$ 个点 $m$ 条边的有向图，每条边上有一个字母，并给出一个整数 $d$ 和一个序列 $s_1, s_2, \dots, s_d$。  

你需要对每一个 $i(1\le i<n)$ 求出一条从 $s_i$ 到 $s_{i+1}$ 的最短路径满足这条路径上的边上的字母连起来后是回文的。  

不保证每个点最多只在 $s$ 中出现一次。
## 输入格式

第一行两个整数 $n, m$。

之后 $m$ 行，每行两个整数 $x_i, y_i$ 与一个字母 $c_i$，表示有一条从 $x_i$ 到 $y_i$ 的边，这条边上的字母是 $c_i$。

之后一行一个整数 $d$。

之后一行 $d$ 个整数， 表示序列 $s$。
## 输出格式

输出共 $d-1$ 行，第 $i$ 行输出一条从 $s_i$ 到 $s_{i+1}$ 的满足条件的路径。  

若不存在这样的路径，则输出 `-1`，否则输出这条路径上的所有字母。  

如果有多条满足条件的路径，任意输出一条即可。
## 样例

### 样例输入 #1
```
6 7
1 2 a
1 3 x
1 4 b
2 6 l
3 5 y
4 5 z
6 5 a
3
1 5 3

```
### 样例输出 #1
```
3 ala
-1

```
## 提示

对于 $100\%$ 的数据，$2\le n\le 400$，$1\le m\le 6\times10^4$，$1\le x_i,y_i\le n$，$2\le d\le100$，$1\le s_i\le n$。

同时保证不会出现重边与自环。


---

---
title: "[POI 2012] PEN-Salaries"
layout: "post"
diff: 省选/NOI-
pid: P3542
tag: ['贪心', '2012', 'POI（波兰）', '深度优先搜索 DFS']
---
# [POI 2012] PEN-Salaries
## 题目描述

The Byteotian Software Corporation (BSC) has $n$ employees.

In BSC's strict hierarchy, each employee has a direct supervisor, except the CEO, to whom all other BSC employees answer, directly or not.

Each employee has a unique monthly salary, and all their salaries range from 1 to $n$ bythalers.

Each supervisor earns more than each of their subordinates.

According to Byteotian law, the salaries of employees on certain posts may be publicly disclosed.

Furthermore, if the salary of an employee is disclosed, then the salary of their supervisor is also disclosed.

The Byteotian Internal Revenue Anti-Corruption Service (BIRAS) has decided to investigate BSC.

Before BIRAS enters BSC with a warrant, they intend to learn the salaries of all BSC employees    that are not disclosed but can be determined from those that are disclosed.
## 输入格式

In the first line of the standard input a single integer $n$ ($1\le n\le 1\ 000\ 000$) is given that denotes the number of BSC employees.

The employees have id's that range from 1 to $n$.

The $n$ lines that follow provide information on these employees.

The line no. $i+1$ describes the employee no. $i$ by two integers $p_i$ and $z_i$ ($1\le p_i\le n$, $0\le z_i\le n$), separated by a single space.

The number $p_i$ is the id of the direct supervisor of the employee $i$.If $p_i=i$, then $i$ is the CEO of BSC. If $z_i>0$,then that is the salary of the employee $i$.If, on the other hand,$z_i=0$, then the salary of employee $i$ is not disclosed.Those $z_i$'s that are positive are also pairwise different.

The input data will always be such that there is at least one assignment of salaries to employees consistent with them, i.e., with the hierarchy and the partial assignment that they provide.

In tests worth 54% of the total points the condition $n\le 10\ 000$  holds in addition.

## 输出格式

Your program should print $n$ lines to the standard output, each line holding a single integer.

If the employee $i$'s salary is disclosed or can be inferred from disclosed salaries, then the $i$-th line should hold employee $i$'s salary.

Otherwise the $i$-th line should contain $0$.

## 样例

### 样例输入 #1
```
10
2 2
2 10
1 0
2 9
2 5
4 0
6 0
6 0
5 0
5 0
```
### 样例输出 #1
```
2
10
1
9
5
8
0
0
0
0
```
## 题目翻译

### 题目描述

**译自 POI 2012 Stage 3. Day 1「[Salaries](https://szkopul.edu.pl/problemset/problem/_qn633f6DVAHRkv0OX3LQaph/site/?key=statement)」**

有一个 $n$ 个点的有根树，每个点的权值分别为 $1 \ldots n$，且大于其儿子的权值。其中一部分点的权值是公开的，且每个权值已知的点的父亲权值也一定已知。求能够根据已知信息推算出来的权值未知的点的权值。

### 输入格式

第一行一个整数 $n$，表示点的个数。

接下来 $n$ 行每行两个整数 $p_i, z_i (1 \le p_i \le n,0 \le z_i \le n)$，其中 $p_i$ 表示结点 $i$ 的父亲，$z_i$ 表示结点 $i$ 的权值。如果 $z_i = 0$，则该点权值未知，否则该点权值为 $z_i$。

### 输出格式

输出 $n$ 行，每行一个整数，表示 $i$ 点的权值。如果该点权值已知或可以推算出来，输出该点权值，否则输出 $0$。

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/bjf4memv.png)

### 数据范围

对于 $54\%$ 的数据有 $n \le 10^4$.

对于所有数据有 $1 \le n \le 10^6$。

翻译来自于 [LibreOJ](https://loj.ac/p/2700)。


---

---
title: "[POI 2012] BEZ-Minimalist Security"
layout: "post"
diff: 省选/NOI-
pid: P3544
tag: ['2012', 'POI（波兰）', '广度优先搜索 BFS']
---
# [POI 2012] BEZ-Minimalist Security
## 题目描述

A map of Mafiatown's road network is given.

The network consists of intersections and bidirectional streets that connect them.

The streets cross only at the intersections, but they may lead through tunnels or flyovers.

Each pair of intersections is linked by at most one street.

At every intersection $v$ there is a police station manned by $p(v)$ policemen.

A street linking the intersections $u$ and $v$ is considered safe if there are at least $b(u,v)$ policemen in total in the two stations at the streets ends. Initially    $p(u)+p(v)\ge b(u,v)$ holds for every street.

However, due to an ongoing crisis the mayor Byteasar has ordained the Minimalist Security Act (MSA), which states that:

a certain number (which may be zero) of policemen is to be laid off from each police station        (we denote the number of policemen laid off from the station at the intersection $v$ by $z(v)$),                  after the layoff, the total number of the policemen at both ends of every street connecting some two intersections,        say $u$ and $v$, should equal $b(u,v)$ exactly, i.e.:

$p(u)-z(u)+p(v)-z(v)=b(u,v)$ These rules do not determine uniquely how many policemen are to be laid off.

Byteasar wonders what is the minimum and the maximum number of laid off policemen    (the sum of $z$ values over all intersections) that complies with aforementioned rules.
## 输入格式

In the first line of the standard input there are two integers, $n$ and $m$ ($1\le n\le 500\ 000$, $0\le m\le 3\ 000\ 000$), separated by a single space, that denote    the number of intersections and the number of streets in Mafiatown, respectively.

The intersections are numbered from 1 to $n$.

In the second line $n$ nonnegative integers separated by single spaces are given.

These are the numbers of policemen currently employed at successive stations, i.e., the values $p(1),p(2),\cdots,p(n)$($0\le p(i)\le 10^6$).

Each of the following $m$ lines describes a single bidirectional street. Such description consists of three integers,$u_i,v_i,b(u_i,v_i)$($1\le u_i,v_i\le n$,$u_i\ne v_i$,$0\le b(u_i,v_i)\le 10^6$), separated by single spaces, that denote respectively: the numbers of the intersections at the ends of the street and the minimum total number of policemen that have to man the stations at those intersections.

## 输出格式

If Byteasar's ordinance can be carried out, your program should print, on the standard output,    exactly one line with two integers separated by a single space.

The numbers should be the minimum and the maximum number of policemen that should be laid off    in order to carry out the ordinance.

If carrying out the ordinance is impossible, your program should print a single line containing    the word NIE (Polish for no).

## 样例

### 样例输入 #1
```
3 2
5 10 5
1 2 5
2 3 3
```
### 样例输出 #1
```
12 15
```
## 题目翻译

### 题目描述

**译自 POI 2012 Stage 3. Day 2「[Bezpieczeństwo minimalistyczne](https://szkopul.edu.pl/problemset/problem/aSbIC_LB4H-CGMYPEVue5jFw/site/?key=statement)」**

给定一张无向图，点有点权 $p(v)$，边有边权 $b(u,v)$，初始时保证对每条边有 $p(u) + p(v) \ge b(u,v)$。

现在需要减少一部分点的点权，使得对每条边都恰有 $p(u) + p(v) = b(u,v)$.

求整张图减少的点权和的最小值和最大值。

### 输入格式

第一行两个整数 $n$ 和 $m$（$1 \le n \le 500\ 000,0 \le m \le 3\ 000\ 000$），表示图的点数和边数。

接下来一行 $n$ 个非负整数 $p(1),p(2),\ldots,p(n) (0 \le p(i) \le 10^6)$，表示点权。

接下来 $m$ 行每行三个整数 $u_i, v_i, b(u_i, v_i)$（$1 \le u_i,v_i \le n,u_i \neq v_i,0 \le b(u_i,v_i) \le 10^6$），表示边和边权。

### 输出格式

如果存在符合条件的方案，输出一行两个整数，表示整张图减少的点权和的最小值和最大值。

如果不存在，输出 `NIE`.

### 数据范围

对于 $56\%$ 的数据有 $n \le 2000,m \le 8000$.

对于所有数据有 $1 \le n \le 500\ 000,0 \le m \le 3\ 000\ 000$.

翻译来自于 [LibreOJ](https://loj.ac/p/2702)。


---

---
title: "[POI 2014] DOO-Around the world"
layout: "post"
diff: 省选/NOI-
pid: P3575
tag: ['搜索', '2014', '倍增', 'POI（波兰）', '栈']
---
# [POI 2014] DOO-Around the world
## 题目描述

After trying hard for many years, Byteasar has finally received a pilot license.

To celebrate the fact, he intends to buy himself an airplane and fly around the planet  3-SATurn (as you may have guessed, this is the planet on which Byteotia is located).

Specifically, Byteasar plans to fly along the equator.

Unfortunately, the equator is rather long, necessitating refuels.

  The flight range (on full tank) of each aircraft is known.

There is a number of airports along the equator, and a plane can be refueled when it lands on one.

Since buying an airplane is a big decision, Byteasar asks your help.

He is about to present you with a list of different plane models he is considering.

Naturally, these differ in their flight range.

For each plane model, he would like to know the minimum number of landings  (including the final one) he would have to make in order to complete the journey.

Note that for each airplane model, the journey may start at a different airport.

通过几年的努力，Byteasar最终拿到了飞行员驾驶证。为了庆祝这一事实，他打算买一架飞机并且绕Byteotia星球赤道飞行一圈。但不幸的是赤道非常长所以需要中途加几次油。现在已知赤道上面所有飞机场，所有飞机从飞机场起飞降落也可以加油。因为买飞机是个十分重大的决定，Byteasar决定寻求你的帮助。他将会让你模拟不同的飞行路线。自然这些飞机一次能走的航程是不同的。对于每次模拟，他想要知道最少需要降落多少次（包括最后一次）。需要注意的是起点可以任意选取。

## 输入格式

The first line of the standard input contains two integers $n$ and $s$ ($2\le n\le 1\ 000\ 000$, $1\le s\le 100$),separated by a single space,  denoting the number of airports along the equator and the number of airplane models Byteasar is considering.

The second line contains $n$ positive integers $l_1,l_2,\cdots,l_n$ ($l_1+l_2+\cdots+l_n\le 10^9$), separated by single spaces, specifying the distances between successive airports along the equator.

The number $l_i$ is the distance between the $i$-th and $(i+1)$-st (or $n$-th and first if $i=n$) in kilometers.

The third line contains $s$ integers $d_1,d_2,\cdots,d_s$ ($1\le d_i\le l_1+l_2+\cdots+l_n$), separated by single spaces. The number $d_i$ is the $i$-th airplane model's flight range in kilometers, i.e., the maximum distance it can fly before landing and refueling.

## 输出格式

Your program should print $s$ lines to the standard output: the $i$-th of these should contain a single integer, namely, the minimum lumber of flight segments (and thus also landings) necessary to fly the $i$-th airplane around the planet 3-SATurn along the equator, starting at an airport of choice, or the word NIE (Polish for no) if it is impossible to complete the journey with this airplane.

## 样例

### 样例输入 #1
```
6 4
2 2 1 3 3 1
3 2 4 11

```
### 样例输出 #1
```
4
NIE
3
2

```
## 提示

通过几年的努力，Byteasar最终拿到了飞行员驾驶证。为了庆祝这一事实，他打算买一架飞机并且绕Byteotia星球赤道飞行一圈。但不幸的是赤道非常长所以需要中途加几次油。现在已知赤道上面所有飞机场，所有飞机从飞机场起飞降落也可以加油。因为买飞机是个十分重大的决定，Byteasar决定寻求你的帮助。他将会让你模拟不同的飞行路线。自然这些飞机一次能走的航程是不同的。对于每次模拟，他想要知道最少需要降落多少次（包括最后一次）。需要注意的是起点可以任意选取。



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
title: "[APIO2007] 动物园"
layout: "post"
diff: 省选/NOI-
pid: P3622
tag: ['2007', 'APIO', '枚举', '深度优先搜索 DFS', '状压 DP']
---
# [APIO2007] 动物园
## 题目描述

新建的圆形动物园是亚太地区的骄傲。圆形动物园坐落于太平洋的一个小岛上，包含一大圈围栏，每个围栏里有一
种动物。如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/8pr43p86.png)

你是动物园的公共主管。你要做的是，让每个来动物园的人都尽可能高兴。今天有一群小朋友来动物园参观，你希望能让他们在动物园度过一段美好的时光。但这并不是一件容易的事——有的动物有一些小朋友喜欢，有的动物有一些小朋友害怕。如，Alex 喜欢可爱的猴子和考拉，而害怕拥牙齿锋利的狮子。而 Polly 会因狮子有美丽的鬃毛而喜欢它，但害怕有臭味的考拉。你可以选择将一些动物从围栏中移走以使得小朋友不会害怕。但你不能移走太多动物，否则小朋友们就没有动物可看了。每个小朋友站在大围栏圈的外面，可以看到连续的 $5$ 个围栏。你得到了所有小朋友喜欢和害怕的动物信息。当下面两处情况之一发生时，小朋友就会高兴：
- 至少有一个他害怕的动物被移走
- 至少有一个他喜欢的动物没被移走

例如，考虑下图中的小朋友和动物：

![](https://cdn.luogu.com.cn/upload/image_hosting/n69iqfv6.png)

- 假如你将围栏 $4$ 和 $12$ 的动物移走。Alex 和 Ka-Shu 将很高兴，因为至少有一个他们害怕的动物被移走了。这也会使 Chaitanya 高兴，因为他喜欢的围栏  $6$ 和 $8$ 中的动物都保留了。但是，Polly 和 Hwan 将不高兴，因为他们看不到任何他们喜欢的动物，而他们害怕的动物都还在。这种安排方式使得三个小朋友高兴。
- 现在，换一种方法，如果你将围栏 $4$ 和 $6$ 中的动物移走，Alex 和 Polly 将很高兴，因为他们害怕的动物被移走了。Chaitanya 也会高兴，虽然他喜欢的动物 $6$ 被移走了，他仍可以看到围栏 $8$ 里面他喜欢的动物。同样的 Hwan 也会因可以看到自己喜欢的动物 $12$ 而高兴。唯一不高兴的只有 Ka-Shu。
- 如果你只移走围栏 $13$ 中的动物，Ka-Shu 将高兴，因为有一个他害怕的动物被移走了，Alex, Polly, Chaitanya 和 Hwan 也会高兴，因为他们都可以看到至少一个他们喜欢的动物。所以有 $5$ 个小朋友会高兴。这种方法使得了最多的小朋友高兴。
## 输入格式

输入的第一行包含两个整数 $N$，$C$，用空格分隔。

$N$ 是围栏数（$10 \le N \le 10^4$），$C$ 是小朋友的个数（$1 \le C \le 5\times 10^4$）。

围栏按照顺时针的方向编号为 $1,2,3,\cdots,N$。

接下来的 $C$ 行，每行描述一个小朋友的信息，以下面的形式给出： $E, F, L ,X_1, X_2 ,\cdots ,X_F ,Y_1 ,Y_2 ,\cdots ,Y_L$。 

其中： $E$ 表示这个小朋友可以看到的第一个围栏的编号（$1 \le E \le N$），换句话说，该小朋友可以看到的围栏为 $E$， $E+1$， $E+2$， $E+3$， $E+4$。

注意，如果编号超过 $N$ 将继续从 $1$ 开始算。

如：当 $N=14$，$ E=13$ 时，这个小朋友可以看到的围栏为 $13,14,1, 2$ 和 $3$。

$F$ 表示该小朋友害怕的动物数。

$L$ 表示该小朋友喜欢的动物数。

围栏 $X_1, X_2, \cdots, X_F$ 中包含该小朋友害怕的动物。

围栏 $Y_1, Y_2, \cdots, Y_L$ 中包含该小朋友喜欢的动物。 

$X_1, X_2, \cdots, X_F, Y_1, Y_2, \cdots, Y_L$ 是两两不同的整数，而且所表示的围栏都是该小朋友可以看到的。

小朋友已经按照他们可以看到的第一个围栏的编号从小到大的顺序排好了（这样最小的 $E$ 对应的小朋友排在第一个，最大的 $E$ 对应的小朋友排在最后一个）。

注意可能有多于一个小朋友对应的 $E$ 是相同的。
## 输出格式

仅输出一个数，表示最多可以让多少个小朋友高兴。

## 样例

### 样例输入 #1
```
14 5 
2 1 2 4 2 6 
3 1 1 6 4 
6 1 2 9 6 8
8 1 1 9 12 
12 3 0 12 13 2 
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
12 7 
1 1 1 1 5 
5 1 1 5 7 
5 0 3 5 7 9 
7 1 1 7 9 
9 1 1 9 11 
9 3 0 9 11 1
11 1 1 11 1
```
### 样例输出 #2
```
6
```
## 提示

**数据范围**
对于 $100\%$ 的数据，$10 \le N \le 10^4$，$1 \le C \le 5\times 10^4$，$1 \le E \le N$。

**样例说明**
- 第一个样例是题目描述中的例子，所有的 $C=5$ 个小朋友都能高兴。
- 第二个样例是一个不能使得所有 $C=7$ 个小朋友都高兴的例子。


---

---
title: "[APIO2010] 巡逻"
layout: "post"
diff: 省选/NOI-
pid: P3629
tag: ['2010', 'APIO', '深度优先搜索 DFS', '树的直径']
---
# [APIO2010] 巡逻
## 题目描述

在一个地区中有 $n$ 个村庄，编号为 $1, 2, \dots, n$。有 $n-1$ 条道路连接着这些村庄，每条道路刚好连接两个村庄，从任何一个村庄，都可以通过这些道路到达其他任何一个村庄。每条道路的长度均为 $1$ 个单位。为保证该地区的安全，巡警车每天要到所有的道路上巡逻。警察局设在编号为 $1$ 的村庄里，每天巡警车总是从警察局出发，最终又回到警察局。下图表示一个有 $8$ 个村庄的地区，其中村庄用圆表示（其中村庄 $1$ 用黑色的圆表示），道路是连接这些圆的线段。为了遍历所有的道路，巡警车需要走的距离为 $14$ 个单位，每条道路都需要经过两次。

![](https://cdn.luogu.com.cn/upload/pic/4401.png)

为了减少总的巡逻距离，该地区准备在这些村庄之间建立 $K$ 条新的道路，每条新道路可以连接任意两个村庄。两条新道路可以在同一个村庄会合或结束，如下面的图例 (c)。一条新道路甚至可以是一个环，即其两端连接到同一个村庄。由于资金有限，$K$ 只能是 $1$ 或 $2$。同时，为了不浪费资金，每天巡警车必须经过新建的道路正好一次。下图给出了一些建立新道路的例子：

![](https://cdn.luogu.com.cn/upload/pic/4402.png) 

在 (a) 中，新建了一条道路，总的距离是 $11$。在 (b) 中，新建了两条道路，总的巡逻距离是 $10$。在 (c) 中，新建了两条道路，但由于巡警车要经过每条新道路正好一次，总的距离变为了 $15$。试编写一个程序，读取村庄间道路的信息和需要新建的道路数，计算出最佳的新建道路的方案使得总的巡逻距离最小，并输出这个最小的巡逻距离。


## 输入格式

第一行包含两个整数 $n, K(1 ≤ K ≤ 2)$。接下来 $n-1$ 行，每行两个整数 $a,b$，表示村庄 $a$ 与 $b$ 之间有一条道路 $(1 ≤ a, b ≤ n)$。

## 输出格式

输出一个整数，表示新建了 $K$ 条道路后能达到的最小巡逻距离。

## 样例

### 样例输入 #1
```
8 1 
1 2 
3 1 
3 4 
5 3 
7 5 
8 5 
5 6 
```
### 样例输出 #1
```
11
```
### 样例输入 #2
```
8 2 
1 2 
3 1 
3 4 
5 3 
7 5 
8 5 
5 6 
```
### 样例输出 #2
```
10
```
### 样例输入 #3
```
5 2 
1 2 
2 3 
3 4 
4 5 
```
### 样例输出 #3
```
6
```
## 提示

- $10\%$ 的数据中，$1≤n≤1000,K=1$；
- $30\%$ 的数据中，$K=1$；
- $80\%$ 的数据中，每个村庄相邻的村庄数不超过 $25$；
- $90\%$ 的数据中，每个村庄相邻的村庄数不超过 $150$；
- $100\%$ 的数据中，$3≤n≤10^5,1≤K≤2$。



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
title: "琪露诺的冰雪小屋"
layout: "post"
diff: 省选/NOI-
pid: P3693
tag: ['模拟', '洛谷原创', '枚举', '广度优先搜索 BFS', '连通块']
---
# 琪露诺的冰雪小屋
## 题目背景

琪露诺有一片正方形的雪地，她想在上面盖一栋小冰屋。

## 题目描述

琪露诺偶然间得到了一片 $N\times N$ 大小的正方形的雪地，她想在上面盖一栋冰雪小屋。

但调皮的⑨才不会认真地收集冰块呢，她要在这片土地上使用冰雪弹幕来制造冰砖，然后一块一块地搭起一个房子。

琪露诺制造冰砖的方式是这样的：她会站在某个方格上，然后向上，下，左，右，左上，左下，右上，右下这八个方向之一发射强力的冰雪弹幕，弹幕能影响到该方向一条直线上一定的距离以内的所有方格。

地面的每个方格都有一个冷冻度，初始为 $0$。被冰雪弹幕影响一次，冷冻度 $+1$，冷冻度的上限为 $4$。

在发射弹幕的间隙中，琪露诺会来到所有冷冻度为 $4$ 的格子，把那里的雪堆到一起，制作一个冰砖（大小为 $1\times1\times1$ 方格），并且将冷冻度重新归零。

琪露诺会拿着这些冰砖来盖房子。这个房子的长度、宽度和坐落位置她在一开始就已经规划好了，但她并不愿意提早确定房子的高度。

琪露诺是这样计划的：这个房子外观上看起来是一个长方体。

她会先盖起这个房子的四面墙（厚度为 $1$ 个方格），并在贴近地面的位置（废话）留一个宽度和高度分别为 $1$ 和 $2$ 的空位不放冰砖，作为房门。（显然，门无法开在墙的拐角处，但可以紧贴拐角）。

在她喜欢的时候，她会结束四面墙的建造，并一次性在墙顶部盖上一个厚度为 $1$ 方格的屋顶，使房子成为一个空心有顶的长方体。

计划已经非常充分了，但琪露诺还是不放心，所以她想请你帮她写一个程序，来随时提醒着她别出什么差错。这个程序需要具备的功能将在下文详细介绍。

----------------------
雪地由 $N$ 行 $N$ 列，$N\times N$ 个方格组成。（下标从 $0$ 开始，也就是说，存在第 $0$ 行第 $0$ 列，但不存在第 $N$ 行第 $N$ 列）每个方格都有一个冷冻度,范围 $[0,4]$，初始为 $0$。注意，空间是三维的，而冷冻度只是地面的属性。

琪露诺想将房子的左上角放在第 $H_R$行，$H_C$ 列（外墙也是房子的一部分，因此左上角位置不应该是房子的内部,而是外墙,并且是墙的拐角）。

这个房子的长度（平行于每列）是 $H_X$，宽度（平行于每行）是 $H_Y$，包含墙。保证房子所占空间不会超出雪地的范围。

除了最后搭建屋顶，琪露诺只会在高度 $[0,H_M-1]$ 放置冰砖。

一开始，琪露诺一个冰砖也没有。
在以下的介绍中，我们用俯视图来作示意：
```plain
0000
0000
4x90
0x01
```
数字代表当前该格子的冷冻度。如果位置紧贴地面（高度为 $0$）的地方放上了冰砖，那么用字母 $x$ 表示。

如果紧贴地面的位置没有冰砖，但是位置正上方的高空存在冰砖，那么仍然用数字表示地面的冷冻度，但这个数字会增加 $5$。即如果在示意图中看到了一个数字 $t\ge5$，表示该位置地面是空的，但高处有冰砖，且地面的冷冻度为 $t-5$。

第一个操作：`ICE_BARRAGE R C D S`  
---------------
表示琪露诺站在第 $R$ 行 $C$ 列的位置，朝着方向 $D$ 发射了一个强度为 $S$ 的弹幕。  
$R,C,D,S\in\mathbf{Z},0\le D\le7,0\le R,C,S<N$。  
方向编号 $0$ 表示上 $(R-1,C)$，$1$ 表示左上 $(R-1,C-1)$，   
$2$ 表示左 $(R,C-1)$，$3$ 表示左下 $(R+1,C-1)$，  
$4$ 表示下 $(R+1,C)$，$5$ 表示右下 $(R+1,C+1)$，  
$6$ 表示右 $(R,C+1)$，$7$ 表示右上 $(R-1,C+1)$。  
强度为 $S$ 的弹幕，可以使“处在发射方向直线上，距离琪露诺不超过 $S$ 格的所有格子（包括她站的格子）”的冷冻度都 $+1$。有以下几种特殊情况：

1. 如果某个格子冷冻度为 $4$，那么该格子冷冻度不变。
2. 如果弹幕所经路途上，有一个位置的地面上（高度为 $0$）已经放了冰砖（就是弹幕撞上了琪露诺已经盖了一半的房子），那么弹幕将被阻挡，无法影响到冰砖所在的格子以及冰砖后面被挡住的格子。
3. 弹幕超出雪地的部分忽略不计。

对于这个操作，需要如下输出一行：`CIRNO FREEZED k BLOCK(S)`  
如果这个弹幕将某个方格的冷冻度成功增加了 $1$，那么认为这个弹幕冻住了该方格。

`k` 表示这个弹幕总共冻住了多少方格。

如图：发射弹幕前地图如下：
```plain
00000
00000
00000
000x0
00000
```
执行操作 `ICE_BARRAGE 1 1 5 4`，地图变为：
```plain
00000
01000
00100
000x0
00000
```
输出：`CIRNO FREEZED 2 BLOCK(S)`  
解释：琪露诺站在第一行第一列，面对右下角发射了一个强度为 $4$ 的弹幕，但弹幕被 `x` 所阻挡，只能影响到 `x` 之前的格子。

第二个操作：`MAKE_ICE_BLOCK`  
-------------------------
琪露诺走遍地图上所有冷冻度为 $4$ 的方格，每个方格可以收集一个冰砖，然后将它们的冷冻度归零。 

对于这个操作，你需要给出如下输出一行：`CIRNO MADE x ICE BLOCK(S),NOW SHE HAS y ICE BLOCK(S)`  
表示琪露诺制造了 $x$ 个冰砖，目前她有 $y$ 个冰砖。  
比如琪露诺一开始有 $0$ 个冰砖，并且状态如下：
```plain
0xxx
0x4x
0x9x
0400
```
执行操作 `MAKE_ICE_BLOCK` 后变为
```plain
0xxx
0x0x
0x5x
0000
```
输出：`CIRNO MADE 3 ICE BLOCK(S),NOW SHE HAS 3 ICE BLOCK(S)`  
在这个示例中，房子已经完成了一部分，`x` 表示墙，`9` 这个位置地面没有冰砖，但高处有（可以猜出是门）。房间内唯一一块空地、门的位置，以及房间外的一个位置的冷冻度都达到了 $4$，因此可以收集到 $3$ 块冰砖，收集后将三个位置冷冻度都归零。

第三个操作：`PUT_ICE_BLOCK R C H` 
-----------------
表示在第 $R$ 行，第 $C$ 列，高度为 $H$ 的地方放一个冰砖。$0\le R,C<N,0\le H<H_M$。

贴近地面的位置高度为 $0$。如果冰砖放置成功，那么琪露诺库存的冰砖数量将减 $1$。

如果放置的位置贴近地面，该位置冷冻度立即归 $0$。

有以下几种情况，序号越小优先级越高，并且只能满足一种情况。

如果满足 $1$ 的话就忽视后面的，不满足 $1$ 的前提下才可能满足 $2\cdots\cdots$ 以此类推。

1. 琪露诺目前没有任何冰砖，无法放置。这种情况下你需要输出：`CIRNO HAS NO ICE_BLOCK`
2. 冰砖将放在半空中，无法依附其他任何冰砖，或者目标位置已有冰砖了。  
这种情况下你需要输出一行：`BAKA CIRNO,CAN'T PUT HERE`，并无视此次操作，不做任何工作。
3. 冰砖放在了规划建造房子的区域之外，即
$R<H_R$ 或 $R>H_R+H_x-1$  
或 $C<H_C$ 或 $C>H_C+H_Y-1$。请输出一行：`CIRNO MISSED THE PLACE`  
尽管琪露诺放错了地方，但你并不能阻止她放置这个冰砖。  
4. 冰砖留在了房子的内部，本应留空的地方被占用了，即  
$H_R+1\le R\le H_R+H_X-2$ 且 $H_C+1\le C\le H_C+H_Y-2$  
在屋顶的高度固定下来前，我们将所有满足上式的情况都认为是放在了房屋内部。  
请输出一行：`CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE`  
尽管琪露诺放错了地方，但你并不能阻止她放置这个冰砖。
5. 冰砖放在了正确的位置（不必考虑是否堵住了留给门的地方）  
请输出一行：`CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS x ICE_BLOCK(S)`  
`x` 表示放过这块冰砖后琪露诺剩余的冰砖。

第四个操作：`REMOVE_ICE_BLOCK R C H` 
---------
表示取走第 $R$ 行，第 $C$ 列，高度为 $H$ 处的冰砖。  
有以下几种情况，序号越小优先级越高，并且只能满足一种情况。

如果满足 $1$ 的话就忽视后面的，不满足 $1$ 的前提下才可能满足 $2\cdots\cdots$ 以此类推。

1. 目标位置没有冰砖，输出一行：`BAKA CIRNO,THERE IS NO ICE_BLOCK`
2. 目标位置有冰砖，并且在这个冰砖被移走后，至少有一个冰砖形成了一个悬空的块。  
如下面的“侧视图”，`x` 表示冰砖，`0` 表示空位。
```plain
xxxx
x000
x000
x000
```
$\ \ $在移走左上角的冰砖后，第一行右边三个冰砖没有了依靠，形成了一个悬空的连通块，就属于这种情况。  
$\ \ $这个冰砖将成功移走，琪露诺的冰砖库存将会 $+1$。并且所有的悬空连通块都会掉下来摔碎并消失  
$\ \ $（既不会进入冰砖库存，也不会在地面上留有任何痕迹）。  
$\ \ $输出一行：`CIRNO REMOVED AN ICE_BLOCK,AND k BLOCK(S) ARE BROKEN`，`k` 表示摔碎的冰砖数量。  
3. 琪露诺挪走了冰砖，并且其他冰砖不受任何影响。    
$\ \ \ $琪露诺的冰砖库存 $+1$，输出一行：`CIRNO REMOVED AN ICE_BLOCK`
    
第五个操作：`MAKE_ROOF` 
--------
这个操作只会出现一次，并且只会作为最后一个操作。  
这个操作表明琪露诺已经完成了冰雪小屋的四墙，只剩屋顶了！  

一般情况下，琪露诺将放置最后的 $H_X\times H_Y$ 个冰砖，把它们放置在墙壁最高的高度 $+1$ 的那一层，  
形成一个屋顶。然后她移除所有多余的冰砖，接下来补好所有残缺的墙壁。

你需要按顺序来执行整个过程，一旦遇到某种用 $\bullet$ 标识的特殊情况，则执行完该情况后退出流程。

在特殊情况之间所描述的均为一般情况，只要之前没有因为满足某种特殊情况而退出流程，均认为满足了一般情况。

首先，琪露诺将会一次性放置最多 $H_X\times H_Y$ 个冰砖来建造屋顶。

为什么是最多呢？请注意一点：如果之前错误放置在房子内部的冰砖恰好充当了屋顶的一部分，那么就不用在这个位置再放冰砖了。并且，所有比屋顶高的冰砖在之后将视为错误放置在了房子外部。

注意，放屋顶的时候可能会触及到高度为 $H_M$ 的那个平面。

建造屋顶前后将会碰到两种特殊情况：
- 琪露诺剩余的冰砖不足以建造屋顶。输出一行：`SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO MAKE ROOF`
- 墙壁的最高高度小于 $2$ 个方格，或者内部有效空间小于两个方格。  
墙壁所在的一圈不算内部空间。计算内部有效空间时请忽视错误放置的冰砖，因为它们将来要被移除。  
输出一行：`SORRY CIRNO,HOUSE IS TOO SMALL`

（特殊情况结束）

此后，我们认为琪露诺已经造好了屋顶，接下来该移除所有多余冰砖了。在移除过程中，琪露诺会尽可能让更少的冰砖摔碎。如果墙壁上某个冰砖因为移走了多余的冰砖而将要摔碎，那么她会先拆掉墙壁上的那个冰砖，然后在填补墙壁残缺时重新补回来（显然，这种行为不会影响到墙壁有无残缺的定性，但可以少损失一个冰砖）。她不会故意拆掉一个处在墙壁上且不会摔碎的冰砖。  
输出两行：  
`K1 ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED`  
`K2 ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED`  
`K1`表示房子内部错误放置的冰砖数量，`K2`表示房子外部错误放置的冰砖数量。

将有可能遭遇一种特殊情况：
- 琪露诺移除了所有多余的冰砖，但在移除过程中，屋顶塌陷了。  
输出一行：`SORRY CIRNO,HOUSE IS BROKEN WHEN REMOVING BLOCKS`

（特殊情况结束）

此后，我们认为琪露诺已经移除了所有多余的冰砖，接下来该填补墙壁的残缺了。

墙壁有残缺的定义是：除了宽为 $1$，高为 $2$ 的门以外，
在房子内部看外面还能看到其他缺口。

如果某个空位将来要作为门的一部分，则不属于残缺。并且房子只能有一个门。

如果墙壁没有残缺，则不要填补，否则需要填补。你需要记下墙壁是否有残缺，之后会用到。

填补的策略是：使用尽可能少的冰砖，在正确的位置填补墙壁，使房屋的状态不满足墙壁有残缺的定义（即不能放置多余的冰砖，通过遮挡视线来达到目的）。在此定义下，**大多数**情况我们无需考虑四角的柱子是否完整，因为在房间里看不到。

将有可能遭遇一种特殊情况：
- 琪露诺剩余的冰砖不足以填补墙壁的残缺。  
输出一行：`SORRY CIRNO,NOT ENOUGH ICE_BLOCKS TO FIX THE WALL`

（特殊情况结束）

此后，我们认为房子被成功建成了，这时你需要输出几行内容来对房子进行评价。

首先输出这么一行来庆祝房子的建成：`GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE`  
1. 在贴近地面的位置找不到一个宽度为 $1$，高度为 $2$ 的位置留给门。  
	输出一行：`HOUSE HAS NO DOOR`，然后琪露诺会尽可能利用墙壁上的残缺来开一个门。  
    否则，输出一行：`DOOR IS OK`
2. 接下来输出一行表示填补之前墙壁的完整程度  
	2.1. 在之前的记录中，墙壁不完整而需要修补。输出：`WALL NEED TO BE FIXED`  
    2.2. 在之前的记录中，墙壁完整而无需修补。输出：`WALL IS OK`  
3. 接下来一行表示四角的完整程度。  
	如果四个角的柱子有不完整的地方，就输出：`CORNER NEED TO BE FIXED`  
    在这种情况下，如果琪露诺剩余的冰砖足够修复拐角的空缺，那么她直接会修复这个空缺。  
    如果不够的话，她会再多收集几个冰砖，数量恰好修复这个空缺，然后修复这个空缺。  
    否则，输出：`CORNER IS OK`
    
接下来，输出一行：`CIRNO FINALLY HAS k ICE_BLOCK(S)`  
`k` 表示琪露诺最后剩余的冰砖的数量。

最后，如果在之前的记录中，墙壁完整无缺，没有一个位置需要填补。房子内外都无任何多余的方块，没有一个位置需要移除。没有出现房子没门的情况，房子四角的柱子也在造屋顶前完全造好，而不是通过修补完善的。并且门恰好开在了某面墙的正中央（如果长度为偶数，中间的两个都算），输出一行：   
`CIRNO IS PERFECT!`
## 输入格式

第一行一个正整数 $N$，表示雪地的大小。

第二行一个正整数$H_M$，表示琪露诺放置方块的最大高度。

第三行四个正整数 $H_R,H_C,H_X,H_Y$，表示房子左上角位置的行列坐标，房子的长度以及宽度。

第四行一个正整数 $M$，表示操作的数量。

接下来 $M$ 行，每行表示一个操作，输入格式见题目描述。
## 输出格式

在题目描述中已经介绍。

## 样例

### 样例输入 #1
```
8
10
4 0 4 4
63
ICE_BARRAGE 2 1 1 3
ICE_BARRAGE 0 1 3 1
MAKE_ICE_BLOCK
PUT_ICE_BLOCK 3 2 0
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 2 0 6 7
ICE_BARRAGE 3 0 6 7
ICE_BARRAGE 4 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
PUT_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 4 0 0
PUT_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 3 0 1
REMOVE_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 4 2 0
PUT_ICE_BLOCK 6 1 0
PUT_ICE_BLOCK 4 3 0
PUT_ICE_BLOCK 5 3 0
PUT_ICE_BLOCK 6 3 0
PUT_ICE_BLOCK 7 3 0
ICE_BARRAGE 0 1 4 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
ICE_BARRAGE 1 0 6 7
MAKE_ICE_BLOCK
REMOVE_ICE_BLOCK 6 1 0
PUT_ICE_BLOCK 5 0 0
PUT_ICE_BLOCK 6 0 0
PUT_ICE_BLOCK 7 0 0
PUT_ICE_BLOCK 7 1 0
PUT_ICE_BLOCK 7 2 0
PUT_ICE_BLOCK 4 0 1
PUT_ICE_BLOCK 5 0 1
PUT_ICE_BLOCK 6 0 1
PUT_ICE_BLOCK 7 0 1
PUT_ICE_BLOCK 7 1 1
PUT_ICE_BLOCK 7 2 1
PUT_ICE_BLOCK 7 3 1
PUT_ICE_BLOCK 6 3 1
PUT_ICE_BLOCK 5 3 1
PUT_ICE_BLOCK 4 3 1
PUT_ICE_BLOCK 4 2 1
MAKE_ROOF

```
### 样例输出 #1
```
CIRNO FREEZED 2 BLOCK(S)
CIRNO FREEZED 2 BLOCK(S)
CIRNO MADE 0 ICE BLOCK(S),NOW SHE HAS 0 ICE BLOCK(S)
CIRNO HAS NO ICE_BLOCK
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 7 BLOCK(S)
CIRNO FREEZED 7 BLOCK(S)
CIRNO FREEZED 0 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 8 ICE BLOCK(S)
BAKA CIRNO,CAN'T PUT HERE
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 7 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 6 ICE_BLOCK(S)
CIRNO MISSED THE PLACE
CIRNO REMOVED AN ICE_BLOCK,AND 1 BLOCK(S) ARE BROKEN
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 5 ICE_BLOCK(S)
CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 3 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 2 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 1 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 0 ICE_BLOCK(S)
CIRNO FREEZED 6 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 7 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 8 ICE BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 16 ICE BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 24 ICE BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO FREEZED 8 BLOCK(S)
CIRNO MADE 8 ICE BLOCK(S),NOW SHE HAS 32 ICE BLOCK(S)
CIRNO REMOVED AN ICE_BLOCK
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 32 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 31 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 30 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 29 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 28 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 27 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 26 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 25 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 24 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 23 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 22 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 21 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 20 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 19 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 18 ICE_BLOCK(S)
CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS 17 ICE_BLOCK(S)
0 ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED
0 ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED
GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE
DOOR IS OK
WALL IS OK
CORNER IS OK
CIRNO FINALLY HAS 1 ICE_BLOCK(S)
CIRNO IS PERFECT!

```
## 提示

共分为 $6$ 个 **Subtask**，每个 **Subtask** 的数据都满足一定条件，并且同时满足序号更大的 **Subtask** 的条件。  
如 **Subtask #0** 同时满足 **Subtask #0~5** 的条件。  
每一个 **Subtask** 的得分取所有测试点的最低分。

**Subtask #0** $20\%$  
琪露诺只想玩玩冰雪弹幕，她不会放置任何冰砖，也不会盖房子(即只有操作一和操作二)。  


**Subtask #1** $10\%$  
琪露诺不会移除已经放置的冰砖。

**Subtask #2** $20\%$  
琪露诺很有信心，她将在没有 `MAKE_ROOF` 的情况下建造她的冰屋(这种情况下，放置方块的高度仍然会小于 $H_M$ 且没有 `MAKE_ROOF` 操作)。

**Subtask #3** $20\%$  
琪露诺在移除方块时会谨慎考虑,不会造成任何冰砖摔落。`MAKE_ROOF` 操作移除多余冰砖时，也不会造成屋顶塌陷。

**Subtask #4** $20\%$  
琪露诺不喜欢把门开到四角的柱子旁边(数据保证在所有可能作为门的墙壁空缺中，有一种可能使得门不紧贴四角的柱子)。 

**Subtask #5** $10\%$  
$4\le N\le 16$，$5\le H_M\le 20$，$10\le M\le 10^3$，保证不属于冰屋范围内的所有空地至多构成一个连通块。

注意：判断墙壁是否有残缺时，候选的开门位如果被方块堵住，在当时还未被清空。"能看到残缺"以当时的情况作为判断依据。


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
title: "[BJOI2017] 树的难题"
layout: "post"
diff: 省选/NOI-
pid: P3714
tag: ['2017', '各省省选', '点分治', '单调队列', '分治', '深度优先搜索 DFS']
---
# [BJOI2017] 树的难题
## 题目描述

给你一棵 $n$ 个点的无根树。

树上的每条边具有颜色。一共有 $m$ 种颜色，编号为 $1$ 到 $m$，第 $i$ 种颜色的权值为 $c_i$。

对于一条树上的简单路径，路径上经过的所有边按顺序组成一个颜色序列，序列可以划分成若干个相同颜色段。定义路径权值为颜色序列上每个同颜色段的颜色权值之和。

请你计算，经过边数在 $l$ 到 $r$ 之间的所有简单路径中，路径权值的最大值。
## 输入格式

第一行，四个整数 $n, m, l, r$。

第二行，$m$ 个整数 $c_1, c_2, \ldots, c_m$，由空格隔开，依次表示每个颜色的权值。

接下来 $n-1$ 行，每行三个整数 $u, v, c$，表示点 $u$ 和点 $v$ 之间有一条颜色为 $c$ 的边。
## 输出格式

输出一行，一个整数，表示答案。

## 样例

### 样例输入 #1
```
5 3 1 4
-1 -5 -2
1 2 1
1 3 1
2 4 2
2 5 3
```
### 样例输出 #1
```
-1
```
### 样例输入 #2
```
8 4 3 4
-7 9 6 1
1 2 1
1 3 2
1 4 1
2 5 1
5 6 2
3 7 1
3 8 3
```
### 样例输出 #2
```
11
```
## 提示

### 样例解释 1
颜色权值均为负，最优路径为 $(1, 2)$ 或 $(1, 3)$。

### 样例解释 2
最优路径为 $(3, 1, 2, 5, 6)$，其颜色序列为 $(2, 1, 1, 2)$。

### 数据范围
| 测试点编号 | $n$ | $m$ | 特殊限制 |
|-|-|-|-|
| $1$ | $=10^3$ | $\le n$ | 无特殊限制 |
| $2$ | $=10^4$ | $=2$ | 无特殊限制 |
| $3$ | $=10^5$ | $\le n$ | 所有点的度数不超过 $2$ |
| $4$ | $=2\times10^5$ | $\le n$ | 所有点的度数不超过 $2$ |
| $5$ | $=10^5$ | $=10$ | $l=1$，$r=n-1$ |
| $6$ | $=2\times10^5$ | $\le n$ | $l=1$，$r=n-1$ |
| $7$ | $=10^5$ | $=50$ | 无特殊限制 |
| $8$ | $=10^5$ | $\le n$ | 无特殊限制 |
| $9$ | $=2\times 10^5$ | $=100$ | 无特殊限制 |
| $10$ | $=2\times 10^5$ | $\le n$ | 无特殊限制 |

对于 $100\%$ 的数据，$1 \leq n, m \leq 2 \times 10^5$，$1 \leq l \leq r \leq n$，$\mid c_i \mid \leq 10^4$。保证树上至少存在一条经过边数在 $l$ 到 $r$ 之间的路径。


---

---
title: "曼哈顿计划E"
layout: "post"
diff: 省选/NOI-
pid: P3727
tag: ['点分治', '洛谷原创', '枚举', '分治', '深度优先搜索 DFS']
---
# 曼哈顿计划E
## 题目背景

1942 年 6 月，美国开始实施利用核裂变反应来研制原子弹的计划，亦称曼哈顿计划。后来两颗原子弹在广岛和长崎爆炸，世界见证了核武器的威力，并在它的威胁下颤抖不已。2200 年，dedsec 组织利用美国军方的网络安全漏洞渗入了美国的和武器系统，并密谋使用隐藏在曼哈顿的核武器储备毁灭世界。然而 dedsec 的一名成员 Badboy17 反对这一计划，她把这一计划告知了艾登。为了拯救他的家人，避免地球变为废土，艾登不得不再次发挥他的黑客能力拯救世界。

![](https://cdn.luogu.com.cn/upload/pic/5119.png)

## 题目描述

艾登尝试黑入 dedsec 的系统并取得控制权，然而 dedsec 有所反应并予以反击。

dedsec 的网络可以看做是一个 $n$ 个点 $n-1$ 条边的连通图（一棵树），每个节点有一个稳定值。

艾登可以选择网络中上的一条链，并对那一条链上的节点进行破解（把这一条链从树上拆下来）。

假设这一条链长度为 $m$，现在你会得到 $m$ 个节点。

然后艾登要和 dedsec 开始攻防战，双方轮流行动，每次可以从任意一个稳定值大于 $0$ 的节点里依照计算规则进行一些操作，操作后，稳定值不能小于 $0$，否则计算机会爆炸，最后不能进行操作的一方算作失败

由于 dedsec 占据了防守的地理优势，dedsec 先进行操作


艾登虽然精于黑客技术，但他的手机没电了。现在他把这个消息告诉了你，希望你帮他拯救世界，所以你需要写一个程序，来帮你判断是否存在一种方式，艾登可以取胜。当然，dedsec 的防守可能完美无缺，艾登根本无法取胜，你只好跑到 shelter 里去当试验品。

## 输入格式

输入包含多组测试数据，输入第一行包含一个整数 $T$，表示数据组数。

对于每组测试数据，第一行一个整数 $n$，表示有 $n$ 个点。

第二行至第 $n$ 行，每行两个整数 $u,v$，表示网络中有一条边连接 $u,v$。

第 $n+1$ 行 $n$ 个整数 $w$，第 $w_i$ 表示 $i$ 号节点的稳定值。

第 $n+2$ 行一个整数 $k$，描述操作的规则：

- 如果 $k=1$，你可以减少任意正整数的稳定值。
- 如果 $k=2$，接下来一行一个正整数 $s$，表示双方每次可以减少 $s$ 的非负整数幂的稳定值。
- 如果 $k=3$，接下来一行一个正整数 $s$，表示双方每次可以减少大于等于 $s$ 的稳定值。
- 如果 $k=4$，表示双方每次可以减少任意正整数的稳定值，或者把一个稳定值数量大于等于 $2$ 的节点分裂成两个，分开后的两个节点的稳定值之和等于原来的节点（比如 $7$ 分成 $3+4$）。
- 如果 $k=5$，双方都不能进行操作。

## 输出格式

对于每一组测试数据，输出一行：

如果存在一种方式，你可以获胜，输出 `Mutalisk ride face how to lose?`。

如果不存在一种方式可以取胜，输出 `The commentary cannot go on!`。

## 样例

### 样例输入 #1
```
1
3
1 2
2 3
1 2 3
1
```
### 样例输出 #1
```
Mutalisk ride face how to lose?
```
### 样例输入 #2
```
1
3
1 2
2 3
1 2 4
1
```
### 样例输出 #2
```
The commentary cannot go on!
```
## 提示

|测试点|$n\le$|$k$|$w_i\le$|
|:-:|:-:|:-:|:-:|
|$1$|$50$|$1$|$10^3$|
|$2$|$3\times 10^4$|$1$|$10^3$|
|$3$|$300$|$3$|$10^6$|
|$4$|$10^3$|$4$|$10^6$|
|$5$|$3\times 10^4$|$1$|$10^9$|
|$6$|$3\times 10^4$|$2$|$10^9$|
|$7$|$3\times 10^4$|$3$|$10^9$|
|$8$|$3\times 10^4$|$3$|$10^9$|
|$9$|$3\times 10^4$|$4$|$10^9$|
|$10$|$3\times 10^4$|$4$|$10^9$|

对于 $100\%$ 的数据，$T\le 5$。

保证输入均为正整数



---

---
title: "[六省联考 2017] 寿司餐厅"
layout: "post"
diff: 省选/NOI-
pid: P3749
tag: ['2017', '各省省选', '广度优先搜索 BFS', '深度优先搜索 DFS', '最小割']
---
# [六省联考 2017] 寿司餐厅
## 题目描述

Kiana 最近喜欢到一家非常美味的寿司餐厅用餐。

每天晚上，这家餐厅都会按顺序提供 $n$ 种寿司，第 $i$ 种寿司有一个代号 $a_i$ 和美味度 $d_{i, i}$，不同种类的寿司有可能使用相同的代号。每种寿司的份数都是无限的，Kiana 也可以无限次取寿司来吃，但每种寿司每次只能取一份，且每次取走的寿司必须是按餐厅提供寿司的顺序连续的一段，即 Kiana 可以一次取走第 $1, 2$ 种寿司各一份，也可以一次取走第 $2, 3$ 种寿司各一份，但不可以一次取走第 $1, 3$ 种寿司。

由于餐厅提供的寿司种类繁多，而不同种类的寿司之间相互会有影响：三文鱼寿司和鱿鱼寿司一起吃或许会很棒，但和水果寿司一起吃就可能会肚子痛。因此，Kiana 定义了一个综合美味度 $d_{i, j} \ (i < j)$，表示在一次取的寿司中，如果包含了餐厅提供的从第 $i$ 份到第 $j$ 份的所有寿司，吃掉这次取的所有寿司后将获得的额外美味度。由于取寿司需要花费一些时间，所以我们认为分两次取来的寿司之间相互不会影响。注意在吃一次取的寿司时，不止一个综合美味度会被累加，比如若 Kiana 一次取走了第 $1, 2, 3$ 种寿司各一份，除了 $d_{1, 3}$ 以外，$d_{1, 2}, d_{2, 3}$ 也会被累加进总美味度中。

神奇的是，Kiana 的美食评判标准是有记忆性的，无论是单种寿司的美味度，还是多种寿司组合起来的综合美味度，在计入 Kiana 的总美味度时都只会被累加一次。比如，若 Kiana 某一次取走了第 $1, 2$ 种寿司各一份，另一次取走了第 $2, 3$ 种寿司各一份，那么这两次取寿司的总美味度为 $d_{1, 1} + d_{2, 2} + d_{3, 3} + d_{1, 2} + d_{2, 3}$，其中 $d_{2, 2}$ 只会计算一次。

奇怪的是，这家寿司餐厅的收费标准很不同寻常。具体来说，如果 Kiana 一共吃过了 $c \ (c > 0)$ **种**代号为 $x$ 的寿司，则她需要为这些寿司付出 $mx^2 + cx$ 元钱，其中 $m$ 是餐厅给出的一个常数。

现在 Kiana 想知道，在这家餐厅吃寿司，自己能获得的总美味度（包括所有吃掉的单种寿司的美味度和所有被累加的综合美味度）减去花费的总钱数的最大值是多少。由于她不会算，所以希望由你告诉她。
## 输入格式

第一行包含两个正整数 $n, m$，分别表示这家餐厅提供的寿司总数和计算寿司价格中使用的常数。  
第二行包含 $n$ 个正整数，其中第 $k$ 个数 $a_k$ 表示第 $k$ 份寿司的代号。  
接下来 $n$ 行，第 $i$ 行包含 $n - i + 1$ 个整数，其中第 $j$ 个数 $d_{i, i+j-1}$ 表示吃掉寿司能获得的相应的美味度，具体含义见问题描述。
## 输出格式

输出共一行包含一个正整数，表示 Kiana 能获得的总美味度减去花费的总钱数的最大值。
## 样例

### 样例输入 #1
```
3 1
2 3 2
5 -10 15
-10 15
15
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
5 0
1 4 1 3 4
50 99 8 -39 30
68 27 -75 -32
70 24 72
-10 81
-95
```
### 样例输出 #2
```
381
```
### 样例输入 #3
```
10 1
5 5 4 4 1 2 5 1 5 3
83 91 72 29 22 -5 57 -14 -36 -3
-11 34 45 96 32 73 -1 0 29
-48 68 44 -5 96 66 17 74
88 47 69 -9 2 25 -49
86 -9 -77 62 -10 -30
2 40 95 -74 46
49 -52 2 -51
-55 50 -44
72 22
-68
```
### 样例输出 #3
```
1223
```
## 提示

### 样例解释 1

在这组样例中，餐厅一共提供了 $3$ 份寿司，它们的代号依次为 $a_1 = 2, a_2 = 3, a_3 = 2$，计算价格时的常数 $m = 1$。

在保证每次取寿司都能获得新的美味度的前提下，Kiana 一共有 $14$ 种不同的吃寿司方案。以下列出其中几种：
1. Kiana 一个寿司也不吃，这样她获得的总美味度和花费的总钱数都是 $0$，两者相减也是 $0$；
2. Kiana 只取 $1$ 次寿司，且只取第 $1$ 个寿司，即她取寿司的情况为 $\{[1, 1]\}$，这样获得的总美味度为 $5$，花费的总钱数为 $1 \times 2^2 + 1 \times 2 = 6$，两者相减为 $-1$；
3. Kiana 取 $2$ 次寿司，第一次取第 $1, 2$ 个寿司，第二次取第 $2, 3$ 个寿司，即她取寿司的情况为 $\{[1, 2], [2, 3]\}$，这样获得的总美味度为 $5 + (-10) + 15 + (-10) + 15 = 15$，花费的总钱数为 $(1 \times 2^2 + 2 \times 2) + (1 \times 3^2 + 1 \times 3) = 20$，两者相减为 $-5$；
4. Kiana 取 $2$ 次寿司，第一次取第 $1$ 个寿司，第二次取第 $3$ 个寿司，即她取寿司的情况为 $\{[1, 1], [3, 3]\}$，这样获得的总美味度为 $5 + 15 = 20$，花费的总钱数为 $1 \times 2^2 + 2 \times 2 = 8$，两者相减为 $12$。

在 $14$ 种方案中，惟一的最优方案是列出的最后一种方案，这时她获得的总美味度减去花费的总钱数的值最大为 $12$。

### 数据范围

对于所有数据，保证 $-500 \leq d_{i, j} \leq 500$。

数据的一些特殊约定如下表：

| Case # | $n$ | $a_i$ | $m$ | 附加限制 |
|:-:|:-:|:-:|:-:|:-:|
| 1 | $\leq 2$ | $\leq 30$ | $= 0$ | - |
| 2 | $\leq 2$ | $\leq 30$ | $= 1$ | - |
| 3 | $\leq 3$ | $\leq 30$ | $= 0$ | - |
| 4 | $\leq 3$ | $\leq 30$ | $= 1$ | - |
| 5 | $\leq 5$ | $\leq 30$ | $= 0$ | - |
| 6 | $\leq 5$ | $\leq 30$ | $= 1$ | - |
| 7 | $\leq 10$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 8 | $\leq 10$ | $\leq 30$ | $= 1$ | - |
| 9 | $\leq 15$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 10 | $\leq 15$ | $\leq 30$ | $= 1$ | - |
| 11 | $\leq 30$ | $\leq 1000$ | $= 0$ | 所有的 $a_i$ 相同 |
| 12 | $\leq 30$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 13 | $\leq 30$ | $\leq 1000$ | $= 0$ | - |
| 14 | $\leq 30$ | $\leq 1000$ | $= 1$ | - |
| 15 | $\leq 50$ | $\leq 1000$ | $= 0$ | 所有的 $a_i$ 相同 |
| 16 | $\leq 50$ | $\leq 30$ | $= 0$ | 所有的 $a_i$ 相同 |
| 17 | $\leq 50$ | $\leq 1000$ | $= 0$ | - |
| 18 | $\leq 50$ | $\leq 1000$ | $= 1$ | - |
| 19 | $\leq 100$ | $\leq 1000$ | $= 0$ | - |
| 20 | $\leq 100$ | $\leq 1000$ | $= 1$ | - |


---

---
title: "魔法"
layout: "post"
diff: 省选/NOI-
pid: P3767
tag: ['搜索', '线段树', '并查集', '洛谷原创', '分治', '洛谷月赛']
---
# 魔法
## 题目背景

小 Y 在 AK 曼哈顿 OI 之后，开始研究膜法。

一个精心构造的魔法阵可以产生强大的魔力，但是也有非常严苛的要求。

魔法阵的强度与咒语的数目相关，但是咒语太多可能会产生冲突，小Y当然会解决这个问题啦，但是他想考一考你。

## 题目描述

魔法阵由 $N$ 个枢纽组成。

每个枢纽可以有五种属性：金、木、水、火、土。它们之间满足相生相克的关系。

 ![](https://cdn.luogu.com.cn/upload/pic/5349.png) 

一开始，魔法阵中没有咒语。

每次，小 Y 会添加一条咒语，它会要求两个枢纽的属性满足相生/相克的关系。然后你需要回答：是否存在一种为每个枢纽分配一个属性的方案，满足所有的要求。

为了调整法阵，小 Y 有时候需要删除一条写过的咒语。

小 Y 觉得这个问题太简单了，于是他使用改变时间线的能力，让每一次操作在之前某一次操作后形成的魔法阵的基础上进行。
## 输入格式

第一行两个正整数 $N,M$，表示枢纽的个数和操作个数。

接下来 $M$ 行，每行四个数表示一次操作。

第一个数 $k$ 表示这次操作在第 $k$ 次操作结束后的魔法阵上进行，如果 $k=0$，则表示在初始的魔法阵上进行。

第二个数 $t$ 表示操作类型。

- $t=1$：接下来输入 $u,v$，表示加入一条咒语，要求 $u$ 生 $v$。

- $t=2$：接下来输入 $u,v$，表示加入一条咒语，要求 $u$ 克 $v$。

- $t=3$: 接下来输入 $x$，表示删除第 $x$ 次操作加入的咒语。
## 输出格式

对于每一次操作，如果操作后存在为每个枢纽分配一个属性的方案，满足所有的要求，输出 `excited`，否则输出 `naive`。

## 样例

### 样例输入 #1
```
3 6  
0 1 1 2  
1 1 2 3  
2 2 1 3  
2 1 3 1  
2 3 1  
5 1 3 1
```
### 样例输出 #1
```
excited  
excited  
excited  
naive  
excited  
excited  
```
## 提示

对于 $30\%$ 的数据，满足 $N,M\leq 100$;

对于另 $30\%$ 的数据，满足 $k_i=i-1$;

对于100%的数据，满足 $N,M \leq 100000, 0\leq k_i < i, u_i \neq v_i, 1 \leq u_i,v_i \leq N$，保证所有删除操作都合法。



---

---
title: "【模板】可持久化平衡树"
layout: "post"
diff: 省选/NOI-
pid: P3835
tag: ['线段树', '平衡树', '深度优先搜索 DFS', '可持久化']
---
# 【模板】可持久化平衡树
## 题目背景

本题为题目 **普通平衡树** 的可持久化加强版。

**数据已经经过强化**

**感谢@Kelin 提供的一组hack数据**

## 题目描述

您需要写一种数据结构（可参考题目标题），来维护一个可重整数集合，其中需要提供以下操作（ **对于各个以往的历史版本** ）：


1、 插入 $x$

2、 删除 $x$（若有多个相同的数，应只删除一个，**如果没有请忽略该操作**）


3、 查询 $x$ 的排名（排名定义为比当前数小的数的个数 $+1$）


4、查询排名为 $x$ 的数


5、 求 $x$ 的前驱（前驱定义为小于 $x$，且最大的数，**如不存在输出** $-2^{31}+1$ ）


6、求 $x$ 的后继（后继定义为大于 $x$，且最小的数，**如不存在输出** $2^{31}-1$ ）


**和原本平衡树不同的一点是，每一次的任何操作都是基于某一个历史版本，同时生成一个新的版本。（操作3, 4, 5, 6即保持原版本无变化）**

每个版本的编号即为操作的序号（版本0即为初始状态，空树）

## 输入格式

第一行包含一个正整数 $n$ ，表示操作的总数。

接下来 $n$ 行，每行包含三个整数，第 $i$ 行记为 $v_i, \text{opt}_i, x_i$。

$v_i$ 表示基于的过去版本号，$\text{opt}_i$ 表示操作的序号， $x_i$ 表示参与操作的数值

## 输出格式

每行包含一个整数，依次为各个 $3,4,5,6$ 操作所对应的答案

## 样例

### 样例输入 #1
```
10
0 1 9
1 1 3
1 1 10
2 4 2
3 3 9
3 1 2
6 4 1
6 2 9
8 6 3
4 5 8
```
### 样例输出 #1
```
9
1
2
10
3
```
## 提示

【数据范围】   
对于 $28\%$ 的数据，$ 1 \leq n \leq 10 $；   
对于 $44\%$ 的数据，$ 1 \leq n \leq 2\times {10}^2 $；   
对于 $60\%$ 的数据， $ 1 \leq n \leq 3\times {10}^3 $；   
对于 $84\%$ 的数据， $ 1 \leq n \leq {10}^5 $；   
对于 $92\%$ 的数据， $ 1 \leq n \leq 2\times {10}^5 $；   
对于 $100\%$ 的数据， $ 1 \leq n \leq 5 \times  10^5 $ , $|x_i| \leq {10}^9$，$0 \le v_i < i$，$1\le \text{opt} \le 6$。

**经实测，正常常数的可持久化平衡树均可通过，请各位放心**



样例说明：

共 $10$ 次操作，$11$ 个版本，各版本的状况依次是：

0.  $[]$

1.  $[9]$

2.  $[3, 9]$

3.  $[9, 10]$

4.  $[3, 9]$

5.  $[9, 10]$

6.  $[2, 9, 10]$

7.  $[2, 9, 10]$

8.  $[2, 10]$

9.  $[2, 10]$

10.  $[3, 9]$



---

---
title: "[湖南集训] 更为厉害"
layout: "post"
diff: 省选/NOI-
pid: P3899
tag: ['线段树', '湖南', '深度优先搜索 DFS', '可持久化线段树']
---
# [湖南集训] 更为厉害
## 题目描述

设 $\text T$ 为一棵有根树，我们做如下的定义：

- 设 $a$ 和 $b$ 为 $\text T$ 中的两个不同节点。如果 $a$ 是 $b$ 的祖先，那么称“$a$ 比 $b$ 更为厉害”。
- 设 $a$ 和 $b$ 为 $\text T$ 中的两个不同节点。如果 $a$ 与 $b$ 在树上的距离不超过某个给定常数 $x$，那么称“ $a$ 与 $b$ 彼此彼此”。

给定一棵 $n$ 个节点的有根树 $\text T$，节点的编号为 $1$ 到 $n$，根节点为 $1$ 号节点。
你需要回答 $q$ 个询问，询问给定两个整数 $p$ 和 $k$，问有多少个有序三元组 $(a,b,c)$ 满足：

1. $a,b,c$ 为 $\text T$ 中三个不同的点，且 $a$ 为 $p$ 号节点；
2. $a$ 和 $b$ 都比 $c$ 更为厉害；
3. $a$ 和 $b$ 彼此彼此。这里彼此彼此中的常数为给定的 $k$。

## 输入格式

输入文件的第一行含有两个正整数 $n$ 和 $q$，分别代表有根树的点数与询问的个数。

接下来 $n - 1$ 行，每行描述一条树上的边。每行含有两个整数 $u$ 和 $v$，代表在节点 $u$ 和 $v$ 之间有一条边。

接下来 $q$ 行，每行描述一个操作。第 $i$ 行含有两个整数，分别表示第 $i$ 个询问的 $p$ 和 $k$。

## 输出格式

输出 $q$ 行，每行对应一个询问，代表询问的答案。

## 样例

### 样例输入 #1
```
5 3
1 2
1 3
2 4
4 5
2 2
4 1
2 3
```
### 样例输出 #1
```
3
1
3
```
## 提示

样例中的树如下图所示：

 ![](https://cdn.luogu.com.cn/upload/pic/6858.png) 

对于第一个和第三个询问，合法的三元组有 $(2,1,4)$、 $(2,1,5)$ 和 $(2,4,5)$。

对于第二个询问，合法的三元组只有 $(4,2,5)$。


所有测试点的数据规模如下（注意，洛谷并不按照以下方式评测）：

 ![](https://cdn.luogu.com.cn/upload/pic/6859.png) 

对于全部测试数据的所有询问，$1\le p,k \le n$。

- 2023.9.15 添加一组 hack 数据。


---

---
title: "Coloring"
layout: "post"
diff: 省选/NOI-
pid: P3936
tag: ['搜索', '洛谷原创', 'Special Judge', '模拟退火']
---
# Coloring
## 题目描述

$\text{Snakes}$正在玩游戏，他在一张画有$n*m$个格子的白纸上给方格染色。然而，杂乱无章的染色并不有趣，所以他想出了一个奇怪的问题：


在$n*m$的方格中用$c$种不同的颜色尝试将所有方格染色，不同的颜色用$1..c$间的整数表示。染色需要满足以下条件：


+ 每个方格只能且必须染一种颜色。

+ 第$i$种颜色最多可以且必须染$p_i$个格子，保证满足$\sum_{i=1}^cp_i=n*m$。

+ 将每个格子上下左右与其颜色相同的格子视为位于同一个联通块内，并定义不同联通块之间的方格边的条数为$q$。可参考样例说明。


现在，$\text{Snakes}$想知道，如果给出$n,m,c$以及$p_1..p_c$，你能够构造出的符合条件且$q$尽量小的染色方案。

## 输入格式

第一行，三个数，$n,m,c$。


第二行，$c$个数，第$i$个数为$p_i$。

## 输出格式

输出共$n$行，每行$m$个数，表示你构造出的$n*m$的$q$尽量少的染色方案。

## 样例

### 样例输入 #1
```
2 3 3
1 2 3
```
### 样例输出 #1
```
2 3 1
2 3 3
```
## 提示

```plain
   |   |   
 2 | 3 | 1 
   +   +---
 2 | 3   3 
   |       
```

对于样例，有$q=4$，其中三条竖边，一条横边。


#### 约定


本题为 Special Judge。


对于每个测试点，将会设置阈值$w$，并保证存在构造使得$q\leq w$。


对于程序输出的答案，我们将会以以下方式计算得分：


$$\begin{matrix}q&score&q&score\\\\ q \leq w&10&1.75w < q \leq 2w&5\\\\ w < q \leq 1.1w&9&2w < q \leq 2.3w&4\\\\ 1.1w < q \leq 1.25w&8&2.3w < q \leq 2.6w&3\\\\ 1.25w < q \leq 1.5w&7&2.6w < q \leq 3w&2\\\\ 1.5w < q \leq 1.75w&6&3w < q \leq 3.5w&1\end{matrix}$$


若$q > 3.5w$，将以 `Wrong Answer` 处理。


比赛时显示的得分即为最后得分。


#### 数据规模


对于$10\%$的数据，有$1\leq n,m\leq 3$，$c\leq 3$。


对于$30\%$的数据，有$1\leq n,m\leq 8$，$c\leq 6$。


对于$50\%$的数据，有$1\leq n,m\leq 15$，$c\leq 25$。


对于$100\%$的数据，有$1\leq n,m\leq 20$，$c\leq 50$，$p_i\leq 20$。



---

---
title: "我永远喜欢珂朵莉~"
layout: "post"
diff: 省选/NOI-
pid: P3987
tag: ['平衡树', '树状数组', '深度优先搜索 DFS', '洛谷月赛']
---
# 我永远喜欢珂朵莉~
## 题目背景

http://sukasuka-anime.com/

戒不掉的珂毒

出不动的分块

 ![](https://cdn.luogu.com.cn/upload/pic/11191.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/11192.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/11193.png) 

哦对了有没有想买BD的珂学家啊？支持一下墨鱼吧~

或者有没有人想来手办众筹啊？

## 题目描述

给珂朵莉一个长为 $n$ 的非负数序列 $a$，支持以下两个操作：

- $\verb!1 l r x!$：把区间 $[l,r]$ 中所有 $x$ 的倍数除以 $x$。
- $\verb!2 l r!$：查询区间 $[l,r]$ 内元素的和。

珂朵莉很可爱，所以你要帮珂朵莉写这个题。

## 输入格式

第一行两个数表示 $n,m$。

第二行 $n$ 个非负整数表示 $a_i$。

之后 $m$ 行每行一个操作：

- $\verb!1 l r x!$：把区间 $[l,r]$ 中所有 $x$ 的倍数除以 $x$。
- $\verb!2 l r!$：查询区间 $[l,r]$ 内元素的和。

## 输出格式

对于每次询问，输出一行一个数表示答案。

## 样例

### 样例输入 #1
```
5 3
1 2 3 4 5
2 1 5
1 1 5 2
2 1 5
```
### 样例输出 #1
```
15
12
```
## 提示

### 数据范围及约定

$1 \le n , m \le 10^5$，$0 \le a_i \le 5\times 10^5$，$1 \le x \le 5\times 10^5$。



---

---
title: "小 Y 和地铁"
layout: "post"
diff: 省选/NOI-
pid: P4005
tag: ['模拟', '搜索', '2017', '树状数组', 'O2优化', '枚举', '模拟退火', 'CTT（清华集训/北大集训）']
---
# 小 Y 和地铁
## 题目描述

小 Y 是一个爱好旅行的 OIer。一天，她来到了一个新的城市。由于不熟悉那里的交通系统，她选择了坐地铁。

她发现每条地铁线路可以看成平面上的一条曲线，不同线路的交点处一定会设有换乘站 。通过调查得知，没有线路是环线，也没有线路与自身相交。任意两条不同的线路只会在若干个点上相交，没有重合的部分，且没有三线共点的情况。即，如图所示的情况都是不存在的：

 ![](https://cdn.luogu.com.cn/upload/pic/12055.png) 

小 Y 坐着地铁 $0$ 号线，路上依次经过了 $n$ 个换乘站。她记下了每个换乘站可以换乘的线路编号，发现每条线路与她所乘坐的线路最多只有 $2$ 个换乘站。现在小 Y 想知道，除掉她经过的换乘站以外，这个城市里最少有几个换乘站。只有你告诉她正确的答案，她才会答应下次带你去玩呢。

## 输入格式

**请注意本题有多组输入数据。**

输入数据的第一行是一个整数 $T$，表示输入数据的组数。接下来依次给出每组数据。

对于每组数据，第一行是一个整数 $n$，表示小 Y 经过的换乘站的数目。第二行为 $n$ 个用空格隔开的整数，依次表示每个换乘站的可以换乘的线路编号。这些编号都在 $1\sim n$ 之内。

## 输出格式

对于每组输入数据，输出一行一个整数，表示除掉这 $n$ 个换乘站之外，最少有几个换乘站。

## 样例

### 样例输入 #1
```
4 4
1 2 1 2
8
1 2 3 4 1 2 3 4
5
5 4 3 3 5
8
1 2 3 4 1 3 2 4
```
### 样例输出 #1
```
0 
0 
0 
1
```
## 提示

【样例 1 解释】

对于样例的前两组数据，一种可能的最优答案如下图所示。

 ![](https://cdn.luogu.com.cn/upload/pic/12053.png) 

【子任务】

一共有 $50$ 个测试点，每个测试点 $2$ 分。你只有在答案完全正确时才能得到该测试点的全部分数，否则不得分。

对于所有测试点，以及对于样例， $1 \leq T \leq 100$, $1 \leq n \leq 44$。对于每个测试点， $n$ 的范围如下表：

![](https://cdn.luogu.com.cn/upload/pic/12054.png)



---

---
title: "[Code+#2] 白金元首与独舞"
layout: "post"
diff: 省选/NOI-
pid: P4033
tag: ['搜索', '图论建模', '生成树', 'Code+']
---
# [Code+#2] 白金元首与独舞
## 题目背景

```cpp
到河北省 见斯大林 / 在月光下 你的背影 / 让我们一起跳舞吧
```
うそだよ~ 河北省怎么可能有 Stalin。


可是…… 可是如果 Stalin 把自己当作炸弹扔到地堡花园里来了呢？


怀揣着这份小小的希望，元首 Adolf 独自走进了花园。终有一天会重逢的吧，Stalin。或许是在此处，或许是在遥远的彼方。


无论如何，在此之前，好好装点一番花园，编排一段优美的舞步吧！

## 题目描述

元首把花园分为 $n$ 行 $m$ 列的网格。每个格子中都可以放置一个标识，指向上、下、左、右四个方向中的任意一个。元首位于一个格子时，会按照其中标识所指的方向进入周围的格子，或者走出花园（即目的格子不在网格之内）。举个例子 —— 对于下面的放置方式，元首从第 $3$ 行第 $2$ 列的格子开始，会沿着以红色标出的路径走出花园；从第 $2$ 行第 22 列的格子开始，则会在以蓝色标出的环路内不断地行走。

 ![](https://cdn.luogu.com.cn/upload/pic/12659.png) 

元首已经设计好了大部分格子的标识。元首用字符 L、R、U、D 分别表示指向左、右、上、下四个方向的标识，用字符 . 表示未决定的格子。现在，元首希望将每个 . 替换为 L、R、U、D 中任意一种，使得从花园中的任意一个格子出发，按照上述规则行走，都可以最终走出花园。


你需要编写程序帮助元首计算替换的不同方案数。两个方案不同当且仅当存在一个格子，使得两个方案中该格子内的标识不同。当然，由于答案可能很大，只需给出方案数除以 $10^9 + 7$所得的余数即可。

## 输入格式

从标准输入读入数据。


输入的第一行包含一个正整数 $T$ —— 测试数据的组数。接下来包含 $T$ 组测试数据，格式如下，测试数据间没有空行。


第 $1$ 行：两个空格分隔的正整数 $n$、$m$ —— 依次表示花园被分成的行数和列数。

接下来 $n$ 行：每行一个长度为 $m$ 的由字符 L、R、U、D 和 . 组成的字符串 —— 表示花园内已经确定的格子状态。

## 输出格式

输出到标准输出。


对于每组测试数据输出一行 —— 满足条件的方案数除以 $10^9 + 7 $所得的余数。

## 样例

### 样例输入 #1
```
5
3 9
LLRRUDUUU
LLR.UDUUU
LLRRUDUUU
4 4
LLRR
L.LL
RR.R
LLRR
4 3
LRD
LUL
DLU
RDL
1 2
LR
2 2
..
..
```
### 样例输出 #1
```
3
8
0
1
192
```
## 提示

**样例解释**

第 $1$ 组数据中，将惟一的 . 替换成 R、U 或 D 均满足要求。


第 $2$ 组数据中，将左上方和右下方的两个 . 分别替换成 LR、LU、LD、UR、UU、UD、DR 或 DD 均满足要求。


第 $3$ 组数据中，没有待决定的格子，原本的安排会使得元首陷入无尽的环路，故答案为 $0$。该组数据与**题目描述**中的例子相同。


第 $4$ 组数据中，也没有待决定的格子，但原本的安排已经满足要求，故答案为 $1$。


令 $k$ 表示标记未确定（即包含 “.”）的格子总数。


对于所有数据，有 $1 \leq T \leq 10$，$1 \leq n, m \leq 200$，$0 \leq k \leq \min(nm, 300)$。

 ![](https://cdn.luogu.com.cn/upload/pic/12660.png) 

“... wie Stalin!”


题面与史实无关。


来自 CodePlus 2017 12 月赛，清华大学计算机科学与技术系学生算法与竞赛协会 荣誉出品。

Credit：idea/吕时清 命题/吕时清 验题/王聿中，杨景钦

Git Repo：https://git.thusaac.org/publish/CodePlus201712

感谢腾讯公司对此次比赛的支持。



---

---
title: "[HEOI2015] 最短不公共子串"
layout: "post"
diff: 省选/NOI-
pid: P4112
tag: ['2015', '各省省选', '河北', '后缀自动机 SAM', 'O2优化', '广度优先搜索 BFS', '后缀数组 SA']
---
# [HEOI2015] 最短不公共子串
## 题目描述

在虐各种最长公共子串、子序列的题虐的不耐烦了之后，你决定反其道而行之。

下面给出一些定义：

- 一个串的“子串”指的是它的连续的一段，例如 `bcd` 是 `abcdef` 的子串，但 `bde` 不是。
- 一个串的“子序列”指的是它的可以不连续的一段，例如 `bde` 是 `abcdef` 的子串，但 `bdd` 不是。

下面，给两个小写字母串 $a, b$，请你计算：

1. $a$ 的一个最短的子串，它不是 $b$ 的子串。
2. $a$ 的一个最短的子串，它不是 $b$ 的子序列。
3. $a$ 的一个最短的子序列，它不是 $b$ 的子串。
4. $a$ 的一个最短的子序列，它不是 $b$ 的子序列。

## 输入格式

有两行，每行一个小写字母组成的字符串，分别代表 $a$ 和 $b$。

## 输出格式

输出 $4$ 行，每行一个整数，依次表示以上 $4$ 个问题的答案的长度。如果没有符合要求的答案，输出 $-1$。

## 样例

### 样例输入 #1
```
aabbcc
abcabc
```
### 样例输出 #1
```
2
4
2
4
```
### 样例输入 #2
```
aabbcc
aabbcc
```
### 样例输出 #2
```
-1
-1
2
-1
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $a$ 和 $b$ 的长度都不超过 $20$。
- 对于 $50\%$ 的数据，保证 $a$ 和 $b$ 的长度都不超过 $500$。
- 对于 $100\%$ 的数据，保证 $a$ 和 $b$ 的长度都不超过 $2000$。



---

---
title: "[WC2011] 最大XOR和路径"
layout: "post"
diff: 省选/NOI-
pid: P4151
tag: ['图论', '贪心', '2011', '枚举', '深度优先搜索 DFS', '线性基', '向量', 'WC']
---
# [WC2011] 最大XOR和路径
## 题目描述

XOR（异或）是一种二元逻辑运算，其运算结果当且仅当两个输入的布尔值不相等时才为真，否则为假。 XOR 运算的真值表如下（$1$ 表示真， $0$ 表示假）：

| 输入 | 输入 | 输出 |
| :----------: | :----------: | :----------: |
| A | B | A XOR B |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |


而两个非负整数的 XOR 是指将它们表示成二进制数，再在对应的二进制位进行 XOR 运算。

譬如 $12$ XOR $9$ 的计算过程如下：

$$
12=(1100)_2\ \ \ 9=(1001)_2\\
\begin{matrix}
&1\ 1\ 0\ 0\\
\text{XOR}&1\ 0\ 0\ 1\\
\hline
&0\ 1\ 0\ 1\\
\end{matrix}\\
(0101)_2=5
$$

故 $12$ XOR $9 = 5$。

容易验证， XOR 运算满足交换律与结合律，故计算若干个数的 XOR 时，不同的计算顺序不会对运算结果造成影响。从而，可以定义 $K$ 个非负整数 $A_1$，$A_2$，……，$A_{K-1}$，$A_K$的 XOR 和为

$A_1$ XOR $A_2$ XOR …… XOR $A_{K-1}$ XOR $A_K$

考虑一个边权为非负整数的无向连通图，节点编号为 $1$ 到 $N$，试求出一条从 $1$ 号节点到 $N$ 号节点的路径，使得路径上经过的边的权值的 XOR 和最大。

路径可以重复经过某些点或边，当一条边在路径中出现了多次时，其权值在计算 XOR 和时也要被计算相应多的次数，具体见样例。

## 输入格式

输入文件 xor.in 的第一行包含两个整数 $N$ 和 $M$， 表示该无向图中点的数目与边的数目。

接下来 $M$ 行描述 $M$ 条边，每行三个整数 $S_i$， $T_i$ ， $D_i$， 表示 $S_i$ 与 $T_i$ 之间存在一条权值为 $D_i$ 的无向边。

图中可能有重边或自环。

## 输出格式

输出文件 xor.out 仅包含一个整数，表示最大的 XOR 和（十进制结果）。

## 样例

### 样例输入 #1
```
5 7
1 2 2
1 3 2
2 4 1
2 5 1
4 5 3
5 3 4
4 3 2
```
### 样例输出 #1
```
6
```
## 提示

【样例说明】

![](https://cdn.luogu.com.cn/upload/image_hosting/p6bf4fgf.png)

如图，路径$1 \rightarrow 2 \rightarrow 4 \rightarrow 3 \rightarrow 5 \rightarrow 2 \rightarrow 4 \rightarrow 5$对应的XOR和为

$2$ XOR $1$ XOR $2$ XOR $4$ XOR $1$ XOR $1$ XOR $3 = 6$

当然，一条边数更少的路径$1 \rightarrow 3 \rightarrow 5$对应的XOR和也是$2$ XOR $4 = 6$。

【数据规模】

对于 $20 \%$ 的数据，$N \leq 100$， $M \leq 1000$，$D_i \leq 10^{4}$；

对于 $50 \%$ 的数据，$N \leq 1000$， $M \leq 10000$，$D_i \leq 10^{18}$；

对于 $70 \%$ 的数据，$N \leq 5000$， $M \leq 50000$，$D_i \leq 10^{18}$；

对于 $100 \%$ 的数据，$N \leq 50000$， $M \leq 100000$，$D_i \leq 10^{18}$。





---

---
title: "[NOI2006] 最大获利"
layout: "post"
diff: 省选/NOI-
pid: P4174
tag: ['2006', 'NOI', '网络流', '广度优先搜索 BFS', '深度优先搜索 DFS']
---
# [NOI2006] 最大获利
## 题目描述

新的技术正冲击着手机通讯市场，对于各大运营商来说，这既是机遇，更是挑战。THU 集团旗下的 CS&T 通讯公司在新一代通讯技术血战的前夜，需要做太多的准备工作，仅就站址选择一项，就需要完成前期市场研究、站址勘测、最优化等项目。

在前期市场调查和站址勘测之后，公司得到了一共 $N$ 个可以作为通讯信号中转站的地址，而由于这些地址的地理位置差异，在不同的地方建造通讯中转站需要投入的成本也是不一样的，所幸在前期调查之后这些都是已知数据：建立第 $i$ 个通讯中转站需要的成本为 $P_i$（$1 \leq i \leq N$）。

另外公司调查得出了所有期望中的用户群，一共 $M$ 个。关于第 $i$ 个用户群的信息概括为 $A_i$，$B_i$ 和 $C_i$ ：这些用户会使用中转站 $A_i$ 和中转站 $B_i$ 进行通讯，公司可以获益 $C_i$。（$1 \leq i \leq M$，$1 \leq A_i, B_i \leq N$）

THU 集团的 CS&T 公司可以有选择的建立一些中转站（投入成本），为一些用户提供服务并获得收益（获益之和）。那么如何选择最终建立的中转站才能让公司的净获利最大呢？（净获利 = 获益之和 – 投入成本之和）

## 输入格式

输入文件中第一行有两个正整数 $N$ 和 $M$。

第二行中有 $N$ 个整数描述每一个通讯中转站的建立成本，依次为 $P_1 , P_2 , …,P_N$。

以下 $M$ 行，第 $i + 2$ 行的三个数 $A_i , B_i$ 和 $C_i$ 描述第 $i$ 个用户群的信息。

所有变量的含义可以参见题目描述。

## 输出格式

你的程序只要向输出文件输出一个整数，表示公司可以得到的最大净获利。

## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 2 3
2 3 4
1 3 3
1 4 2
4 5 3
```
### 样例输出 #1
```
4
```
## 提示

样例：选择建立 $1,2,3$ 号中转站，则需要投入成本 $6$，获利为 $10$，因此得到最大收益 $4$。

$100\%$ 的数据中：$N \leq 5\,000$，$M \leq50\,000$，$0 \leq C_i \leq 100$，$0 \leq P_i  \leq 100$。



---

---
title: "[NOI2005] 智慧珠游戏"
layout: "post"
diff: 省选/NOI-
pid: P4205
tag: ['搜索', '2005', 'NOI', '枚举', '剪枝', 'Dancing Links']
---
# [NOI2005] 智慧珠游戏
## 题目描述

智慧珠游戏拼盘由一个三角形盘件和 12 个形态各异的零件组成。拼盘的盘 件如图 1 所示
![](https://cdn.luogu.com.cn/upload/pic/13767.png)
![](https://cdn.luogu.com.cn/upload/pic/13768.png)
![](https://cdn.luogu.com.cn/upload/pic/13769.png)
对 于 由珠子构成的零件，可以放到盘件的任一位置，条件是能有地方放，且 尺寸合适，所有的零件都允许旋转(0º、90º、180º、270º)和翻转(水平、竖直)。
 
 
现给出一个盘件的初始布局，求一种可行的智慧珠摆放方案，使所有的零件 都能放进盘件中。 
## 输入格式

文件中包含初始的盘件描述，一共有 10 行，第 i 行有 i 个字符。如果第 i 行 的第 j 个字符是字母”A”至”L”中的一个，则表示第 i 行第 j 列的格子上已经放了 零件，零件的编号为对应的字母。如果第 i 行的第 j 个字符是”.”，则表示第 i 行 第 j 列的格子上没有放零件。
输入保证预放的零件已摆放在盘件中。
## 输出格式

如果能找到解，向输出文件打印 10 行，为放完全部 12 个零件后的布局。其 中，第 i 行应包含 i 个字符，第 i 行的第 j 个字符表示第 i 行第 j 列的格子上放的 是哪个零件。 如果无解，输出单独的一个字符串‘No solution’(不要引号，请注意大小写)。
 所有的数据保证最多只有一组解
## 样例

### 样例输入 #1
```
.
..
...
....
.....
.....C
...CCC.
EEEHH...
E.HHH....
E.........
```
### 样例输出 #1
```
B
BK
BKK
BJKK
JJJDD
GJGDDC
GGGCCCI
EEEHHIIA
ELHHHIAAF
ELLLLIFFFF
```


---

---
title: "连环病原体"
layout: "post"
diff: 省选/NOI-
pid: P4230
tag: ['深度优先搜索 DFS', '动态树 LCT', '期望', '差分']
---
# 连环病原体
## 题目背景

###（一）洞穴

顺着狭窄倾斜的溶洞向下走，这里，真有一番地心探险的感觉呢。

告诉你啊，地底有一片广阔的大世界，叫做旧地狱。

那里居住着被地面上的人厌恶的妖怪们。

虽然听着比较吓人，但实际上在地狱废弃后，一切都是井井有条的。

前方有一片开阔的空间啊，好像有人。

"地面上的来客吗,你好啊"

终于遇到地底的居民了。

眼前的两只妖怪是黑谷山女和琪斯美。

琪斯美呆在一个小桶里，悬挂在空中，和山女讨论着什么。

"哇，你们在讨论什么啊"

"嗯，有关病毒的问题，你们不懂的"

忘记说了，山女可以操纵疾病，所以谈论这样的话题自然也就很平常了。

不过好奇心很难抵挡啊，那就假装自己能帮上忙，然后接着问下去吧。

"好吧，你们要是能帮上忙的话就再好不过了"

"嗯，主要是，想知道病原体之间的相互作用，会对疾病产生什么影响呢。你看啊，把不同种的病原体看做点，相互作用看成连接这些点的线，如果产生了环，那么病毒的威力就会大幅加强，我把它叫做加强环。"

"病原体之间的相互作用也有很多种呢，我想研究的是，每种相互作用在产生加强环的过程中有多么重要。"

啊，听起来好复杂，不过如果帮了她的忙，地底的妖怪们大概会对我们友善一些吧。

而且，点，边，环？这些名词似乎见过呢，说不定我真的能帮上忙？

那么，继续详细地询问吧。

嗯，问出来的信息已经记录在这张纸上了。

## 题目描述

问题摘要:

有n 种病原体，它们之间会产生$m$种无方向性的影响，第$i$种影响发生在$u_i$,$v_i$ **两种**病原体之间。

我们把所有的**影响**按编号顺序排成一个序列，如果某一个区间包含有环，那么这个区间被称作加强区间。

求每种影响分别在多少个加强区间中出现过。

那么，到底怎样做才能高效的得出结果呢？

(后续剧情见本题题解，接下来请看T2)
## 输入格式

第一行一个数$m$
接下来$m$行每行两个数$u_i$,$v_i$，用空格分隔
## 输出格式

一行$m$个数字，第$i$个数字代表第$i$种影响在多少个加强区间内出现过，数字之间用空格分隔
## 样例

### 样例输入 #1
```
5
1 2
2 3
3 4
1 4
4 2

```
### 样例输出 #1
```
2 3 3 3 2
```
## 提示

###样例解释：

第一种影响在[1,4]和[1,5]两个加强区间内出现

第二种影响在[1,4]、[1,5]和[2,5]三个加强区间内出现

第三种影响在[1,5]、[1,4]和[2,5]三个加强区间内出现

第四种影响在[1,4]、[2,5]和[1,5]三个加强区间内出现

第五种影响在[2,5]和[1,5]两个加强区间内出现

注意：加强区间是由“影响”构成的，而不是由“病原体”构成的

$n\leqslant2m\leqslant400000$

测试点1~2总分10分，$m\leqslant5$

测试点3~6总分20分，$m\leqslant200$

测试点7~12总分30分，$m\leqslant5000$

测试点13~15总分15分，$m\leqslant50000$

测试点16~18总分15分，$m\leqslant50000$，捆绑测试

测试点19~22总分10分，$m\leqslant200000$，捆绑测试

by oscar


---

---
title: "最小差值生成树"
layout: "post"
diff: 省选/NOI-
pid: P4234
tag: ['图论', 'O2优化', '枚举', '深度优先搜索 DFS', '生成树', '动态树 LCT']
---
# 最小差值生成树
## 题目描述

给定一个点标号从 $1$ 到 $n$ 的、有 $m$ 条边的无向图，求边权最大值与最小值的差值最小的生成树。图可能存在自环。
## 输入格式

第一行有两个整数，表示图的点数 $n$ 和边数 $m$。

接下来 $m$ 行，每行三个整数 $u, v, w$，表示存在一条连接 $u, v$ 长度为 $w$ 的边。
## 输出格式

输出一行一个整数，表示答案。

## 样例

### 样例输入 #1
```
4 6 
1 2 10 
1 3 100 
1 4 90 
2 3 20 
2 4 80 
3 4 40 

```
### 样例输出 #1
```
20
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n \leq 100$，$m \leq 10^3$。
- 对于 $97\%$ 的数据，保证 $n \leq 500$，$m \leq 10^5$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 5 \times 10^4$，$1 \leq m \leq 2 \times 10^5$，$1 \leq u, v \leq n$，$1 \leq w \leq 10^4$。


---

---
title: "[SHOI2008] 仙人掌图 II"
layout: "post"
diff: 省选/NOI-
pid: P4244
tag: ['动态规划 DP', '2008', '各省省选', '上海', '深度优先搜索 DFS', '区间 DP', '仙人掌']
---
# [SHOI2008] 仙人掌图 II
## 题目背景

题目这个II是和[SHOI2006的仙人掌图](https://www.luogu.org/problemnew/show/P4129)区分的，bzoj没有。
**但是实际上还是和bzoj1023是一个题目的**。
## 题目描述

如果某个无向连通图的任意一条边至多只出现在一条简单回路（simple cycle）里，我们就称这张图为仙人掌图（cactus）。所谓简单回路就是指在图上不重复经过任何一个顶点的回路。

![](https://cdn.luogu.com.cn/upload/pic/13241.png)

举例来说，上面的第一个例子是一张仙人图，而第二个不是——注意到它有三条简单回路：（4，3，2，1，6，5，4）、（7，8，9，10，2，3，7）以及（4，3，7，8，9，10，2，1，6，5，4），而（2，3）同时出现在前两个的简单回路里。另外，第三张图也不是仙人图，因为它并不是连通图。显然，仙人图上的每条边，或者是这张仙人图的桥（bridge），或者在且仅在一个简单回路里，两者必居其一。定义在图上两点之间的距离为这两点之间最短路径的距离。定义一个图的直径为这张图相距最远的两个点的距离。**现在我们假定仙人图的每条边的权值都是1，你的任务是求出给定的仙人图的直径**。
## 输入格式

输入的第一行包括两个整数n和m（1≤n≤50000以及0≤m≤10000）。其中n代表顶点个数，我们约定图中的顶点将从1到n编号。接下来一共有m行。代表m条路径。每行的开始有一个整数k（2≤k≤1000），代表在这条路径上的顶点个数。接下来是k个1到n之间的整数，分别对应了一个顶点，相邻的顶点表示存在一条连接这两个顶点的边。一条路径上可能通过一个顶点好几次，比如对于第一个样例，第一条路径从3经过8，又从8返回到了3，但是我们保证所有的边都会出现在某条路径上，而且不会重复出现在两条路径上，或者在一条路径上出现两次。
## 输出格式

只需输出一个数，这个数表示仙人图的直径长度。
## 样例

### 样例输入 #1
```
15 3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
5 2 14 9 15 10
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
10 1
10 1 2 3 4 5 6 7 8 9 10
```
### 样例输出 #2
```
9
```
## 提示


对第一个样例的说明：6号点和12号点的最短路径长度为8，所以这张图的直径为8。

【注意】使用Pascal语言的选手请注意：你的程序在处理大数据的时候可能会出现栈溢出。
如果需要调整栈空间的大小，可以在程序的开头填加一句：{\$M 5000000}，其中5000000即指代栈空间的大小，请根据自己的程序选择适当的数值。


---

---
title: "首都"
layout: "post"
diff: 省选/NOI-
pid: P4299
tag: ['搜索', '并查集', '剪枝', '动态树 LCT']
---
# 首都
## 题目描述

在 X 星球上有 $n$ 个国家，每个国家占据着 X 星球的一座城市，城市从 $1$ 至 $n$ 编号。由于国家之间是敌对关系，所以不同国家的两个城市是不会有公路相连的。

X 星球上战乱频发，如果 A 国打败了 B 国，那么 B 国将永远从这个星球消失，而 B 国的国土也将归 A 国管辖。A 国国王为了加强统治，会在 A 国和 B 国之间修建一条公路，即选择原 A 国的某个城市和 B 国某个城市，修建一条连接这两座城市的公路。

同样为了便于统治自己的国家，国家的首都会选在某个使得其他城市到它距离之和最小的城市，这里的距离是指需要经过公路的条数，如果有多个这样的城市，编号最小的将成为首都。

现在告诉你发生在 X 星球的战事，需要你处理一些关于国家首都的信息，具体地，有如下3种信息需要处理：

- `A x y`：表示某两个国家发生战乱，战胜国选择了 $x$ 城市和 $y$ 城市，在它们之间修建公路（保证其中城市一个在战胜国另一个在战败国）。
- `Q x`：询问当前编号为 $x$ 的城市所在国家的首都。
- `Xor`：询问当前所有国家首都编号的异或和。

## 输入格式

输入的第一行有两个整数，分别表示城市数 $n$ 和需要处理的信息数 $m$。

接下来 $m$ 行，每行首先有一个字符串 $op$，表示信息类型，后有若干个整数，其格式如【题目描述】所示。
## 输出格式

对于每个 `Q` 操作和 `Xor` 操作，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
10 10 
Xor 
Q 1 
A 10 1 
A 1 4 
Q 4 
Q 10 
A 7 6 
Xor 
Q 7 
Xor
```
### 样例输出 #1
```
11 
1 
1 
1 
2 
6 
2 

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 10^5$，$1 \leq m \leq 2 \times 10^5$，$1 \leq x, y \leq n$。


---

---
title: "[JSOI2016] 独特的树叶"
layout: "post"
diff: 省选/NOI-
pid: P4323
tag: ['2016', '江苏', '深度优先搜索 DFS', '哈希 hashing']
---
# [JSOI2016] 独特的树叶
## 题目描述

JYY有两棵树 $A$ 和 $B$ ：树 $A$ 有 $N$ 个点，编号为 $1$ 到 $N$ ；树 $B$ 有$N+1$ 个节点，编号为 $1$ 到$N+1$

JYY 知道树 $B$ 恰好是由树 $A$ 加上一个叶节点，然后将节点的编号打乱后得到的。他想知道，这个多余的叶子到底是树 $B$ 中的哪一个叶节点呢？
## 输入格式

输入一行包含一个正整数 $N$。 接下来 $N-1$ 行，描述树$ A$，每行包含两个整数表示树 $A$ 中的一条边； 接下来 $N$ 行，描述树 $B$，每行包含两个整数表示树 $B$ 中的一条边。
## 输出格式

输出一行一个整数，表示树 $B$ 中相比树 $A$ 多余的那个叶子的编号。如果有多个符合要求的叶子，输出 $B$ 中编号最小的那一个的编号。
## 样例

### 样例输入 #1
```
5
1 2
2 3
1 4
1 5
1 2
2 3
3 4
4 5
3 6
```
### 样例输出 #1
```
1

```
## 提示

对于所有数据，$1 \leq n \leq 10 ^ 5$


---

---
title: "[CQOI2016] 伪光滑数"
layout: "post"
diff: 省选/NOI-
pid: P4359
tag: ['搜索', '2016', '重庆', '各省省选', '可并堆', '素数判断,质数,筛法']
---
# [CQOI2016] 伪光滑数
## 题目描述

若一个大于 $1$ 的整数 $M$ 的质因数分解有 $k$ 项，其最大的质因子为 $a_k$ ，并且满足 $a_{k}^{k} \le N$，$a_k < 128$，我们就称整数 $M$ 为 $N$ - 伪光滑数。

现在给出 $N$，求所有整数中，第 $K$ 大的 $N$ - 伪光滑数。

### 题意澄清

设 $M = 36 = 2^2 \times 3^2$，则其对应的 $k = 4$，也就是说，对 $M$ 运用唯一分解定理，$M = \prod_{i=1}^n{p_i^{c_i}}$，$k = \sum_{i=1}^n{c_i}$。

第 $K$ 大为字面意思，是真的从大到小第 $K$ 个。

modified by expect2004 2020-11-25，这或许是他退役前对洛谷公共题库的最后一次贡献
## 输入格式

只有一行，为用空格隔开的整数 $N$ 和 $K$ 。
## 输出格式

只有一行，为一个整数，表示答案。
## 样例

### 样例输入 #1
```
12345 20
```
### 样例输出 #1
```
9167
```
## 提示

对于 $30\%$ 的数据，$N \le 10^6$；  
对于 $100\%$ 的数据，$2 \le N \le 10^{18},1 \le K \le 800000$。保证至少有 $K$ 个满足要求的数。


---

---
title: "[九省联考 2018] 一双木棋 chess"
layout: "post"
diff: 省选/NOI-
pid: P4363
tag: ['搜索', '2018', '各省省选', '状压 DP']
---
# [九省联考 2018] 一双木棋 chess
## 题目描述

菲菲和牛牛在一块 $n$ 行 $m$ 列的棋盘上下棋，菲菲执黑棋先手，牛牛执白棋后手。

棋局开始时，棋盘上没有任何棋子，两人轮流在格子上落子，直到填满棋盘时结束。  

落子的规则是：一个格子可以落子当且仅当这个格子内没有棋子且这个格子的左侧及上方的所有格子内都有棋子。

棋盘的每个格子上，都写有两个非负整数，从上到下第 $i$ 行中从左到右第 $j$ 列的格子上的两个整数记作 $a_{i,j}$ 和 $b_{i,j}$。

在游戏结束后，菲菲和牛牛会分别计算自己的得分：菲菲的得分是所有有黑棋的格子上的 $a_{i,j}$ 之和，牛牛的得分是所有有白棋的格子上的 $b_{i,j}$ 的和。

菲菲和牛牛都希望，自己的得分减去对方的得分得到的结果最大。现在他们想知道，在给定的棋盘上，如果双方都采用最优策略且知道对方会采用最优策略，那么，最终的结果如何？

## 输入格式

第一行有两个整数，分别表示棋盘的行数 $n$ 和列数 $m$。  
第 $2$ 到第 $(n + 1)$ 行，每行 $m$ 个整数，第 $(i + 1)$ 行的第 $j$ 个整数表示 $a_{i, j}$。  
第 $(n + 2)$ 到第 $(2n + 1)$ 行，每行 $m$ 个整数，第 $(n + i + 1)$ 行的第 $j$ 个整数表示 $b_{i, j}$。
## 输出格式

输出一行一个整数，表示菲菲的得分减去牛牛的得分的结果。
## 样例

### 样例输入 #1
```
2 3
2 7 3
9 1 2
3 7 2
2 3 1

```
### 样例输出 #1
```
2
```
## 提示

### 样例 1 说明

![](https://cdn.luogu.com.cn/upload/pic/16877.png)

棋盘如图所示，双方都采用最优策略时，棋局如下：

- 菲菲下在第 $1$ 行第 $1$ 列（这是第一步时唯一可以落子的格子）。
- 牛牛下在第 $1$ 行第 $2$ 列。
- 菲菲下在第 $2$ 行第 $1$ 列。
- 牛牛下在第 $1$ 行第 $3$ 列。
- 菲菲下在第 $2$ 行第 $2$ 列。
- 牛牛下在第 $2$ 行第 $3$ 列（这是这一步时唯一可以落子的格子）。
- 填满棋盘，游戏结束。

盘面如下：

![](https://cdn.luogu.com.cn/upload/pic/16878.png)

菲菲的得分为 $2 + 9 + 1 = 12$，牛牛的得分为 $7 + 2 + 1 = 10$。

### 数据规模与约定

各测试点信息如下表。

![](https://cdn.luogu.com.cn/upload/pic/16879.png)

- 对于编号为奇数的测试点，保证 $b_{i, j} = 0$。
- 对于全部的测试点，保证 $1 \leq n, m \leq 10$，$0 \leq a_{i, j}, b_{i, j} \leq 10^5$。



---

---
title: "[CQOI2018] 解锁屏幕"
layout: "post"
diff: 省选/NOI-
pid: P4460
tag: ['2018', '重庆', '各省省选', '广度优先搜索 BFS', '状压 DP']
---
# [CQOI2018] 解锁屏幕
## 题目背景

使用过 Android 手机的同学一定对手势解锁屏幕不陌生。 Android 的解锁屏幕由 $3 \times 3$ 个点组成，手指在屏幕上画一条线，将其中一些点连接起来，即可构成一个解锁图案。如下面三个例子所示：

![](https://cdn.luogu.com.cn/upload/pic/17556.png)
![](https://cdn.luogu.com.cn/upload/pic/17557.png)
![](https://cdn.luogu.com.cn/upload/pic/17558.png)
## 题目描述

画线时还需要遵循一些规则：
1. 连接的点数不能少于 $4$ 个。也就是说只连接两个点或者三个点会提示错误。
2. 两个点之间的联线不能弯曲。
3. 每个点只能“使用”一次，不可重复。这里的“使用”是指手指划过一个点，该点变绿。
4. 两个点之间的连线不能“跨过”另一个点，除非那个点之前已经被“使用”过。

对于最后一条规则，参见下图的解释。左边两幅图违反了该规则；而右边两幅图（分别为 $ 2 \rightarrow 4 \rightarrow 1 \rightarrow 3 \rightarrow 6$ 和 $ 6 \rightarrow 5 \rightarrow 4 \rightarrow 1 \rightarrow 9 \rightarrow 2$ ）则没有违反规则，因为在“跨过”点时，点已经被使用过了。

![](https://cdn.luogu.com.cn/upload/pic/17566.png)

现在工程师希望改进解锁屏幕，增减点的数目，并移动点的位置，不再是一个九宫格形状，但保持上述画线规则不变。

请计算新的解锁屏幕上，一共有多少满足规则的画线方案。
## 输入格式

输入第一行为一个整数 $n$ ，表示点的数目。

接下来 $n$ 行，每行两个空格分开的整数 $x_i$ 和 $y_i$ ，表示每个点的坐标。
## 输出格式

输出共一行，为题目所求方案数除以 $10^8+7$ 的余数。
## 样例

### 样例输入 #1
```
4
0 0
1 1
2 2
3 3
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
4
0 0
0 1
0 2
1 0
```
### 样例输出 #2
```
18
```
## 提示

#### 样例解释 1

设 $4$ 个点编号为 $1$ 到 $4$ ，方案有 $1 \rightarrow 2 \rightarrow 3 \rightarrow 4$ ， $2 \rightarrow 1 \rightarrow 3 \rightarrow 4$ ，  $3 \rightarrow 2 \rightarrow 1 \rightarrow 4$ ，  $2 \rightarrow 3 \rightarrow 1 \rightarrow 4$ 以及它们的镜像。

### 数据范围

- 对于 $30\%$ 的数据，$1 \le n \le 10$。
- 对于 $100\%$ 的数据，$-1000 \le x_i ,y_i \le 1000$，$ 1 \le n < 20$。各点坐标不相同。


---

---
title: "[CQOI2018] 九连环"
layout: "post"
diff: 省选/NOI-
pid: P4461
tag: ['搜索', '2018', '重庆', '各省省选', '快速傅里叶变换 FFT']
---
# [CQOI2018] 九连环
## 题目背景

九连环是一种源于中国的传统智力游戏。如图所示，九个的圆环套在一把“剑”上，并且互相牵连。游戏的目标是把九个圆环全部从“剑”上卸下。

![](https://cdn.luogu.com.cn/upload/pic/17568.png)
## 题目描述

圆环的装卸需要遵守两个规则:

1. 第一个(最右边) 环任何时候都可以任意装上或卸下

2. 如果第k 个环没有被卸下，且第k 个环右边的所有环都被卸下，则第k+1个环(第k 个环左边相邻的环) 可以任意装上或卸下

与魔方的千变万化不同，解九连环的最优策略是唯一的。为简单起见，我们以“四连环”为例，演示这一过程。这里用1表示环在“剑”上，0 表示环已经卸下。

初始状态为1111,每步的操作如下:

1. 1101 (根据规则2,卸下第2 个环)

2. 1100 (根据规则1,卸下第1 个环)

3. 0100 (根据规则2,卸下第4 个环)

4. 0101 (根据规则1,装上第1 个环)

5. 0111 (根据规则2,装上第2 个环)

6. 0110 (根据规则1,卸下第1 个环)

7. 0010 (根据规则2,卸下第3 个环)

8. 0011 (根据规则1,装上第1 个环)

9. 0001 (根据规则2,卸下第2 个环)

10. 0000 (根据规则1,卸下第1 个环)

由此可见，卸下“四连环”至少需要10 步。随着环数增加，需要的步数也会随之增多。例如卸下九连环，就至少需要341步。

请你计算，有n 个环的情况下，按照规则，  全部卸下至少需要多少步。
## 输入格式

输入文件第一行，为一个整数m，表示测试点数目。

接下来m行，每行一个整数n。
## 输出格式

输出文件共m行，对应每个测试点的计算结果。
## 样例

### 样例输入 #1
```
3
3
5
9
```
### 样例输出 #1
```
5
21
341
```
## 提示

对于10%的数据，$1≤n≤10$

对于30%的数据，$1≤n≤30$

对于100%的数据，$1≤n≤10^5,1≤m≤10$


---

---
title: "[SDOI2018] 战略游戏"
layout: "post"
diff: 省选/NOI-
pid: P4606
tag: ['2018', '各省省选', '山东', 'O2优化', '深度优先搜索 DFS', '双连通分量', '虚树', '圆方树']
---
# [SDOI2018] 战略游戏
## 题目描述

省选临近，放飞自我的小 Q 无心刷题，于是怂恿小 C 和他一起颓废，玩起了一款战略游戏。

这款战略游戏的地图由 $n$ 个城市以及 $m$ 条连接这些城市的双向道路构成，并且从任意一个城市出发总能沿着道路走到任意其他城市。

现在小 C 已经占领了其中至少两个城市，小 Q 可以摧毁一个小 C 没占领的城市，同时摧毁所有连接这个城市的道路。只要在摧毁这个城市之后能够找到某两个小 C 占领的城市 $u$ 和 $v$，使得从 $u$ 出发沿着道路无论如何都不能走到 $v$，那么小 Q 就能赢下这一局游戏。

小 Q 和小 C 一共进行了 $q$ 局游戏，每一局游戏会给出小 C 占领的城市集合 $S$，你需要帮小 Q 数出有多少个城市在他摧毁之后能够让他赢下这一局游戏。
## 输入格式

第一行包含一个正整数 $T$，表示测试数据的组数。

对于每组测试数据：

第一行是两个整数 $n$ 和 $m$ ，表示地图的城市数和道路数。

接下来 $m$ 行，每行包含两个整数 $u$ 和 $v (1 \le u < v \le n)$，表示第 $u$ 个城市和第 $v$ 个城市之间有一条道路，同一对城市之间可能有多条道路连接。


第 $m + 1$ 是一个整数 $q$，表示游戏的局数，

接下来 $q$ 行，每行先给出一个整数 $|S| (2 \le |S| \le n)$，表示小 C 占领的城市数量，然后给出 $|S|$ 个整数 $(1 \le S_1 < S_2 < \cdots < S_{|S|} ≤ n)$，表示小 C 占领的城市。
## 输出格式

对于每一局游戏，输出一行，包含一个整数，表示这一局游戏中有多少个城市在小 Q 摧毁之后能够让他赢下这一局游戏。
## 样例

### 样例输入 #1
```
2
7 6
1 2
1 3
2 4
2 5
3 6
3 7
3
2 1 2
3 2 3 4
4 4 5 6 7
6 6
1 2
1 3
2 3
1 4
2 5
3 6
4
3 1 2 3
3 1 2 6
3 1 5 6
3 4 5 6

```
### 样例输出 #1
```
0
1
3
0
1
2
3
```
## 提示

- $1 \le T \le 10$；
- $2 \le n \le 10^5$ 且 $n - 1 \le m \le 2\times 10 ^ 5$；
- $1 \le q \le 10^5$；
- 对于每组测试数据，有 $\sum|S| \le 2 \times 10^5$。

### Subtasks

- 子任务 1 (30 分)：对于每组测试数据，满足 $\sum|S| \le 20$；
- 子任务 2 (45 分)：对于每一次询问，满足 $|S| = 2$；
- 子任务 3 (25 分)：没有任何附加的限制。



---

---
title: "[CTSC2000] 采矿"
layout: "post"
diff: 省选/NOI-
pid: P4624
tag: ['搜索', '2000', '剪枝', 'CTSC/CTS']
---
# [CTSC2000] 采矿
## 题目背景

一架人类的航天飞机将人类基地建在了一个荒芜的星球上。面对紧缺的能源，他们只能在最短的时间内用 $\text{SCV}$ （一种智能机器人）采集必须的矿藏。对于这个艰巨的任务，他们希望得到编程高手们的帮助。
## 题目描述

在这个星球上，有着两种不同的矿。一种被称为“冰矿”，是一种类似 $\text{H}_{2}\text{O}$ 的凝固物的蓝色高能矿藏。另一种被称为“气矿”，是四氯化碳的一种异态形式。

人类通过这两种矿的提炼，获得可供生存的能源。 $\text{SCV}$ 是一种唯一可以采集这两种矿的智能机器人。他们每采集一次冰矿需要花费 $t_{1}$ 的时间，每采集一次气矿需要花费 $t_{2}$ 的时间。采集结束后，将得到 $8$ 个冰矿或者 $8$ 个气矿单位。**每一次 $\text{SCV}$ 只能采集冰矿或者是气矿中的一种**。

 $\text{SCV}$ 可以通过主基地制造。每制造一个 $\text{SCV}$ ，主基地将花费 $50$ 单位的冰矿。而主基地由于制造能力有限，在同一时间只能制造**一个** $\text{SCV}$ 。制造一个 $\text{SCV}$ 需要 $t_{3}$ 的时间。

在开始时，人类拥有 $50$ 个单位的冰矿和 $4$ 个 $\text{SCV}$ 。他们需要采集到 $p_{1}$ 单位的冰矿和 $p_{2}$ 单位的气矿。请计算出他们需要的**最短时间**。
## 输入格式

输入文件只有一行，依次为 $t_{1}$ , $t_{2}$ , $t_{3}$ , $p_{1}$ , $p_{2}$ ，每两个数字之间有一个空格。
## 输出格式

输出文件只包含一个数字，表示可以达到目标的最少时间。
## 样例

### 样例输入 #1
```
10 9 18 150 0
```
### 样例输出 #1
```
40
```
## 提示

$1 \leq t_{1},t_{2},t_{3} \leq 18$，$0 \leq p_{1},p_{2} \leq 150$。数据从合法数据中随机均匀选取。


---

---
title: "[BalticOI 2018] 多角恋"
layout: "post"
diff: 省选/NOI-
pid: P4790
tag: ['动态规划 DP', '贪心', '2018', '深度优先搜索 DFS', 'BalticOI（波罗的海）']
---
# [BalticOI 2018] 多角恋
## 题目描述

**题目译自 [BalticOI 2018](https://boi2018.progolymp.se/tasks/) Day1「[Love Polygon](https://boi18-day1-open.kattis.com/problems/boi18.polygon)」**

给一张 $N$ 个点的有向图，每个点的出度为 $1$。每次可以花费 $1$ 的代价修改图上的一条边的终点，也就是改变从一个点出发所到达的点。求最少需要花费多少代价，才能使这张图形成若干个两两不相交的二元环，并且图上的所有点都在某一个环里。
## 输入格式

第一行包含一个整数 $N$。

接下来的 $N$ 行每行包含两个字符串 $s$ 和 $t$，表示图中存在一条 $s\rightarrow t$ 的边。

字符串只包含小写英文字母，且长度不超过 $10$。
## 输出格式

输出一个整数，表示最少需要花费多少代价，才能使这张图形成若干个两两不相交的二元环，并且图上的所有点都在某一个环里。无解请输出 $-1$。
## 样例

### 样例输入 #1
```
8
leonard emmy
ada emmy
isaac leonard
emmy pierre
pierre bernhard
bernhard emmy
sofia karl
karl sofia
```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
4
a c
b c
c d
d d
```
### 样例输出 #2
```
3

```
### 样例输入 #3
```
3
rocky scarlet
scarlet patrick
patrick rocky
```
### 样例输出 #3
```
-1

```
## 提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/1ojydan1.png)

唯一的最优解如上图所示，图的上半部分为原图，底色为粉色的三个点为需要修改的边的起点；图的下半部分表示修改后的情况。

#### 样例 2 解释

存在多组最优解。其中一种是分别改变一条以 ``a``、``b`` 和 ``d`` 为起点的边，使他们分别连接到 ``b``、``a`` 和 `c`。

#### 样例 3 解释

图中有 $3$ 个点，无论如何修改边的终点，总会有一个人不在环里。


| 子任务 | 分值 | 数据范围 | 附加限制 |
|:----------:|:-------:|:-------------:|:-------------:|
|$1$|$21$|$2\leqslant N\leqslant 20$|.|
|$2$|$25$|$2\leqslant N\leqslant 100\, 000$|每个点都有一条入边（可能有自环）|
|$3$|$29$|$2\leqslant N\leqslant 100\, 000$|不存在两个点或更多个点构成的环|
|$4$|$25$|$2\leqslant N\leqslant 100\, 000$|.|




---

---
title: "【模板】最小割树（Gomory-Hu Tree）"
layout: "post"
diff: 省选/NOI-
pid: P4897
tag: ['网络流', '深度优先搜索 DFS', '最小割']
---
# 【模板】最小割树（Gomory-Hu Tree）
## 题目背景

模板题。做本题之前请确保你会 Dinic 或 ISAP。如果你乱搞过了我请你抽烟。

根据惯例，网络流题不允许卡 Dinic/ISAP，但可以卡 EK，本题数据严格遵循上述条约。
## 题目描述

给定一个 $n$ 个点 $m$ 条边的无向连通图，多次询问两点之间的最小割。

两点间的最小割是这样定义的：原图的每条边有一个割断它的代价，你需要用最小的代价使得这两个点不连通。
## 输入格式

第一行两个数 $n,m$。

接下来 $m$ 行，每行 $3$ 个数 $u,v,w$，表示有一条连接 $u$ 与 $v$ 的无向边，割断它的代价为 $w$。

接下来这一行有一个整数$Q$，表示询问次数

接下来 $Q$ 行，每行两个数 $u,v$，你需要求出 $u$ 与 $v$ 之间的最小割

**注意：因为数据有误，给定图的真实点数应该是 $n+1$ 个，编号为 $0$ 到 $n$。**
## 输出格式

输出共 $Q$ 行，每行一个整数对应询问的答案
## 样例

### 样例输入 #1
```
4 5
1 2 2
2 3 2
4 2 3
4 3 1
1 3 1
3
1 4
2 4
2 3
```
### 样例输出 #1
```
3
4
4
```
## 提示

$1\le n\leq 500,\quad 0\le m\leq 1500,\quad 0\le Q\leq 10^5,\quad 0\leq w\leq 10^4,\quad u\neq v$


---

---
title: "[IOI 2018] werewolf 狼人"
layout: "post"
diff: 省选/NOI-
pid: P4899
tag: ['2018', '树状数组', 'IOI', 'O2优化', '深度优先搜索 DFS', '可持久化线段树']
---
# [IOI 2018] werewolf 狼人
## 题目背景

本题为交互题，但在此请提交**完整程序**。
## 题目描述

在日本的茨城县内共有 $N$ 个城市和 $M$ 条道路。这些城市是根据人口数量的升序排列的，依次编号为 $0$ 到 $N - 1$。每条道路连接两个不同的城市，并且可以双向通行。由这些道路，你能从任意一个城市到另外任意一个城市。

你计划了 $Q$ 个行程，这些行程分别编号为 $0$ 至 $Q - 1$。第 $i(0 \leq i \leq Q - 1)$ 个行程是从城市 $S_i$ 到城市 $E_i$。

你是一个狼人。你有两种形态：**人形**和**狼形**。在每个行程开始的时候，你是人形。在每个行程结束的时候，你必须是狼形。在行程中，你必须要变身（从人形变成狼形）恰好一次，而且只能在某个城市内（包括可能是在 $S_i$ 或 $E_i$ 内）变身。

狼人的生活并不容易。当你是人形时，你必须避开人少的城市，而当你是狼形时，你必须避开人多的城市。对于每一次行程 $i(0 \leq i \leq Q - 1)$，都有两个阈值 $L_i$ 和 $R_i(0 \leq L_i \leq R_i \leq N - 1)$，用以表示哪些城市必须要避开。准确地说，当你是人形时，你必须避开城市 $0, 1, \ldots , L_i - 1$ ；而当你是狼形时，则必须避开城市 $R_i + 1, R_i + 2, \ldots , N - 1$。这就是说，在行程 $i$ 中，你必须在城市 $L_i, L_i + 1, \ldots , R_i$ 中的其中一个城市内变身。

你的任务是，对每一次行程，判定是否有可能在满足上述限制的前提下，由城市 $S_i$ 走到城市 $E_i$。你的路线可以有任意长度。
## 输入格式

输入的第一行包含三个正整数 $N, M, Q$，其意义见题目描述。

接下来 $M$ 行，每行包含两个非负整数。在这 $M$ 行中，第 $j$ 行的两个非负整数分别表示 $X_{j - 1}, Y_{j - 1}$，即编号为 $j - 1$ 的道路连接的两个城市的编号。

接下来 $Q$ 行，每行包含四个非负整数。在这 $Q$ 行中，第 $i$ 行的四个非负整数分别表示 $S_{i - 1}, E_{i - 1}, L_{i - 1}, R_{i - 1}$，即编号为 $i - 1$ 的行程的起点城市编号、终点城市编号以及两个阈值。
## 输出格式

输出包含 $Q$ 行，每行包含一个非 $0$ 即 $1$ 的整数。第 $i$ 行的整数表示对于编号为 $i - 1$ 的行程，是否能从城市 $S_{i - 1}$ 走至城市 $E_{i - 1}$，若能够，那么输出整数为 $1$；若不能，那么输出整数为 $0$。
## 样例

### 样例输入 #1
```
6 6 3
5 1
1 2
1 3
3 4
3 0
5 2
4 2 1 2
4 2 2 2
5 4 3 4

```
### 样例输出 #1
```
1
0
0

```
### 样例输入 #2
```
10 9 10
6 7
1 5
8 0
2 9
9 4
2 7
8 5
6 0
3 4
4 9 0 9
8 1 8 9
1 8 1 8
8 3 5 5
8 9 3 9
0 1 0 2
9 0 6 6
1 7 1 8
9 4 5 6
9 5 0 9

```
### 样例输出 #2
```
1
1
1
0
1
1
0
1
0
1

```
## 提示

**限制条件**

- $2 \leq N \leq 200, 000$
- $N - 1 \leq M \leq 400, 000$
- $1 \leq Q \leq 200, 000$
- 对于每个 $0 \leq j \leq M - 1$
    - $0 \leq X_j \leq N - 1$
    - $0 \leq Y_j \leq N - 1$
    - $X_j \neq Y_j$
- 你可以通过道路由任意一个城市去另外任意一个城市。
- 每一对城市最多只由一条道路直接连起来。换言之，对于所有 $0 \leq j < k \leq M - 1$，都有 $(X_j, Y_j) \neq (X_k, Y_k)$ 和 $(Y_j, X_j) \neq (X_k, Y_k)$
- 对于每个 $0 \leq i \leq Q - 1$
    - $0 \leq L_i \leq S_i \leq N - 1$
    - $0 \leq E_i \leq R_i \leq N - 1$
    - $S_i \neq E_i$
    - $L_i \leq R_i$

**子任务**

- 1.（7 分）$N \leq 100$，$M \leq 200$，$Q \leq 100$。
- 2.（8 分）$N \leq 3, 000$，$M \leq 6, 000$，$Q \leq 3, 000$。
- 3.（34 分）$M = N - 1$ 且每个城市最多与两条路相连（所有城市是以一条直线的形式连起来）。
- 4.（51 分）没有附加限制。


---

---
title: "【模板】舞蹈链（DLX）"
layout: "post"
diff: 省选/NOI-
pid: P4929
tag: ['搜索', 'Special Judge', '剪枝', 'Dancing Links']
---
# 【模板】舞蹈链（DLX）
## 题目背景

本题是舞蹈链模板——精确覆盖问题
## 题目描述

给定一个 $N$ 行 $M$ 列的矩阵，矩阵中每个元素要么是 $1$，要么是 $0$。

你需要在矩阵中挑选出若干行，使得对于矩阵的每一列 $j$，在你挑选的这些行中，有且仅有一行的第 $j$ 个元素为 $1$。

## 输入格式

第一行两个数 $N,M$。

接下来 $N$ 行，每行 $M$ 个数字 $0$ 或 $1$，表示这个矩阵。

## 输出格式

一行输出若干个数表示答案，两个数之间用空格隔开，输出任一可行方案均可，顺序随意。

若无解，输出 `No Solution!`。

## 样例

### 样例输入 #1
```
3 3
0 0 1
1 0 0
0 1 0

```
### 样例输出 #1
```
2 1 3

```
### 样例输入 #2
```
3 3
1 0 1
1 1 0
0 1 1

```
### 样例输出 #2
```
No Solution!

```
## 提示

对于 $100\%$ 的数据，$N,M\leq 500$，保证矩阵中 $1$ 的数量不超过 $5000$ 个。


---

---
title: "流量计算"
layout: "post"
diff: 省选/NOI-
pid: P4946
tag: ['搜索', '数学', '图论']
---
# 流量计算
## 题目背景

NOIP2018原创模拟题T7

NOIP2018原创模拟赛DAY2 T2

NOIP DAY1 T2 or DAY2 T2 难度

相关电学知识请参考“说明”中的“背景知识”。
## 题目描述

你看了复杂的电路图，发现在初高中学的电路元件数都目比较少，因此你希望设计一个程序来分析元件数目更多的电路图，并进行一些计算。

经过苦苦思考，你终于找到了描述电路图的方法：

1.电路图可以用$n$个节点，$m$条无向边的连通图来表示，其中$n$表示导线交汇点，$m$表示元件个数，且电路元件只有电源和电阻

2.图中没有自环，但可能有重边

3.电路图**最复杂的情况是并联中嵌套串联**，**不会出现更复杂的电路**，例如下面的情况都不会出现：

![P1](https://cdn.luogu.com.cn/upload/pic/37113.png)

比如样例一便是一个满足条件的电路图（图片见样例一解释）

因为这是你第一次尝试，所以你决定电路中只包含电源与电阻，而且你决定计算电路中的最大电流与最小电流。

在理清思路后你就决定开始尝试了。
## 输入格式

共$m+1$行

第一行两个数 $n,m$，表示电路图抽象为$n$个节点，$m$条边的无向图

接下来$m$行，对于每一行：

前两个数为$x,y$，表示$x,y$之间有一个元件

接下来一个字符，如果为 $'P'$ 表示电源，且$x$方向为电源负极，$y$方向为电源正极，如果为 $'R'$ 表示电阻（均不含引号）

再接下来一个数字，如果为电源，表示电压（单位：伏特），否则表示电阻（单位：欧姆）
## 输出格式

两行

第一行输出最大电流值，保留两位小数

第二行输出最小电流值，保留两位小数
## 样例

### 样例输入 #1
```
4 5
1 2 P 6
2 3 R 2
3 4 R 1
2 4 R 1
1 3 R 1
```
### 样例输出 #1
```
3.00
1.50
```
### 样例输入 #2
```
4 6
1 3 P 6
1 3 R 1
1 2 R 1
2 3 R 1
1 4 R 1
4 3 R 2
```
### 样例输出 #2
```
11.00
2.00
```
### 样例输入 #3
```
16 21
1 2 R 2
2 3 R 1
3 4 R 1
2 5 R 1
4 5 R 1
4 6 R 1
6 7 R 1
7 8 R 2
4 9 R 1
8 9 R 1
1 16 P 128
10 8 R 7
10 11 R 2
11 10 R 1
11 12 R 2
12 15 R 1
15 13 R 2
11 13 R 1
11 14 R 1
14 15 R 2
15 16 R 5
```
### 样例输出 #3
```
7.11
2.37
```
## 提示

**背景知识：**

欧姆定理：$I=\frac{U}{R}$，其中$I$为电流，$U$为电压，$R$为电阻

串联：串联电路中电流相等，总电阻相当于电阻阻值之和

并联：并联电路中电压相等

串并联：即串联与并联结合

![P3](https://cdn.luogu.com.cn/upload/pic/37135.png)

**样例一解释：**

![P4](https://cdn.luogu.com.cn/upload/pic/37121.png)

如图，所有电阻等效电阻为$2Ω$，故最大电流为$\frac{6V}{2Ω}=3A$，在支线$2-3$或$2-4-3$中电流为$1.5A$，为最小电流

**样例二/三提示：**

样例二中所有电阻的等效电阻阻值为$\frac{6}{11}Ω$，且最小电流在支线$1-4-3$上，样例三中所有电阻的等效电阻阻值为$18Ω$

**数据范围：**

对于 30%数据，有：$n,m<=20$

对于 50%数据，有：$n<=10^3,m<=4\times 10^3$

对于 70%数据，有：$n<=5000,m<=2\times10^4$

对于100%数据，有：

1.$n<=2\times10^4,m<=5\times 10^4$，$0<=$电压$<=10^8$，$1<=$电阻$<=10^3$

2.只有有一个电源，电路不会有不规范的地方

3.最复杂的情况为并联中嵌套串联（如图A，当然支路可能更多，电阻串联数量有可能更多，但**支路不会出现并联**），保证**不会出现并联中再嵌套并联**（如图B的情况就不会出现）

![P5](https://cdn.luogu.com.cn/upload/pic/37253.png)

**特殊约定：**

20%数据保证：电路为纯串联电路

另外20%数据保证：电路为纯并联电路


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
title: "绫小路的特别考试"
layout: "post"
diff: 省选/NOI-
pid: P4964
tag: ['贪心', '枚举', '排序', '深度优先搜索 DFS', '栈']
---
# 绫小路的特别考试
## 题目背景

>  这世界上「胜利」便是一切。无关乎过程。
要付出多少牺牲都无所谓。只要最后我「胜出」那就行了。

![](https://i.loli.net/2018/10/06/5bb879f4ac370.jpg)
## 题目描述

一场新的特别考试来临了，这次的考试内容是（wan e de）文化课，但有所不同的是，考试中允许学生使用对讲机。然而，对讲机的接收范围是有限的（每个对讲机都能发送无限远，但是只能接收到接收范围内的信号），所以不是所有学生都能接收到其他同学的广播。

考试时，共有 $n$ 名学生坐成一排（从左至右依次编号为 $1$ ~ $n$），绫小路自己坐在第 $c$ 号位置。每名学生都有一个能力值 $w_i$。绫小路已经给每名学生安排了一个接收范围为 $d_i$ 的对讲机。

每名学生可以直接做出难度**不超过**自身能力值的**所有**题目，一旦一名学生凭能力做出某道题，他就会把这道题的做法进行广播。一名坐在位置 $i$，有接收范围为 $d_i$ 的对讲机的学生，可以接收到 $[i-d_i,\ i+d_i]$ 范围内所有学生的广播，若这个范围内有人公布了做法，则他将会做这道题，并也会把这道题的做法进行广播。

绫小路会问你一些问题：当一道题目难度为 $x$ 时，有多少学生会做这道题？由于绫小路想隐藏实力，他可能会修改自己的能力值。这两种操作分别用以下两种方式表示：

- $1\ x$，表示询问当一道题目难度为 $x$ 时，有多少学生会做这道题。

- $2\ x$，将绫小路的能力值修改为 $x$，即将 $w_c$ 修改为 $x$。

---

形式化描述（与上文同义）：

> 给你两个长为 $n$ 的数列 $w_{1..n}$ 和 $d_{1..n}$，以及一个 $w_c$ 可修改的位置 $c$。现在有两种操作（共 $m$ 次）：
- $1\ x$ 表示一次询问：设 $f_i=\begin{cases}1\quad(w_i\ge x)\\1\quad(\exists\ j \in [i - d_i,\ i + d_i],\ f_j=1)\\ 0\quad(otherwise)\end{cases}$，这里的 $f_i$ 定义中引用了 $f_j$，$\ \ \ \ $所以 $f_{1..n}$ 是会不断更新的，直到无法继续更新时，计算这次询问的答案为 $\sum\limits_{i=1}^nf_i$。
- $2\ x$ 表示一次修改：把 $w_c$ 修改为 $x$。
## 输入格式

由于数据量太大，为了避免读入耗时过长，使用**伪随机数生成器**的方式输入，并**强制在线**。

**建议你忽略输入格式，直接使用下面提供的数据生成器模板，了解具体的生成过程对你来说是不必要的。**

第一行，三个正整数 $n,\ m,\ c$，分别代表学生的总人数，操作总数和绫小路所在的位置。

第二行，五个整数 $\mathrm{seed},\ \mathrm{mind},\ \mathrm{maxd},\ \mathrm{mfq},\ k$。

> 此处的 $\mathrm{mind},\ \mathrm{maxd}$ 仅用于生成初始的 $d_{1..n}$，下文中调整 $d_p$ 所用的 $t$ 可能不在 $[\mathrm{mind},\ \mathrm{maxd}]$ 范围内。

接下来的 $k$ 行，每行两个整数 $p,\ t$，表示调整第 $p$ 号同学的对讲机接收范围（即 $d_p$）为 $t$。

> 若一名同学的对讲机接收范围被调整多次，以**最后一次**为准。

---

** 数据生成器模板：**

```cpp
#include <cstdio>

unsigned long long seed;
int n, m, c, mfq, mind, maxd, k, w[2000001], d[2000001];

inline int randInt() { seed = 99999989 * seed + 1000000007; return seed >> 33; } 

void generate()
{
	// 在读入种子后生成初始的 w 数组和 d 数组.
    for (int i = 1; i <= n; i++) { w[i] = randInt() % n; }
    for (int i = 1; i <= n; i++) { d[i] = randInt() % (maxd - mind + 1) + mind; }
}

void getOperation(int lastans, int &opt, int &x)
{
    // 生成一次操作的参数 opt 和 x, lastans 表示上一次询问的答案, 初始值为 0.
    if ((0ll + randInt() + lastans) % mfq) { opt = 1; } else { opt = 2; }
    x = (0ll + randInt() + lastans) % n;
}

int main()
{
    scanf("%d %d %d", &n, &m, &c);
    scanf("%llu %d %d %d %d", &seed, &mind, &maxd, &mfq, &k);
    generate();
    for (int i = 1; i <= k; i++)
    {
        int p, t;
        scanf("%d %d", &p, &t);
        d[p] = t;
    }
    // 从这里开始，你可以使用生成的 w 数组和 d 数组.
    int lastans = 0, finalans = 0;
    for (int i = 1; i <= m; i++)
    {
        int opt, x;
        getOperation(lastans, opt, x);
        if (opt == 1)
        {
            // 在这里执行询问操作，并用答案的表达式替代下面的 ___.      
            finalans = (finalans * 233ll + ___) % 998244353;
            lastans = ___;
        }
        else
        {
            // 在这里执行修改操作.
        }
    }
    printf("%d\n", finalans);
    return 0;
}
```
## 输出格式

令 $ans_i$ 表示第 $i$ 次询问（操作 $1$）的答案，$T_i=\begin{cases}(T_{i-1}\times 233+ans_i)\mod 998244353\quad(i\ge 1)\\0\quad(i=0)\end{cases}$

设 $q$ 表示询问（操作 $1$）的个数，你只需要输出一个整数 $T_q$。
## 样例

### 样例输入 #1
```
3 3 2
19720918 0 1 2 0
```
### 样例输出 #1
```
700
```
### 样例输入 #2
```
10 10 8
2102036 0 1 4 1
5 2
```
### 样例输出 #2
```
760521825
```
### 样例输入 #3
```
1000 1000 126
114321251 1 2 2 0
```
### 样例输出 #3
```
91977056
```
## 提示

### 你需要用到的变量：

$1\le c\le n\le 2\times 10^6$，$1\le m\le 2\times 10^6$，$0\le w_i,\ d_i,\ x<n$。

### 其它用于生成数据的变量：

$1\le \mathrm{seed},\ \mathrm{mfq}\le 10^9$，$0\le \mathrm{mind}\le \mathrm{maxd}<n$，$0\le k\le 2\times 10^5$，$1\le p\le n$，$0\le t<n$。

## 样例解释

### 样例一：

生成得到三名同学的能力值 $w_{1..3} = \{0,\ 1,\ 2\}$，对讲机接收范围 $d_{1..3} = \{1,\ 0,\ 1\}$。

第一个操作是 `1 1`，询问有多少同学会做难度为 $1$ 的题。

绫小路（第 $2$ 名同学）和第 $3$ 名同学能够独立做出这道题（$w_2 \ge 1$ ，$w_3 \ge 1$），第 $1$ 名同学虽然能力不足，但通过对讲机能接收到绫小路广播的做法（$2 \in [1 - d_1,\ 1 + d_1]$），所以他也会做。故 $ans_1 = 3$。

第二个操作是 `2 0`，修改绫小路（第 $2$ 名同学）的能力值为 $0$。此时 $w_{1..3} = \{0,\ 0,\ 2\}$。

第三个操作是 `1 1`，再次询问有多少同学会做难度为 $1$ 的题。

只有第 $3$ 名同学能够独立做出（$w_3 \ge 1$），然而第 $1$ 名同学和绫小路（第 $2$ 名同学）都无法接收到他广播的做法（$3 \notin [1 - d_1,\ 1 + d_1]$，$3 \notin [2 - d_2,\ 2 + d_2]$），做不出来。故 $ans_2 = 1$。

综上所述，$T_1 = ans_1 = 3$，$T_2 = 3 \times T_1+ ans_2 = 3 \times 233 + 1 = 700$，仅输出 $700$ 即可。

### 样例二：

生成得到 $w_{1..10} = \{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 7,\ 9,\ 5\}$，$d_{1..10} =\{1,\ 1,\ 1,\ 1,\ 2,\ 0,\ 1,\ 0,\ 1,\ 1\}$。

十次操作及对应结果如下所示：

`1 6`，查询操作，$ans_1 = 9$，$T_1 = 9$。

`2 2`，修改操作，$w_{1..10}$ 变为 $\{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 2,\ 9,\ 5\}$。

`1 7`，查询操作，$ans_2 = 2$，$T_2 = 2099$。

`1 3`，查询操作，$ans_3 = 9$，$T_3 = 489076$。

`2 4`，修改操作，$w_{1..10}$ 变为 $\{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 4,\ 9,\ 5\}$。

`1 3`，查询操作，$ans_4 = 10$，$T_4 = 113954718$。
  
`2 2`，修改操作，$w_{1..10}$ 变为 $\{1,\ 6,\ 6,\ 5,\ 3,\ 5,\ 2,\ 2,\ 9,\ 5\}$。
  
`1 9`，查询操作，$ans_5 = 2$，$T_5 = 597096118$。  

`1 0`，查询操作，$ans_6 = 10$，$T_6 = 367430437$。    

`1 3`，查询操作，$ans_7 = 9$，$T_7 = 760521825$。

仅输出 $760521825$ 即可。

### 样例三：

~~出题人有足够的良心写出这个样例的解释，可惜版面太小，写不下。~~


---

---
title: "[Cnoi2019] 雪松果树"
layout: "post"
diff: 省选/NOI-
pid: P5384
tag: ['2019', 'O2优化', '深度优先搜索 DFS', '差分']
---
# [Cnoi2019] 雪松果树
## 题目背景

幻想乡，冬。

一年一度，生长在高山上的雪松果树又结果了。

Cirno 不知从哪弄到了 $1,2,3\cdots9$ 颗雪松果,然后很开心的吃掉了其中 $6$ 颗，最后还剩最后 $1$ 颗。

Cirn o因为以后吃不到雪松果而感到忧愁,于是决定种在美丽的雾之湖畔。

第一天,发芽。

第二天,雪松果树长成了一颗参天大树, 上面长满了雪松果。

Cirno 在雪松果成熟之前早有一些问题想知道，但现在她忙于收集雪松果，就把问题丢给了你。
## 题目描述

雪松果树是一个以 $1$ 为根有着 $N$ 个节点的树。

除此之外, Cirno还有 $Q$ 个询问，每个询问是一个二元组 $(u,k)$ ,表示询问 $u$ 节点的 $k$-cousin 有多少个。

我们定义:

> 节点 $u$ 的 $1$-father 为 路径 $(1, u)$ （不含 u）上距 u 最近的节点
>
> 节点 $u$ 的 $k$-father 为 节点 「$u$ 的 $(k-1)$-father」 的 1-father
>
> 节点 $u$ 的 $k$-son 为所有 $k$-father 为 $u$ 的节点
>
> 节点 $u$ 的 $k$-cousin 为 节点「 $u$ 的 $k$-father」的 $k$-son (不包含 $u$ 本身)
## 输入格式

第一行,两个整数 $N$, $Q$

第二行, $N-1$ 个整数，第 $i$ 个表示 $i+1$ 号节点的 1-father

以下 $Q$ 行，每行一个二元组$(u,k)$
## 输出格式

一行，$Q$ 个数，每一个表示一个询问的答案。若 u 不存在 k-father，输出 0。
## 样例

### 样例输入 #1
```
5 2
1 2 1 4
2 1
3 2
```
### 样例输出 #1
```
1 1
```
## 提示

数据范围：

对于0%-10%的数据 $N,Q \le 100$

对于10%-20%的数据 $N \le 100,Q \le 10^6$

对于 20%-30% 的数据 $N \le 10^5,Q \le100$

对于 30%-35% 的数据 $N \le 10^4,Q \le 5000$

对于 35%-50% 的数据 $N \le 10^5,Q \le 10^5$

对于 50%-70% 的数据 保证树随机

对于 70%-100% 的数据 $N,Q \le 10^6$

另外存在一组记 $20$ 分的 hack 数据。


---

---
title: "[NOI2019] 回家路线"
layout: "post"
diff: 省选/NOI-
pid: P5468
tag: ['动态规划 DP', '2019', 'NOI', 'O2优化', '深度优先搜索 DFS', '生成树']
---
# [NOI2019] 回家路线
## 题目背景

本题原题数据强度较低，若想要测试较强数据可以去 [P6302](https://www.luogu.com.cn/problem/P6302)，除数据范围外均与原题相同。
## 题目描述

猫国的铁路系统中有 $n$ 个站点，从 $1 - n$ 编号。小猫准备从 $1$ 号站点出发，乘坐列车回到猫窝所在的 $n$ 号站点。它查询了能够乘坐的列车，这些列车共 $m$ 班，从$1 - m$编号。小猫将在 $0$ 时刻到达 $1$ 号站点。对于 $i$ 号列车，它将在时刻 $p_i$ 从站点 $x_i$ 出发，在时刻 $q_i$ 直达站点 $y_i$，小猫只能在时刻 $p_i$ 上 $i$ 号列车，也只能在时刻 $q_i$ 下 $i$ 号列车。小猫可以通过多次换乘到达 $n$ 号站点。一次换乘是指对于两班列车，假设分别为 $u$ 号与 $v$ 号列车，若 $y_u = x_v$ 并且 $q_u \leq p_v$，那么小猫可以乘坐完 $u$ 号列车后在 $y_u$ 号站点等待 $p_v - q_u$ 个时刻，并在时刻 $p_v$ 乘坐 $v$ 号列车。

小猫只想回到猫窝并且减少途中的麻烦，对此它用烦躁值来衡量。

- 小猫在站点等待时将增加烦躁值，对于一次 $t (t \geq 0)$ 个时刻的等待，烦躁值将增加 $At^2 + Bt + C$，其中 $A, B,C$ 是给定的常数。注意：小猫登上第一班列车前，即从 $0$ 时刻起停留在 $1$ 号站点的那些时刻也算作一次等待。

- 若小猫最终在时刻 $z$ 到达 $n$ 号站点，则烦躁值将再增加 $z$。

形式化地说，若小猫共乘坐了 $k$ 班列车，依次乘坐的列车编号可用序列 $s_1, s_2, \cdots , s_k$表示。该方案被称作一条可行的回家路线，当且仅当它满足下列两个条件：

1. $x_{s1} = 1$ , $y_{sk} = n$

2. 对于所有 $j (1 \leq j < k)$，满足 $y_{sj} = x_{s_{j+1}}$ 且 $q_{sj}\leq p_{s_{j+1}}$

对于该回家路线，小猫得到的烦躁值将为：

$$q_{s_k}+(A\times p_{s_1}^2+B\times p_{s_1}+C)+\sum_{j=1}^{k-1}(A(p_{s_{j+1}}-q_{s_j})^2+B(p_{s_{j+1}}-q_{s_j})+C)$$

小猫想让自己的烦躁值尽量小，请你帮它求出所有可行的回家路线中，能得到的最
小的烦躁值。题目保证至少存在一条可行的回家路线。

## 输入格式

第一行五个整数 $n, m, A, B,C$，变量意义见题目描述。

接下来 $m$ 行，第 $i$ 行四个整数 $x_i, y_i, p_i, q_i$，分别表示 $i$ 号列车的出发站、到达站、出发时刻与到达时刻。
## 输出格式

输出仅一行一个整数，表示所求的答案。

## 样例

### 样例输入 #1
```
3 4 1 5 10
1 2 3 4
1 2 5 7
1 2 6 8
2 3 9 10
```
### 样例输出 #1
```
94
```
### 样例输入 #2
```
4 3 1 2 3
1 2 2 3
2 3 5 7
3 4 7 9
```
### 样例输出 #2
```
34
```
## 提示

### 更多样例

您可以通过附加文件获得更多样例。

#### 样例 3

见附加文件的 `route/route3.in` 与 `route/route3.ans`。

该样例的数据类型与最终测试点 $5 \sim 8$ 一致。

#### 样例 4

见附加文件的 `route/route4.in` 与 `route/route4.ans`。

该样例的数据类型与最终测试点 $11 \sim 14$ 一致。

#### 样例 5

见附加文件的 `route/route5.in` 与 `route/route5.ans`。

该样例的数据类型与最终测试点 $18 \sim 20$ 一致。

### 样例 1 解释

共有三条可行的回家路线：

- 依次乘坐 1，4 号列车，得到的烦躁值为：$10 + (1 \times 3^2 + 5 \times 3 + 10) + (1 \times (9 - 4)^2 + 5 \times (9 - 4) + 10)= 104$
- 依次乘坐 2，4 号列车，得到的烦躁值为：$10 + (1 \times 5^2 + 5 \times 5 + 10) + (1 \times (9 - 7)^2 + 5 \times (9 - 7) + 10)= 94$
- 依次乘坐 3，4 号列车，得到的烦躁值为：$10 + (1 \times 6^2 + 5 \times 6 + 10) + (1 \times (9 - 8)^2 + 5 \times (9 - 8) + 10)= 102$

第二条路线得到的烦躁值最小为 $94$。

### 数据范围

对于所有测试点：$2\le n\le 10^5,1\le m\le 2\times 10^5,0 \le A \le 10 , 0 \le B, C \le 10^6,1 \le x_i, y_i \le n , x_i \neq y_i , 0 \le p_i < q_i \le 10^3$。

每个测试点的具体限制见下表：

| 测试点编号  |        $n$         |          $m$          | $A,B,C$ 的特殊限制 | 其他特殊条件 |
| :---------: | :----------------: | :-------------------: | :----------------: | :----------: |
|  $1\sim 2$  |     $\le 100$      |        $=n-1$         |         无         | $y_i=x_i+1$  |
|  $3\sim 4$  |     $\le 100$      | $\le 100$ |     $A=B=C=0$      | $y_i=x_i+1$  |
|  $5\sim 8$  | $\le 2\times 10^3$ |  $\le 4\times 10^3$   |     $A=B=C=0$      |  $x_i<y_i$   |
|     $9$     | $\le 2\times 10^3$ |  $\le 4\times 10^3$   |      $A=B=0$       |  $x_i<y_i$   |
|    $10$     | $\le 2\times 10^3$ |  $\le 4\times 10^3$   |       $A=0$        |  $x_i<y_i$   |
| $11\sim 14$ | $\le 2\times 10^3$ |  $\le 4\times 10^3$   |         无         |      无      |
|    $15$     |     $\le 10^5$     |  $\le 2\times 10^5$   |      $A=B=0$       |      无      |
| $16\sim 17$ |     $\le 10^5$     |  $\le 2\times 10^5$   |       $A=0$        |      无      |
| $18\sim 20$ |     $\le 10^5$     |  $\le 2\times 10^5$   |         无         |      无      |


---

---
title: "最优性剪枝"
layout: "post"
diff: 省选/NOI-
pid: P6048
tag: ['搜索', '数学', '2020', '线段树', '剪枝', '树链剖分', '期望']
---
# 最优性剪枝
## 题目背景

Nauuo 是一名出题人。

众所周知，某些出题人非常懒，导致[随便爆搜](https://www.luogu.com.cn/discuss/show/185420)加上一个[最优性剪枝](https://www.luogu.com.cn/discuss/show/184641)就能通过。Nauuo 决定把这些 naive 的暴力都卡掉。
## 题目描述

Nauuo 决定卡一个暴力搜索程序，为此她构建了一组数据。为了简化题目，你将得到这组数据产生的搜索树 $T$。$T$ 中包含 $n$ 个节点，依次编号为 $1 \sim n$，其中 $1$ 号点是 $T$ 的根节点。一个节点的深度是它到 $1$ 号点的简单路径上的节点个数。

这个程序的伪代码如下

```cpp
answer := inf

procedure dfs(node,depth)
	if (node is leaf) 
		answer := min(answer,depth)
		return
	if (depth < answer)
		for i in children of node
			dfs(i,depth+1)

dfs(1,1)
```

其中，`:=` 表示赋值运算。

翻译成人话就是说，这个暴力搜索程序将**深度优先**地遍历这棵搜索树，当访问到一个叶节点时，这个程序将用这个叶节点的深度更新答案。

同时，这个程序有一个最优性剪枝，也就是说，当这个程序访问到任意一个深度等于答案的节点时，它将不会再访问这个节点的子节点。

然而，可怜的 Nauuo 并不知道这个程序在某个节点时访问自己子节点的顺序，因此她认为每个节点访问子节点的顺序都是在所有可能的情况中等概率随机的，显然，一共有 $\prod d_i!$ 种情况，其中 $d_i$ 表示 $i$ 号节点的子节点数量。

现在她想知道这个程序访问到的节点数量的期望，以确定这个程序会不会被自己的数据卡掉。

为了避免浮点误差，答案对 $998244353$ 取模。保证答案能被表示为最简分数 $\frac{p}{q}$，你只需要输出一个 $x (0\leq x < 998244353)$ 使得 $qx \equiv p \pmod {998244353}$。
## 输入格式

第一行一个整数 $n$。

第二行 $n-1$ 个整数 $p_2, p_3 \cdots p_n$，其中 $p_i$ 表示 $i$ 号节点的父节点编号。
## 输出格式

一行一个整数，所求 $x$。
## 样例

### 样例输入 #1
```
4
1 1 3
```
### 样例输出 #1
```
499122180
```
### 样例输入 #2
```
3
1 2
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
13
1 1 1 3 5 4 2 3 7 4 4 6
```
### 样例输出 #3
```
776412285
```
## 提示

#### 样例解释

第一组样例的真实答案为 $\frac{7}{2}$。

一共只有两种情况，如果 $1$ 号节点先遍历 $3$ 号节点，则程序将访问到搜索树中所有节点。如果 $1$ 号节点先遍历 $2$ 号节点，则 $4$ 号节点不会被访问到。

第二组样例中，每个非叶节点的子节点都是唯一的，因此只有一种可能的情况，所有节点都必然被访问到。

第三组样例的真实答案为 $\frac{94}{9}$。

---

#### 数据范围

**「本题采用捆绑测试」**

对于所有测试点，保证 $1 \leq n \leq 3\times 10^5$，$1 \leq p_i < i$。

$\text{Subtask 1 (11 pts)}$ $n \leq 9$。

$\text{Subtask 2 (18 pts)}$ $n \leq 100$。

$\text{Subtask 3 (19 pts)}$ $n\leq 10^3$。

$\text{Subtask 4 (4 pts)}$ $p_i = i-1$。

$\text{Subtask 5 (8 pts)}$ $p_i =\lfloor \frac{i}{2} \rfloor$。

$\text{Subtask 6 (40 pts)}$ 无特殊限制。

---

#### 提示

如果你不知道怎么对分数取模，可以参考[这里](https://www.luogu.com.cn/problem/P3811)。




---

---
title: "[NEERC 2015] Binary vs Decimal"
layout: "post"
diff: 省选/NOI-
pid: P6124
tag: ['高精度', '2015', '广度优先搜索 BFS', 'ICPC']
---
# [NEERC 2015] Binary vs Decimal
## 题目描述

一个正数 $A$，如果它只包含 `0` 或 `1`，且它转成二进制后的 $B$，$A$ 是 $B$ 的后缀，这个数就是我们所要的。

现在给出数字 $N$，求第 $N$ 个这样的数。
## 输入格式

一行一个数 $N$。
## 输出格式

一行一个数，第 $N$ 个数。
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
10
```
### 样例输出 #2
```
1100
```
## 提示

$1 \le N \le 10^4$。

|原数|二进制|评论|
| :-----------: | :-----------: | :-----------: |
|$1$|$1$|√|
|$10$|$1010$|√|
|$11$|$1011$|√|
|$100$|$1100100$|√|
|$101$|$1100101$|√|
|$110$|$1101110$|√|
|$111$|$1101111$|√|
|$1000$|$1111101000$|√|
|$1001$|$1111101001$|√|
|$1010$|$1111110010$|×|
|$1011$|$1111110011$|×|
|$1100$|$10001001100$|√| 


---

---
title: "「EZEC-1」越狱"
layout: "post"
diff: 省选/NOI-
pid: P6436
tag: ['搜索', '图论', '二分', '最短路', 'Tarjan', '最近公共祖先 LCA']
---
# 「EZEC-1」越狱
## 题目背景

由于监狱长 PF 的疏忽，罪犯小 E 找到了机会越狱。

然而，不学无术的小 E 不懂得保密。PF 很快发现了他的计划，并对他展开了追捕。

因为小 E 自己造船，而狱长 PF 坐的是官方的船，所以在每条航道上的表现不一样，通过时间可能不同。具体见输入格式。

为了不饿肚子，小 E 准备买一个包来装食物。
## 题目描述

小 E 的逃跑路线可以被看作是在 $n$ 个岛屿上，这些岛屿由 $n-1$ 条航线两两相连。

每个岛上都有足够的补给。**假设他每在海上航行一天，就要花费一个单位的食物**。黑心老板规定，**能装 $k$ 单位的食物的背包将会卖 $k$ 万元**。

PF 可以命令在任意两个**通过时间不超过 $d$**，**并且岛 $v$ 到岛 $u$ 的航线上至少有 $q$ 个岛屿**（**不包括 $u$ 和 $v$**）的岛屿 $u$ 与 $v$ 之间建立一条双向航线，通过这条航线的时间为 $\left\lfloor \dfrac{time(u \to v)}{2}\right\rfloor$。由于经济问题，**他只能建造一条额外的航线**。

小 E 可以根据官方给出的航线（**包括新增的航线**）确认 PF 到每个岛上的**最短时间**。

PF 将会在 $t$ 时发现小 E 逃走并开始追击。

为了节省钱，同时逃脱 PF 的追捕，小 E 想请你帮他编一个程序，计算最小的 $k$，使得他能够顺利逃脱到至少 $l$ 个岛屿。

**补给不需要时间，中途抓住也算抓住，同时到达则不算。**

**在岛屿上进行补给不需要时间，可以无限进行补给，只要背包装得下。**

题意概括：

有两个人 $a$，$b$ 和一颗 $n$ 个节点组成的树，$a$ 比 $b$早出发 $t$ 秒。如果两个节点之间通过时间不超过 $d$ 则 $b$ 可以在这两点之间建一条通过时间为 $\left\lfloor \dfrac{time(u \to v)}{2}\right\rfloor$ 的线路，求一个方案使 $a$ 至少到 $l$ 个点的最短时间不比 $b$ 长，并在此基础下要求岛屿之间距离最大值尽量小。
## 输入格式

第一行五个整数，$n,t,d,l,q$，表示岛屿的数量，PF 发现的时间，建立航线要求的通过时间范围，至少要到达的岛屿数量，以及建立航线所要求的中间岛屿的数量。他们的出发点均为点 $1$ 。

接下来 $n-1$ 行，每行四个整数 $u,v,p_i,e_i$，表示岛屿 $u$ 和岛屿 $v$ 之间有一条道路。$p_i$ 表示小 E 走这条航线的时间，$e_i$ 表示 PF 走这条航线的时间。**航线为双向** 。
## 输出格式

若有解，输出共两行。

第一行一个整数 $k$，表示最小能够逃脱所需要的钱数（单位：万元）。

第二行一个整数 $r$，表示用 $k$ 万元买背包时的能跑到的岛屿数量（ $1$ 号岛也算在内）。

若无解，只需输出 "no solution" (引号不需要输出)。
## 样例

### 样例输入 #1
```
5 3 20 4 2
1 2 5 5
2 3 5 5
2 4 7 10
1 5 4 1
```
### 样例输出 #1
```
7
4
```
### 样例输入 #2
```
5 2 6 3 2
1 2 5 3
2 3 8 6
1 4 8 2
2 5 4 6
```
### 样例输出 #2
```
5
3
```
### 样例输入 #3
```
5 0 23 4 1
1 2 21 26
1 3 14 16
3 4 4 5
1 5 19 18
```
### 样例输出 #3
```
no solution
```
## 提示

【样例解释】

样例 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/sc3vdm8k.png)

对于样例 $1$，最后能到的点为 $1,2,4,5$，最小花费为 $7$。由于狱长 PF 从点 $3\to 5$ 要经过点为 $5\to1\to2\to3$，满足中间的点数 $\ge q$，故狱长 PF 可以连边点 $3$ 和点 $5$。如果狱长 PF 选择连边 $5\to3$，那么到点 $3$ 的时间为 $3+1+ \left\lfloor \dfrac{1+5+5}{2}\right\rfloor = 9$。而小 E 到点 $3$ 的最短时间为 $5 + 5 = 10$，不满足条件，故无论 $k$ 的大小，点 $3$ 都是不可到达的。


------------

【数据范围】

| 测试点编号 | $n\le$ | $t\le$ | $p_i,e_i\le$ |    $d\le$    | 时间限制| 空间限制 |特点|
| :----------: | :----------: | :----------: | :----------: | :----------: |:-----: | :----------: |:----------: |
|$1$ | $10$ | $50$ | $50$ | $50$ |$1s$ | $128M$ |加边操作 不影响答案|
|$2$ | $16$ | $50$ | $50$ | $50$ |$1s$ | $128M$ |无|
| $3,4$ | $500$ | ${500}$ | ${500}$ |$500$ | $1s$ |  $128M$ |加边操作 不影响答案|
| $5$ | $500$ | ${500}$ | ${500}$ |${500}$ | $1s$ |  $128M$ |$q = 0$|
| $6,7$ | $500$ | ${500}$ | ${500}$ |${500}$ | $1s$ |  $128M$ |无|
| $8$ | $\small{2.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ | $1s$ | $128M$ |加边操作 不影响答案|
| $9,10$ | $\small{2.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ | $1s$ | $128M$ |$q = 0$|
| $11 \sim 14$ | $\small{2.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ | $1s$ | $128M$ |无|
| $15$ | $\small{2.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ | $1s$ | $256M$ |无|
| $16$ | $\small{7.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ |  $2s$ | $256M$ |无|
| $17$ | $\small{7.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ |  $1s$ | $256M$ |无|
| $18 \sim 20$ | $\small{7.5 \times 10^3}$ | $10^8$ | $10^8$ |$10^8$ |  $3s$ |$512M$ |无|

对于 $100 \%$ 的数据，$n\le 7.5\times 10^3$，$1\le l\le n$，$0\le t \le 10^8$，$0 \le u_i<v_i \le n$，$1\le p_i,e_i,d\le 10^8$，$0\le q\le 20$。

**保证可能新建立的双向航线方案数不超过 $5 \times 10^6$**。



---

---
title: "[COCI 2013/2014 #1] SLASTIČAR"
layout: "post"
diff: 省选/NOI-
pid: P6540
tag: ['搜索', '2013', 'COCI（克罗地亚）']
---
# [COCI 2013/2014 #1] SLASTIČAR
## 题目背景

你需要比较一些序列号。
## 题目描述

现有 $M$ 个由数字 $0$ 到 $9$ 组成的短序列号和一个长度为 $N$ 的长序列号。

检查序列号 $A$ 是否包含长度为 $L$ 的序列号 $B$ 的过程如下：

- 将 $A$ 从位置 $1$ 到 $L$ 逐位与 $B$ 比较，一找到不同就将搜索段整体向后移，如果确定相等则停止比较。

- 将搜索段后移意为把 $x$ 到 $y$ 的搜索区域后移为 $x+1$ 和 $y+1$。

- 若剩下用于比较的位数不够，则在字符串末尾填充 `#`。如字符串为 `563232`，从位置 $4$ 到 $10$ 的填充为 `232####`。

- 若尝试了所有段均不匹配则停止比较。

对于每个短序列号，输出停止比较前比较的次数。
## 输入格式

输入的第一行是正整数 $N$。

输入的第二行是一个长度为 $N$ 的长序列号。

输入的第三行包含正整数 $M$。

接下来 $M$ 行每行包含一个长度不超过 $10^5$ 的短序列号。

短序列号总长度不超过 $3\times 10^6$。
## 输出格式

输出 $M$ 个整数，即对于第 $i$ 个短序列号所需的比较次数。
## 样例

### 样例输入 #1
```
7
1090901
4
87650
0901
109
090 
```
### 样例输出 #1
```
7
10
3
4
```
### 样例输入 #2
```
10
5821052680
4
210526
2105
582
105268
```
### 样例输出 #2
```
8
6
3
9
```
### 样例输入 #3
```
3
001
1
11
```
### 样例输出 #3
```
4
```
## 提示

#### 【数据规模与约定】
- 对于 $20\%$ 的数据，$1\le N\le 10^3$，$1\le M\le 500$，任意短序列号长度均不超过 $10^3$。
- 对于 $100\%$ 的数据，满足 $1\le N\le 10^5$，$1\le M\le 5\times 10^4$。
- 对于任意序列号中的一位字符 $c$，满足 $c\in\{0,1,2,3,4,5,6,7,8,9 \}$。

#### 【样例解释】

#### 样例 1 解释

第一个序列号：
- 机器人为每个段查找不同的第一位数字，总共进行 $7$ 次比较。

第二个序列号：
- 尝试第一个位置，立即发现差异，$1$ 次比较。
- 尝试第二个位置，找到第四个数字的差异，$4$ 次比较。
- 尝试第三个位置，立即找到差异，$1$ 次比较。
- 尝试第四个位置，找到匹配，$4$个比较。 
- 总计 $10$ 次比较。

第三序列号：
- 立即找到匹配项，总计 $3$ 个比较。

第四个序列号：
- 在第二个位置找到匹配项，总计 $1+3=4$ 个比较。

#### 样例 3 解释
按顺序将序列号 `11` 与段 `00`，$1$ 次比较，`01`，$1$ 次比较，和`1#`，$2$ 次比较，总计 $4$ 次比较。

--------
#### 【说明】
**题目译自 [COCI2013-2014](https://hsin.hr/coci/archive/2013_2014/) [CONTEST #1](https://hsin.hr/coci/archive/2013_2014/contest1_tasks.pdf)  _T6 SLASTIČAR_。**


---

---
title: "【模板】二分图最大权完美匹配"
layout: "post"
diff: 省选/NOI-
pid: P6577
tag: ['Special Judge', 'O2优化', '\ufeff基础算法', '广度优先搜索 BFS', 'KM算法', '其它技巧']
---
# 【模板】二分图最大权完美匹配
## 题目背景

> $\rm Love ~of ~my ~life$
>
> $\rm U~are~far~from~me$
> 
> $\rm U've ~ turned ~ me ~ on$
> 
> $\rm and ~ now ~ I ~ try ~ to ~ catch ~ up ~ with ~ you$
>
> $\rm Love ~ of ~ my ~ life ~ can't ~ you ~ see$
>
> $\rm I'll ~ always ~ try, ~ always ~ try$
>
> $\rm U ~ are ~ the ~ brightest ~ star ~ to ~ me$
> 
> $\rm No ~ matter ~ others ~ don't ~ know$
>
> $\rm what ~ it ~ means ~ to ~ me$
>
> ——  An adaptation of _Love of My Life_ by Queen


这是一道夹带私货的模板题。
## 题目描述

给定一张二分图，左右部均有 $n$ 个点，共有 $m$ 条带权边，且保证有完美匹配。

求一种完美匹配的方案，使得最终匹配边的边权之和最大。
## 输入格式

第一行两个整数 $n,m$，含义见题目描述。

第 $2\sim m+1$ 行，每行三个整数 $y,c,h$ 描述了图中的一条从左部的 $y$ 号结点到右部的 $c$ 号节点，边权为 $h$ 的边。
## 输出格式

**本题存在 Special Judge**。

第一行一个整数 $ans$ 表示答案。

第二行共 $n$ 个整数 $a_1,a_2,a_3\cdots a_n$，其中 $a_i$ 表示完美匹配下与**右部**第 $i$ 个点相匹配的左部点的编号。如果存在多种方案，请输出任意一种。
## 样例

### 样例输入 #1
```
5 7
5 1 19980600
4 2 19980587
1 3 19980635
3 4 19980559
2 5 19980626
1 2 -15484297
4 5 -17558732

```
### 样例输出 #1
```
99903007
5 4 1 3 2 

```
## 提示

#### 数据规模与约定
- 对于 $10\%$ 的数据，满足 $n\leq 10$。
- 对于 $30\%$ 的数据，满足 $n\leq 100$。
- 对于 $60\%$ 的数据，满足 $n\leq 500$，且保证数据随机 。
- 对于 $100\%$ 的数据，满足 $1\leq n\leq 500$，$1\leq m\leq n^2$，$-19980731\leq h \leq 19980731$ 。且保证没有重边。

数据由善于出锅的出题人耗时好久制造完成。

善良的杨村花提醒你，别忘了仔细观察一下边权范围哦~

善良的杨村花又提醒你，你的复杂度可能只是「看起来」很对哦~


---

---
title: "「SWTR-5」String"
layout: "post"
diff: 省选/NOI-
pid: P6652
tag: ['动态规划 DP', 'O2优化', '广度优先搜索 BFS', '哈希 hashing']
---
# 「SWTR-5」String
## 题目描述

小 A 有一个字符串 $t$。他可以进行以下操作：切掉 $t$ 的一个前/后缀，满足切掉的前/后缀为**切割后** $t$ 的子串。小 A 想得到字符串 $s$，请问他最少需要进行多少次操作。无解输出 $-1$。
## 输入格式

两行字符串分别表示 $t,s$。
## 输出格式

一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
abbabb
ba
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
fxofoxxooffoxooo
fox
```
### 样例输出 #2
```
8
```
### 样例输入 #3
```
abcdefghijklmnopq
rstuvwxyzz
```
### 样例输出 #3
```
-1
```
### 样例输入 #4
```
ycxcy
cxy
```
### 样例输出 #4
```
-1
```
## 提示

「样例说明」

样例 $1$：$\texttt{abbabb}\to \texttt{abba}\to \texttt{bba}\to \texttt{ba}$。方案不唯一。

样例 $2$：$\texttt{fxofoxxooffoxooo}\to\texttt{xofoxxooffoxooo}\to\texttt{foxxooffoxooo}\to\texttt{xooffoxooo}\to\texttt{ffoxooo}\to\texttt{ffoxoo}\to\texttt{ffoxo}\to\texttt{ffox}\to\texttt{fox}$。方案不唯一。

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（1 points）：$s=t$。
- Subtask 2（9 points）：$s$ 仅包含字母 $\texttt{a}$。
- Subtask 3（15 points）：$|t|\leq 100$。
- Subtask 4（17 points）：$|t|\leq 500$。
- Subtask 5（18 points）：$|t|\leq 1.5\times 10^3$。
- Subtask 6（15 points）：$|s|=4$，*数据随机。
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据：$1 \leq |s| \leq |t| \leq 5\times 10^3$，字符集 $\in[\texttt{a,z}]$。

*数据随机：$s,t$ 字符均随机，字符集 $\in[\texttt{a,c}]$。

**请注意常数优化。**

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) E。    
idea & solution：[Isaunoya](https://www.luogu.com.cn/user/96580) & [Alex_Wei](https://www.luogu.com.cn/user/123294)。


---

---
title: "边三连通分量"
layout: "post"
diff: 省选/NOI-
pid: P6658
tag: ['图论', '深度优先搜索 DFS', 'Tarjan']
---
# 边三连通分量
## 题目背景

对于一张无向图 $G = (V, E)$。

- 我们称两个点 $u, v ~ (u, v \in V, u \neq v)$ 是边三连通的，当且仅当存在三条从 $u$ 出发到达 $v$ 的，相互没有公共边的路径。
- 我们称一个点集 $U ~ (U \subseteq V)$ 是边三连通分量，当且仅当对于任意两个点 $u', v' ~ (u', v' \in U, u' \neq v')$ 都是边三连通的。
- 我们称一个边三连通分量 $S$ 是极大边三连通分量，当且仅当不存在 $u \not \in S$ 且 $u \in V$，使得 $S \cup \{u\}$ 也是边三连通分量。
## 题目描述

给出一个 $n$ 个点，$m$ 条边的无向图 $G = (V, E)$，$V = \{1, 2, \ldots, n\}$，请求出其所有的极大边三连通分量。
## 输入格式

第一行输入两个整数 $n, m$，表示点数、边数。

接下来 $m$ 行，每行输入两个数 $u, v$，表示图上的一条边。
## 输出格式

第一行输出一个整数 $s$，表示极大边三连通分量个数。

接下来输出 $s$ 行，每行若干整数，表示一个极大边三连通分量内所有点。

对于单个极大边三连通分量，请将点按照标号升序输出。对于所有极大边三连通分量，请按照点集内编号最小的点升序输出。
## 样例

### 样例输入 #1
```
4 5
1 3
1 2
4 1
3 2
3 4
```
### 样例输出 #1
```
3
1 3
2
4
```
### 样例输入 #2
```
17 29
1 2
1 10
1 10
2 3
2 8
3 4
3 5
4 6
4 6
5 6
5 6
5 7
7 8
7 11
7 12
7 17
7 17
8 9
9 10
11 12
11 17
12 13
12 16
13 14
13 15
13 16
14 15
14 16
15 16
```
### 样例输出 #2
```
7
1 10
2 8
3 4 5 6
7 11 17
9
12
13 14 15 16
```
## 提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/eqpng8sy.png)

如图，$1 \to 3$ 共有 $(1, 2, 3)$，$(1, 3)$，$(1, 4, 3)$ 三条路径，它们互相都没有相交的边。因此 $1$ 与 $3$ 在同一个边三连通分量中。

由于 $2$，$4$ 点度都只有 $2$，不可能有三条边不相交的到其它点的路径，因此它们自己形成边三联通分量。

---

#### 数据范围

- 对于 $30\%$ 的数据，$n \le 100$，$m \le 200$。
- 对于 $50\%$ 的数据，$n \le 1000$，$m \le 2000$。
- 对于 $80\%$ 的数据，$n \le 10 ^ 5$，$m \le 2 \times 10 ^ 5$。
- 对于 $100\%$ 的数据，$1 \le n, m \le 5 \times 10 ^ 5$，$1 \le u, v \le n$。可能有重边和自环。

---

#### 来源

题目搬运自 [Three-Edge-Connected Components](https://judge.yosupo.jp/problem/three_edge_connected_components)。


---

---
title: "[BalticOI 2013] Pipes (Day1)"
layout: "post"
diff: 省选/NOI-
pid: P6755
tag: ['搜索', '图论', '2013', 'BalticOI（波罗的海）']
---
# [BalticOI 2013] Pipes (Day1)
## 题目描述

给定一个 $N$ 点 $M$ 边的无向图，**保证图连通**。现在每个点都有一定量的水，现在可以在一条边上进行操作：

- 让水流出：给定 $d$，假设长度为 $m$，流的时间为 $s$，那么总共失水速度为 $\dfrac{2dm^3}{s}$，这条边两边的每个点的失水速度为 $\dfrac{dm^3}{s}$。
- 让水流进：给定 $p$，假设长度为 $m$，流的时间为 $s$，那么总共得水速度为 $\dfrac{2pm^3}{s}$，这条边两边的每个点的得水速度为 $\dfrac{pm^3}{s}$。

现在给定这个图，和每个点的水量的变化速度，求每条边的水量的变化速度的构造方案。
## 输入格式

第一行两个整数 $N,M$ 代表点数和边数。     
这 $N$ 个点编号为 $1$ 到 $N$。   
接下来 $N$ 行每行一个整数 $c_i$ 代表这个点的水量变化速度，正数为得水，负数为失水。     
接下来 $M$ 行每行两个整数代表一条边。
## 输出格式

如果不存在这样的构造方案或者有多解，只输出一个整数 `0`。   
如果存在这样的方案，输出 $M$ 行，每行一个整数代表每条边的水量变化速度。     
得水为正数，失水为负数。
## 样例

### 样例输入 #1
```
4 3
-1
1
-3
1
1 2
1 3
1 4
```
### 样例输出 #1
```
2
-6
2
```
### 样例输入 #2
```
4 5
1
2
1
2
1 2
2 3
3 4
4 1
1 3
```
### 样例输出 #2
```
0
```
## 提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le N \le 10^5$，$1 \le M \le 5 \times 10^5$，$-10^9 \le c_i \le 10^9$，如果有解且唯一解，每个答案在 $[-10^9,10^9]$ 的范围内。     
对于其中 $30\%$ 的数据，该图为一棵树。

#### 说明

翻译自 [BalticOI 2013 Day1 C Pipes](https://boi.cses.fi/files/boi2013_day1.pdf)。


---

---
title: "「PMOI-4」可怜的团主"
layout: "post"
diff: 省选/NOI-
pid: P7320
tag: ['搜索', '图论', '树形数据结构', 'Special Judge', 'O2优化', '深度优先搜索 DFS', '构造', '洛谷月赛']
---
# 「PMOI-4」可怜的团主
## 题目描述

lnlhm 被塞给了一张 $n$ 个点 $m$ 条边的**简单无向连通**图。很快，他就被 ducati 和 b6e0 盯上了。

ducati 希望能够从中找到**恰好** $\left \lceil \frac n 6 \right \rceil$ 条**不同**的路径，使得所有的点都被至少一条路径经过。

b6e0 希望找到一个大小**恰好**为 $\lfloor \frac n 3 \rfloor$ 的节点集合，使得它们之间**两两没有边**。

lnlhm 知道，如果他没有满足某个人的要求，那么他就会被揍。因此，他向你求助：是否存在一种选择边或点的方案，使得**最多被一个人揍**？
## 输入格式

第一行两个正整数 $n,m$，表示点数以及边数。

下面 $m$ 行，每行两个点 $u,v$，描述一条**无向边**。
## 输出格式

若想要满足 ducati 的需求，在第一行输出 $1$，并在下面的 $\left \lceil \frac {n} 6 \right \rceil$ 行中，每行输出一条路径，你需要保证这些路径两两不同（例如，不能同时输出 $5 \to 3 \to 1$ 和 $1 \to 3 \to 5$）。输出一条路径的格式如下：

- 先输出一个正整数 $k(1\le k\le n)$，表示路径经过的节点数。

- 接下来 $k$ 个正整数，表示路径上的点，点之间用空格隔开。你需要保证，每相邻两个点之间有连边，不存在一个点被**某条**路径经过不少于两次，且每个点均被至少一条路径经过。

若想要满足 b6e0 的需求，在第一行输出 $2$，并在第二行中输出 $\lfloor \frac n 3 \rfloor$ 个点表示选出的独立集，之间用空格隔开。

特别的，若两个人的要求一个也无法满足，那么输出一行 `Poor lnlhm!`。
## 样例

### 样例输入 #1
```
6 7
1 2
1 3
2 3
2 5
4 5
5 6
4 6
```
### 样例输出 #1
```
2
1 4
```
### 样例输入 #2
```
6 6
1 2
2 3
3 4
4 5
5 6
1 6
```
### 样例输出 #2
```
1
6 1 2 3 4 5 6
```
## 提示

【样例解释】

对于第一组样例，我们只需要为 b6e0 选出节点集合 $\{1,4\}$ 即可。注意，$\{1,5\}\{1,6\}\{2,4\}\{2,6\}\{3,4\}\{3,5\}\{3,6\}$ 同样合法。

对于第二组样例，我们只需要为 ducati 选出路径 $1 \to 2 \to 3 \to 4 \to 5 \to 6$ 即可。

【数据范围】

**本题采用捆绑测试**。

- Subtask 1（20pts）：$n,m\le10$。
- Subtask 2（20pts）：保证图为一棵树。
- Subtask 3（60pts）：无特殊限制。

对于 $100\%$ 的数据满足，$3\le n\le10^3$，$3\le m\le\dfrac{n(n-1)}2$，保证给定的图为简单无向连通图。

**温馨提示: 输入量较大，请使用较快的读入方式。**


---

---
title: "[JRKSJ R1] 1+1"
layout: "post"
diff: 省选/NOI-
pid: P7336
tag: ['搜索', '2021', '洛谷原创', '交互题', 'Special Judge', 'O2优化']
---
# [JRKSJ R1] 1+1
## 题目描述

### 玩法简介

「1+1」 是一款双人对抗游戏。两名玩家各自拥有两个数，每次一名玩家可以用自己的一个数加上对方的一个数，如果大于 $9$ 则取个位。双方轮流执行此步骤。如，下面记录了游戏的几个回合，玩家双方分别为 `a` 和 `b`：

在下面的局面解释中，第一个局面标 `*` 的是先手。

```
a:1 1*（初始局面）
b:1 2

a:1 3（1+2）
b:1 2

a:1 3
b:1 5（2+3）

a:6 3（1+5）
b:1 5
```
---

### 特殊局面

我们把下面的情况称为「攻击」：

```
3 3
5 3
6 1
9 1
```
这些攻击的「攻击度」为 $1$ ，除了 `9 1`。`9 1` 的攻击度为 $2$ 。

下面的情况称为「防御」：

```
5 1
5 5
```
这些防御的「防御度」为 $1$ ，除了 `5 5`。`5 5`的 防御度为 $2$ 。

当然，所有的攻击或防御不分两个数的顺序，如 `5 1` 和 `1 5` 都视作防御，而
 `9 1` 和 `1 9` 也都视为攻击，而攻击/防御度不变。

如果玩家 `a` 持有防御，而玩家 `b` 在下一步走成了攻击，如下面的情况：

```
a:1 5
b:1 1*

a:1 5
b:6 1
```
那么此时 `a` 持有防御度为 $1$ 的 `1 5`， `b` 持有攻击度为 $1$ 的 `6 1`，此时应该将 `a` 持有的数变成 `1 1` 而 `b` 的此次攻击无效。

也就是说，如果 `a` 的攻击的攻击度与 `b` 的防御的防御度相等，则将 `b` 的两个数变为 `1 1` 而 `a` 的此次攻击视作无效。

我们认为不属于上面的攻击/防御的攻击/防御度为 $0$ （如 `3 4` 等。）

特别的，如果遇到下面这种情况：

```
a:5 5
b:1 1*

a:5 5
b:1 6
```
`a` 的防御度为 $2$ 而 b 的攻击度为 $1$ 。此时应该把 `a` 变成 `5 1` 而 `b` 的此次攻击作废。



------------


### 胜利条件

如果一方走完一步后，他的攻击度严格大于另一方的防御度，则这一方获胜。此时不应该做任何改动，即使要把另一方变成 `1 1` 或 `5 1`。

下面给出了一个例子：

```
a:1 1
b:6 3*

a:1 1
b:6 4

a:1 5
b:6 4

a:1 5
b:6 9

a:1 1
b:6 9

a:1 1
b:6 0

a:1 7
b:6 0

a:1 7
b:6 1

（ b 胜）
```
为了消除歧义，下面再给出一些例子：

```
a:5 5
b:1 4*

a:1 1
b:1 9

a:1 0（ 1+9=10 ，个位为 0 ）
b:1 9

a:1 0
b:1 9（注意这里， b 用 1 （或 9 ）加了 a 的 0 ，这样也算一次新的攻击）

（ b 胜）
```

```
a:1 1*
b:1 4

a:1 5
b:1 4

a:1 5（因为是最后一步，无须变成“1 1”）
b:1 9（这里 b 的“1 9”直接碾压了 a 的“1 5”）

（ b 胜）
```

现在，你被要求写一个程序，作为先手通过交互的方式和 mcyl35 的程序玩这个游戏。
## 输入格式

第一行五个整数 $p_0,p_1,c_0,c_1,P$，分别表示你的两个数，mcyl35 的两个数和测试点编号。

下面每行两个整数 $x,y$，表示 mcyl35 的第 $x$ 个数加上了你的第 $y$ 个数。

本题使用 IO 交互，具体可见 [P1733 猜数（IO交互版）](https://www.luogu.com.cn/problem/P1733)。
## 输出格式

每行两个整数 $x,y$，表示你的第 $x$ 个数加上了 mcyl35 的第 $y$ 个数。
## 样例

### 样例输入 #1
```
1 1 1 2 0
1 1
1 0
```
### 样例输出 #1
```
0 0
0 1
0 0
```
## 提示

#### 数据规模与约定

对于测试点 $1$，保证玩家可以一步获胜。

对于测试点 $2$，保证 mcyl35 的程序随机走步。

对于其他测试点，无特殊约定。

对于 $100\%$ 的数据，$0\le p_0,p_1,c_0,c_1\le 9$。

#### 评分标准

* 有不合法的输出（如输出中含有除了 $0,1$ 之外的数），得 $0$ 分。

* 获胜或走了 $100$ 步及以上本测试点可以获得满分。

* 否则获得 $\lfloor \dfrac {st} {20} \rfloor$ 分，$st$ 表示走的步数，一步表示 mcyl35 走一步。

#### 提示

当交互库没有返回数时，说明结果已经被判定了。

#### 样例解释

```
pl:1 1*
cp:1 2

pl:2 1
cp:1 2

pl:2 1
cp:1 3

pl:5 1
cp:1 3

pl:5 1
cp:1 8

pl:6 1(胜)
cp:1 8
```


---

---
title: "自动兑换机（2021 CoE-I D）"
layout: "post"
diff: 省选/NOI-
pid: P7396
tag: ['动态规划 DP', '搜索', '2021']
---
# 自动兑换机（2021 CoE-I D）
## 题目描述

Mca 市的地铁公司决定采取一项新措施——勿需购票，投币上车。有传闻说此举是为了减少乘客购票的排队时间。地铁运营商找到了本市计算机协会（Association for Computing Machinery，ACM）旗下的自动收款机（Automated Checkout Machine，ACM）公司，要求开发一款自动兑换机（Automatic exChange Machine，ACM）来满足乘客的需求。他们雇用你来担任首席程序员为此机器编写程序。自动兑换机内部存放有各种面值的硬币，当乘客将纸币放入机器时，机器会自动根据当前可用的硬币面值将乘客的纸币兑换成等值的硬币。当然，乘客不愿意口袋里面装着一大堆硬币去挤地铁，因此兑换成的硬币数量越少越好。如果现有的硬币面值无法完成兑换要求，应该输出一行信息，提示乘客需要寻求人工窗口的服务。
## 输入格式

**输入包含多组测试数据**。

第一行一个整数 $T$，表示数据组数。每组测试数据一行，第一个为整数 $c$，表示硬币面值的种类，接下来是 $c$ 个整数，每个整数 $d_i（1 \leq i \leq c）$ 表示一种硬币的面值，以美分为单位，最后是一个实数 $m$，表示乘客需要兑换的纸币的总面值，以美元为单位。
## 输出格式

对于每行输入均输出一行，如果不存在兑换方案，输出 `No solution.`。否则，按以下格式输出具有最少硬币数量的兑换方案：首先输出方案中硬币的总个数，然后一个空格，接着按照样例输出的格式打印兑换序列，即依照面值从小到大的顺序，将方案使用的各个面值及其对应的硬币个数予以输出。如果存在多种具有最少硬币数量的兑换方案，输出字典序（即按 **[ASCII](https://baike.baidu.com/item/ASCII)** 序）最小的兑换方案。
## 样例

### 样例输入 #1
```
6
6 1 2 5 10 20 50 25.31
5 1 2 2 5 10 0.18
5 1 2 10 9 5 0.18
6 2 5 10 20 50 100 0.03
11 173 151 214 211 238 167 385 179 5 235 112 46.1
13 95 180 285 205 164 82 122 52 362 260 166 364 189 6.55
```
### 样例输出 #1
```
53 1*1+10*1+20*1+50*50
4 1*1+2*1+5*1+10*1
2 9*2
No solution.
14 112*2+151*1+385*11
4 122*1+164*1+180*1+189*1
```
## 提示

#### 样例说明

第一组测试数据，硬币共有 $6$ 种面值，分别为 $1$ 美分、$2$ 美分、$5$ 美分、$10$ 美分、$20$ 美分、$50$ 美分，需要将 $25.31$ 美元（$2531$ 美分）兑换成硬币，具有最少硬币数量的兑换方案为：$50$ 枚硬币，$1$ 枚 $1$ 美分的硬币，$1$ 枚 $10$ 美分的硬币，$1$ 枚 $20$ 美分的硬币，$50$ 枚 $50$ 美分的硬币。

第二组测试数据，硬币共有 $5$ 种面值，但不同的只有 $4$ 种面值，分别为 $1$ 美分、$2$ 美分、$5$ 美分、$10$ 美分，需要将 $0.18$ 美元（$18$ 美分）兑换成硬币，具有最少硬币数量的兑换方案为：$4$ 枚硬币，$1$ 枚 $1$ 美分的硬币，$1$ 枚 $2$ 美分的硬币，$1$ 枚 $5$ 美分的硬币，$1$ 枚 $10$ 美分的硬币。

第三组测试数据，硬币共有 $5$ 种面值，分别为 $1$ 美分、$2$ 美分、$5$ 美分、$9$ 美分、$10$ 美分，需要将 $0.18$ 美元（$18$ 美分）兑换成硬币，具有最少硬币数量的兑换方案为：$2$ 枚硬币，$2$ 枚 $9$ 美分的硬币。

第四组数据，不存在符合要求的兑换方案，输出： `No solution.` 。

第五组数据，最少硬币数量为 $14$，有以下三种兑换方案：
```cpp
14 112*2+151*1+385*11
14 167*1+179*2+235*1+385*10
14 173*2+179*1+235*1+385*10
```
按照题意，以下是字典序最小的兑换方案：
```cpp
14 112*2+151*1+385*11
```


第六组测试数据，最少硬币数量为 $4$，有以下七种兑换方案：
```cpp
4 52*2+189*1+362*1 
4 82*1+122*1+166*1+285*1 
4 95*2+180*1+285*1 
4 95*2+205*1+260*1 
4 95*1+166*1+189*1+205*1
4 122*1+164*2+205*1
4 122*1+164*1+180*1+189*1
```
按照题意，以下是字典序最小的兑换方案：
```cpp
4 122*1+164*1+180*1+189*1
```

------------

#### 数据范围与约定
对于 $100\%$ 的数据，$1 \leq T \leq 400，1 \leq c \leq 100$，$1 \leq d_i \leq 400$，$0 \lt m \leq 100$。表示乘客需要兑换的纸币的总面值的实数 $m$ 有三种情形：没有小数点（是一个整数）、小数点后有一位数字、小数点后有两位数字。

在输出兑换序列时，相同的硬币面值应该合并。例如，假定正确输出为：
```cpp
4 111*2+222*2
```
则以下输出为不符合要求的输出：
```cpp
4 111*1+111*1+222*2
4 111*2+222*1+222*1
4 111*1+111*1+222*1+222*1
```


---

---
title: "[CEOI 2002] Bugs Integrated,Inc."
layout: "post"
diff: 省选/NOI-
pid: P7689
tag: ['2002', 'CEOI（中欧）', '深度优先搜索 DFS', '状压 DP']
---
# [CEOI 2002] Bugs Integrated,Inc.
## 题目描述

Bugs Integrated,Inc. 是高级存储芯片的主要制造商。他们正在开始生产新的 $6$ TB Q-RAM 芯片。每个芯片由以 $2×3$ 的矩形排列的六个方形硅片块组成。Q-RAM 芯片的制造方式是将一块长方形的大硅片分成 $N×M$ 个方形硅片块。然后仔细测试所有方形硅片块，坏的用黑色标记。  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/qqjfauh0.png)  
最后，将硅片切割成存储芯片。每个芯片由 $2×3$（或
 $3×2$）单位方形硅片块组成。当然，任何芯片都不能包含任何坏的（标记的）方形硅片块。它可能不能将硅片切割成每一个好的方形硅片块都成为某些存储芯片的一部分。该公司希望尽可能少地浪费好方形硅片块。因此他们想知道如何切割硅片以尽可能多地切出芯片。  
现您将获得几个硅片的尺寸和其每个硅片所有坏方形硅片块的列表。你的任务是编写一个程序，计算每个硅片最多可以从其切下的芯片数量。
## 输入格式

第一行由一个整数 $D$ 组成，表示硅片的数量。接下来 $D$ 个部分，每个部分描述一个硅片。每个部分的第一行包含三个整数 $N$，$M$，$K$，其间由单个空格分隔。$N$ 是硅片的长度，$M$ 是它的高度，$K$ 是硅片中坏方硅片块的数量。以下 $K$ 行包含一个坏方硅片块列表。每行包含两个整数 $x$ 和 $y$，表示一个坏方硅片块的坐标（左上角的坐标为（$1,1$），左下角是 （$N,M$））。
## 输出格式

每行输出每个硅片最多可以从其切下的芯片数量。
## 样例

### 样例输入 #1
```
2
6 6 5
1 4
4 6
2 2
3 6
6 4
6 5 4
3 3
6 1
6 2
6 4
```
### 样例输出 #1
```
3
4
```
## 提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq D \leq 5$，$1 \leq N \leq 150$，$1 \leq M \leq 10$，$0 \leq K \leq M×N$，$1 \leq x \leq N$，$1 \leq y \leq M$。  
#### 样例说明  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/v4ugwh72.png)  
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2002 的 [Bugs Integrated,Inc.](https://web.ics.upjs.sk/ceoi/documents/tasks/bugs-tsk.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。


---

---
title: "「Stoi2029」以父之名"
layout: "post"
diff: 省选/NOI-
pid: P7816
tag: ['搜索', '图论', 'Special Judge', 'O2优化', '深度优先搜索 DFS', '图遍历', '欧拉回路', '构造', '2029']
---
# 「Stoi2029」以父之名
## 题目背景

> 以父之名判决  
> 那感觉没有适合字汇  
> 就像边笑边掉泪  
> 凝视着完全的黑  
> 阻挡悲剧蔓延的悲剧会让我沉醉  
> ——《[以父之名](https://www.bilibili.com/video/BV1fx411N7bU?p=36)》
## 题目描述

地狱里有 $n$ 个罪人在等待判决，编号为 $1$ 至 $n$。罪人们之间有 $m$ 条罪的联系，编号为 $1$ 至 $m$，每条联系 的值为 $1$ 或 $2$ 且恰好连接两个罪人。

称一个罪人的自负度为他和其他所有罪人之间联系的值之和。两个罪人之间可能不止有一条联系，此时这些联系的值都应该被计算。由于这些罪人承受了太多的罪恶，他们变得不和谐。具体地，每个罪人的自负度都是奇数。

现在，神明将要对他们进行判决。判决的具体方式为：将每条联系都进行定向，使得这条联系所连接的两个罪人中的一个受到惩罚，另一个受到救赎，它们的值均为这条联系的值。

由于神明秉承父的仁慈，希望罪人们更加均等地接受惩罚和救赎，于是他规定判决后每个罪人所受到的惩罚和救赎值总和之差的绝对值必须恰好为 $1$。

由于神明工作繁忙，因此他以父之名要求你为他找到一种判决的方法。由于父的指示不会有错，所以一定存在一种这样的方法。

---

#### 题意简述

给定一个 $n$ 个点 $m$ 条边的无向图，边权均为 $1$ 或 $2$。保证每个点所相连的边权值之和均为奇数。你需要将这些边定向，使每个点的入边权值和与出边权值和之差的绝对值恰为 $1$。保证有解。输出任意一种方案。
## 输入格式

第一行两个正整数：$n,m$，表示有 $n$ 个罪人和 $m$ 条罪的联系。

接下来 $m$ 行，第 $i+1$ 行为三个正整数：$u_i,v_i,w_i$，表示第 $i$ 条联系连接 $u_i$ 与 $v_i$ 且值为 $w_i$。
## 输出格式

共一行 $m$ 个数字，第 $i$ 个数字为 $0$ 表示使 $u_i$ 受到惩罚，使 $v_i$ 受到救赎；为 $1$ 表示使 $v_i$ 受到惩罚，使 $u_i$ 受到救赎。
## 样例

### 样例输入 #1
```
4 5
1 2 1
1 3 2
2 3 1
2 4 1
4 1 2

```
### 样例输出 #1
```
00100

```
## 提示

#### 样例解释

定向后的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/uhz96nbm.png)

更多样例详见题目附件 `trial_sample.zip`。

------

#### 数据范围

**本题采用捆绑测试。**

- 特殊性质 A：边权均为 $1$，且任意两点之间只存在一条简单路径，且没有重边。
- 特殊性质 B：同一个点至多只有一条边权为 $1$ 和一条边权为 $2$ 的边相连。

| Subtask | 分值 | $1\le n \le$ | $1\le m \le$ | 特殊性质 | 
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $7$ | $10$ | $15$ | 无 | 
| $2$ |  $20$ |$10^3$ | $3\times10^3$ | 无 |
| $3$ |  $20$ |$3 \times 10^5$ | $3 \times 10^5$ | A |
| $4$ | $20$ |$3 \times 10^5$ | $3 \times 10^5$ | B | 
| $5$ |  $33$ |$10^6$ | $3 \times 10^6$ | 无 |

对于 $100\%$ 的数据，$1 \le u_i,v_i \le n \le 10^6$，$1 \le m \le 3 \times 10^6$，$w_i \in \{1,2\}$。

在题目附件 `trial_sample.zip` 中：

- `trial_sample1.in` 即为样例 #1。
- `trial_sample2.in` 满足特殊性质 A。
- `trial_sample3.in` 满足特殊性质 B。
- `trial_sample4.in` 不满足特殊性质。

另外该目录下还有 `checker.exe`。

------

#### 提示

**本题输入输出量较大，请使用较快的输入输出方式。**

本题提供 [Special Judge 源码](https://www.luogu.com.cn/paste/7albhubs)和 `checker.exe`，供选手调试。Windows 下使用方法为:  
命令行在目标文件夹输入指令：
```
checker.exe data.in data.out data.out
```
其中 `data.in` 是输入数据文件，`data.out` 是程序运行结果文件。观察评判结果即可。

- `Perfect answer.` 表示答案正确。
-  `Wrong answer on node x, and the difference is d.` 表示答案错误，其中节点 $x$ 的入边权值和与出边权值和之差的绝对值为 $d$ 而不为 $1$。
- `Invalid answer.` 表示输出的字符串长度不正确或输出非法字符。

请务必保证**输出格式正确**，否则 Special Judge 可能会返回 Unknown Error 等不可预估的结果。


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
title: "[CCO 2021] Through Another Maze Darkly"
layout: "post"
diff: 省选/NOI-
pid: P7830
tag: ['2021', 'CCO（加拿大）', '深度优先搜索 DFS', '可持久化线段树']
---
# [CCO 2021] Through Another Maze Darkly
## 题目背景

**警告：滥用本题评测将被封号！**
## 题目描述

黑暗迷宫是一个树形结构，有 $n$ 个房间和 $n - 1$ 个走廊，房间编号 $1, 2, \cdots, n$。

黑暗迷宫里面漆黑一片，你看不见自己在哪里。为了辨别方向，每个房间有一个激光指示器，初始指向连接这个房间的某一个走廊。你重复执行如下策略行动：

- 将当前房间的激光指示器按顺时针方向旋转到下一个走廊
- 沿着激光指示器指向的走廊走到另一个房间

你打算从编号为 $1$ 的房间开始，将这个策略重复执行 $k$ 次，想知道自己会到达哪个房间。你觉得这个问题太简单了，于是进行了 $q$ 次询问。每次询问是相互独立的，即激光指示器每次都会回到初始状态。
## 输入格式

第一行，两个整数 $n, q$；

接下来 $n$ 行，第 $i$ 行描述第 $i$ 个房间。首先，一个整数 $k$ 表示房间 $i$ 连接的走廊数量，接下来 $k$ 个整数 $c_1, c_2, \cdots, c_k$，表示按顺时针顺序每个走廊另一头的房间编号。第 $i$ 个房间的激光指示器初始指向通往房间 $c_1$ 的走廊。

接下来 $q$ 行，每行一个正整数 $k$。
## 输出格式

对于每组询问，输出一行，表示所求的值。
## 样例

### 样例输入 #1
```
5 6
1 2
3 3 1 4
1 2
2 5 2
1 4
1
2
3
4
5
6
```
### 样例输出 #1
```
2
1
2
4
2
3
```
## 提示

#### 样例 #1 解释
初始激光指示器的指向如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2k48xyl0.png)
#### 数据范围
对于 $\frac{7}{45}$ 的数据，第 $i$ 个房间连接第 $i - 1$ 和第 $i + 1$ 个房间（如果这两个房间存在）；

对于另 $\frac{14}{45}$ 的数据，$2 \leq n \leq 2 \times 10^3$，$1 \leq q \leq 2 \times 10^3$；

对于另 $\frac{4}{15}$ 的数据，$q = 1$；

对于 $100\%$ 的数据，$2 \leq n \leq 8 \times 10^5$，$1 \leq q \leq 8 \times 10^5$，$1 \leq k \leq 10^{15}$，保证数据给出的是**一棵树**。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D1T3


---

---
title: "[CCO 2021] Bread First Search"
layout: "post"
diff: 省选/NOI-
pid: P7832
tag: ['动态规划 DP', '线段树', '2021', 'CCO（加拿大）', '广度优先搜索 BFS']
---
# [CCO 2021] Bread First Search
## 题目描述

这个国家有 $n$ 个城市和 $m$ 条双向道路。

有一个人要游览这个国家，但他很讲究。他要求游览线路必须是一个 BFS（Bread First Search，面包优先搜索）序，必须访问每个城市各一次，且满足以下条件：

- 首个城市可以任选；
- 除了首个城市外，每个城市被访问前至少有一个相邻城市已经被访问过；
- 每个城市与首个城市的距离单调不降。其中两个城市的距离定义为它们路径边数的最小值。

这个人还有强迫症，一定要按照编号 $1 \sim n$ 的顺序将每个城市访问一次。为了使这条游览线路符合上述所有要求，政府需要新修若干条道路。请问最少需要新修多少条道路？
## 输入格式

第一行，两个整数 $n, m$；

接下来 $m$ 行，每行两个整数 $a, b$，表示这个国家的一条双向道路。
## 输出格式

一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
2 0
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
6 3
1 3
2 6
4 5
```
### 样例输出 #2
```
2
```
## 提示

#### 样例 #2 解释
一种符合要求的方式是，在城市 $1, 2$ 之间修一条路，在城市 $1, 4$ 之间修一条路。此时城市 $1$ 与城市 $1 \sim 6$ 的距离分别是 $0, 1, 1, 1, 2, 2$。
#### 数据范围
对于 $\frac{11}{32}$ 的数据，$1 \leq n \leq 200$；

对于 $\frac{5}{8}$ 的数据，$1 \leq n \leq 5 \times 10^3$；

对于 $100\%$ 的数据，$1 \leq n \leq 2 \times 10^5$，$0 \leq m \leq \min(2 \times 10^5, \frac{n(n - 1)}{2})$，$1 \leq a, b \leq n$，**保证没有重边和自环**。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D2T2


---

---
title: "[ONTAK2010] Peaks 加强版"
layout: "post"
diff: 省选/NOI-
pid: P7834
tag: ['2010', '倍增', 'Kruskal 重构树', '深度优先搜索 DFS', '可持久化线段树']
---
# [ONTAK2010] Peaks 加强版
## 题目背景

原题链接：[P4197 Peaks](https://www.luogu.com.cn/problem/P4197)
## 题目描述

给定一张 $n$ 个点、$m$ 条边的无向图，第 $i$ 个点的权值为 $a_i$，边有边权。

有 $q$ 组询问，每组询问给定三个整数 $u, x, k$，求从 $u$ 开始只经过权值 $\leq x$ 的边所能到达的权值第 $k$ 大的点的权值，如果不存在输出 $-1$。

**本题强制在线。即：每次查询输入的是 $u', x', k'$，则 $u = (u' \operatorname{xor} \text{lastans}) \bmod n + 1$，$k$ 的解密方式与之相同，$x = x' \operatorname{xor} \text{lastans}$**。
## 输入格式

第一行，三个整数 $n, m, q$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$；

接下来 $m$ 行，每行三个整数 $s, t, w$，表示一条边的两个端点和权值；

接下来 $q$ 行，每行三个整数 $u', x', k'$。

**注意：处理第一组数据和无解时的 $\text{lastans} = 0$。**
## 输出格式

对于每组询问，输出一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
10 11 3
1 2 3 4 5 6 7 8 9 10
1 4 4
2 5 3
9 8 2
7 8 10
7 1 4
6 7 1
6 4 8
2 1 5
10 8 10
3 4 7
3 4 6
0 5 5
1 6 8
7 8 1
```
### 样例输出 #1
```
1
-1
8
```
## 提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq m, q \leq 5 \times 10^5$，$1 \leq s, t \leq n$，$1 \leq a_i, w \leq 10^9$，$0 \leq u', x', k' < 2^{31}$。


---

---
title: "[COCI 2021/2022 #2] Hiperkocka"
layout: "post"
diff: 省选/NOI-
pid: P7966
tag: ['搜索', '2021', 'Special Judge', '广度优先搜索 BFS', '位运算', '构造', 'COCI（克罗地亚）']
---
# [COCI 2021/2022 #2] Hiperkocka
## 题目描述

给定一个 $n$ 维的超正方体。

将该超正方体抽象为一个含 $2^n$ 个结点的图，结点分别用序号 $0,1,\cdots,2^n-1$ 表示。两个结点 $x,y$ 联通，当且仅当 $x \oplus y$ 为 $2$ 的整数幂。

现需将若干棵含有 $n$ 条边的树 $T$ 放置于该超正方体中。结点分别用序号 $0,1,\cdots,n$ 表示。给定每棵树的 $n$ 条边所连接的点的序号，则每一棵树需满足下列条件：

- 每个树上的结点都与超正方体的其中一个结点一一对应
- 每个结点互不相同
- 每一棵树的每一条边所连接的两个结点在超正方体中所对应的两个结点在超正方体中有边相连（即对应的两个结点的异或值为 $2$ 的整数幂）
- 每两棵树的边集在超正方体中所对应的边集不交，即超正方体中的每条边最多包含于一棵树中

请给定一种放置方案，使得放在超正方体中的每一棵树都符合题意。
## 输入格式

第一行一个正整数 $n$，表示超正方体的维数。

接下来的 $n$ 行，每行两个整数 $x,y$，表示在每棵树 $T$ 中，有一条连接 $x,y$ 的边。
## 输出格式

第一行输出放置的树的数目 $k$。

接下来的 $k$ 行，每行输出 $n+1$ 个整数，表示这棵树的对应结点在超正方体中的结点编号。
## 样例

### 样例输入 #1
```
1
0 1
```
### 样例输出 #1
```
1
0 1
```
### 样例输入 #2
```
2
0 1
1 2
```
### 样例输出 #2
```
2
0 1 3
0 2 3
```
### 样例输入 #3
```
3
0 1
0 2
0 3
```
### 样例输出 #3
```
4
0 1 2 4
3 1 2 7
5 1 4 7
6 2 4 7
```
## 提示

**【样例 3 解释】**

![](https://cdn.luogu.com.cn/upload/image_hosting/58a0p43i.png)

**【数据规模与约定】**

对于 $100\%$ 的数据，$1 \le n \le 16$，$0 \le x,y \le n$，$x \neq y$。

**【提示与说明】**

如果程序正确地放置了 $k$ 棵树，则每个测试点的得分为 $f(k) \cdot 110$，其中：

$$f(k)=\begin{cases}
\dfrac{0.7k}{2^{n-1}} & (k \lt 2^{n-1}) \cr
1 & (k=2^{n-1}) \cr
\end{cases}$$

若放置方式错误，则该测试点得分为 $0$。可以证明，总存在一种方式可以放置 $2^{n-1}$ 棵树。

因评分方式特殊，本题启用自行编写的 [Special Judge](https://www.luogu.com.cn/discuss/738608)，欢迎大家 hack。

**题目译自 [COCI 2021-2022](https://hsin.hr/coci/) [CONTEST #2](https://hsin.hr/coci/contest2_tasks.pdf) _Task 3 Hiperkocka_。**

**本题在 COCI 原题中满分 $110$，但由于为了计算方便，将满分修改为 $26 \times 5=130$。**


---

---
title: "「WHOI-2」D&D"
layout: "post"
diff: 省选/NOI-
pid: P8434
tag: ['动态规划 DP', '搜索', '数学', '二分', '洛谷原创', 'O2优化', '位运算', '双指针 two-pointer']
---
# 「WHOI-2」D&D
## 题目背景

有没有发现少了什么？

我们的 miku 决定出门逛街了。但是好巧不巧的就是她家里的装饰物少的可怜，并且只有一些数字可以作为装饰。

但是 miku 发现如果有若干个装饰物组成的数集 $A$，那么 $A$ 的子集 $f(A)$ 是最好看的（尽管不知道为什么）。所以就有了这道题。

但是因为看到了标题，所以聪明的你应该知道 miku 要去哪里了（误）。
## 题目描述

给定**不重**集合 $A$，定义其 _装饰子集_ 

$$f(A)=\{a\in A|\forall b\in A-\{a\},a|b\not= b \}$$

这里的 $\texttt{“|”}$ 表示按位或；这里 $b\in A-\{a\}$ 表示 $b\in A$ 且 $b\not=a$。

miku 有一个长度为 $n$ 的正整数序列 $a_i$。你要给这个序列连续地划分为若干个（至少一个）连续子串。要求这些连续子串元素所组成的**不重集合**的 _装饰子集_ 相同。

求方案数对 $10^9+7$ 取模。
## 输入格式

第一行一个正整数表示 $n$。

接下来长度为 $n$ 的正整数序列表示 $a_i$。
## 输出格式

一行一个正整数表示答案。
## 样例

### 样例输入 #1
```
10
1 2 3 4 5 5 4 3 2 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
9
1 2 2 1 1 1 2 2 1
```
### 样例输出 #2
```
16
```
## 提示

**【样例#1解释】** 可以证明，两种方法分别是：
$$[1,2,3,4,5,5,4,3,2,1]$$
$$[1,2,3,4,5],[5,4,3,2,1]$$

这里三个子集所组成的不重集合都是 $\{1,2,3,4,5\}$。它们的装饰子集都是 $\{3,5\}$。具体说明如下：

- $1:1|3=3$，故不属于。
- $2:2|3=3$，故不属于。
- $3:3|1=3,3|2=3,3|4=7,3|5=7$，故属于。
- $4:4|5=5$，故不属于。
- $5:5|1=5,5|2=7,5|3=7,5|4=5$，故属于。

---
**本题采用捆绑测试**

- $\text{subtask1(5pts)}:n\leq10$。
- $\text{subtask2(10pts)}:a_i\leq7$。
- $\text{subtask3(20pts)}:a_i=2^a+2^b$。其中 $a\not = b$。
- $\text{subtask4(20pts)}:a_i=2^a+2^b$。其中不保证 $a\not =b$。
- $\text{subtask5(10pts)}:$ 保证 $a_i$ 随机生成。
- $\text{subtask6(35pts)}:$ 无特殊限制。时限为 $3s$。

对于 $100\%$ 的数据，保证 $1\leq n\leq 3\times10^6,0\leq a_i\leq2\times 10^6$。


---

---
title: "「SWTR-8」扫雷计数"
layout: "post"
diff: 省选/NOI-
pid: P8455
tag: ['搜索', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「SWTR-8」扫雷计数
## 题目背景

2020 年 6 月的某一天，小 A 在等待网络加载的过程中打开了扫雷，从此便一发不可收拾。

小 A 是一个任何事都喜欢做到极致的人，玩游戏也不例外：他不惜花费大量时间不断尝试打破记录。一个个夜晚就在熟练的 `Alt + G + N` 中过去了。

> “这把有戏，前五十个雷只用了不到四十五秒”。他心里想着，紧握鼠标的手微微颤抖。
>
> “快，快，快 …… 还有最后二十个雷 ……”。
>
> 游戏的关键时刻，他难以按捺激动的心情。直到他遇到了二选一。
>
> 他愣了一下，随后迅速按下最后两块空地当中的一个。
> 
> 一束横贯屏幕的白色激光缓缓扫过，他知道自己打破了记录 …… [整整十二秒](https://cdn.luogu.com.cn/upload/image_hosting/1seixkiz.png)！巨大的惊喜让他跳了起来。
>
> 2020.6.19
## 题目描述

以下是简化后的扫雷游戏规则：

- 定义连通为 **八连通**。
- 如果打开雷，所有雷 **全部同时爆炸**，游戏结束。
- 如果打开空地，若其周围没有雷，则递归打开周围八个方块。
- [如图](https://cdn.luogu.com.cn/upload/image_hosting/kjjqs2v1.png)，点开任意红色框内方块均形成当前局面。


给定一张 $n\times m$ 的初始地图。小 A 决定搜出所有可能的局面，并找到最优鼠标点击顺序，从而速通这张地图。

为设置合适的数组大小，小 A 需要知道有多少种不同局面。对 $998244353$ 取模。

- 如果方块是雷，它有爆炸和未爆炸两种状态；如果方块是空地，它有打开和未打开两种状态。
- 两个局面不同，当且仅当存在方块状态不同。
- 保证周围无雷的空地形成不超过 $37$ 个连通块。
## 输入格式

第一行一个整数 $S$，表示该测试点的 Subtask 编号。

第二行两个整数 $n, m$。

接下来 $n$ 行，每行一个长度为 $m$ 的字符串描述地图，其中 $\texttt{.}$ 表示方块无雷，$\texttt{*}$ 表示方块有雷。
## 输出格式

一行一个整数表示答案。
## 样例

### 样例输入 #1
```
0
1 2
.*
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
0
2 3
..*
...
```
### 样例输出 #2
```
20
```
### 样例输入 #3
```
0
4 4
..*.
.*..
*...
....
```
### 样例输出 #3
```
2112
```
### 样例输入 #4
```
0
7 6
..*...
......
*...**
......
..*...
......
......
```
### 样例输出 #4
```
5041530
```
## 提示

**「样例解释」**

用 `.` 表示未打开的方块，`+` 表示打开的方块，`*` 表示未爆炸的雷，`!` 表示爆炸的雷。

样例 1 的所有 4 种局面为 `.*   +*   .!   +!`。

样例 2 的所有 20 种局面为
```plain
0
..*
...
   
1
++*  .+*  ..!  ..*  ..*
++.  ...  ...  .+.  ..+  
   
2
++!  ++*  .+!  .+*  .+*  ..!  ..!  ..*
++.  +++  ...  .+.  ..+  .+.  ..+  .++
   
3
++!  .+!  .+!  .+*  ..!
+++  .+.  ..+  .++  .++
   
4
.+!
.++
```

数字描述了最少点击次数。

**「数据范围与约定」**

**本题采用捆绑测试。**

设周围无雷的空地形成 $d$ 个连通块。

- Subtask #1（15 points）：$nm\leq 21$。
- Subtask #2（4 points）：地图中只有一个雷。
- Subtask #3（5 points）：$d = 0$。
- Subtask #4（6 points）：$d = 1$。
- Subtask #5（7 points）：$d = 2$。
- Subtask #6（8 points）：$d \leq 17$。依赖 Subtask #1，#2，#3，#4，#5。
- Subtask #7（9 points）：$d \leq 23$。依赖 Subtask #6。
- Subtask #8（16 points）：$d\leq 27$。依赖 Subtask #7。
- Subtask #9（17 points）：$d\leq 33$。依赖 Subtask #8。
- Subtask #10（13 points）：无特殊限制。依赖 Subtask #9。

对于 $100\%$ 的数据：

- $1\leq n, m\leq 500$。
- $0\leq d\leq 37$。
- **不保证** 地图中有雷或空地。

**「题目来源」**

- [Sweet Round 8](https://www.luogu.com.cn/contest/73382) D
- Idea & Solution：[Alex_Wei](https://www.luogu.com.cn/user/123294)。
- Tester：[chenxia25](https://www.luogu.com.cn/user/138400) & [asmend](https://www.luogu.com.cn/user/21658)。

感谢 [Elegia](https://www.luogu.com.cn/user/21423) 对本题做出的贡献。


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

---
title: "「KDOI-04」挑战 NPC Ⅲ"
layout: "post"
diff: 省选/NOI-
pid: P9036
tag: ['搜索', '图论', '贪心', '2023', '洛谷原创', 'O2优化', '枚举', '深度优先搜索 DFS', '剪枝', '组合数学', '洛谷月赛', '状压 DP']
---
# 「KDOI-04」挑战 NPC Ⅲ
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/zn5t5x28.png)
## 题目描述

小 S 有一个伟大的梦想：证明 $\text{P}=\text{NP}$。

有一天，他得知一般图最大独立集是 NPC 问题后，决定解决他。

当然小 S 太菜了，解决不了，于是求助于你：

> 给出一个含有 $n$ 个顶点，$m$ 条边的无向图 $G$，求 $G$ 中大小恰好为 $n-k$ 的独立集的数量。由于答案可能很大，请将其对 $998~244~353$ 取模。

小 S 不喜欢多测，因为他在 NOIp 中因为多测挂分，所以本题包含多组测试数据。
## 输入格式

**本题包含多组测试数据。**

第一行一个正整数 $T$，表示测试数据组数。

对于每组测试数据，第一行三个正整数 $n,m,k$。

接下来 $m$ 行，每行两个正整数 $u,v$ 表示一条边。

保证图中不存在自环，但**可能存在重边**。
## 输出格式

对于每组测试数据，输出一行一个正整数，表示符合要求的独立集数量。答案对 $998~244~353$ 取模。
## 样例

### 样例输入 #1
```
3
4 6 1
1 2
1 3
1 4
2 3
2 4
3 4
4 6 3
1 2
1 3
1 4
2 3
2 4
3 4
8 13 5
1 2
7 8
1 3 
2 5
3 8
6 8
4 7
5 6
5 7
5 8
6 7
1 8
3 5
```
### 样例输出 #1
```
0
4
8
```
## 提示

**【样例解释】**

对于第 $1,2$ 组测试数据，图是完全图，容易发现，完全图的最大独立集为 $1$，并且每一个顶点都单独构成一个独立集。因此第 $1$ 组测试数据的答案为 $0$，第 $2$ 组测试数据的答案为 $4$。

对于第 $3$ 组测试数据，该组数据中给出的无向图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/abt8ho3b.png)

其中，所有大小为 $3$ 的独立集为：

+ $\{2,4,8\}$；
+ $\{2,3,7\}$；
+ $\{3,4,6\}$；
+ $\{2,4,6\}$；
+ $\{1,4,6\}$；
+ $\{2,3,6\}$；
+ $\{1,4,5\}$；
+ $\{2,3,4\}$。

**【数据范围】**

**本题采用捆绑测试。**

![数据范围](https://cdn.luogu.com.cn/upload/image_hosting/p3jwdqp3.png)

对于 $100\%$ 的数据，保证 $1\leq n\leq10^5$，$0\le m\le 10^5$，$0\leq k\leq \min(n-1,18)$，$1\leq T\leq 10^{4}$，$\sum n,\sum m\leq10^6$。

并且对于每个测试点保证：

设 $K=\max k$，即该测试点中所有 $k$ 的最大值，

+ 若 $K\ge 17$，则 $T=1$；
+ 若 $K\ge 15$，则 $T\le 3$；
+ 若 $K\ge 10$，则 $T\le 5$；
+ 若 $K\ge 5$，则 $T\le 300$。



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
title: "「EZEC-14」终点"
layout: "post"
diff: 省选/NOI-
pid: P9462
tag: ['二分', '洛谷原创', '交互题', 'Special Judge', 'O2优化', '广度优先搜索 BFS', '深度优先搜索 DFS', '洛谷月赛']
---
# 「EZEC-14」终点
## 题目背景

~~出题人怎么还没鸟加这首歌啊。~~

于 2023.8.5 拿下。
## 题目描述

**这是一道交互题。**

dXqwq 有一棵 $n$ 个点的无根树，结点从 $1$ 到 $n$ 编号。您需要通过若干次询问得到这棵树的结构。

您可以选择两个整数 $1\leq u,v\leq n$，并输出 `? u v` 进行询问。

对于每次询问，如果 $u,v$ 的路径中点在一个结点上，交互库返回该点的编号，否则返回 ``0``。

请通过不超过 $147154$ 次询问，得到这棵树的结构。

保证树的形态是提前确定的，即**交互库不自适应。**

### 交互方式

输入测试点所在子任务编号 $id$ 和树的大小 $n$ 以开始交互。

交互过程中，您可以进行题目描述中的询问。

对于每次询问，如果你提供的 $u,v$ 不合法或者超出询问次数上限，交互库会返回 ``-1``，否则交互库将会返回一个非负整数，含义见「题目描述」。

当你读取到 ``-1`` 后应立刻退出程序，在此之后交互库的行为未定义。

在您确定答案后，请先输出 `!`，然后接下来 $n-1$ 行依次输出两个整数 ``u[i] v[i]`` 代表树的每条边，最后退出程序。你可以以任意顺序输出这些边。

在您输出一行后，请清空缓冲区：

- 在 C++ 中，使用 `fflush(stdout)` 或 `cout.flush()`。
- 在 Pascal 中，使用 `flush(output)`。
- 在 Python 中，使用 `stdout.flush()`。
- 其它语言请自行查阅文档。
## 输入格式

见「交互方式」。
## 输出格式

见「交互方式」。
## 样例

### 样例输入 #1
```
1 5

1

2

3

4

0
```
### 样例输出 #1
```
 
? 1 1

? 1 3

? 2 4

? 3 5

? 4 5

!
1 2
2 3
3 4
4 5
```
### 样例输入 #2
```
5 5

1

0

0

2

2
```
### 样例输出 #2
```
 
? 1 1

? 1 3

? 2 4

? 3 5

? 4 5

!
1 3
2 3
2 4
2 5
```
## 提示

**本题采用捆绑测试。**

-  Subtask 1（10 pts）：$n \leq 10$，树满足性质 A。
-  Subtask 2（10 pts）：保证存在一个点度数为 $n-1$。
-  Subtask 3（10 pts）：保证所有点度数 $\leq 2$。
-  Subtask 4（10 pts）：$n \leq 500$，树满足性质 A。
-  Subtask 5（20 pts）：$n \leq 500$。 
-  Subtask 6（20 pts）：树满足性质 A。
-  Subtask 7（20 pts）：无特殊限制。

性质 A：对于 $i=2,3,\cdots,n$ 存在整数 $1\leq j<i$ 满足有一条边连接 $i,j$。

对于 $100\%$ 的数据，$2 \leq n \leq 10^4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/3u2zy1q5.png)


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

